#include "common.h"

/* 26F1E0 */

typedef struct {
    u8 unk00[0x3C];
    s32 w3C;
    s32 w40;
    s32 w44;
    s32 w48;
} Task26F;

extern s32 D_80220F68_ovl_25EE90;
extern s32 D_80220F6C_ovl_25EE90;

void func_8021A630_ovl_25EE90(void);
s32 func_8021D168_ovl_25EE90(u16 msg, u8 *o);
void func_8021C62C_ovl_25EE90(void);
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void *func_8020DF00_ovl_25EE90(void *fn);
s32 func_801F7128(u8 c);
void func_8021BA3C_ovl_25EE90();
u8 *func_80217460_ovl_25EE90(s32 id);
void func_8020DC80_ovl_25EE90(u16 state);
s32 func_8021B500_ovl_25EE90(u16 msg, u8 *o);
void func_8020D814_ovl_25EE90(void *t);
void func_8020DFB8_ovl_25EE90(void);
void func_8020B1E0_ovl_25EE90(s16 i, void *p, s16 *out);
void func_8020A4A8_ovl_25EE90(void *a, void *b);
s32 func_8020C9B0_ovl_25EE90(s32 a);
void func_8021AC40_ovl_25EE90(u16 msg, u8 *o);
void func_8020FF6C_ovl_25EE90();
extern u8 D_80220980_ovl_25EE90[];
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021A630_ovl_25EE90);

void *func_8021A998_ovl_25EE90(s32 a, s32 b) {
    D_80220F68_ovl_25EE90 = a;
    D_80220F6C_ovl_25EE90 = b;
    return func_8020DF00_ovl_25EE90(func_8021A630_ovl_25EE90);
}

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
typedef struct {
    s32 flags;
    void *task;
} Slot26F;
typedef struct {
    /* 0x00 */ s16 id;
    /* 0x02 */ u8 side;
    /* 0x04 */ u8 *list;
    /* 0x08 */ void *(*spawn)(s16 id, u8 side, u8 kind, s32 n);
    /* 0x0C */ s32 n;
    /* 0x10 */ s32 pos;
    /* 0x14 */ s32 slot;
    /* 0x18 */ s32 pending;
    /* 0x1C */ Slot26F slots[8];
} Spawner26F;
void bzero(void *p, s32 n);
typedef struct {
    s32 w[3];
} Args26F;
s32 func_8020DCAC_ovl_25EE90(void *t, u16 a);

/* Spawns the effects of a 0xFF-terminated kind list one after another (each once the last has
 * started), keeping up to 8 running; done (0x1002) when all have finished */
s32 func_8021A9C8_ovl_25EE90(u16 msg, Spawner26F *o) {
    s32 r = 0;
    s32 i;
    s32 live;
    Slot26F *s;
    s32 kind;

    switch (msg) {
        case 0x101:
            func_8020DFB8_ovl_25EE90();
            break;
        case 0x100:
            bzero(o, 0x5C);
            *(Args26F *)o = *(Args26F *)&D_80220F68_ovl_25EE90;
            o->pending = 1;
            func_8020DC80_ovl_25EE90(0x1000);
            break;
        case 0x1000:
            kind = o->list[o->pos];
            if (kind != 0xFF) {
                o->pos++;
                s = &o->slots[o->slot];
                if (s->task != NULL) {
                    for (;;) {
                    }
                }
                s->task = o->spawn(o->id, o->side, kind, o->n++);
                if (++o->slot >= 8) {
                    o->slot = 0;
                }
                o->pending--;
            } else {
                o->pending = 0;
            }
            func_8020DC80_ovl_25EE90(0x1001);
        case 0x1001:
            for (i = 0, live = 0; i < 8; i++) {
                s = &o->slots[i];
                if (s->task != NULL) {
                    live++;
                    if (!(s->flags & 1) && func_8020DCAC_ovl_25EE90(s->task, 0x1000) != 0) {
                        s->flags |= 1;
                        o->pending++;
                        func_8020DC80_ovl_25EE90(0x1000);
                    }
                    if (func_8020DCAC_ovl_25EE90(s->task, 0x1001) != 0) {
                        func_8020DCAC_ovl_25EE90(s->task, 0x101);
                        bzero(s, 8);
                    }
                }
            }
            if (live == 0 && o->pending == 0 && o->list[o->pos] == 0xFF) {
                func_8020DC80_ovl_25EE90(0x1002);
            }
            break;
        case 0x1002:
            break;
        case 0x1003:
            if (FIELD(o, u16, -0x1C) == 0x1002) {
                r = 1;
            }
            break;
    }
    return r;
}

