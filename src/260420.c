#include "common.h"
#include "heap.h"
#include "rescache.h"

/* 260420 */

extern s32 D_80220CA0_ovl_25EE90;
extern ResCacheEntry *D_80220CA8_ovl_25EE90;

ResCacheEntry *func_8020BC78_ovl_25EE90(s32 kind, s32 id, s32 arg);
extern s32 D_80220CA4_ovl_25EE90;
extern s32 D_80220CAC_ovl_25EE90;
extern s32 D_80220CB0_ovl_25EE90;
extern ResCacheEntry *D_80220CB8_ovl_25EE90[];
void bzero(void *p, s32 n);
ResCacheEntry *func_8020BA6C_ovl_25EE90(void *p);

static inline void CacheRelease(ResCacheEntry *e) {
    void *data;

    if (--e->count == 0) {
        data = e->data;
        e->nextFree = D_80220CA4_ovl_25EE90;
        D_80220CA4_ovl_25EE90 = e - D_80220CA8_ovl_25EE90;
        HFree(data);
        e->data = NULL;
        e->count = 0;
        e->kind = 0;
        e->id = 0;
        e->arg = 0;
    }
}
/* --- end decls --- */

/* Cache pool: 128 entries chained through nextFree, plus a 32-slot recent-use ring */
void func_8020B870_ovl_25EE90(void) {
    s32 i;

    D_80220CA0_ovl_25EE90 = 0x80;
    D_80220CA8_ovl_25EE90 = HMalloc(0xA00);
    bzero(D_80220CA8_ovl_25EE90, 0xA00);
    for (i = 0; i < D_80220CA0_ovl_25EE90 - 1; i++) {
        D_80220CA8_ovl_25EE90[i].nextFree = i + 1;
    }
    D_80220CA8_ovl_25EE90[i].nextFree = 0xFFFF;
    D_80220CA4_ovl_25EE90 = 0;
    D_80220CAC_ovl_25EE90 = 0x20;
    D_80220CB0_ovl_25EE90 = 0;
    bzero(D_80220CB8_ovl_25EE90, 0x80);
}

void func_8020B940_ovl_25EE90(void) {
    s32 i;

    for (i = 0; i < D_80220CA0_ovl_25EE90; i++) {
        if (D_80220CA8_ovl_25EE90[i].data != NULL) {
            HFree(D_80220CA8_ovl_25EE90[i].data);
        }
    }
    bzero(D_80220CA8_ovl_25EE90, D_80220CA0_ovl_25EE90 * sizeof(ResCacheEntry));
}

void func_8020B9D0_ovl_25EE90(void) {
    s32 i;

    for (i = 0; i < D_80220CA0_ovl_25EE90; i++) {
        if (D_80220CA8_ovl_25EE90[i].data != NULL) {
            HFree(D_80220CA8_ovl_25EE90[i].data);
        }
    }
    bzero(D_80220CA8_ovl_25EE90, D_80220CA0_ovl_25EE90 * sizeof(ResCacheEntry));
    HFree(D_80220CA8_ovl_25EE90);
}

static inline ResCacheEntry *CacheRemember(ResCacheEntry *e) {
    if (++D_80220CB0_ovl_25EE90 >= D_80220CAC_ovl_25EE90) {
        D_80220CB0_ovl_25EE90 = 0;
    }
    D_80220CB8_ovl_25EE90[D_80220CB0_ovl_25EE90] = e;
    return e;
}

/* Finds the cache entry holding p: first in the recent-use ring (newest first), then by scanning
 * the pool from both ends and both sides of the middle at once (recording the hit in the ring).
 * n and k are reused as the two "halves searched" flags */
ResCacheEntry *func_8020BA6C_ovl_25EE90(void *p) {
    s32 n = D_80220CAC_ovl_25EE90;
    s32 k = D_80220CB0_ovl_25EE90;
    ResCacheEntry *lo, *mid, *mid2, *hi;

    for (; n > 0; n--, k--) {
        if (k < 0) {
            k = D_80220CAC_ovl_25EE90 - 1;
        }
        lo = D_80220CB8_ovl_25EE90[k];
        if (lo != NULL && lo->data == p) {
            return lo;
        }
    }
    lo = D_80220CA8_ovl_25EE90;
    n = 0;
    k = 0;
    mid = &lo[D_80220CA0_ovl_25EE90 / 2];
    mid2 = mid + 1;
    hi = &lo[D_80220CA0_ovl_25EE90 - 1];
    do {
        if (lo->data == p) {
            return CacheRemember(lo);
        }
        if (mid->data == p) {
            return CacheRemember(mid);
        }
        if (mid2->data == p) {
            return CacheRemember(mid2);
        }
        if (hi->data == p) {
            return CacheRemember(hi);
        }
        lo++;
        mid--;
        mid2++;
        hi--;
        if (mid < lo) {
            k = 1;
        }
        if (hi < mid2) {
            n = 1;
        }
    } while (!(k & n));
    return NULL;
}

