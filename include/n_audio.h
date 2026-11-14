#ifndef N_AUDIO_H
#define N_AUDIO_H

#include "common.h"

/* Nintendo n_audio (the synthesizer libmus drives), reconstructed layouts */

typedef struct {
    u32 w0;
    u32 w1;
} Acmd;

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))

typedef struct {
    /* 0x00 */ u32 start;
    /* 0x04 */ u32 end;
    /* 0x08 */ u32 count;
    /* 0x0C */ s16 state[16];
} ALADPCMloop;

typedef struct {
    /* 0x00 */ s32 order;
    /* 0x04 */ s32 npredictors;
    /* 0x08 */ s16 book[1];
} ALADPCMBook;

typedef struct {
    /* 0x00 */ u32 start;
    /* 0x04 */ u32 end;
    /* 0x08 */ u32 count;
} ALRawLoop;

typedef struct {
    /* 0x00 */ u8 *base;
    /* 0x04 */ s32 len;
    /* 0x08 */ u8 type; /* AL_ADPCM_WAVE 0, AL_RAW16_WAVE 1 */
    /* 0x09 */ u8 flags;
    /* 0x0C */ union {
        struct {
            ALADPCMloop *loop;
            ALADPCMBook *book;
        } adpcmWave;
        struct {
            ALRawLoop *loop;
        } rawWave;
    } waveInfo;
} ALWaveTable;

typedef struct ALLink_s {
    struct ALLink_s *next;
    struct ALLink_s *prev;
} ALLink;

typedef s32 (*ALDMAproc)(s32 addr, s32 len, void *state);
typedef ALDMAproc (*ALDMANew)(void *state);

/* N_PVoice: decoder, resampler and envelope mixer in one */
typedef struct {
    /* 0x00 */ ALLink node;
    /* 0x08 */ void *vvoice;
    /* decoder */
    /* 0x0C */ s16 *dc_state;
    /* 0x10 */ s16 *dc_lstate;
    /* 0x14 */ ALRawLoop dc_loop;
    /* 0x20 */ ALWaveTable *dc_table;
    /* 0x24 */ s32 dc_bookSize;
    /* 0x28 */ ALDMAproc dc_dma;
    /* 0x2C */ void *dc_dmaState;
    /* 0x30 */ s32 dc_sample;
    /* 0x34 */ s32 dc_lastsam;
    /* 0x38 */ s32 dc_first;
    /* 0x3C */ s32 dc_memin;
    /* resampler */
    /* 0x40 */ s16 *rs_state;
    /* 0x44 */ f32 rs_ratio;
    /* 0x48 */ s32 rs_upitch;
    /* 0x4C */ f32 rs_delta;
    /* 0x50 */ s32 rs_first;
    /* envelope mixer */
    /* 0x54 */ s16 *em_state;
    /* 0x58 */ s16 em_pan;
    /* 0x5A */ s16 em_volume;
    /* 0x5C */ s16 em_cvolL;
    /* 0x5E */ s16 em_cvolR;
    /* 0x60 */ s16 em_dryamt;
    /* 0x62 */ s16 em_wetamt;
    /* 0x64 */ u16 em_lratl;
    /* 0x66 */ s16 em_lratm;
    /* 0x68 */ s16 em_ltgt;
    /* 0x6A */ u16 em_rratl;
    /* 0x6C */ s16 em_rratm;
    /* 0x6E */ s16 em_rtgt;
    /* 0x70 */ s32 em_delta;
    /* 0x74 */ s32 em_segEnd;
    /* 0x78 */ s32 em_first;
    /* 0x7C */ void *em_ctrlList;
    /* 0x80 */ void *em_ctrlTail;
    /* 0x84 */ s32 em_motion;
    /* 0x88 */ s32 offset;
} N_PVoice; /* size 0x8C */

/* libultra ALLowPass */
typedef struct {
    /* 0x00 */ s16 fc;
    /* 0x02 */ s16 fgain;
    /* 0x08 */ union {
        s16 fccoef[16];
        s64 force_aligned;
    } fcvec;
    /* 0x28 */ s16 *fstate;
    /* 0x2C */ s32 first;
} ALLowPass;

/* libultra ALResampler */
typedef struct {
    /* 0x00 */ u8 pad00[0x14];
    /* 0x14 */ s16 *state;
    /* 0x18 */ f32 ratio;
    /* 0x1C */ s32 upitch;
    /* 0x20 */ f32 delta;
    /* 0x24 */ s32 first;
} ALResampler;

/* libultra ALDelay */
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
} ALDelay; /* size 0x28 */

/* libultra ALFx (reverb) */
typedef struct {
    /* 0x00 */ u8 filter[0x14];
    /* 0x14 */ s16 *base;
    /* 0x18 */ s16 *input;
    /* 0x1C */ u32 length;
    /* 0x20 */ ALDelay *delay;
    /* 0x24 */ u8 section_count;
    /* 0x28 */ void *paramHdl;
} ALFx;

/* n_audio N_ALSynth (fields used by the n_ files) */
typedef struct {
    /* 0x00 */ u8 pad00[0x34];
    /* 0x34 */ struct {
        u8 pad00[0x14];
        s32 sourceCount;
        s32 maxSources;
        N_PVoice **sources;
        ALFx *fx;
        ALFx *fxArr[1]; /* 0x24 */
    } *auxBus;
    /* 0x38 */ s32 numPVoices;
    /* 0x3C */ u8 pad3C[4];
    /* 0x40 */ s32 outputRate;
} N_ALSynth;

extern N_ALSynth *alGlobals_800A9E54; /* n_syn */
extern void *n_alGlobals;

/* libultra ALParam */
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
} ALParam; /* size 0x1C */

/* n_audio N_ALVoice */
typedef struct {
    /* 0x00 */ ALLink node;
    /* 0x08 */ N_PVoice *pvoice;
    /* 0x0C */ ALWaveTable *table;
    /* 0x10 */ void *clientPrivate;
    /* 0x14 */ s16 state;
    /* 0x16 */ s16 priority;
    /* 0x18 */ s16 fxBus;
    /* 0x1A */ s16 unityPitch;
} N_ALVoice; /* size 0x1C */

#define AL_FILTER_SET_PITCH 7
#define AL_FILTER_SET_VOLUME 11
#define AL_FILTER_SET_PAN 12
#define AL_FILTER_START_VOICE_ALT 14
#define AL_FILTER_STOP_VOICE 15
#define AL_FILTER_SET_FXAMT 16
#define AL_FILTER_ADD_UPDATE 3

ALParam *__allocParam_800889A8(void);
s32 func_80088AD4(s32 t); /* _n_timeToSamples */
s32 n_alEnvmixerParam(void *filter, s32 paramID, void *param);

void *alHeapDBAlloc(u8 *file, s32 line, void *hp, s32 num, s32 size);
#define alHeapAlloc(hp, elem, size) alHeapDBAlloc(0, 0, (hp), (elem), (size))
void alCopy(void *src, void *dest, s32 len);
u32 osVirtualToPhysical(void *addr);

#endif
