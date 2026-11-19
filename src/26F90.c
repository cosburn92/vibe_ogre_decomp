#include "common.h"
#include "libultra.h"

/* libultra pfsinitpak.c */

#define DEF_DIR_PAGES 2
#define PFS_ID_0AREA 1

typedef struct {
    /* 0x00 */ u32 repaired;
    /* 0x04 */ u32 random;
    /* 0x08 */ u64 serial_mid;
    /* 0x10 */ u64 serial_low;
    /* 0x18 */ u16 deviceid;
    /* 0x1A */ u8 banks;
    /* 0x1B */ u8 version;
    /* 0x1C */ u16 checksum;
    /* 0x1E */ u16 inverted_checksum;
} __OSPackId;

void _bcopy(const void *src, void *dst, s32 len);
s32 _bcmp(const void *a, const void *b, s32 len);
s32 __osIdCheckSum(u16 *ptr, u16 *csum, u16 *icsum);
s32 __osCheckPackId(OSPfs *pfs, __OSPackId *temp);
s32 __osRepairPackId(OSPfs *pfs, __OSPackId *badid, __OSPackId *newid);
s32 osPfsChecker(OSPfs *pfs);
s32 __osPfsCheckRamArea(OSPfs *pfs);

s32 osPfsInitPak(OSMesgQueue *queue, OSPfs *pfs, int channel) {
    s32 ret;
    u8 temp[32];
    __OSPackId newid;
    u16 sum;
    u16 isum;
    __OSPackId *id;

    __osSiGetAccess();
    ret = __osPfsGetStatus(queue, channel);
    __osSiRelAccess();
    if (ret != 0) {
        return ret;
    }
    pfs->queue = queue;
    pfs->channel = channel;
    pfs->status = 0;

    ERRCK(__osPfsCheckRamArea(pfs));
    ERRCK(__osPfsSelectBank(pfs, 0));
    ERRCK(__osContRamRead(pfs->queue, pfs->channel, PFS_ID_0AREA, temp));
    __osIdCheckSum((u16 *)temp, &sum, &isum);
    id = (__OSPackId *)temp;
    if ((id->checksum != sum) || (id->inverted_checksum != isum)) {
        ret = __osCheckPackId(pfs, id);
        if (ret != 0) {
            pfs->status |= PFS_ID_BROKEN;
            return ret;
        }
    }
    if ((id->deviceid & 0x01) == 0) {
        ret = __osRepairPackId(pfs, id, &newid);
        if (ret != 0) {
            if (ret == PFS_ERR_ID_FATAL) {
                pfs->status |= PFS_ID_BROKEN;
            }
            return ret;
        }
        id = &newid;
        if ((id->deviceid & 0x01) == 0) {
            return PFS_ERR_DEVICE;
        }
    }

    _bcopy(id, pfs->id, BLOCKSIZE);
    pfs->version = id->version;
    pfs->banks = id->banks;
    pfs->inode_start_page = 1 + DEF_DIR_PAGES + (2 * pfs->banks);
    pfs->dir_size = DEF_DIR_PAGES * PFS_ONE_PAGE;
    pfs->inode_table = 1 * PFS_ONE_PAGE;
    pfs->minode_table = (1 + pfs->banks) * PFS_ONE_PAGE;
    pfs->dir_table = pfs->minode_table + (pfs->banks * PFS_ONE_PAGE);

    ERRCK(__osContRamRead(pfs->queue, pfs->channel, PFS_LABEL_AREA, pfs->label));

    ret = osPfsChecker(pfs);
    pfs->status |= PFS_INITIALIZED;
    return ret;
}

s32 __osPfsCheckRamArea(OSPfs *pfs) {
    int i = 0;
    u8 temp1[BLOCKSIZE];
    u8 temp2[BLOCKSIZE];
    u8 save[BLOCKSIZE];
    s32 ret = 0;

    ERRCK(__osPfsSelectBank(pfs, 0));
    ERRCK(__osContRamRead(pfs->queue, pfs->channel, 0, save));
    for (i = 0; i < BLOCKSIZE; i++) {
        temp1[i] = i;
    }
    ERRCK(__osContRamWrite(pfs->queue, pfs->channel, 0, temp1, 0));
    ERRCK(__osContRamRead(pfs->queue, pfs->channel, 0, temp2));
    if (_bcmp(temp1, temp2, BLOCKSIZE) != 0) {
        return PFS_ERR_DEVICE;
    }
    return __osContRamWrite(pfs->queue, pfs->channel, 0, save, 0);
}
