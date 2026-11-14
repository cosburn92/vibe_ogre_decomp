#include "n_audio.h"

/* n_audio n_synsetfxmix.c */

/* n_alSynSetFXMix */
void func_80088240(N_ALVoice *v, u8 fxmix) {
    ALParam *update;

    if (v->pvoice) {
        update = __allocParam_800889A8();
        if (update) {
            update->delta = *(s32 *)((u8 *)alGlobals_800A9E54 + 0x1C) + v->pvoice->offset;
            update->type = AL_FILTER_SET_FXAMT;
            if (fxmix > 127) {
                fxmix = 127;
            }
            update->data.i = fxmix;
            update->next = 0;
            n_alEnvmixerParam(v->pvoice, AL_FILTER_ADD_UPDATE, update);
        }
    }
}
