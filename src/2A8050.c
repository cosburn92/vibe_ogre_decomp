#include "common.h"

/* 2A8050 */

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern u8 D_801CFC70;
extern f32 D_80220F68;
extern f32 D_80220F6C;
extern f32 D_80220F70;
extern u8 D_80220EE0[];
extern u8 D_800EB240[];
extern u8 D_800EB290[];
void func_8020DFB8(void);
void func_8020DC80(u16 state);
void func_8020E0B4(s32 a, s32 b);
u8 *func_80214BE8(s32 id);
u8 *func_80216018(s32 id);
void func_8020A4A8(u8 *a, u8 *b);
void func_8020A5A0(u8 *a, u8 *b);
void func_801C5938(void *bank, s32 se);

/* Event scene: spawns the three objects at the camera position, then the follow-up objects
 * one stage at a time, and ends with a sound */
s32 func_80238820_ovl_29A4C0(u16 msg, u8 *ctx) {
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
        case 0x1000: {
            u8 *o;

            o = func_80216018(0x1B5);
            FIELD(o, u16, 0xA) |= 0x8000;
            FIELD(o, f32, 0x1C) = FIELD(ctx, f32, 0);
            FIELD(o, f32, 0x20) = FIELD(ctx, f32, 4);
            FIELD(o, f32, 0x24) = FIELD(ctx, f32, 8);
            o = func_80216018(0x1B6);
            FIELD(o, u16, 0xA) |= 0x8000;
            FIELD(o, f32, 0x1C) = FIELD(ctx, f32, 0);
            FIELD(o, f32, 0x20) = FIELD(ctx, f32, 4);
            FIELD(o, f32, 0x24) = FIELD(ctx, f32, 8);
            o = func_80216018(0x1B7);
            FIELD(o, s32, 0xC) = -1000;
            FIELD(o, u16, 0xA) |= 0x9000;
            FIELD(o, f32, 0x1C) = FIELD(ctx, f32, 0);
            FIELD(o, f32, 0x20) = FIELD(ctx, f32, 4);
            FIELD(o, f32, 0x24) = FIELD(ctx, f32, 8);
            func_801C5938(D_800EB240, 0x201);
            func_8020E0B4(0x2C, 0x1001);
            break;
        }
        case 0x1001: {
            u8 *o = func_80214BE8(0x1B4);
            u8 *p;

            FIELD(o, u16, 0xA) |= 0x8000;
            p = o + 0x1C;
            func_8020A4A8(D_80220EE0, p);
            func_8020A5A0(p, ctx);
            func_8020E0B4(0xC, 0x1002);
            break;
        }
        case 0x1002: {
            u8 *o = func_80216018(0x1B3);

            FIELD(o, u16, 0xA) |= 0x8000;
            FIELD(o, f32, 0x1C) = FIELD(ctx, f32, 0);
            FIELD(o, f32, 0x20) = FIELD(ctx, f32, 4);
            FIELD(o, f32, 0x24) = FIELD(ctx, f32, 8);
            func_8020E0B4(5, 0x1003);
            break;
        }
        case 0x1003: {
            u8 *o = func_80216018(0x1B2);

            FIELD(o, u16, 0xA) |= 0x8000;
            FIELD(o, f32, 0x1C) = FIELD(ctx, f32, 0);
            FIELD(o, f32, 0x20) = FIELD(ctx, f32, 4);
            FIELD(o, f32, 0x24) = FIELD(ctx, f32, 8);
            func_8020E0B4(0x4B, 0x1004);
            break;
        }
        case 0x1004:
            func_801C5938(D_800EB290, 0x202);
            func_8020E0B4(0xF, 0x101);
            break;
    }
    return 0;
}
