#include "common.h"
#include "libultra.h"

/* libultra vi.c */

#define VI_STATUS_REG 0x04400000
#define VI_CURRENT_REG 0x04400010

extern __OSViContext vi_contexts[2];
extern s32 osTvType;
extern OSViMode osViModePalLan1;
extern OSViMode osViModeMpalLan1;
extern OSViMode osViModeNtscLan1;

void bzero(void *p, s32 n);
void __osViSwapContext(void);

void __osViInit(void) {
    bzero(vi_contexts, sizeof(vi_contexts));
    __osViCurr = &vi_contexts[0];
    __osViNext = &vi_contexts[1];
    __osViNext->retraceCount = 1;
    __osViCurr->retraceCount = 1;
    __osViNext->framep = (void *)0x80000000;
    __osViCurr->framep = (void *)0x80000000;
    if (osTvType == 0) { /* OS_TV_PAL */
        __osViNext->modep = &osViModePalLan1;
    } else if (osTvType == 2) { /* OS_TV_MPAL */
        __osViNext->modep = &osViModeMpalLan1;
    } else {
        __osViNext->modep = &osViModeNtscLan1;
    }
    __osViNext->state = VI_STATE_BLACK;
    __osViNext->control = __osViNext->modep->comRegs.ctrl;
    while (IO_READ(VI_CURRENT_REG) > 10) {
    }
    IO_WRITE(VI_STATUS_REG, 0);
    __osViSwapContext();
}
