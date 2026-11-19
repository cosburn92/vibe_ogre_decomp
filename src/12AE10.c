#include "common.h"

/* ovl_101CE0 (12AE10): map/stage logic (chaos frame, inventory) */

/* --- decls --- */
typedef struct {
    /* 0x00 */ u16 flags; /* 2: liberated, 4: enemy-held */
    /* 0x02 */ u8 pref;
    /* 0x03 */ u8 unk03[0x21];
} LocationRec; /* size 0x24 */

extern LocationRec D_801951CC[];
extern u8 gChaosFrame;
extern u8 D_8018F481; /* current stage id */
extern u8 gStageTable[][12];
extern u8 D_801939CC;
extern u16 D_801F1060_ovl_101CE0[];
extern s32 D_801F0DE0_ovl_101CE0;
extern s32 D_801F3610_ovl_101CE0;
extern u8 D_801F365D_ovl_101CE0;

void bzero(void *p, s32 n);
s32 func_80186210(s32 flag);
s32 func_8016FEF4(s32 flag);
void func_801B2B78_ovl_101CE0(u32 *unit);
#include "tables.h"

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 flags;
    /* 0x02 */ u8 members[5];
    /* 0x07 */ u8 pos[5];
    /* 0x0C */ u8 harmony;
    /* 0x0D */ u8 items[10];
    /* 0x17 */ u8 strategy;
    /* 0x18 */ u8 legion;
} SquadRec; /* size 0x19 */

typedef struct {
    /* 0x00 */ Character c;
    /* 0x34 */ u8 unk34[4];
} PlayerChar; /* size 0x38 */

/* Unit on the map */
typedef struct {
    /* 0x00 */ u32 flags; /* 0x08: player side */
    /* 0x04 */ u8 squad;
    /* 0x05 */ u8 unk05[3];
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 y;
    /* 0x10 */ f32 z;
} MapUnit;

typedef struct {
    f32 x, y, z;
} Vec3f;

extern u8 gLegions[][11]; /* +0 number, +1 flags (1 used, 0x80 enemy), +2..6 squads, +8 formation */
extern SquadRec gSquads[];
extern PlayerChar D_80193BC0[];
extern Character D_80195560[];
extern u32 *D_801F0CB0_ovl_101CE0[];

f32 func_8009C780(f32 x, f32 z);
s32 func_801DA228_ovl_101CE0(MapUnit *u);
void func_801DA340_ovl_101CE0(s32 a, Vec3f *out);

