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
u8 *func_80197DE4_ovl_06E660(u8 *desc, u32 index);
void func_801997D0_ovl_06E660(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 mode);

/* Sprite animation player state */
typedef struct {
    /* 0x00 */ u8 *script;
    /* 0x04 */ s16 pc;
    /* 0x06 */ s16 x;
    /* 0x08 */ s16 y;
    /* 0x0A */ u8 loops;
    /* 0x0B */ u8 alpha;
    /* 0x0C */ u8 unk0C;
    /* 0x0D */ u8 frame;
    /* 0x0E */ u8 wait;
    /* 0x0F */ u8 state; /* 0 stopped, bit 7 restart */
} SpriteAnim;

/* Steps a sprite animation script. Pairs (op, arg): op < 0xF0 shows frame op for arg ticks;
 * F0 stop, F1 set loop count, F2/F3 set x/y, F4/F5 subtract from x/y, F6 set alpha,
 * F7 add to alpha (clamped), F8 jump, F9 loop back while the count lasts. */
#ifdef NON_MATCHING
/* anim script step: op/arg registers (a1/a2) swapped */
s32 func_80197B70_ovl_06E660(SpriteAnim *a) {
    u8 done;
    u8 op;
    u8 arg;
    u8 v;

    if (a->state == 0) {
        return 0;
    }
    if (a->state & 0x80) {
        a->state = 1;
        a->y = 0;
        a->x = 0;
        a->pc = -1;
        a->wait = 0;
    }
    if (a->wait == 0 || --a->wait == 0) {
        done = 0;
        a->pc++;
        do {
            op = a->script[a->pc * 2];
            arg = a->script[a->pc * 2 + 1];
            if (op < 0xF0) {
                done++;
                a->frame = op;
                a->wait = arg;
                continue;
            }
            a->pc++;
            switch (op) {
                case 0xF0:
                    a->state = 0;
                    done++;
                    break;
                case 0xF1:
                    a->loops = arg;
                    break;
                case 0xF2:
                    a->x = (s8)arg;
                    break;
                case 0xF3:
                    a->y = (s8)arg;
                    break;
                case 0xF4:
                    a->x -= (s8)arg;
                    break;
                case 0xF5:
                    a->y -= (s8)arg;
                    break;
                case 0xF6:
                    a->alpha = arg;
                    break;
                case 0xF7:
                    if ((s8)arg < 0) {
                        v = a->alpha + arg;
                        if (a->alpha + (s8)arg < 0) {
                            v = 0;
                        }
                    } else {
                        v = a->alpha + arg;
                        if (a->alpha + (s8)arg >= 0x100) {
                            v = 0xFF;
                        }
                    }
                    a->alpha = v;
                    break;
                case 0xF9:
                    if (--a->loops == 0) {
                        break;
                    }
                case 0xF8:
                    a->pc = arg;
                    break;
            }
        } while (done == 0);
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/6E660", func_80197B70_ovl_06E660);
#endif

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

/* Texture set: [2] count, [3] flags (1 image, 2 4-bit, 4 8-bit), u16 width at 4, height at 6;
 * each image header has its own flags (1 texels, 2 second plane, 4 palette). Returns image index. */
u8 *func_80197DE4_ovl_06E660(u8 *t, u32 page) {
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

/* Returns the palette that follows the image data of the texture described by desc */
u8 *func_80197F08_ovl_06E660(u8 *desc, u32 index) {
    u8 *tex = func_80197DE4_ovl_06E660(desc, index);
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

/* Returns the palette of image index */
u8 *func_80197FB4_ovl_06E660(u8 *desc, u32 index) {
    u32 w = *(u16 *)(desc + 4);
    u32 h = *(u16 *)(desc + 6);
    u8 *tex = func_80197DE4_ovl_06E660(desc, index);
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

INCLUDE_ASM("asm/nonmatchings/6E660", func_801980AC_ovl_06E660);

/* Tints an RGBA colour towards blue-grey by its brightest channel, keeping alpha */
/* The red and green results use swapped registers (a3/t0). */
/* Tints an RGBA colour towards blue-grey by its brightest channel, keeping alpha.
 * Form adapted from OB64-Decomp func_00202198 (MIT, (c) 2026 rempred). */
u32 func_8019898C_ovl_06E660(u32 rgba) {
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
