#include "common.h"
#include "chunk.h"
#include "heap.h"
#include "nusys.h"

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

void func_801CCA5C_ovl_1F0A30();
void bzero(void *p, s32 n);
void nuGfxTaskAllEndWait(void);
s32 func_801CE38C_ovl_1F0A30(void);
extern u8 *D_801D06D8_ovl_1F0A30;
extern u8 D_800E7A0C;
extern void *D_800C4BB8;
extern void *D_800A8204[3];
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern NUScTask D_800E7D90[];
extern OSMesgQueue D_800E9BA8;
extern OSMesgQueue D_800E8B4C;
extern u64 D_8009ECB0[];
extern u64 D_8009ED80[];
extern u64 D_800A5110[];
extern u64 D_800A69D0[];
extern u64 D_800AD590[];
extern u64 D_800AD920[];
extern u64 D_800E8710[];
extern u64 D_800C7970[];
extern u64 D_800C6D70[];
extern u32 D_800A9E70;
extern volatile u32 D_800E79A4;
extern u8 D_801CFCE8_ovl_1F0A30[];
typedef struct {
    u8 unk00[0x84];
    u8 *data;
    u8 unk88[0x100];
    s32 size;
} BgJob_20FDC0;
s32 func_801CE064_ovl_1F0A30(s32 type, u16 w, u16 h, u8 *data, u8 a, u8 b);
extern u64 D_8009F540[];
extern u64 jpegTextStart[];
extern u64 D_800AC050[];
extern u64 D_800AC140[];
f64 func_8007FD90(void);
/* --- end decls --- */

void *memcpy(void *dst, const void *src, s32 n);

/* Insertion sort of n elements of the given size, ordered by cmp */
void *memcpy(void *dst, const void *src, s32 n);

/* Insertion sort of n elements of the given size, ordered by cmp */
inline void func_801CC930_ovl_1F0A30(u8 *base, s32 size, s32 n, s32 (*cmp)(void *, void *)) {
    void *tmp = HMalloc(size);
    s32 i;
    s32 j;
    u8 *src;

    for (i = 1; i < n; i++) {
        src = base;
        src += i * size;
        memcpy(tmp, src, size);
        for (j = i - 1; j >= 0 && cmp(tmp, base + j * size) < 0; j--) {
            memcpy(base + (j + 1) * size, base + j * size, size);
        }
        memcpy(base + (j + 1) * size, tmp, size);
    }
    HFree(tmp);
}

/* Quicksort of n elements of the given size, ordered by cmp: partitions with an explicit stack
 * of pending ranges down to fewer than 11 elements, then finishes with an insertion sort */
#ifdef NON_MATCHING
/* 1 instruction short: lo, depth and the pivot get saved registers or stack slots where the original keeps them in t1/t2/t0 with caller-saves around each cmp call (frame 0xC8 vs 0xB8) */
void func_801CCA5C_ovl_1F0A30(u8 *base, s32 size, s32 n, s32 (*cmp)(void *, void *)) {
    s32 stk[24];
    s32 *sp;
    s32 lo;
    s32 hi;
    s32 depth;
    s32 i;
    s32 j;
    s32 io;
    s32 jo;
    u8 *pivot;
    u8 *p;

    lo = 0;
    hi = n - 1;
    depth = 0;
    sp = stk;
loop:
    if (hi - lo < 11) {
        if (depth == 0) {
            goto done;
        }
        sp--;
        depth--;
        lo = sp[0];
        hi = sp[12];
    }
    jo = hi * size;
    pivot = base + (lo + hi) / 2 * size;
    i = lo;
    j = hi;
    io = i * size;
scan:
    p = i * size + base;
up:
    if (cmp(p, pivot) < 0) {
        p += size;
        io += size;
        i++;
        goto up;
    }
    p = j * size + base;
down:
    if (cmp(pivot, p) < 0) {
        p -= size;
        jo -= size;
        j--;
        goto down;
    }
    if (i < j) {
        u8 *a = base + io;
        u8 *b = base + jo;
        s32 k;

        for (k = size - 1; k != -1; k--) {
            u8 t = *a;
            *a++ = *b;
            *b++ = t;
        }
        io += size;
        i++;
        jo -= size;
        j--;
        goto scan;
    }
    if (hi - j < i - lo) {
        if (i - lo < 11) {
            lo = j + 1;
        } else {
            sp[0] = lo;
            sp[12] = i - 1;
            sp++;
            depth++;
            lo = j + 1;
        }
    } else {
        if (hi - j < 11) {
            hi = i - 1;
        } else {
            sp[0] = j + 1;
            sp[12] = hi;
            sp++;
            depth++;
            hi = i - 1;
        }
    }
    goto loop;
done:
    func_801CC930_ovl_1F0A30(base, size, n, cmp);
}
#else
INCLUDE_ASM("asm/nonmatchings/20FDC0", func_801CCA5C_ovl_1F0A30);
#endif

