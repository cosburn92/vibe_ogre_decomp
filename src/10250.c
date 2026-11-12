#include "common.h"

f32 sqrtf(f32);

f32 *func_8007FE50(f32 *dst, f32 *src) {
    f32 x = src[0];
    f32 y = src[1];
    f32 z = src[2];
    dst[0] = x; dst[1] = y; dst[2] = z;
    return dst;
}

#ifdef NON_MATCHING
/* distance between two points
 * Only the scheduling differs: the original sinks the prologue (addiu sp / sw ra)
 * down next to the NaN-fallback sqrtf call, which this cc1 never does. */
f32 func_8007FE70(f32 *a, f32 *b) {
    f32 dx = a[0] - b[0];
    f32 dy = a[1] - b[1];
    f32 dz = a[2] - b[2];
    return sqrtf(dx * dx + dy * dy + dz * dz);
}
#else
INCLUDE_ASM("asm/nonmatchings/10250", func_8007FE70);
#endif
