#include "common.h"

/* NuSystem nugfxfuncset.c */

extern void *D_800AA090; /* nuGfxFunc */

u32 osSetIntMask(u32 mask);
void nuGfxTaskAllEndWait(void);

/* nuGfxFuncSet */
void func_80089990(void *func) {
    u32 mask;

    nuGfxTaskAllEndWait();
    mask = osSetIntMask(1);
    D_800AA090 = func;
    osSetIntMask(mask);
}
