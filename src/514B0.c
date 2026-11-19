#include "common.h"

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))

typedef struct Node {
    /* 0x00 */ struct Node *prev;
    /* 0x04 */ struct Node *next;
    /* 0x08 */ u8 unk08[0xE];
    /* 0x16 */ u16 id;
} Node;

extern u8 D_801936E0_ovl_040E80;
extern u8 D_8018FD64_ovl_040E80[];
extern u8 D_8018FD78_ovl_040E80[];
extern u16 D_800C4C26;
extern Node *D_8018FDC0_ovl_040E80;
s32 func_8019C67C(void);
void func_8019C488(s32 a);
Node *func_8017F3C0_ovl_040E80(void);
void func_8017C2FC_ovl_040E80(Node *n);
void func_801805D0_ovl_040E80(s32 a, s32 b, s32 c, s32 d);



extern u8 D_8018FD50_ovl_040E80[];
extern u8 D_8018FD8C_ovl_040E80[];
extern u8 D_8018FDA0_ovl_040E80[];

void *func_8017B5B0_ovl_040E80(void) {
    return D_8018FD50_ovl_040E80;
}

u8 *func_8017B5BC_ovl_040E80(void) {
    u8 *p = D_8018FD64_ovl_040E80;

    if (D_801936E0_ovl_040E80) {
        p = D_8018FD78_ovl_040E80;
    }
    return p;
}

void *func_8017B5E0_ovl_040E80(void) {
    return D_8018FD8C_ovl_040E80;
}

#include "libultra.h"
#define NODE_DATA(n) FIELD(n, void *, 0xD0)
extern Gfx *D_800E9BA0;
extern u8 D_80187020_ovl_040E80;
extern s32 D_801977C8_ovl_040E80;
void HFree(void *p);
void func_8016C814_ovl_040E80(u8 *p);
void func_801A101C(void);
void func_801B7FA0(u8 *p);
void func_8019B040(s32 a);
extern u8 ovl_079730_TEXT_START[];
extern u8 ovl_079730_TEXT_END[];
extern u8 ovl_079730_DATA_START[];
extern u8 ovl_079730_RODATA_END[];
extern u8 ovl_079730_BSS_START[];
extern u8 ovl_079730_BSS_END[];
extern u8 ovl_079730_ROM_START[];
extern u8 ovl_079730_ROM_END[];
extern u8 ovl_079730_VRAM[];
extern u8 ovl_087200_TEXT_START[];
extern u8 ovl_087200_TEXT_END[];
extern u8 ovl_087200_DATA_START[];
extern u8 ovl_087200_RODATA_END[];
extern u8 ovl_087200_BSS_START[];
extern u8 ovl_087200_BSS_END[];
extern u8 ovl_087200_ROM_START[];
extern u8 ovl_087200_ROM_END[];
extern u8 ovl_087200_VRAM[];
extern u8 ovl_071280_TEXT_START[];
extern u8 ovl_071280_TEXT_END[];
extern u8 ovl_071280_DATA_START[];
extern u8 ovl_071280_RODATA_END[];
extern u8 ovl_071280_BSS_START[];
extern u8 ovl_071280_BSS_END[];
extern u8 ovl_071280_ROM_START[];
extern u8 ovl_071280_ROM_END[];
extern u8 ovl_071280_VRAM[];
void osInvalICache(void *p, s32 n);
void osInvalDCache(void *p, s32 n);
void RomRead(void *rom, void *dst, s32 size);
void bzero(void *p, s32 n);
void func_80073164(u8 relative, s16 a, s16 b, s16 c, s16 d, s16 e, s16 f);
void func_8019A7A0(void);
void func_801C1990(void);
void func_8019A864(void);
s32 func_8019D65C(void);
extern u16 D_800C4C26;
Node *func_8017C074_ovl_040E80(u16 kind, u8 b, void (*fn)(), s16 x, s16 y, s16 w, s16 h);
void func_801807F4_ovl_040E80(Node *n, s32 a);
void func_8017C584_ovl_040E80();
void func_8017EAE8_ovl_040E80();
void func_80221354(void);
extern u8 D_80196AEC_ovl_040E80;
void func_8017F554_ovl_040E80(Node *n);
typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u16 flag;
    s16 s;
    s16 t;
    u8 rgba[4];
} Vtx514; /* 0x10 */
/* --- end decls --- */

