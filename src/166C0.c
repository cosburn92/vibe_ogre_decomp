#include "n_audio.h"

/* n_audio n_env.c */

void n_alLoadParam(void *filter, s32 paramID, void *param);
Acmd *n_alResamplePull(N_PVoice *e, s16 *outp, Acmd *p);
s16 _getRate_80086AFC(f64 vol, f64 tgt, s32 count, u16 *ratel);

extern s16 D_800A9D40[]; /* eqpower */

#define FIXED_SAMPLE 184
#define N_EQPOWER_LENGTH 128

#define n_aSetVolume(pkt, f, v, t, r)                                       \
    {                                                                       \
        Acmd *_a = (Acmd *)pkt;                                             \
                                                                            \
        _a->w0 = _SHIFTL(9, 24, 8) | _SHIFTL(f, 16, 8) | _SHIFTL(v, 0, 16); \
        _a->w1 = _SHIFTL(t, 16, 16) | _SHIFTL(r, 0, 16);                    \
    }

#define n_aEnvMixer(pkt, f, t, s)                                           \
    {                                                                       \
        Acmd *_a = (Acmd *)pkt;                                             \
                                                                            \
        _a->w0 = _SHIFTL(3, 24, 8) | _SHIFTL(f, 16, 8) | _SHIFTL(t, 0, 16); \
        _a->w1 = (u32)(s);                                                  \
    }


INCLUDE_ASM("asm/nonmatchings/166C0", n_alEnvmixerPull);

s32 n_alEnvmixerParam(void *filter, s32 paramID, void *param) {
    N_PVoice *pv = filter;

    switch (paramID) {
        case AL_FILTER_ADD_UPDATE:
            if (pv->em_ctrlTail) {
                ((ALParam *)pv->em_ctrlTail)->next = (ALParam *)param;
            } else {
                pv->em_ctrlList = (ALParam *)param;
            }
            pv->em_ctrlTail = (ALParam *)param;
            break;
        case 4: /* AL_FILTER_RESET */
            pv->em_first = 1;
            pv->em_motion = 0; /* AL_STOPPED */
            pv->em_volume = 1;
            pv->em_segEnd = 0;
            pv->rs_delta = 0.0;
            pv->rs_first = 1;
            pv->rs_upitch = 0;
            n_alLoadParam(pv, 4, param);
            break;
        case 9: /* AL_FILTER_START */
            pv->em_motion = 1; /* AL_PLAYING */
            break;
        default:
            n_alLoadParam(pv, paramID, param);
            break;
    }
    return 0;
}

Acmd *_pullSubFrame_800868DC(void *filter, s16 *inp, s16 *outp, s32 outCount, Acmd *p) {
    Acmd *ptr = p;
    N_PVoice *e = filter;

    if (e->em_motion != 1 || !outCount) { /* AL_PLAYING */
        return ptr;
    }

    ptr = n_alResamplePull(e, inp, p);

    if (e->em_first) {
        e->em_first = 0;

        e->em_ltgt = (e->em_volume * D_800A9D40[e->em_pan]) >> 15;
        e->em_lratm = _getRate_80086AFC((f64)e->em_cvolL, (f64)e->em_ltgt, e->em_segEnd, &e->em_lratl);
        e->em_rtgt = (e->em_volume * D_800A9D40[N_EQPOWER_LENGTH - e->em_pan - 1]) >> 15;
        e->em_rratm = _getRate_80086AFC((f64)e->em_cvolR, (f64)e->em_rtgt, e->em_segEnd, &e->em_rratl);

        n_aSetVolume(ptr++, 0, e->em_ltgt, e->em_lratm, e->em_lratl);
        n_aSetVolume(ptr++, 6, e->em_cvolL, e->em_dryamt, e->em_wetamt); /* A_VOL | A_LEFT */
        n_aSetVolume(ptr++, 4, e->em_rtgt, e->em_rratm, e->em_rratl);    /* A_VOL | A_RIGHT */
        n_aEnvMixer(ptr++, 1, e->em_cvolR, osVirtualToPhysical(e->em_state)); /* A_INIT */
    } else {
        n_aEnvMixer(ptr++, 0, 0, osVirtualToPhysical(e->em_state)); /* A_CONTINUE */
    }

    *inp += FIXED_SAMPLE << 1;
    e->em_delta += FIXED_SAMPLE;

    return ptr;
}

s16 _getRate_80086AFC(f64 vol, f64 tgt, s32 count, u16 *ratel) {
    s16 s;
    f64 invn, a, fs;
    s32 i;

    if (count == 0) {
        if (tgt >= vol) {
            *ratel = 0xFFFF;
            return 0x7FFF;
        } else {
            *ratel = 0;
            return -0x8000;
        }
    }

    invn = 1.0 / count;
    if (tgt < 1.0) {
        tgt = 1.0;
    }
    if (vol <= 0) {
        vol = 1;
    }

    a = (tgt - vol) * invn * 8.0;
    s = (s16)a;
    fs = a - s;
    fs += 1.0;
    i = fs;
    fs -= (s16)i;
    s--;
    s += i;
    *ratel = (u16)(fs * 65535.0);
    return s;
}

s16 _getVol_80086C3C(s16 ivol, s32 samples, s16 ratem, u16 ratel) {
    s32 tmpl;

    samples >>= 3;
    if (samples == 0) {
        return ivol;
    }
    tmpl = ratel * samples;
    tmpl >>= 16;
    tmpl += ratem * samples;
    return ivol + tmpl;
}
