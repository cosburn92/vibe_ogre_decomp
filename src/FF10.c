#include "common.h"
#include "fade.h"

/* Advance the fade; returns 0xFF once it reaches its end value. */
s32 func_8007FB10(Fade *f) {
    s32 done = 0;

    f->cur += f->step;
    if (f->dir) {
        if (f->cur <= f->end) {
            f->cur = f->end;
            done = 0xFF;
        }
    } else if (f->end <= f->cur) {
        f->cur = f->end;
        done = 0xFF;
    }
    return done;
}

INCLUDE_ASM("asm/nonmatchings/FF10", func_8007FB60);
