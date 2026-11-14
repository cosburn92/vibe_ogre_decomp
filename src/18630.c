#include "n_audio.h"

/* n_audio n_syndelete.c */

void n_alSynDelete(void) {
    *(void **)alGlobals_800A9E54 = NULL; /* n_syn->head */
}
