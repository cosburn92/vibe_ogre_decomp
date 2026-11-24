#include "common.h"
#include "heap.h"
#include "tables.h"

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))

extern u8 *D_8022A974;
extern u8 *D_8022A978;
extern u8 D_8022A980;
void func_80227B80(void);



void func_8023BDF8_ovl_2A8D20();

#define SLOT(i) FIELD(D_8022A974 + (i) * 4, u8 *, 0x18)
extern u8 *D_801CE8BC;
u8 func_8016FF5C(u8 a, u8 b);
s32 func_801C8B68(u8 *u);
s32 func_801C8C90(u8 *u);
u8 func_801C1AA4(s32 a, s32 b, u8 c, s16 d, s16 e, s32 f, u8 *g, u8 *h, u8 *i);
extern s16 D_8022A994;
extern u8 D_8018FC19;
extern u8 D_801976E8;
void bzero(void *p, s32 n);
void func_801C22D0(s32 a);
void func_801C45E0(void);
void func_8020B098(void);
void func_801CBD48(void);
void func_801BD1F4(void);
void func_801707F4(void);
void func_80227FD8(s16 a, s32 b);
void func_8022D120(void);
void func_80227010(void);
void func_8023998C_ovl_2A8D20(void);
u8 *func_801C8FE8(s32 i);
void func_801C4778(s32 a);
void func_801ADB00(void *p);
void func_801ADBC0(void *p);
void func_8023D2DC_ovl_2A8D20(s32 a);
extern u8 D_8022A980;
extern f32 D_801CE8CC;
extern f32 D_801CE8D0;
extern f32 D_801CE8D4;
extern f32 D_801CE8D8;
extern f32 D_801CE8DC;
extern f32 D_801CE8E0;
extern f32 D_801CE8E8;
/* Battle camera: field of view, then eye and look-at points */
typedef struct {
    /* 0x00 */ f32 fovy;
    /* 0x04 */ f32 unk04[4];
    /* 0x14 */ f32 eye[3];
    /* 0x20 */ f32 at[3];
} BattleCam2A8;
extern BattleCam2A8 D_8022A720;
/* --- end decls --- */

/* Battle overlay init */
void func_802395C0_ovl_2A8D20(void) {
    D_8022A974 = HMalloc(0x1CB8);
    bzero(D_8022A974, 0x1CB8);
    func_801C22D0(2);
    func_801C45E0();
    func_8020B098();
    func_801CBD48();
    func_801BD1F4();
    func_801707F4();
    func_80227FD8(D_8022A994, 0);
    if (D_8018FC19 == 2) {
        func_8023998C_ovl_2A8D20();
    }
    func_8022D120();
    func_80227010();
}

inline s32 func_8023965C_ovl_2A8D20(u8 *o) {
    u8 *u;
    s32 r;

    if (o == NULL || o[0x147] == 0xFF) {
        return 0;
    }
    u = D_801CE8BC + 0x1C4 + o[0x147] * 0xF8;
    if (FIELD(u, s32, 0x48) == 0) {
        return 0;
    }
    r = func_801C8C90(u);
    if (r == 1) {
        if (o[0x149] == r) {
            return 2;
        }
        return 1;
    }
    return 0;
}

/* result register/branch shape at the end differs */
inline s32 func_802396E4_ovl_2A8D20(u8 *o, u8 *b)
{
  u8 *u;
  s32 r;
  if (o == ((void *) 0))
  {
    return 0;
  }
  if (o[0x147] == 0xFF)
  {
    return 0;
  }
  if (o[0x147] != b[0x147])
  {
    return 0;
  }
  u = (D_801CE8BC + 0x1C4) + (o[0x147] * 0xF8);
  if ((*((s32 *) (((u8 *) u) + 0x48))) == 0)
  {
    return 0;
  }
  r = func_801C8C90(u);
  if (r == 1)
  {
    if (o[0x149] != r)
    {
      return 1;
    }
    return r = 2;
  }
  return 0;
}

/* Swaps the objects in slots a and b, updating their back-references (+0xE4). */
inline void func_8023977C_ovl_2A8D20(u8 a, u8 b) {
    u8 *ctx = D_8022A974;
    u8 *pa = FIELD(ctx + a * 4, u8 *, 0x18);
    u8 *pb = FIELD(ctx + b * 4, u8 *, 0x18);

    FIELD(ctx + a * 4, u8 *, 0x18) = pb;
    FIELD(ctx + b * 4, u8 *, 0x18) = pa;
    if (pa != NULL) {
        FIELD(pa, s32, 0xE4) = b;
    }
    if (pb != NULL) {
        FIELD(pb, s32, 0xE4) = a;
    }
}

void guPerspective(void *m, u16 *perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale);
void guLookAt(void *m, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);
void guMtxCatL(void *a, void *b, void *out);
void func_80098AA0(void *m, f32 x, f32 y, f32 z);
void func_80098C20(void *m, f32 x, f32 y, f32 z);
typedef struct { s32 m[16]; } Mtx2A8;
extern Mtx2A8 *D_801969B0;
typedef struct { u32 w0; u32 w1; } Gfx2A8;
extern Gfx2A8 *D_800E9BA0;

/* Builds the battle camera's projection (perspective x look-at x zoom) and loads it */
void func_802397C4_ovl_2A8D20(void) {
    u8 *z = FIELD(D_8022A974, u8 *, 0x19F0);
    Mtx2A8 s;
    Mtx2A8 t;
    u16 pn;
    Gfx2A8 *g;

    guPerspective(D_801969B0, &pn, D_8022A720.fovy, 1.33333f, 1.0f, 4000.0f, 1.0f);
    guLookAt(D_801969B0 + 1, D_8022A720.eye[0], D_8022A720.eye[1], D_8022A720.eye[2], D_8022A720.at[0], D_8022A720.at[1], D_8022A720.at[2], 0.0f, 1.0f, 0.0f);
    func_80098AA0(&s, FIELD(z, f32, 0x24), FIELD(z, f32, 0x28), 1.0f);
    func_80098C20(&t, FIELD(z, f32, 0x30) / 160.0, FIELD(z, f32, 0x34) / 120.0, 0.0f);
    guMtxCatL(&s, &t, &t);
    guMtxCatL(D_801969B0, &t, D_801969B0);
    g = D_800E9BA0++;
    g->w0 = 0xDB0E0000;
    g->w1 = pn;
    g = D_800E9BA0++;
    g->w0 = 0xDA380007;
    g->w1 = (u32)D_801969B0++;
    g = D_800E9BA0++;
    g->w0 = 0xDA380005;
    g->w1 = (u32)D_801969B0++;
}

