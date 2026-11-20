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

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern u8 D_80193BD3;
extern s32 D_8022C5CC_ovl_27A020;

s32 func_8022592C_ovl_27A020(s16 arg0) {
    s16 var_v1;
    s32 temp_lo;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a1;
    s32 var_t0;
    s32 var_v0;
    u8 temp_v1;
    u8 var_a3;
    u8 var_t2;
    void *var_a2;

    var_a2 = NULL;
    var_t0 = 0;
    var_a3 = 0;
    var_t2 = 0;
    var_a1 = 0;
    if (D_8022D150_ovl_27A020[arg0] == 0) {
        return -1;
    }
    temp_v1 = FIELD(&gSquads[D_801976DC].unk00[arg0], u8, 2);
    var_v1 = temp_v1 - 0x63;
    if (temp_v1 < 0x64U) {
        var_v1 = 0;
    }
    temp_v0 = arg0 << 0x10;
    if ((var_v1 << 0x10) == 0) {
        var_a2 = *(D_8022D150_ovl_27A020 + (temp_v0 >> 0xE));
    } else {
        var_t0 = *(D_8022D150_ovl_27A020 + (temp_v0 >> 0xE));
    }
    if (var_a2 != NULL) {
        if (FIELD(var_a2, u8, 0x33) & 4) {
            var_a1 = 4;
        }
        if (FIELD(var_a2, u16, 0x18) == 0) {
            var_a1 = 0x1B;
        }
        var_a3 = FIELD(var_a2, u8, 0x11);
        var_t2 = FIELD(var_a2, u8, 0x13);
    } else if (var_t0 != 0) {
        if (FIELD((var_t0 + var_v1), u8, 0xF3) & 4) {
            var_a1 = 4;
        }
        var_a3 = 1;
        var_t2 = D_80193BD3;
    }
    if (var_a1 == 0) {
        return 0;
    }
    if ((var_a3 << 0x10) > 0) {
        var_a3 -= 1;
    }
    temp_v1_2 = *(&D_8022C5CC_ovl_27A020 + ((s32) (var_a3 << 0x10) >> 0xE));
    temp_v0_2 = var_t2 + var_a1;
    temp_lo = temp_v1_2 * temp_v0_2;
    temp_v1_3 = (temp_v1_2 * temp_v0_2) % 10;
    var_v0 = temp_lo - temp_v1_3;
    if (temp_v1_3 >= 5) {
        var_v0 = (temp_lo - temp_v1_3) + 0xA;
    }
    return var_v0;
}
#else
INCLUDE_ASM("asm/nonmatchings/27A020", func_8022592C_ovl_27A020);
#endif

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

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_801AD9D4(void *, s32);             /* extern */
s32 func_801C8E30(void **);                         /* extern */
void **func_801C8FE8(s32);                          /* extern */

