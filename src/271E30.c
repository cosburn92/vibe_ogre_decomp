#include "common.h"

/* 271E30 */

typedef struct {
    u8 unk00[0x30];
    s32 w30;
    s32 w34;
    s32 w38;
    s32 w3C;
} Task271;

extern s32 D_80220F68_ovl_25EE90;

Task271 *func_8020DF00_ovl_25EE90(void *fn);
s32 func_8021DACC_ovl_25EE90(u16 msg, u8 *o);
s32 func_8021D2AC_ovl_25EE90(u16 msg, u8 *o);
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
u8 *func_80217460_ovl_25EE90(s32 id);
void func_8020DC80_ovl_25EE90(u16 state);
s32 func_8021B500_ovl_25EE90(u16 msg, u8 *o);
/* --- end decls --- */

void func_8021D280_ovl_25EE90(s32 a) {
    D_80220F68_ovl_25EE90 = a;
    func_8020DF00_ovl_25EE90(func_8021DACC_ovl_25EE90);
}

extern u8 D_80220EE0_b_ovl_25EE90[];
void func_8020DFB8_ovl_25EE90(void);
void bzero(void *p, s32 n);
u8 *func_802173C4_ovl_25EE90(s32 id);
u8 *func_80214BE8_ovl_25EE90(s32 id);
s16 func_801F7128(u8 c);
void func_8020A4A8_ovl_25EE90(void *a, void *b);
void func_8020A5A0_ovl_25EE90(u8 *m, void *pos);
void func_801F9DFC(void *a, u8 b, s32 c);
extern u8 D_800EB240[];
extern u8 D_800EB290[];
extern u8 D_80220EE0_ovl_25EE90[];
void func_80217C84_ovl_25EE90(s32 id, f32 *out);
f32 func_8020A3C8_ovl_25EE90(f32 *v);
void func_8020A2E0_ovl_25EE90(f32 *v, f32 s, f32 *out);
void func_8020E0B4_ovl_25EE90(s32 a, s32 b);
void func_8020D814_ovl_25EE90(void *t);
void func_801C893C();

/* Spell bolt: effect 0x6E flies from the caster's side (x +-95, y -10) to unit 0x10 in 28 steps
 * with a ground shadow (0x70), leaving trail effects every 4 frames, then bursts (0x6C/0x6D/0x6F)
 * and damages the target */
extern u8 D_80220EE0_b_ovl_25EE90[];
void func_8020DFB8_ovl_25EE90(void);
void bzero(void *p, s32 n);
u8 *func_802173C4_ovl_25EE90(s32 id);
u8 *func_80214BE8_ovl_25EE90(s32 id);
s16 func_801F7128(u8 c);
void func_8020A4A8_ovl_25EE90(void *a, void *b);
void func_8020A5A0_ovl_25EE90(u8 *m, void *pos);
void func_801F9DFC(void *a, u8 b, s32 c);
extern u8 D_800EB240[];
extern u8 D_800EB290[];
extern u8 D_80220EE0_ovl_25EE90[];
void func_80217C84_ovl_25EE90(s32 id, f32 *out);
f32 func_8020A3C8_ovl_25EE90(f32 *v);
void func_8020A2E0_ovl_25EE90(f32 *v, f32 s, f32 *out);
void func_8020E0B4_ovl_25EE90(s32 a, s32 b);
void func_8020D814_ovl_25EE90(void *t);
void func_801C893C();

/* Spell bolt: effect 0x6E flies from the caster's side (x +-95, y -10) to unit 0x10 in 28 steps
 * with a ground shadow (0x70), leaving trail effects every 4 frames, then bursts (0x6C/0x6D/0x6F)
 * and damages the target */
