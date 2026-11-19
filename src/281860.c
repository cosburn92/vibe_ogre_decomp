#include "common.h"

/* ovl_281860: scene state functions */

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

typedef struct {
    /* 0x00 */ void (*update)(void);
    /* 0x04 */ void (*draw)(void);
    /* 0x08 */ void (*exit)(void);
    /* 0x0C */ u16 size;
} SceneFuncs;

#define GFX(w0_, w1_)                  \
    {                                  \
        Gfx *_g = D_800E9BA0++;        \
                                       \
        _g->w0 = (w0_);                \
        _g->w1 = (w1_);                \
    }

extern Gfx *D_800E9BA0;
extern SceneFuncs D_800E7A44;
extern s32 D_800E7A54;
extern u8 D_800E7A32;
extern u8 D_800E7A33;
extern u8 D_800E91D0[];
extern u16 D_800C4C26;
extern s32 D_8018F1A4;
extern u16 D_8018F1A0;
extern u8 *D_8018FC10;
extern s8 D_801CFC70;
extern u8 D_8022A7D0_ovl_281860[];
extern u8 D_8022A7F0_ovl_281860;
extern u8 D_8022A981_ovl_281860;
extern u8 D_8022A998_ovl_281860;
extern u8 D_8022A99A_ovl_281860;

void bzero(void *p, s32 n);
void *HFree(void *p);
void nuGfxTaskAllEndWait(void);
void func_8017A714(void);
void func_80178C90(void);
void func_80178E30(void);
void func_801C58F0(void);
void func_801C8850(void);
void func_8020B29C(void);
void func_8022D1AC(void);
void func_8022E214(s32 a);
void func_8022E3D0(void);
void func_8022E5F4(void);
void func_8022E738(void);
void func_8022E7A4(void);
void func_8022EEB4(void);
void func_8022F1A0(void);
void func_8022F848(void);
void func_80230E50(void);
void func_80234DB8(void);
void func_80237620(void);
void func_8023A1B8(void);
void func_8023C9BC(void);
void func_8023D800(void);
void func_8023E7D0(void);
void func_80225890_ovl_281860(void);
void func_80225ABC_ovl_281860(void);
void func_80225B10_ovl_281860(void);
void func_80225BDC_ovl_281860(void);
void func_80225CA8_ovl_281860(void);
void func_80225D14_ovl_281860(void);
void func_80225F00_ovl_281860(void);
void func_80225FD8_ovl_281860(void);
void func_80226034_ovl_281860(void);
void func_802260C4_ovl_281860(void);
void func_80226190_ovl_281860(void);
void func_8022620C_ovl_281860(void);
void func_802262C4_ovl_281860(s32 arg);
void func_802263C4_ovl_281860(s32 arg);
void func_8022681C_ovl_281860(s32 a, s32 b);
void func_80227694_ovl_281860(void);
s32 func_802276EC_ovl_281860(void);
void func_802282B8_ovl_281860(void);

INCLUDE_ASM("asm/nonmatchings/281860", func_80225890_ovl_281860);

void func_80225A1C_ovl_281860(void) {
    D_800E7A44.update = func_80225ABC_ovl_281860;
    D_800E7A44.draw = func_80225B10_ovl_281860;
    D_800E7A44.exit = func_80225BDC_ovl_281860;
    D_800E7A44.size = 0x5C;
    D_800E7A54 = 0;
    D_800E7A32 |= 9;
    D_800E7A33 |= 1;
    bzero(D_800E91D0, 0x5C);
    func_8020B29C();
    func_8022D1AC();
}

void func_80225ABC_ovl_281860(void) {
    func_80230E50();
    if (D_8022A998_ovl_281860 == 1) {
        u8 *flags = &D_800E7A32;

        D_8022A998_ovl_281860 = 0;
        *flags |= 2;
    }
    func_80237620();
}

void func_80225B10_ovl_281860(void) {
    GFX(0xE7000000, 0);
    GFX(0xDC080008, (u32)D_8022A7D0_ovl_281860);
    GFX(0xE7000000, 0);
    GFX(0xED000060, 0x004FC360);
    GFX(0xE7000000, 0);
    func_8023A1B8();
    GFX(0xE7000000, 0);
}

void func_80225BDC_ovl_281860(void) {
    nuGfxTaskAllEndWait();
    func_8022E214(0);
    func_80178C90();
}

void func_80225C08_ovl_281860(void) {
    D_800E7A44.update = func_80225CA8_ovl_281860;
    D_800E7A44.draw = func_80225D14_ovl_281860;
    D_800E7A44.exit = func_80225F00_ovl_281860;
    D_800E7A44.size = 0x5C;
    D_800E7A54 = 0;
    D_800E7A32 |= 9;
    D_800E7A33 |= 1;
    bzero(D_800E91D0, 0x5C);
    D_8022A99A_ovl_281860 = 3;
    func_8022EEB4();
}

