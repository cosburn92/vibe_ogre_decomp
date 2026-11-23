#include "common.h"

/* AE2A0 */

typedef struct {
    u16 v[3];
} Cursor3;

typedef struct {
    /* 0x0 */ s32 n;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 x;
    /* 0xC */ s32 y;
} Bob87; /* size 0x10 */

typedef struct {
    /* 0x0000 */ u8 unk0000[0x92];
    /* 0x0092 */ u8 b92;
    /* 0x0093 */ u8 b93;
    /* 0x0094 */ u8 b94;
    /* 0x0095 */ u8 b95;
    /* 0x0096 */ u8 b96;
    /* 0x0097 */ u8 unk0097;
    /* 0x0098 */ u8 b98;
    /* 0x0099 */ u8 unk0099[0xD];
    /* 0x00A6 */ u16 sp;
    /* 0x00A8 */ Cursor3 stack[20];
    /* 0x0120 */ Cursor3 cur;
    /* 0x0126 */ u8 unk0126[6];
    /* 0x012C */ u16 h12C;
    /* 0x012E */ u8 unk012E[0xF76];
    /* 0x10A4 */ Bob87 bob[8];
    /* 0x1124 */ u8 unk1124[0x5C];
    /* 0x1180 */ u8 rows[1][0x36];
} Menu87;

extern Menu87 *D_80196AF8;
extern u16 D_800E8700;
extern u16 D_800E79BC;
extern s16 D_801EF1BC_ovl_087200[];
extern s16 D_801EF1BE_ovl_087200[]; /* = D_801EF1BC + 1 */

void func_801C54EC_ovl_087200(s32 a, u8 b, u8 c);
extern s16 D_801EE38C_ovl_087200[][2];
void func_801C6DD0_ovl_087200(); /* (x, y, i, slot): the caller passes no slot */
void func_801C79C8_ovl_087200(); /* (x, y, i, slot): func_801C7944 passes no slot */
extern s16 D_801EE38C_ovl_087200[][2];
/* --- end decls --- */

/* Pushes the cursor */
void func_801C1840_ovl_087200(void) {
    Menu87 *m = D_80196AF8;

    m->stack[m->sp].v[0] = m->cur.v[0];
    m->stack[m->sp].v[1] = m->cur.v[1];
    m->stack[m->sp].v[2] = m->cur.v[2];
    m->sp++;
}

/* Pushes the cursor and sets a new one */
void func_801C18AC_ovl_087200(u16 a, u16 b, u16 c) {
    Menu87 *m = D_80196AF8;

    m->stack[m->sp].v[0] = m->cur.v[0];
    m->stack[m->sp].v[1] = m->cur.v[1];
    m->stack[m->sp].v[2] = m->cur.v[2];
    m->cur.v[0] = a;
    m->cur.v[1] = b;
    m->cur.v[2] = c;
    m->sp++;
}

/* Pops the cursor */
void func_801C1924_ovl_087200(void) {
    Menu87 *m = D_80196AF8;

    m->sp--;
    m->cur.v[0] = m->stack[m->sp].v[0];
    m->cur.v[1] = m->stack[m->sp].v[1];
    m->cur.v[2] = m->stack[m->sp].v[2];
}

INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C1990_ovl_087200);

void nuGfxTaskAllEndWait(void);
extern u8 D_801939D8;
extern u8 D_801939D0;
extern u8 D_801936E0;
void func_80199E00(void *p);
void func_80197DB8(void);
void func_801D5308_ovl_087200(void);
void func_80221CB8(void);
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
#define M87P(off) FIELD(D_80196AF8, void *, off)

/* Organize screen teardown: waits for the GPU, frees every buffer of the screen state and the
 * state itself, then resumes the field */
