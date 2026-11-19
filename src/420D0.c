#include "common.h"

/* 420D0 */

void osSetTime(u64 t);
void bzero(void *p, s32 n);
typedef struct {
    u16 hours;
    u8 minutes;
    u8 seconds;
} Clock420;
extern Clock420 D_80196A2C_ovl_040E80;
extern u8 D_80196A30_ovl_040E80[];
extern u8 D_80196A34_ovl_040E80;
extern u8 D_80196A35_ovl_040E80;
void DateAdvanceDay(void *d);
u64 osGetTime(void);
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
inline u8 func_8016C528_ovl_040E80(Clock420 *c, u8 mode) {
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

/* World clock: every D_80196A34 frames advances the clock one second; a day rollover advances the date */
void func_8016C81C_ovl_040E80(void) {
    u8 *t = &D_80196A35_ovl_040E80;

    if (++*t >= D_80196A34_ovl_040E80) {
        *t = 0;
        if (func_8016C528_ovl_040E80(&D_80196A2C_ovl_040E80, 1) == 1) {
            DateAdvanceDay(D_80196A30_ovl_040E80);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/420D0", NewGameInit);

INCLUDE_ASM("asm/nonmatchings/420D0", func_8016C9FC_ovl_040E80);

void func_8016CB08_ovl_040E80(void *p) {
    osSetTime(0);
    bzero(p, 4);
}

/* Play time from the CPU counter (46.875 MHz), capped at 99:59:59 */
void PlayTimeUpdate(Clock420 *c) {
    u64 s = osGetTime() / 46875000;

    c->seconds = s % 60;
    c->minutes = s / 60 % 60;
    s /= 3600;
    if (s < 100) {
        c->hours = s;
    } else {
        c->hours = 99;
        c->seconds = 59;
        c->minutes = 59;
    }
}

INCLUDE_ASM("asm/nonmatchings/420D0", func_8016CC2C_ovl_040E80);