s32 func_8021D2AC_ovl_25EE90(u16 msg, u8 *o) {
    s32 r = 0;

    switch (msg) {
        case 0x101:
            func_8020DFB8_ovl_25EE90();
            break;
        case 0x100:
            bzero(o, 0x4C);
            FIELD(o, u8 *, 0x1C) = func_802173C4_ovl_25EE90(0x6E);
            FIELD(o, f32, 0) = FIELD(o, f32, 4) = FIELD(o, f32, 8) = 0.0f;
            func_8020DC80_ovl_25EE90(0x1002);
            break;
        case 0x1002: {
            u8 *m;
            s32 c;

            if (func_801F7128(o[0xF]) != 0) {
                FIELD(o, f32, 0) = 95.0f;
            } else {
                FIELD(o, f32, 0) = -95.0f;
            }
            FIELD(o, s32, 8) = 0;
            FIELD(o, f32, 4) = -10.0f;
            m = FIELD(o, u8 *, 0x1C) + 0x1C;
            func_8020A4A8_ovl_25EE90(D_80220EE0_ovl_25EE90, m);
            func_8020A5A0_ovl_25EE90(m, o);
            c = 0xF1;
            switch (FIELD(o, s32, 0x18)) {
                case 0x2D:
                    c = 0xF3;
                    break;
                case 0x2E:
                    c = 0xF5;
                    break;
            }
            func_801F9DFC(D_800EB290, o[0xF], c);
            func_8020DC80_ovl_25EE90(0x1003);
            break;
        }
        case 0x1003: {
            f32 t[3];
            f32 *d;

            func_80217C84_ovl_25EE90(FIELD(o, s32, 0x10), t);
            FIELD(o, f32, 0x34) = t[0] - FIELD(o, f32, 0);
            FIELD(o, f32, 0x38) = t[1] - FIELD(o, f32, 4);
            FIELD(o, f32, 0x3C) = t[2] - FIELD(o, f32, 8);
            d = (f32 *)(o + 0x34);
            FIELD(o, f32, 0x44) = func_8020A3C8_ovl_25EE90(d);
            func_8020A2E0_ovl_25EE90(d, 1.0f / FIELD(o, f32, 0x44), d);
            FIELD(o, s32, 0x40) = 0;
            FIELD(o, f32, 0x28) = FIELD(o, f32, 0);
            FIELD(o, f32, 0x2C) = FIELD(o, f32, 4);
            FIELD(o, f32, 0x30) = FIELD(o, f32, 8);
            FIELD(o, f32, 0x48) = FIELD(o, f32, 0x44) / 28.0f;
            func_8020E0B4_ovl_25EE90(2, 0x1004);
            break;
        }
        case 0x1004: {
            u8 *e = func_80214BE8_ovl_25EE90(0x70);

            FIELD(o, u8 *, 0x20) = e;
            FIELD(e, s32, 0xC) -= 500;
            func_8020DC80_ovl_25EE90(0x1005);
        }
        case 0x1005: {
            f32 *s = (f32 *)(o + 0x28);
            u8 *m;
            f32 v[3];
            s32 i;

            if (FIELD(o, f32, 0x44) <= (FIELD(o, f32, 0x40) += FIELD(o, f32, 0x48))) {
                FIELD(o, f32, 0x40) = FIELD(o, f32, 0x44);
                func_8020DC80_ovl_25EE90(0x1006);
            }
            for (i = 0; i < 3; i++) {
                ((f32 *)o)[i] = s[i + 3] * s[6] + s[i];
            }
            m = FIELD(o, u8 *, 0x1C);
            m += 0x1C;
            func_8020A4A8_ovl_25EE90(D_80220EE0_ovl_25EE90, m);
            func_8020A5A0_ovl_25EE90(m, o);
            m = FIELD(o, u8 *, 0x20);
            m += 0x1C;
            func_8020A4A8_ovl_25EE90(D_80220EE0_b_ovl_25EE90, m);
            v[0] = FIELD(o, f32, 0);
            *(s32 *)&v[1] = 0;
            v[2] = FIELD(o, f32, 8);
            func_8020A5A0_ovl_25EE90(m, v);
            if (s[7] * 0.5f <= s[6]) {
                FIELD(o, u16, 0x26) = 1;
            }
            if (++FIELD(o, s16, 0x24) >= 4) {
                D_80220F68_ovl_25EE90 = FIELD(FIELD(o, u8 *, 0x1C), s32, 0x10);
                func_8020A4A8_ovl_25EE90(FIELD(o, u8 *, 0x1C) + 0x1C, (u8 *)func_8020DF00_ovl_25EE90(func_8021DACC_ovl_25EE90) + 0x24);
                FIELD(o, s16, 0x24) = 0;
            }
            break;
        }
        case 0x1006: {
            u8 *e = func_80214BE8_ovl_25EE90(0x6C);
            u8 *m;
            s32 c;

            FIELD(e, s32, 0xC) = -10000;
            FIELD(e, u16, 0xA) |= 0x9000;
            m = e + 0x1C;
            func_8020A4A8_ovl_25EE90(D_80220EE0_ovl_25EE90, m);
            func_8020A5A0_ovl_25EE90(m, o);
            e = func_80214BE8_ovl_25EE90(0x6D);
            FIELD(e, u16, 0xA) |= 0x8000;
            func_8020A4A8_ovl_25EE90(m, e + 0x1C);
            e = func_80214BE8_ovl_25EE90(0x6F);
            FIELD(e, u16, 0xA) |= 0x8000;
            func_8020A4A8_ovl_25EE90(m, e + 0x1C);
            func_801C893C(FIELD(o, s16, 0x12), 10);
            c = 0xF2;
            switch (FIELD(o, s32, 0x18)) {
                case 0x2D:
                    c = 0xF4;
                    break;
                case 0x2E:
                    c = 0xF6;
                    break;
            }
            func_801F9DFC(D_800EB240, o[0xF], c);
            func_8020E0B4_ovl_25EE90(10, 0x1007);
            break;
        }
        case 0x1007:
            func_8020D814_ovl_25EE90(FIELD(o, void *, 0x1C));
            func_8020D814_ovl_25EE90(FIELD(o, void *, 0x20));
            func_8020DC80_ovl_25EE90(0x1008);
            break;
        case 0x1008:
            break;
        case 0x1000:
            r = FIELD(o, u16, 0x26);
            break;
        case 0x1001:
            if (FIELD(o, u16, -0x1C) == 0x1008) {
                r = 1;
            }
            break;
    }
    return r;
}

