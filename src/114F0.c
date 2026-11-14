#include "common.h"

/* libmus channel state (channel_t, 0x13C bytes); only fields the code here touches are named. */
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ void *pdata;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ f32 vib_amount;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 *ppitchbend;
    /* 0x38 */ u8 *pvolume;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 handle;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ void *unk74;
    /* 0x78 */ void *unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ u8 *pbase;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ u8 *ppitchbendbase;
    /* 0x8C */ u8 *pvolumebase;
    /* 0x90 */ f32 unk90;
    /* 0x94 */ s32 unk94;
    /* 0x98 */ s16 unk98;
    /* 0x9A */ u16 unk9A;
    /* 0x9C */ u16 unk9C;
    /* 0x9E */ s16 unk9E;
    /* 0xA0 */ u16 unkA0;
    /* 0xA2 */ u16 unkA2;
    /* 0xA4 */ u16 unkA4;
    /* 0xA6 */ u16 unkA6;
    /* 0xA8 */ u16 unkA8;
    /* 0xAA */ u16 unkAA;
    /* 0xAC */ u16 length;
    /* 0xAE */ u16 unkAE;
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ u16 unkB2;
    /* 0xB4 */ u16 unkB4;
    /* 0xB6 */ u8 vib_delay;
    /* 0xB7 */ u8 unkB7;
    /* 0xB8 */ u8 porta;
    /* 0xB9 */ u8 unkB9;
    /* 0xBA */ u8 unkBA;
    /* 0xBB */ u8 unkBB;
    /* 0xBC */ u8 unkBC;
    /* 0xBD */ u8 unkBD;
    /* 0xBE */ u8 unkBE;
    /* 0xBF */ u8 unkBF;
    /* 0xC0 */ u8 unkC0;
    /* 0xC1 */ u8 unkC1;
    /* 0xC2 */ u8 unkC2;
    /* 0xC3 */ u8 unkC3;
    /* 0xC4 */ u8 unkC4;
    /* 0xC5 */ u8 unkC5;
    /* 0xC6 */ u8 unkC6;
    /* 0xC7 */ u8 unkC7;
    /* 0xC8 */ u8 unkC8;
    /* 0xC9 */ u8 unkC9;
    /* 0xCA */ u8 unkCA;
    /* 0xCB */ u8 unkCB;
    /* 0xCC */ u8 unkCC;
    /* 0xCD */ u8 padCD[0x1];
    /* 0xCE */ u8 wobble;
    /* 0xCF */ u8 unkCF;
    /* 0xD0 */ u8 unkD0;
    /* 0xD1 */ s8 unkD1;
    /* 0xD2 */ u8 velon;
    /* 0xD3 */ u8 unkD3;
    /* 0xD4 */ u8 unkD4;
    /* 0xD5 */ u8 vib_speed;
    /* 0xD6 */ u8 env;
    /* 0xD7 */ u8 trigger;
    /* 0xD8 */ u8 unkD8;
    /* 0xD9 */ u8 sweep_timer;
    /* 0xDA */ u8 unkDA;
    /* 0xDB */ u8 depth;
    /* 0xDC */ f32 vib_precalc;
    /* 0xE0 */ u8 *loopptr[4];
    /* 0xF0 */ u8 *loopvol[4];
    /* 0x100 */ u8 *looppb[4];
    /* 0x110 */ u16 loopA2[4];
    /* 0x118 */ u16 loopA4[4];
    /* 0x120 */ u8 loopcount[4];
    /* 0x124 */ u8 loopBC[4];
    /* 0x128 */ f32 loop70[4];
    /* 0x138 */ u8 pad138[0x4];
} MusChannel; /* size 0x13C */

typedef struct {
    /* 0x00 */ u8 pad00[0x10];
    /* 0x10 */ s32 flags; /* negative once initialised */
} MusBank;

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 count;
    /* 0x08 */ u8 pad08[4];
    /* 0x0C */ s32 flags;
    /* 0x10 */ void *ptrbank;
    /* 0x14 */ u32 unk14;
    /* 0x18 */ struct {
        u32 ptr;
        u32 unk4;
    } entries[1];
} MusFxBank;

typedef struct {
    u8 b[6];
} MusDrum;

typedef struct {
    /* 0x00 */ u8 pad00[8];
    /* 0x08 */ s32 unk08;
    /* 0x0C */ u8 pad0C[8];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 pad18[4];
    /* 0x1C */ MusDrum *drums;
    /* 0x20 */ s32 unk20;
} MusSong;

typedef struct {
    /* 0x00 */ u8 type;
    /* 0x04 */ s32 value;
} MusCommand;

extern MusCommand *D_800B1850;
extern s32 D_800B184C;
extern s32 D_800B1848;
extern s32 D_800B1844;
void *__MusIntMemMalloc(s32 size);
void func_80083F38(s32 handle, s32 a, s32 b);
void func_80085B5C(void *dst, void *src, s32 n);

typedef struct {
    /* 0x00 */ u8 pad00[0x1C];
    /* 0x1C */ u8 unk1C;
    /* 0x20 */ void *unk20;
} MusSample;
void func_800850C0(MusSample *p);

