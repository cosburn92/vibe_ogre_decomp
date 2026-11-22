#include "common.h"

/* 1CE070 */

/* 16 zero bytes (shared rodata splat leaves unmigrated) */
__asm__(".section .rodata\n.global D_801B99A0_ovl_1CE070\nD_801B99A0_ovl_1CE070:\n.word 0, 0, 0, 0\n.section .text\n");

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

typedef struct {
    /* 0x0 */ u8 unk0[4];
    /* 0x4 */ u16 w;
    /* 0x6 */ u16 h;
} SizeCE;

extern Gfx *D_800E9BA0;
extern s32 D_801B8090_ovl_1CE070;
extern s32 D_801B8094_ovl_1CE070;
extern u8 D_801B80B0_ovl_1CE070[];
extern void *D_801BA6F8_ovl_1CE070;
extern u8 D_800A8210;
extern u8 D_800A8211;
extern u8 D_800A8212;
extern s32 D_800C4B20;
extern u8 D_801BA710[];
extern u8 D_80243DB0[];

void *HMalloc(s32 size);
void bzero(void *p, s32 n);
void func_8019898C_ovl_1CE070(SizeCE *s, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
u8 func_8016CD30(void);
void func_8019915C_ovl_1CE070(void);
void func_80076E00(void);
void func_801792BC(void);
void func_8017BF10(void);
void func_80073398(void);
void func_80179058(void);
void func_80070F14(void);
void func_80070C60(void *p, u32 size);
void func_8009DAEC(void);
void func_80179060(void);
void func_8017BDC0(void);
void func_80076E2C(void);
typedef struct {
    /* 0x0 */ u8 unk0[6];
    /* 0x6 */ u16 h6;
    /* 0x8 */ u8 unk8[2];
} RecCE; /* size 0xA */
typedef struct {
    /* 0x00 */ u8 unk0[4];
    /* 0x04 */ u32 n;
    /* 0x08 */ u8 unk8[4];
    /* 0x0C */ RecCE *recs;
    /* 0x10 */ u16 (*links)[2];
} SkelCE;
typedef struct {
    f32 m[4][4];
    s32 pad;
} MtxCE; /* size 0x44 */
extern u8 *D_801B8080_ovl_1CE070;
extern u8 *D_801B8088_ovl_1CE070;
extern u8 *D_801B808C_ovl_1CE070; /* = D_801B8088[1] */
extern u8 *D_801B8084_ovl_1CE070; /* = D_801B8080[1] */
extern u8 D_800E7A0C;
void *HMalloc(s32 size);
void guMtxCatF(void *a, void *b, void *c);
void nuGfxTaskAllEndWait(void);
void func_80072738(s32 a);
void func_80089BC0(void);
void func_80089AB0(void *p, s32 n);
void osViSetSpecialFeatures(u32 f);
void func_8016CD50(s32 a);
extern u8 *D_800A8204[];
extern u8 *D_800C4BB8;
void HFree(void *p);
u8 *func_80199ECC_ovl_1CE070(u8 *t, u32 page);
typedef struct {
    void *name;
    s32 index;
    u8 *buf;
    s32 size;
} Arc16_1CE070;
extern Arc16_1CE070 D_801B99A0_ovl_1CE070;
s32 ChunkSize(s32 id);
void *LoadChunkRaw(void *dst, s32 id);
s32 ReadU32BE(void *p);
void DecodeLZ(void *dst, void *src);
void func_8007ACB0(void *arc, void *reqs, s32 n);
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
/* --- end decls --- */

/* Texture line size in bytes for pixel size siz and width w */
u32 func_80197B70_ovl_1CE070(s32 siz, u32 w) {
    if (siz == 3) {
        return ((w + 3) >> 2) << 4;
    }
    if (siz == 2) {
        return ((w + 3) >> 2) << 3;
    }
    if (siz == 1) {
        return ((w + 7) >> 3) << 3;
    }
    return ((w + 15) >> 4) << 3;
}

/* Width rounded up to a whole 64-bit line for pixel size siz */
u32 func_80197BC4_ovl_1CE070(s32 siz, u32 w) {
    if (siz == 3) {
        return ((w + 3) >> 2) << 2;
    }
    if (siz == 2) {
        return ((w + 3) >> 2) << 2;
    }
    if (siz == 1) {
        return ((w + 7) >> 3) << 3;
    }
    return ((w + 15) >> 4) << 4;
}

/* Texture size in bytes */
u32 func_80197C14_ovl_1CE070(s32 siz, u32 w, s32 h) {
    u32 r;

    if (siz == 3) {
        r = ((w + 3) >> 2) << 4;
    } else if (siz == 2) {
        r = ((w + 3) >> 2) << 3;
    } else if (siz == 1) {
        r = ((w + 7) >> 3) << 3;
    } else {
        r = ((w + 15) >> 4) << 3;
    }
    return r * h;
}

INCLUDE_ASM("asm/nonmatchings/1CE070", func_80197C74_ovl_1CE070);

/* Loads chunk id and unpacks it: LHa archives ("-lh") through func_8007ACB0, otherwise LZ */
void *func_801985D0_ovl_1CE070(s32 id) {
    s32 size = ChunkSize(id);
    u8 *raw = HMalloc(size);
    void *out;

    LoadChunkRaw(raw, id);
    if (raw[2] == '-' && raw[3] == 'l' && raw[4] == 'h') {
        Arc16_1CE070 arc = D_801B99A0_ovl_1CE070;
        Arc16_1CE070 req = D_801B99A0_ovl_1CE070;

        arc.buf = raw;
        arc.size = size;
        func_8007ACB0(&arc, &req, 1);
        out = req.buf;
    } else {
        out = HMalloc(ReadU32BE(raw));
        DecodeLZ(out, raw);
    }
    HFree(raw);
    return out;
}

/* Loads entry k of the index chunk id and unpacks it like func_801985D0; stores the unpacked
 * size in *outSize when given */
#ifdef NON_MATCHING
/* 88/88 instructions, 24 words differ: k and the chunk buffers swap s0/s2 */
void *func_801986E0_ovl_1CE070(s32 id, s32 k, s32 *outSize) {
    s32 *index = HMalloc(ChunkSize(id));
    s32 size;
    u8 *raw;
    void *out;
    s32 n;

    LoadChunkRaw(index, id);
    k = index[k];
    HFree(index);
    size = ChunkSize(k);
    raw = HMalloc(size);
    LoadChunkRaw(raw, k);
    if (raw[2] == '-' && raw[3] == 'l' && raw[4] == 'h') {
        Arc16_1CE070 arc = D_801B99A0_ovl_1CE070;
        Arc16_1CE070 req = D_801B99A0_ovl_1CE070;

        arc.buf = raw;
        arc.size = size;
        func_8007ACB0(&arc, &req, 1);
        out = req.buf;
        n = req.size;
    } else {
        n = ReadU32BE(raw);
        out = HMalloc(n);
        DecodeLZ(out, raw);
    }
    if (outSize != NULL) {
        *outSize = n;
    }
    HFree(raw);
    return out;
}
#else
INCLUDE_ASM("asm/nonmatchings/1CE070", func_801986E0_ovl_1CE070);
#endif

INCLUDE_ASM("asm/nonmatchings/1CE070", func_80198840_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019898C_ovl_1CE070);

void func_80198EAC_ovl_1CE070(SizeCE *s, s32 a, s32 b) {
    func_8019898C_ovl_1CE070(s, 0, 0, s->w, s->h, a, b);
}

void func_80198EE0_ovl_1CE070(void) {
    D_801B8090_ovl_1CE070 = 0;
}

/* Allocates two 0x96000-byte frame buffers (64-byte aligned) and switches the display to them */
void func_80198EEC_ovl_1CE070(void) {
    u8 **raw = &D_801B8088_ovl_1CE070;
    u8 **fb;
    u8 *r0;
    u8 *r1;
    u32 mask;

    raw[0] = HMalloc(0x9603F);
    r1 = (&D_801B8088_ovl_1CE070)[1] = HMalloc(0x9603F);
    r0 = raw[0];
    mask = ~0x3F;
    fb = &D_801B8080_ovl_1CE070;
    (&D_801B8080_ovl_1CE070)[1] = (u8 *)(((u32)r1 + 0x3F) & mask);
    D_800C4B20 = 0;
    D_801B8094_ovl_1CE070 = 0;
    fb[0] = (u8 *)(((u32)r0 + 0x3F) & mask);
    nuGfxTaskAllEndWait();
    func_80072738(9);
    func_80089BC0();
    func_80089AB0(fb, 2);
    osViSetSpecialFeatures(0x9A);
    D_800E7A0C = 0;
    func_8016CD50(1);
    D_801B8090_ovl_1CE070 = 1;
}

/* Same as func_80198EEC, plus a third (capture) buffer */
void func_80198FB4_ovl_1CE070(void) {
    u8 *r0;
    u8 *r1;
    u32 mask;

    D_801B8088_ovl_1CE070 = HMalloc(0x9603F);
    r1 = D_801B808C_ovl_1CE070 = HMalloc(0x9603F);
    r0 = D_801B8088_ovl_1CE070;
    mask = ~0x3F;
    D_801B8084_ovl_1CE070 = (u8 *)(((u32)r1 + 0x3F) & mask);
    D_800C4B20 = 0;
    D_801B8094_ovl_1CE070 = 0;
    D_801B8080_ovl_1CE070 = (u8 *)(((u32)r0 + 0x3F) & mask);
    nuGfxTaskAllEndWait();
    func_80072738(9);
    func_80089BC0();
    func_80089AB0(&D_801B8080_ovl_1CE070, 2);
    osViSetSpecialFeatures(0x9A);
    D_800E7A0C = 0;
    func_8016CD50(1);
    D_801B8090_ovl_1CE070 = 1;
    D_801B8094_ovl_1CE070 = (s32)HMalloc(0x9603F);
}

/* Switches back to the normal frame buffers and frees the high-resolution ones */
void func_80199088_ovl_1CE070(void) {
    u8 **raw;

    nuGfxTaskAllEndWait();
    func_80072738(2);
    func_80089BC0();
    func_80089AB0(D_800A8204, 3);
    D_800E7A0C = 1;
    D_800C4BB8 = D_800A8204[0];
    func_8016CD50(0);
    raw = &D_801B8088_ovl_1CE070;
    D_801B8090_ovl_1CE070 = 1;
    HFree(raw[0]);
    raw[0] = NULL;
    HFree(D_801B808C_ovl_1CE070);
    D_801B808C_ovl_1CE070 = NULL;
    if (D_801B8094_ovl_1CE070 != 0) {
        HFree((void *)D_801B8094_ovl_1CE070);
        D_800C4B20 = 0;
        D_801B8094_ovl_1CE070 = 0;
        D_800A8212 = 0;
        D_800A8211 = 0;
        D_800A8210 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019915C_ovl_1CE070);

void func_801993F0_ovl_1CE070(void) {
    if (func_8016CD30()) {
        D_800A8212 = 1;
        D_800A8211 = 1;
        D_800A8210 = 1;
        if (D_800C4B20 == 0) {
            D_800C4B20 = (D_801B8094_ovl_1CE070 + 0x3F) & ~0x3F;
        }
        func_8019915C_ovl_1CE070();
    }
}

void func_80199460_ovl_1CE070(void) {
    func_80076E00();
    func_801792BC();
    func_8017BF10();
    func_80073398();
    func_80179058();
    func_80070F14();
    func_80070C60(D_801BA710, 0x80400000 - (u32)D_801BA710);
    func_8009DAEC();
}

void func_801994C0_ovl_1CE070(void) {
    func_80073398();
    func_80070F14();
    func_80070C60(D_80243DB0, 0x80400000 - (u32)D_80243DB0);
    func_8009DAEC();
    func_80179060();
    func_8017BDC0();
    func_80076E2C();
}

void func_80199518_ovl_1CE070(void) {
    Gfx *g;

    g = D_800E9BA0++;
    g->w0 = 0xE7000000;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xDC080008;
    g->w1 = (u32)D_801B80B0_ovl_1CE070;
}

INCLUDE_ASM("asm/nonmatchings/1CE070", func_80199560_ovl_1CE070);

/* Effect transform tracks (shapes from OB64-Decomp's E06TransformInput/Output, MIT, (c) 2026 rempred) */
typedef struct {
    f32 m[4][4];
    f32 alpha;
} TrackOut1CE;

typedef struct {
    u32 unk00;
    u32 count;
    void ***curves;
    u8 unk0C[0xC];
    f32 **values;
} TrackIn1CE;

f32 func_80199560_ovl_1CE070(void *curve, f32 t);
void guRotateRPYF(f32 mf[4][4], f32 r, f32 p, f32 h);

static inline void Track1CE_ApplyValues(f32 *v, f32 m[4][4]) {
    guRotateRPYF(m, v[3], v[4], v[5]);
    m[0][0] *= v[0];
    m[0][1] *= v[0];
    m[0][2] *= v[0];
    m[1][0] *= v[1];
    m[1][1] *= v[1];
    m[1][2] *= v[1];
    m[2][0] *= v[2];
    m[2][1] *= v[2];
    m[2][2] *= v[2];
    m[3][0] = v[6];
    m[3][1] = v[7];
    m[3][2] = v[8];
}

static inline void Track1CE_ApplyCurves(f32 t, void **curves, TrackOut1CE *out, f32 *v) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (curves[i] != NULL) {
            v[i] = func_80199560_ovl_1CE070(curves[i], t);
        }
    }
    Track1CE_ApplyValues(v, out->m);
    out->alpha = v[9];
}

