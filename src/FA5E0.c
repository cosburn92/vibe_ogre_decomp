#include "common.h"

/* Field access by offset, for widget records whose layouts are not mapped yet. */
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))

typedef struct {
    s16 h0;
    u8 unk02[2];
    s32 w4;
    u8 unk08[4];
    s32 wC;
    u8 unk10[0x74];
    s32 x84;
    u8 x88;
    u8 x89;
    u8 x8A;
    u8 x8B;
} Widget3390;
extern Widget3390 *D_801B3390_ovl_0FA5E0;
extern u8 *D_801B3E20_ovl_0FA5E0;
extern s32 D_801B3DE0_ovl_0FA5E0[];
extern u8 D_801B436C_ovl_0FA5E0[];
extern u16 D_800C4C26;
void nuGfxTaskAllEndWait(void);
void func_801AEDEC_ovl_0FA5E0(Widget3390 *p);
void func_801AEE94_ovl_0FA5E0(s32 i, void *v);
void HFree(void *p);





typedef struct {
    /* 0x00 */ u16 active;
    /* 0x02 */ u8 pad02[2];
    /* 0x04 */ s32 a;
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 y;
    /* 0x10 */ f32 f10;
    /* 0x14 */ f32 f14;
    /* 0x18 */ s16 f18;
    /* 0x1A */ s16 f1A;
    /* 0x1C */ u16 f1C[4];
    /* 0x24 */ u8 pad24[8];
    /* 0x2C */ u16 f2C[4];
    /* 0x34 */ s32 f34;
    /* 0x38 */ s32 f38;
    /* 0x3C */ s32 f3C;
    /* 0x40 */ s32 f40;
} Anim0444;
s32 func_8009C7CC(void);
s32 func_801793E4(s32 c, s32 b);
void func_801B01FC_ovl_0FA5E0(u8 *p);
void func_801B2FF8_ovl_0FA5E0(void **p);
void HFree(void *p);
typedef struct {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u8 flags2;
    /* 0x03 */ u8 flags3;
    /* 0x04 */ u8 unk04[2];
    /* 0x06 */ s16 x;
    /* 0x08 */ s16 y;
    /* 0x0A */ s16 x2;
    /* 0x0C */ s16 y2;
    /* 0x0E */ u16 hE;
    /* 0x10 */ u8 unk10[4];
    /* 0x14 */ void (*update)(void);
    /* 0x18 */ void (*draw)(void);
    /* 0x1C */ void (*exit)(void);
    /* 0x20 */ u16 size;
    /* 0x22 */ u8 unk22[2];
    /* 0x24 */ s32 w24;
} CurSceneFA;
typedef struct {
    u8 unk00[0x88];
    u8 b88;
    u8 b89;
    u8 unk8A[0x1E];
} SceneFA; /* size 0xA8 */
extern CurSceneFA D_800E7A30;
extern SceneFA D_800E82C8[];
extern u8 D_800E91D0[];
extern u8 D_801A07D0[];
extern u8 D_8018F564;
extern u8 D_8018F565;
extern u8 D_8018F56C;
extern u8 D_8018F56D;
void bzero(void *p, s32 n);
s32 func_8007705C(s32 a, void *b, s32 c, s32 d, s32 e, s32 f, s32 g);
s32 func_801AB020(s32 id, s32 n);
void *LoadAsset(u32 handle, ...);
void func_801AD748_ovl_0FA5E0(void);
void func_801ADF6C_ovl_0FA5E0(void);
void func_801AE090_ovl_0FA5E0(void);
void func_801AEC40_ovl_0FA5E0(Widget3390 *p);
extern s32 D_801B4894_ovl_0FA5E0[]; /* bits per pixel by format */
void _bcopy(const void *src, void *dst, s32 n);
void *HMalloc(s32 size);
void *LoadChunkRaw(void *dst, s32 id);
s32 ReadU32BE(void *p);
void DecodeLZ(void *dst, void *src);
typedef struct {
    u32 w0;
    u32 w1;
} Gfx;
extern Gfx *D_800E9BA0;
void func_801792E8(void);
void func_80179F04(u8 *s);
void func_80179328(void);
extern u8 D_801869C8[];
/* --- end decls --- */

/* Scene init: full-screen (320x240) window scene with a 0x28-line child scene, loads asset 0x209A7B4 */
void func_801AD5A0_ovl_0FA5E0(s32 id) {
    D_800E7A30.update = func_801AD748_ovl_0FA5E0;
    D_800E7A30.draw = func_801ADF6C_ovl_0FA5E0;
    D_800E7A30.exit = func_801AE090_ovl_0FA5E0;
    D_800E7A30.size = 0x53C;
    D_800E7A30.w24 = 0;
    D_800E7A30.flags |= 0x200;
    D_800E7A30.flags2 |= 9;
    D_800E7A30.flags3 |= 0xC;
    bzero(D_800E91D0, 0x53C);
    D_801B3390_ovl_0FA5E0->h0 = id;
    D_801B3390_ovl_0FA5E0->w4 = 0;
    D_800E7A30.y2 = 0xF0;
    D_800E7A30.x2 = 0x140;
    D_800E7A30.x = 0;
    D_800E7A30.y = 0;
    D_800E82C8[func_8007705C(0xC000, D_801A07D0, 0, 0, 0x140, D_800E7A30.y2, (u16)(D_800E7A30.hE - 3))].b88 = 3;
    D_800E82C8[D_801B3390_ovl_0FA5E0->wC = func_801AB020(id, 0x28)].b89 = 9;
    D_8018F565 = 1;
    D_8018F564 = 0;
    D_8018F56D = 1;
    D_8018F56C = 1;
    LoadAsset(0x209A7B4, 0, -6);
    func_801AEC40_ovl_0FA5E0(D_801B3390_ovl_0FA5E0);
}

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801AD748_ovl_0FA5E0);

void func_80078674(s32 x, s32 y, s32 x2, s32 y2);
void func_80078C6C(s32 mode, s32 x, s32 y, s32 x2, s32 y2);
void func_801768D4(s32 w, s32 h, s32 x, s32 y, s32 x2, s32 y2);
void func_80197B70(void);
void func_801AE0C4_ovl_0FA5E0(f32 a, f32 b, s32 c, s32 d, s32 e);
void func_801B15BC_ovl_0FA5E0(Widget3390 *w);
void func_801AE5BC_ovl_0FA5E0(void);
void func_801AEB2C_ovl_0FA5E0(void);

/* Scene draw: frames the scene rectangle, then (unless the widget is closed) draws the background
 * and up to four placed items (entries of 0x1C bytes from widget+0x1C) */
void func_801ADF6C_ovl_0FA5E0(void) {
    s32 i;
    u8 *e;

    func_80078674(D_800E7A30.x, D_800E7A30.y, D_800E7A30.x2, D_800E7A30.y2);
    if (D_801B3390_ovl_0FA5E0->unk10[0] != 0) {
        func_80078C6C(1, D_800E7A30.x, D_800E7A30.y, D_800E7A30.x2, D_800E7A30.y2);
        return;
    }
    func_801768D4(0x140, 0xF0, D_800E7A30.x, D_800E7A30.y, D_800E7A30.x2, D_800E7A30.y2);
    func_80197B70();
    for (i = 0; i < 4; i++) {
        e = (u8 *)D_801B3390_ovl_0FA5E0 + i * 0x1C;
        if (FIELD(e, f32, 0x1C) != 0.0f) {
            func_801AE0C4_ovl_0FA5E0(FIELD(e, f32, 0x1C), FIELD(e, f32, 0x20), FIELD(e, s32, 0x24), FIELD(e, s32, 0x28), FIELD(e, s32, 0x2C));
        }
    }
    func_801B15BC_ovl_0FA5E0(D_801B3390_ovl_0FA5E0);
    func_801AE5BC_ovl_0FA5E0();
    func_801AEB2C_ovl_0FA5E0();
}

