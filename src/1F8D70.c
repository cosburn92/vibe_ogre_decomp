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
/* Battle-screen state block (0xA0 bytes at D_801D0770) */
typedef struct {
    /* 0x00 */ u8 *spr;
    /* 0x04 */ u8 unk04[0x2C];
    /* 0x30 */ u8 *spr2;
    /* 0x34 */ u8 unk34[0x2C];
    /* 0x60 */ u8 *units;   /* 0x64 each */
    /* 0x64 */ u32 nUnits;
    /* 0x68 */ u8 *objs;    /* 0xF8 each */
    /* 0x6C */ void *buf6C;
    /* 0x70 */ u32 nObjs;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ void *buf78;
    /* 0x7C */ void *buf7C;
    /* 0x80 */ void *buf80;
    /* 0x84 */ u8 unk84[0x1C];
} State1F8; /* size 0xA0 */
extern State1F8 D_801D0770_ovl_1F0A30;
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
/* 0x40-byte fixed-point matrix */
typedef struct {
    u8 m[0x40];
} Mtx1F8;
extern Mtx1F8 *D_801969B0; /* matrix pool pointer */
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
        func_801B7284_ovl_1F0A30(img, -160, -120, 2, b, &D_801969B0, a);
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
inline void func_801B7CBC_ovl_1F0A30(u8 *p) {
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

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif

/* Sprite part: offset, size, link to the next part */
typedef struct SprPart1F8 {
    s16 x;
    s16 y;
    u16 w;
    u16 h;
    u8 unk8[4];
    struct SprPart1F8 *next;
} SprPart1F8;

/* Current sprite header: "64" sprites are one centred w x h image (u16 at +4/+6), the others a
 * list of [3] parts starting at +8 */
#define CUR_SPR (D_801D0770_ovl_1F0A30.spr)

/* Bounding box of the current sprite's parts */
static inline void Spr1F8_PartsBox(s32 *r) {
    u8 *s = CUR_SPR;
    SprPart1F8 *p;
    s32 i;

    r[0] = 9999;
    r[1] = 9999;
    r[2] = -9999;
    r[3] = -9999;
    p = (SprPart1F8 *)(s + 8);
    for (i = 0; i < s[3]; i++) {
        if (p->x < r[0]) {
            r[0] = p->x;
        }
        if (r[2] < p->x + p->w) {
            r[2] = p->x + p->w;
        }
        if (p->y < r[1]) {
            r[1] = p->y;
        }
        if (r[3] < p->y + p->h) {
            r[3] = p->y + p->h;
        }
        p = p->next;
    }
}

/* Bounding box (x0, y0, x1, y1) of the current sprite, all zero when there is none */
void func_801B7D54_ovl_1F0A30(s32 *r) {
    u8 *s = CUR_SPR;

    if (s == NULL) {
        r[0] = 0;
        r[1] = 0;
        r[2] = 0;
        r[3] = 0;
    } else if (CUR_SPR[0] == '6' && CUR_SPR[1] == '4') {
        r[0] = -FIELD(s, u16, 4) / 2;
        r[2] = FIELD(s, u16, 4) >> 1;
        r[1] = -FIELD(s, u16, 6) / 2;
        r[3] = FIELD(s, u16, 6) >> 1;
    } else {
        Spr1F8_PartsBox(r);
    }
}

/* 16 zero bytes in rodata (emitted from asm: gcc loses track of the section after INCLUDE_ASM) */
__asm__(".section .rodata
.global D_801D0178_ovl_1F0A30
D_801D0178_ovl_1F0A30:
.word 0, 0, 0, 0
.section .text
");

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B7E9C_ovl_1F0A30);

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void guOrtho(void *m, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, f32 scale);
void func_80098C20(void *m, f32 x, f32 y, f32 z); /* guTranslate */
void func_80098AA0(void *m, f32 x, f32 y, f32 z); /* guScale */
void guRotateRPY(void *m, f32 r, f32 p, f32 y);

typedef struct {
    u32 w0;
    u32 w1;
} Gfx1F8;

/* Loads the projection (ortho 320x240) and o's translate/scale/rotate model matrices */
/* Appends a matrix command for the next matrix of the pool */
static inline void Mtx1F8_Push(u32 w0) {
    Gfx1F8 *g = D_800E9BA0;

    D_800E9BA0 = g + 1;
    g->w0 = w0;
    g->w1 = (u32)D_801969B0++;
}

/* Loads the projection (ortho 320x240) and o's translate/scale/rotate model matrices */
void func_801B8F2C_ovl_1F0A30(u8 *o) {
    Gfx1F8 *g;

    g = D_800E9BA0;
    D_800E9BA0 = g + 1;
    g->w0 = 0xE7000000;
    g->w1 = 0;
    guOrtho(D_801969B0, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);
    func_80098C20(D_801969B0 + 1, FIELD(o, f32, 4), FIELD(o, f32, 8), FIELD(o, f32, 0xC));
    func_80098AA0(D_801969B0 + 2, FIELD(o, f32, 0x1C), FIELD(o, f32, 0x20), FIELD(o, f32, 0x24));
    guRotateRPY(D_801969B0 + 3, FIELD(o, f32, 0x10), FIELD(o, f32, 0x14), FIELD(o, f32, 0x18));
    Mtx1F8_Push(0xDA380007);
    Mtx1F8_Push(0xDA380003);
    Mtx1F8_Push(0xDA380001);
    Mtx1F8_Push(0xDA380001);
}

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B90A8_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801B9698_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BA0DC_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BAA38_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BB58C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F8D70", func_801BB87C_ovl_1F0A30);

void func_801ADB00_ovl_1F0A30(s32 o);
void func_801C24F8_ovl_1F0A30(s32 a, u16 b);

/* Frees everything the battle screen allocated and clears its state */
void func_801BBC78_ovl_1F0A30(void) {
    u32 i;

    func_801BD1F4_ovl_1F0A30();
    func_801B7CBC_ovl_1F0A30(D_801D0770_ovl_1F0A30.spr);
    func_801B7CBC_ovl_1F0A30(D_801D0770_ovl_1F0A30.spr2);
    HFree(D_801D0770_ovl_1F0A30.buf78);
    HFree(D_801D0770_ovl_1F0A30.buf7C);
    HFree(D_801D0770_ovl_1F0A30.buf80);
    for (i = 0; i < D_801D0770_ovl_1F0A30.nObjs; i++) {
        func_801ADB00_ovl_1F0A30(*(s32 *)(D_801D0770_ovl_1F0A30.objs + i * 0xF8));
    }
    HFree(D_801D0770_ovl_1F0A30.objs);
    HFree(D_801D0770_ovl_1F0A30.buf6C);
    for (i = 0; i < D_801D0770_ovl_1F0A30.nUnits; i++) {
        func_801C24F8_ovl_1F0A30(FIELD(D_801D0770_ovl_1F0A30.units + i * 0x64, s32, 0x14), FIELD(D_801D0770_ovl_1F0A30.units + i * 0x64, u16, 6));
    }
    HFree(D_801D0770_ovl_1F0A30.units);
    bzero(&D_801D0770_ovl_1F0A30, sizeof(State1F8));
}

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
    bzero(&D_801D0770_ovl_1F0A30, 0xA0);
    bzero(D_801D0748_ovl_1F0A30, 0x1C);
    bzero(D_801D0828_ovl_1F0A30, 5);
}

