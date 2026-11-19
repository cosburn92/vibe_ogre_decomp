#include "common.h"
#include "scene.h"

/* ovl_1A2C20: camera move / screen colour fade controller */

typedef struct {
    s32 data[0x16];
} Camera;

typedef struct {
    /* 0x00 */ Camera *cam;
    /* 0x04 */ Camera *saved;
} CamSave;

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x04 */ CamSave cs;
    /* 0x0C */ void *asset;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1C */ f32 scaleX;
    /* 0x20 */ f32 scaleY;
    /* 0x24 */ u8 unk24[0xC];
    /* 0x30 */ void *unk30;
    /* 0x34 */ u8 unk34[6];
    /* 0x3A */ s16 alpha;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ u8 unk44[0x10];
} FadeCtx; /* size 0x54 */

extern u16 *D_801AB850;
extern u8 D_800EB0B0[];
extern Camera *D_8018F58C;
extern u8 D_8018F53C;
extern s32 D_8018F548; /* x */
extern s32 D_8018F54C; /* y */
extern u8 D_8018F550;  /* r */
extern u8 D_8018F551;  /* g */
extern u8 D_8018F552;  /* b */
extern u8 D_802167E0_ovl_1A2C20[];
extern FadeCtx *D_80216BE0_ovl_1A2C20;
extern u8 D_80216BE4_ovl_1A2C20;
extern s32 D_80216BE8_ovl_1A2C20; /* finished channels */
extern s32 D_80216EF8_ovl_1A2C20;
extern s32 D_80216EFC_ovl_1A2C20;
extern s32 D_80216F00_ovl_1A2C20;
extern u16 D_80216F70_ovl_1A2C20;
extern s32 D_80216F74_ovl_1A2C20; /* target x */
extern s32 D_80216F78_ovl_1A2C20; /* target y */
extern u8 D_80216F7C_ovl_1A2C20;  /* target r */
extern u8 D_80216F7D_ovl_1A2C20;  /* target g */
extern u8 D_80216F7E_ovl_1A2C20;  /* target b */
extern s32 D_80216F80_ovl_1A2C20; /* x step */
extern s32 D_80216F84_ovl_1A2C20; /* y step */
extern s8 D_80216F88_ovl_1A2C20;  /* r step */
extern s8 D_80216F89_ovl_1A2C20;  /* g step */
extern s8 D_80216F8A_ovl_1A2C20;  /* b step */
extern s16 D_80216F8C_ovl_1A2C20;

void *HMalloc(s32 size);
void *HFree(void *p);
void bzero(void *p, s32 n);
void *LoadAsset(u32 handle, ...);
s16 func_801AB0FC(u16 a, s32 b);
void func_800EA6B0(void *ch, s32 a, s32 b, s32 c);
void func_800EA7E4(void *ch, s32 v);
void func_80215B1C_ovl_1A2C20(void);
void func_80215D30_ovl_1A2C20(void);
void func_8021608C_ovl_1A2C20(void);

inline void func_80214F80_ovl_1A2C20(void) {
    D_80216F8C_ovl_1A2C20 = func_801AB0FC(*D_801AB850, 0x3C);
    D_800E82C8[D_80216F8C_ovl_1A2C20].unk89 = 9;
    D_80216F70_ovl_1A2C20 |= 0x20;
    func_800EA7E4(D_800EB0B0, 300);
}

