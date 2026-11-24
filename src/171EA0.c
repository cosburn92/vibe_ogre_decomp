#include "common.h"

/* 171EA0 */

typedef struct {
    u8 unk00[0x5C];
    s16 h5C;
    u8 b5E;
    u8 unk5F;
    s32 w60;
    u8 b64;
    u8 b65;
    u8 unk66[2];
    s32 w68;
    s32 w6C;
    s32 w70;
    s32 w74;
    s32 w78;
    s32 w7C;
} Ctx17;

extern s16 D_8021AFB0_ovl_171EA0;
extern u8 D_8021AFB2_ovl_171EA0;
extern s8 D_8021AFB3_ovl_171EA0;
extern u8 D_8021AFB4_ovl_171EA0;
extern u8 D_80214E84;
extern Ctx17 *D_8021AA70_ovl_171EA0;
extern u8 D_8018F480;
extern u8 D_801F365D;
extern s32 D_801F0DE0;
extern s32 D_801F0DE8;

void func_80076F5C(s32 a, void *b, s32 c, s32 d, s32 e, s32 f, s32 g);
void func_80214FFC_ovl_171EA0(void);
void func_80079618();
void func_80179018(void);
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
} CurScene17;
extern CurScene17 D_800E7A30;
extern u8 D_800E7A33;
void func_802150C8_ovl_171EA0(void);
void func_80216CD8_ovl_171EA0(void);
void func_80215378_ovl_171EA0(void);
void *LoadAsset(u32 handle, ...);
extern s32 D_801F3658;
extern u8 *D_801F0CB0[];
extern u8 D_801F0FDF;
extern u8 D_801F0FE0;
extern u8 D_801F0FE1;
extern u8 D_80210219;
extern u8 D_801951CC[];
u8 func_801DADF0(u8 *u);
s32 func_801DD244(void);
s32 func_80186210(s32 a);
/* --- end decls --- */

void func_80214F80_ovl_171EA0(s16 a, u8 b, u8 c, u8 d) {
    D_8021AFB0_ovl_171EA0 = a;
    D_8021AFB2_ovl_171EA0 = b;
    D_8021AFB3_ovl_171EA0 = c;
    D_8021AFB4_ovl_171EA0 = d;
    func_80076F5C(0xC000, func_80214FFC_ovl_171EA0, 0x66, 0x41, 0x70, 0x4B, 0xC8);
    D_80214E84 = 1;
}

u8 func_80214FF0_ovl_171EA0(void) {
    return D_80214E84;
}

void func_80214FFC_ovl_171EA0(void) {
    D_800E7A30.flags2 |= 8;
    D_800E7A33 |= 1;
    D_800E7A30.flags2 |= 1;
    D_800E7A30.flags |= 0x200;
    D_800E7A30.update = func_802150C8_ovl_171EA0;
    D_800E7A30.draw = func_80216CD8_ovl_171EA0;
    D_800E7A30.size = 0x80;
    D_800E7A30.w24 = 0;
    D_8021AA70_ovl_171EA0->h5C = D_8021AFB0_ovl_171EA0;
    ((u8 *)D_8021AA70_ovl_171EA0)[0x5E] = 0;
    D_8021AA70_ovl_171EA0->w60 = 0;
    ((u8 *)D_8021AA70_ovl_171EA0)[0x64] = 0;
    ((u8 *)D_8021AA70_ovl_171EA0)[0x65] = 0;
    D_8021AA70_ovl_171EA0->w68 = 0;
    D_8021AA70_ovl_171EA0->w6C = 0;
    D_8021AA70_ovl_171EA0->w70 = 0;
    D_8021AA70_ovl_171EA0->w74 = 0;
    D_8021AA70_ovl_171EA0->w78 = 0;
    D_8021AA70_ovl_171EA0->w7C = 0;
    func_80215378_ovl_171EA0();
}

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void *func_8017BFB0(s32 a, s32 b, void *c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i, s32 j, s32 k);
void func_8017C384(void *w);
void func_8020CDA0(s32 se);
extern u16 *D_800C4BDC;
extern s32 D_801F1070;
extern u8 gLocations[][0x24];
typedef struct {
    u32 w0;
    u32 w1;
} Gfx;
#include "gbi_ultra.h"
extern Gfx *D_800E9BA0;
extern u8 *D_801F0B90;
extern u8 *D_801F36C0;
void func_8017C4B4(s16 a);
u16 func_8017B58C(void *s);
void func_80200F70(void *pal, void *img, u16 w, u16 h, u16 mode);
void func_80200DD0(s32 x, s32 y, s32 icon);
void func_80179034(void *s, s32 x, s32 y);