void func_8020FFA0_ovl_25EE90();
void func_8020C074_ovl_25EE90(s32 a);

/* Scrolling-texture parts handler: 0 sets the parts up (draw routine, texture handle, 16x16
 * window), 1 releases the texture, 2 scrolls the window by one texel */
void func_8021AC40_ovl_25EE90(u16 msg, u8 *o) {
    switch (msg) {
    case 0: {
        s32 r;
        u32 i;
        u8 *e;

        r = func_8020C9B0_ovl_25EE90(3);
        for (i = 0; i < FIELD(FIELD(o, u8 *, 0x50), u32, 4); i++) {
            if (FIELD(o, u8 **, 0x58)[i] != NULL) {
                FIELD(FIELD(o, u8 **, 0x58)[i], void *, 0) = func_8020FFA0_ovl_25EE90;
                e = FIELD(o, u8 **, 0x58)[i];
                FIELD(e, s32, 0x34) = r;
                FIELD(e, u8 *, 0x30) = D_80220980_ovl_25EE90;
                FIELD(e, s16, 0x3A) = 0;
                FIELD(e, s16, 0x38) = 0;
                FIELD(e, s16, 0x3E) = 0xF;
                FIELD(e, s16, 0x3C) = 0xF;
                FIELD(e, s16, 0x42) = 0;
                FIELD(e, s16, 0x40) = 0;
                FIELD(e, s16, 0x46) = 0xF;
                FIELD(e, s16, 0x44) = 0xF;
            }
        }
        break;
    }
    case 1: {
        u32 i;

        for (i = 0; FIELD(o, u8 **, 0x58)[i] == NULL; i++) {
        }
        func_8020C074_ovl_25EE90(FIELD(FIELD(o, u8 **, 0x58)[i], s32, 0x34));
        break;
    }
    case 2: {
        u32 i;
        u8 *e;

        for (i = 0; i < FIELD(FIELD(o, u8 *, 0x50), u32, 4); i++) {
            e = FIELD(o, u8 **, 0x58)[i];
            if (e != NULL) {
                FIELD(e, s16, 0x42) = (FIELD(e, s16, 0x42) + 1) & 0xF;
                FIELD(e, s16, 0x44) = FIELD(e, s16, 0x40) + 0x10;
                FIELD(e, s16, 0x46) = FIELD(e, s16, 0x42) + 0xF;
            }
        }
        break;
    }
    }
}

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021ADE0_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021B040_ovl_25EE90);