void func_80225CA8_ovl_281860(void) {
    func_80227694_ovl_281860();
    func_802282B8_ovl_281860();
    if (D_8022A998_ovl_281860 == 1) {
        u8 *flags = &D_800E7A32;

        D_8022A998_ovl_281860 = 0;
        *flags |= 2;
    }
    func_8023D800();
    func_8022F848();
    func_80234DB8();
}

INCLUDE_ASM("asm/nonmatchings/281860", func_80225D14_ovl_281860);

void func_80225F00_ovl_281860(void) {
    nuGfxTaskAllEndWait();
    func_8022F1A0();
    if (D_8018F1A4 != 0) {
        D_800C4C26 = 2;
    } else {
        D_800C4C26 = 0xFFFE;
    }
}

void func_80225F40_ovl_281860(void) {
    D_800E7A44.update = func_80225FD8_ovl_281860;
    D_800E7A44.draw = func_80226034_ovl_281860;
    D_800E7A44.exit = func_802260C4_ovl_281860;
    D_800E7A44.size = 0x5C;
    D_800E7A54 = 0;
    D_800E7A32 |= 9;
    D_800E7A33 |= 1;
    bzero(D_800E91D0, 0x5C);
    func_8022E3D0();
}

void func_80225FD8_ovl_281860(void) {
    func_80227694_ovl_281860();
    func_802282B8_ovl_281860();
    func_8022E738();
    if (D_8022A998_ovl_281860 == 1) {
        u8 *flags = &D_800E7A32;

        D_8022A998_ovl_281860 = 0;
        *flags |= 2;
    }
}

void func_80226034_ovl_281860(void) {
    GFX(0xDC080008, (u32)D_8022A7D0_ovl_281860);
    GFX(0xE7000000, 0);
    GFX(0xED000000, 0x004FC3BC);
    GFX(0xE7000000, 0);
    func_8022E5F4();
}

void func_802260C4_ovl_281860(void) {
    nuGfxTaskAllEndWait();
    func_8022E7A4();
    func_80178C90();
}

void func_802260F0_ovl_281860(void) {
    D_800E7A44.update = func_80226190_ovl_281860;
    D_800E7A44.draw = func_8022620C_ovl_281860;
    D_800E7A44.exit = func_802262C4_ovl_281860;
    D_800E7A44.size = 0x5C;
    D_800E7A54 = 0;
    D_800E7A32 |= 9;
    D_800E7A33 |= 1;
    bzero(D_800E91D0, 0x5C);
    func_8020B29C();
    func_8022D1AC();
}

void func_80226190_ovl_281860(void) {
    if (D_8022A998_ovl_281860 == 1) {
        u8 *flags = &D_800E7A32;

        D_8022A998_ovl_281860 = 0;
        *flags |= 2;
    }
    func_80230E50();
    if (((func_802276EC_ovl_281860() ^ 0xD7) & 0xFF) == 0) {
        u8 *flags = &D_800E7A32;

        *flags |= 2;
    }
    func_80237620();
}

INCLUDE_ASM("asm/nonmatchings/281860", func_8022620C_ovl_281860);

void func_802262C4_ovl_281860(s32 arg) {
    nuGfxTaskAllEndWait();
    if (((func_802276EC_ovl_281860() ^ 0xD7) & 0xFF) == 0) {
        func_80178E30();
        D_801CFC70 = 0;
        func_80225890_ovl_281860();
    } else {
        func_802263C4_ovl_281860(arg);
    }
}

INCLUDE_ASM("asm/nonmatchings/281860", func_80226324_ovl_281860);

void func_802263C4_ovl_281860(s32 arg) {
    nuGfxTaskAllEndWait();
    if (D_8022A981_ovl_281860 == 2) {
        func_80178E30();
        D_801CFC70 = 0;
        func_80225890_ovl_281860();
    } else {
        func_801C8850();
        func_8023C9BC();
        func_8022E214(0);
        func_8023E7D0();
        D_8022A981_ovl_281860 = 0;
        func_80178C90();
    }
}

INCLUDE_ASM("asm/nonmatchings/281860", func_8022643C_ovl_281860);

INCLUDE_ASM("asm/nonmatchings/281860", func_80226538_ovl_281860);

INCLUDE_ASM("asm/nonmatchings/281860", func_802265EC_ovl_281860);

void func_802267DC_ovl_281860(void) {
    u8 *p = D_8018FC10;

    if (p != NULL) {
        *(u16 *)p = 0;
        if (p[7] == 1) {
            HFree(p);
            D_8018FC10 = NULL;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/281860", func_8022681C_ovl_281860);

s32 func_80226F88_ovl_281860(void) {
    u16 *p;

    func_801C58F0();
    func_8017A714();
    D_801CFC70 = -1;
    if (D_8018F1A0 & 0x4000) {
        D_8022A7F0_ovl_281860 = 1;
    } else {
        D_8022A7F0_ovl_281860 = 0;
    }
    p = &D_8018F1A0;
    func_8022681C_ovl_281860(-5, *p & 0xFFF);
    return *p + 1;
}
