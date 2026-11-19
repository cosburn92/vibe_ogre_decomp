#ifndef NUSYS_H
#define NUSYS_H

/* The libultra and NuSystem types the nusys files use (layouts from the public SDK headers). */

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
    /* 0x00 */ u32 w0;
    /* 0x04 */ u32 w1;
} Gfx;

typedef struct {
    /* 0x00 */ u16 type;
    /* 0x02 */ u8 status;
    /* 0x03 */ u8 errno;
} OSContStatus;

typedef struct {
    /* 0x00 */ u16 button;
    /* 0x02 */ s8 stick_x;
    /* 0x03 */ s8 stick_y;
    /* 0x04 */ u8 errno;
} OSContPad;

typedef s16 NUScMsg;

typedef struct NUScClient_s {
    /* 0x00 */ struct NUScClient_s *next;
    /* 0x04 */ OSMesgQueue *msgQ;
    /* 0x08 */ NUScMsg msgType;
} NUScClient;

typedef struct {
    /* 0x00 */ NUScMsg mesg;
    /* 0x04 */ OSMesgQueue *rtnMesgQ;
    /* 0x08 */ s32 error;
    /* 0x0C */ void *dataPtr;
} NUSiCommonMesg;

typedef s32 (*NUCallBackFunc)(NUSiCommonMesg *mesg);

typedef struct NUCallBackList_s {
    /* 0x00 */ struct NUCallBackList_s *next;
    /* 0x04 */ NUCallBackFunc *func;
    /* 0x08 */ u16 majorNo;
    /* 0x0A */ u8 funcNum;
} NUCallBackList;

#define OS_MESG_NOBLOCK 0
#define OS_MESG_BLOCK 1

void osCreateMesgQueue(OSMesgQueue *mq, OSMesg *msg, s32 count);
s32 osSendMesg(OSMesgQueue *mq, OSMesg msg, s32 flag);
s32 osRecvMesg(OSMesgQueue *mq, OSMesg *msg, s32 flag);
void osCreateThread(OSThread *t, s32 id, void (*entry)(void *), void *arg, void *sp, s32 pri);
void osStartThread(OSThread *t);
void osStopThread(OSThread *t);

s32 func_80089CF8(NUScMsg mesg, void *dataPtr); /* nuSiSendMesg */

#endif
