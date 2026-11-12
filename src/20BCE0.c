#include "common.h"

typedef struct {
    /* 0x00 */ u8 unk00[0x36];
    /* 0x36 */ u16 items[4];
    /* 0x3E */ u8 unk3E[2];
    /* 0x40 */ u32 flags;
    /* 0x44 */ u8 unk44[4];
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 cls;
    /* 0x50 */ u8 unk50[4];
    /* 0x54 */ s32 unk54;
} BattleUnit;

typedef struct {
    s32 (*f0)(void);
    void (*f1)(void);
    void (*f2)(void);
    void (*f3)(s16);
    void (*f4)(s16);
} BattleCallbacks;

extern BattleCallbacks *D_801D0810_ovl_1F0A30;
extern BattleCallbacks D_801CFC74_ovl_1F0A30;
extern u8 D_801CFC70_ovl_1F0A30;
extern u8 D_801976D8;
extern u16 D_80197B60;
extern u8 D_80197B62;
extern struct { u8 b[12]; } D_801976DC[];
extern u8 D_800E9C0A[];
extern u8 *D_801CE8BC_ovl_1F0A30;
extern void *D_801D0824_ovl_1F0A30;
u8 func_8016DE1C(u8 a, u8 b);
u16 func_8016FA34(u16 a, u16 b, u16 c, u16 d);
s32 func_801C8B84_ovl_1F0A30(BattleUnit *u);
void HFree(void *p);

extern u8 D_801CFC8C_ovl_1F0A30[];



void func_801C8850_ovl_1F0A30(void) {
    D_801D0810_ovl_1F0A30 = &D_801CFC74_ovl_1F0A30;
}

s32 func_801C8864_ovl_1F0A30(void) {
    if (D_801D0810_ovl_1F0A30->f0 != NULL) {
        return D_801D0810_ovl_1F0A30->f0();
    }
    return 1;
}

void func_801C889C_ovl_1F0A30(void) {
    if (D_801D0810_ovl_1F0A30->f1 != NULL) {
        D_801D0810_ovl_1F0A30->f1();
    }
}

void func_801C88CC_ovl_1F0A30(void) {
    if (D_801D0810_ovl_1F0A30->f2 != NULL) {
        D_801D0810_ovl_1F0A30->f2();
    }
}

void func_801C88FC_ovl_1F0A30(s16 a) {
    if (D_801D0810_ovl_1F0A30->f3 != NULL) {
        D_801D0810_ovl_1F0A30->f3(a);
    } else {
        D_801CFC70_ovl_1F0A30 = 0;
    }
}

void func_801C893C_ovl_1F0A30(s16 a) {
    if (D_801D0810_ovl_1F0A30->f4 != NULL) {
        D_801D0810_ovl_1F0A30->f4(a);
    }
}

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801C896C_ovl_1F0A30);

s32 func_801C8AA4_ovl_1F0A30(s32 a) {
    return (a - 1) * 38;
}

s32 func_801C8AC0_ovl_1F0A30(s32 a) {
    return (a - 4) * 38;
}

u8 func_801C8ADC_ovl_1F0A30(void) {
    return D_801976D8 & 0x40;
}

u8 func_801C8AEC_ovl_1F0A30(void) {
    return D_801976D8 & 8;
}

u16 func_801C8AFC_ovl_1F0A30(void) {
    return D_80197B60;
}

u8 func_801C8B08_ovl_1F0A30(void) {
    return D_80197B62;
}

u8 func_801C8B14_ovl_1F0A30(BattleUnit *u) {
    u8 *p;

    if (u == NULL) {
        return 0;
    }
    p = func_801C8B84_ovl_1F0A30(u) ? D_801976DC[0].b : D_801976DC[1].b;
    return p[1] & 2;
}

s32 func_801C8B54_ovl_1F0A30(void) {
    return D_800E9C0A[8] == 1;
}

s32 func_801C8B68_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u->flags >> 8) & 1;
}

s32 func_801C8B84_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return ((u->flags >> 8) ^ 1) & 1;
}

s32 func_801C8BA4_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u->flags >> 10) & 1;
}

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801C8BC0_ovl_1F0A30);

