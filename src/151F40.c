#include "common.h"

/* 151F40 */

#include "tables.h"
#include "scene.h"

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

typedef struct {
    Character c;
    u8 pad[4];
} PlayerChar;

typedef struct {
    /* 0x00 */ s32 w0;
    /* 0x04 */ u8 unk04[4];
    /* 0x08 */ s32 w8;
    /* 0x0C */ u8 unk0C[0x18];
} Rec151; /* size 0x24 */

extern Gfx *D_800E9BA0;
extern PlayerChar D_80193BC0[];
extern Character D_80195560[];
extern u8 *D_801F0B90;
extern u8 D_80210258_ovl_14EBE0[];
extern u8 D_802102B8_ovl_14EBE0[];
extern u8 D_80213648_ovl_14EBE0[];
extern void *D_80214F5C_ovl_14EBE0;
extern u8 D_8018F480;

void func_80200F70_ovl_14EBE0(void *a, void *b, s32 c, s32 d, s32 e);
void func_80200DD0_ovl_14EBE0(void *a, s32 b, s32 c);
void func_80179018(void);
void *LoadChunk(u32 handle);
void *HFree(void *p);
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern u8 *D_80213778_ovl_14EBE0;
extern u8 *D_80213670_ovl_14EBE0;
extern u16 (*D_80213068_ovl_14EBE0[])(u8 cls, u8 base);
extern s8 (*D_80213054_ovl_14EBE0[])(u16 v);
extern u16 D_80190EBC[];
extern u16 D_80190F82;
u16 func_80201D1C_ovl_14EBE0(u8 side, u8 idx, u8 stat);
void func_802001A8_ovl_14EBE0(void *a, s32 b, u16 c, s32 d);
extern u8 D_80213780_ovl_14EBE0;
extern u8 D_80213781_ovl_14EBE0;
extern char D_80214D10_ovl_14EBE0[];
s32 func_80076F5C(s32 a, void *fn, s32 b, s32 c, s32 d, s32 e, s32 f);
void func_80205F2C_ovl_14EBE0();
void func_8020CDA0_ovl_14EBE0(s32 a);
void osSyncPrintf(const char *fmt, ...);
extern u8 *D_801F36C0;
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/151F40", func_80200DD0_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80200F70_ovl_14EBE0);

/* Loads a 256-colour TLUT from pal */
void func_8020122C_ovl_14EBE0(u32 pal) {
    Gfx *g;

    g = D_800E9BA0++;
    g->w0 = 0xFD100000;
    g->w1 = pal;
    g = D_800E9BA0++;
    g->w0 = 0xE8000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xF5000100;
    g->w1 = 0x07000000;
    g = D_800E9BA0++;
    g->w0 = 0xE6000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xF0000000;
    g->w1 = 0x073FC000;
    g = D_800E9BA0++;
    g->w0 = 0xE7000000;
    g->w1 = 0;
}

/* Loads a 16-colour TLUT from pal */
void func_802012D8_ovl_14EBE0(u32 pal) {
    Gfx *g;

    g = D_800E9BA0++;
    g->w0 = 0xFD100000;
    g->w1 = pal;
    g = D_800E9BA0++;
    g->w0 = 0xE8000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xF5000100;
    g->w1 = 0x07000000;
    g = D_800E9BA0++;
    g->w0 = 0xE6000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xF0000000;
    g->w1 = 0x0703C000;
    g = D_800E9BA0++;
    g->w0 = 0xE7000000;
    g->w1 = 0;
}

INCLUDE_ASM("asm/nonmatchings/151F40", func_80201384_ovl_14EBE0);

/* Rank 1-3 of stat i: how many thirds of the cap (D_80190F82) it reaches */
#ifdef NON_MATCHING
/* loop condition compiled as a branchless and in the original */
u16 func_802014C8_ovl_14EBE0(u8 i) {
    s32 pad;
    u16 q = D_80190F82 / 3;
    s32 v = D_80190EBC[i] - q;
    u16 n = 0;

    do {
        n++;
        if (!(v > 0 && n < 3)) {
            break;
        }
        v -= q;
    } while (1);
    if (n >= 4) {
        n = 3;
    }
    return n;
}
#else
INCLUDE_ASM("asm/nonmatchings/151F40", func_802014C8_ovl_14EBE0);
#endif

