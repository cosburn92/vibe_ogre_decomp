#include "common.h"
#include "libultra.h"

/* libultra epirawwrite.c */

extern OSPiHandle *__osCurrentHandle[2];

s32 osEPiRawWriteIo(OSPiHandle *pihandle, u32 devAddr, u32 data) {
    register u32 stat;
    register u32 domain;

    EPI_SYNC(pihandle, stat, domain);
    IO_WRITE(pihandle->baseAddress | devAddr, data);
    return 0;
}
