#include "common.h"
#include "tables.h"

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))

typedef struct {
    /* 0x00 */ u8 unk00[0x36];
    /* 0x36 */ u16 items[4];
    /* 0x3E */ u8 unk3E[2];
    /* 0x40 */ u32 flags;
    /* 0x44 */ u8 unk44[4];
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 cls;
    /* 0x50 */ u8 unk50[4];
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 unk5C[0x14];
    /* 0x70 */ s32 actsMax;
} BattleUnit;

typedef struct {
    s32 (*f0)(void);
    void (*f1)(void);
    void (*f2)(void);
    void (*f3)(s16);
    void (*f4)(s16);
    s32 (*f5)(BattleUnit *u);
} BattleCallbacks;

extern BattleCallbacks *D_801D0810_ovl_1F0A30;
extern BattleCallbacks D_801CFC74_ovl_1F0A30;
extern u8 D_801CFC70_ovl_1F0A30;
extern u8 D_801976D8;
extern u16 D_80197B60;
extern u8 D_80197B62;
extern struct { u8 b[12]; } D_801976DC[];
extern u8 D_800E9C0A[];
extern u8 *D_801CE8BC_ovl_1F0A30;
typedef struct {
    u8 unk0[0xD];
    u8 items[10];
    u8 unk17[2];
} SquadRec; /* size 0x19 */
extern SquadRec gSquads[];
typedef struct BattleObj20 {
    void (*fn)(struct BattleObj20 *self);
} BattleObj20;
u8 func_8016E338(u8 a, u8 cls, u8 c);
s32 func_8016F5C8(u16 id);
u8 func_801C9FA4_ovl_1F0A30(s32 idx);
extern void *D_801D0824_ovl_1F0A30;
u8 func_8016DE1C(u8 a, u8 b);
u16 func_8016FA34(u16 a, u16 b, u16 c, u16 d);
s32 func_801C8B84_ovl_1F0A30(BattleUnit *u);
BattleUnit *func_801C8FE8_ovl_1F0A30(u32 i);
void HFree(void *p);

extern u8 D_801CFC8C_ovl_1F0A30[];



void func_801C8850_ovl_1F0A30(void) {
    D_801D0810_ovl_1F0A30 = &D_801CFC74_ovl_1F0A30;
}

s32 func_801C8864_ovl_1F0A30(void) {
    if (D_801D0810_ovl_1F0A30->f0 != NULL) {
        return D_801D0810_ovl_1F0A30->f0();
    }
    return 1;
}

void func_801C889C_ovl_1F0A30(void) {
    if (D_801D0810_ovl_1F0A30->f1 != NULL) {
        D_801D0810_ovl_1F0A30->f1();
    }
}

void func_801C88CC_ovl_1F0A30(void) {
    if (D_801D0810_ovl_1F0A30->f2 != NULL) {
        D_801D0810_ovl_1F0A30->f2();
    }
}

void func_801C88FC_ovl_1F0A30(s16 a) {
    if (D_801D0810_ovl_1F0A30->f3 != NULL) {
        D_801D0810_ovl_1F0A30->f3(a);
    } else {
        D_801CFC70_ovl_1F0A30 = 0;
    }
}

void func_801C893C_ovl_1F0A30(s16 a) {
    if (D_801D0810_ovl_1F0A30->f4 != NULL) {
        D_801D0810_ovl_1F0A30->f4(a);
    }
}

u8 func_801C1AA4_ovl_1F0A30(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, u8 *g, s32 h, s32 i);
void func_801C1EE8_ovl_1F0A30(s32 *out, s32 a, u8 b);
u8 func_801BC76C_ovl_1F0A30(void);
u8 func_801BC838_ovl_1F0A30(void);
u8 func_801BC914_ovl_1F0A30(void);
u8 func_801C1C1C_ovl_1F0A30(u32 a, s32 w, s32 i, u8 *c, u8 *d1, u8 *d2);
void func_801ADCBC_ovl_1F0A30(void *u);
typedef struct {
    void *name;
    s32 index;
    u8 *buf;
    s32 size;
} Arc16_20BCE0;
extern Arc16_20BCE0 D_801D0640_ovl_1F0A30;
s32 ChunkSize(s32 id);
void *LoadChunkRaw(void *dst, s32 id);
s32 ReadU32BE(void *p);
void DecodeLZ(void *dst, void *src);
void func_8007ACB0(void *arc, void *reqs, s32 n);
void *func_80071C04(s32 size);
u8 *func_801CBE18_ovl_1F0A30(s32 a, s32 x, s32 y, s32 z);
void func_801B3CB8_ovl_1F0A30();
void func_801B5524_ovl_1F0A30();
extern s32 D_801CE8FC_ovl_1F0A30;
/* --- end decls --- */

u8 func_8016E230(u8 a, u8 cls, u8 c);
u8 func_8016E458(u8 a);
u8 func_8016E470(u8 a, u16 i0, u16 i1, u16 i2, u16 i3);
void func_8016E50C(u8 *a, u8 b, u8 cls, u8 c, u8 d, u16 i0, u16 i1, u16 i2, u16 i3);
u8 func_8016F5E0(u16 id);

/* Unit u's current element: from the battle callback if one is set, else from its class
 * and equipment */
s32 func_801C896C_ovl_1F0A30(BattleUnit *u) {
    u8 a;
    u8 k;
    u8 t;

    if (D_801D0810_ovl_1F0A30->f5 != NULL) {
        return D_801D0810_ovl_1F0A30->f5(u);
    }
    if (u->unk48 == 0x101) {
        return u->unk00[0x33];
    }
    a = func_8016E230(u->unk48, u->cls, func_801C9FA4_ovl_1F0A30(u->unk58));
    k = func_8016E458(a);
    if ((u8)(k - 3) < 2 || k == 5) {
        if ((u8)(a - 0x31) < 2) {
            return u->unk00[0x33];
        }
        if (a == 0x91) {
            t = func_8016F5E0(func_801C8FB8_ovl_1F0A30(u));
            if (t >= 15) {
                return u->unk00[0x33];
            }
            return t;
        }
        func_8016E50C(&a, u->unk48, u->cls, a, u->unk00[0x33], u->items[0], u->items[1], u->items[2], u->items[3]);
    }
    return func_8016E470(a, u->items[0], u->items[1], u->items[2], u->items[3]);
}

