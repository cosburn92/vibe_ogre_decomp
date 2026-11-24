#include "common.h"
#include "chunk.h"
#include "heap.h"

/* Camera/viewport display-list helpers and the asset cache.
 *
 * The asset cache is a binary search tree of ROM chunks (AssetNode, keyed by chunk handle).
 * A chunk can be a table of further chunk handles, whose nodes hang off `children`, and a
 * chunk's decompressed sub-files are kept in a second tree (AssetSub, keyed by index). */

#define va_list char *
#define va_start(AP, LASTARG) (AP = ((char *)__builtin_next_arg(LASTARG)))
#define va_arg(AP, TYPE) ((TYPE *)(AP = (char *)((((s32)AP + 3) & -4) + 4)))[-1]

typedef struct AssetSub {
    /* 0x00 */ u32 index;
    /* 0x04 */ void *data;
    /* 0x08 */ u32 size;
    /* 0x0C */ s32 type; /* 1 = archive member, 2 = LZ, 3 = other compression */
    /* 0x10 */ struct AssetSub *left;
    /* 0x14 */ struct AssetSub *right;
} AssetSub; /* size 0x18 */

typedef struct AssetNode {
    /* 0x00 */ u32 handle;
    /* 0x04 */ void *data;
    /* 0x08 */ u32 size;
    /* 0x0C */ AssetSub *subs;
    /* 0x10 */ struct AssetNode *children;
    /* 0x14 */ struct AssetNode *left;
    /* 0x18 */ struct AssetNode *right;
} AssetNode; /* size 0x1C */

typedef struct {
    /* 0x00 */ s32 pos;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ void *data;
    /* 0x0C */ u32 size;
} ArchiveStream;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u32 index;
    /* 0x08 */ void *data;
    /* 0x0C */ u32 size;
} ArchiveRequest;

typedef struct {
    /* 0x00 */ f32 fovy;
    /* 0x04 */ f32 aspect;
    /* 0x08 */ f32 near;
    /* 0x0C */ f32 far;
    /* 0x10 */ f32 scale;
    /* 0x14 */ f32 eye[3];
    /* 0x20 */ f32 at[3];
    /* 0x2C */ f32 up[3];
    /* 0x38 */ f32 light1[3];
    /* 0x44 */ f32 light2[3];
    /* 0x50 */ s32 texWidth;
    /* 0x54 */ s32 texHeight;
} Camera; /* size 0x58 */

#define ASSET_FREE_TREE ((u32)-0x11)
#define ASSET_UNLOAD ((u32)-0x12)
#define ASSET_FREE_SUBS ((u32)-0x13)
#define ASSET_FREE_SUB ((u32)-0x14)
#define ASSET_ALL ((u32)-0x16)
#define ASSET_CMD_FIRST ((u32)-0x17)

extern AssetNode *D_800A8740; /* cache root */
extern AssetNode *D_800AF0C0; /* last node found */
extern AssetSub *D_800AF0C4;  /* last sub found */
extern u32 D_800C4BC0;        /* size of the last asset */

void bzero(void *p, s32 n);
f32 sqrtf(f32);
u32 DecodeLZ(u8 *dst, u8 *src);
u32 func_801AB720(void *src);
void func_801AB74C(void *dst, void *src);
s32 func_8007AE9C(ArchiveStream *s);
void func_8007ACB0(ArchiveStream *s, ArchiveRequest *req, s32 n);
void guMtxXFMF(f32 mf[4][4], f32 x, f32 y, f32 z, f32 *ox, f32 *oy, f32 *oz);
void guMtxL2F(f32 mf[4][4], void *m);

AssetNode *func_80079850(AssetNode *node);
AssetNode *func_800798AC(AssetNode *node, u32 handle);
void func_80079950(AssetNode *node, u32 index);
void func_80079AFC(AssetNode *node);
void func_80079BD8(AssetNode *node);
AssetSub *func_80079CB4(AssetSub *sub, u32 index);
AssetNode **func_80079D60(AssetNode **link, u32 handle);
AssetNode *func_80079D98(AssetNode *node);
void func_80079DF8(AssetNode *node);
void func_80079E50(AssetNode *node);
AssetSub *func_80079E9C(AssetSub *sub);
void func_80079EF4(AssetSub *sub, u32 index);

void func_80078300(Camera *dst, Camera *src) {
    *dst = *src;
}

INCLUDE_ASM("asm/nonmatchings/8700", func_8007834C);

void func_8007834C(Camera *cam);

void func_80078658(Camera *cam) {
    func_8007834C(cam);
}

INCLUDE_ASM("asm/nonmatchings/8700", func_80078674);

INCLUDE_ASM("asm/nonmatchings/8700", func_8007896C);

INCLUDE_ASM("asm/nonmatchings/8700", func_80078C6C);

