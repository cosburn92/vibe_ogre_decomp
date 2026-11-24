#include "common.h"
#include "chunk.h"
#include "heap.h"
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

/* One member group of a formation record: class, level bonus, two items, up to three positions */
typedef struct {
    /* 0x0 */ u8 cls;
    /* 0x1 */ s8 level;
    /* 0x2 */ u8 item1[2];
    /* 0x4 */ u8 item2[2];
    /* 0x6 */ u8 pos[3];
} Formation23AGroup; /* size 0x9 */

/* Enemy formation record (35 bytes each in archive chunk 0x021AE74C) */
typedef struct {
    /* 0x00 */ u8 cls;
    /* 0x01 */ s8 level;
    /* 0x02 */ u8 item1[2];
    /* 0x04 */ u8 item2[2];
    /* 0x06 */ u8 pos;
    /* 0x07 */ Formation23AGroup grp[2];
    /* 0x19 */ u8 unk19[10];
} Formation23A; /* size 0x23 */

typedef struct {
    /* 0x00 */ char *name;
    /* 0x04 */ s32 index;
    /* 0x08 */ u8 *buf;
    /* 0x0C */ s32 size;
} Arc23A;

/* Player character record (0x38 bytes) */
typedef struct {
    Character c;
    u8 unk34[4];
} PlayerChar23A;

extern u8 D_80193670;
extern u8 D_80193671;
extern u8 D_80193672;
extern u16 D_80197B60;
extern u8 D_801976DC;
extern u8 D_801976D8;
extern u8 D_801936A8;
extern u8 D_801953F0[];
extern Arc23A D_801D16B0_ovl_23A3A0;
extern PlayerChar23A D_80193BC0[];
void func_8007ACB0(void *arc, void *reqs, s32 n);
void func_80080998(void *dst, void *src, s32 n);
void func_80172394(void);
void func_8017223C(s32 a);
void func_801707F4(void);

/* Adds one unit of class cls to the enemy roster and returns its roster index: class 1 takes a
 * pooled slot (index 100 + slot), any other class the first free enemy Character record */
static inline s32 Squad23A_AddUnit(s32 cls, s32 level, s32 item1, s32 item2) {
    u32 i;
    Character *c;

    if (cls == 1) {
        for (i = 0; i < 120; i++) {
            if (!(D_801953F2.used[i] & 1)) {
                break;
            }
        }
        D_801953F2.vals[i] = D_801953F2.cur;
        D_801953F2.used[i] = 1;
        return i + 100;
    }
    c = &D_80195560[1];
    while (c->cls != 0) {
        c++;
    }
    func_801D0840_ovl_23A3A0(c, cls, level, item1, item2);
    return c - D_80195560;
}

/* Adds the group's units at each occupied position; returns the next free member slot. The goto
 * chain is the jump-threaded shape the original compiles to: all three positions are tested
 * before the first unit is added (plain sequential ifs do not produce it). */
static inline s32 Squad23A_AddGroup(SquadRec *sq, Formation23AGroup *grp, s32 level, s32 n) {
    if (grp->cls != 0) {
        if (grp->pos[0] == 0) {
            if (grp->pos[1] == 0) {
                if (grp->pos[2] == 0) {
                    goto done;
                }
                goto check1;
            } else {
                goto add1;
            }
        } else {
            sq->members[n] = Squad23A_AddUnit(grp->cls, grp->level + level, (grp->item1[0] << 8) + grp->item1[1],
                                              (grp->item2[0] << 8) + grp->item2[1]);
            sq->pos[n] = grp->pos[0] - 1;
            n++;
        check1:
            if (grp->pos[1] != 0) {
            add1:
                sq->members[n] = Squad23A_AddUnit(grp->cls, grp->level + level,
                                                  (grp->item1[0] << 8) + grp->item1[1],
                                                  (grp->item2[0] << 8) + grp->item2[1]);
                sq->pos[n] = grp->pos[1] - 1;
                n++;
            }
            if (grp->pos[2] != 0) {
                sq->members[n] = Squad23A_AddUnit(grp->cls, grp->level + level,
                                                  (grp->item1[0] << 8) + grp->item1[1],
                                                  (grp->item2[0] << 8) + grp->item2[1]);
                sq->pos[n] = grp->pos[2] - 1;
                n++;
            }
        }
    }
done:
    return n;
}

/* Builds the encounter squad (gSquads[30]) for formation D_80193670/71 (or the forced id in
 * D_80197B60): reads its 35-byte record from the formation archive, scales levels to the
 * strongest member of the player's squad D_801976DC (capped at 99), and creates the units */
void func_801D0A8C_ovl_23A3A0(void) {
    u8 harmony = D_80193672;
    s32 id = (D_80193670 << 8) | D_80193671;
    s32 level = 99;
    u8 *built;
    Formation23A rec;
    Arc23A arc;
    Arc23A req;
    s32 *p;
    s32 chunk;
    s32 max;
    u32 n;
    s32 idx;
    SquadRec *mine;
    SquadRec *sq = &gSquads[30];
    u8 *bp;

    if (D_80197B60 != 0) {
        id = D_80197B60 & 0x7FFF;
    }
    built = &D_801976E8;
    if (*built == 30) {
        return;
    }
    arc = D_801D16B0_ovl_23A3A0;
    req = D_801D16B0_ovl_23A3A0;
    p = LoadChunkRaw(NULL, 0x021AE74C);
    chunk = *p;
    HFree(p);
    arc.size = ChunkSize(chunk);
    arc.buf = LoadChunkRaw(NULL, chunk);
    req.index = 0;
    func_8007ACB0(&arc, &req, 1);
    n = 0; /* the level scan's counter, set before this call in the original */
    HFree(arc.buf);
    func_80080998(&rec, req.buf + id * sizeof(Formation23A), sizeof(Formation23A));
    HFree(req.buf);
    bp = (u8 *)&rec;
    *built = 30;

    max = 0;
    mine = &gSquads[D_801976DC];
    for (; n < 5; n++) {
        u8 m = mine->members[n];

        if (m != 0 && m < 100) {
            if (max < D_80193BC0[m].c.level) {
                max = D_80193BC0[m].c.level;
            }
        }
    }
    if ((u32)max < (u32)level) {
        level = max;
    }

    n = 0;
    bzero(D_80195560, 0x141C);
    bzero(D_801953F0, 0x16C);
    D_801953F0[0] = 120;
    D_801953F0[1] = 120;
    func_801D0840_ovl_23A3A0(D_80195560, 1, level, 0, 0);
    D_801953F2.cur = D_80195560[0].maxHp;

    bzero(sq, sizeof(SquadRec));
    idx = Squad23A_AddUnit(((Formation23A *)bp)->cls, ((Formation23A *)bp)->level + level,
                           (((Formation23A *)bp)->item1[0] << 8) + ((Formation23A *)bp)->item1[1],
                           (((Formation23A *)bp)->item2[0] << 8) + ((Formation23A *)bp)->item2[1]);
    sq->members[n] = idx;
    D_80195560[idx & 0xFF].status = 2;
    sq->flags = 0x81;
    sq->harmony = harmony;
    sq->pos[n] = ((Formation23A *)bp)->pos - 1;
    n++;
    bp += 7;
    n = Squad23A_AddGroup(sq, (Formation23AGroup *)bp, level, n);
    bp += 9;
    Squad23A_AddGroup(sq, (Formation23AGroup *)bp, level, n);
    if (D_801976D8 & 8) {
        D_801936A8 = 0x44;
        func_80172394();
        func_8017223C(8);
        func_801707F4();
    }
}

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