s32 func_801C8AA4_ovl_1F0A30(s32 a) {
    return (a - 1) * 38;
}

s32 func_801C8AC0_ovl_1F0A30(s32 a) {
    return (a - 4) * 38;
}

u8 func_801C8ADC_ovl_1F0A30(void) {
    return D_801976D8 & 0x40;
}

u8 func_801C8AEC_ovl_1F0A30(void) {
    return D_801976D8 & 8;
}

u16 func_801C8AFC_ovl_1F0A30(void) {
    return D_80197B60;
}

u8 func_801C8B08_ovl_1F0A30(void) {
    return D_80197B62;
}

u8 func_801C8B14_ovl_1F0A30(BattleUnit *u) {
    u8 *p;

    if (u == NULL) {
        return 0;
    }
    p = func_801C8B84_ovl_1F0A30(u) ? D_801976DC[0].b : D_801976DC[1].b;
    return p[1] & 2;
}

s32 func_801C8B54_ovl_1F0A30(void) {
    return D_800E9C0A[8] == 1;
}

inline s32 func_801C8B68_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u->flags >> 8) & 1;
}

inline s32 func_801C8B84_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return ((u->flags >> 8) ^ 1) & 1;
}

inline s32 func_801C8BA4_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u->flags >> 10) & 1;
}

/* Whether units a and b are on opposite sides */
s32 func_801C8BC0_ovl_1F0A30(u8 a, u8 b) {
    return func_801C8B84_ovl_1F0A30(func_801C8FE8_ovl_1F0A30(a)) ^ func_801C8B84_ovl_1F0A30(func_801C8FE8_ovl_1F0A30(b));
}

inline s32 func_801C8C3C_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u->flags >> 12) & 1;
}

inline s32 func_801C8C58_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u->flags >> 9) & 1;
}

inline s32 func_801C8C74_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return u->cls == 1;
}

s32 func_801C8C90_ovl_1F0A30(BattleUnit *u) {
    s32 r;
    s32 c;

    if (u == NULL) {
        return 0;
    }
    c = u->cls;
    r = 0;
    if (c == 10 || c == 25 || c == 123) {
        r = 1;
    }
    return r;
}

s32 func_801C8CD4_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u32)(u->cls - 0x47) < 2;
}

s32 func_801C8CF0_ovl_1F0A30(s32 c) {
    s32 r = 0;

    if ((u32)(c - 0x2D) < 2 || c == 0x2F || c == 0x30) {
        r = 1;
    }
    return r;
}

s32 func_801C8D24_ovl_1F0A30(BattleUnit *u) {
    s32 c;
    s32 r;

    if (u == NULL) {
        return 0;
    }
    c = u->cls;
    r = 0;
    if ((u32)(c - 45) < 2 || c == 47) {
        r = 1;
    } else if (c == 48) {
        r = 1;
    }
    return r;
}

s32 func_801C8D68_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u32)(u->cls - 2) < 0x22;
}

/* The original tests with branches (bnez / bne) rather than set-compares; GCC merges these. */
/* Young Dragon..Tiamat (56-68) or Death Bahamut (164). */
s32 IsDragon(BattleUnit *u) {
    s32 c;
    s32 r;

    if (u == NULL) {
        return 0;
    }
    c = u->cls;
    r = 0;
    if ((u32)(c - 56) < 13) {
        r = 1;
    } else if (c == 164) {
        r = 1;
    }
    return r;
}

/* The original tests with branches (bnez / bne) rather than set-compares; GCC merges these. */
s32 func_801C8DBC_ovl_1F0A30(BattleUnit *u) {
    s32 c;
    s32 r;

    if (u == NULL) {
        return 0;
    }
    c = u->unk48;
    r = 0;
    if ((u32)(c - 135) < 2) {
        r = 1;
    } else if (c == 161) {
        r = 1;
    }
    return r;
}

s32 func_801C8DF4_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return func_8016DE1C(((u8 *)u)[0x4B], ((u8 *)u)[0x4F]) == 2;
}

inline s32 func_801C8E30_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 1;
    }
    return u->flags & 1;
}

s32 func_801C8E48_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u->flags >> 5) & 1;
}

s32 func_801C8E64_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u->flags >> 3) & 1;
}

s32 func_801C8E80_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u->flags >> 2) & 1;
}

inline s32 func_801C8E9C_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u->flags >> 1) & 1;
}

s32 func_801C8EB8_ovl_1F0A30(BattleUnit *u) {
    if (u == NULL) {
        return 0;
    }
    return (u->flags >> 4) & 1;
}

s32 func_801C8ED4_ovl_1F0A30(s32 a) {
    s32 r = 0;

    if ((u32)(a - 32) < 2 || a == 34) {
        r = 1;
    } else if (a == 35 || a == 103) {
        r = 1;
    }
    return r;
}

s32 func_801C8F18_ovl_1F0A30(s32 a) {
    return a == 12;
}

s32 func_801C8F24_ovl_1F0A30(BattleUnit *u) {
    s32 r;

    if ((u8)(func_8016F5C8(u->items[0]) - 14) < 2) {
        r = 1;
    } else if ((u8)(func_8016F5C8(u->items[1]) - 14) < 2) {
        r = 1;
    } else if ((u8)(func_8016F5C8(u->items[2]) - 14) < 2) {
        r = 1;
    } else {
        r = (u8)(func_8016F5C8(u->items[3]) - 14) < 2;
    }
    return r;
}

u16 func_801C8FB8_ovl_1F0A30(BattleUnit *u) {
    return func_8016FA34(u->items[0], u->items[1], u->items[2], u->items[3]);
}

BattleUnit *func_801C8FE8_ovl_1F0A30(u32 i) {
    u8 *base;
    s32 off;

    if (i < 20) {
        base = D_801CE8BC_ovl_1F0A30;
        off = i * 0xF8;
        if (*(s32 *)(base + off + 0x20C) != 0) {
            return (BattleUnit *)(base + (off + 0x1C4));
        }
    }
    return NULL;
}

