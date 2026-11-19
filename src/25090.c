#include "common.h"
#include "libultra.h"

/* libultra gettime.c */

extern OSTime __osCurrentTime;
extern u32 __osBaseCounter;

u32 osGetCount(void);

OSTime osGetTime(void) {
    u32 tmptime;
    u32 elapseCount;
    OSTime currentCount;
    register u32 saveMask;

    saveMask = __osDisableInt();
    tmptime = osGetCount();
    elapseCount = tmptime - __osBaseCounter;
    currentCount = __osCurrentTime;
    __osRestoreInt(saveMask);
    return currentCount + elapseCount;
}
