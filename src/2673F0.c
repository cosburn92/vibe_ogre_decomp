#include "common.h"

/* 2673F0 */

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

extern Gfx *D_800E9BA0;
extern u8 D_802205B0_ovl_25EE90[];

void func_80212840_ovl_25EE90(void *p);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/2673F0", func_80212840_ovl_25EE90);

s32 func_802129BC_ovl_25EE90(u8 *o) {
    Gfx *g = D_800E9BA0++;

    g->w0 = 0xDE000000;
    g->w1 = (u32)D_802205B0_ovl_25EE90;
    func_80212840_ovl_25EE90(o + 0x18);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/2673F0", func_80212A04_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/2673F0", func_80212AB8_ovl_25EE90);
