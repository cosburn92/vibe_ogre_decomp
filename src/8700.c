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

typedef struct {
    u8 (*lookat)[0x20];
    u8 (*hilite)[0x10];
    u8 (*mtx)[0x40];
} FbSet87;
extern FbSet87 *D_800E9BE0;

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;
extern Gfx *D_800E9BA0;
extern u16 D_800C4BE4; /* next free matrix pool entry */
#include "gbi_ultra.h"

#define GFX87(a, b)                                                                                \
    {                                                                                              \
        Gfx *_g = D_800E9BA0++;                                                                    \
                                                                                                   \
        _g->w0 = (a);                                                                              \
        _g->w1 = (b);                                                                              \
    }

s32 func_8007338C(void);
extern void *D_800C4B20; /* z buffer */
extern void *D_800E8210; /* frame buffer */

typedef struct {
    s16 vscale[4];
    s16 vtrans[4];
} Vp87;

void func_80078300(Camera *dst, Camera *src) {
    *dst = *src;
}

void guPerspective(void *m, u16 *perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale);
void guLookAt(void *m, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);
void guLookAtHilite(void *m, void *l, void *h, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt,
                    f32 xUp, f32 yUp, f32 zUp, f32 xl1, f32 yl1, f32 zl1, f32 xl2, f32 yl2, f32 zl2,
                    s32 twidth, s32 theight);
extern u16 D_800E7A0E; /* projection matrix index */
extern u16 D_800C4C24; /* view matrix index */
extern u16 D_800C4C48; /* next free look-at/hilite entry */

#define K0_TO_PHYS87(p) ((u32)(p) - 0x80000000)

/* Loads the camera's projection and view matrices; with a light direction set, the view comes
 * from guLookAtHilite and the look-at vectors are sent as well */
void func_8007834C(Camera *cam) {
    u16 perspNorm;

    D_800E7A0E = D_800C4BE4;
    guPerspective(D_800E9BE0->mtx[D_800C4BE4], &perspNorm, cam->fovy, cam->aspect, cam->near, cam->far,
                  cam->scale);
    GFX87(0xDB0E0000, perspNorm);
    GFX87(0xDA380007, K0_TO_PHYS87(D_800E9BE0->mtx[D_800C4BE4++]));
    if (cam->light1[0] == 0.0f && cam->light1[1] == 0.0f && cam->light1[2] == 0.0f) {
        D_800C4C24 = D_800C4BE4;
        guLookAt(D_800E9BE0->mtx[D_800C4C24], cam->eye[0], cam->eye[1], cam->eye[2], cam->at[0], cam->at[1],
                 cam->at[2], cam->up[0], cam->up[1], cam->up[2]);
    } else {
        D_800C4C24 = D_800C4BE4;
        guLookAtHilite(D_800E9BE0->mtx[D_800C4C24], D_800E9BE0->lookat[D_800C4C48],
                       D_800E9BE0->hilite[D_800C4C48], cam->eye[0], cam->eye[1], cam->eye[2], cam->at[0],
                       cam->at[1], cam->at[2], cam->up[0], cam->up[1], cam->up[2], cam->light1[0],
                       cam->light1[1], cam->light1[2], cam->light2[0], cam->light2[1], cam->light2[2],
                       cam->texWidth, cam->texHeight);
        GFX87(0xDC08000A, (u32)D_800E9BE0->lookat[D_800C4C48]);
        GFX87(0xDC08030A, (u32)D_800E9BE0->lookat[D_800C4C48++] + 0x10);
    }
    GFX87(0xDA380005, K0_TO_PHYS87(D_800E9BE0->mtx[D_800C4BE4++]));
}

void func_80078658(Camera *cam) {
    func_8007834C(cam);
}

/* Viewport and scissor box (x0, y0) - (x1, y1), clamped to the 320x240 screen. The viewport goes
 * in the next matrix pool entry; the commands are separated by pipe syncs. */
void func_80078674(s16 x0, s16 y0, s16 x1, s16 y1) {
    if (x0 < 0) {
        x0 = 0;
    } else if (x0 >= 320) {
        x0 = 319;
    }
    if (y0 < 0) {
        y0 = 0;
    } else if (y0 >= 240) {
        y0 = 239;
    }
    if (x1 < 0) {
        x1 = 0;
    } else if (x1 >= 320) {
        x1 = 319;
    }
    if (y1 < 0) {
        y1 = 0;
    } else if (y1 >= 240) {
        y1 = 239;
    }
    ((Vp87 *)D_800E9BE0->mtx[D_800C4BE4])->vscale[0] = (x1 - x0 + 1) * 2;
    ((Vp87 *)D_800E9BE0->mtx[D_800C4BE4])->vscale[1] = (y1 - y0 + 1) * 2;
    ((Vp87 *)D_800E9BE0->mtx[D_800C4BE4])->vscale[2] = 0x1FF;
    ((Vp87 *)D_800E9BE0->mtx[D_800C4BE4])->vscale[3] = 0;
    ((Vp87 *)D_800E9BE0->mtx[D_800C4BE4])->vtrans[0] = (x0 + x1) * 2;
    ((Vp87 *)D_800E9BE0->mtx[D_800C4BE4])->vtrans[1] = (y0 + y1) * 2;
    ((Vp87 *)D_800E9BE0->mtx[D_800C4BE4])->vtrans[2] = 0x1FF;
    ((Vp87 *)D_800E9BE0->mtx[D_800C4BE4])->vtrans[3] = 0;
    gDPPipeSync(D_800E9BA0++);
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xDC080008;
        _g->w1 = (u32)D_800E9BE0->mtx[D_800C4BE4++];
    }
    gDPPipeSync(D_800E9BA0++);
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xED000000 | _SHIFTL((s32)((f32)(x0 < 0 ? 0 : x0) * 4.0f), 12, 12) |
                 _SHIFTL((s32)((f32)(y0 < 0 ? 0 : y0) * 4.0f), 0, 12);
        _g->w1 = _SHIFTL((s32)((f32)(x1 + 1 == 320 ? 319 : x1 + 1) * 4.0f), 12, 12) |
                 _SHIFTL((s32)((f32)(y1 + 1 == 240 ? 239 : y1 + 1) * 4.0f), 0, 12);
    }
    gDPPipeSync(D_800E9BA0++);
}

