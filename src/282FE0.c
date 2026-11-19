#include "common.h"

extern u8 D_800EB0B0[];
extern s32 D_8022A8A8_ovl_281860[];
typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
} St8C4;
extern St8C4 *D_8022A8C4_ovl_281860;
extern s32 D_8022A990_ovl_281860;
extern u8 D_8018FC19;
extern u8 D_8022A980_ovl_281860;
extern u8 *D_8018FC10;
extern u8 *D_8022A974_ovl_281860;
void func_800EA838(void *p);
void func_800EA884(s32 a);
void HFree(void *p);
void MusSetMasterVolume(s32 flags, s32 volume);





#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
typedef struct {
    u8 b[0x34];
} EChar282;
typedef struct {
    u8 b[0x38];
} PChar282;
typedef struct Node282 {
    struct Node282 *prev;
    struct Node282 *next;
} Node282;
extern EChar282 D_80195560[];
extern PChar282 D_80193BC0[];
extern void *D_8018EA00[];
extern Node282 *D_8018FDC0;
extern s32 D_8022A720_ovl_281860;
extern s32 D_8022A734_ovl_281860;
extern s32 D_8022A738_ovl_281860;
extern s32 D_8022A73C_ovl_281860;
extern s32 D_8022A740_ovl_281860;
extern s32 D_8022A744_ovl_281860;
extern s32 D_8022A748_ovl_281860;
extern s32 D_8022A778_ovl_281860;
extern s32 D_8022A78C_ovl_281860;
extern s32 D_8022A790_ovl_281860;
extern s32 D_8022A794_ovl_281860;
extern s32 D_8022A798_ovl_281860;
extern s32 D_8022A79C_ovl_281860;
extern s32 D_8022A7A0_ovl_281860;
s32 func_8016FEF4(s32 flag);
void func_800EA7E4(s32 a, s32 b);
void func_802282B8_ovl_281860(void);
void func_800EA86C(s32 ch, s32 v);
void func_800EA89C(s32 ch, s32 v);
void func_800EA8B4(s32 ch, s32 v);
extern s32 D_800EB2E0[];
void *HMalloc(s32 size);
void bzero(void *p, s32 n);
/* --- end decls --- */

void func_80227010_ovl_281860(void) {
    if (!D_8018FC19) {
        D_8022A740_ovl_281860 = 0;
        D_8022A744_ovl_281860 = 0;
        D_8022A748_ovl_281860 = 0;
        D_8022A738_ovl_281860 = 0;
        D_8022A73C_ovl_281860 = 0;
        D_8022A798_ovl_281860 = 0;
        D_8022A79C_ovl_281860 = 0;
        D_8022A7A0_ovl_281860 = 0;
        D_8022A78C_ovl_281860 = 0;
        D_8022A790_ovl_281860 = 0;
        *(f32 *)&D_8022A734_ovl_281860 = 360.0f;
        *(f32 *)&D_8022A720_ovl_281860 = 38.0f;
        *(f32 *)&D_8022A794_ovl_281860 = 360.0f;
        *(f32 *)&D_8022A778_ovl_281860 = 38.0f;
    }
    D_8022A990_ovl_281860 = 0;
    func_802282B8_ovl_281860();
}

INCLUDE_ASM("asm/nonmatchings/282FE0", func_802270BC_ovl_281860);

void func_80227210_ovl_281860(s32 i) {
    if (i == 7) {
        func_800EA838(D_800EB0B0);
    } else {
        func_800EA884(D_8022A8A8_ovl_281860[i]);
    }
}

void func_80227254_ovl_281860(s32 mode, s32 idx, s32 n, s32 h) {
    s32 half = n / 2;

    if (D_8022A8C4_ovl_281860 == NULL) {
        D_8022A8C4_ovl_281860 = HMalloc(4);
        bzero(D_8022A8C4_ovl_281860, 4);
        if ((u32)(mode - 2) < 5) {
            D_8022A8C4_ovl_281860->h2 = 0x7FFF;
        } else {
            D_8022A8C4_ovl_281860->h2 = D_800EB2E0[idx * 2];
        }
        if (n > 0) {
            D_8022A8C4_ovl_281860->h2 -= half * h;
        }
    }
    D_8022A8C4_ovl_281860->h0 = half;
    D_8022A8C4_ovl_281860->h4 = h;
    D_8022A8C4_ovl_281860->h6 = mode;
}

void func_80227348_ovl_281860(void) {
    HFree(D_8022A8C4_ovl_281860);
    D_8022A8C4_ovl_281860 = NULL;
    MusSetMasterVolume(1, 0x7FFF);
}

INCLUDE_ASM("asm/nonmatchings/282FE0", func_80227380_ovl_281860);

void func_802274F4_ovl_281860(s32 i, s32 v) {
    s32 k;
    s32 end;

    k = 0;
    if (func_8016FEF4(0xB5) == 1) {
        return;
    }
    if (i == 7) {
        end = 7;
    } else {
        k = i;
        end = i + 1;
    }
    for (; k < end; k++) {
        func_800EA7E4(D_8022A8A8_ovl_281860[k], v);
    }
}

