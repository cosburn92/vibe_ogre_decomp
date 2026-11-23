#include "common.h"
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))

/* 267750 */

typedef struct {
    /* 0x0 */ u8 unk0[4];
    /* 0x4 */ s32 x;
    /* 0x8 */ s32 y;
    /* 0xC */ s32 z;
} Pos26;

typedef struct {
    /* 0x0 */ u8 unk0[8];
    /* 0x8 */ f32 f8;
    /* 0xC */ s32 wC;
} Obj26;

typedef struct {
    /* 0x00 */ u8 unk00[0x30];
    /* 0x30 */ f32 x;
    /* 0x34 */ f32 y;
    /* 0x38 */ f32 z;
    /* 0x3C */ u8 unk3C[4];
    /* 0x40 */ f32 f40;
} Src26; /* size 0x44 */

typedef struct {
    u8 unk0[4];
    s32 n;
} Cnt26;

typedef struct {
    /* 0x0 */ u8 unk0[4];
    /* 0x4 */ Cnt26 *cnt;
    /* 0x8 */ u8 unk8[4];
    /* 0xC */ void **list;
} Set26;

void func_801ADADC(void *p);
void func_8020D280_ovl_25EE90(void *p);
void func_8020E51C_ovl_25EE90(void *p);
typedef struct {
    /* 0x0 */ u8 unk0[6];
    /* 0x6 */ u16 h6;
    /* 0x8 */ u8 unk8[2];
} Rec10; /* size 0xA */
typedef struct {
    /* 0x0 */ u8 unk0[4];
    /* 0x4 */ u32 n;
    /* 0x8 */ u8 unk8[4];
    /* 0xC */ Rec10 *recs;
} Set38;
void HFree(void *p);
void func_8020C9B0_ovl_25EE90(s16 a);
void func_8020C130_ovl_25EE90(s32 a, s16 b, s32 c);
s32 func_8020D174_ovl_25EE90();
s32 func_8020E4C4_ovl_25EE90();
void func_8020CDF4_ovl_25EE90(Cnt26 *c);
void func_8020C074_ovl_25EE90(Cnt26 *c);
void func_8020D024_ovl_25EE90(Cnt26 *c, u16 a, s32 b, u16 d, s32 e);
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void _bcopy(const void *src, void *dst, s32 n);
void func_80215654_ovl_25EE90();
void func_802148C0_ovl_25EE90();
void guMtxCatF(void *a, void *b, void *out);
void *func_8020C644_ovl_25EE90(s32 id);
u16 func_8020CC00_ovl_25EE90(void *mdl);
void func_80213980_ovl_25EE90(void *mdl, void *mtx, void *slots);
void func_8021404C_ovl_25EE90(void *mdl, void *mtx, void *slots);
void *HMalloc(s32 size);
void bzero(void *p, s32 n);
void guRotateRPYF(f32 mf[4][4], f32 r, f32 p, f32 h);
/* --- end decls --- */

void func_80212BA0_ovl_25EE90(s32 n, Obj26 **arr) {
    s32 pad;
    s32 i;

    for (i = 0; i < n; i++) {
        if (arr[i] != NULL) {
            arr[i]->wC = 1;
        }
    }
}

void func_80212BD8_ovl_25EE90(s32 n, Obj26 **arr, s32 d) {
    s32 pad;
    s32 i;

    for (i = 0; i < n; i++) {
        if (arr[i] != NULL) {
            arr[i]->f8 += d;
        }
    }
}

void func_80212C20_ovl_25EE90(s32 n, Pos26 **arr, s32 d) {
    s32 pad;
    s32 i;
    Pos26 *p;

    for (i = 0; i < n; i++) {
        p = arr[i];
        if (p != NULL) {
            p->x += d;
            p->y += d;
            p->z += d;
        }
    }
}

void func_80212C78_ovl_25EE90(s16 (*t)[2]) {
    s32 i;

    for (i = 0; t[i][0] != -1 || t[i][1] != 0; i++) {
        func_8020C9B0_ovl_25EE90(t[i][1]);
    }
}

void func_80212CF4_ovl_25EE90(s16 (*t)[2]) {
    s32 i;

    for (i = 0; t[i][0] != -1 || t[i][1] != 0; i++) {
        func_8020C130_ovl_25EE90(8, t[i][1], 0);
    }
}

