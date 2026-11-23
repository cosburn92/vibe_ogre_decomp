#include "common.h"

/* 233210 */

typedef struct BattleObj {
    /* 0x00 */ u8 unk00[0x18];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 unk1C[0x28];
    /* 0x44 */ s32 unk44;
} BattleObj;

/* Battle unit (0xF8 bytes, 20 of them at battle state +0x1C4) */
typedef struct BattleUnit {
    /* 0x00 */ struct BattleObj *obj;
    /* 0x04 */ u8 unk04[0x1C];
    /* 0x20 */ u16 hp;
    /* 0x22 */ u16 maxHp;
    /* 0x24 */ u16 str;
    /* 0x26 */ u16 vit;
    /* 0x28 */ u16 agi;
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ u16 intel;
    /* 0x2E */ u16 dex;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 unk31[2];
    /* 0x33 */ u8 unk33;
    /* 0x34 */ u8 unk34[2];
    /* 0x36 */ u16 items[4];
    /* 0x3E */ u8 unk3E;
    /* 0x3F */ u8 unk3F;
    /* 0x40 */ u32 flags; /* bit 0 down, bit 8 enemy side, bit 9 leader, bit 12 not targetable */
    /* 0x44 */ u8 unk44[4];
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 cls;
    /* 0x50 */ s32 unk50;
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
    /* 0x84 */ u8 unk84[0x10];
    /* 0x94 */ s32 unk94;
    /* 0x98 */ u8 unk98[0x60];
} BattleUnit; /* size 0xF8 */

typedef struct {
    /* 0x000 */ u8 unk000[0x1C4];
    /* 0x1C4 */ BattleUnit units[20];
} BattleState;

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
s32 func_801C8D84(BattleUnit *u);
s32 func_801C8B68(BattleUnit *u);
u8 func_8016F580(u16 id);
u8 func_8016F598(u16 id);
typedef struct {
    u8 mode;
    u8 unk1[3];
    u8 flags;
} BattleMode;
extern BattleMode D_801976D9;
extern u8 D_801976E9;
s32 func_8016D2FC(u8 a, u8 b);
s8 func_8016F65C(u16 id);
s8 func_8016F6AC(u16 id);
s8 func_8016F7EC(u16 id);
u8 func_8016D3A4(u8 a, u8 cls);
f32 func_801F1B98_ovl_22A280(BattleUnit *a, BattleUnit *b);
s32 func_8016F9F0(u16 id);
f32 func_801F1884_ovl_22A280(BattleUnit *a, BattleUnit *b);

/* Bonus from the unit's weapon-like item (func_801C8FB8) */
static inline s16 BattleUnitWeaponBonus(BattleUnit *u) {
    u16 id;

    if (u == NULL) {
        return 0;
    }
    id = func_801C8FB8(u);
    if (id == 0) {
        return 0;
    }
    return func_8016F65C(id);
}

static inline s32 BattleUnitItemSum7EC(BattleUnit *u) {
    s16 s;

    if (u == NULL) {
        return 0;
    }
    s = u->items[0] != 0 ? func_8016F7EC(u->items[0]) : 0;
    if (u->items[1] != 0) {
        s += func_8016F7EC(u->items[1]);
    }
    if (u->items[2] != 0) {
        s += func_8016F7EC(u->items[2]);
    }
    if (u->items[3] != 0) {
        return s + func_8016F7EC(u->items[3]);
    }
    return s;
}

static inline s32 BattleUnitItemSum6AC(BattleUnit *u) {
    s16 s;

    if (u == NULL) {
        return 0;
    }
    s = u->items[0] != 0 ? func_8016F6AC(u->items[0]) : 0;
    if (u->items[1] != 0) {
        s += func_8016F6AC(u->items[1]);
    }
    if (u->items[2] != 0) {
        s += func_8016F6AC(u->items[2]);
    }
    if (u->items[3] != 0) {
        return s + func_8016F6AC(u->items[3]);
    }
    return s;
}

