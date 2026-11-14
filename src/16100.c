#include "common.h"

/* n_audio n_auxbus.c */

typedef struct {
    u32 w0;
    u32 w1;
} Acmd;

typedef struct {
    /* 0x00 */ u8 filter[0x14];
    /* 0x14 */ s32 sourceCount;
    /* 0x18 */ s32 maxSources;
    /* 0x1C */ void **sources;
} N_ALAuxBus;

typedef struct {
    /* 0x00 */ u8 pad00[0x34];
    /* 0x34 */ N_ALAuxBus *auxBus;
} N_ALSynth;

#define aClearBuffer(pkt, d, c)                \
    {                                          \
        Acmd *_a = (Acmd *)pkt;                \
                                               \
        _a->w0 = (2 << 24) | ((d) & 0xFFFFFF); \
        _a->w1 = (u32)(c);                     \
    }

extern N_ALSynth *alGlobals_800A9E54; /* n_syn */

Acmd *n_alEnvmixerPull(void *filter, s32 sampleOffset, Acmd *p);

/* n_alAuxBusPull */
Acmd *func_80085D00(s32 sampleOffset, Acmd *p) {
    Acmd *ptr = p;
    N_ALAuxBus *m = alGlobals_800A9E54->auxBus;
    void **sources = m->sources;
    s32 i;

    aClearBuffer(ptr++, 0x7C0, 0x2E0); /* N_AL_AUX_L_OUT, N_AL_DIVIDED << 1 */
    for (i = 0; i < m->sourceCount; i++) {
        ptr = n_alEnvmixerPull(sources[i], sampleOffset, ptr);
    }
    return ptr;
}
