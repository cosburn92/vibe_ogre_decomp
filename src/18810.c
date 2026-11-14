#include "n_audio.h"

/* n_audio n_synsetvol.c */

/* n_alSynSetVol */
void func_80088410(N_ALVoice *v, s16 volume, s32 t) {
    ALParam *update;

    if (v->pvoice) {
        update = __allocParam_800889A8();
        if (update) {
            update->delta = *(s32 *)((u8 *)alGlobals_800A9E54 + 0x1C) + v->pvoice->offset;
            update->type = AL_FILTER_SET_VOLUME;
            update->data.i = volume;
            update->moredata.i = func_80088AD4(t);
            update->next = 0;
            n_alEnvmixerParam(v->pvoice, AL_FILTER_ADD_UPDATE, update);
        }
    }
}
