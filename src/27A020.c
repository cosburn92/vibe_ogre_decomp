#include "common.h"
#include "chunk.h"
#include "heap.h"

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
    /* 0x00 */ u8 *win;  /* main window */
    /* 0x04 */ void *fn; /* its draw callback */
    /* 0x08 */ s16 x;
    /* 0x0A */ s16 y;
    /* 0x0C */ s16 h;
    /* 0x0E */ s16 w;
    /* 0x10 */ u8 unk10[4];
    /* 0x14 */ s32 w14;
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

s32 func_8016E1DC(s32 a, s32 b);
void func_80226980_ovl_27A020(void);
void func_801CBF44(void);
s32 func_802283C0_ovl_27A020(void);
s32 func_8022B5EC_ovl_27A020(u16 msg, Task27 *t);
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
void func_8017BED4(void);
void func_8022A95C_ovl_27A020(Obj27 *o);
void func_8022A750_ovl_27A020(Obj27 *o);
void func_8022AAA4_ovl_27A020(Obj27 *o);
void func_8022AC5C_ovl_27A020(Obj27 *o);
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

s32 func_801C8E30(u8 **u);
u8 **func_801C8FE8(s32 i);

/* Replays the battle-end animations of the 20 units: the leader's parts (0), petrified units (0x26),
 * dead units (0x20, clearing their parts' 0x34), the rest unless func_801C8E30 (8; unit 1 also
 * lowers its parts' 0x1C by 50) */
void func_802264B4_ovl_27A020(void) {
    s32 i;
    u32 k;
    u8 **u;

    for (i = 0; i < 20; i++) {
        u = func_801C8FE8(i);
        if (u == NULL) {
            continue;
        }
        if (i == 0) {
            for (k = 0; k < 3; k++) {
                if (u[k] != NULL) {
                    func_801AD9D4(u[k] + 0x44, 0);
                }
            }
        } else if (FIELD(u, s32, 0x40) & 2) {
            for (k = 0; k < 3; k++) {
                if (u[k] != NULL) {
                    func_801AD9D4(u[k] + 0x44, 0x26);
                }
            }
        } else if (FIELD(u, u16, 0x20) == 0) {
            for (k = 0; k < 3; k++) {
                if (u[k] != NULL) {
                    func_801AD9D4(u[k] + 0x44, 0x20);
                    FIELD(u[k], s16, 0x34) = 0;
                }
                if (u[k + 3] != NULL) {
                    FIELD(u[k + 3], s16, 0x34) = 0;
                }
            }
        } else if (func_801C8E30(u) == 0) {
            for (k = 0; k < 3; k++) {
                if (u[k] != NULL) {
                    func_801AD9D4(u[k] + 0x44, 8);
                    if (i == 1) {
                        FIELD(u[k], u16, 0x1C) -= 50;
                    }
                }
                if (u[k + 3] != NULL) {
                    if (i == 1) {
                        FIELD(u[k + 3], u16, 0x1C) -= 50;
                    }
                }
            }
        }
    }
}

#include "scene.h"
void D_80198BE8(void);

/* Creates a scene box: image id, kind b (top bit set), position (x, y), size (w, h), z, colour
 * index col, with flags 4 (f1) and 8 (f2); returns its slot */
