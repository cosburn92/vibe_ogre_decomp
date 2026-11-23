#include "common.h"

/* 283DF0 */

extern s32 D_8022A950_ovl_281860;
extern s32 D_8022A954_ovl_281860;
extern void *D_8022A958_ovl_281860;
extern void *D_8022A95C_ovl_281860;
extern u16 D_800C4B28;

void *HFree(void *p);
void func_80227FD8_ovl_281860(s32 a, s32 b);
extern u8 *D_8023DE34;
extern u8 D_80197778[];
extern s32 D_8018F1A4;
void func_80080998(u8 *dst, u8 *src, u32 n);
void func_8023BD88(s32 a, s32 b);
void func_8023BC1C(s32 a);
void func_801707F4(void);
void func_8017230C(s32 a, s32 b, u8 c);
void func_80172394(void);
void func_801725B4(s32 a);
extern u8 D_801936A8;
u8 *func_8022EC34(u8 i);
s16 func_802394A0(s32 line);
extern s8 *D_800C47F0;
/* --- end decls --- */

/* Delay-slot use differs by one instruction. */
s32 func_80227E20_ovl_281860(void)
{
  if (D_8022A95C_ovl_281860 != ((void *) 0))
  {
    if (D_8022A95C_ovl_281860)
    {
      return 1;
    }
    else
    {
      return 1;
    }
  }
  return D_8022A958_ovl_281860 == ((void *) 0);
}

INCLUDE_ASM("asm/nonmatchings/283DF0", func_80227E44_ovl_281860);

INCLUDE_ASM("asm/nonmatchings/283DF0", func_80227FD8_ovl_281860);

void func_80228180_ovl_281860(void) {
    HFree(D_8022A958_ovl_281860);
    D_8022A958_ovl_281860 = NULL;
    D_8022A950_ovl_281860 = 0;
}

void func_802281B4_ovl_281860(void) {
    HFree(D_8022A958_ovl_281860);
    HFree(D_8022A95C_ovl_281860);
    D_8022A958_ovl_281860 = NULL;
    D_8022A95C_ovl_281860 = NULL;
    D_8022A950_ovl_281860 = 0;
}

void func_802281FC_ovl_281860(s32 a) {
    HFree(D_8022A958_ovl_281860);
    D_8022A958_ovl_281860 = NULL;
    func_80227FD8_ovl_281860(a, 0);
}

void func_80228240_ovl_281860(s32 a) {
    func_80227FD8_ovl_281860(a, 1);
}

/* Frees the current buffer and promotes the pending one */
void func_8022825C_ovl_281860(void) {
    void *next;
    s32 n;

    HFree(D_8022A958_ovl_281860);
    n = D_8022A954_ovl_281860;
    next = D_8022A95C_ovl_281860;
    D_8022A958_ovl_281860 = NULL;
    D_8022A950_ovl_281860 = 0;
    D_8022A95C_ovl_281860 = NULL;
    D_8022A950_ovl_281860 = n;
    D_8022A958_ovl_281860 = next;
}

INCLUDE_ASM("asm/nonmatchings/283DF0", func_802282B8_ovl_281860);

s32 func_8022A32C_ovl_281860(s32 *p, s32 start, s32 n, s32 dir);

/* Script IF: compares val with the operand using comparison code[pc + 1]; when it holds, runs on
 * past the skip words, otherwise executes the nested block */
s32 func_8022A1F8_ovl_281860(s32 *depth, s32 pc, s32 *code, s32 val, s32 skip, s32 x) {
    s32 ok = 0;

    (*depth)++;
    switch ((u32)code[pc + 1]) {
    case 0:
        if (val == code[pc + 2]) {
            ok = 1;
        }
        break;
    case 1:
        if (val != code[pc + 2]) {
            ok = 1;
        }
        break;
    case 2:
        if (val >= code[pc + 2]) {
            ok = 1;
        }
        break;
    case 3:
        if (code[pc + 2] >= val) {
            ok = 1;
        }
        break;
    case 4:
        if (code[pc + 2] < val) {
            ok = 1;
        }
        break;
    case 5:
        if (val < code[pc + 2]) {
            ok = 1;
        }
        break;
    }
    if (ok != 0) {
        return pc + 2 + skip;
    } else {
        s32 r = func_8022A32C_ovl_281860(code, pc + 2, *depth, x);

        (*depth)--;
        return r;
    }
}

