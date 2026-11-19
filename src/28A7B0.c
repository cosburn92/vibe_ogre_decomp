#include "common.h"
#include "tables.h"

/* ovl_286BD0 (28A7B0) */

typedef struct {
    /* 0x00 */ u8 unk00[2];
    /* 0x02 */ u16 hi;
    /* 0x04 */ u8 mid;
    /* 0x05 */ u8 lo;
} TimeStamp;

extern u8 D_8023E5FF_ovl_286BD0[]; /* bit flags, 1-based */
extern u8 D_8023DF18_ovl_286BD0[]; /* ids, 0xFF-terminated */
extern u8 D_8023E5D0_ovl_286BD0[];
extern u8 D_8023DF0C_ovl_286BD0;
extern u8 D_8023DE3C_ovl_286BD0;
extern s32 D_800A8204[];
extern s32 D_800C4BB8;
extern u8 D_800E7A0C;
extern u8 D_8018FC00[];

void nuGfxTaskAllEndWait(void);
void func_80089AB0(void *p, s32 n);
void func_8016CD5C(s32 a);
void func_802344D0_ovl_286BD0(void);
typedef struct {
    u32 w0;
    u32 w1;
} Gfx;

typedef struct Node28 {
    /* 0x00 */ u8 unk00[4];
    /* 0x04 */ struct Node28 *next;
    /* 0x08 */ u8 unk08[0xC8];
    /* 0xD0 */ void *data;
} Node28;

typedef struct {
    /* 0x00 */ u16 count;
    /* 0x04 */ Node28 *first;
} List28;

typedef struct {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 active;
    /* 0x4 */ u16 unk4;
    /* 0x6 */ s16 sel;
} Sel28;

typedef struct {
    /* 0x0 */ u8 unk0[8];
    /* 0x8 */ s16 a;
    /* 0xA */ s16 b;
} Pair28;

extern Gfx *D_800E9BA0;
extern u8 D_8023DF48_ovl_286BD0[];
extern u8 *D_8023DE30_ovl_286BD0;
extern Pair28 *D_8023DE38_ovl_286BD0;
extern List28 *D_8018FDC0;
extern Sel28 D_8023DF10_ovl_286BD0;
extern u8 D_80197810[];
extern u8 D_8023E5A0_ovl_286BD0[];

void *HMalloc(s32 size);
void *HFree(void *p);
void bzero(void *p, s32 n);
u8 *func_80227A18(s32 id, s32 n);
void func_80238EC4_ovl_286BD0(void *p);
typedef struct {
    /* 0x00 */ void *unk00;
    /* 0x04 */ u8 *pixels;
    /* 0x08 */ u8 *tex;
    /* 0x0C */ void *chunk0C;
    /* 0x10 */ void *sprite;
    /* 0x14 */ void *chunk14;
} Res28;

typedef struct {
    /* 0x00 */ s16 x0;
    /* 0x02 */ s16 y0;
    /* 0x04 */ s16 x1;
    /* 0x06 */ s16 y1;
    /* 0x08 */ u8 unk08[0x58];
    /* 0x60 */ u8 col;
    /* 0x61 */ u8 unk61[0xF];
    /* 0x70 */ u8 row;
} Box28;

typedef struct {
    /* 0x0 */ s16 h0;
    /* 0x2 */ s16 h2;
    /* 0x4 */ s16 h4;
    /* 0x6 */ s16 h6;
    /* 0x8 */ s16 h8;
    /* 0xA */ s16 hA;
    /* 0xC */ s16 hC;
} Pair28Full;

extern Res28 *D_8023DE34_ovl_286BD0;
extern s32 D_8023DE40_ovl_286BD0;
extern s32 D_8023DE44_ovl_286BD0;
extern void *D_8022A974;
extern void *D_8018FC08;
extern void *D_8018FC0C;
extern u8 D_8022A980;
extern u8 D_800EB0B0[];