/* Copies the saved field camera into the battle camera and allocates the transform (cur/target: scale 1, offset (0,0,-50)) */
void func_8023998C_ovl_2A8D20(void) {
    f32 *t;

    D_8022A720.fovy = D_801CE8E8;
    D_8022A720.eye[0] = D_801CE8CC;
    D_8022A720.eye[1] = D_801CE8D0;
    D_8022A720.eye[2] = D_801CE8D4;
    D_8022A720.at[0] = D_801CE8D8;
    D_8022A720.at[1] = D_801CE8DC;
    D_8022A720.at[2] = D_801CE8E0;
    t = HMalloc(0x4C);
    FIELD(D_8022A974, f32 *, 0x19F0) = t;
    t[0] = t[9] = 1.0f;
    t[1] = t[10] = 1.0f;
    t[2] = t[11] = 1.0f;
    t[6] = t[15] = 0.0f;
    t[7] = t[16] = 0.0f;
    t[8] = t[17] = 0.0f;
    t[3] = t[12] = 0.0f;
    t[4] = t[13] = 0.0f;
    t[5] = t[14] = -50.0f;
    *(s16 *)&t[18] = 0;
}

void func_80239A84_ovl_2A8D20(f32 x, f32 y, f32 z, f32 w, s32 n) {
    u8 *o = FIELD(D_8022A974, u8 *, 0x19F0);

    FIELD(o, s16, 0x48) = n;
    FIELD(o, f32, 0xC) = (x - FIELD(o, f32, 0x30)) / n;
    FIELD(o, f32, 0x10) = (y - FIELD(o, f32, 0x34)) / n;
    FIELD(o, f32, 0x0) = (z - FIELD(o, f32, 0x24)) / n;
    FIELD(o, f32, 0x4) = (w - FIELD(o, f32, 0x28)) / n;
}

void func_80239AF8_ovl_2A8D20(void) {
    s32 pad;
    u8 *o = FIELD(D_8022A974, u8 *, 0x19F0);

    if (o != NULL && FIELD(o, s16, 0x48) != 0) {
        FIELD(o, s16, 0x48)--;
        FIELD(o, f32, 0x30) += FIELD(o, f32, 0xC);
        FIELD(o, f32, 0x34) += FIELD(o, f32, 0x10);
        FIELD(o, f32, 0x24) += FIELD(o, f32, 0x0);
        FIELD(o, f32, 0x28) += FIELD(o, f32, 0x4);
    }
}

s32 func_80239B68_ovl_2A8D20(void) {
    s16 v = FIELD(FIELD(D_8022A974, u8 *, 0x19F0), s16, 0x48);
    s32 r = 0;

    if (v != 0) {
        r = v;
    }
    return r;
}

/* First unit id 0..27 that no slot uses, or 0xFF */
u8 func_80239B88_ovl_2A8D20(void) {
    u8 id;
    u8 j;
    u8 *o;

    for (id = 0; id < 28; id++) {
        for (j = 0; j < 28; j++) {
            o = SLOT(j);
            if (o != NULL && o[0x147] == id) {
                break;
            }
        }
        if (j >= 28) {
            return id;
        }
    }
    return 0xFF;
}

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_80239C04_ovl_2A8D20);

u8 func_8023A0FC_ovl_2A8D20(s32 i) {
    u8 b[3];
    u8 *o = SLOT(i);

    return func_801C1AA4(FIELD(o, s32, 0xE8), FIELD(o, s32, 0xEC), o[0x146], FIELD(o, s16, 0x13A), FIELD(o, s16, 0x134),
                         FIELD(o, s32, 0xF0), &b[0], &b[1], &b[2]);
}

#define TERRAIN2A8(o, d)                                                                                       \
    func_801C1AA4(FIELD(o, s32, 0xE8), FIELD(o, s32, 0xEC), (o)[0x146], FIELD(o, s16, 0x13A), FIELD(o, s16, 0x134), \
                  FIELD(o, s32, 0xF0) + (d), NULL, NULL, NULL)

/* Whether unit i can stand where it is: not on terrain 0, nor on a 1-4-0 column while F4 < 2 */
s32 func_8023A164_ovl_2A8D20(s32 i) {
    u8 *o = SLOT(i);
    u8 t = TERRAIN2A8(o, 0);

    if (t == 0) {
        return 0;
    }
    if (t == 1 && TERRAIN2A8(o, 1) == 4 && TERRAIN2A8(o, 2) == 0 && FIELD(o, s32, 0xF4) < 2) {
        return 0;
    }
    return 1;
}

f32 func_8009CFB0(f32);                             /* extern */

f32 func_8023A270_ovl_2A8D20(void *arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    f32 var_fv1;

    temp_fv0 = FIELD(arg0, f32, 0x124);
    if (temp_fv0 < arg2) {
        var_fv1 = (f32) (((f64) func_8009CFB0((FIELD(arg0, f32, 0x11C) - arg1) / (temp_fv0 - arg2)) * 180.0) / 3.141592653589793);
    } else if (arg2 < temp_fv0) {
        var_fv1 = (f32) ((((f64) func_8009CFB0((FIELD(arg0, f32, 0x11C) - arg1) / (temp_fv0 - arg2)) * 180.0) / 3.141592653589793) + 180.0);
    } else {
        var_fv1 = -90.0f;
        if (FIELD(arg0, f32, 0x11C) < arg1) {
            var_fv1 = 90.0f;
        }
    }
    if (var_fv1 < 0.0f) {
        var_fv1 += 360.0f;
    }
    return var_fv1;
}

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023A370_ovl_2A8D20);

