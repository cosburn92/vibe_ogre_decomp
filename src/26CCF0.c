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

INCLUDE_ASM("asm/nonmatchings/26CCF0", func_8021816C_ovl_25EE90);

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
