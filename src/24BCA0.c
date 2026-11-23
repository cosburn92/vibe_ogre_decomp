#include "common.h"

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))

void HFree(void *p);
s32 func_801C8AC0(s32 a);
s32 func_801C8AA4(s32 a);
s32 func_801CA1C4(s32 lane, s32 row);
u8 *func_801C8FE8(s32 i);
void func_801F7344_ovl_24BCA0(u8 c, f32 *p, u8 b);
u8 *func_801F85C0_ovl_24BCA0(u8 *a, u8 *b);
u8 *func_801F885C_ovl_24BCA0(u8 *a, u8 *b);
u8 *func_801F8AF8_ovl_24BCA0(u8 *a, u8 *b, f32 c);
u8 *func_801F91BC_ovl_24BCA0(u8 *a, u8 *b, s32 c);
u8 *func_802174C0(u16 id);
void func_8020A4D0(f32 *scale, void *a, void *b);





u8 func_801F70E0_ovl_24BCA0(u8 c) {
    if (c < 20) {
        return 0;
    }
    if ((u8)(c - 20) < 27) {
        return 1;
    }
    return (u8)-((u8)(c - 47) >= 40) | 2;
}

typedef struct {
    u16 id;
    u8 kind;
    u8 pad;
    u16 flags;
} AnimReq;
extern u8 *(*D_80209718_ovl_24BCA0[])(u16 id);
extern u8 *(*D_80209728_ovl_24BCA0[])(u16 id);
extern u8 *(*D_80209734_ovl_24BCA0[])(u16 id);
extern u8 *(*D_80209740_ovl_24BCA0[])(u16 id, u8 x);
extern u8 *(*D_8020974C_ovl_24BCA0[])(u16 id, s32 a, s32 x, s32 b, s32 y);
extern s32 D_8020A170_ovl_24BCA0[];
u8 *func_80214CF0(u16 id, s32 a);
extern s32 (*D_80209700_ovl_24BCA0[])(u8 c);
extern u32 D_8020A2D4_ovl_24BCA0;
extern u8 *D_80209770_ovl_24BCA0[];
void func_80218104(f32 x, f32 y, s32 z, s32 w);
s32 func_801C8E30(u8 *u);
extern u16 D_801CEF10[];
void func_801C5938(void *a, u16 b);
s32 guRandom(void);
void func_801BC3A0(s16 x, s16 y, s32 a, s32 b);
void func_8020A348(f32 *a, f32 *b, f32 *out);
void guMtxIdentF(f32 (*m)[4]);
/* --- end decls --- */

/* Kind of formation cell character c: 0 below 20, 1 for 20-46, 2 for 47-86, else 0xFF */
static inline u8 CellKind(u8 c) {
    if (c < 20) {
        return 0;
    }
    if ((u8)(c - 20) < 27) {
        return 1;
    }
    if ((u8)(c - 47) < 40) {
        return 2;
    }
    return -1;
}

/* Whether the cell handler for character c accepts it */
s32 func_801F7128_ovl_24BCA0(u8 c) {
    return D_80209700_ovl_24BCA0[CellKind(c)](c) >= 0;
}

s32 func_801F71A0_ovl_24BCA0(u8 c) {
    return (c - 20) / 3;
}

s32 func_801F71CC_ovl_24BCA0(u8 c) {
    return (c - 20) % 3;
}

s32 func_801F71FC_ovl_24BCA0(f32 x) {
    return x / 38.0f + 4.0f;
}

s32 func_801F722C_ovl_24BCA0(f32 x) {
    return x / 38.0f + 1.0f;
}

s32 func_801F725C_ovl_24BCA0(u8 c) {
    return func_801C8AC0((c - 20) / 3);
}

s32 func_801F729C_ovl_24BCA0(u8 c) {
    return func_801C8AA4((c - 20) % 3);
}

s32 func_801F72E0_ovl_24BCA0(s32 a) {
    return (a - 47) / 4 * 38 - 171;
}

s32 func_801F730C_ovl_24BCA0(s32 a) {
    return (a - 47) % 4 * 38 - 57;
}

