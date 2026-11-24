#ifndef SCENE_H
#define SCENE_H

#include "common.h"

/* Scene slots: six 0xA8-byte records at D_800E82C8, flag 0x8000 = in use. */
typedef struct {
    /* 0x00 */ u16 flags;
    /* 0x02 */ u8 flags2; /* 0x10: moved up 0x1C lines */
    /* 0x03 */ u8 flags3;
    /* 0x04 */ u8 unk04[2];
    /* 0x06 */ s16 x;
    /* 0x08 */ s16 y;
    /* 0x0A */ s16 x2;
    /* 0x0C */ s16 y2;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ void *owner;
    /* 0x14 */ void (*update)(s32 slot);
    /* 0x18 */ void (*draw)(s32 slot);
    /* 0x1C */ void (*exit)(s32 slot);
    /* 0x20 */ u16 size; /* bytes of D_800E91D0 saved in data between runs */
    /* 0x22 */ u8 unk22[2];
    /* 0x24 */ u8 *data;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ u8 unk2C[0xC];
    /* 0x38 */ void *slotsA[10];
    /* 0x60 */ void *slotsB[10];
    /* 0x88 */ u8 unk88;
    /* 0x89 */ u8 unk89;
    /* 0x8A */ u8 unk8A;
    /* 0x8B */ u8 unk8B;
    /* 0x8C */ u8 unk8C;
    /* 0x8D */ u8 unk8D;
    /* 0x8E */ u8 unk8E;
    /* 0x8F */ u8 unk8F;
    /* 0x90 */ u8 unk90[4];
    /* 0x94 */ u8 unk94;
    /* 0x95 */ u8 unk95;
    /* 0x96 */ u8 unk96;
    /* 0x97 */ u8 unk97;
    /* 0x98 */ void *unk98; /* display list run when flags3 & 2 */
    /* 0x9C */ u8 unk9C[4];
    /* 0xA0 */ u8 unkA0;
    /* 0xA1 */ u8 unkA1;
    /* 0xA2 */ s16 parent;
    /* 0xA4 */ u8 unkA4[4];
} Scene; /* size 0xA8 */

extern Scene D_800E82C8[];

#endif /* SCENE_H */
