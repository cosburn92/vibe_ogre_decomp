#include "common.h"
#include "libultra.h"

#define SP_STATUS_REG 0x04040010

u32 __osSpGetStatus(void) {
    return IO_READ(SP_STATUS_REG);
}
