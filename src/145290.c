#include "common.h"
#include "libultra.h"

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))

typedef struct {
    /* 0x00 */ u32 flags;
    /* 0x04 */ u8 unk04[0x6C];
    /* 0x70 */ s32 unk70;
} MapUnit;

typedef struct { u16 v[3]; } U16x3;

extern s32 D_801FDA10_ovl_145210;
extern s32 *D_801FDA14_ovl_145210;
extern s32 D_801FDA18_ovl_145210;
extern s32 D_801FDA1C_ovl_145210;
extern s32 D_801FDA20_ovl_145210;
extern u8 D_801FDA24_ovl_145210;
extern u8 D_801FDA30_ovl_145210;
extern u8 *D_801FDA3C_ovl_145210;
extern u16 D_801FDA60_ovl_145210;
extern U16x3 D_801FD958_ovl_145210;
extern s32 D_801F367C;
extern MapUnit *D_801F0CB0[];
void bzero(void *p, s32 size);
void *HMalloc(s32 size);
void HFree(void *p);
void func_801F4358_ovl_145210(s32 kind, void *msg);





typedef struct {
    s32 a;
    u8 b;
    u8 c;
    u8 pad[2];
} Msg8;
typedef struct {
    /* 0x00 */ s32 id;
    /* 0x04 */ u16 flags;
    /* 0x06 */ u8 unk06[5];
    /* 0x0B */ u8 bB;
} MapEntry;
typedef struct MapObj {
    void (*fn)(struct MapObj *self);
} MapObj;
extern u16 D_801FDA32_ovl_145210;
extern MapEntry **D_801FDA34_ovl_145210;
extern Gfx *D_800E9BA0;
extern Gfx D_801FCF70_ovl_145210[];
extern Gfx D_801FCF98_ovl_145210[];
typedef struct {
    /* 0x00 */ MapUnit *u;
    /* 0x04 */ u16 flags;
    /* 0x06 */ u8 b6;
    /* 0x07 */ u8 b7;
    /* 0x08 */ u8 unk08[0x2A];
    /* 0x32 */ u8 b32;
    /* 0x33 */ u8 b33;
} MapMarker;
u8 func_801F4ED8_ovl_145210(MapUnit *u);

void func_801F95F8_ovl_145210(s32 a, u8 *o);
void func_801F6DC8_ovl_145210(void);
extern u8 D_801FCFC0_ovl_145210[][2];
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/145290", func_801F40B0_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F4208_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F4358_ovl_145210);

void func_801F4578_ovl_145210(s32 a, u8 b) {
    Msg8 m;
    Msg8 *p = &m;

    bzero(p, 8);
    m.a = a;
    m.b = b;
    func_801F4358_ovl_145210(2, p);
}

void func_801F45D0_ovl_145210(s32 a, u8 b, u8 c) {
    Msg8 m;
    Msg8 *p = &m;

    bzero(p, 8);
    m.a = a;
    m.b = b;
    m.c = c;
    func_801F4358_ovl_145210(3, p);
}

INCLUDE_ASM("asm/nonmatchings/145290", func_801F4638_ovl_145210);

void func_801F4734_ovl_145210(s16 a) {
    s16 msg[4];
    s16 *p = msg;

    bzero(p, 8);
    p[0] = a;
    func_801F4358_ovl_145210(4, p);
}

void func_801F477C_ovl_145210(s16 a) {
    s16 msg[4];
    s16 *p = msg;

    bzero(p, 8);
    p[0] = a;
    func_801F4358_ovl_145210(5, p);
}

void func_801F47C4_ovl_145210(u8 a) {
    u8 msg[8];
    u8 *p = msg;

    bzero(p, 8);
    p[0] = a;
    func_801F4358_ovl_145210(6, p);
}

INCLUDE_ASM("asm/nonmatchings/145290", func_801F480C_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F4960_ovl_145210);

