#include "common.h"

/* 25DD90 */

extern u8 *D_80220F6C;
extern u8 D_8020A1E8_ovl_24BCA0[];
extern u8 D_8020A1F0_ovl_24BCA0[];
void func_8020DFB8(void);
void func_8020DC80(u16 state);
void func_8020DD34(u16 state);
void func_8020E0B4(s32 a, s32 b);
void func_801F8E50_ovl_24BCA0(u8 id, u8 *s);
extern u8 *D_80220F68;
extern u8 D_8020A1E0_ovl_24BCA0[];
s32 func_8020AB9C(u8 a);
s32 func_8020AB8C(s32 a);
void func_801F93BC_ovl_24BCA0(u8 id, u8 *s, s32 v);
/* --- end decls --- */

s32 func_802091D0_ovl_24BCA0(u16 msg, u8 *o) {
    switch (msg) {
        case 0x101:
            func_8020DFB8();
            break;
        case 0x100:
            o[0] = *D_80220F68;
            o[1] = *D_80220F6C;
            func_8020DC80(0x1000);
            break;
        case 0x1000:
            func_801F93BC_ovl_24BCA0(o[1], D_8020A1E0_ovl_24BCA0, func_8020AB8C(func_8020AB9C(o[0])));
            func_8020E0B4(0xF, 0x1001);
            break;
        case 0x1001:
            func_8020DD34(0x101);
            break;
    }
    return 0;
}

s32 func_802092B8_ovl_24BCA0(u16 msg, u8 *o) {
    switch (msg) {
        case 0x101:
            func_8020DFB8();
            break;
        case 0x100:
            o[0] = *D_80220F6C;
            func_8020DC80(0x1000);
            break;
        case 0x1000:
            func_801F8E50_ovl_24BCA0(o[0], D_8020A1E8_ovl_24BCA0);
            func_8020E0B4(0x12, 0x1001);
            break;
        case 0x1001:
            func_8020DD34(0x101);
            break;
    }
    return 0;
}

s32 func_8020936C_ovl_24BCA0(u16 msg, u8 *o) {
    switch (msg) {
        case 0x101:
            func_8020DFB8();
            break;
        case 0x100:
            o[0] = *D_80220F6C;
            func_8020DC80(0x1000);
            break;
        case 0x1000:
            func_801F8E50_ovl_24BCA0(o[0], D_8020A1F0_ovl_24BCA0);
            func_8020E0B4(0x12, 0x1001);
            break;
        case 0x1001:
            func_8020DD34(0x101);
            break;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/25DD90", func_80209420_ovl_24BCA0);
