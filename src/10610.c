#include "common.h"

/* out = (a * wb + b * wa) / (wa + wb): weighted blend of two points */
f32 *func_80080210(f32 *out, f32 *a, f32 *b, f32 wa, f32 wb) {
    f32 sum = wa + wb;
    f32 x = (wb * a[0] + wa * b[0]) / sum;
    f32 y = (wb * a[1] + wa * b[1]) / sum;
    f32 z = (wb * a[2] + wa * b[2]) / sum;

    out[0] = x;
    out[1] = y;
    out[2] = z;
    return out;
}
