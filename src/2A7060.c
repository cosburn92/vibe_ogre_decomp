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

void func_8023841C_ovl_29A4C0(u16 msg, u8 *ctx);
extern f32 D_80220F6C;
extern f32 D_80220F70;
extern f32 D_80220F74;
extern u8 D_80220EE0[];
u8 *func_80214C84(s32 size, void (*fn)(u16, u8 *));
void func_8020A4A8(u8 *a, u8 *b);
void func_8020A5A0(u8 *a, u8 *b);
void func_8020D814(u8 *o);
void func_8020D86C(u8 *o, s32 a, s32 b);
void func_8020E0E4(u8 *o, s32 a, s32 b);

/* Scene script for the drifting sprites (func_8023841C): sets up the camera, spawns the sprite
 * object and steps through its states */
s32 func_80237E4C_ovl_29A4C0(u16 msg, u8 *ctx) {
    u8 *o;
    u8 *p;

    switch (msg) {
        case 0x101:
            if (FIELD(ctx, u8 *, 0x10) != NULL) {
                func_8020D814(FIELD(ctx, u8 *, 0x10));
            }
            func_8020DFB8();
            break;
        case 0x100:
            FIELD(ctx, f32, 0) = D_80220F6C;
            FIELD(ctx, f32, 4) = D_80220F70;
            FIELD(ctx, f32, 8) = D_80220F74;
            FIELD(ctx, void *, 0x10) = NULL;
            FIELD(ctx, s32, 0xC) = 0;
            func_8020DC80(0x1000);
            break;
        case 0x1000:
            o = func_80214C84(0x1AC, func_8023841C_ovl_29A4C0);
            FIELD(ctx, u8 *, 0x10) = o;
            FIELD(o, u16, 0xA) |= 0x1000;
            FIELD(FIELD(ctx, u8 *, 0x10), s32, 0xC) = -30000;
            p = FIELD(ctx, u8 *, 0x10) + 0x1C;
            func_8020A4A8(D_80220EE0, p);
            func_8020A5A0(p, ctx);
            func_8020E0E4(FIELD(ctx, u8 *, 0x10), 0x1A, 0x1002);
            break;
        case 0x1002:
            FIELD(FIELD(ctx, u8 *, 0x10), u16, 0xA) |= 0x2000;
            func_8020DC80(0x1003);
        case 0x1003:
            if (FIELD(ctx, s32, 0xC) != 0) {
                func_8020DC80(0x1005);
            }
            break;
        case 0x1004:
            FIELD(ctx, s32, 0xC) = 1;
            break;
        case 0x1005:
            FIELD(FIELD(ctx, u8 *, 0x10), u16, 0xA) &= ~0x2000;
            func_8020D86C(FIELD(ctx, u8 *, 0x10), 0x2C, 0x3A);
            func_8020DC80(0x1006);
            break;
    }
    return 0;
}

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

extern s32 D_80239158_ovl_29A4C0[2];

/* Message handler for two drifting sprites: 0 resets them, 2 moves each one pixel left and down */
void func_8023830C_ovl_29A4C0(u16 msg, u8 *ctx) {
    u32 i;

    switch (msg) {
        case 0:
            for (i = 0; i < 2; i++) {
                FIELD(FIELD(ctx, u8 **, 0x58)[D_80239158_ovl_29A4C0[i]], void *, 0) = D_8020F390;
                {
                    u8 *p = FIELD(ctx, u8 **, 0x58)[D_80239158_ovl_29A4C0[i]];

                    FIELD(p, u16, 0x30) = 0;
                    FIELD(p, u16, 0x32) = 0;
                    FIELD(p, s16, 0x34) = FIELD(p, u16, 0x30) + 15;
                    FIELD(p, s16, 0x36) = FIELD(p, u16, 0x32) + 15;
                }
            }
            break;
        case 1:
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                u8 *p = FIELD(ctx, u8 **, 0x58)[D_80239158_ovl_29A4C0[i]];

                FIELD(p, u16, 0x30)--;
                FIELD(p, u16, 0x32)++;
                FIELD(p, s16, 0x34) = FIELD(p, u16, 0x30) + 15;
                FIELD(p, s16, 0x36) = FIELD(p, u16, 0x32) + 15;
            }
            break;
    }
}

extern s32 D_80239160_ovl_29A4C0[2];

/* Message handler for two drifting sprites: 0 resets them, 2 moves each one pixel left and down */
void func_8023841C_ovl_29A4C0(u16 msg, u8 *ctx) {
    u32 i;

    switch (msg) {
        case 0:
            for (i = 0; i < 2; i++) {
                FIELD(FIELD(ctx, u8 **, 0x58)[D_80239160_ovl_29A4C0[i]], void *, 0) = D_8020F390;
                {
                    u8 *p = FIELD(ctx, u8 **, 0x58)[D_80239160_ovl_29A4C0[i]];

                    FIELD(p, u16, 0x30) = 0;
                    FIELD(p, u16, 0x32) = 0;
                    FIELD(p, s16, 0x34) = FIELD(p, u16, 0x30) + 15;
                    FIELD(p, s16, 0x36) = FIELD(p, u16, 0x32) + 15;
                }
            }
            break;
        case 1:
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                u8 *p = FIELD(ctx, u8 **, 0x58)[D_80239160_ovl_29A4C0[i]];

                FIELD(p, u16, 0x30)--;
                FIELD(p, u16, 0x32)++;
                FIELD(p, s16, 0x34) = FIELD(p, u16, 0x30) + 15;
                FIELD(p, s16, 0x36) = FIELD(p, u16, 0x32) + 15;
            }
            break;
    }
}
