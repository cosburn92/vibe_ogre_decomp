#include "common.h"

/* Block header; the block's data follows it. Free blocks sit in a per-heap binary tree keyed by free size. */
typedef struct HeapNode {
    /* 0x00 */ struct HeapNode *prev;
    /* 0x04 */ struct HeapNode *next;
    /* 0x08 */ struct HeapNode **parent;
    /* 0x0C */ struct HeapNode *left;
    /* 0x10 */ struct HeapNode *right;
    /* 0x14 */ u32 used;
    /* 0x18 */ u32 free;
    /* 0x1C */ u8 unk1C[4];
} HeapNode; /* size 0x20 */

typedef struct {
    /* 0x00 */ HeapNode *start;
    /* 0x04 */ HeapNode *end;
    /* 0x08 */ HeapNode *root;
} Heap;

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

extern Heap gHeaps[];

typedef struct {
    /* 0x00 */ u8 unk00[0xC];
    /* 0x0C */ void *fb;
} FrameMsg;

/* Per-frame buffers, double-buffered; sizes come from the counts D_800C4C08.. set by func_80073164. */
typedef struct {
    /* 0x00 */ void *p[5];
    /* 0x14 */ Gfx *gfx;
} FbSet; /* size 0x18 */

extern void *D_800C4BB8;
/* Save-data table: records at base, stride apart; fields are (offset, bytes | 0x80 signed, bits) triples ending in bytes 0. */
typedef struct {
    /* 0x00 */ u8 *base;
    /* 0x04 */ s32 stride;
    /* 0x08 */ u8 *fields;
    /* 0x0C */ u32 count;
} SaveDesc; /* list ends at base NULL */

extern FbSet D_800A81C0[2];
extern u16 D_800C4C08;
extern u16 D_800E7D68;
extern u16 D_800C4A18;
extern u16 D_800E7A1C;
extern u16 D_800C4BCA;
extern u16 D_800C4AD8;
extern u8 D_800AEE72;
extern u8 D_800A81F0;
extern FbSet *D_800E9BE0;
extern s16 D_800E79E0;
extern s16 D_800E9BC4;
extern s16 D_800C4BE4;
extern s16 D_800C4BC8;
extern s16 D_800C4C48;
extern u32 D_800C4BC4;
extern u32 D_800A9E80;
extern u8 D_800A8215;
extern u8 D_800AEDF0[];
extern u8 D_800AEE30[];
extern u16 D_800AEE70;
void *HMallocBack(s32 size);
void func_800737A0(void);
void func_8007382C(void);
void guPerspective(void *m, u16 *perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale);
void guLookAt(void *m, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);
extern u8 D_800C4808;
u8 func_8016CD3C(void);
void osViSwapBuffer(void *fb);
void func_80089804(Gfx *start, s32 size, u8 a, s32 b);
void func_80073C48(void);
extern u32 D_800C4818;
extern u8 osViModeNtscLan1[];
extern u8 osViModeMpalLan1[];
extern u8 D_800AB9B0[];
extern u8 D_800ABA50[];
extern u16 D_800AEF10[4][16];
extern u16 D_800AEE90[4][16];
extern u8 D_800AEE78[];
extern u16 D_800C4BF0;
extern Gfx *D_800E9BA0;
extern u8 D_80186E70[];
extern u8 D_801869C8[];
void bzero(void *p, s32 n);
void _bcopy(void *src, void *dst, s32 n);
void osViSetMode(void *m);

extern u16 gHeapCount;
extern u16 gHeapAllocFlags;
extern s32 osTvType;
extern u8 D_800AEF9A;
extern u8 D_800A8210[];
extern u8 D_800A8211;
extern u8 D_800A8212;
extern u8 D_800A8213;
extern void *D_800AEF9C;
extern u32 D_800C4B20;
extern void *D_800E8210;
u32 osVirtualToPhysical(void *p);
extern u8 *D_800AEFB0;
extern s32 D_800AEFB4;
extern s32 D_800AEFB8;
extern s32 D_800AEFBC;
extern u32 D_800AEFC0;
extern u8 D_800AEF99;
extern s32 D_800A81F4;
extern u32 D_800A81F8;
extern u32 D_800C4BCC;
extern s32 D_800EB0DC;
extern s32 D_800EB12C;
extern s32 D_800EB17C;
extern s32 D_800EB1CC;
extern s32 D_800EB21C;
extern s32 D_800EB26C;
extern s32 D_800EB2BC;
extern s32 *D_800A8218[];
void osViSetSpecialFeatures(u32 f);
void func_80073CB0(u8 alpha);
u8 func_8016CD30(void);
extern u8 D_80186358[];
extern u8 D_80186610[];
void func_80081908(s32 a, s32 b);
void *HMalloc(s32 size);
void *HFree(void *p);
s32 HFindHeap(u32 p);
void func_80071950(HeapNode *n);
void func_800719E8(HeapNode **slot, HeapNode *n);
HeapNode *func_80071A3C(HeapNode *n, u32 size);
void func_80071A74(void);
HeapNode *func_80071E74(HeapNode *n, u32 size);
u32 osSetIntMask(u32 mask);
void __rmonMaskIdleThreadInts(void);
void func_8007328C(void);





