#include "common.h"

s32 __osSpSetPc(u32 pc);

s32 osAfterPreNMI(void) {
    return __osSpSetPc(0);
}
