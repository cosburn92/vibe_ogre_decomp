#include "common.h"
#include "libaudio.h"

extern ALGlobals *alGlobals_800AA710; /* alGlobals */

void alInit(ALGlobals *g, ALSynConfig *c) {
    if (!alGlobals_800AA710) {
        alGlobals_800AA710 = g;
        alSynNew(&alGlobals_800AA710->drvr, c);
    }
}

void alClose(ALGlobals *glob) {
    if (alGlobals_800AA710) {
        alSynDelete(&glob->drvr);
        alGlobals_800AA710 = NULL;
    }
}

void alLink(ALLink *ln, ALLink *to) {
    ln->next = to->next;
    ln->prev = to;
    if (to->next) {
        to->next->prev = ln;
    }
    to->next = ln;
}

void alUnlink(ALLink *ln) {
    if (ln->next) {
        ln->next->prev = ln->prev;
    }
    if (ln->prev) {
        ln->prev->next = ln->next;
    }
}
