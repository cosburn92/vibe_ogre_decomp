#include "common.h"

s32 ProfileFlagTest(s16 flag);
void ProfileFlagSet(s32 flag, s32 value);
void FlagSet(s32 flag, s32 value);
u8 func_80172BBC_ovl_040E80(u8 a);
void func_80172B10_ovl_040E80(u8 a, u8 b);
void func_80172B68_ovl_040E80(u8 a, u8 b);
void func_80172BF0_ovl_040E80(u8 a, u8 b);
void func_8016BA6C_ovl_040E80(u8 a, u8 b);
u16 func_8016B738_ovl_040E80(u16 a);
u16 func_8016B6FC_ovl_040E80(u16 a);
typedef struct { u8 unk0; u8 flags; u8 members[5]; u8 pos[5]; u8 harmony; u8 items[10]; u8 strategy; u8 legion; } SquadRec;
extern SquadRec D_801971F0_ovl_040E80[];
extern u8 D_801969B8_ovl_040E80[];
void bzero(void *p, s32 n);
extern u8 D_80197B00_ovl_040E80[];
extern u8 D_801936A8_ovl_040E80;
extern u16 D_80197B08_ovl_040E80;
typedef struct { u16 id; u8 count; u8 unk3; } InvEntry;
extern InvEntry D_80193AC0_ovl_040E80[]; /* consumable stock, 40 entries */
extern InvEntry D_80196B00_ovl_040E80[]; /* item stock, 278 entries */
typedef struct { u8 name[0x1C]; u16 flags; u8 pad[6]; } Location;
extern Location gLocations[];
extern u8 D_80196A81_ovl_040E80[];
extern u8 D_80196A86_ovl_040E80[];
extern void *D_80197B18_ovl_040E80;
extern void *D_80197B1C_ovl_040E80;
extern s32 D_8018F2F4_ovl_040E80;
extern s32 D_80190F10_ovl_040E80;
extern u8 D_275DD2C[];
extern s32 D_80197B10_ovl_040E80;
extern volatile s32 D_80197B0C_ovl_040E80; /* option mask (re-read after stores) */
extern u8 D_80197B01_ovl_040E80;
extern u8 D_80197B02_ovl_040E80;
extern u8 D_80197B03_ovl_040E80;
extern u16 D_80197B04_ovl_040E80;
void HFree(void *p);
void RomRead(void *rom, void *dst, s32 size);
void func_80171B94_ovl_040E80(void);
extern u8 D_801936A6_ovl_040E80;

extern struct { u16 v; u8 pad[34]; } D_801951CC_ovl_040E80[];
extern struct { u16 v; u8 pad[50]; } D_80195578_ovl_040E80[];
extern struct { u16 v; u8 pad[54]; } D_80193BD8_ovl_040E80[];
extern struct { u8 v; u8 pad[24]; } D_801971F1_ovl_040E80[];
extern struct { u8 v; u8 pad[3]; } D_80193AC2_ovl_040E80[];
extern struct { u8 v; u8 pad[3]; } D_80193AC3_ovl_040E80[];
extern struct { u8 v; u8 pad[3]; } D_80196B02_ovl_040E80[];
extern struct { u8 v; u8 pad[3]; } D_80196B03_ovl_040E80[];
extern struct { u8 v; u8 pad[51]; } D_80195571_ovl_040E80[];
extern struct { u8 v; u8 pad[51]; } D_80195572_ovl_040E80[];
extern struct { u8 v; u8 pad[51]; } D_80195574_ovl_040E80[];
extern struct { u8 v; u8 pad[51]; } D_80195593_ovl_040E80[];
extern struct { u8 v; u8 pad[55]; } D_80193BD1_ovl_040E80[];
extern struct { u8 v; u8 pad[55]; } D_80193BD2_ovl_040E80[];
extern struct { u8 v; u8 pad[55]; } D_80193BD4_ovl_040E80[];
extern struct { u8 v; u8 pad[55]; } D_80193BDA_ovl_040E80[];
extern struct { u8 v; u8 pad[55]; } D_80193BDB_ovl_040E80[];
extern struct { u8 v; u8 pad[55]; } D_80193BF3_ovl_040E80[];
extern u16 D_80190EBC_ovl_040E80[];
extern u16 D_8019532C_ovl_040E80[];
extern u16 D_80196F60_ovl_040E80[];
extern u8 D_80191010_ovl_040E80[];
extern u8 D_8019367C_ovl_040E80[];
extern u8 D_80193681_ovl_040E80[];
extern u8 D_80195480_ovl_040E80[];
extern u8 D_8019EE40[];

