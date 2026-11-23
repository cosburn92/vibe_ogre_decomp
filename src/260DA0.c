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
void func_8020C4EC_ovl_25EE90(void *p);
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

extern s32 D_80220210_ovl_25EE90[];
s32 ChunkSize(s32 id);
void *LoadChunkRaw(void *dst, s32 id);

/* Loads entry k (> 0) of index chunk D_80220210[set] into the shared buffer unless it is already
 * there; hangs on a bad index or size */
inline void func_8020C250_ovl_25EE90(u16 set, s32 k) {
    s32 id;
    s32 n;

    if (k > 0 && (id = D_80220210_ovl_25EE90[set]) != 0) {
        if ((u16)D_80220D40_ovl_25EE90 != set || D_80220D44_ovl_25EE90 != id || D_80220D48_ovl_25EE90 != k) {
            n = ChunkSize(id);
            if (k >= n / 4) {
                while (1) {
                }
            }
            if (n == 0 || n > 0x7FFF) {
                while (1) {
                }
            }
            LoadChunkRaw(D_80220F20_ovl_25EE90, id);
            n = ChunkSize(((s32 *)D_80220F20_ovl_25EE90)[k]);
            if (n == 0 || n > 0x7FFF) {
                while (1) {
                }
            }
            LoadChunkRaw(D_80220F20_ovl_25EE90, ((s32 *)D_80220F20_ovl_25EE90)[k]);
        }
        return;
    }
    while (1) {
    }
}

s32 ReadU32BE(void *p);
void DecodeLZ(void *dst, void *src);

/* Loads entry id of resource set `kind` (func_8020C250) and returns an LZ-decoded copy */
void *func_8020C380_ovl_25EE90(s32 kind, s32 id) {
    void *src;
    void *p;

    func_8020C250_ovl_25EE90(kind, id);
    src = D_80220F20_ovl_25EE90;
    p = HMalloc(ReadU32BE(src));
    if (p != NULL) {
        DecodeLZ(p, src);
        return p;
    }
    while (1) {
    }
}

/* Turns the offsets in a loaded model blob into pointers */
void func_8020C4EC_ovl_25EE90(void *mv) {
    u8 *m = mv;
    u32 i;
    u32 k;
    u32 *p;
    u32 *q;

    FIELD(m, u32, 0x8) += (u32)m;
    FIELD(m, u32, 0xC) += (u32)m;
    FIELD(m, u32, 0x10) += (u32)m;
    if (FIELD(m, u32, 0x14) != 0) {
        FIELD(m, u32, 0x14) += (u32)m;
    }
    FIELD(m, u32, 0x18) += (u32)m;
    for (i = 0; i < FIELD(m, u32, 4); i++) {
        p = (u32 *)(i * 4 + (u32)FIELD(m, u32 *, 8));
        if (*p != 0) {
            *p += (u32)m;
            q = (u32 *)FIELD(m, u32 *, 8)[i];
            for (k = 0; k < 10; k++, q++) {
                if (*q != 0) {
                    *q += (u32)m;
                    *(u32 *)*q += (u32)m;
                }
            }
        }
    }
    for (i = 0; i < FIELD(m, u32, 4); i++) {
        u16 f = *(u16 *)(FIELD(m, u8 *, 0xC) + i * 10 + 2);

        if (f & 0x8000) {
            k = f & 0x7FFF;
            FIELD(m, u32 *, 0x14)[k] += (u32)m;
        }
    }
    for (i = 0; i < FIELD(m, u32, 4); i++) {
        p = (u32 *)(i * 4 + (u32)FIELD(m, u32 *, 0x18));
        if (*p != 0) {
            *p += (u32)m;
        }
    }
}

/* Kind-3 resource id: cached copy, or loaded into a new cache entry */
void *func_8020C644_ovl_25EE90(s32 id) {
    void *r = NULL;
    CacheEnt *e;

    if (id > 0) {
        r = func_8020BF5C_ovl_25EE90(3, id, 0);
        if (r != NULL) {
            func_8020BF94_ovl_25EE90(r);
            return r;
        }
        e = func_8020BFE8_ovl_25EE90();
        if (e != NULL) {
            r = func_8020C380_ovl_25EE90(3, id);
            if (r != NULL) {
                func_8020C4EC_ovl_25EE90(r);
                e->h0 = 1;
                e->data = r;
                e->kind = 3;
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

inline void *func_8020C704_ovl_25EE90(s32 id) {
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

inline void *func_8020C7B8_ovl_25EE90(s32 id) {
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

inline void *func_8020C860_ovl_25EE90(s32 id) {
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

inline void *func_8020C908_ovl_25EE90(s32 id) {
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

inline void *func_8020C9B0_ovl_25EE90(s32 id) {
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

/* Acquires resource id of kind 4, 7 or 8 */
#ifdef NON_MATCHING
/* the three inlined acquires (func_8020C704/C908/C9B0) share their tails differently: the original cross-jumps the cache-entry stores and the add-ref path between the cases */
void *func_8020CA58_ovl_25EE90(u16 kind, s32 id) {
    void *r;

    switch (kind) {
    default:
        while (1) {
        }
    case 4:
        r = func_8020C704_ovl_25EE90(id);
        break;
    case 7:
        r = func_8020C908_ovl_25EE90(id);
        break;
    case 8:
        r = func_8020C9B0_ovl_25EE90(id);
        break;
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/260DA0", func_8020CA58_ovl_25EE90);
#endif

/* Loads the resources of each record of s (kind 6 h6, kind 5 h0, kind 4 h2); 1 if any record is
 * flagged 0x8000 instead of having a kind-4 resource */
s32 func_8020CC00_ovl_25EE90(RecSet *s) {
    s32 r = 0;
    Rec10b *rec = s->recs;
    s32 n;

    for (n = s->n; n > 0; n--, rec++) {
        if (rec->h6 != 0) {
            func_8020C860_ovl_25EE90(rec->h6);
            func_8020C7B8_ovl_25EE90(rec->h0);
            if (rec->h2 & 0x8000) {
                r = 1;
            } else if (rec->h2 != 0) {
                func_8020C704_ovl_25EE90(rec->h2);
            }
        }
    }
    return r;
}

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

/* Loads the resources of each record of s (kind-6 h6 and kind-5 h0 by id) and starts its
 * animation h2 + b on channel a; 1 if any record is flagged 0x8000 instead */
s32 func_8020CE94_ovl_25EE90(RecSet *s, u16 a, s32 b) {
    s32 r = 0;
    Rec10b *rec = s->recs;
    s32 n;

    for (n = s->n; n > 0; n--, rec++) {
        if (rec->h6 != 0) {
            func_8020C860_ovl_25EE90(rec->h6);
            func_8020C7B8_ovl_25EE90(rec->h0);
            if (rec->h2 & 0x8000) {
                r = 1;
            } else {
                func_8020CA58_ovl_25EE90(a, rec->h2 + b);
            }
        }
    }
    return r;
}

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
