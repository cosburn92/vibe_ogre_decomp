#include "common.h"

/* 264770 */

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

extern Gfx *D_800E9BA0;

void func_8020EE30_ovl_25EE90(void *p);
void func_8020FBC0_ovl_25EE90(void *p);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/264770", func_8020FBC0_ovl_25EE90);

s32 func_8020FF6C_ovl_25EE90(u8 *o) {
    u8 *p = o + 0x18;

    func_8020EE30_ovl_25EE90(p);
    func_8020FBC0_ovl_25EE90(p);
    return 0;
}

s32 func_8020FFA0_ovl_25EE90(u8 *o) {
    u8 *p = o + 0x18;
    Gfx *g;

    func_8020EE30_ovl_25EE90(p);
    g = D_800E9BA0++;
    g->w0 = 0xD9FFFFFF;
    g->w1 = 0x400;
    func_8020FBC0_ovl_25EE90(p);
    return 0;
}
