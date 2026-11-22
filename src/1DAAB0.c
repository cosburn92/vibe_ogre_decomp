#include "common.h"

/* 1DAAB0 */

extern u8 D_801BA6E1_ovl_1CE070;

void func_8019915C_ovl_1CE070(void);
void func_80199518_ovl_1CE070(void);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/1DAAB0", func_801A45B0_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1DAAB0", func_801A49CC_ovl_1CE070);

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;
#include "gbi_ultra.h"
extern Gfx *D_800E9BA0;
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern u8 D_801B8730_ovl_1CE070[];
extern u8 D_801B8740_ovl_1CE070[];
void func_8017C4B4(s16 id);
void func_8017A704(void);
void func_8017A714(void);
u16 func_801794C8(u8 *s);
void func_801793AC(u8 *s, s32 x, s32 y);

/* Draws window w's title for entry i: palette D_801B8740 (16 colours), text D_801B8730
 * centred in a 256-px bar at the window's x, 6 px below its top */
#ifdef NON_MATCHING
/* window title: one extra saved register */
void func_801A5190_ovl_1CE070(u8 *w, s32 i) {
    u32 pad;

    func_8017C4B4(FIELD(w + i * 2, s16, 0x18));
    gDPSetTextureLUT(D_800E9BA0++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(D_800E9BA0++, 0, D_801B8740_ovl_1CE070);
    func_8017A704();
    gDPPipeSync(D_800E9BA0++);
    pad = 256 - func_801794C8(D_801B8730_ovl_1CE070);
    func_801793AC(D_801B8730_ovl_1CE070, FIELD(w, s32, 0x2C) + pad / 2, FIELD(w, s32, 0x30) + 6);
    func_8017A714();
}
#else
INCLUDE_ASM("asm/nonmatchings/1DAAB0", func_801A5190_ovl_1CE070);
#endif

INCLUDE_ASM("asm/nonmatchings/1DAAB0", func_801A5300_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1DAAB0", func_801A576C_ovl_1CE070);

void func_801A590C_ovl_1CE070(void) {
}

void func_801A5190_ovl_1CE070(u8 *w, s32 i);
void *func_8017C074(u16 kind, u8 b, void (*fn)(), s16 x, s16 y, s16 w, s16 h);
void func_801A49CC_ovl_1CE070();
void func_801A5300_ovl_1CE070(void);
extern void *D_801BA550_ovl_1CE070;
extern u8 *D_801BA554_ovl_1CE070;
extern s32 *D_801BA558_ovl_1CE070;
extern s32 *D_801BA55C_ovl_1CE070;
extern s32 D_801BA6EC_ovl_1CE070;

/* Menu step: 0 starts, 1 opens the title bar and list windows, 2 runs the list; then points
 * D_801BA558 at the current entry */
s32 func_801A5914_ovl_1CE070(void) {
    switch (D_801BA6EC_ovl_1CE070) {
        case 0:
            D_801BA6E1_ovl_1CE070 = 1;
            D_801BA6EC_ovl_1CE070 = 1;
            break;
        case 1:
            func_8017C074(0, 0, func_801A5190_ovl_1CE070, 0x20, 0x20, 0x120, 0x3A);
            func_8017C074(0x400, 0, func_801A49CC_ovl_1CE070, 0x20, 0x44, 0x120, 0xD0);
            *D_801BA554_ovl_1CE070 = 1;
            D_801BA6EC_ovl_1CE070++;
            break;
        case 2:
            func_801A5300_ovl_1CE070();
            break;
    }
    D_801BA558_ovl_1CE070 = D_801BA55C_ovl_1CE070 + FIELD(D_801BA550_ovl_1CE070, s32, 0xC);
    return 0;
}

void func_801A5A34_ovl_1CE070(void) {
    func_8019915C_ovl_1CE070();
    if (D_801BA6E1_ovl_1CE070) {
        func_80199518_ovl_1CE070();
    }
}
