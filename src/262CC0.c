#include "common.h"
#include "heap.h"

/* 262CC0 */

typedef struct {
    /* 0x00 */ u16 next;
    /* 0x02 */ u8 unk02[2];
    /* 0x04 */ s32 w4;
    /* 0x08 */ s32 w8;
    /* 0x0C */ s32 wC;
    /* 0x10 */ s16 h10;
    /* 0x12 */ u8 unk12[0x66];
} Blk78; /* size 0x78 */

extern u16 D_80220DA0_ovl_25EE90;
extern Blk78 *D_80220DA8_ovl_25EE90;
extern void *D_80220DAC_ovl_25EE90;

extern s32 D_80220DA4_ovl_25EE90;
void func_801B55C4(void);
void func_8020E224_ovl_25EE90(u16 layer);
typedef struct {
    u32 w0;
    u32 w1;
} Gfx;
typedef struct {
    s32 m[16];
} Mtx40;
extern Gfx *D_800E9BA0;
extern Mtx40 *D_801969B0;
void guOrtho(Mtx40 *m, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, f32 scale);
void func_800987E0(Mtx40 *m);
/* --- end decls --- */

/* Pool of 256 blocks chained through `next`, plus a pointer table */
void func_8020E110_ovl_25EE90(void) {
    Blk78 *p;
    s32 i;

    D_80220DA4_ovl_25EE90 = 0x100;
    p = HMalloc(0x7800);
    D_80220DA8_ovl_25EE90 = p;
    for (i = 0; i < D_80220DA4_ovl_25EE90; i++) {
        p[i].w4 = 0;
        p[i].wC = 0;
    }
    D_80220DAC_ovl_25EE90 = HMalloc(D_80220DA4_ovl_25EE90 * 4);
    D_80220DA0_ovl_25EE90 = 0;
    for (i = 0; i < D_80220DA4_ovl_25EE90 - 1; i++) {
        D_80220DA8_ovl_25EE90[i].next = i + 1;
    }
    D_80220DA8_ovl_25EE90[i].next = 0xFFFF;
}

void func_8020E1F4_ovl_25EE90(void) {
    HFree(D_80220DA8_ovl_25EE90);
    HFree(D_80220DAC_ovl_25EE90);
}

#define LIST262 ((Blk78 **)D_80220DAC_ovl_25EE90)

/* Runs the active type-1 blocks of layer `layer` in priority order (w8 ascending; sorted by a
 * two-ended selection sort into the scratch list D_80220DAC) */
#ifdef NON_MATCHING
/* 96 vs 93 instructions: block scan loop setup and the sort's pointer induction variables differ; priorities compare as floats */
void func_8020E224_ovl_25EE90(u16 layer) {
    s32 n = 0;
    s32 i;

    if (D_80220DA4_ovl_25EE90 > 0) {
        Blk78 *b = D_80220DA8_ovl_25EE90;
        Blk78 **list = LIST262;

        i = 0;
        do {
            if (b->w4 != 0 && b->wC == 1 && (u16)b->h10 == layer) {
                *list++ = b;
                n++;
            }
            i++;
            b++;
        } while (i < D_80220DA4_ovl_25EE90);
    }
    if (n > 0) {
        s32 hi = n - 1;
        s32 lo;
        s32 j;

        for (lo = 0; lo < hi; lo++, hi--) {
            for (j = lo; j <= hi; j++) {
                Blk78 *a = LIST262[j];
                Blk78 *c = LIST262[lo];

                if (*(f32 *)&a->w8 < *(f32 *)&c->w8) {
                    LIST262[lo] = a;
                    LIST262[j] = c;
                }
                c = LIST262[hi];
                if (*(f32 *)&c->w8 < *(f32 *)&LIST262[j]->w8) {
                    LIST262[hi] = LIST262[j];
                    LIST262[j] = c;
                }
            }
        }
        for (i = 0; i < n; i++) {
            ((void (*)(Blk78 *))LIST262[i]->w4)(LIST262[i]);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/262CC0", func_8020E224_ovl_25EE90);
#endif

/* 2D pass: orthographic 320x240 projection and identity model view, then draws the blocks of layer a */
void func_8020E3A0_ovl_25EE90(u16 a) {
    Gfx *g;

    g = D_800E9BA0++;
    g->w0 = 0xE7000000;
    g->w1 = 0;
    guOrtho(D_801969B0, -160.0f, 160.0f, -120.0f, 120.0f, -500.0f, 2000.0f, 1.0f);
    func_800987E0(D_801969B0 + 1);
    g = D_800E9BA0++;
    g->w0 = 0xDA380007;
    g->w1 = (u32)D_801969B0++;
    g = D_800E9BA0++;
    g->w0 = 0xDA380003;
    g->w1 = (u32)D_801969B0++;
    func_8020E224_ovl_25EE90(a);
}

void func_8020E4A0_ovl_25EE90(void) {
    func_801B55C4();
    func_8020E224_ovl_25EE90(0);
}

/* Takes a block from the free list (hangs when empty) */
inline Blk78 *func_8020E4C4_ovl_25EE90(void) {
    Blk78 *b;

    if (D_80220DA0_ovl_25EE90 != 0xFFFF) {
        b = &D_80220DA8_ovl_25EE90[D_80220DA0_ovl_25EE90];
        D_80220DA0_ovl_25EE90 = b->next;
    } else {
        for (;;) {
        }
    }
    b->h10 = 2;
    b->wC = 0;
    b->w8 = 0;
    return b;
}

void func_8020E51C_ovl_25EE90(Blk78 *b) {
    if (b != NULL) {
        b->w4 = 0;
        b->next = D_80220DA0_ovl_25EE90;
        D_80220DA0_ovl_25EE90 = b - D_80220DA8_ovl_25EE90;
    }
}

Blk78 *func_8020E570_ovl_25EE90(s32 a, s16 c) {
    Blk78 *b;

    if (D_80220DA0_ovl_25EE90 != 0xFFFF) {
        b = &D_80220DA8_ovl_25EE90[D_80220DA0_ovl_25EE90];
        D_80220DA0_ovl_25EE90 = b->next;
    } else {
        for (;;) {
        }
    }
    b->wC = 0;
    b->h10 = 2;
    b->w8 = 0;
    if (b != NULL) {
        b->w4 = a;
        b->wC = 1;
        b->h10 = c;
    }
    return b;
}
