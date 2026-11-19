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

INCLUDE_ASM("asm/nonmatchings/275850", func_80221368_ovl_275850);

/* Draws the two parts of o under an untranslated matrix, after the setup list */
void func_80221508_ovl_275850(u8 *o) {
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

INCLUDE_ASM("asm/nonmatchings/275850", func_80221750_ovl_275850);
