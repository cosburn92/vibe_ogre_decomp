#include "common.h"
#include "chunk.h"
#include "heap.h"

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
    /* 0x000 */ u8 unk000[0x5C];
    /* 0x05C */ f32 fov;
    /* 0x060 */ u8 unk060[0x10];
    /* 0x070 */ f32 eye[3];
    /* 0x07C */ f32 at[3];
    /* 0x088 */ f32 up[3];
    /* 0x094 */ u8 unk094[0x70];
    /* 0x104 */ s32 w104;
    /* 0x108 */ u8 unk108[4];
    /* 0x10C */ f32 f10C;
    /* 0x110 */ u8 unk110[0xC];
    /* 0x11C */ void *sky; /* 32x64 RGBA16 sky texture */
    /* 0x120 */ void *tex120; /* 32x32 I4 haze texture */
    /* 0x124 */ u8 unk124[0x2A];
    /* 0x14E */ u8 r;
    /* 0x14F */ u8 g;
    /* 0x150 */ u8 b;
    /* 0x151 */ u8 unk151[0xB];
    /* 0x15C */ f32 f15C;
} Scene0E;

extern Gfx *D_800E9BA0;
extern u8 D_8018F481;
extern u8 D_8018F480;
extern u8 D_8018F53F;
extern u8 D_8018F55B;
extern u16 D_8018F55C;
extern u16 D_8018F55E;
extern u8 D_8018F55A;
extern s32 D_801AD580_ovl_0EBBB0;
extern f32 D_801AD584_ovl_0EBBB0;
extern Scene0E *D_801ABA58_ovl_0EBBB0;
extern u8 D_801AC4D0_ovl_0EBBB0[];
extern f32 D_800E7AD0[];
extern f32 D_800C4AD8[];

void nuGfxTaskAllEndWait(void);
void func_80079618();
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
extern u8 D_8018F56D;
typedef struct {
    f32 t;
    f32 v;
    f32 out; /* outgoing tangent */
    f32 in;  /* incoming tangent */
    s16 interp; /* to the next key: 0 step, 1 linear, 2 Hermite */
} CurveKey;

typedef struct {
    CurveKey *keys;
    s16 n;
    s16 slopeMode; /* 1: extrapolate along the end segment rather than the end tangent */
    s16 pre;       /* before the first key: 0 hold, 1 extrapolate, 2 loop */
    s16 post;      /* after the last key, likewise */
} Curve;
f32 func_801A7D9C_ovl_0EBBB0(Curve *c, f32 t);
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

typedef struct {
    /* 0x00 */ void *p0;
    /* 0x04 */ void *p1;
    /* 0x08 */ u8 (*mtx)[0x40];
} FbSet0E;
extern FbSet0E *D_800E9BE0;
typedef struct {
    /* 0x00 */ Tree0E link;
    /* 0x08 */ f32 dist;
    /* 0x0C */ s32 c;
    /* 0x10 */ u16 key;
    /* 0x12 */ u16 m;
    /* 0x14 */ u16 frame;
} DrawNode0E;
void guMtxXFMF(f32 mf[4][4], f32 x, f32 y, f32 z, f32 *ox, f32 *oy, f32 *oz);
void guMtxXFML(void *m, f32 x, f32 y, f32 z, f32 *ox, f32 *oy, f32 *oz);
f32 sqrtf(f32 x);

/* Adds a draw-order node for matrix m (kind 10: a float matrix of the scene, else a frame
 * matrix) keyed by key and by its distance from the camera at cam (+0x14) */
void func_801A3688_ovl_0EBBB0(Tree0E *root, u16 kind, s32 c, s16 key, u16 m, u8 *cam) {
    DrawNode0E *n = HMalloc(0x18);
    f32 x, y, z;
    f32 dx, dy, dz;

    if (kind == 10) {
        n->frame = 0;
        guMtxXFMF((void *)(FIELDX(D_801ABA58_ovl_0EBBB0, u8 *, 0xC0) + (m << 6)), 0.0f, 0.0f, 0.0f, &x, &y, &z);
    } else {
        n->frame = 1;
        guMtxXFML(D_800E9BE0->mtx[FIELDX(D_801ABA58_ovl_0EBBB0, u16 *, 0x124)[m]], 0.0f, 0.0f, 0.0f, &x, &y, &z);
    }
    dx = FIELDX(cam, f32, 0x14) - x;
    dy = FIELDX(cam, f32, 0x18) - y;
    dz = FIELDX(cam, f32, 0x1C) - z;
    n->dist = sqrtf(dx * dx + dy * dy + dz * dz);
    n->c = c;
    n->key = key;
    n->m = m;
    n->link.left = NULL;
    n->link.right = NULL;
    func_801A382C_ovl_0EBBB0(root, &n->link);
}

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

extern u16 D_800C4BE4;
void guMtxF2L(void *mf, void *m);

/* Draws the nodes of draw tree n whose key is k (in tree order): each loads its matrix (a scene
 * float matrix converted into the frame's matrix pool, or a frame matrix) and calls its list */
void func_801A38B4_ovl_0EBBB0(DrawNode0E *n, u16 k) {
    if (n != NULL) {
        D_800E9BA0->w0 = 0xE7000000;
        D_800E9BA0->w1 = 0;
        D_800E9BA0++;
        if (k != n->key) {
            if (k < n->key) {
                func_801A38B4_ovl_0EBBB0((DrawNode0E *)n->link.left, k);
            } else {
                func_801A38B4_ovl_0EBBB0((DrawNode0E *)n->link.right, k);
            }
        } else {
            func_801A38B4_ovl_0EBBB0((DrawNode0E *)n->link.left, k);
            if (n->frame == 0) {
                guMtxF2L(FIELDX(D_801ABA58_ovl_0EBBB0, u8 *, 0xC0) + (n->m << 6), D_800E9BE0->mtx[D_800C4BE4]);
                D_800E9BA0->w0 = 0xDA380003;
                D_800E9BA0++->w1 = (u32)D_800E9BE0->mtx[D_800C4BE4++] - 0x80000000;
            } else {
                D_800E9BA0->w0 = 0xDA380003;
                D_800E9BA0->w1 = (u32)D_800E9BE0->mtx[FIELDX(D_801ABA58_ovl_0EBBB0, u16 *, 0x124)[n->m]] - 0x80000000;
                D_800E9BA0++;
            }
            D_800E9BA0->w0 = 0xDE000000;
            D_800E9BA0->w1 = n->c;
            D_800E9BA0++;
            func_801A38B4_ovl_0EBBB0((DrawNode0E *)n->link.right, k);
        }
    }
}

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

extern f32 D_801AD550_ovl_0EBBB0[4][3]; /* 4x3 transform copied from m */
void _bcopy(const void *src, void *dst, s32 n);

/* Whether any of the 8 corners pts lies in front of every one of the 4 view planes of cam
 * (point at cam[0..2], normals from cam + 0x48), after transforming them by the 4x3 matrix m */
