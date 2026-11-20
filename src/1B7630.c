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

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021AAE8_ovl_1B2670);

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021B040_ovl_1B2670);

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021B31C_ovl_1B2670);

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021B5EC_ovl_1B2670);

/* Loads the shared table chunk (two sections) and creates the two default entries */
#ifdef NON_MATCHING
/* Same issue as 6E660 func_80197D20: the original reuses a1 for both section offsets (load, add, load); here the two halfword loads are scheduled together. */
void **func_8021B93C_ovl_1B2670(void) {
    TblHdr *tmp = HMalloc(ChunkSize(0x315736));
    void **r;

    LoadChunkRaw(tmp, 0x315736);
    D_8021C9E8_ovl_1B2670 = HMalloc(tmp->size);
    _bcopy(tmp, D_8021C9E8_ovl_1B2670, tmp->size);
    D_8021C9E0_ovl_1B2670 = (u8 *)D_8021C9E8_ovl_1B2670 + D_8021C9E8_ovl_1B2670->sec0;
    D_8021C9E4_ovl_1B2670 = (u8 *)D_8021C9E8_ovl_1B2670 + D_8021C9E8_ovl_1B2670->sec1;
    HFree(tmp);
    r = HMalloc(8);
    bzero(r, 8);
    r[0] = func_8021B5EC_ovl_1B2670(1, 1, 0, 1, 1);
    r[1] = func_8021B5EC_ovl_1B2670(1, 1, 0, 0, 1);
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021B93C_ovl_1B2670);
#endif

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021BA30_ovl_1B2670);

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021BB5C_ovl_1B2670);
