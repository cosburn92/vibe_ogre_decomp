#include "common.h"

/* 1F8D70 */

typedef struct {
    /* 0x0 */ u8 unk0[4];
    /* 0x4 */ u16 w;
    /* 0x6 */ u16 h;
} Size1F;

extern s32 D_801CEAB4_ovl_1F0A30;
extern s32 D_801D079C_ovl_1F0A30;
extern s32 D_801D07CC_ovl_1F0A30;
extern s32 D_801D07E4_ovl_1F0A30;
extern s32 D_801D07E8_ovl_1F0A30;
extern s32 D_801D07EC_ovl_1F0A30;
extern s16 D_801D07F4_ovl_1F0A30;
extern s16 D_801D07F6_ovl_1F0A30;
extern s16 D_801D07F8_ovl_1F0A30;
extern s16 D_801D07FA_ovl_1F0A30;
extern s16 D_801D07FC_ovl_1F0A30;
extern s16 D_801D07FE_ovl_1F0A30;
extern s16 D_801D0800_ovl_1F0A30;
extern s16 D_801D0802_ovl_1F0A30;
extern s16 D_801D0804_ovl_1F0A30;
extern s16 D_801D0806_ovl_1F0A30;
extern s16 D_801D0808_ovl_1F0A30;
extern s16 D_801D080A_ovl_1F0A30;
extern u8 D_801D080C_ovl_1F0A30;
extern u8 D_801D080D_ovl_1F0A30;
extern s32 D_801D0770_ovl_1F0A30[];
extern void *D_801D0748_ovl_1F0A30[];
extern void *D_801D074C_ovl_1F0A30;
extern void *D_801D0750_ovl_1F0A30;
extern void *D_801D0754_ovl_1F0A30;
extern u8 D_801D0828_ovl_1F0A30[];
extern u8 *D_801CE8C0_ovl_1F0A30;
extern u8 D_801976DC;
extern u8 D_801976E8;

void bzero(void *p, s32 n);
void *HFree(void *p);
void func_801B594C_ovl_1F0A30(Size1F *a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);
void func_801BC15C_ovl_1F0A30(s16 a, s16 b, s32 c, s32 d, s32 e);
void func_801C5D64_ovl_1F0A30(void);
void func_801BDC78_ovl_1F0A30(void);
void func_801C62E4_ovl_1F0A30(s32 a, u8 *b, u8 c);
/* --- end decls --- */

void func_801B58E0_ovl_1F0A30(void) {
    D_801CEAB4_ovl_1F0A30 = !D_801CEAB4_ovl_1F0A30;
}

s32 func_801B58F8_ovl_1F0A30(void) {
    return D_801CEAB4_ovl_1F0A30;
}

void func_801B5904_ovl_1F0A30(void) {
    s32 *p = &D_801D079C_ovl_1F0A30;

    *p = !*p;
}

void func_801B591C_ovl_1F0A30(void) {
    s32 *p = &D_801D07CC_ovl_1F0A30;

    *p = !*p;
}

s32 func_801B5934_ovl_1F0A30(void) {
    return D_801D079C_ovl_1F0A30;
}

s32 func_801B5940_ovl_1F0A30(void) {
    return D_801D07CC_ovl_1F0A30;
}

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B594C_ovl_1F0A30);

void func_801B5CAC_ovl_1F0A30(Size1F *s, s32 a, s32 b) {
    func_801B594C_ovl_1F0A30(s, 0, 0, s->w, s->h, a, b);
}

void func_801B5CE0_ovl_1F0A30(u16 *p, s16 a, s16 b, s16 c, s16 d) {
    bzero(p, 0x10);
    p[0] = a;
    p[1] = b;
    p[4] = c << 6;
    ((u8 *)p)[0xF] = 0xFF;
    p[5] = d << 6;
}

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B5D58_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B619C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B6970_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B6DB0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B7284_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B77CC_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B7888_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B7914_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B7A7C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B7CBC_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B7D54_ovl_1F0A30);

