#include "common.h"

/* 263690 */

typedef struct {
    /* 0x0 */ s16 timer;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 handle;
    /* 0xC */ u16 next;
    /* 0xE */ u8 unkE[2];
} Slot263; /* size 0x10 */

extern Slot263 *D_80220E14_ovl_25EE90;
extern u16 D_80220E10_ovl_25EE90;

void *HMalloc(s32 size);
void *HFree(void *p);
void bzero(void *p, s32 n);
void func_8020C074_ovl_25EE90(s32 h);
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

/* Counts down every live timer slot; when one reaches zero its handle is released and the slot
 * goes back on the free list */
void func_8020EB7C_ovl_25EE90(void) {
    Slot263 *p;

    for (p = D_80220E14_ovl_25EE90; p < (Slot263 *)((u8 *)D_80220E14_ovl_25EE90 + 0x400); p++) {
        if (p->timer != 0) {
            if (--p->timer == 0) {
                func_8020C074_ovl_25EE90(p->handle);
                p->unk2 = 0;
                p->unk4 = 0;
                p->next = D_80220E10_ovl_25EE90;
                p->handle = 0;
                D_80220E10_ovl_25EE90 = p - D_80220E14_ovl_25EE90;
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/263690", func_8020EC2C_ovl_25EE90);