/* Distance from the matrix's origin to pos, scaled to a fog/LOD value */
u16 func_80079028(f32 mf[4][4], f32 *pos, f32 range) {
    f32 v[3];
    f32 dx, dy, dz;

    guMtxXFMF(mf, 0.0f, 0.0f, 0.0f, &v[0], &v[1], &v[2]);
    dx = pos[0] - v[0];
    dy = pos[1] - v[1];
    dz = pos[2] - v[2];
    return ~(u32)(sqrtf(dx * dx + dy * dy + dz * dz) / range * 65534.0f);
}

typedef struct {
    u8 unk0[8];
    u8 (*mtx)[0x40];
} FbSet87;
extern FbSet87 *D_800E9BE0;
extern u16 D_800C4C24; /* modelview matrix index */
extern u16 D_800E7A0E; /* projection matrix index */

/* out = (x, y, z, 1) transformed by frame matrix idx */
static inline void Xform87(u16 idx, f32 x, f32 y, f32 z, f32 *out) {
    f32 mf[4][4];

    guMtxL2F(mf, D_800E9BE0->mtx[idx]);
    out[0] = mf[0][0] * x + mf[1][0] * y + mf[2][0] * z + mf[3][0];
    out[1] = mf[0][1] * x + mf[1][1] * y + mf[2][1] * z + mf[3][1];
    out[2] = mf[0][2] * x + mf[1][2] * y + mf[2][2] * z + mf[3][2];
    out[3] = mf[0][3] * x + mf[1][3] * y + mf[2][3] * z + mf[3][3];
}

/* Screen depth (z buffer value) of point (x, y, z) through the current modelview and projection */
#ifdef NON_MATCHING
/* 135/135 instructions, 73 words differ: the original frame is a[4] (0x10), matrix (0x20), b[4] (0x60), with the first result kept in fs0-fs2 and the matrix address rematerialised for each guMtxL2F */
s32 func_8007913C(f32 x, f32 y, f32 z) {
    f32 a[4];
    f32 b[4];

    Xform87(D_800C4C24, x, y, z, a);
    Xform87(D_800E7A0E, a[0], a[1], a[2], b);
    return (s32)(b[2] * 16352.0f / b[3]) + 0x3FE0;
}
#else
INCLUDE_ASM("asm/nonmatchings/8700", func_8007913C);
#endif

u32 func_80079358(u32 *p) {
    u32 sum = 0;
    u32 i;

    for (i = 0; i < 16; i++) {
        sum += *p++;
    }
    return sum;
}

void func_80079380(void) {
    D_800A8740 = NULL;
}

