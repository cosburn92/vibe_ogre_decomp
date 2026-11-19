#include "common.h"
#include "libultra.h"

/* NuSystem nuboot.c (built without optimization) */

#define NU_IDLE_THREAD_ID 1
#define NU_MAIN_THREAD_ID 3
#define NU_IDLE_THREAD_PRI 0
#define NU_MAIN_THREAD_PRI 10
#define OS_VI_NTSC_LAN1 2
#define NU_IDLE_STACK_SIZE 0x2000

extern OSThread gIdleThread;
extern OSThread gMainThread;
extern u64 gIdleThreadStack[];
extern u64 D_800C6D60[];        /* end of the main thread stack */
extern void (*D_800E7A18)(void); /* nuIdleFunc */

void IdleThreadEntry(void *arg);
void MainThreadEntry(void *arg);
void osInitialize(void);
void osSetThreadPri(OSThread *t, s32 pri);
void osViSetSpecialFeatures(u32 func);
void func_80089F40(void);           /* nuPiInit */
void func_80088C50(u8 mode, u8 numFields); /* nuScCreateScheduler */

void main(void) {
    osInitialize();
    osCreateThread(&gIdleThread, NU_IDLE_THREAD_ID, IdleThreadEntry, NULL,
                   gIdleThreadStack + NU_IDLE_STACK_SIZE / sizeof(u64), 10);
    osStartThread(&gIdleThread);
}

void IdleThreadEntry(void *arg) {
    D_800E7A18 = NULL;
    func_80089F40();
    func_80088C50(OS_VI_NTSC_LAN1, 1);
    osViSetSpecialFeatures(0x5A);
    osCreateThread(&gMainThread, NU_MAIN_THREAD_ID, MainThreadEntry, NULL, D_800C6D60, NU_MAIN_THREAD_PRI);
    osStartThread(&gMainThread);
    osSetThreadPri(&gIdleThread, NU_IDLE_THREAD_PRI);
    while (1) {
        if (D_800E7A18 != NULL) {
            (*D_800E7A18)();
        }
    }
}
