#include "common.h"
#include "libultra.h"

/* libultra vimgr.c */

#define OS_MESG_TYPE_VRETRACE 13
#define OS_MESG_TYPE_COUNTER 14
#define OS_EVENT_COUNTER 3
#define OS_EVENT_VI 7

extern OSDevMgr __osViDevMgr;
extern u32 __additional_scanline;
extern OSThread viThread;
extern u64 viThreadStack[0x1000 / sizeof(u64)];
extern OSMesgQueue viEventQueue;
extern OSMesg viEventBuf[5];
extern OSIoMesg viRetraceMsg;
extern OSIoMesg viCounterMsg;
extern u16 vimgr_retrace;
extern OSTime __osCurrentTime;
extern u32 __osBaseCounter;
extern u32 __osViIntrCount;

void __osTimerServicesInit(void);
void __osTimerInterrupt(void);
void osSetEventMesg(s32 event, OSMesgQueue *mq, OSMesg msg);
s32 osGetThreadPri(OSThread *t);
void osSetThreadPri(OSThread *t, s32 pri);
void __osViInit(void);
void __osViSwapContext(void);
__OSViContext *__osViGetCurrentContext(void);
u32 osGetCount(void);
void viMgrMain(void *arg);

void osCreateViManager(s32 pri) {
    u32 savedMask;
    s32 oldPri;
    s32 myPri;

    if (__osViDevMgr.active == 0) {
        __osTimerServicesInit();
        __additional_scanline = 0;
        osCreateMesgQueue(&viEventQueue, viEventBuf, 5);
        viRetraceMsg.hdr.type = OS_MESG_TYPE_VRETRACE;
        viRetraceMsg.hdr.pri = OS_MESG_PRI_NORMAL;
        viRetraceMsg.hdr.retQueue = NULL;
        viCounterMsg.hdr.type = OS_MESG_TYPE_COUNTER;
        viCounterMsg.hdr.pri = OS_MESG_PRI_NORMAL;
        viCounterMsg.hdr.retQueue = NULL;
        osSetEventMesg(OS_EVENT_VI, &viEventQueue, &viRetraceMsg);
        osSetEventMesg(OS_EVENT_COUNTER, &viEventQueue, &viCounterMsg);
        oldPri = -1;
        myPri = osGetThreadPri(NULL);
        if (myPri < pri) {
            oldPri = myPri;
            osSetThreadPri(NULL, pri);
        }
        savedMask = __osDisableInt();
        __osViDevMgr.active = 1;
        __osViDevMgr.thread = &viThread;
        __osViDevMgr.cmdQueue = &viEventQueue;
        __osViDevMgr.evtQueue = &viEventQueue;
        __osViDevMgr.acsQueue = NULL;
        __osViDevMgr.dma = NULL;
        __osViDevMgr.edma = NULL;
        osCreateThread(&viThread, 0, viMgrMain, &__osViDevMgr, &viThreadStack[0x1000 / sizeof(u64)], pri);
        __osViInit();
        osStartThread(&viThread);
        __osRestoreInt(savedMask);
        if (oldPri != -1) {
            osSetThreadPri(NULL, oldPri);
        }
    }
}

void viMgrMain(void *arg) {
    __OSViContext *vc;
    OSDevMgr *dm;
    OSIoMesg *mb;
    s32 first;
    u32 count;

    mb = NULL;
    first = 0;
    vc = __osViGetCurrentContext();
    vimgr_retrace = vc->retraceCount;
    if (vimgr_retrace == 0) {
        vimgr_retrace = 1;
    }
    dm = (OSDevMgr *)arg;
    while (1) {
        osRecvMesg(dm->evtQueue, (OSMesg *)&mb, OS_MESG_BLOCK);
        switch (mb->hdr.type) {
            case OS_MESG_TYPE_VRETRACE:
                __osViSwapContext();
                vimgr_retrace--;
                if (vimgr_retrace == 0) {
                    vc = __osViGetCurrentContext();
                    if (vc->msgq != NULL) {
                        osSendMesg(vc->msgq, vc->msg, OS_MESG_NOBLOCK);
                    }
                    vimgr_retrace = vc->retraceCount;
                }
                __osViIntrCount++;
                if (first) {
                    count = osGetCount();
                    __osCurrentTime = count;
                    first = 0;
                }
                count = __osBaseCounter;
                __osBaseCounter = osGetCount();
                count = __osBaseCounter - count;
                __osCurrentTime = __osCurrentTime + count;
                break;
            case OS_MESG_TYPE_COUNTER:
                __osTimerInterrupt();
                break;
        }
    }
}
