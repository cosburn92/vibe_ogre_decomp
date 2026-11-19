#include "common.h"

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))

/* 29A4C0 */

typedef struct {
    /* 0x0 */ void *data;
    /* 0x4 */ s16 h4;
} Grid29;

typedef struct {
    /* 0x0 */ u8 unk0[8];
    /* 0x8 */ s16 h8;
    /* 0xA */ s16 hA;
} Pair29;

typedef struct {
    /* 0x0000 */ u8 unk0000[0x168];
    /* 0x0168 */ void *p168[0x38];
    /* 0x0248 */ Pair29 *p248[0x5BF];
    /* 0x1944 */ void *p1944[0x1C];
    /* 0x19B4 */ u8 unk19B4[0x94];
    /* 0x1A48 */ Grid29 *grid;
    /* 0x1A4C */ u8 unk1A4C[0x168];
    /* 0x1BB4 */ void *p1BB4[20];
} Battle29;

extern Battle29 *D_8022A974;
extern s8 D_801CFC70;
extern u8 D_801D082C;

void *HMalloc(s32 size);
void *HFree(void *p);
void func_8022BB58_ovl_29A4C0(s32 a, s32 b);
void func_801C22E8(s32 a);
#define FLD(p, T, off) (*(T *)((u8 *)(p) + (off)))
s32 func_801BEA0C(s32 fmt, s32 w);
u16 func_801BEB28(u16 c);
u32 func_801BEA70(u32 c);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022AC90_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022AD6C_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022AE84_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022AF94_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022B100_ovl_29A4C0);

void func_8022B414_ovl_29A4C0(s32 i) {
    s32 k;
    s32 end;

    if (i == -1) {
        i = 0;
        end = 30;
    } else {
        end = i + 1;
    }
    for (k = i; k < end; k++) {
        if (FLD(D_8022A974, void *, 0x1AC0 + k * 4) != NULL) {
            HFree(FLD(D_8022A974, void *, 0x1AC0 + k * 4));
            FLD(D_8022A974, void *, 0x1AC0 + k * 4) = NULL;
        }
    }
}

/* Sepia-filters an image in place (fmt 2: RGBA5551, fmt 3: RGBA8888) */
void func_8022B4A8_ovl_29A4C0(void *pix, s32 fmt, s32 h, s32 w) {
    s32 n = func_801BEA0C(fmt, w) * h;
    s32 i;

    if (fmt == 2) {
        u16 *p = pix;

        for (i = 0; i < n; i++, p++) {
            *p = func_801BEB28(*p);
        }
    } else if (fmt == 3) {
        u32 *p = pix;

        for (i = 0; i < n; i++, p++) {
            *p = func_801BEA70(*p);
        }
    }
}

