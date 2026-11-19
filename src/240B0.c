#include "common.h"
#include "libultra.h"

/* libultra sched.c (the SDK's OSSched) */

#define VIDEO_MSG 666
#define RSP_DONE_MSG 667
#define RDP_DONE_MSG 668
#define PRE_NMI_MSG 669

#define OS_SC_RETRACE_MSG 1
#define OS_SC_PRE_NMI_MSG 4
#define OS_SC_MAX_MESGS 8

#define OS_SC_NEEDS_RDP 0x0001
#define OS_SC_NEEDS_RSP 0x0002
#define OS_SC_DRAM_DLIST 0x0004
#define OS_SC_PARALLEL_TASK 0x0010
#define OS_SC_LAST_TASK 0x0020
#define OS_SC_SWAPBUFFER 0x0040
#define OS_SC_RCP_MASK 0x0003
#define OS_SC_TYPE_MASK 0x0007
#define OS_SC_XBUS (OS_SC_NEEDS_RDP | OS_SC_NEEDS_RSP)
#define OS_SC_DRAM (OS_SC_NEEDS_RDP | OS_SC_NEEDS_RSP | OS_SC_DRAM_DLIST)
#define OS_SC_DP_XBUS (OS_SC_NEEDS_RDP)
#define OS_SC_DP_DRAM (OS_SC_NEEDS_RDP | OS_SC_DRAM_DLIST)
#define OS_SC_SP_XBUS (OS_SC_NEEDS_RSP)
#define OS_SC_SP_DRAM (OS_SC_NEEDS_RSP | OS_SC_DRAM_DLIST)
#define OS_SC_YIELD 0x0010
#define OS_SC_YIELDED 0x0020
#define OS_SC_SP 0x0002
#define OS_SC_DP 0x0001

#define M_GFXTASK 1
#define M_AUDTASK 2

#define OS_EVENT_SP 4
#define OS_EVENT_DP 9
#define OS_EVENT_PRENMI 14

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

typedef struct {
    /* 0x00 */ s16 type;
    /* 0x02 */ s8 misc[30];
} OSScMsg;

typedef struct OSScTask_s {
    /* 0x00 */ struct OSScTask_s *next;
    /* 0x04 */ u32 state;
    /* 0x08 */ u32 flags;
    /* 0x0C */ void *framebuffer;
    /* 0x10 */ OSTask list;
    /* 0x50 */ OSMesgQueue *msgQ;
    /* 0x54 */ OSMesg msg;
} OSScTask;

typedef struct OSScClient_s {
    /* 0x00 */ struct OSScClient_s *next;
    /* 0x04 */ OSMesgQueue *msgQ;
} OSScClient;

typedef struct {
    /* 0x000 */ OSScMsg retraceMsg;
    /* 0x020 */ OSScMsg prenmiMsg;
    /* 0x040 */ OSMesgQueue interruptQ;
    /* 0x058 */ OSMesg intBuf[OS_SC_MAX_MESGS];
    /* 0x078 */ OSMesgQueue cmdQ;
    /* 0x090 */ OSMesg cmdMsgBuf[OS_SC_MAX_MESGS];
    /* 0x0B0 */ OSThread thread;
    /* 0x260 */ OSScClient *clientList;
    /* 0x264 */ OSScTask *audioListHead;
    /* 0x268 */ OSScTask *gfxListHead;
    /* 0x26C */ OSScTask *audioListTail;
    /* 0x270 */ OSScTask *gfxListTail;
    /* 0x274 */ OSScTask *curRSPTask;
    /* 0x278 */ OSScTask *curRDPTask;
    /* 0x27C */ u32 frameCount;
    /* 0x280 */ s32 doAudio;
} OSSched;

extern OSViMode osViModeTable[];
extern s32 D_800AA774; /* dp_busy */
extern s32 D_800AA778; /* dpCount */
extern s32 D_800AA77C; /* firsttime */

