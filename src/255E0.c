#include "common.h"
#include "libultra.h"

void *osViGetNextFramebuffer(void) {
    register u32 saveMask = __osDisableInt();
    void *framep = __osViNext->framep;

    __osRestoreInt(saveMask);
    return framep;
}
