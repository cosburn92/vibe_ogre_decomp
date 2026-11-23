#include "common.h"

/* 151F40 */

#include "tables.h"
#include "scene.h"

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

typedef struct {
    Character c;
    u8 pad[4];
} PlayerChar;

typedef struct {
    /* 0x00 */ s32 w0;
    /* 0x04 */ u8 unk04[4];
    /* 0x08 */ s32 w8;
    /* 0x0C */ u8 unk0C[0x18];
} Rec151; /* size 0x24 */

extern Gfx *D_800E9BA0;
extern PlayerChar D_80193BC0[];
extern Character D_80195560[];
extern u8 *D_801F0B90;
extern u8 D_80210258_ovl_14EBE0[];
extern u8 D_802102B8_ovl_14EBE0[];
extern u8 D_80213648_ovl_14EBE0[];
extern void *D_80214F5C_ovl_14EBE0;
extern u8 D_8018F480;

void func_80200F70_ovl_14EBE0(void *pal, void *img, u16 w, u16 h, u16 mode);
void func_80200DD0_ovl_14EBE0(void *a, s32 b, s32 c);
void func_80179018(void);
void *LoadChunk(u32 handle);
void *HFree(void *p);
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern u8 *D_80213778_ovl_14EBE0;
extern u8 *D_80213670_ovl_14EBE0;
extern u16 (*D_80213068_ovl_14EBE0[])(u8 cls, u8 base);
typedef struct {
    s32 w0;
    u8 b[4];
    s32 w8;
    s32 wC;
} Rec151_16;
extern s8 (*D_80213054_ovl_14EBE0[])(u16 v);
extern u16 D_80190EBC[];
extern u16 D_80190F82;
u16 func_80201D1C_ovl_14EBE0(u8 side, u8 idx, u8 stat);
void func_802001A8_ovl_14EBE0(void *a, s32 b, u16 c, s32 d);
extern u8 D_80213780_ovl_14EBE0;
extern u8 D_80213781_ovl_14EBE0;
extern char D_80214D10_ovl_14EBE0[];
s32 func_80076F5C(s32 a, void *fn, s32 b, s32 c, s32 d, s32 e, s32 f);
void func_80205F2C_ovl_14EBE0();
void func_8020CDA0_ovl_14EBE0(s32 a);
void osSyncPrintf(const char *fmt, ...);
extern u8 *D_801F36C0;
u16 func_80201B68_ovl_14EBE0(u8 side, u8 idx, u8 slot);
void func_80201AFC_ovl_14EBE0(u8 enemy, u8 idx, u8 *cls, u8 *base);
extern u16 *D_800C4C4C;
extern u8 *D_80213778_ovl_14EBE0;
extern s32 *D_80214E60_ovl_14EBE0;
extern s32 D_80214E70_ovl_14EBE0;
typedef struct {
    s32 id;
    u8 b4;
    u8 b5;
    u8 b6;
    u8 b7;
} Row151;
#define SLOT151(k) (D_80213778_ovl_14EBE0 + (u8)(k) * 8)
extern u8 D_80214EB8_ovl_14EBE0;
extern u8 D_80214EB9_ovl_14EBE0;
void func_80204210_ovl_14EBE0(s16 id);
/* --- end decls --- */

#ifdef NON_MATCHING
/* m2c draft, 75 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern s32 D_80213180_ovl_14EBE0;

void func_80200DD0_ovl_14EBE0(void *a, s32 b, s32 c) {
    Gfx *temp_t1;
    Gfx *temp_t2;
    Gfx *temp_v1_2;
    s16 temp_t3;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_t0;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a0;
    s32 var_v0;
    void *temp_a2;
    void *temp_a3;

    temp_t1 = D_800E9BA0;
    D_800E9BA0 = temp_t1 + 8;
    temp_t2 = temp_t1 + 0x10;
    temp_t1->w0 = 0xE7000000;
    temp_a2 = ((c & 0xFFFF) * 8) + &D_80213180_ovl_14EBE0;
    temp_t1->w1 = 0;
    temp_t3 = (s32) a * 4;
    D_800E9BA0 = temp_t2;
    D_800E9BA0 = temp_t1 + 0x18;
    FIELD(temp_t1, s32, 0xC) = (s32) (((((s32) a * 4) & ((s32) ~temp_t3 >> 0x1F) & 0xFFC) << 0xC) | ((b * 4) & ((s32) ~(s16) (b * 4) >> 0x1F) & 0xFFC));
    FIELD(temp_t1, s32, 0x10) = 0xE1000000;
    temp_a3 = FIELD(temp_a2, u16, 0) + a;
    temp_t0 = FIELD(temp_a2, u16, 2) + b;
    FIELD(temp_t1, s32, 8) = (s32) (((((s32) temp_a3 * 4) & ((s32) ~(s16) ((s32) temp_a3 * 4) >> 0x1F) & 0xFFC) << 0xC) | (((temp_t0 * 4) & ((s32) ~(s16) (temp_t0 * 4) >> 0x1F) & 0xFFC) | 0xE4000000));
    temp_a1 = FIELD(temp_a2, s16, 6) << 5;
    temp_a0 = FIELD(temp_a2, s16, 4) << 5;
    if (temp_t3 < 0) {
        temp_v1 = temp_t3 * 8;
        var_a0 = (temp_a0 - (temp_v1 & -(temp_v1 < 1))) << 0x10;
    } else {
        var_a0 = temp_a0 << 0x10;
    }
    if (!(b & 0x20000000)) {
        var_v0 = temp_a1 & 0xFFFF;
    } else {
        temp_v0 = (s32) (b << 0x12) >> 0xD;
        var_v0 = (temp_a1 - (temp_v0 & -(temp_v0 < 1))) & 0xFFFF;
    }
    temp_t2->w1 = var_a0 | var_v0;
    temp_v1_2 = D_800E9BA0;
    D_800E9BA0 = temp_v1_2 + 8;
    temp_v1_2->w0 = 0xF1000000;
    D_800E9BA0 = temp_v1_2 + 0x10;
    temp_v1_2->w1 = 0x04000400;
    FIELD(temp_v1_2, s32, 8) = 0xE7000000;
    FIELD(temp_v1_2, s32, 0xC) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/151F40", func_80200DD0_ovl_14EBE0);
#endif

#include "gbi_ultra.h"
/* Texture wrap/mask preset */
typedef struct {
    s32 cms;
    s32 cmt;
    s32 masks;
    s32 maskt;
} TexMode151;
extern TexMode151 D_80213588_ovl_14EBE0[];

