#include "common.h"

/* 10500 */

f32 sqrtf(f32);

#ifdef NON_MATCHING
/* Length of a 3D vector
 * Same size; only the scheduling differs: the original sinks the prologue (addiu sp / sw ra)
 * down next to the NaN-fallback sqrtf call, as in func_8007FE70. */
f32 func_80080100(f32 *v) {
    return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}
#else
INCLUDE_ASM("asm/nonmatchings/10500", func_80080100);
#endif