/* Looks up key in a sorted (key, value) table ending with (-1, 0); falls back to the entry below */
#ifdef NON_MATCHING
/* Loop layout differs: the target re-tests from the top with an index register and no rotation. */
s16 func_80212D78_ovl_25EE90(s32 key, s16 (*t)[2]) {
    s32 i = 0;

loop:
    if (t[i][0] == -1 && t[i][1] == 0) {
        goto below;
    }
    if (key == t[i][0]) {
        goto found;
    }
    if (key < t[i][0]) {
        goto below;
    }
    i++;
    goto loop;
below:
    i--;
    if (i < 0) {
        i = 0;
    }
found:
    return t[i][1];
}
#else
INCLUDE_ASM("asm/nonmatchings/267750", func_80212D78_ovl_25EE90);
#endif

INCLUDE_ASM("asm/nonmatchings/267750", func_80212DE0_ovl_25EE90);

/* Matrix from scale (0-2), rotation in degrees (3-5) and translation (6-8) */
void func_802131E8_ovl_25EE90(f32 *srt, f32 m[4][4]) {
    guRotateRPYF(m, srt[3], srt[4], srt[5]);
    m[0][0] *= srt[0];
    m[0][1] *= srt[0];
    m[0][2] *= srt[0];
    m[1][0] *= srt[1];
    m[1][1] *= srt[1];
    m[1][2] *= srt[1];
    m[2][0] *= srt[2];
    m[2][1] *= srt[2];
    m[2][2] *= srt[2];
    m[3][0] = srt[6];
    m[3][1] = srt[7];
    m[3][2] = srt[8];
}

/* Effect transform tracks (same code as 1CE070 func_80199968; shapes from OB64-Decomp's
 * E06TransformInput/Output, MIT, (c) 2026 rempred) */
typedef struct {
    f32 m[4][4];
    f32 alpha;
} TrackOut267;

typedef struct {
    u32 unk00;
    u32 count;
    void ***curves;
    u8 unk0C[0xC];
    f32 **values;
} TrackIn267;

f32 func_80212DE0_ovl_25EE90(void *curve, f32 t);

static inline void Track267_ApplyValues(f32 *v, f32 m[4][4]) {
    guRotateRPYF(m, v[3], v[4], v[5]);
    m[0][0] *= v[0];
    m[0][1] *= v[0];
    m[0][2] *= v[0];
    m[1][0] *= v[1];
    m[1][1] *= v[1];
    m[1][2] *= v[1];
    m[2][0] *= v[2];
    m[2][1] *= v[2];
    m[2][2] *= v[2];
    m[3][0] = v[6];
    m[3][1] = v[7];
    m[3][2] = v[8];
}

/* Evaluates the ten curves at t into v (null curves keep their value) and builds out from them */
inline void func_802132D0_ovl_25EE90(f32 t, void **curves, TrackOut267 *out, f32 *v) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (curves[i] != NULL) {
            v[i] = func_80212DE0_ovl_25EE90(curves[i], t);
        }
    }
    Track267_ApplyValues(v, out->m);
    out->alpha = v[9];
}


/* Evaluates frame `frame` (30 fps) of an effect's transform tracks into matrices */
void func_80213420_ovl_25EE90(s32 frame, TrackIn267 *in, TrackOut267 *out) {
    f32 values[10];
    f32 t = (f32)frame / 30.0f;
    u32 item;
    u32 k;

    for (item = 0; item < in->count; item++) {
        for (k = 0; k < 9; k++) {
            values[k] = in->values[item][k];
        }
        values[9] = 1.0f;
        if (in->curves[item] != NULL) {
            func_802132D0_ovl_25EE90(t, in->curves[item], &out[item], values);
        } else {
            Track267_ApplyValues(values, out[item].m);
            out[item].alpha = 1.0f;
        }
    }
}

/* Composes the bone matrices of skeleton sk (parent links in sk+0x10) onto root */
typedef struct {
    u16 node;
    u16 parent;
} Link26;
void func_802136F4_ovl_25EE90(void *root, u8 *sk, u8 *mtx) {
    void *stk[32];
    u32 i;

    stk[0] = root;
    for (i = 0; i < FIELD(sk, u32, 4); i++) {
        u16 node = FIELD(sk, Link26 *, 0x10)[i].node;
        u16 parent = FIELD(sk, Link26 *, 0x10)[i].parent;
        u8 *m = mtx + node * 0x44;

        guMtxCatF(m, stk[parent], m);
        stk[parent + 1] = m;
    }
}

