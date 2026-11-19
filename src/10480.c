#include "common.h"

/* out = a * s */
f32 *func_80080080(f32 *out, f32 *a, f32 s) {
    f32 x = a[0] * s;
    f32 y = a[1] * s;
    f32 z = a[2] * s;

    out[0] = x;
    out[1] = y;
    out[2] = z;
    return out;
}
