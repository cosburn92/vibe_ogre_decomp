#ifndef RESCACHE_H
#define RESCACHE_H

#include "common.h"

/* Resource cache (overlay 25EE90, src/260420.c). A loaded resource is keyed by
 * (kind, id, arg) and reference-counted; releasing the last reference frees its data. */
typedef struct {
    /* 0x00 */ u16 count;    /* references */
    /* 0x02 */ u16 kind;
    /* 0x04 */ s32 id;
    /* 0x08 */ s32 arg;
    /* 0x0C */ void *data;   /* NULL when the entry is free */
    /* 0x10 */ u16 nextFree; /* index of the next free entry, 0xFFFF at the end */
    /* 0x12 */ u8 unk12[2];
} ResCacheEntry; /* size 0x14 */

void func_8020B870_ovl_25EE90(void);                 /* allocate the 128-entry pool */
void func_8020B9D0_ovl_25EE90(void);                 /* free every resource and the pool */
void *func_8020BF5C_ovl_25EE90(u16 kind, s32 id, s32 arg); /* cached data, or NULL */
void func_8020BF94_ovl_25EE90(void *data);           /* add a reference */
ResCacheEntry *func_8020BFE8_ovl_25EE90(void);       /* take a free entry */
void func_8020C074_ovl_25EE90(void *data);           /* release by data pointer */
void func_8020C130_ovl_25EE90(u16 kind, s32 id, s32 arg); /* release by key */

#endif /* RESCACHE_H */
