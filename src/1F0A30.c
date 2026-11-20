#include "common.h"

/* 1F0A30 */

typedef struct {
    /* 0x00 */ u8 unk00[4];
    /* 0x04 */ s16 h4;
    /* 0x06 */ s16 h6;
    /* 0x08 */ s16 h8;
    /* 0x0A */ u8 unk0A[2];
    /* 0x0C */ s16 hC;
    /* 0x0E */ s16 hE;
    /* 0x10 */ s16 h10;
    /* 0x12 */ u8 marks[0x10];
    /* 0x22 */ u8 zero[0x10];
    /* 0x32 */ u8 unk32[0x14];
    /* 0x46 */ u8 b46;
    /* 0x47 */ u8 b47;
} Panel1F;

typedef struct {
    /* 0x0000 */ u8 unk0000[0x1C0];
    /* 0x01C0 */ s32 strategy;
    /* 0x01C4 */ u8 unk01C4[0x5020];
    /* 0x51E4 */ s32 listB[0x36];
    /* 0x52BC */ s32 nB;
    /* 0x52C0 */ s32 listA[0x100];
    /* 0x56C0 */ s32 nA;
} Ctx1F;

typedef struct {
    /* 0x00 */ u8 unk00[0x1C];
    /* 0x1C */ s16 x;
    /* 0x1E */ u8 unk1E[2];
    /* 0x20 */ s16 y;
} Spr1F;

typedef struct {
    /* 0x00 */ u8 unk00[8];
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 y;
    /* 0x10 */ f32 vx;
    /* 0x14 */ f32 vy;
    /* 0x18 */ f32 ax;
    /* 0x1C */ f32 ay;
} Mot1F;

typedef struct {
    /* 0x0 */ u8 unk0[4];
    /* 0x4 */ s16 flag;
} Opt1F; /* size 6 */

typedef struct {
    /* 0x0 */ void *data;
    /* 0x4 */ s32 ttl;
    /* 0x8 */ s32 id;
} Slot1F; /* chunk cache slot */

typedef struct {
    u8 unk00[0x17];
    u8 strategy;
    u8 unk18;
} SquadRec; /* size 0x19 */

extern u8 D_800EB1F0[];
extern Ctx1F *D_801CE8BC_ovl_1F0A30;
extern s32 *D_801CE8C0_ovl_1F0A30;
extern u8 D_801976DC;
extern SquadRec gSquads[];
extern Opt1F D_801CE900_ovl_1F0A30[];
extern u8 D_801939CC;
extern u8 D_801CE8A8_ovl_1F0A30[];

void SoundRequest(void *ch, s32 id);
void *memset(void *p, s32 c, s32 n);
void bzero(void *p, s32 n);
void func_801AEA90_ovl_1F0A30();
void func_801CA680_ovl_1F0A30(s32 a);
s32 func_8016FEF4(s32 flag);
void func_801AF730_ovl_1F0A30(void *a, s32 b);
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
void HFree(void *p);
u16 func_801794C8(s32 a);
void func_8017C4B4(s16 a);
void func_80179034(s32 a, s32 x, s32 y);
void *func_801AD60C_ovl_1F0A30(s32 id);
void func_801B0770_ovl_1F0A30(u8 *o, s32 a, s32 b, s32 c, s32 d, s32 e);
extern s16 D_801D071C_ovl_1F0A30;
extern s16 D_801D0820_ovl_1F0A30;
extern f32 D_801D06F0_ovl_1F0A30;
extern f32 D_801D0718_ovl_1F0A30;
extern f32 D_801D0740_ovl_1F0A30;
extern f32 D_801D0764_ovl_1F0A30;
extern f32 D_801D0768_ovl_1F0A30;
extern f32 D_801D0814_ovl_1F0A30;
extern s32 D_801D0838_ovl_1F0A30;
extern s32 D_801D0734_ovl_1F0A30;
extern s32 D_801D070C_ovl_1F0A30;
extern void *D_801CEAB0_ovl_1F0A30;
s32 func_801BE6BC_ovl_1F0A30(void *p);
s32 func_801BE6DC_ovl_1F0A30(void *p);
s32 func_801BE6FC_ovl_1F0A30(void *p);
void func_801B464C_ovl_1F0A30(s32 a, f32 x, f32 y, f32 z, s32 b);
void *LoadChunk(s32 id);
typedef struct {
    u8 b[0x38];
} PChar1F;
typedef struct {
    u8 b[0x34];
} EChar1F;
extern PChar1F D_80193BC0[];
extern EChar1F D_80195560[];
extern u8 D_801976E8;
extern char D_801CE890_ovl_1F0A30[];
s32 func_801C8B68_ovl_1F0A30(u8 *u);
s32 func_801C8BA4_ovl_1F0A30(u8 *u);
s32 func_801C8B84_ovl_1F0A30(u8 *u);
void BattleAnimStep(void *a, s32 b, s32 c, s32 d, s32 e);
s32 func_8016E1DC(u8 a, u8 b);
s32 sprintf(char *buf, const char *fmt, ...);
void func_801AF9B8_ovl_1F0A30(char *s, s32 side);
/* --- end decls --- */