void func_801AE090_ovl_0FA5E0(void) {
    nuGfxTaskAllEndWait();
    D_800C4C26 = 0xFFFE;
    func_801AEDEC_ovl_0FA5E0(D_801B3390_ovl_0FA5E0);
}

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801AE0C4_ovl_0FA5E0);

#define GFXFA(w0_, w1_)                \
    {                                  \
        Gfx *_g = D_800E9BA0++;        \
                                       \
        _g->w0 = (w0_);                \
        _g->w1 = (w1_);                \
    }
extern u8 D_801B36A0_ovl_0FA5E0[8];
extern u8 D_801B36A8_ovl_0FA5E0[8];

/* Eight one-line fill rectangles across the screen at rows D_801B36A8, colours D_801B36A0 */
void func_801AE5BC_ovl_0FA5E0(void) {
    s32 i;

    func_80197B70();
    GFXFA(0xE7000000, 0);
    GFXFA(0xE7000000, 0);
    GFXFA(0xE3000A01, 0);
    GFXFA(0xE7000000, 0);
    GFXFA(0xD9000000, 0);
    GFXFA(0xFCFFFFFF, 0xFFFDF6FB);
    GFXFA(0xE200001C, 0x504340);
    for (i = 0; i < 8; i++) {
        GFXFA(0xE7000000, 0);
        GFXFA(0xFA000000, D_801B36A0_ovl_0FA5E0[i]);
        GFXFA(0xE7000000, 0);
        GFXFA(((D_801B36A8_ovl_0FA5E0[i] + 1) * 4) | 0xE4500000, D_801B36A8_ovl_0FA5E0[i] * 4);
        GFXFA(0xE1000000, 0);
        GFXFA(0xF1000000, 0);
        GFXFA(0xE7000000, 0);
    }
    GFXFA(0xE7000000, 0);
}

void func_801AE79C_ovl_0FA5E0(s32 i) {
    D_801B3390_ovl_0FA5E0->x88 = 1;
    D_801B3390_ovl_0FA5E0->x89 = 0xFF;
    D_801B3390_ovl_0FA5E0->x84 = D_801B3DE0_ovl_0FA5E0[i];
    D_801B3390_ovl_0FA5E0->x8B = 0;
    D_801B3390_ovl_0FA5E0->x8A = 0;
}

void func_801AE7EC_ovl_0FA5E0(void) {
    D_801B3390_ovl_0FA5E0->x88 = 0;
}

s32 func_801AE7FC_ovl_0FA5E0(void) {
    return D_801B3390_ovl_0FA5E0->x88 != 1;
}

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801AE814_ovl_0FA5E0);

/* Draws the widget's caption (colour 12) when it is visible */
void func_801AEB2C_ovl_0FA5E0(void) {
    Gfx *g;

    if (D_801B3390_ovl_0FA5E0->x88 != 0) {
        g = D_800E9BA0++;
        g->w0 = 0xDE000000;
        g->w1 = (u32)D_801869C8;
        func_801792E8();
        func_80179F04("{C12}");
        func_80179F04((u8 *)D_801B3390_ovl_0FA5E0 + 0x8C);
        func_80179328();
    }
}

/* Width of a string in pixels, stopping at '@'; glyph width 11 marks a two-byte character */
#ifdef NON_MATCHING
/* original reloads *s at the loop top; GCC reuses the test load */
s32 func_801AEBA4_ovl_0FA5E0(u8 *s) {
    s32 w = 0;
    u8 c;
    u8 v;

    while (*s != 0) {
        c = *s;
        v = func_801793E4(c, 0);
        if (v == 11) {
            s++;
            w += 11;
        } else {
            if (c == '@') {
                return w;
            }
            w += v;
        }
        s++;
    }
    return w;
}
#else
INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801AEBA4_ovl_0FA5E0);
#endif

/* Loads the 18 LZ images listed in chunk 0x1D61984 into o+0x19C and clears the rest of the state */
void func_801AEC40_ovl_0FA5E0(Widget3390 *o) {
    u32 i;
    s32 *tbl;
    u8 *raw;
    void *img;

    bzero((u8 *)o + 0x19C, 0x48);
    for (i = 0; i < 18; i++) {
        tbl = LoadChunkRaw(NULL, 0x1D61984);
        raw = LoadChunkRaw(NULL, tbl[i]);
        img = HMalloc(ReadU32BE(raw));
        DecodeLZ(img, raw);
        HFree(raw);
        HFree(tbl);
        ((void **)((u8 *)o + 0x19C))[i] = img;
    }
    bzero((u8 *)o + 0x258, 0x17C);
    bzero((u8 *)o + 0x3D4, 0x70);
    bzero((u8 *)o + 0x444, 0x70);
    bzero((u8 *)o + 0x4B4, 0x70);
    bzero((u8 *)o + 0x524, 0xC);
}

void func_801AED48_ovl_0FA5E0(void) {
    func_801AEE94_ovl_0FA5E0(0, D_801B436C_ovl_0FA5E0);
}

void func_801AED6C_ovl_0FA5E0(u8 *p) {
    u32 i;

    for (i = 0; i < 3; i++) {
        if (FIELD(p, void *, 0x524 + i * 4) != NULL) {
            func_801B2FF8_ovl_0FA5E0(FIELD(p, void *, 0x524 + i * 4));
        }
    }
    for (i = 0; i < 3; i++) {
        if (FIELD(p, void *, 0x530 + i * 4) != NULL) {
            func_801B2FF8_ovl_0FA5E0(FIELD(p, void *, 0x530 + i * 4));
        }
    }
}

/* Releases the screen's sub-objects and its 18 buffers */
void func_801AEDEC_ovl_0FA5E0(Widget3390 *w) {
    u8 *p = (u8 *)w;
    u32 i;
    u32 j;

    FIELD(p, s32, 0x194) = 0;
    for (i = 0; i < 3; i++) {
        if (FIELD(p, void *, 0x524 + i * 4) != NULL) {
            func_801B2FF8_ovl_0FA5E0(FIELD(p, void *, 0x524 + i * 4));
        }
    }
    for (i = 0; i < 3; i++) {
        if (FIELD(p, void *, 0x530 + i * 4) != NULL) {
            func_801B2FF8_ovl_0FA5E0(FIELD(p, void *, 0x530 + i * 4));
        }
    }
    for (j = 0; j < 18; j++) {
        HFree(FIELD(p, void *, 0x19C + j * 4));
    }
}

void func_801AEE94_ovl_0FA5E0(s32 i, void *v) {
    u8 *p = D_801B3E20_ovl_0FA5E0;

    p += i * 20;
    FIELD(p, s32, 0x214) = 0;
    FIELD(p, void *, 0x218) = v;
    FIELD(p, s16, 0x208) = 1;
}

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801AEEC0_ovl_0FA5E0);

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern s32 D_801B40F4_ovl_0FA5E0;
extern s32 D_801B4144_ovl_0FA5E0;

