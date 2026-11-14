#include "n_audio.h"

/* n_audio n_synaddplayer.c */

typedef struct ALPlayer_s {
    /* 0x00 */ struct ALPlayer_s *next;
    /* 0x04 */ void *clientData;
    /* 0x08 */ void *handler;
    /* 0x0C */ s32 callTime;
    /* 0x10 */ s32 samplesLeft;
} ALPlayer;

typedef struct {
    /* 0x00 */ ALPlayer *head;
    /* 0x04 */ u8 pad04[0x1C];
    /* 0x20 */ s32 curSamples;
} N_ALSynthPlayers;

u32 osSetIntMask(u32 mask);

/* n_alSynAddPlayer */
void func_80088000(ALPlayer *client) {
    N_ALSynthPlayers *syn;
    u32 mask = osSetIntMask(1);

    syn = (N_ALSynthPlayers *)alGlobals_800A9E54;
    client->samplesLeft = syn->curSamples;
    client->next = syn->head;
    syn->head = client;
    osSetIntMask(mask);
}
