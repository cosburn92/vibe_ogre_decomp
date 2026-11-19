#include "common.h"

/* ovl_06E660 */

typedef struct {
    /* 0x000 */ u32 count;
    /* 0x004 */ u8 unk004[0x408];
    /* 0x40C */ void *frames[0x20];
} SpriteEntry; /* size 0x48C */

typedef struct {
    /* 0x00 */ u32 count;
    /* 0x04 */ SpriteEntry entries[1];
} SpriteTable;

extern u16 *D_8019A798_ovl_06E660;
extern void *D_8019A790_ovl_06E660;
extern void *D_8019A794_ovl_06E660;

void *HMalloc(s32 size);
void *HFree(void *p);
void _bcopy(void *src, void *dst, s32 n);
u32 ChunkSize(u32 handle);
void *LoadChunkRaw(void *dst, u32 handle);
u8 *func_80197DE4_ovl_06E660(u8 *desc);
void func_801997D0_ovl_06E660(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 mode);

INCLUDE_ASM("asm/nonmatchings/6E660", func_80197B70_ovl_06E660);

#ifdef NON_MATCHING
/* Only register choice when computing the two section pointers differs. */
void func_80197D20_ovl_06E660(void) {
    u16 *tmp = HMalloc(ChunkSize(0x315736));

    LoadChunkRaw(tmp, 0x315736);
    D_8019A798_ovl_06E660 = HMalloc(tmp[0x16 / 2]);
    _bcopy(tmp, D_8019A798_ovl_06E660, tmp[0x16 / 2]);
    D_8019A790_ovl_06E660 = (u8 *)D_8019A798_ovl_06E660 + D_8019A798_ovl_06E660[0];
    D_8019A794_ovl_06E660 = (u8 *)D_8019A798_ovl_06E660 + D_8019A798_ovl_06E660[2];
    HFree(tmp);
}
#else
INCLUDE_ASM("asm/nonmatchings/6E660", func_80197D20_ovl_06E660);
#endif

void func_80197DB8_ovl_06E660(void) {
    HFree(D_8019A798_ovl_06E660);
    D_8019A798_ovl_06E660 = NULL;
}

INCLUDE_ASM("asm/nonmatchings/6E660", func_80197DE4_ovl_06E660);

/* Returns the palette that follows the image data of the texture described by desc */
u8 *func_80197F08_ovl_06E660(u8 *desc) {
    u8 *tex = func_80197DE4_ovl_06E660(desc);
    u32 w;
    u32 h;
    u32 rowBytes;

    if (tex == NULL) {
        return NULL;
    }
    w = *(u16 *)(desc + 4);
    h = *(u16 *)(desc + 6);
    if (tex[3] & 2) {
        if (!(tex[3] & 1)) {
            return tex + 8;
        }
        if (desc[3] & 2) {
            rowBytes = (w + 3) / 4 * 16;
        } else if (desc[3] & 4) {
            rowBytes = (w + 7) / 8 * 8;
        } else {
            rowBytes = (w + 3) / 4 * 8;
        }
        return tex + (rowBytes * h + 8);
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/6E660", func_80197FB4_ovl_06E660);

INCLUDE_ASM("asm/nonmatchings/6E660", func_801980AC_ovl_06E660);

INCLUDE_ASM("asm/nonmatchings/6E660", func_8019898C_ovl_06E660);

INCLUDE_ASM("asm/nonmatchings/6E660", func_80198A4C_ovl_06E660);

INCLUDE_ASM("asm/nonmatchings/6E660", func_80198FA4_ovl_06E660);

INCLUDE_ASM("asm/nonmatchings/6E660", func_80199354_ovl_06E660);

INCLUDE_ASM("asm/nonmatchings/6E660", func_80199624_ovl_06E660);

INCLUDE_ASM("asm/nonmatchings/6E660", func_801997D0_ovl_06E660);

void func_80199D74_ovl_06E660(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    func_801997D0_ovl_06E660(a, b, c, d, e, f, 0);
}

void func_80199DA0_ovl_06E660(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    func_801997D0_ovl_06E660(a, b, c, d, e, f, 1);
}

void func_80199DD0_ovl_06E660(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    func_801997D0_ovl_06E660(a, b, c, d, e, f, 2);
}

void func_80199E00_ovl_06E660(SpriteTable *t) {
    u32 i;
    u32 j;

    if (t != NULL) {
        for (i = 0; i < t->count; i++) {
            for (j = 0; j < t->entries[i].count; j++) {
                HFree(t->entries[i].frames[j]);
            }
        }
        HFree(t);
    }
}

INCLUDE_ASM("asm/nonmatchings/6E660", func_80199E98_ovl_06E660);
