#include "common.h"

extern u8 *D_8019A660_ovl_066E10;

void nuGfxTaskAllEndWait(void);
s32 func_80199D10_ovl_066E10(void);

extern u8 D_800E7A0C;
extern void *D_800C4BB8;
extern void *D_800A8204[3];
/* --- end decls --- */

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

/* Reports which frame buffer pair is current (o[0], o[1]) */
void func_8019994C_ovl_066E10(u8 *o) {
    nuGfxTaskAllEndWait();
    o[0] = 0;
    o[1] = 1;
    if (D_800E7A0C == 1) {
        if (D_800C4BB8 == D_800A8204[0]) {
            o[0] = 1;
            o[1] = 2;
        } else if (D_800C4BB8 == D_800A8204[1]) {
            o[0] = 0;
            o[1] = 2;
        } else if (D_800C4BB8 == D_800A8204[2]) {
            o[0] = 0;
            o[1] = 1;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/680F0", func_801999E8_ovl_066E10);

INCLUDE_ASM("asm/nonmatchings/680F0", func_80199D10_ovl_066E10);

INCLUDE_ASM("asm/nonmatchings/680F0", func_8019A088_ovl_066E10);

void func_8019A1DC_ovl_066E10(void) {
    do {
        nuGfxTaskAllEndWait();
    } while (!func_80199D10_ovl_066E10());
}
