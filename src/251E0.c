#include "common.h"
#include "libultra.h"

/* libultra timerintr.c */

extern OSTimer *D_800AA7B0; /* __osTimerList */
extern OSTime __osCurrentTime;
extern u32 __osBaseCounter;
extern u32 __osViIntrCount;
extern u32 __osTimerCounter;

u32 osGetCount(void);
void __osSetCompare(u32 v);
void __osSetTimerIntr(OSTime tim);
OSTime __osInsertTimer(OSTimer *t);

void __osTimerServicesInit(void) {
    __osCurrentTime = 0;
    __osBaseCounter = 0;
    __osViIntrCount = 0;
    D_800AA7B0->prev = D_800AA7B0;
    D_800AA7B0->next = D_800AA7B0->prev;
    D_800AA7B0->value = 0;
    D_800AA7B0->interval = D_800AA7B0->value;
    D_800AA7B0->mq = NULL;
    D_800AA7B0->msg = 0;
}

void __osTimerInterrupt(void) {
    OSTimer *t;
    u32 count;
    u32 elapsed_cycles;

    if (D_800AA7B0->next == D_800AA7B0) {
        return;
    }
    while (1) {
        t = D_800AA7B0->next;
        if (t == D_800AA7B0) {
            __osSetCompare(0);
            __osTimerCounter = 0;
            break;
        }
        count = osGetCount();
        elapsed_cycles = count - __osTimerCounter;
        __osTimerCounter = count;
        if (elapsed_cycles < t->value) {
            t->value -= elapsed_cycles;
            __osSetTimerIntr(t->value);
            return;
        } else {
            t->prev->next = t->next;
            t->next->prev = t->prev;
            t->next = NULL;
            t->prev = NULL;
            if (t->mq != NULL) {
                osSendMesg(t->mq, t->msg, OS_MESG_NOBLOCK);
            }
            if (t->interval != 0) {
                t->value = t->interval;
                __osInsertTimer(t);
            }
        }
    }
}

void __osSetTimerIntr(OSTime tim) {
    OSTime NewTime;
    u32 savedMask;

    savedMask = __osDisableInt();
    __osTimerCounter = osGetCount();
    NewTime = __osTimerCounter + tim;
    __osSetCompare((u32)NewTime);
    __osRestoreInt(savedMask);
}

OSTime __osInsertTimer(OSTimer *t) {
    OSTimer *timep;
    OSTime tim;
    u32 savedMask;

    savedMask = __osDisableInt();
    for (timep = D_800AA7B0->next, tim = t->value; timep != D_800AA7B0 && tim > timep->value;
         tim -= timep->value, timep = timep->next) {
    }
    t->value = tim;
    if (timep != D_800AA7B0) {
        timep->value -= tim;
    }
    t->next = timep;
    t->prev = timep->prev;
    timep->prev->next = t;
    timep->prev = t;
    __osRestoreInt(savedMask);
    return tim;
}
