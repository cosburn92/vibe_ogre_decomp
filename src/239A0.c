#include "common.h"
#include "libultra.h"

/* libultra jammesg.c */

extern OSThreadHdr *__osRunningThread;

void __osEnqueueAndYield(OSThreadHdr **queue);
OSThreadHdr *__osPopThread(OSThreadHdr **queue);

s32 osJamMesg(OSMesgQueue *mq, OSMesg msg, s32 flag) {
    register u32 saveMask;

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
    mq->first = (mq->first + mq->msgCount - 1) % mq->msgCount;
    mq->msg[mq->first] = msg;
    mq->validCount++;
    if (((OSThreadHdr *)mq->mtqueue)->next != NULL) {
        osStartThread((OSThread *)__osPopThread((OSThreadHdr **)&mq->mtqueue));
    }
    __osRestoreInt(saveMask);
    return 0;
}
