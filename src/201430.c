#include "common.h"
#include "chunk.h"
#include "heap.h"
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
u32 func_801BE9A8_ovl_1F0A30(s32 siz, u32 w);
u8 *func_801BFF84_ovl_1F0A30(u8 *desc, u32 page);
void *func_801C0F50_ovl_1F0A30(u8 *chunk, s32 v, u8 *pal, u8 *out, s32 mode);





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

u16 func_801BE138_ovl_1F0A30(s32 cls, s32 base, s32 c, s32 d) {
    if (gClassTable[cls].baseClass == base) {
        return D_801D0690_ovl_1F0A30[cls * 4 + c * 2 + d] & 0xFFF;
    }
    return D_801D0690_ovl_1F0A30[base * 4 + c * 2 + d] & 0xFFF;
}

u16 func_801BE18C_ovl_1F0A30(s32 cls, s32 base, s32 c, s32 d) {
    if (gClassTable[cls].baseClass == base) {
        return D_801D0690_ovl_1F0A30[cls * 4 + c * 2 + d] >> 12;
    }
    return D_801D0690_ovl_1F0A30[base * 4 + c * 2 + d] >> 12;
}

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
s16 func_801BE564_ovl_1F0A30(s32 a, s32 b, s16 *out) {
    s16 *e = (s16 *)((u8 *)D_801D06A0_ovl_1F0A30 + D_801D06A0_ovl_1F0A30[a]);
    s16 kind;

    e += b * 13;
    kind = e[0];

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
void _bcopy(void *src, void *dst, s32 n);
typedef struct {
    u16 off[15];
    u16 size;
} TabHdr201;

/* Loads the class data tables (chunk 0x315736) and points the table globals into the copy */
void func_801BE71C_ovl_1F0A30(void) {
    TabHdr201 *raw = func_80071C04(ChunkSize(0x315736));
    u32 o;

    LoadChunkRaw(raw, 0x315736);
    D_801D06AC_ovl_1F0A30 = HMalloc(raw->size);
    _bcopy(raw, D_801D06AC_ovl_1F0A30, raw->size);
    o = ((TabHdr201 *)D_801D06AC_ovl_1F0A30)->off[0];
    D_801D0690_ovl_1F0A30 = (u16 *)((u8 *)((TabHdr201 *)D_801D06AC_ovl_1F0A30) + o);
    o = ((TabHdr201 *)D_801D06AC_ovl_1F0A30)->off[1];
    D_801D0698_ovl_1F0A30 = (void *)((u8 *)((TabHdr201 *)D_801D06AC_ovl_1F0A30) + o);
    o = ((TabHdr201 *)D_801D06AC_ovl_1F0A30)->off[2];
    D_801D0680_ovl_1F0A30 = (u8 *)((u8 *)((TabHdr201 *)D_801D06AC_ovl_1F0A30) + o);
    o = ((TabHdr201 *)D_801D06AC_ovl_1F0A30)->off[3];
    D_801D0684_ovl_1F0A30 = (u8 *)((u8 *)((TabHdr201 *)D_801D06AC_ovl_1F0A30) + o);
    o = ((TabHdr201 *)D_801D06AC_ovl_1F0A30)->off[4];
    D_801D0688_ovl_1F0A30 = (u8 *)((u8 *)((TabHdr201 *)D_801D06AC_ovl_1F0A30) + o);
    o = ((TabHdr201 *)D_801D06AC_ovl_1F0A30)->off[5];
    D_801D0738_ovl_1F0A30 = (u8 *)((u8 *)((TabHdr201 *)D_801D06AC_ovl_1F0A30) + o);
    o = ((TabHdr201 *)D_801D06AC_ovl_1F0A30)->off[6];
    D_801D06F4_ovl_1F0A30 = (u8 *)((u8 *)((TabHdr201 *)D_801D06AC_ovl_1F0A30) + o);
    o = ((TabHdr201 *)D_801D06AC_ovl_1F0A30)->off[7];
    D_801D0694_ovl_1F0A30 = (u16 *)((u8 *)((TabHdr201 *)D_801D06AC_ovl_1F0A30) + o);
    o = ((TabHdr201 *)D_801D06AC_ovl_1F0A30)->off[8];
    D_801D068C_ovl_1F0A30 = (void *)((u8 *)((TabHdr201 *)D_801D06AC_ovl_1F0A30) + o);
    o = ((TabHdr201 *)D_801D06AC_ovl_1F0A30)->off[9];
    D_801D069C_ovl_1F0A30 = (s16 *)((u8 *)((TabHdr201 *)D_801D06AC_ovl_1F0A30) + o);
    o = ((TabHdr201 *)D_801D06AC_ovl_1F0A30)->off[10];
    D_801D06A0_ovl_1F0A30 = (s16 *)((u8 *)((TabHdr201 *)D_801D06AC_ovl_1F0A30) + o);
    o = ((TabHdr201 *)D_801D06AC_ovl_1F0A30)->off[11];
    D_801D06A4_ovl_1F0A30 = (u8 *)((u8 *)((TabHdr201 *)D_801D06AC_ovl_1F0A30) + o);
    o = ((TabHdr201 *)D_801D06AC_ovl_1F0A30)->off[12];
    D_801D06A8_ovl_1F0A30 = (void *)((u8 *)((TabHdr201 *)D_801D06AC_ovl_1F0A30) + o);
    o = ((TabHdr201 *)D_801D06AC_ovl_1F0A30)->off[13];
    D_801D073C_ovl_1F0A30 = (u8 *)((u8 *)((TabHdr201 *)D_801D06AC_ovl_1F0A30) + o);
    o = ((TabHdr201 *)D_801D06AC_ovl_1F0A30)->off[14];
    D_801D0830_ovl_1F0A30 = (u8 *)((u8 *)((TabHdr201 *)D_801D06AC_ovl_1F0A30) + o);
    HFree(raw);
}

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
u32 func_801BE9A8_ovl_1F0A30(s32 siz, u32 w) {
    u32 n;

    if (siz == 3) {
        return ((w + 3) >> 2) << 4;
    }
    if (siz == 2) {
        n = (w + 3) >> 2;
    } else if (siz == 1) {
        n = (w + 7) >> 3;
    } else if (siz != 0) {
        n = (w + 31) >> 5;
    } else {
        n = (w + 15) >> 4;
    }
    return n << 3;
}

/* Width rounded up to a whole 64-bit word of texels for pixel size siz. The 32b and 16b
 * cases are separate (identical) branches: written as siz == 3 || siz == 2 GCC makes a range test. */
u32 func_801BEA0C_ovl_1F0A30(s32 siz, u32 w) {
    u32 n;

    if (siz == 3) {
        n = ((w + 3) >> 2) << 2;
    } else if (siz == 2) {
        n = ((w + 3) >> 2) << 2;
    } else if (siz == 1) {
        n = ((w + 7) >> 3) << 3;
    } else if (siz != 0) {
        n = ((w + 31) >> 5) << 5;
    } else {
        n = ((w + 15) >> 4) << 4;
    }
    return n;
}

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

static inline u32 Rgba5551To8888(u16 c) {
    u32 r = ((c & 0xF800) << 16) | ((c & 0x7C0) << 13) | ((c & 0x3E) << 10);

    if (c & 1) {
        r |= 0xFF;
    }
    return r;
}
/* RGBA8888 colour of texel (x, y) in a w-wide image of format fmt / size siz (palette pal for CI) */
#ifdef NON_MATCHING
/* 1 instruction over: the shared RGBA5551 tail builds the colour in v0 and copies it to r, where the
 * original builds it in r directly */
u32 func_801BF59C_ovl_1F0A30(u8 *img, u8 *pal, u32 fmt, u32 siz, u32 w, u32 h, u32 x, u32 y) {
    u32 off = RowBytes201(siz, w) * y;
    u32 r = 0;
    u32 v;

    switch (fmt) {
        case 0:
            switch (siz) {
                case 2:
                    r = Rgba5551To8888(*(u16 *)(img + (x * 2 + off)));
                    break;
                case 3:
                    r = *(u32 *)(img + (x * 4 + off));
                    break;
            }
            break;
        case 2:
            switch (siz) {
                case 0:
                    v = img[off + x / 2];
                    if (x & 1) {
                        v &= 0xF;
                    } else {
                        v >>= 4;
                    }
                    r = Rgba5551To8888(*(u16 *)(pal + v * 2));
                    break;
                case 1:
                    r = Rgba5551To8888(*(u16 *)(pal + img[off + x] * 2));
                    break;
            }
            break;
        case 3:
            switch (siz) {
                case 0:
                    v = img[off + x / 2];
                    if (x & 1) {
                        v &= 0xF;
                    } else {
                        v >>= 4;
                    }
                    r = (v & 0xE) << 28 | (v & 0xE) << 20 | (v & 0xE) << 12;
                    if (v & 1) {
                        r |= 0xFF;
                    }
                    break;
                case 1:
                    v = img[off + x];
                    r = (v & 0xF0) << 24 | (v & 0xF0) << 16 | (v & 0xF0) << 8 | v << 4;
                    break;
                case 2:
                    v = *(u16 *)(img + (x * 2 + off));
                    r = (v & 0xFF00) << 16 | (v & 0xFF00) << 8 | (v & 0xFF00) | (v & 0xFF);
                    break;
            }
            break;
        case 4:
            switch (siz) {
                case 0:
                    v = img[off + x / 2];
                    if (x & 1) {
                        v &= 0xF;
                    } else {
                        v >>= 4;
                    }
                    r = (v & 0xF) << 28 | (v & 0xF) << 20 | (v & 0xF) << 12 | (v & 0xF) << 4;
                    break;
                case 1:
                    v = img[off + x];
                    r = v << 24 | v << 16 | v << 8 | v;
                    break;
            }
            break;
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/201430", func_801BF59C_ovl_1F0A30);
#endif
u32 func_801BF59C_ovl_1F0A30(u8 *img, u8 *pal, u32 fmt, u32 siz, u32 w, u32 h, u32 x, u32 y);


/* Collects the distinct RGBA5551 colours of a w x h image (sampled through func_801BF59C) into
 * pal, up to 16 colours (256 when big) */
#ifdef NON_MATCHING
/* 87/87, 8 words: a and b swap s7/s8 */
inline void func_801BF858_ovl_1F0A30(u16 *pal, s32 big, s32 a, s32 b, s32 c, s32 d, u32 w, u32 h) {
    u32 max = 16;
    u32 n;
    u32 x;
    u32 y;
    u32 k;

    if (big) {
        max = 256;
    }
    n = 0;
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            u32 rgba = func_801BF59C_ovl_1F0A30(a, b, c, d, w, h, x, y);
            u16 col = ((rgba >> 16) & 0xF800) | ((rgba >> 13) & 0x7C0) | ((rgba >> 10) & 0x3E) | ((rgba & 0xFF) ? 1 : 0);
            for (k = 0; k < n; k++) {
                if (pal[k] == col) {
                    break;
                }
            }
            if (k >= n) {
                pal[n++] = col;
                if (n >= max) {
                    return;
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/201430", func_801BF858_ovl_1F0A30);
#endif

void func_801BEF14_ovl_1F0A30(s32 dst, u16 *pal, s32 fmt, s32 big, u32 w, u32 h, u32 x, u32 y, u32 rgba);

/* Converts a w x h image sampled through func_801BF59C into dst in format fmt (2: colour-indexed,
 * after collecting its palette into pal) */
#ifdef NON_MATCHING
/* 119 vs 123: the original spills dst/pal/fmt/big/a to stack slots and reloads them in the second loop */
void func_801BF9B4_ovl_1F0A30(s32 dst, u16 *pal, s32 fmt, s32 big, s32 a, s32 b, s32 c, s32 d, u32 w, u32 h) {
    u32 x;
    u32 y;

    if (fmt == 2) {
        func_801BF858_ovl_1F0A30(pal, big, a, b, c, d, w, h);
    }
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            func_801BEF14_ovl_1F0A30(dst, pal, fmt, big, w, h, x, y, func_801BF59C_ovl_1F0A30(a, b, c, d, w, h, x, y));
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/201430", func_801BF9B4_ovl_1F0A30);
#endif

/* Inlined copies of func_801BEA70 (taking the colour as a u32) and func_801BEB28 */
static inline u32 SepiaRgba201(u32 in) {
    Rgba201 c = *(Rgba201 *)&in;
    u32 lum = c.r * 30 + c.g * 59 + c.b * 11;

    c.r = lum * 255 / 30000;
    c.g = lum / 150;
    c.b = lum * 130 / 30000;
    return *(u32 *)&c;
}

static inline u16 Sepia5551(u16 c) {
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

/* Sepia-tones texture tex in place (header: size at 3, width at 4, height at 6, texels from 8);
 * only 32-bit and 16-bit textures are changed */
void func_801BFBA0_ovl_1F0A30(u8 *tex) {
    u32 w = *(u16 *)(tex + 4);
    u32 h = *(u16 *)(tex + 6);
    s32 stride = RowBytes201(tex[3], w);
    u8 *row;
    u8 *row2;
    u32 x;
    u32 y;

    if (tex[3] == 3) {
        row = tex + 8;
        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {
                ((u32 *)row)[x] = SepiaRgba201(((u32 *)row)[x]);
            }
            row += stride;
        }
    } else if (tex[3] == 2) {
        row2 = tex + 8;
        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {
                ((u16 *)row2)[x] = Sepia5551(((u16 *)row2)[x]);
            }
            row2 += stride;
        }
    }
}

#ifdef NON_MATCHING
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif

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

/* Entry `page` of texture set desc (8-byte header, then per entry an 8-byte header followed by
 * the colour plane (flag 1), the second plane (flag 2) and a 0x200-byte palette (flag 4)) */
u8 *func_801BFF84_ovl_1F0A30(u8 *desc, u32 page) {
    if (desc != NULL) {
        u8 f = desc[3];
        u32 w = *(u16 *)(desc + 4);
        u32 h = *(u16 *)(desc + 6);
        u32 sz1, sz2;
        u32 off;
        u32 i;
        u8 *e;

        if (f & 2) {
            sz1 = func_801BE9A8_ovl_1F0A30(3, w) * h;
            sz2 = 0;
        } else if (f & 4) {
            sz1 = func_801BE9A8_ovl_1F0A30(1, w) * h;
            if (desc[3] & 1) {
                sz2 = func_801BE9A8_ovl_1F0A30(0, w) * h;
            } else {
                sz2 = func_801BE9A8_ovl_1F0A30(1, w) * h;
            }
        } else {
            sz1 = func_801BE9A8_ovl_1F0A30(2, w) * h;
            if (desc[3] & 1) {
                sz2 = func_801BE9A8_ovl_1F0A30(0, w) * h;
            } else {
                sz2 = func_801BE9A8_ovl_1F0A30(1, w) * h;
            }
        }
        off = 8;
        e = desc + 8;
        for (i = 0; i < desc[2]; i++) {
            if (i == page) {
                return e;
            }
            off += 8;
            if (e[3] & 1) {
                off += sz1;
            }
            if (e[3] & 2) {
                off += sz2;
            }
            if (e[3] & 4) {
                off += 0x200;
            }
            e = desc + off;
        }
    }
    return NULL;
}

/* Bytes of one plane of pixel size siz for a w x h image (h taken as an int and narrowed, which
 * re-zero-extends it before each multiply) */
static inline u32 PlaneBytes(s32 siz, u32 w, s32 h) {
    return func_801BE9A8_ovl_1F0A30(siz, w) * (u16)h;
}

/* Palette of page `page` of image bank desc (NULL when the page has none) */
u8 *func_801C00E0_ovl_1F0A30(u8 *desc, u32 page) {
    u16 w = *(u16 *)(desc + 4);
    u16 h = *(u16 *)(desc + 6);
    u8 *e = func_801BFF84_ovl_1F0A30(desc, page);
    u32 off;

    if (e == NULL) {
        return NULL;
    }
    off = 8;
    if (e[3] & 1) {
        if (desc[3] & 2) {
            off = PlaneBytes(3, w, h) + 8;
        } else if (desc[3] & 4) {
            off = PlaneBytes(1, w, h) + 8;
        } else {
            off = PlaneBytes(2, w, h) + 8;
        }
    }
    if (e[3] & 2) {
        if (desc[3] & 1) {
            off += PlaneBytes(0, w, h);
        } else {
            off += PlaneBytes(1, w, h);
        }
    }
    if (e[3] & 4) {
        return e + off;
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/201430", func_801C01D4_ovl_1F0A30);

void func_801C0F34_ovl_1F0A30(s32 a, s32 b, s32 c, s32 d) {
    func_801C0F50_ovl_1F0A30((u8 *)a, b, (u8 *)c, (u8 *)d, 0);
}

INCLUDE_ASM("asm/nonmatchings/201430", func_801C0F50_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801C15E0_ovl_1F0A30);
