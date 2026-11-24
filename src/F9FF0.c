#include "common.h"
#include "scene.h"

/* ovl_0F9FF0: creates and queries scene boxes owned by D_80198BE8 */

extern u8 D_8019EE48;
void D_80198BE8(void);


void func_8019EE50_ovl_0F9FF0(void) {
}

s32 func_8019EE58_ovl_0F9FF0(u8 id, u16 a, u16 b, u8 c, u8 flag) {
    s32 i = func_8007F648((s32)D_80198BE8, 0, 0, 0, 0);

    D_800E82C8[i].unk88 = b >> 8;
    D_800E82C8[i].unk89 = b;
    D_800E82C8[i].unk8A = 0;
    if (flag) {
        D_800E82C8[i].unk8A = 4;
    }
    D_800E82C8[i].unk8B = c;
    D_800E82C8[i].unk8F = id;
    D_800E82C8[i].unk96 = a >> 8;
    D_800E82C8[i].unk97 = a;
    D_800E82C8[i].unk8C = 0;
    D_800E82C8[i].unk8D = 0;
    D_800E82C8[i].unk94 = 0;
    D_800E82C8[i].unk95 = 0;
    return i;
}

//UNWRAP_BEGIN
/* Only the prologue saves s1 before s0 in the original. */
s32 func_8019EF80_ovl_0F9FF0(u16 a, s16 b, u16 c) {
    s32 i = func_8007F648((s32)D_80198BE8, 0, 0, 0, 0);

    D_800E82C8[i].unk88 = (a >> 8) | 0x80;
    D_800E82C8[i].unk89 = a;
    if (b >= 0) {
        D_800E82C8[i].unk8A = 0x40;
        D_800E82C8[i].unk8C = b >> 8;
        D_800E82C8[i].unk8D = b;
    } else {
        D_800E82C8[i].unk8A = 0xC0;
        D_800E82C8[i].unk8C = 0;
        D_800E82C8[i].unk8D = 0;
    }
    D_800E82C8[i].unk94 = c >> 8;
    D_800E82C8[i].unk8B = 0;
    D_800E82C8[i].unk95 = c;
    D_800E82C8[i].unk8F = 0xFF;
    D_800E82C8[i].unk96 = 0;
    D_800E82C8[i].unk97 = 0;
    return i;
}
//UNWRAP_END

//UNWRAP_BEGIN
/* The original loads the last two stack arguments with lw (32-bit) but schedules like this u16 version. */
s32 func_8019F0E0_ovl_0F9FF0(s32 id, s32 a, s32 b, s32 c, u8 flag, s32 d, s32 e) {
    s32 i = func_8019EE58_ovl_0F9FF0(id, a, b, c, flag);

    D_800E82C8[i].unk8C = (u16)d >> 8;
    D_800E82C8[i].unk8D = d;
    D_800E82C8[i].unk94 = (u16)e >> 8;
    D_800E82C8[i].unk95 = e;
    return i;
}
//UNWRAP_END

s32 func_8019F174_ovl_0F9FF0(u8 id) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if ((D_800E82C8[i].flags & 0x8000) && D_800E82C8[i].owner == D_80198BE8 && D_800E82C8[i].unk8F == id) {
            return (D_800E82C8[i].unk8A & 1) << 1;
        }
    }
    return (D_8019EE48 & 2) ? 3 : 1;
}

//UNWRAP_BEGIN
/* GCC here folds the 2/0 and 3/1 returns into set-compare arithmetic; the original keeps branches. */
s32 func_8019F210_ovl_0F9FF0(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if ((D_800E82C8[i].flags & 0x8000) && D_800E82C8[i].owner == D_80198BE8 && D_800E82C8[i].unk8F == 0xFF) {
            if (D_800E82C8[i].unk8A & 1) {
                goto two;
            }
            return 0;
        }
    }
    if (!(D_8019EE48 & 2)) {
        goto one;
    }
    return 3;
two:
    return 2;
one:
    return 1;
}
//UNWRAP_END

void func_8019F2C0_ovl_0F9FF0(u8 id) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if ((D_800E82C8[i].flags & 0x8000) && D_800E82C8[i].owner == D_80198BE8 && D_800E82C8[i].unk8F == id) {
            D_800E82C8[i].unk8A |= 2;
            D_800E82C8[i].unk0E = 0xF000;
            return;
        }
    }
}

void func_8019F354_ovl_0F9FF0(u8 id) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if ((D_800E82C8[i].flags & 0x8000) && D_800E82C8[i].owner == D_80198BE8 && D_800E82C8[i].unk8F == id) {
            D_800E82C8[i].flags |= 0x1000;
            return;
        }
    }
}

void func_8019F3CC_ovl_0F9FF0(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if ((D_800E82C8[i].flags & 0x8000) && D_800E82C8[i].owner == D_80198BE8) {
            D_800E82C8[i].flags |= 0x1000;
        }
    }
}
