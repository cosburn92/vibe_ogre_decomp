#ifndef LIBAUDIO_H
#define LIBAUDIO_H

#include "common.h"

/* libultra (classic, non-n) audio library types (layouts from the public SDK libaudio.h / synthInternals.h) */

#define AL_CACHE_ALIGN 15

typedef struct ALLink_s {
    /* 0x00 */ struct ALLink_s *next;
    /* 0x04 */ struct ALLink_s *prev;
} ALLink;

typedef struct {
    /* 0x00 */ u8 *base;
    /* 0x04 */ u8 *cur;
    /* 0x08 */ s32 len;
    /* 0x0C */ s32 count;
} ALHeap;

typedef struct ALFilter_s {
    /* 0x00 */ struct ALFilter_s *source;
    /* 0x04 */ s32 (*handler)(void *, s16 *, s32, s32, void *);
    /* 0x08 */ s32 (*setParam)(void *, s32, void *);
    /* 0x0C */ s16 inp;
    /* 0x0E */ s16 outp;
    /* 0x10 */ s32 type;
} ALFilter;

typedef struct {
    /* 0x00 */ ALFilter filter;
    /* 0x14 */ s16 *base;
    /* 0x18 */ s16 *input;
    /* 0x1C */ u32 length;
    /* 0x20 */ void *delay;
    /* 0x24 */ u8 section_count;
    /* 0x28 */ void *paramHdl;
} ALFx;

typedef struct {
    /* 0x00 */ ALFilter filter;
    /* 0x14 */ s32 sourceCount;
    /* 0x18 */ s32 maxSources;
    /* 0x1C */ void **sources;
    /* 0x20 */ ALFx fx[1];
} ALAuxBus; /* size 0x4C */

typedef struct {
    /* 0x00 */ ALFilter filter;
    /* 0x14 */ s32 sourceCount;
    /* 0x18 */ s32 maxSources;
    /* 0x1C */ ALFilter **sources;
} ALMainBus;

typedef struct ALPlayer_s {
    /* 0x00 */ struct ALPlayer_s *next;
    /* 0x04 */ void *clientData;
    /* 0x08 */ s32 (*handler)(void *);
    /* 0x0C */ s32 callTime;
    /* 0x10 */ s32 samplesLeft;
} ALPlayer;

typedef struct {
    /* 0x00 */ ALPlayer *head;
    /* 0x04 */ ALLink pFreeList;
    /* 0x0C */ ALLink pAllocList;
    /* 0x14 */ ALLink pLameList;
    /* 0x1C */ s32 paramSamples;
    /* 0x20 */ s32 curSamples;
    /* 0x24 */ void *dma;
    /* 0x28 */ ALHeap *heap;
    /* 0x2C */ void *paramList;
    /* 0x30 */ ALMainBus *mainBus;
    /* 0x34 */ ALAuxBus *auxBus;
    /* 0x38 */ void *outputFilter;
    /* 0x3C */ s32 numPVoices;
    /* 0x40 */ s32 maxAuxBusses;
    /* 0x44 */ s32 outputRate;
    /* 0x48 */ s32 maxOutSamples;
} ALSynth;

typedef struct {
    /* 0x00 */ ALSynth drvr;
} ALGlobals;

typedef struct {
    /* 0x00 */ s32 maxVVoices;
    /* 0x04 */ s32 maxPVoices;
    /* 0x08 */ s32 maxUpdates;
    /* 0x0C */ s32 maxFXbusses;
    /* 0x10 */ void *dmaproc;
    /* 0x14 */ ALHeap *heap;
    /* 0x18 */ s32 outputRate;
    /* 0x1C */ u8 fxType;
    /* 0x20 */ s32 *params;
} ALSynConfig;

typedef void *ALFxRef;

#define AL_FILTER_FREE_VOICE 0
#define AL_FILTER_SET_SOURCE 1
#define AL_FILTER_ADD_SOURCE 2
#define AL_FILTER_ADD_UPDATE 3
#define AL_FILTER_RESET 4
#define AL_FILTER_SET_WAVETABLE 5
#define AL_FILTER_SET_DRAM 6
#define AL_FILTER_SET_PITCH 7
#define AL_FILTER_SET_UNITY_PITCH 8
#define AL_FILTER_START 9
#define AL_FILTER_SET_STATE 10
#define AL_FILTER_SET_VOLUME 11
#define AL_FILTER_SET_PAN 12
#define AL_FILTER_START_VOICE_ALT 13
#define AL_FILTER_START_VOICE 14
#define AL_FILTER_STOP_VOICE 15
#define AL_FILTER_SET_FXAMT 16

void alSynNew(ALSynth *drvr, ALSynConfig *c);
void alSynDelete(ALSynth *drvr);
void alFxNew(ALFx *r, ALSynConfig *c, ALHeap *hp);
s32 alFxParam(void *filter, s32 paramID, void *param);
s32 alMainBusParam(void *filter, s32 paramID, void *param);
void *alHeapDBAlloc(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size);
#define alHeapAlloc(hp, elem, size) alHeapDBAlloc(0, 0, (hp), (elem), (size))

#endif