#ifdef NON_MATCHING
/* Block order differs: the target puts the mode 1-8 copy right after the dispatch. */
void func_801D66D0_ovl_101CE0(u8 *dst, u8 *src, u8 mode) {
    switch (mode) {
        case 0:
            dst[0] = src[2];
            dst[2] = src[4];
            if (dst[2] == 0xFF) {
                dst[1] = 0xFF;
                dst[2] = src[3];
            } else {
                dst[1] = src[3];
            }
            dst[3] = src[5];
            if (dst[3] == 0xFF) {
                dst[4] = 0xFF;
                dst[3] = src[6];
            } else {
                dst[4] = src[6];
            }
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            dst[0] = src[2];
            dst[1] = src[3];
            dst[2] = src[4];
            dst[3] = src[5];
            dst[4] = src[6];
            break;
        default:
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/12AE10", func_801D66D0_ovl_101CE0);
#endif

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801D677C_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801D6A84_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801D6D00_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801D7524_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801D8048_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801D8A30_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801D8FBC_ovl_101CE0);

/* Whether the unit's squad leader is alive */
s32 func_801D92D0_ovl_101CE0(MapUnit *u) {
    u8 sq = u->squad;
    s32 leader = gSquads[sq].members[0];
    u16 hp;

    if (leader == 0 || leader >= 100) {
        return 0;
    }
    if (sq < 30) {
        hp = D_80193BC0[leader].c.hp;
    } else {
        hp = D_80195560[leader].hp;
    }
    return hp != 0;
}

s32 func_801D935C_ovl_101CE0(MapUnit *u) {
    u8 sq = u->squad;
    s32 leader = gSquads[sq].members[0];
    u8 st;

    if (leader == 0 || leader >= 100) {
        return 0;
    }
    if (sq < 30) {
        st = D_80193BC0[leader].c.status & 4;
    } else {
        st = D_80195560[leader].status & 4;
    }
    return st != 0;
}

s32 func_801D93EC_ovl_101CE0(MapUnit *u) {
    u8 *legion = gLegions[func_801DA228_ovl_101CE0(u)];
    s32 i;

    for (i = 0; i < 5; i++) {
        u8 s = (legion + i)[2];

        if (s != 0xFF && (*D_801F0CB0_ovl_101CE0[s] & 0x20000)) {
            return 1;
        }
    }
    return 0;
}

/* Two-digit number, blank-padded */
#ifdef NON_MATCHING
/* The pointer increment is scheduled differently. */
void func_801D9474_ovl_101CE0(s32 n, char *buf) {
    s32 tens = n / 10;
    s32 ones = n - tens * 10;

    *buf++ = tens ? tens + '0' : ' ';
    buf[0] = ones + '0';
    buf[1] = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/12AE10", func_801D9474_ovl_101CE0);
#endif

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801D94CC_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801D99EC_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DA0A8_ovl_101CE0);

/* Number of squads in the unit's legion */
s32 func_801DA1AC_ovl_101CE0(MapUnit *u) {
    s32 n;
    u8 *p = &gLegions[func_801DA228_ovl_101CE0(u)][2];
    s32 i;

    n = 0;
    for (i = 0; i < 5; i++) {
        n += p[i] != 0xFF;
    }
    return n;
}

s32 func_801DA210_ovl_101CE0(s32 a) {
    if (a >= 50) {
        return -1;
    }
    return a;
}

/* Legion containing the unit's squad, or -1 */
#ifdef NON_MATCHING
/* Prologue order differs (the squad byte is loaded first). */
s32 func_801DA228_ovl_101CE0(MapUnit *u) {
    u8 sq = u->squad;
    u8 *l = gLegions[0];
    s32 i;
    s32 j;

    for (i = 0; i < 10; i++, l += 11) {
        u8 fl = l[1];

        if (!(fl & 1)) {
            continue;
        }
        if (u->flags & 8) {
            if (fl & 0x80) {
                continue;
            }
        } else if (!(fl & 0x80)) {
            continue;
        }
        for (j = 0; j < 5; j++) {
            if ((l + j)[2] == sq) {
                return i;
            }
        }
    }
    return -1;
}
#else
INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DA228_ovl_101CE0);
#endif

/* Slot of the unit's squad within its legion, or -1 */
#ifdef NON_MATCHING
/* Prologue order differs (the squad byte is loaded first). */
s32 func_801DA2B4_ovl_101CE0(MapUnit *u) {
    u8 *l;
    u8 sq = u->squad;
    s32 i;
    s32 j;

    for (i = 0, l = gLegions[0]; i < 10; i++, l += 11) {
        u8 fl = l[1];

        if (!(fl & 1)) {
            continue;
        }
        if (u->flags & 8) {
            if (fl & 0x80) {
                continue;
            }
        } else if (!(fl & 0x80)) {
            continue;
        }
        for (j = 0; j < 5; j++) {
            if ((l + j)[2] == sq) {
                return j;
            }
        }
    }
    return -1;
}
#else
INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DA2B4_ovl_101CE0);
#endif

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DA340_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DA478_ovl_101CE0);

