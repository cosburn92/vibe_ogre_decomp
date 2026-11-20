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

typedef struct {
    u32 w0;
    u32 w1;
} Gfx;
#include "gbi_ultra.h"

/* Appends a full-screen fill in colour (r, g, b) at alpha f->a to the display list at *pp */
void func_8007FB60(Gfx **pp, Fade *f) {
    Gfx *g = *pp;

    gDPPipeSync(g++);
    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0);
    gDPPipeSync(g++);
    {
        Gfx *_g = g++;

        _g->w0 = 0xD9000000;
        _g->w1 = 0;
    }
    gDPSetPrimColor(g++, 0, 0, f->r, f->g, f->b, (u32)f->cur);
    {
        Gfx *_g = g++;

        _g->w0 = 0xFCFFFFFF;
        _g->w1 = 0xFFFDF6FB;
    }
    {
        Gfx *_g = g++;

        _g->w0 = 0xE200001C;
        _g->w1 = 0x005041C8;
    }
    gDPPipeSync(g++);
    gSPTextureRectangle(g++, 0, 0, 319 << 2, 239 << 2, 0, 0, 0, 0, 0);
    gDPPipeSync(g++);
    *pp = g;
}
