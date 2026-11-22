#include "common.h"

/* 2A7060 */

extern u8 D_80239140_ovl_29A4C0[];
extern u8 D_8023914C_ovl_29A4C0[];
void func_8020DFB8(void);
void func_8020DC80(u16 state);
void func_8020E0B4(s32 a, s32 b);
void func_8020B538(s32 a, u8 *s);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/2A7060", func_80237830_ovl_29A4C0);

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern u8 D_8020F390[];
extern s32 D_80239130_ovl_29A4C0[2];

/* Message handler for two blinking sprites (objects D_80239130[0..1] of ctx): 0 resets them,
 * 2 toggles the blink and moves each one left a pixel on its visible frames */
void func_80237B84_ovl_29A4C0(u16 msg, u8 *ctx) {
    u32 i;
    u8 *o;

    switch (msg) {
        case 0:
            for (i = 0; i < 2; i++) {
                FIELD(FIELD(ctx, u8 **, 0x58)[D_80239130_ovl_29A4C0[i]], void *, 0) = D_8020F390;
                {
                    u8 *p = FIELD(ctx, u8 **, 0x58)[D_80239130_ovl_29A4C0[i]];

                    FIELD(p, u16, 0x30) = 0;
                    FIELD(p, u16, 0x32) = 0;
                    FIELD(p, s16, 0x38) = 0;
                    FIELD(p, s16, 0x34) = FIELD(p, u16, 0x30) + 15;
                    FIELD(p, s16, 0x36) = FIELD(p, u16, 0x32) + 15;
                }
            }
            break;
        case 1:
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                o = FIELD(ctx, u8 **, 0x58)[D_80239130_ovl_29A4C0[i]];
                FIELD(o, u16, 0x38) = (FIELD(o, u16, 0x38) + 1) & 1;
                if (FIELD(o, u16, 0x38) != 0) {
                    FIELD(o, s16, 0x34) = FIELD(o, s16, 0x30)-- + 14;
                }
            }
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/2A7060", func_80237C90_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/2A7060", func_80237E4C_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/2A7060", func_80238004_ovl_29A4C0);

s32 func_8023823C_ovl_29A4C0(u16 msg) {
    switch (msg) {
        case 0x101:
            func_8020DFB8();
            break;
        case 0x100:
            func_8020DC80(0x1010);
            break;
        case 0x1010:
            func_8020E0B4(10, 0x1100);
            break;
        case 0x1100:
            func_8020B538(4, D_80239140_ovl_29A4C0);
            func_8020E0B4(10, 0x1200);
            break;
        case 0x1200:
            func_8020B538(4, D_8023914C_ovl_29A4C0);
            func_8020E0B4(10, 0x101);
            break;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/2A7060", func_8023830C_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/2A7060", func_8023841C_ovl_29A4C0);
