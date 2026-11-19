#include "common.h"

typedef struct {
    /* 0x00 */ u32 type;
    /* 0x04 */ u32 flags;
} OSTaskHead;

u32 __osSpGetStatus(void);

s32 osSpTaskYielded(OSTaskHead *tp) {
    s32 status;
    s32 result;

    status = __osSpGetStatus();
    result = (status & 0x100) ? 1 : 0; /* SP_STATUS_YIELDED -> OS_TASK_YIELDED */
    if (status & 0x80) { /* SP_STATUS_YIELD */
        tp->flags |= result;
        tp->flags &= ~2; /* OS_TASK_DP_WAIT */
    }
    return result;
}
