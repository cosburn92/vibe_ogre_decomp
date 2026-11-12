#include "common.h"

typedef struct { u8 b[0x76]; } ScriptObj;   /* 4 x 0x76 at D_8022A2E8 */
typedef struct { s32 used; u8 b[0x58]; } ScriptRes; /* 4 x 0x5C at D_8022A4E0 */
typedef struct { u8 b; u8 pad[31]; } Rec32;

extern ScriptObj D_8022A2E8_ovl_1BA050[];
extern ScriptRes D_8022A4E0_ovl_1BA050[];
extern Rec32 D_8022A6A1_ovl_1BA050[];
extern s16 D_8022A718_ovl_1BA050;
extern s16 D_8022A71A_ovl_1BA050;
extern s16 D_8022A71C_ovl_1BA050;
extern s16 D_8022A71E_ovl_1BA050;
void bzero(void *p, s32 size);
void *func_8017F334(s32 id);
void func_8017C2FC(void *p);
void func_80225058_ovl_1BA050(s32 a, s32 b);
void func_802261D0_ovl_1BA050(s32 a, s32 b);





ScriptObj *func_80222EA0_ovl_1BA050(s32 i) {
    ScriptObj *o = &D_8022A2E8_ovl_1BA050[i];

    bzero(o, sizeof(ScriptObj));
    return o;
}

ScriptObj *func_80222EEC_ovl_1BA050(s32 i) {
    return &D_8022A2E8_ovl_1BA050[i];
}

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80222F10_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_8022402C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80224268_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80224320_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_802243A0_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_802245EC_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_8022478C_ovl_1BA050);

void func_80224A88_ovl_1BA050(void) {
    bzero(D_8022A2E8_ovl_1BA050, 4 * sizeof(ScriptObj));
}

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80224AAC_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80224B5C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80224BE8_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80224C60_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80224D60_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80224E1C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80224E74_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80225058_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80225DFC_ovl_1BA050);

ScriptRes *func_80226164_ovl_1BA050(u32 i) {
    if (i >= 4) {
        for (;;) {
        }
    }
    return &D_8022A4E0_ovl_1BA050[i];
}

s32 func_80226198_ovl_1BA050(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_8022A4E0_ovl_1BA050[i].used != 0) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_802261D0_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_8022630C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_802263CC_ovl_1BA050);

s32 func_80226420_ovl_1BA050(u8 *p) {
    return p[0xD] == 5;
}

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80226430_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_8022648C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80226564_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80226A1C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80226E8C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80227234_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_8022750C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80227E00_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80227EB8_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80227F14_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80227F68_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80228048_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_802282D0_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80228378_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_8022845C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_802284B4_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80228BF0_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80228CE4_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80228E88_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80228EE4_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80228F54_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80228FE8_ovl_1BA050);

s32 func_80229040_ovl_1BA050(s32 i) {
    return D_8022A6A1_ovl_1BA050[i].b == 3;
}

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_8022905C_ovl_1BA050);

void func_802291BC_ovl_1BA050(s16 a, s16 b, s16 c, s16 d) {
    D_8022A718_ovl_1BA050 = a;
    D_8022A71A_ovl_1BA050 = b;
    D_8022A71C_ovl_1BA050 = c;
    D_8022A71E_ovl_1BA050 = d;
}

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_802291E0_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_802292DC_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80229604_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_802296B0_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80229828_ovl_1BA050);

void func_80229930_ovl_1BA050(void) {
    void *o = func_8017F334(0x5500);

    if (o != NULL) {
        func_8017C2FC(o);
    }
}

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_8022995C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80229A20_ovl_1BA050);

void func_80229B18_ovl_1BA050(void) {
    void *o = func_8017F334(0x5501);

    if (o != NULL) {
        func_8017C2FC(o);
    }
}

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80229B44_ovl_1BA050);

void func_80229B98_ovl_1BA050(s32 a, s32 b) {
    func_80225058_ovl_1BA050(a, b);
    func_802261D0_ovl_1BA050(a, b);
}

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80229BD4_ovl_1BA050);

INCLUDE_RODATA("asm/nonmatchings/1BBFB0", D_8022A1D8_ovl_1BA050);

INCLUDE_RODATA("asm/nonmatchings/1BBFB0", D_8022A1E0_ovl_1BA050);
