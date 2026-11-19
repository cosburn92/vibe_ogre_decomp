#include "common.h"
#include "nucontpak.h"

/* NuSystem nucontpakrepairid.c, nucontpakfileopen.c */

void _bcopy(const void *src, void *dst, s32 len);
void bzero(void *p, s32 n);

/* nuContPakRepairId */
void func_8008AC70(NUContPakFile *file) {
    file->error = func_80089CF8(0x208, file); /* NU_CONT_PAK_REPAIRID_MSG */
}

/* nuContPakFileOpen */
#ifdef NON_MATCHING
/* s0/s1 hold the two name buffers the other way round */
void func_8008ACA0(NUContPakFile *file, u8 *noteName, u8 *extName, u32 mode, s32 size) {
    NUContPakFileOpenMesg openMesg;
    u8 noteNameBuf[16];
    u8 extNameBuf[4];

    if (file->type != 0) {
        _bcopy(noteName, noteNameBuf, 16);
        bzero(extNameBuf, 4);
        extNameBuf[0] = extName[0];
        openMesg.file = file;
        openMesg.noteName = noteNameBuf;
        openMesg.extName = extNameBuf;
        openMesg.size = size;
        openMesg.mode = mode;
        file->error = func_80089CF8(0x203, &openMesg); /* NU_CONT_PAK_FOPEN_MSG */
    } else {
        file->error = 1; /* PFS_ERR_NOPACK */
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/1B070", func_8008ACA0);
#endif
