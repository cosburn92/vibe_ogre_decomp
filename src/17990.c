#include "n_audio.h"

/* n_audio n_reverb.c */

#define FIXED_SAMPLE 184
#define RANGE 2.0
#define CONVERT 173123.404906676

#define n_aLoadBuffer(pkt, c, d, s)                                          \
    {                                                                        \
        Acmd *_a = (Acmd *)pkt;                                              \
                                                                             \
        _a->w0 = _SHIFTL(4, 24, 8) | _SHIFTL(c, 12, 12) | _SHIFTL(d, 0, 12); \
        _a->w1 = (u32)(s);                                                   \
    }

#define n_aSaveBuffer(pkt, c, d, s)                                          \
    {                                                                        \
        Acmd *_a = (Acmd *)pkt;                                              \
                                                                             \
        _a->w0 = _SHIFTL(6, 24, 8) | _SHIFTL(c, 12, 12) | _SHIFTL(d, 0, 12); \
        _a->w1 = (u32)(s);                                                   \
    }

#define aLoadADPCM(pkt, c, d)                            \
    {                                                    \
        Acmd *_a = (Acmd *)pkt;                          \
                                                         \
        _a->w0 = _SHIFTL(11, 24, 8) | _SHIFTL(c, 0, 24); \
        _a->w1 = (u32)(d);                               \
    }

#define n_aPoleFilter(pkt, f, g, t, s)                                       \
    {                                                                        \
        Acmd *_a = (Acmd *)pkt;                                              \
                                                                             \
        _a->w0 = _SHIFTL(14, 24, 8) | _SHIFTL(f, 16, 8) | _SHIFTL(g, 0, 16); \
        _a->w1 = _SHIFTL(t, 24, 8) | _SHIFTL((u32)(s), 0, 24);               \
    }

#define n_aMix(pkt, f, g, i, o)                                              \
    {                                                                        \
        Acmd *_a = (Acmd *)pkt;                                              \
                                                                             \
        _a->w0 = _SHIFTL(12, 24, 8) | _SHIFTL(f, 16, 8) | _SHIFTL(g, 0, 16); \
        _a->w1 = _SHIFTL(i, 16, 16) | _SHIFTL(o, 0, 16);                     \
    }

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

#define n_aResample(pkt, s, f, p, i, o)                                                                \
    {                                                                                                  \
        Acmd *_a = (Acmd *)pkt;                                                                        \
                                                                                                       \
        _a->w0 = _SHIFTL(5, 24, 8) | _SHIFTL(s, 0, 24);                                                \
        _a->w1 = _SHIFTL(f, 30, 2) | _SHIFTL(p, 14, 16) | _SHIFTL(i, 2, 12) | _SHIFTL((o) >> 8, 0, 2); \
    }

void init_lpfilter(ALLowPass *lp);
Acmd *func_80085D00(s32 sampleOffset, Acmd *p); /* n_alAuxBusPull */
f32 _doModFunc(ALDelay *d, s32 count);
Acmd *_n_loadOutputBuffer(ALFx *r, ALDelay *d, s32 buff, Acmd *p);
Acmd *_n_loadBuffer(ALFx *r, s16 *curr_ptr, s32 buff, s32 count, Acmd *p);
Acmd *_n_saveBuffer(ALFx *r, s16 *curr_ptr, s32 buff, Acmd *p);
Acmd *_n_filterBuffer(ALLowPass *lp, s32 buff, Acmd *p);

#define UNITY_PITCH 0x8000
#define N_AL_TEMP_0 0
#define N_AL_TEMP_1 0x170
#define N_AL_TEMP_2 0x2E0
#define N_AL_AUX_L_OUT 0x7C0
#define N_AL_AUX_R_OUT 0x930
#define SWAP(in, out)     {                         s16 t = out;          out = in;             in = t;           }

