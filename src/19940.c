#include "common.h"

/* NuSystem nugfxtaskmgr.c: the ring of graphics tasks and the thread that handles finished ones */

typedef void *OSMesg;

typedef struct {
    /* 0x00 */ void *mtqueue;
    /* 0x04 */ void *fullqueue;
    /* 0x08 */ s32 validCount;
    /* 0x0C */ s32 first;
    /* 0x10 */ s32 msgCount;
    /* 0x14 */ OSMesg *msg;
} OSMesgQueue;

typedef struct {
    u64 pad[0x1B0 / 8];
} OSThread;

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
} OSTask;

typedef s16 NUScMsg;

typedef struct NUScTask_s {
    /* 0x00 */ struct NUScTask_s *next;
    /* 0x04 */ u32 state;
    /* 0x08 */ u32 flags;
    /* 0x0C */ void *framebuffer;
    /* 0x10 */ OSTask list;
    /* 0x50 */ OSMesgQueue *msgQ;
    /* 0x54 */ OSMesg msg;
} NUScTask; /* size 0x58 */

typedef struct {
    /* 0x00 */ u64 *ucode;
    /* 0x04 */ u64 *ucode_data;
} NUUcode;

#define NU_GFX_TASK_NUM 10
#define NU_SC_SWAPBUFFER_MSG 4
#define NU_SC_GTASKEND_MSG 8
#define NU_SC_SWAPBUFFER 1

extern NUScTask D_800E7D90[NU_GFX_TASK_NUM]; /* nuGfxTask */
extern volatile u32 D_800E79A4;              /* nuGfxTaskSpool */
extern NUScTask *D_800B9C80;                 /* nuGfxTask_ptr */
extern NUScMsg D_800B9C84;                   /* taskDoneMsg */
extern NUScMsg D_800B9C86;                   /* swapBufMsg */
extern OSThread D_800B9C88;                  /* GfxTaskMgrThread */
extern OSMesg D_800BBE40[];                  /* nuGfxTaskMgrMesgBuf (and the end of the thread's stack) */
extern OSMesgQueue D_800E9BA8;               /* nuGfxTaskMgrMesgQ */
extern void (*D_800A9E84)(NUScTask *);       /* nuGfxSwapCfbFunc */
extern void (*D_800A9E88)(NUScTask *);       /* nuGfxTaskEndFunc */
extern void (*D_800A9E8C)(NUScTask *);
extern u32 D_800C4BD8;                       /* nuGfxDisplay */
extern u64 D_8009ECB0[];                     /* rspbootTextStart */
extern u64 D_8009ED80[];                     /* rspbootTextEnd */
extern u64 D_800E8710[];                     /* nuDramStack */
extern u64 D_800C7970[];                     /* nuRDPOutputBuf */
extern u64 D_800C6D70[];                     /* nuYieldBuf */
extern NUUcode *D_800C4CE0;                  /* nuGfxUcode */
extern void *D_800E8210;                     /* nuGfxCfb_ptr */
extern void **D_800E8290;                    /* nuGfxCfb */
extern u32 D_800C4BC4;                       /* nuGfxCfbCounter */
extern u32 D_800A9E80;                       /* nuGfxCfbNum */
extern u32 D_800A9E70;                       /* nuRDPOutputBufSize */
extern u16 D_800A9E90;                       /* flags of the previous task */
extern OSMesgQueue D_800E8B4C;               /* nusched.graphicsRequestMQ */

void osCreateMesgQueue(OSMesgQueue *mq, OSMesg *msg, s32 count);
s32 osRecvMesg(OSMesgQueue *mq, OSMesg *msg, s32 flag);
s32 osSendMesg(OSMesgQueue *mq, OSMesg msg, s32 flag);
void osCreateThread(void *t, s32 id, void (*entry)(void *), void *arg, void *sp, s32 pri);
void osStartThread(void *t);
u32 osSetIntMask(u32 mask);
void osWritebackDCacheAll(void);
void func_80089BC0(void);      /* nuGfxDisplayOff */
void func_80089BE4(u8 active); /* osViBlack wrapper */

