#include "common.h"

/* 260420 */

typedef struct {
    /* 0x00 */ u16 count;
    /* 0x02 */ u8 unk02[0xA];
    /* 0x0C */ s32 id;
    /* 0x10 */ u8 unk10[4];
} Ent260; /* size 0x14 */

extern s32 D_80220CA0_ovl_25EE90;
extern Ent260 *D_80220CA8_ovl_25EE90;

Ent260 *func_8020BC78_ovl_25EE90(u16 a);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/260420", func_8020B870_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260420", func_8020B940_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260420", func_8020B9D0_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260420", func_8020BA6C_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260420", func_8020BC78_ovl_25EE90);

s32 func_8020BF5C_ovl_25EE90(u16 a) {
    s32 r = 0;
    Ent260 *e = func_8020BC78_ovl_25EE90(a);

    if (e != NULL) {
        r = e->id;
    }
    return r;
}

#ifdef NON_MATCHING
/* Loop shape differs. */
void func_8020BF94_ovl_25EE90(s32 id) {
    s32 pad;
    s32 n = D_80220CA0_ovl_25EE90;
    Ent260 *e = D_80220CA8_ovl_25EE90;
    s32 i;

    for (i = 0; i < n; i++, e++) {
        if (e->id == id) {
            e->count++;
            return;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/260420", func_8020BF94_ovl_25EE90);
#endif

INCLUDE_ASM("asm/nonmatchings/260420", func_8020BFE8_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260420", func_8020C074_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/260420", func_8020C130_ovl_25EE90);