typedef struct {
    u8 pad00[0x34];
    struct {
        u8 pad00[0x20];
        void *unk20;
        s32 arr[1];
    } *unk34;
} AlGlobalsLike;
extern AlGlobalsLike *alGlobals_800A9E54;
extern AlGlobalsLike *n_alGlobals;
extern AlGlobalsLike *D_800E8298;
void func_80084C98(s32 *p);


extern s16 D_800B181C;
extern s16 D_800B181E;
extern void *D_800B1828;
extern MusBank *D_800B182C;
extern s32 D_800B1830;
extern s32 D_800B1834;
extern MusFxBank *D_800B1838;
extern MusFxBank *D_800B183C;
extern s32 D_800B1840;
extern s32 D_800B1804;
extern MusChannel *D_800B180C;
s32 func_80083B24(MusFxBank *bank, s32 number, s32 volume, s32 pan, s32 priority);
s32 func_80083A74(MusChannel *cp, MusFxBank *bank, s32 number, s32 volume, s32 pan, s32 priority);
extern MusChannel *D_800B1810;
extern s32 D_800B1814;
f32 func_80083378(f32 pitch);
void func_80088380(void *voice, f32 pitch);
extern s32 D_800A9B8C;
extern u8 D_800A99D8[];
s32 func_80083CCC(void *addr);
void MusHandleUnPause(s32 handle);
void func_8008350C(void *bank);
s32 func_80082214(MusCommand *cmd);
s32 ChangeCustomEffect(s32 fx);
s32 func_800836A4(s32 range);
void func_80083738(MusChannel *cp);
extern s32 D_800B1820;
extern s32 D_800B1824;
extern u8 *D_800B1808;
void func_80088550(void *voice);
void func_800884C0(void *voice, void *wave);
extern s32 D_800A9B60;
void func_80084DE0(s32 *fx);
void alFxParam(void *fx, s32 id, void *param);





INCLUDE_ASM("asm/nonmatchings/114F0", func_800810F0);

INCLUDE_ASM("asm/nonmatchings/114F0", func_8008123C);

void MusSetMasterVolume(u32 flags, s32 volume) {
    if (flags & 1) {
        D_800B181C = volume;
    }
    if (flags & 2) {
        D_800B181E = volume;
    }
}

s32 MusStartSong(void *addr) {
    s32 handle = func_80083CCC(addr);

    MusHandleUnPause(handle);
    return handle;
}

INCLUDE_ASM("asm/nonmatchings/114F0", func_80081520);

s32 func_80081770(s32 number) {
    MusFxBank *bank = D_800B183C;
    s32 ret;

    if (bank != NULL) {
        D_800B183C = NULL;
    } else {
        bank = D_800B1838;
        if (bank == NULL) {
            D_800B1828 = NULL;
            return 0;
        }
    }
    if (D_800B1828 == NULL) {
        D_800B1828 = bank->ptrbank;
    }
    ret = func_80083B24(bank, number, 0x80, 0x80, -1);
    D_800B1828 = NULL;
    return ret;
}

s32 func_800817F0(s32 number, s32 volume, s32 pan, s32 restartflag, s32 priority) {
    MusFxBank *bank;
    MusFxBank *next = D_800B183C;
    MusChannel *cp;
    s32 i;
    s32 ret;

    if (next != NULL) {
        bank = next;
        D_800B183C = NULL;
    } else {
        bank = D_800B1838;
        if (bank == NULL) {
            D_800B1828 = NULL;
            return 0;
        }
    }
    if (D_800B1828 == NULL) {
        D_800B1828 = bank->ptrbank;
    }
    if (restartflag) {
        cp = D_800B1810;
        for (i = 4; i < D_800B1804; i++, cp++) {
            if (cp->unkA6 == number && cp->unk78 == bank) {
                if (priority == -1) {
                    priority = bank->entries[number].unk4;
                }
                ret = func_80083A74(cp, bank, number, volume, pan, priority);
                D_800B1828 = NULL;
                return ret;
            }
        }
    }
    ret = func_80083B24(bank, number, volume, pan, priority);
    D_800B1828 = NULL;
    return ret;
}

void func_80081908(u32 flags, s32 speed) {
    s32 i;
    s32 s;
    MusChannel *cp;

    s = speed;
    if (s == 0) {
        s = 1;
    }
    cp = D_800B180C;
    for (i = 0; i < D_800B1804; i++, cp++) {
        if ((cp->unk78 != 0 && (flags & 1)) || (cp->unk78 == 0 && (flags & 2))) {
            if (cp->unk04 != 0 && cp->unk10 == -1) {
                if (cp->unk00 & 1) {
                    cp->unk1C = 1;
                    cp->unk10 = 0;
                    cp->unk00 &= ~1;
                } else {
                    cp->unk1C = s;
                    cp->unk10 = speed;
                }
            }
        }
    }
}

s32 func_800819D4(u32 flags) {
    s32 i;
    s32 n = 0;
    MusChannel *cp = D_800B180C;

    for (i = 0; i < D_800B1804; i++, cp++) {
        if (cp->unk04 != 0) {
            if ((cp->unk78 != 0 && (flags & 1)) || (cp->unk78 == 0 && (flags & 2))) {
                n++;
            }
        }
    }
    return n;
}

