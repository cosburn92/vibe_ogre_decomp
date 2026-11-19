#include "common.h"

/* 222190 */

typedef struct {
    /* 0x00 */ u8 unk00[0x1C];
    /* 0x1C */ s16 x;
    /* 0x1E */ s16 h1E;
    /* 0x20 */ s16 y;
} Pt21;

typedef struct {
    /* 0x00 */ u8 unk00[0x40];
    /* 0x40 */ s32 flags;
    /* 0x44 */ u8 unk44[0x50];
    /* 0x94 */ s32 w94;
} Msg21;

extern u8 D_801976E8[];

void func_801D90E0_ovl_213B10(void);
void func_80172394(void);
s32 func_8017223C(s32 a);
void func_801707F4(void);
f32 func_801BC35C(s16 a, s16 b);
void func_801D9FBC_ovl_213B10(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
void func_801D9F60_ovl_213B10(s32 a, s32 b, s32 c, s32 d);
void func_801E0D34_ovl_213B10(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i);
u8 *func_801E14FC_ovl_213B10(void);
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
typedef struct {
    s32 w[20];
} Blob50;
s32 func_801C8B68(u8 *u);
s32 func_801C8BA4(u8 *u);
u16 func_801C8FB8(u8 *u);
void func_801C41C8(s32 *a, s32 *b, s32 *c, s32 *d, s32 *e, s32 f);
f32 func_8007FE70(f32 *a, f32 *b);
f32 func_801BE1E0(s32 cls, s32 base);
f32 func_801BE264(s32 cls, s32 base);
void func_801AD9D4(Blob50 *b, s32 a);
s32 func_801AE4EC(s32 a, Blob50 *b, s32 c);
s32 func_801DFB80_ovl_213B10(u8 *o, s32 a, u8 b);
/* --- end decls --- */

#ifdef NON_MATCHING
/* stack argument is loaded into a GPR up front in the original */
s32 func_801DEEC0_ovl_213B10(u8 *o, s32 x1, s32 z1, s32 x2, s32 z2) {
    f32 a[3];
    f32 b[3];

    a[0] = x1;
    a[1] = 0.0f;
    a[2] = z1;
    b[0] = x2;
    b[1] = 0.0f;
    b[2] = z2;
    return func_8007FE70(a, b) / func_801BE1E0(FIELD(o, s32, 0x48), FIELD(o, s32, 0x4C));
}
#else
INCLUDE_ASM("asm/nonmatchings/222190", func_801DEEC0_ovl_213B10);
#endif

INCLUDE_ASM("asm/nonmatchings/222190", func_801DEF5C_ovl_213B10);

#ifdef NON_MATCHING
/* stack argument is loaded into a GPR up front in the original */
s32 func_801DF074_ovl_213B10(u8 *o, s32 x1, s32 z1, s32 x2, s32 z2) {
    f32 a[3];
    f32 b[3];

    b[0] = x1;
    a[0] = x2;
    a[1] = 0.0f;
    b[1] = 0.0f;
    b[2] = z1;
    a[2] = z2;
    return func_8007FE70(a, b) / func_801BE264(FIELD(o, s32, 0x48), FIELD(o, s32, 0x4C));
}
#else
INCLUDE_ASM("asm/nonmatchings/222190", func_801DF074_ovl_213B10);
#endif

INCLUDE_ASM("asm/nonmatchings/222190", func_801DF110_ovl_213B10);

s32 func_801DF224_ovl_213B10(void) {
    s32 r;

    func_801D90E0_ovl_213B10();
    func_80172394();
    r = func_8017223C(0x10);
    func_801707F4();
    return r;
}

void func_801DF260_ovl_213B10(Pt21 *a, Pt21 *b) {
    s16 v = func_801BC35C(a->x, a->y);

    b->h1E = v;
    a->h1E = v;
}

s32 func_801DF2AC_ovl_213B10(Blob50 *o, s32 a, s32 c) {
    Blob50 copy = *o;

    func_801AD9D4(&copy, a);
    return func_801AE4EC(FIELD(FIELD(o, u8 *, 0x4C), s32, 0x40), &copy, c);
}

INCLUDE_ASM("asm/nonmatchings/222190", func_801DF334_ovl_213B10);

INCLUDE_ASM("asm/nonmatchings/222190", func_801DF404_ovl_213B10);

INCLUDE_ASM("asm/nonmatchings/222190", func_801DF9D8_ovl_213B10);

INCLUDE_ASM("asm/nonmatchings/222190", func_801DFB80_ovl_213B10);

INCLUDE_ASM("asm/nonmatchings/222190", func_801E0244_ovl_213B10);

void func_801E05A4_ovl_213B10(u8 *o, s32 a, s32 b, s32 c, u8 d) {
    s32 e;

    func_801D9FBC_ovl_213B10(0x18, b, (s32)o, 0xFF, c >> 8, c & 0xFF);
    e = b + a;
    func_801D9F60_ovl_213B10(0x19, e, (s32)o, 0xFF);
    FIELD(o, s32, 0x94) = func_801DFB80_ovl_213B10(o, e, d);
}

void func_801E063C_ovl_213B10(Msg21 *m, s32 a, s32 b, s32 c) {
    func_801D9FBC_ovl_213B10(0x1A, b, (s32)m, 0xFF, b + 100, c);
    m->w94 = b + a;
    m->flags |= 8;
}

void func_801E06A8_ovl_213B10(Msg21 *m, s32 a, s32 b) {
    func_801D9F60_ovl_213B10(0x25, b, (s32)m, 0xFF);
    m->w94 = b + a;
    m->flags |= 4;
}

void func_801E0708_ovl_213B10(Msg21 *m, s32 a, s32 b) {
    func_801D9F60_ovl_213B10(0x27, b, (s32)m, 0xFF);
    m->w94 = b + a;
    m->flags |= 0x10;
}

INCLUDE_ASM("asm/nonmatchings/222190", func_801E0768_ovl_213B10);

INCLUDE_ASM("asm/nonmatchings/222190", func_801E08A8_ovl_213B10);

INCLUDE_ASM("asm/nonmatchings/222190", func_801E0ACC_ovl_213B10);

INCLUDE_ASM("asm/nonmatchings/222190", func_801E0D34_ovl_213B10);

void func_801E1014_ovl_213B10(s32 a, s32 b, s32 c, s32 d, s32 e, u8 f) {
    func_801E0D34_ovl_213B10(a, b, c, d, e, f, 1, 0, 0);
}

void func_801E104C_ovl_213B10(s32 a, s32 b, s32 c, s32 d, s32 e) {
    func_801E0D34_ovl_213B10(a, b, c, d, e, 0, 0, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/222190", func_801E107C_ovl_213B10);

INCLUDE_ASM("asm/nonmatchings/222190", func_801E11D8_ovl_213B10);

void func_801E145C_ovl_213B10(Msg21 *m, s32 a, s32 b, s32 d, s32 e) {
    func_801D9FBC_ovl_213B10(0x36, b, (s32)m, d, e >> 8, e & 0xFF);
    m->w94 = b + a;
}

inline u8 *func_801E14C0_ovl_213B10(s32 side) {
    u8 *p = D_801976E8;

    if (!side) {
        p -= 12;
    }
    if (p[1] & 1) {
        return func_801E14FC_ovl_213B10();
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/222190", func_801E14FC_ovl_213B10);

u8 func_801E1590_ovl_213B10(s32 side) {
    u8 *r = func_801E14C0_ovl_213B10(side);

    if (r != NULL) {
        return r[8];
    }
    return 0xFF;
}

void func_801E15E0_ovl_213B10(u8 *u, s32 cls) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;

    a = FIELD(u, s32, 0x48);
    c = func_801C8B68(u);
    d = func_801C8BA4(u);
    b = cls;
    e = func_801C8FB8(u);
    func_801C41C8(&a, &b, &c, &d, &e, 1);
}

INCLUDE_ASM("asm/nonmatchings/222190", func_801E1660_ovl_213B10);

INCLUDE_ASM("asm/nonmatchings/222190", func_801E1810_ovl_213B10);

INCLUDE_ASM("asm/nonmatchings/222190", func_801E1A48_ovl_213B10);
