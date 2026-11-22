#include "common.h"

/* 2A7D60 */

INCLUDE_ASM("asm/nonmatchings/2A7D60", func_80238530_ovl_29A4C0);

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern u8 D_8020F390[];
extern s32 D_80239170_ovl_29A4C0[4];

/* Message handler for four 16x32 sprites: 0 resets them, 2 moves each two pixels left and down */
void func_8023870C_ovl_29A4C0(u16 msg, u8 *ctx) {
    u32 i;

    switch (msg) {
        case 0:
            for (i = 0; i < 4; i++) {
                FIELD(FIELD(ctx, u8 **, 0x58)[D_80239170_ovl_29A4C0[i]], void *, 0) = D_8020F390;
                {
                    u8 *p = FIELD(ctx, u8 **, 0x58)[D_80239170_ovl_29A4C0[i]];

                    FIELD(p, u16, 0x30) = 0;
                    FIELD(p, u16, 0x32) = 0;
                    FIELD(p, s16, 0x34) = FIELD(p, u16, 0x30) + 15;
                    FIELD(p, s16, 0x36) = FIELD(p, u16, 0x32) + 31;
                }
            }
            break;
        case 1:
            break;
        case 2:
            for (i = 0; i < 4; i++) {
                u8 *p = FIELD(ctx, u8 **, 0x58)[D_80239170_ovl_29A4C0[i]];

                FIELD(p, u16, 0x30) -= 2;
                FIELD(p, u16, 0x32) += 2;
                FIELD(p, s16, 0x34) = FIELD(p, u16, 0x30) + 15;
                FIELD(p, s16, 0x36) = FIELD(p, u16, 0x32) + 31;
            }
            break;
    }
}
