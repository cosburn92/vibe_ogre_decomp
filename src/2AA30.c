#include "common.h"
#include "libultra.h"

/* libultra dpsetnextbuf.c */

#define DPC_START_REG 0x04100000
#define DPC_END_REG 0x04100004
#define DPC_STATUS_REG 0x0410000C
#define DPC_CLR_XBUS_DMEM_DMA 0x0001
#define DPC_STATUS_XBUS_DMEM_DMA 0x001

s32 __osDpDeviceBusy(void);

s32 osDpSetNextBuffer(void *buf, u64 size) {
    if (__osDpDeviceBusy()) {
        return -1;
    }
    IO_WRITE(DPC_STATUS_REG, DPC_CLR_XBUS_DMEM_DMA);
    do {
    } while (IO_READ(DPC_STATUS_REG) & DPC_STATUS_XBUS_DMEM_DMA);
    IO_WRITE(DPC_START_REG, osVirtualToPhysical(buf));
    IO_WRITE(DPC_END_REG, osVirtualToPhysical(buf) + size);
    return 0;
}