/* Sepia-filters every RGBA5551 image in a sprite bank */
#ifdef NON_MATCHING
/* hdr/k registers swapped (s3/s4) and the a0=2 hoist differs */
void func_8022B56C_ovl_29A4C0(u8 *bank) {
    u8 *e = bank + 8;
    u8 k;

    for (k = 0; k < bank[3]; k++) {
        u8 *hdr = e;
        s32 h = FIELD(hdr, u16, 6);
        s32 n;
        s32 i;

        e = hdr + 0x10;
        n = func_801BEA0C(2, FIELD(hdr, u16, 4)) * h;
        for (i = 0; i < n; i++, e += 2) {
            *(u16 *)e = func_801BEB28(*(u16 *)e);
        }
        e = FIELD(hdr, u8 *, 0xC);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022B56C_ovl_29A4C0);
#endif

/* Sepia-filters a single image (8-byte header: [3] fmt, u16 width at 4, height at 6) */
#ifdef NON_MATCHING
/* Same as func_8022B4A8 applied to img+8. Inlining that function gets closest; the only difference left is that the original keeps the pixel pointer in the img register (s1) and fmt in s3. */
void func_8022B62C_ovl_29A4C0(u8 *img) {
    s32 fmt = img[3];
    s32 w = FIELD(img, u16, 4);
    s32 h = FIELD(img, u16, 6);
    s32 n;
    s32 i;

    img += 8;
    n = func_801BEA0C(fmt, w) * h;
    if (fmt == 2) {
        u16 *p = (u16 *)img;

        for (i = 0; i < n; i++, p++) {
            *p = func_801BEB28(*p);
        }
    } else if (fmt == 3) {
        u32 *p = (u32 *)img;

        for (i = 0; i < n; i++, p++) {
            *p = func_801BEA70(*p);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022B62C_ovl_29A4C0);
#endif

INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022B6F4_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022BB58_ovl_29A4C0);

void func_8022BD74_ovl_29A4C0(void) {
    Grid29 *g;

    if (D_8022A974->grid != NULL) {
        HFree(D_8022A974->grid->data);
        HFree(D_8022A974->grid);
    }
    g = HMalloc(8);
    D_8022A974->grid = g;
    g->h4 = -1;
    func_8022BB58_ovl_29A4C0(0xA0, 0x78);
}

void func_8022BDDC_ovl_29A4C0(void) {
    if (D_8022A974->grid != NULL) {
        HFree(D_8022A974->grid->data);
        HFree(D_8022A974->grid);
        D_8022A974->grid = NULL;
        func_801C22E8(1);
    }
}

INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022BE30_ovl_29A4C0);

void func_8022BF5C_ovl_29A4C0(s32 *a) {
    s16 i = FLD(a, s16, 2);
    u8 *p;

    if (D_8022A974->p1944[i] != NULL) {
        HFree(D_8022A974->p1944[i]);
    }
    p = HMalloc(7);
    D_8022A974->p1944[i] = p;
    p[0] = a[7];
    p[1] = a[1];
    p[2] = a[2];
    p[3] = a[3];
    p[4] = a[4];
    p[5] = a[5];
    p[6] = a[6];
}

void func_8022BFFC_ovl_29A4C0(void) {
    s32 i;

    for (i = 0; i < 0x1C; i++) {
        if (D_8022A974->p1944[i] != NULL) {
            HFree(D_8022A974->p1944[i]);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022C04C_ovl_29A4C0);

void func_8022C1B0_ovl_29A4C0(s32 i) {
    if (D_8022A974->p1944[i] != NULL) {
        HFree(D_8022A974->p1944[i]);
        D_8022A974->p1944[i] = NULL;
    }
}

/* RGBA5551 to RGBA8888 */
u32 func_8022C200_ovl_29A4C0(u32 c) {
    return ((c & 0xF800) << 16) | ((c & 0x7C0) << 13) | ((c & 0x3E) << 10) | 0xFF;
}

/* RGBA8888 to RGBA5551 */
u32 func_8022C228_ovl_29A4C0(u32 c) {
    return ((c >> 16) & 0xF800) | ((c >> 13) & 0x7C0) | ((c & 0xF800) >> 10) | 1;
}

INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022C250_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022C3A8_ovl_29A4C0);

s32 func_8022C594_ovl_29A4C0(s32 i) {
    Pair29 *p = D_8022A974->p248[i];
    s32 r = 0;

    if (p != NULL) {
        r = p->hA != p->h8;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022C5C8_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022C6C4_ovl_29A4C0);

s32 func_8022C96C_ovl_29A4C0(void) {
    if (D_801CFC70 < 0) {
        return 1;
    }
    return D_801CFC70;
}

INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022C988_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022CBD4_ovl_29A4C0);

void func_8022CD00_ovl_29A4C0(void) {
    u32 i;

    for (i = 0; i < 20; i++) {
        if (D_8022A974->p1BB4[i] != NULL) {
            HFree(D_8022A974->p1BB4[i]);
            D_8022A974->p1BB4[i] = NULL;
        }
    }
    D_801D082C = 0;
}

void func_8022CD70_ovl_29A4C0(s32 i, s32 v) {
    s32 end;
    u8 *u;

    if (i == -1) {
        i = 0;
        end = 28;
    } else {
        end = i + 1;
    }
    for (; i < end; i++) {
        u = FLD(D_8022A974, u8 *, 0x18 + i * 4);
        if (u != NULL) {
            if (v != -1) {
                FLD(u, f32, 0x120) = v;
            }
            FLD(u, s32, 0x128) = 0;
            u[0x145] = (u[0x145] & ~1) | 4;
        }
    }
}

/* small s16 tables (shared rodata splat leaves unmigrated) */
__asm__(".section .rodata\n.global D_80239190_ovl_29A4C0\nD_80239190_ovl_29A4C0:\n.half 0, 9, 6, 3\n.global D_80239198_ovl_29A4C0\nD_80239198_ovl_29A4C0:\n.half 0, 9, 8, 3, 7, 7, 2, 6, 5, 1, 4, 4\n.section .text\n");

INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022CDF4_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29A4C0", func_8022CF60_ovl_29A4C0);

s32 func_8022D0FC_ovl_29A4C0(s32 i) {
    return D_8022A974->p168[i] != NULL;
}
