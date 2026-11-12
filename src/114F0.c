#include "common.h"

/* libmus channel state (channel_t); only the fields the command handlers touch are named. */
typedef struct {
    /* 0x00 */ u8 pad00[0x8];
    /* 0x08 */ void *pdata;
    /* 0x0C */ u8 pad0C[0x18];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ u8 pad28[0x4];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ u8 pad30[0x4];
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ u8 pad3C[0x4];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ u8 pad48[0x8];
    /* 0x50 */ f32 unk50;
    /* 0x54 */ u8 pad54[0x14];
    /* 0x68 */ s32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ u8 pad7C[0x8];
    /* 0x84 */ s32 unk84;
    /* 0x88 */ u8 pad88[0xC];
    /* 0x94 */ s32 unk94;
    /* 0x98 */ u8 pad98[0x14];
    /* 0xAC */ u16 length;
    /* 0xAE */ u16 unkAE;
    /* 0xB0 */ u8 padB0[0x2];
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
    /* 0xBE */ u8 padBE[0xC];
    /* 0xCA */ u8 unkCA;
    /* 0xCB */ u8 padCB[0x3];
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
    /* 0xDB */ u8 padDB[0x1];
} MusChannel;

typedef struct {
    /* 0x00 */ u8 pad00[0x10];
    /* 0x10 */ s32 flags; /* negative once initialised */
} MusBank;

typedef struct {
    /* 0x00 */ u8 pad00[4];
    /* 0x04 */ s32 count;
    /* 0x08 */ u8 pad08[8];
    /* 0x10 */ void *ptrbank;
} MusFxBank;

typedef struct {
    /* 0x00 */ u8 type;
    /* 0x04 */ s32 value;
} MusCommand;

typedef struct {
    /* 0x00 */ u8 pad00[0x1C];
    /* 0x1C */ u8 unk1C;
    /* 0x20 */ void *unk20;
} MusSample;

extern s16 D_800B181C;
extern s16 D_800B181E;
extern MusBank *D_800B1828;
extern MusBank *D_800B182C;
extern s32 D_800B1830;
extern s32 D_800B1834;
extern s32 D_800B1838;
extern s32 D_800B183C;
extern s32 D_800B1840;
extern s32 D_800A9B8C;
extern u8 D_800A99D8[];
s32 func_80083CCC(void *addr);
void MusHandleUnPause(s32 handle);
void func_8008350C(void *bank);
void func_80082214(MusCommand *cmd);
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

INCLUDE_ASM("asm/nonmatchings/114F0", func_80081770);

INCLUDE_ASM("asm/nonmatchings/114F0", func_800817F0);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80081908);

INCLUDE_ASM("asm/nonmatchings/114F0", func_800819D4);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80081A54);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80081B08);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80081B60);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80081BC0);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80081C30);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80081CA0);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80081D2C);

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

INCLUDE_ASM("asm/nonmatchings/114F0", func_80081E48);

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

void MusSetFxType(s32 type) {
    MusCommand cmd;

    cmd.type = 2;
    cmd.value = type;
    D_800B1834 = type;
    func_80082214(&cmd);
}

INCLUDE_ASM("asm/nonmatchings/114F0", func_80081F20);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80081F7C);

s32 MusFxBankNumberOfEffects(MusFxBank *bank) {
    return bank->count;
}

void func_80082008(s32 a) {
    D_800B1838 = a;
}

void func_80082014(s32 a) {
    D_800B183C = a;
}

s32 func_80082020(void) {
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

INCLUDE_ASM("asm/nonmatchings/114F0", func_80082048);

INCLUDE_ASM("asm/nonmatchings/114F0", func_800820AC);

void func_80082124(s32 a) {
    D_800B1840 = a;
}

INCLUDE_ASM("asm/nonmatchings/114F0", func_80082130);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80082194);

INCLUDE_ASM("asm/nonmatchings/114F0", func_80082214);

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
    cp->unk44 = 0;
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