extern f32 D_801CE8EC;
extern f32 D_801CE8F0;
extern f32 D_801CE8F4;
f32 sqrtf(f32 x);
f32 func_8009CFE0(f32 y, f32 x); /* atan2f */

/* Pitch and yaw (degrees, into D_801CE8EC / D_801CE8F0) of camera o (eye 0x14-0x1C, at 0x20-0x28) */
#ifdef NON_MATCHING
/* 111/111: the original copies o to v0 for the second branch and loads 0x28 after the sqrt; the angles are f32 (D_801CE8EC/F0/F4) */
void func_8023AA8C_ovl_2A8D20(u8 *o) {
    f32 z = FIELD(o, f32, 0x1C);
    f32 dy;
    f32 dx;
    f32 d;
    f32 dz;

    D_801CE8F4 = 0.0f;
    if (z < 0.0f) {
        dy = FIELD(o, f32, 0x24) - FIELD(o, f32, 0x18);
        dx = FIELD(o, f32, 0x20) - FIELD(o, f32, 0x14);
        dz = FIELD(o, f32, 0x28) - z;
        d = sqrtf(dy * dy + dx * dx);
        D_801CE8EC = func_8009CFE0(d, dz) * 180.0f / 3.14159265358979312 + -90.0;
        D_801CE8F0 = (f32)(func_8009CFE0(dx, dz) * 180.0f / 3.14159265358979312) - 180.0f;
    } else {
        dy = FIELD(o, f32, 0x18) - FIELD(o, f32, 0x24);
        dx = FIELD(o, f32, 0x14) - FIELD(o, f32, 0x20);
        D_801CE8F4 = 0.0f;
        dz = z - FIELD(o, f32, 0x28);
        d = sqrtf(dy * dy + dx * dx);
        D_801CE8EC = func_8009CFE0(d, dz) * 180.0f / 3.14159265358979312 + -90.0;
        D_801CE8F0 = func_8009CFE0(dx, dz) * 180.0f / 3.14159265358979312;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023AA8C_ovl_2A8D20);
#endif

/* func_8023965C with a u8 result: 0 none, 1 on the field, 2 mounted (0x149 == 1) */
static inline u8 MountState2A8(u8 *o) {
    u8 *u;

    if (o == NULL || o[0x147] == 0xFF) {
        return 0;
    }
    u = D_801CE8BC + 0x1C4 + o[0x147] * 0xF8;
    if (FIELD(u, s32, 0x48) == 0) {
        return 0;
    }
    if (func_801C8C90(u) == 1) {
        if (o[0x149] == 1) {
            return 2;
        }
        return 1;
    }
    return 0;
}

void func_80098B60(f32 mf[4][4], f32 x, f32 y, f32 z); /* guScaleF */
void guRotateRPYF(f32 mf[4][4], f32 r, f32 p, f32 h);
extern f32 D_801D06FC;
void func_8023A370_ovl_2A8D20(f32 rot[4][4], f32 scale[4][4], u8 *o);

/* Draws the 28 battle objects with the camera rotation and the global scale; an object riding
 * another (state 2) is first placed 8 units beside its mount, by facing */
void func_8023AC50_ovl_2A8D20(void) {
    f32 rot[4][4];
    f32 scale[4][4];
    s16 i;
    s16 j;
    u8 *o;
    u8 *b;

    func_8023AA8C_ovl_2A8D20((u8 *)&D_8022A720);
    guRotateRPYF(rot, D_801CE8EC, D_801CE8F0, D_801CE8F4);
    func_80098B60(scale, D_801D06FC, D_801D06FC, D_801D06FC);
    for (i = 0; i < 28; i++) {
        o = SLOT(i);
        if (o == NULL) {
            continue;
        }
        if (MountState2A8(o) == 2) {
            for (j = 0; j < 28; j++) {
                b = SLOT(j);
                if (func_802396E4_ovl_2A8D20(b, o) == 1) {
                    break;
                }
            }
            if (j < 28) {
                if (FIELD(o, s16, 0x13A) == 1) {
                    FIELD(o, f32, 0x11C) = FIELD(b, f32, 0x11C) + 8.0f;
                    FIELD(o, f32, 0x124) = FIELD(b, f32, 0x124) - 8.0f;
                } else {
                    FIELD(o, f32, 0x11C) = FIELD(b, f32, 0x11C) - 8.0f;
                    FIELD(o, f32, 0x124) = FIELD(b, f32, 0x124) + 8.0f;
                }
                FIELD(o, f32, 0x120) = FIELD(b, f32, 0x120);
            }
        }
        func_8023A370_ovl_2A8D20(rot, scale, o);
    }
}

s32 func_8023AEA8_ovl_2A8D20(u8 *p) {
    s32 c = FIELD(p, s32, 0xE8);
    s32 r;

    if ((u32)(c - 0x51) < 3) {
        r = 1;
    } else {
        r = c == 0xA3;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023AECC_ovl_2A8D20);

s16 func_8023B428_ovl_2A8D20(s32 id, s32 mode) {
    s32 r = -1;
    s32 i;
    u8 *o;

    for (i = 0; i < 28; i++) {
        o = SLOT(i);
        if (o == NULL) {
            if (mode != 1) {
                r = i;
            }
        } else if (o[0x147] == id) {
            if (mode == 1) {
                return i;
            }
            return -1;
        }
    }
    return r;
}

u8 *func_8023B494_ovl_2A8D20(void) {
    u8 *p = FIELD(D_8022A974, u8 *, 0x1CA8);
    u8 i;

    if (p == NULL) {
        p = HMalloc(0x1D);
        FIELD(D_8022A974, u8 *, 0x1CA8) = p;
        for (i = 0; i < 28; i++) {
            p[i] = 4;
        }
    }
    return p;
}

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023B500_ovl_2A8D20);

f32 func_801BE1E0(s32 cls, s32 base);
f32 func_801BE264(s32 cls, s32 base);
void func_802312E4(s32 o, f32 a, f32 b, f32 x, f32 z, s32 c, s32 t);
void func_80239C04_ovl_2A8D20(s32 o, s32 cls, s32 base, s16 anim, s32 a, s32 b, s32 c, s32 d);

/* Turns battle object o to face its target part on unit u, moving it there at the unit's speed,
 * and starts the advance animation (5 or 11; +50 for the leader in slot 1) */
#ifdef NON_MATCHING
/* 106/106 instructions, 6 words differ: f * 555 and the target z swap f0/f2 */
s32 func_8023B998_ovl_2A8D20(u8 *o, u8 *u) {
    u8 side = func_801C8B68(u) != 0;
    u8 *p = FIELD(u + o[0x149] * 4, u8 *, 0);
    s32 px = FIELD(p, s16, 0x28);
    s32 pz = FIELD(p, s16, 0x2C);
    s16 anim;
    f32 f;

    if (side == 1) {
        anim = 11;
        if (FIELD(o, f32, 0x11C) < px) {
            anim = 5;
        }
    } else {
        anim = 11;
        if (px < FIELD(o, f32, 0x11C)) {
            anim = 5;
        }
    }
    if (anim == 5) {
        f = func_801BE1E0(FIELD(u, s32, 0x48), FIELD(u, s32, 0x4C));
    } else {
        f = func_801BE264(FIELD(u, s32, 0x48), FIELD(u, s32, 0x4C));
    }
    func_802312E4(FIELD(o, s32, 0xE4), -1.0f, -1.0f, px, pz, 0, f * 555.0f);
    if (func_801C8C90(u) == 1 && o[0x149] == 1) {
        anim += 50;
    }
    func_80239C04_ovl_2A8D20(FIELD(o, s32, 0xE4), FIELD(u, s32, 0x48), FIELD(u, s32, 0x4C), anim, side, side, 0, 1);
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023B998_ovl_2A8D20);
#endif

/* Battle camera zoom state (D_8022A974 + 0x19F0) */
typedef struct {
    /* 0x00 */ f32 dsx;
    /* 0x04 */ f32 dsy;
    /* 0x08 */ u8 unk08[4];
    /* 0x0C */ f32 dx;
    /* 0x10 */ f32 dy;
    /* 0x14 */ u8 unk14[0x10];
    /* 0x24 */ f32 sx;
    /* 0x28 */ f32 sy;
    /* 0x2C */ u8 unk2C[4];
    /* 0x30 */ f32 x;
    /* 0x34 */ f32 y;
    /* 0x38 */ u8 unk38[0x10];
    /* 0x48 */ s16 frames;
} Zoom2A8;

static inline void Zoom2A8_SetSteps(s16 n) {
    Zoom2A8 *z = FIELD(D_8022A974, Zoom2A8 *, 0x19F0);
    f32 f = n;

    z->frames = n;
    z->dx = (0.0f - z->x) / f;
    z->dy = (0.0f - z->y) / f;
    z->dsx = (1.0f - z->sx) / f;
    z->dsy = (1.0f - z->sy) / f;
}

/* Starts easing the battle camera zoom back to scale 1 / offset 0 over n frames
 * (n == 0: pick a duration from the current offset and scale); returns the picked duration */
#ifdef NON_MATCHING
/* zoom reset: float register allocation differs */
s16 func_8023BB48_ovl_2A8D20(s16 n) {
    Zoom2A8 *z = FIELD(D_8022A974, Zoom2A8 *, 0x19F0);
    s16 t = 0;
    s16 u;
    f32 s;

    D_8022A980 = 0x80;
    if (z->x == 0.0 && z->y == 0.0 && z->sx == 1.0 && z->sy == 1.0) {
        D_8022A980 = 0x81;
    }
    if ((D_8022A980 | 1) != D_8022A980) {
        if (n == 0) {
            t = (z->x * z->x + z->y * z->y) / 80.0f;
            s = (z->sy < z->sx) ? z->sx : z->sy;
            u = (s - 1.0f) * 100.0f;
            if (t < u) {
                t = u;
            }
            Zoom2A8_SetSteps(t);
        } else {
            Zoom2A8_SetSteps(n);
        }
    }
    return t;
}
#else
INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023BB48_ovl_2A8D20);
#endif

