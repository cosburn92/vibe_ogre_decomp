#include "common.h"

/* 27A020 */

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

typedef struct {
    /* 0x00 */ u8 unk00[1];
    /* 0x01 */ u8 flags;
    /* 0x02 */ u8 members[5];
    /* 0x07 */ u8 unk07[0x12];
} SquadRec; /* size 0x19 */

typedef struct Task27 {
    /* 0x00 */ u8 unk00[4];
    /* 0x04 */ s16 h4;
    /* 0x06 */ u16 next;
    /* 0x08 */ void (*fn)(s32, struct Task27 *);
    /* 0x0C */ s16 hC;
    /* 0x0E */ s16 hE;
    /* 0x10 */ s16 h10;
    /* 0x12 */ u8 unk12[0x26];
} Task27; /* size 0x38 */

typedef struct {
    /* 0x00 */ u8 unk00[0x18];
    /* 0x18 */ s32 *w18;
    /* 0x1C */ s16 h1C;
    /* 0x1E */ s16 h1E;
    /* 0x20 */ u8 *w20;
    /* 0x24 */ u8 *w24;
    /* 0x28 */ s16 h28;
} Obj27;

typedef struct {
    u8 unk00[0x4C];
    s32 w4C;
} Unit27;

extern Gfx *D_800E9BA0;
extern u8 D_801976DC;
extern SquadRec gSquads[];
extern Unit27 *D_8022D134_ovl_27A020[];
extern s32 D_8022D150_ovl_27A020[];
extern void *D_8022C890_ovl_27A020;
extern u16 D_8022D0F0_ovl_27A020;
extern Task27 *D_8022D148_ovl_27A020;
extern Obj27 *D_8022CB20_ovl_27A020;

void *HFree(void *p);
s32 func_8016E1DC(s32 a, s32 b);
void func_80226980_ovl_27A020(void);
void func_801CBF44(void);
s32 func_802283C0_ovl_27A020(void);
void func_8022B5EC_ovl_27A020(s32 a, Task27 *t);
void func_8022A488_ovl_27A020(Obj27 *o);
void func_8022A2A8_ovl_27A020(Obj27 *o);
/* --- end decls --- */

/* Member id of the current squad's slot, made relative to 99 (0 for ids below 100) */
s32 func_80225890_ovl_27A020(s16 slot) {
    SquadRec *sq = &gSquads[D_801976DC];
    u8 m = sq->members[slot];

    if (m < 100) {
        return 0;
    }
    return m - 99;
}

s32 func_802258DC_ovl_27A020(s16 i) {
    if (D_8022D134_ovl_27A020[i]->w4C == 1) {
        return func_8016E1DC(1, 1);
    }
    return D_8022D150_ovl_27A020[i];
}

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022592C_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_80225AAC_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_80225B90_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_80225CF8_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_802264B4_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_80226644_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_802267F8_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_80226980_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_80226A24_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_80226B5C_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_80226CC0_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_80226DA8_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_80227130_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_802283C0_ovl_27A020);

s16 func_8022857C_ovl_27A020(void) {
    func_80226980_ovl_27A020();
    func_801CBF44();
    return func_802283C0_ovl_27A020();
}

INCLUDE_ASM("asm/nonmatchings/27A020", func_802285B0_ovl_27A020);

void func_80228650_ovl_27A020(void) {
    if (D_8022C890_ovl_27A020 != NULL) {
        HFree(D_8022C890_ovl_27A020);
        D_8022C890_ovl_27A020 = NULL;
    }
}

INCLUDE_ASM("asm/nonmatchings/27A020", func_80228680_ovl_27A020);

/* Takes a task from the free list and starts it with message 0x10 */
Task27 *func_8022874C_ovl_27A020(void (*fn)(s32, Task27 *)) {
    Task27 *t = NULL;

    if (D_8022D0F0_ovl_27A020 != 0xFFFF) {
        t = &D_8022D148_ovl_27A020[D_8022D0F0_ovl_27A020];
        D_8022D0F0_ovl_27A020 = t->next;
    }
    if (t != NULL) {
        t->fn = fn;
        t->h10 = 0;
        fn(0x10, t);
    }
    return t;
}

void func_802287C0_ovl_27A020(Task27 *t) {
    t->fn = NULL;
    t->h10 = 0;
    t->next = D_8022D0F0_ovl_27A020;
    D_8022D0F0_ovl_27A020 = t - D_8022D148_ovl_27A020;
}

void func_8022881C_ovl_27A020(Task27 *t, s16 a) {
    t->hE = -1;
    t->hC = a;
    t->h4 = 0;
    t->h10 = 1;
}

void func_80228838_ovl_27A020(Task27 *t) {
    t->hE = 0;
    t->h10 = 0;
}

INCLUDE_ASM("asm/nonmatchings/27A020", func_80228844_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_802288C0_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_80228B7C_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_80228D1C_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_80228EFC_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_802291A0_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_802293B4_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_802297D8_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022A120_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022A2A8_ovl_27A020);

/* Shared rodata after "Yes" that splat leaves unmigrated */
__asm__(".section .rodata\n"
        ".global D_8022D094_ovl_27A020\nD_8022D094_ovl_27A020:\n.asciz \"No\"\n.align 2\n"
        ".global D_8022D098_ovl_27A020\nD_8022D098_ovl_27A020:\n.word 0, 0\n"
        ".global D_8022D0A0_ovl_27A020\nD_8022D0A0_ovl_27A020:\n.half 0x1E, 0xF0, 0, 0xF0, 0, 0, 0, 0\n"
        ".section .text\n");

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022A488_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022A750_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022A95C_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022AAA4_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022AC5C_ovl_27A020);

void func_8022AFCC_ovl_27A020(Obj27 *o) {
    *o->w18 = 0;
    o->h1C = 0;
    o->h1E ^= o->h1E;
}

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022AFE8_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022B1D8_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022B36C_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022B494_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022B560_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022B5EC_ovl_27A020);

void func_8022BC08_ovl_27A020(void) {
    func_8022874C_ovl_27A020(func_8022B5EC_ovl_27A020);
}

s16 func_8022BC28_ovl_27A020(Obj27 *o) {
    return o->h28;
}

void func_8022BC30_ovl_27A020(void) {
    Obj27 *o = D_8022CB20_ovl_27A020;
    Gfx *g = D_800E9BA0;

    g->w0 = 0xFA000000;
    D_800E9BA0 = g + 1;
    g->w1 = o->w20[0x19] | 0xFFFFFF00;
    func_8022A488_ovl_27A020(o);
}

void func_8022BC80_ovl_27A020(void) {
    Obj27 *o = D_8022CB20_ovl_27A020;
    Gfx *g = D_800E9BA0;

    g->w0 = 0xFA000000;
    D_800E9BA0 = g + 1;
    g->w1 = o->w24[0x19] | 0xFFFFFF00;
    func_8022A2A8_ovl_27A020(o);
}

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022BCD0_ovl_27A020);
