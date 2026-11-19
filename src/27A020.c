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
    /* 0x04 */ u16 state; /* >= 0x10: callback runs; 0: idle timer */
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
extern s16 D_8022D0F2_ovl_27A020;
extern void *D_8022D100_ovl_27A020;
extern void *D_8022D104_ovl_27A020;
extern void *D_8022D108_ovl_27A020;
extern void *D_8022D10C_ovl_27A020;
extern void *D_8022D110_ovl_27A020;
extern void *D_8022D114_ovl_27A020;
extern void *D_8022D118_ovl_27A020;
extern void *D_8022D11C_ovl_27A020;
extern void *D_8022D120_ovl_27A020;
extern s32 D_800C6D60;
extern s8 *D_800C47F0[];
extern u16 D_800E9BE4[];
void *HMalloc(s32 size);
void func_8017BED4(void);
void func_8022A95C_ovl_27A020(Obj27 *o);
void func_8022A750_ovl_27A020(Obj27 *o);
void func_8022AAA4_ovl_27A020(Obj27 *o);
void func_8022AC5C_ovl_27A020(Obj27 *o);
void *LoadChunk(s32 id);
void func_8017BDC0(void);
typedef struct {
    s16 *list;
    u16 key;
} Find27;
extern void *D_801CE8BC;
extern u8 *D_8022C5C0_ovl_27A020;
extern u8 D_8022C5C4_ovl_27A020;
extern u8 D_801976DA;
extern u8 D_800E9C0A[];
extern f32 D_801CE8EC;
extern f32 D_801CE8F0;
extern f32 D_801CE8F4;
void func_801BE894(void);
void func_800EA76C(void);
void func_80079618(s32 a);
void func_8020B098(void);
void func_801BBC78(void);
void func_801B0020(void);
void func_801C1D98(void);
void func_801C1A9C(void);
void func_801C234C(void);
/* --- end decls --- */

