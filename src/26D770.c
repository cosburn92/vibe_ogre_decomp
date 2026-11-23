#include "common.h"

/* 26D770 */

typedef struct {
    u8 unk00[0x3C];
    s32 w3C;
    s32 w40;
    s32 w44;
    s32 w48;
    s32 w4C;
    s32 w50;
} Task26D;

extern s32 D_80220F68_ovl_25EE90;

Task26D *func_8020DF00_ovl_25EE90(void *fn);
void func_80219140_ovl_25EE90(void);
s32 func_8021A57C_ovl_25EE90(u16 msg, u8 *o);
void func_80219A9C_ovl_25EE90(void);
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
u8 *func_80217460_ovl_25EE90(s32 id);
void func_8020DC80_ovl_25EE90(u16 state);
s32 func_8021B500_ovl_25EE90(u16 msg, u8 *o);
/* --- end decls --- */

u8 *func_8020E570_ovl_25EE90(void *fn, s32 a);
void func_802118D4_ovl_25EE90();
void func_80212200_ovl_25EE90();
void func_80212488_ovl_25EE90();
void func_80210410_ovl_25EE90(s32 id, u8 *out);
void func_8020A980_ovl_25EE90(void *a, void *b, u8 *out);
void func_8020A5A0_ovl_25EE90(u8 *m, void *pos);
void func_8020A4A8_ovl_25EE90(u8 *src, u8 *dst, s32 n);
void func_80098D00(void *mf, f32 x, f32 y, f32 z);
s32 func_8020AB8C_ovl_25EE90(s32 a);
u8 *func_80214EB4_ovl_25EE90(s32 id, s32 a, s32 b, s32 c, s32 d);
void bzero(void *p, s32 n);
extern u8 D_802206DC_ovl_25EE90[];
extern u8 D_802206D0_ovl_25EE90[];
extern u8 D_802206A0_ovl_25EE90[];

/* Sets up the parts of effect o: billboard sprite (frames from o+0x40), its shadow, a positioned
 * marker and the 0x22 particle animation */
