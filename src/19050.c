#include "common.h"

/*
 * NuSystem (nusys) nusched.c: the scheduler with its event, audio and graphics threads, plus a
 * game-specific fourth thread that loads graphics tasks onto the RSP once it has halted.
 */

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

typedef struct NUScClient_s {
    /* 0x00 */ struct NUScClient_s *next;
    /* 0x04 */ OSMesgQueue *msgQ;
    /* 0x08 */ NUScMsg msgType;
} NUScClient;

typedef struct NUScTask_s {
    /* 0x00 */ struct NUScTask_s *next;
    /* 0x04 */ u32 state;
    /* 0x08 */ u32 flags;
    /* 0x0C */ void *framebuffer;
    /* 0x10 */ OSTask list;
    /* 0x50 */ OSMesgQueue *msgQ;
    /* 0x54 */ OSMesg msg;
} NUScTask;

typedef struct {
    /* 0x000 */ NUScMsg retraceMsg;
    /* 0x002 */ NUScMsg prenmiMsg;
    /* 0x004 */ OSMesgQueue audioRequestMQ;
    /* 0x01C */ OSMesg audioRequestBuf[8];
    /* 0x03C */ OSMesgQueue graphicsRequestMQ;
    /* 0x054 */ OSMesg graphicsRequestBuf[8];
    /* 0x074 */ OSMesgQueue retraceMQ;
    /* 0x08C */ OSMesg retraceMsgBuf[8];
    /* 0x0AC */ OSMesgQueue rspMQ;
    /* 0x0C4 */ OSMesg rspMsgBuf[8];
    /* 0x0E4 */ OSMesgQueue rdpMQ;
    /* 0x0FC */ OSMesg rdpMsgBuf[8];
    /* 0x11C */ OSMesgQueue waitMQ;
    /* 0x134 */ OSMesg waitMsgBuf[8];
    /* 0x158 */ OSThread schedulerThread;
    /* 0x308 */ OSThread audioThread;
    /* 0x4B8 */ OSThread graphicsThread;
    /* 0x668 */ NUScClient *clientList;
    /* 0x66C */ NUScTask *curGraphicsTask;
    /* 0x670 */ NUScTask *curAudioTask;
    /* 0x674 */ NUScTask *graphicsTaskSuspended;
    /* 0x678 */ u32 retraceCount;
    /* 0x67C */ u8 frameRate;
    /* 0x67D */ u8 frameBufferNum;
} NUSched;

#define NU_SC_RETRACE_MSG 1
#define NU_SC_PRENMI_MSG 2
#define NU_SC_RESET_FLAG 1
#define NU_SC_BEFORE_RESET 2
#define NU_SC_NOSWAPBUFFER 2

extern NUSched nusched;
extern u8 nuScPreNMIFlag;
extern u32 nuScRetraceCounter;
extern void (*nuScPreNMIFunc)(void);
extern u64 nuScStack[];
extern u64 nuScAudioStack[];
extern u64 nuScGraphicsStack[];
extern OSThread D_800B7A90;         /* the RSP loader thread */
extern OSMesgQueue D_800B9C40;      /* graphics tasks for the RSP loader thread */
extern OSMesg D_800B9C58[];
extern u8 osViModeTable[];
extern s32 osTvType;

void osCreateMesgQueue(OSMesgQueue *mq, OSMesg *msg, s32 count);
s32 osRecvMesg(OSMesgQueue *mq, OSMesg *msg, s32 flag);
s32 osSendMesg(OSMesgQueue *mq, OSMesg msg, s32 flag);
void osCreateViManager(s32 pri);
void osViSetMode(void *mode);
void osViSetEvent(OSMesgQueue *mq, OSMesg msg, u32 retraceCount);
void osSetEventMesg(s32 event, OSMesgQueue *mq, OSMesg msg);
void osCreateThread(void *t, s32 id, void (*entry)(void *), void *arg, void *sp, s32 pri);
void osStartThread(void *t);
u32 osSetIntMask(u32 mask);
void osWritebackDCacheAll(void);
u32 __osSpGetStatus(void);
void osSpTaskYield(void);
s32 osSpTaskYielded(OSTask *task);
void osSpTaskLoad(OSTask *task);
void osSpTaskStartGo(OSTask *task);
s32 osAfterPreNMI(void);
void osViSetYScale(f32 scale);
void *osViGetCurrentFramebuffer(void);
void *osViGetNextFramebuffer(void);
void func_80089BE4(u8 active); /* nusys osViBlack wrapper */

void func_80088F08(void *arg);
void func_80089200(void *arg);
void func_800893C0(void *arg);
void func_80089358(void *arg);
void func_80089054(NUScClient *c, OSMesgQueue *mq, NUScMsg msgType);
void func_80089124(NUScClient *c);
void func_800891A0(NUScMsg *msg);
void func_8008949C(NUScTask *task);

