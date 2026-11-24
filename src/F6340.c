#include "common.h"
#include "scene.h"

/* F6340 */

extern s16 D_800E7A36;
extern s16 D_800E7A38;
extern s16 D_800E7A3A;
extern s16 D_800E7A3C;
extern u8 *D_801AD100_ovl_0EBBB0;
typedef struct {
    u32 w0;
    u32 w1;
} Gfx;
extern Gfx *D_800E9BA0;

s32 func_8007705C(s32 a, void *b, s32 c, s32 d, s32 e, s32 f, s32 g);
void func_801AB2A4_ovl_0EBBB0(s16 id);
void func_80078674(s16 a, s16 b, s16 c, s16 d);
void func_8007FB60(void *gfx, void *p);
void _bcopy(void *src, void *dst, s32 n);
u32 func_801AB5B0_ovl_0EBBB0(u8 *src, u32 size, void *dst);
typedef struct {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u8 flags2;
    /* 0x03 */ u8 flags3;
    /* 0x04 */ u8 unk04[0x10];
    /* 0x14 */ void (*update)(void);
    /* 0x18 */ void (*draw)(void);
    /* 0x1C */ void (*exit)(void);
    /* 0x20 */ u16 size;
    /* 0x22 */ u8 unk22[2];
    /* 0x24 */ s32 w24;
} CurScene;
extern CurScene D_800E7A30;
extern u8 D_800E91D0[];
void bzero(void *p, s32 n);
void func_801AB33C_ovl_0EBBB0(void);
void func_801AB55C_ovl_0EBBB0(void);
void func_801A9DB0_ovl_0EBBB0(s32 a, s32 b, f32 *x, f32 *y);
void func_801AA248_ovl_0EBBB0(s32 a, s32 b, s32 c, f32 *x, f32 *y);
extern u8 D_801ACA00_ovl_0EBBB0[];
extern u8 D_801ACD10_ovl_0EBBB0[];
extern u8 D_801AD030_ovl_0EBBB0[];
/* --- end decls --- */

#include "gbi_ultra.h"
extern u8 D_801AC940_ovl_0EBBB0[];
void *LoadAsset(u32 id, s32 a, s32 b, s32 c);

/* Draws background panel 0x02093576: 32x64 RGBA16 texture, then display list D_801AC940 */
void func_801A95E0_ovl_0EBBB0(void) {
    void *img = LoadAsset(0x02093576, 4, -3, 0);

    gDPPipeSync(D_800E9BA0++);
    gDPLoadTextureBlock(D_800E9BA0++, img, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0, 0, 0, 5, 6, 13, 14);
    gSPDisplayList(D_800E9BA0++, D_801AC940_ovl_0EBBB0);
}

/* Background panel 0x02093576 frame 0 again: 32x64 RGBA16, then display list D_801ACA00 */
void func_801A9714_ovl_0EBBB0(void) {
    void *img = LoadAsset(0x02093576, 4, -3, 0);

    gDPPipeSync(D_800E9BA0++);
    gDPLoadTextureBlock(D_800E9BA0++, img, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0, 0, 0, 5, 6, 13, 14);
    gSPDisplayList(D_800E9BA0++, D_801ACA00_ovl_0EBBB0);
}

/* Panel 0x02093576 frame 4: 64x32 RGBA16 clamped, then display list D_801ACD10 */
void func_801A9848_ovl_0EBBB0(void) {
    void *img = LoadAsset(0x02093576, 4, -3, 4);

    gDPPipeSync(D_800E9BA0++);
    gDPLoadTextureBlock(D_800E9BA0++, img, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, 2, 2, 6, 5, 0, 0);
    gSPDisplayList(D_800E9BA0++, D_801ACD10_ovl_0EBBB0);
}

/* Panel 0x02093576 frame 3: 32x64 RGBA16 clamped, then display list D_801AD030 */
void func_801A997C_ovl_0EBBB0(void) {
    void *img = LoadAsset(0x02093576, 4, -3, 3);

    gDPPipeSync(D_800E9BA0++);
    gDPLoadTextureBlock(D_800E9BA0++, img, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0, 2, 2, 5, 6, 0, 0);
    gSPDisplayList(D_800E9BA0++, D_801AD030_ovl_0EBBB0);
}

INCLUDE_ASM("asm/nonmatchings/F6340", func_801A9AB0_ovl_0EBBB0);

