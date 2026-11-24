#include "common.h"

/* 1F8D70 */

typedef struct {
    /* 0x0 */ u8 unk0[4];
    /* 0x4 */ u16 w;
    /* 0x6 */ u16 h;
} Size1F;

extern s32 D_801CEAB4_ovl_1F0A30;
extern s32 D_801D079C_ovl_1F0A30;
extern s32 D_801D07CC_ovl_1F0A30;
extern s32 D_801D07E4_ovl_1F0A30;
extern s32 D_801D07E8_ovl_1F0A30;
extern s32 D_801D07EC_ovl_1F0A30;
extern s16 D_801D07F4_ovl_1F0A30;
extern s16 D_801D07F6_ovl_1F0A30;
extern s16 D_801D07F8_ovl_1F0A30;
extern s16 D_801D07FA_ovl_1F0A30;
extern s16 D_801D07FC_ovl_1F0A30;
extern s16 D_801D07FE_ovl_1F0A30;
extern s16 D_801D0800_ovl_1F0A30;
extern s16 D_801D0802_ovl_1F0A30;
extern s16 D_801D0804_ovl_1F0A30;
extern s16 D_801D0806_ovl_1F0A30;
extern s16 D_801D0808_ovl_1F0A30;
extern s16 D_801D080A_ovl_1F0A30;
extern u8 D_801D080C_ovl_1F0A30;
extern u8 D_801D080D_ovl_1F0A30;
/* Battle-screen state block (0xA0 bytes at D_801D0770) */
typedef struct {
    /* 0x00 */ u8 *spr;
    /* 0x04 */ u8 unk04[0x2C];
    /* 0x30 */ u8 *spr2;
    /* 0x34 */ u8 unk34[0x2C];
    /* 0x60 */ u8 *units;   /* 0x64 each */
    /* 0x64 */ u32 nUnits;
    /* 0x68 */ u8 *objs;    /* 0xF8 each */
    /* 0x6C */ void *buf6C;
    /* 0x70 */ u32 nObjs;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ void *buf78;
    /* 0x7C */ void *buf7C;
    /* 0x80 */ void *buf80;
    /* 0x84 */ u8 unk84[0x1C];
} State1F8; /* size 0xA0 */
extern State1F8 D_801D0770_ovl_1F0A30;
extern void *D_801D0748_ovl_1F0A30[];
extern void *D_801D074C_ovl_1F0A30;
extern void *D_801D0750_ovl_1F0A30;
extern void *D_801D0754_ovl_1F0A30;
extern u8 D_801D0828_ovl_1F0A30[];
extern u8 *D_801CE8C0_ovl_1F0A30;
extern u8 D_801976DC;
extern u8 D_801976E8;

void bzero(void *p, s32 n);
void *HFree(void *p);
void func_801B594C_ovl_1F0A30(Size1F *a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);
f32 func_801BC15C_ovl_1F0A30(s16 x, s16 z, s32 c, s32 d, s32 e);
void func_801C5D64_ovl_1F0A30(void);
void func_801BDC78_ovl_1F0A30(void);
void func_801C62E4_ovl_1F0A30(s32 a, u8 *b, u8 c);
/* 16-byte Vtx */
typedef struct {
    u16 v[8];
} Vtx1F8;
extern Vtx1F8 *D_80197178; /* vertex pool cursor */
extern void *D_800E9BA0;
/* 0x40-byte fixed-point matrix */
typedef struct {
    u8 m[0x40];
} Mtx1F8;
extern Mtx1F8 *D_801969B0; /* matrix pool pointer */
typedef struct {
    u8 *img;
} ImgRef1F8;
typedef struct {
    u16 magic;
} ImgHdr1F8;
void func_801B5D58_ovl_1F0A30(ImgRef1F8 *pp);
void func_801B619C_ovl_1F0A30(void *a, void *b, u8 *img, u8 c, s32 d, s32 e);
void func_801B6970_ovl_1F0A30(void *a, void *b, u8 *img, u8 c, s32 d, s32 e);
void func_801B6DB0_ovl_1F0A30(void *a, void *b, u8 *img);
void func_801B7284_ovl_1F0A30(u8 *img, s16 x, s16 y, s16 s, void *b, void *m, void *a);
extern u8 D_801976DA;
extern s32 D_801CEAB0_ovl_1F0A30;
extern u8 D_801936A7;
extern u8 D_8018F557;
extern u8 D_8018F558;
extern u8 D_8018F559;

/* Map ids 0x22, 0x28, 0x29 and 0x2F-0x39 */
static inline s32 func_1F8D70_isTintedMap(s32 m) {
    switch (m) {
        case 0x22:
        case 0x28:
        case 0x29:
        case 0x2F:
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
            return 1;
        default:
            return 0;
    }
}
/* --- end decls --- */

void func_801B58E0_ovl_1F0A30(void) {
    D_801CEAB4_ovl_1F0A30 = !D_801CEAB4_ovl_1F0A30;
}

s32 func_801B58F8_ovl_1F0A30(void) {
    return D_801CEAB4_ovl_1F0A30;
}

void func_801B5904_ovl_1F0A30(void) {
    s32 *p = &D_801D079C_ovl_1F0A30;

    *p = !*p;
}

void func_801B591C_ovl_1F0A30(void) {
    s32 *p = &D_801D07CC_ovl_1F0A30;

    *p = !*p;
}

s32 func_801B5934_ovl_1F0A30(void) {
    return D_801D079C_ovl_1F0A30;
}

s32 func_801B5940_ovl_1F0A30(void) {
    return D_801D07CC_ovl_1F0A30;
}

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;
#include "gbi_ultra.h"
s32 func_801BE9A8_ovl_1F0A30(s32 fmt, s32 w);
u32 func_801BEA0C_ovl_1F0A30(s32 fmt, s32 w);
void func_801BA0DC_ovl_1F0A30(void *timg, s32 a, s32 b, s32 fmt, s32 siz, s32 stride, s32 height, s32 uls,
                              s32 ult, s32 lrs, s32 lrt, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i);

/* Draws a w x h window at (s, t) of image img to the screen at (x, y) as textured rectangles,
 * in strips of as many rows as fit in TMEM */
void func_801B594C_ovl_1F0A30(Size1F *img, s32 s, s32 t, s32 w, s32 h, s32 x, s32 y) {
    s32 bpr;
    s32 rows;
    s32 i;
    s32 n;
    s32 stride;
    s32 tt;

    if (w == 0) {
        return;
    }
    bpr = func_801BE9A8_ovl_1F0A30(img->unk0[3], w);
    rows = 0x1000 / bpr;
    if (img->unk0[2] == 2) {
        rows = 0x800 / bpr;
    }
    for (i = 0; i < h; i += rows) {
        n = rows;
        if (h - i < rows) {
            n = h - i;
        }
        stride = func_801BEA0C_ovl_1F0A30(img->unk0[3], img->w);
        tt = t + i;
        func_801BA0DC_ovl_1F0A30((u8 *)img + 8, 0, 0, img->unk0[2], img->unk0[3], stride, img->h, s, tt,
                                 s + func_801BEA0C_ovl_1F0A30(img->unk0[3], w) - 1, tt + n - 1, 0, 0, 0, 0, 0,
                                 0, 0);
        gDPPipeSync(((Gfx *)D_800E9BA0)++);
        gSPScisTextureRectangle(((Gfx *)D_800E9BA0)++, x << 2, (y + i) << 2, (x + w) << 2, (y + i + n) << 2, 0, s << 5,
                                tt << 5, 1 << 10, 1 << 10);
        gDPPipeSync(((Gfx *)D_800E9BA0)++);
    }
}

void func_801B5CAC_ovl_1F0A30(Size1F *s, s32 a, s32 b) {
    func_801B594C_ovl_1F0A30(s, 0, 0, s->w, s->h, a, b);
}

inline void func_801B5CE0_ovl_1F0A30(u16 *p, s16 a, s16 b, s16 c, s16 d) {
    bzero(p, 0x10);
    p[0] = a;
    p[1] = b;
    p[4] = c << 6;
    p[5] = d << 6;
    ((u8 *)p)[0xF] = 0xFF;
}

#define VTXP1F8 D_80197178

/* Draws a 16-bit RGBA image centred on the origin as textured quads, in strips of as many rows
 * as fit in TMEM: first the vertex pairs along the strip edges, then a tile load and two
 * triangles per strip */
