#include "common.h"
#include "libultra.h"

#define SP_STATUS_REG 0x04040010

void __osSpSetStatus(u32 data) {
    IO_WRITE(SP_STATUS_REG, data);
}