/* Inlined form of func_801C8FE8 used by the unit-search loops (base loaded up front) */
static inline BattleUnit *BattleGetUnit(u32 i) {
    u8 *base = D_801CE8BC_ovl_1F0A30;
    s32 off;

    if (i < 20) {
        off = i * 0xF8;
        if (*(s32 *)(base + off + 0x20C) != 0) {
            return (BattleUnit *)(base + (off + 0x1C4));
        }
    }
    return NULL;
}

extern s32 D_801CE8EC_ovl_1F0A30;
extern s32 D_801CE8F0_ovl_1F0A30;
extern s32 D_801CE8F4_ovl_1F0A30;
extern f32 D_801D06FC_ovl_1F0A30;
extern f32 D_801D0700_ovl_1F0A30;
extern f32 D_801D0704_ovl_1F0A30;
extern f32 D_801D0710_ovl_1F0A30;
extern f32 D_801D0720_ovl_1F0A30;
extern f32 D_801D072C_ovl_1F0A30;
extern f32 D_801D0730_ovl_1F0A30;
extern f32 D_801D083C_ovl_1F0A30;
void func_80098C20(void *m, f32 x, f32 y, f32 z);
void func_80098AA0(void *m, f32 x, f32 y, f32 z);
void guMtxCatL(void *a, void *b, void *out);
void guRotateRPY(void *m, s32 r, s32 p, s32 y);
void guMtxL2F(f32 mf[4][4], void *m);
void func_801CCD70_ovl_1F0A30(f32 *scr, f32 *v, f32 mf[4][4], f32 *eye, f32 *at, f32 *up, f32 fov);

/* Screen position (x, 240 - y) of map point (x, y, z) through the field camera */
extern s32 D_801CE8EC_ovl_1F0A30;
extern s32 D_801CE8F0_ovl_1F0A30;
extern s32 D_801CE8F4_ovl_1F0A30;
extern f32 D_801D06FC_ovl_1F0A30;
extern f32 D_801D0700_ovl_1F0A30;
extern f32 D_801D0704_ovl_1F0A30;
extern f32 D_801D0710_ovl_1F0A30;
extern f32 D_801D0720_ovl_1F0A30;
extern f32 D_801D072C_ovl_1F0A30;
extern f32 D_801D0730_ovl_1F0A30;
extern f32 D_801D083C_ovl_1F0A30;
void func_80098C20(void *m, f32 x, f32 y, f32 z);
void func_80098AA0(void *m, f32 x, f32 y, f32 z);
void guMtxCatL(void *a, void *b, void *out);
void guRotateRPY(void *m, s32 r, s32 p, s32 y);
void guMtxL2F(f32 mf[4][4], void *m);
void func_801CCD70_ovl_1F0A30(f32 *scr, f32 *v, f32 mf[4][4], f32 *eye, f32 *at, f32 *up, f32 fov);

/* Screen position (x, 240 - y) of map point (x, y, z) through the field camera */
void func_801C9028_ovl_1F0A30(s32 x, s32 y, s32 z, s32 *sx, s32 *sy) {
    f32 scr[2];
    f32 v[3];
    f32 mf[4][4];
    f32 eye[3];
    f32 at[3];
    f32 up[3];
    u8 a[0x40];
    u8 b[0x40];
    u8 c[0x40];

    func_80098C20(b, x, y, z);
    func_80098AA0(a, 0.63f, 0.63f, 0.63f);
    guMtxCatL(a, b, b);
    guRotateRPY(c, D_801CE8EC_ovl_1F0A30, D_801CE8F0_ovl_1F0A30, D_801CE8F4_ovl_1F0A30);
    guMtxCatL(c, b, a);
    func_80098AA0(b, D_801D06FC_ovl_1F0A30, D_801D06FC_ovl_1F0A30, D_801D06FC_ovl_1F0A30);
    guMtxCatL(a, b, c);
    v[0] = v[2] = scr[0] = scr[1] = 0.0f;
    v[1] = 30.0f;
    guMtxL2F(mf, c);
    up[0] = 0.0f;
    up[2] = 0.0f;
    eye[0] = D_801D0730_ovl_1F0A30;
    eye[1] = D_801D083C_ovl_1F0A30;
    eye[2] = D_801D0700_ovl_1F0A30;
    at[0] = D_801D0720_ovl_1F0A30;
    at[1] = D_801D072C_ovl_1F0A30;
    at[2] = D_801D0704_ovl_1F0A30;
    up[1] = 1.0f;
    func_801CCD70_ovl_1F0A30(scr, v, mf, eye, at, up, D_801D0710_ovl_1F0A30);
    if (sx != NULL) {
        *sx = scr[0];
    }
    if (sy != NULL) {
        *sy = 240 - (s32)scr[1];
    }
}

/* Scans the text of t, returning the last two line values */
void func_801C9234_ovl_1F0A30(u8 *t, s32 *prev, s32 *last) {
    u8 c;
    u8 d1;
    u8 d2;
    s32 i = 0;
    u8 r;

    *last = 0;
    *prev = 0;
    for (;;) {
        r = func_801C1C1C_ovl_1F0A30(FIELD(t, u32, 0), (t[0x48] & 1) ? 0x58 : 0x26, i, &c, &d1, &d2);
        if (r == 0) {
            break;
        }
        i++;
        if (r == 1) {
            *prev = *last;
            *last = c;
        }
    }
}

/* The player side's leader */
BattleUnit *func_801C92F8_ovl_1F0A30(void) {
    s32 i;
    BattleUnit *u;

    for (i = 0; i < 20; i++) {
        u = BattleGetUnit(i);
        if (func_801C8B68_ovl_1F0A30(u) && func_801C8C58_ovl_1F0A30(u)) {
            return u;
        }
    }
    return NULL;
}

/* The enemy side's leader */
BattleUnit *func_801C9380_ovl_1F0A30(void) {
    s32 i;
    BattleUnit *u;

    for (i = 0; i < 20; i++) {
        u = BattleGetUnit(i);
        if (func_801C8B84_ovl_1F0A30(u) && func_801C8C58_ovl_1F0A30(u)) {
            return u;
        }
    }
    return NULL;
}

