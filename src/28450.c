#include "common.h"
#include "libultra.h"

/* libultra initialize.c */

typedef struct {
    u32 inst1, inst2, inst3, inst4;
} __osExceptionVector;

extern __osExceptionVector __osException[];
extern u64 osClockRate;
extern s32 osViClock;
extern u32 __osFinalrom;
extern s32 osResetType;
extern s32 osTvType;
extern u8 osAppNMIBuffer[64];
extern OSPiHandle __Dom1SpeedParam;
extern OSPiHandle __Dom2SpeedParam;

u32 __osGetSR(void);
void __osSetSR(u32 v);
void __osSetFpcCsr(u32 v);
void __osSetWatchLo(u32 v);
s32 __osSiRawReadIo(u32 devAddr, u32 *data);
s32 __osSiRawWriteIo(u32 devAddr, u32 data);
void osWritebackDCache(void *vaddr, s32 nbytes);
void osInvalICache(void *vaddr, s32 nbytes);
void osUnmapTLBAll(void);
void osMapTLBRdb(void);
u32 __osGetCause(void);
void bzero(void *p, s32 n);
void createSpeedParam(void);

#define UT_VEC 0x80000000
#define XUT_VEC 0x80000080
#define ECC_VEC 0x80000100
#define E_VEC 0x80000180

void osInitialize(void) {
    u32 pifdata;

    __osFinalrom = 1;
    __osSetSR(__osGetSR() | 0x20000000); /* SR_CU1 */
    __osSetFpcCsr(0x01000000 | 0x00000800); /* FPCSR_FS | FPCSR_EV */
    __osSetWatchLo(0x04900000);
    while (__osSiRawReadIo(0x1FC007FC, &pifdata)) { /* PIF_RAM_END - 3 */
    }
    while (__osSiRawWriteIo(0x1FC007FC, pifdata | 8)) {
    }
    *(__osExceptionVector *)UT_VEC = *__osException;
    *(__osExceptionVector *)XUT_VEC = *__osException;
    *(__osExceptionVector *)ECC_VEC = *__osException;
    *(__osExceptionVector *)E_VEC = *__osException;
    osWritebackDCache((void *)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
    osInvalICache((void *)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
    createSpeedParam();
    osUnmapTLBAll();
    osMapTLBRdb();
    osClockRate = osClockRate * 3 / 4;
    if (osResetType == 0) {
        bzero(osAppNMIBuffer, 64);
    }
    if (osTvType == 0) { /* OS_TV_PAL */
        osViClock = 49656530;
    } else if (osTvType == 2) { /* OS_TV_MPAL */
        osViClock = 48628316;
    } else {
        osViClock = 48681812;
    }
    if (__osGetCause() & 0x1000) { /* CAUSE_IP5 */
        while (1) {
        }
    }
    IO_WRITE(AI_CONTROL_REG, 1);    /* AI_CONTROL_DMA_ON */
    IO_WRITE(AI_DACRATE_REG, 0x3FFF); /* AI_MAX_DAC_RATE - 1 */
    IO_WRITE(AI_BITRATE_REG, 0xF);    /* AI_MAX_BIT_RATE - 1 */
}

void createSpeedParam(void) {
    __Dom1SpeedParam.type = 7; /* DEVICE_TYPE_INIT */
    __Dom1SpeedParam.latency = IO_READ(PI_BSD_DOM1_LAT_REG);
    __Dom1SpeedParam.pulse = IO_READ(PI_BSD_DOM1_PWD_REG);
    __Dom1SpeedParam.pageSize = IO_READ(PI_BSD_DOM1_PGS_REG);
    __Dom1SpeedParam.relDuration = IO_READ(PI_BSD_DOM1_RLS_REG);

    __Dom2SpeedParam.type = 7;
    __Dom2SpeedParam.latency = IO_READ(PI_BSD_DOM2_LAT_REG);
    __Dom2SpeedParam.pulse = IO_READ(PI_BSD_DOM2_PWD_REG);
    __Dom2SpeedParam.pageSize = IO_READ(PI_BSD_DOM2_PGS_REG);
    __Dom2SpeedParam.relDuration = IO_READ(PI_BSD_DOM2_RLS_REG);
}
