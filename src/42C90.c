#include "common.h"

/* 42C90 */

typedef struct {
    u32 flag : 1;
    u32 mode : 4;
    u32 rest : 27;
} Bits42;

extern u8 D_80187030_ovl_040E80;
extern u8 D_80187031_ovl_040E80;

void func_8016CDF4_ovl_040E80(Bits42 *p);
typedef struct {
    u8 b[16];
    s16 h;
} Opts42; /* 0x12 bytes, 2-aligned */
extern Opts42 D_800ABD80;
extern Opts42 D_800E9C08;
extern u8 D_80195560_ovl_040E80[];
extern u8 D_80193BC0_ovl_040E80[];
extern u8 D_80187618_ovl_040E80[];
extern u8 D_80187444_ovl_040E80[];
extern u8 D_80196A28_ovl_040E80[];
void NewGameInit(void);
void func_8016CF64_ovl_040E80(s32 a);
void func_800742F4(s32 a, void *b);
void func_8017AAF4_ovl_040E80(void *name, void *rec);
void func_8016B774_ovl_040E80(void);
void func_8016BA10_ovl_040E80(s32 a);
void func_8016CC2C_ovl_040E80(void *c);
void *HMalloc(s32 size);
void HFree(void *p);
void bzero(void *p, s32 n);
void _bcopy(const void *src, void *dst, s32 n);
/* --- end decls --- */

void func_8016CD90_ovl_040E80(Bits42 *p) {
    p->flag = D_80187030_ovl_040E80 = 0;
    p->mode = D_80187031_ovl_040E80 = 0;
}

void func_8016CDCC_ovl_040E80(Bits42 *p) {
    D_80187030_ovl_040E80 = p->flag;
    D_80187031_ovl_040E80 = p->mode;
}

void func_8016CDF4_ovl_040E80(Bits42 *p) {
    p->flag = D_80187030_ovl_040E80;
    p->mode = D_80187031_ovl_040E80;
}

/* New game with default options */
void func_8016CE40_ovl_040E80(s32 a) {
    NewGameInit();
    D_800E9C08 = D_800ABD80;
    func_8016CF64_ovl_040E80(a);
}

/* Loads the player roster from save data and fixes up the 100 character names */
void func_8016CEC4_ovl_040E80(s32 a) {
    u8 *name;
    u8 *c;
    s32 i;

    func_800742F4(a, D_80187444_ovl_040E80);
    name = HMalloc(0x10);
    for (i = 0, c = D_80193BC0_ovl_040E80; i < 100; i++, c += 0x38) {
        _bcopy(c, name, 0x10);
        func_8017AAF4_ovl_040E80(name, c);
    }
    HFree(name);
    func_8016B774_ovl_040E80();
    func_8016BA10_ovl_040E80(1);
    func_8016CC2C_ovl_040E80(D_80196A28_ovl_040E80);
}

INCLUDE_ASM("asm/nonmatchings/42C90", func_8016CF64_ovl_040E80);

/* Loads the enemy roster and fixes up the 100 character names */
void func_8016D068_ovl_040E80(s32 a) {
    u8 *name;
    u8 *c = D_80195560_ovl_040E80;
    s32 i;

    bzero(c, 0x1450);
    func_800742F4(a, D_80187618_ovl_040E80);
    name = HMalloc(0x10);
    for (i = 0; i < 100; i++, c += 0x34) {
        _bcopy(c, name, 0x10);
        func_8017AAF4_ovl_040E80(name, c);
    }
    HFree(name);
}

INCLUDE_ASM("asm/nonmatchings/42C90", func_8016D100_ovl_040E80);
