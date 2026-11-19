#include "common.h"

/* 16F990 */

extern s32 D_801F3658;
extern s32 D_801F1074;
extern u8 *D_801F0CB0[];
extern u8 D_80214A60;
extern u8 D_80214A62;
extern u8 D_80214A63;
extern u8 D_801F365D;
extern s32 D_801F0DE0;
extern u8 D_801F0FDF;
extern u8 D_801F0FE0;
extern u8 D_801F0FE1;
void func_801B2D2C(u8 *u);
void func_801C8EAC(s32 a);
u8 func_801DADF0(u8 *u);
extern u16 *D_800C4BDC;
extern u16 *D_801F0CA0;
extern s32 D_8018F58C;
extern s32 D_801F0DE8;
extern u8 D_80210219;
extern u8 D_801F105F;
void func_801B8D44(f32 x, f32 y, f32 z, s32 a, s32 b);
void func_80216BF0_ovl_165FC0(void);
void func_8020CDA0(s32 a);
/* --- end decls --- */

/* Confirm keys centre the camera on the current unit (its leader when it is a member); key 15
 * toggles D_801F105F */
void func_8021E950_ovl_165FC0(void) {
    u16 *keys = D_801F0CA0;
    u16 btn = *D_800C4BDC;
    u8 *u;
    u8 pad[16]; /* unused, but the original frame has room for it */

    if ((btn & keys[0]) || (btn & keys[1])) {
        u = D_801F0CB0[D_801F3658];
        if (*(u32 *)u & 0x40) {
            D_801F3658 = D_801F1074;
            u = D_801F0CB0[D_801F1074];
        }
        func_801B8D44(*(f32 *)(u + 8), *(f32 *)(u + 0xC), *(f32 *)(u + 0x10), D_8018F58C, 0x2F);
        D_801F0DE8 = 0;
        func_80216BF0_ovl_165FC0();
        D_80210219 = 0x11;
        func_8020CDA0(6);
    } else if (btn & keys[15]) {
        {
            u8 *p = &D_801F105F;

            *p ^= 1;
        }
        func_8020CDA0(6);
    }
}

/* Unit menu confirm (states 1 and 2); state 1 first refreshes the unit, keeping the selection */
void func_8021EA50_ovl_165FC0(void) {
    s32 cur = D_801F3658;
    u8 *u = D_801F0CB0[cur];
    s32 sel;

    if ((u8)(D_80214A60 - 1) < 2) {
        if (D_80214A60 == 1) {
            sel = D_801F1074;
            func_801B2D2C(u);
            func_801C8EAC(1);
            *(u32 *)u &= ~2;
            D_801F3658 = cur;
            D_801F1074 = sel;
            D_801F365D |= 1;
            u[0x91] = D_80214A62;
            u[0x92] = D_80214A63;
        }
        D_801F0DE0 = 4;
        D_801F0FE1 = func_801DADF0(u);
        D_801F0FDF = 1;
        D_801F0FE0 = 2;
    }
}
