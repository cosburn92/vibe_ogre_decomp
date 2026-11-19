#include "common.h"

/* 1B7630 */

u8 *func_80219F40_ovl_1B2670(u8 *t, u32 page);
typedef struct {
    /* 0x00 */ u16 sec0;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u16 sec1;
    /* 0x06 */ u8 unk06[0x10];
    /* 0x16 */ u16 size;
} TblHdr;
extern TblHdr *D_8021C9E8_ovl_1B2670;
extern u8 *D_8021C9E0_ovl_1B2670;
extern u8 *D_8021C9E4_ovl_1B2670;
s32 ChunkSize(s32 id);
void *LoadChunkRaw(void *dst, s32 id);
void *HMalloc(s32 size);
void HFree(void *p);
void bzero(void *p, s32 n);
void _bcopy(const void *src, void *dst, s32 n);
void *func_8021B5EC_ovl_1B2670(s32 a, s32 b, s32 c, s32 d, s32 e);
/* --- end decls --- */

/* Page `page` of image bank t (pages are 8-byte headers followed by pixels, sub-image and palette as flagged) */
u8 *func_80219F40_ovl_1B2670(u8 *t, u32 page) {
    u32 w;
    s32 h;
    u32 pix;
    u32 sub;
    u32 off;
    u32 i;
    u8 *e;
    u8 f;
    u8 g;

    if (t == NULL) {
        return NULL;
    }
    f = t[3];
    w = *(u16 *)(t + 4);
    h = *(u16 *)(t + 6);
    if (f & 2) {
        pix = ((w + 3) >> 2 << 4) * h;
        sub = 0;
    } else if (f & 4) {
        pix = ((w + 7) >> 3 << 3) * h;
        if (f & 1) {
            sub = ((w + 15) >> 4 << 3) * h;
        } else {
            sub = pix;
        }
    } else {
        pix = ((w + 3) >> 2 << 3) * h;
        if (f & 1) {
            sub = ((w + 15) >> 4 << 3) * h;
        } else {
            sub = ((w + 7) >> 3 << 3) * h;
        }
    }
    off = 8;
    e = t + 8;
    for (i = 0; i < t[2]; i++) {
        if (i == page) {
            return e;
        }
        g = e[3];
        off += 8;
        if (g & 1) {
            off += pix;
        }
        if (g & 2) {
            off += sub;
        }
        if (g & 4) {
            off += 0x200;
        }
        e = t + off;
    }
    return NULL;
}

/* Palette that follows the pixel data of image t's page (NULL if the page has none) */
u8 *func_8021A064_ovl_1B2670(u8 *t, u32 page) {
    u8 *e = func_80219F40_ovl_1B2670(t, page);
    u16 w;
    s32 h;
    s32 stride;

    if (e == NULL) {
        return NULL;
    }
    w = *(u16 *)(t + 4);
    h = *(u16 *)(t + 6);
    if (e[3] & 2) {
        if (!(e[3] & 1)) {
            return e + 8;
        }
        if (t[3] & 2) {
            stride = ((u32)(w + 3) >> 2) << 4;
        } else if (t[3] & 4) {
            stride = ((u32)(w + 7) >> 3) << 3;
        } else {
            stride = ((u32)(w + 3) >> 2) << 3;
        }
        return e + (stride * h + 8);
    }
    return NULL;
}

/* Returns the palette of image index */
u8 *func_8021A110_ovl_1B2670(u8 *desc, u32 index) {
    u32 w = *(u16 *)(desc + 4);
    u32 h = *(u16 *)(desc + 6);
    u8 *tex = func_80219F40_ovl_1B2670(desc, index);
    u32 off;

    if (tex == NULL) {
        return NULL;
    }
    off = 8;
    if (tex[3] & 1) {
        if (desc[3] & 2) {
            off = h * (((w + 3) >> 2) << 4) + 8;
        } else if (desc[3] & 4) {
            off = h * (((w + 7) >> 3) << 3) + 8;
        } else {
            off = h * (((w + 3) >> 2) << 3) + 8;
        }
    }
    if (tex[3] & 2) {
        if (desc[3] & 1) {
            off += h * (((w + 15) >> 4) << 3);
        } else {
            off += h * (((w + 7) >> 3) << 3);
        }
    }
    if (tex[3] & 4) {
        return tex + off;
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021A208_ovl_1B2670);

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021AAE8_ovl_1B2670);

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021B040_ovl_1B2670);

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021B31C_ovl_1B2670);

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021B5EC_ovl_1B2670);

/* Loads the shared table chunk (two sections) and creates the two default entries */
#ifdef NON_MATCHING
/* Same issue as 6E660 func_80197D20: the original reuses a1 for both section offsets (load, add, load); here the two halfword loads are scheduled together. */
void **func_8021B93C_ovl_1B2670(void) {
    TblHdr *tmp = HMalloc(ChunkSize(0x315736));
    void **r;

    LoadChunkRaw(tmp, 0x315736);
    D_8021C9E8_ovl_1B2670 = HMalloc(tmp->size);
    _bcopy(tmp, D_8021C9E8_ovl_1B2670, tmp->size);
    D_8021C9E0_ovl_1B2670 = (u8 *)D_8021C9E8_ovl_1B2670 + D_8021C9E8_ovl_1B2670->sec0;
    D_8021C9E4_ovl_1B2670 = (u8 *)D_8021C9E8_ovl_1B2670 + D_8021C9E8_ovl_1B2670->sec1;
    HFree(tmp);
    r = HMalloc(8);
    bzero(r, 8);
    r[0] = func_8021B5EC_ovl_1B2670(1, 1, 0, 1, 1);
    r[1] = func_8021B5EC_ovl_1B2670(1, 1, 0, 0, 1);
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021B93C_ovl_1B2670);
#endif

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021BA30_ovl_1B2670);

INCLUDE_ASM("asm/nonmatchings/1B7630", func_8021BB5C_ovl_1B2670);
