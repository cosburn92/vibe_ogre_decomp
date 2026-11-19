#include "common.h"

/* 283DF0 */

extern s32 D_8022A950_ovl_281860;
extern s32 D_8022A954_ovl_281860;
extern void *D_8022A958_ovl_281860;
extern void *D_8022A95C_ovl_281860;
extern u16 D_800C4B28;

void *HFree(void *p);
void func_80227FD8_ovl_281860(s32 a, s32 b);
/* --- end decls --- */

#ifdef NON_MATCHING
/* Delay-slot use differs by one instruction. */
s32 func_80227E20_ovl_281860(void) {
    if (D_8022A95C_ovl_281860 != NULL) {
        return 1;
    }
    return D_8022A958_ovl_281860 == NULL;
}
#else
INCLUDE_ASM("asm/nonmatchings/283DF0", func_80227E20_ovl_281860);
#endif

INCLUDE_ASM("asm/nonmatchings/283DF0", func_80227E44_ovl_281860);

INCLUDE_ASM("asm/nonmatchings/283DF0", func_80227FD8_ovl_281860);

void func_80228180_ovl_281860(void) {
    HFree(D_8022A958_ovl_281860);
    D_8022A958_ovl_281860 = NULL;
    D_8022A950_ovl_281860 = 0;
}

void func_802281B4_ovl_281860(void) {
    HFree(D_8022A958_ovl_281860);
    HFree(D_8022A95C_ovl_281860);
    D_8022A958_ovl_281860 = NULL;
    D_8022A95C_ovl_281860 = NULL;
    D_8022A950_ovl_281860 = 0;
}

void func_802281FC_ovl_281860(s32 a) {
    HFree(D_8022A958_ovl_281860);
    D_8022A958_ovl_281860 = NULL;
    func_80227FD8_ovl_281860(a, 0);
}

void func_80228240_ovl_281860(s32 a) {
    func_80227FD8_ovl_281860(a, 1);
}

/* Frees the current buffer and promotes the pending one */
void func_8022825C_ovl_281860(void) {
    void *next;
    s32 n;

    HFree(D_8022A958_ovl_281860);
    n = D_8022A954_ovl_281860;
    next = D_8022A95C_ovl_281860;
    D_8022A958_ovl_281860 = NULL;
    D_8022A950_ovl_281860 = 0;
    D_8022A95C_ovl_281860 = NULL;
    D_8022A950_ovl_281860 = n;
    D_8022A958_ovl_281860 = next;
}

INCLUDE_ASM("asm/nonmatchings/283DF0", func_802282B8_ovl_281860);

INCLUDE_ASM("asm/nonmatchings/283DF0", func_8022A1F8_ovl_281860);

INCLUDE_ASM("asm/nonmatchings/283DF0", func_8022A32C_ovl_281860);

/* Index of the (0x80000005, a) pair in the list, or 0 */
s32 func_8022A428_ovl_281860(s32 a, s32 *p) {
    s32 i;

    for (i = 0; i < 0xFFFFFFF; i++, p++) {
        if (p[0] == 0x80000005 && p[1] == a) {
            return i;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/283DF0", func_8022A474_ovl_281860);

s32 func_8022A528_ovl_281860(s32 mask) {
    s32 r;

    if (mask) {
        r = (D_800C4B28 & mask) == 0;
    } else {
        r = D_800C4B28;
    }
    return r;
}

void func_8022A554_ovl_281860(void) {
    func_80227FD8_ovl_281860(2, 1);
}

INCLUDE_ASM("asm/nonmatchings/283DF0", func_8022A574_ovl_281860);

INCLUDE_ASM("asm/nonmatchings/283DF0", func_8022A650_ovl_281860);
