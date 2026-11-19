#ifndef GU_H
#define GU_H

/* libultra gu declarations */

typedef union {
    s32 m[4][4];
    s64 force_structure_alignment;
} Mtx;

typedef f32 MtxF[4][4];

typedef struct {
    /* 0x00 */ u8 col[3];
    /* 0x03 */ s8 pad1;
    /* 0x04 */ u8 colc[3];
    /* 0x07 */ s8 pad2;
    /* 0x08 */ s8 dir[3];
    /* 0x0B */ s8 pad3;
} Light_t;

typedef union {
    Light_t l;
    s64 force_structure_alignment[2];
} Light;

typedef struct {
    Light l[2];
} LookAt;

typedef union {
    struct {
        s32 x1, y1, x2, y2;
    } h;
    s32 force_structure_alignment[4];
} Hilite;

#define FTOFRAC8(x) ((s32)MIN(((x) * (128.0f)), 127.0f) & 0xFF)
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

void guMtxIdentF(f32 mf[4][4]);
void guMtxF2L(f32 mf[4][4], Mtx *m);
f32 sqrtf(f32 x);
f32 sinf(f32 x);
f32 cosf(f32 x);

#endif
