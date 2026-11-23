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

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern u8 D_80193BD3;
extern s32 D_8022C5CC_ovl_27A020[];

/* Cost of curing slot's member: the class price times (level + 4 when petrified, + 27 when dead),
 * rounded to the nearest 10; 0 when it needs no cure, -1 for an empty slot */
#ifdef NON_MATCHING
/* 96/96, 69 words: the member offset (func_80225890 inlined) is tested after the call in the original; here the zero case is threaded straight to the else branch */
s32 func_8022592C_ovl_27A020(s16 slot) {
    u8 *c = NULL;
    u8 *g = NULL;
    s16 cls = 0;
    u8 lvl = 0;
    s32 add = 0;
    s16 e;
    s32 v;
    s32 r;

    if (D_8022D150_ovl_27A020[slot] == 0) {
        return -1;
    }
    e = func_80225890_ovl_27A020(slot);
    if (e == 0) {
        c = (u8 *)D_8022D150_ovl_27A020[slot];
    } else {
        g = (u8 *)D_8022D150_ovl_27A020[slot];
    }
    if (c != NULL) {
        if (c[0x33] & 4) {
            add = 4;
        }
        if (FIELD(c, u16, 0x18) == 0) {
            add = 0x1B;
        }
        cls = c[0x11];
        lvl = c[0x13];
    } else if (g != NULL) {
        if (g[e + 0xF3] & 4) {
            add = 4;
        }
        cls = 1;
        lvl = D_80193BD3;
    }
    if (add == 0) {
        return 0;
    }
    if (cls > 0) {
        cls--;
    }
    v = D_8022C5CC_ovl_27A020[cls] * (lvl + add);
    r = v % 10;
    if (r >= 5) {
        return v - r + 10;
    }
    return v - r;
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

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_801AD9D4(void *, s32);

/* Revives squad member k (HP 0 -> 1) and cures its status bit 2, then replays animation 0x25 on
 * its parts */
#ifdef NON_MATCHING
/* 90/90 instructions, 41 words differ: the squad table base is materialised separately, the generic-index test branches the other way and the parts loop index is re-extended */
void func_80225B90_ovl_27A020(s16 k) {
    u8 *pc = NULL;
    s32 gen = 0;
    s16 g;
    u8 c;
    u8 *u;
    u16 i;

    if (D_8022D150_ovl_27A020[k] != 0) {
        c = FIELD(&gSquads[D_801976DC].unk00[k], u8, 2);
        if (c >= 100) {
            g = c - 99;
        } else {
            g = 0;
        }
        if (g == 0) {
            pc = (u8 *)D_8022D150_ovl_27A020[k];
        } else {
            gen = D_8022D150_ovl_27A020[k];
        }
        u = (u8 *)D_8022D134_ovl_27A020[k];
        if (pc != NULL) {
            if (FIELD(pc, u16, 0x18) == 0) {
                FIELD(pc, u16, 0x18) = 1;
                FIELD(u, s32, 0x20) = 1;
            }
            if (pc[0x33] & 4) {
                pc[0x33] &= ~4;
                FIELD(u, s32, 0x40) &= ~2;
            }
        } else if (gen != 0) {
            if (FIELD(gen + g, u8, 0xF3) & 4) {
                FIELD(gen + g, u8, 0xF3) &= ~4;
                FIELD(u, s32, 0x40) &= ~2;
            }
        }
        for (i = 0; i < 3; i++) {
            if (FIELD(u, s32, i * 4) != 0) {
                func_801AD9D4(FIELD(u, u8 *, i * 4) + 0x44, 0x25);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/27A020", func_80225B90_ovl_27A020);
#endif

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

#include "scene.h"
s32 func_8007F648(void *func, s16 x, s16 y, s16 b, u16 c);
void D_80198BE8(void);

/* Creates a scene box: image id, kind b (top bit set), position (x, y), size (w, h), z, colour
 * index col, with flags 4 (f1) and 8 (f2); returns its slot */
#ifdef NON_MATCHING
/* 109/109 instructions, 92 words differ: register allocation (the original keeps z in s6 and spills id and col to the frame) */
s32 func_80226644_ovl_27A020(u8 id, u16 b, u32 x, u32 y, u16 w, u16 col, u32 z, u8 f1, u8 f2) {
    s32 i = func_8007F648(D_80198BE8, 0, 0, 0, 0);
    u8 flags;

    bzero(&D_800E82C8[i].unk88, 0x10);
    flags = (f1 != 0) * 4;
    D_800E82C8[i].unk89 = b;
    D_800E82C8[i].unk88 = (b >> 8) | 0x80;
    if (f2) {
        flags |= 8;
    }
    D_800E82C8[i].unk8A = flags;
    D_800E82C8[i].unk8C = x >> 8;
    D_800E82C8[i].unk8D = x;
    D_800E82C8[i].unk8F = id;
    D_800E82C8[i].unk90[1] = 8;
    D_800E82C8[i].unk90[2] = z >> 8;
    D_800E82C8[i].unk90[3] = z;
    D_800E82C8[i].unk94 = y >> 8;
    D_800E82C8[i].unk95 = y;
    D_800E82C8[i].unk8E = w >> 8;
    D_800E82C8[i].unk90[0] = w;
    D_800E82C8[i].unk8B = col;
    return i;
}
#else
INCLUDE_ASM("asm/nonmatchings/27A020", func_80226644_ovl_27A020);
#endif

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
typedef struct {
    f32 x;
    f32 y;
} Scroll27;
extern Scroll27 D_801D0774;
extern u8 *D_8022D130_ovl_27A020[];

/* Screen rect (x0, y0, x1, y1) of the info window beside unit k: right of it when the scroll is
 * positive, else below */
void func_802267F8_ovl_27A020(s16 k, s16 *r) {
    u8 *u = D_8022D130_ovl_27A020[k];
    f32 *sx = &D_801D0774.x;

    if (*sx > 0.0f) {
        r[0] = FIELD(u, s32, 0x98) + *sx + 5.0f;
        r[1] = FIELD(u, s32, 0x9C) - D_801D0774.y - 12.0f;
        r[2] = FIELD(u, s32, 0x98) + *sx + 5.0f;
        r[3] = FIELD(u, s32, 0x9C) - D_801D0774.y - 60.0f;
    } else {
        r[0] = FIELD(u, s32, 0x98) + *sx;
        r[1] = FIELD(u, s32, 0x9C) - D_801D0774.y + 16.0f;
        r[2] = FIELD(u, s32, 0x98) + *sx + 55.0f;
        r[3] = FIELD(u, s32, 0x9C) - D_801D0774.y + 55.0f;
    }
}

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

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif

/* Steps the value at state+0xC toward the target (+0x10) by the step (+0x12) and clamps it;
 * returns 1 once the target is reached */
s32 func_80226A24_ovl_27A020(void) {
    s16 *cur = FIELD(D_8022C5C0_ovl_27A020, s16 *, 0xC);
    s16 target = FIELD(D_8022C5C0_ovl_27A020, s16, 0x10);
    s16 step = FIELD(D_8022C5C0_ovl_27A020, s16, 0x12);
    s16 delta;

    if (cur != NULL) {
        s16 d = target - *cur;

        if (d == 0) {
            return 1;
        }
        if (d > 0) {
            delta = target / step;
        } else {
            delta = -((0xFF - target) / step);
        }
        *cur += delta;
        if (delta < 0) {
            if (*cur <= target) {
                *cur = target;
                return 1;
            }
        } else if (*cur >= target) {
            *cur = target;
            return 1;
        }
    }
    return 0;
}

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void bzero(void *p, s32 n);
void func_80179018(void);
void func_801AEA90(void);
void func_801B7E9C(void);
void func_801BC5FC(void);
void func_801BC640(void);
void func_801BE71C(void);
void func_801C1A94(void);
void func_801C1D90(void);
void func_801C22D0(s32 n);
void func_801C2310(void);
void func_8020B030(void);
extern void *D_801CE8C0;
extern s32 D_801CEAB0;

/* System flags; byte 8 is cleared while this screen is open */
typedef struct {
    u8 unk0[8];
    u8 unk8;
} Flags27A;

/* Enters the screen: allocates the 0x6094-byte work area and the 0x48-byte saved state (camera
 * position and mode), then initialises the screen's subsystems */
void func_80226B5C_ovl_27A020(void) {
    u8 *buf;
    u8 *state;
    u8 flag;
    u8 *st;
    f32 x, y, z;

    D_801CEAB0 = 0x29;
    func_801BE71C();
    buf = HMalloc(0x6094);
    D_801CE8BC = buf;
    bzero(buf, 0x6094);
    D_801CE8C0 = (u8 *)D_801CE8BC + 0x57E0;
    FIELD(D_801CE8BC, s8, 0x6084) = 1;
    state = HMalloc(0x48);
    D_8022C5C0_ovl_27A020 = state;
    bzero(state, 0x48);
    st = D_8022C5C0_ovl_27A020;
    FIELD(st, s16, 4) = 0xFF;
    FIELD(st, s32, 0) = 0;
    FIELD(st, s32, 8) = 0;
    FIELD(st, u8, 0x14) = D_801976DA;
    x = D_801CE8EC;
    y = D_801CE8F0;
    z = D_801CE8F4;
    D_801976DA = 0x18;
    FIELD(st, f32, 0x18) = x;
    FIELD(st, f32, 0x1C) = y;
    FIELD(st, f32, 0x20) = z;
    flag = ((Flags27A *)D_800E9C0A)->unk8;
    ((Flags27A *)D_800E9C0A)->unk8 = 1;
    D_8022C5C4_ovl_27A020 = flag;
    func_802285B0_ovl_27A020();
    func_8022B494_ovl_27A020();
    func_801C1D90();
    func_801C1A94();
    func_801C2310();
    func_801C22D0(2);
    func_801BC5FC();
    func_801BC640();
    func_801B7E9C();
    func_801AEA90();
    func_8020B030();
    func_80225CF8_ovl_27A020();
    func_80179018();
    func_802264B4_ovl_27A020();
    FIELD(D_8022C5C0_ovl_27A020, s32, 0) = 0;
}

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

void func_80227130_ovl_27A020(s32 a, Task27 *t);
void func_801BC9F0(void);
void func_8020B104(void);
void func_801D8010(void);
s32 func_80186210(s32 flag);
extern u8 D_800EB0B0[];
void func_800EA7E4(void *bank, s32 a);

typedef struct {
    /* 0x00 */ u32 state;
    /* 0x04 */ s16 fade;
    /* 0x06 */ u8 unk06[2];
    /* 0x08 */ Task27 *task;
    /* 0x0C */ s16 *fadep;
    /* 0x10 */ s16 target;
    /* 0x12 */ s16 step;
} Shop27;

/* Shop main step: 0 starts the shop task and fades in, 2 waits for the fade, 4 runs the menu
 * (0x12F / 0x130 pick the next scene), 5 fades out and finishes (1) */
#ifdef NON_MATCHING
/* 111/111 instructions, 4 words differ: the next scene state for 0x12F is built in v1 where the original reuses v0 */
s32 func_802283C0_ovl_27A020(void) {
    switch (((Shop27 *)D_8022C5C0_ovl_27A020)->state) {
        case 1:
            return 1;
        case 0:
            ((Shop27 *)D_8022C5C0_ovl_27A020)->task = func_8022874C_ovl_27A020(func_80227130_ovl_27A020);
            ((Shop27 *)D_8022C5C0_ovl_27A020)->state = 2;
            ((Shop27 *)D_8022C5C0_ovl_27A020)->fadep = &((Shop27 *)D_8022C5C0_ovl_27A020)->fade;
            ((Shop27 *)D_8022C5C0_ovl_27A020)->target = 10;
            ((Shop27 *)D_8022C5C0_ovl_27A020)->step = 60;
            break;
        case 2:
            if ((s16)func_80226A24_ovl_27A020() != 0) {
                ((Shop27 *)D_8022C5C0_ovl_27A020)->fadep = &((Shop27 *)D_8022C5C0_ovl_27A020)->fade;
                ((Shop27 *)D_8022C5C0_ovl_27A020)->target = 0xFF;
                ((Shop27 *)D_8022C5C0_ovl_27A020)->step = 60;
                ((Shop27 *)D_8022C5C0_ovl_27A020)->state = 4;
            }
            break;
        case 4: {
            Task27 *t = ((Shop27 *)D_8022C5C0_ovl_27A020)->task;
            s16 r = func_80228844_ovl_27A020((Find27 *)t);
            s16 next;

            if (r == 0) {
                next = 0;
            } else {
                switch (r) {
                    case 0x12F:
                        if (func_80186210(0x13) == 0) {
                            t->state = 0x109;
                        } else {
                            t->state = 0x103;
                        }
                        next = 4;
                        break;
                    case 0x130:
                        func_800EA7E4(D_800EB0B0, 0x78);
                        t->state = 0x107;
                        next = 5;
                        break;
                    default:
                        next = r;
                        break;
                }
            }
            if (next != 0) {
                ((Shop27 *)D_8022C5C0_ovl_27A020)->state = next;
            }
            break;
        }
        case 5:
            if ((s16)func_80226A24_ovl_27A020() != 0) {
                func_800EA76C();
                ((Shop27 *)D_8022C5C0_ovl_27A020)->state = 1;
            }
            break;
    }
    func_801BC9F0();
    func_80228680_ovl_27A020();
    func_8020B104();
    func_801D8010();
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/27A020", func_802283C0_ovl_27A020);
#endif

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

#include "gbi_ultra.h"
typedef struct {
    u16 w;
    u16 h;
    s16 s;
    s16 t;
} Icon27A;
extern Icon27A D_8022C8A0_ovl_27A020[];

/* Draws icon k of the icon sheet (w, h, s, t from D_8022C8A0) at screen position (x, y) */
void func_80228B7C_ovl_27A020(s32 x, s32 y, s32 k) {
    Icon27A *e = &D_8022C8A0_ovl_27A020[(u16)k];

    gDPPipeSync(D_800E9BA0++);
    gSPScisTextureRectangle(D_800E9BA0++, x << 2, y << 2, (x + e->w) << 2, (y + e->h) << 2, 0, e->s << 5, e->t << 5,
                            1 << 10, 1 << 10);
    gDPPipeSync(D_800E9BA0++);
}

/* Sprite atlas entry: screen rect relative to the draw position and texel origin */
typedef struct {
    u16 x0;
    u16 y0;
    u16 x1;
    u16 y1;
    u16 s;
    u16 t;
} Atlas27;
extern Atlas27 D_8022CA38_ovl_27A020[];

/* Draws atlas sprite `id` (rect + texture origin in D_8022CA38) at (x, y) */
/* Draws atlas sprite `id` (rect + texture origin in D_8022CA38) at (x, y) */
#ifdef NON_MATCHING
/* atlas sprite: 4 instructions short; original has an 8-byte frame and mixes lh/lhu loads of y0 */
void func_80228D1C_ovl_27A020(s32 x, s32 y, u16 id) {
    Atlas27 *a = &D_8022CA38_ovl_27A020[id];

    gDPPipeSync(D_800E9BA0++);
    gSPScisTextureRectangle(D_800E9BA0++, (a->x0 + x) * 4, (a->y0 + y) * 4, (a->x1 + x) * 4, (a->y1 + y) * 4, 0,
                            a->s << 5, a->t << 5, 1 << 10, 1 << 10);
    gDPPipeSync(D_800E9BA0++);
}
#else
INCLUDE_ASM("asm/nonmatchings/27A020", func_80228D1C_ovl_27A020);
#endif

/* Draws value as 7x9 digit sprites right-aligned in `digits` cells at (x, y) (0 = as many as
 * needed up to 3; negative = blank leading zeros), then a pipe sync */
#ifdef NON_MATCHING
/* 165 vs 169: the original hoists the /10 magic constant and (blank != 0) into registers and keeps one more saved register */
void func_80228EFC_ovl_27A020(s32 x, s32 y, s32 value, s32 digits) {
    s32 blank = 0;
    s32 v = value;
    s32 n;
    s32 i;

    if (v < 0) {
        v = -v;
    }
    if (digits == 0) {
        digits = 1;
        if (v >= 10) {
            digits = v >= 100 ? 3 : 2;
        }
    } else if (digits < 0) {
        digits = -digits;
        blank = 1;
    }
    n = v;
    x += (digits - 1) * 7;
    for (i = 0; i < digits; i++) {
        if (!((blank != 0) & (n == 0)) || i == 0) {
            gDPPipeSync(D_800E9BA0++);
            gSPScisTextureRectangle(D_800E9BA0++, x << 2, y << 2, (x + 7) << 2, (y + 9) << 2, 0, (n % 10) * 7 << 5,
                                    0, 1 << 10, 1 << 10);
            gDPPipeSync(D_800E9BA0++);
        }
        n /= 10;
        x -= 7;
    }
    gDPPipeSync(D_800E9BA0++);
}
#else
INCLUDE_ASM("asm/nonmatchings/27A020", func_80228EFC_ovl_27A020);
#endif

#include "gbi_ultra.h"
extern u8 D_8022CA98_ovl_27A020[];
extern u8 D_8022CAB8_ovl_27A020[];
void func_80228D1C_ovl_27A020(s32 x, s32 y, s32 id);

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

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern u8 D_800EB1F0[];
void func_800EA604(void *bank, s32 se);
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

extern u16 D_800E8100;
extern s32 gGoth;

/* Shop list cursor (five rows at o->0x10): up/down move to the next pickable entry with a key
 * repeat delay; A returns 1 (3 when the price exceeds gGoth), B returns 2, else 0 */
s32 func_8022A120_ovl_27A020(Obj27 *o) {
    List27 *l = (List27 *)&o->w18;
    s16 d = 0;

    if (--FIELD(o, s16, 0x1C) > 0) {
        return 0;
    }
    FIELD(o, s16, 0x1C) = 0;
    if (D_800E8100 & 0x8000) {
        return ((u32)gGoth < func_8022592C_ovl_27A020(FIELD(o, s16, 0x10))) ? 3 : 1;
    }
    if (D_800E8100 & 0x4000) {
        return 2;
    }
    while (1) {
        if (D_800E9BE4[0] & 0x800) {
            d--;
            l->unk4 = 5;
            if (FIELD(o, s16, 0x10) + d < 0) {
                break;
            }
        } else if (D_800E9BE4[0] & 0x400) {
            d++;
            l->unk4 = 5;
            if (FIELD(o, s16, 0x10) + d >= 5) {
                break;
            }
        } else {
            break;
        }
        if (List27_EntryMark(l, (u8 *)l->items[FIELD(o, s16, 0x10) + d]) != 0) {
            FIELD(o, s16, 0x10) += d;
            func_800EA604(D_800EB1F0, 2);
            break;
        }
    }
    return 0;
}

extern s16 D_8022CB28_ovl_27A020;
extern s16 D_8022CB2A_ovl_27A020; /* selected row: 1 = Yes, 0 = No */
extern u8 D_8022CB2C_ovl_27A020;  /* cursor bob step */
extern s16 D_8022CB30_ovl_27A020[]; /* cursor x offsets, 0x63-terminated */
void func_80179034(s32 a, s32 x, s32 y);
void func_801818A0(s16 x, s16 y);

/* Draws the Yes/No prompt of window o and its cursor (bobbing while D_8022CB28 is 2) */
#ifdef NON_MATCHING
/* 120/120 instructions, 2 words differ: the window y load is scheduled one slot earlier than in the original (the Yes/No strings would also need the shared rodata block split) */
void func_8022A2A8_ovl_27A020(Obj27 *o) {
    char yes[4] = "Yes";
    char no[3] = "No";
    s32 x = FIELD(o->w24, s32, 0x2C);
    s32 y = FIELD(o->w24, s32, 0x30);
    s16 cx;
    s16 cy;

    gSPDisplayList(D_800E9BA0++, D_8022CAB8_ovl_27A020);
    func_80179034((s32)yes, x + 0x1A, y + 1);
    func_80179034((s32)no, x + 0x1A, y + 0x13);
    y += 2;
    cy = y + (1 - D_8022CB2A_ovl_27A020) * 18;
    if (D_8022CB30_ovl_27A020[D_8022CB2C_ovl_27A020] == 0x63) {
        D_8022CB2C_ovl_27A020 = 0;
    }
    if (D_8022CB28_ovl_27A020 == 2) {
        cx = D_8022CB30_ovl_27A020[D_8022CB2C_ovl_27A020++] + x;
    } else {
        cx = x + 3;
    }
    gSPDisplayList(D_800E9BA0++, D_8022CAB8_ovl_27A020);
    gDPPipeSync(D_800E9BA0++);
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xE200001C;
        _g->w1 = 0x504240;
    }
    func_801818A0(cx, cy);
    gDPPipeSync(D_800E9BA0++);
}
#else
INCLUDE_ASM("asm/nonmatchings/27A020", func_8022A2A8_ovl_27A020);
#endif

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

extern u8 D_8022CAB8_ovl_27A020[];
void func_8016DE1C(u8 a, u8 b);

/* Draws the price rows of the marked list entries: a frame (lower for palette-2 entries), the
 * price label (greyed when above gGoth) and the price */
#ifdef NON_MATCHING
/* 124/131 instructions: logic as in the original; the loads of the window position and list pointer, and the frame offset select, are scheduled differently */
void func_8022A750_ovl_27A020(Obj27 *o) {
    u8 *win = FIELD(o, u8 *, 0);
    List27 *l = (List27 *)&o->w18;
    s16 i;
    s16 y;
    s32 x;
    s32 yy;
    u32 price;
    u8 *e;

    gSPDisplayList(D_800E9BA0++, D_8022CAB8_ovl_27A020);
    y = FIELD(win, s32, 0x30) + 3;
    x = (s16)FIELD(win, s32, 0x2C) + FIELD(o, s16, 0xE);
    for (i = 0; i < 5; i++) {
        e = (u8 *)l->items[i];
        if (List27_EntryMark(l, e)) {
            yy = y + ((((u8 (*)(u8, u8))func_8016DE1C)(e[0x4B], e[0x4F]) == 2) ? 22 : 20);
            func_802288C0_ovl_27A020(D_8022D104_ovl_27A020 + 0x320, D_8022D100_ovl_27A020 + 0x2828, 0x30, 0x20, 2);
            func_80228B7C_ovl_27A020(x - 0x1A, yy + 1, 0xC);
            price = func_8022592C_ovl_27A020(i);
            func_802288C0_ovl_27A020(D_8022C9D8_ovl_27A020 + (((u32)gGoth < price) << 6), D_8022D120_ovl_27A020, 0x50,
                                     0x11, 2);
            func_80228EFC_ovl_27A020(x - 0x50, yy, price, -7);
            y += 0x24;
            func_8016DE1C(e[0x4B], e[0x4F]);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/27A020", func_8022A750_ovl_27A020);
#endif

extern u8 D_8022CAB8_ovl_27A020[];
void func_80179034(s32 a, s32 x, s32 y);
void func_8016DE1C(u8 a, u8 b);

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif


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

void func_802297D8_ovl_27A020(u8 *e, s16 x, s32 y, s16 mark);
void func_802293B4_ovl_27A020(s32 x, s32 y, s32 icon);

/* Draws the list entries that carry a mark: entry palette, background slot, the entry row,
 * and the mark icon (12 for idle, 4 for flagged) */
#ifdef NON_MATCHING
/* marked entries draw: one instruction short, original keeps the palette in s4 */
void func_8022AAA4_ovl_27A020(Obj27 *o) {
    u8 *win = FIELD(o, u8 *, 0);
    List27 *l = (List27 *)&o->w18;
    s16 i;
    s16 y;
    s16 x;
    s16 mark;
    u8 *e;
    u8 pal;

    gSPDisplayList(D_800E9BA0++, D_8022CAB8_ovl_27A020);
    y = FIELD(win, s32, 0x30) + 3;
    x = FIELD(win, s32, 0x2C) + 5;
    for (i = 0; i < 5; i++) {
        e = (u8 *)l->items[i];
        mark = List27_EntryMark(l, e);
        if (mark != 0) {
            pal = ((u8 (*)(u8, u8))func_8016DE1C)(e[0x4B], e[0x4F]);
            func_802291A0_ovl_27A020(x, y + 1, pal);
            func_802297D8_ovl_27A020(e, x, y + 1, mark);
            switch (mark) {
                case 1:
                    func_802293B4_ovl_27A020(x - 15, y + 20, 12);
                    break;
                case 2:
                    func_802293B4_ovl_27A020(x - 7, y + 20, 4);
                    break;
            }
            y += 36;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/27A020", func_8022AAA4_ovl_27A020);
#endif

INCLUDE_ASM("asm/nonmatchings/27A020", func_8022AC5C_ovl_27A020);

void func_8022AFCC_ovl_27A020(Obj27 *o) {
    *o->w18 = 0;
    o->h1C = 0;
    o->h1E ^= o->h1E;
}

void func_8022BCD0_ovl_27A020(void);
void func_8016DE1C(u8 a, u8 b);

/* Sizes the shop list window for the marked entries (0x24 per row plus 0xB) and selects the
 * first marked entry; returns 0 when no entry is marked */
#ifdef NON_MATCHING
/* 124/124 instructions, 3 words differ: the found flag is set after the height update in the original */
s32 func_8022AFE8_ovl_27A020(Obj27 *o) {
    List27 *l = (List27 *)&o->w18;
    s16 i;
    s16 any = 0;

    FIELD(o, u16, 0xC) = 0;
    l->flags = (l->flags ^ l->flags) | 3;
    for (i = 0; i < 5; i++) {
        if (List27_EntryMark(l, (u8 *)l->items[i])) {
            u8 *e = (u8 *)l->items[i];

            func_8016DE1C(e[0x4B], e[0x4F]);
            FIELD(o, u16, 0xC) += 0x24;
            any = 1;
        }
    }
    if (!any) {
        return any;
    }
    FIELD(o, u16, 0xC) += 0xB;
    FIELD(o, s16, 0x10) = 0;
    FIELD(o, s16, 0xE) = 0x7C;
    FIELD(o, s16, 8) = 0x1E;
    FIELD(o, s16, 0xA) = 0xE6 - FIELD(o, u16, 0xC);
    for (i = 0; i < 5; i++) {
        if (List27_EntryMark(l, (u8 *)l->items[FIELD(o, s16, 0x10)])) {
            break;
        }
        FIELD(o, s16, 0x10)++;
    }
    FIELD(o, void *, 4) = func_8022BCD0_ovl_27A020;
    FIELD(o, s32, 0) = 0;
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/27A020", func_8022AFE8_ovl_27A020);
#endif

typedef struct {
    /* 0x00 */ u8 unk00[0x18];
    /* 0x18 */ s16 fade;
    /* 0x1A */ u8 unk1A[0xE];
    /* 0x28 */ u16 flags;
} Win27;
extern u16 D_800E79B0;
extern s16 D_8022CB28_ovl_27A020;
extern s16 D_8022CB2A_ovl_27A020;
void func_8017C384(u8 *w);

/* Shop yes/no cursor: up selects 1, down 0 (with a click when it moves); A returns the
 * selection, B returns 0, otherwise -1 */
static inline s16 ShopYesNo27(void) {
    if (D_800E79B0 & 0x8000) {
        return D_8022CB2A_ovl_27A020;
    }
    if (D_800E79B0 & 0x4000) {
        return 0;
    }
    if (D_800E9BE4[0] & 0x800) {
        if (D_8022CB2A_ovl_27A020 != 1) {
            func_800EA604(D_800EB1F0, 2);
        }
        D_8022CB2A_ovl_27A020 = 1;
    } else if (D_800E9BE4[0] & 0x400) {
        if (D_8022CB2A_ovl_27A020 != 0) {
            func_800EA604(D_800EB1F0, 2);
        }
        D_8022CB2A_ovl_27A020 = 0;
    }
    return -1;
}

/* Runs the shop's yes/no window once it has faded in: 1 for yes, 2 for no (closing the window),
 * 0 while undecided */
s32 func_8022B1D8_ovl_27A020(void) {
    Obj27 *o = D_8022CB20_ovl_27A020;
    u8 *sub = (u8 *)&o->w18;
    s16 r;

    if (o->w24 == NULL) {
        return 0;
    }
    D_8022CB28_ovl_27A020 = 2;
    if (((Win27 *)o->w24)->fade <= 200) {
        return 0;
    }
    r = ShopYesNo27();
    if (r == 1) {
        func_800EA604(D_800EB1F0, 0);
        if (FIELD(sub, u8 *, 0xC) != NULL && !(((Win27 *)FIELD(sub, u8 *, 0xC))->flags & 2)) {
            func_8017C384(FIELD(sub, u8 *, 0xC));
            return 1;
        }
        return 1;
    }
    if (r == 0) {
        func_800EA604(D_800EB1F0, 1);
        if (FIELD(sub, u8 *, 0xC) != NULL && !(((Win27 *)FIELD(sub, u8 *, 0xC))->flags & 2)) {
            func_8017C384(FIELD(sub, u8 *, 0xC));
            return 2;
        }
        return 2;
    }
    return 0;
}

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
