#include "common.h"

extern u8 *D_8019A660_ovl_066E10;

void nuGfxTaskAllEndWait(void);
s32 func_80199D10_ovl_066E10(void);

INCLUDE_ASM("asm/nonmatchings/680F0", func_80198E50_ovl_066E10);

INCLUDE_ASM("asm/nonmatchings/680F0", func_80198FC8_ovl_066E10);

INCLUDE_ASM("asm/nonmatchings/680F0", func_80199110_ovl_066E10);

void func_8019951C_ovl_066E10(void) {
    if (D_8019A660_ovl_066E10[0x7E] == 1) {
        D_8019A660_ovl_066E10[0x7E]++;
    }
    if (D_8019A660_ovl_066E10[0x7E] == 4) {
        D_8019A660_ovl_066E10[0x7E]++;
    }
}

INCLUDE_ASM("asm/nonmatchings/680F0", func_80199568_ovl_066E10);

INCLUDE_ASM("asm/nonmatchings/680F0", func_8019974C_ovl_066E10);

INCLUDE_ASM("asm/nonmatchings/680F0", func_8019994C_ovl_066E10);

INCLUDE_ASM("asm/nonmatchings/680F0", func_801999E8_ovl_066E10);

INCLUDE_ASM("asm/nonmatchings/680F0", func_80199D10_ovl_066E10);

INCLUDE_ASM("asm/nonmatchings/680F0", func_8019A088_ovl_066E10);

void func_8019A1DC_ovl_066E10(void) {
    do {
        nuGfxTaskAllEndWait();
    } while (!func_80199D10_ovl_066E10());
}
