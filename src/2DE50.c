#include "common.h"
#include "chunk.h"
#include "heap.h"

/* ROM chunk loader. Chunks are addressed by handle: the table at ROM 0x594280 holds each
 * chunk's size (at handle & 0x0FFFFFFF) and the data follows at 0x594284 + handle. */

extern u8 D_594280[]; /* chunk size table (ROM) */
extern u8 D_594284[]; /* chunk data (ROM) */
extern u32 gChunkSizeCache;
extern u32 gChunkSizeCacheHandle;
extern u32 D_800C47E0;

void PiDmaRead(u32 rom_addr, void *buf_ptr, u32 size);
u32 DecodeLZ(u8 *dst, u8 *src);

/* DMA from ROM; reads shorter than 16 bytes go through an aligned stack buffer */
inline void RomRead(void *rom, void *dst, u32 size) {
    u8 buf[0x20];
    u8 *p = (u8 *)(((u32)buf + 15) / 16 * 16);
    u8 *d;

    if (size < 16) {
        d = dst;
        PiDmaRead((u32)rom, p, (size + 1) & ~1);
        while (size-- != 0) {
            *d++ = *p++;
        }
    } else {
        PiDmaRead((u32)rom, dst, (size + 1) & ~1);
    }
}

void func_8009DAEC(void) {
}

inline u32 ChunkSize(u32 handle) {
    if (handle == 0) {
        return 0;
    }
    if (handle == gChunkSizeCacheHandle) {
        return gChunkSizeCache;
    }
    RomRead(D_594280 + (handle & 0x0FFFFFFF), &D_800C47E0, 4);
    gChunkSizeCacheHandle = handle;
    gChunkSizeCache = D_800C47E0;
    return gChunkSizeCache;
}

void *LoadChunkRaw(void *dst, u32 handle) {
    u32 size = ChunkSize(handle);

    if (dst == NULL) {
        dst = HMalloc(size);
    }
    RomRead(D_594284 + handle, dst, (size + 1) & ~1);
    return dst;
}

u8 *func_8009DD28(u32 handle) {
    return D_594284 + handle;
}

/* Loads an LZ-compressed chunk */
void *LoadChunk(u32 handle) {
    u8 *packed = func_80071C04(ChunkSize(handle));
    u8 *dst;

    LoadChunkRaw(packed, handle);
    dst = HMalloc(ReadU32BE(packed));
    DecodeLZ(dst, packed);
    HFree(packed);
    return dst;
}

void *func_8009DE40(u32 handle) {
    u8 *packed = func_80071C04(ChunkSize(handle));
    u8 *dst;

    LoadChunkRaw(packed, handle);
    dst = HMallocBack(ReadU32BE(packed));
    DecodeLZ(dst, packed);
    HFree(packed);
    return dst;
}

void *func_8009DF48(u32 handle) {
    u8 *packed = func_80071C04(ChunkSize(handle));
    u8 *dst;

    LoadChunkRaw(packed, handle);
    dst = func_80071C04(ReadU32BE(packed));
    DecodeLZ(dst, packed);
    HFree(packed);
    return dst;
}
