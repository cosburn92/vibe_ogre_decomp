#include "common.h"

/* 2A3150 */

u8 *func_80232E44_ovl_29A4C0(s32 a, s32 b);
/* --- end decls --- */

u8 *func_80233920_ovl_29A4C0(s32 a, s32 i, s32 b) {
    u8 *p = func_80232E44_ovl_29A4C0(a, b);

    if (p != NULL) {
        return (u8 *)(((s32 *)p)[i] + (s32)p);
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/2A3150", func_80233968_ovl_29A4C0);