void func_802264B4_ovl_27A020(void) {
    s32 var_s2;
    u32 var_s1;
    u32 var_s1_2;
    void **temp_s1;
    void **var_s0;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_a0_4;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    var_s2 = 0;
    do {
        var_s0 = func_801C8FE8(var_s2);
        if (var_s0 != NULL) {
            var_s1 = 0;
            if (var_s2 == 0) {
                do {
                    temp_a0 = *var_s0;
                    if (temp_a0 != NULL) {
                        func_801AD9D4(temp_a0 + 0x44, 0);
                    }
                    var_s1 += 1;
                    var_s0 += 4;
                } while (var_s1 < 3U);
                var_s2 += 1;
            } else if (FIELD(var_s0, s32, 0x40) & 2) {
                do {
                    temp_a0_2 = *var_s0;
                    if (temp_a0_2 != NULL) {
                        func_801AD9D4(temp_a0_2 + 0x44, 0x26);
                    }
                    var_s1 += 1;
                    var_s0 += 4;
                } while (var_s1 < 3U);
                var_s2 += 1;
            } else {
                var_s1_2 = 0;
                if (FIELD(var_s0, u16, 0x20) == 0) {
                    do {
                        temp_a0_3 = FIELD(var_s0, void *, 0);
                        if (temp_a0_3 != NULL) {
                            func_801AD9D4(temp_a0_3 + 0x44, 0x20);
                            FIELD(FIELD(var_s0, void *, 0), s16, 0x34) = 0;
                        }
                        temp_v0 = FIELD(var_s0, void *, 0xC);
                        if (temp_v0 != NULL) {
                            FIELD(temp_v0, s16, 0x34) = 0;
                        }
                        var_s1_2 += 1;
                        var_s0 += 4;
                    } while (var_s1_2 < 3U);
                    var_s2 += 1;
                } else {
                    if (func_801C8E30(var_s0) == 0) {
                        temp_s1 = var_s0 + 0xC;
                        do {
                            temp_a0_4 = FIELD(var_s0, void *, 0);
                            if (temp_a0_4 != NULL) {
                                func_801AD9D4(temp_a0_4 + 0x44, 8);
                                if (var_s2 == 1) {
                                    temp_v1 = FIELD(var_s0, void *, 0);
                                    FIELD(temp_v1, u16, 0x1C) = (u16) (FIELD(temp_v1, u16, 0x1C) - 0x32);
                                }
                            }
                            temp_v1_2 = FIELD(var_s0, void *, 0xC);
                            var_s0 += 4;
                            if ((temp_v1_2 != NULL) && (var_s2 == 1)) {
                                FIELD(temp_v1_2, u16, 0x1C) = (u16) (FIELD(temp_v1_2, u16, 0x1C) - 0x32);
                            }
                        } while ((u32) var_s0 < (u32) temp_s1);
                    }
                    goto block_28;
                }
            }
        } else {
block_28:
            var_s2 += 1;
        }
    } while (var_s2 < 0x14);
}
#else
INCLUDE_ASM("asm/nonmatchings/27A020", func_802264B4_ovl_27A020);
#endif

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

#include "gbi_ultra.h"
typedef struct {
    s32 cms;
    s32 cmt;
    s32 masks;
    s32 maskt;
} TexMode27;
extern TexMode27 D_8022C918_ovl_27A020[];

/* Loads a CI4 texture (w x h pixels at img) with its 16-colour palette pal; wrap/mask settings
 * come from preset `mode` in D_8022C918 (same loader as 151F40 func_80200F70) */
void func_802288C0_ovl_27A020(void *pal, void *img, u16 w, u16 h, u16 mode) {
    TexMode27 *m = &D_8022C918_ovl_27A020[mode];

    gDPLoadTLUT_pal16(D_800E9BA0++, 0, pal);
    gDPLoadTextureBlock_4b(D_800E9BA0++, img, G_IM_FMT_CI, w, h, 0, m->cms, m->cmt, m->masks, m->maskt, 0, 0);
}