void func_802137A8_ovl_25EE90(s32 n, void **arr) {
    s32 pad;
    s32 i;

    for (i = 0; i < n; i++) {
        if (arr[i] != NULL) {
            func_801ADADC(arr[i]);
        }
    }
}

void func_80213804_ovl_25EE90(s32 n, Src26 *src, Obj26 **arr) {
    s32 pad;
    s32 i;

    for (i = 0; i < n; i++) {
        if (arr[i] != NULL) {
            arr[i]->f8 = src[i].z * 30.0f;
        }
    }
}

void func_80213850_ovl_25EE90(s32 n, Src26 *src, Pos26 **arr) {
    s32 pad;
    s32 i;

    for (i = 0; i < n; i++) {
        if (arr[i] != NULL) {
            arr[i]->x = src[i].x * 30.0f;
            arr[i]->y = src[i].y * 30.0f;
            arr[i]->z = src[i].z * 30.0f;
        }
    }
}

void func_802138C8_ovl_25EE90(s32 n, Src26 *src, f32 v) {
    s32 pad;
    s32 i;

    for (i = 0; i < n; i++, src++) {
        src->f40 = v;
    }
}

inline void func_802138FC_ovl_25EE90(Set38 *s, s32 *out) {
    u32 i;

    for (i = 0; i < s->n; i++) {
        if (s->recs[i].h6 != 0) {
            out[i] = func_8020D174_ovl_25EE90();
        } else {
            out[i] = 0;
        }
    }
}

void *func_8020BF5C_ovl_25EE90(s32 kind, s32 id, s32 c);
void func_8020F134_ovl_25EE90();

/* Binds model mdl's bone slots: draw routine, bone matrix (0x44 each) and the cached kind-6 mesh,
 * kind-5 texture and kind-4 animation of each record (hangs when one is missing) */
