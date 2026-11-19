#include "common.h"

/* ovl_17F9C0 */

extern u8 D_80214A68;
extern s32 D_80214EA4;
extern s32 D_80214EA8;
extern u8 D_8021E120_ovl_17F9C0;

s32 func_8017BFB0(s32 a, s32 b, void *func, s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3);
void func_80215094_ovl_17F9C0(void);
void func_802166D8_ovl_17F9C0(void);
void func_80214FC4_ovl_17F9C0(void);

void func_80214F80_ovl_17F9C0(void) {
    if (D_80214A68 == 0) {
        func_80214FC4_ovl_17F9C0();
        D_8021E120_ovl_17F9C0 = 0;
        D_80214A68++;
    }
}

void func_80214FC4_ovl_17F9C0(void) {
    func_802166D8_ovl_17F9C0();
    D_80214EA4 = func_8017BFB0(0, 0, func_80215094_ovl_17F9C0, 0x120, 0xD0, 0x128, 0xD8, 0xBA, 0xD0, 0x128, 0xE2);
    D_80214EA8 = func_8017BFB0(0, 0, func_80215094_ovl_17F9C0, 0x18, 0xD0, 0x20, 0xD8, 0x18, 0xD0, 0x86, 0xE2);
}

INCLUDE_ASM("asm/nonmatchings/17F9C0", func_80215094_ovl_17F9C0);

INCLUDE_ASM("asm/nonmatchings/17F9C0", func_8021550C_ovl_17F9C0);

INCLUDE_ASM("asm/nonmatchings/17F9C0", func_802166D8_ovl_17F9C0);

/* Which quarter-turn sector an angle (in turns) falls in: 1..3, 0 otherwise */
s32 func_80216A14_ovl_17F9C0(f32 a) {
    if (0.208 <= a && a < 0.375) {
        return 1;
    }
    if (0.375 <= a && a < 0.625) {
        return 2;
    }
    if (0.625 <= a && a < 0.791) {
        return 3;
    }
    return 0;
}
