#include "common.h"

/* NuSystem nugfxswapcfb.c */

typedef struct {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ void *framebuffer;
} NUScTaskFb;

void osViSwapBuffer(void *frameBufPtr);

/* nuGfxSwapCfb */
void func_8008B110(NUScTaskFb *gfxTask) {
    osViSwapBuffer(gfxTask->framebuffer);
}
