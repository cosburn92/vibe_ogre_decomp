#include "n_audio.h"

/* n_audio n_env.c */

void n_alLoadParam(void *filter, s32 paramID, void *param);

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

INCLUDE_ASM("asm/nonmatchings/166C0", _pullSubFrame_800868DC);

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
