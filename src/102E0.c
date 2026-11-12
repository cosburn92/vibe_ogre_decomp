#include "common.h"

/* out = a x b */
float *func_8007FEE0(float *out, float *a, float *b) {
    float x = a[1] * b[2] - b[1] * a[2];
    float y = b[0] * a[2] - a[0] * b[2];
    float z = a[0] * b[1] - b[0] * a[1];
    out[0] = x; out[1] = y; out[2] = z;
    return out;
}
