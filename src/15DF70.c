#include "common.h"

/* 15DF70 */

extern void *D_80213EE8_ovl_14EBE0;

void *HFree(void *p);
/* --- end decls --- */

void func_8020CE00_ovl_14EBE0(void) {
    D_80213EE8_ovl_14EBE0 = NULL;
}

INCLUDE_ASM("asm/nonmatchings/15DF70", func_8020CE0C_ovl_14EBE0);

void func_8020CE8C_ovl_14EBE0(void) {
    if (D_80213EE8_ovl_14EBE0 != NULL) {
        HFree(D_80213EE8_ovl_14EBE0);
    }
    D_80213EE8_ovl_14EBE0 = NULL;
}

INCLUDE_ASM("asm/nonmatchings/15DF70", func_8020CEBC_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/15DF70", func_8020D210_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/15DF70", func_8020D328_ovl_14EBE0);
