#include "common.h"

/* 29C950 */

typedef struct {
    /* 0x000 */ u8 unk000[0xE8];
    /* 0x0E8 */ s32 wE8;
    /* 0x0EC */ u8 unk0EC[4];
    /* 0x0F0 */ s32 wF0;
    /* 0x0F4 */ u8 unk0F4[0x34];
    /* 0x128 */ s32 w128;
    /* 0x12C */ u8 unk12C[8];
    /* 0x134 */ s16 h134;
    /* 0x136 */ u8 unk136[0xF];
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
void *HFree(void *p);
void func_801CCA5C(s32 a, s32 b, s32 c);
u8 func_80233968_ovl_29A4C0(s32 a, s16 b, s32 c, u8 d, u8 *r, u8 *g, u8 *bl);
u8 func_8019F174(u8 a);
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

INCLUDE_ASM("asm/nonmatchings/29C950", func_8022D1AC_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29C950", func_8022D2A8_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29C950", func_8022D3AC_ovl_29A4C0);

/* Vec3f {0, 1, 0} + pad (shared rodata splat leaves unmigrated) */
__asm__(".section .rodata\n.global D_802391D0_ovl_29A4C0\nD_802391D0_ovl_29A4C0:\n.word 0x00000000, 0x3F800000, 0, 0\n.section .text\n");

INCLUDE_ASM("asm/nonmatchings/29C950", func_8022D534_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29C950", func_8022D928_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29C950", func_8022D988_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29C950", func_8022DA84_ovl_29A4C0);

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

INCLUDE_ASM("asm/nonmatchings/29C950", func_8022E08C_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29C950", func_8022E214_ovl_29A4C0);

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

INCLUDE_ASM("asm/nonmatchings/29C950", func_8022EEDC_ovl_29A4C0);

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

INCLUDE_ASM("asm/nonmatchings/29C950", func_80230B60_ovl_29A4C0);

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

INCLUDE_ASM("asm/nonmatchings/29C950", func_80231238_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29C950", func_802312E4_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/29C950", func_802315FC_ovl_29A4C0);

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

INCLUDE_ASM("asm/nonmatchings/29C950", func_80231E60_ovl_29A4C0);

#ifdef NON_MATCHING
/* s16 range-loop register flow differs */
void func_80231F2C_ovl_29A4C0(s32 i, u8 v) {
    s16 k;
    s16 end;
    s32 start;

    if (i == -1) {
        start = 0;
        end = 28;
    } else {
        start = i;
        end = i + 1;
    }
    for (k = start; k < end; k++) {
        if (D_8022A974->units[k] != NULL) {
            FIELD(D_8022A974->units[k], u8, 0x13C) = v;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/29C950", func_80231F2C_ovl_29A4C0);
#endif

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
