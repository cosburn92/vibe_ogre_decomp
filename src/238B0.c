#include "common.h"
#include "libultra.h"

/* libultra libc sprintf.c */

void *memcpy(void *s1, const void *s2, u32 n);
s32 _Printf(void *(*prout)(void *, const char *, u32), char *arg, const char *fmt, va_list args);
void *proutSprintf(void *dst, const char *src, u32 count);

s32 sprintf(char *dst, const char *fmt, ...) {
    s32 ans;
    va_list ap;

    va_start(ap, fmt);
    ans = _Printf(proutSprintf, dst, fmt, ap);
    if (ans >= 0) {
        dst[ans] = 0;
    }
    va_end(ap);
    return ans;
}

void *proutSprintf(void *dst, const char *src, u32 count) {
    return (char *)memcpy((u8 *)dst, (u8 *)src, count) + count;
}
