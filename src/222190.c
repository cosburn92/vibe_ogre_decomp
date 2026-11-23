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
u8 *func_801E14FC_ovl_213B10(s32 enemy);
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
typedef struct {
    u8 b0;
    u8 flags;
    u8 members[5];
    u8 rest[4];
} Squad222; /* 11 bytes, 10 of them at D_801969B8 */
extern u8 D_801969B9[]; /* squad records (11 bytes) start at 0x801969B8: [1] flags, [2..6] members */
extern u8 D_801969BA[];
s32 func_801C8B08(u8 *u);
s32 func_801C8B84(u8 *u);
s32 func_801C8C58(u8 *u);
u8 func_8016FF5C(u8 a, u8 b);
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

inline s32 func_801DF2AC_ovl_213B10(Blob50 *o, s32 a, s32 c) {
    Blob50 copy = *o;

    func_801AD9D4(&copy, a);
    return func_801AE4EC(FIELD(FIELD(o, u8 *, 0x4C), s32, 0x40), &copy, c);
}

s32 func_801DF334_ovl_213B10(u8 *u, u32 f) {
    s32 r = 0;
    s32 k = func_801C8B08(u);

    if (f & 0x8000) {
        return 0;
    }
    if (func_801C8B84(u) && (f & 0x400)) {
        r = 1;
    }
    if (func_801C8B68(u) && !(f & 0x400)) {
        r = 1;
    }
    if (k == 0) {
        r = 0;
    }
    if (r) {
        if (k == 0xFF) {
            if (!func_801C8C58(u)) {
                r = 0;
            }
        } else if (!func_8016FF5C(*(s32 *)(u + 0x48), k)) {
            r = 0;
        }
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/222190", func_801DF404_ovl_213B10);

typedef struct {
    u8 b[8];
} Col222;
extern u8 *D_801CE8C0;
u8 **func_801C8FE8(s32 i);
s32 func_801C8E30(u8 **u);
void func_8020B1E0(u8 mode, s16 *in, u16 *out);
u8 func_801BC76C(void);
u8 func_801BC838(void);
u8 func_801BC914(void);

/* When the pending colour change (0x822) is for side id, finishes every unit's colour tween:
 * keeps the resulting colour, restarts the fade from the scene colour and copies it to the
 * unit's two linked objects */
void func_801DF9D8_ovl_213B10(s16 id) {
    s32 i;
    u32 j;
    u8 **u;
    u8 *o;
    u16 out[4];
    s16 in[12];

    if (D_801CE8C0 == NULL || D_801CE8C0[0x822] == 0) {
        return;
    }
    if (D_801CE8C0[0x821] != id) {
        return;
    }
    for (i = 0; i < 20; i++) {
        u = func_801C8FE8(i);
        if (func_801C8E30(u) != 0) {
            continue;
        }
        for (j = 0; j < 3; j++) {
            o = u[j];
            if (o != NULL) {
                in[0] = o[0x37];
                in[1] = o[0x38];
                in[2] = o[0x39];
                in[3] = o[0x3A];
                in[5] = o[0x3B];
                in[6] = o[0x3C];
                in[7] = o[0x3D];
                func_8020B1E0(o[0x36], in, out);
                o[0x3B] = out[0];
                o[0x3C] = out[1];
                o[0x3D] = out[2];
                o[0x38] = func_801BC76C();
                o[0x39] = func_801BC838();
                o[0x3A] = func_801BC914();
                o[0x36] = 0;
                o[0x37] = 10;
            }
        }
        if (u[6] != NULL) {
            *(Col222 *)(u[6] + 0x36) = *(Col222 *)(u[0] + 0x36);
        }
        if (u[7] != NULL) {
            *(Col222 *)(u[7] + 0x36) = *(Col222 *)(u[0] + 0x36);
        }
    }
    D_801CE8C0[0x822] = 0;
}

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

void func_801D9F30_ovl_213B10(s32 a, s32 b, s32 c);
s32 func_801C8E9C(u8 *u);
s32 func_801C8E64(u8 *u);
s32 func_801C8E80(u8 *u);

/* Queues the battle messages for unit message m from line pos on: the hit or miss line with its
 * damage, then the optional status effect (extra) or poison/other lines; stores the next line */
void func_801E08A8_ovl_213B10(u8 *m, s32 pos, s32 hit, u8 extra) {
    if (func_801C8E9C(m) == 0) {
        func_801D9F60_ovl_213B10(hit ? 0xD : 0x12, pos, (s32)m, 0xFF);
        pos += func_801DF2AC_ovl_213B10((Blob50 *)(FIELD(m, u8 *, 0) + 0x44), hit ? 0x12 : 0x1A, 0);
    } else {
        func_801D9F30_ovl_213B10(0x2C, pos, (s32)m);
    }
    if (extra != 0) {
        pos = func_801DFB80_ovl_213B10(m, pos, extra);
    } else if (func_801C8E9C(m) == 0) {
        if (func_801C8E64(m) != 0) {
            func_801D9F8C_ovl_213B10(0x1D, pos, m, 0xFF, 0x20);
            pos += func_801DF2AC_ovl_213B10((Blob50 *)(FIELD(m, u8 *, 0) + 0x44), 0x20, 0);
        } else if (func_801C8E80(m) != 0) {
            func_801D9F8C_ovl_213B10(0x1D, pos, m, 0xFF, 0x22);
            pos += func_801DF2AC_ovl_213B10((Blob50 *)(FIELD(m, u8 *, 0) + 0x44), 0x22, 0);
        }
    }
    FIELD(m, s32, 0x94) = pos;
}

INCLUDE_ASM("asm/nonmatchings/222190", func_801E0ACC_ovl_213B10);

INCLUDE_ASM("asm/nonmatchings/222190", func_801E0D34_ovl_213B10);

void func_801E1014_ovl_213B10(s32 a, s32 b, s32 c, s32 d, s32 e, u8 f) {
    func_801E0D34_ovl_213B10(a, b, c, d, e, f, 1, 0, 0);
}

void func_801E104C_ovl_213B10(s32 a, s32 b, s32 c, s32 d, s32 e) {
    func_801E0D34_ovl_213B10(a, b, c, d, e, 0, 0, 0, 0);
}

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_801D9F8C_ovl_213B10(s32, s32, void *, s32, s32); /* extern */
extern s32 D_801CE8BC;

void func_801E107C_ovl_213B10(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    void *sp28;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a0_3;
    s32 var_a2;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_t0;
    s32 var_t1;
    void **var_a0;
    void **var_a0_2;
    void *temp_v1;
    void *temp_v1_4;

    var_a2 = arg2;
    var_t1 = 0;
    var_s1 = 0;
    var_t0 = 0x1C4;
    var_a0 = &sp28;
    FIELD(arg0, s32, 0x94) = var_a2;
    do {
        temp_v1 = D_801CE8BC + var_t0;
        var_s1 += 1;
        if (FIELD(temp_v1, s32, 0x40) & 0x2000) {
            *var_a0 = temp_v1;
            var_a0 += 4;
            var_t1 += 1;
        }
        var_t0 += 0xF8;
    } while (var_s1 < 0x14);
    var_s1_2 = 0;
    if (var_t1 > 0) {
        var_a0_2 = &sp28;
        do {
            temp_v1_2 = FIELD(*var_a0_2, s32, 0x94);
            if (FIELD(arg0, s32, 0x94) < temp_v1_2) {
                FIELD(arg0, s32, 0x94) = temp_v1_2;
            }
            var_s1_2 += 1;
            var_a0_2 += 4;
        } while (var_s1_2 < var_t1);
    }
    temp_v1_3 = FIELD(arg0, s32, 0x94);
    if (var_a2 < temp_v1_3) {
        var_a2 = temp_v1_3;
    }
    func_801E0D34_ovl_213B10((s32) arg0, arg1, var_a2, arg3, arg4, 0, 1, 0, 0);
    temp_s0 = FIELD(arg0, s32, 0x94);
    var_s1_3 = 0;
    var_a0_3 = 0x1C4;
loop_12:
    temp_v1_4 = D_801CE8BC + var_a0_3;
    if (FIELD(temp_v1_4, s32, 0x48) != 0) {
        var_s1_3 += 1;
        goto block_19;
    }
    if (FIELD(temp_v1_4, s32, 0x4C) != 0) {
        var_s1_3 += 1;
block_19:
        var_a0_3 += 0xF8;
        if (var_s1_3 < 0x14) {
            goto loop_12;
        }
    } else {
        FIELD(temp_v1_4, s32, 0x4C) = 1;
    }
    func_801D9F8C_ovl_213B10(0x39, temp_s0, arg0, arg5, var_s1_3);
    temp_s0_2 = temp_s0 + 0x23;
    func_801D9F60_ovl_213B10(0x3A, temp_s0_2, (s32) arg0, var_s1_3);
    FIELD(arg0, s32, 0x94) = temp_s0_2;
}
#else
INCLUDE_ASM("asm/nonmatchings/222190", func_801E107C_ovl_213B10);
#endif

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
        return func_801E14FC_ovl_213B10(side);
    }
    return NULL;
}

