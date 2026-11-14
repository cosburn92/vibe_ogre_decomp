#include "n_audio.h"

/* n_audio n_alInit / n_alClose */

void func_800885D0(void *c); /* n_alSynNew */
void n_alSynDelete(void);

/* n_alInit */
void func_80087F80(void *g, void *c) {
    if (!n_alGlobals) {
        n_alGlobals = g;
        if (!alGlobals_800A9E54) {
            alGlobals_800A9E54 = g;
            func_800885D0(c);
        }
    }
}

void n_alClose(void) {
    if (n_alGlobals) {
        n_alSynDelete();
        n_alGlobals = NULL;
        alGlobals_800A9E54 = NULL;
    }
}