/* Evaluates frame `frame` (30 fps) of an effect's transform tracks into 4x4 matrices:
 * each item has 9 base values (scale xyz, rotation xyz, translation xyz) plus an alpha,
 * and any value with a curve is replaced by the curve's value.
 * Structure from OB64-Decomp func_00267FD0 (MIT, (c) 2026 rempred). */
void func_80199968_ovl_1CE070(s32 frame, TrackIn1CE *in, TrackOut1CE *out) {
    f32 values[10];
    f32 t = (f32)frame / 30.0f;
    u32 item;
    u32 k;

    for (item = 0; item < in->count; item++) {
        for (k = 0; k < 9; k++) {
            values[k] = in->values[item][k];
        }
        values[9] = 1.0f;
        if (in->curves[item] != NULL) {
            Track1CE_ApplyCurves(t, in->curves[item], &out[item], values);
        } else {
            Track1CE_ApplyValues(values, out[item].m);
            out[item].alpha = 1.0f;
        }
    }
}

/* Builds each joint's world matrix: out[joint] = out[joint] * parent's */
void func_80199C3C_ovl_1CE070(void *root, SkelCE *s, MtxCE *out) {
    void *m[32];
    u32 i;
    MtxCE *dst;
    void **pm;

    m[0] = root;
    for (i = 0; i < s->n; i++) {
        dst = &out[s->links[i][0]];
        pm = (void **)(s->links[i][1] * 4 + (s32)m);
        guMtxCatF(dst, *pm, dst);
        pm[1] = dst;
    }
}

