#include "common.h"
#include "heap.h"
#include "scene.h"

/* 49820 */

typedef struct {
    u8 b[0xA8];
} SceneSlot;

extern u8 D_8018F380_ovl_040E80[];
extern u8 D_801A07D0[];
extern SceneSlot D_800E82CA[];

s32 func_80077314(void *p);
void func_80079618();
extern s32 D_80190F20_ovl_040E80;
extern u8 *D_801977CC_ovl_040E80;
extern u8 *D_800C4BB8;
extern u16 D_800C4C26;
void func_80089BC0(void);
void _bcopy(const void *src, void *dst, s32 n);
void func_80073164(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);
s32 func_80076F5C(s32 a, void *b, s32 c, s32 d, s32 e, s32 f, s32 g);
extern s32 D_801951A4_ovl_040E80;
/* --- end decls --- */

u8 *func_80173920_ovl_040E80(void) {
    return D_8018F380_ovl_040E80;
}

void func_8017392C_ovl_040E80(void) {
    func_80073164(0, 1, 1, 0x80, 1, 0x80, 0x2000);
    D_801977CC_ovl_040E80 = HMallocBack(0x25800);
    D_80190F20_ovl_040E80 = func_80076F5C(0xC000, D_801A07D0, 0, 0, 0x13F, 0xEF, 0xF000);
    D_800E82C8[D_80190F20_ovl_040E80].unk88 = D_801951A4_ovl_040E80;
    D_800E82C8[D_80190F20_ovl_040E80].unk8B |= 1;
}

/* Copies the current frame buffer into the capture buffer if the scene asked for it */
void func_80173A18_ovl_040E80(void) {
    func_80089BC0();
    if (D_800E82C8[D_80190F20_ovl_040E80].unk8B & 2) {
        _bcopy(D_800C4BB8, D_801977CC_ovl_040E80, 0x25800);
        D_800E82C8[D_80190F20_ovl_040E80].flags2 |= 2;
        D_800C4C26 = 0xFFFE;
    }
}

void func_80173AC4_ovl_040E80(void) {
}

void func_80173ACC_ovl_040E80(void) {
    s32 i = func_80077314(D_801A07D0);

    if (i >= 0) {
        D_800E82CA[i].b[0] |= 2;
    }
    func_80079618(-0x11);
}
