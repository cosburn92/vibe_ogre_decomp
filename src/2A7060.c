#include "common.h"

/* 2A7060 */

extern u8 D_80239140_ovl_29A4C0[];
extern u8 D_8023914C_ovl_29A4C0[];
void func_8020DFB8(void);
void func_8020DC80(u16 state);
void func_8020E0B4(s32 a, s32 b);
void func_8020B538(s32 a, u8 *s);
/* --- end decls --- */

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern f32 D_80220F68;
extern f32 D_80220F6C;
extern f32 D_80220F70;
extern u8 D_80220EE0[];
extern u8 D_800EB240[];
extern u8 D_800EB290[];
u8 *func_80214BE8(s32 id);
u8 *func_80214C84(s32 id, void (*fn)(u16, u8 *));
u8 *func_80216018(s32 id);
void func_8020A4A8(u8 *a, u8 *b);
void func_8020A5A0(u8 *a, u8 *b);
void func_8020D86C(u8 *o, s32 a, s32 b);
void func_8020D884(u8 *o);
void func_801C5938(void *bank, s32 se);
void func_8020E0B4(s32 a, s32 b);
void func_80237B84_ovl_29A4C0(u16 msg, u8 *ctx);

/* Event scene with the two blinking sprites (func_80237B84 at 0x50 and a second object at 0x54):
 * spawns them, waits for the cue (0x1009), then plays the follow-up objects */
s32 func_80237830_ovl_29A4C0(u16 msg, u8 *ctx) {
    switch (msg) {
        case 0x101:
            func_8020DFB8();
            break;
        case 0x100:
            FIELD(ctx, f32, 0) = D_80220F68;
            FIELD(ctx, f32, 4) = D_80220F6C;
            FIELD(ctx, f32, 8) = D_80220F70;
            FIELD(ctx, s32, 0xC) = 0;
            func_8020DC80(0x1000);
            break;
        case 0x1000:
            func_8020A4A8(D_80220EE0, ctx + 0x10);
            func_8020A5A0(ctx + 0x10, ctx);
            func_801C5938(D_800EB240, 0x1F2);
        case 0x1001:
            FIELD(ctx, u8 *, 0x50) = func_80214C84(0x1A8, func_80237B84_ovl_29A4C0);
            FIELD(FIELD(ctx, u8 *, 0x50), u16, 0xA) |= 0x8000;
            func_8020D86C(FIELD(ctx, u8 *, 0x50), 0x96, 0xAA);
            func_8020A4A8(ctx + 0x10, FIELD(ctx, u8 *, 0x50) + 0x1C);
            func_8020E0B4(4, 0x1002);
            break;
        case 0x1002: {
            u8 *o = func_80214BE8(0x1A9);

            FIELD(o, u16, 0xA) |= 0x8000;
            func_8020A4A8(ctx + 0x10, o + 0x1C);
            func_8020E0B4(0x49, 0x1003);
            break;
        }
        case 0x1003:
            FIELD(ctx, u8 *, 0x54) = func_80214BE8(0x1A6);
            FIELD(FIELD(ctx, u8 *, 0x54), u16, 0xA) |= 0x1000;
            func_8020D86C(FIELD(ctx, u8 *, 0x54), 0x48, 0x5C);
            FIELD(FIELD(ctx, u8 *, 0x54), s32, 0xC) = -10000;
            func_8020A4A8(ctx + 0x10, FIELD(ctx, u8 *, 0x54) + 0x1C);
            func_801C5938(D_800EB290, 0x1F3);
            func_8020DC80(0x1004);
            break;
        case 0x1004:
            if (FIELD(ctx, s32, 0xC) != 0) {
                func_8020D884(FIELD(ctx, u8 *, 0x50));
                func_8020D884(FIELD(ctx, u8 *, 0x54));
                func_8020DC80(0x1005);
            }
            break;
        case 0x1005:
            if (FIELD(FIELD(ctx, u8 *, 0x50), s32, 0x10) >= 0xAA) {
                func_801C5938(D_800EB290, 0x1F4);
                func_8020E0B4(0x8D, 0x1006);
            }
            break;
        case 0x1006: {
            u8 *o = func_80216018(0x1A4);

            FIELD(o, f32, 0x1C) = FIELD(ctx, f32, 0);
            FIELD(o, f32, 0x20) = FIELD(ctx, f32, 4);
            FIELD(o, f32, 0x24) = FIELD(ctx, f32, 8);
            func_801C5938(D_800EB290, 0x1F5);
            func_8020E0B4(0x1C, 0x1007);
            break;
        }
        case 0x1007: {
            u8 *o = func_80216018(0x1A7);

            FIELD(o, f32, 0x1C) = FIELD(ctx, f32, 0);
            FIELD(o, f32, 0x20) = FIELD(ctx, f32, 4);
            FIELD(o, f32, 0x24) = FIELD(ctx, f32, 8);
            func_8020E0B4(0x1A, 0x1008);
            break;
        }
        case 0x1008: {
            u8 *o = func_80216018(0x1A5);

            FIELD(o, u16, 0xA) |= 0x8000;
            FIELD(o, f32, 0x1C) = FIELD(ctx, f32, 0);
            FIELD(o, f32, 0x20) = FIELD(ctx, f32, 4);
            FIELD(o, f32, 0x24) = FIELD(ctx, f32, 8);
            func_8020E0B4(0x3C, 0x101);
            break;
        }
        case 0x1009:
            FIELD(ctx, s32, 0xC) = 1;
            break;
    }
    return 0;
}