/* Starts a move to (640, 200) and a fade to (r, g, b) over the given number of frames */
void func_80215000_ovl_1A2C20(u8 r, u8 g, u8 b, s32 frames) {
    D_80216BE8_ovl_1A2C20 = 0;
    D_80216F74_ovl_1A2C20 = 640;
    D_80216F78_ovl_1A2C20 = 200;
    D_80216F7C_ovl_1A2C20 = r;
    D_80216F7D_ovl_1A2C20 = g;
    D_80216F7E_ovl_1A2C20 = b;
    if (frames < 0) {
        frames = -frames;
    }
    if (frames > 300) {
        frames = 300;
    }

    /* (sic) the x step is written to the x position */
    D_8018F548 = (D_80216F74_ovl_1A2C20 - D_8018F548) / frames;
    if (D_8018F548 != D_80216F74_ovl_1A2C20 && D_80216F80_ovl_1A2C20 == 0) {
        if (D_8018F548 < D_80216F74_ovl_1A2C20) {
            D_80216F80_ovl_1A2C20 = 1;
        } else {
            D_80216F80_ovl_1A2C20 = -1;
        }
    }

    D_80216F84_ovl_1A2C20 = (D_80216F78_ovl_1A2C20 - D_8018F54C) / frames;
    if (D_80216F78_ovl_1A2C20 != D_8018F54C && D_80216F84_ovl_1A2C20 == 0) {
        if (D_8018F54C < D_80216F78_ovl_1A2C20) {
            D_80216F84_ovl_1A2C20 = 1;
        } else {
            D_80216F84_ovl_1A2C20 = -1;
        }
    }

    D_80216F88_ovl_1A2C20 = ((s8)D_80216F7C_ovl_1A2C20 - (s8)D_8018F550) / (frames + 10);
    if (D_80216F7C_ovl_1A2C20 != D_8018F550 && D_80216F88_ovl_1A2C20 == 0) {
        if (D_8018F550 < D_80216F7C_ovl_1A2C20) {
            D_80216F88_ovl_1A2C20 = 1;
        } else {
            D_80216F88_ovl_1A2C20 = -1;
        }
    }

    D_80216F89_ovl_1A2C20 = ((s8)D_80216F7D_ovl_1A2C20 - (s8)D_8018F551) / frames;
    if (D_80216F7D_ovl_1A2C20 != D_8018F551 && D_80216F89_ovl_1A2C20 == 0) {
        if (D_8018F551 < D_80216F7D_ovl_1A2C20) {
            D_80216F89_ovl_1A2C20 = 1;
        } else {
            D_80216F89_ovl_1A2C20 = -1;
        }
    }

    D_80216F8A_ovl_1A2C20 = ((s8)D_80216F7E_ovl_1A2C20 - (s8)D_8018F552) / frames;
    if (D_80216F7E_ovl_1A2C20 != D_8018F552 && D_80216F8A_ovl_1A2C20 == 0) {
        if (D_8018F552 < D_80216F7E_ovl_1A2C20) {
            D_80216F8A_ovl_1A2C20 = 1;
        } else {
            D_80216F8A_ovl_1A2C20 = -1;
        }
    }
    D_8018F53C = 1;
}

