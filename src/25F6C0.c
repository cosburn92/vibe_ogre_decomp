#include "common.h"

/* 25F6C0 */

typedef struct {
    /* 0x00 */ u8 unk00[0x5C];
    /* 0x5C */ s32 w5C;
    /* 0x60 */ s32 w60;
    /* 0x64 */ s32 w64;
} Ent25;

extern u8 D_8021F450_ovl_25EE90[];

Ent25 *func_801C8FE8(void);
void func_801C896C(Ent25 *e);
/* --- end decls --- */

/* Sorts n u16 values ascending */
void func_8020AB10_ovl_25EE90(u16 *a, s32 n) {
    s32 pad;
    s32 i;
    s32 j;
    u16 t;

    if (n < 2) {
        return;
    }
    for (i = 0; i < n - 1; i++) {
        for (j = i; j < n; j++) {
            if (a[i] > a[j]) {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

u8 func_8020AB8C_ovl_25EE90(s32 i) {
    return D_8021F450_ovl_25EE90[i];
}

void func_8020AB9C_ovl_25EE90(void) {
    func_801C896C(func_801C8FE8());
}

s32 func_8020ABC0_ovl_25EE90(Ent25 *e) {
    return e->w5C;
}

s32 func_8020ABC8_ovl_25EE90(void) {
    return func_801C8FE8()->w5C;
}

s32 func_8020ABE8_ovl_25EE90(Ent25 *e) {
    return e->w60;
}

s32 func_8020ABF0_ovl_25EE90(void) {
    return func_801C8FE8()->w60;
}

s32 func_8020AC10_ovl_25EE90(Ent25 *e) {
    return e->w64;
}

s32 func_8020AC18_ovl_25EE90(void) {
    return func_801C8FE8()->w64;
}
