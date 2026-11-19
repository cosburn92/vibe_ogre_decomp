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

INCLUDE_ASM("asm/nonmatchings/1CE070", func_801986E0_ovl_1CE070);

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

INCLUDE_ASM("asm/nonmatchings/1CE070", func_80199968_ovl_1CE070);

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

INCLUDE_ASM("asm/nonmatchings/1CE070", func_80199CF0_ovl_1CE070);

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

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019AF3C_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019B054_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", UnitAnimGetCommand);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019B2E0_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019B6D8_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019B8AC_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019BB7C_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019BCEC_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019C168_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019C5B4_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019CBB8_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019CE8C_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019D09C_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019D2EC_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019D438_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1CE070", func_8019D548_ovl_1CE070);
