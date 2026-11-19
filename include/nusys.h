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
    long long force_structure_alignment;
} OSTask;

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
