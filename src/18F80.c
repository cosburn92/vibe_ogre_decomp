#include "n_audio.h"

/* n_audio n_synallocfx.c and n_mainbus.c */

void n_alFxNew(void *fx, void *c, void *hp);

/* n_alSynAllocFX */
void *func_80088B80(s16 bus, void *c, void *hp) {
    n_alFxNew(&alGlobals_800A9E54->auxBus->fxArr[bus], c, hp);
    return alGlobals_800A9E54->auxBus->fxArr[bus];
}

/* n_alMainBusPull */
Acmd *func_80088BD0(s32 sampleOffset, Acmd *p) {
    Acmd *ptr = p;
    Acmd *(*handler)(s32, Acmd *);

    {
        Acmd *_a = ptr++; /* aClearBuffer(N_AL_MAIN_L_OUT, N_AL_DIVIDED << 1) */

        _a->w0 = 0x020004E0;
        _a->w1 = 0x2E0;
    }
    handler = *(void **)(*(u8 **)((u8 *)alGlobals_800A9E54 + 0x30) + 4);
    ptr = handler(sampleOffset, ptr);
    {
        Acmd *_a = ptr++; /* n_aMix(0, 0x7FFF, N_AL_AUX_L_OUT, N_AL_MAIN_L_OUT) */

        _a->w0 = 0x0C007FFF;
        _a->w1 = 0x07C004E0;
    }
    {
        Acmd *_a = ptr++; /* n_aMix(0, 0x7FFF, N_AL_AUX_R_OUT, N_AL_MAIN_R_OUT) */

        _a->w0 = 0x0C007FFF;
        _a->w1 = 0x09300650;
    }
    return ptr;
}
