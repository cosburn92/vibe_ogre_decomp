#include "common.h"
#include "libultra.h"

/* libultra stopthread.c */

extern OSThread *__osRunningThread;
extern OSThread *__osRunQueue;

void __osEnqueueAndYield(OSThread **queue);
void __osEnqueueThread(OSThread **queue, OSThread *t);
OSThread *__osPopThread(OSThread **queue);
void __osDequeueThread(OSThread **queue, OSThread *t);
void __osDispatchThread(void);

void osStopThread(OSThread *t) {
    register u32 saveMask = __osDisableInt();
    register u16 state;

    state = (t == NULL) ? OS_STATE_RUNNING : t->state;
    switch (state) {
        case OS_STATE_RUNNING:
            __osRunningThread->state = OS_STATE_STOPPED;
            __osEnqueueAndYield(NULL);
            break;
        case OS_STATE_RUNNABLE:
        case OS_STATE_WAITING:
            t->state = OS_STATE_STOPPED;
            __osDequeueThread(t->queue, t);
            break;
    }
    __osRestoreInt(saveMask);
}
