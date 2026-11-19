#include "common.h"

/* E48F0 */

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

extern Gfx *D_800E9BA0;
extern s32 D_8019E180_ovl_0E48F0;
extern u8 D_8018F480;
extern u8 D_80186BD0[];
extern u8 D_80186D90[];
/* --- end decls --- */

void func_80197B70_ovl_0E48F0(void) {
    Gfx *g;

    D_8019E180_ovl_0E48F0 = 8;
    D_8018F480 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xDE000000;
    g->w1 = (u32)D_80186BD0;
}

void func_80197BB0_ovl_0E48F0(void) {
    Gfx *g = D_800E9BA0++;

    g->w0 = 0xDE000000;
    g->w1 = (u32)D_80186D90;
}

INCLUDE_ASM("asm/nonmatchings/E48F0", func_80197BDC_ovl_0E48F0);
