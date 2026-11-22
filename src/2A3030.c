#include "common.h"

/* 2A3030 */

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
typedef struct {
    /* 0x00 */ u16 a;
    /* 0x02 */ s16 b;
    /* 0x04 */ s16 c;
    /* 0x06 */ u16 d;
    /* 0x08 */ u16 e;
    /* 0x0A */ u16 f;
    /* 0x0C */ u16 sx; /* 6.10 fixed point */
    /* 0x0E */ u16 sy;
} Key2A3;

typedef struct {
    /* 0x00 */ s32 a;
    /* 0x04 */ s32 b;
    /* 0x08 */ s32 c;
    /* 0x0C */ s32 d;
    /* 0x10 */ s32 e;
    /* 0x14 */ s32 f;
    /* 0x18 */ f32 sx;
    /* 0x1C */ f32 sy;
    /* 0x20 */ u8 index;
} KeyOut2A3;

u8 *func_80232DE0_ovl_29A4C0(s32 a, s32 id);

/* Copies key k of animation anim of resource id (owner's) into out, like func_8019B054 in
 * ovl_1CE070; returns 0 when k is past the key count */
s32 func_80233800_ovl_29A4C0(s32 owner, s32 anim, u32 k, s32 id, KeyOut2A3 *out) {
    u8 *tab = func_80232DE0_ovl_29A4C0(owner, id);
    u16 *a;
    Key2A3 *key;

    if (tab != NULL) {
        a = (u16 *)(tab + ((s32 *)tab)[anim]);
    } else {
        a = NULL;
    }
    if (k < *a++) {
        a = (u16 *)((Key2A3 *)a + k);
        key = (Key2A3 *)a;
        out->a = key->a;
        out->b = key->b;
        out->c = key->c;
        out->d = key->d;
        out->e = key->e;
        out->f = key->f;
        out->sx = (key->sx >> 10) + (key->sx & 0x3FF) / 1024.0f;
        out->sy = (key->sy >> 10) + (key->sy & 0x3FF) / 1024.0f;
        return 1;
    }
    return 0;
}