#ifdef NON_MATCHING
/* Same size; w, -w/2 and the 0xFF alpha constant get s8/s6/s7 instead of s7/s8/s6, which also reorders a few vertex stores */
void func_801B5D58_ovl_1F0A30(ImgRef1F8 *pp) {
    u8 *img = pp->img;
    s32 bpr;
    s32 h;
    u32 w;
    s32 hh;
    s32 hw;
    s32 nhw;
    u8 *timg;
    s32 rows;
    s32 row;
    s32 n;
    u8 *start;

    bpr = func_801BE9A8_ovl_1F0A30(2, ((Size1F *)img)->w);
    h = ((Size1F *)img)->h;
    start = (u8 *)VTXP1F8;
    w = ((Size1F *)img)->w;
    timg = img + 8;
    hh = ((Size1F *)img)->h >> 1;
    rows = 0x1000 / bpr;
    hw = w >> 1;
    nhw = -hw;
    for (row = 0; h > 0; h -= rows, row += rows) {
        func_801B5CE0_ovl_1F0A30((u16 *)VTXP1F8++, nhw, hh - row, 0, row);
        func_801B5CE0_ovl_1F0A30((u16 *)VTXP1F8++, hw, hh - row, w, row);
        if (rows >= h) {
            row += h;
            func_801B5CE0_ovl_1F0A30((u16 *)VTXP1F8++, nhw, hh - row, 0, row);
            func_801B5CE0_ovl_1F0A30((u16 *)VTXP1F8++, hw, hh - row, w, row);
            break;
        }
    }
    h = ((Size1F *)img)->h;
    row = 0;
    while (start + 0x20 < (u8 *)VTXP1F8) {
        n = rows;
        if (h < rows) {
            n = h;
        }
        h -= n;
        gDPLoadTextureTile(((Gfx *)D_800E9BA0)++, timg, G_IM_FMT_RGBA, G_IM_SIZ_16b,
                           func_801BEA0C_ovl_1F0A30(2, w), 0, 0, row, func_801BEA0C_ovl_1F0A30(2, w) - 1,
                           row + n - 1, 0, 0, 0, 0, 0, 0, 0);
        row += n;
        gSPVertex(((Gfx *)D_800E9BA0)++, start, 4, 0);
        gSP2Triangles(((Gfx *)D_800E9BA0)++, 0, 2, 3, 0, 0, 3, 1, 0);
        start += 0x20;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B5D58_ovl_1F0A30);
#endif

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B619C_ovl_1F0A30);

/* Image part: position, size, next part and pixels */
typedef struct Part1F8 {
    /* 0x00 */ u16 x;
    /* 0x02 */ u16 y;
    /* 0x04 */ u16 w;
    /* 0x06 */ u16 h;
    /* 0x08 */ u8 unk08[4];
    /* 0x0C */ struct Part1F8 *next;
    /* 0x10 */ u8 data[1];
} Part1F8;

/* Draws each part of a 32-bit RGBA multi-part image at (d, e) as TMEM-strip textured quads,
 * writing vertices and commands through the given cursors */
#ifdef NON_MATCHING
/* Same size; the vertex cursor, command cursor and row get different saved registers, the vertex stores go through vtx+10 instead of vtx+15, and spill reloads use a3 instead of t0 */
void func_801B6970_ovl_1F0A30(void *a, void *b, u8 *img, u8 c, s32 d, s32 e) {
    u8 *vtx = *(u8 **)a;
    Gfx *gfx = *(Gfx **)b;
    Part1F8 *part = (Part1F8 *)(img + 8);
    s32 i;
    s32 bpr;
    u8 *start;
    s32 h;
    u8 *timg;
    s32 x;
    s32 y;
    s32 w;
    s32 xr;
    s32 rows;
    s32 row;
    s32 n;

    for (i = 0; i < img[3]; part = part->next, i++) {
        Part1F8 *p = part;

        bpr = func_801BE9A8_ovl_1F0A30(3, p->w);
        start = vtx;
        h = p->h;
        timg = p->data;
        x = p->x + d;
        y = p->y + e;
        w = p->w;
        rows = 0x1000 / bpr;
        row = 0;
        xr = x + w;
        for (; h > 0; h -= rows, row += rows) {
            func_801B5CE0_ovl_1F0A30((u16 *)vtx, x, -(y + row), 0, row);
            vtx += 0x10;
            func_801B5CE0_ovl_1F0A30((u16 *)vtx, xr, -(y + row), w, row);
            vtx += 0x10;
            if (rows >= h) {
                row += h;
                func_801B5CE0_ovl_1F0A30((u16 *)vtx, x, -(y + row), 0, row);
                vtx += 0x10;
                func_801B5CE0_ovl_1F0A30((u16 *)vtx, xr, -(y + row), w, row);
                vtx += 0x10;
                break;
            }
        }
        h = p->h;
        row = 0;
        while (start + 0x20 < vtx) {
            n = rows;
            if (h < rows) {
                n = h - 1;
            }
            gDPLoadTextureTile(gfx++, timg, G_IM_FMT_RGBA, G_IM_SIZ_32b, func_801BEA0C_ovl_1F0A30(3, p->w), 0,
                               0, row, func_801BEA0C_ovl_1F0A30(3, p->w) - 1, row + n, 0, 0, 0, 0, 0, 0, 0);
            h -= n;
            row += n;
            gSPVertex(gfx++, start, 4, 0);
            gSP2Triangles(gfx++, 0, 2, 3, 0, 0, 3, 1, 0);
            start += 0x20;
        }
    }
    *(u8 **)a = vtx;
    *(Gfx **)b = gfx;
}
#else
INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B6970_ovl_1F0A30);
#endif

/* Draws each part of a 16-bit RGBA multi-part image at its own position as TMEM-strip textured
 * quads (strips overlap by one row), writing vertices and commands through the given cursors */
void func_801B6DB0_ovl_1F0A30(void *a, void *b, u8 *img) {
    typedef struct { u16 h[8]; } V16;
    V16 *vtx = *(V16 **)a;
    Gfx *gfx = *(Gfx **)b;
    Part1F8 *part = (Part1F8 *)(img + 8);
    s32 i;
    u8 *timg;
    s32 rows;
    V16 *start;
    s32 h;
    s32 x;
    s32 xr;
    s32 w;
    s32 row;
    s32 n;

    for (i = 0; i < img[3]; part = part->next, i++) {
        Part1F8 *p = part;

        rows = 0x1000 / func_801BE9A8_ovl_1F0A30(2, p->w);
        start = vtx;
        h = p->h;
        rows--;
        timg = p->data;
        w = p->w;
        x = p->x;
        row = 0;
        xr = x + w;
        while (h > 0) {
            func_801B5CE0_ovl_1F0A30((u16 *)vtx++, x, -(p->y + row), 0, row);
            func_801B5CE0_ovl_1F0A30((u16 *)vtx++, xr, -(p->y + row), w, row);
            if (rows >= h) {
                row += h;
                func_801B5CE0_ovl_1F0A30((u16 *)vtx++, x, -(p->y + row), 0, row);
                    func_801B5CE0_ovl_1F0A30((u16 *)vtx++, xr, -(p->y + row), w, row);
                    break;
            }
            func_801B5CE0_ovl_1F0A30((u16 *)vtx++, x, -(p->y + row + rows + 1), 0, row + rows + 1);
            func_801B5CE0_ovl_1F0A30((u16 *)vtx++, xr, -(p->y + row + rows + 1), w, row + rows + 1);
            h -= rows;
            row += rows;
        }
        h = p->h;
        row = 0;
        while (start < vtx) {
            n = rows;
            if (h < rows) {
                n = h - 1;
            }
            gDPLoadTextureTile(gfx++, timg, G_IM_FMT_RGBA, G_IM_SIZ_16b, func_801BEA0C_ovl_1F0A30(2, p->w), 0,
                               0, row, func_801BEA0C_ovl_1F0A30(2, p->w) - 1, row + n, 0, 0, 0, 0, 0, 0, 0);
            row += n;
            gSPVertex(gfx++, start, 4, 0);
            gSP2Triangles(gfx++, 0, 2, 3, 0, 0, 3, 1, 0);
            h -= n;
            start += 4;
        }
    }
    *(V16 **)a = vtx;
    *(Gfx **)b = gfx;
}

