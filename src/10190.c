#include "common.h"

f64 sqrt(f64);
f64 func_800808F0(void);   /* uniform random double */
f64 func_8009CCF0(f64);    /* log */
f64 func_8009CAF0(f64);
f64 func_8009C9A0(f64);

extern s32 D_800A88E0;     /* nonzero: a cached value is pending */
extern f64 D_800B17A0;     /* radius */
extern f64 D_800B17A8;     /* angle */

/* Normally distributed random number (Box-Muller); produces values in pairs. */
f64 func_8007FD90(void) {
    if (D_800A88E0 == 0) {
        D_800A88E0 = 1;
        D_800B17A0 = sqrt(func_8009CCF0(1.0 - func_800808F0()) * -2.0);
        D_800B17A8 = func_800808F0() * 6.283185307179586;
        return D_800B17A0 * func_8009CAF0(D_800B17A8);
    } else {
        D_800A88E0 = 0;
        return D_800B17A0 * func_8009C9A0(D_800B17A8);
    }
}
