#include "common.h"

/* libmus channel state (channel_t, 0x13C bytes); only fields the code here touches are named. */
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ void *pdata;
    /* 0x0C */ u8 pad0C[0x4];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 pad14[0x8];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8 pad20[0x4];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ u8 pad28[0x4];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ u8 pad3C[0x4];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 handle;
    /* 0x48 */ u8 pad48[0x8];
    /* 0x50 */ f32 unk50;
    /* 0x54 */ u8 pad54[0x14];
    /* 0x68 */ s32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ void *unk74;
    /* 0x78 */ void *unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ u8 pad80[0x4];
    /* 0x84 */ s32 unk84;
    /* 0x88 */ u8 pad88[0x8];
    /* 0x90 */ f32 unk90;
    /* 0x94 */ s32 unk94;
    /* 0x98 */ u16 unk98;
    /* 0x9A */ u8 pad9A[0x2];
    /* 0x9C */ u16 unk9C;
    /* 0x9E */ u16 unk9E;
    /* 0xA0 */ u8 padA0[0x8];
    /* 0xA8 */ u16 unkA8;
    /* 0xAA */ u8 padAA[0x2];
    /* 0xAC */ u16 length;
    /* 0xAE */ u16 unkAE;
    /* 0xB0 */ u16 unkB0;
    /* 0xB2 */ u16 unkB2;
    /* 0xB4 */ u16 unkB4;
    /* 0xB6 */ u8 padB6[0x1];
    /* 0xB7 */ u8 unkB7;
    /* 0xB8 */ u8 porta;
    /* 0xB9 */ u8 unkB9;
    /* 0xBA */ u8 unkBA;
    /* 0xBB */ u8 padBB[0x1];
    /* 0xBC */ u8 unkBC;
    /* 0xBD */ u8 unkBD;
    /* 0xBE */ u8 unkBE;
    /* 0xBF */ u8 padBF[0xB];
    /* 0xCA */ u8 unkCA;
    /* 0xCB */ u8 unkCB;
    /* 0xCC */ u8 unkCC;
    /* 0xCD */ u8 padCD[0x1];
    /* 0xCE */ u8 wobble;
    /* 0xCF */ u8 unkCF;
    /* 0xD0 */ u8 padD0[0x2];
    /* 0xD2 */ u8 velon;
    /* 0xD3 */ u8 unkD3;
    /* 0xD4 */ u8 unkD4;
    /* 0xD5 */ u8 vib;
    /* 0xD6 */ u8 env;
    /* 0xD7 */ u8 trigger;
    /* 0xD8 */ u8 unkD8;
    /* 0xD9 */ u8 sweep_timer;
    /* 0xDA */ u8 unkDA;
    /* 0xDB */ u8 padDB[0x61];
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
    /* 0x00 */ u8 pad00[8];
    /* 0x08 */ s32 unk08;
    /* 0x0C */ u8 pad0C[8];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 pad18[8];
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
s32 func_80083B24(MusFxBank *bank, void *addr, s32 a, s32 b, s32 c);
extern s32 D_800A9B8C;
extern u8 D_800A99D8[];
s32 func_80083CCC(void *addr);
void MusHandleUnPause(s32 handle);
void func_8008350C(void *bank);
s32 func_80082214(MusCommand *cmd);
void ChangeCustomEffect(s32 fx);





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

s32 func_80081770(void *addr) {
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
    ret = func_80083B24(bank, addr, 0x80, 0x80, -1);
    D_800B1828 = NULL;
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/114F0", func_800817F0);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80081908);

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

INCLUDE_ASM("asm/nonmatchings/114F0", func_80082AE8);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80082B64);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80082CB8);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80082DC4);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80082E34);

void __MusIntInitSweep(MusChannel *cp) {
    cp->sweep_timer = 0;
    cp->unk94 = cp->unk40;
    cp->unkDA = cp->unkBD & 0x40;
}

INCLUDE_ASM("asm/nonmatchings/114F0", func_8008302C);

INCLUDE_ASM("asm/nonmatchings/114F0", func_800830E4);

INCLUDE_ASM("asm/nonmatchings/114F0", func_8008313C);

INCLUDE_ASM("asm/nonmatchings/114F0", func_800831A0);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80083264);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80083378);

INCLUDE_ASM("asm/nonmatchings/114F0", func_8008350C);

INCLUDE_ASM("asm/nonmatchings/114F0", func_800836A4);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80083738);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80083874);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80083A3C);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80083A74);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80083B24);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80083CCC);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80083F38);

u8 *Fstop(MusChannel *cp, u8 *ptr) {
    cp->unk38 = 0;
    cp->unk34 = 0;
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

INCLUDE_ASM("asm/nonmatchings/114F0", func_80084008);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80084130);

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

INCLUDE_ASM("asm/nonmatchings/114F0", func_8008424C);

INCLUDE_ASM("asm/nonmatchings/114F0", func_800842BC);

u8 *Fviboff(MusChannel *cp, u8 *ptr) {
    cp->vib = 0;
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

INCLUDE_ASM("asm/nonmatchings/114F0", func_800843A0);

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

INCLUDE_ASM("asm/nonmatchings/114F0", func_80084430);

INCLUDE_ASM("asm/nonmatchings/114F0", func_8008449C);

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

INCLUDE_ASM("asm/nonmatchings/114F0", func_800845B8);

u8 *Fdrumsoff(MusChannel *cp, u8 *ptr) {
    cp->unk84 = 0;
    return ptr;
}

u8 *Fprint(MusChannel *cp, u8 *ptr) {
    return ptr + 1;
}

INCLUDE_ASM("asm/nonmatchings/114F0", func_80084614);

u8 *func_80084684(MusChannel *cp, u8 *ptr) {
    cp->unkCA = *ptr;
    return ptr + 1;
}

INCLUDE_ASM("asm/nonmatchings/114F0", func_80084694);

INCLUDE_ASM("asm/nonmatchings/114F0", func_800846E4);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80084734);

u8 *func_80084784(MusChannel *cp, u8 *ptr) {
    cp->unkBC = *ptr;
    return ptr + 1;
}

INCLUDE_ASM("asm/nonmatchings/114F0", func_80084794);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80084864);

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

INCLUDE_ASM("asm/nonmatchings/114F0", func_800848F4);

u8 *Flength0(MusChannel *cp, u8 *ptr) {
    cp->length = 0;
    return ptr;
}

INCLUDE_ASM("asm/nonmatchings/114F0", func_80084970);

INCLUDE_ASM("asm/nonmatchings/114F0", func_800849D8);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80084C48);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80084C98);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80084DE0);

void func_800850C0(MusSample *p) {
    p->unk1C = 6;
    p->unk20 = D_800A99D8;
}

INCLUDE_ASM("asm/nonmatchings/114F0", func_800850D8);

INCLUDE_ASM("asm/nonmatchings/114F0", func_8008511C);

INCLUDE_ASM("asm/nonmatchings/114F0", ChangeCustomEffect);
