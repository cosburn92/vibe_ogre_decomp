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
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/23D090", func_801E8E20_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801E8F90_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801E9130_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801E92D4_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801E9618_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801E9834_ovl_23B220);

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

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EA404_ovl_23B220);

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

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EA9BC_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EAA58_ovl_23B220);

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

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EB508_ovl_23B220);

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

INCLUDE_ASM("asm/nonmatchings/23D090", func_801ECC58_ovl_23B220);

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

INCLUDE_ASM("asm/nonmatchings/23D090", func_801ECD80_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801ECE30_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801ED01C_ovl_23B220);

INCLUDE_ASM("asm/nonmatchings/23D090", func_801ED224_ovl_23B220);
