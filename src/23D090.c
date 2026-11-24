#include "common.h"
#include "chunk.h"
#include "heap.h"
#include "gu.h"

/* 23D090 */

/* 16 zero bytes (shared rodata splat leaves unmigrated) */
__asm__(".section .rodata\n.global D_801F0490_ovl_23B220\nD_801F0490_ovl_23B220:\n.word 0, 0, 0, 0\n.section .text\n");

typedef struct {
    /* 0x00 */ s32 (*draw)(u8 *o);
    /* 0x04 */ s32 sx;
    /* 0x08 */ s32 sy;
    /* 0x0C */ s32 sz;
    /* 0x10 */ u8 unk10[8];
    /* 0x18 */ void *img;
    /* 0x1C */ u8 unk1C[4];
    /* 0x20 */ f32 mf[4][4];
    /* 0x60 */ u16 flags;
    /* 0x62 */ s16 unk62;
    /* 0x64 */ s16 unk64;
    /* 0x66 */ s16 id;
} Ent23; /* size 0x68 */

typedef struct {
    /* 0x000 */ Ent23 ent[4];
    /* 0x1A0 */ u8 *logo;
    /* 0x1A4 */ u8 unk1A4[0x98];
    /* 0x23C */ u16 unk23C;
    /* 0x23E */ u8 unk23E[0x10E];
    /* 0x34C */ u8 *backdrop;
    /* 0x350 */ u8 unk350[0x10];
    /* 0x360 */ s32 backdropSize;
    /* 0x364 */ u8 unk364[8];
    /* 0x36C */ u8 unk36C[4]; /* func_801EA770's block starts here */
    /* 0x370 */ s16 x0;
    /* 0x372 */ s16 x1;
    /* 0x374 */ s16 y0;
    /* 0x376 */ s16 y1;
    /* 0x378 */ u8 unk378[0x24C];
    /* 0x5C4 */ u8 *img5C4;
    /* 0x5C8 */ u8 *img5C8;
    /* 0x5CC */ u8 unk5CC[0x40];
    /* 0x60C */ u8 *img60C;
    /* 0x610 */ s16 unk610;
    /* 0x612 */ s16 unk612;
    /* 0x614 */ u8 unk614[0x3C];
    /* 0x650 */ u16 flags;
    /* 0x652 */ s16 h652;
    /* 0x654 */ u8 unk654[2]; /* saved time of day, sound setting */
    /* 0x656 */ s16 fade;
} Ctx23;

extern Ctx23 *D_801EFE48_ovl_23B220;
extern u8 D_801CEAAB;

void func_801E98B4_ovl_23B220(s32 id);
void func_801EADF8_ovl_23B220(void);
#include "libultra.h"
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern Gfx *D_800E9BA0;
extern Gfx D_801F0028_ovl_23B220[];
extern Gfx D_801F01D0_ovl_23B220[];
void func_801B5CAC(s32 a, s32 b, s32 c);
void func_801EAAD8_ovl_23B220(void);
void func_801EAFC8_ovl_23B220(void);
void func_801EB594_ovl_23B220(void);
void func_801EBDD8_ovl_23B220(void);
void func_801EC00C_ovl_23B220(void);
void func_801ECAB0_ovl_23B220(void);
extern u8 *D_801969B0;
extern Gfx D_801F0090_ovl_23B220[];
void func_801E9DFC_ovl_23B220(s32 id, u8 *img);
typedef struct {
    u8 id;
    u8 pad[3];
    u8 *text;
} Title23;
extern Title23 D_801EFF04_ovl_23B220[27];
extern s8 D_801EFE8C_ovl_23B220[][2];
extern s8 D_801EFE8D_ovl_23B220[][2];
extern u8 D_801EFE34_ovl_23B220[];
void func_8016F11C(void *p, s32 n);
extern s32 D_801EFE70_ovl_23B220[];
s32 func_801EB968_ovl_23B220();
void guRotateRPYF(f32 mf[4][4], f32 r, f32 p, f32 h);
void guMtxCatF(f32 m[4][4], f32 n[4][4], f32 r[4][4]);
/* --- end decls --- */

typedef struct {
    void *name;
    s32 index;
    u8 *buf;
    s32 size;
} Arc16_23D;
extern Arc16_23D D_801F0490_ovl_23B220;
void DecodeLZ(void *dst, void *src);
void func_8007ACB0(void *arc, void *reqs, s32 n);
void func_801EFB24_ovl_23B220(u8 *data, s32 a, s32 b);
void *func_801EFC78_ovl_23B220(void);

/* Loads chunk id and unpacks it: LHa archives ("-lh"), Huffman images ("HU" / "B5", decoded by
 * func_801EFB24) or LZ */
void *func_801E8E20_ovl_23B220(s32 id) {
    s32 size = ChunkSize(id);
    u8 *raw = HMalloc(size);
    void *out;

    LoadChunkRaw(raw, id);
    if (raw[2] == '-' && raw[3] == 'l' && raw[4] == 'h') {
        Arc16_23D arc = D_801F0490_ovl_23B220;
        Arc16_23D req = D_801F0490_ovl_23B220;

        arc.size = size;
        arc.buf = raw;
        func_8007ACB0(&arc, &req, 1);
        HFree(raw);
        out = req.buf;
    } else if (raw[0] == 'H' && raw[1] == 'U') {
        func_801EFB24_ovl_23B220(raw, 1, 0);
        out = func_801EFC78_ovl_23B220();
    } else if (raw[0] == 'B' && raw[1] == '5') {
        func_801EFB24_ovl_23B220(raw, 1, 0);
        out = func_801EFC78_ovl_23B220();
    } else {
        out = HMalloc(ReadU32BE(raw));
        DecodeLZ(out, raw);
        HFree(raw);
    }
    return out;
}

typedef struct {
    /* 0x00 */ s32 w0;
    /* 0x04 */ s32 w4;
    /* 0x08 */ s16 h8;
    /* 0x0A */ s16 hA;
    /* 0x0C */ s32 w[16];
    /* 0x4C */ void *owner;
} Spr23; /* size 0x50 */

typedef struct {
    u16 x;
    u16 y;
} Pos23;

extern Pos23 D_801EFFF8_ovl_23B220[];
void func_801AD9D4(Spr23 *s, s32 a);
void func_801ADD88(Spr23 *s, s32 x, s32 y, s32 a, s32 b);
s32 func_801C49A0(s32 x, s32 y, s16 h, s32 a, s32 b, u16 c, void *out);
s32 func_801C8B68(u8 *u);
s32 func_801C8BA4(u8 *u);
u16 func_801C8FB8(u8 *u);

/* Builds portrait slot i (0-2) for side 1's unit i: draws its sprite into the slot and
 * places it at layout position k */
void func_801E8F90_ovl_23B220(s32 i, s32 k) {
    u8 *e = (u8 *)D_801EFE48_ovl_23B220 + (i * 0x18 + 0x1AC);
    u8 *u = func_801C8FE8(1);
    s32 *xy;
    Spr23 s;

    xy = (s32 *)(e + 4);
    s = *(Spr23 *)(((u8 **)u)[i] + 0x44);
    s.w0 = FIELD(u, s32, 0x50);
    s.owner = ((u8 **)u)[i];
    func_801AD9D4(&s, 0);
    func_801ADD88(&s, FIELD(u, s32, 0x48), FIELD(u, s32, 0x4C), func_801C8B68(u), func_801C8BA4(u));
    FIELD(e, s32, 0) = func_801C49A0(FIELD(u, s32, 0x48), FIELD(u, s32, 0x4C), s.hA, func_801C8B68(u),
                                     func_801C8BA4(u), func_801C8FB8(u), xy);
    FIELD(e, u16, 0x14) = D_801EFFF8_ovl_23B220[k].x + 0x5A;
    FIELD(e, u16, 0x16) = D_801EFFF8_ovl_23B220[k].y + 0x40;
    FIELD(e, u16, 0x14) += FIELD(e, s32, 4);
    FIELD(e, u16, 0x16) += FIELD(e, s32, 8);
}

extern Pos23 D_801F0010_ovl_23B220[];

/* Builds portrait slot i (3-5) for side 2's unit i - 3: draws its sprite into the slot and
 * places it at layout position k */
void func_801E9130_ovl_23B220(s32 i, s32 k) {
    u8 *e = (u8 *)D_801EFE48_ovl_23B220 + (i * 0x18 + 0x1AC);
    u8 *u = func_801C8FE8(2);
    s32 j = i - 3;
    s32 *xy;
    Spr23 s;

    xy = (s32 *)(e + 4);
    s = *(Spr23 *)(((u8 **)u)[j] + 0x44);
    s.w0 = FIELD(u, s32, 0x50);
    s.owner = ((u8 **)u)[j];
    func_801AD9D4(&s, 0);
    func_801ADD88(&s, FIELD(u, s32, 0x48), FIELD(u, s32, 0x4C), func_801C8B68(u), func_801C8BA4(u));
    FIELD(e, s32, 0) = func_801C49A0(FIELD(u, s32, 0x48), FIELD(u, s32, 0x4C), s.hA, func_801C8B68(u),
                                     func_801C8BA4(u), func_801C8FB8(u), xy);
    FIELD(e, u16, 0x14) = D_801F0010_ovl_23B220[k].x + 0x38;
    FIELD(e, u16, 0x16) = D_801F0010_ovl_23B220[k].y + 0x44;
    FIELD(e, u16, 0x14) += FIELD(e, s32, 4);
    FIELD(e, u16, 0x16) += FIELD(e, s32, 8);
}

