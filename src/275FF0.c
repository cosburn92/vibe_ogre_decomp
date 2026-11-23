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
s32 func_8022237C_ovl_275850(u16 msg, u8 *o);
s32 func_8022202C_ovl_275850(u16 msg, u8 *o);
extern u8 D_80225718_ovl_275850[];
extern u8 D_8022571E_ovl_275850[];
extern u8 D_80225724_ovl_275850[];
void func_801F9DFC(s32 a, u8 b, s32 c);
void func_801F8E50(u8 id, u8 *s);
void func_801F8E90(u8 id, u8 *s);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/275FF0", func_80221860_ovl_275850);

INCLUDE_ASM("asm/nonmatchings/275FF0", func_80221B60_ovl_275850);

INCLUDE_ASM("asm/nonmatchings/275FF0", func_80221D8C_ovl_275850);

void func_8020E0D0();
extern u8 D_802256C4_ovl_275850[];
extern u8 D_802256CA_ovl_275850[];
extern u8 D_802256D0_ovl_275850[];
extern u8 D_802256D6_ovl_275850[];
extern u8 D_802256DC_ovl_275850[];
extern u8 D_802256E8_ovl_275850[];

s32 func_8022202C_ovl_275850(u16 msg, u8 *o) {
    switch (msg) {
        case 0x101:
            func_8020E0D0();
            func_8020DFB8();
            break;
        case 0x100:
            FIELD(o, s32, 4) = D_80220F6C;
            func_8020DC80(0x1001);
            break;
        case 0x1001:
            func_801F9DFC(0, *FIELD(o, u8 *, 0), 0x21);
            func_801F8E50(*FIELD(o, u8 *, 4), D_802256CA_ovl_275850);
            func_801F8E50(*FIELD(o, u8 *, 4), D_802256CA_ovl_275850 + 0x18);
            func_8020E0B4(5, 0x1002);
            break;
        case 0x1002:
            func_801F8E50(*FIELD(o, u8 *, 4), D_802256C4_ovl_275850);
            func_8020E0B4(7, 0x1003);
            break;
        case 0x1003:
            func_8020E0D0();
            func_8020E0B4(0xC, 0x1004);
            break;
        case 0x1004:
            func_801F8E50(*FIELD(o, u8 *, 4), D_802256D0_ovl_275850);
            func_8020E0B4(3, 0x1005);
            break;
        case 0x1005:
            func_801F8E50(*FIELD(o, u8 *, 4), D_802256E8_ovl_275850);
            func_8020E0B4(0xD, 0x1006);
            break;
        case 0x1006:
            func_801F8E50(*FIELD(o, u8 *, 4), D_802256D6_ovl_275850);
            func_8020E0B4(9, 0x1007);
            break;
        case 0x1007:
            func_801F8E50(*FIELD(o, u8 *, 4), D_802256DC_ovl_275850);
            func_8020E0B4(0x23, 0x101);
            break;
    }
    return 0;
}

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

extern u8 D_802256EE_ovl_275850[];
extern u8 D_802256F4_ovl_275850[];
extern u8 D_802256FA_ovl_275850[];
extern u8 D_80225700_ovl_275850[];
extern u8 D_80225706_ovl_275850[];
extern u8 D_80225712_ovl_275850[];

s32 func_8022237C_ovl_275850(u16 msg, u8 *o) {
    switch (msg) {
        case 0x101:
            func_8020E0D0();
            func_8020DFB8();
            break;
        case 0x100:
            FIELD(o, s32, 4) = D_80220F6C;
            func_8020DC80(0x1001);
            break;
        case 0x1001:
            func_801F9DFC(0, *FIELD(o, u8 *, 0), 0x22);
            func_801F8E50(*FIELD(o, u8 *, 4), D_802256F4_ovl_275850);
            func_801F8E50(*FIELD(o, u8 *, 4), D_802256F4_ovl_275850 + 0x18);
            func_8020E0B4(5, 0x1002);
            break;
        case 0x1002:
            func_801F8E50(*FIELD(o, u8 *, 4), D_802256EE_ovl_275850);
            func_8020E0B4(1, 0x1003);
            break;
        case 0x1003:
            func_8020E0D0();
            func_8020E0B4(1, 0x1004);
            break;
        case 0x1004:
            func_801F8E50(*FIELD(o, u8 *, 4), D_802256FA_ovl_275850);
            func_8020E0B4(4, 0x1005);
            break;
        case 0x1005:
            func_801F8E50(*FIELD(o, u8 *, 4), D_80225712_ovl_275850);
            func_8020E0B4(0x1E, 0x1006);
            break;
        case 0x1006:
            func_801F8E50(*FIELD(o, u8 *, 4), D_80225700_ovl_275850);
            func_8020E0B4(9, 0x1007);
            break;
        case 0x1007:
            func_801F8E50(*FIELD(o, u8 *, 4), D_80225706_ovl_275850);
            func_8020E0B4(0x23, 0x101);
            break;
    }
    return 0;
}

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

s32 func_802226B8_ovl_275850(u16 msg, u8 *o) {
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
            func_801F9DFC(0, *FIELD(o, u8 *, 0), 0x23);
            func_801F8E50(*FIELD(o, u8 *, 4), D_80225718_ovl_275850);
            func_8020E0B4(0x15, 0x1003);
            break;
        case 0x1003:
            func_801F8E90(*FIELD(o, u8 *, 4), D_8022571E_ovl_275850);
            func_8020E0B4(1, 0x1004);
            break;
        case 0x1004:
            func_801F8E50(*FIELD(o, u8 *, 4), D_80225724_ovl_275850);
            func_80207F30(*FIELD(o, u8 *, 4), 5, 0xF);
            func_8020E0B4(0x28, 0x1005);
            break;
        case 0x1005:
            func_8020DD34(0x101);
            break;
    }
    return 0;
}
