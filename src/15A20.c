#include "common.h"

/* libmus: scheduler glue (audio tasks go through the game's OSSched) */

typedef void *OSMesg;

typedef struct {
    /* 0x00 */ void *mtqueue;
    /* 0x04 */ void *fullqueue;
    /* 0x08 */ s32 validCount;
    /* 0x0C */ s32 first;
    /* 0x10 */ s32 msgCount;
    /* 0x14 */ OSMesg *msg;
} OSMesgQueue; /* size 0x18 */

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
} OSTask_t; /* size 0x40 */

typedef struct OSScTask_s {
    /* 0x00 */ struct OSScTask_s *next;
    /* 0x04 */ u32 state;
    /* 0x08 */ u32 flags;
    /* 0x0C */ void *framebuffer;
    /* 0x10 */ OSTask_t list;
    /* 0x50 */ OSMesgQueue *msgQ;
    /* 0x54 */ OSMesg msg;
    /* 0x58 */ u64 startTime;
    /* 0x60 */ u64 totalTime;
} OSScTask; /* size 0x68 */

typedef struct {
    /* 0x00 */ s16 type;
    /* 0x02 */ s8 misc[30];
} OSScMsg;

typedef struct OSScClient_s {
    /* 0x00 */ struct OSScClient_s *next;
    /* 0x04 */ OSMesgQueue *msgQ;
} OSScClient;

typedef struct {
    /* 0x00 */ OSScClient client;
    /* 0x08 */ OSMesgQueue msgQ;
    /* 0x20 */ OSMesg msgbuf[4];
    /* 0x30 */ OSMesgQueue taskQ;
    /* 0x48 */ OSMesg taskbuf[4];
} MusSchedData; /* size 0x58 */

/* the audio task as built by the audio manager */
typedef struct {
    /* 0x00 */ u64 *data;
    /* 0x04 */ u32 size;
    /* 0x08 */ u64 *ucode;
    /* 0x0C */ u64 *ucode_data;
} MusTask;

extern void *D_800B18A0; /* OSSched * */
extern MusSchedData *D_800B18A4;
extern u64 D_8009ECB0[]; /* rspbootTextStart */
extern u64 D_8009ED80[]; /* rspbootTextEnd */

void *__MusIntMemMalloc(s32 size);
void osCreateMesgQueue(OSMesgQueue *mq, OSMesg *msg, s32 count);
s32 osRecvMesg(OSMesgQueue *mq, OSMesg *msg, s32 flag);
s32 osSendMesg(OSMesgQueue *mq, OSMesg msg, s32 flag);
void osScAddClient(void *sc, OSScClient *c, OSMesgQueue *msgQ);
OSMesgQueue *osScGetCmdQ(void *sc);

void func_80085620(void *sched) {
    D_800B18A0 = sched;
}

void __OsSchedInstall(void) {
    D_800B18A4 = __MusIntMemMalloc(sizeof(MusSchedData));
    osCreateMesgQueue(&D_800B18A4->msgQ, D_800B18A4->msgbuf, 4);
    osCreateMesgQueue(&D_800B18A4->taskQ, D_800B18A4->taskbuf, 4);
    osScAddClient(D_800B18A0, &D_800B18A4->client, &D_800B18A4->msgQ);
}

/* __OsSchedWaitFrame: wait for a retrace message */
void func_80085690(void) {
    OSScMsg *msg;

    do {
        osRecvMesg(&D_800B18A4->msgQ, (OSMesg *)&msg, 1);
        osRecvMesg(&D_800B18A4->msgQ, NULL, 0);
    } while (msg->type != 1);
}

/* __OsSchedDoTask */
void func_800856F0(MusTask *task) {
    OSScTask t;
    OSScMsg msg;

    t.next = NULL;
    t.msgQ = &D_800B18A4->taskQ;
    t.msg = &msg;
    t.flags = 2;
    t.list.data_ptr = task->data;
    t.list.data_size = task->size;
    t.list.type = 2;
    t.list.ucode_boot = D_8009ECB0;
    t.list.ucode_boot_size = (u8 *)D_8009ED80 - (u8 *)D_8009ECB0;
    t.list.flags = 0;
    t.list.ucode = task->ucode;
    t.list.ucode_data = task->ucode_data;
    t.list.ucode_size = 0x1000;
    t.list.ucode_data_size = 0x800;
    t.list.dram_stack = NULL;
    t.list.dram_stack_size = 0;
    t.list.output_buff = NULL;
    t.list.output_buff_size = NULL;
    t.list.yield_data_ptr = NULL;
    t.list.yield_data_size = 0;
    osSendMesg(osScGetCmdQ(D_800B18A0), &t, 1);
    osRecvMesg(&D_800B18A4->taskQ, NULL, 1);
}
