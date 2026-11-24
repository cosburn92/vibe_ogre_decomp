#include "common.h"

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))

/* 29A4C0 */

typedef struct {
    /* 0x0 */ void *data;
    /* 0x4 */ s16 h4;
} Grid29;

/* Colour fade of a unit: from -> to over h8 frames (hA counts up); h6 = also set the env colour */
typedef struct {
    /* 0x0 */ u8 from[3];
    /* 0x3 */ u8 to[3];
    /* 0x6 */ s16 h6;
    /* 0x8 */ s16 h8;
    /* 0xA */ s16 hA;
} Pair29;

typedef struct {
    /* 0x0000 */ u8 unk0000[0x168];
    /* 0x0168 */ void *p168[0x38];
    /* 0x0248 */ Pair29 *p248[0x5BF];
    /* 0x1944 */ void *p1944[0x1C];
    /* 0x19B4 */ u8 unk19B4[0x94];
    /* 0x1A48 */ Grid29 *grid;
    /* 0x1A4C */ u8 unk1A4C[0x168];
    /* 0x1BB4 */ void *p1BB4[20];
} Battle29;

extern Battle29 *D_8022A974;
extern s8 D_801CFC70;
extern u8 D_801D082C;

void *HMalloc(s32 size);
void *HFree(void *p);
void func_8022BB58_ovl_29A4C0(s32 a, s32 b);
void func_801C22E8(s32 a);
#define FLD(p, T, off) (*(T *)((u8 *)(p) + (off)))
s32 func_801BEA0C(s32 fmt, s32 w);
u16 func_801BEB28(u16 c);
u32 func_801BEA70(u32 c);
extern u8 D_8018FC19;
extern f32 D_8022A720;
extern f32 D_8022A734;
extern f32 D_8022A738;
extern f32 D_8022A73C;
extern f32 D_8022A740;
extern f32 D_8022A744;
extern f32 D_8022A748;
extern f32 D_801D0700;
extern f32 D_801D0704;
extern f32 D_801D0710;
extern f32 D_801D0720;
extern f32 D_801D072C;
extern f32 D_801D0730;
extern f32 D_801D083C;
/* --- end decls --- */

/* Camera setup from 7 fixed-point values (x1000); in mode 2 also mirrored into the second camera */
void func_8022AC90_ovl_29A4C0(s32 *in) {
    f32 v[7];
    s32 i;

    for (i = 0; i < 7; i++) {
        v[i] = *in++ / 1000.0f;
    }
    D_8022A740 = v[0];
    D_8022A744 = v[1];
    D_8022A748 = v[2];
    D_8022A734 = v[3];
    D_8022A738 = v[4];
    D_8022A73C = v[5];
    D_8022A720 = v[6];
    if (D_8018FC19 == 2) {
        D_801D0710 = v[6];
        D_801D0720 = v[3];
        D_801D072C = v[4];
        D_801D0704 = v[5];
        D_801D0730 = v[0];
        D_801D083C = v[1];
        D_801D0700 = v[2];
    }
}

typedef struct {
    s16 period;
    s16 count;
    s16 total;
    s16 pad;
    f32 delta;
} Drift29;

/* Starts unit i drifting toward target over total frames (period -1: every frame); a drift that
 * would move less than 0.01 is dropped */
void func_8022AD6C_ovl_29A4C0(s32 i, s32 period, s32 target, s32 total) {
    Drift29 *d;
    f32 diff;

    d = FLD(D_8022A974, Drift29 *, 0x1A50 + i * 4);
    if (d == NULL) {
        FLD(D_8022A974, Drift29 *, 0x1A50 + i * 4) = HMalloc(0xC);
    }
    d = FLD(D_8022A974, Drift29 *, 0x1A50 + i * 4);
    d->period = period;
    d->count = 0;
    d->total = total;
    d->delta = target;
    if (d->period == -1) {
        diff = d->delta - FLD(FLD(D_8022A974, u8 *, 0x18 + i * 4), f32, 0x120);
        if (diff >= 0.01 || diff <= -0.01) {
            d->delta = diff / total;
        } else {
            HFree(d);
            FLD(D_8022A974, Drift29 *, 0x1A50 + i * 4) = NULL;
        }
    }
}

/* Periodic drift: every `period` ticks (or each tick when -1) add delta to x/z, `total` ticks */