/* The squad (enemy side if enemy != 0, else the player's) containing the current unit, or NULL */
#ifdef NON_MATCHING
/* induction variables and the flags-byte addressing differ */
u8 *func_801E14FC_ovl_213B10(s32 enemy) {
    u8 *key = D_801976E8;
    s32 i;
    u8 *res;
    u8 *mb;
    u8 *m;

    if (enemy == 0) {
        key -= 0xC;
    }
    res = D_801969BA - 2;
    mb = D_801969BA;
    for (i = 0; i < 10; i++, res += 11, mb += 11) {
        if (D_801969B9[i * 11] & 1) {
            m = mb;
            do {
                if (*m == *key) {
                    return res;
                }
            } while (++m < mb + 5);
        }
    }
    return NULL;
}
#else
INCLUDE_ASM("asm/nonmatchings/222190", func_801E14FC_ovl_213B10);
#endif

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

#ifdef NON_MATCHING
/* m2c draft, 16 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_801ADADC(s32);                         /* extern */
s32 func_801ADB9C(s32);                         /* extern */
s32 func_801C92F8();                                /* extern */
s32 func_801C9380();                                /* extern */
s32 func_801C96D4(u8 *, s32);                   /* extern */
s32 func_801C974C(u8 *, s32, s32, s32);     /* extern */
extern s32 D_801CE8BC;

