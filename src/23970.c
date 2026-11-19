#include "common.h"
#include "libultra.h"

/* libultra createmesgqueue.c */

extern OSThreadHdr *D_800AA790; /* __osThreadTail */

void osCreateMesgQueue(OSMesgQueue *mq, OSMesg *msg, s32 msgCount) {
    mq->mtqueue = &D_800AA790;
    mq->fullqueue = &D_800AA790;
    mq->validCount = 0;
    mq->first = 0;
    mq->msgCount = msgCount;
    mq->msg = msg;
}
