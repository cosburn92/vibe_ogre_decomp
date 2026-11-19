#include "common.h"
#include "libultra.h"

/* libultra pfsfilestate.c */

void _bcopy(const void *src, void *dst, s32 len);

s32 osPfsFileState(OSPfs *pfs, s32 file_no, OSPfsState *state) {
    s32 ret;
    __OSInode inode;
    __OSDir dir;
    __OSInodeUnit last_page;
    u8 bank;
    int pages;

    if ((file_no >= pfs->dir_size) || (file_no < 0)) {
        return PFS_ERR_INVALID;
    }
    PFS_CHECK_STATUS;
    PFS_CHECK_ID;
    SET_ACTIVEBANK_TO_ZERO;
    ERRCK(__osContRamRead(pfs->queue, pfs->channel, pfs->dir_table + file_no, (u8 *)&dir));
    if ((dir.company_code == 0) || (dir.game_code == 0)) {
        return PFS_ERR_INVALID;
    }
    pages = 0;
    last_page = dir.start_page;
    bank = 0xFF;
    while (1) {
        if (last_page.ipage < pfs->inode_start_page) {
            break;
        }
        if (last_page.inode_t.bank != bank) {
            bank = last_page.inode_t.bank;
            ERRCK(__osPfsRWInode(pfs, &inode, PFS_READ, bank));
        }
        pages++;
        last_page = inode.inode_page[last_page.inode_t.page];
    }
    if (last_page.ipage != PFS_EOF) {
        return PFS_ERR_INCONSISTENT;
    }
    state->file_size = pages * BLOCKSIZE * PFS_ONE_PAGE;
    state->company_code = dir.company_code;
    state->game_code = dir.game_code;
    _bcopy(&dir.game_name, state->game_name, PFS_FILE_NAME_LEN);
    _bcopy(&dir.ext_name, state->ext_name, PFS_FILE_EXT_LEN);
    return __osPfsGetStatus(pfs->queue, pfs->channel);
}
