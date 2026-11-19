#include "common.h"

/* 2664B0 */

void func_80211C10_ovl_25EE90(void *p);
void func_80211E80_ovl_25EE90(void *p);
void func_80212220_ovl_25EE90(void *p);
void func_80212558_ovl_25EE90(void *p);
typedef struct {
    u32 w0;
    u32 w1;
} Gfx;
extern Gfx *D_800E9BA0;
extern u8 *D_801969B0;
extern Gfx D_802204C0_ovl_25EE90[];
void guMtxF2L(void *mf, void *m);
typedef struct {
    /* 0x00 */ u8 unk00[0x14];
    /* 0x14 */ f32 mtx[4][4];
    /* 0x54 */ Gfx *dl;
} Model266;
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/2664B0", func_80211900_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/2664B0", func_80211C10_ovl_25EE90);

s32 func_80211E40_ovl_25EE90(u8 *p) {
    func_80211C10_ovl_25EE90(p + 0x18);
    return 0;
}

s32 func_80211E60_ovl_25EE90(u8 *p) {
    func_80211C10_ovl_25EE90(p + 0x14);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/2664B0", func_80211E80_ovl_25EE90);

s32 func_80212200_ovl_25EE90(u8 *p) {
    func_80211E80_ovl_25EE90(p + 0x14);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/2664B0", func_80212220_ovl_25EE90);

s32 func_80212468_ovl_25EE90(u8 *p) {
    func_80212220_ovl_25EE90(p + 0x18);
    return 0;
}

/* Draws o's display list (0x54) under its matrix (0x14), after the shared setup list */
s32 func_80212488_ovl_25EE90(Model266 *o) {
    Gfx *g;

    g = D_800E9BA0++;
    g->w0 = 0xDE000000;
    g->w1 = (u32)D_802204C0_ovl_25EE90;
    guMtxF2L(o->mtx, D_801969B0);
    g = D_800E9BA0++;
    g->w0 = 0xDA380000;
    g->w1 = (u32)D_801969B0;
    g = D_800E9BA0++;
    g->w0 = 0xDE000000;
    g->w1 = (u32)o->dl;
    g = D_800E9BA0++;
    g->w0 = 0xD8380002;
    g->w1 = 0x40;
    D_801969B0 += 0x40;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/2664B0", func_80212558_ovl_25EE90);

s32 func_80212814_ovl_25EE90(u8 *p) {
    func_80212558_ovl_25EE90(p + 0x18);
    return 0;
}
