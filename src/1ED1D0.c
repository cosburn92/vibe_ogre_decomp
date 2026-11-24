#include "common.h"
#include "heap.h"
#include "nusys.h"

/* 1ED1D0 */

void nuGfxTaskAllEndWait(void);
s32 func_801B7B7C_ovl_1CE070(void);
extern u8 D_800E7A0C;
extern void *D_800C4BB8;
extern void *D_800A8204[3];
extern u8 D_800E7A0C;
extern void *D_800C4BB8;
extern void *D_800A8204[3];
typedef struct {
    u8 unk00[0x7E];
    u8 step;
} Seq1ED;
extern Seq1ED *D_801BA6D0_ovl_1CE070;
typedef struct {
    /* 0x000 */ u8 unk00[0x84];
    /* 0x084 */ u8 *data;
    /* 0x088 */ u8 unk88[0x100];
    /* 0x188 */ s32 size;
} BgJob;
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
extern u8 D_801B9998_ovl_1CE070[];
s32 BgDecodeHu(s32 type, u16 w, u16 h, u8 *data, u8 a, u8 b);
void bzero(void *p, s32 n);
extern u64 D_8009F540[];
extern u64 jpegTextStart[];
extern u64 D_800AC050[];
extern u64 D_800AC140[];
/* --- end decls --- */

/* Sends the JPEG decode RSP task for a w x h image (in 16x16 blocks) */
void BgJpegTask(s8 mode, void *data_ptr, s16 w, s16 h) {
    s32 bw = w / 16;
    s32 bh = h / 16;
    NUScTask *t = (NUScTask *)D_801BA6D0_ovl_1CE070;
    u32 mask;

    t->framebuffer = FIELD(t, void *, 0x64);
    t->state = 1;
    t->next = D_800E7D90;
    t->msgQ = &D_800E9BA8;
    t->msg = D_801B9998_ovl_1CE070;
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
    ((u8 *)D_801BA6D0_ovl_1CE070)[0x7E]++;
    osSendMesg(&D_800E8B4C, D_801BA6D0_ovl_1CE070, 1);
}

/* Sends the JPEG decode RSP task (data at data_ptr) to the scheduler, like nuGfxTaskStart */
void func_801B6E48_ovl_1CE070(void *data_ptr, u32 data_size, s32 unused, u32 flags) {
    NUScTask *t = (NUScTask *)D_801BA6D0_ovl_1CE070;
    u32 mask;

    t->framebuffer = FIELD(t, void *, 0x64);
    t->state = 1;
    t->next = D_800E7D90;
    t->msgQ = &D_800E9BA8;
    t->msg = D_801B9998_ovl_1CE070;
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
    osSendMesg(&D_800E8B4C, D_801BA6D0_ovl_1CE070, 1);
}

typedef struct {
    u32 w0;
    u32 w1;
} Gfx1ED;
extern u8 D_801B9980_ovl_1CE070[];
void func_801B6F90_ovl_1CE070(Gfx1ED **gp);

/* Background JPEG display list (same code as 20FDC0 func_801CD7A0): YUV colour conversion
 * setup for the frame buffer, then one 16x16 YUV tile load and decode command per block */
