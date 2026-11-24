#include "common.h"
#include "heap.h"

/* ovl_17F9C0 */

extern u8 D_80214A68;
extern s32 D_80214EA4;
extern s32 D_80214EA8;
extern u8 D_8021E120_ovl_17F9C0;

s32 func_8017BFB0(s32 a, s32 b, void *func, s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3);
void func_80215094_ovl_17F9C0(void);
void func_802166D8_ovl_17F9C0(void);
void func_80214FC4_ovl_17F9C0(void);

void func_80214F80_ovl_17F9C0(void) {
    if (D_80214A68 == 0) {
        func_80214FC4_ovl_17F9C0();
        D_8021E120_ovl_17F9C0 = 0;
        D_80214A68++;
    }
}

void func_80214FC4_ovl_17F9C0(void) {
    func_802166D8_ovl_17F9C0();
    D_80214EA4 = func_8017BFB0(0, 0, func_80215094_ovl_17F9C0, 0x120, 0xD0, 0x128, 0xD8, 0xBA, 0xD0, 0x128, 0xE2);
    D_80214EA8 = func_8017BFB0(0, 0, func_80215094_ovl_17F9C0, 0x18, 0xD0, 0x20, 0xD8, 0x18, 0xD0, 0x86, 0xE2);
}

INCLUDE_ASM("asm/nonmatchings/17F9C0", func_80215094_ovl_17F9C0);

INCLUDE_ASM("asm/nonmatchings/17F9C0", func_8021550C_ovl_17F9C0);

typedef struct {
    s32 flags;
    u8 pad4[0x6C];
    s32 unk70;
} Unit17;
extern Unit17 *D_801F0CB0[];
extern u8 D_801976DC;
extern u8 D_801976E8;
extern f32 D_801976E0;
extern f32 D_801976EC;
extern u8 D_801971F2[][0x19]; /* gSquads[].members[0] */
extern u8 D_80193BD1[][0x38]; /* player characters: class, base class */
extern u8 D_80193BD2[][0x38];
extern u8 D_80195571[][0x34]; /* enemy characters */
extern u8 D_80195572[][0x34];
extern u8 D_80187C59[][0x48]; /* gClassTable[].baseClass */
extern u8 D_8021AB9C_ovl_17F9C0[];
extern u8 D_8021ABA0_ovl_17F9C0[];
extern u8 D_8021E121_ovl_17F9C0;
extern u8 D_8021E122_ovl_17F9C0;
extern u8 *D_80214F54[];
extern u16 *D_80214E88[];
s32 func_801F4030(s32 a, s32 alt);
u8 *func_801F4734(u16 a); /* defined as func_801F4734_ovl_145210 */
u8 *func_801F477C(u16 a);
void func_801F4A34(u8 *src, u8 *dst, s32 n);
void func_801F4A6C(u8 *src, u8 *img, u16 alt, u16 *dst, s32 n);
void func_801F40B0(s32 v);
s32 func_80216A14_ovl_17F9C0(f32 a);

/* Loads the portraits of the two squad leaders (player side, then enemy side) into the image and
 * palette buffers, choosing each one's facing from the angle sectors */
#ifdef NON_MATCHING
/* same length, register allocation only: the original keeps size in s7 and mirror in s8 and spills
 * i to the stack (its frame is 8 bytes larger); here size is the one spilled */
void func_802166D8_ovl_17F9C0(void) {
    u32 size = 0x400;
    s32 i;
    Unit17 *o;
    u8 m;
    u8 cls;
    u8 base;
    s32 alt;
    s32 mirror;
    s32 off;
    s32 r;
    s32 id;
    u8 *img;
    u8 *pal;
    u8 a;
    u8 b;

    for (i = 0; i < 2; i++) {
        if (i == 0) {
            o = D_801F0CB0[D_801976DC];
            m = D_801971F2[D_801976DC][0];
            cls = D_80193BD1[m][0];
            base = D_80193BD2[m][0];
            alt = o->unk70 == 1 && !(o->flags & 0x40);
            mirror = 0;
            a = func_80216A14_ovl_17F9C0(D_801976E0);
            b = func_80216A14_ovl_17F9C0(D_801976EC);
            D_8021E121_ovl_17F9C0 = D_8021AB9C_ovl_17F9C0[a];
            D_8021E122_ovl_17F9C0 = D_8021ABA0_ovl_17F9C0[b];
            off = (u8)(D_8021E121_ovl_17F9C0 - 1) < 2 ? 4 : 10;
        } else {
            o = D_801F0CB0[D_801976E8];
            m = D_801971F2[D_801976E8][0];
            cls = D_80195571[m][0];
            base = D_80195572[m][0];
            alt = o->unk70 == 1 && !(o->flags & 0x40);
            mirror = 1;
            off = (u8)(D_8021E122_ovl_17F9C0 - 1) < 2 ? 4 : 10;
            if (cls == 0x87) {
                size = 0x780;
                mirror = 0;
                off = 1;
                D_8021E122_ovl_17F9C0 = 2;
            }
        }
        if (D_80187C59[cls][0] == 0) {
            r = cls;
            if (r != base) {
                r = base;
            }
        } else {
            r = cls;
            if (D_80187C59[cls][0] != base) {
                r = base;
            }
        }
        if (r >= 0xAA) {
            r = base;
        }
        D_80214F54[i] = HMalloc(size >> 1);
        D_80214E88[i] = HMalloc(size * 2);
        id = func_801F4030(r, alt);
        if (id == -1) {
            id = func_801F4030(base, alt);
        }
        img = func_801F4734(off + id);
        pal = func_801F477C(id);
        func_801F4A34(img, D_80214F54[i], size);
        func_801F4A6C(img, pal, mirror, D_80214E88[i], size);
        func_801F40B0((s32)img);
        func_801F40B0((s32)pal);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/17F9C0", func_802166D8_ovl_17F9C0);
#endif

/* Which quarter-turn sector an angle (in turns) falls in: 1..3, 0 otherwise */
s32 func_80216A14_ovl_17F9C0(f32 a) {
    if (0.208 <= a && a < 0.375) {
        return 1;
    }
    if (0.375 <= a && a < 0.625) {
        return 2;
    }
    if (0.625 <= a && a < 0.791) {
        return 3;
    }
    return 0;
}