u8 *func_801E1660_ovl_213B10(u8 *arg0, s32 arg1, s32 arg2) {
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s2;
    s32 var_a3;
    s32 var_v0;
    u8 *temp_s1;

    temp_s2 = arg1 & 0xFF;
    var_a3 = temp_s2;
    temp_a2 = arg2 & 0xFF;
    temp_a1 = FIELD(arg0, s32, 0x48);
    temp_s1 = D_801CE8BC + ((temp_a2 * 0xF8) + 0x1C4);
    if (FIELD(arg0, s32, 0x4C) != temp_a1) {
        var_a3 = temp_a1;
    }
    FIELD(temp_s1, s32, 0x48) = var_a3;
    FIELD(temp_s1, s32, 0x4C) = temp_s2;
    FIELD(temp_s1, u8, 0xF6) = (u8) FIELD(arg0, u8, 0xF6);
    FIELD(temp_s1, s32, 0x6C) = (s32) FIELD(arg0, s32, 0x6C);
    FIELD(temp_s1, u8, 0x31) = (u8) FIELD(arg0, u8, 0x31);
    FIELD(temp_s1, u8, 0x33) = (u8) FIELD(arg0, u8, 0x33);
    FIELD(temp_s1, u16, 0x22) = (u16) FIELD(arg0, u16, 0x22);
    FIELD(temp_s1, u16, 0x20) = (u16) FIELD(arg0, u16, 0x20);
    FIELD(temp_s1, u16, 0x24) = (u16) FIELD(arg0, u16, 0x24);
    FIELD(temp_s1, u16, 0x26) = (u16) FIELD(arg0, u16, 0x26);
    FIELD(temp_s1, u16, 0x28) = (u16) FIELD(arg0, u16, 0x28);
    FIELD(temp_s1, u16, 0x2A) = (u16) FIELD(arg0, u16, 0x2A);
    FIELD(temp_s1, u16, 0x2C) = (u16) FIELD(arg0, u16, 0x2C);
    FIELD(temp_s1, u16, 0x2E) = (u16) FIELD(arg0, u16, 0x2E);
    FIELD(temp_s1, u8, 0x30) = (u8) FIELD(arg0, u8, 0x30);
    FIELD(temp_s1, u8, 0x34) = (u8) FIELD(arg0, u8, 0x34);
    FIELD(temp_s1, u8, 0x3F) = (u8) FIELD(arg0, u8, 0x3F);
    FIELD(temp_s1, s32, 0x40) = (s32) FIELD(arg0, s32, 0x40);
    FIELD(temp_s1, s32, 0x58) = (s32) FIELD(arg0, s32, 0x58);
    FIELD(temp_s1, s32, 0x54) = (s32) FIELD(arg0, s32, 0x54);
    func_801C974C(temp_s1, 0, temp_a2, var_a3);
    if (func_801C8B84(arg0) != 0) {
        var_v0 = func_801C9380();
    } else {
        var_v0 = func_801C92F8();
    }
    func_801C96D4(arg0, var_v0);
    sp18 = FIELD(temp_s1, s32, 0x48);
    sp20 = func_801C8B68(temp_s1);
    sp24 = func_801C8BA4(temp_s1);
    sp1C = temp_s2;
    sp28 = func_801C8FB8(temp_s1) & 0xFFFF;
    func_801C41C8(&sp18, &sp1C, &sp20, &sp24, &sp28, 1);
    func_801ADADC(FIELD(temp_s1, s32, 0));
    func_801ADB9C(FIELD(temp_s1, s32, 0xC));
    return temp_s1;
}
#else
INCLUDE_ASM("asm/nonmatchings/222190", func_801E1660_ovl_213B10);
#endif

#ifdef NON_MATCHING
/* m2c draft, 41 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 guRandom(s32);                              /* extern */
extern s32 D_801E5E20_ovl_213B10;