void func_801CCD4C_ovl_1F0A30(s32 a, s32 b, s32 c) {
    ((void (*)())func_801CCA5C_ovl_1F0A30)(a, c, b);
}

void guLookAtF(f32 mf[4][4], f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);
void guMtxCatF(f32 m[4][4], f32 n[4][4], f32 r[4][4]);
f32 sinf(f32 x);
f32 cosf(f32 x);

/* Projects point p through model matrix m and the camera (eye, at, up, vertical fov in degrees)
 * to 320x240 screen coordinates */
void func_801CCD70_ovl_1F0A30(f32 *out, f32 *p, f32 m[4][4], f32 *at, f32 *eye, f32 *up, f32 fovy) {
    f32 mf[4][4];
    f32 v[3];
    f32 t; /* half the fov in radians, then the view depth scale */
    f32 x;
    f32 y;
    f32 z;

    guLookAtF(mf, eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);
    guMtxCatF(m, mf, mf);
    x = p[0];
    y = p[1];
    z = p[2];
    v[0] = x * mf[0][0] + y * mf[1][0] + z * mf[2][0] + mf[3][0];
    v[1] = x * mf[0][1] + y * mf[1][1] + z * mf[2][1] + mf[3][1];
    v[2] = x * mf[0][2] + y * mf[1][2] + z * mf[2][2] + mf[3][2];
    t = fovy * 3.14159265358979312 / 360.0;
    t = v[2] * sinf(t) / cosf(t);
    out[0] = (320.0 - v[0] * 320.0f / (t * 1.3)) / 2.0;
    out[1] = (240.0f - v[1] * 240.0f / t) / 2.0f;
}

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
/* Loop counter compare differs. */
void func_801CD01C_ovl_1F0A30(u8 *dst, u8 *src, s32 n)
{
  dst += n;
  src += n;
  while (0 != (n--))
  {
    *(--dst) = *(--src);
  }

}

/* Number of decimal digits in n */
s32 func_801CD058_ovl_1F0A30(u32 n) {
    if (n < 10) {
        return 1;
    }
    if (n < 100) {
        return 2;
    }
    if (n < 1000) {
        return 3;
    }
    if (n < 10000) {
        return 4;
    }
    if (n < 100000) {
        return 5;
    }
    if (n < 1000000) {
        return 6;
    }
    if (n < 10000000) {
        return 7;
    }
    if (n < 100000000) {
        return 8;
    }
    if (n < 1000000000) {
        return 9;
    }
    return 10;
}

/* Random integer in [-n, n] */
s32 func_801CD108_ovl_1F0A30(s32 n) {
    s32 r = n + 1;

    while (r < -n || n < r) {
        r = func_8007FD90() / 1.5 * n;
    }
    return r;
}

/* Whether tiles a and b (1-based) are blocked in direction dir (2/8/4/16 test wall bits 8/4/2/1) */
s32 func_801CD19C_ovl_1F0A30(s32 a, s32 b, u32 dir) {
    u8 *t;
    s32 r;

    switch (dir) {
        case 2:
            t = D_801D06D0_ovl_1F0A30;
            r = 0;
            if ((t[a - 1] & 8) || (t[b - 1] & 8)) {
                r = 1;
            }
            return r;
        case 8:
            t = D_801D06D0_ovl_1F0A30;
            r = 0;
            if ((t[a - 1] & 4) || (t[b - 1] & 4)) {
                r = 1;
            }
            return r;
        case 4:
            t = D_801D06D0_ovl_1F0A30;
            r = 0;
            if ((t[a - 1] & 2) || (t[b - 1] & 2)) {
                r = 1;
            }
            return r;
        case 16:
            t = D_801D06D0_ovl_1F0A30;
            r = 0;
            if ((t[a - 1] & 1) || (t[b - 1] & 1)) {
                r = 1;
            }
            return r;
    }
    return 0;
}

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
void CombinationTablesLoad(void) {
    u32 o;

    D_801CFCC0_ovl_1F0A30 = HMalloc(ChunkSize(0x31823A));
    LoadChunkRaw(D_801CFCC0_ovl_1F0A30, 0x31823A);
    o = ((u16 *)D_801CFCC0_ovl_1F0A30)[0];
    D_801D06D4_ovl_1F0A30 = (u8 *)D_801CFCC0_ovl_1F0A30 + o;
    o = ((u16 *)D_801CFCC0_ovl_1F0A30)[1];
    D_801D06D8_ovl_1F0A30 = (u8 *)D_801CFCC0_ovl_1F0A30 + o;
    o = ((u16 *)D_801CFCC0_ovl_1F0A30)[2];
    D_801D06DC_ovl_1F0A30 = (u8 *)D_801CFCC0_ovl_1F0A30 + o;
    D_801D06D0_ovl_1F0A30 = HMalloc(ChunkSize(0x3188AE));
    LoadChunkRaw(D_801D06D0_ovl_1F0A30, 0x3188AE);
}