void func_801AD5A0_ovl_1F0A30(void) {
    SoundRequest(D_800EB1F0, 0);
}

void func_801AD5C4_ovl_1F0A30(void) {
    SoundRequest(D_800EB1F0, 1);
}

void func_801AD5E8_ovl_1F0A30(void) {
    SoundRequest(D_800EB1F0, 2);
}

/* Returns the cached chunk id (16 slots of {data, ttl, id}), loading it into a free slot */
void *func_801AD60C_ovl_1F0A30(s32 id) {
    Slot1F *s = (Slot1F *)D_801CE8BC_ovl_1F0A30;
    u32 i;

    for (i = 0; i < 16; i++) {
        if (s[i].id == id) {
            s[i].ttl = 15;
            return s[i].data;
        }
    }
    for (i = 0; i < 16; i++) {
        if ((s = (Slot1F *)D_801CE8BC_ovl_1F0A30 + i)->id == 0) {
            s->id = id;
            s->ttl = 15;
            return (s = (Slot1F *)D_801CE8BC_ovl_1F0A30 + i)->data = LoadChunk(id);
        }
    }
    return NULL;
}

/* Ages the chunk caches; frees entries whose ttl runs out */
#ifdef NON_MATCHING
/* base+offset operand order in the slot address (cf. AD60C) */
void func_801AD6B0_ovl_1F0A30(void) {
    Slot1F *s;
    u32 i;

    for (i = 0; i < 16; i++) {
        if ((s = (Slot1F *)D_801CE8BC_ovl_1F0A30 + i)->id != 0) {
            if (--s->ttl == 0) {
                HFree(s->data);
                ((Slot1F *)D_801CE8BC_ovl_1F0A30 + i)->data = NULL;
                ((Slot1F *)D_801CE8BC_ovl_1F0A30 + i)->id = 0;
            }
        }
    }
    for (i = 0; i < 16; i++) {
        if ((s = (Slot1F *)((u8 *)D_801CE8BC_ovl_1F0A30 + 0xC0) + i)->data != NULL) {
            if (--s->id == 0) {
                HFree(s->data);
                ((Slot1F *)((u8 *)D_801CE8BC_ovl_1F0A30 + 0xC0) + i)->data = NULL;
                ((Slot1F *)((u8 *)D_801CE8BC_ovl_1F0A30 + 0xC0) + i)->ttl = 0;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AD6B0_ovl_1F0A30);
#endif

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AD794_ovl_1F0A30);

void func_801AD974_ovl_1F0A30(Panel1F *p, s16 a) {
    p->h4 = a;
    p->h6 = -1;
    p->h8 = 0;
    p->h10 = 0;
    p->hE = 0;
    p->hC = 0;
    p->b46 = 0;
    p->b47 = 0;
    memset(p->marks, 0xFF, 0x10);
    bzero(p->zero, 0x10);
}

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AD9D4_ovl_1F0A30);

s32 func_801ADACC_ovl_1F0A30(u8 *a, u8 *b) {
    return *a - *b;
}

void func_801ADADC_ovl_1F0A30(s32 v) {
    Ctx1F *c = D_801CE8BC_ovl_1F0A30;

    c->listA[c->nA++] = v;
}

/* Removes v from listA, shifting the rest down */
#ifdef NON_MATCHING
/* original indexes i*4+c each pass (no induction pointer), inner loop test at top */
void func_801ADB00_ovl_1F0A30(s32 v) {
    s32 pad;
    Ctx1F *c = D_801CE8BC_ovl_1F0A30;
    u32 i;

    for (i = 0; i < c->nA; i++) {
        if (c->listA[i] == v) {
            Ctx1F *d = c;

            while (i < d->nA - 1) {
                d->listA[i] = d->listA[i + 1];
                i++;
            }
            c->nA--;
            c->listA[c->nA] = 0;
            return;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801ADB00_ovl_1F0A30);
#endif

void func_801ADB9C_ovl_1F0A30(s32 v) {
    Ctx1F *c = D_801CE8BC_ovl_1F0A30;

    c->listB[c->nB++] = v;
}

/* Removes v from listB */
void func_801ADBC0_ovl_1F0A30(s32 v) {
    s32 i;

    for (i = 0; i < D_801CE8BC_ovl_1F0A30->nB; i++) {
        if (D_801CE8BC_ovl_1F0A30->listB[i] == v) {
            _bcopy(&D_801CE8BC_ovl_1F0A30->listB[i + 1], &D_801CE8BC_ovl_1F0A30->listB[i], (D_801CE8BC_ovl_1F0A30->nB - i - 1) * 4);
            D_801CE8BC_ovl_1F0A30->nB--;
            D_801CE8BC_ovl_1F0A30->listB[D_801CE8BC_ovl_1F0A30->nB] = 0;
            return;
        }
    }
}

void func_801ADC60_ovl_1F0A30(Spr1F *s, Mot1F *m) {
    m->vx += m->ax;
    m->vy += m->ay;
    s->x = m->x + m->vx;
    s->y = m->y + m->vy;
}

/* Steps the animations attached to battle unit u */
void func_801ADCBC_ovl_1F0A30(u8 *u) {
    u32 i = 0;
    u8 **a = (u8 **)u;

    for (; i < 3; i++, a++) {
        if (*a != NULL) {
            s32 x = func_801C8B68_ovl_1F0A30(u);
            BattleAnimStep(*a + 0x44, FIELD(u, s32, 0x48), FIELD(u, s32, 0x4C), x, func_801C8BA4_ovl_1F0A30(u));
        }
    }
    if (FIELD(u, u8 *, 0x18) != NULL) {
        BattleAnimStep(FIELD(u, u8 *, 0x18) + 0x44, FIELD(u, s32, 0x48), FIELD(u, s32, 0x4C), 0, 0);
    }
    if (FIELD(u, u8 *, 0x1C) != NULL) {
        BattleAnimStep(FIELD(u, u8 *, 0x1C) + 0x44, FIELD(u, s32, 0x48), FIELD(u, s32, 0x4C), 0, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/1F0A30", BattleAnimStep);

INCLUDE_ASM("asm/nonmatchings/1F0A30", BattleAnimEventTimes);

void func_801AE8CC_ovl_1F0A30(void) {
    s32 v;

    D_801D0838_ovl_1F0A30 = func_801BE6BC_ovl_1F0A30(D_801CEAB0_ovl_1F0A30);
    D_801D0734_ovl_1F0A30 = func_801BE6DC_ovl_1F0A30(D_801CEAB0_ovl_1F0A30);
    v = func_801BE6FC_ovl_1F0A30(D_801CEAB0_ovl_1F0A30);
    D_801D0768_ovl_1F0A30 = D_801D06F0_ovl_1F0A30 = D_801D0838_ovl_1F0A30;
    D_801D0718_ovl_1F0A30 = D_801D0740_ovl_1F0A30 = D_801D0734_ovl_1F0A30;
    D_801D070C_ovl_1F0A30 = v;
    D_801D0814_ovl_1F0A30 = D_801D0764_ovl_1F0A30 = v;
    D_801D071C_ovl_1F0A30 = 0xFF;
    D_801D0820_ovl_1F0A30 = 0;
}

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AE988_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AEA90_ovl_1F0A30);

void func_801AECA4_ovl_1F0A30(s32 a) {
    s32 *p;

    D_801CE8BC_ovl_1F0A30->strategy = gSquads[D_801976DC].strategy;
    func_801AEA90_ovl_1F0A30();
    p = D_801CE8C0_ovl_1F0A30;
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    func_801CA680_ovl_1F0A30(a);
}

inline Opt1F *func_801AED14_ovl_1F0A30(s32 i) {
    if (func_8016FEF4(D_801CE900_ovl_1F0A30[i].flag) && ((D_801939CC >> i) & 1)) {
        return &D_801CE900_ovl_1F0A30[i];
    }
    return NULL;
}

/* Number of tactic options currently available */
inline s32 func_801AED84_ovl_1F0A30(void) {
    s32 n = 0;
    u32 i;

    for (i = 0; i < 6; i++) {
        n += func_801AED14_ovl_1F0A30(i) != NULL;
    }
    return n;
}

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AEE18_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AEF3C_ovl_1F0A30);

extern u16 D_800E8700;

/* Moves the tactic cursor (o+0x22) up/down within the available options */
void func_801AF0B8_ovl_1F0A30(u8 *o) {
    s32 n = func_801AED84_ovl_1F0A30();

    if (D_800E8700 & 0x800) {
        if ((s8)o[0x22] > 0) {
            o[0x22]--;
            SoundRequest(D_800EB1F0, 2);
        }
    }
    if (D_800E8700 & 0x400) {
        if ((s8)o[0x22] + 1 < n) {
            o[0x22]++;
            SoundRequest(D_800EB1F0, 2);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AF1CC_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AF730_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AF9B8_ovl_1F0A30);

/* Shows "<name> ..." message for unit u's action a */
void func_801AFB0C_ovl_1F0A30(u8 *u, u8 *a) {
    char buf[64];
    u8 *rec;
    s32 player;

    if (func_801C8B84_ovl_1F0A30(u)) {
        s32 sq = D_801976DC;

        player = sq < 30;
    } else {
        s32 sq = D_801976E8;

        player = sq < 30;
    }
    if (player) {
        rec = D_80193BC0[u[0xF6]].b;
    } else {
        rec = D_80195560[u[0xF6]].b;
    }
    sprintf(buf, D_801CE890_ovl_1F0A30, rec, func_8016E1DC(a[0x4B], a[0x4F]));
    func_801AF9B8_ovl_1F0A30(buf, func_801C8B84_ovl_1F0A30(u));
}

void func_801AFBE8_ovl_1F0A30(s32 a) {
    func_801AF730_ovl_1F0A30(D_801CE8A8_ovl_1F0A30, a);
}

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AFC0C_ovl_1F0A30);

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_8009C7CC();                                /* extern */
s32 func_8016E338(u8, u8, s32);                     /* extern */
s32 func_801BCFF0_ovl_1F0A30();                 /* extern */
s32 func_801C22D0_ovl_1F0A30(s32);          /* extern */
s32 func_801C22E8_ovl_1F0A30(s32);          /* extern */
s32 func_801C45E0_ovl_1F0A30();                 /* extern */
s32 func_801C8E30_ovl_1F0A30(void **);              /* extern */
void **func_801C8FE8_ovl_1F0A30(s32);               /* extern */
s32 func_801C9FA4_ovl_1F0A30(s32);                  /* extern */
s32 func_801CBC2C_ovl_1F0A30();                 /* extern */
s32 func_801CBF44_ovl_1F0A30();                 /* extern */
s32 func_801CC7EC_ovl_1F0A30(void **);          /* extern */
s32 func_8020B030();                            /* extern */
s32 osSyncPrintf(s32 *);                    /* extern */
extern s32 D_801CE8C4_ovl_1F0A30;

void func_801AFE30_ovl_1F0A30(void) {
    s16 var_s0;
    s32 temp_s0;
    s32 temp_s1;
    s32 var_s0_2;
    s32 var_s6;
    u32 var_s5;
    void **temp_v0;
    void **var_s4;
    void *temp_s2;

    D_801CE8C4_ovl_1F0A30 = 0;
    var_s6 = 0;
    osSyncPrintf("\n");
    do {
        temp_v0 = func_801C8FE8_ovl_1F0A30(var_s6);
        if (func_801C8E30_ovl_1F0A30(temp_v0) == 0) {
            var_s5 = 0;
            var_s4 = temp_v0;
            do {
                temp_s2 = *var_s4;
                if (temp_s2 != NULL) {
                    var_s0 = 0;
                    if (FIELD(temp_s2, u8, 0x8C) & 2) {
                        temp_s0 = func_8009C7CC();
                        temp_s1 = func_8009C7CC();
                        var_s0 = (((temp_s0 << 0x12) & 0x0C000000) | (temp_s1 << 0xF) | func_8009C7CC()) % 5;
                    }
                    if (FIELD(temp_s2, u8, 0x8C) & 1) {
                        var_s0 += 0x32;
                    }
                    FIELD(temp_s2, s16, 0x48) = var_s0;
                    FIELD(temp_s2, s16, 0x4A) = -1;
                    FIELD(temp_s2, s16, 0x4C) = 0;
                    FIELD(temp_s2, s16, 0x54) = 0;
                    FIELD(temp_s2, s16, 0x52) = 0;
                    FIELD(temp_s2, s16, 0x50) = 0;
                    FIELD(temp_s2, s8, 0x8A) = 0;
                    FIELD(temp_s2, s8, 0x8B) = 0;
                    memset(temp_s2 + 0x56, 0xFF, 0x10);
                    bzero(temp_s2 + 0x66, 0x10);
                }
                var_s5 += 1;
                var_s4 += 4;
            } while (var_s5 < 3U);
            FIELD(temp_v0, s32, 0x6C) = 0;
            FIELD(temp_v0, s32, 0x70) = (s32) (func_8016E338(FIELD(temp_v0, u8, 0x4B), FIELD(temp_v0, u8, 0x4F), func_801C9FA4_ovl_1F0A30(FIELD(temp_v0, s32, 0x58)) & 0xFF) & 0xFF);
        }
        var_s6 += 1;
        var_s0_2 = 0;
    } while (var_s6 < 0x14);
    do {
        func_801CC7EC_ovl_1F0A30(func_801C8FE8_ovl_1F0A30(var_s0_2));
        var_s0_2 += 1;
    } while (var_s0_2 < 0x14);
    func_801BCFF0_ovl_1F0A30();
    func_801CBC2C_ovl_1F0A30();
    func_801C22D0_ovl_1F0A30(2);
    func_8020B030();
    func_801C22E8_ovl_1F0A30(1);
    func_801C45E0_ovl_1F0A30();
    func_801CBF44_ovl_1F0A30();
}
#else
INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AFE30_ovl_1F0A30);
#endif

#ifdef NON_MATCHING
/* addu operand order (1 instruction) */
void func_801B0020_ovl_1F0A30(void) {
    u32 i;

    for (i = 0; i < 16; i++) {
        HFree(*(void **)(i * 12 + (u8 *)D_801CE8BC_ovl_1F0A30));
    }
    for (i = 0; i < 10; i++) {
        HFree(FIELD(D_801CE8BC_ovl_1F0A30, void *, 0x180 + i * 4));
    }
    bzero(D_801CE8BC_ovl_1F0A30, 0xC0);
}
#else
INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B0020_ovl_1F0A30);
#endif

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B00B0_ovl_1F0A30);

/* Draws label i centred in a 270-pixel field */
void func_801B0284_ovl_1F0A30(u8 *o, s32 i) {
    u16 w = func_801794C8(FIELD(FIELD(o, u8 *, 0xD0), s32, 0x530));
    s32 x;

    x = (270 - w) / 2;
    func_8017C4B4(((s16 *)(o + 0x18))[i]);
    func_80179034(FIELD(FIELD(o, u8 *, 0xD0), s32, 0x530), FIELD(o, s32, 0x2C) + x, FIELD(o, s32, 0x30) + 1);
}

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B0300_ovl_1F0A30);

extern u8 *D_801D06F4_ovl_1F0A30;

/* Sky colour for the current map: blends its two palette rows by the camera height */
#ifdef NON_MATCHING
/* sky colour lerp: structure exact, float registers differ */
void func_801B0658_ovl_1F0A30(void *o, f32 *r, f32 *g, f32 *b) {
    f32 y = FIELD(o, s16, 0x1C) + FIELD(o, s16, 0x20) + 190;
    u8 *c = D_801D06F4_ovl_1F0A30 + (s32)D_801CEAB0_ovl_1F0A30 * 6;

    if (y < 0.0f) {
        y = 0.0f;
    } else if (y > 380.0f) {
        y = 380.0f;
    }
    y = 380.0f - y;
    *r = y * ((f32)c[3] - (f32)c[0]) / 380.0f + c[0];
    *g = y * ((f32)c[4] - (f32)c[1]) / 380.0f + c[1];
    *b = y * ((f32)c[5] - (f32)c[2]) / 380.0f + c[2];
}
#else
INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B0658_ovl_1F0A30);
#endif

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B0770_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", BattleDrawUnitSprite);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B2C08_ovl_1F0A30);