extern s32 D_80220F6C_ovl_25EE90;
void func_8020DFB8_ovl_25EE90(void);
s32 func_8020DCAC_ovl_25EE90(void *t, u16 a);
void *func_8021A998_ovl_25EE90(s32 a, s32 b);
s16 func_801F7128(u8 c);
void func_80207CE4(u8 *p);
void func_8020E0B4_ovl_25EE90(s32 a, s32 b);
s32 func_801C8B84(u8 *u);
u8 *func_801C8FE8(s32 i);
void func_801F9DFC(void *a, u8 b, s32 c);
extern u8 D_800EB240[];
extern u8 D_80220F6A_ovl_25EE90;
extern void *D_80220F70_ovl_25EE90;
s32 func_80218D68_ovl_25EE90();
s32 func_8021A9C8_ovl_25EE90();
void func_8021DB6C_ovl_25EE90(s16 a, s32 b, s32 c, s32 d);

s32 func_8021D7C4_ovl_25EE90(u16 msg, u8 *o) {
    u8 *t;
    s32 c;
    s32 *g;

    switch (msg) {
        case 0x101:
            func_8020DFB8_ovl_25EE90();
            break;
        case 0x100:
            FIELD(o, s32, 4) = D_80220F68_ovl_25EE90;
            FIELD(o, s32, 8) = D_80220F6C_ovl_25EE90;
            func_8020DC80_ovl_25EE90(0x1000);
            break;
        case 0x1000:
            func_80207CE4(FIELD(o, u8 *, 4));
            func_8020E0B4_ovl_25EE90(-1, 0x1001);
            break;
        case 0x1001:
        case 0x1002:
            g = &D_80220F68_ovl_25EE90;
            if (func_801F7128(*FIELD(o, u8 *, 4)) != 0) {
                ((f32 *)g)[0] = 95.0f;
            } else {
                ((f32 *)g)[0] = -95.0f;
            }
            g[3] = 30;
            g[4] = 0x40;
            g[2] = 0;
            g[5] = 6;
            ((f32 *)g)[1] = -1.0f;
            t = (u8 *)func_8020DF00_ovl_25EE90(func_80218D68_ovl_25EE90);
            func_8020DCAC_ovl_25EE90(t, 0x1007);
            FIELD(o, u8 *, 0x18) = t;
            FIELD(o, void *, 0x20) = func_8021A998_ovl_25EE90(func_801C8B84(func_801C8FE8(*FIELD(o, u8 *, 4))), 20);
            FIELD(o, s32, 0x14) = 0;
            FIELD(o, s32, 0x10) = 0;
            FIELD(o, s32, 0xC) = 0;
            c = 0x50;
            switch (FIELD(o, s16, 0)) {
                case 0x2D:
                    c = 0x51;
                    break;
                case 0x2E:
                    c = 0x52;
                    break;
            }
            func_801F9DFC(D_800EB240, *FIELD(o, u8 *, 4), c);
            func_8020DC80_ovl_25EE90(0x1003);
            break;
        case 0x1003:
            if (func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x18), 0x1005) != 0) {
                func_8020DC80_ovl_25EE90(0x1004);
            }
            break;
        case 0x1004:
            D_80220F6A_ovl_25EE90 = *FIELD(o, u8 *, 4);
            D_80220F6C_ovl_25EE90 = FIELD(o, s32, 8);
            D_80220F70_ovl_25EE90 = func_8021DB6C_ovl_25EE90;
            FIELD(o, void *, 0x1C) = (void *)func_8020DF00_ovl_25EE90(func_8021A9C8_ovl_25EE90);
            func_8020DC80_ovl_25EE90(0x1005);
            break;
        case 0x1005:
            if (func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x1C), 0x1003) != 0) {
                func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x1C), 0x101);
                func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x18), 0x1008);
                func_8020DC80_ovl_25EE90(0x1006);
            }
            break;
        case 0x1006:
            FIELD(o, s32, 0x10)++;
            if (FIELD(o, s32, 0x14) == 0 && FIELD(o, s32, 0x10) >= FIELD(o, s32, 0xC) - 20) {
                func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x20), 0x1003);
                FIELD(o, s32, 0x14) = 1;
            }
            if (func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x18), 0x1006) != 0) {
                func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x18), 0x101);
                func_8020DC80_ovl_25EE90(0x1007);
            }
            break;
        case 0x1007:
            func_8020DC80_ovl_25EE90(0x101);
            break;
    }
    return 0;
}

