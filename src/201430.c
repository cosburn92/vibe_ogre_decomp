#include "common.h"
#include "tables.h"

extern struct { u8 a; u8 b; } D_801CECF0_ovl_1F0A30[];
extern u8 *D_801D0680_ovl_1F0A30;
extern u8 *D_801D0684_ovl_1F0A30;
extern u8 *D_801D0688_ovl_1F0A30;
extern u8 D_80187C59[];
extern u16 *D_801D0694_ovl_1F0A30;
extern u8 D_801CEE14_ovl_1F0A30[];
extern u8 *D_801D06A4_ovl_1F0A30;
extern struct { s16 x; s16 y; s16 z; } *D_801D06A8_ovl_1F0A30;
extern void *D_801D06AC_ovl_1F0A30;
extern u8 D_801CEEC0_ovl_1F0A30[][4];
void HFree(void *p);
u32 func_801BE9A8_ovl_1F0A30(s32 siz, u32 w);
u8 *func_801BFF84_ovl_1F0A30(u8 *desc, u32 page);
void func_801C0F50_ovl_1F0A30(s32 a, s32 b, s32 c, s32 d, s32 e);





char *func_801BDFA0_ovl_1F0A30(u8 i) {
    return gAttackTable[i + 0x37].name;
}

extern u8 (*D_801D068C_ovl_1F0A30)[2];
extern u16 *D_801D0690_ovl_1F0A30;
extern u8 (*D_801D0698_ovl_1F0A30)[2];
typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Rgba201;
extern s16 *D_801D069C_ovl_1F0A30;
/* --- end decls --- */

u8 func_801BDFBC_ovl_1F0A30(u8 a) {
    if ((u8)(a - 17) < 28) {
        return a + 80;
    }
    if ((u8)(a - 146) < 8) {
        return a + 235;
    }
    if ((u8)(a - 55) < 36) {
        return a + 201;
    }
    if ((u8)(a - 91) < 54) {
        return a + 204;
    }
    if ((u8)(a - 154) < 3) {
        return a + 138;
    }
    return 1;
}

u8 func_801BE034_ovl_1F0A30(u8 a) {
    if (a < 36) {
        return a + 55;
    }
    if ((u8)(a - 36) < 3) {
        return a + 118;
    }
    if ((u8)(a - 39) < 54) {
        return a + 52;
    }
    if ((u8)(a - 97) < 28) {
        return a + 176;
    }
    if ((u8)(a - 125) < 8) {
        return a + 21;
    }
    return 1;
}

u8 func_801BE0A8_ovl_1F0A30(u8 i) {
    return D_801CECF0_ovl_1F0A30[i].a;
}

u8 func_801BE0C0_ovl_1F0A30(u8 i) {
    return D_801CECF0_ovl_1F0A30[i].b & 0xF;
}

u8 func_801BE0DC_ovl_1F0A30(u16 i) {
    return D_801D0680_ovl_1F0A30[i];
}

u8 func_801BE0F4_ovl_1F0A30(s32 cls, s32 other) {
    if (gClassTable[cls].baseClass == other) {
        return D_801D0684_ovl_1F0A30[cls];
    }
    return D_801D0684_ovl_1F0A30[other];
}

#ifdef NON_MATCHING
/* index arithmetic order differs (original selects k*4 in each branch) */
u16 func_801BE138_ovl_1F0A30(s32 cls, s32 base, s32 c, s32 d) {
    s32 off;

    if (gClassTable[cls].baseClass == base) {
        off = cls * 4;
    } else {
        off = base * 4;
    }
    return D_801D0690_ovl_1F0A30[c * 2 + off + d] & 0xFFF;
}
#else
INCLUDE_ASM("asm/nonmatchings/201430", func_801BE138_ovl_1F0A30);
#endif

#ifdef NON_MATCHING
/* index arithmetic order differs (original selects k*4 in each branch) */
u16 func_801BE18C_ovl_1F0A30(s32 cls, s32 base, s32 c, s32 d) {
    s32 k;

    if (gClassTable[cls].baseClass == base) {
        k = cls;
    } else {
        k = base;
    }
    return D_801D0690_ovl_1F0A30[c * 2 + k * 4 + d] >> 12;
}
#else
INCLUDE_ASM("asm/nonmatchings/201430", func_801BE18C_ovl_1F0A30);
#endif