extern s32 (*D_8020970C_ovl_24BCA0[])(u8 c);
f32 func_801BC35C(s16 x, s16 z);
s32 func_8020ABF0(u8 c);
s32 func_801CA100(u8 *u);

/* World position of map cell c into p (x, y, z); flag 0x20 / 0x10 raise y by a full / half unit
 * height (cells 0-19 are units: by their own height) */
void func_801F7344_ovl_24BCA0(u8 c, f32 *p, u8 b) {
    u16 k;

    k = CellKind(c);
    p[0] = D_80209700_ovl_24BCA0[k]((u8)c);
    p[2] = D_8020970C_ovl_24BCA0[k]((u8)c);
    if (k == 0) {
        p[1] = func_8020ABF0((u8)c);
        if (b & 0x20) {
            p[1] += func_801CA100(func_801C8FE8((u8)c));
        } else if (b & 0x10) {
            p[1] += func_801CA100(func_801C8FE8((u8)c)) / 2;
        }
    } else {
        p[1] = func_801BC35C(p[0], p[2]);
        if (b & 0x20) {
            p[1] += 38.0f;
        } else if (b & 0x10) {
            p[1] += 19.0f;
        }
    }
}

extern s32 (*D_8020970C_ovl_24BCA0[])(u8 c);
f32 func_801BC35C(s16 x, s16 z);

/* World position of map cell c: table x/z plus offsets, y from the ground height */
void func_801F751C_ovl_24BCA0(u8 c, f32 *p, f32 ox, f32 oy, f32 oz) {
    u8 k = CellKind(c);

    p[0] = D_80209700_ovl_24BCA0[k]((u8)c) + ox;
    p[2] = D_8020970C_ovl_24BCA0[k]((u8)c) + oz;
    p[1] = func_801BC35C(p[0], p[2]) + oy;
}

/* Position for string str (0xFF-terminated): x of the last character, y and z averaged */
void func_801F7644_ovl_24BCA0(u8 *str, f32 *out, u8 c) {
    struct {
        f32 x;
        f32 y;
        f32 z;
    } sum;
    struct {
        f32 x;
        f32 y;
        f32 z;
        s32 w;
    } p;
    s16 i;

    bzero(&sum, 0xC);
    for (i = 0; str[i] != 0xFF; i++) {
        func_801F7344_ovl_24BCA0(str[i], (f32 *)&p, c);
        sum.y += p.y;
        sum.z += p.z;
    }
    out[0] = p.x;
    out[1] = sum.y / i;
    out[2] = sum.z / i;
}

/* Map unit index at world position pos (-1 if none or not targetable) */
s16 func_801F7738_ovl_24BCA0(f32 *pos) {
    s16 i = func_801CA1C4(pos[2] / 38.0f + 1.0f, pos[0] / 38.0f + 4.0f);

    if (i != -1) {
        if (func_801C8E30(func_801C8FE8(i))) {
            i = -1;
        }
    }
    return i;
}

/* Map unit index at the cell for character c (20 + row * 3 + lane) */
s16 func_801F77E0_ovl_24BCA0(u8 c) {
    s32 v = c - 20;

    return func_801CA1C4(v % 3, v / 3);
}

s16 func_801F782C_ovl_24BCA0(u8 i) {
    u8 *u = func_801C8FE8(i);

    return FIELD(u, s32, 0x58) * 3 + FIELD(u, s32, 0x54) + 20;
}

/* Lists the free cells of a formation grid in out (0xFF-terminated): the nine cells starting at
 * 38 when c's handler accepts it, else 20, whose map unit slot is empty */
void func_801F7868_ovl_24BCA0(u8 *out, u8 c) {
    s16 i;
    s16 n;
    s32 r = D_80209700_ovl_24BCA0[CellKind(c)](c) >= 0;
    s32 base = r * 18 + 20;

    for (i = 0, n = 0; i < 9; i++) {
        u8 cell = i + base;

        if (func_801CA1C4((cell - 20) % 3, (cell - 20) / 3) == -1) {
            out[n++] = cell;
        }
    }
    out[n] = 0xFF;
}

extern s8 D_80209758_ovl_24BCA0[][2];
extern s8 D_80209768_ovl_24BCA0[][2];

