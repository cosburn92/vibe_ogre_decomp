#include "common.h"
#include "gu.h"

void guMtxL2F(f32 mf[4][4], Mtx *m);
void guMtxXFMF(f32 mf[4][4], f32 x, f32 y, f32 z, f32 *ox, f32 *oy, f32 *oz);

void guMtxXFML(Mtx *m, f32 x, f32 y, f32 z, f32 *ox, f32 *oy, f32 *oz) {
    f32 mf[4][4];

    guMtxL2F(mf, m);
    guMtxXFMF(mf, x, y, z, ox, oy, oz);
}
