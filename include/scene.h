#ifndef SCENE_H
#define SCENE_H

#include "common.h"

/* Scene slots: six 0xA8-byte records at D_800E82C8, flag 0x8000 = in use. */
typedef struct {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u8 flags2; /* 0x10: moved up 0x1C lines */
    /* 0x03 */ u8 unk03[3];
    /* 0x06 */ s16 x;
    /* 0x08 */ s16 y;
    /* 0x0A */ s16 x2;
    /* 0x0C */ s16 y2;
    /* 0x0E */ u8 unk0E[2];
    /* 0x10 */ void *owner;
    /* 0x14 */ u8 unk14[0x14];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ u8 unk2C[0xC];
    /* 0x38 */ void *slotsA[10];
    /* 0x60 */ void *slotsB[10];
    /* 0x88 */ u8 unk88[0x20];
} Scene; /* size 0xA8 */

extern Scene D_800E82C8[];

#endif /* SCENE_H */
