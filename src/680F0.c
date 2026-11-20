#include "common.h"
#include "nusys.h"

extern u8 *D_8019A660_ovl_066E10;

void nuGfxTaskAllEndWait(void);
s32 func_80199D10_ovl_066E10(void);

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
extern u8 D_8019A388_ovl_066E10[];
typedef struct {
    u8 unk00[0x84];
    u8 *data;
    u8 unk88[0x100];
    s32 size;
} BgJob_680F0;
void func_801999E8_ovl_066E10(s8 type, u16 w, u16 h, u8 *data, u8 a, u8 b);
void *HMalloc(s32 size);
void bzero(void *p, s32 n);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/680F0", func_80198E50_ovl_066E10);

/* Sends the JPEG decode RSP task (data at data_ptr) to the scheduler, like nuGfxTaskStart */
void func_80198FC8_ovl_066E10(void *data_ptr, u32 data_size, s32 unused, u32 flags) {
    NUScTask *t = (NUScTask *)D_8019A660_ovl_066E10;
    u32 mask;

    t->framebuffer = FIELD(t, void *, 0x64);
    t->state = 1;
    t->next = D_800E7D90;
    t->msgQ = &D_800E9BA8;
    t->msg = D_8019A388_ovl_066E10;
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
    osSendMesg(&D_800E8B4C, D_8019A660_ovl_066E10, 1);
}

INCLUDE_ASM("asm/nonmatchings/680F0", func_80199110_ovl_066E10);

void func_8019951C_ovl_066E10(void) {
    if (D_8019A660_ovl_066E10[0x7E] == 1) {
        D_8019A660_ovl_066E10[0x7E]++;
    }
    if (D_8019A660_ovl_066E10[0x7E] == 4) {
        D_8019A660_ovl_066E10[0x7E]++;
    }
}

typedef struct {
    u32 w0;
    u32 w1;
} Gfx680;

void func_80199110_ovl_066E10(Gfx680 **gp);

#ifdef NON_MATCHING
/* 121/121 instructions, 30 words differ: scheduling of the task-field stores (same function in 1ED1D0 and 20FDC0) */
void func_80199568_ovl_066E10(u8 last) {
    NUScTask *t;
    Gfx680 *gp;
    Gfx680 *start;
    u32 mask;

    if (!last) {
        gp = FIELD(D_8019A660_ovl_066E10, Gfx680 *, 0x5C);
        func_80199110_ovl_066E10(&gp);
        {
            Gfx680 *_g = gp++;
            _g->w0 = 0xE9000000;
            _g->w1 = 0;
        }
        {
            Gfx680 *_g = gp++;
            _g->w0 = 0xDF000000;
            _g->w1 = 0;
        }
        D_8019A660_ovl_066E10[0x7E]++;
        FIELD(D_8019A660_ovl_066E10, Gfx680 *, 0x58) = gp;
        return;
    }
    D_8019A660_ovl_066E10[0x7E]++;
    t = (NUScTask *)D_8019A660_ovl_066E10;
    start = FIELD(t, Gfx680 *, 0x5C);
    t->framebuffer = FIELD(t, void *, 0x64);
    t->state = 1;
    t->next = D_800E7D90;
    t->msgQ = &D_800E9BA8;
    t->msg = D_8019A388_ovl_066E10;
    t->flags = 0;
    t->list.t.type = 1;
    t->list.t.ucode_boot = D_8009ECB0;
    t->list.t.ucode_boot_size = (s32)D_8009ED80 - (s32)D_8009ECB0;
    t->list.t.ucode = D_800A5110;
    t->list.t.ucode_size = (s32)D_800A69D0 - (s32)D_800A5110;
    t->list.t.ucode_data = D_800AD590;
    t->list.t.ucode_data_size = (s32)D_800AD920 - (s32)D_800AD590;
    t->list.t.flags = 0;
    t->list.t.dram_stack = D_800E8710;
    t->list.t.dram_stack_size = 0x400;
    t->list.t.output_buff = D_800C7970;
    t->list.t.output_buff_size = (u64 *)(D_800A9E70 + (u32)D_800C7970);
    t->list.t.data_ptr = (u64 *)start;
    t->list.t.data_size = (FIELD(t, Gfx680 *, 0x58) - start) * sizeof(Gfx680);
    t->list.t.yield_data_ptr = D_800C6D70;
    t->list.t.yield_data_size = 0xC00;
    mask = osSetIntMask(1);
    D_800E79A4++;
    osSetIntMask(mask);
    osWritebackDCacheAll();
    osSendMesg(&D_800E8B4C, D_8019A660_ovl_066E10, 1);
}
#else
INCLUDE_ASM("asm/nonmatchings/680F0", func_80199568_ovl_066E10);
#endif

INCLUDE_ASM("asm/nonmatchings/680F0", func_8019974C_ovl_066E10);

/* Reports which frame buffer pair is current (o[0], o[1]) */
void func_8019994C_ovl_066E10(u8 *o) {
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

INCLUDE_ASM("asm/nonmatchings/680F0", func_801999E8_ovl_066E10);

INCLUDE_ASM("asm/nonmatchings/680F0", func_80199D10_ovl_066E10);

/* Background image: "HU" data is decoded straight away; anything else is a JPEG job
 * (state block at D_801BA6D0) and returns 1 */
s32 func_8019A088_ovl_066E10(u8 *data, u8 a, u8 b) {
    u8 *p = data;
    s8 type = p[2];
    u16 w = *(u16 *)(p + 4);
    u16 h = *(u16 *)(p + 6);
    u8 *q;
    u8 *r;

    nuGfxTaskAllEndWait();
    p += 8;
    if (*(u16 *)data == 0x4855) {
        func_801999E8_ovl_066E10(type, w, h, p, a, b);
        return 0;
    } else {
        D_8019A660_ovl_066E10 = HMalloc(0x190);
        bzero(D_8019A660_ovl_066E10, 0x190);
        ((u8 *)D_8019A660_ovl_066E10)[0x7E] = 0;
        ((BgJob_680F0 *)D_8019A660_ovl_066E10)->data = data;
        ((u8 *)D_8019A660_ovl_066E10)[0x81] = 1;
        ((BgJob_680F0 *)D_8019A660_ovl_066E10)->size = 0;
        ((u8 *)D_8019A660_ovl_066E10)[0x82] = a;
        ((BgJob_680F0 *)D_8019A660_ovl_066E10)->size = 8;
        r = p;
        p += 0x10;
        ((BgJob_680F0 *)D_8019A660_ovl_066E10)->size = *(u16 *)(r + 4) * *(u16 *)(r + 6) * 2 + 0x18;
        q = p;
        p += 8;
        func_801999E8_ovl_066E10(q[2], *(u16 *)(q + 4), *(u16 *)(q + 6), p, 0, 1);
        return 1;
    }
}

void func_8019A1DC_ovl_066E10(void) {
    do {
        nuGfxTaskAllEndWait();
    } while (!func_80199D10_ovl_066E10());
}
