#include "common.h"

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))

extern u8 *D_8022A974;
extern u8 *D_8022A978;
extern u8 D_8022A980;
void HFree(void *p);
void func_80227B80(void);



void func_8023BDF8_ovl_2A8D20();

#define SLOT(i) FIELD(D_8022A974 + (i) * 4, u8 *, 0x18)
extern u8 *D_801CE8BC;
u8 func_8016FF5C(u8 a, u8 b);
void *HMalloc(s32 size);
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
extern f32 D_8022A720;
extern f32 D_8022A734;
extern f32 D_8022A738;
extern f32 D_8022A73C;
extern f32 D_8022A740;
extern f32 D_8022A744;
extern f32 D_8022A748;
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

s32 func_8023965C_ovl_2A8D20(u8 *o) {
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

#ifdef NON_MATCHING
/* result register/branch shape at the end differs */
s32 func_802396E4_ovl_2A8D20(u8 *o, u8 *b) {
    u8 *u;
    s32 r;

    if (o == NULL) {
        return 0;
    }
    if (o[0x147] == 0xFF) {
        return 0;
    }
    if (o[0x147] != b[0x147]) {
        return 0;
    }
    u = D_801CE8BC + 0x1C4 + o[0x147] * 0xF8;
    if (FIELD(u, s32, 0x48) == 0) {
        return 0;
    }
    r = func_801C8C90(u);
    if (r == 1) {
        if (o[0x149] != r) {
            return 1;
        }
        return 2;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/2A8D20", func_802396E4_ovl_2A8D20);
#endif

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

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_802397C4_ovl_2A8D20);

/* Copies the saved field camera into the battle camera and allocates the transform (cur/target: scale 1, offset (0,0,-50)) */
void func_8023998C_ovl_2A8D20(void) {
    f32 *t;

    D_8022A720 = D_801CE8E8;
    D_8022A734 = D_801CE8CC;
    D_8022A738 = D_801CE8D0;
    D_8022A73C = D_801CE8D4;
    D_8022A740 = D_801CE8D8;
    D_8022A744 = D_801CE8DC;
    D_8022A748 = D_801CE8E0;
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

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023A164_ovl_2A8D20);

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

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023AA8C_ovl_2A8D20);

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_80098B60(s32 *, f32, f32, f32);    /* extern */
s32 guRotateRPYF(s32 *, s32, s32, s32);     /* extern */
extern s32 D_801CE8EC;
extern s32 D_801CE8F0;
extern s32 D_801CE8F4;
extern f32 D_801D06FC;

void func_8023AC50_ovl_2A8D20(void) {
    s32 sp10;
    s32 sp50;
    f32 var_fv0;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 var_s2;
    s16 var_s4;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 temp_v1;
    u8 temp_v1_2;
    void *temp_s0;
    void *temp_s1;

    var_s4 = 0;
    func_8023AA8C_ovl_2A8D20(&D_8022A720);
    guRotateRPYF(&sp10, D_801CE8EC, D_801CE8F0, D_801CE8F4);
    func_80098B60(&sp50, D_801D06FC, D_801D06FC, D_801D06FC);
    do {
        temp_s1 = FIELD(&D_8022A974[(s32) (var_s4 << 0x10) >> 0xE], void *, 0x18);
        if (temp_s1 != NULL) {
            temp_v1 = FIELD(temp_s1, u8, 0x147);
            if (temp_v1 != 0xFF) {
                temp_a0 = D_801CE8BC + ((temp_v1 * 0xF8) + 0x1C4);
                var_v1 = 0;
                if (FIELD(temp_a0, s32, 0x48) != 0) {
                    var_v1 = 0;
                    if (func_801C8C90(temp_a0) == 1) {
                        var_v1 = 1;
                        if (FIELD(temp_s1, u8, 0x149) == 1) {
                            var_v1 = 2;
                        }
                    }
                }
            } else {
                var_v1 = 0;
            }
            if ((var_v1 & 0xFF) == 2) {
                var_s2 = 0;
loop_10:
                temp_s0 = FIELD(&D_8022A974[(s32) (var_s2 << 0x10) >> 0xE], void *, 0x18);
                var_v0 = 0;
                if (temp_s0 != NULL) {
                    temp_v1_2 = FIELD(temp_s0, u8, 0x147);
                    if (temp_v1_2 != 0xFF) {
                        var_v0 = 0;
                        if (temp_v1_2 == FIELD(temp_s1, u8, 0x147)) {
                            temp_a0_2 = D_801CE8BC + ((temp_v1_2 * 0xF8) + 0x1C4);
                            var_v0 = 0;
                            if (FIELD(temp_a0_2, s32, 0x48) != 0) {
                                var_v0 = 0;
                                if (func_801C8C90(temp_a0_2) == 1) {
                                    var_v0 = 1;
                                    if (FIELD(temp_s0, u8, 0x149) == 1) {
                                        var_v0 = 2;
                                    }
                                }
                            }
                        }
                    }
                }
                temp_v0_2 = var_s2 + 1;
                if (var_v0 != 1) {
                    var_s2 = temp_v0_2;
                    if (temp_v0_2 < 0x1C) {
                        goto loop_10;
                    }
                }
                if (var_s2 < 0x1C) {
                    if (FIELD(temp_s1, s16, 0x13A) == 1) {
                        FIELD(temp_s1, f32, 0x11C) = (f32) (FIELD(temp_s0, f32, 0x11C) + 8.0f);
                        var_fv0 = FIELD(temp_s0, f32, 0x124) - 8.0f;
                    } else {
                        FIELD(temp_s1, f32, 0x11C) = (f32) (FIELD(temp_s0, f32, 0x11C) - 8.0f);
                        var_fv0 = FIELD(temp_s0, f32, 0x124) + 8.0f;
                    }
                    FIELD(temp_s1, f32, 0x124) = var_fv0;
                    FIELD(temp_s1, f32, 0x120) = (f32) FIELD(temp_s0, f32, 0x120);
                }
            }
            func_8023A370_ovl_2A8D20(&sp10, &sp50, temp_s1);
        }
        temp_v0 = var_s4 + 1;
        var_s4 = temp_v0;
    } while (temp_v0 < 0x1C);
}
#else
INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023AC50_ovl_2A8D20);
#endif

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

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023B998_ovl_2A8D20);

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

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023BE14_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023BF5C_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023C0B0_ovl_2A8D20);

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

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023C874_ovl_2A8D20);

void func_8023C9BC_ovl_2A8D20(void) {
    HFree(FIELD(D_8022A974, void *, 0x19F0));
    FIELD(D_8022A974, void *, 0x19F0) = NULL;
}

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023C9EC_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023CFA0_ovl_2A8D20);

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

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023D878_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023DAC4_ovl_2A8D20);

s32 func_8023DCC0_ovl_2A8D20(void) {
    return FIELD(D_8022A974, s32, 0x1CA8) != 0;
}

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023DCD4_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023DE14_ovl_2A8D20);

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

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023E050_ovl_2A8D20);

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