void func_80070C60(u32 start, s32 size) {
    Heap *h;
    u32 end = (start + size) & ~0xF;

    start = (start + 0xF) & ~0xF;
    h = gHeaps;
    h->start = (HeapNode *)start;
    bzero((void *)start, 0x20);
    gHeaps[0].start->next = (HeapNode *)end;
    gHeaps[0].start->free = end - start - 0x20;
    gHeaps[0].root = NULL;
    func_800719E8(&h->root, h->start);
    D_800C4818 = 0;
    gHeapCount = 1;
    gHeapAllocFlags = 3;
    gHeaps[0].end = gHeaps[0].start->next;
}

INCLUDE_ASM("asm/nonmatchings/1060", AddHeap);

void func_80070F14(void) {
    gHeapCount = 1;
    gHeapAllocFlags = 3;
}

void *HMalloc(s32 size) {
    u16 flags;
    s32 h, count, i;
    HeapNode *b, *n;
    u32 total;

    size = (size + 0xF) & ~0xF;
    if (size == 0) {
        return NULL;
    }
    flags = gHeapAllocFlags;
    h = (flags >> 1) & 1;
    if (h) {
        count = gHeapCount - (~flags & 1);
        h = h & -(gHeapCount >= 2);
    } else {
        count = flags & 1;
    }
    for (i = 0; i < count; i++) {
        total = size + 0x20;
        b = func_80071A3C(gHeaps[h].root, total);
        if (b != NULL) {
            n = (HeapNode *)((u8 *)b + b->used + 0x20);
            n->next = b->next;
            b->next = n;
            if (n->next < gHeaps[h].end) {
                n->next->prev = n;
            }
            n->prev = b;
            func_80071950(b);
            b->free = 0;
            n->used = size;
            n->free = (u8 *)n->next - (u8 *)n - total;
            if (n->free > 0x20) {
                func_800719E8(&gHeaps[h].root, n);
            }
            return n + 1;
        }
        h = (h + 1) % gHeapCount;
    }
    return NULL;
}

/* Same as HMalloc. */
void *func_800710DC(s32 size) {
    u16 flags;
    s32 h, count, i;
    HeapNode *b, *n;
    u32 total;

    size = (size + 0xF) & ~0xF;
    if (size == 0) {
        return NULL;
    }
    flags = gHeapAllocFlags;
    h = (flags >> 1) & 1;
    if (h) {
        count = gHeapCount - (~flags & 1);
        h = h & -(gHeapCount >= 2);
    } else {
        count = flags & 1;
    }
    for (i = 0; i < count; i++) {
        total = size + 0x20;
        b = func_80071A3C(gHeaps[h].root, total);
        if (b != NULL) {
            n = (HeapNode *)((u8 *)b + b->used + 0x20);
            n->next = b->next;
            b->next = n;
            if (n->next < gHeaps[h].end) {
                n->next->prev = n;
            }
            n->prev = b;
            func_80071950(b);
            b->free = 0;
            n->used = size;
            n->free = (u8 *)n->next - (u8 *)n - total;
            if (n->free > 0x20) {
                func_800719E8(&gHeaps[h].root, n);
            }
            return n + 1;
        }
        h = (h + 1) % gHeapCount;
    }
    return NULL;
}

void *HMallocBack(s32 size) {
    u16 saved = gHeapAllocFlags;
    void *p;

    gHeapAllocFlags = 1;
    p = HMalloc(size);
    gHeapAllocFlags = saved;
    return p;
}

void *HFree(void *ptr) {
    s32 h = HFindHeap((u32)ptr);
    HeapNode *b;

    if (ptr == NULL) {
        return NULL;
    }
    b = (HeapNode *)ptr - 1;
    if (b->free > 0x20) {
        func_80071950(b);
    }
    ((HeapNode *)ptr - 1)->prev->next = ((HeapNode *)ptr - 1)->next;
    if (((HeapNode *)ptr - 1)->next < gHeaps[h].end) {
        ((HeapNode *)ptr - 1)->next->prev = ((HeapNode *)ptr - 1)->prev;
    }
    b = ((HeapNode *)ptr - 1)->prev;
    if (b->free > 0x20) {
        func_80071950(b);
    }
    b->free = (u8 *)b->next - ((u8 *)b + (b->used + sizeof(HeapNode)));
    if (b->free > 0x20) {
        func_800719E8(&gHeaps[h].root, b);
    }
    ((HeapNode *)ptr - 1)->next = NULL;
    ((HeapNode *)ptr - 1)->prev = NULL;
    if (++D_800C4818 > 0x3FFFF) {
        func_80071A74();
        D_800C4818 = 0;
    }
    return NULL;
}

