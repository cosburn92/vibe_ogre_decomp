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
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 unk18[0x34];
    /* 0x4C */ f32 savedX;
    /* 0x50 */ f32 savedY;
    /* 0x54 */ f32 savedZ;
    /* 0x58 */ u8 unk58[0xC];
    /* 0x64 */ s32 unk64;
    /* 0x68 */ u8 unk68[0x18];
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ u8 unk88[9];
    /* 0x91 */ u8 unk91;
    /* 0x92 */ u8 unk92;
    /* 0x93 */ u8 unk93[0x15];
    /* 0xA8 */ s32 *ids;
    /* 0xAC */ u8 unkAC[0xE];
    /* 0xBA */ u8 unkBA;
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
extern s32 D_801F3670_ovl_101CE0;
extern u8 D_801EB2D4_ovl_101CE0;
extern u8 D_801EB2D5_ovl_101CE0;
extern s32 D_801EB280_ovl_101CE0;
extern s32 D_801EB284_ovl_101CE0;
extern s32 D_801EB288_ovl_101CE0;
extern void *D_801EB28C_ovl_101CE0;

void func_80079618();
void func_8017C384(s32 h);
void *HFree(void *p);
void func_801B2D2C_ovl_101CE0(MapUnit *u);
typedef struct {
    /* 0x0 */ u16 id;
    /* 0x2 */ u8 equipped;
    /* 0x3 */ u8 count;
} StockEntry;

extern StockEntry D_80196B00[]; /* item stock, 0x116 entries */
extern StockEntry D_80193AC0[]; /* consumables, 0x28 entries */

s32 guRandom(void);
void osSyncPrintf(const char *fmt, ...);
extern u8 D_800E7A90[]; /* pointer table; +0x29 scene slot, +0x35 map data slot */
extern s32 D_801F1070_ovl_101CE0; /* location count */
extern MapUnit *D_801F0D28_ovl_101CE0;

