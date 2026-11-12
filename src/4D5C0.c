#include "common.h"

extern u16 D_800C4C26;
extern u16 D_800E9C0A[];
extern u16 D_80190F30_ovl_040E80;
extern u8 D_80187030_ovl_040E80;
extern u8 D_8018FB20_ovl_040E80[];
extern struct { u8 pad[4]; u16 state; } *D_800C4BBC;
void func_80198080(s32 arg);
void func_8007337C(void);
void func_801C8864(void);
void func_80173610_ovl_040E80(void);
void func_801A9288(void);
void func_8016C814_ovl_040E80(void);
void func_801C889C(s32 arg);
s32 func_80170794_ovl_040E80(s32 arg);
void func_801A1A0C(void);
void func_801A1AD4(void);
void func_8007485C(s32 arg);
void func_801B5A30(void);
s16 func_801B5C24(void);

extern u8 D_8018FAE4_ovl_040E80[];
extern u8 D_8018FAF8_ovl_040E80[];
extern u8 D_8018FB0C_ovl_040E80[];
extern u8 D_8018FB38_ovl_040E80[];
extern u8 D_8018FB50_ovl_040E80[];
extern u8 D_8018FB64_ovl_040E80[];
extern u8 D_8018FB78_ovl_040E80[];
extern u8 D_8018FB8C_ovl_040E80[];
extern u8 D_8018FBA0_ovl_040E80[];
extern u8 D_8018FBB4_ovl_040E80[];
extern u8 D_8018FBC8_ovl_040E80[];
extern u8 D_8018FBE0_ovl_040E80[];
extern u8 D_8018FC1C_ovl_040E80[];
void func_8019B2E0();
void func_8019B6D8();
void func_8019D548();
void func_801A39F0();
void func_801A3B98();
void func_801A40CC();
void func_801A576C();
void func_801A590C();
void func_801A5914();
void func_801A5A34();
void func_801A9C48();
void func_801AA0B4();
void func_801AC924();
void func_801ACDE0();
void func_801B00B0();
void func_801B5ACC();
void func_801B6C08();
void func_801D40EC();
void func_801D4128();
void func_801EE718();
void func_80226CC0();
void func_80226DA8();

void *func_801776C0_ovl_040E80(void) {
    return D_8018FAE4_ovl_040E80;
}

void func_801776CC_ovl_040E80(void) {
    func_80198080(-1);
    D_800C4C26 = 0x800E;
}

void *func_801776F4_ovl_040E80(void) {
    return D_8018FAF8_ovl_040E80;
}

void func_80177700_ovl_040E80(void) {
    func_80198080(0x29);
    D_800C4C26 = 0x8014;
}

void *func_80177728_ovl_040E80(void) {
    return D_8018FB0C_ovl_040E80;
}

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80177734_ovl_040E80);

void func_8017798C_ovl_040E80(void) {
    func_8007337C();
    func_801C8864();
}

void func_801779B0_ovl_040E80(s32 arg) {
    func_8016C814_ovl_040E80();
    func_801C889C(arg);
}

void func_801779DC_ovl_040E80(void) {
    func_801B00B0();
}

void *func_801779F8_ovl_040E80(void) {
    func_80173610_ovl_040E80();
    return D_8018FB20_ovl_040E80;
}

void func_80177A1C_ovl_040E80(void) {
    func_8019B2E0();
}

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80177A38_ovl_040E80);

void func_80177B40_ovl_040E80(void) {
    func_8019D548();
}

void func_80177B5C_ovl_040E80(void) {
    func_8019B6D8();
}

void *func_80177B78_ovl_040E80(void) {
    return D_8018FB38_ovl_040E80;
}

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80177B84_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80177CC0_ovl_040E80);

void func_80177D04_ovl_040E80(void) {
    func_801EE718();
}

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80177D20_ovl_040E80);

void *func_80177D74_ovl_040E80(void) {
    return D_8018FB50_ovl_040E80;
}