s32 func_801AFB94_ovl_0FA5E0(void) {
    s32 *var_v1;
    s32 *var_v1_2;
    f32 temp_ft0;
    f32 temp_ft0_2;
    f32 var_fv0;
    f32 var_fv0_2;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_v1_3;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_t0;
    s32 var_v0;
    s32 var_v0_2;
    u8 *temp_a3;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;
    void *temp_v1_2;

    var_t0 = 0;
    var_a0 = 0;
    var_v1 = &D_801B40F4_ovl_0FA5E0;
    temp_a3 = D_801B3E20_ovl_0FA5E0 + 0x1E4;
    temp_a1 = FIELD(D_801B3E20_ovl_0FA5E0, s32, 0x1E8);
loop_1:
    if ((temp_a1 < FIELD(var_v1, s32, 0)) || (var_v0 = var_a0 < 9, ((temp_a1 < FIELD(var_v1, s32, 8)) == 0))) {
        var_a0 += 1;
        var_v1 += 8;
        if (var_a0 >= 9) {
            var_v0 = var_a0 < 9;
        } else {
            goto loop_1;
        }
    }
    if (var_v0 != 0) {
        temp_v0 = (var_a0 * 8) + &D_801B40F4_ovl_0FA5E0;
        temp_v1 = ((var_a0 + 1) * 8) + &D_801B40F4_ovl_0FA5E0;
        temp_ft0 = FIELD(temp_v0, f32, 4);
        temp_a0 = FIELD(temp_v0, s32, 0);
        var_fv0 = (((FIELD(temp_v1, f32, 4) - temp_ft0) * (f32) (temp_a1 - temp_a0)) / (f32) (FIELD(temp_v1, s32, 0) - temp_a0)) + temp_ft0;
    } else {
        var_fv0 = FIELD(((var_a0 * 8) + &D_801B40F4_ovl_0FA5E0), f32, 4);
    }
    temp_a1_2 = FIELD(temp_a3, s32, 4);
    var_a0_2 = 0;
    var_v1_2 = &D_801B4144_ovl_0FA5E0;
    FIELD(temp_a3, f32, 0xC) = var_fv0;
loop_9:
    if ((temp_a1_2 < FIELD(var_v1_2, s32, 0)) || (var_v0_2 = var_a0_2 < 0xF, ((temp_a1_2 < FIELD(var_v1_2, s32, 8)) == 0))) {
        var_a0_2 += 1;
        var_v1_2 += 8;
        if (var_a0_2 >= 0xF) {
            var_v0_2 = var_a0_2 < 0xF;
        } else {
            goto loop_9;
        }
    }
    if (var_v0_2 != 0) {
        temp_v0_2 = (var_a0_2 * 8) + &D_801B4144_ovl_0FA5E0;
        temp_v1_2 = ((var_a0_2 + 1) * 8) + &D_801B4144_ovl_0FA5E0;
        temp_ft0_2 = FIELD(temp_v0_2, f32, 4);
        temp_a0_2 = FIELD(temp_v0_2, s32, 0);
        var_fv0_2 = (((FIELD(temp_v1_2, f32, 4) - temp_ft0_2) * (f32) (temp_a1_2 - temp_a0_2)) / (f32) (FIELD(temp_v1_2, s32, 0) - temp_a0_2)) + temp_ft0_2;
    } else {
        var_fv0_2 = FIELD(((var_a0_2 * 8) + &D_801B4144_ovl_0FA5E0), f32, 4);
    }
    temp_v1_3 = FIELD(temp_a3, s32, 4);
    FIELD(temp_a3, f32, 0x14) = var_fv0_2;
    if (temp_v1_3 < 0x1E) {
        FIELD(temp_a3, s32, 4) = (s32) (temp_v1_3 + 1);
    } else {
        var_t0 = 1;
    }
    return var_t0;
}
#else
INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801AFB94_ovl_0FA5E0);
#endif

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801AFD30_ovl_0FA5E0);

void func_801B01FC_ovl_0FA5E0(u8 *p) {
    FIELD(p, s16, 0x20) = 0xFF;
    FIELD(p, s16, 0x1E) = 0xFF;
    FIELD(p, s16, 0x18) = 0xFF;
    FIELD(p, s16, 0x1C) = 0;
    FIELD(p, s16, 0x1A) = 0;
}

void func_801B0218_ovl_0FA5E0(u8 *p, s16 a, s16 b, s16 c) {
    FIELD(p, s16, 0x1E) = b;
    FIELD(p, s16, 0x20) = c;
    FIELD(p, s16, 0x1C) = a;
    FIELD(p, s16, 0x1A) = 0;
}

/* Linear step: out = from + (to - from) * i / n, then i++; holds at `to` once i reaches n */
void func_801B022C_ovl_0FA5E0(u8 *p) {
    s32 pad;

    if (FIELD(p, u16, 0) != 0) {
        if (FIELD(p, s16, 0x1A) < FIELD(p, s16, 0x1C)) {
            FIELD(p, s16, 0x18) = FIELD(p, s16, 0x1E) + (FIELD(p, s16, 0x20) - FIELD(p, s16, 0x1E)) * FIELD(p, s16, 0x1A) / FIELD(p, s16, 0x1C);
            FIELD(p, s16, 0x1A)++;
        } else {
            FIELD(p, s16, 0x18) = FIELD(p, s16, 0x20);
        }
    }
}

typedef struct {
    /* 0x00 */ void *p0;
    /* 0x04 */ void *p1;
    /* 0x08 */ u8 (*mtx)[0x40];
} FbSetFA5;
extern FbSetFA5 *D_800E9BE0;
extern u16 D_800C4BE4;
void func_80098B60(f32 mf[4][4], f32 x, f32 y, f32 z); /* guScaleF */
void guMtxF2L(f32 mf[4][4], void *m);
void func_801AFD30_ovl_0FA5E0(void *a, s32 b, s32 c);

typedef struct {
    /* 0x00 */ u16 state;
    /* 0x02 */ u8 unk02[6];
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 y;
    /* 0x10 */ f32 z;
    /* 0x14 */ f32 scale;
    /* 0x18 */ s16 alpha;
} CursorFA5;

/* Draws the cursor model (D_801B3E20's model at 0x19C) at the object's position, scaled by
 * 0x14 and faded by its alpha */
#ifdef NON_MATCHING
/* 97/97 instructions, 6 words differ: v0/v1 swapped between the matrix command word and D_800E9BE0 */
void func_801B02C0_ovl_0FA5E0(CursorFA5 *o) {
    f32 mf[4][4];

    if (o->state != 0) {
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xE7000000;
            _g->w1 = 0;
        }
        if (o->alpha == 0xFF) {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xE200001C;
            _g->w1 = 0x0F0A4000;
        } else {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xE200001C;
            _g->w1 = 0x504340;
        }
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xFCFFFFFF;
            _g->w1 = 0xFFFCF67B;
        }
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xFA000000;
            _g->w1 = (u8)o->alpha;
        }
        func_80098B60(mf, o->scale, o->scale, o->scale);
        mf[3][0] = o->x;
        mf[3][1] = o->y;
        mf[3][2] = o->z;
        guMtxF2L(mf, D_800E9BE0->mtx[D_800C4BE4]);
        D_800E9BA0->w0 = 0xDA380003;
        D_800E9BA0->w1 = (u32)D_800E9BE0->mtx[D_800C4BE4];
        D_800C4BE4++;
        D_800E9BA0++;
        func_801AFD30_ovl_0FA5E0(((void **)D_801B3E20_ovl_0FA5E0)[0x67], 0, 0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B02C0_ovl_0FA5E0);
#endif

