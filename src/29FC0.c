#include "common.h"
#include "libultra.h"

s32 __osAiDeviceBusy(void) {
    register s32 status = IO_READ(AI_STATUS_REG);

    if (status & 0x80000000) { /* AI_STATUS_FIFO_FULL */
        return 1;
    } else {
        return 0;
    }
}
