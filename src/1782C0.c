#include "common.h"

/* 1782C0 */

extern u8 D_80218D91_ovl_177ED0;

void func_80215AF4_ovl_177ED0(void);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/1782C0", func_80215370_ovl_177ED0);

void func_802154CC_ovl_177ED0(void) {
    if (D_80218D91_ovl_177ED0) {
        func_80215AF4_ovl_177ED0();
    }
}
