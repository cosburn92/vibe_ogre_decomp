#include "common.h"

/* n_audio n_resample.c */

typedef struct {
    u32 w0;
    u32 w1;
} Acmd;

/* n_audio N_PVoice (resampler and decoder parts) */
typedef struct {
    /* 0x00 */ u8 pad00[0x40];
    /* 0x40 */ void *rs_state;
    /* 0x44 */ f32 rs_ratio;
    /* 0x48 */ s32 rs_upitch;
    /* 0x4C */ f32 rs_delta;
    /* 0x50 */ s32 rs_first;
} N_PVoice;

#define UNITY_PITCH 0x8000
#define MAX_RATIO 1.99996
#define FIXED_SAMPLE 184
#define N_AL_DECODER_OUT 0x170

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))

#define aDMEMMove(pkt, dmemi, dmemo, count)                         \
    {                                                               \
        Acmd *_a = (Acmd *)pkt;                                     \
                                                                    \
        _a->w0 = _SHIFTL(10, 24, 8) | _SHIFTL(dmemi, 0, 24);        \
        _a->w1 = _SHIFTL(dmemo, 16, 16) | _SHIFTL(count, 0, 16);    \
    }

#define n_aResample(pkt, s, f, p, i)                                        \
    {                                                                       \
        Acmd *_a = (Acmd *)pkt;                                             \
                                                                            \
        _a->w0 = _SHIFTL(5, 24, 8) | _SHIFTL(s, 0, 24);                     \
        _a->w1 = _SHIFTL(f, 30, 2) | _SHIFTL(p, 14, 16) | _SHIFTL(i, 2, 12); \
    }

Acmd *n_alAdpcmPull(N_PVoice *f, s16 *outp, s32 byteCount, Acmd *p);
s32 n_alLoadParam(void *filter, s32 paramID, void *param);
u32 osVirtualToPhysical(void *addr);

Acmd *n_alResamplePull(N_PVoice *e, s16 *outp, Acmd *p) {
    Acmd *ptr = p;
    s16 inp;
    s32 inCount;
    s32 incr;
    f32 finCount;

    inp = N_AL_DECODER_OUT;

    if (e->rs_upitch) {
        ptr = n_alAdpcmPull(e, &inp, FIXED_SAMPLE, p);
        aDMEMMove(ptr++, inp, *outp, FIXED_SAMPLE << 1);
    } else {
        if (e->rs_ratio > MAX_RATIO) {
            e->rs_ratio = MAX_RATIO;
        }
        e->rs_ratio = (s32)(e->rs_ratio * UNITY_PITCH) / (f32)UNITY_PITCH;
        finCount = e->rs_delta + (FIXED_SAMPLE * e->rs_ratio);
        inCount = (s32)finCount;
        e->rs_delta = finCount - (f32)inCount;
        ptr = n_alAdpcmPull(e, &inp, inCount, p);
        incr = (s32)(e->rs_ratio * UNITY_PITCH);
        n_aResample(ptr++, osVirtualToPhysical(e->rs_state), e->rs_first, incr, inp);
        e->rs_first = 0;
    }
    return ptr;
}

s32 n_alResampleParam(void *filter, s32 paramID, void *param) {
    n_alLoadParam(filter, paramID, param);
    return 0;
}
