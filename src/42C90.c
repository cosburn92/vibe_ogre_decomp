#include "common.h"

/* 42C90 */

typedef struct {
    u32 flag : 1;
    u32 mode : 4;
    u32 rest : 27;
} Bits42;

extern u8 D_80187030_ovl_040E80;
extern u8 D_80187031_ovl_040E80;

void func_8016CDF4_ovl_040E80(Bits42 *p);
/* --- end decls --- */

void func_8016CD90_ovl_040E80(Bits42 *p) {
    p->flag = D_80187030_ovl_040E80 = 0;
    p->mode = D_80187031_ovl_040E80 = 0;
}

void func_8016CDCC_ovl_040E80(Bits42 *p) {
    D_80187030_ovl_040E80 = p->flag;
    D_80187031_ovl_040E80 = p->mode;
}

void func_8016CDF4_ovl_040E80(Bits42 *p) {
    p->flag = D_80187030_ovl_040E80;
    p->mode = D_80187031_ovl_040E80;
}

INCLUDE_ASM("asm/nonmatchings/42C90", func_8016CE40_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/42C90", func_8016CEC4_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/42C90", func_8016CF64_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/42C90", func_8016D068_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/42C90", func_8016D100_ovl_040E80);
