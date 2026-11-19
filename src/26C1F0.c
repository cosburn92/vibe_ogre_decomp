#include "common.h"

/* 26C1F0 */

typedef struct {
    f32 x, y, z;
} Vec3f;

typedef struct Ent26 Ent26;

extern f32 D_801D06F0;
extern f32 D_801D0740;
extern s32 D_801D0764;
extern s16 D_801D0820;
extern s16 D_801D071C;

void func_8020A980_ovl_25EE90(Vec3f *v);
s32 func_801C8B68(s32 a);
s32 func_801C8E48(s32 a);
Ent26 *func_801C8FE8(void);
s32 func_8020ABC0_ovl_25EE90(Ent26 *e);
s32 func_8020ABE8_ovl_25EE90(Ent26 *e);
s32 func_8020AC10_ovl_25EE90(Ent26 *e);
void func_801AD9D4(void *p, s32 a);
void _bcopy(void *src, void *dst, s32 n);
void func_8020A418_ovl_25EE90(f32 *v);
void func_8020A348_ovl_25EE90(f32 *a, f32 *b, f32 *out);
void guMtxIdentF(f32 (*m)[4]);
extern f32 D_80220610_ovl_25EE90;
extern f32 D_80220614_ovl_25EE90;
extern f32 D_80220618_ovl_25EE90;
/* --- end decls --- */

void func_80217640_ovl_25EE90(Vec3f *v) {
    Vec3f n;

    n.x = -v->x;
    n.y = -v->y;
    n.z = -v->z;
    func_8020A980_ovl_25EE90(&n);
}

/* Rotation matrix whose z axis is dir (y up) */
void func_80217680_ovl_25EE90(f32 *dir, f32 (*m)[4]) {
    f32 b[3][3];
    s32 i;
    s32 j;
    s32 k;

    b[2][0] = dir[0];
    b[2][1] = dir[1];
    b[2][2] = dir[2];
    func_8020A418_ovl_25EE90(b[2]);
    b[1][0] = 0.0f;
    b[1][1] = 1.0f;
    b[1][2] = 0.0f;
    func_8020A348_ovl_25EE90(b[1], b[2], b[0]);
    func_8020A348_ovl_25EE90(b[2], b[0], b[1]);
    guMtxIdentF(m);
    for (i = 0, k = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            m[i][j] = b[0][k++];
        }
    }
}

/* Rotation matrix whose z axis is -dir (y up) */
#ifdef NON_MATCHING
/* original keeps only the side vector in a saved register; frame 0x58 */
void func_80217760_ovl_25EE90(f32 *dir, f32 (*m)[4]) {
    f32 n[3];
    f32 b[3][3];
    s32 i;
    s32 j;
    s32 k;

    n[0] = -dir[0];
    n[1] = -dir[1];
    n[2] = -dir[2];
    b[2][0] = n[0];
    b[2][1] = n[1];
    b[2][2] = n[2];
    func_8020A418_ovl_25EE90(b[2]);
    b[1][0] = 0.0f;
    b[1][1] = 1.0f;
    b[1][2] = 0.0f;
    func_8020A348_ovl_25EE90(b[1], b[2], b[0]);
    func_8020A348_ovl_25EE90(b[2], b[0], b[1]);
    guMtxIdentF(m);
    for (i = 0, k = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            m[i][j] = b[0][k++];
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/26C1F0", func_80217760_ovl_25EE90);
#endif

/* Same, facing against the camera direction D_80220610 */
#ifdef NON_MATCHING
/* same as func_80217760 */
void func_80217848_ovl_25EE90(f32 (*m)[4]) {
    f32 n[3];
    f32 b[3][3];
    s32 i;
    s32 j;
    s32 k;

    n[0] = -D_80220610_ovl_25EE90;
    n[1] = -D_80220614_ovl_25EE90;
    n[2] = -D_80220618_ovl_25EE90;
    b[2][0] = n[0];
    b[2][1] = n[1];
    b[2][2] = n[2];
    func_8020A418_ovl_25EE90(b[2]);
    b[1][0] = 0.0f;
    b[1][1] = 1.0f;
    b[1][2] = 0.0f;
    func_8020A348_ovl_25EE90(b[1], b[2], b[0]);
    func_8020A348_ovl_25EE90(b[2], b[0], b[1]);
    guMtxIdentF(m);
    for (i = 0, k = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            m[i][j] = b[0][k++];
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/26C1F0", func_80217848_ovl_25EE90);
#endif

void func_8021793C_ovl_25EE90(s32 a, Vec3f *out) {
    if (func_801C8B68(a) != func_801C8E48(a)) {
        out->x = 1.0f;
    } else {
        out->x = -1.0f;
    }
    out->y = 0.0f;
    out->z = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/26C1F0", func_802179AC_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26C1F0", func_80217AD4_ovl_25EE90);

void func_80217C14_ovl_25EE90(Ent26 *e, Vec3f *out) {
    out->x = func_8020ABC0_ovl_25EE90(e);
    out->z = func_8020AC10_ovl_25EE90(e);
    out->y = func_8020ABE8_ovl_25EE90(e);
}

void func_80217C84_ovl_25EE90(s32 unused, Vec3f *out) {
    Ent26 *e = func_801C8FE8();

    out->x = func_8020ABC0_ovl_25EE90(e);
    out->z = func_8020AC10_ovl_25EE90(e);
    out->y = func_8020ABE8_ovl_25EE90(e);
}

void func_80217CFC_ovl_25EE90(u8 **arr, s32 a) {
    u32 i;

    for (i = 0; i < 3; i++) {
        if (arr[i] != NULL) {
            func_801AD9D4(arr[i] + 0x44, a);
        }
    }
}

void func_80217D5C_ovl_25EE90(s32 unused, s32 a) {
    u8 **arr = (u8 **)func_801C8FE8();
    u32 i;

    for (i = 0; i < 3; i++) {
        if (arr[i] != NULL) {
            func_801AD9D4(arr[i] + 0x44, a);
        }
    }
}

void func_80217DC0_ovl_25EE90(u8 **e, void *dst) {
    _bcopy(e[0] + 0x44, dst, 0x50);
}

void func_80217DE4_ovl_25EE90(s32 unused, void *dst) {
    _bcopy(((u8 **)func_801C8FE8())[0] + 0x44, dst, 0x50);
}

INCLUDE_ASM("asm/nonmatchings/26C1F0", func_80217E1C_ovl_25EE90);

/* Cubic spline value at x through n knots (xs, ys) with per-knot coefficients m */
f32 func_8021802C_ovl_25EE90(f32 x, s32 n, f32 *xs, f32 *ys, f32 *m) {
    s32 lo = 0;
    s32 hi = n - 1;
    s32 mid;
    f32 t;
    f32 h;

    while (lo < hi) {
        mid = (lo + hi) / 2;
        if (xs[mid] < x) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    lo -= (lo > 0);
    t = x - xs[lo];
    h = xs[lo + 1] - xs[lo];
    return ((((m[lo + 1] - m[lo]) * t / h + m[lo] * 3.0f) * t + ((ys[lo + 1] - ys[lo]) / h - (m[lo] + m[lo] + m[lo + 1]) * h)) * t) + ys[lo];
}

void func_80218104_ovl_25EE90(f32 a, f32 b, s32 c, s32 d) {
    D_801D06F0 = a;
    D_801D0740 = b;
    D_801D0764 = c;
    D_801D0820 = d;
    D_801D071C = 0xFF - d;
}
