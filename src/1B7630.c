#include "common.h"

/* 1B7630 */

u8 *func_80219F40_ovl_1B2670(u8 *t, u32 page);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/1B7630", func_80219F40_ovl_1B2670);

/* Palette that follows the pixel data of image t's page (NULL if the page has none) */
u8 *func_8021A064_ovl_1B2670(u8 *t, u32 page) {
    u8 *e = func_80219F40_ovl_1B2670(t, page);
    u16 w;
    s32 h;
    s32 stride;

    if (e == NULL) {
        return NULL;
    }
    w = *(u16 *)(t + 4);
    h = *(u16 *)(t + 6);
    if (e[3] & 2) {
        if (!(e[3] & 1)) {
            return e + 8;
        }
        if (t[3] & 2) {
            stride = ((u32)(w + 3) >> 2) << 4;
        } else if (t[3] & 4) {
            stride = ((u32)(w + 7) >> 3) << 3;
        } else {
            stride = ((u32)(w + 3) >> 2) << 3;
        }
        return e + (stride * h + 8);
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021A110_ovl_1B2670);

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021A208_ovl_1B2670);

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021AAE8_ovl_1B2670);

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021B040_ovl_1B2670);

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021B31C_ovl_1B2670);

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021B5EC_ovl_1B2670);

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021B93C_ovl_1B2670);

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021BA30_ovl_1B2670);

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021BB5C_ovl_1B2670);
