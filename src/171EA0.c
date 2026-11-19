#include "common.h"

/* 171EA0 */

typedef struct {
    u8 unk00[0x70];
    s32 w70;
    s32 w74;
    s32 w78;
    s32 w7C;
} Ctx17;

extern s16 D_8021AFB0_ovl_171EA0;
extern u8 D_8021AFB2_ovl_171EA0;
extern u8 D_8021AFB3_ovl_171EA0;
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

INCLUDE_ASM("asm/nonmatchings/171EA0", func_80214FFC_ovl_171EA0);

INCLUDE_ASM("asm/nonmatchings/171EA0", func_802150C8_ovl_171EA0);

INCLUDE_ASM("asm/nonmatchings/171EA0", func_80215378_ovl_171EA0);

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
