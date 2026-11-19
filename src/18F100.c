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

INCLUDE_ASM("asm/nonmatchings/18F100", func_80214F80_ovl_18F100);

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