f32 func_801BE1E0_ovl_1F0A30(s32 cls, s32 base) {
    if (gClassTable[cls].baseClass == base && D_801D0698_ovl_1F0A30[cls][0] != 0xFF) {
        return D_801D0698_ovl_1F0A30[cls][0] / 16.0f;
    }
    return D_801D0698_ovl_1F0A30[base][0] / 16.0f;
}

f32 func_801BE264_ovl_1F0A30(s32 cls, s32 base) {
    if (gClassTable[cls].baseClass == base && D_801D0698_ovl_1F0A30[cls][1] != 0xFF) {
        return D_801D0698_ovl_1F0A30[cls][1] / 16.0f;
    }
    return D_801D0698_ovl_1F0A30[base][1] / 16.0f;
}

u8 func_801BE2E8_ovl_1F0A30(s32 a, s32 b) {
    return D_801D0688_ovl_1F0A30[a * 3 + b];
}

/* Looks up key in the 4-byte entry list for slot a (if its byte matches b and it has one) or for b;
 * returns byte k + 1 of the entry, or 0x28 when absent */
#ifdef NON_MATCHING
/* The search loop matches. The original keeps the table and entry pointers in t1/t0 (a0/a1 stay live) and branches on tbl[a] != 0xFFFF straight into the loop. */
u8 func_801BE308_ovl_1F0A30(s32 a, s32 b, s32 key, s32 k) {
    u16 *tbl = D_801D0694_ovl_1F0A30;
    u8 *p;
    u8 c;

    if (D_80187C59[a * 0x48] == b && tbl[a] != 0xFFFF) {
        p = (u8 *)tbl + tbl[a];
    } else {
        p = (u8 *)tbl + tbl[b];
    }
    for (; *p != 0xFF; p += 4) {
        if (*p == key) {
            return p[k + 1];
        }
    }
    return 0x28;
}
#else
INCLUDE_ASM("asm/nonmatchings/201430", func_801BE308_ovl_1F0A30);
#endif

u8 func_801BE3A8_ovl_1F0A30(s32 cls, s32 base) {
    if (gClassTable[cls].baseClass == base && D_801D068C_ovl_1F0A30[cls][0] == 0xFF &&
        D_801D068C_ovl_1F0A30[base][0] == 0xFF) {
        return 0;
    }
    return D_801D068C_ovl_1F0A30[base][0];
}

u8 func_801BE410_ovl_1F0A30(s32 cls, s32 base) {
    if (gClassTable[cls].baseClass == base && D_801D068C_ovl_1F0A30[cls][1] == 0xFF &&
        D_801D068C_ovl_1F0A30[base][1] == 0xFF) {
        return 0;
    }
    return D_801D068C_ovl_1F0A30[base][1];
}

/* Row b of table a (11 halfwords each). -1 ends the table; -2 rows carry a full record,
 * others a short one. Copies into out when given and returns the row's first word. */
/* Row b of table a (11 halfwords each). -1 ends the table; -2 rows carry a full record,
 * others a short one. Copies into out when given and returns the row's first word. */
/* Row b of table a (11 halfwords each). -1 ends the table; -2 rows carry a full record,
 * others a short one. Copies into out when given and returns the row's first word. */
/* Row b of table a (11 halfwords each). -1 ends the table; -2 rows carry a full record,
 * others a short one. Copies into out when given and returns the row's first word. */
/* Row b of table a (11 halfwords each). -1 ends the table; -2 rows carry a full record,
 * others a short one. Copies into out when given and returns the row's first word. */
/* Row b of table a (11 halfwords each). -1 ends the table; -2 rows carry a full record,
 * others a short one. Copies into out when given and returns the row's first word. */
/* Row b of table a (11 halfwords each). -1 ends the table; -2 rows carry a full record,
 * others a short one. Copies into out when given and returns the row's first word. */