/* Effect message handler: spawns effect 0x6E with colour (A, B, C, D) */
s32 func_8021DACC_ovl_25EE90(u16 msg, u8 *o) {
    s32 r = 0;

    if (msg == 0x100) {
        u8 *e;

        FIELD(o, s32, 0x44) = D_80220F68_ovl_25EE90;
        e = func_80217460_ovl_25EE90(0x6E);
        FIELD(o, u8 *, 0x40) = e;
        FIELD(e, s32, 0x10) = FIELD(o, s32, 0x44);
        FIELD(FIELD(o, u8 *, 0x40), u16, 0xA) |= 0x2000;
        FIELD(o, s16, 0x4C) = 0;
        FIELD(o, s16, 0x4E) = 0xFF;
        FIELD(o, s16, 0x50) = 0x40;
        FIELD(o, s16, 0x52) = 0x40;
        func_8020DC80_ovl_25EE90(0x1000);
    } else {
        r = func_8021B500_ovl_25EE90(msg, o);
    }
    return r;
}

void func_8021DB6C_ovl_25EE90(s16 a, s32 b, s32 c, s32 d) {
    Task271 *t = func_8020DF00_ovl_25EE90(func_8021D2AC_ovl_25EE90);

    t->w30 = b;
    t->w34 = c;
    t->w38 = d;
    t->w3C = a;
}
