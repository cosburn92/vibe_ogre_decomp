#include "common.h"

/* 26CCF0 */

typedef struct {
    u8 unk00[0x48];
    s32 w48;
    s32 w4C;
    s32 w50;
} Task26C;

extern s32 D_80220F68_ovl_25EE90;

Task26C *func_8020DF00_ovl_25EE90(void *fn);
s32 func_80218AC0_ovl_25EE90(u16 msg, u8 *o);
void func_802182C4_ovl_25EE90(void);
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
u8 *func_80217460_ovl_25EE90(s32 id);
void func_8020DC80_ovl_25EE90(u16 state);
s32 func_8021B500_ovl_25EE90(u16 msg, u8 *o);
/* --- end decls --- */

void func_80218140_ovl_25EE90(s32 a) {
    D_80220F68_ovl_25EE90 = a;
    func_8020DF00_ovl_25EE90(func_80218AC0_ovl_25EE90);
}

typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 dir[3];
    /* 0x18 */ s32 t;
    /* 0x1C */ f32 len;
    /* 0x20 */ f32 speed;
    /* 0x24 */ u8 unk24[0xC];
    /* 0x30 */ f32 a[4];
    /* 0x40 */ f32 b[4];
    /* 0x50 */ f32 out[4];
} Path26C;
void func_80217C84_ovl_25EE90(s32 id, f32 *out);
f32 func_8020A3C8_ovl_25EE90(f32 *v);
void func_8020A2E0_ovl_25EE90(f32 *v, f32 s, f32 *out);
void func_80217E1C_ovl_25EE90(s32 n, f32 *a, f32 *b, f32 *out);

/* Sets up o's flight path from its position to target 0x28's: unit direction, length less 40
 * and the curve coefficients */
void func_8021816C_ovl_25EE90(u8 *o) {
    Path26C *p = FIELD(o, Path26C *, 0x3C);
    f32 to[3];

    p->pos[0] = FIELD(o, f32, 0xC);
    p->pos[1] = FIELD(o, f32, 0x10);
    p->pos[2] = FIELD(o, f32, 0x14);
    func_80217C84_ovl_25EE90(FIELD(o, s32, 0x28), to);
    p->dir[0] = to[0] - FIELD(o, f32, 0xC);
    p->dir[1] = to[1] - FIELD(o, f32, 0x10);
    p->dir[2] = to[2] - FIELD(o, f32, 0x14);
    p->len = func_8020A3C8_ovl_25EE90(p->dir);
    p->t = 0;
    p->speed = 10.0f;
    func_8020A2E0_ovl_25EE90(p->dir, 1.0f / p->len, p->dir);
    p->a[0] = 0;
    p->b[0] = 0;
    p->b[3] = 0;
    p->a[3] = p->len;
    p->a[1] = p->len / 6.0f;
    p->a[2] = p->len / 2.0f;
    p->b[2] = p->len / 6.0f;
    p->b[1] = -p->len / 20.0f;
    func_80217E1C_ovl_25EE90(4, p->a, p->b, p->out);
    p->len = p->len - 40.0f;
}

INCLUDE_ASM("asm/nonmatchings/26CCF0", func_802182C4_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/26CCF0", func_802187A4_ovl_25EE90);

/* Effect message handler: spawns effect 0x28 with colour (A, B, C, D) */
s32 func_80218AC0_ovl_25EE90(u16 msg, u8 *o) {
    s32 r = 0;

    if (msg == 0x100) {
        u8 *e;

        FIELD(o, s32, 0x44) = D_80220F68_ovl_25EE90;
        e = func_80217460_ovl_25EE90(0x28);
        FIELD(o, u8 *, 0x40) = e;
        FIELD(e, s32, 0x10) = FIELD(o, s32, 0x44);
        FIELD(FIELD(o, u8 *, 0x40), u16, 0xA) |= 0x2000;
        FIELD(o, s16, 0x4C) = 0xFF;
        FIELD(o, s16, 0x4E) = 0x40;
        FIELD(o, s16, 0x50) = 0x80;
        FIELD(o, s16, 0x52) = 0;
        func_8020DC80_ovl_25EE90(0x1000);
    } else {
        r = func_8021B500_ovl_25EE90(msg, o);
    }
    return r;
}

void func_80218B64_ovl_25EE90(s16 a, s32 b, s32 c) {
    Task26C *t = func_8020DF00_ovl_25EE90(func_802182C4_ovl_25EE90);

    t->w48 = b;
    t->w4C = c;
    t->w50 = a;
}
