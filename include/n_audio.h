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

void *alHeapDBAlloc(u8 *file, s32 line, void *hp, s32 num, s32 size);
#define alHeapAlloc(hp, elem, size) alHeapDBAlloc(0, 0, (hp), (elem), (size))
void alCopy(void *src, void *dest, s32 len);
u32 osVirtualToPhysical(void *addr);

#endif
