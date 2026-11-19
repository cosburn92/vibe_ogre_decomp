#include "common.h"
#include "libultra.h"

#define SP_STATUS_REG 0x04040010

s32 __osSpDeviceBusy(void) {
    register u32 stat = IO_READ(SP_STATUS_REG);

    if (stat & (0x04 | 0x08 | 0x10)) { /* SP_STATUS_DMA_BUSY | SP_STATUS_DMA_FULL | SP_STATUS_IO_FULL */
        return 1;
    }
    return 0;
}