void func_801B0444_ovl_0FA5E0(Anim0444 *p, s32 a, f32 x, f32 y, u16 *src) {
    s32 i;

    for (i = 0; i < 4; i++) {
        p->f1C[i] = p->f2C[i] = src[i];
    }
    p->a = a;
    p->x = x;
    p->y = y;
    p->f1A = 0;
    p->f18 = 0;
    p->f34 = 0;
    p->f3C = 0;
    p->f38 = 0;
    p->f40 = 0;
    p->active = 1;
    p->f14 = 1.0f;
    p->f10 = 1.0f;
}

void func_801B04B8_ovl_0FA5E0(u16 *p) {
    if (*p == 1) {
        *p = 0;
    } else if (*p == 2) {
        *p = 0xFFFF;
    }
}

/* Two image buffers sized for the image at 0x4 (header copied into each), plus three parameters */
void func_801B04E4_ovl_0FA5E0(u8 *o, s32 a, s32 b, s32 c) {
    u8 *img = FIELD(o, u8 *, 4);
    s32 size;
    u32 i;

    size = FIELD(img, u16, 4) * FIELD(img, u16, 6) * D_801B4894_ovl_0FA5E0[img[3]];
    size /= 8;
    size += 8;
    for (i = 0; i < 2; i++) {
        ((u8 **)(o + 0x38))[i] = HMalloc(size);
        _bcopy(FIELD(o, u8 *, 4), ((u8 **)(o + 0x38))[i], 8);
    }
    FIELD(o, s32, 0x34) = 0;
    FIELD(o, s32, 0x40) = a;
    FIELD(o, s32, 0x44) = b;
    FIELD(o, s32, 0x48) = c;
    FIELD(o, u16, 0) = 2;
}

void func_801B05D0_ovl_0FA5E0(u8 *p, s16 a, u16 *x, u16 *y) {
    s32 i;

    for (i = 0; i < 4; i++) {
        FIELD(p, u16, 0x24 + i * 2) = *x++;
        FIELD(p, u16, 0x2C + i * 2) = *y++;
    }
    FIELD(p, s16, 0x18) = 0;
    FIELD(p, s16, 0x1A) = a;
}

/* Rectangle tween owned by a widget: state, step t of n, current/from/to (x, y, w, h) */
typedef struct {
    /* 0x00 */ u16 state;
    /* 0x02 */ u8 unk02[0x16];
    /* 0x18 */ s16 t;
    /* 0x1A */ s16 n;
    /* 0x1C */ s16 cur[4];
    /* 0x24 */ s16 from[4];
    /* 0x2C */ s16 to[4];
    /* 0x34 */ u8 unk34[4];
    /* 0x38 */ void *bufA;
    /* 0x3C */ void *bufB;
} TweenFA5;

/* Advances the tween one step; 0xFFFF/0xFFFE/0xFFFD count down to freeing its buffers */
void func_801B060C_ovl_0FA5E0(TweenFA5 *tw) {
    s32 i;

    switch (tw->state) {
        case 0xFFFF:
            tw->state = 0xFFFE;
            return;
        case 0xFFFE:
            tw->state = 0xFFFD;
            return;
        case 0xFFFD:
            HFree(tw->bufA);
            HFree(tw->bufB);
            tw->state = 0;
            return;
        case 0:
            return;
        default:
            if (tw->t < tw->n) {
                for (i = 0; i < 4; i++) {
                    tw->cur[i] = tw->from[i] + (tw->to[i] - tw->from[i]) * tw->t / tw->n;
                }
                tw->t++;
            } else {
                for (i = 0; i < 4; i++) {
                    tw->cur[i] = tw->to[i];
                }
            }
            break;
    }
}

/* Image: header then pixels at +8 */
typedef struct {
    /* 0x0 */ u8 unk0[3];
    /* 0x3 */ u8 fmt;
    /* 0x4 */ u16 w;
    /* 0x6 */ u16 h;
    /* 0x8 */ u8 pix[1];
} ImgFA5;
typedef struct {
    s16 lo;
    s16 hi;
} SpanFA5;
extern s32 D_801B48A4_ovl_0FA5E0[]; /* bits per pixel by format */

/* Clears dst, then copies the pixels of src inside the circle of radius r around (cx, cy) */
#ifdef NON_MATCHING
/* 159/159 instructions, 15 words differ: registers of the span clamp and copy loops */
void func_801B073C_ovl_0FA5E0(ImgFA5 *src, ImgFA5 *dst, s32 r, s32 cx, s32 cy) {
    SpanFA5 *spans;
    s32 x;
    s32 y;
    s32 d;
    s32 row;
    s32 i;
    s32 k;
    s32 size;

    size = src->w * src->h * D_801B48A4_ovl_0FA5E0[src->fmt];
    size /= 8;
    bzero(dst->pix, size);
    if (r != 0) {
        s32 size = src->h * 4;

        spans = HMalloc(size);
        bzero(spans, size);
        x = 0;
        y = r;
        d = 3 - y * 2;
        while (y >= x) {
            row = cy + y;
            if (row >= src->h) {
                row = src->h - 1;
            }
            spans[row].hi = cx + x;
            spans[row].lo = cx - x;
            row = cy - y;
            if (row < 0) {
                row = 0;
            }
            spans[row].hi = cx + x;
            spans[row].lo = cx - x;
            row = cy + x;
            if (row >= src->h) {
                row = src->h - 1;
            }
            spans[row].hi = cx + y;
            spans[row].lo = cx - y;
            row = cy - x;
            if (row < 0) {
                row = 0;
            }
            spans[row].hi = cx + y;
            spans[row].lo = cx - y;
            if (d < 0) {
                d = d + x * 4 + 6;
            } else {
                d = d + (x - y) * 4 + 10;
                y--;
            }
            x++;
        }
        for (i = 0; i < src->h; i++) {
            if (spans[i].lo < 0) {
                spans[i].lo = 0;
            }
            if (spans[i].hi >= src->w) {
                spans[i].hi = src->w - 1;
            }
        }
        {
            u8 *s = src->pix;
            u8 *t = dst->pix;

            for (i = 0; i < src->h; i++) {
                k = spans[i].lo;
                row = i * src->w + k;
                if (k <= spans[i].hi) {
                    u8 *p = t + row;
                    u8 *q = s + row;

                    do {
                        *p++ = *q++;
                        k++;
                    } while (k <= spans[i].hi);
                }
            }
        }
        HFree(spans);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B073C_ovl_0FA5E0);
#endif


/* Draws the tween's sprite at (x, y) scaled by (sx, sy) in colour cur[]; mode 2 flips between
 * its two buffers each frame */
void func_801B09B8_ovl_0FA5E0(TweenFA5 *tw) {
    f32 mf[4][4];

    switch (tw->state) {
        case 0:
        case 0xFFFD:
        case 0xFFFE:
        case 0xFFFF:
            return;
    }
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xE7000000;
        _g->w1 = 0;
    }
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xE200001C;
        _g->w1 = 0x4041C8;
    }
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xFC119623;
        _g->w1 = 0xFF2FFFFF;
    }
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xFA000000;
        _g->w1 = ((u8)tw->cur[0] << 24) | ((u8)tw->cur[1] << 16) | ((u8)tw->cur[2] << 8) | (u8)tw->cur[3];
    }
    func_80098B60(mf, FIELD(tw, f32, 0x10), FIELD(tw, f32, 0x14), 1.0f);
    mf[3][0] = FIELD(tw, f32, 8);
    mf[3][1] = FIELD(tw, f32, 0xC);
    mf[3][2] = 0.0f;
    guMtxF2L(mf, D_800E9BE0->mtx[D_800C4BE4]);
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xDA380000;
        _g->w1 = (u32)D_800E9BE0->mtx[D_800C4BE4++];
    }
    switch (tw->state) {
        case 1:
            func_801AFD30_ovl_0FA5E0(FIELD(tw, void *, 4), 0, 0);
            break;
        case 2:
            func_801B073C_ovl_0FA5E0(FIELD(tw, void *, 4), FIELD(tw, void *, 0x38 + FIELD(tw, s32, 0x34) * 4),
                                     FIELD(tw, s32, 0x40), FIELD(tw, s32, 0x44), FIELD(tw, s32, 0x48));
            func_801AFD30_ovl_0FA5E0(FIELD(tw, void *, 0x38 + FIELD(tw, s32, 0x34) * 4), 0, 0);
            FIELD(tw, s32, 0x34) ^= 1;
            break;
    }
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xD8380002;
        _g->w1 = 0x40;
    }
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xE7000000;
        _g->w1 = 0;
    }
}

