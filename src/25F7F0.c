#include "common.h"

/* ovl_25EE90 (25F7F0) */

typedef struct {
    /* 0x00 */ u16 head[4];
    /* 0x08 */ u16 active;
    /* 0x0A */ u16 timer;
    /* 0x0C */ u16 data[9]; /* len, end values[4], start values[4] */
} Interp4; /* size 0x1E */

typedef struct {
    /* 0x00 */ u16 id;
    /* 0x02 */ u8 data[10];
} Ovl25EE90Msg;

extern s32 D_8020A2D4;
extern Ovl25EE90Msg D_80220E60_ovl_25EE90;
extern Interp4 D_80220E70_ovl_25EE90;
extern u16 D_80220E78_ovl_25EE90; /* = .active */
extern u16 D_80220E7A_ovl_25EE90; /* = .timer */

void bzero(void *p, s32 n);
void _bcopy(void *src, void *dst, s32 n);
s32 func_801BC76C(void);
s32 func_801BC838(void);
s32 func_801BC914(void);
void func_8020AC50_ovl_25EE90(void);
void func_8020B29C_ovl_25EE90(void);
void func_8020B304_ovl_25EE90(void);
void func_8020B6B4_ovl_25EE90(void);
void func_8020B6C0_ovl_25EE90(void);
void func_8020B870_ovl_25EE90(void);
void func_8020B9D0_ovl_25EE90(void);
void func_8020C1F0_ovl_25EE90(void);
void func_8020C22C_ovl_25EE90(void);
void func_8020D0E0_ovl_25EE90(void);
void func_8020D150_ovl_25EE90(void);
void func_8020D2E0_ovl_25EE90(void);
void func_8020D3B0_ovl_25EE90(void);
void func_8020D3D4_ovl_25EE90(void);
void func_8020D8A0_ovl_25EE90(void);
void func_8020D9D8_ovl_25EE90(void);
void func_8020D9FC_ovl_25EE90(void);
void func_8020E110_ovl_25EE90(void);
void func_8020E1F4_ovl_25EE90(void);
void func_8020E5E0_ovl_25EE90(void);
void func_8020E61C_ovl_25EE90(void);
void func_8020E850_ovl_25EE90(s16 a);
void func_8020EAE0_ovl_25EE90(void);
void func_8020EB58_ovl_25EE90(void);
void func_8020EB7C_ovl_25EE90(void);

void func_8020AC40_ovl_25EE90(void) {
}

void func_8020AC48_ovl_25EE90(void) {
}

INCLUDE_ASM("asm/nonmatchings/25F7F0", func_8020AC50_ovl_25EE90);

void func_8020B030_ovl_25EE90(void) {
    D_8020A2D4 = 0;
    func_8020B29C_ovl_25EE90();
    func_8020B6B4_ovl_25EE90();
    func_8020B870_ovl_25EE90();
    func_8020C1F0_ovl_25EE90();
    func_8020EAE0_ovl_25EE90();
    func_8020D0E0_ovl_25EE90();
    func_8020E110_ovl_25EE90();
    func_8020D2E0_ovl_25EE90();
    func_8020D8A0_ovl_25EE90();
    func_8020E5E0_ovl_25EE90();
}

void func_8020B098_ovl_25EE90(void) {
    func_8020D9D8_ovl_25EE90();
    func_8020D3B0_ovl_25EE90();
    func_8020E1F4_ovl_25EE90();
    func_8020D150_ovl_25EE90();
    func_8020EB58_ovl_25EE90();
    func_8020C22C_ovl_25EE90();
    func_8020B9D0_ovl_25EE90();
}

void func_8020B0E4_ovl_25EE90(s32 a) {
    func_8020E850_ovl_25EE90(a);
}

void func_8020B104_ovl_25EE90(void) {
    func_8020EB7C_ovl_25EE90();
    func_8020AC50_ovl_25EE90();
    func_8020D9FC_ovl_25EE90();
    func_8020E61C_ovl_25EE90();
    func_8020D3D4_ovl_25EE90();
    func_8020B304_ovl_25EE90();
    func_8020B6C0_ovl_25EE90();
}

/* Which group of eight an id belongs to (1..7), 0 when out of range */
s32 func_8020B150_ovl_25EE90(s32 a) {
    u16 v = a;

    if (v < 8) {
        return 1;
    }
    if (v >= 8 && v < 16) {
        return 2;
    }
    if (v >= 16 && v < 24) {
        return 3;
    }
    if (v >= 24 && v < 32) {
        return 4;
    }
    if (v >= 32 && v < 39) {
        return 5;
    }
    if (v >= 39 && v < 47) {
        return 6;
    }
    if (v >= 47 && v < 51) {
        return 7;
    }
    return 0;
}

