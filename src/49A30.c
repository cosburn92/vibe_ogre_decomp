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

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 _bcopy(s32 *, void *, s32);
extern s32 D_8018F3A0_ovl_040E80;

/* Fills quad v (four 16-byte vertices from the template) for the screen rectangle (x0, y0) -
 * (x1, y1): centred coordinates and texture coordinates spanning the rectangle */
#ifdef NON_MATCHING
/* 71 vs 70: the original keeps copies of x0/x1 (s5/s6) and compares the sign-extended differences, likely an inline span helper */
void func_80174138_ovl_040E80(void *v, s16 x0, s16 y0, s16 x1, u16 y1) {
    s32 w, h;
    s16 l, t, r, b;

    _bcopy(&D_8018F3A0_ovl_040E80, v, 0x40);
    w = (x1 - x0 > 0) ? x1 - x0 : x0 - x1;
    h = ((s16)y1 - y0 > 0) ? y1 - y0 : y0 - y1;
    w = (w - 1) << 6;
    h = (h - 1) << 6;
    r = 0xA0 - x1;
    b = 0x78 - y1;
    t = 0x78 - y0;
    l = 0xA0 - x0;
    FIELD(v, s16, 0x12) = t;
    FIELD(v, s16, 0x22) = t;
    FIELD(v, s16, 0) = r;
    FIELD(v, s16, 2) = b;
    FIELD(v, s16, 0xA) = h;
    FIELD(v, s16, 0x10) = r;
    FIELD(v, s16, 0x20) = l;
    FIELD(v, s16, 0x28) = w;
    FIELD(v, s16, 0x30) = l;
    FIELD(v, s16, 0x32) = b;
    FIELD(v, s16, 0x38) = w;
    FIELD(v, s16, 0x3A) = h;
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
