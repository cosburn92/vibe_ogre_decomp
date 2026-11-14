#include "common.h"

/* NuSystem nugfxtaskallendwait.c */

extern volatile u32 D_800E79A4; /* nuGfxTaskSpool */

void nuGfxTaskAllEndWait(void) {
    while (D_800E79A4) {
    }
}
