#include "common.h"

/* 20-entry cache keyed by id (0 = free), 0xB0 bytes each. */
typedef struct {
    /* 0x00 */ s32 key;
    /* 0x04 */ u8 unk04[0x40];
    /* 0x44 */ void *data;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ u8 unk54[0x4E];
    /* 0xA2 */ u8 bytes[6];
    /* 0xA8 */ u16 halves[4];
} CacheEntry;

extern u8 D_801CEF00_ovl_1F0A30;
extern CacheEntry *D_801D0728_ovl_1F0A30;
extern s32 D_801D06B0_ovl_1F0A30[8];
extern u8 D_800EB0B0[];
extern u8 D_800EB100[];
extern u8 D_800EB150[];
extern u8 D_800EB1A0[];
extern u8 D_800EB1F0[];
extern u8 D_800EB240[];
extern u8 D_800EB290[];
extern u16 D_800E810E;
typedef struct {
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
} BBox205;
typedef struct {
    s32 unk0;
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    s32 unk14[5];
} Item205;
extern BBox205 D_801D03A0_ovl_1F0A30;
extern u8 D_801CEEE0_ovl_1F0A30[]; /* event length by type */
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
void func_800EA6B0(void *ch, s32 a, s32 b);
void func_800EA604(void *ch, s32 sound);
void *HMalloc(s32 size);
void HFree(void *p);
void bzero(void *p, s32 size);





void func_801C1D90_ovl_1F0A30(void) {
}

void func_801C1D98_ovl_1F0A30(void) {
}

s32 func_801C2178_ovl_1F0A30(void *a, void *b, s32 i, s32 *r);
s32 func_801C2C5C_ovl_1F0A30(s32 key);
/* --- end decls --- */

/* Width spanned by the glyph boxes of a text layout (0 if empty) */
s32 func_801C1DA0_ovl_1F0A30(void *a, void *b) {
    s32 r[10];
    s32 i;
    s32 lo = 1000;
    s32 hi = -1000;

    for (i = 0; func_801C2178_ovl_1F0A30(a, b, i, r); i++) {
        if (r[2] < lo) {
            lo = r[2];
        }
        if (hi < r[2] + r[4]) {
            hi = r[2] + r[4];
        }
    }
    {
        s32 d = hi - lo;

        return d < 0 ? 0 : d;
    }
}

/* Height spanned by the glyph boxes of a text layout (0 if empty) */
s32 func_801C1E44_ovl_1F0A30(void *a, void *b) {
    s32 r[10];
    s32 i;
    s32 lo = 1000;
    s32 hi = -1000;

    for (i = 0; func_801C2178_ovl_1F0A30(a, b, i, r); i++) {
        if (r[1] < lo) {
            lo = r[1];
        }
        if (hi < r[1] + r[3]) {
            hi = r[1] + r[3];
        }
    }
    {
        s32 d = hi - lo;

        return d < 0 ? 0 : d;
    }
}

/* Bounding box of all items of (a, b), starting from the default box */
BBox205 func_801C1EE8_ovl_1F0A30(void *a, void *b) {
    Item205 it;
    BBox205 bb = D_801D03A0_ovl_1F0A30;
    s32 i;

    for (i = 0; func_801C2178_ovl_1F0A30(a, b, i, (s32 *)&it); i++) {
        if (it.x < bb.x0) {
            bb.x0 = it.x;
        }
        if (it.y < bb.y0) {
            bb.y0 = it.y;
        }
        if (bb.x1 < it.x + it.w) {
            bb.x1 = it.x + it.w;
        }
        if (bb.y1 < it.y + it.h) {
            bb.y1 = it.y + it.h;
        }
    }
    return bb;
}

typedef struct {
    /* 0x0 */ u16 id;
    /* 0x2 */ s16 x;
    /* 0x4 */ s16 y;
    /* 0x6 */ u16 w;
    /* 0x8 */ u16 h;
    /* 0xA */ u16 unkA;
    /* 0xC */ u16 u; /* 6.10 fixed point */
    /* 0xE */ u16 v;
} RawItem205;

