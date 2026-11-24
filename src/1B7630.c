#include "common.h"

/* 1B7630 */

u8 *func_80219F40_ovl_1B2670(u8 *t, u32 page);
typedef struct {
    /* 0x00 */ u16 sec0;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u16 sec1;
    /* 0x06 */ u8 unk06[0x10];
    /* 0x16 */ u16 size;
} TblHdr;
extern TblHdr *D_8021C9E8_ovl_1B2670;
extern u8 *D_8021C9E0_ovl_1B2670;
extern u8 *D_8021C9E4_ovl_1B2670;
s32 ChunkSize(s32 id);
void *LoadChunkRaw(void *dst, s32 id);
void *HMalloc(s32 size);
void HFree(void *p);
void bzero(void *p, s32 n);
void _bcopy(const void *src, void *dst, s32 n);
void *func_8021B5EC_ovl_1B2670(s32 a, s32 b, s32 c, s32 d, s32 e);
/* --- end decls --- */

/* Page `page` of image bank t (pages are 8-byte headers followed by pixels, sub-image and palette as flagged) */
u8 *func_80219F40_ovl_1B2670(u8 *t, u32 page) {
    u32 w;
    s32 h;
    u32 pix;
    u32 sub;
    u32 off;
    u32 i;
    u8 *e;
    u8 f;
    u8 g;

    if (t == NULL) {
        return NULL;
    }
    f = t[3];
    w = *(u16 *)(t + 4);
    h = *(u16 *)(t + 6);
    if (f & 2) {
        pix = ((w + 3) >> 2 << 4) * h;
        sub = 0;
    } else if (f & 4) {
        pix = ((w + 7) >> 3 << 3) * h;
        if (f & 1) {
            sub = ((w + 15) >> 4 << 3) * h;
        } else {
            sub = pix;
        }
    } else {
        pix = ((w + 3) >> 2 << 3) * h;
        if (f & 1) {
            sub = ((w + 15) >> 4 << 3) * h;
        } else {
            sub = ((w + 7) >> 3 << 3) * h;
        }
    }
    off = 8;
    e = t + 8;
    for (i = 0; i < t[2]; i++) {
        if (i == page) {
            return e;
        }
        g = e[3];
        off += 8;
        if (g & 1) {
            off += pix;
        }
        if (g & 2) {
            off += sub;
        }
        if (g & 4) {
            off += 0x200;
        }
        e = t + off;
    }
    return NULL;
}

/* Palette that follows the pixel data of image t's page (NULL if the page has none) */
u8 *func_8021A064_ovl_1B2670(u8 *t, u32 page) {
    u8 *e = func_80219F40_ovl_1B2670(t, page);
    u16 w;
    s32 h;
    s32 stride;

    if (e == NULL) {
        return NULL;
    }
    w = *(u16 *)(t + 4);
    h = *(u16 *)(t + 6);
    if (e[3] & 2) {
        if (!(e[3] & 1)) {
            return e + 8;
        }
        if (t[3] & 2) {
            stride = ((u32)(w + 3) >> 2) << 4;
        } else if (t[3] & 4) {
            stride = ((u32)(w + 7) >> 3) << 3;
        } else {
            stride = ((u32)(w + 3) >> 2) << 3;
        }
        return e + (stride * h + 8);
    }
    return NULL;
}

/* Returns the palette of image index */
u8 *func_8021A110_ovl_1B2670(u8 *desc, u32 index) {
    u32 w = *(u16 *)(desc + 4);
    u32 h = *(u16 *)(desc + 6);
    u8 *tex = func_80219F40_ovl_1B2670(desc, index);
    u32 off;

    if (tex == NULL) {
        return NULL;
    }
    off = 8;
    if (tex[3] & 1) {
        if (desc[3] & 2) {
            off = h * (((w + 3) >> 2) << 4) + 8;
        } else if (desc[3] & 4) {
            off = h * (((w + 7) >> 3) << 3) + 8;
        } else {
            off = h * (((w + 3) >> 2) << 3) + 8;
        }
    }
    if (tex[3] & 2) {
        if (desc[3] & 1) {
            off += h * (((w + 15) >> 4) << 3);
        } else {
            off += h * (((w + 7) >> 3) << 3);
        }
    }
    if (tex[3] & 4) {
        return tex + off;
    }
    return NULL;
}

