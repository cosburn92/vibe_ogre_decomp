#include "common.h"

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

void *HFree(void *p);
void func_8022B6F4_ovl_29A4C0(void);
void func_80233398_ovl_29A4C0(void);
extern u8 *D_80197AF0;
void nuGfxTaskAllEndWait(void);
void *osViGetCurrentFramebuffer(void);
void func_80080998(void *dst, void *src, s32 n);
void func_80234E50_ovl_29A4C0(void);
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

INCLUDE_ASM("asm/nonmatchings/2A3F20", func_80234C04_ovl_29A4C0);

INCLUDE_ASM("asm/nonmatchings/2A3F20", func_80234CBC_ovl_29A4C0);

void func_80234E50_ovl_29A4C0(void) {
    Res2A3 *r = D_8022A974->res;

    if (r != NULL) {
        HFree(r->data);
        HFree(r);
        D_8022A974->res = NULL;
    }
}
