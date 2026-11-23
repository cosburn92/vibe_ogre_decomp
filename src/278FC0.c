#include "common.h"

/* 278FC0 */

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern s32 D_80220F68;
extern s32 D_80220F6C;
extern u8 D_800EB1F0[];
extern u8 D_80225828_ovl_275850[];
extern u8 D_8022582E_ovl_275850[];
void func_8020DFB8(void);
void func_8020DC80(u16 state);
void func_8020DD34(u16 state);
void func_8020E0B4(s32 a, s32 b);
void func_801F8E50(u8 id, u8 *s);
void func_800EA604(u8 *a, s32 b);
void func_8020DF00(void *fn);
struct Shot278;
s32 func_80224CD0_ovl_275850(u16 msg, struct Shot278 *o);
extern u8 D_80225810_ovl_275850[];
extern u8 D_80225816_ovl_275850[];
extern u8 D_8022581C_ovl_275850[];
extern u8 D_80225822_ovl_275850[];
void func_80207F30(u8 a, s32 b, s32 c);
/* --- end decls --- */

s32 func_80224830_ovl_275850(u16 msg, u8 *o) {
    switch (msg) {
        case 0x101:
            func_8020DFB8();
            break;
        case 0x100:
            FIELD(o, s32, 0) = D_80220F68;
            FIELD(o, s32, 4) = D_80220F6C;
            func_8020DC80(0x1002);
            break;
        case 0x1002:
            func_800EA604(D_800EB1F0, 0x2E0);
            func_801F8E50(*FIELD(o, u8 *, 4), D_80225810_ovl_275850);
            func_8020E0B4(9, 0x1003);
            break;
        case 0x1003:
            func_801F8E50(*FIELD(o, u8 *, 4), D_80225816_ovl_275850);
            func_8020E0B4(0x21, 0x1004);
            break;
        case 0x1004:
            func_801F8E50(*FIELD(o, u8 *, 4), D_8022581C_ovl_275850);
            func_8020E0B4(9, 0x1005);
            break;
        case 0x1005:
            func_801F8E50(*FIELD(o, u8 *, 4), D_80225822_ovl_275850);
            func_80207F30(*FIELD(o, u8 *, 4), 5, 0xF);
            func_8020E0B4(0x1E, 0x1006);
            break;
        case 0x1006:
            func_8020DD34(0x101);
            break;
    }
    return 0;
}

s32 func_802249C4_ovl_275850(u16 msg, u8 *o) {
    switch (msg) {
        case 0x101:
            func_8020DFB8();
            break;
        case 0x100:
            FIELD(o, s32, 0) = D_80220F68;
            FIELD(o, s32, 4) = D_80220F6C;
            func_8020DC80(0x1002);
            break;
        case 0x1002:
            func_800EA604(D_800EB1F0, 0x2DE);
            func_801F8E50(*FIELD(o, u8 *, 4), D_80225828_ovl_275850);
            func_8020E0B4(1, 0x1003);
            break;
        case 0x1003:
            func_801F8E50(*FIELD(o, u8 *, 4), D_8022582E_ovl_275850);
            func_8020E0B4(0x50, 0x1004);
            break;
        case 0x1004:
            func_800EA604(D_800EB1F0, 0x2DF);
            func_8020E0B4(0x56, 0x1005);
            break;
        case 0x1005:
            func_8020DD34(0x101);
            break;
    }
    return 0;
}

void func_8020A4A8(void *src, void *dst);
u8 *func_80217460(s32 id);
void func_8020D814(u8 *p);
extern u16 D_80225840_ovl_275850[][3];

s32 func_80224B00_ovl_275850(u16 msg, u8 *o) {
    u8 *p;
    s32 r = 0;

    switch (msg) {
        case 0x101:
            func_8020DFB8();
            break;
        case 0x100:
            FIELD(o, u16, 0x44) = *(u16 *)&D_80220F68;
            FIELD(o, f32, 0x40) = 0.25f;
            func_8020A4A8((u8 *)&D_80220F68 + 4, o);
            FIELD(o, u8 *, 0x48) = func_80217460(0xF3);
            func_8020DC80(0x1000);
            break;
        case 0x1000:
            FIELD(FIELD(o, u8 *, 0x48), u16, 0xA) |= 0x2000;
            p = FIELD(o, u8 *, 0x48);
            func_8020A4A8(o, p + 0x1C);
            FIELD(p, f32, 0x5C) = 1.0f;
            FIELD(p, u16, 0x60) = D_80225840_ovl_275850[FIELD(o, s16, 0x44)][0];
            FIELD(p, u16, 0x62) = D_80225840_ovl_275850[FIELD(o, s16, 0x44)][1];
            FIELD(p, u16, 0x64) = D_80225840_ovl_275850[FIELD(o, s16, 0x44)][2];
            func_8020DC80(0x1001);
            break;
        case 0x1001:
            if ((FIELD(FIELD(o, u8 *, 0x48), f32, 0x5C) -= FIELD(o, f32, 0x40)) <= 0.0f) {
                func_8020D814(FIELD(o, u8 *, 0x48));
                func_8020DC80(0x1002);
            }
            break;
        case 0x1002:
            func_8020DD34(0x101);
            break;
        default:
            r = 0;
            break;
    }
    return r;
}

