#include "common.h"

/* NuSystem nugfxdisplayon.c, nusimgr.c, nupiinit.c, nupireadrom.c, nupiinitsram.c */

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

typedef s16 NUScMsg;

typedef struct NUScClient_s {
    /* 0x00 */ struct NUScClient_s *next;
    /* 0x04 */ OSMesgQueue *msgQ;
    /* 0x08 */ NUScMsg msgType;
} NUScClient;

typedef struct {
    /* 0x00 */ u16 type;
    /* 0x02 */ u8 pri;
    /* 0x03 */ u8 status;
    /* 0x04 */ OSMesgQueue *retQueue;
} OSIoMesgHdr;

typedef struct {
    /* 0x00 */ OSIoMesgHdr hdr;
    /* 0x08 */ void *dramAddr;
    /* 0x0C */ u32 devAddr;
    /* 0x10 */ u32 size;
    /* 0x14 */ void *piHandle;
} OSIoMesg;

typedef struct {
    /* 0x00 */ u32 errStatus;
    /* 0x04 */ void *dramAddr;
    /* 0x08 */ void *C2Addr;
    /* 0x0C */ u32 sectorSize;
    /* 0x10 */ u32 C1ErrNum;
    /* 0x14 */ u32 C1ErrSector[4];
} __OSBlockInfo;

typedef struct {
    /* 0x00 */ u32 cmdType;
    /* 0x04 */ u16 transferMode;
    /* 0x06 */ u16 blockNum;
    /* 0x08 */ s32 sectorNum;
    /* 0x0C */ u32 devAddr;
    /* 0x10 */ u32 bmCtlShadow;
    /* 0x14 */ u32 seqCtlShadow;
    /* 0x18 */ __OSBlockInfo block[2];
} __OSTranxInfo;

typedef struct OSPiHandle_s {
    /* 0x00 */ struct OSPiHandle_s *next;
    /* 0x04 */ u8 type;
    /* 0x05 */ u8 latency;
    /* 0x06 */ u8 pageSize;
    /* 0x07 */ u8 relDuration;
    /* 0x08 */ u8 pulse;
    /* 0x09 */ u8 domain;
    /* 0x0C */ u32 baseAddress;
    /* 0x10 */ u32 speed;
    /* 0x14 */ __OSTranxInfo transferInfo;
} OSPiHandle;

typedef struct {
    /* 0x00 */ u16 type;
    /* 0x02 */ u8 status;
    /* 0x03 */ u8 errno;
} OSContStatus;

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

extern u32 D_800C4BD8;               /* nuGfxDisplay */
extern NUCallBackList *D_800A9EA0;   /* nuSiCallBackList */
extern OSMesgQueue D_800E9B88;       /* nuSiMesgQ */
extern OSMesg D_800BBE60[];          /* nuSiMesgBuf */
extern OSThread D_800BBE80;          /* siMgrThread */
extern u64 D_800BE030[];             /* end of siMgrStack */
extern OSMesgQueue D_800E7988;       /* nuSiMgrMesgQ */
extern OSMesg D_800BE048[];          /* nuPiMesgBuf */
extern OSPiHandle *D_800E7A20;       /* nuPiCartHandle */
extern OSPiHandle *D_800E79AC;       /* nuPiSramHandle */
extern OSPiHandle nuPiSramHandleBody; /* SramHandle */

void osCreateMesgQueue(OSMesgQueue *mq, OSMesg *msg, s32 count);
s32 osSendMesg(OSMesgQueue *mq, OSMesg msg, s32 flag);
s32 osRecvMesg(OSMesgQueue *mq, OSMesg *msg, s32 flag);
void osSetEventMesg(s32 event, OSMesgQueue *mq, OSMesg msg);
s32 osContInit(OSMesgQueue *mq, u8 *bitpattern, OSContStatus *status);
void osCreateThread(OSThread *t, s32 id, void (*entry)(void *), void *arg, void *sp, s32 pri);
void osStartThread(OSThread *t);
void osStopThread(OSThread *t);
void osInvalDCache(void *vaddr, s32 nbytes);
void osCreatePiManager(s32 pri, OSMesgQueue *cmdQ, OSMesg *cmdBuf, s32 cmdMsgCnt);
OSPiHandle *osCartRomInit(void);
s32 func_8008BC40(OSPiHandle *pihandle, OSIoMesg *mb, s32 direction); /* osEPiStartDma */
s32 osEPiLinkHandle(OSPiHandle *eph);
void bzero(void *p, s32 n);
void func_80089054(NUScClient *c, OSMesgQueue *mq, NUScMsg msgType); /* nuScAddClient */
void func_800890E4(NUScClient *c, NUScMsg msgType);                 /* nuScResetClientMesgType */

void func_80089D9C(void *arg);

/* nuGfxDisplayOn */
void func_80089C50(void) {
    D_800C4BD8 = 0x80; /* NU_GFX_DISPLAY_ON_TRIGGER */
}

/* nuSiMgrInit */
u8 func_80089C60(void) {
    u8 pattern;
    OSContStatus status[4];

    osCreateMesgQueue(&D_800E9B88, D_800BBE60, 8);
    osSetEventMesg(5, &D_800E9B88, 0); /* OS_EVENT_SI */
    osContInit(&D_800E9B88, &pattern, status);
    osCreateThread(&D_800BBE80, 5, func_80089D9C, NULL, D_800BE030, 0x73);
    osStartThread(&D_800BBE80);
    return pattern;
}

