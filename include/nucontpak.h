#ifndef NUCONTPAK_H
#define NUCONTPAK_H

#include "nusys.h"

typedef struct {
    /* 0x00 */ OSPfs *pfs;
    /* 0x04 */ s32 file_no;
    /* 0x08 */ s32 error;
    /* 0x0C */ u32 type;
} NUContPakFile;

typedef struct {
    /* 0x00 */ NUContPakFile *file;
    /* 0x04 */ s32 size;
} NUContPakFreeMesg;

typedef struct {
    /* 0x00 */ NUContPakFile *file;
    /* 0x04 */ u8 *noteName;
    /* 0x08 */ u8 *extName;
    /* 0x0C */ s32 size;
    /* 0x10 */ s32 mode;
} NUContPakFileOpenMesg;

typedef struct {
    /* 0x00 */ NUContPakFile *file;
    /* 0x04 */ s32 offset;
    /* 0x08 */ s32 size;
    /* 0x0C */ u8 mode;
    /* 0x10 */ u8 *buf;
} NUContPakFileRWMesg;

typedef struct {
    /* 0x00 */ NUContPakFile *file;
    /* 0x04 */ void *state;
} NUContPakFileStateMesg;

typedef struct {
    /* 0x00 */ NUContPakFile *file;
    /* 0x04 */ s32 *max_files;
    /* 0x08 */ s32 *used_files;
} NUContPakFileNumMesg;

#endif