#ifdef NON_MATCHING
/* 122/143 instructions: the original hoists all twelve matrix floats and the negated camera position into registers (several held in GPRs) and keeps the empty corner loop as a counted loop */
s32 func_801A3BEC_ovl_0EBBB0(f32 *cam, f32 (*pts)[3], f32 *m) {
    s32 i;
    s32 j;
    f32 x;
    f32 y;
    f32 z;

    _bcopy(m, D_801AD550_ovl_0EBBB0, 0x30);
    for (j = 0; j < 8; j++) {
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 8; j++) {
            x = pts[j][0];
            y = pts[j][1];
            z = pts[j][2];
            if ((D_801AD550_ovl_0EBBB0[0][0] * x + D_801AD550_ovl_0EBBB0[1][0] * y + D_801AD550_ovl_0EBBB0[2][0] * z +
                 D_801AD550_ovl_0EBBB0[3][0] + -cam[0]) * cam[i * 3 + 18] +
                    (D_801AD550_ovl_0EBBB0[0][1] * x + D_801AD550_ovl_0EBBB0[1][1] * y + D_801AD550_ovl_0EBBB0[2][1] * z +
                     D_801AD550_ovl_0EBBB0[3][1] + -cam[1]) * cam[i * 3 + 19] +
                    (D_801AD550_ovl_0EBBB0[0][2] * x + D_801AD550_ovl_0EBBB0[1][2] * y + D_801AD550_ovl_0EBBB0[2][2] * z +
                     D_801AD550_ovl_0EBBB0[3][2] + -cam[2]) * cam[i * 3 + 20] >=
                0.0f) {
                break;
            }
        }
        if (j == 8) {
            return 0;
        }
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/ED530", func_801A3BEC_ovl_0EBBB0);
#endif

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

typedef struct {
    f32 v[3];
} Vec3E;
extern Vec3E D_801AD220_ovl_0EBBB0; /* default up */
extern u8 D_8018F565;

/* Samples the scene's camera curves at frame (30 fps): eye (curves 0-2), look-at (3-5), roll
 * (curve 7, turning the up vector about the view axis) and field of view (curve 6, else the
 * default at F4 + 0x18) */
void func_801A3EA8_ovl_0EBBB0(s32 frame) {
    void **c = *FIELDX(D_801ABA58_ovl_0EBBB0, void ***, 0xF0);
    Vec3E up = D_801AD220_ovl_0EBBB0;
    f32 t = (f32)frame / 30.0f;
    f32 dir[3];
    f32 side[3];
    f32 u[3];
    f32 mf[4][4];
    s32 i;

    if (FIELDX(D_801ABA58_ovl_0EBBB0, u8, 0xF8) != 0 && D_8018F565 != 0) {
        for (i = 0; i < 3; i++) {
            D_801ABA58_ovl_0EBBB0->eye[i] = func_801A7D9C_ovl_0EBBB0(c[i], t);
        }
        for (i = 0; i < 3; i++) {
            D_801ABA58_ovl_0EBBB0->at[i] = func_801A7D9C_ovl_0EBBB0(c[i + 3], t);
        }
        if (c[7] != NULL) {
            f32 a = func_801A7D9C_ovl_0EBBB0(c[7], t);

            dir[0] = D_801ABA58_ovl_0EBBB0->at[0] - D_801ABA58_ovl_0EBBB0->eye[0];
            dir[1] = D_801ABA58_ovl_0EBBB0->at[1] - D_801ABA58_ovl_0EBBB0->eye[1];
            dir[2] = D_801ABA58_ovl_0EBBB0->at[2] - D_801ABA58_ovl_0EBBB0->eye[2];
            func_8007FEE0(side, u, dir);
            func_8007FEE0(u, dir, side);
            guRotateF((f32 *)mf, a, dir[0], dir[1], dir[2]);
            guMtxXFMF(mf, u[0], u[1], u[2], &up.v[0], &up.v[1], &up.v[2]);
        }
        for (i = 0; i < 3; i++) {
            D_801ABA58_ovl_0EBBB0->up[i] = up.v[i];
        }
        if (c[6] != NULL) {
            D_801ABA58_ovl_0EBBB0->fov = func_801A7D9C_ovl_0EBBB0(c[6], t);
        } else {
            D_801ABA58_ovl_0EBBB0->fov = FIELDX(FIELDX(D_801ABA58_ovl_0EBBB0, u8 *, 0xF4), f32, 0x18);
        }
    }
}

/* Samples the ten curves of each of the n channels at time t/30 into the 0xEC value table */
#ifdef NON_MATCHING
/* The logic matches. The original eliminates the outer counter: i*40 and i*4 offsets plus an n*40 end value in five saved registers; here i stays as a counter. */
void func_801A4100_ovl_0EBBB0(s32 t, s32 n) {
    f32 time = t / 30.0f;
    s32 i;
    s32 k;
    void **c;

    if (FIELDX(D_801ABA58_ovl_0EBBB0, u8, 0xF9) == 0 || D_8018F56D == 0) {
        return;
    }
    for (i = 0; i < n; i++) {
        c = FIELDX(D_801ABA58_ovl_0EBBB0, void ***, 0xE8)[i];
        for (k = 0; k < 10; k++, c++) {
            if (*c != NULL) {
                ((f32 *)(FIELDX(D_801ABA58_ovl_0EBBB0, u8 *, 0xEC) + i * 40))[k] = func_801A7D9C_ovl_0EBBB0(*c, time);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/ED530", func_801A4100_ovl_0EBBB0);
#endif

#include "gbi_ultra.h"

/* Alpha-graded fill: rectangle x0..x1, y0..y1 in colour r,g,b. The top half is drawn in up to 240
 * bands whose alpha steps from a0 down by |a1 - a0|, the rest as one band at alpha a1 */
#ifdef NON_MATCHING
/* Same size; the original keeps y0 in s0 and the band count in t3 (ours s-registers), computes the
 * half-height before the header, re-reads 0xE4 inside the loop and masks the right edge with 0xFFC */
void func_801A4204_ovl_0EBBB0(u8 r, u8 g, u8 b, u8 a0, u8 a1, u16 x0, u16 y0, u16 x1, s32 y1) {
    s32 xr = x1 + 1;
    s32 yb = (u16)(y1 + 1);
    s32 mid = (u32)(y0 + yb) >> 1;
    s32 d;
    u32 cnt;
    u32 n;
    s32 i;
    s32 ytop;
    s32 ybot;

    gDPPipeSync(D_800E9BA0++);
    gDPPipeSync(D_800E9BA0++);
    { Gfx *_g = D_800E9BA0++; _g->w0 = 0xE3000A01; _g->w1 = 0; } /* 1-cycle */
    gDPPipeSync(D_800E9BA0++);
    { Gfx *_g = D_800E9BA0++; _g->w0 = 0xD9000000; _g->w1 = 0; }
    { Gfx *_g = D_800E9BA0++; _g->w0 = 0xFCFFFFFF; _g->w1 = 0xFFFDF6FB; }
    { Gfx *_g = D_800E9BA0++; _g->w0 = 0xE200001C; _g->w1 = 0x504340; }
    if (xr > 320) {
        xr = 320;
    }
    d = a1 - a0;
    if (d <= 0) {
        d = a0 - a1;
    }
    cnt = d + 1;
    n = cnt;
    if (n > 240) {
        n = 240;
    }
    ytop = y0;
    for (i = 0; i < n; i++) {
        ybot = (i + 1) * (mid - y0 + 1) / n + y0;
        gDPSetPrimColor(D_800E9BA0++, 0, 0, r, g, b, a0 - cnt * i / n);
        gDPPipeSync(D_800E9BA0++);
        gSPTextureRectangle(D_800E9BA0++, x0 * 4, ytop * 4, xr * 4, ybot * 4, 0, 0, 0, 0, 0);
        gDPPipeSync(D_800E9BA0++);
        ytop = ybot;
    }
    gDPSetPrimColor(D_800E9BA0++, 0, 0, r, g, b, a1);
    gDPPipeSync(D_800E9BA0++);
    gSPTextureRectangle(D_800E9BA0++, x0 * 4, ytop * 4, xr * 4, yb * 4, 0, 0, 0, 0, 0);
    gDPPipeSync(D_800E9BA0++);
    gDPPipeSync(D_800E9BA0++);
}
#else
INCLUDE_ASM("asm/nonmatchings/ED530", func_801A4204_ovl_0EBBB0);
#endif

s32 func_8009C7CC(void);

/* Third of three random draws */
#define RAND3() (func_8009C7CC(), func_8009C7CC(), func_8009C7CC())

/* Flicker state machine: D_8018F55B steps through dark wait (0), choose (1), fade in over
 * D_8018F55E frames (2), lit wait (3), choose (4), fade out (5); D_8018F55A is the level 0..255
 * and D_8018F55C the frame counter, reloaded with a random 0x100..0x600 wait */
void func_801A45F4_ovl_0EBBB0(void) {
    u8 unused[0xB0]; /* only sizes the frame */

    if (D_8018F55C >= 0x800 || D_8018F55E >= 0x800) {
        D_8018F55A = 0;
        D_8018F55B = 0xFF;
    }
    if (FIELDX(D_801ABA58_ovl_0EBBB0, u8, 0x139) != 0) {
        return;
    }
    switch (D_8018F55B) {
        case 0:
            D_8018F55A = 0;
            if (D_8018F55C != 0) {
                D_8018F55C--;
            } else {
                D_8018F55B++;
            }
            break;
        case 1:
            D_8018F55A = 0;
            do {
                D_8018F55C = RAND3() & 0x7FF;
            } while (D_8018F55C < 0x100 || D_8018F55C > 0x600);
            if (RAND3() & 4) {
                D_8018F55B--;
            } else {
                D_8018F55B++;
                D_8018F55E = D_8018F55C;
                D_8018F55C = 0;
            }
            break;
        case 2:
            if (D_8018F55C < D_8018F55E) {
                D_8018F55C++;
                D_8018F55A = D_8018F55C * 255 / D_8018F55E;
            } else {
                do {
                    D_8018F55C = RAND3() & 0x7FF;
                } while (D_8018F55C < 0x100 || D_8018F55C > 0x600);
                D_8018F55A = 0xFF;
                D_8018F55B++;
            }
            break;
        case 3:
            D_8018F55A = 0xFF;
            if (D_8018F55C != 0) {
                D_8018F55C--;
            } else {
                D_8018F55B++;
            }
            break;
        case 4:
            D_8018F55A = 0xFF;
            do {
                D_8018F55C = RAND3() & 0x7FF;
            } while (D_8018F55C < 0x100 || D_8018F55C > 0x600);
            if (RAND3() & 8) {
                D_8018F55B--;
            } else {
                D_8018F55B++;
                D_8018F55E = D_8018F55C = D_8018F55C; /* the store to D_8018F55C is in the original */
            }
            break;
        case 5:
            if (D_8018F55C != 0) {
                D_8018F55C--;
                D_8018F55A = D_8018F55C * 255 / D_8018F55E;
            } else {
                do {
                    D_8018F55C = RAND3() & 0x7FF;
                } while (D_8018F55C < 0x100 || D_8018F55C > 0x600);
                D_8018F55A = 0;
                D_8018F55B = 0;
            }
            break;
        default:
            D_8018F55A = 0;
            D_8018F55B = 0;
            D_8018F55C = 0;
            D_8018F55E = 0;
            break;
    }
}

/* Sky state from the hour (D_8018F481): next of 8 colour pairs and an angle (hour * 20 mod 5400) */
void func_801A499C_ovl_0EBBB0(void) {
    u8 k = (D_8018F481 + 1) & 7;

    D_8018F540 = k;
    D_8018F542 = D_801ABA70_ovl_0EBBB0[k].a;
    D_8018F544 = D_801ABA70_ovl_0EBBB0[k].b;
    D_8018F546 = (D_8018F481 * 20) % 5400;
}

s32 func_8009C7CC(void); /* rand */
extern s32 D_801ABA90_ovl_0EBBB0; /* 16.16, high half read as u16 */
extern u16 D_801ABA92_ovl_0EBBB0;
extern s32 D_801ABA94_ovl_0EBBB0;
extern u16 D_801ABA96_ovl_0EBBB0;
extern u8 D_800E7A90[];
extern s32 D_8018F818[][3];

static inline u32 Rand30_0E(void) {
    u32 a = func_8009C7CC();
    u32 b = func_8009C7CC();

    return ((a << 18) & 0xC000000) | (b << 15) | func_8009C7CC();
}

/* Sky colour drift (maps flagged 0x400): every 5400 ticks a new random target pair (7 is rare);
 * the current pair (D_8018F542 / D_8018F544, 16.16 steps of 0x2321) moves toward it, the first
 * kept at most 20 below the second */
#ifdef NON_MATCHING
/* 170/170, 12 words: in the retry loop the original hoists the constant 7 before the 0xC000000 mask (s2/s1 set in the other order) */
void func_801A4A38_ovl_0EBBB0(void) {
    if (FIELDX(D_801ABA58_ovl_0EBBB0, u8, 0x139) == 0 && (D_8018F818[D_800E7A90[0x28]][0] & 0x400)) {
        D_8018F540 &= 7;
        D_8018F546 %= 5400;
        if (D_8018F546 == 0) {
            D_8018F546 = Rand30_0E() % 5400 + 1;
            do {
                D_8018F540 = Rand30_0E() & 7;
            } while (D_8018F540 == 7 && (Rand30_0E() & 6));
        }
        D_801ABA90_ovl_0EBBB0 = D_801ABA92_ovl_0EBBB0 | (D_8018F542 << 16);
        D_801ABA94_ovl_0EBBB0 = D_801ABA96_ovl_0EBBB0 | (D_8018F544 << 16);
        if (D_8018F542 < D_801ABA70_ovl_0EBBB0[D_8018F540].a) {
            D_801ABA90_ovl_0EBBB0 += 0x2321;
        } else if (D_801ABA70_ovl_0EBBB0[D_8018F540].a < D_8018F542) {
            D_801ABA90_ovl_0EBBB0 -= 0x2321;
        }
        if (D_8018F544 < D_801ABA70_ovl_0EBBB0[D_8018F540].b) {
            D_801ABA94_ovl_0EBBB0 += 0x2321;
        } else if (D_801ABA70_ovl_0EBBB0[D_8018F540].b < D_8018F544) {
            D_801ABA94_ovl_0EBBB0 -= 0x2321;
        }
        D_8018F542 = *(u16 *)&D_801ABA90_ovl_0EBBB0;
        D_8018F544 = *(u16 *)&D_801ABA94_ovl_0EBBB0;
        if (*(u16 *)&D_801ABA94_ovl_0EBBB0 - 20 < *(u16 *)&D_801ABA90_ovl_0EBBB0) {
            D_8018F542 = *(u16 *)&D_801ABA94_ovl_0EBBB0 - 20;
        }
        D_8018F546--;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/ED530", func_801A4A38_ovl_0EBBB0);
#endif

f64 func_8009C9A0(f64);
extern u32 D_8018F530;
extern u8 D_8018F557;
extern u8 D_8018F558;
extern u8 D_8018F559;

/* Fog for the scene: brightness 0.35 * sin(angle 0x12C) + 0.55 clamped to 0.55..0.9 scales the
 * base fog colour (channels scaled by D_8018F530 / 65536, at least 0x20); fog range D_8018F542..D_8018F544 */
#ifdef NON_MATCHING
/* same size; in the fog colour word the green and blue channels swap v1/a0 and the blue shift is scheduled later */
void func_801A4CE0_ovl_0EBBB0(void) {
    f32 f;
    u32 r;
    u32 g;
    u32 b;
    s32 fm;
    s32 fo;
    u8 cr;
    u8 cg;
    u8 cb;

    f = func_8009C9A0(FIELDX(D_801ABA58_ovl_0EBBB0, f32, 0x12C) * 0.017453292519943295) * 0.35f + 0.55f;
    if (f > 0.9f) {
        f = 0.9f;
    } else if (f < 0.55f) {
        f = 0.55f;
    }
    r = D_8018F557 * f;
    g = D_8018F558 * f;
    b = D_8018F559 * f;
    fm = 128000 / (D_8018F544 - D_8018F542);
    fo = (500 - D_8018F542) * 256 / (D_8018F544 - D_8018F542);
    { Gfx *_g = D_800E9BA0++; _g->w0 = 0xE7000000; _g->w1 = 0; }
    { Gfx *_g = D_800E9BA0++; _g->w0 = 0xDB080000; _g->w1 = (fm << 16) | (fo & 0xFFFF); }
    {
        Gfx *_g = D_800E9BA0++;
        u32 w;
        _g->w0 = 0xF8000000;
        cr = (r * D_8018F530) >> 16;
        if (cr < 0x20) {
            cr = 0x20;
        }
        w = cr << 24;
        cg = (g * D_8018F530) >> 16;
        if (cg < 0x20) {
            cg = 0x20;
        }
        cb = (b * D_8018F530) >> 16;
        w |= cg << 16;
        if (cb < 0x20) {
            cb = 0x20;
        }
        _g->w1 = w | (cb << 8) | 0xFF;
    }
    { Gfx *_g = D_800E9BA0++; _g->w0 = 0xE7000000; _g->w1 = 0; }
}
#else
INCLUDE_ASM("asm/nonmatchings/ED530", func_801A4CE0_ovl_0EBBB0);
#endif

typedef struct {
    s32 m[16];
} MtxE;
typedef struct {
    u8 unk0[8];
    MtxE *mtx;
} DynE;
extern u16 D_800C4BE4;
extern u8 D_801ABAD8_ovl_0EBBB0[];
void func_800987E0(MtxE *m);

/* Identity matrix from the frame's pool, then the 32x64 RGBA16 sky texture (scene +0x11C)
 * and display list D_801ABAD8 */
void func_801A4FF4_ovl_0EBBB0(DynE *d) {
    func_800987E0(&d->mtx[D_800C4BE4]);
    gDPPipeSync(D_800E9BA0++);
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xDA380003;
        _g->w1 = (u32)&d->mtx[D_800C4BE4++] - 0x80000000;
    }
    gDPLoadTextureBlock(D_800E9BA0++, D_801ABA58_ovl_0EBBB0->sky, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64,
                        0, 0, 0, 5, 6, 14, 15);
    gSPDisplayList(D_800E9BA0++, D_801ABAD8_ovl_0EBBB0);
}

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A5184_ovl_0EBBB0);

extern u32 D_8018F530; /* light level */
extern u8 D_801ABD58_ovl_0EBBB0[];
void func_80098C20(void *m, f32 x, f32 y, f32 z); /* guTranslate */

/* Ground shadow/haze: translated to (x, 0, z), the scene's 32x32 I4 texture (+0x120) tinted by
 * the light level (each channel at least 0x20), alpha 0xBE */
#ifdef NON_MATCHING
/* 153/153 instructions, 114 words differ in scheduling: the original batches the display-list stores after computing the tint and matrix pointer */
void func_801A5718_ovl_0EBBB0(DynE *d, f32 x, f32 z) {
    u32 r;
    u32 g;
    u32 b;

    func_80098C20(&d->mtx[D_800C4BE4], x, 0.0f, z);
    gDPPipeSync(D_800E9BA0++);
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xDA380003;
        _g->w1 = (u32)&d->mtx[D_800C4BE4++] - 0x80000000;
    }
    gDPLoadTextureBlock_4b(D_800E9BA0++, D_801ABA58_ovl_0EBBB0->tex120, G_IM_FMT_I, 32, 32, 0,
                           G_TX_CLAMP, G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    r = D_8018F530 * 0xB9 >> 16;
    if ((u8)r < 0x20) {
        r = 0x20;
    }
    g = D_8018F530 * 0x4B >> 15;
    if ((u8)g < 0x20) {
        g = 0x20;
    }
    b = D_8018F530 * 0x23 >> 16;
    if ((u8)b < 0x20) {
        b = 0x20;
    }
    gDPSetPrimColor(D_800E9BA0++, 0, 0, r, g, b, 0xBE);
    gSPDisplayList(D_800E9BA0++, D_801ABD58_ovl_0EBBB0);
    gDPPipeSync(D_800E9BA0++);
}
#else
INCLUDE_ASM("asm/nonmatchings/ED530", func_801A5718_ovl_0EBBB0);
#endif

void func_80098D00(f32 mf[4][4], f32 x, f32 y, f32 z); /* guTranslateF */
void guMtxXFMF(f32 mf[4][4], f32 x, f32 y, f32 z, f32 *ox, f32 *oy, f32 *oz);
void func_80080210(f32 *out, f32 *a, f32 *v, f32 b, f32 c);
void func_8007FFD0(f32 *v);
void func_80080190(f32 *v, f32 s);

/* For an angle (0x12C) within 15-165 degrees, rotates a point 50 units out into view and, when
 * it lies in front, sets flag 0x138 and stores its projected position (0x130/0x134) */
void func_801A597C_ovl_0EBBB0(void) {
    f32 m[4][4];
    f32 r[4][4];
    f32 out[4];
    f32 v[3];

    D_801ABA58_ovl_0EBBB0->unk110[0x28] = 0;
    if (FIELDX(D_801ABA58_ovl_0EBBB0, f32, 0x12C) < 15.0f || FIELDX(D_801ABA58_ovl_0EBBB0, f32, 0x12C) > 165.0f) {
        return;
    }
    guRotateF((f32 *)m, 60.0f, 1.0f, 0.0f, 0.0f);
    guRotateF((f32 *)r, FIELDX(D_801ABA58_ovl_0EBBB0, f32, 0x12C), 0.0f, -1.0f, 0.0f);
    guMtxCatF((f32 *)r, (f32 *)m, (f32 *)m);
    func_80098D00(r, -50.0f, 0.0f, 0.0f);
    guMtxCatF((f32 *)r, (f32 *)m, (f32 *)m);
    guMtxXFMF(m, 0.0f, 0.0f, 0.0f, &v[0], &v[1], &v[2]);
    if (v[1] > 0.0f) {
        func_80080210(out, (f32 *)&D_801ABA58_ovl_0EBBB0->unk000[0x18], v, FIELDX(D_801ABA58_ovl_0EBBB0, f32, 0x1C),
                      v[1]);
        D_801ABA58_ovl_0EBBB0->unk110[0x28] = 1;
        FIELDX(D_801ABA58_ovl_0EBBB0, f32, 0x130) = out[0];
        FIELDX(D_801ABA58_ovl_0EBBB0, f32, 0x134) = out[2];
        func_8007FFD0(v);
        func_80080190(v, 100.0f);
    }
}

extern f32 D_801AC0D8_ovl_0EBBB0[8];
extern f32 D_801ABDD8_ovl_0EBBB0[8][2][4][3]; /* second name: D_801ABE08 - 0x30 */
typedef struct {
    /* 0x00 */ u8 acol[4];
    /* 0x04 */ u8 acolc[4];
    /* 0x08 */ u8 col[4];
    /* 0x0C */ u8 colc[4];
    /* 0x10 */ s8 dir[4];
} Lights0E;
extern Lights0E D_801ABA40_ovl_0EBBB0;
extern u8 D_8018F557;
extern u8 D_8018F558;
extern u8 D_8018F559;
void func_801A633C_ovl_0EBBB0(f32 lo, f32 hi, f32 x, f32 *from, f32 *to, u8 *out);

/* Sun light from the sun angle (0x12C): direction (rotated -60 about x, by the angle about y,
 * 50 out, normalised to 119) into D_801ABA50..52, and two colour pairs lerped between the
 * surrounding angle keys D_801AC0D8 (scaled by the light level, each channel at least 0x20) */
void func_801A5B0C_ovl_0EBBB0(void) {
    f32 m[4][4];
    f32 r[4][4];
    f32 v[3];
    u8 c[3];
    s32 i;
    s32 j;
    f32 hi;
    u32 k;

    for (i = 7; i > 0; i--) {
        if (D_801AC0D8_ovl_0EBBB0[i] <= FIELDX(D_801ABA58_ovl_0EBBB0, f32, 0x12C)) {
            break;
        }
    }
    for (j = 1; j < 8; j++) {
        if (FIELDX(D_801ABA58_ovl_0EBBB0, f32, 0x12C) <= D_801AC0D8_ovl_0EBBB0[j]) {
            break;
        }
    }
    guRotateF((f32 *)m, -60.0f, 1.0f, 0.0f, 0.0f);
    guRotateF((f32 *)r, FIELDX(D_801ABA58_ovl_0EBBB0, f32, 0x12C), 0.0f, 1.0f, 0.0f);
    guMtxCatF((f32 *)r, (f32 *)m, (f32 *)m);
    func_80098D00(r, -50.0f, 0.0f, 0.0f);
    guMtxCatF((f32 *)r, (f32 *)m, (f32 *)m);
    guMtxXFMF(m, 0.0f, 0.0f, 0.0f, &v[0], &v[1], &v[2]);
    func_8007FFD0(v);
    j &= 7;
    func_80080190(v, 119.0f);
    D_801ABA40_ovl_0EBBB0.dir[0] = v[0];
    D_801ABA40_ovl_0EBBB0.dir[1] = v[1];
    D_801ABA40_ovl_0EBBB0.dir[2] = v[2];

    hi = D_801AC0D8_ovl_0EBBB0[j];
    if (hi < D_801AC0D8_ovl_0EBBB0[i]) {
        hi += 360.0f;
    }
    func_801A633C_ovl_0EBBB0(D_801AC0D8_ovl_0EBBB0[i], hi, FIELDX(D_801ABA58_ovl_0EBBB0, f32, 0x12C),
                             D_801ABDD8_ovl_0EBBB0[i][1][D_8018F53F], D_801ABDD8_ovl_0EBBB0[j][1][D_8018F53F], c);
    k = c[0] * D_8018F530 >> 16;
    if ((u8)k < 0x20) {
        k = 0x20;
    }
    D_801ABA40_ovl_0EBBB0.acolc[0] = k;
    D_801ABA40_ovl_0EBBB0.acol[0] = k;
    k = c[1] * D_8018F530 >> 16;
    if ((u8)k < 0x20) {
        k = 0x20;
    }
    D_801ABA40_ovl_0EBBB0.acolc[1] = k;
    D_801ABA40_ovl_0EBBB0.acol[1] = k;
    k = c[2] * D_8018F530 >> 16;
    if ((u8)k < 0x20) {
        k = 0x20;
    }
    D_801ABA40_ovl_0EBBB0.acolc[2] = k;
    D_801ABA40_ovl_0EBBB0.acol[2] = k;

    hi = D_801AC0D8_ovl_0EBBB0[j];
    if (hi < D_801AC0D8_ovl_0EBBB0[i]) {
        hi += 360.0f;
    }
    func_801A633C_ovl_0EBBB0(D_801AC0D8_ovl_0EBBB0[i], hi, FIELDX(D_801ABA58_ovl_0EBBB0, f32, 0x12C),
                             D_801ABDD8_ovl_0EBBB0[i][0][D_8018F53F], D_801ABDD8_ovl_0EBBB0[j][0][D_8018F53F], c);
    k = c[0] * D_8018F530 >> 16;
    if ((u8)k < 0x20) {
        k = 0x20;
    }
    D_801ABA40_ovl_0EBBB0.colc[0] = k;
    D_801ABA40_ovl_0EBBB0.col[0] = k;
    k = c[1] * D_8018F530 >> 16;
    if ((u8)k < 0x20) {
        k = 0x20;
    }
    D_801ABA40_ovl_0EBBB0.colc[1] = k;
    D_801ABA40_ovl_0EBBB0.col[1] = k;
    k = c[2] * D_8018F530 >> 16;
    if ((u8)k < 0x20) {
        k = 0x20;
    }
    D_801ABA40_ovl_0EBBB0.colc[2] = k;
    D_801ABA40_ovl_0EBBB0.col[2] = k;
    D_8018F557 = c[0];
    D_8018F558 = c[1];
    D_8018F559 = c[2];
}

extern u16 D_801AC34A_ovl_0EBBB0[];
extern u16 D_801AC356_ovl_0EBBB0[];
extern f32 D_801AC1E0_ovl_0EBBB0[2][5][3];
extern f32 D_801AC258_ovl_0EBBB0[5][3];
extern f32 D_801AC294_ovl_0EBBB0[5][3];
extern f32 D_801AC2D0_ovl_0EBBB0[5][3];
extern f32 D_801AC30C_ovl_0EBBB0[5][3];
extern u8 D_801AC104_ovl_0EBBB0[];
extern u8 D_801AC1A0_ovl_0EBBB0[];
extern Gfx D_801AC138_ovl_0EBBB0[];
void func_801A6284_ovl_0EBBB0(s32 lo, s32 hi, s32 x, f32 *from, f32 *to, u8 *out);

/* Time-of-day colours: picks the key interval containing t, lerps the light colours
 * (D_801AC104) and four scene colours, then emits the light matrix and display list */
void func_801A5F38_ovl_0EBBB0(s32 t) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        if (t < D_801AC34A_ovl_0EBBB0[i]) {
            break;
        }
    }
    j = i;
    if (i < 4) {
        j++;
    }
    func_801A6284_ovl_0EBBB0(D_801AC34A_ovl_0EBBB0[i - 1], D_801AC34A_ovl_0EBBB0[j - 1], t,
                             D_801AC1E0_ovl_0EBBB0[0][i], D_801AC1E0_ovl_0EBBB0[0][j], D_801AC104_ovl_0EBBB0);
    _bcopy(D_801AC104_ovl_0EBBB0, D_801AC104_ovl_0EBBB0 + 0x10, 3);
    func_801A6284_ovl_0EBBB0(D_801AC34A_ovl_0EBBB0[i - 1], D_801AC34A_ovl_0EBBB0[j - 1], t,
                             D_801AC1E0_ovl_0EBBB0[1][i], D_801AC1E0_ovl_0EBBB0[1][j], D_801AC104_ovl_0EBBB0 + 0x20);
    _bcopy(D_801AC104_ovl_0EBBB0 + 0x20, D_801AC104_ovl_0EBBB0 + 0x30, 3);
    gDPPipeSync(D_800E9BA0++);
    guMtxF2L(D_801AC1A0_ovl_0EBBB0, D_800E9BE0->mtx[D_800C4BE4]);
    func_800987E0((MtxE *)D_800E9BE0->mtx[D_800C4BE4]);
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xDA380003;
        _g->w1 = (u32)D_800E9BE0->mtx[D_800C4BE4++] - 0x80000000;
    }
    gSPDisplayList(D_800E9BA0++, D_801AC138_ovl_0EBBB0);

    for (i = 0; i < 4; i++) {
        if (t < D_801AC356_ovl_0EBBB0[i]) {
            break;
        }
    }
    j = i;
    if (i < 4) {
        j++;
    }
    func_801A6284_ovl_0EBBB0(D_801AC356_ovl_0EBBB0[i - 1], D_801AC356_ovl_0EBBB0[j - 1], t,
                             D_801AC258_ovl_0EBBB0[i], D_801AC258_ovl_0EBBB0[j], D_801ABA58_ovl_0EBBB0->unk124 + 0x24);
    func_801A6284_ovl_0EBBB0(D_801AC356_ovl_0EBBB0[i - 1], D_801AC356_ovl_0EBBB0[j - 1], t,
                             D_801AC294_ovl_0EBBB0[i], D_801AC294_ovl_0EBBB0[j], D_801ABA58_ovl_0EBBB0->unk124 + 0x27);
    func_801A6284_ovl_0EBBB0(D_801AC356_ovl_0EBBB0[i - 1], D_801AC356_ovl_0EBBB0[j - 1], t,
                             D_801AC2D0_ovl_0EBBB0[i], D_801AC2D0_ovl_0EBBB0[j], D_801ABA58_ovl_0EBBB0->unk124 + 0x20);
    func_801A6284_ovl_0EBBB0(D_801AC356_ovl_0EBBB0[i - 1], D_801AC356_ovl_0EBBB0[j - 1], t,
                             D_801AC30C_ovl_0EBBB0[i], D_801AC30C_ovl_0EBBB0[j], &D_801ABA58_ovl_0EBBB0->r);
    gDPPipeSync(D_800E9BA0++);
}

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

#include "scene.h"
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern s32 D_8018F818[][3];
f32 func_801A63FC_ovl_0EBBB0(s32 slot, f32 x, f32 z);
s32 func_801A69A4_ovl_0EBBB0(u16 *grid, s32 x, s32 row);

/* Ground height at (x, z) in scene slot's height grid for maps with flag 0x8 (0 otherwise):
 * the grid cell's two triangles are interpolated (16-bit heights over 0xC-0x10) */
#ifdef NON_MATCHING
/* same size; in both branches the a0 argument move is scheduled after the index update instead of first */
f32 func_801A63FC_ovl_0EBBB0(s32 slot, f32 x, f32 z) {
    u8 *g = (u8 *)D_800E82C8[slot].slotsB[D_800E82C8[slot].unk8D];
    f32 fx;
    f32 fz;
    s32 ix;
    s32 iz;
    s32 a;
    s32 b;
    s32 c;
    f32 dx;
    f32 dz;
    f32 v;

    if (!(D_8018F818[D_800E82C8[slot].unk88][0] & 8)) {
        return 0.0f;
    }
    fx = (x - FIELD(g, f32, 4)) / (FIELD(g, f32, 8) - FIELD(g, f32, 4)) * (f32)(FIELD(g, u16, 0) - 1);
    fz = (z - FIELD(g, f32, 0x14)) / (FIELD(g, f32, 0x18) - FIELD(g, f32, 0x14)) * (f32)(FIELD(g, u16, 2) - 1);
    ix = func_8009D3E0(fx);
    iz = func_8009D3E0(fz);
    a = func_801A69A4_ovl_0EBBB0((u16 *)g, ix, iz);
    b = func_801A69A4_ovl_0EBBB0((u16 *)g, ix + 1, iz + 1);
    dz = fz - iz;
    dx = fx - ix;
    if (dz - dx >= 0.0f) {
        { s32 t = ix; ix = iz + 1; c = func_801A69A4_ovl_0EBBB0((u16 *)g, t, ix); }
        v = dx * (b - c) - (fz - ix) * (a - c) + c;
    } else {
        c = func_801A69A4_ovl_0EBBB0((u16 *)g, ++ix, iz);
        v = -(fx - ix) * (a - c) + dz * (b - c) + c;
    }
    return v / 65279.0f * (FIELD(g, f32, 0x10) - FIELD(g, f32, 0xC)) + FIELD(g, f32, 0xC);
}
#else
INCLUDE_ASM("asm/nonmatchings/ED530", func_801A63FC_ovl_0EBBB0);
#endif

/* Ground height at (x, z) in scene slot's height grid: the grid cell's two triangles are
 * interpolated (16-bit heights over 0xC-0x10); maps without flag 0x10 use func_801A63FC */
#ifdef NON_MATCHING
/* same size; as in func_801A63FC, the a0 argument move is scheduled after the index update instead of first */
f32 func_801A66C8_ovl_0EBBB0(s32 slot, f32 x, f32 z) {
    u8 *g = (u8 *)D_800E82C8[slot].slotsB[D_800E82C8[slot].unk8D];
    f32 fx;
    f32 fz;
    s32 ix;
    s32 iz;
    s32 a;
    s32 b;
    s32 c;
    f32 dx;
    f32 dz;
    f32 v;

    if (!(D_8018F818[D_800E82C8[slot].unk88][0] & 0x10)) {
        return func_801A63FC_ovl_0EBBB0(slot, x, z);
    }
    fx = (x - FIELD(g, f32, 4)) / (FIELD(g, f32, 8) - FIELD(g, f32, 4)) * (f32)(FIELD(g, u16, 0) - 1);
    fz = (z - FIELD(g, f32, 0x14)) / (FIELD(g, f32, 0x18) - FIELD(g, f32, 0x14)) * (f32)(FIELD(g, u16, 2) - 1);
    ix = func_8009D3E0(fx);
    iz = func_8009D3E0(fz);
    a = func_801A69A4_ovl_0EBBB0((u16 *)g, ix, iz);
    b = func_801A69A4_ovl_0EBBB0((u16 *)g, ix + 1, iz + 1);
    dz = fz - iz;
    dx = fx - ix;
    if (dz - dx >= 0.0f) {
        { s32 t = ix; ix = iz + 1; c = func_801A69A4_ovl_0EBBB0((u16 *)g, t, ix); }
        v = dx * (b - c) - (fz - ix) * (a - c) + c;
    } else {
        ix++;
        c = func_801A69A4_ovl_0EBBB0((u16 *)g, ix, iz);
        v = -(fx - ix) * (a - c) + dz * (b - c) + c;
    }
    return v / 65279.0f * (FIELD(g, f32, 0x10) - FIELD(g, f32, 0xC)) + FIELD(g, f32, 0xC);
}
#else
INCLUDE_ASM("asm/nonmatchings/ED530", func_801A66C8_ovl_0EBBB0);
#endif

/* Cell x of row `row` in a run-length grid: u16 width, u16 height, row offsets at +0x1C
 * (in halfwords, from +0x1C). A word 0xFFnn repeats the following word nn times. */
/* plain inline: also inlined into func_801A6E3C */
inline s32 func_801A69A4_ovl_0EBBB0(u16 *grid, s32 x, s32 row) {
    u16 *p = &grid[14] + grid[14 + row];
    u16 w;
    u16 j;
    u16 i;

    if (x < 0 || x >= grid[0] || row < 0 || row >= grid[1]) {
        return 0;
    }
    i = 0;
    j = 0;
    while (1) {
        w = p[j++];
        if ((w >> 8) != 0xFF) {
            if (i++ < x) {
                continue;
            }
            return w;
        } else {
            i += w & 0xFF;
            if (i - 1 >= x) {
                return p[j];
            }
            j++;
        }
    }
}

typedef struct {
    /* 0x00 */ u16 *grids[10];
    /* 0x28 */ u8 pad28[4];
    /* 0x2C */ u8 grid;
    /* 0x2D */ u8 pad2D[0xA8 - 0x2D];
} SceneGrids;
extern SceneGrids D_800E8328[];

/* Heights of the four corners of grid cell (x, z) in scene slot's height grid, in the order
 * (x, z), (x+1, z), (x, z+1), (x+1, z+1); returns the index of the highest corner */
s32 func_801A6A78_ovl_0EBBB0(s32 slot, s32 x, s32 z, s32 *h) {
    u16 *g = D_800E8328[slot].grids[D_800E8328[slot].grid];
    s32 m;
    s32 r;

    m = h[0] = func_801A69A4_ovl_0EBBB0(g, x, z);
    r = 0;
    h[1] = func_801A69A4_ovl_0EBBB0(g, x + 1, z);
    if (m < h[1]) {
        r = 1;
        m = h[1];
    }
    h[2] = func_801A69A4_ovl_0EBBB0(g, x, z + 1);
    if (m < h[2]) {
        r = 2;
        m = h[2];
    }
    z++;
    x++;
    h[3] = func_801A69A4_ovl_0EBBB0(g, x, z);
    if (m < h[3]) {
        r = 3;
    }
    return r;
}

/* Heights of the three corners of triangle tri (0: x+1 corner, else z+1 corner) of grid cell
 * (x, z) in the current scene's height grid; returns the index of the highest corner */
s32 func_801A6E3C_ovl_0EBBB0(s32 tri, s32 x, s32 z, s32 *h) {
    u16 *g = D_800E8328[D_801AD580_ovl_0EBBB0].grids[D_800E8328[D_801AD580_ovl_0EBBB0].grid];
    s32 m;
    s32 r;

    m = h[0] = func_801A69A4_ovl_0EBBB0(g, x, z);
    r = 0;
    h[1] = func_801A69A4_ovl_0EBBB0(g, x + 1, z + 1);
    if (m < h[1]) {
        r = 1;
        m = h[1];
    }
    if (!tri) {
        x++;
    } else {
        z++;
    }
    h[2] = func_801A69A4_ovl_0EBBB0(g, x, z);
    if (m < h[2]) {
        r = 2;
    }
    return r;
}

void func_801A7130_ovl_0EBBB0(s32 a, s32 b) {
    D_801AD580_ovl_0EBBB0 = a;
    D_801AD584_ovl_0EBBB0 = b;
}

INCLUDE_ASM("asm/nonmatchings/ED530", func_801A7150_ovl_0EBBB0);

extern f32 D_801AD588_ovl_0EBBB0;
extern f32 D_801AD58C_ovl_0EBBB0;
extern f32 D_801AD590_ovl_0EBBB0;
extern f32 D_801AD594_ovl_0EBBB0;
extern u8 D_801AC450_ovl_0EBBB0[][2];
s32 func_801A7AA0_ovl_0EBBB0(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, s32 cx, s32 cz, s32 tri, f32 *out);

/* Walks a segment from (px, pz) through up to four grid-edge crossings (dirs: 0 = end point,
 * 1/3 = column line col/col+1, 2/4 = row line row+off/+1, 5 = diagonal) on the line
 * z = D_801AD588 * x + D_801AD58C, testing each piece against triangle ids (0xFF ends);
 * mode != 0 swaps the x/z axes. Returns 1 on the first hit */
s32 func_801A7754_ovl_0EBBB0(u8 mode, f32 px, f32 pz, f32 ax, f32 az, s32 col, s32 row, u8 *ids, u8 *dirs,
                             f32 *out) {
    f32 x;
    f32 z;
    s32 i;
    u8 id;
    s8 off;

    x = z = 0.0f;
    for (i = 0; i < 4; i++) {
        id = ids[i];
        if (id == 0xFF) {
            break;
        }
        off = D_801AC450_ovl_0EBBB0[id][0];
        switch (dirs[i]) {
            case 0:
                x = ax;
                z = az;
                break;
            case 1:
                x = col;
                z = D_801AD588_ovl_0EBBB0 * x + D_801AD58C_ovl_0EBBB0;
                break;
            case 2:
                z = row + off;
                x = (z - D_801AD58C_ovl_0EBBB0) / D_801AD588_ovl_0EBBB0;
                break;
            case 3:
                x = col + 1;
                z = D_801AD588_ovl_0EBBB0 * x + D_801AD58C_ovl_0EBBB0;
                break;
            case 4:
                z = row + off + 1;
                x = (z - D_801AD58C_ovl_0EBBB0) / D_801AD588_ovl_0EBBB0;
                break;
            case 5:
                z = row + off - col;
                x = (z - D_801AD58C_ovl_0EBBB0) / (D_801AD588_ovl_0EBBB0 - 1.0f);
                z = z + x;
                break;
        }
        if (mode == 0) {
            if (px != x || pz != z) {
                if (func_801A7AA0_ovl_0EBBB0(px, D_801AD590_ovl_0EBBB0 * px + D_801AD594_ovl_0EBBB0, pz, x,
                                             D_801AD590_ovl_0EBBB0 * x + D_801AD594_ovl_0EBBB0, z, col, row + off,
                                             (s8)D_801AC450_ovl_0EBBB0[id][1], out)) {
                    return 1;
                }
            }
        } else {
            if (px != x || pz != z) {
                if (func_801A7AA0_ovl_0EBBB0(pz, D_801AD590_ovl_0EBBB0 * px + D_801AD594_ovl_0EBBB0, px, z,
                                             D_801AD590_ovl_0EBBB0 * x + D_801AD594_ovl_0EBBB0, x, row + off, col,
                                             (s8)(D_801AC450_ovl_0EBBB0[id][1] ^ 1), out)) {
                    return 1;
                }
            }
        }
        px = x;
        pz = z;
    }
    return 0;
}

s32 func_801A6E3C_ovl_0EBBB0(s32 tri, s32 x, s32 z, s32 *h);

/* Intersects segment (x0, y0, z0) - (x1, y1, z1) with triangle tri of ground cell (cx, cz); on a
 * hit stores the point in out and returns 1 */
#ifdef NON_MATCHING
/* 157 vs 159: in the lowest-height test the original loads h[2] into v0 and copies it to v1 (two moves) */
s32 func_801A7AA0_ovl_0EBBB0(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, s32 cx, s32 cz, s32 tri, f32 *out) {
    s32 h[3];
    s32 k;
    s32 dx;
    s32 dz;
    s32 lo;
    f32 d0;
    f32 d1;
    f32 p;
    f32 t;

    if (tri == 0) {
        k = func_801A6E3C_ovl_0EBBB0(0, cx, cz, h);
        dx = h[0] - h[2];
        dz = h[2] - h[1];
    } else {
        k = func_801A6E3C_ovl_0EBBB0(1, cx, cz, h);
        dx = h[2] - h[1];
        dz = h[0] - h[2];
    }
    k = h[k];
    if (h[0] < h[1]) {
        lo = h[2];
        if (h[0] < lo) {
            lo = h[0];
        }
    } else {
        lo = h[2];
        if (h[1] < lo) {
            lo = h[1];
        }
    }
    if (k < y0 && k < y1) {
        return 0;
    }
    if (y0 < lo && y1 < lo) {
        return 0;
    }
    d0 = dx * (x0 - cx) + (y0 - h[0]) + dz * (z0 - cz);
    d1 = dx * (x1 - cx) + (y1 - h[0]) + dz * (z1 - cz);
    p = d0 * d1;
    if (p > 0.0f) {
        return 0;
    }
    if (p < 0.0f) {
        t = d0 / (d0 - d1);
        out[0] = (x1 - x0) * t + x0;
        out[1] = (y1 - y0) * t + y0;
        out[2] = (z1 - z0) * t + z0;
        return 1;
    }
    if (d0 == 0.0f) {
        out[0] = x0;
        out[1] = y0;
        out[2] = z0;
        return 1;
    }
    out[0] = x1;
    out[1] = y1;
    out[2] = z1;
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/ED530", func_801A7AA0_ovl_0EBBB0);
#endif

/* Whether b's fractional part is larger than a's */
s32 func_801A7D44_ovl_0EBBB0(f32 a, f32 b) {
    a -= func_8009D3E0(a);
    b -= func_8009D3E0(b);
    if (b <= a) {
        return 0;
    }
    return 1;
}

/* Value of a keyframe curve at time t (same code as 267750 func_80212DE0). One float x serves
 * as the segment length, the loop bounds and the Hermite offset */
f32 func_801A7D9C_ovl_0EBBB0(Curve *c, f32 t) {
    CurveKey *k;
    CurveKey *p;
    s32 lo;
    s32 hi;
    s32 mid;
    f32 x;
    f32 slope;
    f32 period;
    f32 t1;
    f32 v1;
    f32 in1;
    f32 t0;
    f32 v0;
    f32 out0;
    f32 inv;
    f32 s2;
    f32 s3;
    f32 inv2;
    f32 h1;
    f32 h2;
    f32 h10;
    f32 h11;

    if (c == NULL || c->n == 0) {
        return 0.0f;
    }
    if (t < c->keys[0].t) {
        switch (c->pre) {
        case 0:
            return c->keys[0].v;
        case 1:
            if (c->n == 1) {
                return c->keys[0].v;
            }
            k = c->keys;
            x = k[1].t - k[0].t;
            if (c->slopeMode == 1 && x != 0.0) {
                slope = (k[1].v - k[0].v) / x;
            } else {
                slope = k[0].in;
            }
            return k[0].v - (k[0].t - t) * slope;
        case 2:
            x = c->keys[0].t;
            if (c->n == 1) {
                return c->keys[0].v;
            }
            period = c->keys[c->n - 1].t - x;
            while (t < x) {
                t += period;
            }
            break;
        default:
            return 0.0f;
        }
    }
    if (c->keys[c->n - 1].t <= t) {
        switch (c->post) {
        case 0:
            return c->keys[c->n - 1].v;
        case 1:
            if (c->n == 1) {
                return c->keys[0].v;
            }
            k = &c->keys[c->n - 2];
            p = &c->keys[c->n - 1];
            x = p->t - k->t;
            if (c->slopeMode == 1 && x != 0.0) {
                slope = (p->v - k->v) / x;
            } else {
                slope = p->out;
            }
            return p->v + (t - p->t) * slope;
        case 2:
            x = c->keys[c->n - 1].t;
            if (c->n == 1) {
                return c->keys[0].v;
            }
            period = x - c->keys[0].t;
            while (x < t) {
                t -= period;
            }
            break;
        default:
            return 0.0f;
        }
    }
    lo = 1;
    hi = c->n - 1;
    while (lo < hi) {
        mid = (lo + hi) / 2;
        k = &c->keys[mid];
        if (t < k->t) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    k = &c->keys[lo];
    t1 = k->t;
    if (t == t1) {
        return k->v;
    }
    v1 = k->v;
    in1 = k->in;
    k--;
    t0 = k->t;
    v0 = k->v;
    out0 = k->out;
    switch (k->interp) {
    case 0:
        return v0;
    case 1:
        return v0 + (v1 - v0) * (t - t0) / (t1 - t0);
    case 2:
        inv = 1.0 / (t1 - t0);
        x = t - t0;
        s2 = x * x;
        s3 = s2 * x;
        inv2 = inv * inv;
        s3 *= inv2;
        h1 = 2.0 * s3 * inv;
        h2 = 3.0 * s2 * inv2;
        s2 *= inv;
        h11 = s3 - s2;
        h10 = h11 - s2 + x;
        return (h1 - h2) * v0 + v0 + v1 * (-h1 + h2) + out0 * h10 + in1 * h11;
    default:
        return 0.0f;
    }
}


/* Loads the two scrolling 32x32 water textures (tiles 0 and 1, both 0x02093576 entry 4) at
 * half alpha and scrolls them against each other by the scene timer */
void func_801A81A4_ovl_0EBBB0(void) {
    void *a = LoadAsset(0x02093576, 4, -4, 5);
    void *b = LoadAsset(0x02093576, 4, -4, 6);
    s32 t = D_801ABA58_ovl_0EBBB0->w104;
    u8 s;

    gDPPipeSync(D_800E9BA0++);
    gDPLoadTextureBlock(D_800E9BA0++, a, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, 0, 0, 5, 5, 14, 14);
    gDPLoadMultiBlock(D_800E9BA0++, b, 0x100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, 0, 0, 5, 5, 14, 14);
    {
        Gfx *g = D_800E9BA0++;

        g->w0 = 0xE3001001;
        g->w1 = 0;
    }
    gDPSetPrimColor(D_800E9BA0++, 0, 0, 0, 0, 0, 0x80);
    s = t >> 1;
    {
        Gfx *g = D_800E9BA0++;

        g->w0 = 0xF2000000 | (((0x80 - s) & 0x7F) << 12) | (s & 0x7F);
        g->w1 = 0;
    }
    {
        Gfx *g = D_800E9BA0++;

        g->w0 = 0xF2000000 | ((t & 0x7F) << 12) | (t & 0x7F);
        g->w1 = 0x01000000;
    }
}

/* As func_801A81A4 with the textures at half scale (shift 13) */
void func_801A8448_ovl_0EBBB0(void) {
    void *a = LoadAsset(0x02093576, 4, -4, 5);
    void *b = LoadAsset(0x02093576, 4, -4, 6);
    s32 t = D_801ABA58_ovl_0EBBB0->w104;
    u8 s;

    gDPPipeSync(D_800E9BA0++);
    gDPLoadTextureBlock(D_800E9BA0++, a, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, 0, 0, 5, 5, 13, 13);
    gDPLoadMultiBlock(D_800E9BA0++, b, 0x100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, 0, 0, 5, 5, 13, 13);
    {
        Gfx *g = D_800E9BA0++;

        g->w0 = 0xE3001001;
        g->w1 = 0;
    }
    gDPSetPrimColor(D_800E9BA0++, 0, 0, 0, 0, 0, 0x80);
    s = t >> 1;
    {
        Gfx *g = D_800E9BA0++;

        g->w0 = 0xF2000000 | (((0x80 - s) & 0x7F) << 12) | (s & 0x7F);
        g->w1 = 0;
    }
    {
        Gfx *g = D_800E9BA0++;

        g->w0 = 0xF2000000 | ((t & 0x7F) << 12) | (t & 0xFF);
        g->w1 = 0x01000000;
    }
}

#include "gbi_ultra.h"

/* Loads the scrolling 32x32 cloud texture 0x0203C53E into tile 1 (TMEM 0x100), half-alpha,
 * scrolled by the scene timer */
void func_801A86F0_ovl_0EBBB0(void) {
    gDPPipeSync(D_800E9BA0++);
    gDPLoadMultiBlock(D_800E9BA0++, LoadAsset(0x0203C53E, 0x9E, -10), 0x100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                      0, 0, 5, 5, 0, 15);
    gDPSetPrimColor(D_800E9BA0++, 0, 0, 0, 0, 0, 0x80);
    {
        Gfx *g = D_800E9BA0++;

        g->w0 = 0xF2000000 | (((D_801ABA58_ovl_0EBBB0->w104 * 4) & 0x7F) << 12);
        g->w1 = 0x01000000;
    }
}

extern u16 D_801AC45C_ovl_0EBBB0[];

/* Draws frame (timer / 6) % 6 of a 64x64 intensity animation in the scene colour (0x148-0x14A),
 * faded by f15C */
#ifdef NON_MATCHING
/* 125/126 instructions: as func_801A8A64, the original gives the display-list pointer v0 and moves the texture pointer to t3 */
void func_801A886C_ovl_0EBBB0(void) {
    void *tex = LoadAsset(0x0203C53E, D_801AC45C_ovl_0EBBB0[D_801ABA58_ovl_0EBBB0->w104 / 6 % 6], -0xA);

    gDPPipeSync(D_800E9BA0++);
    gDPLoadTextureBlock(D_800E9BA0++, tex, G_IM_FMT_I, G_IM_SIZ_8b, 64, 64, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 6,
                        G_TX_NOLOD, G_TX_NOLOD);
    gDPSetPrimColor(D_800E9BA0++, 0, 0, D_801ABA58_ovl_0EBBB0->unk124[0x24], D_801ABA58_ovl_0EBBB0->unk124[0x25],
                    D_801ABA58_ovl_0EBBB0->unk124[0x26], (u8)(D_801ABA58_ovl_0EBBB0->f15C * 255.0f));
}
#else
INCLUDE_ASM("asm/nonmatchings/ED530", func_801A886C_ovl_0EBBB0);
#endif

extern u16 D_801AC468_ovl_0EBBB0[];

/* Draws frame (timer / 6) % 6 of a 64x64 intensity animation in the scene colour (0x14B-0x14D),
 * faded by f15C */
#ifdef NON_MATCHING
/* 125/126 instructions: the original gives the display-list pointer v0 and moves the texture pointer to t3 */
void func_801A8A64_ovl_0EBBB0(void) {
    void *tex = LoadAsset(0x0203C53E, D_801AC468_ovl_0EBBB0[D_801ABA58_ovl_0EBBB0->w104 / 6 % 6], -0xA);

    gDPPipeSync(D_800E9BA0++);
    gDPLoadTextureBlock(D_800E9BA0++, tex, G_IM_FMT_I, G_IM_SIZ_8b, 64, 64, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 6,
                        G_TX_NOLOD, G_TX_NOLOD);
    gDPSetPrimColor(D_800E9BA0++, 0, 0, D_801ABA58_ovl_0EBBB0->unk124[0x27], D_801ABA58_ovl_0EBBB0->unk124[0x28],
                    D_801ABA58_ovl_0EBBB0->unk124[0x29], (u8)(D_801ABA58_ovl_0EBBB0->f15C * 255.0f));
}
#else
INCLUDE_ASM("asm/nonmatchings/ED530", func_801A8A64_ovl_0EBBB0);
#endif

extern u8 D_8018F520[];
extern s32 D_8018F568;
extern s8 D_8018F56C;
extern u16 D_801AC474_ovl_0EBBB0[];

/* Draws frame D_8018F568 (clamped to 45) of a 32x32 intensity animation in a fixed tan colour,
 * faded by f15C; clears flag 2 from frame 12 on and flag 4 (and D_8018F56C/D) at the end */
void func_801A8C5C_ovl_0EBBB0(void) {
    s32 f = D_8018F568;

    if (f >= 12) {
        D_8018F520[0] &= ~2;
    }
    if (f >= 46) {
        f = 45;
        D_8018F56D = 0;
        D_8018F56C = 0;
        D_8018F520[0] &= ~4;
    }
    gDPPipeSync(D_800E9BA0++);
    gDPLoadTextureBlock(D_800E9BA0++, LoadAsset(0x0203C53E, D_801AC474_ovl_0EBBB0[f], -0xA), G_IM_FMT_I, G_IM_SIZ_8b,
                        32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPSetPrimColor(D_800E9BA0++, 0, 0, 0xB5, 0xA5, 0x83, (u8)(D_801ABA58_ovl_0EBBB0->f15C * 255.0f));
}

typedef struct {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u8 unk02[0x22];
} Rec24;
extern Rec24 D_801951CC[];

#define G0E(w0_, w1_)                  \
    {                                  \
        Gfx *_g = D_800E9BA0++;        \
                                       \
        _g->w0 = (w0_);                \
        _g->w1 = (u32)(w1_);           \
    }

/* Loads the 8x16 CI4 icon of record i (1-based; 0xAA/0xAB/0xAC by flag bits 1-2) with its palette */
void func_801A8E64_ovl_0EBBB0(s32 i) {
    u8 *tex;
    s32 id;
    s32 f = D_801951CC[i - 1].flags & 6;

    id = 0xAC;
    if (f == 2) {
        id = 0xAA;
    } else {
        id -= f == 4;
    }
    tex = LoadAsset(0x0203C53E, id, -0xA);
    G0E(0xE7000000, 0);
    G0E(0xE3001001, 0x8000);
    G0E(0xFD500000, tex);
    G0E(0xF5500000, 0x07090230);
    G0E(0xE6000000, 0);
    G0E(0xF3000000, 0x0703F800);
    G0E(0xE7000000, 0);
    G0E(0xF5480200, 0x00090230);
    G0E(0xF2000000, 0x0001C03C);
    G0E(0xFD100000, tex + 0x80);
    G0E(0xE8000000, 0);
    G0E(0xF5000100, 0x07000000);
    G0E(0xE6000000, 0);
    G0E(0xF0000000, 0x073FC000);
    G0E(0xE7000000, 0);
}

extern u16 D_801AC624_ovl_0EBBB0[];

/* While flag bit (i * 2 + 6) is set, draws frame D_8018F568 (clamped to 65) of a 32x32 intensity
 * animation in pale yellow faded by f15C; clears bit (i * 2 + 5) from frame 34 on and its own bit
 * (and D_8018F56C/D) at the end */
void func_801A906C_ovl_0EBBB0(s32 i) {
    s32 f = D_8018F568;

    if ((D_8018F520[(i * 2 + 6) / 8] >> ((i * 2 + 6) & 7)) & 1) {
        if (f >= 34) {
            D_8018F520[(i * 2 + 5) / 8] &= ~(1 << ((i * 2 + 5) & 7));
        }
        if (f >= 66) {
            f = 65;
            D_8018F520[(i * 2 + 6) / 8] &= ~(1 << ((i * 2 + 6) & 7));
            D_8018F56D = 0;
            D_8018F56C = 0;
        }
        gDPPipeSync(D_800E9BA0++);
        gDPLoadTextureBlock(D_800E9BA0++, LoadAsset(0x0203C53E, D_801AC624_ovl_0EBBB0[f], -0xA), G_IM_FMT_I,
                            G_IM_SIZ_8b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetPrimColor(D_800E9BA0++, 0, 0, 0xFF, 0xFF, 0x97, (u8)(D_801ABA58_ovl_0EBBB0->f15C * 255.0f));
    }
}

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

/* With f15C as a struct member the pointer updates land correctly. What remains is register allocation (g in v1, the scene pointer in a0) and the float-to-u32 branch layout (bc1t with g copied in the delay slot). */
void func_801A93A4_ovl_0EBBB0(void)
{
  Gfx *new_var;
  Gfx *g;
  g = D_800E9BA0++;
  g->w0 = 0xE7000000;
  g->w1 = 0;
  g = D_800E9BA0++;
  g->w0 = 0xFA000000;
  new_var = g;
  new_var->w1 = (u8) ((u32) (D_801ABA58_ovl_0EBBB0->f15C * 255.0f));
}

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
