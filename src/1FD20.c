#include "common.h"
#include "libaudio.h"

/* libultra audio synthesizer.c */

#define AL_MAX_RSP_SAMPLES 160
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define aSegment(pkt, s, b)                                          \
    {                                                                \
        Acmd *_a = (Acmd *)pkt;                                      \
        _a->w0 = _SHIFTL(A_SEGMENT, 24, 8);                          \
        _a->w1 = _SHIFTL(s, 24, 8) | _SHIFTL(b, 0, 24);              \
    }

typedef struct {
    /* 0x00 */ ALLink node;
    /* 0x08 */ void *vvoice;
    /* 0x0C */ ALFilter *channelKnob;
    /* 0x10 */ ALLoadFilter decoder;
    /* 0x58 */ ALResampler resampler;
    /* 0x8C */ ALEnvMixer envmixer;
    /* 0xD8 */ s32 offset;
} PVoice;

extern ALGlobals *alGlobals_800AA710;

void alSaveNew(ALSave *f);
void alAuxBusNew(ALAuxBus *m, void *sources, s32 maxSources);
void alMainBusNew(ALMainBus *m, void *sources, s32 maxSources);
void alLoadNew(ALLoadFilter *f, ALDMANew dmaNew, ALHeap *hp);
void alResampleNew(ALResampler *r, ALHeap *hp);
void alEnvmixerNew(ALEnvMixer *e, ALHeap *hp);
void alLoadParam(void *filter, s32 paramID, void *param);
s32 alResampleParam(void *filter, s32 paramID, void *param);
s32 alEnvmixerParam(void *filter, s32 paramID, void *param);
s32 alAuxBusParam(void *filter, s32 paramID, void *param);
s32 alSaveParam(void *filter, s32 paramID, void *param);
ALFxRef alSynAllocFX(ALSynth *s, s16 bus, ALSynConfig *c, ALHeap *hp);
void alLink(ALLink *ln, ALLink *to);
void alUnlink(ALLink *ln);
s32 __nextSampleTime(ALSynth *drvr, ALPlayer **client);
s32 func_8008FE74(ALSynth *synth, s32 micros); /* _timeToSamplesNoRound */
void _collectPVoices(ALSynth *drvr);

void alSynNew(ALSynth *drvr, ALSynConfig *c) {
    s32 i;
    PVoice *pv;
    PVoice *pvoices;
    ALHeap *hp = c->heap;
    ALSave *save;
    ALParam *params;
    ALParam *paramPtr;
    ALFilter **sources;

    drvr->head = NULL;
    drvr->numPVoices = c->maxPVoices;
    drvr->curSamples = 0;
    drvr->paramSamples = 0;
    drvr->outputRate = c->outputRate;
    drvr->maxOutSamples = AL_MAX_RSP_SAMPLES;
    drvr->dma = c->dmaproc;

    save = alHeapAlloc(hp, 1, sizeof(ALSave));
    alSaveNew(save);
    drvr->outputFilter = (ALFilter *)save;

    drvr->auxBus = alHeapAlloc(hp, 1, sizeof(ALAuxBus));
    drvr->maxAuxBusses = 1;
    sources = alHeapAlloc(hp, c->maxPVoices, sizeof(ALFilter *));
    alAuxBusNew(drvr->auxBus, sources, c->maxPVoices);

    drvr->mainBus = alHeapAlloc(hp, 1, sizeof(ALMainBus));
    sources = alHeapAlloc(hp, c->maxPVoices, sizeof(ALFilter *));
    alMainBusNew(drvr->mainBus, sources, c->maxPVoices);

    if (c->fxType != AL_FX_NONE) {
        alSynAllocFX(drvr, 0, c, hp);
    } else {
        alMainBusParam(drvr->mainBus, AL_FILTER_ADD_SOURCE, &drvr->auxBus[0]);
    }

    drvr->pFreeList.next = 0;
    drvr->pFreeList.prev = 0;
    drvr->pLameList.next = 0;
    drvr->pLameList.prev = 0;
    drvr->pAllocList.next = 0;
    drvr->pAllocList.prev = 0;

    pvoices = alHeapAlloc(hp, c->maxPVoices, sizeof(PVoice));
    for (i = 0; i < c->maxPVoices; i++) {
        pv = &pvoices[i];
        alLink((ALLink *)pv, &drvr->pFreeList);
        pv->vvoice = 0;

        alLoadNew(&pv->decoder, drvr->dma, hp);
        alLoadParam(&pv->decoder, AL_FILTER_SET_SOURCE, 0);

        alResampleNew(&pv->resampler, hp);
        alResampleParam(&pv->resampler, AL_FILTER_SET_SOURCE, &pv->decoder);

        alEnvmixerNew(&pv->envmixer, hp);
        alEnvmixerParam(&pv->envmixer, AL_FILTER_SET_SOURCE, &pv->resampler);

        alAuxBusParam(drvr->auxBus, AL_FILTER_ADD_SOURCE, &pv->envmixer);

        pv->channelKnob = (ALFilter *)&pv->envmixer;
    }

    alSaveParam(save, AL_FILTER_SET_SOURCE, drvr->mainBus);

    params = alHeapAlloc(hp, c->maxUpdates, sizeof(ALParam));
    drvr->paramList = 0;
    for (i = 0; i < c->maxUpdates; i++) {
        paramPtr = &params[i];
        paramPtr->next = drvr->paramList;
        drvr->paramList = paramPtr;
    }

    drvr->heap = hp;
}

