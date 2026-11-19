#include "common.h"

/* ovl_087200 (B8DE0): ten animation slots */

typedef struct {
    /* 0x000 */ s32 f00;
    /* 0x004 */ s32 f04;
    /* 0x008 */ s32 f08;
    /* 0x00C */ s32 cur[4];
    /* 0x01C */ s32 v1C;
    /* 0x020 */ s32 v20;
    /* 0x024 */ s32 v24;
    /* 0x028 */ s32 v28;
    /* 0x02C */ s32 start[4];
    /* 0x03C */ u8 unk03C[0xAA];
    /* 0x0E6 */ u8 flags;
    /* 0x0E7 */ u8 unk0E7;
    /* 0x0E8 */ u16 mode;
    /* 0x0EA */ u16 type;
    /* 0x0EC */ u16 unk0EC;
    /* 0x0EE */ u16 id;
    /* 0x0F0 */ s32 unk0F0;
    /* 0x0F4 */ void *data;
    /* 0x0F8 */ u8 unk0F8[0x10];
} AnimSlot; /* size 0x108 */

typedef struct {
    /* 0x0000 */ u8 unk0000[0x650];
    /* 0x0650 */ AnimSlot slots[10];
    /* 0x10A0 */ u16 count;
} AnimState;

extern AnimState *D_80196AF8;

void *HFree(void *p);
void _bcopy(void *src, void *dst, s32 n);
void func_801CC84C_ovl_087200(s16 i);

void func_801CC380_ovl_087200(void) {
    s32 i;

    for (i = 0; i < 10; i++) {
        D_80196AF8->slots[i].flags = 0;
    }
    D_80196AF8->count = 0;
}

/* Slot index of the active animation with this id, or -1 */
inline s16 func_801CC3B8_ovl_087200(u16 id) {
    AnimSlot *s;
    s32 i;

    for (i = 0; i < 10; i++) {
        s = &D_80196AF8->slots[i];
        if ((s->flags & 1) && s->id == id) {
            return i;
        }
    }
    return -1;
}

AnimSlot *func_801CC410_ovl_087200(u16 id) {
    AnimSlot *s;
    s32 i;

    for (i = 0; i < 10; i++) {
        s = &D_80196AF8->slots[i];
        if ((s->flags & 1) && s->id == id) {
            return s;
        }
    }
    return NULL;
}

/* Last used slot */
AnimSlot *func_801CC464_ovl_087200(void) {
    AnimSlot *found = NULL;
    AnimSlot *s;
    s32 i;

    for (i = 9; i >= 0; i--) {
        s = &D_80196AF8->slots[i];
        if (s->flags != 0) {
            found = s;
            break;
        }
    }
    return found;
}

void func_801CC4A0_ovl_087200(AnimSlot *s) {
    if (s->id == 0x100 || s->id == 5) {
        HFree(s->data);
    }
    s->flags = 0;
    s->f08 = 0;
    s->f00 = 0;
    D_80196AF8->count--;
}

static inline s16 FindFreeSlot(void) {
    AnimState *st = D_80196AF8;
    AnimSlot *s;
    s32 i;

    for (i = 0; i < 10; i++) {
        s = &st->slots[i];
        if (s->flags == 0) {
            return i;
        }
    }
    return -1;
}

void func_801CC50C_ovl_087200(AnimSlot *src) {
    s16 i = FindFreeSlot();

    if (i >= 0) {
        _bcopy(src, &D_80196AF8->slots[i], sizeof(AnimSlot));
        D_80196AF8->slots[i].id = 1;
        func_801CC84C_ovl_087200(i);
    }
}

void func_801CC5B4_ovl_087200(AnimSlot *s, s16 a, s16 b, s16 c, s16 d) {
    s->start[0] = a;
    s->start[1] = b;
    s->start[2] = c;
    s->start[3] = d;
}

void func_801CC5EC_ovl_087200(AnimSlot *s, s16 a, s16 b, s16 c, s16 d, s16 e, s16 f, s16 g, s16 h) {
    s->start[0] = a;
    s->cur[0] = a;
    s->start[1] = b;
    s->cur[1] = b;
    s->start[2] = c;
    s->cur[2] = c;
    s->type = 1;
    s->mode = 0x8000;
    s->start[3] = d;
    s->cur[3] = d;
    s->v1C = e;
    s->v20 = f;
    s->v24 = g;
    s->v28 = h;
}

void func_801CC684_ovl_087200(AnimSlot *s, s32 a, s16 b, s16 c, s16 d, s16 e) {
    s->f08 = a;
    s->v1C = b;
    s->v20 = c;
    s->type = 3;
    s->mode = 0x8000;
    s->v24 = d;
    s->v28 = e;
}

void func_801CC6D4_ovl_087200(AnimSlot *s, s32 a, s32 b, s16 c, s16 d, s16 e, s16 f) {
    s->f04 = a;
    s->f08 = b;
    s->v1C = c;
    s->type = 4;
    s->mode = 0x8000;
    s->v20 = d;
    s->v24 = e;
    s->v28 = f;
}

void func_801CC72C_ovl_087200(AnimSlot *s, s32 a, s32 b, s16 c, s16 d, s16 e, s16 f) {
    s->f00 = a;
    s->f08 = b;
    s->v1C = c;
    s->type = 5;
    s->mode = 0x8000;
    s->v20 = d;
    s->v24 = e;
    s->v28 = f;
}

void func_801CC784_ovl_087200(AnimSlot *s, s16 a, s16 b, s16 c, s16 d) {
    s->v1C = a;
    s->v20 = b;
    s->v24 = c;
    s->type = 6;
    s->mode = 0x8002;
    s->f08 = s->f00;
    s->v28 = d;
}

void func_801CC7D4_ovl_087200(u16 id) {
    s16 i = func_801CC3B8_ovl_087200(id);

    if (i >= 0) {
        func_801CC84C_ovl_087200(i);
    }
}

INCLUDE_ASM("asm/nonmatchings/B8DE0", func_801CC84C_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B8DE0", func_801CC974_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B8DE0", func_801CCA50_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B8DE0", func_801CCD08_ovl_087200);

INCLUDE_ASM("asm/nonmatchings/B8DE0", func_801CCDCC_ovl_087200);
