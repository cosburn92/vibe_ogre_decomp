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

INCLUDE_ASM("asm/nonmatchings/F6340", func_801A9DB0_ovl_0EBBB0);

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

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AA248_ovl_0EBBB0);

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

#ifdef NON_MATCHING
/* m2c draft, 29 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_8007FEE0(s32 *, s32 *, s32 *); /* extern */
s32 func_8007FFD0(s32 *);                   /* extern */
s32 func_80080040(s32 *, s32, s32);         /* extern */
s32 func_800800C0(s32 *, s32 *, s32 *); /* extern */
s32 func_80080190(s32 *, f32);              /* extern */
s32 func_800801D0(s32 *, s32 *);        /* extern */
f32 func_8009CE20(f32);                             /* extern */

void func_801AA720_ovl_0EBBB0(f32 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 *arg5) {
    s32 sp10;
    s32 sp20;
    s32 sp30;

    func_80080040(&sp10, arg0 + 0x20, arg0 + 0x14);
    func_8007FFD0(&sp10);
    func_8007FEE0(&sp30, &sp10, arg0 + 0x2C);
    func_8007FFD0(&sp30);
    func_8007FEE0(&sp20, &sp10, &sp30);
    func_8007FFD0(&sp20);
    func_80080190(&sp10, 1.0f / func_8009CE20(((*arg0 * 0.5f) / 360.0f) * 6.2831855f));
    func_80080190(&sp20, 2.0f * ((arg2 / arg4) - 0.5f));
    func_80080190(&sp30, 2.0f * ((((arg1 / arg3) - 0.5f) * arg3) / arg4));
    func_800801D0(&sp10, &sp20);
    func_800800C0(arg5, &sp10, &sp30);
    func_8007FFD0(arg5);
}
#else
INCLUDE_ASM("asm/nonmatchings/F6340", func_801AA720_ovl_0EBBB0);
#endif

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AA8A4_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AAE10_ovl_0EBBB0);

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

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_8007FA38(u8 *, u8, u8, u8, s32, s32, s32); /* extern */
u8 func_8007FB10(u8 *);                             /* extern */
extern u8 D_800E7A32;
extern s16 D_800E7A3E;
extern s32 D_800E7A90;
extern s32 D_800E82CA;
extern s32 D_800E82CE;
extern s32 D_800E82D0;
extern s32 D_800E82D2;
extern s32 D_800E82D4;

void func_801AB33C_ovl_0EBBB0(void) {
    s32 temp_v0;
    s32 temp_v1;
    void *temp_s0;

    if (FIELD(D_801AD100_ovl_0EBBB0, u8, 0x25) == 0) {
        temp_s0 = &D_800E7A90 + 0x29;
        if (FIELD(&D_800E7A90, u8, 0x29) & 1) {
            if (!(D_800E82C8[FIELD(temp_s0, u8, -1)].flags & 0x8000)) {
                goto block_3;
            }
            if (FIELD(&D_800E7A90, u8, 0x29) & 8) {
                func_8007FA38(D_801AD100_ovl_0EBBB0 + 4, FIELD(&D_800E7A90, u8, 0x2A), FIELD(&D_800E7A90, u8, 0x2B), FIELD(&D_800E7A90, u8, 0x2C), (s32) FIELD(&D_800E7A90, u8, 0x2D), (s32) FIELD(&D_800E7A90, u8, 0x2E), (s32) FIELD(&D_800E7A90, u8, 0x2F));
                D_800E7A3E = 0xF100;
                FIELD(&D_800E7A90, u8, 0x29) = (u8) (FIELD(&D_800E7A90, u8, 0x29) & 0xF7);
                FIELD(&D_800E7A90, u8, 0x37) = (u8) (FIELD(&D_800E7A90, u8, 0x37) & 0xFE);
            } else if (FIELD(D_801AD100_ovl_0EBBB0, u8, 0x24) == 0xFF) {
                FIELD(&D_800E7A90, u8, 0x37) = (u8) (FIELD(&D_800E7A90, u8, 0x37) | 1);
                if (FIELD(&D_800E7A90, u8, 0x29) & 2) {
                    FIELD(D_801AD100_ovl_0EBBB0, u8, 0x25) = 1U;
                }
                if (FIELD(&D_800E7A90, u8, 0x29) & 4) {
                    temp_v1 = FIELD(temp_s0, u8, -1) * 0xA8;
                    *(&D_800E82CA + temp_v1) = *(&D_800E82CA + temp_v1) | 2;
                }
            } else {
                FIELD(&D_800E7A90, u8, 0x37) = (u8) (FIELD(&D_800E7A90, u8, 0x37) & 0xFE);
            }
            temp_v0 = FIELD(&D_800E7A90, u8, 0x28) * 0xA8;
            D_800E7A36 = (s16) *(&D_800E82CE + temp_v0);
            D_800E7A38 = (s16) *(&D_800E82D0 + temp_v0);
            D_800E7A3A = (s16) *(&D_800E82D2 + temp_v0);
            D_800E7A3C = (s16) *(&D_800E82D4 + temp_v0);
            FIELD(D_801AD100_ovl_0EBBB0, u8, 0x24) = func_8007FB10(D_801AD100_ovl_0EBBB0 + 4);
        }
    } else {
block_3:
        D_800E7A32 |= 2;
    }
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