void func_801B0C0C_ovl_0FA5E0(u8 *p, s32 a, s32 b, s32 c, u16 d) {
    FIELD(p, s32, 0xC) = a;
    FIELD(p, s32, 0x4) = b;
    FIELD(p, s32, 0x8) = c;
    FIELD(p, s16, 0x16) = 0;
    FIELD(p, s16, 0x14) = 0;
    FIELD(p, s16, 0x12) = 0;
    FIELD(p, s16, 0x0) = 1;
    FIELD(p, u16, 0x18) = d;
    FIELD(p, u16, 0x10) = d;
}

void func_801B0C3C_ovl_0FA5E0(u8 *p, s16 a, s16 b, s16 c) {
    FIELD(p, s16, 0x12) = 0;
    FIELD(p, s16, 0x14) = a;
    FIELD(p, s16, 0x16) = b;
    FIELD(p, s16, 0x18) = c;
}

void func_801B0C50_ovl_0FA5E0(u8 *p) {
    s32 pad;

    if (FIELD(p, u16, 0) != 0) {
        if (FIELD(p, s16, 0x12) < FIELD(p, s16, 0x14)) {
            FIELD(p, s16, 0x10) = FIELD(p, s16, 0x16) + (FIELD(p, s16, 0x18) - FIELD(p, s16, 0x16)) * FIELD(p, s16, 0x12) / FIELD(p, s16, 0x14);
            FIELD(p, s16, 0x12)++;
        } else {
            FIELD(p, s16, 0x10) = FIELD(p, s16, 0x18);
        }
    }
}

void func_80098D00(f32 mf[4][4], f32 x, f32 y, f32 z); /* guTranslateF */

typedef struct {
    /* 0x00 */ u16 state;
    /* 0x02 */ u8 unk02[2];
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ void *model;
    /* 0x10 */ s16 alpha;
} SpriteFA5;

/* Draws o's model at (x, y), faded by its alpha */
void func_801B0CE4_ovl_0FA5E0(SpriteFA5 *o) {
    f32 mf[4][4];

    if (o->state != 0) {
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xE7000000;
            _g->w1 = 0;
        }
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xE200001C;
            _g->w1 = 0x4041C8;
        }
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xFCFF97FF;
            _g->w1 = 0xFF2CFE7F;
        }
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xFA000000;
            _g->w1 = (u8)o->alpha;
        }
        func_80098D00(mf, o->x, o->y, 0.0f);
        guMtxF2L(mf, D_800E9BE0->mtx[D_800C4BE4]);
        D_800E9BA0->w0 = 0xDA380000;
        D_800E9BA0->w1 = (u32)D_800E9BE0->mtx[D_800C4BE4];
        D_800C4BE4++;
        D_800E9BA0++;
        func_801AFD30_ovl_0FA5E0(o->model, 0, 0);
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xD8380002;
            _g->w1 = 0x40;
        }
    }
}

void func_801B0E48_ovl_0FA5E0(u8 *p, s32 a, s32 b) {
    s32 pad[4];

    FIELD(p, s16, 0x14) = 0xFF;
    FIELD(p, s16, 0x12) = 0xFF;
    FIELD(p, s16, 0xC) = 0xFF;
    FIELD(p, u16, 0) = 1;
    FIELD(p, s32, 4) = a;
    FIELD(p, s32, 8) = b;
    FIELD(p, s16, 0x10) = 0;
    FIELD(p, s16, 0xE) = 0;
    FIELD(p, s16, 0x18) = 10;
    func_8009C7CC();
    func_8009C7CC();
    FIELD(p, s16, 0x16) = func_8009C7CC() & 0xF;
    FIELD(p, s16, 0x1A) = 0;
}

void func_801B0EB8_ovl_0FA5E0(u8 *p, s16 a, s16 b, s16 c) {
    FIELD(p, s16, 0xE) = 0;
    FIELD(p, s16, 0x10) = a;
    FIELD(p, s16, 0x12) = b;
    FIELD(p, s16, 0x14) = c;
}

void func_801B0ECC_ovl_0FA5E0(u8 *p) {
    s32 pad;

    if (FIELD(p, u16, 0) != 0) {
        if (FIELD(p, s16, 0xE) < FIELD(p, s16, 0x10)) {
            FIELD(p, s16, 0xC) = FIELD(p, s16, 0x12) + (FIELD(p, s16, 0x14) - FIELD(p, s16, 0x12)) * FIELD(p, s16, 0xE) / FIELD(p, s16, 0x10);
            FIELD(p, s16, 0xE)++;
        } else {
            FIELD(p, s16, 0xC) = FIELD(p, s16, 0x14);
        }
    }
}

typedef struct {
    /* 0x0 */ s16 kind;
    /* 0x2 */ u16 time;
} FrameFA5;
typedef struct {
    /* 0x0 */ FrameFA5 *frames;
    /* 0x4 */ s32 count;
} AnimFA5;
extern AnimFA5 D_801B4914_ovl_0FA5E0[];

/* Draws an animated sprite at (x, y): steps its frame timer, picking a random animation when one
 * ends, and draws the frame's model (D_801B3E20 + 0x1C0 + kind * 4) */
#ifdef NON_MATCHING
/* 188/188 instructions, 11 words differ: the matrix command's increments are scheduled before its w1 store, and the random pick ORs in the other operand order */
void func_801B0F60_ovl_0FA5E0(u8 *p) {
    f32 mf[4][4];
    void *m;

    if (FIELD(p, u16, 0) != 0) {
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xE7000000;
            _g->w1 = 0;
        }
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xE200001C;
            _g->w1 = 0x4041C8;
        }
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xFCFF97FF;
            _g->w1 = 0xFF2CFE7F;
        }
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xFA000000;
            _g->w1 = (u8)FIELD(p, s16, 0xC);
        }
        func_80098D00(mf, FIELD(p, f32, 4), FIELD(p, f32, 8), 0.0f);
        guMtxF2L(mf, D_800E9BE0->mtx[D_800C4BE4]);
        D_800E9BA0->w0 = 0xDA380000;
        D_800E9BA0->w1 = (u32)D_800E9BE0->mtx[D_800C4BE4];
        D_800E9BA0++;
        D_800C4BE4++;
        m = NULL;
        if (--FIELD(p, s16, 0x18) == 0) {
            if (++FIELD(p, s16, 0x1A) >= D_801B4914_ovl_0FA5E0[FIELD(p, s16, 0x16)].count) {
                u32 x = func_8009C7CC();
                u32 y = func_8009C7CC();
                u32 r = func_8009C7CC();

                r |= ((x << 18) & 0xC000000) | (y << 15);

                FIELD(p, s16, 0x16) = (r >> 23) & 0xF;
                FIELD(p, s16, 0x1A) = 0;
            }
            FIELD(p, u16, 0x18) = D_801B4914_ovl_0FA5E0[FIELD(p, s16, 0x16)].frames[FIELD(p, s16, 0x1A)].time;
        }
        switch (D_801B4914_ovl_0FA5E0[FIELD(p, s16, 0x16)].frames[FIELD(p, s16, 0x1A)].kind) {
        case 0:
            m = FIELD(D_801B3E20_ovl_0FA5E0, void *, 0x1C0);
            break;
        case 1:
            m = FIELD(D_801B3E20_ovl_0FA5E0, void *, 0x1C4);
            break;
        case 2:
            m = FIELD(D_801B3E20_ovl_0FA5E0, void *, 0x1C8);
            break;
        case 3:
            m = FIELD(D_801B3E20_ovl_0FA5E0, void *, 0x1CC);
            break;
        }
        func_801AFD30_ovl_0FA5E0(m, 0, 0);
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xD8380002;
            _g->w1 = 0x40;
        }
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xE7000000;
            _g->w1 = 0;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B0F60_ovl_0FA5E0);
