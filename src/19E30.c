#include "common.h"

/* NuSystem nugfxretracewait.c */

typedef void *OSMesg;

typedef struct {
    /* 0x00 */ void *mtqueue;
    /* 0x04 */ void *fullqueue;
    /* 0x08 */ s32 validCount;
    /* 0x0C */ s32 first;
    /* 0x10 */ s32 msgCount;
    /* 0x14 */ OSMesg *msg;
} OSMesgQueue;

typedef struct NUScClient_s {
    /* 0x00 */ struct NUScClient_s *next;
    /* 0x04 */ OSMesgQueue *msgQ;
    /* 0x08 */ s16 msgType;
} NUScClient;

void osCreateMesgQueue(OSMesgQueue *mq, OSMesg *msg, s32 count);
s32 osRecvMesg(OSMesgQueue *mq, OSMesg *msg, s32 flag);
void func_80089054(NUScClient *c, OSMesgQueue *mq, s16 msgType); /* nuScAddClient */
void func_80089124(NUScClient *c);                             /* nuScRemoveClient */

/* nuGfxRetraceWait */
void func_80089A30(u32 retrace_num) {
    NUScClient client;
    OSMesgQueue mesgQ;
    OSMesg mesgBuf;

    osCreateMesgQueue(&mesgQ, &mesgBuf, 1);
    func_80089054(&client, &mesgQ, 1); /* NU_SC_RETRACE_MSG */
    while (retrace_num) {
        osRecvMesg(&mesgQ, NULL, 1);
        retrace_num--;
    }
    func_80089124(&client);
}