static inline s32 BattleUnitItemSum65C(BattleUnit *u) {
    s16 s;

    if (u == NULL) {
        return 0;
    }
    s = u->items[0] != 0 ? func_8016F65C(u->items[0]) : 0;
    if (u->items[1] != 0) {
        s += func_8016F65C(u->items[1]);
    }
    if (u->items[2] != 0) {
        s += func_8016F65C(u->items[2]);
    }
    if (u->items[3] != 0) {
        return s + func_8016F65C(u->items[3]);
    }
    return s;
}
BattleUnit *func_801CA2E0(s32 lane, s32 row);
s32 func_801CD19C(s32 a, s32 cls, s32 flag);
s32 func_801C8B08(BattleUnit *u);
u8 func_8016FF5C(u8 a, u8 b);
u16 func_8016DF88(u8 a, u8 cls);
u16 func_8016DFDC(u8 a, u8 cls);
u16 func_8016E030(u8 a, u8 cls);
u16 func_8016E084(u8 a, u8 cls);
u8 func_8016E338(u8 a, u8 cls, u8 c);
s32 func_801C8BA4(BattleUnit *u);
s32 func_801DF2AC(s32 *p, s32 a, s32 b);
void func_801D9F8C(s32 a, s32 b, BattleUnit *u, s32 c, s32 d);
void func_801D9F60(s32 a, s32 b, BattleUnit *u, s32 c);
extern BattleState *D_801CE8BC;
s32 func_801BE138(s32 a, s32 cls, s32 c, s32 d);
void func_801E15E0(BattleUnit *u, s32 cls);
u8 func_8016E470(u8 a, u16 b, u16 c, u16 d, u16 e);
extern s8 D_801F6A14_ovl_22A280[][5];
extern s8 D_801F6A44_ovl_22A280[][7];

/* Folds an affinity id onto 0-6: 1-6 stay, 9/13 -> 1, 10/14 -> 2, 11 -> 3, 12 -> 4, else 0 */
#define FOLD_AFFINITY(k)        switch (k) {                    case 1:                     case 2:                     case 3:                     case 4:                     case 5:                     case 6:                         break;                  case 11:                        k = 3;                      break;                  case 12:                        k = 4;                      break;                  case 9:                     case 13:                        k = 1;                      break;                  case 10:                    case 14:                        k = 2;                      break;                  default:                        k = 0;                      break;              }
/* --- end decls --- */

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_801C8AEC(void);
s32 func_801C8AFC(void);
s32 func_801C8C74(BattleUnit *u);
extern s8 D_801F69D0_ovl_22A280[11][2]; /* alignment difference threshold, step */
extern s8 D_801F69E8_ovl_22A280[11][2]; /* level difference threshold, step */
extern s8 D_801F6A00_ovl_22A280[];      /* per-battle bias */

/* How much attacker a's alignment (unk34[0]) changes for defeating b: steps from the
 * alignment and level differences plus the battle's bias, -5..5, kept within 0..100 */
s32 BattleAlignmentChange(BattleUnit *a, BattleUnit *b) {
    s32 da;
    s32 dl;
    u32 i;
    u32 j;
    s32 v;

    if ((a == NULL) | (b == NULL)) {
        return 0;
    }
    if (func_801C8AEC() != 0 || func_801C8AFC() != 0 || (u32)(a->unk48 - 0x51) < 3 || func_801C8B68(a) != 0 ||
        func_801C8C74(a) != 0 || func_801C8C74(b) != 0) {
        return 0;
    }
    if ((u8)*D_801976DC >= 30) {
        return 0;
    }
    da = a->unk34[0] - b->unk34[0];
    for (i = 0; i < 11; i++) {
        if (da >= D_801F69D0_ovl_22A280[i][0]) {
            da = D_801F69D0_ovl_22A280[i][1];
            break;
        }
    }
    dl = a->unk31[0] - b->unk31[0];
    for (j = 0; j < 11; j++) {
        if (dl <= D_801F69E8_ovl_22A280[j][0]) {
            dl = D_801F69E8_ovl_22A280[j][1];
            break;
        }
    }
    da += dl + D_801F6A00_ovl_22A280[FIELD(D_801CE8BC, s32, 0x1C0)];
    if (da > 5) {
        da = 5;
    }
    if (da < -5) {
        da = -5;
    }
    v = a->unk34[0] + da;
    if (v < 0) {
        v = 0;
    }
    if (v > 100) {
        v = 100;
    }
    return v - a->unk34[0];
}

