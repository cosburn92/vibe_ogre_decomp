#include "common.h"

/* 1DAAB0 */

extern u8 D_801BA6E1_ovl_1CE070;

void func_8019915C_ovl_1CE070(void);
void func_80199518_ovl_1CE070(void);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/1DAAB0", func_801A45B0_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1DAAB0", func_801A49CC_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1DAAB0", func_801A5190_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1DAAB0", func_801A5300_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1DAAB0", func_801A576C_ovl_1CE070);

void func_801A590C_ovl_1CE070(void) {
}

INCLUDE_ASM("asm/nonmatchings/1DAAB0", func_801A5914_ovl_1CE070);

void func_801A5A34_ovl_1CE070(void) {
    func_8019915C_ovl_1CE070();
    if (D_801BA6E1_ovl_1CE070) {
        func_80199518_ovl_1CE070();
    }
}
