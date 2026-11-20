#include "common.h"

/* C2330 */

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern u8 *D_80196AF8;
extern u8 D_801EF474_ovl_087200[];
extern s8 D_801EF480_ovl_087200[];
u8 func_801D6508_ovl_087200(void);
extern u8 D_801EF487_ovl_087200[];
/* --- end decls --- */

/* Whether grid cell pos of squad sq has a neighbour (by D_801EF474 direction mask) other than m */
/* neighbour scan: register assignment differs */
#ifdef NON_MATCHING
/* neighbour scan: register assignment differs */
u8 func_801D58D0_ovl_087200(u16 sq, u8 m, u8 pos) {
    s32 n = 0;
    s32 k;
    u8 mask;
    u8 *q;
    u8 c;

    if (pos >= 9) {
        return n;
    }
    mask = D_801EF474_ovl_087200[pos];
    q = D_80196AF8 + (sq * 0x36 + 0x117C);
    for (k = 0; k < 8; k++) {
        if ((mask >> k) & 1) {
            c = (q + (pos + D_801EF480_ovl_087200[k]))[4];
            if (c != 0xFF && c != m) {
                n++;
                break;
            }
        }
    }
    return n;
}
#else
INCLUDE_ASM("asm/nonmatchings/C2330", func_801D58D0_ovl_087200);
#endif

/* neighbour scan: register assignment differs */
#ifdef NON_MATCHING
/* neighbour scan: register assignment differs */
u8 func_801D597C_ovl_087200(u8 m) {
    u8 *st = D_80196AF8;
    s32 n = 0;
    s32 k;
    u8 *q;
    u8 pos;
    u8 mask;
    u8 c;

    pos = st[0x19B];
    if (pos >= 9) {
        return n;
    }
    q = st + (FIELD(st, u16, 0x18C) * 0x36 + 0x117C);
    mask = D_801EF474_ovl_087200[pos];
    for (k = 0; k < 8; k++) {
        if ((mask >> k) & 1) {
            c = (q + (pos + D_801EF480_ovl_087200[k]))[4];
            if (c != 0xFF && c != m) {
                n++;
                break;
            }
        }
    }
    return n;
}
#else
INCLUDE_ASM("asm/nonmatchings/C2330", func_801D597C_ovl_087200);
#endif

u8 func_801D5A2C_ovl_087200(u8 m) {
    u8 *st = D_80196AF8;
    s32 n = 0;
    s32 k;
    u8 *q;
    s32 pos;
    u8 mask;
    u8 c;

    q = st + (FIELD(st, u16, 0x18C) * 0x36 + 0x117C);
    pos = FIELD(st, u16, 0x19C);
    mask = D_801EF474_ovl_087200[pos];
    for (k = 0; k < 8; k++) {
        if ((mask >> k) & 1) {
            c = (q + (pos + D_801EF480_ovl_087200[k]))[4];
            if (c != 0xFF && c != m) {
                n++;
                break;
            }
        }
    }
    return n;
}

#ifdef NON_MATCHING
/* m2c draft, 53 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_8016DE1C(u8, u8);                          /* extern */
extern s32 D_80193BC0;

s32 func_801D5AD0_ovl_087200(s32 arg0, s32 arg1, s32 arg2) {
    s32 *var_v1;
    s32 temp_s2;
    s32 var_s0;
    s32 var_s1;
    u8 temp_a0;
    void *temp_s3;

    var_s1 = 0;
    var_s0 = 0;
    temp_s2 = arg2 & 0xFF;
    temp_s3 = D_80196AF8 + (((arg0 & 0xFFFF) * 0x36) + 0x117C);
loop_1:
    if (!(((s32) D_801EF474_ovl_087200[temp_s2] >> var_s0) & 1)) {
        var_s0 += 1;
        goto block_13;
    }
    temp_a0 = FIELD((temp_s3 + (temp_s2 + D_801EF480_ovl_087200[var_s0])), u8, 4);
    if (!((temp_a0 != 0xFF) & (temp_a0 != (arg1 & 0xFF)))) {
        var_s0 += 1;
        goto block_13;
    }
    var_v1 = &D_80193BC0;
    if (temp_a0 < 0x64U) {
        var_v1 = (temp_a0 * 0x38) + &D_80193BC0;
    }
    if ((func_8016DE1C(FIELD(var_v1, u8, 0x11), FIELD(var_v1, u8, 0x12)) & 0xFF) != 2) {
        var_s0 += 1;
block_13:
        if (var_s0 < 8) {
            goto loop_1;
        }
    } else {
        var_s1 = 1;
    }
    return var_s1 & 0xFF;
}
#else
INCLUDE_ASM("asm/nonmatchings/C2330", func_801D5AD0_ovl_087200);
#endif

INCLUDE_ASM("asm/nonmatchings/C2330", func_801D5BF0_ovl_087200);

s32 func_801D5D10_ovl_087200(u8 *out) {
    u8 r;
    u8 none;

    *out = 0;
    r = func_801D6508_ovl_087200();
    none = r == 0;
    if (!none) {
        *out = D_801EF487_ovl_087200[r];
    }
    return none;
}

INCLUDE_ASM("asm/nonmatchings/C2330", func_801D5D5C_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/C2330", func_801D6508_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/C2330", func_801D6D8C_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/C2330", func_801D6EA0_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/C2330", func_801D734C_ovl_087200);