void func_80177D80_ovl_040E80(void) {
    if (!func_80170794_ovl_040E80(1)) {
        func_801A1A0C();
    }
}

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80177DAC_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80177DE8_ovl_040E80);

void func_80177E20_ovl_040E80(void) {
    if (!func_80170794_ovl_040E80(1)) {
        func_801A1AD4();
    }
}

void *func_80177E4C_ovl_040E80(void) {
    return D_8018FB64_ovl_040E80;
}

void func_80177E58_ovl_040E80(void) {
    func_801A39F0();
}

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80177E74_ovl_040E80);

void func_80177EA0_ovl_040E80(void) {
    func_801A40CC();
}

void func_80177EBC_ovl_040E80(void) {
    func_801A3B98();
}

void *func_80177ED8_ovl_040E80(void) {
    return D_8018FB78_ovl_040E80;
}

void func_80177EE4_ovl_040E80(void) {
    func_801A576C();
}

void func_80177F00_ovl_040E80(void) {
    func_801A5914();
}

void func_80177F1C_ovl_040E80(void) {
    func_801A5A34();
}

void func_80177F38_ovl_040E80(void) {
    func_801A590C();
}

void *func_80177F54_ovl_040E80(void) {
    return D_8018FB8C_ovl_040E80;
}

void func_80177F60_ovl_040E80(void) {
    func_801AC924();
}

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80177F7C_ovl_040E80);

void func_80177FB4_ovl_040E80(void) {
    func_801ACDE0();
}

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80177FD0_ovl_040E80);

void func_80178014_ovl_040E80(void) {
    func_801A9288();
    func_8007337C();
}

void func_80178038_ovl_040E80(void) {
    func_801A9C48();
}

void *func_80178054_ovl_040E80(void) {
    return D_8018FBA0_ovl_040E80;
}

void *func_80178060_ovl_040E80(void) {
    return D_8018FBB4_ovl_040E80;
}

void func_8017806C_ovl_040E80(void) {
    D_80187030_ovl_040E80 = 1;
    func_8007485C(14);
    func_801B5A30();
}

void func_8017809C_ovl_040E80(void) {
    if (func_801B5C24()) {
        D_800C4C26 = 0xFFFD;
    }
}

void func_801780CC_ovl_040E80(void) {
    func_801B6C08();
}

void func_801780E8_ovl_040E80(void) {
    func_801B5ACC();
}

void *func_80178104_ovl_040E80(void) {
    return D_8018FBC8_ovl_040E80;
}

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80178110_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80178250_ovl_040E80);

void func_80178280_ovl_040E80(void) {
    func_80226DA8();
}

void func_8017829C_ovl_040E80(void) {
    func_80226CC0();
}

void *func_801782B8_ovl_040E80(void) {
    return D_8018FBE0_ovl_040E80;
}

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_801782C4_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_801783A8_ovl_040E80);

void func_801783D8_ovl_040E80(void) {
    func_801D40EC();
}

void func_801783F4_ovl_040E80(void) {
    func_801D4128();
}

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80178410_ovl_040E80);

void func_80178444_ovl_040E80(void) {
    func_801AA0B4();
}

void *func_80178460_ovl_040E80(void) {
    return D_8018FC1C_ovl_040E80;
}

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_8017846C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_801784BC_ovl_040E80);

void func_8017850C_ovl_040E80(void) {
    if (D_800C4BBC != NULL && D_800C4BBC->state == 13) {
        D_800C4BBC->state = 2;
    }
}

void func_80178534_ovl_040E80(void) {
    D_800E9C0A[1] = D_80190F30_ovl_040E80;
}

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80178548_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80178898_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80178900_ovl_040E80);

void func_8017892C_ovl_040E80(void) {
}

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80178934_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80178B20_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80178B5C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80178BF4_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80178C64_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80178C90_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80178CCC_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80178D10_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80178D3C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80178DFC_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80178E30_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4D5C0", func_80178E60_ovl_040E80);

INCLUDE_RODATA("asm/nonmatchings/4D5C0", D_80190C80_ovl_040E80);
