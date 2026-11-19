#include "common.h"
#include "libultra.h"

/* libultra setthreadpri.c */

extern OSThread *__osRunningThread;
extern OSThread *__osRunQueue;

void __osEnqueueAndYield(OSThread **queue);
void __osEnqueueThread(OSThread **queue, OSThread *t);
OSThread *__osPopThread(OSThread **queue);
void __osDequeueThread(OSThread **queue, OSThread *t);
void __osDispatchThread(void);

void osSetThreadPri(OSThread *t, s32 pri) {
    register u32 saveMask = __osDisableInt();

    if (t == NULL) {
        t = __osRunningThread;
    }
    if (t->priority != pri) {
        t->priority = pri;
        if (t != __osRunningThread && t->state != OS_STATE_STOPPED) {
            __osDequeueThread(t->queue, t);
            __osEnqueueThread(t->queue, t);
        }
        if (__osRunningThread->priority < __osRunQueue->priority) {
            __osRunningThread->state = OS_STATE_RUNNABLE;
            __osEnqueueAndYield(&__osRunQueue);
        }
    }
    __osRestoreInt(saveMask);
}
