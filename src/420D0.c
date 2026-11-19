#include "common.h"

/* 420D0 */

void osSetTime(u64 t);
void bzero(void *p, s32 n);
typedef struct {
    u16 hours;
    u8 minutes;
    u8 seconds;
} Clock420;
/* --- end decls --- */

/* Leap-year test; era 1 years are offset by 1748 */
s32 func_8016C1D0_ovl_040E80(u16 year, u8 era) {
    s32 r;

    if (era) {
        year += 1748;
    }
    r = 0;
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        r = 1;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/420D0", func_8016C268_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/420D0", func_8016C3C4_ovl_040E80);

/* One-second tick; in day mode (1) wraps at 24 hours and returns 1, otherwise counts hours up to 0xFFFD */
s32 func_8016C528_ovl_040E80(Clock420 *c, u8 mode) {
    if (++c->seconds == 60) {
        c->minutes++;
        c->seconds = 0;
        if (c->minutes == 60) {
            c->hours++;
            c->minutes = 0;
            if (mode == 1) {
                if (c->hours == 24) {
                    c->hours = 0;
                    return 1;
                }
            } else if (c->hours == 0xFFFE) {
                c->hours--;
            }
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/420D0", DateAdvanceDay);

INCLUDE_ASM("asm/nonmatchings/420D0", func_8016C70C_ovl_040E80);

void func_8016C814_ovl_040E80(void) {
}

INCLUDE_ASM("asm/nonmatchings/420D0", func_8016C81C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/420D0", NewGameInit);

INCLUDE_ASM("asm/nonmatchings/420D0", func_8016C9FC_ovl_040E80);

void func_8016CB08_ovl_040E80(void *p) {
    osSetTime(0);
    bzero(p, 4);
}

INCLUDE_ASM("asm/nonmatchings/420D0", PlayTimeUpdate);

INCLUDE_ASM("asm/nonmatchings/420D0", func_8016CC2C_ovl_040E80);
