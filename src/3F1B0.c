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





#define CHF(ch, off) (*(s32 *)((u8 *)(ch) + (off)))
extern SoundChannel D_800EB1F0_ovl_03F1B0;
extern SoundChannel D_800EB240_ovl_03F1B0;
extern SoundChannel D_800EB290_ovl_03F1B0;
extern u8 D_80104710_ovl_03F1B0[];
s32 func_80081B08(s32 h);
void func_80081A54(s32 h, s32 a);
void func_80081DF0(void *p);
s32 func_80081770(s32 a);
void func_800EA488_ovl_03F1B0(SoundChannel *ch);
extern u8 D_2B8BA0[];
extern u8 D_2BF250[];
extern u8 D_423FF0[];
extern u8 D_429CD0[];
extern u8 D_4E3140[];
extern u8 D_4F0FB0[];
extern u8 D_80164770_ovl_03F1B0[];
extern u8 D_8010A760_ovl_03F1B0[];
extern s32 D_800EB4F0_ovl_03F1B0[];
extern s32 D_800EB4F4_ovl_03F1B0[];
extern s32 D_800EB2E0_ovl_03F1B0[];
extern s32 D_800EB2E4_ovl_03F1B0[];
extern s32 D_800EB174_ovl_03F1B0;
void PiDmaRead(void *rom, void *ram, s32 size);
void func_80081DB4(void *ram, void *romEnd);
void func_80081F7C(void *bank);
void MusFxBankSetPtrBank(void *fx, void *ptr);
void MusSetMasterVolume(s32 flags, s32 vol);
s32 MusStartSong(void *song);
void func_80081D2C(s32 h, s32 v);
void func_800EA1C8_ovl_03F1B0(SoundChannel *ch);
void func_800EA3BC_ovl_03F1B0(SoundChannel *ch);
void func_800EA3E4_ovl_03F1B0(SoundChannel *ch);
void func_800EA568_ovl_03F1B0(SoundChannel *ch);
#define CH_LOOP(ch) (*(s32 *)&(ch)->unk10[8])
/* --- end decls --- */

/* Loads the sound banks from ROM and registers them with the music library */
#ifdef NON_MATCHING
/* original re-materialises the ROM end addresses instead of keeping them in saved registers */
void func_800E9C20_ovl_03F1B0(void) {
    PiDmaRead(D_2B8BA0, D_80164770_ovl_03F1B0, D_2BF250 - D_2B8BA0);
    PiDmaRead(D_423FF0, D_80104710_ovl_03F1B0, D_429CD0 - D_423FF0);
    PiDmaRead(D_4E3140, D_8010A760_ovl_03F1B0, D_4F0FB0 - D_4E3140);
    func_80081DB4(D_80164770_ovl_03F1B0, D_2BF250);
    func_80081DB4(D_80104710_ovl_03F1B0, D_429CD0);
    func_80081F7C(D_8010A760_ovl_03F1B0);
    MusFxBankSetPtrBank(D_8010A760_ovl_03F1B0, D_80104710_ovl_03F1B0);
}
#else
INCLUDE_ASM("asm/nonmatchings/3F1B0", func_800E9C20_ovl_03F1B0);
#endif

INCLUDE_ASM("asm/nonmatchings/3F1B0", func_800E9CEC_ovl_03F1B0);

INCLUDE_ASM("asm/nonmatchings/3F1B0", func_800E9E34_ovl_03F1B0);

/* Applies a pending request: kinds 1-4 restart, 5/6 stop looping, 7 loops */
void func_800EA0E4_ovl_03F1B0(SoundChannel *ch) {
    if (ch->pending == 0) {
        return;
    }
    func_800EA3BC_ovl_03F1B0(ch);
    switch (ch->unk00) {
        case 1:
        case 2:
        case 3:
        case 4:
            if (ch->saved[1]) {
                func_800EA1C8_ovl_03F1B0(ch);
            }
            if (ch->saved[0]) {
                func_800EA3E4_ovl_03F1B0(ch);
            }
            break;
        case 5:
            CH_LOOP(ch) = 0;
            if (ch->saved[1]) {
                func_800EA1C8_ovl_03F1B0(ch);
            }
            if (ch->saved[0]) {
                func_800EA568_ovl_03F1B0(ch);
            }
            break;
        case 6:
            CH_LOOP(ch) = 0;
            if (ch->saved[1]) {
                func_800EA1C8_ovl_03F1B0(ch);
            }
            if (ch->saved[0]) {
                func_800EA568_ovl_03F1B0(ch);
            }
            break;
        case 7:
            CH_LOOP(ch) = 1;
            if (ch->saved[1]) {
                func_800EA1C8_ovl_03F1B0(ch);
            }
            if (ch->saved[0]) {
                func_800EA568_ovl_03F1B0(ch);
            }
            break;
    }
    ch->pending = 0;
}

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

