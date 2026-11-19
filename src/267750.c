#include "common.h"

/* 267750 */

typedef struct {
    /* 0x0 */ u8 unk0[4];
    /* 0x4 */ s32 x;
    /* 0x8 */ s32 y;
    /* 0xC */ s32 z;
} Pos26;

typedef struct {
    /* 0x0 */ u8 unk0[8];
    /* 0x8 */ f32 f8;
    /* 0xC */ s32 wC;
} Obj26;

typedef struct {
    /* 0x00 */ u8 unk00[0x30];
    /* 0x30 */ f32 x;
    /* 0x34 */ f32 y;
    /* 0x38 */ f32 z;
    /* 0x3C */ u8 unk3C[4];
    /* 0x40 */ f32 f40;
} Src26; /* size 0x44 */

typedef struct {
    u8 unk0[4];
    s32 n;
} Cnt26;

typedef struct {
    /* 0x0 */ u8 unk0[4];
    /* 0x4 */ Cnt26 *cnt;
    /* 0x8 */ u8 unk8[4];
    /* 0xC */ void **list;
} Set26;

void func_801ADADC(void *p);
void func_8020D280_ovl_25EE90(void *p);
void func_8020E51C_ovl_25EE90(void *p);
/* --- end decls --- */

void func_80212BA0_ovl_25EE90(s32 n, Obj26 **arr) {
    s32 pad;
    s32 i;

    for (i = 0; i < n; i++) {
        if (arr[i] != NULL) {
            arr[i]->wC = 1;
        }
    }
}

void func_80212BD8_ovl_25EE90(s32 n, Obj26 **arr, s32 d) {
    s32 pad;
    s32 i;

    for (i = 0; i < n; i++) {
        if (arr[i] != NULL) {
            arr[i]->f8 += d;
        }
    }
}

void func_80212C20_ovl_25EE90(s32 n, Pos26 **arr, s32 d) {
    s32 pad;
    s32 i;
    Pos26 *p;

    for (i = 0; i < n; i++) {
        p = arr[i];
        if (p != NULL) {
            p->x += d;
            p->y += d;
            p->z += d;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/267750", func_80212C78_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/267750", func_80212CF4_ovl_25EE90);

/* Looks up key in a sorted (key, value) table ending with (-1, 0); falls back to the entry below */
#ifdef NON_MATCHING
/* Loop layout differs: the target re-tests from the top with an index register and no rotation. */
s16 func_80212D78_ovl_25EE90(s32 key, s16 (*t)[2]) {
    s32 i = 0;

loop:
    if (t[i][0] == -1 && t[i][1] == 0) {
        goto below;
    }
    if (key == t[i][0]) {
        goto found;
    }
    if (key < t[i][0]) {
        goto below;
    }
    i++;
    goto loop;
below:
    i--;
    if (i < 0) {
        i = 0;
    }
found:
    return t[i][1];
}
#else
INCLUDE_ASM("asm/nonmatchings/267750", func_80212D78_ovl_25EE90);
#endif

INCLUDE_ASM("asm/nonmatchings/267750", func_80212DE0_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/267750", func_802131E8_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/267750", func_802132D0_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/267750", func_80213420_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/267750", func_802136F4_ovl_25EE90);

void func_802137A8_ovl_25EE90(s32 n, void **arr) {
    s32 pad;
    s32 i;

    for (i = 0; i < n; i++) {
        if (arr[i] != NULL) {
            func_801ADADC(arr[i]);
        }
    }
}

void func_80213804_ovl_25EE90(s32 n, Src26 *src, Obj26 **arr) {
    s32 pad;
    s32 i;

    for (i = 0; i < n; i++) {
        if (arr[i] != NULL) {
            arr[i]->f8 = src[i].z * 30.0f;
        }
    }
}

void func_80213850_ovl_25EE90(s32 n, Src26 *src, Pos26 **arr) {
    s32 pad;
    s32 i;

    for (i = 0; i < n; i++) {
        if (arr[i] != NULL) {
            arr[i]->x = src[i].x * 30.0f;
            arr[i]->y = src[i].y * 30.0f;
            arr[i]->z = src[i].z * 30.0f;
        }
    }
}

void func_802138C8_ovl_25EE90(s32 n, Src26 *src, f32 v) {
    s32 pad;
    s32 i;

    for (i = 0; i < n; i++, src++) {
        src->f40 = v;
    }
}

INCLUDE_ASM("asm/nonmatchings/267750", func_802138FC_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/267750", func_80213980_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/267750", func_80213AC8_ovl_25EE90);

void func_80213BE8_ovl_25EE90(Set26 *s) {
    s32 pad;
    s32 n = s->cnt->n;
    void **list = s->list;
    s32 i;

    for (i = 0; i < n; i++) {
        if (list[i] != NULL) {
            func_8020D280_ovl_25EE90(list[i]);
            list[i] = NULL;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/267750", func_80213C50_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/267750", func_80213CE0_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/267750", func_80213F28_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/267750", func_80213FC8_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/267750", func_8021404C_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/267750", func_8021419C_ovl_25EE90);

void func_802142BC_ovl_25EE90(Set26 *s) {
    s32 pad;
    s32 n = s->cnt->n;
    void **list = s->list;
    s32 i;

    for (i = 0; i < n; i++) {
        if (list[i] != NULL) {
            func_8020E51C_ovl_25EE90(list[i]);
            list[i] = NULL;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/267750", func_80214324_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/267750", func_802143B4_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/267750", func_802144EC_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/267750", func_8021463C_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/267750", func_80214774_ovl_25EE90);

INCLUDE_ASM("asm/nonmatchings/267750", func_80214814_ovl_25EE90);
