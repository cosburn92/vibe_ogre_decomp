#include "common.h"

/* 134830 */

extern s32 D_801ED4A4_ovl_101CE0[];
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/134830", func_801E00F0_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/134830", func_801E027C_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/134830", func_801E0594_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/134830", func_801E0868_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/134830", func_801E09DC_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/134830", func_801E0DBC_ovl_101CE0);

s32 func_801E0F30_ovl_101CE0(s32 a) {
    s32 *p = D_801ED4A4_ovl_101CE0;
    s32 i = 0;

    while (*p != a) {
        p += 3;
        i += 3;
    }
    return i;
}