/* World positions of the four sub-cells of map cell c into out: half-cell offsets for kind-2
 * cells, else full-cell offsets for facing dir; y from the ground height */
void func_801F79BC_ovl_24BCA0(u8 c, f32 (*out)[3], u8 dir) {
    s16 i;
    u16 k = CellKind(c);
    f32 x = D_80209700_ovl_24BCA0[k](c);
    f32 z = D_8020970C_ovl_24BCA0[k](c);

    for (i = 0; i < 4; i++) {
        f32 dx;
        f32 dz;

        if (k == 2) {
            dx = D_80209768_ovl_24BCA0[i][0] * 19;
            dz = D_80209768_ovl_24BCA0[i][1] * 19;
        } else {
            dx = D_80209758_ovl_24BCA0[i + dir * 4][0] * 38;
            dz = D_80209758_ovl_24BCA0[i + dir * 4][1] * 38;
        }
        out[i][0] = x + dx;
        out[i][2] = z + dz;
        out[i][1] = func_801BC35C(out[i][0], out[i][2]);
    }
}

void func_801F7BE4_ovl_24BCA0(f32 *d, f32 *a, f32 *b) {
    d[0] = a[0] - b[0];
    d[1] = a[1] - b[1];
    d[2] = a[2] - b[2];
}

/* Rotation matrix whose z axis is dir (y up); dir is used as given (not normalised) */
void func_801F7C18_ovl_24BCA0(f32 *dir, f32 (*m)[4]) {
    f32 b[3][3];
    s32 i;
    s32 j;
    s32 k;

    b[1][0] = 0.0f;
    b[1][1] = 1.0f;
    b[1][2] = 0.0f;
    b[2][0] = dir[0];
    b[2][1] = dir[1];
    b[2][2] = dir[2];
    func_8020A348(b[1], b[2], b[0]);
    func_8020A348(b[2], b[0], b[1]);
    guMtxIdentF(m);
    for (i = 0, k = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            m[i][j] = b[0][k++];
        }
    }
}

f32 sqrtf(f32 x);
f32 func_8009CF00(f32 x); /* acosf */

/* Heading (degrees, 0-360) of the horizontal direction v (x at 0, z at 8) */
f32 func_801F7CF4_ovl_24BCA0(f32 *v) {
    f32 a = func_8009CF00(v[2] / sqrtf(v[0] * v[0] + v[2] * v[2])) * 180.0 / 3.14159265358979312;

    return v[0] < 0.0f ? 360.0f - a : a;
}

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F7DA4_ovl_24BCA0);

typedef struct {
    /* 0x00 */ u8 unk00[8];
    /* 0x08 */ f32 from[3];
    /* 0x14 */ f32 to[3];
    /* 0x20 */ f32 dir[3];
    /* 0x2C */ f32 len;
    /* 0x30 */ s32 t;
    /* 0x34 */ u8 unk34[4];
    /* 0x38 */ f32 *a;
    /* 0x3C */ f32 *b;
    /* 0x40 */ f32 *out;
} Curve24B;
f32 func_8020A3C8(f32 *v);
void func_8020A418(f32 *v);
void func_80217E1C(s32 n, f32 *a, f32 *b, f32 *out);
void *HMalloc(s32 size);

/* Sets up curve c from `from` to `to` with n samples: unit direction, length, and the distance and
 * height keys (height arc * h, rising to 20 at the end when flag 0x10) */
void func_801F8008_ovl_24BCA0(Curve24B *c, s16 n, f32 h, s32 flags) {
    c->dir[0] = c->to[0] - c->from[0];
    c->dir[1] = c->to[1] - c->from[1];
    c->dir[2] = c->to[2] - c->from[2];
    c->len = func_8020A3C8(c->dir);
    func_8020A418(c->dir);
    c->a = HMalloc(n * 4);
    c->b = HMalloc(n * 4);
    c->out = HMalloc(n * 4);
    c->t = 0;
    c->a[0] = 0.0f;
    c->a[1] = c->len / 3.0f;
    c->a[2] = 2.0f * c->len / 3.0f;
    c->a[3] = c->len;
    c->b[0] = 0.0f;
    c->b[1] = c->len * h * 0.25f;
    c->b[2] = c->b[1];
    if (flags & 0x10) {
        c->b[3] = 20.0f;
    } else {
        c->b[3] = 0.0f;
    }
    func_80217E1C(n, c->a, c->b, c->out);
}

