#include "common.h"

/* 2B8610 */

extern u8 *D_801CE8BC;
extern u8 *D_801CE8C0;
extern u8 D_8022A7F0;

void *HMalloc(s32 size);
void bzero(void *p, s32 n);
void func_801BE71C(void);
void func_801C1D90(void);
void func_801C1A94(void);
void func_801C2310(void);
void func_801AECA4(u8 a);
/* --- end decls --- */

void func_80243810_ovl_2AE3C0(void) {
    u8 *p;

    func_801BE71C();
    p = HMalloc(0x6094);
    D_801CE8BC = p;
    bzero(p, 0x6094);
    D_801CE8C0 = D_801CE8BC + 0x57E0;
    func_801C1D90();
    func_801C1A94();
    func_801C2310();
    func_801AECA4(D_8022A7F0);
}

INCLUDE_ASM("asm/nonmatchings/2B8610", func_8024387C_ovl_2AE3C0);

INCLUDE_ASM("asm/nonmatchings/2B8610", func_80243AC8_ovl_2AE3C0);
