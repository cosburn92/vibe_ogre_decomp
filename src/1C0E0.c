#include "common.h"
#include "libultra.h"

extern OSPiHandle *__osPiTable;

s32 osEPiLinkHandle(OSPiHandle *EPiHandle) {
    u32 saveMask = __osDisableInt();

    EPiHandle->next = __osPiTable;
    __osPiTable = EPiHandle;
    __osRestoreInt(saveMask);
    return 0;
}
