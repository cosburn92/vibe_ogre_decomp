#include "common.h"

/* 262CC0 */

typedef struct {
    /* 0x00 */ u16 next;
    /* 0x02 */ u8 unk02[2];
    /* 0x04 */ s32 w4;
    /* 0x08 */ s32 w8;
    /* 0x0C */ s32 wC;
    /* 0x10 */ s16 h10;
    /* 0x12 */ u8 unk12[0x66];
} Blk78; /* size 0x78 */

extern u16 D_80220DA0_ovl_25EE90;
extern Blk78 *D_80220DA8_ovl_25EE90;
extern void *D_80220DAC_ovl_25EE90;

void *HFree(void *p);
void *HMalloc(s32 size);
extern s32 D_80220DA4_ovl_25EE90;
void func_801B55C4(void);
void func_8020E224_ovl_25EE90(s32 a);
/* --- end decls --- */

/* Pool of 256 blocks chained through `next`, plus a pointer table */
void func_8020E110_ovl_25EE90(void) {
    Blk78 *p;
    s32 i;

    D_80220DA4_ovl_25EE90 = 0x100;
    p = HMalloc(0x7800);
    D_80220DA8_ovl_25EE90 = p;
    for (i = 0; i < D_80220DA4_ovl_25EE90; i++) {
        p[i].w4 = 0;
        p[i].wC = 0;
    }
    D_80220DAC_ovl_25EE90 = HMalloc(D_80220DA4_ovl_25EE90 * 4);
    D_80220DA0_ovl_25EE90 = 0;
    for (i = 0; i < D_80220DA4_ovl_25EE90 - 1; i++) {
        D_80220DA8_ovl_25EE90[i].next = i + 1;
    }
    D_80220DA8_ovl_25EE90[i].next = 0xFFFF;
}

void func_8020E1F4_ovl_25EE90(void) {
    HFree(D_80220DA8_ovl_25EE90);
    HFree(D_80220DAC_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/262CC0", func_8020E224_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/262CC0", func_8020E3A0_ovl_25EE90);

void func_8020E4A0_ovl_25EE90(void) {
    func_801B55C4();
    func_8020E224_ovl_25EE90(0);
}

/* Takes a block from the free list (hangs when empty) */
inline Blk78 *func_8020E4C4_ovl_25EE90(void) {
    Blk78 *b;

    if (D_80220DA0_ovl_25EE90 != 0xFFFF) {
        b = &D_80220DA8_ovl_25EE90[D_80220DA0_ovl_25EE90];
        D_80220DA0_ovl_25EE90 = b->next;
    } else {
        for (;;) {
        }
    }
    b->h10 = 2;
    b->wC = 0;
    b->w8 = 0;
    return b;
}

void func_8020E51C_ovl_25EE90(Blk78 *b) {
    if (b != NULL) {
        b->w4 = 0;
        b->next = D_80220DA0_ovl_25EE90;
        D_80220DA0_ovl_25EE90 = b - D_80220DA8_ovl_25EE90;
    }
}

Blk78 *func_8020E570_ovl_25EE90(s32 a, s16 c) {
    Blk78 *b;

    if (D_80220DA0_ovl_25EE90 != 0xFFFF) {
        b = &D_80220DA8_ovl_25EE90[D_80220DA0_ovl_25EE90];
        D_80220DA0_ovl_25EE90 = b->next;
    } else {
        for (;;) {
        }
    }
    b->wC = 0;
    b->h10 = 2;
    b->w8 = 0;
    if (b != NULL) {
        b->w4 = a;
        b->wC = 1;
        b->h10 = c;
    }
    return b;
}
