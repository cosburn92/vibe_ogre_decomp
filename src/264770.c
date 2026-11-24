#include "common.h"

/* 264770 */

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

extern Gfx *D_800E9BA0;
#define G2647(w0_, w1_)                  \
    {                                   \
        Gfx *_g = D_800E9BA0++;         \
        _g->w0 = (w0_);                 \
        _g->w1 = (u32)(w1_);            \
    }
/* gDPSetTileSize for tile 0, coordinates in pixels */
#define TILESIZE2647(uls, ult, lrs, lrt)                                              \
    G2647(0xF2000000 | ((((uls) << 2) & 0xFFF) << 12) | (((ult) << 2) & 0xFFF),       \
          ((((lrs) << 2) & 0xFFF) << 12) | (((lrt) << 2) & 0xFFF))

extern u8 *D_801969B0; /* frame matrix pool cursor */
void guMtxF2L(void *mf, void *m);

typedef struct {
    /* 0x00 */ u8 unk00[0x40];
    /* 0x40 */ f32 alpha;
} Mdl2647Mtx;

typedef struct {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u8 unk02[2];
    /* 0x04 */ Mdl2647Mtx *mtx;
    /* 0x08 */ void *dl;
    /* 0x0C */ u8 *seg6;
    /* 0x10 */ u8 unk10[4];
    /* 0x14 */ u8 *segE;
    /* 0x18 */ void *dlb;
    /* 0x1C */ u8 *seg6b;
    /* 0x20 */ s16 tile[4];
    /* 0x28 */ s16 tileb[4];
} Mdl2647;

void func_8020EE30_ovl_25EE90(u16 *o);
void func_8020FBC0_ovl_25EE90(Mdl2647 *m);
/* --- end decls --- */

/* Draws the two-part model: alpha as prim alpha, its matrix, the optional segment-6 list,
 * then tile 0 sized to the first rectangle and the segment-E list; if the second segment-6
 * pointer is set, a render-mode change, that pointer with the second list, and the
 * segment-E list again with the second rectangle */
void func_8020FBC0_ovl_25EE90(Mdl2647 *m) {
    G2647(0xFA000000, (u8)(m->mtx->alpha * 255.0f));
    guMtxF2L(m->mtx, D_801969B0);
    G2647(0xDA380000, D_801969B0);
    if (m->seg6 != NULL) {
        G2647(0xE7000000, 0);
        G2647(0xDB06003C, m->seg6 - 0x80000000);
        G2647(0xE7000000, 0);
        G2647(0xDE000000, m->dl);
    }
    TILESIZE2647(m->tile[0], m->tile[1], m->tile[2], m->tile[3]);
    G2647(0xE7000000, 0);
    G2647(0xDB060038, m->segE - 0x80000000);
    G2647(0xE7000000, 0);
    G2647(0xDE000000, 0x0E000000);
    if (m->seg6b != NULL) {
        G2647(0xE7000000, 0);
        G2647(0xE200001C, 0x00404340);
        G2647(0xE7000000, 0);
        G2647(0xDB06003C, m->seg6b - 0x80000000);
        G2647(0xE7000000, 0);
        G2647(0xDE000000, m->dlb);
        TILESIZE2647(m->tileb[0], m->tileb[1], m->tileb[2], m->tileb[3]);
        G2647(0xE7000000, 0);
        G2647(0xDB060038, m->segE - 0x80000000);
        G2647(0xE7000000, 0);
        G2647(0xDE000000, 0x0E000000);
    }
    G2647(0xD8380002, 0x40);
    D_801969B0 += 0x40;
}

s32 func_8020FF6C_ovl_25EE90(u8 *o) {
    u8 *p = o + 0x18;

    func_8020EE30_ovl_25EE90((u16 *)p);
    func_8020FBC0_ovl_25EE90((Mdl2647 *)p);
    return 0;
}

s32 func_8020FFA0_ovl_25EE90(u8 *o) {
    u8 *p = o + 0x18;
    Gfx *g;

    func_8020EE30_ovl_25EE90((u16 *)p);
    g = D_800E9BA0++;
    g->w0 = 0xD9FFFFFF;
    g->w1 = 0x400;
    func_8020FBC0_ovl_25EE90((Mdl2647 *)p);
    return 0;
}