void func_801B6F90_ovl_1CE070(Gfx1ED **gp) {
    Gfx1ED *g = *gp;
    u8 *img;
    u8 i;
    u8 j;

    {
        Gfx1ED *_g = g++;
        _g->w0 = 0xDB060000;
        _g->w1 = 0;
    }
    {
        Gfx1ED *_g = g++;
        _g->w0 = 0xE7000000;
        _g->w1 = 0;
    }
    {
        Gfx1ED *_g = g++;
        _g->w0 = 0xE3000A01;
        _g->w1 = 0;
    }
    {
        Gfx1ED *_g = g++;
        _g->w0 = 0xE3000800;
        _g->w1 = 0;
    }
    {
        Gfx1ED *_g = g++;
        _g->w0 = 0xFF10013F;
        _g->w1 = FIELD(D_801BA6D0_ovl_1CE070, u32, 0x64);
    }
    {
        Gfx1ED *_g = g++;
        _g->w0 = 0xED000000;
        _g->w1 = 0x005003C0;
    }
    {
        Gfx1ED *_g = g++;
        _g->w0 = 0xE3000C00;
        _g->w1 = 0;
    }
    {
        Gfx1ED *_g = g++;
        _g->w0 = 0xE3000F00;
        _g->w1 = 0;
    }
    {
        Gfx1ED *_g = g++;
        _g->w0 = 0xE3001001;
        _g->w1 = 0;
    }
    {
        Gfx1ED *_g = g++;
        _g->w0 = 0xE3000D01;
        _g->w1 = 0;
    }
    {
        Gfx1ED *_g = g++;
        _g->w0 = 0xE3001402;
        _g->w1 = 0;
    }
    {
        Gfx1ED *_g = g++;
        _g->w0 = 0xEC15FD5D;
        _g->w1 = 0x3B78E42A;
    }
    {
        Gfx1ED *_g = g++;
        _g->w0 = 0xE3001201;
        _g->w1 = 0;
    }
    {
        Gfx1ED *_g = g++;
        _g->w0 = 0xFC17FE2F;
        _g->w1 = 0x77FCF87C;
    }
    {
        Gfx1ED *_g = g++;
        _g->w0 = 0xE3001700;
        _g->w1 = 0;
    }
    {
        Gfx1ED *_g = g++;
        _g->w0 = 0xE200001C;
        _g->w1 = 0x0F0A4000;
    }
    {
        Gfx1ED *_g = g++;
        _g->w0 = 0xE2001E01;
        _g->w1 = 0;
    }
    {
        Gfx1ED *_g = g++;
        _g->w0 = 0xE3001801;
        _g->w1 = 0xC0;
    }
    img = FIELD(D_801BA6D0_ovl_1CE070, u8 *, 0x68);
    for (i = 0; i < FIELD(D_801BA6D0_ovl_1CE070, s16, 0x7A) / 16; i++) {
        for (j = 0; j < FIELD(D_801BA6D0_ovl_1CE070, s16, 0x78) / 16; j++) {
            {
                Gfx1ED *_g = g++;
                _g->w0 = 0xFD30000F;
                _g->w1 = (u32)img;
            }
            {
                Gfx1ED *_g = g++;
                _g->w0 = 0xF5300400;
                _g->w1 = 0x07080200;
            }
            {
                Gfx1ED *_g = g++;
                _g->w0 = 0xE6000000;
                _g->w1 = 0;
            }
            {
                Gfx1ED *_g = g++;
                _g->w0 = 0xF4000000;
                _g->w1 = 0x0703C03C;
            }
            {
                Gfx1ED *_g = g++;
                _g->w0 = 0xDC070002;
                _g->w1 = (u32)&FIELD(D_801BA6D0_ovl_1CE070, Gfx1ED *, 0x60)[i * (FIELD(D_801BA6D0_ovl_1CE070, s16, 0x78) / 16) + j];
            }
            {
                Gfx1ED *_g = g++;
                _g->w0 = 0xDA000000;
                _g->w1 = (u32)D_801B9980_ovl_1CE070;
            }
            img += 0x300;
        }
    }
    *gp = g;
}

void func_801B7388_ovl_1CE070(void) {
    if (D_801BA6D0_ovl_1CE070->step == 1) {
        D_801BA6D0_ovl_1CE070->step++;
    }
    if (D_801BA6D0_ovl_1CE070->step == 4) {
        D_801BA6D0_ovl_1CE070->step++;
    }
}

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif

/* Closes the display list (last == 0: full sync + end, records its end) or sends it to the
 * scheduler as a graphics task, like nuGfxTaskStart */
