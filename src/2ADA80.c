#include "common.h"

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

typedef struct {
    /* 0x00 */ u8 unk00[0x33];
    /* 0x33 */ u8 unk33;
    /* 0x34 */ u8 unk34[2];
    /* 0x36 */ u16 items[4];
} Recruit;

extern u8 *D_8022A974;
extern void *D_801CE8BC;
extern s32 D_801CEAB0;
extern u8 *D_801D06F4; /* colour pairs: from rgb, to rgb */
extern Gfx *D_800E9BA0;
typedef struct {
    /* 0x00 */ u8 cls;
    /* 0x01 */ u8 baseCls;
    /* 0x02 */ u8 unk02[0x36];
} PlayerClass; /* player character records (0x38 bytes) seen from their class field */

extern PlayerClass D_80193BD1[];

void *HMalloc(s32 size);
void *HFree(void *p);
void func_801B0020(void);
void func_801BBC78(void);
void func_801BE894(void);
void func_801C1A9C(void);
void func_801C1D98(void);
void func_801C234C(void);
void func_801C5D64(void);
void func_801CA3E0(Recruit *r);
u8 func_8016FF5C(u8 cls, u8 want);
u16 func_8016DF88(u8 cls, u8 base);
u16 func_8016DFDC(u8 cls, u8 base);
u16 func_8016E030(u8 cls, u8 base);
u16 func_8016E084(u8 cls, u8 base);

/* Allocates the {limit, count} counter at ctx+0x1CAC */
void func_8023E320_ovl_2A8D20(void) {
    s16 *counter = HMalloc(4);

    FIELD(D_8022A974, s16 *, 0x1CAC) = counter;
    counter[0] = 60;
    counter[1] = 0;
}

void func_8023E354_ovl_2A8D20(void) {
    s16 *counter;

    if (D_8022A974 != NULL) {
        counter = FIELD(D_8022A974, s16 *, 0x1CAC);
        if (counter != NULL && counter[1] < counter[0]) {
            counter[1]++;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/2ADA80", func_8023E394_ovl_2A8D20);

void func_8023E7D0_ovl_2A8D20(void) {
    if (D_801CE8BC != NULL) {
        func_801BE894();
        func_801BBC78();
        func_801C5D64();
        func_801B0020();
        func_801C1D98();
        func_801C1A9C();
        func_801C234C();
        HFree(D_801CE8BC);
        D_801CE8BC = NULL;
    }
}

/* Sets the environment colour from the object's height (fades between two colours) */
void func_8023E83C_ovl_2A8D20(u8 *obj) {
    f32 y = FIELD(obj, f32, 0x11C) + 152.0f + FIELD(obj, f32, 0x124) + 38.0f;
    u8 *col = &D_801D06F4[D_801CEAB0 * 6];
    f32 t;
    f32 r;
    f32 g;
    f32 b;
    Gfx *gfx;

    if (y < 0.0f) {
        y = 0.0f;
    } else if (380.0f < y) {
        y = 380.0f;
    }
    t = 380.0f - y;
    r = t * (col[3] - (f32)col[0]) / 380.0f + col[0];
    g = t * (col[4] - (f32)col[1]) / 380.0f + col[1];
    b = t * (col[5] - (f32)col[2]) / 380.0f + col[2];
    gfx = D_800E9BA0++;
    gfx->w0 = 0xFB000000;
    gfx->w1 = ((u32)r << 24) | (((u32)g & 0xFF) << 16) | (((u32)b & 0xFF) << 8) | 1;
}

/* Fills the recruit's empty item slots with the defaults of the first character of class want */
#ifdef NON_MATCHING
/* The original keeps the post-loop index in a1 (so the found-branch uses beql). */
s32 func_8023EA44_ovl_2A8D20(u8 want, Recruit *r) {
    u8 i;
    u8 cls;
    u8 base;

    for (i = 0; i < 100; i++) {
        if (func_8016FF5C(D_80193BD1[i].cls, want) == 1) {
            break;
        }
    }
    if (i >= 100) {
        return 1;
    }
    cls = D_80193BD1[i].cls;
    base = D_80193BD1[i].baseCls;
    func_801CA3E0(r);
    if (r->items[0] == 0) {
        r->items[0] = func_8016DF88(cls, base);
    }
    if (r->items[1] == 0) {
        r->items[1] = func_8016DFDC(cls, base);
    }
    if (r->items[2] == 0) {
        r->items[2] = func_8016E030(cls, base);
    }
    if (r->items[3] == 0) {
        r->items[3] = func_8016E084(cls, base);
    }
    if (r->items[0] == 0xE9) {
        r->items[0] += r->unk33;
    }
    if (r->items[1] == 0xE9) {
        r->items[1] += r->unk33;
    }
    if (r->items[2] == 0xE9) {
        r->items[2] += r->unk33;
    }
    if (r->items[3] == 0xE9) {
        r->items[3] += r->unk33;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/2ADA80", func_8023EA44_ovl_2A8D20);
#endif
