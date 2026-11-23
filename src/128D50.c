#include "common.h"

/* 128D50 */

typedef struct {
    u8 unk0;
    u8 flags;
    u8 rest[0x17];
} SquadRec; /* size 0x19 */

typedef struct {
    u8 unk0[4];
    u8 squad;
} MapUnit12;

extern SquadRec gSquads[];
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
f32 func_801D3910_ovl_101CE0(u8 *o);
void func_801D427C_ovl_101CE0(u8 *o);
void func_801B2B78_ovl_101CE0(u8 *o);
u8 func_801D4928_ovl_101CE0(void *sq);
u8 func_8016B088(u8 a, u8 b, u8 c, u8 d, u8 e);
/* --- end decls --- */

void func_801D4610_ovl_101CE0(u8 *o) {
    if (func_801D3910_ovl_101CE0(o) != -1.0f) {
        FIELD(o, s32, 0x88) = 90;
        o[0x20] = 0;
        FIELD(o, s32, 0x88) = 90;
        FIELD(o, u32, 0) |= 0x2000;
        FIELD(o, f32, 0x28) = FIELD(o, f32, 0x8);
        FIELD(o, f32, 0x2C) = FIELD(o, f32, 0xC);
        FIELD(o, f32, 0x30) = FIELD(o, f32, 0x10);
        FIELD(o, s32, 0x58) = FIELD(o, s32, 0x14);
        o[0x98] = o[0x91];
        FIELD(o, f32, 0x9C) = FIELD(o, f32, 0x18);
    }
}

void func_801D469C_ovl_101CE0(u8 *o) {
    if (FIELD(o, s32, 0x88) > 0) {
        func_801D427C_ovl_101CE0(o);
        FIELD(o, s32, 0x88)--;
    } else {
        FIELD(o, s32, 0x88) = 90;
        if (func_801D3910_ovl_101CE0(o) == -1.0f) {
            func_801B2B78_ovl_101CE0(o);
            o[0x20] = 1;
            FIELD(o, s32, 0x24) = 1;
            FIELD(o, u32, 0) &= ~4;
            FIELD(o, u32, 0) &= ~0x200;
        }
    }
}

void func_801D4738_ovl_101CE0(void) {
}

extern u8 D_801F0BD8_ovl_101CE0[];
extern u8 D_801F0C3C_ovl_101CE0;
typedef struct {
    u16 h0;
    u8 unk2[0x30];
    u8 b32;
    u8 unk33[5];
} Unit38;
typedef struct {
    u16 h0;
    u8 unk2[0x2C];
    u8 b2E;
    u8 unk2F[5];
} Enemy34;
extern Unit38 D_80193BD8[];
extern Enemy34 D_80195578[];
extern u8 D_801971F1[];
extern u8 D_801971F2[];
void bzero(void *p, s32 n);

/* Marks the unit ids (1-99) in use on each side: empty roster records and the members of every
 * deployed squad (squads 0-29 ally, 30-49 enemy) */
void func_801D4740_ovl_101CE0(void) {
    s32 i;
    u8 *sq;
    s32 j;

    bzero(D_801F0BD8_ovl_101CE0, 0xC8);
    D_801F0BD8_ovl_101CE0[0] |= 1;
    D_801F0C3C_ovl_101CE0 |= 1;
    for (i = 1; i < 100; i++) {
        if (D_80193BD8[i - 1].b32 == 0) {
            D_801F0BD8_ovl_101CE0[i] |= 1;
        }
        if (D_80193BD8[i].h0 == 0) {
            D_801F0BD8_ovl_101CE0[i] |= 1;
        }
    }
    for (i = 1; i < 100; i++) {
        if (D_80195578[i - 1].b2E == 0) {
            (&D_801F0C3C_ovl_101CE0)[i] |= 1;
        }
        if (D_80195578[i].h0 == 0) {
            (&D_801F0C3C_ovl_101CE0)[i] |= 1;
        }
    }
    j = 0;
    sq = D_801971F2;
    for (; j < 50; j++) {
        if (gSquads[j].flags & 1) {
            s32 k;

            if (j < 30) {
                for (k = 0; k < 5; k++) {
                    s32 id = sq[k];

                    if (id != 0) {
                        if (id < 100) {
                            D_801F0BD8_ovl_101CE0[id] |= 1;
                        }
                    }
                }
            } else {
                for (k = 0; k < 5; k++) {
                    s32 id = sq[k];

                    if (id != 0) {
                        if (id < 100) {
                            (&D_801F0C3C_ovl_101CE0)[id] |= 1;
                        }
                    }
                }
            }
        }
        sq += 25;
    }
}

