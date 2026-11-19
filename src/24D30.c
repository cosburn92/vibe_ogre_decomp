#include "common.h"
#include "libultra.h"

/* libultra getthreadpri.c */

extern OSThread *__osRunningThread;

s32 osGetThreadPri(OSThread *thread) {
    if (thread == NULL) {
        thread = __osRunningThread;
    }
    return thread->priority;
}
