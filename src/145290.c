#include "common.h"
#include "heap.h"
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
s32 func_801F4ED8_ovl_145210(MapUnit *u);

void func_801F95F8_ovl_145210(s32 a, u8 *o);
void func_801F6DC8_ovl_145210(void);
extern u8 D_801FCFC0_ovl_145210[][2];
typedef struct {
    u8 next;
    u8 used;
    u8 unk02[0x12];
} Slot145; /* size 0x14 */
extern s16 D_801FDA00_ovl_145210;
extern u8 D_801FDA02_ovl_145210;
extern Slot145 *D_801FDA54_ovl_145210;
extern u8 D_801FDA31_ovl_145210;
extern s32 D_801FDA38_ovl_145210;
extern s16 D_801FDA58_ovl_145210;
extern void *D_801FDA5C_ovl_145210;
extern void *D_801FDA50_ovl_145210;
extern s16 D_801FDA68_ovl_145210;
extern s16 D_801FDA6A_ovl_145210;
void func_801F988C_ovl_145210(void);
typedef struct {
    u8 b0;
    u8 type;
    u8 unk02[2];
    u8 key[8];
    u8 unk0C[4];
    s32 value;
} Ent145; /* size 0x14 */
/* --- end decls --- */

void func_80079618();
typedef struct {
    /* 0x00 */ u8 next;
    /* 0x01 */ u8 used;
    /* 0x02 */ u8 unk02[2];
    /* 0x04 */ s32 handle;
    /* 0x08 */ u8 b8;
    /* 0x09 */ u8 b9;
    /* 0x0A */ u8 unk0A[2];
    /* 0x0C */ u16 refs;
    /* 0x0E */ u8 unk0E[2];
    /* 0x10 */ s32 value;
} Res145;

/* Releases one reference to the cached asset whose value is v; on the last one frees it by kind
 * and returns the slot to the free list (hangs if v is not cached) */
void func_801F40B0_ovl_145210(s32 v) {
    Slot145 *found = NULL;
    Slot145 *e;
    s32 i;

    for (i = 0; i < D_801FDA00_ovl_145210; i++) {
        if (D_801FDA54_ovl_145210[i].used != 0 && FIELD(&D_801FDA54_ovl_145210[i], s32, 0x10) == v) {
            found = &D_801FDA54_ovl_145210[i];
            break;
        }
    }
    e = found;
    if (e == NULL) {
        while (1) {
        }
    }
    if (--((Res145 *)e)->refs == 0) {
        {
            u8 *d = (u8 *)e + 4;

            switch (e->used) {
            case 2:
                func_80079618(FIELD(d, s32, 0), d[4], -0x11);
                break;
            case 3:
                func_80079618(FIELD(d, s32, 0), d[4], -0x14, d[5]);
                break;
            case 4:
            case 5:
                func_80079618(0x0209D322, FIELD(d, u16, 0), -0x11);
                break;
            case 6:
                HFree(FIELD(e, void *, 0x10));
                break;
            }
        }
        e->next = D_801FDA02_ovl_145210;
        ((Res145 *)e)->refs = 0;
        D_801FDA02_ovl_145210 = e - D_801FDA54_ovl_145210;
        e->used = 0;
    }
}

u8 *func_801F4734_ovl_145210(u16 a);
u8 *func_801F477C_ovl_145210(u16 a);
void func_801F4A6C_ovl_145210(u8 *src, u8 *img, u16 alt, u16 *dst, s32 n);
void func_801F4A34_ovl_145210(u8 *src, u8 *dst, s32 n);
/* Builds the three palette sets of portrait id: one 0x1E20 block holding 3 colour tables (0x100
 * entries) then 3 alpha tables (0x40), each filled from messages 0x4F5+i over image 0x4F4 */
/* Builds the three palette sets of portrait id: one 0x1E20 block holding 3 colour tables (0x100
 * entries) then 3 alpha tables (0x40), each filled from messages 0x4F5+i over image 0x4F4 */
#ifdef NON_MATCHING
/* 85/84: the original keeps 0x100/0x40/3/0x400 in saved registers and computes the table offsets and the size check at run time; ours folds them */
void *func_801F4208_ovl_145210(u8 id) {
    s32 n1;
    s32 n2;
    s32 count;
    u8 **t;
    s32 i;
    s32 total = 0;
    s32 off = 0x18;
    u8 *img;
    s32 size = 0x400;

    count = 3;
    n1 = 0x100;
    n2 = 0x40;
    t = HMalloc(0x1E20);
    for (i = 0; i < count; i++) {
        t[i] = (u8 *)t + off;
        off += n1 * 8;
        total += n1;
        t[i + 3] = (u8 *)t + off;
        off += n2 * 8;
        total += n2;
    }
    if (total != (n1 + n2) * count) {
        for (;;) {
        }
    }
    img = func_801F477C_ovl_145210(0x4F4);
    for (i = 0; i < count; i++) {
        u8 *p = func_801F4734_ovl_145210(0x4F5 + i);

        func_801F4A6C_ovl_145210(p, img, id, (u16 *)t[i], size);
        func_801F4A34_ovl_145210(p, t[i + 3], size);
        func_801F40B0_ovl_145210((s32)p);
    }
    func_801F40B0_ovl_145210((s32)img);
    return t;
}
#else
INCLUDE_ASM("asm/nonmatchings/145290", func_801F4208_ovl_145210);
#endif