s32 func_8023BD7C_ovl_2A8D20(void) {
    s16 v = FIELD(FIELD(D_8022A974, u8 *, 0x19F0), s16, 0x48);
    s32 r = 0;

    if (v != 0) {
        r = v;
    }
    return r;
}

void func_8023BD9C_ovl_2A8D20(u8 v) {
    D_8022A980 = v;
}

void func_8023BDA8_ovl_2A8D20(s32 f) {
    if (f == 0) {
        D_8022A980 = 0xD7;
    } else {
        D_8022A980 = 0;
        func_80227B80();
    }
}

void func_8023BDDC_ovl_2A8D20(void) {
    func_8023BDF8_ovl_2A8D20();
}

#ifdef NON_MATCHING
/* The original keeps a redundant `i = 0` before the first increment. */
/* Busy-waits briefly. */
void func_8023BDF8_ovl_2A8D20(void) {
    s32 i = 0;

    for (i++; i < 28; i++) {
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023BDF8_ovl_2A8D20);
#endif

/* Moves each side's leader (alive, or below 50) into slot 0 (enemy) or 1 (player) */
void func_8023BE14_ovl_2A8D20(void) {
    s32 i;

    for (i = 0; i < 28; i++) {
        u8 *o = SLOT(i);
        u8 *u;

        if (o != NULL) {
            u = D_801CE8BC + 0x1C4 + o[0x147] * 0xF8;
            if ((func_801C8C90(u) != 1 || FIELD(o, s16, 0x138) < 50) && func_801C8C58(u) != 0) {
                if (func_801C8B68(u) != 0) {
                    if (i != 1) {
                        func_8023977C_ovl_2A8D20(1, i);
                    }
                } else {
                    if (i != 0) {
                        func_8023977C_ovl_2A8D20(0, i);
                    }
                }
            }
        }
    }
}

s32 func_801C8C58(u8 *u);

/* Checks the pair (*pa, *pb) for unit u (-1/-2/0 are special values); clears a side that
 * func_8016FF5C rejects for id */
s32 func_8023BF5C_ovl_2A8D20(s32 id, s32 *pa, s32 *pb, u8 *u) {
    s32 a = *pa;
    s32 b = *pb;

    if (a == -1 && func_801C8B68(u)) {
        return 0;
    }
    if (b == -1 && !func_801C8B68(u)) {
        return 0;
    }
    if (a == -2 && func_801C8B68(u) && func_801C8C58(u)) {
        return 0;
    }
    if (b == -2 && !func_801C8B68(u) && func_801C8C58(u)) {
        return 0;
    }
    if (a == 0 && func_801C8B68(u)) {
        return 1;
    }
    if (b == 0 && !func_801C8B68(u)) {
        return 1;
    }
    if (func_8016FF5C(a, id)) {
        *pa = 0;
        return 0;
    }
    if (func_8016FF5C(b, id)) {
        *pb = 0;
        return 0;
    }
    return 1;
}

s32 func_801C8C74(u8 *u);
f32 func_801BC35C(s16 x, s16 z);
void *memset(void *p, s32 c, u32 n);
extern s32 D_801CE8FC;
extern u8 D_8022F2CC[];

/* Places the (up to three) members of unit u in free battle slots: allocates and clears each slot,
 * sets its stats and position (height from the map unless mode 4), writes the slot numbers to out
 * and returns the first one */
#ifdef NON_MATCHING
/* 0x30C of 0x32C: GCC cross-jumps the first two slot-number arms (the original keeps all three
 * separate), and the original spills out/side to the stack and keeps the constant 1 in s8 */
s32 func_8023C0B0_ovl_2A8D20(s32 *out, u8 *u, s32 side, u16 d, s32 e, s32 f, u8 g) {
    s32 mode = 0;
    s32 first = 0;
    s32 i;
    s32 k;
    u8 *o;
    u8 **m;
    s32 *p;
    s16 hp;

    if (func_801C8C74(u) == 1) {
        mode = 1;
    } else if (func_801C8C90(u) == 1) {
        mode = 2;
    } else if (e == 0x87) {
        if (g == 1) {
            mode = 4;
        }
    } else if (e == 0xA1) {
        mode = 2;
    } else if (e == 0x88) {
        mode = 2;
    }
    m = (u8 **)u;
    p = out;
    for (i = 0; i < 3; i++, m++, p++) {
        if (*m == NULL) {
            continue;
        }
        for (k = 0; k < 28; k++) {
            if (SLOT(k) == NULL) {
                break;
            }
        }
        *p = k;
        if (i == 0) {
            first = k;
        }
        o = HMalloc(0x150);
        SLOT(k) = o;
        bzero(o, 0x150);
        if (mode == 2 && i == 1) {
            FIELD(o, s32, 0xE4) = k & 0xFF;
            hp = 60;
        } else if (mode == 4) {
            FIELD(o, s32, 0xE4) = k & 0xFF;
            hp = 60;
        } else {
            FIELD(o, s32, 0xE4) = k & 0xFF;
            hp = 10;
        }
        if (e != -1) {
            FIELD(o, s32, 0xE8) = e;
        }
        FIELD(o, s16, 0x138) = hp;
        if (f != -1) {
            FIELD(o, s32, 0xEC) = f;
        }
        o[0x13D] = 1;
        FIELD(o, s16, 0x134) = hp;
        FIELD(o, s32, 0xF0) = -1;
        FIELD(o, s32, 0xF4) = 0;
        FIELD(o, s32, 0xF8) = 0;
        FIELD(o, s32, 0x12C) = 0;
        FIELD(o, u8 *, 0xE0) = D_8022F2CC;
        FIELD(o, u16, 0x13A) = d;
        FIELD(o, s32, 0x12C) = 0;
        FIELD(o, f32, 0x130) = 1.0f;
        FIELD(o, s32, 0x128) = 0;
        o[0x145] = 1;
        o[0x13C] = D_801CE8FC;
        memset(o, 0xFF, 0x10);
        bzero(o + 0x10, 0x10);
        o[0x146] = d;
        o[0x141] = 0;
        FIELD(o, f32, 0x11C) = FIELD(*m, s16, 0x28);
        FIELD(o, f32, 0x124) = FIELD(*m, s16, 0x2C);
        if (mode != 4) {
            FIELD(o, f32, 0x120) = (s16)func_801BC35C(FIELD(o, f32, 0x11C), FIELD(o, f32, 0x124));
        } else {
            FIELD(o, f32, 0x120) = FIELD(*m, s16, 0x2A);
        }
        for (k = 0; k < 3; k++) {
            FIELD(o, f32, 0x104 + k * 4) = 1.0f;
            FIELD(o, s32, 0x110 + k * 4) = 0;
            o[0x142 + k] = 0xFF;
        }
        o[0x149] = i;
        o[0x147] = side;
    }
    return first;
}
#else
INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023C0B0_ovl_2A8D20);
#endif

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023C3DC_ovl_2A8D20);