#endif

void func_801B1250_ovl_0FA5E0(u8 *p, s32 a, s32 b) {
    FIELD(p, s16, 0x16) = 4;
    FIELD(p, s16, 0x14) = 0xFF;
    FIELD(p, s16, 0x12) = 0xFF;
    FIELD(p, s16, 0xC) = 0xFF;
    FIELD(p, s16, 0x18) = 0;
    FIELD(p, s16, 0x10) = 0;
    FIELD(p, s16, 0xE) = 0;
    FIELD(p, s32, 0x4) = a;
    FIELD(p, s32, 0x8) = b;
    FIELD(p, s16, 0x0) = 1;
}

void func_801B1288_ovl_0FA5E0(u8 *p, s16 a, s16 b, s16 c) {
    FIELD(p, s16, 0xE) = 0;
    FIELD(p, s16, 0x10) = a;
    FIELD(p, s16, 0x12) = b;
    FIELD(p, s16, 0x14) = c;
}

void func_801B129C_ovl_0FA5E0(u8 *p) {
    s32 pad;

    if (FIELD(p, u16, 0) != 0) {
        if (FIELD(p, s16, 0xE) < FIELD(p, s16, 0x10)) {
            FIELD(p, s16, 0xC) = FIELD(p, s16, 0x12) + (FIELD(p, s16, 0x14) - FIELD(p, s16, 0x12)) * FIELD(p, s16, 0xE) / FIELD(p, s16, 0x10);
            FIELD(p, s16, 0xE)++;
        } else {
            FIELD(p, s16, 0xC) = FIELD(p, s16, 0x14);
        }
    }
}

typedef struct {
    /* 0x0 */ s16 model; /* 0-4: D_801B3E20 model at 0x1D0 + model * 4 */
    /* 0x2 */ u16 frames;
    /* 0x4 */ s16 arg;
    /* 0x6 */ s16 dx;
} SparkFrameFA5;
extern SparkFrameFA5 D_801B4994_ovl_0FA5E0[7];

typedef struct {
    /* 0x00 */ u16 state;
    /* 0x02 */ u8 unk02[2];
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ u8 unk0C;
    /* 0x0D */ u8 alpha;
    /* 0x0E */ u8 unk0E[8];
    /* 0x16 */ s16 timer;
    /* 0x18 */ u16 frame;
} SparkFA5;
void func_80098D00(f32 mf[4][4], f32 x, f32 y, f32 z); /* guTranslateF */

/* Steps and draws an animated sprite through the 7-frame table D_801B4994 */
void func_801B1330_ovl_0FA5E0(SparkFA5 *o) {
    f32 mf[4][4];
    void *model;

    if (o->state != 0) {
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xE7000000;
            _g->w1 = 0;
        }
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xE200001C;
            _g->w1 = 0x4041C8;
        }
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xFCFF97FF;
            _g->w1 = 0xFF2CFE7F;
        }
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xFA000000;
            _g->w1 = o->alpha;
        }
        if (--o->timer == 0) {
            if (++o->frame >= 7) {
                o->frame = 0;
            }
            o->timer = D_801B4994_ovl_0FA5E0[(s16)o->frame].frames;
        }
        func_80098D00(mf, o->x + D_801B4994_ovl_0FA5E0[(s16)o->frame].dx, o->y, 0.0f);
        guMtxF2L(mf, D_800E9BE0->mtx[D_800C4BE4]);
        D_800E9BA0->w0 = 0xDA380000;
        D_800E9BA0->w1 = (u32)D_800E9BE0->mtx[D_800C4BE4++];
        D_800E9BA0++;
        switch (D_801B4994_ovl_0FA5E0[(s16)o->frame].model) {
            case 0:
                model = FIELD(D_801B3E20_ovl_0FA5E0, void *, 0x1D0);
                break;
            case 1:
                model = FIELD(D_801B3E20_ovl_0FA5E0, void *, 0x1D4);
                break;
            case 2:
                model = FIELD(D_801B3E20_ovl_0FA5E0, void *, 0x1D8);
                break;
            case 3:
                model = FIELD(D_801B3E20_ovl_0FA5E0, void *, 0x1DC);
                break;
            case 4:
                model = FIELD(D_801B3E20_ovl_0FA5E0, void *, 0x1E0);
                break;
            default:
                for (;;) {
                }
        }
        func_801AFD30_ovl_0FA5E0(model, D_801B4994_ovl_0FA5E0[(s16)o->frame].arg, 0);
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xD8380002;
            _g->w1 = 0x40;
        }
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xE7000000;
            _g->w1 = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B15BC_ovl_0FA5E0);

extern f64 D_801B4CA0_ovl_0FA5E0[]; /* knot spacing h[i] */
extern f64 D_801B4CF8_ovl_0FA5E0[]; /* d[i + 1]: slopes, then the eliminated diagonal */
#define SPL_H D_801B4CA0_ovl_0FA5E0
#define SPL_D(i) D_801B4CF8_ovl_0FA5E0[(i) - 1]

/* Solves for the second-derivative terms z[] of the natural spline through (x[i], y[i]), i < n */
void func_801B18AC_ovl_0FA5E0(f32 *x, f32 *y, f32 *z, s16 n) {
    s32 i;
    f64 t;

    z[0] = 0.0f;
    z[n - 1] = 0.0f;
    for (i = 0; i < n - 1; i++) {
        SPL_H[i] = x[i + 1] - x[i];
        SPL_D(i + 1) = (y[i + 1] - y[i]) / SPL_H[i];
    }
    z[1] = SPL_D(2) - SPL_D(1) - SPL_H[0] * z[0];
    SPL_D(1) = 2.0f * (x[2] - x[0]);
    for (i = 1; i < n - 2; i++) {
        t = SPL_H[i] / SPL_D(i);
        z[i + 1] = SPL_D(i + 2) - SPL_D(i + 1) - z[i] * t;
        SPL_D(i + 1) = 2.0f * (x[i + 2] - x[i]) - SPL_H[i] * t;
    }
    z[n - 2] -= SPL_H[n - 2] * z[n - 1];
    for (i = n - 2; i > 0; i--) {
        z[i] = (z[i] - SPL_H[i] * z[i + 1]) / SPL_D(i);
    }
}