/* Loads a CI4 texture (w x h pixels at img) with its 16-colour palette pal; wrap/mask settings
 * come from preset `mode` in D_80213588 */
void func_80200F70_ovl_14EBE0(void *pal, void *img, u16 w, u16 h, u16 mode) {
    TexMode151 *m = &D_80213588_ovl_14EBE0[mode];

    gDPLoadTLUT_pal16(D_800E9BA0++, 0, pal);
    gDPLoadTextureBlock_4b(D_800E9BA0++, img, G_IM_FMT_CI, w, h, 0, m->cms, m->cmt, m->masks, m->maskt, 0, 0);
}

/* Loads a 256-colour TLUT from pal */
void func_8020122C_ovl_14EBE0(u32 pal) {
    Gfx *g;

    g = D_800E9BA0++;
    g->w0 = 0xFD100000;
    g->w1 = pal;
    g = D_800E9BA0++;
    g->w0 = 0xE8000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xF5000100;
    g->w1 = 0x07000000;
    g = D_800E9BA0++;
    g->w0 = 0xE6000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xF0000000;
    g->w1 = 0x073FC000;
    g = D_800E9BA0++;
    g->w0 = 0xE7000000;
    g->w1 = 0;
}

/* Loads a 16-colour TLUT from pal */
void func_802012D8_ovl_14EBE0(u32 pal) {
    Gfx *g;

    g = D_800E9BA0++;
    g->w0 = 0xFD100000;
    g->w1 = pal;
    g = D_800E9BA0++;
    g->w0 = 0xE8000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xF5000100;
    g->w1 = 0x07000000;
    g = D_800E9BA0++;
    g->w0 = 0xE6000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xF0000000;
    g->w1 = 0x0703C000;
    g = D_800E9BA0++;
    g->w0 = 0xE7000000;
    g->w1 = 0;
}

/* Sets the scissor box (x0, y0) - (x1, y1), clamped to the 320x240 screen, between pipe syncs */
void func_80201384_ovl_14EBE0(s32 x0, s32 y0, s32 x1, s32 y1) {
    gDPPipeSync(D_800E9BA0++);
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xED000000 | _SHIFTL((s32)((f32)(x0 < 0 ? 0 : x0) * 4.0f), 12, 12) |
                 _SHIFTL((s32)((f32)(y0 < 0 ? 0 : y0) * 4.0f), 0, 12);
        _g->w1 = _SHIFTL((s32)((f32)(x1 == 320 ? 319 : x1) * 4.0f), 12, 12) |
                 _SHIFTL((s32)((f32)(y1 == 240 ? 239 : y1) * 4.0f), 0, 12);
    }
    gDPPipeSync(D_800E9BA0++);
}

/* Rank 1-3 of stat i: how many thirds of the cap (D_80190F82) it reaches */
#ifdef NON_MATCHING
/* loop condition compiled as a branchless and in the original */
u16 func_802014C8_ovl_14EBE0(u8 i) {
    s32 pad;
    u16 q = D_80190F82 / 3;
    s32 v = D_80190EBC[i] - q;
    u16 n = 0;

    do {
        n++;
        if (!(v > 0 && n < 3)) {
            break;
        }
        v -= q;
    } while (1);
    if (n >= 4) {
        n = 3;
    }
    return n;
}
#else
INCLUDE_ASM("asm/nonmatchings/151F40", func_802014C8_ovl_14EBE0);
#endif

INCLUDE_ASM("asm/nonmatchings/151F40", func_8020153C_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_802017C0_ovl_14EBE0);

/* Sum of stat k's bonus over the four item slots */
s16 func_80201A44_ovl_14EBE0(s32 side, s32 idx, s32 k) {
    u8 cls;
    u8 base;
    s16 sum = 0;
    s32 i;

    func_80201AFC_ovl_14EBE0(side, idx, &cls, &base);
    for (i = 1; i < 5; i++) {
        sum += (s8)D_80213054_ovl_14EBE0[(u8)k](func_80201B68_ovl_14EBE0(side, idx, i));
    }
    return sum;
}

/* Index clamp and table select laid out differently. */
void func_80201AFC_ovl_14EBE0(u8 enemy, u8 idx, u8 *cls, u8 *base)
{
  Character *c;
  if (idx >= 100)
  {
    idx = 0;
  }
  if (!enemy)
  {
    c = &D_80193BC0[idx].c;
  }
  else
  {
    c = &D_80195560[idx];
  }
  *cls = c->cls;
  *base = c->baseCls;
}

/* Item in equipment slot 1-4, or the class default (D_80213068) when the slot is empty */
u16 func_80201B68_ovl_14EBE0(u8 side, u8 idx, u8 slot) {
    Character *c;
    u16 v;
    u8 cls;
    u8 base;

    if (side == 0) {
        c = &D_80193BC0[idx].c;
    } else {
        c = &D_80195560[idx];
    }
    cls = c->cls;
    base = c->baseCls;
    v = 0;
    switch (slot) {
        case 1:
            v = c->items[0];
            break;
        case 2:
            v = c->items[1];
            break;
        case 3:
            v = c->items[2];
            break;
        case 4:
            v = c->items[3];
            break;
    }
    if (v == 0 && (slot != 0 & slot < 5)) {
        v = D_80213068_ovl_14EBE0[slot](cls, base);
    }
    return v;
}

