#include "common.h"

/* 132D30 */

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern u8 D_801951CC[];         /* 0x24-byte records, u16 flags */
extern u8 D_801969BA[];         /* 11-byte records */
extern u8 *D_801F0CB0_ovl_101CE0[];
s32 func_801DA228_ovl_101CE0(u8 *u);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/132D30", func_801DE5F0_ovl_101CE0);

/* Whether unit u (or, with flag 0x40, the unit it is linked to) has record flag 2 set */
#ifdef NON_MATCHING
/* The structure matches. The original tests flag 2 with andi + sltu where GCC here emits srl + andi, and the linked unit's 0x74 value lands in v1 instead of a0. */
s32 func_801DE800_ovl_101CE0(u8 *u) {
    s32 r = 0;

    if (!(FIELD(u, u32, 0) & 0x40)) {
        if (!(FIELD(u, u32, 0) & 0x40000)) {
            if (FIELD(u, s32, 0x74) != -1) {
                r = (FIELD(D_801951CC + FIELD(u, s32, 0x74) * 0x24, u16, 0) & 2) != 0;
            }
        }
    } else {
        u = D_801F0CB0_ovl_101CE0[D_801969BA[func_801DA228_ovl_101CE0(u) * 11]];
        if (!(FIELD(u, u32, 0) & 0x40000)) {
            if (FIELD(u, s32, 0x74) != -1 && (FIELD(D_801951CC + FIELD(u, s32, 0x74) * 0x24, u16, 0) & 2)) {
                r = 1;
            }
        }
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/132D30", func_801DE800_ovl_101CE0);
#endif

INCLUDE_ASM("asm/nonmatchings/132D30", func_801DE8E8_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/132D30", func_801DEAF4_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/132D30", func_801DED50_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/132D30", func_801DEFC0_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/132D30", func_801DF204_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/132D30", func_801DF34C_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/132D30", func_801DF4A0_ovl_101CE0);
