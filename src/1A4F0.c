#include "common.h"

/* NuSystem: one cartridge DMA in either direction */

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
    /* 0x00 */ u16 type;
    /* 0x02 */ u8 pri;
    /* 0x03 */ u8 status;
    /* 0x04 */ OSMesgQueue *retQueue;
    /* 0x08 */ void *dramAddr;
    /* 0x0C */ u32 devAddr;
    /* 0x10 */ u32 size;
    /* 0x14 */ void *piHandle;
} OSIoMesg;

extern void *D_800E79AC; /* nuPiCartHandle */

void osCreateMesgQueue(OSMesgQueue *mq, OSMesg *msg, s32 count);
s32 osRecvMesg(OSMesgQueue *mq, OSMesg *msg, s32 flag);
void osInvalDCache(void *addr, s32 size);
void osWritebackDCache(void *addr, s32 size);
s32 func_8008BC40(void *handle, OSIoMesg *mb, s32 direction); /* osEPiStartDma */

/* nuPiReadWriteRom */
void func_8008A0F0(u32 rom_addr, void *buf_ptr, u32 size, s32 direction) {
    OSIoMesg dmaIoMesgBuf;
    OSMesgQueue dmaMesgQ;
    OSMesg dmaMesgBuf;

    osCreateMesgQueue(&dmaMesgQ, &dmaMesgBuf, 1);
    dmaIoMesgBuf.pri = 0; /* OS_MESG_PRI_NORMAL */
    dmaIoMesgBuf.retQueue = &dmaMesgQ;
    dmaIoMesgBuf.dramAddr = buf_ptr;
    dmaIoMesgBuf.devAddr = rom_addr;
    dmaIoMesgBuf.size = size;
    if (direction == 0) { /* OS_READ */
        osInvalDCache(buf_ptr, size);
    } else {
        osWritebackDCache(buf_ptr, size);
    }
    func_8008BC40(D_800E79AC, &dmaIoMesgBuf, direction);
    osRecvMesg(&dmaMesgQ, &dmaMesgBuf, 1);
}
