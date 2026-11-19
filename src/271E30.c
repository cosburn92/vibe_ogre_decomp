#include "common.h"

/* 271E30 */

typedef struct {
    u8 unk00[0x30];
    s32 w30;
    s32 w34;
    s32 w38;
    s32 w3C;
} Task271;

extern s32 D_80220F68_ovl_25EE90;

Task271 *func_8020DF00_ovl_25EE90(void *fn);
void func_8021DACC_ovl_25EE90(void);
void func_8021D2AC_ovl_25EE90(void);
/* --- end decls --- */

void func_8021D280_ovl_25EE90(s32 a) {
    D_80220F68_ovl_25EE90 = a;
    func_8020DF00_ovl_25EE90(func_8021DACC_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/271E30", func_8021D2AC_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/271E30", func_8021D7C4_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/271E30", func_8021DACC_ovl_25EE90);

void func_8021DB6C_ovl_25EE90(s16 a, s32 b, s32 c, s32 d) {
    Task271 *t = func_8020DF00_ovl_25EE90(func_8021D2AC_ovl_25EE90);

    t->w30 = b;
    t->w34 = c;
    t->w38 = d;
    t->w3C = a;
}
