#include "n_audio.h"

/* n_audio n_load.c */

#define ADPCMFSIZE 16
#define ADPCMFBYTES 9
#define LFSAMPLES 4
#define A_LOOP 2
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define aClearBuffer(pkt, d, c)                         \
    {                                                   \
        Acmd *_a = (Acmd *)pkt;                         \
                                                        \
        _a->w0 = _SHIFTL(2, 24, 8) | _SHIFTL(d, 0, 24); \
        _a->w1 = (u32)(c);                              \
    }

#define aDMEMMove(pkt, dmemi, dmemo, count)                      \
    {                                                            \
        Acmd *_a = (Acmd *)pkt;                                  \
                                                                 \
        _a->w0 = _SHIFTL(10, 24, 8) | _SHIFTL(dmemi, 0, 24);     \
        _a->w1 = _SHIFTL(dmemo, 16, 16) | _SHIFTL(count, 0, 16); \
    }

#define aLoadADPCM(pkt, c, d)                            \
    {                                                    \
        Acmd *_a = (Acmd *)pkt;                          \
                                                         \
        _a->w0 = _SHIFTL(11, 24, 8) | _SHIFTL(c, 0, 24); \
        _a->w1 = (u32)(d);                               \
    }

#define K0_TO_PHYS(x) ((u32)(x) & 0x1FFFFFFF)

#define n_aLoadBuffer(pkt, c, d, s)                                          \
    {                                                                        \
        Acmd *_a = (Acmd *)pkt;                                              \
                                                                             \
        _a->w0 = _SHIFTL(4, 24, 8) | _SHIFTL(c, 12, 12) | _SHIFTL(d, 0, 12); \
        _a->w1 = (u32)(s);                                                   \
    }

#define aSetLoop(pkt, a)             \
    {                                \
        Acmd *_a = (Acmd *)pkt;      \
                                     \
        _a->w0 = _SHIFTL(15, 24, 8); \
        _a->w1 = (u32)(a);           \
    }

#define n_aADPCMdec(pkt, s, f, c, a, d)                                                          \
    {                                                                                            \
        Acmd *_a = (Acmd *)pkt;                                                                  \
                                                                                                 \
        _a->w0 = _SHIFTL(1, 24, 8) | _SHIFTL(s, 0, 24);                                          \
        _a->w1 = _SHIFTL(f, 28, 4) | _SHIFTL(c, 16, 12) | _SHIFTL(a, 12, 4) | _SHIFTL(d, 0, 12); \
    }

Acmd *_decodeChunk_80087264(Acmd *ptr, N_PVoice *f, s32 tsam, s32 nbytes, s16 outp, s16 inp, u32 flags);

#ifdef NON_MATCHING
/* Same code; decoded and the zero inp argument swap s7/s8. The pad array reproduces the 0x58 frame. */
Acmd *n_alAdpcmPull(N_PVoice *f, s16 *outp, s32 outCount, Acmd *p) {
    s16 inp;
    Acmd *ptr = p;
    s32 nbytes;
    s32 nSam;
    s32 nframes;
    s32 op;
    s32 tsam;
    s32 nLeft;
    s32 bEnd;
    s32 decoded = 0;
    s32 looped = 0;
    s32 overFlow;
    s32 nOver;
    s32 startZero;
    s32 pad[4];

    if (outCount == 0) {
        return ptr;
    }

    aLoadADPCM(ptr++, f->dc_bookSize, K0_TO_PHYS(f->dc_table->waveInfo.adpcmWave.book->book));

    inp = 0;
    looped = (outCount + f->dc_sample > f->dc_loop.end) && (f->dc_loop.count != 0);
    if (looped) {
        nSam = f->dc_loop.end - f->dc_sample;
    } else {
        nSam = outCount;
    }

    if (f->dc_lastsam) {
        nLeft = ADPCMFSIZE - f->dc_lastsam;
    } else {
        nLeft = 0;
    }
    tsam = nSam - nLeft;
    if (tsam < 0) {
        tsam = 0;
    }

    nframes = (tsam + ADPCMFSIZE - 1) >> LFSAMPLES;
    nbytes = nframes * ADPCMFBYTES;

    if (looped) {
        ptr = _decodeChunk_80087264(ptr, f, tsam, nbytes, *outp, 0, f->dc_first);

        if (f->dc_lastsam) {
            *outp += (f->dc_lastsam << 1);
        } else {
            *outp += (ADPCMFSIZE << 1);
        }

        f->dc_lastsam = f->dc_loop.start & 0xF;
        f->dc_memin = (s32)f->dc_table->base + ADPCMFBYTES * ((s32)(f->dc_loop.start >> LFSAMPLES) + 1);
        f->dc_sample = f->dc_loop.start;

        bEnd = *outp;
        while (outCount > nSam) {
            outCount -= nSam;

            op = (bEnd + ((nframes + 1) << (LFSAMPLES + 1)) + 16) & ~0x1F;

            bEnd += (nSam << 1);

            if ((f->dc_loop.count != -1) && (f->dc_loop.count != 0)) {
                f->dc_loop.count--;
            }

            nSam = MIN(outCount, f->dc_loop.end - f->dc_loop.start);
            tsam = nSam - ADPCMFSIZE + f->dc_lastsam;
            if (tsam < 0) {
                tsam = 0;
            }
            nframes = (tsam + ADPCMFSIZE - 1) >> LFSAMPLES;
            nbytes = nframes * ADPCMFBYTES;
            ptr = _decodeChunk_80087264(ptr, f, tsam, nbytes, op, inp, f->dc_first | A_LOOP);

            aDMEMMove(ptr++, op + (f->dc_lastsam << 1), bEnd, nSam << 1);
        }

        f->dc_lastsam = (outCount + f->dc_lastsam) & 0xF;
        f->dc_sample += outCount;
        f->dc_memin += ADPCMFBYTES * nframes;
        return ptr;
    }

    nSam = nframes << LFSAMPLES;

    overFlow = f->dc_memin + nbytes - ((s32)f->dc_table->base + f->dc_table->len);
    if (overFlow < 0) {
        overFlow = 0;
    }
    nOver = (overFlow / ADPCMFBYTES) << LFSAMPLES;
    if (nOver > nSam + nLeft) {
        nOver = nSam + nLeft;
    }

    nbytes -= overFlow;

    if ((nOver - (nOver & 0xF)) < outCount) {
        decoded = 1;
        ptr = _decodeChunk_80087264(ptr, f, nSam - nOver, nbytes, *outp, 0, f->dc_first);

        if (f->dc_lastsam) {
            *outp += (f->dc_lastsam << 1);
        } else {
            *outp += (ADPCMFSIZE << 1);
        }

        f->dc_lastsam = (outCount + f->dc_lastsam) & 0xF;
        f->dc_sample += outCount;
        f->dc_memin += ADPCMFBYTES * nframes;
    } else {
        f->dc_lastsam = 0;
        f->dc_memin += ADPCMFBYTES * nframes;
    }

    if (nOver) {
        f->dc_lastsam = 0;
        if (decoded) {
            startZero = (nLeft + nSam - nOver) << 1;
        } else {
            startZero = 0;
        }
        aClearBuffer(ptr++, startZero + *outp, nOver << 1);
    }
    return ptr;
}
#else
INCLUDE_ASM("asm/nonmatchings/17090", n_alAdpcmPull);
#endif

