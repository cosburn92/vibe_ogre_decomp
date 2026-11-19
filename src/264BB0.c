#include "common.h"

/* 264BB0 */

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

extern Gfx *D_800E9BA0;

void func_8020EE30_ovl_25EE90(void *p);
void func_80210000_ovl_25EE90(void *p);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/264BB0", func_80210000_ovl_25EE90);

s32 func_80210374_ovl_25EE90(u8 *o) {
    u8 *p = o + 0x18;

    func_8020EE30_ovl_25EE90(p);
    func_80210000_ovl_25EE90(p);
    return 0;
}

s32 func_802103A8_ovl_25EE90(u8 *o) {
    u8 *p = o + 0x18;
    Gfx *g;

    func_8020EE30_ovl_25EE90(p);
    g = D_800E9BA0++;
    g->w0 = 0xD9FFFFFF;
    g->w1 = 0x400;
    func_80210000_ovl_25EE90(p);
    return 0;
}