void func_801CD4A0_ovl_1F0A30(void) {
    HFree(D_801CFCC0_ovl_1F0A30);
    D_801CFCC0_ovl_1F0A30 = NULL;
    HFree(D_801D06D0_ovl_1F0A30);
    D_801D06D0_ovl_1F0A30 = NULL;
}

/* Sends the JPEG decode RSP task for a w x h image (in 16x16 blocks) */
void func_801CD4E0_ovl_1F0A30(s8 mode, void *data_ptr, s16 w, s16 h) {
    s32 bw = w / 16;
    s32 bh = h / 16;
    NUScTask *t = (NUScTask *)D_801D06E0_ovl_1F0A30;
    u32 mask;

    t->framebuffer = FIELD(t, void *, 0x64);
    t->state = 1;
    t->next = D_800E7D90;
    t->msgQ = &D_800E9BA8;
    t->msg = D_801CFCE8_ovl_1F0A30;
    t->flags = 2;
    t->list.t.type = 4;
    t->list.t.ucode_boot = D_8009ECB0;
    t->list.t.ucode_boot_size = (s32)D_8009ED80 - (s32)D_8009ECB0;
    t->list.t.ucode = jpegTextStart;
    t->list.t.ucode_size = (s32)D_8009F540 - (s32)jpegTextStart;
    t->list.t.ucode_data = D_800AC050;
    t->list.t.ucode_data_size = (s32)D_800AC140 - (s32)D_800AC050;
    t->list.t.flags = 0;
    t->list.t.dram_stack = NULL;
    t->list.t.dram_stack_size = 0;
    t->list.t.output_buff = NULL;
    t->list.t.output_buff_size = NULL;
    t->list.t.data_ptr = data_ptr;
    t->list.t.data_size = bw * bh;
    t->list.t.yield_data_ptr = NULL;
    t->list.t.yield_data_size = mode;
    mask = osSetIntMask(1);
    D_800E79A4++;
    osSetIntMask(mask);
    osWritebackDCacheAll();
    ((u8 *)D_801D06E0_ovl_1F0A30)[0x7E]++;
    osSendMesg(&D_800E8B4C, D_801D06E0_ovl_1F0A30, 1);
}

/* Sends the JPEG decode RSP task (data at data_ptr) to the scheduler, like nuGfxTaskStart */
void func_801CD658_ovl_1F0A30(void *data_ptr, u32 data_size, s32 unused, u32 flags) {
    NUScTask *t = (NUScTask *)D_801D06E0_ovl_1F0A30;
    u32 mask;

    t->framebuffer = FIELD(t, void *, 0x64);
    t->state = 1;
    t->next = D_800E7D90;
    t->msgQ = &D_800E9BA8;
    t->msg = D_801CFCE8_ovl_1F0A30;
    t->list.t.type = 1;
    t->list.t.ucode_boot = D_8009ECB0;
    t->list.t.ucode_boot_size = (s32)D_8009ED80 - (s32)D_8009ECB0;
    t->list.t.ucode = D_800A5110;
    t->list.t.ucode_size = (s32)D_800A69D0 - (s32)D_800A5110;
    t->list.t.data_ptr = data_ptr;
    t->flags = flags;
    t->list.t.flags = 0;
    t->list.t.ucode_data = D_800AD590;
    t->list.t.ucode_data_size = (s32)D_800AD920 - (s32)D_800AD590;
    t->list.t.dram_stack = D_800E8710;
    t->list.t.dram_stack_size = 0x400;
    t->list.t.output_buff = D_800C7970;
    t->list.t.data_size = data_size;
    t->list.t.output_buff_size = (u64 *)(D_800A9E70 + (u32)D_800C7970);
    t->list.t.yield_data_ptr = D_800C6D70;
    t->list.t.yield_data_size = 0xC00;
    mask = osSetIntMask(1);
    D_800E79A4++;
    osSetIntMask(mask);
    osWritebackDCacheAll();
    osSendMesg(&D_800E8B4C, D_801D06E0_ovl_1F0A30, 1);
}