void func_801C1EA8_ovl_087200(void) {
    nuGfxTaskAllEndWait();
    D_801939D8 = 0;
    *(s16 *)&D_80196AF8->cur.v[0] = -1;
    HFree(M87P(0x58));
    HFree(M87P(0x4C));
    HFree(M87P(0x48));
    HFree(M87P(0x28));
    HFree(M87P(0x24));
    HFree(M87P(0x20));
    HFree(M87P(0x60));
    HFree(M87P(0x5C));
    HFree(M87P(0x1C));
    HFree(M87P(0x18));
    HFree(M87P(0x14));
    HFree(M87P(0x10));
    HFree(M87P(0x2C));
    HFree(M87P(0xC));
    HFree(M87P(0x30));
    if (M87P(0x34) != NULL) {
        HFree(M87P(0x34));
    }
    if (M87P(0x38) != NULL) {
        HFree(M87P(0x38));
    }
    HFree(M87P(0x3C));
    if (M87P(0x40) != NULL) {
        HFree(M87P(0x40));
    }
    if (M87P(0x44) != NULL) {
        HFree(M87P(0x44));
    }
    if (M87P(0x50) != NULL) {
        HFree(M87P(0x50));
    }
    if (M87P(0x54) != NULL) {
        HFree(M87P(0x54));
    }
    HFree(M87P(0x8));
    HFree(M87P(0x4));
    HFree(M87P(0x68));
    HFree(M87P(0x6C));
    func_80199E00(M87P(0x24F0));
    func_80199E00(M87P(0x24F4));
    func_80197DB8();
    func_801D5308_ovl_087200();
    HFree(M87P(0x0));
    HFree(D_80196AF8);
    D_80196AF8 = NULL;
    D_801939D0 = 0;
    if (D_801936E0 != 0) {
        func_80221CB8();
    }
}

INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C212C_ovl_087200);

/* formation tables (shared rodata splat leaves unmigrated) */
__asm__(".section .rodata\n"
        ".global D_801EFA50_ovl_087200\nD_801EFA50_ovl_087200:\n"
        ".byte 0x64, 0x01, 0xF6, 0x0A, 0x00, 0x03, 0xF6, 0x02, 0x00, 0x04, 0x01, 0x0A, 0x01, 0x64, 0xF6, 0x04, 0x02, 0x64, 0x03, 0x0A\n"
        ".global D_801EFA64_ovl_087200\nD_801EFA64_ovl_087200:\n"
        ".byte 0, 2, 1, 4, 3, 0, 0, 0, 0, 0, 0, 0\n"
        ".section .text\n");

INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C419C_ovl_087200);

void func_801C54A0_ovl_087200(void) {
    func_801C54EC_ovl_087200(0, 0, 0);
}

void func_801C54C4_ovl_087200(u8 a, u8 b) {
    func_801C54EC_ovl_087200(0, a, b);
}

INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C54EC_ovl_087200);

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif

/* Clamps the two list cursors (0x134, 0x154) and refreshes the selections they drive: kind 2
 * picks a unit (0x18A), 3 a squad (0x18C), 4 a legion (0x18E) */
