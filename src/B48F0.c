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
void func_801C7CA0_ovl_087200(s16 *a, s16 *b, s16 *c, s16 *d);
void func_801CCA50_ovl_087200(s32 a, s32 b, void (*f)(), s32 c, s32 d, s32 e, s32 g);
void func_801CC784_ovl_087200(u8 *w, s32 a, s32 b, s32 c, s32 d);





typedef struct {
    u8 b[0x36];
} OrgSquad; /* organize-screen squad record, 30 of them at state +0x117C */
u8 func_801D06F4_ovl_087200(u16 sq);
s32 func_801CC974_ovl_087200(s32 id, s32 a, void (*f)(), s32 b, s32 c, s32 d, s32 e, s32 g, s32 h, s32 i, s32 j);
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
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801C7E90_ovl_087200);

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

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801C9D4C_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801C9F44_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CA030_ovl_087200);

void func_801CA110_ovl_087200(void) {
    func_801CC7D4_ovl_087200(0x400);
    func_801CC7D4_ovl_087200(3);
    func_801CC7D4_ovl_087200(5);
    D_80196AF8[0xA1] = 0;
}

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CA148_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CA328_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CA44C_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CA588_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CA704_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CA80C_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CA900_ovl_087200);

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

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CAA64_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CAB68_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CAD90_ovl_087200);

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

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CAF18_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CB0FC_ovl_087200);

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

#ifdef NON_MATCHING
/* Constant/load order differs at the start. */
void func_801CBB54_ovl_087200(void) {
    u8 *st = D_80196AF8;
    u8 *p = st + 0x1164;
    s32 i;

    st[0x1167] = 1;
    st[0x1169] = 0;
    st[0x1168] = 0;
    st[0x116D] = 0xFF;
    st[0x116B] = 0;
    st[0x116C] = 0;
    for (i = 4; i >= 0; i--) {
        p[2] = 0xFF;
        p--;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CBB54_ovl_087200);
#endif

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

#ifdef NON_MATCHING
/* argument evaluation order of the window rect differs */
void func_801CBD34_ovl_087200(u8 *w) {
    s16 i = func_801CC974_ovl_087200(4, 0x12, func_801AA114_ovl_087200, (s16)(FIELD(w, s32, 0x24) - 0xC), (s16)(FIELD(w, s32, 0x28) - 8),
                                     (s16)(FIELD(w, s32, 0x24) - 4), (s16)(FIELD(w, s32, 0x28) + 8), (s16)(FIELD(w, s32, 0x24) - 0x54),
                                     (s16)(FIELD(w, s32, 0x28) - 0x24), (s16)(FIELD(w, s32, 0x24) - 4), (s16)(FIELD(w, s32, 0x28) + 0x10));

    D_80196AF8[0x737 + i * 0x108] = w[0xE7];
}
#else
INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CBD34_ovl_087200);
#endif

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CBE08_ovl_087200);

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

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CC1EC_ovl_087200);

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
