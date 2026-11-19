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
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/276FE0", func_80222850_ovl_275850);

INCLUDE_ASM("asm/nonmatchings/276FE0", func_80222DD8_ovl_275850);

INCLUDE_ASM("asm/nonmatchings/276FE0", func_80222F84_ovl_275850);

INCLUDE_ASM("asm/nonmatchings/276FE0", func_80223144_ovl_275850);

INCLUDE_ASM("asm/nonmatchings/276FE0", func_802232B0_ovl_275850);

INCLUDE_ASM("asm/nonmatchings/276FE0", func_8022341C_ovl_275850);

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
