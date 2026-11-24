#include "common.h"
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

INCLUDE_ASM("asm/nonmatchings/20FDC0", func_801CD7A0_ovl_1F0A30);

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
typedef struct {
    u32 w0;
    u32 w1;
} Gfx20F;

void func_801CD7A0_ovl_1F0A30(Gfx20F **gp);

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
void *HMallocBack(s32 size);
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

typedef struct BgPart20F {
    u8 unk0[4];
    u16 w;
    u16 h;
    s32 size;
    struct BgPart20F *next;
} BgPart20F;
typedef struct {
    u8 unk00[0x60];
    BgTile20F *tiles;
    void *fb;
    void *img;
    u8 *data;
    u8 *out;
    u8 *buf;
    s16 w;
    s16 h;
    s16 type;
    u8 step;
    u8 a;
    u8 b;
    u8 busy;
    u8 freeSrc;
    u8 unk83;
    u8 *parts[0x41];
    s32 size;
} BgJobFull20F;

/* NON_MATCHING: 2 instructions short; the header-copy loop keeps its cursor in one register where the
 * original computes it in a1 and copies it (and the count) each pass; s4/s5/s6 allocation differs */
#ifdef NON_MATCHING
/* Finishes the background job: runs it to step 6 and frees its buffers. A single image returns
 * its pixels; a multi-part image starts decoding the next part (returns 0), and once every part
 * is decoded links them into one block (header + part list) and returns it */
s32 func_801CE38C_ovl_1F0A30(void) {
    u8 hdr[8];
    BgPart20F e[64];
    BgPart20F *prev = NULL;
    u8 *first = NULL;
    u8 *out;
    u8 *data;
    u8 count;
    u8 i;
    u8 *p;
    BgPart20F *cur;
    s32 size;
    s32 extra;
    u8 t;
    u16 w;
    u16 h;

    while (D_801D06E0_ovl_1F0A30->step != 6) {
        nuGfxTaskAllEndWait();
        func_801CDDC8_ovl_1F0A30();
    }
    func_8008AFA0(NULL);
    nuGfxTaskAllEndWait();
    HFree(((BgJobFull20F *)D_801D06E0_ovl_1F0A30)->img);
    HFree(((BgJobFull20F *)D_801D06E0_ovl_1F0A30)->tiles);
    out = ((BgJobFull20F *)D_801D06E0_ovl_1F0A30)->buf;
    if (((BgJobFull20F *)D_801D06E0_ovl_1F0A30)->busy == 0) {
        void *job = D_801D06E0_ovl_1F0A30;
        D_801D06E0_ovl_1F0A30 = NULL;
        HFree(job);
        return (s32)out;
    }
    ((BgJobFull20F *)D_801D06E0_ovl_1F0A30)->parts[((BgJobFull20F *)D_801D06E0_ovl_1F0A30)->busy] = out;
    ((BgJobFull20F *)D_801D06E0_ovl_1F0A30)->busy++;
    ((BgJobFull20F *)D_801D06E0_ovl_1F0A30)->step++;
    data = ((BgJobFull20F *)D_801D06E0_ovl_1F0A30)->parts[0];
    count = data[3];
    if (count < ((BgJobFull20F *)D_801D06E0_ovl_1F0A30)->busy) {
        func_80080998(hdr, data, 8);
        p = data + 8;
        for (i = 0; i < count; i++) {
            func_80080998(&e[i], p, 0x10);
            p += ((BgPart20F *)p)->size + 0x10;
        }
        if (((BgJobFull20F *)D_801D06E0_ovl_1F0A30)->freeSrc == 1) {
            HFree(((BgJobFull20F *)D_801D06E0_ovl_1F0A30)->parts[0]);
        }
        extra = 8;
        hdr[2] = 1;
        for (i = 0; i < count; extra = 0, i++) {
            size = e[i].w * e[i].h * 2;
            extra += 0x10;
            extra += size;
            cur = HMallocBack(extra);
            if (i == 0) {
                func_80080998(cur, hdr, 8);
                first = (u8 *)cur;
                prev = cur = (BgPart20F *)(first + 8);
            } else {
                prev->next = cur;
                prev = cur;
            }
            e[i].size = size;
            func_80080998(cur, &e[i], 0x10);
            func_80080998(cur + 1, ((BgJobFull20F *)D_801D06E0_ovl_1F0A30)->parts[i + 1], size);
            HFree(((BgJobFull20F *)D_801D06E0_ovl_1F0A30)->parts[i + 1]);
        }
        prev->next = NULL;
        HFree(D_801D06E0_ovl_1F0A30);
        D_801D06E0_ovl_1F0A30 = NULL;
        return (s32)first;
    } else {
        ((BgJobFull20F *)D_801D06E0_ovl_1F0A30)->size = 8;
        count = data[3];
        p = data + 8;
        for (i = 0; i < count; i++) {
            cur = (BgPart20F *)p;
            p += 0x10;
            t = p[2];
            w = *(u16 *)(p + 4);
            h = *(u16 *)(p + 6);
            p += 8;
            ((BgJobFull20F *)D_801D06E0_ovl_1F0A30)->size += cur->w * cur->h * 2 + 0x10;
            if (((BgJobFull20F *)D_801D06E0_ovl_1F0A30)->busy == i + 1) {
                func_801CE064_ovl_1F0A30((s8)t, w, h, p, 0, 1);
                return 0;
            }
            p += cur->size - 8;
        }
        return 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/20FDC0", func_801CE38C_ovl_1F0A30);
#endif

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
