#include "common.h"
#include "tables.h"

/* 18C2E0 */

extern void *D_8021B588_ovl_188B60[2]; /* the two info windows (D_8021B58C is [1]) */

void *func_8017BFB0(s32 a, s32 b, void *c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i, s32 j, s32 k);
typedef struct {
    u32 w0;
    u32 w1;
} Gfx;
#include "gbi_ultra.h"

/* Window object (func_8017BFB0); only the fields used here are named */
typedef struct {
    /* 0x00 */ u8 unk00[0x18];
    /* 0x18 */ s16 fade[2];
    /* 0x1C */ u8 unk1C[0x10];
    /* 0x2C */ s32 x;
    /* 0x30 */ s32 y;
    /* 0x34 */ u8 unk34[0x48];
    /* 0x7C */ s32 rect[4];
} Win18C;

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 flags;
    /* 0x02 */ u8 members[5];
    /* 0x07 */ u8 pos[5];
    /* 0x0C */ u8 harmony;
    /* 0x0D */ u8 items[10];
    /* 0x17 */ u8 strategy;
    /* 0x18 */ u8 legion;
} SquadRec18C; /* size 0x19 */

void func_80219584_ovl_188B60(Win18C *w, s32 page);
extern s32 D_8021B5A4_ovl_188B60;
extern s32 D_8021B5B0_ovl_188B60;
extern Gfx *D_800E9BA0;
extern s8 D_8018F480;
extern u8 *D_801F0B90;
extern u8 *D_801F0BCC;
extern u8 *D_801F36C0;
extern Gfx D_801EB1D0[];
extern u8 D_80210217[][5];   /* formation slot -> map cell (row << 4 | column) */
extern u8 D_80193BC0[][0x38]; /* player characters */
extern u8 gLegions[][11];
extern SquadRec18C gSquads[];
extern u8 D_8021B59E_ovl_188B60;
extern s32 D_8021B5A8_ovl_188B60;
extern s32 D_8021B5AC_ovl_188B60;
extern s32 D_8021B5B4_ovl_188B60;
extern s16 D_8021B5E6_ovl_188B60;
extern s16 D_8021B5EC_ovl_188B60;
void func_8017C4B4(s16 a);
void func_802027DC(void);
void func_80200DD0(s32 x, s32 y, s32 icon);
void func_802001A8(s32 x, s32 y, u16 n, s32 digits);
void func_80200A38(s32 x, s32 y);
void func_8020078C(u8 n, s32 x, s32 y);
void func_80200F70(void *pal, void *img, u16 w, u16 h, u16 mode);
void func_801D66D0(u8 *dst, u8 *legion, u8 formation);
void *func_8016B070(u8 strategy);
void func_80179034(void *s, s32 x, s32 y);
void func_802012D8(void *pal);
void func_80201384(s32 a, s32 b, s32 c, s32 d);
/* Sprite set for the formation editor (D_801ED5C0) */
typedef struct {
    /* 0x00 */ u8 *sheetA; /* class sprites */
    /* 0x04 */ u8 unk04[4];
    /* 0x08 */ u8 *sheetB; /* sprites of classes flagged 0x80 in D_8018ECE4 */
    /* 0x0C */ u8 unk0C[0x88];
    /* 0x94 */ u8 *slots;  /* 32x128 CI4 slot markers */
} SpriteSet18C;

typedef struct {
    s32 x;
    s32 y;
} SlotPos18C;

extern SpriteSet18C *D_801ED5C0;
extern Gfx D_80213648[];
extern u8 D_8021B59D_ovl_188B60;
extern u8 D_8021B5B8_ovl_188B60;
extern u8 *D_8021B5BC_ovl_188B60;
extern u8 D_8021B5C0_ovl_188B60;
extern SlotPos18C D_8021B4B8_ovl_188B60[5];
extern u8 D_80212768[];
extern u8 D_801F39B0[];
extern u8 D_80212518[];
extern u8 D_80212410[];
extern u8 D_8018ECE4[][6];
u8 func_8016DF18(u8 cls, u8 base);
void func_8020122C(void *pal);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/18C2E0", func_80218700_ovl_188B60);

