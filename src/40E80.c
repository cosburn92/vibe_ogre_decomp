#include "common.h"

/* ovl_040E80 (40E80): unit roster and strategy helpers */

typedef struct {
    /* 0x00 */ u8 unk00[0x10];
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12[0x22];
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 unk35[3];
} Unit38; /* size 0x38 */

typedef struct {
    /* 0x00 */ u8 id;
    /* 0x01 */ u8 flags;
    /* 0x02 */ u8 unk02[0x17];
} Entry19; /* size 0x19 */

extern char *gStrategyNames[];
extern u8 D_80186FBC_ovl_040E80[];
extern u16 D_80190EBC_ovl_040E80[];
extern u16 D_80190F82_ovl_040E80;
extern u8 D_801936AA_ovl_040E80;
extern u8 D_801936AB_ovl_040E80;
extern u16 D_80193AC0_ovl_040E80[][2];
extern Unit38 D_80193BC0_ovl_040E80[];
extern u16 D_8019532C_ovl_040E80[];
extern u16 D_801953F2_ovl_040E80;
extern u8 gLegions[][11]; /* 10 legions x 11 bytes */
extern u8 gPlayTime[];
extern u16 D_80196B00_ovl_040E80[][2];
extern Entry19 gSquads[]; /* 25 bytes per squad */
extern u8 D_80197710_ovl_040E80[];
extern u8 D_801977D8_ovl_040E80[];

void bzero(void *p, s32 n);
void _bcopy(void *src, void *dst, s32 n);
s32 ProfileFlagTest(s16 flag);
u8 func_8016BF80_ovl_040E80(void);

void func_8016AF80_ovl_040E80(void) {
}

void func_8016AF88_ovl_040E80(void) {
}

void func_8016AF90_ovl_040E80(u8 *out) {
    s16 i;
    s32 n;

    D_80193BC0_ovl_040E80[func_8016BF80_ovl_040E80()].unk10 = 0;
    i = 1;
    _bcopy(&D_80193BC0_ovl_040E80[func_8016BF80_ovl_040E80()], out + 8, 0x11);
    _bcopy(gPlayTime, out + 4, 4);
    out[2] = D_801936AA_ovl_040E80;
    out[1] = D_801936AB_ovl_040E80;
    n = 0;
    do {
        if (!ProfileFlagTest(i)) {
            break;
        }
        i++;
        n++;
    } while (i < 5);
    out[0] = n;
}

char *StrategyGetName(u8 i) {
    return gStrategyNames[i];
}

u8 func_8016B088_ovl_040E80(u8 a, u8 b, u8 c, u8 d, u8 e) {
    u8 buf[5];
    u8 *p;
    u32 i;
    s32 j;

    buf[0] = a;
    buf[1] = b;
    buf[2] = c;
    buf[3] = d;
    buf[4] = e;
    for (i = 0; i < 7; i++) {
        p = buf;
        for (j = 0; j < 5; j++) {
            if (*p++ == D_80186FBC_ovl_040E80[i]) {
                return D_80186FBC_ovl_040E80[i];
            }
        }
    }
    return 7;
}

u8 func_8016B0F4_ovl_040E80(u8 which, u8 k) {
    s16 v;
    u16 step;
    s16 n;

    if (which) {
        step = D_801953F2_ovl_040E80 / 3;
        v = D_8019532C_ovl_040E80[k];
    } else {
        step = D_80190F82_ovl_040E80 / 3;
        v = D_80190EBC_ovl_040E80[k];
    }
    n = 0;
    while (v > 0) {
        v -= step;
        n++;
    }
    if (n >= 4) {
        n = 3;
    }
    return n;
}

INCLUDE_ASM("asm/nonmatchings/40E80", func_8016B198_ovl_040E80);

u16 func_8016B6FC_ovl_040E80(u16 id) {
    s32 i;
    u16 (*p)[2] = D_80196B00_ovl_040E80;

    for (i = 0; i < 0x116; i++) {
        if (p[i][0] == id) {
            return i;
        }
    }
    return 0x1FF;
}

u16 func_8016B738_ovl_040E80(u16 id) {
    s32 i;
    u16 (*p)[2] = D_80193AC0_ovl_040E80;

    for (i = 0; i < 0x28; i++) {
        if (p[i][0] == id) {
            return i;
        }
    }
    return 0x1FF;
}

INCLUDE_ASM("asm/nonmatchings/40E80", func_8016B774_ovl_040E80);

void func_8016BA10_ovl_040E80(u8 mode) {
    s32 i;
    u8 (*p)[11] = gLegions;

    for (i = 0; i < 10; i++) {
        switch (mode) {
            case 0:
                p[i][10] -= 5;
                break;
            case 1:
                p[i][10] += 5;
                break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/40E80", func_8016BA6C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/40E80", func_8016BD20_ovl_040E80);

const u32 D_8018FEAC_ovl_040E80[] = { 0x01E34336, 0x01E3497C, 0x01E34F34 };
const u32 D_8018FEB8_ovl_040E80 = 0;
const u32 D_8018FEBC_ovl_040E80[] = { 0x0E446561, 0x74681063, 0x42616861, 0x6D75740F, 0 };

u8 func_8016BF80_ovl_040E80(void) {
    s32 i;

    for (i = 0; i < 100; i++) {
        u8 v = D_80193BC0_ovl_040E80[i].unk11;

        if (v >= 0x51 && v < 0x54) {
            return i;
        }
    }
    return 0xFF;
}

/* Lowest free id (1-based) among the flagged entries */
u8 func_8016BFC0_ovl_040E80(void) {
    u8 used[30];
    s32 i;
    Entry19 *e = gSquads;

    bzero(used, 30);
    for (i = 0; i < 30; i++) {
        if (e[i].flags & 1) {
            used[e[i].id - 1] = 1;
        }
    }
    for (i = 0; i < 30; i++) {
        if (used[i] == 0) {
            break;
        }
    }
    return i + 1;
}

u8 func_8016C048_ovl_040E80(void) {
    u8 used[100];
    s32 i;
    Unit38 *u = D_80193BC0_ovl_040E80;

    bzero(used, 100);
    for (i = 1; i < 100; i++) {
        if (u[i].unk11 != 0) {
            used[u[i].unk34] = 1;
        }
    }
    for (i = 1; i < 100; i++) {
        if (used[i] == 0) {
            break;
        }
    }
    return i;
}

#ifdef NON_MATCHING
/* Index and value registers (a1/a2) are swapped. */
void func_8016C0C8_ovl_040E80(u8 id) {
    s32 i;
    s32 j = 0;
    s32 v;

    for (i = 0; i < 100; i++) {
        v = D_80197710_ovl_040E80[i];
        if (v == 0 && i != 0) {
            j = i;
            break;
        }
        if (D_80193BC0_ovl_040E80[v].unk11 == 0) {
            if (v != id) {
                j = i;
                break;
            }
        }
        if (v > 100) {
            j = i;
            break;
        }
    }
    D_80197710_ovl_040E80[(u8)j] = id;
}
#else
INCLUDE_ASM("asm/nonmatchings/40E80", func_8016C0C8_ovl_040E80);
#endif

void func_8016C150_ovl_040E80(u8 idx) {
    s32 max = 0;
    s32 i;
    s32 v;

    for (i = 0; i < 30; i++) {
        if ((gSquads[i].flags & 1) && i != idx) {
            v = D_801977D8_ovl_040E80[i];
            if (v < 30) {
                if (max < v) {
                    max = v;
                }
            }
        }
    }
    D_801977D8_ovl_040E80[idx] = max + 1;
}