void func_801B73D4_ovl_1CE070(u8 last) {
    NUScTask *t;
    Gfx1ED *gp;
    Gfx1ED *start;
    Gfx1ED *end;
    u32 mask;

    if (!last) {
        gp = FIELD(D_801BA6D0_ovl_1CE070, Gfx1ED *, 0x5C);
        func_801B6F90_ovl_1CE070(&gp);
        {
            Gfx1ED *_g = gp++;
            _g->w0 = 0xE9000000;
            _g->w1 = 0;
        }
        {
            Gfx1ED *_g = gp++;
            _g->w0 = 0xDF000000;
            _g->w1 = 0;
        }
        ((u8 *)D_801BA6D0_ovl_1CE070)[0x7E]++;
        FIELD(D_801BA6D0_ovl_1CE070, Gfx1ED *, 0x58) = gp;
        return;
    }
    ((u8 *)D_801BA6D0_ovl_1CE070)[0x7E]++;
    t = (NUScTask *)D_801BA6D0_ovl_1CE070;
    end = FIELD(t, Gfx1ED *, 0x58);
    start = FIELD(t, Gfx1ED *, 0x5C);
    t->framebuffer = FIELD(t, void *, 0x64);
    t->state = 1;
    t->next = D_800E7D90;
    t->msgQ = &D_800E9BA8;
    t->msg = D_801B9998_ovl_1CE070;
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
    t->list.t.data_size = (end - start) * sizeof(Gfx1ED);
    t->list.t.yield_data_ptr = D_800C6D70;
    t->list.t.yield_data_size = 0xC00;
    mask = osSetIntMask(1);
    D_800E79A4++;
    osSetIntMask(mask);
    osWritebackDCacheAll();
    osSendMesg(&D_800E8B4C, D_801BA6D0_ovl_1CE070, 1);
}

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void func_80080998(void *dst, void *src, s32 n);

/* Steps the background JPEG job: 0 starts the decode task and closes its display list once the
 * decoder reaches step 2; 3 sends it and, at step 5, copies the decoded rows into the image (a
 * "64" bitmap header unless raw) */
void func_801B75B8_ovl_1CE070(void) {
    u8 *src;
    s32 row;
    s16 y;

    nuGfxTaskAllEndWait();
    if (((u8 *)D_801BA6D0_ovl_1CE070)[0x7E] == 0) {
        if (((u8 *)D_801BA6D0_ovl_1CE070)[0x80] == 0) {
            FIELD(D_801BA6D0_ovl_1CE070, u8 *, 0x70) = FIELD(D_801BA6D0_ovl_1CE070, u8 *, 0x74) + 8;
        } else {
            FIELD(D_801BA6D0_ovl_1CE070, u8 *, 0x70) = FIELD(D_801BA6D0_ovl_1CE070, u8 *, 0x74);
        }
        BgJpegTask(FIELD(D_801BA6D0_ovl_1CE070, s8, 0x7D), FIELD(D_801BA6D0_ovl_1CE070, void *, 0x68),
                                 FIELD(D_801BA6D0_ovl_1CE070, s16, 0x78), FIELD(D_801BA6D0_ovl_1CE070, s16, 0x7A));
        while (((u8 *)D_801BA6D0_ovl_1CE070)[0x7E] != 2) {
            nuGfxTaskAllEndWait();
        }
        nuGfxTaskAllEndWait();
        func_801B73D4_ovl_1CE070(0);
    } else if (((u8 *)D_801BA6D0_ovl_1CE070)[0x7E] == 3) {
        func_801B73D4_ovl_1CE070(1);
        while (((u8 *)D_801BA6D0_ovl_1CE070)[0x7E] != 5) {
            nuGfxTaskAllEndWait();
        }
        src = FIELD(D_801BA6D0_ovl_1CE070, u8 *, 0x64);
        row = FIELD(D_801BA6D0_ovl_1CE070, s16, 0x78) * 2;
        for (y = 0; y < FIELD(D_801BA6D0_ovl_1CE070, s16, 0x7A); y++) {
            func_80080998(FIELD(D_801BA6D0_ovl_1CE070, u8 *, 0x70), src,
                          FIELD(D_801BA6D0_ovl_1CE070, s16, 0x78) * 2);
            FIELD(D_801BA6D0_ovl_1CE070, u8 *, 0x70) += row;
            src += 0x280;
        }
        if (((u8 *)D_801BA6D0_ovl_1CE070)[0x80] == 0) {
            FIELD(D_801BA6D0_ovl_1CE070, u8 *, 0x74)[0] = '6';
            FIELD(D_801BA6D0_ovl_1CE070, u8 *, 0x74)[1] = '4';
            FIELD(D_801BA6D0_ovl_1CE070, u8 *, 0x74)[2] = 0;
            FIELD(D_801BA6D0_ovl_1CE070, u8 *, 0x74)[3] = 2;
            FIELD(FIELD(D_801BA6D0_ovl_1CE070, u8 *, 0x74), u16, 4) = FIELD(D_801BA6D0_ovl_1CE070, s16, 0x78);
            FIELD(FIELD(D_801BA6D0_ovl_1CE070, u8 *, 0x74), u16, 6) = FIELD(D_801BA6D0_ovl_1CE070, s16, 0x7A);
        }
        ((u8 *)D_801BA6D0_ovl_1CE070)[0x7E]++;
    }
}

