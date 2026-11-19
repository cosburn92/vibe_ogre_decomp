#include "common.h"

typedef struct {
    /* 0x00 */ u32 flags;
    /* 0x04 */ u8 unk04[4];
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 y;
    /* 0x10 */ f32 z;
    /* 0x14 */ u8 unk14[0x98];
    /* 0xAC */ f32 angle; /* in turns */
} FieldObj;

extern FieldObj *D_801F0CB0[]; /* 30 objects, then the focus object */
extern s32 D_801F0CA8;
extern s32 D_801F0E00;
extern f32 D_801F0D98;
extern f32 D_801F0D9C;
extern f32 D_801F0DA0;
extern f32 D_801F0DA4;
extern void *D_8018F58C;

f32 func_8009CFE0(f32 y, f32 x); /* atan2f */
void func_801B8D44(f32 x, f32 y, f32 z, void *cam, s32 b);
void func_801D25E4(FieldObj *o);
void func_801D2A14(s32 a, s32 b, s32 c);

/* Turns nearby objects to face the focus object */
void func_802165D0_ovl_1A2C20(void) {
    f32 r = ((D_801F0DA0 - D_801F0D98) + (D_801F0DA4 - D_801F0D9C)) / 2.0f;
    s32 i;
    FieldObj *o;
    FieldObj *focus;
    f32 dx;
    f32 dz;
    f32 a;

    r = r * 75.0f / 256.0f;
    for (i = 0; i < 30; i++) {
        o = D_801F0CB0[i];
        focus = D_801F0CB0[30];
        if ((o->flags & 0x1011) == 0x11) {
            dx = o->x - focus->x;
            dz = o->z - focus->z;
            if (dx * dx + dz * dz < r * r) {
                func_801D2A14(30, i, 0);
                a = func_8009CFE0(focus->z - o->z, o->x - focus->x) / 6.283185307179586;
                o->angle = a;
                if (a < 0.0f) {
                    o->angle = a + 1.0f;
                } else if (1.0f <= a) {
                    o->angle = a - 1.0f;
                }
            }
        } else if (o->flags & 0x1000) {
            func_801D25E4(o);
        }
    }
    if (--D_801F0CA8 == 0) {
        o = D_801F0CB0[D_801F0E00];
        func_801B8D44(o->x, o->y, o->z, D_8018F58C, 0x31);
    }
}

const f64 D_80216F68_ovl_1A2C20 = 0.0;
