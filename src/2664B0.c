#include "common.h"

/* 2664B0 */

void func_80211C10_ovl_25EE90(u8 *p);
void func_80211E80_ovl_25EE90(void *p);
void func_80212220_ovl_25EE90(u8 *p);
void func_80212558_ovl_25EE90(void *p);
typedef struct {
    u32 w0;
    u32 w1;
} Gfx;
extern Gfx *D_800E9BA0;
extern u8 *D_801969B0;
extern Gfx D_802204C0_ovl_25EE90[];
void guMtxF2L(void *mf, void *m);
typedef struct {
    /* 0x00 */ u8 unk00[0x14];
    /* 0x14 */ f32 mtx[4][4];
    /* 0x54 */ Gfx *dl;
} Model266;
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/2664B0", func_80211900_ovl_25EE90);

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
#define GFX266(w0_, w1_)               \
    {                                  \
        Gfx *_g = D_800E9BA0++;        \
                                       \
        _g->w0 = (w0_);                \
        _g->w1 = (w1_);                \
    }
typedef struct {
    s16 x;
    s16 y;
    u8 a;
    u8 pad;
} RingPt266;
extern Gfx D_80220410_ovl_25EE90[];
extern Gfx D_80220460_ovl_25EE90[];
f32 cosf(f32 x);
f32 sinf(f32 x);
void func_80211900_ovl_25EE90(Gfx *dl, RingPt266 *pts, s32 n, u16 w);