void *LoadChunkRaw(void *dst, u32 handle);
void *LoadChunk(u32 handle);
void *func_8016FBE0(u8 cls, u8 variant, void *out);
void func_800EA6B0();
void func_80227778(s32 a);
void func_802281B4(void);
void func_80179058(void);
void func_80179018(void);
void func_8022767C(void);
void func_80079618();
void func_80230ADC_ovl_286BD0(u8 a);
void func_8022FD78_ovl_286BD0(u8 a, u8 b);
void func_80231098_ovl_286BD0(u8 a, u8 b);
void func_80231D58_ovl_286BD0(u8 a, u8 b);
typedef struct {
    /* 0x00 */ u8 unk00[0x18];
    /* 0x18 */ s16 alpha; /* low byte also read alone */
    /* 0x1A */ u8 unk1A[0x16];
    /* 0x30 */ s32 x;
    /* 0x34 */ s32 y;
    /* 0x38 */ s32 w;
    /* 0x3C */ u8 unk3C[0x94];
    /* 0xD0 */ u8 *text;
} Win28;

extern u8 D_8023E0DC_ovl_286BD0[]; /* digit characters */

typedef struct {
    /* 0x00 */ Character c;
    /* 0x34 */ u8 unk34[4];
} PlayerChar; /* size 0x38 */

extern PlayerChar D_80193BC0[];

u8 func_8016FF5C(u8 cls, u8 x);
void func_8017D6D0(Win28 *w, u8 a, u8 b, u8 c, s32 d, s32 e, s32 f);
s32 strlen(const char *s);
u16 func_801794C8(char *s);
TimeStamp *func_8022EC34_ovl_286BD0(u8 i);
typedef struct {
    u8 unk0[4];
    u8 **ptrs;
} PtrTbl28;
void bzero(void *p, s32 n);
void func_80080998(void *dst, void *src, s32 n);
void func_80080998(void *dst, void *src, s32 n);
void bzero(void *p, s32 n);
typedef struct {
    u8 v[3];
} Ofs3;
extern Ofs3 D_8023E178_ovl_286BD0;
/* --- end decls --- */

void func_8022E870_ovl_286BD0(s32 unused, s32 n, u8 set) {
    u8 i;

    i = n - 1;
    if (set == 1) {
        D_8023E5FF_ovl_286BD0[i / 8] |= 1 << (i % 8);
    } else {
        D_8023E5FF_ovl_286BD0[i / 8] &= ~(1 << (i % 8));
    }
}

s32 func_8022E8D4_ovl_286BD0(s16 n) {
    return (D_8023E5FF_ovl_286BD0[n / 8] >> (n % 8)) & 1;
}

void func_8022E90C_ovl_286BD0(u8 id, u8 val) {
    s16 i;

    for (i = 0; D_8023DF18_ovl_286BD0[i] != 0xFF; i++) {
        if (D_8023DF18_ovl_286BD0[i] == id) {
            D_8023E5D0_ovl_286BD0[i] = val;
            return;
        }
    }
}

void func_8022E978_ovl_286BD0(u8 a) {
    D_8023DF0C_ovl_286BD0 = a;
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022E984_ovl_286BD0);

/* Whether b is earlier than a */
s32 func_8022EA9C_ovl_286BD0(TimeStamp *a, TimeStamp *b) {
    s32 va = a->lo + a->mid * 30 + a->hi * 600;
    s32 vb = b->lo + b->mid * 30 + b->hi * 600;

    return vb < va;
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022EB0C_ovl_286BD0);

#ifdef NON_MATCHING
/* Struct-base addressing and branch order differ. */
u8 *func_8022EC34_ovl_286BD0(s32 n) {
    Sel28 *s = &D_8023DF10_ovl_286BD0;

    if (s->active == 0) {
        D_8023DF10_ovl_286BD0.sel = -1;
    }
    if (D_8023DF10_ovl_286BD0.sel == (u8)n) {
        return (u8 *)s;
    }
    if (D_8023DF10_ovl_286BD0.sel != -1 && D_8023DF10_ovl_286BD0.sel < (u8)n) {
        n--;
    }
    if (D_80197810[(u8)n * 6] == 0xFF) {
        return NULL;
    }
    return &D_80197810[(u8)n * 6];
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022EC34_ovl_286BD0);
#endif

