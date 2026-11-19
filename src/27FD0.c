#include "common.h"
#include "libultra.h"

/* libultra contramread.c */

extern s32 D_800ABAB0; /* __osPfsLastChannel */

void _bcopy(const void *src, void *dst, s32 len);

s32 __osContRamRead(OSMesgQueue *mq, int channel, u16 address, u8 *buffer) {
    s32 ret;
    int i;
    u8 *ptr;
    int retry = 2;

    __osSiGetAccess();
    do {
        ptr = (u8 *)&__osPfsPifRam_800E86C0;
        if (__osContLastCmd != CONT_CMD_READ_MEMPACK || D_800ABAB0 != channel) {
            __osContLastCmd = CONT_CMD_READ_MEMPACK;
            D_800ABAB0 = channel;
            for (i = 0; i < channel; i++) {
                *ptr++ = 0;
            }
            __osPfsPifRam_800E86C0.pifstatus = CONT_CMD_EXE;
            ((__OSContRamReadFormat *)ptr)->dummy = CONT_CMD_NOP;
            ((__OSContRamReadFormat *)ptr)->txsize = CONT_CMD_READ_MEMPACK_TX;
            ((__OSContRamReadFormat *)ptr)->rxsize = CONT_CMD_READ_MEMPACK_RX;
            ((__OSContRamReadFormat *)ptr)->cmd = CONT_CMD_READ_MEMPACK;
            ((__OSContRamReadFormat *)ptr)->datacrc = CONT_CMD_NOP;
            ptr[sizeof(__OSContRamReadFormat)] = CONT_CMD_END;
        } else {
            ptr += channel;
        }
        ((__OSContRamReadFormat *)ptr)->addrh = address >> 3;
        ((__OSContRamReadFormat *)ptr)->addrl = (u8)(__osContAddressCrc(address) | (address << 5));
        ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam_800E86C0);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam_800E86C0);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        ret = CHNL_ERR(*(__OSContRamReadFormat *)ptr);
        if (ret == 0) {
            if (__osContDataCrc(((__OSContRamReadFormat *)ptr)->data) != ((__OSContRamReadFormat *)ptr)->datacrc) {
                ret = __osPfsGetStatus(mq, channel);
                if (ret != 0) {
                    break;
                }
                ret = PFS_ERR_CONTRFAIL;
            } else {
                _bcopy(((__OSContRamReadFormat *)ptr)->data, buffer, BLOCKSIZE);
            }
        } else {
            ret = PFS_ERR_NOPACK;
        }
    } while ((ret == PFS_ERR_CONTRFAIL) && (retry-- >= 0));
    __osSiRelAccess();
    return ret;
}
