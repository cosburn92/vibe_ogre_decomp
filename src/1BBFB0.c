#include "common.h"

typedef struct { u8 b[0x76]; } ScriptObj;   /* 4 x 0x76 at D_8022A2E8 */
typedef struct { s32 used; u8 b[0x58]; } ScriptRes; /* 4 x 0x5C at D_8022A4E0 */
typedef struct { u8 b; u8 pad[31]; } Rec32;

extern ScriptObj D_8022A2E8_ovl_1BA050[];
extern ScriptRes D_8022A4E0_ovl_1BA050[];
extern Rec32 D_8022A6A1_ovl_1BA050[];
extern s16 D_8022A718_ovl_1BA050;
extern s16 D_8022A71A_ovl_1BA050;
extern s16 D_8022A71C_ovl_1BA050;
extern s16 D_8022A71E_ovl_1BA050;
void bzero(void *p, s32 size);
void *func_8017F334(u16 id);
void func_8017C2FC(void *p);
void func_80225058_ovl_1BA050(s32 a, s32 b);
void func_802261D0_ovl_1BA050(s32 a, s32 b);





ScriptObj *func_80222EA0_ovl_1BA050(s32 i) {
    ScriptObj *o = &D_8022A2E8_ovl_1BA050[i];

    bzero(o, sizeof(ScriptObj));
    return o;
}

ScriptObj *func_80222EEC_ovl_1BA050(s32 i) {
    return &D_8022A2E8_ovl_1BA050[i];
}

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
void func_80224AAC_ovl_1BA050();
void func_80180B1C(u8 *n, s16 x0, s16 y0, s16 x1, s16 y1);
s32 func_801794C8(void *text);
void func_802284B4_ovl_1BA050();
void func_80228BF0_ovl_1BA050(s32 id);
void func_8017C4B4(s16 id);
void func_80224E74_ovl_1BA050(s16 x0, s16 y0, s16 x1, s16 y1);
void func_80179034(void *s, s32 x, s32 y);
extern u8 D_8022A1D8_ovl_1BA050[];
s32 func_8017B550(u8 c);
extern u8 D_8022A0A8_ovl_1BA050;
extern u8 D_8022A0A4_ovl_1BA050;
extern u8 D_8022A09D_ovl_1BA050;
extern u8 D_8022A09C_ovl_1BA050;
extern u8 D_8022A099_ovl_1BA050;
extern u8 D_8022A098_ovl_1BA050;
typedef struct {
    /* 0x00 */ s32 used;
    /* 0x04 */ void *text;
    /* 0x08 */ u8 flags;
    /* 0x09 */ u8 state;
    /* 0x0A */ s16 hA;
    /* 0x0C */ s16 hC;
    /* 0x0E */ u16 hE;
    /* 0x10 */ u16 h10;
    /* 0x12 */ u16 h12;
    /* 0x14 */ u16 h14;
    /* 0x16 */ s16 h16;
    /* 0x18 */ s16 h18;
    /* 0x1A */ s16 h1A;
    /* 0x1C */ s16 h1C;
    /* 0x1E */ u8 unk1E[2];
} Rec698; /* size 0x20 */
extern Rec698 D_8022A698_ovl_1BA050[];
extern u16 D_8022A4D8_ovl_1BA050;
extern u16 D_8022A4DA_ovl_1BA050;
extern u16 D_8022A4DC_ovl_1BA050;
extern u16 D_8022A4DE_ovl_1BA050;
extern u16 D_800E79B0;
extern u16 D_800E9BE4;
extern void *D_8022A4C0_ovl_1BA050[];
extern u8 *D_8022A650_ovl_1BA050;
extern s32 D_8022A838_ovl_1BA050;
extern u8 D_8022A820_ovl_1BA050;
extern u8 D_80229F9C_ovl_1BA050[];
extern u8 D_8022A834_ovl_1BA050;
extern s16 D_8022A832_ovl_1BA050;
void HFree(void *p);
void func_80220F64_ovl_1BA050(u16 a, u8 b);
u8 *func_8017C074(u16 a, u8 b, void *fn, s16 c, s16 d, s16 e, s16 f);
void func_80229BD4_ovl_1BA050(void);
s32 func_8016FBE0(u8 a, u8 b, void *out);
typedef void (*ScriptObjFn)(ScriptObj *o);
extern ScriptObjFn D_8022A020_ovl_1BA050[];
extern void *D_8022A260_ovl_1BA050[];
extern void *D_8022A654_ovl_1BA050;
extern u8 D_8022A658_ovl_1BA050[];
void *HMalloc(s32 size);
void *LoadChunk(s32 id);
void _bcopy(void *src, void *dst, s32 n);
typedef struct {
    u32 w0;
    u32 w1;
} GfxBB;
extern GfxBB *D_800E9BA0;
extern u8 D_80229FB8_ovl_1BA050[];
extern ScriptObjFn D_80229FA4_ovl_1BA050[];
extern s32 D_8022A720_ovl_1BA050;
extern s16 D_8022A724_ovl_1BA050;
extern s16 D_8022A726_ovl_1BA050;
extern s16 D_8022A728_ovl_1BA050;
extern s16 D_8022A72A_ovl_1BA050;
void func_80227234_ovl_1BA050(u8 *p);
void func_80226E8C_ovl_1BA050(ScriptRes *r);
void func_802292DC_ovl_1BA050(s16 *p);
s32 ChunkSize(s32 id);
void *LoadChunkRaw(void *dst, s32 id);
void *func_8017BFB0(u16 kind, u8 b, void (*fn)(), s16 x, s16 y, s16 w, s16 h, s16 x2, s16 y2, s16 w2, s16 h2);
void func_80229B98_ovl_1BA050();
extern u8 D_8022A821_ovl_1BA050;
extern u8 D_8022A824_ovl_1BA050;
extern s16 D_8022A826_ovl_1BA050;
extern u8 D_8022A833_ovl_1BA050;
extern u8 D_8022A0D0_ovl_1BA050[];
void func_802296B0_ovl_1BA050();
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80222F10_ovl_1BA050);

