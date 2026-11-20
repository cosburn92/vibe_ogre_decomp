#include "common.h"
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
void BgDecodeHu(s8 type, u16 w, u16 h, u8 *data, u8 a, u8 b);
void *HMalloc(s32 size);
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

INCLUDE_ASM("asm/nonmatchings/1ED1D0", func_801B6F90_ovl_1CE070);

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
typedef struct {
    u32 w0;
    u32 w1;
} Gfx1ED;

void func_801B6F90_ovl_1CE070(Gfx1ED **gp);

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
void func_801B77B8_ovl_1CE070(u8 *o) {
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

INCLUDE_ASM("asm/nonmatchings/1ED1D0", BgDecodeHu);

INCLUDE_ASM("asm/nonmatchings/1ED1D0", func_801B7B7C_ovl_1CE070);

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
        BgDecodeHu(q[2], *(u16 *)(q + 4), *(u16 *)(q + 6), p, 0, 1);
        return 1;
    }
}

void func_801B8048_ovl_1CE070(void) {
    do {
        nuGfxTaskAllEndWait();
    } while (!func_801B7B7C_ovl_1CE070());
}
