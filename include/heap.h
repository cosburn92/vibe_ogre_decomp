#ifndef HEAP_H
#define HEAP_H

#include "common.h"

/* Heap allocator (src/1060.c) */
void *HMalloc(s32 size);
void *HMallocBack(s32 size); /* HMalloc with gHeapAllocFlags set to 1 */
void *func_80071C04(s32 size);
void *HFree(void *ptr);      /* always returns NULL, so callers can write p = HFree(p) */

#endif /* HEAP_H */
