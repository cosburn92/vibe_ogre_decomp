#include "common.h"
#include "heap.h"

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))

extern u8 *D_80196AF8; /* Organize-screen state */
extern u16 D_80190F84[];
void func_801C7E90_ovl_087200(s32 a, s32 b, s32 c);
u8 *func_801CC410_ovl_087200(s32 id);
void func_801CC7D4_ovl_087200(s32 a);
void _bcopy(const void *src, void *dst, s32 n);
void func_801CC684_ovl_087200(u8 *w, void (*f)(), s32 a, s32 b, s32 c, s32 d);
void func_801B6394_ovl_087200();
void func_801B3B00_ovl_087200();
u8 func_801D080C_ovl_087200(u16 row);
void func_801CE540_ovl_087200(void);
void func_801CE66C_ovl_087200(void);
void func_801CE374_ovl_087200(void);
void func_801CE28C_ovl_087200(void);
void func_801AA2B8_ovl_087200();
void func_801C7CA0_ovl_087200(s16 *a, s16 *b, s16 *c, s16 *d);
void func_801CCA50_ovl_087200(s32 a, s32 b, void (*f)(), s32 c, s32 d, s32 e, s32 g);
void func_801CC784_ovl_087200(u8 *w, s32 a, s32 b, s32 c, s32 d);





typedef struct {
    u8 b[0x36];
} OrgSquad; /* organize-screen squad record, 30 of them at state +0x117C */
u8 func_801D06F4_ovl_087200(u16 sq);
s32 func_801CC974_ovl_087200(u16 kind, u8 b, void (*fn)(), s16 x, s16 y, s16 w, s16 h, s16 x2, s16 y2, s16 w2, s16 h2);
void func_801B1FE0_ovl_087200();
extern u16 D_80190EBC[];
extern u16 D_80190F82;
void func_801C7D78_ovl_087200(s16 *a, s16 *b, s16 *c, s16 *d);
void func_801CC6D4_ovl_087200(u8 *w, void (*f)(), void (*g)(), s32 a, s32 b, s32 c, s32 d);
void func_801B7F50_ovl_087200();
void func_801B74CC_ovl_087200();
void bzero(void *p, s32 n);
void func_801CC72C_ovl_087200(u8 *w, void (*f)(), void (*g)(), s32 a, s32 b, s32 c, s32 d);
void func_801CC5B4_ovl_087200(u8 *w, s32 a, s32 b, s32 c, s32 d);
void func_801C67B0_ovl_087200(s32 sq);
void func_801B4AF4_ovl_087200();
void func_801B577C_ovl_087200();
s32 func_801CC3B8_ovl_087200(s32 id);
void func_801C0798_ovl_087200(s16 a, s32 b);
void func_801A43F4_ovl_087200();
void func_801AA114_ovl_087200();
u8 func_801D8B58_ovl_087200(void);
u8 func_801D8AE0_ovl_087200(void);
void func_801C18AC_ovl_087200(s32 a, s32 b, s32 c);
extern void (*D_801EF1E0_ovl_087200[])(void);
void func_801D8A60_ovl_087200(s32 a);
extern u8 D_80191010[];
extern u8 D_80190F81;
u16 func_801CBC98_ovl_087200(u8 i);
void func_801CE074_ovl_087200(void);
/* --- end decls --- */

void func_801A4894_ovl_087200();
extern s32 D_800E9C0A;

/* Opens message a in the message window at the bottom (pos 1), middle (2) or top of the screen;
 * groups 0x1C-0x1E use the tall portrait window. With show set, a group-5 message is skipped when
 * the message option (D_800E9C0A + 6) is off */
