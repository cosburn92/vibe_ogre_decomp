#include "common.h"

/* libmus lib_memory.c and the audio frame-size bookkeeping */

/* libultra ALHeap */
typedef struct {
    /* 0x00 */ u8 *base;
    /* 0x04 */ u8 *cur;
    /* 0x08 */ s32 len;
    /* 0x0C */ s32 count;
} MusHeap;

extern MusHeap D_800B1A70;
extern u32 D_800B1A80; /* samples per frame */
extern u32 D_800B1A84; /* minimum */
extern u32 D_800B1A88; /* maximum */
extern u32 D_800B1A8C; /* extra */
extern s32 D_800A9BA0;

void *alHeapDBAlloc(u8 *file, s32 line, void *hp, s32 num, s32 size);
void alHeapInit(MusHeap *hp, u8 *base, s32 len); /* alHeapInit */
void func_80085B30(void *dest, u8 value, u32 length);

/* __MusIntMemInit */
void func_80085A90(u8 *heap, s32 length) {
    func_80085B30(heap, 0, length);
    alHeapInit(&D_800B1A70, heap, length);
}

void *__MusIntMemMalloc(s32 size) {
    return alHeapDBAlloc(NULL, 0, &D_800B1A70, 1, size);
}

/* bytes of the libmus heap in use */
s32 func_80085B0C(void) {
    return D_800B1A70.cur - D_800B1A70.base;
}

MusHeap *func_80085B24(void) {
    return &D_800B1A70;
}

/* __MusIntMemSet */
void func_80085B30(void *dest, u8 value, u32 length) {
    u8 *p = dest;

    while (length--) {
        *p++ = value;
    }
}

/* __MusIntMemMove */
void func_80085B5C(u8 *dest, u8 *src, u32 length) {
    if (src < dest) {
        dest += length;
        src += length;
        while (length--) {
            *--dest = *--src;
        }
    } else {
        while (length--) {
            *dest++ = *src++;
        }
    }
}

#ifdef NON_MATCHING
/* The original starts with a nop (it is the jal target) and keeps frame in v1. */
/* __MusIntSamplesInit */
u32 func_80085BD0(u32 retrace, u32 output_rate, u32 vsyncs_per_second, u32 extra_ratio) {
    u32 frame;

    frame = (retrace * output_rate + vsyncs_per_second - 1) / vsyncs_per_second;
    frame = (frame / 184 + 1) * 184;
    D_800B1A80 = frame;
    D_800B1A84 = frame - 184;
    D_800B1A88 = frame + 184;
    D_800B1A8C = frame * extra_ratio / 100;
    return frame + D_800B1A8C + 184;
}
#else
INCLUDE_ASM("asm/nonmatchings/15E90", func_80085BD0);
#endif

/* __MusIntSamplesCurrent */
u32 func_80085C74(u32 samples) {
    if (samples > D_800B1A8C + 184) {
        if (D_800A9BA0) {
            D_800A9BA0 = 0;
            return D_800B1A84;
        }
    } else if (samples < D_800B1A8C) {
        if (D_800A9BA0) {
            D_800A9BA0 = 0;
            return D_800B1A88;
        }
    } else {
        D_800A9BA0 = 1;
    }
    return D_800B1A80;
}