void func_801F4A34_ovl_145210(u8 *src, u8 *dst, s32 n) {
    n -= n / 2;
    while (n > 0) {
        *dst++ = *src++;
        n--;
    }
}

/* Expands n palette indices (from the middle of src) into RGBA16 using the image's palette */
void func_801F4A6C_ovl_145210(u8 *src, u8 *img, u16 alt, u16 *dst, s32 n) {
    u16 *pal;

    if (img[0] < 2) {
        pal = (u16 *)(img + 8);
    } else if (alt == 0) {
        pal = (u16 *)(img + 8);
    } else {
        pal = (u16 *)(img + 0x208);
    }
    src += n / 2;
    for (; n > 0; n--) {
        *dst++ = pal[*src++];
    }
}

void func_801F4AD0_ovl_145210(void) {
    D_801FDA10_ovl_145210 = 105;
    D_801FDA14_ovl_145210 = HMalloc(0x1A4);
    bzero(D_801FDA14_ovl_145210, 0x1A4);
    D_801FDA18_ovl_145210 = 0;
}

void func_801F4B14_ovl_145210(void) {
    HFree(D_801FDA14_ovl_145210);
}

void func_801F4B38_ovl_145210(void) {
    D_801FDA18_ovl_145210 = 0;
    D_801FDA1C_ovl_145210 = 0;
    D_801FDA20_ovl_145210 = 0;
    D_801FDA24_ovl_145210 = 0;
}

void func_801F4B5C_ovl_145210(void) {
    s32 i;
    MapObj *o;

    for (i = D_801FDA18_ovl_145210 - 1; i >= 0; i--) {
        o = ((MapObj **)D_801FDA14_ovl_145210)[i];
        if (o != NULL) {
            o->fn(o);
        }
    }
}

void func_801F4BBC_ovl_145210(s32 v) {
    D_801FDA14_ovl_145210[D_801FDA18_ovl_145210++] = v;
}

void func_801F4BE8_ovl_145210(s32 *p, s32 v) {
    p[0] = v;
}

void func_801F4BF0_ovl_145210(s32 *p, s32 v) {
    p[1] = v;
}

void func_801F4BF8_ovl_145210(s32 v) {
    D_801FDA1C_ovl_145210 = v;
}

s32 func_801F4C04_ovl_145210(s32 v) {
    return D_801FDA1C_ovl_145210 == v;
}

void func_801F4C18_ovl_145210(s32 v) {
    D_801FDA20_ovl_145210 = v;
}

s32 func_801F4C24_ovl_145210(s32 v) {
    return D_801FDA20_ovl_145210 == v;
}

/* Switches the map's display mode, emitting the matching display list once */
void func_801F4C38_ovl_145210(s32 on) {
    Gfx *g;

    if (on != 0) {
        if (D_801FDA24_ovl_145210 != 1) {
            D_801FDA24_ovl_145210 = 1;
            g = D_800E9BA0++;
            g->w0 = 0xDE000000;
            g->w1 = (u32)D_801FCF70_ovl_145210;
        }
    } else if (D_801FDA24_ovl_145210 != 2) {
        D_801FDA24_ovl_145210 = 2;
        g = D_800E9BA0++;
        g->w0 = 0xDE000000;
        g->w1 = (u32)D_801FCF98_ovl_145210;
    }
}

INCLUDE_ASM("asm/nonmatchings/145290", func_801F4CD0_ovl_145210);

s32 func_801F4EB4_ovl_145210(MapUnit *u) {
    return u->unk70 == 1 && !(u->flags & 0x40);
}

INCLUDE_ASM("asm/nonmatchings/145290", func_801F4ED8_ovl_145210);

/* Slot of a unit; hangs if it is not on the map. */
s32 func_801F4FF4_ovl_145210(MapUnit *u) {
    s32 n = D_801F367C;
    s32 i;

    for (i = 0; i < n; i++) {
        if (D_801F0CB0[i] == u) {
            return i;
        }
    }
    for (;;) {
    }
}

