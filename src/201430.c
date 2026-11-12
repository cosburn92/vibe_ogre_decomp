#include "common.h"
#include "tables.h"

extern struct { u8 a; u8 b; } D_801CECF0_ovl_1F0A30[];
extern u8 *D_801D0680_ovl_1F0A30;
extern u8 *D_801D0684_ovl_1F0A30;
extern u8 *D_801D0688_ovl_1F0A30;
extern u8 D_801CEE14_ovl_1F0A30[];
extern u8 *D_801D06A4_ovl_1F0A30;
extern struct { s16 x; s16 y; s16 z; } *D_801D06A8_ovl_1F0A30;
extern void *D_801D06AC_ovl_1F0A30;
extern u8 D_801CEEC0_ovl_1F0A30[][4];
void HFree(void *p);
s32 func_801BE9A8_ovl_1F0A30(s32 a, s32 b);
void func_801C0F50_ovl_1F0A30(s32 a, s32 b, s32 c, s32 d, s32 e);





char *func_801BDFA0_ovl_1F0A30(u8 i) {
    return gAttackTable[i + 0x37].name;
}

INCLUDE_ASM("asm/nonmatchings/201430", func_801BDFBC_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BE034_ovl_1F0A30);

u8 func_801BE0A8_ovl_1F0A30(u8 i) {
    return D_801CECF0_ovl_1F0A30[i].a;
}

u8 func_801BE0C0_ovl_1F0A30(u8 i) {
    return D_801CECF0_ovl_1F0A30[i].b & 0xF;
}

u8 func_801BE0DC_ovl_1F0A30(u16 i) {
    return D_801D0680_ovl_1F0A30[i];
}

u8 func_801BE0F4_ovl_1F0A30(s32 cls, s32 other) {
    if (gClassTable[cls].baseClass == other) {
        return D_801D0684_ovl_1F0A30[cls];
    }
    return D_801D0684_ovl_1F0A30[other];
}

INCLUDE_ASM("asm/nonmatchings/201430", func_801BE138_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BE18C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BE1E0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BE264_ovl_1F0A30);

u8 func_801BE2E8_ovl_1F0A30(s32 a, s32 b) {
    return D_801D0688_ovl_1F0A30[a * 3 + b];
}

INCLUDE_ASM("asm/nonmatchings/201430", func_801BE308_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BE3A8_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BE410_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BE478_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BE564_ovl_1F0A30);

u8 func_801BE688_ovl_1F0A30(u32 i) {
    if (i < 160) {
        return D_801CEE14_ovl_1F0A30[i];
    }
    return 100;
}

u8 func_801BE6A8_ovl_1F0A30(s32 i) {
    return D_801D06A4_ovl_1F0A30[i];
}

s16 func_801BE6BC_ovl_1F0A30(s32 i) {
    return D_801D06A8_ovl_1F0A30[i].x;
}

s16 func_801BE6DC_ovl_1F0A30(s32 i) {
    return D_801D06A8_ovl_1F0A30[i].y;
}

s16 func_801BE6FC_ovl_1F0A30(s32 i) {
    return D_801D06A8_ovl_1F0A30[i].z;
}

INCLUDE_ASM("asm/nonmatchings/201430", func_801BE71C_ovl_1F0A30);

void func_801BE894_ovl_1F0A30(void) {
    HFree(D_801D06AC_ovl_1F0A30);
    D_801D06AC_ovl_1F0A30 = NULL;
}

u8 func_801BE8C0_ovl_1F0A30(u32 a, u32 b) {
    if (a >= 5 || b >= 4) {
        return 0;
    }
    return D_801CEEC0_ovl_1F0A30[a][b];
}

INCLUDE_ASM("asm/nonmatchings/201430", func_801BE8FC_ovl_1F0A30);

s32 func_801BE978_ovl_1F0A30(s32 a, s32 b, s32 c) {
    return func_801BE9A8_ovl_1F0A30(a, b) * c;
}

INCLUDE_ASM("asm/nonmatchings/201430", func_801BE9A8_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BEA0C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BEA70_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BEB28_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BEBE4_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BED08_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BEDC8_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BEEA0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BEEDC_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BEF14_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BF59C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BF858_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BF9B4_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BFBA0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BFE28_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BFF84_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801C00E0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801C01D4_ovl_1F0A30);

void func_801C0F34_ovl_1F0A30(s32 a, s32 b, s32 c, s32 d) {
    func_801C0F50_ovl_1F0A30(a, b, c, d, 0);
}

INCLUDE_ASM("asm/nonmatchings/201430", func_801C0F50_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801C15E0_ovl_1F0A30);
