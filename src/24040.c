#include "common.h"

void __osSpSetStatus(u32 data);

void osSpTaskYield(void) {
    __osSpSetStatus(0x400); /* SP_SET_YIELD */
}
