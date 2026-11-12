#include "common.h"

/* Sound channel (0x50 bytes; seven of them at D_800EB0B0, effects channel at D_800EB1F0). */
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 request;
    /* 0x08 */ s32 command;
    /* 0x0C */ s32 fade;
    /* 0x10 */ u8 unk10[0x14];
    /* 0x24 */ s32 handle;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 saved[3];
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 param;
    /* 0x40 */ u8 unk40[0xC];
    /* 0x4C */ s32 pending;
} SoundChannel;

extern SoundChannel D_800EB0B0_ovl_03F1B0[];
extern s32 D_80164760_ovl_03F1B0;
s32 func_800EA924_ovl_03F1B0(SoundChannel *ch, s32 a, u16 b, s32 c);
void func_80081908(s32 a, s32 b);
void func_80081B08(s32 handle);





INCLUDE_ASM("asm/nonmatchings/3F1B0", func_800E9C20_ovl_03F1B0);

INCLUDE_ASM("asm/nonmatchings/3F1B0", func_800E9CEC_ovl_03F1B0);

INCLUDE_ASM("asm/nonmatchings/3F1B0", func_800E9E34_ovl_03F1B0);

INCLUDE_ASM("asm/nonmatchings/3F1B0", func_800EA0E4_ovl_03F1B0);

INCLUDE_ASM("asm/nonmatchings/3F1B0", func_800EA1C8_ovl_03F1B0);

void func_800EA3BC_ovl_03F1B0(SoundChannel *ch) {
    s32 a = ch->request;
    s32 b = ch->command;
    s32 c = ch->fade;

    ch->request = 0;
    ch->command = 0;
    ch->fade = 0;
    ch->saved[0] = a;
    ch->saved[1] = b;
    ch->saved[2] = c;
}

INCLUDE_ASM("asm/nonmatchings/3F1B0", func_800EA3E4_ovl_03F1B0);

INCLUDE_ASM("asm/nonmatchings/3F1B0", func_800EA488_ovl_03F1B0);

INCLUDE_ASM("asm/nonmatchings/3F1B0", func_800EA568_ovl_03F1B0);

INCLUDE_ASM("asm/nonmatchings/3F1B0", SoundPlay);

void SoundPlayFade(SoundChannel *ch, s32 id, s32 fade) {
    ch->request = id + 1;
    ch->fade = fade;
    ch->pending = 1;
}

void func_800EA6C8_ovl_03F1B0(SoundChannel *ch) {
    if (!func_800EA924_ovl_03F1B0(ch, 2, 0, 0x4000)) {
        ch->command = 5;
        ch->param = 4;
        ch->pending = 1;
    }
}

void func_800EA714_ovl_03F1B0(void) {
    D_800EB0B0_ovl_03F1B0[0].saved[0] = 0;
    D_800EB0B0_ovl_03F1B0[1].saved[0] = 0;
    D_800EB0B0_ovl_03F1B0[2].saved[0] = 0;
    D_800EB0B0_ovl_03F1B0[3].saved[0] = 0;
    D_800EB0B0_ovl_03F1B0[4].saved[0] = 0;
    D_800EB0B0_ovl_03F1B0[5].saved[0] = 0;
    D_800EB0B0_ovl_03F1B0[6].saved[0] = 0;
    func_80081908(3, 0);
}

void func_800EA76C_ovl_03F1B0(void) {
    D_800EB0B0_ovl_03F1B0[0].saved[0] = 0;
    D_800EB0B0_ovl_03F1B0[1].saved[0] = 0;
    D_800EB0B0_ovl_03F1B0[2].saved[0] = 0;
    D_800EB0B0_ovl_03F1B0[3].saved[0] = 0;
    func_80081908(2, 0);
}

void func_800EA7AC_ovl_03F1B0(void) {
    D_800EB0B0_ovl_03F1B0[4].saved[0] = 0;
    D_800EB0B0_ovl_03F1B0[5].saved[0] = 0;
    D_800EB0B0_ovl_03F1B0[6].saved[0] = 0;
    func_80081908(1, 0);
}

void func_800EA7E4_ovl_03F1B0(SoundChannel *ch, s32 v) {
    if (!func_800EA924_ovl_03F1B0(ch, 2, v, 0x4000)) {
        ch->command = 5;
        ch->param = v;
        ch->pending = 1;
    }
}

void func_800EA838_ovl_03F1B0(SoundChannel *ch, s32 param) {
    ch->command = 2;
    ch->param = param;
    ch->pending = 1;
}

void func_800EA850_ovl_03F1B0(SoundChannel *ch) {
    func_80081B08(ch->handle);
}

void func_800EA86C_ovl_03F1B0(SoundChannel *ch, s32 param) {
    ch->command = 11;
    ch->param = param;
    ch->pending = 1;
}

void func_800EA884_ovl_03F1B0(SoundChannel *ch, s32 param) {
    ch->command = 3;
    ch->param = param;
    ch->pending = 1;
}

void func_800EA89C_ovl_03F1B0(SoundChannel *ch, s32 param) {
    ch->command = 9;
    ch->param = param;
    ch->pending = 1;
}

void func_800EA8B4_ovl_03F1B0(SoundChannel *ch, s32 param) {
    ch->command = 12;
    ch->param = param;
    ch->pending = 1;
}

void func_800EA8CC_ovl_03F1B0(s32 v) {
    D_80164760_ovl_03F1B0 = v;
}
