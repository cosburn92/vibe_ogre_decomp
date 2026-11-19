#include "common.h"

/* libultra libc ldiv.c */

typedef struct {
    s32 quot;
    s32 rem;
} ldiv_t;

typedef struct {
    s64 quot;
    s64 rem;
} lldiv_t;

ldiv_t ldiv(s32 num, s32 denom) {
    ldiv_t r;

    r.quot = num / denom;
    r.rem = num - denom * r.quot;
    if (r.quot < 0 && r.rem > 0) {
        r.quot++;
        r.rem -= denom;
    }
    return r;
}

lldiv_t lldiv(s64 num, s64 denom) {
    lldiv_t r;

    r.quot = num / denom;
    r.rem = num - denom * r.quot;
    if (r.quot < 0 && r.rem > 0) {
        r.quot++;
        r.rem -= denom;
    }
    return r;
}
