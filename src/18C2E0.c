#include "common.h"

/* 18C2E0 */

extern void *D_8021B588_ovl_188B60;

void *func_8017BFB0(s32 a, s32 b, void *c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i, s32 j, s32 k);
void func_80219584_ovl_188B60(void);
extern s32 D_8021B5A4_ovl_188B60;
extern s32 D_8021B5B0_ovl_188B60;
extern void *D_8021B58C_ovl_188B60;
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/18C2E0", func_80218700_ovl_188B60);

INCLUDE_ASM("asm/nonmatchings/18C2E0", func_802188EC_ovl_188B60);

INCLUDE_ASM("asm/nonmatchings/18C2E0", func_80218F74_ovl_188B60);

void func_8021948C_ovl_188B60(void) {
    void **p = &D_8021B588_ovl_188B60;

    if (*p == NULL) {
        *p = func_8017BFB0(0, 0, func_80219584_ovl_188B60, 0x18, 0x18, 0x1C, 0x1C, 0x18, 0x18, 0x91, 0x4A);
    }
}

void func_80219500_ovl_188B60(void) {
    if (D_8021B5A4_ovl_188B60 == -1) {
        D_8021B5A4_ovl_188B60 = D_8021B5B0_ovl_188B60;
        D_8021B58C_ovl_188B60 = func_8017BFB0(0, 0, func_80219584_ovl_188B60, 0x124, 0x18, 0x128, 0x1C, 0xAF, 0x18, 0x128, 0x4A);
    }
}

INCLUDE_ASM("asm/nonmatchings/18C2E0", func_80219584_ovl_188B60);

INCLUDE_ASM("asm/nonmatchings/18C2E0", func_80219F84_ovl_188B60);

INCLUDE_ASM("asm/nonmatchings/18C2E0", func_8021A0A4_ovl_188B60);

INCLUDE_ASM("asm/nonmatchings/18C2E0", func_8021AA3C_ovl_188B60);

INCLUDE_ASM("asm/nonmatchings/18C2E0", func_8021AFD8_ovl_188B60);