/* Draws a 16-bit (s == 2) or 32-bit (s == 3) RGBA image at (x, y) as TMEM-strip textured quads,
 * writing commands and vertices through the given cursors (the matrix cursor is passed through) */
void func_801B7284_ovl_1F0A30(u8 *img, s16 x, s16 y, s16 s, void *b, void *m, void *a) {
    typedef struct { u16 h[8]; } V16;
    Size1F *hdr = (Size1F *)img;
    Gfx *gfx;
    V16 *vtx;
    s32 bpr;
    u8 *timg;
    s32 rows;
    V16 *start;
    void *mtx;
    s32 h;
    s32 w;
    s32 xr;
    s32 x0;
    s32 ny;
    s32 row;
    s32 n;

    gfx = *(Gfx **)b;
    vtx = *(V16 **)a;
    mtx = *(void **)m;
    bpr = func_801BE9A8_ovl_1F0A30(s, hdr->w);
    h = hdr->h;
    timg = (u8 *)hdr + 8;
    start = vtx;
    w = hdr->w;
    rows = 0x1000 / bpr;
    row = 0;
    x0 = x;
    ny = -y;
    xr = w + x0;
    for (; h > 0; h -= rows, row += rows) {
        func_801B5CE0_ovl_1F0A30((u16 *)vtx++, x0, ny - row, 0, row);
        func_801B5CE0_ovl_1F0A30((u16 *)vtx++, xr, ny - row, w, row);
        if (rows >= h) {
            row += h;
            func_801B5CE0_ovl_1F0A30((u16 *)vtx++, x0, ny - row, 0, row);
            func_801B5CE0_ovl_1F0A30((u16 *)vtx++, xr, ny - row, w, row);
            break;
        }
    }
    h = hdr->h;
    row = 0;
    while (start + 2 < vtx) {
        n = rows;
        if (h < rows) {
            n = h;
        }
        if (s == 3) {
            gDPLoadTextureTile(gfx++, timg, G_IM_FMT_RGBA, G_IM_SIZ_32b, func_801BEA0C_ovl_1F0A30(3, w), 0, 0,
                               row, func_801BEA0C_ovl_1F0A30(3, w) - 1, row + n - 1, 0, 0, 0, 0, 0, 0, 0);
        } else {
            gDPLoadTextureTile(gfx++, timg, G_IM_FMT_RGBA, G_IM_SIZ_16b, func_801BEA0C_ovl_1F0A30(2, w), 0, 0,
                               row, func_801BEA0C_ovl_1F0A30(2, w) - 1, row + n - 1, 0, 0, 0, 0, 0, 0, 0);
        }
        gSPVertex(gfx++, start, 4, 0);
        gSP2Triangles(gfx++, 0, 2, 3, 0, 0, 3, 1, 0);
        row += n;
        start += 2;
        h -= n;
    }
    *(Gfx **)b = gfx;
    *(void **)m = mtx;
    *(V16 **)a = vtx;
}

/* Draws image img: '64' bitmaps, or 'B5' banks by format (1, 3, other) */
void func_801B77CC_ovl_1F0A30(void *a, void *b, u8 *img, u8 c, s32 d, s32 e) {
    if (*(u16 *)img == 0x3634) {
        func_801B7284_ovl_1F0A30(img, -160, -120, 2, b, &D_801969B0, a);
    } else if (img[2] == 1) {
        func_801B6DB0_ovl_1F0A30(a, b, img);
    } else if (img[2] == 3) {
        func_801B6970_ovl_1F0A30(a, b, img, c, d, e);
    } else {
        func_801B619C_ovl_1F0A30(a, b, img, c, d, e);
    }
}

/* Draws a full-screen image into the main display list */
inline void func_801B7888_ovl_1F0A30(ImgRef1F8 *pp) {
    u8 *img = pp->img;
    s32 pad[2];

    if (((ImgHdr1F8 *)img)->magic == 0x4235) {
        u8 *dst = (u8 *)&D_80197178;
        void *gp = &D_800E9BA0;

        if (img[2] == 1) {
            func_801B6DB0_ovl_1F0A30(dst, gp, img);
        } else if (img[2] == 3) {
            func_801B6970_ovl_1F0A30(dst, gp, img, 0, 0, 0);
        } else {
            func_801B619C_ovl_1F0A30(dst, gp, img, 0, 0, 0);
        }
    } else {
        func_801B5D58_ovl_1F0A30(pp);
    }
}

s32 func_8009C7CC(void);
extern u8 D_801CEAB8_ovl_1F0A30[][4];
extern u8 D_8018F481;

/* Random enemy kind for terrain t (4 choices per terrain from D_801CEAB8); terrains 15 and 19 depend
 * on the current map */
u8 func_801B7914_ovl_1F0A30(s32 t) {
    s32 pad[0x1C];

    if (t != 15 && t != 19) {
        u32 row = (u32)(t - 1) % 22;

        func_8009C7CC();
        func_8009C7CC();
        return D_801CEAB8_ovl_1F0A30[row][func_8009C7CC() & 3];
    }
    if (t == 15) {
        if (D_8018F481 >= 0x2E && D_8018F481 <= 0x2F) {
            return 0x3A;
        }
        if (D_8018F481 == 0x30) {
            return 0x3A;
        }
        func_8009C7CC();
        func_8009C7CC();
        return (func_8009C7CC() & 1) + 0x15;
    }
    if (t == 19) {
        switch (D_8018F481) {
            case 7:
                return 0x33;
            case 17:
                return 0x3B;
            case 20:
                return 0x34;
            case 31:
                return 0x37;
            case 43:
                return 0x35;
            case 48:
                return 0x36;
            case 46:
                return 0x39;
        }
    }
    return 0;
}

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_801BE9A8_ovl_1F0A30(s32 fmt, s32 w);
void func_80080998(void *dst, void *src, s32 n);

/* Copies image src into its own allocation and frees src; a "B5" multi-frame image becomes a chain
 * of separately allocated frames (header link at 0x14, frame links at 0xC) */
#ifdef NON_MATCHING
/* 140/140, 38 words: src and the frame size swap s1/s2 */
void *func_801B7A7C_ovl_1F0A30(u8 *src) {
    u8 *out;
    s32 n;
    u8 *h = src;

    if (FIELD(src, u16, 0) == 0x4235) {
        u8 *o2;
        u8 *p = h + 8;
        s32 sz;
        u32 i;
        void **link;

        if (h[2] == 1) {
            sz = func_801BE9A8_ovl_1F0A30(2, FIELD(h, u16, 0xC)) * FIELD(h, u16, 0xE);
        } else if (h[2] == 3) {
            sz = func_801BE9A8_ovl_1F0A30(3, FIELD(h, u16, 0xC)) * FIELD(h, u16, 0xE);
        } else {
            sz = (func_801BE9A8_ovl_1F0A30(2, FIELD(h, u16, 0xC)) + func_801BE9A8_ovl_1F0A30(1, FIELD(h, u16, 0xC))) * FIELD(h, u16, 0xE);
        }
        n = sz + 0x18;
        o2 = HMalloc(n);
        func_80080998(o2, h, n);
        FIELD(o2, void *, 0x14) = NULL;
        link = (void **)(o2 + 0x14);
        for (i = 1; i < h[3]; i++) {
            u8 *f;

            p += sz + 0x10;
            if (h[2] == 1) {
                sz = func_801BE9A8_ovl_1F0A30(2, FIELD(p, u16, 4)) * FIELD(p, u16, 6);
            } else if (h[2] == 3) {
                sz = func_801BE9A8_ovl_1F0A30(3, FIELD(p, u16, 4)) * FIELD(p, u16, 6);
            } else {
                sz = (func_801BE9A8_ovl_1F0A30(2, FIELD(p, u16, 4)) + func_801BE9A8_ovl_1F0A30(1, FIELD(p, u16, 4))) * FIELD(p, u16, 6);
            }
            n = sz + 0x10;
            *link = HMalloc(n);
            func_80080998(*link, p, n);
            f = *link;
            FIELD(f, void *, 0xC) = NULL;
            link = (void **)(f + 0xC);
        }
        HFree(h);
        return o2;
    }
    n = func_801BE9A8_ovl_1F0A30(src[3], FIELD(src, u16, 4)) * FIELD(src, u16, 6) + 8;
    out = HMalloc(n);
    func_80080998(out, src, n);
    HFree(src);
    return out;
}
#else
INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B7A7C_ovl_1F0A30);
#endif

