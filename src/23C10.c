#include "common.h"
#include "libultra.h"

/* libultra sendmesg.c */

extern OSThreadHdr *__osRunningThread;

void __osEnqueueAndYield(OSThreadHdr **queue);
OSThreadHdr *__osPopThread(OSThreadHdr **queue);

s32 osSendMesg(OSMesgQueue *mq, OSMesg msg, s32 flag) {
    register u32 saveMask;
    register s32 last;

    saveMask = __osDisableInt();
    while (MQ_IS_FULL(mq)) {
        if (flag == OS_MESG_BLOCK) {
            __osRunningThread->state = OS_STATE_WAITING;
            __osEnqueueAndYield((OSThreadHdr **)&mq->fullqueue);
        } else {
            __osRestoreInt(saveMask);
            return -1;
        }
    }
    last = (mq->first + mq->validCount) % mq->msgCount;
    mq->msg[last] = msg;
    mq->validCount++;
    if (((OSThreadHdr *)mq->mtqueue)->next != NULL) {
        osStartThread((OSThread *)__osPopThread((OSThreadHdr **)&mq->mtqueue));
    }
    __osRestoreInt(saveMask);
    return 0;
}
