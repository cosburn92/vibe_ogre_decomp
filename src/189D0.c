#include "n_audio.h"

/* n_audio n_synthesizer.c */

typedef struct ALPlayer_s {
    /* 0x00 */ struct ALPlayer_s *next;
    /* 0x04 */ void *clientData;
    /* 0x08 */ s32 (*handler)(void *);
    /* 0x0C */ s32 callTime;
    /* 0x10 */ s32 samplesLeft;
} ALPlayer;

/* n_audio ALSynConfig */
typedef struct {
    /* 0x00 */ s32 maxVVoices;
    /* 0x04 */ s32 maxPVoices;
    /* 0x08 */ s32 maxUpdates;
    /* 0x0C */ s32 maxFXbusses;
    /* 0x10 */ void *dmaproc;
    /* 0x14 */ void *heap;
    /* 0x18 */ s32 outputRate;
    /* 0x1C */ u8 fxType;
    /* 0x20 */ s32 *params;
} ALSynConfig;

typedef struct {
    /* 0x00 */ ALPlayer *head;
    /* 0x04 */ ALLink pFreeList;
    /* 0x0C */ ALLink pAllocList;
    /* 0x14 */ ALLink pLameList;
    /* 0x1C */ s32 paramSamples;
    /* 0x20 */ s32 curSamples;
    /* 0x24 */ void *dma;
    /* 0x28 */ void *heap;
    /* 0x2C */ ALParam *paramList;
    /* 0x30 */ struct {
        u8 pad00[4];
        void *handler; /* 0x04 */
    } *mainBus;
    /* 0x34 */ struct {
        u8 pad00[0x14];
        s32 sourceCount; /* 0x14 */
        s32 maxSources;  /* 0x18 */
        N_PVoice **sources; /* 0x1C */
        void *fx;        /* 0x20 */
    } *auxBus;
    /* 0x38 */ s32 numPVoices;
    /* 0x3C */ u8 pad3C[4];
    /* 0x40 */ s32 outputRate;
    /* 0x44 */ s32 maxOutSamples;
    /* 0x48 */ s32 sv_dramout;
    /* 0x4C */ s32 sv_first;
} N_ALSynthFull;

#define n_syn ((N_ALSynthFull *)alGlobals_800A9E54)
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

void alLink(ALLink *ln, ALLink *to);
void alUnlink(ALLink *ln);
void alN_PVoiceNew(N_PVoice *mv, void *dmaNew, void *hp);
void *func_80088B80(s16 bus, ALSynConfig *c, void *hp); /* n_alSynAllocFX */
Acmd *func_80087590(s32 sampleOffset, Acmd *p);         /* n_alFxPull */
Acmd *func_80085D00(s32 sampleOffset, Acmd *p);         /* n_alAuxBusPull */
Acmd *func_80088B30(s32 sampleOffset, Acmd *p);         /* n_alSavePull */
void func_800889EC(void);
s32 func_80088A84(s32 micros);

/* n_alSynNew */
void func_800885D0(ALSynConfig *c) {
    s32 i;
    N_PVoice *pv;
    N_PVoice *pvoices;
    ALParam *params;
    void *hp = c->heap;

    n_syn->head = NULL;
    n_syn->numPVoices = c->maxPVoices;
    n_syn->curSamples = 0;
    n_syn->paramSamples = 0;
    n_syn->outputRate = c->outputRate;
    n_syn->maxOutSamples = 184;
    n_syn->dma = c->dmaproc;
    n_syn->sv_dramout = 0;
    n_syn->sv_first = 1;

    n_syn->auxBus = alHeapAlloc(hp, 1, 0x44);
    n_syn->auxBus->sourceCount = 0;
    n_syn->auxBus->maxSources = c->maxPVoices;
    n_syn->auxBus->sources = alHeapAlloc(hp, c->maxPVoices, 4);

    n_syn->mainBus = alHeapAlloc(hp, 1, 0x14);
    if (c->fxType != 0) {
        n_syn->auxBus->fx = func_80088B80(0, c, hp);
        n_syn->mainBus->handler = func_80087590;
    } else {
        n_syn->mainBus->handler = func_80085D00;
    }

    n_syn->pFreeList.next = NULL;
    n_syn->pFreeList.prev = NULL;
    n_syn->pLameList.next = NULL;
    n_syn->pLameList.prev = NULL;
    n_syn->pAllocList.next = NULL;
    n_syn->pAllocList.prev = NULL;

    pvoices = alHeapAlloc(hp, c->maxPVoices, sizeof(N_PVoice));
    for (i = 0; i < c->maxPVoices; i++) {
        pv = &pvoices[i];
        alLink(&pv->node, &n_syn->pFreeList);
        pv->vvoice = NULL;
        alN_PVoiceNew(pv, n_syn->dma, hp);
        n_syn->auxBus->sources[n_syn->auxBus->sourceCount++] = pv;
    }

    params = alHeapAlloc(hp, c->maxUpdates, sizeof(ALParam));
    n_syn->paramList = NULL;
    for (i = 0; i < c->maxUpdates; i++) {
        params[i].next = n_syn->paramList;
        n_syn->paramList = &params[i];
    }

    n_syn->heap = hp;
}

/* n_alAudioFrame (libmus runs a single player) */
Acmd *func_80088840(Acmd *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen) {
    ALPlayer *client;
    Acmd *cmdlEnd = cmdList;
    Acmd *cmdPtr;
    s32 nOut;
    s16 *lOutBuf = outBuf;

    if (n_syn->head == NULL) {
        *cmdLen = 0;
        return cmdList;
    }

    client = n_syn->head;
    while (client->samplesLeft - n_syn->curSamples < outLen) {
        n_syn->paramSamples = client->samplesLeft & ~0xF;
        client->samplesLeft += func_80088A84((*client->handler)(client));
    }

    n_syn->paramSamples &= ~0xF;

    while (outLen > 0) {
        nOut = MIN(n_syn->maxOutSamples, outLen);
        cmdPtr = cmdlEnd;
        n_syn->sv_dramout = (s32)lOutBuf;
        cmdlEnd = func_80088B30(n_syn->curSamples, cmdPtr);
        outLen -= nOut;
        lOutBuf += nOut << 1;
        n_syn->curSamples += nOut;
    }
    *cmdLen = (s32)(cmdlEnd - cmdList);
    func_800889EC();
    return cmdlEnd;
}

ALParam *__allocParam_800889A8(void) {
    ALParam *update = 0;

    if (n_syn->paramList) {
        update = n_syn->paramList;
        n_syn->paramList = n_syn->paramList->next;
        update->next = 0;
    }
    return update;
}

void __freeParam_800889D4(ALParam *param) {
    param->next = n_syn->paramList;
    n_syn->paramList = param;
}

/* _n_collectPVoices */
void func_800889EC(void) {
    ALLink *dl;

    while ((dl = n_syn->pLameList.next) != 0) {
        alUnlink(dl);
        alLink(dl, &n_syn->pFreeList);
    }
}

void _n_freePVoice(N_PVoice *pvoice) {
    alUnlink(&pvoice->node);
    alLink(&pvoice->node, &n_syn->pLameList);
}

/* _n_timeToSamplesNoRound */
s32 func_80088A84(s32 micros) {
    f32 tmp = ((f32)micros) * n_syn->outputRate / 1000000.0 + 0.5;

    return (s32)tmp;
}

/* _n_timeToSamples */
s32 func_80088AD4(s32 micros) {
    f32 tmp = ((f32)micros) * n_syn->outputRate / 1000000.0 + 0.5;

    return (s32)tmp & ~0xF;
}