/* Loads overlay 079730 and enters it (mode 1) */
void func_8017B5EC_ovl_040E80(void) {
    osInvalICache(ovl_079730_TEXT_START, ovl_079730_TEXT_END - ovl_079730_TEXT_START);
    osInvalDCache(ovl_079730_DATA_START, ovl_079730_RODATA_END - ovl_079730_DATA_START);
    RomRead(ovl_079730_ROM_START, ovl_079730_VRAM, ovl_079730_ROM_END - ovl_079730_ROM_START);
    if (ovl_079730_BSS_START != ovl_079730_BSS_END) {
        bzero(ovl_079730_BSS_START, ovl_079730_BSS_END - ovl_079730_BSS_START);
    }
    func_80073164(0, 8, 2, 0x40, 0x40, 0x100, 0x1800);
    func_8019A7A0();
    D_801977C8_ovl_040E80 = 1;
}

/* Loads overlay 087200 and enters it (mode 2) */
void func_8017B6B0_ovl_040E80(void) {
    osInvalICache(ovl_087200_TEXT_START, ovl_087200_TEXT_END - ovl_087200_TEXT_START);
    osInvalDCache(ovl_087200_DATA_START, ovl_087200_RODATA_END - ovl_087200_DATA_START);
    RomRead(ovl_087200_ROM_START, ovl_087200_VRAM, ovl_087200_ROM_END - ovl_087200_ROM_START);
    if (ovl_087200_BSS_START != ovl_087200_BSS_END) {
        bzero(ovl_087200_BSS_START, ovl_087200_BSS_END - ovl_087200_BSS_START);
    }
    func_80073164(0, 1, 1, 0x40, 1, 0x600, 0x2200);
    func_801C1990();
    D_801977C8_ovl_040E80 = 2;
}

/* Loads overlay 071280 and enters it (mode 3) */
void func_8017B774_ovl_040E80(void) {
    osInvalICache(ovl_071280_TEXT_START, ovl_071280_TEXT_END - ovl_071280_TEXT_START);
    osInvalDCache(ovl_071280_DATA_START, ovl_071280_RODATA_END - ovl_071280_DATA_START);
    RomRead(ovl_071280_ROM_START, ovl_071280_VRAM, ovl_071280_ROM_END - ovl_071280_ROM_START);
    if (ovl_071280_BSS_START != ovl_071280_BSS_END) {
        bzero(ovl_071280_BSS_START, ovl_071280_BSS_END - ovl_071280_BSS_START);
    }
    func_80073164(0, 8, 2, 0x40, 0x40, 0x100, 0x3000);
    func_8019A864();
    D_801977C8_ovl_040E80 = 3;
}

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017B838_ovl_040E80);

void func_8017B9A8_ovl_040E80(u8 *p) {
    func_8016C814_ovl_040E80(p);
    switch (D_801977C8_ovl_040E80) {
        case 0:
            break;
        case 1:
            func_801A101C();
            break;
        case 2:
            func_801B7FA0(FIELD(p, u8 *, 0x10) + 0x200);
            break;
        case 3:
            func_8019B040(FIELD(p, s32, 0x10));
            break;
    }
}

void func_8017BA2C_ovl_040E80(void) {
}

void *func_8017BA34_ovl_040E80(void) {
    return D_8018FDA0_ovl_040E80;
}

void func_8017BA40_ovl_040E80(void) {
    osInvalICache(ovl_071280_TEXT_START, ovl_071280_TEXT_END - ovl_071280_TEXT_START);
    osInvalDCache(ovl_071280_DATA_START, ovl_071280_RODATA_END - ovl_071280_DATA_START);
    RomRead(ovl_071280_ROM_START, ovl_071280_VRAM, ovl_071280_ROM_END - ovl_071280_ROM_START);
    if (ovl_071280_BSS_START != ovl_071280_BSS_END) {
        bzero(ovl_071280_BSS_START, ovl_071280_BSS_END - ovl_071280_BSS_START);
    }
    func_80073164(0, 8, 2, 0x40, 0x40, 0x100, 0x3000);
    if (func_8019D65C()) {
        D_800C4C26 = 9;
    }
}

void func_8017BB08_ovl_040E80(void) {
    if (func_8019C67C()) {
        D_800C4C26 = 9;
    }
}

void func_8017BB34_ovl_040E80(u8 *p) {
    func_8019C488(FIELD(p, s32, 0x10));
}

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017BB50_ovl_040E80);