static inline s32 Cmp8_145(u8 *x, u8 *y) {
    s32 n;

    for (n = 8; n != 0; n--) {
        if (*x++ != *y++) {
            return 1;
        }
    }
    return 0;
}

void *func_801F4208_ovl_145210(u8 id);

/* Reference-counted asset cache: finds the kind/key entry (8-byte key msg) and bumps its count,
 * or takes a free slot and loads the asset for it; hangs on overflow */
#ifdef NON_MATCHING
/* 132/136 instructions: the key compare increments the message pointer later, and the free index D_801FDA02 is reloaded after its 0xFF check in the original */
void func_801F4358_ovl_145210(s32 kind, void *msg) {
    Ent145 *found = NULL;
    Ent145 *e;
    s32 i;

    for (i = 0; i < D_801FDA00_ovl_145210; i++) {
        if (((Ent145 *)D_801FDA54_ovl_145210)[i].type == (u8)kind && !Cmp8_145(((Ent145 *)D_801FDA54_ovl_145210)[i].key, msg)) {
            found = &((Ent145 *)D_801FDA54_ovl_145210)[i];
            break;
        }
    }
    e = found;
    if (e != NULL) {
        if (*(u16 *)e->unk0C >= 0xFFFF) {
            for (;;) {
            }
        }
        (*(u16 *)e->unk0C)++;
    } else {
        if (D_801FDA02_ovl_145210 == 0xFF) {
            for (;;) {
            }
        }
        e = &D_801FDA54_ovl_145210[D_801FDA02_ovl_145210];
        *(u16 *)e->unk0C = 0;
        e->value = 0;
        D_801FDA02_ovl_145210 = e->b0;
        e->type = 0;
        bzero(e->key, 8);
        e->type = kind;
        *(u16 *)e->unk0C = 1;
        _bcopy(msg, e->key, 8);
        switch ((u8)kind) {
            case 2:
                e->value = (s32)LoadAsset(((s32 *)msg)[0], ((u8 *)msg)[4], -2);
                break;
            case 3:
                e->value = (s32)LoadAsset(((s32 *)msg)[0], ((u8 *)msg)[4], -3, ((u8 *)msg)[5]);
                break;
            case 4:
                e->value = (s32)LoadAsset(0x0209D322, ((u16 *)msg)[0], -0xA);
                break;
            case 5:
                e->value = (s32)LoadAsset(0x0209D322, ((u16 *)msg)[0], -1);
                break;
            case 6:
                e->value = (s32)func_801F4208_ovl_145210(((u8 *)msg)[0]);
                break;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/145290", func_801F4358_ovl_145210);
#endif

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

/* Value of the type-3 table entry keyed (a, b, c); hangs if there is none */
#ifdef NON_MATCHING
/* Close. The original keeps the key pointer in s0 (parameters in s1-s3), tests count > 0 with blez, and loads the table base after that test; here the pointer lands in s3 and the base loads first. */
s32 func_801F4638_ovl_145210(s32 a, u8 b, u8 c) {
    struct {
        s32 a;
        u8 b;
        u8 c;
        u8 pad[2];
    } key;
    Ent145 *e;
    Ent145 *found;
    u8 *kp = (u8 *)&key;

    bzero(kp, 8);
    found = NULL;
    key.a = a;
    key.b = b;
    key.c = c;
    for (e = D_801FDA54_ovl_145210; e < D_801FDA54_ovl_145210 + D_801FDA00_ovl_145210; e++) {
        if (e->type == 3 && !Cmp8_145(e->key, kp)) {
            found = e;
            break;
        }
    }
    if (found == NULL) {
        for (;;);
    }
    return found->value;
}
#else
INCLUDE_ASM("asm/nonmatchings/145290", func_801F4638_ovl_145210);
#endif

/* Sends message 4 for a; returns whatever func_801F4358 left in v0 (no return statement) */
u8 *func_801F4734_ovl_145210(u16 a) {
    s16 msg[4];
    s16 *p = msg;

    bzero(p, 8);
    p[0] = a;
    func_801F4358_ovl_145210(4, p);
}

/* Sends message 5 for a; returns whatever func_801F4358 left in v0 (no return statement) */
u8 *func_801F477C_ovl_145210(u16 a) {
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

/* Frees cached asset e by kind and returns its slot to the free list */
static inline void Release145(Slot145 *e) {
    u8 *d = (u8 *)e + 4;

    switch (e->used) {
    case 2:
        func_80079618(FIELD(d, s32, 0), d[4], -0x11);
        break;
    case 3:
        func_80079618(FIELD(d, s32, 0), d[4], -0x14, d[5]);
        break;
    case 4:
    case 5:
        func_80079618(0x0209D322, FIELD(d, u16, 0), -0x11);
        break;
    case 6:
        HFree(FIELD(e, void *, 0x10));
        break;
    }
    e->next = D_801FDA02_ovl_145210;
    ((Res145 *)e)->refs = 0;
    D_801FDA02_ovl_145210 = e - D_801FDA54_ovl_145210;
    e->used = 0;
}

/* Frees every cached asset and the cache table */
void func_801F480C_ovl_145210(void) {
    s32 i;

    for (i = 0; i < D_801FDA00_ovl_145210; i++) {
        if (D_801FDA54_ovl_145210[i].used != 0) {
            Release145(&D_801FDA54_ovl_145210[i]);
        }
    }
    D_801FDA54_ovl_145210 = ((void *(*)(void *))HFree)(D_801FDA54_ovl_145210);
}

/* the switch table above is padded by two words in the original rodata */
__asm__(".section .rodata\n.word 0, 0\n.section .text\n");

/* Pool of 32 slots chained by index; 0xFF ends the chain */
void func_801F4960_ovl_145210(void) {
    s32 i;

    D_801FDA00_ovl_145210 = 0x20;
    D_801FDA54_ovl_145210 = HMalloc(0x280);
    bzero(D_801FDA54_ovl_145210, 0x280);
    for (i = 0; i < D_801FDA00_ovl_145210 - 1; i++) {
        D_801FDA54_ovl_145210[i].used = 0;
        D_801FDA54_ovl_145210[i].next = i + 1;
    }
    D_801FDA54_ovl_145210[i].used = 0;
    D_801FDA54_ovl_145210[i].next = 0xFF;
    D_801FDA02_ovl_145210 = 0;
}

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

/* Facing (0-7) for a turn fraction a in [0, 1), in eighths centred on each direction */
s32 func_801F4CD0_ovl_145210(f32 a) {
    if (a >= 0.9375 || a < 0.0625) {
        return 2;
    }
    if (a >= 0.0625 && a < 0.1875) {
        return 3;
    }
    if (a >= 0.1875 && a < 0.3125) {
        return 4;
    }
    if (a >= 0.3125 && a < 0.4375) {
        return 5;
    }
    if (a >= 0.4375 && a < 0.5625) {
        return 6;
    }
    if (a >= 0.5625 && a < 0.6875) {
        return 7;
    }
    if (a >= 0.6875 && a < 0.8125) {
        return 0;
    }
    if (a >= 0.8125 && a < 0.9375) {
        return 1;
    }
    return 0;
}

s32 func_801F4EB4_ovl_145210(MapUnit *u) {
    return u->unk70 == 1 && !(u->flags & 0x40);
}

s32 func_801F4030_ovl_145210(s32 a, s32 alt);
extern u8 D_80187C59[][0x48]; /* gClassTable[].baseClass */
extern u8 D_80193BD1[][0x38]; /* player characters: class, base class */
extern u8 D_80193BD2[][0x38];
extern u8 D_80195571[][0x34]; /* enemy characters */
extern u8 D_80195572[][0x34];
extern u8 D_801971F2[][0x19]; /* gSquads[].members[0] */

/* Portrait class of map unit u's squad leader: its base class when the class has none of its own
 * or differs, falling back to the base class when out of range or without a portrait */
#ifdef NON_MATCHING
/* 71/71, 5 words: the squad id is kept in a2 in the original, a1 here */
s32 func_801F4ED8_ovl_145210(MapUnit *u) {
    u8 sq = u->unk04[0];
    u8 m = D_801971F2[sq][0];
    u8 base;
    u8 cls;
    s32 r;

    if (u->flags & 8 ? sq < 30 : 0) {
        cls = D_80193BD1[m][0];
        base = D_80193BD2[m][0];
    } else {
        cls = D_80195571[m][0];
        base = D_80195572[m][0];
    }
    if (D_80187C59[cls][0] == 0) {
        r = cls;
        if (r != base) {
            r = base;
        }
    } else {
        r = cls;
        if (D_80187C59[cls][0] != base) {
            r = base;
        }
    }
    if (r >= 0xAA) {
        r = base;
    }
    if (((s32 (*)())func_801F4030_ovl_145210)(r) == -1) { /* called without alt: a1 left over */
        r = base;
    }
    return (u8)r;
}
#else
INCLUDE_ASM("asm/nonmatchings/145290", func_801F4ED8_ovl_145210);
#endif

/* Slot of a unit; hangs if it is not on the map. */
inline s32 func_801F4FF4_ovl_145210(MapUnit *u) {
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

inline void func_801F503C_ovl_145210(u8 *a, u8 *b, u8 *t) {
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

s32 func_801F40A0_ovl_145210(s32 a);
#define IsLarge145(c) func_801F40A0_ovl_145210(c) /* returns c == 0x87 */
extern u8 *D_801FCD2C_ovl_145210[];
void func_801F9EC8_ovl_145210();

/* Sets map entry a up for class d (c: palette, e: palette table, f: second class byte): builds
 * both of its sprite parts (texture and palette buffers sized by the class's sprite size) and
 * installs its draw callback with data b */
#ifdef NON_MATCHING
/* 164 vs 160: func_801F503C inlined; the original keeps 1 and 0x87 in s8/s7, walks the parts with an unbiased pointer and shares one hang loop */
void func_801F5550_ovl_145210(u8 *a, void *b, s32 c, s32 d, s32 e, s32 f) {
    u32 k;
    u8 *p;
    u8 *q;

    bzero(a, 4);
    a[2] = d;
    a[8] = d;
    a[4] = c;
    a[0xA] = c;
    a[3] = f;
    a[9] = f;
    a[5] = e;
    a[0xB] = e;
    for (k = 0, q = a; k < 2; k++, q += 0x14) {
        u32 size;
        s32 t;
        u8 *s3;
        u8 *s2;
        u8 pal;
        u8 b8;

        t = IsLarge145(a[2]);
        size = 0x400;
        if (t != 0) {
            size = 0x780;
            if (t != 1) {
                for (;;) {
                }
            }
        }
        FIELD(q, u16 *, 0x10) = HMalloc(size * 2);
        FIELD(q, u8 *, 0x14) = HMalloc(size >> 1);
        p = q + 0x10;
        pal = 8;
        if (a[2] != 0x87) {
            pal = a[5];
        }
        p[0xA] = D_801FCD2C_ovl_145210[pal][a[6] * 2 + 1] & 0xF;
        FIELD(p, u16, 8) = ((s32 (*)())func_801F4030_ovl_145210)(a[2]); /* a1 left over */
        b8 = 0;
        if (a[2] != 0x87) {
            b8 = a[4];
        }
        p[0xB] = b8;
        p[0xC] = IsLarge145(a[2]);
        FIELD(q, u16, 0x1E) = FIELD(q, u16, 0x18);
        q[0x20] = q[0x1A];
        q[0x21] = q[0x1B];
        q[0x22] = q[0x1C];
        s3 = func_801F477C_ovl_145210(FIELD(q, u16, 0x18));
        s2 = func_801F4734_ovl_145210(FIELD(q, u16, 0x18) + q[0x1A]);
        func_801F503C_ovl_145210(s2, s3, q + 0x10);
        func_801F40B0_ovl_145210((s32)s3);
        func_801F40B0_ovl_145210((s32)s2);
    }
    func_801F4BE8_ovl_145210((s32 *)(a + 0x38), (s32)func_801F9EC8_ovl_145210);
    func_801F4BF0_ovl_145210((s32 *)(a + 0x38), (s32)b);
    a[0x4E] = 0xFF;
    a[0x4D] = 0xFF;
    a[0x4C] = 0xFF;
    a[0x4B] = 0xFF;
    FIELD(a, s32, 0x58) = 0;
    a[0] = 3;
    FIELD(a, f32, 0x54) = 1.0f;
    FIELD(a, f32, 0x50) = 1.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/145290", func_801F5550_ovl_145210);
#endif

typedef struct {
    u8 unk00[8];
    u16 cls;
    u8 pal;
    u8 b0B;
    u8 large;
    u8 unk0D[7];
} Part145; /* size 0x14 */

typedef struct {
    u8 unk00[0x10];
    Part145 part[2];
} MapEnt145;

/* Map entry a's animation step. Mode 2 flips the shown sprite part and sets state 3; mode 3
 * counts frames on the key table and, on a new key frame (queued at the tail) or a changed
 * class/position (queued at the head), rebuilds the hidden part and queues the entry */
#ifdef NON_MATCHING
/* same size (0x300): GCC keeps 0x87 in s3 across the func_801F4030 call where the original
 * reloads it for each compare, and adds 0x10 to the part offset before the base (original:
 * base + offset, then 0x10) */
void func_801F57D0_ovl_145210(u8 *a, u8 mode) {
    s32 r;
    Part145 *p;
    u8 *t;
    u8 pal;
    u8 b8;
    s16 i;
    s32 k;

    switch (mode) {
        case 2:
            a[0] = 3;
            a[0xC] ^= 1;
            break;
        case 1:
            break;
        case 3:
            r = 0;
            if (!(a[1] & 2)) {
                a[7]++;
            }
            if (a[2] != 0x87) {
                k = a[5];
            } else {
                k = 8;
            }
            t = D_801FCD2C_ovl_145210[k];
            if (a[7] >= t[a[6] * 2]) {
                a[6]++;
                a[7] = 0;
                r = 1;
                if (t[a[6] * 2] == 0 && t[a[6] * 2 + 1] == 0xFF) {
                    a[6] = 0;
                }
            } else if (FIELD(a, u16, 8) != FIELD(a, u16, 2) || FIELD(a, u16, 0xA) != FIELD(a, u16, 4)) {
                r = 2;
            }
            if (r != 0) {
                a[0xD] = a[0xC] ^ 1;
                p = &((MapEnt145 *)a)->part[a[0xD]];
                pal = 8;
                if (a[2] != 0x87) {
                    pal = a[5];
                }
                p->pal = D_801FCD2C_ovl_145210[pal][a[6] * 2 + 1] & 0xF;
                p->cls = func_801F4030_ovl_145210(a[2], a[3]);
                b8 = 0;
                if (a[2] != 0x87) {
                    b8 = a[4];
                }
                p->b0B = b8;
                p->large = func_801F40A0_ovl_145210(a[2]);
                if (r == 1) {
                    i = D_801FDA68_ovl_145210 - 1;
                    if (i < 0) {
                        i = D_801FDA58_ovl_145210 - 1;
                    }
                    if (D_801FDA6A_ovl_145210 == i) {
                        for (;;) {
                        }
                    }
                    ((u8 **)D_801FDA5C_ovl_145210)[D_801FDA6A_ovl_145210++] = a;
                    if (D_801FDA6A_ovl_145210 >= D_801FDA58_ovl_145210) {
                        D_801FDA6A_ovl_145210 = 0;
                    }
                } else {
                    D_801FDA68_ovl_145210--;
                    if (D_801FDA68_ovl_145210 < 0) {
                        D_801FDA68_ovl_145210 = D_801FDA58_ovl_145210 - 1;
                    }
                    if (D_801FDA6A_ovl_145210 == D_801FDA68_ovl_145210) {
                        for (;;) {
                        }
                    }
                    ((u8 **)D_801FDA5C_ovl_145210)[D_801FDA68_ovl_145210] = a;
                }
                a[0] = 1;
            }
            a[8] = a[2];
            a[9] = a[3];
            a[0xA] = a[4];
            a[0xB] = a[5];
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/145290", func_801F57D0_ovl_145210);
#endif

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern s32 D_801F3658;
extern u8 *D_801FCD2C_ovl_145210[];

void func_801F5AD0_ovl_145210(void *unit, void *src) {
    s32 table;
    u16 flags;
    u8 bits;
    void *sub;

    if (FIELD(unit, u8, 1) & 1) {
        flags = FIELD(src, u16, 4);
        sub = unit + 0x38;
        if (flags & 8) {
            if (flags & 0x10) {
                FIELD(unit, s8, 0x48) = 3;
            } else {
                FIELD(unit, s8, 0x48) = 2;
            }
        } else if (flags & 0x8000) {
            FIELD(unit, s8, 0x48) = 1;
        } else {
            FIELD(unit, s8, 0x48) = 0;
        }
        if (!(FIELD(src, u16, 4) & 0x4000)) {
            FIELD(sub, u8, 0x13) = (u8) FIELD(src, u8, 8);
            FIELD(sub, u8, 0x14) = (u8) FIELD(src, u8, 9);
            FIELD(sub, u8, 0x15) = (u8) FIELD(src, u8, 0xA);
            FIELD(sub, u8, 0x16) = (u8) FIELD(src, u8, 0xB);
        }
        {
            u8 *r = (u8 *)unit + FIELD(unit, u8, 0xC) * 0x14;

            FIELD(sub, s32, 8) = FIELD(r, s32, 0x10);
        }
        {
            u8 *r = (u8 *)unit + FIELD(unit, u8, 0xC) * 0x14;

            FIELD(sub, s32, 0xC) = FIELD(r, s32, 0x14);
        }
        FIELD(sub, s8, 0x12) = func_801F40A0_ovl_145210(FIELD(unit, u8, 2));
        table = (s32)D_801FCD2C_ovl_145210[FIELD(unit, u8, 5)];
        bits = FIELD(sub, u8, 0x11) & 0xF8;
        FIELD(sub, u8, 0x11) = bits;
        if (FIELD(((FIELD(unit, u8, 6) * 2) + table), u8, 1) & 0x80) {
            FIELD(sub, u8, 0x11) = (u8) (bits | 1);
        }
        if (FIELD(((FIELD(unit, u8, 6) * 2) + table), u8, 1) & 0x40) {
            FIELD(sub, u8, 0x11) = (u8) (FIELD(sub, u8, 0x11) | 2);
        }
        if ((D_801F3658 != -1) && (FIELD(src, s32, 0) == ((s32 *)D_801F0CB0)[D_801F3658])) {
            FIELD(sub, u8, 0x11) = (u8) (FIELD(sub, u8, 0x11) | 4);
        }
        func_801F4BBC_ovl_145210((s32) sub);
    }
}

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

typedef struct {
    /* 0x0 */ u8 t;
    /* 0x1 */ u8 pad[3];
    /* 0x4 */ f32 x;
    /* 0x8 */ f32 y;
} Key145;

/* Steps o's frame (o+6) and sets its position (o+0x20/0x24) from the n keys, interpolating between
 * the surrounding pair; 1 once the frame reaches `end` */
s32 func_801F5D28_ovl_145210(u8 *o, Key145 *k, u8 n, u8 end) {
    u8 t = ++o[6];
    s32 lo = 0;
    s32 hi = n - 1;
    s32 done = t >= end;

    while (lo < hi) {
        s32 mid = (lo + hi) / 2;
        s32 m1 = mid + 1;

        if (t < k[m1].t) {
            hi = mid;
        } else {
            lo = m1;
        }
    }
    hi = lo + 1;
    if (lo == n - 1) {
        FIELD(o, f32, 0x20) = k[lo].x;
        FIELD(o, f32, 0x24) = k[lo].y;
    } else {
        FIELD(o, f32, 0x20) = k[lo].x + (k[hi].x - k[lo].x) * (f32)(o[6] - k[lo].t) / (f32)(k[hi].t - k[lo].t);
        FIELD(o, f32, 0x24) = k[lo].y + (k[hi].y - k[lo].y) * (f32)(o[6] - k[lo].t) / (f32)(k[hi].t - k[lo].t);
    }
    return done;
}

INCLUDE_RODATA("asm/nonmatchings/145290", D_801FD958_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F5E94_ovl_145210);

static inline f32 Wrap360_145(f32 a) {
    while (a < 0.0f) {
        a += 360.0f;
    }
    while (a >= 360.0f) {
        a -= 360.0f;
    }
    return a;
}

/* Steps map marker m's flip animation (angle at +0x88): opens, turns to 270, refreshes its unit
 * info, turns back to 0 and finishes */
#ifdef NON_MATCHING
/* 119/119 instructions, 6 words differ: in case 4 the unit pointer and the result swap a0/a1 */
void func_801F632C_ovl_145210(MapMarker *m) {
    u8 *s = (u8 *)m + 0x30;
    u8 *a = (u8 *)m + 0x68;
    f32 r;
    s32 v;

    switch (m->b7) {
        case 0:
            m->flags |= 0x4000;
        case 1:
        case 2:
        case 5:
        case 6:
            m->b7++;
            break;
        case 3:
            FIELD(a, f32, 0x20) -= 16.0f;
            FIELD(a, f32, 0x20) = Wrap360_145(FIELD(a, f32, 0x20));
            if (FIELD(a, f32, 0x20) <= 270.0f) {
                FIELD(a, f32, 0x20) = 270.0f;
                m->b7 = 4;
            }
            break;
        case 4:
            v = 0;
            if (m->u->unk70 == 1) {
                u32 t = m->u->flags & 0x40;

                v = t == 0;
            }
            s[3] = v;
            s[2] = func_801F4ED8_ovl_145210(m->u);
            m->b7++;
            break;
        case 7:
            FIELD(a, f32, 0x20) = 90.0f;
            m->b7++;
        case 8:
            r = FIELD(a, f32, 0x20) - 16.0f;
            FIELD(a, f32, 0x20) = r;
            if (r <= 0.0f) {
                FIELD(a, f32, 0x20) = 0.0f;
                m->b7 = 9;
            } else {
                while (r >= 360.0f) {
                    r -= 360.0f;
                }
                FIELD(a, f32, 0x20) = r;
            }
            break;
        case 9:
            m->b6 = 0;
            m->flags &= 0xB7FF;
            break;
    }
    s[1] |= 2;
}
#else
INCLUDE_ASM("asm/nonmatchings/145290", func_801F632C_ovl_145210);
#endif

extern void (*D_801FD094_ovl_145210[])(MapMarker *m);

/* Per-frame marker update for a live unit: visibility (bit 0), outline flags, brightness,
 * blink alpha (0xB), then picks a new animation state when idle and runs its handler */
#ifdef NON_MATCHING
/* 4 instructions short: the original keeps separate copies of the brightness and blink values
 * (extra moves) and stores the blink alpha in each branch; register choice differs throughout */
void func_801F6540_ovl_145210(MapMarker *m) {
    u8 *s;
    s32 v;
    s32 t;
    s32 c;
    u8 w;
    u32 fl;

    if (!(m->u->flags & 1)) {
        return;
    }
    if ((m->u->flags & 0x60000) != 0x40000) {
        m->flags |= 1;
    } else {
        m->flags &= ~1;
    }
    s = (u8 *)m + 0x30;
    t = m->u->unk70 == 1 && !(m->u->flags & 0x40);
    m->b33 = t;
    w = FIELD(m, u8, 0x31) & ~1;
    FIELD(m, u8, 0x31) = w;
    if ((m->u->flags & 0x28) || (!(m->u->flags & 0x20) && FIELD(m, u8, 0xB) != 0)) {
        FIELD(m, u8, 0x31) = w | 1;
    } else if ((m->u->flags & 0x11) == 1) {
        s[1] |= 1;
    }
    if ((m->flags & 1) && (s[6] == 0 || s[6] == 2)) {
        s[1] |= 2;
    } else {
        s[1] &= ~2;
    }
    if (m->flags & 0x200) {
        c = FIELD(m, u8, 8) - 0x20;
        if (c <= 100) {
            c = 100;
        }
    } else {
        c = FIELD(m, u8, 8) + 0x40;
        if (c >= 0xFF) {
            c = 0xFF;
        }
    }
    w = c;
    FIELD(m, u8, 0xA) = FIELD(m, u8, 9) = FIELD(m, u8, 8) = w;
    if (m->flags & 0x100) {
        s[1] |= 1;
        if (m->flags & 0x80) {
            v = FIELD(m, u8, 0xB) - 0x20;
            if (v <= 0) {
                v = 0;
                m->flags &= ~0x80;
            }
        } else {
            v = FIELD(m, u8, 0xB) + 0x20;
            if (v >= 0xFF) {
                v = 0xFF;
                m->flags |= 0x80;
            }
        }
    } else {
        v = FIELD(m, u8, 0xB);
        if (m->u->flags & 0x28) {
            if (v < 0xDF) {
                v += 0x20;
            } else {
                v = 0xFF;
            }
        } else if (v < 0x41) {
            v = 0;
        } else {
            v -= 0x20;
        }
    }
    FIELD(m, u8, 0xB) = v;
    if (m->b6 == 0) {
        fl = m->u->flags;
        if (!(fl & 0x10)) {
            v = 2;
        } else if (m->flags & 0x400) {
            v = 5;
        } else if (m->flags & 0x800) {
            v = 6;
        } else if ((fl & 0x28) == 8) {
            v = 4;
        } else if (fl & 0x20000) {
            v = 1;
        } else if (fl & 0x80000) {
            v = 3;
        } else {
            goto run;
        }
        m->b6 = v;
        m->b7 = 0;
    }
run:
    D_801FD094_ovl_145210[m->b6](m);
}
#else
INCLUDE_ASM("asm/nonmatchings/145290", func_801F6540_ovl_145210);
#endif

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void func_801FB3BC_ovl_145210();
void func_801F5550_ovl_145210(u8 *a, void *b, s32 c, s32 d, s32 e, s32 f);

/* Creates the map entry of unit u in the first free slot and links it to the unit's battle index */
#ifdef NON_MATCHING
/* 108/108 instructions, 21 words differ: register choice and one delay slot */
void func_801F67F0_ovl_145210(MapUnit *u) {
    MapEntry *e = HMalloc(0xDC);
    s32 slot;
    s32 ally;
    s32 kind;
    s32 lead;

    bzero(e, 0xDC);
    for (slot = 0; slot < D_801FDA32_ovl_145210; slot++) {
        if (D_801FDA34_ovl_145210[slot] == NULL) {
            break;
        }
    }
    ally = (u->flags & 8) == 0;
    kind = func_801F4CD0_ovl_145210(FIELD(u, f32, 0x18));
    lead = u->unk70 == 1 && !(u->flags & 0x40);
    func_801F5550_ovl_145210((u8 *)e + 0x30, (u8 *)e + 0x10, ally, func_801F4ED8_ovl_145210(u), kind, lead);
    if (u->flags & 0x20000) {
        e->unk06[0] = 1;
        e->unk06[1] = 3;
    }
    e->bB = 0xFF;
    e->unk06[4] = 0xFF;
    e->unk06[3] = 0xFF;
    e->unk06[2] = 0xFF;
    e->bB = 0;
    e->id = (s32)u;
    FIELD(e, s16, 0x28) = D_801F367C - func_801F4FF4_ovl_145210(u);
    func_801F4BE8_ovl_145210((s32 *)((u8 *)e + 0xCC), (s32)func_801FB3BC_ovl_145210);
    func_801F4BF0_ovl_145210((s32 *)((u8 *)e + 0xCC), (s32)((u8 *)e + 0x10));
    D_801FDA34_ovl_145210[slot] = e;
}
#else
INCLUDE_ASM("asm/nonmatchings/145290", func_801F67F0_ovl_145210);
#endif

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

/* Frees unit u's map entry (its two parts' buffers and the entry) and clears its slot's flag 1 */
void func_801F69FC_ovl_145210(MapUnit *u) {
    s32 i;
    u32 k;
    MapEntry *e;
    u8 *p;

    for (i = 0; i < D_801FDA32_ovl_145210; i++) {
        if (D_801FDA34_ovl_145210[i] != NULL && D_801FDA34_ovl_145210[i]->id == (s32)u) {
            break;
        }
    }
    if (i < D_801FDA32_ovl_145210) {
        e = D_801FDA34_ovl_145210[i];
        p = (u8 *)e + 0x30;
        for (k = 0; k < 2; k++) {
            u8 *q = (u8 *)(k * 0x14 + (s32)p);

            q += 0x10;
            HFree(((void **)q)[0]);
            HFree(((void **)q)[1]);
        }
        HFree(e);
        D_801FDA34_ovl_145210[i] = NULL;
        i = func_801F4FF4_ovl_145210(u);
        D_801FDA3C_ovl_145210[i * 4] &= ~1;
    }
}

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

void func_801F9860_ovl_145210(void);

/* Frees the map's buffers and every entry with its two sub-records' images */
#ifdef NON_MATCHING
/* 71/71 instructions, 15 words differ: the sub-record pointer is kept as base + offset and 0x10 added before the loads */
void func_801F83F4_ovl_145210(void) {
    s32 i;
    MapEntry *e;
    u8 *subs;
    u8 *p;
    u32 j;
    s32 off;

    HFree(D_801FDA3C_ovl_145210);
    i = 0;
    func_801F4B14_ovl_145210();
    HFree(D_801FDA50_ovl_145210);
    D_801FDA50_ovl_145210 = NULL;
    HFree(D_801FDA5C_ovl_145210);
    D_801FDA5C_ovl_145210 = NULL;
    func_801F9860_ovl_145210();
    func_801F480C_ovl_145210();
    for (; i < D_801FDA32_ovl_145210; i++) {
        e = D_801FDA34_ovl_145210[i];
        if (e != NULL) {
            subs = (u8 *)e + 0x30;
            j = 0;
            off = 0;
            p = subs;
            do {
                off += 0x14;
                HFree(FIELD(p, void *, 0x10));
                j++;
                HFree(FIELD(p, void *, 0x14));
                p = subs + off;
            } while (j < 2);
            HFree(e);
        }
    }
    HFree(D_801FDA34_ovl_145210);
}
#else
INCLUDE_ASM("asm/nonmatchings/145290", func_801F83F4_ovl_145210);
#endif

void func_801F8510_ovl_145210(void) {
    s32 n;

    D_801FDA32_ovl_145210 = 0x19;
    D_801FDA34_ovl_145210 = HMalloc(0x64);
    bzero(D_801FDA34_ovl_145210, 0x64);
    D_801FDA31_ovl_145210 = 0;
    D_801FDA30_ovl_145210 = 0;
    D_801FDA38_ovl_145210 = -1;
    func_801F4960_ovl_145210();
    func_801F988C_ovl_145210();
    D_801FDA58_ovl_145210 = 0x1A;
    D_801FDA5C_ovl_145210 = HMalloc(0x68);
    D_801FDA50_ovl_145210 = HMalloc(0x68);
    D_801FDA6A_ovl_145210 = 0;
    D_801FDA68_ovl_145210 = 0;
    func_801F5504_ovl_145210(0);
    func_801F4AD0_ovl_145210();
    n = D_801F367C * 4;
    D_801FDA3C_ovl_145210 = HMalloc(n);
    bzero(D_801FDA3C_ovl_145210, n);
}

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