/* n_alFxPull */
Acmd *func_80087590(s32 sampleOffset, Acmd *p) {
    Acmd *ptr = p;
    ALFx *r = alGlobals_800A9E54->auxBus->fx;
    s16 i, buff1, buff2, input, output;
    s16 *in_ptr, *out_ptr, *prev_out_ptr = 0;
    ALDelay *d;

    ptr = func_80085D00(sampleOffset, p);

    input = N_AL_AUX_L_OUT;
    output = N_AL_AUX_R_OUT;
    buff1 = N_AL_TEMP_0;
    buff2 = N_AL_TEMP_1;

    n_aMix(ptr++, 0, 0xDA83, N_AL_AUX_L_OUT, input);
    n_aMix(ptr++, 0, 0x5A82, N_AL_AUX_R_OUT, input);
    ptr = _n_saveBuffer(r, r->input, input, ptr);
    aClearBuffer(ptr++, output, FIXED_SAMPLE << 1);

    for (i = 0; i < r->section_count; i++) {
        d = &r->delay[i];
        in_ptr = &r->input[-d->input];
        out_ptr = &r->input[-d->output];

        if (in_ptr == prev_out_ptr) {
            SWAP(buff1, buff2);
        } else {
            ptr = _n_loadBuffer(r, in_ptr, buff1, FIXED_SAMPLE, ptr);
        }
        ptr = _n_loadOutputBuffer(r, d, buff2, ptr);

        if (d->ffcoef) {
            n_aMix(ptr++, 0, (u16)d->ffcoef, buff1, buff2);
            if (!d->rs && !d->lp) {
                ptr = _n_saveBuffer(r, out_ptr, buff2, ptr);
            }
        }

        if (d->fbcoef) {
            n_aMix(ptr++, 0, (u16)d->fbcoef, buff2, buff1);
            ptr = _n_saveBuffer(r, in_ptr, buff1, ptr);
        }

        if (d->lp) {
            ptr = _n_filterBuffer(d->lp, buff2, ptr);
        }

        if (!d->rs) {
            ptr = _n_saveBuffer(r, out_ptr, buff2, ptr);
        }

        if (d->gain) {
            n_aMix(ptr++, 0, (u16)d->gain, buff2, output);
        }

        prev_out_ptr = &r->input[d->output];
    }

    r->input += FIXED_SAMPLE;
    if (r->input > &r->base[r->length]) {
        r->input -= r->length;
    }

    aDMEMMove(ptr++, output, N_AL_AUX_L_OUT, FIXED_SAMPLE << 1);
    return ptr;
}

/* n_alFxParamHdl */
s32 func_800878A0(void *filter, s32 paramID, void *param) {
    ALFx *f = (ALFx *)filter;
    s32 p = (paramID - 2) % 8;
    s32 s = (paramID - 2) / 8;
    s32 val = *(s32 *)param;

    switch (p) {
        case 0: /* INPUT_PARAM */
            f->delay[s].input = (u32)val & 0xFFFFFFF8;
            break;
        case 1: /* OUTPUT_PARAM */
            f->delay[s].output = (u32)val & 0xFFFFFFF8;
            break;
        case 3: /* FFCOEF_PARAM */
            f->delay[s].ffcoef = (s16)val;
            break;
        case 2: /* FBCOEF_PARAM */
            f->delay[s].fbcoef = (s16)val;
            break;
        case 4: /* GAIN_PARAM */
            f->delay[s].gain = (s16)val;
            break;
        case 5: /* CHORUSRATE_PARAM */
            f->delay[s].rsinc = ((((f32)val) / 1000) * RANGE) / alGlobals_800A9E54->outputRate;
            break;
        case 6: /* CHORUSDEPTH_PARAM */
            f->delay[s].rsgain = (((f32)val) / CONVERT) * (f->delay[s].output - f->delay[s].input);
            break;
        case 7: /* LPFILT_PARAM */
            if (f->delay[s].lp) {
                f->delay[s].lp->fc = (s16)val;
                init_lpfilter(f->delay[s].lp);
            }
            break;
    }
    return 0;
}

