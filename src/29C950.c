#include "common.h"

/* 29C950 */

typedef struct {
    /* 0x000 */ u8 unk000[0xE8];
    /* 0x0E8 */ s32 wE8;
    /* 0x0EC */ s32 wEC;
    /* 0x0F0 */ s32 wF0;
    /* 0x0F4 */ s32 wF4;
    /* 0x0F8 */ u8 unk0F8[0x30];
    /* 0x128 */ s32 w128;
    /* 0x12C */ u8 unk12C[8];
    /* 0x134 */ s16 h134;
    /* 0x136 */ u8 unk136[4];
    /* 0x13A */ s16 h13A;
    /* 0x13C */ u8 unk13C;
    /* 0x13D */ u8 b13D;
    /* 0x13E */ u8 unk13E[7];
    /* 0x145 */ u8 b145;
    /* 0x146 */ u8 b146;
} BUnit;

typedef struct {
    /* 0x0 */ u8 unk0[0xC];
    /* 0xC */ s16 hC;
    /* 0xE */ u8 bE;
} BObj;

typedef struct {
    /* 0x00 */ u8 unk00[0x18];
    /* 0x18 */ BUnit *units[0x38];
    /* 0xF8 */ BObj *objs[1];
} Battle;

extern Battle *D_8022A974;
extern s16 D_800E9C0A[];
extern u8 D_8019EE40[];

void bzero(void *p, s32 n);
typedef struct {
    s32 m[16];
} Mtx29;
void guMtxL2F(f32 mf[4][4], Mtx29 *m);
void func_80233AE0_ovl_29A4C0(f32 x, f32 y, f32 z, f32 *out, f32 mf[4][4]);
s32 func_80080D70(f32 y);
f32 sqrtf(f32 x);
f32 fabsf(f32 x);
extern s16 D_8022A994;
extern u8 D_8018FC19;
extern u8 D_8022A997;
void func_80227FD8(s32 a, s32 b);
void func_8023998C(void);
void func_8023A98C(void);
void func_80227010(void);
void *HFree(void *p);
void func_801CCA5C(s32 a, s32 b, s32 c);
u8 func_80233968_ovl_29A4C0(s32 a, s16 b, s32 c, u8 d, u8 *r, u8 *g, u8 *bl);
u8 func_8019F174(u8 a);
u8 func_801C1AA4(s32 a, s32 b, u8 c, s16 d, s16 e, s32 f, u8 *r, u8 *g, u8 *bl);
void func_8019F2C0(u8 a);
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern s16 *D_8022A97C;
void *HMalloc(s32 size);
s32 ChunkSize(s32 id);
void LoadChunkRaw(void *dst, s32 id);
u32 ReadU32BE(void *p);
void DecodeLZ(void *dst, void *src);
void func_802329B0_ovl_29A4C0(void);
void func_8019F354(u8 a);
typedef struct {
    s32 unk00;
    s32 key2;
    s32 unk08;
    s32 key1;
    u8 unk10[0x24];
} Sort29C; /* size 0x34 */
void BattleAnimStep2(void *a);
void func_8022EFB0_ovl_29A4C0(void *a);
f32 func_8009CFE0(f32 y, f32 x);
f32 func_8022F280_ovl_29A4C0(f32 a);
/* --- end decls --- */

void func_8022D120_ovl_29A4C0(void) {
    u8 *tmp;

    if (D_8022A97C != NULL) {
        HFree(D_8022A97C);
    }
    tmp = HMalloc(ChunkSize(0x109EEB0));
    LoadChunkRaw(tmp, 0x109EEB0);
    D_8022A97C = HMalloc(ReadU32BE(tmp));
    DecodeLZ(D_8022A97C, tmp);
    HFree(tmp);
    func_802329B0_ovl_29A4C0();
}

