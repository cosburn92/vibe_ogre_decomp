#include "common.h"
#include "libultra.h"

extern OSDevMgr __osPiDevMgr;
extern OSThread piThread;
extern u64 piThreadStack[0x1000 / sizeof(u64)];
extern OSMesgQueue piEventQueue;
extern OSMesg piEventBuf;
extern OSMesgQueue __osPiAccessQueue;
extern u32 __osPiAccessQueueEnabled;

void osSetEventMesg(s32 event, OSMesgQueue *mq, OSMesg msg);
s32 osGetThreadPri(OSThread *t);
void osSetThreadPri(OSThread *t, s32 pri);
void __osPiCreateAccessQueue(void);
void __osDevMgrMain(void *arg);
s32 osPiRawStartDma(s32 direction, u32 devAddr, void *dramAddr, u32 size);
s32 osEPiRawStartDma(OSPiHandle *pihandle, s32 direction, u32 devAddr, void *dramAddr, u32 size);

void osCreatePiManager(s32 pri, OSMesgQueue *cmdQ, OSMesg *cmdBuf, s32 cmdMsgCnt) {
    u32 savedMask;
    s32 oldPri;
    s32 myPri;

    if (!__osPiDevMgr.active) {
        osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
        osCreateMesgQueue(&piEventQueue, &piEventBuf, 1);
        if (!__osPiAccessQueueEnabled) {
            __osPiCreateAccessQueue();
        }
        osSetEventMesg(8, &piEventQueue, (OSMesg)0x22222222); /* OS_EVENT_PI */
        oldPri = -1;
        myPri = osGetThreadPri(NULL);
        if (myPri < pri) {
            oldPri = myPri;
            osSetThreadPri(NULL, pri);
        }
        savedMask = __osDisableInt();
        __osPiDevMgr.active = 1;
        __osPiDevMgr.thread = &piThread;
        __osPiDevMgr.cmdQueue = cmdQ;
        __osPiDevMgr.evtQueue = &piEventQueue;
        __osPiDevMgr.acsQueue = &__osPiAccessQueue;
        __osPiDevMgr.dma = osPiRawStartDma;
        __osPiDevMgr.edma = osEPiRawStartDma;
        osCreateThread(&piThread, 0, __osDevMgrMain, &__osPiDevMgr, &piThreadStack[0x1000 / sizeof(u64)], pri);
        osStartThread(&piThread);
        __osRestoreInt(savedMask);
        if (oldPri != -1) {
            osSetThreadPri(NULL, oldPri);
        }
    }
}
