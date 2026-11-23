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

extern s32 D_801F3678;
void func_8020CDA0(s32 se);
void func_802158B8_ovl_18F100(void);
void func_8021592C_ovl_18F100(void);

/* Formation screen update: tracks the member under the cursor, and on confirm picks up the
 * member under the cursor or drops the held one there (swapping with the member already in the
 * cell, or moving into an empty one); blocked cells raise a message instead. Cancel puts the
 * held member back, or closes the screen */
void func_80215438_ovl_18F100(void) {
    s32 i;
    s32 j;
    u8 t;
    u8 f;
    s32 cur;

    if (D_801F0B9C == -1) {
        D_8021B2B0_ovl_18F100 = D_8021B290_ovl_18F100[D_801ED5B0];
    }
    func_802158B8_ovl_18F100();
    cur = D_801F0B9C;
    if (cur != -1) {
        D_8021B2B4_ovl_18F100 = D_8021B290_ovl_18F100[D_801ED5B0];
        func_8021592C_ovl_18F100();
    } else if (D_8021B2AC_ovl_18F100 != cur) {
        func_8017C384(D_8021B174_ovl_18F100);
        D_8021B2AC_ovl_18F100 = cur;
    }
    if (D_8021B2A4_ovl_18F100 == 0) {
        return;
    }
    if (D_8021B2A4_ovl_18F100 > 0) {
        if (D_801F3678 < 0x80) {
        done:
            D_8021B2A4_ovl_18F100 = 0;
            return;
        }
        {
            if (D_801F0B9C == -1) {
                if (D_8021B290_ovl_18F100[D_801ED5B0] == 0) {
                    func_8020CDA0(9);
                    goto done;
                } else {
                    D_801F0B9C = D_801ED5B0;
                    D_8021B2A4_ovl_18F100 = 0;
                    func_8020CDA0(6);
                    func_802152F4_ovl_18F100();
                    return;
                }
            } else if (D_8021B330_ovl_18F100[D_801ED5B0] == 0) {
                i = 0;
                if (D_8021B290_ovl_18F100[D_801ED5B0] != 0) {
                    for (; i < 5; i++) {
                        if (gSquads[D_801F3658].members[i] == D_8021B2B0_ovl_18F100) {
                            break;
                        }
                    }
                    for (j = 0; j < 5; j++) {
                        if (gSquads[D_801F3658].members[j] == D_8021B290_ovl_18F100[D_801ED5B0]) {
                            break;
                        }
                    }
                    t = gSquads[D_801F3658].pos[i];
                    gSquads[D_801F3658].pos[i] = gSquads[D_801F3658].pos[j];
                    gSquads[D_801F3658].pos[j] = t;
                    D_8021B290_ovl_18F100[D_801F0B9C] = gSquads[D_801F3658].members[j];
                    D_8021B290_ovl_18F100[D_801ED5B0] = gSquads[D_801F3658].members[i];
                    t = D_8021B299_ovl_18F100[D_801F0B9C];
                    D_8021B299_ovl_18F100[D_801F0B9C] = D_8021B299_ovl_18F100[D_801ED5B0];
                    D_8021B299_ovl_18F100[D_801ED5B0] = t;
                } else {
                    for (; i < 5; i++) {
                        if (gSquads[D_801F3658].members[i] == D_8021B2B0_ovl_18F100) {
                            break;
                        }
                    }
                    gSquads[D_801F3658].pos[i] = D_801ED5B0;
                    D_8021B290_ovl_18F100[D_801ED5B0] = D_8021B290_ovl_18F100[D_801F0B9C];
                    D_8021B290_ovl_18F100[D_801F0B9C] = 0;
                    D_8021B299_ovl_18F100[D_801ED5B0] = D_8021B299_ovl_18F100[D_801F0B9C];
                    D_8021B299_ovl_18F100[D_801F0B9C] = 0;
                }
                func_8020CDA0(0);
                D_801F0B9C = -1;
            } else {
                func_8020CDA0(9);
                f = D_8021B330_ovl_18F100[D_801ED5B0];
                for (i = 0; i < 8; i++) {
                    if (f & 1) {
                        break;
                    }
                    f >>= 1;
                }
                D_8021B2B8_ovl_18F100 = i + 0x36;
            }
        }
        goto done;
    }
    if (D_801F0B9C != -1) {
        D_801ED5B0 = D_801F0B9C;
        D_801F0B9C = -1;
        D_8021B2A4_ovl_18F100 = 0;
    } else {
        D_8021B2A4_ovl_18F100 = -100;
    }
    func_8020CDA0(1);
}

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
/* Whether any id in list i (except the current one) has a level of at least lvl */
s32 func_80216FF4_ovl_18F100(s32 i, s32 lvl) {
    s8 *l = &D_8021B188_ovl_18F100[i * 9];
    s32 k;

    if (l[0] != -1) {
        k = 0;
        do {
            if (l[k] != D_801F0B9C && D_8021B299_ovl_18F100[l[k]] >= lvl) {
                return 1;
            }
            k++;
        } while (l[k] != -1);
    }
    return 0;
}

