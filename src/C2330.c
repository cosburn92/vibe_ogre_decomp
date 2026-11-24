#include "common.h"

/* C2330 */

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern u8 *D_80196AF8;
extern u8 D_801EF474_ovl_087200[];
extern s8 D_801EF480_ovl_087200[];
u8 func_801D6508_ovl_087200(void);
extern u8 D_801EF487_ovl_087200[];
/* --- end decls --- */

/* Whether formation cell pos of squad sq has an occupied neighbour (by the D_801EF474 direction
 * mask) other than member m */
u8 func_801D58D0_ovl_087200(u16 sq, u8 m, u8 pos) {
    s32 n = 0;

    if (pos < 9) {
        s32 k;
        u8 mask = D_801EF474_ovl_087200[pos];
        u8 *q = D_80196AF8 + (sq * 0x36 + 0x117C);

        for (k = 0; k < 8; k++) {
            if ((mask >> k) & 1) {
                u8 c = (q + (pos + D_801EF480_ovl_087200[k]))[4];

                if (c != 0xFF && c != m) {
                    n++;
                    break;
                }
            }
        }
    }
    return n;
}

/* As func_801D58D0 for the organize screen's current squad (0x18C) and cell (0x19B) */
u8 func_801D597C_ovl_087200(u8 m) {
    u8 *st = D_80196AF8;
    s32 n = 0;
    u8 pos = st[0x19B];
    u16 sq = FIELD(st, u16, 0x18C);

    if (pos < 9) {
        s32 k;
        u8 *q = st + (sq * 0x36 + 0x117C);
        u8 mask = D_801EF474_ovl_087200[pos];

        for (k = 0; k < 8; k++) {
            if ((mask >> k) & 1) {
                u8 c = (q + (pos + D_801EF480_ovl_087200[k]))[4];

                if ((c != 0xFF) & (c != m)) {
                    n++;
                    break;
                }
            }
        }
    }
    return n;
}

u8 func_801D5A2C_ovl_087200(u8 m) {
    u8 *st = D_80196AF8;
    s32 n = 0;
    s32 k;
    u8 *q;
    s32 pos;
    u8 mask;
    u8 c;

    q = st + (FIELD(st, u16, 0x18C) * 0x36 + 0x117C);
    pos = FIELD(st, u16, 0x19C);
    mask = D_801EF474_ovl_087200[pos];
    for (k = 0; k < 8; k++) {
        if ((mask >> k) & 1) {
            c = (q + (pos + D_801EF480_ovl_087200[k]))[4];
            if (c != 0xFF && c != m) {
                n++;
                break;
            }
        }
    }
    return n;
}

u8 func_8016DE1C(u8 cls, u8 base);
extern u8 D_80193BC0[][0x38];

/* Whether formation cell pos of squad sq has a neighbour (other than member m) whose class has
 * kind 2 */
u8 func_801D5AD0_ovl_087200(u16 sq, u8 m, u8 pos) {
    s32 n = 0;
    s32 k;
    u8 *q = D_80196AF8 + (sq * 0x36 + 0x117C);

    for (k = 0; k < 8; k++) {
        if ((D_801EF474_ovl_087200[pos] >> k) & 1) {
            u8 c = (q + (pos + D_801EF480_ovl_087200[k]))[4];

            if ((c != 0xFF) & (c != m)) {
                u8 *u = D_80193BC0[0];

                if (c < 100) {
                    u = D_80193BC0[c];
                }
                if (func_8016DE1C(u[0x11], u[0x12]) == 2) {
                    n++;
                    break;
                }
            }
        }
    }
    return n;
}

/* As func_801D5AD0 for the organize screen's current squad (0x18C) and cell (0x19B) */
u8 func_801D5BF0_ovl_087200(u8 m) {
    s32 n = 0;
    s32 k;
    u8 pos = D_80196AF8[0x19B];
    u8 *q = D_80196AF8 + (FIELD(D_80196AF8, u16, 0x18C) * 0x36 + 0x117C);

    for (k = 0; k < 8; k++) {
        if ((D_801EF474_ovl_087200[pos] >> k) & 1) {
            u8 c = (q + (pos + D_801EF480_ovl_087200[k]))[4];

            if ((c != 0xFF) & (c != m)) {
                u8 *u = D_80193BC0[0];

                if (c < 100) {
                    u = D_80193BC0[c];
                }
                if (func_8016DE1C(u[0x11], u[0x12]) == 2) {
                    n++;
                    break;
                }
            }
        }
    }
    return n;
}