void func_8022AE84_ovl_29A4C0(void) {
    s32 i;
    Drift29 *d;
    u8 *u;

    for (i = 0; i < 0x1C; i++) {
        d = FLD(D_8022A974, Drift29 *, 0x1A50 + i * 4);
        if (d == NULL) {
            continue;
        }
        if (++d->count == d->total) {
            HFree(d);
            FLD(D_8022A974, Drift29 *, 0x1A50 + i * 4) = NULL;
        } else {
            u = FLD(D_8022A974, u8 *, 0x18 + i * 4);
            if (d->period == -1 || d->period - 1 == d->count % d->period) {
                FLD(u, f32, 0x120) += d->delta;
                if (!(u[0x145] & 4)) {
                    FLD(u, f32, 0x128) += d->delta;
                }
            }
        }
    }
}

void func_8022EFB0_ovl_29A4C0(u8 *e);
s16 func_80231BBC_ovl_29A4C0(s32 a, s16 b, s32 c, s32 d);
void *memset(void *p, s32 c, s32 n);
void func_8022FDB8_ovl_29A4C0();

/* Creates the 0x50-byte effect object of unit i (replacing any old one) and registers it */
s32 func_8022AF94_ovl_29A4C0(u8 i, s32 kind, s32 sub, s32 mode, s32 x, s32 y, s32 layer, s32 time, s32 flags) {
    u8 *e;

    if (FLD(D_8022A974, u8 *, 0x1AC0 + i * 4) != NULL) {
        HFree(FLD(D_8022A974, u8 *, 0x1AC0 + i * 4));
    }
    e = HMalloc(0x50);
    FLD(D_8022A974, u8 *, 0x1AC0 + i * 4) = e;
    e[0x4A] = layer;
    FLD(e, s32, 0x2C) = i;
    if (kind != -1) {
        FLD(e, s32, 0x30) = kind;
    }
    if (sub != -1) {
        FLD(e, s16, 0x44) = sub;
    }
    FLD(e, s16, 0x42) = func_80231BBC_ovl_29A4C0(FLD(e, s32, 0x30), FLD(e, s16, 0x44), mode, 0);
    FLD(e, s32, 0x34) = -1;
    FLD(e, s32, 0x38) = 0;
    FLD(e, s32, 0x3C) = 0;
    if ((x != -1) | (y != -1)) {
        FLD(e, s32, 0x24) = x;
        FLD(e, s32, 0x28) = -y;
    }
    FLD(e, void *, 0x20) = func_8022FDB8_ovl_29A4C0;
    e[0x4B] = mode;
    FLD(e, s16, 0x46) = 0;
    FLD(e, s16, 0x40) = 180;
    FLD(e, u16, 0x48) = time;
    e[0x4C] = flags;
    memset(e, 0xFF, 0x10);
    bzero(e + 0x10, 0x10);
    func_8022EFB0_ovl_29A4C0(e);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022B100_ovl_29A4C0);

void func_8022B414_ovl_29A4C0(s32 i) {
    s32 k;
    s32 end;

    if (i == -1) {
        i = 0;
        end = 30;
    } else {
        end = i + 1;
    }
    for (k = i; k < end; k++) {
        if (FLD(D_8022A974, void *, 0x1AC0 + k * 4) != NULL) {
            HFree(FLD(D_8022A974, void *, 0x1AC0 + k * 4));
            FLD(D_8022A974, void *, 0x1AC0 + k * 4) = NULL;
        }
    }
}

/* Sepia-filters an image in place (fmt 2: RGBA5551, fmt 3: RGBA8888) */
void func_8022B4A8_ovl_29A4C0(void *pix, s32 fmt, s32 h, s32 w) {
    s32 n = func_801BEA0C(fmt, w) * h;
    s32 i;

    if (fmt == 2) {
        u16 *p = pix;

        for (i = 0; i < n; i++, p++) {
            *p = func_801BEB28(*p);
        }
    } else if (fmt == 3) {
        u32 *p = pix;

        for (i = 0; i < n; i++, p++) {
            *p = func_801BEA70(*p);
        }
    }
}

/* inlined copy of func_8022B4A8 (n computed in two statements) */
static inline void SepiaImg29(void *pix, s32 fmt, s32 h, s32 w) {
    s32 n;
    s32 i;

    n = func_801BEA0C(fmt, w);
    n *= h;

    if (fmt == 2) {
        u16 *p = pix;

        for (i = 0; i < n; i++, p++) {
            *p = func_801BEB28(*p);
        }
    } else if (fmt == 3) {
        u32 *p = pix;

        for (i = 0; i < n; i++, p++) {
            *p = func_801BEA70(*p);
        }
    }
}

