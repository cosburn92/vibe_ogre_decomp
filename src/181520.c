#include "common.h"

typedef struct {
    s32 data[0x16];
} Camera; /* size 0x58 */

typedef struct {
    /* 0x00 */ Camera *saved;
    /* 0x04 */ s32 arg;
    /* 0x08 */ s16 timer;
    /* 0x0A */ s16 alpha;
    /* 0x0C */ s16 *alphaPtr;
    /* 0x10 */ s16 unk10;
    /* 0x14 */ s32 unk14;
} Ovl17F9C0Ctx; /* size 0x18 */

extern Ovl17F9C0Ctx *D_8021AF00_ovl_17F9C0;
extern u8 D_8021AF04_ovl_17F9C0;
extern Camera *D_8018F58C;
extern u8 D_800EB290[];

void *HMalloc(s32 size);
void *HFree(void *p);
void func_800EA604(void *ch, s32 sound);
void func_80216AE0_ovl_17F9C0(void);
void func_80216F3C_ovl_17F9C0(void);
void func_80217114_ovl_17F9C0(void);

INCLUDE_ASM("asm/nonmatchings/181520", func_80216AE0_ovl_17F9C0);

INCLUDE_ASM("asm/nonmatchings/181520", func_80216C08_ovl_17F9C0);

INCLUDE_ASM("asm/nonmatchings/181520", func_80216F3C_ovl_17F9C0);

INCLUDE_ASM("asm/nonmatchings/181520", func_80217114_ovl_17F9C0);

void func_80217474_ovl_17F9C0(s32 arg) {
    D_8021AF00_ovl_17F9C0 = HMalloc(sizeof(Ovl17F9C0Ctx));
    D_8021AF00_ovl_17F9C0->arg = arg;
    D_8021AF00_ovl_17F9C0->saved = HMalloc(sizeof(Camera));
    *D_8021AF00_ovl_17F9C0->saved = *D_8018F58C;
    D_8021AF00_ovl_17F9C0->timer = 0;
    D_8021AF00_ovl_17F9C0->alpha = 0xFF;
}

void func_8021751C_ovl_17F9C0(void) {
    *D_8018F58C = *D_8021AF00_ovl_17F9C0->saved;
    HFree(D_8021AF00_ovl_17F9C0->saved);
    HFree(D_8021AF00_ovl_17F9C0);
    D_8021AF00_ovl_17F9C0 = NULL;
    D_8021AF04_ovl_17F9C0 = 0;
}

void func_802175B0_ovl_17F9C0(void) {
    Ovl17F9C0Ctx *ctx = D_8021AF00_ovl_17F9C0;

    if (ctx->timer == 0) {
        func_800EA604(D_800EB290, 0x288);
    }
    D_8021AF00_ovl_17F9C0->timer++;
    ctx->alphaPtr = &D_8021AF00_ovl_17F9C0->alpha;
    ctx->unk10 = 0;
    ctx->unk14 = 0x26;
    func_80216AE0_ovl_17F9C0();
    if (D_8021AF00_ovl_17F9C0->timer < 50) {
        D_8021AF04_ovl_17F9C0 = 4;
    } else {
        D_8021AF04_ovl_17F9C0 = 1;
    }
}

void func_80217640_ovl_17F9C0(void) {
    func_80216F3C_ovl_17F9C0();
    func_80217114_ovl_17F9C0();
}

u8 func_80217664_ovl_17F9C0(void) {
    return D_8021AF04_ovl_17F9C0;
}

INCLUDE_ASM("asm/nonmatchings/181520", func_80217670_ovl_17F9C0);
