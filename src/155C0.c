#include "common.h"

/* libmus: sample DMA buffers (after the SDK audiomgr's __amDma) */

typedef void *OSMesg;

typedef struct {
    /* 0x00 */ void *mtqueue;
    /* 0x04 */ void *fullqueue;
    /* 0x08 */ s32 validCount;
    /* 0x0C */ s32 first;
    /* 0x10 */ s32 msgCount;
    /* 0x14 */ OSMesg *msg;
} OSMesgQueue;

typedef struct {
    /* 0x00 */ u16 type;
    /* 0x02 */ u8 pri;
    /* 0x03 */ u8 status;
    /* 0x04 */ OSMesgQueue *retQueue;
} OSIoMesgHdr;

typedef struct {
    /* 0x00 */ OSIoMesgHdr hdr;
    /* 0x08 */ void *dramAddr;
    /* 0x0C */ u32 devAddr;
    /* 0x10 */ u32 size;
    /* 0x14 */ void *piHandle;
} OSIoMesg; /* size 0x18 */

typedef struct DmaBuffer {
    /* 0x00 */ struct DmaBuffer *prev;
    /* 0x04 */ struct DmaBuffer *next;
    /* 0x08 */ s32 frames; /* frames until it goes back on the free list */
    /* 0x0C */ u32 startAddr;
    /* 0x10 */ u8 *ptr;
} DmaBuffer; /* size 0x14 */

extern DmaBuffer *D_800B1860; /* used list, sorted by startAddr */
extern DmaBuffer *D_800B1864; /* free list */
extern DmaBuffer *D_800B1868; /* all buffers */
extern OSIoMesg *D_800B186C;
extern OSMesg *D_800B1870;
extern u32 D_800B1874; /* buffer length */
extern s32 D_800B1878; /* DMAs in flight */
extern OSMesgQueue D_800B1880;
extern void *D_800B1898; /* cartridge PI handle */
extern void *D_800C4B48; /* disk ROM PI handle */
extern u32 D_800E7A14;   /* musConfig control_flag */

void *__MusIntMemMalloc(s32 size);
void func_80085B30(void *dest, u8 value, u32 length);
void *osCartRomInit(void);
void osCreateMesgQueue(OSMesgQueue *mq, OSMesg *msg, s32 count);
s32 osRecvMesg(OSMesgQueue *mq, OSMesg *msg, s32 flag);
u32 osVirtualToPhysical(void *addr);
s32 func_8008BC40(void *handle, OSIoMesg *mb, s32 direction); /* osEPiStartDma */
DmaBuffer *func_8008547C(u32 addr, s32 len);
void *func_80085404(void *state);
s32 func_80085410(u32 addr, s32 len, void *state);

/* __MusIntDmaInit: returns the synthesizer's DMA-new callback */
void *func_800851C0(s32 count, s32 length) {
    s32 i;
    DmaBuffer *b;

    D_800B1898 = osCartRomInit();
    D_800B186C = __MusIntMemMalloc(count * 2 * sizeof(OSIoMesg));
    D_800B1870 = __MusIntMemMalloc(count * 2 * sizeof(OSMesg));
    D_800B1868 = __MusIntMemMalloc(count * sizeof(DmaBuffer));
    func_80085B30(D_800B1868, 0, count * sizeof(DmaBuffer));
    for (i = 0; i < count - 1; i++) {
        b = (DmaBuffer *)(i * sizeof(DmaBuffer) + (u32)D_800B1868);
        b->next = b + 1;
        b[1].prev = b;
        D_800B1868[i].ptr = __MusIntMemMalloc(length);
        D_800B1868[i].startAddr = -1;
    }
    D_800B1868[i].ptr = __MusIntMemMalloc(length);
    D_800B1868[i].startAddr = -1;
    D_800B1874 = length;
    D_800B1878 = 0;
    D_800B1860 = NULL;
    D_800B1864 = D_800B1868;
    osCreateMesgQueue(&D_800B1880, D_800B1870, count * 2);
    return func_80085404;
}

/* __MusIntDmaProcess: once per frame, retire finished DMAs and age the used buffers */
void func_80085334(void) {
    OSMesg msg;
    DmaBuffer *dmaPtr, *next;

    while (D_800B1878 != 0) {
        osRecvMesg(&D_800B1880, &msg, 0);
        D_800B1878--;
    }
    dmaPtr = D_800B1860;
    while (dmaPtr != NULL) {
        if (--dmaPtr->frames == 0) {
            next = dmaPtr->next;
            if (next != NULL) {
                next->prev = dmaPtr->prev;
            }
            if (dmaPtr->prev != NULL) {
                dmaPtr->prev->next = dmaPtr->next;
            } else {
                D_800B1860 = dmaPtr->next;
            }
            dmaPtr->prev = NULL;
            dmaPtr->next = D_800B1864;
            D_800B1864 = dmaPtr;
            dmaPtr = next;
        } else {
            dmaPtr = dmaPtr->next;
        }
    }
}

void *func_80085404(void *state) {
    return func_80085410;
}

/* the ALDMAproc */
s32 func_80085410(u32 addr, s32 len, void *state) {
    DmaBuffer *dmaPtr = func_8008547C(addr, len);

    if (dmaPtr == NULL) {
        return osVirtualToPhysical((void *)addr);
    }
    if ((addr & 0xFF000000) == 0xFF000000) {
        addr &= 0xFFFFFF;
        addr += 0x140000;
    }
    return osVirtualToPhysical(dmaPtr->ptr + addr - dmaPtr->startAddr);
}

/* __MusIntDmaSample: find or start the DMA holding [addr, addr + len) */
DmaBuffer *func_8008547C(u32 addr, s32 len) {
    void *handle;
    DmaBuffer *dmaPtr, *lastDmaPtr, *newPtr;
    OSIoMesg *iomsg;
    u32 addrEnd;

    if ((addr & 0xFF000000) == 0xFF000000) {
        handle = D_800C4B48;
        addr &= 0xFFFFFF;
        addr += 0x140000;
    } else {
        if (D_800E7A14 & 1) {
            return NULL;
        }
        handle = D_800B1898;
    }
    lastDmaPtr = NULL;
    dmaPtr = D_800B1860;
    addrEnd = addr + len;
    while (dmaPtr != NULL) {
        if (addr < dmaPtr->startAddr) {
            break;
        }
        if (addrEnd <= dmaPtr->startAddr + D_800B1874) {
            dmaPtr->frames = 2;
            return dmaPtr;
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = dmaPtr->next;
    }
    newPtr = D_800B1864;
    if (newPtr == NULL) {
        return D_800B1860;
    }
    D_800B1864 = newPtr->next;
    if (lastDmaPtr != NULL) {
        newPtr->next = lastDmaPtr->next;
        if (newPtr->next != NULL) {
            newPtr->next->prev = newPtr;
        }
        newPtr->prev = lastDmaPtr;
        lastDmaPtr->next = newPtr;
    } else {
        newPtr->prev = NULL;
        newPtr->next = D_800B1860;
        if (D_800B1860 != NULL) {
            D_800B1860->prev = newPtr;
        }
        D_800B1860 = newPtr;
    }
    newPtr->startAddr = addr & ~1;
    newPtr->frames = 2;
    iomsg = &D_800B186C[D_800B1878++];
    iomsg->hdr.pri = 0;
    iomsg->hdr.retQueue = &D_800B1880;
    iomsg->dramAddr = newPtr->ptr;
    iomsg->devAddr = newPtr->startAddr;
    iomsg->size = D_800B1874;
    func_8008BC40(handle, iomsg, 0);
    return newPtr;
}