void func_801F8180_ovl_24BCA0(u8 *p) {
    HFree(FIELD(p, void *, 0x38));
    FIELD(p, void *, 0x38) = NULL;
    HFree(FIELD(p, void *, 0x3C));
    FIELD(p, void *, 0x3C) = NULL;
    HFree(FIELD(p, void *, 0x40));
    FIELD(p, void *, 0x40) = NULL;
}

inline void func_801F81C4_ovl_24BCA0(u8 *p, u16 f) {
    s16 v;

    FIELD(p, u16, 0xA) |= f & 0xD000;
    if (f & 0x1000) {
        if (f & 0x400) {
            v = (f & 0x800) ? 10000 : -10000;
        } else {
            v = (f & 0x800) ? 1000 : -1000;
        }
        FIELD(p, s32, 0xC) = v;
    }
}

inline u8 *func_801F8218_ovl_24BCA0(AnimReq *r) {
    u8 *o = D_80209718_ovl_24BCA0[r->kind & 3](r->id);

    func_801F81C4_ovl_24BCA0(o, r->flags);
    return o + 0x1C;
}

inline u8 *func_801F82B4_ovl_24BCA0(AnimReq *r) {
    u8 *o = D_80209728_ovl_24BCA0[r->kind & 3](r->id);

    func_801F81C4_ovl_24BCA0(o, r->flags);
    return o + 0x1C;
}

u8 *func_801F8350_ovl_24BCA0(AnimReq *r) {
    u8 *o = D_80209734_ovl_24BCA0[r->kind & 3](r->id);

    func_801F81C4_ovl_24BCA0(o, r->flags);
    return o + 0x1C;
}

u8 *func_801F83EC_ovl_24BCA0(AnimReq *r, s32 i) {
    u8 *o = func_80214CF0(r->id, D_8020A170_ovl_24BCA0[i]);

    func_801F81C4_ovl_24BCA0(o, r->flags);
    return o + 0x1C;
}

u8 *func_801F847C_ovl_24BCA0(AnimReq *r, u8 x) {
    u8 *o = D_80209740_ovl_24BCA0[r->kind & 3](r->id, x);

    func_801F81C4_ovl_24BCA0(o, r->flags);
    return o + 0x1C;
}

u8 *func_801F8518_ovl_24BCA0(AnimReq *r, s32 x) {
    u8 *o = D_8020974C_ovl_24BCA0[r->kind & 3](r->id, 8, x, 8, x);

    func_801F81C4_ovl_24BCA0(o, r->flags);
    return o + 0x1C;
}

typedef struct {
    f32 v[3];
} Dir24B;
extern Dir24B D_8020A230_ovl_24BCA0;
extern u8 D_80220EE0[];
void func_8020A4A8(void *src, u8 *dst);
void func_80217680(f32 *dir, u8 *dst);
void func_8020A5A0(u8 *m, f32 *pos);

/* Spawns animation r at pos: kind 0 just places it, kinds 1-2 also orient it (copied matrix or
 * the default direction, mirrored to pos's side) */
