#include "common.h"

/* 20-entry cache keyed by id (0 = free), 0xB0 bytes each. */
typedef struct {
    /* 0x00 */ s32 key;
    /* 0x04 */ u8 unk04[0x40];
    /* 0x44 */ void *data;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ u8 unk54[0x4E];
    /* 0xA2 */ u8 bytes[6];
    /* 0xA8 */ u16 halves[4];
} CacheEntry;

extern u8 D_801CEF00_ovl_1F0A30;
extern CacheEntry *D_801D0728_ovl_1F0A30;
extern s32 D_801D06B0_ovl_1F0A30[8];
void *HMalloc(s32 size);
void HFree(void *p);
void bzero(void *p, s32 size);





void func_801C1D90_ovl_1F0A30(void) {
}

void func_801C1D98_ovl_1F0A30(void) {
}

s32 func_801C2178_ovl_1F0A30(void *a, void *b, s32 i, s32 *r);
/* --- end decls --- */

/* Width spanned by the glyph boxes of a text layout (0 if empty) */
s32 func_801C1DA0_ovl_1F0A30(void *a, void *b) {
    s32 r[10];
    s32 i;
    s32 lo = 1000;
    s32 hi = -1000;

    for (i = 0; func_801C2178_ovl_1F0A30(a, b, i, r); i++) {
        if (r[2] < lo) {
            lo = r[2];
        }
        if (hi < r[2] + r[4]) {
            hi = r[2] + r[4];
        }
    }
    {
        s32 d = hi - lo;

        return d < 0 ? 0 : d;
    }
}

/* Height spanned by the glyph boxes of a text layout (0 if empty) */
s32 func_801C1E44_ovl_1F0A30(void *a, void *b) {
    s32 r[10];
    s32 i;
    s32 lo = 1000;
    s32 hi = -1000;

    for (i = 0; func_801C2178_ovl_1F0A30(a, b, i, r); i++) {
        if (r[1] < lo) {
            lo = r[1];
        }
        if (hi < r[1] + r[3]) {
            hi = r[1] + r[3];
        }
    }
    {
        s32 d = hi - lo;

        return d < 0 ? 0 : d;
    }
}

INCLUDE_ASM("asm/nonmatchings/205220", func_801C1EE8_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C1FF4_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C2178_ovl_1F0A30);

u32 func_801C2290_ovl_1F0A30(u32 v) {
    return (v >> 24) | ((v >> 8) & 0xFF00) | ((v & 0xFF00) << 8) | (v << 24);
}

u16 func_801C22B8_ovl_1F0A30(u32 v) {
    return ((v & 0xFF00) >> 8) | ((v & 0xFF) << 8);
}

void func_801C22D0_ovl_1F0A30(u8 bits) {
    D_801CEF00_ovl_1F0A30 |= bits;
}

void func_801C22E8_ovl_1F0A30(u8 bits) {
    D_801CEF00_ovl_1F0A30 &= ~bits;
}

u8 func_801C2304_ovl_1F0A30(void) {
    return D_801CEF00_ovl_1F0A30;
}

void func_801C2310_ovl_1F0A30(void) {
    D_801CEF00_ovl_1F0A30 = 2;
    D_801D0728_ovl_1F0A30 = HMalloc(0xDC0);
    bzero(D_801D0728_ovl_1F0A30, 0xDC0);
}

INCLUDE_ASM("asm/nonmatchings/205220", func_801C234C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C24F8_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C2710_ovl_1F0A30);

INCLUDE_RODATA("asm/nonmatchings/205220", D_801D03A0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C27F8_ovl_1F0A30);

s32 func_801C2C5C_ovl_1F0A30(s32 key) {
    CacheEntry *e = D_801D0728_ovl_1F0A30;
    s32 i = 19;

    do {
        if (e->key != 0 && e->key == key) {
            return e->unk48;
        }
        e++;
    } while (i-- != 0);
    return 0;
}

s32 func_801C2CA0_ovl_1F0A30(s32 key) {
    CacheEntry *e = D_801D0728_ovl_1F0A30;
    s32 i = 19;

    do {
        if (e->key != 0 && e->key == key) {
            return e->unk50;
        }
        e++;
    } while (i-- != 0);
    return 0;
}

void * func_801C2CE4_ovl_1F0A30(s32 key) {
    CacheEntry *e = D_801D0728_ovl_1F0A30;
    s32 i = 19;

    do {
        if (e->key != 0 && e->key == key) {
            return e->data;
        }
        e++;
    } while (i-- != 0);
    return 0;
}

s32 func_801C2D28_ovl_1F0A30(s32 key) {
    CacheEntry *e = D_801D0728_ovl_1F0A30;
    s32 i = 19;

    do {
        if (e->key != 0 && e->key == key) {
            return e->unk4C;
        }
        e++;
    } while (i-- != 0);
    return 0;
}

void func_801C2D6C_ovl_1F0A30(s32 key, void *data) {
    CacheEntry *e = D_801D0728_ovl_1F0A30;
    s32 i = 19;

    do {
        if (e->key != 0 && e->key == key) {
            HFree(e->data);
            e->data = data;
            return;
        }
        e++;
    } while (i-- != 0);
}

void func_801C2DDC_ovl_1F0A30(s32 key, s32 *a, s32 *b, s32 *c, s32 *d) {
    CacheEntry *e = D_801D0728_ovl_1F0A30;
    s32 i = 19;

    do {
        if (e->key != 0 && e->key == key) {
            *a = e->halves[0];
            *b = e->halves[1];
            *c = e->halves[2];
            *d = e->halves[3];
            return;
        }
        e++;
    } while (i-- != 0);
}

void func_801C2E40_ovl_1F0A30(s32 key, u8 *out) {
    CacheEntry *e = D_801D0728_ovl_1F0A30;
    s32 i = 19;

    do {
        if (e->key != 0 && e->key == key) {
            out[0] = e->bytes[0];
            out[1] = e->bytes[1];
            out[2] = e->bytes[2];
            out[3] = e->bytes[3];
            out[4] = e->bytes[4];
            out[5] = e->bytes[5];
            return;
        }
        e++;
    } while (i-- != 0);
}

INCLUDE_ASM("asm/nonmatchings/205220", func_801C2EB0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C33F8_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C3750_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C3D64_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C3F3C_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C41C8_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C45E0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C4778_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C49A0_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C5078_ovl_1F0A30);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C5470_ovl_1F0A30);

void func_801C58F0_ovl_1F0A30(void) {
    D_801D06B0_ovl_1F0A30[7] = -1;
    D_801D06B0_ovl_1F0A30[6] = -1;
    D_801D06B0_ovl_1F0A30[5] = -1;
    D_801D06B0_ovl_1F0A30[4] = -1;
    D_801D06B0_ovl_1F0A30[3] = -1;
    D_801D06B0_ovl_1F0A30[2] = -1;
    D_801D06B0_ovl_1F0A30[1] = -1;
    D_801D06B0_ovl_1F0A30[0] = -1;
}

INCLUDE_ASM("asm/nonmatchings/205220", SoundRequest);

INCLUDE_ASM("asm/nonmatchings/205220", func_801C5A20_ovl_1F0A30);