/* Sepia-filters every RGBA5551 image in a sprite bank */
void func_8022B56C_ovl_29A4C0(u8 *bank) {
    u8 *e = bank + 8;
    s32 k;

    for (k = 0; k < bank[3]; k++) {
        u8 *hdr = e;

        SepiaImg29(hdr + 0x10, 2, FIELD(hdr, u16, 6), FIELD(hdr, u16, 4));
        e = FIELD(hdr, u8 *, 0xC);
    }
}

/* Sepia-filters a single image (8-byte header: [3] fmt, u16 width at 4, height at 6) */
void func_8022B62C_ovl_29A4C0(u8 *img) {
    u8 *hdr = img;

    img += 8;
    SepiaImg29(img, hdr[3], FIELD(hdr, u16, 6), FIELD(hdr, u16, 4));
}

/* inlined copy of func_8022B56C */
static inline void SepiaBank29(u8 *bank) {
    u8 *e = bank + 8;
    s32 k;

    for (k = 0; k < bank[3]; k++) {
        u8 *hdr = e;

        SepiaImg29(hdr + 0x10, 2, FIELD(hdr, u16, 6), FIELD(hdr, u16, 4));
        e = FIELD(hdr, u8 *, 0xC);
    }
}

/* inlined copy of func_8022B62C */
static inline void SepiaOne29(u8 *img) {
    u8 *hdr = img;

    img += 8;
    SepiaImg29(img, hdr[3], FIELD(hdr, u16, 6), FIELD(hdr, u16, 4));
}

extern u8 *D_801D0770;
extern u8 *volatile D_801D07A0;
void func_801C45E0(void);
void func_801C22D0(s32 a);
void func_8022BD74_ovl_29A4C0(void);

#define IMG29(k) FLD(D_8022A974, u8 *, 0x1C04 + (k) * 4)

/* Sepia-filters the backdrop (a "64" single image or a sprite bank) and the overlay bank, or
 * outside mode 2 the 20 battle images ("64"/"74" single images, else banks); then redraws */
void func_8022B6F4_ovl_29A4C0(void) {
    s32 k;

    if (D_8018FC19 == 2) {
        if (D_801D0770[0] == 0x36 && D_801D0770[1] == 0x34) {
            SepiaOne29(D_801D0770);
        } else {
            SepiaBank29(D_801D0770);
        }
        if (D_801D07A0 != NULL) {
            SepiaBank29(D_801D07A0);
        }
    } else {
        for (k = 0; k < 20; k++) {
            if (IMG29(k) != NULL) {
                if (IMG29(k)[0] == 0x36 && IMG29(k)[1] == 0x34) {
                    SepiaOne29(IMG29(k));
                }
                if (IMG29(k)[0] == 0x37 && IMG29(k)[1] == 0x34) {
                    SepiaOne29(IMG29(k));
                } else {
                    SepiaBank29(IMG29(k));
                }
            }
        }
    }
    func_801C45E0();
    func_801C22D0(1);
    func_8022BD74_ovl_29A4C0();
}

typedef struct {
    s16 x[4];
    s16 y[4];
} Quad29;

typedef struct {
    u16 h[8];
} Vtx29;

void func_8022DC38_ovl_29A4C0(Vtx29 *p, s16 a, s16 b, s32 c);

/* Grid line vertices: for each corner (+-a, +-b) of the w x h box, a line from the midpoint of the
 * corner (offset 10) to the matching half-screen corner, then a closing line back to the first */
