#include "common.h"

extern void (*D_800A9E8C)(void *); /* graphics-task callback for flag 0x10 */

u32 osSetIntMask(u32 mask);

void func_8008AFA0(void (*func)(void *)) {
    u32 mask;

    mask = osSetIntMask(1);
    D_800A9E8C = func;
    osSetIntMask(mask);
}
