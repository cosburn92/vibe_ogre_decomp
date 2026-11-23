#include "common.h"

/* 134830 */

extern s32 D_801ED4A4_ovl_101CE0[];
/* --- end decls --- */

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
typedef struct {
    /* 0x00 */ s32 id;
    /* 0x04 */ u8 unk04[8];
    /* 0x0C */ s32 x2;
    /* 0x10 */ s32 y2;
    /* 0x14 */ s32 w2;
    /* 0x18 */ s32 h2;
    /* 0x1C */ s32 x;
    /* 0x20 */ s32 y;
    /* 0x24 */ s32 w;
    /* 0x28 */ s32 h;
    /* 0x2C */ u8 *win;
    /* 0x30 */ u8 unk30[8];
    /* 0x38 */ s32 a;
    /* 0x3C */ s32 b;
    /* 0x40 */ s32 c;
    /* 0x44 */ u8 unk44[0x1D];
    /* 0x61 */ s8 d;
} Dialog134;
extern Dialog134 D_801ED540_ovl_101CE0;
extern s32 D_801F0B40_ovl_101CE0;
extern u16 *D_801F0CA0_ovl_101CE0;
extern u16 *D_800C4BDC;
void func_801E09DC_ovl_101CE0(Dialog134 *d);
void func_801E0594_ovl_101CE0();
u8 *func_8017BFB0(s32 kind, s32 b, void (*fn)(), s16 x, s16 y, s16 w, s16 h, s16 x2, s16 y2, s16 w2, s16 h2);
void func_8017C384(u8 *w);
void func_8020CDA0(s32 se);

/* Yes/no dialog step: opens dialog id on the first call; once the window is up, returns 1 for
 * the confirm button and 3 for the cancel button (closing it), 2 while waiting */
s32 func_801E00F0_ovl_101CE0(s32 id, s32 a, s32 b, s32 c, s32 d, s32 x2) {
    if (D_801ED540_ovl_101CE0.id == -1) {
        D_801ED540_ovl_101CE0.d = d;
        D_801ED540_ovl_101CE0.id = id;
        D_801ED540_ovl_101CE0.a = a;
        D_801ED540_ovl_101CE0.b = b;
        D_801ED540_ovl_101CE0.c = c;
        D_801F0B40_ovl_101CE0 = 0;
        D_801ED540_ovl_101CE0.x2 = x2;
        func_801E09DC_ovl_101CE0(&D_801ED540_ovl_101CE0);
        D_801ED540_ovl_101CE0.win = func_8017BFB0(4, 0, func_801E0594_ovl_101CE0, D_801ED540_ovl_101CE0.x,
                                                  D_801ED540_ovl_101CE0.y, D_801ED540_ovl_101CE0.w,
                                                  D_801ED540_ovl_101CE0.h, D_801ED540_ovl_101CE0.x2,
                                                  D_801ED540_ovl_101CE0.y2, D_801ED540_ovl_101CE0.w2,
                                                  D_801ED540_ovl_101CE0.h2);
        return 2;
    }
    if (FIELD(D_801ED540_ovl_101CE0.win, u16, 0x26) == 0) {
        if ((*D_800C4BDC & D_801F0CA0_ovl_101CE0[0]) || (*D_800C4BDC & D_801F0CA0_ovl_101CE0[1])) {
            func_8020CDA0(6);
            func_8017C384(D_801ED540_ovl_101CE0.win);
            D_801ED540_ovl_101CE0.id = -1;
            return (*D_800C4BDC & D_801F0CA0_ovl_101CE0[0]) ? 1 : 3;
        }
    }
    return 2;
}