void func_801E1810_ovl_213B10(void *arg0) {
    s16 temp_v0_2;
    s16 temp_v1;
    s32 temp_fp;
    s32 temp_s6;
    s32 temp_v0_4;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a0_2;
    s32 var_a1;
    s32 var_s5;
    u16 temp_v0_3;
    u8 *var_v0;
    u8 *var_v1;
    u8 temp_s7;
    u8 temp_v0;
    u8 var_a0;
    void *temp_s0;
    void *temp_s1;
    void *temp_s2;
    void *var_s4;

    temp_v0 = FIELD(arg0, u8, 0xA7);
    var_v1 = D_801976E8;
    temp_s7 = FIELD(arg0, u8, 0xA6);
    if (temp_v0 == 0) {
        var_v1 = D_801976E8 - 0xC;
    }
    var_v0 = NULL;
    if (FIELD(var_v1, u8, 1) & 1) {
        var_v0 = func_801E14FC_ovl_213B10((s32) temp_v0);
    }
    var_a0 = 0xFF;
    if (var_v0 != NULL) {
        var_a0 = FIELD(var_v0, u8, 8);
    }
    var_a1 = var_a0 & 0xFF;
    if (FIELD(arg0, u8, 0xA7) == 0) {
        if (var_a1 != 6) {
            if (var_a1 < 7) {
                if (var_a1 == 5) {
                    var_a1 = 7;
                    goto block_20;
                }
                var_s5 = 0;
            } else {
                switch (var_a1) {                   /* irregular */
                case 8:
                    var_a1 = 6;
                    goto block_20;
                default:
                    var_s5 = 0;
                    break;
                case 7:
                    var_a1 = 5;
                    goto block_20;
                }
            }
        } else {
            var_a1 = 8;
            goto block_20;
        }
    } else {
block_20:
        var_s5 = 0;
    }
    temp_s6 = (var_a1 * 6) + ((FIELD(arg0, u8, 0xA8) & 1) * 3);
    if (temp_s7 != 0) {
        temp_fp = (temp_s6 == 0) | (temp_s6 == 0x18);
        var_s4 = arg0;
        do {
            var_a0_2 = 0;
            temp_s1 = FIELD(var_s4, void *, 0);
            temp_s0 = FIELD(var_s4, void *, 0xC);
            temp_s2 = ((temp_s6 + var_s5) * 8) + &D_801E5E20_ovl_213B10;
            if (temp_fp != 0) {
                var_a0_2 = guRandom(0) % 15;
            }
            temp_v0_2 = FIELD(arg0, s32, 0x5C) + FIELD(temp_s2, s32, 0) + var_a0_2;
            FIELD(temp_s0, s16, 0x28) = temp_v0_2;
            FIELD(temp_s0, s16, 0x1C) = temp_v0_2;
            FIELD(temp_s1, s16, 0x28) = temp_v0_2;
            FIELD(temp_s1, s16, 0x1C) = temp_v0_2;
            temp_v1 = FIELD(arg0, s32, 0x64) + FIELD(temp_s2, s32, 4);
            FIELD(temp_s0, s16, 0x2C) = temp_v1;
            FIELD(temp_s0, s16, 0x20) = temp_v1;
            FIELD(temp_s1, s16, 0x2C) = temp_v1;
            FIELD(temp_s1, s16, 0x20) = temp_v1;
            temp_v0_3 = FIELD(arg0, u16, 0x62);
            FIELD(temp_s0, u16, 0x2A) = temp_v0_3;
            FIELD(temp_s0, u16, 0x1E) = temp_v0_3;
            FIELD(temp_s1, u16, 0x2A) = temp_v0_3;
            FIELD(temp_s1, u16, 0x1E) = temp_v0_3;
            temp_v1_2 = FIELD(arg0, s32, 0x5C) + (FIELD(temp_s2, s32, 0) * 0x1E);
            FIELD(temp_s0, s32, 4) = temp_v1_2;
            FIELD(temp_s1, s32, 4) = temp_v1_2;
            temp_v1_3 = FIELD(arg0, s32, 0x64) + (FIELD(temp_s2, s32, 4) * 0x1E);
            FIELD(temp_s0, s32, 0xC) = temp_v1_3;
            FIELD(temp_s1, s32, 0xC) = temp_v1_3;
            temp_v0_4 = FIELD(arg0, s32, 0x60);
            var_s5 += 1;
            FIELD(temp_s0, s32, 8) = temp_v0_4;
            FIELD(temp_s1, s32, 8) = temp_v0_4;
            var_s4 += 4;
        } while (var_s5 < (s32) temp_s7);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/222190", func_801E1810_ovl_213B10);
#endif

INCLUDE_ASM("asm/nonmatchings/222190", func_801E1A48_ovl_213B10);
