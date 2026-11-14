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

void init_lpfilter(ALLowPass *lp);

INCLUDE_ASM("asm/nonmatchings/17990", func_80087590);

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

INCLUDE_ASM("asm/nonmatchings/17990", _n_loadOutputBuffer);

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
