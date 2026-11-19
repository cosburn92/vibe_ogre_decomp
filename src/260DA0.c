#include "common.h"

/* 260DA0 */

extern void *D_80220F20_ovl_25EE90;
extern s32 D_80220D48_ovl_25EE90;
extern s32 D_80220D44_ovl_25EE90;
extern s16 D_80220D40_ovl_25EE90;

void *HMalloc(s32 size);
/* --- end decls --- */

void func_8020C1F0_ovl_25EE90(void) {
    D_80220F20_ovl_25EE90 = HMalloc(0x8000);
    D_80220D48_ovl_25EE90 = 0;
    D_80220D44_ovl_25EE90 = 0;
    D_80220D40_ovl_25EE90 = 0;
}

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020C22C_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020C250_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020C380_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020C4EC_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020C644_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020C704_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020C7B8_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020C860_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020C908_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020C9B0_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020CA58_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020CC00_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020CDF4_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020CE94_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020D024_ovl_25EE90);