s32 func_801B3C3C_ovl_1F0A30(u8 *o) {
    u8 *p = o;
    s32 v;

    if (FIELD(o, u32, 0x94) & 4) {
        v = (s32)func_801AD60C_ovl_1F0A30(0x3224BA);
    } else {
        v = 0;
    }
    func_801B0770_ovl_1F0A30(o, p[0x14] != 3, FIELD(p, u32, 0x94) & 2, v, 0, 0);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B3CB8_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B3EE0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B40F4_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B4398_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B464C_ovl_1F0A30);

s32 func_801B5524_ovl_1F0A30(s32 a) {
    if (D_801D071C_ovl_1F0A30 != 0) {
        func_801B464C_ovl_1F0A30(a, D_801D0768_ovl_1F0A30, D_801D0718_ovl_1F0A30, D_801D0814_ovl_1F0A30, D_801D071C_ovl_1F0A30);
    }
    if (D_801D0820_ovl_1F0A30 != 0) {
        func_801B464C_ovl_1F0A30(a, D_801D06F0_ovl_1F0A30, D_801D0740_ovl_1F0A30, D_801D0764_ovl_1F0A30, D_801D0820_ovl_1F0A30);
    }
    return 0;
}

#ifdef NON_MATCHING
/* m2c draft, 32 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_80098AA0(s32, f32, f32, f32);          /* extern */
s32 guLookAt(s32, f32, f32, f32, f32, f32, f32, s32, f32, s32); /* extern */
s32 guPerspective(s32, u16 *, f32, s32, f32, f32, f32); /* extern */
extern void *D_800E9BA0;
extern s32 D_801969B0;
extern f32 D_801D06FC_ovl_1F0A30;
extern f32 D_801D0700_ovl_1F0A30;
extern f32 D_801D0704_ovl_1F0A30;
extern f32 D_801D0710_ovl_1F0A30;
extern f32 D_801D0720_ovl_1F0A30;
extern f32 D_801D072C_ovl_1F0A30;
extern f32 D_801D0730_ovl_1F0A30;
extern f32 D_801D083C_ovl_1F0A30;

