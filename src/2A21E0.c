#include "common.h"
#include "chunk.h"
#include "heap.h"

/* 2A21E0 */

typedef struct {
    /* 0x00 */ s32 id;
    /* 0x04 */ s32 chunk;
    /* 0x08 */ s32 *p08;
    /* 0x0C */ s32 kind;
    /* 0x10 */ u32 n;
    /* 0x14 */ void *p14;
    /* 0x18 */ u8 unk18[4];
    /* 0x1C */ void **list;
    /* 0x20 */ u32 *age;
    /* 0x24 */ u8 *p24;
    /* 0x28 */ s32 w28;
    /* 0x2C */ s32 w2C;
    /* 0x30 */ u8 *w30;
    /* 0x34 */ u8 *p34;
    /* 0x38 */ void *p38;
} Rec2A; /* size 0x3C */

extern Rec2A *D_802395B0_ovl_29A4C0;
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern u8 *D_8022A974;

void bzero(void *p, s32 n);
void nuGfxTaskAllEndWait(void);
Rec2A *func_80232C28_ovl_29A4C0(s32 id, s32 kind);
void func_801BFBA0(void *p);
void _bcopy(void *src, void *dst, s32 n);
void DecodeLZ(void *dst, void *src);
s32 func_801C2304(void);
void *func_801C15E0(u8 *img, u32 pal, u8 *palData, u8 *out, s32 flag);
u32 func_801BE9A8(s32 siz, u32 w);
void func_80080998(u8 *dst, u8 *src, u32 n);
/* --- end decls --- */

void func_802329B0_ovl_29A4C0(void) {
    Rec2A *p = HMalloc(0x960);

    D_802395B0_ovl_29A4C0 = p;
    bzero(p, 0x960);
}

/* Frees every record's buffers; the table itself too unless keep is set */
void func_802329E0_ovl_29A4C0(s32 keep) {
    u32 i;
    u32 k;

    if (D_802395B0_ovl_29A4C0 == NULL) {
        return;
    }
    for (i = 0; i < 40; i++) {
        for (k = 0; k < D_802395B0_ovl_29A4C0[i].n; k++) {
            if (D_802395B0_ovl_29A4C0[i].list[k] != NULL) {
                HFree(D_802395B0_ovl_29A4C0[i].list[k]);
            }
        }
        HFree(D_802395B0_ovl_29A4C0[i].age);
        HFree(D_802395B0_ovl_29A4C0[i].p08);
        HFree((void *)D_802395B0_ovl_29A4C0[i].w2C);
        HFree((void *)D_802395B0_ovl_29A4C0[i].w28);
        HFree(D_802395B0_ovl_29A4C0[i].p38);
        HFree(D_802395B0_ovl_29A4C0[i].p14);
    }
    if (!keep) {
        HFree(D_802395B0_ovl_29A4C0);
        D_802395B0_ovl_29A4C0 = NULL;
    }
}

/* Frees the record for (id, kind) and clears it */
static inline void Rec2AFree(s32 id, s32 kind) {
    Rec2A *r;
    u32 i;
    u32 k;

    if (D_802395B0_ovl_29A4C0 == NULL) {
        return;
    }
    r = D_802395B0_ovl_29A4C0;
    for (i = 0; i < 40; r++, i++) {
        if (r->id == id && r->kind == kind) {
            for (k = 0; k < r->n; k++) {
                if (r->list[k] != NULL) {
                    HFree(r->list[k]);
                    r->list[k] = NULL;
                }
            }
            HFree(r->age);
            HFree(r->p08);
            HFree((void *)r->w2C);
            HFree((void *)r->w28);
            HFree(r->p38);
            HFree(r->p14);
            bzero(r, 0x3C);
            return;
        }
    }
}

void func_80232B20_ovl_29A4C0(s32 id, s32 kind) {
    Rec2AFree(id, kind);
}

