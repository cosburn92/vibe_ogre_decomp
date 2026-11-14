#include "n_audio.h"

/* n_audio n_synstartvoice.c */

/* n_alSynStartVoice */
void func_800884C0(N_ALVoice *v, ALWaveTable *table) {
    ALParam *update;

    if (v->pvoice) {
        update = __allocParam_800889A8();
        if (update) {
            update->delta = *(s32 *)((u8 *)alGlobals_800A9E54 + 0x1C) + v->pvoice->offset;
            update->type = AL_FILTER_START_VOICE_ALT;
            update->data.i = (s32)table;
            update->next = 0;
            update->unity = v->unityPitch;
            n_alEnvmixerParam(v->pvoice, AL_FILTER_ADD_UPDATE, update);
        }
    }
}
