#ifndef NUSYS_H
#define NUSYS_H

/* The libultra and NuSystem types the nusys files use (layouts from the public SDK headers). */

#include "libultra.h"

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

s32 func_80089CF8(NUScMsg mesg, void *dataPtr); /* nuSiSendMesg */

#endif
