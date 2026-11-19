#include "common.h"

/* ED530 */

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

typedef struct Tree0E {
    struct Tree0E *left;
    struct Tree0E *right;
} Tree0E;

typedef struct {
    /* 0x000 */ u8 unk000[0x104];
    /* 0x104 */ s32 w104;
    /* 0x108 */ u8 unk108[4];
    /* 0x10C */ f32 f10C;
    /* 0x110 */ u8 unk110[0x3E];
    /* 0x14E */ u8 r;
    /* 0x14F */ u8 g;
    /* 0x150 */ u8 b;
} Scene0E;

extern Gfx *D_800E9BA0;
extern u8 D_8018F481;
extern u8 D_8018F480;
extern u8 D_8018F53F;
extern u8 D_8018F55B;
extern s16 D_8018F55C;
extern s16 D_8018F55E;
extern s32 D_801AD580_ovl_0EBBB0;
extern f32 D_801AD584_ovl_0EBBB0;
extern Scene0E *D_801ABA58_ovl_0EBBB0;
extern u8 D_801AC4D0_ovl_0EBBB0[];
extern f32 D_800E7AD0[];
extern f32 D_800C4AD8[];

void nuGfxTaskAllEndWait(void);
void func_80079618();
void *HFree(void *p);
void func_801A499C_ovl_0EBBB0(void);
f32 func_8009D3E0(f32 x);
void func_80197FA4(s32 a, s32 b, u8 c);
void guRotateF(f32 *mf, f32 a, f32 x, f32 y, f32 z);
void guMtxCatF(f32 *m, f32 *n, f32 *r);
#define FIELDX(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern u8 D_8018F540;
extern u16 D_8018F542;
extern u16 D_8018F544;
extern u16 D_8018F546;
typedef struct {
    u16 a;
    u16 b;
} Pair0E;
extern Pair0E D_801ABA70_ovl_0EBBB0[];
f32 *func_80080040(f32 *out, f32 *a, f32 *b);
f32 *func_8007FEE0(f32 *out, f32 *a, f32 *b);
void func_801A9AB0_ovl_0EBBB0(f32 a, f32 b, f32 *p, f32 *q, f32 *axis, f32 c, s32 d);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A07D0_ovl_0EBBB0);

void func_801A12F0_ovl_0EBBB0(void) {
    D_8018F55B = 0;
    D_8018F55C = 0;
    D_8018F55E = 0;
    D_8018F53F = D_8018F481 & 3;
    func_801A499C_ovl_0EBBB0();
}

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A1334_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A1B78_ovl_0EBBB0);

void func_801A363C_ovl_0EBBB0(void) {
    nuGfxTaskAllEndWait();
    func_80079618(0x1E39DCE, -0x11);
    func_80079618(0x203C53E, -0x11);
    func_80079618(0x2092506, -0x11);
}

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A3688_ovl_0EBBB0);

/* Inserts n into the draw-order tree: by key (+0x10) ascending, then depth (+0x8) descending */
Tree0E *func_801A382C_ovl_0EBBB0(Tree0E *root, Tree0E *n) {
    if (root != NULL) {
        if (FIELDX(n, u16, 0x10) == FIELDX(root, u16, 0x10) ? FIELDX(n, f32, 8) > FIELDX(root, f32, 8)
                                                           : FIELDX(n, u16, 0x10) < FIELDX(root, u16, 0x10)) {
            root->left = func_801A382C_ovl_0EBBB0(root->left, n);
        } else {
            root->right = func_801A382C_ovl_0EBBB0(root->right, n);
        }
    } else {
        root = n;
    }
    return root;
}

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A38B4_ovl_0EBBB0);

/* Frees a binary tree */
void func_801A3A5C_ovl_0EBBB0(Tree0E *n) {
    if (n != NULL) {
        func_801A3A5C_ovl_0EBBB0(n->left);
        func_801A3A5C_ovl_0EBBB0(n->right);
        HFree(n);
    }
}