/* Row b of table a (11 halfwords each). -1 ends the table; -2 rows carry a full record,
 * others a short one. Copies into out when given and returns the row's first word. */
/* Row b of table a (11 halfwords each). -1 ends the table; -2 rows carry a full record,
 * others a short one. Copies into out when given and returns the row's first word. */
/* Row b of table a (11 halfwords each). -1 ends the table; -2 rows carry a full record,
 * others a short one. Copies into out when given and returns the row's first word. */
/* Row b of table a (11 halfwords each). -1 ends the table; -2 rows carry a full record,
 * others a short one. Copies into out when given and returns the row's first word. */
/* Row b of table a (11 halfwords each). -1 ends the table; -2 rows carry a full record,
 * others a short one. Copies into out when given and returns the row's first word. */
/* Row b of table a (11 halfwords each). -1 ends the table; -2 rows carry a full record,
 * others a short one. Copies into out when given and returns the row's first word. */
/* Row b of table a (11 halfwords each). -1 ends the table; -2 rows carry a full record,
 * others a short one. Copies into out when given and returns the row's first word. */
/* Row b of table a (11 halfwords each). -1 ends the table; -2 rows carry a full record,
 * others a short one. Copies into out when given and returns the row's first word. */
/* Row b of table a (11 halfwords each). -1 ends the table; -2 rows carry a full record,
 * others a short one. Copies into out when given and returns the row's first word. */
s16 func_801BE478_ovl_1F0A30(s32 a, s32 b, s16 *out) {
    s16 pad[1];
    s16 *row;
    s16 v;

    row = (s16 *)((u8 *)D_801D069C_ovl_1F0A30 + D_801D069C_ovl_1F0A30[a]);
    row += b * 11;
    v = row[0];

    if (v != -1) {
        if (out == NULL) {
            return v;
        }
        if (v == -2) {
            out[0] = row[1];
            out[1] = row[2];
            out[2] = row[3];
            out[6] = row[4];
            out[7] = row[5];
            out[8] = row[6];
            out[9] = row[7];
            out[10] = row[8];
            out[11] = row[9];
            out[5] = row[10];
        } else {
            out[0] = v;
            out[1] = row[1];
            out[2] = row[2];
            out[3] = row[3];
            out[4] = row[4];
            out[5] = row[5];
            out[7] = 1;
        }
    }
    return row[0];
}

extern s16 *D_801D06A0_ovl_1F0A30;

/* Looks up entry b of group a in the D_801D06A0 table (13 halfwords each). Returns its kind
 * (-1 = none); with out, copies the entry: kind -2 is the twelve-value form */
