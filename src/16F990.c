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
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/16F990", func_8021E950_ovl_165FC0);

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