#ifdef NON_MATCHING
/* Same code; loop counters get different registers. */
s32 func_80081A54(s32 handle, s32 speed) {
    s32 i, n;
    s32 s;
    MusChannel *cp;

    if (handle == 0) {
        return 0;
    }
    s = speed;
    if (s == 0) {
        s = 1;
    }
    n = 0;
    cp = D_800B180C;
    for (i = 0; i < D_800B1804; i++, cp++) {
        if (cp->handle == handle && cp->unk10 == -1) {
            if (cp->unk00 & 1) {
                cp->unk1C = 1;
                cp->unk10 = 0;
                cp->unk00 &= ~1;
            } else {
                cp->unk1C = s;
                cp->unk10 = speed;
            }
            n++;
        }
    }
    return n;
}
#else
INCLUDE_ASM("asm/nonmatchings/114F0", func_80081A54);
#endif

#ifdef NON_MATCHING
/* Same code; i/cp/count load order differs (register assignment). */
s32 func_80081B08(s32 handle) {
    s32 i, n;

    if (handle == 0) {
        return 0;
    }
    n = 0;
    for (i = 0; i < D_800B1804; i++) {
        n += (D_800B180C[i].handle == handle);
    }
    return n;
}
#else
INCLUDE_ASM("asm/nonmatchings/114F0", func_80081B08);
#endif

s32 func_80081B60(s32 handle, u16 value) {
    s32 i, n;
    MusChannel *cp;

    if (handle == 0) {
        return 0;
    }
    n = 0;
    cp = D_800B180C;
    for (i = 0; i < D_800B1804; i++, cp++) {
        if (cp->handle == handle) {
            cp->unk9E = value;
            n++;
        }
    }
    return n;
}

s32 func_80081BC0(s32 handle, u16 value) {
    s32 i, n;
    MusChannel *cp;

    if (handle == 0) {
        return 0;
    }
    n = 0;
    cp = D_800B180C;
    for (i = 0; i < D_800B1804; i++, cp++) {
        if (cp->handle == handle) {
            n++;
            cp->unkB0 = value;
            cp->unkBE = 0xFF;
        }
    }
    return n;
}

s32 func_80081C30(s32 handle, f32 value) {
    s32 i, n;
    MusChannel *cp;

    if (handle == 0) {
        return 0;
    }
    n = 0;
    cp = D_800B180C;
    for (i = 0; i < D_800B1804; i++, cp++) {
        if (cp->handle == handle) {
            cp->unk30 = value + cp->unk90;
            n++;
        }
    }
    return n;
}

s32 func_80081CA0(s32 handle, s32 tempo) {
    s32 i, n;
    MusChannel *cp;

    if (handle == 0) {
        return 0;
    }
    if (tempo <= 0) {
        tempo = 1;
    } else if (tempo > 0x100) {
        tempo = 0x100;
    }
    n = 0;
    cp = D_800B180C;
    for (i = 0; i < D_800B1804; i++, cp++) {
        if (cp->handle == handle) {
            n++;
            cp->unk98 = tempo;
            cp->unk9C = (cp->unkA8 * tempo) >> 7;
        }
    }
    return n;
}

s32 func_80081D2C(s32 handle, s32 pan) {
    s32 i, n;
    MusChannel *cp;

    if (handle == 0) {
        return 0;
    }
    if (pan < 0) {
        pan = 0;
    } else if (pan >= 0x80) {
        pan = 0x7F;
    }
    n = 0;
    cp = D_800B180C;
    for (i = 0; i < D_800B1804; i++, cp++) {
        if (cp->handle == handle) {
            n++;
            cp->unkCB = pan;
            cp->unkCC = 0xFF;
        }
    }
    return n;
}

void func_80081DB4(void *bank) {
    func_8008350C(bank);
    if (D_800B182C == NULL) {
        D_800B182C = bank;
    }
}

MusBank *func_80081DF0(MusBank *bank) {
    if (bank != NULL && bank->flags < 0) {
        D_800B1828 = bank;
    }
    return D_800B1828;
}

void MusPtrBankSetCurrent(MusBank *bank) {
    if (bank != NULL && bank->flags < 0) {
        D_800B182C = bank;
    }
}

MusBank *func_80081E3C(void) {
    return D_800B182C;
}

s32 func_80081E48(s32 handle) {
    s32 i;
    MusChannel *cp;

    if (handle == 0) {
        return 0;
    }
    cp = D_800B180C;
    for (i = 0; i < D_800B1804; i++, cp++) {
        if (cp->handle == handle) {
            return cp->unk7C;
        }
    }
    return 0;
}

void MusHandlePause(s32 handle) {
    MusCommand cmd;

    cmd.type = 0;
    cmd.value = handle;
    func_80082214(&cmd);
}

void MusHandleUnPause(s32 handle) {
    MusCommand cmd;

    cmd.type = 1;
    cmd.value = handle;
    func_80082214(&cmd);
}

inline s32 MusSetFxType(s32 type) {
    MusCommand cmd;

    cmd.type = 2;
    cmd.value = type;
    D_800B1834 = type;
    return func_80082214(&cmd);
}

