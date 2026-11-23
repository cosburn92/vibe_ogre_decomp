#include "common.h"
#include "scene.h"

typedef struct {
    s32 data[0x16];
} Camera; /* size 0x58 */

typedef struct {
    /* 0x00 */ Camera *saved;
    /* 0x04 */ s32 arg;
    /* 0x08 */ s16 timer;
    /* 0x0A */ s16 alpha;
    /* 0x0C */ s16 *alphaPtr;
    /* 0x10 */ s16 unk10;
    /* 0x14 */ s32 unk14;
} Ovl17F9C0Ctx; /* size 0x18 */

extern Ovl17F9C0Ctx *D_8021AF00_ovl_17F9C0;
extern u8 D_8021AF04_ovl_17F9C0;
extern Camera *D_8018F58C;
extern u8 D_800EB290[];
extern u8 D_801F365D;
extern u8 D_800E7A90[];
extern s32 D_801F3620;

void *HMalloc(s32 size);
void *HFree(void *p);
void func_800EA604(void *ch, s32 sound);
s32 func_80216AE0_ovl_17F9C0(void);
void func_80216F3C_ovl_17F9C0(void);
void func_80217114_ovl_17F9C0(void);
void func_801DFF50(void);
void func_801DFF80(void);
void func_8017BED4(void);

