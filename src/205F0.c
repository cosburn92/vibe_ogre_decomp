#include "common.h"
#include "libultra.h"

/* libultra contquery.c */

void __osPackRequestData(u8 cmd);
void __osContGetInitData(u8 *pattern, OSContStatus *data);

s32 osContStartQuery(OSMesgQueue *mq) {
    s32 ret;

    __osSiGetAccess();
    if (__osContLastCmd != CONT_CMD_REQUEST_STATUS) {
        __osPackRequestData(CONT_CMD_REQUEST_STATUS);
        ret = __osSiRawStartDma(OS_WRITE, &__osContPifRam_800C4A20);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    }
    ret = __osSiRawStartDma(OS_READ, &__osContPifRam_800C4A20);
    __osContLastCmd = CONT_CMD_REQUEST_STATUS;
    __osSiRelAccess();
    return ret;
}

void osContGetQuery(OSContStatus *data) {
    u8 pattern;

    __osContGetInitData(&pattern, data);
}
