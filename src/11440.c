#include "common.h"

typedef void (*MusFrameCallback)(s32 type, s32 frame);

extern MusFrameCallback D_800A9894;

u32 osSetIntMask(u32 mask);

void func_80081040(MusFrameCallback cb) {
    u32 mask = osSetIntMask(1);

    D_800A9894 = cb;
    osSetIntMask(mask);
}
