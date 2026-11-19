#ifndef LIBULTRA_H
#define LIBULTRA_H

/* libultra types and declarations (layouts from the public SDK headers) */

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

#define OS_MESG_NOBLOCK 0
#define OS_MESG_BLOCK 1

void osCreateMesgQueue(OSMesgQueue *mq, OSMesg *msg, s32 count);
s32 osSendMesg(OSMesgQueue *mq, OSMesg msg, s32 flag);
s32 osRecvMesg(OSMesgQueue *mq, OSMesg *msg, s32 flag);
void osCreateThread(OSThread *t, s32 id, void (*entry)(void *), void *arg, void *sp, s32 pri);
void osStartThread(OSThread *t);
void osStopThread(OSThread *t);

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
    /* 0x14 */ struct OSPiHandle_s *piHandle;
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
    /* 0x00 */ s32 active;
    /* 0x04 */ OSThread *thread;
    /* 0x08 */ OSMesgQueue *cmdQueue;
    /* 0x0C */ OSMesgQueue *evtQueue;
    /* 0x10 */ OSMesgQueue *acsQueue;
    /* 0x14 */ s32 (*dma)(s32, u32, void *, u32);
    /* 0x18 */ s32 (*edma)(OSPiHandle *, s32, u32, void *, u32);
} OSDevMgr;

#define OS_READ 0
#define OS_WRITE 1
#define OS_MESG_PRI_NORMAL 0
#define OS_MESG_PRI_HIGH 1
#define OS_MESG_TYPE_DMAREAD 11
#define OS_MESG_TYPE_DMAWRITE 12
#define OS_MESG_TYPE_EDMAREAD 15
#define OS_MESG_TYPE_EDMAWRITE 16

#define PHYS_TO_K1(x) ((u32)(x) | 0xA0000000)
#define IO_READ(addr) (*(vu32 *)PHYS_TO_K1(addr))
#define IO_WRITE(addr, data) (*(vu32 *)PHYS_TO_K1(addr) = (u32)(data))

#define PI_BASE_REG 0x04600000
#define PI_DRAM_ADDR_REG (PI_BASE_REG + 0x00)
#define PI_CART_ADDR_REG (PI_BASE_REG + 0x04)
#define PI_RD_LEN_REG (PI_BASE_REG + 0x08)
#define PI_WR_LEN_REG (PI_BASE_REG + 0x0C)
#define PI_STATUS_REG (PI_BASE_REG + 0x10)
#define PI_BSD_DOM1_LAT_REG (PI_BASE_REG + 0x14)
#define PI_BSD_DOM1_PWD_REG (PI_BASE_REG + 0x18)
#define PI_BSD_DOM1_PGS_REG (PI_BASE_REG + 0x1C)
#define PI_BSD_DOM1_RLS_REG (PI_BASE_REG + 0x20)
#define PI_BSD_DOM2_LAT_REG (PI_BASE_REG + 0x24)
#define PI_BSD_DOM2_PWD_REG (PI_BASE_REG + 0x28)
#define PI_BSD_DOM2_PGS_REG (PI_BASE_REG + 0x2C)
#define PI_BSD_DOM2_RLS_REG (PI_BASE_REG + 0x30)
#define PI_STATUS_DMA_BUSY 0x01
#define PI_STATUS_IO_BUSY 0x02
#define PI_DOMAIN1 0
#define PI_DOMAIN2 1
#define K1_TO_PHYS(x) ((u32)(x) & 0x1FFFFFFF)

#define WAIT_ON_IOBUSY(stat)                                              stat = IO_READ(PI_STATUS_REG);                                        while (stat & (PI_STATUS_IO_BUSY | PI_STATUS_DMA_BUSY))                   stat = IO_READ(PI_STATUS_REG);

#define AI_BASE_REG 0x04500000
#define AI_DRAM_ADDR_REG (AI_BASE_REG + 0x00)
#define AI_LEN_REG (AI_BASE_REG + 0x04)
#define AI_CONTROL_REG (AI_BASE_REG + 0x08)
#define AI_STATUS_REG (AI_BASE_REG + 0x0C)
#define AI_DACRATE_REG (AI_BASE_REG + 0x10)
#define AI_BITRATE_REG (AI_BASE_REG + 0x14)

u32 __osDisableInt(void);
void __osRestoreInt(u32 mask);
s32 osJamMesg(OSMesgQueue *mq, OSMesg msg, s32 flag);
OSMesgQueue *osPiGetCmdQueue(void);
u32 osVirtualToPhysical(void *addr);

#endif