void func_801B55C4_ovl_1F0A30(void) {
    u16 sp28;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    void *temp_v1;

    guPerspective(D_801969B0, &sp28, D_801D0710_ovl_1F0A30, 0x3FAAAAAB, 1.0f, 4000.0f, 1.0f);
    guLookAt(D_801969B0 + 0x40, D_801D0720_ovl_1F0A30, D_801D072C_ovl_1F0A30, D_801D0704_ovl_1F0A30, D_801D0730_ovl_1F0A30, D_801D083C_ovl_1F0A30, D_801D0700_ovl_1F0A30, 0, 1.0f, 0);
    func_80098AA0(D_801969B0 + 0x80, D_801D06FC_ovl_1F0A30, D_801D06FC_ovl_1F0A30, D_801D06FC_ovl_1F0A30);
    temp_v1 = D_800E9BA0;
    D_800E9BA0 = temp_v1 + 8;
    FIELD(temp_v1, s32, 0) = 0xDB0E0000;
    FIELD(temp_v1, s32, 4) = (s32) sp28;
    temp_a1 = D_801969B0 + 0x40;
    D_800E9BA0 = temp_v1 + 0x10;
    FIELD(temp_v1, s32, 8) = 0xDA380007;
    temp_a2 = D_801969B0 + 0x80;
    D_800E9BA0 = temp_v1 + 0x18;
    FIELD(temp_v1, s32, 0xC) = (s32) D_801969B0;
    temp_a0 = D_801969B0 + 0xC0;
    D_801969B0 = temp_a1;
    FIELD(temp_v1, s32, 0x10) = 0xDA380005;
    D_801969B0 = temp_a2;
    FIELD(temp_v1, s32, 0x14) = temp_a1;
    D_800E9BA0 = temp_v1 + 0x20;
    FIELD(temp_v1, s32, 0x18) = 0xDA380003;
    D_801969B0 = temp_a0;
    FIELD(temp_v1, s32, 0x1C) = temp_a2;
}
#else
INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B55C4_ovl_1F0A30);
#endif

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;
#include "gbi_ultra.h"
#ifndef NON_MATCHING
extern Gfx *D_800E9BA0;
#endif
extern u8 D_801CEAAC_ovl_1F0A30;
extern u8 D_801CEAAD_ovl_1F0A30;
extern u8 D_801CEAAE_ovl_1F0A30;

/* Fills the screen with colour D_801CEAAC (r, g, b) at alpha a (no-op at 0) */
void func_801B574C_ovl_1F0A30(u8 a) {
    if (a == 0) {
        return;
    }
    gDPPipeSync(D_800E9BA0++);
    gDPPipeSync(D_800E9BA0++);
    gSPSetOtherMode(D_800E9BA0++, G_SETOTHERMODE_H, 20, 2, 0);
    gDPPipeSync(D_800E9BA0++);
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xD9000000;
        _g->w1 = 0;
    }
    gDPSetPrimColor(D_800E9BA0++, 0, 0, D_801CEAAC_ovl_1F0A30, D_801CEAAD_ovl_1F0A30, D_801CEAAE_ovl_1F0A30, a);
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xFCFFFFFF;
        _g->w1 = 0xFFFDF6FB;
    }
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xE200001C;
        _g->w1 = 0x00504240;
    }
    gDPPipeSync(D_800E9BA0++);
    gSPTextureRectangle(D_800E9BA0++, 0, 0, 319 << 2, 239 << 2, 0, 0, 0, 0, 0);
    gDPPipeSync(D_800E9BA0++);
}
