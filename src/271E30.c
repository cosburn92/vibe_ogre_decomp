#include "common.h"

/* 271E30 */

typedef struct {
    u8 unk00[0x30];
    s32 w30;
    s32 w34;
    s32 w38;
    s32 w3C;
} Task271;

extern s32 D_80220F68_ovl_25EE90;

Task271 *func_8020DF00_ovl_25EE90(void *fn);
s32 func_8021DACC_ovl_25EE90(u16 msg, u8 *o);
void func_8021D2AC_ovl_25EE90(void);
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
u8 *func_80217460_ovl_25EE90(s32 id);
void func_8020DC80_ovl_25EE90(u16 state);
s32 func_8021B500_ovl_25EE90(u16 msg, u8 *o);
/* --- end decls --- */

void func_8021D280_ovl_25EE90(s32 a) {
    D_80220F68_ovl_25EE90 = a;
    func_8020DF00_ovl_25EE90(func_8021DACC_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/271E30", func_8021D2AC_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/271E30", func_8021D7C4_ovl_25EE90);

/* Effect message handler: spawns effect 0x6E with colour (A, B, C, D) */
s32 func_8021DACC_ovl_25EE90(u16 msg, u8 *o) {
    s32 r = 0;

    if (msg == 0x100) {
        u8 *e;

        FIELD(o, s32, 0x44) = D_80220F68_ovl_25EE90;
        e = func_80217460_ovl_25EE90(0x6E);
        FIELD(o, u8 *, 0x40) = e;
        FIELD(e, s32, 0x10) = FIELD(o, s32, 0x44);
        FIELD(FIELD(o, u8 *, 0x40), u16, 0xA) |= 0x2000;
        FIELD(o, s16, 0x4C) = 0;
        FIELD(o, s16, 0x4E) = 0xFF;
        FIELD(o, s16, 0x50) = 0x40;
        FIELD(o, s16, 0x52) = 0x40;
        func_8020DC80_ovl_25EE90(0x1000);
    } else {
        r = func_8021B500_ovl_25EE90(msg, o);
    }
    return r;
}

void func_8021DB6C_ovl_25EE90(s16 a, s32 b, s32 c, s32 d) {
    Task271 *t = func_8020DF00_ovl_25EE90(func_8021D2AC_ovl_25EE90);

    t->w30 = b;
    t->w34 = c;
    t->w38 = d;
    t->w3C = a;
}
