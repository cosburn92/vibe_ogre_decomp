#include "common.h"

/* 15DF10 */

extern u16 D_80213BF0_ovl_14EBE0[];
extern u8 D_800EB240[];
extern u8 D_800EB290[];

void func_800EA604(void *ch);
/* --- end decls --- */

#ifdef NON_MATCHING
/* Call argument selection laid out differently. */
void func_8020CDA0_ovl_14EBE0(u16 a) {
    u32 i;

    for (i = 0; i < 15; i++) {
        if (a == D_80213BF0_ovl_14EBE0[i]) {
            func_800EA604(D_800EB240);
            return;
        }
    }
    func_800EA604(D_800EB290);
}
#else
INCLUDE_ASM("asm/nonmatchings/15DF10", func_8020CDA0_ovl_14EBE0);
#endif
