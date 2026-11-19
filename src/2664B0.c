#include "common.h"

/* 2664B0 */

void func_80211C10_ovl_25EE90(void *p);
void func_80211E80_ovl_25EE90(void *p);
void func_80212220_ovl_25EE90(void *p);
void func_80212558_ovl_25EE90(void *p);
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

INCLUDE_ASM("asm/nonmatchings/2664B0", func_80212488_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/2664B0", func_80212558_ovl_25EE90);

s32 func_80212814_ovl_25EE90(u8 *p) {
    func_80212558_ovl_25EE90(p + 0x18);
    return 0;
}
