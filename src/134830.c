#include "common.h"

/* 134830 */

extern s32 D_801ED4A4_ovl_101CE0[];
/* --- end decls --- */

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
typedef struct {
    /* 0x00 */ s32 id;
    /* 0x04 */ u8 unk04[8];
    /* 0x0C */ s32 x2;
    /* 0x10 */ s32 y2;
    /* 0x14 */ s32 w2;
    /* 0x18 */ s32 h2;
    /* 0x1C */ s32 x;
    /* 0x20 */ s32 y;
    /* 0x24 */ s32 w;
    /* 0x28 */ s32 h;
    /* 0x2C */ u8 *win;
    /* 0x30 */ u8 unk30[8];
    /* 0x38 */ s32 a;
    /* 0x3C */ s32 b;
    /* 0x40 */ s32 c;
    /* 0x44 */ u8 unk44[0x1D];
    /* 0x61 */ s8 d;
} Dialog134;
extern Dialog134 D_801ED540_ovl_101CE0;
extern s32 D_801F0B40_ovl_101CE0;
extern u16 *D_801F0CA0_ovl_101CE0;
extern u16 *D_800C4BDC;
void func_801E09DC_ovl_101CE0(Dialog134 *d);
void func_801E0594_ovl_101CE0();
u8 *func_8017BFB0(s32 kind, s32 b, void (*fn)(), s16 x, s16 y, s16 w, s16 h, s16 x2, s16 y2, s16 w2, s16 h2);
void func_8017C384(u8 *w);
void func_8020CDA0(s32 se);

/* Yes/no dialog step: opens dialog id on the first call; once the window is up, returns 1 for
 * the confirm button and 3 for the cancel button (closing it), 2 while waiting */
s32 func_801E00F0_ovl_101CE0(s32 id, s32 a, s32 b, s32 c, s32 d, s32 x2) {
    if (D_801ED540_ovl_101CE0.id == -1) {
        D_801ED540_ovl_101CE0.d = d;
        D_801ED540_ovl_101CE0.id = id;
        D_801ED540_ovl_101CE0.a = a;
        D_801ED540_ovl_101CE0.b = b;
        D_801ED540_ovl_101CE0.c = c;
        D_801F0B40_ovl_101CE0 = 0;
        D_801ED540_ovl_101CE0.x2 = x2;
        func_801E09DC_ovl_101CE0(&D_801ED540_ovl_101CE0);
        D_801ED540_ovl_101CE0.win = func_8017BFB0(4, 0, func_801E0594_ovl_101CE0, D_801ED540_ovl_101CE0.x,
                                                  D_801ED540_ovl_101CE0.y, D_801ED540_ovl_101CE0.w,
                                                  D_801ED540_ovl_101CE0.h, D_801ED540_ovl_101CE0.x2,
                                                  D_801ED540_ovl_101CE0.y2, D_801ED540_ovl_101CE0.w2,
                                                  D_801ED540_ovl_101CE0.h2);
        return 2;
    }
    if (FIELD(D_801ED540_ovl_101CE0.win, u16, 0x26) == 0) {
        if ((*D_800C4BDC & D_801F0CA0_ovl_101CE0[0]) || (*D_800C4BDC & D_801F0CA0_ovl_101CE0[1])) {
            func_8020CDA0(6);
            func_8017C384(D_801ED540_ovl_101CE0.win);
            D_801ED540_ovl_101CE0.id = -1;
            return (*D_800C4BDC & D_801F0CA0_ovl_101CE0[0]) ? 1 : 3;
        }
    }
    return 2;
}

INCLUDE_ASM("asm/nonmatchings/134830", func_801E027C_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/134830", func_801E0594_ovl_101CE0);

#ifdef NON_MATCHING
/* m2c draft, 49 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 _bcopy(s32, s32 *, s32);                /* extern */
s32 bzero(s32 *, s32);                  /* extern */
s32 func_80179034(s32 *, s32, s32);         /* extern */
s32 func_8017C4B4(s16, void *);                 /* extern */
s32 func_801818A0(s32, s32);                    /* extern */
extern void *D_800E9BA0;
extern s32 D_801ED584_ovl_101CE0;
extern s32 D_801ED588_ovl_101CE0;
extern s32 D_801ED598_ovl_101CE0;
extern s32 D_801ED59C_ovl_101CE0;
extern u8 D_801ED5A0_ovl_101CE0;
extern u8 D_801ED5A4_ovl_101CE0;

void func_801E0868_ovl_101CE0(void *arg0, s32 arg1) {
    s32 sp10;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s3_2;
    u8 temp_v0;
    u8 temp_v1;
    u8 temp_v1_2;
    void *temp_a1;

    temp_a1 = (arg1 * 2) + arg0;
    if (FIELD(temp_a1, s16, 0x18) != 0) {
        temp_s0 = FIELD(arg0, s32, 0x2C);
        temp_s2 = FIELD(arg0, s32, 0x30);
        FIELD(D_800E9BA0, s32, 0) = 0xE7000000;
        FIELD(D_800E9BA0, s32, 4) = 0;
        D_800E9BA0 += 8;
        temp_s3 = temp_s2 + 1;
        func_8017C4B4(FIELD(temp_a1, s16, 0x18), temp_a1);
        bzero(&sp10, 0x100);
        _bcopy(D_801ED584_ovl_101CE0, &sp10, D_801ED598_ovl_101CE0);
        temp_s1 = temp_s0 + 0x17;
        func_80179034(&sp10, temp_s1, temp_s3);
        bzero(&sp10, 0x100);
        temp_s3_2 = temp_s2 + 0x10;
        _bcopy(D_801ED588_ovl_101CE0, &sp10, D_801ED59C_ovl_101CE0);
        func_80179034(&sp10, temp_s1, temp_s3_2);
        func_801818A0((temp_s0 + (D_801ED5A4_ovl_101CE0 & 0xF)) - 1, temp_s3_2 + ((D_801ED5A0_ovl_101CE0 - 1) * 0xF) + 2);
        temp_v0 = D_801ED5A4_ovl_101CE0 + 1;
        if (D_801ED5A4_ovl_101CE0 & 0xF0) {
            D_801ED5A4_ovl_101CE0 = temp_v0;
            temp_v1 = temp_v0 & 0xF;
            if (temp_v1 >= 5U) {
                D_801ED5A4_ovl_101CE0 = temp_v1;
            }
        } else {
            temp_v1_2 = D_801ED5A4_ovl_101CE0 - 1;
            D_801ED5A4_ovl_101CE0 = temp_v1_2;
            if (!(temp_v1_2 & 0xF)) {
                D_801ED5A4_ovl_101CE0 = temp_v1_2 | 0xF0;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/134830", func_801E0868_ovl_101CE0);
#endif

INCLUDE_ASM("asm/nonmatchings/134830", func_801E09DC_ovl_101CE0);

INCLUDE_ASM("asm/nonmatchings/134830", func_801E0DBC_ovl_101CE0);

s32 func_801E0F30_ovl_101CE0(s32 a) {
    s32 *p = D_801ED4A4_ovl_101CE0;
    s32 i = 0;

    while (*p != a) {
        p += 3;
        i += 3;
    }
    return i;
}
