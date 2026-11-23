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
void func_80231D58_ovl_286BD0(s16 a, s16 b);
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
u8 func_80239EE0_ovl_286BD0(s32 a, u8 *p, s32 b);
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

typedef struct {
    u16 year;
    u8 month;
    u8 day;
} Date28;
extern u8 D_80196A32;
extern u8 D_80196A33;
extern Date28 D_80196A72;
extern Date28 D_8023DC9C_ovl_286BD0[];
extern Date28 D_8023DCF8_ovl_286BD0[];
extern Date28 D_8023DE84_ovl_286BD0;
extern Date28 D_8023DEAC_ovl_286BD0;
extern Date28 D_8023DEF4_ovl_286BD0;
extern Date28 D_8023DF00_ovl_286BD0;
extern Date28 D_8023DF08_ovl_286BD0;
extern u16 gDate;

/* Age in years of character id on the current date, from its birth date record */
s16 func_8022E984_ovl_286BD0(s16 id) {
    Date28 *d;
    s16 age;

    if (id == 0xDC) {
        d = &D_8023DEAC_ovl_286BD0;
    } else if (id == 0xDD) {
        d = &D_8023DE84_ovl_286BD0;
    } else if (id < 0x54) {
        d = &D_80196A72;
    } else if (id == 0xB7) {
        d = &D_8023DEF4_ovl_286BD0;
    } else if ((u16)(id - 0x99) < 3) {
        d = &D_8023DC9C_ovl_286BD0[id];
    } else if (id == 0x96) {
        d = &D_8023DF08_ovl_286BD0;
    } else if (id < 0xC8) {
        d = &D_8023DCF8_ovl_286BD0[id];
    } else {
        d = &D_8023DF00_ovl_286BD0;
    }
    age = gDate - d->year;
    if (d->month * 30 + d->day <= D_80196A32 * 30 + D_80196A33) {
        age++;
    }
    return age;
}

/* Whether b is earlier than a */
inline s32 func_8022EA9C_ovl_286BD0(TimeStamp *a, TimeStamp *b) {
    s32 va = a->lo + a->mid * 30 + a->hi * 600;
    s32 vb = b->lo + b->mid * 30 + b->hi * 600;

    return vb < va;
}

extern u8 D_80193678[];
extern s16 D_8023DF16_ovl_286BD0;

/* Copies the current game time into the selection record (0x2) and selects the first saved
 * time stamp later than it (0x6), if the record is active */