/* Per-frame update: cycles the blink phase (0x72-0x74), advances each bit slot's fade counter,
 * and moves the position (2, 4) from (6, 8) toward (0xA, 0xC) over 0xE frames */
#ifdef NON_MATCHING
static inline s16 Lerp1BB(s16 from, s16 to, u16 t, u16 dur) {
    s32 d = to - from;

    if ((u32)(d + 1) < 3) {
        return to;
    }
    return from + d * t / dur;
}

/* Close: the slot loop pointer starts at o+0x12 instead of o, and the two lerps differ in register allocation and branch layout (the original copies to/from into separate registers, which suggests an inlined helper). */
void func_8022402C_ovl_1BA050(u8 *o) {
    u8 lim = D_80229F9C_ovl_1BA050[o[0x72]];
    u8 c = ++o[0x73];
    u8 *e;

    if (c <= lim) {
        o[0x74] = 0;
    } else if (c >= lim + 0x11) {
        o[0x73] = 0;
        o[0x74] = 0;
        if (++o[0x72] >= 3) {
            o[0x72] = 0;
        }
    } else {
        o[0x74] = c - lim;
    }
    e = o;
    do {
        if (FIELD(e, u16, 0x12) == 0) {
            goto next;
        }
        if (e[0x15] < 8) {
            e[0x14] = 0;
        } else if (e[0x15] < 12) {
            e[0x14] = 2;
        } else if (e[0x15] < 14) {
            e[0x14] = 1;
        }
        if (++e[0x15] >= 16) {
            if (e[0x16] != 0) {
                e[0x15] = 0;
            } else {
                FIELD(e, u16, 0x12) = 0;
            }
        }
    next:
        e += 6;
    } while (e < o + 0x60);
    if (FIELD(o, u16, 0x10) < FIELD(o, u16, 0xE)) {
        FIELD(o, s16, 2) = Lerp1BB(FIELD(o, s16, 6), FIELD(o, s16, 0xA), FIELD(o, u16, 0x10), FIELD(o, u16, 0xE));
        FIELD(o, s16, 4) = Lerp1BB(FIELD(o, s16, 8), FIELD(o, s16, 0xC), FIELD(o, u16, 0x10), FIELD(o, u16, 0xE));
        FIELD(o, u16, 0x10)++;
        FIELD(o, s16, 6) = FIELD(o, s16, 2);
        FIELD(o, s16, 8) = FIELD(o, s16, 4);
    } else {
        FIELD(o, s16, 2) = FIELD(o, s16, 0xA);
        FIELD(o, s16, 4) = FIELD(o, s16, 0xC);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_8022402C_ovl_1BA050);
#endif

/* For each bit in mask: reuse the slot holding that bit, else the first empty one (hangs when full),
 * and set it to (bit, 0, 0, v) */
void func_80224268_ovl_1BA050(u8 *p, u16 mask, u8 v) {
    u16 bit = 1;
    u32 i;
    u8 *q;

    while (mask != 0) {
        if (mask & bit) {
            for (i = 0; i < 16; i++) {
                if (FIELD(p, u16, 0x12 + i * 6) & bit) {
                    break;
                }
            }
            if (i >= 16) {
                for (i = 0; i < 16; i++) {
                    if (FIELD(p, u16, 0x12 + i * 6) == 0) {
                        break;
                    }
                }
                if (i >= 16) {
                    for (;;);
                }
            }
            mask ^= bit;
            q = p + i * 6;
            FIELD(q, u16, 0x12) = bit;
            q[0x14] = 0;
            q[0x15] = 0;
            q[0x16] = v;
        }
        bit <<= 1;
    }
}

void func_80224320_ovl_1BA050(u8 *p, u16 mask) {
    u16 bit = 1;
    u32 i;
    u8 *q;

    while (mask != 0) {
        if (mask & bit) {
            for (i = 0; i < 16; i++) {
                if (FIELD(p, u16, 0x12 + i * 6) & bit) {
                    break;
                }
            }
            if (i < 16) {
                mask ^= bit;
                q = p + i * 6;
                FIELD(q, u16, 0x12) = 0;
                q[0x14] = 0;
                q[0x15] = 0;
                q[0x16] = 0;
            }
        }
        bit <<= 1;
    }
}

typedef GfxBB Gfx;
#include "gbi_ultra.h"

/* Draws 16x16 window piece `piece` (CI4 image D_8022A260[piece]) at (x, y), clipped at 0 */
void func_802243A0_ovl_1BA050(s32 piece, s32 x, s32 y) {
    gDPLoadTextureBlock_4b(D_800E9BA0++, D_8022A260_ovl_1BA050[piece], G_IM_FMT_CI, 16, 16, 0, 2, 2, 4, 4, 0, 0);
    gDPPipeSync(D_800E9BA0++);
    gSPScisTextureRectangle(D_800E9BA0++, x * 4, y * 4, (x + 16) * 4, (y + 16) * 4, 0, 0, 0, 1 << 10, 1 << 10);
    gDPPipeSync(D_800E9BA0++);
}

extern u8 D_80229FA0_ovl_1BA050[];
void func_802243A0_ovl_1BA050(s32 piece, s32 x, s32 y);

/* Draws window o's four 16x16 corner pieces with its palette and alpha (o+0x1D) */
void func_802245EC_ovl_1BA050(u8 *o) {
    {
        GfxBB *_g = D_800E9BA0++;

        _g->w0 = 0xFCFF97FF;
        _g->w1 = 0xFF2CFE7F;
    }
    gDPSetTextureLUT(D_800E9BA0++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(D_800E9BA0++, 0, D_8022A260_ovl_1BA050[D_80229FA0_ovl_1BA050[o[0x19]]]);
    gDPSetPrimColor(D_800E9BA0++, 0, 0, 255, 255, 255, o[0x1D]);
    func_802243A0_ovl_1BA050(0x1C, FIELD(o, s16, 0x1E), FIELD(o, s16, 0x20));
    func_802243A0_ovl_1BA050(0x1D, FIELD(o, s16, 0x22) - 16, FIELD(o, s16, 0x20));
    func_802243A0_ovl_1BA050(0x1E, FIELD(o, s16, 0x1E), FIELD(o, s16, 0x24) - 16);
    func_802243A0_ovl_1BA050(0x1F, FIELD(o, s16, 0x22) - 16, FIELD(o, s16, 0x24) - 16);
}

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_8022478C_ovl_1BA050);

void func_80224A88_ovl_1BA050(void) {
    bzero(D_8022A2E8_ovl_1BA050, 4 * sizeof(ScriptObj));
}

void func_80224AAC_ovl_1BA050(void) {
    GfxBB *g;
    s32 i;
    ScriptObjFn fn;

    g = D_800E9BA0++;
    g->w0 = 0xDE000000;
    g->w1 = (u32)D_80229FB8_ovl_1BA050;
    for (i = 0; i < 4; i++) {
        fn = D_80229FA4_ovl_1BA050[D_8022A2E8_ovl_1BA050[i].b[0]];
        if (fn != NULL) {
            fn(&D_8022A2E8_ovl_1BA050[i]);
        }
    }
}

/* Runs each active script object's type handler */
void func_80224B5C_ovl_1BA050(void) {
    s32 i;
    ScriptObjFn fn;

    for (i = 0; i < 4; i++) {
        if (D_8022A2E8_ovl_1BA050[i].b[0] != 0) {
            fn = D_8022A020_ovl_1BA050[D_8022A2E8_ovl_1BA050[i].b[0]];
            if (fn != NULL) {
                fn(&D_8022A2E8_ovl_1BA050[i]);
            }
        }
    }
}

void func_80224BE8_ovl_1BA050(void) {
    void *o = func_8017F334(0x5100);
    s32 i;
    s32 n;

    if (o != NULL) {
        func_8017C2FC(o);
    }
    n = 34;
    for (i = 0; i < n; i++) {
        if (D_8022A260_ovl_1BA050[i] != NULL) {
            HFree(D_8022A260_ovl_1BA050[i]);
            D_8022A260_ovl_1BA050[i] = NULL;
        }
    }
}

/* Loads the 34 chunks named by table chunk 0x21BFEDC and starts the script object */
void func_80224C60_ovl_1BA050(void) {
    s32 n;
    s32 *tbl;
    s32 i;

    bzero(D_8022A260_ovl_1BA050, 0x88);
    bzero(D_8022A2E8_ovl_1BA050, 0x10);
    i = ChunkSize(0x21BFEDC);
    n = 34;
    if (i / 4 != n) {
        for (;;);
    }
    tbl = LoadChunkRaw(NULL, 0x21BFEDC);
    for (i = 0; i < n; i++) {
        D_8022A260_ovl_1BA050[i] = LoadChunkRaw(NULL, tbl[i]);
    }
    HFree(tbl);
    func_8017C074(0x5100, 0x13, func_80224AAC_ovl_1BA050, 0, 0, 0, 0);
}

/* Loads the six event resource chunks listed in chunk 0x21C2F70 */
void func_80224D60_ovl_1BA050(void) {
    s32 n = 6;
    s32 *tbl;
    s32 i;

    i = ChunkSize(0x21C2F70);
    if (i / 4 != n) {
        for (;;) {
        }
    }
    tbl = LoadChunkRaw(NULL, 0x21C2F70);
    for (i = 0; i < n; i++) {
        D_8022A4C0_ovl_1BA050[i] = LoadChunkRaw(NULL, tbl[i]);
    }
    HFree(tbl);
}

void func_80224E1C_ovl_1BA050(void) {
    s32 i;
    s32 n = 6;

    for (i = 0; i < n; i++) {
        HFree(D_8022A4C0_ovl_1BA050[i]);
        D_8022A4C0_ovl_1BA050[i] = NULL;
    }
}

/* Scissor to (x0, y0)-(x1, y1), clamped to the 320x240 screen, between two pipe syncs */
#ifdef NON_MATCHING
/* scissor: structure right, display-list pointer scheduling differs */
void func_80224E74_ovl_1BA050(s16 x0, s16 y0, s16 x1, s16 y1) {
    u32 w;

    if (x0 < 0) {
        x0 = 0;
    } else if (x0 > 320) {
        x0 = 320;
    }
    if (y0 < 0) {
        y0 = 0;
    } else if (y0 > 240) {
        y0 = 240;
    }
    if (x1 < 0) {
        x1 = 0;
    } else if (x1 > 320) {
        x1 = 320;
    }
    if (y1 < 0) {
        y1 = 0;
    } else if (y1 > 240) {
        y1 = 240;
    }
    {
        GfxBB *_g = D_800E9BA0++;

        _g->w0 = 0xE7000000;
        _g->w1 = 0;
    }
    {
        GfxBB *g = D_800E9BA0++;

        w = 0xED000000;
        if (x0 >= 0) {
            w = (((s32)(x0 * 4.0f) & 0xFFF) << 12) | 0xED000000;
        }
        g->w0 = w;
        if (y0 >= 0) {
            g->w0 = w | ((s32)(y0 * 4.0f) & 0xFFF);
        }
        if (x1 == 320) {
            w = 0x4FC000;
        } else {
            w = ((s32)(x1 * 4.0f) & 0xFFF) << 12;
        }
        if (y1 == 240) {
            g->w1 = w | 0x3BC;
        } else {
            g->w1 = w | ((s32)(y1 * 4.0f) & 0xFFF);
        }
    }
    {
        GfxBB *_g = D_800E9BA0++;

        _g->w0 = 0xE7000000;
        _g->w1 = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80224E74_ovl_1BA050);
#endif

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80225058_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80225DFC_ovl_1BA050);

ScriptRes *func_80226164_ovl_1BA050(u32 i) {
    if (i >= 4) {
        for (;;) {
        }
    }
    return &D_8022A4E0_ovl_1BA050[i];
}

s32 func_80226198_ovl_1BA050(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_8022A4E0_ovl_1BA050[i].used != 0) {
            return 1;
        }
    }
    return 0;
}