void FlagGet();
s32 func_80170794_ovl_040E80();

u8 func_80170190_ovl_040E80(s32 squad, s32 i) {
    return D_801971F0_ovl_040E80[squad].members[i];
}

u16 func_801701B8_ovl_040E80(s32 idx) {
    return D_80193BD8_ovl_040E80[idx].v;
}

u8 func_801701D4_ovl_040E80(s32 idx) {
    return D_80193BD1_ovl_040E80[idx].v;
}

u8 func_801701F0_ovl_040E80(s32 idx) {
    return D_80193BD2_ovl_040E80[idx].v;
}

u8 func_8017020C_ovl_040E80(s32 idx) {
    return D_80193BF3_ovl_040E80[idx].v;
}

u8 func_80170228_ovl_040E80(s32 idx) {
    return D_80193BD4_ovl_040E80[idx].v;
}

u16 func_80170244_ovl_040E80(s32 idx) {
    return D_80195578_ovl_040E80[idx].v;
}

u8 func_80170268_ovl_040E80(s32 idx) {
    return D_80195571_ovl_040E80[idx].v;
}

u8 func_8017028C_ovl_040E80(s32 idx) {
    return D_80195572_ovl_040E80[idx].v;
}

u8 func_801702B0_ovl_040E80(s32 idx) {
    return D_80195593_ovl_040E80[idx].v;
}

u8 func_801702D4_ovl_040E80(s32 idx) {
    return D_80195574_ovl_040E80[idx].v;
}

s32 func_801702F8_ovl_040E80(s32 flag) {
    return ProfileFlagTest(flag);
}

u8 func_80170318_ovl_040E80(s32 idx) {
    return D_801971F1_ovl_040E80[idx].v;
}

u16 func_80170338_ovl_040E80(s32 idx) {
    return D_80190EBC_ovl_040E80[idx];
}

u8 func_8017034C_ovl_040E80(s32 idx) {
    return D_80191010_ovl_040E80[idx];
}

u16 func_8017035C_ovl_040E80(s32 idx) {
    return D_8019532C_ovl_040E80[idx];
}

u8 func_80170370_ovl_040E80(s32 idx) {
    return D_80195480_ovl_040E80[idx];
}

u8 func_80170380_ovl_040E80(s32 idx) {
    return D_8019EE40[idx];
}

s32 func_80170390_ovl_040E80(s32 idx) {
    return (D_801951CC_ovl_040E80[idx].v & 0x2);
}

s32 func_801703B0_ovl_040E80(s32 idx) {
    return (D_801951CC_ovl_040E80[idx].v & 0x4);
}

s32 func_801703D0_ovl_040E80(s32 idx) {
    return ((D_801951CC_ovl_040E80[idx].v & 0x6) == 0);
}

u8 func_801703F4_ovl_040E80(s32 a) {
    return func_80172BBC_ovl_040E80(a);
}

u8 func_80170414_ovl_040E80(s32 idx) {
    return D_8019367C_ovl_040E80[idx];
}

u8 func_80170424_ovl_040E80(s32 idx) {
    return D_80193681_ovl_040E80[idx];
}

s32 func_80170434_ovl_040E80(void) {
    return 0;
}

void func_8017043C_ovl_040E80(void) {
    FlagGet();
}

u8 func_80170458_ovl_040E80(s32 idx) {
    return D_80193BDB_ovl_040E80[idx].v;
}

void func_80170474_ovl_040E80(s32 squad, s32 i, u8 value) {
    D_801971F0_ovl_040E80[squad].members[i] = value;
}

void func_8017049C_ovl_040E80(s32 flag, s32 unused, s32 value) {
    ProfileFlagSet(flag, value);
}

void func_801704B8_ovl_040E80(s32 idx, s32 unused, u8 value) {
    D_801971F1_ovl_040E80[idx].v = value;
}

void LocationSetLiberated(s32 unused0, s32 unused1, s32 loc) {
    gLocations[loc].flags |= 2;
}

void LocationSetCaptured(s32 unused0, s32 unused1, s32 loc) {
    gLocations[loc].flags |= 4;
}

void LocationClearOwner(s32 unused0, s32 unused1, s32 loc) {
    gLocations[loc].flags &= ~6;
}

void func_8017055C_ovl_040E80(s32 a, s32 unused, s32 b) {
    func_80172B10_ovl_040E80(a, b);
}

void func_8017057C_ovl_040E80(s32 a, s32 unused, s32 b) {
    func_80172B68_ovl_040E80(a, b);
}

