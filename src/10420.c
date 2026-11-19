#include "common.h"

/* v = (x, y, z) */
f32 *func_80080020(f32 *v, f32 x, f32 y, f32 z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    return v;
}