/* The first player-side unit */
BattleUnit *func_801C940C_ovl_1F0A30(void) {
    s32 i;
    BattleUnit *u;

    for (i = 0; i < 20; i++) {
        u = BattleGetUnit(i);
        if (func_801C8B68_ovl_1F0A30(u)) {
            return u;
        }
    }
    return NULL;
}

typedef struct {
    /* 0x00 */ Character c;
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 morale;
    /* 0x36 */ u8 unk36[2];
} PlayerChar20B; /* size 0x38 */
extern PlayerChar20B D_80193BC0[];
extern Character D_80195560[];

static inline s32 IsLord20B(u8 *u) {
    if (u == NULL) {
        return 0;
    }
    return FIELD(u, s32, 0x4C) == 1;
}

/* Builds battle unit u from enemy character k */
void func_801C9478_ovl_1F0A30(u8 *u, s32 k) {
    Character *p = &D_80195560[k];

    bzero(u, 0xF8);
    FIELD(u, s32, 0x48) = p->cls;
    FIELD(u, s32, 0x4C) = p->baseCls;
    u[0xF6] = k;
    u[0x31] = p->level;
    u[0x33] = p->element;
    FIELD(u, u16, 0x22) = p->maxHp;
    FIELD(u, u16, 0x20) = p->hp;
    FIELD(u, u16, 0x24) = p->str;
    FIELD(u, u16, 0x26) = p->vit;
    FIELD(u, u16, 0x28) = p->intl;
    FIELD(u, u16, 0x2A) = p->men;
    FIELD(u, u16, 0x2C) = p->agi;
    FIELD(u, u16, 0x2E) = p->dex;
    u[0x30] = p->luck;
    u[0x34] = u[0x3F] = p->alignment;
    FIELD(u, u16, 0x36) = p->items[0];
    FIELD(u, u16, 0x38) = p->items[1];
    FIELD(u, u16, 0x3A) = p->items[2];
    FIELD(u, u16, 0x3C) = p->items[3];
    u[0x3E] = p->fatigue;
    if (IsLord20B(u)) {
        u[0x3E] = 0;
    }
    if (p->status & 2) {
        FIELD(u, s32, 0x40) |= 0x200;
    }
    if (p->status & 4) {
        FIELD(u, s32, 0x40) |= 2;
    }
    FIELD(u, s32, 0x40) |= 0x500;
}

typedef struct Fx20B {
    /* 0x00 */ void (*fn)();
    /* 0x04 */ u8 unk04[0x10];
    /* 0x14 */ u8 b14;
    /* 0x15 */ u8 unk15[0x1F];
    /* 0x34 */ s16 h34;
    /* 0x36 */ u8 unk36[0xA];
    /* 0x40 */ u8 *owner;
    /* 0x44 */ s32 w44;
    /* 0x48 */ u8 unk48[0x48];
    /* 0x90 */ struct Fx20B *head;
} Fx20B;

/* Creates the two linked effect nodes for slot k of o at its position plus (dx, dy, dz) */
void func_801C95D8_ovl_1F0A30(u8 *o, s32 k, s32 dx, s32 dy, s32 dz) {
    Fx20B *a;
    Fx20B *b;

    a = (Fx20B *)func_801CBE18_ovl_1F0A30(FIELD(o, s32, 0x50), FIELD(o, s32, 0x5C) + dx, FIELD(o, s32, 0x60) + dy,
                                          FIELD(o, s32, 0x64) + dz);
    a->b14 = 0;
    ((Fx20B **)o)[k] = a;
    b = (Fx20B *)func_801CBE18_ovl_1F0A30(FIELD(o, s32, 0x50), FIELD(o, s32, 0x5C) + dx, FIELD(o, s32, 0x60) + dy,
                                          FIELD(o, s32, 0x64) + dz);
    b->b14 = 0;
    ((Fx20B **)o)[k + 3] = b;
    b->owner = o;
    a->fn = func_801B3CB8_ovl_1F0A30;
    a->owner = o;
    b->fn = func_801B5524_ovl_1F0A30;
    a->h34 = 0xFF;
    b->h34 = D_801CE8FC_ovl_1F0A30;
    a->w44 = b->w44 = FIELD(o, s32, 0x50);
    b->head = a;
    a->head = a;
}

