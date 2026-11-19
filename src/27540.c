#include "common.h"
#include "libultra.h"

/* libultra pfsinternal.c (contpfs.c) */

#define PFS_ONE_PAGE 8
#define PFS_MAX_BANKS 62
#define PFS_ID_0AREA 1
#define PFS_ID_1AREA 3
#define PFS_ID_2AREA 4
#define PFS_ID_3AREA 6
#define PFS_INODE_SIZE_PER_PAGE 128
#define DEF_DIR_PAGES 2
#define PFS_READ 0
#define PFS_WRITE 1

#define ERRCK(fn)          \
    ret = fn;              \
    if (ret != 0) {        \
        return ret;        \
    }

#define SET_ACTIVEBANK_TO_ZERO                  \
    if (pfs->activebank != 0) {                 \
        ERRCK(__osPfsSelectBank(pfs, 0));       \
    }

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

typedef union {
    struct {
        u8 bank;
        u8 page;
    } inode_t;
    u16 ipage;
} __OSInodeUnit;

typedef struct {
    __OSInodeUnit inode_page[128];
} __OSInode;

extern __OSInode __osPfsInodeCache;
extern s32 D_800ABAA0; /* __osPfsInodeCacheChannel */

u32 osGetCount(void);
void _bcopy(const void *src, void *dst, s32 len);
s32 _bcmp(const void *a, const void *b, s32 len);
s32 __osCheckPackId(OSPfs *pfs, __OSPackId *temp);
s32 __osRepairPackId(OSPfs *pfs, __OSPackId *badid, __OSPackId *newid);

inline u16 __osSumcalc(u8 *ptr, int length) {
    int i;
    u32 sum = 0;
    u8 *tmp = ptr;

    for (i = 0; i < length; i++) {
        sum += *tmp;
        tmp++;
    }
    return sum & 0xFFFF;
}

inline s32 __osIdCheckSum(u16 *ptr, u16 *csum, u16 *icsum) {
    u16 data = 0;
    u32 j;

    *csum = *icsum = 0;
    for (j = 0; j < ((sizeof(__OSPackId) - sizeof(u32)) / sizeof(u8)); j += 2) {
        data = *((u16 *)((u32)ptr + j));
        *csum += data;
        *icsum += ~data;
    }
    return 0;
}

s32 __osRepairPackId(OSPfs *pfs, __OSPackId *badid, __OSPackId *newid) {
    s32 ret = 0;
    u8 temp[BLOCKSIZE];
    u8 comp[BLOCKSIZE];
    u8 mask = 0;
    int i;
    int j = 0;
    u16 index[4];

    newid->repaired = -1;
    newid->random = osGetCount();
    newid->serial_mid = badid->serial_mid;
    newid->serial_low = badid->serial_low;

    SET_ACTIVEBANK_TO_ZERO;
    do {
        ERRCK(__osPfsSelectBank(pfs, j));
        ERRCK(__osContRamRead(pfs->queue, pfs->channel, 0, (u8 *)temp));

        temp[0] = j | 0x80;
        for (i = 1; i < BLOCKSIZE; i++) {
            temp[i] = ~temp[i];
        }

        ERRCK(__osContRamWrite(pfs->queue, pfs->channel, 0, (u8 *)temp, 0));
        ERRCK(__osContRamRead(pfs->queue, pfs->channel, 0, (u8 *)comp));

        for (i = 0; i < BLOCKSIZE; i++) {
            if (comp[i] != temp[i]) {
                break;
            }
        }
        if (i != BLOCKSIZE) {
            break;
        }
        if (j > 0) {
            ERRCK(__osPfsSelectBank(pfs, 0));
            ERRCK(__osContRamRead(pfs->queue, pfs->channel, 0, (u8 *)temp));
            if (temp[0] != 0x80) {
                break;
            }
        }
        j++;
    } while (j < PFS_MAX_BANKS);

    SET_ACTIVEBANK_TO_ZERO;

    mask = (j > 0) ? 1 : 0;
    newid->deviceid = (badid->deviceid & (u16)~1) | mask;
    newid->banks = j;
    newid->version = badid->version;
    __osIdCheckSum((u16 *)newid, &newid->checksum, &newid->inverted_checksum);

    index[0] = PFS_ID_0AREA;
    index[1] = PFS_ID_1AREA;
    index[2] = PFS_ID_2AREA;
    index[3] = PFS_ID_3AREA;
    for (i = 0; i < 4; i++) {
        ERRCK(__osContRamWrite(pfs->queue, pfs->channel, index[i], (u8 *)newid, 1));
    }
    ERRCK(__osContRamRead(pfs->queue, pfs->channel, PFS_ID_0AREA, (u8 *)temp));
    for (i = 0; i < BLOCKSIZE; i++) {
        if (temp[i] != ((u8 *)newid)[i]) {
            return PFS_ERR_DEVICE;
        }
    }
    return 0;
}

