#include "common.h"

/* 28EA0 */

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void func_80098AA0(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 temp_ft3;
    s32 temp_ft3_2;
    s32 temp_ft3_3;

    temp_ft3 = (s32) (arg1 * 65536.0f);
    FIELD(arg0, s32, 0) = (s32) (((u32) temp_ft3 >> 0x10) << 0x10);
    FIELD(arg0, s32, 0x20) = (s32) (temp_ft3 << 0x10);
    temp_ft3_2 = (s32) (arg2 * 65536.0f);
    FIELD(arg0, u32, 8) = (u32) ((u32) temp_ft3_2 >> 0x10);
    FIELD(arg0, s32, 0x28) = (s32) (temp_ft3_2 & 0xFFFF);
    temp_ft3_3 = (s32) (arg3 * 65536.0f);
    FIELD(arg0, s32, 0x14) = (s32) (((u32) temp_ft3_3 >> 0x10) << 0x10);
    FIELD(arg0, s32, 0x34) = (s32) (temp_ft3_3 << 0x10);
    FIELD(arg0, s32, 0x1C) = 1;
    FIELD(arg0, s32, 4) = 0;
    FIELD(arg0, s32, 0xC) = 0;
    FIELD(arg0, s32, 0x10) = 0;
    FIELD(arg0, s32, 0x18) = 0;
    FIELD(arg0, s32, 0x24) = 0;
    FIELD(arg0, s32, 0x2C) = 0;
    FIELD(arg0, s32, 0x30) = 0;
    FIELD(arg0, s32, 0x38) = 0;
    FIELD(arg0, s32, 0x3C) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/28EA0", func_80098AA0);
#endif
