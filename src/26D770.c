#include "common.h"
#include "heap.h"

/* 26D770 */

typedef struct {
    u8 unk00[0x3C];
    s32 w3C;
    s32 w40;
    s32 w44;
    s32 w48;
    s32 w4C;
    s32 w50;
} Task26D;

extern s32 D_80220F68_ovl_25EE90;

Task26D *func_8020DF00_ovl_25EE90(void *fn);
s32 func_80219140_ovl_25EE90(u16 msg, u8 *o);
s32 func_8021A57C_ovl_25EE90(u16 msg, u8 *o);
void func_80219A9C_ovl_25EE90(void);
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
u8 *func_80217460_ovl_25EE90(s32 id);
void func_8020DC80_ovl_25EE90(u16 state);
s32 func_8021B500_ovl_25EE90(u16 msg, u8 *o);
/* --- end decls --- */

u8 *func_8020E570_ovl_25EE90(void *fn, s32 a);
void func_802118D4_ovl_25EE90();
void func_80212200_ovl_25EE90();
void func_80212488_ovl_25EE90();
void func_80210410_ovl_25EE90(s32 id, u8 *out);
void func_8020A980_ovl_25EE90(void *a, void *b, u8 *out);
void func_8020A5A0_ovl_25EE90(u8 *m, void *pos);
void func_8020A4A8_ovl_25EE90(u8 *src, u8 *dst, s32 n);
void func_80098D00(void *mf, f32 x, f32 y, f32 z);
s32 func_8020AB8C_ovl_25EE90(s32 a);
u8 *func_80214EB4_ovl_25EE90(s32 id, s32 a, s32 b, s32 c, s32 d);
void bzero(void *p, s32 n);
extern u8 D_802206DC_ovl_25EE90[];
extern u8 D_802206D0_ovl_25EE90[];
extern u8 D_802206A0_ovl_25EE90[];

/* Sets up the parts of effect o: billboard sprite (frames from o+0x40), its shadow, a positioned
 * marker and the 0x22 particle animation */
void func_80218BC0_ovl_25EE90(u8 *o) {
    u8 *s;
    u8 *m;
    u8 *p;

    FIELD(o, u8 *, 0x14) = func_8020E570_ovl_25EE90(func_802118D4_ovl_25EE90, 1);
    FIELD(FIELD(o, u8 *, 0x14), f32, 8) = 1000.0f;
    s = FIELD(o, u8 *, 0x14);
    func_80210410_ovl_25EE90(FIELD(o, s32, 0x40), s + 0x64);
    FIELD(s, s16, 0x5A) = 0x20;
    FIELD(s, s16, 0x5C) = 2;
    FIELD(s, s16, 0x5E) = FIELD(s, u16, 0x68) >> 1;
    FIELD(s, s16, 0x60) = FIELD(s, u16, 0x6A) >> 1;
    m = s + 0x14;
    FIELD(s, s16, 0x56) = FIELD(o, s32, 0);
    FIELD(s, u16, 0x58) = FIELD(o, s32, 0x3C);
    FIELD(s, s16, 0x62) = 1;
    func_8020A980_ovl_25EE90(D_802206DC_ovl_25EE90, D_802206D0_ovl_25EE90, m);
    func_8020A5A0_ovl_25EE90(m, o + 8);
    FIELD(o, u8 *, 0x18) = p = func_8020E570_ovl_25EE90(func_80212200_ovl_25EE90, 1);
    {
        s32 n;

        FIELD(p, s16, 0x58) = 0;
        FIELD(p, s16, 0x5A) = 0;
        n = FIELD(s, u16, 0x58) - 2;
        FIELD(p, s16, 0x5E) = 0x20;
        p[0x56] = 0;
        p[0x55] = 0;
        p[0x54] = 0;
        p[0x57] = 0xFF;
        FIELD(p, s16, 0x5C) = n;
        func_8020A4A8_ovl_25EE90(m, p + 0x14, n);
    }
    FIELD(o, u8 *, 0x1C) = p = func_8020E570_ovl_25EE90(func_80212488_ovl_25EE90, 0);
    func_80098D00(p + 0x14, FIELD(o, f32, 8), FIELD(o, f32, 0xC), FIELD(o, f32, 0x10));
    FIELD(p, u8 *, 0x54) = D_802206A0_ovl_25EE90;
    {
        s32 n = func_8020AB8C_ovl_25EE90(FIELD(o, s32, 0x34));

        FIELD(o, u8 *, 0x20) = p = func_80214EB4_ovl_25EE90(0x22, 8, n, 8, n);
    }
    FIELD(p, u16, 0xA) |= 0x4000;
    bzero(FIELD(o, u8 *, 0x20) + 0x1C, 0x10);
    FIELD(o, f32, 0x28) = FIELD(o, f32, 0x2C) = FIELD(o, f32, 0x30) = 0.0f;
}

