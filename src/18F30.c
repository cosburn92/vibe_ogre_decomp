#include "n_audio.h"

/* n_audio n_save.c */

Acmd *func_80088BD0(s32 sampleOffset, Acmd *p); /* n_alMainBusPull */

/* n_alSavePull */
Acmd *func_80088B30(s32 sampleOffset, Acmd *p) {
    Acmd *ptr = p;

    ptr = func_80088BD0(sampleOffset, ptr);
    {
        Acmd *_a = ptr++; /* n_aInterleave */

        _a->w0 = 0x0D000000;
    }
    {
        Acmd *_a = ptr++; /* n_aSaveBuffer(FIXED_SAMPLE << 2, 0, n_syn->sv_dramout) */

        _a->w0 = 0x062E0000;
        _a->w1 = *(s32 *)((u8 *)alGlobals_800A9E54 + 0x48);
    }
    return ptr;
}