s32 __osCheckPackId(OSPfs *pfs, __OSPackId *temp) {
    u16 index[4];
    s32 ret = 0;
    u16 sum;
    u16 isum;
    int i, j;

    SET_ACTIVEBANK_TO_ZERO;
    index[0] = PFS_ID_0AREA;
    index[1] = PFS_ID_1AREA;
    index[2] = PFS_ID_2AREA;
    index[3] = PFS_ID_3AREA;
    for (i = 1; i < 4; i++) {
        ERRCK(__osContRamRead(pfs->queue, pfs->channel, index[i], (u8 *)temp));
        __osIdCheckSum((u16 *)temp, &sum, &isum);
        if ((temp->checksum == sum) && (temp->inverted_checksum == isum)) {
            break;
        }
    }
    if (i == 4) {
        return PFS_ERR_ID_FATAL;
    }
    for (j = 0; j < 4; j++) {
        if (j != i) {
            ERRCK(__osContRamWrite(pfs->queue, pfs->channel, index[j], (u8 *)temp, 1));
        }
    }
    return 0;
}

s32 __osGetId(OSPfs *pfs) {
    u8 temp[BLOCKSIZE];
    __OSPackId newid;
    u16 sum;
    u16 isum;
    s32 ret;
    __OSPackId *id;

    SET_ACTIVEBANK_TO_ZERO;
    ERRCK(__osContRamRead(pfs->queue, pfs->channel, PFS_ID_0AREA, (u8 *)temp));
    __osIdCheckSum((u16 *)temp, &sum, &isum);
    id = (__OSPackId *)temp;
    if ((id->checksum != sum) || (id->inverted_checksum != isum)) {
        ret = __osCheckPackId(pfs, id);
        if (ret == PFS_ERR_ID_FATAL) {
            ERRCK(__osRepairPackId(pfs, id, &newid));
            id = &newid;
        } else if (ret != 0) {
            return ret;
        }
    }
    if ((id->deviceid & 0x01) == 0) {
        ERRCK(__osRepairPackId(pfs, id, &newid));
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
    return 0;
}

s32 __osCheckId(OSPfs *pfs) {
    u8 temp[BLOCKSIZE];
    s32 ret;

    if (pfs->activebank != 0) {
        ret = __osPfsSelectBank(pfs, 0);
        if (ret == PFS_ERR_NEW_PACK) {
            ret = __osPfsSelectBank(pfs, 0);
        }
        if (ret != 0) {
            return ret;
        }
    }
    ret = __osContRamRead(pfs->queue, pfs->channel, PFS_ID_0AREA, (u8 *)temp);
    if (ret != 0) {
        if (ret != PFS_ERR_NEW_PACK) {
            return ret;
        }
        ret = __osContRamRead(pfs->queue, pfs->channel, PFS_ID_0AREA, (u8 *)temp);
        if (ret != 0) {
            return ret;
        }
    }
    if (_bcmp(pfs->id, temp, BLOCKSIZE) != 0) {
        return PFS_ERR_NEW_PACK;
    }
    return 0;
}

s32 __osPfsRWInode(OSPfs *pfs, __OSInode *inode, u8 flag, u8 bank) {
    u8 sum;
    int j;
    s32 ret;
    int offset;
    u8 *addr;

    if (flag == PFS_READ && bank == __osPfsInodeCacheBank && (pfs->channel == D_800ABAA0)) {
        _bcopy(&__osPfsInodeCache, inode, sizeof(__OSInode));
        return 0;
    }

    SET_ACTIVEBANK_TO_ZERO;

    if (bank > 0) {
        offset = 1;
    } else {
        offset = pfs->inode_start_page;
    }

    if (flag == PFS_WRITE) {
        inode->inode_page[0].inode_t.page =
            __osSumcalc((u8 *)&inode->inode_page[offset], (PFS_INODE_SIZE_PER_PAGE - offset) * 2);
    }

    for (j = 0; j < PFS_ONE_PAGE; j++) {
        addr = ((u8 *)inode->inode_page + j * BLOCKSIZE);
        if (flag == PFS_WRITE) {
            ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->inode_table + bank * PFS_ONE_PAGE + j, addr, 0);
            ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->minode_table + bank * PFS_ONE_PAGE + j, addr, 0);
        } else {
            ret = __osContRamRead(pfs->queue, pfs->channel, pfs->inode_table + bank * PFS_ONE_PAGE + j, addr);
        }
        if (ret != 0) {
            return ret;
        }
    }

    if (flag == PFS_READ) {
        sum = __osSumcalc((u8 *)&inode->inode_page[offset], (PFS_INODE_SIZE_PER_PAGE - offset) * 2);
        if (sum != inode->inode_page[0].inode_t.page) {
            for (j = 0; j < PFS_ONE_PAGE; j++) {
                addr = ((u8 *)inode->inode_page + j * BLOCKSIZE);
                ret = __osContRamRead(pfs->queue, pfs->channel, pfs->minode_table + bank * PFS_ONE_PAGE + j, addr);
            }
            sum = __osSumcalc((u8 *)&inode->inode_page[offset], (PFS_INODE_SIZE_PER_PAGE - offset) * 2);
            if (sum != inode->inode_page[0].inode_t.page) {
                return PFS_ERR_INCONSISTENT;
            }
            for (j = 0; j < PFS_ONE_PAGE; j++) {
                addr = ((u8 *)inode->inode_page + j * BLOCKSIZE);
                ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->inode_table + bank * PFS_ONE_PAGE + j, addr, 0);
            }
        }
    }

    __osPfsInodeCacheBank = bank;
    _bcopy(inode, &__osPfsInodeCache, sizeof(__OSInode));
    D_800ABAA0 = pfs->channel;
    return 0;
}