/* Common effect message handler: 0x100 spawns effect 0x54, 0x1000/0x1001 run a 12-frame colour fade */
#ifdef NON_MATCHING
/* only the object/effect saved registers are swapped (s0/s1) */
s32 func_8021B500_ovl_25EE90(u16 msg, u8 *o) {
    s16 c[4];
    u8 *e;

    switch (msg) {
        case 0x101:
            func_8020D814_ovl_25EE90(FIELD(o, void *, 0x40));
            func_8020DFB8_ovl_25EE90();
            break;
        case 0x100: {
            u8 *n;

            FIELD(o, s32, 0x44) = D_80220F68_ovl_25EE90;
            n = func_80217460_ovl_25EE90(0x54);
            FIELD(o, u8 *, 0x40) = n;
            FIELD(n, s32, 0x10) = FIELD(o, s32, 0x44);
            FIELD(FIELD(o, u8 *, 0x40), u16, 0xA) |= 0x2000;
            FIELD(o, s16, 0x4C) = 0x40;
            FIELD(o, s16, 0x4E) = 0xFF;
            FIELD(o, s16, 0x50) = 0x80;
            FIELD(o, s16, 0x52) = 0;
            func_8020DC80_ovl_25EE90(0x1000);
            break;
        }
        case 0x1000:
            FIELD(o, s16, 0x4A) = 12;
            FIELD(o, s16, 0x48) = 0;
            FIELD(o, s16, 0x54) = 0xFF;
            FIELD(o, s16, 0x56) = 0xFF;
            FIELD(o, s16, 0x58) = 0xFF;
            FIELD(o, s16, 0x5A) = 0xFF;
            FIELD(o, s32, 0x5C) = 0;
            func_8020DC80_ovl_25EE90(0x1001);
            /* fallthrough */
        case 0x1001:
            e = FIELD(o, u8 *, 0x40);
            func_8020B1E0_ovl_25EE90(FIELD(o, s16, 0x48), o + 0x4A, c);
            FIELD(e, s16, 0x60) = c[0];
            FIELD(e, s16, 0x62) = c[1];
            FIELD(e, s16, 0x64) = c[2];
            e += 0x1C;
            if (FIELD(o, s32, 0x5C) == 0) {
                func_8020A4A8_ovl_25EE90(o, e);
                FIELD(o, s32, 0x5C)++;
            } else if (FIELD(o, s32, 0x5C) == 1) {
                FIELD(FIELD(o, u8 *, 0x40), u16, 8) &= ~1;
                FIELD(o, s32, 0x5C)++;
            }
            FIELD(e, f32, 0x40) = c[3] / 255.0f;
            if (++FIELD(o, s16, 0x48) > FIELD(o, s16, 0x4A)) {
                func_8020DC80_ovl_25EE90(0x101);
            }
            break;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021B500_ovl_25EE90);
#endif

void func_8021B6C4_ovl_25EE90(s32 a) {
    D_80220F68_ovl_25EE90 = a;
    func_8020DF00_ovl_25EE90(func_8021B500_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021B6F0_ovl_25EE90);

typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 dir[3];
    /* 0x18 */ s32 t;
    /* 0x1C */ f32 len;
    /* 0x20 */ f32 speed;
} Path26F;
typedef struct {
    s16 x;
    s16 z;
} Point26F;
extern Point26F D_802209E0_ovl_25EE90[];
void func_80217C84_ovl_25EE90(s32 id, f32 *out);
f32 func_8020A3C8_ovl_25EE90(f32 *v);
void func_8020A2E0_ovl_25EE90(f32 *v, f32 s, f32 *out);

/* Aims o's path (at 0x4C) from its position at its next waypoint, or at target 0x1C (stopping 40
 * short) when the route has ended */
void func_8021B8D8_ovl_25EE90(u8 *o) {
    Path26F *p;
    f32 to[3];
    s16 k;

    FIELD(o, f32, 0x4C) = FIELD(o, f32, 0xC);
    FIELD(o, f32, 0x50) = FIELD(o, f32, 0x10);
    FIELD(o, f32, 0x54) = FIELD(o, f32, 0x14);
    k = FIELD(o, s16 *, 0x74)[FIELD(o, s32, 0x70)];
    p = (Path26F *)(o + 0x4C);
    if (k != -1) {
        to[0] = D_802209E0_ovl_25EE90[k].x;
        to[1] = 0.0f;
        to[2] = D_802209E0_ovl_25EE90[k].z;
    } else {
        func_80217C84_ovl_25EE90(FIELD(o, s32, 0x1C), to);
    }
    p->dir[0] = to[0] - FIELD(o, f32, 0xC);
    p->dir[1] = to[1] - FIELD(o, f32, 0x10);
    p->dir[2] = to[2] - FIELD(o, f32, 0x14);
    p->len = func_8020A3C8_ovl_25EE90(p->dir);
    func_8020A2E0_ovl_25EE90(p->dir, 1.0f / p->len, p->dir);
    p->t = 0;
    p->speed = p->len * 0.07692308f;
    if (k == -1) {
        p->len = p->len - 40.0f;
    }
}

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021BA3C_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021C044_ovl_25EE90);