extern u8 D_8022A068_ovl_1BA050[];
extern void *D_8022A090_ovl_1BA050[];
void func_801818A0(s32 x, s32 y, ScriptRes *r);

extern ScriptRes D_8022A534_ovl_1BA050[]; /* = &D_8022A4E0[0].b[0x50] (owner window) */
/* Draws message window w (callback arg0): its two caption lines, then (when not closing) the
 * choice cursor of the script slot that owns the window */
#ifdef NON_MATCHING
/* message window draw: sign-extend of y scheduled late in the original */
void func_802261D0_ovl_1BA050(s32 arg0, s32 arg1) {
    u8 *w = (u8 *)arg0;
    u32 i;
    s32 j;
    u16 y;
    ScriptRes *r;
    ScriptRes *p;

    gSPDisplayList(D_800E9BA0++, D_8022A068_ovl_1BA050);
    gDPSetPrimColor(D_800E9BA0++, 0, 0, 0, 0, 0, w[0x19]);
    y = FIELD(w, u16, 0x32);
    for (i = 0; i < 2; i++, y += 0x14) {
        func_80179034(D_8022A090_ovl_1BA050[i], FIELD(w, s32, 0x2C) + 0x14, (s16)y);
    }
    r = NULL;
    if (FIELD(w, u16, 0x26) == 0) {
        for (j = 0, p = D_8022A4E0_ovl_1BA050; j < 4; p++, j++) {
            if (D_8022A4E0_ovl_1BA050[j].used != 0 && D_8022A534_ovl_1BA050[j].used == (s32)w) {
                r = p;
                break;
            }
        }
        func_801818A0(FIELD(w, s32, 0x2C), FIELD(w, s32, 0x30) + (s8)r->b[0x54] * 0x14 + 4, r);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_802261D0_ovl_1BA050);
#endif

#ifdef NON_MATCHING
/* original copies x/y through extra temps (t2/t1/t4); b/fn assigned straight into a1/a2 */
void func_8022630C_ovl_1BA050(u8 id, s32 x, s32 y, u8 alt) {
    s32 x1 = x - 4;
    s32 y1 = y + 4;
    s32 x2 = x - 0x3C;
    s32 y2 = y + 0x28;
    s32 x3 = x;
    s32 y3 = y;
    s32 x4 = x;
    u8 b;
    void (*fn)();

    if (alt) {
        b = 3;
        fn = func_80229B98_ovl_1BA050;
    } else {
        b = 0;
        fn = func_802261D0_ovl_1BA050;
    }
    func_8017BFB0(id | 0x5300, b, fn, x, y, x1, y1, x2, y3, x4, y2);
}
#else
INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_8022630C_ovl_1BA050);
#endif

