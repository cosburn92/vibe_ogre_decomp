#include "common.h"

/* 128D50 */

typedef struct {
    u8 unk0;
    u8 flags;
    u8 rest[0x17];
} SquadRec; /* size 0x19 */

typedef struct {
    u8 unk0[4];
    u8 squad;
} MapUnit12;

extern SquadRec gSquads[];
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/128D50", func_801D4610_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/128D50", func_801D469C_ovl_101CE0);

void func_801D4738_ovl_101CE0(void) {
}

INCLUDE_ASM("asm/nonmatchings/128D50", func_801D4740_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/128D50", func_801D4928_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/128D50", func_801D4A74_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/128D50", func_801D4B28_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/128D50", func_801D4F3C_ovl_101CE0);

void func_801D51D8_ovl_101CE0(MapUnit12 *u) {
    SquadRec *s = &gSquads[u->squad];

    s->flags &= ~4;
}

void func_801D5208_ovl_101CE0(MapUnit12 *u) {
    SquadRec *s = &gSquads[u->squad];

    s->flags |= 4;
}

INCLUDE_ASM("asm/nonmatchings/128D50", func_801D5238_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/128D50", func_801D5910_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/128D50", func_801D5A60_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/128D50", func_801D5E34_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/128D50", func_801D60E8_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/128D50", func_801D6218_ovl_101CE0);
