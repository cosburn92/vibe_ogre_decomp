#include "common.h"

/* Task records (0x9C bytes) in a pool with a free list (D_80220E8E = first free index). */
typedef struct Task {
    /* 0x00 */ u16 nextFree;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ void (*func)();
    /* 0x08 */ u16 state;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ struct Task *next;
    /* 0x10 */ struct Task *prev;
    /* 0x14 */ struct Task *parent;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8 data[0x78];
} Task;

extern void *D_80220EDC_ovl_25EE90;
extern u16 D_80220E8E_ovl_25EE90;
extern Task *D_80220D84_ovl_25EE90;
extern Task *D_80220D88_ovl_25EE90;
extern Task *D_80220D8C_ovl_25EE90;
extern Task *D_80220FE8_ovl_25EE90; /* current task */
void HFree(void *p);
void func_8020DD60_ovl_25EE90(s32 a, Task *t);





INCLUDE_ASM("asm/nonmatchings/262450", func_8020D8A0_ovl_25EE90);

void func_8020D9D8_ovl_25EE90(void) {
    HFree(D_80220EDC_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/262450", func_8020D9FC_ovl_25EE90);

/* Takes a task from the free list; hangs when the pool is empty. */
Task *func_8020DAE4_ovl_25EE90(void) {
    s32 i = D_80220E8E_ovl_25EE90;
    Task *t;

    if (i != 0xFFFF) {
        t = &D_80220D84_ovl_25EE90[i];
        D_80220E8E_ovl_25EE90 = t->nextFree;
    } else {
        for (;;) {
        }
    }
    return t;
}

/* Returns a task to the free list. */
void func_8020DB34_ovl_25EE90(Task *t) {
    t->func = NULL;
    t->parent = NULL;
    t->prev = NULL;
    t->next = NULL;
    t->state = 0;
    t->nextFree = D_80220E8E_ovl_25EE90;
    D_80220E8E_ovl_25EE90 = t - D_80220D84_ovl_25EE90;
}

INCLUDE_ASM("asm/nonmatchings/262450", func_8020DB80_ovl_25EE90);

/* Unlinks a task from the run list. */
void func_8020DC30_ovl_25EE90(Task *t) {
    Task *prev = t->prev;
    Task *next = t->next;

    if (prev != NULL) {
        prev->next = next;
    }
    if (next != NULL) {
        next->prev = prev;
    }
    if (D_80220D88_ovl_25EE90 == t) {
        D_80220D88_ovl_25EE90 = prev;
    }
    if (D_80220D8C_ovl_25EE90 == t) {
        D_80220D8C_ovl_25EE90 = next;
    }
}

void func_8020DC80_ovl_25EE90(u16 state) {
    D_80220FE8_ovl_25EE90->state = state;
}

void func_8020DC90_ovl_25EE90(Task *t) {
    t->state = 0x100;
    t->func = NULL;
    t->parent = NULL;
    t->prev = NULL;
    t->next = NULL;
}

INCLUDE_ASM("asm/nonmatchings/262450", func_8020DCAC_ovl_25EE90);

void func_8020DD34_ovl_25EE90(u16 a) {
    Task *t = D_80220FE8_ovl_25EE90;

    t->func(a, t->data);
}

INCLUDE_ASM("asm/nonmatchings/262450", func_8020DD60_ovl_25EE90);

void func_8020DF00_ovl_25EE90(s32 a) {
    func_8020DD60_ovl_25EE90(a, D_80220FE8_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/262450", func_8020DF24_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/262450", func_8020DFB8_ovl_25EE90);

#ifdef NON_MATCHING
/* Two instructions short: the original leaves its branch delay slots unfilled. */
/* The child of t (a following task whose parent is t) running func, or NULL. */
Task *func_8020E054_ovl_25EE90(Task *t, void (*func)()) {
    Task *c;

    for (c = t->prev; c != NULL; c = c->prev) {
        if (c->parent != t) {
            break;
        }
        if (c->func == func) {
            return c;
        }
    }
    return NULL;
}
#else
INCLUDE_ASM("asm/nonmatchings/262450", func_8020E054_ovl_25EE90);
#endif

s16 func_8020E094_ovl_25EE90(void) {
    return D_80220FE8_ovl_25EE90->unk1A;
}

void func_8020E0A4_ovl_25EE90(s16 v) {
    D_80220FE8_ovl_25EE90->unk1A = v;
}

void func_8020E0B4_ovl_25EE90(s16 a, s16 b) {
    Task *t = D_80220FE8_ovl_25EE90;

    t->unk1A = a;
    t->unk18 = b;
    t->state = 1;
}

void func_8020E0D0_ovl_25EE90(void) {
    D_80220FE8_ovl_25EE90->parent->unk1A = 0;
}

void func_8020E0E4_ovl_25EE90(s32 a, s32 b, s16 c) {
    Task *t = D_80220FE8_ovl_25EE90;

    t->unk18 = c;
    t->unk1C = a;
    t->unk20 = b;
    t->state = 2;
}
