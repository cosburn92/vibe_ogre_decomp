#include "common.h"

/* 23B220 */

typedef struct {
    u8 unk00[0xD0];
    u8 bD0;
} Ent23B;

extern u8 *D_801D0810;
extern u8 D_801EFCB0_ovl_23B220[];

Ent23B *func_801C8FE8(s16 a);
/* --- end decls --- */

void func_801E6FB0_ovl_23B220(void) {
    D_801D0810 = D_801EFCB0_ovl_23B220;
}

s32 func_801E6FC4_ovl_23B220(void) {
    return 1;
}

void func_801E6FCC_ovl_23B220(void) {
}

void func_801E6FD4_ovl_23B220(void) {
}

void func_801E6FDC_ovl_23B220(s16 a) {
    func_801C8FE8(a)->bD0 = 1;
}

INCLUDE_ASM("asm/nonmatchings/23B220", func_801E7004_ovl_23B220);

u8 func_801E7164_ovl_23B220(u8 *p) {
    return p[0xA4];
}