#ifdef NON_MATCHING
/* m2c draft, 75 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern s32 D_8022C8A0_ovl_27A020;

void func_80228B7C_ovl_27A020(s32 arg0, s32 arg1, s32 arg2) {
    Gfx *temp_t1;
    Gfx *temp_t2;
    Gfx *temp_v1_2;
    s16 temp_t3;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a3;
    s32 temp_t0;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a0;
    s32 var_v0;
    void *temp_a2;

    temp_t1 = D_800E9BA0;
    D_800E9BA0 = temp_t1 + 8;
    temp_t2 = temp_t1 + 0x10;
    temp_t1->w0 = 0xE7000000;
    temp_a2 = ((arg2 & 0xFFFF) * 8) + &D_8022C8A0_ovl_27A020;
    temp_t1->w1 = 0;
    temp_t3 = arg0 * 4;
    D_800E9BA0 = temp_t2;
    D_800E9BA0 = temp_t1 + 0x18;
    FIELD(temp_t1, s32, 0xC) = (s32) ((((arg0 * 4) & ((s32) ~temp_t3 >> 0x1F) & 0xFFC) << 0xC) | ((arg1 * 4) & ((s32) ~(s16) (arg1 * 4) >> 0x1F) & 0xFFC));
    FIELD(temp_t1, s32, 0x10) = 0xE1000000;
    temp_a3 = FIELD(temp_a2, u16, 0) + arg0;
    temp_t0 = FIELD(temp_a2, u16, 2) + arg1;
    FIELD(temp_t1, s32, 8) = (s32) ((((temp_a3 * 4) & ((s32) ~(s16) (temp_a3 * 4) >> 0x1F) & 0xFFC) << 0xC) | (((temp_t0 * 4) & ((s32) ~(s16) (temp_t0 * 4) >> 0x1F) & 0xFFC) | 0xE4000000));
    temp_a1 = FIELD(temp_a2, s16, 6) << 5;
    temp_a0 = FIELD(temp_a2, s16, 4) << 5;
    if (temp_t3 < 0) {
        temp_v1 = temp_t3 * 8;
        var_a0 = (temp_a0 - (temp_v1 & -(temp_v1 < 1))) << 0x10;
    } else {
        var_a0 = temp_a0 << 0x10;
    }
    if (!(arg1 & 0x20000000)) {
        var_v0 = temp_a1 & 0xFFFF;
    } else {
        temp_v0 = (s32) (arg1 << 0x12) >> 0xD;
        var_v0 = (temp_a1 - (temp_v0 & -(temp_v0 < 1))) & 0xFFFF;
    }
    temp_t2->w1 = var_a0 | var_v0;
    temp_v1_2 = D_800E9BA0;
    D_800E9BA0 = temp_v1_2 + 8;
    temp_v1_2->w0 = 0xF1000000;
    D_800E9BA0 = temp_v1_2 + 0x10;
    temp_v1_2->w1 = 0x04000400;
    FIELD(temp_v1_2, s32, 8) = 0xE7000000;
    FIELD(temp_v1_2, s32, 0xC) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/27A020", func_80228B7C_ovl_27A020);
#endif

INCLUDE_ASM("asm/nonmatchings/27A020", func_80228D1C_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_80228EFC_ovl_27A020);

#include "gbi_ultra.h"
extern u8 D_8022CA98_ovl_27A020[];
extern u8 D_8022CAB8_ovl_27A020[];
void func_80228D1C_ovl_27A020(s32 x, s32 y, s32 z);

/* Draws the 32x128 gauge frame (CI4, palette D_8022CA98) at (x, y); mode 2 sits one pixel in */
void func_802291A0_ovl_27A020(s32 x, s32 y, s32 mode) {
    gSPDisplayList(D_800E9BA0++, D_8022CAB8_ovl_27A020);
    gDPPipeSync(D_800E9BA0++);
    gSPTexture(D_800E9BA0++, 0x8000, 0x8000, 0, 0, G_ON);
    gDPLoadTLUT_pal16(D_800E9BA0++, 0, D_8022CA98_ovl_27A020);
    gDPLoadTextureBlock_4b(D_800E9BA0++, D_8022D108_ovl_27A020, G_IM_FMT_CI, 32, 128, 0, 2, 2, 5, 7, 0, 0);
    if (mode == 2) {
        func_80228D1C_ovl_27A020(x - 2, y + 12, 0);
    } else {
        func_80228D1C_ovl_27A020(x - 3, y + 11, 0);
    }
}

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

extern s32 gGoth;
extern u8 D_8022C9D8_ovl_27A020[];
void func_80228EFC_ovl_27A020(s32 x, s32 y, s32 value, s32 digits);
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif

/* Draws the Goth (money) panel of window o: backdrop, the amount, the coin icon, and the
 * extra arrows when the window's value is above 64 */
#ifdef NON_MATCHING
/* Goth panel: gGoth load scheduled before the display-list pointer in the original */
void func_8022A488_ovl_27A020(Obj27 *o) {
    s32 goth = gGoth;
    u8 *w;
    s32 x;
    s32 y;

    gSPDisplayList(D_800E9BA0++, D_8022CAB8_ovl_27A020);
    w = o->w20;
    x = FIELD(w, s32, 0x2C);
    y = FIELD(w, s32, 0x30);
    if (FIELD(w, s16, 0x18) == 0) {
        return;
    }
    func_802288C0_ovl_27A020(D_8022C9D8_ovl_27A020, D_8022D120_ovl_27A020, 0x50, 0x11, 2);
    func_80228EFC_ovl_27A020(x + 8, y + 8, goth, 7);
    gDPLoadTLUT_pal16(D_800E9BA0++, 0, (u8 *)D_8022D104_ovl_27A020 + 0x320);
    gDPLoadTextureBlock_4b(D_800E9BA0++, (u8 *)D_8022D100_ovl_27A020 + 0x2828, G_IM_FMT_CI, 48, 32, 0, 0, 0, 0, 0, 0, 0);
    func_80228B7C_ovl_27A020(x + 0x3C, y + 0xA, 0xC);
    gDPPipeSync(D_800E9BA0++);
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xED000000;
        _g->w1 = 0x004FC3BC;
    }
    gDPPipeSync(D_800E9BA0++);
    if (FIELD(o->w20, s16, 0x18) > 0x40) {
        func_80228B7C_ovl_27A020(x + 8, y - 6, 0xD);
        func_80228B7C_ovl_27A020(x + 0x20, y - 6, 0xE);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/27A020", func_8022A488_ovl_27A020);
#endif

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022A750_ovl_27A020);

