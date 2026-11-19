#ifndef NUCONTPAK_H
#define NUCONTPAK_H

#include "nusys.h"

typedef struct {
    /* 0x00 */ s32 status;
    /* 0x04 */ OSMesgQueue *queue;
    /* 0x08 */ s32 channel;
    /* 0x0C */ u8 id[32];
    /* 0x2C */ u8 label[32];
    /* 0x4C */ s32 version;
    /* 0x50 */ s32 dir_size;
    /* 0x54 */ s32 inode_table;
    /* 0x58 */ s32 minode_table;
    /* 0x5C */ s32 dir_table;
    /* 0x60 */ s32 inode_start_page;
    /* 0x64 */ u8 banks;
    /* 0x65 */ u8 activebank;
} OSPfs;

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