#ifdef NON_MATCHING
/* 71/74: the original materialises the inlined comparison with a branch (bnez / li 1 / move 0) instead of slt */
void func_8022EB0C_ovl_286BD0(void) {
    s16 i;

    func_80080998((u8 *)&D_8023DF10_ovl_286BD0 + 2, D_80193678, 4);
    if (*(u8 *)&D_8023DF10_ovl_286BD0 != 0 && D_8023DF10_ovl_286BD0.active != 0) {
        for (i = 0; i < 0x79; i++) {
            if (func_8022EA9C_ovl_286BD0((TimeStamp *)&D_80197810[i * 6], (TimeStamp *)&D_8023DF10_ovl_286BD0) == 1) {
                D_8023DF16_ovl_286BD0 = i;
                return;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022EB0C_ovl_286BD0);
#endif

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

inline void func_8022EDEC_ovl_286BD0(void) {
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

extern s16 D_8022A994;
extern s32 D_8018F1A4;
extern s32 D_8022A990;
void func_80171FE0(s32 a, s32 b);
void func_8022EB0C_ovl_286BD0(void);
void func_80227FD8(s32 a, s32 b);
void func_8022A650(void);
void func_802282B8(void);

/* Enters the scene: resets the selection, previews three messages, loads the scene resources and
 * the battle work area */
void func_8022EEB4_ovl_286BD0(void) {
    bzero(D_8023E5D0_ovl_286BD0, 0x2F);
    D_8023DF10_ovl_286BD0.sel = -1;
    *(u8 *)&D_8023DF10_ovl_286BD0 = 0;
    func_80171FE0(0x43, 0);
    func_80171FE0(0x43, 1);
    func_80171FE0(0x43, 2);
    func_8022EB0C_ovl_286BD0();
    func_8022EDEC_ovl_286BD0();
    D_8023DE38_ovl_286BD0 = NULL;
    D_8022A974 = HMalloc(0x1CB8);
    bzero(D_8022A974, 0x1CB8);
    func_80227FD8(D_8022A994, 0);
    if (D_8018F1A4 != 0) {
        func_8022A650();
    }
    D_8022A990 = 0;
    func_802282B8();
}

typedef struct {
    u8 b[0x40];
} Mtx28;
typedef struct {
    u8 b[0x10];
} Vtx28;
typedef struct {
    /* 0x00 */ void *p0;
    /* 0x04 */ void *p4;
    /* 0x08 */ Mtx28 *mtx;
    /* 0x0C */ void *pC;
    /* 0x10 */ Vtx28 *vtx;
} FbSet28;
extern u8 D_800A81F0;
extern u8 D_8022A996;
extern FbSet28 *D_800E9BE0;
extern u16 D_800E79E0;
extern u16 D_800C4BE4;
extern u32 D_801969B0;
extern u32 D_80197178;
u8 func_8016CD30(void);
void func_8022F5C4_ovl_286BD0(void);
void func_8022F864_ovl_286BD0(void);
void func_8023498C_ovl_286BD0(u8 *img);
void func_8023DB88_ovl_286BD0(void);

/* Per-frame draw: points the matrix/vertex cursors at this frame's pools, draws, then advances the
 * pool counts by what was used */
void func_8022F024_ovl_286BD0(void) {
    D_8022A996 = D_800A81F0;
    D_801969B0 = (u32)(D_800E9BE0->mtx + D_800C4BE4);
    D_80197178 = (u32)(D_800E9BE0->vtx + D_800E79E0);
    if (func_8016CD30()) {
        func_8022F5C4_ovl_286BD0();
        func_8022F864_ovl_286BD0();
    } else if (((u8 *)D_8023DE34_ovl_286BD0)[0x66] != 2 && D_8023DE34_ovl_286BD0->chunk14 != NULL) {
        func_8023498C_ovl_286BD0((u8 *)D_8023DE34_ovl_286BD0->chunk14);
    }
    func_8023DB88_ovl_286BD0();
    D_800C4BE4 += (Mtx28 *)D_801969B0 - (D_800E9BE0->mtx + D_800C4BE4);
    D_800E79E0 += (Vtx28 *)D_80197178 - (D_800E9BE0->vtx + D_800E79E0);
}

inline void func_8022F148_ovl_286BD0(void) {
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

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif

void func_80089C50(void);

/* Leaves the screen: stops the graphics tasks and display, then frees the object table at
 * D_8023DE30 (50 objects with their 0x30 buffers and four buffer lists) and reloads chunk 0x14 */
void func_8022F408_ovl_286BD0(void) {
    void **t;
    s32 i;
    u8 *raw;

    func_8022F148_ovl_286BD0();
    func_80089C50();
    for (i = 0; i < 50; i++) {
        if (((void **)D_8023DE30_ovl_286BD0)[i] != NULL) {
            HFree(FIELD(((void **)D_8023DE30_ovl_286BD0)[i], void *, 0x30));
            HFree(((void **)D_8023DE30_ovl_286BD0)[i]);
        }
    }
    for (i = 0; i < 10; i++) {
        HFree(FIELD(D_8023DE30_ovl_286BD0 + i * 4, void *, 0x208));
    }
    for (i = 0; i < 10; i++) {
        if (FIELD(D_8023DE30_ovl_286BD0 + i * 4, void *, 0x168) != NULL) {
            HFree(FIELD(D_8023DE30_ovl_286BD0 + i * 4, void *, 0x168));
        }
    }
    for (i = 0; i < 40; i++) {
        if (FIELD(D_8023DE30_ovl_286BD0 + i * 4, void *, 0xC8) != NULL) {
            HFree(FIELD(D_8023DE30_ovl_286BD0 + i * 4, void *, 0xC8));
        }
    }
    for (i = 0; i < 10; i++) {
        if (FIELD(D_8023DE30_ovl_286BD0 + i * 4, void *, 0x190) != NULL) {
            HFree(FIELD(D_8023DE30_ovl_286BD0 + i * 4, void *, 0x190));
        }
    }
    HFree(D_8023DE30_ovl_286BD0);
    D_8023DE30_ovl_286BD0 = NULL;
    raw = LoadChunkRaw(NULL, 0x1890C90);
    D_8023DE34_ovl_286BD0->chunk14 = LoadChunk(*(u32 *)(raw + 0x4C));
    HFree(raw);
}

extern void *D_800C4B20; /* z buffer (NULL when unused) */
extern void *D_800E8210; /* frame buffer */
extern u8 D_80186380[];  /* full-screen fill rectangle */
u32 osVirtualToPhysical(void *p);
#define G28(w0_, w1_)                  \
    {                                  \
        Gfx *_g = D_800E9BA0++;        \
                                       \
        _g->w0 = (w0_);                \
        _g->w1 = (u32)(w1_);           \
    }

/* Clears the z buffer (when there is one) and, for the first two frames, the frame buffer, then
 * sets the frame buffer as the colour image */
void func_8022F5C4_ovl_286BD0(void) {
    G28(0xE7000000, 0);
    G28(0xE7000000, 0);
    G28(0xE3000A01, 0x300000);
    G28(0xE7000000, 0);
    G28(0xE200001C, 0);
    if (D_800C4B20 != NULL) {
        G28(0xFE000000, (u32)D_800C4B20 - 0x80000000);
        G28(0xFF10027F, (u32)D_800C4B20 - 0x80000000);
        G28(0xF7000000, 0xFFFCFFFC);
        G28(0xE7000000, 0);
        G28(0xDE000000, D_80186380);
        G28(0xE7000000, 0);
    }
    G28(0xFF10027F, osVirtualToPhysical(D_800E8210));
    if (D_8023DE3C_ovl_286BD0 < 2) {
        G28(0xF7000000, 0x10001);
        G28(0xE7000000, 0);
        G28(0xDE000000, D_80186380);
        G28(0xE7000000, 0);
    }
    G28(0xE7000000, 0);
    G28(0xE7000000, 0);
    G28(0xE3000A01, 0);
    G28(0xE7000000, 0);
    if (D_8023DE3C_ovl_286BD0 < 5) {
        D_8023DE3C_ovl_286BD0++;
    }
}

void func_8022F848_ovl_286BD0(void) {
    func_802344D0_ovl_286BD0();
}

#include "gbi_ultra.h"
void func_80098C20(Mtx28 *m, f32 x, f32 y, f32 z);
void guOrtho(Mtx28 *m, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, f32 scale);
void func_80232E20_ovl_286BD0();
void func_80230360_ovl_286BD0(s32 a);
void func_802311B0_ovl_286BD0(void);
void func_8023324C_ovl_286BD0(void);

/* (D_801969B0 is the matrix pool pointer kept as a u32 here: += 0x40 then - 0x40 is its post-increment) */
/* Sets a 320x240 orthographic camera and, unless the screen is locked (0x238), draws the grid */
void func_8022F864_ovl_286BD0(void) {
    gDPPipeSync(D_800E9BA0++);
    guOrtho((Mtx28 *)D_801969B0, -160.0f, 160.0f, -120.0f, 120.0f, -1000.0f, 2000.0f, 1.0f);
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xDA380007;
        _g->w1 = (D_801969B0 += 0x40) - 0x40;
    }
    func_80098C20((Mtx28 *)D_801969B0, 0.0f, 0.0f, 0.0f);
    {
        Gfx *_g = D_800E9BA0++;

        _g->w0 = 0xDA380003;
        _g->w1 = (D_801969B0 += 0x40) - 0x40;
    }
    if (D_8023DE30_ovl_286BD0[0x238] == 0) {
        func_80232E20_ovl_286BD0();
        func_80230360_ovl_286BD0(0);
        func_802311B0_ovl_286BD0();
        func_8023324C_ovl_286BD0();
    }
}

/* Arrow position for slot idx: grid cell k (column 0x60, row 0x70), pushed 18 out every other
 * 8 frames, plus a bob from D_8023E178 in direction a (0xA0 up, 0xB0 right, 0xC0 left, 0xD0 down) */
#ifdef NON_MATCHING
/* 108/114 instructions: as func_8022FB60, the table index is added as index + sp and 8 goes onto p[1] before the table byte; here the 0xB0 and 0xC0 cases also tail-merge */
void func_8022F998_ovl_286BD0(u8 a, s32 frame, u8 idx, u8 k, u8 *o) {
    Ofs3 tab = D_8023E178_ovl_286BD0;
    s32 f;
    s16 *p;

    p = (s16 *)(o + idx * 4);
    p[0] = (o + k)[0x60] * 60;
    f = frame & 7;
    p[1] = (o + k)[0x70] * 72;
    if (frame & 8) {
        switch (a) {
            case 0xA0:
                p[1] += 18;
                break;
            case 0xB0:
                p[0] += 18;
                break;
            case 0xC0:
                p[0] -= 18;
                break;
            case 0xD0:
                p[1] -= 18;
                break;
        }
    }
    switch (a) {
        case 0xA0:
            ((s16 *)(o + idx * 4))[0] += f[tab.v];
            break;
        case 0xB0:
            ((s16 *)(o + idx * 4))[1] = f[tab.v] + (((s16 *)(o + idx * 4))[1] + 8);
            break;
        case 0xC0:
            ((s16 *)(o + idx * 4))[0] += 60;
            ((s16 *)(o + idx * 4))[1] = f[tab.v] + (((s16 *)(o + idx * 4))[1] + 8);
            break;
        case 0xD0:
            ((s16 *)(o + idx * 4))[0] += f[tab.v];
            ((s16 *)(o + idx * 4))[1] += 72;
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8022F998_ovl_286BD0);
#endif

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

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
u8 func_8016FEF4(s32, u8);
extern u8 D_80193C09;

/* Loads the portrait sprite (0x30) of every entry that lacks one, by class: the two lords use
 * fixed classes, class 0x51 has a variant when D_80193C09 is 0x53, and two classes take their
 * variant from game flags 0xD / 0xE */
#ifdef NON_MATCHING
/* 69 vs 70: the original also keeps the class constant 0x86 in a saved register (s3) across the loop */
void func_80231098_ovl_286BD0(u8 a, u8 b) {
    s32 i;

    for (i = 0; i < 50; i++) {
        u8 *e = ((u8 **)D_8023DE30_ovl_286BD0)[i];

        if (e != NULL && FIELD(e, void *, 0x30) == NULL) {
            u16 id = FIELD(e, u16, 0x2C);
            s32 cls = id;
            u8 v;

            if (cls == 0xDC) {
                cls = 0x6D;
            }
            if (cls == 0xDD) {
                cls = 0x63;
            }
            if (id == 0x51 && D_80193C09 == 0x53) {
                cls = 0x53;
            }
            v = e[6];
            if (cls == 0x86) {
                v = func_8016FEF4(0xD, v);
            }
            if (cls == 0x71) {
                v = func_8016FEF4(0xE, v);
            }
            FIELD(e, void *, 0x30) = func_8016FBE0(cls, v, e + 0x34);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80231098_ovl_286BD0);
#endif

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802311B0_ovl_286BD0);

/* Clips the ten window rects to the 12x8 view whose corner is (x - 2, y - 2); rects outside it get
 * 0xFF clips */
#ifdef NON_MATCHING
/* 81 vs 85 instructions: the original evaluates the four overlap tests as setcc/negu/and; GCC here branches on each (same issue as 420D0 func_8016C268) */
void func_80231D58_ovl_286BD0(s16 x, s16 y) {
    u8 x0 = 0;
    u8 y0 = 0;
    u8 i;

    if (x >= 2) {
        x0 = x - 2;
    }
    if (y >= 2) {
        y0 = y - 2;
    }
    for (i = 0; i < 10; i++) {
        u8 *r = FIELD(D_8023DE30_ovl_286BD0, u8 **, 0x168 + i * 4);

        if (r == NULL) {
            break;
        }
        if (!((r[2] >= x0) & (r[3] >= y0) & (x0 + 12 >= r[0]) & (y0 + 8 >= r[1]))) {
            r[4] = 0xFF;
            r[6] = 0xFF;
            r[5] = 0xFF;
            r[7] = 0xFF;
        } else {
            r[4] = r[0];
            r[6] = r[2];
            r[5] = r[1];
            r[7] = r[3];
            if (r[0] < x0) {
                r[4] = x0;
            }
            if (r[1] < y0) {
                r[5] = y0;
            }
            if (x0 + 12 < r[2]) {
                r[6] = x0 + 12;
            }
            if (y0 + 8 < r[3]) {
                r[7] = y0 + 8;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80231D58_ovl_286BD0);
#endif

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

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_80231F04_ovl_286BD0(s32 arg0, s32 arg1, s8 *arg2, s8 *arg3, s8 *arg4, s8 *arg5) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v1;

    temp_v0 = arg1 & 0xFF;
    var_v1 = 0xF;
    switch (temp_v0) {                              /* switch 1 */
    case 3:                                         /* switch 1 */
block_6:
        *arg5 = 1;
        break;
    case 6:                                         /* switch 1 */
        goto block_6;
    case 2:                                         /* switch 1 */
    case 7:                                         /* switch 1 */
        *arg4 = 1;
        break;
    case 1:                                         /* switch 1 */
    case 8:                                         /* switch 1 */
        *arg4 = 1;
        goto block_6;
    }
    temp_v0_2 = arg0 & 0xFF;
    switch (temp_v0_2) {                            /* switch 2 */
    case 3:                                         /* switch 2 */
block_13:
        *arg3 = 1;
        break;
    case 6:                                         /* switch 2 */
        goto block_13;
    case 2:                                         /* switch 2 */
    case 7:                                         /* switch 2 */
        *arg2 = 1;
        break;
    case 1:                                         /* switch 2 */
    case 8:                                         /* switch 2 */
        *arg2 = 1;
        goto block_13;
    }
    temp_v0_3 = arg0 & 0xFF;
    switch (temp_v0_3) {                            /* switch 3 */
    case 1:                                         /* switch 3 */
        var_v1 = 0xF & 0xF5;
        break;
    case 2:                                         /* switch 3 */
        var_v1 = 0xF & 0xF9;
        break;
    case 3:                                         /* switch 3 */
        var_v1 = 0xF & 0xF6;
        break;
    case 4:                                         /* switch 3 */
        var_v1 = 0xF & 0xFA;
        break;
    case 5:                                         /* switch 3 */
        var_v1 = 0xF & 8;
        break;
    case 6:                                         /* switch 3 */
        var_v1 = 0xF & 2;
        break;
    case 7:                                         /* switch 3 */
        var_v1 = 0xF & 1;
        break;
    case 8:                                         /* switch 3 */
        var_v1 = 0xF & 4;
        break;
    }
    temp_v0_4 = arg1 & 0xFF;
    switch (temp_v0_4) {                            /* switch 4 */
    case 1:                                         /* switch 4 */
        var_v1 &= 0xF5;
        break;
    case 2:                                         /* switch 4 */
        var_v1 &= 0xF9;
        break;
    case 3:                                         /* switch 4 */
        var_v1 &= 0xF6;
        break;
    case 4:                                         /* switch 4 */
        var_v1 &= 0xFA;
        break;
    case 5:                                         /* switch 4 */
        var_v1 &= 2;
        break;
    case 6:                                         /* switch 4 */
        var_v1 &= 4;
        break;
    case 7:                                         /* switch 4 */
        var_v1 &= 8;
        break;
    case 8:                                         /* switch 4 */
        var_v1 &= 1;
        break;
    }
    temp_v1 = var_v1 & 0xFF;
    if (temp_v1 != 2) {
        var_v0 = 0;
        if (temp_v1 >= 3) {
            if (temp_v1 != 4) {
                var_v0 = 3;
                if (temp_v1 != 8) {
                    return 0;
                }
                /* Duplicate return node #41. Try simplifying control flow for better match */
                return var_v0;
            }
            var_v0 = 2;
            /* Duplicate return node #41. Try simplifying control flow for better match */
            return var_v0;
        }
        return var_v0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80231F04_ovl_286BD0);
#endif

/* Mirroring (flip x / flip y) and texture offsets (x, y; +16 y for the lower-half pieces 5-8) of
 * frame piece d (1-8) */
void func_802320C0_ovl_286BD0(s32 d, s8 *fx, s8 *fy, s32 *x, s32 *y) {
    switch ((u8)d) {
        case 3:
            *fy = 1;
            break;
        case 6:
            *fy = 1;
            break;
        case 2:
        case 7:
            *fx = 1;
            break;
        case 1:
        case 8:
            *fx = 1;
            *fy = 1;
            break;
    }
    switch ((s16)d) {
        case 1:
            *fx = 1;
            *fy = 1;
            *x = 0;
            *y = 0;
            break;
        case 2:
            *fx = 1;
            *x = 8;
            *y = 0;
            break;
        case 3:
            *fy = 1;
            *x = 0;
            *y = 8;
            break;
        case 4:
            *x = 8;
            *y = 8;
            break;
        case 5:
            *x = 8;
            *y = 0;
            break;
        case 6:
            *fy = 1;
            *x = 0;
            *y = 0;
            break;
        case 7:
            *x = 8;
            *y = 8;
            *fx = 1;
            break;
        case 8:
            *x = 0;
            *y = 8;
            *fx = 1;
            *fy = 1;
            break;
    }
    if ((s16)d >= 5) {
        *y += 16;
    }
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802321FC_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80232E20_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023324C_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802339D8_ovl_286BD0);

/* Finds the entry under the cursor (0x230/0x234, cells 60x72); 0 if none. Unless mode is 1 or
 * the list is locked (0x23C), selects it (0x23E) and stores which screen edge it touches (0x23F:
 * +1 right, +2 bottom, relative to the scroll origin 0x244/0x245) */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
#ifdef NON_MATCHING
/* 99/100: the mode==1 exit shares the setter's return-1 block in the original (bne over j/li); ours threads it */
s32 func_80233DA8_ovl_286BD0(s32 mode) {
    s32 i;
    s32 x = FIELD(D_8023DE30_ovl_286BD0, s32, 0x230) - 0x34;
    s32 y = FIELD(D_8023DE30_ovl_286BD0, s32, 0x234) - 0x36;
    u8 *e;

    for (i = 0; i < 50; i++) {
        s32 cx, cy;
        s32 dx, dy;
        s32 k;

        e = ((u8 **)D_8023DE30_ovl_286BD0)[i];
        if (e == NULL) {
            continue;
        }
        cx = e[4] * 60;
        cy = e[5] * 72;
        if (x < cx) continue;
        if (x > cx + 60) continue;
        if (y < cy) continue;
        if (y > cy + 72) continue;
        if (mode == 1) {
            return 1;
        }
        if (D_8023DE30_ovl_286BD0[0x23C] == 1) {
            return 1;
        }
        D_8023DE30_ovl_286BD0[0x23E] = i;
        dx = e[4] - D_8023DE30_ovl_286BD0[0x244];
        dy = e[5] - D_8023DE30_ovl_286BD0[0x245];
        k = 0;
        if (dx == 4 || dy == 2) {
            s32 sx = FIELD(D_8023DE30_ovl_286BD0, s32, 0x1C4) - FIELD(D_8023DE30_ovl_286BD0, s32, 0x1B8);
            s32 sy = FIELD(D_8023DE30_ovl_286BD0, s32, 0x1EC) - FIELD(D_8023DE30_ovl_286BD0, s32, 0x1E0);

            sx = dx >= 4 ? sx : 0;
            if (dx >= 5) {
                sx = 1;
            }
            sy = dy >= 2 ? sy : 0;
            if (dy >= 3) {
                sy = 1;
            }
            if (sy > 0) {
                k = 2;
            }
            k += sx > 0;
        } else {
            if (dy >= 3) {
                k = 2;
            }
            k += dx >= 5;
        }
        D_8023DE30_ovl_286BD0[0x23F] = k;
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80233DA8_ovl_286BD0);
#endif

/* Scrolls the grid cursor one cell (dir 4 left, 5 right, 6 up, 7 down) within the 60x72 grid */
inline void func_80233F38_ovl_286BD0(u8 dir) {
    switch (dir) {
        case 4:
            if (D_8023DE40_ovl_286BD0 >= 0x35) {
                D_8023DE30_ovl_286BD0[0x244]--;
                D_8023DE40_ovl_286BD0 -= 60;
            }
            break;
        case 5:
            if (D_8023DE40_ovl_286BD0 < 0x35) {
                D_8023DE30_ovl_286BD0[0x244]++;
                D_8023DE40_ovl_286BD0 += 60;
            }
            break;
        case 6:
            if (D_8023DE44_ovl_286BD0 >= 0x37) {
                D_8023DE30_ovl_286BD0[0x245]--;
                D_8023DE44_ovl_286BD0 -= 72;
            }
            break;
        case 7:
            if (D_8023DE44_ovl_286BD0 < 0x37) {
                D_8023DE30_ovl_286BD0[0x245]++;
                D_8023DE44_ovl_286BD0 += 72;
            }
            break;
    }
}

/* Edge scrolling: flags (0x23A) 1/2/4/8 start when the cursor nears the left/right/top/bottom of
 * the view and the grid extends that way; while set, the view follows the cursor's last move
 * and scrolls a cell at a time, stopping when the cursor turns back */
void func_80234078_ovl_286BD0(void) {
    u8 f = D_8023DE30_ovl_286BD0[0x23A];
    s32 sy = D_8023DE30_ovl_286BD0[0x245];
    u32 sx = D_8023DE30_ovl_286BD0[0x244];
    s16 y = FIELD(D_8023DE30_ovl_286BD0, s32, 0x234) - 0x36;
    s16 x = FIELD(D_8023DE30_ovl_286BD0, s32, 0x230) - 0x34;
    s16 top = (sy + 1) * 72;
    s16 right = (sx + 8) * 60;
    s16 bot = (sy + 4) * 72;
    s16 left = (sx + 1) * 60;


    if (x < (s16)left && !(f & 2)) {
        if (D_8023DE30_ovl_286BD0[0x240] < sx) {
            f |= 1;
        }
    } else if ((s16)right < x && !(f & 1)) {
        if (D_8023DE30_ovl_286BD0[0x244] <= D_8023DE30_ovl_286BD0[0x242]) {
            f |= 2;
        }
    }
    if ((s16)top > y && !(f & 8)) {
        if (D_8023DE30_ovl_286BD0[0x245] > D_8023DE30_ovl_286BD0[0x241]) {
            f |= 4;
        }
    } else if ((s16)bot < y && !(f & 4)) {
        if (D_8023DE30_ovl_286BD0[0x245] <= D_8023DE30_ovl_286BD0[0x243]) {
            f |= 8;
        }
    }
    if (f & 1) {
        if (D_8023DE40_ovl_286BD0 >= 0x71) {
            func_80233F38_ovl_286BD0(4);
            if (FIELD(D_8023DE30_ovl_286BD0, s32, 0x1BC) - FIELD(D_8023DE30_ovl_286BD0, s32, 0x1B8) < 0) {
                f &= 0xE;
            }
        } else if (D_8023DE40_ovl_286BD0 < 0x35) {
            if (FIELD(D_8023DE30_ovl_286BD0, s32, 0x1BC) - FIELD(D_8023DE30_ovl_286BD0, s32, 0x1B8) < 0) {
                f &= 0xE;
            }
        }
        if (f & 1) {
            D_8023DE40_ovl_286BD0 += FIELD(D_8023DE30_ovl_286BD0, s32, 0x1BC) - FIELD(D_8023DE30_ovl_286BD0, s32, 0x1B8);
        }
    }
    if (f & 2) {
        if (D_8023DE40_ovl_286BD0 < -7) {
            func_80233F38_ovl_286BD0(5);
            if (FIELD(D_8023DE30_ovl_286BD0, s32, 0x1BC) - FIELD(D_8023DE30_ovl_286BD0, s32, 0x1B8) > 0) {
                f &= 0xD;
            }
        } else if (D_8023DE40_ovl_286BD0 >= 0x35) {
            if (FIELD(D_8023DE30_ovl_286BD0, s32, 0x1BC) - FIELD(D_8023DE30_ovl_286BD0, s32, 0x1B8) > 0) {
                f &= 0xD;
            }
        }
        if (f & 2) {
            D_8023DE40_ovl_286BD0 += FIELD(D_8023DE30_ovl_286BD0, s32, 0x1BC) - FIELD(D_8023DE30_ovl_286BD0, s32, 0x1B8);
        }
    }
    if (f & 4) {
        if (D_8023DE44_ovl_286BD0 >= 0x7F) {
            func_80233F38_ovl_286BD0(6);
            if (FIELD(D_8023DE30_ovl_286BD0, s32, 0x1E4) - FIELD(D_8023DE30_ovl_286BD0, s32, 0x1E0) < 0) {
                f &= 0xB;
            }
        } else if (D_8023DE44_ovl_286BD0 < 0x37) {
            if (FIELD(D_8023DE30_ovl_286BD0, s32, 0x1E4) - FIELD(D_8023DE30_ovl_286BD0, s32, 0x1E0) < 0) {
                f &= 0xB;
            }
        }
        if (f & 4) {
            D_8023DE44_ovl_286BD0 += FIELD(D_8023DE30_ovl_286BD0, s32, 0x1E4) - FIELD(D_8023DE30_ovl_286BD0, s32, 0x1E0);
        }
    }
    if (f & 8) {
        if (D_8023DE44_ovl_286BD0 < -0x11) {
            func_80233F38_ovl_286BD0(7);
            if (FIELD(D_8023DE30_ovl_286BD0, s32, 0x1E4) - FIELD(D_8023DE30_ovl_286BD0, s32, 0x1E0) > 0) {
                f &= 7;
            }
        } else if (D_8023DE44_ovl_286BD0 >= 0x37) {
            if (FIELD(D_8023DE30_ovl_286BD0, s32, 0x1E4) - FIELD(D_8023DE30_ovl_286BD0, s32, 0x1E0) > 0) {
                f &= 7;
            }
        }
        if (f & 8) {
            D_8023DE44_ovl_286BD0 += FIELD(D_8023DE30_ovl_286BD0, s32, 0x1E4) - FIELD(D_8023DE30_ovl_286BD0, s32, 0x1E0);
        }
    }
    D_8023DE30_ovl_286BD0[0x23A] = f;
    if (f) {
        func_80231D58_ovl_286BD0(D_8023DE30_ovl_286BD0[0x244], D_8023DE30_ovl_286BD0[0x245]);
    }
}

extern u8 *D_800C47F0;
extern u16 D_800E79B0;
void func_80234078_ovl_286BD0(void);

/* Moves the grid cursor (0x230/0x234) by 15 per held d-pad direction, or by a third of the analog
 * stick outside its dead zone; clamps it to the visible cells, records it in the trails
 * (0x1B4/0x1DC) and, once it rests, selects the entry under it */
#ifdef NON_MATCHING
/* 247 vs 246: the trail loop ends in bnezl in the original, and the 0x1E0 store is scheduled before bc1t there */
void func_802344D0_ovl_286BD0(void) {
    f32 fy = 0.0f;
    s32 moved = 0;
    f32 fx = 0.0f;
    u8 *pad = D_800C47F0;
    s32 x;
    s32 lim;
    u8 k;
    s32 rest;
    s32 ok;
    u16 *btn;

    if (D_8023DE30_ovl_286BD0 == NULL) {
        return;
    }
    D_8023DE30_ovl_286BD0[0x239]++;
    if ((D_8023DE30_ovl_286BD0[0x239] >> 2) >= 4) {
        D_8023DE30_ovl_286BD0[0x239] = 0;
    }
    if (D_8023DE30_ovl_286BD0[0x23B] == 1) {
        return;
    }
    btn = &D_800E79B0;
    if (*btn & 0x800) {
        moved = 1;
        FIELD(D_8023DE30_ovl_286BD0, s32, 0x234) -= 15;
    }
    if (*btn & 0x400) {
        moved = 1;
        FIELD(D_8023DE30_ovl_286BD0, s32, 0x234) += 15;
    }
    if (*btn & 0x100) {
        moved = 1;
        FIELD(D_8023DE30_ovl_286BD0, s32, 0x230) += 15;
    }
    if (*btn & 0x200) {
        moved = 1;
        FIELD(D_8023DE30_ovl_286BD0, s32, 0x230) -= 15;
    }
    ok = pad != NULL;
    if (ok & (moved ^ 1)) {
        if ((u8)(pad[2] + 4) >= 9) {
            fx = (s8)pad[2] / 3.0f;
        }
        if ((u8)(pad[3] + 4) >= 9) {
            fy = (s8)pad[3] / 3.0f;
        }
        if (fx > 0.0f) {
            FIELD(D_8023DE30_ovl_286BD0, s32, 0x230) += (s16)fx;
        }
        if (fx < 0.0f) {
            FIELD(D_8023DE30_ovl_286BD0, s32, 0x230) += (s16)fx;
        }
        if (fy < 0.0f) {
            FIELD(D_8023DE30_ovl_286BD0, s32, 0x234) -= (s16)fy;
        }
        if (fy > 0.0f) {
            FIELD(D_8023DE30_ovl_286BD0, s32, 0x234) -= (s16)fy;
        }
    }
    x = FIELD(D_8023DE30_ovl_286BD0, s32, 0x230);
    lim = D_8023DE30_ovl_286BD0[0x240] * 60 + 0x34;
    if (lim >= x) {
        FIELD(D_8023DE30_ovl_286BD0, s32, 0x230) = lim;
    } else {
        lim = (D_8023DE30_ovl_286BD0[0x242] + 1) * 60 + 0x34;
        if (lim < x) {
            FIELD(D_8023DE30_ovl_286BD0, s32, 0x230) = lim;
        }
    }
    x = FIELD(D_8023DE30_ovl_286BD0, s32, 0x234);
    lim = D_8023DE30_ovl_286BD0[0x241] * 72 + 0x36;
    if (lim >= x) {
        FIELD(D_8023DE30_ovl_286BD0, s32, 0x234) = lim;
    } else {
        lim = (D_8023DE30_ovl_286BD0[0x243] + 1) * 72 + 0x36;
        if (lim < x) {
            FIELD(D_8023DE30_ovl_286BD0, s32, 0x234) = lim;
        }
    }
    for (k = 7; k != 0; k--) {
        s32 *t = (s32 *)(D_8023DE30_ovl_286BD0 + k * 4);

        t[0x1B4 / 4] = t[0x1B0 / 4];
        t[0x1DC / 4] = t[0x1D8 / 4];
    }
    FIELD(D_8023DE30_ovl_286BD0, s32, 0x1B8) = FIELD(D_8023DE30_ovl_286BD0, s32, 0x230);
    FIELD(D_8023DE30_ovl_286BD0, s32, 0x1E0) = FIELD(D_8023DE30_ovl_286BD0, s32, 0x234);
    rest = 1;
    if (fx != 0.0f) {
        rest = 0;
    }
    if ((moved ^ 1) & rest) {
        if (fy == 0.0f) {
            if ((u8)func_80233DA8_ovl_286BD0(0) && D_8023DE30_ovl_286BD0[0x23C] != 2) {
                D_8023DE30_ovl_286BD0[0x23C] = 1;
            }
            goto end;
        }
    }
    D_8023DE30_ovl_286BD0[0x23C] = 0;
end:
    func_80234078_ovl_286BD0();
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_802344D0_ovl_286BD0);
#endif

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

#include "gbi_ultra.h"
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void func_8022B980_ovl_286BD0(u8 *img, s32 x, s32 y);

/* Draws image img (header: size code at +3, w/h at +4/+6, pixels at +8, 256-colour palette
 * after the pixels) with the CI8 draw state */
void func_8023498C_ovl_286BD0(u8 *img) {
    u16 w = FIELD(img, u16, 4);
    s32 row;
    s32 h;

    if (img[3] == 3) {
        row = ((u32)(w + 3) >> 2) << 4;
    } else if (img[3] == 2) {
        row = ((u32)(w + 3) >> 2) << 3;
    } else if (img[3] == 1) {
        row = ((u32)(w + 7) >> 3) << 3;
    } else {
        row = ((u32)(w + 15) >> 4) << 3;
    }
    h = FIELD(img, u16, 6);
    gSPDisplayList(D_800E9BA0++, D_8023DF48_ovl_286BD0);
    gDPSetPrimColor(D_800E9BA0++, 0, 0, 255, 255, 255, 255);
    gDPLoadTLUT_pal256(D_800E9BA0++, img + (row * h + 8));
    gSPTexture(D_800E9BA0++, 0x8000, 0x8000, 0, 0, G_ON);
    gDPPipeSync(D_800E9BA0++);
    func_8022B980_ovl_286BD0(img, 0, 0);
}

/* Image header: size code at +3, width/height, pixels from +8 (palette after them) */
typedef struct {
    /* 0x0 */ u8 unk0[3];
    /* 0x3 */ u8 siz;
    /* 0x4 */ u16 w;
    /* 0x6 */ u16 h;
} ImgHdr28;

/* Loads icon i (CI4 32x32 at slot 0x214 of the menu state, palette after the pixels) */
#ifdef NON_MATCHING
/* icon load: register naming only */
void func_80234B38_ovl_286BD0(u8 i) {
    ImgHdr28 *img = FIELD(D_8023DE30_ovl_286BD0, ImgHdr28 *, 0x214 + i * 4);
    u8 *pal = (u8 *)img + (((u32)(img->w + 15) >> 4) * 8 * img->h + 8);

    gDPPipeSync(D_800E9BA0++);
    gDPLoadTLUT_pal16(D_800E9BA0++, 0, pal);
    gDPLoadTextureBlock_4b(D_800E9BA0++, (u8 *)img + 8, G_IM_FMT_CI, 32, 32, 0, 0, 0, 5, 5, 0, 0);
    gDPPipeSync(D_800E9BA0++);
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80234B38_ovl_286BD0);
#endif

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

void *func_80071C04(s32 size);
s32 ChunkSize(u32 id);
s32 ReadU32BE(void *p);
void DecodeLZ(void *dst, void *src);

/* Loads text id (LZ, from directory chunk 0x018855FE) and splits it at CR LF into lines (o + 4);
 * lines of pages not yet unlocked (func_8022E8D4, except text 1) are left out; a blank line ends
 * the text. Returns the text with the line count in *count and the page of each line at o + 0x10 */
#ifdef NON_MATCHING
/* 154/147 instructions: control flow as in the original; register use differs (the original reloads o and id from the stack and keeps 0xD/0xA in s-registers) */
char *func_80238A00_ovl_286BD0(s32 id, s16 *count, u8 *o) {
    s8 page[0x100];
    u8 *raw;
    u8 *txt;
    s32 size;
    u32 h;
    s32 i;
    s16 n;
    s8 line;
    u8 *p;

    raw = func_80071C04(ChunkSize(0x018855FE));
    LoadChunkRaw(raw, 0x018855FE);
    h = ((u32 *)raw)[id];
    n = 1;
    size = ChunkSize(h);
    HFree(raw);
    raw = func_80071C04(size);
    LoadChunkRaw(raw, h);
    size = ReadU32BE(raw);
    txt = HMalloc(size);
    DecodeLZ(txt, raw);
    HFree(raw);
    FIELD(o, u8 **, 4) = HMalloc(0x1F40);
    line = 1;
    i = 0;
    FIELD(o, u8 **, 4)[0] = txt;
    page[0] = 0;
    for (p = txt; i < size; i++, p++) {
        if (p[0] == '\r') {
            if (p[1] == '\n' && p[2] == '\r' && p[3] == '\n') {
                p[0] = 0;
                page[n] = line;
                break;
            }
            if (p[0] == '\r' && p[1] == '\n') {
                p[0] = 0;
                if (!(u8)func_8022E8D4_ovl_286BD0(line - 1) && id != 1) {
                    FIELD(o, u8 **, 4)[n] = NULL;
                } else {
                    FIELD(o, u8 **, 4)[n] = txt + i + 2;
                    page[n++] = line;
                }
                line++;
            }
        }
    }
    *count = n;
    FIELD(o, u8 *, 0x10) = HMalloc(n + 2);
    func_80080998(FIELD(o, u8 *, 0x10), page, n);
    return txt;
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80238A00_ovl_286BD0);
#endif

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

/* Loads paragraph para (paragraphs end in a blank line) of text chunk id into a new 0x500-byte
 * buffer, marking its line breaks with 0x81 0x97; w's line table (0x4, new) gets each line's
 * start and *nlines the line count. Returns the buffer */
#ifdef NON_MATCHING
/* 108/108, 26 words: register allocation only (n/start/dst/src/w get different saved registers) */
u8 *func_80238D14_ovl_286BD0(s32 id, s32 para, s16 *nlines, u8 *w) {
    s16 n;
    s32 start;
    s32 k;
    u8 *src;
    u8 *dst;
    s32 i;

    src = func_80227A18(0x018855FE, id);
    n = 1;
    start = 0;
    k = 0;
    FIELD(w, u8 **, 4) = HMalloc(0x1F40);
    dst = HMalloc(0x500);
    bzero(dst, 0x500);
    FIELD(w, u8 **, 4)[0] = dst;
    for (i = 0; i <= 0x0FFFFFFE; i++) {
        if (src[i + 0] == '\r' && src[i + 1] == '\n' && src[i + 2] == '\r' && src[i + 3] == '\n') {
            k++;
            if (para == k) {
                start = i + 4;
            } else {
                if (para + 1 == k) {
                    func_80080998(dst, src + start, i - start);
                    *nlines = n;
                    goto done;
                }
            }
            i += 3;
        } else if (src[i + 0] == '\r' && src[i + 1] == '\n') {
            if (para == k) {
                src[i + 0] = 0x81;
                src[i + 1] = 0x97;
                FIELD(w, u8 **, 4)[n] = dst + (i - (start - 2));
                n++;
            }
            i++;
        }
    }
    *nlines = n;
done:
    HFree(src);
    return dst;
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80238D14_ovl_286BD0);
#endif

extern u16 gPlayTime;
extern u8 D_80196A2A;
extern u8 D_80196A2B;
extern char *D_8023E0B0_ovl_286BD0[10];
extern char *D_8023E0D8_ovl_286BD0;

void func_8009C620(void *dst, void *src);

/* Writes the play time into p as "HH:MM:SS" (digits from the D_8023E0B0 strings), capped at
 * 99:59:59 */
void func_80238EC4_ovl_286BD0(void *p) {
    s32 h;
    s32 m;
    s32 s;

    if (gPlayTime >= 100) {
        h = 99;
        m = 59;
        s = 59;
    } else {
        h = gPlayTime;
        m = D_80196A2A;
        s = D_80196A2B;
    }
    *(u8 *)p = 0;
    func_8009C550(p, D_8023E0B0_ovl_286BD0[h / 10]);
    func_8009C620(p, D_8023E0B0_ovl_286BD0[h % 10]);
    func_8009C620(p, D_8023E0D8_ovl_286BD0);
    func_8009C620(p, D_8023E0B0_ovl_286BD0[m / 10]);
    func_8009C620(p, D_8023E0B0_ovl_286BD0[m % 10]);
    func_8009C620(p, D_8023E0D8_ovl_286BD0);
    func_8009C620(p, D_8023E0B0_ovl_286BD0[s / 10]);
    func_8009C620(p, D_8023E0B0_ovl_286BD0[s % 10]);
}

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

/* Index of the first entry of group n (a new year or month starts a group); past the end the
 * group count */
static inline s32 GroupFirst(s32 n) {
    s32 k = 0;
    u8 lastB = 0;
    u16 lastH = 0;
    s32 i;
    TimeStamp *e;

    for (i = 0; i < 121; i++) {
        e = func_8022EC34_ovl_286BD0(i);
        if (e == NULL) {
            break;
        }
        if (lastH != e->hi) {
            lastH = e->hi;
            lastB = e->mid;
            k++;
        } else if (lastB != e->mid) {
            k++;
            lastB = e->mid;
        }
        if (n == k - 1) {
            return i;
        }
    }
    return k;
}

extern char *D_8023E060_ovl_286BD0[];
extern char D_8023E304_ovl_286BD0[];
extern char D_8023E320_ovl_286BD0[];
s32 sprintf(char *buf, const char *fmt, ...);
void func_8009C550(char *dst, char *src);

/* Fills window w with up to five headings (month and year changes) starting at group a: text
 * goes to src's buffer (0x8), line pointers to its list (0x4); returns the line count */
#ifdef NON_MATCHING
/* 145 vs 141: the group start is sign-extended once up front and the month/year trackers need no masking in the original */
s16 func_80239160_ovl_286BD0(u8 *w, s32 a, u8 *src) {
    u16 lastH = 0;
    u8 lastB = 1;
    s32 off = 0;
    u8 *text = FIELD(src, u8 *, 8);
    s16 start;
    s32 j;
    s16 n;
    u8 *p;
    TimeStamp *e;

    bzero(text, 0x500);
    bzero(w, 0x500);
    start = GroupFirst(a);
    j = 0;
    if (start > 0) {
        lastH = func_8022EC34_ovl_286BD0(start - 1)->hi;
        j = 0;
    }
    n = 0;
    p = w;
    do {
        char buf[0x64];

        bzero(buf, 0x64);
        e = func_8022EC34_ovl_286BD0(start + j);
        if (e == NULL) {
            break;
        }
        if (lastH != e->hi) {
            lastB = e->mid;
            lastH = e->hi;
            sprintf(buf, D_8023E304_ovl_286BD0, D_8023E060_ovl_286BD0[lastB], lastB, lastH);
        } else if (lastB != e->mid) {
            sprintf(buf, D_8023E320_ovl_286BD0, D_8023E060_ovl_286BD0[e->mid], e->mid);
            lastB = e->mid;
        } else {
            goto next;
        }
        FIELD(src, u8 **, 4)[n++] = text + off;
        FIELD(p, u8 *, 0x530) = w + off;
        func_8009C550((char *)(text + off), buf);
        off += strlen(buf) + 2;
        p += 4;
    next:
        j++;
    } while (n < 5);
    func_80080998(w, text, off);
    return n;
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80239160_ovl_286BD0);
#endif

extern char D_8023E0A0_ovl_286BD0[];
extern char D_8023E338_ovl_286BD0[];
s32 sprintf(char *buf, const char *fmt, ...);
void func_8009C550(char *dst, char *src);

/* Writes the heading of group n (its first entry's year) into text window buffer w */
u8 *func_80239394_ovl_286BD0(u8 *w, s32 n) {
    char buf[0x64];
    TimeStamp *e;

    bzero(w, 0x500);
    e = func_8022EC34_ovl_286BD0(GroupFirst(n));
    bzero(buf, 0x64);
    sprintf(buf, D_8023E338_ovl_286BD0, D_8023E0A0_ovl_286BD0, e->hi);
    FIELD(w, u8 *, 0x530) = w;
    func_8009C550((char *)w, buf);
    return w;
}

/* Item index shown on display line `line` (a new group or subgroup adds an extra line);
 * past the end returns the line count */
inline s16 func_802394A0_ovl_286BD0(s32 line) {
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
            lastH = *(u16 *)(e + 2);
            if (line == k) {
                return i;
            }
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

extern char D_8023E378_ovl_286BD0[];

/* Writes the full date of the entry on list line `line` into text window buffer w */
u8 *func_80239B14_ovl_286BD0(u8 *w, s32 line) {
    char buf[0x64];
    TimeStamp *e;

    bzero(w, 0x500);
    e = func_8022EC34_ovl_286BD0(func_802394A0_ovl_286BD0(line));
    bzero(buf, 0x64);
    sprintf(buf, D_8023E378_ovl_286BD0, D_8023E0A0_ovl_286BD0, e->hi, D_8023E060_ovl_286BD0[e->mid], e->lo);
    FIELD(w, u8 *, 0x530) = w;
    func_8009C550((char *)w, buf);
    return w;
}

extern char D_8023E378_ovl_286BD0[];   /* date line format */
extern char D_8023E38C_ovl_286BD0[];   /* indent format */
extern char D_8023E394_ovl_286BD0[];   /* name format */
extern char D_8023E0A0_ovl_286BD0[];
extern char *D_8023E060_ovl_286BD0[];  /* month names */
s32 sprintf(char *buf, const char *fmt, ...);
void func_8009C550(char *dst, char *src);

/* Entry index shown on list line n (a date line precedes each change of date) */
static inline s32 ListEntry28(s32 n) {
    TimeStamp *e;
    s32 line = 0;
    u8 mid = 0;
    u16 hi = 0;
    s32 i;

    for (i = 0; i < 121; i++) {
        e = func_8022EC34_ovl_286BD0(i);
        if (e == NULL) {
            return line;
        }
        if (hi != e->hi) {
            mid = e->mid;
            hi = e->hi;
            if (n == line) {
                return i;
            }
            line++;
        } else if (mid != e->mid) {
            if (n == line) {
                return i;
            }
            line++;
            mid = e->mid;
        }
        if (n == line) {
            return i;
        }
        line++;
    }
    return line;
}

/* Builds the two text lines (date, then the name centred in 0xF2 pixels) of list line n, where a
 * line is inserted before each entry whose date differs from the previous one */
#ifdef NON_MATCHING
/* 114/117 instructions: the original keeps the date-change exits (one shared stub) apart from the per-entry exit, where this gcc merges all three */
char *func_80239C5C_ovl_286BD0(char *buf, s32 n) {
    char tmp[100];
    TimeStamp *e;
    s32 len;
    s32 pad;

    e = func_8022EC34_ovl_286BD0(ListEntry28(n));
    bzero(buf, 0x500);
    bzero(tmp, 100);
    sprintf(tmp, D_8023E378_ovl_286BD0, D_8023E0A0_ovl_286BD0, e->hi, D_8023E060_ovl_286BD0[e->mid], e->lo);
    FIELD(buf, char *, 0x530) = buf;
    func_8009C550(buf, tmp);
    len = strlen(buf) + 1;
    bzero(tmp, 100);
    pad = (0xF2 - func_801794C8((char *)D_8023DE34_ovl_286BD0 + 0x24)) / 2;
    if (pad > 0) {
        sprintf(tmp, D_8023E38C_ovl_286BD0, pad);
    }
    sprintf(tmp + strlen(tmp), D_8023E394_ovl_286BD0, (char *)D_8023DE34_ovl_286BD0 + 0x24);
    FIELD(buf, char *, 0x534) = buf + len;
    func_8009C550(buf + len, tmp);
    return buf;
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_80239C5C_ovl_286BD0);
#endif

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

s32 func_8022ECBC_ovl_286BD0();
/* Opens o's text window with paragraph n of message 0x018855FE (paragraphs are separated by
 * "\r\n\r\n"), n coming from the selected entry's id; mode is kept at 0x600 */
u8 *func_8023A42C_ovl_286BD0(u8 *o, s32 mode) {
    u8 buf[0x500];
    u8 *bp;
    u8 *t;
    u8 *e;
    u16 n;
    u8 *msg;
    s32 start;
    s32 k;
    s32 i;

    {
        u8 *w = HMalloc(0x604);

        FIELD(o, u8 *, 0xD0) = w;
        bzero(w, 0x604);
    }
    bzero(buf, 0x500);
    t = FIELD(o, u8 *, 0xD0);
    t[0x5F3] = 0x3F;
    t[0x5F6] = 0x11;
    t[0x5F0] = 0;
    t[0x5FE] = 2;
    {
        u8 *d = D_8023DE30_ovl_286BD0;

        FIELD(t, s32, 0x600) = mode;
        e = ((u8 **)d)[d[0x23D]];
    }
    bp = buf;
    start = 0;
    n = func_8022ECBC_ovl_286BD0(e[0x2D]) & 0xFF;
    msg = func_80227A18(0x018855FE, 2);
    k = 0;
    for (i = 0; i < 0x0FFFFFFF; i++) {
        if (msg[i] == '\r' && msg[i + 1] == '\n' && msg[i + 2] == '\r' && msg[i + 3] == '\n') {
            k++;
            if (n == k) {
                s32 len = i - start;

                bzero(bp, len + 2);
                func_80080998(bp, msg + start, len);
                break;
            }
            start = i + 4;
        }
    }
    HFree(msg);
    _bcopy((s32 *)buf, t, 0x500);
    o[0x25] = 1;
    t[0x5F4] = 1;
    t[0x5F5] = func_80239EE0_ovl_286BD0(1, t, FIELD(e, s16, 0x2C));
    return t;
}

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023A5D8_ovl_286BD0);

INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023A814_ovl_286BD0);

/* Allocates o's 0x604-byte text window (0x500 bytes of text copied from src) for window kind */
u8 *func_8023AA70_ovl_286BD0(u8 *o, s32 kind, u8 *src) {
    u8 *p;

    *(u8 **)(o + 0xD0) = HMalloc(0x604);
    bzero(*(u8 **)(o + 0xD0), 0x604);
    p = *(u8 **)(o + 0xD0);
    p[0x5F3] = 0x3F;
    p[0x5F6] = 0xF;
    *(s32 *)(p + 0x600) = kind;
    p[0x5F0] = 0;
    p[0x5FE] = 2;
    bzero(p, 0x500);
    func_80080998(p, src, 0x500);
    o[0x25] = 0;
    switch ((u32)(kind & 0xFF)) {
        case 13:
            p[0x5F4] = 1;
            break;
        case 12:
        case 18:
            p[0x5F4] = 7;
            break;
    }
    ((u8 *)D_8023DE34_ovl_286BD0)[0x64] = 0;
    p[0x5F5] = func_80239EE0_ovl_286BD0(0, p, 0);
    return p;
}

s16 func_80239160_ovl_286BD0(u8 *w, s32 a, u8 *src);
void func_802397B8_ovl_286BD0(u8 *w, s32 a, u8 *src);

/* Gives window o its text block for page kind k (6: built list, 11: copied table with 7 line
 * pointers, 16: second list) */
#ifdef NON_MATCHING
/* 102 vs 103 instructions: the original keeps the loop bound 7 in a register (slt), and stores 0x600 right after loading the window */
u8 *func_8023AB74_ovl_286BD0(u8 *o, u32 k, u8 *src) {
    u8 *w;
    u32 kind;

    FIELD(o, u8 *, 0xD0) = HMalloc(0x604);
    bzero(FIELD(o, u8 *, 0xD0), 0x604);
    w = FIELD(o, u8 *, 0xD0);
    FIELD(w, s32, 0x600) = k;
    kind = k & 0xFF;
    w[0x5F0] = 6;
    w[0x5F3] = 20;
    w[0x5F6] = 17;
    w[0x5FE] = 2;
    w[0x5FD] = kind;
    switch (kind) {
    case 6:
        FIELD(src, void *, 8) = HMalloc(0x500);
        FIELD(src, void *, 4) = HMalloc(0x1F40);
        w[0x5F4] = 5;
        func_80239160_ovl_286BD0(w, 0, src);
        break;
    case 11: {
        u8 *t;
        s32 i;

        w[0x5F4] = 7;
        t = *FIELD(src, u8 **, 4);
        bzero(w, 0x500);
        func_80080998(w, t, 0x500);
        for (i = 0; i < 7; i++) {
            ((u8 **)(w + 0x530))[i] = w + (FIELD(src, s32 *, 4)[i] - FIELD(src, s32 *, 4)[0]);
        }
        break;
    }
    case 16:
        w[0x5F4] = 8;
        func_802397B8_ovl_286BD0(w, 0, src);
        w[0x5FC] = 1;
        break;
    }
    o[0x25] = 5;
    w[0x5F5] = 5;
    w[0x5F2] = 48;
    return w;
}
#else
INCLUDE_ASM("asm/nonmatchings/28A7B0", func_8023AB74_ovl_286BD0);
#endif

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
