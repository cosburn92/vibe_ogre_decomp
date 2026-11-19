#include "common.h"
#include "libultra.h"

extern u8 D_800AA450; /* hdwrBugFlag */

s32 __osAiDeviceBusy(void);

s32 osAiSetNextBuffer(void *bufPtr, u32 size) {
    char *bptr;

    if (__osAiDeviceBusy()) {
        return -1;
    }
    bptr = bufPtr;
    if (D_800AA450) {
        bptr -= 0x2000;
    }
    if ((((u32)bufPtr + size) & 0x1FFF) == 0) {
        D_800AA450 = 1;
    } else {
        D_800AA450 = 0;
    }
    IO_WRITE(AI_DRAM_ADDR_REG, osVirtualToPhysical(bptr));
    IO_WRITE(AI_LEN_REG, size);
    return 0;
}
