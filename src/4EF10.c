#include "common.h"

typedef struct TextNode {
    /* 0x00 */ struct TextNode *next;
    /* 0x04 */ struct TextNode *prev;
    /* 0x08 */ u8 data[0x70];
    /* 0x78 */ u16 id;
    /* 0x7A */ u8 value;
} TextNode;

extern u32 *D_800E9BA0; /* display list head */
extern void *D_8018FC68_ovl_040E80;
extern u8 D_8018FC80_ovl_040E80[];
extern u8 D_8018FD10_ovl_040E80[];
extern s16 D_80190F58_ovl_040E80;
extern s16 D_80190F5A_ovl_040E80;
extern s16 D_80190F5C_ovl_040E80;
extern s16 D_80190F5E_ovl_040E80;
extern s16 D_80190F60_ovl_040E80;
extern s16 D_80190F62_ovl_040E80;
extern u8 D_80190F6D_ovl_040E80;
extern u8 D_80190F6E_ovl_040E80;
extern s16 D_80190F74_ovl_040E80;
extern s16 D_80190F76_ovl_040E80;
extern TextNode *D_80190F4C_ovl_040E80; /* most recently used */
extern TextNode *D_80190F48_ovl_040E80; /* least recently used */
void *HFree(void *p);
void func_8017907C_ovl_040E80(s32 a);
void func_80179354_ovl_040E80(void);
void func_80179F04_ovl_040E80(void);
u16 func_801794C8_ovl_040E80(void);



void func_80179354_ovl_040E80();
void func_801793AC_ovl_040E80();

void func_80179010_ovl_040E80(void) {
}

void func_80179018_ovl_040E80(void) {
    func_80179354_ovl_040E80();
}

void func_80179034_ovl_040E80(void) {
    func_801793AC_ovl_040E80();
}

void func_80179050_ovl_040E80(void) {
}

void func_80179058_ovl_040E80(void) {
}

void func_80179060_ovl_040E80(void) {
    func_8017907C_ovl_040E80(0x100);
}

extern u8 *D_80190F50_ovl_040E80;
u8 *func_8017AD3C_ovl_040E80(s32 id);
s32 func_8017AE20_ovl_040E80(s32 id);
extern u8 D_8018FC6C_ovl_040E80;
extern u8 *D_8018FC70_ovl_040E80;
extern u8 *D_8018FC74_ovl_040E80;
s32 func_8017B550_ovl_040E80(u8 c);
s32 func_8017B500_ovl_040E80(u8 **pp);
s16 func_8017A720_ovl_040E80(u8 **pp);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/4EF10", func_8017907C_ovl_040E80);

void func_801792BC_ovl_040E80(void) {
    D_8018FC68_ovl_040E80 = HFree(D_8018FC68_ovl_040E80);
}

void func_801792E8_ovl_040E80(void) {
    u32 *g = D_800E9BA0;

    D_800E9BA0 = g + 2;
    g[0] = 0xDE000000; /* gSPDisplayList */
    g[1] = (u32)D_8018FC80_ovl_040E80;
    func_80179354_ovl_040E80();
}

void func_80179328_ovl_040E80(void) {
    u32 *g = D_800E9BA0;

    D_800E9BA0 = g + 2;
    g[0] = 0xDE000000; /* gSPDisplayList */
    g[1] = (u32)D_8018FD10_ovl_040E80;
}

void func_80179354_ovl_040E80(void) {
    D_80190F76_ovl_040E80 = 0;
    D_80190F62_ovl_040E80 = 0;
    D_80190F60_ovl_040E80 = 0;
    D_80190F5A_ovl_040E80 = 0;
    D_80190F58_ovl_040E80 = 0;
    D_80190F5E_ovl_040E80 = 0;
    D_80190F5C_ovl_040E80 = 0;
    D_80190F6E_ovl_040E80 = 0;
    D_80190F6D_ovl_040E80 = 0;
    D_80190F74_ovl_040E80 = -1;
}