s32 func_8023C804_ovl_2A8D20(s32 i) {
    u8 *o = SLOT(i);
    s32 r;

    if (o == NULL || o[0x147] == 0xFF) {
        return 0;
    }
    r = func_801C8B68(D_801CE8BC + 0x1C4 + o[0x147] * 0xF8);
    if (r == 0) {
        return 1;
    }
    return 2;
}

extern u8 D_8022A981;
extern s32 D_801CEAB0;
extern u8 D_80196AED;
extern u8 *D_801CE8C0;
extern u8 D_801976D8;
extern u16 D_80197B60;
extern u8 D_80190F80[];
typedef struct {
    /* 0x00 */ Character c;
    /* 0x34 */ u8 unk34[4];
} PlayerChar2A8; /* size 0x38 */
extern PlayerChar2A8 D_80193BC0[];
extern u8 D_8022A7F0;
void func_801BE71C(void);
void func_80080998(void *dst, void *src, s32 n);
void func_801C1D90(void);
void func_801C1A94(void);
void func_801C2310(void);
void func_801BC5FC(void);
void func_801BC640(void);
void func_801B7E9C(void);
void func_801C5CE0(void);
void func_801AECA4(s32 a);
void func_8020B29C(void);

/* Sets up the map scene once: its work area, a snapshot of the army (0x16C bytes of state plus
 * every character's HP and status) when needed, then the scene modules */