/* Pipe sync, scissor (full screen or letterboxed), pipe sync */
#ifdef NON_MATCHING
/* scissor DL: original's branch layout/cross-jump differs */
void func_8017BD48_ovl_040E80(void) {
    Gfx *g;

    if (D_80187020_ovl_040E80) {
        g = D_800E9BA0++;
        g->w0 = 0xE7000000;
        g->w1 = 0;
        g = D_800E9BA0++;
        g->w0 = 0xED000000;
        g->w1 = 0xA00780;
        g = D_800E9BA0++;
        g->w0 = 0xE7000000;
        g->w1 = 0;
    } else {
        g = D_800E9BA0++;
        g->w0 = 0xE7000000;
        g->w1 = 0;
        g = D_800E9BA0++;
        g->w0 = 0xED000000;
        g->w1 = 0x4FC3BC;
        g = D_800E9BA0++;
        g->w0 = 0xE7000000;
        g->w1 = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/514B0", func_8017BD48_ovl_040E80);
#endif

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017BDC0_ovl_040E80);

/* Releases nodes from the end of the list until it is empty. */
void func_8017BED4_ovl_040E80(void) {
    Node *n = func_8017F3C0_ovl_040E80();

    if (n != NULL) {
        do {
            func_8017C2FC_ovl_040E80(n);
            n = func_8017F3C0_ovl_040E80();
        } while (n != NULL);
    }
}

/* Frees every node, then the list's buffers and head */
#ifdef NON_MATCHING
/* original reloads the list head between the final stores */
void func_8017BF10_ovl_040E80(void) {
    Node *n;
    Node *t;

    if (D_8018FDC0_ovl_040E80 == NULL) {
        return;
    }
    n = D_8018FDC0_ovl_040E80->next;
    while (n != NULL) {
        t = n;
        if (NODE_DATA(n) != NULL) {
            HFree(NODE_DATA(n));
        }
        n = n->next;
        HFree(t);
    }
    HFree(FIELD(D_8018FDC0_ovl_040E80, void *, 0xCC));
    HFree(FIELD(D_8018FDC0_ovl_040E80, void *, 0xC8));
    FIELD(D_8018FDC0_ovl_040E80, u16, 0) = 0;
    D_8018FDC0_ovl_040E80->next = NULL;
    HFree(D_8018FDC0_ovl_040E80);
    D_8018FDC0_ovl_040E80 = NULL;
}
#else
INCLUDE_ASM("asm/nonmatchings/514B0", func_8017BF10_ovl_040E80);
#endif

Node *func_8017BFB0_ovl_040E80(u16 kind, u8 b, void (*fn)(), s16 x, s16 y, s16 w, s16 h, s16 x2, s16 y2, s16 w2, s16 h2) {
    Node *n = func_8017C074_ovl_040E80(kind, b, fn, x, y, w, h);

    FIELD(n, s16, 0x18) = 0;
    FIELD(n, s32, 0x3C) = x2;
    FIELD(n, s32, 0x40) = y2;
    FIELD(n, s32, 0x44) = w2;
    FIELD(n, s32, 0x48) = h2;
    FIELD(n, s16, 0x28) = 1;
    FIELD(n, u16, 0x26) = 0x8000;
    return n;
}

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017C074_ovl_040E80);

#ifdef NON_MATCHING
/* Stores match; the stack arguments are loaded earlier than in the original. */
void func_8017C24C_ovl_040E80(u8 *p, s32 a, s16 b, s16 c, s16 d, s16 e) {
    FIELD(p, s32, 0x10) = a;
    FIELD(p, s32, 0x3C) = b;
    FIELD(p, u16, 0x28) = 3;
    FIELD(p, s32, 0x40) = c;
    FIELD(p, u16, 0x26) = 0x8000;
    FIELD(p, s32, 0x44) = d;
    FIELD(p, s32, 0x48) = e;
}
#else
INCLUDE_ASM("asm/nonmatchings/514B0", func_8017C24C_ovl_040E80);
#endif

