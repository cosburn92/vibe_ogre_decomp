#include "common.h"
#include "libultra.h"

/* libultra sirawdma.c */

#define SI_DRAM_ADDR_REG 0x04800000
#define SI_PIF_ADDR_RD64B_REG 0x04800004
#define SI_PIF_ADDR_WR64B_REG 0x04800010
#define SI_STATUS_REG 0x04800018
#define SI_STATUS_DMA_BUSY 0x0001
#define SI_STATUS_RD_BUSY 0x0002
#define PIF_RAM_START 0x1FC007C0

void osWritebackDCache(void *vaddr, s32 nbytes);
void osInvalDCache(void *vaddr, s32 nbytes);

s32 __osSiRawStartDma(s32 direction, void *dramAddr) {
    if (IO_READ(SI_STATUS_REG) & (SI_STATUS_DMA_BUSY | SI_STATUS_RD_BUSY)) {
        return -1;
    }
    if (direction == OS_WRITE) {
        osWritebackDCache(dramAddr, 64);
    }
    IO_WRITE(SI_DRAM_ADDR_REG, osVirtualToPhysical(dramAddr));
    if (direction == OS_READ) {
        IO_WRITE(SI_PIF_ADDR_RD64B_REG, PIF_RAM_START);
    } else {
        IO_WRITE(SI_PIF_ADDR_WR64B_REG, PIF_RAM_START);
    }
    if (direction == OS_READ) {
        osInvalDCache(dramAddr, 64);
    }
    return 0;
}