INCLUDE_ASM("asm/nonmatchings/134830", func_801E027C_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/134830", func_801E0594_ovl_101CE0);

#include "libultra.h"
#include "gbi_ultra.h"
void _bcopy(void *src, void *dst, s32 n);
void bzero(void *p, s32 n);
void func_80179034(char *s, s32 x, s32 y);
void func_8017C4B4(s16 a);
void func_801818A0(s32 x, s32 y);
extern Gfx *D_800E9BA0;
extern char *D_801ED584_ovl_101CE0;
extern char *D_801ED588_ovl_101CE0;
extern s32 D_801ED598_ovl_101CE0;
extern s32 D_801ED59C_ovl_101CE0;
extern u8 D_801ED5A0_ovl_101CE0;
extern u8 D_801ED5A4_ovl_101CE0;

/* Draws window o's page i: its two text lines and the blinking cursor (column in the low nibble
 * of D_801ED5A4, row D_801ED5A0), then steps the cursor blink */
#ifdef NON_MATCHING
/* 93/93, 5 words: the page id is reloaded before the display-list pointer store in the original, after it here */
void func_801E0868_ovl_101CE0(u8 *o, s32 i) {
    u8 *p = o + i * 2;

    if (FIELD(p, s16, 0x18) != 0) {
        s32 x = FIELD(o, s32, 0x2C);
        s32 y = FIELD(o, s32, 0x30);
        s32 tx, ty;
        char buf[0x100];

        D_800E9BA0->w0 = 0xE7000000;
        D_800E9BA0->w1 = 0;
        D_800E9BA0++;
        ty = y + 1;
        func_8017C4B4(FIELD(p, s16, 0x18));
        bzero(buf, 0x100);
        _bcopy(D_801ED584_ovl_101CE0, buf, D_801ED598_ovl_101CE0);
        tx = x + 0x17;
        func_80179034(buf, tx, ty);
        bzero(buf, 0x100);
        ty = y + 0x10;
        _bcopy(D_801ED588_ovl_101CE0, buf, D_801ED59C_ovl_101CE0);
        func_80179034(buf, tx, ty);
        func_801818A0(x + (D_801ED5A4_ovl_101CE0 & 0xF) - 1, ty + (D_801ED5A0_ovl_101CE0 - 1) * 15 + 2);
        if (D_801ED5A4_ovl_101CE0 & 0xF0) {
            D_801ED5A4_ovl_101CE0++;
            if ((D_801ED5A4_ovl_101CE0 & 0xF) >= 5) {
                D_801ED5A4_ovl_101CE0 &= 0xF;
            }
        } else {
            D_801ED5A4_ovl_101CE0--;
            if (!(D_801ED5A4_ovl_101CE0 & 0xF)) {
                D_801ED5A4_ovl_101CE0 |= 0xF0;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/134830", func_801E0868_ovl_101CE0);
#endif

INCLUDE_ASM("asm/nonmatchings/134830", func_801E09DC_ovl_101CE0);

u8 func_801793E4(u8 c, s32 a);

/* Length of string s in cells (control byte 0x0B takes two) while adding the glyph widths to *w */
static inline s32 TextLen134(u8 *s, s32 *w) {
    s32 n = 0;

    while (*s != 0) {
        s32 c = func_801793E4(*s, 0);

        if (c == 0xB) {
            s++;
            n += 2;
        } else {
            n++;
        }
        s++;
        *w += c;
    }
    return n;
}

/* Lays out the two-line prompt of window o: line lengths, and the button and text rects in r */
#ifdef NON_MATCHING
/* 93/93 instructions, 10 words differ: the original keeps right - 22 - w - 16 as three steps and stores the second length after loading both widths */
void func_801E0DBC_ovl_101CE0(u8 *o, s32 *r) {
    s32 w0;
    s32 w1;
    s32 w;
    s32 x;
    s32 y;
    s32 m;

    FIELD(o, s32, 0x58) = TextLen134(FIELD(o, u8 *, 0x44), &w0);
    FIELD(o, s32, 0x5C) = TextLen134(FIELD(o, u8 *, 0x48), &w1);
    {
        s32 right = FIELD(o, s32, 0x14);

        w = w0 < w1 ? w1 : w0;
        x = right - 0x16 - w - 0x10;
        y = FIELD(o, s32, 0x18);
        m = (x + right) / 2;
        *r++ = m - 2;
        *r++ = y + 1;
        *r++ = m + 2;
        *r++ = y + 3;
        *r++ = x;
        *r++ = y + 1;
        *r++ = right;
        *r = y + 0x25;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/134830", func_801E0DBC_ovl_101CE0);
#endif

s32 func_801E0F30_ovl_101CE0(s32 a) {
    s32 *p = D_801ED4A4_ovl_101CE0;
    s32 i = 0;

    while (*p != a) {
        p += 3;
        i += 3;
    }
    return i;
}
