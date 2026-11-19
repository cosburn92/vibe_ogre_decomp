#include "common.h"

/* 2B8610 */

extern u8 *D_801CE8BC;
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern u8 *D_8022A974;
s32 func_801C8B68(u8 *u);
s32 func_801C8C58(u8 *u);
void func_8024387C_ovl_2AE3C0(u8 *u, s32 i, s32 a, s32 id, s32 b, u8 slot, s16 c);
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

/* Hands the first eligible army unit (present, not func_801C8B68, func_801C8C58) to func_8024387C for
 * battle slot `slot`, if that slot is occupied */
s32 func_80243AC8_ovl_2AE3C0(s16 slot, s16 b) {
    s32 i;
    u8 *u;

    for (i = 0; i < 20; i++) {
        u = D_801CE8BC + 0x1C4 + i * 0xF8;
        if (FIELD(u, s32, 0x48) != 0 && !func_801C8B68(u) && func_801C8C58(u)) {
            if (FIELD(D_8022A974 + slot * 4, u8 *, 0x18) != NULL) {
                func_8024387C_ovl_2AE3C0(u, i, FIELD(u, s32, 0x58) < 4, FIELD(u, s32, 0x48), FIELD(u, s32, 0x4C),
                                         slot, b);
                return 0;
            }
        }
    }
    return 0;
}
