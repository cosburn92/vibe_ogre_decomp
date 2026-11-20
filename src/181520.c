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

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_80098B60(s32 *, f32, f32, f32);    /* extern */
s32 func_80098D00(s32 *, f32, f32, s32); /* extern */
s32 guMtxCatF(s32 *, s32 *, s32 *); /* extern */
s32 guRotateF(s32 *, f32, f32, f32, f32);   /* extern */
extern s32 D_8021AC58_ovl_17F9C0;
extern s32 D_8021AC5A_ovl_17F9C0;
extern s32 D_8021AD50_ovl_17F9C0;
extern s32 D_8021AD52_ovl_17F9C0;
extern s32 D_8021AD54_ovl_17F9C0;

void func_80216C08_ovl_17F9C0(s32 *arg0, s16 arg1) {
    s32 sp18;
    s32 sp58;
    s32 sp98;
    f32 temp_fv0;
    f32 temp_fv0_3;
    f64 temp_fv0_2;
    s16 temp_v0_2;
    s16 temp_v1_2;
    s16 var_a0;
    s16 var_v0;
    s32 temp_s0;
    s32 temp_s2;
    s32 var_v0_2;
    u16 temp_v0;
    u16 temp_v1;

    if (D_8021AF04_ovl_17F9C0 == 4) {
        temp_s2 = arg1 * 6;
        temp_v1 = *(&D_8021AD54_ovl_17F9C0 + temp_s2);
        temp_v0 = (u16) D_8021AF00_ovl_17F9C0->timer;
        temp_v0_2 = temp_v0 - temp_v1;
        if (temp_v0_2 >= 0) {
            temp_fv0 = (f32) (1.0 - ((f64) temp_v0_2 * 0.015));
            func_80098B60(&sp98, temp_fv0, temp_fv0, temp_fv0);
            var_a0 = temp_v0_2;
            if (temp_v0_2 >= 0x5B) {
                var_a0 = (temp_v0 - temp_v1) % 90;
            }
            var_v0 = *(&D_8021AD52_ovl_17F9C0 + temp_s2);
            temp_v1_2 = *(&D_8021AD50_ovl_17F9C0 + temp_s2);
            if (var_v0 < 0) {
                var_v0 = -var_v0;
            }
            if (temp_v1_2 >= 0) {
                var_v0_2 = var_v0 + temp_v1_2;
            } else {
                var_v0_2 = var_v0 - temp_v1_2;
            }
            temp_s0 = arg1 * 6;
            guRotateF(&sp58, (f32) var_a0 * ((f32) var_v0_2 + 4.0f), (f32) *(&D_8021AD52_ovl_17F9C0 + temp_s0), (f32) -*(&D_8021AD50_ovl_17F9C0 + temp_s0), (f32) ((f64) temp_v0_2 * 0.01));
            guMtxCatF(&sp98, &sp58, &sp58);
            temp_fv0_2 = (f64) (f32) temp_v0_2;
            temp_fv0_3 = (f32) (temp_fv0_2 * (temp_fv0_2 * 0.04));
            func_80098D00(&sp18, (f32) *(&D_8021AC58_ovl_17F9C0 + temp_s0) + ((f32) *(&D_8021AD50_ovl_17F9C0 + temp_s0) * temp_fv0_3), (f32) *(&D_8021AC5A_ovl_17F9C0 + temp_s0) + ((f32) *(&D_8021AD52_ovl_17F9C0 + temp_s0) * temp_fv0_3) + 1.0f, 0xC2C80000);
            guMtxCatF(&sp58, &sp18, arg0);
            return;
        }
        func_80098D00(arg0, (f32) *(&D_8021AC58_ovl_17F9C0 + temp_s2), (f32) (*(&D_8021AC5A_ovl_17F9C0 + temp_s2) + 1), 0xC2C80000);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/181520", func_80216C08_ovl_17F9C0);
#endif

INCLUDE_ASM("asm/nonmatchings/181520", func_80216F3C_ovl_17F9C0);

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
