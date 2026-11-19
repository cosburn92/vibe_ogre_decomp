#include "common.h"

/* 261E90 */

typedef struct {
    /* 0x00 */ u16 next;
    /* 0x02 */ u8 unk02[2];
    /* 0x04 */ s32 w4;
    /* 0x08 */ u8 unk08[0x8C];
} Node26; /* size 0x94 */

typedef struct Task26 {
    /* 0x00 */ u8 unk00[4];
    /* 0x04 */ s32 (*fn)(s32, struct Task26 *);
    /* 0x08 */ u16 h8;
    /* 0x0A */ u16 hA;
    /* 0x0C */ s32 wC;
    /* 0x10 */ s32 w10;
    /* 0x14 */ s32 w14;
    /* 0x18 */ s32 w18;
} Task26;

extern void *D_80220D60_ovl_25EE90;
extern u16 D_80220D64_ovl_25EE90;
extern Node26 *D_80220D6C_ovl_25EE90;

void *HFree(void *p);
extern s32 D_80220D68_ovl_25EE90;
extern Node26 *D_80220D70_ovl_25EE90;
void *HMalloc(s32 size);
/* --- end decls --- */

/* Node pool: 32 entries of 0x94 bytes chained through `next` */
void func_8020D2E0_ovl_25EE90(void) {
    Node26 *p;
    s32 i;

    D_80220D68_ovl_25EE90 = 0x20;
    D_80220D6C_ovl_25EE90 = D_80220D60_ovl_25EE90 = HMalloc(0x1300);
    D_80220D70_ovl_25EE90 = D_80220D6C_ovl_25EE90 + D_80220D68_ovl_25EE90;
    for (i = 0; i < D_80220D68_ovl_25EE90; i++) {
        D_80220D6C_ovl_25EE90[i].w4 = 0;
    }
    p = D_80220D6C_ovl_25EE90;
    D_80220D64_ovl_25EE90 = 0;
    for (i = 0; i < D_80220D68_ovl_25EE90 - 1; i++) {
        p->next = i + 1;
        p++;
    }
    p->next = 0xFFFF;
}

void func_8020D3B0_ovl_25EE90(void) {
    HFree(D_80220D60_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/261E90", func_8020D3D4_ovl_25EE90);

/* Takes a node from the free list (hangs when empty) */
inline Node26 *func_8020D6B4_ovl_25EE90(void) {
    Node26 *n;

    if (D_80220D64_ovl_25EE90 != 0xFFFF) {
        n = &D_80220D6C_ovl_25EE90[D_80220D64_ovl_25EE90];
        D_80220D64_ovl_25EE90 = n->next;
    } else {
        for (;;) {
        }
    }
    return n;
}

void func_8020D704_ovl_25EE90(Node26 *n) {
    n->w4 = 0;
    n->next = D_80220D64_ovl_25EE90;
    D_80220D64_ovl_25EE90 = n - D_80220D6C_ovl_25EE90;
}

inline void func_8020D758_ovl_25EE90(Task26 *t) {
    t->h8 = 7;
    t->fn = NULL;
    t->hA = 0;
    t->wC = 0x708;
    t->w10 = 0;
}

/* Starts a task running fn (called once with message 0) */
Task26 *func_8020D778_ovl_25EE90(s32 (*fn)(s32, Task26 *)) {
    Task26 *t = (Task26 *)func_8020D6B4_ovl_25EE90();

    if (t != NULL) {
        func_8020D758_ovl_25EE90(t);
        t->fn = fn;
        fn(0, t);
    }
    return t;
}

void func_8020D814_ovl_25EE90(Task26 *t) {
    t->hA &= 0x3FFF;
    t->h8 |= 0x8000;
}

s32 func_8020D830_ovl_25EE90(Task26 *t) {
    s32 r = t->fn(6, t);

    return !(t->w10 < r);
}

void func_8020D86C_ovl_25EE90(Task26 *t, s32 a, s32 b) {
    t->w14 = a;
    t->w18 = b;
    t->hA |= 0x200;
}

void func_8020D884_ovl_25EE90(Task26 *t) {
    t->hA &= ~0x200;
}
