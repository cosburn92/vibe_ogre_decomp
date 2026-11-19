#ifndef LIBULTRA_H
#define LIBULTRA_H

/* libultra types and declarations (layouts from the public SDK headers) */

typedef void *OSMesg;

typedef struct {
    /* 0x00 */ struct OSThread_s *mtqueue;
    /* 0x04 */ struct OSThread_s *fullqueue;
    /* 0x08 */ s32 validCount;
    /* 0x0C */ s32 first;
    /* 0x10 */ s32 msgCount;
    /* 0x14 */ OSMesg *msg;
} OSMesgQueue;

typedef struct {
    /* 0x000 */ u64 at, v0, v1, a0, a1, a2, a3;
    /* 0x038 */ u64 t0, t1, t2, t3, t4, t5, t6, t7;
    /* 0x078 */ u64 s0, s1, s2, s3, s4, s5, s6, s7;
    /* 0x0B8 */ u64 t8, t9, gp, sp, s8, ra;
    /* 0x0E8 */ u64 lo, hi;
    /* 0x0F8 */ u32 sr, pc, cause, badvaddr, rcp;
    /* 0x10C */ u32 fpcsr;
    /* 0x110 */ u64 fp[16];
} __OSThreadContext; /* size 0x190 */

typedef struct OSThread_s {
    /* 0x00 */ struct OSThread_s *next;
    /* 0x04 */ s32 priority;
    /* 0x08 */ struct OSThread_s **queue;
    /* 0x0C */ struct OSThread_s *tlnext;
    /* 0x10 */ u16 state;
    /* 0x12 */ u16 flags;
    /* 0x14 */ s32 id;
    /* 0x18 */ s32 fp;
    /* 0x20 */ __OSThreadContext context;
} OSThread; /* size 0x1B0 */

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

#define EPI_SYNC(pihandle, stat, domain)                                           \
    WAIT_ON_IOBUSY(stat);                                                          \
    domain = pihandle->domain;                                                     \
    if (__osCurrentHandle[domain]->type != pihandle->type) {                       \
        OSPiHandle *cHandle = __osCurrentHandle[domain];                           \
        if (domain == PI_DOMAIN1) {                                                \
            if (cHandle->latency != pihandle->latency) {                           \
                IO_WRITE(PI_BSD_DOM1_LAT_REG, pihandle->latency);                  \
            }                                                                      \
            if (cHandle->pageSize != pihandle->pageSize) {                         \
                IO_WRITE(PI_BSD_DOM1_PGS_REG, pihandle->pageSize);                 \
            }                                                                      \
            if (cHandle->relDuration != pihandle->relDuration) {                   \
                IO_WRITE(PI_BSD_DOM1_RLS_REG, pihandle->relDuration);              \
            }                                                                      \
            if (cHandle->pulse != pihandle->pulse) {                               \
                IO_WRITE(PI_BSD_DOM1_PWD_REG, pihandle->pulse);                    \
            }                                                                      \
        } else {                                                                   \
            if (cHandle->latency != pihandle->latency) {                           \
                IO_WRITE(PI_BSD_DOM2_LAT_REG, pihandle->latency);                  \
            }                                                                      \
            if (cHandle->pageSize != pihandle->pageSize) {                         \
                IO_WRITE(PI_BSD_DOM2_PGS_REG, pihandle->pageSize);                 \
            }                                                                      \
            if (cHandle->relDuration != pihandle->relDuration) {                   \
                IO_WRITE(PI_BSD_DOM2_RLS_REG, pihandle->relDuration);              \
            }                                                                      \
            if (cHandle->pulse != pihandle->pulse) {                               \
                IO_WRITE(PI_BSD_DOM2_PWD_REG, pihandle->pulse);                    \
            }                                                                      \
        }                                                                          \
        cHandle->type = pihandle->type;                                            \
        cHandle->latency = pihandle->latency;                                      \
        cHandle->pageSize = pihandle->pageSize;                                    \
        cHandle->relDuration = pihandle->relDuration;                              \
        cHandle->pulse = pihandle->pulse;                                          \
    }

#define AI_BASE_REG 0x04500000
#define AI_DRAM_ADDR_REG (AI_BASE_REG + 0x00)
#define AI_LEN_REG (AI_BASE_REG + 0x04)
#define AI_CONTROL_REG (AI_BASE_REG + 0x08)
#define AI_STATUS_REG (AI_BASE_REG + 0x0C)
#define AI_DACRATE_REG (AI_BASE_REG + 0x10)
#define AI_BITRATE_REG (AI_BASE_REG + 0x14)

typedef u64 OSTime;


#define OS_STATE_STOPPED 1
#define OS_STATE_RUNNABLE 2
#define OS_STATE_RUNNING 4
#define OS_STATE_WAITING 8

#define MQ_IS_EMPTY(mq) ((mq)->validCount == 0)
#define MQ_IS_FULL(mq) ((mq)->validCount >= (mq)->msgCount)

