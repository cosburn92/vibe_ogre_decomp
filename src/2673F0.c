#include "common.h"

/* 2673F0 */

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

extern Gfx *D_800E9BA0;
extern u8 D_802205B0_ovl_25EE90[];

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern u8 D_802205D0_ovl_25EE90[];
void func_80212840_ovl_25EE90(void *p);
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

INCLUDE_ASM("asm/nonmatchings/2673F0", func_80212840_ovl_25EE90);

s32 func_802129BC_ovl_25EE90(u8 *o) {
    Gfx *g = D_800E9BA0++;

    g->w0 = 0xDE000000;
    g->w1 = (u32)D_802205B0_ovl_25EE90;
    func_80212840_ovl_25EE90(o + 0x18);
    return 0;
}

/* Draws the object with its fade (+0x40 of its owner, 0..1) as prim alpha */
#ifdef NON_MATCHING
/* display-list pointer updates scheduled after the float alpha conversion in the original */
s32 func_80212A04_ovl_25EE90(u8 *o) {
    Gfx *g = D_800E9BA0;

    g->w0 = 0xDE000000;
    g->w1 = (u32)D_802205D0_ovl_25EE90;
    g++;
    g->w0 = 0xFA000000;
    D_800E9BA0 = g;
    D_800E9BA0 = g + 1;
    g->w1 = (u8)(u32)(FIELD(FIELD(o, u8 *, 0x1C), f32, 0x40) * 255.0f);
    func_80212840_ovl_25EE90(o + 0x18);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/2673F0", func_80212A04_ovl_25EE90);
#endif

/* Same with the object's own colour (0x31/0x33/0x35) and the owner's fade as alpha */
#ifdef NON_MATCHING
/* Struct members (owner->fade) give the right store/pointer-update order. Register allocation still differs (the original keeps g in v0 with no copy) and so does the float-to-u32 branch layout, as in func_80212A04 and ED530 func_801A93A4. */
s32 func_80212AB8_ovl_25EE90(Obj267 *o) {
    Gfx *g;

    g = D_800E9BA0++;
    g->w0 = 0xDE000000;
    g->w1 = (u32)D_802205F0_ovl_25EE90;
    g = D_800E9BA0++;
    g->w0 = 0xFA000000;
    g->w1 = (o->r << 24) | (o->g << 16) | (o->b << 8) | (u8)(u32)(o->owner->fade * 255.0f);
    func_80212840_ovl_25EE90(o->sub);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/2673F0", func_80212AB8_ovl_25EE90);
#endif