f32 func_801A63FC(s32 slot, f32 x, f32 z);
extern f32 D_801F0D98_ovl_101CE0;
extern f32 D_801F0D9C_ovl_101CE0;
extern f32 D_801F0DA0_ovl_101CE0;
extern f32 D_801F0DA4_ovl_101CE0;
/* --- end decls --- */

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
inline s32 func_801D92D0_ovl_101CE0(MapUnit *u) {
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

inline s32 func_801D935C_ovl_101CE0(MapUnit *u) {
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

/* First squad member without status bit 2 (else the first member) */
Character *func_801DA0A8_ovl_101CE0(MapUnit *u) {
    SquadRec *sq = &gSquads[u->squad];
    Character *c;
    s32 i;

    for (i = 0; i < 5; i++) {
        u8 m = sq->members[i];

        if (m < 100) {
            if (u->squad < 30) {
                c = &D_80193BC0[m].c;
            } else {
                c = &D_80195560[m];
            }
            if (c->status & 2) {
                break;
            }
        }
    }
    if (i >= 5) {
        i = 0;
    }
    if (u->squad >= 30) {
        return &D_80195560[sq->members[i]];
    }
    return &D_80193BC0[sq->members[i]].c;
}

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

/* Map position of a location (-1: the first one with flag 0x10); y from the terrain */
#ifdef NON_MATCHING
/* Stage test shape differs: the target uses range compares for 0x2F-0x30 and 0x3C-0x3D, each paired with loc == 0. */
void func_801DA340_ovl_101CE0(s32 loc, Vec3f *out) {
    s32 i;
    f32 *p;
    f32 x;
    f32 z;
    f32 *o = (f32 *)out;

    if (loc == -1) {
        for (i = 0; i < D_801F1070_ovl_101CE0; i++) {
            if (D_801951CC[i].flags & 0x10) {
                break;
            }
        }
    } else {
        i = loc;
    }
    p = (f32 *)(((u8 **)D_800E7A90)[D_800E7A90[0x35]] + 0x1C) + i * 2;
    x = p[0];
    z = p[1];
    if ((D_8018F481 == 0x27 || D_8018F481 == 0x2F || D_8018F481 == 0x30 || D_8018F481 == 0x3C || D_8018F481 == 0x3D ||
         D_8018F481 == 0x33) && loc == 0) {
        x = D_801F0D28_ovl_101CE0->x;
        z = D_801F0D28_ovl_101CE0->z;
    }
    *o++ = x;
    *o = func_801A63FC(D_800E7A90[0x29], x, z);
    o[1] = z;
}
#else
INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DA340_ovl_101CE0);
#endif

/* Map cell (gx, gz) in 1/256 steps across the map bounds to a world position, with the ground height */
void func_801DA478_ovl_101CE0(s32 gx, s32 gz, f32 *o) {
    f32 v[3];

    v[0] = D_801F0D98_ovl_101CE0 + (D_801F0DA0_ovl_101CE0 - D_801F0D98_ovl_101CE0) * gx / 256.0f;
    v[2] = D_801F0D9C_ovl_101CE0 + (D_801F0DA4_ovl_101CE0 - D_801F0D9C_ovl_101CE0) * gz / 256.0f;
    *o++ = v[0];
    *o = func_801A63FC(D_800E7A90[0x29], v[0], v[2]);
    o[1] = v[2];
}

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

extern u16 D_80190EBC[];
extern u8 D_80191010[];
extern u16 D_8019532C[];
extern u8 D_80195480[];

/* Whether squad sq is wiped out: no member that is alive and not petrified (members 100+ are
 * the special units, kept in separate hp/status tables) */
s32 func_801DA8D0_ovl_101CE0(s32 sq) {
    s32 i;

    for (i = 0; i < 5; i++) {
        s32 m = gSquads[sq].members[i];

        if (m == 0) {
            continue;
        }
        if (m >= 100) {
            if (sq >= 30) {
                if (D_8019532C[m] != 0 && !(D_80195480[m] & 4)) {
                    return 0;
                }
            } else {
                if (D_80190EBC[m] != 0 && !(D_80191010[m] & 4)) {
                    return 0;
                }
            }
        } else if (sq >= 30) {
            if (D_80195560[m].hp != 0 && !(D_80195560[m].status & 4)) {
                return 0;
            }
        } else {
            if (D_80193BC0[m].c.hp != 0 && !(D_80193BC0[m].c.status & 4)) {
                return 0;
            }
        }
    }
    return 1;
}

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

/* (squad, location): adjusts gChaosFrame by -5..+2 from how far the squad's mean alignment is from
 * the town's preference (plus 40 when bit 7 of the preference is set) and a random 0-7.
 * Returns whether the score was 31 or more. */
#ifdef NON_MATCHING
/* Logic is complete; loop strength reduction and register use differ. */
s32 ChaosFrameOnLiberate(s32 squad, s32 loc) {
    u16 pref = D_801951CC[loc].pref;
    u16 bonus;
    u16 sum;
    u16 avg;
    u16 score;
    u8 cnt;
    s32 r;
    s32 d;
    s32 delta;
    s32 v;
    u8 *m;

    if (pref == 0xFF || squad >= 30) {
        return 0;
    }
    bonus = (pref >> 7) ? 40 : 0;
    pref &= 0x7F;
    sum = 0;
    cnt = 0;
    for (m = gSquads[squad].members; m < gSquads[squad].members + 5; m++) {
        if (*m == 0 || *m >= 99) {
            continue;
        }
        if (squad < 30) {
            sum += D_80193BC0[*m].c.alignment;
        } else {
            sum += D_80195560[*m].alignment;
        }
        cnt++;
    }
    if (cnt == 0) {
        avg = 50;
    } else {
        avg = sum / cnt;
    }
    r = guRandom() % 8;
    d = avg - pref;
    if (d <= 0) {
        d = pref - avg;
    }
    score = d + r + bonus;
    if (score > 140) {
        delta = -5;
    } else if (score > 110) {
        delta = -4;
    } else if (score > 80) {
        delta = -3;
    } else if (score > 50) {
        delta = -2;
    } else if (score > 30) {
        delta = -1;
    } else if (score > 15) {
        delta = 0;
    } else if (score > 5) {
        delta = 1;
    } else {
        delta = 2;
    }
    v = gChaosFrame + delta;
    if (v > 100) {
        v = 100;
    } else if (v < 0) {
        v = 0;
    }
    gChaosFrame = v;
    return score > 30;
}
#else
INCLUDE_ASM("asm/nonmatchings/12AE10", ChaosFrameOnLiberate);
#endif

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

s32 func_801DBE74_ovl_101CE0(MapUnit *u) {
    s32 r = 0;

    if (u->flags & 0x40) {
        return 0;
    }
    if (!func_801D92D0_ovl_101CE0(u) || func_801D935C_ovl_101CE0(u)) {
        func_801B2D2C_ovl_101CE0(u);
        r = 1;
        u->flags = (u->flags & ~0x2000) | 0x800000;
        u->unk92 = 0;
        u->unk91 = 0;
        u->unk84 = -1;
        u->unk80 = -1;
        u->unk92 = 2;
        u->unkBA = 1;
        u->savedX = u->x;
        u->savedY = u->y;
        u->savedZ = u->z;
        u->unk64 = u->unk14;
        u->flags &= ~0x08000000;
        u->flags &= ~0x00800000;
    }
    return r;
}

s32 func_801DC054_ovl_101CE0(void) {
    u8 v = D_8018F481;
    s32 r = (v == 0x3F || v == 0x41);

    if (v == 0x40 || v == 0x42) {
        r = 1;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DC094_ovl_101CE0);

/* Index of the location the player's leader stands on (-1 if none); fixed 0 or 6 on some maps */
/* Index of the location the player's leader stands on (-1 if none); fixed 0 or 6 on some maps */
s32 func_801DC4EC_ovl_101CE0(void) {
    MapUnit *u;
    Vec3f p;
    s32 i;

    if (D_8018F481 == 0x27 || (D_8018F481 >= 0x2F && D_8018F481 <= 0x30) || (D_8018F481 >= 0x3C && D_8018F481 <= 0x3D) || D_8018F481 == 0x33) {
        return 0;
    }
    if (D_8018F481 == 8) {
        return 6;
    }
    u = D_801F0D28_ovl_101CE0;
    for (i = 0; i < D_801F1070_ovl_101CE0; i++) {
        f32 d;

        func_801DA340_ovl_101CE0(i, &p);
        d = u->x - p.x;
        if (!(d > 0.0f)) {
            d = -d;
        }
        if (d < 0.01) {
            d = u->z - p.z;
            if (!(d > 0.0f)) {
                d = -d;
            }
            if (d < 0.01) {
                break;
            }
        }
    }
    if (i != D_801F1070_ovl_101CE0) {
        return i;
    }
    return -1;
}

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

/* v with bit 15: item v & 0x7FFF into the item stock, else consumable v (max 99 each) */
#ifdef NON_MATCHING
/* Logic is complete; the target walks the count bytes with a pointer and indexes the ids. */
void InventoryAdd(u16 v, u8 flag) {
    u16 id = v & 0x7FFF;
    s32 i;

    if (v & 0x8000) {
        for (i = 0; i < 0x116; i++) {
            if (D_80196B00[i].id == id) {
                if (++D_80196B00[i].count >= 100) {
                    D_80196B00[i].count = 99;
                }
                break;
            }
        }
        if (i == 0x116) {
            for (i = 0; i < 0x116; i++) {
                if (D_80196B00[i].id == 0) {
                    D_80196B00[i].id = id;
                    D_80196B00[i].count = 1;
                    break;
                }
            }
            if (i == 0x116) {
                osSyncPrintf("no space to put item[%d]\n", id);
            }
        }
    } else {
        for (i = 0; i < 0x28; i++) {
            if (D_80193AC0[i].id == id) {
                D_80193AC0[i].count++;
                if (flag) {
                    D_80193AC0[i].equipped++;
                }
                if (D_80193AC0[i].count >= 100) {
                    D_80193AC0[i].count = 99;
                }
                if (D_80193AC0[i].count < D_80193AC0[i].equipped) {
                    D_80193AC0[i].equipped = D_80193AC0[i].count;
                }
                break;
            }
        }
        if (i == 0x28) {
            for (i = 0; i < 0x28; i++) {
                if (D_80193AC0[i].id == 0) {
                    D_80193AC0[i].id = id;
                    D_80193AC0[i].count = 1;
                    if (flag) {
                        D_80193AC0[i].equipped = 1;
                    }
                    break;
                }
            }
            if (i == 0x28) {
                osSyncPrintf("no space to put item[%d]\n", id);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/12AE10", InventoryAdd);
#endif

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

/* Whether any living member (1-99) of unit u's squad carries item id, equipped or as its class
 * default */
s32 func_801DCD90_ovl_101CE0(MapUnit *u, u16 id) {
    u8 sq;
    s32 player;
    u8 *m;
    u8 *end;

    if (id == 0) {
        return 0;
    found:
        return 1;
    }
    sq = u->squad;
    player = sq < 30;
    m = gSquads[sq].members;
    end = m + 5;
    do {
        s32 k = *m;
        Character *c;
        ClassData *cls;

        if ((k >= 100) | (k == 0)) {
            goto next;
        }
        if (player) {
            c = &D_80193BC0[k].c;
        } else {
            c = &D_80195560[k];
        }
        if (c->items[0] == id || c->items[1] == id || c->items[2] == id || c->items[3] == id) {
            goto found;
        }
        if (gClassTable[c->cls].baseClass != 0) {
            cls = &gClassTable[c->baseCls];
        } else {
            cls = &gClassTable[c->cls];
        }
        if (cls->defaultItems[0] == id || cls->defaultItems[1] == id || cls->defaultItems[2] == id ||
            cls->defaultItems[3] == id) {
            goto found;
        }
    next:
        m++;
    } while ((s32)m < (s32)end);
    return 0;
}

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

/* Icon index for the squad leader: special classes 4-24, else by alignment (3 high, 2 middle)
 * or gender (1 for gender 1, 0 otherwise) */
s32 func_801DCF90_ovl_101CE0(MapUnit *u) {
    s32 leader = gSquads[u->squad].members[0];
    u8 cls = D_80193BC0[leader].c.cls;
    u8 align = D_80193BC0[leader].c.alignment;
    u8 gender = D_80193BC0[leader].c.gender;
    s32 r;

    switch (cls) {
        case 81:
        case 82:
        case 83:
            r = 4;
            break;
        case 163:
            r = 5;
            break;
        case 84:
        case 85:
            r = 6;
            break;
        case 86:
        case 87:
            r = 7;
            break;
        case 88:
            r = 8;
            break;
        case 89:
            r = 9;
            break;
        case 90:
            r = 10;
            break;
        case 91:
            r = 11;
            break;
        case 92:
            r = 12;
            break;
        case 93:
            r = 13;
            break;
        case 94:
            r = 14;
            break;
        case 95:
        case 96:
            r = 15;
            break;
        case 97:
            r = 16;
            break;
        case 117:
            r = 17;
            break;
        case 118:
            r = 18;
            break;
        case 119:
            r = 19;
            break;
        case 120:
            r = 20;
            break;
        case 121:
            r = 21;
            break;
        case 122:
            r = 22;
            break;
        case 123:
            r = 23;
            break;
        case 124:
            r = 24;
            break;
        default:
            r = 0;
            break;
    }
    if (r == 0) {
        if (align >= 66) {
            r = 3;
        } else if (align >= 35) {
            r = 2;
        } else {
            r = gender == 1;
        }
    }
    return r;
}

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern f32 D_801F3A38_ovl_101CE0;
s32 func_801DD244_ovl_101CE0();

/* While flag 1 is set, looks for a location within a quarter of D_801F3A38 of the unit; on finding
 * one, records it at 0x7C and swaps flag 1 for 0x40 */
void func_801DD0E8_ovl_101CE0(u8 *u) {
    Vec3f p;
    s32 i;

    if (FIELD(u, s32, 0x78) & 1) {
        for (i = 0; i < D_801F1070_ovl_101CE0; i++) {
            if (func_801DD244_ovl_101CE0() == 0 && !(D_801951CC[i].flags & 2)) {
                f32 dx, dz;

                func_801DA340_ovl_101CE0(i, &p);
                dx = FIELD(u, f32, 8) - p.x;
                dz = FIELD(u, f32, 0x10) - p.z;
                if (dx * dx + dz * dz < (D_801F3A38_ovl_101CE0 * 0.25) * (D_801F3A38_ovl_101CE0 * 0.25)) {
                    FIELD(u, s32, 0x7C) = i;
                    FIELD(u, s32, 0x78) = (FIELD(u, s32, 0x78) & ~1) | 0x40;
                    return;
                }
            }
        }
    }
}

s32 func_801DD208_ovl_101CE0(void) {
    s32 r = 0;

    switch (D_8018F481) {
        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x2A:
        case 0x2B:
        case 0x2C:
        case 0x39:
        case 0x3A:
            r = 1;
            break;
    }
    return r;
}

s32 func_801DD244_ovl_101CE0(void) {
    s32 r = 0;

    switch (D_8018F481) {
        case 0x27:
        case 0x2F:
        case 0x30:
        case 0x33:
        case 0x3C:
        case 0x3D:
            r = 1;
            break;
    }
    return r;
}

s32 func_801DD280_ovl_101CE0(u32 a) {
    s32 r = 0;

    switch (a) {
        case 0:
        case 2:
        case 8:
        case 16:
        case 17:
        case 18:
        case 19:
        case 23:
            r = 1;
            break;
    }
    return r;
}

#ifdef NON_MATCHING
/* The flags temporary lands in v0 instead of v1. */
s32 func_801DD2B0_ovl_101CE0(MapUnit *u) {
    if (u->flags & 8) {
        return u->squad >= 30;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DD2B0_ovl_101CE0);
#endif

#define UNIT_TOWN(u) (*(s32 *)&(u)->unk68[0xC]) /* town index at +0x74, -1 when none */

/* Starts unit u's move (a = kind, b = mode); mode 0 onto an owned town keeps a return point */
#ifdef NON_MATCHING
/* flag masks folded into one constant, params re-masked; original keeps two masks and unmasked a/b */
void func_801DD2D4_ovl_101CE0(MapUnit *u, u8 a, u8 b) {
    u8 v;

    if (u->flags & 0x40) {
        return;
    }
    func_801B2D2C_ovl_101CE0(u);
    u->unk92 = 0;
    u->unk91 = 0;
    u->unk84 = -1;
    u->unk80 = -1;
    u->flags = u->flags & ~0x2000 & ~0x800000;
    if (b == 0 && UNIT_TOWN(u) != -1 && (D_801951CC[UNIT_TOWN(u)].flags & 2)) {
        u->flags |= 0x800000;
        u->savedX = u->x;
        u->savedY = u->y;
        u->savedZ = u->z;
        u->unk64 = u->unk14;
    } else {
        u->unk92 = b;
    }
    u->unk91 = a;
    if (a == 1 && b == 1) {
        v = 1;
    } else if (a == 2 && b == 2) {
        v = 2;
    } else if (a == 0 && b == 0) {
        v = 0;
    } else {
        v = 3;
    }
    u->unk88[8] = v;
}
#else
INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DD2D4_ovl_101CE0);
#endif

u16 func_8016B6FC(u16 id);

/* Adds one of item v to the stock: into its existing slot (func_8016B6FC), else the first
 * free one; both counts are capped at 99 */
void func_801DD410_ovl_101CE0(u16 v) {
    s32 i;

    if (v != 0) {
        i = func_8016B6FC(v);
        if (i == 0x1FF) {
            for (i = 0; i < 0x116; i++) {
                if (D_80196B00[i].id == 0) {
                    D_80196B00[i].id = v;
                    D_80196B00[i].equipped++;
                    D_80196B00[i].count++;
                    break;
                }
            }
        } else {
            D_80196B00[i].equipped++;
            D_80196B00[i].count++;
        }
        if (D_80196B00[i].count >= 100) {
            D_80196B00[i].count = 99;
        }
        if (D_80196B00[i].equipped >= 100) {
            D_80196B00[i].equipped = 99;
        }
    }
}

void func_801DD530_ovl_101CE0(void) {
    if (D_801F3670_ovl_101CE0 != 0) {
        func_80079618(0x218E9B4, D_801EB2D4_ovl_101CE0, -0x11);
        D_801F3670_ovl_101CE0 = 0;
        D_801EB2D4_ovl_101CE0 = 0xFF;
        D_801EB2D5_ovl_101CE0 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DD584_ovl_101CE0);

void func_801DDDA8_ovl_101CE0(void) {
    s32 *p = &D_801EB280_ovl_101CE0;

    if (*p != 0) {
        func_8017C384(*p);
        *p = 0;
    }
    func_8017C384(D_801EB284_ovl_101CE0);
    D_801EB284_ovl_101CE0 = 0;
}

INCLUDE_ASM("asm/nonmatchings/12AE10", func_801DDDF8_ovl_101CE0);

void *LoadChunk(s32 id);
void *HMalloc(s32 size);
void _bcopy(void *src, void *dst, s32 n);
s32 LoadAsset(u32 handle, ...);
s32 func_8017BFB0(s32 a, s32 b, void *func, s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3);
void func_8020CDA0(s32 se);
extern s16 D_801F0B50_ovl_101CE0;
void func_801DDDF8_ovl_101CE0();

/* Opens the window for page k: with bit 15 set, builds a palette from the shared base and the
 * page's own 0x100 bytes */
void func_801DE440_ovl_101CE0(s16 k) {
    s32 *p = &D_801EB288_ovl_101CE0;

    *p = 0;
    D_801EB28C_ovl_101CE0 = NULL;
    if (k & 0x8000) {
        u8 *src = LoadChunk(0x01DEE82C);
        u8 *pal = HMalloc(0x300);

        _bcopy(src, pal, 0x200);
        _bcopy(src + (((k & 0x7FFF) << 8) + 0x100), pal + 0x200, 0x100);
        HFree(src);
        D_801EB28C_ovl_101CE0 = pal;
    }
    *p = LoadAsset(0x0218E9B4, 0x15, -3, 6);
    D_801EB284_ovl_101CE0 = func_8017BFB0(0, 0, func_801DDDF8_ovl_101CE0, 0x9E, 0xA4, 0xA2, 0xA8, 0x5A, 0x95, 0xE6, 0xB7);
    func_8020CDA0(0x2D3);
    D_801F0B50_ovl_101CE0 = k;
}

void func_801DE57C_ovl_101CE0(void) {
    s32 *p = &D_801EB288_ovl_101CE0;

    if (*p != 0) {
        func_80079618(0x218E9B4, 0x15, -0x14, 6);
        *p = 0;
    }
    if (D_801EB28C_ovl_101CE0 != NULL) {
        HFree(D_801EB28C_ovl_101CE0);
        D_801EB28C_ovl_101CE0 = NULL;
    }
}