Acmd *alAudioFrame(Acmd *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen) {
    ALPlayer *client;
    ALFilter *output;
    ALSynth *drvr = &alGlobals_800AA710->drvr;
    s16 tmp = 0;
    Acmd *cmdlEnd = cmdList;
    Acmd *cmdPtr;
    s32 nOut;
    s16 *lOutBuf = outBuf;

    if (drvr->head == 0) {
        *cmdLen = 0;
        return cmdList;
    }

    for (drvr->paramSamples = __nextSampleTime(drvr, &client); drvr->paramSamples - drvr->curSamples < outLen;
         drvr->paramSamples = __nextSampleTime(drvr, &client)) {
        drvr->paramSamples &= ~0xF;
        client->samplesLeft += func_8008FE74(drvr, (*client->handler)(client));
    }

    drvr->paramSamples &= ~0xF;

    while (outLen > 0) {
        nOut = MIN(drvr->maxOutSamples, outLen);

        cmdPtr = cmdlEnd;
        aSegment(cmdPtr++, 0, 0);
        output = drvr->outputFilter;
        (*output->setParam)(output, AL_FILTER_SET_DRAM, lOutBuf);
        cmdlEnd = (*output->handler)(output, &tmp, nOut, drvr->curSamples, cmdPtr);

        outLen -= nOut;
        lOutBuf += nOut << 1;
        drvr->curSamples += nOut;
    }
    *cmdLen = (s32)(cmdlEnd - cmdList);

    _collectPVoices(drvr);

    return cmdlEnd;
}

ALParam *__allocParam_8008FD9C(void) {
    ALParam *update = 0;
    ALSynth *drvr = &alGlobals_800AA710->drvr;

    if (drvr->paramList) {
        update = drvr->paramList;
        drvr->paramList = drvr->paramList->next;
        update->next = 0;
    }
    return update;
}

void __freeParam_8008FDC8(ALParam *param) {
    ALSynth *drvr = &alGlobals_800AA710->drvr;

    param->next = drvr->paramList;
    drvr->paramList = param;
}

void _collectPVoices(ALSynth *drvr) {
    ALLink *dl;

    while ((dl = drvr->pLameList.next) != 0) {
        alUnlink(dl);
        alLink(dl, &drvr->pFreeList);
    }
}

void _freePVoice(ALSynth *drvr, PVoice *pvoice) {
    alUnlink((ALLink *)pvoice);
    alLink((ALLink *)pvoice, &drvr->pLameList);
}

/* _timeToSamplesNoRound */
s32 func_8008FE74(ALSynth *synth, s32 micros) {
    f32 tmp = ((f32)micros) * synth->outputRate / 1000000.0 + 0.5;

    return (s32)tmp;
}

static inline s32 _timeToSamplesNoRound(ALSynth *synth, s32 micros) {
    f32 tmp = ((f32)micros) * synth->outputRate / 1000000.0 + 0.5;

    return (s32)tmp;
}

s32 _timeToSamples(ALSynth *synth, s32 micros) {
    return _timeToSamplesNoRound(synth, micros) & ~0xF;
}

s32 __nextSampleTime(ALSynth *drvr, ALPlayer **client) {
    s32 delta = 0x7FFFFFFF;
    ALPlayer *cl;

    *client = 0;
    for (cl = drvr->head; cl != 0; cl = cl->next) {
        if ((cl->samplesLeft - drvr->curSamples) < delta) {
            *client = cl;
            delta = cl->samplesLeft - drvr->curSamples;
        }
    }
    return (*client)->samplesLeft;
}

