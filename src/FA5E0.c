#include "common.h"

/* Field access by offset, for widget records whose layouts are not mapped yet. */
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))

typedef struct {
    u8 unk00[0x84];
    s32 x84;
    u8 x88;
    u8 x89;
    u8 x8A;
    u8 x8B;
} Widget3390;
extern Widget3390 *D_801B3390_ovl_0FA5E0;
extern u8 *D_801B3E20_ovl_0FA5E0;
extern s32 D_801B3DE0_ovl_0FA5E0[];
extern u8 D_801B436C_ovl_0FA5E0[];
extern u16 D_800C4C26;
void nuGfxTaskAllEndWait(void);
void func_801AEDEC_ovl_0FA5E0(Widget3390 *p);
void func_801AEE94_ovl_0FA5E0(s32 i, void *v);
void HFree(void *p);





typedef struct {
    /* 0x00 */ u16 active;
    /* 0x02 */ u8 pad02[2];
    /* 0x04 */ s32 a;
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 y;
    /* 0x10 */ f32 f10;
    /* 0x14 */ f32 f14;
    /* 0x18 */ s16 f18;
    /* 0x1A */ s16 f1A;
    /* 0x1C */ u16 f1C[4];
    /* 0x24 */ u8 pad24[8];
    /* 0x2C */ u16 f2C[4];
    /* 0x34 */ s32 f34;
    /* 0x38 */ s32 f38;
    /* 0x3C */ s32 f3C;
    /* 0x40 */ s32 f40;
} Anim0444;
s32 func_8009C7CC(void);
s32 func_801793E4(s32 c, s32 b);
void func_801B01FC_ovl_0FA5E0(u8 *p);
void func_801B2FF8_ovl_0FA5E0(void **p);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801AD5A0_ovl_0FA5E0);

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801AD748_ovl_0FA5E0);

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801ADF6C_ovl_0FA5E0);

void func_801AE090_ovl_0FA5E0(void) {
    nuGfxTaskAllEndWait();
    D_800C4C26 = 0xFFFE;
    func_801AEDEC_ovl_0FA5E0(D_801B3390_ovl_0FA5E0);
}

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801AE0C4_ovl_0FA5E0);

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801AE5BC_ovl_0FA5E0);

void func_801AE79C_ovl_0FA5E0(s32 i) {
    D_801B3390_ovl_0FA5E0->x88 = 1;
    D_801B3390_ovl_0FA5E0->x89 = 0xFF;
    D_801B3390_ovl_0FA5E0->x84 = D_801B3DE0_ovl_0FA5E0[i];
    D_801B3390_ovl_0FA5E0->x8B = 0;
    D_801B3390_ovl_0FA5E0->x8A = 0;
}

void func_801AE7EC_ovl_0FA5E0(void) {
    D_801B3390_ovl_0FA5E0->x88 = 0;
}

s32 func_801AE7FC_ovl_0FA5E0(void) {
    return D_801B3390_ovl_0FA5E0->x88 != 1;
}

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801AE814_ovl_0FA5E0);

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801AEB2C_ovl_0FA5E0);

/* Width of a string in pixels, stopping at '@'; glyph width 11 marks a two-byte character */
#ifdef NON_MATCHING
/* original reloads *s at the loop top; GCC reuses the test load */
s32 func_801AEBA4_ovl_0FA5E0(u8 *s) {
    s32 w = 0;
    u8 c;
    u8 v;

    while (*s != 0) {
        c = *s;
        v = func_801793E4(c, 0);
        if (v == 11) {
            s++;
            w += 11;
        } else {
            if (c == '@') {
                return w;
            }
            w += v;
        }
        s++;
    }
    return w;
}
#else
INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801AEBA4_ovl_0FA5E0);
#endif

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801AEC40_ovl_0FA5E0);

void func_801AED48_ovl_0FA5E0(void) {
    func_801AEE94_ovl_0FA5E0(0, D_801B436C_ovl_0FA5E0);
}