typedef struct {
    u32 w0;
    u32 w1;
} Gfx20F;
extern u8 D_801CFCD0_ovl_1F0A30[];

/* Background JPEG display list: YUV colour conversion setup for the frame buffer, then one
 * 16x16 YUV tile load and decode command per block of the image */
void func_801CD7A0_ovl_1F0A30(Gfx20F **gp) {
    Gfx20F *g = *gp;
    u8 *img;
    u8 i;
    u8 j;

    {
        Gfx20F *_g = g++;
        _g->w0 = 0xDB060000;
        _g->w1 = 0;
    }
    {
        Gfx20F *_g = g++;
        _g->w0 = 0xE7000000;
        _g->w1 = 0;
    }
    {
        Gfx20F *_g = g++;
        _g->w0 = 0xE3000A01;
        _g->w1 = 0;
    }
    {
        Gfx20F *_g = g++;
        _g->w0 = 0xE3000800;
        _g->w1 = 0;
    }
    {
        Gfx20F *_g = g++;
        _g->w0 = 0xFF10013F;
        _g->w1 = FIELD(D_801D06E0_ovl_1F0A30, u32, 0x64);
    }
    {
        Gfx20F *_g = g++;
        _g->w0 = 0xED000000;
        _g->w1 = 0x005003C0;
    }
    {
        Gfx20F *_g = g++;
        _g->w0 = 0xE3000C00;
        _g->w1 = 0;
    }
    {
        Gfx20F *_g = g++;
        _g->w0 = 0xE3000F00;
        _g->w1 = 0;
    }
    {
        Gfx20F *_g = g++;
        _g->w0 = 0xE3001001;
        _g->w1 = 0;
    }
    {
        Gfx20F *_g = g++;
        _g->w0 = 0xE3000D01;
        _g->w1 = 0;
    }
    {
        Gfx20F *_g = g++;
        _g->w0 = 0xE3001402;
        _g->w1 = 0;
    }
    {
        Gfx20F *_g = g++;
        _g->w0 = 0xEC15FD5D;
        _g->w1 = 0x3B78E42A;
    }
    {
        Gfx20F *_g = g++;
        _g->w0 = 0xE3001201;
        _g->w1 = 0;
    }
    {
        Gfx20F *_g = g++;
        _g->w0 = 0xFC17FE2F;
        _g->w1 = 0x77FCF87C;
    }
    {
        Gfx20F *_g = g++;
        _g->w0 = 0xE3001700;
        _g->w1 = 0;
    }
    {
        Gfx20F *_g = g++;
        _g->w0 = 0xE200001C;
        _g->w1 = 0x0F0A4000;
    }
    {
        Gfx20F *_g = g++;
        _g->w0 = 0xE2001E01;
        _g->w1 = 0;
    }
    {
        Gfx20F *_g = g++;
        _g->w0 = 0xE3001801;
        _g->w1 = 0xC0;
    }
    img = FIELD(D_801D06E0_ovl_1F0A30, u8 *, 0x68);
    for (i = 0; i < FIELD(D_801D06E0_ovl_1F0A30, s16, 0x7A) / 16; i++) {
        for (j = 0; j < FIELD(D_801D06E0_ovl_1F0A30, s16, 0x78) / 16; j++) {
            {
                Gfx20F *_g = g++;
                _g->w0 = 0xFD30000F;
                _g->w1 = (u32)img;
            }
            {
                Gfx20F *_g = g++;
                _g->w0 = 0xF5300400;
                _g->w1 = 0x07080200;
            }
            {
                Gfx20F *_g = g++;
                _g->w0 = 0xE6000000;
                _g->w1 = 0;
            }
            {
                Gfx20F *_g = g++;
                _g->w0 = 0xF4000000;
                _g->w1 = 0x0703C03C;
            }
            {
                Gfx20F *_g = g++;
                _g->w0 = 0xDC070002;
                _g->w1 = (u32)&FIELD(D_801D06E0_ovl_1F0A30, Gfx20F *, 0x60)[i * (FIELD(D_801D06E0_ovl_1F0A30, s16, 0x78) / 16) + j];
            }
            {
                Gfx20F *_g = g++;
                _g->w0 = 0xDA000000;
                _g->w1 = (u32)D_801CFCD0_ovl_1F0A30;
            }
            img += 0x300;
        }
    }
    *gp = g;
}

