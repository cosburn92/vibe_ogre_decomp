#include "common.h"

/* a *= s */
f32 *func_80080190(f32 *a, f32 s) {
    f32 x = a[0] * s;
    f32 y = a[1] * s;
    f32 z = a[2] * s;

    a[0] = x;
    a[1] = y;
    a[2] = z;
    return a;
}