#ifdef NON_MATCHING
/* same length; base+index operand order in the table lookups and the legion-case branch polarity differ */
void func_801C5880_ovl_087200(void) {
    Menu87 *m = D_80196AF8;
    s32 i;
    u8 *c;

    for (i = 0; i < 2; i++) {
        c = (u8 *)m + 0x134 + i * 0x20;
        if (FIELD(c, u16, 2) == 0) {
            continue;
        }
        switch (FIELD(c, u16, 0)) {
            case 0:
            case 1:
                break;
            case 2:
                if (FIELD(c, u16, 6) >= FIELD(m, s32, 0x5D4)) {
                    FIELD(c, u16, 6) = FIELD(m, s32, 0x5D4) - 1;
                }
                FIELD(c, u16, 0x1A) = FIELD(c, u16, 6);
                FIELD(m, u16, 0x18A) = ((u8 *)m + 0x1A2E)[FIELD(c, u16, 6)];
                break;
            case 3:
                FIELD(c, u16, 0x1C) = FIELD(c, u16, 6);
                FIELD(m, u16, 0x18C) = ((u8 *)m + 0x1A92)[FIELD(c, u16, 6)];
                if (c[0x19] == 1) {
                    FIELD(m, u16, 0x18A) = m->rows[FIELD(m, u16, 0x18C)][FIELD(m, u16, 0x19A)];
                }
                break;
            case 4: {
                s32 l;

                FIELD(c, u16, 0x1E) = FIELD(c, u16, 6);
                l = ((u8 *)m + 0x1AB0)[FIELD(c, u16, 6)];
                FIELD(m, u16, 0x18E) = l;
                if (c[0x19] != 1) {
                    if (c[0x19] == 2) {
                        u8 s = FIELD(m, u8, (u16)l * 14 + FIELD(m, u16, 0x198) + 0x10D6);

                        if (s != 0xFF) {
                            FIELD(m, u16, 0x18C) = s;
                        } else {
                            FIELD(m, u16, 0x18C) = FIELD(m, u16, 0x198) + (u16)l * 5 + 0x80;
                        }
                    }
                } else {
                    u8 s = FIELD(m, u8, l * 14 + FIELD(m, u16, 0x198) + 0x10D6);

                    if (s != 0xFF) {
                        FIELD(m, u16, 0x18A) = m->rows[s][FIELD(m, u16, 0x19A)];
                    } else {
                        FIELD(m, u16, 0x18A) = s;
                    }
                }
                break;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C5880_ovl_087200);
#endif

/* Direction from the d-pad bits (0 up, 1 down, 2 left, 3 right), -1 if none */
s32 func_801C5A0C_ovl_087200(void) {
    u16 b = D_800E8700;
    s32 r = -1;

    if (b & 0x800) {
        r = 0;
    } else if (b & 0x400) {
        r = 1;
    } else if (b & 0x200) {
        r = 2;
    } else if (b & 0x100) {
        r = 3;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C5A5C_ovl_087200);

s32 func_801C6760_ovl_087200(void) {
    u16 b = D_800E79BC;
    s32 r = -1;

    if (b & 8) {
        r = 0;
    } else if (b & 4) {
        r = 1;
    } else if (b & 2) {
        r = 2;
    } else if (b & 1) {
        r = 3;
    }
    return r;
}

#ifdef NON_MATCHING
/* m2c draft, 129 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void func_801C67B0_ovl_087200(s32 arg0) {
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_a3;
    s32 var_a3_2;
    s32 var_v0;
    s32 var_v0_2;
    u8 temp_v1_2;
    void *temp_a0;
    void *temp_v1;
    void *var_a2;

    var_a3 = 0;
    temp_v1 = D_80196AF8 + ((arg0 * 0x36) + 0x117C);
    var_v0 = 0 < 9;
    do {
        temp_a0 = temp_v1 + var_a3;
        if (var_v0 != 0) {
            FIELD(temp_a0, s8, 0xE) = 0xF;
        } else {
            FIELD(temp_a0, s8, 0xE) = 0;
        }
        var_a3 += 1;
        var_v0 = var_a3 < 9;
    } while (var_a3 < 0xF);
    var_a3_2 = 0;
    var_a2 = temp_v1;
    do {
        temp_v1_2 = FIELD(var_a2, u8, 4);
        if ((temp_v1_2 != 0xFF) && (FIELD((D_80196AF8 + (temp_v1_2 * 2)), u8, 0x1873) == 3)) {
            FIELD(var_a2, s8, 0xE) = 0xF;
            if (var_a3_2 < 6) {
                FIELD(var_a2, u8, 0x17) = (u8) (FIELD(var_a2, u8, 0x17) | 3);
                temp_v1_3 = var_a3_2 % 3;
                if (temp_v1_3 != 1) {
                    if (temp_v1_3 < 2) {
                        var_v0_2 = var_a3_2 < 3;
                        if (temp_v1_3 != 0) {

                        } else {
                            FIELD(var_a2, u8, 0x18) = (u8) (FIELD(var_a2, u8, 0x18) | 1);
                            FIELD(var_a2, u8, 0xF) = (u8) (FIELD(var_a2, u8, 0xF) | 5);
                            goto block_18;
                        }
                    } else {
                        var_v0_2 = var_a3_2 < 3;
                        if (temp_v1_3 != 2) {

                        } else {
                            FIELD(var_a2, u8, 0x16) = (u8) (FIELD(var_a2, u8, 0x16) | 2);
                            FIELD(var_a2, u8, 0xD) = (u8) (FIELD(var_a2, u8, 0xD) | 0xA);
                            goto block_18;
                        }
                    }
                } else {
                    FIELD(var_a2, u8, 0x18) = (u8) (FIELD(var_a2, u8, 0x18) | 1);
                    FIELD(var_a2, u8, 0x16) = (u8) (FIELD(var_a2, u8, 0x16) | 2);
                    FIELD(var_a2, u8, 0xD) = (u8) (FIELD(var_a2, u8, 0xD) | 0xA);
                    FIELD(var_a2, u8, 0xF) = (u8) (FIELD(var_a2, u8, 0xF) | 5);
                    goto block_18;
                }
            } else {
block_18:
                var_v0_2 = var_a3_2 < 3;
            }
            if (var_v0_2 == 0) {
                FIELD(var_a2, u8, 0xB) = (u8) (FIELD(var_a2, u8, 0xB) & 3);
                temp_v1_4 = var_a3_2 % 3;
                if (temp_v1_4 != 1) {
                    if (temp_v1_4 < 2) {
                        if (temp_v1_4 != 0) {
                            var_a3_2 += 1;
                        } else {
                            FIELD(var_a2, u8, 0xC) = (u8) (FIELD(var_a2, u8, 0xC) & 0xB);
                            goto block_29;
                        }
                    } else if (temp_v1_4 != 2) {
                        var_a3_2 += 1;
                    } else {
                        FIELD(var_a2, u8, 0xA) = (u8) (FIELD(var_a2, u8, 0xA) & 7);
                        goto block_29;
                    }
                } else {
                    FIELD(var_a2, u8, 0xC) = (u8) (FIELD(var_a2, u8, 0xC) & 0xB);
                    FIELD(var_a2, u8, 0xA) = (u8) (FIELD(var_a2, u8, 0xA) & 7);
                    goto block_29;
                }
            } else {
                goto block_29;
            }
        } else {
block_29:
            var_a3_2 += 1;
        }
        var_a2 += 1;
    } while (var_a3_2 < 9);
}
#else
INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C67B0_ovl_087200);
#endif

void func_801C69D8_ovl_087200(void) {
    D_80196AF8->b98 = 0;
}

#ifdef NON_MATCHING
/* The target indexes base + i each pass; this strength-reduces to a pointer. */
s32 func_801C69E8_ovl_087200(u16 row) {
    s32 i = 0;
    s32 n = 0;
    Menu87 *m = D_80196AF8;

    do {
        n += m->rows[row][i] != 0xFF;
        i++;
    } while (i < 9);
    return n;
}
#else
INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C69E8_ovl_087200);
#endif

void func_801C6A40_ovl_087200(u8 a, u8 b, u8 c, u8 d, u8 e) {
    Menu87 *m = D_80196AF8;

    m->b92 = a;
    m->b93 = b;
    m->b94 = c;
    m->b95 = d;
    m->b96 = e;
}

/* Screen position of grid cell n (6 per column) */
void func_801C6A64_ovl_087200(f32 *x, f32 *y, s32 n) {
    f32 c = n / 6;
    f32 r = 5 - n % 6;

    *x = 10.0f - c * 36.0f + r * 15.0f + 0.5f;
    *y = r * 25.0f + -5.0f + c * 10.0f + 0.5f - 72.0f;
}

/* Screen position of slot i in the 4-wide formation grid (isometric) */
#ifdef NON_MATCHING
/* float constants 10.0/0.5 are shared registers in the original */
void func_801C6B28_ovl_087200(f32 *x, f32 *y, s32 i) {
    s32 r = i / 4;
    f32 fr = r;
    f32 fc = 3 - (i - r * 4);

    *x = 10.0f - fr * 36.0f + fc * 15.0f + 0.5f;
    *y = fc * 25.0f + -5.0f + fr * 10.0f + 0.5f;
}
#else
INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C6B28_ovl_087200);
#endif

/* Screen position of cell n in the 3-row grid, columns counted back from the last (st+0x2C0 entries) */
void func_801C6BCC_ovl_087200(f32 *x, f32 *y, s32 n) {
    s32 col = (*(s32 *)((u8 *)D_80196AF8 + 0x2C0) - 1) / 3 - n / 3 + 1;
    s32 row = 2 - n % 3;
    f32 c = col;
    f32 r = row;

    *x = c * 72.0f + r * 30.0f + 0.5f;
    *y = r * 50.0f - c * 20.0f + 0.5f - 72.0f;
}

/* Screen position of grid slot i (three per column, newest column first) */
void func_801C6CA4_ovl_087200(f32 *x, f32 *y, s32 i) {
    s32 c = ((*(s32 *)((u8 *)D_80196AF8 + 0x2C0)) - 1) / 3 - i / 3 + 1;
    s32 r = 2 - i % 3;
    f32 col = c;
    f32 row = r;
    s16 *o = D_801EE38C_ovl_087200[(*(u16 *)((u8 *)D_80196AF8 + 0x19A))];

    *x = col * 72.0f + row * 30.0f + 0.5f;
    *y = row * 50.0f - col * 20.0f + 0.5f - 72.0f;
    *x = *x - o[0] + 0.5f;
    *y = *y - o[1] + 0.5f;
}

/* slot order (shared rodata splat leaves unmigrated) */
__asm__(".section .rodata\n"
        ".global D_801EFAFC_ovl_087200\nD_801EFAFC_ovl_087200:\n"
        ".word 0, 3, 1, 4, 2\n"
        ".section .text\n");

typedef struct {
    s32 v[5];
} Slots87;
extern Slots87 D_801EFAFC_ovl_087200;
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif

/* As func_801C79C8 one row down (base + 3) and 72 higher */
#ifdef NON_MATCHING
/* 146/147 instructions: float scheduling as in func_801C79C8; K&R definition because the caller passes no slot */
void func_801C6DD0_ovl_087200(x, y, i, j)
    f32 *x;
    f32 *y;
    s32 i;
    s32 j;
{
    Slots87 tab = D_801EFAFC_ovl_087200;
    s32 base;
    s32 r;
    s32 k;
    s32 n;
    s32 m;
    f32 c;
    f32 rr;
    f32 fy;

    if (FIELD(D_80196AF8, s32, 0x2C0) != 0) {
        base = (FIELD(D_80196AF8, s32, 0x2C0) + 2) / 3 * 3 + 3;
    } else {
        base = 3;
    }
    r = FIELD(D_80196AF8, s32, 0x5DC) - i - 1;
    if (r < 0) {
        r = 0;
    }
    k = tab.v[j];
    if (k == 0) {
        n = base + r * 6 + 2;
        c = n / 3;
        rr = n % 3;
        fy = rr * 50.0f - c * 20.0f - 10.0f + 0.5f - 72.0f;
        *x = c * 72.0f + 36.0f + rr * 30.0f + 0.5f;
    } else {
        n = base + r * 6 - (k < 3);
        m = n + 1;
        if (!(k & 1)) {
            m = n - 1;
        }
        n = m + k;
        c = n / 3;
        rr = n % 3;
        fy = rr * 50.0f - c * 20.0f + 0.5f - 72.0f;
        *x = c * 72.0f + rr * 30.0f + 0.5f;
    }
    *y = fy;
}
#else
INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C6DD0_ovl_087200);
#endif

void func_801C701C_ovl_087200(f32 *x, f32 *y, s32 i) {
    s16 *off;

    func_801C6DD0_ovl_087200(x, y, i);
    off = D_801EE38C_ovl_087200[*(u16 *)((u8 *)D_80196AF8 + 0x19A)];
    *x -= off[0];
    *y -= off[1];
}

INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C70A0_ovl_087200);