s32 func_801BE138(s32 a, s32 b, s32 c, s32 d);
void func_801C2DDC_ovl_1F0A30(s32 key, s32 *a, s32 *b, s32 *c, s32 *d);

/* Item i of layout `layout` of the resource for (a, b, c, d), unpacked into r like func_801C2178;
 * the two mirrored layouts map to their sources with flag 0x40 or 0x80; r[8] = i */
s32 func_801C1FF4_ovl_1F0A30(s32 a, s32 b, s32 c, s32 d, s32 layout, u32 i, s32 *r) {
    s32 key = func_801BE138(a, b, c, d);
    s32 l0, m0, l1, m1;
    s32 base;
    u16 *t;
    RawItem205 *e;

    func_801C2DDC_ovl_1F0A30(key, &l0, &m0, &l1, &m1);
    if (layout == l0) {
        layout = m0;
        r[5] = 0x40;
    } else if (layout == l1) {
        layout = m1;
        r[5] = 0x80;
    } else {
        r[5] = 0;
    }
    base = func_801C2C5C_ovl_1F0A30(key);
    if (base != 0) {
        t = (u16 *)(base + ((s32 *)base)[layout]);
    } else {
        t = NULL;
    }
    if (i < *t++) {
        t += i * 8;
        e = (RawItem205 *)t;
        ((s8 *)r)[0x20] = i;
        r[0] = e->id;
        r[1] = e->x;
        r[2] = e->y;
        r[3] = e->w;
        r[4] = e->h;
        r[5] |= e->unkA;
        ((f32 *)r)[6] = (f32)(e->u >> 10) + (f32)(e->u & 0x3FF) / 1024.0f;
        ((f32 *)r)[7] = (f32)(e->v >> 10) + (f32)(e->v & 0x3FF) / 1024.0f;
        return 1;
    }
    return 0;
}


/* Item i of layout b in the cached resource a, unpacked into r (s32 fields, then two floats);
 * 0 past the end */
s32 func_801C2178_ovl_1F0A30(void *a, void *b, s32 i, s32 *r) {
    s32 base = func_801C2C5C_ovl_1F0A30((s32)a);
    u16 *t;
    RawItem205 *e;

    if (base != 0) {
        t = (u16 *)(base + ((s32 *)base)[(s32)b]);
    } else {
        t = NULL;
    }
    if ((u32)i < *t++) {
        t += i * 8;
        e = (RawItem205 *)t;
        r[0] = e->id;
        r[1] = e->x;
        r[2] = e->y;
        r[3] = e->w;
        r[4] = e->h;
        r[5] = e->unkA;
        ((f32 *)r)[6] = (f32)(e->u >> 10) + (f32)(e->u & 0x3FF) / 1024.0f;
        ((f32 *)r)[7] = (f32)(e->v >> 10) + (f32)(e->v & 0x3FF) / 1024.0f;
        return 1;
    }
    return 0;
}

u32 func_801C2290_ovl_1F0A30(u32 v) {
    return (v >> 24) | ((v >> 8) & 0xFF00) | ((v & 0xFF00) << 8) | (v << 24);
}

u16 func_801C22B8_ovl_1F0A30(u32 v) {
    return ((v & 0xFF00) >> 8) | ((v & 0xFF) << 8);
}

void func_801C22D0_ovl_1F0A30(u8 bits) {
    D_801CEF00_ovl_1F0A30 |= bits;
}

void func_801C22E8_ovl_1F0A30(u8 bits) {
    D_801CEF00_ovl_1F0A30 &= ~bits;
}

u8 func_801C2304_ovl_1F0A30(void) {
    return D_801CEF00_ovl_1F0A30;
}

void func_801C2310_ovl_1F0A30(void) {
    D_801CEF00_ovl_1F0A30 = 2;
    D_801D0728_ovl_1F0A30 = HMalloc(0xDC0);
    bzero(D_801D0728_ovl_1F0A30, 0xDC0);
}

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
#define CE205A(o) ((u8 *)((o) + (u32)D_801D0728_ovl_1F0A30))