/* Window object (func_8017BFB0); only the fields used here are named */
typedef struct {
    /* 0x00 */ u8 unk00[0x18];
    /* 0x18 */ s16 fade[2];
} Win17;

void func_80215494_ovl_171EA0(Win17 *w, s32 page);
void func_80215780_ovl_171EA0();
void func_80215444_ovl_171EA0(void);

/* Location info screen update: picks the location (0x5C, or the first one when out of range,
 * closing the screen) and its kind (0x5E: 0 plain, 1 town, 2 temple), then opens the two windows,
 * waits for a button, closes them and ends the screen */
void func_802150C8_ovl_171EA0(void) {
    u8 *loc = gLocations[0];

    if ((u16)D_8021AA70_ovl_171EA0->h5C < D_801F1070) {
        loc = gLocations[(u16)D_8021AA70_ovl_171EA0->h5C];
    } else {
        D_800E7A30.flags2 |= 2;
    }
    if (!(FIELD(loc, u16, 0x1C) & 6)) {
        D_8021AA70_ovl_171EA0->b5E = 0;
    } else if (FIELD(loc, u16, 0x1C) & 2) {
        D_8021AA70_ovl_171EA0->b5E = 1;
    } else {
        D_8021AA70_ovl_171EA0->b5E = 2;
    }
    D_8021AA70_ovl_171EA0->w60 = (s32)loc;
    switch (D_8021AA70_ovl_171EA0->b64) {
        case 0:
            if (D_8021AA70_ovl_171EA0->w68 == 0) {
                u8 *w;
                u8 *w2;

                w = func_8017BFB0(0, 0, func_80215494_ovl_171EA0, 100, 110, 220, 210, 80, 90, 240, 230);
                D_8021AA70_ovl_171EA0->w68 = (s32)w;
                w[0x14] |= 3;
                w2 = func_8017BFB0(0, 0, func_80215780_ovl_171EA0, 80, 40, 240, 190, 60, 20, 260, 210);
                D_8021AA70_ovl_171EA0->w6C = (s32)w2;
                w2[0x14] |= 3;
            }
            if (D_8021AA70_ovl_171EA0->b65 >= 9) {
                D_8021AA70_ovl_171EA0->b64 = 1;
                D_8021AA70_ovl_171EA0->b65 = 0;
            } else {
                D_8021AA70_ovl_171EA0->b65++;
            }
            break;
        case 1:
            if (*D_800C4BDC & 0xC000) {
                D_8021AA70_ovl_171EA0->b64 = 2;
                func_8020CDA0(1);
            }
            break;
        case 2:
            if (D_8021AA70_ovl_171EA0->w68 != 0) {
                func_8017C384((void *)D_8021AA70_ovl_171EA0->w68);
                func_8017C384((void *)D_8021AA70_ovl_171EA0->w6C);
                D_8021AA70_ovl_171EA0->w68 = 0;
                D_8021AA70_ovl_171EA0->w6C = 0;
            }
            if (D_8021AA70_ovl_171EA0->b65 >= 17) {
                D_8021AA70_ovl_171EA0->b64 = 3;
                D_8021AA70_ovl_171EA0->b65 = 0;
            } else {
                D_8021AA70_ovl_171EA0->b65++;
            }
            break;
        case 3:
            func_80215444_ovl_171EA0();
            D_80214E84 = 0;
            D_800E7A30.flags2 |= 2;
            break;
    }
}

/* Loads the four images from asset 0x218E9B4 (frame, then variants picked by the three parameters) */
void func_80215378_ovl_171EA0(void) {
    if (D_8021AA70_ovl_171EA0->w70 == 0) {
        D_8021AA70_ovl_171EA0->w70 = (s32)LoadAsset(0x218E9B4, 0x16, -3, 0);
        D_8021AA70_ovl_171EA0->w74 = (s32)LoadAsset(0x218E9B4, 0x16, -3, D_8021AFB4_ovl_171EA0 + 0x14);
        D_8021AA70_ovl_171EA0->w78 = (s32)LoadAsset(0x218E9B4, 0x16, -3, D_8021AFB2_ovl_171EA0 + 1);
        D_8021AA70_ovl_171EA0->w7C = (s32)LoadAsset(0x218E9B4, 0x16, -3, D_8021AFB3_ovl_171EA0 + 0xC);
    }
}

