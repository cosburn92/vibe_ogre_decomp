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

extern u8 ovl_213B10_TEXT_START[];
extern u8 ovl_213B10_TEXT_END[];
extern u8 ovl_213B10_DATA_START[];
extern u8 ovl_213B10_RODATA_END[];
extern u8 ovl_213B10_BSS_START[];
extern u8 ovl_213B10_BSS_END[];
extern u8 ovl_213B10_ROM_START[];
extern u8 ovl_213B10_ROM_END[];
extern u8 ovl_213B10_VRAM[];
extern u8 ovl_22A280_TEXT_START[];
extern u8 ovl_22A280_TEXT_END[];
extern u8 ovl_22A280_DATA_START[];
extern u8 ovl_22A280_RODATA_END[];
extern u8 ovl_22A280_BSS_START[];
extern u8 ovl_22A280_BSS_END[];
extern u8 ovl_22A280_ROM_START[];
extern u8 ovl_22A280_ROM_END[];
extern u8 ovl_22A280_VRAM[];
void osInvalICache(void *p, s32 n);
void osInvalDCache(void *p, s32 n);
void RomRead(void *rom, void *dst, s32 size);
void func_80073164(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);
extern u8 D_8022A980_ovl_281860;
void func_801D0840(void);
void func_801AFE30(s32 a);
void func_801C88CC(s32 a);
void func_801C8864(void);
void func_80172394(void);
void func_80172124(void);
void func_801707F4(void);
void func_80226190_ovl_281860(void);
void func_8022620C_ovl_281860(void);
void func_802395C0(void);
s32 func_8023E050(void);
void func_8023C9EC(void);
/* --- end decls --- */

/* Reloads the battle overlays and restarts the battle */
void func_80225890_ovl_281860(void) {
    if (((func_802276EC_ovl_281860() ^ 0xD7) & 0xFF) != 0) {
        return;
    }
    func_8023C9BC();
    func_8022E214(0);
    osInvalICache(ovl_213B10_TEXT_START, ovl_213B10_TEXT_END - ovl_213B10_TEXT_START);
    osInvalDCache(ovl_213B10_DATA_START, ovl_213B10_RODATA_END - ovl_213B10_DATA_START);
    RomRead(ovl_213B10_ROM_START, ovl_213B10_VRAM, ovl_213B10_ROM_END - ovl_213B10_ROM_START);
    if (ovl_213B10_BSS_START != ovl_213B10_BSS_END) {
        bzero(ovl_213B10_BSS_START, ovl_213B10_BSS_END - ovl_213B10_BSS_START);
    }
    osInvalICache(ovl_22A280_TEXT_START, ovl_22A280_TEXT_END - ovl_22A280_TEXT_START);
    osInvalDCache(ovl_22A280_DATA_START, ovl_22A280_RODATA_END - ovl_22A280_DATA_START);
    RomRead(ovl_22A280_ROM_START, ovl_22A280_VRAM, ovl_22A280_ROM_END - ovl_22A280_ROM_START);
    if (ovl_22A280_BSS_START != ovl_22A280_BSS_END) {
        bzero(ovl_22A280_BSS_START, ovl_22A280_BSS_END - ovl_22A280_BSS_START);
    }
    func_801D0840();
    func_801AFE30(0);
    func_80073164(0, 0x10, 0x10, 0x200, 0x10, 0x800, 0x1900);
    func_801C88CC(2);
    func_801C8864();
    func_80172394();
    func_80172124();
    func_801707F4();
    D_8022A980_ovl_281860 = 0xFF;
}

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

void func_8022620C_ovl_281860(void) {
    GFX(0xDC080008, (u32)D_8022A7D0_ovl_281860);
    if (!func_8023E050()) {
        GFX(0xE7000000, 0);
        GFX(0xED000060, 0x004FC35C);
        GFX(0xE7000000, 0);
    }
    if (D_8022A998_ovl_281860 == 0) {
        func_8023C9EC();
    }
}

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

void func_80226324_ovl_281860(void) {
    D_800E7A44.update = func_80226190_ovl_281860;
    D_800E7A44.draw = func_8022620C_ovl_281860;
    D_800E7A44.exit = (void (*)(void))func_802263C4_ovl_281860;
    D_800E7A44.size = 0x5C;
    D_800E7A54 = 0;
    D_800E7A32 |= 9;
    D_800E7A33 |= 1;
    bzero(D_800E91D0, 0x5C);
    D_8022A980_ovl_281860 = 1;
    func_802395C0();
}

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

/* Fade step: interpolates +8 from +9 to +0xA over the remaining frames */
void func_80226538_ovl_281860(void) {
    u8 *f = D_8018FC10;

    if (f == NULL) {
        return;
    }
    if (f[7] == 1) {
        u8 *flags = &D_800E7A32;

        *flags |= 2;
        return;
    }
    if (f[7] == 2) {
        f[7] = 0;
    }
    if (*(s16 *)f > 0) {
        s16 n = *(s16 *)f - 1;

        f[8] = f[9] + (f[0xA] - f[9]) * n / *(s16 *)(f + 2);
        *(s16 *)f = n;
    }
}

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