void func_8023C874_ovl_2A8D20(void) {
    if (D_8022A981 == 0) {
        D_801CEAB0 = D_80196AED;
        func_801BE71C();
        D_801CE8BC = HMalloc(0x6094);
        bzero(D_801CE8BC, 0x6094);
        D_801CE8C0 = D_801CE8BC + 0x57E0;
        if ((D_801976D8 & 8) || D_80197B60 != 0) {
            u8 *snap = HMalloc(0x298);
            s32 i;

            func_80080998(snap, D_80190F80, 0x16C);
            for (i = 0; i < 100; i++) {
                ((u16 *)(snap + 0x16C))[i] = D_80193BC0[i].c.hp;
                (snap + i)[0x234] = D_80193BC0[i].c.status;
            }
            FIELD(D_801CE8BC, u8 *, 0x607C) = snap;
        }
        func_801C1D90();
        func_801C1A94();
        func_801C2310();
        func_801BC5FC();
        func_801BC640();
        func_801B7E9C();
        func_801C5CE0();
        func_801AECA4(D_8022A7F0);
        func_8020B29C();
    }
}

void func_8023C9BC_ovl_2A8D20(void) {
    HFree(FIELD(D_8022A974, void *, 0x19F0));
    FIELD(D_8022A974, void *, 0x19F0) = NULL;
}

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023C9EC_ovl_2A8D20);

extern Character D_80195560[];
extern u8 D_8022A920[][2];

/* Portrait expression of unit i: gender * 3 plus alignment band (0-32, 33-65, 66+), unless its
 * class has a fixed face in D_8022A920 ({face, class} pairs ending at class 0xFF); 0xFF if none */