/* nuScCreateScheduler */
void func_80088C50(u8 videoMode, u8 numFields) {
    nusched.curGraphicsTask = NULL;
    nusched.curAudioTask = NULL;
    nusched.graphicsTaskSuspended = NULL;
    nusched.clientList = NULL;
    nusched.retraceMsg = NU_SC_RETRACE_MSG;
    nusched.prenmiMsg = NU_SC_PRENMI_MSG;
    nusched.retraceCount = numFields;
    nusched.frameBufferNum = 2;
    if (osTvType == 0) { /* OS_TV_PAL */
        nusched.frameRate = 50;
    } else {
        nusched.frameRate = 60;
    }
    nuScPreNMIFlag = 0;

    osCreateMesgQueue(&nusched.retraceMQ, nusched.retraceMsgBuf, 8);
    osCreateMesgQueue(&nusched.rspMQ, nusched.rspMsgBuf, 8);
    osCreateMesgQueue(&nusched.rdpMQ, nusched.rdpMsgBuf, 8);
    osCreateMesgQueue(&nusched.graphicsRequestMQ, nusched.graphicsRequestBuf, 8);
    osCreateMesgQueue(&nusched.audioRequestMQ, nusched.audioRequestBuf, 8);
    osCreateMesgQueue(&nusched.waitMQ, nusched.waitMsgBuf, 8);

    osCreateViManager(254); /* OS_PRIORITY_VIMGR */
    osViSetMode(&osViModeTable[videoMode * 0x50]);
    func_80089BE4(1);

    osViSetEvent(&nusched.retraceMQ, (OSMesg)666, numFields);
    osSetEventMesg(4, &nusched.rspMQ, (OSMesg)667);      /* OS_EVENT_SP */
    osSetEventMesg(9, &nusched.rdpMQ, (OSMesg)668);      /* OS_EVENT_DP */
    osSetEventMesg(14, &nusched.retraceMQ, (OSMesg)669); /* OS_EVENT_PRENMI */

    osCreateThread(&nusched.schedulerThread, 19, func_80088F08, &nusched, nuScStack + 0x2000 / 8, 120);
    osStartThread(&nusched.schedulerThread);
    osCreateThread(&nusched.audioThread, 18, func_80089200, &nusched, nuScAudioStack + 0x2000 / 8, 110);
    osStartThread(&nusched.audioThread);
    osCreateThread(&nusched.graphicsThread, 17, func_800893C0, &nusched, nuScGraphicsStack + 0x2000 / 8, 100);
    osStartThread(&nusched.graphicsThread);

    osCreateMesgQueue(&D_800B9C40, D_800B9C58, 8);
    osCreateThread(&D_800B7A90, 16, func_80089358, NULL, (u8 *)D_800B9C58 + 0x1000, 111);
    osStartThread(&D_800B7A90);
}

/* nuScGetAudioMQ */
OSMesgQueue *func_80088EF0(void) {
    return &nusched.audioRequestMQ;
}

/* nuScGetGfxMQ */
OSMesgQueue *func_80088EFC(void) {
    return &nusched.graphicsRequestMQ;
}

/* nuScEventHandler */
void func_80088F08(void *arg) {
    OSMesg msg;
    s32 beforeResetFrame;

    nuScRetraceCounter = 0;

    while (1) {
        osRecvMesg(&nusched.retraceMQ, &msg, 1);

        switch ((s32)msg) {
            case 666: /* retrace */
                nuScRetraceCounter++;
                func_800891A0(&nusched.retraceMsg);

                if (nuScPreNMIFlag) {
                    if (beforeResetFrame) {
                        beforeResetFrame--;
                    } else {
                        nuScPreNMIFlag |= NU_SC_BEFORE_RESET;
                        osAfterPreNMI();
                        osViSetYScale(1.0f);
                        func_80089BE4(1);
                    }
                }
                break;

            case 669: /* pre-NMI */
                nuScPreNMIFlag = NU_SC_RESET_FLAG;
                func_800891A0(&nusched.prenmiMsg);
                if (nuScPreNMIFunc != NULL) {
                    nuScPreNMIFunc();
                }
                beforeResetFrame = nusched.frameRate / 2 / nusched.retraceCount - 3;
                break;
        }
    }
}

/* nuScAddClient */
void func_80089054(NUScClient *c, OSMesgQueue *mq, NUScMsg msgType) {
    u32 mask;

    mask = osSetIntMask(1);
    c->msgQ = mq;
    c->next = nusched.clientList;
    c->msgType = msgType;
    nusched.clientList = c;
    if ((msgType & NU_SC_PRENMI_MSG) && nuScPreNMIFlag) {
        osSendMesg(mq, &nusched.prenmiMsg, 0);
    }
    osSetIntMask(mask);
}