u8 *func_801F85C0_ovl_24BCA0(u8 *a, u8 *b) {
    f32 *pos = (f32 *)a;
    AnimReq *r = (AnimReq *)b;
    u8 *o;
    u8 *m;
    Dir24B dir;
    u8 k;

    switch (r->kind & 3) {
    case 0:
        m = func_801F8218_ovl_24BCA0(r);
        ((f32 *)m)[0] = pos[0];
        ((f32 *)m)[1] = pos[1];
        ((f32 *)m)[2] = pos[2];
        return m - 0x1C;
    case 1:
        o = D_80209718_ovl_24BCA0[1](r->id);
        func_801F81C4_ovl_24BCA0(o, r->flags);
        k = r->kind;
        dir = D_8020A230_ovl_24BCA0;
        m = o + 0x1C;
        if (k & 0x40) {
            func_8020A4A8(D_80220EE0, m);
        } else {
            if (k & 0x80) {
                dir.v[0] = (-pos[0] < 0.0f) ? -1.0f : 1.0f;
            }
            func_80217680(dir.v, m);
        }
        func_8020A5A0(m, pos);
        return m - 0x1C;
    case 2:
        o = D_80209718_ovl_24BCA0[2](r->id);
        func_801F81C4_ovl_24BCA0(o, r->flags);
        k = r->kind;
        dir = D_8020A230_ovl_24BCA0;
        m = o + 0x1C;
        if (k & 0x40) {
            func_8020A4A8(D_80220EE0, m);
        } else {
            if (k & 0x80) {
                dir.v[0] = (-pos[0] < 0.0f) ? -1.0f : 1.0f;
            }
            func_80217680(dir.v, m);
        }
        func_8020A5A0(m, pos);
        return m - 0x1C;
    }
    return NULL;
}

/* As func_801F85C0 with the second spawner table: kind 0 just places it, kinds 1-2 also orient it (copied matrix or
 * the default direction, mirrored to pos's side) */
u8 *func_801F885C_ovl_24BCA0(u8 *a, u8 *b) {
    f32 *pos = (f32 *)a;
    AnimReq *r = (AnimReq *)b;
    u8 *o;
    u8 *m;
    Dir24B dir;
    u8 k;

    switch (r->kind & 3) {
    case 0:
        m = func_801F82B4_ovl_24BCA0(r);
        ((f32 *)m)[0] = pos[0];
        ((f32 *)m)[1] = pos[1];
        ((f32 *)m)[2] = pos[2];
        return m - 0x1C;
    case 1:
        o = D_80209728_ovl_24BCA0[1](r->id);
        func_801F81C4_ovl_24BCA0(o, r->flags);
        k = r->kind;
        dir = D_8020A230_ovl_24BCA0;
        m = o + 0x1C;
        if (k & 0x40) {
            func_8020A4A8(D_80220EE0, m);
        } else {
            if (k & 0x80) {
                dir.v[0] = (-pos[0] < 0.0f) ? -1.0f : 1.0f;
            }
            func_80217680(dir.v, m);
        }
        func_8020A5A0(m, pos);
        return m - 0x1C;
    case 2:
        o = D_80209728_ovl_24BCA0[2](r->id);
        func_801F81C4_ovl_24BCA0(o, r->flags);
        k = r->kind;
        dir = D_8020A230_ovl_24BCA0;
        m = o + 0x1C;
        if (k & 0x40) {
            func_8020A4A8(D_80220EE0, m);
        } else {
            if (k & 0x80) {
                dir.v[0] = (-pos[0] < 0.0f) ? -1.0f : 1.0f;
            }
            func_80217680(dir.v, m);
        }
        func_8020A5A0(m, pos);
        return m - 0x1C;
    }
    return NULL;
}

#ifdef NON_MATCHING
static inline u8 *Place24B(f32 *pos, AnimReq *r) {
    u8 *m = func_801F8218_ovl_24BCA0(r);

    ((f32 *)m)[0] = pos[0];
    ((f32 *)m)[1] = pos[1];
    ((f32 *)m)[2] = pos[2];
    return m - 0x1C;
}

static inline u8 *Orient24B(f32 *pos, AnimReq *r, s32 n) {
    u8 *o = D_80209718_ovl_24BCA0[n](r->id);
    Dir24B dir;
    u8 *m;
    u8 k;

    func_801F81C4_ovl_24BCA0(o, r->flags);
    k = r->kind;
    dir = D_8020A230_ovl_24BCA0;
    m = o + 0x1C;
    if (k & 0x40) {
        func_8020A4A8(D_80220EE0, m);
    } else {
        if (k & 0x80) {
            dir.v[0] = (-pos[0] < 0.0f) ? -1.0f : 1.0f;
        }
        func_80217680(dir.v, m);
    }
    func_8020A5A0(m, pos);
    return m;
}

