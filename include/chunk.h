#ifndef CHUNK_H
#define CHUNK_H

#include "common.h"

/* ROM reads and data chunks (src/2DE50.c). A chunk's size word is at ROM
 * 0x594280 + handle and its data follows at 0x594284 + handle. */
void RomRead(void *rom, void *dst, u32 size);
u32 ChunkSize(u32 handle);
void *LoadChunkRaw(void *dst, u32 handle); /* dst == NULL allocates it */
void *LoadChunk(u32 handle);               /* load and LZ-decode */

/* src/8700.c: LoadAsset(handle, table index..., command[, member]) walks chunk tables from
 * handle and returns the data the command asks for */
void *LoadAsset(u32 handle, ...);

/* src/A370.c */
u32 ReadU32BE(u8 *p);

#endif /* CHUNK_H */
