#include "common.h"

/* 2639E0 */

typedef struct {
    u32 w0;
    u32 w1;
} Gfx263;
extern Gfx263 *D_800E9BA0;
extern u8 D_80220250_ovl_25EE90[];
extern u8 D_802202D0_ovl_25EE90[];
#define G263(w0_, w1_)                 \
    {                                  \
        Gfx263 *_g = D_800E9BA0++;     \
                                       \
        _g->w0 = (w0_);                \
        _g->w1 = (u32)(w1_);           \
    }

/* Display list for object o: setup list by kind (0x10: 0 or 1; hangs otherwise), then the
 * translucent render mode (flag 2) and back-face culling off (flag 1) */
inline void func_8020EE30_ovl_25EE90(u16 *o) {
    switch (o[8]) {
        case 0:
            G263(0xDE000000, D_80220250_ovl_25EE90);
            break;
        case 1:
            G263(0xDE000000, D_802202D0_ovl_25EE90);
            break;
        default:
            for (;;) {
            }
    }
    if (o[0] & 2) {
        G263(0xE200001C, 0x4041C8);
    }
    if (o[0] & 1) {
        G263(0xD9FFFFFF, 0x400);
    }
    G263(0xE7000000, 0);
}

INCLUDE_ASM("asm/nonmatchings/2639E0", func_8020EF40_ovl_25EE90);

void func_8020EF40_ovl_25EE90(void *o);

/* Draws the model at o + 0x18 (setup as func_8020EE30, then func_8020EF40) */
void func_8020EF40_ovl_25EE90(void *o);

/* Draws the model at o + 0x18 (setup as func_8020EE30, then func_8020EF40) */
s32 func_8020F134_ovl_25EE90(u8 *o) {
    u8 *m = o + 0x18;

    func_8020EE30_ovl_25EE90((u16 *)m);
    func_8020EF40_ovl_25EE90(m);
    return 0;
}

/* As func_8020F134 for the model at o + 0x14 */
s32 func_8020F260_ovl_25EE90(u8 *o) {
    u8 *m = o + 0x14;

    func_8020EE30_ovl_25EE90((u16 *)m);
    func_8020EF40_ovl_25EE90(m);
    return 0;
}