#endif
/* As func_801F85C0, also scaled by c */
#ifdef NON_MATCHING
/* 214/214 instructions, 16 words differ: in kinds 1-2 the spawned object and the kind byte swap a2/a3 */
u8 *func_801F8AF8_ovl_24BCA0(u8 *a, u8 *b, f32 c) {
    f32 *pos = (f32 *)a;
    AnimReq *r = (AnimReq *)b;
    u8 *o;
    u8 *m;
    u8 k;

    switch (r->kind & 3) {
    case 0:
        o = Place24B(pos, r);
        FIELD(o, f32, 0x28) = FIELD(o, f32, 0x2C) = FIELD(o, f32, 0x30) = c;
        return o;
    case 1: {
        f32 s[3];

        m = Orient24B(pos, r, 1);
        s[0] = s[1] = s[2] = c;
        func_8020A4D0(s, m, m);
        return m - 0x1C;
    }
    case 2: {
        f32 s[3];

        m = Orient24B(pos, r, 2);
        s[0] = s[1] = s[2] = c;
        func_8020A4D0(s, m, m);
        return m - 0x1C;
    }
    }
    return NULL;
}
#else
INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F8AF8_ovl_24BCA0);
#endif

void func_801F8E50_ovl_24BCA0(u8 a, u8 *b) {
    u8 tmp[16];

    func_801F7344_ovl_24BCA0(a, tmp, b[2] & 0xF0);
    func_801F85C0_ovl_24BCA0(tmp, b);
}

void func_801F8E90_ovl_24BCA0(u8 a, u8 *b) {
    u8 tmp[16];

    func_801F7344_ovl_24BCA0(a, tmp, b[2] & 0xF0);
    func_801F885C_ovl_24BCA0(tmp, b);
}

void func_801F8ED0_ovl_24BCA0(u8 a, u8 *b, f32 c) {
    u8 tmp[16];

    func_801F7344_ovl_24BCA0(a, tmp, b[2] & 0xF0);
    func_801F8AF8_ovl_24BCA0(tmp, b, c);
}


/* Spawns animation r (variant i) at pos: its matrix is copied from D_80220EE0 (kind bit 6) or built
 * from the default direction, mirrored to face pos's side when kind bit 7 is set */
inline u8 *func_801F8F24_ovl_24BCA0(f32 *pos, AnimReq *r, s32 i) {
    u8 *o = func_80214CF0(r->id, D_8020A170_ovl_24BCA0[i]);
    Dir24B dir;
    u8 *m;
    u8 k;

    func_801F81C4_ovl_24BCA0(o, r->flags);
    k = r->kind;
    dir = D_8020A230_ovl_24BCA0;
    m = o + 0x1C;
    if (k & 0x40) {
        func_8020A4A8(D_80220EE0, m);
    } else {
        if (k & 0x80) {
            dir.v[0] = (-pos[0] < 0.0f) ? -1.0f : 1.0f;
        }
        func_80217680(dir.v, m);
    }
    func_8020A5A0(m, pos);
    return m - 0x1C;
}

/* As func_801F8F24 at the position of map cell c */
u8 *func_801F9060_ovl_24BCA0(u8 c, AnimReq *r, s32 i) {
    u8 tmp[16];

    func_801F7344_ovl_24BCA0(c, tmp, r->kind & 0xF0);
    return func_801F8F24_ovl_24BCA0((f32 *)tmp, r, i);
}

/* As func_801F85C0 for the timed spawners (D_8020974C, duration c): kind 0 places, kind 2 orients */
#ifdef NON_MATCHING
/* 128/128: in the placement case the spawned object lands in a2 instead of a0 */
u8 *func_801F91BC_ovl_24BCA0(u8 *a, u8 *b, s32 c) {
    f32 *pos = (f32 *)a;
    AnimReq *r = (AnimReq *)b;
    s32 k = r->kind & 3;
    u8 *o;
    u8 *m;
    Dir24B dir;
    u8 kk;

    switch ((u8)k) {
    case 0:
        o = D_8020974C_ovl_24BCA0[k](r->id, 8, c, 8, c);
        func_801F81C4_ovl_24BCA0(o, r->flags);
        m = o + 0x1C;
        ((f32 *)m)[0] = pos[0];
        ((f32 *)m)[1] = pos[1];
        ((f32 *)m)[2] = pos[2];
        return m - 0x1C;
    case 2:
        o = D_8020974C_ovl_24BCA0[k](r->id, 8, c, 8, c);
        func_801F81C4_ovl_24BCA0(o, r->flags);
        kk = r->kind;
        dir = D_8020A230_ovl_24BCA0;
        m = o + 0x1C;
        if (kk & 0x40) {
            func_8020A4A8(D_80220EE0, m);
        } else {
            if (kk & 0x80) {
                dir.v[0] = (-pos[0] < 0.0f) ? -1.0f : 1.0f;
            }
            func_80217680(dir.v, m);
        }
        func_8020A5A0(m, pos);
        return m - 0x1C;
    }
    return NULL;
}
#else
INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F91BC_ovl_24BCA0);
#endif