#ifdef NON_MATCHING
/* 88/88, 9 words: the window height lands in t2 here, t1 in the original */
void func_801C7E90_ovl_087200(s32 a, s32 b, s32 c) {
    u8 pos = b;
    u8 show = c;
    s32 grp = a & 0xFFFF0000;
    void (*fn)();
    u32 h;
    s32 y0, y1;
    s16 ty0, ty1;

    if ((grp == 0x1C0000) | (grp == 0x1D0000) || (h = 0x28, grp == 0x1E0000)) {
        fn = func_801A4894_ovl_087200;
        h = 0x38;
    } else {
        fn = func_801A43F4_ovl_087200;
    }
    if (show && ((FIELD(&D_800E9C0A, u8, 6) == 0) & (grp == 0x50000))) {
        return;
    }

    FIELD(D_80196AF8, s32, 0x10C8) = a;
    if (pos == 1) {
        y0 = 0xCB;
        y1 = 0xCF;
        ty0 = 0xCF - h;
        ty1 = 0xCF;
    } else if (pos == 2) {
        y0 = 0x76;
        y1 = 0x7A;
        ty0 = 0x78 - (h >> 1);
        ty1 = (h >> 1) + 0x78;
    } else {
        y0 = 0x18;
        y1 = 0x1C;
        ty0 = 0x18;
        ty1 = h + 0x18;
    }
    FIELD(D_80196AF8, s32, 0x10CC) = func_801CC974_ovl_087200(0x100, 0x12, fn, 0x9C, y0, 0xA4, y1, 0x18, ty0, 0x128, ty1);
    ((void (*)(s32, s32))func_801C0798_ovl_087200)(FIELD(D_80196AF8, s32, 0x10CC), FIELD(D_80196AF8, s32, 0x10C8));
    func_801C18AC_ovl_087200(0xB, 0, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/B48F0", func_801C7E90_ovl_087200);
#endif

void func_801C7FF0_ovl_087200(s32 a, u8 b) {
    func_801C7E90_ovl_087200(a, b, 1);
}

inline void func_801C8010_ovl_087200(s32 a) {
    u8 *st = D_80196AF8;
    s32 f;

    if (st[0x98] == 0 || st[0x99] == 1) {
        f = 1;
    } else {
        f = 0;
    }
    func_801C7E90_ovl_087200(a, f, 1);
}

void func_801C8050_ovl_087200(s32 a, s32 v) {
    u8 *st = D_80196AF8;
    s32 f;

    if (st[0x98] == 0 || st[0x99] == 1) {
        f = 1;
    } else {
        f = 0;
    }
    func_801C7E90_ovl_087200(a, f, 1);
    func_801CC410_ovl_087200(0x100)[0xE7] = v;
}

inline void func_801C80A8_ovl_087200(s32 a) {
    u8 *w = func_801CC410_ovl_087200(5);

    u8 *x = w;

    if (w == NULL) {
        FIELD(D_80196AF8, s32, 0x10D0) = func_801CC974_ovl_087200(5, 10, func_801A43F4_ovl_087200, 0x9C, 0xD6, 0xA4, 0xDE, 0x18, 0xB6, 0x128, 0xDE);
    } else {
        HFree(FIELD(x, void *, 0xF4));
    }
    func_801C0798_ovl_087200(func_801CC3B8_ovl_087200(5), a);
}

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801C8158_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801C84BC_ovl_087200);

void func_801C97A0_ovl_087200(void) {
    s32 pad;
    u8 *st = D_80196AF8;
    s16 v = FIELD(st, s16, 0x122);

    switch (v) {
        case 0:
            FIELD(st, u16, 0x12E) = 10;
            FIELD(st, u16, 0x122)++;
            break;
        case 1:
            if (FIELD(st, u16, 0x12E) == 0) {
                FIELD(st, u16, 0x122) = v + 1;
            }
            break;
        case 2:
        case 99:
            FIELD(st, u16, 0x120) = 999;
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801C9828_ovl_087200);

u16 func_801CF190_ovl_087200(u8 *st);
u8 func_801CF7F8_ovl_087200();
extern s32 D_801939DC;

/* Organize-screen auto-arrange step (state 0x122): counts the free slots, warns when nothing can
 * be arranged, otherwise picks the arrangement and confirms; state 99 closes */
void func_801C9D4C_ovl_087200(void) {
    switch (FIELD(D_80196AF8, s16, 0x122)) {
        case 0:
            bzero(D_80196AF8 + 0x1BEE, 0x1FE);
            D_80196AF8[0x1DED] = func_801CF7F8_ovl_087200();
            if (D_80190F81 == 0) {
                FIELD(D_80196AF8, s16, 0x122) = 99;
                func_801C8010_ovl_087200(0x40009);
            } else if (D_80196AF8[0x1DED] == 0) {
                FIELD(D_80196AF8, s16, 0x122) = 99;
                func_801C8010_ovl_087200(0x4000E);
            } else {
                FIELD(D_80196AF8, s16, 0x122)++;
            }
            break;
        case 1:
            if (D_80196AF8[0x1DED] > D_80190F81) {
                D_801939DC = func_801CF190_ovl_087200(D_80196AF8);
                FIELD(D_80196AF8, s16, 0x122)++;
                func_801C8010_ovl_087200(0x4001A);
            } else {
                D_801939DC = func_801CF190_ovl_087200(D_80196AF8);
                FIELD(D_80196AF8, s16, 0x122)++;
                func_801C8010_ovl_087200(0x40031);
            }
            break;
        case 2:
            if (func_801CC410_ovl_087200(0x100) == NULL) {
                FIELD(D_80196AF8, s16, 0x122) = 99;
            }
            break;
        case 99:
            func_801C8158_ovl_087200(D_80196AF8);
            break;
    }
}

void func_801C9F44_ovl_087200(void) {
    if (func_801D8B58_ovl_087200()) {
        D_80196AF8[0xA0] |= 0x82;
        func_801C18AC_ovl_087200(FIELD(D_80196AF8, s16, 0x122) != 0 ? 9 : 8, 0, 0);
    } else if (FIELD(D_80196AF8, s16, 0x122) != 0 && func_801D8AE0_ovl_087200()) {
        D_80196AF8[0xA0] |= 0x81;
        FIELD(D_80196AF8, s16, 0x120) = 7;
        func_801C18AC_ovl_087200(6, 0x63, 0);
    } else {
        D_801EF1E0_ovl_087200[FIELD(D_80196AF8, s32, 0x1BD4)]();
    }
}

/* Cycles the tab cursor (0..2) left or right, skipping disabled tabs */
void func_801CA030_ovl_087200(s32 dir) {
    if (D_80196AF8[0x1DFF] >= 2) {
        if (dir == -1) {
            func_801D8A60_ovl_087200(2);
            do {
                D_80196AF8[0x9D] = (D_80196AF8[0x9D] == 0) ? 2 : D_80196AF8[0x9D] - 1;
            } while ((D_80196AF8 + D_80196AF8[0x9D])[0x1E00] == 0);
        } else if (dir == 1) {
            func_801D8A60_ovl_087200(2);
            do {
                D_80196AF8[0x9D] = (D_80196AF8[0x9D] + 1) % 3;
            } while ((D_80196AF8 + D_80196AF8[0x9D])[0x1E00] == 0);
        }
    }
}

void func_801CA110_ovl_087200(void) {
    func_801CC7D4_ovl_087200(0x400);
    func_801CC7D4_ovl_087200(3);
    func_801CC7D4_ovl_087200(5);
    D_80196AF8[0xA1] = 0;
}

typedef struct {
    /* 0x0 */ u16 id;
    /* 0x2 */ u8 equipped;
    /* 0x3 */ u8 count;
} StockB48;
extern StockB48 D_80193AC0[];

void func_801A7940_ovl_087200();
void func_801A87F8_ovl_087200();
extern StockB48 D_80196B00[];

/* Opens the item list for the selected category: list window (its frame flag 4 set), scroll
 * bar, then the description window for the current entry (consumables use message group 0x1B) */
void func_801CA148_ovl_087200(s32 unused) {
    u16 k = FIELD(D_80196AF8 + FIELD(D_80196AF8, s16, 0x1BDA) * 2, u16, 0x1BEE);
    s32 msg;
    u8 *w;

    D_80196AF8[0xA1] = 1;
    if ((D_80196AF8 + D_80196AF8[0x9D])[0x1E00] >= 7) {
        msg = D_80193AC0[k].id | 0x1B0000;
    } else {
        msg = D_80196B00[k].id | 0x130000;
    }
    w = D_80196AF8 + ((s16)func_801CC974_ovl_087200(0x400, 10, func_801A87F8_ovl_087200, 0x18, 0x16, 0x20, 0x1E, 0x18, 0x16,
                                               0xB2, 0xB0) * 0x108 + 0x650);
    w[0xE6] |= 4;
    func_801CC974_ovl_087200(3, 10, func_801A7940_ovl_087200, 0x120, 0x18, 0x128, 0x20, 0xBC, 0x18, 0x128, 0xAE);
    func_801C80A8_ovl_087200(msg);
}

u16 func_801CFA04_ovl_087200(u16 k);
void func_801CA148_ovl_087200(s32 a);

/* Builds the list of the 8 item categories that have entries (0x1E00, count 0x1DFF), selects
 * the first and sets the list window up for its entry count */
void func_801CA328_ovl_087200(void) {
    s32 i;

    D_80196AF8[0x9D] = 0;
    D_80196AF8[0x1DFF] = 0;
    for (i = 0; i < 8; i++) {
        (D_80196AF8 + i)[0x1E00] = 0;
        (D_80196AF8 + i)[0x1DF6] = 0;
        (D_80196AF8 + i)[0x1DEE] = 0;
        if (func_801CFA04_ovl_087200(i)) {
            u8 *st = D_80196AF8;
            u8 n = st[0x1DFF];

            st[0x1DFF] = n + 1;
            st[n + 0x1E00] = i + 1;
        }
    }
    D_80196AF8[0x1DFE] = 3;
    D_80196AF8[0x9B] = 0;
    D_80196AF8[0x9A] = 0;
    D_80196AF8[0x1DED] = func_801CFA04_ovl_087200((D_80196AF8 + D_80196AF8[0x9D])[0x1E00] - 1);
    FIELD(D_80196AF8, s16, 0x1BDA) = 0;
    FIELD(D_80196AF8, s16, 0x1BDC) = 0;
    FIELD(D_80196AF8, s16, 0x1BDE) = 8;
    func_801CA148_ovl_087200(FIELD(D_80196AF8, s16, 0x1BE0) = D_80196AF8[0x1DED] - 1);
}

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif

/* Recounts squad sq's items (ids from 100 in its leader's 9 slots, clearing their flags) and
 * releases members from the back while the squad is over that count */
void func_801CA44C_ovl_087200(u8 *sq) {
    u8 *m;
    u8 *p;
    s32 i;
    s32 j;
    s32 n;
    u8 c;

    n = 1;
    m = D_80196AF8 + ((sq[2] * 0x36) + 0x117C);
    for (i = 0; i < 9; i++) {
        c = (m + i)[4];
        n += (c != 0xFF) & (c >= 100);
        if (c != 0xFF) {
            p = D_80196AF8 + ((c * 2) + 0x1872);
            *p &= 0xDF;
        }
    }
    sq[9] = n;
    for (j = 4; n < sq[8] && j != 0; j--) {
        c = (sq + j)[2];
        if (c != 0xFF) {
            m = D_80196AF8 + ((c * 0x36) + 0x117C);
            if (m[1] & 8) {
                FIELD(D_80196AF8, s32, 0x2C0)++;
            }
            m[1] = 0;
            m[2] = 0xFF;
            (sq + j)[2] = 0xFF;
            sq[8]--;
        }
    }
    func_801CE28C_ovl_087200();
}

u16 func_8016B738(u16 id);
u8 func_801CDEB8_ovl_087200(u8 sq);
void func_801CA704_ovl_087200(u16 r);
void func_801CAD90_ovl_087200(u16 id);

/* Disbands squad record sq of the organize screen: clears its grid row if it is deployed, frees
 * its nine members, returns its ten items to the stock and resets the record */
#ifdef NON_MATCHING
/* 95/95 instructions, 6 words differ: the original loads the state pointer before masking the row index, so the two swap v0/v1 */
void func_801CA588_ovl_087200(u16 sq) {
    u8 *m = D_80196AF8 + (sq * 0x36 + 0x117C);
    s32 i;
    u8 r;
    u8 c;
    u16 it;

    if (m[1] & 8) {
        r = func_801CDEB8_ovl_087200(sq);
        if ((D_80196AF8 + r * 14)[0x10D6] == sq) {
            func_801CA704_ovl_087200(r);
        }
    }
    for (i = 0; i < 9; i++) {
        c = (m + i)[4];
        if (c != 0xFF) {
            func_801CAD90_ovl_087200(c);
            (m + i)[4] = 0xFF;
        }
    }
    for (i = 0; i < 10; i++) {
        it = FIELD(m + i * 2, u16, 0x22);
        if (it != 0) {
            D_80193AC0[func_8016B738(it)].equipped--;
            FIELD(m + i * 2, u16, 0x22) = 0;
        }
    }
    m[3] = 0xFF;
    m[0] = 0;
    m[1] = 0;
    if (sq != 30) {
        FIELD(D_80196AF8, s32, 0x2C0)--;
        FIELD(D_80196AF8, s32, 0x2C4)--;
    }
    func_801CE540_ovl_087200();
    func_801CE28C_ovl_087200();
}
#else
INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CA588_ovl_087200);
#endif

/* Clears grid row r: frees its units (members lose their 0x20 flag) and resets the row */
void func_801CA704_ovl_087200(u16 r) {
    u8 *row = D_80196AF8 + (r * 14 + 0x10D4);
    s32 c;
    s32 k;
    u8 u;
    u8 m;
    u8 *rec;
    s32 o;

    for (c = 0; c < 5; c++) {
        u = (row + c)[2];
        if (u == 0xFF) {
            continue;
        }
        rec = D_80196AF8 + (u * 54 + 0x117C);
        rec[1] = 0;
        rec[2] = 0xFF;
        (row + c)[2] = 0xFF;
        FIELD(D_80196AF8, s32, 0x2C0)++;
        for (k = 0; k < 9; k++) {
            m = (rec + k)[4];
            if (m != 0xFF) {
                o = m * 2;
                (D_80196AF8 + o)[0x1872] &= ~0x20;
            }
        }
    }
    row[8] = 0;
    row[0] = 0;
    row[1] = 0;
    FIELD(D_80196AF8, s32, 0x5DC)--;
    func_801CE66C_ovl_087200();
    func_801CE374_ovl_087200();
}

/* Clears flag 0x20 of the members of slot record u (see ClearMemberFlag4) */
static inline void ClearMemberFlag20(u8 u) {
    s32 k;

    for (k = 0; k < 9; k++) {
        s32 o;
        u8 m;

        o = u * 54;
        m = (D_80196AF8 + o + k)[0x1180];
        if (m != 0xFF) {
            o = m * 2;
            (D_80196AF8 + o)[0x1872] &= ~0x20;
        }
    }
}

/* Removes the unit in grid cell (r, c) of the organize screen: clears its slot record, shifts the
 * cell behind it forward for columns 1-2, and drops its members' 0x20 flag */
void func_801CA80C_ovl_087200(u16 r, u16 c) {
    u8 *row = D_80196AF8 + 0x10D4 + r * 14;
    u8 *cell = row + c;
    u8 u = cell[2];
    s32 off;
    u8 t;

    if (u == 0xFF) {
        return;
    }
    off = u * 54;
    (D_80196AF8 + off)[0x117D] = 0;
    (D_80196AF8 + off)[0x117E] = 0xFF;
    cell[2] = 0xFF;
    FIELD(D_80196AF8, s32, 0x2C0)++;
    if ((u16)(c - 1) < 2) {
        t = cell[4];
        cell[4] = 0xFF;
        cell[2] = t;
    }
    row[8]--;
    ClearMemberFlag20(u);
}

/* Marks every unit placed in the ten grid rows as deployed (flag 8, counting down the free total),
 * recomputes each row's value and refreshes the lists */
void func_801CA900_ovl_087200(void) {
    s32 i;
    s32 k;
    u8 *row;
    u8 *rec;
    u8 u;

    for (i = 0; i < 10; i++) {
        row = D_80196AF8 + 0x10D4 + i * 14;
        if (row[8] == 0) {
            continue;
        }
        for (k = 0; k < 5; k++) {
            u = (row + k)[2];
            if (u == 0xFF) {
                continue;
            }
            rec = D_80196AF8 + (u * 54 + 0x117C);
            if (!(rec[1] & 8)) {
                FIELD(D_80196AF8, s32, 0x2C0)--;
                rec[1] |= 8;
            }
        }
        row[0xA] = func_801D080C_ovl_087200(i);
    }
    func_801CE540_ovl_087200();
    func_801CE66C_ovl_087200();
    func_801CE374_ovl_087200();
    func_801CE28C_ovl_087200();
}

void func_801CA9FC_ovl_087200(void) {
    u8 *b = D_80196AF8 + 0x1160;
    s32 i;
    u8 s;

    for (i = 0; i < 5; i++) {
        s = (b + i)[2];
        if (s != 0xFF) {
            u8 *q = D_80196AF8 + (s * 0x36 + 0x117C);

            q[1] &= 0xFD;
        }
    }
}

/* Clears flag 2 on the nine slot units; units 100+ (guests) are also returned: their count goes back
 * to D_80190F81 and their entries are cleared */
void func_801CAA64_ovl_087200(void) {
    u8 *slots = D_80196AF8 + 0x17D0;
    s32 i;
    u8 u;
    u8 *p;

    for (i = 0; i < 9; i++) {
        u = (slots + i)[4];
        if (u == 0xFF) {
            continue;
        }
        p = D_80196AF8 + (u * 2 + 0x1872);
        if (u < 100) {
            if (*p & 2) {
                *p &= ~2;
            }
        } else {
            if (*p & 2) {
                *p &= ~0x42;
            }
            ((u8 *)D_80190EBC)[0xC5] += func_801CBC98_ovl_087200(u);
            D_80190EBC[u] = 0;
            D_80191010[u] = 0;
        }
    }
}

u8 func_801CBBA0_ovl_087200(void);
u8 func_801CBBD4_ovl_087200(void);
u8 func_801D1E38_ovl_087200(u8 sq);
u8 func_801CF0D4_ovl_087200(u16 sq);
void func_801D0484_ovl_087200(u16 sq);

/* Commits squad sq (30 = the squad being built, stored into a new slot first): marks its members
 * placed (0x08, counting down the free total unless already 0x40) and led (0x20), then refreshes */
#ifdef NON_MATCHING
/* 138/138 instructions, 7 words differ: only the operand order of the squad-record address adds (base + s * 0x36, then + i) */
void func_801CAB68_ovl_087200(s32 sq) {
    u16 s;
    u8 *st;
    s32 i;
    s32 k;
    u8 *f;
    u8 id;

    if (sq < 0x80) {
        s = sq;
        if (sq == 30) {
            s = func_801CBBA0_ovl_087200();
            st = D_80196AF8 + 0x17D0;
            st[0x00] = func_801CBBD4_ovl_087200();
            st[0x02] = 0xFF;
            st[0x20] = 0;
            st[0x0D] = 0xFF;
            st[0x1F] = 0;
            st[0x1E] = 0;
            st[0x01] = 0;
            st[0x1D] = func_801D06F4_ovl_087200(30);
            for (k = 9; k >= 0; k--) {
                ((s16 *)(st + 0x22))[k] = 0;
            }
            _bcopy(D_80196AF8 + 0x17D0, D_80196AF8 + (s * 0x36 + 0x117C), 0x36);
            FIELD(D_80196AF8, s32, 0x2C0)++;
            FIELD(D_80196AF8, s32, 0x2C4)++;
        }
        for (i = 0; i < 9; i++) {
            id = ((OrgSquad *)(D_80196AF8 + 0x117C))[s].b[i + 4];
            f = D_80196AF8 + (id * 2 + 0x1872);
            if (id != 0xFF && !(*f & 8)) {
                u8 v = *f;

                *f = v & 0x7F;
                if (v & 0x40) {
                    *f = (v & 0x7F) | 0x48;
                } else {
                    *f = (v & 0x7F) | 8;
                    FIELD(D_80196AF8, s32, 0x5D4)--;
                }
                if (((OrgSquad *)(D_80196AF8 + 0x117C))[s].b[2] != 0xFF) {
                    *f |= 0x20;
                }
            }
        }
        if (sq != 30 && func_801D1E38_ovl_087200(sq)) {
            D_80196AF8[func_801CDEB8_ovl_087200(sq) * 0xE + 0x10DD] = func_801CF0D4_ovl_087200(sq) + 1;
        }
        func_801D0484_ovl_087200(s);
        func_801CE540_ovl_087200();
        func_801CE074_ovl_087200();
        func_801CE28C_ovl_087200();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CAB68_ovl_087200);
#endif

void func_801CAD90_ovl_087200(u16 id) {
    if (id != 0xFF) {
        if (id >= 100) {
            u16 r = func_801CBC98_ovl_087200(id);
            s32 o = id * 2;

            /* D_80190EBC[id] spelled with the byte offset o: the original computes id * 2 once
             * for both tables, and D_80190EBC[id] gets its own shift */
            *(u16 *)((u8 *)D_80190EBC + o) = 0;
            D_80191010[id] = 0;
            D_80190F81 += r;
            (D_80196AF8 + o)[0x1872] = 0;
        }
        {
            s32 o = id * 2;

            if ((D_80196AF8 + o)[0x1872] & 8) {
                FIELD(D_80196AF8, s32, 0x5D4)++;
            }
            (D_80196AF8 + o)[0x1872] = 0;
        }
        func_801CE074_ovl_087200();
    }
}

/* Clears flag 4 of every member placed in squad sq's nine cells (o is one offset variable,
 * the row offset then the member offset, which keeps the base + offset add order; inlined
 * into its callers, so each copy gets its own loop counter) */
static inline void ClearMemberFlag4(u16 sq) {
    s32 i;

    for (i = 0; i < 9; i++) {
        s32 o;
        u8 m;

        o = sq * 0x36;
        m = (D_80196AF8 + o + i)[0x1180];
        if (m != 0xFF) {
            o = m * 2;
            (D_80196AF8 + o)[0x1872] &= ~4;
        }
    }
}

void func_801CAE4C_ovl_087200(u16 sq) {
    ClearMemberFlag4(sq);
}

void func_801CAEB0_ovl_087200(u16 sq, u16 v) {
    OrgSquad *q = &((OrgSquad *)(D_80196AF8 + 0x117C))[sq];

    if (q->b[4 + v] != 0xFF) {
        q->b[3] = v;
    }
    q->b[0x1D] = func_801D06F4_ovl_087200(sq);
}

/* Moves the member in cell a of squad sa to cell b of squad sb, swapping with its occupant (cells
 * 9+ are the reserve list); the leader cell (row byte 3) follows the move. Clears flag 4 of both
 * squads' members and rebuilds their flag grids */
void func_801CAF18_ovl_087200(u16 sa, u16 a, u16 sb, u16 b) {
    u8 moved = 0;
    u8 *pa;
    u8 *pb;
    u8 *row;
    u8 t;

    if (a >= 9) {
        pa = D_80196AF8 + (a + 0x1A21);
    } else {
        row = D_80196AF8 + (sa * 0x36 + 0x117C);
        pa = row + (a + 4);
        if (row[3] == a) {
            row[3] = b;
            moved = 1;
        }
    }
    if (b >= 9) {
        pb = D_80196AF8 + (b + 0x1A21);
    } else {
        row = D_80196AF8 + (sb * 0x36 + 0x117C);
        pb = row + (b + 4);
        if (!moved && row[3] == b) {
            row[3] = a;
        }
    }
    if (*pb == 0xFF) {
        *pb = *pa;
        *pa = 0xFF;
    } else {
        t = *pa;
        *pa = *pb;
        *pb = t;
    }
    ClearMemberFlag4(sa);
    ClearMemberFlag4(sb);
    func_801C67B0_ovl_087200(sa);
    func_801C67B0_ovl_087200(sb);
}

/* Swaps formation cells a and b of squad sq (the leader follows its cell), clears flag 4 of every
 * member, then refreshes the squad's front-row count (0x1D) and its display */
void func_801CB0FC_ovl_087200(s32 sq, s32 a, s32 b) {
    u8 *s = D_80196AF8 + ((u16)sq * 0x36 + 0x117C);
    u8 *pb = s + (u16)b;
    u8 t = pb[4];

    if (t == 0xFF) {
        u8 *pa = s + (u16)a;

        pb[4] = pa[4];
        pa[4] = 0xFF;
    } else {
        u8 *pa = s + (u16)a;
        u8 x = pa[4];

        pa[4] = t;
        pb[4] = x;
    }
    if (s[3] == (u16)a) {
        s[3] = b;
    } else if (s[3] == (u16)b) {
        s[3] = a;
    }
    ClearMemberFlag4(sq);
    s[0x1D] = func_801D06F4_ovl_087200((u16)sq);
    func_801C67B0_ovl_087200((u16)sq);
}

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CB21C_ovl_087200);

u8 func_801D08B8_ovl_087200(u8 r);
u8 func_801D1E38_ovl_087200(u8 sq);
u8 func_801CF0D4_ovl_087200(u16 sq);
void func_801D0484_ovl_087200(u16 sq);

/* Refreshes squad record sq after an edit: its 0x1D value, its grid row's derived values when
 * deployed, its members' deployed flag (0x20), then the dependent screens */
#ifdef NON_MATCHING
/* 99/99 instructions, 8 words differ: the grid row address is formed offset + base where the original adds base + offset */
void func_801CB8A0_ovl_087200(u16 sq) {
    u8 *m = D_80196AF8 + (sq * 0x36 + 0x117C);
    s32 i;
    u8 r;
    u8 c;
    u8 *p;

    m[0x1D] = func_801D06F4_ovl_087200(sq);
    if (m[1] & 8) {
        r = func_801CDEB8_ovl_087200(sq);
        D_80196AF8[r * 14 + 0x10DE] = func_801D080C_ovl_087200(r);
        D_80196AF8[r * 14 + 0x10DF] = func_801D08B8_ovl_087200(r);
        if (func_801D1E38_ovl_087200(sq)) {
            D_80196AF8[func_801CDEB8_ovl_087200(sq) * 14 + 0x10DD] = func_801CF0D4_ovl_087200(sq) + 1;
        }
    }
    for (i = 0; i < 9; i++) {
        c = (m + i)[4];
        if (c != 0xFF) {
            p = D_80196AF8 + (c * 2 + 0x1872);
            if (m[1] & 8) {
                *p |= 0x20;
            } else {
                *p &= ~0x20;
            }
        }
    }
    func_801D0484_ovl_087200(sq);
    func_801C67B0_ovl_087200(sq);
}
#else
INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CB8A0_ovl_087200);
#endif

