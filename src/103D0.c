#include "common.h"

f32 func_80080100(f32 *v); /* length */

/* v = v / |v| */
f32 *func_8007FFD0(f32 *v) {
    f32 len = func_80080100(v);
    f32 x = v[0] / len;
    f32 y = v[1] / len;
    f32 z = v[2] / len;

    v[0] = x;
    v[1] = y;
    v[2] = z;
    return v;
}
