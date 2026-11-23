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

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern s16 D_80220F70;
s16 func_801F70E0_ovl_24BCA0(u8 id);
u8 func_801BE034(u8 id);
void func_801C893C(s32 id, s32 v);
extern u8 D_8018AA82[][16];

typedef struct {
    /* 0x00 */ u8 *src;
    /* 0x04 */ u8 *list;
    /* 0x08 */ s16 spell;
    /* 0x0A */ s16 i;
} Spell25D;

#ifdef NON_MATCHING
/* 1 word: in the 0x1002 case the original masks the list byte (andi) before comparing with 0xFF; here GCC knows it is zero-extended */
s32 func_80209420_ovl_24BCA0(u16 msg, u8 *o) {
    s32 next;
    s32 next2;
    u8 *lp;
    u16 c;
    s16 i;

    switch (msg) {
        case 0x101:
            func_8020DFB8();
            break;
        case 0x100:
            FIELD(o, u8 *, 0) = D_80220F68;
            FIELD(o, u8 *, 4) = D_80220F6C;
            FIELD(o, s16, 8) = D_80220F70;
            FIELD(o, s16, 10) = 0;
            if (func_801F70E0_ovl_24BCA0(*FIELD(o, u8 *, 4)) != 0) {
                FIELD(o, s16, 10)++;
            }
            func_8020DC80(0x1000);
            break;
        case 0x1000:
            func_8020E0B4(0xF, D_8018AA82[func_801BE034(FIELD(o, u8, 9))][0] == 5 ? 0x1002 : 0x1001);
            break;
        case 0x1001:
            switch (FIELD(o, s16, 8)) {
                case 0x61:
                case 0x66:
                    next = 0x1003;
                    break;
                case 0x79:
                    c = FIELD(o, u8 *, 4)[FIELD(o, s16, 10)];
                    if ((u8)c == 0xFF) {
                        func_801C893C(c, -1);
                        next = 0x1005;
                        break;
                    }
                default:
                    next = 0x1005;
                    break;
            }
            for (i = FIELD(o, s16, 10); FIELD(o, u8 *, 4)[i] != 0xFF; i++) {
                func_801C893C(FIELD(o, u8 *, 4)[i], 0);
            }
            func_8020E0B4(5, next);
            break;
        case 0x1002:
            next2 = 0x1002;
            c = *(lp = &FIELD(o, u8 *, 4)[FIELD(o, s16, 10)]);
            if ((c & 0xFF) != 0xFF) {
                func_801C893C(*lp, 0);
            }
            if (FIELD(o, u8 *, 4)[++FIELD(o, s16, 10)] == 0xFF) {
                next2 = 0x1005;
                if (FIELD(o, s16, 8) == 0x6B) {
                    next2 = 0x1003;
                }
            }
            func_8020E0B4(5, next2);
            break;
        case 0x1003:
            func_801C893C(*FIELD(o, u8 *, 0), 0);
            func_8020E0B4(5, 0x1005);
            break;
        case 0x1005:
            func_8020DD34(0x101);
            break;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/25DD90", func_80209420_ovl_24BCA0);
#endif