/* Pad edge detection: pressed = held & ~previous, for both controllers */
void func_802263CC_ovl_1BA050(void) {
    u16 pa = D_8022A4DC_ovl_1BA050;
    u16 a = D_800E79B0;
    u16 pb = D_8022A4DE_ovl_1BA050;
    u16 b = D_800E9BE4;

    D_8022A4D8_ovl_1BA050 = a & ~pa;
    D_8022A4DC_ovl_1BA050 = a;
    D_8022A4DA_ovl_1BA050 = b & ~pb;
    D_8022A4DE_ovl_1BA050 = b;
}

s32 func_80226420_ovl_1BA050(u8 *p) {
    return p[0xD] == 5;
}

void func_80226430_ovl_1BA050(u8 *p, s32 a) {
    u32 i;

    FIELD(p, s32, 0x18) = a;
    FIELD(p, s32, 0x1C) = 0;
    p[0x11] = 0;
    FIELD(p, s32, 0x38) = 0;
    p[0x22] = 0;
    for (i = 0; i < 4; i++) {
        FIELD(p, s32, 0x24 + i * 4) = 0;
    }
    p[0x41] = 0;
    p[0x40] = 0;
    if (p[0xD] != 0 && p[0xD] < 17) {
        p[0xD] = 1;
    }
}