#ifdef NON_MATCHING
/* stack argument load is scheduled first in the original */
u8 *func_8017C29C_ovl_040E80(u8 *p, s16 x, s16 y, s16 z, s16 w) {
    FIELD(p, s32, 0x2C) = x;
    FIELD(p, s32, 0x3C) = x;
    FIELD(p, s32, 0x30) = y;
    FIELD(p, s32, 0x40) = y;
    FIELD(p, s16, 0x18) = 0xFF;
    FIELD(p, s32, 0x34) = z;
    FIELD(p, s32, 0x44) = z;
    FIELD(p, s16, 0x28) = 0;
    FIELD(p, u16, 0x26) = 0x8004;
    FIELD(p, s32, 0x38) = w;
    FIELD(p, s32, 0x48) = w;
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/514B0", func_8017C29C_ovl_040E80);
#endif

/* Unlinks a node from the list and frees it */
void func_8017C2FC_ovl_040E80(Node *n) {
    Node *next;
    Node *prev;

    if (NODE_DATA(n) != NULL) {
        HFree(NODE_DATA(n));
    }
    next = n->next;
    prev = n->prev;
    if (next != NULL) {
        next->prev = prev;
    }
    if (D_8018FDC0_ovl_040E80->next == n) {
        D_8018FDC0_ovl_040E80->next = next;
    } else {
        prev->next = n->next;
    }
    FIELD(D_8018FDC0_ovl_040E80, u16, 0)--;
    if (n != NULL) {
        HFree(n);
    }
}

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017C384_ovl_040E80);

/* Window fill render state with alpha a (opaque when 0xFF) */
#ifdef NON_MATCHING
/* display list pointer/global store scheduling differs around the alpha branch */
void func_8017C4B4_ovl_040E80(u32 a) {
    Gfx *g;
    u32 w0;
    u32 w1;

    g = D_800E9BA0++;
    g->w0 = 0xFA000000;
    g->w1 = a | 0xFFFFFF00;
    g = D_800E9BA0++;
    g->w0 = 0xE3000C00;
    g->w1 = 0;
    g = D_800E9BA0++;
    g->w0 = 0xE3001201;
    g->w1 = 0;
    if (a == 0xFF) {
        w0 = 0xE200001C;
        w1 = 0x0F0A7008;
    } else {
        w0 = 0xE200001C;
        w1 = 0x00504240;
    }
    g = D_800E9BA0++;
    g->w0 = w0;
    g->w1 = w1;
    g = D_800E9BA0++;
    g->w0 = 0xFC119623;
    g->w1 = 0xFF2FFFFF;
}
#else
INCLUDE_ASM("asm/nonmatchings/514B0", func_8017C4B4_ovl_040E80);
#endif

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017C584_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017CBE8_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017D6D0_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017E264_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017E80C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017EAE8_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017EC84_ovl_040E80);

void func_8017EE64_ovl_040E80(s32 a, u16 kind, s16 x, s16 y, s16 w, s16 h) {
    Node *n = func_8017C074_ovl_040E80(kind | 0x100, 0, func_8017C584_ovl_040E80, x, y, w, h);

    FIELD(n, s16, 0x28) = 1;
    FIELD(n, s16, 0x18) = 0;
    FIELD(n, s32, 0x3C) = x;
    FIELD(n, s32, 0x40) = y;
    FIELD(n, s32, 0x44) = w;
    FIELD(n, s32, 0x48) = h;
    FIELD(n, u16, 0x26) = 0x8000;
    func_801807F4_ovl_040E80(n, a);
}

/* Like func_8017EE64, with a separate inner rectangle */
#ifdef NON_MATCHING
/* Only scheduling differs: the original sign-extends the four stack parameters before li v0,1 for the 0x28 store; with any statement order tried, the li lands first or the stores move. */
void func_8017EF24_ovl_040E80(s32 a, u16 kind, s16 x, s16 y, s16 w, s16 h, s16 x2, s16 y2, s16 w2, s16 h2) {
    Node *n = func_8017C074_ovl_040E80(kind | 0x100, 0, func_8017C584_ovl_040E80, x, y, w, h);

    FIELD(n, s32, 0x3C) = x2;
    FIELD(n, s32, 0x40) = y2;
    FIELD(n, s32, 0x44) = w2;
    FIELD(n, s32, 0x48) = h2;
    FIELD(n, s16, 0x28) = 1;
    FIELD(n, s16, 0x18) = 0;
    FIELD(n, u16, 0x26) = 0x8000;
    func_801807F4_ovl_040E80(n, a);
}
#else
INCLUDE_ASM("asm/nonmatchings/514B0", func_8017EF24_ovl_040E80);
#endif

