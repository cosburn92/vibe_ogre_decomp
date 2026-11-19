#include "common.h"

/* 23D090 */

/* 16 zero bytes (shared rodata splat leaves unmigrated) */
__asm__(".section .rodata\n.global D_801F0490_ovl_23B220\nD_801F0490_ovl_23B220:\n.word 0, 0, 0, 0\n.section .text\n");

typedef struct {
    /* 0x00 */ u8 unk00[0x60];
    /* 0x60 */ u16 flags;
    /* 0x62 */ u8 unk62[4];
    /* 0x66 */ s16 id;
} Ent23; /* size 0x68 */

typedef struct {
    /* 0x000 */ Ent23 ent[4];
    /* 0x1A0 */ u8 unk1A0[0x1D0];
    /* 0x370 */ s16 x0;
    /* 0x372 */ s16 x1;
    /* 0x374 */ s16 y0;
    /* 0x376 */ s16 y1;
    /* 0x378 */ u8 unk378[0x2D8];
    /* 0x650 */ u16 flags;
    /* 0x652 */ s16 h652;
    /* 0x654 */ u8 unk654[2];
    /* 0x656 */ s16 fade;
} Ctx23;

extern Ctx23 *D_801EFE48_ovl_23B220;
extern u8 D_801CEAAB;

void func_801E98B4_ovl_23B220(s16 id);
void func_801EADF8_ovl_23B220(void);
#include "libultra.h"
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern Gfx *D_800E9BA0;
extern Gfx D_801F0028_ovl_23B220[];
extern Gfx D_801F01D0_ovl_23B220[];
void func_801B5CAC(s32 a, s32 b, s32 c);
void func_801EAAD8_ovl_23B220(void);
void func_801EAFC8_ovl_23B220(void);
void func_801EB594_ovl_23B220(void);
void func_801EBDD8_ovl_23B220(void);
void func_801EC00C_ovl_23B220(void);
void func_801ECAB0_ovl_23B220(void);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/23D090", func_801E8E20_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801E8F90_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801E9130_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801E92D4_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801E9618_ovl_23B220);

void func_801E9834_ovl_23B220(void) {
    Ctx23 *s = D_801EFE48_ovl_23B220;
    Gfx *g;

    if (s->flags & 1) {
        g = D_800E9BA0++;
        g->w0 = 0xDE000000;
        g->w1 = (u32)D_801F0028_ovl_23B220;
        func_801B5CAC(FIELD(s, s32, 0x1A0), 0, 0);
        g = D_800E9BA0++;
        g->w0 = 0xE7000000;
        g->w1 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/23D090", func_801E98B4_ovl_23B220);

void func_801E99FC_ovl_23B220(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        func_801E98B4_ovl_23B220(D_801EFE48_ovl_23B220->ent[i].id);
    }
}

INCLUDE_ASM("asm/nonmatchings/23D090", func_801E9A50_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801E9DFC_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EA158_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EA224_ovl_23B220);

#ifdef NON_MATCHING
/* branch layout of the id test differs */
void func_801EA404_ovl_23B220(void) {
    Ctx23 *s = D_801EFE48_ovl_23B220;
    s32 i;
    s32 m = ~0x10;

    for (i = 0; i < 4; i++) {
        if (FIELD(s, u16, 0x23C) & 1) {
            if (s->ent[i].id == 0 || s->ent[i].id == 3) {
                goto set;
            }
        } else if ((u16)(s->ent[i].id - 1) < 2) {
        set:
            if (s->ent[i].flags & 0x10) {
                s->ent[i].flags = (s->ent[i].flags & m) | 0x20;
            }
        }
    }
    FIELD(s, u16, 0x23C)++;
}
#else
INCLUDE_ASM("asm/nonmatchings/23D090", func_801EA404_ovl_23B220);
#endif

/* Whether all four entries have flag 0x10 */
s32 func_801EA498_ovl_23B220(void) {
    s32 n = 0;
    s32 i;
    Ent23 *e = D_801EFE48_ovl_23B220->ent;

    for (i = 0; i < 4; i++) {
        if (e[i].flags & 0x10) {
            n++;
        }
    }
    return n == 4;
}

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EA4D4_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EA770_ovl_23B220);