/* Turns the offsets in a loaded model blob into pointers */
void func_80199CF0_ovl_1CE070(void *mv) {
    u8 *m = mv;
    u32 i;
    u32 k;
    u32 *p;
    u32 *q;

    FIELD(m, u32, 0x8) += (u32)m;
    FIELD(m, u32, 0xC) += (u32)m;
    FIELD(m, u32, 0x10) += (u32)m;
    if (FIELD(m, u32, 0x14) != 0) {
        FIELD(m, u32, 0x14) += (u32)m;
    }
    FIELD(m, u32, 0x18) += (u32)m;
    for (i = 0; i < FIELD(m, u32, 4); i++) {
        p = (u32 *)(i * 4 + (u32)FIELD(m, u32 *, 8));
        if (*p != 0) {
            *p += (u32)m;
            q = (u32 *)FIELD(m, u32 *, 8)[i];
            for (k = 0; k < 10; k++, q++) {
                if (*q != 0) {
                    *q += (u32)m;
                    *(u32 *)*q += (u32)m;
                }
            }
        }
    }
    for (i = 0; i < FIELD(m, u32, 4); i++) {
        u16 f = *(u16 *)(FIELD(m, u8 *, 0xC) + i * 10 + 2);

        if (f & 0x8000) {
            k = f & 0x7FFF;
            FIELD(m, u32 *, 0x14)[k] += (u32)m;
        }
    }
    for (i = 0; i < FIELD(m, u32, 4); i++) {
        p = (u32 *)(i * 4 + (u32)FIELD(m, u32 *, 0x18));
        if (*p != 0) {
            *p += (u32)m;
        }
    }
}

