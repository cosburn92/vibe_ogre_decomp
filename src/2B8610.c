#include "common.h"
#include "heap.h"

/* 2B8610 */

extern u8 *D_801CE8BC;
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
extern u8 *D_8022A974;
s32 func_801C8B68(u8 *u);
s32 func_801C8C58(u8 *u);
/* The callee reads c as u16 (lhu) but the caller sign-extends it: the caller saw an s16 prototype */
#ifdef NON_MATCHING
void func_8024387C_ovl_2AE3C0(u8 *u, s32 i, s32 a, s32 id, s32 b, u8 slot, u16 c);
#else
void func_8024387C_ovl_2AE3C0(u8 *u, s32 i, s32 a, s32 id, s32 b, u8 slot, s16 c);
#endif
extern u8 *D_801CE8C0;
extern u8 D_8022A7F0;

void bzero(void *p, s32 n);
void func_801BE71C(void);
void func_801C1D90(void);
void func_801C1A94(void);
void func_801C2310(void);
void func_801AECA4(u8 a);
/* --- end decls --- */

void func_80243810_ovl_2AE3C0(void) {
    u8 *p;

    func_801BE71C();
    p = HMalloc(0x6094);
    D_801CE8BC = p;
    bzero(p, 0x6094);
    D_801CE8C0 = D_801CE8BC + 0x57E0;
    func_801C1D90();
    func_801C1A94();
    func_801C2310();
    func_801AECA4(D_8022A7F0);
}

typedef struct {
    /* 0x000 */ u8 pad0[0xE4];
    /* 0x0E4 */ s32 id;
    /* 0x0E8 */ s32 e8;
    /* 0x0EC */ s32 ec;
    /* 0x0F0 */ u8 padF0[4];
    /* 0x0F4 */ s32 f4;
    /* 0x0F8 */ s32 f8;
    /* 0x0FC */ u8 padFC[0x20];
    /* 0x11C */ f32 x;
    /* 0x120 */ f32 y;
    /* 0x124 */ f32 z;
    /* 0x128 */ u8 pad128[0xC];
    /* 0x134 */ u16 h134;
    /* 0x136 */ u16 h136;
    /* 0x138 */ u16 h138;
    /* 0x13A */ u16 h13A;
    /* 0x13C */ u8 b13C;
    /* 0x13D */ u8 b13D;
    /* 0x13E */ u8 pad13E[7];
    /* 0x145 */ u8 b145;
    /* 0x146 */ u8 b146;
    /* 0x147 */ u8 b147;
    /* 0x148 */ u8 b148;
    /* 0x149 */ u8 member;
    /* 0x14A */ u8 pad14A[6];
} BattleObj150; /* size 0x150 */

s32 func_801C8C90(u8 *u);
u16 func_8016FA34(u16 a, u16 b, u16 c, u16 d);
void func_801C41C8(s32 *a, s32 *b, s32 *c, s32 *d, s32 *e, s32 f);
void func_8022E9E8(BattleObj150 *o);

/* Puts the members of army unit u into battle: member 0 reuses the object of slot `slot`, members 1-2
 * get a fresh copy of the previous one in the first free slot, 8 units further out, each 50 apart in c */
#ifdef NON_MATCHING
/* same length; k/slot (s2/s3) and u/c (s4/s5) swap registers and the field stores schedule differently */
void func_8024387C_ovl_2AE3C0(u8 *u, s32 i, s32 a, s32 id, s32 b, u8 slot, u16 c) {
    s32 ids[3];
    s32 tmp;
    s32 j;
    s32 k = 0;
    BattleObj150 *obj = NULL;
    BattleObj150 *prev = NULL;

    if (func_801C8C90(u) == 1) {
        for (k = 0; k < 28; k++) {
            if (FIELD(D_8022A974 + k * 4, BattleObj150 *, 0x18) == NULL) {
                break;
            }
        }
    }
    for (j = 0; j < 3; j++) {
        if (((s32 *)u)[j] != 0) {
            if (j == 0) {
                ids[0] = slot;
                obj = FIELD(D_8022A974 + slot * 4, BattleObj150 *, 0x18);
            } else {
                ids[j] = k;
                obj = HMalloc(0x150);
                FIELD(D_8022A974 + k * 4, BattleObj150 *, 0x18) = obj;
                bzero(obj, 0x150);
                *obj = *prev;
                obj->x -= 8.0f;
                obj->z += 8.0f;
            }
            obj->id = ids[j];
            obj->e8 = id;
            obj->ec = b;
            obj->b145 = 1;
            obj->b13D = 1;
            obj->h138 = c;
            obj->h134 = c;
            obj->member = j;
            obj->f8 = 0;
            obj->f4 = 0;
            obj->b147 = i;
            obj->h13A = a;
            obj->b146 = a;
            tmp = func_8016FA34(FIELD(u, u16, 0x36), FIELD(u, u16, 0x38), FIELD(u, u16, 0x3A), FIELD(u, u16, 0x3C));
            prev = obj;
            func_801C41C8(&id, &b, &a, &a, &tmp, 1);
            func_8022E9E8(obj);
        }
        c += 50;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/2B8610", func_8024387C_ovl_2AE3C0);
#endif

/* Hands the first eligible army unit (present, not func_801C8B68, func_801C8C58) to func_8024387C for
 * battle slot `slot`, if that slot is occupied */
s32 func_80243AC8_ovl_2AE3C0(s16 slot, s16 b) {
    s32 i;
    u8 *u;

    for (i = 0; i < 20; i++) {
        u = D_801CE8BC + 0x1C4 + i * 0xF8;
        if (FIELD(u, s32, 0x48) != 0 && !func_801C8B68(u) && func_801C8C58(u)) {
            if (FIELD(D_8022A974 + slot * 4, u8 *, 0x18) != NULL) {
                func_8024387C_ovl_2AE3C0(u, i, FIELD(u, s32, 0x58) < 4, FIELD(u, s32, 0x48), FIELD(u, s32, 0x4C),
                                         slot, b);
                return 0;
            }
        }
    }
    return 0;
}