void func_801AED6C_ovl_0FA5E0(u8 *p) {
    u32 i;

    for (i = 0; i < 3; i++) {
        if (FIELD(p, void *, 0x524 + i * 4) != NULL) {
            func_801B2FF8_ovl_0FA5E0(FIELD(p, void *, 0x524 + i * 4));
        }
    }
    for (i = 0; i < 3; i++) {
        if (FIELD(p, void *, 0x530 + i * 4) != NULL) {
            func_801B2FF8_ovl_0FA5E0(FIELD(p, void *, 0x530 + i * 4));
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801AEDEC_ovl_0FA5E0);

void func_801AEE94_ovl_0FA5E0(s32 i, void *v) {
    u8 *p = D_801B3E20_ovl_0FA5E0;

    p += i * 20;
    FIELD(p, s32, 0x214) = 0;
    FIELD(p, void *, 0x218) = v;
    FIELD(p, s16, 0x208) = 1;
}

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801AEEC0_ovl_0FA5E0);

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801AFB94_ovl_0FA5E0);

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801AFD30_ovl_0FA5E0);

void func_801B01FC_ovl_0FA5E0(u8 *p) {
    FIELD(p, s16, 0x20) = 0xFF;
    FIELD(p, s16, 0x1E) = 0xFF;
    FIELD(p, s16, 0x18) = 0xFF;
    FIELD(p, s16, 0x1C) = 0;
    FIELD(p, s16, 0x1A) = 0;
}

void func_801B0218_ovl_0FA5E0(u8 *p, s16 a, s16 b, s16 c) {
    FIELD(p, s16, 0x1E) = b;
    FIELD(p, s16, 0x20) = c;
    FIELD(p, s16, 0x1C) = a;
    FIELD(p, s16, 0x1A) = 0;
}

/* Linear step: out = from + (to - from) * i / n, then i++; holds at `to` once i reaches n */
void func_801B022C_ovl_0FA5E0(u8 *p) {
    s32 pad;

    if (FIELD(p, u16, 0) != 0) {
        if (FIELD(p, s16, 0x1A) < FIELD(p, s16, 0x1C)) {
            FIELD(p, s16, 0x18) = FIELD(p, s16, 0x1E) + (FIELD(p, s16, 0x20) - FIELD(p, s16, 0x1E)) * FIELD(p, s16, 0x1A) / FIELD(p, s16, 0x1C);
            FIELD(p, s16, 0x1A)++;
        } else {
            FIELD(p, s16, 0x18) = FIELD(p, s16, 0x20);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B02C0_ovl_0FA5E0);

void func_801B0444_ovl_0FA5E0(Anim0444 *p, s32 a, f32 x, f32 y, u16 *src) {
    s32 i;

    for (i = 0; i < 4; i++) {
        p->f1C[i] = p->f2C[i] = src[i];
    }
    p->a = a;
    p->x = x;
    p->y = y;
    p->f1A = 0;
    p->f18 = 0;
    p->f34 = 0;
    p->f3C = 0;
    p->f38 = 0;
    p->f40 = 0;
    p->active = 1;
    p->f14 = 1.0f;
    p->f10 = 1.0f;
}

void func_801B04B8_ovl_0FA5E0(u16 *p) {
    if (*p == 1) {
        *p = 0;
    } else if (*p == 2) {
        *p = 0xFFFF;
    }
}

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B04E4_ovl_0FA5E0);

void func_801B05D0_ovl_0FA5E0(u8 *p, s16 a, u16 *x, u16 *y) {
    s32 i;

    for (i = 0; i < 4; i++) {
        FIELD(p, u16, 0x24 + i * 2) = *x++;
        FIELD(p, u16, 0x2C + i * 2) = *y++;
    }
    FIELD(p, s16, 0x18) = 0;
    FIELD(p, s16, 0x1A) = a;
}

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B060C_ovl_0FA5E0);

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B073C_ovl_0FA5E0);

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B09B8_ovl_0FA5E0);

void func_801B0C0C_ovl_0FA5E0(u8 *p, s32 a, s32 b, s32 c, u16 d) {
    FIELD(p, s32, 0xC) = a;
    FIELD(p, s32, 0x4) = b;
    FIELD(p, s32, 0x8) = c;
    FIELD(p, s16, 0x16) = 0;
    FIELD(p, s16, 0x14) = 0;
    FIELD(p, s16, 0x12) = 0;
    FIELD(p, s16, 0x0) = 1;
    FIELD(p, u16, 0x18) = d;
    FIELD(p, u16, 0x10) = d;
}

