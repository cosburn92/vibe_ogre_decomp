#include "common.h"

/* 26D770 */

typedef struct {
    u8 unk00[0x3C];
    s32 w3C;
    s32 w40;
    s32 w44;
    s32 w48;
    s32 w4C;
    s32 w50;
} Task26D;

extern s32 D_80220F68_ovl_25EE90;

Task26D *func_8020DF00_ovl_25EE90(void *fn);
void func_80219140_ovl_25EE90(void);
void func_8021A57C_ovl_25EE90(void);
void func_80219A9C_ovl_25EE90(void);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/26D770", func_80218BC0_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26D770", func_80218D68_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26D770", func_80219140_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26D770", func_8021965C_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26D770", func_80219970_ovl_25EE90);

void func_80219A18_ovl_25EE90(s16 a, s32 b, s32 c) {
    Task26D *t = func_8020DF00_ovl_25EE90(func_80219140_ovl_25EE90);

    t->w48 = b;
    t->w4C = c;
    t->w50 = a;
}

void func_80219A70_ovl_25EE90(s32 a) {
    D_80220F68_ovl_25EE90 = a;
    func_8020DF00_ovl_25EE90(func_8021A57C_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/26D770", func_80219A9C_ovl_25EE90);

void func_8021A210_ovl_25EE90(s16 a, s32 b, s32 c) {
    Task26D *t = func_8020DF00_ovl_25EE90(func_80219A9C_ovl_25EE90);

    t->w3C = b;
    t->w40 = c;
    t->w44 = a;
}

INCLUDE_ASM("asm/nonmatchings/26D770", func_8021A268_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26D770", func_8021A57C_ovl_25EE90);