#define CACHE_HIT(e) ((e)->data != NULL && (e)->kind == (u16)kind && (e)->id == id && (e)->arg == arg)

/* Finds the cache entry for resource (kind, id, arg) the same way as func_8020BA6C */
ResCacheEntry *func_8020BC78_ovl_25EE90(s32 kind, s32 id, s32 arg) {
    s32 n = D_80220CAC_ovl_25EE90;
    s32 k = D_80220CB0_ovl_25EE90;
    ResCacheEntry *lo, *mid, *mid2, *hi;

    for (; n > 0; n--, k--) {
        if (k < 0) {
            k = D_80220CAC_ovl_25EE90 - 1;
        }
        lo = D_80220CB8_ovl_25EE90[k];
        if (lo != NULL && CACHE_HIT(lo)) {
            return lo;
        }
    }
    lo = D_80220CA8_ovl_25EE90;
    n = 0;
    k = 0;
    mid = &lo[D_80220CA0_ovl_25EE90 / 2];
    mid2 = mid + 1;
    hi = &lo[D_80220CA0_ovl_25EE90 - 1];
    do {
        if (CACHE_HIT(lo)) {
            return CacheRemember(lo);
        }
        if (CACHE_HIT(mid)) {
            return CacheRemember(mid);
        }
        if (CACHE_HIT(mid2)) {
            return CacheRemember(mid2);
        }
        if (CACHE_HIT(hi)) {
            return CacheRemember(hi);
        }
        lo++;
        mid--;
        mid2++;
        hi--;
        if (mid < lo) {
            k = 1;
        }
        if (hi < mid2) {
            n = 1;
        }
    } while (!(k & n));
    return NULL;
}

void *func_8020BF5C_ovl_25EE90(u16 kind, s32 id, s32 arg) {
    void *data = NULL;
    ResCacheEntry *e = func_8020BC78_ovl_25EE90(kind, id, arg);

    if (e != NULL) {
        data = e->data;
    }
    return data;
}

void func_8020BF94_ovl_25EE90(void *data) {
    s32 pad[1];
    ResCacheEntry *e = D_80220CA8_ovl_25EE90;
    s32 i;

    for (i = 0; i < D_80220CA0_ovl_25EE90; i++, e++) {
        if (e->data == data) {
            e->count++;
            return;
        }
    }
}

/* Takes a cache entry from the free list and records it in the recent-use ring */
ResCacheEntry *func_8020BFE8_ovl_25EE90(void) {
    ResCacheEntry *e;

    if (D_80220CA4_ovl_25EE90 == 0xFFFF) {
        for (;;) {
        }
    }
    e = &D_80220CA8_ovl_25EE90[D_80220CA4_ovl_25EE90];
    D_80220CA4_ovl_25EE90 = e->nextFree;
    if (++D_80220CB0_ovl_25EE90 >= D_80220CAC_ovl_25EE90) {
        D_80220CB0_ovl_25EE90 = 0;
    }
    D_80220CB8_ovl_25EE90[D_80220CB0_ovl_25EE90] = e;
    e->data = e; /* marks the entry used until the caller stores the data */
    return e;
}

/* Drops a reference to the cache entry holding p; frees it on the last one */
void func_8020C074_ovl_25EE90(void *data) {
    ResCacheEntry *e;

    if (data != NULL) {
        e = func_8020BA6C_ovl_25EE90(data);
        if (e != NULL) {
            CacheRelease(e);
        }
    } else {
        for (;;) {
        }
    }
}

void func_8020C130_ovl_25EE90(u16 kind, s32 id, s32 arg) {
    ResCacheEntry *e = func_8020BC78_ovl_25EE90(kind, id, arg);

    if (e != NULL) {
        CacheRelease(e);
    } else {
        for (;;) {
        }
    }
}
