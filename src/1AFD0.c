#include "common.h"
#include "nucontpak.h"

/* NuSystem nucontpakopen.c */

extern OSPfs D_800E99E8[4]; /* nuContPfs */

/* nuContPakOpen */
void func_8008ABD0(NUContPakFile *file, u32 contNo) {
    file->pfs = &D_800E99E8[contNo];
    file->pfs->channel = contNo;
    file->error = func_80089CF8(0x201, file); /* NU_CONT_PAK_OPEN_MSG */
}
