#include "common.h"

/* 260420 */

typedef struct {
    /* 0x00 */ u16 count;
    /* 0x02 */ u16 h2;
    /* 0x04 */ s32 w4;
    /* 0x08 */ s32 w8;
    /* 0x0C */ s32 id; /* the cached data pointer */
    /* 0x10 */ u16 nextFree;
    /* 0x12 */ u8 unk12[2];
} Ent260; /* size 0x14 */

extern s32 D_80220CA0_ovl_25EE90;
extern Ent260 *D_80220CA8_ovl_25EE90;

Ent260 *func_8020BC78_ovl_25EE90();
extern s32 D_80220CA4_ovl_25EE90;
extern s32 D_80220CAC_ovl_25EE90;
extern s32 D_80220CB0_ovl_25EE90;
extern Ent260 *D_80220CB8_ovl_25EE90[];
void HFree(void *p);
void bzero(void *p, s32 n);
void *HMalloc(s32 size);
Ent260 *func_8020BA6C_ovl_25EE90(void *p);

static inline void CacheRelease(Ent260 *e) {
    void *data;

    if (--e->count == 0) {
        data = (void *)e->id;
        e->nextFree = D_80220CA4_ovl_25EE90;
        D_80220CA4_ovl_25EE90 = e - D_80220CA8_ovl_25EE90;
        HFree(data);
        e->id = 0;
        e->count = 0;
        e->h2 = 0;
        e->w4 = 0;
        e->w8 = 0;
    }
}
/* --- end decls --- */

/* Cache pool: 128 entries chained through nextFree, plus a 32-bucket table */
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
        if (D_80220CA8_ovl_25EE90[i].id != 0) {
            HFree((void *)D_80220CA8_ovl_25EE90[i].id);
        }
    }
    bzero(D_80220CA8_ovl_25EE90, D_80220CA0_ovl_25EE90 * sizeof(Ent260));
}

void func_8020B9D0_ovl_25EE90(void) {
    s32 i;

    for (i = 0; i < D_80220CA0_ovl_25EE90; i++) {
        if (D_80220CA8_ovl_25EE90[i].id != 0) {
            HFree((void *)D_80220CA8_ovl_25EE90[i].id);
        }
    }
    bzero(D_80220CA8_ovl_25EE90, D_80220CA0_ovl_25EE90 * sizeof(Ent260));
    HFree(D_80220CA8_ovl_25EE90);
}

static inline Ent260 *CacheRemember(Ent260 *e) {
    if (++D_80220CB0_ovl_25EE90 >= D_80220CAC_ovl_25EE90) {
        D_80220CB0_ovl_25EE90 = 0;
    }
    D_80220CB8_ovl_25EE90[D_80220CB0_ovl_25EE90] = e;
    return e;
}

/* Finds the cache entry holding p: first in the recent-use ring (newest first), then by scanning
 * the pool from both ends and both sides of the middle at once (recording the hit in the ring).
 * n and k are reused as the two "halves searched" flags */
Ent260 *func_8020BA6C_ovl_25EE90(void *p) {
    s32 n = D_80220CAC_ovl_25EE90;
    s32 k = D_80220CB0_ovl_25EE90;
    Ent260 *lo, *mid, *mid2, *hi;

    for (; n > 0; n--, k--) {
        if (k < 0) {
            k = D_80220CAC_ovl_25EE90 - 1;
        }
        lo = D_80220CB8_ovl_25EE90[k];
        if (lo != NULL && lo->id == (s32)p) {
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
        if (lo->id == (s32)p) {
            return CacheRemember(lo);
        }
        if (mid->id == (s32)p) {
            return CacheRemember(mid);
        }
        if (mid2->id == (s32)p) {
            return CacheRemember(mid2);
        }
        if (hi->id == (s32)p) {
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

#define CACHE_HIT(e) ((e)->id != 0 && (e)->h2 == (u16)a && (e)->w4 == b && (e)->w8 == c)

/* Finds the cache entry for resource (a, b, c) the same way as func_8020BA6C */
Ent260 *func_8020BC78_ovl_25EE90(s32 a, s32 b, s32 c) {
    s32 n = D_80220CAC_ovl_25EE90;
    s32 k = D_80220CB0_ovl_25EE90;
    Ent260 *lo, *mid, *mid2, *hi;

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

s32 func_8020BF5C_ovl_25EE90(u16 a) {
    s32 r = 0;
    Ent260 *e = ((Ent260 *(*)())func_8020BC78_ovl_25EE90)(a);

    if (e != NULL) {
        r = e->id;
    }
    return r;
}

#ifdef NON_MATCHING
/* Loop shape differs. */
void func_8020BF94_ovl_25EE90(s32 id) {
    s32 pad;
    s32 n = D_80220CA0_ovl_25EE90;
    Ent260 *e = D_80220CA8_ovl_25EE90;
    s32 i;

    for (i = 0; i < n; i++, e++) {
        if (e->id == id) {
            e->count++;
            return;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/260420", func_8020BF94_ovl_25EE90);
#endif

/* Takes a cache entry from the free list and records it in the recent-use ring */
Ent260 *func_8020BFE8_ovl_25EE90(void) {
    Ent260 *e;

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
    e->id = (s32)e;
    return e;
}

/* Drops a reference to the cache entry holding p; frees it on the last one */
void func_8020C074_ovl_25EE90(void *p) {
    Ent260 *e;

    if (p != NULL) {
        e = func_8020BA6C_ovl_25EE90(p);
        if (e != NULL) {
            CacheRelease(e);
        }
    } else {
        for (;;) {
        }
    }
}

void func_8020C130_ovl_25EE90(u16 id) {
    Ent260 *e = ((Ent260 *(*)())func_8020BC78_ovl_25EE90)(id);

    if (e != NULL) {
        CacheRelease(e);
    } else {
        for (;;) {
        }
    }
}