u32 func_800713EC(void) {
    u16 flags;
    s32 h, count, i;
    u32 max = 0;
    HeapNode *n;

    flags = gHeapAllocFlags;
    h = (flags >> 1) & 1;
    if (h) {
        count = gHeapCount - (~flags & 1);
        h = h & -(gHeapCount >= 2);
    } else {
        count = flags & 1;
    }
    for (i = 0; i < count; i++) {
        for (n = gHeaps[h].root; n != NULL; n = n->right) {
            if (max < n->free) {
                max = n->free;
            }
        }
        h = (h + 1) % gHeapCount;
    }
    return max;
}

INCLUDE_ASM("asm/nonmatchings/1060", HIsAllocatedPointer);

s32 func_80071634(s32 *p) {
    return p[-3];
}

s32 func_8007163C(void) {
    return 0;
}

static inline void *HFreeInline(void *ptr) {
    s32 h = HFindHeap((u32)ptr);
    HeapNode *b;

    if (ptr == NULL) {
        return NULL;
    }
    b = (HeapNode *)ptr - 1;
    if (b->free > 0x20) {
        func_80071950(b);
    }
    ((HeapNode *)ptr - 1)->prev->next = ((HeapNode *)ptr - 1)->next;
    if (((HeapNode *)ptr - 1)->next < gHeaps[h].end) {
        ((HeapNode *)ptr - 1)->next->prev = ((HeapNode *)ptr - 1)->prev;
    }
    b = ((HeapNode *)ptr - 1)->prev;
    if (b->free > 0x20) {
        func_80071950(b);
    }
    b->free = (u8 *)b->next - ((u8 *)b + (b->used + sizeof(HeapNode)));
    if (b->free > 0x20) {
        func_800719E8(&gHeaps[h].root, b);
    }
    ((HeapNode *)ptr - 1)->next = NULL;
    ((HeapNode *)ptr - 1)->prev = NULL;
    if (++D_800C4818 > 0x3FFFF) {
        func_80071A74();
        D_800C4818 = 0;
    }
    return NULL;
}

/* HRealloc: resizes in place when possible, otherwise allocates, copies and frees. */
void *func_80071644(void *ptr, s32 size) {
    HeapNode *b;
    s32 d;
    void *p;

    if (size == 0) {
        HFreeInline(ptr);
        return NULL;
    }
    if (ptr == NULL) {
        return HMalloc(size);
    }
    size = (size + 0xF) & ~0xF;
    b = (HeapNode *)ptr - 1;
    d = size - b->used;
    if (d >= -0x7F) {
        if (d <= 0) {
            return ptr;
        }
        if (b->free < d) {
            goto copy;
        }
    }
    if (((HeapNode *)ptr - 1)->free > 0x20) {
        func_80071950(b);
    }
    ((HeapNode *)ptr - 1)->used = size;
    ((HeapNode *)ptr - 1)->free = (u8 *)((HeapNode *)ptr - 1)->next - ((u8 *)b + (size + sizeof(HeapNode)));
    if (((HeapNode *)ptr - 1)->free > 0x20) {
        func_800719E8(&gHeaps[HFindHeap((u32)b)].root, b);
    }
    return ptr;

copy:
    p = HMalloc(size);
    _bcopy(ptr, p, ((HeapNode *)ptr - 1)->used);
    HFreeInline(ptr);
    return p;
}

void func_80071950(HeapNode *n) {
    HeapNode *p;

    if (n->left == NULL) {
        if (n->right != NULL) {
            *n->parent = n->right;
            n->right->parent = n->parent;
        } else {
            *n->parent = NULL;
        }
    } else {
        *n->parent = n->left;
        n->left->parent = n->parent;
        if (n->right != NULL) {
            p = n->left;
            while (p->right != NULL) {
                p = p->right;
            }
            p->right = n->right;
            n->right->parent = &p->right;
        }
    }
}

void func_800719E8(HeapNode **slot, HeapNode *n) {
    HeapNode *r = *slot;

    if (r == NULL) {
        n->parent = slot;
        n->left = NULL;
        n->right = NULL;
        *slot = n;
    } else {
        func_800719E8(r->free < n->free ? &r->right : &r->left, n);
    }
}

HeapNode *func_80071A3C(HeapNode *n, u32 size) {
    HeapNode *best = NULL;

    while (n != NULL) {
        if (n->free < size) {
            n = n->right;
        } else {
            best = n;
            n = best->left;
        }
    }
    return best;
}

void func_80071A74(void) {
    u16 flags;
    s32 count, i;
    HeapNode *b, *r;
    HeapNode **slot;

    flags = gHeapAllocFlags;
    i = (flags >> 1) & 1;
    if (i) {
        count = gHeapCount - (~flags & 1);
    } else {
        count = flags & 1;
    }
    for (i = 0; i < count; i++) {
        b = gHeaps[i].start;
        gHeaps[i].root = NULL;
        while (b < gHeaps[i].end) {
            if (b->free > 0x20) {
                slot = &gHeaps[i].root;
                r = *slot;
                if (r == NULL) {
                    b->parent = slot;
                    b->left = NULL;
                    b->right = NULL;
                    *slot = b;
                } else {
                    func_800719E8(r->free >= b->free ? &r->left : &r->right, b);
                }
            }
            b = b->next;
        }
    }
}

