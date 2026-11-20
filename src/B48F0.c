#include "common.h"

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
void func_801C67B0_ovl_087200(u8 sq);
void func_801B4AF4_ovl_087200();
void func_801B577C_ovl_087200();
void HFree(void *p);
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

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void func_801A4894_ovl_087200();                    /* extern */
extern s32 D_800E9C0A;

void func_801C7E90_ovl_087200(s32 a, s32 b, s32 c) {
    s16 var_t0;
    s16 var_v1;
    s32 temp_a1;
    s32 temp_a3;
    s32 temp_v0;
    s32 var_a3;
    s32 var_t2;
    u32 temp_v1;
    u32 var_t1;
    void (*var_t3)();

    temp_a3 = a & 0xFFFF0000;
    if ((((temp_a3 == 0x1C0000) | (temp_a3 == 0x1D0000)) != 0) || (var_t1 = 0x28, (temp_a3 == 0x1E0000))) {
        var_t3 = func_801A4894_ovl_087200;
        var_t1 = 0x38;
    } else {
        var_t3 = func_801A43F4_ovl_087200;
    }
    if (!(c & 0xFF) || !((FIELD(&D_800E9C0A, u8, 6) == 0) & (temp_a3 == 0x50000))) {
        temp_a1 = b & 0xFF;
        FIELD(D_80196AF8, s32, 0x10C8) = a;
        if (temp_a1 == 1) {
            var_t2 = 0xCB;
            var_a3 = 0xCF;
            var_t0 = 0xCF - var_t1;
            var_v1 = 0xCF;
        } else {
            var_t2 = 0x18;
            if (temp_a1 == 2) {
                var_t2 = 0x76;
                var_a3 = 0x7A;
                temp_v1 = var_t1 >> 1;
                var_t0 = 0x78 - temp_v1;
                var_v1 = temp_v1 + 0x78;
            } else {
                var_a3 = 0x1C;
                var_t0 = 0x18;
                var_v1 = var_t1 + 0x18;
            }
        }
        temp_v0 = func_801CC974_ovl_087200(0x100U, 0x12U, var_t3, 0x9C, (s16) var_t2, 0xA4, (s16) var_a3, 0x18, (s16) (s32) var_t0, 0x128, (s16) (s32) var_v1);
        FIELD(D_80196AF8, s32, 0x10CC) = temp_v0;
        func_801C0798_ovl_087200((s16) temp_v0, FIELD(D_80196AF8, s32, 0x10C8));
        func_801C18AC_ovl_087200(0xB, 0, 0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/B48F0", func_801C7E90_ovl_087200);
#endif

void func_801C7FF0_ovl_087200(s32 a, u8 b) {
    func_801C7E90_ovl_087200(a, b, 1);
}

void func_801C8010_ovl_087200(s32 a) {
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

void func_801C80A8_ovl_087200(s32 a) {
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

#ifdef NON_MATCHING
/* m2c draft, 38 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_801CF190_ovl_087200(u8 *);                 /* extern */
u8 func_801CF7F8_ovl_087200();                      /* extern */
extern s32 D_801939DC;

void func_801C9D4C_ovl_087200(void) {
    s16 temp_s0;
    s32 var_a0;
    s32 var_a1;

    temp_s0 = FIELD(D_80196AF8, s16, 0x122);
    switch (temp_s0) {                              /* irregular */
    case 0x0:
        bzero(D_80196AF8 + 0x1BEE, 0x1FE);
        FIELD(D_80196AF8, u8, 0x1DED) = func_801CF7F8_ovl_087200();
        if (D_80190F81 == 0) {
            FIELD(D_80196AF8, s16, 0x122) = 0x63;
            if ((FIELD(D_80196AF8, u8, 0x98) == 0) || (var_a1 = 0, (FIELD(D_80196AF8, u8, 0x99) == 1))) {
                var_a1 = 1;
            }
            var_a0 = 0x40009;
            goto block_29;
        }
        if (FIELD(D_80196AF8, u8, 0x1DED) == 0) {
            FIELD(D_80196AF8, s16, 0x122) = 0x63;
            if ((FIELD(D_80196AF8, u8, 0x98) == 0) || (var_a1 = 0, (FIELD(D_80196AF8, u8, 0x99) == 1))) {
                var_a1 = 1;
            }
            var_a0 = 0x4000E;
block_29:
            func_801C7E90_ovl_087200(var_a0, var_a1, 1);
            return;
        }
        FIELD(D_80196AF8, s16, 0x122) = (s16) ((u16) FIELD(D_80196AF8, s16, 0x122) + 1);
        return;
    case 0x1:
        if ((u8) D_80190F81 < (u8) FIELD(D_80196AF8, u8, 0x1DED)) {
            D_801939DC = func_801CF190_ovl_087200(D_80196AF8) & 0xFFFF;
            FIELD(D_80196AF8, s16, 0x122) = (s16) ((u16) FIELD(D_80196AF8, s16, 0x122) + 1);
            if ((FIELD(D_80196AF8, u8, 0x98) == 0) || (var_a1 = 0, (FIELD(D_80196AF8, u8, 0x99) == temp_s0))) {
                var_a1 = 1;
            }
            var_a0 = 0x4001A;
        } else {
            D_801939DC = func_801CF190_ovl_087200(D_80196AF8) & 0xFFFF;
            FIELD(D_80196AF8, s16, 0x122) = (s16) ((u16) FIELD(D_80196AF8, s16, 0x122) + 1);
            if ((FIELD(D_80196AF8, u8, 0x98) == 0) || (var_a1 = 0, (FIELD(D_80196AF8, u8, 0x99) == temp_s0))) {
                var_a1 = 1;
            }
            var_a0 = 0x40031;
        }
        goto block_29;
    case 0x2:
        if (func_801CC410_ovl_087200(0x100) == NULL) {
            FIELD(D_80196AF8, s16, 0x122) = 0x63;
            return;
        }
        return;
    case 0x63:
        func_801C8158_ovl_087200(D_80196AF8);
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/B48F0", func_801C9D4C_ovl_087200);
#endif

void func_801C9F44_ovl_087200(void) {
    if (func_801D8B58_ovl_087200()) {
        D_80196AF8[0xA0] |= 0x82;
        func_801C18AC_ovl_087200((-(FIELD(D_80196AF8, s16, 0x122) != 0) & 9) | 8, 0, 0);
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

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void func_801A7940_ovl_087200();                    /* extern */
void func_801A87F8_ovl_087200();                    /* extern */
extern s32 D_80193AC0;
extern s32 D_80196B00;

void func_801CA148_ovl_087200(void) {
    s32 temp_v0;
    s32 var_v0;
    u16 var_v1;
    u8 *temp_v0_2;
    void *temp_t0;

    FIELD(D_80196AF8, s8, 0xA1) = 1;
    temp_v0 = FIELD(((FIELD(D_80196AF8, s16, 0x1BDA) * 2) + D_80196AF8), u16, 0x1BEE) * 4;
    if ((u8) FIELD(&D_80196AF8[FIELD(D_80196AF8, u8, 0x9D)], u8, 0x1E00) >= 7U) {
        var_v1 = *(&D_80193AC0 + temp_v0);
        var_v0 = 0x1B0000;
    } else {
        var_v1 = *(&D_80196B00 + temp_v0);
        var_v0 = 0x130000;
    }
    temp_t0 = D_80196AF8 + ((func_801CC974_ovl_087200(0x400U, 0xAU, func_801A87F8_ovl_087200, 0x18, 0x16, 0x20, 0x1E, 0x18, 0x16, 0xB2, 0xB0) * 0x108) + 0x650);
    FIELD(temp_t0, u8, 0xE6) = (u8) (FIELD(temp_t0, u8, 0xE6) | 4);
    func_801CC974_ovl_087200(3U, 0xAU, func_801A7940_ovl_087200, 0x120, 0x18, 0x128, 0x20, 0xBC, 0x18, 0x128, 0xAE);
    temp_v0_2 = func_801CC410_ovl_087200(5);
    if (temp_v0_2 == NULL) {
        FIELD(D_80196AF8, s32, 0x10D0) = func_801CC974_ovl_087200(5U, 0xAU, func_801A43F4_ovl_087200, 0x9C, 0xD6, 0xA4, 0xDE, 0x18, 0xB6, 0x128, 0xDE);
    } else {
        HFree(FIELD(temp_v0_2, void *, 0xF4));
    }
    func_801C0798_ovl_087200(func_801CC3B8_ovl_087200(5), var_v1 | var_v0);
}
#else
INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CA148_ovl_087200);
#endif

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
u8 func_801CFA04_ovl_087200(s32);                   /* extern */

void func_801CA328_ovl_087200(void) {
    s16 temp_a0_2;
    s32 var_s0;
    u8 temp_a0;

    FIELD(D_80196AF8, u8, 0x9D) = 0U;
    var_s0 = 0;
    FIELD(D_80196AF8, u8, 0x1DFF) = 0U;
    do {
        FIELD(&D_80196AF8[var_s0], s8, 0x1E00) = 0;
        FIELD(&D_80196AF8[var_s0], s8, 0x1DF6) = 0;
        FIELD(&D_80196AF8[var_s0], s8, 0x1DEE) = 0;
        if (func_801CFA04_ovl_087200(var_s0 & 0xFFFF) & 0xFFFF) {
            temp_a0 = FIELD(D_80196AF8, u8, 0x1DFF);
            FIELD(D_80196AF8, u8, 0x1DFF) = (u8) (temp_a0 + 1);
            FIELD(&D_80196AF8[temp_a0], s8, 0x1E00) = (s8) (var_s0 + 1);
        }
        var_s0 += 1;
    } while (var_s0 < 8);
    FIELD(D_80196AF8, s8, 0x1DFE) = 3;
    FIELD(D_80196AF8, s8, 0x9B) = 0;
    FIELD(D_80196AF8, s8, 0x9A) = 0;
    FIELD(D_80196AF8, u8, 0x1DED) = func_801CFA04_ovl_087200((FIELD(&D_80196AF8[FIELD(D_80196AF8, u8, 0x9D)], u8, 0x1E00) - 1) & 0xFFFF);
    FIELD(D_80196AF8, s16, 0x1BDA) = 0;
    FIELD(D_80196AF8, s16, 0x1BDC) = 0;
    FIELD(D_80196AF8, s16, 0x1BDE) = 8;
    temp_a0_2 = FIELD(D_80196AF8, u8, 0x1DED) - 1;
    FIELD(D_80196AF8, s16, 0x1BE0) = temp_a0_2;
    func_801CA148_ovl_087200(temp_a0_2);
}
#else
INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CA328_ovl_087200);
#endif

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CA44C_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CA588_ovl_087200);

/* Clears grid row r: frees its units (members lose their 0x20 flag) and resets the row */
#ifdef NON_MATCHING
/* Only one register pair differs: in the member loop the original loads the member id into v0 (the address register) and the state pointer into v1. */
void func_801CA704_ovl_087200(u16 r) {
    u8 *row = D_80196AF8 + (r * 14 + 0x10D4);
    s32 c;
    s32 k;
    u8 u;
    u8 m;
    u8 *rec;

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
                (D_80196AF8 + m * 2)[0x1872] &= ~0x20;
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
#else
INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CA704_ovl_087200);
#endif

/* Removes the unit in grid cell (r, c) of the organize screen: clears its slot record, shifts the
 * cell behind it forward for columns 1-2, and drops its members' 0x20 flag */
#ifdef NON_MATCHING
/* The logic matches. The original swaps a2/a3 (the 0xFF constant against the record offset) and uses base + index order on the 0x117E and 0x1872 adds. */
void func_801CA80C_ovl_087200(u16 r, u16 c) {
    u8 *row = D_80196AF8 + 0x10D4 + r * 14;
    u8 *cell = row + c;
    u8 u = cell[2];
    s32 off;
    s32 k;
    u8 m;
    u8 t;

    if (u == 0xFF) {
        return;
    }
    off = u * 54;
    D_80196AF8[off + 0x117D] = 0;
    D_80196AF8[off + 0x117E] = 0xFF;
    cell[2] = 0xFF;
    FIELD(D_80196AF8, s32, 0x2C0)++;
    if ((u16)(c - 1) < 2) {
        t = cell[4];
        cell[4] = 0xFF;
        cell[2] = t;
    }
    row[8]--;
    for (k = 0; k < 9; k++) {
        m = (D_80196AF8 + off + k)[0x1180];
        if (m != 0xFF) {
            (D_80196AF8 + m * 2)[0x1872] &= ~0x20;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CA80C_ovl_087200);
#endif

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

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CAB68_ovl_087200);

#ifdef NON_MATCHING
/* store order/scheduling of the release block differs */
void func_801CAD90_ovl_087200(u16 id) {
    if (id != 0xFF) {
        if (id >= 100) {
            u16 r = func_801CBC98_ovl_087200(id);

            D_80190EBC[id] = 0;
            D_80191010[id] = 0;
            D_80190F81 += r;
            FIELD(D_80196AF8, u8, 0x1872 + id * 2) = 0;
        }
        if (FIELD(D_80196AF8, u8, 0x1872 + id * 2) & 8) {
            FIELD(D_80196AF8, s32, 0x5D4)++;
        }
        FIELD(D_80196AF8, u8, 0x1872 + id * 2) = 0;
        func_801CE074_ovl_087200();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CAD90_ovl_087200);
#endif

#ifdef NON_MATCHING
/* addu operand order (3 instructions) */
void func_801CAE4C_ovl_087200(u16 sq) {
    s32 i;
    u8 m;

    for (i = 0; i < 9; i++) {
        m = (D_80196AF8 + sq * 0x36)[i + 0x1180];
        if (m != 0xFF) {
            D_80196AF8[m * 2 + 0x1872] &= 0xFB;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CAE4C_ovl_087200);
#endif

void func_801CAEB0_ovl_087200(u16 sq, u16 v) {
    OrgSquad *q = &((OrgSquad *)(D_80196AF8 + 0x117C))[sq];

    if (q->b[4 + v] != 0xFF) {
        q->b[3] = v;
    }
    q->b[0x1D] = func_801D06F4_ovl_087200(sq);
}

#ifdef NON_MATCHING
/* m2c draft, 20 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void func_801CAF18_ovl_087200(s32 arg0, u8 arg1, s32 arg2, u8 arg3) {
    s32 var_a2;
    s32 var_a2_2;
    s32 var_t2;
    u32 temp_a3;
    u32 temp_t0;
    u8 *var_t0;
    u8 *var_t1;
    u8 temp_a1;
    u8 temp_v0;
    u8 temp_v1;
    u8 temp_v1_3;
    void *temp_a2;
    void *temp_a2_2;
    void *temp_v1_2;
    void *temp_v1_4;

    var_t2 = 0;
    temp_t0 = arg1 & 0xFFFF;
    if (temp_t0 >= 9U) {
        var_t1 = &FIELD(&D_80196AF8[temp_t0], u8, 0x1A21);
    } else {
        temp_a2 = D_80196AF8 + (((arg0 & 0xFFFF) * 0x36) + 0x117C);
        var_t1 = temp_a2 + (temp_t0 + 4);
        if (FIELD(temp_a2, u8, 3) == temp_t0) {
            FIELD(temp_a2, u8, 3) = arg3;
            var_t2 = 1;
        }
    }
    temp_a3 = arg3 & 0xFFFF;
    if (temp_a3 >= 9U) {
        var_t0 = &FIELD(&D_80196AF8[temp_a3], u8, 0x1A21);
    } else {
        temp_a2_2 = D_80196AF8 + (((arg2 & 0xFFFF) * 0x36) + 0x117C);
        var_t0 = temp_a2_2 + (temp_a3 + 4);
        if (!(var_t2 & 0xFF) && (FIELD(temp_a2_2, u8, 3) == temp_a3)) {
            FIELD(temp_a2_2, u8, 3) = arg1;
        }
    }
    temp_a1 = *var_t0;
    if ((temp_a1 & 0xFF) == 0xFF) {
        *var_t0 = *var_t1;
        *var_t1 = 0xFF;
    } else {
        temp_v0 = *var_t1;
        *var_t1 = temp_a1;
        *var_t0 = temp_v0;
    }
    var_a2 = 0;
    do {
        temp_v1 = FIELD((D_80196AF8 + ((arg0 & 0xFFFF) * 0x36) + var_a2), u8, 0x1180);
        var_a2 += 1;
        if (temp_v1 != 0xFF) {
            temp_v1_2 = D_80196AF8 + (temp_v1 * 2);
            FIELD(temp_v1_2, u8, 0x1872) = (u8) (FIELD(temp_v1_2, u8, 0x1872) & 0xFB);
        }
    } while (var_a2 < 9);
    var_a2_2 = 0;
    do {
        temp_v1_3 = FIELD((D_80196AF8 + ((arg2 & 0xFFFF) * 0x36) + var_a2_2), u8, 0x1180);
        var_a2_2 += 1;
        if (temp_v1_3 != 0xFF) {
            temp_v1_4 = D_80196AF8 + (temp_v1_3 * 2);
            FIELD(temp_v1_4, u8, 0x1872) = (u8) (FIELD(temp_v1_4, u8, 0x1872) & 0xFB);
        }
    } while (var_a2_2 < 9);
    func_801C67B0_ovl_087200(arg0 & 0xFFFF);
    func_801C67B0_ovl_087200(arg2 & 0xFFFF);
}
#else
INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CAF18_ovl_087200);
#endif

#ifdef NON_MATCHING
/* m2c draft, 13 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void func_801CB0FC_ovl_087200(s32 arg0, u8 arg1, u8 arg2) {
    s32 temp_v0;
    s32 var_a2;
    u16 temp_s0;
    u8 temp_t0;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    void *temp_a3;
    void *temp_s1;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v1_4;

    temp_s1 = D_80196AF8 + (((arg0 & 0xFFFF) * 0x36) + 0x117C);
    temp_a3 = temp_s1 + (arg2 & 0xFFFF);
    temp_t0 = FIELD(temp_a3, u8, 4);
    temp_v0 = arg1 & 0xFFFF;
    if ((temp_t0 & 0xFF) == 0xFF) {
        temp_v0_2 = temp_s1 + temp_v0;
        FIELD(temp_a3, u8, 4) = (u8) FIELD(temp_v0_2, u8, 4);
        FIELD(temp_v0_2, u8, 4) = 0xFFU;
    } else {
        temp_v0_3 = temp_s1 + temp_v0;
        temp_v1 = FIELD(temp_v0_3, u8, 4);
        FIELD(temp_v0_3, u8, 4) = temp_t0;
        FIELD(temp_a3, u8, 4) = temp_v1;
    }
    temp_v1_2 = FIELD(temp_s1, u8, 3);
    if (temp_v1_2 == (arg1 & 0xFFFF)) {
        FIELD(temp_s1, u8, 3) = arg2;
    } else if (temp_v1_2 == (arg2 & 0xFFFF)) {
        FIELD(temp_s1, u8, 3) = arg1;
    }
    var_a2 = 0;
    do {
        temp_v1_3 = FIELD((D_80196AF8 + ((arg0 & 0xFFFF) * 0x36) + var_a2), u8, 0x1180);
        var_a2 += 1;
        if (temp_v1_3 != 0xFF) {
            temp_v1_4 = D_80196AF8 + (temp_v1_3 * 2);
            FIELD(temp_v1_4, u8, 0x1872) = (u8) (FIELD(temp_v1_4, u8, 0x1872) & 0xFB);
        }
        temp_s0 = arg0 & 0xFFFF;
    } while (var_a2 < 9);
    FIELD(temp_s1, u8, 0x1D) = func_801D06F4_ovl_087200(temp_s0);
    func_801C67B0_ovl_087200((u8) temp_s0);
}
#else
INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CB0FC_ovl_087200);
#endif

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CB21C_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CB8A0_ovl_087200);

void func_801CBA2C_ovl_087200(u16 i) {
    _bcopy(D_80196AF8 + 0x117C + i * 0x36, D_80196AF8 + 0x1806, 0x36);
}

void func_801CBA74_ovl_087200(u16 i) {
    _bcopy(D_80196AF8 + 0x1806, D_80196AF8 + 0x117C + i * 0x36, 0x36);
}

/* Clears squad record sq (leader, members, positions) */
#ifdef NON_MATCHING
/* first loop: original walks a byte pointer down from q+8 */
void func_801CBABC_ovl_087200(u8 sq) {
    u8 *q = D_80196AF8 + (sq * 0x36 + 0x117C);
    s32 k;

    q[1] = 0;
    q[2] = 0xFF;
    q[3] = 0xFF;
    q[0xD] = 0xFF;
    q[0x20] = 0;
    q[0x1E] = 0;
    q[0x1D] = 0;
    for (k = 8; k >= 0; k--) {
        q[4 + k] = 0xFF;
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
  short new_var;
  s32 var_v1;
  new_var = func_801CF070_ovl_087200() & 0xFF;
  var_v1 = 0xE8;
  if (new_var)
  {
    var_v1 = 0x128;
  }
  func_801CC974_ovl_087200(0x15U, 0xAU, func_801B10FC_ovl_087200, 0x60, -8, 0xE0, 0, 0x18, 0x18, (s16) var_v1, 0x34);
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
