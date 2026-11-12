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

/* Fade between two explicit levels instead of 0 and 255. */
void func_8007FA38(Fade *f, s16 frames, s32 r, s32 g, s32 b, u32 from, u32 to) {
    f->cur = from;
    f->start = from;
    f->end = to;
    if (to < from) {
        f->dir = 1;
    } else {
        f->dir = 0;
    }
    f->step = (f->end - f->start) / frames;
    f->r = r;
    f->g = g;
    f->b = b;
}
