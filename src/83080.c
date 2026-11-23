#include "common.h"

/* 83080 */

INCLUDE_ASM("asm/nonmatchings/83080", func_801A40F0_ovl_079730);

extern u8 D_80193BC0[][0x38];
void func_801A40F0_ovl_079730(u8 *u);

/* Applies func_801A40F0 to every player unit 1-99 of an unpromoted 0x52-0x57 class: on event 3
 * to classes 0x52 / 0x55 / 0x57, on event 4 to class 0x53 */
void func_801A4568_ovl_079730(u16 ev) {
    s32 i;

    for (i = 1; i < 100; i++) {
        u8 *u = D_80193BC0[i];
        s32 c = u[0x11];
        s32 d = u[0x12];

        if ((u32)(c - 0x52) < 6 && (c = (u8)c) == d) {
            switch (ev) {
                case 3:
                    switch (c) {
                        case 0x52:
                        case 0x55:
                        case 0x57:
                            func_801A40F0_ovl_079730(u);
                            break;
                    }
                    break;
                case 4:
                    if (c == 0x53) {
                        func_801A40F0_ovl_079730(u);
                    }
                    break;
            }
        }
    }
}
