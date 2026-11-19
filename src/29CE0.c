#include "common.h"
#include "libultra.h"

/* libultra epirawread.c */

extern OSPiHandle *__osCurrentHandle[2];

s32 osEPiRawReadIo(OSPiHandle *pihandle, u32 devAddr, u32 *data) {
    register u32 stat;
    register u32 domain;

    EPI_SYNC(pihandle, stat, domain);
    *data = IO_READ(pihandle->baseAddress | devAddr);
    return 0;
}
