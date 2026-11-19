#include "common.h"

/* 1CE070 */

/* 16 zero bytes (shared rodata splat leaves unmigrated) */
__asm__(".section .rodata\n.global D_801B99A0_ovl_1CE070\nD_801B99A0_ovl_1CE070:\n.word 0, 0, 0, 0\n.section .text\n");

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

typedef struct {
    /* 0x0 */ u8 unk0[4];
    /* 0x4 */ u16 w;
    /* 0x6 */ u16 h;
} SizeCE;

extern Gfx *D_800E9BA0;
extern s32 D_801B8090_ovl_1CE070;
extern s32 D_801B8094_ovl_1CE070;
extern u8 D_801B80B0_ovl_1CE070[];
extern void *D_801BA6F8_ovl_1CE070;
extern u8 D_800A8210;
extern u8 D_800A8211;
extern u8 D_800A8212;
extern s32 D_800C4B20;
extern u8 D_801BA710[];
extern u8 D_80243DB0[];

void *HMalloc(s32 size);
void bzero(void *p, s32 n);
void func_8019898C_ovl_1CE070(SizeCE *s, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
u8 func_8016CD30(void);
void func_8019915C_ovl_1CE070(void);
void func_80076E00(void);
void func_801792BC(void);
void func_8017BF10(void);
void func_80073398(void);
void func_80179058(void);
void func_80070F14(void);
void func_80070C60(void *p, u32 size);
void func_8009DAEC(void);
void func_80179060(void);
void func_8017BDC0(void);
void func_80076E2C(void);
/* --- end decls --- */

/* Texture line size in bytes for pixel size siz and width w */
u32 func_80197B70_ovl_1CE070(s32 siz, u32 w) {
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
u32 func_80197BC4_ovl_1CE070(s32 siz, u32 w) {
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

/* Texture size in bytes */
u32 func_80197C14_ovl_1CE070(s32 siz, u32 w, s32 h) {
    u32 r;

    if (siz == 3) {
        r = ((w + 3) >> 2) << 4;
    } else if (siz == 2) {
        r = ((w + 3) >> 2) << 3;
    } else if (siz == 1) {
        r = ((w + 7) >> 3) << 3;
    } else {
        r = ((w + 15) >> 4) << 3;
    }
    return r * h;
}

INCLUDE_ASM("asm/nonmatchings/1CE070", func_80197C74_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_801985D0_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_801986E0_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_80198840_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019898C_ovl_1CE070);

void func_80198EAC_ovl_1CE070(SizeCE *s, s32 a, s32 b) {
    func_8019898C_ovl_1CE070(s, 0, 0, s->w, s->h, a, b);
}

void func_80198EE0_ovl_1CE070(void) {
    D_801B8090_ovl_1CE070 = 0;
}

INCLUDE_ASM("asm/nonmatchings/1CE070", func_80198EEC_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_80198FB4_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_80199088_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019915C_ovl_1CE070);

void func_801993F0_ovl_1CE070(void) {
    if (func_8016CD30()) {
        D_800A8212 = 1;
        D_800A8211 = 1;
        D_800A8210 = 1;
        if (D_800C4B20 == 0) {
            D_800C4B20 = (D_801B8094_ovl_1CE070 + 0x3F) & ~0x3F;
        }
        func_8019915C_ovl_1CE070();
    }
}

void func_80199460_ovl_1CE070(void) {
    func_80076E00();
    func_801792BC();
    func_8017BF10();
    func_80073398();
    func_80179058();
    func_80070F14();
    func_80070C60(D_801BA710, 0x80400000 - (u32)D_801BA710);
    func_8009DAEC();
}

void func_801994C0_ovl_1CE070(void) {
    func_80073398();
    func_80070F14();
    func_80070C60(D_80243DB0, 0x80400000 - (u32)D_80243DB0);
    func_8009DAEC();
    func_80179060();
    func_8017BDC0();
    func_80076E2C();
}

void func_80199518_ovl_1CE070(void) {
    Gfx *g;

    g = D_800E9BA0++;
    g->w0 = 0xE7000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xDC080008;
    g->w1 = (u32)D_801B80B0_ovl_1CE070;
}

INCLUDE_ASM("asm/nonmatchings/1CE070", func_80199560_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_80199968_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_80199C3C_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_80199CF0_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_80199E48_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_80199ECC_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_80199FF0_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019A09C_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019A194_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", UtCreateTexture);

void func_8019AF0C_ovl_1CE070(void) {
    void *p = HMalloc(0x398);

    D_801BA6F8_ovl_1CE070 = p;
    bzero(p, 0x398);
}

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019AF3C_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019B054_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", UnitAnimGetCommand);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019B2E0_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019B6D8_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019B8AC_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019BB7C_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019BCEC_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019C168_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019C5B4_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019CBB8_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019CE8C_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019D09C_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019D2EC_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019D438_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019D548_ovl_1CE070);
