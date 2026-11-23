#include "common.h"

/* 275850 */

typedef struct {
    /* 0x00 */ u8 unk00[0x1C];
    /* 0x1C */ void *w1C;
    /* 0x20 */ u16 flags;
    /* 0x22 */ s16 h22;
    /* 0x24 */ s32 w24;
    /* 0x28 */ s16 h28;
} Obj27;

typedef struct {
    /* 0x0 */ u8 unk0[4];
    /* 0x4 */ s32 x;
    /* 0x8 */ s32 y;
    /* 0xC */ s32 z;
} IPos27;

typedef struct {
    f32 x, y, z;
} Vec3f;

void *func_8020C9B0(s32 a);
void func_8020C074(void *p);
typedef struct {
    u32 w0;
    u32 w1;
} Gfx;
extern Gfx *D_800E9BA0;
typedef struct {
    s32 m[16];
} Mtx40;
extern Mtx40 *D_801969B0;
extern Gfx D_80225620_ovl_275850[];
void func_80098D00(f32 mf[4][4], f32 x, f32 y, f32 z);
void guMtxF2L(f32 mf[4][4], void *m);
s32 func_802210C0_ovl_275850(u8 *o, s32 k);
void func_80221368_ovl_275850(u8 *o, s32 a);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/275850", func_802210C0_ovl_275850);

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
#define G275(a, b)                   \
    {                                \
        Gfx *_g = D_800E9BA0++;      \
                                     \
        _g->w0 = (a);                \
        _g->w1 = (b);                \
    }

/* Loads o's 32x32 texture (o+4) with its alpha (o+0x11) and draws its quads from vertex block a,
 * four vertices at a time (o+0xA quads) */
#ifdef NON_MATCHING
/* 104/104 instructions, 22 words differ: the first command's word is stored before D_800E9BA0 advances in the original, and the final pointer store is sunk below the quad count load */
void func_80221368_ovl_275850(u8 *o, s32 a) {
    s16 i;

    if (FIELD(o, u32, 4) != 0) {
        G275(0xFD180000, FIELD(o, u32, 4));
        G275(0xF5180000, 0x07000000);
        G275(0xE6000000, 0);
        G275(0xF3000000, 0x0717F100);
        G275(0xE7000000, 0);
        G275(0xF5180800, 0);
        G275(0xF2000000, 0x3C05C);
        G275(0xFA000000, o[0x11] | ~0xFF);
        G275(0xE6000000, 0);
        for (i = 0; i < FIELD(o, s16, 0xA) * 4; i += 4) {
            G275(0x01004008, a + (i << 4));
            G275(0x06000204, 0x406);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/275850", func_80221368_ovl_275850);
#endif

/* Draws the two parts of o under an untranslated matrix, after the setup list */
inline void func_80221508_ovl_275850(u8 *o) {
    f32 m[4][4];
    Gfx *g;

    func_80098D00(m, 0.0f, 0.0f, 0.0f);
    guMtxF2L(m, D_801969B0);
    g = D_800E9BA0++;
    g->w0 = 0xDA380000;
    g->w1 = (u32)D_801969B0++;
    g = D_800E9BA0++;
    g->w0 = 0xDE000000;
    g->w1 = (u32)D_80225620_ovl_275850;
    func_80221368_ovl_275850(o, func_802210C0_ovl_275850(o, 0));
    func_80221368_ovl_275850(o, func_802210C0_ovl_275850(o, 1));
    g = D_800E9BA0++;
    g->w0 = 0xD8380002;
    g->w1 = 0x40;
}

void func_802215FC_ovl_275850(Obj27 *o, s32 v) {
    if (o->w24 == 0) {
        o->w24 = v;
    }
}

void func_80221610_ovl_275850(Obj27 *o, f32 v) {
    o->h28 = v;
}

void func_8022162C_ovl_275850(Obj27 *o, s16 v) {
    o->h22 = v;
}

/* Integer map position (x30 + 9000) of whichever point has the smaller x */
void func_80221634_ovl_275850(IPos27 *out, Vec3f *a, Vec3f *b) {
    if (a->x < b->x) {
        b = a;
    }
    out->x = b->x * 30.0f + 9000.0f;
    out->y = b->y * 30.0f + 9000.0f;
    out->z = b->z * 30.0f + 9000.0f;
}

void func_802216AC_ovl_275850(Obj27 *o) {
    o->flags |= 1;
}

void func_802216BC_ovl_275850(Obj27 *o) {
    o->flags &= ~1;
}

s32 func_802216CC_ovl_275850(Obj27 *o) {
    return o->flags & 1;
}

void func_802216D8_ovl_275850(Obj27 *o) {
    o->h28 = 0;
    o->w1C = NULL;
    o->w24 = 0;
    o->h22 = 0;
    o->flags ^= o->flags;
    o->w1C = func_8020C9B0(4);
}

void func_80221720_ovl_275850(Obj27 *o) {
    if (o->w1C != NULL) {
        func_8020C074(o->w1C);
    }
}

void func_80221748_ovl_275850(void) {
}

/* Draws object o's model (at o + 0x18) when flag 1 is set */
s32 func_80221750_ovl_275850(Obj27 *o) {
    u8 *m = (u8 *)o + 0x18;

    if (!(o->flags & 1)) {
        return 0;
    }
    func_80221508_ovl_275850(m);
    return 0;
}