/* LoadAsset(handle, index..., command): walks the chunk tables and loads what the command asks for */
#ifdef NON_MATCHING
/* The original stores D_800A8740 before the first va_arg load; GCC here hoists the load above the store. */
void *LoadAsset(u32 handle, ...) {
    va_list ap;
    u32 arg;
    AssetNode *node;
    void *ret;
    u32 i;

    D_800A8740 = func_800798AC(D_800A8740, handle);
    va_start(ap, handle);
    for (arg = va_arg(ap, u32); arg < ASSET_CMD_FIRST; arg = va_arg(ap, u32)) {
        node = D_800AF0C0;
        func_80079850(node);
        node->children = func_800798AC(node->children, ((u32 *)node->data)[arg]);
    }
    node = D_800AF0C0;
    ret = NULL;
    switch (arg) {
        case (u32)-4:
        case (u32)-3:
            func_80079950(node, *(u32 *)ap);
            break;
        case (u32)-6:
        case (u32)-5:
            func_80079950(node, ASSET_ALL);
            break;
        case (u32)-10:
        case (u32)-9:
            func_80079AFC(node);
            break;
        case (u32)-14:
        case (u32)-13:
            func_80079BD8(node);
            break;
        case (u32)-1:
            func_80079850(node);
            D_800C4BC0 = node->size;
            ret = node->data;
            break;
        case (u32)-12:
        case (u32)-11:
        case (u32)-8:
        case (u32)-7:
        case (u32)-2:
            ret = (void *)(node->size / 4);
            for (i = 0; i < (u32)ret; i++) {
                node->children = func_800798AC(node->children, ((u32 *)node->data)[i]);
                func_80079850(D_800AF0C0);
                switch (arg) {
                    case (u32)-8:
                    case (u32)-7:
                        func_80079950(D_800AF0C0, ASSET_ALL);
                        break;
                    case (u32)-12:
                    case (u32)-11:
                        func_80079AFC(node);
                        break;
                    case (u32)-16:
                    case (u32)-15:
                        func_80079BD8(node);
                        break;
                }
                if (arg == (u32)-8 || arg == (u32)-12) {
                    HFree(node->data);
                    node->data = NULL;
                }
            }
            break;
    }
    if (ret == NULL) {
        ret = D_800AF0C4->data;
    }
    switch (arg) {
        case (u32)-14:
        case (u32)-10:
        case (u32)-9:
        case (u32)-6:
        case (u32)-4:
        case (u32)-3:
            HFree(node->data);
            node->data = NULL;
            break;
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/8700", LoadAsset);
#endif

/* UnloadAsset(handle or command, index..., command) */
void func_80079618(u32 handle, ...) {
    va_list ap;
    u32 arg;
    AssetNode **link;
    AssetNode *node;
    AssetNode **plink;
    AssetNode *pred;

    switch (handle) {
        case ASSET_FREE_TREE:
            D_800A8740 = func_80079D98(D_800A8740);
            return;
        case ASSET_UNLOAD:
            func_80079DF8(D_800A8740);
            return;
        case ASSET_FREE_SUBS:
            func_80079E50(D_800A8740);
            return;
    }
    link = func_80079D60(&D_800A8740, handle);
    if (*link == NULL) {
        return;
    }
    va_start(ap, handle);
    for (arg = va_arg(ap, u32); arg < ASSET_CMD_FIRST; arg = va_arg(ap, u32)) {
        link = func_80079D60(&(*link)->children, ((u32 *)(*link)->data)[arg]);
        if (*link == NULL) {
            return;
        }
    }
    node = *link;
    switch (arg) {
        case ASSET_FREE_TREE:
            if (node->right == NULL) {
                *link = node->left;
            } else if (node->left == NULL) {
                *link = node->right;
            } else {
                plink = &node->left;
                while ((*plink)->right != NULL) {
                    plink = &(*plink)->right;
                }
                pred = *plink;
                *plink = pred->left;
                pred->left = node->left;
                pred->right = node->right;
                *link = pred;
            }
            func_80079D98(node->children);
            func_80079E9C(node->subs);
            HFree(node->data);
            HFree(node);
            break;
        case ASSET_UNLOAD:
            func_80079DF8(node->children);
            if (node->subs != NULL) {
                HFree(node->data);
                node->data = NULL;
            }
            break;
        case ASSET_FREE_SUBS:
            func_80079E50(node->children);
            node->subs = func_80079E9C(node->subs);
            break;
        case ASSET_FREE_SUB:
            func_80079EF4(node->subs, *(u32 *)ap);
            break;
    }
}

inline AssetNode *func_80079850(AssetNode *node) {
    if (node->data == NULL) {
        node->size = ChunkSize(node->handle);
        if (node->size != 0) {
            node->data = HMalloc(node->size);
            LoadChunkRaw(node->data, node->handle);
        }
    }
    return node;
}

/* Find-or-insert in the node tree; D_800AF0C0 = the node for handle */
AssetNode *func_800798AC(AssetNode *node, u32 handle) {
    if (node != NULL) {
        if (handle == node->handle) {
            D_800AF0C0 = node;
            return node;
        }
        if (handle < node->handle) {
            node->left = func_800798AC(node->left, handle);
        } else {
            node->right = func_800798AC(node->right, handle);
        }
    } else {
        node = HMallocBack(sizeof(AssetNode));
        D_800AF0C0 = node;
        bzero(node, sizeof(AssetNode));
        node->handle = handle;
    }
    return node;
}

/* Extracts archive member index (or every member) of node's chunk */
#ifdef NON_MATCHING
/* Only the final `D_800C4BC0 = D_800AF0C4->size` uses v0 where the original uses v1. */
void func_80079950(AssetNode *node, u32 index) {
    ArchiveStream stream;
    ArchiveRequest req;
    u32 i;
    u32 end;

    stream.pos = 0;
    stream.data = node->data;
    stream.size = node->size;
    if (index == ASSET_ALL) {
        func_80079850(node);
        stream.data = node->data;
        stream.size = node->size;
        i = 0;
        end = func_8007AE9C(&stream);
    } else {
        i = index;
        end = i + 1;
    }
    for (; i < end; i++) {
        node->subs = func_80079CB4(node->subs, i);
        if (D_800AF0C4->data != NULL) {
            continue;
        }
        if (index != ASSET_ALL) {
            func_80079850(node);
            stream.data = node->data;
            stream.size = node->size;
        }
        req.unk0 = 0;
        req.index = i;
        func_8007ACB0(&stream, &req, 1);
        D_800AF0C4->data = req.data;
        D_800AF0C4->size = req.size;
        D_800AF0C4->type = 1;
    }
    D_800C4BC0 = D_800AF0C4->size;
}
#else
INCLUDE_ASM("asm/nonmatchings/8700", func_80079950);
#endif

/* Decompresses node's chunk (LZ) into sub 0 */
/* Only the final `D_800C4BC0 = D_800AF0C4->size` uses v0 where the original uses v1. */
void func_80079AFC(AssetNode *node) {
    node->subs = func_80079CB4(node->subs, 0);
    if (D_800AF0C4->data == NULL) {
        func_80079850(node);
        if (node->data != NULL) {
            D_800AF0C4->size = ReadU32BE(node->data);
            D_800AF0C4->data = HMalloc(D_800AF0C4->size);
            DecodeLZ(D_800AF0C4->data, node->data);
            D_800AF0C4->type = 2;
        }
    }
    {
        /* Identical stores in both arms keep the context pointer live so the size lands in v1
         * (technique from OB64-Decomp boot_resource_node_overlay_context_materialize,
         * MIT, (c) 2026 rempred). */
        AssetSub *ctx = D_800AF0C4;
        u32 size = ctx->size;

        if (ctx) {
            D_800C4BC0 = size;
        } else {
            D_800C4BC0 = size;
        }
    }
}

/* Only the final `D_800C4BC0 = D_800AF0C4->size` uses v0 where the original uses v1. */
void func_80079BD8(AssetNode *node) {
    node->subs = func_80079CB4(node->subs, 0);
    if (D_800AF0C4->data == NULL) {
        func_80079850(node);
        if (node->data != NULL) {
            D_800AF0C4->size = func_801AB720(node->data);
            D_800AF0C4->data = HMalloc(D_800AF0C4->size);
            func_801AB74C(D_800AF0C4->data, node->data);
            D_800AF0C4->type = 3;
        }
    }
    {
        /* Identical stores in both arms keep the context pointer live so the size lands in v1
         * (technique from OB64-Decomp boot_resource_node_overlay_context_materialize,
         * MIT, (c) 2026 rempred). */
        AssetSub *ctx = D_800AF0C4;
        u32 size = ctx->size;

        if (ctx) {
            D_800C4BC0 = size;
        } else {
            D_800C4BC0 = size;
        }
    }
}

/* Find-or-insert in a sub tree; D_800AF0C4 = the sub for index */
AssetSub *func_80079CB4(AssetSub *sub, u32 index) {
    if (sub != NULL) {
        if (index == sub->index) {
            D_800AF0C4 = sub;
            return sub;
        }
        if (index < sub->index) {
            sub->left = func_80079CB4(sub->left, index);
        } else {
            sub->right = func_80079CB4(sub->right, index);
        }
    } else {
        sub = HMallocBack(sizeof(AssetSub));
        D_800AF0C4 = sub;
        sub->index = index;
        sub->type = 0;
        sub->data = NULL;
        sub->size = 0;
        sub->right = NULL;
        sub->left = NULL;
    }
    return sub;
}

#ifdef NON_MATCHING
/* Register choice: the original reloads *link instead of keeping it in a register. */
AssetNode **func_80079D60(AssetNode **link, u32 handle) {
    if (*link == NULL || handle == (*link)->handle) {
        return link;
    }
    if ((*link)->handle < handle) {
        return func_80079D60(&(*link)->right, handle);
    }
    return func_80079D60(&(*link)->left, handle);
}
#else
INCLUDE_ASM("asm/nonmatchings/8700", func_80079D60);
#endif

AssetNode *func_80079D98(AssetNode *node) {
    if (node != NULL) {
        func_80079D98(node->children);
        func_80079D98(node->left);
        func_80079D98(node->right);
        func_80079E9C(node->subs);
        HFree(node->data);
        HFree(node);
        node = NULL;
    }
    return node;
}

void func_80079DF8(AssetNode *node) {
    if (node != NULL) {
        func_80079DF8(node->children);
        func_80079DF8(node->left);
        func_80079DF8(node->right);
        if (node->subs != NULL) {
            HFree(node->data);
            node->data = NULL;
        }
    }
}

void func_80079E50(AssetNode *node) {
    if (node != NULL) {
        func_80079E50(node->children);
        func_80079E50(node->left);
        func_80079E50(node->right);
        node->subs = func_80079E9C(node->subs);
    }
}

AssetSub *func_80079E9C(AssetSub *sub) {
    if (sub != NULL) {
        sub->left = func_80079E9C(sub->left);
        sub->right = func_80079E9C(sub->right);
        HFree(sub->data);
        HFree(sub);
        sub = NULL;
    }
    return sub;
}

void func_80079EF4(AssetSub *sub, u32 index) {
    if (sub != NULL) {
        if (index < sub->index) {
            func_80079EF4(sub->left, index);
        } else if (sub->index < index) {
            func_80079EF4(sub->right, index);
        } else {
            HFree(sub->data);
            sub->data = NULL;
            sub->size = 0;
            sub->type = 0;
        }
    }
}
