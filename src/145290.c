#include "common.h"

typedef struct {
    /* 0x00 */ u32 flags;
    /* 0x04 */ u8 unk04[0x6C];
    /* 0x70 */ s32 unk70;
} MapUnit;

typedef struct { u16 v[3]; } U16x3;

extern s32 D_801FDA10_ovl_145210;
extern s32 *D_801FDA14_ovl_145210;
extern s32 D_801FDA18_ovl_145210;
extern s32 D_801FDA1C_ovl_145210;
extern s32 D_801FDA20_ovl_145210;
extern u8 D_801FDA24_ovl_145210;
extern u8 D_801FDA30_ovl_145210;
extern u8 *D_801FDA3C_ovl_145210;
extern u16 D_801FDA60_ovl_145210;
extern U16x3 D_801FD958_ovl_145210;
extern s32 D_801F367C;
extern MapUnit *D_801F0CB0[];
void bzero(void *p, s32 size);
void *HMalloc(s32 size);
void HFree(void *p);
void func_801F4358_ovl_145210(s32 kind, void *msg);





INCLUDE_ASM("asm/nonmatchings/145290", func_801F40B0_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F4208_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F4358_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F4578_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F45D0_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F4638_ovl_145210);

void func_801F4734_ovl_145210(s16 a) {
    s16 msg[4];
    s16 *p = msg;

    bzero(p, 8);
    p[0] = a;
    func_801F4358_ovl_145210(4, p);
}

void func_801F477C_ovl_145210(s16 a) {
    s16 msg[4];
    s16 *p = msg;

    bzero(p, 8);
    p[0] = a;
    func_801F4358_ovl_145210(5, p);
}

void func_801F47C4_ovl_145210(u8 a) {
    u8 msg[8];
    u8 *p = msg;

    bzero(p, 8);
    p[0] = a;
    func_801F4358_ovl_145210(6, p);
}

INCLUDE_ASM("asm/nonmatchings/145290", func_801F480C_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F4960_ovl_145210);

void func_801F4A34_ovl_145210(u8 *src, u8 *dst, s32 n) {
    n -= n / 2;
    while (n > 0) {
        *dst++ = *src++;
        n--;
    }
}

INCLUDE_ASM("asm/nonmatchings/145290", func_801F4A6C_ovl_145210);

void func_801F4AD0_ovl_145210(void) {
    D_801FDA10_ovl_145210 = 105;
    D_801FDA14_ovl_145210 = HMalloc(0x1A4);
    bzero(D_801FDA14_ovl_145210, 0x1A4);
    D_801FDA18_ovl_145210 = 0;
}

void func_801F4B14_ovl_145210(void) {
    HFree(D_801FDA14_ovl_145210);
}

void func_801F4B38_ovl_145210(void) {
    D_801FDA18_ovl_145210 = 0;
    D_801FDA1C_ovl_145210 = 0;
    D_801FDA20_ovl_145210 = 0;
    D_801FDA24_ovl_145210 = 0;
}

INCLUDE_ASM("asm/nonmatchings/145290", func_801F4B5C_ovl_145210);

void func_801F4BBC_ovl_145210(s32 v) {
    D_801FDA14_ovl_145210[D_801FDA18_ovl_145210++] = v;
}

void func_801F4BE8_ovl_145210(s32 *p, s32 v) {
    p[0] = v;
}

void func_801F4BF0_ovl_145210(s32 *p, s32 v) {
    p[1] = v;
}

void func_801F4BF8_ovl_145210(s32 v) {
    D_801FDA1C_ovl_145210 = v;
}

s32 func_801F4C04_ovl_145210(s32 v) {
    return D_801FDA1C_ovl_145210 == v;
}

void func_801F4C18_ovl_145210(s32 v) {
    D_801FDA20_ovl_145210 = v;
}

s32 func_801F4C24_ovl_145210(s32 v) {
    return D_801FDA20_ovl_145210 == v;
}

INCLUDE_ASM("asm/nonmatchings/145290", func_801F4C38_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F4CD0_ovl_145210);

s32 func_801F4EB4_ovl_145210(MapUnit *u) {
    return u->unk70 == 1 && !(u->flags & 0x40);
}

INCLUDE_ASM("asm/nonmatchings/145290", func_801F4ED8_ovl_145210);

/* Slot of a unit; hangs if it is not on the map. */
s32 func_801F4FF4_ovl_145210(MapUnit *u) {
    s32 n = D_801F367C;
    s32 i;

    for (i = 0; i < n; i++) {
        if (D_801F0CB0[i] == u) {
            return i;
        }
    }
    for (;;) {
    }
}

INCLUDE_ASM("asm/nonmatchings/145290", func_801F503C_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F50F0_ovl_145210);

void func_801F5504_ovl_145210(u32 i) {
    U16x3 t = D_801FD958_ovl_145210;

    if (i >= 3) {
        i = 0;
    }
    D_801FDA60_ovl_145210 = t.v[i];
}

INCLUDE_ASM("asm/nonmatchings/145290", func_801F5550_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F57D0_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F5AD0_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F5C74_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F5D28_ovl_145210);

INCLUDE_RODATA("asm/nonmatchings/145290", D_801FD958_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F5E94_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F632C_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F6540_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F67F0_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F69A0_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F69FC_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F6B64_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F6BC0_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F6C48_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F6CB4_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F6D3C_ovl_145210);

void func_801F6DC8_ovl_145210(void) {
    D_801FDA30_ovl_145210 = 1;
}

void func_801F6DD8_ovl_145210(s32 unused, s32 i) {
    D_801F0CB0[i]->flags |= 0x4000000;
    D_801FDA3C_ovl_145210[i * 4] |= 2;
}

INCLUDE_ASM("asm/nonmatchings/145290", func_801F6E14_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F7684_ovl_145210);

INCLUDE_RODATA("asm/nonmatchings/145290", D_801FD9A0_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F7C40_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F83F4_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F8510_ovl_145210);

void func_801F85F0_ovl_145210(void) {
}

INCLUDE_ASM("asm/nonmatchings/145290", func_801F85F8_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F86A8_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F8774_ovl_145210);

INCLUDE_ASM("asm/nonmatchings/145290", func_801F8830_ovl_145210);