void func_8021C360_ovl_25EE90(u16 msg, u8 *o) {
    s32 r;
    u32 i;
    u8 *e;

    if (msg == 0) {
        r = func_8020C9B0_ovl_25EE90(3);
        for (i = 0; i < FIELD(FIELD(o, u8 *, 0x50), u32, 4); i++) {
            if (FIELD(o, u8 **, 0x58)[i] != NULL) {
                FIELD(FIELD(o, u8 **, 0x58)[i], void *, 0) = func_8020FF6C_ovl_25EE90;
                e = FIELD(o, u8 **, 0x58)[i];
                FIELD(e, s32, 0x34) = r;
                FIELD(e, u8 *, 0x30) = D_80220980_ovl_25EE90;
                FIELD(e, s16, 0x3A) = 0;
                FIELD(e, s16, 0x38) = 0;
                FIELD(e, s16, 0x3E) = 0xF;
                FIELD(e, s16, 0x3C) = 0xF;
                FIELD(e, s16, 0x42) = 0;
                FIELD(e, s16, 0x40) = 0;
                FIELD(e, s16, 0x46) = 0xF;
                FIELD(e, s16, 0x44) = 0xF;
            }
        }
    } else {
        func_8021AC40_ovl_25EE90(msg, o);
    }
}

/* Starts a task for character c (with two extra parameters and a 16-bit argument) */
u8 *func_8021C440_ovl_25EE90(s16 a, s32 c, s32 b, s32 d) {
    u8 *t = func_8020DF00_ovl_25EE90(func_8021BA3C_ovl_25EE90);

    FIELD(t, s32, 0x3C) = c;
    FIELD(t, s32, 0x40) = b;
    FIELD(t, s32, 0x44) = d;
    FIELD(t, s32, 0x48) = a;
    func_801F7128(c);
    return t;
}

