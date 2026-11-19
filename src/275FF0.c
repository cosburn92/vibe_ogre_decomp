#include "common.h"

/* 275FF0 */

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern s32 D_80220F68;
extern s32 D_80220F6C;
void func_8020DFB8(void);
void func_8020DC80(u16 state);
void func_8020DD34(u16 state);
void func_8020DF00(void (*fn)());
void func_8020E0B4(s32 a, s32 b);
void func_80207CE4(u8 *p);
void func_80207F30(u8 a, s32 b, s32 c);
void func_80207FA0(u8 *a, s32 b, s32 c);
void func_8022237C_ovl_275850();
void func_8022202C_ovl_275850();
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/275FF0", func_80221860_ovl_275850);

INCLUDE_ASM("asm/nonmatchings/275FF0", func_80221B60_ovl_275850);

INCLUDE_ASM("asm/nonmatchings/275FF0", func_80221D8C_ovl_275850);

INCLUDE_ASM("asm/nonmatchings/275FF0", func_8022202C_ovl_275850);

s32 func_80222208_ovl_275850(u16 msg, u8 *o) {
    s32 r = 0;

    switch (msg) {
        case 0x101:
            func_8020DFB8();
            break;
        case 0x100:
            FIELD(o, s32, 0) = D_80220F68;
            FIELD(o, s32, 4) = D_80220F6C;
            func_8020DC80(0x1000);
            break;
        case 0x1000:
            func_80207CE4(FIELD(o, u8 *, 0));
            func_8020E0B4(-1, 0x1002);
            break;
        case 0x1002:
            func_8020DC80(0x1003);
            /* fallthrough */
        case 0x1003:
            D_80220F6C = FIELD(o, s32, 4);
            func_8020DF00(func_8022202C_ovl_275850);
            func_8020E0B4(-1, 0x1004);
            break;
        case 0x1004:
            func_80207F30(*FIELD(o, u8 *, 4), 0, 0x28);
            func_80207FA0(FIELD(o, u8 *, 4) + 1, 0x23, 0xF);
            func_8020E0B4(0x50, 0x1005);
            break;
        case 0x1005:
            func_8020DD34(0x101);
            break;
        default:
            r = 0;
            break;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/275FF0", func_8022237C_ovl_275850);

s32 func_80222558_ovl_275850(u16 msg, u8 *o) {
    switch (msg) {
        case 0x101:
            func_8020DFB8();
            break;
        case 0x100:
            FIELD(o, s32, 0) = D_80220F68;
            FIELD(o, s32, 4) = D_80220F6C;
            func_8020DC80(0x1000);
            break;
        case 0x1000:
            func_80207CE4(FIELD(o, u8 *, 0));
            func_8020E0B4(-1, 0x1002);
            break;
        case 0x1002:
            func_8020DC80(0x1003);
            /* fallthrough */
        case 0x1003:
            D_80220F6C = FIELD(o, s32, 4);
            func_8020DF00(func_8022237C_ovl_275850);
            func_8020E0B4(-1, 0x1004);
            break;
        case 0x1004:
            func_80207F30(*FIELD(o, u8 *, 4), 5, 0x23);
            func_80207FA0(FIELD(o, u8 *, 4) + 1, 0x1E, 0xF);
            func_8020E0B4(0x5A, 0x1005);
            break;
        case 0x1005:
            func_8020DD34(0x101);
            break;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/275FF0", func_802226B8_ovl_275850);
