#include "common.h"

/* NuSystem nucontdatalock.c */

extern u32 D_800C4B30; /* nuContDataLockKey */

u32 osSetIntMask(u32 mask);

/* nuContDataLock */
void func_8008A5A0(void) {
    u32 mask;

    mask = osSetIntMask(1); /* OS_IM_NONE */
    D_800C4B30 = 1;         /* NU_CONT_DATA_LOCK */
    osSetIntMask(mask);
}

/* nuContDataUnLock */
void func_8008A5D0(void) {
    u32 mask;

    mask = osSetIntMask(1);
    D_800C4B30 = 0;
    osSetIntMask(mask);
}