s32 HFindHeap(u32 p) {
    s32 i;

    for (i = 0; i < gHeapCount; i++) {
        if (p >= (u32)gHeaps[i].start && p < (u32)gHeaps[i].end) {
            return i;
        }
    }
    return i;
}

static inline void TreeRemoveInline(HeapNode *n) {
    HeapNode *p;

    if (n->left == NULL) {
        if (n->right != NULL) {
            *n->parent = n->right;
            n->right->parent = n->parent;
        } else {
            *n->parent = NULL;
        }
    } else {
        *n->parent = n->left;
        n->left->parent = n->parent;
        if (n->right != NULL) {
            p = n->left;
            while (p->right != NULL) {
                p = p->right;
            }
            p->right = n->right;
            n->right->parent = &p->right;
        }
    }
}

/* Allocates from the top of the last free block that is large enough. */
void *func_80071C04(s32 size) {
    u16 flags;
    s32 h, count, i;
    HeapNode *b, *n, *r;
    HeapNode **slot;

    size = (size + 0xF) & ~0xF;
    if (size == 0) {
        return NULL;
    }
    flags = gHeapAllocFlags;
    h = (flags >> 1) & 1;
    if (h) {
        count = gHeapCount - (~flags & 1);
        h = h & -(gHeapCount >= 2);
    } else {
        count = flags & 1;
    }
    for (i = 0; i < count; i++) {
        b = func_80071E74(gHeaps[h].root, size + 0x20);
        if (b != NULL) {
            n = (HeapNode *)((u8 *)b + b->used + b->free - size);
            n->next = b->next;
            b->next = n;
            if (n->next < gHeaps[h].end) {
                n->next->prev = n;
            }
            n->prev = b;
            TreeRemoveInline(b);
            b->free = b->free - size - 0x20;
            slot = &gHeaps[h].root;
            n->used = size;
            n->free = 0;
            n->parent = slot;
            n->left = NULL;
            n->right = NULL;
            if (b->free > 0x20) {
                r = *slot;
                if (r == NULL) {
                    b->parent = slot;
                    b->left = NULL;
                    b->right = NULL;
                    *slot = b;
                } else {
                    func_800719E8(r->free >= b->free ? &r->left : &r->right, b);
                }
            }
            return n + 1;
        }
        h = (h + 1) % gHeapCount;
    }
    return NULL;
}

HeapNode *func_80071E74(HeapNode *n, u32 size) {
    if (n == NULL) {
        return NULL;
    }
    while (n->right != NULL) {
        n = n->right;
    }
    return n->free >= size ? n : NULL;
}

INCLUDE_ASM("asm/nonmatchings/1060", MainThreadEntry);

INCLUDE_ASM("asm/nonmatchings/1060", func_80072398);

void func_80072710(void) {
    if (osTvType != 1 && osTvType != 2) {
        for (;;) {
        }
    }
}

void func_80072738(s32 mode) {
    switch (osTvType) {
        case 1:
            switch (mode) {
                case 2:
                    osViSetMode(&osViModeNtscLan1);
                    break;
                case 9:
                    osViSetMode(D_800AB9B0);
                    break;
            }
            break;
        case 2:
            switch (mode) {
                case 2:
                    osViSetMode(&osViModeMpalLan1);
                    break;
                case 9:
                    osViSetMode(D_800ABA50);
                    break;
            }
            break;
    }
}

void func_800727D8(void) {
    s32 i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 16; j++) {
            D_800AEE90[i][j] = D_800AEF10[i][j] = 0;
        }
    }
    bzero(D_800AEE78, 0x18);
}

void func_8007284C(void) {
    u8 f = D_800AEF9A;

    if ((f & 1) && !(f & 4)) {
        if (f & 2) {
            if (D_800C4BF0 == 0) {
                D_800AEF9A = f & ~2;
            }
        } else if (D_800C4BF0 == 0xD020 || D_800C4BF0 == 0xF000) {
            D_800AEF9A = f | 6;
        }
    }
}

u8 func_800728BC(void) {
    u32 mask = osSetIntMask(1);
    u8 v = D_800AEF9A | 1;

    D_800AEF9A = v;
    osSetIntMask(mask);
    return v;
}

u8 func_80072900(void) {
    u32 mask = osSetIntMask(1);
    u8 v = D_800AEF9A & ~5;

    D_800AEF9A = v;
    osSetIntMask(mask);
    return v;
}

u8 func_80072944(void) {
    u32 mask = osSetIntMask(1);
    u8 v = D_800AEF9A;

    osSetIntMask(mask);
    return v & 4;
}