#define va_list char *
#define va_start(AP, LASTARG) (AP = ((char *)__builtin_next_arg(LASTARG)))
#define va_end(AP)

typedef struct OSTimer_s {
    /* 0x00 */ struct OSTimer_s *next;
    /* 0x04 */ struct OSTimer_s *prev;
    /* 0x08 */ OSTime interval;
    /* 0x10 */ OSTime value;
    /* 0x18 */ OSMesgQueue *mq;
    /* 0x1C */ OSMesg msg;
} OSTimer;

typedef struct {
    /* 0x00 */ u32 ramarray[15];
    /* 0x3C */ u32 pifstatus;
} OSPifRam;

typedef struct {
    /* 0x00 */ u8 dummy;
    /* 0x01 */ u8 txsize;
    /* 0x02 */ u8 rxsize;
    /* 0x03 */ u8 cmd;
    /* 0x04 */ u16 button;
    /* 0x06 */ s8 stick_x;
    /* 0x07 */ s8 stick_y;
} __OSContReadFormat;

typedef struct {
    /* 0x00 */ u8 dummy;
    /* 0x01 */ u8 txsize;
    /* 0x02 */ u8 rxsize;
    /* 0x03 */ u8 cmd;
    /* 0x04 */ u8 typeh;
    /* 0x05 */ u8 typel;
    /* 0x06 */ u8 status;
    /* 0x07 */ u8 dummy1;
} __OSContRequesFormat;

#define CHNL_ERR_MASK 0xC0
#define CHNL_ERR(format) (((format).rxsize & CHNL_ERR_MASK) >> 4)
#define CONT_CMD_REQUEST_STATUS 0
#define CONT_CMD_READ_BUTTON 1
#define CONT_CMD_REQUEST_STATUS_TX 1
#define CONT_CMD_REQUEST_STATUS_RX 3
#define CONT_CMD_READ_BUTTON_TX 1
#define CONT_CMD_READ_BUTTON_RX 4
#define CONT_CMD_EXE 1
#define CONT_CMD_NOP 0xFF
#define CONT_CMD_END 0xFE
#define MAXCONTROLLERS 4

extern OSPifRam __osContPifRam_800C4A20; /* __osContPifRam */
extern u8 __osContLastCmd;
extern u8 __osMaxControllers;

s32 __osSiRawStartDma(s32 direction, void *dramAddr);
void __osSiGetAccess(void);
void __osSiRelAccess(void);
void __osSiCreateAccessQueue(void);
OSTime osGetTime(void);
s32 osSetTimer(OSTimer *t, OSTime value, OSTime interval, OSMesgQueue *mq, OSMesg msg);

typedef struct {
    /* 0x00 */ u32 ctrl;
    /* 0x04 */ u32 width;
    /* 0x08 */ u32 burst;
    /* 0x0C */ u32 vSync;
    /* 0x10 */ u32 hSync;
    /* 0x14 */ u32 leap;
    /* 0x18 */ u32 hStart;
    /* 0x1C */ u32 xScale;
    /* 0x20 */ u32 vCurrent;
} OSViCommonRegs;

typedef struct {
    /* 0x00 */ u32 origin;
    /* 0x04 */ u32 yScale;
    /* 0x08 */ u32 vStart;
    /* 0x0C */ u32 vBurst;
    /* 0x10 */ u32 vIntr;
} OSViFieldRegs;

typedef struct {
    /* 0x00 */ u8 type;
    /* 0x04 */ OSViCommonRegs comRegs;
    /* 0x28 */ OSViFieldRegs fldRegs[2];
} OSViMode;

typedef struct {
    /* 0x00 */ f32 factor;
    /* 0x04 */ u16 offset;
    /* 0x08 */ u32 scale;
} __OSViScale;

typedef struct {
    /* 0x00 */ u16 state;
    /* 0x02 */ u16 retraceCount;
    /* 0x04 */ void *framep;
    /* 0x08 */ OSViMode *modep;
    /* 0x0C */ u32 control;
    /* 0x10 */ OSMesgQueue *msgq;
    /* 0x14 */ OSMesg msg;
    /* 0x18 */ __OSViScale x;
    /* 0x24 */ __OSViScale y;
} __OSViContext;

#define VI_STATE_MODE_UPDATED 0x01
#define VI_STATE_XSCALE_UPDATED 0x02
#define VI_STATE_YSCALE_UPDATED 0x04
#define VI_STATE_CTRL_UPDATED 0x08
#define VI_STATE_BUFFER_UPDATED 0x10
#define VI_STATE_BLACK 0x20
#define VI_STATE_REPEATLINE 0x40
#define VI_STATE_FADE 0x80

extern __OSViContext *__osViCurr;
extern __OSViContext *__osViNext;

u32 __osDisableInt(void);
void __osRestoreInt(u32 mask);
s32 osJamMesg(OSMesgQueue *mq, OSMesg msg, s32 flag);
OSMesgQueue *osPiGetCmdQueue(void);
u32 osVirtualToPhysical(void *addr);

#endif
