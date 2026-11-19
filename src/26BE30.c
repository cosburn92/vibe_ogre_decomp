#include "common.h"

/* 26BE30 */

extern s16 D_80221038_ovl_25EE90[];
extern s32 D_8022103C_ovl_25EE90;

void bzero(void *p, s32 n);
void func_8020D778_ovl_25EE90(void *fn);
void func_80217280_ovl_25EE90(void);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/26BE30", func_80217280_ovl_25EE90);

void func_802173C4_ovl_25EE90(s32 a) {
    bzero(D_80221038_ovl_25EE90, 0x18);
    D_8022103C_ovl_25EE90 = a;
    func_8020D778_ovl_25EE90(func_80217280_ovl_25EE90);
}

void func_80217408_ovl_25EE90(s32 a) {
    s16 *p = D_80221038_ovl_25EE90;

    bzero(p, 0x18);
    p[0] = 2;
    D_8022103C_ovl_25EE90 = a;
    func_8020D778_ovl_25EE90(func_80217280_ovl_25EE90);
}

void func_80217460_ovl_25EE90(s32 a) {
    s16 *p = D_80221038_ovl_25EE90;

    bzero(p, 0x18);
    p[0] = 10;
    D_8022103C_ovl_25EE90 = a;
    func_8020D778_ovl_25EE90(func_80217280_ovl_25EE90);
}
