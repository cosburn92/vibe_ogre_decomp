#include "common.h"

/* 213B10 */

extern u8 *D_801D0810;
extern u8 D_801E5AA0_ovl_213B10[];
/* --- end decls --- */

void func_801D0840_ovl_213B10(void) {
    D_801D0810 = D_801E5AA0_ovl_213B10;
}

u8 func_801D0854_ovl_213B10(u8 *p) {
    if (*(s32 *)(p + 0x48) == 0x101) {
        return p[0x33];
    }
    return p[0xA4];
}
