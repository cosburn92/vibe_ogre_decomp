#include "common.h"
#include "libultra.h"

#define SI_STATUS_REG 0x04800018

s32 __osSiDeviceBusy(void) {
    register u32 stat = IO_READ(SI_STATUS_REG);

    if (stat & (0x0001 | 0x0002)) { /* SI_STATUS_DMA_BUSY | SI_STATUS_RD_BUSY */
        return 1;
    }
    return 0;
}