void func_801CDB98_ovl_1F0A30(void) {
    if (D_801D06E0_ovl_1F0A30->step == 1) {
        D_801D06E0_ovl_1F0A30->step++;
    }
    if (D_801D06E0_ovl_1F0A30->step == 4) {
        D_801D06E0_ovl_1F0A30->step++;
    }
}

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif

/* Closes the display list (last == 0: full sync + end, records its end) or sends it to the
 * scheduler as a graphics task, like nuGfxTaskStart */
void func_801CDBE4_ovl_1F0A30(u8 last) {
    NUScTask *t;
    Gfx20F *gp;
    Gfx20F *start;
    Gfx20F *end;
    u32 mask;

    if (!last) {
        gp = FIELD(D_801D06E0_ovl_1F0A30, Gfx20F *, 0x5C);
        func_801CD7A0_ovl_1F0A30(&gp);
        {
            Gfx20F *_g = gp++;
            _g->w0 = 0xE9000000;
            _g->w1 = 0;
        }
        {
            Gfx20F *_g = gp++;
            _g->w0 = 0xDF000000;
            _g->w1 = 0;
        }
        ((u8 *)D_801D06E0_ovl_1F0A30)[0x7E]++;
        FIELD(D_801D06E0_ovl_1F0A30, Gfx20F *, 0x58) = gp;
        return;
    }
    ((u8 *)D_801D06E0_ovl_1F0A30)[0x7E]++;
    t = (NUScTask *)D_801D06E0_ovl_1F0A30;
    end = FIELD(t, Gfx20F *, 0x58);
    start = FIELD(t, Gfx20F *, 0x5C);
    t->framebuffer = FIELD(t, void *, 0x64);
    t->state = 1;
    t->next = D_800E7D90;
    t->msgQ = &D_800E9BA8;
    t->msg = D_801CFCE8_ovl_1F0A30;
    t->flags = 0;
    t->list.t.type = 1;
    t->list.t.ucode_boot = D_8009ECB0;
    t->list.t.ucode_boot_size = (s32)D_8009ED80 - (s32)D_8009ECB0;
    t->list.t.ucode = D_800A5110;
    t->list.t.ucode_size = (s32)D_800A69D0 - (s32)D_800A5110;
    t->list.t.flags = 0;
    t->list.t.ucode_data = D_800AD590;
    t->list.t.ucode_data_size = (s32)D_800AD920 - (s32)D_800AD590;
    t->list.t.dram_stack = D_800E8710;
    t->list.t.dram_stack_size = 0x400;
    t->list.t.output_buff = D_800C7970;
    t->list.t.output_buff_size = (u64 *)(D_800A9E70 + (u32)D_800C7970);
    t->list.t.data_ptr = (u64 *)start;
    t->list.t.data_size = (end - start) * sizeof(Gfx20F);
    t->list.t.yield_data_ptr = D_800C6D70;
    t->list.t.yield_data_size = 0xC00;
    mask = osSetIntMask(1);
    D_800E79A4++;
    osSetIntMask(mask);
    osWritebackDCacheAll();
    osSendMesg(&D_800E8B4C, D_801D06E0_ovl_1F0A30, 1);
}

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void func_80080998(void *dst, void *src, s32 n);

/* Steps the background JPEG job: 0 starts the decode task and closes its display list once the
 * decoder reaches step 2; 3 sends it and, at step 5, copies the decoded rows into the image (a
 * "64" bitmap header unless raw) */
