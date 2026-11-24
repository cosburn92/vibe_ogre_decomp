#include "common.h"

/* 263F40 */

typedef struct {
    u32 w0;
    u32 w1;
} Gwords263;
typedef union {
    Gwords263 words;
    long long force_align[1];
} Gfx263;
extern Gfx263 *D_800E9BA0;
extern u8 *D_801969B0; /* frame matrix pool cursor */
void guMtxF2L(void *mf, void *m);
void func_8020EE30_ovl_25EE90(void *p);

#define SHIFTL263(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define G263(pkt, w0_, w1_)            \
    {                                  \
        Gfx263 *_g = (Gfx263 *)(pkt);  \
                                       \
        _g->words.w0 = (w0_);          \
        _g->words.w1 = (u32)(w1_);     \
    }

typedef struct {
    /* 0x00 */ u8 unk00[0x40];
    /* 0x40 */ f32 alpha;
} Mdl263Mtx;

typedef struct {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u8 unk02[2];
    /* 0x04 */ Mdl263Mtx *mtx;
    /* 0x08 */ void *dl;
    /* 0x0C */ u8 *seg6;
    /* 0x10 */ u8 unk10[4];
    /* 0x14 */ u8 *segE;
    /* 0x18 */ s16 ulx;
    /* 0x1A */ s16 uly;
    /* 0x1C */ s16 lrx;
    /* 0x1E */ s16 lry;
} Mdl263;

/* Draws the model at o + 0x18 like func_8020F134, with its own scissor box before the segment-E list */
s32 func_8020F390_ovl_25EE90(u8 *o) {
    Mdl263 *m = (Mdl263 *)(o + 0x18);

    func_8020EE30_ovl_25EE90(m);
    G263(D_800E9BA0++, 0xFA000000, (u8)(m->mtx->alpha * 255.0f));
    guMtxF2L(m->mtx, D_801969B0);
    G263(D_800E9BA0++, 0xDA380000, D_801969B0);
    if (m->seg6 != NULL) {
        G263(D_800E9BA0++, 0xE7000000, 0);
        G263(D_800E9BA0++, 0xDB06003C, m->seg6 - 0x80000000);
        G263(D_800E9BA0++, 0xE7000000, 0);
        G263(D_800E9BA0++, 0xDE000000, m->dl);
    }
    G263(D_800E9BA0++, SHIFTL263(0xF2, 24, 8) | SHIFTL263(m->ulx * 4, 12, 12) | SHIFTL263(m->uly * 4, 0, 12),
         SHIFTL263(m->lrx * 4, 12, 12) | SHIFTL263(m->lry * 4, 0, 12));
    G263(D_800E9BA0++, 0xE7000000, 0);
    G263(D_800E9BA0++, 0xDB060038, m->segE - 0x80000000);
    G263(D_800E9BA0++, 0xE7000000, 0);
    G263(D_800E9BA0++, 0xDE000000, 0x0E000000);
    G263(D_800E9BA0++, 0xD8380002, 0x40);
    D_801969B0 += 0x40;
    return 0;
}