/* Evaluates the piecewise cubic through knots t[] with values y[] and slopes m[] at x */
static inline f32 SplineFA5(f32 x, f32 *t, f32 *y, f32 *m, s16 n) {
    s32 lo = 0;
    s32 hi = n - 1;
    s32 mid;
    f32 d;
    f32 h;

    while (lo < hi) {
        mid = (lo + hi) / 2;
        if (t[mid] < x) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    lo -= lo > 0;
    d = x - t[lo];
    h = t[lo + 1] - t[lo];
    return ((((m[lo + 1] - m[lo]) * d) / h + m[lo] * 3.0f) * d +
            ((y[lo + 1] - y[lo]) / h - (2.0f * m[lo] + m[lo + 1]) * h)) * d + y[lo];
}

/* Evaluates two splines sharing the knots t[] at x */
void func_801B1AF0_ovl_0FA5E0(f32 x, f32 *outA, f32 *outB, f32 *t, f32 *yA, f32 *yB, f32 *mA, f32 *mB, s16 n) {
    *outA = SplineFA5(x, t, yA, mA, n);
    *outB = SplineFA5(x, t, yB, mB, n);
}

f32 sqrtf(f32 x);

/* Resamples the path (x[i], y[i]), i < n, at m evenly spaced points into outX/outY: a straight line
 * for two points, otherwise a spline over the normalised arc length */
void func_801B1CC0_ovl_0FA5E0(f32 *outX, f32 *outY, s16 m, s16 n, f32 *x, f32 *y) {
    s16 i;

    if (n == 2) {
        f32 dx = (x[1] - x[0]) / m;
        f32 dy = (y[1] - y[0]) / m;

        outX[0] = x[0];
        outY[0] = y[0];
        for (i = 1; i < m; i++) {
            outX[i] = outX[i - 1] + dx;
            outY[i] = outY[i - 1] + dy;
        }
    } else {
        f32 *t = HMalloc(n * 4);
        f32 *mx = HMalloc(n * 4);
        f32 *my = HMalloc(n * 4);
        s32 k;

        t[0] = 0.0f;
        for (k = 1; k < n; k++) {
            f32 dx = x[k] - x[k - 1];
            f32 dy = y[k] - y[k - 1];
            t[k] = t[k - 1] + sqrtf(dx * dx + dy * dy);
        }
        for (k = 1; k < n; k++) {
            t[k] /= t[n - 1];
        }
        func_801B18AC_ovl_0FA5E0(t, x, mx, n);
        func_801B18AC_ovl_0FA5E0(t, y, my, n);
        for (i = 0; i < m; i++, outX++, outY++) {
            func_801B1AF0_ovl_0FA5E0((1.0 / m) * i, outX, outY, t, x, y, mx, my, n);
        }
        HFree(t);
        HFree(mx);
        HFree(my);
    }
}

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B1FD8_ovl_0FA5E0);

#ifndef _SHIFTL
#define _SHIFTL(v, s, w) ((unsigned int)(((unsigned int)(v) & ((0x01 << (w)) - 1)) << (s)))
#endif
#define VTX_FA5(g, v, n, v0)                                                                   \
    {                                                                                          \
        Gfx *_g = (g)++;                                                                       \
        _g->w0 = _SHIFTL(0x01, 24, 8) | _SHIFTL((n), 12, 8) | _SHIFTL((v0) + (n), 1, 7);      \
        _g->w1 = (u32)(v);                                                                     \
    }
#define TRI2_FA5(g, a0, a1, a2, b0, b1, b2)                                                     \
    {                                                                                          \
        Gfx *_g = (g)++;                                                                       \
        _g->w0 = _SHIFTL(0x06, 24, 8) | (_SHIFTL((a0) * 2, 16, 8) | _SHIFTL((a1) * 2, 8, 8) | _SHIFTL((a2) * 2, 0, 8)); \
        _g->w1 = _SHIFTL((b0) * 2, 16, 8) | _SHIFTL((b1) * 2, 8, 8) | _SHIFTL((b2) * 2, 0, 8); \
    }

/* Emits the triangle strip of vertex buffer k: batches of 30 vertices (14 quads, sharing an edge
 * with the next batch), then the remainder */
#ifdef NON_MATCHING
/* 123/124 instructions: the original copies the remainder count n into another register for the last loop */
void func_801B2664_ovl_0FA5E0(u8 *m, Gfx **pg, s32 k) {
    u8 *v = ((u8 **)m)[k];
    Gfx *g = *pg;
    s32 j;
    s32 i;
    s32 n;

    for (j = 0; j < FIELD(m, s32, 0x58) / 14; j++) {
        VTX_FA5(g, v, 30, 0);
        for (i = 0; i < 28; i += 2) {
            TRI2_FA5(g, i, i + 2, i + 3, i, i + 3, i + 1);
        }
        v += 28 * 16;
    }
    n = FIELD(m, s32, 0x58) % 14 * 2;
    VTX_FA5(g, v, n + 2, 0);
    for (i = 0; i < n; i += 2) {
        TRI2_FA5(g, i, i + 2, i + 3, i, i + 3, i + 1);
    }
    *pg = g;
}
#else
INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B2664_ovl_0FA5E0);
#endif

INCLUDE_RODATA("asm/nonmatchings/FA5E0", D_801B4C78_ovl_0FA5E0);

INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B2854_ovl_0FA5E0);

void func_801B2CC0_ovl_0FA5E0(u8 *p, s16 a, u16 *x, u16 *y) {
    s32 i;

    for (i = 0; i < 4; i++) {
        FIELD(p, u16, 0x94 + i * 2) = *x++;
        FIELD(p, u16, 0x9C + i * 2) = *y++;
    }
    FIELD(p, s16, 0x88) = 0;
    FIELD(p, s16, 0x8A) = a;
}

/* Steps the 4 values at 0x8C from 0x94 toward 0x9C over 0x8A frames (counter at 0x88) */
void func_801B2CFC_ovl_0FA5E0(u8 *o) {
    u32 i;

    if (FIELD(o, s16, 0x88) < FIELD(o, s16, 0x8A)) {
        for (i = 0; i < 4; i++) {
            ((s16 *)(o + 0x8C))[i] = ((s16 *)(o + 0x94))[i] +
                (((s16 *)(o + 0x9C))[i] - ((s16 *)(o + 0x94))[i]) * FIELD(o, s16, 0x88) / FIELD(o, s16, 0x8A);
        }
        FIELD(o, s16, 0x88)++;
    } else {
        for (i = 0; i < 4; i++) {
            ((s16 *)(o + 0x8C))[i] = ((s16 *)(o + 0x9C))[i];
        }
    }
}

typedef struct { s32 m[16]; } MtxFA5;
extern u8 D_801B49D0_ovl_0FA5E0[];
void func_80098AA0(void *m, f32 x, f32 y, f32 z);
void func_801B2854_ovl_0FA5E0(u8 *m, s32 k);

/* Draws vertex buffer k: copies the colours from the source buffer, ramps the alpha along the
 * strip, then emits it at half scale with the model's prim colour */