/* 16 zero bytes in rodata (emitted from asm: gcc loses track of the section after INCLUDE_ASM) */
__asm__(".section .rodata
.global D_801D0178_ovl_1F0A30
D_801D0178_ovl_1F0A30:
.word 0, 0, 0, 0
.section .text
");

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B7E9C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B8F2C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B90A8_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B9698_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BA0DC_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BAA38_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BB58C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BB87C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BBC78_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BBE60_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BC15C_ovl_1F0A30);

void func_801BC35C_ovl_1F0A30(s16 a, s16 b) {
    func_801BC15C_ovl_1F0A30(a, b, D_801D07E8_ovl_1F0A30, D_801D07EC_ovl_1F0A30, D_801D07E4_ovl_1F0A30);
}

void func_801BC3A0_ovl_1F0A30(s16 a, s16 b, s16 c, s16 d) {
    D_801D07F4_ovl_1F0A30 = a;
    D_801D07F6_ovl_1F0A30 = b;
    D_801D07F8_ovl_1F0A30 = c;
    D_801D07FA_ovl_1F0A30 = d;
    D_801D080C_ovl_1F0A30 = 0;
    D_801D080D_ovl_1F0A30 = 1;
}

void func_801BC3D8_ovl_1F0A30(s16 a, s16 b, s16 c, s16 d, u8 e) {
    D_801D0804_ovl_1F0A30 = a;
    D_801D0806_ovl_1F0A30 = b;
    D_801D0808_ovl_1F0A30 = c;
    D_801D080A_ovl_1F0A30 = d;
    D_801D080D_ovl_1F0A30 = 0;
    D_801D07FC_ovl_1F0A30 = D_801D07F4_ovl_1F0A30;
    D_801D07FE_ovl_1F0A30 = D_801D07F6_ovl_1F0A30;
    D_801D0800_ovl_1F0A30 = D_801D07F8_ovl_1F0A30;
    D_801D0802_ovl_1F0A30 = D_801D07FA_ovl_1F0A30;
    D_801D080C_ovl_1F0A30 = e;
}

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BC450_ovl_1F0A30);

void func_801BC5FC_ovl_1F0A30(void) {
    bzero(D_801D0770_ovl_1F0A30, 0xA0);
    bzero(D_801D0748_ovl_1F0A30, 0x1C);
    bzero(D_801D0828_ovl_1F0A30, 5);
}

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BC640_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BC76C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BC838_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BC914_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BC9F0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BCD0C_ovl_1F0A30);

s32 func_801BCFE4_ovl_1F0A30(void) {
    return D_801D0770_ovl_1F0A30[0];
}

/* 16 zero bytes in rodata (emitted from asm: gcc loses track of the section after INCLUDE_ASM) */
__asm__(".section .rodata
.global D_801D02B0_ovl_1F0A30
D_801D02B0_ovl_1F0A30:
.word 0, 0, 0, 0
.section .text
");

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BCFF0_ovl_1F0A30);

void func_801BD1F4_ovl_1F0A30(void) {
    HFree(D_801D0748_ovl_1F0A30[0]);
    HFree(D_801D074C_ovl_1F0A30);
    HFree(D_801D0750_ovl_1F0A30);
    HFree(D_801D0754_ovl_1F0A30);
    bzero(D_801D0748_ovl_1F0A30, 0x1C);
    func_801C5D64_ovl_1F0A30();
}

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BD258_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BDC78_ovl_1F0A30);

void func_801BDF40_ovl_1F0A30(void) {
    func_801BDC78_ovl_1F0A30();
    func_801C62E4_ovl_1F0A30(0, D_801CE8C0_ovl_1F0A30 + 0x82F, D_801976DC);
    func_801C62E4_ovl_1F0A30(1, D_801CE8C0_ovl_1F0A30 + 0x848, D_801976E8);
}