#ifdef NON_MATCHING
/* 80 vs 83 instructions: the original keeps the sign fix-up of al / 33 (GCC here knows al is non-negative) and walks the face table with separate pointer/index registers */
u8 func_8023CFA0_ovl_2A8D20(s32 i) {
    u8 *o = SLOT(i);
    u8 *u;
    s32 al;
    u8 g;
    u8 r;
    s32 j;

    if (o == NULL) {
        return 0xFF;
    }
    u = D_801CE8BC + 0x1C4 + o[0x147] * 0xF8;
    if (FIELD(u, s32, 0x48) == 0) {
        return 0xFF;
    }
    al = u[0x34];
    if (func_801C8B68(u) == 0) {
        g = D_80193BC0[u[0xF6]].c.gender;
    } else {
        g = D_80195560[u[0xF6]].gender;
    }
    if (al >= 99) {
        al = 98;
    }
    r = g * 3 + al / 33;
    if (D_8022A920[0][1] != 0xFF) {
        for (j = 0; D_8022A920[j][1] != 0xFF; j++) {
            if (D_8022A920[j][1] == FIELD(u, s32, 0x48)) {
                r = D_8022A920[j][0];
            }
        }
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023CFA0_ovl_2A8D20);
#endif

/* Finds the first battle unit record (20 x 0xF8 from 0x1C4) whose id passes func_8016FF5C(id, kind),
 * then swaps the first unit slot of that side with slot `slot` */
typedef struct {
    u8 unk00[0x48];
    s32 id;
    u8 unk4C[0xAC];
} Unit2A8; /* size 0xF8 */
typedef struct {
    u8 unk000[0x1C4];
    Unit2A8 units[20];
} Army2A8;

void func_8023D0EC_ovl_2A8D20(u8 slot, u8 kind) {
    s32 i;
    s32 k;
    s32 id;
    s32 off;
    u8 *d;
    u8 *a;
    u8 *b;

    i = 0;
    off = 0x1C4;
    do {
        id = FIELD(D_801CE8BC + off, s32, 0x48);
        if (id != 0 && func_8016FF5C(id, kind)) {
            break;
        }
        i++;
        off += 0xF8;
    } while (i < 20);
    if (i < 20) {
        d = D_8022A974;
        for (k = 0; k < 28; k++) {
            if (FIELD(d + k * 4, u8 *, 0x18) != NULL && FIELD(d + k * 4, u8 *, 0x18)[0x147] == i) {
                b = FIELD(d + (u8)k * 4, u8 *, 0x18);
                a = FIELD(d + slot * 4, u8 *, 0x18);
                FIELD(d + (u8)k * 4, u8 *, 0x18) = a;
                FIELD(d + slot * 4, u8 *, 0x18) = b;
                if (b != NULL) {
                    FIELD(b, s32, 0xE4) = slot;
                }
                if (a != NULL) {
                    FIELD(a, s32, 0xE4) = (u8)k;
                }
                return;
            }
        }
    }
}

/* Swaps display slot `slot` with the slot showing the unit at map cell `cell` (row * 3 + lane) */
#ifdef NON_MATCHING
/* loop over slots uses a pointer IV with hoisted base; swap stores the back-refs in the opposite order to func_8023977C */
void func_8023D1E8_ovl_2A8D20(u8 slot, s32 cell) {
    s32 i;
    s32 k;
    s32 row = cell / 3;

    for (i = 0; i < 20; i++) {
        u8 *u = D_801CE8BC + 0x1C4 + i * 0xF8;

        if (FIELD(u, s32, 0x48) != 0 && FIELD(u, s32, 0x58) == row && FIELD(u, s32, 0x54) == cell - FIELD(u, s32, 0x58) * 3) {
            break;
        }
    }
    if (i < 20) {
        for (k = 0; k < 28; k++) {
            if (SLOT(k) != NULL && SLOT(k)[0x147] == i) {
                func_8023977C_ovl_2A8D20(slot, k);
                return;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023D1E8_ovl_2A8D20);
#endif

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023D2DC_ovl_2A8D20);

/* Removes all 20 enemy units (and their attached effects) and resets the enemy squad */
void func_8023D7A8_ovl_2A8D20(void) {
    s32 i;
    u32 k;
    u8 *u;

    for (i = 0; i < 20; i++) {
        u = func_801C8FE8(i);
        if (func_801C8B68(u) == 0) {
            continue;
        }
        func_801C4778(FIELD(u, s32, 0x50));
        for (k = 0; k < 3; k++) {
            if (((u8 **)u)[k] != NULL) {
                FIELD(((u8 **)u)[k], s32, 0x18) = 0;
                FIELD(((u8 **)u)[k + 3], s32, 0x18) = 0;
                func_801ADB00(((u8 **)u)[k]);
                func_801ADBC0(((u8 **)u)[k + 3]);
                ((u8 **)u)[k] = NULL;
                ((u8 **)u)[k + 3] = NULL;
            }
        }
        bzero(u, 0xF8);
    }
    func_8023D2DC_ovl_2A8D20(0x1E);
    D_801976E8 = 0x1E;
}

s16 func_80231238(u8 *o, f32 x, f32 z, f32 tx, f32 tz);
s32 func_801C8C58(u8 *u);

/* Starts the walk-in of every placed battle object whose unit belongs to the side and line of
 * phase n (n / 3: side, n % 3: 0 all, 1 rear-line units, 2 front-line units) and is not already
 * at its formation spot; flags[i] = 1 for each started one (flags are created at 4) */
#ifdef NON_MATCHING
/* 146 vs 147: the flags pointer, phase and constant 1 get different saved registers; the original keeps n in s7 and copies the flags base once more */
void func_8023D878_ovl_2A8D20(s32 n) {
    s8 *flags = FIELD(D_8022A974, s8 *, 0x1CA8);
    s32 i;
    s32 k;

    if (flags == NULL) {
        u8 j;

        flags = HMalloc(0x1D);
        FIELD(D_8022A974, s8 *, 0x1CA8) = flags;
        for (j = 0; j < 0x1C; j++) {
            flags[j] = 4;
        }
    }
    flags[0x1C] = 0;
    k = n % 3;
    for (i = 0; i < 0x1C; i++, flags++) {
        u8 *o = SLOT(i);
        u8 *u;
        s32 side;

        if (o == NULL || o[0x147] == 0xFF) {
            continue;
        }
        u = D_801CE8BC + 0x1C4 + o[0x147] * 0xF8;
        side = func_801C8B68(u) != 0;
        if (n < 3) {
            if (side == 0) {
                continue;
            }
        } else if (side == 1) {
            continue;
        }
        if (k == 1) {
            if (func_801C8C58(u) == 0) {
                continue;
            }
        } else if (k == 2 && func_801C8C58(u) != 0) {
            continue;
        }
        {
            u8 *p = ((u8 **)u)[o[0x149]];

            if (func_80231238(o, FIELD(o, f32, 0x11C), FIELD(o, f32, 0x124), FIELD(p, s16, 0x28), FIELD(p, s16, 0x2C)) != 3) {
                s16 a;

                if (func_801C8C90(u) == 1) {
                    a = (-(o[0x149] == 1) & 0x3B) | 9;
                } else {
                    a = 9;
                }
                func_80239C04_ovl_2A8D20(i, FIELD(u, s32, 0x48), FIELD(u, s32, 0x4C), a, side, side, 0, 1);
                *flags = 1;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023D878_ovl_2A8D20);
#endif

s32 func_80231B94(s32 i);
void func_8023B998_ovl_2A8D20(u8 *o, u8 *u);
void func_80239C04_ovl_2A8D20(s32 i, s32 a, s32 b, s16 c, s32 d, s32 e, s32 f, s32 g);

/* Steps the 28 members' hit sequences (state per member at ctx+0x1CA8; 4 = done): waits for each
 * stage, then plays the hit (with 50 extra when the target is a guarded unit, 8 more for state 2) */
#ifdef NON_MATCHING
/* 126 vs 127: the original hoists the -1 argument into a saved register and spills the busy flag to the stack */
void func_8023DAC4_ovl_2A8D20(void) {
    u8 *st = FIELD(D_8022A974, u8 *, 0x1CA8);
    u8 busy = 0;

    if (st != NULL) {
        s16 i;

        for (i = 0; i < 28; i++) {
            u8 *s = &st[i];

            if (*s != 4) {
                u8 *o = ((u8 **)(D_8022A974 + 0x18))[i];
                s16 off = 0;
                u8 *u;

                busy = 1;
                u = D_801CE8BC + o[0x147] * 0xF8 + 0x1C4;
                if (func_801C8C90(u) == 1) {
                    off = -(o[0x149] == 1) & 50;
                }
                switch (*s) {
                    case 5:
                        if (func_8023A164_ovl_2A8D20(i) == 0) {
                            goto hit;
                        }
                        break;
                    case 1:
                        if (func_8023A164_ovl_2A8D20(i) == 0) {
                            *s = 2;
                            func_8023B998_ovl_2A8D20(o, u);
                        }
                        break;
                    case 2:
                        if (func_80231B94(i) == 0) {
                            if (st[0x1C] == 0) {
                                off += 8;
                            }
                        hit:
                            func_80239C04_ovl_2A8D20(i, -1, -1, off, -1, -1, 0, 1);
                            *s = 4;
                        }
                        break;
                }
            }
        }
        if (!busy) {
            HFree(st);
            FIELD(D_8022A974, void *, 0x1CA8) = NULL;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023DAC4_ovl_2A8D20);
#endif

s32 func_8023DCC0_ovl_2A8D20(void) {
    return FIELD(D_8022A974, s32, 0x1CA8) != 0;
}

extern u8 D_801971F2[][25];

/* Puts member m of the current enemy squad into battle slot k: finds its map unit, then swaps that
 * unit's battle object into slot k */
#ifdef NON_MATCHING
/* 80/80 instructions, 37 words differ: the original hoists &slot[k] out of the inner loop and keeps the member byte in s4 */
void func_8023DCD4_ovl_2A8D20(u8 k, s32 m) {
    u8 c = D_801971F2[D_801976E8][m];
    u8 i;
    u8 j;

    for (i = 0; i < 20; i++) {
        u8 *u = D_801CE8BC + 0x1C4 + i * 0xF8;

        if (func_801C8B68(u) && u[0xF6] == c && FIELD(u, s32, 0x48) != 0) {
            for (j = 0; j < 28; j++) {
                u8 *o = SLOT(j);

                if (o != NULL && o[0x147] == i) {
                    u8 *t = SLOT(k);

                    SLOT(j) = t;
                    SLOT(k) = o;
                    FIELD(o, s32, 0xE4) = k;
                    if (t != NULL) {
                        FIELD(t, s32, 0xE4) = j;
                    }
                    return;
                }
            }
            return;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023DCD4_ovl_2A8D20);
#endif

s32 func_801C8B84(u8 *u);
extern u8 D_801976DC;
extern u8 D_801976E8;
extern u16 D_80190EBC[];
extern u8 D_80191010[];
extern u16 D_8019532C[];
extern u8 D_80195480[];

/* 1 when unit u is out of action (no HP or status bit 2), except in mode 1 */
s32 func_8023DE14_ovl_2A8D20(u8 *u) {
    s32 r = 0;
    s32 st;
    u8 k;
    s32 c;

    if (D_8022A7F0 == 1) {
        return 0;
    }
    if (func_801C8B84(u)) {
        c = D_801976DC < 30;
    } else {
        c = D_801976E8 < 30;
    }
    if (c) {
        k = u[0xF6];
        if (k < 100) {
            if (D_80193BC0[k].c.hp == 0) {
                r = 1;
            }
            st = D_80193BC0[k].c.status & 4;
        } else {
            if (D_80190EBC[k] == 0) {
                r = 1;
            }
            st = D_80191010[k] & 4;
        }
    } else {
        k = u[0xF6];
        if (k < 100) {
            if (D_80195560[k].hp == 0) {
                r = 1;
            }
            st = D_80195560[k].status & 4;
        } else {
            if (D_8019532C[k] == 0) {
                r = 1;
            }
            st = D_80195480[k] & 4;
        }
    }
    if (st) {
        r = 1;
    }
    return r;
}

/* Sets up the cursor box (x, y, w, h; w = h = -1 means 24x24) */
void func_8023DF70_ovl_2A8D20(s32 w, s32 h, s32 x, s32 y, s32 a, s32 b) {
    D_8022A980 = 0x80;
    if (D_8022A978 == NULL) {
        D_8022A978 = HMalloc(0xE);
    }
    if (w == -1 && h == -1) {
        ((s16 *)D_8022A978)[2] = 24;
        ((s16 *)D_8022A978)[3] = 24;
    } else {
        ((s16 *)D_8022A978)[2] = w;
        ((s16 *)D_8022A978)[3] = h;
    }
    {
        s16 *p = (s16 *)D_8022A978;

        p[0] = x;
        p[1] = y;
        p[4] = 0;
        p[5] = a;
        p[6] = b;
    }
}

s32 func_80227DC4(s32 from, s32 to, s32 t, s32 n);

/* Pipe sync and a full-width scissor from line y0 down to 0xEF - y1 */
static inline void Scissor2A8(s32 y0, s32 y1) {
    s32 y;

    {
        Gfx2A8 *_g = D_800E9BA0++;

        _g->w0 = 0xE7000000;
        _g->w1 = 0;
    }
    {
        Gfx2A8 *g = D_800E9BA0++;

        if (y0 >= 0) {
            g->w0 = ((s32)(y0 * 4.0f) & 0xFFF) | 0xED000000;
        } else {
            g->w0 = 0xED000000;
        }
        y = 0xEF - y1;
        if (y != 0xF0) {
            g->w1 = ((s32)(y * 4.0f) & 0xFFF) | 0x4FC000;
        } else {
            g->w1 = 0x4FC3BC;
        }
    }
}

/* Steps the letterbox (D_8022A978: from top/bottom, to top/bottom, t, n, keep) and sets its
 * scissor; frees it once finished unless kept. Returns 0 when there is none */
#ifdef NON_MATCHING
/* 148/156 instructions: logic as in the original, which writes the pipe sync and scissor of each branch through D_800E9BA0 directly and advances it once in the shared tail */
s32 func_8023E050_ovl_2A8D20(void) {
    s32 top;
    s32 bot;

    if (D_8022A978 == NULL) {
        return 0;
    }
    if (FIELD(D_8022A978, s16, 8) == FIELD(D_8022A978, s16, 0xA)) {
        if (FIELD(D_8022A978, s16, 0xC) == 0) {
            HFree(D_8022A978);
            D_8022A978 = NULL;
            return 0;
        }
        Scissor2A8(FIELD(D_8022A978, s16, 0), FIELD(D_8022A978, s16, 2));
    } else {
        FIELD(D_8022A978, s16, 8)++;
        top = func_80227DC4(FIELD(D_8022A978, s16, 0), FIELD(D_8022A978, s16, 4), FIELD(D_8022A978, s16, 8),
                            FIELD(D_8022A978, s16, 0xA));
        bot = func_80227DC4(FIELD(D_8022A978, s16, 2), FIELD(D_8022A978, s16, 6), FIELD(D_8022A978, s16, 8),
                            FIELD(D_8022A978, s16, 0xA));
        Scissor2A8(top, bot);
    }
    {
        Gfx2A8 *_g = D_800E9BA0++;

        _g->w0 = 0xE7000000;
        _g->w1 = 0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023E050_ovl_2A8D20);
#endif

s32 func_8023E2C0_ovl_2A8D20(void) {
    u8 *p = D_8022A978;
    s32 r = 0;

    if (p != NULL) {
        r = FIELD(p, s16, 0x8) != FIELD(p, s16, 0xA);
    }
    return r;
}

void func_8023E2E8_ovl_2A8D20(void) {
    HFree(D_8022A978);
    D_8022A978 = NULL;
}
