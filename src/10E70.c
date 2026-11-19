#include "common.h"

typedef s32 Mtx[16];

extern f32 D_800A9880; /* degrees to radians */

f32 sinf(f32);
f32 cosf(f32);
void guMtxIdentF(f32 mf[4][4]);
void guMtxF2L(f32 mf[4][4], Mtx *m);

/* Rotation matrix from X/Y/Z angles in degrees */
#ifdef NON_MATCHING
/* Both functions are correct but the FPU register allocation / scheduling of the
 * matrix products differs slightly. */
inline void func_80080A70(f32 mf[4][4], f32 x, f32 y, f32 z) {
    f32 sx, cx, sy, cy, cz, sz;

    x *= D_800A9880;
    y *= D_800A9880;
    z *= D_800A9880;
    sx = sinf(x);
    cx = cosf(x);
    sy = sinf(y);
    cy = cosf(y);
    sz = sinf(z);
    cz = cosf(z);

    guMtxIdentF(mf);
    {
    f32 a = cz * sy;
    f32 b = sy * sz;
    mf[0][0] = cy * cz;
    mf[0][1] = sx * a + cx * sz;
    mf[0][2] = -cx * a + sx * sz;
    mf[1][0] = -cy * sz;
    mf[1][1] = cx * cz - sx * b;
    mf[1][2] = cz * sx + cx * b;
    mf[2][0] = sy;
    mf[2][1] = -cy * sx;
    mf[2][2] = cx * cy;
    }
}

void func_80080BE0(Mtx *m, f32 x, f32 y, f32 z) {
    f32 mf[4][4];

    func_80080A70(mf, x, y, z);
    guMtxF2L(mf, m);
}
#else
INCLUDE_ASM("asm/nonmatchings/10E70", func_80080A70);

INCLUDE_ASM("asm/nonmatchings/10E70", func_80080BE0);
#endif
