#ifndef FADE_H
#define FADE_H

#include "common.h"

/* Linear 0..255 fade, stepped once per frame. */
typedef struct Fade {
    /* 0x00 */ f32 cur;
    /* 0x04 */ f32 start;
    /* 0x08 */ f32 end;
    /* 0x0C */ u8 dir;    /* nonzero: counting down */
    /* 0x10 */ f32 step;
    /* 0x14 */ s32 r;     /* low bytes used as the RGB of the fade colour */
    /* 0x18 */ s32 g;
    /* 0x1C */ s32 b;
} Fade; /* size = 0x20 */

#endif /* FADE_H */