/* How well code c matches the current one: 4 if all four bytes match, 2 for a valid code,
 * otherwise 1 plus the length up to the terminator when it starts with the alternate lead byte */
s32 func_8022648C_ovl_1BA050(u8 *c) {
    s32 n;
    s32 i;
    u8 buf[16]; /* unused, but the original frame has room for it */

    if (c[0] == 0) {
        return 0;
    }
    if (func_8017B550(c[0])) {
        n = 2;
        if (c[0] == D_8022A098_ovl_1BA050 && c[1] == D_8022A099_ovl_1BA050 && c[2] == D_8022A09C_ovl_1BA050 &&
            c[3] == D_8022A09D_ovl_1BA050) {
            n = 4;
        }
        return n;
    }
    n = 1;
    if (c[0] == D_8022A0A4_ovl_1BA050) {
        for (i = 1; c[i] != D_8022A0A8_ovl_1BA050; i++) {
            n++;
        }
        n++;
    }
    return n;
}

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80226564_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80226A1C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80226E8C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80227234_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_8022750C_ovl_1BA050);

/* Unlinks script resource i from the active list and frees its buffers */
void func_80227E00_ovl_1BA050(s32 i) {
    u8 *r;

    if (i >= 4) {
        for (;;) {
        }
    }
    r = (u8 *)&D_8022A4E0_ovl_1BA050[i];
    if (*(u8 **)(r + 4) != NULL) {
        *(u8 **)(*(u8 **)(r + 4) + 8) = *(u8 **)(r + 8);
    } else {
        D_8022A650_ovl_1BA050 = *(u8 **)(r + 8);
    }
    if (*(u8 **)(r + 8) != NULL) {
        *(u8 **)(*(u8 **)(r + 8) + 4) = *(u8 **)(r + 4);
    }
    if (*(void **)(r + 0x34) != NULL) {
        HFree(*(void **)(r + 0x34));
        *(void **)(r + 0x34) = NULL;
    }
    if (*(void **)(r + 0x4C) != NULL) {
        HFree(*(void **)(r + 0x4C));
        *(void **)(r + 0x4C) = NULL;
    }
    *(s32 *)r = 0;
}

void func_80227EB8_ovl_1BA050(u8 *p, s32 a, s32 b, s32 c) {
    p[0xF] |= c;
    FIELD(p, s32, 0x4C) = func_8016FBE0(a, b, p + 0x50);
    FIELD(p, u16, 0x46) = 2;
    FIELD(p, u16, 0x14) = 2;
    FIELD(p, u16, 0x48) = 2;
    FIELD(p, u16, 0x20) = FIELD(p, u16, 0x46) + 0x2C;
}

void func_80227F14_ovl_1BA050(u32 i, s32 v) {
    if (i >= 4) {
        for (;;) {
        }
    }
    D_8022A4E0_ovl_1BA050[i].b[10] = v;
    func_80220F64_ovl_1BA050(i | 0x5200, v);
}

/* Unlinks script resource slot i and frees its buffers */
static inline void ScriptResFree(s32 i) {
    ScriptRes *e;

    if (i >= 4) {
        for (;;);
    }
    e = &D_8022A4E0_ovl_1BA050[i];
    if (FIELD(e, u8 *, 4) != NULL) {
        FIELD(FIELD(e, u8 *, 4), u8 *, 8) = FIELD(e, u8 *, 8);
    } else {
        D_8022A650_ovl_1BA050 = FIELD(e, u8 *, 8);
    }
    if (FIELD(e, u8 *, 8) != NULL) {
        FIELD(FIELD(e, u8 *, 8), u8 *, 4) = FIELD(e, u8 *, 4);
    }
    if (FIELD(e, void *, 0x34) != NULL) {
        HFree(FIELD(e, void *, 0x34));
        FIELD(e, void *, 0x34) = NULL;
    }
    if (FIELD(e, void *, 0x4C) != NULL) {
        HFree(FIELD(e, void *, 0x4C));
        FIELD(e, void *, 0x4C) = NULL;
    }
    e->used = 0;
}

/* Releases script resource slot i unless object 0x5200 | i still exists; returns whether it did */
s32 func_80227F68_ovl_1BA050(s32 i) {
    void *o = func_8017F334(i | 0x5200);

    if (o == NULL) {
        ScriptResFree(i);
    }
    return o == NULL;
}

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_80228048_ovl_1BA050);

void func_802282D0_ovl_1BA050(void) {
    u8 *n = D_8022A650_ovl_1BA050;
    u8 *last = NULL;
    s32 i;

    if (n != NULL) {
        while (*(u8 **)(n + 8) != NULL) {
            n = *(u8 **)(n + 8);
        }
        last = n;
    }
    if (last != NULL) {
        func_80227234_ovl_1BA050(last);
    }
    for (i = 0; i < 4; i++) {
        if (D_8022A4E0_ovl_1BA050[i].used != 0) {
            func_80226E8C_ovl_1BA050(&D_8022A4E0_ovl_1BA050[i]);
        }
    }
}

