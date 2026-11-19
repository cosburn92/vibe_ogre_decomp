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

INCLUDE_ASM("asm/nonmatchings/C2330", func_801D5AD0_ovl_087200);

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
