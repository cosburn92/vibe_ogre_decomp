#include "common.h"

/* 171EA0 */

typedef struct {
    u8 unk00[0x5C];
    s16 h5C;
    u8 b5E;
    u8 unk5F;
    s32 w60;
    u8 b64;
    u8 b65;
    u8 unk66[2];
    s32 w68;
    s32 w6C;
    s32 w70;
    s32 w74;
    s32 w78;
    s32 w7C;
} Ctx17;

extern s16 D_8021AFB0_ovl_171EA0;
extern u8 D_8021AFB2_ovl_171EA0;
extern s8 D_8021AFB3_ovl_171EA0;
extern u8 D_8021AFB4_ovl_171EA0;
extern u8 D_80214E84;
extern Ctx17 *D_8021AA70_ovl_171EA0;
extern u8 D_8018F480;
extern u8 D_801F365D;
extern s32 D_801F0DE0;
extern s32 D_801F0DE8;

void func_80076F5C(s32 a, void *b, s32 c, s32 d, s32 e, s32 f, s32 g);
void func_80214FFC_ovl_171EA0(void);
void func_80079618();
void func_80179018(void);
typedef struct {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u8 flags2;
    /* 0x03 */ u8 flags3;
    /* 0x04 */ u8 unk04[0x10];
    /* 0x14 */ void (*update)(void);
    /* 0x18 */ void (*draw)(void);
    /* 0x1C */ void (*exit)(void);
    /* 0x20 */ u16 size;
    /* 0x22 */ u8 unk22[2];
    /* 0x24 */ s32 w24;
} CurScene17;
extern CurScene17 D_800E7A30;
extern u8 D_800E7A33;
void func_802150C8_ovl_171EA0(void);
void func_80216CD8_ovl_171EA0(void);
void func_80215378_ovl_171EA0(void);
void *LoadAsset(u32 handle, ...);
/* --- end decls --- */

void func_80214F80_ovl_171EA0(s16 a, u8 b, u8 c, u8 d) {
    D_8021AFB0_ovl_171EA0 = a;
    D_8021AFB2_ovl_171EA0 = b;
    D_8021AFB3_ovl_171EA0 = c;
    D_8021AFB4_ovl_171EA0 = d;
    func_80076F5C(0xC000, func_80214FFC_ovl_171EA0, 0x66, 0x41, 0x70, 0x4B, 0xC8);
    D_80214E84 = 1;
}

u8 func_80214FF0_ovl_171EA0(void) {
    return D_80214E84;
}

void func_80214FFC_ovl_171EA0(void) {
    D_800E7A30.flags2 |= 8;
    D_800E7A33 |= 1;
    D_800E7A30.flags2 |= 1;
    D_800E7A30.flags |= 0x200;
    D_800E7A30.update = func_802150C8_ovl_171EA0;
    D_800E7A30.draw = func_80216CD8_ovl_171EA0;
    D_800E7A30.size = 0x80;
    D_800E7A30.w24 = 0;
    D_8021AA70_ovl_171EA0->h5C = D_8021AFB0_ovl_171EA0;
    ((u8 *)D_8021AA70_ovl_171EA0)[0x5E] = 0;
    D_8021AA70_ovl_171EA0->w60 = 0;
    ((u8 *)D_8021AA70_ovl_171EA0)[0x64] = 0;
    ((u8 *)D_8021AA70_ovl_171EA0)[0x65] = 0;
    D_8021AA70_ovl_171EA0->w68 = 0;
    D_8021AA70_ovl_171EA0->w6C = 0;
    D_8021AA70_ovl_171EA0->w70 = 0;
    D_8021AA70_ovl_171EA0->w74 = 0;
    D_8021AA70_ovl_171EA0->w78 = 0;
    D_8021AA70_ovl_171EA0->w7C = 0;
    func_80215378_ovl_171EA0();
}

INCLUDE_ASM("asm/nonmatchings/171EA0", func_802150C8_ovl_171EA0);

/* Loads the four images from asset 0x218E9B4 (frame, then variants picked by the three parameters) */
void func_80215378_ovl_171EA0(void) {
    if (D_8021AA70_ovl_171EA0->w70 == 0) {
        D_8021AA70_ovl_171EA0->w70 = (s32)LoadAsset(0x218E9B4, 0x16, -3, 0);
        D_8021AA70_ovl_171EA0->w74 = (s32)LoadAsset(0x218E9B4, 0x16, -3, D_8021AFB4_ovl_171EA0 + 0x14);
        D_8021AA70_ovl_171EA0->w78 = (s32)LoadAsset(0x218E9B4, 0x16, -3, D_8021AFB2_ovl_171EA0 + 1);
        D_8021AA70_ovl_171EA0->w7C = (s32)LoadAsset(0x218E9B4, 0x16, -3, D_8021AFB3_ovl_171EA0 + 0xC);
    }
}

void func_80215444_ovl_171EA0(void) {
    if (D_8021AA70_ovl_171EA0->w70 != 0) {
        func_80079618(0x218E9B4, 0x16, -0x11);
        D_8021AA70_ovl_171EA0->w70 = 0;
        D_8021AA70_ovl_171EA0->w74 = 0;
        D_8021AA70_ovl_171EA0->w78 = 0;
        D_8021AA70_ovl_171EA0->w7C = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/171EA0", func_80215494_ovl_171EA0);

INCLUDE_ASM("asm/nonmatchings/171EA0", func_80215780_ovl_171EA0);

void func_80216CD8_ovl_171EA0(void) {
    func_80179018();
    D_8018F480 = 0;
}

void func_80216CFC_ovl_171EA0(void) {
    if (D_80214E84 == 0) {
        D_801F0DE0 = 0;
        D_801F0DE8 = 0;
        D_801F365D &= 0xFE;
    }
}

INCLUDE_ASM("asm/nonmatchings/171EA0", func_80216D38_ovl_171EA0);