void func_801CBA2C_ovl_087200(u16 i) {
    _bcopy(D_80196AF8 + 0x117C + i * 0x36, D_80196AF8 + 0x1806, 0x36);
}

void func_801CBA74_ovl_087200(u16 i) {
    _bcopy(D_80196AF8 + 0x1806, D_80196AF8 + 0x117C + i * 0x36, 0x36);
}

/* Clears squad record sq (leader, members, positions) */
#ifdef NON_MATCHING
/* two instructions off: the original loads 0xFF (a3) before the loop count 8 (a1); every other
 * instruction matches. The member loop through m = q + 4 gives the walking byte pointer. */
void func_801CBABC_ovl_087200(u8 sq) {
    u8 *q = D_80196AF8 + (sq * 0x36 + 0x117C);
    u8 *m = q + 4;
    s32 k;

    q[1] = 0;
    q[2] = 0xFF;
    q[3] = 0xFF;
    q[0xD] = 0xFF;
    q[0x20] = 0;
    q[0x1E] = 0;
    q[0x1D] = 0;
    for (k = 8; k >= 0; k--) {
        m[k] = 0xFF;
    }
    for (k = 9; k >= 0; k--) {
        FIELD(q, s16, 0x22 + k * 2) = 0;
    }
    func_801C67B0_ovl_087200(sq);
}
#else
INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CBABC_ovl_087200);
#endif

