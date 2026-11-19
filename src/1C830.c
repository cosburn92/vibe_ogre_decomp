#include "common.h"
#include "libultra.h"

extern s32 osViClock;

s32 osAiSetFrequency(u32 frequency) {
    register unsigned int dacRate;
    register unsigned char bitRate;
    register float f;

    f = osViClock / (float)frequency + .5f;
    dacRate = f;
    if (dacRate < 132) { /* AI_MIN_DACRATE */
        return -1;
    }
    bitRate = (dacRate / 66);
    if (bitRate > 16) { /* AI_MAX_BIT_RATE */
        bitRate = 16;
    }
    IO_WRITE(AI_DACRATE_REG, dacRate - 1);
    IO_WRITE(AI_BITRATE_REG, bitRate - 1);
    return osViClock / (s32)dacRate;
}
