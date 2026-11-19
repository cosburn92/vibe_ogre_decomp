#include "common.h"
#include "libultra.h"

/* libultra contreaddata.c */

void __osPackReadData(void);

s32 osContStartReadData(OSMesgQueue *mq) {
    s32 ret = 0;

    __osSiGetAccess();
    if (__osContLastCmd != CONT_CMD_READ_BUTTON) {
        __osPackReadData();
        ret = __osSiRawStartDma(OS_WRITE, &__osContPifRam_800C4A20);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    }
    ret = __osSiRawStartDma(OS_READ, &__osContPifRam_800C4A20);
    __osContLastCmd = CONT_CMD_READ_BUTTON;
    __osSiRelAccess();
    return ret;
}

void osContGetReadData(OSContPad *data) {
    u8 *ptr;
    __OSContReadFormat readformat;
    int i;

    ptr = (u8 *)__osContPifRam_800C4A20.ramarray;
    for (i = 0; i < __osMaxControllers; i++, ptr += sizeof(__OSContReadFormat), data++) {
        readformat = *(__OSContReadFormat *)ptr;
        data->errno = CHNL_ERR(readformat);
        if (data->errno == 0) {
            data->button = readformat.button;
            data->stick_x = readformat.stick_x;
            data->stick_y = readformat.stick_y;
        }
    }
}

void __osPackReadData(void) {
    u8 *ptr;
    __OSContReadFormat readformat;
    int i;

    ptr = (u8 *)__osContPifRam_800C4A20.ramarray;
    for (i = 0; i < 15; i++) {
        __osContPifRam_800C4A20.ramarray[i] = 0;
    }

    __osContPifRam_800C4A20.pifstatus = CONT_CMD_EXE;
    readformat.dummy = CONT_CMD_NOP;
    readformat.txsize = CONT_CMD_READ_BUTTON_TX;
    readformat.rxsize = CONT_CMD_READ_BUTTON_RX;
    readformat.cmd = CONT_CMD_READ_BUTTON;
    readformat.button = 0xFFFF;
    readformat.stick_x = -1;
    readformat.stick_y = -1;
    for (i = 0; i < __osMaxControllers; i++) {
        *(__OSContReadFormat *)ptr = readformat;
        ptr += sizeof(__OSContReadFormat);
    }
    *ptr = CONT_CMD_END;
}