/* Inner-rect widget carrying a pointer at 0xE0, created with argument 0x52057 */
#ifdef NON_MATCHING
/* Same scheduling issue as func_8017EF24: the original sign-extends the four stack parameters before li v0,1. */
Node *func_8017F010_ovl_040E80(void *data, u16 kind, s16 x, s16 y, s16 w, s16 h, s16 x2, s16 y2, s16 w2, s16 h2) {
    Node *n = func_8017C074_ovl_040E80(kind | 0x100, 0, func_8017C584_ovl_040E80, x, y, w, h);

    FIELD(n, s16, 0x28) = 1;
    FIELD(n, s16, 0x18) = 0;
    FIELD(n, s32, 0x3C) = x2;
    FIELD(n, s32, 0x40) = y2;
    FIELD(n, s32, 0x44) = w2;
    FIELD(n, s32, 0x48) = h2;
    FIELD(n, u16, 0x26) = 0x8000;
    FIELD(n, void *, 0xE0) = data;
    func_801807F4_ovl_040E80(n, 0x52057);
    return n;
}
#else
INCLUDE_ASM("asm/nonmatchings/514B0", func_8017F010_ovl_040E80);
#endif

/* Marker widget next to o (same colour index), drawn by func_8017EAE8 */
#ifdef NON_MATCHING
/* Same scheduling issue as func_8017EF24 (sign-extensions before li v1,1). The original also computes x-0x3E, y-0x10 and y+0x10 before the call, reusing the x/y registers. An inline setter with s16 parameters did not help. */
void func_8017F114_ovl_040E80(Node *o) {
    s32 x = FIELD(o, s32, 0x44);
    s32 y = FIELD(o, s32, 0x48);
    Node *n = func_8017C074_ovl_040E80(4, 0, func_8017EAE8_ovl_040E80, x - 12, y - 8, x - 4, y + 8);

    FIELD(n, s16, 0x28) = 1;
    FIELD(n, s16, 0x18) = 0;
    FIELD(n, s32, 0x3C) = (s16)(x - 0x3E);
    FIELD(n, s32, 0x40) = (s16)(y - 0x10);
    FIELD(n, s32, 0x44) = (s16)(x - 4);
    FIELD(n, s32, 0x48) = (s16)(y + 0x10);
    FIELD(n, u16, 0x26) = 0x8000;
    FIELD(n, u8, 0x22) = FIELD(o, u8, 0x22);
    FIELD(n, u8, 0x24) = 1;
    FIELD(n, u8, 0x25) = 2;
    FIELD(n, u8, 0x23) = FIELD(o, u8, 0x22);
}
#else
INCLUDE_ASM("asm/nonmatchings/514B0", func_8017F114_ovl_040E80);
#endif

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017F214_ovl_040E80);

/* The last node in the list with this id, or NULL. */
Node *func_8017F334_ovl_040E80(u16 id) {
    Node *found = NULL;
    Node *n;

    for (n = D_8018FDC0_ovl_040E80->next; n != NULL; n = n->next) {
        if (n->id == id) {
            found = n;
        }
    }
    return found;
}

/* Last node whose id is (low byte == id, high byte clear) or (high byte part == id) */
Node *func_8017F36C_ovl_040E80(u16 id) {
    Node *n;
    Node *r = NULL;

    for (n = D_8018FDC0_ovl_040E80->next; n != NULL; n = n->next) {
        if (!(n->id & 0xFF00) && (n->id & 0xFF) == id) {
            r = n;
        } else if ((n->id & 0xFF00) == id) {
            r = n;
        }
    }
    return r;
}

/* The last node of the list, or NULL. */
inline Node *func_8017F3C0_ovl_040E80(void) {
    Node *n;

    if (D_8018FDC0_ovl_040E80 == NULL) {
        return NULL;
    }
    n = D_8018FDC0_ovl_040E80->next;
    if (n != NULL && n->next != NULL) {
        do {
            n = n->next;
        } while (n->next != NULL);
    }
    return n;
}

/* The last node whose flag 0x10 is clear, walking back from the tail (NULL if none) */
static inline Node *tail514(void) {
    Node *n;

    if (D_8018FDC0_ovl_040E80 == NULL) {
        return NULL;
    }
    n = D_8018FDC0_ovl_040E80->next;
    if (n == NULL) {
        return NULL;
    }
    while (n->next != NULL) {
        n = n->next;
    }
    return n;
}
inline Node *func_8017F408_ovl_040E80(void) {
    Node *n;

    if (D_8018FDC0_ovl_040E80 == NULL) {
        return NULL;
    }
    if (D_8018FDC0_ovl_040E80->next == NULL) {
        return NULL;
    }
    n = func_8017F3C0_ovl_040E80();
    while (n != NULL) {
        if (!(FIELD(n, u8, 0x14) & 0x10)) {
            return n;
        }
        n = (n->prev != D_8018FDC0_ovl_040E80->next) ? n->prev : NULL;
    }
    return n;
}

