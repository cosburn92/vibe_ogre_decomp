#include "common.h"

/* 42C30 */

extern u8 D_80187020_ovl_040E80;
extern u8 D_80187021_ovl_040E80;
/* --- end decls --- */

u8 func_8016CD30_ovl_040E80(void) {
    return D_80187020_ovl_040E80;
}

u8 func_8016CD3C_ovl_040E80(void) {
    u8 v = D_80187021_ovl_040E80;

    D_80187021_ovl_040E80 = 0;
    return v;
}

void func_8016CD50_ovl_040E80(u8 a) {
    D_80187020_ovl_040E80 = a;
}

/* Sets the mode; a change also records mode + 1 as pending */
void func_8016CD5C_ovl_040E80(u8 a) {
    if (D_80187020_ovl_040E80 != a) {
        D_80187021_ovl_040E80 = a + 1;
    }
    D_80187020_ovl_040E80 = a;
}