/* Frees a 'B5' image bank (and its chained pages) */
inline void func_801B7CBC_ovl_1F0A30(u8 *p) {
    if (p != NULL) {
        if (p[0] == 'B' && p[1] == '5') {
            u8 *bank = p;
            u8 *e = *(u8 **)(p + 0x14);
            u32 i;

            for (i = 1; i < bank[3]; i++) {
                u8 *cur = e;

                e = *(u8 **)(cur + 0xC);
                HFree(cur);
            }
        }
        HFree(p);
    }
}

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif

/* Sprite part: offset, size, link to the next part */
typedef struct SprPart1F8 {
    s16 x;
    s16 y;
    u16 w;
    u16 h;
    u8 unk8[4];
    struct SprPart1F8 *next;
} SprPart1F8;

/* Current sprite header: "64" sprites are one centred w x h image (u16 at +4/+6), the others a
 * list of [3] parts starting at +8 */
#define CUR_SPR (D_801D0770_ovl_1F0A30.spr)

/* Bounding box of the current sprite's parts */
static inline void Spr1F8_PartsBox(s32 *r) {
    u8 *s = CUR_SPR;
    SprPart1F8 *p;
    s32 i;

    r[0] = 9999;
    r[1] = 9999;
    r[2] = -9999;
    r[3] = -9999;
    p = (SprPart1F8 *)(s + 8);
    for (i = 0; i < s[3]; i++) {
        if (p->x < r[0]) {
            r[0] = p->x;
        }
        if (r[2] < p->x + p->w) {
            r[2] = p->x + p->w;
        }
        if (p->y < r[1]) {
            r[1] = p->y;
        }
        if (r[3] < p->y + p->h) {
            r[3] = p->y + p->h;
        }
        p = p->next;
    }
}

/* Bounding box (x0, y0, x1, y1) of the current sprite, all zero when there is none */
void func_801B7D54_ovl_1F0A30(s32 *r) {
    u8 *s = CUR_SPR;

    if (s == NULL) {
        r[0] = 0;
        r[1] = 0;
        r[2] = 0;
        r[3] = 0;
    } else if (CUR_SPR[0] == '6' && CUR_SPR[1] == '4') {
        r[0] = -FIELD(s, u16, 4) / 2;
        r[2] = FIELD(s, u16, 4) >> 1;
        r[1] = -FIELD(s, u16, 6) / 2;
        r[3] = FIELD(s, u16, 6) >> 1;
    } else {
        Spr1F8_PartsBox(r);
    }
}

/* 16 zero bytes in rodata (emitted from asm: gcc loses track of the section after INCLUDE_ASM) */
__asm__(".section .rodata
.global D_801D0178_ovl_1F0A30
D_801D0178_ovl_1F0A30:
.word 0, 0, 0, 0
.section .text
");

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B7E9C_ovl_1F0A30);

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void guOrtho(void *m, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, f32 scale);
void func_80098C20(void *m, f32 x, f32 y, f32 z); /* guTranslate */
void func_80098AA0(void *m, f32 x, f32 y, f32 z); /* guScale */
void guRotateRPY(void *m, f32 r, f32 p, f32 y);

typedef struct {
    u32 w0;
    u32 w1;
} Gfx1F8;

/* Loads the projection (ortho 320x240) and o's translate/scale/rotate model matrices */
/* Appends a matrix command for the next matrix of the pool */
static inline void Mtx1F8_Push(u32 w0) {
    Gfx1F8 *g = D_800E9BA0;

    D_800E9BA0 = g + 1;
    g->w0 = w0;
    g->w1 = (u32)D_801969B0++;
}

/* Loads the projection (ortho 320x240) and o's translate/scale/rotate model matrices */
void func_801B8F2C_ovl_1F0A30(u8 *o) {
    Gfx1F8 *g;

    g = D_800E9BA0;
    D_800E9BA0 = g + 1;
    g->w0 = 0xE7000000;
    g->w1 = 0;
    guOrtho(D_801969B0, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);
    func_80098C20(D_801969B0 + 1, FIELD(o, f32, 4), FIELD(o, f32, 8), FIELD(o, f32, 0xC));
    func_80098AA0(D_801969B0 + 2, FIELD(o, f32, 0x1C), FIELD(o, f32, 0x20), FIELD(o, f32, 0x24));
    guRotateRPY(D_801969B0 + 3, FIELD(o, f32, 0x10), FIELD(o, f32, 0x14), FIELD(o, f32, 0x18));
    Mtx1F8_Push(0xDA380007);
    Mtx1F8_Push(0xDA380003);
    Mtx1F8_Push(0xDA380001);
    Mtx1F8_Push(0xDA380001);
}

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B90A8_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B9698_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BA0DC_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BAA38_ovl_1F0A30);

extern u8 D_80220E71;
extern u8 D_80220E73;
extern u8 D_80220E75;
extern u8 D_801CEBA0_ovl_1F0A30[];
extern u8 D_801CEB30_ovl_1F0A30[];
void func_801BAA38_ovl_1F0A30(u8 *u, u8 *tint);

/* Draws the backdrop image (tinted by D_801D0828 when its flag bit 0 is set), then every
 * picture unit that sits nearer the first light plane than the second */
