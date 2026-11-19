#include "common.h"

/* 112C00 */

extern u8 *D_801AB850;
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/112C00", func_801BE4C0_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/112C00", func_801BECD0_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/112C00", func_801BEF54_ovl_101CE0);

/* Steps the 0..4 open counter at +0x1C (clears +0x20 when it reaches 4) */
void func_801BF2F0_ovl_101CE0(void) {
    u8 *s = D_801AB850;

    if (s[0x18] & 1) {
        if (*(s32 *)(s + 0x1C) < 4) {
            if (++*(s32 *)(s + 0x1C) == 4) {
                s[0x20] = 0;
            }
        }
    } else if (*(s32 *)(s + 0x1C) > 0) {
        (*(s32 *)(s + 0x1C))--;
    }
}