static inline f32 AbsF63(f32 v) {
    return v < 0.0f ? -v : v;
}

void func_8007FFD0(f32 *v);                       /* normalise */
void func_8007FEE0(f32 *out, f32 *a, f32 *b);     /* out = a x b */
f32 *func_80080080(f32 *out, f32 *a, f32 s);  /* scale */
f32 sinf(f32 x);
f32 cosf(f32 x);

/* Screen position (*x, *y; 320x240 view) of world point p seen by camera c (fov at 0, eye 0x14,
 * target 0x20, up 0x2C) */
void func_801A9DB0_ovl_0EBBB0(s32 cam, s32 pt, f32 *x, f32 *y) {
    f32 *c = (f32 *)cam;
    f32 *p = (f32 *)pt;
    f32 perp[3];
    f32 up[3];
    f32 right[3];
    f32 fwd[3];
    f32 rel[3];
    f32 proj[3];
    f32 t;

    rel[0] = p[0] - c[5];
    rel[1] = p[1] - c[6];
    rel[2] = p[2] - c[7];
    fwd[0] = c[8] - c[5];
    fwd[1] = c[9] - c[6];
    fwd[2] = c[10] - c[7];
    func_8007FFD0(fwd);
    func_8007FEE0(right, c + 11, fwd);
    func_8007FEE0(up, fwd, right);
    func_8007FFD0(up);
    func_8007FFD0(right);
    func_80080080(proj, fwd, fwd[0] * rel[0] + fwd[1] * rel[1] + fwd[2] * rel[2]);
    perp[0] = rel[0] - proj[0];
    perp[1] = rel[1] - proj[1];
    perp[2] = rel[2] - proj[2];
    t = sinf(c[0] / 2.0f / 360.0f * 6.2831855f) / cosf(c[0] / 2.0f / 360.0f * 6.2831855f) *
        (fwd[0] * rel[0] + fwd[1] * rel[1] + fwd[2] * rel[2]);
    t = AbsF63(t);
    *x = 160.0f - (perp[0] * right[0] + perp[1] * right[1] + perp[2] * right[2]) * 120.0f / t;
    *y = 120.0f - (perp[0] * up[0] + perp[1] * up[1] + perp[2] * up[2]) * 120.0f / t;
}

/* func_801AA15C with integer results */
void func_801AA064_ovl_0EBBB0(s32 i, s32 a, s32 b, s32 *x, s32 *y) {
    f32 sx;
    f32 sy;

    func_801A9DB0_ovl_0EBBB0(a, b, &sx, &sy);
    *x = sx / 320.0f * (D_800E82C8[i].x2 - D_800E82C8[i].x + 1);
    *y = sy / 240.0f * (D_800E82C8[i].y2 - D_800E82C8[i].y + 1);
}

/* Projects (a, b) to screen space and scales it from 320x240 to scene i's window size */
void func_801AA15C_ovl_0EBBB0(s32 i, s32 a, s32 b, f32 *x, f32 *y) {
    f32 sx;
    f32 sy;

    func_801A9DB0_ovl_0EBBB0(a, b, &sx, &sy);
    *x = sx / 320.0f * (D_800E82C8[i].x2 - D_800E82C8[i].x + 1);
    *y = sy / 240.0f * (D_800E82C8[i].y2 - D_800E82C8[i].y + 1);
}

void guMtxXFMF(f32 mf[4][4], f32 x, f32 y, f32 z, f32 *ox, f32 *oy, f32 *oz);