INCLUDE_ASM("asm/nonmatchings/151F40", func_8020153C_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_802017C0_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80201A44_ovl_14EBE0);

#ifdef NON_MATCHING
/* Index clamp and table select laid out differently. */
void func_80201AFC_ovl_14EBE0(u8 enemy, u8 idx, u8 *cls, u8 *base) {
    Character *c;

    if (idx >= 100) {
        idx = 0;
    }
    if (enemy) {
        c = &D_80195560[idx];
    } else {
        c = &D_80193BC0[idx].c;
    }
    *cls = c->cls;
    *base = c->baseCls;
}
#else
INCLUDE_ASM("asm/nonmatchings/151F40", func_80201AFC_ovl_14EBE0);
#endif

INCLUDE_ASM("asm/nonmatchings/151F40", func_80201B68_ovl_14EBE0);

s16 func_80201C7C_ovl_14EBE0(u8 side, u8 idx, u8 k) {
    s16 sum = 0;
    s32 i;

    for (i = 1; i < 5; i++) {
        sum += D_80213054_ovl_14EBE0[k](func_80201D1C_ovl_14EBE0(side, idx, i));
    }
    return sum;
}

u16 func_80201D1C_ovl_14EBE0(u8 side, u8 idx, u8 stat) {
    Character *c;

    if (side == 0) {
        c = &D_80193BC0[idx].c;
    } else {
        c = &D_80195560[idx];
    }
    return D_80213068_ovl_14EBE0[stat](c->cls, c->baseCls);
}

/* Equipped item `slot` (1-4) of a character (side 0 player, 1 enemy), 0 if slot is out of range */
u16 func_80201D9C_ovl_14EBE0(u8 side, u8 idx, u8 slot) {
    Character *c;
    u16 v;

    if (side == 0) {
        c = &D_80193BC0[idx].c;
    } else {
        c = &D_80195560[idx];
    }
    v = 0;
    switch (slot) {
        case 1:
            v = c->items[0];
            break;
        case 2:
            v = c->items[1];
            break;
        case 3:
            v = c->items[2];
            break;
        case 4:
            v = c->items[3];
            break;
    }
    return v;
}

INCLUDE_ASM("asm/nonmatchings/151F40", func_80201E4C_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80202140_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80202434_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80202728_ovl_14EBE0);

void func_802027DC_ovl_14EBE0(void) {
    Gfx *g = D_800E9BA0++;

    g->w0 = 0xDE000000;
    g->w1 = (u32)D_80213648_ovl_14EBE0;
    func_80200F70_ovl_14EBE0(D_80210258_ovl_14EBE0, D_801F0B90 + 0x948, 0x40, 0x40, 2);
}

void func_80202840_ovl_14EBE0(void) {
    Gfx *g = D_800E9BA0++;

    g->w0 = 0xDE000000;
    g->w1 = (u32)D_80213648_ovl_14EBE0;
    func_80200F70_ovl_14EBE0(D_802102B8_ovl_14EBE0, D_801F0B90 + 0x948, 0x40, 0x40, 2);
}

void func_802028A4_ovl_14EBE0(u8 *p, s32 b, u16 c, u16 d) {
    func_80200DD0_ovl_14EBE0(p, b, 2);
    func_802001A8_ovl_14EBE0(p + 0x14, b, c, -3);
    func_80200DD0_ovl_14EBE0(p + 0x2A, b, 7);
    func_802001A8_ovl_14EBE0(p + 0x32, b, d, -3);
}

void func_80202928_ovl_14EBE0(u8 *p, s32 b) {
    func_80200DD0_ovl_14EBE0(p, b, 2);
    func_80200DD0_ovl_14EBE0(p + 0x2A, b, 7);
}

INCLUDE_ASM("asm/nonmatchings/151F40", func_8020296C_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80202B70_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80202E10_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80202F54_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80203050_ovl_14EBE0);

#ifdef NON_MATCHING
/* Constant select laid out differently. */
void func_80203524_ovl_14EBE0(void *a, s32 b, u8 c) {
    func_80200DD0_ovl_14EBE0(a, b, (c == 3) ? 0x11 : 0x10);
}
#else
INCLUDE_ASM("asm/nonmatchings/151F40", func_80203524_ovl_14EBE0);
#endif

INCLUDE_ASM("asm/nonmatchings/151F40", func_80203558_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80203D9C_ovl_14EBE0);