#ifdef NON_MATCHING
/* Same code; the original computes buff >> 8 before loading d->rs->first for the resample command. */
Acmd *_n_loadOutputBuffer(ALFx *r, ALDelay *d, s32 buff, Acmd *p) {
    Acmd *ptr = p;
    s32 ratio, count, rbuff = N_AL_TEMP_2;
    s16 *out_ptr;
    f32 fincount, fratio, delta;
    s32 ramalign = 0, length;
    s32 incount = FIXED_SAMPLE;

    if (d->rs) {
        length = d->output - d->input;
        delta = _doModFunc(d, incount);
        delta /= length;
        delta = (s32)(delta * UNITY_PITCH);
        delta = delta / UNITY_PITCH;
        fratio = 1.0 - delta;

        fincount = d->rs->delta + (fratio * (f32)incount);
        count = (s32)fincount;
        d->rs->delta = fincount - (f32)count;

        out_ptr = &r->input[-(d->output - d->rsdelta)];
        ramalign = ((s32)out_ptr & 0x7) >> 1;
        ptr = _n_loadBuffer(r, out_ptr - ramalign, rbuff, count + ramalign, ptr);

        ratio = (s32)(fratio * UNITY_PITCH);
        n_aResample(ptr++, osVirtualToPhysical(d->rs->state), d->rs->first, ratio, rbuff + (ramalign << 1), buff);
        d->rs->first = 0;
        d->rsdelta += count - incount;
    } else {
        out_ptr = &r->input[-d->output];
        ptr = _n_loadBuffer(r, out_ptr, buff, incount, ptr);
    }
    return ptr;
}
#else
INCLUDE_ASM("asm/nonmatchings/17990", _n_loadOutputBuffer);
#endif

Acmd *_n_loadBuffer(ALFx *r, s16 *curr_ptr, s32 buff, s32 count, Acmd *p) {
    Acmd *ptr = p;
    s32 after_end, before_end;
    s16 *updated_ptr, *delay_end;

    delay_end = &r->base[r->length];
    if (curr_ptr < r->base) {
        curr_ptr += r->length;
    }
    updated_ptr = curr_ptr + count;

    if (updated_ptr > delay_end) {
        after_end = updated_ptr - delay_end;
        before_end = delay_end - curr_ptr;

        n_aLoadBuffer(ptr++, before_end << 1, buff, osVirtualToPhysical(curr_ptr));
        n_aLoadBuffer(ptr++, after_end << 1, buff + (before_end << 1), osVirtualToPhysical(r->base));
    } else {
        n_aLoadBuffer(ptr++, count << 1, buff, osVirtualToPhysical(curr_ptr));
    }
    return ptr;
}

Acmd *_n_saveBuffer(ALFx *r, s16 *curr_ptr, s32 buff, Acmd *p) {
    Acmd *ptr = p;
    s32 after_end, before_end;
    s16 *updated_ptr, *delay_end;

    delay_end = &r->base[r->length];
    if (curr_ptr < r->base) {
        curr_ptr += r->length;
    }
    updated_ptr = curr_ptr + FIXED_SAMPLE;

    if (updated_ptr > delay_end) {
        after_end = updated_ptr - delay_end;
        before_end = delay_end - curr_ptr;

        n_aSaveBuffer(ptr++, before_end << 1, buff, osVirtualToPhysical(curr_ptr));
        n_aSaveBuffer(ptr++, after_end << 1, buff + (before_end << 1), osVirtualToPhysical(r->base));
    } else {
        n_aSaveBuffer(ptr++, FIXED_SAMPLE << 1, buff, osVirtualToPhysical(curr_ptr));
    }
    return ptr;
}

Acmd *_n_filterBuffer(ALLowPass *lp, s32 buff, Acmd *p) {
    Acmd *ptr = p;
    s32 t = buff >> 8;

    aLoadADPCM(ptr++, 32, osVirtualToPhysical(lp->fcvec.fccoef));
    n_aPoleFilter(ptr++, lp->first, lp->fgain, t, osVirtualToPhysical(lp->fstate));
    lp->first = 0;
    return ptr;
}