void func_8021C4C0_ovl_25EE90(s32 a) {
    D_80220F68_ovl_25EE90 = a;
    func_8020DF00_ovl_25EE90(func_8021D168_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021C4EC_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26F1E0", func_8021C62C_ovl_25EE90);

void func_80207CE4(u8 *p);
void func_8020E0B4_ovl_25EE90(s32 a, s32 b);
s32 func_801C8B84(u8 *u);
u8 *func_801C8FE8(s32 i);
void func_801F9DFC(void *a, u8 b, s32 c);
extern u8 D_800EB240[];
extern u8 D_80220F6A_ovl_25EE90;
extern void *D_80220F70_ovl_25EE90;
s32 func_8021B040_ovl_25EE90();
s32 func_8021A9C8_ovl_25EE90();
void func_8021D20C_ovl_25EE90(s16 a, s32 b, s32 c, s32 d);

s32 func_8021CE60_ovl_25EE90(u16 msg, u8 *o) {
    u8 *t;
    s32 c;
    s32 *g;

    switch (msg) {
        case 0x101:
            func_8020DFB8_ovl_25EE90();
            break;
        case 0x100:
            FIELD(o, s32, 4) = D_80220F68_ovl_25EE90;
            FIELD(o, s32, 8) = D_80220F6C_ovl_25EE90;
            func_8020DC80_ovl_25EE90(0x1000);
            break;
        case 0x1000:
            func_80207CE4(FIELD(o, u8 *, 4));
            func_8020E0B4_ovl_25EE90(-1, 0x1002);
            break;
        case 0x1001:
        case 0x1002:
            g = &D_80220F68_ovl_25EE90;
            if ((D_80220F68_ovl_25EE90 = (s16)func_801F7128(*FIELD(o, u8 *, 4))) != 0) {
                *(f32 *)&D_80220F6C_ovl_25EE90 = 228.0f;
            } else {
                *(f32 *)&D_80220F6C_ovl_25EE90 = -228.0f;
            }
            g[3] = 0;
            g[4] = 5;
            ((f32 *)g)[2] = 50.0f;
            t = func_8020DF00_ovl_25EE90(func_8021B040_ovl_25EE90);
            func_8020DCAC_ovl_25EE90(t, 0x1007);
            FIELD(o, u8 *, 0x18) = t;
            FIELD(o, void *, 0x20) = func_8021A998_ovl_25EE90(func_801C8B84(func_801C8FE8(*FIELD(o, u8 *, 4))), 20);
            FIELD(o, s32, 0x14) = 0;
            FIELD(o, s32, 0x10) = 0;
            FIELD(o, s32, 0xC) = 0;
            c = 0xF7;
            switch (FIELD(o, s16, 0)) {
                case 0x25:
                    c = 0xFA;
                    break;
                case 0x26:
                    c = 0xFD;
                    break;
            }
            func_801F9DFC(D_800EB240, *FIELD(o, u8 *, 4), c);
            func_8020DC80_ovl_25EE90(0x1003);
            break;
        case 0x1003:
            FIELD(o, s32, 0xC)++;
            if (func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x18), 0x1005) != 0) {
                func_8020DC80_ovl_25EE90(0x1004);
            }
            break;
        case 0x1004:
            D_80220F6A_ovl_25EE90 = *FIELD(o, u8 *, 4);
            D_80220F6C_ovl_25EE90 = FIELD(o, s32, 8);
            D_80220F70_ovl_25EE90 = func_8021D20C_ovl_25EE90;
            FIELD(o, void *, 0x1C) = func_8020DF00_ovl_25EE90(func_8021A9C8_ovl_25EE90);
            func_8020DC80_ovl_25EE90(0x1005);
            break;
        case 0x1005:
            if (func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x1C), 0x1003) != 0) {
                func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x1C), 0x101);
                func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x18), 0x1008);
                func_8020DC80_ovl_25EE90(0x1006);
            }
            break;
        case 0x1006:
            FIELD(o, s32, 0x10)++;
            if (FIELD(o, s32, 0x14) == 0 && FIELD(o, s32, 0x10) >= FIELD(o, s32, 0xC) - 20) {
                func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x20), 0x1003);
                FIELD(o, s32, 0x14) = 1;
            }
            if (func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x18), 0x1006) != 0) {
                func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x18), 0x101);
                func_8020DC80_ovl_25EE90(0x1007);
            }
            break;
        case 0x1007:
            func_8020DC80_ovl_25EE90(0x101);
            break;
    }
    return 0;
}

s32 func_8021D168_ovl_25EE90(u16 msg, u8 *o) {
    s32 r = 0;

    if (msg == 0x100) {
        u8 *e;

        FIELD(o, s32, 0x44) = D_80220F68_ovl_25EE90;
        e = func_80217460_ovl_25EE90(0x5D);
        FIELD(o, u8 *, 0x40) = e;
        FIELD(e, s32, 0x10) = FIELD(o, s32, 0x44);
        FIELD(FIELD(o, u8 *, 0x40), u16, 0xA) |= 0x2000;
        FIELD(o, s16, 0x4C) = 0x40;
        FIELD(o, s16, 0x4E) = 0x80;
        FIELD(o, s16, 0x50) = 0xFF;
        FIELD(o, s16, 0x52) = 0;
        func_8020DC80_ovl_25EE90(0x1000);
    } else {
        r = func_8021B500_ovl_25EE90(msg, o);
    }
    return r;
}

void func_8021D20C_ovl_25EE90(s16 a, s32 b, s32 c, s32 d) {
    Task26F *t = func_8020DF00_ovl_25EE90(func_8021C62C_ovl_25EE90);

    t->w3C = b;
    t->w40 = c;
    t->w44 = d;
    t->w48 = a;
}