void n_alLoadParam(void *filter, s32 paramID, void *param) {
    N_PVoice *a = (N_PVoice *)filter;

    switch (paramID) {
        case 5: /* AL_FILTER_SET_WAVETABLE */
            a->dc_table = (ALWaveTable *)param;
            a->dc_memin = (s32)a->dc_table->base;
            a->dc_sample = 0;
            switch (a->dc_table->type) {
                case 0: /* AL_ADPCM_WAVE */
                    a->dc_table->len = 9 * ((s32)(a->dc_table->len / 9));
                    a->dc_bookSize = 2 * a->dc_table->waveInfo.adpcmWave.book->order *
                                     a->dc_table->waveInfo.adpcmWave.book->npredictors * 8;
                    if (a->dc_table->waveInfo.adpcmWave.loop) {
                        a->dc_loop.start = a->dc_table->waveInfo.adpcmWave.loop->start;
                        a->dc_loop.end = a->dc_table->waveInfo.adpcmWave.loop->end;
                        a->dc_loop.count = a->dc_table->waveInfo.adpcmWave.loop->count;
                        alCopy(a->dc_table->waveInfo.adpcmWave.loop->state, a->dc_lstate, 0x20);
                    } else {
                        a->dc_loop.start = a->dc_loop.end = a->dc_loop.count = 0;
                    }
                    break;
                case 1: /* AL_RAW16_WAVE */
                    if (a->dc_table->waveInfo.rawWave.loop) {
                        a->dc_loop.start = a->dc_table->waveInfo.rawWave.loop->start;
                        a->dc_loop.end = a->dc_table->waveInfo.rawWave.loop->end;
                        a->dc_loop.count = a->dc_table->waveInfo.rawWave.loop->count;
                    } else {
                        a->dc_loop.start = a->dc_loop.end = a->dc_loop.count = 0;
                    }
                    break;
                default:
                    break;
            }
            break;
        case 4: /* AL_FILTER_RESET */
            a->dc_lastsam = 0;
            a->dc_first = 1;
            a->dc_sample = 0;
            if (a->dc_table) {
                a->dc_memin = (s32)a->dc_table->base;
                if (a->dc_table->type == 0) {
                    if (a->dc_table->waveInfo.adpcmWave.loop) {
                        a->dc_loop.count = a->dc_table->waveInfo.adpcmWave.loop->count;
                    }
                } else if (a->dc_table->type == 1) {
                    if (a->dc_table->waveInfo.rawWave.loop) {
                        a->dc_loop.count = a->dc_table->waveInfo.rawWave.loop->count;
                    }
                }
            }
            break;
        default:
            break;
    }
}

Acmd *_decodeChunk_80087264(Acmd *ptr, N_PVoice *f, s32 tsam, s32 nbytes, s16 outp, s16 inp, u32 flags) {
    s32 dramAlign, dramLoc;

    if (nbytes > 0) {
        dramLoc = (f->dc_dma)(f->dc_memin, nbytes, f->dc_dmaState);
        dramAlign = dramLoc & 0x7;
        nbytes += dramAlign;
        n_aLoadBuffer(ptr++, nbytes + 8 - (nbytes & 0x7), inp, dramLoc - dramAlign);
    } else {
        dramAlign = 0;
    }

    if (flags & A_LOOP) {
        aSetLoop(ptr++, K0_TO_PHYS(f->dc_lstate));
    }

    n_aADPCMdec(ptr++, f->dc_state, flags, tsam << 1, dramAlign, outp);

    f->dc_first = 0;

    return ptr;
}
