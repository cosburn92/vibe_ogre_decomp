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
void func_8020D814_ovl_25EE90(void *t);
void func_8020DFB8_ovl_25EE90(void);
void func_8020B1E0_ovl_25EE90(s16 i, void *p, s16 *out);
void func_8020A4A8_ovl_25EE90(void *a, void *b);
s32 func_8020C9B0_ovl_25EE90(s32 a);
void func_8021AC40_ovl_25EE90(u16 msg, u8 *o);
void func_8020FF6C_ovl_25EE90();
extern u8 D_80220980_ovl_25EE90[];
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

/* Common effect message handler: 0x100 spawns effect 0x54, 0x1000/0x1001 run a 12-frame colour fade */
#ifdef NON_MATCHING
/* only the object/effect saved registers are swapped (s0/s1) */
s32 func_8021B500_ovl_25EE90(u16 msg, u8 *o) {
    s16 c[4];
    u8 *e;

    switch (msg) {
        case 0x101:
            func_8020D814_ovl_25EE90(FIELD(o, void *, 0x40));
            func_8020DFB8_ovl_25EE90();
            break;
        case 0x100: {
            u8 *n;

            FIELD(o, s32, 0x44) = D_80220F68_ovl_25EE90;
            n = func_80217460_ovl_25EE90(0x54);
            FIELD(o, u8 *, 0x40) = n;
            FIELD(n, s32, 0x10) = FIELD(o, s32, 0x44);
            FIELD(FIELD(o, u8 *, 0x40), u16, 0xA) |= 0x2000;
            FIELD(o, s16, 0x4C) = 0x40;
            FIELD(o, s16, 0x4E) = 0xFF;
            FIELD(o, s16, 0x50) = 0x80;
            FIELD(o, s16, 0x52) = 0;
            func_8020DC80_ovl_25EE90(0x1000);
            break;
        }
        case 0x1000:
            FIELD(o, s16, 0x4A) = 12;
            FIELD(o, s16, 0x48) = 0;
            FIELD(o, s16, 0x54) = 0xFF;
            FIELD(o, s16, 0x56) = 0xFF;
            FIELD(o, s16, 0x58) = 0xFF;
            FIELD(o, s16, 0x5A) = 0xFF;
            FIELD(o, s32, 0x5C) = 0;
            func_8020DC80_ovl_25EE90(0x1001);
            /* fallthrough */
        case 0x1001:
            e = FIELD(o, u8 *, 0x40);
            func_8020B1E0_ovl_25EE90(FIELD(o, s16, 0x48), o + 0x4A, c);
            FIELD(e, s16, 0x60) = c[0];
            FIELD(e, s16, 0x62) = c[1];
            FIELD(e, s16, 0x64) = c[2];
            e += 0x1C;
            if (FIELD(o, s32, 0x5C) == 0) {
                func_8020A4A8_ovl_25EE90(o, e);
                FIELD(o, s32, 0x5C)++;
            } else if (FIELD(o, s32, 0x5C) == 1) {
                FIELD(FIELD(o, u8 *, 0x40), u16, 8) &= ~1;
                FIELD(o, s32, 0x5C)++;
            }
            FIELD(e, f32, 0x40) = c[3] / 255.0f;
            if (++FIELD(o, s16, 0x48) > FIELD(o, s16, 0x4A)) {
                func_8020DC80_ovl_25EE90(0x101);
            }
            break;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021B500_ovl_25EE90);
#endif

void func_8021B6C4_ovl_25EE90(s32 a) {
    D_80220F68_ovl_25EE90 = a;
    func_8020DF00_ovl_25EE90(func_8021B500_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021B6F0_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021B8D8_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021BA3C_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021C044_ovl_25EE90);

void func_8021C360_ovl_25EE90(u16 msg, u8 *o) {
    s32 r;
    u32 i;
    u8 *e;

    if (msg == 0) {
        r = func_8020C9B0_ovl_25EE90(3);
        for (i = 0; i < FIELD(FIELD(o, u8 *, 0x50), u32, 4); i++) {
            if (FIELD(o, u8 **, 0x58)[i] != NULL) {
                FIELD(FIELD(o, u8 **, 0x58)[i], void *, 0) = func_8020FF6C_ovl_25EE90;
                e = FIELD(o, u8 **, 0x58)[i];
                FIELD(e, s32, 0x34) = r;
                FIELD(e, u8 *, 0x30) = D_80220980_ovl_25EE90;
                FIELD(e, s16, 0x3A) = 0;
                FIELD(e, s16, 0x38) = 0;
                FIELD(e, s16, 0x3E) = 0xF;
                FIELD(e, s16, 0x3C) = 0xF;
                FIELD(e, s16, 0x42) = 0;
                FIELD(e, s16, 0x40) = 0;
                FIELD(e, s16, 0x46) = 0xF;
                FIELD(e, s16, 0x44) = 0xF;
            }
        }
    } else {
        func_8021AC40_ovl_25EE90(msg, o);
    }
}

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