/* Deletes the objects of all four script resource slots and releases the slots */
void func_80228378_ovl_1BA050(void) {
    s32 i;
    void *o;

    for (i = 0; i < 4; i++) {
        o = func_8017F334(i | 0x5200);
        if (o != NULL) {
            func_8017C2FC(o);
        }
        ScriptResFree(i);
    }
}

void func_8022845C_ovl_1BA050(void) {
    bzero(D_8022A4E0_ovl_1BA050, 0x170);
    D_8022A650_ovl_1BA050 = 0;
    D_8022A4DE_ovl_1BA050 = 0;
    D_8022A4DC_ovl_1BA050 = 0;
    D_8022A4DA_ovl_1BA050 = 0;
    D_8022A4D8_ovl_1BA050 = 0;
    D_8022A838_ovl_1BA050 = -1;
}

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_802284B4_ovl_1BA050);

static inline Rec698 *Rec698Find(s32 id) {
    Rec698 *r = NULL;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_8022A698_ovl_1BA050[i].used != 0 && D_8022A698_ovl_1BA050[i].used == id) {
            r = &D_8022A698_ovl_1BA050[i];
            break;
        }
    }
    return r;
}

/* Redraws the frame and text of the window record for id (hangs if there is none) */
void func_80228BF0_ovl_1BA050(s32 id) {
    Rec698 *r = Rec698Find(id);
    u16 x;

    if (r == NULL) {
        for (;;);
    }
    func_8017C4B4(FIELD(r, s16, 0x16));
    x = FIELD(r, u16, 0xA) - FIELD(r, u16, 0x10) / 2;
    func_80224E74_ovl_1BA050(x, FIELD(r, u16, 0xC) - 11, x + FIELD(r, u16, 0x10), FIELD(r, u16, 0xC) + 10);
    func_80179034(D_8022A1D8_ovl_1BA050, 0, 0);
    func_80179034(FIELD(r, void *, 4), FIELD(r, s16, 0xA) - FIELD(r, u16, 0xE) / 2 + 8, FIELD(r, s16, 0xC) - 8);
}

/* Window open/close animation over 10 frames (states 1 and 2), then updates the frames of framed
 * windows */
void func_80228CE4_ovl_1BA050(void) {
    s32 i;
    Rec698 *r;
    u8 *n;
    s32 st;

    for (i = 0; i < 4; i++) {
        r = &D_8022A698_ovl_1BA050[i];
        if (r->used == 0) {
            continue;
        }
        st = r->state;
        if (st != 0) {
            if (st < 3) {
                if (++r->h1C >= 10) {
                    r->h1C = 10;
                    r->h10 = r->h14;
                    r->h16 = r->h1A;
                    if (r->state == 1) {
                        r->state = 0;
                    } else {
                        r->state = 3;
                    }
                } else {
                    r->h10 = r->h12 + (r->h14 - r->h12) * r->h1C / 10;
                    r->h16 = r->h18 + (r->h1A - r->h18) * r->h1C / 10;
                }
            }
        }
        if (!(r->flags & 2)) {
            continue;
        }
        n = (u8 *)r->used;
        FIELD(n, s32, 0x2C) = r->hA - r->h10 / 2;
        FIELD(n, s32, 0x30) = r->hC - 11;
        FIELD(n, s32, 0x34) = FIELD(n, s32, 0x2C) + r->h10;
        FIELD(n, s32, 0x38) = FIELD(n, s32, 0x30) + 0x15;
        func_80180B1C(n, FIELD(n, s16, 0x2E), FIELD(n, s16, 0x32), FIELD(n, s16, 0x36), FIELD(n, s32, 0x38));
    }
}

void func_80228E88_ovl_1BA050(s32 i) {
    void *o;

    if (i >= 4) {
        for (;;) {
        }
    }
    o = func_8017F334(i | 0x5400);
    if (o != NULL) {
        func_8017C2FC(o);
    }
    D_8022A698_ovl_1BA050[i].used = 0;
}

void func_80228EE4_ovl_1BA050(void) {
    s32 i;
    void *o;

    for (i = 0; i < 4; i++) {
        o = func_8017F334(i | 0x5400);
        if (o != NULL) {
            func_8017C2FC(o);
        }
        D_8022A698_ovl_1BA050[i].used = 0;
    }
    HFree(D_8022A654_ovl_1BA050);
}

void func_80228F54_ovl_1BA050(void) {
    u8 *p;

    bzero(D_8022A698_ovl_1BA050, 0x80);
    D_8022A654_ovl_1BA050 = HMalloc(0x2D0);
    p = LoadChunk(0x1DC873E);
    _bcopy(p + 0x3E28, D_8022A654_ovl_1BA050, 0x2D0);
    HFree(p);
    p = LoadChunk(0x1DCB92C);
    _bcopy(p + 0x520, D_8022A658_ovl_1BA050, 0x20);
    HFree(p);
}

void func_80228FE8_ovl_1BA050(s32 i) {
    Rec698 *r;

    if (i >= 4) {
        for (;;) {
        }
    }
    r = &D_8022A698_ovl_1BA050[i];
    if (r->used == 0) {
        for (;;) {
        }
    }
    r->h14 = 0;
    r->h1A = 0;
    r->h1C = 0;
    r->state = 2;
    r->h12 = r->h10;
    r->h18 = r->h16;
}