/* nuGfxTaskMgr */
void func_80089540(void *arg) {
    NUScTask *gfxTask;
    s16 *msgtype;
    u32 mask;

    osCreateMesgQueue(&D_800E9BA8, D_800BBE40, 8);

loop:
    {
        osRecvMesg(&D_800E9BA8, (OSMesg *)&gfxTask, 1);
        msgtype = (s16 *)gfxTask->msg;
        switch (*msgtype) {
            case NU_SC_SWAPBUFFER_MSG:
                if (D_800A9E84 != NULL) {
                    D_800A9E84(gfxTask);
                }
                if (D_800C4BD8 & 0x80) { /* NU_GFX_DISPLAY_ON_TRIGGER */
                    func_80089BE4(0);
                    D_800C4BD8 = 1; /* NU_GFX_DISPLAY_ON */
                }
                break;
            case NU_SC_GTASKEND_MSG:
                if (D_800A9E88 != NULL) {
                    D_800A9E88(gfxTask);
                }
                break;
            case 0x10:
                if (D_800A9E8C != NULL) {
                    D_800A9E8C(gfxTask);
                }
                break;
            default:
                goto loop;
        }
        mask = osSetIntMask(1);
        D_800E79A4--;
        osSetIntMask(mask);
    }
    goto loop;
}

/* nuGfxTaskMgrInit */
void func_80089660(void) {
    u32 cnt;

    D_800B9C84 = NU_SC_GTASKEND_MSG;
    D_800B9C86 = NU_SC_SWAPBUFFER_MSG;
    D_800E79A4 = 0;
    func_80089BC0();

    osCreateThread(&D_800B9C88, 5, func_80089540, NULL, D_800BBE40, 60);
    osStartThread(&D_800B9C88);

    for (cnt = 0; cnt < NU_GFX_TASK_NUM; cnt++) {
        D_800E7D90[cnt].next = &D_800E7D90[cnt + 1];
        D_800E7D90[cnt].msgQ = &D_800E9BA8;
        D_800E7D90[cnt].list.type = 1; /* M_GFXTASK */
        D_800E7D90[cnt].list.flags = 0;
        D_800E7D90[cnt].list.ucode_boot = D_8009ECB0;
        D_800E7D90[cnt].list.ucode_boot_size = (s32)D_8009ED80 - (s32)D_8009ECB0;
        D_800E7D90[cnt].list.ucode_size = 0x1000;
        D_800E7D90[cnt].list.ucode_data_size = 0x800;
        D_800E7D90[cnt].list.dram_stack = D_800E8710;
        D_800E7D90[cnt].list.dram_stack_size = 0x400;
        D_800E7D90[cnt].list.output_buff = D_800C7970;
        D_800E7D90[cnt].list.yield_data_ptr = D_800C6D70;
        D_800E7D90[cnt].list.yield_data_size = 0xC00;
        D_800E7D90[cnt].msgQ = &D_800E9BA8;
    }
    D_800E7D90[NU_GFX_TASK_NUM - 1].next = &D_800E7D90[0];
    D_800B9C80 = &D_800E7D90[0];
}

/* nuGfxTaskStart */
void func_80089804(void *gfxList_ptr, u32 gfxListSize, u32 ucode, u32 flag) {
    u32 mask;

    D_800B9C80->list.data_ptr = gfxList_ptr;
    D_800B9C80->list.data_size = gfxListSize;
    D_800B9C80->list.flags = flag >> 16;
    D_800B9C80->list.ucode = D_800C4CE0[ucode].ucode;
    D_800B9C80->list.ucode_data = D_800C4CE0[ucode].ucode_data;
    D_800B9C80->flags = flag & 0xFFFF;
    D_800B9C80->framebuffer = D_800E8210;
    D_800B9C80->list.output_buff_size = (u64 *)(D_800A9E70 + (u32)D_800C7970);

    if (D_800A9E90 & 4) {
        D_800A9E90 ^= 4;
        D_800B9C80->list.flags |= 2;
    }
    D_800A9E90 = flag;

    if (flag & NU_SC_SWAPBUFFER) {
        D_800B9C80->msg = &D_800B9C86;
        D_800C4BC4 = (D_800C4BC4 + 1) % D_800A9E80;
        D_800E8210 = D_800E8290[D_800C4BC4];
    } else {
        D_800B9C80->msg = &D_800B9C84;
    }

    mask = osSetIntMask(1);
    D_800E79A4++;
    osSetIntMask(mask);

    osWritebackDCacheAll();
    osSendMesg(&D_800E8B4C, D_800B9C80, 1);
    D_800B9C80 = D_800B9C80->next;
}
