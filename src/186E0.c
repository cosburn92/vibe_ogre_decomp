#include "n_audio.h"

/* n_audio n_synsetpan.c */

extern s32 D_80164760; /* mono output */

/* n_alSynSetPan */
void func_800882E0(N_ALVoice *v, u8 pan) {
    ALParam *update;

    if (v->pvoice) {
        update = __allocParam_800889A8();
        if (update) {
            update->delta = *(s32 *)((u8 *)alGlobals_800A9E54 + 0x1C) + v->pvoice->offset;
            update->type = AL_FILTER_SET_PAN;
            if (!D_80164760) {
                update->data.i = pan;
            } else {
                update->data.i = 64;
            }
            update->next = 0;
            n_alEnvmixerParam(v->pvoice, AL_FILTER_ADD_UPDATE, update);
        }
    }
}
