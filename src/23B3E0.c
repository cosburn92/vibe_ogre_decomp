#include "common.h"

/* 23B3E0 */

typedef struct Task23 {
    /* 0x00 */ u16 next;
    /* 0x02 */ u8 unk02[2];
    /* 0x04 */ void (*fn)(s32, struct Task23 *);
    /* 0x08 */ s16 h8;
    /* 0x0A */ s16 hA;
    /* 0x0C */ s16 hC;
    /* 0x0E */ s16 hE;
    /* 0x10 */ u8 unk10[0x20];
} Task23; /* size 0x30 */

extern void *D_801F0530_ovl_23B220;
extern u16 D_801F0534_ovl_23B220;
extern Task23 *D_801F0560_ovl_23B220;

void *HFree(void *p);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/23B3E0", func_801E7170_ovl_23B220);

void func_801E7228_ovl_23B220(void) {
    HFree(D_801F0530_ovl_23B220);
}

INCLUDE_ASM("asm/nonmatchings/23B3E0", func_801E724C_ovl_23B220);

/* Takes a task from the free list and starts it with message 0x10 */
Task23 *func_801E7318_ovl_23B220(void (*fn)(s32, Task23 *)) {
    Task23 *t = NULL;

    if (D_801F0534_ovl_23B220 != 0xFFFF) {
        t = &D_801F0560_ovl_23B220[D_801F0534_ovl_23B220];
        D_801F0534_ovl_23B220 = t->next;
    }
    if (t != NULL) {
        t->fn = fn;
        t->hE = 0;
        fn(0x10, t);
    }
    return t;
}

void func_801E738C_ovl_23B220(Task23 *t) {
    t->fn = NULL;
    t->hE = 0;
    t->next = D_801F0534_ovl_23B220;
    D_801F0534_ovl_23B220 = t - D_801F0560_ovl_23B220;
}

void func_801E73E0_ovl_23B220(Task23 *t, s16 a) {
    t->hC = -1;
    t->hA = a;
    t->h8 = 0;
    t->hE = 1;
}

void func_801E73FC_ovl_23B220(Task23 *t) {
    t->hC = 0;
    t->hE = 0;
}
