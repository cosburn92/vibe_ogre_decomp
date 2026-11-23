#include "common.h"

/* 18F100 */

extern void *D_8021B170_ovl_18F100;
extern s8 D_8021B188_ovl_18F100[];
extern u8 D_8021B299_ovl_18F100[];
extern s32 D_801F0B9C;

void *func_8017BFB0(s32 a, s32 b, void *c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i, s32 j, s32 k);
void func_802159B0_ovl_18F100(void);
extern void *D_8021B174_ovl_18F100;
extern s32 D_8021B2AC_ovl_18F100;
extern s32 D_8021B2A4_ovl_18F100;
extern u8 D_80210219;
void func_8017C384(void *w);
extern void *D_8021B174_ovl_18F100;
extern s32 D_8021B2AC_ovl_18F100;
extern s32 D_8021B2A4_ovl_18F100;
extern u8 D_80210219;
void func_8017C384(void *w);
extern s32 D_8021B2B4_ovl_18F100;
/* --- end decls --- */

#include "libultra.h"
#include "gbi_ultra.h"
extern Gfx *D_800E9BA0;

/* Draws the sprite-sheet rectangle (x0, y0) - (x1, y1) sampled from (s, t) */
void func_80214F80_ovl_18F100(s32 x0, s32 y0, s32 x1, s32 y1, s32 s, s32 t) {
    gDPPipeSync(D_800E9BA0++);
    gSPScisTextureRectangle(D_800E9BA0++, x0 << 2, y0 << 2, x1 << 2, y1 << 2, 0, s << 5, t << 5, 1 << 10, 1 << 10);
    gDPPipeSync(D_800E9BA0++);
}

typedef struct {
    u8 unk0;
    u8 flags;
    u8 members[5];
    u8 pos[5];
    u8 rest[0xD];
} Squad18F; /* size 0x19 */

typedef struct {
    u8 unk00[0x11];
    u8 b11;
    u8 b12;
    u8 rest[0x25];
} Unit18F; /* size 0x38 */

extern Squad18F gSquads[];
extern Unit18F D_80193BC0[];
extern s32 D_801F3658;
extern s32 D_801ED5B0;
extern u8 D_8021B290_ovl_18F100[];
extern s32 D_8021B2A8_ovl_18F100;
extern s32 D_8021B2B0_ovl_18F100;
extern s32 D_8021B2B8_ovl_18F100;
u8 func_8016DE1C(u8 a, u8 b);
void bzero(void *p, s32 n);

/* Builds the 3x3 grid for squad D_801F3658: the member in each cell and its size (1 for
 * special members >= 100), and resets the selection */
void func_802150FC_ovl_18F100(void) {
    s32 i;
    s32 m;
    u8 p;

    bzero(D_8021B290_ovl_18F100, 9);
    bzero(D_8021B299_ovl_18F100, 9);
    for (i = 0; i < 5; i++) {
        m = gSquads[D_801F3658].members[i];
        if (m != 0) {
            p = gSquads[D_801F3658].pos[i];
            D_8021B290_ovl_18F100[p] = m;
            if (m >= 100) {
                D_8021B299_ovl_18F100[p] = 1;
            } else {
                D_8021B299_ovl_18F100[p] = func_8016DE1C(D_80193BC0[m].b11, D_80193BC0[m].b12);
            }
        }
    }
    D_801ED5B0 = gSquads[D_801F3658].pos[0];
    D_8021B2A8_ovl_18F100 = -1;
    D_8021B2AC_ovl_18F100 = -1;
    D_8021B2B4_ovl_18F100 = -1;
    D_8021B2B0_ovl_18F100 = -1;
    D_8021B170_ovl_18F100 = NULL;
    D_8021B174_ovl_18F100 = NULL;
    D_8021B2A4_ovl_18F100 = 0;
    D_8021B2B8_ovl_18F100 = 0;
    D_80210219 = (D_80210219 & 0xF) | 0x20;
}

/* Closes this screen's windows */
/* Closes this screen's windows */
void func_80215298_ovl_18F100(void) {
    s32 pad[4];

    if (D_8021B170_ovl_18F100 != NULL) {
        func_8017C384(D_8021B170_ovl_18F100);
    }
    if (D_8021B2AC_ovl_18F100 != -1) {
        func_8017C384(D_8021B174_ovl_18F100);
    }
    D_8021B2A4_ovl_18F100 = 0;
    D_80210219 = 0x11;
}

extern u8 D_8021B330_ovl_18F100[];

/* Rebuilds the 9 node flags: 4 for each node with a neighbour (other than the current node) at
 * level 2+ (1+ while the current node is at level 2); when the current node has such a neighbour
 * at level 1+, every level-2 node gets 4; the current node gets 0x10 */
void func_802152F4_ovl_18F100(void) {
    s32 i;

    bzero(D_8021B330_ovl_18F100, 9);
    for (i = 0; i < 9; i++) {
        if ((u8)func_80216FF4_ovl_18F100(i, 2)) {
            D_8021B330_ovl_18F100[i] |= 4;
        }
    }
    i = 0;
    if (D_8021B299_ovl_18F100[D_801F0B9C] == 2) {
        for (i = 0; i < 9; i++) {
            if ((u8)func_80216FF4_ovl_18F100(i, 1)) {
                D_8021B330_ovl_18F100[i] |= 4;
            }
        }
        i = 0;
    }
    do {
        if (D_8021B299_ovl_18F100[i] == 2 && (u8)func_80216FF4_ovl_18F100(D_801F0B9C, 1)) {
            D_8021B330_ovl_18F100[i] = 4;
        }
        i++;
    } while (i < 9);
    D_8021B330_ovl_18F100[D_801F0B9C] |= 0x10;
}

INCLUDE_ASM("asm/nonmatchings/18F100", func_80215438_ovl_18F100);

void func_802158B8_ovl_18F100(void) {
    if (D_8021B170_ovl_18F100 == NULL) {
        D_8021B170_ovl_18F100 =
            func_8017BFB0(0, 0, func_802159B0_ovl_18F100, 0x18, 0x14, 0x20, 0x1C, 0x18, 0x14, 0x9A, 0x40);
    }
}

void func_8021592C_ovl_18F100(void) {
    if (D_8021B2AC_ovl_18F100 == -1) {
        D_8021B2AC_ovl_18F100 = D_8021B2B4_ovl_18F100;
        D_8021B174_ovl_18F100 = func_8017BFB0(0, 0, func_802159B0_ovl_18F100, 0x120, 0x14, 0x128, 0x1C, 0xA6, 0x14, 0x128, 0x40);
    }
}

INCLUDE_ASM("asm/nonmatchings/18F100", func_802159B0_ovl_18F100);

/* Whether any id in list i (except the current one) has a level of at least lvl */
#ifdef NON_MATCHING
/* Loop layout differs. */
s32 func_80216FF4_ovl_18F100(s32 i, s32 lvl) {
    s8 *p = &D_8021B188_ovl_18F100[i * 9];

    if (*p == -1) {
        return 0;
    }
    for (; *p != -1; p++) {
        if (*p == D_801F0B9C) {
            continue;
        }
        if (D_8021B299_ovl_18F100[*p] >= lvl) {
            return 1;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/18F100", func_80216FF4_ovl_18F100);
#endif

INCLUDE_ASM("asm/nonmatchings/18F100", func_80217068_ovl_18F100);
