#include "n_audio.h"

/* n_audio n_synsetpitch.c */

/* n_alSynSetPitch */
void func_80088380(N_ALVoice *v, f32 pitch) {
    ALParam *update;

    if (v->pvoice) {
        update = __allocParam_800889A8();
        if (update) {
            update->delta = *(s32 *)((u8 *)alGlobals_800A9E54 + 0x1C) + v->pvoice->offset;
            update->type = AL_FILTER_SET_PITCH;
            update->data.f = pitch;
            update->next = 0;
            n_alEnvmixerParam(v->pvoice, AL_FILTER_ADD_UPDATE, update);
        }
    }
}
