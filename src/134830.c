#include "common.h"

/* 134830 */

extern s32 D_801ED4A4_ovl_101CE0[];
extern char *D_801ED494_ovl_101CE0[];
extern u8 D_8019EE40[];
extern u16 *D_800C4C4C;
/* --- end decls --- */

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
typedef struct {
    /* 0x00 */ s32 id;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 lines;
    /* 0x0C */ s32 x2;
    /* 0x10 */ s32 y2;
    /* 0x14 */ s32 w2;
    /* 0x18 */ s32 h2;
    /* 0x1C */ s32 x;
    /* 0x20 */ s32 y;
    /* 0x24 */ s32 w;
    /* 0x28 */ s32 h;
    /* 0x2C */ u8 *win;
    /* 0x30 */ u8 *win2;
    /* 0x34 */ u8 *text;
    /* 0x38 */ s32 a;
    /* 0x3C */ s32 b;
    /* 0x40 */ s32 c;
    /* 0x44 */ char *opt0;
    /* 0x48 */ char *opt1;
    /* 0x4C */ s32 lenA;
    /* 0x50 */ s32 lenB;
    /* 0x54 */ s32 lenC;
    /* 0x58 */ s32 len0;
    /* 0x5C */ s32 len1;
    /* 0x60 */ u8 sel;
    /* 0x61 */ u8 d;
} Dialog134;
extern Dialog134 D_801ED540_ovl_101CE0;
extern s32 D_801F0B40_ovl_101CE0;
extern u16 *D_801F0CA0_ovl_101CE0;
extern u16 *D_800C4BDC;
void func_801E09DC_ovl_101CE0(Dialog134 *d);
void func_801E0594_ovl_101CE0(u8 *o, s32 i);
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

s32 func_801E0F30_ovl_101CE0(s32 a);
void func_801E0DBC_ovl_101CE0(Dialog134 *d, s32 *r);
void func_801E0868_ovl_101CE0(u8 *o, s32 i);

/* Two-choice dialog step: opens dialog id (message window plus a choice window whose two
 * labels come from the id's table entry) on the first call; then left/right (0x800/0x400)
 * moves the choice, confirm returns 1 (D_8019EE40 = the choice), cancel returns 3, else 2 */
s32 func_801E027C_ovl_101CE0(s32 id, s32 a, s32 b, s32 c, s32 sel, s32 d, s32 x2) {
    s32 r[8];

    if (D_801ED540_ovl_101CE0.id == -1) {
        s32 k;

        D_801ED540_ovl_101CE0.d = d;
        D_801ED540_ovl_101CE0.id = id;
        D_801ED540_ovl_101CE0.a = a;
        D_801ED540_ovl_101CE0.b = b;
        D_801ED540_ovl_101CE0.c = c;
        k = func_801E0F30_ovl_101CE0(id);
        D_801ED540_ovl_101CE0.opt0 = D_801ED494_ovl_101CE0[D_801ED4A4_ovl_101CE0[k + 1]];
        D_801ED540_ovl_101CE0.opt1 = D_801ED494_ovl_101CE0[D_801ED4A4_ovl_101CE0[k + 2]];
        D_801F0B40_ovl_101CE0 = 0;
        D_801ED540_ovl_101CE0.sel = sel != 0;
        D_801ED540_ovl_101CE0.x2 = x2;
        func_801E09DC_ovl_101CE0(&D_801ED540_ovl_101CE0);
        func_801E0DBC_ovl_101CE0(&D_801ED540_ovl_101CE0, r);
        D_801ED540_ovl_101CE0.win = func_8017BFB0(4, 0, func_801E0594_ovl_101CE0, D_801ED540_ovl_101CE0.x,
                                                  D_801ED540_ovl_101CE0.y, D_801ED540_ovl_101CE0.w,
                                                  D_801ED540_ovl_101CE0.h, D_801ED540_ovl_101CE0.x2,
                                                  D_801ED540_ovl_101CE0.y2, D_801ED540_ovl_101CE0.w2,
                                                  D_801ED540_ovl_101CE0.h2);
        D_801ED540_ovl_101CE0.win2 = func_8017BFB0(4, 0, func_801E0868_ovl_101CE0, r[0], r[1], r[2], r[3], r[4],
                                                   r[5], r[6], r[7]);
        return 2;
    }
    if (FIELD(D_801ED540_ovl_101CE0.win, u16, 0x26) == 0 && FIELD(D_801ED540_ovl_101CE0.win2, u16, 0x26) == 0) {
        if ((*D_800C4BDC & D_801F0CA0_ovl_101CE0[0]) || (*D_800C4BDC & D_801F0CA0_ovl_101CE0[1])) {
            func_8017C384(D_801ED540_ovl_101CE0.win);
            func_8017C384(D_801ED540_ovl_101CE0.win2);
            D_801ED540_ovl_101CE0.id = -1;
            if (*D_800C4BDC & D_801F0CA0_ovl_101CE0[0]) {
                s32 se;

                if (D_801ED540_ovl_101CE0.sel == 0) {
                    D_8019EE40[0] = 0;
                    se = 6;
                } else {
                    D_8019EE40[0] = 1;
                    se = 1;
                }
                func_8020CDA0(se);
                return 1;
            }
            func_8020CDA0(1);
            return 3;
        } else {
            u16 pad = *D_800C4C4C;

            if (pad & 0x800) {
                if (D_801ED540_ovl_101CE0.sel != 0) {
                    D_801ED540_ovl_101CE0.sel = 0;
                    func_8020CDA0(2);
                }
            } else if (pad & 0x400) {
                if (D_801ED540_ovl_101CE0.sel != 1) {
                    D_801ED540_ovl_101CE0.sel = 1;
                    func_8020CDA0(2);
                }
            }
        }
    }
    return 2;
}

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
s32 func_8017B550(u8 c);
void func_80201384(s32 a, s32 b, s32 c, s32 d);
void func_8020D780(s32 x, s32 y);
void func_8020DAA8(s32 x, s32 y);
typedef struct { u8 pad[0x18]; s16 page; } Page134;