/* Texels of image index in texture set t, or NULL when the image has none */
#define TEXSET_TEXELS(p, t, index)                   \
    {                                                \
        u8 *_e = func_80219F40_ovl_1B2670(t, index); \
        if (_e == NULL) {                            \
            p = NULL;                                \
        } else {                                     \
            p = NULL;                                \
            if (_e[3] & 1) {                         \
                p = _e + 8;                          \
            }                                        \
        }                                            \
    }

/* Decodes image index of texture set t into a new one-image set. An image that names itself as
 * its reference is copied as is; otherwise its reference is decoded first (recursively) and this
 * image's data are applied as deltas: XOR for 32-bit sets, subtraction for 8- and 16-bit texels
 * and for the second (4-bit or 8-bit) plane. Image flag 8 marks texels stored whole. */
u8 *func_8021A208_ovl_1B2670(u8 *t, u32 index) {
    u8 f = t[3];
    u32 w = *(u16 *)(t + 4);
    u32 h = *(u16 *)(t + 6);
    s32 pitch;
    s32 subPitch;
    s32 texBytes;
    s32 subBytes;
    s32 size;
    u8 *e;
    s32 dsize;
    u8 *out;
    u8 *base;
    u8 *hdr;
    u8 g;
    u32 x;
    u32 y;
    u16 half;

    if (f & 2) {
        pitch = ((u32)(w + 3) >> 2) * 16;
        subPitch = 0;
    } else if (f & 4) {
        pitch = ((u32)(w + 7) >> 3) * 8;
        if (f & 1) {
            subPitch = ((u32)(w + 15) >> 4) * 8;
        } else {
            subPitch = pitch;
        }
    } else {
        pitch = ((u32)(w + 3) >> 2) * 8;
        if (f & 1) {
            subPitch = ((u32)(w + 15) >> 4) * 8;
        } else {
            subPitch = ((u32)(w + 7) >> 3) * 8;
        }
    }
    texBytes = pitch * h;
    e = func_80219F40_ovl_1B2670(t, index);
    subBytes = subPitch * h;
    if (index == e[2]) {
        g = e[3];
        size = 0x10;
        if (g & 1) {
            size = texBytes + 0x10;
        }
        if (g & 2) {
            size += subBytes;
        }
        if (g & 4) {
            size += 0x200;
        }
        out = HMalloc(size);
        _bcopy(t, out, 8);
        out[2] = 1;
        _bcopy(e, out + 8, size - 8);
        out[10] = 0;
        return out;
    }
    base = func_8021A208_ovl_1B2670(t, e[2]);
    g = e[3];
    dsize = 0x10;
    if (g & 1) {
        dsize = texBytes + 0x10;
    }
    if (g & 2) {
        dsize += subBytes;
    }
    if (g & 4) {
        dsize += 0x200;
    }
    out = HMalloc(dsize);
    _bcopy(t, out, 8);
    hdr = out + 8;
    out[2] = 1;
    _bcopy(e, hdr, 8);
    out[10] = 0;
    f = t[3];
    if (f & 2) {
        u8 *src;
        u8 *prev;
        u8 *dst;

        TEXSET_TEXELS(src, t, index);
        TEXSET_TEXELS(prev, base, 0);
        TEXSET_TEXELS(dst, out, 0);
        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {
                ((u32 *)dst)[x] = ((u32 *)prev)[x] ^ ((u32 *)src)[x];
            }
            dst += pitch;
            prev += pitch;
            src += pitch;
        }
    } else if (f & 4) {
        u8 *src;
        u8 *ssrc;
        u8 *prev;
        u8 *sprev;
        u8 *dst;
        u8 *sdst;

        TEXSET_TEXELS(src, t, index);
        ssrc = func_8021A064_ovl_1B2670(t, index);
        TEXSET_TEXELS(prev, base, 0);
        sprev = func_8021A064_ovl_1B2670(base, 0);
        TEXSET_TEXELS(dst, out, 0);
        sdst = func_8021A064_ovl_1B2670(out, 0);
        g = hdr[3];
        if (g & 1) {
            if (g & 8) {
                for (y = 0; y < h; y++) {
                    for (x = 0; x < w; x++) {
                        dst[x] = src[x];
                    }
                    dst += pitch;
                    src += pitch;
                }
            } else {
                for (y = 0; y < h; y++) {
                    for (x = 0; x < w; x++) {
                        dst[x] = prev[x] - src[x];
                    }
                    dst += pitch;
                    prev += pitch;
                    src += pitch;
                }
            }
        }
        if (hdr[3] & 2) {
            if (t[3] & 1) {
                half = (w + 1) >> 1;
                for (y = 0; y < h; y++) {
                    for (x = 0; x < half; x++) {
                        u8 hi = ((sprev[x] & 0xF0) - (ssrc[x] & 0xF0)) & ~0xF;
                        u8 lo = ((sprev[x] & 0xF) - (ssrc[x] & 0xF)) & 0xF;

                        sdst[x] = lo | hi;
                    }
                    sdst += subPitch;
                    sprev += subPitch;
                    ssrc += subPitch;
                }
            } else {
                for (y = 0; y < h; y++) {
                    for (x = 0; x < w; x++) {
                        sdst[x] = sprev[x] - ssrc[x];
                    }
                    sdst += subPitch;
                    sprev += subPitch;
                    ssrc += subPitch;
                }
            }
        }
        if (hdr[3] & 4) {
            _bcopy(func_8021A110_ovl_1B2670(t, index), func_8021A110_ovl_1B2670(out, 0), 0x200);
        }
    } else if (!(f & 6)) {
        u8 *src;
        u8 *ssrc;
        u8 *prev;
        u8 *sprev;
        u8 *dst;
        u8 *sdst;

        TEXSET_TEXELS(src, t, index);
        ssrc = func_8021A064_ovl_1B2670(t, index);
        TEXSET_TEXELS(prev, base, 0);
        sprev = func_8021A064_ovl_1B2670(base, 0);
        TEXSET_TEXELS(dst, out, 0);
        sdst = func_8021A064_ovl_1B2670(out, 0);
        g = hdr[3];
        if (g & 1) {
            if (g & 8) {
                for (y = 0; y < h; y++) {
                    for (x = 0; x < w; x++) {
                        ((u16 *)dst)[x] = ((u16 *)src)[x];
                    }
                    dst += pitch;
                    src += pitch;
                }
            } else {
                for (y = 0; y < h; y++) {
                    for (x = 0; x < w; x++) {
                        ((u16 *)dst)[x] = ((u16 *)prev)[x] - ((u16 *)src)[x];
                    }
                    dst += pitch;
                    src += pitch;
                    prev += pitch;
                }
            }
        }
        if (hdr[3] & 2) {
            if (t[3] & 1) {
                half = (w + 1) >> 1;
                for (y = 0; y < h; y++) {
                    for (x = 0; x < half; x++) {
                        u8 hi = ((sprev[x] & 0xF0) - (ssrc[x] & 0xF0)) & ~0xF;
                        u8 lo = ((sprev[x] & 0xF) - (ssrc[x] & 0xF)) & 0xF;

                        sdst[x] = lo | hi;
                    }
                    sdst += subPitch;
                    sprev += subPitch;
                    ssrc += subPitch;
                }
            } else {
                for (y = 0; y < h; y++) {
                    for (x = 0; x < w; x++) {
                        sdst[x] = sprev[x] - ssrc[x];
                    }
                    sdst += subPitch;
                    sprev += subPitch;
                    ssrc += subPitch;
                }
            }
        }
    }
    HFree(base);
    return out;
}

