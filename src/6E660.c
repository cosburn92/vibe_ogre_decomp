#include "common.h"
#include "tables.h"

/* ovl_06E660 */

typedef struct {
    /* 0x000 */ u32 count;
    /* 0x004 */ u8 unk004[0x408];
    /* 0x40C */ void *frames[0x20];
} SpriteEntry; /* size 0x48C */

typedef struct {
    /* 0x00 */ u32 count;
    /* 0x04 */ SpriteEntry entries[1];
} SpriteTable;

extern u16 *D_8019A798_ovl_06E660;
extern void *D_8019A790_ovl_06E660;
extern void *D_8019A794_ovl_06E660;

void *HMalloc(s32 size);
void *HFree(void *p);
void _bcopy(void *src, void *dst, s32 n);
u32 ChunkSize(u32 handle);
void *LoadChunkRaw(void *dst, u32 handle);
u8 *func_80197DE4_ovl_06E660(u8 *desc, u32 index);
void func_801997D0_ovl_06E660(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 mode);

/* Sprite animation player state */
typedef struct {
    /* 0x00 */ u8 *script;
    /* 0x04 */ s16 pc;
    /* 0x06 */ s16 x;
    /* 0x08 */ s16 y;
    /* 0x0A */ u8 loops;
    /* 0x0B */ u8 alpha;
    /* 0x0C */ u8 unk0C;
    /* 0x0D */ u8 frame;
    /* 0x0E */ u8 wait;
    /* 0x0F */ u8 state; /* 0 stopped, bit 7 restart */
} SpriteAnim;

/* Steps a sprite animation script. Pairs (op, arg): op < 0xF0 shows frame op for arg ticks;
 * F0 stop, F1 set loop count, F2/F3 set x/y, F4/F5 subtract from x/y, F6 set alpha,
 * F7 add to alpha (clamped), F8 jump, F9 loop back while the count lasts. */