void func_8022BB58_ovl_29A4C0(s32 a, s32 b) {
    Vtx29 *v;
    s32 i;
    s32 j;
    Quad29 p;
    Quad29 first;
    Quad29 c;

    v = HMalloc(0x3A0);
    D_8022A974->grid->data = v;
    c.x[0] = -a;
    c.x[1] = -a;
    c.x[2] = a;
    c.x[3] = a;
    c.y[0] = b;
    c.y[1] = -b;
    c.y[2] = -b;
    c.y[3] = b;
    for (i = 0; i < 4; i++) {
        p.x[1] = 0x140;
        p.y[1] = 0xD8;
        switch (i) {
            case 0:
                p.x[1] = -0x140;
                break;
            case 1:
                p.x[1] = -0x140;
                p.y[1] = -0xD8;
                break;
            case 2:
                p.y[1] = -0xD8;
                break;
        }
        p.x[1] /= 2;
        p.y[1] /= 2;
        for (j = 0; j < 1; j++) {
            p.x[0] = c.x[i] + 10;
            p.y[0] = c.y[i] + 10;
            p.x[0] /= 2;
            p.y[0] /= 2;
            func_8022DC38_ovl_29A4C0(v++, p.x[0], p.y[0], 10);
            func_8022DC38_ovl_29A4C0(v++, p.x[1], p.y[1], 200);
            if (j == 0 && i == 0) {
                first.x[0] = p.x[0];
                first.x[1] = p.x[1];
                first.y[0] = p.y[0];
                first.y[1] = p.y[1];
            }
        }
    }
    func_8022DC38_ovl_29A4C0(v++, first.x[0], first.y[0], 10);
    func_8022DC38_ovl_29A4C0(v++, first.x[1], first.y[1], 200);
}

void func_8022BD74_ovl_29A4C0(void) {
    Grid29 *g;

    if (D_8022A974->grid != NULL) {
        HFree(D_8022A974->grid->data);
        HFree(D_8022A974->grid);
    }
    g = HMalloc(8);
    D_8022A974->grid = g;
    g->h4 = -1;
    func_8022BB58_ovl_29A4C0(0xA0, 0x78);
}

void func_8022BDDC_ovl_29A4C0(void) {
    if (D_8022A974->grid != NULL) {
        HFree(D_8022A974->grid->data);
        HFree(D_8022A974->grid);
        D_8022A974->grid = NULL;
        func_801C22E8(1);
    }
}

typedef struct {
    u32 w0;
    u32 w1;
} Gfx29;
extern Gfx29 *D_800E9BA0;
extern s32 D_80197178; /* frame vertex pool cursor */
extern u8 D_8022AB48[];
void func_80080998(s32 dst, void *src, s32 n);

/* Draws the battle grid overlay: copies its 0x3A0 bytes of vertices into the frame's vertex
 * pool (D_80197178) and emits four quad strips plus the border */
void func_8022BE30_ovl_29A4C0(void) {
    Grid29 *g = D_8022A974->grid;
    s32 v;
    s32 i;

    if (g == NULL) {
        return;
    }
    func_80080998(D_80197178, g->data, 0x3A0);
    v = D_80197178;
    {
        Gfx29 *_g = D_800E9BA0++;

        _g->w0 = 0xDE000000;
        _g->w1 = (u32)D_8022AB48;
    }
    for (i = 0; i < 4; i++) {
        {
            Gfx29 *_g = D_800E9BA0++;

            _g->w0 = 0x01004008;
            _g->w1 = v;
        }
        v += 0x20;
        {
            Gfx29 *_g = D_800E9BA0++;

            _g->w0 = 0x06000206;
            _g->w1 = 0x604;
        }
    }
    v = D_80197178;
    {
        Gfx29 *_g = D_800E9BA0++;

        _g->w0 = 0x01008010;
        _g->w1 = v;
    }
    {
        Gfx29 *_g = D_800E9BA0++;

        _g->w0 = 0x06000408;
        _g->w1 = 0x80C;
    }
    {
        Gfx29 *_g = D_800E9BA0++;

        _g->w0 = 0xE7000000;
        _g->w1 = 0;
    }
    D_80197178 += 0x3A0;
}

void func_8022BF5C_ovl_29A4C0(s32 *a) {
    s16 i = FLD(a, s16, 2);
    u8 *p;

    if (D_8022A974->p1944[i] != NULL) {
        HFree(D_8022A974->p1944[i]);
    }
    p = HMalloc(7);
    D_8022A974->p1944[i] = p;
    p[0] = a[7];
    p[1] = a[1];
    p[2] = a[2];
    p[3] = a[3];
    p[4] = a[4];
    p[5] = a[5];
    p[6] = a[6];
}

void func_8022BFFC_ovl_29A4C0(void) {
    s32 i;

    for (i = 0; i < 0x1C; i++) {
        if (D_8022A974->p1944[i] != NULL) {
            HFree(D_8022A974->p1944[i]);
        }
    }
}

typedef struct {
    /* 0x0 */ u8 kind;
    /* 0x1 */ u8 r;
    /* 0x2 */ u8 g;
    /* 0x3 */ u8 b;
    /* 0x4 */ u8 c[3];
} Tint29;

