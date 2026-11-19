#include "common.h"

/* 263690 */

typedef struct {
    u8 unk0[0xC];
    u16 next;
    u8 unkE[2];
} Slot263; /* size 0x10 */

extern Slot263 *D_80220E14_ovl_25EE90;
extern u16 D_80220E10_ovl_25EE90;

void *HMalloc(s32 size);
void *HFree(void *p);
void bzero(void *p, s32 n);
/* --- end decls --- */

void func_8020EAE0_ovl_25EE90(void) {
    Slot263 *p = HMalloc(0x400);
    s32 i;

    D_80220E14_ovl_25EE90 = p;
    bzero(p, 0x400);
    for (i = 0; i < 63; i++) {
        D_80220E14_ovl_25EE90[i].next = i + 1;
    }
    D_80220E10_ovl_25EE90 = 0;
    D_80220E14_ovl_25EE90[i].next = 0xFFFF;
}

void func_8020EB58_ovl_25EE90(void) {
    HFree(D_80220E14_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/263690", func_8020EB7C_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/263690", func_8020EC2C_ovl_25EE90);
