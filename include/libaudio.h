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

typedef struct ALParam_s {
    /* 0x00 */ struct ALParam_s *next;
    /* 0x04 */ s32 delta;
    /* 0x08 */ s16 type;
    /* 0x0A */ s16 unity;
    /* 0x0C */ union {
        f32 f;
        s32 i;
    } data;
    /* 0x10 */ union {
        f32 f;
        s32 i;
    } moredata;
    /* 0x14 */ union {
        f32 f;
        s32 i;
    } stillmoredata;
    /* 0x18 */ union {
        f32 f;
        s32 i;
    } yetstillmoredata;
} ALParam;

typedef short ENVMIX_STATE[40];
typedef short RESAMPLE_STATE[16];
typedef short POLEF_STATE[4];
typedef short ADPCM_STATE[16];

typedef struct {
    /* 0x00 */ s16 fc;
    /* 0x02 */ s16 fgain;
    /* 0x08 */ union {
        s16 fccoef[16];
        s64 force_aligned;
    } fcvec;
    /* 0x28 */ POLEF_STATE *fstate;
    /* 0x2C */ s32 first;
} ALLowPass;

typedef struct {
    /* 0x00 */ ALFilter filter;
    /* 0x14 */ RESAMPLE_STATE *state;
    /* 0x18 */ f32 ratio;
    /* 0x1C */ s32 upitch;
    /* 0x20 */ f32 delta;
    /* 0x24 */ s32 first;
    /* 0x28 */ ALParam *ctrlList;
    /* 0x2C */ ALParam *ctrlTail;
    /* 0x30 */ s32 motion;
} ALResampler;

typedef struct {
    /* 0x00 */ u32 input;
    /* 0x04 */ u32 output;
    /* 0x08 */ s16 ffcoef;
    /* 0x0A */ s16 fbcoef;
    /* 0x0C */ s16 gain;
    /* 0x10 */ f32 rsinc;
    /* 0x14 */ f32 rsval;
    /* 0x18 */ s32 rsdelta;
    /* 0x1C */ f32 rsgain;
    /* 0x20 */ ALLowPass *lp;
    /* 0x24 */ ALResampler *rs;
} ALDelay;

typedef struct {
    /* 0x00 */ ALFilter filter;
    /* 0x14 */ ENVMIX_STATE *state;
    /* 0x18 */ s16 pan;
    /* 0x1A */ s16 volume;
    /* 0x1C */ s16 cvolL;
    /* 0x1E */ s16 cvolR;
    /* 0x20 */ s16 dryamt;
    /* 0x22 */ s16 wetamt;
    /* 0x24 */ u16 lratl;
    /* 0x26 */ s16 lratm;
    /* 0x28 */ s16 ltgt;
    /* 0x2A */ u16 rratl;
    /* 0x2C */ s16 rratm;
    /* 0x2E */ s16 rtgt;
    /* 0x30 */ s32 delta;
    /* 0x34 */ s32 segEnd;
    /* 0x38 */ s32 first;
    /* 0x3C */ ALParam *ctrlList;
    /* 0x40 */ ALParam *ctrlTail;
    /* 0x44 */ ALFilter **sources;
    /* 0x48 */ s32 motion;
} ALEnvMixer;

typedef struct {
    /* 0x00 */ u32 start;
    /* 0x04 */ u32 end;
    /* 0x08 */ u32 count;
} ALRawLoop;

typedef s32 (*ALDMAproc)(s32 addr, s32 len, void *state);
typedef ALDMAproc (*ALDMANew)(void *state);

typedef struct {
    /* 0x00 */ ALFilter filter;
    /* 0x14 */ ADPCM_STATE *state;
    /* 0x18 */ ADPCM_STATE *lstate;
    /* 0x1C */ ALRawLoop loop;
    /* 0x28 */ struct ALWaveTable_s *table;
    /* 0x2C */ s32 bookSize;
    /* 0x30 */ ALDMAproc dma;
    /* 0x34 */ void *dmaState;
    /* 0x38 */ s32 sample;
    /* 0x3C */ s32 lastsam;
    /* 0x40 */ s32 first;
    /* 0x44 */ s32 memin;
} ALLoadFilter;

typedef struct {
    /* 0x00 */ ALFilter filter;
    /* 0x14 */ s16 *base;
    /* 0x18 */ s16 *input;
    /* 0x1C */ u32 length;
    /* 0x20 */ ALDelay *delay;
    /* 0x24 */ u8 section_count;
    /* 0x28 */ ALSetParam paramHdl;
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

#define AL_ADPCM 0
#define AL_RESAMPLE 1
#define AL_BUFFER 2
#define AL_SAVE 3
#define AL_ENVMIX 4
#define AL_FX 5
#define AL_AUXBUS 6
#define AL_MAINBUS 7

#define AL_STOPPED 0
#define AL_PLAYING 1
#define AL_STOPPING 2

#define AL_FX_NONE 0
#define AL_FX_SMALLROOM 1
#define AL_FX_BIGROOM 2
#define AL_FX_CHORUS 3
#define AL_FX_FLANGE 4
#define AL_FX_ECHO 5
#define AL_FX_CUSTOM 6

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

void alFilterNew(ALFilter *f, ALCmdHandler h, ALSetParam s, s32 type);
void alSynNew(ALSynth *drvr, ALSynConfig *c);
void alSynDelete(ALSynth *drvr);
void alFxNew(ALFx *r, ALSynConfig *c, ALHeap *hp);
s32 alFxParam(void *filter, s32 paramID, void *param);
s32 alMainBusParam(void *filter, s32 paramID, void *param);
void *alHeapDBAlloc(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size);
#define alHeapAlloc(hp, elem, size) alHeapDBAlloc(0, 0, (hp), (elem), (size))

#endif