/* Battle start: allocates the battle state, sets up the mode and loads the LZ battle data 0x109EEB0 */
void func_8022D1AC_ovl_29A4C0(void) {
    void *raw;

    D_8022A974 = HMalloc(0x1CB8);
    bzero(D_8022A974, 0x1CB8);
    func_80227FD8(D_8022A994, 0);
    if (D_8018FC19 == 2) {
        func_8023998C();
    } else if (D_8018FC19 == 0) {
        D_8022A997 = 0;
        func_8023A98C();
    }
    if (D_8022A97C != NULL) {
        HFree(D_8022A97C);
    }
    raw = HMalloc(ChunkSize(0x109EEB0));
    LoadChunkRaw(raw, 0x109EEB0);
    D_8022A97C = HMalloc(ReadU32BE(raw));
    DecodeLZ(D_8022A97C, raw);
    HFree(raw);
    func_802329B0_ovl_29A4C0();
    func_80227010();
}

/* Screen position of the origin under matrix m (0 when out of integer range) */
void func_8022D2A8_ovl_29A4C0(Mtx29 m, s32 *x, s32 *y) {
    f32 mf[4][4];
    f32 out[3];

    guMtxL2F(mf, &m);
    *x = 0;
    *y = 0;
    func_80233AE0_ovl_29A4C0(0.0f, 0.0f, 0.0f, out, mf);
    if (out[0] < 2147483008.0f && -2147483008.0f < out[0]) {
        *x = out[0];
    }
    if (out[2] < 2147483008.0f && -2147483008.0f < out[2]) {
        *y = out[2];
    }
}

void guLookAtF(f32 mf[4][4], f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);
void guMtxCatF(f32 m[4][4], f32 n[4][4], f32 r[4][4]);
f32 sinf(f32 x);
f32 cosf(f32 x);
void func_80233AE0_ovl_29A4C0(f32 x, f32 y, f32 z, f32 *out, f32 mf[4][4]);

/* Projects point p through model matrix m and the camera (eye, at, up, vertical fov in degrees)
 * to 320x240 screen coordinates */
void func_8022D3AC_ovl_29A4C0(f32 *out, f32 *p, f32 m[4][4], f32 *at, f32 *eye, f32 *up, f32 fov) {
    f32 mf[4][4];
    f32 v[3];
    f32 t;

    guLookAtF(mf, eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);
    guMtxCatF(m, mf, mf);
    func_80233AE0_ovl_29A4C0(p[0], p[1], p[2], v, mf);
    t = fov * 3.141592653589793 / 360.0;
    t = v[2] * sinf(t) / cosf(t);
    if (t != 0.0f) {
        out[0] = 160.0 - v[0] * 160.0f / (t * 1.333);
        out[1] = 120.0f - v[1] * 120.0f / t;
    } else {
        out[0] = v[0];
        out[1] = v[1];
    }
}

/* Vec3f {0, 1, 0} + pad (shared rodata splat leaves unmigrated) */
__asm__(".section .rodata\n.global D_802391D0_ovl_29A4C0\nD_802391D0_ovl_29A4C0:\n.word 0x00000000, 0x3F800000, 0, 0\n.section .text\n");

INCLUDE_ASM("asm/nonmatchings/29C950", func_8022D534_ovl_29A4C0);

/* Turns unit u to face point p (degrees, offset by 180) */
void func_8022D928_ovl_29A4C0(BUnit *u, f32 *p) {
    f32 a = func_8009CFE0(FIELD(u, f32, 0x11C) - p[0], p[2] - FIELD(u, f32, 0x124));

    func_8022F280_ovl_29A4C0((f32)(a * 180.0 / 3.14159265358979312) + 180.0f);
}

/* Slope from unit u to point p (horizontal distance over height difference), 0 when p is at or
 * below ground, 6 when both are on the same height step; capped at 5 */
