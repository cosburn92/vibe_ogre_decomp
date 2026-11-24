#include "common.h"
#include "heap.h"
#include "rescache.h"

/* 263690 */

typedef struct {
    /* 0x0 */ s16 timer;
    /* 0x2 */ u16 id;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ void *data; /* resource cache data */
    /* 0xC */ u16 next;
    /* 0xE */ u8 unkE[2];
} Slot263; /* size 0x10 */

extern Slot263 *D_80220E14_ovl_25EE90;
extern u16 D_80220E10_ovl_25EE90;

void bzero(void *p, s32 n);
void *func_8020CA58_ovl_25EE90(u16 kind, s32 id);
/* --- end decls --- */

void func_8020EAE0_ovl_25EE90(void) {
    Slot263 *p = HMalloc(0x400);
    s32 i;

    D_80220E14_ovl_25EE90 = p;
    bzero(p, 0x400);
    for (i = 0; i < 63; i++) {
        D_80220E14_ovl_25EE90[i].next = i + 1;
    }
    D_80220E10_ovl_25EE90 = 0;
    D_80220E14_ovl_25EE90[i].next = 0xFFFF;
}

void func_8020EB58_ovl_25EE90(void) {
    HFree(D_80220E14_ovl_25EE90);
}

/* Counts down every live timer slot; when one reaches zero its resource is released and the slot
 * goes back on the free list */
void func_8020EB7C_ovl_25EE90(void) {
    Slot263 *p;

    for (p = D_80220E14_ovl_25EE90; p < (Slot263 *)((u8 *)D_80220E14_ovl_25EE90 + 0x400); p++) {
        if (p->timer != 0) {
            if (--p->timer == 0) {
                func_8020C074_ovl_25EE90(p->data);
                p->id = 0;
                p->unk4 = 0;
                p->next = D_80220E10_ovl_25EE90;
                p->data = NULL;
                D_80220E10_ovl_25EE90 = p - D_80220E14_ovl_25EE90;
            }
        }
    }
}

/* Handle for (id, key), cached for 5 countdown ticks; a miss takes a free slot and creates it */
#ifdef NON_MATCHING
/* Only register allocation differs: the original copies id from a0 to a2 at entry and keeps the loop end in a0; the free-slot pointer goes through v1 before s0. */
void *func_8020EC2C_ovl_25EE90(u16 id, s32 key) {
    Slot263 *p;

    for (p = D_80220E14_ovl_25EE90; p < (Slot263 *)((u8 *)D_80220E14_ovl_25EE90 + 0x400); p++) {
        if (p->timer != 0 && p->id == id && p->unk4 == key) {
            p->timer = 5;
            return p->data;
        }
    }
    p = Slot263Take();
    p->timer = 5;
    p->id = id;
    p->unk4 = key;
    D_80220E10_ovl_25EE90 = p->next;
    if ((p->data = func_8020CA58_ovl_25EE90(id, key)) == NULL) {
        for (;;);
    }
    return p->data;
}
#else
INCLUDE_ASM("asm/nonmatchings/263690", func_8020EC2C_ovl_25EE90);
#endif