typedef struct {
    f32 x, y, z;
} Vec3f278;
extern u8 D_80220F69;
s16 func_801F7128(u8 c);
void func_801F751C(s32 c, Vec3f278 *out, f32 ox, f32 oy, f32 oz);
void func_801F7344(u8 a, Vec3f278 *out, u8 b);
void func_801F7BE4(Vec3f278 *dir, Vec3f278 *to, Vec3f278 *from);
f32 func_8020A3C8(Vec3f278 *v);
void func_8020A418(Vec3f278 *v);
u8 *func_802173C4(s32 id);
void func_801F7C18(Vec3f278 *a, void *b);
void func_8020E0D0(void);
s16 func_8020AB9C(u8 a);

typedef struct Shot278 {
    /* 0x00 */ u8 from;
    /* 0x01 */ u8 to;
    /* 0x04 */ Vec3f278 pos;
    /* 0x10 */ Vec3f278 tgt;
    /* 0x1C */ Vec3f278 dir;
    /* 0x28 */ f32 dist;
    /* 0x2C */ s16 speed;
    /* 0x30 */ s32 pad30;
    /* 0x34 */ u8 *e;
} Shot278;

/* A projectile (effect 0xF3) flying from unit `from` to unit `to` at 45 units a frame, then
 * starting the fading hit effect at its last position */
s32 func_80224CD0_ovl_275850(u16 msg, Shot278 *o) {
    s32 r = 0;

    switch (msg) {
        case 0x101:
            func_8020DFB8();
            break;
        case 0x100: {
            Vec3f278 off;

            o->from = *(u8 *)&D_80220F68;
            o->to = D_80220F69;
            if (func_801F7128(o->from) != 0) {
                off.x = 0.0f;
                off.y = 16.0f;
                off.z = 0.0f;
            } else {
                off.x = 0.0f;
                off.y = 32.0f;
                off.z = 0.0f;
            }
            func_801F751C(o->from, &o->pos, off.x, off.y, off.z);
            func_801F7344(o->to, &o->tgt, 0x10);
            func_801F7BE4(&o->dir, &o->tgt, &o->pos);
            o->dist = func_8020A3C8(&o->dir);
            func_8020A418(&o->dir);
            o->speed = 45;
            func_8020DC80(0x1000);
            break;
        }
        case 0x1000: {
            u8 *e = func_802173C4(0xF3);

            o->e = e;
            FIELD(e, u16, 0xA) |= 0x2000;
            func_801F7C18(&o->dir, e + 0x1C);
            FIELD(e, f32, 0x4C) = o->pos.x + o->speed * o->dir.x;
            FIELD(e, f32, 0x50) = o->pos.y + o->speed * o->dir.y;
            FIELD(e, f32, 0x54) = o->pos.z + o->speed * o->dir.z;
            o->dist -= o->speed;
            func_8020E0D0();
            func_8020DC80(0x1001);
            break;
        }
        case 0x1001: {
            u8 *e = o->e;
            u8 *g;
            u8 *src;
            struct {
                u8 pad[0x30];
                Vec3f278 pos;
            } m;

            FIELD(e, f32, 0x4C) += o->speed * o->dir.x;
            FIELD(e, f32, 0x50) += o->speed * o->dir.y;
            FIELD(e, f32, 0x54) += o->speed * o->dir.z;
            o->dist -= o->speed;
            g = (u8 *)&D_80220F68;
            src = e + 0x1C;
            if (o->dist < o->speed) {
                func_8020DC80(0x1002);
            } else {
                func_8020DC80(0x1001);
            }
            func_8020A4A8(src, &m);
            m.pos.x -= o->speed * o->dir.x;
            m.pos.y -= o->speed * o->dir.y;
            m.pos.z -= o->speed * o->dir.z;
            func_8020A4A8(&m, g + 4);
            *(s16 *)g = func_8020AB9C(o->from);
            func_8020DF00(func_80224B00_ovl_275850);
            break;
        }
        case 0x1002:
            func_8020D814(o->e);
            func_8020DD34(0x101);
            break;
        default:
            r = 0;
            break;
    }
    return r;
}

s32 func_80225080_ovl_275850(u16 msg, u8 *o) {
    s32 r = 0;

    switch (msg) {
        case 0x101:
            func_8020DFB8();
            break;
        case 0x100:
            o[0] = *(u8 *)D_80220F68;
            o[1] = *(u8 *)D_80220F6C;
            func_8020DC80(0x1000);
            break;
        case 0x1000:
            /* the original stores into the bytes of the pointer variable itself */
            ((u8 *)&D_80220F68)[0] = o[0];
            ((u8 *)&D_80220F68)[1] = o[1];
            func_8020DF00(func_80224CD0_ovl_275850);
            func_8020E0B4(-1, 0x1001);
            break;
        case 0x1001:
            func_8020E0B4(0x14, 0x1002);
            break;
        case 0x1002:
            func_8020DD34(0x101);
            break;
        default:
            r = 0;
            break;
    }
    return r;
}
