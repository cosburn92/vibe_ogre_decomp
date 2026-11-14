#include "n_audio.h"

/* n_audio n_reverb.c (n_alFxNew) and n_synallocvoice/drvrNew (alN_PVoiceNew) */

INCLUDE_ASM("asm/nonmatchings/161A0", n_alFxNew);

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
