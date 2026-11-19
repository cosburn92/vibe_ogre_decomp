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

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
typedef struct {
    /* 0x00 */ s32 used;
    /* 0x04 */ u8 unk04[5];
    /* 0x09 */ u8 state;
    /* 0x0A */ u8 unk0A[6];
    /* 0x10 */ u16 h10;
    /* 0x12 */ u16 h12;
    /* 0x14 */ u16 h14;
    /* 0x16 */ u16 h16;
    /* 0x18 */ u16 h18;
    /* 0x1A */ u16 h1A;
    /* 0x1C */ u16 h1C;
    /* 0x1E */ u8 unk1E[2];
} Rec698; /* size 0x20 */
extern Rec698 D_8022A698_ovl_1BA050[];
extern u16 D_8022A4D8_ovl_1BA050;
extern u16 D_8022A4DA_ovl_1BA050;
extern u16 D_8022A4DC_ovl_1BA050;
extern u16 D_8022A4DE_ovl_1BA050;
extern u16 D_800E79B0;
extern u16 D_800E9BE4;
extern void *D_8022A4C0_ovl_1BA050[];
extern s32 D_8022A650_ovl_1BA050;
extern s32 D_8022A838_ovl_1BA050;
extern u8 D_8022A820_ovl_1BA050;
extern u8 D_8022A834_ovl_1BA050;
extern s16 D_8022A832_ovl_1BA050;
void HFree(void *p);
void func_80220F64_ovl_1BA050(u16 a, u8 b);
void func_8017C074(s32 a, s32 b, void *fn, s32 c, s32 d, s32 e, s32 f);
void func_80229BD4_ovl_1BA050(void);
s32 func_8016FBE0(u8 a, u8 b, void *out);
/* --- end decls --- */

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

void func_80224E1C_ovl_1BA050(void) {
    s32 i;
    s32 n = 6;

    for (i = 0; i < n; i++) {
        HFree(D_8022A4C0_ovl_1BA050[i]);
        D_8022A4C0_ovl_1BA050[i] = NULL;
    }
}

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

/* Pad edge detection: pressed = held & ~previous, for both controllers */
void func_802263CC_ovl_1BA050(void) {
    u16 pa = D_8022A4DC_ovl_1BA050;
    u16 a = D_800E79B0;
    u16 pb = D_8022A4DE_ovl_1BA050;
    u16 b = D_800E9BE4;

    D_8022A4D8_ovl_1BA050 = a & ~pa;
    D_8022A4DC_ovl_1BA050 = a;
    D_8022A4DA_ovl_1BA050 = b & ~pb;
    D_8022A4DE_ovl_1BA050 = b;
}

s32 func_80226420_ovl_1BA050(u8 *p) {
    return p[0xD] == 5;
}

void func_80226430_ovl_1BA050(u8 *p, s32 a) {
    u32 i;

    FIELD(p, s32, 0x18) = a;
    FIELD(p, s32, 0x1C) = 0;
    p[0x11] = 0;
    FIELD(p, s32, 0x38) = 0;
    p[0x22] = 0;
    for (i = 0; i < 4; i++) {
        FIELD(p, s32, 0x24 + i * 4) = 0;
    }
    p[0x41] = 0;
    p[0x40] = 0;
    if (p[0xD] != 0 && p[0xD] < 17) {
        p[0xD] = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_8022648C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80226564_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80226A1C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80226E8C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80227234_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_8022750C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80227E00_ovl_1BA050);

void func_80227EB8_ovl_1BA050(u8 *p, s32 a, s32 b, s32 c) {
    p[0xF] |= c;
    FIELD(p, s32, 0x4C) = func_8016FBE0(a, b, p + 0x50);
    FIELD(p, u16, 0x46) = 2;
    FIELD(p, u16, 0x14) = 2;
    FIELD(p, u16, 0x48) = 2;
    FIELD(p, u16, 0x20) = FIELD(p, u16, 0x46) + 0x2C;
}

void func_80227F14_ovl_1BA050(u32 i, s32 v) {
    if (i >= 4) {
        for (;;) {
        }
    }
    D_8022A4E0_ovl_1BA050[i].b[10] = v;
    func_80220F64_ovl_1BA050(i | 0x5200, v);
}

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80227F68_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80228048_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_802282D0_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80228378_ovl_1BA050);

void func_8022845C_ovl_1BA050(void) {
    bzero(D_8022A4E0_ovl_1BA050, 0x170);
    D_8022A650_ovl_1BA050 = 0;
    D_8022A4DE_ovl_1BA050 = 0;
    D_8022A4DC_ovl_1BA050 = 0;
    D_8022A4DA_ovl_1BA050 = 0;
    D_8022A4D8_ovl_1BA050 = 0;
    D_8022A838_ovl_1BA050 = -1;
}

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_802284B4_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80228BF0_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80228CE4_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80228E88_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80228EE4_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80228F54_ovl_1BA050);

void func_80228FE8_ovl_1BA050(s32 i) {
    Rec698 *r;

    if (i >= 4) {
        for (;;) {
        }
    }
    r = &D_8022A698_ovl_1BA050[i];
    if (r->used == 0) {
        for (;;) {
        }
    }
    r->h14 = 0;
    r->h1A = 0;
    r->h1C = 0;
    r->state = 2;
    r->h12 = r->h10;
    r->h18 = r->h16;
}

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

void func_80229B44_ovl_1BA050(void) {
    D_8022A820_ovl_1BA050 = 0;
    D_8022A834_ovl_1BA050 = 8;
    D_8022A832_ovl_1BA050 = 0;
    func_8017C074(0x5501, 0x13, func_80229BD4_ovl_1BA050, 0, 0, 0, 0);
}

void func_80229B98_ovl_1BA050(s32 a, s32 b) {
    func_80225058_ovl_1BA050(a, b);
    func_802261D0_ovl_1BA050(a, b);
}

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80229BD4_ovl_1BA050);

INCLUDE_RODATA("asm/nonmatchings/1BBFB0", D_8022A1D8_ovl_1BA050);

INCLUDE_RODATA("asm/nonmatchings/1BBFB0", D_8022A1E0_ovl_1BA050);