INCLUDE_ASM("asm/nonmatchings/18C2E0", func_802188EC_ovl_188B60);

INCLUDE_ASM("asm/nonmatchings/18C2E0", func_80218F74_ovl_188B60);

void func_8021948C_ovl_188B60(void) {
    void **p = &D_8021B588_ovl_188B60[0];

    if (*p == NULL) {
        *p = func_8017BFB0(0, 0, func_80219584_ovl_188B60, 0x18, 0x18, 0x1C, 0x1C, 0x18, 0x18, 0x91, 0x4A);
    }
}

void func_80219500_ovl_188B60(void) {
    if (D_8021B5A4_ovl_188B60 == -1) {
        D_8021B5A4_ovl_188B60 = D_8021B5B0_ovl_188B60;
        D_8021B588_ovl_188B60[1] = func_8017BFB0(0, 0, func_80219584_ovl_188B60, 0x124, 0x18, 0x128, 0x1C, 0xAF, 0x18, 0x128, 0x4A);
    }
}

/* Draws one page of the squad info window w (fade value per page in w->fade): with a squad
 * selected, its leader, strategy and legion (plus, in the main window, the legion's formation
 * map with this squad's place marked); with none, a fading empty panel. The second window then
 * gets its selection arrows. */
void func_80219584_ovl_188B60(Win18C *w, s32 page) {
    s32 x;
    s32 y;
    s32 sq;
    s32 i;
    u8 slots[5];
    s32 p;
    s32 col;
    s32 row;

    if (w->fade[page] == 0) {
        return;
    }
    x = w->x;
    y = w->y;
    gDPPipeSync(D_800E9BA0++);
    func_8017C4B4(w->fade[page]);
    if (w == D_8021B588_ovl_188B60[0]) {
        sq = D_8021B5AC_ovl_188B60;
    } else {
        sq = D_8021B5B0_ovl_188B60;
    }
    func_802027DC();
    if (sq != 0xFF) {
        func_80200DD0(x + 4, y + 4, 4);
        func_80200DD0(x + 0x17, y + 4, 0);
        func_802001A8(x + 0x28, y + 4, gSquads[sq].unk0, 2);
        func_80200A38(x + 6, y + 0x20);
        if (D_8021B59E_ovl_188B60 == 0 && w == D_8021B588_ovl_188B60[0]) {
            D_8018F480 = 1;
            gDPSetTextureLUT(D_800E9BA0++, G_TT_NONE);
            gDPLoadTextureBlock(D_800E9BA0++, D_801F0BCC, G_IM_FMT_RGBA, G_IM_SIZ_16b, 24, 9, 0, 2, 2, 0, 0, 0, 0);
            gDPPipeSync(D_800E9BA0++);
            gSPTextureRectangle(D_800E9BA0++, (x + 9) << 2, (y + 19) << 2, (x + 19) << 2, (y + 28) << 2, 0, 8 << 5,
                                0, 1 << 10, 1 << 10);
            gDPPipeSync(D_800E9BA0++);
            gDPPipeSync(D_800E9BA0++);
            D_8018F480 = 2;
            gDPSetTextureLUT(D_800E9BA0++, G_TT_RGBA16);
        }
        if (w == D_8021B588_ovl_188B60[0]) {
            func_8020078C(gLegions[D_8021B5B4_ovl_188B60][9] - 1, x + 0x58, y + 4);
            func_80200F70(D_801F36C0 + 0x360, D_801F0B90 + ((gLegions[D_8021B5B4_ovl_188B60][8] << 7) + 0x11C8), 16, 16, 2);
            func_80200DD0(x + 0x44, y + 2, 0x21);
            func_80200F70(D_801F36C0 + 0x1A0, D_801F0B90 + 0x1648, 16, 4, 2);
            func_801D66D0(slots, gLegions[D_8021B5B4_ovl_188B60], gLegions[D_8021B5B4_ovl_188B60][8]);
            for (i = 0; i < 5; i++) {
                if (slots[i] == sq) {
                    break;
                }
            }
            p = D_80210217[gLegions[D_8021B5B4_ovl_188B60][8]][i];
            col = (p >> 4) * 3 + 0x44;
            row = (p & 0xF) + 2;
            func_80200DD0(x + col, y + row, 0x36);
        } else {
            func_8020078C(gSquads[sq].legion - 1, x + 0x58, y + 4);
        }
        func_80179034(func_8016B070(gSquads[sq].strategy), x + 0x1C, y + 0x20);
        func_80179034(D_80193BC0[gSquads[sq].members[0]], x + 0x1C, y + 0x10);
    } else {
        gDPSetTextureLUT(D_800E9BA0++, G_TT_RGBA16);
        gSPSetOtherMode(D_800E9BA0++, G_SETOTHERMODE_H, 12, 2, 0x2000); /* bilinear filtering */
        gSPTexture(D_800E9BA0++, 0x8000, 0x8000, 0, 0, G_ON);
        gDPSetPrimColor(D_800E9BA0++, 0, 0, 0xFF, 0xFF, 0xFF, w->fade[page] > 0x50 ? 0x50 : w->fade[page]);
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
        func_802012D8(D_801F36C0 + 0x2C0);
        gDPPipeSync(D_800E9BA0++);
        gDPLoadTextureBlock_4b(D_800E9BA0++, D_801F0B90 + 0x20E8, G_IM_FMT_CI, 96, 36, 0, 1, 1, 0, 0, 0, 0);
        gDPPipeSync(D_800E9BA0++);
        gSPScisTextureRectangle(D_800E9BA0++, x << 2, y << 2, (x + 0x90) << 2, (y + 0x36) << 2, 0, 0, 0, 0x300, 0x300);
        gDPPipeSync(D_800E9BA0++);
        gDPPipeSync(D_800E9BA0++);
    }
    D_800E9BA0->w0 = 0xDE000000;
    D_800E9BA0->w1 = (u32)D_801EB1D0;
    D_800E9BA0++;
    if (w == D_8021B588_ovl_188B60[1] && D_8021B5A8_ovl_188B60 != -1 && D_8021B59E_ovl_188B60 != 0) {
        if (D_8021B5E6_ovl_188B60 == D_8021B5EC_ovl_188B60) {
            func_80201384(w->rect[0] - 0x20, w->rect[1], w->rect[2], w->rect[3]);
            func_80200DD0(x - 0x15, y + 0x10, 0x25);
        } else if (D_8021B5AC_ovl_188B60 == 0xFF) {
            func_80201384(w->rect[0] - 0x20, w->rect[1], w->rect[2], w->rect[3]);
            func_80200DD0(x - 0x15, y + 0x10, 0x24);
        } else {
            func_80201384(w->rect[0] - 0x20, w->rect[1], w->rect[2], w->rect[3]);
            func_80200DD0(x - 0x15, y + 0x19, 0x24);
            func_80200DD0(x - 0x15, y + 7, 0x25);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/18C2E0", func_80219F84_ovl_188B60);

/* Draws the legion formation editor: the backdrop (56 strips of 240x2), the five squad slots
 * (selected/highlighted palettes), each squad leader's class sprite with a crown on the first,
 * and the bouncing cursor over the selected slot */
void func_80219584_ovl_188B60(Win18C *w, s32 page);
void func_80219584_ovl_188B60(Win18C *w, s32 page);
#ifdef NON_MATCHING
/* formation editor draw: length matches (614), 153 words differ in register allocation */
void func_8021A0A4_ovl_188B60(void)
{
  s32 i;
  s32 y;
  s32 off;
  u8 *pal;
  s32 sq;
  s32 x;
  u8 cls;
  u8 base;
  u8 frame;
  u8 sprite;
  u8 *sheet;
  u8 c;
  u8 t;
  s32 bob;
  s32 bx = 0x3A;
  s32 by = 0x72;
  SpriteSet18C *ss;
  if ((D_8021B59D_ovl_188B60 == 0) || (D_801ED5C0 == ((void *) 0)))
  {
    return;
  }
  {
    Gfx *_g = (Gfx *) (D_800E9BA0++);
    _g->w0 = (unsigned int) ((((unsigned int) 0xDE) & ((0x01 << 8) - 1)) << 24);
    _g->w1 = (unsigned int) D_80213648;
  }
  ;
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
  {
    Gfx *_g = (Gfx *) (D_800E9BA0++);
    _g->w0 = (((unsigned int) ((((unsigned int) 0xE3) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((32 - 19) - 1)) & ((0x01 << 8) - 1)) << 8))) | ((unsigned int) ((((unsigned int) (1 - 1)) & ((0x01 << 8) - 1)) << 0));
    _g->w1 = (unsigned int) 0;
  }
  ;
  {
    Gfx *_g = (Gfx *) (D_800E9BA0++);
    _g->w0 = (((unsigned int) ((((unsigned int) 0xFA) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 8) - 1)) << 8))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 8) - 1)) << 0));
    _g->w1 = ((((unsigned int) ((((unsigned int) 0xFF) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0xFF) & ((0x01 << 8) - 1)) << 16))) | ((unsigned int) ((((unsigned int) 0xFF) & ((0x01 << 8) - 1)) << 8))) | ((unsigned int) ((((unsigned int) D_8021B5B8_ovl_188B60) & ((0x01 << 8) - 1)) << 0));
  }
  ;
  {
    Gfx *_g = (Gfx *) (D_800E9BA0++);
    _g->w0 = (((unsigned int) ((((unsigned int) 0xE3) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((32 - 14) - 2)) & ((0x01 << 8) - 1)) << 8))) | ((unsigned int) ((((unsigned int) (2 - 1)) & ((0x01 << 8) - 1)) << 0));
    _g->w1 = (unsigned int) (2 << 14);
  }
  ;
  func_8020122C(D_8021B5BC_ovl_188B60);
  for (i = 0, y = 0x5E, off = 0x200; i < 56; i++, y += 2, off += 0x1E0)
  {
    {
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = ((((unsigned int) ((((unsigned int) 0xFD) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) (1 - 1)) & ((0x01 << 12) - 1)) << 0));
        _g->w1 = (unsigned int) (D_8021B5BC_ovl_188B60 + off);
      }
      ;
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = (((((unsigned int) ((((unsigned int) 0xF5) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 9) - 1)) << 9))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 9) - 1)) << 0));
        _g->w1 = ((((((((unsigned int) ((((unsigned int) 7) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 20))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 2) - 1)) << 18))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 14))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 10))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 2) - 1)) << 8))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 4))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 0));
      }
      ;
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = (unsigned int) ((((unsigned int) 0xE6) & ((0x01 << 8) - 1)) << 24);
        _g->w1 = 0;
      }
      ;
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = (((unsigned int) ((((unsigned int) 0xF3) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 0));
        _g->w1 = (((unsigned int) ((((unsigned int) 7) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((((((240 * 2) + 1) >> 1) - 1) < 2047) ? ((((240 * 2) + 1) >> 1) - 1) : (2047))) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((((1 << 11) + ((1 > ((240 * 1) / 8)) ? (1) : ((240 * 1) / 8))) - 1) / ((1 > ((240 * 1) / 8)) ? (1) : ((240 * 1) / 8)))) & ((0x01 << 12) - 1)) << 0));
      }
      ;
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = (unsigned int) ((((unsigned int) 0xE7) & ((0x01 << 8) - 1)) << 24);
        _g->w1 = 0;
      }
      ;
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = (((((unsigned int) ((((unsigned int) 0xF5) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 1) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) (((240 * 1) + 7) >> 3)) & ((0x01 << 9) - 1)) << 9))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 9) - 1)) << 0));
        _g->w1 = ((((((((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 20))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 2) - 1)) << 18))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 14))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 10))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 2) - 1)) << 8))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 4))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 0));
      }
      ;
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = (((unsigned int) ((((unsigned int) 0xF2) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 0));
        _g->w1 = (((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((240 - 1) << 2)) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((2 - 1) << 2)) & ((0x01 << 12) - 1)) << 0));
      }
    }
    ;
    func_80200DD0(0x28, y, 0x5D);
  }

  {
    Gfx *_g = (Gfx *) (D_800E9BA0++);
    _g->w0 = (unsigned int) ((((unsigned int) 0xE7) & ((0x01 << 8) - 1)) << 24);
    _g->w1 = 0;
  }
  ;
  {
    Gfx *_g = (Gfx *) (D_800E9BA0++);
    _g->w0 = (unsigned int) ((((unsigned int) 0xE7) & ((0x01 << 8) - 1)) << 24);
    _g->w1 = 0;
  }
  ;
  {
    {
      Gfx *_g = (Gfx *) (D_800E9BA0++);
      _g->w0 = ((((unsigned int) ((((unsigned int) 0xFD) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) (1 - 1)) & ((0x01 << 12) - 1)) << 0));
      _g->w1 = (unsigned int) D_801ED5C0->slots;
    }
    ;
    {
      Gfx *_g = (Gfx *) (D_800E9BA0++);
      _g->w0 = (((((unsigned int) ((((unsigned int) 0xF5) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 9) - 1)) << 9))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 9) - 1)) << 0));
      _g->w1 = ((((((((unsigned int) ((((unsigned int) 7) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 20))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 2) - 1)) << 18))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 14))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 10))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 2) - 1)) << 8))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 4))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 0));
    }
    ;
    {
      Gfx *_g = (Gfx *) (D_800E9BA0++);
      _g->w0 = (unsigned int) ((((unsigned int) 0xE6) & ((0x01 << 8) - 1)) << 24);
      _g->w1 = 0;
    }
    ;
    {
      Gfx *_g = (Gfx *) (D_800E9BA0++);
      _g->w0 = (((unsigned int) ((((unsigned int) 0xF3) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 0));
      _g->w1 = (((unsigned int) ((((unsigned int) 7) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((((((32 * 128) + 3) >> 2) - 1) < 2047) ? ((((32 * 128) + 3) >> 2) - 1) : (2047))) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((((1 << 11) + ((1 > (32 / 16)) ? (1) : (32 / 16))) - 1) / ((1 > (32 / 16)) ? (1) : (32 / 16)))) & ((0x01 << 12) - 1)) << 0));
    }
    ;
    {
      Gfx *_g = (Gfx *) (D_800E9BA0++);
      _g->w0 = (unsigned int) ((((unsigned int) 0xE7) & ((0x01 << 8) - 1)) << 24);
      _g->w1 = 0;
    }
    ;
    {
      Gfx *_g = (Gfx *) (D_800E9BA0++);
      _g->w0 = (((((unsigned int) ((((unsigned int) 0xF5) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) (((32 >> 1) + 7) >> 3)) & ((0x01 << 9) - 1)) << 9))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 9) - 1)) << 0));
      _g->w1 = ((((((((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 20))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 2) - 1)) << 18))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 14))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 10))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 2) - 1)) << 8))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 4))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 0));
    }
    ;
    {
      Gfx *_g = (Gfx *) (D_800E9BA0++);
      _g->w0 = (((unsigned int) ((((unsigned int) 0xF2) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 0));
      _g->w1 = (((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((32 - 1) << 2)) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((128 - 1) << 2)) & ((0x01 << 12) - 1)) << 0));
    }
  }
  ;
  for (i = 0; i < 5; i++)
  {
    if (i == D_8021B59E_ovl_188B60)
    {
      pal = D_80212768;
    }
    else
    {
      pal = D_801F39B0;
      if (i == D_8021B5A8_ovl_188B60)
      {
        pal += 0x60;
      }
    }
    func_802012D8(pal);
    func_80200DD0((bx + D_8021B4B8_ovl_188B60[i].x) + 1, (by + D_8021B4B8_ovl_188B60[i].y) + 1, 0x5C);
  }

  ss = D_801ED5C0;
  for (i = 0; i < 5; i++)
  {
    sq = gLegions[D_8021B5B4_ovl_188B60][2 + i];
    if (sq == 0xFF)
    {
      continue;
    }
    x = (bx + D_8021B4B8_ovl_188B60[i].x) + 8;
    y = (by + D_8021B4B8_ovl_188B60[i].y) + 0xE;
    cls = D_80193BC0[gSquads[sq].members[0]][0x11];
    base = D_80193BC0[gSquads[sq].members[0]][0x12];
    t = func_8016DF18(cls, base);
    c = cls;
    if (gClassTable[cls].baseClass != base)
    {
      c = base;
    }
    frame = t;
    if (D_8018ECE4[c][0] & 0x80)
    {
      sheet = ss->sheetB;
    }
    else
    {
      sheet = ss->sheetA;
    }
    {
      Gfx *_g = (Gfx *) (D_800E9BA0++);
      _g->w0 = (unsigned int) ((((unsigned int) 0xE7) & ((0x01 << 8) - 1)) << 24);
      _g->w1 = 0;
    }
    ;
    func_8020122C(sheet + 0x200);
    {
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = ((((unsigned int) ((((unsigned int) 0xFD) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) (1 - 1)) & ((0x01 << 12) - 1)) << 0));
        _g->w1 = (unsigned int) (sheet + ((frame * 0x180) + 0x400));
      }
      ;
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = (((((unsigned int) ((((unsigned int) 0xF5) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 9) - 1)) << 9))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 9) - 1)) << 0));
        _g->w1 = ((((((((unsigned int) ((((unsigned int) 7) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 20))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 18))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 14))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 10))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 8))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 4))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 0));
      }
      ;
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = (unsigned int) ((((unsigned int) 0xE6) & ((0x01 << 8) - 1)) << 24);
        _g->w1 = 0;
      }
      ;
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = (((unsigned int) ((((unsigned int) 0xF3) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 0));
        _g->w1 = (((unsigned int) ((((unsigned int) 7) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((((((16 * 24) + 1) >> 1) - 1) < 2047) ? ((((16 * 24) + 1) >> 1) - 1) : (2047))) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((((1 << 11) + ((1 > ((16 * 1) / 8)) ? (1) : ((16 * 1) / 8))) - 1) / ((1 > ((16 * 1) / 8)) ? (1) : ((16 * 1) / 8)))) & ((0x01 << 12) - 1)) << 0));
      }
      ;
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = (unsigned int) ((((unsigned int) 0xE7) & ((0x01 << 8) - 1)) << 24);
        _g->w1 = 0;
      }
      ;
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = (((((unsigned int) ((((unsigned int) 0xF5) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 1) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) (((16 * 1) + 7) >> 3)) & ((0x01 << 9) - 1)) << 9))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 9) - 1)) << 0));
        _g->w1 = ((((((((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 20))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 18))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 14))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 10))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 8))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 4))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 0));
      }
      ;
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = (((unsigned int) ((((unsigned int) 0xF2) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 0));
        _g->w1 = (((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((16 - 1) << 2)) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((24 - 1) << 2)) & ((0x01 << 12) - 1)) << 0));
      }
    }
    ;
    func_80200DD0(x, y - 0x18, 0x5E);
    if (i == 0)
    {
      D_8018F480 = 1;
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = (unsigned int) ((((unsigned int) 0xE7) & ((0x01 << 8) - 1)) << 24);
        _g->w1 = 0;
      }
      ;
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = (((unsigned int) ((((unsigned int) 0xE3) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((32 - 14) - 2)) & ((0x01 << 8) - 1)) << 8))) | ((unsigned int) ((((unsigned int) (2 - 1)) & ((0x01 << 8) - 1)) << 0));
        _g->w1 = (unsigned int) (0 << 14);
      }
      ;
      {
        {
          Gfx *_g = (Gfx *) (D_800E9BA0++);
          _g->w0 = ((((unsigned int) ((((unsigned int) 0xFD) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) (1 - 1)) & ((0x01 << 12) - 1)) << 0));
          _g->w1 = (unsigned int) D_801F0BCC;
        }
        ;
        {
          Gfx *_g = (Gfx *) (D_800E9BA0++);
          _g->w0 = (((((unsigned int) ((((unsigned int) 0xF5) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 9) - 1)) << 9))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 9) - 1)) << 0));
          _g->w1 = ((((((((unsigned int) ((((unsigned int) 7) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 20))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 18))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 14))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 10))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 8))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 4))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 0));
        }
        ;
        {
          Gfx *_g = (Gfx *) (D_800E9BA0++);
          _g->w0 = (unsigned int) ((((unsigned int) 0xE6) & ((0x01 << 8) - 1)) << 24);
          _g->w1 = 0;
        }
        ;
        {
          Gfx *_g = (Gfx *) (D_800E9BA0++);
          _g->w0 = (((unsigned int) ((((unsigned int) 0xF3) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 0));
          _g->w1 = (((unsigned int) ((((unsigned int) 7) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((((((24 * 9) + 0) >> 0) - 1) < 2047) ? ((((24 * 9) + 0) >> 0) - 1) : (2047))) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((((1 << 11) + ((1 > ((24 * 2) / 8)) ? (1) : ((24 * 2) / 8))) - 1) / ((1 > ((24 * 2) / 8)) ? (1) : ((24 * 2) / 8)))) & ((0x01 << 12) - 1)) << 0));
        }
        ;
        {
          Gfx *_g = (Gfx *) (D_800E9BA0++);
          _g->w0 = (unsigned int) ((((unsigned int) 0xE7) & ((0x01 << 8) - 1)) << 24);
          _g->w1 = 0;
        }
        ;
        {
          Gfx *_g = (Gfx *) (D_800E9BA0++);
          _g->w0 = (((((unsigned int) ((((unsigned int) 0xF5) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 21))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 19))) | ((unsigned int) ((((unsigned int) (((24 * 2) + 7) >> 3)) & ((0x01 << 9) - 1)) << 9))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 9) - 1)) << 0));
          _g->w1 = ((((((((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 20))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 18))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 14))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 10))) | ((unsigned int) ((((unsigned int) 2) & ((0x01 << 2) - 1)) << 8))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 4))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 4) - 1)) << 0));
        }
        ;
        {
          Gfx *_g = (Gfx *) (D_800E9BA0++);
          _g->w0 = (((unsigned int) ((((unsigned int) 0xF2) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 12) - 1)) << 0));
          _g->w1 = (((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((24 - 1) << 2)) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((9 - 1) << 2)) & ((0x01 << 12) - 1)) << 0));
        }
      }
      ;
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = (unsigned int) ((((unsigned int) 0xE7) & ((0x01 << 8) - 1)) << 24);
        _g->w1 = 0;
      }
      ;
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = (((unsigned int) ((((unsigned int) 0xE4) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((x + 22) << 2)) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((y - 13) << 2)) & ((0x01 << 12) - 1)) << 0));
        _g->w1 = (((unsigned int) ((((unsigned int) 0) & ((0x01 << 3) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((x + 12) << 2)) & ((0x01 << 12) - 1)) << 12))) | ((unsigned int) ((((unsigned int) ((y - 22) << 2)) & ((0x01 << 12) - 1)) << 0));
        {
          Gfx *_g = (Gfx *) (D_800E9BA0++);
          _g->w0 = (unsigned int) ((((unsigned int) 0xE1) & ((0x01 << 8) - 1)) << 24);
          _g->w1 = (unsigned int) (((unsigned int) ((((unsigned int) (8 << 5)) & ((0x01 << 16) - 1)) << 16)) | ((unsigned int) ((((unsigned int) 0) & ((0x01 << 16) - 1)) << 0)));
        }
        ;
        {
          Gfx *_g = (Gfx *) (D_800E9BA0++);
          _g->w0 = (unsigned int) ((((unsigned int) 0xF1) & ((0x01 << 8) - 1)) << 24);
          _g->w1 = (unsigned int) (((unsigned int) ((((unsigned int) (1 << 10)) & ((0x01 << 16) - 1)) << 16)) | ((unsigned int) ((((unsigned int) (1 << 10)) & ((0x01 << 16) - 1)) << 0)));
        }
        ;
      }
      ;
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = (unsigned int) ((((unsigned int) 0xE7) & ((0x01 << 8) - 1)) << 24);
        _g->w1 = 0;
      }
      ;
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = (unsigned int) ((((unsigned int) 0xE7) & ((0x01 << 8) - 1)) << 24);
        _g->w1 = 0;
      }
      ;
      D_8018F480 = 2;
      {
        Gfx *_g = (Gfx *) (D_800E9BA0++);
        _g->w0 = (((unsigned int) ((((unsigned int) 0xE3) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((32 - 14) - 2)) & ((0x01 << 8) - 1)) << 8))) | ((unsigned int) ((((unsigned int) (2 - 1)) & ((0x01 << 8) - 1)) << 0));
        _g->w1 = (unsigned int) (2 << 14);
      }
      ;
    }
  }

  {
    Gfx *_g = (Gfx *) (D_800E9BA0++);
    _g->w0 = (unsigned int) ((((unsigned int) 0xDE) & ((0x01 << 8) - 1)) << 24);
    _g->w1 = (unsigned int) D_80213648;
  }
  ;
  {
    Gfx *_g = (Gfx *) (D_800E9BA0++);
    _g->w0 = (((unsigned int) ((((unsigned int) 0xE3) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((32 - 19) - 1)) & ((0x01 << 8) - 1)) << 8))) | ((unsigned int) ((((unsigned int) (1 - 1)) & ((0x01 << 8) - 1)) << 0));
    _g->w1 = (unsigned int) 0;
  }
  ;
  bob = D_8021B5C0_ovl_188B60 & 0xF;
  x = (bx + D_8021B4B8_ovl_188B60[D_8021B59E_ovl_188B60].x) + 0xB;
  y = (by + D_8021B4B8_ovl_188B60[D_8021B59E_ovl_188B60].y) - 0x1E;
  func_80200F70(D_80212518, D_80212410, 16, 32, 2);
  func_80200DD0(x, y + bob, 0x3F);
  {
    Gfx *_g = (Gfx *) (D_800E9BA0++);
    _g->w0 = (unsigned int) ((((unsigned int) 0xE7) & ((0x01 << 8) - 1)) << 24);
    _g->w1 = 0;
  }
  ;
  if (D_8021B5A8_ovl_188B60 == (-1))
  {
    if (D_8021B5C0_ovl_188B60 & 0x80)
    {
      D_8021B5C0_ovl_188B60--;
      if (!(D_8021B5C0_ovl_188B60 & 0xF))
      {
        D_8021B5C0_ovl_188B60 &= 0x7F;
      }
    }
    else
    {
      D_8021B5C0_ovl_188B60++;
      if ((D_8021B5C0_ovl_188B60 & 0xF) >= 5)
      {
        D_8021B5C0_ovl_188B60 |= 0x80;
      }
    }
  }
}
#else
INCLUDE_ASM("asm/nonmatchings/18C2E0", func_8021A0A4_ovl_188B60);
#endif

INCLUDE_ASM("asm/nonmatchings/18C2E0", func_8021AA3C_ovl_188B60);

INCLUDE_ASM("asm/nonmatchings/18C2E0", func_8021AFD8_ovl_188B60);
