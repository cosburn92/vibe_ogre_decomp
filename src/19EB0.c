#include "common.h"

/* NuSystem nugfxsetcfb.c */

extern void **D_800E8290; /* nuGfxCfb */
extern u32 D_800A9E80;    /* nuGfxCfbNum */
extern u32 D_800C4BC4;    /* nuGfxCfbCounter */
extern void *D_800E8210;  /* nuGfxCfb_ptr */

void func_80089A30(u32 retrace_num); /* nuGfxRetraceWait */
void func_80089528(u8 frameBufferNum); /* nuScSetFrameBufferNum */
void *osViGetCurrentFramebuffer(void);

/* nuGfxSetCfb */
void func_80089AB0(void **framebuf, u32 framebufnum) {
    u32 cnt;

    D_800E8290 = framebuf;
    D_800A9E80 = framebufnum;
    D_800C4BC4 = 0;
    D_800E8210 = framebuf[0];

    func_80089A30(1);
    func_80089528(framebufnum);

    if (framebufnum > 1) {
        for (cnt = 0; cnt < framebufnum - 1; cnt++) {
            if (D_800E8290[cnt] != D_800E8290[cnt + 1]) {
                break;
            }
        }
        if (cnt == framebufnum - 1) {
            func_80089528(1);
        } else {
            for (cnt = 0; cnt < framebufnum; cnt++) {
                if (osViGetCurrentFramebuffer() != D_800E8290[cnt]) {
                    D_800C4BC4 = cnt;
                    D_800E8210 = D_800E8290[cnt];
                    break;
                }
            }
        }
    }
}