/* Draws dialog window o's message: D_801ED540.lines lines of its text, where the SJIS codes
 * 0x8194, 0x8190 and 0x8193 are replaced by strings a, b and c and 0x8197 ends a line; then,
 * if the dialog has a choice marker (d = 1 or 2), its frame and marker */
void func_801E0594_ovl_101CE0(u8 *o, s32 i) {
    Dialog134 *s = &D_801ED540_ovl_101CE0;
    Page134 *p = (Page134 *)(i * 2 + (s32)o);

    if (p->page != 0) {
        s32 x = FIELD(o, s32, 0x2C);
        s32 y = FIELD(o, s32, 0x30);
        s32 line;
        s32 n;
        s32 ty;
        u8 *t;
        u8 *start;
        char *dst;
        char buf[0x100];

        D_800E9BA0->w0 = 0xE7000000;
        D_800E9BA0->w1 = 0;
        D_800E9BA0++;
        line = 0;
        func_8017C4B4(p->page);
        t = s->text;
        ty = y + 4;
        for (start = t; line < s->lines; line++) {
            bzero(buf, 0x100);
            dst = buf;
            n = 0;
            while (1) {
                if (func_8017B550(*t)) {
                    s32 c = t[1] | (t[0] << 8);

                    if (c == 0x8197) {
                        _bcopy(start, dst, n);
                        t += 2;
                        break;
                    }
                    if (c == 0x8194) {
                        _bcopy(start, dst, n);
                        start += n + 2;
                        dst += n;
                        _bcopy((void *)s->a, dst, s->lenA);
                        dst += s->lenA;
                        n = 0;
                        t++;
                    } else if (c == 0x8190) {
                        _bcopy(start, dst, n);
                        start += n + 2;
                        dst += n;
                        _bcopy((void *)s->b, dst, s->lenB);
                        dst += s->lenB;
                        n = 0;
                        t++;
                    } else if (c == 0x8193) {
                        _bcopy(start, dst, n);
                        start += n + 2;
                        dst += n;
                        _bcopy((void *)s->c, dst, s->lenC);
                        dst += s->lenC;
                        n = 0;
                        t++;
                    } else {
                        n += 2;
                        t++;
                    }
                } else if (*t == 0) {
                    _bcopy(start, dst, n);
                    break;
                } else {
                    n++;
                }
                t++;
            }
            func_80179034(buf, s->x2 + 4, ty);
            ty += 15;
            start = t;
        }
        if (s->d != 0) {
            func_80201384(FIELD(o, s32, 0x7C), FIELD(o, s32, 0x80) - 12, FIELD(o, s32, 0x84), FIELD(o, s32, 0x88));
            D_800E9BA0->w0 = 0xE3001001;
            D_800E9BA0->w1 = 0x8000;
            D_800E9BA0++;
            if (s->d == 1) {
                func_8020D780(x + 6, y - 10);
            } else if (s->d == 2) {
                func_8020DAA8(x + 6, y - 10);
            }
        }
    }
}

/* Draws window o's page i: its two text lines and the blinking cursor (column in the low nibble
 * of D_801ED5A4, row D_801ED5A0), then steps the cursor blink */
