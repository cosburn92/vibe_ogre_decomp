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
extern u8 D_80197178[];
extern void *D_800E9BA0;
extern u8 D_801969B0[];
void func_801B5D58_ovl_1F0A30(void *a, void *b, u8 *img);
void func_801B619C_ovl_1F0A30(void *a, void *b, u8 *img, u8 c, s32 d, s32 e);
void func_801B6970_ovl_1F0A30(void *a, void *b, u8 *img, u8 c, s32 d, s32 e);
void func_801B6DB0_ovl_1F0A30(void *a, void *b, u8 *img);
void func_801B7284_ovl_1F0A30(u8 *img, s32 x, s32 y, s32 s, void *b, void *m, void *a);
extern u8 D_801976DA;
extern s32 D_801CEAB0_ovl_1F0A30;
extern u8 D_801936A7;
extern u8 D_8018F557;
extern u8 D_8018F558;
extern u8 D_8018F559;

/* Map ids 0x22, 0x28, 0x29 and 0x2F-0x39 */
static inline s32 func_1F8D70_isTintedMap(s32 m) {
    switch (m) {
        case 0x22:
        case 0x28:
        case 0x29:
        case 0x2F:
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
            return 1;
        default:
            return 0;
    }
}
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

/* Draws image img: '64' bitmaps, or 'B5' banks by format (1, 3, other) */
void func_801B77CC_ovl_1F0A30(void *a, void *b, u8 *img, u8 c, s32 d, s32 e) {
    if (*(u16 *)img == 0x3634) {
        func_801B7284_ovl_1F0A30(img, -160, -120, 2, b, D_801969B0, a);
    } else if (img[2] == 1) {
        func_801B6DB0_ovl_1F0A30(a, b, img);
    } else if (img[2] == 3) {
        func_801B6970_ovl_1F0A30(a, b, img, c, d, e);
    } else {
        func_801B619C_ovl_1F0A30(a, b, img, c, d, e);
    }
}

/* Draws a full-screen image into the main display list */
#ifdef NON_MATCHING
/* original hoists the D_80197178/D_800E9BA0 args above the format test; frame 0x28 */
void func_801B7888_ovl_1F0A30(u8 **pp, void *b) {
    u8 *img = *pp;

    if (*(u16 *)img == 0x4235) {
        if (img[2] == 1) {
            func_801B6DB0_ovl_1F0A30(D_80197178, &D_800E9BA0, img);
        } else if (img[2] == 3) {
            func_801B6970_ovl_1F0A30(D_80197178, &D_800E9BA0, img, 0, 0, 0);
        } else {
            func_801B619C_ovl_1F0A30(D_80197178, &D_800E9BA0, img, 0, 0, 0);
        }
    } else {
        func_801B5D58_ovl_1F0A30(pp, b, img);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B7888_ovl_1F0A30);
#endif

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B7914_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B7A7C_ovl_1F0A30);

/* Frees a 'B5' image bank (and its chained pages) */
void func_801B7CBC_ovl_1F0A30(u8 *p) {
    if (p != NULL) {
        if (p[0] == 'B' && p[1] == '5') {
            u8 *bank = p;
            u8 *e = *(u8 **)(p + 0x14);
            u32 i;

            for (i = 1; i < bank[3]; i++) {
                u8 *cur = e;

                e = *(u8 **)(cur + 0xC);
                HFree(cur);
            }
        }
        HFree(p);
    }
}

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

/* Steps the box tween: frame D_801D080D of D_801D080C, from the 07FC.. rect toward 0804.. */
void func_801BC450_ovl_1F0A30(void) {
    u32 temp_t4;

    if (D_801D080C_ovl_1F0A30 != 0) {
        temp_t4 = D_801D080D_ovl_1F0A30 & 0xFF;
        if ((u8) D_801D080C_ovl_1F0A30 >= temp_t4) {
            D_801D080D_ovl_1F0A30 += 1;
            D_801D07F4_ovl_1F0A30 = D_801D07FC_ovl_1F0A30 + ((s32) ((D_801D0804_ovl_1F0A30 - D_801D07FC_ovl_1F0A30) * temp_t4) / (s32) D_801D080C_ovl_1F0A30);
            D_801D07F6_ovl_1F0A30 = D_801D07FE_ovl_1F0A30 + ((s32) ((D_801D0806_ovl_1F0A30 - D_801D07FE_ovl_1F0A30) * temp_t4) / (s32) D_801D080C_ovl_1F0A30);
            D_801D07F8_ovl_1F0A30 = D_801D0800_ovl_1F0A30 + ((s32) ((D_801D0808_ovl_1F0A30 - D_801D0800_ovl_1F0A30) * temp_t4) / (s32) D_801D080C_ovl_1F0A30);
            D_801D07FA_ovl_1F0A30 = D_801D0802_ovl_1F0A30 + ((s32) ((D_801D080A_ovl_1F0A30 - D_801D0802_ovl_1F0A30) * temp_t4) / (s32) D_801D080C_ovl_1F0A30);
        }
    }
}

void func_801BC5FC_ovl_1F0A30(void) {
    bzero(D_801D0770_ovl_1F0A30, 0xA0);
    bzero(D_801D0748_ovl_1F0A30, 0x1C);
    bzero(D_801D0828_ovl_1F0A30, 5);
}

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BC640_ovl_1F0A30);

/* Channel tint for the current map (ids 0x3B/0x2E special-cased) */
u8 func_801BC76C_ovl_1F0A30(void) {
    s32 t;

    if ((D_801976DA ^ 0x18) == 0) {
        return 0xFF;
    }
    if (D_801CEAB0_ovl_1F0A30 == 0x3B && D_801936A7 == 0x20) {
        return 0xFF;
    }
    if (D_801CEAB0_ovl_1F0A30 == 0x2E) {
        return 0xFF;
    }
    if (func_1F8D70_isTintedMap(D_801CEAB0_ovl_1F0A30)) {
        return 0xFF;
    }
    t = D_8018F557 * 128 / 255;
    if (t + 128 >= 0xFF) {
        return 0xFF;
    }
    return t + 128;
}

u8 func_801BC838_ovl_1F0A30(void) {
    s32 t;

    if ((D_801976DA ^ 0x18) == 0) {
        return 0xFF;
    }
    if (D_801CEAB0_ovl_1F0A30 == 0x3B && D_801936A7 == 0x20) {
        return 0x80;
    }
    if (D_801CEAB0_ovl_1F0A30 == 0x2E) {
        return 0xD2;
    }
    if (func_1F8D70_isTintedMap(D_801CEAB0_ovl_1F0A30)) {
        return 0xFF;
    }
    t = D_8018F558 * 128 / 255;
    if (t + 128 >= 0xFF) {
        return 0xFF;
    }
    return t + 128;
}

u8 func_801BC914_ovl_1F0A30(void) {
    s32 t;

    if ((D_801976DA ^ 0x18) == 0) {
        return 0xFF;
    }
    if (D_801CEAB0_ovl_1F0A30 == 0x3B && D_801936A7 == 0x20) {
        return 0x80;
    }
    if (D_801CEAB0_ovl_1F0A30 == 0x2E) {
        return 0;
    }
    if (func_1F8D70_isTintedMap(D_801CEAB0_ovl_1F0A30)) {
        return 0xFF;
    }
    t = D_8018F559 * 128 / 255;
    if (t + 128 >= 0xFF) {
        return 0xFF;
    }
    return t + 128;
}

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