/* Reports which frame buffer pair is current (o[0], o[1]) */
/* Reports which frame buffer pair is current (o[0], o[1]) */
inline void func_801B77B8_ovl_1CE070(u8 *o) {
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
} BgTile1ED;
typedef struct {
    u8 unk00[0x68];
    void *img;
    u8 unk6C[0xC];
    s16 w;
    s16 h;
} BgState1ED;
void HuDecode(void *src, void *dst);
void func_8008AFA0(void (*func)(void *));

/* Sets up a background image job (same code as 20FDC0 func_801CE064): w x h pixels in 16x16
 * tiles, decodes the "HU" data (freeing it if a == 1) and hooks func_801B7388 as the per-frame
 * step. Returns -1 if a JPEG job is still busy */
s32 BgDecodeHu(s32 type, u16 w, u16 h, u8 *data, u8 a, u8 b) {
    u8 o[2];
    s16 n;
    s16 k;
    s16 i;
    s16 j;

    if (D_801BA6D0_ovl_1CE070 == NULL) {
        D_801BA6D0_ovl_1CE070 = HMalloc(0x190);
        bzero(D_801BA6D0_ovl_1CE070, 0x190);
        ((u8 *)D_801BA6D0_ovl_1CE070)[0x81] = 0;
    } else if (((u8 *)D_801BA6D0_ovl_1CE070)[0x81] == 0) {
        return -1;
    }
    n = (w >> 4) * (h >> 4);
    if (b == 0) {
        FIELD(D_801BA6D0_ovl_1CE070, void *, 0x74) = HMallocBack(w * h * 2 + 8);
    } else {
        FIELD(D_801BA6D0_ovl_1CE070, void *, 0x74) = HMalloc(w * h * 2);
    }
    func_801B77B8_ovl_1CE070(o);
    FIELD(D_801BA6D0_ovl_1CE070, void *, 0x64) = D_800A8204[o[0]];
    FIELD(D_801BA6D0_ovl_1CE070, BgTile1ED *, 0x60) = HMalloc(n * 8);
    FIELD(D_801BA6D0_ovl_1CE070, void *, 0x5C) = D_800A8204[o[1]];
    ((u8 *)D_801BA6D0_ovl_1CE070)[0x80] = b;
    ((BgState1ED *)D_801BA6D0_ovl_1CE070)->img = HMalloc(n * 0x300);
    ((BgState1ED *)D_801BA6D0_ovl_1CE070)->w = w;
    ((BgState1ED *)D_801BA6D0_ovl_1CE070)->h = h;
    D_801BA6D0_ovl_1CE070->step = 0;
    FIELD(D_801BA6D0_ovl_1CE070, s16, 0x7C) = type;
    FIELD(D_801BA6D0_ovl_1CE070, u8 *, 0x6C) = data;
    ((u8 *)D_801BA6D0_ovl_1CE070)[0x7F] = a;
    k = 0;
    for (i = 0; i < (h >> 4); i++) {
        for (j = 0; j < (w >> 4); j++) {
            FIELD(D_801BA6D0_ovl_1CE070, BgTile1ED *, 0x60)[k].x = j * 64;
            FIELD(D_801BA6D0_ovl_1CE070, BgTile1ED *, 0x60)[k].y = i * 64;
            FIELD(D_801BA6D0_ovl_1CE070, BgTile1ED *, 0x60)[k].w = 0x400;
            FIELD(D_801BA6D0_ovl_1CE070, BgTile1ED *, 0x60)[k].h = 0x400;
            k++;
        }
    }
    HuDecode(FIELD(D_801BA6D0_ovl_1CE070, u8 *, 0x6C), FIELD(D_801BA6D0_ovl_1CE070, void *, 0x68));
    if (((u8 *)D_801BA6D0_ovl_1CE070)[0x7F] == 1) {
        HFree(FIELD(D_801BA6D0_ovl_1CE070, u8 *, 0x6C) - 8);
    }
    func_8008AFA0((void (*)(void *))func_801B7388_ovl_1CE070);
    return 0;
}