#ifdef NON_MATCHING
/* The count decrement is scheduled differently (target: +0xFF in the delay slot). */
u8 func_8022ECBC_ovl_286BD0(u8 id) {
    s16 i;
    u8 v;

    for (i = 0; D_8023DF18_ovl_286BD0[i] != 0xFF; i++) {
        if (D_8023DF18_ovl_286BD0[i] == id) {
            v = D_8023E5D0_ovl_286BD0[i];
            if (v == 0) {
                return 0;
            }
            return D_8023E5A0_ovl_286BD0[i] + (u8)(v - 1);
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022ECBC_ovl_286BD0);
#endif

/* Texture line size in bytes for pixel size siz and width w */
u32 func_8022ED48_ovl_286BD0(s32 siz, u32 w) {
    if (siz == 3) {
        return ((w + 3) >> 2) << 4;
    }
    if (siz == 2) {
        return ((w + 3) >> 2) << 3;
    }
    if (siz == 1) {
        return ((w + 7) >> 3) << 3;
    }
    return ((w + 15) >> 4) << 3;
}

/* Width rounded up to a whole 64-bit line for pixel size siz */
u32 func_8022ED9C_ovl_286BD0(s32 siz, u32 w) {
    if (siz == 3) {
        return ((w + 3) >> 2) << 2;
    }
    if (siz == 2) {
        return ((w + 3) >> 2) << 2;
    }
    if (siz == 1) {
        return ((w + 7) >> 3) << 3;
    }
    return ((w + 15) >> 4) << 4;
}

void func_8022EDEC_ovl_286BD0(void) {
    u8 *raw;

    D_8023DE34_ovl_286BD0 = HMalloc(0x68);
    bzero(D_8023DE34_ovl_286BD0, 0x68);
    raw = LoadChunkRaw(NULL, 0x1890C90);
    D_8023DE34_ovl_286BD0->chunk14 = LoadChunk(*(u32 *)(raw + 0x4C));
    HFree(raw);
    D_8023DE34_ovl_286BD0->sprite = func_8016FBE0(0x7D, 0, D_8023DE34_ovl_286BD0);
    D_8023DE34_ovl_286BD0->tex = func_802351F0_ovl_286BD0(&D_8023DE34_ovl_286BD0->pixels);
    D_8023DE34_ovl_286BD0->chunk0C = LoadChunk(0x1885534);
    func_800EA6B0(D_800EB0B0, 7, 5);
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022EEB4_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022F024_ovl_286BD0);

void func_8022F148_ovl_286BD0(void) {
    nuGfxTaskAllEndWait();
    func_80089AB0(D_800A8204, 3);
    D_800C4BB8 = D_800A8204[0];
    nuGfxTaskAllEndWait();
    func_8016CD5C(0);
    D_800E7A0C = 1;
}

void func_8022F1A0_ovl_286BD0(void) {
    func_80227778(-1);
    func_802281B4();
    func_80179058();
    func_80179018();
    HFree(D_8022A974);
    D_8022A974 = NULL;
    HFree(D_8023DE34_ovl_286BD0->chunk14);
    HFree(D_8023DE34_ovl_286BD0->sprite);
    HFree(D_8023DE34_ovl_286BD0->tex);
    HFree(D_8023DE34_ovl_286BD0->chunk0C);
    HFree(D_8023DE34_ovl_286BD0);
    func_80079618(-0x11);
    func_802351C4_ovl_286BD0();
    func_8022767C();
    HFree(D_8018FC08);
    HFree(D_8018FC0C);
}

void func_8022F264_ovl_286BD0(void) {
    Node28 *n;
    Node28 *cur;

    if (D_8018FDC0 != NULL) {
        n = D_8018FDC0->first;
        while (n != NULL) {
            cur = n;
            if (cur->data != NULL) {
                HFree(cur->data);
            }
            n = cur->next;
            HFree(cur);
        }
        D_8018FDC0->count = 0;
        D_8018FDC0->first = NULL;
    }
}

void func_8022F2D8_ovl_286BD0(void) {
    nuGfxTaskAllEndWait();
    func_80089AB0(D_8018FC00, 2);
    nuGfxTaskAllEndWait();
    func_8016CD5C(1);
    D_800E7A0C = 0;
    D_8023DE3C_ovl_286BD0 = 0;
}

void func_8022F324_ovl_286BD0(void) {
    nuGfxTaskAllEndWait();
    func_80089AB0(D_8018FC00, 2);
    nuGfxTaskAllEndWait();
    func_8016CD5C(1);
    D_800E7A0C = 0;
    D_8023DE3C_ovl_286BD0 = 0;
    HFree(D_8023DE34_ovl_286BD0->chunk14);
    D_8023DE34_ovl_286BD0->chunk14 = NULL;
    D_8023DE30_ovl_286BD0 = HMalloc(0x248);
    bzero(D_8023DE30_ovl_286BD0, 0x248);
    D_8023DE40_ovl_286BD0 = 0x34;
    D_8023DE44_ovl_286BD0 = 0x36;
    func_80230ADC_ovl_286BD0(D_8023DF0C_ovl_286BD0);
    func_8022FD78_ovl_286BD0(D_8023DE30_ovl_286BD0[0x244], D_8023DE30_ovl_286BD0[0x245]);
    func_80231098_ovl_286BD0(D_8023DE30_ovl_286BD0[0x244], D_8023DE30_ovl_286BD0[0x245]);
    func_80231D58_ovl_286BD0(D_8023DE30_ovl_286BD0[0x244], D_8023DE30_ovl_286BD0[0x245]);
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022F408_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022F5C4_ovl_286BD0);

void func_8022F848_ovl_286BD0(void) {
    func_802344D0_ovl_286BD0();
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022F864_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022F998_ovl_286BD0);

/* Cursor position for slot idx: grid cell (column 0x60+k, row 0x70+k) plus a small offset chosen by
 * the high nibble of a */
#ifdef NON_MATCHING
/* The switch and grid part match. What differs is the stack table indexing (index + sp, not sp + index) and the original loading p[1] before storing p[0], adding 8 to p[1] before the table byte. */
void func_8022FB60_ovl_286BD0(u8 a, u8 b, u8 idx, u8 k, u8 *o) {
    Ofs3 tab = D_8023E178_ovl_286BD0;
    s32 xi = 0;
    s32 yi = 0;
    s16 *p;

    switch (a & 0xF0) {
        case 0xA0:
        case 0xD0:
            xi = a & 7;
            yi = b & 7;
            break;
        case 0xB0:
        case 0xC0:
            xi = b & 7;
            yi = a & 7;
            break;
    }
    p = (s16 *)(o + idx * 4);
    p[0] = (o + k)[0x60] * 60;
    p[1] = (o + k)[0x70] * 72;
    p[0] += xi[tab.v];
    p[1] = yi[tab.v] + (p[1] + 8);
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022FB60_ovl_286BD0);
#endif

/* Whether direction b (high nibble) is not the opposite of a */
s32 func_8022FC54_ovl_286BD0(s32 a, s32 b) {
    switch (b & 0xF0) {
        case 0xA0:
            return (a & 0xF0) != 0xD0;
        case 0xB0:
            return (a & 0xF0) != 0xC0;
        case 0xC0:
            return (a & 0xF0) != 0xB0;
        case 0xD0:
            return (a & 0xF0) != 0xA0;
    }
    return 1;
}

void func_8022FCD4_ovl_286BD0(u8 kind, Box28 *p) {
    p->x0 = p->col * 60 + 12;
    p->y0 = p->row * 72 + 10;
    if (kind == 0xA0) {
        p->x1 = p->col * 60 + 0x30;
        p->y1 = p->row * 72 + 0x3A;
    } else {
        p->x1 = p->col * 60 + 0x2C;
        p->y1 = p->row * 72 + 0x3E;
    }
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022FD78_ovl_286BD0);

void func_802300A8_ovl_286BD0(void) {
    Gfx *g = D_800E9BA0++;

    g->w0 = 0xDE000000;
    g->w1 = (u32)D_8023DF48_ovl_286BD0;
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802300D4_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80230360_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80230ADC_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80231098_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802311B0_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80231D58_ovl_286BD0);

void func_80231EAC_ovl_286BD0(u8 k, u8 *a, u8 *b) {
    switch (k) {
        case 3:
            *b = 1;
            break;
        case 6:
            *b = 1;
            break;
        case 2:
        case 7:
            *a = 1;
            break;
        case 1:
        case 8:
            *a = 1;
            *b = 1;
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80231F04_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802320C0_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802321FC_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80232E20_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023324C_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802339D8_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80233DA8_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80233F38_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80234078_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802344D0_ovl_286BD0);

void func_802348A8_ovl_286BD0(u8 a) {
    D_8023DE30_ovl_286BD0[0x23B] = a;
}

s32 func_802348B8_ovl_286BD0(void) {
    return D_8023DE30_ovl_286BD0[0x23C] != 1;
}

void func_802348D0_ovl_286BD0(u8 a) {
    D_8023DE30_ovl_286BD0[0x23C] = a;
}

s32 func_802348E0_ovl_286BD0(u8 x) {
    u8 i;

    for (i = 0; i < 100; i++) {
        if (func_8016FF5C(D_80193BC0[i].c.cls, x)) {
            if (D_80193BC0[i].c.status & 4) {
                return 1;
            }
            return D_80193BC0[i].c.hp == 0;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023498C_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80234B38_ovl_286BD0);

void func_80234D10_ovl_286BD0(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    D_8022A980 = 0x80;
    if (D_8023DE38_ovl_286BD0 == NULL) {
        D_8023DE38_ovl_286BD0 = HMalloc(0xE);
    }
    ((Pair28Full *)D_8023DE38_ovl_286BD0)->h4 = a;
    ((Pair28Full *)D_8023DE38_ovl_286BD0)->h6 = b;
    ((Pair28Full *)D_8023DE38_ovl_286BD0)->h0 = c;
    ((Pair28Full *)D_8023DE38_ovl_286BD0)->h2 = d;
    ((Pair28Full *)D_8023DE38_ovl_286BD0)->h8 = 0;
    ((Pair28Full *)D_8023DE38_ovl_286BD0)->hA = e;
    ((Pair28Full *)D_8023DE38_ovl_286BD0)->hC = f;
}

void func_80234DB8_ovl_286BD0(void) {
    Pair28Full *p = (Pair28Full *)D_8023DE38_ovl_286BD0;

    if (p != NULL) {
        if (p->h8 == p->hA) {
            if (p->hC == 0) {
                HFree(p);
                D_8023DE38_ovl_286BD0 = NULL;
            }
        } else {
            p->h8++;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80234E10_ovl_286BD0);

s32 func_8023519C_ovl_286BD0(void) {
    Pair28 *p = D_8023DE38_ovl_286BD0;
    s32 r = 0;

    if (p != NULL) {
        r = p->a != p->b;
    }
    return r;
}

void func_802351C4_ovl_286BD0(void) {
    HFree(D_8023DE38_ovl_286BD0);
    D_8023DE38_ovl_286BD0 = NULL;
}

u8 *func_802351F0_ovl_286BD0(u8 **out) {
    u8 *t = func_80227A18(0x18855FE, 8);

    *out = t + (func_8022ED48_ovl_286BD0(t[3], *(u16 *)(t + 4)) * *(u16 *)(t + 6) + 8);
    return t;
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80235254_ovl_286BD0);

#ifdef NON_MATCHING
/* Argument setup order differs. */
void func_80235914_ovl_286BD0(Win28 *w) {
    u8 *t = w->text;
    u8 last;

    if (w->alpha != 0) {
        last = t[0x5F5] - 1;
        if (t[0x5F4] < last) {
            Gfx *g = D_800E9BA0++;

            g->w0 = 0xFA000000;
            g->w1 = ((u8 *)w)[0x19] | 0xFFFFFF00;
            func_8017D6D0(w, t[0x5F1], t[0x5F4], last, w->y - 4, w->x + 4, w->w - 12);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80235914_ovl_286BD0);
#endif

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802359B4_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802372C8_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802376B8_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80237B7C_ovl_286BD0);

/* Copies paragraph n (paragraphs end with CR LF CR LF) of text chunk 0x18855FE into dst */
#ifdef NON_MATCHING
/* only prologue scheduling of the u8 param mask vs the chunk id load differs */
void func_80238910_ovl_286BD0(u8 *dst, u8 n, u8 b) {
    u16 want;
    u8 *buf;
    s32 count;
    s32 start;
    s32 i;
    s32 len;

    want = n;
    buf = func_80227A18(0x18855FE, b);
    count = 0;
    start = 0;
    for (i = 0; i < 0xFFFFFFF; i++) {
        if (buf[i] == '\r' && buf[i + 1] == '\n' && buf[i + 2] == buf[i] && buf[i + 3] == buf[i + 1]) {
            if (want == ++count) {
                len = i - start;
                bzero(dst, len + 2);
                func_80080998(dst, buf + start, len);
                break;
            }
            start = i + 4;
        }
    }
    HFree(buf);
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80238910_ovl_286BD0);
#endif

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80238A00_ovl_286BD0);

/* Copies block idx (0x500 bytes) into o and rebases its sub-block pointers into o */
#ifdef NON_MATCHING
/* loop count test is blez (signed) in the original; register order differs */
void func_80238C4C_ovl_286BD0(u8 *o, u16 idx, PtrTbl28 *t) {
    s32 n = o[0x5F4];
    u8 *src = t->ptrs[idx];
    s32 i;

    bzero(o, 0x500);
    func_80080998(o, src, 0x500);
    for (i = 0; i < n; i++) {
        *(u8 **)(o + 0x530 + i * 4) = o + (t->ptrs[idx + i] - t->ptrs[idx]);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80238C4C_ovl_286BD0);
#endif

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80238D14_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80238EC4_ovl_286BD0);

void *func_8023906C_ovl_286BD0(void) {
    void *p = HMalloc(0x500);

    bzero(p, 0x500);
    func_80238EC4_ovl_286BD0(p);
    return p;
}

/* Index of the first save entry in date group n (groups split on hi/mid of the timestamp) */
s16 func_802390AC_ovl_286BD0(s32 n) {
    s32 g = 0;
    u8 mid = 0;
    u16 hi = 0;
    s32 i;
    TimeStamp *t;

    for (i = 0; i < 121; i++) {
        t = func_8022EC34_ovl_286BD0(i);
        if (t == NULL) {
            break;
        }
        if (hi != t->hi) {
            hi = t->hi;
            mid = t->mid;
            g++;
        } else if (mid != t->mid) {
            g++;
            mid = t->mid;
        }
        if (n == g - 1) {
            return i;
        }
    }
    return g;
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80239160_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80239394_ovl_286BD0);

/* Item index shown on display line `line` (a new group or subgroup adds an extra line);
 * past the end returns the line count */
s16 func_802394A0_ovl_286BD0(s32 line) {
    s32 k = 0;
    u8 lastB = 0;
    u16 lastH = 0;
    s32 i;
    u8 *e;

    for (i = 0; i < 121; i++) {
        e = (u8 *)func_8022EC34_ovl_286BD0(i);
        if (e == NULL) {
            break;
        }
        if (lastH != *(u16 *)(e + 2)) {
            lastB = e[4];
            if (line == k) {
                return i;
            }
            lastH = *(u16 *)(e + 2);
            k++;
        } else if (lastB != e[4]) {
            if (line == k) {
                return i;
            }
            k++;
            lastB = e[4];
        }
        if (line == k) {
            return i;
        }
        k++;
    }
    return k;
}

/* List row of date group n's header (rows count group headers plus entries) */
s16 func_80239570_ovl_286BD0(s32 n) {
    s32 g = 0;
    u8 mid = 0;
    u16 hi = 0;
    s32 r = 0;
    s32 i;
    TimeStamp *t;

    for (i = 0; i < 121; i++) {
        t = func_8022EC34_ovl_286BD0(i);
        if (t == NULL) {
            break;
        }
        if (hi != t->hi) {
            hi = t->hi;
            mid = t->mid;
            g++;
            r++;
        } else if (mid != t->mid) {
            g++;
            r++;
            mid = t->mid;
        }
        if (n + 1 == g) {
            break;
        }
        r++;
    }
    return r;
}

/* Whether list row n is a date-group header */
s32 func_80239634_ovl_286BD0(s32 n) {
    s32 k = 0;
    u8 mid = 0;
    u16 hi = 0;
    s32 i;
    TimeStamp *t;

    for (i = 0; i < 121; i++) {
        t = func_8022EC34_ovl_286BD0(i);
        if (t == NULL) {
            return 0;
        }
        if (hi != t->hi) {
            mid = t->mid;
            hi = t->hi;
            if (n == k) {
                return 1;
            }
            k++;
        } else if (mid != t->mid) {
            if (n == k) {
                return 1;
            }
            k++;
            mid = t->mid;
        }
        if (n == k) {
            return 0;
        }
        k++;
    }
    return 0;
}

/* Whether list row n is the last entry of its date group */
#ifdef NON_MATCHING
/* return-1 block placement differs */
s32 func_802396F0_ovl_286BD0(s32 n) {
    s32 k = 0;
    u8 mid = 0;
    u16 hi = 0;
    s32 i;
    TimeStamp *t;

    for (i = 0; i < 121; i++) {
        t = func_8022EC34_ovl_286BD0(i);
        if (t == NULL) {
            return 0;
        }
        if (hi != t->hi) {
            mid = t->mid;
            hi = t->hi;
            if (n == k) {
                return 0;
            }
            k++;
            if (n == k) {
                return 1;
            }
        } else {
            if (mid != t->mid) {
                if (n == k) {
                    return 0;
                }
                k++;
                mid = t->mid;
                if (n == k) {
                    return 1;
                }
            }
            if (n == k) {
                return 0;
            }
        }
        k++;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802396F0_ovl_286BD0);
#endif

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802397B8_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80239B14_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80239C5C_ovl_286BD0);

#ifdef NON_MATCHING
/* Digit loop shape differs. */
void func_80239E30_ovl_286BD0(s32 n, char *out) {
    char buf[20];
    char *o = out;
    s32 i;
    s32 j;

    for (i = 0; i < 20; i++) {
        if (n == 0) {
            *o = 0;
            break;
        }
        o++;
        buf[i] = D_8023E0DC_ovl_286BD0[n % 10];
        n /= 10;
    }
    for (j = 0; j < i; j++) {
        *out++ = (buf - 1)[i - j];
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80239E30_ovl_286BD0);
#endif

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80239EE0_ovl_286BD0);

/* Whether str (cut at p) is wider than n * 11 */
#ifdef NON_MATCHING
/* Width register allocation differs. */
s32 func_8023A398_ovl_286BD0(s32 n, char *str, char *p) {
    u8 saved = *p;
    s32 w;
    s32 len;

    *p = 0;
    len = strlen(str);
    w = 0;
    if (len != 0) {
        w = func_801794C8(str);
    }
    *p = saved;
    if (len == 0) {
        return 0;
    }
    return n * 11 < w;
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023A398_ovl_286BD0);
#endif

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023A42C_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023A5D8_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023A814_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023AA70_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023AB74_ovl_286BD0);

/* The a and b saved registers are swapped. */
#ifdef NON_MATCHING
/* a and b saved registers swapped (s1/s2); tried param types and an inline split */
u8 *func_8023AD10_ovl_286BD0(Win28 *w, s32 a, u8 b) {
    u8 *t;

    w->text = t = HMalloc(0x604);
    bzero(t, 0x604);
    t = w->text;
    t[0x5F3] = 0x3F;
    t[0x5F6] = 0xF;
    *(s32 *)(t + 0x600) = a;
    t[0x5F0] = 0;
    t[0x5FE] = 2;
    bzero(t, 0x500);
    t[0x5F4] = b;
    t[0x5F5] = b;
    return t;
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023AD10_ovl_286BD0);
#endif