/* Screen position (*x, *y; 320x240 view) of point p transformed by matrix m, seen by camera c */
void func_801AA248_ovl_0EBBB0(s32 cam, s32 m, s32 pt, f32 *x, f32 *y) {
    f32 *c = (f32 *)cam;
    f32 *p = (f32 *)pt;
    f32 perp[3];
    f32 up[3];
    f32 right[3];
    f32 fwd[3];
    f32 rel[3];
    f32 proj[3];
    f32 w[3];
    f32 t;

    guMtxXFMF((f32 (*)[4])m, p[0], p[1], p[2], &w[0], &w[1], &w[2]);
    rel[0] = w[0] - c[5];
    rel[1] = w[1] - c[6];
    rel[2] = w[2] - c[7];
    fwd[0] = c[8] - c[5];
    fwd[1] = c[9] - c[6];
    fwd[2] = c[10] - c[7];
    func_8007FFD0(fwd);
    func_8007FEE0(right, c + 11, fwd);
    func_8007FEE0(up, fwd, right);
    func_8007FFD0(up);
    func_8007FFD0(right);
    func_80080080(proj, fwd, fwd[0] * rel[0] + fwd[1] * rel[1] + fwd[2] * rel[2]);
    perp[0] = rel[0] - proj[0];
    perp[1] = rel[1] - proj[1];
    perp[2] = rel[2] - proj[2];
    t = sinf(c[0] / 2.0f / 360.0f * 6.2831855f) / cosf(c[0] / 2.0f / 360.0f * 6.2831855f) *
        (fwd[0] * rel[0] + fwd[1] * rel[1] + fwd[2] * rel[2]);
    t = AbsF63(t);
    *x = 160.0f - (perp[0] * right[0] + perp[1] * right[1] + perp[2] * right[2]) * 120.0f / t;
    *y = 120.0f - (perp[0] * up[0] + perp[1] * up[1] + perp[2] * up[2]) * 120.0f / t;
}

/* func_801AA62C with integer results */
void func_801AA52C_ovl_0EBBB0(s32 i, s32 a, s32 b, s32 c, s32 *x, s32 *y) {
    f32 sx;
    f32 sy;

    func_801AA248_ovl_0EBBB0(a, b, c, &sx, &sy);
    *x = sx / 320.0f * (D_800E82C8[i].x2 - D_800E82C8[i].x + 1);
    *y = sy / 240.0f * (D_800E82C8[i].y2 - D_800E82C8[i].y + 1);
}

/* Same as func_801AA15C for a 3D point */
void func_801AA62C_ovl_0EBBB0(s32 i, s32 a, s32 b, s32 c, f32 *x, f32 *y) {
    f32 sx;
    f32 sy;

    func_801AA248_ovl_0EBBB0(a, b, c, &sx, &sy);
    *x = sx / 320.0f * (D_800E82C8[i].x2 - D_800E82C8[i].x + 1);
    *y = sy / 240.0f * (D_800E82C8[i].y2 - D_800E82C8[i].y + 1);
}

void func_8007FE50(f32 *dst, f32 *src);           /* copy */
void func_80080040(f32 *out, f32 *a, f32 *b);     /* out = a - b */
void func_8007FFD0(f32 *v);                       /* normalise */
void func_8007FEE0(f32 *out, f32 *a, f32 *b);     /* out = a x b */
void func_80080190(f32 *v, f32 s);                /* v *= s */
void func_800801D0(f32 *a, f32 *b);               /* a += b */
void func_800800C0(f32 *out, f32 *a, f32 *b);     /* out = a + b */
f32 *func_80080020(f32 *v, f32 x, f32 y, f32 z);  /* set */
f32 func_8009CE20(f32 x);                         /* tanf */

/* Camera: vertical fov (degrees) at 0, eye at 0x14, look-at at 0x20, up at 0x2C */
typedef struct {
    /* 0x00 */ f32 fov;
    /* 0x04 */ u8 unk04[0x10];
    /* 0x14 */ f32 eye[3];
    /* 0x20 */ f32 at[3];
    /* 0x2C */ f32 up[3];
} CamF63;

/* Unit direction of the ray through screen point (x, y) of a w x h view */
inline void func_801AA720_ovl_0EBBB0(CamF63 *c, f32 x, f32 y, f32 w, f32 h, f32 *dir) {
    f32 fwd[3];
    f32 up[3];
    f32 right[3];

    func_80080040(fwd, c->at, c->eye);
    func_8007FFD0(fwd);
    func_8007FEE0(right, fwd, c->up);
    func_8007FFD0(right);
    func_8007FEE0(up, fwd, right);
    func_8007FFD0(up);
    func_80080190(fwd, 1.0f / func_8009CE20(c->fov * 0.5f / 360.0f * 6.2831855f));
    func_80080190(up, 2.0f * (y / h - 0.5f));
    func_80080190(right, 2.0f * ((x / w - 0.5f) * w / h));
    func_800801D0(fwd, up);
    func_800800C0(dir, fwd, right);
    func_8007FFD0(dir);
}

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AA8A4_ovl_0EBBB0);

/* Where the ray through screen point (x, y) meets the ground plane (y = 0); 0 when it points
 * away. A camera on the ground returns its own position. */