void func_801793AC_ovl_040E80(s32 unused, s32 x, s32 y) {
    D_80190F58_ovl_040E80 = x;
    D_80190F5C_ovl_040E80 = x;
    D_80190F5A_ovl_040E80 = y;
    D_80190F5E_ovl_040E80 = y;
    func_80179F04_ovl_040E80();
}

/* Width of character c in the normal or alternate font (control codes 0, kanji 11; a forced glyph
 * D_80190F74 overrides); characters below 0x80 are offset by 0x10 in the width table */
u8 func_801793E4_ovl_040E80(u8 c, s32 alt) {
    u8 *p;

    if (c < 0x11) {
        return 0;
    }
    if (func_8017B550_ovl_040E80(c)) {
        return 0xB;
    }
    if (D_80190F74_ovl_040E80 != -1) {
        if (!alt) {
            p = D_8018FC70_ovl_040E80 + D_80190F74_ovl_040E80;
        } else {
            p = D_8018FC74_ovl_040E80 + D_80190F74_ovl_040E80;
        }
    } else if (!alt) {
        if (c >= 0x80) {
            p = D_8018FC70_ovl_040E80 + c;
        } else {
            p = (u8 *)((u32)c + (u32)D_8018FC70_ovl_040E80);
            return p[0x10];
        }
    } else {
        if (c < 0x80) {
            p = (u8 *)((u32)c + (u32)D_8018FC74_ovl_040E80);
            return p[0x10];
        }
        p = D_8018FC74_ovl_040E80 + c;
    }
    return *p;
}

INCLUDE_ASM("asm/nonmatchings/4EF10", func_801794C8_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4EF10", func_8017996C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4EF10", func_80179F04_ovl_040E80);

void func_8017A704_ovl_040E80(void) {
    D_80190F6E_ovl_040E80 = 1;
}

void func_8017A714_ovl_040E80(void) {
    D_80190F6E_ovl_040E80 = 0;
}

extern void *D_80190F40_ovl_040E80;
extern u32 D_80190F44_ovl_040E80;
extern u16 *D_80190F54_ovl_040E80;
extern u8 D_8018FC78_ovl_040E80;
void *func_8009DD28(s32 id);

/* Reads the next character from *pp: a two-byte kanji becomes 0x200 + its index in the font table
 * (-1 when not found or a full-width space); a single byte becomes its glyph number (+0x100 for the
 * alternate font). Switches the loaded font to match. */
#ifdef NON_MATCHING
/* 106/114 instructions: the original keeps the high-byte key masked and threads the font-select branches separately */
s16 func_8017A720_ovl_040E80(u8 **pp) {
    s16 g;
    s32 id;

    if (func_8017B550_ovl_040E80(**pp) != 0) {
        u16 c;
        s32 k;
        s32 r;

        if (D_8018FC6C_ovl_040E80 == 0) {
            D_8018FC6C_ovl_040E80 = 1;
            D_80190F40_ovl_040E80 = func_8009DD28(0x0216E296);
        }
        k = *(*pp)++ << 8;
        k = *(*pp)++ | k;
        c = k;
        r = -1;
        if (c != 0x8140) {
            s32 lo = 0;
            s32 hi = D_80190F44_ovl_040E80 >> 1;

            while (lo < hi) {
                s32 mid = (lo + hi) >> 1;
                if (D_80190F54_ovl_040E80[mid] < c) {
                    lo = mid + 1;
                } else {
                    hi = mid;
                }
            }
            r = -1;
            if (D_80190F54_ovl_040E80[lo] == k) {
                r = lo + 0x200;
            }
        }
        return r;
    }
    if (D_8018FC6C_ovl_040E80 == 1) {
        D_8018FC6C_ovl_040E80 = 0;
    }
    D_80190F40_ovl_040E80 = func_8009DD28(D_8018FC78_ovl_040E80 ? 0x0218DEF2 : 0x0218C4FA);
    if (D_80190F74_ovl_040E80 != -1) {
        g = D_80190F74_ovl_040E80;
        D_80190F74_ovl_040E80 = -1;
    } else {
        u8 b = *(*pp)++;
        g = (b < 0x80) ? b + 0x10 : b;
    }
    if (D_8018FC78_ovl_040E80) {
        g += 0x100;
    }
    return g;
}
#else
INCLUDE_ASM("asm/nonmatchings/4EF10", func_8017A720_ovl_040E80);
#endif

