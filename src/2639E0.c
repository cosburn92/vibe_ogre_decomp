#include "common.h"

/* 2639E0 */

typedef struct {
    u32 w0;
    u32 w1;
} Gwords263;
typedef union {
    Gwords263 words;
    long long force_align[1];
} Gfx263;
extern Gfx263 *D_800E9BA0;
extern u8 D_80220250_ovl_25EE90[];
extern u8 D_802202D0_ovl_25EE90[];
#define G263(w0_, w1_)                 \
    {                                  \
        Gfx263 *_g = (Gfx263 *)(D_800E9BA0++);     \
                                       \
        _g->words.w0 = (w0_);         \
        _g->words.w1 = (u32)(w1_);          \
    }

/* Display list for object o: setup list by kind (0x10: 0 or 1; hangs otherwise), then the
 * translucent render mode (flag 2) and back-face culling off (flag 1) */
inline void func_8020EE30_ovl_25EE90(u16 *o) {
    switch (o[8]) {
        case 0:
            G263(0xDE000000, D_80220250_ovl_25EE90);
            break;
        case 1:
            G263(0xDE000000, D_802202D0_ovl_25EE90);
            break;
        default:
            for (;;) {
            }
    }
    if (o[0] & 2) {
        G263(0xE200001C, 0x4041C8);
    }
    if (o[0] & 1) {
        G263(0xD9FFFFFF, 0x400);
    }
    G263(0xE7000000, 0);
}

extern u8 *D_801969B0; /* frame matrix pool cursor */
void guMtxF2L(void *mf, void *m);
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif

/* Draws model o: alpha (matrix + 0x40) as prim alpha, its float matrix (o + 4), the optional
 * segment-F setup list (o + 8 with segment o + 0xC), then segment E (o + 0x14) list 0x0E000000 */
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
} Mdl263;

void func_8020EF40_ovl_25EE90(Mdl263 *m) {
    G263(0xFA000000, (u8)(m->mtx->alpha * 255.0f));
    guMtxF2L(m->mtx, D_801969B0);
    G263(0xDA380000, D_801969B0);
    if (m->seg6 != NULL) {
        G263(0xE7000000, 0);
        G263(0xDB06003C, m->seg6 - 0x80000000);
        G263(0xE7000000, 0);
        G263(0xDE000000, m->dl);
    }
    G263(0xE7000000, 0);
    G263(0xDB060038, m->segE - 0x80000000);
    G263(0xE7000000, 0);
    G263(0xDE000000, 0x0E000000);
    G263(0xD8380002, 0x40);
    D_801969B0 += 0x40;
}


/* Draws the model at o + 0x18 (setup as func_8020EE30, then func_8020EF40) */
s32 func_8020F134_ovl_25EE90(u8 *o) {
    u8 *m = o + 0x18;

    func_8020EE30_ovl_25EE90((u16 *)m);
    func_8020EF40_ovl_25EE90((Mdl263 *)m);
    return 0;
}

/* As func_8020F134 for the model at o + 0x14 */
s32 func_8020F260_ovl_25EE90(u8 *o) {
    u8 *m = o + 0x14;

    func_8020EE30_ovl_25EE90((u16 *)m);
    func_8020EF40_ovl_25EE90((Mdl263 *)m);
    return 0;
}
