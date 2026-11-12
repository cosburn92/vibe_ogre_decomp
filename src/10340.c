#include "common.h"

f32 func_80080100(f32 *v);

/* dot product */
f32 func_8007FF40(f32 *a, f32 *b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

/* out = v / |v| */
f32 *func_8007FF70(f32 *out, f32 *v) {
    f32 len = func_80080100(v);
    f32 x = v[0] / len;
    f32 y = v[1] / len;
    f32 z = v[2] / len;
    out[0] = x; out[1] = y; out[2] = z;
    return out;
}
