#include "common.h"

/* 1782C0 */

extern u8 D_80218D91_ovl_177ED0;

void func_80215AF4_ovl_177ED0(void);
/* --- end decls --- */

void func_80215500_ovl_177ED0(void);
void func_80218A34_ovl_177ED0(void);
extern s8 D_8018F53E;
extern s32 D_801F0DE0;
extern s32 D_801F0DE8;
extern s8 D_801F0FE0;
extern s32 D_801F3658;
extern u8 D_801F365D;
extern s8 D_801F3A34;
extern u8 D_80218D90_ovl_177ED0;
extern s32 D_80218D94_ovl_177ED0;
extern u8 D_8021E300_ovl_177ED0[];

extern s32 *D_801F0CB0[];

/* Runs the scene with bit 0x40000 of the 50 tracked flags cleared (saving them first) and
 * puts the saved bits back when the scene reaches state 5 */
void func_80215370_ovl_177ED0(void) {
    s32 i;

    if (D_80218D94_ovl_177ED0 == 0) {
        for (i = 0; i < 50; i++) {
            if (*D_801F0CB0[i] & 0x40000) {
                D_8021E300_ovl_177ED0[i] = 1;
            } else {
                D_8021E300_ovl_177ED0[i] = 0;
            }
            *D_801F0CB0[i] &= ~0x40000;
        }
        D_80218D94_ovl_177ED0 = 1;
        D_801F3A34 = 1;
    }
    func_80218A34_ovl_177ED0();
    if (D_80218D91_ovl_177ED0) {
        func_80215500_ovl_177ED0();
    }
    if (D_80218D90_ovl_177ED0 == 5) {
        D_801F0DE0 = 3;
        D_801F3658 = -1;
        D_801F0DE8 = 0;
        D_801F0FE0 = 3;
        D_8018F53E = 0;
        D_801F365D |= 1;
        for (i = 0; i < 50; i++) {
            if (D_8021E300_ovl_177ED0[i]) {
                *D_801F0CB0[i] |= 0x40000;
            }
        }
        D_80218D94_ovl_177ED0 = 0;
        D_801F3A34 = 0;
    }
}

void func_802154CC_ovl_177ED0(void) {
    if (D_80218D91_ovl_177ED0) {
        func_80215AF4_ovl_177ED0();
    }
}
