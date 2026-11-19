#include "common.h"

/* 18F100 */

extern void *D_8021B170_ovl_18F100;
extern s8 D_8021B188_ovl_18F100[];
extern u8 D_8021B299_ovl_18F100[];
extern s32 D_801F0B9C;

void *func_8017BFB0(s32 a, s32 b, void *c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i, s32 j, s32 k);
void func_802159B0_ovl_18F100(void);
extern void *D_8021B174_ovl_18F100;
extern s32 D_8021B2AC_ovl_18F100;
extern s32 D_8021B2A4_ovl_18F100;
extern u8 D_80210219;
void func_8017C384(void *w);
extern void *D_8021B174_ovl_18F100;
extern s32 D_8021B2AC_ovl_18F100;
extern s32 D_8021B2A4_ovl_18F100;
extern u8 D_80210219;
void func_8017C384(void *w);
extern s32 D_8021B2B4_ovl_18F100;
/* --- end decls --- */

#ifdef NON_MATCHING
/* m2c draft, 60 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern void *D_800E9BA0;

void func_80214F80_ovl_18F100(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s16 temp_a1;
    s32 temp_t2;
    s32 temp_t3;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_t3;
    s32 var_v0;
    void *temp_t0;
    void *temp_t1;
    void *temp_v1_2;

    temp_t0 = D_800E9BA0;
    D_800E9BA0 = temp_t0 + 8;
    temp_t1 = temp_t0 + 0x10;
    FIELD(temp_t0, s32, 0) = 0xE7000000;
    FIELD(temp_t0, s32, 8) = (s32) ((((arg2 * 4) & ((s32) ~(s16) (arg2 * 4) >> 0x1F) & 0xFFC) << 0xC) | (((arg3 * 4) & ((s32) ~(s16) (arg3 * 4) >> 0x1F) & 0xFFC) | 0xE4000000));
    temp_a1 = arg0 * 4;
    D_800E9BA0 = temp_t1;
    D_800E9BA0 = temp_t0 + 0x18;
    temp_t2 = arg5 << 5;
    temp_t3 = arg4 << 5;
    FIELD(temp_t0, s32, 4) = 0;
    FIELD(temp_t0, s32, 0xC) = (s32) ((((arg0 * 4) & ((s32) ~temp_a1 >> 0x1F) & 0xFFC) << 0xC) | ((arg1 * 4) & ((s32) ~(s16) (arg1 * 4) >> 0x1F) & 0xFFC));
    FIELD(temp_t0, s32, 0x10) = 0xE1000000;
    if (temp_a1 < 0) {
        temp_v1 = temp_a1 * 8;
        var_t3 = (temp_t3 - (temp_v1 & -(temp_v1 < 1))) << 0x10;
    } else {
        var_t3 = temp_t3 << 0x10;
    }
    if (!(arg1 & 0x20000000)) {
        var_v0 = temp_t2 & 0xFFFF;
    } else {
        temp_v0 = (s32) (arg1 << 0x12) >> 0xD;
        var_v0 = (temp_t2 - (temp_v0 & -(temp_v0 < 1))) & 0xFFFF;
    }
    FIELD(temp_t1, s32, 4) = (s32) (var_t3 | var_v0);
    temp_v1_2 = D_800E9BA0;
    D_800E9BA0 = temp_v1_2 + 8;
    FIELD(temp_v1_2, s32, 0) = 0xF1000000;
    D_800E9BA0 = temp_v1_2 + 0x10;
    FIELD(temp_v1_2, s32, 4) = 0x04000400;
    FIELD(temp_v1_2, s32, 8) = 0xE7000000;
    FIELD(temp_v1_2, s32, 0xC) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/18F100", func_80214F80_ovl_18F100);
#endif

INCLUDE_ASM("asm/nonmatchings/18F100", func_802150FC_ovl_18F100);

/* Closes this screen's windows */
/* Closes this screen's windows */
void func_80215298_ovl_18F100(void) {
    s32 pad[4];

    if (D_8021B170_ovl_18F100 != NULL) {
        func_8017C384(D_8021B170_ovl_18F100);
    }
    if (D_8021B2AC_ovl_18F100 != -1) {
        func_8017C384(D_8021B174_ovl_18F100);
    }
    D_8021B2A4_ovl_18F100 = 0;
    D_80210219 = 0x11;
}

INCLUDE_ASM("asm/nonmatchings/18F100", func_802152F4_ovl_18F100);

INCLUDE_ASM("asm/nonmatchings/18F100", func_80215438_ovl_18F100);

void func_802158B8_ovl_18F100(void) {
    if (D_8021B170_ovl_18F100 == NULL) {
        D_8021B170_ovl_18F100 =
            func_8017BFB0(0, 0, func_802159B0_ovl_18F100, 0x18, 0x14, 0x20, 0x1C, 0x18, 0x14, 0x9A, 0x40);
    }
}

void func_8021592C_ovl_18F100(void) {
    if (D_8021B2AC_ovl_18F100 == -1) {
        D_8021B2AC_ovl_18F100 = D_8021B2B4_ovl_18F100;
        D_8021B174_ovl_18F100 = func_8017BFB0(0, 0, func_802159B0_ovl_18F100, 0x120, 0x14, 0x128, 0x1C, 0xA6, 0x14, 0x128, 0x40);
    }
}

INCLUDE_ASM("asm/nonmatchings/18F100", func_802159B0_ovl_18F100);

/* Whether any id in list i (except the current one) has a level of at least lvl */
#ifdef NON_MATCHING
/* Loop layout differs. */
s32 func_80216FF4_ovl_18F100(s32 i, s32 lvl) {
    s8 *p = &D_8021B188_ovl_18F100[i * 9];

    if (*p == -1) {
        return 0;
    }
    for (; *p != -1; p++) {
        if (*p == D_801F0B9C) {
            continue;
        }
        if (D_8021B299_ovl_18F100[*p] >= lvl) {
            return 1;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/18F100", func_80216FF4_ovl_18F100);
#endif

INCLUDE_ASM("asm/nonmatchings/18F100", func_80217068_ovl_18F100);