/* Screen position of slot i in the six-row grid; negative i counts columns to the left */
#ifdef NON_MATCHING
/* six-row grid position: float register use differs */
void func_801C74D8_ovl_087200(f32 *x, f32 *y, s32 i) {
    s32 r;
    s32 c;
    f32 fc;
    f32 fr;

    if (i < 0) {
        r = i % 6;
        r = (r != 0) ? 6 - ((r < 0) ? -r : r) : 0;
    } else {
        r = i % 6;
    }
    c = (i < 0) ? ((i + 1) / 6 - 1) * 6 : i;
    fc = c / 6;
    fr = 5 - r;
    *x = 10.0f - fc * 36.0f + fr * 15.0f + 0.5f;
    *y = fr * 25.0f + -5.0f + fc * 10.0f + 0.5f;
}
#else
INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C74D8_ovl_087200);
#endif

/* Screen position of the cursor cell (index st+0x186, may be negative) in the 6-wide grid, using
 * floored division */
#ifdef NON_MATCHING
/* 97 vs 94 instructions: the original keeps the index in a2 and the column in a3 (no copy of x out of a0) and avoids re-extending the floored row */
void func_801C7624_ovl_087200(f32 *x, f32 *y) {
    s32 i = FIELD(D_80196AF8, s16, 0x186);
    s32 c;
    s16 q;
    f32 fr;
    f32 fc;

    if (i < 0) {
        c = i % 6;
        if (c != 0) {
            if (c < 0) {
                c = -c;
            }
            c = 6 - c;
        } else {
            c = 0;
        }
    } else {
        c = i % 6;
    }
    q = i;
    if (i < 0) {
        q = ((i + 1) / 6 - 1) * 6;
    }
    fr = q / 6;
    fc = 5 - c;
    *x = 10.0f - fr * 36.0f + fc * 15.0f + 0.5f;
    *y = fc * 25.0f + -5.0f + fr * 10.0f + 0.5f;
    *x += 15.0f;
    *y += 25.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C7624_ovl_087200);