void func_80199E48_ovl_1CE070(SkelCE *s, void **out) {
    u32 i;

    for (i = 0; i < s->n; i++) {
        if (s->recs[i].h6 != 0) {
            out[i] = HMalloc(0x24);
        } else {
            out[i] = NULL;
        }
    }
}

/* Page `page` of image bank t (pages are 8-byte headers followed by pixels, sub-image and palette as flagged) */
u8 *func_80199ECC_ovl_1CE070(u8 *t, u32 page) {
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
u8 *func_80199FF0_ovl_1CE070(u8 *t, u32 page) {
    u8 *e = func_80199ECC_ovl_1CE070(t, page);
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
u8 *func_8019A09C_ovl_1CE070(u8 *desc, u32 index) {
    u32 w = *(u16 *)(desc + 4);
    u32 h = *(u16 *)(desc + 6);
    u8 *tex = func_80199ECC_ovl_1CE070(desc, index);
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

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019A194_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", UtCreateTexture);

void func_8019AF0C_ovl_1CE070(void) {
    void *p = HMalloc(0x398);

    D_801BA6F8_ovl_1CE070 = p;
    bzero(p, 0x398);
}

typedef struct {
    /* 0x00 */ s32 id;
    /* 0x04 */ u8 unk04[4];
    /* 0x08 */ void *p08;
    /* 0x0C */ u8 unk0C[0xC];
    /* 0x18 */ u32 count;
    /* 0x1C */ u8 unk1C[0xC];
    /* 0x28 */ void *p28;
    /* 0x2C */ u8 unk2C[8];
    /* 0x34 */ void **parts;
    /* 0x38 */ void *p38;
    /* 0x3C */ void *p3C;
    /* 0x40 */ u8 unk40[0x18];
    /* 0x58 */ void *p58;
} Ent1CE; /* size 0x5C */

/* Frees the ten entries of the table func_8019AF0C allocates (each entry's parts and buffers), then the table */
void func_8019AF3C_ovl_1CE070(void) {
    u32 i, j;

    if (D_801BA6F8_ovl_1CE070 != NULL) {
        for (i = 0; i < 10; i++) {
            for (j = 0; j < ((Ent1CE *)D_801BA6F8_ovl_1CE070)[i].count; j++) {
                if (((Ent1CE *)D_801BA6F8_ovl_1CE070)[i].parts[j] != NULL) {
                    HFree(((Ent1CE *)D_801BA6F8_ovl_1CE070)[i].parts[j]);
                }
            }
            HFree(((Ent1CE *)D_801BA6F8_ovl_1CE070)[i].p08);
            HFree(((Ent1CE *)D_801BA6F8_ovl_1CE070)[i].p3C);
            HFree(((Ent1CE *)D_801BA6F8_ovl_1CE070)[i].p38);
            HFree(((Ent1CE *)D_801BA6F8_ovl_1CE070)[i].p58);
            HFree(((Ent1CE *)D_801BA6F8_ovl_1CE070)[i].p28);
        }
        HFree(D_801BA6F8_ovl_1CE070);
        D_801BA6F8_ovl_1CE070 = NULL;
    }
}

typedef struct {
    /* 0x00 */ u16 a;
    /* 0x02 */ s16 b;
    /* 0x04 */ s16 c;
    /* 0x06 */ u16 d;
    /* 0x08 */ u16 e;
    /* 0x0A */ u16 f;
    /* 0x0C */ u16 sx; /* 6.10 fixed point */
    /* 0x0E */ u16 sy;
} Key1CE;

typedef struct {
    /* 0x00 */ s32 a;
    /* 0x04 */ s32 b;
    /* 0x08 */ s32 c;
    /* 0x0C */ s32 d;
    /* 0x10 */ s32 e;
    /* 0x14 */ s32 f;
    /* 0x18 */ f32 sx;
    /* 0x1C */ f32 sy;
    /* 0x20 */ u8 index;
} KeyOut1CE;

/* Copies key k of animation anim of loaded entry id into out (scales from 6.10 fixed point);
 * returns 0 when k is past the animation's key count */
s32 func_8019B054_ovl_1CE070(s32 id, s32 anim, u32 k, KeyOut1CE *out) {
    Ent1CE *e = D_801BA6F8_ovl_1CE070;
    s32 n = 9;
    u8 *tab;
    u16 *a;
    Key1CE *key;

    do {
        if (e->id != 0 && e->id == id) {
            tab = e->p3C;
            goto found;
        }
        e++;
    } while (n--);
    tab = NULL;
found:
    if (tab != NULL) {
        a = (u16 *)(tab + ((s32 *)tab)[anim]);
    } else {
        a = NULL;
    }
    if (k < *a++) {
        a = (u16 *)((Key1CE *)a + k);
        key = (Key1CE *)a;
        out->index = k;
        out->a = key->a;
        out->b = key->b;
        out->c = key->c;
        out->d = key->d;
        out->e = key->e;
        out->f = key->f;
        out->sx = (key->sx >> 10) + (key->sx & 0x3FF) / 1024.0f;
        out->sy = (key->sy >> 10) + (key->sy & 0x3FF) / 1024.0f;
        return 1;
    }
    return 0;
}

extern u8 D_801B8098_ovl_1CE070[];

/* Command n of animation anim of loaded entry id: returns its opcode and stores up
 * to three operand bytes (the command's length comes from D_801B8098) */
u8 UnitAnimGetCommand(s32 id, s32 anim, u32 n, u8 *p1, u8 *p2, u8 *p3) {
    Ent1CE *e = D_801BA6F8_ovl_1CE070;
    s32 k = 9;
    u8 *tab;
    u8 *c;
    u32 count;
    u32 i;

    do {
        if (e->id != 0 && e->id == id) {
            tab = e->p38;
            goto found;
        }
        e++;
    } while (k--);
    tab = NULL;
found:
    if (tab != NULL) {
        c = (u8 *)(((s32 *)tab)[anim] + (s32)tab);
    } else {
        c = NULL;
    }
    count = *c++;
    for (i = 0; i < count; i++) {
        if (i == n) {
            switch (D_801B8098_ovl_1CE070[c[0]]) {
                case 2:
                    if (p1 != NULL) {
                        *p1 = c[1];
                    }
                    break;
                case 3:
                    if (p1 != NULL) {
                        *p1 = c[1];
                    }
                    if (p2 != NULL) {
                        *p2 = c[2];
                    }
                    break;
                case 4:
                    if (p1 != NULL) {
                        *p1 = c[1];
                    }
                    if (p2 != NULL) {
                        *p2 = c[2];
                    }
                    if (p3 != NULL) {
                        *p3 = c[3];
                    }
                    break;
            }
            return c[0];
        }
        c += D_801B8098_ovl_1CE070[c[0]];
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019B2E0_ovl_1CE070);

/* Resource slot (0x24 bytes) in the table at D_801B80C0 */
typedef struct {
    /* 0x00 */ void *data;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ u8 unk08[0x1C];
} Slot1CE;
extern Slot1CE *D_801B80C0_ovl_1CE070;
#define FREE_SLOT1CE(k)                                        if (D_801B80C0_ovl_1CE070[k].data != NULL) {                   HFree(D_801B80C0_ovl_1CE070[k].data);                      D_801B80C0_ovl_1CE070[k].data = NULL;                  }

/* Frees every loaded resource slot (four, three and three in loops, then the singles) and the table */
#ifdef NON_MATCHING
/* resource table free: loop counter/pointer registers swapped */
void func_8019B6D8_ovl_1CE070(void) {
    s32 i;
    Slot1CE *s;

    for (i = 0; i < 4; i++) {
        Slot1CE *p = &D_801B80C0_ovl_1CE070[i];

        if (p->data != NULL) {
            HFree(p->data);
            p->data = NULL;
        }
    }
    for (i = 0; i < 3; i++) {
        Slot1CE *p = &D_801B80C0_ovl_1CE070[4 + i];

        if (p->data != NULL) {
            HFree(p->data);
            p->data = NULL;
        }
    }
    for (i = 0; i < 3; i++) {
        Slot1CE *p = &D_801B80C0_ovl_1CE070[7 + i];

        if (p->data != NULL) {
            HFree(p->data);
            p->data = NULL;
        }
    }
    s = D_801B80C0_ovl_1CE070;
    if (s[10].data != NULL) {
        HFree(s[10].data);
        s[10].data = NULL;
        s = D_801B80C0_ovl_1CE070;
    }
    if (s[11].data != NULL) {
        HFree(s[11].data);
        s[11].data = NULL;
    }
    s = D_801B80C0_ovl_1CE070;
    if (s[12].data != NULL) {
        HFree(s[12].data);
        s[12].data = NULL;
        s = D_801B80C0_ovl_1CE070;
    }
    if (s[16].data != NULL) {
        HFree(s[16].data);
        s[16].data = NULL;
    }
    s = D_801B80C0_ovl_1CE070;
    if (s[13].data != NULL) {
        HFree(s[13].data);
        s[13].data = NULL;
        s = D_801B80C0_ovl_1CE070;
    }
    if (s[14].data != NULL) {
        HFree(s[14].data);
        s[14].data = NULL;
    }
    FREE_SLOT1CE(15);
    HFree(D_801B80C0_ovl_1CE070);
    D_801B80C0_ovl_1CE070 = NULL;
    func_801994C0_ovl_1CE070();
}
#else
INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019B6D8_ovl_1CE070);
#endif

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019B8AC_ovl_1CE070);

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_8016C900();                            /* extern */
s32 func_80184D70();                            /* extern */
extern s32 D_800ABD80;
extern s32 D_800E9C08;
extern s32 D_800E9C0A;
extern s32 D_80186FF0;
extern s32 D_80190F80;
extern s32 D_80193AB0;
extern s32 D_80193AC0;
extern s32 D_80193BC0;
extern s32 D_801953F0;
extern s32 D_80195560;
extern s32 D_80196B00;
extern s32 D_80197710;
extern s32 D_801977D8;
extern s32 gFlags;
extern s32 gLegions;
extern s32 gLocations;
extern s32 gSquads;
extern s32 gTreasureFound;

void func_8019BB7C_ovl_1CE070(void) {
    bzero(&D_80193BC0, 0x15E0);
    bzero(&D_80195560, 0x1450);
    bzero(&gSquads, 0x4E2);
    bzero(&gLegions, 0x6E);
    bzero(&D_80190F80, 0x16C);
    bzero(&D_801953F0, 0x16C);
    bzero(&D_80193AC0, 0xA0);
    bzero(&D_80196B00, 0x458);
    bzero(&D_80197710, 0x64);
    bzero(&D_801977D8, 0x32);
    bzero(&D_80193AB0, 0xA);
    bzero(&gTreasureFound, 0x20);
    bzero(&gFlags, 0x10);
    bzero(&gLocations, 0x240);
    D_80186FF0 = 0;
    func_80184D70();
    func_8016C900();
    FIELD(&D_800E9C08, s32, 0) = M2C_UNALIGNED32(FIELD(&D_800ABD80, s32, 0));
    FIELD(&D_800E9C08, s32, 4) = M2C_UNALIGNED32(FIELD(&D_800ABD80, s32, 4));
    FIELD(&D_800E9C08, s32, 8) = M2C_UNALIGNED32(FIELD(&D_800ABD80, s32, 8));
    FIELD(&D_800E9C08, s32, 0xC) = M2C_UNALIGNED32(FIELD(&D_800ABD80, s32, 0xC));
    FIELD(&D_800E9C08, s16, 0x10) = (s16) FIELD(&D_800ABD80, s16, 0x10);
    FIELD(&D_800E9C0A, u8, 7) = (u8) FIELD(&D_800E9C0A, u8, 7);
}
#else
INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019BB7C_ovl_1CE070);
#endif

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019BCEC_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019C168_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019C5B4_ovl_1CE070);

