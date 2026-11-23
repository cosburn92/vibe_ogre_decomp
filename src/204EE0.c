#include "common.h"

/* 204EE0 */

u8 *func_801C2CE4_ovl_1F0A30(s32 a);
/* --- end decls --- */

/* Entry i of a chunk that starts with an offset table */
inline u8 *func_801C1A50_ovl_1F0A30(s32 a, s32 i) {
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

s32 func_801BE138_ovl_1F0A30(s32 a, s32 b, s32 c, s32 d);
extern u8 D_801CEEE0_ovl_1F0A30[];

/* Opcode of command k in list `layout` of the resource for (a, b, c, d), with up to three operand
 * bytes copied out (commands are variable length, D_801CEEE0[op] bytes); 0 past the end */
u8 func_801C1AA4_ovl_1F0A30(s32 a, s32 b, s32 c, s32 d, s32 layout, u32 k, u8 *p0, u8 *p1, u8 *p2) {
    u8 *s = func_801C1A50_ovl_1F0A30(func_801BE138_ovl_1F0A30(a, b, c, d), layout);
    u32 n = *s++;
    u32 i;

    for (i = 0; i < n; i++) {
        if (i == k) {
            switch (D_801CEEE0_ovl_1F0A30[s[0]]) {
            case 2:
                if (p0 != NULL) {
                    *p0 = s[1];
                }
                break;
            case 3:
                if (p0 != NULL) {
                    *p0 = s[1];
                }
                if (p1 != NULL) {
                    *p1 = s[2];
                }
                break;
            case 4:
                if (p0 != NULL) {
                    *p0 = s[1];
                }
                if (p1 != NULL) {
                    *p1 = s[2];
                }
                if (p2 != NULL) {
                    *p2 = s[3];
                }
                break;
            }
            return s[0];
        }
        s += D_801CEEE0_ovl_1F0A30[s[0]];
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/204EE0", func_801C1C1C_ovl_1F0A30);
