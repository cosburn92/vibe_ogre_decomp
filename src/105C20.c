#include "common.h"

/* 105C20 */

typedef struct {
    u32 w[0x30];
} Unit105; /* size 0xC0 */

extern Unit105 D_801F38D8_ovl_101CE0;

void _bcopy(void *src, void *dst, s32 n);
/* --- end decls --- */

/* Saves a copy of the unit (with flag 0x80000 cleared) */
void func_801B14E0_ovl_101CE0(Unit105 *u) {
    u->w[0] &= ~0x80000;
    D_801F38D8_ovl_101CE0 = *u;
}

/* Restores the saved unit, keeping its +0xA8 word */
void func_801B1538_ovl_101CE0(Unit105 *u) {
    u32 keep = u->w[0x2A];

    _bcopy(&D_801F38D8_ovl_101CE0, u, sizeof(Unit105));
    u->w[0x2A] = keep;
}