s32 func_8017A8E8_ovl_040E80(s32 id) {
    if (id >= 0x1000) {
        return 0;
    }
    if ((D_80190F50_ovl_040E80[id >> 3] >> (id & 7)) & 1) {
        return (s32)func_8017AD3C_ovl_040E80(id);
    }
    return func_8017AE20_ovl_040E80(id);
}

/* JIS X 0208 code to Shift-JIS */
u16 func_8017A94C_ovl_040E80(u16 c) {
    u16 hi = (c & 0x7F7F) >> 8;
    u16 lo = c & 0x7F;
    s32 h;

    if (hi & 1) {
        lo += 0x1F;
    } else {
        lo += 0x7D;
    }
    if (lo >= 0x7F) {
        lo++;
    }
    h = (hi - 0x21) >> 1;
    hi = h + 0x81;
    if (hi >= 0xA0) {
        hi = h + 0xC1;
    }
    return lo | (hi << 8);
}

/* Shift-JIS code to EUC (JIS | 0x8080) */
#ifdef NON_MATCHING
/* u16/int temporaries of the high byte differ */
u16 func_8017A9B0_ovl_040E80(u16 c) {
    u16 b = c >> 8;
    u16 lo = c & 0xFF;
    s32 hi = b;
    s32 h;

    if (b >= 0xE0) {
        hi = b - 0x40;
    }
    h = (hi - 0x81) * 2;
    hi = h + 0x21;
    if (lo >= 0x80) {
        lo--;
    }
    if (lo < 0x9E) {
        lo -= 0x1F;
    } else {
        hi = h + 0x22;
        lo -= 0x7D;
    }
    return (lo | (hi << 8)) | 0x8080;
}
#else
INCLUDE_ASM("asm/nonmatchings/4EF10", func_8017A9B0_ovl_040E80);
#endif

/* Encodes string src into dst: {n} becomes byte n - 1, other characters go through func_8017A720
 * ('0' when unknown); terminated with 0xFF */
void func_8017AA18_ovl_040E80(u8 *str, u8 *dst) {
    u8 *src = str;
    s32 save = D_8018FC6C_ovl_040E80;
    s32 c;

    if (save == 1) {
        D_8018FC6C_ovl_040E80 = 0;
    }
    while (*src != 0) {
        if (*src == '{') {
            src++;
            *dst++ = func_8017B500_ovl_040E80(&src) - 1;
            src++;
        } else {
            c = (s16)func_8017A720_ovl_040E80(&src);
            if (c >= 0) {
                *dst = c;
            } else {
                *dst = '0';
            }
            dst++;
        }
    }
    *dst = 0xFF;
    D_8018FC6C_ovl_040E80 = save;
    {
        s32 pad[2];
    }
}

INCLUDE_ASM("asm/nonmatchings/4EF10", func_8017AAF4_ovl_040E80);

