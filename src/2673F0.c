#include "common.h"

/* 2673F0 */

typedef struct {
    u32 w0;
    u32 w1;
} Gwords;
typedef union {
    Gwords words;
    long long force_align[1];
} Gfx;
#define G267(w0_, w1_)                   \
    {                                    \
        Gfx *_g = (Gfx *)(D_800E9BA0++); \
                                         \
        _g->words.w0 = (w0_);            \
        _g->words.w1 = (u32)(w1_);       \
    }

extern Gfx *D_800E9BA0;
extern u8 D_802205B0_ovl_25EE90[];

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern u8 D_802205D0_ovl_25EE90[];
void func_80212840_ovl_25EE90();
typedef struct {
    /* 0x00 */ u8 unk00[0x40];
    /* 0x40 */ f32 fade;
} Owner267;
typedef struct {
    /* 0x00 */ u8 unk00[0x18];
    /* 0x18 */ u8 sub[4];
    /* 0x1C */ Owner267 *owner;
    /* 0x20 */ u8 unk20[0x11];
    /* 0x31 */ u8 r;
    /* 0x32 */ u8 unk32;
    /* 0x33 */ u8 g;
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 b;
} Obj267;
extern u8 D_802205F0_ovl_25EE90[];
/* --- end decls --- */

typedef struct {
    u8 b[0x40];
} Mtx267;
typedef struct {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u8 unk02[2];
    /* 0x04 */ f32 *mtx;
    /* 0x08 */ void *dl;
    /* 0x0C */ u8 *seg6;
    /* 0x10 */ u8 unk10[4];
    /* 0x14 */ u8 *segE;
} Mdl267;
extern Mtx267 *D_801969B0;
void guMtxF2L(f32 *mf, Mtx267 *m);

/* Draws part p: its matrix (p+4), then its own display list (p+8) with segment 6 = p+0xC when
 * present, then the shared list in segment 0xE (p+0x14) */
void func_80212840_ovl_25EE90(Mdl267 *m) {
    guMtxF2L(m->mtx, D_801969B0);
    G267(0xDA380000, D_801969B0);
    if (m->seg6 != NULL) {
        G267(0xE7000000, 0);
        G267(0xDB06003C, m->seg6 - 0x80000000);
        G267(0xE7000000, 0);
        G267(0xDE000000, m->dl);
    }
    G267(0xE7000000, 0);
    G267(0xDB060038, m->segE - 0x80000000);
    G267(0xE7000000, 0);
    G267(0xDE000000, 0x0E000000);
    G267(0xD8380002, 0x40);
    D_801969B0++;
}

s32 func_802129BC_ovl_25EE90(u8 *o) {
    Gfx *g = D_800E9BA0++;

    g->words.w0 = 0xDE000000;
    g->words.w1 = (u32)D_802205B0_ovl_25EE90;
    func_80212840_ovl_25EE90(o + 0x18);
    return 0;
}

/* Draws the object with its fade (+0x40 of its owner, 0..1) as prim alpha */
s32 func_80212A04_ovl_25EE90(Obj267 *o) {
    Mdl267 *m = (Mdl267 *)o->sub;

    G267(0xDE000000, D_802205D0_ovl_25EE90);
    G267(0xFA000000, (u8)(o->owner->fade * 255.0f));
    func_80212840_ovl_25EE90(m);
    return 0;
}

/* Same with the object's own colour (0x31/0x33/0x35) and the owner's fade as alpha */
s32 func_80212AB8_ovl_25EE90(Obj267 *o) {
    Mdl267 *m = (Mdl267 *)o->sub;

    G267(0xDE000000, D_802205F0_ovl_25EE90);
    G267(0xFA000000, (o->r << 24) | (o->g << 16) | (o->b << 8) | (u8)(o->owner->fade * 255.0f));
    func_80212840_ovl_25EE90(m);
    return 0;
}