extern u8 D_8018F481;
extern u8 D_80193BC0[][0x38];
extern u8 D_80187C40[][0x48];
extern u8 D_80195560[][0x34];

/* Squad type of s from its five members' class types (0 empty, 2 generic), 7 for the special
 * squads 31 and 32 on some stages */
u8 func_801D4928_ovl_101CE0(void *sq) {
    SquadRec *s = sq;
    u8 t[5];
    s32 i;

    if (s->unk0 == 31 && D_8018F481 != 8) {
        return 7;
    }
    switch (D_8018F481) {
    case 0x27:
    case 0x2D:
    case 0x2E:
    case 0x2F:
    case 0x3C:
        if (s->unk0 == 32) {
            return 7;
        }
    }
    for (i = 0; i < 5; i++) {
        u8 c = s->rest[i];

        if (c == 0) {
            t[i] = 0;
        } else if (c >= 100) {
            t[i] = 2;
        } else if (s->unk0 >= 31) {
            t[i] = D_80187C40[D_80195560[c][0x12]][0];
        } else {
            t[i] = D_80187C40[D_80193BC0[c][0x12]][0];
        }
    }
    return func_8016B088(t[0], t[1], t[2], t[3], t[4]);
}

u8 func_801D4A74_ovl_101CE0(u8 *sq) {
    u8 v[5];
    s32 i;

    for (i = 0; i < 5; i++) {
        u8 m = (sq + i)[2];

        if (m == 0xFF) {
            v[i] = 0;
        } else {
            v[i] = func_801D4928_ovl_101CE0(&gSquads[m]);
        }
    }
    return func_8016B088(v[0], v[1], v[2], v[3], v[4]);
}

INCLUDE_ASM("asm/nonmatchings/128D50", func_801D4B28_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/128D50", func_801D4F3C_ovl_101CE0);

void func_801D51D8_ovl_101CE0(MapUnit12 *u) {
    SquadRec *s = &gSquads[u->squad];

    s->flags &= ~4;
}

void func_801D5208_ovl_101CE0(MapUnit12 *u) {
    SquadRec *s = &gSquads[u->squad];

    s->flags |= 4;
}

INCLUDE_ASM("asm/nonmatchings/128D50", func_801D5238_ovl_101CE0);

void bzero(void *p, s32 n);
extern s16 D_8019532C[];
extern u8 D_80195480[];
extern u8 D_80195560[][0x34];
extern u32 *D_801F0CB0_ovl_101CE0[];
void func_801B2D2C_ovl_101CE0(u32 *o);
void HFree(void *p);

extern s32 D_801F367C_ovl_101CE0;
extern u8 gLegions[][11];

/* Clears the enemy side: map units, enemy characters 1-98, generic enemies, squads 30-49 and the
 * enemy legions (flag 0x80) */
void func_801D5910_ovl_101CE0(void) {
    s32 i;

    for (i = 0; i < D_801F367C_ovl_101CE0; i++) {
        u32 *o = D_801F0CB0_ovl_101CE0[i];

        func_801B2D2C_ovl_101CE0(o);
        if (FIELD(o, void *, 0xA8) != NULL) {
            HFree(FIELD(o, void *, 0xA8));
        }
        bzero(o, 0xC0);
    }
    for (i = 1; i < 99; i++) {
        bzero(D_80195560[i], 0x34);
        D_80195560[i][0x33] &= 0x7F;
    }
    for (i = 119; i >= 0; i--) {
        D_8019532C[100 + i] = 0;
    }
    for (i = 30; i < 50; i++) {
        bzero(&gSquads[i], 25);
    }
    for (i = 0; i < 10; i++) {
        if (gLegions[i][1] & 0x80) {
            bzero(gLegions[i], 11);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/128D50", func_801D5A60_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/128D50", func_801D5E34_ovl_101CE0);


/* Disbands squad k: frees its members (generic ids 100+, else clears the character), clears the
 * record and hides its map unit */
void func_801D60E8_ovl_101CE0(s32 k) {
    SquadRec *s = &gSquads[k];
    u32 *o = D_801F0CB0_ovl_101CE0[k];
    s32 i;

    if (s->flags & 1) {
        for (i = 0; i < 5; i++) {
            s32 c = s->rest[i];

            if (c != 0) {
                if (c >= 100) {
                    D_8019532C[c] = 0;
                    D_80195480[c] = 0;
                } else {
                    bzero(D_80195560[c], 0x34);
                }
            }
        }
        bzero(s, 0x19);
    }
    s->flags = 0x80;
    func_801B2D2C_ovl_101CE0(o);
    *o &= ~1;
    *o &= ~0x10;
    *o &= ~8;
}

INCLUDE_ASM("asm/nonmatchings/128D50", func_801D6218_ovl_101CE0);
