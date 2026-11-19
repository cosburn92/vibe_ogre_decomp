#include "common.h"

inline void func_80080970(u8 *dst, u8 *src, s32 n) {
    u8 *end = src + n;

    while (src != end) {
        *dst++ = *src++;
    }
}

#ifdef NON_MATCHING
/* Only differs by a t0/a3 register swap between t and s. */
/* Copies 8 bytes at a time when both pointers are 8-byte aligned */
void func_80080998(u8 *dst, u8 *src, u32 n) {
    register u64 *s;
    u64 *d;
    u32 t;

    t = (u32)dst;
    if (t & 7) {
        func_80080970(dst, src, n);
        return;
    }
    t = (u32)src;
    if (t & 7) {
        func_80080970(dst, (u8 *)t, n);
        return;
    }
    s = (u64 *)src;
    d = (u64 *)dst;
    t = n >> 3;
    t = (u32)(s + t);
    while (t != (u32)s) {
        *d++ = *s++;
    }
    t = n & 7;
    if (t != 0) {
        func_80080970((u8 *)d, (u8 *)s, t);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/10D70", func_80080998);
#endif
