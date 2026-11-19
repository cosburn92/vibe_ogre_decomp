#include "common.h"
#include "nucontpak.h"

/* NuSystem nucontpakfilestate.c */

/* nuContPakFileState */
void func_8008AF20(NUContPakFile *file, void *state) {
    NUContPakFileStateMesg stateMesg;

    stateMesg.file = file;
    stateMesg.state = state;
    file->error = func_80089CF8(0x206, &stateMesg); /* NU_CONT_PAK_FILESTATE_MSG */
}