/* Advances the move and fade; returns whether all five channels arrived */
s32 func_80215298_ovl_1A2C20(void) {
    D_8018F548 += D_80216F80_ovl_1A2C20;
    if (D_80216F80_ovl_1A2C20 >= 0) {
        if (D_8018F548 >= D_80216F74_ovl_1A2C20) {
            D_8018F548 = D_80216F74_ovl_1A2C20;
            D_80216BE8_ovl_1A2C20++;
        }
    } else if (D_8018F548 < D_80216F74_ovl_1A2C20) {
        D_8018F548 = D_80216F74_ovl_1A2C20;
        D_80216BE8_ovl_1A2C20++;
    }

    D_8018F54C += D_80216F84_ovl_1A2C20;
    if (D_80216F84_ovl_1A2C20 >= 0) {
        if (D_8018F54C >= D_80216F78_ovl_1A2C20) {
            D_8018F54C = D_80216F78_ovl_1A2C20;
            D_80216BE8_ovl_1A2C20++;
        }
    } else if (D_8018F54C < D_80216F78_ovl_1A2C20) {
        D_8018F54C = D_80216F78_ovl_1A2C20;
        D_80216BE8_ovl_1A2C20++;
    }

    D_8018F550 += D_80216F88_ovl_1A2C20;
    if (D_80216F88_ovl_1A2C20 >= 0) {
        if (D_8018F550 >= D_80216F7C_ovl_1A2C20) {
            D_8018F550 = D_80216F7C_ovl_1A2C20;
            D_80216BE8_ovl_1A2C20++;
        }
    } else if (D_8018F550 < D_80216F7C_ovl_1A2C20) {
        D_8018F550 = D_80216F7C_ovl_1A2C20;
        D_80216BE8_ovl_1A2C20++;
    }

    D_8018F551 += D_80216F89_ovl_1A2C20;
    if (D_80216F89_ovl_1A2C20 >= 0) {
        if (D_8018F551 >= D_80216F7D_ovl_1A2C20) {
            D_8018F551 = D_80216F7D_ovl_1A2C20;
            D_80216BE8_ovl_1A2C20++;
        }
    } else if (D_8018F551 < D_80216F7D_ovl_1A2C20) {
        D_8018F551 = D_80216F7D_ovl_1A2C20;
        D_80216BE8_ovl_1A2C20++;
    }

    D_8018F552 += D_80216F8A_ovl_1A2C20;
    if (D_80216F8A_ovl_1A2C20 >= 0) {
        if (D_8018F552 >= D_80216F7E_ovl_1A2C20) {
            D_8018F552 = D_80216F7E_ovl_1A2C20;
            D_80216BE8_ovl_1A2C20++;
        }
    } else if (D_8018F552 < D_80216F7E_ovl_1A2C20) {
        D_8018F552 = D_80216F7E_ovl_1A2C20;
        D_80216BE8_ovl_1A2C20++;
    }

    return D_80216BE8_ovl_1A2C20 >= 5;
}

#ifdef NON_MATCHING
/* Instruction scheduling around the LoadAsset call differs. */
void func_802154E0_ovl_1A2C20(void) {
    FadeCtx *ctx;

    D_80216BE0_ovl_1A2C20 = HMalloc(sizeof(FadeCtx));
    bzero(D_80216BE0_ovl_1A2C20, sizeof(FadeCtx));
    ctx = D_80216BE0_ovl_1A2C20;
    ctx->cs.saved = HMalloc(sizeof(Camera));
    ctx->cs.cam = D_8018F58C;
    *ctx->cs.saved = *D_8018F58C;
    ctx = D_80216BE0_ovl_1A2C20;
    ctx->asset = LoadAsset(0x218E9B4, 0x19, -3, 2);
    ctx->unk18 = 0x22;
    ctx->unk16 = 0;
    ctx->unk10 = 0;
    ctx->unk12 = 0;
    ctx->unk14 = 0;
    D_80216BE0_ovl_1A2C20->unk30 = D_802167E0_ovl_1A2C20;
    D_80216BE0_ovl_1A2C20->alpha = 0xFF;
    D_80216BE0_ovl_1A2C20->unk3C = 1.0f;
    D_80216BE0_ovl_1A2C20->unk40 = 1.0f;
    D_80216BE0_ovl_1A2C20->unk00 = -0x2D;
    D_80216F70_ovl_1A2C20 ^= D_80216F70_ovl_1A2C20;
    func_800EA6B0(D_800EB0B0, 11, 10, D_80216F70_ovl_1A2C20);
    func_80215000_ovl_1A2C20(0x1F, 0x1F, 0x1F, 120);
}
#else
INCLUDE_ASM("asm/nonmatchings/1A2C20", func_802154E0_ovl_1A2C20);
#endif

void func_8021562C_ovl_1A2C20(void) {
    CamSave *cs = &D_80216BE0_ovl_1A2C20->cs;

    *cs->cam = *cs->saved;
    HFree(cs->saved);
    HFree(D_80216BE0_ovl_1A2C20);
    D_80216BE0_ovl_1A2C20 = NULL;
    D_80216BE4_ovl_1A2C20 = 0;
}