/* t (class 33) grants u an extra action */
void func_801C96D4_ovl_1F0A30(BattleUnit *u, BattleUnit *t) {
    u32 f;

    if (t != NULL) {
        if (u != t) {
            if (t->cls == 33) {
                f = t->flags;
                if (!(f & 1)) {
                    if (!((f >> 1) & 1)) {
                        u->actsMax = func_8016E338(u->unk48, u->cls, func_801C9FA4_ovl_1F0A30(u->unk58)) + 1;
                    }
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801C974C_ovl_1F0A30);

u8 func_801C9FA4_ovl_1F0A30(s32 idx) {
    return D_801CFC8C_ovl_1F0A30[idx];
}

/* How many thirds of b fit into a, capped at 3 */
s32 func_801C9FB4_ovl_1F0A30(s32 a, s32 b) {
    s32 q = b / 3;
    s32 n = 0;

    while (a > 0) {
        a -= q;
        n++;
    }
    a = 3;
    if (n < 4) {
        a = n;
    }
    return a;
}

s32 func_801CA000_ovl_1F0A30(s32 a, s32 b) {
    s32 q;

    q = a / 3;
    if (b == 3) {
        return a;
    } else {
        return q * b;
    }
}

/* Amount of healing u can take, capped at max HP; class 1 caps at the current third of max HP */
#ifdef NON_MATCHING
/* division hoisting/branch layout differs */
s32 func_801CA038_ovl_1F0A30(BattleUnit *u, s32 amount) {
    s32 cap;

    if (func_801C8C74_ovl_1F0A30(u)) {
        s32 max = *(u16 *)((u8 *)u + 0x22);
        s32 h = *(u16 *)((u8 *)u + 0x20);
        s32 n = 0;

        while (h > 0) {
            h -= max / 3;
            n++;
        }
        n = n < 4 ? n : 3;
        cap = max / 3;
        if (n == 3) {
            cap = max;
        } else {
            cap *= n;
        }
    } else {
        cap = *(u16 *)((u8 *)u + 0x22);
    }
    if (cap < *(u16 *)((u8 *)u + 0x20) + amount) {
        amount = cap - *(u16 *)((u8 *)u + 0x20);
    }
    return amount;
}
#else
INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CA038_ovl_1F0A30);
#endif

s32 func_801CA100_ovl_1F0A30(BattleUnit *u) {
    s32 out[4];
    u8 b;
    s32 i = 0;

    if (u->unk48 == 0x101) {
        return 0x26;
    }
    while (func_801C1AA4_ovl_1F0A30(u->unk48, u->cls, func_801C8BA4_ovl_1F0A30(u), func_801C8B68_ovl_1F0A30(u), 0, i, &b, 0, 0) != 1) {
        i++;
    }
    func_801C1EE8_ovl_1F0A30(out, *(s32 *)((u8 *)u + 0x50), b);
    return -out[1];
}

/* Unit index at (lane, row), or -1 */
s32 func_801CA1C4_ovl_1F0A30(u32 lane, s32 row) {
    s32 i;
    BattleUnit *u;

    if (lane >= 3 || row < 0) {
        return -1;
    }
    if (row >= 9) {
        return -1;
    }
    for (i = 0; i < 20; i++) {
        u = BattleGetUnit(i);
        if (u != NULL && !(u->flags & 1) && u->unk54 == lane && u->unk58 == row) {
            return i;
        }
    }
    return -1;
}

s32 func_801CA268_ovl_1F0A30(BattleUnit *a, BattleUnit *b) {
    s32 r = a->unk54 > b->unk54;

    if (func_801C8B68_ovl_1F0A30(a)) {
        r = !r;
    }
    return r;
}

/* Index of a battle unit, or -1 */
s32 func_801CA29C_ovl_1F0A30(BattleUnit *u) {
    s32 i;
    u8 *base;

    if (u == NULL) {
        return -1;
    }
    base = D_801CE8BC_ovl_1F0A30;
    for (i = 0; i < 20; i++) {
        if ((BattleUnit *)(base + 0x1C4 + i * 0xF8) == u) {
            return i;
        }
    }
    return -1;
}

/* Living unit at (lane, row), or NULL */
BattleUnit *func_801CA2E0_ovl_1F0A30(u32 lane, s32 row) {
    s32 i;
    BattleUnit *u;

    if (lane >= 3 || row < 0) {
        return NULL;
    }
    if (row >= 9) {
        return NULL;
    }
    for (i = 0; i < 20; i++) {
        u = BattleGetUnit(i);
        if (u != NULL && !(u->flags & 1) && u->unk54 == lane && u->unk58 == row) {
            return u;
        }
    }
    return NULL;
}

/* The unit's squad strategy: the in-battle setting (state +0x1C0) for the player side, the squad record for the enemy */
s32 func_801CA384_ovl_1F0A30(BattleUnit *u) {
    if (func_801C8B84_ovl_1F0A30(u)) {
        return *(s32 *)(D_801CE8BC_ovl_1F0A30 + 0x1C0);
    }
    return gSquads[D_801976DC[1].b[0]].unk17[0];
}

/* Builds battle unit u from player character k */
void func_801CA3E0_ovl_1F0A30(u8 *u, s32 k) {
    PlayerChar20B *p = &D_80193BC0[k];

    bzero(u, 0xF8);
    FIELD(u, s32, 0x48) = p->c.cls;
    FIELD(u, s32, 0x4C) = p->c.baseCls;
    u[0xF6] = k;
    u[0x31] = p->c.level;
    u[0x33] = p->c.element;
    FIELD(u, u16, 0x22) = p->c.maxHp;
    FIELD(u, u16, 0x20) = p->c.hp;
    FIELD(u, u16, 0x24) = p->c.str;
    FIELD(u, u16, 0x26) = p->c.vit;
    FIELD(u, u16, 0x28) = p->c.intl;
    FIELD(u, u16, 0x2A) = p->c.men;
    FIELD(u, u16, 0x2C) = p->c.agi;
    FIELD(u, u16, 0x2E) = p->c.dex;
    u[0x30] = p->c.luck;
    u[0x34] = u[0x3F] = p->c.alignment;
    FIELD(u, u16, 0x36) = p->c.items[0];
    FIELD(u, u16, 0x38) = p->c.items[1];
    FIELD(u, u16, 0x3A) = p->c.items[2];
    FIELD(u, u16, 0x3C) = p->c.items[3];
    u[0x3E] = p->c.fatigue;
    if (IsLord20B(u)) {
        u[0x3E] = 0;
    }
    if (p->c.status & 2) {
        FIELD(u, s32, 0x40) |= 0x200;
    }
    if (p->c.status & 4) {
        FIELD(u, s32, 0x40) |= 2;
    }
    u[0x32] = p->morale;
}

s32 func_801CA534_ovl_1F0A30(u8 *p) {
    s32 i;

    for (i = 0; i < *(s32 *)(D_801CE8BC_ovl_1F0A30 + 0x52BC); i++) {
        BattleObj20 *o = ((BattleObj20 **)(p + 0xC0))[i];

        o->fn(o);
    }
    return 1;
}

extern u8 D_801CFC98_ovl_1F0A30[];
extern u8 D_801CFCA4_ovl_1F0A30[];
extern u8 D_801CFCB0_ovl_1F0A30[];

/* Tint of colour c for fade level t: three bands between 0.208 and 0.791 */
u8 func_801CA5A0_ovl_1F0A30(u8 c, f32 t) {
    if (t >= 0.208 && t < 0.375) {
        return D_801CFC98_ovl_1F0A30[(u8)c];
    }
    if (t >= 0.375 && t < 0.625) {
        return D_801CFCA4_ovl_1F0A30[(u8)c];
    }
    if (t >= 0.625 && t < 0.791) {
        return D_801CFCB0_ovl_1F0A30[(u8)c];
    }
    return c;
}

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CA680_ovl_1F0A30);

typedef struct {
    /* 0x00 */ u16 next;
    /* 0x02 */ u16 a;
    /* 0x04 */ u16 b;
    /* 0x06 */ u8 unk06[2];
    /* 0x08 */ s32 c;
    /* 0x0C */ u8 unk0C[0x78];
} Node20B; /* size 0x84 */

extern Node20B *D_801D0708_ovl_1F0A30;
extern s16 D_801D0714_ovl_1F0A30;
extern u16 D_801D0724_ovl_1F0A30;
extern u16 D_801D0818_ovl_1F0A30;
extern Node20B *D_801D081C_ovl_1F0A30;
extern s32 D_801D0834_ovl_1F0A30;

/* Allocates the node pool (16 nodes of 0x84 bytes chained into a free list, then a 0xA0-byte
 * header) and empties the lists */
void func_801CBC2C_ovl_1F0A30(void) {
    Node20B *n;
    s32 i;

    D_801D0834_ovl_1F0A30 = 16;
    n = HMalloc(0x8E0);
    D_801D0824_ovl_1F0A30 = n;
    D_801D081C_ovl_1F0A30 = n;
    D_801D0708_ovl_1F0A30 = n + D_801D0834_ovl_1F0A30;
    for (i = 0; i < D_801D0834_ovl_1F0A30; i++) {
        n[i].c = 0;
        n[i].b = 0xFFFF;
        n[i].a = 0xFFFF;
    }
    for (i = 0; i < D_801D0834_ovl_1F0A30 - 1; i++) {
        D_801D081C_ovl_1F0A30[i].next = i + 1;
    }
    D_801D081C_ovl_1F0A30[i].next = 0xFFFF;
    bzero(D_801D0708_ovl_1F0A30, 0xA0);
    D_801D0714_ovl_1F0A30 = 0;
    D_801D0818_ovl_1F0A30 = 0xFFFF;
    D_801D0724_ovl_1F0A30 = 0xFFFF;
}

void func_801CBD48_ovl_1F0A30(void) {
    HFree(D_801D0824_ovl_1F0A30);
}

/* Places object o at cell (x, y, z) (world position = cell * 30) and resets its colour */
#ifdef NON_MATCHING
/* stack arg z loaded late in the original; no statement order reproduces it */
u8 *func_801CBD6C_ovl_1F0A30(u8 *o, s32 a, s32 x, s32 y, s32 z) {
    FIELD(o, s16, 0x1C) = FIELD(o, s16, 0x28) = x;
    FIELD(o, s16, 0x1E) = FIELD(o, s16, 0x2A) = y;
    FIELD(o, s32, 0x18) = a;
    FIELD(o, s32, 0x4) = x * 30;
    FIELD(o, s32, 0x8) = y * 30;
    FIELD(o, s16, 0x20) = FIELD(o, s16, 0x2C) = z;
    FIELD(o, s32, 0xC) = z * 30;
    o[0x38] = func_801BC76C_ovl_1F0A30();
    o[0x39] = func_801BC838_ovl_1F0A30();
    o[0x3A] = func_801BC914_ovl_1F0A30();
    o[0x3B] = o[0x3C] = o[0x3D] = 0xFF;
    o[0x37] = 0;
    return o;
}
#else
INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CBD6C_ovl_1F0A30);
#endif

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif

/* Takes the first free 0xC0-byte effect record (of 80) and starts it at (x, y, z) */
u8 *func_801CBE18_ovl_1F0A30(s32 a, s32 x, s32 y, s32 z) {
    u32 i;
    u8 *p;

    for (i = 0; i < 80; i++) {
        if (FIELD(D_801CE8BC_ovl_1F0A30 + i * 0xC0, s32, 0x153C) == 0) {
            break;
        }
    }
    while (i >= 80) {
    }
    p = D_801CE8BC_ovl_1F0A30 + ((i * 0xC0) + 0x1524);
    bzero(p, 0xC0);
    FIELD(p, s16, 0x1C) = FIELD(p, s16, 0x28) = x;
    FIELD(p, s16, 0x20) = FIELD(p, s16, 0x2C) = z;
    FIELD(p, s16, 0x1E) = FIELD(p, s16, 0x2A) = y;
    FIELD(p, s32, 4) = x * 0x1E;
    FIELD(p, s32, 0xC) = z * 0x1E;
    FIELD(p, s32, 0x18) = a;
    FIELD(p, s32, 8) = y * 0x1E;
    FIELD(p, u8, 0x38) = func_801BC76C_ovl_1F0A30();
    FIELD(p, u8, 0x39) = func_801BC838_ovl_1F0A30();
    FIELD(p, u8, 0x3A) = func_801BC914_ovl_1F0A30();
    FIELD(p, u8, 0x3D) = 0xFF;
    FIELD(p, u8, 0x3C) = 0xFF;
    FIELD(p, u8, 0x3B) = 0xFF;
    FIELD(p, u8, 0x37) = 0;
    return p;
}

/* func_801C8FE8 as inlined here (base loaded after the range check) */
static inline u8 *BattleGetUnit2(u32 i) {
    u8 *base;
    s32 off;

    if (i < 20) {
        base = D_801CE8BC_ovl_1F0A30;
        off = i * 0xF8;
        if (*(s32 *)(base + off + 0x20C) != 0) {
            return base + (off + 0x1C4);
        }
    }
    return NULL;
}

typedef struct {
    s32 w[20];
} Pose20B;

static inline void bumpAnim20B(u8 *e) {
    if (e != NULL && e[0x36] < e[0x37]) {
        e[0x36]++;
    }
}

/* Per-round unit refresh: steps animations, copies poses to shadows, expires timed states */
void func_801CBF44_ovl_1F0A30(void) {
    s32 i;

    for (i = 0; i < 20; i++) {
        u8 *u = BattleGetUnit2(i);
        u8 **p;

        if (u == NULL) {
            continue;
        }
        func_801ADCBC_ovl_1F0A30(u);
        p = (u8 **)u;
        do {
            if (p[0] != NULL) {
                if (p[3] != NULL) {
                    *(Pose20B *)(p[3] + 0x44) = *(Pose20B *)(p[0] + 0x44);
                }
                bumpAnim20B(p[0]);
            }
            p++;
        } while (p < (u8 **)(u + 0xC));
        bumpAnim20B(FIELD(u, u8 *, 0x18));
        bumpAnim20B(FIELD(u, u8 *, 0x1C));
        if (FIELD(u, s32, 0xA0) != 0 && --FIELD(u, s32, 0xA0) == 0) {
            u32 k;

            for (k = 0; k < 3; k++) {
                u8 *e = ((u8 **)u)[k];

                if (e != NULL) {
                    FIELD(e, s16, 0x32) = 0;
                    FIELD(e, s16, 0x30) = 0;
                    FIELD(e, s16, 0x2E) = 0;
                }
            }
        }
        if (FIELD(u, u8 *, 0x18) != NULL && FIELD(FIELD(u, u8 *, 0x18), s16, 0x48) == 0) {
            FIELD(FIELD(u, u8 *, 0x18), s32, 0x18) = 0;
            FIELD(u, u8 *, 0x18) = NULL;
        }
        if (FIELD(u, u8 *, 0x1C) != NULL && FIELD(FIELD(u, u8 *, 0x1C), s16, 0x48) == 0) {
            FIELD(FIELD(u, u8 *, 0x1C), s32, 0x18) = 0;
            FIELD(u, u8 *, 0x1C) = NULL;
        }
    }
    FIELD(D_801CE8BC_ovl_1F0A30, s32, 0x6080)++;
}

/* Loads chunk id and unpacks it: LHa archives ("-lh") through func_8007ACB0, otherwise LZ */
void *func_801CC124_ovl_1F0A30(s32 id) {
    s32 size = ChunkSize(id);
    u8 *raw = func_80071C04(size);
    void *out;

    LoadChunkRaw(raw, id);
    if (raw[2] == '-' && raw[3] == 'l' && raw[4] == 'h') {
        Arc16_20BCE0 arc = D_801D0640_ovl_1F0A30;
        Arc16_20BCE0 req = D_801D0640_ovl_1F0A30;

        arc.buf = raw;
        arc.size = size;
        func_8007ACB0(&arc, &req, 1);
        out = req.buf;
    } else {
        out = HMalloc(ReadU32BE(raw));
        DecodeLZ(out, raw);
    }
    HFree(raw);
    return out;
}

/* Loads entry k of the index chunk id and unpacks it like func_801CC124 */
/* Loads entry k of the index chunk id and unpacks it like func_801CC124 */
void *func_801CC234_ovl_1F0A30(s32 id, s32 k) {
    s32 *index = func_80071C04(ChunkSize(id));
    s32 size;
    u8 *raw;
    void *out;

    raw = (u8 *)index;
    LoadChunkRaw(raw, id);
    {
        s32 e = index[k];

        HFree(raw);
        size = ChunkSize(e);
        raw = func_80071C04(size);
        LoadChunkRaw(raw, e);
    }
    if (raw[2] == '-' && raw[3] == 'l' && raw[4] == 'h') {
        Arc16_20BCE0 arc = D_801D0640_ovl_1F0A30;
        Arc16_20BCE0 req = D_801D0640_ovl_1F0A30;

        arc.buf = raw;
        arc.size = size;
        func_8007ACB0(&arc, &req, 1);
        out = req.buf;
    } else {
        out = HMalloc(ReadU32BE(raw));
        DecodeLZ(out, raw);
    }
    HFree(raw);
    return out;
}

/* 1 when one side has no active units left (dead, retreated or flag 1 excluded) */
s32 func_801CC37C_ovl_1F0A30(void) {
    s32 enemy = 0;
    s32 player = 0;
    s32 i;
    BattleUnit *u;

    for (i = 0; i < 20; i++) {
        u = BattleGetUnit(i);
        if (func_801C8E30_ovl_1F0A30(u)) {
            continue;
        }
        if (func_801C8C3C_ovl_1F0A30(u)) {
            continue;
        }
        if (func_801C8E9C_ovl_1F0A30(u)) {
            continue;
        }
        if (func_801C8B84_ovl_1F0A30(u)) {
            player++;
        } else {
            enemy++;
        }
    }
    return (player == 0) | (enemy == 0);
}

/* 1 when one side is gone or no active unit has +0x6C < +0x70 (likely: battle round finished) */
s32 func_801CC44C_ovl_1F0A30(void) {
    s32 i;
    BattleUnit *u;

    if (func_801CC37C_ovl_1F0A30()) {
        return 1;
    }
    for (i = 0; i < 20; i++) {
        u = BattleGetUnit(i);
        if (func_801C8E30_ovl_1F0A30(u)) {
            continue;
        }
        if (func_801C8E9C_ovl_1F0A30(u)) {
            continue;
        }
        if (func_801C8C3C_ovl_1F0A30(u)) {
            continue;
        }
        if (FIELD(u, s32, 0x6C) < FIELD(u, s32, 0x70)) {
            return 0;
        }
    }
    return 1;
}

/* Whether the player's squad carries consumable id */
s32 func_801CC51C_ovl_1F0A30(s32 id) {
    SquadRec *sq = &gSquads[D_801976DC[0].b[0]];
    s32 i;

    for (i = 0; i < 10; i++) {
        if (sq->items[i] == id) {
            return 1;
        }
    }
    return 0;
}

#ifdef NON_MATCHING
/* m2c draft, 88 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 bzero(void *, s32);                     /* extern */
s32 func_801AD9D4_ovl_1F0A30(void *, s32, s32); /* extern */

void func_801CC574_ovl_1F0A30(void *arg0, s32 arg1) {
    s32 temp_a2;
    s32 temp_a2_2;
    s32 var_s2;
    s32 var_v0;
    s32 var_v0_2;
    u32 var_v1;
    u32 var_v1_2;
    u8 *var_a0;
    u8 *var_a0_2;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;

    temp_v0 = FIELD(arg0, void *, 0x18);
    var_s2 = arg1;
    if (temp_v0 != NULL) {
        FIELD(temp_v0, s32, 0x18) = 0;
    }
    temp_v0_2 = FIELD(arg0, void *, 0x1C);
    if (temp_v0_2 != NULL) {
        FIELD(temp_v0_2, s32, 0x18) = 0;
    }
    if ((func_8016DE1C(FIELD(arg0, u8, 0x4B), FIELD(arg0, u8, 0x4F)) & 0xFF) == 2) {
        var_s2 += 0xC;
    }
    var_v1 = 0;
    var_a0 = D_801CE8BC_ovl_1F0A30;
loop_7:
    var_v0 = var_v1 < 0x50U;
    if (FIELD(var_a0, s32, 0x153C) != 0) {
        var_v1 += 1;
        var_a0 += 0xC0;
        if (var_v1 >= 0x50U) {
            var_v0 = var_v1 < 0x50U;
        } else {
            goto loop_7;
        }
    }
    do {

    } while (var_v0 == 0);
    temp_s0 = D_801CE8BC_ovl_1F0A30 + ((var_v1 * 0xC0) + 0x1524);
    bzero(temp_s0, 0xC0);
    FIELD(temp_s0, s32, 0x18) = 5;
    FIELD(temp_s0, s16, 0x28) = 0;
    FIELD(temp_s0, s16, 0x1C) = 0;
    FIELD(temp_s0, s16, 0x2C) = 0;
    FIELD(temp_s0, s16, 0x20) = 0;
    FIELD(temp_s0, s16, 0x2A) = 0;
    FIELD(temp_s0, s16, 0x1E) = 0;
    FIELD(temp_s0, s32, 4) = 0;
    FIELD(temp_s0, s32, 0xC) = 0;
    FIELD(temp_s0, s32, 8) = 0;
    FIELD(temp_s0, u8, 0x38) = func_801BC76C_ovl_1F0A30();
    FIELD(temp_s0, u8, 0x39) = func_801BC838_ovl_1F0A30();
    FIELD(temp_s0, u8, 0x3A) = func_801BC914_ovl_1F0A30();
    FIELD(temp_s0, s8, 0x3D) = 0xFF;
    FIELD(temp_s0, s8, 0x3C) = 0xFF;
    FIELD(temp_s0, s8, 0x3B) = 0xFF;
    FIELD(temp_s0, s8, 0x37) = 0;
    FIELD(temp_s0, s8, 0x14) = 0;
    FIELD(temp_s0, s16, 0x34) = 0xFF;
    FIELD(temp_s0, void *, 0x40) = arg0;
    FIELD(temp_s0, s8, 0x8C) = 0;
    FIELD(temp_s0, void *, 0x90) = temp_s0;
    FIELD(temp_s0, s32, 0x44) = (s32) FIELD(temp_s0, s32, 0x18);
    temp_v0_3 = FIELD(arg0, void *, 0);
    temp_a2 = M2C_UNALIGNED32(FIELD(temp_v0_3, s32, 0x3A));
    FIELD(temp_s0, s32, 0x36) = M2C_UNALIGNED32(FIELD(temp_v0_3, s32, 0x36));
    FIELD(temp_s0, u8, 0x3A) = temp_a2;
    FIELD(arg0, void *, 0x18) = temp_s0;
    func_801AD9D4_ovl_1F0A30(temp_s0 + 0x44, var_s2, temp_a2);
    var_v1_2 = 0;
    var_a0_2 = D_801CE8BC_ovl_1F0A30;
loop_12:
    var_v0_2 = var_v1_2 < 0x50U;
    if (FIELD(var_a0_2, s32, 0x153C) != 0) {
        var_v1_2 += 1;
        var_a0_2 += 0xC0;
        if (var_v1_2 >= 0x50U) {
            var_v0_2 = var_v1_2 < 0x50U;
        } else {
            goto loop_12;
        }
    }
    do {

    } while (var_v0_2 == 0);
    temp_s0_2 = D_801CE8BC_ovl_1F0A30 + ((var_v1_2 * 0xC0) + 0x1524);
    bzero(temp_s0_2, 0xC0);
    FIELD(temp_s0_2, s32, 0x18) = 5;
    FIELD(temp_s0_2, s16, 0x28) = 0;
    FIELD(temp_s0_2, s16, 0x1C) = 0;
    FIELD(temp_s0_2, s16, 0x2C) = 0;
    FIELD(temp_s0_2, s16, 0x20) = 0;
    FIELD(temp_s0_2, s16, 0x2A) = 0;
    FIELD(temp_s0_2, s16, 0x1E) = 0;
    FIELD(temp_s0_2, s32, 4) = 0;
    FIELD(temp_s0_2, s32, 0xC) = 0;
    FIELD(temp_s0_2, s32, 8) = 0;
    FIELD(temp_s0_2, u8, 0x38) = func_801BC76C_ovl_1F0A30();
    FIELD(temp_s0_2, u8, 0x39) = func_801BC838_ovl_1F0A30();
    FIELD(temp_s0_2, u8, 0x3A) = func_801BC914_ovl_1F0A30();
    FIELD(temp_s0_2, s8, 0x3D) = 0xFF;
    FIELD(temp_s0_2, s8, 0x3C) = 0xFF;
    FIELD(temp_s0_2, s8, 0x3B) = 0xFF;
    FIELD(temp_s0_2, s8, 0x37) = 0;
    FIELD(temp_s0_2, s8, 0x14) = 0;
    FIELD(temp_s0_2, s16, 0x34) = 0xFF;
    FIELD(temp_s0_2, void *, 0x40) = arg0;
    FIELD(temp_s0_2, s8, 0x8C) = 0;
    FIELD(temp_s0_2, void *, 0x90) = temp_s0_2;
    FIELD(temp_s0_2, s32, 0x44) = (s32) FIELD(temp_s0_2, s32, 0x18);
    temp_v0_4 = FIELD(arg0, void *, 0);
    temp_a2_2 = M2C_UNALIGNED32(FIELD(temp_v0_4, s32, 0x3A));
    FIELD(temp_s0_2, s32, 0x36) = M2C_UNALIGNED32(FIELD(temp_v0_4, s32, 0x36));
    FIELD(temp_s0_2, u8, 0x3A) = temp_a2_2;
    FIELD(arg0, void *, 0x1C) = temp_s0_2;
    func_801AD9D4_ovl_1F0A30(temp_s0_2 + 0x44, var_s2 + 1, temp_a2_2);
}
#else
INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CC574_ovl_1F0A30);
#endif

INCLUDE_ASM("asm/nonmatchings/20BCE0", func_801CC7EC_ovl_1F0A30);

INCLUDE_RODATA("asm/nonmatchings/20BCE0", D_801D0640_ovl_1F0A30);