extern u8 D_8022CAB8_ovl_27A020[];
void func_80179034(s32 a, s32 x, s32 y);
void func_8016DE1C(u8 a, u8 b);

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
/* Entry list inside Obj27 (+0x18) */
typedef struct {
    /* 0x0 */ s32 *items;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 flags;
} List27;

static inline s16 List27_EntryMark(List27 *l, u8 *e) {
    s16 mark = 0;

    if (e == NULL) {
        return 0;
    }
    if ((l->flags & 2) && (FIELD(e, s32, 0x40) & 2)) {
        mark = 2;
    }
    if ((l->flags & 1) && FIELD(e, u16, 0x20) == 0) {
        mark = 1;
    }
    return mark;
}


/* Draws the marks beside the (up to five) list entries that need one: 2 when the list
 * flags bit 1 and the entry has flag 2, 1 when the list flags bit 0 and the entry is idle */
#ifdef NON_MATCHING
/* entry marks: register allocation differs */
void func_8022A95C_ovl_27A020(Obj27 *o) {
    u8 *win = FIELD(o, u8 *, 0);
    List27 *l = (List27 *)&o->w18;
    s16 i;
    s16 y;
    s16 x;
    u8 *e;

    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xDE000000;
        _g->w1 = (u32)&D_8022CAB8_ovl_27A020;
    }
    y = FIELD(win, s32, 0x30) + 3;
    x = FIELD(win, s32, 0x2C) + 5;
    for (i = 0; i < 5; i++) {
        e = (u8 *)l->items[i];
        if (List27_EntryMark(l, e)) {
            func_80179034(func_802258DC_ovl_27A020(i), x + 30, y + 2);
            y += 36;
            func_8016DE1C(e[0x4B], e[0x4F]);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/27A020", func_8022A95C_ovl_27A020);
#endif

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022AAA4_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022AC5C_ovl_27A020);

void func_8022AFCC_ovl_27A020(Obj27 *o) {
    *o->w18 = 0;
    o->h1C = 0;
    o->h1E ^= o->h1E;
}

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022AFE8_ovl_27A020);

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022B1D8_ovl_27A020);

extern s16 D_8022CB2A_ovl_27A020;
extern s16 D_8022CB64_ovl_27A020[2][8];
u8 *func_8017BFB0(s32 a, s32 b, void *fn, s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3);
void func_8022BC80_ovl_27A020(void);

/* Opens the shop window in layout `mode` (0 or 1; rectangles in D_8022CB64) */
void func_8022B36C_ovl_27A020(s16 mode) {
    Obj27 *o = D_8022CB20_ovl_27A020;

    D_8022CB2A_ovl_27A020 = 1;
    gSPDisplayList(D_800E9BA0++, D_8022CAB8_ovl_27A020);
    if (mode == 0) {
        o->w24 = func_8017BFB0(4, 0, func_8022BC80_ovl_27A020, D_8022CB64_ovl_27A020[0][0], D_8022CB64_ovl_27A020[0][1],
                               D_8022CB64_ovl_27A020[0][2], D_8022CB64_ovl_27A020[0][3], D_8022CB64_ovl_27A020[0][4],
                               D_8022CB64_ovl_27A020[0][5], D_8022CB64_ovl_27A020[0][6], D_8022CB64_ovl_27A020[0][7]);
    } else if (mode == 1) {
        o->w24 = func_8017BFB0(4, 0, func_8022BC80_ovl_27A020, D_8022CB64_ovl_27A020[1][0], D_8022CB64_ovl_27A020[1][1],
                               D_8022CB64_ovl_27A020[1][2], D_8022CB64_ovl_27A020[1][3], D_8022CB64_ovl_27A020[1][4],
                               D_8022CB64_ovl_27A020[1][5], D_8022CB64_ovl_27A020[1][6], D_8022CB64_ovl_27A020[1][7]);
    }
}

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