void func_80203FA4_ovl_14EBE0(s32 a, s32 b) {
    Gfx *g;

    g = D_800E9BA0++;
    g->w0 = 0xE7000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xD7000002;
    g->w1 = 0x80008000;
    func_80200F70_ovl_14EBE0(D_801F36C0 + 0x2E0, D_801F0B90 + 0x27A8, 16, 8, 2);
    func_80200DD0_ovl_14EBE0((void *)a, b, 0x47);
}

INCLUDE_ASM("asm/nonmatchings/151F40", func_80204050_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80204120_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80204210_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_8020439C_ovl_14EBE0);

void func_80204B34_ovl_14EBE0(void) {
    func_80179018();
    D_8018F480 = 0;
}

void func_80204B58_ovl_14EBE0(void) {
    D_80214F5C_ovl_14EBE0 = LoadChunk(0x1DF98EA);
}

void func_80204B80_ovl_14EBE0(void) {
    HFree(D_80214F5C_ovl_14EBE0);
}

/* Number of records (up to the -1 terminator) whose +8 is k */
u8 func_80204BA4_ovl_14EBE0(Rec151 *r, u8 k) {
    u8 n = 0;
    u8 i = 0;
    Rec151 *e;

    do {
        e = &r[i];
        if (e->w8 == k) {
            n++;
        }
        i++;
    } while (e->w0 != -1);
    return n;
}

u8 func_80204BE8_ovl_14EBE0(Rec151 *a, u8 id) {
    s8 j = -1;
    u32 i = 0;
    Rec151 *r;

    do {
        r = &a[(u8)i];
        if (r->w8 == id) {
            j++;
        }
        i++;
    } while (j != (s8)D_80213670_ovl_14EBE0[0x68]);
    return FIELD(r, u8, 3);
}

INCLUDE_ASM("asm/nonmatchings/151F40", func_80204C3C_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_8020521C_ovl_14EBE0);

s32 func_80205D20_ovl_14EBE0(u8 a) {
    u8 *f = &D_80213780_ovl_14EBE0;
    s32 i;
    s32 r;

    if (*f != 0) {
        *f = 0;
        D_80213781_ovl_14EBE0 = a;
        i = func_80076F5C(0xC000, func_80205F2C_ovl_14EBE0, 0x19, 0x28, 0x23, 0x32, 0xC8);
        D_800E82C8[i].unk88 = 0xFF;
        func_8020CDA0_ovl_14EBE0(6);
        r = 1;
    } else {
        osSyncPrintf(D_80214D10_ovl_14EBE0);
        r = 0;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/151F40", func_80205DC8_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80205F2C_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80206340_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80206C70_ovl_14EBE0);

#ifdef NON_MATCHING
/* addu operand order (1 instruction) */
void func_80206D78_ovl_14EBE0(void) {
    u8 *o = D_80213778_ovl_14EBE0;
    s8 v = o[0x5E];
    u8 k = o[0x605 + v * 10];

    if (v == 1) {
        o[0x5D8] = (o + k * 8)[0x35C];
    } else {
        o[0x5D8] = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/151F40", func_80206D78_ovl_14EBE0);
#endif

void func_80206DBC_ovl_14EBE0(u8 a, s16 *p) {
    p[2] = 4;
    p[0] = 0;
    p[1] = 0;
    p[3] = a - 1;
    p[4] = 0xFF;
}

INCLUDE_ASM("asm/nonmatchings/151F40", func_80206DE4_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80206EB4_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80207068_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80207210_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80207380_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_8020746C_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_8020753C_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_8020766C_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80207C94_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_8020808C_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80208304_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80208920_ovl_14EBE0);

/* Insertion sort of n bytes, ascending */
void func_80208A3C_ovl_14EBE0(u8 *a, s16 n) {
    s16 i;
    s16 j;
    u8 t;

    for (i = 1; i < n; i++) {
        t = a[i];
        for (j = i - 1; j >= 0 && a[j] > t; j--) {
            a[j + 1] = a[j];
        }
        a[j + 1] = t;
    }
}

INCLUDE_ASM("asm/nonmatchings/151F40", func_80208ADC_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80208BE4_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_80208E64_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_8020C284_ovl_14EBE0);

INCLUDE_ASM("asm/nonmatchings/151F40", func_8020C7F4_ovl_14EBE0);