void func_801BB58C_ovl_1F0A30(ImgRef1F8 *pp) {
    Gfx1F8 *g;
    u8 r;
    u8 gr;
    u8 b;
    u8 a;
    u32 i;
    f32 z;
    f32 d0;
    f32 d1;

    if (pp->img != NULL) {
        r = D_80220E71;
        gr = D_80220E73;
        b = D_80220E75;
        g = D_800E9BA0;
        g->w0 = 0xDE000000;
        g->w1 = (u32)D_801CEBA0_ovl_1F0A30;
        D_800E9BA0 = g + 1;
        a = 0xFF;
        if (D_801D0828_ovl_1F0A30[4] & 1) {
            r = r * D_801D0828_ovl_1F0A30[0] / 255;
            gr = gr * D_801D0828_ovl_1F0A30[1] / 255;
            b = b * D_801D0828_ovl_1F0A30[2] / 255;
            a = a * D_801D0828_ovl_1F0A30[3] / 255;
        }
        g[1].w0 = 0xFA000000;
        g[1].w1 = (r << 24) | ((gr & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF);
        D_800E9BA0 = g + 2;
        func_801B7888_ovl_1F0A30(pp);
    }
    {
        Gfx1F8 *g2 = D_800E9BA0;

        g2->w0 = 0xDE000000;
        g2->w1 = (u32)D_801CEB30_ovl_1F0A30;
        g2++;
        D_800E9BA0 = g2;
    }
    for (i = 0; i < D_801D0770_ovl_1F0A30.nUnits; i++) {
        z = *(s16 *)(D_801D0770_ovl_1F0A30.units + i * 0x64 + 4);
        d0 = *(f32 *)&D_801D0770_ovl_1F0A30.unk04[8] - z;
        if (!(d0 > 0.0f)) {
            d0 = -d0;
        }
        d1 = *(f32 *)&D_801D0770_ovl_1F0A30.unk34[8] - z;
        if (!(d1 > 0.0f)) {
            d1 = -d1;
        }
        if (d1 < d0) {
            continue;
        }
        func_801BAA38_ovl_1F0A30(D_801D0770_ovl_1F0A30.units + i * 0x64,
                                 (D_801D0828_ovl_1F0A30[4] & 2) ? D_801D0828_ovl_1F0A30 : NULL);
    }
}

extern u8 D_801CEC18_ovl_1F0A30[];
void func_801B90A8_ovl_1F0A30(u8 *img);

typedef union {
    Gfx1F8 words;
    long long force_align[1];
} GfxU1F8;
#define GFX1F8(a, b)                                       \
    {                                                      \
        GfxU1F8 *_g = ((GfxU1F8 *)D_800E9BA0)++;         \
        _g->words.w0 = (a);                                \
        _g->words.w1 = (b);                                \
    }

/* Draws the picture units behind the second light plane, then the foreground image (tinted by
 * D_801D0828 when its flag bit 3 is set) followed by pipe syncs, then the units in front of it */
void func_801BB87C_ovl_1F0A30(ImgRef1F8 *pp) {
    Gfx1F8 *g;
    u8 r;
    u8 gr;
    u8 b;
    u8 a;
    u32 i;
    f32 z;
    f32 d0;
    f32 d1;

    {
        Gfx1F8 *g2 = D_800E9BA0;

        g2->w0 = 0xDE000000;
        g2->w1 = (u32)D_801CEB30_ovl_1F0A30;
        g2++;
        D_800E9BA0 = g2;
    }
    for (i = 0; i < D_801D0770_ovl_1F0A30.nUnits; i++) {
        z = *(s16 *)(D_801D0770_ovl_1F0A30.units + i * 0x64 + 4);
        d0 = *(f32 *)&D_801D0770_ovl_1F0A30.unk04[8] - z;
        if (!(d0 > 0.0f)) {
            d0 = -d0;
        }
        d1 = *(f32 *)&D_801D0770_ovl_1F0A30.unk34[8] - z;
        if (!(d1 > 0.0f)) {
            d1 = -d1;
        }
        if (d0 <= d1) {
            continue;
        }
        if (z <= *(f32 *)&D_801D0770_ovl_1F0A30.unk34[8]) {
            continue;
        }
        func_801BAA38_ovl_1F0A30(D_801D0770_ovl_1F0A30.units + i * 0x64,
                                 (D_801D0828_ovl_1F0A30[4] & 4) ? D_801D0828_ovl_1F0A30 : NULL);
    }
    if (pp->img != NULL) {
        r = D_80220E71;
        gr = D_80220E73;
        b = D_80220E75;
        g = D_800E9BA0;
        g->w0 = 0xDE000000;
        g->w1 = (u32)D_801CEC18_ovl_1F0A30;
        D_800E9BA0 = g + 1;
        a = 0xFF;
        if (D_801D0828_ovl_1F0A30[4] & 8) {
            r = r * D_801D0828_ovl_1F0A30[0] / 255;
            gr = gr * D_801D0828_ovl_1F0A30[1] / 255;
            b = b * D_801D0828_ovl_1F0A30[2] / 255;
            a = a * D_801D0828_ovl_1F0A30[3] / 255;
        }
        g[1].w0 = 0xFA000000;
        g[1].w1 = (r << 24) | ((gr & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF);
        D_800E9BA0 = g + 2;
        func_801B90A8_ovl_1F0A30(pp->img);
        GFX1F8(0xE7000000, 0);
        GFX1F8(0xE7000000, 0);
        GFX1F8(0xE3000A01, 0);
        GFX1F8(0xE7000000, 0);
    }
    {
        Gfx1F8 *g2 = D_800E9BA0;

        g2->w0 = 0xDE000000;
        g2->w1 = (u32)D_801CEB30_ovl_1F0A30;
        g2++;
        D_800E9BA0 = g2;
    }
    for (i = 0; i < D_801D0770_ovl_1F0A30.nUnits; i++) {
        z = *(s16 *)(D_801D0770_ovl_1F0A30.units + i * 0x64 + 4);
        d0 = *(f32 *)&D_801D0770_ovl_1F0A30.unk04[8] - z;
        if (!(d0 > 0.0f)) {
            d0 = -d0;
        }
        d1 = *(f32 *)&D_801D0770_ovl_1F0A30.unk34[8] - z;
        if (!(d1 > 0.0f)) {
            d1 = -d1;
        }
        if (d0 <= d1) {
            continue;
        }
        if (*(f32 *)&D_801D0770_ovl_1F0A30.unk34[8] < z) {
            continue;
        }
        func_801BAA38_ovl_1F0A30(D_801D0770_ovl_1F0A30.units + i * 0x64,
                                 (D_801D0828_ovl_1F0A30[4] & 0x10) ? D_801D0828_ovl_1F0A30 : NULL);
    }
}

void func_801ADB00_ovl_1F0A30(s32 o);
void func_801C24F8_ovl_1F0A30(s32 a, u16 b);

/* Frees everything the battle screen allocated and clears its state */
void func_801BBC78_ovl_1F0A30(void) {
    u32 i;

    func_801BD1F4_ovl_1F0A30();
    func_801B7CBC_ovl_1F0A30(D_801D0770_ovl_1F0A30.spr);
    func_801B7CBC_ovl_1F0A30(D_801D0770_ovl_1F0A30.spr2);
    HFree(D_801D0770_ovl_1F0A30.buf78);
    HFree(D_801D0770_ovl_1F0A30.buf7C);
    HFree(D_801D0770_ovl_1F0A30.buf80);
    for (i = 0; i < D_801D0770_ovl_1F0A30.nObjs; i++) {
        func_801ADB00_ovl_1F0A30(*(s32 *)(D_801D0770_ovl_1F0A30.objs + i * 0xF8));
    }
    HFree(D_801D0770_ovl_1F0A30.objs);
    HFree(D_801D0770_ovl_1F0A30.buf6C);
    for (i = 0; i < D_801D0770_ovl_1F0A30.nUnits; i++) {
        func_801C24F8_ovl_1F0A30(FIELD(D_801D0770_ovl_1F0A30.units + i * 0x64, s32, 0x14), FIELD(D_801D0770_ovl_1F0A30.units + i * 0x64, u16, 6));
    }
    HFree(D_801D0770_ovl_1F0A30.units);
    bzero(&D_801D0770_ovl_1F0A30, sizeof(State1F8));
}

f32 sqrtf(f32);

/* Floor triangle under (x, z): of the n triangles (vertex index triples into the x/y/z s16 vertex
 * list) whose x/z bounding box holds the point, the one with the smallest summed distance from the
 * point to its corners; n when there is none */
typedef struct {
    u16 v[3];
} Tri1F8;

u32 func_801BBE60_ovl_1F0A30(s16 x, s16 z, s16 *verts, Tri1F8 *tris, u32 n);

#ifdef NON_MATCHING
/* 5 instructions longer: the original re-reads the first corner's coordinates for each min/max
 * (lhu for the value, lh for the compare), keeps n in fp and the result in s7, and steps the
 * triangle pointer unbiased */
u32 func_801BBE60_ovl_1F0A30(s16 x, s16 z, s16 *verts, Tri1F8 *tris, u32 n) {
    f32 best = 999999.0f;
    u32 found = n;
    u32 i;

    for (i = 0; i < n; i++, tris++) {
        s16 *a = &verts[tris->v[0] * 3];
        s16 *b = &verts[tris->v[1] * 3];
        s16 *c = &verts[tris->v[2] * 3];
        s16 x0;
        s16 x1;
        s16 z0;
        s16 z1;
        f32 dx[4];
        f32 dz[4];
        s32 pad[7];
        f32 sum;
        u32 k;

        x0 = a[0];
        if (b[0] < a[0]) {
            x0 = b[0];
        }
        if (c[0] < x0) {
            x0 = c[0];
        }
        x1 = a[0];
        if (a[0] < b[0]) {
            x1 = b[0];
        }
        if (x1 < c[0]) {
            x1 = c[0];
        }
        z0 = a[2];
        if (b[2] < a[2]) {
            z0 = b[2];
        }
        if (c[2] < z0) {
            z0 = c[2];
        }
        z1 = a[2];
        if (a[2] < b[2]) {
            z1 = b[2];
        }
        if (z1 < c[2]) {
            z1 = c[2];
        }
        if (x < x0 || x1 < x) {
            continue;
        }
        if (z < z0 || z1 < z) {
            continue;
        }
        dx[0] = a[0] - x;
        dz[0] = a[2] - z;
        dx[1] = b[0] - x;
        dz[1] = b[2] - z;
        dx[2] = c[0] - x;
        dz[2] = c[2] - z;
        sum = 0.0f;
        for (k = 0; k < 3; k++) {
            sum += sqrtf(dx[k] * dx[k] + dz[k] * dz[k]);
        }
        if (sum < best) {
            best = sum;
            found = i;
        }
    }
    return found;
}
#else
INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BBE60_ovl_1F0A30);
#endif

/* Height of the floor at (x, -z): finds the floor plane under the point (clamping it into the
 * field when none is found) and projects the point onto it; 0 when there is no plane */
#ifdef NON_MATCHING
/* 124/124 instructions, 8 words differ: the projected x and y swap float registers */
f32 func_801BC15C_ovl_1F0A30(s16 x, s16 z, s32 c, s32 d, s32 e) {
    f32 h = 0.0f;
    s16 nz = -z;
    s32 k = func_801BBE60_ovl_1F0A30(x, nz, (s16 *)c, (Tri1F8 *)d, e);

    if (k == e) {
        if (x > 0xAA) {
            x = 0xAA;
        }
        if (x < -0xAA) {
            x = -0xAA;
        }
        if (nz > 0x39) {
            nz = 0x39;
        }
        if (nz < -0x39) {
            nz = -0x39;
        }
        k = func_801BBE60_ovl_1F0A30(x, nz, (s16 *)c, (Tri1F8 *)d, k);
        if (k == e) {
            return h;
        }
    }
    {
        f64 *pl = (f64 *)D_801D0770_ovl_1F0A30.buf80 + k * 4;
        f64 n = pl[0] * pl[0] + pl[1] * pl[1] + pl[2] * pl[2];
        f64 f = pl[0] * x + pl[2] * nz + pl[3];
        f64 px;
        f64 py;
        f64 pz;
        f64 zero = 0.0;

        if (f > zero) {
            py = f * -pl[1] / n;
            px = f * -pl[0] / n;
            pz = f * -pl[2] / n;
        } else {
            py = -f * pl[1] / n;
            px = -f * pl[0] / n;
            pz = -f * pl[2] / n;
        }
        if (py != zero) {
            h = (px * px + pz * pz) / py + py;
        }
    }
    return h;
}
#else
INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BC15C_ovl_1F0A30);
#endif

