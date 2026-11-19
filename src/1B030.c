#include "common.h"
#include "nucontpak.h"

/* NuSystem nucontpakgetfree.c */

/* nuContPakGetFree */
s32 func_8008AC30(NUContPakFile *file) {
    NUContPakFreeMesg freeMesg;

    freeMesg.file = file;
    file->error = func_80089CF8(0x202, &freeMesg); /* NU_CONT_PAK_FREE_MSG */
    return freeMesg.size;
}