void func_801B0C3C_ovl_0FA5E0(u8 *p, s16 a, s16 b, s16 c) {
    FIELD(p, s16, 0x12) = 0;
    FIELD(p, s16, 0x14) = a;
    FIELD(p, s16, 0x16) = b;
    FIELD(p, s16, 0x18) = c;
}

void func_801B0C50_ovl_0FA5E0(u8 *p) {
    s32 pad;

    if (FIELD(p, u16, 0) != 0) {
        if (FIELD(p, s16, 0x12) < FIELD(p, s16, 0x14)) {
            FIELD(p, s16, 0x10) = FIELD(p, s16, 0x16) + (FIELD(p, s16, 0x18) - FIELD(p, s16, 0x16)) * FIELD(p, s16, 0x12) / FIELD(p, s16, 0x14);
            FIELD(p, s16, 0x12)++;
        } else {
            FIELD(p, s16, 0x10) = FIELD(p, s16, 0x18);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B0CE4_ovl_0FA5E0);

void func_801B0E48_ovl_0FA5E0(u8 *p, s32 a, s32 b) {
    s32 pad[4];

    FIELD(p, s16, 0x14) = 0xFF;
    FIELD(p, s16, 0x12) = 0xFF;
    FIELD(p, s16, 0xC) = 0xFF;
    FIELD(p, u16, 0) = 1;
    FIELD(p, s32, 4) = a;
    FIELD(p, s32, 8) = b;
    FIELD(p, s16, 0x10) = 0;
    FIELD(p, s16, 0xE) = 0;
    FIELD(p, s16, 0x18) = 10;
    func_8009C7CC();
    func_8009C7CC();
    FIELD(p, s16, 0x16) = func_8009C7CC() & 0xF;
    FIELD(p, s16, 0x1A) = 0;
}

void func_801B0EB8_ovl_0FA5E0(u8 *p, s16 a, s16 b, s16 c) {
    FIELD(p, s16, 0xE) = 0;
    FIELD(p, s16, 0x10) = a;
    FIELD(p, s16, 0x12) = b;
    FIELD(p, s16, 0x14) = c;
}

void func_801B0ECC_ovl_0FA5E0(u8 *p) {
    s32 pad;

    if (FIELD(p, u16, 0) != 0) {
        if (FIELD(p, s16, 0xE) < FIELD(p, s16, 0x10)) {
            FIELD(p, s16, 0xC) = FIELD(p, s16, 0x12) + (FIELD(p, s16, 0x14) - FIELD(p, s16, 0x12)) * FIELD(p, s16, 0xE) / FIELD(p, s16, 0x10);
            FIELD(p, s16, 0xE)++;
        } else {
            FIELD(p, s16, 0xC) = FIELD(p, s16, 0x14);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B0F60_ovl_0FA5E0);

void func_801B1250_ovl_0FA5E0(u8 *p, s32 a, s32 b) {
    FIELD(p, s16, 0x16) = 4;
    FIELD(p, s16, 0x14) = 0xFF;
    FIELD(p, s16, 0x12) = 0xFF;
    FIELD(p, s16, 0xC) = 0xFF;
    FIELD(p, s16, 0x18) = 0;
    FIELD(p, s16, 0x10) = 0;
    FIELD(p, s16, 0xE) = 0;
    FIELD(p, s32, 0x4) = a;
    FIELD(p, s32, 0x8) = b;
    FIELD(p, s16, 0x0) = 1;
}

void func_801B1288_ovl_0FA5E0(u8 *p, s16 a, s16 b, s16 c) {
    FIELD(p, s16, 0xE) = 0;
    FIELD(p, s16, 0x10) = a;
    FIELD(p, s16, 0x12) = b;
    FIELD(p, s16, 0x14) = c;
}

void func_801B129C_ovl_0FA5E0(u8 *p) {
    s32 pad;

    if (FIELD(p, u16, 0) != 0) {
        if (FIELD(p, s16, 0xE) < FIELD(p, s16, 0x10)) {
            FIELD(p, s16, 0xC) = FIELD(p, s16, 0x12) + (FIELD(p, s16, 0x14) - FIELD(p, s16, 0x12)) * FIELD(p, s16, 0xE) / FIELD(p, s16, 0x10);
            FIELD(p, s16, 0xE)++;
        } else {
            FIELD(p, s16, 0xC) = FIELD(p, s16, 0x14);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B1330_ovl_0FA5E0);

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B15BC_ovl_0FA5E0);

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B18AC_ovl_0FA5E0);

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B1AF0_ovl_0FA5E0);

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B1CC0_ovl_0FA5E0);

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B1FD8_ovl_0FA5E0);

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B2664_ovl_0FA5E0);