s32 func_801C8AEC(void);
s32 func_801C8AFC(void);
s32 func_801C8C74(BattleUnit *u);
extern s8 D_801F6A04_ovl_22A280[7][2]; /* (average minus unit's value) threshold, adjustment */

/* Pulls every eligible unit's unk34[0] toward the side's average (table steps, clamped 0..100) */
void func_801F00E4_ovl_22A280(void) {
    BattleUnit *u;
    s32 n;
    s32 sum;
    s32 i;
    u32 k;
    s32 v;
    s32 d;

    if (func_801C8AEC() == 0 && func_801C8AFC() == 0) {
        n = 0;
        if ((u8)*D_801976DC < 30) {
            sum = 0;
            for (i = 0; i < 20; i++) {
                u = func_801C8FE8(i);
                if (u != NULL && func_801C8B68(u) == 0 && func_801C8C74(u) == 0) {
                    n++;
                    sum += u->unk34[0];
                }
            }
            if (n != 0) {
                sum /= n;
                for (i = 0; i < 20; i++) {
                    u = func_801C8FE8(i);
                    if (func_801C8E30(u) == 0 && func_801C8B68(u) == 0 && func_801C8C74(u) == 0 &&
                        func_801C8E9C(u) == 0) {
                        d = sum - u->unk34[0];
                        for (k = 0; k < 7; k++) {
                            if (d >= D_801F6A04_ovl_22A280[k][0]) {
                                v = D_801F6A04_ovl_22A280[k][1] + u->unk34[0];
                                if (v < 0) {
                                    v = 0;
                                }
                                if (v > 100) {
                                    v = 100;
                                }
                                u->unk34[0] = v;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

#ifdef NON_MATCHING
/* u16 result kept in a0 unmasked; return-path masking differs */
u8 func_801F0298_ovl_22A280(BattleUnit *u) {
    s32 r;
    u8 k;

    r = func_8016FB50(u->items[0], u->items[1], u->items[2], u->items[3]) & 0xFFFF;
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

/* Support target: the leader for Attack Leader if reachable, otherwise the highest threat */
#ifdef NON_MATCHING
/* case-2 found block is laid out before the loop in the original */
s32 func_801F0D24_ovl_22A280(BattleUnit *self, u8 mode) {
    BattleUnit *list[6];
    BattleUnit *t;
    s32 n;
    s32 i;

    n = func_801F0514_ovl_22A280(list, (func_801C8B84(self) == 0) << 3, self->lane);
    if (n == 0) {
        return -1;
    }
    switch ((u32)func_801CA384(self)) {
        case 2:
            for (i = 0; i < n; i++) {
                if (func_801C8C58(list[i])) {
                    t = list[i];
                    goto done;
                }
            }
        case 0:
        case 1:
        case 3:
            t = func_801F089C_ovl_22A280(self, list, n, mode);
            break;
        default:
            t = NULL;
            break;
    }
done:
    return func_801CA29C(t);
}
#else
INCLUDE_ASM("asm/nonmatchings/233210", func_801F0D24_ovl_22A280);
#endif

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

/* Changes a unit's class: default equipment, action count and sprite follow the new class */
inline void func_801F0F5C_ovl_22A280(BattleUnit *u, s32 cls) {
    BattleObj *o;
    s32 v;
    s32 x;

    if (u->cls == u->unk48) {
        u->unk48 = cls;
    }
    u->cls = cls;
    u->items[0] = func_8016DF88(u->unk48, cls);
    u->items[1] = func_8016DFDC(u->unk48, cls);
    u->items[2] = func_8016E030(u->unk48, cls);
    u->items[3] = func_8016E084(u->unk48, cls);
    u->actsMax = func_8016E338(u->unk48, u->cls, func_801C9FA4(u->unk58));
    x = func_801C8B68(u);
    v = func_801BE138(u->unk48, cls, x, func_801C8BA4(u));
    o = u->obj;
    u->unk50 = v;
    o->unk44 = v;
    o->unk18 = v;
    func_801E15E0(u, cls);
}

#ifdef NON_MATCHING
/* loop keeps base and 0x1C4+i*0xF8 offset separate; GCC folds 0x20C */
void func_801F104C_ovl_22A280(BattleUnit *u, s32 t, s32 cls) {
    s32 *o = &u->obj->unk44;
    s32 i;

    t += func_801DF2AC(o, 0x11, 0);
    t += func_801DF2AC(o, 0x12, 0);
    for (i = 0; i < 20; i++) {
        if (D_801CE8BC->units[i].unk48 == 0) {
            break;
        }
    }
    func_801D9F8C(0x39, t, u, cls, i);
    func_801D9F60(0x3A, t += 0x23, u, i);
    func_801F0F5C_ovl_22A280(u, cls);
    u->unk94 = t;
}
#else
INCLUDE_ASM("asm/nonmatchings/233210", func_801F104C_ovl_22A280);
#endif

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

f32 func_801F1274_ovl_22A280(s32 k, BattleUnit *u) {
    FOLD_AFFINITY(k);
    if (k == 5) {
        return (u->unk34[0] - 50) * 0.1;
    }
    if (k == 6) {
        return (50 - u->unk34[0]) * 0.1;
    }
    return D_801F6A14_ovl_22A280[k][u->unk33];
}

s8 func_801F1344_ovl_22A280(BattleUnit *u) {
    u8 a = func_801C9FA4(u->unk58);

    return D_801F6A30_ovl_22A280[func_8016E458(((u8 *)u)[0x7F])][a];
}

s32 func_801F139C_ovl_22A280(BattleUnit *a, BattleUnit *b) {
    s32 r = 0;

    if (func_801C8D84(b)) {
        if (a->cls == 20) {
            r = 5;
        } else if ((func_8016F580(a->items[0]) | func_8016F580(a->items[1]) | func_8016F580(a->items[2]) |
                    func_8016F580(a->items[3])) & 1) {
            r = 5;
        }
    }
    return r;
}

s32 func_801F1444_ovl_22A280(BattleUnit *a, BattleUnit *b) {
    s32 r = 0;

    if (func_801C8D84(a)) {
        if (b->cls == 20) {
            r = 5;
        } else if ((func_8016F598(b->items[0]) | func_8016F598(b->items[1]) | func_8016F598(b->items[2]) |
                    func_8016F598(b->items[3])) & 1) {
            r = 5;
        }
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/233210", func_801F14E8_ovl_22A280);

#ifdef NON_MATCHING
/* original keeps &D_801976D9 in s1 across the call; GCC rematerializes it */
s32 func_801F1700_ovl_22A280(BattleUnit *u) {
    BattleMode *s = &D_801976D9;
    u8 t;

    t = (s->mode & 0x80) ? 15 : s->mode;
    if (t != 15 && t != 19) {
        return 0;
    }
    if (func_801C8B84(u) && (s->flags & 8)) {
        return 3;
    }
    if (func_801C8B68(u) == 0) {
        return 0;
    }
    return (D_801976E9 & 8) ? 3 : 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/233210", func_801F1700_ovl_22A280);
#endif

s8 func_801F17B8_ovl_22A280(BattleUnit *u) {
    u8 k = func_8016E470(u->attack, u->items[0], u->items[1], u->items[2], u->items[3]);
    u8 e = func_8016F5E0(func_801C8FB8(u));

    FOLD_AFFINITY(k);
    return D_801F6A44_ovl_22A280[e][k];
}

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

/* Physical attack power: (class power + weapon) / 6 * (str + item str + 50) / 50
 * * (stat 0x2E + item bonus + 100) / 100 * (100 + func_801F1884) / 100 */
#ifdef NON_MATCHING
/* formula right; inlined item-sum helper's register flow differs */
s32 func_801F2484_ovl_22A280(BattleUnit *a, BattleUnit *b) {
    u8 base = func_8016D2FC(a->unk48, a->cls);
    f32 p;
    s16 s;

    p = (f32)(base + BattleUnitWeaponBonus(a)) / 6.0f;
    s = 0;
    if (!func_8016F9F0(a->items[0])) {
        s = func_8016F65C(a->items[0]);
    }
    if (!func_8016F9F0(a->items[1])) {
        s += func_8016F65C(a->items[1]);
    }
    if (!func_8016F9F0(a->items[2])) {
        s += func_8016F65C(a->items[2]);
    }
    if (!func_8016F9F0(a->items[3])) {
        s += func_8016F65C(a->items[3]);
    }
    p *= (f32)(a->str + s + 50) / 50.0f;
    p *= (f32)(a->dex + BattleUnitItemSum7EC(a) + 100) / 100.0f;
    p *= (func_801F1884_ovl_22A280(a, b) + 100.0f) / 100.0f;
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/233210", func_801F2484_ovl_22A280);
#endif

/* Physical defence of b against a: class defence / 20 * (0x26 + item bonus + 25) / 25
 * * (0x24 + item bonus + 100) / 100 * (100 + func_801F1B98) / 100 */
#ifdef NON_MATCHING
/* formula right; inlined item-sum helper's register flow differs */
s32 func_801F26D4_ovl_22A280(BattleUnit *a, BattleUnit *b) {
    f32 p = func_8016D3A4(b->unk48, b->cls) / 20.0f;

    p *= (f32)(b->vit + BattleUnitItemSum6AC(b) + 25) / 25.0f;
    p *= (f32)(b->str + BattleUnitItemSum65C(b) + 100) / 100.0f;
    p *= (func_801F1B98_ovl_22A280(a, b) + 100.0f) / 100.0f;
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/233210", func_801F26D4_ovl_22A280);
#endif

#ifdef NON_MATCHING
/* formula right; inlined item-sum helper's register flow differs */
s32 func_801F28E0_ovl_22A280(BattleUnit *a, BattleUnit *b) {
    u8 base = func_8016D2FC(a->unk48, a->cls);
    f32 p;

    p = (f32)(base + BattleUnitItemSum7EC(a)) / 6.0f;
    p *= (f32)(a->dex + 50) / 50.0f;
    p *= (f32)(a->vit + BattleUnitItemSum6AC(a) + 100) / 100.0f;
    p *= (func_801F1884_ovl_22A280(a, b) + 100.0f) / 100.0f;
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/233210", func_801F28E0_ovl_22A280);
#endif

INCLUDE_ASM("asm/nonmatchings/233210", func_801F2AF8_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F2D10_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F2F1C_ovl_22A280);

s8 func_8016F79C(u16 id);
f32 func_801F2340_ovl_22A280(BattleUnit *u);

static inline s8 Bonus79C(u16 id) {
    return id != 0 ? func_8016F79C(id) : 0;
}

static inline s8 Bonus7EC(u16 id) {
    return id != 0 ? func_8016F7EC(id) : 0;
}


static inline s32 BattleUnitItemSum79C(BattleUnit *u) {
    s16 s;

    if (u == NULL) {
        return 0;
    }
    s = Bonus79C(u->items[0]);
    if (u->items[1] != 0) {
        s += func_8016F79C(u->items[1]);
    }
    if (u->items[2] != 0) {
        s += func_8016F79C(u->items[2]);
    }
    if (u->items[3] != 0) {
        return s + func_8016F79C(u->items[3]);
    }
    return s;
}

static inline s32 ItemSum7EC_b(BattleUnit *u) {
    s16 s;

    if (u == NULL) {
        return 0;
    }
    s = Bonus7EC(u->items[0]);
    if (u->items[1] != 0) {
        s += func_8016F7EC(u->items[1]);
    }
    if (u->items[2] != 0) {
        s += func_8016F7EC(u->items[2]);
    }
    if (u->items[3] != 0) {
        return s + func_8016F7EC(u->items[3]);
    }
    return s;
}

#ifdef NON_MATCHING
/* same length; the inlined item sums' last item (if/return vs the original's single truncation at the join) differs */
s32 func_801F312C_ovl_22A280(BattleUnit *u) {
    f32 p = u->intel + BattleUnitItemSum79C(u) + 50;

    p *= (f32)(u->dex + ItemSum7EC_b(u) + 100) / 50.0f;
    p *= (func_801F2340_ovl_22A280(u) + 100.0f) / 100.0f;
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/233210", func_801F312C_ovl_22A280);
#endif

INCLUDE_ASM("asm/nonmatchings/233210", func_801F32EC_ovl_22A280);

/* Element affinity between two elements: 0 if either is none/7/8/15; Virtue/Bane (5, 6): 1 same, -1 opposite;
 * 9+ fold onto 1-4; otherwise 1 - |a - b| */
s32 func_801F356C_ovl_22A280(u8 a, u8 b) {
    s32 d;

    if (a == 0 || b == 0) {
        return 0;
    }
    if (a == 7 || b == 7) {
        return 0;
    }
    if (a == 8 || b == 8) {
        return 0;
    }
    if (a == 15 || b == 15) {
        return 0;
    }
    if ((u8)(a - 5) < 2) {
        if ((u8)(b - 5) < 2) {
            return (a != b) ? -1 : 1;
        }
        return 0;
    }
    if ((u8)(b - 5) < 2) {
        return 0;
    }
    if (a >= 9) {
        a = (a - 9) % 4 + 1;
    }
    if (b >= 9) {
        b = (b - 9) % 4 + 1;
    }
    d = a - b;
    if (d <= 0) {
        d = b - a;
    }
    return 1 - d;
}

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

/* Chance roll: ((a - b) / 2 + 5)% on the +0x30 values */
s32 func_801F4540_ovl_22A280(BattleUnit *a, BattleUnit *b) {
    s32 v = (a->unk30 - b->unk30) / 2 + 5;

    if (v > 0) {
        return func_8009C7CC() % 100 < v;
    }
    return 0;
}

/* Status effects a's weapon inflicts that b's equipment and class don't protect against */
u8 func_801F45C0_ovl_22A280(BattleUnit *a, BattleUnit *b) {
    u8 inflict;
    u8 protect;
    u16 id = func_801C8FB8(a);

    inflict = 0;
    protect = 0;
    if (id != 0) {
        inflict = func_8016F580(id);
    }
    if (b->items[0] != 0) {
        protect = func_8016F598(b->items[0]);
    }
    if (b->items[1] != 0) {
        protect |= func_8016F598(b->items[1]);
    }
    if (b->items[2] != 0) {
        protect |= func_8016F598(b->items[2]);
    }
    if (b->items[3] != 0) {
        protect |= func_8016F598(b->items[3]);
    }
    if (func_801CD19C(b->unk48, b->cls, 4)) {
        protect |= 2;
    }
    if (func_801CD19C(b->unk48, b->cls, 8)) {
        protect |= 4;
    }
    if (func_801CD19C(b->unk48, b->cls, 2)) {
        protect |= 8;
    }
    if (func_801CD19C(b->unk48, b->cls, 0x10)) {
        protect |= 0x20;
    }
    inflict &= ~protect;
    return inflict;
}

/* Whether u is not protected against status effect `effect` (4, 3, 8, 10 map to protect bits 2, 8, 4, 0x20) */
s32 func_801F46DC_ovl_22A280(s32 effect, BattleUnit *u) {
    u8 p = 0;
    s32 r;

    if (u->items[0] != 0) {
        p = func_8016F598(u->items[0]);
    }
    if (u->items[1] != 0) {
        p |= func_8016F598(u->items[1]);
    }
    if (u->items[2] != 0) {
        p |= func_8016F598(u->items[2]);
    }
    if (u->items[3] != 0) {
        p |= func_8016F598(u->items[3]);
    }
    if (func_801CD19C(u->unk48, u->cls, 4)) {
        p |= 2;
    }
    if (func_801CD19C(u->unk48, u->cls, 8)) {
        p |= 4;
    }
    if (func_801CD19C(u->unk48, u->cls, 2)) {
        p |= 8;
    }
    if (func_801CD19C(u->unk48, u->cls, 0x10)) {
        p |= 0x20;
    }
    switch ((u32)effect) {
        case 4:
            r = p & 2;
            break;
        case 3:
            r = p & 8;
            break;
        case 8:
            r = p & 4;
            break;
        case 10:
            r = p & 0x20;
            break;
        default:
            return 1;
    }
    if (r != 0) {
        r = 0;
    } else {
        r = 1;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/233210", func_801F4828_ovl_22A280);

/* Battle grid position of slot i: units 0-19 from the unit, 20-46 a 3-wide grid, 47-86 a 4-wide grid */
void func_801F4A8C_ovl_22A280(s32 i, s32 *x, s32 *y) {
    if (i < 20) {
        BattleUnit *u = func_801C8FE8(i);

        *x = u->lane;
        *y = u->unk58;
    } else if (i < 47) {
        i -= 20;
        *x = i % 3;
        *y = i / 3;
    } else if (i < 87) {
        i -= 47;
        *x = i % 4;
        *y = i / 4;
    } else {
        *x = -1;
        *y = -1;
    }
}

/* addu operand order (1 byte) */
u8 *func_801F4B48_ovl_22A280(u8 *p, s32 i)
{
  s32 new_var;
  return (u8 *) ((i * 3) + (new_var = (s32) (p + 0x14)));
}

INCLUDE_ASM("asm/nonmatchings/233210", func_801F4B5C_ovl_22A280);

/* Whether nobody stands in front of u in its lane (front row 6 for the player side, 2 for the enemy) */
s32 func_801F54C8_ovl_22A280(BattleUnit *u) {
    if (func_801C8B84(u)) {
        if (u->unk58 == 6) {
            return 1;
        }
        if (u->unk58 == 7) {
            return func_801C8E30(func_801CA2E0(u->lane, 6)) != 0;
        }
        if (u->unk58 == 8) {
            if (!func_801C8E30(func_801CA2E0(u->lane, 7))) {
                return 0;
            }
            return func_801C8E30(func_801CA2E0(u->lane, 6)) != 0;
        }
    } else {
        if (u->unk58 == 2) {
            return 1;
        }
        if (u->unk58 == 1) {
            return func_801C8E30(func_801CA2E0(u->lane, 2)) != 0;
        }
        if (u->unk58 == 0) {
            if (!func_801C8E30(func_801CA2E0(u->lane, 1))) {
                return 0;
            }
            return func_801C8E30(func_801CA2E0(u->lane, 2)) != 0;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/233210", func_801F55AC_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F5AC4_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F6068_ovl_22A280);

INCLUDE_ASM("asm/nonmatchings/233210", func_801F6504_ovl_22A280);

s32 func_801F67D4_ovl_22A280(BattleUnit *u, u32 f) {
    s32 r = 0;
    s32 k = func_801C8B08(u);

    if (f & 0x8000) {
        return 0;
    }
    if (func_801C8B84(u) && (f & 0x400)) {
        r = 1;
    }
    if (func_801C8B68(u) && !(f & 0x400)) {
        r = 1;
    }
    if (k == 0) {
        r = 0;
    }
    if (r) {
        if (k == 0xFF) {
            if (!func_801C8C58(u)) {
                r = 0;
            }
        } else if (!func_8016FF5C(u->unk48, k)) {
            r = 0;
        }
    }
    return r;
}

s32 func_801F68A4_ovl_22A280(u8 *a, u8 *b) {
    return a[1] - b[1];
}

s32 func_801F68B4_ovl_22A280(u8 *a, u8 *b) {
    return a[2] - b[2];
}