INCLUDE_ASM("asm/nonmatchings/1060", func_8007297C);

void func_8007307C(FrameMsg *msg) {
    u8 s;

    D_800C4BB8 = msg->fb;
    s = func_8016CD3C();
    if (s == 2) {
        switch (osTvType) {
            case 1:
                osViSetMode(D_800AB9B0);
                break;
            case 2:
                osViSetMode(D_800ABA50);
                break;
        }
    } else if (s == 1) {
        switch (osTvType) {
            case 1:
                osViSetMode(&osViModeNtscLan1);
                break;
            case 2:
                osViSetMode(&osViModeMpalLan1);
                break;
        }
    }
    if (s != 0) {
        osViSetSpecialFeatures(0x5A);
    }
    osViSwapBuffer(msg->fb);
}

void func_80073164(u8 relative, s16 a, s16 b, s16 c, s16 d, s16 e, s16 f) {
    if (!relative) {
        if (a >= 0) {
            D_800C4C08 = a;
        }
        if (b >= 0) {
            D_800E7D68 = b;
        }
        if (c >= 0) {
            D_800C4A18 = c;
        }
        if (d >= 0) {
            D_800E7A1C = d;
        }
        if (e >= 0) {
            D_800C4BCA = e;
        }
        if (f >= 0) {
            D_800C4AD8 = f;
        }
    } else {
        D_800C4C08 += a;
        D_800E7D68 += b;
        D_800C4A18 += c;
        D_800E7A1C += d;
        D_800C4BCA += e;
        D_800C4AD8 += f;
    }
    D_800AEE72 = 2;
}

void func_8007328C(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        HFree(D_800A81C0[i].p[0]);
        HFree(D_800A81C0[i].p[1]);
        HFree(D_800A81C0[i].p[2]);
        HFree(D_800A81C0[i].p[3]);
        HFree(D_800A81C0[i].p[4]);
        HFree(D_800A81C0[i].gfx);
    }
    D_800C4C08 = 0;
    D_800E7D68 = 0;
    D_800C4A18 = 0;
    D_800E7A1C = 0;
    D_800C4BCA = 0;
    D_800C4AD8 = 0;
    D_800AEE72 = 2;
    bzero(D_800A81C0, 0x30);
    D_800A81F0 = 0;
}

void func_8007337C(void) {
    D_800A8213 = 1;
}

u8 func_8007338C(void) {
    return D_800A8213;
}

void func_80073398(void) {
    __rmonMaskIdleThreadInts();
    func_8007328C();
    D_800A8213 = 0;
    D_800A8212 = 0;
    D_800A8211 = 0;
    D_800A8210[0] = 0;
    D_800AEF9C = HFree(D_800AEF9C);
    D_800C4B20 = 0;
}