#define G29(a, b)                    \
    {                                \
        Gfx29 *_g = D_800E9BA0++;    \
                                     \
        _g->w0 = (a);                \
        _g->w1 = (b);                \
    }

/* Sets up the tinted combiner for unit u from its tint record (u+0xE7), and copies the tint's
 * colour to u+0x142 */
void func_8022C04C_ovl_29A4C0(u8 *u) {
    Tint29 *p = D_8022A974->p1944[u[0xE7]];

    if (p != NULL) {
        Tint29 *t = p;

        G29(0xE7000000, 0);
        G29(0xE7000000, 0);
        G29(0xE3000A01, 0x100000);
        G29(0xE7000000, 0);
        if (t->kind == 1) {
            G29(0xE200001C, 0x104240);
            {
                Gfx29 *_g = D_800E9BA0++;

                ((u32 *)_g)[0] = 0xFC629603;
                ((u32 *)_g)[1] = 0x2F2D7BFD;
            }
        } else {
            G29(0xE200001C, 0x104240);
            {
                Gfx29 *_g = D_800E9BA0++;

                ((u32 *)_g)[0] = 0xFC2296C3;
                ((u32 *)_g)[1] = 0xF22FFA3D;
            }
        }
        G29(0xFB000000, (t->r << 24) | (t->g << 16) | (t->b << 8) | 1);
        u[0x142] = t->c[0];
        u[0x143] = t->c[1];
        u[0x144] = t->c[2];
    }
}

void func_8022C1B0_ovl_29A4C0(s32 i) {
    if (D_8022A974->p1944[i] != NULL) {
        HFree(D_8022A974->p1944[i]);
        D_8022A974->p1944[i] = NULL;
    }
}

/* RGBA5551 to RGBA8888 */
u32 func_8022C200_ovl_29A4C0(u32 c) {
    return ((c & 0xF800) << 16) | ((c & 0x7C0) << 13) | ((c & 0x3E) << 10) | 0xFF;
}

/* RGBA8888 to RGBA5551 */
u32 func_8022C228_ovl_29A4C0(u32 c) {
    return ((c >> 16) & 0xF800) | ((c >> 13) & 0x7C0) | ((c & 0xF800) >> 10) | 1;
}

/* (Re)creates the tint record of unit i (all present units when i is -1): colour, alpha range,
 * duration and timer */
void func_8022C250_ovl_29A4C0(s32 i, s32 r, s32 g, s32 b, s32 a0, s32 a1, s32 a2, s32 dur, s32 time) {
    s16 j;
    s16 end;
    u8 *rec;

    j = 0;
    end = 0x1C;
    if (i != -1) {
        j = i;
        end = i + 1;
    }
    for (; j < end; j++) {
        if (FLD(D_8022A974, u8 *, 0x248 + j * 4) != NULL) {
            HFree(FLD(D_8022A974, u8 *, 0x248 + j * 4));
        }
        if (i != -1 || FLD(D_8022A974, u8 *, 0x18 + j * 4) != NULL) {
            rec = HMalloc(0xC);
            FLD(D_8022A974, u8 *, 0x248 + j * 4) = rec;
            rec[0] = r;
            rec[1] = g;
            rec[2] = b;
            rec[3] = a0;
            rec[4] = a1;
            rec[5] = a2;
            FLD(rec, u16, 8) = dur;
            FLD(rec, s16, 0xA) = 0;
            FLD(rec, s16, 6) = time;
        }
    }
}

