#include "common.h"

/* 83080 */

INCLUDE_ASM("asm/nonmatchings/83080", func_801A40F0_ovl_079730);

#ifdef NON_MATCHING
/* m2c draft, 47 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern s32 D_80193BF8;

void func_801A4568_ovl_079730(s32 arg0) {
    s32 *var_s0;
    s32 temp_s2;
    s32 temp_v1_2;
    s32 var_s1;
    u8 temp_v1;

    var_s1 = 1;
    temp_s2 = arg0 & 0xFFFF;
    var_s0 = &D_80193BF8;
    do {
        temp_v1 = FIELD(var_s0, u8, 0x11);
        temp_v1_2 = temp_v1 & 0xFF;
        if (((u32) (temp_v1 - 0x52) < 6U) && (temp_v1_2 == FIELD(var_s0, u8, 0x12))) {
            if (temp_s2 != 3) {
                if (temp_s2 != 4) {
                    var_s1 += 1;
                } else {
                    if (temp_v1_2 == 0x53) {
                        goto block_13;
                    }
                    goto block_14;
                }
            } else {
                switch (temp_v1_2) {                /* irregular */
                default:
                    var_s1 += 1;
                    break;
                case 0x57:
                    /* fallthrough */
                case 0x55:
                case 0x52:
block_13:
                    func_801A40F0_ovl_079730(var_s0);
                    goto block_14;
                }
            }
        } else {
block_14:
            var_s1 += 1;
        }
        var_s0 += 0x38;
    } while (var_s1 < 0x64);
}
#else
INCLUDE_ASM("asm/nonmatchings/83080", func_801A4568_ovl_079730);
#endif