#ifdef NON_MATCHING
/* Matches except v0/v1 swapped for the display-list head in the closing five commands. */
/* Starts a frame: reallocates the frame buffers after a size change, sets up the depth buffer and camera. */
void func_800733F8(void) {
    FbSet *cur = &D_800A81C0[D_800A81F0];
    Gfx *g;

    D_800E9BE0 = cur;
    if (D_800AEE72 != 0) {
        D_800AEE72--;
        HFree(cur->p[0]);
        D_800E9BE0->p[0] = HMallocBack(D_800C4C08 * 32);
        HFree(D_800E9BE0->p[1]);
        D_800E9BE0->p[1] = HMallocBack(D_800E7D68 * 16);
        HFree(D_800E9BE0->p[2]);
        D_800E9BE0->p[2] = HMallocBack(D_800C4A18 * 64);
        HFree(D_800E9BE0->p[3]);
        D_800E9BE0->p[3] = HMallocBack(D_800E7A1C * 120);
        HFree(D_800E9BE0->p[4]);
        D_800E9BE0->p[4] = HMallocBack(D_800C4BCA * 16);
        HFree(D_800E9BE0->gfx);
        D_800E9BE0->gfx = HMallocBack(D_800C4AD8 * 8);
    }
    D_800E79E0 = 0;
    D_800E9BC4 = 0;
    D_800C4BE4 = 0;
    D_800C4BC8 = 0;
    D_800C4C48 = 0;
    D_800E9BA0 = D_800E9BE0->gfx;
    if (D_800A8213 && D_800AEF9C == NULL) {
        D_800AEF9C = HMallocBack(0x2583F);
        D_800C4B20 = ((u32)D_800AEF9C + 0x3F) & ~0x3F;
    }
    D_800A8210[D_800C4BC4 % D_800A9E80] = D_800A8213;
    if (!D_800A8210[0] && !D_800A8211 && !D_800A8212 && D_800C4B20) {
        D_800AEF9C = HFree(D_800AEF9C);
        D_800C4B20 = 0;
    }
    func_800737A0();
    func_8007382C();
    if (D_800A8215) {
        guPerspective(D_800AEDF0, &D_800AEE70, 40.0f, 1.3333334f, 10.0f, 100.0f, 1.0f);
        guLookAt(D_800AEE30, 100.0f, 100.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        D_800A8215 = 0;
    }
    g = D_800E9BA0++;
    g->w0 = 0xDC08000A;
    g->w1 = (u32)D_800AEE30;
    g = D_800E9BA0++;
    g->w0 = 0xDC08030A;
    g->w1 = (u32)D_800AEE30 + 0x10;
    g = D_800E9BA0++;
    g->w0 = 0xDB0E0000;
    g->w1 = D_800AEE70;
    g = D_800E9BA0++;
    g->w0 = 0xDA380007;
    g->w1 = (u32)D_800AEDF0 - 0x80000000;
    g = D_800E9BA0++;
    g->w0 = 0xDA380005;
    g->w1 = (u32)D_800AEE30 - 0x80000000;
}
#else
INCLUDE_ASM("asm/nonmatchings/1060", func_800733F8);
#endif

void func_800737A0(void) {
    Gfx *g;

    g = D_800E9BA0++;
    g->w0 = 0xE7000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xDB060000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xE7000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xDE000000;
    g->w1 = (u32)D_80186E70;
    g = D_800E9BA0++;
    g->w0 = 0xDE000000;
    g->w1 = (u32)D_801869C8;
}

/* Clears the depth buffer (when requested) and the color buffer. */
void func_8007382C(void) {
    if (func_8016CD30()) {
        return;
    }
    if (D_800A8213) {
        Gfx *g = D_800E9BA0;

        D_800E9BA0 = g + 1;
        g[0].w0 = 0xFE000000;
        g[0].w1 = D_800C4B20 - 0x80000000;
        D_800E9BA0 = g + 2;
        g[1].w0 = 0xE7000000;
        g[1].w1 = 0;
        D_800E9BA0 = g + 3;
        g[2].w0 = 0xE7000000;
        g[2].w1 = 0;
        D_800E9BA0 = g + 4;
        g[3].w0 = 0xE3000A01;
        g[3].w1 = 0x300000;
        D_800E9BA0 = g + 5;
        g[4].w0 = 0xE7000000;
        g[4].w1 = 0;
        D_800E9BA0 = g + 6;
        g[5].w0 = 0xE200001C;
        g[5].w1 = 0;
        D_800E9BA0 = g + 7;
        g[6].w0 = 0xFF10013F;
        g[6].w1 = D_800C4B20 - 0x80000000;
        D_800E9BA0 = g + 8;
        g[7].w0 = 0xF7000000;
        g[7].w1 = 0xFFFCFFFC;
        D_800E9BA0 = g + 9;
        g[8].w0 = 0xE7000000;
        g[8].w1 = 0;
        D_800E9BA0 = g + 10;
        g[9].w0 = 0xF64FC3BC;
        g[9].w1 = 0;
        D_800E9BA0 = g + 11;
        g[10].w0 = 0xE7000000;
        g[10].w1 = 0;
        D_800E9BA0 = g + 12;
        g[11].w0 = 0xE7000000;
        g[11].w1 = 0;
    }
    {
        Gfx *g = D_800E9BA0;

        D_800E9BA0 = g + 1;
        g[0].w0 = 0xE7000000;
        g[0].w1 = 0;
        D_800E9BA0 = g + 2;
        g[1].w0 = 0xE7000000;
        g[1].w1 = 0;
        D_800E9BA0 = g + 3;
        g[2].w0 = 0xE3000A01;
        g[2].w1 = 0x300000;
        D_800E9BA0 = g + 4;
        g[3].w0 = 0xE7000000;
        g[3].w1 = 0;
        D_800E9BA0 = g + 5;
        g[4].w0 = 0xE200001C;
        g[4].w1 = 0;
        D_800E9BA0 = g + 6;
        g[5].w0 = 0xFF10013F;
        g[5].w1 = osVirtualToPhysical(D_800E8210);
    }
    {
        Gfx *g = D_800E9BA0;

        D_800E9BA0 = g + 1;
        g[0].w0 = 0xF7000000;
        g[0].w1 = 0x10001;
        D_800E9BA0 = g + 2;
        g[1].w0 = 0xE7000000;
        g[1].w1 = 0;
        D_800E9BA0 = g + 3;
        g[2].w0 = 0xF64FC3BC;
        g[2].w1 = 0;
        D_800E9BA0 = g + 4;
        g[3].w0 = 0xE7000000;
        g[3].w1 = 0;
        D_800E9BA0 = g + 5;
        g[4].w0 = 0xDE000000;
        g[4].w1 = (u32)D_801869C8;
    }
}

void func_80073AE4(void) {
    Gfx *g;

    func_80073C48();
    g = D_800E9BA0++;
    g->w0 = 0xDE000000;
    g->w1 = (u32)D_801869C8;
    g = D_800E9BA0++;
    g->w0 = 0xDE000000;
    g->w1 = (u32)D_80186E70;
    g = D_800E9BA0++;
    g->w0 = 0xE7000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xE9000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xDF000000;
    g->w1 = 0;
    func_80089804(D_800E9BE0->gfx, (D_800E9BA0 - D_800E9BE0->gfx) * sizeof(Gfx), D_800C4808, 1);
    D_800A8213 = 0;
    D_800A81F0 ^= 1;
}

void func_80073BD0(void) {
    Gfx *g;

    osViSetSpecialFeatures(0x5A);
    g = D_800E9BA0++;
    g->w0 = 0xE7000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xE3001801;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xE3001A01;
    g->w1 = 0x30;
}

void func_80073C48(void) {
    if (D_800AEF99 != 0) {
        if (D_800AEF99 > 12) {
            D_800AEF99 = 12;
        }
        func_80073CB0(D_800AEF99 * 255 / 12);
    }
}

void func_80073CB0(u8 alpha) {
    if (alpha != 0) {
        {
            Gfx *g = D_800E9BA0;

            D_800E9BA0 = g + 1;
            g[0].w0 = 0xE7000000;
            g[0].w1 = 0;
            D_800E9BA0 = g + 2;
            g[1].w0 = 0xDE000000;
            g[1].w1 = (u32)D_801869C8;
            D_800E9BA0 = g + 3;
            g[2].w0 = 0xD9000000;
            g[2].w1 = 0;
            D_800E9BA0 = g + 4;
            g[3].w0 = 0xE7000000;
            g[3].w1 = 0;
            D_800E9BA0 = g + 5;
            g[4].w0 = 0xE7000000;
            g[4].w1 = 0;
            D_800E9BA0 = g + 6;
            g[5].w0 = 0xE3000A01;
            g[5].w1 = 0;
            D_800E9BA0 = g + 7;
            g[6].w0 = 0xE7000000;
            g[6].w1 = 0;
            D_800E9BA0 = g + 8;
            g[7].w0 = 0xFCFFFFFF;
            g[7].w1 = 0xFFFDF6FB;
            D_800E9BA0 = g + 9;
            g[8].w0 = 0xE200001C;
            g[8].w1 = 0x504340;
            D_800E9BA0 = g + 10;
            g[9].w0 = 0xFA000000;
            g[9].w1 = alpha;
        }
        if (!func_8016CD30()) {
            Gfx *g = D_800E9BA0;

            D_800E9BA0 = g + 1;
            g[0].w0 = 0xE7000000;
            g[0].w1 = 0;
            D_800E9BA0 = g + 2;
            g[1].w0 = 0xE45003C0;
            g[1].w1 = 0;
            D_800E9BA0 = g + 3;
            g[2].w0 = 0xE1000000;
            g[2].w1 = 0;
            D_800E9BA0 = g + 4;
            g[3].w0 = 0xF1000000;
            g[3].w1 = 0;
            D_800E9BA0 = g + 5;
            g[4].w0 = 0xE7000000;
            g[4].w1 = 0;
        } else {
            Gfx *g = D_800E9BA0;

            D_800E9BA0 = g + 1;
            g[0].w0 = 0xDE000000;
            g[0].w1 = (u32)D_80186358;
            D_800E9BA0 = g + 2;
            g[1].w0 = 0xDE000000;
            g[1].w1 = (u32)D_80186610;
        }
        {
            Gfx *g = D_800E9BA0;

            D_800E9BA0 = g + 1;
            g[0].w0 = 0xE7000000;
            g[0].w1 = 0;
        }
    }
}

void func_80073ED8(void) {
    if (D_800A81F4 == 0) {
        D_800EB0DC = 0;
        D_800EB12C = 0;
        D_800EB17C = 0;
        D_800EB1CC = 0;
        D_800EB21C = 0;
        D_800EB26C = 0;
        D_800EB2BC = 0;
        func_80081908(3, 12);
        D_800A81F4 = 12;
        D_800A81F8 = D_800C4BCC;
    }
}

s32 func_80073F58(void) {
    u32 start = D_800A81F8;
    u32 end = start + 60;

    if (D_800A81F4 == 0) {
        return 0;
    }
    if (start < end) {
        if (D_800C4BCC >= end || D_800C4BCC < start) {
            D_800A81F4 = 0;
        }
    } else if (D_800C4BCC > end && D_800C4BCC < start) {
        D_800A81F4 = 0;
    }
    return D_800A81F4;
}

void func_80073FD4(void) {
    u32 mask = osSetIntMask(1);
    s32 i;

    for (i = 0; i < 7; i++) {
        D_800A8218[i][11] = 0;
        D_800A8218[i][12] = 0;
        D_800A8218[i][13] = 0;
        D_800A8218[i][14] = 0;
        D_800A8218[i][15] = 0;
        D_800A8218[i][16] = 0;
        D_800A8218[i][19] = 0;
    }
    osSetIntMask(mask);
}

void func_80074050(u8 *a) {
    D_800AEFB0 = a;
    D_800AEFB4 = 0;
    D_800AEFB8 = 0;
    D_800AEFBC = 8;
    D_800AEFC0 = 0;
}

u32 func_80074080(void) {
    if (--D_800AEFB8 >= 0) {
        return (D_800AEFC0 >> D_800AEFB8) & 1;
    }
    D_800AEFB8 = 7;
    D_800AEFC0 = D_800AEFB0[D_800AEFB4++];
    return D_800AEFC0 >> 7;
}

u32 func_800740F0(s32 n) {
    u32 r = 0;

    while (D_800AEFB8 < n) {
        n -= D_800AEFB8;
        r |= (D_800AEFC0 & ((1 << D_800AEFB8) - 1)) << n;
        D_800AEFC0 = D_800AEFB0[D_800AEFB4++];
        D_800AEFB8 = 8;
    }
    D_800AEFB8 -= n;
    return r | ((D_800AEFC0 >> D_800AEFB8) & ((1 << n) - 1));
}

void func_800741A8(s32 bit) {
    s32 n = --D_800AEFBC;

    if (bit) {
        D_800AEFC0 |= 1 << n;
    }
    if (n == 0) {
        D_800AEFB0[D_800AEFB4++] = D_800AEFC0;
        D_800AEFC0 = 0;
        D_800AEFBC = 8;
    }
}

void func_8007422C(s32 n, u32 val) {
    while (n >= D_800AEFBC) {
        n -= D_800AEFBC;
        D_800AEFC0 |= (val >> n) & ((1 << D_800AEFBC) - 1);
        D_800AEFB0[D_800AEFB4++] = D_800AEFC0;
        D_800AEFC0 = 0;
        D_800AEFBC = 8;
    }
    D_800AEFBC -= n;
    D_800AEFC0 |= (val & ((1 << n) - 1)) << D_800AEFBC;
}

static inline void BitInitInline(u8 *a) {
    D_800AEFB0 = a;
    D_800AEFB4 = 0;
    D_800AEFB8 = 0;
    D_800AEFBC = 8;
    D_800AEFC0 = 0;
}

static inline u32 BitReadInline(s32 n) {
    u32 r = 0;

    while (D_800AEFB8 < n) {
        n -= D_800AEFB8;
        r |= (D_800AEFC0 & ((1 << D_800AEFB8) - 1)) << n;
        D_800AEFC0 = D_800AEFB0[D_800AEFB4++];
        D_800AEFB8 = 8;
    }
    D_800AEFB8 -= n;
    return r | ((D_800AEFC0 >> D_800AEFB8) & ((1 << n) - 1));
}

static inline void BitWriteInline(s32 n, u32 val) {
    while (n >= D_800AEFBC) {
        n -= D_800AEFBC;
        D_800AEFC0 |= (val >> n) & ((1 << D_800AEFBC) - 1);
        D_800AEFB0[D_800AEFB4++] = D_800AEFC0;
        D_800AEFC0 = 0;
        D_800AEFBC = 8;
    }
    D_800AEFBC -= n;
    D_800AEFC0 |= (val & ((1 << n) - 1)) << D_800AEFBC;
}

/* Unpacks bit-packed records from buf into the tables listed in d (save data). */
void func_800742F4(u8 *buf, SaveDesc *d) {
    u8 *base = d->base;
    u32 i;
    u8 *f;
    u8 *p;
    s32 n;
    u32 v;
    s32 j = 0;

    BitInitInline(buf);
    if (base != NULL) {
        do {
            for (i = 0; i < d[j].count; i++) {
                f = d[j].fields;
                n = f[1];
                while (n != 0) {
                    p = base + f[0];
                    v = BitReadInline(f[2]);
                    if (n & 0x80) {
                        n &= 0x7F;
                        v |= -(1 << f[2]);
                    }
                    while (--n >= 0) {
                        *p++ = v >> (n * 8);
                    }
                    f += 3;
                    n = f[1];
                }
                base += d[j].stride;
            }
            j++;
            base = d[j].base;
        } while (base != NULL);
    }
}

void func_80074494(u8 *buf, SaveDesc *d) {
    u8 *base = d->base;
    u32 i;
    u8 *f;
    u8 *p;
    s32 n;
    u32 v;
    s32 j = 0;

    BitInitInline(buf);
    if (base != NULL) {
        do {
            for (i = 0; i < d[j].count; i++) {
                f = d[j].fields;
                n = f[1] & 0x7F;
                while (n != 0) {
                    p = base + f[0];
                    v = 0;
                    for (; n > 0; n--) {
                        v = (v << 8) | *p++;
                    }
                    BitWriteInline(f[2], v);
                    f += 3;
                    n = f[1] & 0x7F;
                }
                base += d[j].stride;
            }
            j++;
            base = d[j].base;
        } while (base != NULL);
    }
    BitWriteInline(7, 0);
}