/* Image header at the start of a background file and of each part's data */
typedef struct {
    /* 0x0 */ u8 unk0[2];
    /* 0x2 */ u8 type;
    /* 0x3 */ u8 count; /* parts that follow (file header only) */
    /* 0x4 */ u16 w;
    /* 0x6 */ u16 h;
} BgHdr1ED;
/* Part header: followed by size bytes (an image header and its data) */
typedef struct BgPart1ED {
    /* 0x0 */ u8 unk0[2];
    /* 0x2 */ u8 type;
    /* 0x3 */ u8 unk3;
    /* 0x4 */ u16 w;
    /* 0x6 */ u16 h;
    /* 0x8 */ s32 size;
    /* 0xC */ struct BgPart1ED *next;
} BgPart1ED;
/* The JPEG job state at D_801BA6D0 as this function sees it */
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
} BgSeq1ED;
#define BGSEQ ((BgSeq1ED *)D_801BA6D0_ovl_1CE070)

/* Finishes the current JPEG part. While parts remain, it starts the decode of the next one and
 * returns 0. After the last part it packs the file header and every decoded part (part header +
 * pixels, linked through next) into fresh blocks, frees the job and returns the first block;
 * a single-image job returns its output buffer directly. */
s32 func_801B7B7C_ovl_1CE070(void) {
    BgHdr1ED hdr;
    BgPart1ED parts[64];
    BgSeq1ED *s;
    BgHdr1ED *file;
    u8 count;
    u8 i;
    s32 bytes;
    s32 sz;
    BgPart1ED *blk;
    BgPart1ED *last;
    u8 *ret;

    last = NULL;
    ret = NULL;
    while (D_801BA6D0_ovl_1CE070->step != 6) {
        nuGfxTaskAllEndWait();
        func_801B75B8_ovl_1CE070();
    }
    func_8008AFA0(NULL);
    nuGfxTaskAllEndWait();
    HFree(BGSEQ->img);
    HFree(BGSEQ->tiles);
    file = (BgHdr1ED *)BGSEQ->out;
    if (BGSEQ->n == 0) {
        s = BGSEQ;
        D_801BA6D0_ovl_1CE070 = NULL;
        HFree(s);
        return (s32)file;
    }
    /* data[n] = file, spelled as an int sum: the indexed form adds index + base, the original base + index */
    *(u8 **)((s32)BGSEQ + (BGSEQ->n << 2) + 0x84) = (u8 *)file;
    ((u8 *)D_801BA6D0_ovl_1CE070)[0x81]++;
    ((u8 *)D_801BA6D0_ovl_1CE070)[0x7E]++;
    file = (BgHdr1ED *)BGSEQ->data[0];
    count = file->count;
    if (count < BGSEQ->n) {
        u8 *q;

        func_80080998(&hdr, file, 8);
        q = (u8 *)(file + 1);
        for (i = 0; i < count; i++) {
            last = (BgPart1ED *)q;
            func_80080998(&parts[i], q, 16);
            q = (u8 *)last + (last->size + 16);
        }
        if (BGSEQ->own == 1) {
            HFree(BGSEQ->data[0]);
        }
        sz = 8;
        hdr.type = 1;
        for (i = 0; i < count; i++) {
            bytes = parts[i].w * parts[i].h * 2;
            blk = HMallocBack((sz += 0x10) + bytes);
            if (i == 0) {
                func_80080998(blk, &hdr, 8);
                ret = (u8 *)blk;
                blk = (BgPart1ED *)(ret + 8);
                last = blk;
            } else {
                last->next = blk;
                last = blk;
            }
            parts[i].size = bytes;
            func_80080998(blk, &parts[i], 16);
            func_80080998(blk + 1, *(u8 **)((i * 4) + (s32)BGSEQ + 0x88), bytes);
            HFree(*(u8 **)((i * 4) + (s32)BGSEQ + 0x88));
            sz = 0;
        }
        last->next = NULL;
        HFree(D_801BA6D0_ovl_1CE070);
        D_801BA6D0_ovl_1CE070 = NULL;
        return (s32)ret;
    }
    BGSEQ->size = 8;
    ret = (u8 *)(file + 1);
    count = file->count;
    for (i = 0; i < count; i++) {
        s32 type;
        s32 w;
        s32 h;

        last = (BgPart1ED *)ret;
        ret += 0x10;
        type = ((BgHdr1ED *)ret)->type;
        w = ((BgHdr1ED *)ret)->w;
        h = ((BgHdr1ED *)ret)->h;
        BGSEQ->size += last->w * last->h * 2 + 0x10;
        ret += 8;
        if (BGSEQ->n == i + 1) {
            BgDecodeHu((s8)type, w, h, ret, 0, 1);
            return 0;
        }
        ret += last->size - 8;
    }
    return 0;
}