/* nuSiSendMesg */
s32 func_80089CF8(NUScMsg mesg, void *dataPtr) {
    OSMesgQueue rtnMesgQ;
    NUSiCommonMesg siCommonMesg;
    OSMesg rtnMesgBuf;

    siCommonMesg.mesg = mesg;
    siCommonMesg.dataPtr = dataPtr;
    siCommonMesg.rtnMesgQ = &rtnMesgQ;
    osCreateMesgQueue(&rtnMesgQ, &rtnMesgBuf, 1);
    osSendMesg(&D_800E7988, (OSMesg)&siCommonMesg, 1);
    osRecvMesg(&rtnMesgQ, NULL, 1);
    return siCommonMesg.error;
}

/* nuSiMgrStop */
void func_80089D5C(void) {
    func_80089CF8(0x7F00, NULL); /* NU_SI_STOP_MGR_MSG */
}

/* nuSiMgrRestart */
void func_80089D7C(void) {
    osStartThread(&D_800BBE80);
}

/* nuSiMgrThread */
void func_80089D9C(void *arg) {
    NUScClient siClient;
    OSMesg mesgBuf[8];
    NUSiCommonMesg *siMesg;
    NUCallBackList **siCallBackListPtr;
    s32 ret;
    u16 majorNo;
    u16 minorNo;

    osCreateMesgQueue(&D_800E7988, mesgBuf, 8);
    func_80089054(&siClient, &D_800E7988, 1);

    while (1) {
        osRecvMesg(&D_800E7988, (OSMesg *)&siMesg, 1);
        siCallBackListPtr = &D_800A9EA0;
        switch (siMesg->mesg) {
            case 1: /* NU_SC_RETRACE_MSG */
                if (*siCallBackListPtr == NULL) {
                    continue;
                }
                while (*siCallBackListPtr) {
                    if ((*siCallBackListPtr)->func[0]) {
                        ret = (*(*siCallBackListPtr)->func[0])(siMesg);
                    }
                    if (ret) {
                        break;
                    }
                    siCallBackListPtr = &(*siCallBackListPtr)->next;
                }
                break;
            case 0x7F00: /* NU_SI_STOP_MGR_MSG */
                osSendMesg(siMesg->rtnMesgQ, NULL, 1);
                func_800890E4(&siClient, 0);
                osStopThread(NULL);
                func_800890E4(&siClient, 1);
                break;
            default:
                majorNo = siMesg->mesg & 0xFF00;
                minorNo = siMesg->mesg & 0x00FF;
                while (*siCallBackListPtr) {
                    if ((*siCallBackListPtr)->majorNo == majorNo) {
                        if ((*siCallBackListPtr)->funcNum > minorNo) {
                            siMesg->error = (*(*siCallBackListPtr)->func[minorNo])(siMesg);
                        }
                        if (siMesg->rtnMesgQ != NULL) {
                            osSendMesg(siMesg->rtnMesgQ, NULL, 1);
                        }
                        break;
                    }
                    siCallBackListPtr = &(*siCallBackListPtr)->next;
                }
                break;
        }
    }
}

/* nuPiInit */
void func_80089F40(void) {
    osCreatePiManager(150, (OSMesgQueue *)D_800BE030, D_800BE048, 50);
    D_800E7A20 = osCartRomInit();
}

/* nuPiReadRom */
void PiDmaRead(u32 rom_addr, void *buf_ptr, u32 size) {
    OSIoMesg dmaIoMesgBuf;
    OSMesgQueue dmaMesgQ;
    OSMesg dmaMesgBuf;
    u32 readSize;

    osCreateMesgQueue(&dmaMesgQ, &dmaMesgBuf, 1);
    dmaIoMesgBuf.hdr.pri = 0;
    dmaIoMesgBuf.hdr.retQueue = &dmaMesgQ;
    osInvalDCache(buf_ptr, size);

    while (size) {
        if (size > 0x200) {
            readSize = 0x200;
        } else {
            readSize = size;
        }
        dmaIoMesgBuf.dramAddr = buf_ptr;
        dmaIoMesgBuf.devAddr = rom_addr;
        dmaIoMesgBuf.size = readSize;
        func_8008BC40(D_800E7A20, &dmaIoMesgBuf, 0);
        osRecvMesg(&dmaMesgQ, &dmaMesgBuf, 1);
        rom_addr += readSize;
        buf_ptr = (u8 *)buf_ptr + readSize;
        size -= readSize;
    }
}

/* nuPiInitSram */
void func_8008A040(void) {
    if (nuPiSramHandleBody.baseAddress == 0xA8000000) {
        return;
    }
    nuPiSramHandleBody.type = 3;
    nuPiSramHandleBody.baseAddress = 0xA8000000;
    nuPiSramHandleBody.latency = 5;
    nuPiSramHandleBody.pulse = 0xC;
    nuPiSramHandleBody.pageSize = 0xD;
    nuPiSramHandleBody.relDuration = 2;
    nuPiSramHandleBody.domain = 1;
    nuPiSramHandleBody.speed = 0;
    bzero(&nuPiSramHandleBody.transferInfo, sizeof(nuPiSramHandleBody.transferInfo));
    osEPiLinkHandle(&nuPiSramHandleBody);
    D_800E79AC = &nuPiSramHandleBody;
}
