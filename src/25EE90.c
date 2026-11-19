#include "common.h"

/* 25EE90 */

f32 sqrtf(f32 x);
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
void func_8020A348_ovl_25EE90(f32 *a, f32 *b, f32 *out) {
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
void func_8020A418_ovl_25EE90(f32 *v) {
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

INCLUDE_ASM("asm/nonmatchings/25EE90", func_8020A4D0_ovl_25EE90);

/* Sets the translation row of a 4x4 matrix */
void func_8020A5A0_ovl_25EE90(f32 *m, f32 *t) {
    s32 i;

    for (i = 0; i < 3; i++) {
        m[12 + i] = t[i];
    }
}

INCLUDE_ASM("asm/nonmatchings/25EE90", func_8020A5C8_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/25EE90", func_8020A7A0_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/25EE90", func_8020A888_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/25EE90", func_8020A980_ovl_25EE90);

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