extern u8 D_80187C59[][0x48]; /* gClassTable[].baseClass */
void *LoadChunk(s32 id);
u8 func_8016F5E0(u16 id);

typedef struct {
    /* 0x00 */ u32 id;
    /* 0x04 */ s32 chunk;
    /* 0x08 */ s32 *chunks;
    /* 0x0C */ u32 kind;
    /* 0x10 */ u32 byte10;
    /* 0x14 */ u32 byte14;
    /* 0x18 */ s32 count;
    /* 0x1C */ s32 hdr1C;
    /* 0x20 */ s32 hdr20;
    /* 0x24 */ s32 hdr24;
    /* 0x28 */ u8 *buf;
    /* 0x2C */ u8 *bufEnd;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ u8 *words;
    /* 0x38 */ u8 *bytes38;
    /* 0x3C */ u8 *bytes3C;
    /* 0x40 */ void *res40;
    /* 0x44 */ void *res44;
    /* 0x48 */ u8 *bytes48;
    /* 0x4C */ u8 *bytes4C;
    /* 0x50 */ void *res50;
} SprRec;
void *func_8021AAE8_ovl_1B2670(void *t, u32 page, void *pal, s32 flags);

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021AAE8_ovl_1B2670);

typedef struct {
    /* 0x00 */ u32 cell;
    /* 0x04 */ s32 x;
    /* 0x08 */ s32 y;
    /* 0x0C */ u32 w;
    /* 0x10 */ u32 h;
    /* 0x14 */ u32 z;
    /* 0x18 */ f32 u;
    /* 0x1C */ f32 v;
} SprPart;

