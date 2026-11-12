#include "common.h"

#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))

typedef struct Node {
    /* 0x00 */ s32 unk00;
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

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017B5EC_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017B6B0_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017B774_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017B838_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017B9A8_ovl_040E80);

void func_8017BA2C_ovl_040E80(void) {
}

void *func_8017BA34_ovl_040E80(void) {
    return D_8018FDA0_ovl_040E80;
}

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017BA40_ovl_040E80);

void func_8017BB08_ovl_040E80(void) {
    if (func_8019C67C()) {
        D_800C4C26 = 9;
    }
}

void func_8017BB34_ovl_040E80(u8 *p) {
    func_8019C488(FIELD(p, s32, 0x10));
}

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017BB50_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017BD48_ovl_040E80);

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

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017BF10_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017BFB0_ovl_040E80);

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

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017C29C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017C2FC_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017C384_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017C4B4_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017C584_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017CBE8_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017D6D0_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017E264_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017E80C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017EAE8_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017EC84_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017EE64_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017EF24_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017F010_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017F114_ovl_040E80);

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

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017F36C_ovl_040E80);

/* The last node of the list, or NULL. */
Node *func_8017F3C0_ovl_040E80(void) {
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

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017F408_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017F490_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017F554_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017FAF8_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_8017FC28_ovl_040E80);

void func_801805B4_ovl_040E80(s32 a, s32 b, s32 c) {
    func_801805D0_ovl_040E80(a, b, c, 0);
}

INCLUDE_ASM("asm/nonmatchings/514B0", func_801805D0_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_801807F4_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_80180B1C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_80180BDC_ovl_040E80);

s32 func_80181498_ovl_040E80(u8 *p, s32 i) {
    return FIELD(FIELD(p, u8 *, 0xD0) + i * 4, s32, 0x530);
}

INCLUDE_ASM("asm/nonmatchings/514B0", func_801814AC_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_80181504_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_801818A0_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_80181C2C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_80182578_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_80184130_ovl_040E80);

INCLUDE_RODATA("asm/nonmatchings/514B0", D_80190E4C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/514B0", func_801841F4_ovl_040E80);
