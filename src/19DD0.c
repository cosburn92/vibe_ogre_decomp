#include "common.h"

/* NuSystem nugfxswapcfbfuncset.c */

extern void *D_800A9E84; /* nuGfxSwapCfbFunc */

u32 osSetIntMask(u32 mask);

/* nuGfxSwapCfbFuncSet */
void func_800899D0(void *func) {
    u32 mask;

    mask = osSetIntMask(1);
    D_800A9E84 = func;
    osSetIntMask(mask);
}
