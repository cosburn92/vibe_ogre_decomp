#include "common.h"
#include "libultra.h"

__OSViContext *__osViGetCurrentContext(void) {
    return __osViCurr;
}
