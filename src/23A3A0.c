#include "common.h"
#include "tables.h"

/* ovl_23A3A0: creates enemy units and squads */

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 flags;
    /* 0x02 */ u8 members[5];
    /* 0x07 */ u8 pos[5];
    /* 0x0C */ u8 harmony;
    /* 0x0D */ u8 items[10];
    /* 0x17 */ u8 strategy;
    /* 0x18 */ u8 legion;
} SquadRec; /* size 0x19 */

extern SquadRec gSquads[];
extern Character D_80195560[];
extern u8 D_801936A7;
extern u8 D_801936AC;
extern u8 D_801936E0;
typedef struct {
    /* 0x00 */ u16 cur;
    /* 0x02 */ u16 vals[120];
    /* 0xF2 */ u8 used[120];
} UnitPool;

extern UnitPool D_801953F2;
extern u8 D_801976E8;

void bzero(void *p, s32 n);
s32 func_8009C7CC(void);
void func_8009C550(char *dst, char *src);
void func_8016BD20(s32 a, u8 index);
u8 func_8016DE70(u8 cls, u8 base);
u16 func_8016DF88(u8 cls, u8 base);
u16 func_8016DFDC(u8 cls, u8 base);
u16 func_8016E030(u8 cls, u8 base);
u16 func_8016E084(u8 cls, u8 base);
char *func_8016E1DC(u8 cls, u8 base);
void func_8016F11C(Character *c, u8 level);
u8 func_8016F5C8(u16 item);

/* Sets up an enemy unit of the given class and level, optionally replacing default items */
void func_801D0840_ovl_23A3A0(Character *c, s32 cls, s32 level, s32 item1, s32 item2) {
    s32 base = gClassTable[cls].baseClass;
    u8 kind;
    s32 gender;

    if (base == 0) {
        base = cls;
    }
    func_8009C550((char *)c, func_8016E1DC(cls, base));
    c->cls = cls;
    c->baseCls = base;
    c->level = level;
    c->items[0] = func_8016DF88(cls, base);
    c->items[1] = func_8016DFDC(cls, base);
    c->items[2] = func_8016E030(cls, base);
    c->items[3] = func_8016E084(cls, base);
    if (item1 != 0) {
        kind = func_8016F5C8(item1);
        if (func_8016F5C8(c->items[0]) == kind) {
            c->items[0] = item1;
        }
        if (func_8016F5C8(c->items[1]) == kind) {
            c->items[1] = item1;
        }
        if (func_8016F5C8(c->items[2]) == kind) {
            c->items[2] = item1;
        }
        if (func_8016F5C8(c->items[3]) == kind) {
            c->items[3] = item1;
        }
    }
    if (item2 != 0) {
        kind = func_8016F5C8(item2);
        if (func_8016F5C8(c->items[0]) == kind) {
            c->items[0] = item2;
        }
        if (func_8016F5C8(c->items[1]) == kind) {
            c->items[1] = item2;
        }
        if (func_8016F5C8(c->items[2]) == kind) {
            c->items[2] = item2;
        }
        if (func_8016F5C8(c->items[3]) == kind) {
            c->items[3] = item2;
        }
    }
    func_8016F11C(c, level);
    func_8016BD20(1, c - D_80195560);
    gender = (u8)func_8016DE70(cls, base);
    if (gender == 3) {
        c->gender = 0;
    } else if (gender == 4) {
        c->gender = func_8009C7CC() & 1;
    } else {
        c->gender = gender;
    }
}

INCLUDE_ASM("asm/nonmatchings/23A3A0", func_801D0A8C_ovl_23A3A0);

/* Creates a one-unit enemy squad in the first free slot from 49 down to 30 */
void func_801D14E8_ovl_23A3A0(void) {
    s32 cls = D_801976E8;
    s32 level = D_801936AC;
    u32 i;
    u32 member;
    u32 k;
    SquadRec *sq;
    Character *c;

    for (i = 49; i >= 30; i--) {
        if (!(gSquads[i].flags & 1)) {
            break;
        }
    }
    if (D_801936E0 && D_801936A7 == 0x3F) {
        level += 15;
    }
    sq = &gSquads[(u8)i];
    D_801976E8 = i;
    bzero(sq, sizeof(SquadRec));
    sq->flags = 0x81;
    if (cls == 1) {
        for (k = 0; k < 120; k++) {
            if (!(D_801953F2.used[k] & 1)) {
                break;
            }
        }
        D_801953F2.vals[k] = D_801953F2.cur;
        D_801953F2.used[k] = 1;
        member = k + 100;
    } else {
        for (c = &D_80195560[1]; c->cls != 0; c++) {
        }
        func_801D0840_ovl_23A3A0(c, cls, level, 0, 0);
        member = c - D_80195560;
    }
    sq->members[1] = member;
    if (D_801936E0 && D_801936A7 == 0x3F) {
        sq->pos[1] = 7;
    } else {
        sq->pos[1] = 4;
    }
}
