#include "common.h"

/* 49A30 */

extern u8 D_8018F481_ovl_040E80;
extern void *D_8018FDC0_ovl_040E80;
extern s32 D_801939C8_ovl_040E80;
extern s32 D_80197AF4_ovl_040E80;
extern f32 D_80196AF4_ovl_040E80;
extern f32 D_801977D0_ovl_040E80;

void func_8017BDC0_ovl_040E80(void);
void func_8017BF10_ovl_040E80(void);
void func_8017EE64_ovl_040E80(s32 a, u16 b, s16 c, s16 d, s16 e, s16 f);
void func_8017F490_ovl_040E80(void);
void func_8017BFB0_ovl_040E80(u16 a, u8 b, void *c, s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2, s16 x3, s16 y3);
void func_801841F4_ovl_040E80(void);
void func_80180BDC_ovl_040E80(void);
/* --- end decls --- */

void func_80173B30_ovl_040E80(u8 *p) {
    D_8018F481_ovl_040E80 = 0;
    *p = 0;
}

void func_80173B40_ovl_040E80(u8 *p) {
    D_8018F481_ovl_040E80 = *p;
}

void func_80173B50_ovl_040E80(u8 *p) {
    *p = D_8018F481_ovl_040E80;
}

void *func_80173B60_ovl_040E80(void *list) {
    void *old = D_8018FDC0_ovl_040E80;
    void *r;

    D_8018FDC0_ovl_040E80 = list;
    func_8017BDC0_ovl_040E80();
    r = D_8018FDC0_ovl_040E80;
    D_8018FDC0_ovl_040E80 = old;
    return r;
}

void *func_80173BA0_ovl_040E80(void *list) {
    void *old = D_8018FDC0_ovl_040E80;
    void *r;

    D_8018FDC0_ovl_040E80 = list;
    func_8017BF10_ovl_040E80();
    r = D_8018FDC0_ovl_040E80;
    D_8018FDC0_ovl_040E80 = old;
    return r;
}

void func_80173BE0_ovl_040E80(void *list, s32 a, u16 b, s16 c, s16 d, s16 e, s16 f) {
    void *old = D_8018FDC0_ovl_040E80;

    D_8018FDC0_ovl_040E80 = list;
    func_8017EE64_ovl_040E80(a, b, c, d, e, f);
    D_8018FDC0_ovl_040E80 = old;
}

void func_80173C54_ovl_040E80(void *list, u16 a, u8 b, void *c, s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2,
                              s16 x3, s16 y3) {
    void *old = D_8018FDC0_ovl_040E80;

    D_8018FDC0_ovl_040E80 = list;
    func_8017BFB0_ovl_040E80(a, b, c, x0, y0, x1, y1, x2, y2, x3, y3);
    D_8018FDC0_ovl_040E80 = old;
}

void func_80173D14_ovl_040E80(void *list) {
    void *old = D_8018FDC0_ovl_040E80;

    D_8018FDC0_ovl_040E80 = list;
    func_8017F490_ovl_040E80();
    D_8018FDC0_ovl_040E80 = old;
}

void func_80173D4C_ovl_040E80(void *list) {
    void *old = D_8018FDC0_ovl_040E80;

    D_8018FDC0_ovl_040E80 = list;
    func_801841F4_ovl_040E80();
    D_8018FDC0_ovl_040E80 = old;
}

void func_80173D84_ovl_040E80(void *list) {
    void *old = D_8018FDC0_ovl_040E80;

    D_8018FDC0_ovl_040E80 = list;
    func_80180BDC_ovl_040E80();
    D_8018FDC0_ovl_040E80 = old;
}

INCLUDE_ASM("asm/nonmatchings/49A30", func_80173DBC_ovl_040E80);

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 _bcopy(s32 *, void *, s32);
extern s32 D_8018F3A0_ovl_040E80;

/* Fills quad v (four 16-byte vertices from the template) for the screen rectangle (x0, y0) -
 * (x1, y1): centred coordinates and texture coordinates spanning the rectangle */
#ifdef NON_MATCHING
/* 71 vs 70: the original keeps copies of x0/x1 (s5/s6) and compares the sign-extended differences, likely an inline span helper */
void func_80174138_ovl_040E80(void *v, s16 x0, s16 y0, s16 x1, u16 y1) {
    s32 w, h;
    s16 l, t, r, b;

    _bcopy(&D_8018F3A0_ovl_040E80, v, 0x40);
    w = (x1 - x0 > 0) ? x1 - x0 : x0 - x1;
    h = ((s16)y1 - y0 > 0) ? y1 - y0 : y0 - y1;
    w = (w - 1) << 6;
    h = (h - 1) << 6;
    r = 0xA0 - x1;
    b = 0x78 - y1;
    t = 0x78 - y0;
    l = 0xA0 - x0;
    FIELD(v, s16, 0x12) = t;
    FIELD(v, s16, 0x22) = t;
    FIELD(v, s16, 0) = r;
    FIELD(v, s16, 2) = b;
    FIELD(v, s16, 0xA) = h;
    FIELD(v, s16, 0x10) = r;
    FIELD(v, s16, 0x20) = l;
    FIELD(v, s16, 0x28) = w;
    FIELD(v, s16, 0x30) = l;
    FIELD(v, s16, 0x32) = b;
    FIELD(v, s16, 0x38) = w;
    FIELD(v, s16, 0x3A) = h;
}
#else
INCLUDE_ASM("asm/nonmatchings/49A30", func_80174138_ovl_040E80);
#endif

