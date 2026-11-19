#include "common.h"
#include "gu.h"

void guMtxL2F(f32 mf[4][4], Mtx *m);
void guMtxCatF(f32 mf[4][4], f32 nf[4][4], f32 res[4][4]);

void guMtxCatL(Mtx *m, Mtx *n, Mtx *res) {
    f32 mf[4][4], nf[4][4], resf[4][4];

    guMtxL2F(mf, m);
    guMtxL2F(nf, n);
    guMtxCatF(mf, nf, resf);
    guMtxF2L(resf, res);
}