/* Takes a free record for id: loads its chunk list from 0x109F95E and the four chunks it names */
Rec2A *func_80232C28_ovl_29A4C0(s32 id, s32 kind) {
    Rec2A *r = D_802395B0_ovl_29A4C0;
    s32 i = 39;
    s32 *tbl;
    u32 *hdr;
    u32 a;
    u32 b;
    u8 *m;

    while (1) {
        if (r->id == 0) {
            break;
        }
        r++;
        if (i-- == 0) {
            break;
        }
    }
    r->id = id;
    tbl = HMalloc(ChunkSize(0x109F95E));
    LoadChunkRaw(tbl, 0x109F95E);
    r->chunk = tbl[r->id - 1];
    r->p08 = HMalloc(ChunkSize(r->chunk));
    LoadChunkRaw(r->p08, r->chunk);
    HFree(tbl);
    r->w2C = (s32)LoadChunk(r->p08[0]);
    r->w28 = (s32)LoadChunk(r->p08[1]);
    hdr = LoadChunk(r->p08[2]);
    r->p38 = LoadChunk(r->p08[3]);
    r->kind = kind;
    r->n = hdr[0];
    b = (r->n + 7) & ~7;
    a = (r->n * 4 + 7) & ~7;
    m = HMalloc(b * 3 + a);
    r->p14 = m;
    r->list = (void **)m;
    r->w30 = m + a;
    r->p24 = m + a + b;
    r->p34 = m + a + b + b;
    r->age = HMalloc(a);
    bzero(r->age, a);
    bzero(r->list, a);
    bzero(r->p24, b);
    _bcopy(hdr + 8, r->w30, r->n);
    _bcopy((u8 *)hdr + hdr[7], r->p34, r->n);
    HFree(hdr);
    return r;
}

/* The record pointer and derived field pointer use swapped registers. */
s32 func_80232DE0_ovl_29A4C0(s32 id, s32 kind)
{
  Rec2A *r = D_802395B0_ovl_29A4C0;
  s32 i;
  for (i = 40; (i--) != 0; r++)
  {
    if ((r->id == id) && (r->kind == kind))
    {
      return r->w2C;
    }
  }

  r = func_80232C28_ovl_29A4C0(id, kind);
  return r->w2C;
}

/* The record pointer and derived field pointer use swapped registers. */
s32 func_80232E44_ovl_29A4C0(s32 id, s32 kind)
{
  Rec2A *r = D_802395B0_ovl_29A4C0;
  s32 i;
  for (i = 40; (i--) != 0; r++)
  {
    if ((r->id == id) && (r->kind == kind))
    {
      return r->w28;
    }
  }

  r = func_80232C28_ovl_29A4C0(id, kind);
  return r->w28;
}

u8 func_80232EA8_ovl_29A4C0(s32 id, s32 k) {
    Rec2A *r = D_802395B0_ovl_29A4C0;
    s32 i;

    for (i = 40; i-- != 0; r++) {
        if (r->id == id) {
            return r->w30[k];
        }
    }
    return 0;
}

/* Image n of the record for (id, kind), loading and unpacking it on first use: "UT" images are
 * converted with palette set p34[n], "64" images are copied as is. Resets the entry's age. */
void *func_80232EE8_ovl_29A4C0(s32 id, u32 *idx, u8 *outPal, s32 side, u8 kind) {
    u32 n = *idx;
    u32 i;
    Rec2A *r;
    u8 *raw;
    u8 *img;
    u8 *pal;
    void *res;
    s32 flag;
    u32 size;

    for (i = 0; i < 40; i++) {
        r = &D_802395B0_ovl_29A4C0[i];
        if (r->id != id || r->kind != kind) {
            continue;
        }
        if (r->list[n] == NULL) {
            raw = func_80071C04(ChunkSize(r->p08[n + 4]));
            LoadChunkRaw(raw, r->p08[n + 4]);
            img = func_80071C04(ReadU32BE(raw));
            DecodeLZ(img, raw);
            HFree(raw);
            if (*(u16 *)img == 0x5554) {
                flag = 0;
                pal = (u8 *)r->p38 + (r->p34[n] << 9);
                if (FIELD(D_8022A974, u8 *, 0x1A48) != NULL &&
                    FIELD(FIELD(D_8022A974, u8 *, 0x1A48), s16, 4) != side) {
                    flag = func_801C2304() & 1;
                }
                if (FIELD(D_8022A974, u8 *, 0x1CA4) != NULL) {
                    flag &= -(*FIELD(D_8022A974, u8 *, 0x1CA4) != 3);
                }
                res = func_801C15E0(img, kind < img[2] ? kind : 0, pal, r->p24 + n, flag);
                HFree(img);
            } else if (*(u16 *)(res = img) == 0x3634) {
                size = func_801BE9A8(((u8 *)res)[3], *(u16 *)((u8 *)res + 4)) * *(u16 *)((u8 *)res + 6) + 8;
                res = HMalloc(size);
                func_80080998(res, img, size);
            } else {
                goto done;
            }
            r->list[n] = res;
        }
    done:
        if (outPal != NULL) {
            *outPal = r->p24[n];
        }
        r->age[n] = 0;
        return r->list[n];
    }
    return NULL;
}