/* the switch table above is the overlay's last rodata; the section ends 8-byte aligned */
__asm__(".section .rodata\n.word 0, 0\n.section .text\n");

/* Script marker search from start: dir 1 finds the next 0x80000002; otherwise goes to the 0x80000000
 * end marker and walks back to the n-th 0x80000002. -1 when not found */
s32 func_8022A32C_ovl_281860(s32 *p, s32 start, s32 n, s32 dir) {
    s32 cnt = 0;
    s32 i;

    if (dir == 1) {
        for (i = start; i <= 0xFFFFFFE; i++) {
            if (p[i] == 0x80000002) {
                return i;
            }
        }
        return -1;
    }
    for (i = start; i <= 0xFFFFFFE; i++) {
        if (p[i] == 0x80000000) {
            for (; start < i; i--) {
                if (p[i] == 0x80000002) {
                    cnt++;
                    if (n == cnt) {
                        return i;
                    }
                }
            }
            return -1;
        }
    }
    return -1;
}

/* Index of the (0x80000005, a) pair in the list, or 0 */
s32 func_8022A428_ovl_281860(s32 a, s32 *p) {
    s32 i;

    for (i = 0; i < 0xFFFFFFF; i++, p++) {
        if (p[0] == 0x80000005 && p[1] == a) {
            return i;
        }
    }
    return 0;
}

/* Whether the analog stick is outside the dead zone (|x| or |y| > 4) */
s32 func_8022A474_ovl_281860(void) {
    f32 x = 0.0f;
    f32 y = x;

    if (D_800C47F0 != NULL) {
        if ((u8)(D_800C47F0[2] + 4) >= 9) {
            x = D_800C47F0[2] / 16.0f;
        }
        if ((u8)(D_800C47F0[3] + 4) >= 9) {
            y = D_800C47F0[3] / 16.0f;
        }
    }
    return (x + y) != 0.0;
}

s32 func_8022A528_ovl_281860(s32 mask) {
    s32 r;

    if (mask) {
        r = (D_800C4B28 & mask) == 0;
    } else {
        r = D_800C4B28;
    }
    return r;
}

void func_8022A554_ovl_281860(void) {
    func_80227FD8_ovl_281860(2, 1);
}

void func_8022A574_ovl_281860(void) {
    u8 *e;

    D_8018F1A4 = (s32)D_80197778;
    *(s32 *)D_80197778 = D_8022A950_ovl_281860;
    func_80080998(D_80197778 + 0x44, D_8023DE34 + 0x18, 6);
    func_80080998(D_80197778 + 0x4A, D_8023DE34 + 0x1E, 6);
    func_80080998(D_80197778 + 4, D_8023DE34 + 0x24, 0x40);
    e = func_8022EC34(func_802394A0(*(u16 *)(D_8023DE34 + 0x1C)));
    D_801936A8 = 0x42;
    func_801725B4(-1);
    func_80172394();
    func_8017230C(1, 0, *e);
    func_801707F4();
    func_80227FD8_ovl_281860(3, 1);
}

void func_8022A650_ovl_281860(void) {
    D_8022A950_ovl_281860 = *(s32 *)D_80197778;
    func_80080998(D_8023DE34 + 0x18, D_80197778 + 0x44, 6);
    func_80080998(D_8023DE34 + 0x1E, D_80197778 + 0x4A, 6);
    func_80080998(D_8023DE34 + 0x24, D_80197778 + 4, 0x40);
    func_8023BD88(10, 0x11);
    func_8023BC1C(10);
    func_8023BD88(11, 0x12);
    func_8023BC1C(11);
    D_8018F1A4 = 0;
    D_8023DE34[0x64] = 1;
    func_80227FD8_ovl_281860(4, 1);
}
