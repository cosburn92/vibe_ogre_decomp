#include "common.h"
#include "libultra.h"

/* libultra sptask.c */

typedef struct {
    /* 0x00 */ u32 type;
    /* 0x04 */ u32 flags;
    /* 0x08 */ u64 *ucode_boot;
    /* 0x0C */ u32 ucode_boot_size;
    /* 0x10 */ u64 *ucode;
    /* 0x14 */ u32 ucode_size;
    /* 0x18 */ u64 *ucode_data;
    /* 0x1C */ u32 ucode_data_size;
    /* 0x20 */ u64 *dram_stack;
    /* 0x24 */ u32 dram_stack_size;
    /* 0x28 */ u64 *output_buff;
    /* 0x2C */ u64 *output_buff_size;
    /* 0x30 */ u64 *data_ptr;
    /* 0x34 */ u32 data_size;
    /* 0x38 */ u64 *yield_data_ptr;
    /* 0x3C */ u32 yield_data_size;
} OSTask_t;

typedef union {
    OSTask_t t;
    s64 force_structure_alignment;
} OSTask;

#define OS_TASK_YIELDED 0x0001
#define OS_TASK_LOADABLE 0x0004
#define OS_YIELD_DATA_SIZE 0xC00
#define SP_IMEM_START 0x04001000
#define SP_CLR_HALT 0x00001
#define SP_CLR_BROKE 0x00004
#define SP_CLR_SSTEP 0x00020
#define SP_SET_INTR_BREAK 0x00100
#define SP_CLR_YIELD 0x00200
#define SP_CLR_YIELDED 0x00800
#define SP_CLR_TASKDONE 0x02000

#define _osVirtualToPhysical(ptr)                     \
    if (ptr != NULL) {                                \
        ptr = (void *)osVirtualToPhysical(ptr);       \
    }

extern OSTask D_800C3560; /* tmp_task */

void _bcopy(const void *src, void *dst, s32 len);
void osWritebackDCache(void *vaddr, s32 nbytes);
void __osSpSetStatus(u32 data);
s32 __osSpSetPc(u32 pc);
s32 __osSpRawStartDma(s32 direction, u32 devAddr, void *dramAddr, u32 size);
s32 __osSpDeviceBusy_8009A740(void);

static inline OSTask *_VirtualToPhysicalTask(OSTask *intp) {
    OSTask *tp;

    tp = &D_800C3560;
    _bcopy(intp, tp, sizeof(OSTask));
    _osVirtualToPhysical(tp->t.ucode);
    _osVirtualToPhysical(tp->t.ucode_data);
    _osVirtualToPhysical(tp->t.dram_stack);
    _osVirtualToPhysical(tp->t.output_buff);
    _osVirtualToPhysical(tp->t.output_buff_size);
    _osVirtualToPhysical(tp->t.data_ptr);
    _osVirtualToPhysical(tp->t.yield_data_ptr);
    return tp;
}

void osSpTaskLoad(OSTask *intp) {
    OSTask *tp;

    tp = _VirtualToPhysicalTask(intp);
    if (tp->t.flags & OS_TASK_YIELDED) {
        tp->t.ucode_data = tp->t.yield_data_ptr;
        tp->t.ucode_data_size = tp->t.yield_data_size;
        intp->t.flags &= ~OS_TASK_YIELDED;
        if (tp->t.flags & OS_TASK_LOADABLE) {
            tp->t.ucode = (u64 *)IO_READ((u32)intp->t.yield_data_ptr + OS_YIELD_DATA_SIZE - 4);
        }
    }
    osWritebackDCache(tp, sizeof(OSTask));
    __osSpSetStatus(SP_CLR_YIELD | SP_CLR_YIELDED | SP_CLR_TASKDONE | SP_SET_INTR_BREAK);
    while (__osSpSetPc(SP_IMEM_START) == -1) {
    }
    while (__osSpRawStartDma(1, (SP_IMEM_START - sizeof(*tp)), tp, sizeof(OSTask)) == -1) {
    }
    while (__osSpDeviceBusy_8009A740()) {
    }
    while (__osSpRawStartDma(1, SP_IMEM_START, tp->t.ucode_boot, tp->t.ucode_boot_size) == -1) {
    }
}

void osSpTaskStartGo(OSTask *tp) {
    while (__osSpDeviceBusy_8009A740()) {
    }
    __osSpSetStatus(SP_SET_INTR_BREAK | SP_CLR_SSTEP | SP_CLR_BROKE | SP_CLR_HALT);
}