/* part[i] and img[i] overlap past the first part, as in the original */
typedef struct {
    /* 0x00 */ u32 idx;
    /* 0x04 */ u32 n;
    /* 0x08 */ SprPart part[1];
    /* 0x28 */ void *img[1];
} SprFrame;

/* Fills out with frame idx of record r: per part a 0x20-byte entry (cell, x, y, three sizes and
 * two 6.10 fixed-point coordinates) and the part's image converted with a palette chosen by the
 * cell's kind byte (0: id-table kind, 1: entry byte, 2: func_8016F5E0 of e). */
#ifdef NON_MATCHING
/* Same size; register allocation only: the original keeps sel in s3 and the cell index in s4
 * (swapped here), and shifts the 6.10 value's integer part in place. */
SprFrame *func_8021B040_ovl_1B2670(SprFrame *out, SprRec *r, s32 cls, s32 b, s32 c, s32 d, s32 e, u32 idx) {
    u32 *tbl = r->res44;
    u8 *p;
    u32 i;
    u32 k;
    u32 sel = 0;
    u16 v;
    u16 *q;
    u8 *img;

    if (idx >= tbl[0] >> 2) {
        return NULL;
    }
    out->idx = idx;
    p = (u8 *)tbl + tbl[idx];
    out->n = *(u16 *)p;
    p += 2;
    for (i = 0; i < out->n; i++) {
        out->part[i].cell = k = *(u16 *)p;
        out->part[i].x = *(s16 *)(p + 2);
        out->part[i].y = *(s16 *)(p + 4);
        out->part[i].w = *(u16 *)(p + 6);
        out->part[i].h = *(u16 *)(p + 8);
        out->part[i].z = *(u16 *)(p + 10);
        v = *(u16 *)(p + 12);
        out->part[i].u = (s32)(v >> 10) + (s32)(v & 0x3FF) / 1024.0f;
        v = *(u16 *)(p + 14);
        out->part[i].v = (s32)(v >> 10) + (s32)(v & 0x3FF) / 1024.0f;
        p += 16;
        switch (r->bytes48[k]) {
        case 0:
            if (D_80187C59[cls][0] == b) {
                q = (u16 *)((c * 2 + cls * 4 + d) * 2 + (s32)D_8021C9E0_ovl_1B2670);
            } else {
                q = (u16 *)((c * 2 + b * 4 + d) * 2 + (s32)D_8021C9E0_ovl_1B2670);
            }
            sel = *q >> 12;
            break;
        case 1:
            sel = D_8021C9E4_ovl_1B2670[e];
            break;
        case 2:
            sel = func_8016F5E0(e);
            break;
        }
        img = LoadChunk(r->chunks[k + 4]);
        if (sel >= img[2]) {
            sel = 0;
        }
        out->img[i] = func_8021AAE8_ovl_1B2670(img, sel, (u8 *)r->res50 + (r->bytes4C[k] << 9), 0);
        HFree(img);
    }
    return out;
}
#else
INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021B040_ovl_1B2670);
#endif


/* Fills record o for class cls (or for b when cls is not b's base class), variant c/d and
 * entry e: looks up the id in the shared table, loads its chunk list and the four chunks it
 * names, and splits one buffer into a word array and four byte arrays of count entries. */
#ifdef NON_MATCHING
/* Same size; scheduling only: the original loads the table pointer before adding d to the
 * index and before the >> 12, and stores buf then reloads it for words, where this stores
 * words first. */