s32 func_801DA52C_ovl_101CE0(MapUnit *u) {
    Vec3f pos;
    s32 ret;

    func_801DA340_ovl_101CE0(-1, &pos);
    ret = 0;
    if (func_8009C780(pos.x - u->x, pos.z - u->z) < 0.5) {
        ret = 1;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DA59C_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DA8D0_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DAA00_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DADF0_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DB180_ovl_101CE0);

typedef struct {
    u8 unk00[0xA8];
    s32 *ids;
} DB424Arg;

#ifdef NON_MATCHING
/* The table address is hoisted above the search loop; the target computes it after. */
s32 func_801DB424_ovl_101CE0(DB424Arg *a, s32 id) {
    s32 *p;

    if (a->ids == NULL) {
        return 0;
    }
    for (p = a->ids; *p != -1; p++) {
        if (*p == id) {
            return (*D_801F0CB0_ovl_101CE0[id] & 0x31) == 0x31;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DB424_ovl_101CE0);
#endif

INCLUDE_ASM("asm/nonmatchings/12AE10", ChaosFrameOnLiberate);

void ChaosFrameOnCapture(s32 loc) {
    s32 v;

    if (D_801951CC[loc].pref != 0xFF) {
        v = gChaosFrame - 2;
        if (v > 100) {
            v = 100;
        } else if (v < 0) {
            v = 0;
        }
        gChaosFrame = v;
    }
}

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DB718_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DBE74_ovl_101CE0);

s32 func_801DC054_ovl_101CE0(void) {
    u8 v = D_8018F481;
    s32 r = (v == 0x3F || v == 0x41);

    if (v == 0x40 || v == 0x42) {
        r = 1;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DC094_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DC4EC_ovl_101CE0);

void LocationGetStageValue(u16 loc, s8 *value, u8 *side) {
    u16 fl = D_801951CC[loc].flags;

    if (fl & 2) {
        *value = gStageTable[D_8018F481][3];
        if (func_80186210(0x11)) {
            if (func_8016FEF4(0x6B)) {
                *value = 1;
            } else {
                *value = 4;
            }
        }
        *side = 1;
    } else if (fl & 4) {
        *value = gStageTable[D_8018F481][4];
        *side = 2;
    } else {
        *value = -1;
        *side = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/12AE10", InventoryAdd);

void func_801DC910_ovl_101CE0(void) {
    s32 i;

    for (i = 0; i < 50; i++) {
        func_801B2B78_ovl_101CE0(D_801F0CB0_ovl_101CE0[i]);
    }
}

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DC95C_ovl_101CE0);

/* Packs the squad's items to the front */
void func_801DCC48_ovl_101CE0(SquadRec *sq) {
    u8 tmp[10];
    u8 *d;
    s32 i;

    bzero(tmp, 10);
    for (i = 0, d = tmp; i < 10; i++) {
        if (sq->items[i] != 0) {
            *d++ = sq->items[i];
        }
    }
    for (i = 0; i < 10; i++) {
        sq->items[i] = tmp[i];
    }
}

void func_801DCCC4_ovl_101CE0(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (D_801F1060_ovl_101CE0[i] == 0 || --D_801F1060_ovl_101CE0[i] == 0) {
            D_801939CC |= 1 << i;
        } else {
            D_801939CC &= ~(1 << i);
        }
    }
}

/* Whether the unit's squad carries this item */
s32 func_801DCD40_ovl_101CE0(MapUnit *u, u8 item) {
    u8 *p = gSquads[u->squad].items;
    s32 i;

    for (i = 0; i < 10; i++) {
        if (p[i] == item) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DCD90_ovl_101CE0);

s32 func_801DCEE4_ovl_101CE0(void) {
    s32 r = D_801F0DE0_ovl_101CE0 == 0;

    if (D_801F3610_ovl_101CE0 != 0) {
        r = 0;
    }
    if (D_801F365D_ovl_101CE0 & 2) {
        r = 0;
    }
    return r;
}

s32 func_801DCF20_ovl_101CE0(void) {
    if (func_8016FEF4(5)) {
        return 1;
    }
    if (func_8016FEF4(6)) {
        return 1;
    }
    if (func_8016FEF4(7)) {
        return 1;
    }
    if (func_8016FEF4(8)) {
        return 1;
    }
    if (func_8016FEF4(9)) {
        return 1;
    }
    if (func_8016FEF4(10)) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DCF90_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DD0E8_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DD208_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DD244_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DD280_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DD2B0_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DD2D4_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DD410_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DD530_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DD584_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DDDA8_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DDDF8_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DE440_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DE57C_ovl_101CE0);
