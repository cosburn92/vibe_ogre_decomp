#include "common.h"

/* 261C90 */

typedef struct {
    /* 0x00 */ u16 next;
    /* 0x02 */ u8 unk02[2];
    /* 0x04 */ u8 unk04[4];
    /* 0x08 */ s32 w8;
    /* 0x0C */ s32 wC;
    /* 0x10 */ s32 w10;
    /* 0x14 */ s32 w14;
    /* 0x18 */ u8 b18;
    /* 0x19 */ u8 unk19[0x67];
} Block26; /* size 0x80 */

extern u16 D_80220D50_ovl_25EE90;
extern u32 D_80220D54_ovl_25EE90;
extern Block26 *D_80220D58_ovl_25EE90;

void *HMalloc(s32 size);
void *HFree(void *p);
void func_801ADB00(void *p);
/* --- end decls --- */

/* Builds a free list of 0x80-byte blocks */
void func_8020D0E0_ovl_25EE90(void) {
    Block26 *b;
    u32 i;
    u32 n;

    D_80220D54_ovl_25EE90 = 0x100;
    b = HMalloc(0x8000);
    D_80220D58_ovl_25EE90 = b;
    D_80220D50_ovl_25EE90 = 0;
    n = D_80220D54_ovl_25EE90 - 1;
    for (i = 0; i < n; i++, b++) {
        b->next = i + 1;
    }
    b->next = 0xFFFF;
}

void func_8020D150_ovl_25EE90(void) {
    HFree(D_80220D58_ovl_25EE90);
}

/* Takes a block (hangs when empty); returns its payload */
void *func_8020D174_ovl_25EE90(void) {
    Block26 *b;

    if (D_80220D50_ovl_25EE90 != 0xFFFF) {
        b = &D_80220D58_ovl_25EE90[D_80220D50_ovl_25EE90];
        D_80220D50_ovl_25EE90 = b->next;
    } else {
        for (;;) {
        }
    }
    b->b18 = 1;
    b->w10 = 0;
    b->wC = 0;
    b->w8 = 0;
    b->w14 = 0;
    return b->unk04;
}

inline void func_8020D1CC_ovl_25EE90(void *p) {
    Block26 *b = (Block26 *)((u8 *)p - 4);

    b->next = D_80220D50_ovl_25EE90;
    D_80220D50_ovl_25EE90 = b - D_80220D58_ovl_25EE90;
}

INCLUDE_ASM("asm/nonmatchings/261C90", func_8020D1F8_ovl_25EE90);

void func_8020D280_ovl_25EE90(void *p) {
    if (p != NULL) {
        func_801ADB00(p);
        func_8020D1CC_ovl_25EE90(p);
    }
}
