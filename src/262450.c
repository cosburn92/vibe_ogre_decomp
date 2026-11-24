#include "common.h"
#include "heap.h"

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
Task *func_8020DD60_ovl_25EE90(void (*fn)(), Task *t);





extern s32 D_80220D90_ovl_25EE90;
extern Task **D_80220D94_ovl_25EE90;
void func_8020DCAC_ovl_25EE90(Task *t, u16 a);
/* --- end decls --- */

extern s32 D_80220D80_ovl_25EE90;
/* Allocates the task pool (24 tasks plus a 24-entry pointer list) and chains the free list */
void func_8020D8A0_ovl_25EE90(void) {
    s32 i;
    s32 j;

    D_80220D80_ovl_25EE90 = 24;
    D_80220E8E_ovl_25EE90 = 0;
    D_80220D8C_ovl_25EE90 = NULL;
    D_80220D88_ovl_25EE90 = NULL;
    D_80220FE8_ovl_25EE90 = NULL;
    D_80220D90_ovl_25EE90 = 24;
    D_80220D84_ovl_25EE90 = D_80220EDC_ovl_25EE90 = HMalloc(0xF04);
    D_80220D94_ovl_25EE90 = (Task **)&D_80220D84_ovl_25EE90[D_80220D80_ovl_25EE90];
    D_80220D94_ovl_25EE90[D_80220D90_ovl_25EE90] = NULL;
    for (i = 0; i < D_80220D80_ovl_25EE90; i++) {
        D_80220D84_ovl_25EE90[i].func = NULL;
    }
    for (j = 0; j < D_80220D80_ovl_25EE90 - 1; j++) {
        D_80220D84_ovl_25EE90[j].nextFree = j + 1;
    }
    D_80220D84_ovl_25EE90[j].nextFree = 0xFFFF;
}

void func_8020D9D8_ovl_25EE90(void) {
    HFree(D_80220EDC_ovl_25EE90);
}

/* Runs every task: states 0x100+ call the task function; state 1 waits unk1A frames (-1 = forever),
 * state 2 waits until the watched counter (unk1C + 0x10) reaches unk20; both then switch to unk18 */
void func_8020D9FC_ovl_25EE90(void) {
    Task *t;

    D_80220FE8_ovl_25EE90 = NULL;
    for (t = D_80220D88_ovl_25EE90; t != NULL; t = t->prev) {
        if (t->state >= 0x100) {
            func_8020DCAC_ovl_25EE90(t, t->state);
            continue;
        }
        switch (t->state) {
            case 1:
                if (t->unk1A == -1) {
                    break;
                }
                if (--t->unk1A > 0) {
                    break;
                }
                t->state = t->unk18;
                break;
            case 2:
                if (*(s32 *)(t->unk1C + 0x10) < t->unk20) {
                    break;
                }
                t->state = t->unk18;
                break;
        }
    }
    D_80220FE8_ovl_25EE90 = NULL;
}

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

/* Links task n after `after` (or at the end of the list when after is NULL) */
void func_8020DB80_ovl_25EE90(Task *after, Task *n) {
    /* +0x10 is the forward link, +0xC the backward one */
    if (after == NULL) {
        if (D_80220D8C_ovl_25EE90 != NULL) {
            if (D_80220D8C_ovl_25EE90->prev != NULL) {
                do {
                    D_80220D8C_ovl_25EE90 = D_80220D8C_ovl_25EE90->prev;
                } while (D_80220D8C_ovl_25EE90->prev != NULL);
            }
            D_80220D8C_ovl_25EE90->prev = n;
        }
        n->next = D_80220D8C_ovl_25EE90;
        D_80220D8C_ovl_25EE90 = n;
        if (D_80220D88_ovl_25EE90 == NULL) {
            D_80220D88_ovl_25EE90 = n;
        }
    } else {
        n->prev = after->prev;
        after->prev = n;
        if (n->prev != NULL) {
            n->prev->next = n;
        }
        n->next = after;
        n->parent = after;
        if (n->prev == NULL) {
            D_80220D8C_ovl_25EE90 = n;
        }
    }
}

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

