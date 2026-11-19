#include "common.h"
#include "libultra.h"

/* libultra pfsrepairid.c */

s32 osPfsRepairId(OSPfs *pfs) {
    s32 ret;

    if ((pfs->status & PFS_INITIALIZED) || (pfs->status & PFS_ID_BROKEN)) {
        ret = __osGetId(pfs);
        if (ret == 0) {
            pfs->status &= ~PFS_ID_BROKEN;
        }
    } else {
        ret = PFS_ERR_INVALID;
    }
    return ret;
}