s32 func_80229040_ovl_1BA050(s32 i) {
    return D_8022A6A1_ovl_1BA050[i].b == 3;
}

/* Text record i, cleared; hangs if i is out of range or the record is in use */
static inline Rec698 *Rec698_Take(s32 i) {
    Rec698 *r;

    if (i >= 4) {
        for (;;);
    }
    r = &D_8022A698_ovl_1BA050[i];
    if (r->used != 0) {
        for (;;);
    }
    bzero(r, 0x20);
    return r;
}

/* Opens window record i for text at (x, y); flag 1 = vertical layout, 2 = framed (redraws via
 * func_80228BF0) instead of animated (func_802284B4) */
Rec698 *func_8022905C_ovl_1BA050(s32 i, void *text, s32 x, s32 y, u8 flags) {
    Rec698 *r;
    u8 *n;
    u16 w;
    u8 prio;
    void (*fn)();

    r = Rec698_Take(i);
    r->text = text;
    r->hA = x;
    r->hC = y;
    r->hE = func_801794C8(r->text) + 0x10;
    r->flags = flags;
    if (flags & 1) {
        w = r->hE;
        r->h14 = w;
        if (!(flags & 2)) {
            r->h14 = w - 0x10;
        }
        r->h1A = 0xFF;
        r->state = 1;
    } else {
        w = r->hE;
        r->h10 = w;
        if (!(flags & 2)) {
            r->h10 = w - 0x10;
        }
        r->h16 = 0xFF;
        r->state = 0;
    }
    if (flags & 2) {
        prio = 0;
        fn = func_80228BF0_ovl_1BA050;
    } else {
        fn = func_802284B4_ovl_1BA050;
        prio = 3;
    }
    n = func_8017C074(i | 0x5400, prio, fn, 0, 0, 0, 0);
    r->used = (s32)n;
    FIELD(n, s16, 0x26) = 0;
    return r;
}

inline void func_802291BC_ovl_1BA050(s16 a, s16 b, s16 c, s16 d) {
    D_8022A718_ovl_1BA050 = a;
    D_8022A71A_ovl_1BA050 = b;
    D_8022A71C_ovl_1BA050 = c;
    D_8022A71E_ovl_1BA050 = d;
}

typedef struct {
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
} Rect1BB;

/* Splits rectangle a minus rectangle b into up to four rectangles in out; returns how many */
s32 func_802291E0_ovl_1BA050(Rect1BB *a, Rect1BB *b, Rect1BB *out) {
    s32 n = 0;

    if (a->x0 < b->x0) {
        out[0].x0 = a->x0;
        out[0].x1 = b->x0;
        out[0].y0 = a->y0;
        out[0].y1 = a->y1;
        n = 1;
    }
    if (b->x1 < a->x1) {
        out[n].x0 = b->x1;
        out[n].x1 = a->x1;
        out[n].y0 = a->y0;
        out[n].y1 = a->y1;
        n++;
    }
    if (b->y0 > a->y0) {
        out[n].x0 = b->x0;
        out[n].x1 = b->x1;
        out[n].y0 = a->y0;
        out[n].y1 = b->y0;
        n++;
    }
    if (b->y1 < a->y1) {
        out[n].x0 = b->x0;
        out[n].x1 = b->x1;
        out[n].y0 = b->y1;
        out[n].y1 = a->y1;
        n++;
    }
    return n;
}

INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_802292DC_ovl_1BA050);

inline void func_80229604_ovl_1BA050(s16 *list) {
    if (list == NULL) {
        s32 *p = &D_8022A720_ovl_1BA050;

        bzero(p, 0xF4);
        *p = 1;
        D_8022A72A_ovl_1BA050 = 0xF0;
        D_8022A726_ovl_1BA050 = 0;
        D_8022A724_ovl_1BA050 = 0;
        D_8022A728_ovl_1BA050 = 0x140;
    } else {
        s16 *q = list;

        while (q[1] != 0 || q[3] != 0 || q[0] != 0 || q[2] != 0) {
            func_802292DC_ovl_1BA050(q);
            q += 4;
        }
    }
}

extern u8 D_8022A827_ovl_1BA050;