/* nuScResetClientMesgType */
void func_800890E4(NUScClient *c, NUScMsg msgType) {
    u32 mask;

    mask = osSetIntMask(1);
    c->msgType = msgType;
    osSetIntMask(mask);
}

/* nuScRemoveClient */
void func_80089124(NUScClient *c) {
    u32 mask;
    NUScClient *client;
    NUScClient *prev;

    mask = osSetIntMask(1);
    client = nusched.clientList;
    prev = 0;
    while (client != 0) {
        if (client == c) {
            if (prev) {
                prev->next = c->next;
            } else {
                nusched.clientList = c->next;
            }
            break;
        }
        prev = client;
        client = client->next;
    }
    osSetIntMask(mask);
}

/* nuScEventBroadcast */
void func_800891A0(NUScMsg *msg) {
    NUScClient *client;

    for (client = nusched.clientList; client != 0; client = client->next) {
        if (client->msgType & *msg) {
            osSendMesg(client->msgQ, msg, 0);
        }
    }
}

/* nuScExecuteAudio */
void func_80089200(void *arg) {
    NUScTask *gfxTask;
    NUScTask *audioTask;
    OSMesg msg;
    u32 yieldFlag;

    while (1) {
        osRecvMesg(&nusched.audioRequestMQ, (OSMesg *)&audioTask, 1);

        if (!(nuScPreNMIFlag & NU_SC_BEFORE_RESET)) {
            osWritebackDCacheAll();

            yieldFlag = 0;
            gfxTask = nusched.curGraphicsTask;

            if ((__osSpGetStatus() & 0x202) != 0x202 && gfxTask) {
                osSpTaskYield();
                yieldFlag = 2;
                osRecvMesg(&nusched.rspMQ, &msg, 1);
                if (osSpTaskYielded(&gfxTask->list)) {
                    yieldFlag = 1;
                }
            }

            nusched.curAudioTask = audioTask;
            osSpTaskLoad(&audioTask->list);
            osSpTaskStartGo(&audioTask->list);
            osRecvMesg(&nusched.rspMQ, &msg, 1);
            nusched.curAudioTask = NULL;

            if (yieldFlag == 1) {
                osSpTaskLoad(&gfxTask->list);
                osSpTaskStartGo(&gfxTask->list);
            } else if (yieldFlag == 2) {
                osSendMesg(&nusched.rspMQ, &msg, 1);
            }
        }
        osSendMesg(audioTask->msgQ, audioTask->msg, 1);
    }
}

/* the RSP loader thread: starts each graphics task once the RSP has halted */
void func_80089358(void *arg) {
    NUScTask *task;

    while (1) {
        osRecvMesg(&D_800B9C40, (OSMesg *)&task, 1);
        while (!(__osSpGetStatus() & 1)) { /* SP_STATUS_HALT */
        }
        nusched.curGraphicsTask = task;
        if (task != NULL) {
            osSpTaskLoad(&task->list);
            osSpTaskStartGo(&task->list);
        }
    }
}

/* nuScExecuteGraph */
void func_800893C0(void *arg) {
    OSMesg msg;
    NUScTask *gfxTask;

    while (1) {
        osRecvMesg(&nusched.graphicsRequestMQ, (OSMesg *)&gfxTask, 1);

        if (!(nuScPreNMIFlag & NU_SC_BEFORE_RESET)) {
            func_8008949C(gfxTask);
            osWritebackDCacheAll();
            osSendMesg(&D_800B9C40, gfxTask, 1);
            osRecvMesg(&nusched.rspMQ, &msg, 1);
            osSendMesg(&D_800B9C40, NULL, 1);
            if (!(gfxTask->flags & NU_SC_NOSWAPBUFFER)) {
                osRecvMesg(&nusched.rdpMQ, &msg, 1);
            }
        }
        osSendMesg(gfxTask->msgQ, gfxTask, 1);
    }
}

/* nuScWaitTaskReady */
void func_8008949C(NUScTask *task) {
    NUScClient client;
    void *fb = task->framebuffer;

    if (nusched.frameBufferNum == 1) {
        return;
    }
    while (osViGetCurrentFramebuffer() == fb || osViGetNextFramebuffer() == fb) {
        func_80089054(&client, &nusched.waitMQ, NU_SC_RETRACE_MSG);
        osRecvMesg(&nusched.waitMQ, NULL, 1);
        func_80089124(&client);
    }
}

/* nuScSetFrameBufferNum */
void func_80089528(u8 frameBufferNum) {
    nusched.frameBufferNum = frameBufferNum;
}

/* nuScGetFrameRate */
u8 func_80089534(void) {
    return nusched.frameRate;
}

INCLUDE_ASM("asm/nonmatchings/19050", func_80089540);

INCLUDE_ASM("asm/nonmatchings/19050", func_80089660);

INCLUDE_ASM("asm/nonmatchings/19050", func_80089804);

INCLUDE_ASM("asm/nonmatchings/19050", func_80089990);