INCLUDE_RODATA("asm/nonmatchings/FA5E0", D_801B4C78_ovl_0FA5E0);

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B2854_ovl_0FA5E0);

void func_801B2CC0_ovl_0FA5E0(u8 *p, s16 a, u16 *x, u16 *y) {
    s32 i;

    for (i = 0; i < 4; i++) {
        FIELD(p, u16, 0x94 + i * 2) = *x++;
        FIELD(p, u16, 0x9C + i * 2) = *y++;
    }
    FIELD(p, s16, 0x88) = 0;
    FIELD(p, s16, 0x8A) = a;
}

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B2CFC_ovl_0FA5E0);

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B2DBC_ovl_0FA5E0);

void func_801B2FF8_ovl_0FA5E0(void **p) {
    HFree(p[0]);
    HFree(p[1]);
    HFree(p[2]);
    HFree(p);
}

void func_801B3038_ovl_0FA5E0(u8 *p, s32 v) {
    FIELD(p, s32, 0x50) = v;
}

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B3040_ovl_0FA5E0);

s32 func_801B3258_ovl_0FA5E0(void) {
    u8 *q = D_801B3E20_ovl_0FA5E0;
    s32 r = 0;

    if (FIELD(q, u16, 0x444) && FIELD(q, u16, 0x460)) {
        r = FIELD(q, u16, 0x47C) != 0;
    }
    return r;
}

s32 func_801B3288_ovl_0FA5E0(void) {
    u8 *q = D_801B3E20_ovl_0FA5E0;
    s32 r = 0;

    if (FIELD(q, s32, 0x298) < 130) {
        FIELD(q, s32, 0x298)++;
    } else {
        r = 1;
    }
    return r;
}

s32 func_801B32B8_ovl_0FA5E0(void) {
    u8 *p = D_801B3E20_ovl_0FA5E0;
    s32 r = 0;

    if (FIELD(p, s32, 0x2E4) < 120) {
        FIELD(p, s32, 0x2E4) += 2;
    } else {
        r = 1;
    }
    return r;
}

s32 func_801B32E8_ovl_0FA5E0(void) {
    u8 *p = D_801B3E20_ovl_0FA5E0;

    func_801B01FC_ovl_0FA5E0(p + 0x1E4);
    FIELD(p, s16, 0x1E4) = 1;
    FIELD(p, s32, 0x1F8) = 0;
    FIELD(p, s32, 0x1EC) = 0;
    FIELD(p, s32, 0x1F4) = 0;
    FIELD(p, s32, 0x1E8) = 0;
    FIELD(p, f32, 0x1F0) = 15.0f;
    return 1;
}

s32 func_801B333C_ovl_0FA5E0(void) {
    return FIELD(D_801B3E20_ovl_0FA5E0, s16, 0x4CC) == 0;
}

s32 func_801B3350_ovl_0FA5E0(void) {
    return FIELD(D_801B3E20_ovl_0FA5E0, s16, 0x4CC) != 0;
}

s32 func_801B3364_ovl_0FA5E0(void) {
    return FIELD(D_801B3E20_ovl_0FA5E0, s16, 0x4E8) == 0;
}

s32 func_801B3378_ovl_0FA5E0(void) {
    return FIELD(D_801B3E20_ovl_0FA5E0, s16, 0x4E8) != 0;
}

INCLUDE_RODATA("asm/nonmatchings/FA5E0", D_801B4C90_ovl_0FA5E0);
