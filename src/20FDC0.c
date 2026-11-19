#include "common.h"

/* 20FDC0 */

typedef struct {
    u8 unk00[0x7E];
    u8 step;
} Seq20F;

extern u8 *D_801D06D4_ovl_1F0A30;
extern u8 *D_801D06DC_ovl_1F0A30;
extern void *D_801CFCC0_ovl_1F0A30;
extern void *D_801D06D0_ovl_1F0A30;
extern Seq20F *D_801D06E0_ovl_1F0A30;

void func_801CCA5C_ovl_1F0A30(s32 a, s32 b, s32 c);
void bzero(void *p, s32 n);
void *HFree(void *p);
void nuGfxTaskAllEndWait(void);
s32 func_801CE38C_ovl_1F0A30(void);
extern u8 *D_801D06D8_ovl_1F0A30;
s32 ChunkSize(s32 id);
void *HMalloc(s32 size);
void *LoadChunkRaw(void *dst, s32 id);
extern u8 D_800E7A0C;
extern void *D_800C4BB8;
extern void *D_800A8204[3];
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/20FDC0", func_801CC930_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20FDC0", func_801CCA5C_ovl_1F0A30);

void func_801CCD4C_ovl_1F0A30(s32 a, s32 b, s32 c) {
    func_801CCA5C_ovl_1F0A30(a, c, b);
}

INCLUDE_ASM("asm/nonmatchings/20FDC0", func_801CCD70_ovl_1F0A30);

void func_801CCF5C_ovl_1F0A30(u16 *p, s16 a, s16 b, s16 c, s16 d) {
    bzero(p, 0x10);
    p[0] = a;
    p[1] = b;
    p[4] = c << 6;
    ((u8 *)p)[0xF] = 0xFF;
    p[5] = d << 6;
}

/* Sum of the integers from b to a */
s32 func_801CCFD4_ovl_1F0A30(s32 a, s32 b) {
    s32 s = 0;

    for (; a >= b; a--) {
        s += a;
    }
    return s;
}

/* Triangular number n(n+1)/2 */
s32 func_801CCFFC_ovl_1F0A30(s32 n) {
    s32 s = 0;

    for (; n > 0; n--) {
        s += n;
    }
    return s;
}

