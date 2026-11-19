#include "common.h"
#include "nucontpak.h"

/* NuSystem nucontpakfileopenjis.c */

void bzero(void *p, s32 n);
void func_8008A910(u8 *jis, u8 *n64, u32 len); /* nuContPakJisToN64 */
void func_8008ACA0(NUContPakFile *file, u8 *noteName, u8 *extName, u32 mode, s32 size); /* nuContPakFileOpen */

/* nuContPakFileOpenJis */
void func_8008AD60(NUContPakFile *file, u8 *noteName, u8 *extName, u32 mode, s32 size) {
    u8 noteNameN64[32];
    u8 extNameN64[4];
    u32 len;

    if (file->type == 0) {
        file->error = 1; /* PFS_ERR_NOPACK */
        return;
    }
    bzero(noteNameN64, 32);
    bzero(extNameN64, 4);
    for (len = 0; noteName[len] != 0; len++) {
    }
    func_8008A910(noteName, noteNameN64, len);
    func_8008A910(extName, extNameN64, 1);
    func_8008ACA0(file, noteNameN64, extNameN64, mode, size);
}
