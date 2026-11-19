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

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AD60C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AD6B0_ovl_1F0A30);

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

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801ADB00_ovl_1F0A30);

void func_801ADB9C_ovl_1F0A30(s32 v) {
    Ctx1F *c = D_801CE8BC_ovl_1F0A30;

    c->listB[c->nB++] = v;
}

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801ADBC0_ovl_1F0A30);

void func_801ADC60_ovl_1F0A30(Spr1F *s, Mot1F *m) {
    m->vx += m->ax;
    m->vy += m->ay;
    s->x = m->x + m->vx;
    s->y = m->y + m->vy;
}

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801ADCBC_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", BattleAnimStep);

INCLUDE_ASM("asm/nonmatchings/1F0A30", BattleAnimEventTimes);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AE8CC_ovl_1F0A30);

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

Opt1F *func_801AED14_ovl_1F0A30(s32 i) {
    if (func_8016FEF4(D_801CE900_ovl_1F0A30[i].flag) && ((D_801939CC >> i) & 1)) {
        return &D_801CE900_ovl_1F0A30[i];
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AED84_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AEE18_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AEF3C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AF0B8_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AF1CC_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AF730_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AF9B8_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AFB0C_ovl_1F0A30);

void func_801AFBE8_ovl_1F0A30(s32 a) {
    func_801AF730_ovl_1F0A30(D_801CE8A8_ovl_1F0A30, a);
}

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AFC0C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801AFE30_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B0020_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B00B0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B0284_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B0300_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B0658_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B0770_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", BattleDrawUnitSprite);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B2C08_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B3C3C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B3CB8_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B3EE0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B40F4_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B4398_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B464C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B5524_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B55C4_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/1F0A30", func_801B574C_ovl_1F0A30);