void func_801CDDC8_ovl_1F0A30(void) {
    u8 *src;
    s32 row;
    s16 y;

    nuGfxTaskAllEndWait();
    if (((u8 *)D_801D06E0_ovl_1F0A30)[0x7E] == 0) {
        if (((u8 *)D_801D06E0_ovl_1F0A30)[0x80] == 0) {
            FIELD(D_801D06E0_ovl_1F0A30, u8 *, 0x70) = FIELD(D_801D06E0_ovl_1F0A30, u8 *, 0x74) + 8;
        } else {
            FIELD(D_801D06E0_ovl_1F0A30, u8 *, 0x70) = FIELD(D_801D06E0_ovl_1F0A30, u8 *, 0x74);
        }
        func_801CD4E0_ovl_1F0A30(FIELD(D_801D06E0_ovl_1F0A30, s8, 0x7D), FIELD(D_801D06E0_ovl_1F0A30, void *, 0x68),
                                 FIELD(D_801D06E0_ovl_1F0A30, s16, 0x78), FIELD(D_801D06E0_ovl_1F0A30, s16, 0x7A));
        while (((u8 *)D_801D06E0_ovl_1F0A30)[0x7E] != 2) {
            nuGfxTaskAllEndWait();
        }
        nuGfxTaskAllEndWait();
        func_801CDBE4_ovl_1F0A30(0);
    } else if (((u8 *)D_801D06E0_ovl_1F0A30)[0x7E] == 3) {
        func_801CDBE4_ovl_1F0A30(1);
        while (((u8 *)D_801D06E0_ovl_1F0A30)[0x7E] != 5) {
            nuGfxTaskAllEndWait();
        }
        src = FIELD(D_801D06E0_ovl_1F0A30, u8 *, 0x64);
        row = FIELD(D_801D06E0_ovl_1F0A30, s16, 0x78) * 2;
        for (y = 0; y < FIELD(D_801D06E0_ovl_1F0A30, s16, 0x7A); y++) {
            func_80080998(FIELD(D_801D06E0_ovl_1F0A30, u8 *, 0x70), src,
                          FIELD(D_801D06E0_ovl_1F0A30, s16, 0x78) * 2);
            FIELD(D_801D06E0_ovl_1F0A30, u8 *, 0x70) += row;
            src += 0x280;
        }
        if (((u8 *)D_801D06E0_ovl_1F0A30)[0x80] == 0) {
            FIELD(D_801D06E0_ovl_1F0A30, u8 *, 0x74)[0] = '6';
            FIELD(D_801D06E0_ovl_1F0A30, u8 *, 0x74)[1] = '4';
            FIELD(D_801D06E0_ovl_1F0A30, u8 *, 0x74)[2] = 0;
            FIELD(D_801D06E0_ovl_1F0A30, u8 *, 0x74)[3] = 2;
            FIELD(FIELD(D_801D06E0_ovl_1F0A30, u8 *, 0x74), u16, 4) = FIELD(D_801D06E0_ovl_1F0A30, s16, 0x78);
            FIELD(FIELD(D_801D06E0_ovl_1F0A30, u8 *, 0x74), u16, 6) = FIELD(D_801D06E0_ovl_1F0A30, s16, 0x7A);
        }
        ((u8 *)D_801D06E0_ovl_1F0A30)[0x7E]++;
    }
}

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

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} BgTile20F;
typedef struct {
    u8 unk00[0x68];
    void *img;
    u8 unk6C[0xC];
    s16 w;
    s16 h;
} BgState20F;
void HuDecode(void *src, void *dst);
void func_8008AFA0(void (*func)(void));

