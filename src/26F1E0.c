#include "common.h"

/* 26F1E0 */

typedef struct {
    u8 unk00[0x3C];
    s32 w3C;
    s32 w40;
    s32 w44;
    s32 w48;
} Task26F;

extern s32 D_80220F68_ovl_25EE90;
extern s32 D_80220F6C_ovl_25EE90;

void func_8021A630_ovl_25EE90(void);
s32 func_8021D168_ovl_25EE90(u16 msg, u8 *o);
void func_8021C62C_ovl_25EE90(void);
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void *func_8020DF00_ovl_25EE90(void *fn);
s32 func_801F7128(u8 c);
void func_8021BA3C_ovl_25EE90();
u8 *func_80217460_ovl_25EE90(s32 id);
void func_8020DC80_ovl_25EE90(u16 state);
s32 func_8021B500_ovl_25EE90(u16 msg, u8 *o);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021A630_ovl_25EE90);

void func_8021A998_ovl_25EE90(s32 a, s32 b) {
    D_80220F68_ovl_25EE90 = a;
    D_80220F6C_ovl_25EE90 = b;
    func_8020DF00_ovl_25EE90(func_8021A630_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021A9C8_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021AC40_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021ADE0_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021B040_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021B500_ovl_25EE90);

void func_8021B6C4_ovl_25EE90(s32 a) {
    D_80220F68_ovl_25EE90 = a;
    func_8020DF00_ovl_25EE90(func_8021B500_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021B6F0_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021B8D8_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021BA3C_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021C044_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021C360_ovl_25EE90);

/* Starts a task for character c (with two extra parameters and a 16-bit argument) */
u8 *func_8021C440_ovl_25EE90(s16 a, s32 c, s32 b, s32 d) {
    u8 *t = func_8020DF00_ovl_25EE90(func_8021BA3C_ovl_25EE90);

    FIELD(t, s32, 0x3C) = c;
    FIELD(t, s32, 0x40) = b;
    FIELD(t, s32, 0x44) = d;
    FIELD(t, s32, 0x48) = a;
    func_801F7128(c);
    return t;
}

void func_8021C4C0_ovl_25EE90(s32 a) {
    D_80220F68_ovl_25EE90 = a;
    func_8020DF00_ovl_25EE90(func_8021D168_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021C4EC_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021C62C_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021CE60_ovl_25EE90);

s32 func_8021D168_ovl_25EE90(u16 msg, u8 *o) {
    s32 r = 0;

    if (msg == 0x100) {
        u8 *e;

        FIELD(o, s32, 0x44) = D_80220F68_ovl_25EE90;
        e = func_80217460_ovl_25EE90(0x5D);
        FIELD(o, u8 *, 0x40) = e;
        FIELD(e, s32, 0x10) = FIELD(o, s32, 0x44);
        FIELD(FIELD(o, u8 *, 0x40), u16, 0xA) |= 0x2000;
        FIELD(o, s16, 0x4C) = 0x40;
        FIELD(o, s16, 0x4E) = 0x80;
        FIELD(o, s16, 0x50) = 0xFF;
        FIELD(o, s16, 0x52) = 0;
        func_8020DC80_ovl_25EE90(0x1000);
    } else {
        r = func_8021B500_ovl_25EE90(msg, o);
    }
    return r;
}

void func_8021D20C_ovl_25EE90(s16 a, s32 b, s32 c, s32 d) {
    Task26F *t = func_8020DF00_ovl_25EE90(func_8021C62C_ovl_25EE90);

    t->w3C = b;
    t->w40 = c;
    t->w44 = d;
    t->w48 = a;
}