void func_801BC35C_ovl_1F0A30(s16 a, s16 b) {
    func_801BC15C_ovl_1F0A30(a, b, D_801D07E8_ovl_1F0A30, D_801D07EC_ovl_1F0A30, D_801D07E4_ovl_1F0A30);
}

void func_801BC3A0_ovl_1F0A30(s16 a, s16 b, s16 c, s16 d) {
    D_801D07F4_ovl_1F0A30 = a;
    D_801D07F6_ovl_1F0A30 = b;
    D_801D07F8_ovl_1F0A30 = c;
    D_801D07FA_ovl_1F0A30 = d;
    D_801D080C_ovl_1F0A30 = 0;
    D_801D080D_ovl_1F0A30 = 1;
}

void func_801BC3D8_ovl_1F0A30(s16 a, s16 b, s16 c, s16 d, u8 e) {
    D_801D0804_ovl_1F0A30 = a;
    D_801D0806_ovl_1F0A30 = b;
    D_801D0808_ovl_1F0A30 = c;
    D_801D080A_ovl_1F0A30 = d;
    D_801D080D_ovl_1F0A30 = 0;
    D_801D07FC_ovl_1F0A30 = D_801D07F4_ovl_1F0A30;
    D_801D07FE_ovl_1F0A30 = D_801D07F6_ovl_1F0A30;
    D_801D0800_ovl_1F0A30 = D_801D07F8_ovl_1F0A30;
    D_801D0802_ovl_1F0A30 = D_801D07FA_ovl_1F0A30;
    D_801D080C_ovl_1F0A30 = e;
}

/* Steps the box tween: frame D_801D080D of D_801D080C, from the 07FC.. rect toward 0804.. */
void func_801BC450_ovl_1F0A30(void) {
    u32 temp_t4;

    if (D_801D080C_ovl_1F0A30 != 0) {
        temp_t4 = D_801D080D_ovl_1F0A30 & 0xFF;
        if ((u8) D_801D080C_ovl_1F0A30 >= temp_t4) {
            D_801D080D_ovl_1F0A30 += 1;
            D_801D07F4_ovl_1F0A30 = D_801D07FC_ovl_1F0A30 + ((s32) ((D_801D0804_ovl_1F0A30 - D_801D07FC_ovl_1F0A30) * temp_t4) / (s32) D_801D080C_ovl_1F0A30);
            D_801D07F6_ovl_1F0A30 = D_801D07FE_ovl_1F0A30 + ((s32) ((D_801D0806_ovl_1F0A30 - D_801D07FE_ovl_1F0A30) * temp_t4) / (s32) D_801D080C_ovl_1F0A30);
            D_801D07F8_ovl_1F0A30 = D_801D0800_ovl_1F0A30 + ((s32) ((D_801D0808_ovl_1F0A30 - D_801D0800_ovl_1F0A30) * temp_t4) / (s32) D_801D080C_ovl_1F0A30);
            D_801D07FA_ovl_1F0A30 = D_801D0802_ovl_1F0A30 + ((s32) ((D_801D080A_ovl_1F0A30 - D_801D0802_ovl_1F0A30) * temp_t4) / (s32) D_801D080C_ovl_1F0A30);
        }
    }
}

void func_801BC5FC_ovl_1F0A30(void) {
    bzero(&D_801D0770_ovl_1F0A30, 0xA0);
    bzero(D_801D0748_ovl_1F0A30, 0x1C);
    bzero(D_801D0828_ovl_1F0A30, 5);
}

/* Two light/fog parameter blocks (0x30 bytes each) at D_801D0774 */
typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 dir[3];
    /* 0x18 */ f32 scale[3];
    /* 0x24 */ u8 rgba[4];
    /* 0x28 */ s32 on;
    /* 0x2C */ u8 unk2C[4];
} Light1F8;
extern Light1F8 D_801D0774_ovl_1F0A30[2];

/* Resets both light blocks and the 0x1A-byte state at D_801D07F4 */
void func_801BC640_ovl_1F0A30(void) {
    D_801D0774_ovl_1F0A30[0].rgba[0] = D_801D0774_ovl_1F0A30[0].rgba[1] = D_801D0774_ovl_1F0A30[0].rgba[2] = D_801D0774_ovl_1F0A30[0].rgba[3] = 0xFF;
    D_801D0774_ovl_1F0A30[0].on = 1;
    D_801D0774_ovl_1F0A30[1].rgba[0] = D_801D0774_ovl_1F0A30[1].rgba[1] = D_801D0774_ovl_1F0A30[1].rgba[2] = D_801D0774_ovl_1F0A30[1].rgba[3] = 0xFF;
    D_801D0774_ovl_1F0A30[1].on = 1;
    D_801D0774_ovl_1F0A30[0].pos[0] = D_801D0774_ovl_1F0A30[0].pos[1] = 0.0f;
    D_801D0774_ovl_1F0A30[0].dir[0] = D_801D0774_ovl_1F0A30[0].dir[1] = D_801D0774_ovl_1F0A30[0].dir[2] = 0.0f;
    D_801D0774_ovl_1F0A30[1].pos[0] = D_801D0774_ovl_1F0A30[1].pos[1] = 0.0f;
    D_801D0774_ovl_1F0A30[1].dir[0] = D_801D0774_ovl_1F0A30[1].dir[1] = D_801D0774_ovl_1F0A30[1].dir[2] = 0.0f;
    D_801D0774_ovl_1F0A30[0].pos[2] = -5.0f;
    D_801D0774_ovl_1F0A30[0].scale[0] = D_801D0774_ovl_1F0A30[0].scale[1] = D_801D0774_ovl_1F0A30[0].scale[2] = 1.0f;
    D_801D0774_ovl_1F0A30[1].pos[2] = -905.0f;
    D_801D0774_ovl_1F0A30[1].scale[0] = D_801D0774_ovl_1F0A30[1].scale[1] = D_801D0774_ovl_1F0A30[1].scale[2] = 1.0f;
    bzero(&D_801D07F4_ovl_1F0A30, 0x1A);
}

/* Channel tint for the current map (ids 0x3B/0x2E special-cased) */
u8 func_801BC76C_ovl_1F0A30(void) {
    s32 t;

    if ((D_801976DA ^ 0x18) == 0) {
        return 0xFF;
    }
    if (D_801CEAB0_ovl_1F0A30 == 0x3B && D_801936A7 == 0x20) {
        return 0xFF;
    }
    if (D_801CEAB0_ovl_1F0A30 == 0x2E) {
        return 0xFF;
    }
    if (func_1F8D70_isTintedMap(D_801CEAB0_ovl_1F0A30)) {
        return 0xFF;
    }
    t = D_8018F557 * 128 / 255;
    if (t + 128 >= 0xFF) {
        return 0xFF;
    }
    return t + 128;
}