/* Two light/fog parameter blocks (0x30 bytes each) at D_801D0774 */
typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 dir[3];
    /* 0x18 */ f32 scale[3];
    /* 0x24 */ u8 rgba[4];
    /* 0x28 */ s32 on;
    /* 0x2C */ u8 unk2C[4];
} Light1F8;
extern Light1F8 D_801D0774_ovl_1F0A30[2];

/* Resets both light blocks and the 0x1A-byte state at D_801D07F4 */
void func_801BC640_ovl_1F0A30(void) {
    D_801D0774_ovl_1F0A30[0].rgba[0] = D_801D0774_ovl_1F0A30[0].rgba[1] = D_801D0774_ovl_1F0A30[0].rgba[2] = D_801D0774_ovl_1F0A30[0].rgba[3] = 0xFF;
    D_801D0774_ovl_1F0A30[0].on = 1;
    D_801D0774_ovl_1F0A30[1].rgba[0] = D_801D0774_ovl_1F0A30[1].rgba[1] = D_801D0774_ovl_1F0A30[1].rgba[2] = D_801D0774_ovl_1F0A30[1].rgba[3] = 0xFF;
    D_801D0774_ovl_1F0A30[1].on = 1;
    D_801D0774_ovl_1F0A30[0].pos[0] = D_801D0774_ovl_1F0A30[0].pos[1] = 0.0f;
    D_801D0774_ovl_1F0A30[0].dir[0] = D_801D0774_ovl_1F0A30[0].dir[1] = D_801D0774_ovl_1F0A30[0].dir[2] = 0.0f;
    D_801D0774_ovl_1F0A30[1].pos[0] = D_801D0774_ovl_1F0A30[1].pos[1] = 0.0f;
    D_801D0774_ovl_1F0A30[1].dir[0] = D_801D0774_ovl_1F0A30[1].dir[1] = D_801D0774_ovl_1F0A30[1].dir[2] = 0.0f;
    D_801D0774_ovl_1F0A30[0].pos[2] = -5.0f;
    D_801D0774_ovl_1F0A30[0].scale[0] = D_801D0774_ovl_1F0A30[0].scale[1] = D_801D0774_ovl_1F0A30[0].scale[2] = 1.0f;
    D_801D0774_ovl_1F0A30[1].pos[2] = -905.0f;
    D_801D0774_ovl_1F0A30[1].scale[0] = D_801D0774_ovl_1F0A30[1].scale[1] = D_801D0774_ovl_1F0A30[1].scale[2] = 1.0f;
    bzero(&D_801D07F4_ovl_1F0A30, 0x1A);
}

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
    return (s32)D_801D0770_ovl_1F0A30.spr;
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
