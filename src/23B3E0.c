#include "common.h"

/* 23B3E0 */

typedef struct Task23 {
    /* 0x00 */ u16 next;
    /* 0x02 */ u8 unk02[2];
    /* 0x04 */ void (*fn)(s32, struct Task23 *);
    /* 0x08 */ u16 state;
    /* 0x0A */ u16 nextState;
    /* 0x0C */ s16 hC;
    /* 0x0E */ s16 hE;
    /* 0x10 */ u8 unk10[0x20];
} Task23; /* size 0x30 */

extern void *D_801F0530_ovl_23B220;
extern u16 D_801F0534_ovl_23B220;
extern Task23 *D_801F0560_ovl_23B220;
extern s32 D_801F0538_ovl_23B220;

void *HFree(void *p);
void *HMalloc(s32 size);
void bzero(void *p, s32 n);
/* --- end decls --- */

/* Task pool: 3 entries chained through `next`, all idle */
void func_801E7170_ovl_23B220(void) {
    Task23 *p;
    s32 i;

    D_801F0538_ovl_23B220 = 3;
    D_801F0534_ovl_23B220 = 0;
    D_801F0530_ovl_23B220 = HMalloc(0x90);
    bzero(D_801F0530_ovl_23B220, 0x90);
    D_801F0560_ovl_23B220 = D_801F0530_ovl_23B220;
    for (i = 0; i < D_801F0538_ovl_23B220; i++) {
        D_801F0560_ovl_23B220[i].fn = NULL;
    }
    p = D_801F0560_ovl_23B220;
    for (i = 1; i < D_801F0538_ovl_23B220; i++) {
        p->next = i;
        p++;
    }
    p->next = 0xFFFF;
}

void func_801E7228_ovl_23B220(void) {
    HFree(D_801F0530_ovl_23B220);
}

/* Runs every active task: states 0x10+ call fn(state, task); state 0 counts hC down (-1 = forever)
 * and then switches to nextState */
void func_801E724C_ovl_23B220(void) {
    Task23 *t = D_801F0560_ovl_23B220;
    s32 i;

    for (i = 0; i < D_801F0538_ovl_23B220; t++, i++) {
        if (t->fn == NULL) {
            continue;
        }
        if (t->state >= 0x10) {
            t->fn(t->state, t);
            continue;
        }
        if (t->state != 0) {
            continue;
        }
        if (t->hC == -1) {
            continue;
        }
        if (--t->hC > 0) {
            continue;
        }
        t->state = t->nextState;
    }
}

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
    t->nextState = a;
    t->state = 0;
    t->hE = 1;
}

void func_801E73FC_ovl_23B220(Task23 *t) {
    t->hC = 0;
    t->hE = 0;
}
