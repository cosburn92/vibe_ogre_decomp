#include "common.h"
#include "libultra.h"

extern OSDevMgr __osPiDevMgr;

OSMesgQueue *osPiGetCmdQueue(void) {
    if (!__osPiDevMgr.active) {
        return NULL;
    }
    return __osPiDevMgr.cmdQueue;
}