s32 func_80170794(s32 flag);
#include "gbi_ultra.h"

/* Draws the header bar (slot 12; one half or both depending on story flag 1) and, while the
 * flag is clear, the badge in slot 16 */
void func_8019CBB8_ovl_1CE070(void) {
    SizeCE *s = D_801B80C0_ovl_1CE070[12].data;
    SizeCE *t;

    gDPSetTextureLUT(D_800E9BA0++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(D_800E9BA0++, 0, (u8 *)s + (func_80197C14_ovl_1CE070(0, s->w, s->h) + 8));
    if (func_80170794(1)) {
        func_8019898C_ovl_1CE070(s, 0, 11, s->w, 11, 0x80, 200);
    } else {
        func_8019898C_ovl_1CE070(s, 0, 0, s->w, 11, 0x50, 200);
        func_8019898C_ovl_1CE070(s, 0, 11, s->w, 11, 0xB0, 200);
    }
    t = D_801B80C0_ovl_1CE070[16].data;
    gDPSetTextureLUT(D_800E9BA0++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(D_800E9BA0++, 0, (u8 *)t + (func_80197C14_ovl_1CE070(0, t->w, t->h) + 8));
    if (!func_80170794(1)) {
        func_8019898C_ovl_1CE070(t, 0, 0, t->w, 11, 0x40, 0xD4);
    }
}

extern u8 D_800E82C4;
#include "gbi_ultra.h"

/* Draws resource slot 13 (a CI4 strip, palette after the pixels) when shown: the lower third on
 * even frames of D_800E82C4, the upper third on odd ones */
void func_8019CE8C_ovl_1CE070(void) {
    Slot1CE *t = D_801B80C0_ovl_1CE070;
    SizeCE *s;

    if (*(u8 *)&t[13].x == 0) {
        return;
    }
    s = t[13].data;
    gDPPipeSync(D_800E9BA0++);
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xFCFFFFFF;
        _g->w1 = 0xFFFCF279;
    }
    gDPSetTextureLUT(D_800E9BA0++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(D_800E9BA0++, 0, (u8 *)s + (func_80197C14_ovl_1CE070(0, s->w, s->h) + 8));
    func_8019898C_ovl_1CE070(s, 0, (D_800E82C4 & 1) ? 0 : s->h / 3, s->w,
                             (D_800E82C4 & 1) ? s->h / 3 : s->h * 2 / 3, 0x5D, 0x90);
}

extern s32 D_800E9C0A;

/* Draws the four rows of menu image slot 14 (one fifth of its height each), bright when the
 * row's bit is set in the slot's flags and dimmed otherwise; mode 2 (slot 15) hides row 1 */
#ifdef NON_MATCHING
/* menu rows: constant 3 kept in s7, scheduling */
void func_8019D09C_ovl_1CE070(void) {
    s32 bit = 0;
    s32 i = 0;
    SizeCE *s = D_801B80C0_ovl_1CE070[14].data;
    s32 y = 0x8E;
    u8 *flags;
    s16 *mode;
    s32 r;
    s32 g;
    s32 bl;
    s32 h;

    gDPSetTextureLUT(D_800E9BA0++, G_TT_RGBA16);
    flags = (u8 *)&D_801B80C0_ovl_1CE070[14].x;
    mode = (s16 *)((u8 *)D_801B80C0_ovl_1CE070 + 0x220);
    gDPLoadTLUT_pal16(D_800E9BA0++, 0, (u8 *)s + (func_80197C14_ovl_1CE070(0, s->w, s->h) + 8));
    do {
        if ((mode[2] == 2) & (i == 1)) {
        } else {
            if (i == 3 && ((u8 *)&D_800E9C0A)[7] != 0) {
                i = 4;
            }
            bl = 0xFF;
            if ((*flags >> bit) & 1) {
                g = 0xFF;
                r = 0xFF;
            } else {
                bl = 0x80;
                g = 0x80;
                r = 0x80;
            }
            gDPSetPrimColor(D_800E9BA0++, 0, 0, r, g, bl, 0xFF);
            bit++;
            h = s->h / 5;
            y += 14;
            func_8019898C_ovl_1CE070(s, 0, i * h, s->w, h, 0x82, y);
        }
        i++;
    } while (i < 4);
}
#else
INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019D09C_ovl_1CE070);
#endif

#include "gbi_ultra.h"

/* Draws resource slot 15 (a CI4 image with its 16-colour palette) at its stored position */
void func_8019D2EC_ovl_1CE070(void) {
    Slot1CE *t = D_801B80C0_ovl_1CE070;
    SizeCE *s = t[15].data;

    gDPSetTextureLUT(D_800E9BA0++, G_TT_RGBA16);
    gDPSetPrimColor(D_800E9BA0++, 0, 0, 255, 255, 255, 255);
    gDPLoadTLUT_pal16(D_800E9BA0++, 0, (u8 *)s + (func_80197C14_ovl_1CE070(0, s->w, s->h) + 8));
    func_80198EAC_ovl_1CE070(s, t[15].x, t[15].y);
}

/* Darkens the whole screen with alpha a (no-op at 0) */
void func_8019D438_ovl_1CE070(u8 a) {
    if (a == 0) {
        return;
    }
    gDPPipeSync(D_800E9BA0++);
    gDPSetTextureLUT(D_800E9BA0++, G_TT_NONE);
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xFCFFFFFF;
        _g->w1 = 0xFFFDF6FB;
    }
    gDPSetPrimColor(D_800E9BA0++, 0, 0, 0, 0, 0, a);
    gDPPipeSync(D_800E9BA0++);
    gSPTextureRectangle(D_800E9BA0++, 0, 0, 319 << 2, 239 << 2, 0, 0, 0, 0, 0);
    gDPPipeSync(D_800E9BA0++);
    gDPPipeSync(D_800E9BA0++);
}

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019D548_ovl_1CE070);