/* Constant/load order differs at the start. */
void func_801CBB54_ovl_087200(void)
{
  u8 *st = D_80196AF8;
  long new_var;
  u8 *p = st + 0x1164;
  s32 i;
  st[0x1167] = 1;
  st[0x1169] = 0;
  st[0x1168] = 0;
  st[0x116D] = 0xFF;
  st[0x116B] = 0;
  new_var = 0xFF;
  st[0x116C] = 0;
  for (i = 4; i >= 0; i--)
  {
    p[2] = new_var;
    p--;
  }

}

/* First free squad slot (0..30) */
u8 func_801CBBA0_ovl_087200(void) {
    u8 *st = D_80196AF8;
    s32 i;

    for (i = 0; i < 30; i++) {
        if (st[0x117F + i * 0x36] == 0xFF) {
            break;
        }
    }
    return i;
}

/* Lowest squad number (1-30) not used by any squad */
u8 func_801CBBD4_ovl_087200(void) {
    u8 used[30];
    s32 i;

    bzero(used, 30);
    for (i = 0; i < 30; i++) {
        u8 *q = D_80196AF8 + 0x117C + i * 0x36;

        if (q[3] != 0xFF) {
            used[q[0] - 1] = 1;
        }
    }
    for (i = 0; i < 30; i++) {
        if (used[i] == 0) {
            break;
        }
    }
    return i + 1;
}

