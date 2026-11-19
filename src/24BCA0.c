#include "common.h"

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))

void HFree(void *p);
s32 func_801C8AC0(s32 a);
s32 func_801C8AA4(s32 a);
s32 func_801CA1C4(s32 lane, s32 row);
u8 *func_801C8FE8(s32 i);
void func_801F7344_ovl_24BCA0(u8 a, u8 *out, u8 b);
void func_801F85C0_ovl_24BCA0(u8 *a, u8 *b);
void func_801F885C_ovl_24BCA0(u8 *a, u8 *b);
void func_801F8AF8_ovl_24BCA0(u8 *a, u8 *b, f32 c);
void func_801F91BC_ovl_24BCA0(u8 *a, u8 *b, s32 c);
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

#ifdef NON_MATCHING
/* range chain: the original branches where GCC uses set-compares for the last test */
s32 func_801F7128_ovl_24BCA0(u8 c) {
    s32 k;

    if (c < 20) {
        k = 0;
    } else if ((u8)(c - 20) < 27) {
        k = 1;
    } else if ((u8)(c - 47) < 40) {
        k = 2;
    } else {
        k = 0xFF;
    }
    return D_80209700_ovl_24BCA0[k](c) >= 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F7128_ovl_24BCA0);
#endif

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

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F7344_ovl_24BCA0);

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F751C_ovl_24BCA0);

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
        func_801F7344_ovl_24BCA0(str[i], (u8 *)&p, c);
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

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F7868_ovl_24BCA0);

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F79BC_ovl_24BCA0);

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

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F7CF4_ovl_24BCA0);

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F7DA4_ovl_24BCA0);

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F8008_ovl_24BCA0);

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

u8 *func_801F8218_ovl_24BCA0(AnimReq *r) {
    u8 *o = D_80209718_ovl_24BCA0[r->kind & 3](r->id);

    func_801F81C4_ovl_24BCA0(o, r->flags);
    return o + 0x1C;
}

u8 *func_801F82B4_ovl_24BCA0(AnimReq *r) {
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

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F85C0_ovl_24BCA0);

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F885C_ovl_24BCA0);

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F8AF8_ovl_24BCA0);

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

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F8F24_ovl_24BCA0);

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F9060_ovl_24BCA0);

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F91BC_ovl_24BCA0);

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

    func_801F7344_ovl_24BCA0(a, (u8 *)&t, 0x20);
    func_80218104(t.x, t.y, t.z, b);
}

/* Plays voice k for class c (0-19, 20-46, 47-86) on the next of two channels; the class handler
 * picks between the two variants */
#ifdef NON_MATCHING
/* Same range-chain set-compare issue as func_801F7128 and func_801F9DFC: GCC turns the last range test into xori/negu/and instead of a branch, and keeps k in s0 later. */
void func_801F9D1C_ovl_24BCA0(u8 c, s32 k) {
    s32 t;

    if (c < 20) {
        t = 0;
    } else if ((u8)(c - 20) < 27) {
        t = 1;
    } else if ((u8)(c - 47) < 40) {
        t = 2;
    } else {
        t = 0xFF;
    }
    k = k * 2 + (D_80209700_ovl_24BCA0[t](c) >= 0);
    func_801C5938(D_80209770_ovl_24BCA0[D_8020A2D4_ovl_24BCA0], D_801CEF10[k]);
    if (++D_8020A2D4_ovl_24BCA0 >= 2) {
        D_8020A2D4_ovl_24BCA0 = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F9D1C_ovl_24BCA0);
#endif

static inline s32 cls24(u8 c) {
    s32 k;

    if (c < 20) {
        k = 0;
    } else if ((u8)(c - 20) < 27) {
        k = 1;
    } else if ((u8)(c - 47) < 40) {
        k = 2;
    } else {
        k = 0xFF;
    }
    return D_80209700_ovl_24BCA0[k](c) >= 0;
}
#ifdef NON_MATCHING
/* same range-chain set-compare issue as func_801F7128 (inlined here) */
void func_801F9DFC_ovl_24BCA0(void *a, u8 c, s32 s) {
    s = s * 2 + cls24(c);
    func_801C5938(a, D_801CEF10[s]);
}
#else
INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F9DFC_ovl_24BCA0);
#endif

INCLUDE_RODATA("asm/nonmatchings/24BCA0", D_8020A230_ovl_24BCA0);
