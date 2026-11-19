#include "common.h"
#include "libultra.h"

/* libultra contramwrite.c */

extern s32 D_800ABAB0; /* __osPfsLastChannel */

void _bcopy(const void *src, void *dst, s32 len);

s32 __osContRamWrite(OSMesgQueue *mq, int channel, u16 address, u8 *buffer, int force) {
    s32 ret = 0;
    int i;
    u8 *ptr;
    int retry = 2;
    u8 crc;

    if ((force != 1) && (address < PFS_LABEL_AREA) && (address != 0)) {
        return 0;
    }

    __osSiGetAccess();
    do {
        ptr = (u8 *)&__osPfsPifRam_800E86C0;
        if (__osContLastCmd != CONT_CMD_WRITE_MEMPACK || D_800ABAB0 != channel) {
            __osContLastCmd = CONT_CMD_WRITE_MEMPACK;
            D_800ABAB0 = channel;
            for (i = 0; i < channel; i++) {
                *ptr++ = 0;
            }
            __osPfsPifRam_800E86C0.pifstatus = CONT_CMD_EXE;
            ((__OSContRamReadFormat *)ptr)->dummy = CONT_CMD_NOP;
            ((__OSContRamReadFormat *)ptr)->txsize = CONT_CMD_WRITE_MEMPACK_TX;
            ((__OSContRamReadFormat *)ptr)->rxsize = CONT_CMD_WRITE_MEMPACK_RX;
            ((__OSContRamReadFormat *)ptr)->cmd = CONT_CMD_WRITE_MEMPACK;
            ((__OSContRamReadFormat *)ptr)->datacrc = CONT_CMD_NOP;
            ptr[sizeof(__OSContRamReadFormat)] = CONT_CMD_END;
        } else {
            ptr += channel;
        }
        ((__OSContRamReadFormat *)ptr)->addrh = address >> 3;
        ((__OSContRamReadFormat *)ptr)->addrl = ((address << 5) | __osContAddressCrc(address));
        _bcopy(buffer, ((__OSContRamReadFormat *)ptr)->data, BLOCKSIZE);
        ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam_800E86C0);
        crc = __osContDataCrc(buffer);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam_800E86C0);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        ret = CHNL_ERR(*(__OSContRamReadFormat *)ptr);
        if (ret == 0) {
            if (crc != ((__OSContRamReadFormat *)ptr)->datacrc) {
                if ((ret = __osPfsGetStatus(mq, channel)) != 0) {
                    break;
                }
                ret = PFS_ERR_CONTRFAIL;
            }
        } else {
            ret = PFS_ERR_NOPACK;
        }
    } while ((ret == PFS_ERR_CONTRFAIL) && (retry-- >= 0));
    __osSiRelAccess();
    return ret;
}

/* The original object carries 0x60 more bytes of padding after this function */
asm(".space 0x60");
