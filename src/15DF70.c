#include "common.h"
#include "chunk.h"
#include "heap.h"

/* 15DF70 */

extern void *D_80213EE8_ovl_14EBE0;

extern u8 D_801F36A0;
extern s32 D_801F401C;
extern u8 D_80213EA4_ovl_14EBE0[];
/* Cursor records: entry list, current entry, base id ORed into entry ids */
typedef struct {
    u8 *items; /* 10-byte entries: s16 x, s16 y, u8 next[4] (left, right, down, up), u16 id */
    u8 cur;
    u8 b5;
    u8 pad6[2];
    s32 base;
} Cursor15;
extern Cursor15 D_80213EA0_ovl_14EBE0[];
extern u8 D_80213EEC_ovl_14EBE0;
extern s32 D_80213EF0_ovl_14EBE0;
void func_80200DD0_ovl_14EBE0(s32 x, s32 y, s32 tile);
void func_80200F70_ovl_14EBE0(void *a, void *b, s32 c, s32 d, s32 e);
typedef struct {
    u32 w0;
    u32 w1;
} Gfx;
extern Gfx *D_800E9BA0;
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
/* --- end decls --- */

void func_8020CE00_ovl_14EBE0(void) {
    D_80213EE8_ovl_14EBE0 = NULL;
}

void func_8020CE0C_ovl_14EBE0(void) {
    u8 f;

    if (D_80213EE8_ovl_14EBE0 == NULL) {
        D_80213EE8_ovl_14EBE0 = LoadChunk(0x1DC326E);
    }
    f = D_801F36A0;
    if ((f & 1) && !(f & 4) && D_801F401C < 100) {
        s32 i;

        if (!(f & 2)) {
            i = 0x30;
        } else {
            i = 0x18;
        }
        D_80213EA4_ovl_14EBE0[i] = 1;
    }
}

void func_8020CE8C_ovl_14EBE0(void) {
    if (D_80213EE8_ovl_14EBE0 != NULL) {
        HFree(D_80213EE8_ovl_14EBE0);
    }
    D_80213EE8_ovl_14EBE0 = NULL;
}

extern u16 *D_800C4BDC; /* buttons pressed */
extern u16 *D_800C4C4C; /* buttons repeated */
extern u16 *D_801F0CA0;
extern u8 D_801939D3;
extern u8 D_801939D4;
void *func_8017F36C(u16 id);
void func_8017EF24(s32 a, u16 kind, s16 x, s16 y, s16 w, s16 h, s16 x2, s16 y2, s16 w2, s16 h2);
void func_8020CDA0_ovl_14EBE0(s32 se);
s32 func_8020D328_ovl_14EBE0(u8 kind);

/* Cursor k update: on confirm opens the entry's message box (0x300), otherwise moves along the
 * entry's neighbour links with the d-pad and wraps the 0x80-flagged targets */
#ifdef NON_MATCHING
/* four instructions long: the original keeps k * 12 in s1 for the final cursor store, after the
 * wrap tests join; here it is recomputed from k */