#ifdef NON_MATCHING
/* inlined F408 loop: a0/v1 register swap */
void func_8017F490_ovl_040E80(void) {
    if (D_801936E0_ovl_040E80 && (D_80196AEC_ovl_040E80 & 0x80)) {
        func_80221354();
    }
    func_8017F554_ovl_040E80(func_8017F408_ovl_040E80());
}
#else
INCLUDE_ASM("asm/nonmatchings/514B0", func_8017F490_ovl_040E80);
#endif

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017F554_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017FAF8_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017FC28_ovl_040E80);

void func_801805B4_ovl_040E80(s32 a, s32 b, s32 c) {
    func_801805D0_ovl_040E80(a, b, c, 0);
}

INCLUDE_ASM("asm/nonmatchings/514B0", func_801805D0_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_801807F4_ovl_040E80);

/* Fills the 4 vertices at +0x90 for a textured quad from (x0, y0) to (x1, y1) in screen coords */
void func_80180B1C_ovl_040E80(Vtx514 *v, s16 x0, s16 y0, s16 x1, s16 y1) {
    s32 cx = 160;
    s32 cy = 120;
    s16 sw = (x1 - x0 > 0 ? x1 - x0 : x0 - x1) - 1;
    s16 sh = (y1 - y0 > 0 ? y1 - y0 : y0 - y1) - 1;

    v[9].x = cx - x1;
    v[9].y = cy - y1;
    v[9].s = 0;
    v[9].t = sh << 6;
    v[10].x = cx - x1;
    v[10].y = cy - y0;
    v[10].s = 0;
    v[10].t = 0;
    v[11].x = cx - x0;
    v[11].y = cy - y0;
    v[11].s = sw << 6;
    v[11].t = 0;
    v[12].x = cx - x0;
    v[12].y = cy - y1;
    v[12].s = sw << 6;
    v[12].t = sh << 6;
}

INCLUDE_ASM("asm/nonmatchings/514B0", func_80180BDC_ovl_040E80);

s32 func_80181498_ovl_040E80(u8 *p, s32 i) {
    return FIELD(FIELD(p, u8 *, 0xD0) + i * 4, s32, 0x530);
}

void func_801814AC_ovl_040E80(u8 *obj, s32 i, u8 *dst, u8 n) {
    s32 pad;
    u8 *src = FIELD(FIELD(obj, u8 *, 0xD0) + i * 4, u8 *, 0x530);
    s32 k;

    for (k = 0; k < n; k++) {
        *dst++ = *src++;
        *dst++ = *src++;
    }
    *dst = 0;
}

INCLUDE_ASM("asm/nonmatchings/514B0", func_80181504_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_801818A0_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_80181C2C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_80182578_ovl_040E80);

/* Starts the open/close animation: current rect = from, step = (to - from) / frames */
#ifdef NON_MATCHING
/* from-x int kept in a register instead of reloaded with lwc1 */
void func_80184130_ovl_040E80(Node *n) {
    f32 t = FIELD(n, u16, 0x1E);
    f32 dx = (FIELD(n, s32, 0x3C) - FIELD(n, s32, 0x2C)) / t;
    f32 dy = (FIELD(n, s32, 0x40) - FIELD(n, s32, 0x30)) / t;
    f32 dw = (FIELD(n, s32, 0x44) - FIELD(n, s32, 0x34)) / t;
    f32 dh = (FIELD(n, s32, 0x48) - FIELD(n, s32, 0x38)) / t;

    FIELD(n, f32, 0x5C) = FIELD(n, s32, 0x2C);
    FIELD(n, f32, 0x60) = FIELD(n, s32, 0x30);
    FIELD(n, f32, 0x64) = FIELD(n, s32, 0x34);
    FIELD(n, f32, 0x68) = FIELD(n, s32, 0x38);
    FIELD(n, f32, 0x6C) = dx;
    FIELD(n, f32, 0x70) = dy;
    FIELD(n, f32, 0x74) = dw;
    FIELD(n, f32, 0x78) = dh;
}
#else
INCLUDE_ASM("asm/nonmatchings/514B0", func_80184130_ovl_040E80);
#endif

INCLUDE_RODATA("asm/nonmatchings/514B0", D_80190E4C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_801841F4_ovl_040E80);
