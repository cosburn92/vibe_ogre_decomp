#include "common.h"
#include "libultra.h"

/* libultra createthread.c */

extern OSThread *__osActiveQueue;

void __osCleanupThread(void);

void osCreateThread(OSThread *t, s32 id, void (*entry)(void *), void *arg, void *sp, s32 p) {
    register u32 saveMask;
    u32 mask;

    t->id = id;
    t->priority = p;
    t->next = NULL;
    t->queue = NULL;
    t->context.pc = (u32)entry;
    t->context.a0 = (s64)(s32)arg;
    t->context.sp = (s64)(s32)sp - 16;
    t->context.ra = (s64)(s32)__osCleanupThread;
    mask = 0x003FFF01; /* OS_IM_ALL */
    t->context.sr = 0xFF03; /* SR_IMASK | SR_EXL | SR_IE */
    t->context.rcp = (mask & 0x003F0000) >> 16;
    t->context.fpcsr = (u32)(0x01000000 | 0x00000800); /* FPCSR_FS | FPCSR_EV */
    t->fp = 0;
    t->state = OS_STATE_STOPPED;
    t->flags = 0;
    saveMask = __osDisableInt();
    t->tlnext = __osActiveQueue;
    __osActiveQueue = t;
    __osRestoreInt(saveMask);
}
