#include "common.h"

/* 26F1E0 */

typedef struct {
    u8 unk00[0x3C];
    s32 w3C;
    s32 w40;
    s32 w44;
    s32 w48;
} Task26F;

extern s32 D_80220F68_ovl_25EE90;
extern s32 D_80220F6C_ovl_25EE90;

Task26F *func_8020DF00_ovl_25EE90(void *fn);
void func_8021A630_ovl_25EE90(void);
void func_8021B500_ovl_25EE90(void);
void func_8021D168_ovl_25EE90(void);
void func_8021C62C_ovl_25EE90(void);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021A630_ovl_25EE90);

void func_8021A998_ovl_25EE90(s32 a, s32 b) {
    D_80220F68_ovl_25EE90 = a;
    D_80220F6C_ovl_25EE90 = b;
    func_8020DF00_ovl_25EE90(func_8021A630_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021A9C8_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021AC40_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021ADE0_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021B040_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021B500_ovl_25EE90);

void func_8021B6C4_ovl_25EE90(s32 a) {
    D_80220F68_ovl_25EE90 = a;
    func_8020DF00_ovl_25EE90(func_8021B500_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021B6F0_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021B8D8_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021BA3C_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021C044_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021C360_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021C440_ovl_25EE90);

void func_8021C4C0_ovl_25EE90(s32 a) {
    D_80220F68_ovl_25EE90 = a;
    func_8020DF00_ovl_25EE90(func_8021D168_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021C4EC_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021C62C_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021CE60_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021D168_ovl_25EE90);

void func_8021D20C_ovl_25EE90(s16 a, s32 b, s32 c, s32 d) {
    Task26F *t = func_8020DF00_ovl_25EE90(func_8021C62C_ovl_25EE90);

    t->w3C = b;
    t->w40 = c;
    t->w44 = d;
    t->w48 = a;
}
