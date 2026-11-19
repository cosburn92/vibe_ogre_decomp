#include "common.h"

/* ovl_213B10 (21C970): message text buffer. Codes 0x16 and 0x38 carry a length byte at +3;
 * other codes take D_801E5C70[code] bytes. Byte +2 of each entry is its pixel width. */

typedef struct {
    /* 0x000 */ s32 unk000;
    /* 0x004 */ s32 col;
    /* 0x008 */ s32 x;
    /* 0x00C */ s32 unk00C;
    /* 0x010 */ u8 text[0x800];
    /* 0x810 */ u32 pos;
    /* 0x814 */ u32 len;
} TextBuf;

extern TextBuf *D_801CE8C0;
extern u8 D_801E5C70_ovl_213B10[]; /* entry size per code */

void func_801D98F4_ovl_213B10(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i);
void func_801DA180_ovl_213B10(s32 a, f32 step);

/* Index of the entry after i, or -1 */
#ifdef NON_MATCHING
/* Branch layout of the 0x16 case and the final range check differ. */
u32 func_801D96A0_ovl_213B10(u32 i) {
    TextBuf *tb = D_801CE8C0;
    u8 c;

    if (i >= tb->len) {
        return -1;
    }
    c = tb->text[i];
    if (c == 0x16) {
        i = (i + 4) + tb->text[i + 3];
    } else if (c == 0x38) {
        i += tb->text[i + 3];
    } else if (c == 0) {
        i++;
        while (D_801CE8C0->text[i] == 0) {
            i++;
        }
        return i;
    } else {
        i += D_801E5C70_ovl_213B10[c];
    }
    if (i < D_801CE8C0->len) {
        return i;
    }
    return -1;
}
#else
INCLUDE_ASM("asm/nonmatchings/21C970", func_801D96A0_ovl_213B10);
#endif

/* Index of the entry before n */
u32 func_801D9748_ovl_213B10(u32 n) {
    u32 prev = -1;
    u32 i;

    for (i = 0; i < D_801CE8C0->len; i = func_801D96A0_ovl_213B10(i)) {
        if (i == n) {
            return prev;
        }
        prev = i;
    }
    return prev;
}

/* Index of the entry under pixel x */
#ifdef NON_MATCHING
/* Loop structure and the cached buffer pointer differ. */
u32 func_801D97B8_ovl_213B10(u32 x) {
    TextBuf *tb = D_801CE8C0;
    u32 i = 0;
    u8 w;
    u8 c;

    while (i < D_801CE8C0->len) {
        w = D_801CE8C0->text[i + 2];
        if (w >= x) {
            return i;
        }
        c = D_801CE8C0->text[i];
        x -= w;
        if (c == 0x16) {
            i = i + 4 + D_801CE8C0->text[i + 3];
        } else if (c == 0x38) {
            i += D_801CE8C0->text[i + 3];
        } else {
            i += D_801E5C70_ovl_213B10[tb->text[i]];
        }
    }
    return i;
}
#else
INCLUDE_ASM("asm/nonmatchings/21C970", func_801D97B8_ovl_213B10);
#endif

/* Moves the cursor to pixel x */
void func_801D9860_ovl_213B10(u32 x) {
    u32 i = 0;
    u32 acc = 0;
    u8 w;

    while (i < D_801CE8C0->len) {
        w = D_801CE8C0->text[i + 2];
        if (w >= x) {
            break;
        }
        x -= w;
        acc += w;
        i = func_801D96A0_ovl_213B10(i);
    }
    D_801CE8C0->x = acc + x;
    D_801CE8C0->col = x;
    D_801CE8C0->pos = i;
}

const char D_801E6AE0_ovl_213B10[] = "AddTimeTable:!!!!\x96\xA2\x92m\x82\xCC\x96\xBD\x97\xDF!!!!!(%d)\n";
const char D_801E6B08_ovl_213B10[] =
    "\x82\xA0\x82\xEA\x81H\x82\xA8\x82\xA9\x82\xB5\x82\xA2\x82\xBC\x81I\x81I\x81H\n";

INCLUDE_ASM("asm/nonmatchings/21C970", func_801D98F4_ovl_213B10);

void func_801D9EFC_ovl_213B10(s32 a, s32 b) {
    func_801D98F4_ovl_213B10(a, b, 0, 0, 0, 0, 0, 0, 0);
}

void func_801D9F30_ovl_213B10(s32 a, s32 b, s32 c) {
    func_801D98F4_ovl_213B10(a, b, c, 0, 0, 0, 0, 0, 0);
}

void func_801D9F60_ovl_213B10(s32 a, s32 b, s32 c, s32 d) {
    func_801D98F4_ovl_213B10(a, b, c, d, 0, 0, 0, 0, 0);
}

void func_801D9F8C_ovl_213B10(s32 a, s32 b, s32 c, s32 d, s32 e) {
    func_801D98F4_ovl_213B10(a, b, c, d, e, 0, 0, 0, 0);
}

void func_801D9FBC_ovl_213B10(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    func_801D98F4_ovl_213B10(a, b, c, d, e, f, 0, 0, 0);
}

void func_801D9FF0_ovl_213B10(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g) {
    func_801D98F4_ovl_213B10(a, b, c, d, e, f, g, 0, 0);
}

void func_801DA028_ovl_213B10(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h) {
    func_801D98F4_ovl_213B10(a, b, c, d, e, f, g, h, 0);
}

void func_801DA064_ovl_213B10(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i) {
    func_801D98F4_ovl_213B10(a, b, c, d, e, f, g, h, i);
}

/* Deletes the entry at i, adding its +1 byte to the entry that moves into its place */
#ifdef NON_MATCHING
/* Loop and pointer reloads differ. */
void func_801DA0A4_ovl_213B10(u32 i) {
    u8 *p = &D_801CE8C0->text[i];
    u8 c = p[0];
    u8 extra = p[1];
    u32 n;
    u32 j;

    if (c == 0x16) {
        n = p[3] + 4;
    } else if (c == 0x38) {
        n = p[3];
    } else {
        n = D_801E5C70_ovl_213B10[D_801CE8C0->text[i]];
    }
    for (j = i; j < D_801CE8C0->len - n; j++) {
        D_801CE8C0->text[j] = D_801CE8C0->text[j + n];
    }
    D_801CE8C0->len -= n;
    D_801CE8C0->text[i + 1] += extra;
}
#else
INCLUDE_ASM("asm/nonmatchings/21C970", func_801DA0A4_ovl_213B10);
#endif

INCLUDE_ASM("asm/nonmatchings/21C970", func_801DA180_ovl_213B10);

void func_801DA4B4_ovl_213B10(s32 a) {
    func_801DA180_ovl_213B10(a, 0.1f);
}

void func_801DA4D8_ovl_213B10(s32 a) {
    func_801DA180_ovl_213B10(a, -0.1f);
}

void func_801DA4FC_ovl_213B10(s32 a) {
    func_801DA180_ovl_213B10(a, 0.0f);
}