void func_8017059C_ovl_040E80(s32 idx, s32 unused, u8 value) {
    D_8019367C_ovl_040E80[idx] = value;
}

void func_801705AC_ovl_040E80(s32 idx, s32 unused, u8 value) {
    D_80193681_ovl_040E80[idx] = value;
}

void func_801705BC_ovl_040E80(s32 idx, s32 unused, u16 value) {
    D_80196F60_ovl_040E80[idx] = value;
}

void func_801705D0_ovl_040E80(s32 flag, s32 unused, s32 value) {
    FlagSet(flag, value);
}

u16 func_801705EC_ovl_040E80(s32 a) {
    return func_8016B738_ovl_040E80(a);
}

u8 func_8017060C_ovl_040E80(s32 idx) {
    return D_80193AC3_ovl_040E80[idx].v;
}

u16 func_80170620_ovl_040E80(s32 idx) {
    return D_80193AC0_ovl_040E80[idx].id;
}

u8 func_80170634_ovl_040E80(s32 idx) {
    return D_80193AC2_ovl_040E80[idx].v;
}

u16 func_80170648_ovl_040E80(s32 a) {
    return func_8016B6FC_ovl_040E80(a);
}

u8 func_80170668_ovl_040E80(s32 idx) {
    return D_80196B03_ovl_040E80[idx].v;
}

u16 func_8017067C_ovl_040E80(s32 idx) {
    return D_80196B00_ovl_040E80[idx].id;
}

u8 func_80170690_ovl_040E80(s32 idx) {
    return D_80196B02_ovl_040E80[idx].v;
}

u8 func_801706A4_ovl_040E80(s32 idx) {
    return D_80193BDA_ovl_040E80[idx].v;
}

void func_801706C0_ovl_040E80(void) {
    func_80170794_ovl_040E80();
}

void func_801706DC_ovl_040E80(s32 idx, s32 unused, u8 value) {
    D_80193AC3_ovl_040E80[idx].v = value;
}

void func_801706F0_ovl_040E80(s32 idx, s32 unused, u16 value) {
    D_80193AC0_ovl_040E80[idx].id = value;
}

void func_80170704_ovl_040E80(s32 idx, s32 unused, u8 value) {
    D_80193AC2_ovl_040E80[idx].v = value;
}

void func_80170718_ovl_040E80(s32 idx, s32 unused, u8 value) {
    D_80196B03_ovl_040E80[idx].v = value;
}

void func_8017072C_ovl_040E80(s32 idx, s32 unused, u16 value) {
    D_80196B00_ovl_040E80[idx].id = value;
}

void func_80170740_ovl_040E80(s32 idx, s32 unused, u8 value) {
    D_80196B02_ovl_040E80[idx].v = value;
}

void func_80170754_ovl_040E80(s32 a, s32 unused, s32 b) {
    func_8016BA6C_ovl_040E80(b, a);
}

void func_80170774_ovl_040E80(s32 a, s32 unused, s32 b) {
    func_80172BF0_ovl_040E80(a, b);
}

s32 func_80170794_ovl_040E80(s32 mask) {
    if (!D_8018F2F4_ovl_040E80) {
        RomRead(D_275DD2C, &D_80190F10_ovl_040E80, 4);
        D_8018F2F4_ovl_040E80 = 1;
    }
    return (u8)mask & D_80190F10_ovl_040E80;
}

void func_801707F4_ovl_040E80(void) {
    void **p = &D_80197B18_ovl_040E80;

    HFree(*p);
    HFree(D_80197B1C_ovl_040E80);
    *p = NULL;
    D_80197B1C_ovl_040E80 = NULL;
}

extern u8 D_80196A93_ovl_040E80[];
extern u8 D_80196A30_ovl_040E80[];
s32 func_80171FE0_ovl_040E80(s32 a, s32 b);
void DateAdvanceDay(void *d);
void func_8016C70C_ovl_040E80(void *d);
extern s16 D_80197B06_ovl_040E80;
void func_80171B94_ovl_040E80(void);
s32 func_80171ED8_ovl_040E80(void);
void func_8016B774_ovl_040E80(void);
s32 ChunkSize(s32 id);
void *func_80071C04(s32 size);
void *LoadChunkRaw(void *dst, s32 id);
s32 ReadU32BE(void *p);
void DecodeLZ(void *dst, void *src);
extern u8 D_8018F320_ovl_040E80;
extern u8 D_8018F321_ovl_040E80;
extern s16 D_8018F322_ovl_040E80;
u8 func_8016FF5C_ovl_040E80(u8 a, u8 b);
void func_80172610_ovl_040E80(u8 i);
extern u8 D_80196A9A_ovl_040E80;
s32 func_80170954_ovl_040E80(u8 *msg);
void func_80172394_ovl_040E80(void);
/* --- end decls --- */