#ifndef FIELD
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
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

extern f32 D_80220F68;
extern u8 D_800EB240[];
void func_8023830C_ovl_29A4C0(u16 msg, u8 *ctx);
void func_801C5938(void *bank, s32 se);

/* Scene script for the other drifting sprites (func_8023830C), with sounds on spawn and exit */
s32 func_80237C90_ovl_29A4C0(u16 msg, u8 *ctx) {
    u8 *o;
    u8 *p;

    switch (msg) {
        case 0x101:
            if (FIELD(ctx, u8 *, 0xC) != NULL) {
                func_8020D814(FIELD(ctx, u8 *, 0xC));
            }
            func_8020DFB8();
            break;
        case 0x100:
            FIELD(ctx, f32, 0) = D_80220F68;
            FIELD(ctx, f32, 4) = D_80220F6C;
            FIELD(ctx, f32, 8) = D_80220F70;
            FIELD(ctx, void *, 0xC) = NULL;
            FIELD(ctx, s32, 0x10) = 0;
            func_8020DC80(0x1000);
            break;
        case 0x1000:
            o = func_80214C84(0x1AA, func_8023830C_ovl_29A4C0);
            FIELD(ctx, u8 *, 0xC) = o;
            p = o + 0x1C;
            func_8020A4A8(D_80220EE0, p);
            func_8020A5A0(p, ctx);
            func_801C5938(D_800EB240, 0x1F8);
            func_8020E0E4(FIELD(ctx, u8 *, 0xC), 0x146, 0x1001);
            break;
        case 0x1001:
            FIELD(FIELD(ctx, u8 *, 0xC), u16, 0xA) |= 0x2000;
            func_8020DC80(0x1002);
        case 0x1002:
            if (FIELD(ctx, s32, 0x10) != 0) {
                func_801C5938(D_800EB240, 0x1F9);
                func_8020DC80(0x1004);
            }
            break;
        case 0x1003:
            FIELD(ctx, s32, 0x10) = 1;
            break;
        case 0x1004:
            FIELD(FIELD(ctx, u8 *, 0xC), u16, 0xA) &= ~0x2000;
            func_8020D86C(FIELD(ctx, u8 *, 0xC), 0x158, 0x166);
            func_8020DC80(0x1005);
            break;
    }
    return 0;
}

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

extern u8 D_801CFC70;
s32 func_8020DF00(s32 (*fn)(u16, u8 *));
void func_8020DCAC(s32 h, u16 msg);
u8 *func_802158AC(s32 id);
u8 *func_80216018(s32 id);
s32 func_80237E4C_ovl_29A4C0(u16 msg, u8 *ctx);
s32 func_8023823C_ovl_29A4C0(u16 msg);

/* Parent scene: runs the two drifting sprite scripts (handles at 0xC and 0x10) around the
 * central object and passes the camera position on to them */
s32 func_80238004_ovl_29A4C0(u16 msg, u8 *ctx) {
    switch (msg) {
        case 0x101:
            D_801CFC70 = 0;
            func_8020DFB8();
            break;
        case 0x100:
            FIELD(ctx, f32, 0) = D_80220F68;
            FIELD(ctx, f32, 4) = D_80220F6C;
            FIELD(ctx, f32, 8) = D_80220F70;
            func_8020DC80(0x1000);
            break;
        case 0x1000:
            D_80220F68 = FIELD(ctx, f32, 0);
            D_80220F6C = FIELD(ctx, f32, 4);
            D_80220F70 = FIELD(ctx, f32, 8);
            FIELD(ctx, s32, 0xC) = func_8020DF00(func_80237C90_ovl_29A4C0);
            func_8020E0B4(0x105, 0x1003);
            break;
        case 0x1003: {
            u8 *o = func_802158AC(0x1AD);
            u8 *p;

            FIELD(o, s32, 0xC) = 10000;
            FIELD(o, u16, 0xA) |= 0x9000;
            p = o + 0x1C;
            func_8020A4A8(D_80220EE0, p);
            func_8020A5A0(p, ctx);
            func_8020DF00((s32 (*)(u16, u8 *))func_8023823C_ovl_29A4C0);
            func_801C5938(D_800EB240, 0x1F9);
            func_8020E0B4(0x10, 0x1001);
            break;
        }
        case 0x1001: {
            u8 *o = func_80216018(0x1AB);

            FIELD(o, u16, 0xA) |= 0x8000;
            FIELD(o, f32, 0x1C) = FIELD(ctx, f32, 0);
            FIELD(o, f32, 0x20) = FIELD(ctx, f32, 4);
            FIELD(o, f32, 0x24) = FIELD(ctx, f32, 8);
            func_8020E0B4(0x16, 0x1002);
            break;
        }
        case 0x1002:
            D_80220F6C = FIELD(ctx, f32, 0);
            D_80220F70 = FIELD(ctx, f32, 4);
            D_80220F74 = FIELD(ctx, f32, 8);
            FIELD(ctx, s32, 0x10) = func_8020DF00(func_80237E4C_ovl_29A4C0);
            func_8020DC80(0x1004);
            break;
        case 0x1005:
            func_8020DCAC(FIELD(ctx, s32, 0xC), 0x1003);
            func_8020DCAC(FIELD(ctx, s32, 0x10), 0x1004);
            break;
        case 0x1004:
            break;
    }
    return 0;
}

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
