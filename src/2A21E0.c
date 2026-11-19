#include "common.h"

/* 2A21E0 */

typedef struct {
    /* 0x00 */ s32 id;
    /* 0x04 */ u8 unk04[4];
    /* 0x08 */ void *p08;
    /* 0x0C */ s32 kind;
    /* 0x10 */ u32 n;
    /* 0x14 */ void *p14;
    /* 0x18 */ u8 unk18[4];
    /* 0x1C */ void **list;
    /* 0x20 */ void *p20;
    /* 0x24 */ u8 unk24[4];
    /* 0x28 */ s32 w28;
    /* 0x2C */ s32 w2C;
    /* 0x30 */ u8 *w30;
    /* 0x34 */ u8 unk34[4];
    /* 0x38 */ void *p38;
} Rec2A; /* size 0x3C */

extern Rec2A *D_802395B0_ovl_29A4C0;
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern u8 *D_8022A974;

void *HMalloc(s32 size);
void bzero(void *p, s32 n);
void HFree(void *p);
Rec2A *func_80232C28_ovl_29A4C0(void);
void func_801BFBA0(void *p);
/* --- end decls --- */

void func_802329B0_ovl_29A4C0(void) {
    Rec2A *p = HMalloc(0x960);

    D_802395B0_ovl_29A4C0 = p;
    bzero(p, 0x960);
}

INCLUDE_ASM("asm/nonmatchings/2A21E0", func_802329E0_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/2A21E0", func_80232B20_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/2A21E0", func_80232C28_ovl_29A4C0);

#ifdef NON_MATCHING
/* The record pointer and derived field pointer use swapped registers. */
s32 func_80232DE0_ovl_29A4C0(s32 id, s32 kind) {
    Rec2A *r = D_802395B0_ovl_29A4C0;
    s32 i;

    for (i = 40; i-- != 0; r++) {
        if (r->id == id && r->kind == kind) {
            return r->w2C;
        }
    }
    return func_80232C28_ovl_29A4C0()->w2C;
}
#else
INCLUDE_ASM("asm/nonmatchings/2A21E0", func_80232DE0_ovl_29A4C0);
#endif

#ifdef NON_MATCHING
/* The record pointer and derived field pointer use swapped registers. */
s32 func_80232E44_ovl_29A4C0(s32 id, s32 kind) {
    Rec2A *r = D_802395B0_ovl_29A4C0;
    s32 i;

    for (i = 40; i-- != 0; r++) {
        if (r->id == id && r->kind == kind) {
            return r->w28;
        }
    }
    return func_80232C28_ovl_29A4C0()->w28;
}
#else
INCLUDE_ASM("asm/nonmatchings/2A21E0", func_80232E44_ovl_29A4C0);
#endif

u8 func_80232EA8_ovl_29A4C0(s32 id, s32 k) {
    Rec2A *r = D_802395B0_ovl_29A4C0;
    s32 i;

    for (i = 40; i-- != 0; r++) {
        if (r->id == id) {
            return r->w30[k];
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/2A21E0", func_80232EE8_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/2A21E0", func_80233134_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/2A21E0", func_802332A0_ovl_29A4C0);

/* Passes every non-null entry of every record's list to func_801BFBA0 */
void func_80233398_ovl_29A4C0(void) {
    Rec2A *r;
    u32 i;
    u32 k;

    if (D_802395B0_ovl_29A4C0 == NULL) {
        return;
    }
    for (i = 0; i < 40; i++) {
        r = &D_802395B0_ovl_29A4C0[i];
        for (k = 0; k < D_802395B0_ovl_29A4C0[i].n; k++) {
            if (r->list[k] != NULL) {
                func_801BFBA0(r->list[k]);
            }
        }
    }
}

/* Frees the record of the active unit (matched by id and kind) and clears it */
void func_80233448_ovl_29A4C0(void) {
    s16 side = FIELD(FIELD(D_8022A974, u8 *, 0x1A48), s16, 4);
    u8 *u;
    Rec2A *r;
    s32 id;
    s32 kind;
    u32 i;
    u32 k;

    if (side == -1) {
        return;
    }
    u = FIELD(D_8022A974, u8 *, 0x18 + side * 4);
    if (u == NULL) {
        return;
    }
    id = FIELD(u, s32, 0xE8);
    kind = u[0x146];
    if (D_802395B0_ovl_29A4C0 == NULL) {
        return;
    }
    r = D_802395B0_ovl_29A4C0;
    for (i = 0; i < 40; r++, i++) {
        if (r->id == id && r->kind == kind) {
            for (k = 0; k < r->n; k++) {
                if (r->list[k] != NULL) {
                    HFree(r->list[k]);
                    r->list[k] = NULL;
                }
            }
            HFree(r->p20);
            HFree(r->p08);
            HFree((void *)r->w2C);
            HFree((void *)r->w28);
            HFree(r->p38);
            HFree(r->p14);
            bzero(r, 0x3C);
            return;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/2A21E0", func_80233580_ovl_29A4C0);
