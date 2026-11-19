#include "common.h"

/* 2A7060 */

extern u8 D_80239140_ovl_29A4C0[];
extern u8 D_8023914C_ovl_29A4C0[];
void func_8020DFB8(void);
void func_8020DC80(u16 state);
void func_8020E0B4(s32 a, s32 b);
void func_8020B538(s32 a, u8 *s);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/2A7060", func_80237830_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/2A7060", func_80237B84_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/2A7060", func_80237C90_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/2A7060", func_80237E4C_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/2A7060", func_80238004_ovl_29A4C0);

s32 func_8023823C_ovl_29A4C0(u16 msg) {
    switch (msg) {
        case 0x101:
            func_8020DFB8();
            break;
        case 0x100:
            func_8020DC80(0x1010);
            break;
        case 0x1010:
            func_8020E0B4(10, 0x1100);
            break;
        case 0x1100:
            func_8020B538(4, D_80239140_ovl_29A4C0);
            func_8020E0B4(10, 0x1200);
            break;
        case 0x1200:
            func_8020B538(4, D_8023914C_ovl_29A4C0);
            func_8020E0B4(10, 0x101);
            break;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/2A7060", func_8023830C_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/2A7060", func_8023841C_ovl_29A4C0);