#ifdef NON_MATCHING
/* m2c draft, 70 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void func_8017AC08_ovl_040E80(s32 arg0, s8 *arg1) {
    s32 temp_a0;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a3;
    s32 var_t0;
    s8 *var_a1;
    void *temp_v0;
    void *var_a2;

    var_a1 = arg1;
    var_a3 = 0;
    var_t0 = 0;
    var_a2 = var_a1 + 7;
    do {
        temp_v0 = arg0 + (var_a3 >> 2);
        temp_v1 = (var_a3 & 3) * 2;
        temp_v1_2 = var_t0 & 3;
        temp_a0 = (FIELD(temp_v0, u8, 0) << temp_v1) | ((s32) FIELD(temp_v0, u8, 1) >> (8 - temp_v1));
        if (temp_v1_2 != 1) {
            if (temp_v1_2 < 2) {
                if (temp_v1_2 == 0) {
                    var_a3 += 4;
                    *var_a1 = ((temp_a0 >> 2) & 0x30) | ((temp_a0 >> 4) & 3);
                    FIELD(var_a2, s8, -6) = (s8) (((temp_a0 * 4) & 0x30) | (temp_a0 & 3));
                    goto block_18;
                }
                var_t0 += 1;
            } else {
                switch (temp_v1_2) {                /* irregular */
                case 2:
                    var_a3 += 3;
                    FIELD(var_a2, s8, -3) = (s8) (((temp_a0 >> 2) & 0x30) | ((temp_a0 >> 4) & 3));
                    FIELD(var_a2, s8, -2) = (s8) ((temp_a0 * 4) & 0x30);
                    goto block_18;
                case 3:
                    FIELD(var_a2, s8, -1) = 0;
                    FIELD(var_a2, s8, 0) = 0;
                    var_a2 += 8;
                    var_a1 += 8;
                    goto block_18;
                default:
                    var_t0 += 1;
                    break;
                }
            }
        } else {
            var_a3 += 4;
            FIELD(var_a2, s8, -5) = (s8) (((temp_a0 >> 2) & 0x30) | ((temp_a0 >> 4) & 3));
            FIELD(var_a2, s8, -4) = (s8) (((temp_a0 * 4) & 0x30) | (temp_a0 & 3));
block_18:
            var_t0 += 1;
        }
    } while (var_t0 < 0x38);
}
#else
INCLUDE_ASM("asm/nonmatchings/4EF10", func_8017AC08_ovl_040E80);
#endif

/* Cached text for id (moved to the front of the LRU list), or NULL */
u8 *func_8017AD3C_ovl_040E80(s32 id) {
    TextNode *n;

    for (n = D_80190F4C_ovl_040E80; n != NULL; n = n->next) {
        if (n->id == id) {
            if (n->next == NULL) {
                TextNode *prev = n->prev;
                TextNode *old = D_80190F4C_ovl_040E80;

                D_80190F4C_ovl_040E80 = n;
                D_80190F48_ovl_040E80 = prev;
                prev->next = NULL;
                old->prev = n;
                n->prev = NULL;
                n->next = old;
            } else if (n->prev != NULL) {
                TextNode *prev;
                TextNode *next;
                TextNode *old;

                n->next->prev = n->prev;
                prev = n->prev;
                next = n->next;
                old = D_80190F4C_ovl_040E80;
                D_80190F4C_ovl_040E80 = n;
                prev->next = next;
                old->prev = n;
                n->next = old;
                n->prev = NULL;
            }
            return n->data;
        }
    }
    return NULL;
}

u8 func_8017ADE8_ovl_040E80(s32 id) {
    TextNode *p;

    for (p = D_80190F4C_ovl_040E80; p != NULL; p = p->next) {
        if (p->id == id) {
            return p->value;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/4EF10", func_8017AE20_ovl_040E80);

INCLUDE_RODATA("asm/nonmatchings/4EF10", D_80190C88_ovl_040E80);

INCLUDE_RODATA("asm/nonmatchings/4EF10", D_80190D00_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/4EF10", func_8017B098_ovl_040E80);

/* GCC shares (c - '0') between the test and the sum; the original computes n * 10 - '0' + c. */
/* Parses the decimal number after the current character, advancing *pp past it. */
s32 func_8017B500_ovl_040E80(u8 **pp)
{
  short new_var;
  int new_var2;
  u8 *s = *pp;
  s32 n = 0;
  u8 c;
  if ((*s) != 0)
  {
    do
    {
      u8 *t = s + 1;
      *pp = t;
      new_var2 = '0';
      c = s[1];
      new_var = c - new_var2;
      if (((u32) new_var) >= 10)
      {
        break;
      }
      n = ((n * 10) - new_var2) + c;
      s = t;
    }
    while (c != 0);
  }
  return n;
}

/* Shift-JIS lead byte: 0x81-0x9F or 0xE0-0xFC. */
s32 func_8017B550_ovl_040E80(u8 c) {
    if (c < 0x81 || (u8)(c + 0x60) < 0x40 || c >= 0xFD) {
        return 0;
    }
    return 1;
}

u16 func_8017B58C_ovl_040E80(void) {
    return func_801794C8_ovl_040E80();
}
