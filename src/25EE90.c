#include "common.h"

/* 25EE90 */

f32 sqrtf(f32 x);
void func_8020A5C8_ovl_25EE90(f32 *a, f32 *b, f32 *c, f32 (*m)[4]);
void guMtxIdentF(f32 (*m)[4]);
/* --- end decls --- */

/* out = v * s (safe when out overlaps v) */
void func_8020A2E0_ovl_25EE90(f32 *v, f32 s, f32 *out) {
    f32 t[3];
    s32 i;

    for (i = 0; i < 3; i++) {
        t[i] = v[i] * s;
    }
    for (i--; i >= 0; i--) {
        out[i] = t[i];
    }
}

/* out = a x b (safe when out overlaps an input) */
inline void func_8020A348_ovl_25EE90(f32 *a, f32 *b, f32 *out) {
    f32 t[3];

    t[0] = a[1] * b[2] - a[2] * b[1];
    t[1] = a[2] * b[0] - a[0] * b[2];
    t[2] = a[0] * b[1] - a[1] * b[0];
    out[0] = t[0];
    out[1] = t[1];
    out[2] = t[2];
}

f32 func_8020A3C8_ovl_25EE90(f32 *v) {
    return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

/* Normalises v in place */
inline void func_8020A418_ovl_25EE90(f32 *v) {
    f32 inv = 1.0f / sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    v[0] *= inv;
    v[1] *= inv;
    v[2] *= inv;
}

/* 4x4 matrix copy */
void func_8020A4A8_ovl_25EE90(f32 *src, f32 *dst) {
    s32 i;

    for (i = 0; i < 16; i++) {
        *dst++ = *src++;
    }
}

/* out = m with its first three rows scaled by s[row] (translation column kept) */
#ifdef NON_MATCHING
/* loop induction registers assigned in a different order */
void func_8020A4D0_ovl_25EE90(f32 *s, f32 m[4][4], f32 out[4][4]) {
    f32 t[4][4];
    s32 i;
    s32 j;

    for (j = 0; j < 3; j++) {
        for (i = 0; i < 4; i++) {
            if (i != 3) {
                t[j][i] = m[j][i] * s[j];
            } else {
                t[j][3] = m[j][3];
            }
        }
    }
    for (i = 0; i < 4; i++) {
        t[3][i] = m[3][i];
    }
    for (i = 0; i < 16; i++) {
        ((f32 *)out)[i] = ((f32 *)t)[i];
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/25EE90", func_8020A4D0_ovl_25EE90);
#endif

/* Sets the translation row of a 4x4 matrix */
void func_8020A5A0_ovl_25EE90(f32 *m, f32 *t) {
    s32 i;

    for (i = 0; i < 3; i++) {
        m[12 + i] = t[i];
    }
}

/* Rotation matrix from three axes (normalised in place): rows b, c, a */
void func_8020A5C8_ovl_25EE90(f32 *a, f32 *b, f32 *c, f32 (*m)[4]) {
    func_8020A418_ovl_25EE90(b);
    func_8020A418_ovl_25EE90(c);
    func_8020A418_ovl_25EE90(a);
    guMtxIdentF(m);
    m[0][0] = b[0];
    m[0][1] = b[1];
    m[0][2] = b[2];
    m[1][0] = c[0];
    m[1][1] = c[1];
    m[1][2] = c[2];
    m[2][0] = a[0];
    m[2][1] = a[1];
    m[2][2] = a[2];
}

/* Orthonormal-ish basis from forward a and up b: c = a x b, b = c x a, then builds m */
void func_8020A7A0_ovl_25EE90(f32 *a, f32 *b, void *m) {
    f32 c[3];

    func_8020A348_ovl_25EE90(a, b, c);
    func_8020A348_ovl_25EE90(c, a, b);
    func_8020A5C8_ovl_25EE90(a, b, c, (f32 (*)[4])m);
}

INCLUDE_ASM("asm/nonmatchings/25EE90", func_8020A888_ovl_25EE90);

void func_8020A980_ovl_25EE90(f32 *a, f32 *b, void *m) {
    f32 c[3];

    func_8020A348_ovl_25EE90(b, a, c);
    func_8020A348_ovl_25EE90(a, c, b);
    func_8020A5C8_ovl_25EE90(a, c, b, (f32 (*)[4])m);
}

/* out = v * m (row vector times 4x4 matrix) */
void func_8020AA70_ovl_25EE90(f32 m[4][4], f32 *v, f32 *out) {
    f32 t[4];
    s32 i;
    s32 j;

    for (j = 0; j < 4; j++) {
        t[j] = 0.0f;
        for (i = 0; i < 4; i++) {
            t[j] += m[i][j] * v[i];
        }
    }
    for (i = 0; i < 4; i++) {
        out[i] = t[i];
    }
}