extern s32 D_80220F6C_ovl_25EE90;
extern void *D_80220F70_ovl_25EE90;
extern s32 D_80220F74_ovl_25EE90;
extern s32 D_80220F78_ovl_25EE90;
extern s32 D_80220F7C_ovl_25EE90;
extern void *D_801D0770;
void *func_801BCFE4(void);
void func_8020DFB8_ovl_25EE90(void);
void func_8020D814_ovl_25EE90(void *p);
void func_8020E51C_ovl_25EE90(void *p);
void func_80218104_ovl_25EE90(f32 x, f32 y, f32 z, s32 a);
void func_8020A4D0_ovl_25EE90(void *a, u8 *b, u8 *out);
extern u8 D_802206E8_ovl_25EE90[];
extern u8 D_802206F4_ovl_25EE90[];

/* Growing/shrinking aura at (x, y, z) (o+8): 0x1007 grows it over o->dur frames, 0x1008 shrinks it */
#ifdef NON_MATCHING
/* 238 vs 246: GCC cross-jumps the shared alpha/scale computation of the 0x1003 and 0x1004 cases (the original keeps them separate and joins at the draw call); the dispatch tree also differs */
s32 func_80218D68_ovl_25EE90(u16 msg, u8 *o) {
    s32 r = 0;
    s32 dur;
    s32 a;
    u8 *m;

    switch (msg) {
        case 0x101:
            if (FIELD(o, s32, 4) != 0) {
                func_8020D814_ovl_25EE90(FIELD(o, void *, 0x20));
                func_8020E51C_ovl_25EE90(FIELD(o, void *, 0x14));
                func_8020E51C_ovl_25EE90(FIELD(o, void *, 0x18));
                func_8020E51C_ovl_25EE90(FIELD(o, void *, 0x1C));
            }
            if (D_801D0770 != FIELD(o, void *, 0x40)) {
                HFree(FIELD(o, void *, 0x40));
            }
            func_8020DFB8_ovl_25EE90();
            break;
        case 0x100:
            bzero(o, 0x44);
            FIELD(o, f32, 8) = *(f32 *)&D_80220F68_ovl_25EE90;
            FIELD(o, f32, 0xC) = *(f32 *)&D_80220F6C_ovl_25EE90;
            FIELD(o, f32, 0x10) = *(f32 *)&D_80220F70_ovl_25EE90;
            FIELD(o, s32, 0x38) = D_80220F74_ovl_25EE90;
            FIELD(o, s32, 0x3C) = D_80220F78_ovl_25EE90;
            FIELD(o, s32, 0) = 0;
            FIELD(o, s32, 0x34) = D_80220F7C_ovl_25EE90;
            FIELD(o, void *, 0x40) = func_801BCFE4();
            func_8020DC80_ovl_25EE90(0x1000);
            break;
        case 0x1003:
            dur = FIELD(o, s32, 0x38);
            if (++FIELD(o, s32, 0) >= dur) {
                FIELD(o, s32, 0) = dur;
                func_8020DC80_ovl_25EE90(0x1001);
            }
            FIELD(o, f32, 0x24) = -(FIELD(o, s32, 0) * 160) / dur + 200;
            a = FIELD(o, s32, 0) * 255 / dur;
            FIELD(o, f32, 0x30) = FIELD(o, f32, 0x28) = (f32)(FIELD(o, s32, 0) + 1) / 64.0f;
            FIELD(o, f32, 0x2C) = FIELD(o, f32, 0x24) / 120.0f;
            goto draw;
        case 0x1004:
            dur = FIELD(o, s32, 0x38);
            if (--FIELD(o, s32, 0) <= 0) {
                FIELD(o, s32, 0) = 0;
                func_8020DC80_ovl_25EE90(0x1002);
            }
            a = FIELD(o, s32, 0) * 255 / dur;
            FIELD(o, f32, 0x30) = FIELD(o, f32, 0x28) = (f32)(FIELD(o, s32, 0) + 1) / 64.0f;
            FIELD(o, f32, 0x2C) = FIELD(o, f32, 0x24) / 120.0f;
        draw:
            func_80218104_ovl_25EE90(FIELD(o, f32, 8), FIELD(o, f32, 0xC), FIELD(o, f32, 0x10), a);
            m = FIELD(o, u8 *, 0x20) + 0x1C;
            func_8020A980_ovl_25EE90(D_802206E8_ovl_25EE90, D_802206F4_ovl_25EE90, m);
            func_8020A4D0_ovl_25EE90(o + 0x28, m, m);
            func_8020A5A0_ovl_25EE90(m, o + 8);
            FIELD(FIELD(o, u8 *, 0x18), s16, 0x5C) = FIELD(o, s32, 0) + 2;
            FIELD(FIELD(o, u8 *, 0x14), s16, 0x56) = FIELD(o, s32, 0);
            break;
        case 0x1005:
            if (FIELD(o, u16, -0x1C) == 0x1001) {
                r = 1;
            }
            break;
        case 0x1006:
            if (FIELD(o, u16, -0x1C) == 0x1002) {
                r = 1;
            }
            break;
        case 0x1007:
        case 0x1008:
            if (FIELD(o, s32, 4) == 0) {
                func_80218BC0_ovl_25EE90(o);
                FIELD(o, s32, 4) = 1;
            }
            func_8020DC80_ovl_25EE90(msg == 0x1007 ? 0x1003 : 0x1004);
            break;
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/26D770", func_80218D68_ovl_25EE90);
#endif

s16 func_801F7128(u8 c);
u8 *func_801C8FE8(s32 i);
void func_801F9DFC(void *a, u8 b, s32 c);
extern u8 D_800EB240[];
extern u8 D_800EB290[];
u8 *func_802173C4_ovl_25EE90(s32 id);
u8 *func_80214BE8_ovl_25EE90(s32 id);
u8 *func_802158AC_ovl_25EE90(s32 id);
void func_80217C84_ovl_25EE90(s32 id, f32 *out);
f32 func_8020A3C8_ovl_25EE90(f32 *v);
void func_8020A2E0_ovl_25EE90(f32 *v, f32 s, f32 *out);
void func_80217680_ovl_25EE90(u8 *o, u8 *m);
void func_8020D86C_ovl_25EE90(u8 *e, s32 a, s32 b);
void func_80217C14_ovl_25EE90(u8 *u, f32 *out);
void func_80217AD4_ovl_25EE90(u8 *u, u8 *m);
void func_80217848_ovl_25EE90(u8 *m);
void func_801C893C();
s32 func_80219970_ovl_25EE90(u16 msg, u8 *o);
void func_8020DC80_ovl_25EE90(u16 state);
void bzero(void *p, s32 n);

typedef struct {
    f32 start[3];
    f32 dir[3];
    f32 t;
    f32 len;
    f32 step;
} Path26D;

/* Thrown weapon: effect 0x37 turns toward unit 0x28, waits for its wind-up (frame 20), flies along
 * the path in steps of 6 leaving trails every 5 frames, then hits (0x35 / 0x36) */
#ifdef NON_MATCHING
/* 326 vs 325: dispatch and cases line up; GCC keeps one more value in a saved register (the hit position address in 0x1006), costing a register save */
s32 func_80219140_ovl_25EE90(u16 msg, u8 *o) {
    s32 r = 0;

    switch (msg) {
        case 0x101:
            func_8020DFB8_ovl_25EE90();
            break;
        case 0x100:
            bzero(o, 0x5C);
            FIELD(o, u8 *, 0x30) = func_802173C4_ovl_25EE90(0x37);
            FIELD(o, f32, 4) = FIELD(o, f32, 0) = FIELD(o, f32, 0x18) = FIELD(o, f32, 0x1C) = FIELD(o, f32, 0x20) = 0.0f;
            FIELD(o, f32, 0xC) = FIELD(o, f32, 0x10) = FIELD(o, f32, 0x14) = FIELD(o, f32, 8) = 1.0f;
            func_8020DC80_ovl_25EE90(0x1002);
            break;
        case 0x1002:
            func_8020DC80_ovl_25EE90(0x1003);
        case 0x1003: {
            Path26D *p = (Path26D *)(o + 0x38);
            f32 t[3];
            u8 *m;

            if (func_801F7128(o[0x27]) != 0) {
                FIELD(o, f32, 0x18) = 75.0f;
            } else {
                FIELD(o, f32, 0x18) = -75.0f;
            }
            FIELD(o, f32, 0x1C) = FIELD(o, f32, 0x20) = 0.0f;
            func_80217C84_ovl_25EE90(FIELD(o, s32, 0x28), t);
            FIELD(o, f32, 0) = t[0] - FIELD(o, f32, 0x18);
            FIELD(o, f32, 4) = t[1] - FIELD(o, f32, 0x1C);
            FIELD(o, f32, 8) = t[2] - FIELD(o, f32, 0x20);
            p->len = func_8020A3C8_ovl_25EE90((f32 *)o);
            func_8020A2E0_ovl_25EE90((f32 *)o, 1.0f / p->len, p->dir);
            p->t = 0.0f;
            p->step = 6.0f;
            p->len -= 30.0f;
            p->start[0] = FIELD(o, f32, 0x18);
            p->start[1] = FIELD(o, f32, 0x1C);
            p->start[2] = FIELD(o, f32, 0x20);
            m = FIELD(o, u8 *, 0x30) + 0x1C;
            func_80217680_ovl_25EE90(o, m);
            func_8020A4D0_ovl_25EE90(o + 0xC, m, m);
            func_8020A5A0_ovl_25EE90(m, o + 0x18);
            func_8020DC80_ovl_25EE90(0x1004);
            break;
        }
        case 0x1004: {
            u8 *m;

            if (FIELD(FIELD(o, u8 *, 0x30), s32, 0x10) >= 20) {
                s32 c;

                func_8020D86C_ovl_25EE90(FIELD(o, u8 *, 0x30), 0x15, 0x24);
                c = 0xDF;
                switch (FIELD(o, s32, 0x2C)) {
                    case 14:
                        c = 0xE1;
                        break;
                    case 15:
                        c = 0xE3;
                        break;
                }
                func_801F9DFC(D_800EB290, o[0x27], c);
                func_8020DC80_ovl_25EE90(0x1005);
            }
            m = FIELD(o, u8 *, 0x30) + 0x1C;
            func_80217680_ovl_25EE90(o, m);
            func_8020A4D0_ovl_25EE90(o + 0xC, m, m);
            func_8020A5A0_ovl_25EE90(m, o + 0x18);
            break;
        }
        case 0x1005: {
            Path26D *p = (Path26D *)(o + 0x38);
            u8 *m;
            s32 i;

            if (p->len < (p->t += p->step)) {
                p->t = p->len;
                func_8020DC80_ovl_25EE90(0x1006);
            }
            for (i = 0; i < 3; i++) {
                FIELD(o, f32, 0x18 + i * 4) = p->dir[i] * p->t + p->start[i];
            }
            m = FIELD(o, u8 *, 0x30) + 0x1C;
            func_80217680_ovl_25EE90(o, m);
            func_8020A4D0_ovl_25EE90(o + 0xC, m, m);
            func_8020A5A0_ovl_25EE90(m, o + 0x18);
            if (p->len / 2.0f <= p->t) {
                FIELD(o, u16, 0x36) = 1;
            }
            if (++FIELD(o, s16, 0x34) >= 5) {
                FIELD(o, s16, 0x34) = 0;
                D_80220F68_ovl_25EE90 = FIELD(FIELD(o, u8 *, 0x30), s32, 0x10);
                ((void (*)())func_8020A4A8_ovl_25EE90)(FIELD(o, u8 *, 0x30) + 0x1C, (u8 *)func_8020DF00_ovl_25EE90(func_80219970_ovl_25EE90) + 0x24);
            }
            break;
        }
        case 0x1006: {
            u8 *u;
            u8 *m;
            f32 v[3];
            s32 c;

            func_8020D814_ovl_25EE90(FIELD(o, u8 *, 0x30));
            u = func_801C8FE8(FIELD(o, s32, 0x28));
            func_80217C14_ovl_25EE90(u, v);
            {
                u8 *e = func_80214BE8_ovl_25EE90(0x35);

                m = e + 0x1C;
                FIELD(e, u16, 0xA) |= 0x8000;
            }
            func_80217AD4_ovl_25EE90(u, m);
            func_8020A5A0_ovl_25EE90(m, v);
            {
                u8 *e = func_802158AC_ovl_25EE90(0x36);

                m = e + 0x1C;
                FIELD(e, u16, 0xA) |= 0x8000;
            }
            func_80217848_ovl_25EE90(m);
            func_8020A5A0_ovl_25EE90(m, v);
            func_801C893C(FIELD(o, s16, 0x2A), 10);
            c = 0xE0;
            switch (FIELD(o, s32, 0x2C)) {
                case 14:
                    c = 0xE2;
                    break;
                case 15:
                    c = 0xE4;
                    break;
            }
            func_801F9DFC(D_800EB240, o[0x27], c);
            func_8020DC80_ovl_25EE90(0x1007);
            break;
        }
        case 0x1000:
            r = FIELD(o, u16, 0x36);
            break;
        case 0x1007:
            break;
        case 0x1001:
            if (FIELD(o, u16, -0x1C) == 0x1007) {
                r = 1;
            }
            break;
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/26D770", func_80219140_ovl_25EE90);
#endif

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern s32 D_80220F68_ovl_25EE90;
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
s32 func_80218D68_ovl_25EE90(u16 msg, u8 *o);
s32 func_8021A9C8_ovl_25EE90();
void func_80219A18_ovl_25EE90(s16 a, s32 b, s32 c);
void func_8020DC80_ovl_25EE90(u16 state);

s32 func_8021965C_ovl_25EE90(u16 msg, u8 *o) {
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
            g[3] = 0x1E;
            g[4] = 0x40;
            g[2] = 0;
            g[5] = 2;
            ((f32 *)g)[1] = -1.0f;
            t = (u8 *)func_8020DF00_ovl_25EE90(func_80218D68_ovl_25EE90);
            func_8020DCAC_ovl_25EE90(t, 0x1007);
            FIELD(o, u8 *, 0x18) = t;
            FIELD(o, void *, 0x20) = func_8021A998_ovl_25EE90(func_801C8B84(func_801C8FE8(*FIELD(o, u8 *, 4))), 20);
            FIELD(o, s32, 0x14) = 0;
            FIELD(o, s32, 0x10) = 0;
            FIELD(o, s32, 0xC) = 0;
            c = 0x2E;
            switch (FIELD(o, s16, 0)) {
                case 14:
                    c = 0x2F;
                    break;
                case 15:
                    c = 0x30;
                    break;
            }
            func_801F9DFC(D_800EB240, *FIELD(o, u8 *, 4), c);
            func_8020DC80_ovl_25EE90(0x1003);
            break;
        case 0x1003:
            FIELD(o, s32, 0xC)++;
            if (func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x18), 0x1005) != 0) {
                func_8020DC80_ovl_25EE90(0x1004);
            }
            break;
        case 0x1004:
            D_80220F6A_ovl_25EE90 = *FIELD(o, u8 *, 4);
            D_80220F6C_ovl_25EE90 = FIELD(o, s32, 8);
            D_80220F70_ovl_25EE90 = func_80219A18_ovl_25EE90;
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

/* Effect message handler: spawns effect 0x37 with colour (A, B, C, D) */
s32 func_80219970_ovl_25EE90(u16 msg, u8 *o) {
    s32 r = 0;

    if (msg == 0x100) {
        u8 *e;

        FIELD(o, s32, 0x44) = D_80220F68_ovl_25EE90;
        e = func_80217460_ovl_25EE90(0x37);
        FIELD(o, u8 *, 0x40) = e;
        FIELD(e, s32, 0x10) = FIELD(o, s32, 0x44);
        FIELD(FIELD(o, u8 *, 0x40), u16, 0xA) |= 0x2000;
        FIELD(o, s16, 0x4C) = 0x20;
        FIELD(o, s16, 0x4E) = 0xC8;
        FIELD(o, s16, 0x50) = 0xFF;
        FIELD(o, s16, 0x52) = 0x3C;
        func_8020DC80_ovl_25EE90(0x1000);
    } else {
        r = func_8021B500_ovl_25EE90(msg, o);
    }
    return r;
}

void func_80219A18_ovl_25EE90(s16 a, s32 b, s32 c) {
    Task26D *t = func_8020DF00_ovl_25EE90(func_80219140_ovl_25EE90);

    t->w48 = b;
    t->w4C = c;
    t->w50 = a;
}

void func_80219A70_ovl_25EE90(s32 a) {
    D_80220F68_ovl_25EE90 = a;
    func_8020DF00_ovl_25EE90(func_8021A57C_ovl_25EE90);
}

INCLUDE_ASM("asm/nonmatchings/26D770", func_80219A9C_ovl_25EE90);

void func_8021A210_ovl_25EE90(s16 a, s32 b, s32 c) {
    Task26D *t = func_8020DF00_ovl_25EE90(func_80219A9C_ovl_25EE90);

    t->w3C = b;
    t->w40 = c;
    t->w44 = a;
}

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern s32 D_80220F68_ovl_25EE90;
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
s32 func_80218D68_ovl_25EE90(u16 msg, u8 *o);
s32 func_8021A9C8_ovl_25EE90();
void func_8021A210_ovl_25EE90(s16 a, s32 b, s32 c);
void func_8020DC80_ovl_25EE90(u16 state);

s32 func_8021A268_ovl_25EE90(u16 msg, u8 *o) {
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
            g[3] = 0x32;
            g[4] = 0x50;
            g[2] = 0;
            g[5] = 3;
            ((f32 *)g)[1] = -1.0f;
            t = (u8 *)func_8020DF00_ovl_25EE90(func_80218D68_ovl_25EE90);
            func_8020DCAC_ovl_25EE90(t, 0x1007);
            FIELD(o, u8 *, 0x18) = t;
            FIELD(o, void *, 0x20) = func_8021A998_ovl_25EE90(func_801C8B84(func_801C8FE8(*FIELD(o, u8 *, 4))), 20);
            FIELD(o, s32, 0x14) = 0;
            FIELD(o, s32, 0x10) = 0;
            FIELD(o, s32, 0xC) = 0;
            c = 0x38;
            switch (FIELD(o, s16, 0)) {
                case 22:
                    c = 0x39;
                    break;
                case 23:
                    c = 0x3A;
                    break;
            }
            func_801F9DFC(D_800EB240, *FIELD(o, u8 *, 4), c);
            func_8020DC80_ovl_25EE90(0x1003);
            break;
        case 0x1003:
            FIELD(o, s32, 0xC)++;
            if (func_8020DCAC_ovl_25EE90(FIELD(o, void *, 0x18), 0x1005) != 0) {
                func_8020DC80_ovl_25EE90(0x1004);
            }
            break;
        case 0x1004:
            D_80220F6A_ovl_25EE90 = *FIELD(o, u8 *, 4);
            D_80220F6C_ovl_25EE90 = FIELD(o, s32, 8);
            D_80220F70_ovl_25EE90 = func_8021A210_ovl_25EE90;
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

/* Effect message handler: spawns effect 0x45 with colour (A, B, C, D) */
s32 func_8021A57C_ovl_25EE90(u16 msg, u8 *o) {
    s32 r = 0;

    if (msg == 0x100) {
        u8 *e;

        FIELD(o, s32, 0x44) = D_80220F68_ovl_25EE90;
        e = func_80217460_ovl_25EE90(0x45);
        FIELD(o, u8 *, 0x40) = e;
        FIELD(e, s32, 0x10) = FIELD(o, s32, 0x44);
        FIELD(FIELD(o, u8 *, 0x40), u16, 0xA) |= 0x2000;
        FIELD(o, s16, 0x4C) = 0x10;
        FIELD(o, s16, 0x4E) = 0xFF;
        FIELD(o, s16, 0x50) = 0xC8;
        FIELD(o, s16, 0x52) = 0x40;
        func_8020DC80_ovl_25EE90(0x1000);
    } else {
        r = func_8021B500_ovl_25EE90(msg, o);
    }
    return r;
}
