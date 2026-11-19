#include "common.h"
#include "nucontpak.h"

/* NuSystem nucontpakfilereadwrite.c */

/* nuContPakFileReadWrite */
void func_8008AE90(NUContPakFile *file, s32 offset, s32 size, u8 *buf, u32 mode) {
    NUContPakFileRWMesg rwMesg;

    rwMesg.file = file;
    rwMesg.offset = offset;
    rwMesg.size = size;
    rwMesg.mode = mode;
    rwMesg.buf = buf;
    file->error = func_80089CF8(0x204, &rwMesg); /* NU_CONT_PAK_READWRITE_MSG */
}
