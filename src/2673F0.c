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
void func_80212840_ovl_25EE90(u8 *p);
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
extern Mtx267 *D_801969B0;
void guMtxF2L(f32 *mf, Mtx267 *m);

/* Draws part p: its matrix (p+4), then its own display list (p+8) with segment 6 = p+0xC when
 * present, then the shared list in segment 0xE (p+0x14) */
#ifdef NON_MATCHING
/* 95/95 instructions, 67 words differ: the original writes each block's command words before advancing D_800E9BA0 (pointer stores sunk to the end of the block) */
void func_80212840_ovl_25EE90(u8 *p) {
    guMtxF2L(FIELD(p, f32 *, 4), D_801969B0);
    D_800E9BA0->w0 = 0xDA380000;
    D_800E9BA0->w1 = (u32)D_801969B0;
    D_800E9BA0++;
    if (FIELD(p, u32, 0xC) != 0) {
        D_800E9BA0->w0 = 0xE7000000;
        D_800E9BA0->w1 = 0;
        D_800E9BA0++;
        D_800E9BA0->w0 = 0xDB06003C;
        D_800E9BA0->w1 = FIELD(p, u32, 0xC) - 0x80000000;
        D_800E9BA0++;
        D_800E9BA0->w0 = 0xE7000000;
        D_800E9BA0->w1 = 0;
        D_800E9BA0++;
        D_800E9BA0->w0 = 0xDE000000;
        D_800E9BA0->w1 = FIELD(p, u32, 8);
        D_800E9BA0++;
    }
    D_800E9BA0->w0 = 0xE7000000;
    D_800E9BA0->w1 = 0;
    D_800E9BA0++;
    D_800E9BA0->w0 = 0xDB060038;
    D_800E9BA0->w1 = FIELD(p, u32, 0x14) - 0x80000000;
    D_800E9BA0++;
    D_800E9BA0->w0 = 0xE7000000;
    D_800E9BA0->w1 = 0;
    D_800E9BA0++;
    D_800E9BA0->w0 = 0xDE000000;
    D_800E9BA0->w1 = 0x0E000000;
    D_800E9BA0++;
    D_800E9BA0->w0 = 0xD8380002;
    D_800E9BA0->w1 = 0x40;
    D_800E9BA0++;
    D_801969B0++;
}
#else
INCLUDE_ASM("asm/nonmatchings/2673F0", func_80212840_ovl_25EE90);
#endif

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
