#include "common.h"

extern u8 gFlags[];
extern u8 D_80197AE7_ovl_040E80[];
extern s32 D_80196F58_ovl_040E80;
extern u8 D_801951A1_ovl_040E80;

void func_80186160_ovl_040E80(void) {
    gFlags[0] |= 1;
}

void func_80186178_ovl_040E80(void) {
    gFlags[0] &= ~1;
}

void FlagSet(s32 flag, s32 value) {
    if (value) {
        gFlags[flag / 8] |= 1 << (flag % 8);
    } else {
        gFlags[flag / 8] &= ~(1 << (flag % 8));
    }
}

s32 FlagGet(s32 flag) {
    return (gFlags[flag / 8] >> (flag % 8)) & 1;
}

s32 func_80186240_ovl_040E80(s32 flag) {
    if (flag == -1) {
        return 1;
    }
    return ((D_80197AE7_ovl_040E80[flag / 8] >> (flag % 8)) & 1) ^ 1;
}

void func_80186284_ovl_040E80(s32 value) {
    D_80196F58_ovl_040E80 = value;
}

void func_80186290_ovl_040E80(void) {
    D_801951A1_ovl_040E80 |= 1;
}

void func_801862A8_ovl_040E80(void) {
    bzero(D_80197AE7_ovl_040E80, 8);
}
