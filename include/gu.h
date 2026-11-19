#ifndef GU_H
#define GU_H

/* libultra gu declarations */

typedef union {
    s32 m[4][4];
    s64 force_structure_alignment;
} Mtx;

typedef f32 MtxF[4][4];

void guMtxIdentF(f32 mf[4][4]);
void guMtxF2L(f32 mf[4][4], Mtx *m);
f32 sqrtf(f32 x);
f32 sinf(f32 x);
f32 cosf(f32 x);

#endif
