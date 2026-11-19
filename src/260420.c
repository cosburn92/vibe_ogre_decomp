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

Ent260 *func_8020BC78_ovl_25EE90(u16 a);
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

INCLUDE_ASM("asm/nonmatchings/260420", func_8020BA6C_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260420", func_8020BC78_ovl_25EE90);

s32 func_8020BF5C_ovl_25EE90(u16 a) {
    s32 r = 0;
    Ent260 *e = func_8020BC78_ovl_25EE90(a);

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
    Ent260 *e = func_8020BC78_ovl_25EE90(id);

    if (e != NULL) {
        CacheRelease(e);
    } else {
        for (;;) {
        }
    }
}