u8 func_801CBC64_ovl_087200(void) {
    s32 i;

    for (i = 0; i < 120; i++) {
        if (D_80190F84[i] == 0) {
            break;
        }
    }
    return i + 100;
}

#ifdef NON_MATCHING
/* rank loop: frame pad and loop branch-likely shape not reproduced */
u16 func_801CBC98_ovl_087200(u8 i) {
    s32 pad;
    u16 q = D_80190F82 / 3;
    s32 v = D_80190EBC[i] - q;
    u16 n = 0;

    do {
        n++;
    } while ((v > 0) & (n < 3) ? (v -= q, 1) : 0);
    if (n >= 4) {
        n = 3;
    }
    return n;
}
#else
INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CBC98_ovl_087200);
#endif

void func_801CBD0C_ovl_087200(s16 a, s16 b, u8 f) {
    u8 *st = D_80196AF8;

    st[0x180] = f;
    if (f) {
        FIELD(st, s16, 0x17C) = a;
        FIELD(st, s16, 0x17E) = b;
    }
}

/* argument evaluation order of the window rect differs */
/* Opens the side window for o. Form adapted from OB64-Decomp func_000b8868 (MIT, (c) 2026 rempred). */
void func_801CBD34_ovl_087200(u8 *o) {
    s32 x = FIELD(o, s32, 0x24);
    s32 y = FIELD(o, s32, 0x28);
    s16 r = func_801CC974_ovl_087200(4, 0x12, func_801AA114_ovl_087200, x - 12, y - 8, x - 4, y + 8, x - 0x54, y - 0x24,
                                     x - 4, y + 0x10);
    u8 *st = D_80196AF8;

    st += r * 0x108;
    st[0x737] = o[0xE7];
}

