#ifndef LIBAUDIO_H
#define LIBAUDIO_H

#include "common.h"

/* libultra (classic, non-n) audio library types (layouts from the public SDK libaudio.h / synthInternals.h) */

#define AL_CACHE_ALIGN 15

typedef struct {
    u32 w0;
    u32 w1;
} Acmd;

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define _SHIFTR(v, s, w) ((u32)(((u32)(v) >> (s)) & ((0x01 << (w)) - 1)))

#define A_ADPCM 1
#define A_CLEARBUFF 2
#define A_ENVMIXER 3
#define A_LOADBUFF 4
#define A_RESAMPLE 5
#define A_SAVEBUFF 6
#define A_SEGMENT 7
#define A_SETBUFF 8
#define A_SETVOL 9
#define A_DMEMMOVE 10
#define A_LOADADPCM 11
#define A_MIXER 12
#define A_INTERLEAVE 13
#define A_POLEF 14
#define A_SETLOOP 15

#define aClearBuffer(pkt, d, c)                                          {                                                                        Acmd *_a = (Acmd *)pkt;                                              _a->w0 = _SHIFTL(A_CLEARBUFF, 24, 8) | _SHIFTL(d, 0, 24);            _a->w1 = (u32)(c);                                               }
#define aSetBuffer(pkt, f, i, o, c)                                                          {                                                                                            Acmd *_a = (Acmd *)pkt;                                                                  _a->w0 = (_SHIFTL(A_SETBUFF, 24, 8) | _SHIFTL(f, 16, 8) | _SHIFTL(i, 0, 16));            _a->w1 = _SHIFTL(o, 16, 16) | _SHIFTL(c, 0, 16);                                     }
#define aMix(pkt, f, g, i, o)                                                                {                                                                                            Acmd *_a = (Acmd *)pkt;                                                                  _a->w0 = (_SHIFTL(A_MIXER, 24, 8) | _SHIFTL(f, 16, 8) | _SHIFTL(g, 0, 16));              _a->w1 = _SHIFTL(i, 16, 16) | _SHIFTL(o, 0, 16);                                     }
#define aInterleave(pkt, l, r)                                           {                                                                        Acmd *_a = (Acmd *)pkt;                                              _a->w0 = _SHIFTL(A_INTERLEAVE, 24, 8);                               _a->w1 = _SHIFTL(l, 16, 16) | _SHIFTL(r, 0, 16);                 }
#define aSaveBuffer(pkt, s)                                              {                                                                        Acmd *_a = (Acmd *)pkt;                                              _a->w0 = _SHIFTL(A_SAVEBUFF, 24, 8);                                 _a->w1 = (u32)(s);                                               }

#define AL_MAIN_L_OUT 0x440
#define AL_MAIN_R_OUT 0x580
#define AL_AUX_L_OUT 0x6C0
#define AL_AUX_R_OUT 0x800

typedef Acmd *(*ALCmdHandler)(void *, s16 *, s32, s32, Acmd *);
typedef s32 (*ALSetParam)(void *, s32, void *);

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
    /* 0x04 */ ALCmdHandler handler;
    /* 0x08 */ ALSetParam setParam;
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
    /* 0x1C */ ALFilter **sources;
    /* 0x20 */ ALFx fx[1];
} ALAuxBus; /* size 0x4C */

typedef struct {
    /* 0x00 */ ALFilter filter;
    /* 0x14 */ s32 sourceCount;
    /* 0x18 */ s32 maxSources;
    /* 0x1C */ ALFilter **sources;
} ALMainBus;

typedef struct {
    /* 0x00 */ ALFilter filter;
    /* 0x14 */ s32 dramout;
    /* 0x18 */ s32 first;
} ALSave;

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