SprRec *func_8021B31C_ovl_1B2670(SprRec *o, s32 cls, s32 b, s32 c, s32 d, s32 e) {
    s32 *tmp;
    s32 *src;
    s32 n1;
    s32 n4;
    s32 size;
    s32 i;

    if (D_80187C59[cls][0] == b) {
        i = c * 2 + cls * 4 + d;
    } else {
        i = c * 2 + b * 4 + d;
    }
    o->id = ((u16 *)D_8021C9E0_ovl_1B2670)[i] & 0xFFF;
    if (o->id == 0) {
        return NULL;
    }
    tmp = HMalloc(ChunkSize(0x3B6CD0));
    LoadChunkRaw(tmp, 0x3B6CD0);
    o->chunk = tmp[o->id - 1];
    o->chunks = HMalloc(ChunkSize(o->chunk));
    if (o->chunks == NULL) {
        HFree(tmp);
        return NULL;
    }
    LoadChunkRaw(o->chunks, o->chunk);
    HFree(tmp);
    o->res44 = LoadChunk(o->chunks[0]);
    o->res40 = LoadChunk(o->chunks[1]);
    src = LoadChunk(o->chunks[2]);
    o->res50 = LoadChunk(o->chunks[3]);
    if (D_80187C59[cls][0] == b) {
        i = c * 2 + cls * 4 + d;
    } else {
        i = c * 2 + b * 4 + d;
    }
    o->kind = ((u16 *)D_8021C9E0_ovl_1B2670)[i] >> 12;
    o->byte10 = D_8021C9E4_ovl_1B2670[e];
    o->byte14 = func_8016F5E0(e);
    o->count = src[0];
    o->hdr1C = src[1];
    o->hdr20 = src[2];
    o->hdr24 = src[3];
    n1 = (o->count + 7) & ~7;
    n4 = (o->count * 4 + 7) & ~7;
    size = n4 + n1 + n1 + n1 + n1;
    o->buf = HMalloc(size);
    o->words = o->buf;
    o->bufEnd = o->words + size;
    o->bytes48 = o->buf + n4;
    o->bytes3C = o->bytes48 + n1;
    o->bytes4C = o->bytes3C + n1;
    o->bytes38 = o->bytes4C + n1;
    bzero(o->words, n4);
    bzero(o->bytes3C, n1);
    bzero(o->bytes38, n1);
    _bcopy(src + 8, o->bytes48, o->count);
    _bcopy((u8 *)src + src[7], o->bytes4C, o->count);
    HFree(src);
    return o;
}
#else
INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021B31C_ovl_1B2670);
#endif

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021B5EC_ovl_1B2670);

/* Loads the shared table chunk (two sections) and creates the two default entries */
void **func_8021B93C_ovl_1B2670(void) {
    TblHdr *tmp = HMalloc(ChunkSize(0x315736));
    void **r;
    s32 one = 1;
    u32 o;

    LoadChunkRaw(tmp, 0x315736);
    D_8021C9E8_ovl_1B2670 = HMalloc(tmp->size);
    _bcopy(tmp, D_8021C9E8_ovl_1B2670, tmp->size);
    o = D_8021C9E8_ovl_1B2670->sec0;
    D_8021C9E0_ovl_1B2670 = (u8 *)D_8021C9E8_ovl_1B2670 + o;
    o = D_8021C9E8_ovl_1B2670->sec1;
    D_8021C9E4_ovl_1B2670 = (u8 *)D_8021C9E8_ovl_1B2670 + o;
    HFree(tmp);
    r = HMalloc(8);
    bzero(r, 8);
    r[0] = func_8021B5EC_ovl_1B2670(1, 1, 0, 1, one);
    r[1] = func_8021B5EC_ovl_1B2670(1, 1, 0, 0, one);
    return r;
}

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif

/* Frees a table: each of its 0x2C-byte entries owns a list of buffers */
static inline void FreeTable1B7(u8 *t) {
    u32 i;
    u32 j;

    if (t != NULL) {
        for (i = 0; i < FIELD(t, u32, 0x108); i++) {
            for (j = 0; j < FIELD(t + i * 0x2C, u32, 0x110); j++) {
                HFree(FIELD(t + i * 0x2C + j * 4, void *, 0x134));
            }
        }
        HFree(t);
    }
}

/* Frees both tables of set s, the set itself and the shared buffer */
void func_8021BA30_ovl_1B2670(u8 **s) {
    FreeTable1B7(s[0]);
    FreeTable1B7(s[1]);
    HFree(s);
    HFree(D_8021C9E8_ovl_1B2670);
    D_8021C9E8_ovl_1B2670 = NULL;
}

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021BB5C_ovl_1B2670);
