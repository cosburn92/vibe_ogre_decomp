#include "common.h"
#include "libultra.h"

extern OSPiHandle __CartRomHandle;
extern OSPiHandle *__osPiTable;
extern s32 D_800AA430; /* first */

void __osPiGetAccess(void);
void __osPiRelAccess(void);
void bzero(void *p, s32 n);

OSPiHandle *osCartRomInit(void) {
    u32 value = 0;
    u32 saveMask;
    register u32 stat;
    u32 latency;
    u32 pulse;
    u32 pageSize;
    u32 relDuration;

    __osPiGetAccess();
    if (!D_800AA430) {
        __osPiRelAccess();
        return &__CartRomHandle;
    }
    D_800AA430 = 0;
    __CartRomHandle.type = 0; /* DEVICE_TYPE_CART */
    __CartRomHandle.baseAddress = 0xB0000000;
    __CartRomHandle.domain = PI_DOMAIN1;
    __CartRomHandle.speed = 0;
    bzero(&__CartRomHandle.transferInfo, sizeof(__OSTranxInfo));

    WAIT_ON_IOBUSY(stat);
    latency = IO_READ(PI_BSD_DOM1_LAT_REG);
    pageSize = IO_READ(PI_BSD_DOM1_PGS_REG);
    relDuration = IO_READ(PI_BSD_DOM1_RLS_REG);
    pulse = IO_READ(PI_BSD_DOM1_PWD_REG);

    IO_WRITE(PI_BSD_DOM1_LAT_REG, 0xFF);
    IO_WRITE(PI_BSD_DOM1_PGS_REG, 0);
    IO_WRITE(PI_BSD_DOM1_RLS_REG, 3);
    IO_WRITE(PI_BSD_DOM1_PWD_REG, 0xFF);

    value = IO_READ(__CartRomHandle.baseAddress);
    __CartRomHandle.latency = value & 0xFF;
    __CartRomHandle.pageSize = (value >> 16) & 0xF;
    __CartRomHandle.relDuration = (value >> 20) & 0xF;
    __CartRomHandle.pulse = (value >> 8) & 0xFF;

    IO_WRITE(PI_BSD_DOM1_LAT_REG, latency);
    IO_WRITE(PI_BSD_DOM1_PGS_REG, pageSize);
    IO_WRITE(PI_BSD_DOM1_RLS_REG, relDuration);
    IO_WRITE(PI_BSD_DOM1_PWD_REG, pulse);

    saveMask = __osDisableInt();
    __CartRomHandle.next = __osPiTable;
    __osPiTable = &__CartRomHandle;
    __osRestoreInt(saveMask);
    __osPiRelAccess();
    return &__CartRomHandle;
}