f32 func_8022D988_ovl_29A4C0(BUnit *u, f32 *p) {
    f32 r = 6.0f;
    f32 dx;
    f32 dz;

    if (p[1] <= 0.0f) {
        r = 0.0f;
    } else if (func_80080D70(FIELD(u, f32, 0x120)) != func_80080D70(p[1])) {
        dx = FIELD(u, f32, 0x11C) - p[0];
        dz = FIELD(u, f32, 0x124) - p[2];
        dx = sqrtf(dx * dx + dz * dz);
        r = dx / (p[1] - FIELD(u, f32, 0x120));
    }
    r = fabsf(r);
    if (5.0f < r) {
        r = 5.0f;
    }
    return r;
}

/* Turns every unit to face the battle's focus point (x 4, z 0xC) and sets its approach
 * speed from the distance and height difference to the focus (0x8), capped at 5 */
#ifdef NON_MATCHING
/* unit facing/speed: only float registers in the distance differ */
void func_8022DA84_ovl_29A4C0(void) {
    u32 i;
    BUnit *u;
    Battle *b;
    f32 spd;
    f32 dx;
    f32 dz;

    if (FIELD(D_8022A974, f32, 8) == 0.0f) {
        return;
    }
    for (i = 0; i < 0x1C; i++) {
        u = D_8022A974->units[i];
        if (u == NULL) {
            continue;
        }
        FIELD(u, f32, 0x12C) = func_8022F280_ovl_29A4C0(
            (f32)(func_8009CFE0(FIELD(u, f32, 0x11C) - FIELD(D_8022A974, f32, 4),
                                FIELD(D_8022A974, f32, 0xC) - FIELD(u, f32, 0x124)) * 180.0 / 3.14159265358979312) + 180.0f);
        b = D_8022A974;
        spd = 6.0f;
        if (FIELD(b, f32, 8) <= 0.0f) {
            spd = 0.0f;
        } else if (func_80080D70(FIELD(u, f32, 0x120)) != func_80080D70(FIELD(b, f32, 8))) {
            dx = FIELD(u, f32, 0x11C) - FIELD(b, f32, 4);
            dz = FIELD(u, f32, 0x124) - FIELD(b, f32, 0xC);
            spd = sqrtf(dx * dx + dz * dz) / (FIELD(b, f32, 8) - FIELD(u, f32, 0x120));
        }
        spd = fabsf(spd);
        if (spd > 5.0f) {
            spd = 5.0f;
        }
        FIELD(u, f32, 0x130) = spd;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/29C950", func_8022DA84_ovl_29A4C0);
#endif

void func_8022DC38_ovl_29A4C0(u16 *p, s16 a, s16 b, s32 c) {
    bzero(p, 0x10);
    p[0] = a;
    p[1] = b;
    ((u8 *)p)[0xC] = 0;
    ((u8 *)p)[0xD] = 0;
    ((u8 *)p)[0xE] = 0;
    ((u8 *)p)[0xF] = c;
}

void func_8022DC9C_ovl_29A4C0(s32 a, s32 b, s32 c) {
    func_801CCA5C(a, c, b);
}

INCLUDE_ASM("asm/nonmatchings/29C950", func_8022DCC0_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29C950", func_8022DE04_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29C950", func_8022DF60_ovl_29A4C0);

#define BLIST(b, off) ((void **)((u8 *)(b) + (off)))

void func_8019F3CC(void);

/* Frees every battle unit's buffers and clears the unit tables */
void func_8022E08C_ovl_29A4C0(void) {
    u8 i;

    for (i = 0; i < 0x1C; i++) {
        HFree(D_8022A974->units[i]);
        HFree(BLIST(D_8022A974, 0xF8)[i]);
        HFree(BLIST(D_8022A974, 0x168)[i]);
        HFree(BLIST(D_8022A974, 0x248)[i]);
        HFree(BLIST(D_8022A974, 0x2B8)[i]);
        HFree(BLIST(D_8022A974, 0x1A50)[i]);
        HFree(BLIST(D_8022A974, 0x1D8)[i]);
        HFree(BLIST(D_8022A974, 0x88)[i]);
    }
    bzero(BLIST(D_8022A974, 0x18), 0x70);
    bzero(BLIST(D_8022A974, 0xF8), 0x70);
    bzero(BLIST(D_8022A974, 0x168), 0x70);
    bzero(BLIST(D_8022A974, 0x248), 0x70);
    bzero(BLIST(D_8022A974, 0x1D8), 0x70);
    bzero(BLIST(D_8022A974, 0x2B8), 0x70);
    bzero(BLIST(D_8022A974, 0x1A50), 0x70);
    bzero(BLIST(D_8022A974, 0x88), 0x70);
    func_8019F3CC();
}

void func_80079618();
void func_8017BED4(void);
void func_80234E50_ovl_29A4C0(void);
void func_8022E08C_ovl_29A4C0(void);
void func_802329E0_ovl_29A4C0(s32 a);
void func_8022BFFC_ovl_29A4C0(void);
void func_802281B4(void);
void func_80179058(void);
void func_80179018(void);
void func_80239710(void);
void func_8022CD00_ovl_29A4C0(void);
void func_8023D318(void);
void func_8023AB3C(void);
void func_8023E904(void);
void func_8023AA54(void);
void func_802408A8(s32 a, s32 b);
void func_8023A7C4(void);
void func_80227778(s32 a);
void func_80236470_ovl_29A4C0(void);
void func_8022BDDC_ovl_29A4C0(void);
void func_8022B414_ovl_29A4C0(s32 a);
void func_8023E2E8(void);
s32 func_802276EC(void);
void func_8022767C(void);
extern void *D_80238A90_ovl_29A4C0;
extern u8 D_8022A980;
extern u8 *D_8018FDC0;
extern s16 D_8018F1A0;

/* Battle screen teardown: frees the battle buffers and shuts down the subsystems by mode */
void func_8022E214_ovl_29A4C0(void) {
    func_8017BED4();
    func_80234E50_ovl_29A4C0();
    func_8022E08C_ovl_29A4C0();
    func_802329E0_ovl_29A4C0(0);
    func_8022BFFC_ovl_29A4C0();
    func_802281B4();
    HFree(D_80238A90_ovl_29A4C0);
    D_80238A90_ovl_29A4C0 = NULL;
    if (D_8018FC19 != 2) {
        if (FIELD(D_8022A974, void *, 0x1BB0) != NULL) {
            HFree(FIELD(FIELD(D_8022A974, void *, 0x1BB0), void *, 4));
            HFree(FIELD(D_8022A974, void *, 0x1BB0));
        }
    }
    HFree(D_8022A97C);
    D_8022A97C = NULL;
    func_80079618(0x02093576, 0, -0x11);
    func_80079618(-0x11);
    func_80179058();
    func_80179018();
    if (D_8018FC19 != 2) {
        func_80239710();
    }
    func_8022CD00_ovl_29A4C0();
    if (D_8018FC19 == 0) {
        func_8023D318();
        func_8023AB3C();
        func_8023E904();
        func_8023AA54();
        func_802408A8(-1, 0);
        func_8023A7C4();
    }
    func_80227778(-1);
    func_80236470_ovl_29A4C0();
    func_8022BDDC_ovl_29A4C0();
    func_8022B414_ovl_29A4C0(-1);
    if (D_8018FC19 == 2) {
        func_8023E2E8();
    }
    if ((u8)func_802276EC() == 0xD7) {
        D_8022A980 = 0xFE;
    }
    func_8022767C();
    HFree(D_8022A974);
    D_8022A974 = NULL;
    D_8018FDC0[0xD2] = 0;
    D_8018F1A0 = 0;
}

INCLUDE_ASM("asm/nonmatchings/29C950", func_8022E3DC_ovl_29A4C0);

void func_8022E698_ovl_29A4C0(s32 i, s32 v, s32 flag) {
    BUnit *u = D_8022A974->units[i];

    u->w128 = v;
    u->b145 |= 2;
    if (flag) {
        u->b145 = 4;
    } else {
        u->b145 = 2;
    }
}

u8 func_8022E6D4_ovl_29A4C0(s32 i) {
    BUnit *u = D_8022A974->units[i];
    u8 c[3];

    return func_80233968_ovl_29A4C0(u->wE8, u->h134, u->wF0, u->b146, &c[0], &c[1], &c[2]);
}

INCLUDE_ASM("asm/nonmatchings/29C950", func_8022E72C_ovl_29A4C0);

/* 16 zero bytes (shared rodata splat leaves unmigrated) */
__asm__(".section .rodata\n.global D_80239240_ovl_29A4C0\nD_80239240_ovl_29A4C0:\n.word 0, 0, 0, 0\n.section .text\n");

INCLUDE_ASM("asm/nonmatchings/29C950", BattleAnimStep2);

/* Advances u's frame counter until the colour query reports 4, then steps it back by 2 */
#ifdef NON_MATCHING
/* Only the epilogue differs: the original reloads wF0 into v0 and re-materialises 4 with li after the store; here v0 still holds 4 from the loop compare. */
s32 func_8022EEDC_ovl_29A4C0(BUnit *u) {
    u8 c[3];
    u8 r;

    u->wF4 = 0;
    while (1) {
        u->wF0++;
        if (u->b13D == 0) {
            r = func_80233968_ovl_29A4C0(u->wE8, u->h134, u->wF0, u->b146, &c[0], &c[1], &c[2]);
        } else {
            r = func_801C1AA4(u->wE8, u->wEC, u->b146, u->h13A, u->h134, u->wF0, &c[0], &c[1], &c[2]);
        }
        if (r == 4) {
            u->wF0 -= 2;
            return 4;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/29C950", func_8022EEDC_ovl_29A4C0);
#endif

INCLUDE_ASM("asm/nonmatchings/29C950", func_8022EFB0_ovl_29A4C0);

/* Wraps an angle into [0, 360) */
f32 func_8022F280_ovl_29A4C0(f32 a) {
    for (;;) {
        if (a < 0.0f) {
            a += 360.0f;
        } else if (a >= 360.0f) {
            a -= 360.0f;
        } else {
            break;
        }
    }
    return a;
}

INCLUDE_ASM("asm/nonmatchings/29C950", func_8022F2CC_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29C950", func_8022FDB8_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29C950", func_80230744_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29C950", func_80230858_ovl_29A4C0);

u8 func_80230B24_ovl_29A4C0(u8 a) {
    return func_8019F174(a);
}

void func_80230B44_ovl_29A4C0(u8 a) {
    func_8019F2C0(a);
}

#include "scene.h"
void func_8022D534_ovl_29A4C0(s32 *a, f32 *out, s32 b, s32 c);
typedef struct { s32 v[3]; } Pt29C;
extern Pt29C D_80239240_ovl_29A4C0;

/* Moves each visible unit's name label (scene slot) to its projected screen position */
void func_80230B60_ovl_29A4C0(s32 a0, s32 a1, s32 a2, s32 arg0) {
    Pt29C p;
    f32 out[2];
    s16 i;

    p = D_80239240_ovl_29A4C0;
    for (i = 0; i < 0x1C; i++) {
        s16 *o = ((s16 **)((u8 *)D_8022A974 + 0x1D8))[i];
        u32 y;
        if (o != NULL && (y = (u32)D_8022A974->units[i]) != 0) {
            s16 n = o[0];
            if (!(D_800E82C8[n].unk8A & 0x40) && (D_800E82C8[n].flags & 0x8000)) {
                func_8022D534_ovl_29A4C0(p.v, out, y + 0xA0, arg0);
                arg0 = out[0];
                if (out[1] < (s16)(o[2] * 14 + 0x31)) {
                    y = (s32)out[1] - 0x14;
                } else {
                    y = (s32)out[1] - 0x2D;
                }
                {
                    u8 xh = (u32)arg0 >> 8;
                    u8 yh = y >> 8;
                    D_800E82C8[n].unk8C = xh;
                    D_800E82C8[n].unk8D = arg0;
                    D_800E82C8[n].unk94 = yh;
                    D_800E82C8[n].unk95 = y;
                }
            }
        }
    }
}

void func_80230D0C_ovl_29A4C0(s16 a) {
    D_800E9C0A[1] = a;
}

void func_80230D18_ovl_29A4C0(s32 id) {
    s16 k;
    u8 *p;

    for (k = 0; k < 28; k++) {
        p = FIELD(D_8022A974, u8 *, 0x1D8 + k * 4);
        if (p != NULL && FIELD(p, s16, 2) == id) {
            HFree(p);
            FIELD(D_8022A974, u8 *, 0x1D8 + k * 4) = NULL;
            break;
        }
    }
    func_8019F354(id);
}

u8 func_80230DAC_ovl_29A4C0(s32 i) {
    return D_8019EE40[i];
}

void func_80230DBC_ovl_29A4C0(s32 i) {
    s32 k;
    s32 end;

    if (i == -1) {
        i = 0;
        end = 28;
    } else {
        end = i + 1;
    }
    for (k = i; k < end; k++) {
        if (D_8022A974->units[k] != NULL) {
            HFree(D_8022A974->units[k]);
            D_8022A974->units[k] = NULL;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/29C950", func_80230E50_ovl_29A4C0);

/* Steps unit animations (28) and effect objects (30) unless paused */
void func_80230FD4_ovl_29A4C0(void) {
    s16 i;

    if (FIELD(D_8022A974, u8, 0x1CB1) == 0) {
        for (i = 0; i < 28; i++) {
            if (D_8022A974->units[i] != NULL) {
                BattleAnimStep2(D_8022A974->units[i]);
            }
        }
        for (i = 0; i < 30; i++) {
            if (((void **)((u8 *)D_8022A974 + 0x1AC0))[i] != NULL) {
                func_8022EFB0_ovl_29A4C0(((void **)((u8 *)D_8022A974 + 0x1AC0))[i]);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/29C950", func_80231090_ovl_29A4C0);

/* Snaps the unit's x/z to the target when within 0.1; returns bit 0 = x snapped, bit 1 = z snapped */
s16 func_80231238_ovl_29A4C0(BUnit *u, f32 x, f32 z, f32 tx, f32 tz) {
    s16 r = 0;

    if (x < tx + 0.1 && tx - 0.1 < x) {
        FIELD(u, f32, 0x11C) = tx;
        r = 1;
    }
    if (z < tz + 0.1 && tz - 0.1 < z) {
        FIELD(u, f32, 0x124) = tz;
        r += 2;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/29C950", func_802312E4_ovl_29A4C0);

/* First unit of the other side (and not in the 0x88 table) within 20 of u on both x and z, or -1 */
#ifdef NON_MATCHING
/* The original copies u from a0 to a2 at entry (so the other unit lands in a0), and it takes abs(dx) before truncating dz. */
s16 func_802315FC_ovl_29A4C0(BUnit *u) {
    u16 i;
    BUnit *o;
    s32 dx;
    s32 dz;

    for (i = 0; i < 28; i++) {
        o = D_8022A974->units[(s16)i];
        if (o == NULL) {
            continue;
        }
        if (o == u) {
            continue;
        }
        if (FIELD(o, u8, 0x147) == FIELD(u, u8, 0x147)) {
            continue;
        }
        if (D_8022A974->units[(s16)i + 28] != NULL) {
            continue;
        }
        dx = FIELD(o, f32, 0x11C) - FIELD(u, f32, 0x11C);
        dz = FIELD(o, f32, 0x124) - FIELD(u, f32, 0x124);
        if (dx < 0) {
            dx = -dx;
        }
        if (dz < 0) {
            dz = -dz;
        }
        if ((dx < 20) & (dz < 20)) {
            return (s16)i;
        }
    }
    return -1;
}
#else
INCLUDE_ASM("asm/nonmatchings/29C950", func_802315FC_ovl_29A4C0);
#endif

INCLUDE_ASM("asm/nonmatchings/29C950", func_802316C0_ovl_29A4C0);

void func_80231B2C_ovl_29A4C0(s32 i, u8 v) {
    if (D_8022A974->objs[i] != NULL) {
        D_8022A974->objs[i]->bE = v;
    }
}

void func_80231B50_ovl_29A4C0(s32 i) {
    HFree(D_8022A974->objs[i]);
    D_8022A974->objs[i] = NULL;
}

s16 func_80231B94_ovl_29A4C0(s32 i) {
    if (D_8022A974->objs[i] == NULL) {
        return 0;
    }
    return D_8022A974->objs[i]->hC;
}

/* Index of cell a * 10 + b in list id (header table holds 2 halves per id); -1 if absent or flag set */
s16 func_80231BBC_ovl_29A4C0(s32 id, s32 a, s32 b, s32 flag) {
    s16 *list = D_8022A97C + D_8022A97C[(s16)((id - 1) * 2)];
    s16 i;

    for (i = 0; list[i] != -1; i++) {
        if (a * 10 + b == list[i]) {
            if (!flag) {
                return i;
            }
            return -1;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/29C950", func_80231C54_ovl_29A4C0);

#ifdef NON_MATCHING
/* s16 range-loop register flow differs */
void func_80231DE0_ovl_29A4C0(s32 i, s32 unused, f32 v) {
    s16 k;
    s16 end;
    s16 start;

    if (i == -1) {
        start = 0;
        end = 28;
    } else {
        start = i;
        end = i + 1;
    }
    for (k = start; k < end; k++) {
        if (D_8022A974->units[k] != NULL) {
            FIELD(D_8022A974->units[k], f32, 0x12C) = v;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/29C950", func_80231DE0_ovl_29A4C0);
#endif

/* Sets the speed (pct / 100) of every part of unit i, or of all units when i == -1 */
#ifdef NON_MATCHING
/* D_8022A974 lands in v1 and end gets copied to a3; the original keeps end in v1 and the base in t0. */
void func_80231E60_ovl_29A4C0(s32 i, s32 pct) {
    s16 s;
    s16 end;
    s16 k;
    s16 j;
    BUnit *u;

    if (i == -1) {
        s = 0;
        end = 0x1C;
    } else {
        s = i;
        end = i + 1;
    }
    for (k = s; k < end; k++) {
        u = D_8022A974->units[k];
        if (u != NULL) {
            for (j = 0; j < 3; j++) {
                FIELD(u, f32, 0x104 + j * 4) = (f32)pct / 100.0;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/29C950", func_80231E60_ovl_29A4C0);
#endif

/* s16 range-loop register flow differs */
void func_80231F2C_ovl_29A4C0(s32 i, u8 v)
{
  s16 k;
  s16 end;
  unsigned short start;
  if (i == (-1))
  {
    start = 0;
    end = 28;
  }
  else
  {
    start = i;
    end = i - -1;
  }
  for (k = start; k < end; k++)
  {
    if (D_8022A974->units[k] != ((void *) 0))
    {
      *((u8 *) (((u8 *) D_8022A974->units[k]) + 0x13C)) = v;
    }
  }

}

/* qsort order: key1 ascending, then key2 descending, then original order */
#ifdef NON_MATCHING
/* pointer difference: original multiplies via shift-add chain then shifts; GCC uses mult */
s32 func_80231FB0_ovl_29A4C0(Sort29C *a, Sort29C *b) {
    if (a->key1 < b->key1) {
        return -1;
    }
    if (a->key1 > b->key1) {
        return 1;
    }
    if (a->key2 < b->key2) {
        return 1;
    }
    if (a->key2 > b->key2) {
        return -1;
    }
    return a - b;
}
#else
INCLUDE_ASM("asm/nonmatchings/29C950", func_80231FB0_ovl_29A4C0);
#endif
