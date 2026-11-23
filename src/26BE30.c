#include "common.h"

/* 26BE30 */

extern s16 D_80221038_ovl_25EE90[];
extern s32 D_8022103C_ovl_25EE90;

void bzero(void *p, s32 n);
void func_8020D778_ovl_25EE90(void *fn);
s32 func_80217280_ovl_25EE90(u16 msg, u8 *o);
/* --- end decls --- */

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_802148C0_ovl_25EE90(u16 msg);
void func_80212AB8_ovl_25EE90();
void func_802129BC_ovl_25EE90();
void func_80212A04_ovl_25EE90();

/* Model task: on start picks each part's draw routine from the render flags (0x64 / 0x66) and sets
 * the colour to white; message 4 pushes the colour (0x60-0x64) to every part when flag 0x66 & 8 */
#ifdef NON_MATCHING
/* 81/81: the draw-routine choice branches on the other polarity (bnezl vs beqzl) and two loads are scheduled differently */
s32 func_80217280_ovl_25EE90(u16 msg, u8 *o) {
    s32 r = func_802148C0_ovl_25EE90(msg);

    switch (msg) {
        case 0: {
            u8 *mdl = FIELD(o, u8 *, 0x6C);
            u8 **sl = FIELD(o, u8 **, 0x74);
            u8 *m = o + 0x1C;
            u32 i;

            for (i = 0; i < FIELD(mdl, u32, 4); i++, sl++) {
                u8 *p = *sl;

                if (p != NULL) {
                    if ((FIELD(m, s32, 0x48) & 0xA) == 0xA) {
                        FIELD(p, void *, 0) = func_80212AB8_ovl_25EE90;
                    } else if (FIELD(m, u16, 0x4A) & 2) {
                        FIELD(p, void *, 0) = func_80212A04_ovl_25EE90;
                    } else {
                        FIELD(p, void *, 0) = func_802129BC_ovl_25EE90;
                    }
                }
            }
            FIELD(m, s16, 0x44) = FIELD(m, s16, 0x46) = FIELD(m, s16, 0x48) = 0xFF;
            break;
        }
        case 4: {
            u8 *mdl = FIELD(o, u8 *, 0x6C);
            u8 **sl = FIELD(o, u8 **, 0x74);
            u8 *m = o + 0x1C;
            u32 i;

            if (FIELD(o, u16, 0x66) & 8) {
                for (i = 0; i < FIELD(mdl, u32, 4); i++, sl++) {
                    u8 *p = *sl;

                    if (p != NULL) {
                        FIELD(p, u16, 0x30) = FIELD(m, u16, 0x44);
                        FIELD(p, u16, 0x32) = FIELD(m, u16, 0x46);
                        FIELD(p, u16, 0x34) = FIELD(m, u16, 0x48);
                    }
                }
            }
            break;
        }
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/26BE30", func_80217280_ovl_25EE90);
#endif

void func_802173C4_ovl_25EE90(s32 a) {
    bzero(D_80221038_ovl_25EE90, 0x18);
    D_8022103C_ovl_25EE90 = a;
    func_8020D778_ovl_25EE90(func_80217280_ovl_25EE90);
}

void func_80217408_ovl_25EE90(s32 a) {
    s16 *p = D_80221038_ovl_25EE90;

    bzero(p, 0x18);
    p[0] = 2;
    D_8022103C_ovl_25EE90 = a;
    func_8020D778_ovl_25EE90(func_80217280_ovl_25EE90);
}

void func_80217460_ovl_25EE90(s32 a) {
    s16 *p = D_80221038_ovl_25EE90;

    bzero(p, 0x18);
    p[0] = 10;
    D_8022103C_ovl_25EE90 = a;
    func_8020D778_ovl_25EE90(func_80217280_ovl_25EE90);
}
