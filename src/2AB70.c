#include "common.h"
#include "libultra.h"

#define SP_STATUS_REG 0x04040010
#define SP_PC_REG 0x04080000

s32 __osSpSetPc(u32 pc) {
    register u32 stat = IO_READ(SP_STATUS_REG);

    if (!(stat & 0x0001)) { /* SP_STATUS_HALT */
        return -1;
    }
    IO_WRITE(SP_PC_REG, pc);
    return 0;
}