/* Builds the axis perpendicular to (q - p) within the plane of the up vector at 0x2C, then draws */
void func_801A3A9C_ovl_0EBBB0(s32 arg, u8 *o) {
    f32 d[3];
    f32 c[3];
    f32 n[3];

    func_80080040(d, (f32 *)(o + 0x20), (f32 *)(o + 0x14));
    func_8007FEE0(c, (f32 *)(o + 0x2C), d);
    func_8007FEE0(n, d, c);
    func_801A9AB0_ovl_0EBBB0(FIELDX(o, f32, 0), FIELDX(o, f32, 4), (f32 *)(o + 0x14), (f32 *)(o + 0x20), n,
                             FIELDX(o, f32, 0xC), arg);
}

/* Whether a box (8 corners) is at least partly inside the view: fails if all corners are behind any of the 4 side planes */
#ifdef NON_MATCHING
/* GCC biases the plane pointer (+80); the original keeps offsets 72..80 */
s32 func_801A3B4C_ovl_0EBBB0(f32 *cam, f32 (*pts)[3]) {
    f32 x = cam[0];
    f32 y = cam[1];
    f32 z = cam[2];
    s32 k;
    s32 i;

    for (k = 0; k < 4; k++, cam += 3) {
        f32 nx = cam[18];
        f32 ny = cam[19];
        f32 nz = cam[20];

        for (i = 0; i < 8; i++) {
            if ((pts[i][0] - x) * nx + (pts[i][1] - y) * ny + (pts[i][2] - z) * nz >= 0.0f) {
                break;
            }
        }
        if (i == 8) {
            return 0;
        }
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/ED530", func_801A3B4C_ovl_0EBBB0);
#endif

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A3BEC_ovl_0EBBB0);

/* Relocates n loaded tables by delta: each table pointer, its 10 entries and the word each entry points at */
#ifdef NON_MATCHING
/* Inner-loop address reuse differs. */
void func_801A3E30_ovl_0EBBB0(s32 *tab, s32 n, s32 delta) {
    s32 *end = tab + n;
    s32 j;

    for (; tab < end; tab++) {
        *tab += delta;
        for (j = 0; j < 10; j++) {
            if (((s32 *)*tab)[j] != 0) {
                ((s32 *)*tab)[j] += delta;
                *(s32 *)((s32 *)*tab)[j] += delta;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/ED530", func_801A3E30_ovl_0EBBB0);
#endif

/* Vec3f {0, 1, 0} + pad (rodata splat leaves unmigrated) */
__asm__(".section .rodata\n.global D_801AD220_ovl_0EBBB0\nD_801AD220_ovl_0EBBB0:\n.word 0x00000000, 0x3F800000, 0, 0\n.section .text\n");

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A3EA8_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A4100_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A4204_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A45F4_ovl_0EBBB0);

/* Sky state from the hour (D_8018F481): next of 8 colour pairs and an angle (hour * 20 mod 5400) */
void func_801A499C_ovl_0EBBB0(void) {
    u8 k = (D_8018F481 + 1) & 7;

    D_8018F540 = k;
    D_8018F542 = D_801ABA70_ovl_0EBBB0[k].a;
    D_8018F544 = D_801ABA70_ovl_0EBBB0[k].b;
    D_8018F546 = (D_8018F481 * 20) % 5400;
}

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A4A38_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A4CE0_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A4FF4_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A5184_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A5718_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A597C_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A5B0C_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A5F38_ovl_0EBBB0);

/* RGB lerp from `from` to `to` as x goes lo..hi (clamped), written as bytes (x256, capped at 255) */
void func_801A6284_ovl_0EBBB0(s32 lo, s32 hi, s32 x, f32 *from, f32 *to, u8 *out) {
    s32 i;
    s32 c;
    f32 v;

    if (x < lo) {
        x = lo;
    }
    if (hi < x) {
        x = hi;
    }
    for (i = 0; i < 3; i++) {
        v = to[i];
        if (v != from[i]) {
            v = (v - from[i]) / (hi - lo) * (x - lo) + from[i];
        }
        c = v * 256.0f;
        if (c >= 256) {
            c = 255;
        }
        out[i] = c;
    }
}

/* Same as func_801A6284 with float bounds */
void func_801A633C_ovl_0EBBB0(f32 lo, f32 hi, f32 x, f32 *from, f32 *to, u8 *out) {
    s32 i;
    s32 c;
    f32 v;

    if (x < lo) {
        x = lo;
    }
    if (hi < x) {
        x = hi;
    }
    for (i = 0; i < 3; i++) {
        v = to[i];
        if (v != from[i]) {
            v = (v - from[i]) / (hi - lo) * (x - lo) + from[i];
        }
        c = v * 256.0f;
        if (c >= 256) {
            c = 255;
        }
        out[i] = c;
    }
}

s32 func_801A63F4_ovl_0EBBB0(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A63FC_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A66C8_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A69A4_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A6A78_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A6E3C_ovl_0EBBB0);

void func_801A7130_ovl_0EBBB0(s32 a, s32 b) {
    D_801AD580_ovl_0EBBB0 = a;
    D_801AD584_ovl_0EBBB0 = b;
}

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A7150_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A7754_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A7AA0_ovl_0EBBB0);

/* Whether b's fractional part is larger than a's */
s32 func_801A7D44_ovl_0EBBB0(f32 a, f32 b) {
    a -= func_8009D3E0(a);
    b -= func_8009D3E0(b);
    if (b <= a) {
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A7D9C_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A81A4_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A8448_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A86F0_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A886C_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A8A64_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A8C5C_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A8E64_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A906C_ovl_0EBBB0);

void func_801A9304_ovl_0EBBB0(void) {
    Gfx *g;

    g = D_800E9BA0++;
    g->w0 = 0xE7000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xF2000000 | (((D_801ABA58_ovl_0EBBB0->w104 >> 1) & 0x7F) << 12);
    g->w1 = 0x7C0FC;
    g = D_800E9BA0++;
    g->w0 = 0xFA000000;
    g->w1 = (FIELDX(D_801ABA58_ovl_0EBBB0, u8, 0x157) << 24) | (FIELDX(D_801ABA58_ovl_0EBBB0, u8, 0x158) << 16) |
            (FIELDX(D_801ABA58_ovl_0EBBB0, u8, 0x159) << 8) | FIELDX(D_801ABA58_ovl_0EBBB0, u8, 0x15A);
}

#ifdef NON_MATCHING
/* display-list pointer updates are scheduled after the command stores */
void func_801A93A4_ovl_0EBBB0(void) {
    Gfx *g;

    g = D_800E9BA0++;
    g->w0 = 0xE7000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xFA000000;
    g->w1 = (u8)(u32)(FIELDX(D_801ABA58_ovl_0EBBB0, f32, 0x15C) * 255.0f);
}
#else
INCLUDE_ASM("asm/nonmatchings/ED530", func_801A93A4_ovl_0EBBB0);
#endif

void func_801A9438_ovl_0EBBB0(void) {
    Gfx *g;

    g = D_800E9BA0++;
    g->w0 = 0xE7000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xF2000000 | (((D_801ABA58_ovl_0EBBB0->w104 >> 1) & 0x7F) << 12);
    g->w1 = 0;
}

void func_801A9490_ovl_0EBBB0(void) {
    Gfx *g = D_800E9BA0;
    Scene0E *s = D_801ABA58_ovl_0EBBB0;

    D_800E9BA0 = g + 1;
    g->w0 = 0xE7000000;
    D_800E9BA0 = g + 2;
    g->w1 = 0;
    g[1].w0 = 0xFA000000;
    g[1].w1 = (s->r << 24) | (s->g << 16) | (s->b << 8) | 0xFF;
}

void func_801A94F8_ovl_0EBBB0(void) {
    s32 k = (f32)(D_801ABA58_ovl_0EBBB0->w104 & 0x1FF) / 512.0f * 340.0f;

    D_8018F480 = 0;
    func_80197FA4(0x2093576, 5, D_801AC4D0_ovl_0EBBB0[k]);
}

void func_801A9570_ovl_0EBBB0(void) {
    guRotateF(&D_800E7AD0[2], D_801ABA58_ovl_0EBBB0->f10C, 0.0f, 0.0f, 1.0f);
    guMtxCatF(&D_800E7AD0[2], &D_800C4AD8[2], &D_800C4AD8[2]);
}