void func_80081F20(s32 type) {
    s32 ok = 1;

    if (type == 0) {
        ok = MusSetFxType(D_800B1834);
    }
    if (ok) {
        D_800B1830 = type;
    }
}

#ifdef NON_MATCHING
/* Same code; bank and the index swap registers. */
void func_80081F7C(MusFxBank *bank) {
    u32 base = (u32)bank;
    s32 i;

    if (bank->flags & 1) {
        return;
    }
    if (D_800B1838 == NULL) {
        D_800B1838 = bank;
    }
    bank->flags = 1;
    bank->ptrbank = NULL;
    bank->unk14 = base + bank->unk14;
    for (i = 0; i < bank->unk00; i++) {
        bank->entries[i].ptr = base + bank->entries[i].ptr;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/114F0", func_80081F7C);
#endif

s32 MusFxBankNumberOfEffects(MusFxBank *bank) {
    return bank->count;
}

void func_80082008(MusFxBank *a) {
    D_800B1838 = a;
}

void func_80082014(MusFxBank *a) {
    D_800B183C = a;
}

MusFxBank *func_80082020(void) {
    return D_800B1838;
}

void MusFxBankSetPtrBank(MusFxBank *bank, void *ptrbank) {
    bank->ptrbank = ptrbank;
}

void *MusFxBankGetPtrBank(MusFxBank *bank) {
    return bank->ptrbank;
}

void func_8008203C(s32 a) {
    D_800A9B8C = a;
}

#ifdef NON_MATCHING
/* Same code; count and channel pointer swap registers. */
s32 func_80082048(s32 handle) {
    s32 i;
    MusChannel *cp;

    if (handle != 0) {
        cp = D_800B180C;
        for (i = 0; i < D_800B1804; i++, cp++) {
            if (cp->handle == handle) {
                return ((cp->unk74 != 0) ? (MusSong *)cp->unk74 : (MusSong *)cp->unk78)->unk08;
            }
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/114F0", func_80082048);
#endif

s32 func_800820AC(s32 handle) {
    s32 i;
    MusChannel *cp;

    if (handle == 0) {
        return 0;
    }
    cp = D_800B180C;
    for (i = 0; i < D_800B1804; i++, cp++) {
        if (cp->handle == handle) {
            if (cp->unk74 != 0) {
                return ((MusSong *)cp->unk74)->unk20;
            }
            return ((MusSong *)cp->unk78)->unk14;
        }
    }
    return 0;
}

void func_80082124(s32 a) {
    D_800B1840 = a;
}

void func_80082130(s32 n) {
    if (n < 0x40) {
        n = 0x40;
    } else if (n > 0x400) {
        n = 0x400;
    }
    D_800B1850 = __MusIntMemMalloc(n * 8);
    D_800B184C = n;
    D_800B1848 = 0;
    D_800B1844 = 0;
}

void func_80082194(MusCommand *cmd) {
    switch (cmd->type) {
        case 0:
            func_80083F38(cmd->value, -2, 1);
            break;
        case 1:
            func_80083F38(cmd->value, -2, 0);
            break;
        case 2:
            ChangeCustomEffect(cmd->value);
            break;
    }
}

s32 func_80082214(MusCommand *cmd) {
    s32 next = (D_800B1848 + 1) % D_800B184C;

    if (next == D_800B1844) {
        return 0;
    }
    func_80085B5C(D_800B1850 + D_800B1848, cmd, 8);
    D_800B1848 = next;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/114F0", func_800822AC);

INCLUDE_ASM("asm/nonmatchings/114F0", func_8008259C);

void func_80082AE8(MusChannel *cp, s32 voice) {
    if (cp->unkC9 != 0) {
        func_80088550(D_800B1808 + voice * 0x1C);
    }
    cp->unkC9 = 1;
    func_800884C0(D_800B1808 + voice * 0x1C, cp->pdata);
    cp->pdata = NULL;
}

INCLUDE_ASM("asm/nonmatchings/114F0", func_80082B64);

void func_80082CB8(MusChannel *cp, s32 voice, f32 offset) {
    f32 pitch = cp->unk2C;

    if (cp->porta != 0) {
        if (cp->porta < cp->unkAA) {
            cp->unk50 = pitch;
        } else {
            pitch = cp->unk4C + (pitch - cp->unk4C) / (f32)cp->porta * (f32)cp->unkAA;
            cp->unk50 = pitch;
        }
    }
    pitch += offset + cp->unk24;
    if (pitch != cp->unk28) {
        cp->unk28 = pitch;
        pitch = func_80083378(pitch * (1.0 / 12.0));
        if (pitch > 2.0) {
            pitch = 2.0f;
            cp->unkBB = 0;
        }
        func_80088380(D_800B1808 + voice * 0x1C, pitch);
    }
}

void func_80082DC4(MusChannel *cp) {
    if (cp->unk9A != 0x7FFF) {
        if (cp->unkB2 != 0) {
            cp->unk54 = cp->unk40 + (cp->unkB2 << 8);
        } else {
            cp->unk54 = cp->unk3C - (cp->unkB4 << 8);
        }
    } else {
        cp->unk54 = cp->unk40 + 0x7FFFFFFF;
    }
    cp->unkC3 = 1;
    cp->unkC4 = cp->unkC0;
    cp->unkC5 = cp->unkBF;
}

INCLUDE_ASM("asm/nonmatchings/114F0", func_80082E34);

void __MusIntInitSweep(MusChannel *cp) {
    cp->sweep_timer = 0;
    cp->unk94 = cp->unk40;
    cp->unkDA = cp->unkBD & 0x40;
}

void func_8008302C(MusChannel *cp) {
    u32 t;

    do {
        t = cp->sweep_timer + cp->unkD4;
        cp->unk94 += 0x100;
        if (t < 0x40) {
            cp->sweep_timer = t;
        } else {
            cp->sweep_timer = t & 0x3F;
            t >>= 6;
            if (cp->unkDA == 0) {
                cp->unkBD += t;
                if (cp->unkBD >= 0x80) {
                    cp->unkBD = 0x7F;
                    cp->unkDA = 1;
                }
            } else {
                cp->unkBD -= t;
                if (cp->unkBD >= 0x80 || cp->unkBD == 0) {
                    cp->unkBD = 0;
                    cp->unkDA = 0;
                }
            }
        }
    } while (cp->unk94 - cp->unk0C < 0);
}

f32 func_800830E4(MusChannel *cp) {
    if (--cp->unkD0 == 0) {
        if (cp->unkD1 == 0) {
            cp->unkD1 = cp->unkD8;
            cp->unkD0 = cp->wobble;
        } else {
            cp->unkD1 = 0;
            cp->unkD0 = cp->unkCF;
        }
    }
    return cp->unkD1;
}

f32 sinf(f32);

f32 func_8008313C(MusChannel *cp) {
    s32 t = cp->unkAA - cp->vib_delay;
    f32 r;

    if (t <= 0) {
        r = 0.0f;
    } else {
        r = cp->unk68 = sinf((f32)t * cp->vib_precalc) * cp->vib_amount;
    }
    return r;
}

void func_800831A0(MusChannel *cp) {
    u8 v;

    do {
        cp->unk14 += 0x100;
        if (--cp->unkA2 == 0) {
            v = *cp->pvolume++;
            if (v >= 0x80) {
                cp->unkBC = v & 0x7F;
                v = *cp->pvolume++;
                if (v >= 0x80) {
                    cp->unkA2 = (v & 0x7F) << 8;
                    cp->unkA2 += *cp->pvolume++ + 2;
                } else {
                    cp->unkA2 = v + 2;
                }
            } else {
                cp->unkBC = v;
                cp->unkA2 = 1;
            }
        }
    } while (cp->unk14 - cp->unk0C < 0);
}

void func_80083264(MusChannel *cp) {
    u8 v;

    do {
        cp->unk18 += 0x100;
        if (--cp->unkA4 == 0) {
            v = *cp->ppitchbend++;
            if (v >= 0x80) {
                cp->unk70 = (f32)(v & 0x7F) - 64.0;
                cp->unk24 = cp->unk70 * cp->unk6C;
                v = *cp->ppitchbend++;
                if (v >= 0x80) {
                    cp->unkA4 = (v & 0x7F) << 8;
                    cp->unkA4 += *cp->ppitchbend++ + 2;
                } else {
                    cp->unkA4 = v + 2;
                }
            } else {
                cp->unk70 = (f32)v - 64.0;
                cp->unk24 = cp->unk70 * cp->unk6C;
                cp->unkA4 = 1;
            }
        }
    } while (cp->unk18 - cp->unk0C < 0);
}

INCLUDE_ASM("asm/nonmatchings/114F0", func_80083378);

INCLUDE_ASM("asm/nonmatchings/114F0", func_8008350C);

s32 func_800836A4(s32 range) {
    s32 i;

    for (i = 0; i < 8; i++) {
        u32 t = D_800B1824 & 0x48000000;

        D_800B1824 <<= 1;
        if (t == 0x48000000 || t == 0x08000000) {
            D_800B1824 |= 1;
        }
    }
    return (f32)range * ((f32)D_800B1824 / 65536.0f / 65536.0f);
}

#ifdef NON_MATCHING
/* Same code; the original keeps cp in a2 and 0xFF in a1 (register allocation). */
void func_80083738(MusChannel *cp) {
    u8 old = cp->unkC9;
    u8 *p = (u8 *)cp;
    u32 i;

    cp->unk04 = 0;
    for (i = 0; i < sizeof(MusChannel); i++) {
        *p++ = 0;
    }
    cp->unkCC = 0xFF;
    cp->unkBE = 0xFF;
    cp->unk9C = cp->unkA8 = 0x6000 / D_800B1814;
    cp->unkD3 = 0x7F;
    cp->unkBC = 0x7F;
    cp->unkC1 = 0x7F;
    cp->unkC7 = 0xFF;
    cp->unkC2 = 0x7F;
    cp->unkBD = 0x40;
    cp->unkBF = 1;
    cp->unkC6 = 1;
    cp->unkC8 = 0xF;
    cp->unkA0 = 0xFFFF;
    cp->unk9A = 1;
    cp->unkA2 = 1;
    cp->unkA4 = 1;
    cp->unk10 = -1;
    cp->unk9E = 0x80;
    cp->unkB0 = 0x80;
    cp->unk98 = 0x80;
    cp->unk28 = 99.9f;
    cp->unk6C = 0.03125f;
    cp->unk58 = 1.0f;
    cp->unk5C = 1.0f / 255.0f;
    cp->unk60 = 1.0f / 15.0f;
    cp->unk7C = (s32)(D_800B1828 != NULL ? D_800B1828 : D_800B182C);
    cp->unkC9 = old;
}
#else
INCLUDE_ASM("asm/nonmatchings/114F0", func_80083738);
#endif

INCLUDE_ASM("asm/nonmatchings/114F0", func_80083874);

void func_80083A3C(u32 *p, u32 base, s32 n) {
    s32 i;

    for (i = 0; i < n; i++, p++) {
        if (*p != 0) {
            *p += base;
        }
    }
}

s32 func_80083A74(MusChannel *cp, MusFxBank *bank, s32 number, s32 volume, s32 pan, s32 priority) {
    func_80083738(cp);
    cp->unkA6 = number;
    cp->unk78 = bank;
    cp->unk9E = volume;
    cp->unkB0 = pan;
    cp->handle = D_800B1820++;
    cp->unk48 = priority;
    if (bank->ptrbank != NULL) {
        cp->unk7C = (s32)bank->ptrbank;
    }
    cp->unk04 = (s32)(cp->pbase = (u8 *)bank->entries[number].ptr);
    return cp->handle;
}

INCLUDE_ASM("asm/nonmatchings/114F0", func_80083B24);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80083CCC);

void func_80083F38(s32 handle, s32 and, s32 or) {
    s32 i;
    MusChannel *cp = D_800B180C;

    for (i = 0; i < D_800B1804; i++, cp++) {
        if (cp->handle == handle) {
            cp->unk00 = (cp->unk00 & and) | or;
        }
    }
}

u8 *Fstop(MusChannel *cp, u8 *ptr) {
    cp->pvolume = 0;
    cp->ppitchbend = 0;
    cp->unk74 = 0;
    cp->unk78 = 0;
    cp->handle = 0;
    cp->pdata = NULL;
    return NULL;
}

u8 *func_80083FAC(MusChannel *cp, u8 *ptr) {
    u16 v = *ptr++;

    if (v & 0x80) {
        v = ((v & 0x7F) << 8) | *ptr++;
    }
    cp->unkAE = v;
    return ptr;
}

u8 *func_80083FDC(MusChannel *cp, u8 *ptr) {
    if ((cp->porta = *ptr++) != 0) {
        cp->unk50 = cp->unk2C;
    }
    return ptr;
}

u8 *Fportoff(MusChannel *cp, u8 *ptr) {
    cp->porta = 0;
    return ptr;
}

/* Fenvelope */
u8 *func_80084008(MusChannel *cp, u8 *ptr) {
    u8 v, t;

    v = *ptr++;
    if (v == 0) {
        v = 1;
    }
    cp->unkBF = v;
    cp->unk64 = 0x400 / v;
    cp->unkC0 = *ptr++;
    v = *ptr++;
    cp->unkC6 = v;
    t = *ptr++;
    cp->unk58 = (1.0 / (f32)v) * (f32)(t - cp->unkC0);
    cp->unkC1 = t;
    v = *ptr++;
    cp->unkC7 = v;
    t = *ptr++;
    cp->unk5C = (1.0 / (f32)v) * (f32)(t - cp->unkC1);
    cp->unkC2 = t;
    v = *ptr++;
    cp->unkC8 = v;
    cp->unk60 = 1.0 / (f32)v;
    return ptr;
}

/* Ftempo */
u8 *func_80084130(MusChannel *cp, u8 *ptr) {
    s32 tempo, calc, i;
    MusChannel *cp2;

    tempo = (*ptr++ * 0x6000 / 120) / D_800B1814;
    calc = (tempo * cp->unk98) >> 7;
    if (cp->unk78 != 0) {
        cp->unk9C = tempo;
    } else {
        cp2 = D_800B180C;
        for (i = 0; i < D_800B1804; i++, cp2++) {
            if (cp2->unk74 == cp->unk74) {
                cp2->unkA8 = tempo;
                cp2->unk9C = calc;
            }
        }
    }
    return ptr;
}

u8 *func_80084214(MusChannel *cp, u8 *ptr) {
    cp->unkB4 = *ptr++;
    cp->unkB2 = 0;
    return ptr;
}

u8 *func_80084228(MusChannel *cp, u8 *ptr) {
    u16 v = *ptr++ << 8;

    v |= *ptr++;
    cp->unkB4 = 0;
    cp->unkB2 = v;
    return ptr;
}

/* Fvibup */
u8 *func_8008424C(MusChannel *cp, u8 *ptr) {
    cp->vib_delay = *ptr++;
    cp->vib_speed = *ptr++;
    cp->vib_amount = (f32)*ptr++ / 50.0;
    cp->vib_precalc = 6.2831852 / (f32)cp->vib_speed;
    return ptr;
}

#ifdef NON_MATCHING
/* The original reloads vib_speed right after storing it; GCC here forwards the stored value. */
/* Fvibdown */
u8 *func_800842BC(MusChannel *cp, u8 *ptr) {
    cp->vib_delay = *ptr++;
    cp->vib_speed = *ptr++;
    cp->vib_precalc = 6.2831852 / (f32)cp->vib_speed;
    cp->vib_amount = -(f32)*ptr++ / 50.0;
    return ptr;
}
#else
INCLUDE_ASM("asm/nonmatchings/114F0", func_800842BC);
#endif

u8 *Fviboff(MusChannel *cp, u8 *ptr) {
    cp->vib_speed = 0;
    cp->unk68 = 0;
    return ptr;
}

u8 *func_80084340(MusChannel *cp, u8 *ptr) {
    s32 v = *ptr++;

    if (v >= 0x80) {
        v &= 0x7F;
        v <<= 8;
        v |= *ptr++;
    }
    cp->length = v;
    return ptr;
}

u8 *func_80084370(MusChannel *cp, u8 *ptr) {
    cp->unkB7 = 1;
    return ptr;
}

u8 *func_80084380(MusChannel *cp, u8 *ptr) {
    cp->unkB9 = *ptr;
    return ptr + 1;
}

u8 *func_80084390(MusChannel *cp, u8 *ptr) {
    cp->unkBA = 1;
    return ptr;
}

/* Fdetune */
u8 *func_800843A0(MusChannel *cp, u8 *ptr) {
    s32 det = *ptr++;
    f32 old;

    if (det & 0x80) {
        det |= ~0xFF;
    }
    old = cp->unk90;
    cp->unk90 = (f32)det / 100.0;
    cp->unk30 = cp->unk30 - old + cp->unk90;
    return ptr;
}

u8 *func_800843F8(MusChannel *cp, u8 *ptr) {
    cp->env = 1;
    return ptr;
}

u8 *Fenvon(MusChannel *cp, u8 *ptr) {
    cp->env = 0;
    return ptr;
}

u8 *func_80084414(MusChannel *cp, u8 *ptr) {
    cp->trigger = 1;
    return ptr;
}

u8 *Ftron(MusChannel *cp, u8 *ptr) {
    cp->trigger = 0;
    return ptr;
}

/* Floop: push a repeat frame */
u8 *func_80084430(MusChannel *cp, u8 *ptr) {
    s32 i = cp->depth;

    cp->loopcount[i] = *ptr++;
    cp->loopptr[i] = ptr;
    cp->loopvol[i] = cp->pvolume;
    cp->looppb[i] = cp->ppitchbend;
    cp->loopBC[i] = cp->unkBC;
    cp->loop70[i] = cp->unk70;
    cp->loopA2[i] = cp->unkA2;
    cp->loopA4[i] = cp->unkA4;
    cp->depth++;
    return ptr;
}

/* Floopend: repeat or pop the innermost frame */
u8 *func_8008449C(MusChannel *cp, u8 *ptr) {
    s32 i = cp->depth - 1;

    if (cp->loopcount[i] != 0xFF) {
        if (--cp->loopcount[i] == 0) {
            cp->depth = i;
            i = -1;
        }
    }
    if (i >= 0) {
        ptr = cp->loopptr[i];
        cp->pvolume = cp->loopvol[i];
        cp->ppitchbend = cp->looppb[i];
        cp->unkBC = cp->loopBC[i];
        cp->unk70 = cp->loop70[i];
        cp->unkA2 = cp->loopA2[i];
        cp->unkA4 = cp->loopA4[i];
        cp->unk24 = cp->unk70 * cp->unk6C;
    }
    return ptr;
}

u8 *func_80084538(MusChannel *cp, u8 *ptr) {
    cp->unkD8 = *ptr++;
    cp->wobble = *ptr++;
    cp->unkCF = *ptr++;
    return ptr;
}

u8 *Fwobbleoff(MusChannel *cp, u8 *ptr) {
    cp->wobble = 0;
    return ptr;
}

u8 *func_8008456C(MusChannel *cp, u8 *ptr) {
    cp->velon = 1;
    return ptr;
}

u8 *Fveloff(MusChannel *cp, u8 *ptr) {
    cp->velon = 0;
    return ptr;
}

u8 *func_80084588(MusChannel *cp, u8 *ptr) {
    cp->unkD3 = *ptr;
    cp->velon = 0;
    return ptr + 1;
}

u8 *func_8008459C(MusChannel *cp, u8 *ptr) {
    cp->unkBD = *ptr >> 1;
    return ptr + 1;
}

u8 *Fstereo(MusChannel *cp, u8 *ptr) {
    return ptr + 2;
}

u8 *func_800845B8(MusChannel *cp, u8 *ptr) {
    s32 v = *ptr++;

    if (v >= 0x80) {
        v &= 0x7F;
        v <<= 8;
        v |= *ptr++;
    }
    cp->unk84 = (s32)&((MusSong *)cp->unk74)->drums[v];
    return ptr;
}

u8 *Fdrumsoff(MusChannel *cp, u8 *ptr) {
    cp->unk84 = 0;
    return ptr;
}

u8 *Fprint(MusChannel *cp, u8 *ptr) {
    return ptr + 1;
}

#ifdef NON_MATCHING
/* Same operations; the original interleaves the byte reads with the stores differently. */
/* Fgoto */
u8 *func_80084614(MusChannel *cp, u8 *ptr) {
    u32 off1, off2, off3;

    off1 = *ptr++ << 8;
    off1 += *ptr++;
    off2 = *ptr++ << 8;
    off2 += *ptr++;
    cp->unkA2 = 1;
    cp->pvolume = cp->pvolumebase + off2;
    off3 = *ptr++ << 8;
    off3 += *ptr++;
    cp->unkA4 = 1;
    cp->ppitchbend = cp->ppitchbendbase + off3;
    return cp->pbase + off1;
}
#else
INCLUDE_ASM("asm/nonmatchings/114F0", func_80084614);
#endif

u8 *func_80084684(MusChannel *cp, u8 *ptr) {
    cp->unkCA = *ptr;
    return ptr + 1;
}

u8 *func_80084694(MusChannel *cp, u8 *ptr) {
    cp->unkB9 = func_800836A4(*ptr++);
    cp->unkB9 += *ptr++;
    return ptr;
}

u8 *func_800846E4(MusChannel *cp, u8 *ptr) {
    cp->unkBC = func_800836A4(*ptr++);
    cp->unkBC += *ptr++;
    return ptr;
}

u8 *func_80084734(MusChannel *cp, u8 *ptr) {
    cp->unkBD = func_800836A4(*ptr++);
    cp->unkBD += *ptr++;
    return ptr;
}

u8 *func_80084784(MusChannel *cp, u8 *ptr) {
    cp->unkBC = *ptr;
    return ptr + 1;
}

u8 *func_80084794(MusChannel *cp, u8 *ptr) {
    s32 v = *ptr++;
    s32 h, i;
    MusChannel *cp2;

    if (v >= 0x80) {
        v = ((v & 0x7F) << 8) + *ptr++;
    }
    cp->unk48++;
    h = func_80083B24(cp->unk78, v, cp->unk9E, cp->unkB0, cp->unk48);
    cp->unk48--;
    if (h != 0) {
        cp2 = D_800B180C;
        for (i = 0; i < D_800B1804; i++, cp2++) {
            if (cp2->handle == h) {
                cp2->handle = cp->handle;
                cp2->unk7C = cp->unk7C;
            }
        }
    }
    return ptr;
}

u8 *func_80084864(MusChannel *cp, u8 *ptr) {
    cp->unk6C = (f32)*ptr * 0.015625;
    cp->unk24 = cp->unk70 * cp->unk6C;
    return ptr + 1;
}

/* Unreferenced double that follows this function's constant in the original rodata. */
const f64 D_800AE4E8 = 0.0;

u8 *func_800848A0(MusChannel *cp, u8 *ptr) {
    cp->unkD4 = *ptr;
    return ptr + 1;
}

u8 *Fchangefx(MusChannel *cp, u8 *ptr) {
    s32 fx = *ptr++;

    if (D_800B1830 == 1) {
        ChangeCustomEffect(fx);
    }
    return ptr;
}

u8 *func_800848F4(MusChannel *cp, u8 *ptr) {
    s32 v = *ptr++;
    s32 len = *ptr++;

    if (len & 0x80) {
        len = ((len & 0x7F) << 8) | *ptr++;
    }
    if ((cp->unk00 & 3) == 2 && D_800B1840 != 0) {
        ((void (*)(s32, s32))D_800B1840)(cp->handle, v);
    }
    return ptr;
}

u8 *Flength0(MusChannel *cp, u8 *ptr) {
    cp->length = 0;
    return ptr;
}

void func_800849D8(void *c);

void func_80084970(AlGlobalsLike *g, void *c) {
    if (n_alGlobals == NULL) {
        n_alGlobals = g;
        if (alGlobals_800A9E54 == NULL) {
            func_800850C0(c);
            alGlobals_800A9E54 = D_800E8298 = n_alGlobals;
            func_800849D8(c);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/114F0", func_800849D8);

s32 func_80084C48(s16 idx) {
    func_80084C98(&alGlobals_800A9E54->unk34->arr[idx]);
    return alGlobals_800A9E54->unk34->arr[idx];
}

INCLUDE_ASM("asm/nonmatchings/114F0", func_80084C98);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80084DE0);

void func_800850C0(MusSample *p) {
    p->unk1C = 6;
    p->unk20 = D_800A99D8;
}

extern s32 *D_800A9B64[];

s32 func_800850D8(void) {
    s32 i;
    s32 max = 0;

    for (i = 0; D_800A9B64[i] != NULL; i++) {
        if (max < D_800A9B64[i][0]) {
            max = D_800A9B64[i][0];
        }
    }
    return max;
}

s32 func_8008511C(void) {
    s32 i;
    s32 max = 0;

    for (i = 0; D_800A9B64[i] != NULL; i++) {
        if (max < D_800A9B64[i][1]) {
            max = D_800A9B64[i][1];
        }
    }
    return max;
}

s32 ChangeCustomEffect(s32 fx) {
    s32 r;

    if (fx < D_800A9B60) {
        func_80084DE0(D_800A9B64[fx]);
        alFxParam(D_800E8298->unk34->unk20, 1, D_800E8298->unk34);
        r = 0;
    } else {
        r = 1;
    }
    return r;
}
