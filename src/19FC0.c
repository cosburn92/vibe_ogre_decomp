#include "common.h"

/* NuSystem nugfxdisplayoff.c / nugfxdisplayon.c helper */

extern u32 osTvType;
extern u32 D_800C4BD8; /* nuGfxDisplay */

void osViSetYScale(f32 scale);
void osViBlack(u8 active);
void func_80089BE4(u8 active);

/* nuGfxDisplayOff */
void func_80089BC0(void) {
    D_800C4BD8 = 0;
    func_80089BE4(1);
}

/* osViBlack wrapper that also fixes the PAL vertical scale */
void func_80089BE4(u8 active) {
    if (osTvType == 0) {
        if (active == 1) {
            osViSetYScale(1.0f);
        } else {
            osViSetYScale(0.833f);
        }
    }
    osViBlack(active);
}
