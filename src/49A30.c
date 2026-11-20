#include "common.h"

/* 49A30 */

extern u8 D_8018F481_ovl_040E80;
extern void *D_8018FDC0_ovl_040E80;
extern s32 D_801939C8_ovl_040E80;
extern s32 D_80197AF4_ovl_040E80;
extern f32 D_80196AF4_ovl_040E80;
extern f32 D_801977D0_ovl_040E80;

void func_8017BDC0_ovl_040E80(void);
void func_8017BF10_ovl_040E80(void);
void func_8017EE64_ovl_040E80(s32 a, u16 b, s16 c, s16 d, s16 e, s16 f);
void func_8017F490_ovl_040E80(void);
void func_8017BFB0_ovl_040E80(u16 a, u8 b, void *c, s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2, s16 x3, s16 y3);
void func_801841F4_ovl_040E80(void);
void func_80180BDC_ovl_040E80(void);
/* --- end decls --- */

void func_80173B30_ovl_040E80(u8 *p) {
    D_8018F481_ovl_040E80 = 0;
    *p = 0;
}

void func_80173B40_ovl_040E80(u8 *p) {
    D_8018F481_ovl_040E80 = *p;
}

void func_80173B50_ovl_040E80(u8 *p) {
    *p = D_8018F481_ovl_040E80;
}

void *func_80173B60_ovl_040E80(void *list) {
    void *old = D_8018FDC0_ovl_040E80;
    void *r;

    D_8018FDC0_ovl_040E80 = list;
    func_8017BDC0_ovl_040E80();
    r = D_8018FDC0_ovl_040E80;
    D_8018FDC0_ovl_040E80 = old;
    return r;
}

void *func_80173BA0_ovl_040E80(void *list) {
    void *old = D_8018FDC0_ovl_040E80;
    void *r;

    D_8018FDC0_ovl_040E80 = list;
    func_8017BF10_ovl_040E80();
    r = D_8018FDC0_ovl_040E80;
    D_8018FDC0_ovl_040E80 = old;
    return r;
}

void func_80173BE0_ovl_040E80(void *list, s32 a, u16 b, s16 c, s16 d, s16 e, s16 f) {
    void *old = D_8018FDC0_ovl_040E80;

    D_8018FDC0_ovl_040E80 = list;
    func_8017EE64_ovl_040E80(a, b, c, d, e, f);
    D_8018FDC0_ovl_040E80 = old;
}

void func_80173C54_ovl_040E80(void *list, u16 a, u8 b, void *c, s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2,
                              s16 x3, s16 y3) {
    void *old = D_8018FDC0_ovl_040E80;

    D_8018FDC0_ovl_040E80 = list;
    func_8017BFB0_ovl_040E80(a, b, c, x0, y0, x1, y1, x2, y2, x3, y3);
    D_8018FDC0_ovl_040E80 = old;
}

void func_80173D14_ovl_040E80(void *list) {
    void *old = D_8018FDC0_ovl_040E80;

    D_8018FDC0_ovl_040E80 = list;
    func_8017F490_ovl_040E80();
    D_8018FDC0_ovl_040E80 = old;
}

void func_80173D4C_ovl_040E80(void *list) {
    void *old = D_8018FDC0_ovl_040E80;

    D_8018FDC0_ovl_040E80 = list;
    func_801841F4_ovl_040E80();
    D_8018FDC0_ovl_040E80 = old;
}

void func_80173D84_ovl_040E80(void *list) {
    void *old = D_8018FDC0_ovl_040E80;

    D_8018FDC0_ovl_040E80 = list;
    func_80180BDC_ovl_040E80();
    D_8018FDC0_ovl_040E80 = old;
}

INCLUDE_ASM("asm/nonmatchings/49A30", func_80173DBC_ovl_040E80);

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 _bcopy(s32 *, void *, s32);         /* extern */
extern s32 D_8018F3A0_ovl_040E80;

void func_80174138_ovl_040E80(void *arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4) {
    s16 temp_a0;
    s16 temp_a1;
    s16 temp_a2;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v1;
    s32 var_v0;
    s32 var_v0_2;

    _bcopy(&D_8018F3A0_ovl_040E80, arg0, 0x40);
    if ((arg3 - arg1) > 0) {
        var_v0 = arg3 - arg1;
    } else {
        var_v0 = arg1 - arg3;
    }
    var_v0_2 = arg4 - arg2;
    if (((s16) arg4 - arg2) <= 0) {
        var_v0_2 = arg2 - arg4;
    }
    temp_a0 = 0xA0 - arg3;
    temp_a1 = 0x78 - arg4;
    temp_a2 = (var_v0_2 - 1) << 6;
    temp_v0 = 0x78 - arg2;
    temp_v1 = 0xA0 - arg1;
    FIELD(arg0, s16, 0x12) = temp_v0;
    FIELD(arg0, s16, 0x22) = temp_v0;
    temp_v0_2 = (var_v0 - 1) << 6;
    FIELD(arg0, s16, 0) = temp_a0;
    FIELD(arg0, s16, 2) = temp_a1;
    FIELD(arg0, s16, 0xA) = temp_a2;
    FIELD(arg0, s16, 0x10) = temp_a0;
    FIELD(arg0, s16, 0x20) = temp_v1;
    FIELD(arg0, s16, 0x28) = temp_v0_2;
    FIELD(arg0, s16, 0x30) = temp_v1;
    FIELD(arg0, s16, 0x32) = temp_a1;
    FIELD(arg0, s16, 0x38) = temp_v0_2;
    FIELD(arg0, s16, 0x3A) = temp_a2;
}
#else
INCLUDE_ASM("asm/nonmatchings/49A30", func_80174138_ovl_040E80);
#endif

INCLUDE_ASM("asm/nonmatchings/49A30", func_80174250_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/49A30", func_801758C0_ovl_040E80);

void func_801768D4_ovl_040E80(s32 w, s32 h, s32 x0, s32 y0, s32 x1, s32 y1) {
    D_801939C8_ovl_040E80 = x0;
    D_80197AF4_ovl_040E80 = y0;
    D_80196AF4_ovl_040E80 = (f32)(x1 - x0 + 1) / w;
    D_801977D0_ovl_040E80 = (f32)(y1 - y0 + 1) / h;
}

INCLUDE_ASM("asm/nonmatchings/49A30", func_80176948_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/49A30", func_80176C6C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/49A30", func_80176F90_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/49A30", func_801772C0_ovl_040E80);
