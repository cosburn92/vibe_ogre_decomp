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

INCLUDE_ASM("asm/nonmatchings/132D30", func_801DED50_ovl_101CE0);

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_801DCD40_ovl_101CE0(u8 *, s32);        /* extern */
s32 func_801DD244_ovl_101CE0(void *);               /* extern */
extern u8 D_801F0E0A_ovl_101CE0;
extern s32 gLocations;

s32 func_801DEFC0_ovl_101CE0(u8 *arg0) {
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_4;
    s32 temp_v1_6;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    u16 temp_a0_4;
    u16 temp_v1_5;
    u32 temp_v1_3;
    u8 *temp_a0_2;
    void *temp_a0;
    void *temp_a0_3;

    temp_v1 = FIELD(arg0, s32, 0);
    var_s1 = 0;
    var_s2 = -1;
    if ((temp_v1 & 1) && !(temp_v1 & 0x20000) && ((((temp_v1 & 0x40000) || (FIELD(arg0, s32, 0x74) == -1)) && (FIELD(arg0, u8, 4) != 0x1E)) || (((temp_a0 = (FIELD(arg0, s32, 0x74) * 0x24) + &gLocations, ((FIELD(arg0, s32, 0) & 8) == 0)) || !(FIELD(temp_a0, u16, 0x1C) & 2)) && !(FIELD(temp_a0, u16, 0x1C) & 4) && (func_801DD244_ovl_101CE0(temp_a0) == 0)))) {
        var_v1 = 0 & 0xFF;
        if ((FIELD(arg0, s32, 0) & 0x40040) == 0x40) {
            temp_a0_2 = D_801F0CB0_ovl_101CE0[*(D_801969BA + (func_801DA228_ovl_101CE0(arg0) * 0xB))];
            var_v1 = 0 & 0xFF;
            if (!(FIELD(temp_a0_2, s32, 0) & 0x40000)) {
                temp_v1_2 = FIELD(temp_a0_2, s32, 0x74);
                if (temp_v1_2 != -1) {
                    temp_a0_3 = (temp_v1_2 * 0x24) + &gLocations;
                    if (FIELD(arg0, s32, 0) & 8) {
                        var_v0_2 = FIELD(temp_a0_3, u16, 0x1C) & 2;
                    } else {
                        var_v0_2 = FIELD(temp_a0_3, u16, 0x1C) & 4;
                    }
                    var_v1 = 0 & 0xFF;
                    if (var_v0_2 != 0) {
                        goto block_16;
                    }
                } else {
                    goto block_17;
                }
            }
        }
    } else {
block_16:
        var_s1 = 1;
block_17:
        var_v1 = var_s1 & 0xFF;
    }
    var_v0 = -1;
    if (var_v1 == 1) {
        var_s1_2 = 3;
        if (func_801DCD40_ovl_101CE0(arg0, 0x1B) != 0) {
            var_s1_2 = 6;
        }
        temp_a0_4 = FIELD(arg0, u16, 0xB6);
        temp_v1_3 = var_s1_2 & 0xFF;
        if (temp_a0_4 >= temp_v1_3) {
            FIELD(arg0, u16, 0xB6) = (u16) (temp_a0_4 - temp_v1_3);
        } else {
            FIELD(arg0, u16, 0xB6) = 0xB4U;
            temp_v1_4 = func_801DF4A0_ovl_101CE0(arg0) & 0xFF;
            if (temp_v1_4 > -1) {
                var_s2 = temp_v1_4;
            }
        }
        var_v0 = var_s2;
        if ((u32) (D_801F0E0A_ovl_101CE0 - 6) >= 0xCU) {
            temp_v1_5 = FIELD(arg0, u16, 0xB6);
            if (temp_v1_5 >= 2U) {
                FIELD(arg0, u16, 0xB6) = (u16) (temp_v1_5 - 2);
            } else {
                FIELD(arg0, u16, 0xB6) = 0xB4U;
                temp_v1_6 = func_801DF4A0_ovl_101CE0(arg0) & 0xFF;
                if (var_s2 < temp_v1_6) {
                    var_s2 = temp_v1_6;
                }
            }
            var_v0 = var_s2;
        }
    }
    return var_v0;
}
#else
INCLUDE_ASM("asm/nonmatchings/132D30", func_801DEFC0_ovl_101CE0);
#endif

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_801DCD40_ovl_101CE0(void *, s32);      /* extern */
extern s32 D_801F0DE0_ovl_101CE0;
extern u8 D_801F0E0A_ovl_101CE0;

