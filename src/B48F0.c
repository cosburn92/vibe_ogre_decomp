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

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801C80A8_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801C8158_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801C84BC_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801C97A0_ovl_087200);

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

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CA9FC_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CAA64_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CAB68_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CAD90_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CAE4C_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CAEB0_ovl_087200);

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

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CBABC_ovl_087200);

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

#ifdef NON_MATCHING
/* Constant/load order differs at the start. */
u8 func_801CBBA0_ovl_087200(void) {
    s32 i = 0;
    u8 *st;

    for (st = D_80196AF8; i < 30; i++) {
        if (st[0x117F] == 0xFF) {
            break;
        }
        st += 0x36;
    }
    return i;
}
#else
INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CBBA0_ovl_087200);
#endif

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CBBD4_ovl_087200);

u8 func_801CBC64_ovl_087200(void) {
    s32 i;

    for (i = 0; i < 120; i++) {
        if (D_80190F84[i] == 0) {
            break;
        }
    }
    return i + 100;
}

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CBC98_ovl_087200);

void func_801CBD0C_ovl_087200(s16 a, s16 b, u8 f) {
    u8 *st = D_80196AF8;

    st[0x180] = f;
    if (f) {
        FIELD(st, s16, 0x17C) = a;
        FIELD(st, s16, 0x17E) = b;
    }
}

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CBD34_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CBE08_ovl_087200);

void func_801CBEDC_ovl_087200(void) {
    func_801CC684_ovl_087200(func_801CC410_ovl_087200(0), func_801B6394_ovl_087200, 0x18, 0x14, 0x128, 0x8A);
}

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CBF20_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CBF8C_ovl_087200);

void func_801CC034_ovl_087200(void) {
    s16 a, b, c, d;

    func_801C7CA0_ovl_087200(&a, &b, &c, &d);
    func_801CCA50_ovl_087200(0, 10, func_801B3B00_ovl_087200, a, b, c, d);
}

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CC08C_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CC100_ovl_087200);

void func_801CC190_ovl_087200(void) {
    u8 *w = func_801CC410_ovl_087200(0);
    s16 a, b, c, d;

    if (w != NULL) {
        func_801C7CA0_ovl_087200(&a, &b, &c, &d);
        func_801CC784_ovl_087200(w, a, b, c, d);
    }
}

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CC1EC_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B48F0", func_801CC310_ovl_087200);

INCLUDE_RODATA("asm/nonmatchings/B48F0", D_801EFB10_ovl_087200);

INCLUDE_RODATA("asm/nonmatchings/B48F0", D_801EFB18_ovl_087200);

INCLUDE_RODATA("asm/nonmatchings/B48F0", D_801EFB1C_ovl_087200);

INCLUDE_RODATA("asm/nonmatchings/B48F0", D_801EFB20_ovl_087200);

INCLUDE_RODATA("asm/nonmatchings/B48F0", D_801EFB44_ovl_087200);
