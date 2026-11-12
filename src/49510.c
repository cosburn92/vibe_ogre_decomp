#include "common.h"

extern u8 D_801936B0_ovl_040E80[];
extern u8 D_80196AEC_ovl_040E80;
extern u8 D_801936E0_ovl_040E80;
extern u8 D_801951A0_ovl_040E80;
extern u8 D_80197AFC_ovl_040E80;
extern u8 D_80197AE6_ovl_040E80;
extern s32 D_801971E8_ovl_040E80;
extern u8 D_801969B4_ovl_040E80;
extern s32 D_80193674_ovl_040E80;

void func_80173610_ovl_040E80(void) {
    D_80196AEC_ovl_040E80 = 0;
    D_801936E0_ovl_040E80 = 0;
    D_801951A0_ovl_040E80 = 0;
    D_80197AFC_ovl_040E80 = 0;
    D_80197AE6_ovl_040E80 = 0;
    D_801971E8_ovl_040E80 = 0;
    D_801969B4_ovl_040E80 = 0;
    D_80193674_ovl_040E80 = 0;
    bzero(&D_801936B0_ovl_040E80[2], 5);
}

void func_80173674_ovl_040E80(u8 mode) {
    D_801936E0_ovl_040E80 = mode;
    if (mode == 1) {
        if (!(D_80196AEC_ovl_040E80 & 2)) {
            D_801971E8_ovl_040E80 = 0;
        }
    } else if (mode == 2) {
        if (!(D_80196AEC_ovl_040E80 & 4)) {
            D_80193674_ovl_040E80 = 0;
        }
    }
}