#ifdef NON_MATCHING
/* anim script step: op/arg registers (a1/a2) swapped */
s32 func_80197B70_ovl_06E660(SpriteAnim *a) {
    u8 done;
    u8 op;
    u8 arg;
    u8 v;

    if (a->state == 0) {
        return 0;
    }
    if (a->state & 0x80) {
        a->state = 1;
        a->y = 0;
        a->x = 0;
        a->pc = -1;
        a->wait = 0;
    }
    if (a->wait == 0 || --a->wait == 0) {
        done = 0;
        a->pc++;
        do {
            op = a->script[a->pc * 2];
            arg = a->script[a->pc * 2 + 1];
            if (op < 0xF0) {
                done++;
                a->frame = op;
                a->wait = arg;
                continue;
            }
            a->pc++;
            switch (op) {
                case 0xF0:
                    a->state = 0;
                    done++;
                    break;
                case 0xF1:
                    a->loops = arg;
                    break;
                case 0xF2:
                    a->x = (s8)arg;
                    break;
                case 0xF3:
                    a->y = (s8)arg;
                    break;
                case 0xF4:
                    a->x -= (s8)arg;
                    break;
                case 0xF5:
                    a->y -= (s8)arg;
                    break;
                case 0xF6:
                    a->alpha = arg;
                    break;
                case 0xF7:
                    if ((s8)arg < 0) {
                        v = a->alpha + arg;
                        if (a->alpha + (s8)arg < 0) {
                            v = 0;
                        }
                    } else {
                        v = a->alpha + arg;
                        if (a->alpha + (s8)arg >= 0x100) {
                            v = 0xFF;
                        }
                    }
                    a->alpha = v;
                    break;
                case 0xF9:
                    if (--a->loops == 0) {
                        break;
                    }
                case 0xF8:
                    a->pc = arg;
                    break;
            }
        } while (done == 0);
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/6E660", func_80197B70_ovl_06E660);
#endif

void func_80197D20_ovl_06E660(void) {
    u16 *tmp = HMalloc(ChunkSize(0x315736));
    u32 o;

    LoadChunkRaw(tmp, 0x315736);
    D_8019A798_ovl_06E660 = HMalloc(tmp[0x16 / 2]);
    _bcopy(tmp, D_8019A798_ovl_06E660, tmp[0x16 / 2]);
    o = D_8019A798_ovl_06E660[0];
    D_8019A790_ovl_06E660 = (u8 *)D_8019A798_ovl_06E660 + o;
    o = D_8019A798_ovl_06E660[2];
    D_8019A794_ovl_06E660 = (u8 *)D_8019A798_ovl_06E660 + o;
    HFree(tmp);
}

void func_80197DB8_ovl_06E660(void) {
    HFree(D_8019A798_ovl_06E660);
    D_8019A798_ovl_06E660 = NULL;
}

/* Texture set: [2] count, [3] flags (1 image, 2 4-bit, 4 8-bit), u16 width at 4, height at 6;
 * each image header has its own flags (1 texels, 2 second plane, 4 palette). Returns image index. */
u8 *func_80197DE4_ovl_06E660(u8 *t, u32 page) {
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

/* Returns the palette that follows the image data of the texture described by desc */
u8 *func_80197F08_ovl_06E660(u8 *desc, u32 index) {
    u8 *tex = func_80197DE4_ovl_06E660(desc, index);
    u32 w;
    u32 h;
    u32 rowBytes;

    if (tex == NULL) {
        return NULL;
    }
    w = *(u16 *)(desc + 4);
    h = *(u16 *)(desc + 6);
    if (tex[3] & 2) {
        if (!(tex[3] & 1)) {
            return tex + 8;
        }
        if (desc[3] & 2) {
            rowBytes = (w + 3) / 4 * 16;
        } else if (desc[3] & 4) {
            rowBytes = (w + 7) / 8 * 8;
        } else {
            rowBytes = (w + 3) / 4 * 8;
        }
        return tex + (rowBytes * h + 8);
    }
    return NULL;
}

/* Returns the palette of image index */
u8 *func_80197FB4_ovl_06E660(u8 *desc, u32 index) {
    u32 w = *(u16 *)(desc + 4);
    u32 h = *(u16 *)(desc + 6);
    u8 *tex = func_80197DE4_ovl_06E660(desc, index);
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
        u8 *_e = func_80197DE4_ovl_06E660(t, index); \
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
u8 *func_801980AC_ovl_06E660(u8 *t, u32 index) {
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
    e = func_80197DE4_ovl_06E660(t, index);
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
    base = func_801980AC_ovl_06E660(t, e[2]);
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
        ssrc = func_80197F08_ovl_06E660(t, index);
        TEXSET_TEXELS(prev, base, 0);
        sprev = func_80197F08_ovl_06E660(base, 0);
        TEXSET_TEXELS(dst, out, 0);
        sdst = func_80197F08_ovl_06E660(out, 0);
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
            _bcopy(func_80197FB4_ovl_06E660(t, index), func_80197FB4_ovl_06E660(out, 0), 0x200);
        }
    } else if (!(f & 6)) {
        u8 *src;
        u8 *ssrc;
        u8 *prev;
        u8 *sprev;
        u8 *dst;
        u8 *sdst;

        TEXSET_TEXELS(src, t, index);
        ssrc = func_80197F08_ovl_06E660(t, index);
        TEXSET_TEXELS(prev, base, 0);
        sprev = func_80197F08_ovl_06E660(base, 0);
        TEXSET_TEXELS(dst, out, 0);
        sdst = func_80197F08_ovl_06E660(out, 0);
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

/* Tints an RGBA colour towards blue-grey by its brightest channel, keeping alpha */
/* The red and green results use swapped registers (a3/t0). */
/* Tints an RGBA colour towards blue-grey by its brightest channel, keeping alpha.
 * Form adapted from OB64-Decomp func_00202198 (MIT, (c) 2026 rempred). */
u32 func_8019898C_ovl_06E660(u32 rgba) {
    s32 g = (rgba >> 16) & 0xFF;
    s32 r;
    s32 b = (rgba >> 8) & 0xFF;
    u32 a = rgba & 0xFF;
    s32 max = rgba >> 24;

    if (max < g) {
        max = g;
    }
    if (max < b) {
        max = b;
    }
    if (max < 128) {
        r = max * 112 / 128 + 24;
        g = max * 112 / 128 + 28;
        b = max * 96 / 128 + 8;
    } else {
        r = max * 80 / 128 + 56;
        g = max * 80 / 128 + 60;
        b = max * 80 / 128 + 40;
    }
    r <<= 8;
    return (((u32)r << 16) + ((u32)g << 16) + ((u32)b << 8)) | a;
}

INCLUDE_ASM("asm/nonmatchings/6E660", func_80198A4C_ovl_06E660);

INCLUDE_ASM("asm/nonmatchings/6E660", func_80198FA4_ovl_06E660);

typedef struct {
    /* 0x00 */ u32 id;
    /* 0x04 */ u32 handle;
    /* 0x08 */ u32 *p08;
    /* 0x0C */ u32 kind;
    /* 0x10 */ u32 unk10;
    /* 0x14 */ u32 unk14;
    /* 0x18 */ u32 count;
    /* 0x1C */ u32 unk1C;
    /* 0x20 */ u32 unk20;
    /* 0x24 */ u32 unk24;
    /* 0x28 */ u8 *p28;
    /* 0x2C */ u8 *p2C;
    /* 0x30 */ u8 unk30[4];
    /* 0x34 */ void **parts;
    /* 0x38 */ u8 *p38;
    /* 0x3C */ u8 *p3C;
    /* 0x40 */ void *p40;
    /* 0x44 */ void *p44;
    /* 0x48 */ u8 *p48;
    /* 0x4C */ u8 *p4C;
    /* 0x50 */ void *p50;
} Model6E;

void *LoadChunk(s32 handle);
u8 func_8016F5E0(u16 id);
void bzero(void *, s32);

static inline u16 ModelId(s32 a, s32 b, s32 c, s32 d) {
    return *(u16 *)(((gClassTable[a].baseClass == b ? c * 2 + a * 4 : c * 2 + b * 4) + d) * 2 + (s32)D_8019A790_ovl_06E660);
}

#ifdef NON_MATCHING
/* same size, 6 instructions differ: the original computes the kind (id >> 12) in v1 and the palette table
 * address in v0, swapped here */
/* Model header for class a (or its base class b), variant c/d, palette e: looks the model id up in the
 * id table, loads the model chunk, its four sub-chunks and a work buffer split into five parts */
Model6E *func_80199354_ovl_06E660(Model6E *out, s32 a, s32 b, s32 c, s32 d, s32 e) {
    u32 *idx;
    u32 *hdr;
    u32 *data;
    u32 n;
    s32 rows;
    s32 ptrs;
    s32 total;

    out->id = ModelId(a, b, c, d) & 0xFFF;
    if (out->id == 0) {
        return NULL;
    }
    idx = HMalloc(ChunkSize(0x3B6CD0));
    LoadChunkRaw(idx, 0x3B6CD0);
    out->handle = idx[out->id - 1];
    hdr = HMalloc(ChunkSize(out->handle));
    out->p08 = hdr;
    if (hdr == NULL) {
        HFree(idx);
        return NULL;
    }
    LoadChunkRaw(hdr, out->handle);
    HFree(idx);
    out->p44 = LoadChunk(out->p08[0]);
    out->p40 = LoadChunk(out->p08[1]);
    data = LoadChunk(out->p08[2]);
    out->p50 = LoadChunk(out->p08[3]);
    out->kind = ModelId(a, b, c, d) >> 12;
    out->unk10 = *(u8 *)((s32)D_8019A794_ovl_06E660 + e);
    out->unk14 = func_8016F5E0(e);
    out->count = data[0];
    out->unk1C = data[1];
    out->unk20 = data[2];
    out->unk24 = data[3];
    n = out->count;
    rows = (n + 7) & ~7;
    ptrs = (n * 4 + 7) & ~7;
    total = ptrs + rows + rows + rows + rows;
    out->p28 = HMalloc(total);
    out->p2C = out->p28 + total;
    out->parts = (void **)out->p28;
    out->p48 = (u8 *)out->parts + ptrs;
    out->p3C = out->p48 + rows;
    out->p4C = out->p3C + rows;
    out->p38 = out->p4C + rows;
    bzero(out->parts, ptrs);
    bzero(out->p3C, rows);
    bzero(out->p38, rows);
    _bcopy(data + 8, out->p48, out->count);
    _bcopy((u8 *)data + data[7], out->p4C, out->count);
    HFree(data);
    return out;
}
#else
INCLUDE_ASM("asm/nonmatchings/6E660", func_80199354_ovl_06E660);
#endif

Model6E *func_80199354_ovl_06E660(Model6E *out, s32 a, s32 b, s32 c, s32 d, s32 e);
s32 func_80198FA4_ovl_06E660(SpriteEntry *dst, Model6E *m, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);
void func_80199E00_ovl_06E660(SpriteTable *t);

static inline void FreeModel6E(Model6E *m) {
    u32 i;

    for (i = 0; i < m->count; i++) {
        HFree(m->parts[i]);
    }
    HFree(m->p08);
    HFree(m->p44);
    HFree(m->p40);
    HFree(m->p50);
    HFree(m->p28);
}

/* Loads the model for (a..e) into a local header and builds a one-entry sprite table from it (frame data via
 * func_80198FA4); frees the model either way and returns NULL on failure */
SpriteTable *func_80199624_ovl_06E660(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    Model6E tmp;
    Model6E *m = func_80199354_ovl_06E660(&tmp, a, b, c, d, e);
    SpriteTable *t;

    if (m == NULL) {
        return NULL;
    }
    t = HMalloc(0xDA8);
    bzero(t, 0xDA8);
    if (func_80198FA4_ovl_06E660(t->entries, m, a, b, c, d, e, f, 0) == 0) {
        func_80199E00_ovl_06E660(t);
        FreeModel6E(m);
        return NULL;
    }
    t->count = 1;
    FreeModel6E(m);
    return t;
}

INCLUDE_ASM("asm/nonmatchings/6E660", func_801997D0_ovl_06E660);

void func_80199D74_ovl_06E660(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    func_801997D0_ovl_06E660(a, b, c, d, e, f, 0);
}

void func_80199DA0_ovl_06E660(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    func_801997D0_ovl_06E660(a, b, c, d, e, f, 1);
}

void func_80199DD0_ovl_06E660(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    func_801997D0_ovl_06E660(a, b, c, d, e, f, 2);
}

void func_80199E00_ovl_06E660(SpriteTable *t) {
    u32 i;
    u32 j;

    if (t != NULL) {
        for (i = 0; i < t->count; i++) {
            for (j = 0; j < t->entries[i].count; j++) {
                HFree(t->entries[i].frames[j]);
            }
        }
        HFree(t);
    }
}

INCLUDE_ASM("asm/nonmatchings/6E660", func_80199E98_ovl_06E660);