#endif

#ifdef NON_MATCHING
/* float constants 10.0/0.5 are shared registers in the original */
void func_801C779C_ovl_087200(f32 *x, f32 *y, s32 i) {
    s32 r = i / 4;
    f32 fr = r;
    f32 fc = 3 - (i - r * 4);

    *x = 10.0f - fr * 36.0f + fc * 15.0f + 0.5f;
    *y = fc * 25.0f + -5.0f + fr * 10.0f + 0.5f;
}
#else
INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C779C_ovl_087200);
#endif

/* func_801C6BCC minus the layout offset for the current page (D_801EE38C[st+0x19A]) */
/* The values match. The original loads the page index (st+0x19A) right after the count, before the divisions, and keeps n/3 in a3. */
void func_801C7840_ovl_087200(f32 *x, f32 *y, s32 n) {
    s16 *ofs = D_801EE38C_ovl_087200[*(u16 *)((u8 *)D_80196AF8 + 0x19A)];
    s32 ci = (*(s32 *)((u8 *)D_80196AF8 + 0x2C0) - 1) / 3 - n / 3;
    s32 ri = 2 - n % 3;
    f32 c = ci;
    f32 r = ri;

    *x = c * 72.0f + r * 30.0f - ofs[0] + 0.5f;
    *y = r * 50.0f - c * 20.0f - ofs[1] + 0.5f;
}