void func_801F503C_ovl_145210(u8 *a, u8 *b, u8 *t) {
    s32 size;

    if (t[0xC] != t[0x12]) {
        for (;;) {
        }
    }
    switch (t[0xC]) {
        case 0:
            size = 0x400;
            break;
        case 1:
            size = 0x780;
            break;
        default:
            for (;;) {
            }
    }
    func_801F4A6C_ovl_145210(a, b, t[0xB], FIELD(t, u16 *, 0), size);
    func_801F4A34_ovl_145210(a, FIELD(t, u8 *, 4), size);
    FIELD(t, u16, 0xE) = FIELD(t, u16, 8);
    t[0x10] = t[0xA];
    t[0x11] = t[0xB];
    t[0x12] = t[0xC];
}

INCLUDE_ASM("asm/nonmatchings/145290", func_801F50F0_ovl_145210);

void func_801F5504_ovl_145210(u32 i) {
    U16x3 t = D_801FD958_ovl_145210;

    if (i >= 3) {
        i = 0;
    }
    D_801FDA60_ovl_145210 = t.v[i];
}

INCLUDE_ASM("asm/nonmatchings/145290", func_801F5550_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F57D0_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F5AD0_ovl_145210);

/* Advances the 12-frame cycle and picks the frame pair from the key table */
void func_801F5C74_ovl_145210(u8 *o) {
    s32 lo;
    s32 hi;
    s32 mid;

    if (++o[5] >= 12) {
        o[5] = 0;
    }
    lo = 0;
    hi = 2;
    while (lo < hi) {
        mid = (lo + hi) / 2;
        if (o[5] < D_801FCFC0_ovl_145210[mid + 1][0]) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    FIELD(o, s32, 0x10) = FIELD(o, s32 *, 0)[D_801FCFC0_ovl_145210[lo][1]];
    FIELD(o, s32, 0x14) = FIELD(o, s32 *, 0)[D_801FCFC0_ovl_145210[lo][1] + 3];
}

INCLUDE_ASM("asm/nonmatchings/145290", func_801F5D28_ovl_145210);

INCLUDE_RODATA("asm/nonmatchings/145290", D_801FD958_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F5E94_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F632C_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F6540_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F67F0_ovl_145210);

inline MapEntry *func_801F69A0_ovl_145210(s32 id) {
    s32 pad;
    s32 i;
    MapEntry *r = NULL;

    for (i = 0; i < D_801FDA32_ovl_145210; i++) {
        if (D_801FDA34_ovl_145210[i] != NULL && D_801FDA34_ovl_145210[i]->id == id) {
            r = D_801FDA34_ovl_145210[i];
            break;
        }
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/145290", func_801F69FC_ovl_145210);

u8 func_801F6B64_ovl_145210(s32 id) {
    MapEntry *e = func_801F69A0_ovl_145210(id);

    if (e != NULL) {
        return e->bB;
    }
    return 0;
}

s32 func_801F6BC0_ovl_145210(s32 id) {
    s32 pad;
    s32 i;

    for (i = 0; i < D_801FDA32_ovl_145210; i++) {
        if (D_801FDA34_ovl_145210[i] != NULL && D_801FDA34_ovl_145210[i]->id == id) {
            break;
        }
    }
    if (i >= D_801FDA32_ovl_145210) {
        for (;;) {
        }
    }
    return (D_801FDA34_ovl_145210[i]->flags >> 6) & 1;
}

void func_801F6C48_ovl_145210(s32 id) {
    MapEntry *e = func_801F69A0_ovl_145210(id);

    if (e != NULL) {
        e->flags |= 0x400;
    }
}

void func_801F6CB4_ovl_145210(s32 id) {
    s32 pad;
    s32 i;

    for (i = 0; i < D_801FDA32_ovl_145210; i++) {
        if (D_801FDA34_ovl_145210[i] != NULL && D_801FDA34_ovl_145210[i]->id == id) {
            break;
        }
    }
    if (i >= D_801FDA32_ovl_145210) {
        for (;;) {
        }
    }
    D_801FDA34_ovl_145210[i]->flags |= 0x800;
}

s32 func_801F6D3C_ovl_145210(s32 id) {
    s32 pad;
    s32 i;

    for (i = 0; i < D_801FDA32_ovl_145210; i++) {
        if (D_801FDA34_ovl_145210[i] != NULL && D_801FDA34_ovl_145210[i]->id == id) {
            break;
        }
    }
    if (i >= D_801FDA32_ovl_145210) {
        for (;;) {
        }
    }
    return (*(u32 *)&D_801FDA34_ovl_145210[i]->flags & 0xC000000) != 0;
}

void func_801F6DC8_ovl_145210(void) {
    D_801FDA30_ovl_145210 = 1;
}

void func_801F6DD8_ovl_145210(s32 unused, s32 i) {
    D_801F0CB0[i]->flags |= 0x4000000;
    D_801FDA3C_ovl_145210[i * 4] |= 2;
}

INCLUDE_ASM("asm/nonmatchings/145290", func_801F6E14_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F7684_ovl_145210);

INCLUDE_RODATA("asm/nonmatchings/145290", D_801FD9A0_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F7C40_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F83F4_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F8510_ovl_145210);

void func_801F85F0_ovl_145210(void) {
}

void func_801F85F8_ovl_145210(u8 *o) {
    switch (o[7]) {
        case 0:
            FIELD(o, u16, 4) = (FIELD(o, u16, 4) & 0xFFEB) | 0x4008;
            func_801F95F8_ovl_145210(1, o);
            o[7] = 1;
            break;
        case 1:
            if (!(FIELD(o, u16, 4) & 4)) {
                break;
            }
            *FIELD(o, u32 *, 0) &= ~1;
            o[7] = 2;
            /* fallthrough */
        case 2:
            o[0x31] &= 0xFE;
            break;
    }
}

void func_801F86A8_ovl_145210(u8 *o) {
    switch (o[7]) {
        case 0:
            FIELD(o, u16, 4) = (FIELD(o, u16, 4) & 0xFFDF) | 0x6000;
            func_801F95F8_ovl_145210(3, o);
            func_801F6DC8_ovl_145210();
            o[7] = 1;
            break;
        case 1:
            if (FIELD(o, u16, 4) & 0x20) {
                o[7] = 2;
            }
            break;
        case 2:
            *FIELD(o, u32 *, 0) &= ~0x80000;
            func_801F6DC8_ovl_145210();
            o[0xB] = 0xFF;
            o[6] = 0;
            FIELD(o, u16, 4) &= 0x9FFF;
            break;
    }
}

void func_801F8774_ovl_145210(u8 *o) {
    switch (o[7]) {
        case 0:
            FIELD(o, u16, 4) = (FIELD(o, u16, 4) & 0xFFBF) | 0x6000;
            func_801F95F8_ovl_145210(4, o);
            o[7] = 1;
            break;
        case 1:
            if (!(FIELD(o, u16, 4) & 0x40)) {
                break;
            }
            o[7] = 2;
            /* fallthrough */
        case 2:
            o[0x31] &= 0xFE;
            if (*FIELD(o, u32 *, 0) & 0x80000) {
                o[6] = 3;
                o[7] = 0;
            }
            break;
    }
}

void func_801F8830_ovl_145210(MapMarker *m) {
    s32 r;

    if (m->b7 == 0) {
        r = 0;
        if (m->u->unk70 == 1) {
            u32 t = m->u->flags & 0x40;

            r = t == 0;
        }
        m->b33 = r;
        m->b32 = func_801F4ED8_ovl_145210(m->u);
        m->b6 = 0;
        m->flags &= 0xFBFF;
    }
}
