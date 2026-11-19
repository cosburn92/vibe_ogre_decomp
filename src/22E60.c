#include "common.h"

/* libultra random.c */

extern u32 D_800AA740; /* xseed */

u32 guRandom(void) {
    u32 x;

    x = (D_800AA740 << 2) + 2;
    x *= (x + 1);
    x = x >> 2;
    D_800AA740 = x;
    return x;
}