#define RECTS1BB ((s16 (*)[4])&D_8022A724_ovl_1BA050)
/* Draws the D_8022A720 solid rectangles (x0, y0, x1, y1 at D_8022A724) with alpha D_8022A827 */
#ifdef NON_MATCHING
/* rect list draw: original indexes the rect table by byte offset, no pointer strength reduction */
void func_802296B0_ovl_1BA050(void) {
    s32 i;
    s32 *n = &D_8022A720_ovl_1BA050;

    if (D_8022A821_ovl_1BA050 == 0) {
        return;
    }
    gSPDisplayList(D_800E9BA0++, D_8022A0D0_ovl_1BA050);
    gDPSetPrimColor(D_800E9BA0++, 0, 0, 0, 0, 0, D_8022A827_ovl_1BA050);
    for (i = 0; i < *n; i++) {
        gDPPipeSync(D_800E9BA0++);
        gSPTextureRectangle(D_800E9BA0++, RECTS1BB[i][0] * 4, RECTS1BB[i][1] * 4, RECTS1BB[i][2] * 4, RECTS1BB[i][3] * 4, 0, 0, 0, 1 << 10, 1 << 10);
        gDPPipeSync(D_800E9BA0++);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_802296B0_ovl_1BA050);
#endif

/* Second fade: mode 1 raises the level to D_8022A71E, mode 2 lowers it to 0 and stops, over
 * D_8022A824 frames */
void func_80229828_ovl_1BA050(void) {
    if (D_8022A821_ovl_1BA050 == 0) {
        return;
    }
    if (D_8022A821_ovl_1BA050 == 1) {
        D_8022A826_ovl_1BA050 += D_8022A71E_ovl_1BA050 / D_8022A824_ovl_1BA050;
        if (D_8022A826_ovl_1BA050 >= D_8022A71E_ovl_1BA050) {
            D_8022A826_ovl_1BA050 = D_8022A71E_ovl_1BA050;
        }
    } else if (D_8022A821_ovl_1BA050 == 2) {
        D_8022A826_ovl_1BA050 -= D_8022A71E_ovl_1BA050 / D_8022A824_ovl_1BA050;
        if (D_8022A826_ovl_1BA050 < 0) {
            D_8022A826_ovl_1BA050 = 0;
            D_8022A821_ovl_1BA050 = 0;
        }
    }
}

void func_80229930_ovl_1BA050(void) {
    void *o = func_8017F334(0x5500);

    if (o != NULL) {
        func_8017C2FC(o);
    }
}

/* func_80229604(NULL) as inlined here */
static inline void func_8022995C_reset(void) {
    bzero(&D_8022A720_ovl_1BA050, 0xF4);
    D_8022A720_ovl_1BA050 = 1;
    D_8022A72A_ovl_1BA050 = 0xF0;
    D_8022A726_ovl_1BA050 = 0;
    D_8022A724_ovl_1BA050 = 0;
    D_8022A728_ovl_1BA050 = 0x140;
}

#ifdef NON_MATCHING
/* store scheduling: original loads call args after the global stores */
void func_8022995C_ovl_1BA050(void) {
    D_8022A821_ovl_1BA050 = 0;
    func_8022995C_reset();
    D_8022A71E_ovl_1BA050 = 0;
    func_802291BC_ovl_1BA050(0, 0, 0, 0xA0);
    D_8022A826_ovl_1BA050 = 0;
    D_8022A824_ovl_1BA050 = 4;
    func_8017C074(0x5500, 0x13, func_802296B0_ovl_1BA050, 0, 0, 0, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/1BBFB0", func_8022995C_ovl_1BA050);
#endif

/* Fade step: mode 1 raises the level to 255, mode 2 lowers it to 0 and then stops, over
 * D_8022A834 frames */
void func_80229A20_ovl_1BA050(void) {
    if (D_8022A820_ovl_1BA050 == 0) {
        return;
    }
    if (D_8022A820_ovl_1BA050 == 1) {
        D_8022A832_ovl_1BA050 += 255 / D_8022A834_ovl_1BA050;
        if (D_8022A832_ovl_1BA050 >= 0x100) {
            D_8022A832_ovl_1BA050 = 0xFF;
        }
    } else if (D_8022A820_ovl_1BA050 == 2) {
        D_8022A832_ovl_1BA050 -= 255 / D_8022A834_ovl_1BA050;
        if (D_8022A832_ovl_1BA050 < 0) {
            D_8022A832_ovl_1BA050 = 0;
            D_8022A820_ovl_1BA050 = 0;
        }
    }
}

void func_80229B18_ovl_1BA050(void) {
    void *o = func_8017F334(0x5501);

    if (o != NULL) {
        func_8017C2FC(o);
    }
}

void func_80229B44_ovl_1BA050(void) {
    D_8022A820_ovl_1BA050 = 0;
    D_8022A834_ovl_1BA050 = 8;
    D_8022A832_ovl_1BA050 = 0;
    func_8017C074(0x5501, 0x13, func_80229BD4_ovl_1BA050, 0, 0, 0, 0);
}

void func_80229B98_ovl_1BA050(s32 a, s32 b) {
    func_80225058_ovl_1BA050(a, b);
    func_802261D0_ovl_1BA050(a, b);
}

/* Fullscreen fade rectangle with alpha D_8022A833 */
void func_80229BD4_ovl_1BA050(void) {
    GfxBB *g;

    if (D_8022A820_ovl_1BA050) {
        g = D_800E9BA0++;
        g->w0 = 0xDE000000;
        g->w1 = (u32)D_8022A0D0_ovl_1BA050;
        g = D_800E9BA0++;
        g->w0 = 0xFA000000;
        g->w1 = D_8022A833_ovl_1BA050;
        g = D_800E9BA0++;
        g->w0 = 0xE7000000;
        g->w1 = 0;
        g = D_800E9BA0++;
        g->w0 = 0xE45003C0;
        g->w1 = 0;
        g = D_800E9BA0++;
        g->w0 = 0xE1000000;
        g->w1 = 0;
        g = D_800E9BA0++;
        g->w0 = 0xF1000000;
        g->w1 = 0x04000400;
        g = D_800E9BA0++;
        g->w0 = 0xE7000000;
        g->w1 = 0;
    }
}

INCLUDE_RODATA("asm/nonmatchings/1BBFB0", D_8022A1D8_ovl_1BA050);

INCLUDE_RODATA("asm/nonmatchings/1BBFB0", D_8022A1E0_ovl_1BA050);