#ifdef NON_MATCHING
/* 73/73 instructions, 2 words differ: the group address (table + offset) lands in v1 instead of a0 */
s16 func_801BE564_ovl_1F0A30(s32 a, s32 b, s16 *out) {
    s16 *e = (s16 *)((u8 *)D_801D06A0_ovl_1F0A30 + D_801D06A0_ovl_1F0A30[a]) + b * 13;
    s16 kind = e[0];

    if (kind != -1) {
        if (out == NULL) {
            return kind;
        }
        if (kind == -2) {
            out[0] = e[1];
            out[1] = e[2];
            out[2] = e[3];
            out[9] = e[4];
            out[10] = e[5];
            out[11] = e[6];
            out[12] = e[7];
            out[13] = e[8];
            out[14] = e[9];
            out[15] = e[10];
            out[16] = e[11];
            out[17] = e[12];
        } else {
            out[0] = kind;
            out[1] = e[1];
            out[2] = e[2];
            out[4] = e[3];
            if ((u16)e[4] == 0x8000) {
                out[5] = 0;
            } else {
                out[5] = e[4];
            }
            out[6] = e[5];
            out[3] = e[6];
            out[7] = e[7];
            out[8] = e[8];
            out[11] = 1;
        }
    }
    return e[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/201430", func_801BE564_ovl_1F0A30);
#endif

u8 func_801BE688_ovl_1F0A30(u32 i) {
    if (i < 160) {
        return D_801CEE14_ovl_1F0A30[i];
    }
    return 100;
}

u8 func_801BE6A8_ovl_1F0A30(s32 i) {
    return D_801D06A4_ovl_1F0A30[i];
}

s16 func_801BE6BC_ovl_1F0A30(s32 i) {
    return D_801D06A8_ovl_1F0A30[i].x;
}

s16 func_801BE6DC_ovl_1F0A30(s32 i) {
    return D_801D06A8_ovl_1F0A30[i].y;
}

s16 func_801BE6FC_ovl_1F0A30(s32 i) {
    return D_801D06A8_ovl_1F0A30[i].z;
}

extern u8 *D_801D0738_ovl_1F0A30;
extern u8 *D_801D06F4_ovl_1F0A30;
extern u8 *D_801D073C_ovl_1F0A30;
extern u8 *D_801D0830_ovl_1F0A30;
s32 ChunkSize(s32 id);
void *LoadChunkRaw(void *dst, s32 id);
void *func_80071C04(s32 size);
void *HMalloc(s32 size);
void _bcopy(void *src, void *dst, s32 n);
typedef struct {
    u16 off[15];
    u16 size;
} TabHdr201;

/* Loads the class data tables (chunk 0x315736) and points the table globals into the copy */
#ifdef NON_MATCHING
/* 96 vs 94 instructions: the original pairs each offset load with its add through t8 and saves one register fewer; GCC here loads all fifteen offsets first */
void func_801BE71C_ovl_1F0A30(void) {
    TabHdr201 *raw = func_80071C04(ChunkSize(0x315736));
    TabHdr201 *h;

    LoadChunkRaw(raw, 0x315736);
    D_801D06AC_ovl_1F0A30 = HMalloc(raw->size);
    _bcopy(raw, D_801D06AC_ovl_1F0A30, raw->size);
    h = D_801D06AC_ovl_1F0A30;
    D_801D0690_ovl_1F0A30 = (u16 *)((u8 *)h + h->off[0]);
    D_801D0698_ovl_1F0A30 = (void *)((u8 *)h + h->off[1]);
    D_801D0680_ovl_1F0A30 = (u8 *)h + h->off[2];
    D_801D0684_ovl_1F0A30 = (u8 *)h + h->off[3];
    D_801D0688_ovl_1F0A30 = (u8 *)h + h->off[4];
    D_801D0738_ovl_1F0A30 = (u8 *)h + h->off[5];
    D_801D06F4_ovl_1F0A30 = (u8 *)h + h->off[6];
    D_801D0694_ovl_1F0A30 = (u16 *)((u8 *)h + h->off[7]);
    D_801D068C_ovl_1F0A30 = (void *)((u8 *)h + h->off[8]);
    D_801D069C_ovl_1F0A30 = (s16 *)((u8 *)h + h->off[9]);
    D_801D06A0_ovl_1F0A30 = (s16 *)((u8 *)h + h->off[10]);
    D_801D06A4_ovl_1F0A30 = (u8 *)h + h->off[11];
    D_801D06A8_ovl_1F0A30 = (void *)((u8 *)h + h->off[12]);
    D_801D073C_ovl_1F0A30 = (u8 *)h + h->off[13];
    D_801D0830_ovl_1F0A30 = (u8 *)h + h->off[14];
    HFree(raw);
}
#else
INCLUDE_ASM("asm/nonmatchings/201430", func_801BE71C_ovl_1F0A30);
#endif

void func_801BE894_ovl_1F0A30(void) {
    HFree(D_801D06AC_ovl_1F0A30);
    D_801D06AC_ovl_1F0A30 = NULL;
}

u8 func_801BE8C0_ovl_1F0A30(u32 a, u32 b) {
    if (a >= 5 || b >= 4) {
        return 0;
    }
    return D_801CEEC0_ovl_1F0A30[a][b];
}

/* Number of bits needed for n - 1 (1..10) */
s32 func_801BE8FC_ovl_1F0A30(u32 n) {
    if (n < 2) {
        return 1;
    }
    if (n < 5) {
        return 2;
    }
    if (n < 9) {
        return 3;
    }
    if (n < 17) {
        return 4;
    }
    if (n < 33) {
        return 5;
    }
    if (n < 65) {
        return 6;
    }
    if (n < 129) {
        return 7;
    }
    if (n < 257) {
        return 8;
    }
    if (n < 513) {
        return 9;
    }
    return 10;
}

s32 func_801BE978_ovl_1F0A30(s32 a, s32 b, s32 c) {
    return func_801BE9A8_ovl_1F0A30(a, b) * c;
}

/* Texture line size in bytes for pixel size siz (G_IM_SIZ_*) and width w, 8-byte aligned */
#ifdef NON_MATCHING
/* branch layout of the size chain differs */
u32 func_801BE9A8_ovl_1F0A30(s32 siz, u32 w) {
    if (siz == 3) {
        return ((w + 3) >> 2) << 4;
    }
    if (siz == 2) {
        w = (w + 3) >> 2;
    } else if (siz == 1) {
        w = (w + 7) >> 3;
    } else if (siz != 0) {
        w = (w + 31) >> 5;
    } else {
        w = (w + 15) >> 4;
    }
    return w << 3;
}
#else
INCLUDE_ASM("asm/nonmatchings/201430", func_801BE9A8_ovl_1F0A30);
#endif

/* Width rounded up to a whole 64-bit word of texels for pixel size siz */
#ifdef NON_MATCHING
/* branch layout of the size chain differs */
u32 func_801BEA0C_ovl_1F0A30(s32 siz, u32 w) {
    if (siz == 3 || siz == 2) {
        return ((w + 3) >> 2) << 2;
    }
    if (siz == 1) {
        return ((w + 7) >> 3) << 3;
    }
    if (siz != 0) {
        return ((w + 31) >> 5) << 5;
    }
    return ((w + 15) >> 4) << 4;
}
#else
INCLUDE_ASM("asm/nonmatchings/201430", func_801BEA0C_ovl_1F0A30);
#endif

/* Sepia tone of c (alpha kept) */
u32 func_801BEA70_ovl_1F0A30(Rgba201 in) {
    Rgba201 c = in;
    u32 lum = c.r * 30 + c.g * 59 + c.b * 11;

    c.r = lum * 255 / 30000;
    c.g = lum / 150;
    c.b = lum * 130 / 30000;
    return *(u32 *)&c;
}

/* Sepia tone of an RGBA5551 colour */
u16 func_801BEB28_ovl_1F0A30(u16 c) {
    u32 r = (c >> 8) & 0xF8;
    u32 g = (c >> 3) & 0xF8;
    u32 b = (c << 2) & 0xF8;
    u32 lum = r * 30 + g * 59 + b * 11;

    r = lum * 255 / 30000;
    g = lum / 150;
    b = lum * 130 / 30000;
    lum = ((r & 0xF8) << 8) + ((g & 0xF8) << 3) + ((b & 0xF8) >> 2) + (c & 1);
    return lum;
}

typedef struct {
    u8 r, g, b, a;
} Color201;

/* Sepia tone of colour c: grey from 30/59/11 % weights, then tinted 220/180/120 % */
s32 func_801BEBE4_ovl_1F0A30(Color201 c) {
    Color201 out = c;
    s32 grey = ((out.r * 30) / 100 + (out.g * 59) / 100 + (out.b * 11) / 100) / 3;

    out.r = (u32)(grey * 220) / 100;
    out.g = (u32)(grey * 180) / 100;
    out.b = (u32)(grey * 120) / 100;
    return *(s32 *)&out;
}

/* Blue-tinted shade of an RGBA8888 colour by its brightest channel */
/* new r/g registers (a3/t0) swapped */
u32 func_801BED08_ovl_1F0A30(u32 rgba) {
    s32 g = (rgba >> 16) & 0xFF;
    s32 r;
    s32 b = (rgba >> 8) & 0xFF;
    u32 a = rgba & 0xFF;
    s32 max = rgba >> 24;

    if (max < g) {
        max = g;
    }
    if (max < b) {
        max = b;
    }
    if (max < 128) {
        r = max * 112 / 128 + 24;
        g = max * 112 / 128 + 28;
        b = max * 96 / 128 + 8;
    } else {
        r = max * 80 / 128 + 56;
        g = max * 80 / 128 + 60;
        b = max * 80 / 128 + 40;
    }
    r <<= 8;
    return (((u32)r << 16) + ((u32)g << 16) + ((u32)b << 8)) | a;
}

/* RGBA5551 version of the tint above */
#ifdef NON_MATCHING
/* c&1 hoisted early in original; register order differs */
u16 func_801BEDC8_ovl_1F0A30(u16 c) {
    u32 r;
    u32 g = (c >> 3) & 0xF8;
    u32 b = (c << 2) & 0xF8;
    s32 m = (c >> 8) & 0xF8;

    if (m < g) {
        m = g;
    }
    if (m < b) {
        m = b;
    }
    if (m < 0x80) {
        r = m * 112 / 128 + 24;
        g = m * 112 / 128 + 28;
        b = m * 96 / 128 + 8;
    } else {
        r = m * 80 / 128 + 56;
        g = m * 80 / 128 + 60;
        b = m * 80 / 128 + 40;
    }
    return ((r & 0xF8) << 8) + ((g & 0xF8) << 3) + ((b & 0xF8) >> 2) + (c & 1);
}
#else
INCLUDE_ASM("asm/nonmatchings/201430", func_801BEDC8_ovl_1F0A30);
#endif

/* Whether c is at least half opaque */
static inline s32 transp201(Rgba201 c) {
    s32 r = 0;

    if (c.a < 0x80) {
        r = 1;
    }
    return r;
}
#ifdef NON_MATCHING
/* original keeps a dead 0 and returns (0 == 0) on the opaque path */
s32 func_801BEEA0_ovl_1F0A30(Rgba201 in) {
    Rgba201 c = in;

    if (c.a < 0x80) {
        return 0;
    }
    return !transp201(c);
}
#else
INCLUDE_ASM("asm/nonmatchings/201430", func_801BEEA0_ovl_1F0A30);
#endif

/* Whether an RGBA5551 colour is nonzero, as 0 / 0xFF */
u8 func_801BEEDC_ovl_1F0A30(u16 c) {
    u32 x = ((c & 0xF800) << 16) | ((c & 0x7C0) << 13) | ((c & 0x3E) << 10) | (c & 1);

    return x ? 0xFF : 0;
}

INCLUDE_ASM("asm/nonmatchings/201430", func_801BEF14_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BF59C_ovl_1F0A30);

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void func_801BF858_ovl_1F0A30(u16 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u32 arg6, u32 arg7) {
    u32 sp38;
    s16 *var_s2;
    s16 var_a0;
    s32 temp_a0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_v0;
    u16 *var_a1;
    u32 temp_v0;
    u32 var_s0;
    u32 var_s1;
    u32 var_s3;
    u32 var_s6;
    u32 var_t0;
    u32 var_v1;

    var_t0 = arg7;
    var_s6 = 0x10;
    if (arg1 != 0) {
        var_s6 = 0x100;
    }
    var_s0 = 0;
    var_s3 = 0;
    if (var_t0 != 0) {
loop_3:
        var_s1 = 0;
        if (arg6 != 0) {
            var_s2 = (var_s0 * 2) + arg0;
loop_5:
            sp38 = var_t0;
            temp_v0 = func_801BF59C_ovl_1F0A30(arg2, arg3, arg4, arg5, arg6, var_t0, var_s1, var_s3);
            temp_a0 = ((temp_v0 >> 0x10) & 0xF800) | ((temp_v0 >> 0xD) & 0x7C0);
            temp_v1 = (temp_v0 >> 0xA) & 0x3E;
            temp_v0_2 = temp_v0 & 0xFF;
            var_a0 = temp_a0 | temp_v1;
            if (temp_v0_2 != 0) {
                var_a0 |= 1;
            }
            var_v1 = 0;
            if (var_s0 != 0) {
                var_a1 = arg0;
loop_9:
                var_v0 = var_v1 < var_s0;
                if (*var_a1 != (var_a0 & 0xFFFF)) {
                    var_v1 += 1;
                    var_a1 += 2;
                    if (var_v1 >= var_s0) {
                        var_v0 = var_v1 < var_s0;
                    } else {
                        goto loop_9;
                    }
                }
                if (var_v0 == 0) {
                    goto block_13;
                }
                goto block_14;
            }
block_13:
            *var_s2 = var_a0;
            var_s0 += 1;
            var_s2 += 2;
            if (var_s0 < var_s6) {
block_14:
                var_s1 += 1;
                if (var_s1 >= arg6) {
                    goto block_15;
                }
                goto loop_5;
            }
        } else {
block_15:
            var_s3 += 1;
            if (var_s3 < var_t0) {
                goto loop_3;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/201430", func_801BF858_ovl_1F0A30);
#endif

#ifdef NON_MATCHING
/* m2c draft, 99 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void func_801BF9B4_ovl_1F0A30(s32 arg0, u16 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u32 arg8, u32 arg9) {
    u16 *sp2C;
    s32 sp34;
    s32 sp3C;
    s32 sp44;
    s32 sp4C;
    s32 var_v0;
    u16 *var_a1;
    u16 *var_s2;
    u16 var_a0;
    u32 temp_v0;
    u32 var_s0;
    u32 var_s0_2;
    u32 var_s1;
    u32 var_s1_2;
    u32 var_s3;
    u32 var_s7;
    u32 var_v1;

    sp2C = arg1;
    sp34 = arg2;
    sp3C = arg3;
    sp4C = arg0;
    sp44 = arg4;
    if (arg2 == 2) {
        var_s7 = 0x10;
        if (arg3 != 0) {
            var_s7 = 0x100;
        }
        var_s0 = 0;
        var_s3 = 0;
        if (arg9 != 0) {
loop_4:
            var_s1 = 0;
            if (arg8 != 0) {
                var_s2 = &sp2C[var_s0];
loop_6:
                temp_v0 = func_801BF59C_ovl_1F0A30(sp44, arg5, arg6, arg7, arg8, arg9, var_s1, var_s3);
                var_a0 = ((temp_v0 >> 0x10) & 0xF800) | ((temp_v0 >> 0xD) & 0x7C0) | ((temp_v0 >> 0xA) & 0x3E);
                if (temp_v0 & 0xFF) {
                    var_a0 |= 1;
                }
                var_v1 = 0;
                if (var_s0 != 0) {
                    var_a1 = sp2C;
loop_10:
                    var_v0 = var_v1 < var_s0;
                    if (*var_a1 != (var_a0 & 0xFFFF)) {
                        var_v1 += 1;
                        var_a1 += 2;
                        if (var_v1 >= var_s0) {
                            var_v0 = var_v1 < var_s0;
                        } else {
                            goto loop_10;
                        }
                    }
                    if (var_v0 == 0) {
                        goto block_14;
                    }
                    goto block_15;
                }
block_14:
                *var_s2 = var_a0;
                var_s0 += 1;
                var_s2 += 2;
                if (var_s0 < var_s7) {
block_15:
                    var_s1 += 1;
                    if (var_s1 >= arg8) {
                        goto block_16;
                    }
                    goto loop_6;
                }
            } else {
block_16:
                var_s3 += 1;
                if (var_s3 < arg9) {
                    goto loop_4;
                }
            }
        }
    }
    var_s1_2 = 0;
    if (arg9 != 0) {
        do {
            var_s0_2 = 0;
            if (arg8 != 0) {
                do {
                    func_801BEF14_ovl_1F0A30(sp4C, sp2C, sp34, sp3C, arg8, arg9, var_s0_2, var_s1_2, func_801BF59C_ovl_1F0A30(sp44, arg5, arg6, arg7, arg8, arg9, var_s0_2, var_s1_2));
                    var_s0_2 += 1;
                } while (var_s0_2 < arg8);
            }
            var_s1_2 += 1;
        } while (var_s1_2 < arg9);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/201430", func_801BF9B4_ovl_1F0A30);
#endif

INCLUDE_ASM("asm/nonmatchings/201430", func_801BFBA0_ovl_1F0A30);

#ifdef NON_MATCHING
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
/* Bytes per row of a w-pixel texture in format fmt (3: 32-bit, 2: 16-bit, 1: 8-bit, 0: 4-bit,
 * else 1-bit), padded to 8 bytes */
static inline s32 RowBytes201(s32 fmt, u32 w) {
    if (fmt == 3) {
        return ((u32)(w + 3) >> 2) * 16;
    }
    if (fmt == 2) {
        return ((u32)(w + 3) >> 2) * 8;
    }
    if (fmt == 1) {
        return ((u32)(w + 7) >> 3) * 8;
    }
    if (fmt == 0) {
        return ((u32)(w + 15) >> 4) * 8;
    }
    return ((u32)(w + 31) >> 5) * 8;
}

/* 87/87 instructions, 26 words differ: width/stride/row land in s5/s4 instead of s3/s5 and the format copy goes to a1 */
/* Converts a texture's pixels in place (32-bit through func_801BED08, 16-bit through func_801BEDC8) */
void func_801BFE28_ovl_1F0A30(u8 *d) {
    u32 w = FIELD(d, u16, 4);
    u32 h = FIELD(d, u16, 6);
    s32 stride = RowBytes201(d[3], w);
    u32 x;
    u32 y;
    u8 *row;

    if (d[3] == 3) {
        row = d + 8;
        for (y = 0; y < h; y++) {
            u32 *p = (u32 *)row;

            for (x = 0; x < w; x++) {
                *p = func_801BED08_ovl_1F0A30(*p);
                p++;
            }
            row += stride;
        }
    } else if (d[3] == 2) {
        row = d + 8;
        for (y = 0; y < h; y++) {
            u16 *p = (u16 *)row;

            for (x = 0; x < w; x++) {
                *p = func_801BEDC8_ovl_1F0A30(*p);
                p++;
            }
            row += stride;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/201430", func_801BFE28_ovl_1F0A30);
#endif

INCLUDE_ASM("asm/nonmatchings/201430", func_801BFF84_ovl_1F0A30);

/* Palette of page `page` of image bank desc (NULL when the page has none) */
#ifdef NON_MATCHING
/* Three differences remain: the original re-zero-extends h (andi 0xFFFF) before each multiply, picks the second-plane size with a branch rather than xori, and allocates e/w/h as s2/s3/s4. */
u8 *func_801C00E0_ovl_1F0A30(u8 *desc, u32 page) {
    u32 w = *(u16 *)(desc + 4);
    u32 h = *(u16 *)(desc + 6);
    u8 *e = func_801BFF84_ovl_1F0A30(desc, page);
    u32 off;
    s32 siz;

    if (e == NULL) {
        return NULL;
    }
    off = 8;
    if (e[3] & 1) {
        if (desc[3] & 2) {
            siz = 3;
        } else if (desc[3] & 4) {
            siz = 1;
        } else {
            siz = 2;
        }
        off = func_801BE9A8_ovl_1F0A30(siz, w) * (u16)h + 8;
    }
    if (e[3] & 2) {
        off += func_801BE9A8_ovl_1F0A30((desc[3] & 1) ? 0 : 1, w) * (u16)h;
    }
    if (e[3] & 4) {
        return e + off;
    }
    return NULL;
}
#else
INCLUDE_ASM("asm/nonmatchings/201430", func_801C00E0_ovl_1F0A30);
#endif

INCLUDE_ASM("asm/nonmatchings/201430", func_801C01D4_ovl_1F0A30);

void func_801C0F34_ovl_1F0A30(s32 a, s32 b, s32 c, s32 d) {
    func_801C0F50_ovl_1F0A30(a, b, c, d, 0);
}

INCLUDE_ASM("asm/nonmatchings/201430", func_801C0F50_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801C15E0_ovl_1F0A30);
