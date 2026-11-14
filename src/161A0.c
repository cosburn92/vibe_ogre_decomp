#include "n_audio.h"

/* n_audio n_reverb.c (n_alFxNew) and n_synallocvoice/drvrNew (alN_PVoiceNew) */

/* n_audio ALSynConfig */
typedef struct {
    /* 0x00 */ s32 maxVVoices;
    /* 0x04 */ s32 maxPVoices;
    /* 0x08 */ s32 maxUpdates;
    /* 0x0C */ s32 maxFXbusses;
    /* 0x10 */ void *dmaproc;
    /* 0x14 */ void *heap;
    /* 0x18 */ s32 outputRate;
    /* 0x1C */ u8 fxType;
    /* 0x20 */ s32 *params;
} ALSynConfig;

extern s32 D_800A9BB0[]; /* SMALLROOM_PARAMS */
extern s32 D_800A9C18[]; /* BIGROOM_PARAMS */
extern s32 D_800A9CA0[]; /* ECHO_PARAMS */
extern s32 D_800A9CC8[]; /* CHORUS_PARAMS */
extern s32 D_800A9CF0[]; /* FLANGE_PARAMS */
extern s32 D_800A9D18[]; /* NULL_PARAMS */

void init_lpfilter(ALLowPass *lp);

#define RANGE 2.0
#define CONVERT 173123.404906676
#define LENGTH (d->output - d->input)

void n_alFxNew(ALFx **fx_ar, ALSynConfig *c, void *hp) {
    u16 i, j, k;
    s32 *param = 0;
    ALDelay *d;
    ALFx *r;

    *fx_ar = r = (ALFx *)alHeapAlloc(hp, 1, sizeof(ALFx));

    switch (c->fxType) {
        case 1: /* AL_FX_SMALLROOM */
            param = D_800A9BB0;
            break;
        case 2: /* AL_FX_BIGROOM */
            param = D_800A9C18;
            break;
        case 5: /* AL_FX_ECHO */
            param = D_800A9CA0;
            break;
        case 3: /* AL_FX_CHORUS */
            param = D_800A9CC8;
            break;
        case 4: /* AL_FX_FLANGE */
            param = D_800A9CF0;
            break;
        case 6: /* AL_FX_CUSTOM */
            param = c->params;
            break;
        default:
            param = D_800A9D18;
            break;
    }

    j = 0;

    r->section_count = param[j++];
    r->length = param[j++];

    r->delay = alHeapAlloc(hp, r->section_count, sizeof(ALDelay));
    r->base = alHeapAlloc(hp, r->length, sizeof(s16));
    r->input = r->base;

    for (k = 0; k < r->length; k++) {
        r->base[k] = 0;
    }

    for (i = 0; i < r->section_count; i++) {
        d = &r->delay[i];
        d->input = param[j++];
        d->output = param[j++];
        d->fbcoef = param[j++];
        d->ffcoef = param[j++];
        d->gain = param[j++];

        if (param[j]) {
            d->rsinc = ((((f32)param[j++]) / 1000) * RANGE) / c->outputRate;
            d->rsgain = (((f32)param[j++]) / CONVERT) * LENGTH;
            d->rsval = 1.0;
            d->rsdelta = 0.0;
            d->rs = alHeapAlloc(hp, 1, sizeof(ALResampler));
            d->rs->state = alHeapAlloc(hp, 1, 0x20);
            d->rs->delta = 0.0;
            d->rs->first = 1;
        } else {
            d->rs = 0;
            j++;
            j++;
        }

        if (param[j]) {
            d->lp = alHeapAlloc(hp, 1, sizeof(ALLowPass));
            d->lp->fstate = alHeapAlloc(hp, 1, 8); /* POLEF_STATE */
            d->lp->fc = param[j++];
            init_lpfilter(d->lp);
        } else {
            d->lp = 0;
            j++;
        }
    }
}

void alN_PVoiceNew(N_PVoice *mv, ALDMANew dmaNew, void *hp) {
    mv->dc_state = alHeapAlloc(hp, 1, 0x20);
    mv->dc_lstate = alHeapAlloc(hp, 1, 0x20);
    mv->dc_dma = dmaNew(&mv->dc_dmaState);
    mv->dc_lastsam = 0;
    mv->dc_first = 1;
    mv->dc_memin = 0;

    mv->rs_state = alHeapAlloc(hp, 1, 0x20);
    mv->rs_delta = 0.0;
    mv->rs_first = 1;
    mv->rs_ratio = 1.0;
    mv->rs_upitch = 0;

    mv->em_state = alHeapAlloc(hp, 1, 0x50);
    mv->em_first = 1;
    mv->em_motion = 0; /* AL_STOPPED */
    mv->em_volume = 1;
    mv->em_ltgt = 1;
    mv->em_rtgt = 1;
    mv->em_cvolL = 1;
    mv->em_cvolR = 1;
    mv->em_dryamt = 0;
    mv->em_wetamt = 0;
    mv->em_lratm = 1;
    mv->em_lratl = 0;
    mv->em_lratm = 1;
    mv->em_lratl = 0;
    mv->em_delta = 0;
    mv->em_segEnd = 0;
    mv->em_pan = 0;
    mv->em_ctrlList = 0;
    mv->em_ctrlTail = 0;
}
