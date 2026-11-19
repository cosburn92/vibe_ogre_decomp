#include "common.h"

/* a -= b */
f32 *func_80080150(f32 *a, f32 *b) {
    f32 x = a[0] - b[0];
    f32 y = a[1] - b[1];
    f32 z = a[2] - b[2];

    a[0] = x;
    a[1] = y;
    a[2] = z;
    return a;
}
