#include "common.h"

/* Debug text renderer: 8x8 glyphs drawn as texture rectangles into a display list */

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))

#define gDPPipeSync(pkt)                 \
    {                                    \
        Gfx *_g = (Gfx *)(pkt);          \
        _g->w0 = 0xE7000000;             \
        _g->w1 = 0;                      \
    }

#define gSPDisplayList(pkt, dl)          \
    {                                    \
        Gfx *_g = (Gfx *)(pkt);          \
        _g->w0 = 0xDE000000;             \
        _g->w1 = (u32)(dl);              \
    }

#define gImmp1(pkt, c, p0)               \
    {                                    \
        Gfx *_g = (Gfx *)(pkt);          \
        _g->w0 = _SHIFTL(c, 24, 8);      \
        _g->w1 = (u32)(p0);              \
    }

#define gSPTextureRectangle(pkt, xl, yl, xh, yh, tile, s, t, dsdx, dtdy)                       \
    {                                                                                          \
        Gfx *_g = (Gfx *)(pkt);                                                                \
        _g->w0 = (_SHIFTL(0xE4, 24, 8) | _SHIFTL(xh, 12, 12) | _SHIFTL(yh, 0, 12));            \
        _g->w1 = (_SHIFTL(tile, 24, 3) | _SHIFTL(xl, 12, 12) | _SHIFTL(yl, 0, 12));            \
        gImmp1(pkt, 0xE1, (_SHIFTL(s, 16, 16) | _SHIFTL(t, 0, 16)));                           \
        gImmp1(pkt, 0xF1, (_SHIFTL(dsdx, 16, 16) | _SHIFTL(dtdy, 0, 16)));                     \
    }

extern Gfx **D_800B17B0; /* display list cursor */
extern s16 D_800B17B4;   /* origin x */
extern s16 D_800B17B6;   /* origin y */
extern s16 D_800B17B8;   /* line start x */
extern s16 D_800B17BA;   /* cursor x */
extern s16 D_800B17BC;   /* cursor y */
extern u16 D_800B17BE;   /* palette loaded in TMEM */
extern u16 D_800B17C0;   /* current palette */
extern u8 D_800B17C2;    /* font half (glyph bit 6) currently loaded */
extern u8 D_800A96C0;    /* raw mode: no control characters */
extern Gfx D_800A96C8[]; /* setup display list */
extern Gfx D_800A9790[]; /* restore display list */
extern Gfx D_800A97C8[]; /* load font half 0 */
extern Gfx D_800A9810[]; /* load font half 1 */
extern u8 D_800A9858[];  /* extra glyph characters */

s32 func_800807DC(u8 c);
s32 func_80080894(char **pstr);

void func_80080280(Gfx **gdl) {
    D_800B17B0 = gdl;
}

void func_8008028C(void) {
    D_800B17B4 = D_800B17B6 = D_800B17B8 = D_800B17BA = D_800B17BC = D_800B17BE = D_800B17C0 = 0;
    D_800B17C2 = 0xFF;
    D_800A96C0 = 0;
    gSPDisplayList((*D_800B17B0)++, D_800A96C8);
}

void func_80080304(s16 x, s16 y) {
    D_800B17B4 = D_800B17B6 = D_800B17B8 = D_800B17BA = D_800B17BC = D_800B17BE = D_800B17C0 = 0;
    D_800B17C2 = 0xFF;
    D_800A96C0 = 0;
    gSPDisplayList((*D_800B17B0)++, D_800A96C8);
    D_800B17B4 = x;
    D_800B17B6 = y;
}

void func_8008038C(void) {
    gSPDisplayList((*D_800B17B0)++, D_800A9790);
}

void func_800803B8(char *str) {
    u8 c;
    u32 glyph;

    gDPPipeSync((*D_800B17B0)++);
    while ((c = *str++) != 0) {
        if (D_800A96C0 == 0) {
            if (c == '\t') {
                D_800B17BA = (((D_800B17BA / 8) + 4) / 4) * 32;
                continue;
            } else if (c == '\n') {
                D_800B17BA = D_800B17B8;
                D_800B17BC += 9;
                continue;
            } else if (c == '{') {
                c = *str++;
                switch (c) {
                    case 'C':
                    case 'c':
                        D_800B17C0 = func_80080894(&str);
                        break;
                }
                continue;
            }
        }
        if (c != ' ') {
            glyph = func_800807DC(c);
            if (((glyph >> 6) & 1) != D_800B17C2) {
                if ((D_800B17C2 = (glyph >> 6) & 1)) {
                    gSPDisplayList((*D_800B17B0)++, D_800A9810);
                } else {
                    gSPDisplayList((*D_800B17B0)++, D_800A97C8);
                }
                D_800B17BE = ~D_800B17C0;
            }
            glyph &= 0x3F;
            if (D_800B17BE != D_800B17C0) {
                D_800B17BE = D_800B17C0;
                gDPPipeSync((*D_800B17B0)++);
                {
                    Gfx *_g = (*D_800B17B0)++;
                    _g->w0 = 0xF5400800;
                    _g->w1 = (D_800B17C0 & 0xF) << 20;
                }
                gDPPipeSync((*D_800B17B0)++);
            }
            gDPPipeSync((*D_800B17B0)++);
            gSPTextureRectangle((*D_800B17B0)++, (D_800B17B4 + D_800B17BA) << 2, (D_800B17B6 + D_800B17BC) << 2,
                                (D_800B17B4 + D_800B17BA + 8) << 2, (D_800B17B6 + D_800B17BC + 8) << 2, 0,
                                ((u16)glyph % 8) << 8, ((u16)glyph / 8) << 8, 1 << 10, 1 << 10);
            gDPPipeSync((*D_800B17B0)++);
            gDPPipeSync((*D_800B17B0)++);
        }
        D_800B17BA += 8;
    }
}

void func_80080768(char *str, s16 x, s16 y) {
    D_800B17B8 = x;
    D_800B17BA = x;
    D_800B17BC = y;
    func_800803B8(str);
}

/* Same, without control-character handling */
void func_80080798(char *str, s16 x, s16 y) {
    D_800B17B8 = x;
    D_800B17BA = x;
    D_800B17BC = y;
    D_800A96C0 = 1;
    func_800803B8(str);
    D_800A96C0 = 0;
}

/* Character to glyph index */
s32 func_800807DC(u8 c) {
    s32 i;

    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;
    }
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 36;
    }
    for (i = 0; D_800A9858[i] != 0; i++) {
        if (c == D_800A9858[i]) {
            return i + 0x3E;
        }
    }
    if (c == 0xFF) {
        return 0x5F;
    }
    return i + 0x3D;
}

/* Parses a decimal number, advancing the string past the first non-digit */
s32 func_80080894(char **pstr) {
    s32 n = 0;
    u8 c;

    while ((c = **pstr) != 0) {
        (*pstr)++;
        if (!(c >= '0' && c <= '9')) {
            break;
        }
        n = (c - '0') + n * 10;
    }
    return n;
}
