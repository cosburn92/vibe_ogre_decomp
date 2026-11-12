#include "common.h"

extern u8 gChaosFrame;
extern u8 D_80197810_ovl_040E80[][6];
extern u16 gDate[];
extern u8 D_80193686_ovl_040E80[];
extern u8 D_80195560_ovl_040E80[][0x34];
extern u16 D_801953F4_ovl_040E80[];
extern u8 D_801971F0_ovl_040E80[][0x19];
extern u8 D_801969B8_ovl_040E80[][0xB];

void func_8016FDB0_ovl_040E80(s8 delta) {
    u8 *p = &gChaosFrame;
    s16 v = *p;

    v += delta;
    if (v < 0) {
        *p = 0;
    } else if (v > 100) {
        *p = 100;
    } else {
        *p = v;
    }
}

/* Appends (id, today's date) to the first free slot of a 121-entry log. */
void func_8016FDFC_ovl_040E80(u8 id) {
    s16 i;

    for (i = 0; i < 121; i++) {
        u8 *e = D_80197810_ovl_040E80[i];
        if (e[0] == 0xFF) {
            e[0] = id;
            *(u16 *)(e + 2) = gDate[0];
            e[4] = ((u8 *)gDate)[2];
            e[5] = ((u8 *)gDate)[3];
            return;
        }
    }
}

void ProfileFlagSet(s32 flag, s32 value) {
    if (value == 1) {
        D_80193686_ovl_040E80[flag / 8] |= 1 << (flag % 8);
    } else {
        D_80193686_ovl_040E80[flag / 8] &= ~(1 << (flag % 8));
    }
}

s32 ProfileFlagTest(s16 flag) {
    s32 negate = 0;

    if (flag < 0) {
        flag = -flag;
        negate = 1;
    }
    if (!((D_80193686_ovl_040E80[flag / 8] >> (flag % 8)) & 1)) {
        return negate;
    }
    return 1 - negate;
}

s32 func_8016FF5C_ovl_040E80(u8 a, u8 b) {
    if (a == b) {
        return 1;
    }
    if ((u8)(b - 0x51) < 3 && (u8)(a - 0x51) < 3) {
        return 1;
    }
    if ((u8)(b - 0x54) < 2 && (u8)(a - 0x54) < 2) {
        return 1;
    }
    if ((u8)(b - 0x56) < 2 && (u8)(a - 0x56) < 2) {
        return 1;
    }
    if ((u8)(b - 0x5F) < 2 && (u8)(a - 0x5F) < 2) {
        return 1;
    }
    if ((u8)(b - 0x63) < 2 && (u8)(a - 0x63) < 2) {
        return 1;
    }
    return 0;
}

/* Clears the enemy characters, squads and legions. */
void func_80170030_ovl_040E80(void) {
    s16 i;

    for (i = 1; i < 99; i++) {
        bzero(D_80195560_ovl_040E80[i], 0x34);
    }
    for (i = 0; i < 120; i++) {
        D_801953F4_ovl_040E80[i] = 0;
    }
    for (i = 30; i < 50; i++) {
        bzero(D_801971F0_ovl_040E80[i], 0x19);
    }
    for (i = 0; i < 10; i++) {
        if (D_801969B8_ovl_040E80[i][1] & 0x80) {
            bzero(D_801969B8_ovl_040E80[i], 0xB);
        }
    }
}
