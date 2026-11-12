#include "common.h"
#include "fade.h"

void func_8007F9C0(Fade *f, u8 dir, s16 frames, s32 r, s32 g, s32 b) {
    f->dir = dir;
    if (dir) {
        f->cur = 255.0f;
    } else {
        f->cur = 0.0f;
    }
    f->start = f->cur;
    f->end = 255.0f - f->cur;
    f->step = (f->end - f->start) / frames;
    f->r = r;
    f->g = g;
    f->b = b;
}

INCLUDE_ASM("asm/nonmatchings/FDC0", func_8007FA38);
