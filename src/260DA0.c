#include "common.h"

/* 260DA0 */

extern void *D_80220F20_ovl_25EE90;
extern s32 D_80220D48_ovl_25EE90;
extern s32 D_80220D44_ovl_25EE90;
extern s16 D_80220D40_ovl_25EE90;

void *HMalloc(s32 size);
typedef struct {
    /* 0x0 */ u16 h0;
    /* 0x2 */ u16 kind;
    /* 0x4 */ s32 id;
    /* 0x8 */ s32 w8;
    /* 0xC */ void *data;
} CacheEnt;
typedef struct {
    /* 0x0 */ u16 h0;
    /* 0x2 */ u16 h2;
    /* 0x4 */ u8 unk4[2];
    /* 0x6 */ u16 h6;
    /* 0x8 */ u8 unk8[2];
} Rec10b;
typedef struct {
    /* 0x0 */ u8 unk0[4];
    /* 0x4 */ s32 n;
    /* 0x8 */ u8 unk8[4];
    /* 0xC */ Rec10b *recs;
} RecSet;
void HFree(void *p);
void *func_8020BF5C_ovl_25EE90(s32 kind, s32 id, s32 c);
void func_8020BF94_ovl_25EE90(void *p);
CacheEnt *func_8020BFE8_ovl_25EE90(void);
void *func_8020C380_ovl_25EE90(s32 kind, s32 id);
void func_8020C130_ovl_25EE90(u16 a, s32 b, s32 c);
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
/* --- end decls --- */

void func_8020C1F0_ovl_25EE90(void) {
    D_80220F20_ovl_25EE90 = HMalloc(0x8000);
    D_80220D48_ovl_25EE90 = 0;
    D_80220D44_ovl_25EE90 = 0;
    D_80220D40_ovl_25EE90 = 0;
}

void func_8020C22C_ovl_25EE90(void) {
    HFree(D_80220F20_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020C250_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020C380_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020C4EC_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020C644_ovl_25EE90);

void *func_8020C704_ovl_25EE90(s32 id) {
    void *r = NULL;
    CacheEnt *e;

    if (id > 0) {
        r = func_8020BF5C_ovl_25EE90(4, id, 0);
        if (r != NULL) {
            func_8020BF94_ovl_25EE90(r);
            return r;
        }
        e = func_8020BFE8_ovl_25EE90();
        if (e != NULL) {
            r = func_8020C380_ovl_25EE90(4, id);
            if (r != NULL) {
                e->h0 = 1;
                e->data = r;
                e->kind = 4;
                e->id = id;
                e->w8 = 0;
            } else {
                for (;;) {
                }
            }
        }
    }
    return r;
}

void *func_8020C7B8_ovl_25EE90(s32 id) {
    void *r = NULL;
    CacheEnt *e;

    if (id > 0) {
        r = func_8020BF5C_ovl_25EE90(5, id, 0);
        if (r != NULL) {
            func_8020BF94_ovl_25EE90(r);
            return r;
        }
        e = func_8020BFE8_ovl_25EE90();
        if (e != NULL) {
            r = func_8020C380_ovl_25EE90(5, id);
            if (r != NULL) {
                e->h0 = 1;
                e->data = r;
                e->kind = 5;
                e->id = id;
                e->w8 = 0;
            }
        }
    }
    return r;
}

void *func_8020C860_ovl_25EE90(s32 id) {
    void *r = NULL;
    CacheEnt *e;

    if (id > 0) {
        r = func_8020BF5C_ovl_25EE90(6, id, 0);
        if (r != NULL) {
            func_8020BF94_ovl_25EE90(r);
            return r;
        }
        e = func_8020BFE8_ovl_25EE90();
        if (e != NULL) {
            r = func_8020C380_ovl_25EE90(6, id);
            if (r != NULL) {
                e->h0 = 1;
                e->data = r;
                e->kind = 6;
                e->id = id;
                e->w8 = 0;
            }
        }
    }
    return r;
}

void *func_8020C908_ovl_25EE90(s32 id) {
    void *r = NULL;
    CacheEnt *e;

    if (id > 0) {
        r = func_8020BF5C_ovl_25EE90(7, id, 0);
        if (r != NULL) {
            func_8020BF94_ovl_25EE90(r);
            return r;
        }
        e = func_8020BFE8_ovl_25EE90();
        if (e != NULL) {
            r = func_8020C380_ovl_25EE90(7, id);
            if (r != NULL) {
                e->h0 = 1;
                e->data = r;
                e->kind = 7;
                e->id = id;
                e->w8 = 0;
            }
        }
    }
    return r;
}

void *func_8020C9B0_ovl_25EE90(s32 id) {
    void *r = NULL;
    CacheEnt *e;

    if (id > 0) {
        r = func_8020BF5C_ovl_25EE90(8, id, 0);
        if (r != NULL) {
            func_8020BF94_ovl_25EE90(r);
            return r;
        }
        e = func_8020BFE8_ovl_25EE90();
        if (e != NULL) {
            r = func_8020C380_ovl_25EE90(8, id);
            if (r != NULL) {
                e->h0 = 1;
                e->data = r;
                e->kind = 8;
                e->id = id;
                e->w8 = 0;
            }
        }
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020CA58_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020CC00_ovl_25EE90);

void func_8020CDF4_ovl_25EE90(RecSet *s) {
    s32 n = s->n;
    Rec10b *r = s->recs;

    for (; n > 0; n--, r++) {
        if (r->h6 == 0) {
            continue;
        }
        func_8020C130_ovl_25EE90(6, r->h6, 0);
        if (r->h0 != 0) {
            func_8020C130_ovl_25EE90(5, r->h0, 0);
        }
        if (!(r->h2 & 0x8000) && r->h2 != 0) {
            func_8020C130_ovl_25EE90(4, r->h2, 0);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020CE94_ovl_25EE90);

/* Issues the load requests for every entry of a sprite list (kinds 6/5, then `kind` for id + base) */
#ifdef NON_MATCHING
/* list ptr and count registers swapped (s1/s2) and prologue order differs */
void func_8020D024_ovl_25EE90(u8 *spr, s32 kind, s32 base) {
    u16 *e = FIELD(spr, u16 *, 0xC);
    s32 n;

    for (n = FIELD(spr, s32, 4); n > 0; n--, e += 5) {
        if (e[3] == 0) {
            continue;
        }
        func_8020C130_ovl_25EE90(6, e[3], 0);
        if (e[0] != 0) {
            func_8020C130_ovl_25EE90(5, e[0], 0);
        }
        if (e[1] & 0x8000) {
            continue;
        }
        func_8020C130_ovl_25EE90(kind, e[1] + base, 0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020D024_ovl_25EE90);
#endif
