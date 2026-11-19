#include "common.h"

/* 233210 */

/* Battle unit (0xF8 bytes, 20 of them at battle state +0x1C4) */
typedef struct BattleUnit {
    /* 0x00 */ u8 unk00[0x20];
    /* 0x20 */ u16 hp;
    /* 0x22 */ u16 maxHp;
    /* 0x24 */ u8 unk24[0xF];
    /* 0x33 */ u8 unk33;
    /* 0x34 */ u8 unk34[2];
    /* 0x36 */ u16 stats[4];
    /* 0x3E */ u8 unk3E;
    /* 0x3F */ u8 unk3F;
    /* 0x40 */ u32 flags; /* bit 0 down, bit 8 player side, bit 9 leader, bit 12 not targetable */
    /* 0x44 */ u8 unk44[0x10];
    /* 0x54 */ s32 lane;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 unk5C[0xC];
    /* 0x68 */ s32 target;
    /* 0x6C */ s32 actsUsed;
    /* 0x70 */ s32 actsMax;
    /* 0x74 */ u8 unk74[4];
    /* 0x78 */ u8 actionKind;
    /* 0x79 */ u8 unk79[3];
    /* 0x7C */ s32 attack;
    /* 0x80 */ s32 unk80;
} BattleUnit;

s32 func_8009C7CC(void);
s32 func_801C8B84(BattleUnit *u);
s32 func_801C8BC0(u8 a, u8 b);
s32 func_801C8C3C(BattleUnit *u);
s32 func_801C8C58(BattleUnit *u);
s32 func_801C8D24(BattleUnit *u);
s32 func_801C8E30(BattleUnit *u);
s32 func_801C8E64(BattleUnit *u);
s32 func_801C8E80(BattleUnit *u);
s32 func_801C8E9C(BattleUnit *u);
s32 func_801C8EB8(BattleUnit *u);
u16 func_801C8FB8(BattleUnit *u);
BattleUnit *func_801C8FE8(s32 i);
u8 func_801C9FA4(s32 a);
s32 func_801CA038(BattleUnit *u, s32 amount);
s32 func_801CA29C(BattleUnit *u);
s32 func_801CA384(BattleUnit *u);
u8 func_8016E458(u8 a);
s32 func_8016F5E0(u16 a);
u16 func_8016FB50(u16 a, u16 b, u16 c, u16 d);
s32 func_801F0514_ovl_22A280(BattleUnit **out, s32 start, s32 lane);
s32 func_801F14E8_ovl_22A280(BattleUnit *u);
s32 func_801F2484_ovl_22A280(BattleUnit *a, BattleUnit *b);
s32 func_801F28E0_ovl_22A280(BattleUnit *a, BattleUnit *b);
s32 func_801F2AF8_ovl_22A280(BattleUnit *a, BattleUnit *b);
s32 BattleCalcDamage(BattleUnit *a, BattleUnit *b, f32 power, s32 c, s32 d, s32 e);
extern s8 D_801F6A30_ovl_22A280[][3];
s32 func_801F4480_ovl_22A280(BattleUnit *a, BattleUnit *b, s32 c, s32 d, s32 e);
BattleUnit *func_801F0A3C_ovl_22A280(BattleUnit *self, BattleUnit **list, s32 n);
#include "tables.h"
f64 fabs(f64 x);
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

extern SquadRec gSquads[];
extern PlayerChar D_80193BC0[];
extern Character D_80195560[];
extern u8 D_801976DC[];
extern u8 D_801976E8[];
extern u8 D_80190F80[];
extern u8 D_801953F0[];
u8 *func_801E14C0(s32 side);
s32 func_801C9FB4(u16 a, u16 b);
s32 func_801C8AC0(s32 a);
f32 func_8007FE70(f32 *a, f32 *b);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/233210", BattleAlignmentChange);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F00E4_ovl_22A280);

#ifdef NON_MATCHING
/* u16 result kept in a0 unmasked; return-path masking differs */
u8 func_801F0298_ovl_22A280(BattleUnit *u) {
    s32 r;
    u8 k;

    r = func_8016FB50(u->stats[0], u->stats[1], u->stats[2], u->stats[3]) & 0xFFFF;
    if (r != 0 || (r = func_801C8FB8(u) & 0xFFFF) != 0) {
        k = func_8016F5E0(r);
        if (k != 8) {
            return k;
        }
    }
    return u->unk33;
}
#else
INCLUDE_ASM("asm/nonmatchings/233210", func_801F0298_ovl_22A280);
#endif

