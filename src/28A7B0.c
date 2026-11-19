#include "common.h"

/* ovl_286BD0 (28A7B0) */

typedef struct {
    /* 0x00 */ u8 unk00[2];
    /* 0x02 */ u16 hi;
    /* 0x04 */ u8 mid;
    /* 0x05 */ u8 lo;
} TimeStamp;

extern u8 D_8023E5FF_ovl_286BD0[]; /* bit flags, 1-based */
extern u8 D_8023DF18_ovl_286BD0[]; /* ids, 0xFF-terminated */
extern u8 D_8023E5D0_ovl_286BD0[];
extern u8 D_8023DF0C_ovl_286BD0;
extern u8 D_8023DE3C_ovl_286BD0;
extern s32 D_800A8204[];
extern s32 D_800C4BB8;
extern u8 D_800E7A0C;
extern u8 D_8018FC00[];

void nuGfxTaskAllEndWait(void);
void func_80089AB0(void *p, s32 n);
void func_8016CD5C(s32 a);
void func_802344D0_ovl_286BD0(void);
/* --- end decls --- */

void func_8022E870_ovl_286BD0(s32 unused, s32 n, u8 set) {
    u8 i;

    i = n - 1;
    if (set == 1) {
        D_8023E5FF_ovl_286BD0[i / 8] |= 1 << (i % 8);
    } else {
        D_8023E5FF_ovl_286BD0[i / 8] &= ~(1 << (i % 8));
    }
}

s32 func_8022E8D4_ovl_286BD0(s16 n) {
    return (D_8023E5FF_ovl_286BD0[n / 8] >> (n % 8)) & 1;
}

void func_8022E90C_ovl_286BD0(u8 id, u8 val) {
    s16 i;

    for (i = 0; D_8023DF18_ovl_286BD0[i] != 0xFF; i++) {
        if (D_8023DF18_ovl_286BD0[i] == id) {
            D_8023E5D0_ovl_286BD0[i] = val;
            return;
        }
    }
}

void func_8022E978_ovl_286BD0(u8 a) {
    D_8023DF0C_ovl_286BD0 = a;
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022E984_ovl_286BD0);

/* Whether b is earlier than a */
s32 func_8022EA9C_ovl_286BD0(TimeStamp *a, TimeStamp *b) {
    s32 va = a->lo + a->mid * 30 + a->hi * 600;
    s32 vb = b->lo + b->mid * 30 + b->hi * 600;

    return vb < va;
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022EB0C_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022EC34_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022ECBC_ovl_286BD0);

/* Texture line size in bytes for pixel size siz and width w */
u32 func_8022ED48_ovl_286BD0(s32 siz, u32 w) {
    if (siz == 3) {
        return ((w + 3) >> 2) << 4;
    }
    if (siz == 2) {
        return ((w + 3) >> 2) << 3;
    }
    if (siz == 1) {
        return ((w + 7) >> 3) << 3;
    }
    return ((w + 15) >> 4) << 3;
}

/* Width rounded up to a whole 64-bit line for pixel size siz */
u32 func_8022ED9C_ovl_286BD0(s32 siz, u32 w) {
    if (siz == 3) {
        return ((w + 3) >> 2) << 2;
    }
    if (siz == 2) {
        return ((w + 3) >> 2) << 2;
    }
    if (siz == 1) {
        return ((w + 7) >> 3) << 3;
    }
    return ((w + 15) >> 4) << 4;
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022EDEC_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022EEB4_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022F024_ovl_286BD0);

void func_8022F148_ovl_286BD0(void) {
    nuGfxTaskAllEndWait();
    func_80089AB0(D_800A8204, 3);
    D_800C4BB8 = D_800A8204[0];
    nuGfxTaskAllEndWait();
    func_8016CD5C(0);
    D_800E7A0C = 1;
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022F1A0_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022F264_ovl_286BD0);

void func_8022F2D8_ovl_286BD0(void) {
    nuGfxTaskAllEndWait();
    func_80089AB0(D_8018FC00, 2);
    nuGfxTaskAllEndWait();
    func_8016CD5C(1);
    D_800E7A0C = 0;
    D_8023DE3C_ovl_286BD0 = 0;
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022F324_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022F408_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022F5C4_ovl_286BD0);

void func_8022F848_ovl_286BD0(void) {
    func_802344D0_ovl_286BD0();
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022F864_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022F998_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022FB60_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022FC54_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022FCD4_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022FD78_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802300A8_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802300D4_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80230360_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80230ADC_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80231098_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802311B0_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80231D58_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80231EAC_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80231F04_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802320C0_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802321FC_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80232E20_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023324C_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802339D8_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80233DA8_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80233F38_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80234078_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802344D0_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802348A8_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802348B8_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802348D0_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802348E0_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023498C_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80234B38_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80234D10_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80234DB8_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80234E10_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023519C_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802351C4_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802351F0_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80235254_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80235914_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802359B4_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802372C8_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802376B8_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80237B7C_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80238910_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80238A00_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80238C4C_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80238D14_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80238EC4_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023906C_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802390AC_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80239160_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80239394_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802394A0_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80239570_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80239634_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802396F0_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802397B8_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80239B14_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80239C5C_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80239E30_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80239EE0_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023A398_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023A42C_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023A5D8_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023A814_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023AA70_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023AB74_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023AD10_ovl_286BD0);
