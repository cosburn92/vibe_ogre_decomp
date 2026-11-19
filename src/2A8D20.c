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
void func_8023977C_ovl_2A8D20(u8 a, u8 b) {
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

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023998C_ovl_2A8D20);

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

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023A270_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023A370_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023AA8C_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023AC50_ovl_2A8D20);

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

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023BB48_ovl_2A8D20);

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

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023D0EC_ovl_2A8D20);

INCLUDE_ASM("asm/nonmatchings/2A8D20", func_8023D1E8_ovl_2A8D20);

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