INCLUDE_ASM("asm/nonmatchings/49A30", func_80174250_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/49A30", func_801758C0_ovl_040E80);

void func_801768D4_ovl_040E80(s32 w, s32 h, s32 x0, s32 y0, s32 x1, s32 y1) {
    D_801939C8_ovl_040E80 = x0;
    D_80197AF4_ovl_040E80 = y0;
    D_80196AF4_ovl_040E80 = (f32)(x1 - x0 + 1) / w;
    D_801977D0_ovl_040E80 = (f32)(y1 - y0 + 1) / h;
}

typedef struct {
    u32 w0;
    u32 w1;
} Gfx49;
extern Gfx49 *D_800E9BA0;

/* Texture rectangle over screen cells x0..x1, y0..y1 (scaled and offset by func_801768D4) showing
 * texels s0..s1, t0..t1 of the tile; clipped to the 320x240 screen, with the texture start
 * advanced past any part left of or above it */
#ifdef NON_MATCHING
/* 0x320 vs 0x324: the opening float conversions schedule lrx before uly (one load-delay nop
 * fewer); from the divides on the code is the same apart from registers and the order of the
 * E4 word's x field */
void func_80176948_ovl_040E80(s32 x0, s32 y0, s32 x1, s32 y1, s32 s0, s32 t0, s32 s1, s32 t1, s32 tile) {
    s32 ulx;
    s32 uly;
    s32 lrx;
    s32 lry;
    s32 s;
    s32 t;
    s32 dsdx;
    s32 dtdy;
    s32 n;
    s32 span;

    ulx = ((s32)(D_80196AF4_ovl_040E80 * x0) + D_801939C8_ovl_040E80) * 4;
    uly = ((s32)(D_801977D0_ovl_040E80 * y0) + D_80197AF4_ovl_040E80) * 4;
    lrx = ((s32)(D_80196AF4_ovl_040E80 * (x1 + 1)) + D_801939C8_ovl_040E80) * 4;
    lry = ((s32)(D_801977D0_ovl_040E80 * (y1 + 1)) + D_80197AF4_ovl_040E80) * 4;
    s = s0 * 32;
    t = t0 * 32;

    span = (s1 - s0 + 1) * 1024;
    n = (lrx - ulx) >> 2;
    if (n != 1) {
        dsdx = span / (n - 1) - 1;
    } else {
        dsdx = span - 1;
    }
    span = (t1 - t0 + 1) * 1024;
    n = (lry - uly) >> 2;
    if (n != 1) {
        dtdy = span / (n - 1) - 1;
    } else {
        dtdy = span - 1;
    }

    if (lrx >= 0 && lry >= 0 && ulx < 0x500 && uly < 0x3C0) {
        u32 w1;
        s32 x;
        s32 y;

        {
            Gfx49 *g = D_800E9BA0++;

            g->w0 = 0xE7000000;
            g->w1 = 0;
        }
        {
            Gfx49 *g = D_800E9BA0++;

            x = lrx;
            if (x > 0x500) {
                x = 0x500;
            }
            x = (x & 0xFFF) << 12;
            y = lry;
            if (y > 0x3C0) {
                y = 0x3C0;
            }
            g->w0 = x | (0xE4000000 | (y & 0xFFF));
            w1 = (tile & 7) << 24;
            if (ulx >= 0) {
                w1 |= (ulx & 0xFFF) << 12;
            }
            g->w1 = w1;
            if (uly >= 0) {
                g->w1 = w1 | (uly & 0xFFF);
            }
        }
        {
            Gfx49 *g = D_800E9BA0++;

            g->w0 = 0xE1000000;
            g->w1 = ((ulx < 0 ? s + ((-ulx * dsdx) >> 7) : s) << 16) | ((uly < 0 ? t + ((-uly * dtdy) >> 7) : t) & 0xFFFF);
        }
        {
            Gfx49 *g = D_800E9BA0++;

            g->w0 = 0xF1000000;
            g->w1 = (dsdx << 16) | (dtdy & 0xFFFF);
        }
        {
            Gfx49 *g = D_800E9BA0++;

            g->w0 = 0xE7000000;
            g->w1 = 0;
        }
    }
    {
        Gfx49 *g = D_800E9BA0++;

        g->w0 = 0xE7000000;
        g->w1 = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/49A30", func_80176948_ovl_040E80);
#endif

INCLUDE_ASM("asm/nonmatchings/49A30", func_80176C6C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/49A30", func_80176F90_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/49A30", func_801772C0_ovl_040E80);
