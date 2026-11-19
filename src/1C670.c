#include "common.h"
#include "libultra.h"

extern OSMesgQueue __osPiAccessQueue;
extern u32 __osPiAccessQueueEnabled;
extern OSMesg piAccessBuf[1];

inline void __osPiCreateAccessQueue(void) {
    __osPiAccessQueueEnabled = 1;
    osCreateMesgQueue(&__osPiAccessQueue, piAccessBuf, 1);
    osSendMesg(&__osPiAccessQueue, NULL, OS_MESG_NOBLOCK);
}

void __osPiGetAccess(void) {
    OSMesg dummyMesg;

    if (!__osPiAccessQueueEnabled) {
        __osPiCreateAccessQueue();
    }
    osRecvMesg(&__osPiAccessQueue, &dummyMesg, OS_MESG_BLOCK);
}

void __osPiRelAccess(void) {
    osSendMesg(&__osPiAccessQueue, NULL, OS_MESG_NOBLOCK);
}