s32 func_801C8C3C_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u->flags >> 12) & 1;
}

s32 func_801C8C58_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u->flags >> 9) & 1;
}

s32 func_801C8C74_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return u->cls == 1;
}

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801C8C90_ovl_1F0A30);

s32 func_801C8CD4_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u32)(u->cls - 0x47) < 2;
}

s32 func_801C8CF0_ovl_1F0A30(s32 c) {
    s32 r = 0;

    if ((u32)(c - 0x2D) < 2 || c == 0x2F || c == 0x30) {
        r = 1;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801C8D24_ovl_1F0A30);

s32 func_801C8D68_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u32)(u->cls - 2) < 0x22;
}

#ifdef NON_MATCHING
/* The original tests with branches (bnez / bne) rather than set-compares; GCC merges these. */
/* Young Dragon..Tiamat (56-68) or Death Bahamut (164). */
s32 IsDragon(BattleUnit *u) {
    s32 c;

    if (u == NULL) {
        return 0;
    }
    c = u->cls;
    return (u32)(c - 0x38) < 13 || c == 0xA4;
}
#else
INCLUDE_ASM("asm/nonmatchings/20BCE0", IsDragon);
#endif

#ifdef NON_MATCHING
/* The original tests with branches (bnez / bne) rather than set-compares; GCC merges these. */
s32 func_801C8DBC_ovl_1F0A30(BattleUnit *u) {
    s32 c;
    s32 r;

    if (u == NULL) {
        return 0;
    }
    c = u->unk48;
    r = 0;
    if ((u32)(c - 0x87) < 2 || c == 0xA1) {
        r = 1;
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801C8DBC_ovl_1F0A30);
#endif

s32 func_801C8DF4_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return func_8016DE1C(((u8 *)u)[0x4B], ((u8 *)u)[0x4F]) == 2;
}

s32 func_801C8E30_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 1;
    }
    return u->flags & 1;
}

s32 func_801C8E48_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u->flags >> 5) & 1;
}

s32 func_801C8E64_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u->flags >> 3) & 1;
}

s32 func_801C8E80_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u->flags >> 2) & 1;
}

s32 func_801C8E9C_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u->flags >> 1) & 1;
}

s32 func_801C8EB8_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u->flags >> 4) & 1;
}

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801C8ED4_ovl_1F0A30);

s32 func_801C8F18_ovl_1F0A30(s32 a) {
    return a == 12;
}

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801C8F24_ovl_1F0A30);

u16 func_801C8FB8_ovl_1F0A30(BattleUnit *u) {
    return func_8016FA34(u->items[0], u->items[1], u->items[2], u->items[3]);
}

BattleUnit *func_801C8FE8_ovl_1F0A30(u32 i) {
    u8 *base;
    s32 off;

    if (i < 20) {
        base = D_801CE8BC_ovl_1F0A30;
        off = i * 0xF8;
        if (*(s32 *)(base + off + 0x20C) != 0) {
            return (BattleUnit *)(base + (off + 0x1C4));
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801C9028_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801C9234_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801C92F8_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801C9380_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801C940C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801C9478_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801C95D8_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801C96D4_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801C974C_ovl_1F0A30);

u8 func_801C9FA4_ovl_1F0A30(s32 idx) {
    return D_801CFC8C_ovl_1F0A30[idx];
}

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801C9FB4_ovl_1F0A30);

s32 func_801CA000_ovl_1F0A30(s32 a, s32 b) {
    s32 q;

    q = a / 3;
    if (b == 3) {
        return a;
    } else {
        return q * b;
    }
}

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CA038_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CA100_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CA1C4_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CA268_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CA29C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CA2E0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CA384_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CA3E0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CA534_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CA5A0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CA680_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CBC2C_ovl_1F0A30);

void func_801CBD48_ovl_1F0A30(void) {
    HFree(D_801D0824_ovl_1F0A30);
}

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CBD6C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CBE18_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CBF44_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CC124_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CC234_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CC37C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CC44C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CC51C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CC574_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CC7EC_ovl_1F0A30);

INCLUDE_RODATA("asm/nonmatchings/20BCE0", D_801D0640_ovl_1F0A30);