void func_801C7944_ovl_087200(f32 *x, f32 *y, s32 i) {
    s16 *off;

    func_801C79C8_ovl_087200(x, y, i);
    off = D_801EE38C_ovl_087200[*(u16 *)((u8 *)D_80196AF8 + 0x19A)];
    *x -= off[0];
    *y -= off[1];
}

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif

/* Screen position of slot j (D_801EFAFC kind) of squad row i, counted from the last row, in the
 * organize grid of three columns */
#ifdef NON_MATCHING
/* 138/138 instructions, 48 words differ: float scheduling in the odd/even branch (column computed before the row there) */
void func_801C79C8_ovl_087200(f32 *x, f32 *y, s32 i, s32 j) {
    Slots87 tab = D_801EFAFC_ovl_087200;
    s32 base;
    s32 r;
    s32 k;
    s32 n;
    s32 m;
    f32 c;
    f32 rr;
    f32 fx;
    f32 fy;

    if (FIELD(D_80196AF8, s32, 0x2C0) != 0) {
        base = (FIELD(D_80196AF8, s32, 0x2C0) + 2) / 3 * 3;
    } else {
        base = 0;
    }
    r = FIELD(D_80196AF8, s32, 0x5DC) - i - 1;
    if (r < 0) {
        r = 0;
    }
    k = tab.v[j];
    if (k == 0) {
        n = base + r * 6 + 2;
        c = n / 3;
        rr = n % 3;
        fy = rr * 50.0f - c * 20.0f - 10.0f;
        fx = c * 72.0f + 36.0f + rr * 30.0f;
    } else {
        n = base + r * 6 - (k < 3);
        m = n + 1;
        if (!(k & 1)) {
            m = n - 1;
        }
        n = m + k;
        c = n / 3;
        rr = n % 3;
        fx = c * 72.0f + rr * 30.0f;
        fy = rr * 50.0f - c * 20.0f;
    }
    *x = fx + 0.5f;
    *y = fy + 0.5f;
}
#else
INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C79C8_ovl_087200);
#endif