extern u8 D_801939D1_ovl_040E80;
extern u8 D_8018FAE0_ovl_040E80;
extern u8 D_8018FBDC_ovl_040E80;

/* Next game state for menu choice k (setting the battle / map mode flags some choices need) */
s32 func_80170838_ovl_040E80(u8 k) {
    s32 r;

    switch (k) {
        case 1:
            r = 0x8002;
            break;
        case 2:
            r = 0x8003;
            break;
        case 3:
            r = 0x8005;
            break;
        case 4:
            D_801939D1_ovl_040E80 = 1;
            r = 0x8007;
            break;
        case 11:
            r = 2;
            break;
        case 12:
            r = 3;
            break;
        case 13:
            r = 5;
            break;
        case 14:
            D_801939D1_ovl_040E80 = 1;
            r = 7;
            break;
        case 18:
            r = 0x13;
            break;
        case 19:
            r = 0x11;
            break;
        case 20:
            D_801939D1_ovl_040E80 = 2;
            r = 0x8007;
            break;
        case 21:
            D_801939D1_ovl_040E80 = 0;
            r = 0x8007;
            break;
        case 22:
            D_8018FAE0_ovl_040E80 = 1;
            r = 0x8016;
            break;
        case 23:
            D_8018FAE0_ovl_040E80 = 0;
            D_8018FBDC_ovl_040E80 = 0;
            r = 0x8016;
            break;
        case 24:
            r = 0x8016;
            D_8018FAE0_ovl_040E80 = 0;
            D_8018FBDC_ovl_040E80 = 1;
            break;
        case 25:
            r = 0x8016;
            D_8018FAE0_ovl_040E80 = 0;
            D_8018FBDC_ovl_040E80 = 2;
            break;
        case 26:
            r = 0xFFFD;
            break;
        case 27:
            D_8018FAE0_ovl_040E80 = 3;
            r = 0x8016;
            break;
        default:
            r = 0xFFFE;
            break;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/46090", func_80170954_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/46090", func_80171B94_ovl_040E80);

/* Runs the menu message for the current option; on completion frees the message tables and resets the menu */
s32 func_80171ED8_ovl_040E80(void) {
    s32 m = D_80197B0C_ovl_040E80;
    u8 *p;
    s32 r;

    D_80197B04_ovl_040E80 = 0;
    if (m == 1) {
        p = (u8 *)D_80197B18_ovl_040E80 + ((u16 *)D_80197B18_ovl_040E80)[D_80196A9A_ovl_040E80 & 0x7F];
    } else if (m == 0x40) {
        p = (u8 *)D_80197B1C_ovl_040E80 + ((u16 *)D_80197B1C_ovl_040E80)[D_80196A9A_ovl_040E80 & 0x7F];
    } else if (m == 0x80) {
        r = func_80170954_ovl_040E80((u8 *)D_80197B1C_ovl_040E80 + ((u16 *)D_80197B1C_ovl_040E80)[D_80196A9A_ovl_040E80 & 0x7F]);
        D_801936A8_ovl_040E80 = 0;
        return r;
    } else {
        return 0;
    }
    r = func_80170954_ovl_040E80(p);
    if (r == 0) {
        return 0;
    }
    HFree(D_80197B18_ovl_040E80);
    HFree(D_80197B1C_ovl_040E80);
    D_80197B18_ovl_040E80 = NULL;
    D_80197B1C_ovl_040E80 = NULL;
    func_80172394_ovl_040E80();
    func_8017223C_ovl_040E80(1);
    return r;
}

extern s32 D_80197B14_ovl_040E80;
extern u8 D_80197B02_ovl_040E80;
void *LoadChunk(s32 id);
typedef struct {
    s32 w[25];
} MsgState46;

/* Runs message b of script a immediately (mode 2) without disturbing the current message state */
#ifdef NON_MATCHING
/* 80 vs 81 instructions: the original keeps &state+2 in s1 for the two byte stores and the final restore, and re-reads the script index by symbol */
s32 func_80171FE0_ovl_040E80(s32 a, s32 b) {
    MsgState46 saved = *(MsgState46 *)D_80197B00_ovl_040E80;
    s32 *t;
    s32 id;
    u8 *m;

    D_80197B02_ovl_040E80 = 0;
    D_80197B03_ovl_040E80 = 2;
    D_80197B04_ovl_040E80 = 0;
    D_80197B00_ovl_040E80[0] = a;
    D_80197B01_ovl_040E80 = b;
    t = LoadChunkRaw(NULL, 0x3A5668);
    id = t[D_80197B00_ovl_040E80[0]];
    HFree(t);
    m = LoadChunk(id);
    func_80170954_ovl_040E80(m + ((u16 *)m)[D_80197B01_ovl_040E80]);
    HFree(m);
    a = D_80197B14_ovl_040E80;
    *(MsgState46 *)D_80197B00_ovl_040E80 = saved;
    return a;
}
#else
INCLUDE_ASM("asm/nonmatchings/46090", func_80171FE0_ovl_040E80);
#endif

extern s32 D_80197B14_ovl_040E80;
void *LoadChunk(s32 id);

/* Starts the current message: mode 0/1 builds it (two ways), mode 2 loads message D_80197B01 of
 * script D_80197B00 */
s32 func_80172124_ovl_040E80(void) {
    bzero(D_80196F60_ovl_040E80, 0x200);
    if (D_80197B00_ovl_040E80[2] != 0) {
        D_80197B00_ovl_040E80[2] = 0;
        D_80197B04_ovl_040E80++;
    }
    switch (D_80197B03_ovl_040E80) {
    case 0:
    case 1:
        if (D_80197B06_ovl_040E80 != 0) {
            func_80171B94_ovl_040E80();
            return;
        }
        return func_80171ED8_ovl_040E80();
    case 2: {
        s32 *t = LoadChunkRaw(NULL, 0x3A5668);
        s32 id = t[D_80197B00_ovl_040E80[0]];
        u8 *m;

        HFree(t);
        m = LoadChunk(id);
        func_80170954_ovl_040E80(m + ((u16 *)m)[D_80197B01_ovl_040E80]);
        HFree(m);
        return D_80197B14_ovl_040E80;
    }
    }
    return 0;
}

/* Sets the menu option mask and puts the cursor on the first enabled option */
void func_8017223C_ovl_040E80(s16 mask) {
    s32 m;

    D_80197B10_ovl_040E80 = mask;
    D_80197B0C_ovl_040E80 = mask;
    D_80197B03_ovl_040E80 = 0;
    if (D_80197B06_ovl_040E80 != 0) {
        D_80197B02_ovl_040E80 = 0;
        m = D_80197B0C_ovl_040E80;
        if (m & 1) {
            D_80197B00_ovl_040E80[0] = 0;
        } else if (m & 2) {
            D_80197B00_ovl_040E80[0] = 1;
        } else if (m & 4) {
            D_80197B00_ovl_040E80[0] = 2;
        } else if (m & 8) {
            D_80197B00_ovl_040E80[0] = 3;
        } else if (m & 0x10) {
            D_80197B00_ovl_040E80[0] = 4;
        } else if (m & 0x20) {
            D_80197B00_ovl_040E80[0] = 5;
        }
        D_80197B01_ovl_040E80 = 0;
        D_80197B04_ovl_040E80 = 0;
        func_80171B94_ovl_040E80();
    } else {
        D_80197B04_ovl_040E80 = 0;
        func_80171ED8_ovl_040E80();
    }
}

void func_8017230C_ovl_040E80(s16 a, u8 b, u8 c) {
    D_80197B10_ovl_040E80 = a;
    D_80197B0C_ovl_040E80 = a;
    D_80197B03_ovl_040E80 = 1;
    D_80197B00_ovl_040E80[0] = b;
    D_80197B01_ovl_040E80 = c;
    D_80197B02_ovl_040E80 = 0;
    D_80197B04_ovl_040E80 = 0;
    func_80171B94_ovl_040E80();
}

void func_80172368_ovl_040E80(void) {
    bzero(D_80197B00_ovl_040E80, 100);
    D_801936A8_ovl_040E80 = 0;
}

extern s16 D_8018F1A0_ovl_040E80;
extern s16 D_80197B60_ovl_040E80;
void func_80080998(void *dst, void *src, s32 n);
void *LoadChunkRaw(void *dst, s32 id);

/* Reloads the message scripts for the current chapter (D_801936A8), resetting the message
 * state but keeping its id (0x08), option word (0x60) and the 0x40-byte work area (0x20) */
#ifdef NON_MATCHING
/* 132 vs 136: GCC cross-jumps the script-index load (t[D_80197B06]) of both branches into the shared tail; the original keeps one per branch with t in a0 */
void func_80172394_ovl_040E80(void) {
    MsgState46 saved;
    s32 *t;
    s32 a;
    s32 b;

    D_8018F1A0_ovl_040E80 = 0;
    HFree(*(void **)(D_80197B00_ovl_040E80 + 0x18));
    HFree(D_80197B1C_ovl_040E80);
    if ((s16)D_80197B08_ovl_040E80 != 1 && (s16)D_80197B08_ovl_040E80 != -1) {
        D_80197B08_ovl_040E80 = -1;
    }
    if (D_801936A8_ovl_040E80 != 0) {
        if (D_80197B02_ovl_040E80 == 0) {
            saved = *(MsgState46 *)D_80197B00_ovl_040E80;
            bzero(D_80197B00_ovl_040E80, 0x64);
            D_80197B08_ovl_040E80 = ((u16 *)&saved)[4];
            D_80197B60_ovl_040E80 = ((u16 *)&saved)[0x30];
            func_80080998(D_80197B00_ovl_040E80 + 0x20, (u8 *)&saved + 0x20, 0x40);
            D_80197B06_ovl_040E80 = D_801936A8_ovl_040E80;
        }
        t = LoadChunkRaw(NULL, 0x3A5668);
        a = t[D_80197B06_ovl_040E80];
        b = t[0x104 / 4];
    } else {
        saved = *(MsgState46 *)D_80197B00_ovl_040E80;
        bzero(D_80197B00_ovl_040E80, 0x64);
        D_80197B08_ovl_040E80 = ((u16 *)&saved)[4];
        func_80080998(D_80197B00_ovl_040E80 + 0x20, (u8 *)&saved + 0x20, 0x40);
        D_80197B06_ovl_040E80 = D_801936A8_ovl_040E80;
        t = LoadChunkRaw(NULL, 0x3A5668);
        a = t[D_80197B06_ovl_040E80];
        b = t[0x118 / 4];
    }
    HFree(t);
    D_80197B18_ovl_040E80 = LoadChunk(a);
    D_80197B1C_ovl_040E80 = LoadChunk(b);
}
#else
INCLUDE_ASM("asm/nonmatchings/46090", func_80172394_ovl_040E80);
#endif

void func_801725B4_ovl_040E80(u16 v) {
    D_80197B08_ovl_040E80 = v;
}

inline s32 func_801725C0_ovl_040E80(u8 c) {
    s32 r = 0;

    if ((u8)(c - 0x2D) < 2 || c == 0x2F || (u8)(c - 0x24) < 2 || c == 0x30) {
        r = 1;
    }
    return r;
}

extern u8 D_801971F2_ovl_040E80[];
extern u8 D_801969B9_ovl_040E80[];
extern u8 D_801969BA_ovl_040E80[];

/* Removes unit i from its squad (and, when it led a squad flagged 2, that squad from its
 * legion's line-up) */
#ifdef NON_MATCHING
/* 122 vs 124: loops and stores right; the original's legion pass addresses the flag byte by symbol + index each time and copies the line-up through a second base */
void func_80172610_ovl_040E80(u8 i) {
    s16 sq;
    s16 j;
    s16 found = 0;

    j = 0;
    for (sq = 0; sq < 30; sq++) {
        for (j = 0; j < 5; j++) {
            u8 *m = &D_801971F2_ovl_040E80[sq * 25 + j];

            if (*m == i) {
                u8 f = D_801971F1_ovl_040E80[sq].v;

                D_801971F1_ovl_040E80[sq].v = f & 0xFB;
                if (j != 0) {
                    *m = 0;
                    D_801971F2_ovl_040E80[sq * 25 + 5 + j] = 0;
                    return;
                }
                D_801971F1_ovl_040E80[sq].v = f & 0xFA;
                if (!(f & 2)) {
                    return;
                }
                found = sq;
                break;
            }
        }
        j = 0;
    }
    for (sq = 0; sq < 6; sq++) {
        u8 *l = &D_801969BA_ovl_040E80[sq * 11];

        for (; j < 5; j++) {
            if (l[j] == found) {
                u8 f = D_801969B9_ovl_040E80[sq * 11];

                D_801969B9_ovl_040E80[sq * 11] = f & 0xFB;
                if (j == 0) {
                    D_801969B9_ovl_040E80[sq * 11] = f & 0xFA;
                    return;
                }
                for (; j < 4; j++) {
                    l[j] = l[j + 1];
                }
                l[j] = 0xFF;
                break;
            }
        }
        j = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/46090", func_80172610_ovl_040E80);
#endif

/* Adds n of item id to the stock (max 99), using the first empty slot for a new item */
void func_80172800_ovl_040E80(u16 id, s32 n) {
    u16 i;
    u16 free = 0xFFFF;

    if (id == 0) {
        return;
    }
    for (i = 0; i < 0x116; i++) {
        if (D_80196B00_ovl_040E80[i].id == id) {
            u8 c = D_80196B03_ovl_040E80[i].v + n;

            D_80196B03_ovl_040E80[i].v = c;
            if (c >= 100) {
                D_80196B03_ovl_040E80[i].v = 99;
            }
            break;
        }
        if (D_80196B00_ovl_040E80[i].id == 0 && free == 0xFFFF) {
            free = i;
        }
    }
    if (i >= 0x116) {
        if (free != 0xFFFF) {
            D_80196B00_ovl_040E80[free].id = id;
            D_80196B03_ovl_040E80[free].v = n;
        }
    }
    func_8016B774_ovl_040E80();
}

s32 func_801728EC_ovl_040E80(u8 id) {
    u16 slot = func_8016B738_ovl_040E80(id);

    if (slot < 40) {
        return D_80193AC0_ovl_040E80[slot].unk3 - D_80193AC0_ovl_040E80[slot].count;
    }
    return 0;
}

s32 func_8017293C_ovl_040E80(u16 id) {
    u16 slot = func_8016B6FC_ovl_040E80(id);

    if (slot < 278) {
        return D_80196B00_ovl_040E80[slot].unk3 - D_80196B00_ovl_040E80[slot].count;
    }
    return 0;
}

u8 func_8017298C_ovl_040E80(u16 id) {
    u16 slot = func_8016B738_ovl_040E80(id);

    if (slot < 40) {
        return D_80193AC0_ovl_040E80[slot].unk3;
    }
    return 0;
}

/* Indexes the consumable stock with an item slot (likely a bug). */
u8 func_801729CC_ovl_040E80(u16 id) {
    u16 slot = func_8016B6FC_ovl_040E80(id);

    if (slot < 278) {
        return D_80193AC0_ovl_040E80[slot].unk3;
    }
    return 0;
}

u8 func_80172A0C_ovl_040E80(u8 i) {
    return (D_801936A6_ovl_040E80 >> (i * 2)) & 3;
}

/* Mode 1: applies func_80172610 to every unit matching val; otherwise records a pending request */
void func_80172A28_ovl_040E80(s32 mode, s32 kind, s32 val, u8 extra) {
    u8 *st = &D_8018F320_ovl_040E80;
    u16 i;

    *st = 0;
    if (mode == 1) {
        for (i = 0; i < 100; i++) {
            if (func_8016FF5C_ovl_040E80(D_80193BD1_ovl_040E80[i].v, val) == 1) {
                func_80172610_ovl_040E80(i);
                func_8016BA6C_ovl_040E80(0, i);
            }
        }
    } else {
        if (kind == 0) {
            *st = 1;
        } else if (kind == 2) {
            *st = 4;
        } else {
            *st = 3;
        }
        D_8018F322_ovl_040E80 = val;
        D_8018F321_ovl_040E80 = extra;
    }
}

/* Sets the 2-bit field n (1-based) */
void func_80172B10_ovl_040E80(u8 n, u8 v) {
    s32 i = n - 1;
    s32 sh;
    u8 old = D_80196A86_ovl_040E80[i / 4];

    sh = (i & 3) * 2;
    old &= ~(3 << sh);
    D_80196A86_ovl_040E80[i / 4] = old | (v << sh);
}

/* Sets bit flag n (1-based) */
/* param masking/register order differs */
void func_80172B68_ovl_040E80(u8 n, u8 v)
{
  int new_var;
  s32 i = n - 1;
  s32 s;
  unsigned int new_var2;
  new_var2 = D_80196A81_ovl_040E80[i / 8];
  if (1)
  {
    s = i & 7;
 dummy_label_803137: ;
  }
  new_var = new_var2 & (~(1 << s));
  D_80196A81_ovl_040E80[i / 8] = new_var | (v << s);
}

u8 func_80172BBC_ovl_040E80(u8 n) {
    s32 i = n - 1;

    return (D_80196A81_ovl_040E80[i / 8] >> (i & 7)) & 1;
}

/* param masking/register order differs */
void func_80172BF0_ovl_040E80(u8 n, u8 v)
{
  int new_var;
  s32 i = n - 1;
  new_var = D_80196A93_ovl_040E80[i / 8] & (~(1 << (i & 7)));
  D_80196A93_ovl_040E80[i / 8] = new_var | (v << ((n - 1) & 7));
}

INCLUDE_ASM("asm/nonmatchings/46090", func_80172C44_ovl_040E80);

extern u8 D_80193BC0_ovl_040E80[][0x38];
void func_80172C44_ovl_040E80(u8 *c);

/* Turns every player character (1-99) whose class matches v (and is not a lord class) into class
 * cls / base class base, then refreshes it */
void func_801730BC_ovl_040E80(u8 v, u8 cls, u8 base) {
    u8 i;

    for (i = 1; i < 100; i++) {
        if (func_801725C0_ovl_040E80(D_80193BD2_ovl_040E80[i].v) == 0) {
            if (func_8016FF5C_ovl_040E80(D_80193BD1_ovl_040E80[i].v, v) == 1) {
                D_80193BD2_ovl_040E80[i].v = cls;
                D_80193BD1_ovl_040E80[i].v = base;
                func_80172C44_ovl_040E80(D_80193BC0_ovl_040E80[i]);
            }
        }
    }
}

/* Default 11-byte record using the legion of the first squad found with member 1 (the member test
 * only ever looks at squad 0) */
void func_801731EC_ovl_040E80(void) {
    u8 i;
    u8 k;
    SquadRec *sq;
    u8 *r = D_801969B8_ovl_040E80;

    bzero(r, 0xB);
    for (i = 0; i < 30; i++) {
        for (k = 0; k < 5; k++) {
            if (D_801971F0_ovl_040E80[0].members[k] == 1) {
                break;
            }
        }
        if (k < 5) {
            break;
        }
    }
    sq = &D_801971F0_ovl_040E80[i];
    for (k = 0; k < 5; k++) {
    }
    r[0] = 1;
    r[1] = 1;
    r[3] = 0xFF;
    r[4] = 0xFF;
    r[5] = 0xFF;
    r[6] = 0xFF;
    r[8] = 1;
    r[9] = sq->legion;
    r[0xA] = 10;
}

/* Moves the calendar n days forward (or back for negative n) */
void func_801732E0_ovl_040E80(s16 n) {
    s16 i;

    if (n >= 0) {
        func_80171FE0_ovl_040E80(0x43, 3);
        for (i = 0; i < n; i++) {
            DateAdvanceDay(D_80196A30_ovl_040E80);
            func_80171FE0_ovl_040E80(0x43, 3);
        }
    } else {
        for (n++; n != 1; n++) {
            func_8016C70C_ovl_040E80(D_80196A30_ovl_040E80);
        }
    }
}

/* Low byte of the trailing marker word (0xFFxxxxxx) of compressed entry i in table chunk 0x19A8804, or 0 */
s32 func_801733A0_ovl_040E80(s32 i) {
    s32 *buf;
    s32 *out;

    buf = func_80071C04(ChunkSize(0x19A8804));
    LoadChunkRaw(buf, 0x19A8804);
    /* i = buf[i], computed in place */
    i *= 4;
    i += (s32)buf;
    i = *(s32 *)i;
    HFree(buf);
    buf = func_80071C04(ChunkSize(i));
    LoadChunkRaw(buf, i);
    i = ReadU32BE(buf);
    out = func_80071C04(i);
    DecodeLZ(out, buf);
    i = out[i / 4 - 1];
    HFree(buf);
    HFree(out);
    if ((i & 0xFF000000) == 0xFF000000) {
        return i & 0xFF;
    }
    return 0;
}

s32 func_80173490_ovl_040E80(u8 v) {
    u8 i;

    for (i = 0; i < 5; i++) {
        if (D_8019367C_ovl_040E80[i] == v) {
            return 1;
        }
    }
    return 0;
}

/* Group and position of id in the grouped list chunk 0x01A8E7AE (u16 group starts, then the ids) */
void func_801734D4_ovl_040E80(s16 *grp, s16 *pos, u8 id) {
    u16 *t;
    u16 *ids;
    s16 g = 0;
    s16 n = 0;
    u16 i;
    u16 j;

    t = LoadChunkRaw(NULL, 0x01A8E7AE);
    ids = t + t[0];
    for (i = 0; ids[i] != 0xFFFF; i++) {
        if (id == ids[i]) {
            for (j = 0; t[j] != 0xFFFF; j++) {
                if (i < t[j] - t[0]) {
                    break;
                }
            }
            g = j - 1;
            n = i - t[j];
            break;
        }
    }
    HFree(t);
    *grp = g;
    *pos = n;
}
