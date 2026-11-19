#include "common.h"

extern u32 D_800A9E70; /* nuRDPOutputBufSize */

void nuGfxTaskAllEndWait(void);
u32 osSetIntMask(u32 mask);

/* Sets the RDP output buffer size once every graphics task has finished */
void func_8008AF60(u32 size) {
    u32 mask;

    nuGfxTaskAllEndWait();
    mask = osSetIntMask(1);
    D_800A9E70 = size;
    osSetIntMask(mask);
}