/* Backward byte copy (overlap-safe when dst > src) */
#ifdef NON_MATCHING
/* Loop counter compare differs. */
void func_801CD01C_ovl_1F0A30(u8 *dst, u8 *src, s32 n) {
    dst += n;
    src += n;
    while (n-- != 0) {
        *--dst = *--src;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/20FDC0", func_801CD01C_ovl_1F0A30);
#endif

INCLUDE_ASM("asm/nonmatchings/20FDC0", func_801CD058_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20FDC0", func_801CD108_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20FDC0", func_801CD19C_ovl_1F0A30);

/* Walks the combination trie (section 1) over n sorted elements; returns the last participant
 * mask reached (0 if none) */
#ifdef NON_MATCHING
/* Logic complete; prologue scheduling and register choice differ. */
s32 CombinationMatch(u8 *e, s32 n) {
    u8 *node = D_801D06D4_ovl_1F0A30;
    u8 *base = node;
    s32 r = 0;
    u8 *end;
    u8 k = node[0];

    if (k != 0xFF) {
        end = e + n;
        do {
            if (k == *e) {
                if (node[1] != 0) {
                    r = node[1];
                }
                e++;
                node = base + *(u16 *)(node + 2);
                if (!(e < end)) {
                    break;
                }
            } else {
                node += 4;
            }
            k = node[0];
        } while (k != 0xFF);
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/20FDC0", CombinationMatch);
#endif

/* Walks the 6-byte-node trie (section 1b) over n elements; returns the last result id reached
 * (0xFF if none) and stores the matching secondary value in *out */
#ifdef NON_MATCHING
/* same register/scheduling issue as CombinationMatch */
s32 CombinationLookup(u8 *e, s32 n, u8 *out) {
    u8 *node = D_801D06D8_ovl_1F0A30;
    u8 *base = node;
    s32 r2 = 0;
    s32 r = 0xFF;
    u8 *end;
    u8 k = node[0];

    if (k != 0xFF) {
        end = e + n;
        do {
            if (k == *e) {
                if (node[1] != 0xFF) {
                    r = node[1];
                }
                if (node[2] != 0xFF) {
                    r2 = node[2];
                }
                e++;
                node = base + *(u16 *)(node + 4);
                if (!(e < end)) {
                    break;
                }
            } else {
                node += 6;
            }
            k = node[0];
        } while (k != 0xFF);
    }
    if (out != NULL) {
        *out = r2;
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/20FDC0", CombinationLookup);
#endif

#ifdef NON_MATCHING
/* Same as CombinationMatch (section 2). */
s32 func_801CD390_ovl_1F0A30(u8 *e, s32 n) {
    u8 *node = D_801D06DC_ovl_1F0A30;
    u8 *base = node;
    s32 r = 0;
    u8 *end;
    u8 k = node[0];

    if (k != 0xFF) {
        end = e + n;
        do {
            if (k == *e) {
                if (node[1] != 0) {
                    r = node[1];
                }
                e++;
                node = base + *(u16 *)(node + 2);
                if (!(e < end)) {
                    break;
                }
            } else {
                node += 4;
            }
            k = node[0];
        } while (k != 0xFF);
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/20FDC0", func_801CD390_ovl_1F0A30);
#endif

/* Loads the combination tries (chunk 0x31823A, three sections) and chunk 0x3188AE */
#ifdef NON_MATCHING
/* original reuses one register for each section offset */
void CombinationTablesLoad(void) {
    u8 *t;
    u8 *a;
    u8 *b;
    u8 *c;

    D_801CFCC0_ovl_1F0A30 = HMalloc(ChunkSize(0x31823A));
    LoadChunkRaw(D_801CFCC0_ovl_1F0A30, 0x31823A);
    t = D_801CFCC0_ovl_1F0A30;
    a = t + *(u16 *)(t + 0);
    b = t + *(u16 *)(t + 2);
    c = t + *(u16 *)(t + 4);
    D_801D06D4_ovl_1F0A30 = a;
    D_801D06D8_ovl_1F0A30 = b;
    D_801D06DC_ovl_1F0A30 = c;
    D_801D06D0_ovl_1F0A30 = HMalloc(ChunkSize(0x3188AE));
    LoadChunkRaw(D_801D06D0_ovl_1F0A30, 0x3188AE);
}
#else
INCLUDE_ASM("asm/nonmatchings/20FDC0", CombinationTablesLoad);
#endif

void func_801CD4A0_ovl_1F0A30(void) {
    HFree(D_801CFCC0_ovl_1F0A30);
    D_801CFCC0_ovl_1F0A30 = NULL;
    HFree(D_801D06D0_ovl_1F0A30);
    D_801D06D0_ovl_1F0A30 = NULL;
}

INCLUDE_ASM("asm/nonmatchings/20FDC0", func_801CD4E0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20FDC0", func_801CD658_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20FDC0", func_801CD7A0_ovl_1F0A30);

void func_801CDB98_ovl_1F0A30(void) {
    if (D_801D06E0_ovl_1F0A30->step == 1) {
        D_801D06E0_ovl_1F0A30->step++;
    }
    if (D_801D06E0_ovl_1F0A30->step == 4) {
        D_801D06E0_ovl_1F0A30->step++;
    }
}

INCLUDE_ASM("asm/nonmatchings/20FDC0", func_801CDBE4_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20FDC0", func_801CDDC8_ovl_1F0A30);

/* Reports which frame buffer pair is current (o[0], o[1]) */
void func_801CDFC8_ovl_1F0A30(u8 *o) {
    nuGfxTaskAllEndWait();
    o[0] = 0;
    o[1] = 1;
    if (D_800E7A0C == 1) {
        if (D_800C4BB8 == D_800A8204[0]) {
            o[0] = 1;
            o[1] = 2;
        } else if (D_800C4BB8 == D_800A8204[1]) {
            o[0] = 0;
            o[1] = 2;
        } else if (D_800C4BB8 == D_800A8204[2]) {
            o[0] = 0;
            o[1] = 1;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/20FDC0", func_801CE064_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20FDC0", func_801CE38C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/20FDC0", func_801CE704_ovl_1F0A30);

void func_801CE858_ovl_1F0A30(void) {
    do {
        nuGfxTaskAllEndWait();
    } while (!func_801CE38C_ovl_1F0A30());
}