#ifdef NON_MATCHING
/* The constant 20 is loaded once into a0 in the target. */
void func_801EA990_ovl_23B220(void) {
    Ctx23 *c = D_801EFE48_ovl_23B220;

    c->y1 = 0xA2;
    c->y0 = 0x14;
    c->x0 = 0x14;
    c->x1 = 0xF2;
    c->h652 = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/23D090", func_801EA990_ovl_23B220);
#endif

/* Closes the panel by 8 px a frame and fades out; 1 when the fade completes */
#ifdef NON_MATCHING
/* same as func_801EAA58 */
s32 func_801EA9BC_ovl_23B220(void) {
    Ctx23 *s = D_801EFE48_ovl_23B220;
    s32 step = 25;
    s16 *f = &s->h652;

    if (s->x1 >= s->y1) {
        s->x1 -= 8;
        if (s->x1 <= s->y1) {
            s->x1 = s->y1;
            s->y1 = 0xF2;
        }
    }
    if (*f != 0xFF) {
        *f += step;
        if (*f < 0xFF) {
            return 0;
        }
        *f = 0xFF;
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/23D090", func_801EA9BC_ovl_23B220);
#endif

/* Opens the panel by 8 px a frame and fades in; 1 when the fade completes */
static inline s32 fade23(s16 *f, s32 step) {
    if (*f != 0) {
        *f -= step;
        if (*f > 0) {
            return 0;
        }
        *f = 0;
        return 1;
    }
    return 0;
}
static inline void open23(Ctx23 *s) {
    if (s->x1 != s->y1) {
        s->x1 += 8;
        if (s->x1 >= s->y1) {
            s->x1 = s->y1;
        }
    }
}
#ifdef NON_MATCHING
/* step 25 kept in a3 (unpropagated constant, likely an inlined helper arg); 0x18 frame */
s32 func_801EAA58_ovl_23B220(void) {
    Ctx23 *s = D_801EFE48_ovl_23B220;
    s32 step = 25;
    s16 *f = &s->h652;

    open23(s);
    return fade23(f, step);
}
#else
INCLUDE_ASM("asm/nonmatchings/23D090", func_801EAA58_ovl_23B220);
#endif

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EAAD8_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EADF8_ovl_23B220);

void func_801EAF9C_ovl_23B220(void) {
    D_801EFE48_ovl_23B220->flags |= 0x10;
}

s32 func_801EAFB4_ovl_23B220(void) {
    return D_801EFE48_ovl_23B220->flags & 0x20;
}

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EAFC8_ovl_23B220);

void func_801EB394_ovl_23B220(void) {
    if (D_801EFE48_ovl_23B220->flags & 0x10) {
        func_801EADF8_ovl_23B220();
    }
}

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EB3C8_ovl_23B220);

void func_801EB4F0_ovl_23B220(void) {
    D_801EFE48_ovl_23B220->flags |= 4;
}

#ifdef NON_MATCHING
/* display-list pointer store is scheduled after the argument loads */
void func_801EB508_ovl_23B220(void) {
    Ctx23 *s = D_801EFE48_ovl_23B220;
    Gfx *g;

    if (s->flags & 4) {
        g = D_800E9BA0;
        g->w0 = 0xDE000000;
        g->w1 = (u32)D_801F01D0_ovl_23B220;
        D_800E9BA0 = g + 1;
        func_801B5CAC(FIELD(s, s32, 0x36C), s->x0, s->x1);
        g = D_800E9BA0++;
        g->w0 = 0xE7000000;
        g->w1 = 0;
        func_801EAAD8_ovl_23B220();
        func_801EAFC8_ovl_23B220();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/23D090", func_801EB508_ovl_23B220);
#endif

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EB594_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EB6C8_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EB968_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EBB5C_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EBCFC_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EBDD8_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EBF58_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EC00C_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EC4B0_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EC6F4_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801ECAB0_ovl_23B220);

void func_801ECC40_ovl_23B220(void) {
    D_801EFE48_ovl_23B220->flags |= 2;
}

void func_801ECC58_ovl_23B220(void) {
    s32 i;
    u8 *o;

    if (D_801EFE48_ovl_23B220->flags & 2) {
        func_801EB594_ovl_23B220();
        for (i = 0; i < 7; i++) {
            o = (u8 *)D_801EFE48_ovl_23B220 + 0x378 + i * 0x54;
            (*(void (**)(u8 *))o)(o);
        }
        func_801EBDD8_ovl_23B220();
        func_801EC00C_ovl_23B220();
        func_801ECAB0_ovl_23B220();
    }
}

/* Fade-out step; returns 1 when done */
#ifdef NON_MATCHING
/* Branch layout of the done path differs. */
s32 func_801ECCE0_ovl_23B220(void) {
    Ctx23 *c = D_801EFE48_ovl_23B220;
    s32 r;
    s16 v = c->fade - 8;

    c->fade = v;
    if (v > 0) {
        r = 0;
        D_801CEAAB = v;
    } else {
        r = 1;
        D_801CEAAB = 0;
        c->fade = 0;
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/23D090", func_801ECCE0_ovl_23B220);
#endif

/* Fade-in step; returns 1 when done */
#ifdef NON_MATCHING
/* Branch layout of the done path differs. */
s32 func_801ECD28_ovl_23B220(void) {
    Ctx23 *c = D_801EFE48_ovl_23B220;
    s16 v = c->fade + 8;

    c->fade = v;
    if (v < 0xFF) {
        D_801CEAAB = v;
        return 0;
    }
    D_801CEAAB = 0xFF;
    c->fade = 0xFF;
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/23D090", func_801ECD28_ovl_23B220);
#endif

void func_801ECD80_ovl_23B220(void) {
    Ctx23 *s = D_801EFE48_ovl_23B220;
    s32 i;

    if (FIELD(s, void *, 0x244) != NULL) {
        HFree(FIELD(s, void *, 0x244));
        FIELD(s, void *, 0x244) = NULL;
        FIELD(s, s32, 0x248) = 0;
    }
    D_801EFE48_ovl_23B220->flags &= 3;
    for (i = 0; i < 2; i++) {
        u8 *e = (u8 *)D_801EFE48_ovl_23B220 + 0x5D4 + i * 0x1C;

        if (FIELD(e, void *, 4) != NULL) {
            HFree(FIELD(e, void *, 4));
            FIELD(e, void *, 4) = NULL;
        }
    }
    D_801EFE48_ovl_23B220->flags &= ~2;
}

INCLUDE_ASM("asm/nonmatchings/23D090", func_801ECE30_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801ED01C_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801ED224_ovl_23B220);
