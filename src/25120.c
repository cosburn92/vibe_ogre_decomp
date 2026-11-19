#include "common.h"
#include "libultra.h"

/* libultra settime.c */

extern OSTime __osCurrentTime;

void osSetTime(OSTime ticks) {
    __osCurrentTime = ticks;
}
