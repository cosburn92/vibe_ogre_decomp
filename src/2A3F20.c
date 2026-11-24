#include "common.h"
#include "heap.h"

/* 2A3F20 */

typedef struct {
    u8 unk0[0xC];
    void *data;
} Res2A3;

typedef struct {
    u8 unk0000[0x1CA4];
    Res2A3 *res;
} Battle2A3;

extern Battle2A3 *D_8022A974;

void func_8022B6F4_ovl_29A4C0(void);
void func_80233398_ovl_29A4C0(void);
extern u8 *D_80197AF0;
void nuGfxTaskAllEndWait(void);
void *osViGetCurrentFramebuffer(void);
void func_80080998(void *dst, void *src, s32 n);
void func_80234E50_ovl_29A4C0(void);
extern u8 D_8018FC19;
extern s32 D_80197774;
extern u8 D_8022A960;
void func_801C22E8(s32 a);
void func_801C45E0(void);
void func_801B7E9C(void);
void func_8023AA84(s32 a);
void func_8023BF30(u8 a, s32 b);
void func_80233580_ovl_29A4C0(void);
void func_8022BDDC_ovl_29A4C0(void);
/* --- end decls --- */

/* Copies the displayed frame (2 x 0x12C00 bytes) into the capture buffer */
#ifdef NON_MATCHING
/* capture buffer load scheduled before the frame pointer add in the original */
u8 *func_802346F0_ovl_29A4C0(void) {
    nuGfxTaskAllEndWait();
    if (D_80197AF0 != NULL) {
        func_80080998(D_80197AF0, osViGetCurrentFramebuffer(), 0x12C00);
        func_80080998(D_80197AF0 + 0x12C00, (u8 *)osViGetCurrentFramebuffer() + 0x12C00, 0x12C00);
    }
    return D_80197AF0;
}
#else
INCLUDE_ASM("asm/nonmatchings/2A3F20", func_802346F0_ovl_29A4C0);
#endif

/* Steps the battle effect timer; 1 while active */
s32 func_80234770_ovl_29A4C0(void) {
    u8 *e = (u8 *)D_8022A974->res;

    if (e == NULL) {
        return 0;
    }
    if (e[0] < 2) {
        return 0;
    }
    switch (e[0]) {
        case 2:
        case 3:
            if (++*(u16 *)(e + 2) == *(u16 *)(e + 4)) {
                func_80234E50_ovl_29A4C0();
            }
            break;
        case 4:
            if (*(u16 *)(e + 2) != *(u16 *)(e + 4)) {
                (*(u16 *)(e + 2))++;
            }
            break;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/2A3F20", func_80234814_ovl_29A4C0);

void func_80234BE0_ovl_29A4C0(void) {
    func_8022B6F4_ovl_29A4C0();
    func_80233398_ovl_29A4C0();
}

/* Battle teardown: in mode 2 hands back to func_801B7E9C, otherwise releases the 20 handles at 0x1C04 */
void func_80234C04_ovl_29A4C0(void) {
    u8 i;

    func_801C22E8(1);
    func_801C45E0();
    if (D_8018FC19 == 2) {
        D_80197774 = 0;
        func_801B7E9C();
    } else {
        for (i = 0; i < 20; i++) {
            func_8023AA84(((s32 *)((u8 *)D_8022A974 + 0x1C04))[i]);
            ((s32 *)((u8 *)D_8022A974 + 0x1C04))[i] = 0;
        }
        func_8023BF30(D_8022A960, 0);
    }
    func_80233580_ovl_29A4C0();
    func_8022BDDC_ovl_29A4C0();
}

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
void bzero(void *p, s32 n);
static inline u8 *Capture2A3(void) {
    nuGfxTaskAllEndWait();
    if (D_80197AF0 != NULL) {
        func_80080998(D_80197AF0, osViGetCurrentFramebuffer(), 0x12C00);
        func_80080998(D_80197AF0 + 0x12C00, (u8 *)osViGetCurrentFramebuffer() + 0x12C00, 0x12C00);
    }
    return D_80197AF0;
}

/* Starts battle effect kind over n frames on a capture of the current frame; kind 3 also
 * clears the twenty field objects */
#ifdef NON_MATCHING
/* 101/101 instructions, 3 words differ: the capture buffer load is scheduled before the frame pointer add (as in func_802346F0) */
void func_80234CBC_ovl_29A4C0(u8 kind, s16 n) {
    Res2A3 *r = HMalloc(0x10);
    u8 *cap;
    u8 i;

    D_8022A974->res = r;
    bzero(r, 0x10);
    r->unk0[0] = kind;
    cap = Capture2A3();
    FIELD(r, s16, 2) = 0;
    FIELD(r, s16, 4) = n;
    r->data = NULL;
    FIELD(r, u8 *, 8) = cap;
    if (kind == 2) {
            func_8022B6F4_ovl_29A4C0();
            func_80233398_ovl_29A4C0();
    } else if (kind == 3) {
            func_801C22E8(1);
            func_801C45E0();
            if (D_8018FC19 == 2) {
                D_80197774 = 0;
                func_801B7E9C();
            } else {
                for (i = 0; i < 20; i++) {
                    func_8023AA84(FIELD(D_8022A974, s32, 0x1C04 + i * 4));
                    FIELD(D_8022A974, s32, 0x1C04 + i * 4) = 0;
                }
                func_8023BF30(D_8022A960, 0);
            }
            func_80233580_ovl_29A4C0();
            func_8022BDDC_ovl_29A4C0();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/2A3F20", func_80234CBC_ovl_29A4C0);
#endif

void func_80234E50_ovl_29A4C0(void) {
    Res2A3 *r = D_8022A974->res;

    if (r != NULL) {
        HFree(r->data);
        HFree(r);
        D_8022A974->res = NULL;
    }
}
