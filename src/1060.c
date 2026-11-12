#include "common.h"

typedef struct HeapNode {
    /* 0x00 */ u8 unk00[4];
    /* 0x04 */ u32 end;
    /* 0x08 */ struct HeapNode **parent;
    /* 0x0C */ struct HeapNode *left;
    /* 0x10 */ struct HeapNode *right;
    /* 0x14 */ u8 unk14[4];
    /* 0x18 */ u32 size;
} HeapNode;

typedef struct {
    /* 0x00 */ HeapNode *start;
    /* 0x04 */ u32 end;
    /* 0x08 */ HeapNode *root;
} Heap;

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

extern Heap gHeaps[];
extern s32 D_800C4818;
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
void osViSetMode(void *m);

extern u16 gHeapCount;
extern u16 gHeapAllocFlags;
extern s32 osTvType;
extern u8 D_800AEF9A;
extern u8 D_800A8210;
extern u8 D_800A8211;
extern u8 D_800A8212;
extern u8 D_800A8213;
extern void *D_800AEF9C;
extern s32 D_800C4B20;
extern s32 D_800AEFB0;
extern s32 D_800AEFB4;
extern s32 D_800AEFB8;
extern s32 D_800AEFBC;
extern s32 D_800AEFC0;
void *HMalloc(s32 size);
void *HFree(void *p);
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
    gHeaps[0].start->end = end;
    gHeaps[0].start->size = end - start - 0x20;
    gHeaps[0].root = NULL;
    func_800719E8(&h->root, h->start);
    D_800C4818 = 0;
    gHeapCount = 1;
    gHeapAllocFlags = 3;
    gHeaps[0].end = gHeaps[0].start->end;
}

INCLUDE_ASM("asm/nonmatchings/1060", AddHeap);

void func_80070F14(void) {
    gHeapCount = 1;
    gHeapAllocFlags = 3;
}

INCLUDE_ASM("asm/nonmatchings/1060", HMalloc);

INCLUDE_ASM("asm/nonmatchings/1060", func_800710DC);

void *HMallocBack(s32 size) {
    u16 saved = gHeapAllocFlags;
    void *p;

    gHeapAllocFlags = 1;
    p = HMalloc(size);
    gHeapAllocFlags = saved;
    return p;
}

INCLUDE_ASM("asm/nonmatchings/1060", HFree);

INCLUDE_ASM("asm/nonmatchings/1060", func_800713EC);

INCLUDE_ASM("asm/nonmatchings/1060", HIsAllocatedPointer);

s32 func_80071634(s32 *p) {
    return p[-3];
}

s32 func_8007163C(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/1060", func_80071644);

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
        func_800719E8(r->size < n->size ? &r->right : &r->left, n);
    }
}

HeapNode *func_80071A3C(HeapNode *n, u32 size) {
    HeapNode *best = NULL;

    while (n != NULL) {
        if (n->size < size) {
            n = n->right;
        } else {
            best = n;
            n = best->left;
        }
    }
    return best;
}

INCLUDE_ASM("asm/nonmatchings/1060", func_80071A74);

s32 HFindHeap(u32 p) {
    s32 i;

    for (i = 0; i < gHeapCount; i++) {
        if (p >= (u32)gHeaps[i].start && p < gHeaps[i].end) {
            return i;
        }
    }
    return i;
}

INCLUDE_ASM("asm/nonmatchings/1060", func_80071C04);

HeapNode *func_80071E74(HeapNode *n, u32 size) {
    if (n == NULL) {
        return NULL;
    }
    while (n->right != NULL) {
        n = n->right;
    }
    return n->size >= size ? n : NULL;
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

INCLUDE_ASM("asm/nonmatchings/1060", func_8007307C);

INCLUDE_ASM("asm/nonmatchings/1060", func_80073164);

INCLUDE_ASM("asm/nonmatchings/1060", func_8007328C);

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
    D_800A8210 = 0;
    D_800AEF9C = HFree(D_800AEF9C);
    D_800C4B20 = 0;
}

INCLUDE_ASM("asm/nonmatchings/1060", func_800733F8);

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

INCLUDE_ASM("asm/nonmatchings/1060", func_8007382C);

INCLUDE_ASM("asm/nonmatchings/1060", func_80073AE4);

INCLUDE_ASM("asm/nonmatchings/1060", func_80073BD0);

INCLUDE_ASM("asm/nonmatchings/1060", func_80073C48);

INCLUDE_ASM("asm/nonmatchings/1060", func_80073CB0);

INCLUDE_ASM("asm/nonmatchings/1060", func_80073ED8);

INCLUDE_ASM("asm/nonmatchings/1060", func_80073F58);

INCLUDE_ASM("asm/nonmatchings/1060", func_80073FD4);

void func_80074050(s32 a) {
    D_800AEFB0 = a;
    D_800AEFB4 = 0;
    D_800AEFB8 = 0;
    D_800AEFBC = 8;
    D_800AEFC0 = 0;
}

INCLUDE_ASM("asm/nonmatchings/1060", func_80074080);

INCLUDE_ASM("asm/nonmatchings/1060", func_800740F0);

INCLUDE_ASM("asm/nonmatchings/1060", func_800741A8);

INCLUDE_ASM("asm/nonmatchings/1060", func_8007422C);

INCLUDE_ASM("asm/nonmatchings/1060", func_800742F4);

INCLUDE_ASM("asm/nonmatchings/1060", func_80074494);