s16 func_80201C7C_ovl_14EBE0(u8 side, u8 idx, u8 k) {
    s16 sum = 0;
    s32 i;

    for (i = 1; i < 5; i++) {
        sum += D_80213054_ovl_14EBE0[k](func_80201D1C_ovl_14EBE0(side, idx, i));
    }
    return sum;
}

u16 func_80201D1C_ovl_14EBE0(u8 side, u8 idx, u8 stat) {
    Character *c;

    if (side == 0) {
        c = &D_80193BC0[idx].c;
    } else {
        c = &D_80195560[idx];
    }
    return D_80213068_ovl_14EBE0[stat](c->cls, c->baseCls);
}

/* Equipped item `slot` (1-4) of a character (side 0 player, 1 enemy), 0 if slot is out of range */
u16 func_80201D9C_ovl_14EBE0(u8 side, u8 idx, u8 slot) {
    Character *c;
    u16 v;

    if (side == 0) {
        c = &D_80193BC0[idx].c;
    } else {
        c = &D_80195560[idx];
    }
    v = 0;
    switch (slot) {
        case 1:
            v = c->items[0];
            break;
        case 2:
            v = c->items[1];
            break;
        case 3:
            v = c->items[2];
            break;
        case 4:
            v = c->items[3];
            break;
    }
    return v;
}

INCLUDE_ASM("asm/nonmatchings/151F40", func_80201E4C_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80202140_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80202434_ovl_14EBE0);

/* Base stat `stat` (0 str .. 5 dex) of a character (side 0 player, else enemy); idx >= 100 reads slot 0 */
u16 func_80202728_ovl_14EBE0(u8 side, u8 idx, u8 stat) {
    Character *c;
    u16 v;
    u8 i;

    i = idx < 100 ? idx : 0;
    if (side == 0) {
        c = &D_80193BC0[i].c;
    } else {
        c = &D_80195560[i];
    }
    v = 0;
    switch (stat) {
        case 0:
            v = c->str;
            break;
        case 1:
            v = c->vit;
            break;
        case 2:
            v = c->intl;
            break;
        case 3:
            v = c->men;
            break;
        case 4:
            v = c->agi;
            break;
        case 5:
            v = c->dex;
            break;
    }
    return v;
}

void func_802027DC_ovl_14EBE0(void) {
    Gfx *g = D_800E9BA0++;

    g->w0 = 0xDE000000;
    g->w1 = (u32)D_80213648_ovl_14EBE0;
    func_80200F70_ovl_14EBE0(D_80210258_ovl_14EBE0, D_801F0B90 + 0x948, 0x40, 0x40, 2);
}

void func_80202840_ovl_14EBE0(void) {
    Gfx *g = D_800E9BA0++;

    g->w0 = 0xDE000000;
    g->w1 = (u32)D_80213648_ovl_14EBE0;
    func_80200F70_ovl_14EBE0(D_802102B8_ovl_14EBE0, D_801F0B90 + 0x948, 0x40, 0x40, 2);
}

void func_802028A4_ovl_14EBE0(u8 *p, s32 b, u16 c, u16 d) {
    func_80200DD0_ovl_14EBE0(p, b, 2);
    func_802001A8_ovl_14EBE0(p + 0x14, b, c, -3);
    func_80200DD0_ovl_14EBE0(p + 0x2A, b, 7);
    func_802001A8_ovl_14EBE0(p + 0x32, b, d, -3);
}

void func_80202928_ovl_14EBE0(u8 *p, s32 b) {
    func_80200DD0_ovl_14EBE0(p, b, 2);
    func_80200DD0_ovl_14EBE0(p + 0x2A, b, 7);
}

#ifdef NON_MATCHING
/* m2c draft, 54 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void func_8020296C_ovl_14EBE0(s32 arg0, s32 arg1, s32 arg2) {
    Gfx *temp_a1;
    Gfx *temp_a2;
    Gfx *temp_v1;
    Gfx *temp_v1_3;
    s16 temp_s0;
    s32 temp_s1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_v0;

    temp_v1 = D_800E9BA0;
    D_800E9BA0 = temp_v1 + 8;
    temp_v1->w0 = 0xDE000000;
    temp_v1->w1 = (u32) D_80213648_ovl_14EBE0;
    func_80200F70_ovl_14EBE0(D_801F36C0 + ((arg2 << 5) + 0x1E0), D_801F0B90 + 0x1868, 0x10, 0x50, 2);
    temp_a1 = D_800E9BA0;
    temp_s1 = arg2 << 9;
    D_800E9BA0 = temp_a1 + 8;
    temp_a2 = temp_a1 + 0x10;
    temp_a1->w0 = 0xE7000000;
    temp_v0 = arg0 + 0xF;
    temp_v0_2 = arg1 + 0xF;
    temp_s0 = arg0 * 4;
    FIELD(temp_a1, s32, 8) = (s32) ((((temp_v0 * 4) & ((s32) ~(s16) (temp_v0 * 4) >> 0x1F) & 0xFFC) << 0xC) | (((temp_v0_2 * 4) & ((s32) ~(s16) (temp_v0_2 * 4) >> 0x1F) & 0xFFC) | 0xE4000000));
    D_800E9BA0 = temp_a2;
    D_800E9BA0 = temp_a1 + 0x18;
    temp_a1->w1 = 0;
    FIELD(temp_a1, s32, 0xC) = (s32) ((((arg0 * 4) & ((s32) ~temp_s0 >> 0x1F) & 0xFFC) << 0xC) | ((arg1 * 4) & ((s32) ~(s16) (arg1 * 4) >> 0x1F) & 0xFFC));
    FIELD(temp_a1, s32, 0x10) = 0xE1000000;
    if (temp_s0 < 0) {
        temp_v1_2 = temp_s0 * 8;
        var_a0 = (temp_v1_2 & -(temp_v1_2 < 1)) * -0x10000;
    } else {
        var_a0 = 0;
    }
    if (!(arg1 & 0x20000000)) {
        var_v0 = temp_s1 & 0xFFFF;
    } else {
        temp_v0_3 = (s32) (arg1 << 0x12) >> 0xD;
        var_v0 = (temp_s1 - (temp_v0_3 & -(temp_v0_3 < 1))) & 0xFFFF;
    }
    temp_a2->w1 = var_a0 | var_v0;
    temp_v1_3 = D_800E9BA0;
    D_800E9BA0 = temp_v1_3 + 8;
    temp_v1_3->w0 = 0xF1000000;
    D_800E9BA0 = temp_v1_3 + 0x10;
    temp_v1_3->w1 = 0x04000400;
    FIELD(temp_v1_3, s32, 8) = 0xE7000000;
    FIELD(temp_v1_3, s32, 0xC) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/151F40", func_8020296C_ovl_14EBE0);
#endif

/* Draws status icon k (1 uses the first palette, others the second) at (a, b) */
void func_80202B70_ovl_14EBE0(void *a, s32 b, u8 k) {
    if (k == 0) {
        return;
    }
    gDPSetTextureLUT(D_800E9BA0++, G_TT_RGBA16);
    if (k == 1) {
        gDPLoadTLUT_pal16(D_800E9BA0++, 0, D_801F36C0 + 0x40);
    } else {
        gDPLoadTLUT_pal16(D_800E9BA0++, 0, D_801F36C0 + 0x60);
    }
    gDPLoadTextureBlock_4b(D_800E9BA0++, D_801F0B90 + ((k << 7) + 0x450), G_IM_FMT_CI, 16, 16, 0, 0, 0, 0, 0, 0, 0);
    func_80200DD0_ovl_14EBE0(a, b, 0xD);
}

