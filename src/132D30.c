#include "common.h"

/* 132D30 */

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern u8 D_801951CC[];         /* 0x24-byte records, u16 flags */
extern u8 D_801969BA[];         /* 11-byte records */
extern u8 *D_801F0CB0_ovl_101CE0[];
s32 func_801DA228_ovl_101CE0(u8 *u);
/* --- end decls --- */

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
} Squad132; /* size 0x19 */
typedef struct {
    /* 0x00 */ Character c;
    /* 0x34 */ u8 unk34[4];
} Player132; /* size 0x38 */
extern Squad132 gSquads[];
extern Player132 D_80193BC0[];
extern Character D_80195560[];

/* Whether unit u's squad (or, with flag 0x40, any squad of its legion) has a member at fatigue 10+ */
s32 func_801DE5F0_ovl_101CE0(u8 *u) {
    u8 max = 0;
    s32 i;
    s32 k;
    s32 id;
    u8 *l;

    if (!(FIELD(u, u32, 0) & 0x40)) {
        for (i = 0; i < 5; i++) {
            id = gSquads[u[4]].members[i];
            if (id != 0) {
                if (id < 100) {
                    if (u[4] < 30) {
                        if (D_80193BC0[id].c.hp != 0 && max < D_80193BC0[id].c.fatigue) {
                            max = D_80193BC0[id].c.fatigue;
                        }
                    } else {
                        if (D_80195560[id].hp != 0 && max < D_80195560[id].fatigue) {
                            max = D_80195560[id].fatigue;
                        }
                    }
                }
            }
        }
    } else {
        l = &D_801969BA[func_801DA228_ovl_101CE0(u) * 11];
        for (k = 0; k < 5; k++) {
            if (l[k] != 0xFF) {
                for (i = 0; i < 5; i++) {
                    id = gSquads[l[k]].members[i];
                    if (id != 0) {
                        if (id < 100) {
                            if (u[4] < 30) {
                                if (D_80193BC0[id].c.hp != 0 && max < D_80193BC0[id].c.fatigue) {
                                    max = D_80193BC0[id].c.fatigue;
                                }
                            } else {
                                if (D_80195560[id].hp != 0 && max < D_80195560[id].fatigue) {
                                    max = D_80195560[id].fatigue;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return !(max < 10);
}

/* Whether unit u (or, with flag 0x40, the unit it is linked to) has record flag 2 set */
s32 func_801DE800_ovl_101CE0(u8 *u) {
    s32 r = 0;
    u8 *l;

    if (!(FIELD(u, u32, 0) & 0x40)) {
        if (!(FIELD(u, u32, 0) & 0x40000)) {
            if (FIELD(u, s32, 0x74) != -1) {
                if (FIELD(D_801951CC + FIELD(u, s32, 0x74) * 0x24, u16, 0) & 2) {
                    r = 1;
                }
            }
        }
    } else {
        l = D_801F0CB0_ovl_101CE0[D_801969BA[func_801DA228_ovl_101CE0(u) * 11]];
        if (!(FIELD(l, u32, 0) & 0x40000)) {
            if (FIELD(l, s32, 0x74) != -1 && (FIELD(D_801951CC + FIELD(l, s32, 0x74) * 0x24, u16, 0) & 2)) {
                r = 1;
            }
        }
    }
    return r;
}

/* Whether every member of unit u's squad (or legion) has fatigue below 90 */
s32 func_801DE8E8_ovl_101CE0(u8 *u) {
    u8 max = 0;
    s32 i;
    s32 k;
    s32 id;
    u8 *l;

    if (!(FIELD(u, u32, 0) & 0x40)) {
        for (i = 0; i < 5; i++) {
            id = gSquads[u[4]].members[i];
            if (id != 0) {
                if (id < 100) {
                    if (u[4] < 30) {
                        if (D_80193BC0[id].c.hp != 0 && max < D_80193BC0[id].c.fatigue) {
                            max = D_80193BC0[id].c.fatigue;
                        }
                    } else {
                        if (D_80195560[id].hp != 0 && max < D_80195560[id].fatigue) {
                            max = D_80195560[id].fatigue;
                        }
                    }
                }
            }
        }
    } else {
        l = &D_801969BA[func_801DA228_ovl_101CE0(u) * 11];
        for (k = 0; k < 5; k++) {
            if (l[k] != 0xFF) {
                for (i = 0; i < 5; i++) {
                    id = gSquads[l[k]].members[i];
                    if (id != 0) {
                        if (id < 100) {
                            if (u[4] < 30) {
                                if (D_80193BC0[id].c.hp != 0 && max < D_80193BC0[id].c.fatigue) {
                                    max = D_80193BC0[id].c.fatigue;
                                }
                            } else {
                                if (D_80195560[id].hp != 0 && max < D_80195560[id].fatigue) {
                                    max = D_80195560[id].fatigue;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return max < 90;
}

extern s32 D_801EB2E0_ovl_101CE0; /* next character to recover */
extern u8 D_801F0C3C_ovl_101CE0[]; /* per enemy character: busy */
extern s32 D_801F367C_ovl_101CE0;  /* map unit count */
void func_801DED50_ovl_101CE0(u8 *u, s32 r);
s32 func_801DEFC0_ovl_101CE0(u8 *u);
s32 func_801DF204_ovl_101CE0(void *u);

/* Rests ten more characters (fatigue -4, HP +4) each call, then lets every idle unit pick its
 * next action */
void func_801DEAF4_ovl_101CE0(void) {
    s32 i;
    u8 *u;
    s32 r;

    for (i = D_801EB2E0_ovl_101CE0; i < D_801EB2E0_ovl_101CE0 + 10; i++) {
        if (i >= 200) {
            break;
        }
        if (D_801F0C3C_ovl_101CE0[i - 100] == 0) {
            if (i < 100) {
                if (D_80193BC0[i].c.fatigue >= 4) {
                    D_80193BC0[i].c.fatigue -= 4;
                } else {
                    D_80193BC0[i].c.fatigue = 0;
                }
                if (D_80193BC0[i].c.maxHp >= D_80193BC0[i].c.hp + 4) {
                    D_80193BC0[i].c.hp += 4;
                } else {
                    D_80193BC0[i].c.hp = D_80193BC0[i].c.maxHp;
                }
            } else {
                if (D_80195560[i - 100].fatigue >= 4) {
                    D_80195560[i - 100].fatigue -= 4;
                } else {
                    D_80195560[i - 100].fatigue = 0;
                }
                if (D_80195560[i - 100].maxHp >= D_80195560[i - 100].hp + 4) {
                    D_80195560[i - 100].hp += 4;
                } else {
                    D_80195560[i - 100].hp = D_80195560[i - 100].maxHp;
                }
            }
        }
    }
    D_801EB2E0_ovl_101CE0 += 10;
    if (D_801EB2E0_ovl_101CE0 >= 200) {
        D_801EB2E0_ovl_101CE0 = 0;
    }
    for (i = 0; i < D_801F367C_ovl_101CE0; i++) {
        u = D_801F0CB0_ovl_101CE0[i];
        if (FIELD(u, s32, 0) & 0x10) {
            if (!(FIELD(u, s32, 0) & 0x1000)) {
                r = func_801DF204_ovl_101CE0(u);
                if (r == -1) {
                    r = func_801DEFC0_ovl_101CE0(u);
                    if (r == -1) {
                        continue;
                    }
                }
                func_801DED50_ovl_101CE0(u, r);
            }
        }
    }
}

extern u8 gLegions[][11];
extern u8 D_800E7A90[];
void func_801DC910_ovl_101CE0(void);

/* Applies unit u's resting result r: 0 ends a camp (stationed units under 30 get flag 0x4000
 * instead), 100 starts one: a resting legion leader on suitable ground (or whose members are all
 * at rest) gets flag 0x2000; otherwise the unit stops and, for a leader, all members camp */
#ifdef NON_MATCHING
/* same size; the original zero-extends the tile id (andi 0xFFFF) for the compares and adds the
 * legion base and index the other way round in the last loop */
void func_801DED50_ovl_101CE0(u8 *u, s32 r) {
    u8 *l;
    u8 *m;
    s32 i;

    if (r == -1) {
        return;
    }
    if (r == 0) {
        if (!(FIELD(u, u32, 0) & 0x20000)) {
            return;
        }
        if ((FIELD(u, u32, 0) & 8) && u[4] < 30) {
            FIELD(u, u32, 0x78) |= 0x4000;
            return;
        }
        func_801DC910_ovl_101CE0();
        FIELD(u, u32, 0) &= ~0x20000;
        return;
    }
    if (r != 100) {
        return;
    }
    if (FIELD(u, u32, 0) & 0x21000) {
        return;
    }
    if ((FIELD(u, u32, 0) & 8) && u[4] < 30) {
        if (FIELD(u, u32, 0) & 0x40) {
            l = &D_801969BA[func_801DA228_ovl_101CE0(u) * 11];
            for (i = 0; i < 5; i++) {
                if (l[i] != 0xFF) {
                    m = D_801F0CB0_ovl_101CE0[l[i]];
                    if (FIELD(m, u32, 0) & 0x20000) {
                        FIELD(u, u32, 0x78) |= 0x2000;
                        break;
                    }
                    if (FIELD(m, u32, 0x78) & 0x2000) {
                        break;
                    }
                }
            }
            if (i == 5) {
                FIELD(u, u32, 0x78) |= 0x2000;
            }
        } else {
            u8 c = ((u8 **)D_800E7A90)[D_800E7A90[0x33]][FIELD(u, s32, 0x14)];
            u16 t = c;

            if (t == 8 || t == 15 || (u32)(c - 0x10) < 2 || t == 0x12 || t == 0x13) {
                return;
            }
            FIELD(u, u32, 0x78) |= 0x2000;
        }
        return;
    }
    func_801DC910_ovl_101CE0();
    if (!(FIELD(u, u32, 0) & 0x40)) {
        FIELD(u, u32, 0) |= 0x20000;
        return;
    }
    {
        s32 j;
        u8 *g;

        g = gLegions[func_801DA228_ovl_101CE0(u)];
        for (j = 0; j < 5; j++) {
            if (g[j + 2] != 0xFF) {
                FIELD(D_801F0CB0_ovl_101CE0[g[j + 2]], u32, 0) |= 0x20000;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/132D30", func_801DED50_ovl_101CE0);
#endif

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_801DCD40_ovl_101CE0(u8 *u, s32 a);
s32 func_801DD244_ovl_101CE0(u8 *loc);
extern u8 D_801F0E0A_ovl_101CE0;
extern u8 gLocations[][0x24];
u8 func_801DF4A0_ovl_101CE0(u8 *u);

/* Rest timer of unit u (0xB6): while it rests (inactive, stationed in a town or temple, or
 * following a leader stationed there), counts down by 3 (6 with effect 0x1B) plus 2 outside hours 6-17;
 * each full 180 recovers the squad. Returns the lowest fatigue reached, or -1 */
s32 func_801DEFC0_ovl_101CE0(u8 *u) {
    u8 rest = 0;
    s32 r = -1;
    u8 step;
    s32 t;
    u8 *loc;
    u8 *l;
    s32 m;

    if (!(FIELD(u, u32, 0) & 1)) {
        goto yes;
    }
    if (FIELD(u, u32, 0) & 0x20000) {
        goto yes;
    }
    if (((FIELD(u, u32, 0) & 0x40000) || FIELD(u, s32, 0x74) == -1) && u[4] != 30) {
    } else {
        loc = gLocations[FIELD(u, s32, 0x74)];
        if ((FIELD(u, u32, 0) & 8) && (FIELD(loc, u16, 0x1C) & 2)) {
            goto yes;
        }
        if (FIELD(loc, u16, 0x1C) & 4) {
            goto yes;
        }
        if (func_801DD244_ovl_101CE0(loc) != 0) {
            goto yes;
        }
    }
    if ((FIELD(u, u32, 0) & 0x40040) == 0x40) {
        l = D_801F0CB0_ovl_101CE0[D_801969BA[func_801DA228_ovl_101CE0(u) * 11]];
        if (!(FIELD(l, u32, 0) & 0x40000) && FIELD(l, s32, 0x74) != -1) {
            loc = gLocations[FIELD(l, s32, 0x74)];
            if (FIELD(u, u32, 0) & 8) {
                m = FIELD(loc, u16, 0x1C) & 2;
            } else {
                m = FIELD(loc, u16, 0x1C) & 4;
            }
            if (m != 0) {
            yes:
                rest = 1;
            }
        }
    }
    if (rest == 1) {
        step = 3;
        if (func_801DCD40_ovl_101CE0(u, 0x1B) != 0) {
            step = 6;
        }
        if (FIELD(u, u16, 0xB6) >= step) {
            FIELD(u, u16, 0xB6) -= step;
        } else {
            FIELD(u, u16, 0xB6) = 180;
            t = func_801DF4A0_ovl_101CE0(u);
            if (r < t) {
                r = t;
            }
        }
        if ((u32)(D_801F0E0A_ovl_101CE0 - 6) >= 12) {
            if (FIELD(u, u16, 0xB6) >= 2) {
                FIELD(u, u16, 0xB6) -= 2;
            } else {
                FIELD(u, u16, 0xB6) = 180;
                t = func_801DF4A0_ovl_101CE0(u);
                if (r < t) {
                    r = t;
                }
            }
        }
    }
    return r;
}

s32 func_801DCD40_ovl_101CE0(u8 *u, s32 a);
extern s32 D_801F0DE0_ovl_101CE0;
extern u8 D_801F0E0A_ovl_101CE0;
u8 func_801DF34C_ovl_101CE0(u8 *u);

/* Advances unit u's march timer (0xB6, 180 per step) by 2 or 3 (halved by effect 0x1A), plus 1
 * outside hours 6-17; each full step tires the squad. Returns the highest fatigue reached, or -1 */
#ifdef NON_MATCHING
/* 82/82, 1 word: the timer add is addu v1,s0,v0 in the original (operands swapped here) */
s32 func_801DF204_ovl_101CE0(void *p) {
    u8 *u = p;
    u32 f = FIELD(u, u32, 0);
    s32 r = -1;

    if (!(f & 1)) {
        return -1;
    }
    if (f & 0x20000) {
        return -1;
    }
    if (D_801F0DE0_ovl_101CE0 != 0) {
        return -1;
    }
    if (!(f & 0x40000) || u[4] == 30) {
    fail:
        return -1;
    }
    {
    u32 step = 2;
    s32 t;

    if (!(f & 0x40)) {
        step = (FIELD(u, s32, 0x70) == 1) ? 3 : 2;
    }
    if (func_801DCD40_ovl_101CE0(u, 0x1A) != 0) {
        step >>= 1;
    }
    FIELD(u, u16, 0xB6) += step;
    if (FIELD(u, u16, 0xB6) >= 181) {
        FIELD(u, u16, 0xB6) -= 180;
        t = func_801DF34C_ovl_101CE0(u);
        if (r < t) {
            r = t;
        }
    }
    if ((u32)(D_801F0E0A_ovl_101CE0 - 6) >= 12) {
        FIELD(u, u16, 0xB6)++;
        if (FIELD(u, u16, 0xB6) >= 181) {
            FIELD(u, u16, 0xB6) -= 180;
            t = func_801DF34C_ovl_101CE0(u);
            if (r < t) {
                r = t;
            }
        }
    }
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/132D30", func_801DF204_ovl_101CE0);
#endif

extern u8 D_8018F481;

/* Raises the fatigue of every living, unpetrified member of unit u's squad by one (capped at 100,
 * 50 on maps 0x3F-0x40); returns the highest fatigue */
u8 func_801DF34C_ovl_101CE0(u8 *u) {
    u8 max = 0;
    s32 i;

    for (i = 0; i < 5; i++) {
        s32 id = gSquads[u[4]].members[i];

        if (id != 0) {
            if (id < 100) {
                u8 *f;
                u16 *hp;

                if (u[4] < 30) {
                    if (D_80193BC0[id].c.hp != 0 && !(D_80193BC0[id].c.status & 4)) {
                        f = &D_80193BC0[id].c.fatigue;
                        hp = &D_80193BC0[id].c.hp;
                        goto tire;
                    }
                } else {
                    if (D_80195560[id].hp != 0 && !(D_80195560[id].status & 4)) {
                        f = &D_80195560[id].fatigue;
                        hp = &D_80195560[id].hp;
                    tire:
                        if (*hp != 0) {
                            u32 cap = 100;

                            if ((u32)(D_8018F481 - 0x3F) < 2) {
                                cap = 50;
                            }
                            if (*f < cap) {
                                (*f)++;
                            }
                            if (max < *f) {
                                max = *f;
                            }
                        }
                    }
                }
            }
        }
    }
    return max;
}

extern u16 D_80190EBC[]; /* player generic troops' HP; [99] is the cap */
extern u8 D_80191010[];
extern u16 D_8019532C[]; /* enemy generic troops' HP; [99] is the cap */
extern u8 D_80195480[];

/* One rest tick for squad u's members: characters (id < 100) with a class and HP lose 2 fatigue
 * and gain 1 HP up to max; generic troops regain 1 HP up to the next third of the cap. Returns the
 * highest fatigue left */
u8 func_801DF4A0_ovl_101CE0(u8 *u) {
    u8 max = 0;
    s32 k;
    s32 c;
    u16 *p;
    u16 *cap;
    u8 *f;

    for (k = 0; k < 5; k++) {
        c = gSquads[u[4]].members[k];
        if (c == 0) {
            continue;
        }
        if (c >= 100) {
            u16 m;
            u16 t;
            u16 v;

            if (FIELD(u, u32, 0) & 8) {
                if (D_80191010[c] & 4) {
                    continue;
                }
                p = &D_80190EBC[c];
                cap = &D_80190EBC[99];
            } else {
                if (D_80195480[c] & 4) {
                    continue;
                }
                p = &D_8019532C[c];
                cap = &D_8019532C[99];
            }
            m = *cap;
            t = m / 3;
            v = *p;
            if (t >= v) {
                *p = v + 1;
                if (t < *p) {
                    *p = t;
                }
            } else {
                s32 t2 = t * 2;

                if (t2 >= v) {
                    *p = v + 1;
                    if (t2 < *p) {
                        *p = t2;
                    }
                } else if (m >= v) {
                    *p = v + 1;
                    if (*cap < *p) {
                        *p = *cap;
                    }
                } else {
                    *p = m;
                }
            }
            continue;
        }
        if (u[4] < 30) {
            if (D_80193BC0[c].c.baseCls == 0 || D_80193BC0[c].c.hp == 0 || (D_80193BC0[c].c.status & 4)) {
                continue;
            }
            f = &D_80193BC0[c].c.fatigue;
            p = &D_80193BC0[c].c.hp;
            cap = &D_80193BC0[c].c.maxHp;
        } else {
            if (D_80195560[c].baseCls == 0 || D_80195560[c].hp == 0 || (D_80195560[c].status & 4)) {
                continue;
            }
            f = &D_80195560[c].fatigue;
            p = &D_80195560[c].hp;
            cap = &D_80195560[c].maxHp;
        }
        if (*p == 0) {
            continue;
        }
        if (*f >= 2) {
            *f -= 2;
        } else {
            *f = 0;
        }
        if (max < *f) {
            max = *f;
        }
        if (*p < *cap) {
            *p += 1;
            if (*cap < *p) {
                *p = *cap;
            }
        }
    }
    return max;
}
