#include "common.h"

/* 1ED1D0 */

void nuGfxTaskAllEndWait(void);
s32 func_801B7B7C_ovl_1CE070(void);
extern u8 D_800E7A0C;
extern void *D_800C4BB8;
extern void *D_800A8204[3];
extern u8 D_800E7A0C;
extern void *D_800C4BB8;
extern void *D_800A8204[3];
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/1ED1D0", BgJpegTask);

INCLUDE_ASM("asm/nonmatchings/1ED1D0", func_801B6E48_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1ED1D0", func_801B6F90_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1ED1D0", func_801B7388_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1ED1D0", func_801B73D4_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1ED1D0", func_801B75B8_ovl_1CE070);

/* Reports which frame buffer pair is current (o[0], o[1]) */
/* Reports which frame buffer pair is current (o[0], o[1]) */
void func_801B77B8_ovl_1CE070(u8 *o) {
    nuGfxTaskAllEndWait();
    o[0] = 0;
    o[1] = 1;
    if (D_800E7A0C == 1) {
        if (D_800C4BB8 == D_800A8204[0]) {
            o[0] = 1;
            o[1] = 2;
        } else if (D_800C4BB8 == D_800A8204[1]) {
            o[0] = 0;
            o[1] = 2;
        } else if (D_800C4BB8 == D_800A8204[2]) {
            o[0] = 0;
            o[1] = 1;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/1ED1D0", BgDecodeHu);

INCLUDE_ASM("asm/nonmatchings/1ED1D0", func_801B7B7C_ovl_1CE070);

INCLUDE_ASM("asm/nonmatchings/1ED1D0", BgLoad);

void func_801B8048_ovl_1CE070(void) {
    do {
        nuGfxTaskAllEndWait();
    } while (!func_801B7B7C_ovl_1CE070());
}