extern u8 D_80210AD0_ovl_14EBE0[];
extern u8 *D_80214E80_ovl_14EBE0;

/* Draws the 32x16 gauge icon at (x, y) for value v (0-100 in 7 steps) */
void func_80202E10_ovl_14EBE0(void *x, s32 y, u8 v) {
    u16 k = v / 14.285714f;

    if (k > 6) {
        k = 6;
    }
    gSPDisplayList(D_800E9BA0++, D_80213648_ovl_14EBE0);
    {
        Gfx *_g = D_800E9BA0++; /* gDPSetTexturePersp(G_TP_NONE) */

        _g->w0 = 0xE3000C00;
        _g->w1 = 0;
    }
    func_80200F70_ovl_14EBE0(D_80210AD0_ovl_14EBE0, D_80214E80_ovl_14EBE0 + (k << 8), 32, 16, 2);
    func_80200DD0_ovl_14EBE0(x, y, 9);
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xD7000000;
        _g->w1 = 0x80008000;
    }
}

/* Draws gauge cap: tiles 10/11/12 by fill level (pct / 14.29, 0-6) */
void func_80202F54_ovl_14EBE0(u8 *p, s32 b, u8 pct) {
    u16 v = pct / 14.285714f;

    if (v > 6) {
        v = 6;
    }
    switch (v) {
        case 0:
        case 1:
            func_80200DD0_ovl_14EBE0(p - (v * 2 - 12), b + 8, 10);
            break;
        case 5:
        case 6:
            func_80200DD0_ovl_14EBE0(p - (v * 2 - 12), b + 8, 12);
            break;
        default:
            func_80200DD0_ovl_14EBE0(p - (v * 2 - 12), b + 8, 11);
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/151F40", func_80203050_ovl_14EBE0);

#ifdef NON_MATCHING
/* Constant select laid out differently. */
void func_80203524_ovl_14EBE0(void *a, s32 b, u8 c) {
    func_80200DD0_ovl_14EBE0(a, b, (c == 3) ? 0x11 : 0x10);
}
#else
INCLUDE_ASM("asm/nonmatchings/151F40", func_80203524_ovl_14EBE0);
#endif

INCLUDE_ASM("asm/nonmatchings/151F40", func_80203558_ovl_14EBE0);

/* Draws digit cell n % 9 (blank row when n is 0) at (x + 7, y) after its frame */
#ifdef NON_MATCHING
/* 130/130 instructions, 6 words differ: the original keeps the quotient and remainder of n % 9 in d's register */
void func_80203D9C_ovl_14EBE0(s32 x, s32 y, s32 n) {
    s32 d = n % 9;

    d -= d != 0;
    func_80200DD0_ovl_14EBE0(x, y + 3, 0x46);
    gDPPipeSync(D_800E9BA0++);
    gSPScisTextureRectangle(D_800E9BA0++, (x + 7) << 2, y << 2, (x + 13) << 2, (y + 9) << 2, 0,
                            d * 7 << 5, (-(n == 0) & 0x340) | 0x200, 1 << 10, 1 << 10);
    gDPPipeSync(D_800E9BA0++);
}
#else
INCLUDE_ASM("asm/nonmatchings/151F40", func_80203D9C_ovl_14EBE0);
#endif

void func_80203FA4_ovl_14EBE0(s32 a, s32 b) {
    Gfx *g;

    g = D_800E9BA0++;
    g->w0 = 0xE7000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xD7000002;
    g->w1 = 0x80008000;
    func_80200F70_ovl_14EBE0(D_801F36C0 + 0x2E0, D_801F0B90 + 0x27A8, 16, 8, 2);
    func_80200DD0_ovl_14EBE0((void *)a, b, 0x47);
}

#ifdef NON_MATCHING
/* display-list setup: constant loads and pointer updates are scheduled differently */
void func_80204050_ovl_14EBE0(s32 a) {
    Gfx *g;

    g = D_800E9BA0++;
    g->w0 = 0xFA000000;
    g->w1 = a | 0xFFFFFF00;
    g = D_800E9BA0++;
    g->w0 = 0xE3000C00;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xE3001201;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xE200001C;
    if (a == 0xFF) {
        g->w1 = 0x0F0A7008;
    } else {
        g->w1 = 0x00504240;
    }
    g = D_800E9BA0++;
    g->w0 = 0xFC119623;
    g->w1 = 0xFF2FFFFF;
}
#else
INCLUDE_ASM("asm/nonmatchings/151F40", func_80204050_ovl_14EBE0);
#endif

void func_80204120_ovl_14EBE0(u8 mode, s32 *p, u8 b, u8 c) {
    s32 i;

    D_80214E60_ovl_14EBE0 = p;
    if (mode) {
        D_80214EB9_ovl_14EBE0 = *p | 0x80;
    } else {
        D_80214EB8_ovl_14EBE0 = b;
        if (b < 8) {
            D_80214EB8_ovl_14EBE0 = b | 0x80;
        } else {
            D_80214EB8_ovl_14EBE0 = 0x80;
        }
        D_80214EB9_ovl_14EBE0 = D_80214EB8_ovl_14EBE0;
    }
    i = func_80076F5C(0xC000, func_80204210_ovl_14EBE0, 0x58, 0x78, 0x62, 0x82, 0xC8);
    D_800E82C8[i].unk88 = b;
    D_800E82C8[i].unk89 = c;
    D_800E82C8[i].unk8A = mode;
}

typedef struct {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u8 flags2;
    /* 0x03 */ u8 flags3;
    /* 0x04 */ u8 unk04[0x10];
    /* 0x14 */ void (*update)();
    /* 0x18 */ void (*draw)();
    /* 0x1C */ void (*exit)();
    /* 0x20 */ u16 size;
    /* 0x22 */ u8 unk22[2];
    /* 0x24 */ s32 w24;
    /* 0x28 */ u8 unk28[0x60];
    /* 0x88 */ u8 b88;
    /* 0x89 */ u8 b89;
    /* 0x8A */ u8 b8A;
} Win151;
extern Win151 D_800E7A30;
extern u8 D_800E91D0[];
void func_8020439C_ovl_14EBE0();
void func_80204B34_ovl_14EBE0(void);
u8 func_80204BA4_ovl_14EBE0(Rec151 *r, u8 k);
u8 func_80204BE8_ovl_14EBE0(Rec151 *a, u8 id);

/* Window init for list id: installs the update/draw callbacks and resets the list state */
#ifdef NON_MATCHING
/* 99/99 instructions, 10 words differ: the last five stores reload the record pointer into v1/a0 where GCC here uses v0 */
void func_80204210_ovl_14EBE0(s16 id) {
    D_800E7A30.flags2 |= 8;
    D_800E7A30.flags3 |= 1;
    D_800E7A30.flags2 |= 9;
    D_800E7A30.flags |= 0x200;
    D_800E7A30.update = func_8020439C_ovl_14EBE0;
    D_800E7A30.draw = func_80204B34_ovl_14EBE0;
    D_800E7A30.size = 0x7C;
    D_800E7A30.w24 = 0;
    *(s16 *)D_800E91D0 = id;
    *(s32 **)(D_800E91D0 + 0x60) = D_80214E60_ovl_14EBE0;
    D_800E91D0[0x68] = D_800E7A30.b88;
    D_800E91D0[0x66] = D_800E7A30.b89;
    D_800E91D0[0x78] = D_800E7A30.b8A;
    D_80213670_ovl_14EBE0[0x67] = func_80204BA4_ovl_14EBE0(*(Rec151 **)(D_80213670_ovl_14EBE0 + 0x60), D_80213670_ovl_14EBE0[0x66]);
    D_80213670_ovl_14EBE0[0x64] = func_80204BE8_ovl_14EBE0(*(Rec151 **)(D_80213670_ovl_14EBE0 + 0x60), D_80213670_ovl_14EBE0[0x66]);
    D_80213670_ovl_14EBE0[0x6A] = 0;
    D_80213670_ovl_14EBE0[0x6B] = 0;
    D_80213670_ovl_14EBE0[0x6C] = 0;
    D_80213670_ovl_14EBE0[0x6D] = 0;
    D_80213670_ovl_14EBE0[0x6E] = 0;
    D_80213670_ovl_14EBE0[0x69] = 0xFF;
    D_80213670_ovl_14EBE0[0x65] = D_80213670_ovl_14EBE0[0x64];
    D_80213670_ovl_14EBE0[0x6F] = 0;
    D_80213670_ovl_14EBE0[0x70] = 0;
    D_80213670_ovl_14EBE0[0x76] = 0;
    *(s16 *)(D_80213670_ovl_14EBE0 + 0x72) = 0xFF;
    *(s16 *)(D_80213670_ovl_14EBE0 + 0x74) = 0;
    *(s32 *)(D_80213670_ovl_14EBE0 + 0x5C) = 0;
    D_80213670_ovl_14EBE0[0x77] = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/151F40", func_80204210_ovl_14EBE0);
#endif

INCLUDE_ASM("asm/nonmatchings/151F40", func_8020439C_ovl_14EBE0);

void func_80204B34_ovl_14EBE0(void) {
    func_80179018();
    D_8018F480 = 0;
}

void func_80204B58_ovl_14EBE0(void) {
    D_80214F5C_ovl_14EBE0 = LoadChunk(0x1DF98EA);
}

void func_80204B80_ovl_14EBE0(void) {
    HFree(D_80214F5C_ovl_14EBE0);
}

/* Number of records (up to the -1 terminator) whose +8 is k */
u8 func_80204BA4_ovl_14EBE0(Rec151 *r, u8 k) {
    u8 n = 0;
    u8 i = 0;
    Rec151 *e;

    do {
        e = &r[i];
        if (e->w8 == k) {
            n++;
        }
        i++;
    } while (e->w0 != -1);
    return n;
}

u8 func_80204BE8_ovl_14EBE0(Rec151 *a, u8 id) {
    s8 j = -1;
    u32 i = 0;
    Rec151 *r;

    do {
        r = &a[(u8)i];
        if (r->w8 == id) {
            j++;
        }
        i++;
    } while (j != (s8)D_80213670_ovl_14EBE0[0x68]);
    return FIELD(r, u8, 3);
}

INCLUDE_ASM("asm/nonmatchings/151F40", func_80204C3C_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_8020521C_ovl_14EBE0);

s32 func_80205D20_ovl_14EBE0(u8 a) {
    u8 *f = &D_80213780_ovl_14EBE0;
    s32 i;
    s32 r;

    if (*f != 0) {
        *f = 0;
        D_80213781_ovl_14EBE0 = a;
        i = func_80076F5C(0xC000, func_80205F2C_ovl_14EBE0, 0x19, 0x28, 0x23, 0x32, 0xC8);
        D_800E82C8[i].unk88 = 0xFF;
        func_8020CDA0_ovl_14EBE0(6);
        r = 1;
    } else {
        osSyncPrintf(D_80214D10_ovl_14EBE0);
        r = 0;
    }
    return r;
}

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern s32 D_800E8328;

s32 func_80205DC8_ovl_14EBE0(s32 arg0, s32 *arg1, s32 arg2) {
    s32 *var_v1;
    s32 temp_a1;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v0_2;
    s8 var_a0;

    if (D_80213780_ovl_14EBE0 == 0) {
        osSyncPrintf(D_80214D10_ovl_14EBE0);
        return 0;
    }
    D_80213780_ovl_14EBE0 = 0;
    D_80213781_ovl_14EBE0 = 3;
    temp_a1 = func_80076F5C(0xC000, func_80205F2C_ovl_14EBE0, 0x19, 0x28, 0x23, 0x32, 0xC8);
    if (arg2 >= 0) {
        var_a0 = 0;
        if (*arg1 >= 0) {
            var_v1 = arg1;
            var_v0 = *var_v1;
loop_5:
            var_v0_2 = var_a0 < 0x1E;
            if (var_v0 != arg2) {
                var_v1 += 4;
                var_v0 = *var_v1;
                var_a0 += 1;
                if (var_v0 < 0) {
                    goto block_7;
                }
                goto loop_5;
            }
        } else {
block_7:
            var_v0_2 = var_a0 < 0x1E;
        }
        if ((var_v0_2 == 0) || (*((var_a0 * 4) + arg1) < 0)) {
            goto block_10;
        }
        *(&D_800E8328 + 0x28 + (temp_a1 * 0xA8)) = var_a0;
    } else {
block_10:
        *(&D_800E8328 + 0x28 + (temp_a1 * 0xA8)) = 0xFF;
    }
    temp_v1 = temp_a1 * 0xA8;
    *(&D_800E8328 + temp_v1) = arg0;
    *(&D_800E8328 + 4 + temp_v1) = arg1;
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/151F40", func_80205DC8_ovl_14EBE0);
#endif

INCLUDE_ASM("asm/nonmatchings/151F40", func_80205F2C_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80206340_ovl_14EBE0);

/* Steps the cursor blink (0x5F3), bob offset (0x5F4) and pulse counter (0x5F5) */
/* Steps the cursor blink (0x5F3), bob offset (0x5F4) and pulse counter (0x5F5) */
/* Steps the cursor blink (0x5F3), bob offset (0x5F4) and pulse counter (0x5F5) */
/* Steps the cursor blink (0x5F3), bob offset (0x5F4) and pulse counter (0x5F5) */
/* Steps the cursor blink (0x5F3), bob offset (0x5F4) and pulse counter (0x5F5) */
/* Steps the cursor blink (0x5F3), bob offset (0x5F4) and pulse counter (0x5F5) */
/* Steps the cursor blink (0x5F3), bob offset (0x5F4) and pulse counter (0x5F5) */
/* Steps the cursor blink (0x5F3), bob offset (0x5F4) and pulse counter (0x5F5) */
void func_80206C70_ovl_14EBE0(void) {
    u8 v;

    v = D_80213778_ovl_14EBE0[0x5F3];
    if ((s8)(v & 0x7F) >= 0x10) {
        D_80213778_ovl_14EBE0[0x5F3] = v & 0x80;
        D_80213778_ovl_14EBE0[0x5F3] ^= 0x80;
    }
    D_80213778_ovl_14EBE0[0x5F3]++;
    if (D_80213778_ovl_14EBE0[0x5F3] & 0x80) {
        D_80213778_ovl_14EBE0[0x5F4] += 2;
    } else {
        D_80213778_ovl_14EBE0[0x5F4] -= 2;
    }
    v = D_80213778_ovl_14EBE0[0x5F5];
    if (v & 0x80) {
        if (v & 0xF) {
            D_80213778_ovl_14EBE0[0x5F5] = v - 1;
            D_80213778_ovl_14EBE0[0x5F5] |= 0x80;
        } else {
            D_80213778_ovl_14EBE0[0x5F5] = 0;
        }
    } else if ((v & 0xF) < 4) {
        D_80213778_ovl_14EBE0[0x5F5] = v + 1;
        D_80213778_ovl_14EBE0[0x5F5] &= 0x7F;
    } else {
        D_80213778_ovl_14EBE0[0x5F5] = 0x84;
    }
    func_80179018();
}

/* addu operand order (1 instruction) */
void func_80206D78_ovl_14EBE0(void)
{
  u8 *o = D_80213778_ovl_14EBE0;
  u8 *new_var;
  s8 v = o[0x5E];
  u8 k = o[0x605 + (v * 10)];
  if (v == 1)
  {
    new_var = &(o + (k * 8))[0x35C];
    o[0x5D8] = *new_var;
  }
  else
  {
    o[0x5D8] = 0;
  }
}

void func_80206DBC_ovl_14EBE0(u8 a, s16 *p) {
    p[2] = 4;
    p[0] = 0;
    p[1] = 0;
    p[3] = a - 1;
    p[4] = 0xFF;
}

/* Moves the 3-way cursor with the pad (the third entry needs flag +0x5D8 to be reachable) */
s8 func_80206DE4_ovl_14EBE0(s8 cur) {
    u16 b = *D_800C4C4C;

    if (b & 0x100) {
        if (cur != 1 || D_80213778_ovl_14EBE0[0x5D8] != 0) {
            if (++cur == 2) {
                func_8020CDA0_ovl_14EBE0(2);
            }
        }
    } else if (b & 0x200) {
        if (cur >= 2) {
            cur--;
            func_8020CDA0_ovl_14EBE0(2);
        }
    }
    return cur < 0 ? 0 : (cur < 3 ? cur : 2);
}

typedef struct {
    u8 id;
    u8 flags;
    u8 rest[23];
} Sq151;
extern Sq151 gSquads[];

extern u8 D_80213782_ovl_14EBE0;

/* Picks the target of menu choice `mode` for row recs[mode] (10-byte rows, target id at +1):
 * 0 a table entry, 1 the deployed unit (when 0x5F6 is 2), 2 the reserve entry, 3 the first
 * active squad of the slot's side (or none if the slot is taken) */
extern u8 D_80213782_ovl_14EBE0;

/* Picks the target of menu choice `mode` for row recs[mode] (10-byte rows, target id at +1):
 * 0 a table entry, 1 the deployed unit (when 0x5F6 is 2), 2 the reserve entry, 3 the first
 * active squad of the slot's side (or none if the slot is taken) */
#ifdef NON_MATCHING
/* 109/109: case 2 adds the reserve offset before truncating k, and the row address operands are swapped */
void func_80206EB4_ovl_14EBE0(s8 mode, u8 *recs, u8 *tbl, s32 unused, u8 *slots) {
    u8 *sel = &D_80213781_ovl_14EBE0;
    u8 k;
    s32 idx;

    *sel = mode;
    k = recs[mode * 10 + 1];
    switch (mode) {
        case 0:
            D_80213782_ovl_14EBE0 = tbl[k * 12];
            break;
        case 1:
            if ((s8)D_80213778_ovl_14EBE0[0x5F6] == 2) {
                *sel = 0;
                {
                    u8 base = D_80213778_ovl_14EBE0[0x62D];

                    k = D_80213778_ovl_14EBE0[(u8)(base + slots[k * 8 + 5]) + 0x5D9];
                }
                D_80213782_ovl_14EBE0 = tbl[k * 12];
            } else {
                D_80213782_ovl_14EBE0 = k;
            }
            break;
        case 2:
            *sel = 0;
            k += D_80213778_ovl_14EBE0[0x5F7];
            D_80213782_ovl_14EBE0 = tbl[k * 12];
            break;
        case 3:
            if ((*sel = D_800E91D0[k * 8 + 0x3DF]) != 0) {
                D_80213782_ovl_14EBE0 = 0;
            } else {
                u8 side = D_80213778_ovl_14EBE0[k * 8 + 0x3DC] & 0x7F;
                s32 i;
                u32 n = 50;

                for (i = 0; (u8)i < n; i++) {
                    if (gSquads[(u8)i].id == side && (gSquads[(u8)i].flags & 1)) {
                        break;
                    }
                }
                D_80213782_ovl_14EBE0 = i;
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/151F40", func_80206EB4_ovl_14EBE0);
#endif

extern s32 D_801F0BA8;
extern u8 D_80213783_ovl_14EBE0;

/* Sets the cursor target byte D_80213783 for list row `row` of list kind `kind`: a table entry
 * (|0x40) or a raw id (|0x80) */
#ifdef NON_MATCHING
/* 103 vs 106: the original re-masks the row byte (andi 0xFF) in every case, which GCC here omits since it knows the load is zero-extended; the squad search loop branches differ */
void func_80207068_ovl_14EBE0(s8 kind, u8 *rows, u8 *tab, s32 unused, u8 *slots) {
    u8 c = rows[kind * 10 + 1];

    switch (kind) {
        case 0:
            D_80213783_ovl_14EBE0 = tab[c * 12] | 0x40;
            break;
        case 1:
            if ((s8)D_80213778_ovl_14EBE0[0x5F6] != 2) {
                D_80213783_ovl_14EBE0 = c | 0x80;
            } else {
                D_80213783_ovl_14EBE0 = tab[D_80213778_ovl_14EBE0[(u8)(D_80213778_ovl_14EBE0[0x62D] + slots[c * 8 + 5]) + 0x5D9] * 12] | 0x40;
            }
            break;
        case 2:
            D_80213783_ovl_14EBE0 = tab[(c + D_80213778_ovl_14EBE0[0x5F7]) * 12] | 0x40;
            break;
        case 3:
            if (D_800E91D0[c * 8 + 0x3DF] != 0) {
                D_80213783_ovl_14EBE0 = D_801F0BA8 | 0x80;
            } else {
                u8 side = D_80213778_ovl_14EBE0[c * 8 + 0x3DC] & 0x7F;
                s32 i;

                for (i = 0; (u8)i < 50; i++) {
                    if (gSquads[(u8)i].id == side && (gSquads[(u8)i].flags & 1)) {
                        break;
                    }
                }
                D_80213783_ovl_14EBE0 = i | 0x40;
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/151F40", func_80207068_ovl_14EBE0);
#endif

/* Target of menu choice `mode` for row recs[mode] shifted by off (10-byte rows, id at +3): 0 a
 * table entry, 1 the deployed unit (when 0x5F6 is 2), 2 the reserve entry, 3 the first active
 * squad of the slot's side (or D_801F0BA8 if the slot is taken) */
#ifdef NON_MATCHING
/* 92/92: the result and the row id use different registers (a2 vs v1) and the case 1-2 tails are scheduled differently */
s32 func_80207210_ovl_14EBE0(s8 mode, s32 off, u8 *recs, u8 *tbl, s32 unused, u8 *slots) {
    s32 r = 0;
    u8 k = recs[mode * 10 + 3] + off;

    switch (mode) {
        case 0:
            r = tbl[k * 12];
            break;
        case 1:
            r = k;
            if ((s8)D_80213778_ovl_14EBE0[0x5F6] == 2) {
                k = D_80213778_ovl_14EBE0[(u8)(D_80213778_ovl_14EBE0[0x62D] + slots[k * 8 + 5]) + 0x5D9];
                r = tbl[k * 12];
            }
            break;
        case 2:
            k += D_80213778_ovl_14EBE0[0x5F7];
            r = tbl[k * 12];
            break;
        case 3:
            if (D_800E91D0[k * 8 + 0x3DF] != 0) {
                r = D_801F0BA8;
            } else {
                u8 side = D_80213778_ovl_14EBE0[k * 8 + 0x3DC] & 0x7F;
                s32 i;
                u32 n = 50;

                for (i = 0; (u8)i < n; i++) {
                    if (gSquads[(u8)i].id == side && (gSquads[(u8)i].flags & 1)) {
                        break;
                    }
                }
                r = (u8)i;
            }
            break;
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/151F40", func_80207210_ovl_14EBE0);
#endif

typedef struct {
    u8 b[12];
} Ent151;
#define ENT151(i) ((u8 *)((Ent151 *)D_80213778_ovl_14EBE0 + (u8)(i)))

/* Fills n 8-byte list rows from the entries starting at `first` */
#ifdef NON_MATCHING
/* register assignment of out/first/i differs (t0/t1/a3) */
s32 func_80207380_ovl_14EBE0(u8 *out, s32 first, u8 n) {
    u8 i;

    for (i = 0; i < n; i++, first++) {
        u8 *e = ENT151(first);
        u8 *o = i * 8 + out;

        FIELD(o, s32, 0) = FIELD(e, s32, 0x68);
        o[4] = e[0x63] & 0x80;
        o[5] = ENT151(first)[0x61];
        o[7] = 0;
        o[6] = ENT151(first)[0x62];
        if (ENT151(first)[0x63] & 1) {
            o[6] = 0xFF;
            o[7] |= 1;
        }
        if (ENT151(first)[0x63] & 2) {
            o[4] |= 1;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/151F40", func_80207380_ovl_14EBE0);
#endif

#ifdef NON_MATCHING
/* same register pressure as func_80207380: one extra live value spills */
s32 func_8020746C_ovl_14EBE0(u8 *out, s32 first, u8 n) {
    s32 i;
    s32 k = D_80213778_ovl_14EBE0[0x5F7] + first;

    for (i = 0; (u8)i < n; i++, k++) {
        u8 *e = ENT151(k);
        u8 *o = out + (u8)i * 8;

        FIELD(o, s32, 0) = FIELD(e, s32, 0x68);
        o[4] = e[0x63] & 0x80;
        o[5] = ENT151(k)[0x61];
        o[6] = ENT151(k)[0x62];
        o[7] = 0;
        if (ENT151(k)[0x63] & 1) {
            o[6] = 0xFF;
            o[7] |= 1;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/151F40", func_8020746C_ovl_14EBE0);
#endif

/* Fills n list rows from the 8-byte slots at 0x3D8 starting at `first`;
 * sets D_80214E70 when a row's id byte is 0x80-0xFD */
#ifdef NON_MATCHING
/* row filler: structure exact, registers differ (a0/a1/v1 roles) */
s32 func_8020753C_ovl_14EBE0(Row151 *out, s32 first, u8 n) {
    u8 i;
    s32 k = first;

    D_80214E70_ovl_14EBE0 = 0;
    for (i = 0; (u8)i < n; i++, k++) {
        out[(u8)i].id = FIELD(SLOT151(k), s32, 0x3D8);
        out[(u8)i].b4 = SLOT151(k)[0x3DE] & 0x80;
        out[(u8)i].b5 = SLOT151(k)[0x3DC];
        out[(u8)i].b6 = SLOT151(k)[0x3DD];
        out[(u8)i].b7 = SLOT151(k)[0x3DE] & 1;
        if ((out[(u8)i].b5 & 0x80) && out[(u8)i].b5 < 0xFE) {
            D_80214E70_ovl_14EBE0 = 1;
        }
        if (out[(u8)i].b7) {
            out[(u8)i].b6 = 0xFF;
        }
        if (SLOT151(k)[0x3DF]) {
            out[(u8)i].b5 = 0xFF;
        }
        if (SLOT151(k)[0x3DE] & 2) {
            out[(u8)i].b4 |= 1;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/151F40", func_8020753C_ovl_14EBE0);
#endif

INCLUDE_ASM("asm/nonmatchings/151F40", func_8020766C_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80207C94_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_8020808C_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80208304_ovl_14EBE0);

/* 12-byte record sorted by its key byte */
typedef struct {
    s32 a;
    u8 key;
    u8 pad[3];
    s32 c;
} SortRec;

/* Insertion sort of n records by ascending key */
void func_80208920_ovl_14EBE0(SortRec *list, s16 n) {
    s16 i;
    s16 j;
    SortRec tmp;
    u8 key;

    for (i = 1; i < n; i++) {
        key = list[i].key;
        tmp = list[i];
        for (j = i - 1; j >= 0 && key < list[j].key; j--) {
            list[j + 1] = list[j];
        }
        list[j + 1] = tmp;
    }
}

/* Insertion sort of n bytes, ascending */
void func_80208A3C_ovl_14EBE0(u8 *a, s16 n) {
    s16 i;
    s16 j;
    u8 t;

    for (i = 1; i < n; i++) {
        t = a[i];
        for (j = i - 1; j >= 0 && a[j] > t; j--) {
            a[j + 1] = a[j];
        }
        a[j + 1] = t;
    }
}

/* Insertion sort of n 16-byte records by byte 7, ascending */
void func_80208ADC_ovl_14EBE0(Rec151_16 *a, s16 n) {
    s16 i;
    s16 j;
    Rec151_16 t;
    u8 k;

    for (i = 1; i < n; i++) {
        k = a[i].b[3];
        t = a[i];
        for (j = i - 1; j >= 0 && a[j].b[3] > k; j--) {
            a[j + 1] = a[j];
        }
        a[j + 1] = t;
    }
}

INCLUDE_ASM("asm/nonmatchings/151F40", func_80208BE4_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80208E64_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_8020C284_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_8020C7F4_ovl_14EBE0);
