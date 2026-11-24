#include "common.h"

/* 2641B0 */

typedef struct {
    u32 w0;
    u32 w1;
} Gwords264;
typedef union {
    Gwords264 words;
    long long force_align[1];
} Gfx264;
extern Gfx264 *D_800E9BA0;
#define G264(w0_, w1_)                             \
    {                                              \
        Gfx264 *_g = (Gfx264 *)(D_800E9BA0++);     \
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
} Mdl264Mtx;

typedef struct {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u8 unk02[2];
    /* 0x04 */ Mdl264Mtx *mtx;
    /* 0x08 */ void *dl;
    /* 0x0C */ u8 *seg6;
    /* 0x10 */ u8 unk10[4];
    /* 0x14 */ u8 *segE;
    /* 0x18 */ void *dl2;
    /* 0x1C */ u8 *seg6b;
} Mdl264;

/* Draws the two-part model at o + 0x18: setup list, alpha as prim alpha, its matrix, the
 * optional segment-6 list, the segment-E list, then optionally a second segment-6 list
 * followed by the segment-E list again */
s32 func_8020F600_ovl_25EE90(u8 *o) {
    Mdl264 *m = (Mdl264 *)(o + 0x18);

    func_8020EE30_ovl_25EE90((u16 *)m);
    G264(0xFA000000, (u8)(m->mtx->alpha * 255.0f));
    guMtxF2L(m->mtx, D_801969B0);
    G264(0xDA380000, D_801969B0);
    if (m->seg6 != NULL) {
        G264(0xE7000000, 0);
        G264(0xDB06003C, m->seg6 - 0x80000000);
        G264(0xE7000000, 0);
        G264(0xDE000000, m->dl);
    }
    G264(0xE7000000, 0);
    G264(0xDB060038, m->segE - 0x80000000);
    G264(0xE7000000, 0);
    G264(0xDE000000, 0x0E000000);
    if (m->seg6b != NULL) {
        G264(0xE7000000, 0);
        G264(0xDB06003C, m->seg6b - 0x80000000);
        G264(0xE7000000, 0);
        G264(0xDE000000, m->dl2);
        G264(0xE7000000, 0);
        G264(0xDB060038, m->segE - 0x80000000);
        G264(0xE7000000, 0);
        G264(0xDE000000, 0x0E000000);
    }
    G264(0xD8380002, 0x40);
    D_801969B0 += 0x40;
    return 0;
}
