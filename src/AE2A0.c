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
void func_801C6DD0_ovl_087200(f32 *x, f32 *y, s32 i);
void func_801C79C8_ovl_087200(f32 *x, f32 *y, s32 i);
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

INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C1EA8_ovl_087200);

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

INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C5880_ovl_087200);

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

INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C67B0_ovl_087200);

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

INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C6CA4_ovl_087200);

/* slot order (shared rodata splat leaves unmigrated) */
__asm__(".section .rodata\n"
        ".global D_801EFAFC_ovl_087200\nD_801EFAFC_ovl_087200:\n"
        ".word 0, 3, 1, 4, 2\n"
        ".section .text\n");

INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C6DD0_ovl_087200);

void func_801C701C_ovl_087200(f32 *x, f32 *y, s32 i) {
    s16 *off;

    func_801C6DD0_ovl_087200(x, y, i);
    off = D_801EE38C_ovl_087200[*(u16 *)((u8 *)D_80196AF8 + 0x19A)];
    *x -= off[0];
    *y -= off[1];
}

INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C70A0_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C74D8_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C7624_ovl_087200);

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
#ifdef NON_MATCHING
/* The values match. The original loads the page index (st+0x19A) right after the count, before the divisions, and keeps n/3 in a3. */
void func_801C7840_ovl_087200(f32 *x, f32 *y, s32 n) {
    f32 c = (*(s32 *)((u8 *)D_80196AF8 + 0x2C0) - 1) / 3 - n / 3;
    f32 r = 2 - n % 3;
    s16 *ofs = D_801EE38C_ovl_087200[*(u16 *)((u8 *)D_80196AF8 + 0x19A)];

    *x = c * 72.0f + r * 30.0f - ofs[0] + 0.5f;
    *y = r * 50.0f - c * 20.0f - ofs[1] + 0.5f;
}
#else
INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C7840_ovl_087200);
#endif

void func_801C7944_ovl_087200(f32 *x, f32 *y, s32 i) {
    s16 *off;

    func_801C79C8_ovl_087200(x, y, i);
    off = D_801EE38C_ovl_087200[*(u16 *)((u8 *)D_80196AF8 + 0x19A)];
    *x -= off[0];
    *y -= off[1];
}

INCLUDE_ASM("asm/nonmatchings/AE2A0", func_801C79C8_ovl_087200);

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
