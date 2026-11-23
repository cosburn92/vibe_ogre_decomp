#include "common.h"

/* 420D0 */

void osSetTime(u64 t);
void bzero(void *p, s32 n);
typedef struct {
    u16 hours;
    u8 minutes;
    u8 seconds;
} Clock420;

typedef struct {
    u16 year;
    u8 month;
    u8 day;
} Date420;
extern Clock420 D_80196A2C_ovl_040E80;
extern u8 D_80196A30_ovl_040E80[];
extern u8 D_80196A34_ovl_040E80;
extern u8 D_80196A35_ovl_040E80;
s32 DateAdvanceDay(Date420 *d);
u64 osGetTime(void);
extern u8 D_80196A28_ovl_040E80[];
extern u8 D_80196A32_ovl_040E80;
extern u8 D_80196A33_ovl_040E80;
extern u8 D_80196A36_ovl_040E80;
extern u16 D_80193678_ovl_040E80;
extern u8 D_8019367A_ovl_040E80;
extern u8 D_8019367B_ovl_040E80;
extern u8 D_801936A7_ovl_040E80;
extern u8 D_801936A9_ovl_040E80;
extern u8 D_801936AA_ovl_040E80;
extern u8 D_801936AC_ovl_040E80;
extern u8 D_801936AD_ovl_040E80;
extern u8 D_80196AA4_ovl_040E80;
extern u8 D_80197810_ovl_040E80[];
void *memset(void *p, s32 c, s32 n);
extern u8 D_80186FFF_ovl_040E80[];
void ProfileFlagSet(s32 flag, s32 v);
/* --- end decls --- */