s32 func_801DF204_ovl_101CE0(void *arg0) {
    s32 temp_a0;
    s32 temp_v1_2;
    s32 temp_v1_4;
    s32 var_s2;
    s32 var_v0;
    u16 temp_v0;
    u16 temp_v1;
    u16 temp_v1_3;
    u32 var_s0;

    temp_a0 = FIELD(arg0, s32, 0);
    var_s2 = -1;
    if (temp_a0 & 1) {
        var_v0 = -1;
        if (!(temp_a0 & 0x20000)) {
            var_v0 = -1;
            if (D_801F0DE0_ovl_101CE0 == 0) {
                if (!(temp_a0 & 0x40000) || (FIELD(arg0, u8, 4) == 0x1E)) {
                    goto block_5;
                }
                var_s0 = 2;
                if (!(temp_a0 & 0x40)) {
                    var_s0 = (-(FIELD(arg0, s32, 0x70) == 1) & 3) | 2;
                }
                if (func_801DCD40_ovl_101CE0(arg0, 0x1A) != 0) {
                    var_s0 = var_s0 >> 1;
                }
                temp_v1 = var_s0 + FIELD(arg0, u16, 0xB6);
                FIELD(arg0, u16, 0xB6) = temp_v1;
                if ((u32) (temp_v1 & 0xFFFF) >= 0xB5U) {
                    FIELD(arg0, u16, 0xB6) = (u16) (temp_v1 - 0xB4);
                    temp_v1_2 = func_801DF34C_ovl_101CE0(arg0) & 0xFF;
                    if (temp_v1_2 > -1) {
                        var_s2 = temp_v1_2;
                    }
                }
                var_v0 = var_s2;
                if ((u32) (D_801F0E0A_ovl_101CE0 - 6) >= 0xCU) {
                    temp_v1_3 = FIELD(arg0, u16, 0xB6);
                    temp_v0 = temp_v1_3 + 1;
                    FIELD(arg0, u16, 0xB6) = temp_v0;
                    var_v0 = var_s2;
                    if ((u32) (temp_v0 & 0xFFFF) >= 0xB5U) {
                        FIELD(arg0, u16, 0xB6) = (u16) (temp_v1_3 - 0xB3);
                        temp_v1_4 = func_801DF34C_ovl_101CE0(arg0) & 0xFF;
                        if (var_s2 < temp_v1_4) {
                            var_s2 = temp_v1_4;
                        }
                        var_v0 = var_s2;
                    }
                }
                /* Duplicate return node #18. Try simplifying control flow for better match */
                return var_v0;
            }
        }
        return var_v0;
    }
block_5:
    return -1;
}
#else
INCLUDE_ASM("asm/nonmatchings/132D30", func_801DF204_ovl_101CE0);
#endif

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern u8 D_8018F481;
extern s32 D_80193BD8;
extern s32 D_80193BF2;
extern s32 D_80193BF3;
extern s32 D_80195578;
extern s32 D_80195592;
extern s32 D_80195593;
extern s32 D_801971F2;

u8 func_801DF34C_ovl_101CE0(void *arg0) {
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a3;
    u16 *var_v0;
    u32 var_a1;
    u8 *var_a2;
    u8 temp_a1;
    u8 temp_v1;
    u8 temp_v1_4;
    u8 var_t0;

    var_t0 = 0;
    var_a3 = 0;
    do {
        temp_a1 = FIELD(arg0, u8, 4);
        temp_v1 = *((temp_a1 * 0x19) + &D_801971F2 + var_a3);
        if ((temp_v1 != 0) && ((s32) temp_v1 < 0x64)) {
            if (temp_a1 < 0x1EU) {
                temp_v1_2 = temp_v1 * 0x38;
                if ((*(&D_80193BD8 + temp_v1_2) != 0) && !(*(&D_80193BF3 + temp_v1_2) & 4)) {
                    var_a2 = temp_v1_2 + &D_80193BF2;
                    var_v0 = temp_v1_2 + (&D_80193BF2 - 0x1A);
                    goto block_10;
                }
            } else {
                temp_v1_3 = temp_v1 * 0x34;
                if ((*(&D_80195578 + temp_v1_3) != 0) && !(*(&D_80195593 + temp_v1_3) & 4)) {
                    var_a2 = temp_v1_3 + &D_80195592;
                    var_v0 = temp_v1_3 + (&D_80195592 - 0x1A);
block_10:
                    if (*var_v0 != 0) {
                        var_a1 = 0x64;
                        if ((u32) (D_8018F481 - 0x3F) < 2U) {
                            var_a1 = 0x32;
                        }
                        temp_v1_4 = *var_a2;
                        if (temp_v1_4 < var_a1) {
                            *var_a2 = temp_v1_4 + 1;
                        }
                        if (var_t0 < *var_a2) {
                            var_t0 = *var_a2;
                        }
                    }
                }
            }
        }
        var_a3 += 1;
    } while (var_a3 < 5);
    return var_t0;
}
#else
INCLUDE_ASM("asm/nonmatchings/132D30", func_801DF34C_ovl_101CE0);
#endif

INCLUDE_ASM("asm/nonmatchings/132D30", func_801DF4A0_ovl_101CE0);