static inline void BgFramePair(u8 *o) {
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

/* Sets up a background image job: w x h pixels in 16x16 tiles, buffers for the decoded image,
 * the tile list and the display list, then decodes the "HU" data (freeing it if a == 1) and
 * hooks func_801CDB98 as the per-frame step. Returns -1 if a JPEG job is still busy */
s32 func_801CE064_ovl_1F0A30(s32 type, u16 w, u16 h, u8 *data, u8 a, u8 b) {
    u8 o[2];
    s16 n;
    s16 k;
    s16 i;
    s16 j;

    if (D_801D06E0_ovl_1F0A30 == NULL) {
        D_801D06E0_ovl_1F0A30 = HMalloc(0x190);
        bzero(D_801D06E0_ovl_1F0A30, 0x190);
        ((u8 *)D_801D06E0_ovl_1F0A30)[0x81] = 0;
    } else if (((u8 *)D_801D06E0_ovl_1F0A30)[0x81] == 0) {
        return -1;
    }
    n = (w >> 4) * (h >> 4);
    if (b == 0) {
        FIELD(D_801D06E0_ovl_1F0A30, void *, 0x74) = HMallocBack(w * h * 2 + 8);
    } else {
        FIELD(D_801D06E0_ovl_1F0A30, void *, 0x74) = HMalloc(w * h * 2);
    }
    BgFramePair(o);
    FIELD(D_801D06E0_ovl_1F0A30, void *, 0x64) = D_800A8204[o[0]];
    FIELD(D_801D06E0_ovl_1F0A30, BgTile20F *, 0x60) = HMalloc(n * 8);
    FIELD(D_801D06E0_ovl_1F0A30, void *, 0x5C) = D_800A8204[o[1]];
    ((u8 *)D_801D06E0_ovl_1F0A30)[0x80] = b;
    ((BgState20F *)D_801D06E0_ovl_1F0A30)->img = HMalloc(n * 0x300);
    ((BgState20F *)D_801D06E0_ovl_1F0A30)->w = w;
    ((BgState20F *)D_801D06E0_ovl_1F0A30)->h = h;
    D_801D06E0_ovl_1F0A30->step = 0;
    FIELD(D_801D06E0_ovl_1F0A30, s16, 0x7C) = type;
    FIELD(D_801D06E0_ovl_1F0A30, u8 *, 0x6C) = data;
    ((u8 *)D_801D06E0_ovl_1F0A30)[0x7F] = a;
    k = 0;
    for (i = 0; i < (h >> 4); i++) {
        for (j = 0; j < (w >> 4); j++) {
            FIELD(D_801D06E0_ovl_1F0A30, BgTile20F *, 0x60)[k].x = j * 64;
            FIELD(D_801D06E0_ovl_1F0A30, BgTile20F *, 0x60)[k].y = i * 64;
            FIELD(D_801D06E0_ovl_1F0A30, BgTile20F *, 0x60)[k].w = 0x400;
            FIELD(D_801D06E0_ovl_1F0A30, BgTile20F *, 0x60)[k].h = 0x400;
            k++;
        }
    }
    HuDecode(FIELD(D_801D06E0_ovl_1F0A30, u8 *, 0x6C), FIELD(D_801D06E0_ovl_1F0A30, void *, 0x68));
    if (((u8 *)D_801D06E0_ovl_1F0A30)[0x7F] == 1) {
        HFree(FIELD(D_801D06E0_ovl_1F0A30, u8 *, 0x6C) - 8);
    }
    func_8008AFA0(func_801CDB98_ovl_1F0A30);
    return 0;
}

/* Image header at the start of a background file and of each part's data */
typedef struct {
    /* 0x0 */ u8 unk0[2];
    /* 0x2 */ u8 type;
    /* 0x3 */ u8 count; /* parts that follow (file header only) */
    /* 0x4 */ u16 w;
    /* 0x6 */ u16 h;
} BgHdr20F;
/* Part header: followed by size bytes (an image header and its data) */
typedef struct BgPart20F {
    /* 0x0 */ u8 unk0[2];
    /* 0x2 */ u8 type;
    /* 0x3 */ u8 unk3;
    /* 0x4 */ u16 w;
    /* 0x6 */ u16 h;
    /* 0x8 */ s32 size;
    /* 0xC */ struct BgPart20F *next;
} BgPart20F;
/* The JPEG job state at D_801D06E0 as this function sees it */
typedef struct {
    /* 0x000 */ u8 unk00[0x60];
    /* 0x060 */ void *tiles;
    /* 0x064 */ u8 unk64[4];
    /* 0x068 */ void *img;
    /* 0x06C */ u8 unk6C[8];
    /* 0x074 */ u8 *out;
    /* 0x078 */ u8 unk78[6];
    /* 0x07E */ u8 step;
    /* 0x07F */ u8 unk7F[2];
    /* 0x081 */ u8 n;   /* parts decoded so far */
    /* 0x082 */ u8 own; /* 1: the file (data[0]) is freed at the end */
    /* 0x083 */ u8 unk83;
    /* 0x084 */ u8 *data[65]; /* [0] the file, [1..] each decoded part */
    /* 0x188 */ s32 size;
} BgSeq20F;
#define BGSEQ20F ((BgSeq20F *)D_801D06E0_ovl_1F0A30)

/* Finishes the current JPEG part. While parts remain, it starts the decode of the next one and
 * returns 0. After the last part it packs the file header and every decoded part (part header +
 * pixels, linked through next) into fresh blocks, frees the job and returns the first block;
 * a single-image job returns its output buffer directly. */
s32 func_801CE38C_ovl_1F0A30(void) {
    BgHdr20F hdr;
    BgPart20F parts[64];
    BgSeq20F *s;
    BgHdr20F *file;
    u8 count;
    u8 i;
    s32 bytes;
    s32 sz;
    BgPart20F *blk;
    BgPart20F *last;
    u8 *ret;

    last = NULL;
    ret = NULL;
    while (D_801D06E0_ovl_1F0A30->step != 6) {
        nuGfxTaskAllEndWait();
        func_801CDDC8_ovl_1F0A30();
    }
    func_8008AFA0(NULL);
    nuGfxTaskAllEndWait();
    HFree(BGSEQ20F->img);
    HFree(BGSEQ20F->tiles);
    file = (BgHdr20F *)BGSEQ20F->out;
    if (BGSEQ20F->n == 0) {
        s = BGSEQ20F;
        D_801D06E0_ovl_1F0A30 = NULL;
        HFree(s);
        return (s32)file;
    }
    /* data[n] = file, spelled as an int sum: the indexed form adds index + base, the original base + index */
    *(u8 **)((s32)BGSEQ20F + (BGSEQ20F->n << 2) + 0x84) = (u8 *)file;
    ((u8 *)D_801D06E0_ovl_1F0A30)[0x81]++;
    ((u8 *)D_801D06E0_ovl_1F0A30)[0x7E]++;
    file = (BgHdr20F *)BGSEQ20F->data[0];
    count = file->count;
    if (count < BGSEQ20F->n) {
        u8 *q;

        func_80080998(&hdr, file, 8);
        q = (u8 *)(file + 1);
        for (i = 0; i < count; i++) {
            last = (BgPart20F *)q;
            func_80080998(&parts[i], q, 16);
            q = (u8 *)last + (last->size + 16);
        }
        if (BGSEQ20F->own == 1) {
            HFree(BGSEQ20F->data[0]);
        }
        sz = 8;
        hdr.type = 1;
        for (i = 0; i < count; i++) {
            bytes = parts[i].w * parts[i].h * 2;
            blk = HMallocBack((sz += 0x10) + bytes);
            if (i == 0) {
                func_80080998(blk, &hdr, 8);
                ret = (u8 *)blk;
                blk = (BgPart20F *)(ret + 8);
                last = blk;
            } else {
                last->next = blk;
                last = blk;
            }
            parts[i].size = bytes;
            func_80080998(blk, &parts[i], 16);
            func_80080998(blk + 1, *(u8 **)((i * 4) + (s32)BGSEQ20F + 0x88), bytes);
            HFree(*(u8 **)((i * 4) + (s32)BGSEQ20F + 0x88));
            sz = 0;
        }
        last->next = NULL;
        HFree(D_801D06E0_ovl_1F0A30);
        D_801D06E0_ovl_1F0A30 = NULL;
        return (s32)ret;
    }
    BGSEQ20F->size = 8;
    ret = (u8 *)(file + 1);
    count = file->count;
    for (i = 0; i < count; i++) {
        s32 type;
        s32 w;
        s32 h;

        last = (BgPart20F *)ret;
        ret += 0x10;
        type = ((BgHdr20F *)ret)->type;
        w = ((BgHdr20F *)ret)->w;
        h = ((BgHdr20F *)ret)->h;
        BGSEQ20F->size += last->w * last->h * 2 + 0x10;
        ret += 8;
        if (BGSEQ20F->n == i + 1) {
            func_801CE064_ovl_1F0A30((s8)type, w, h, ret, 0, 1);
            return 0;
        }
        ret += last->size - 8;
    }
    return 0;
}

/* Background image: "HU" data is decoded straight away; anything else is a JPEG job
 * (state block at D_801BA6D0) and returns 1 */
s32 func_801CE704_ovl_1F0A30(u8 *data, u8 a, u8 b) {
    u8 *p = data;
    s8 type = p[2];
    u16 w = *(u16 *)(p + 4);
    u16 h = *(u16 *)(p + 6);
    u8 *q;
    u8 *r;

    nuGfxTaskAllEndWait();
    p += 8;
    if (*(u16 *)data == 0x4855) {
        func_801CE064_ovl_1F0A30(type, w, h, p, a, b);
        return 0;
    } else {
        D_801D06E0_ovl_1F0A30 = HMalloc(0x190);
        bzero(D_801D06E0_ovl_1F0A30, 0x190);
        ((u8 *)D_801D06E0_ovl_1F0A30)[0x7E] = 0;
        ((BgJob_20FDC0 *)D_801D06E0_ovl_1F0A30)->data = data;
        ((u8 *)D_801D06E0_ovl_1F0A30)[0x81] = 1;
        ((BgJob_20FDC0 *)D_801D06E0_ovl_1F0A30)->size = 0;
        ((u8 *)D_801D06E0_ovl_1F0A30)[0x82] = a;
        ((BgJob_20FDC0 *)D_801D06E0_ovl_1F0A30)->size = 8;
        r = p;
        p += 0x10;
        ((BgJob_20FDC0 *)D_801D06E0_ovl_1F0A30)->size = *(u16 *)(r + 4) * *(u16 *)(r + 6) * 2 + 0x18;
        q = p;
        p += 8;
        func_801CE064_ovl_1F0A30((s8)q[2], *(u16 *)(q + 4), *(u16 *)(q + 6), p, 0, 1);
        return 1;
    }
}

void func_801CE858_ovl_1F0A30(void) {
    do {
        nuGfxTaskAllEndWait();
    } while (!func_801CE38C_ovl_1F0A30());
}
