#include "common.h"

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))

void HFree(void *p);
s32 func_801C8AC0(s32 a);
s32 func_801C8AA4(s32 a);
s32 func_801CA1C4(s32 a);
u8 *func_801C8FE8(u8 i);
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
extern s32 D_8020A170_ovl_24BCA0[];
u8 *func_80214CF0(u16 id, s32 a);
extern s32 (*D_80209700_ovl_24BCA0[])(u8 c);
void func_80218104(f32 x, f32 y, s32 z, s32 w);
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

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F7644_ovl_24BCA0);

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F7738_ovl_24BCA0);

#ifdef NON_MATCHING
/* Register allocation differs in the modulo. */
s16 func_801F77E0_ovl_24BCA0(u8 c) {
    return func_801CA1C4((c - 20) % 3);
}
#else
INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F77E0_ovl_24BCA0);
#endif

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

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F7C18_ovl_24BCA0);

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

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F8518_ovl_24BCA0);

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

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F9BEC_ovl_24BCA0);

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

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F9D1C_ovl_24BCA0);

INCLUDE_ASM("asm/nonmatchings/24BCA0", func_801F9DFC_ovl_24BCA0);

INCLUDE_RODATA("asm/nonmatchings/24BCA0", D_8020A230_ovl_24BCA0);