s32 func_801AAE10_ovl_0EBBB0(CamF63 *c, f32 x, f32 y, f32 *out) {
    f32 dir[3];
    f32 t;

    if (c->eye[1] == 0.0f) {
        func_8007FE50(out, c->eye);
        return 1;
    }
    func_801AA720_ovl_0EBBB0(c, x, y, 320.0f, 240.0f, dir);
    if (!(c->eye[1] * dir[1] >= 0.0f)) {
        t = -c->eye[1] / dir[1];
        func_80080020(out, c->eye[0] + t * dir[0], 0.0f, c->eye[2] + t * dir[2]);
        return 1;
    }
    return 0;
}

/* Opens a scene for this screen and sets its fade parameters; returns the scene slot */
s32 func_801AB020_ovl_0EBBB0(s32 a, u8 b) {
    s32 i = func_8007705C(0xC000, func_801AB2A4_ovl_0EBBB0, 0, 0, 0, 0, 0xF000);

    D_800E82C8[i].unk89 = 11;
    D_800E82C8[i].unk88 = a;
    D_800E82C8[i].unk8A = b;
    D_800E82C8[i].unk8B = 0;
    D_800E82C8[i].unk8C = 0;
    D_800E82C8[i].unk8D = 0;
    D_800E82C8[i].unk8E = 0xFF;
    D_800E82C8[i].unk8F = 0;
    D_800E82C8[i].unk97 = 0;
    return i;
}

/* Same with fade mode 15 */
s32 func_801AB0FC_ovl_0EBBB0(s32 a, u8 b) {
    s32 i = func_8007705C(0xC000, func_801AB2A4_ovl_0EBBB0, 0, 0, 0, 0, 0xF000);

    D_800E82C8[i].unk89 = 15;
    D_800E82C8[i].unk88 = a;
    D_800E82C8[i].unk8A = b;
    D_800E82C8[i].unk8B = 0;
    D_800E82C8[i].unk8C = 0;
    D_800E82C8[i].unk8D = 0;
    D_800E82C8[i].unk8E = 0;
    D_800E82C8[i].unk8F = 0xFF;
    D_800E82C8[i].unk97 = 0;
    return i;
}

void func_801AB1D8_ovl_0EBBB0(void) {
    func_8007705C(0xC000, func_801AB2A4_ovl_0EBBB0, 0, 0, 0, 0, 0xF000);
}

void func_801AB214_ovl_0EBBB0(u8 i, u8 a, u8 b, u8 c, u8 d, u8 e, u8 f, u8 g, u8 h) {
    D_800E82C8[i].unk88 = a;
    D_800E82C8[i].unk89 = b;
    D_800E82C8[i].unk8A = c;
    D_800E82C8[i].unk8B = d;
    D_800E82C8[i].unk8C = e;
    D_800E82C8[i].unk8D = f;
    D_800E82C8[i].unk8E = g;
    D_800E82C8[i].unk8F = h;
}

/* Scene init: installs the update/draw handlers with 0x28 bytes of state, stores the id */
void func_801AB2A4_ovl_0EBBB0(s16 id) {
    D_800E7A30.update = func_801AB33C_ovl_0EBBB0;
    D_800E7A30.draw = func_801AB55C_ovl_0EBBB0;
    D_800E7A30.size = 0x28;
    D_800E7A30.w24 = 0;
    D_800E7A30.flags |= 0x200;
    D_800E7A30.flags2 |= 9;
    D_800E7A30.flags3 |= 0xC;
    bzero(D_800E91D0, 0x28);
    *(s16 *)D_801AD100_ovl_0EBBB0 = id;
}

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void func_8007FA38(u8 *p, u8 a, u8 b, u8 c, s32 d, s32 e, s32 f);
u8 func_8007FB10(u8 *p);
extern u8 D_800E7A32[];
extern s16 D_800E7A3E;
extern u8 D_800E7A90[];

/* Per-frame update of the field message window: closes it (D_800E7A32 bit 2) once finished or when
 * its scene slot is gone; applies a pending restart (flag 8), and on reaching the end (0xFF) marks
 * it done and optionally flags the scene; copies the scene's rectangle and steps the text */
