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

extern s32 D_80220F6C_ovl_25EE90;
void func_8020DFB8_ovl_25EE90(void);
s32 func_8020DCAC_ovl_25EE90(void *t, u16 a);
void *func_8021A998_ovl_25EE90(s32 a, s32 b);
s16 func_801F7128(u8 c);
void func_80207CE4(u8 *p);
void func_8020E0B4_ovl_25EE90(s32 a, s32 b);
s32 func_801C8B84(u8 *u);
u8 *func_801C8FE8(s32 i);
void func_801F9DFC(void *a, u8 b, s32 c);
extern u8 D_800EB240[];
extern u8 D_80220F6A_ovl_25EE90;
extern void *D_80220F70_ovl_25EE90;
s32 func_80218D68_ovl_25EE90();
s32 func_8021A9C8_ovl_25EE90();
void func_8021DB6C_ovl_25EE90(s16 a, s32 b, s32 c, s32 d);

s32 func_8021D7C4_ovl_25EE90(u16 msg, u8 *o) {
    u8 *t;
    s32 c;
    s32 *g;

    switch (msg) {
        case 0x101:
            func_8020DFB8_ovl_25EE90();
            break;
        case 0x100:
            FIELD(o, s32, 4) = D_80220F68_ovl_25EE90;
            FIELD(o, s32, 8) = D_80220F6C_ovl_25EE90;
            func_8020DC80_ovl_25EE90(0x1000);
            break;
        case 0x1000:
            func_80207CE4(FIELD(o, u8 *, 4));
            func_8020E0B4_ovl_25EE90(-1, 0x1001);
            break;
        case 0x1001:
        case 0x1002:
            g = &D_80220F68_ovl_25EE90;
            if (func_801F7128(*FIELD(o, u8 *, 4)) != 0) {
                ((f32 *)g)[0] = 95.0f;
            } else {
                ((f32 *)g)[0] = -95.0f;
            }
            g[3] = 30;
            g[4] = 0x40;
            g[2] = 0;
            g[5] = 6;
            ((f32 *)g)[1] = -1.0f;
            t = (u8 *)func_8020DF00_ovl_25EE90(func_80218D68_ovl_25EE90);
            func_8020DCAC_ovl_25EE90(t, 0x1007);
            FIELD(o, u8 *, 0x18) = t;
            FIELD(o, void *, 0x20) = func_8021A998_ovl_25EE90(func_801C8B84(func_801C8FE8(*FIELD(o, u8 *, 4))), 20);
            FIELD(o, s32, 0x14) = 0;
            FIELD(o, s32, 0x10) = 0;
            FIELD(o, s32, 0xC) = 0;
            c = 0x50;
            switch (FIELD(o, s16, 0)) {
                case 0x2D:
                    c = 0x51;
                    break;
                case 0x2E:
                    c = 0x52;
                    break;
            }
            func_801F9DFC(D_800EB240, *FIELD(o, u8 *, 4), c);
            func_8020DC80_ovl_25EE90(0x1003);
            break;
        case 0x1003:
            if (func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x18), 0x1005) != 0) {
                func_8020DC80_ovl_25EE90(0x1004);
            }
            break;
        case 0x1004:
            D_80220F6A_ovl_25EE90 = *FIELD(o, u8 *, 4);
            D_80220F6C_ovl_25EE90 = FIELD(o, s32, 8);
            D_80220F70_ovl_25EE90 = func_8021DB6C_ovl_25EE90;
            FIELD(o, void *, 0x1C) = (void *)func_8020DF00_ovl_25EE90(func_8021A9C8_ovl_25EE90);
            func_8020DC80_ovl_25EE90(0x1005);
            break;
        case 0x1005:
            if (func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x1C), 0x1003) != 0) {
                func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x1C), 0x101);
                func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x18), 0x1008);
                func_8020DC80_ovl_25EE90(0x1006);
            }
            break;
        case 0x1006:
            FIELD(o, s32, 0x10)++;
            if (FIELD(o, s32, 0x14) == 0 && FIELD(o, s32, 0x10) >= FIELD(o, s32, 0xC) - 20) {
                func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x20), 0x1003);
                FIELD(o, s32, 0x14) = 1;
            }
            if (func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x18), 0x1006) != 0) {
                func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x18), 0x101);
                func_8020DC80_ovl_25EE90(0x1007);
            }
            break;
        case 0x1007:
            func_8020DC80_ovl_25EE90(0x101);
            break;
    }
    return 0;
}

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
