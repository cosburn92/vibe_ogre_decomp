#include "common.h"
#include "nusys.h"

/* NuSystem nucontpakmgr.c */

typedef struct {
    /* 0x00 */ s32 status;
    /* 0x04 */ OSMesgQueue *queue;
    /* 0x08 */ s32 channel;
    /* 0x0C */ u8 id[32];
    /* 0x2C */ s32 version;
    /* 0x30 */ s32 dir_size;
    /* 0x34 */ s32 inode_table;
    /* 0x38 */ s32 minode_table;
    /* 0x3C */ s32 dir_table;
    /* 0x40 */ s32 inode_start_page;
    /* 0x44 */ u8 banks;
    /* 0x45 */ u8 activebank;
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

extern OSMesgQueue D_800E9B88;       /* nuSiMesgQ */
extern NUCallBackList D_800AA040;    /* nuContPakCallBack */
extern u16 D_800AA010;               /* nuContPakCompanyCode */
extern u32 D_800AA014;               /* nuContPakGameCode */

void func_8008B130(NUCallBackList *list); /* nuSiCallBackAdd */
void func_8008B1D0(NUCallBackList *list); /* nuSiCallBackRemove */
s32 osPfsInitPak(OSMesgQueue *queue, OSPfs *pfs, s32 channel);
s32 osPfsFreeBlocks(OSPfs *pfs, s32 *bytes_not_used);
s32 osPfsReadWriteFile(OSPfs *pfs, s32 file_no, u8 flag, s32 offset, s32 size, u8 *data_buffer);
s32 osPfsFindFile(OSPfs *pfs, u16 company_code, u32 game_code, u8 *game_name, u8 *ext_name, s32 *file_no);
s32 osPfsAllocateFile(OSPfs *pfs, u16 company_code, u32 game_code, u8 *game_name, u8 *ext_name, s32 file_size_in_bytes, s32 *file_no);
s32 osPfsDeleteFile(OSPfs *pfs, u16 company_code, u32 game_code, u8 *game_name, u8 *ext_name);
s32 osPfsFileState(OSPfs *pfs, s32 file_no, void *state);
s32 osPfsNumFiles(OSPfs *pfs, s32 *max_files, s32 *files_used);
s32 osPfsRepairId(OSPfs *pfs);

/* nuContPakMgrInit */
void func_8008A6A0(void) {
    func_8008B130(&D_800AA040);
}

/* nuContPakMgrRemove */
void func_8008A6C0(void) {
    func_8008B1D0(&D_800AA040);
}

/* contPakOpen */
s32 func_8008A6E0(NUSiCommonMesg *mesg) {
    s32 rtn;
    NUContPakFile *file;

    file = (NUContPakFile *)mesg->dataPtr;
    file->type = 0; /* NU_CONT_PAK_TYPE_NONE */
    rtn = osPfsInitPak(&D_800E9B88, file->pfs, file->pfs->channel);
    if (!rtn) {
        file->type = 1; /* NU_CONT_PAK_TYPE_PAK */
    }
    return rtn;
}

/* contPakFree */
s32 func_8008A730(NUSiCommonMesg *mesg) {
    NUContPakFreeMesg *freeMesg;

    freeMesg = (NUContPakFreeMesg *)mesg->dataPtr;
    return osPfsFreeBlocks(freeMesg->file->pfs, &freeMesg->size);
}

/* contPakFileReadWrite */
s32 func_8008A758(NUSiCommonMesg *mesg) {
    NUContPakFileRWMesg *rwMesg;

    rwMesg = (NUContPakFileRWMesg *)mesg->dataPtr;
    return osPfsReadWriteFile(rwMesg->file->pfs, rwMesg->file->file_no, rwMesg->mode, rwMesg->offset,
                              rwMesg->size, rwMesg->buf);
}

/* contPakFileOpen */
s32 func_8008A798(NUSiCommonMesg *mesg) {
    NUContPakFileOpenMesg *openMesg;
    NUContPakFile *file;
    s32 rtn;

    openMesg = (NUContPakFileOpenMesg *)mesg->dataPtr;
    file = openMesg->file;
    rtn = osPfsFindFile(file->pfs, D_800AA010, D_800AA014, openMesg->noteName, openMesg->extName,
                        &file->file_no);
    if ((rtn == 5) && (openMesg->mode == 1)) { /* PFS_ERR_INVALID, NU_CONT_PAK_MODE_CREATE */
        rtn = osPfsAllocateFile(file->pfs, D_800AA010, D_800AA014, openMesg->noteName, openMesg->extName,
                                openMesg->size, &file->file_no);
    }
    return rtn;
}

/* contPakFileDelete */
s32 func_8008A850(NUSiCommonMesg *mesg) {
    NUContPakFileOpenMesg *delMesg;

    delMesg = (NUContPakFileOpenMesg *)mesg->dataPtr;
    return osPfsDeleteFile(delMesg->file->pfs, D_800AA010, D_800AA014, delMesg->noteName, delMesg->extName);
}

/* contPakFileState */
s32 func_8008A890(NUSiCommonMesg *mesg) {
    NUContPakFileStateMesg *stateMesg;

    stateMesg = (NUContPakFileStateMesg *)mesg->dataPtr;
    return osPfsFileState(stateMesg->file->pfs, stateMesg->file->file_no, stateMesg->state);
}

/* contPakFileNum */
s32 func_8008A8BC(NUSiCommonMesg *mesg) {
    NUContPakFileNumMesg *numMesg;

    numMesg = (NUContPakFileNumMesg *)mesg->dataPtr;
    return osPfsNumFiles(numMesg->file->pfs, numMesg->max_files, numMesg->used_files);
}

/* contPakRepairId */
s32 func_8008A8E8(NUSiCommonMesg *mesg) {
    NUContPakFile *file;

    file = (NUContPakFile *)mesg->dataPtr;
    return osPfsRepairId(file->pfs);
}
