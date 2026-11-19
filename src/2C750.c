#include "common.h"
#include "libultra.h"

#define DPC_STATUS_REG 0x0410000C

s32 __osDpDeviceBusy(void) {
    register u32 stat = IO_READ(DPC_STATUS_REG);

    if (stat & 0x100) { /* DPC_STATUS_DMA_BUSY */
        return 1;
    }
    return 0;
}
