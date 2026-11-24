#include "common.h"

/* 264490 */

typedef struct {
    u32 w0;
    u32 w1;
} Gwords2644;
typedef union {
    Gwords2644 words;
    long long force_align[1];
} Gfx2644;
extern Gfx2644 *D_800E9BA0;
#define G2644(w0_, w1_)                             \
    {                                              \
        Gfx2644 *_g = (Gfx2644 *)(D_800E9BA0++);     \
                                                   \
        _g->words.w0 = (w0_);                      \
        _g->words.w1 = (u32)(w1_);                 \
    }

extern u8 *D_801969B0; /* frame matrix pool cursor */
void guMtxF2L(void *mf, void *m);
void func_8020EE30_ovl_25EE90(u16 *o);

typedef struct {
    /* 0x00 */ u8 unk00[0x40];
    /* 0x40 */ f32 alpha;
} Mdl2644Mtx;

typedef struct {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u8 unk02[2];
    /* 0x04 */ Mdl2644Mtx *mtx;
    /* 0x08 */ void *dl;
    /* 0x0C */ u8 *seg6;
    /* 0x10 */ u8 unk10[4];
    /* 0x14 */ u8 *segE;
    /* 0x18 */ u8 *seg6b;
} Mdl2644;

/* Draws the two-part model at o + 0x18: setup list, alpha as prim alpha, its matrix, the
 * optional segment-6 list, the segment-E list, then, if the second segment-6 pointer
 * (o + 0x30) is set, the same list again with it followed by the segment-E list again */
s32 func_8020F8E0_ovl_25EE90(u8 *o) {
    Mdl2644 *m = (Mdl2644 *)(o + 0x18);

    func_8020EE30_ovl_25EE90((u16 *)m);
    G2644(0xFA000000, (u8)(m->mtx->alpha * 255.0f));
    guMtxF2L(m->mtx, D_801969B0);
    G2644(0xDA380000, D_801969B0);
    if (m->seg6 != NULL) {
        G2644(0xE7000000, 0);
        G2644(0xDB06003C, m->seg6 - 0x80000000);
        G2644(0xE7000000, 0);
        G2644(0xDE000000, m->dl);
    }
    G2644(0xE7000000, 0);
    G2644(0xDB060038, m->segE - 0x80000000);
    G2644(0xE7000000, 0);
    G2644(0xDE000000, 0x0E000000);
    if (m->seg6b != NULL) {
        G2644(0xE7000000, 0);
        G2644(0xDB06003C, m->seg6b - 0x80000000);
        G2644(0xE7000000, 0);
        G2644(0xDE000000, m->dl);
        G2644(0xE7000000, 0);
        G2644(0xDB060038, m->segE - 0x80000000);
        G2644(0xE7000000, 0);
        G2644(0xDE000000, 0x0E000000);
    }
    G2644(0xD8380002, 0x40);
    D_801969B0 += 0x40;
    return 0;
}
