#include "common.h"

/* libmus audio.c: the audio manager and its thread */

typedef struct {
    u32 w0;
    u32 w1;
} Acmd;

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

/* libmus musConfig (fields used here) */
typedef struct {
    /* 0x00 */ u32 control_flag;
    /* 0x04 */ s32 channels;
    /* 0x08 */ void *sched;
    /* 0x0C */ s32 thread_priority;
    /* 0x10 */ u8 *heap;
    /* 0x14 */ s32 heap_length;
    /* 0x18 */ void *ptr;
    /* 0x1C */ u8 *wbk;
    /* 0x20 */ void *default_fxbank;
    /* 0x24 */ s32 fifo_length;
    /* 0x28 */ s32 syn_updates;
    /* 0x2C */ s32 syn_output_rate;
    /* 0x30 */ s32 syn_rsp_cmds;
    /* 0x34 */ s32 syn_retraceCount;
    /* 0x38 */ s32 syn_num_dma_bufs;
    /* 0x3C */ s32 syn_dma_buf_size;
} MusConfig;

typedef struct {
    /* 0x00 */ s16 *ptr;
    /* 0x04 */ u32 len; /* in samples */
} AudioBuffer;

/* passed to the scheduler's do-task callback */
typedef struct {
    /* 0x00 */ Acmd *data;
    /* 0x04 */ s32 size;
    /* 0x08 */ u64 *ucode;
    /* 0x0C */ u64 *ucode_data;
} MusTask;

typedef struct {
    void (*install)(void);
    void (*waitframe)(void);
    void (*dotask)(MusTask *task);
} MusSchedCallbacks;

extern u8 D_800B18B0[]; /* OSThread */
extern u8 *D_800B1A60;  /* thread stack */
extern AudioBuffer *D_800B1A64;
extern Acmd *D_800B1A68;
extern u8 D_800E7D18[]; /* ALGlobals */
extern MusSchedCallbacks *D_800A9B8C;
extern AudioBuffer *D_800A9B90; /* the buffer queued for the next AI DMA */
extern u64 n_aspMainTextStart[];
extern u64 D_800ABDA0[]; /* n_aspMainDataStart */

void *func_800851C0(s32 count, s32 length);
void *func_80085B24(void);
void func_80084970(void *g, ALSynConfig *c);
u32 func_80085BD0(u32 retrace, u32 output_rate, u32 vsyncs_per_second, u32 extra_ratio);
void *__MusIntMemMalloc(s32 size);
void func_80085334(void);
u32 func_80085C74(u32 samples);
Acmd *func_80088840(Acmd *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen); /* n_alAudioFrame */
s32 osAiSetFrequency(u32 frequency);
u32 osAiGetStatus(void);
u32 osAiGetLength(void);
s32 osAiSetNextBuffer(void *buf, u32 size);
u32 osVirtualToPhysical(void *addr);
void osCreateThread(void *t, s32 id, void (*entry)(void *), void *arg, void *sp, s32 pri);
void osStartThread(void *t);
void func_80085908(void *arg);

/* __MusIntAudManInit */
void func_800857D0(MusConfig *config, s32 vsyncs_per_second, s32 fx_type) {
    ALSynConfig audio_config;
    u32 i;
    s32 frame_size;

    audio_config.maxVVoices = audio_config.maxPVoices = config->channels;
    audio_config.maxUpdates = config->syn_updates;
    audio_config.dmaproc = func_800851C0(config->syn_num_dma_bufs, config->syn_dma_buf_size);
    audio_config.fxType = fx_type;
    audio_config.outputRate = osAiSetFrequency(config->syn_output_rate);
    audio_config.heap = func_80085B24();
    func_80084970(D_800E7D18, &audio_config);
    frame_size = func_80085BD0(config->syn_retraceCount, audio_config.outputRate, vsyncs_per_second, 20);
    D_800B1A68 = __MusIntMemMalloc(config->syn_rsp_cmds * sizeof(Acmd));
    D_800B1A64 = __MusIntMemMalloc(3 * sizeof(AudioBuffer));
    for (i = 0; i < 3; i++) {
        D_800B1A64[i].ptr = __MusIntMemMalloc(frame_size * 4);
    }
    D_800B1A60 = __MusIntMemMalloc(0x2000);
    osCreateThread(D_800B18B0, 3, func_80085908, NULL, D_800B1A60 + 0x2000, config->thread_priority);
    osStartThread(D_800B18B0);
}

/* __MusIntThreadProcess */
void func_80085908(void *arg) {
    MusTask task;
    s32 cmdLen;
    u32 frame = 0;
    u32 samples;
    u32 status;
    AudioBuffer *buf;
    Acmd *cmdEnd;

    task.data = D_800B1A68;
    task.ucode = n_aspMainTextStart;
    task.ucode_data = D_800ABDA0;
    D_800A9B8C->install();
    while (1) {
        do {
            D_800A9B8C->waitframe();
            status = osAiGetStatus();
            samples = osAiGetLength() >> 2;
        } while (status & 0x80000000); /* AI_STATUS_FIFO_FULL */
        func_80085334();
        if (D_800A9B90 != NULL && cmdLen != 0) {
            osAiSetNextBuffer(D_800A9B90->ptr, D_800A9B90->len << 2);
        }
        buf = &D_800B1A64[frame];
        buf->len = func_80085C74(samples);
        cmdEnd = func_80088840(D_800B1A68, &cmdLen, (s16 *)osVirtualToPhysical(buf->ptr), buf->len);
        if (cmdLen != 0) {
            task.size = (cmdEnd - D_800B1A68) * sizeof(Acmd);
            D_800A9B8C->dotask(&task);
            D_800A9B90 = buf;
        }
        frame = (frame + 1) % 3;
    }
}