void func_801CBE08_ovl_087200(u8 *o) {
    s32 x = FIELD(o, s32, 0x24);
    s32 y = FIELD(o, s32, 0x28);
    s16 r = func_801CC974_ovl_087200(4, 0x12, func_801AA2B8_ovl_087200, x - 12, y - 8, x - 4, y + 8, x - 0x3E, y - 0x10,
                                     x - 4, y + 0x10);
    u8 *st = D_80196AF8;

    st += r * 0x108;
    st[0x737] = o[0xE7];
}

void func_801CBEDC_ovl_087200(void) {
    func_801CC684_ovl_087200(func_801CC410_ovl_087200(0), func_801B6394_ovl_087200, 0x18, 0x14, 0x128, 0x8A);
}

void func_801CBF20_ovl_087200(void) {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
    u8 *w = func_801CC410_ovl_087200(0);

    func_801C7CA0_ovl_087200(&a, &b, &c, &d);
    func_801CC7D4_ovl_087200(2);
    func_801CC684_ovl_087200(w, func_801B3B00_ovl_087200, a, b, c, d);
}

void func_801CBF8C_ovl_087200(void) {
    u8 *w = func_801CC410_ovl_087200(0);

    if (w != NULL) {
        func_801CC684_ovl_087200(w, func_801B4AF4_ovl_087200, (s16)FIELD(w, s32, 0xC), (s16)FIELD(w, s32, 0x10),
                                 (s16)(FIELD(w, s32, 0xC) + 0x82), (s16)(FIELD(w, s32, 0x10) + 0x30));
        func_801CC974_ovl_087200(2, 10, func_801B577C_ovl_087200, 0x120, 0x14, 0x128, 0x1C, 0xA6, 0x14, 0x128, 0x44);
    }
}

