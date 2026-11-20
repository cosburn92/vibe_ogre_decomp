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

/* Switches the render state to `mode` (bits: 0-1 render mode, 2 geometry flags,
 * 3 alpha compare, 4 texture filter, 5 clears D_8018F480), emitting only what changes */
#ifdef NON_MATCHING
/* render-state switch: only the opening (state load / ~mode) is scheduled differently */
void func_80197BDC_ovl_0E48F0(s32 mode) {
    s32 off;
    s32 on;

    off = D_8019E180_ovl_0E48F0 & ~mode;
    if (D_8019E180_ovl_0E48F0 == mode) {
        return;
    }
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xE7000000;
        _g->w1 = 0;
    }
    if (off != 0) {
        if (off & 4) {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xD9000000;
            _g->w1 = 0;
        }
        if (off & 8) {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xE2001E01;
            _g->w1 = 0;
        }
        if (off & 0x10) {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xE3001201;
            _g->w1 = 0;
        }
        if (off & 0x20) {
            D_8018F480 = 0;
        }
        D_8019E180_ovl_0E48F0 &= ~off | 3;
    }
    on = (D_8019E180_ovl_0E48F0 ^ mode) & mode;
    if (on != 0) {
        if (on & 4) {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xD9FFFFFF;
            _g->w1 = 1;
        }
        if (on & 8) {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xE2001E01;
            _g->w1 = 1;
        }
        if (on & 0x10) {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xE3001201;
            _g->w1 = 0x2000;
        }
        D_8019E180_ovl_0E48F0 |= on & ~3;
    }
    if ((D_8019E180_ovl_0E48F0 & 3) != (mode & 3)) {
        switch ((u32)(mode & 3)) {
            case 0: {
                Gfx *_g = D_800E9BA0++;

                _g->w0 = 0xE200001C;
                _g->w1 = 0x0F0A4000;
                break;
            }
            case 1: {
                Gfx *_g = D_800E9BA0++;

                _g->w0 = 0xE200001C;
                _g->w1 = 0x00552230;
                break;
            }
            case 2: {
                Gfx *_g = D_800E9BA0++;

                _g->w0 = 0xE200001C;
                _g->w1 = 0x00504240;
                break;
            }
            case 3: {
                Gfx *_g = D_800E9BA0++;

                _g->w0 = 0xE200001C;
                _g->w1 = 0x00504A50;
                break;
            }
        }
        D_8019E180_ovl_0E48F0 = (D_8019E180_ovl_0E48F0 & ~3) | (mode & 3);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/E48F0", func_80197BDC_ovl_0E48F0);
#endif
