#include "common.h"

/* 420D0 */

void osSetTime(u64 t);
void bzero(void *p, s32 n);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/420D0", func_8016C1D0_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/420D0", func_8016C268_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/420D0", func_8016C3C4_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/420D0", func_8016C528_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/420D0", DateAdvanceDay);

INCLUDE_ASM("asm/nonmatchings/420D0", func_8016C70C_ovl_040E80);

void func_8016C814_ovl_040E80(void) {
}

INCLUDE_ASM("asm/nonmatchings/420D0", func_8016C81C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/420D0", NewGameInit);

INCLUDE_ASM("asm/nonmatchings/420D0", func_8016C9FC_ovl_040E80);

void func_8016CB08_ovl_040E80(void *p) {
    osSetTime(0);
    bzero(p, 4);
}

INCLUDE_ASM("asm/nonmatchings/420D0", PlayTimeUpdate);

INCLUDE_ASM("asm/nonmatchings/420D0", func_8016CC2C_ovl_040E80);
