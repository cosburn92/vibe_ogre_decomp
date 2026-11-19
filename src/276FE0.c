#include "common.h"

/* 276FE0 */

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern s32 D_80220F6C;
extern u8 D_8022574E_ovl_275850[];
extern u8 D_80225754_ovl_275850[];
extern u8 D_80225760_ovl_275850[];
void func_8020DFB8(void);
void func_8020DC80(u16 state);
void func_801F8E50(u8 id, u8 *s);
void func_801F9060(u8 id, u8 *s, s32 n);
void func_8020E0B4(s32 a, s32 b);
extern u8 D_80225766_ovl_275850[];
extern s32 D_80220F68;
extern u8 D_80225772_ovl_275850[];
void func_80207CE4(u8 *p);
void func_801F9DFC(s32 a, u8 b, s32 c);
void func_80207F30(u8 a, s32 b, s32 c);
void func_8020DD34(u16 state);
void func_8020DF00(void *fn);
void func_80207FA0(u8 *a, s32 b, s32 c);
s32 func_8022353C_ovl_275850(u16 msg, u8 *o);
s32 func_802235D0_ovl_275850(u16 msg, u8 *o);
s32 func_80223698_ovl_275850(u16 msg, u8 *o);
s32 func_8022372C_ovl_275850(u16 msg, u8 *o);
extern u8 D_80225742_ovl_275850[];
s32 func_80222850_ovl_275850(u16 msg, u8 *o);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/276FE0", func_80222850_ovl_275850);

s32 func_80222DD8_ovl_275850(u16 msg, u8 *o) {
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
            D_80220F68 = FIELD(o, s32, 0);
            D_80220F6C = FIELD(o, s32, 4);
            func_801F9DFC(0, *FIELD(o, u8 *, 0), 0x3B);
            if (*FIELD(o, u8 *, 0) != *FIELD(o, u8 *, 4)) {
                func_8020DF00(func_80222850_ovl_275850);
                func_8020E0B4(-1, 0x1003);
            } else {
                func_8020DC80(0x101);
            }
            break;
        case 0x1003:
            func_801F9DFC(0, *FIELD(o, u8 *, 0), 0x3C);
            func_801F8E50(*FIELD(o, u8 *, 4), D_80225742_ovl_275850);
            func_80207F30(*FIELD(o, u8 *, 4), 0xF, 0xF);
            func_8020E0B4(0x2D, 0x1004);
            break;
        case 0x1004:
            func_8020DD34(0x101);
            break;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/276FE0", func_80222F84_ovl_275850);

s32 func_80223144_ovl_275850(u16 msg, u8 *o) {
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
            D_80220F6C = FIELD(o, s32, 4);
            func_801F9DFC(0, *FIELD(o, u8 *, 0), 0x3F);
            func_8020DF00(func_8022353C_ovl_275850);
            func_8020DF00(func_802235D0_ovl_275850);
            func_8020DC80(0x1003);
            break;
        case 0x1003:
            func_80207F30(*FIELD(o, u8 *, 4), 0x19, 0x28);
            func_80207FA0(FIELD(o, u8 *, 4) + 1, 0x1E, 0x14);
            func_8020E0B4(0x46, 0x1004);
            break;
        case 0x1004:
            func_8020DD34(0x101);
            break;
    }
    return 0;
}

s32 func_802232B0_ovl_275850(u16 msg, u8 *o) {
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
            D_80220F6C = FIELD(o, s32, 4);
            func_801F9DFC(0, *FIELD(o, u8 *, 0), 0x40);
            func_8020DF00(func_80223698_ovl_275850);
            func_8020DF00(func_8022372C_ovl_275850);
            func_8020DC80(0x1003);
            break;
        case 0x1003:
            func_80207F30(*FIELD(o, u8 *, 4), 5, 0x46);
            func_80207FA0(FIELD(o, u8 *, 4) + 1, 0x1E, 0x1E);
            func_8020E0B4(0x50, 0x1004);
            break;
        case 0x1004:
            func_8020DD34(0x101);
            break;
    }
    return 0;
}

s32 func_8022341C_ovl_275850(u16 msg, u8 *o) {
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
            func_801F9DFC(0, *FIELD(o, u8 *, 0), 0x41);
            func_801F8E50(*FIELD(o, u8 *, 4), D_80225772_ovl_275850);
            func_80207F30(*FIELD(o, u8 *, 4), 0x23, 0x19);
            func_8020E0B4(0x37, 0x1003);
            break;
        case 0x1003:
            func_8020DD34(0x101);
            break;
    }
    return 0;
}

s32 func_8022353C_ovl_275850(u16 msg, u8 *o) {
    switch (msg) {
        case 0x101:
            func_8020DFB8();
            break;
        case 0x100:
            FIELD(o, s32, 4) = D_80220F6C;
            func_8020DC80(0x1000);
            break;
        case 0x1000:
            func_801F8E50(*FIELD(o, u8 *, 4), D_8022574E_ovl_275850);
            func_8020DC80(0x101);
            break;
    }
    return 0;
}

s32 func_802235D0_ovl_275850(u16 msg, u8 *o) {
    switch (msg) {
        case 0x101:
            func_8020DFB8();
            break;
        case 0x100:
            FIELD(o, s32, 4) = D_80220F6C;
            func_8020E0B4(10, 0x1000);
            break;
        case 0x1000:
            func_801F9060(*FIELD(o, u8 *, 4), D_80225754_ovl_275850, 14);
            func_801F8E50(*FIELD(o, u8 *, 4), D_80225754_ovl_275850 + 6);
            func_8020DC80(0x101);
            break;
    }
    return 0;
}

s32 func_80223698_ovl_275850(u16 msg, u8 *o) {
    switch (msg) {
        case 0x101:
            func_8020DFB8();
            break;
        case 0x100:
            FIELD(o, s32, 4) = D_80220F6C;
            func_8020DC80(0x1000);
            break;
        case 0x1000:
            func_801F8E50(*FIELD(o, u8 *, 4), D_80225760_ovl_275850);
            func_8020DC80(0x101);
            break;
    }
    return 0;
}

s32 func_8022372C_ovl_275850(u16 msg, u8 *o) {
    switch (msg) {
        case 0x101:
            func_8020DFB8();
            break;
        case 0x100:
            FIELD(o, s32, 4) = D_80220F6C;
            func_8020E0B4(10, 0x1000);
            break;
        case 0x1000:
            func_801F9060(*FIELD(o, u8 *, 4), D_80225766_ovl_275850, 14);
            func_801F8E50(*FIELD(o, u8 *, 4), D_80225766_ovl_275850 + 6);
            func_8020DC80(0x101);
            break;
    }
    return 0;
}