u32 osSetIntMask(u32 mask);
void osCreateViManager(s32 pri);
void osViSetMode(OSViMode *modep);
void osViBlack(u8 active);
void osViSetEvent(OSMesgQueue *mq, OSMesg m, u32 retraceCount);
void osSetEventMesg(s32 event, OSMesgQueue *mq, OSMesg msg);
void *osViGetCurrentFramebuffer(void);
void *osViGetNextFramebuffer(void);
void osViSwapBuffer(void *frameBufPtr);
s32 osSpTaskYielded(OSTask *tp);
void osSpTaskYield(void);
void osSpTaskLoad(OSTask *tp);
void osSpTaskStartGo(OSTask *tp);
void osWritebackDCacheAll(void);
s32 osDpSetNextBuffer(void *buf, u64 size);

void __scMain(void *arg);
void __scHandleRetrace(OSSched *sc);
void __scHandleRSP(OSSched *sc);
void __scHandleRDP(OSSched *sc);
s32 __scTaskComplete(OSSched *sc, OSScTask *t);
void __scAppendList(OSSched *sc, OSScTask *t);
void __scExec(OSSched *sc, OSScTask *sp, OSScTask *dp);
void __scYield(OSSched *sc);
s32 __scSchedule(OSSched *sc, OSScTask **sp, OSScTask **dp, s32 availRCP);

void osCreateScheduler(OSSched *sc, void *stack, s32 priority, u8 mode, u8 numFields) {
    sc->curRSPTask = 0;
    sc->curRDPTask = 0;
    sc->clientList = 0;
    sc->frameCount = 0;
    sc->audioListHead = 0;
    sc->gfxListHead = 0;
    sc->audioListTail = 0;
    sc->gfxListTail = 0;
    sc->retraceMsg.type = OS_SC_RETRACE_MSG;
    sc->prenmiMsg.type = OS_SC_PRE_NMI_MSG;

    osCreateMesgQueue(&sc->interruptQ, sc->intBuf, OS_SC_MAX_MESGS);
    osCreateMesgQueue(&sc->cmdQ, sc->cmdMsgBuf, OS_SC_MAX_MESGS);

    osCreateViManager(254); /* OS_PRIORITY_VIMGR */
    osViSetMode(&osViModeTable[mode]);
    osViBlack(1);
    osSetEventMesg(OS_EVENT_SP, &sc->interruptQ, (OSMesg)RSP_DONE_MSG);
    osSetEventMesg(OS_EVENT_DP, &sc->interruptQ, (OSMesg)RDP_DONE_MSG);
    osSetEventMesg(OS_EVENT_PRENMI, &sc->interruptQ, (OSMesg)PRE_NMI_MSG);
    osViSetEvent(&sc->interruptQ, (OSMesg)VIDEO_MSG, numFields);

    osCreateThread(&sc->thread, 4, __scMain, (void *)sc, stack, priority);
    osStartThread(&sc->thread);
}

void osScAddClient(OSSched *sc, OSScClient *c, OSMesgQueue *msgQ) {
    u32 mask;

    mask = osSetIntMask(1); /* OS_IM_NONE */
    c->msgQ = msgQ;
    c->next = sc->clientList;
    sc->clientList = c;
    osSetIntMask(mask);
}

void osScRemoveClient(OSSched *sc, OSScClient *c) {
    OSScClient *client = sc->clientList;
    OSScClient *prev = 0;
    u32 mask;

    mask = osSetIntMask(1);

    while (client != 0) {
        if (client == c) {
            if (prev) {
                prev->next = c->next;
            } else {
                sc->clientList = c->next;
            }
            break;
        }
        prev = client;
        client = client->next;
    }

    osSetIntMask(mask);
}

OSMesgQueue *osScGetCmdQ(OSSched *sc) {
    return &sc->cmdQ;
}

void __scMain(void *arg) {
    OSMesg msg;
    OSSched *sc = (OSSched *)arg;
    OSScClient *client;

    while (1) {
        osRecvMesg(&sc->interruptQ, (OSMesg *)&msg, OS_MESG_BLOCK);
        switch ((int)msg) {
            case VIDEO_MSG:
                __scHandleRetrace(sc);
                break;
            case RSP_DONE_MSG:
                __scHandleRSP(sc);
                break;
            case RDP_DONE_MSG:
                __scHandleRDP(sc);
                break;
            case PRE_NMI_MSG:
                for (client = sc->clientList; client != 0; client = client->next) {
                    osSendMesg(client->msgQ, (OSMesg)&sc->prenmiMsg, OS_MESG_NOBLOCK);
                }
                break;
        }
    }
}