/* Member id of the current squad's slot, made relative to 99 (0 for ids below 100) */
inline s32 func_80225890_ovl_27A020(s16 slot) {
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

/* Slot i status: -1 empty, 1 down (hp 0), 2 flag 4 set, 0 otherwise */
#ifdef NON_MATCHING
/* inlined member lookup: k computed as m-99 then zeroed; branch layout differs */
s32 func_80225AAC_ovl_27A020(s16 i) {
    u8 *a = NULL;
    u8 *b = NULL;
    s16 k;

    if (D_8022D150_ovl_27A020[i] == 0) {
        return -1;
    }
    k = func_80225890_ovl_27A020(i);
    if (k == 0) {
        a = (u8 *)D_8022D150_ovl_27A020[i];
    } else {
        b = (u8 *)D_8022D150_ovl_27A020[i];
    }
    if (a != NULL) {
        if (*(u16 *)(a + 0x18) == 0) {
            return 1;
        }
        if (a[0x33] & 4) {
            return 2;
        }
    } else if (b != NULL && (b[k + 0xF3] & 4)) {
        return 2;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/27A020", func_80225AAC_ovl_27A020);
#endif

INCLUDE_ASM("asm/nonmatchings/27A020", func_80225B90_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_80225CF8_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_802264B4_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_80226644_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_802267F8_ovl_27A020);

/* Analog stick Y beyond the dead zone sets the d-pad up/down bits (0x800 / 0x400) */
void func_80226980_ovl_27A020(void) {
    s16 i;
    s8 y;

    for (i = 0; i < D_800C6D60; i++) {
        y = D_800C47F0[i][3];
        if (y < -15) {
            D_800E9BE4[i] = (D_800E9BE4[i] & ~0x800) | 0x400;
        } else if (y >= 26) {
            D_800E9BE4[i] = (D_800E9BE4[i] & ~0x400) | 0x800;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/27A020", func_80226A24_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_80226B5C_ovl_27A020);

/* Leaves the field: saves the cursor/camera state and frees the overlay's resources */
void func_80226CC0_ovl_27A020(void) {
    if (D_801CE8BC != NULL) {
        func_801BE894();
        func_8022B560_ovl_27A020();
        func_80228650_ovl_27A020();
        if (D_8022C5C0_ovl_27A020 != NULL) {
            f32 x, y, z;

            D_801976DA = D_8022C5C0_ovl_27A020[0x14];
            x = *(f32 *)(D_8022C5C0_ovl_27A020 + 0x18);
            y = *(f32 *)(D_8022C5C0_ovl_27A020 + 0x1C);
            z = *(f32 *)(D_8022C5C0_ovl_27A020 + 0x20);
            D_800E9C0A[8] = D_8022C5C4_ovl_27A020;
            D_801CE8EC = x;
            D_801CE8F0 = y;
            D_801CE8F4 = z;
            HFree(D_8022C5C0_ovl_27A020);
            D_8022C5C0_ovl_27A020 = NULL;
        }
        func_800EA76C();
        func_80079618(-0x11);
        func_8020B098();
        func_801BBC78();
        func_801B0020();
        func_801C1D98();
        func_801C1A9C();
        func_801C234C();
        HFree(D_801CE8BC);
        D_801CE8BC = NULL;
    }
}

INCLUDE_ASM("asm/nonmatchings/27A020", func_80226DA8_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_80227130_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_802283C0_ovl_27A020);

s16 func_8022857C_ovl_27A020(void) {
    func_80226980_ovl_27A020();
    func_801CBF44();
    return func_802283C0_ovl_27A020();
}

/* Task pool: 5 entries chained through `next`, all idle */
#ifdef NON_MATCHING
/* pool count load and HMalloc result registers differ */
void func_802285B0_ovl_27A020(void) {
    Task27 *p;
    s32 i;
    s32 n;

    D_8022D0F2_ovl_27A020 = 5;
    p = HMalloc(0x118);
    n = D_8022D0F2_ovl_27A020;
    D_8022C890_ovl_27A020 = p;
    D_8022D148_ovl_27A020 = p;
    for (i = 0; i < n; i++) {
        p[i].fn = NULL;
    }
    p = D_8022D148_ovl_27A020;
    for (i = 1; i < D_8022D0F2_ovl_27A020; i++) {
        p->next = i;
        p++;
    }
    p->next = 0xFFFF;
}
#else
INCLUDE_ASM("asm/nonmatchings/27A020", func_802285B0_ovl_27A020);
#endif

void func_80228650_ovl_27A020(void) {
    if (D_8022C890_ovl_27A020 != NULL) {
        HFree(D_8022C890_ovl_27A020);
        D_8022C890_ovl_27A020 = NULL;
    }
}

/* Runs task callbacks (states >= 0x10) and counts down idle timers */
void func_80228680_ovl_27A020(void) {
    Task27 *t = D_8022D148_ovl_27A020;
    s32 i;

    for (i = 0; i < D_8022D0F2_ovl_27A020; i++) {
        Task27 *p = t;

        if (p->fn != NULL) {
            if (p->state >= 0x10) {
                p->fn(p->state, t);
            } else if (p->state == 0 && p->hE != -1) {
                if (--p->hE <= 0) {
                    p->state = p->hC;
                }
            }
        }
        t++;
    }
}

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
    t->state = 0;
    t->h10 = 1;
}

void func_80228838_ovl_27A020(Task27 *t) {
    t->hE = 0;
    t->h10 = 0;
}

s16 func_80228844_ovl_27A020(Find27 *f) {
    s16 i;

    if (f == NULL || f->list == NULL) {
        return 0;
    }
    for (i = 0; f->list[i] != 0; i++) {
        if (f->list[i] == f->key) {
            return f->key;
        }
    }
    return 0;
}

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

void func_8022B494_ovl_27A020(void) {
    D_8022D108_ovl_27A020 = LoadChunk(0x1DB3672);
    D_8022D10C_ovl_27A020 = LoadChunk(0x1DBB2AC);
    D_8022D110_ovl_27A020 = LoadChunk(0x1DB47A0);
    D_8022D114_ovl_27A020 = LoadChunk(0x1DC3320);
    D_8022D118_ovl_27A020 = LoadChunk(0x1DF98EA);
    D_8022D11C_ovl_27A020 = LoadChunk(0x1DB156C);
    D_8022D120_ovl_27A020 = LoadChunk(0x1DC2EE8);
    D_8022D100_ovl_27A020 = LoadChunk(0x1DC873E);
    D_8022D104_ovl_27A020 = LoadChunk(0x1DCB92C);
    func_8017BDC0();
}

void func_8022B560_ovl_27A020(void) {
    HFree(D_8022D108_ovl_27A020);
    HFree(D_8022D10C_ovl_27A020);
    HFree(D_8022D110_ovl_27A020);
    HFree(D_8022D114_ovl_27A020);
    HFree(D_8022D118_ovl_27A020);
    HFree(D_8022D11C_ovl_27A020);
    HFree(D_8022D120_ovl_27A020);
    HFree(D_8022D100_ovl_27A020);
    HFree(D_8022D104_ovl_27A020);
    func_8017BED4();
}

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

void func_8022BCD0_ovl_27A020(void) {
    Gfx *g = D_800E9BA0;
    Obj27 *o = D_8022CB20_ovl_27A020;

    u8 *q;

    g->w0 = 0xFA000000;
    q = *(u8 **)o;
    D_800E9BA0 = g + 1;
    g->w1 = q[0x19] | 0xFFFFFF00;
    func_8022A95C_ovl_27A020(o);
    func_8022A750_ovl_27A020(D_8022CB20_ovl_27A020);
    func_8022AAA4_ovl_27A020(D_8022CB20_ovl_27A020);
    func_8022AC5C_ovl_27A020(D_8022CB20_ovl_27A020);
}