#ifdef NON_MATCHING
/* 136/136, 7 words: identical code but our frame is 64 bytes (24 bytes of unused locals) against 40 */
void func_801AB33C_ovl_0EBBB0(void) {
    if (D_801AD100_ovl_0EBBB0[0x25] != 0) {
        goto close;
    }
    if (!(D_800E7A90[0x29] & 1)) {
        return;
    }
    if (!(D_800E82C8[D_800E7A90[0x28]].flags & 0x8000)) {
    close:
        D_800E7A32[0] |= 2;
        return;
    }
    if (D_800E7A90[0x29] & 8) {
        func_8007FA38(D_801AD100_ovl_0EBBB0 + 4, D_800E7A90[0x2A], D_800E7A90[0x2B], D_800E7A90[0x2C],
                      D_800E7A90[0x2D], D_800E7A90[0x2E], D_800E7A90[0x2F]);
        D_800E7A3E = 0xF100;
        D_800E7A90[0x29] &= ~8;
        D_800E7A90[0x37] &= ~1;
    } else if (D_801AD100_ovl_0EBBB0[0x24] == 0xFF) {
        D_800E7A90[0x37] |= 1;
        if (D_800E7A90[0x29] & 2) {
            D_801AD100_ovl_0EBBB0[0x25] = 1;
        }
        if (D_800E7A90[0x29] & 4) {
            D_800E82C8[D_800E7A90[0x28]].flags2 |= 2;
        }
    } else {
        D_800E7A90[0x37] &= ~1;
    }
    D_800E7A36 = FIELD(&D_800E82C8[D_800E7A90[0x28]], s16, 6);
    D_800E7A38 = FIELD(&D_800E82C8[D_800E7A90[0x28]], s16, 8);
    D_800E7A3A = FIELD(&D_800E82C8[D_800E7A90[0x28]], s16, 10);
    D_800E7A3C = FIELD(&D_800E82C8[D_800E7A90[0x28]], s16, 12);
    D_801AD100_ovl_0EBBB0[0x24] = func_8007FB10(D_801AD100_ovl_0EBBB0 + 4);
}
#else
INCLUDE_ASM("asm/nonmatchings/F6340", func_801AB33C_ovl_0EBBB0);
#endif

void func_801AB55C_ovl_0EBBB0(void) {
    func_80078674(D_800E7A36, D_800E7A38, D_800E7A3A, D_800E7A3C);
    func_8007FB60(&D_800E9BA0, D_801AD100_ovl_0EBBB0 + 4);
}

/* RLE decoder: c < 0x80 copies c + 1 bytes; 0xE0 | n sets a new fill byte and writes n + 3 of it;
 * 0xC0 | n writes n + 2 of the last fill byte; 0x80 | n writes n + 2 zeros. Returns the size. */
u32 func_801AB5B0_ovl_0EBBB0(u8 *src, u32 size, void *dst) {
    u32 in = 0;
    u8 fill = 0xFF;
    u32 out = 0;
    u8 c;
    u8 n;
    u8 i;

    while (in < size) {
        n = src[in++];
        c = n;
        if (c < 0x80) {
            n = c + 1;
            for (i = 0; i < n; i++) {
                ((u8 *)dst)[out++] = src[in++];
            }
        } else if (!(c & 0x40)) {
            n = (c & 0x3F) + 2;
            for (i = 0; i < n; i++) {
                ((u8 *)dst)[out++] = 0;
            }
        } else if (!(c & 0x20)) {
            n = (c & 0x1F) + 2;
            for (i = 0; i < n; i++) {
                ((u8 *)dst)[out++] = fill;
            }
        } else {
            fill = src[in++];
            n = (c & 0x1F) + 3;
            for (i = 0; i < n; i++) {
                ((u8 *)dst)[out++] = fill;
            }
        }
    }
    return out;
}

/* Reads a big-endian u32 from an unaligned pointer */
inline u32 func_801AB720_ovl_0EBBB0(u8 *p) {
    return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
}

/* Unpacks a [size, packed size, data] block into dst (stored raw when packed size is 0); returns the size */
#ifdef NON_MATCHING
/* inlined BE32 result copy/branch layout differs */
u32 func_801AB74C_ovl_0EBBB0(void *dst, u8 *src) {
    u32 c = func_801AB720_ovl_0EBBB0(src + 4);
    u32 n;

    if (c != 0) {
        return func_801AB5B0_ovl_0EBBB0(src + 8, c, dst);
    }
    n = func_801AB720_ovl_0EBBB0(src);
    _bcopy(src + 8, dst, n);
    return n;
}
#else
INCLUDE_ASM("asm/nonmatchings/F6340", func_801AB74C_ovl_0EBBB0);
#endif