void func_801C7BF0_ovl_087200(s32 x, s32 y, s32 i) {
    Bob87 *b = &D_80196AF8->bob[i];
    s32 k = b->n++;
    s32 v = D_801EF1BC_ovl_087200[k];

    if (v == 99) {
        b->n = 2;
        v = D_801EF1BC_ovl_087200[1];
    }
    b->x = x;
    b->y = y + v;
}

void func_801C7C4C_ovl_087200(s32 x, s32 y) {
    Menu87 *m = D_80196AF8;
    s32 v = D_801EF1BE_ovl_087200[m->h12C % 10];

    m->bob[0].x = x;
    m->bob[0].y = y + v;
}

/* Window rectangle for the current list mode (mode 3/4 drop a step depending on 0x14D) */
void func_801C7CA0_ovl_087200(s16 *x, s16 *y, s16 *w, s16 *h) {
    s32 mode = *(u16 *)((u8 *)D_80196AF8 + 0x182);
    u8 sub;

    if (mode == 3) {
        sub = *((u8 *)D_80196AF8 + 0x14D);
        if (sub == 1) {
            mode = 2;
        }
    } else if (mode == 4) {
        sub = *((u8 *)D_80196AF8 + 0x14D);
        if (sub == 2) {
            mode = 3;
        } else if (sub == 1) {
            mode = 2;
        }
    }
    switch (mode) {
        case 0:
        case 1:
        case 2:
            *x = 0x18;
            *y = 0x14;
            *w = 0x128;
            *h = 0x38;
            break;
        case 3:
            *x = 0x18;
            *y = 0x14;
            *w = 0x128;
            *h = 0x38;
            break;
        case 4:
            *x = 0x9A;
            *y = 0x14;
            *w = 0x128;
            *h = 0x42;
            break;
    }
}

void func_801C7D78_ovl_087200(s16 *a, s16 *b, s16 *c, s16 *d) {
    *a = 0x18;
    *b = 0x14;
    *c = 0x128;
    *d = 0x9A;
}

/* For each axis, an 8-pixel span at whichever of the two points is farther from the screen centre */
#define DIST_FROM(v, c) ((v) - (c) > 0 ? (v) - (c) : (c) - (v))
void func_801C7D9C_ovl_087200(s16 x0, s16 y0, s16 x1, s16 y1, s16 *ox0, s16 *oy0, s16 *ox1, s16 *oy1) {
    if (DIST_FROM(x0, 160) >= DIST_FROM(x1, 160)) {
        *ox0 = x0;
        *ox1 = x0 + 8;
    } else {
        *ox0 = x1 - 8;
        *ox1 = x1;
    }
    if (DIST_FROM(y0, 120) > DIST_FROM(y1, 120)) {
        *oy0 = y0;
        *oy1 = y0 + 8;
    } else {
        *oy0 = y1 - 8;
        *oy1 = y1;
    }
}