void func_801E0868_ovl_101CE0(u8 *o, s32 i) {
    Page134 *p = (Page134 *)(i * 2 + (s32)o);

    if (p->page != 0) {
        s32 x = FIELD(o, s32, 0x2C);
        s32 y = FIELD(o, s32, 0x30);
        s32 tx, ty;
        char buf[0x100];

        D_800E9BA0->w0 = 0xE7000000;
        D_800E9BA0->w1 = 0;
        D_800E9BA0++;
        ty = y + 1;
        func_8017C4B4(p->page);
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

extern u8 *D_801ED290_ovl_101CE0[];
/* one-field struct: retail keeps its load after the rect stores (struct-member aliasing) */
extern struct { s32 y; } D_801F0B48_ovl_101CE0;

/* Lays out dialog d: lengths and widths of the placeholder strings a/b/c, then the size of
 * message D_801ED290[id] (0x8197 breaks a line, 0x0E/0x0F switch the glyph set), and the
 * message and title rects centred on screen, or placed at D_801F0B48 when D_801F0B40 is set;
 * a top y other than -1 passed in x2 moves both rects there */
void func_801E09DC_ovl_101CE0(Dialog134 *d) {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 top;
    u8 *t;
    s32 alt;
    s32 max;
    s32 cur;
    s32 lines;
    s32 x;
    s32 y;
    s32 h;
    s32 right;
    s32 bottom;

    w2 = 0;
    w1 = 0;
    w0 = 0;
    top = d->x2;
    if (d->a != 0) {
        d->lenA = TextLen134((u8 *)d->a, &w0);
    }
    if (d->b != 0) {
        d->lenB = TextLen134((u8 *)d->b, &w1);
    }
    if (d->c != 0) {
        d->lenC = TextLen134((u8 *)d->c, &w2);
    }
    t = D_801ED290_ovl_101CE0[d->id];
    alt = 0;
    max = 0;
    cur = 0;
    lines = 1;
    while (*t != 0) {
        if (func_8017B550(*t)) {
            u16 c = t[1] | (t[0] << 8);

            if (c == 0x8197) {
                lines++;
                if (max < cur) {
                    max = cur;
                }
                cur = 0;
            } else if (c == 0x8194) {
                cur += w0;
            } else if (c == 0x8190) {
                cur += w1;
            } else if (c == 0x8193) {
                cur += w2;
            } else {
                cur += 0xB;
            }
            t++;
        } else if (*t == 0xE) {
            alt = 1;
        } else if (*t == 0xF) {
            alt = 0;
        } else {
            cur += func_801793E4(*t, alt);
        }
        t++;
    }
    if (max < cur) {
        max = cur;
    }
    d->unk04 = max;
    d->lines = lines;
    d->text = D_801ED290_ovl_101CE0[d->id];
    x = (320 - max) / 2;
    h = lines * 15;
    y = (240 - h) / 2;
    right = 320 - x;
    bottom = 0xEE - y;
    if (D_801F0B40_ovl_101CE0 == 0) {
        d->y2 = y + 0x21;
        d->x2 = x - 4;
        d->w2 = right + 4;
        d->h2 = bottom + 0x25;
        d->x = 0x9C;
        d->w = 0xA4;
        d->y = d->y2;
        d->h = d->y + 4;
    } else {
        d->x2 = x - 4;
        d->w2 = right + 4;
        d->y2 = D_801F0B48_ovl_101CE0.y;
        d->h2 = d->y2 + h + 2;
        d->x = (d->x2 + d->w2) / 2 - 4;
        d->w = (d->x2 + d->w2) / 2 + 4;
        d->y = d->y2;
        d->h = d->y2 + 4;
    }
    d->h2 += 3;
    if (top != -1) {
        s32 old = d->y2;

        d->y2 = top;
        d->h2 = top + (d->h2 - old);
        d->y = d->y2;
        d->h = d->y + 4;
    }
}

/* Lays out the choice window of dialog d: label lengths, and the button and text rects in r
 * (the label widths w0/w1 are never zeroed before TextLen134 adds to them, as in retail) */
#ifdef NON_MATCHING
/* 93/93 instructions, same code: only a0/a1 are swapped between x and the w1/y temporaries */
void func_801E0DBC_ovl_101CE0(Dialog134 *d, s32 *r) {
    s32 w0;
    s32 w1;
    s32 w;
    s32 x;
    s32 y;
    s32 m;
    s32 right;

    d->len0 = TextLen134((u8 *)d->opt0, &w0);
    d->len1 = TextLen134((u8 *)d->opt1, &w1);
    right = d->w2;
    x = right - 0x16;
    w = w0;
    if (w < w1) {
        w = w1;
    }
    x -= w;
    x -= 0x10;
    y = d->h2;
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
