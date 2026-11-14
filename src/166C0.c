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


/* ALStartParamAlt as n_audio lays it out */
typedef struct {
    /* 0x00 */ ALParam *next;
    /* 0x04 */ s32 delta;
    /* 0x08 */ s16 type;
    /* 0x0A */ s16 unity;
    /* 0x0C */ f32 pitch;
    /* 0x10 */ s16 volume;
    /* 0x12 */ u8 pan;
    /* 0x13 */ u8 fxMix;
    /* 0x14 */ s32 samples;
    /* 0x18 */ ALWaveTable *wave;
} ALStartParamAlt;

typedef struct {
    /* 0x00 */ ALParam *next;
    /* 0x04 */ s32 delta;
    /* 0x08 */ s16 type;
    /* 0x0C */ N_PVoice *pvoice;
} ALFreeParam;

Acmd *_pullSubFrame_800868DC(void *filter, s16 *inp, s16 *outp, s32 outCount, Acmd *p);
s16 _getVol_80086C3C(s16 ivol, s32 samples, s16 ratem, u16 ratel);
void _n_freePVoice(N_PVoice *pvoice);
void __freeParam_800889D4(ALParam *param);

Acmd *n_alEnvmixerPull(N_PVoice *filter, s32 sampleOffset, Acmd *p) {
    Acmd *ptr = p;
    N_PVoice *e = filter;
    s16 inp;
    s32 lastOffset;
    s32 thisOffset = sampleOffset;
    s32 samples;
    s16 loutp = 0;
    s32 fVol;
    ALParam *thisParam;
    s32 outCount = FIXED_SAMPLE;

    inp = 0;

    while (e->em_ctrlList != 0) {
        lastOffset = thisOffset;
        thisOffset = e->em_ctrlList->delta;
        samples = (((thisOffset - lastOffset) + FIXED_SAMPLE / 2) / FIXED_SAMPLE) * FIXED_SAMPLE;
        if (samples == 0) {
            thisOffset = lastOffset;
        }
        if (samples > outCount) {
            break;
        }

        switch (e->em_ctrlList->type) {
            case AL_FILTER_START_VOICE_ALT: {
                ALStartParamAlt *param = (ALStartParamAlt *)e->em_ctrlList;

                if (param->unity) {
                    e->rs_upitch = 1;
                }
                n_alLoadParam(e, 5, param->wave); /* AL_FILTER_SET_WAVETABLE */
                e->em_motion = 1;                 /* AL_PLAYING */
                e->em_first = 1;
                e->em_delta = 0;
                e->em_segEnd = ((param->samples + FIXED_SAMPLE / 2) / FIXED_SAMPLE) * FIXED_SAMPLE;
                e->em_volume = ((s32)param->volume * (s32)param->volume) >> 15;
                e->em_pan = param->pan;
                e->em_dryamt = D_800A9D40[param->fxMix];
                e->em_wetamt = D_800A9D40[N_EQPOWER_LENGTH - param->fxMix - 1];
                if (param->samples) {
                    e->em_cvolL = 1;
                    e->em_cvolR = 1;
                } else {
                    e->em_cvolL = (e->em_volume * D_800A9D40[e->em_pan]) >> 15;
                    e->em_cvolR = (e->em_volume * D_800A9D40[N_EQPOWER_LENGTH - e->em_pan - 1]) >> 15;
                }
                e->rs_ratio = param->pitch;
            } break;

            case AL_FILTER_SET_FXAMT:
            case AL_FILTER_SET_PAN:
            case AL_FILTER_SET_VOLUME:
                ptr = _pullSubFrame_800868DC(e, &inp, &loutp, samples, ptr);

                if (e->em_delta >= e->em_segEnd) {
                    e->em_ltgt = (e->em_volume * D_800A9D40[e->em_pan]) >> 15;
                    e->em_rtgt = (e->em_volume * D_800A9D40[N_EQPOWER_LENGTH - e->em_pan - 1]) >> 15;
                    e->em_delta = e->em_segEnd;
                    e->em_cvolL = e->em_ltgt;
                    e->em_cvolR = e->em_rtgt;
                } else {
                    e->em_cvolL = _getVol_80086C3C(e->em_cvolL, e->em_delta, e->em_lratm, e->em_lratl);
                    e->em_cvolR = _getVol_80086C3C(e->em_cvolR, e->em_delta, e->em_rratm, e->em_rratl);
                }

                if (e->em_cvolL == 0) {
                    e->em_cvolL = 1;
                }
                if (e->em_cvolR == 0) {
                    e->em_cvolR = 1;
                }

                if (e->em_ctrlList->type == AL_FILTER_SET_PAN) {
                    e->em_pan = (s16)e->em_ctrlList->data.i;
                }

                if (e->em_ctrlList->type == AL_FILTER_SET_VOLUME) {
                    e->em_delta = 0;
                    fVol = (e->em_ctrlList->data.i);
                    fVol = (fVol * fVol) >> 15;
                    e->em_volume = (s16)fVol;
                    e->em_segEnd = ((e->em_ctrlList->moredata.i + FIXED_SAMPLE / 2) / FIXED_SAMPLE) * FIXED_SAMPLE;
                }

                if (e->em_ctrlList->type == AL_FILTER_SET_FXAMT) {
                    e->em_dryamt = D_800A9D40[e->em_ctrlList->data.i];
                    e->em_wetamt = D_800A9D40[N_EQPOWER_LENGTH - e->em_ctrlList->data.i - 1];
                }

                e->em_first = 1;
                break;

            case AL_FILTER_START_VOICE: {
                ALParam *param = e->em_ctrlList;

                if (param->unity) {
                    e->rs_upitch = 1;
                }
                n_alLoadParam(e, 5, (void *)param->data.i);
                e->em_motion = 1;
            } break;

            case AL_FILTER_STOP_VOICE:
                ptr = _pullSubFrame_800868DC(e, &inp, &loutp, samples, ptr);
                n_alEnvmixerParam(e, 4, 0); /* AL_FILTER_RESET */
                break;

            case 0: { /* AL_FILTER_FREE_VOICE */
                ALFreeParam *param = (ALFreeParam *)e->em_ctrlList;

                param->pvoice->offset = 0;
                _n_freePVoice(param->pvoice);
            } break;

            case AL_FILTER_SET_PITCH:
                ptr = _pullSubFrame_800868DC(e, &inp, &loutp, samples, ptr);
                e->rs_ratio = e->em_ctrlList->data.f;
                break;

            case 8: /* AL_FILTER_SET_UNITY_PITCH */
                ptr = _pullSubFrame_800868DC(e, &inp, &loutp, samples, ptr);
                e->rs_upitch = 1;
                break;

            case 5: /* AL_FILTER_SET_WAVETABLE */
                ptr = _pullSubFrame_800868DC(e, &inp, &loutp, samples, ptr);
                n_alLoadParam(e, 5, (void *)e->em_ctrlList->data.i);
                break;

            default:
                ptr = _pullSubFrame_800868DC(e, &inp, &loutp, samples, ptr);
                n_alEnvmixerParam(e, e->em_ctrlList->type, (void *)e->em_ctrlList->data.i);
                break;
        }
        loutp += (samples << 1);
        outCount -= samples;

        thisParam = e->em_ctrlList;
        e->em_ctrlList = e->em_ctrlList->next;
        if (e->em_ctrlList == 0) {
            e->em_ctrlTail = 0;
        }
        __freeParam_800889D4(thisParam);
    }

    ptr = _pullSubFrame_800868DC(e, &inp, &loutp, outCount, ptr);

    if (e->em_delta > e->em_segEnd) {
        e->em_delta = e->em_segEnd;
    }
    return ptr;
}

s32 n_alEnvmixerParam(void *filter, s32 paramID, void *param) {
    N_PVoice *pv = filter;

    switch (paramID) {
        case AL_FILTER_ADD_UPDATE:
            if (pv->em_ctrlTail) {
                pv->em_ctrlTail->next = (ALParam *)param;
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
