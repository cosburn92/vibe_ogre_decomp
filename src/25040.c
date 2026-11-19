#include "common.h"
#include "libultra.h"

/* libultra yieldthread.c */

extern OSThread *__osRunningThread;
extern OSThread *__osRunQueue;

void __osEnqueueAndYield(OSThread **queue);
void __osEnqueueThread(OSThread **queue, OSThread *t);
OSThread *__osPopThread(OSThread **queue);
void __osDequeueThread(OSThread **queue, OSThread *t);
void __osDispatchThread(void);

void osYieldThread(void) {
    register u32 saveMask = __osDisableInt();

    __osRunningThread->state = OS_STATE_RUNNABLE;
    __osEnqueueAndYield(&__osRunQueue);
    __osRestoreInt(saveMask);
}
