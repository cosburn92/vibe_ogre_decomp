#include "common.h"

/* 204EE0 */

u8 *func_801C2CE4_ovl_1F0A30(s32 a);
/* --- end decls --- */

/* Entry i of a chunk that starts with an offset table */
u8 *func_801C1A50_ovl_1F0A30(s32 a, s32 i) {
    u8 *p = func_801C2CE4_ovl_1F0A30(a);

    if (p != NULL) {
        return (u8 *)(((s32 *)p)[i] + (s32)p);
    }
    return NULL;
}

void func_801C1A94_ovl_1F0A30(void) {
}

void func_801C1A9C_ovl_1F0A30(void) {
}

INCLUDE_ASM("asm/nonmatchings/204EE0", func_801C1AA4_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/204EE0", func_801C1C1C_ovl_1F0A30);