#ifdef NON_MATCHING
/* 109/109 instructions, 92 words differ: register allocation (the original keeps z in s6 and spills id and col to the frame) */
s32 func_80226644_ovl_27A020(u8 id, u16 b, u32 x, u32 y, u16 w, u16 col, u32 z, u8 f1, u8 f2) {
    s32 i = func_8007F648((s32)D_80198BE8, 0, 0, 0, 0);
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

typedef struct {
    s32 m[16];
} Mtx27; /* size 0x40 */
typedef struct {
    s16 v[8];
} Vtx27; /* size 0x10 */
/* This frame's buffers */
typedef struct {
    /* 0x00 */ void *p0;
    /* 0x04 */ void *p4;
    /* 0x08 */ Mtx27 *mtx;
    /* 0x0C */ void *pC;
    /* 0x10 */ Vtx27 *vtx;
} FbSet27;
/* Battle-screen state block (0xA0 bytes): two sprite layers, then viewport adjustments */
typedef struct {
    /* 0x00 */ u8 *spr;
    /* 0x04 */ u8 unk04[0x2C];
    /* 0x30 */ u8 *spr2;
    /* 0x34 */ u8 unk34[0x50];
    /* 0x84 */ s16 transX; /* viewport adjustments, 1/4 pixel */
    /* 0x86 */ s16 transY;
    /* 0x88 */ s16 scaleX;
    /* 0x8A */ s16 scaleY;
    /* 0x8C */ u8 unk8C[0x14];
} Battle27;
extern Battle27 D_801D0770;
extern u16 D_800C4BE4;
extern u16 D_800E79E0;
extern Mtx27 *D_801969B0;
extern Vtx27 *D_80197178;
typedef struct {
    s16 vscale[4];
    s16 vtrans[4];
} Vp27; /* a viewport; the draw sets this one but loads the one after it (D_8022C870) */
extern Vp27 D_8022C860_ovl_27A020;
extern Vp27 D_8022C870_ovl_27A020;
extern u8 D_801CEAA8;
extern u8 D_801CEAA9;
extern u8 D_801CEAAA;
s32 func_801B5934(void);
s32 func_801B5940(void);
void func_801B8F2C(u8 *o);
void func_801BB58C(u8 *pp);
void func_801BB87C(u8 *pp);
void func_8020E4A0(void);
void func_8020E3A0(u16 a);
void func_801B574C(u8 a);
void func_801B0300(void);
void func_8022BF68_ovl_27A020(void);

#define GFX27(w0_, w1_)         \
    {                           \
        Gfx *_g = D_800E9BA0++; \
                                \
        _g->w0 = (w0_);         \
        _g->w1 = (w1_);         \
    }

/* Shop frame draw: points the matrix/vertex cursors at this frame's pools, sets the viewport from
 * the battle-screen block, draws both sprite layers and the scene, then a full-screen black
 * rectangle with the shop's fade alpha, and advances the pool counts by what was used */
void func_80226DA8_ovl_27A020(FbSet27 *fb) {
    D_801969B0 = fb->mtx + D_800C4BE4;
    D_80197178 = fb->vtx + D_800E79E0;
    GFX27(0xE7000000, 0);
    D_8022C860_ovl_27A020.vtrans[0] = D_801D0770.transX + 0x280;
    D_8022C860_ovl_27A020.vtrans[1] = D_801D0770.transY + 0x1E0;
    D_8022C860_ovl_27A020.vscale[0] = D_801D0770.scaleX + 0x280;
    D_8022C860_ovl_27A020.vscale[1] = D_801D0770.scaleY + 0x1E0;
    GFX27(0xDC080008, (u32)&D_8022C870_ovl_27A020);
    if (func_801B5934()) {
        func_801B8F2C((u8 *)&D_801D0770.spr);
        func_801BB58C((u8 *)&D_801D0770.spr);
    }
    func_8020E4A0();
    func_8020E3A0(1);
    func_801B574C(D_801CEAA8);
    func_8022BF68_ovl_27A020();
    GFX27(0xE7000000, 0);
    GFX27(0xE7000000, 0);
    GFX27(0xE3000A01, 0); /* 1-cycle */
    GFX27(0xE7000000, 0);
    func_801B0300();
    func_801B574C(D_801CEAA9);
    if (func_801B5940()) {
        func_801B8F2C((u8 *)&D_801D0770.spr2);
        func_801BB87C((u8 *)&D_801D0770.spr2);
    }
    func_8020E3A0(2);
    func_801B574C(D_801CEAAA);
    GFX27(0xDC080008, (u32)&D_8022C870_ovl_27A020);
    GFX27(0xE7000000, 0);
    GFX27(0xFCFFFFFF, 0xFFFDF6FB); /* shade colour */
    GFX27(0xE200001C, 0x00504240); /* translucent surface */
    GFX27(0xFA000000, D_8022C5C0_ovl_27A020[5]);
    GFX27(0xE7000000, 0);
    GFX27(0xE44FC3BC, 0);
    GFX27(0xE1000000, 0);
    GFX27(0xF1000000, 0);
    GFX27(0xE7000000, 0);
    GFX27(0xE7000000, 0);
    D_800C4BE4 += D_801969B0 - (fb->mtx + D_800C4BE4);
    D_800E79E0 += D_80197178 - (fb->vtx + D_800E79E0);
}

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
void func_802285B0_ovl_27A020(void) {
    Task27 *p;
    s32 i;

    D_8022D0F2_ovl_27A020 = 5;
    D_8022C890_ovl_27A020 = HMalloc(0x118);
    D_8022D148_ovl_27A020 = D_8022C890_ovl_27A020;
    for (i = 0; i < D_8022D0F2_ovl_27A020; i++) {
        D_8022D148_ovl_27A020[i].fn = NULL;
    }
    p = D_8022D148_ovl_27A020;
    for (i = 1; i < D_8022D0F2_ovl_27A020; i++) {
        p->next = i;
        p++;
    }
    p->next = 0xFFFF;
}

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

/* Image chunk header: pixels follow at +8, then the palette */
typedef struct {
    /* 0x00 */ u8 unk0[3];
    /* 0x03 */ u8 siz;
    /* 0x04 */ u16 w;
    /* 0x06 */ u16 h;
} Img27;
Img27 *func_801AD60C(s32 id);
s32 func_801BE9A8(s32 siz, s32 w);
s32 func_801BE978(s32 siz, s32 w, s32 h);

/* Draws icon `icon` (an 8-row band of the 0x321B8C icon strip, CI8 with a 256-colour palette)
 * 0x38 wide at screen position (x, y); -1 draws nothing */
void func_802293B4_ovl_27A020(s32 x, s32 y, s16 icon) {
    Img27 *img;
    u8 *tex;
    s32 row;

    if (icon != -1) {
        img = func_801AD60C(0x321B8C);
        row = icon * 8;
        tex = (u8 *)img + (func_801BE9A8(img->siz, img->w) * row + 8);
        gDPPipeSync(D_800E9BA0++);
        gDPLoadTLUT_pal256(D_800E9BA0++, (u8 *)img + (func_801BE978(1, img->w, img->h) + 8));
        gDPLoadTextureBlock(D_800E9BA0++, tex, G_IM_FMT_CI, G_IM_SIZ_8b, img->w, 8, 0, 0, 0, 0, 0, 0, 0);
        gDPPipeSync(D_800E9BA0++);
        gSPScisTextureRectangle(D_800E9BA0++, x << 2, y << 2, (x + 0x38) << 2, (y + 8) << 2, 0, 0, 0, 1 << 10,
                                1 << 10);
        gDPPipeSync(D_800E9BA0++);
    }
}

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

/* Draws the bobbing cursor beside the selected list row (o->0x10) inside the window's scissor
 * box; the row's y skips the rows above that carry a mark */
#ifdef NON_MATCHING
/* 220/220 instructions: registers and scheduling differ (the original hoists the constant 2 and x - 16 out of the row loop, after i = 0, and copies the scissor command pointer) */
void func_8022AC5C_ovl_27A020(Obj27 *o) {
    List27 *l = (List27 *)&o->w18;
    s16 x = FIELD(FIELD(o, u8 *, 0), s32, 0x2C);
    s16 y = FIELD(FIELD(o, u8 *, 0), s32, 0x30) + 3;
    s16 i;
    u8 *e;
    Gfx *g;
    s32 two;
    s16 left;

    gDPPipeSync(D_800E9BA0++);
    g = D_800E9BA0++;
    {
        u8 *win = FIELD(o, u8 *, 0);
        s32 y0 = FIELD(win, s32, 0x30);

        g->w0 = 0xED000000 | _SHIFTL((s32)((f32)0 * 4.0f), 12, 12) |
                 _SHIFTL((s32)((f32)(y0 < 0 ? 0 : y0) * 4.0f), 0, 12);
        g->w1 = _SHIFTL((s32)((f32)(FIELD(FIELD(o, u8 *, 0), s32, 0x34) == 320 ? 319 : FIELD(FIELD(o, u8 *, 0), s32, 0x34)) * 4.0f), 12, 12) |
                 _SHIFTL((s32)((f32)(FIELD(FIELD(o, u8 *, 0), s32, 0x38) == 240 ? 239 : FIELD(FIELD(o, u8 *, 0), s32, 0x38)) * 4.0f), 0, 12);
    }
    gDPPipeSync(D_800E9BA0++);
    i = 0;
    two = 2;
    left = x - 16;
    for (; i < 5; i++) {
        e = (u8 *)l->items[i];
        if (List27_EntryMark(l, e)) {
            if (i == FIELD(o, s16, 0x10)) {
                s16 cx;
                s16 cy;

                if (((u8 (*)(u8, u8))func_8016DE1C)(e[0x4B], e[0x4F]) == two) {
                    y += 7;
                } else {
                    y += 8;
                }
                if (D_8022CB30_ovl_27A020[D_8022CB2C_ovl_27A020] == 0x63) {
                    D_8022CB2C_ovl_27A020 = 0;
                }
                cy = y + 2;
                cx = x - 13;
                if (D_8022CB28_ovl_27A020 == 1) {
                    cx = D_8022CB30_ovl_27A020[D_8022CB2C_ovl_27A020++] + left;
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
                return;
            }
            y += 36;
            func_8016DE1C(e[0x4B], e[0x4F]);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/27A020", func_8022AC5C_ovl_27A020);
#endif

void func_8022AFCC_ovl_27A020(Obj27 *o) {
    *o->w18 = 0;
    o->h1C = 0;
    o->h1E ^= o->h1E; /* the original loads and xors the field (lhu/xor/sh); "= 0" is two instructions shorter */
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
    /* 0x1A */ u8 unk1A[4];
    /* 0x1E */ s16 moveTime;
    /* 0x20 */ u8 unk20[6];
    /* 0x26 */ u16 flags26;
    /* 0x28 */ u16 flags;
    /* 0x2A */ u8 unk2A[0x12];
    /* 0x3C */ s32 move[4]; /* rectangle to move to (x0, y0, x1, y1) */
    /* 0x4C */ s32 rect4C[4];
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

typedef struct {
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
} Rect27;
extern Rect27 D_8022D098_ovl_27A020;
extern Rect27 D_8022D0A0_ovl_27A020;
extern u8 D_8022CB84_ovl_27A020[];
void func_80184130(Win27 *w);
void func_8022BC30_ovl_27A020(void);
u8 *func_8017F334(s32 id);

/* Starts window w moving to rectangle r (x0, y0, x1, y1) over 8 frames */
static inline void Win27_MoveTo(Win27 *w, s16 *r) {
    if (w == NULL || r == NULL) {
        return;
    }
    w->moveTime = 8;
    w->flags26 |= 1;
    w->move[0] = r[0];
    w->move[1] = r[1];
    w->move[2] = r[2];
    w->move[3] = r[3];
    func_80184130(w);
}

static inline void Win27_SetRect4C(Win27 *w, Rect27 *r) {
    w->rect4C[0] = r->x0;
    w->rect4C[1] = r->y0;
    w->rect4C[2] = r->x1;
    w->rect4C[3] = r->y1;
}

/* Closes window w unless it is already closing */
static inline void Win27_Close(Win27 *w) {
    if (w != NULL && !(w->flags & 2)) {
        func_8017C384((u8 *)w);
    }
}

/* Shop yes/no task: 0x10 sets it up, 0x100 opens the prompt window, 0x102 opens the list window
 * beside the marked entries (none marked: 0x10B), 0x103 runs the prompt (yes 0x10A, no 0x10B,
 * 0x10C), 0x106/0x108 close the windows; the window handles are refreshed every call */
s32 func_8022B5EC_ovl_27A020(u16 msg, Task27 *t) {
    Obj27 *o = (Obj27 *)((u8 *)t + 0x18);
    u8 *sub = (u8 *)&o->w18;
    Rect27 a;
    Rect27 b;
    Rect27 r;
    Rect27 r2;
    Rect27 r3;
    s16 res;

    switch (msg) {
        case 0x11:
            func_802287C0_ovl_27A020(t);
            break;
        case 0x10:
            FIELD(t, u8 *, 0) = D_8022CB84_ovl_27A020;
            o->w18 = (s32 *)D_8022D134_ovl_27A020;
            o->w14 = 0;
            o->h1C = 0;
            o->w24 = NULL;
            o->w20 = NULL;
            D_8022CB20_ovl_27A020 = o;
            D_8022CB28_ovl_27A020 = 0;
            t->state = 0x100;
            o->h1E ^= o->h1E; /* the original loads and xors the field (lhu/xor/sh), as in func_8022AFCC */
            break;
        case 0x100:
            a = D_8022D098_ovl_27A020;
            b = D_8022D098_ovl_27A020;
            a.y0 = b.y0 = 0xCD;
            a.y1 = b.y1 = 0xE1;
            b.x0 = a.x0 = a.x1 = 0x1E;
            b.x1 = 0x74;
            o->w20 = func_8017BFB0(2, 0, func_8022BC30_ovl_27A020, a.x0, a.y0, a.x1, a.y1, b.x0, b.y0, b.x1, b.y1);
            t->state = 0x109;
            break;
        case 0x102:
            r = D_8022D0A0_ovl_27A020;
            r2 = D_8022D098_ovl_27A020;
            res = func_8022AFE8_ovl_27A020(o);
            if (res == 0) {
                t->state = 0x10B;
                break;
            }
            r.x1 = o->x + o->w;
            if (o->win == NULL) {
                o->win = func_8017BFB0(0x401, 0, o->fn, r.x0, r.y0, r.x1, r.y1, o->x, o->y, (s16)(o->x + o->w),
                                       (s16)(o->y + o->h));
            }
            r.x1 = r.x0 + o->w;
            Win27_SetRect4C((Win27 *)o->win, &r);
            r2.y0 = o->y - 0x19;
            r2.y1 = o->y - 5;
            r2.x0 = o->x;
            r2.x1 = r2.x0 + 0x56;
            Win27_MoveTo((Win27 *)o->w20, &r2.x0);
            r2.x0 = r2.x1 = 10;
            Win27_SetRect4C((Win27 *)o->w20, &r2);
            t->hE = 9;
            t->hC = 0x103;
            t->state = 0;
            break;
        case 0x103:
            res = func_8022A120_ovl_27A020(o);
            D_8022CB28_ovl_27A020 = 1;
            if (res == 1) {
                func_800EA604(D_800EB1F0, 0);
                t->state = 0x10A;
            } else if (res == 2) {
                func_800EA604(D_800EB1F0, 1);
                t->state = 0x10B;
            } else if (res == 3) {
                func_800EA604(D_800EB1F0, 9);
                t->state = 0x10C;
            }
            break;
        case 0x106:
            Win27_Close((Win27 *)o->w24);
            Win27_Close((Win27 *)o->win);
            t->hE = 3;
            t->hC = 0x107;
            t->state = 0;
            break;
        case 0x107:
            r3 = D_8022D098_ovl_27A020;
            r3.y0 = 0xCD;
            r3.y1 = 0xE1;
            r3.x0 = 0x1E;
            r3.x1 = 0x74;
            Win27_MoveTo((Win27 *)o->w20, &r3.x0);
            r3.x0 = r3.x1 = 10;
            Win27_SetRect4C((Win27 *)o->w20, &r3);
            t->state = 0x109;
            break;
        case 0x108:
            Win27_Close((Win27 *)o->w24);
            Win27_Close(FIELD(sub, Win27 *, 8));
            Win27_Close((Win27 *)o->win);
            t->hE = 0xF;
            t->hC = 0x11;
            t->state = 0;
            break;
        case 0x109:
        case 0x10A:
        case 0x10B:
        case 0x10C:
            break;
    }
    o->win = func_8017F334(0x401);
    o->w20 = func_8017F334(2);
    o->w24 = func_8017F334(4);
    return 0;
}

void func_8022BC08_ovl_27A020(void) {
    func_8022874C_ovl_27A020((void (*)(s32, Task27 *))func_8022B5EC_ovl_27A020);
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
