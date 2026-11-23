#include "common.h"

/* 23B220 */

typedef struct {
    u8 unk00[0xD0];
    u8 bD0;
} Ent23B;

extern u8 *D_801D0810;
extern u8 D_801EFCB0_ovl_23B220[];

Ent23B *func_801C8FE8(s16 a);
/* --- end decls --- */

void func_801E6FB0_ovl_23B220(void) {
    D_801D0810 = D_801EFCB0_ovl_23B220;
}

s32 func_801E6FC4_ovl_23B220(void) {
    return 1;
}

void func_801E6FCC_ovl_23B220(void) {
}

void func_801E6FD4_ovl_23B220(void) {
}

void func_801E6FDC_ovl_23B220(s16 a) {
    func_801C8FE8(a)->bD0 = 1;
}

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_801E7410_ovl_23B220(s32 a);
s32 func_801DF2AC(u8 *p, s32 a, s32 b);
void func_801AD9D4(u8 *p, s16 a);
extern u8 (*D_801D0738)[3];
extern u8 D_801B3EE0[];

/* Starts entity k's action lasting t frames: when its anim is not ready (or k is 1) the parts get
 * the default draw routine, otherwise each part takes the colour of the entity's palette and
 * animation 0x11 */
void func_801E7004_ovl_23B220(s16 k, s32 t) {
    Ent23B *e = func_801C8FE8(k);
    u32 i;

    if (func_801E7410_ovl_23B220(FIELD(e, s32, 0x80)) != 0 || k == 1) {
        FIELD(e, s32, 0x88) = t;
        for (i = 0; i < 3; i++) {
            if (FIELD(e, u8 **, i * 4) != NULL) {
                *FIELD(e, void **, i * 4) = D_801B3EE0;
            }
        }
    } else {
        FIELD(e, s32, 0xA0) = 10;
        FIELD(e, s32, 0x88) = func_801DF2AC(FIELD(e, u8 *, 0) + 0x44, 0x11, 0) + t;
        for (i = 0; i < 3; i++) {
            if (FIELD(e, u8 *, i * 4) != NULL) {
                FIELD(FIELD(e, u8 *, i * 4), s16, 0x2E) = D_801D0738[e->unk00[0xA4]][0];
                FIELD(FIELD(e, u8 *, i * 4), s16, 0x30) = D_801D0738[e->unk00[0xA4]][1];
                FIELD(FIELD(e, u8 *, i * 4), s16, 0x32) = D_801D0738[e->unk00[0xA4]][2];
                func_801AD9D4(FIELD(e, u8 *, i * 4) + 0x44, 0x11);
            }
        }
    }
    e->unk00[0xA7] = FIELD(e, s32, 0x88) / 2;
}

u8 func_801E7164_ovl_23B220(u8 *p) {
    return p[0xA4];
}
