#include "common.h"

/* 15DF70 */

extern void *D_80213EE8_ovl_14EBE0;

void *HFree(void *p);
extern u8 D_801F36A0;
extern s32 D_801F401C;
extern u8 D_80213EA4_ovl_14EBE0[];
void *LoadChunk(s32 id);
extern s32 D_80213EA0_ovl_14EBE0;
extern u8 D_80213EEC_ovl_14EBE0;
extern s32 D_80213EF0_ovl_14EBE0;
void func_80200DD0_ovl_14EBE0(s32 x, s32 y, s32 tile);
void func_80200F70_ovl_14EBE0(void *a, void *b, s32 c, s32 d, s32 e);
typedef struct {
    u32 w0;
    u32 w1;
} Gfx;
extern Gfx *D_800E9BA0;
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
/* --- end decls --- */

void func_8020CE00_ovl_14EBE0(void) {
    D_80213EE8_ovl_14EBE0 = NULL;
}

void func_8020CE0C_ovl_14EBE0(void) {
    u8 f;

    if (D_80213EE8_ovl_14EBE0 == NULL) {
        D_80213EE8_ovl_14EBE0 = LoadChunk(0x1DC326E);
    }
    f = D_801F36A0;
    if ((f & 1) && !(f & 4) && D_801F401C < 100) {
        s32 i;

        if (!(f & 2)) {
            i = 0x30;
        } else {
            i = 0x18;
        }
        D_80213EA4_ovl_14EBE0[i] = 1;
    }
}

void func_8020CE8C_ovl_14EBE0(void) {
    if (D_80213EE8_ovl_14EBE0 != NULL) {
        HFree(D_80213EE8_ovl_14EBE0);
    }
    D_80213EE8_ovl_14EBE0 = NULL;
}

INCLUDE_ASM("asm/nonmatchings/15DF70", func_8020CEBC_ovl_14EBE0);

/* Draws cursor k (12-byte records at D_80213EA0: list pointer, index at +4) at its list
 * entry's position, flipped one way when the entry has flag 0x8000 */
#ifdef NON_MATCHING
/* cursor draw: entry address loads scheduled differently */
void func_8020D210_ovl_14EBE0(u8 k) {
    u8 *e = *(u8 **)((u8 *)&D_80213EA0_ovl_14EBE0 + k * 12) + D_80213EA4_ovl_14EBE0[k * 12] * 10;
    s32 x = FIELD(e, s16, 0);
    s32 y = FIELD(e, s16, 2);

    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xDE000000;
        _g->w1 = (u32)&D_80213EF0_ovl_14EBE0;
    }
    func_80200F70_ovl_14EBE0((u8 *)D_80213EE8_ovl_14EBE0 + ((D_80213EEC_ovl_14EBE0 * 8) & 0x20),
                             (u8 *)D_80213EE8_ovl_14EBE0 + 0x40, 0x20, 0x10, 1);
    if (FIELD(e, u16, 8) & 0x8000) {
        func_80200DD0_ovl_14EBE0(x + 16, y, 0x37);
    } else {
        func_80200DD0_ovl_14EBE0(x, y, 0x38);
    }
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xE7000000;
        _g->w1 = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/15DF70", func_8020D210_ovl_14EBE0);
#endif

INCLUDE_ASM("asm/nonmatchings/15DF70", func_8020D328_ovl_14EBE0);
