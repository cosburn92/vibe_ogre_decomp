#include "common.h"
#include "libultra.h"

/* libultra recvmesg.c */

extern OSThreadHdr *__osRunningThread;

void __osEnqueueAndYield(OSThreadHdr **queue);
OSThreadHdr *__osPopThread(OSThreadHdr **queue);

s32 osRecvMesg(OSMesgQueue *mq, OSMesg *msg, s32 flag) {
    register u32 saveMask;

    saveMask = __osDisableInt();
    while (MQ_IS_EMPTY(mq)) {
        if (flag == OS_MESG_NOBLOCK) {
            __osRestoreInt(saveMask);
            return -1;
        }
        __osRunningThread->state = OS_STATE_WAITING;
        __osEnqueueAndYield((OSThreadHdr **)&mq->mtqueue);
    }
    if (msg != NULL) {
        *msg = mq->msg[mq->first];
    }
    mq->first = (mq->first + 1) % mq->msgCount;
    mq->validCount--;
    if (((OSThreadHdr *)mq->fullqueue)->next != NULL) {
        osStartThread((OSThread *)__osPopThread((OSThreadHdr **)&mq->fullqueue));
    }
    __osRestoreInt(saveMask);
    return 0;
}
