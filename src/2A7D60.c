#include "common.h"

/* 2A7D60 */

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern f32 D_80220F68;
extern f32 D_80220F6C;
extern f32 D_80220F70;
extern u8 D_80220EE0[];
extern u8 D_800EB240[];
void func_8023870C_ovl_29A4C0(u16 msg, u8 *ctx);
void func_8020DFB8(void);
void func_8020DC80(u16 state);
void func_8020E0B4(s32 a, s32 b);
u8 *func_80214BE8(s32 id);
u8 *func_80214C84(s32 id, void (*fn)(u16, u8 *));
u8 *func_80216018(s32 id);
void func_8020A4A8(u8 *a, u8 *b);
void func_8020A5A0(u8 *a, u8 *b);
void func_801C5938(void *bank, s32 se);

/* Scene script for the four falling sprites (func_8023870C): spawns the backdrop and the
 * sprites, then the follow-up objects, and ends the scene after 60 frames */
s32 func_80238530_ovl_29A4C0(u16 msg, u8 *ctx) {
    switch (msg) {
        case 0x101:
            func_8020DFB8();
            break;
        case 0x100:
            FIELD(ctx, f32, 0) = D_80220F68;
            FIELD(ctx, f32, 4) = D_80220F6C;
            FIELD(ctx, f32, 8) = D_80220F70;
            func_8020DC80(0x1000);
            break;
        case 0x1000: {
            u8 *o;
            u8 *p;

            o = func_80214BE8(0x1AF);
            p = o + 0x1C;
            FIELD(o, u16, 0xA) |= 0x8000;
            func_8020A4A8(D_80220EE0, p);
            func_8020A5A0(p, ctx);
            o = func_80214C84(0x1B1, func_8023870C_ovl_29A4C0);
            p = o + 0x1C;
            FIELD(o, s32, 0xC) = -1000;
            FIELD(o, u16, 0xA) |= 0x9000;
            func_8020A4A8(D_80220EE0, p);
            func_8020A5A0(p, ctx);
            func_801C5938(D_800EB240, 0x200);
            func_8020E0B4(0x11, 0x1001);
            break;
        }
        case 0x1001: {
            u8 *o = func_80216018(0x1AE);

            FIELD(o, u16, 0xA) |= 0x8000;
            FIELD(o, f32, 0x1C) = FIELD(ctx, f32, 0);
            FIELD(o, f32, 0x20) = FIELD(ctx, f32, 4);
            FIELD(o, f32, 0x24) = FIELD(ctx, f32, 8);
            func_8020E0B4(3, 0x1002);
            break;
        }
        case 0x1002: {
            u8 *o = func_80214BE8(0x1B0);
            u8 *p = o + 0x1C;

            FIELD(o, u16, 0xA) |= 0x8000;
            func_8020A4A8(D_80220EE0, p);
            func_8020A5A0(p, ctx);
            func_8020E0B4(0x3C, 0x101);
            break;
        }
    }
    return 0;
}

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern u8 D_8020F390[];
extern s32 D_80239170_ovl_29A4C0[4];

/* Message handler for four 16x32 sprites: 0 resets them, 2 moves each two pixels left and down */
void func_8023870C_ovl_29A4C0(u16 msg, u8 *ctx) {
    u32 i;

    switch (msg) {
        case 0:
            for (i = 0; i < 4; i++) {
                FIELD(FIELD(ctx, u8 **, 0x58)[D_80239170_ovl_29A4C0[i]], void *, 0) = D_8020F390;
                {
                    u8 *p = FIELD(ctx, u8 **, 0x58)[D_80239170_ovl_29A4C0[i]];

                    FIELD(p, u16, 0x30) = 0;
                    FIELD(p, u16, 0x32) = 0;
                    FIELD(p, s16, 0x34) = FIELD(p, u16, 0x30) + 15;
                    FIELD(p, s16, 0x36) = FIELD(p, u16, 0x32) + 31;
                }
            }
            break;
        case 1:
            break;
        case 2:
            for (i = 0; i < 4; i++) {
                u8 *p = FIELD(ctx, u8 **, 0x58)[D_80239170_ovl_29A4C0[i]];

                FIELD(p, u16, 0x30) -= 2;
                FIELD(p, u16, 0x32) += 2;
                FIELD(p, s16, 0x34) = FIELD(p, u16, 0x30) + 15;
                FIELD(p, s16, 0x36) = FIELD(p, u16, 0x32) + 31;
            }
            break;
    }
}