extern s32 D_801F0DE0[]; /* indexed here: a plain s32 store is scheduled later */
extern s32 D_801F3618;
extern u8 D_801F0FE1;
u8 func_801DADF0(u8 *u);
extern u8 *D_801F0CB0[];
extern u8 D_801F0FDF;
extern u8 D_801F0FE0;
extern u16 *D_801F0CA0;
extern u16 *D_800C4BDC;
extern u16 *D_800C4C4C;
void *func_8017F36C(u16 id);
void func_8017EF24(s32 a, u16 kind, s16 x, s16 y, s16 w, s16 h, s16 x2, s16 y2, s16 w2, s16 h2);
void func_8020CDA0(s32 se);
s32 func_801E00F0(s32 id, s32 a, s32 b, s32 c, s32 d, s32 x2);
void func_80215438_ovl_18F100(void);

/* Per-frame handler of the 3x3 node grid: closes the screen once state -100 is reached, opens
 * the help box on its button, and otherwise moves the cursor (D_801ED5B0) with the d-pad, sets
 * the state to 1 / -1 on confirm / cancel, and redraws */
void func_80217068_ovl_18F100(void) {
    s32 c;
    s32 old;
    s32 r;
    s32 pad[3];

    if (D_8021B2A4_ovl_18F100 == -100) {
        if (D_8021B170_ovl_18F100 != NULL) {
            func_8017C384(D_8021B170_ovl_18F100);
        }
        if (D_8021B2AC_ovl_18F100 != -1) {
            func_8017C384(D_8021B174_ovl_18F100);
        }
        D_801F0DE0[0] = 4;
        D_8021B2A4_ovl_18F100 = 0;
        D_801F3618 = -1;
        D_80210219 = 0x11;
        D_801F0FE1 = func_801DADF0(D_801F0CB0[D_801F3658]);
        D_801F0FDF = 2;
        D_801F0FE0 = 1;
        return;
    }
    if ((*D_800C4BDC & D_801F0CA0[3]) && func_8017F36C(0x300) == NULL) {
        func_8017EF24(0x3100B, 0x200, 0x98, 0x70, 0xA8, 0x80, 0x18, 0x64, 0x128, 0x8C);
        func_8020CDA0(0x10);
        return;
    }
    if (func_8017F36C(0x300) != NULL) {
        return;
    }
    if (D_8021B2B8_ovl_18F100 == 0) {
        c = D_801ED5B0;
        old = c;
        if (*D_800C4C4C & 0x800) {
            if (c >= 3) {
                c -= 3;
            }
        } else if (*D_800C4C4C & 0x400) {
            if (c < 6) {
                c += 3;
            }
        }
        if (*D_800C4C4C & 0x200) {
            if (c < 3) {
                c += c < 2;
            } else if (c < 6) {
                c += c < 5;
            } else {
                c += c < 8;
            }
        } else if (*D_800C4C4C & 0x100) {
            if (c < 3) {
                c -= c > 0;
            } else if (c < 6) {
                c -= !(c < 4);
            } else {
                c -= !(c < 7);
            }
        }
        if (c != old) {
            func_8020CDA0(2);
        }
        D_801ED5B0 = c;
        if (*D_800C4BDC & D_801F0CA0[0]) {
            D_8021B2A4_ovl_18F100 = 1;
        } else if (*D_800C4BDC & D_801F0CA0[1]) {
            D_8021B2A4_ovl_18F100 = -1;
        }
    } else {
        r = func_801E00F0(D_8021B2B8_ovl_18F100, 0, 0, 0, 1, -1);
        if (r == 1 || r == 3) {
            D_8021B2B8_ovl_18F100 = 0;
        }
    }
    func_80215438_ovl_18F100();
}
