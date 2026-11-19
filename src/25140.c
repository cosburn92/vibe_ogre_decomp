#include "common.h"
#include "libultra.h"

/* libultra settimer.c */

extern OSTimer *D_800AA7B0; /* __osTimerList */

OSTime __osInsertTimer(OSTimer *t);
void __osSetTimerIntr(OSTime tim);

s32 osSetTimer(OSTimer *t, OSTime value, OSTime interval, OSMesgQueue *mq, OSMesg msg) {
    OSTime tim;

    t->next = NULL;
    t->prev = NULL;
    t->interval = interval;
    t->value = (value != 0) ? value : interval;
    t->mq = mq;
    t->msg = msg;
    tim = __osInsertTimer(t);
    if (D_800AA7B0->next == t) {
        __osSetTimerIntr(tim);
    }
    return 0;
}
