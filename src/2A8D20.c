#include "common.h"

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))

extern u8 *D_8022A974;
extern u8 *D_8022A978;
extern u8 D_8022A980;
void HFree(void *p);
void func_80227B80(void);



void func_8023BDF8_ovl_2A8D20();

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_802395C0_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023965C_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_802396E4_ovl_2A8D20);

/* Swaps the objects in slots a and b, updating their back-references (+0xE4). */
void func_8023977C_ovl_2A8D20(u8 a, u8 b) {
    u8 *ctx = D_8022A974;
    u8 *pa = FIELD(ctx + a * 4, u8 *, 0x18);
    u8 *pb = FIELD(ctx + b * 4, u8 *, 0x18);

    FIELD(ctx + a * 4, u8 *, 0x18) = pb;
    FIELD(ctx + b * 4, u8 *, 0x18) = pa;
    if (pa != NULL) {
        FIELD(pa, s32, 0xE4) = b;
    }
    if (pb != NULL) {
        FIELD(pb, s32, 0xE4) = a;
    }
}

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_802397C4_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023998C_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_80239A84_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_80239AF8_ovl_2A8D20);

s32 func_80239B68_ovl_2A8D20(void) {
    s16 v = FIELD(FIELD(D_8022A974, u8 *, 0x19F0), s16, 0x48);
    s32 r = 0;

    if (v != 0) {
        r = v;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_80239B88_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_80239C04_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023A0FC_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023A164_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023A270_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023A370_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023AA8C_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023AC50_ovl_2A8D20);

s32 func_8023AEA8_ovl_2A8D20(u8 *p) {
    s32 c = FIELD(p, s32, 0xE8);
    s32 r;

    if ((u32)(c - 0x51) < 3) {
        r = 1;
    } else {
        r = c == 0xA3;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023AECC_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023B428_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023B494_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023B500_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023B998_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023BB48_ovl_2A8D20);

s32 func_8023BD7C_ovl_2A8D20(void) {
    s16 v = FIELD(FIELD(D_8022A974, u8 *, 0x19F0), s16, 0x48);
    s32 r = 0;

    if (v != 0) {
        r = v;
    }
    return r;
}

void func_8023BD9C_ovl_2A8D20(u8 v) {
    D_8022A980 = v;
}

void func_8023BDA8_ovl_2A8D20(s32 f) {
    if (f == 0) {
        D_8022A980 = 0xD7;
    } else {
        D_8022A980 = 0;
        func_80227B80();
    }
}

void func_8023BDDC_ovl_2A8D20(void) {
    func_8023BDF8_ovl_2A8D20();
}

#ifdef NON_MATCHING
/* The original keeps a redundant `i = 0` before the first increment. */
/* Busy-waits briefly. */
void func_8023BDF8_ovl_2A8D20(void) {
    s32 i = 0;

    for (i++; i < 28; i++) {
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023BDF8_ovl_2A8D20);
#endif

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023BE14_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023BF5C_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023C0B0_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023C3DC_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023C804_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023C874_ovl_2A8D20);

void func_8023C9BC_ovl_2A8D20(void) {
    HFree(FIELD(D_8022A974, void *, 0x19F0));
    FIELD(D_8022A974, void *, 0x19F0) = NULL;
}

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023C9EC_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023CFA0_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023D0EC_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023D1E8_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023D2DC_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023D7A8_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023D878_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023DAC4_ovl_2A8D20);

s32 func_8023DCC0_ovl_2A8D20(void) {
    return FIELD(D_8022A974, s32, 0x1CA8) != 0;
}

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023DCD4_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023DE14_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023DF70_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023E050_ovl_2A8D20);

s32 func_8023E2C0_ovl_2A8D20(void) {
    u8 *p = D_8022A978;
    s32 r = 0;

    if (p != NULL) {
        r = FIELD(p, s16, 0x8) != FIELD(p, s16, 0xA);
    }
    return r;
}

void func_8023E2E8_ovl_2A8D20(void) {
    HFree(D_8022A978);
    D_8022A978 = NULL;
}
