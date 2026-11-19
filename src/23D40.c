#include "common.h"
#include "libultra.h"

/* libultra seteventmesg.c */

typedef struct {
    /* 0x00 */ OSMesgQueue *messageQueue;
    /* 0x04 */ OSMesg message;
} __OSEventState;

extern __OSEventState __osEventStateTab[];
extern u32 __osShutdown;
extern u32 D_800AA760; /* __osPreNMI */

void osSetEventMesg(s32 event, OSMesgQueue *mq, OSMesg msg) {
    register u32 saveMask = __osDisableInt();
    __OSEventState *es;

    es = &__osEventStateTab[event];
    es->messageQueue = mq;
    es->message = msg;

    if (event == 14) { /* OS_EVENT_PRENMI */
        if (__osShutdown && !D_800AA760) {
            osSendMesg(mq, msg, OS_MESG_NOBLOCK);
        }
        D_800AA760 = 1;
    }
    __osRestoreInt(saveMask);
}
