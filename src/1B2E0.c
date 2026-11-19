#include "common.h"
#include "nucontpak.h"

/* NuSystem nucontpakfiledelete.c */

/* nuContPakFileDelete */
void func_8008AEE0(NUContPakFile *file, u8 *noteName, u8 *extName) {
    NUContPakFileOpenMesg delMesg;

    delMesg.file = file;
    delMesg.noteName = noteName;
    delMesg.extName = extName;
    file->error = func_80089CF8(0x205, &delMesg); /* NU_CONT_PAK_FILEDELETE_MSG */
}
