#include "common.h"
#include "gu.h"

/* libultra rotate.c */

extern f32 D_800ABAE0; /* dtor */

void guNormalize(f32 *x, f32 *y, f32 *z);

inline void guRotateF(f32 mf[4][4], f32 a, f32 x, f32 y, f32 z) {
    f32 sine;
    f32 cosine;
    f32 ab, bc, ca, t;
    f32 xs, ys, zs;

    guNormalize(&x, &y, &z);
    a *= D_800ABAE0;
    sine = sinf(a);
    cosine = cosf(a);
    t = (1 - cosine);
    ab = x * y * t;
    bc = y * z * t;
    ca = z * x * t;

    guMtxIdentF(mf);

    xs = x * sine;
    ys = y * sine;
    zs = z * sine;

    t = x * x;
    mf[0][0] = t + cosine * (1 - t);
    mf[2][1] = bc - xs;
    mf[1][2] = bc + xs;

    t = y * y;
    mf[1][1] = t + cosine * (1 - t);
    mf[2][0] = ca + ys;
    mf[0][2] = ca - ys;

    t = z * z;
    mf[2][2] = t + cosine * (1 - t);
    mf[1][0] = ab - zs;
    mf[0][1] = ab + zs;
}

void guRotate(Mtx *m, f32 a, f32 x, f32 y, f32 z) {
    f32 mf[4][4];

    guRotateF(mf, a, x, y, z);
    guMtxF2L(mf, m);
}