/* Draws a ring (radius 0x48, 0x4A segments, colour 0x40) under matrix p */
#ifdef NON_MATCHING
/* same length; the point counter's zeroing is scheduled before the hoisted 0.01745 constant instead of after */
void func_80211C10_ovl_25EE90(u8 *p) {
    RingPt266 pts[128];

    if (FIELD(p, s16, 0x4A) <= 128) {
        GFX266(0xDE000000, (u32)D_80220410_ovl_25EE90);
        guMtxF2L(p, D_801969B0);
        GFX266(0xDA380000, (u32)D_801969B0);
        GFX266(0xFA000000, (p[0x40] << 24) | (p[0x41] << 16) | (p[0x42] << 8) | p[0x43]);
        if (FIELD(p, u16, 0x44) == 0) {
            RingPt266 *q = pts;
            s32 n = 0;
            f32 ang = 0.0f;
            f32 r = FIELD(p, s16, 0x48);
            f32 step = 360.0f / FIELD(p, s16, 0x4A);

            do {
                f32 rad = ang * 0.017453292f;

                q->x = r * cosf(rad);
                q->y = r * sinf(rad);
                q->a = 0xFF;
                ang += step;
                n++;
                q++;
            } while (ang < 360.0f);
            func_80211900_ovl_25EE90(D_80220460_ovl_25EE90, pts, n, FIELD(p, u16, 0x46));
        }
        GFX266(0xD8380002, 0x40);
        D_801969B0 += 0x40;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/2664B0", func_80211C10_ovl_25EE90);
#endif

s32 func_80211E40_ovl_25EE90(u8 *p) {
    func_80211C10_ovl_25EE90(p + 0x18);
    return 0;
}

s32 func_80211E60_ovl_25EE90(u8 *p) {
    func_80211C10_ovl_25EE90(p + 0x14);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/2664B0", func_80211E80_ovl_25EE90);

s32 func_80212200_ovl_25EE90(u8 *p) {
    func_80211E80_ovl_25EE90(p + 0x14);
    return 0;
}

extern Gfx D_80220470_ovl_25EE90[];

/* Draws a filled disc (centre alpha 0x44, rim alpha 0x43) under matrix p */
void func_80212220_ovl_25EE90(u8 *p) {
    RingPt266 c;
    RingPt266 pts[128];

    if (FIELD(p, s16, 0x4A) <= 128) {
        RingPt266 *q = pts;

        GFX266(0xDE000000, (u32)D_80220470_ovl_25EE90);
        GFX266(0xFA000000, (p[0x40] << 24) | (p[0x41] << 16) | (p[0x42] << 8));
        guMtxF2L(p, D_801969B0);
        GFX266(0xDA380000, (u32)D_801969B0);
        {
            s32 n = 0;
            f32 ang;
            f32 r;
            f32 step;
            s32 i;

            c.y = 0;
            c.x = 0;
            ang = 0.0f;
            c.a = p[0x44];
            r = FIELD(p, s16, 0x48);
            step = 360.0f / FIELD(p, s16, 0x4A);
            do {
                f32 rad = ang * 0.017453292f;

                q->x = r * cosf(rad);
                q->y = r * sinf(rad);
                q->a = 0xFF;
                ang += step;
                n++;
                q++;
            } while (ang < 360.0f);
            {
                s32 m = n;

                for (i = 0; i < m; i++) {
                    pts[i].a = p[0x43];
                }
                func_80211900_ovl_25EE90(&c, pts, m, FIELD(p, u16, 0x46));
            }
        }
        GFX266(0xD8380002, 0x40);
        D_801969B0 += 0x40;
    }
}

s32 func_80212468_ovl_25EE90(u8 *p) {
    func_80212220_ovl_25EE90(p + 0x18);
    return 0;
}

/* Draws o's display list (0x54) under its matrix (0x14), after the shared setup list */
s32 func_80212488_ovl_25EE90(Model266 *o) {
    Gfx *g;

    g = D_800E9BA0++;
    g->w0 = 0xDE000000;
    g->w1 = (u32)D_802204C0_ovl_25EE90;
    guMtxF2L(o->mtx, D_801969B0);
    g = D_800E9BA0++;
    g->w0 = 0xDA380000;
    g->w1 = (u32)D_801969B0;
    g = D_800E9BA0++;
    g->w0 = 0xDE000000;
    g->w1 = (u32)o->dl;
    g = D_800E9BA0++;
    g->w0 = 0xD8380002;
    g->w1 = 0x40;
    D_801969B0 += 0x40;
    return 0;
}

typedef struct {
    s16 ob[3];
    u16 flag;
    s16 tc[2];
    u8 cn[4];
} Vtx266;
extern Vtx266 *D_80197178;
extern Gfx D_80220520_ovl_25EE90[];
void bzero(void *p, s32 n);

typedef struct {
    f32 mtx[4][4];
    f32 alpha;
    s16 w;
    s16 h;
    u16 type;
} Tri266;

/* Draws a flat triangle (half width 0x44, height 0x46, shape 0x48: 0 centred, 1 left-shaded,
 * 2 right) under matrix p with alpha 0x40 */
void func_80212558_ovl_25EE90(void *arg) {
    Tri266 *p = arg;
    s32 w;
    s32 h;
    s32 type;
    Vtx266 *vtx;
    s32 i;
    s32 x;
    s32 y;
    s32 c;

    GFX266(0xDE000000, (u32)D_80220520_ovl_25EE90);
    guMtxF2L(p->mtx, D_801969B0);
    GFX266(0xDA380000, (u32)D_801969B0);
    GFX266(0xFA000000, (u8)(p->alpha * 255.0f));
    w = p->w;
    h = p->h;
    vtx = D_80197178;
    c = 0xFF;
    type = p->type;
    for (i = 0; i < 3; i++) {
        if (i == 0) {
            y = 0;
        } else if (i == 1) {
            y = h;
        } else {
            y = -h;
        }
        bzero(D_80197178, 16);
        switch (type) {
        case 0:
            if (i == 0) {
                x = w;
            } else {
                x = -w;
            }
            break;
        case 1:
            if (i == 0) {
                x = 0;
                c = 0x80;
            } else {
                x = w * 2;
                c = 0;
            }
            break;
        case 2:
            x = i ? 0 : -(w * 2);
            break;
        default:
            for (;;) {
            }
        }
        D_80197178->ob[0] = y;
        D_80197178->ob[2] = x;
        FIELD(D_80197178, u8, 0xC) = 0xFF;
        FIELD(D_80197178, u8, 0xD) = c;
        FIELD(D_80197178, u8, 0xE) = c;
        FIELD(D_80197178, u8, 0xF) = 0xFF;
        D_80197178++;
    }
    GFX266(0x01003006, (u32)vtx);
    GFX266(0x05000204, 0);
    GFX266(0xD8380002, 0x40);
    D_801969B0 += 0x40;
}

s32 func_80212814_ovl_25EE90(u8 *p) {
    func_80212558_ovl_25EE90(p + 0x18);
    return 0;
}