/* When depth clearing is on (func_8007338C), fills (x0, y0) - (x1, y1) of the z buffer with the
 * maximum depth (the y0 clamp uses the screen width, as in the original), then points the colour
 * image back at the frame buffer */
void func_8007896C(s16 x0, s16 y0, s16 x1, s16 y1) {
    if (func_8007338C()) {
        if (x0 < 0) {
            x0 = 0;
        } else if (x0 >= 320) {
            x0 = 319;
        }
        if (y0 < 0) {
            y0 = 0;
        } else if (y0 >= 320) {
            y0 = 319;
        }
        if (x1 < 0) {
            x1 = 0;
        } else if (x1 >= 320) {
            x1 = 319;
        }
        if (y1 < 0) {
            y1 = 0;
        } else if (y1 >= 240) {
            y1 = 239;
        }
        GFX87(0xE7000000, 0);
        GFX87(0xE200001C, 0);
        GFX87(0xE7000000, 0);
        GFX87(0xE7000000, 0);
        GFX87(0xE7000000, 0);
        GFX87(0xE3000A01, 0x300000);
        GFX87(0xE7000000, 0);
        GFX87(0xFE000000, (u32)D_800C4B20 - 0x80000000);
        GFX87(0xFF10013F, (u32)D_800C4B20 - 0x80000000);
        GFX87(0xF7000000, 0xFFFCFFFC);
        GFX87(0xE7000000, 0);
        GFX87(0xF6000000 | _SHIFTL(x1, 14, 10) | _SHIFTL(y1, 2, 10), _SHIFTL(x0, 14, 10) | _SHIFTL(y0, 2, 10));
        GFX87(0xE7000000, 0);
        GFX87(0xE7000000, 0);
        GFX87(0xE7000000, 0);
        GFX87(0xE7000000, 0);
        GFX87(0xFF10013F, (u32)D_800E8210 - 0x80000000);
        GFX87(0xE7000000, 0);
        GFX87(0xE7000000, 0);
        GFX87(0xE3000A01, 0);
        GFX87(0xE7000000, 0);
    }
}

/* Fills (x0, y0) - (x1, y1) of the frame buffer with the RGBA5551 colour, after clearing the same
 * rectangle of the z buffer when depth clearing is on (func_8007338C). The y0 clamp uses the
 * screen width, as in func_8007896C. */
void func_80078C6C(u16 color, s16 x0, s16 y0, s16 x1, s16 y1) {
    if (x0 < 0) {
        x0 = 0;
    } else if (x0 >= 320) {
        x0 = 319;
    }
    if (y0 < 0) {
        y0 = 0;
    } else if (y0 >= 320) {
        y0 = 319;
    }
    if (x1 < 0) {
        x1 = 0;
    } else if (x1 >= 320) {
        x1 = 319;
    }
    if (y1 < 0) {
        y1 = 0;
    } else if (y1 >= 240) {
        y1 = 239;
    }
    GFX87(0xE7000000, 0);
    GFX87(0xE200001C, 0);
    GFX87(0xE7000000, 0);
    GFX87(0xE7000000, 0);
    GFX87(0xE7000000, 0);
    GFX87(0xE3000A01, 0x300000);
    GFX87(0xE7000000, 0);
    if (func_8007338C()) {
        GFX87(0xFE000000, (u32)D_800C4B20 - 0x80000000);
        GFX87(0xFF10013F, (u32)D_800C4B20 - 0x80000000);
        GFX87(0xF7000000, 0xFFFCFFFC);
        GFX87(0xE7000000, 0);
        GFX87(0xF6000000 | _SHIFTL(x1, 14, 10) | _SHIFTL(y1, 2, 10), _SHIFTL(x0, 14, 10) | _SHIFTL(y0, 2, 10));
        GFX87(0xE7000000, 0);
        GFX87(0xE7000000, 0);
        GFX87(0xE7000000, 0);
        GFX87(0xE7000000, 0);
    }
    GFX87(0xFF10013F, (u32)D_800E8210 - 0x80000000);
    GFX87(0xF7000000, (color << 16) | color);
    GFX87(0xE7000000, 0);
    GFX87(0xF6000000 | _SHIFTL(x1, 14, 10) | _SHIFTL(y1, 2, 10), _SHIFTL(x0, 14, 10) | _SHIFTL(y0, 2, 10));
    GFX87(0xE7000000, 0);
    GFX87(0xE7000000, 0);
    GFX87(0xE7000000, 0);
    GFX87(0xE3000A01, 0);
    GFX87(0xE7000000, 0);
}

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

/* Returns the link that holds handle's node, or the empty link where it would be inserted */
AssetNode **func_80079D60(AssetNode **link, u32 handle) {
    AssetNode *n;

    while (*link != NULL) {
        n = *link;
        if (handle == n->handle) {
            break;
        }
        if (n->handle < handle) {
            link = &n->right;
        } else {
            link = &n->left;
        }
    }
    return link;
}

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
