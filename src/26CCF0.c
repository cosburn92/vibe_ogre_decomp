#include "common.h"

/* 26CCF0 */

typedef struct {
    u8 unk00[0x48];
    s32 w48;
    s32 w4C;
    s32 w50;
} Task26C;

extern s32 D_80220F68_ovl_25EE90;

Task26C *func_8020DF00_ovl_25EE90(void *fn);
void func_80218AC0_ovl_25EE90(void);
void func_802182C4_ovl_25EE90(void);
/* --- end decls --- */

void func_80218140_ovl_25EE90(s32 a) {
    D_80220F68_ovl_25EE90 = a;
    func_8020DF00_ovl_25EE90(func_80218AC0_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/26CCF0", func_8021816C_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26CCF0", func_802182C4_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26CCF0", func_802187A4_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26CCF0", func_80218AC0_ovl_25EE90);

void func_80218B64_ovl_25EE90(s16 a, s32 b, s32 c) {
    Task26C *t = func_8020DF00_ovl_25EE90(func_802182C4_ovl_25EE90);

    t->w48 = b;
    t->w4C = c;
    t->w50 = a;
}