/* Frees the record for (id, kind) unless a unit with that id and kind has a different w */
void func_80233134_ovl_29A4C0(s32 id, s32 w, s32 kind) {
    u32 i;
    u8 *u;

    nuGfxTaskAllEndWait();
    for (i = 0; i < 28; i++) {
        u = FIELD(D_8022A974, u8 *, 0x18 + i * 4);
        if (u != NULL && FIELD(u, s32, 0xE8) == id && kind == u[0x146] && w != FIELD(u, s32, 0xE4)) {
            break;
        }
    }
    if (i == 28) {
        Rec2AFree(id, kind);
    }
}

/* Ages every list entry; entries unused for 3 ticks are freed */
void func_802332A0_ovl_29A4C0(void) {
    Rec2A *r;
    u32 i;
    u32 k;

    if (D_802395B0_ovl_29A4C0 == NULL) {
        return;
    }
    for (i = 0; i < 40; i++) {
        r = &D_802395B0_ovl_29A4C0[i];
        for (k = 0; k < D_802395B0_ovl_29A4C0[i].n; k++) {
            if (r->list[k] != NULL) {
                r->age[k]++;
                if (r->age[k] >= 3) {
                    HFree(r->list[k]);
                    r->list[k] = NULL;
                }
            }
        }
    }
}

/* Passes every non-null entry of every record's list to func_801BFBA0 */
void func_80233398_ovl_29A4C0(void) {
    Rec2A *r;
    u32 i;
    u32 k;

    if (D_802395B0_ovl_29A4C0 == NULL) {
        return;
    }
    for (i = 0; i < 40; i++) {
        r = &D_802395B0_ovl_29A4C0[i];
        for (k = 0; k < D_802395B0_ovl_29A4C0[i].n; k++) {
            if (r->list[k] != NULL) {
                func_801BFBA0(r->list[k]);
            }
        }
    }
}

/* Frees the record of the active unit (matched by id and kind) and clears it */
void func_80233448_ovl_29A4C0(void) {
    s16 side = FIELD(FIELD(D_8022A974, u8 *, 0x1A48), s16, 4);
    u8 *u;
    Rec2A *r;
    s32 id;
    s32 kind;
    u32 i;
    u32 k;

    if (side == -1) {
        return;
    }
    u = FIELD(D_8022A974, u8 *, 0x18 + side * 4);
    if (u == NULL) {
        return;
    }
    id = FIELD(u, s32, 0xE8);
    kind = u[0x146];
    if (D_802395B0_ovl_29A4C0 == NULL) {
        return;
    }
    r = D_802395B0_ovl_29A4C0;
    for (i = 0; i < 40; r++, i++) {
        if (r->id == id && r->kind == kind) {
            for (k = 0; k < r->n; k++) {
                if (r->list[k] != NULL) {
                    HFree(r->list[k]);
                    r->list[k] = NULL;
                }
            }
            HFree(r->age);
            HFree(r->p08);
            HFree((void *)r->w2C);
            HFree((void *)r->w28);
            HFree(r->p38);
            HFree(r->p14);
            bzero(r, 0x3C);
            return;
        }
    }
}

/* Waits for the GPU, then frees the cached records of all 28 battle units and 30 effect objects */
void func_80233580_ovl_29A4C0(void) {
    u8 i;
    u8 *o;

    nuGfxTaskAllEndWait();
    for (i = 0; i < 28; i++) {
        o = FIELD(D_8022A974, u8 *, 0x18 + i * 4);
        if (o != NULL) {
            Rec2AFree(FIELD(o, s32, 0xE8), o[0x146]);
        }
    }
    for (i = 0; i < 30; i++) {
        o = FIELD(D_8022A974, u8 *, 0x1AC0 + i * 4);
        if (o != NULL) {
            Rec2AFree(FIELD(o, s32, 0x30), o[0x4C]);
        }
    }
}
