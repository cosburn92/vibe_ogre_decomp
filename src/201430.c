#include "common.h"
#include "tables.h"

extern struct { u8 a; u8 b; } D_801CECF0_ovl_1F0A30[];
extern u8 *D_801D0680_ovl_1F0A30;
extern u8 *D_801D0684_ovl_1F0A30;
extern u8 *D_801D0688_ovl_1F0A30;
extern u8 D_801CEE14_ovl_1F0A30[];
extern u8 *D_801D06A4_ovl_1F0A30;
extern struct { s16 x; s16 y; s16 z; } *D_801D06A8_ovl_1F0A30;
extern void *D_801D06AC_ovl_1F0A30;
extern u8 D_801CEEC0_ovl_1F0A30[][4];
void HFree(void *p);
u32 func_801BE9A8_ovl_1F0A30(s32 siz, u32 w);
void func_801C0F50_ovl_1F0A30(s32 a, s32 b, s32 c, s32 d, s32 e);





char *func_801BDFA0_ovl_1F0A30(u8 i) {
    return gAttackTable[i + 0x37].name;
}

extern u8 (*D_801D068C_ovl_1F0A30)[2];
extern u16 *D_801D0690_ovl_1F0A30;
extern u8 (*D_801D0698_ovl_1F0A30)[2];
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

INCLUDE_ASM("asm/nonmatchings/201430", func_801BE308_ovl_1F0A30);

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

INCLUDE_ASM("asm/nonmatchings/201430", func_801BE478_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BE564_ovl_1F0A30);

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

INCLUDE_ASM("asm/nonmatchings/201430", func_801BE71C_ovl_1F0A30);

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

INCLUDE_ASM("asm/nonmatchings/201430", func_801BEA70_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BEB28_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BEBE4_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BED08_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BEDC8_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BEEA0_ovl_1F0A30);

/* Whether an RGBA5551 colour is nonzero, as 0 / 0xFF */
u8 func_801BEEDC_ovl_1F0A30(u16 c) {
    u32 x = ((c & 0xF800) << 16) | ((c & 0x7C0) << 13) | ((c & 0x3E) << 10) | (c & 1);

    return x ? 0xFF : 0;
}

INCLUDE_ASM("asm/nonmatchings/201430", func_801BEF14_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BF59C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BF858_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BF9B4_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BFBA0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BFE28_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801BFF84_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801C00E0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801C01D4_ovl_1F0A30);

void func_801C0F34_ovl_1F0A30(s32 a, s32 b, s32 c, s32 d) {
    func_801C0F50_ovl_1F0A30(a, b, c, d, 0);
}

INCLUDE_ASM("asm/nonmatchings/201430", func_801C0F50_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/201430", func_801C15E0_ovl_1F0A30);