/* Steps *alphaPtr towards unk10 over unk14 frames; returns 1 once it arrives */
#ifdef NON_MATCHING
/* Branch layout differs (the original returns 1 via a jump with the constant in the delay slot). */
s32 func_80216AE0_ovl_17F9C0(void) {
    s16 *p = D_8021AF00_ovl_17F9C0->alphaPtr;
    s16 target = D_8021AF00_ovl_17F9C0->unk10;
    s32 frames = D_8021AF00_ovl_17F9C0->unk14;
    s16 d;
    s16 step;

    if (p == NULL) {
        return 0;
    }
    d = target - *p;
    if (d == 0) {
        return 1;
    }
    if (d > 0) {
        step = target / frames;
    } else {
        step = -((255 - target) / frames);
    }
    *p += step;
    if (step < 0) {
        if (target < *p) {
            return 0;
        }
    } else if (*p < target) {
        return 0;
    }
    *p = target;
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/181520", func_80216AE0_ovl_17F9C0);
#endif

void func_80098B60(f32 mf[4][4], f32 x, f32 y, f32 z); /* guScaleF */
void func_80098D00(f32 mf[4][4], f32 x, f32 y, f32 z); /* guTranslateF */
void guMtxCatF(f32 a[4][4], f32 b[4][4], f32 r[4][4]);
void guRotateF(f32 mf[4][4], f32 a, f32 x, f32 y, f32 z);
typedef struct {
    s16 x;
    s16 y;
    s16 pad;
} Pos17F;
typedef struct {
    s16 vx;
    s16 vy;
    u16 delay;
} Shard17F;
extern Pos17F D_8021AC58_ovl_17F9C0[];
extern Shard17F D_8021AD50_ovl_17F9C0[];

/* Matrix of shard i of the shattering screen (state 4): after its delay it shrinks, spins about
 * its flight direction and flies off along (vx, vy) with growing speed */
#ifdef NON_MATCHING
/* 205/205 but 196 words: the original keeps no float in a saved register (frame 248, no f20) and computes timer - delay once */
void func_80216C08_ovl_17F9C0(f32 mf[4][4], s16 i) {
    f32 tr[4][4];
    f32 rot[4][4];
    f32 scale[4][4];
    u16 dl;
    u16 tm;
    s16 t;
    s32 a;
    s32 vy;
    s32 vx;
    s32 speed;
    f32 s;
    f32 d;

    if (D_8021AF04_ovl_17F9C0 != 4) {
        return;
    }
    dl = D_8021AD50_ovl_17F9C0[i].delay;
    tm = D_8021AF00_ovl_17F9C0->timer;
    t = tm - dl;
    if (t >= 0) {
        s = 1.0 - t * 0.015;
        func_80098B60(scale, s, s, s);
        a = t;
        if (t > 90) {
            a = (tm - dl) % 90;
        }
        vy = D_8021AD50_ovl_17F9C0[i].vy;
        vx = D_8021AD50_ovl_17F9C0[i].vx;
        if (vy < 0) {
            vy = -vy;
        }
        if (vx >= 0) {
            speed = vy + vx;
        } else {
            speed = vy - vx;
        }
        guRotateF(rot, a * (speed + 4.0f), D_8021AD50_ovl_17F9C0[i].vy, -D_8021AD50_ovl_17F9C0[i].vx, t * 0.01);
        guMtxCatF(scale, rot, rot);
        d = t * (t * 0.04);
        func_80098D00(tr, D_8021AC58_ovl_17F9C0[i].x + D_8021AD50_ovl_17F9C0[i].vx * d,
                      D_8021AC58_ovl_17F9C0[i].y + D_8021AD50_ovl_17F9C0[i].vy * d + 1.0f, -100.0f);
        guMtxCatF(rot, tr, mf);
        return;
    }
    func_80098D00(mf, D_8021AC58_ovl_17F9C0[i].x, D_8021AC58_ovl_17F9C0[i].y + 1, -100.0f);
}
#else
INCLUDE_ASM("asm/nonmatchings/181520", func_80216C08_ovl_17F9C0);
#endif

typedef struct {
    u32 w0;
    u32 w1;
} Gfx181;
typedef struct {
    /* 0x00 */ void *p0;
    /* 0x04 */ void *p1;
    /* 0x08 */ u8 (*mtx)[0x40];
} FbSet181;
extern Gfx181 *D_800E9BA0;
extern FbSet181 *D_800E9BE0;
extern u16 D_800C4BE4;
extern u16 D_800C4C24;
extern u16 D_800E7A0E;
extern u8 D_8021ABC0_ovl_17F9C0[];
void guOrtho(void *m, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, f32 scale);
void guLookAt(void *m, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);
#define CAMF(i) (((f32 *)D_8018F58C->data)[i])

/* Sets up a 320x240 orthographic camera looking at the screen centre (same as 1A2C20's) */
void func_80216F3C_ovl_17F9C0(void) {
    CAMF(5) = 160.0f;
    CAMF(6) = 120.0f;
    CAMF(7) = 60.0f;
    CAMF(8) = 160.0f;
    CAMF(9) = 120.0f;
    CAMF(10) = 0.0f;
    CAMF(11) = 0.0f;
    CAMF(12) = 1.0f;
    CAMF(13) = 0.0f;
    D_800E7A0E = D_800C4BE4;
    guOrtho(D_800E9BE0->mtx[D_800C4BE4], -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);
    {
        Gfx181 *_g = D_800E9BA0++;

        _g->w0 = 0xDA380007;
        _g->w1 = (u32)D_800E9BE0->mtx[D_800C4BE4] - 0x80000000;
    }
    D_800C4C24 = ++D_800C4BE4;
    guLookAt(D_800E9BE0->mtx[D_800C4C24], CAMF(5), CAMF(6), CAMF(7), CAMF(8), CAMF(9), CAMF(10), CAMF(11), CAMF(12),
             CAMF(13));
    {
        Gfx181 *_g = D_800E9BA0++;

        _g->w0 = 0xDA380005;
        _g->w1 = (u32)D_800E9BE0->mtx[D_800C4BE4++] - 0x80000000;
    }
    {
        Gfx181 *_g = D_800E9BA0++;

        _g->w0 = 0xDE000000;
        _g->w1 = (u32)D_8021ABC0_ovl_17F9C0;
    }
}

INCLUDE_ASM("asm/nonmatchings/181520", func_80217114_ovl_17F9C0);

inline void func_80217474_ovl_17F9C0(s32 arg) {
    D_8021AF00_ovl_17F9C0 = HMalloc(sizeof(Ovl17F9C0Ctx));
    D_8021AF00_ovl_17F9C0->arg = arg;
    D_8021AF00_ovl_17F9C0->saved = HMalloc(sizeof(Camera));
    *D_8021AF00_ovl_17F9C0->saved = *D_8018F58C;
    D_8021AF00_ovl_17F9C0->timer = 0;
    D_8021AF00_ovl_17F9C0->alpha = 0xFF;
}

inline void func_8021751C_ovl_17F9C0(void) {
    *D_8018F58C = *D_8021AF00_ovl_17F9C0->saved;
    HFree(D_8021AF00_ovl_17F9C0->saved);
    HFree(D_8021AF00_ovl_17F9C0);
    D_8021AF00_ovl_17F9C0 = NULL;
    D_8021AF04_ovl_17F9C0 = 0;
}

inline void func_802175B0_ovl_17F9C0(void) {
    Ovl17F9C0Ctx *ctx = D_8021AF00_ovl_17F9C0;

    if (ctx->timer == 0) {
        func_800EA604(D_800EB290, 0x288);
    }
    D_8021AF00_ovl_17F9C0->timer++;
    ctx->alphaPtr = &D_8021AF00_ovl_17F9C0->alpha;
    ctx->unk10 = 0;
    ctx->unk14 = 0x26;
    func_80216AE0_ovl_17F9C0();
    if (D_8021AF00_ovl_17F9C0->timer < 50) {
        D_8021AF04_ovl_17F9C0 = 4;
    } else {
        D_8021AF04_ovl_17F9C0 = 1;
    }
}

void func_80217640_ovl_17F9C0(void) {
    func_80216F3C_ovl_17F9C0();
    func_80217114_ovl_17F9C0();
}

u8 func_80217664_ovl_17F9C0(void) {
    return D_8021AF04_ovl_17F9C0;
}

s32 func_80217670_ovl_17F9C0(void) {
    s32 ret = 0;

    D_801F365D |= 1;
    D_800E82C8[D_800E7A90[0x29]].unk8B |= 4;
    if (D_8021AF04_ovl_17F9C0 == 0) {
        func_801DFF50();
        func_8017BED4();
        func_80217474_ovl_17F9C0(D_801F3620);
    }
    func_802175B0_ovl_17F9C0();
    if (D_8021AF04_ovl_17F9C0 == 1) {
        func_8021751C_ovl_17F9C0();
        ret = 1;
        func_801DFF80();
    }
    return ret;
}