#ifdef NON_MATCHING
/* saved[0] load scheduled before the param store */
void func_800EA3E4_ovl_03F1B0(SoundChannel *ch) {
    s32 v;

    if (!func_80081B08(ch->handle)) {
        D_800EB0B0_ovl_03F1B0[0].unk38 = 0;
        func_800EA488_ovl_03F1B0(ch);
        return;
    }
    if (ch->unk38 == 0) {
        if (ch->saved[2] != 0) {
            func_80081A54(ch->handle, ch->saved[2]);
            v = ch->saved[2] + 3;
        } else {
            func_80081A54(ch->handle, 1);
            v = 3;
        }
        CHF(ch, 0x3C) = v;
        ch->unk38 = 2;
        CHF(ch, 0x40) = ch->saved[0];
    } else {
        CHF(ch, 0x40) = ch->saved[0];
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/3F1B0", func_800EA3E4_ovl_03F1B0);
#endif

/* Loads song saved[0] (1-based) from ROM into the channel buffer and starts it */
#ifdef NON_MATCHING
/* channel/index saved registers assigned differently */
void func_800EA488_ovl_03F1B0(SoundChannel *ch) {
    s32 k = ch->saved[0] - 1;

    if (func_80081B08(ch->handle)) {
        func_80081A54(ch->handle, 0);
    }
    PiDmaRead((void *)D_800EB4F0_ovl_03F1B0[k * 2], (void *)CHF(ch, 0x48), D_800EB4F4_ovl_03F1B0[k * 2] - D_800EB4F0_ovl_03F1B0[k * 2] + 4);
    MusSetMasterVolume(2, D_800EB2E0_ovl_03F1B0[k * 2]);
    if (&ch->handle != &D_800EB174_ovl_03F1B0) {
        func_80081DF0(D_80104710_ovl_03F1B0);
    }
    ch->handle = MusStartSong((void *)CHF(ch, 0x48));
    func_80081D2C(ch->handle, D_800EB2E4_ovl_03F1B0[k * 2]);
    CHF(ch, 0x20) = ch->saved[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/3F1B0", func_800EA488_ovl_03F1B0);
#endif

void func_800EA568_ovl_03F1B0(SoundChannel *ch) {
    if (CHF(ch, 0x18) != 0) {
        if (func_80081B08(ch->handle)) {
            func_80081A54(ch->handle, 0);
        }
    } else if (ch->unk28 != -1 && func_80081B08(ch->unk28)) {
        func_80081A54(ch->unk28, 0);
    }
    ch->unk28 = ch->handle;
    func_80081DF0(D_80104710_ovl_03F1B0);
    ch->handle = func_80081770(ch->saved[0] - 1);
    CHF(ch, 0x20) = ch->saved[0];
}

/* Starts sound id on channel ch: effect channels (4, 5, none) play directly, channel 6 stops first, music channels queue it */
void SoundPlay(SoundChannel *ch, s32 id) {
    if (ch == &D_800EB1F0_ovl_03F1B0 || ch == &D_800EB240_ovl_03F1B0 || ch == NULL) {
        func_800EA924_ovl_03F1B0(ch, 1, id, 0x4000);
    } else if (ch == &D_800EB290_ovl_03F1B0) {
        func_800EA924_ovl_03F1B0(ch, 2, 0, 0x4000);
        func_800EA924_ovl_03F1B0(ch, 1, id, 0x4000);
    } else {
        ch->request = id + 1;
        ch->fade = 4;
        ch->pending = 1;
    }
}

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