void func_80215444_ovl_171EA0(void) {
    if (D_8021AA70_ovl_171EA0->w70 != 0) {
        func_80079618(0x218E9B4, 0x16, -0x11);
        D_8021AA70_ovl_171EA0->w70 = 0;
        D_8021AA70_ovl_171EA0->w74 = 0;
        D_8021AA70_ovl_171EA0->w78 = 0;
        D_8021AA70_ovl_171EA0->w7C = 0;
    }
}

#ifdef NON_MATCHING
/* Same size, 66 lines differ: the original has no sign extension for the (s16) casts in
 * gSPScisTextureRectangle (GCC must know the coordinates fit; the clamped width here has two sets),
 * so registers shift from 0x174 on */
/* Texture strip (xl, yl) - (xh, yh) in 10.2 screen coordinates between pipe syncs */
static inline void func_80215494_strip(Gfx **gp, s32 xl, s32 yl, s32 xh, s32 yh) {
    gDPPipeSync((*gp)++);
    gSPScisTextureRectangle((*gp)++, xl, yl, xh, yh, 0, 0, 24 << 5, 1 << 10, 1 << 10);
    gDPPipeSync((*gp)++);
}

/* Draws the location name plate (window page callback): a background strip at least 77 pixels
 * wide centred on x 0xA0, with end caps 0x76/0x77, and the name of the current location on it */
void func_80215494_ovl_171EA0(Win17 *w, s32 page) {
    u16 len;
    u32 n;
    s32 x;
    s32 y;

    if (w->fade[page] == 0) {
        return;
    }
    gDPPipeSync(D_800E9BA0++);
    func_8017C4B4(w->fade[page]);
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xE200001C;
        _g->w1 = 0x00504240;
    }
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xFC119623;
        _g->w1 = 0xFF2FFFFF;
    }
    gDPSetPrimColor(D_800E9BA0++, 0, 0, 0xFF, 0xFF, 0xFF, w->fade[page]);
    gDPSetTextureLUT(D_800E9BA0++, G_TT_RGBA16);
    gSPTexture(D_800E9BA0++, 0x8000, 0x8000, 0, 0, G_ON);
    len = func_8017B58C((void *)D_8021AA70_ovl_171EA0->w60);
    n = (u8)len;
    if (n < 77) {
        n = 77;
    }
    x = 0x90 - n / 2;
    y = 0x92;
    func_80200F70(D_801F36C0 + 0x520, D_801F0B90 + 0x3E28, 32, 45, 10);
    func_80200DD0(x, y, 0x76);
    func_80215494_strip(&D_800E9BA0, (x + 16) << 2, (y + 3) << 2, (x + (n + 16)) << 2, (y + 24) << 2);
    func_80200DD0(x + n + 16, y, 0x77);
    if ((u8)len < 77) {
        x = 0xA0 - (u8)len / 2;
    } else {
        x += 16;
    }
    func_80179034((void *)D_8021AA70_ovl_171EA0->w60, x, y + 6);
}
#else
INCLUDE_ASM("asm/nonmatchings/171EA0", func_80215494_ovl_171EA0);
#endif

INCLUDE_ASM("asm/nonmatchings/171EA0", func_80215780_ovl_171EA0);

void func_80216CD8_ovl_171EA0(void) {
    func_80179018();
    D_8018F480 = 0;
}

void func_80216CFC_ovl_171EA0(void) {
    if (D_80214E84 == 0) {
        D_801F0DE0 = 0;
        D_801F0DE8 = 0;
        D_801F365D &= 0xFE;
    }
}

void func_80216D38_ovl_171EA0(void) {
    u8 *u = D_801F0CB0[D_801F3658];
    u8 pad[16]; /* unused, but the original frame has room for it */

    if (D_80214E84 != 0) {
        return;
    }
    D_801F0DE0 = 4;
    D_801F0FE1 = func_801DADF0(u);
    D_801F0FDF = 5;
    D_801F0FE0 = 1;
    if ((func_801DD244() && !(*(u16 *)(D_801951CC + *(s32 *)(u + 0x74) * 36) & 6)) || func_80186210(30)) {
        D_801F0FDF = 0;
        D_801F0FE0 = 2;
    } else if (func_801DD244()) {
        D_801F0FE0 = 0;
    }
    D_80210219 = 0x11;
}
