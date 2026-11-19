#include "common.h"
#include "libultra.h"

/* libultra controller.c */

extern s32 D_800AA720;          /* __osContinitialized */
extern OSMesgQueue D_800E99D0;  /* __osEepromTimerQ */
extern OSMesg D_800E79B8;       /* __osEepromTimerMsg */

void __osContGetInitData(u8 *pattern, OSContStatus *data);
void __osPackRequestData(u8 cmd);

s32 osContInit(OSMesgQueue *mq, u8 *bitpattern, OSContStatus *data) {
    OSTimer mytimer;
    OSMesgQueue timerMesgQueue;
    OSMesg dummy;
    s32 ret = 0;
    OSTime t;

    if (D_800AA720) {
        return 0;
    }
    D_800AA720 = 1;
    t = osGetTime();
    if (t < 23437500) { /* OS_USEC_TO_CYCLES(500000) */
        osCreateMesgQueue(&timerMesgQueue, &dummy, 1);
        osSetTimer(&mytimer, 23437500 - t, 0, &timerMesgQueue, &dummy);
        osRecvMesg(&timerMesgQueue, &dummy, OS_MESG_BLOCK);
    }
    __osMaxControllers = MAXCONTROLLERS;
    __osPackRequestData(CONT_CMD_REQUEST_STATUS);
    ret = __osSiRawStartDma(OS_WRITE, &__osContPifRam_800C4A20);
    osRecvMesg(mq, &dummy, OS_MESG_BLOCK);
    ret = __osSiRawStartDma(OS_READ, &__osContPifRam_800C4A20);
    osRecvMesg(mq, &dummy, OS_MESG_BLOCK);
    __osContGetInitData(bitpattern, data);
    __osContLastCmd = CONT_CMD_REQUEST_STATUS;
    __osSiCreateAccessQueue();
    osCreateMesgQueue(&D_800E99D0, &D_800E79B8, 1);
    return ret;
}

void __osContGetInitData(u8 *pattern, OSContStatus *data) {
    u8 *ptr;
    __OSContRequesFormat requestformat;
    int i;
    u8 bits;

    bits = 0;
    ptr = (u8 *)__osContPifRam_800C4A20.ramarray;
    for (i = 0; i < __osMaxControllers; i++, ptr += sizeof(requestformat), data++) {
        requestformat = *(__OSContRequesFormat *)ptr;
        data->errno = CHNL_ERR(requestformat);
        if (data->errno == 0) {
            data->type = (requestformat.typel << 8) | requestformat.typeh;
            data->status = requestformat.status;
            bits |= 1 << i;
        }
    }
    *pattern = bits;
}

void __osPackRequestData(u8 cmd) {
    u8 *ptr;
    __OSContRequesFormat requestformat;
    int i;

    for (i = 0; i < 15; i++) {
        __osContPifRam_800C4A20.ramarray[i] = 0;
    }
    __osContPifRam_800C4A20.pifstatus = CONT_CMD_EXE;
    ptr = (u8 *)__osContPifRam_800C4A20.ramarray;
    requestformat.dummy = CONT_CMD_NOP;
    requestformat.txsize = CONT_CMD_REQUEST_STATUS_TX;
    requestformat.rxsize = CONT_CMD_REQUEST_STATUS_RX;
    requestformat.cmd = cmd;
    requestformat.typeh = CONT_CMD_NOP;
    requestformat.typel = CONT_CMD_NOP;
    requestformat.status = CONT_CMD_NOP;
    requestformat.dummy1 = CONT_CMD_NOP;

    for (i = 0; i < __osMaxControllers; i++) {
        *(__OSContRequesFormat *)ptr = requestformat;
        ptr += sizeof(requestformat);
    }
    *ptr = CONT_CMD_END;
}
