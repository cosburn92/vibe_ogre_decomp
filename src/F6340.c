#include "common.h"

/* F6340 */

extern s16 D_800E7A36;
extern s16 D_800E7A38;
extern s16 D_800E7A3A;
extern s16 D_800E7A3C;
extern u8 *D_801AD100_ovl_0EBBB0;
extern void *D_800E9BA0;

void func_8007705C(s32 a, void *b, s32 c, s32 d, s32 e, s32 f, s32 g);
void func_801AB2A4_ovl_0EBBB0(void);
void func_80078674(s16 a, s16 b, s16 c, s16 d);
void func_8007FB60(void *gfx, void *p);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/F6340", func_801A95E0_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801A9714_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801A9848_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801A997C_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801A9AB0_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801A9DB0_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AA064_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AA15C_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AA248_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AA52C_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AA62C_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AA720_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AA8A4_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AAE10_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AB020_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AB0FC_ovl_0EBBB0);

void func_801AB1D8_ovl_0EBBB0(void) {
    func_8007705C(0xC000, func_801AB2A4_ovl_0EBBB0, 0, 0, 0, 0, 0xF000);
}

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AB214_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AB2A4_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AB33C_ovl_0EBBB0);

void func_801AB55C_ovl_0EBBB0(void) {
    func_80078674(D_800E7A36, D_800E7A38, D_800E7A3A, D_800E7A3C);
    func_8007FB60(&D_800E9BA0, D_801AD100_ovl_0EBBB0 + 4);
}

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AB5B0_ovl_0EBBB0);

/* Reads a big-endian u32 from an unaligned pointer */
u32 func_801AB720_ovl_0EBBB0(u8 *p) {
    return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
}

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AB74C_ovl_0EBBB0);
