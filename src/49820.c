#include "common.h"

/* 49820 */

typedef struct {
    u8 b[0xA8];
} SceneSlot;

extern u8 D_8018F380_ovl_040E80[];
extern u8 D_801A07D0[];
extern SceneSlot D_800E82CA[];

s32 func_80077314(void *p);
void func_80079618();
/* --- end decls --- */

u8 *func_80173920_ovl_040E80(void) {
    return D_8018F380_ovl_040E80;
}

INCLUDE_ASM("asm/nonmatchings/49820", func_8017392C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/49820", func_80173A18_ovl_040E80);

void func_80173AC4_ovl_040E80(void) {
}

void func_80173ACC_ovl_040E80(void) {
    s32 i = func_80077314(D_801A07D0);

    if (i >= 0) {
        D_800E82CA[i].b[0] |= 2;
    }
    func_80079618(-0x11);
}