void func_8020CEBC_ovl_14EBE0(u8 k) {
    u8 *list;
    u8 cur;
    u16 id;
    s32 v;
    u8 *n;
    u8 old;
    u16 btn;
    u8 c;
    u8 nc;

    D_80213EEC_ovl_14EBE0++;
    list = D_80213EA0_ovl_14EBE0[k].items;
    cur = D_80213EA0_ovl_14EBE0[k].cur;
    if ((*D_801F0CA0 & *D_800C4BDC) && func_8017F36C(0x300) == NULL) {
        id = *(u16 *)(list + cur * 10 + 8);
        if (id & 0x4000) {
            v = func_8020D328_ovl_14EBE0(id & 0xFF);
        } else {
            v = D_80213EA0_ovl_14EBE0[k].base | (id & 0xFF);
        }
        D_801939D3 = D_801F36A0 & 1;
        D_801939D4 = D_801F401C;
        func_8017EF24(v | 0x30000, 0x200, 0x98, 0x8E, 0xA8, 0x9E, 0x18, 0x82, 0x128, 0xAA);
        n = func_8017F36C(0x300);
        FIELD(FIELD(n, u8 *, 0xD0), u8, 0x5F4) = 2;
        FIELD(FIELD(n, u8 *, 0xD0), u8, 0x5F0) = 0xFF;
        func_8020CDA0_ovl_14EBE0(0x10);
        return;
    }
    n = func_8017F36C(0x300);
    if (n != NULL) {
        if (FIELD(FIELD(n, u8 *, 0xD0), u8, 0x5F0) == 0xFF) {
            FIELD(FIELD(n, u8 *, 0xD0), u8, 0x5F0) = 0;
        }
        return;
    }
    old = D_80213EA0_ovl_14EBE0[k].cur;
    if (*D_800C4BDC & 0x4000) {
        D_80213EA0_ovl_14EBE0[k].b5 = 0;
        D_80213EA0_ovl_14EBE0[k].cur = 0;
    } else {
        btn = *D_800C4C4C;
        if (btn & 0x200) {
            D_80213EA0_ovl_14EBE0[k].cur = list[cur * 10 + 5];
        } else if (btn & 0x100) {
            D_80213EA0_ovl_14EBE0[k].cur = list[cur * 10 + 4];
        } else if (btn & 0x800) {
            D_80213EA0_ovl_14EBE0[k].cur = list[cur * 10 + 7];
        } else if (btn & 0x400) {
            D_80213EA0_ovl_14EBE0[k].cur = list[cur * 10 + 6];
        }
    }
    if (old != D_80213EA0_ovl_14EBE0[k].cur) {
        func_8020CDA0_ovl_14EBE0(2);
    }
    c = D_80213EA0_ovl_14EBE0[k].cur;
    if (c & 0x80) {
        if (k == 0) {
            if (D_801F36A0 & 4) {
                D_80213EA0_ovl_14EBE0[k].cur &= 0x7F;
            } else {
                D_80213EA0_ovl_14EBE0[k].cur = 5;
            }
        } else {
            if ((k == 2 || k == 4) && !(D_801F36A0 & 4)) {
                nc = 1;
            } else {
                nc = c & 0x7F;
            }
            D_80213EA0_ovl_14EBE0[k].cur = nc;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/15DF70", func_8020CEBC_ovl_14EBE0);
#endif

/* Draws cursor k (12-byte records at D_80213EA0: list pointer, index at +4) at its list
 * entry's position, flipped one way when the entry has flag 0x8000 */
#ifdef NON_MATCHING
/* cursor draw: entry address loads scheduled differently */
void func_8020D210_ovl_14EBE0(u8 k) {
    u8 *e = *(u8 **)((u8 *)&D_80213EA0_ovl_14EBE0 + k * 12) + D_80213EA4_ovl_14EBE0[k * 12] * 10;
    s32 x = FIELD(e, s16, 0);
    s32 y = FIELD(e, s16, 2);

    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xDE000000;
        _g->w1 = (u32)&D_80213EF0_ovl_14EBE0;
    }
    func_80200F70_ovl_14EBE0((u8 *)D_80213EE8_ovl_14EBE0 + ((D_80213EEC_ovl_14EBE0 * 8) & 0x20),
                             (u8 *)D_80213EE8_ovl_14EBE0 + 0x40, 0x20, 0x10, 1);
    if (FIELD(e, u16, 8) & 0x8000) {
        func_80200DD0_ovl_14EBE0(x + 16, y, 0x37);
    } else {
        func_80200DD0_ovl_14EBE0(x, y, 0x38);
    }
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xE7000000;
        _g->w1 = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/15DF70", func_8020D210_ovl_14EBE0);
#endif

u8 func_8016DEC4(u8 cls, u8 base);
extern u8 D_8018F481;
extern u8 D_80193BC0[][0x38]; /* player characters */
extern u8 D_80195560[][0x34]; /* enemy characters */
extern u16 D_801F36BC;
extern u8 D_801F401F;

/* Portrait id for speaker kind: 4 = the current character's class portrait (0x4004/0x4005),
 * 0 = its face (0x5000 | id), 15/18 = map-relative portraits */
s32 func_8020D328_ovl_14EBE0(u8 kind) {
    u8 a;
    u8 b;

    switch (kind) {
        case 0:
            if (D_801F401F >= 100 || D_801F401F == 0) {
                a = 1;
            } else if (D_801F36A0 & 1) {
                a = D_80195560[D_801F401F][0x12];
            } else {
                a = D_80193BC0[D_801F401F][0x12];
            }
            if (D_8018F481 == 4 && a == 0x62) {
                a = 0xE0;
            }
            return a | 0x5000;
        case 4:
            b = 0;
            if (D_801F401F >= 100 || D_801F401F == 0) {
                a = 0;
            } else if (D_801F36A0 & 1) {
                a = D_80195560[D_801F401F][0x11];
                b = D_80195560[D_801F401F][0x12];
            } else {
                a = D_80193BC0[D_801F401F][0x11];
                b = D_80193BC0[D_801F401F][0x12];
            }
            return func_8016DEC4(a, b) == 2 ? 0x4005 : 0x4004;
        case 15:
            return ((D_801F36BC >> 8) + 15) | 0x4000;
        case 18:
            return ((D_801F36BC >> 8) + 18) | 0x4000;
        default:
            return 0x40000;
    }
}