void func_801CC034_ovl_087200(void) {
    s16 a, b, c, d;

    func_801C7CA0_ovl_087200(&a, &b, &c, &d);
    func_801CCA50_ovl_087200(0, 10, func_801B3B00_ovl_087200, a, b, c, d);
}

void func_801CC08C_ovl_087200(void) {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
    u8 *w = func_801CC410_ovl_087200(0);

    if (w != NULL) {
        func_801C7D78_ovl_087200(&a, &b, &c, &d);
        func_801CC6D4_ovl_087200(w, func_801B7F50_ovl_087200, func_801B74CC_ovl_087200, a, b, c, d);
    }
}

void func_801CC100_ovl_087200(void) {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
    u8 *w = func_801CC410_ovl_087200(0);

    if (w != NULL) {
        func_801C7CA0_ovl_087200(&a, &b, &c, &d);
        func_801CC72C_ovl_087200(w, func_801B3B00_ovl_087200, func_801B74CC_ovl_087200, a, b, c, d);
        func_801CC5B4_ovl_087200(w, a, b, c, d);
    }
}

void func_801CC190_ovl_087200(void) {
    u8 *w = func_801CC410_ovl_087200(0);
    s16 a, b, c, d;

    if (w != NULL) {
        func_801C7CA0_ovl_087200(&a, &b, &c, &d);
        func_801CC784_ovl_087200(w, a, b, c, d);
    }
}