#ifdef NON_MATCHING
/* 141/141 instructions, 13 words differ: the alpha-ramp loop's counter and pointer land in different registers */
void func_801B2DBC_ovl_0FA5E0(u8 *m, Gfx **pg, MtxFA5 **pmtx, s32 k) {
    u8 *v = ((u8 **)m)[k];
    u8 *src = FIELD(m, u8 *, 8);
    Gfx *g = *pg;
    MtxFA5 *mtx = *pmtx;
    u8 *end = v + FIELD(m, s32, 0x68) * 16;
    s32 i;
    u8 *p;
    s32 n;

    if (FIELD(m, u8, 0x85) != 0) {
    loop1:
        if (v < end) {
            u8 c;
            for (c = 0; c < 4; c++) {
                v[c + 0xC] = src[c + 0xC];
            }
            v += 0x20;
            src += 0x20;
            goto loop1;
        }
    }
    func_801B2854_ovl_0FA5E0(m, k);
    i = 0;
    n = FIELD(m, s32, 0x68);
    v = ((u8 **)m)[k];
    end = v + n * 16;
    if (FIELD(m, u8, 0x85) != 0) {
        p = &v[0xF];
        end = &end[0xF];
    loop2:
        if (p < end) {
            s32 a = *p * i / n;
            if (a < 0) {
                a = 0;
            }
            if (a >= 0x100) {
                a = 0xFF;
            }
            *p = a;
            p += 0x10;
            *p = a;
            p += 0x10;
            i += 2;
            goto loop2;
        }
    }
    func_80098AA0(mtx, 0.5f, 0.5f, 0.5f);
    {
        Gfx *_g = g++;
        _g->w0 = 0xDA380000;
        _g->w1 = (u32)mtx++;
    }
    {
        Gfx *_g = g++;
        _g->w0 = 0xDE000000;
        _g->w1 = (u32)D_801B49D0_ovl_0FA5E0;
    }
    {
        Gfx *_g = g++;
        _g->w0 = 0xFA000000;
        _g->w1 = (FIELD(m, u8, 0x8D) << 24) | (FIELD(m, u8, 0x8F) << 16) | (FIELD(m, u8, 0x91) << 8) | FIELD(m, u8, 0x93);
    }
    func_801B2664_ovl_0FA5E0(m, &g, k);
    {
        Gfx *_g = g++;
        _g->w0 = 0xD8380002;
        _g->w1 = 0x40;
    }
    *pg = g;
    *pmtx = mtx;
}
#else
INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B2DBC_ovl_0FA5E0);
#endif

void func_801B2FF8_ovl_0FA5E0(void **p) {
    HFree(p[0]);
    HFree(p[1]);
    HFree(p[2]);
    HFree(p);
}

void func_801B3038_ovl_0FA5E0(u8 *p, s32 v) {
    FIELD(p, s32, 0x50) = v;
}

/* Ribbon: a spline strip drawn through up to n control points */
typedef struct {
    /* 0x00 */ u8 unk00[0x50];
    /* 0x50 */ s32 percent;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 count;
    /* 0x5C */ u8 unk5C[0xC];
    /* 0x68 */ s32 shown;
    /* 0x6C */ u16 unk6C;
    /* 0x6E */ s16 x0;
    /* 0x70 */ s16 y0;
    /* 0x72 */ s16 x1;
    /* 0x74 */ s16 y1;
    /* 0x76 */ u8 unk76[0xE];
    /* 0x84 */ u8 width;
    /* 0x85 */ u8 fade;
    /* 0x86 */ u8 growing;
    /* 0x87 */ u8 unk87;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u16 color[8];
    /* 0x9C */ u16 color2[4];
} RibbonFA5; /* size 0xA4 */

typedef struct { s16 v[5]; } RibbonStepsFA5;
extern RibbonStepsFA5 D_801B4C78_ovl_0FA5E0;
void func_801B1FD8_ovl_0FA5E0(f32 *x, f32 *y, s32 n, RibbonFA5 *r, s32 w, s32 b);

/* Creates a ribbon through the n points (x[i], y[i]) */
#ifdef NON_MATCHING
/* 134/134 instructions, 7 words differ: the colour-copy loop counter and pointer sit one register over */
RibbonFA5 *func_801B3040_ovl_0FA5E0(f32 *x, f32 *y, s32 n, s32 percent, s32 width, s32 grow, s32 fade, u16 arg7,
                                    u16 *color) {
    RibbonFA5 *r = HMalloc(sizeof(RibbonFA5));
    u32 i;

    bzero(r, sizeof(RibbonFA5));
    r->x0 = x[0];
    r->y0 = y[0];
    r->x1 = x[n - 1];
    r->y1 = y[n - 1];
    r->unk54 = -1;
    r->width = width;
    r->fade = fade;
    r->percent = percent;
    r->growing = 1;
    r->unk6C = arg7;
    r->unk8A = 0;
    r->unk88 = 0;
    for (i = 0; i < 4; i++) {
        r->color[i] = color[i];
        r->color2[i] = color[i];
    }
    func_801B1FD8_ovl_0FA5E0(x, y, n, r, width + 3, 1);
    if (grow == 0) {
        r->shown = 5;
    } else {
        s32 lim = r->count * 2;
        s32 lim2;
        RibbonStepsFA5 steps = D_801B4C78_ovl_0FA5E0;

        r->shown = 0;
        lim2 = lim - 2;
        lim2 = lim2 * r->percent / 100;
        while (1) {
            if ((r->shown + steps.v[width - 1]) * 2 >= lim2) {
                break;
            }
            r->shown += 2;
        }
        r->growing = 0;
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/FA5E0", func_801B3040_ovl_0FA5E0);
#endif

s32 func_801B3258_ovl_0FA5E0(void) {
    u8 *q = D_801B3E20_ovl_0FA5E0;
    s32 r = 0;

    if (FIELD(q, u16, 0x444) && FIELD(q, u16, 0x460)) {
        r = FIELD(q, u16, 0x47C) != 0;
    }
    return r;
}

s32 func_801B3288_ovl_0FA5E0(void) {
    u8 *q = D_801B3E20_ovl_0FA5E0;
    s32 r = 0;

    if (FIELD(q, s32, 0x298) < 130) {
        FIELD(q, s32, 0x298)++;
    } else {
        r = 1;
    }
    return r;
}

s32 func_801B32B8_ovl_0FA5E0(void) {
    u8 *p = D_801B3E20_ovl_0FA5E0;
    s32 r = 0;

    if (FIELD(p, s32, 0x2E4) < 120) {
        FIELD(p, s32, 0x2E4) += 2;
    } else {
        r = 1;
    }
    return r;
}

s32 func_801B32E8_ovl_0FA5E0(void) {
    u8 *p = D_801B3E20_ovl_0FA5E0;

    func_801B01FC_ovl_0FA5E0(p + 0x1E4);
    FIELD(p, s16, 0x1E4) = 1;
    FIELD(p, s32, 0x1F8) = 0;
    FIELD(p, s32, 0x1EC) = 0;
    FIELD(p, s32, 0x1F4) = 0;
    FIELD(p, s32, 0x1E8) = 0;
    FIELD(p, f32, 0x1F0) = 15.0f;
    return 1;
}

s32 func_801B333C_ovl_0FA5E0(void) {
    return FIELD(D_801B3E20_ovl_0FA5E0, s16, 0x4CC) == 0;
}

s32 func_801B3350_ovl_0FA5E0(void) {
    return FIELD(D_801B3E20_ovl_0FA5E0, s16, 0x4CC) != 0;
}

s32 func_801B3364_ovl_0FA5E0(void) {
    return FIELD(D_801B3E20_ovl_0FA5E0, s16, 0x4E8) == 0;
}

s32 func_801B3378_ovl_0FA5E0(void) {
    return FIELD(D_801B3E20_ovl_0FA5E0, s16, 0x4E8) != 0;
}

INCLUDE_RODATA("asm/nonmatchings/FA5E0", D_801B4C90_ovl_0FA5E0);