u8 func_801BC838_ovl_1F0A30(void) {
    s32 t;

    if ((D_801976DA ^ 0x18) == 0) {
        return 0xFF;
    }
    if (D_801CEAB0_ovl_1F0A30 == 0x3B && D_801936A7 == 0x20) {
        return 0x80;
    }
    if (D_801CEAB0_ovl_1F0A30 == 0x2E) {
        return 0xD2;
    }
    if (func_1F8D70_isTintedMap(D_801CEAB0_ovl_1F0A30)) {
        return 0xFF;
    }
    t = D_8018F558 * 128 / 255;
    if (t + 128 >= 0xFF) {
        return 0xFF;
    }
    return t + 128;
}

u8 func_801BC914_ovl_1F0A30(void) {
    s32 t;

    if ((D_801976DA ^ 0x18) == 0) {
        return 0xFF;
    }
    if (D_801CEAB0_ovl_1F0A30 == 0x3B && D_801936A7 == 0x20) {
        return 0x80;
    }
    if (D_801CEAB0_ovl_1F0A30 == 0x2E) {
        return 0;
    }
    if (func_1F8D70_isTintedMap(D_801CEAB0_ovl_1F0A30)) {
        return 0xFF;
    }
    t = D_8018F559 * 128 / 255;
    if (t + 128 >= 0xFF) {
        return 0xFF;
    }
    return t + 128;
}

/* Scrolling picture unit (0x64 bytes, D_801D0770.units) */
typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ u8 unk04[4];
    /* 0x08 */ s16 x0;
    /* 0x0A */ s16 y0;
    /* 0x0C */ s16 x1;
    /* 0x0E */ s16 y1;
    /* 0x10 */ u16 flags;
    /* 0x12 */ u8 unk12[2];
    /* 0x14 */ u8 anim[0xC];
    /* 0x20 */ s16 ox;
    /* 0x22 */ s16 oy;
    /* 0x24 */ u8 unk24[0x40];
} Scroll1F8;

typedef struct {
    /* 0x00 */ u8 unk00[0x1E];
    /* 0x1E */ s16 h1E;
    /* 0x20 */ u8 unk20[0x24];
    /* 0x44 */ u8 anim[4];
    /* 0x48 */ s16 frame;
    /* 0x4A */ u8 unk4A[6];
    /* 0x50 */ s16 h50;
    /* 0x52 */ s16 h52;
    /* 0x54 */ s16 h54;
    /* 0x56 */ u8 unk56[0x3E];
    /* 0x94 */ s32 flags;
} Panel1F8;

/* Battle object slot (0xF8 bytes, D_801D0770.objs) */
typedef struct {
    /* 0x00 */ Panel1F8 *panel;
    /* 0x04 */ u8 unk04[0x28];
    /* 0x2C */ u16 h2C;
    /* 0x2E */ u8 unk2E[0xA];
    /* 0x38 */ u16 frames;
    /* 0x3A */ u16 base;
    /* 0x3C */ u8 unk3C[0xC];
    /* 0x48 */ s32 speed;
    /* 0x4C */ u8 unk4C[0xAC];
} Obj1F8;

extern u8 D_801CEAA9;
extern u8 *D_801D07D8_ovl_1F0A30; /* D_801D0770.objs */
extern u32 D_801D07E0_ovl_1F0A30; /* D_801D0770.nObjs */
void BattleAnimStep(void *a, s32 b, s32 c, s32 d, s32 e);
void func_801AD9D4_ovl_1F0A30(void *p, s32 a);

/* Per-frame update: wraps the scrolling pictures, steps the object animations (looping the
 * ones that ran off), the box tween and the two countdown timers */
#ifdef NON_MATCHING
/* one instruction short: the original keeps copies of the panel/object pointers and of top
 * (a0/a3/a2) for the scrolled-off check and its reset branch; ours uses s2/a1 directly */
void func_801BC9F0_ovl_1F0A30(void) {
    s32 pad[2];
    u32 i;
    Scroll1F8 *s;
    Obj1F8 *o;
    Panel1F8 *p;
    u16 prev;
    s16 top;
    s16 h52;
    s16 h50;
    s16 h54;
    u8 *c;

    for (i = 0; i < D_801D0770_ovl_1F0A30.nUnits; i++) {
        s = (Scroll1F8 *)D_801D0770_ovl_1F0A30.units + i;
        BattleAnimStep(s->anim, 0x100, 0, 0, 0);
        if (s->flags & 1) {
            if (s->x0 > s->x + s->ox) {
                s->ox = s->x1 + s->ox - s->x0;
            }
            if (s->x1 < s->x + s->ox) {
                s->ox = s->x0 + s->ox - s->x1;
            }
            if (s->y0 > s->y + s->oy) {
                s->oy = s->y1 + s->oy - s->y0;
            }
            if (s->y1 < s->y + s->oy) {
                s->oy = s->y0 + s->oy - s->y1;
            }
        }
    }
    for (i = 0; i < D_801D07E0_ovl_1F0A30; i++) {
        o = (Obj1F8 *)(i * sizeof(Obj1F8) + (u32)D_801D07D8_ovl_1F0A30);
        prev = o->panel->frame;
        BattleAnimStep(o->panel->anim, o->speed, 0, 0, 0);
        o = (Obj1F8 *)(i * sizeof(Obj1F8) + (u32)D_801D07D8_ovl_1F0A30);
        p = o->panel;
        if (p->flags & 0x10) {
            top = p->h1E;
            h52 = p->h52;
            if (top + h52 < 0) {
                if (p->frame != prev) {
                    p->h50 = 0;
                    p->h54 = 0;
                    p->h52 = o->h2C - top;
                } else if (p->frame < o->frames) {
                    h50 = p->h50;
                    h54 = p->h54;
                    func_801AD9D4_ovl_1F0A30(p->anim, p->frame + o->base);
                    p->h50 = h50;
                    p->h52 = h52;
                    p->h54 = h54;
                }
            }
        }
    }
    func_801BC450_ovl_1F0A30();
    c = D_801CE8C0_ovl_1F0A30;
    if (c[0x82C] != 0) {
        if (--c[0x82C] == 0) {
            D_801CEAA9 = 0;
        }
    }
    c = D_801CE8C0_ovl_1F0A30;
    if (c[0x82D] != 0) {
        if (--c[0x82D] == 0) {
            D_801D0804_ovl_1F0A30 = 0;
            D_801D0806_ovl_1F0A30 = 0;
            D_801D0808_ovl_1F0A30 = 0;
            D_801D080A_ovl_1F0A30 = 0;
            D_801D080C_ovl_1F0A30 = 2;
            D_801D080D_ovl_1F0A30 = 0;
            D_801D07FC_ovl_1F0A30 = D_801D07F4_ovl_1F0A30;
            D_801D07FE_ovl_1F0A30 = D_801D07F6_ovl_1F0A30;
            D_801D0800_ovl_1F0A30 = D_801D07F8_ovl_1F0A30;
            D_801D0802_ovl_1F0A30 = D_801D07FA_ovl_1F0A30;
        }
    }
    func_801BDF40_ovl_1F0A30();
}
#else
INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BC9F0_ovl_1F0A30);
#endif

extern void *D_800C4BB8;
extern u8 D_800E7A0C;
extern u16 *D_800A8204[3];
void nuGfxTaskAllEndWait(void);
void *HMalloc(s32 size);
u32 func_801BEA0C_ovl_1F0A30(s32 fmt, s32 w);

/* Flattens the current 'B5' part sprite into a free frame buffer at the light position and
 * replaces it with a full-screen 320x240 '64' image copied from there */
