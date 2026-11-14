#include "n_audio.h"

/* n_audio n_synallocvoice.c */

typedef struct {
    /* 0x00 */ s16 priority;
    /* 0x02 */ s16 fxBus;
    /* 0x04 */ u8 unityPitch;
} ALVoiceConfig;

typedef struct {
    /* 0x00 */ void *head;
    /* 0x04 */ ALLink pFreeList;
    /* 0x0C */ ALLink pAllocList;
    /* 0x14 */ ALLink pLameList;
    /* 0x1C */ s32 paramSamples;
} N_ALSynthLists;

void alUnlink(ALLink *ln);
void alLink(ALLink *ln, ALLink *to);
s32 func_80088168(N_PVoice **pvoice, s16 priority);

#define n_syn ((N_ALSynthLists *)alGlobals_800A9E54)

/* n_alSynAllocVoice */
s32 func_80088050(N_ALVoice *voice, ALVoiceConfig *vc) {
    N_PVoice *pvoice = 0;
    ALParam *update;
    s32 stolen;

    voice->priority = vc->priority;
    voice->unityPitch = vc->unityPitch;
    voice->table = 0;
    voice->fxBus = vc->fxBus;
    voice->state = 0; /* AL_STOPPED */
    voice->pvoice = 0;

    stolen = func_80088168(&pvoice, vc->priority);

    if (pvoice) {
        if (stolen) {
            pvoice->offset = 552;
            ((N_ALVoice *)pvoice->vvoice)->pvoice = 0;
            pvoice->vvoice = voice;
            voice->pvoice = pvoice;

            /* ramp down the stolen voice */
            update = __allocParam_800889A8();
            update->delta = n_syn->paramSamples;
            update->type = AL_FILTER_SET_VOLUME;
            update->data.i = 0;
            update->moredata.i = 552 - 184;
            n_alEnvmixerParam(voice->pvoice, AL_FILTER_ADD_UPDATE, update);

            /* and stop it */
            update = __allocParam_800889A8();
            if (update) {
                update->delta = n_syn->paramSamples + pvoice->offset;
                update->type = AL_FILTER_STOP_VOICE;
                update->next = 0;
                n_alEnvmixerParam(voice->pvoice, AL_FILTER_ADD_UPDATE, update);
            }
        } else {
            pvoice->offset = 0;
            pvoice->vvoice = voice;
            voice->pvoice = pvoice;
        }
    }
    return (pvoice != 0);
}

/* _allocatePVoice */
s32 func_80088168(N_PVoice **pvoice, s16 priority) {
    ALLink *dl;
    N_PVoice *pv;
    s32 stolen = 0;

    if ((dl = n_syn->pLameList.next) != 0) {
        *pvoice = (N_PVoice *)dl;
        alUnlink(dl);
        alLink(dl, &n_syn->pAllocList);
    } else if ((dl = n_syn->pFreeList.next) != 0) {
        *pvoice = (N_PVoice *)dl;
        alUnlink(dl);
        alLink(dl, &n_syn->pAllocList);
    } else {
        for (dl = n_syn->pAllocList.next; dl != 0; dl = dl->next) {
            pv = (N_PVoice *)dl;
            if ((((N_ALVoice *)pv->vvoice)->priority <= priority) && (pv->offset == 0)) {
                *pvoice = pv;
                priority = ((N_ALVoice *)pv->vvoice)->priority;
                stolen = 1;
            }
        }
    }
    return stolen;
}