/* Background image: "HU" data is decoded straight away; anything else is a JPEG job
 * (state block at D_801BA6D0) and returns 1 */
s32 BgLoad(u8 *data, u8 a, u8 b) {
    u8 *p = data;
    s8 type = p[2];
    u16 w = *(u16 *)(p + 4);
    u16 h = *(u16 *)(p + 6);
    u8 *q;
    u8 *r;

    nuGfxTaskAllEndWait();
    p += 8;
    if (*(u16 *)data == 0x4855) {
        BgDecodeHu(type, w, h, p, a, b);
        return 0;
    } else {
        D_801BA6D0_ovl_1CE070 = HMalloc(0x190);
        bzero(D_801BA6D0_ovl_1CE070, 0x190);
        ((u8 *)D_801BA6D0_ovl_1CE070)[0x7E] = 0;
        ((BgJob *)D_801BA6D0_ovl_1CE070)->data = data;
        ((u8 *)D_801BA6D0_ovl_1CE070)[0x81] = 1;
        ((BgJob *)D_801BA6D0_ovl_1CE070)->size = 0;
        ((u8 *)D_801BA6D0_ovl_1CE070)[0x82] = a;
        ((BgJob *)D_801BA6D0_ovl_1CE070)->size = 8;
        r = p;
        p += 0x10;
        ((BgJob *)D_801BA6D0_ovl_1CE070)->size = *(u16 *)(r + 4) * *(u16 *)(r + 6) * 2 + 0x18;
        q = p;
        p += 8;
        BgDecodeHu((s8)q[2], *(u16 *)(q + 4), *(u16 *)(q + 6), p, 0, 1);
        return 1;
    }
}

void func_801B8048_ovl_1CE070(void) {
    do {
        nuGfxTaskAllEndWait();
    } while (!func_801B7B7C_ovl_1CE070());
}