void func_801F93BC_ovl_24BCA0(u8 a, u8 *b, s32 c) {
    u8 tmp[16];

    func_801F7344_ovl_24BCA0(a, tmp, b[2] & 0xF0);
    func_801F91BC_ovl_24BCA0(tmp, b, c);
}

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F940C_ovl_24BCA0);

void func_801F9848_ovl_24BCA0(u16 id) {
    FIELD(func_802174C0(id), u16, 0xA) |= 0x8000;
}

u8 *func_801F9870_ovl_24BCA0(u16 id, f32 scale) {
    u8 *o = func_802174C0(id);
    f32 v[3];

    FIELD(o, u16, 0xA) |= 0x8000;
    v[2] = scale;
    v[1] = scale;
    v[0] = scale;
    func_8020A4D0(v, o + 0x1C, o + 0x1C);
    return o;
}

void func_801F98D0_ovl_24BCA0(u8 a, u8 *b, u8 n) {
    u8 tmp[16];
    s16 i;
    u8 *p;

    func_801F7344_ovl_24BCA0(a, tmp, b[2] & 0xF0);
    for (i = 0; i < n; i++) {
        p = b;
        b += 6;
        func_801F85C0_ovl_24BCA0(tmp, p);
    }
}

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F9950_ovl_24BCA0);

/* Screen shake by amt on the axes in flags (bit 0 x, bit 1 y), random signs */
#ifdef NON_MATCHING
/* only the s1/s2 save order in the prologue differs */
void func_801F9BEC_ovl_24BCA0(s32 amt, s32 flags) {
    s16 x = 0;
    s16 y = 0;

    if ((u8)amt != 0xFF) {
        s16 r = guRandom() % 50 % 2;
        s16 nr;

        x = 0;
        nr = r ^ 1;

        if (flags & 1) {
            x = (u8)amt;
        }
        if (flags & 2) {
            y = (u8)amt;
        }
        if (r) {
            x = -x;
        }
        if (nr) {
            y = -y;
        }
    }
    func_801BC3A0(x, y, 0, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F9BEC_ovl_24BCA0);
#endif

void func_801F9CD8_ovl_24BCA0(u8 a, s32 b) {
    struct {
        f32 x;
        f32 y;
        s32 z;
        s32 w;
    } t;

    func_801F7344_ovl_24BCA0(a, (f32 *)&t, 0x20);
    func_80218104(t.x, t.y, t.z, b);
}

/* Plays voice k for class c (0-19, 20-46, 47-86) on the next of two channels; the class handler
 * picks between the two variants */
void func_801F9D1C_ovl_24BCA0(u8 c, s32 k) {
    s16 r = D_80209700_ovl_24BCA0[CellKind(c)](c) >= 0;

    k = k * 2 + r;
    func_801C5938(D_80209770_ovl_24BCA0[D_8020A2D4_ovl_24BCA0], D_801CEF10[k]);
    if (++D_8020A2D4_ovl_24BCA0 >= 2) {
        D_8020A2D4_ovl_24BCA0 = 0;
    }
}

void func_801F9DFC_ovl_24BCA0(void *a, u8 c, s32 s) {
    s16 r = D_80209700_ovl_24BCA0[CellKind(c)](c) >= 0;

    s = s * 2 + r;
    func_801C5938(a, D_801CEF10[s]);
}

INCLUDE_RODATA("asm/nonmatchings/24BCA0", D_8020A230_ovl_24BCA0);