s32 func_801BE9A8(s32 siz, s32 w);

/* Blends slot i's portrait into entry k's image at the slot position: each pixel whose mask
 * byte a is nonzero becomes a sepia tint of its luminance (220/180/120 percent), mixed a/255
 * over the destination pixel */
#ifdef NON_MATCHING
/* One instruction long: the /300 multiplier constant is hoisted out of the pixel loop (the
 * original loads it per pixel), so the source row stride lands on the stack instead of the
 * destination pixel base and the registers differ from there */
void func_801E92D4_ovl_23B220(s32 i, s32 k) {
    Ctx23 *c = D_801EFE48_ovl_23B220;
    u8 *e = (u8 *)c + (i * 0x18 + 0x1AC);
    u8 *src = FIELD(e, u8 *, 0);
    s32 x = FIELD(e, s16, 0x14);
    u8 *dst = c->ent[k].img;
    s32 y = FIELD(e, s16, 0x16);
    s32 sstride;
    s32 dstride;
    s32 mstride;
    u8 *mask;
    u8 *sp;
    u16 *dp;
    s32 row;
    s32 col;

    sstride = func_801BE9A8(2, FIELD(src, u16, 4));
    dstride = func_801BE9A8(2, FIELD(dst, u16, 4));
    mask = src + FIELD(src, u16, 6) * sstride;
    mstride = func_801BE9A8(1, FIELD(mask, u16, 0xC));
    sp = FIELD(e, u8 *, 0) + 8;
    mask += 0x10;
    dp = (u16 *)((u8 *)c->ent[k].img + 8);
    for (row = 0; row < FIELD(src, u16, 6); row++) {
        if (y + row >= 0 && y + row < FIELD(dst, u16, 6)) {
            u16 *s = (u16 *)sp;
            u8 *m = mask;

            for (col = 0; col < FIELD(src, u16, 4); col++, m++) {
                s32 dx = col + x;

                if (dx >= 0 && dx < FIELD(dst, u16, 4)) {
                    u32 a = *m;

                    if (a != 0) {
                        u32 r = (*s >> 8) & 0xF8;
                        u32 g = (*s >> 3) & 0xF8;
                        u32 b = (*s << 2) & 0xF8;
                        u32 l = (r * 30 + g * 59 + b * 11) / 300;
                        u16 q;

                        r = l * 220 / 100;
                        g = l * 180 / 100;
                        b = l * 120 / 100;
                        q = dp[(y + row) * dstride / 2 + x + col];
                        dp[(y + row) * dstride / 2 + x + col] = ((((((q >> 8) & 0xF8) * (255 - a) + r * a) / 255) << 8) & 0xF800) +
                             ((((((q >> 3) & 0xF8) * (255 - a) + g * a) / 255) << 3) & 0x7C0) +
                             ((((((q << 2) & 0xF8) * (255 - a) + b * a) / 255) >> 2) & 0x3E);
                    }
                }
                s++;
            }
            sp += sstride;
            mask += mstride;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/23D090", func_801E92D4_ovl_23B220);
#endif

void _bcopy(void *src, void *dst, s32 n);
u8 *func_801C8FE8(s32);
void *func_801CC234(s32, s32);
void func_801E8F90_ovl_23B220(s32, s32);
void func_801E9130_ovl_23B220(s32, s32);
void func_801E92D4_ovl_23B220(s32, s32);

/* For each of the two sides: copies image 0x36EA02 into the side's sheet (0x150 / 0xE8), then
 * builds its 1-3 entries (slots 0-2 and 3-5) and frees their 0x1AC buffers */
void func_801E9618_ovl_23B220(void) {
    {
        u8 *u = func_801C8FE8(1);
        s32 n, k, i;
        u8 *img;
        Ctx23 *s;
        void **pp;

        if (func_801C8C74(u)) {
            n = 3;
            k = 1;
        } else if (func_801C8C90(u)) {
            n = 2;
            k = 4;
        } else {
            n = 1;
            k = 0;
        }
        s = D_801EFE48_ovl_23B220;
        img = func_801CC234(0x36EA02, 0);
        _bcopy(img + 8, FIELD(s, u8 *, 0x150) + 8, func_801BE978(2, FIELD(FIELD(s, u8 *, 0x150), u16, 4), FIELD(FIELD(s, u8 *, 0x150), u16, 6)));
        HFree(img);
        for (i = 0; i < n; i++) {
            func_801E8F90_ovl_23B220(i, k);
            func_801E92D4_ovl_23B220(i, 3);
            pp = &FIELD(D_801EFE48_ovl_23B220, void *, 0x1AC + i * 0x18);
            k++;
            if (*pp != NULL) {
                HFree(*pp);
                *pp = NULL;
            }
        }
    }
    {
        u8 *u = func_801C8FE8(2);
        s32 n, k, i;
        u8 *img;
        Ctx23 *s;
        void **pp;

        if (func_801C8C74(u)) {
            n = 3;
            k = 1;
        } else if (func_801C8C90(u)) {
            n = 2;
            k = 4;
        } else {
            n = 1;
            k = 0;
        }
        s = D_801EFE48_ovl_23B220;
        img = func_801CC234(0x36EA02, 1);
        _bcopy(img + 8, FIELD(s, u8 *, 0xE8) + 8, func_801BE978(2, FIELD(FIELD(s, u8 *, 0xE8), u16, 4), FIELD(FIELD(s, u8 *, 0xE8), u16, 6)));
        HFree(img);
        for (i = 3; i < n + 3; i++) {
            func_801E9130_ovl_23B220(i, k);
            func_801E92D4_ovl_23B220(i, 2);
            pp = &FIELD(D_801EFE48_ovl_23B220, void *, 0x1AC + i * 0x18);
            k++;
            if (*pp != NULL) {
                HFree(*pp);
                *pp = NULL;
            }
        }
    }
}

void func_801E9834_ovl_23B220(void) {
    Ctx23 *s = D_801EFE48_ovl_23B220;
    Gfx *g;

    if (s->flags & 1) {
        g = D_800E9BA0++;
        g->w0 = 0xDE000000;
        g->w1 = (u32)D_801F0028_ovl_23B220;
        func_801B5CAC(FIELD(s, s32, 0x1A0), 0, 0);
        g = D_800E9BA0++;
        g->w0 = 0xE7000000;
        g->w1 = 0;
    }
}

/* Spins entry id away (0x64 counts down by 3); when it is gone, brings in its partner: the other
 * entry of the same pair for even ids, the other pair's odd entry for odd ids */
void func_801E98B4_ovl_23B220(s32 id) {
    Ent23 *e = &D_801EFE48_ovl_23B220->ent[id];
    u8 *m = (u8 *)e + 0x18;

    if (e->flags & 0x20) {
        e->unk64 -= 3;
        if (e->unk64 == 0x42) {
            e->sx -= 1000;
            e->sy -= 1000;
            e->sz -= 1000;
        }
        if (e->unk64 < -0x56) {
            e->unk64 = -0x57;
            e->flags = (e->flags & ~0x20) | 0x10;
            if (!(id & 1)) {
                Ent23 *o = D_801EFE48_ovl_23B220->ent;

                if (id / 2 == 0) {
                    o += 2;
                }
                o->unk64 = 90;
                o->sx = o->sy = o->sz = -11500;
                e->sx = e->sy = e->sz = -13000;
            } else {
                Ent23 *o;

                if ((id - 1) / 2 != 0) {
                    o = &D_801EFE48_ovl_23B220->ent[1];
                } else {
                    o = &D_801EFE48_ovl_23B220->ent[3];
                }
                o->unk64 = 90;
                FIELD(m, s16, 0x4C) = 90;
                o->sx = o->sy = o->sz = -10000;
                e->sx = e->sy = e->sz = -12000;
            }
        }
    }
}

void func_801E99FC_ovl_23B220(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        func_801E98B4_ovl_23B220(D_801EFE48_ovl_23B220->ent[i].id);
    }
}

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ u16 flag;
    /* 0x8 */ s16 s;
    /* 0xA */ s16 t;
    /* 0xC */ s8 nx;
    /* 0xD */ s8 ny;
    /* 0xE */ s8 nz;
    /* 0xF */ u8 a;
} Vtx23;
extern Vtx23 *D_80197178; /* frame vertex pool cursor */

/* Entry fields from the image pointer on (entry + 0x18) */
typedef struct {
    /* 0x00 */ void *img;
    /* 0x04 */ u8 unk04[0x44];
    /* 0x48 */ u16 flags;
    /* 0x4A */ s16 radius;
    /* 0x4C */ s16 angle;
} EntPose23;

/* Lays entry id's strip vertices out along an arc of the entry's radius, starting at its angle
 * (degrees) and stepping one degree per column pair: flag 2 shrinks the radius by 4 per pair
 * from |radius|, flag 1 grows it by 4 from 0 (walking the angles back from the far end). With a
 * negative angle each y is raised to at least the arc height at 87 degrees; the strip ends in a
 * pair at (0, -5) */
void func_801E9A50_ovl_23B220(s32 id) {
    EntPose23 *o = (EntPose23 *)&D_801EFE48_ovl_23B220->ent[id].img;
    f32 ang = o->angle / 180.0 * 3.141592653589793;
    f32 lim = 87.0 / 180.0 * 3.141592653589793;
    s16 r;
    s16 i;
    s16 x;
    s16 y;

    if (o->flags & 2) {
        r = o->radius < 0 ? -o->radius : o->radius;
        for (i = 0; i < 62; i += 2) {
            if (i > 0) {
                r -= 4;
            }
            x = r * sinf(ang - i / 4 / 180.0 * 3.141592653589793);
            y = r * cosf(ang - i / 4 / 180.0 * 3.141592653589793);
            D_80197178[i + 1].x = D_80197178[i].x = x;
            D_80197178[i + 1].y = D_80197178[i].y = y;
            if (o->angle < 0) {
                y = r * cosf(lim - i / 4 / 180.0 * 3.141592653589793);
                if (D_80197178[i].y < y) {
                    D_80197178[i + 1].y = D_80197178[i].y = y;
                }
            }
        }
        D_80197178[i].x = D_80197178[i + 1].x = 0;
        D_80197178[i].y = D_80197178[i + 1].y = -5;
    } else if (o->flags & 1) {
        r = 0;
        D_80197178[0].x = D_80197178[1].x = 0;
        D_80197178[0].y = D_80197178[1].y = -5;
        for (i = 2; i < 64; i += 2) {
            r += 4;
            x = r * sinf(ang - (64 - i) / 4 / 180.0 * 3.141592653589793);
            y = r * cosf(ang - (64 - i) / 4 / 180.0 * 3.141592653589793);
            D_80197178[i + 1].x = D_80197178[i].x = x;
            D_80197178[i + 1].y = D_80197178[i].y = y;
            if (o->angle < 0) {
                y = r * cosf(lim - (64 - i) / 4 / 180.0 * 3.141592653589793);
                if (D_80197178[i].y < y) {
                    D_80197178[i + 1].y = D_80197178[i].y = y;
                }
            }
        }
    }
}

void func_801E9A50_ovl_23B220(s32 id);
void func_801BA0DC(void *timg, s32 a, s32 b, s32 fmt, s32 siz, s32 stride, s32 height, s32 uls, s32 ult,
                   s32 lrs, s32 lrt, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i);
#include "gbi_ultra.h"

/* Draws image img (16-bit, w x h) as a strip of 4-texel-wide columns standing in the yz plane
 * (64 vertices in the frame pool, one texture load per column pair); func_801E9A50 lays the
 * columns out along an arc */
void func_801E9DFC_ovl_23B220(s32 id, u8 *img) {
    if (D_801EFE48_ovl_23B220->flags & 1) {
        Vtx23 *v = D_80197178;
        s32 h;
        s32 w;
        s32 i;
        s32 s;

        bzero(v, 0x400);
        h = FIELD(img, u16, 6);
        w = FIELD(img, u16, 4);
        D_80197178[0].z = -h / 2;
        D_80197178[1].z = (u32)h / 2;
        for (i = 2; i < 64; i += 2) {
            D_80197178[i].z = (u32)h / 2;
            D_80197178[i + 1].z = -h / 2;
        }
        func_801E9A50_ovl_23B220(id);
        for (i = 0, s = 4; i < 64; i++) {
            if (i == 0 || i == 1) {
                D_80197178[i].s = 0;
                if (i & 1) {
                    D_80197178[i].t = h << 6;
                } else {
                    D_80197178[i].t = 0;
                }
            } else {
                D_80197178[i].s = s << 6;
                if (!(i & 1)) {
                    D_80197178[i].t = h << 6;
                } else {
                    D_80197178[i].t = 0;
                }
                if (i & 1) {
                    s += 4;
                }
            }
            D_80197178[i].flag = 0;
            D_80197178[i].nx = 0;
            D_80197178[i].ny = 0;
            D_80197178[i].nz = 0;
            D_80197178[i].a = 0xFF;
        }
        D_80197178 += 64;
        func_801BA0DC(img + 8, 0, 0, 0, 2, w, h, 0, 0, 4, h - 1, 0, 0, 0, 0, 0, 0, 0);
        gSPVertex(D_800E9BA0++, v, 4, 0);
        gSP2Triangles(D_800E9BA0++, 0, 1, 2, 0, 0, 2, 3, 0);
        gDPPipeSync(D_800E9BA0++);
        s = 4;
        for (i = 2; i < 62; i += 2) {
            func_801BA0DC(img + 8, 0, 0, 0, 2, w, h, s, 0, s + 4, h - 1, 0, 0, 0, 0, 0, 0, 0);
            s += 4;
            gSPVertex(D_800E9BA0++, &v[i], 4, 0);
            gSP2Triangles(D_800E9BA0++, 1, 0, 2, 0, 1, 2, 3, 0);
            gDPPipeSync(D_800E9BA0++);
        }
    }
}

/* Draws object o with its float matrix (o + 0x20) */
s32 func_801EA158_ovl_23B220(u8 *o) {
    Ent23 *e = (Ent23 *)o;

    {
        Gfx *_g = D_800E9BA0++;
        _g->w0 = 0xDE000000;
        _g->w1 = (u32)D_801F0090_ovl_23B220;
    }
    guMtxF2L(e->mf, (Mtx *)D_801969B0);
    {
        Gfx *_g = D_800E9BA0++;
        _g->w0 = 0xDA380000;
        _g->w1 = (u32)D_801969B0;
    }
    func_801E9DFC_ovl_23B220(e->id, e->img);
    {
        Gfx *_g = D_800E9BA0++;
        _g->w0 = 0xD8380002;
        _g->w1 = 0x40;
    }
    D_801969B0 += 0x40;
    return 0;
}

extern void *D_801EFE4C_ovl_23B220;
void func_801ADADC(void *o);
s32 func_801EA158_ovl_23B220(u8 *o);

/* Creates the four title objects (ids 0-3) with their scales, angles and images */
void func_801EA224_ovl_23B220(void) {
    s32 img = 0;
    s32 i;
    Ent23 *e;

    D_801EFE4C_ovl_23B220 = func_801CC234(0x36EA02, 2);
    for (i = 0; i < 4; i++) {
        e = &D_801EFE48_ovl_23B220->ent[i];
        e->draw = func_801EA158_ovl_23B220;
        e->id = i;
        e->unk62 = 0x7C;
        guMtxIdentF(e->mf);
        e->mf[3][0] = -100.0f;
        e->flags |= 0x10;
        e->mf[3][2] = 10.0f;
        switch (i) {
            case 0:
                img = 2;
                e->sx = e->sy = e->sz = -13000;
                e->unk64 = -0x57;
                e->flags |= 2;
                break;
            case 1:
                img = 2;
                e->sx = e->sy = e->sz = -10000;
                e->unk64 = 0x5A;
                e->flags |= 1;
                break;
            case 2:
                img = 1;
                e->sx = e->sy = e->sz = -11500;
                e->unk64 = 0x5A;
                e->flags |= 2;
                break;
            case 3:
                img = 0;
                e->sx = e->sy = e->sz = -12000;
                e->unk64 = 0x5A;
                e->flags |= 1;
                break;
        }
        if (i == 2 || i == 3) {
            e->img = func_801CC234(0x36EA02, img);
        } else {
            e->img = D_801EFE4C_ovl_23B220;
        }
        func_801ADADC(e);
    }
}

/* On odd counts (0x23C) the entries with id 0 or 3, on even counts those with id 1 or 2, turn flag 0x10 into 0x20 */
void func_801EA404_ovl_23B220(void) {
    Ctx23 *s = D_801EFE48_ovl_23B220;
    s32 i;
    s32 m;

    i = 0;
    m = ~0x10;
    for (; i < 4; i++) {
        if (FIELD(s, u16, 0x23C) & 1) {
            /* Not || or &&: retail ORs the two equality results (sltiu, or) and
             * tests the sum, and KMC turns either logical form into an AND of !=. */
            if (((s->ent[i].id == 0) | (s->ent[i].id == 3)) == 0) {
                continue;
            }
            goto set;
        } else if ((u16)(s->ent[i].id - 1) < 2) {
        set:
            if (s->ent[i].flags & 0x10) {
                s->ent[i].flags = (s->ent[i].flags & m) | 0x20;
            }
        }
    }
    FIELD(s, u16, 0x23C)++;
}

/* Whether all four entries have flag 0x10 */
s32 func_801EA498_ovl_23B220(void) {
    s32 n = 0;
    s32 i;
    Ent23 *e = D_801EFE48_ovl_23B220->ent;

    for (i = 0; i < 4; i++) {
        if (e[i].flags & 0x10) {
            n++;
        }
    }
    return n == 4;
}

typedef struct {
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
} Rect23;
/* A run of one piece repeated count times across (or down) the logo canvas */
typedef struct {
    /* 0x0 */ u16 x;
    /* 0x2 */ u16 y;
    /* 0x4 */ u8 vertical;
    /* 0x5 */ u8 piece;
    /* 0x6 */ u8 count;
    /* 0x7 */ u8 unk7;
} Run23;
extern Rect23 D_801F00F0_ovl_23B220[]; /* pieces of image 0x36A9A0 */
extern Run23 D_801F0170_ovl_23B220[8];
extern Rect23 D_801F01B0_ovl_23B220;
extern Rect23 D_801F01C0_ovl_23B220;
u32 func_801BE978(s32 siz, u16 w, u16 h);
void func_801ED224_ovl_23B220(u8 *dst, s32 x, s32 y, u8 *src, Rect23 r);
void func_801EA4D4_ovl_23B220(Rect23 a, Rect23 b, u8 *dst, u8 *src);

s32 func_801BEF14(void *img, void *pal, u8 fmt, u8 siz, s32 w, s32 h, s32 x, s32 y, s32 c);
s32 func_801BF59C(void *img, void *pal, u8 fmt, u8 siz, s32 w, s32 h, s32 x, s32 y);

/* func_801ED224's rectangle copy, inlined here */
static inline void BlitRect23(u8 *dst, s32 dx, s32 dy, u8 *src, Rect23 r) {
    u8 *sImg = src + 8;
    u8 *dImg = dst + 8;
    u8 *sPal = sImg + func_801BE978(src[3], FIELD(src, u16, 4), FIELD(src, u16, 6));
    u8 *dPal = dImg + func_801BE978(dst[3], FIELD(dst, u16, 4), FIELD(dst, u16, 6));
    s32 i, j;

    for (j = 0; j < r.y1 - r.y0; j++) {
        for (i = 0; i < r.x1 - r.x0; i++) {
            func_801BEF14(dImg, dPal, dst[2], dst[3], FIELD(dst, u16, 4), FIELD(dst, u16, 6), dx + i, dy + j,
                          func_801BF59C(sImg, sPal, src[2], src[3], FIELD(src, u16, 4), FIELD(src, u16, 6),
                                        r.x0 + i, r.y0 + j));
        }
    }
}

/* Fills rectangle a of texture dst with copies of rectangle b of texture src (tiles clipped at
 * a's right and bottom edges) */
void func_801EA4D4_ovl_23B220(Rect23 a, Rect23 b, u8 *dst, u8 *src) {
    s32 x;
    s32 y;
    s32 w = a.x1 - a.x0;
    s32 h = a.y1 - a.y0;

    for (y = 0; y < h; y += b.y1 - b.y0) {
        Rect23 r = b;

        if (h < y + r.y1 - r.y0) {
            r.y1 = r.y0 + h - y;
        }
        for (x = 0; x < w; x += b.x1 - b.x0) {
            if (w < x + r.x1 - r.x0) {
                r.x1 = r.x0 + w - x;
            }
            BlitRect23(dst, a.x0 + x, a.y0 + y, src, r);
        }
    }
}


/* Builds the 280x60 16-bit frame image *out from pieces of image 0x36A9A0 */
#ifdef NON_MATCHING
/* 140/136 instructions: the original walks the run table with its own pointer (s1) next to the index used for the count (fp + k * 8) */
void func_801EA770_ovl_23B220(u8 **out) {
    u8 *img;
    u8 *src;
    s32 k;
    s32 j;
    s32 x;
    s32 y;
    s32 p;
    Run23 *r;

    img = HMalloc(func_801BE978(2, 280, 60) + 8);
    bzero(img, func_801BE978(2, 280, 60) + 8);
    img[0] = '6';
    img[1] = '4';
    img[3] = 2;
    *(u16 *)(img + 4) = 280;
    img[2] = 0;
    *(u16 *)(img + 6) = 60;
    *out = img;
    src = func_801E8E20_ovl_23B220(0x36A9A0);
    img = *out;
    for (k = 0; k < 8; k++) {
        r = &D_801F0170_ovl_23B220[k];
        x = r->x;
        y = r->y;
        for (j = 0; j < D_801F0170_ovl_23B220[k].count; j++) {
            p = r->piece;
            func_801ED224_ovl_23B220(img, x, y, src, D_801F00F0_ovl_23B220[p]);
            if (r->vertical) {
                y += D_801F00F0_ovl_23B220[p].y1 - D_801F00F0_ovl_23B220[p].y0;
            } else {
                x += D_801F00F0_ovl_23B220[p].x1 - D_801F00F0_ovl_23B220[p].x0;
            }
        }
    }
    func_801EA4D4_ovl_23B220(D_801F01C0_ovl_23B220, D_801F01B0_ovl_23B220, img, src);
    HFree(src);
}
#else
INCLUDE_ASM("asm/nonmatchings/23D090", func_801EA770_ovl_23B220);
#endif

/* The constant 20 is loaded once into a0 in the target. */
void func_801EA990_ovl_23B220(void)
{
  Ctx23 *c = D_801EFE48_ovl_23B220;
  c->y0 = 0x14;
  c->y1 = 0xA2;
  c->x0 = 0x14;
  c->x1 = 0xF2;
  c->h652 = 0;
}

/* Closes the panel by 8 px a frame and fades out; 1 when the fade completes */
#ifdef NON_MATCHING
/* same as func_801EAA58 */
s32 func_801EA9BC_ovl_23B220(void) {
    Ctx23 *s = D_801EFE48_ovl_23B220;
    s32 step = 25;
    s16 *f = &s->h652;

    if (s->x1 >= s->y1) {
        s->x1 -= 8;
        if (s->x1 <= s->y1) {
            s->x1 = s->y1;
            s->y1 = 0xF2;
        }
    }
    if (*f != 0xFF) {
        *f += step;
        if (*f < 0xFF) {
            return 0;
        }
        *f = 0xFF;
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/23D090", func_801EA9BC_ovl_23B220);
#endif

/* Opens the panel by 8 px a frame and fades in; 1 when the fade completes */
static inline s32 fade23(s16 *f, s32 step) {
    if (*f != 0) {
        *f -= step;
        if (*f > 0) {
            return 0;
        }
        *f = 0;
        return 1;
    }
    return 0;
}
static inline void open23(Ctx23 *s) {
    if (s->x1 != s->y1) {
        s->x1 += 8;
        if (s->x1 >= s->y1) {
            s->x1 = s->y1;
        }
    }
}
#ifdef NON_MATCHING
/* step 25 kept in a3 (unpropagated constant, likely an inlined helper arg); 0x18 frame */
s32 func_801EAA58_ovl_23B220(void) {
    Ctx23 *s = D_801EFE48_ovl_23B220;
    s32 step = 25;
    s16 *f = &s->h652;

    open23(s);
    return fade23(f, step);
}
#else
INCLUDE_ASM("asm/nonmatchings/23D090", func_801EAA58_ovl_23B220);
#endif

#include "gbi_ultra.h"
extern Gfx D_801F0230_ovl_23B220[];
typedef struct {
    /* 0x000 */ u8 pad0[0x244];
    /* 0x244 */ void *img;
    /* 0x248 */ void *pal;
    /* 0x24C */ u8 pad24C[0x124];
    /* 0x370 */ u16 x;
    /* 0x372 */ u16 y;
} Pic23;

/* Draws the 40x48 CI8 picture (palette at 0x248, texels at 0x244) at (x0 + 6, x1 + 6) */
void func_801EAAD8_ovl_23B220(void) {
    Pic23 *s = (Pic23 *)D_801EFE48_ovl_23B220;
    s16 x = s->x;
    s16 y = s->y;

    gSPDisplayList(D_800E9BA0++, D_801F0230_ovl_23B220);
    gDPLoadTLUT_pal256(D_800E9BA0++, s->pal);
    gDPLoadTextureBlock(D_800E9BA0++, s->img, G_IM_FMT_CI, G_IM_SIZ_8b, 40, 48, 0, 0, 0, 0, 0, 0, 0);
    gDPPipeSync(D_800E9BA0++);
    gSPScisTextureRectangle(D_800E9BA0++, (x + 6) << 2, (y + 6) << 2, (x + 46) << 2, (y + 54) << 2,
                            G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    gDPPipeSync(D_800E9BA0++);
    gDPPipeSync(D_800E9BA0++);
}

typedef struct {
    /* 0x000 */ u8 text[0x100];
    /* 0x100 */ u8 *backdrop;
    /* 0x104 */ u8 unk104[4];
    /* 0x108 */ u8 *src;
    /* 0x10C */ s32 len;
    /* 0x110 */ s32 tick;
    /* 0x114 */ s32 backdropSize;
    /* 0x118 */ s32 lines;
    /* 0x11C */ s16 x;
    /* 0x11E */ s16 y;
} Text23;

/* Advances the text box's typewriter: one character per 0x100 ticks (two-byte SJIS characters at
 * once); "@c" clears, "@s" / "@w" pause, "@n" breaks the line; a 0 byte ends the text */
#ifdef NON_MATCHING
/* same length; register allocation of the character copies differs and GCC hoists the '\n' constant out of the loop */
void func_801EADF8_ovl_23B220(void) {
    if (!(D_801EFE48_ovl_23B220->flags & 0x20)) {
        Text23 *t = (Text23 *)&D_801EFE48_ovl_23B220->unk23E[0xE];

        t->tick += 0x100;
        while (t->tick > 0x100) {
            u8 *p = t->src;
            s32 c = *p;
            u8 b = c;
            u16 w = b;

            if (c == 0) {
                t->tick = 0x100;
                D_801EFE48_ovl_23B220->flags |= 0x20;
            } else if (w < 0x81 || (u32)(b - 0xA0) < 0x40 || w >= 0xFD) {
                if (c == '@') {
                    t->src = p + 2;
                    switch (p[1]) {
                        case 'c':
                            t->len = 0;
                            break;
                        case 's':
                            t->tick = -0x800;
                            break;
                        case 'w':
                            t->tick = -0x2000;
                            break;
                        case 'n':
                            t->text[t->len++] = '\n';
                            if (++t->lines < 3) {
                                t->tick += 0x100;
                            }
                            break;
                    }
                } else {
                    t->text[t->len++] = *t->src++;
                }
            } else {
                t->text[t->len++] = *t->src++;
                t->text[t->len++] = *t->src++;
            }
            t->tick -= 0x100;
        }
        t->text[t->len] = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/23D090", func_801EADF8_ovl_23B220);
#endif

void func_801EAF9C_ovl_23B220(void) {
    D_801EFE48_ovl_23B220->flags |= 0x10;
}

s32 func_801EAFB4_ovl_23B220(void) {
    return D_801EFE48_ovl_23B220->flags & 0x20;
}

void func_80179018(void);
void func_80179034(char *s, s32 x, s32 y);
void func_8017A704(void *a, void *b, void *c);
extern u16 D_801EFE50_ovl_23B220[];

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
} Box23;

/* Draws the text box text when flag 0x10 is set: scissor to the box at the panel position (bottom
 * edge clamped to the screen), font palette, the text at its offset; once three lines are shown the
 * text scrolls up one 14-pixel line */
#ifdef NON_MATCHING
/* one instruction short: the original evaluates the clamped bottom edge twice (add and compare
 * redone after the == 240 test); here GCC reuses the first compare */
void func_801EAFC8_ovl_23B220(void) {
    Ctx23 *c = D_801EFE48_ovl_23B220;
    Text23 *t = (Text23 *)&c->unk23E[0xE];
    Box23 *p;

    if (c->flags & 0x10) {
        gDPPipeSync(D_800E9BA0++);
        gDPPipeSync(D_800E9BA0++);
        p = (Box23 *)c->unk36C;
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xED000000 | _SHIFTL((s32)((f32)(c->x0 + 48 < 0 ? 0 : c->x0 + 48) * 4.0f), 12, 12) |
                     _SHIFTL((s32)((f32)(p->y + 8 < 0 ? 0 : p->y + 8) * 4.0f), 0, 12);
            _g->w1 = _SHIFTL((s32)((f32)(p->x + 274 == 320 ? 319 : p->x + 274) * 4.0f), 12, 12) |
                     _SHIFTL((s32)((f32)((p->y + 53 > 240 ? 240 : p->y + 53) == 240 ? 239 : (p->y + 53 > 240 ? 240 : p->y + 53)) * 4.0f), 0, 12);
        }
        gDPPipeSync(D_800E9BA0++);
        func_80179018();
        ((void (*)(void))func_8017A704)();
        gDPPipeSync(D_800E9BA0++);
        gDPSetBlendColor(D_800E9BA0++, 255, 255, 255, 1);
        gDPSetAlphaCompare(D_800E9BA0++, G_AC_THRESHOLD);
        gDPSetTextureLUT(D_800E9BA0++, G_TT_RGBA16);
        gDPLoadTLUT_pal16(D_800E9BA0++, 0, D_801EFE50_ovl_23B220);
        func_80179034((char *)t->text, p->x + t->x, p->y + t->y);
        if (t->lines >= 3) {
            t->y -= 14;
            t->lines--;
        }
        gDPPipeSync(D_800E9BA0++);
        gDPSetAlphaCompare(D_800E9BA0++, G_AC_NONE);
        gDPPipeSync(D_800E9BA0++);
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = 0xED000000;
            _g->w1 = 0x4FC3BC;
        }
        gDPPipeSync(D_800E9BA0++);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/23D090", func_801EAFC8_ovl_23B220);
#endif

void func_801EB394_ovl_23B220(void) {
    if (D_801EFE48_ovl_23B220->flags & 0x10) {
        func_801EADF8_ovl_23B220();
    }
}

void *func_8016FBE0(u8 cls, u8 variant, void *out);

/* Loads character k's portrait and points the text box at its details message: the text after
 * "$nnn" (nnn = k) in the details script, or a fallback */
#ifdef NON_MATCHING
/* 74/74 instructions, 12 words differ: the script size is loaded into the loop bound register directly instead of via v0, and the text pointer copy is made before the empty check; the fallback string is in this function's rodata */
void func_801EB3C8_ovl_23B220(u8 k) {
    Ctx23 *c = D_801EFE48_ovl_23B220;
    u8 *s;
    u8 *tb;
    u8 *text;
    u8 *r;
    u32 i;
    u32 n0;
    void *pt;

    pt = func_8016FBE0(k, 0, (u8 *)c + 0x248);

    FIELD(c, u8, 0x240) = k;
    FIELD(c, void *, 0x244) = pt;
    n0 = D_801EFE48_ovl_23B220->backdropSize;
    s = D_801EFE48_ovl_23B220->backdrop;
    tb = (u8 *)D_801EFE48_ovl_23B220 + 0x24C;
    for (text = s, i = 0; i < n0; i++) {
        text++;
        if (*s++ == '$') {
            s32 n = (s[0] - '0') * 100 + (text[1] - '0') * 10 + (text[2] - '0');

            text += 3;
            s += 3;
            i += 3;
            if (k == n) {
                r = text;
                goto found;
            }
        }
    }
    r = "There is no details message of@nthis charcter.";
found:
    FIELD(tb, u8 *, 0x104) = r;
    FIELD(tb, u8 *, 0x108) = r;
    FIELD(tb, s32, 0x110) = 0x100;
    FIELD(tb, s16, 0x11C) = 50;
    FIELD(tb, s32, 0x10C) = 0;
    FIELD(tb, s32, 0x118) = 0;
    FIELD(tb, s16, 0x11E) = 8;
}
#else
INCLUDE_ASM("asm/nonmatchings/23D090", func_801EB3C8_ovl_23B220);
#endif

void func_801EB4F0_ovl_23B220(void) {
    D_801EFE48_ovl_23B220->flags |= 4;
}

void func_801EB508_ovl_23B220(void) {
    Ctx23 *s = D_801EFE48_ovl_23B220;

    if (s->flags & 4) {
        {
            Gfx *_g = D_800E9BA0++;
            _g->w0 = 0xDE000000;
            _g->w1 = (u32)D_801F01D0_ovl_23B220;
        }
        func_801B5CAC(((struct { u8 pad[0x36C]; s32 v; } *)s)->v, s->x0, s->x1);
        {
            Gfx *_g = D_800E9BA0++;
            _g->w0 = 0xE7000000;
            _g->w1 = 0;
        }
        func_801EAAD8_ovl_23B220();
        func_801EAFC8_ovl_23B220();
    }
}

#include "gbi_ultra.h"
s32 func_801B594C(void *img, s32 a, s32 b, u16 w, s32 h, s32 x, s32 y);
extern Gfx D_801F0250_ovl_23B220[];

/* Draws the full-screen picture (0x60C, at x 0x610) in 16-line strips with prim alpha 0x653 */
void func_801EB594_ovl_23B220(void) {
    u8 *e;
    s32 i;

    gSPDisplayList(D_800E9BA0++, D_801F0250_ovl_23B220);
    i = 0;
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xFA000000;
        e = (u8 *)&D_801EFE48_ovl_23B220->img60C;
        _g->w1 = FIELD(D_801EFE48_ovl_23B220, u8, 0x653);
    }
    do {
        func_801B594C(FIELD(e, u8 *, 0), 0, 0, FIELD(FIELD(e, u8 *, 0), u16, 4), 16, FIELD(e, s16, 4), i * 16);
        i++;
        gDPPipeSync(D_800E9BA0++);
    } while (i < 8);
    func_801B594C(FIELD(e, u8 *, 0), 0, 0, FIELD(FIELD(e, u8 *, 0), u16, 4), FIELD(FIELD(e, u8 *, 0), u16, 6),
                  FIELD(e, s16, 4), i * 16);
    gDPPipeSync(D_800E9BA0++);
}


/* Builds a lit box of half-size (a, b, c) in the vertex pool (four faces of four vertices each,
 * normals +z, +y, -y, -z) and draws it as four quads */
void func_801EB6C8_ovl_23B220(s16 a, s16 b, s16 c) {
    Vtx23 *v = D_80197178;
    s32 i;

    for (i = 0; i < 16; i++) {
        bzero(D_80197178, 0x10);
        if ((u32)(i % 4) >= 2) {
            D_80197178->x = 0;
        } else {
            D_80197178->x = -a;
        }
        if (i == 0 || i == 3 || (u32)(i - 4) < 4 || (u32)(i - 13) < 2) {
            D_80197178->y = b;
        } else {
            D_80197178->y = -b;
        }
        if ((u32)i < 4 || (u32)(i - 5) < 2 || i == 8 || i == 11) {
            D_80197178->z = c;
        } else {
            D_80197178->z = -c;
        }
        if ((u32)i < 4) {
            D_80197178->nz = 0x7F;
        } else if ((u32)(i - 4) < 4) {
            D_80197178->ny = 0x7F;
        } else if ((u32)(i - 8) < 4) {
            D_80197178->ny = -0x7F;
        } else {
            D_80197178->nz = -0x7F;
        }
        D_80197178->a = 0xFF;
        D_80197178++;
    }
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0x01010020;
        _g->w1 = (u32)v;
    }
    for (i = 0; i < 16; i += 4) {
        {
            Gfx *_g = D_800E9BA0++;

            _g->w0 = _SHIFTL(6, 24, 8) | (_SHIFTL(i * 2, 16, 8) | _SHIFTL((i + 1) * 2, 8, 8) | _SHIFTL((i + 2) * 2, 0, 8));
            _g->w1 = _SHIFTL(i * 2, 16, 8) | _SHIFTL((i + 2) * 2, 8, 8) | _SHIFTL((i + 3) * 2, 0, 8);
        }
        gDPPipeSync(D_800E9BA0++);
    }
}

#include "gbi_ultra.h"
typedef struct { s32 m[16]; } Mtx23;
#define MTX23 (*(Mtx23 **)&D_801969B0)
void func_800987E0(void *m); /* identity */
extern u8 D_801F02B8_ovl_23B220[];
void func_801EB6C8_ovl_23B220(s16 a, s16 b, s16 c);

/* Draws object o in a 320x240 orthographic view: its light colour (0x4C), its matrix (o + 4) and
 * shape (0x44-0x48), faded by the title context's alpha */
typedef union { struct { u32 w0, w1; } words; long long force_align[1]; } GfxU23;
typedef struct { s32 pad0; f32 mf[4][4]; s16 a, b, c; s16 pad4A; u32 col; } Obj23b;
#define GU23(w0_, w1_) { GfxU23 *_g = (GfxU23 *)(D_800E9BA0++); _g->words.w0 = (w0_); _g->words.w1 = (u32)(w1_); }
s32 func_801EB968_ovl_23B220(u8 *o) {
    Obj23b *ob = (Obj23b *)o;

    GU23(0xE7000000, 0);
    guOrtho((Mtx *)D_801969B0, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);
    func_800987E0(D_801969B0 + 0x40);
    GU23(0xDA380007, (D_801969B0 += 0x40) - 0x40);
    GU23(0xDA380002, (D_801969B0 += 0x40) - 0x40);
    GU23(0xDE000000, D_801F02B8_ovl_23B220);
    GU23(0xDB0A0000, ob->col);
    GU23(0xDB0A0004, ob->col);
    guMtxF2L(ob->mf, (Mtx *)D_801969B0);
    GU23(0xDA380001, D_801969B0);
    GU23(0xFA000000, (u8)D_801EFE48_ovl_23B220->h652);
    func_801EB6C8_ovl_23B220(ob->a, ob->b, ob->c);
    GU23(0xD8380002, 0x40);
    D_801969B0 += 0x40;
    return 0;
}

/* Loads unit u's stats and sets up the seven stat bars (length = stat / 150 * 60) */
#ifdef NON_MATCHING
/* GCC hoists the func_801EB968 address into s8; the original reloads it each pass */
void func_801EBB5C_ovl_23B220(u8 *u) {
    u8 *s = (u8 *)D_801EFE48_ovl_23B220;
    u16 *st;
    s32 i;
    s32 y;

    s[0x629] = FIELD(u, s32, 0x48);
    s[0x62A] = FIELD(u, s32, 0x4C);
    func_8016F11C(s + 0x618, 8);
    FIELD(u, u16, 0x22) = FIELD(s, u16, 0x62E);
    FIELD(u, u16, 0x24) = FIELD(s, u16, 0x634);
    FIELD(u, u16, 0x26) = FIELD(s, u16, 0x636);
    FIELD(u, u16, 0x28) = FIELD(s, u16, 0x638);
    FIELD(u, u16, 0x2A) = FIELD(s, u16, 0x63A);
    FIELD(u, u16, 0x2C) = FIELD(s, u16, 0x63C);
    FIELD(u, u16, 0x2E) = FIELD(s, u16, 0x63E);
    st = (u16 *)(u + 0x22);
    for (i = 0, y = 75; i < 7; i++, y -= 8) {
        u8 *b = (u8 *)D_801EFE48_ovl_23B220 + 0x378 + i * 0x54;

        FIELD(b, s16, 0x44) = 0;
        FIELD(b, s16, 0x46) = 2;
        FIELD(b, s16, 0x48) = 2;
        FIELD(b, s32, 0x4C) = D_801EFE70_ovl_23B220[i];
        FIELD(b, s16, 0x50) = st[i] / 150.0f * 60.0f;
        guMtxIdentF((f32 (*)[4])(b + 4));
        FIELD(b, void *, 0) = func_801EB968_ovl_23B220;
        FIELD(b, f32, 0x34) = 105.0f;
        FIELD(b, f32, 0x38) = y;
        FIELD(b, f32, 0x3C) = -10.0f;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/23D090", func_801EBB5C_ovl_23B220);
#endif

typedef struct {
    /* 0x00 */ u8 unk00[4];
    /* 0x04 */ f32 m[4][4];
    /* 0x44 */ s16 h44;
    /* 0x46 */ u8 unk46[0xA];
    /* 0x50 */ s16 h50;
    /* 0x52 */ u8 unk52[2];
} Part23; /* size 0x54 */

/* Spins the 7 parts (0x54 bytes each from 0x378) by 5 degrees, easing their 0x44 value up to 0x50 */
void func_801EBCFC_ovl_23B220(void) {
    f32 m[4][4];
    s32 i;
    Part23 *e;
    f32 (*mtx)[4];

    if (!(FIELD(D_801EFE48_ovl_23B220, u16, 0x650) & 2)) {
        return;
    }
    for (i = 0; i < 7; i++) {
        e = (Part23 *)((u8 *)D_801EFE48_ovl_23B220 + 0x378) + i;
        mtx = e->m;
        if (e->h44 < e->h50) {
            e->h44 += 2;
            if (e->h44 < e->h50) {
                goto rot;
            }
        }
        e->h44 = e->h50;
    rot:
        guRotateRPYF(m, 5.0f, 0.0f, 0.0f);
        guMtxCatF(m, mtx, mtx);
    }
}

#include "gbi_ultra.h"
typedef struct {
    u8 unk0[4];
    u16 w;
    u16 h;
} SizeEB;
extern u8 D_801F0320_ovl_23B220[];
u32 func_801BE978(s32 siz, u16 w, u16 h);

/* Draws the panel's CI4 image (palette after the pixels) at alpha ctx->0x653 */
void func_801EBDD8_ovl_23B220(void) {
    SizeEB *s = FIELD(D_801EFE48_ovl_23B220, SizeEB *, 0x5C4);

    gSPDisplayList(D_800E9BA0++, D_801F0320_ovl_23B220);
    gDPSetPrimColor(D_800E9BA0++, 0, 0, 0, 0, 0, FIELD(D_801EFE48_ovl_23B220, u8, 0x653));
    gDPSetTextureLUT(D_800E9BA0++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(D_800E9BA0++, 0, (u8 *)s + (func_801BE978(0, s->w, s->h) + 8));
    func_801B5CAC((s32)s, 0xFF, 0x2B);
    gDPPipeSync(D_800E9BA0++);
}

/* Selects the title text for id and right-aligns it (x = 0x113 - width) */
#ifdef NON_MATCHING
/* register allocation: original keeps the title ptr in t0 and second kern in a0 */
void func_801EBF58_ovl_23B220(u8 id) {
    u8 *t = (u8 *)D_801EFE48_ovl_23B220 + 0x5C8;
    u32 i;
    u8 *s;
    u8 c;
    s32 w;

    FIELD(D_801EFE48_ovl_23B220, u8 *, 0x5CC) = D_801EFE34_ovl_23B220;
    for (i = 0; i < 27; i++) {
        if (D_801EFF04_ovl_23B220[i].id == id) {
            FIELD(t, u8 *, 4) = D_801EFF04_ovl_23B220[i].text;
        }
    }
    s = FIELD(t, u8 *, 4);
    w = 0;
    while (*s != 0) {
        c = *s++;
        w -= D_801EFE8C_ovl_23B220[c - 'A'][0];
        w += 16;
        w -= D_801EFE8D_ovl_23B220[c - 'A'][0];
    }
    FIELD(t, s16, 8) = 0x113 - w;
    FIELD(t, s16, 0xA) = 0x1E;
}
#else
INCLUDE_ASM("asm/nonmatchings/23D090", func_801EBF58_ovl_23B220);
#endif

INCLUDE_ASM("asm/nonmatchings/23D090", func_801EC00C_ovl_23B220);

s32 func_801C8C90(u8 *u);

/* Builds the two portrait slots of unit u (its leader part, then its second part when
 * func_801C8C90 says it has one) at their fixed screen positions */
void func_801EC4B0_ovl_23B220(u8 *u) {
    u8 *e = (u8 *)D_801EFE48_ovl_23B220 + 0x5D4;
    s32 *xy = (s32 *)((u8 *)D_801EFE48_ovl_23B220 + 0x5DC);
    Spr23 s;

    s = *(Spr23 *)(((u8 **)u)[0] + 0x44);
    s.w0 = FIELD(u, s32, 0x50);
    s.owner = ((u8 **)u)[0];
    func_801AD9D4(&s, 0);
    func_801ADD88(&s, FIELD(u, s32, 0x48), FIELD(u, s32, 0x4C), func_801C8B68(u), func_801C8BA4(u));
    FIELD(e, s32, 4) = func_801C49A0(FIELD(u, s32, 0x48), FIELD(u, s32, 0x4C), s.hA, func_801C8B68(u),
                                     func_801C8BA4(u), func_801C8FB8(u), xy);
    FIELD(e, u8 *, 0) = u;
    FIELD(e, s16, 0x18) = 0xF0 - FIELD(e, s32, 0x10);
    FIELD(e, s16, 0x1A) = FIELD(e, s32, 0xC) + 0x87;
    if (func_801C8C90(u) != 0) {
        e = (u8 *)D_801EFE48_ovl_23B220 + 0x5F0;
        xy = (s32 *)((u8 *)D_801EFE48_ovl_23B220 + 0x5F8);
        s = *(Spr23 *)(((u8 **)u)[1] + 0x44);
        s.w0 = FIELD(u, s32, 0x50);
        s.owner = ((u8 **)u)[1];
        func_801AD9D4(&s, 0);
        func_801ADD88(&s, FIELD(u, s32, 0x48), FIELD(u, s32, 0x4C), func_801C8B68(u), func_801C8BA4(u));
        FIELD(e, s32, 4) = func_801C49A0(FIELD(u, s32, 0x48), FIELD(u, s32, 0x4C), s.hA, func_801C8B68(u),
                                         func_801C8BA4(u), func_801C8FB8(u), xy);
        FIELD(e, u8 *, 0) = u;
        FIELD(e, s16, 0x18) = 0xE4 - FIELD(e, s32, 0x10);
        FIELD(e, s16, 0x1A) = FIELD(e, s32, 0xC) + 0x8A;
    }
}

s32 func_801BEA0C(s32 siz, s32 w);
typedef struct { u8 pad0[3]; u8 siz; u16 w; u16 h; u8 data[1]; } Img23; /* 8-byte header, then texels */
/* gSPScisTextureRectangle written through the aligned GfxU23 union (keeps every word store
 * ahead of the D_800E9BA0 updates, as in the original) */
#define ScisTexRect23(pkt, xl, yl, xh, yh, tile, s, t, dsdx, dtdy)                                        \
    {                                                                                                     \
        GfxU23 *_g = (GfxU23 *)(pkt);                                                                     \
        _g->words.w0 = _SHIFTL(G_TEXRECT, 24, 8) | _SHIFTL(MAX((s16)(xh), 0), 12, 12) |                   \
                       _SHIFTL(MAX((s16)(yh), 0), 0, 12);                                                 \
        _g->words.w1 = _SHIFTL((tile), 24, 3) | _SHIFTL(MAX((s16)(xl), 0), 12, 12) |                      \
                       _SHIFTL(MAX((s16)(yl), 0), 0, 12);                                                 \
        GU23(G_RDPHALF_1 << 24,                                                                           \
             _SHIFTL((s) - (((s16)(xl) < 0) ? (((s16)(dsdx) < 0) ? MAX(((s16)(xl) * (s16)(dsdx)) >> 7, 0) \
                                                              : MIN(((s16)(xl) * (s16)(dsdx)) >> 7, 0))   \
                                             : 0), 16, 16) |                                              \
             _SHIFTL((t) - (((yl) < 0) ? (((s16)(dtdy) < 0) ? MAX(((s16)(yl) * (s16)(dtdy)) >> 7, 0)      \
                                                         : MIN(((s16)(yl) * (s16)(dtdy)) >> 7, 0))        \
                                       : 0), 0, 16));                                                     \
        GU23(G_RDPHALF_2 << 24, _SHIFTL((dsdx), 16, 16) | _SHIFTL((dtdy), 0, 16));                        \
    }

/* Draws image img (16-bit texels, w x h) mirrored left to right at (x, y), loading the 8-bit
 * mask stored after its texels into TMEM 0x100 alongside, in bands of rows that fit in 2 KB */
void func_801EC6F4_ovl_23B220(Img23 *img, s16 x, s16 y) {
    s32 stride = func_801BE9A8(2, img->w);
    Img23 *mask = (Img23 *)((u8 *)img + (stride * img->h + 8));
    s32 band = 0x800 / stride;
    s32 row;
    s32 n;

    for (row = 0; row < img->h; row += band) {
        n = band;
        if (img->h - row < band) {
            n = img->h - row;
        }
        func_801BA0DC(mask->data, 0x100, 0, 4, 1, func_801BEA0C(1, mask->w), mask->h, 0, row,
                      func_801BEA0C(1, mask->w) - 1, row + n - 1, 0, 0, 0, 0, 0, 0, 0);
        func_801BA0DC(img->data, 0, 1, 0, 2, func_801BEA0C(2, img->w), img->h, 0, row,
                      func_801BEA0C(2, img->w) - 1, row + n - 1, 0, 0, 0, 0, 0, 0, 0);
        GU23(0xE7000000, 0);
        ScisTexRect23(D_800E9BA0++, x << 2, (y + row) << 2, (x + img->w) << 2, (y + row + n) << 2, 0,
                      (func_801BEA0C(img->siz, img->w) - 1) << 5, row << 5, -1024, 1024);
        GU23(0xE7000000, 0);
        GU23(0xE7000000, 0);
    }
}

extern Gfx D_801F0380_ovl_23B220[];
s32 func_801C8C74(u8 *u);
s32 func_801C8C90(u8 *u);
void func_801EC6F4_ovl_23B220(Img23 *img, s16 x, s16 y);

/* Draws the unit sprites of the battle preview: the attacker (doubled with an offset echo when
 * func_801C8C74 says so) and, if present, the target */
void func_801ECAB0_ovl_23B220(void) {
    Ctx23 *c = D_801EFE48_ovl_23B220;
    u8 **target;

    gSPDisplayList(D_800E9BA0++, D_801F0380_ovl_23B220);
    gDPSetPrimColor(D_800E9BA0++, 0, 0, 0, 0, 0, FIELD(c, u8, 0x653));
    target = &FIELD(c, u8 *, 0x5D4);
    if (func_801C8C74(FIELD(c, u8 *, 0x5D4))) {
        func_801EC6F4_ovl_23B220(FIELD(c, Img23 *, 0x5D8), FIELD(c, s16, 0x5EC) - 10, FIELD(c, s16, 0x5EE) - 5);
        func_801EC6F4_ovl_23B220(FIELD(c, Img23 *, 0x5D8), FIELD(c, s16, 0x5EC) + 10, FIELD(c, s16, 0x5EE));
        func_801EC6F4_ovl_23B220(FIELD(c, Img23 *, 0x5D8), FIELD(c, s16, 0x5EC) - 3, FIELD(c, s16, 0x5EE) + 5);
    } else {
        func_801EC6F4_ovl_23B220(FIELD(c, Img23 *, 0x5D8), FIELD(c, s16, 0x5EC), FIELD(c, s16, 0x5EE));
    }
    if (func_801C8C90(*target)) {
        func_801EC6F4_ovl_23B220(FIELD(D_801EFE48_ovl_23B220, Img23 *, 0x5F4), FIELD(D_801EFE48_ovl_23B220, s16, 0x608),
                                 FIELD(D_801EFE48_ovl_23B220, s16, 0x60A));
    }
    gDPPipeSync(D_800E9BA0++);
    gDPPipeSync(D_800E9BA0++);
    gSPSetOtherMode(D_800E9BA0++, G_SETOTHERMODE_H, 20, 2, 0);
    gDPPipeSync(D_800E9BA0++);
}

void func_801ECC40_ovl_23B220(void) {
    D_801EFE48_ovl_23B220->flags |= 2;
}

void func_801ECC58_ovl_23B220(void) {
    s32 i;
    u8 *o;

    if (D_801EFE48_ovl_23B220->flags & 2) {
        func_801EB594_ovl_23B220();
        for (i = 0; i < 7; i++) {
            o = (u8 *)D_801EFE48_ovl_23B220 + 0x378 + i * 0x54;
            (*(void (**)(u8 *))o)(o);
        }
        func_801EBDD8_ovl_23B220();
        func_801EC00C_ovl_23B220();
        func_801ECAB0_ovl_23B220();
    }
}

/* Fade-out step; returns 1 when done */
/* Fade-out step; returns 1 when done */
s32 func_801ECCE0_ovl_23B220(void) {
    Ctx23 *c = D_801EFE48_ovl_23B220;
    s32 r;

    c->fade -= 8;
    if ((s16)c->fade > 0) {
        r = 0;
        D_801CEAAB = c->fade;
    } else {
        r = 1;
        D_801CEAAB = 0;
        c->fade = 0;
    }
    return r;
}

/* Fade-in step; returns 1 when done */
/* Fade-in step; returns 1 when done */
s32 func_801ECD28_ovl_23B220(void) {
    Ctx23 *c = D_801EFE48_ovl_23B220;

    c->fade += 8;
    if (c->fade >= 0xFF) {
        D_801CEAAB = 0xFF;
        c->fade = 0xFF;
        return 1;
    }
    D_801CEAAB = c->fade;
    return 0;
}

void func_801ECD80_ovl_23B220(void) {
    Ctx23 *s = D_801EFE48_ovl_23B220;
    s32 i;

    if (FIELD(s, void *, 0x244) != NULL) {
        HFree(FIELD(s, void *, 0x244));
        FIELD(s, void *, 0x244) = NULL;
        FIELD(s, s32, 0x248) = 0;
    }
    D_801EFE48_ovl_23B220->flags &= 3;
    for (i = 0; i < 2; i++) {
        u8 *e = (u8 *)D_801EFE48_ovl_23B220 + 0x5D4 + i * 0x1C;

        if (FIELD(e, void *, 4) != NULL) {
            HFree(FIELD(e, void *, 4));
            FIELD(e, void *, 4) = NULL;
        }
    }
    D_801EFE48_ovl_23B220->flags &= ~2;
}

void func_801EA770_ovl_23B220(u8 **out);
extern s32 D_800E9C0A;
extern u8 D_801976DA;
extern u8 D_801CEAAC;
extern u8 D_801CEAAD;
extern u8 D_801CEAAE;

/* Title screen init: allocates the context, loads the logo, objects and backdrop, and saves the
 * time of day and sound setting it overrides */
#ifdef NON_MATCHING
/* 121/123 instructions: the original loads D_801EFE48 into saved registers before each loader call and copies the 16-byte archive descriptors with three registers */
void func_801ECE30_ovl_23B220(void) {
    Ctx23 *s;

    s = HMalloc(0x658);
    D_801EFE48_ovl_23B220 = s;
    bzero(s, 0x658);
    s = D_801EFE48_ovl_23B220;
    s->logo = func_801E8E20_ovl_23B220(0x36BC52);
    func_801EA224_ovl_23B220();
    {
        Arc16_23D arc = D_801F0490_ovl_23B220;
        Arc16_23D req = D_801F0490_ovl_23B220;

        s = D_801EFE48_ovl_23B220;
        arc.size = ChunkSize(0x36A070);
        arc.buf = HMalloc(arc.size);
        LoadChunkRaw(arc.buf, 0x36A070);
        func_8007ACB0(&arc, &req, 1);
        HFree(arc.buf);
        s->backdropSize = req.size;
        s->backdrop = req.buf;
    }
    func_801EA770_ovl_23B220(D_801EFE48_ovl_23B220->unk36C);
    s = D_801EFE48_ovl_23B220;
    s->img60C = func_801E8E20_ovl_23B220(0x36AB9C);
    s->unk610 = 0xC8;
    s->unk612 = 0;
    s = D_801EFE48_ovl_23B220;
    s->img5C4 = func_801E8E20_ovl_23B220(0x36AA92);
    s = D_801EFE48_ovl_23B220;
    s->img5C8 = func_801E8E20_ovl_23B220(0x01DD375A);
    D_801EFE48_ovl_23B220->unk654[0] = D_801976DA;
    D_801976DA = 0x18;
    D_801EFE48_ovl_23B220->unk654[1] = FIELD(&D_800E9C0A, u8, 8);
    FIELD(&D_800E9C0A, u8, 8) = 1;
    D_801CEAAE = 0;
    D_801CEAAD = 0;
    D_801CEAAC = 0;
    D_801EFE48_ovl_23B220->fade = 0xFF;
    D_801EFE48_ovl_23B220->unk23C = 0;
    D_801EFE48_ovl_23B220->flags |= 1;
    func_8017A704(D_801EFE48_ovl_23B220, &FIELD(&D_800E9C0A, u8, 8), D_801EFE48_ovl_23B220);
}
#else
INCLUDE_ASM("asm/nonmatchings/23D090", func_801ECE30_ovl_23B220);
#endif

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_8017A714();
extern u8 D_801976DA;

/* Tears the title screen down: restores the saved time of day / sound setting, frees every
 * buffer the context owns (re-reading the context pointer after each free), then the context */
void func_801ED01C_ovl_23B220(void) {
    u8 *s;
    void **pp;
    s32 i;
    s32 off;

    FIELD(&D_800E9C0A, u8, 8) = D_801EFE48_ovl_23B220->unk654[1];
    D_801976DA = D_801EFE48_ovl_23B220->unk654[0];
    for (i = 0, off = 0x1AC; i < 6; off += 0x18) {
        pp = (void **)((u8 *)D_801EFE48_ovl_23B220 + off);
        i++;
        if (*pp != NULL) {
            HFree(*pp);
            *pp = NULL;
        }
    }
    s = (u8 *)D_801EFE48_ovl_23B220;
    if (FIELD(s, void *, 0x1A0) != NULL) {
        HFree(FIELD(s, void *, 0x1A0));
        FIELD(s, void *, 0x1A0) = NULL;
        s = (u8 *)D_801EFE48_ovl_23B220;
    }
    if (FIELD(s, void *, 0x150) != NULL) {
        HFree(FIELD(s, void *, 0x150));
        FIELD(s, void *, 0x150) = NULL;
    }
    s = (u8 *)D_801EFE48_ovl_23B220;
    if (FIELD(s, void *, 0xE8) != NULL) {
        HFree(FIELD(s, void *, 0xE8));
        FIELD(s, s32, 0xE8) = 0;
    }
    HFree(D_801EFE4C_ovl_23B220);
    s = (u8 *)D_801EFE48_ovl_23B220;
    {
        void *p = FIELD(s, void *, 0x36C);

        D_801EFE4C_ovl_23B220 = NULL;
        if (p != NULL) {
            HFree(p);
            FIELD(s, s32, 0x36C) = 0;
        }
    }
    s = (u8 *)D_801EFE48_ovl_23B220;
    if (FIELD(s, void *, 0x34C) != NULL) {
        HFree(FIELD(s, void *, 0x34C));
        FIELD(s, void *, 0x34C) = NULL;
        s = (u8 *)D_801EFE48_ovl_23B220;
    }
    if (FIELD(s, void *, 0x244) != NULL) {
        HFree(FIELD(s, void *, 0x244));
        FIELD(s, void *, 0x244) = NULL;
        FIELD(s, s32, 0x248) = 0;
    }
    s = (u8 *)D_801EFE48_ovl_23B220;
    if (FIELD(s, void *, 0x60C) != NULL) {
        HFree(FIELD(s, void *, 0x60C));
        FIELD(s, void *, 0x60C) = NULL;
        s = (u8 *)D_801EFE48_ovl_23B220;
    }
    if (FIELD(s, void *, 0x5C4) != NULL) {
        HFree(FIELD(s, void *, 0x5C4));
        FIELD(s, void *, 0x5C4) = NULL;
    }
    s = (u8 *)D_801EFE48_ovl_23B220;
    {
        void *p = FIELD(s, void *, 0x5C8);

        i = 0;
        if (p != NULL) {
            HFree(p);
            FIELD(s, s32, 0x5C8) = 0;
        }
    }
    for (off = 0x5D4; i < 2; off += 0x1C) {
        pp = (void **)((u8 *)D_801EFE48_ovl_23B220 + off + 4);
        i++;
        if (*pp != NULL) {
            HFree(*pp);
            *pp = NULL;
        }
    }
    func_8017A714();
    HFree(D_801EFE48_ovl_23B220);
    D_801EFE48_ovl_23B220 = NULL;
}

s32 func_801BEF14(void *img, void *pal, u8 fmt, u8 siz, s32 w, s32 h, s32 x, s32 y, s32 c);
s32 func_801BF59C(void *img, void *pal, u8 fmt, u8 siz, s32 w, s32 h, s32 x, s32 y);

/* Copies the rectangle (x0, y0) - (x1, y1) of texture src to texture dst at (dx, dy), pixel by
 * pixel through each texture's own format and palette */
void func_801ED224_ovl_23B220(u8 *dst, s32 dx, s32 dy, u8 *src, Rect23 r) {
    u8 *sImg = src + 8;
    u8 *sPal = sImg + func_801BE978(src[3], FIELD(src, u16, 4), FIELD(src, u16, 6));
    u8 *dImg = dst + 8;
    u8 *dPal = dImg + func_801BE978(dst[3], FIELD(dst, u16, 4), FIELD(dst, u16, 6));
    s32 i, j;

    for (j = 0; j < r.y1 - r.y0; j++) {
        for (i = 0; i < r.x1 - r.x0; i++) {
            func_801BEF14(dImg, dPal, dst[2], dst[3], FIELD(dst, u16, 4), FIELD(dst, u16, 6), dx + i, dy + j,
                          func_801BF59C(sImg, sPal, src[2], src[3], FIELD(src, u16, 4), FIELD(src, u16, 6),
                                        r.x0 + i, r.y0 + j));
        }
    }
}