s32 func_801F0310_ovl_22A280(s32 side) {
    u8 *st;
    u8 *tbl;
    u8 *p;
    u8 *m;
    u8 *end;
    s32 sum;
    s32 c;
    s32 idx;

    if (side == 0) {
        st = D_801976DC;
        tbl = D_80190F80;
    } else {
        st = D_801976E8;
        tbl = D_801953F0;
    }
    p = func_801E14C0(side);
    if (p == NULL) {
        return 0;
    }
    idx = p[2];
    if (idx == st[0]) {
        return 0;
    }
    if (fabs(*(f32 *)(st + 8)) < 1.2) {
        sum = 0;
        m = gSquads[idx].members;
        end = m + 5;
        do {
            c = *m;
            if (c == 0) {
                continue;
            }
            if (c < 100) {
                continue;
            }
            c -= 100;
            if (((u16 *)(tbl + 4))[c] == 0) {
                continue;
            }
            if ((tbl + c)[0xF4] & 4) {
                continue;
            }
            sum += func_801C9FB4(((u16 *)(tbl + 4))[c], *(u16 *)(tbl + 2));
        } while (++m < end);
        return sum;
    }
    return 0;
}

/* Which side's squad leader has the lower value at +0x20 (no squad on one side decides it) */
s32 func_801F043C_ovl_22A280(void) {
    u8 *a = func_801E14C0(0);
    u8 *b = func_801E14C0(1);

    if (a != NULL && b == NULL) {
        return 0;
    }
    if (a == NULL && b != NULL) {
        return 1;
    }
    return D_80193BC0[gSquads[a[2]].members[0]].c.intl < D_80195560[gSquads[b[2]].members[0]].intl;
}

INCLUDE_ASM("asm/nonmatchings/233210", func_801F0514_ovl_22A280);

/* Threat score: the target's own attack power times its remaining actions; picks the highest */
BattleUnit *func_801F089C_ovl_22A280(BattleUnit *self, BattleUnit **list, s32 n, u8 mode) {
    s32 best = -9999;
    s32 bestIdx = -1;
    s32 i;
    s32 v;

    for (i = 0; i < n; i++) {
        v = func_801F2484_ovl_22A280(list[i], NULL) + func_801F2AF8_ovl_22A280(list[i], NULL) +
            func_801F28E0_ovl_22A280(list[i], NULL);
        v *= list[i]->actsMax - list[i]->actsUsed;
        v++;
        if (mode != 0 && func_801C8E9C(list[i])) {
            v = 0;
        } else if (mode == 8 && func_801C8E64(list[i])) {
            v = 0;
        } else if (mode == 10 && func_801C8EB8(list[i])) {
            v = 0;
        } else if (mode == 4 && func_801C8E80(list[i])) {
            v = 0;
        }
        if (v == best) {
            best = v - (func_8009C7CC() & 1);
        }
        if (best < v) {
            best = v;
            bestIdx = i;
        }
    }
    if (bestIdx < 0) {
        return NULL;
    }
    return list[bestIdx];
}

/* Picks the attack target from the reachable candidates by the squad strategy:
 * 0 Autonomous: random; 1 Attack Strongest: highest current HP;
 * 2 Attack Leader: the leader if reachable, else random;
 * 3 Attack Weakest: the one this attacker's current attack would damage most. */
/* Picks the attack target from the reachable candidates by the squad strategy:
 * 0 Autonomous: random; 1 Attack Strongest: highest current HP;
 * 2 Attack Leader: the leader if reachable, else random;
 * 3 Attack Weakest: the one this attacker's current attack would damage most. */
#ifdef NON_MATCHING
/* logic matches; self/list land in s5/s6 swapped */
BattleUnit *func_801F0A3C_ovl_22A280(BattleUnit *self, BattleUnit **list, s32 n) {
    switch ((u32)func_801CA384(self)) {
        case 0:
        random:
            return list[func_8009C7CC() % n];
        case 1: {
            s32 best = -9999;
            s32 bestIdx = -1;
            s32 i;

            for (i = 0; i < n; i++) {
                if (best < list[i]->hp) {
                    best = list[i]->hp;
                    bestIdx = i;
                }
            }
            if (bestIdx < 0) {
                return NULL;
            }
            return list[bestIdx];
        }
        case 2: {
            s32 i;

            for (i = 0; i < n; i++) {
                if (func_801C8C58(list[i])) {
                    goto found;
                }
            }
            if (n <= 0) {
                break;
            }
            goto random;
        found:
            return list[i];
        }
        case 3: {
            s32 best = -9999;
            s32 bestIdx = -1;
            s32 i;
            s32 v;

            for (i = 0; i < n; i++) {
                v = func_801F4480_ovl_22A280(self, list[i], 0, 0, 0);
                if (best < v) {
                    best = v;
                    bestIdx = i;
                }
            }
            if (bestIdx < 0) {
                return NULL;
            }
            return list[bestIdx];
        }
    }
    return NULL;
}
#else
INCLUDE_ASM("asm/nonmatchings/233210", func_801F0A3C_ovl_22A280);
#endif

s32 func_801F0C04_ovl_22A280(BattleUnit *u) {
    BattleUnit *list[6];
    s32 n = func_801F0514_ovl_22A280(list, (-(func_801C8B84(u) == 0) & 6) | 2, u->lane);

    if (n != 0) {
        return func_801CA29C(func_801F0A3C_ovl_22A280(u, list, n));
    }
    return -1;
}