void func_80218BC0_ovl_25EE90(u8 *o) {
    u8 *s;
    u8 *m;
    u8 *p;

    FIELD(o, u8 *, 0x14) = func_8020E570_ovl_25EE90(func_802118D4_ovl_25EE90, 1);
    FIELD(FIELD(o, u8 *, 0x14), f32, 8) = 1000.0f;
    s = FIELD(o, u8 *, 0x14);
    func_80210410_ovl_25EE90(FIELD(o, s32, 0x40), s + 0x64);
    FIELD(s, s16, 0x5A) = 0x20;
    FIELD(s, s16, 0x5C) = 2;
    FIELD(s, s16, 0x5E) = FIELD(s, u16, 0x68) >> 1;
    FIELD(s, s16, 0x60) = FIELD(s, u16, 0x6A) >> 1;
    m = s + 0x14;
    FIELD(s, s16, 0x56) = FIELD(o, s32, 0);
    FIELD(s, u16, 0x58) = FIELD(o, s32, 0x3C);
    FIELD(s, s16, 0x62) = 1;
    func_8020A980_ovl_25EE90(D_802206DC_ovl_25EE90, D_802206D0_ovl_25EE90, m);
    func_8020A5A0_ovl_25EE90(m, o + 8);
    FIELD(o, u8 *, 0x18) = p = func_8020E570_ovl_25EE90(func_80212200_ovl_25EE90, 1);
    {
        s32 n;

        FIELD(p, s16, 0x58) = 0;
        FIELD(p, s16, 0x5A) = 0;
        n = FIELD(s, u16, 0x58) - 2;
        FIELD(p, s16, 0x5E) = 0x20;
        p[0x56] = 0;
        p[0x55] = 0;
        p[0x54] = 0;
        p[0x57] = 0xFF;
        FIELD(p, s16, 0x5C) = n;
        func_8020A4A8_ovl_25EE90(m, p + 0x14, n);
    }
    FIELD(o, u8 *, 0x1C) = p = func_8020E570_ovl_25EE90(func_80212488_ovl_25EE90, 0);
    func_80098D00(p + 0x14, FIELD(o, f32, 8), FIELD(o, f32, 0xC), FIELD(o, f32, 0x10));
    FIELD(p, u8 *, 0x54) = D_802206A0_ovl_25EE90;
    {
        s32 n = func_8020AB8C_ovl_25EE90(FIELD(o, s32, 0x34));

        FIELD(o, u8 *, 0x20) = p = func_80214EB4_ovl_25EE90(0x22, 8, n, 8, n);
    }
    FIELD(p, u16, 0xA) |= 0x4000;
    bzero(FIELD(o, u8 *, 0x20) + 0x1C, 0x10);
    FIELD(o, f32, 0x28) = FIELD(o, f32, 0x2C) = FIELD(o, f32, 0x30) = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/26D770", func_80218D68_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26D770", func_80219140_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26D770", func_8021965C_ovl_25EE90);

/* Effect message handler: spawns effect 0x37 with colour (A, B, C, D) */
s32 func_80219970_ovl_25EE90(u16 msg, u8 *o) {
    s32 r = 0;

    if (msg == 0x100) {
        u8 *e;

        FIELD(o, s32, 0x44) = D_80220F68_ovl_25EE90;
        e = func_80217460_ovl_25EE90(0x37);
        FIELD(o, u8 *, 0x40) = e;
        FIELD(e, s32, 0x10) = FIELD(o, s32, 0x44);
        FIELD(FIELD(o, u8 *, 0x40), u16, 0xA) |= 0x2000;
        FIELD(o, s16, 0x4C) = 0x20;
        FIELD(o, s16, 0x4E) = 0xC8;
        FIELD(o, s16, 0x50) = 0xFF;
        FIELD(o, s16, 0x52) = 0x3C;
        func_8020DC80_ovl_25EE90(0x1000);
    } else {
        r = func_8021B500_ovl_25EE90(msg, o);
    }
    return r;
}

void func_80219A18_ovl_25EE90(s16 a, s32 b, s32 c) {
    Task26D *t = func_8020DF00_ovl_25EE90(func_80219140_ovl_25EE90);

    t->w48 = b;
    t->w4C = c;
    t->w50 = a;
}

void func_80219A70_ovl_25EE90(s32 a) {
    D_80220F68_ovl_25EE90 = a;
    func_8020DF00_ovl_25EE90(func_8021A57C_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/26D770", func_80219A9C_ovl_25EE90);

void func_8021A210_ovl_25EE90(s16 a, s32 b, s32 c) {
    Task26D *t = func_8020DF00_ovl_25EE90(func_80219A9C_ovl_25EE90);

    t->w3C = b;
    t->w40 = c;
    t->w44 = a;
}

INCLUDE_ASM("asm/nonmatchings/26D770", func_8021A268_ovl_25EE90);

/* Effect message handler: spawns effect 0x45 with colour (A, B, C, D) */
s32 func_8021A57C_ovl_25EE90(u16 msg, u8 *o) {
    s32 r = 0;

    if (msg == 0x100) {
        u8 *e;

        FIELD(o, s32, 0x44) = D_80220F68_ovl_25EE90;
        e = func_80217460_ovl_25EE90(0x45);
        FIELD(o, u8 *, 0x40) = e;
        FIELD(e, s32, 0x10) = FIELD(o, s32, 0x44);
        FIELD(FIELD(o, u8 *, 0x40), u16, 0xA) |= 0x2000;
        FIELD(o, s16, 0x4C) = 0x10;
        FIELD(o, s16, 0x4E) = 0xFF;
        FIELD(o, s16, 0x50) = 0xC8;
        FIELD(o, s16, 0x52) = 0x40;
        func_8020DC80_ovl_25EE90(0x1000);
    } else {
        r = func_8021B500_ovl_25EE90(msg, o);
    }
    return r;
}
