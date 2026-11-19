#include "common.h"

s32 func_8009C7CC(void);

/* Uniform random double in [0, 1) built from three calls to func_8009C7CC. */
f64 func_800808F0(void) {
    u32 a = func_8009C7CC();
    u32 b = func_8009C7CC();
    u32 c = func_8009C7CC();

    return (f64)(((a << 18) & 0xC000000) | (b << 15) | c) * (1.0 / 4294967296.0);
}