/* Sets the three parameters of sound channel i (all 7 when i is 7); -1 leaves one unchanged */
void func_80227594_ovl_281860(s32 i, s32 a, s32 b, s32 c) {
    s32 k = 0;
    s32 end;

    if (i == 7) {
        end = 7;
    } else {
        k = i;
        end = i + 1;
    }
    for (; k < end; k++) {
        if (a != -1) {
            func_800EA86C(D_8022A8A8_ovl_281860[k], a);
        }
        if (b != -1) {
            func_800EA89C(D_8022A8A8_ovl_281860[k], b);
        }
        if (c != -1) {
            func_800EA8B4(D_8022A8A8_ovl_281860[k], c / 128);
        }
    }
}

void func_8022767C_ovl_281860(void) {
}

void func_80227684_ovl_281860(void) {
    D_8022A990_ovl_281860 = 1;
}

/* Counts up while running (non-zero), stopping before it wraps. */
void func_80227694_ovl_281860(void) {
    if ((u32)(D_8022A990_ovl_281860 - 1) < 0xFFFFFFE) {
        D_8022A990_ovl_281860++;
    }
}

s32 func_802276C4_ovl_281860(void) {
    return D_8022A990_ovl_281860 - 1;
}

void func_802276D4_ovl_281860(void) {
    D_8022A990_ovl_281860 = 0;
}

void func_802276E0_ovl_281860(u8 v) {
    D_8018FC19 = v;
}

u8 func_802276EC_ovl_281860(void) {
    return D_8022A980_ovl_281860;
}

s16 func_802276F8_ovl_281860(s32 i) {
    s32 *p = FIELD(D_8022A974_ovl_281860 + i * 4, s32 *, 0x19B8);
    u8 found = 0;
    Node282 *n;

    if (p == NULL) {
        return -5;
    }
    for (n = D_8018FDC0->next; n != NULL; n = n->next) {
        if (FIELD(n, u8 *, 0xD0) != NULL && FIELD(FIELD(n, u8 *, 0xD0), s32, 0x600) == *p) {
            found = 1;
            break;
        }
    }
    if (!found) {
        return -6;
    }
    return FIELD(p, s16, 0x14);
}

void func_80227770_ovl_281860(void) {
}

/* Frees record slot i at 0x19B8 (all 14 when i is -1) */
void func_80227778_ovl_281860(s32 i) {
    u8 k = 0;
    u8 end = 14;
    u8 *r;

    if (i != -1) {
        k = i;
        end = i + 1;
    }
    for (; k < end; k++) {
        r = FIELD(D_8022A974_ovl_281860 + k * 4, u8 *, 0x19B8);
        if (r != NULL) {
            HFree(FIELD(r, void *, 0x10));
            HFree(FIELD(r, void *, 8));
            HFree(FIELD(r, void *, 4));
            HFree(r);
            FIELD(D_8022A974_ovl_281860 + k * 4, u8 *, 0x19B8) = NULL;
        }
    }
}

/* Character record for id: enemy table, then player table, then the extras table (ids 0x54+) */
void *func_80227838_ovl_281860(s32 id) {
    s32 i;

    for (i = 0; i < 100; i++) {
        if (D_80195560[i].b[0x11] == id) {
            return &D_80195560[i];
        }
    }
    for (i = 0; i < 100; i++) {
        if (D_80193BC0[i].b[0x11] == id) {
            return &D_80193BC0[i];
        }
    }
    if (id >= 0x54) {
        return D_8018EA00[id];
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/282FE0", func_802278DC_ovl_281860);

void func_802279D8_ovl_281860(void) {
    if (D_8018FC10 != NULL) {
        D_8018FC10[7] = 1;
    }
}

s16 func_802279F4_ovl_281860(void) {
    if (D_8018FC10 != NULL) {
        return *(s16 *)D_8018FC10;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/282FE0", func_80227A18_ovl_281860);

void func_80227B60_ovl_281860(void) {
    u8 *p = D_8022A974_ovl_281860;

    if (!p[0x1CB1]) {
        p[0x1CB1] = 1;
    }
}

void func_80227B80_ovl_281860(void) {
    u8 *p = D_8022A974_ovl_281860;

    if (p[0x1CB1]) {
        p[0x1CB1] = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/282FE0", func_80227B9C_ovl_281860);

INCLUDE_ASM("asm/nonmatchings/282FE0", func_80227CBC_ovl_281860);

/* Linear interpolation: b + (a - b) * c / d. */
s32 func_80227DC4_ovl_281860(s32 a, s32 b, s32 c, s32 d) {
    return (a - b) * c / d + b;
}

INCLUDE_RODATA("asm/nonmatchings/282FE0", D_8022ABA8_ovl_281860);

INCLUDE_RODATA("asm/nonmatchings/282FE0", D_8022ABB8_ovl_281860);