s32 func_801F0C68_ovl_22A280(BattleUnit *u) {
    BattleUnit *list[6];
    s32 n = func_801F0514_ovl_22A280(list, (func_801C8B84(u) == 0) << 3, u->lane);

    if (n != 0) {
        return func_801CA29C(func_801F0A3C_ovl_22A280(u, list, n));
    }
    return -1;
}

s32 func_801F0CC4_ovl_22A280(BattleUnit *u) {
    BattleUnit *list[6];
    s32 n = func_801F0514_ovl_22A280(list, (func_801C8B84(u) == 0) << 3, u->lane);

    if (n == 0) {
        return -1;
    }
    return func_801CA29C(func_801F0A3C_ovl_22A280(u, list, n));
}

INCLUDE_ASM("asm/nonmatchings/233210", func_801F0D24_ovl_22A280);

/* Heal target: the unit missing the largest share of its HP (missing capped at 999) */
s32 func_801F0E1C_ovl_22A280(BattleUnit *self) {
    s32 selfIdx = func_801CA29C(self);
    s32 best = -1;
    s32 bestIdx = -1;
    s32 i;
    BattleUnit *u;
    s32 v;

    for (i = 0; i < 20; i++) {
        u = func_801C8FE8(i);
        if (u == NULL) {
            continue;
        }
        if (func_801C8E30(u)) {
            continue;
        }
        if (func_801C8C3C(u)) {
            continue;
        }
        if (func_801C8BC0(selfIdx, i)) {
            continue;
        }
        if (func_801C8D24(u)) {
            continue;
        }
        v = func_801CA038(u, 999);
        v = v * 100 / (u->hp + v);
        if (best == v) {
            best -= func_8009C7CC() & 1;
        }
        if (best < v) {
            best = v;
            bestIdx = i;
        }
    }
    return bestIdx;
}

INCLUDE_ASM("asm/nonmatchings/233210", func_801F0F5C_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F104C_ovl_22A280);

s32 func_801F11E4_ovl_22A280(BattleUnit *u, s32 d) {
    f32 a[3];
    f32 b[3];

    a[0] = func_801C8AC0(4);
    a[1] = 0.0f;
    a[2] = 0.0f;
    b[0] = func_801C8AC0(u->unk58);
    b[1] = 0.0f;
    b[2] = 0.0f;
    return func_8007FE70(a, b) / d;
}

INCLUDE_ASM("asm/nonmatchings/233210", func_801F1274_ovl_22A280);

s8 func_801F1344_ovl_22A280(BattleUnit *u) {
    u8 a = func_801C9FA4(u->unk58);

    return D_801F6A30_ovl_22A280[func_8016E458(((u8 *)u)[0x7F])][a];
}

INCLUDE_ASM("asm/nonmatchings/233210", func_801F139C_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F1444_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F14E8_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F1700_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F17B8_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F1884_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F1B98_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F1F04_ovl_22A280);

f32 func_801F22CC_ovl_22A280(BattleUnit *u) {
    f32 base = func_801F14E8_ovl_22A280(u);
    s32 b = 0;

    if (u != NULL) {
        if (u->unk3E >= 70) {
            if (u->unk3E < 80) {
                b = 5;
            } else if (u->unk3E < 90) {
                b = 18;
            } else {
                b = 40;
            }
        }
    }
    return base - b;
}

INCLUDE_ASM("asm/nonmatchings/233210", func_801F2340_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F2484_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F26D4_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F28E0_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F2AF8_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F2D10_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F2F1C_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F312C_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F32EC_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F356C_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", BattleCalcDamage);

/* Estimated damage of self's current action on target (power by action kind) */
s32 func_801F4480_ovl_22A280(BattleUnit *a, BattleUnit *b, s32 c, s32 d, s32 e) {
    f32 p;

    if ((u8)(a->actionKind - 4) < 2) {
        p = func_801F28E0_ovl_22A280(a, b);
    } else if (a->actionKind == 3) {
        p = func_801F2AF8_ovl_22A280(a, b);
    } else {
        p = func_801F2484_ovl_22A280(a, b);
    }
    return BattleCalcDamage(a, b, p, c, d, e);
}

INCLUDE_ASM("asm/nonmatchings/233210", func_801F4540_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F45C0_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F46DC_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F4828_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F4A8C_ovl_22A280);

#ifdef NON_MATCHING
/* addu operand order (1 byte) */
u8 *func_801F4B48_ovl_22A280(u8 *p, s32 i) {
    return (u8 *)(i * 3 + (s32)(p + 0x14));
}
#else
INCLUDE_ASM("asm/nonmatchings/233210", func_801F4B48_ovl_22A280);
#endif

INCLUDE_ASM("asm/nonmatchings/233210", func_801F4B5C_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F54C8_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F55AC_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F5AC4_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F6068_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F6504_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F67D4_ovl_22A280);

s32 func_801F68A4_ovl_22A280(u8 *a, u8 *b) {
    return a[1] - b[1];
}

s32 func_801F68B4_ovl_22A280(u8 *a, u8 *b) {
    return a[2] - b[2];
}
