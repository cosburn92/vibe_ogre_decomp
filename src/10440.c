#include "common.h"

/* out = a - b */
f32 *func_80080040(f32 *out, f32 *a, f32 *b) {
    f32 x = a[0] - b[0];
    f32 y = a[1] - b[1];
    f32 z = a[2] - b[2];

    out[0] = x;
    out[1] = y;
    out[2] = z;
    return out;
}