void __scHandleRetrace(OSSched *sc) {
    OSScTask *rspTask;
    OSScClient *client;
    s32 state;
    OSScTask *sp = 0;
    OSScTask *dp = 0;

    sc->frameCount++;

    while (osRecvMesg(&sc->cmdQ, (OSMesg *)&rspTask, OS_MESG_NOBLOCK) != -1) {
        __scAppendList(sc, rspTask);
    }

    if (sc->doAudio && sc->curRSPTask) {
        __scYield(sc);
    } else {
        state = (sc->curRSPTask == 0) << 1;
        if (sc->curRDPTask == 0) {
            state |= 1;
        }
        if (__scSchedule(sc, &sp, &dp, state) != state) {
            __scExec(sc, sp, dp);
        }
    }

    for (client = sc->clientList; client != 0; client = client->next) {
        osSendMesg(client->msgQ, (OSMesg)&sc->retraceMsg, OS_MESG_NOBLOCK);
    }
}

void __scHandleRSP(OSSched *sc) {
    OSScTask *t, *sp = 0, *dp = 0;
    s32 state;

    t = sc->curRSPTask;
    sc->curRSPTask = 0;

    if ((t->state & OS_SC_YIELD) && osSpTaskYielded(&t->list)) {
        t->state |= OS_SC_YIELDED;
        if ((t->flags & OS_SC_TYPE_MASK) == OS_SC_XBUS) {
            t->next = sc->gfxListHead;
            sc->gfxListHead = t;
            if (sc->gfxListTail == 0) {
                sc->gfxListTail = t;
            }
        }
    } else {
        t->state &= ~OS_SC_NEEDS_RSP;
        __scTaskComplete(sc, t);
    }

    state = (sc->curRSPTask == 0) << 1;
    if (sc->curRDPTask == 0) {
        state |= 1;
    }
    if (__scSchedule(sc, &sp, &dp, state) != state) {
        __scExec(sc, sp, dp);
    }
}

void __scHandleRDP(OSSched *sc) {
    OSScTask *t, *sp = 0, *dp = 0;
    s32 state;

    t = sc->curRDPTask;
    sc->curRDPTask = 0;

    t->state &= ~OS_SC_NEEDS_RDP;

    __scTaskComplete(sc, t);

    state = (sc->curRSPTask == 0) << 1;
    if (sc->curRDPTask == 0) {
        state |= 1;
    }
    if (__scSchedule(sc, &sp, &dp, state) != state) {
        __scExec(sc, sp, dp);
    }
}

inline OSScTask *__scTaskReady(OSScTask *t) {
    void *a;
    void *b;

    if (t) {
        a = osViGetCurrentFramebuffer();
        b = osViGetNextFramebuffer();
        if (a != b) {
            return 0;
        }
        return t;
    }
    return 0;
}

s32 __scTaskComplete(OSSched *sc, OSScTask *t) {
    if ((t->state & OS_SC_RCP_MASK) == 0) {
        osSendMesg(t->msgQ, t->msg, OS_MESG_BLOCK);

        if (t->list.t.type == M_GFXTASK) {
            if ((t->flags & (OS_SC_SWAPBUFFER | OS_SC_LAST_TASK)) == (OS_SC_SWAPBUFFER | OS_SC_LAST_TASK)) {
                if (D_800AA77C) {
                    osViBlack(0);
                    D_800AA77C = 0;
                }
                osViSwapBuffer(t->framebuffer);
            }
        }
        return 1;
    }
    return 0;
}