/* Runs task t's function with t as the current task (task stack D_80220D94) */
#ifdef NON_MATCHING
/* register choice after the call differs (a0/a1 vs v1/a0) */
void func_8020DCAC_ovl_25EE90(Task *t, u16 a) {
    D_80220FE8_ovl_25EE90 = t;
    D_80220D94_ovl_25EE90[--D_80220D90_ovl_25EE90] = t;
    t->func(a, t->data);
    D_80220FE8_ovl_25EE90 = D_80220D94_ovl_25EE90[++D_80220D90_ovl_25EE90];
}
#else
INCLUDE_ASM("asm/nonmatchings/262450", func_8020DCAC_ovl_25EE90);
#endif

void func_8020DD34_ovl_25EE90(u16 a) {
    Task *t = D_80220FE8_ovl_25EE90;

    t->func(a, t->data);
}

/* Takes a task record off the free list (hangs when none is left) */
static inline Task *TaskAlloc262(void) {
    u16 i = D_80220E8E_ovl_25EE90;
    Task *n;

    if (i != 0xFFFF) {
        n = &D_80220D84_ovl_25EE90[i];
        D_80220E8E_ovl_25EE90 = n->nextFree;
        return n;
    }
    while (1) {
    }
}

/* Creates a task running fn, linked before t (or at the head of the list), and runs its init
 * call (0x100) as the current task; returns it */
Task *func_8020DD60_ovl_25EE90(void (*fn)(), Task *t) {
    Task *n = TaskAlloc262();

    if (n != NULL) {
        n->state = 0x100;
        n->func = NULL;
        n->parent = NULL;
        n->prev = NULL;
        n->next = NULL;
        if (t == NULL) {
            if (D_80220D8C_ovl_25EE90 != NULL) {
                if (D_80220D8C_ovl_25EE90->prev != NULL) {
                    Task *p;

                    do {
                        p = D_80220D8C_ovl_25EE90->prev;
                        D_80220D8C_ovl_25EE90 = p;
                    } while (p->prev != NULL);
                }
                D_80220D8C_ovl_25EE90->prev = n;
            }
            n->next = D_80220D8C_ovl_25EE90;
            D_80220D8C_ovl_25EE90 = n;
            if (D_80220D88_ovl_25EE90 == NULL) {
                D_80220D88_ovl_25EE90 = n;
            }
        } else {
            n->prev = t->prev;
            t->prev = n;
            if (n->prev != NULL) {
                n->prev->next = n;
            }
            n->next = t;
            n->parent = t;
            if (n->prev == NULL) {
                D_80220D8C_ovl_25EE90 = n;
            }
        }
        n->func = fn;
        D_80220D94_ovl_25EE90[--D_80220D90_ovl_25EE90] = n;
        D_80220FE8_ovl_25EE90 = n;
        n->func(0x100, n->data);
        D_80220FE8_ovl_25EE90 = D_80220D94_ovl_25EE90[++D_80220D90_ovl_25EE90];
    }
    return n;
}

void func_8020DF00_ovl_25EE90(s32 a) {
    func_8020DD60_ovl_25EE90(a, D_80220FE8_ovl_25EE90);
}

/* Unlinks task t and returns it to the free list */
inline void func_8020DF24_ovl_25EE90(Task *t) {
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
    t->func = NULL;
    t->parent = NULL;
    t->prev = NULL;
    t->next = NULL;
    t->state = 0;
    t->nextFree = D_80220E8E_ovl_25EE90;
    D_80220E8E_ovl_25EE90 = t - D_80220D84_ovl_25EE90;
}

void func_8020DFB8_ovl_25EE90(void) {
    func_8020DF24_ovl_25EE90(D_80220FE8_ovl_25EE90);
}

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