/* Frees the cache and everything its 20 entries own */
#ifdef NON_MATCHING
/* same length; only v0/v1 swap in the 0x70 slot loop's address computation */
void func_801C234C_ovl_1F0A30(void) {
    u32 off;
    u32 i;

    if (D_801D0728_ovl_1F0A30 != NULL) {
        for (off = 0; off < 0xDC0; off += 0xB0) {
            for (i = 0; i < FIELD(CE205A(off), u32, 0x18); i++) {
                if (FIELD(CE205A(off), void **, 0x38)[i] != NULL) {
                    HFree(FIELD(CE205A(off), void **, 0x38)[i]);
                }
                if (FIELD(CE205A(off), void **, 0x3C)[i] != NULL) {
                    HFree(FIELD(CE205A(off), void **, 0x3C)[i]);
                }
                if (FIELD(CE205A(off), void **, 0x40)[i] != NULL) {
                    HFree(FIELD(CE205A(off), void **, 0x40)[i]);
                }
            }
            {
                u32 o = off;

                for (i = 0; i < 10; i++) {
                    if (FIELD(CE205A(o) + i * 4, void *, 0x70) != NULL) {
                        HFree(FIELD(CE205A(o) + i * 4, void *, 0x70));
                    }
                }
            }
            HFree(FIELD(CE205A(off), void *, 0x8));
            HFree(FIELD(CE205A(off), void *, 0x48));
            HFree(FIELD(CE205A(off), void *, 0x44));
            HFree(FIELD(CE205A(off), void *, 0x6C));
            HFree(FIELD(CE205A(off), void *, 0x2C));
        }
        HFree(D_801D0728_ovl_1F0A30);
        D_801D0728_ovl_1F0A30 = NULL;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/205220", func_801C234C_ovl_1F0A30);
#endif

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
#define CE205C(o) ((u8 *)((o) + (u32)D_801D0728_ovl_1F0A30))
void bzero(void *p, s32 n);

/* Frees and clears the cache entry for (key a, sub-key b) */
void func_801C24F8_ovl_1F0A30(s32 a, s32 b) {
    u32 off;
    u32 i;

    if (D_801D0728_ovl_1F0A30 != NULL) {
        for (off = 0; off < 0xDC0; off += 0xB0) {
            if (FIELD(CE205C(off), s32, 0) == a && FIELD(CE205C(off), s32, 0xC) == b) {
                for (i = 0; i < FIELD(CE205C(off), u32, 0x18); i++) {
                    HFree(FIELD(CE205C(off), void **, 0x38)[i]);
                }
                for (i = 0; i < FIELD(CE205C(off), u32, 0x18); i++) {
                    HFree(FIELD(CE205C(off), void **, 0x3C)[i]);
                }
                for (i = 0; i < FIELD(CE205C(off), u32, 0x18); i++) {
                    HFree(FIELD(CE205C(off), void **, 0x40)[i]);
                }
                i = 0;
                {
                    u32 o = off;

                    for (; i < 10; i++) {
                        HFree(FIELD(CE205C(o) + i * 4, void *, 0x70));
                    }
                }
                HFree(FIELD(CE205C(off), void *, 0x8));
                HFree(FIELD(CE205C(off), void *, 0x48));
                HFree(FIELD(CE205C(off), void *, 0x44));
                HFree(FIELD(CE205C(off), void *, 0x6C));
                HFree(FIELD(CE205C(off), void *, 0x2C));
                bzero((u8 *)D_801D0728_ovl_1F0A30 + off, 0xB0);
            }
        }
    }
}

/* Scans the two event streams of o's data (offsets at 0x98 and, from 0x58 on, 0x160) for type-1
 * events, keeping the last two values of each in 0xA8/0xAA and 0xAC/0xAE */
void func_801C2710_ovl_1F0A30(u8 *o) {
    u8 *d = FIELD(o, u8 *, 0x44);
    u8 *p = d + FIELD(d, s32, 0x98);
    u32 n = *p++;
    u32 i;

    FIELD(o, u16, 0xAA) = FIELD(o, u16, 0xA8) = FIELD(o, u16, 0xAE) = FIELD(o, u16, 0xAC) = 0xFFFF;
    for (i = 0; i < n; i++) {
        if (*p == 1) {
            FIELD(o, u16, 0xAA) = FIELD(o, u16, 0xA8);
            FIELD(o, u16, 0xA8) = p[1];
        }
        p += D_801CEEE0_ovl_1F0A30[*p];
    }
    if (FIELD(o, u32, 0x4C) >= 0x58) {
        p = d + FIELD(d, s32, 0x160);
        n = *p++;
        for (i = 0; i < n; i++) {
            if (*p == 1) {
                FIELD(o, u16, 0xAE) = FIELD(o, u16, 0xAC);
                FIELD(o, u16, 0xAC) = p[1];
            }
            p += D_801CEEE0_ovl_1F0A30[*p];
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/205220", D_801D03A0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C27F8_ovl_1F0A30);

s32 func_801C2C5C_ovl_1F0A30(s32 key) {
    CacheEntry *e = D_801D0728_ovl_1F0A30;
    s32 i = 19;

    do {
        if (e->key != 0 && e->key == key) {
            return e->unk48;
        }
        e++;
    } while (i-- != 0);
    return 0;
}

s32 func_801C2CA0_ovl_1F0A30(s32 key) {
    CacheEntry *e = D_801D0728_ovl_1F0A30;
    s32 i = 19;

    do {
        if (e->key != 0 && e->key == key) {
            return e->unk50;
        }
        e++;
    } while (i-- != 0);
    return 0;
}

void * func_801C2CE4_ovl_1F0A30(s32 key) {
    CacheEntry *e = D_801D0728_ovl_1F0A30;
    s32 i = 19;

    do {
        if (e->key != 0 && e->key == key) {
            return e->data;
        }
        e++;
    } while (i-- != 0);
    return 0;
}

s32 func_801C2D28_ovl_1F0A30(s32 key) {
    CacheEntry *e = D_801D0728_ovl_1F0A30;
    s32 i = 19;

    do {
        if (e->key != 0 && e->key == key) {
            return e->unk4C;
        }
        e++;
    } while (i-- != 0);
    return 0;
}

void func_801C2D6C_ovl_1F0A30(s32 key, void *data) {
    CacheEntry *e = D_801D0728_ovl_1F0A30;
    s32 i = 19;

    do {
        if (e->key != 0 && e->key == key) {
            HFree(e->data);
            e->data = data;
            return;
        }
        e++;
    } while (i-- != 0);
}

void func_801C2DDC_ovl_1F0A30(s32 key, s32 *a, s32 *b, s32 *c, s32 *d) {
    CacheEntry *e = D_801D0728_ovl_1F0A30;
    s32 i = 19;

    do {
        if (e->key != 0 && e->key == key) {
            *a = e->halves[0];
            *b = e->halves[1];
            *c = e->halves[2];
            *d = e->halves[3];
            return;
        }
        e++;
    } while (i-- != 0);
}

void func_801C2E40_ovl_1F0A30(s32 key, u8 *out) {
    CacheEntry *e = D_801D0728_ovl_1F0A30;
    s32 i = 19;

    do {
        if (e->key != 0 && e->key == key) {
            out[0] = e->bytes[0];
            out[1] = e->bytes[1];
            out[2] = e->bytes[2];
            out[3] = e->bytes[3];
            out[4] = e->bytes[4];
            out[5] = e->bytes[5];
            return;
        }
        e++;
    } while (i-- != 0);
}

INCLUDE_ASM("asm/nonmatchings/205220", func_801C2EB0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C33F8_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C3750_ovl_1F0A30);

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif

/* Ages the cache: every loaded part's use count drops by one and parts reaching 0 are freed */
void func_801C3D64_ovl_1F0A30(void) {
    u32 n;
    s32 off;
    u32 i;

    if (D_801D0728_ovl_1F0A30 != NULL) {
        for (n = 0, off = 0; n < 20; n++, off += 0xB0) {
            u8 *e = (u8 *)D_801D0728_ovl_1F0A30 + off;

            if (FIELD(e, s32, 0) == 0) {
                continue;
            }
            for (i = 0; i < FIELD(e, u32, 0x18); i++) {
                if (FIELD(e, void **, 0x38)[i] != NULL) {
                    if (--FIELD(e, u8 *, 0x60)[i] == 0) {
                        HFree(FIELD(e, void **, 0x38)[i]);
                        FIELD(e, void **, 0x38)[i] = NULL;
                    }
                }
                if (FIELD(e, void **, 0x3C)[i] != NULL) {
                    if (--FIELD(e, u8 *, 0x64)[i] == 0) {
                        HFree(FIELD(e, void **, 0x3C)[i]);
                        FIELD(e, void **, 0x3C)[i] = NULL;
                    }
                }
                if (FIELD(e, void **, 0x40)[i] != NULL) {
                    if (--FIELD(e, u8 *, 0x68)[i] == 0) {
                        HFree(FIELD(e, void **, 0x40)[i]);
                        FIELD(e, void **, 0x40)[i] = NULL;
                    }
                }
            }
            for (i = 0; i < 10; i++) {
                if (FIELD(e + i * 4, void *, 0x70) != NULL) {
                    if (--FIELD(e + i, u8, 0x98) == 0) {
                        HFree(FIELD(e + i * 4, void *, 0x70));
                        FIELD(e + i * 4, void *, 0x70) = NULL;
                    }
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/205220", func_801C3F3C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C41C8_ovl_1F0A30);

#define CE205(o) ((o) + (u8 *)D_801D0728_ovl_1F0A30)


/* Frees every cache entry's per-item buffers (0x38/0x3C/0x40 lists of 0x18 items) and its ten
 * buffers at 0x70 */
void func_801C45E0_ovl_1F0A30(void) {
    s32 off;
    s32 j;

    if (D_801D0728_ovl_1F0A30 != NULL) {
        for (off = 0; off < 0xDC0; off += 0xB0) {
            for (j = 0; j < FIELD(CE205A(off), u32, 0x18); j++) {
                if (FIELD(CE205A(off), void **, 0x38)[j] != NULL) {
                    HFree(FIELD(CE205A(off), void **, 0x38)[j]);
                    FIELD(CE205A(off), void **, 0x38)[j] = NULL;
                }
                if (FIELD(CE205A(off), void **, 0x3C)[j] != NULL) {
                    HFree(FIELD(CE205A(off), void **, 0x3C)[j]);
                    FIELD(CE205A(off), void **, 0x3C)[j] = NULL;
                }
                if (FIELD(CE205A(off), void **, 0x40)[j] != NULL) {
                    HFree(FIELD(CE205A(off), void **, 0x40)[j]);
                    FIELD(CE205A(off), void **, 0x40)[j] = NULL;
                }
            }
            j = 0;
            {
                s32 o = off;

                for (; j < 10; j++) {
                    if (FIELD(CE205A(o) + j * 4, void *, 0x70) != NULL) {
                        HFree(FIELD(CE205A(o) + j * 4, void *, 0x70));
                        FIELD(CE205A(o) + j * 4, void *, 0x70) = NULL;
                    }
                }
            }
        }
    }
}

#define CE205D(o) ((u8 *)((o) + (u32)D_801D0728_ovl_1F0A30))
void bzero(void *p, s32 n);

/* Frees and clears every cache entry with key a */
void func_801C4778_ovl_1F0A30(s32 a) {
    s32 off;
    s32 j;

    if (D_801D0728_ovl_1F0A30 != NULL) {
        for (off = 0; off < 0xDC0; off += 0xB0) {
            if (FIELD(CE205D(off), s32, 0) == a) {
                for (j = 0; j < FIELD(CE205D(off), u32, 0x18); j++) {
                    if (FIELD(CE205D(off), void **, 0x38)[j] != NULL) {
                        HFree(FIELD(CE205D(off), void **, 0x38)[j]);
                        FIELD(CE205D(off), void **, 0x38)[j] = NULL;
                    }
                    if (FIELD(CE205D(off), void **, 0x3C)[j] != NULL) {
                        HFree(FIELD(CE205D(off), void **, 0x3C)[j]);
                        FIELD(CE205D(off), void **, 0x3C)[j] = NULL;
                    }
                    if (FIELD(CE205D(off), void **, 0x40)[j] != NULL) {
                        HFree(FIELD(CE205D(off), void **, 0x40)[j]);
                        FIELD(CE205D(off), void **, 0x40)[j] = NULL;
                    }
                }
                j = 0;
                {
                    s32 o = off;

                    for (; j < 10; j++) {
                        if (FIELD(CE205D(o) + j * 4, void *, 0x70) != NULL) {
                            HFree(FIELD(CE205D(o) + j * 4, void *, 0x70));
                            FIELD(CE205D(o) + j * 4, void *, 0x70) = NULL;
                        }
                    }
                }
                HFree(FIELD(CE205D(off), void *, 0x8));
                HFree(FIELD(CE205D(off), void *, 0x48));
                HFree(FIELD(CE205D(off), void *, 0x44));
                HFree(FIELD(CE205D(off), void *, 0x6C));
                HFree(FIELD(CE205D(off), void *, 0x2C));
                bzero((u8 *)D_801D0728_ovl_1F0A30 + off, 0xB0);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/205220", func_801C49A0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C5078_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C5470_ovl_1F0A30);

void func_801C58F0_ovl_1F0A30(void) {
    D_801D06B0_ovl_1F0A30[7] = -1;
    D_801D06B0_ovl_1F0A30[6] = -1;
    D_801D06B0_ovl_1F0A30[5] = -1;
    D_801D06B0_ovl_1F0A30[4] = -1;
    D_801D06B0_ovl_1F0A30[3] = -1;
    D_801D06B0_ovl_1F0A30[2] = -1;
    D_801D06B0_ovl_1F0A30[1] = -1;
    D_801D06B0_ovl_1F0A30[0] = -1;
}

/* Remembers the sound requested on channel ch (restarted by func_801C5A20); with no channel it is
 * played straight away unless the game state is 12 */
void SoundRequest(u8 *ch, s32 sound) {
    if (ch == D_800EB240) {
        D_801D06B0_ovl_1F0A30[5] = sound;
    } else if (ch == D_800EB290) {
        D_801D06B0_ovl_1F0A30[6] = sound;
    } else if (ch == NULL) {
        if (D_800E810E != 12) {
            func_800EA604(NULL, sound);
        }
    } else if (ch == D_800EB0B0) {
        D_801D06B0_ovl_1F0A30[0] = sound;
    } else if (ch == D_800EB100) {
        D_801D06B0_ovl_1F0A30[1] = sound;
    } else if (ch == D_800EB150) {
        D_801D06B0_ovl_1F0A30[2] = sound;
    } else if (ch == D_800EB1A0) {
        D_801D06B0_ovl_1F0A30[3] = sound;
    } else {
        D_801D06B0_ovl_1F0A30[4] = sound;
    }
}

/* Starts the saved sound (-1 = none) on each of the seven sound channels */
void func_801C5A20_ovl_1F0A30(void) {
    if (D_801D06B0_ovl_1F0A30[0] >= 0) {
        func_800EA6B0(D_800EB0B0, D_801D06B0_ovl_1F0A30[0], 10);
    }
    if (D_801D06B0_ovl_1F0A30[1] >= 0) {
        func_800EA6B0(D_800EB100, D_801D06B0_ovl_1F0A30[1], 10);
    }
    if (D_801D06B0_ovl_1F0A30[2] >= 0) {
        func_800EA604(D_800EB150, D_801D06B0_ovl_1F0A30[2]);
    }
    if (D_801D06B0_ovl_1F0A30[3] >= 0) {
        func_800EA604(D_800EB1A0, D_801D06B0_ovl_1F0A30[3]);
    }
    if (D_801D06B0_ovl_1F0A30[4] >= 0) {
        func_800EA604(D_800EB1F0, D_801D06B0_ovl_1F0A30[4]);
    }
    if (D_801D06B0_ovl_1F0A30[5] >= 0) {
        func_800EA604(D_800EB240, D_801D06B0_ovl_1F0A30[5]);
    }
    if (D_801D06B0_ovl_1F0A30[6] >= 0) {
        func_800EA604(D_800EB290, D_801D06B0_ovl_1F0A30[6]);
    }
}