/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_8016FEF4(s32);                         /* extern */
void func_801B10FC_ovl_087200();                    /* extern */
void func_801B1624_ovl_087200();                    /* extern */
void func_801B18FC_ovl_087200();                    /* extern */
s32 func_801CF070_ovl_087200();                     /* extern */
extern u8 D_801936E0;

void func_801CC1EC_ovl_087200(void)
{
  s16 option;
  s32 x;
  option = func_801CF070_ovl_087200() & 0xFF;
  x = 0xE8;
  if (option)
  {
    x = 0x128;
  }
  func_801CC974_ovl_087200(0x15U, 0xAU, func_801B10FC_ovl_087200, 0x60, -8, 0xE0, 0, 0x18, 0x18, (s16) x, 0x34);
  func_801CC974_ovl_087200(6U, 0xAU, func_801B1624_ovl_087200, 0x18, 0xD8, 0x20, 0xE0, 0x18, 0xC8, 0x6E, 0xE0);
  if ((D_801936E0 != 0) || (func_8016FEF4(0xB) != 0))
  {
    func_801CC974_ovl_087200(0x10U, 8U, func_801B18FC_ovl_087200, 0x128, 0xF0, 0x124, 0xF4, 0x114, 0xC8, 0x128, 0xE0);
  }
}

void func_801CC310_ovl_087200(void) {
    if (func_801CC410_ovl_087200(0x11) == NULL) {
        func_801CC974_ovl_087200(0x11, 8, func_801B1FE0_ovl_087200, 0x144, 0xC8, 0x148, 0xE0, 0xD0, 0xC8, 0x128, 0xE0);
    }
}

INCLUDE_RODATA("asm/nonmatchings/B48F0", D_801EFB10_ovl_087200);

INCLUDE_RODATA("asm/nonmatchings/B48F0", D_801EFB18_ovl_087200);

INCLUDE_RODATA("asm/nonmatchings/B48F0", D_801EFB1C_ovl_087200);

INCLUDE_RODATA("asm/nonmatchings/B48F0", D_801EFB20_ovl_087200);

INCLUDE_RODATA("asm/nonmatchings/B48F0", D_801EFB44_ovl_087200);