void __scAppendList(OSSched *sc, OSScTask *t) {
    long type = t->list.t.type;

    if (type == M_AUDTASK) {
        if (sc->audioListTail) {
            sc->audioListTail->next = t;
        } else {
            sc->audioListHead = t;
        }
        sc->audioListTail = t;
        sc->doAudio = 1;
    } else {
        if (sc->gfxListTail) {
            sc->gfxListTail->next = t;
        } else {
            sc->gfxListHead = t;
        }
        sc->gfxListTail = t;
    }

    t->next = NULL;
    t->state = t->flags & OS_SC_RCP_MASK;
}

void __scExec(OSSched *sc, OSScTask *sp, OSScTask *dp) {
    if (sp) {
        if (sp->list.t.type == M_AUDTASK) {
            osWritebackDCacheAll();
        }

        sp->state &= ~(OS_SC_YIELD | OS_SC_YIELDED);
        osSpTaskLoad(&sp->list);
        osSpTaskStartGo(&sp->list);
        sc->curRSPTask = sp;

        if (sp == dp) {
            sc->curRDPTask = dp;
        }
    }

    if (dp && (dp != sp)) {
        osDpSetNextBuffer(dp->list.t.output_buff, *dp->list.t.output_buff_size);
        D_800AA774 = 1;
        D_800AA778 = 0;
        sc->curRDPTask = dp;
    }
}

void __scYield(OSSched *sc) {
    if (sc->curRSPTask->list.t.type == M_GFXTASK) {
        sc->curRSPTask->state |= OS_SC_YIELD;
        osSpTaskYield();
    }
}

s32 __scSchedule(OSSched *sc, OSScTask **sp, OSScTask **dp, s32 availRCP) {
    s32 avail = availRCP;
    OSScTask *gfx = sc->gfxListHead;
    OSScTask *audio = sc->audioListHead;

    if (sc->doAudio && (avail & OS_SC_SP)) {
        if (gfx && (gfx->flags & OS_SC_PARALLEL_TASK)) {
            *sp = gfx;
            avail &= ~OS_SC_SP;
        } else {
            *sp = audio;
            avail &= ~OS_SC_SP;
            sc->doAudio = 0;
            sc->audioListHead = sc->audioListHead->next;
            if (sc->audioListHead == NULL) {
                sc->audioListTail = NULL;
            }
        }
    } else {
        if (__scTaskReady(gfx)) {
            switch (gfx->flags & OS_SC_TYPE_MASK) {
                case OS_SC_XBUS:
                    if (gfx->state & OS_SC_YIELDED) {
                        if (avail & OS_SC_SP) {
                            *sp = gfx;
                            avail &= ~OS_SC_SP;

                            if (gfx->state & OS_SC_NEEDS_RDP) {
                                *dp = gfx;
                                avail &= ~OS_SC_DP;
                            }

                            sc->gfxListHead = sc->gfxListHead->next;
                            if (sc->gfxListHead == NULL) {
                                sc->gfxListTail = NULL;
                            }
                        }
                    } else {
                        if (avail == (OS_SC_SP | OS_SC_DP)) {
                            *sp = *dp = gfx;
                            avail &= ~(OS_SC_SP | OS_SC_DP);
                            sc->gfxListHead = sc->gfxListHead->next;
                            if (sc->gfxListHead == NULL) {
                                sc->gfxListTail = NULL;
                            }
                        }
                    }
                    break;

                case OS_SC_DRAM:
                case OS_SC_SP_XBUS:
                case OS_SC_SP_DRAM:
                    if (gfx->state & OS_SC_NEEDS_RSP) {
                        if (avail & OS_SC_SP) {
                            *sp = gfx;
                            avail &= ~OS_SC_SP;
                        }
                    } else if (gfx->state & OS_SC_NEEDS_RDP) {
                        if (avail & OS_SC_DP) {
                            *dp = gfx;
                            avail &= ~OS_SC_DP;
                            sc->gfxListHead = sc->gfxListHead->next;
                            if (sc->gfxListHead == NULL) {
                                sc->gfxListTail = NULL;
                            }
                        }
                    }
                    break;

                case OS_SC_DP_XBUS:
                case OS_SC_DP_DRAM:
                    break;
            }
        }
    }

    if (avail != availRCP) {
        avail = __scSchedule(sc, sp, dp, avail);
    }

    return avail;
}
