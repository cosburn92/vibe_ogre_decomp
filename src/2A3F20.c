#include "common.h"

/* 2A3F20 */

typedef struct {
    u8 unk0[0xC];
    void *data;
} Res2A3;

typedef struct {
    u8 unk0000[0x1CA4];
    Res2A3 *res;
} Battle2A3;

extern Battle2A3 *D_8022A974;

void *HFree(void *p);
void func_8022B6F4_ovl_29A4C0(void);
void func_80233398_ovl_29A4C0(void);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/2A3F20", func_802346F0_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/2A3F20", func_80234770_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/2A3F20", func_80234814_ovl_29A4C0);

void func_80234BE0_ovl_29A4C0(void) {
    func_8022B6F4_ovl_29A4C0();
    func_80233398_ovl_29A4C0();
}

INCLUDE_ASM("asm/nonmatchings/2A3F20", func_80234C04_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/2A3F20", func_80234CBC_ovl_29A4C0);

void func_80234E50_ovl_29A4C0(void) {
    Res2A3 *r = D_8022A974->res;

    if (r != NULL) {
        HFree(r->data);
        HFree(r);
        D_8022A974->res = NULL;
    }
}