/* dst[k] = from[k] + (to[k] - from[k]) * t / len, or to[k] once t reaches len */
void func_8020B1E0_ovl_25EE90(s16 t, s16 *src, s16 *dst) {
    s32 k;

    if (t < src[0]) {
        for (k = 0; k < 4; k++) {
            *dst++ = src[5 + k] + (src[1 + k] - src[5 + k]) * t / src[0];
        }
    } else {
        for (k = 0; k < 4; k++) {
            *dst++ = src[1 + k];
        }
    }
}

void func_8020B29C_ovl_25EE90(void) {
    bzero(&D_80220E70_ovl_25EE90, sizeof(Interp4));
    D_80220E70_ovl_25EE90.head[0] = (u8)func_801BC76C();
    D_80220E70_ovl_25EE90.head[1] = (u8)func_801BC838();
    D_80220E70_ovl_25EE90.head[2] = (u8)func_801BC914();
    D_80220E70_ovl_25EE90.head[3] = 0;
}

INCLUDE_ASM("asm/nonmatchings/25F7F0", func_8020B304_ovl_25EE90);

void func_8020B4E4_ovl_25EE90(u16 active, u16 *src) {
    s32 k;
    Interp4 *s;
    u16 *d;

    D_80220E7A_ovl_25EE90 = 0;
    D_80220E78_ovl_25EE90 = active;
    s = &D_80220E70_ovl_25EE90;
    d = s->data;
    s->data[0] = src[0];
    for (k = 0; k < 4; k++) {
        d[5 + k] = src[1 + k];
        d[1 + k] = src[5 + k];
    }
}

extern u8 D_801CEAA8;
extern u8 D_801CEAA9;
extern u8 D_801CEAAA;
extern u8 D_801CEAAB;

/* Starts an interpolation from the current values (the fourth from mode's setting) to src */
void func_8020B538_ovl_25EE90(u16 mode, u16 *src) {
    Interp4 *s = &D_80220E70_ovl_25EE90;
    u16 *d = s->data;

    s->data[5] = s->head[0];
    s->data[6] = s->head[1];
    s->data[7] = s->head[2];
    if (mode == 1) {
        d[8] = s->head[3];
    } else {
        switch (mode) {
        case 2:
            d[8] = D_801CEAA8;
            break;
        case 3:
            d[8] = D_801CEAA9;
            break;
        case 4:
            d[8] = D_801CEAAA;
            break;
        case 5:
            d[8] = D_801CEAAB;
            break;
        default:
            while (1) {
            }
        }
    }
    d[0] = src[0];
    d[1] = src[1];
    d[2] = src[2];
    d[3] = src[3];
    d[4] = src[4];
    s->timer = 0;
    s->active = mode;
}

void func_8020B660_ovl_25EE90(u16 *src) {
    s32 k;
    Interp4 *s = &D_80220E70_ovl_25EE90;
    u16 *d = s->data;

    s->data[0] = src[0];
    for (k = 0; k < 4; k++) {
        d[5 + k] = s->head[k];
        d[1 + k] = src[1 + k];
    }
    s->timer = 0;
    s->active = 1;
}

void func_8020B6B4_ovl_25EE90(void) {
    D_80220E60_ovl_25EE90.id = 0;
}

extern s8 D_801CEAAC;
extern s8 D_801CEAAD;
extern s8 D_801CEAAE;
extern s16 D_80220E62_ovl_25EE90;

/* Steps the timed light override: while it runs, holds light slot id-1 at the value and sets the
 * tint; when it expires, clears both and ends the override */
void func_8020B6C0_ovl_25EE90(void) {
    Ovl25EE90Msg *m = &D_80220E60_ovl_25EE90;

    if (m->id != 0) {
        if (--D_80220E62_ovl_25EE90 < 0) {
            D_801CEAAC = 0;
            D_801CEAAD = 0;
            D_801CEAAE = 0;
            switch (m->id) {
            case 1:
                D_801CEAA8 = 0;
                break;
            case 2:
                D_801CEAA9 = 0;
                break;
            case 3:
                D_801CEAAA = 0;
                break;
            case 4:
                D_801CEAAB = 0;
                break;
            }
            m->id = 0;
            return;
        }
        switch (m->id) {
        case 1:
            D_801CEAA8 = *(u16 *)&D_80220E60_ovl_25EE90.data[8];
            break;
        case 2:
            D_801CEAA9 = *(u16 *)&D_80220E60_ovl_25EE90.data[8];
            break;
        case 3:
            D_801CEAAA = *(u16 *)&D_80220E60_ovl_25EE90.data[8];
            break;
        case 4:
            D_801CEAAB = *(u16 *)&D_80220E60_ovl_25EE90.data[8];
            break;
        }
        D_801CEAAC = *(u16 *)&m->data[2];
        D_801CEAAD = *(u16 *)&m->data[4];
        D_801CEAAE = *(u16 *)&m->data[6];
    }
}

void func_8020B83C_ovl_25EE90(u16 id, void *data) {
    D_80220E60_ovl_25EE90.id = id;
    _bcopy(data, D_80220E60_ovl_25EE90.data, 10);
}