inline s32 func_802156B8_ovl_1A2C20(void) {
    s32 t;
    f32 sx;
    f32 sy;

    if (!(D_80216F70_ovl_1A2C20 & 1)) {
        return 0;
    }
    t = D_80216EF8_ovl_1A2C20;
    sx = 1.45 - t / 100.0f;
    sy = t / 45.0f;
    if (sx < 1.0f) {
        sx = 1.0f;
    }
    if (1.0f < sy) {
        sy = 1.0f;
    }
    D_80216EF8_ovl_1A2C20 = t + 1;
    D_80216BE0_ovl_1A2C20->scaleX = sx;
    D_80216BE0_ovl_1A2C20->scaleY = sy;
    return 0;
}

inline s32 func_80215764_ovl_1A2C20(void) {
    s32 t;
    f32 scale;

    if (!(D_80216F70_ovl_1A2C20 & 2)) {
        return 0;
    }
    if (D_80216EFC_ovl_1A2C20 >= 120) {
        D_80216EFC_ovl_1A2C20 = 120;
    }
    t = D_80216EFC_ovl_1A2C20;
    scale = 1.2 - t / 100.0f;
    D_80216EFC_ovl_1A2C20 = t + 1;
    D_80216BE0_ovl_1A2C20->unk3C = scale;
    D_80216BE0_ovl_1A2C20->unk40 = scale;
    return 0;
}

void func_802157F0_ovl_1A2C20(void) {
    s16 t = D_80216BE0_ovl_1A2C20->unk00;

    func_80215298_ovl_1A2C20();
    if (t < 45 || D_80216F00_ovl_1A2C20 >= 240) {
        D_80216BE0_ovl_1A2C20->unk00++;
    } else {
        D_80216F00_ovl_1A2C20 = D_80216F00_ovl_1A2C20 + 1;
        if (D_80216F00_ovl_1A2C20 >= 240) {
            func_80214F80_ovl_1A2C20();
        }
    }
    if (t == 0) {
        D_80216F70_ovl_1A2C20 |= 3;
    }
    if (t < 0) {
        D_80216BE4_ovl_1A2C20 = 2;
    } else if (t < 45) {
        D_80216BE4_ovl_1A2C20 = 3;
    } else {
        D_80216BE4_ovl_1A2C20 = 4;
    }
    if (D_80216F70_ovl_1A2C20 & 0x20) {
        D_80216BE0_ovl_1A2C20->unk00++;
        if (t < 115) {
            D_80216BE4_ovl_1A2C20 = 5;
        } else if (t < 160) {
            D_80216BE4_ovl_1A2C20 = 6;
        } else if (D_800E82C8[D_80216F8C_ovl_1A2C20].unk97 & 1) {
            D_80216BE4_ovl_1A2C20 = 1;
        }
    }
    func_802156B8_ovl_1A2C20();
    func_80215764_ovl_1A2C20();
}

void func_80215AC8_ovl_1A2C20(void) {
    *D_80216BE0_ovl_1A2C20->cs.cam = *D_80216BE0_ovl_1A2C20->cs.saved;
}

INCLUDE_ASM("asm/nonmatchings/1A2C20", func_80215B1C_ovl_1A2C20);

INCLUDE_ASM("asm/nonmatchings/1A2C20", func_80215D30_ovl_1A2C20);

INCLUDE_ASM("asm/nonmatchings/1A2C20", func_8021608C_ovl_1A2C20);

void func_80216380_ovl_1A2C20(void) {
    func_80215B1C_ovl_1A2C20();
    func_8021608C_ovl_1A2C20();
    func_80215D30_ovl_1A2C20();
}

u8 func_802163AC_ovl_1A2C20(void) {
    return D_80216BE4_ovl_1A2C20;
}

INCLUDE_ASM("asm/nonmatchings/1A2C20", func_802163B8_ovl_1A2C20);