/* Steps unit u's colour fade and writes the colour to u + 0x142 (and the env colour) */
#ifdef NON_MATCHING
/* 123/123 instructions, 18 words differ: the pipe-sync and fade pointer loads are scheduled differently and the loop counters use other registers */
void func_8022C3A8_ovl_29A4C0(u8 *u) {
    Pair29 *p;
    s16 c[3];
    s16 i;

    D_800E9BA0->w0 = 0xE7000000;
    D_800E9BA0->w1 = 0;
    D_800E9BA0++;
    p = D_8022A974->p248[FIELD(u, s32, 0xE4)];
    if (p != NULL) {
        Pair29 *q = p;

        if (q->hA >= q->h8) {
            q->hA = q->h8;
            for (i = 0; i < 3; i++) {
                c[i] = q->to[i];
            }
        } else {
            q->hA++;
            for (i = 0; i < 3; i++) {
                c[i] = q->to[i] - q->from[i];
                c[i] = q->from[i] + (s32)((f32)q->hA / (f32)q->h8 * c[i]);
            }
        }
        if (q->h6 != 0) {
            {
                Gfx29 *_g = D_800E9BA0++;

                _g->w0 = 0xFC62FEC3;
                _g->w1 = 0x200D723D;
            }
            {
                Gfx29 *_g = D_800E9BA0++;

                _g->w0 = 0xFB000000;
                _g->w1 = ((u8)c[0] << 24) | ((u8)c[1] << 16) | ((u8)c[2] << 8) | 1;
            }
        }
        for (i = 0; i < 3; i++) {
            (u + i)[0x142] = c[i];
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022C3A8_ovl_29A4C0);
#endif

s32 func_8022C594_ovl_29A4C0(s32 i) {
    Pair29 *p = D_8022A974->p248[i];
    s32 r = 0;

    if (p != NULL) {
        r = p->hA != p->h8;
    }
    return r;
}

/* Frees the 0x248 buffer of unit slot i (all 30 when i is -1) and resets the unit's three 0x142 bytes */
#ifdef NON_MATCHING
/* The logic matches. The original sets k through a temporary (v0 then s2) and keeps k*4 in s0 across the HFree call, using one more saved register. */
void func_8022C5C8_ovl_29A4C0(s32 i) {
    s16 k;
    s16 end;
    s16 j;
    u8 *u;

    if (i == -1) {
        k = 0;
        end = 30;
    } else {
        k = i;
        end = i + 1;
    }
    for (; k < end; k++) {
        HFree(D_8022A974->p248[k]);
        u = FLD(D_8022A974, u8 *, 0x18 + k * 4);
        D_8022A974->p248[k] = NULL;
        if (u != NULL) {
            for (j = 0; j < 3; j++) {
                u[0x142 + j] = 0xFF;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022C5C8_ovl_29A4C0);
#endif

extern u8 D_802394F0_ovl_29A4C0[];
extern u8 D_802394FC_ovl_29A4C0[];
extern u8 *D_801CE8BC;
extern s8 D_800E9C0A[];
extern f32 D_8022A778;
extern f32 D_8022A78C;
extern f32 D_8022A790;
extern f32 D_8022A794;
extern f32 D_8022A798;
extern f32 D_8022A79C;
extern f32 D_8022A7A0;
s8 func_8020B150(s16 id, u8 *idx, u8 *o);
void func_8020B0E4(s16 id, u8 *a, u8 *b, s32 c);

/* Starts battle message id for the objects in slots[0..3]: each one's message unit is placed at
 * the object (offset by the current camera when not in mode 1), the camera parameters are
 * restored and the message runs with sound byte 8 forced on */
#ifdef NON_MATCHING
/* 170/170, 157 words: the original keeps 0xFF in s4 across the loop (one more saved register) and tests the unit byte without re-masking */
void func_8022C6C4_ovl_29A4C0(s16 id, s32 *slots) {
    u8 idx[4];
    u8 *cam;
    u32 i;
    s32 k;
    u8 save;

    memset(D_802394F0_ovl_29A4C0, -1, 0xC);
    memset(D_802394FC_ovl_29A4C0, -1, 0xC);
    memset(idx, -1, 4);
    cam = NULL;
    if (D_8018FC19 == 0) {
        cam = FLD(D_8022A974, u8 *, FLD(D_8022A974, u8, 0x1CB0) * 4 + 0x1C54);
    }
    for (i = 0; i < 28; i++) {
        u8 *o = FLD(D_8022A974, u8 *, i * 4 + 0x18);

        if (o == NULL) {
            continue;
        }
        for (k = 0; k < 4; k++) {
            if (i == slots[k]) {
                u8 *u;

                if (o[0x147] != 0xFF) {
                    idx[k] = o[0x147];
                } else {
                    idx[k] = i;
                    o[0x147] = i;
                }
                u = D_801CE8BC + 0x1C4 + o[0x147] * 0xF8;
                FLD(u, s32, 0x48) = 0x101;
                FLD(u, s32, 0x5C) = FLD(o, f32, 0x11C);
                FLD(u, s32, 0x60) = FLD(o, f32, 0x120);
                FLD(u, s32, 0x64) = FLD(o, f32, 0x124);
                if (D_8018FC19 == 0) {
                    FLD(u, s32, 0x5C) = FLD(u, s32, 0x5C) + FLD(cam, f32, 0x40);
                    FLD(u, s32, 0x64) = FLD(u, s32, 0x64) + FLD(cam, f32, 0x44);
                }
                u[0x33] = func_8020B150(id, &idx[k], o);
                break;
            }
        }
    }
    if (D_8018FC19 == 0) {
        D_801D0710 = D_8022A778;
        D_801D0720 = D_8022A78C;
        D_801D072C = D_8022A790;
        D_801D0704 = D_8022A794;
        D_801D0730 = D_8022A798;
        D_801D083C = D_8022A79C;
        D_801D0700 = D_8022A7A0;
    }
    save = D_800E9C0A[8];
    D_800E9C0A[8] = 1;
    D_802394F0_ovl_29A4C0[0] = idx[0];
    D_802394F0_ovl_29A4C0[1] = idx[1];
    D_802394FC_ovl_29A4C0[0] = idx[2];
    D_802394FC_ovl_29A4C0[1] = idx[3];
    func_8020B0E4(id, D_802394F0_ovl_29A4C0, D_802394FC_ovl_29A4C0, 0);
    D_801CFC70 = 1;
    D_800E9C0A[8] = save;
}
#else
INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022C6C4_ovl_29A4C0);
#endif

s32 func_8022C96C_ovl_29A4C0(void) {
    if (D_801CFC70 < 0) {
        return 1;
    }
    return D_801CFC70;
}

/* Colour fade slot (D_8022A974->p1BB4[i]) */
typedef struct {
    /* 0x0 */ s16 total;
    /* 0x2 */ s16 t;
    /* 0x4 */ u8 cur[3];
    /* 0x7 */ u8 from[3];
    /* 0xA */ u8 to[3];
} Fade29;

extern u8 D_801D0828;
extern u8 D_801D0829;
extern u8 D_801D082A;
extern u8 D_801D082B;
extern u8 D_801D082C;

/* (Re)creates unit k's tint record: colour a (bytes 4-9 twice) to b (10-12) over n frames */
static inline void SetTint29(u32 k, s32 *a, s32 *b, s16 n) {
    s32 i;

    if (D_8022A974->p1BB4[k] != NULL) {
        HFree(D_8022A974->p1BB4[k]);
    }
    D_8022A974->p1BB4[k] = HMalloc(0x50);
    for (i = 0; i < 3; i++) {
        ((Fade29 *)D_8022A974->p1BB4[k])->cur[i] = a[i];
        ((Fade29 *)D_8022A974->p1BB4[k])->from[i] = a[i];
        ((Fade29 *)D_8022A974->p1BB4[k])->to[i] = b[i];
    }
    ((Fade29 *)D_8022A974->p1BB4[k])->total = n;
    ((Fade29 *)D_8022A974->p1BB4[k])->t = 0;
}

/* Sets the tint of unit k (all 20 when k is -1) and the global tint colour */
#ifdef NON_MATCHING
/* 147/147 instructions, 12 words differ: the original keeps the global tint stores and the colour loads in source order */
void func_8022C988_ovl_29A4C0(s32 *a, s32 *b, s16 n, s32 k) {
    u32 j;

    if (k == -1) {
        for (j = 0; j < 20; j++) {
            SetTint29(j, a, b, n);
        }
    } else {
        SetTint29(k, a, b, n);
    }
    D_801D082C = 0x5F;
    D_801D0828 = a[0];
    D_801D0829 = a[1];
    D_801D082B = 0xFF;
    D_801D082A = a[2];
}
#else
INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022C988_ovl_29A4C0);
#endif

extern u8 D_801D0828;
extern u8 D_801D0829;
extern u8 D_801D082A;

/* Steps the 20 colour fades; slot 0 also drives the global tint D_801D0828..A */
void func_8022CBD4_ovl_29A4C0(void) {
    u32 i;
    s32 k;
    Fade29 *f;
    void *p;

    for (i = 0; i < 20; i++) {
        p = D_8022A974->p1BB4[i];
        if (p == NULL) {
            continue;
        }
        f = p;
        if (f->t == f->total) {
            for (k = 0; k < 3; k++) {
                f->cur[k] = f->to[k];
            }
        } else if (f->t < f->total) {
            f->t++;
            for (k = 0; k < 3; k++) {
                f->cur[k] = f->from[k] - (f->from[k] - f->to[k]) * f->t / f->total;
            }
        }
    }
    p = D_8022A974->p1BB4[0];
    if (p != NULL) {
        f = p;
        D_801D0828 = f->cur[0];
        D_801D0829 = f->cur[1];
        D_801D082A = f->cur[2];
    }
}

void func_8022CD00_ovl_29A4C0(void) {
    u32 i;

    for (i = 0; i < 20; i++) {
        if (D_8022A974->p1BB4[i] != NULL) {
            HFree(D_8022A974->p1BB4[i]);
            D_8022A974->p1BB4[i] = NULL;
        }
    }
    D_801D082C = 0;
}

void func_8022CD70_ovl_29A4C0(s32 i, s32 v) {
    s32 end;
    u8 *u;

    if (i == -1) {
        i = 0;
        end = 28;
    } else {
        end = i + 1;
    }
    for (; i < end; i++) {
        u = FLD(D_8022A974, u8 *, 0x18 + i * 4);
        if (u != NULL) {
            if (v != -1) {
                FLD(u, f32, 0x120) = v;
            }
            FLD(u, s32, 0x128) = 0;
            u[0x145] = (u[0x145] & ~1) | 4;
        }
    }
}

/* small s16 tables (shared rodata splat leaves unmigrated) */
__asm__(".section .rodata\n.global D_80239190_ovl_29A4C0\nD_80239190_ovl_29A4C0:\n.half 0, 9, 6, 3\n.global D_80239198_ovl_29A4C0\nD_80239198_ovl_29A4C0:\n.half 0, 9, 8, 3, 7, 7, 2, 6, 5, 1, 4, 4\n.section .text\n");

typedef struct {
    s16 v[4];
} Dirs29A;
extern Dirs29A D_80239190_ovl_29A4C0;

/* Starts turning unit i from facing a to facing b (clock positions 0/9/6/3) in direction -dir:
 * record {start, steps, frames per step for n frames, 0, direction} */
#ifdef NON_MATCHING
/* 91/91: the frame count and the turn direction swap s4/s5 */
void func_8022CDF4_ovl_29A4C0(s32 i, s32 a, s32 b, s32 dir, s32 n) {
    Dirs29A tab = D_80239190_ovl_29A4C0;
    s32 sd = -dir;
    s16 *e;
    s16 *t = tab.v;
    s32 d;

    if (D_8022A974->p168[i] == NULL) {
        D_8022A974->p168[i] = HMalloc(10);
    }
    e = D_8022A974->p168[i];
    if (sd == 1) {
        d = t[b] - t[a];
    } else {
        d = t[a] - t[b];
    }
    if (d < 0) {
        d += 12;
    }
    e[1] = d;
    e[4] = sd;
    e[0] = tab.v[a];
    e[3] = 0;
    e[2] = n / 3 * 3 / d;
}
#else
INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022CDF4_ovl_29A4C0);
#endif

typedef struct {
    s16 v[12];
} Steps29A;
extern Steps29A D_80239198_ovl_29A4C0;
void func_80231090_ovl_29A4C0(u32 i, s32 a, s32 b, s16 c, f32 x, f32 y, f32 z, s32 d, s32 e);

/* Steps the 28 cycling effects: each time its timer runs out, advances the phase (mod 12),
 * re-applies the phase's value and frees the effect after its last cycle */
void func_8022CF60_ovl_29A4C0(void) {
    Steps29A tab = D_80239198_ovl_29A4C0;
    u32 i;
    s16 *o;
    s16 v;

    for (i = 0; i < 28; i++) {
        o = FIELD(D_8022A974, s16 *, 0x168 + i * 4);
        if (o == NULL) {
            continue;
        }
        if (o[3] == 0) {
            o[1]--;
            o[3] = o[2];
            o[0] = v = o[0] + o[4];
            if (v < 0) {
                o[0] = v + 12;
            } else if (v >= 12) {
                o[0] = v - 12;
            }
            func_80231090_ovl_29A4C0(i, -1, -1, tab.v[o[0]], -1.0f, -1.0f, -1.0f, -1, 1);
            if (o[1] == 0) {
                HFree(o);
                o = NULL;
                FIELD(D_8022A974, s32, 0x168 + i * 4) = 0;
            }
        }
        if (o != NULL) {
            o[3]--;
        }
    }
}

s32 func_8022D0FC_ovl_29A4C0(s32 i) {
    return D_8022A974->p168[i] != NULL;
}
