#include "common.h"

/* 2A7010 */

extern s32 D_80220F68;
extern s32 D_80220F6C;
extern s32 D_80220F70;
extern void *D_80239110_ovl_29A4C0[];

void func_8020DD60(void *fn, s32 a);
/* --- end decls --- */

#ifdef NON_MATCHING
/* Scheduling of the index shift differs. */
void func_802377E0_ovl_29A4C0(s32 i, s32 a, s32 b, s32 c) {
    D_80220F68 = a;
    D_80220F6C = b;
    D_80220F70 = c;
    func_8020DD60(D_80239110_ovl_29A4C0[i], 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/2A7010", func_802377E0_ovl_29A4C0);
#endif