#ifdef NON_MATCHING
/* 82/82 instructions, 2 words differ: i = 0 lands in the branch delay slot in the original, slots copy after it */
void func_80213980_ovl_25EE90(void *mdl, void *mtx, void *slots) {
    s32 pad[2];

    if (((Set38 *)mdl)->n != 0) {
        u8 **sl = slots;
        u8 *m = mtx;
        s32 off = 0;
        u32 i = 0;

    loop:
        if (*sl != NULL) {
            u8 *o;
            u8 *d;
            u16 *r;

            FIELD(*sl, void *, 0) = func_8020F134_ovl_25EE90;
            o = *sl;
            d = o + 0x18;
            bzero(d, 0x18);
            r = (u16 *)((u8 *)((Set38 *)mdl)->recs + off);
            if (r[3] != 0) {
                FIELD(o, u8 *, 0x1C) = m;
                if ((FIELD(o, void *, 0x2C) = func_8020BF5C_ovl_25EE90(6, r[3], 0)) == NULL) {
                    while (1) {
                    }
                }
                if (r[0] != 0) {
                    if ((FIELD(d, void *, 8) = func_8020BF5C_ovl_25EE90(5, r[0], 0)) == NULL) {
                        while (1) {
                        }
                    }
                }
                FIELD(d, u16, 0x10) = r[2];
                if (r[1] != 0 && !(r[1] & 0x8000)) {
                    if ((FIELD(d, void *, 0xC) = func_8020BF5C_ovl_25EE90(4, r[1], 0)) == NULL) {
                        while (1) {
                        }
                    }
                }
            }
        }
        m += 0x44;
        off += 0xA;
        i++;
        sl++;
        if (i < ((Set38 *)mdl)->n) {
            goto loop;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/267750", func_80213980_ovl_25EE90);
#endif

/* Instantiates model id: bone matrices (0x44 each) plus a slot table, 64-byte aligned */
void func_80213AC8_ovl_25EE90(u8 *m, s32 id) {
    u8 *mdl;
    u32 size;

    FIELD(m, s32, 0) = id;
    mdl = func_8020C644_ovl_25EE90(id);
    FIELD(m, u8 *, 4) = mdl;
    size = FIELD(mdl, u32, 4) * 0x44 + FIELD(mdl, u32, 4) * 4;
    if (size & 0x3F) {
        size = (size & ~0x3F) + 0x40;
    }
    FIELD(m, u8 *, 0x14) = HMalloc(size);
    bzero(FIELD(m, u8 *, 0x14), size);
    FIELD(m, u8 *, 8) = FIELD(m, u8 *, 0x14);
    FIELD(m, u8 *, 0xC) = FIELD(m, u8 *, 0x14) + FIELD(mdl, u32, 4) * 0x44;
    func_802138FC_ovl_25EE90((Set38 *)mdl, FIELD(m, s32 *, 0xC));
    FIELD(m, u16, 0x10) = func_8020CC00_ovl_25EE90(mdl);
    func_80213980_ovl_25EE90(mdl, FIELD(m, void *, 8), FIELD(m, void *, 0xC));
}

inline void func_80213BE8_ovl_25EE90(Set26 *s) {
    s32 pad;
    s32 n = s->cnt->n;
    void **list = s->list;
    s32 i;

    for (i = 0; i < n; i++) {
        if (list[i] != NULL) {
            func_8020D280_ovl_25EE90(list[i]);
            list[i] = NULL;
        }
    }
}

void func_80213C50_ovl_25EE90(Set26 *s) {
    func_8020CDF4_ovl_25EE90(s->cnt);
    func_80213BE8_ovl_25EE90(s);
    HFree(FIELD(s, void *, 0x14));
    func_8020C074_ovl_25EE90(s->cnt);
}

INCLUDE_ASM("asm/nonmatchings/267750", func_80213CE0_ovl_25EE90);

void func_80213F28_ovl_25EE90(Set26 *s, u16 a, s32 b, u16 d, s32 e) {
    func_8020D024_ovl_25EE90(s->cnt, a, b, d, e);
    func_80213BE8_ovl_25EE90(s);
    HFree(FIELD(s, void *, 0x14));
    func_8020C074_ovl_25EE90(s->cnt);
}

inline void func_80213FC8_ovl_25EE90(Set38 *s, s32 *out) {
    u32 i;

    for (i = 0; i < s->n; i++) {
        if (s->recs[i].h6 != 0) {
            out[i] = func_8020E4C4_ovl_25EE90();
        } else {
            out[i] = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/267750", func_8021404C_ovl_25EE90);

/* Instantiates model id: bone matrices (0x44 each) plus a slot table, 64-byte aligned */
void func_8021419C_ovl_25EE90(u8 *m, s32 id) {
    u8 *mdl;
    u32 size;

    FIELD(m, s32, 0) = id;
    mdl = func_8020C644_ovl_25EE90(id);
    FIELD(m, u8 *, 4) = mdl;
    size = FIELD(mdl, u32, 4) * 0x44 + FIELD(mdl, u32, 4) * 4;
    if (size & 0x3F) {
        size = (size & ~0x3F) + 0x40;
    }
    FIELD(m, u8 *, 0x14) = HMalloc(size);
    bzero(FIELD(m, u8 *, 0x14), size);
    FIELD(m, u8 *, 8) = FIELD(m, u8 *, 0x14);
    FIELD(m, u8 *, 0xC) = FIELD(m, u8 *, 0x14) + FIELD(mdl, u32, 4) * 0x44;
    func_80213FC8_ovl_25EE90((Set38 *)mdl, FIELD(m, s32 *, 0xC));
    FIELD(m, u16, 0x10) = func_8020CC00_ovl_25EE90(mdl);
    func_8021404C_ovl_25EE90(mdl, FIELD(m, void *, 8), FIELD(m, void *, 0xC));
}

inline void func_802142BC_ovl_25EE90(Set26 *s) {
    s32 pad;
    s32 n = s->cnt->n;
    void **list = s->list;
    s32 i;

    for (i = 0; i < n; i++) {
        if (list[i] != NULL) {
            func_8020E51C_ovl_25EE90(list[i]);
            list[i] = NULL;
        }
    }
}

void func_80214324_ovl_25EE90(Set26 *s) {
    func_8020CDF4_ovl_25EE90(s->cnt);
    func_802142BC_ovl_25EE90(s);
    HFree(FIELD(s, void *, 0x14));
    func_8020C074_ovl_25EE90(s->cnt);
}

typedef struct {
    s16 frame;
    s16 val;
} Key26;
s32 func_8020EC2C_ovl_25EE90(s32 kind, s32 val);

/* Applies frame `frame` of model mdl's keyed tracks (record flag 0x8000) to the slots: each slot
 * gets the value of the last key at or before the frame */
#ifdef NON_MATCHING
/* 78/78 instructions, 13 words differ: frame, record offset and slot pointer rotate through s2-s5 */
void func_802143B4_ovl_25EE90(s32 frame, Set38 *mdl, s32 *slots) {
    u32 i;

    if (FIELD(mdl, s32, 0) >= frame) {
        for (i = 0; i < mdl->n; i++) {
            if (slots[i] != 0) {
                u16 f = FIELD(&mdl->recs[i], u16, 2);
                u8 *o = (u8 *)slots[i] + 0x18;

                if (f & 0x8000) {
                    Key26 *k = FIELD(mdl, Key26 **, 0x14)[f & 0x7FFF];
                    s32 j = 0;

                loop:
                    if (k[j].frame == -1 && k[j].val == 0) {
                        j--;
                    } else if (frame == k[j].frame) {
                        goto found;
                    } else if (frame < k[j].frame) {
                        j--;
                    } else {
                        j++;
                        goto loop;
                    }
                    if (j < 0) {
                        j = 0;
                    }
                found:
                    FIELD(o, s32, 0xC) = func_8020EC2C_ovl_25EE90(7, k[j].val);
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/267750", func_802143B4_ovl_25EE90);
#endif

INCLUDE_ASM("asm/nonmatchings/267750", func_802144EC_ovl_25EE90);

/* As func_802143B4 for the other slot layout (value at +0x20): applies frame `frame` of model mdl's keyed tracks (record flag 0x8000) to the slots: each slot
 * gets the value of the last key at or before the frame */
#ifdef NON_MATCHING
/* same as func_802143B4 */
void func_8021463C_ovl_25EE90(s32 frame, Set38 *mdl, s32 *slots) {
    u32 i;

    if (FIELD(mdl, s32, 0) >= frame) {
        for (i = 0; i < mdl->n; i++) {
            if (slots[i] != 0) {
                u16 f = FIELD(&mdl->recs[i], u16, 2);
                u8 *o = (u8 *)slots[i] + 0x14;

                if (f & 0x8000) {
                    Key26 *k = FIELD(mdl, Key26 **, 0x14)[f & 0x7FFF];
                    s32 j = 0;

                loop:
                    if (k[j].frame == -1 && k[j].val == 0) {
                        j--;
                    } else if (frame == k[j].frame) {
                        goto found;
                    } else if (frame < k[j].frame) {
                        j--;
                    } else {
                        j++;
                        goto loop;
                    }
                    if (j < 0) {
                        j = 0;
                    }
                found:
                    FIELD(o, s32, 0xC) = func_8020EC2C_ovl_25EE90(7, k[j].val);
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/267750", func_8021463C_ovl_25EE90);
#endif

/* Converts object o to the func_80215654 layout (rebuilds its body from +0x1C) */
void func_80214774_ovl_25EE90(u8 *o) {
    u8 b[0x70];

    FIELD(o, void *, 4) = func_80215654_ovl_25EE90;
    _bcopy(o + 0x1C, b, 0x40);
    _bcopy(o + 0x68, b + 0x48, 0x18);
    FIELD(b, f32, 0x40) = FIELD(o, f32, 0x5C);
    FIELD(b, u16, 0x44) = FIELD(o, u16, 0x66);
    FIELD(b, u16, 0x60) = FIELD(o, u16, 0x80);
    FIELD(b, u16, 0x62) = FIELD(o, u16, 0x82);
    FIELD(b, s32, 0x64) = FIELD(o, s32, 0x84);
    FIELD(b, s32, 0x68) = FIELD(o, s32, 0x88);
    FIELD(b, s32, 0x6C) = FIELD(o, s32, 0x8C);
    _bcopy(b, o + 0x1C, 0x70);
}

/* Converts object o to the func_802148C0 layout */
void func_80214814_ovl_25EE90(u8 *o) {
    u8 b[0x74];

    FIELD(o, void *, 4) = func_802148C0_ovl_25EE90;
    _bcopy(o + 0x1C, b, 0x40);
    _bcopy(o + 0x64, b + 0x4C, 0x18);
    FIELD(b, f32, 0x40) = FIELD(o, f32, 0x5C);
    FIELD(b, u16, 0x4A) = FIELD(o, u16, 0x60);
    FIELD(b, u16, 0x64) = FIELD(o, u16, 0x7C);
    FIELD(b, u16, 0x66) = FIELD(o, u16, 0x7E);
    FIELD(b, s32, 0x68) = FIELD(o, s32, 0x80);
    FIELD(b, s32, 0x6C) = FIELD(o, s32, 0x84);
    FIELD(b, s32, 0x70) = FIELD(o, s32, 0x88);
    _bcopy(b, o + 0x1C, 0x74);
}
