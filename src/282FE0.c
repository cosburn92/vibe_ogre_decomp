#include "common.h"

extern u8 D_800EB0B0[];
extern s32 D_8022A8A8_ovl_281860[];
extern void *D_8022A8C4_ovl_281860;
extern s32 D_8022A990_ovl_281860;
extern u8 D_8018FC19;
extern u8 D_8022A980_ovl_281860;
extern u8 *D_8018FC10;
extern u8 *D_8022A974_ovl_281860;
void func_800EA838(void *p);
void func_800EA884(s32 a);
void HFree(void *p);
void MusSetMasterVolume(s32 flags, s32 volume);





INCLUDE_ASM("asm/nonmatchings/282FE0", func_80227010_ovl_281860);

INCLUDE_ASM("asm/nonmatchings/282FE0", func_802270BC_ovl_281860);

void func_80227210_ovl_281860(s32 i) {
    if (i == 7) {
        func_800EA838(D_800EB0B0);
    } else {
        func_800EA884(D_8022A8A8_ovl_281860[i]);
    }
}

INCLUDE_ASM("asm/nonmatchings/282FE0", func_80227254_ovl_281860);

void func_80227348_ovl_281860(void) {
    HFree(D_8022A8C4_ovl_281860);
    D_8022A8C4_ovl_281860 = NULL;
    MusSetMasterVolume(1, 0x7FFF);
}

INCLUDE_ASM("asm/nonmatchings/282FE0", func_80227380_ovl_281860);

INCLUDE_ASM("asm/nonmatchings/282FE0", func_802274F4_ovl_281860);

INCLUDE_ASM("asm/nonmatchings/282FE0", func_80227594_ovl_281860);

void func_8022767C_ovl_281860(void) {
}

void func_80227684_ovl_281860(void) {
    D_8022A990_ovl_281860 = 1;
}

/* Counts up while running (non-zero), stopping before it wraps. */
void func_80227694_ovl_281860(void) {
    if ((u32)(D_8022A990_ovl_281860 - 1) < 0xFFFFFFE) {
        D_8022A990_ovl_281860++;
    }
}

s32 func_802276C4_ovl_281860(void) {
    return D_8022A990_ovl_281860 - 1;
}

void func_802276D4_ovl_281860(void) {
    D_8022A990_ovl_281860 = 0;
}

void func_802276E0_ovl_281860(u8 v) {
    D_8018FC19 = v;
}

u8 func_802276EC_ovl_281860(void) {
    return D_8022A980_ovl_281860;
}

INCLUDE_ASM("asm/nonmatchings/282FE0", func_802276F8_ovl_281860);

void func_80227770_ovl_281860(void) {
}

INCLUDE_ASM("asm/nonmatchings/282FE0", func_80227778_ovl_281860);

INCLUDE_ASM("asm/nonmatchings/282FE0", func_80227838_ovl_281860);

INCLUDE_ASM("asm/nonmatchings/282FE0", func_802278DC_ovl_281860);

void func_802279D8_ovl_281860(void) {
    if (D_8018FC10 != NULL) {
        D_8018FC10[7] = 1;
    }
}

s16 func_802279F4_ovl_281860(void) {
    if (D_8018FC10 != NULL) {
        return *(s16 *)D_8018FC10;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/282FE0", func_80227A18_ovl_281860);

void func_80227B60_ovl_281860(void) {
    u8 *p = D_8022A974_ovl_281860;

    if (!p[0x1CB1]) {
        p[0x1CB1] = 1;
    }
}

void func_80227B80_ovl_281860(void) {
    u8 *p = D_8022A974_ovl_281860;

    if (p[0x1CB1]) {
        p[0x1CB1] = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/282FE0", func_80227B9C_ovl_281860);

INCLUDE_ASM("asm/nonmatchings/282FE0", func_80227CBC_ovl_281860);

/* Linear interpolation: b + (a - b) * c / d. */
s32 func_80227DC4_ovl_281860(s32 a, s32 b, s32 c, s32 d) {
    return (a - b) * c / d + b;
}

INCLUDE_RODATA("asm/nonmatchings/282FE0", D_8022ABA8_ovl_281860);

INCLUDE_RODATA("asm/nonmatchings/282FE0", D_8022ABB8_ovl_281860);