s32 func_801D5D10_ovl_087200(u8 *out) {
    u8 r;
    u8 none;

    *out = 0;
    r = func_801D6508_ovl_087200();
    none = r == 0;
    if (!none) {
        *out = D_801EF487_ovl_087200[r];
    }
    return none;
}

INCLUDE_ASM("asm/nonmatchings/C2330", func_801D5D5C_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/C2330", func_801D6508_ovl_087200);

u16 func_801CF320_ovl_087200(u8 id);
u16 func_801CF2F0_ovl_087200(u8 id);

/* 1 if items a and b can be combined: kinds 1/2 sharing a kind bit (same item or a has a
 * sub-kind), or both of kind 8 with sub-kind 5 */
#ifdef NON_MATCHING
/* 61/69: the original's switch tree splits at 5 (range 1-2 left, 32 and 8 right) and counts r up with bnezl; ours roots at 8 */
u8 func_801D6D8C_ovl_087200(u8 a, u8 b) {
    s32 r = 0;
    u16 ka = func_801CF320_ovl_087200(a);
    u16 kb = func_801CF320_ovl_087200(b);

    switch (ka) {
        case 1:
        case 2:
            if (a == b || func_801CF2F0_ovl_087200(a) != 0) {
                if (ka & (ka & kb)) {
                    r++;
                }
            }
            break;
        case 8:
            if (func_801CF2F0_ovl_087200(a) == 5 && func_801CF2F0_ovl_087200(b) == 5) {
                r = 1;
            }
            break;
        case 32:
            break;
    }
    return (u8)r;
}
#else
INCLUDE_ASM("asm/nonmatchings/C2330", func_801D6D8C_ovl_087200);
#endif

INCLUDE_ASM("asm/nonmatchings/C2330", func_801D6EA0_ovl_087200);

extern u8 D_80193BF8[][0x38]; /* player characters from index 1 */
extern u8 D_80196A76[];       /* class unlock bits */
extern u16 D_801EF2CC_ovl_087200[]; /* class list, 0xFFFF-terminated */
extern u8 D_801EF3B0_ovl_087200[];  /* bit masks 1 << n */
extern u8 D_801EF3B8_ovl_087200[];  /* class -> unlock class (0: use base class) */
u8 func_801D6EA0_ovl_087200(u8 who, u8 cls);

/* Rebuilds the class unlock bits from the characters' classes, then from func_801D6EA0 for every
 * listed class still locked */
#ifdef NON_MATCHING
/* 102/102 instructions, 53 words differ: the character table is walked by pointer and k / 8 is a signed division in the original */
void func_801D734C_ovl_087200(void) {
    s32 i;
    s32 c;
    u8 k;
    u8 cls;
    u16 *l;

    for (i = 1; i < 100; i++) {
        cls = D_80193BF8[i - 1][0x11];
        k = D_801EF3B8_ovl_087200[cls];
        if (k == 0) {
            k = D_80193BF8[i - 1][0x12];
        }
        if ((cls != 0) & (k <= 80)) {
            if (!(D_801EF3B0_ovl_087200[k % 8] & D_80196A76[k / 8])) {
                D_80196A76[k / 8] |= D_801EF3B0_ovl_087200[k % 8];
            }
        }
    }
    l = D_801EF2CC_ovl_087200;
    c = 0;
    do {
        if (!(D_801EF3B0_ovl_087200[c % 8] & D_80196A76[c / 8])) {
            for (i = 1; i < 99; i++) {
                if (func_801D6EA0_ovl_087200(i, c)) {
                    D_80196A76[c / 8] |= D_801EF3B0_ovl_087200[c % 8];
                }
            }
        }
        c++;
        l++;
    } while (*l != 0xFFFF);
}
#else
INCLUDE_ASM("asm/nonmatchings/C2330", func_801D734C_ovl_087200);
#endif