void func_801BCD0C_ovl_1F0A30(void) {
    u8 *s = CUR_SPR;
    SprPart1F8 *p = (SprPart1F8 *)(s + 8);
    s32 ox;
    s32 oy;
    u8 fb[2];
    u16 *dst;
    s32 n;
    u8 *out;

    if (*(u16 *)s != 0x4235) {
        return;
    }
    ox = D_801D0774_ovl_1F0A30[0].pos[0];
    oy = D_801D0774_ovl_1F0A30[0].pos[1];
    nuGfxTaskAllEndWait();
    fb[0] = 0;
    fb[1] = 1;
    if (D_800E7A0C == 1) {
        if (D_800C4BB8 == D_800A8204[0]) {
            fb[0] = 1;
            fb[1] = 2;
        } else if (D_800C4BB8 == D_800A8204[1]) {
            fb[0] = 0;
            fb[1] = 2;
        } else if (D_800C4BB8 == D_800A8204[2]) {
            fb[0] = 0;
            fb[1] = 1;
        }
    }
    dst = D_800A8204[fb[0]];
    for (n = 0; n < s[3]; n++) {
        SprPart1F8 *q = p;
        u16 *pix = (u16 *)(p + 1);
        s32 x0 = ox + p->x + 160;
        s32 y0 = -oy + p->y + 120;
        s32 stride = func_801BEA0C_ovl_1F0A30(2, p->w);
        s32 j;

        for (j = 0; j < q->h; j++) {
            s32 i;

            for (i = 0; i < q->w; i++) {
                s32 xx = x0 + i;
                s32 yy = y0 + j;

                if (xx >= 0 && xx < 320 && yy >= 0 && yy < 240) {
                    dst[yy * 320 + xx] = pix[j * stride + i];
                }
            }
        }
        p = p->next;
    }
    func_801B7CBC_ovl_1F0A30(CUR_SPR);
    out = HMalloc(0x25808);
    out[0] = '6';
    out[1] = '4';
    out[3] = 2;
    FIELD(out, u16, 4) = 320;
    out[2] = 0;
    FIELD(out, u16, 6) = 240;
    func_80080998(out + 8, dst, 0x25800);
    CUR_SPR = out;
}

s32 func_801BCFE4_ovl_1F0A30(void) {
    return (s32)D_801D0770_ovl_1F0A30.spr;
}

/* 16 zero bytes in rodata (emitted from asm: gcc loses track of the section after INCLUDE_ASM) */
__asm__(".section .rodata
.global D_801D02B0_ovl_1F0A30
D_801D02B0_ovl_1F0A30:
.word 0, 0, 0, 0
.section .text
");

typedef struct {
    s32 unk0;
    s32 index;
    u8 *buf;
    s32 size;
} Arc16_1F8;
extern Arc16_1F8 D_801D02B0_ovl_1F0A30;
extern u8 D_801CEC80_ovl_1F0A30[];
extern s16 D_801D0758_ovl_1F0A30;
extern s16 D_801D075A_ovl_1F0A30;
extern s16 D_801D075C_ovl_1F0A30;
extern s16 D_801D075E_ovl_1F0A30;
extern s16 D_801D0760_ovl_1F0A30;
void *LoadChunk(s32 id);
void *func_80071C04(s32 size);
s32 ChunkSize(s32 id);
void *LoadChunkRaw(void *dst, s32 id);
void func_8007ACB0(void *arc, void *reqs, s32 n);
void func_801C5CE0_ovl_1F0A30(void);

/* Reloads the battle frame graphics; the backdrop comes from the map's LHa archive (entry chosen by
 * the time of day) */
void func_801BCFF0_ovl_1F0A30(void) {
    Arc16_1F8 arc;
    Arc16_1F8 req;
    u8 *dir;
    s32 id;

    HFree(D_801D0748_ovl_1F0A30[0]);
    D_801D0748_ovl_1F0A30[0] = NULL;
    HFree(D_801D074C_ovl_1F0A30);
    D_801D074C_ovl_1F0A30 = NULL;
    HFree(D_801D0750_ovl_1F0A30);
    D_801D0750_ovl_1F0A30 = NULL;
    HFree(D_801D0754_ovl_1F0A30);
    D_801D0754_ovl_1F0A30 = NULL;
    D_801D0748_ovl_1F0A30[0] = LoadChunk(0x31D484);
    D_801D074C_ovl_1F0A30 = LoadChunk(0x31EE10);
    D_801D0750_ovl_1F0A30 = LoadChunk(0x32007E);
    arc = D_801D02B0_ovl_1F0A30;
    req = D_801D02B0_ovl_1F0A30;
    dir = func_80071C04(ChunkSize(0x0218E9B4));
    LoadChunkRaw(dir, 0x0218E9B4);
    id = FIELD(dir, s32, 8);
    HFree(dir);
    arc.size = ChunkSize(id);
    arc.buf = func_80071C04(arc.size);
    LoadChunkRaw(arc.buf, id);
    req.index = D_801CEC80_ovl_1F0A30[D_801976DA == 0x18 ? 12 : (u8)(D_801976DA % 24)];
    func_8007ACB0(&arc, &req, 1);
    HFree(arc.buf);
    D_801D0758_ovl_1F0A30 = 0xAA;
    D_801D075A_ovl_1F0A30 = 0x10;
    D_801D075C_ovl_1F0A30 = 0x16;
    D_801D075E_ovl_1F0A30 = 0x98;
    D_801D0760_ovl_1F0A30 = 1;
    D_801D0754_ovl_1F0A30 = req.buf;
    func_801C5CE0_ovl_1F0A30();
}

void func_801BD1F4_ovl_1F0A30(void) {
    HFree(D_801D0748_ovl_1F0A30[0]);
    HFree(D_801D074C_ovl_1F0A30);
    HFree(D_801D0750_ovl_1F0A30);
    HFree(D_801D0754_ovl_1F0A30);
    bzero(D_801D0748_ovl_1F0A30, 0x1C);
    func_801C5D64_ovl_1F0A30();
}

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BD258_ovl_1F0A30);

typedef struct {
    u8 b[0x19];
} SquadCopy1F8; /* one gSquads record */
extern SquadCopy1F8 gSquads[];

typedef struct {
    /* 0x00 */ u8 unk00[0x54];
    /* 0x54 */ s32 col;
    /* 0x58 */ s32 row;
    /* 0x5C */ u8 unk5C[0x9A];
    /* 0xF6 */ u8 id;
} Unit1F8;
Unit1F8 *func_801C8FE8_ovl_1F0A30(s32 i);
s32 func_801C8B84_ovl_1F0A30(Unit1F8 *u);
s32 func_801C8B68_ovl_1F0A30(Unit1F8 *u);
s32 func_801C8E30_ovl_1F0A30(Unit1F8 *u);

/* Copies both sides' squad records into the battle context and gives each live member its
 * formation slot (player side mirrored); members not found or dead are dropped */
void func_801BDC78_ovl_1F0A30(void) {
    SquadCopy1F8 *s;
    u32 k;
    s32 i;
    Unit1F8 *u;

    *(SquadCopy1F8 *)(D_801CE8C0_ovl_1F0A30 + 0x82F) = gSquads[D_801976DC];
    *(SquadCopy1F8 *)(D_801CE8C0_ovl_1F0A30 + 0x848) = gSquads[D_801976E8];
    s = (SquadCopy1F8 *)(D_801CE8C0_ovl_1F0A30 + 0x82F);
    for (k = 0; k < 5; k++) {
        if (s->b[k + 2] != 0) {
            for (i = 0; i < 20; i++) {
                u = func_801C8FE8_ovl_1F0A30(i);
                if (u == NULL || func_801C8B84_ovl_1F0A30(u) == 0 || u->id != s->b[k + 2]) {
                    continue;
                }
                if (func_801C8E30_ovl_1F0A30(u) != 0) {
                    s->b[k + 2] = 0;
                    continue;
                }
                s->b[k + 7] = (8 - u->row) * 3 - (u->col - 2);
                break;
            }
            if (i >= 20) {
                s->b[k + 2] = 0;
            }
        }
    }
    s = (SquadCopy1F8 *)(D_801CE8C0_ovl_1F0A30 + 0x848);
    for (k = 0; k < 5; k++) {
        if (s->b[k + 2] != 0) {
            for (i = 0; i < 20; i++) {
                u = func_801C8FE8_ovl_1F0A30(i);
                if (u == NULL || func_801C8B68_ovl_1F0A30(u) == 0 || u->id != s->b[k + 2]) {
                    continue;
                }
                if (func_801C8E30_ovl_1F0A30(u) != 0) {
                    s->b[k + 2] = 0;
                    continue;
                }
                s->b[k + 7] = u->row * 3 + u->col;
                break;
            }
            if (i >= 20) {
                s->b[k + 2] = 0;
            }
        }
    }
}

void func_801BDF40_ovl_1F0A30(void) {
    func_801BDC78_ovl_1F0A30();
    func_801C62E4_ovl_1F0A30(0, D_801CE8C0_ovl_1F0A30 + 0x82F, D_801976DC);
    func_801C62E4_ovl_1F0A30(1, D_801CE8C0_ovl_1F0A30 + 0x848, D_801976E8);
}