/* Leap-year test; era 1 years are offset by 1748 */
inline s32 func_8016C1D0_ovl_040E80(u16 year, u8 era) {
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

extern u8 D_80187000_ovl_040E80[];
extern u8 D_80187010_ovl_040E80[];

/* Converts d from the 16-month game calendar to the 12-month one (year - 1748) */
#ifdef NON_MATCHING
/* 91 vs 87 instructions: the original evaluates (m == 1) & leap as setcc + and; GCC here turns it into branches */
void func_8016C268_ovl_040E80(Date420 *d) {
    s32 leap = 0;
    s16 days = d->day - 1;
    s32 c;
    u8 t;
    u8 m;

    if (func_8016C1D0_ovl_040E80(d->year, 0) == 1) {
        leap = 1;
    }
    d->year -= 1748;
    for (m = 0; m < d->month - 1; m++) {
        days += D_80187010_ovl_040E80[m];
        c = (m == 1) & leap;
        if (c) {
            days++;
        }
    }
    for (m = 0;; m++) {
        t = D_80187000_ovl_040E80[m];
        c = (m == 2) & leap;
        days -= t;
        if (c) {
            days--;
        }
        if (days < 0) {
            break;
        }
    }
    if (c) {
        days++;
    }
    days += t;
    d->month = m + 1;
    d->day = days + 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/420D0", func_8016C268_ovl_040E80);
#endif

/* Converts d from the 12-month calendar back to the 16-month game one (year + 1748) */
#ifdef NON_MATCHING
/* 93 vs 89 instructions: as func_8016C268, the original evaluates (m == k) & leap as setcc + and; GCC here turns it into branches */
void func_8016C3C4_ovl_040E80(Date420 *d) {
    s32 leap = 0;
    s16 days = d->day - 1;
    s32 c;
    u8 t;
    u8 m;

    if (func_8016C1D0_ovl_040E80(d->year, 1) == 1) {
        leap = 1;
    }
    d->year += 1748;
    for (m = 0; m < d->month - 1; m++) {
        days += D_80187000_ovl_040E80[m];
        c = (m == 2) & leap;
        if (c) {
            days++;
        }
    }
    for (m = 0;; m++) {
        t = D_80187010_ovl_040E80[m];
        c = (m == 1) & leap;
        days -= t;
        if (c) {
            days--;
        }
        if (days < 0) {
            break;
        }
    }
    if (c) {
        days++;
    }
    days += t;
    d->month = m + 1;
    d->day = days + 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/420D0", func_8016C3C4_ovl_040E80);
#endif

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

/* Steps the date forward one day (month 3 gets an extra day in leap years); stops at 25/15/999 */
s32 DateAdvanceDay(Date420 *d) {
    s32 leap = 0;
    u16 y;

    if (d->day == 25) {
        if (d->month == 15) {
            if (d->year == 999) {
                return 0;
            }
        }
    }
    if (d->month == 3) {
        if (func_8016C1D0_ovl_040E80(d->year, 1) == 1) {
            leap = 1;
        }
    }
    if (++d->day > leap + D_80186FFF_ovl_040E80[d->month]) {
        d->day = 1;
        if (++d->month >= 16) {
            d->month = 1;
            y = d->year;
            if ((d->year = y + 1) == 999) {
                d->year = y;
            }
        }
    }
    return 0;
}

/* Steps the date back one day (month 4 gets an extra day in leap years) */
s32 func_8016C70C_ovl_040E80(Date420 *d) {
    s32 leap = 0;

    if (d->month == 4) {
        if (func_8016C1D0_ovl_040E80(d->year, 1) == 1) {
            leap = 1;
        }
    }
    if (--d->day == 0) {
        if (--d->month == 0) {
            d->month = 15;
            d->year--;
        }
        d->day = D_80186FFF_ovl_040E80[d->month] + leap;
    }
    return 0;
}

void func_8016C814_ovl_040E80(void) {
}

/* World clock: every D_80196A34 frames advances the clock one second; a day rollover advances the date */
void func_8016C81C_ovl_040E80(void) {
    u8 *t = &D_80196A35_ovl_040E80;

    if (++*t >= D_80196A34_ovl_040E80) {
        *t = 0;
        if (func_8016C528_ovl_040E80(&D_80196A2C_ovl_040E80, 1) == 1) {
            DateAdvanceDay((Date420 *)D_80196A30_ovl_040E80);
        }
    }
}

/* New game: date {251, 4, 1}, clock 06:00:00, default settings, event flags cleared to 0xFF */
void NewGameInit(void) {
    u16 *p;

    func_8016CB08_ovl_040E80(D_80196A28_ovl_040E80);
    p = &D_80193678_ovl_040E80;
    *(u16 *)D_80196A30_ovl_040E80 = 0xFB;
    D_80196A36_ovl_040E80 = 0;
    D_80196A32_ovl_040E80 = 4;
    D_80196A33_ovl_040E80 = 1;
    D_80196A2C_ovl_040E80.hours = 6;
    D_80196A2C_ovl_040E80.minutes = 0;
    D_80196A2C_ovl_040E80.seconds = 0;
    bzero(p, 0x3A);
    D_801936AA_ovl_040E80 = 7;
    D_801936A9_ovl_040E80 = 50;
    D_801936A7_ovl_040E80 = 0;
    *p = 0xF9;
    D_8019367A_ovl_040E80 = 1;
    D_8019367B_ovl_040E80 = 1;
    D_801936AD_ovl_040E80 = 4;
    D_801936AC_ovl_040E80 = 2;
    D_80196AA4_ovl_040E80 = 2;
    memset(D_80197810_ovl_040E80, 0xFF, 0x2D6);
}

#ifdef NON_MATCHING
/* the inlined NewGameInit keeps &D_80193678 in s2; the original re-materialises it for the store */
static inline void func_8016C9FC_newGame(void) {
    func_8016CB08_ovl_040E80(D_80196A28_ovl_040E80);
    *(u16 *)D_80196A30_ovl_040E80 = 0xFB;
    D_80196A36_ovl_040E80 = 0;
    D_80196A32_ovl_040E80 = 4;
    D_80196A33_ovl_040E80 = 1;
    D_80196A2C_ovl_040E80.hours = 6;
    D_80196A2C_ovl_040E80.minutes = 0;
    D_80196A2C_ovl_040E80.seconds = 0;
    bzero(&D_80193678_ovl_040E80, 0x3A);
    D_801936AA_ovl_040E80 = 7;
    D_801936A9_ovl_040E80 = 50;
    D_801936A7_ovl_040E80 = 0;
    D_80193678_ovl_040E80 = 0xF9;
    D_8019367A_ovl_040E80 = 1;
    D_8019367B_ovl_040E80 = 1;
    D_801936AD_ovl_040E80 = 4;
    D_801936AC_ovl_040E80 = 2;
    D_80196AA4_ovl_040E80 = 2;
    memset(D_80197810_ovl_040E80, 0xFF, 0x2D6);
}

/* NewGameInit, then sets profile flag 0x19 and starts the clock at 07:00 */
void func_8016C9FC_ovl_040E80(void) {
    func_8016C9FC_newGame();
    ProfileFlagSet(0x19, 1);
    D_80196A2C_ovl_040E80.hours = 7;
}
#else
INCLUDE_ASM("asm/nonmatchings/420D0", func_8016C9FC_ovl_040E80);
#endif

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

/* Restarts the play-time counter at the time in c */
void func_8016CC2C_ovl_040E80(Clock420 *c) {
    osSetTime(((u64)c->hours * 3600 + (u64)c->minutes * 60 + (u64)c->seconds) * 46875000);
}
