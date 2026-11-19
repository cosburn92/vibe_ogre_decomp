#include "common.h"
#include "scene.h"

/* F6340 */

extern s16 D_800E7A36;
extern s16 D_800E7A38;
extern s16 D_800E7A3A;
extern s16 D_800E7A3C;
extern u8 *D_801AD100_ovl_0EBBB0;
extern void *D_800E9BA0;

s32 func_8007705C(s32 a, void *b, s32 c, s32 d, s32 e, s32 f, s32 g);
void func_801AB2A4_ovl_0EBBB0(s16 id);
void func_80078674(s16 a, s16 b, s16 c, s16 d);
void func_8007FB60(void *gfx, void *p);
void _bcopy(void *src, void *dst, s32 n);
u32 func_801AB5B0_ovl_0EBBB0(u8 *src, u32 size, void *dst);
typedef struct {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u8 flags2;
    /* 0x03 */ u8 flags3;
    /* 0x04 */ u8 unk04[0x10];
    /* 0x14 */ void (*update)(void);
    /* 0x18 */ void (*draw)(void);
    /* 0x1C */ void (*exit)(void);
    /* 0x20 */ u16 size;
    /* 0x22 */ u8 unk22[2];
    /* 0x24 */ s32 w24;
} CurScene;
extern CurScene D_800E7A30;
extern u8 D_800E91D0[];
void bzero(void *p, s32 n);
void func_801AB33C_ovl_0EBBB0(void);
void func_801AB55C_ovl_0EBBB0(void);
void func_801A9DB0_ovl_0EBBB0(s32 a, s32 b, f32 *x, f32 *y);
void func_801AA248_ovl_0EBBB0(s32 a, s32 b, s32 c, f32 *x, f32 *y);
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/F6340", func_801A95E0_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801A9714_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801A9848_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801A997C_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801A9AB0_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801A9DB0_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AA064_ovl_0EBBB0);

/* Projects (a, b) to screen space and scales it from 320x240 to scene i's window size */
void func_801AA15C_ovl_0EBBB0(s32 i, s32 a, s32 b, f32 *x, f32 *y) {
    f32 sx;
    f32 sy;

    func_801A9DB0_ovl_0EBBB0(a, b, &sx, &sy);
    *x = sx / 320.0f * (D_800E82C8[i].x2 - D_800E82C8[i].x + 1);
    *y = sy / 240.0f * (D_800E82C8[i].y2 - D_800E82C8[i].y + 1);
}

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AA248_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AA52C_ovl_0EBBB0);

/* Same as func_801AA15C for a 3D point */
void func_801AA62C_ovl_0EBBB0(s32 i, s32 a, s32 b, s32 c, f32 *x, f32 *y) {
    f32 sx;
    f32 sy;

    func_801AA248_ovl_0EBBB0(a, b, c, &sx, &sy);
    *x = sx / 320.0f * (D_800E82C8[i].x2 - D_800E82C8[i].x + 1);
    *y = sy / 240.0f * (D_800E82C8[i].y2 - D_800E82C8[i].y + 1);
}

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AA720_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AA8A4_ovl_0EBBB0);

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AAE10_ovl_0EBBB0);

/* Opens a scene for this screen and sets its fade parameters; returns the scene slot */
s32 func_801AB020_ovl_0EBBB0(s32 a, u8 b) {
    s32 i = func_8007705C(0xC000, func_801AB2A4_ovl_0EBBB0, 0, 0, 0, 0, 0xF000);

    D_800E82C8[i].unk89 = 11;
    D_800E82C8[i].unk88 = a;
    D_800E82C8[i].unk8A = b;
    D_800E82C8[i].unk8B = 0;
    D_800E82C8[i].unk8C = 0;
    D_800E82C8[i].unk8D = 0;
    D_800E82C8[i].unk8E = 0xFF;
    D_800E82C8[i].unk8F = 0;
    D_800E82C8[i].unk97 = 0;
    return i;
}

/* Same with fade mode 15 */
s32 func_801AB0FC_ovl_0EBBB0(s32 a, u8 b) {
    s32 i = func_8007705C(0xC000, func_801AB2A4_ovl_0EBBB0, 0, 0, 0, 0, 0xF000);

    D_800E82C8[i].unk89 = 15;
    D_800E82C8[i].unk88 = a;
    D_800E82C8[i].unk8A = b;
    D_800E82C8[i].unk8B = 0;
    D_800E82C8[i].unk8C = 0;
    D_800E82C8[i].unk8D = 0;
    D_800E82C8[i].unk8E = 0;
    D_800E82C8[i].unk8F = 0xFF;
    D_800E82C8[i].unk97 = 0;
    return i;
}

void func_801AB1D8_ovl_0EBBB0(void) {
    func_8007705C(0xC000, func_801AB2A4_ovl_0EBBB0, 0, 0, 0, 0, 0xF000);
}

void func_801AB214_ovl_0EBBB0(u8 i, u8 a, u8 b, u8 c, u8 d, u8 e, u8 f, u8 g, u8 h) {
    D_800E82C8[i].unk88 = a;
    D_800E82C8[i].unk89 = b;
    D_800E82C8[i].unk8A = c;
    D_800E82C8[i].unk8B = d;
    D_800E82C8[i].unk8C = e;
    D_800E82C8[i].unk8D = f;
    D_800E82C8[i].unk8E = g;
    D_800E82C8[i].unk8F = h;
}

/* Scene init: installs the update/draw handlers with 0x28 bytes of state, stores the id */
void func_801AB2A4_ovl_0EBBB0(s16 id) {
    D_800E7A30.update = func_801AB33C_ovl_0EBBB0;
    D_800E7A30.draw = func_801AB55C_ovl_0EBBB0;
    D_800E7A30.size = 0x28;
    D_800E7A30.w24 = 0;
    D_800E7A30.flags |= 0x200;
    D_800E7A30.flags2 |= 9;
    D_800E7A30.flags3 |= 0xC;
    bzero(D_800E91D0, 0x28);
    *(s16 *)D_801AD100_ovl_0EBBB0 = id;
}

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AB33C_ovl_0EBBB0);

void func_801AB55C_ovl_0EBBB0(void) {
    func_80078674(D_800E7A36, D_800E7A38, D_800E7A3A, D_800E7A3C);
    func_8007FB60(&D_800E9BA0, D_801AD100_ovl_0EBBB0 + 4);
}

INCLUDE_ASM("asm/nonmatchings/F6340", func_801AB5B0_ovl_0EBBB0);

/* Reads a big-endian u32 from an unaligned pointer */
inline u32 func_801AB720_ovl_0EBBB0(u8 *p) {
    return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
}

/* Unpacks a [size, packed size, data] block into dst (stored raw when packed size is 0); returns the size */
#ifdef NON_MATCHING
/* inlined BE32 result copy/branch layout differs */
u32 func_801AB74C_ovl_0EBBB0(void *dst, u8 *src) {
    u32 c = func_801AB720_ovl_0EBBB0(src + 4);
    u32 n;

    if (c != 0) {
        return func_801AB5B0_ovl_0EBBB0(src + 8, c, dst);
    }
    n = func_801AB720_ovl_0EBBB0(src);
    _bcopy(src + 8, dst, n);
    return n;
}
#else
INCLUDE_ASM("asm/nonmatchings/F6340", func_801AB74C_ovl_0EBBB0);
#endif
