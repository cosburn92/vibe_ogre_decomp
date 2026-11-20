#include "common.h"

/* Event-script interpreter context: opcodes advance pc and return 0 (continue) or 1 (wait). */
typedef struct {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 state; /* for multi-frame opcodes */
    /* 0x02 */ u8 unk02[2];
    /* 0x04 */ u8 *base;
    /* 0x08 */ u8 *volatile pc;
    /* 0x0C */ u16 depth;
    /* 0x0E */ u8 unk0E[2];
    /* 0x10 */ u8 *stack[4];
    /* 0x20 */ u16 loopDepth;
    /* 0x22 */ u16 loopCount[4];
    /* 0x2A */ u8 unk2A[2];
    /* 0x2C */ u16 cond;
} ScriptCtx;

typedef struct {
    u8 used;
    u8 value;
    u16 id;
} ScriptSlot;

extern ScriptSlot D_8022A1F0_ovl_1BA050[];
extern u8 *D_8022A248_ovl_1BA050;
extern s32 D_8022A24C_ovl_1BA050;
extern volatile s32 D_8022A250_ovl_1BA050;
extern s32 *D_8022A214_ovl_1BA050;
extern s32 D_8022A82C_ovl_1BA050;
extern u16 D_8022A254_ovl_1BA050;
extern u16 D_8022A256_ovl_1BA050;
extern u8 D_8022A821_ovl_1BA050;
u8 *func_80222EEC_ovl_1BA050(u16 id);
void func_80229604_ovl_1BA050(s32 arg);
extern u16 D_8022A218_ovl_1BA050[];
extern u16 *D_80229CB0_ovl_1BA050[];
extern u16 D_8022A822_ovl_1BA050;
extern u16 D_8022A830_ovl_1BA050;
extern u16 D_8022A828_ovl_1BA050;
extern u16 *D_80229CE0_ovl_1BA050[];
extern u16 *D_80229CEC_ovl_1BA050[];
extern u16 *D_80229CF8_ovl_1BA050[];
extern u16 *D_80229D04_ovl_1BA050[];
extern s8 D_800E9C0A[];
u8 *func_80226164_ovl_1BA050(u8 id);
ScriptCtx *func_802219E0_ovl_1BA050(u8 *base, s32 off, s32 idx);
u8 *func_80222EA0_ovl_1BA050(u16 id);
extern u8 *D_8022A234_ovl_1BA050;
extern u8 D_801936E0;
extern u8 D_80196AEC;
void HFree(void *p);
void bzero(void *p, s32 size);
void func_80229930_ovl_1BA050(void);
void func_80228EE4_ovl_1BA050(void);
void func_80228378_ovl_1BA050(void);
void func_80224E1C_ovl_1BA050(void);
void func_80224BE8_ovl_1BA050(void);
void func_80079618(s32 handle, s32 flags);
void func_80224268_ovl_1BA050(u8 *o, u16 a, s32 b);
void func_80224320_ovl_1BA050(u8 *o, u16 a);
s32 func_80227F68_ovl_1BA050(u16 a);





void func_80220F40_ovl_1BA050(void) {
    bzero(D_8022A1F0_ovl_1BA050, 0x20);
}

extern s32 D_8022A210_ovl_1BA050;
extern s32 D_8022A230_ovl_1BA050;
void *func_8017F334(u16 id);
void func_8017C2FC(void *o);
void func_8017C384(void *o);
void *LoadAsset(s32 file, s32 id, s32 a, s32 b);
void bzero(void *p, s32 n);
#define U16AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
typedef struct {
    /* 0x00 */ u8 *vram;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u8 *romStart;
    /* 0x0C */ u8 *romEnd;
    /* 0x10 */ u8 *bssStart;
    /* 0x14 */ u8 *bssEnd;
    /* 0x18 */ u8 *textStart;
    /* 0x1C */ u8 *textEnd;
    /* 0x20 */ u8 *dataStart;
    /* 0x24 */ u8 *dataEnd;
} OvlDesc; /* size 0x28 */
typedef struct {
    /* 0x00 */ s32 a;
    /* 0x04 */ s32 b;
    /* 0x08 */ void (*init)(void);
    /* 0x0C */ s32 c;
    /* 0x10 */ s32 d;
    /* 0x14 */ u8 *e;
    /* 0x18 */ s32 f;
} EvSetup; /* size 0x1C */
extern OvlDesc D_80229DBC_ovl_1BA050[];
extern EvSetup D_80229E68_ovl_1BA050[];
extern s32 D_8022A238_ovl_1BA050;
extern s32 D_8022A23C_ovl_1BA050;
extern s32 D_8022A240_ovl_1BA050;
extern s32 D_8022A244_ovl_1BA050;
void osInvalICache(void *p, s32 n);
void osInvalDCache(void *p, s32 n);
void RomRead(void *rom, void *dst, s32 size);
void func_80224C60_ovl_1BA050(void);
void func_80224D60_ovl_1BA050(void);
void func_8022995C_ovl_1BA050(void);
void func_80228E88_ovl_1BA050(s32 i);
void func_80228FE8_ovl_1BA050(s32 i);
s32 func_80229040_ovl_1BA050(s32 i);
void *func_8022905C_ovl_1BA050(s32 i, void *text, s32 x, s32 y, u8 flags);
/* --- end decls --- */

inline void func_80220F64_ovl_1BA050(u16 id, u8 v) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (D_8022A1F0_ovl_1BA050[i].used == 0) {
            break;
        }
    }
    if (i >= 8) {
        for (;;) {
        }
    }
    D_8022A1F0_ovl_1BA050[i].value = v;
    D_8022A1F0_ovl_1BA050[i].id = id;
    D_8022A1F0_ovl_1BA050[i].used = 1;
}

void func_80220FD0_ovl_1BA050(u16 id) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (D_8022A1F0_ovl_1BA050[i].used != 0 && D_8022A1F0_ovl_1BA050[i].id == id) {
            D_8022A1F0_ovl_1BA050[i].value = 0;
            D_8022A1F0_ovl_1BA050[i].id = 0;
            D_8022A1F0_ovl_1BA050[i].used = 0;
            return;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80221030_ovl_1BA050);

inline void func_8022126C_ovl_1BA050(void) {
    if (D_8022A248_ovl_1BA050 != NULL && D_8022A24C_ovl_1BA050 != 0) {
        bzero(D_8022A248_ovl_1BA050, D_8022A24C_ovl_1BA050);
    }
    D_8022A250_ovl_1BA050 = 0;
}

/* Script i of the loaded script bank (a table of offsets); hangs if none is loaded. */
u8 *func_802212AC_ovl_1BA050(s32 i) {
    if (D_8022A214_ovl_1BA050 == NULL) {
        for (;;) {
        }
    }
    return (u8 *)((s32)D_8022A214_ovl_1BA050 + D_8022A214_ovl_1BA050[i]);
}

void func_802212D4_ovl_1BA050(s32 id) {
    if (D_8022A210_ovl_1BA050 != id) {
        if (D_8022A210_ovl_1BA050 != -1) {
            ((void (*)(s32, s32, s32))func_80079618)(0x21C3C38, D_8022A210_ovl_1BA050, -0x11);
        }
        D_8022A210_ovl_1BA050 = id;
    }
    if (id != -1) {
        D_8022A214_ovl_1BA050 = LoadAsset(0x21C3C38, id, -4, 0);
    } else {
        D_8022A214_ovl_1BA050 = NULL;
    }
}

void func_80221354_ovl_1BA050(void) {
    u32 i;

    for (i = 0; i < 12; i++) {
        *D_80229CB0_ovl_1BA050[i] = D_8022A218_ovl_1BA050[i] & ~D_8022A822_ovl_1BA050;
    }
}

/* Clears the bits from the first halfword of three entries (four times over, as written). */
void func_802213A0_ovl_1BA050(u16 bits) {
    s32 i;
    s32 j;

    for (i = 0; i < 3; i++) {
        u16 *p = D_80229CE0_ovl_1BA050[i];

        for (j = 0; j < 4; j++) {
            *p &= ~bits;
        }
    }
}

/* Clears the bits from the first halfword of three entries (four times over, as written). */
void func_802213EC_ovl_1BA050(u16 bits) {
    s32 i;
    s32 j;

    for (i = 0; i < 3; i++) {
        u16 *p = D_80229CEC_ovl_1BA050[i];

        for (j = 0; j < 4; j++) {
            *p &= ~bits;
        }
    }
}

/* Clears the bits from the first halfword of three entries (four times over, as written). */
void func_80221438_ovl_1BA050(u16 bits) {
    s32 i;
    s32 j;

    for (i = 0; i < 3; i++) {
        u16 *p = D_80229CF8_ovl_1BA050[i];

        for (j = 0; j < 4; j++) {
            *p &= ~bits;
        }
    }
}

/* Clears the bits from the first halfword of three entries (four times over, as written). */
void func_80221484_ovl_1BA050(u16 bits) {
    s32 i;
    s32 j;

    for (i = 0; i < 3; i++) {
        u16 *p = D_80229D04_ovl_1BA050[i];

        for (j = 0; j < 4; j++) {
            *p &= ~bits;
        }
    }
}

#ifdef NON_MATCHING
/* m2c draft, 500 words from the target; queued for the permuter */
#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
s32 func_802263CC_ovl_1BA050(u16 *, u32);       /* extern */
extern void *D_800C47F0;
extern u16 *D_80229D10_ovl_1BA050;
extern u16 *D_80229D28_ovl_1BA050;

void func_802214D0_ovl_1BA050(void) {
    s32 temp_a3;
    s32 var_a0_2;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a2_3;
    s32 var_a2_4;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_5;
    u16 **var_a1_2;
    u16 **var_a1_3;
    u16 **var_a1_4;
    u16 **var_a1_5;
    u16 **var_a1_6;
    u16 **var_a1_7;
    u16 **var_v1;
    u16 *temp_a0;
    u16 *temp_a0_2;
    u16 *temp_a0_3;
    u16 *temp_a0_4;
    u16 *temp_a0_5;
    u16 *temp_a0_6;
    u16 *var_a0;
    u16 temp_v0;
    u32 var_a1;
    u32 var_a2_5;
    u32 var_a2_6;
    void **var_v1_6;

    if (!(D_8022A254_ovl_1BA050 & 0x8000)) {
        D_8022A254_ovl_1BA050 |= 0x8000;
        var_a1 = 0;
        var_a0 = D_8022A218_ovl_1BA050;
        var_v1 = D_80229CB0_ovl_1BA050;
        do {
            temp_v0 = **var_v1;
            var_v1 += 4;
            var_a1 += 1;
            *var_a0 = temp_v0;
            var_a0 += 2;
        } while (var_a1 < 0xCU);
        func_802263CC_ovl_1BA050(var_a0, var_a1);
        var_a2 = 0;
        var_a1_2 = D_80229CE0_ovl_1BA050;
        do {
            temp_a0 = *var_a1_2;
            var_v1_2 = 0;
loop_5:
            var_v1_2 += 1;
            *temp_a0 &= ~D_8022A830_ovl_1BA050;
            if (var_v1_2 < 4) {
                goto loop_5;
            }
            var_a2 += 1;
            var_a1_2 += 4;
        } while (var_a2 < 3);
        var_a2_2 = 0;
        var_a1_3 = D_80229CEC_ovl_1BA050;
        do {
            temp_a0_2 = *var_a1_3;
            var_v1_3 = 0;
loop_9:
            var_v1_3 += 1;
            *temp_a0_2 &= ~D_8022A830_ovl_1BA050;
            if (var_v1_3 < 4) {
                goto loop_9;
            }
            var_a2_2 += 1;
            var_a1_3 += 4;
        } while (var_a2_2 < 3);
        var_a2_3 = 0;
        var_a1_4 = D_80229CF8_ovl_1BA050;
        do {
            temp_a0_3 = *var_a1_4;
            var_v1_4 = 0;
loop_13:
            var_v1_4 += 1;
            *temp_a0_3 &= ~D_8022A830_ovl_1BA050;
            if (var_v1_4 < 4) {
                goto loop_13;
            }
            var_a2_3 += 1;
            var_a1_4 += 4;
        } while (var_a2_3 < 3);
        var_a2_4 = 0;
        var_a1_5 = D_80229D04_ovl_1BA050;
        temp_a3 = ~D_8022A830_ovl_1BA050;
        do {
            temp_a0_4 = *var_a1_5;
            var_v1_5 = 0;
loop_17:
            var_v1_5 += 1;
            *temp_a0_4 &= temp_a3;
            if (var_v1_5 < 4) {
                goto loop_17;
            }
            var_a2_4 += 1;
            var_a1_5 += 4;
        } while (var_a2_4 < 3);
        if (D_8022A254_ovl_1BA050 & 1) {
            var_a0_2 = 0;
            var_v1_6 = &D_800C47F0;
            do {
                FIELD(*var_v1_6, s8, 2) = 0;
                var_a0_2 += 1;
                FIELD(*var_v1_6, s8, 3) = 0;
                var_v1_6 += 4;
            } while (var_a0_2 < 4);
        }
        var_a2_5 = 0;
        if (D_8022A254_ovl_1BA050 & 2) {
            var_a1_6 = &D_80229D10_ovl_1BA050;
            do {
                temp_a0_5 = *var_a1_6;
                var_a2_5 += 1;
                *temp_a0_5 |= D_8022A828_ovl_1BA050;
                var_a1_6 += 4;
            } while (var_a2_5 < 6U);
            D_8022A254_ovl_1BA050 &= 0xFFFD;
        }
        var_a2_6 = 0;
        var_a1_7 = &D_80229D28_ovl_1BA050;
        do {
            temp_a0_6 = *var_a1_7;
            var_a2_6 += 1;
            *temp_a0_6 |= D_8022A256_ovl_1BA050;
            var_a1_7 += 4;
        } while (var_a2_6 < 3U);
        if (D_8022A250_ovl_1BA050 != 0) {
            ((s32 (*)(u16 *, u16 **, u32, s32)) D_8022A250_ovl_1BA050)(temp_a0_6, var_a1_7, var_a2_6, temp_a3);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/1BA050", func_802214D0_ovl_1BA050);
#endif

void func_80221750_ovl_1BA050(ScriptCtx *ctx) {
    bzero(ctx, 0x38);
}

INCLUDE_ASM("asm/nonmatchings/1BA050", func_8022176C_ovl_1BA050);

/* Script command: open window cmd[3] with text cmd->w8 at (h4, h6), flags cmd[1]; registers it with
 * value cmd[2] + 1 */
s32 func_802218E4_ovl_1BA050(u8 *ctx) {
    s32 k = *(s32 *)(*(u8 **)(ctx + 8) + 8);
    u8 *cmd;
    u8 *text;
    s32 i;
    u16 id;
    u8 v;

    if (D_8022A214_ovl_1BA050 == NULL) {
        for (;;);
    }
    text = (u8 *)D_8022A214_ovl_1BA050 + D_8022A214_ovl_1BA050[k];
    func_8022905C_ovl_1BA050((*(u8 **)(ctx + 8))[3], text,
                             *(s16 *)(*(u8 **)(ctx + 8) + 4), *(s16 *)(*(u8 **)(ctx + 8) + 6), (*(u8 **)(ctx + 8))[1]);
    cmd = *(u8 **)(ctx + 8);
    id = cmd[3] | 0x5400;
    v = cmd[2] + 1;
    for (i = 0; i < 8; i++) {
        if (D_8022A1F0_ovl_1BA050[i].used == 0) {
            break;
        }
    }
    if (i >= 8) {
        for (;;) {
        }
    }
    D_8022A1F0_ovl_1BA050[i].id = id;
    D_8022A1F0_ovl_1BA050[i].value = v;
    D_8022A1F0_ovl_1BA050[i].used = 1;
    *(u8 **)(ctx + 8) += 12;
    return 0;
}

ScriptCtx *func_802219E0_ovl_1BA050(u8 *base, s32 off, s32 idx) {
    ScriptCtx *c;

    if (idx < 0 || idx >= D_8022A230_ovl_1BA050) {
        for (;;) {
        }
    }
    c = (ScriptCtx *)(D_8022A234_ovl_1BA050 + idx * 0x38);
    bzero(c, 0x38);
    c->pc = base + off;
    c->unk00 = 1;
    c->base = base;
    return c;
}

/* Starts a script context at base + off in the first free slot */
ScriptCtx *func_80221A6C_ovl_1BA050(u8 *base, s32 off) {
    ScriptCtx *ctx;
    s32 i;

    if (!D_801936E0) {
        return NULL;
    }
    if (D_8022A234_ovl_1BA050 == NULL) {
        for (;;) {
        }
    }
    for (i = 0; i < D_8022A230_ovl_1BA050; i++) {
        if (D_8022A234_ovl_1BA050[i * 0x38] == 0) {
            break;
        }
    }
    if (i < 0 || i >= D_8022A230_ovl_1BA050) {
        for (;;) {
        }
    }
    ctx = (ScriptCtx *)(D_8022A234_ovl_1BA050 + i * 0x38);
    bzero(ctx, 0x38);
    ctx->pc = base + off;
    ctx->base = base;
    ctx->unk00 = 1;
    return ctx;
}

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80221B5C_ovl_1BA050);

void func_80221CB8_ovl_1BA050(void) {
    if (D_801936E0) {
        HFree(D_8022A234_ovl_1BA050);
        func_80229930_ovl_1BA050();
        func_80228EE4_ovl_1BA050();
        func_80228378_ovl_1BA050();
        func_80224E1C_ovl_1BA050();
        func_80224BE8_ovl_1BA050();
        D_80196AEC &= 0x7F;
        func_80079618(0x21C3C38, -0x11);
    }
}

/* Sets up the event system for the current scenario (D_801936E0): loads its event overlay and script state */
void func_80221D30_ovl_1BA050(void) {
    OvlDesc *o;
    EvSetup *e;

    if (D_801936E0 == 0) {
        return;
    }
    D_8022A230_ovl_1BA050 = 8;
    D_8022A234_ovl_1BA050 = HMalloc(0x1C0);
    bzero(D_8022A234_ovl_1BA050, 0x1C0);
    D_8022A82C_ovl_1BA050 = 0;
    bzero(D_8022A218_ovl_1BA050, 0x18);
    D_8022A254_ovl_1BA050 = 0;
    D_8022A256_ovl_1BA050 = 0;
    D_8022A828_ovl_1BA050 = 0;
    D_8022A830_ovl_1BA050 = 0;
    D_8022A822_ovl_1BA050 = 0;
    bzero(D_8022A1F0_ovl_1BA050, 0x20);
    o = &D_80229DBC_ovl_1BA050[D_801936E0];
    D_8022A214_ovl_1BA050 = NULL;
    D_8022A210_ovl_1BA050 = -1;
    if (o->vram != NULL) {
        osInvalICache(o->textStart, o->textEnd - o->textStart);
        osInvalDCache(o->dataStart, o->dataEnd - o->dataStart);
        RomRead(o->romStart, o->vram, o->romEnd - o->romStart);
        if (o->bssEnd != o->bssStart) {
            bzero(o->bssStart, o->bssEnd - o->bssStart);
        }
    }
    e = &D_80229E68_ovl_1BA050[D_801936E0];
    D_8022A238_ovl_1BA050 = e->a;
    D_8022A23C_ovl_1BA050 = e->b;
    if (e->init != NULL) {
        e->init();
    }
    D_8022A240_ovl_1BA050 = e->c;
    D_8022A244_ovl_1BA050 = e->d;
    D_8022A248_ovl_1BA050 = e->e;
    D_8022A24C_ovl_1BA050 = e->f;
    func_80224C60_ovl_1BA050();
    func_80220F64_ovl_1BA050(0x5100, 0xFF);
    func_80224D60_ovl_1BA050();
    func_8022845C_ovl_1BA050();
    func_80228F54_ovl_1BA050();
    func_8022995C_ovl_1BA050();
    func_80220F64_ovl_1BA050(0x5500, 0);
    func_8022126C_ovl_1BA050();
    D_80196AEC |= 0x80;
}

/* nop */
s32 func_8022200C_ovl_1BA050(ScriptCtx *ctx) {
    ctx->pc += 4;
    return 0;
}

s32 func_80222020_ovl_1BA050(ScriptCtx *ctx) {
    bzero(ctx, 0x38);
    return 1;
}

/* wait n frames (n = -1: forever) */
s32 func_80222040_ovl_1BA050(ScriptCtx *ctx) {
    s32 r = 0;
    s16 n;

    if (ctx->state == 0) {
        ctx->cond = 0;
        ctx->state = 1;
    }
    n = *(s16 *)(ctx->pc + 2);
    if (n == -1) {
        r = 1;
    } else if ((s16)ctx->cond < n) {
        ctx->cond++;
        r = 1;
    } else {
        ctx->state = 0;
        ctx->pc += 4;
    }
    return r;
}

/* loop start: push a counter and the loop address */
s32 func_802220B4_ovl_1BA050(ScriptCtx *ctx) {
    u8 *ret;

    if (ctx->loopDepth >= 4) {
        for (;;) {
        }
    }
    ctx->loopCount[ctx->loopDepth++] = 0;
    ret = ctx->pc;
    if (ctx->depth >= 4) {
        for (;;) {
        }
    }
    ctx->stack[ctx->depth++] = ret;
    ctx->pc += 4;
    return 0;
}

/* loop end: count up and jump back, or pop the loop */
s32 func_8022212C_ovl_1BA050(ScriptCtx *ctx) {
    s16 n;
    u16 *p;
    u8 *start;

    if (ctx->loopDepth == 0) {
        for (;;) {
        }
    }
    p = &ctx->loopCount[ctx->loopDepth - 1];
    start = ctx->stack[ctx->depth - 1];
    n = ++*p;
    if (*(s16 *)(start + 2) < 0 || n < *(s16 *)(start + 2)) {
        ctx->pc = start + 4;
    } else {
        if (ctx->depth == 0) {
            for (;;) {
            }
        }
        ctx->depth--;
        ctx->loopDepth--;
        ctx->pc += 4;
    }
    return 0;
}

/* call: push the return address (at most 4 deep) and jump */
s32 func_802221D0_ovl_1BA050(ScriptCtx *ctx) {
    u8 *ret = ctx->pc + 8;

    if (ctx->depth >= 4) {
        for (;;) {
        }
    }
    ctx->stack[ctx->depth++] = ret;
    ctx->pc = (u8 *)(*(s32 *)(ctx->pc + 4) + (s32)ctx->base);
    return 0;
}

/* return from a call; hangs on an empty stack */
s32 func_80222220_ovl_1BA050(ScriptCtx *ctx) {
    if (ctx->depth == 0) {
        for (;;) {
        }
    }
    ctx->depth--;
    ctx->pc = ctx->stack[ctx->depth];
    return 0;
}

/* jump */
s32 func_8022225C_ovl_1BA050(ScriptCtx *ctx) {
    ctx->pc = (u8 *)(*(s32 *)(ctx->pc + 4) + (s32)ctx->base);
    return 0;
}

/* jump if the condition is set */
s32 func_80222278_ovl_1BA050(ScriptCtx *ctx) {
    ctx->pc = ctx->cond ? (u8 *)(*(s32 *)(ctx->pc + 4) + (s32)ctx->base) : ctx->pc + 8;
    return 0;
}

/* jump if the condition is clear */
s32 func_802222AC_ovl_1BA050(ScriptCtx *ctx) {
    ctx->pc = !ctx->cond ? (u8 *)(*(s32 *)(ctx->pc + 4) + (s32)ctx->base) : ctx->pc + 8;
    return 0;
}

/* jump through a table indexed by the condition value (1-based); fall through when 0 */
s32 func_802222E0_ovl_1BA050(ScriptCtx *ctx) {
    u16 n = ctx->cond;

    if (n != 0) {
        ctx->pc = (u8 *)(((s32 *)(*(s32 *)(ctx->pc + 4) + (s32)ctx->base))[n - 1] + (s32)ctx->base);
    } else {
        ctx->pc += 8;
    }
    return 0;
}

#ifdef NON_MATCHING
/* Branch layout differs by one instruction. */
s32 func_80222328_ovl_1BA050(ScriptCtx *ctx) {
    s32 r = 1;

    if (ctx->state == 0) {
        if (func_80227F68_ovl_1BA050(*(u16 *)(ctx->pc + 2))) {
            ctx->state = 1;
        }
    } else if (ctx->state == 1) {
        r = 0;
        ctx->state = 0;
        ctx->pc += 4;
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/1BA050", func_80222328_ovl_1BA050);
#endif

s32 func_8022239C_ovl_1BA050(ScriptCtx *c) {
    void *o = func_8017F334(c->pc[3] | 0x5200);

    if (o == NULL) {
        for (;;) {
        }
    }
    if (c->pc[2] != 0) {
        func_8017C384(o);
    } else {
        func_8017C2FC(o);
    }
    c->pc += 4;
    return 0;
}

s32 func_80222418_ovl_1BA050(ScriptCtx *ctx) {
    u8 *o = func_80226164_ovl_1BA050(ctx->pc[3]);

    o[0x10] |= ctx->pc[2];
    ctx->pc += 4;
    return 0;
}

s32 func_80222468_ovl_1BA050(ScriptCtx *ctx) {
    u8 *o = func_80226164_ovl_1BA050(ctx->pc[3]);

    o[0x10] &= ~ctx->pc[2];
    ctx->pc += 4;
    return 0;
}

/* run effect id (operand 3) if operand 2 is set, waiting for it to finish */
s32 func_802224BC_ovl_1BA050(ScriptCtx *ctx) {
    u8 *pc = ctx->pc;
    u8 id = pc[3];
    s32 r = 1;

    switch (ctx->state) {
        case 0:
            if (pc[2] != 0) {
                func_80228FE8_ovl_1BA050(id);
                ctx->state++;
            } else {
                r = 0;
            }
            break;
        case 1:
            r = func_80229040_ovl_1BA050(id) == 0;
            break;
    }
    if (!r) {
        func_80228E88_ovl_1BA050(id);
        ctx->state = 0;
        ctx->pc += 4;
    }
    return r;
}

s32 func_80222564_ovl_1BA050(ScriptCtx *ctx) {
    s32 v = *(s32 *)(ctx->pc + 4);

    ctx->pc = ctx->pc + 8;
    D_8022A82C_ovl_1BA050 = v;
    return 0;
}

/* wait until D_8022A82C equals the operand */
s32 func_80222588_ovl_1BA050(ScriptCtx *ctx) {
    s32 r = 0;

    if (D_8022A82C_ovl_1BA050 == *(s32 *)(ctx->pc + 4)) {
        D_8022A82C_ovl_1BA050 = 0;
        ctx->pc += 8;
    } else {
        r = 1;
    }
    return r;
}

s32 func_802225C4_ovl_1BA050(ScriptCtx *ctx) {
    u16 a = D_8022A830_ovl_1BA050 | *(u16 *)(ctx->pc + 2);
    u16 b = D_8022A822_ovl_1BA050 | *(u16 *)(ctx->pc + 2);

    ctx->pc += 4;
    D_8022A830_ovl_1BA050 = a;
    D_8022A822_ovl_1BA050 = b;
    return 0;
}

/* Same operations; the order of the loads and stores around the volatile pc differs. */
s32 func_80222610_ovl_1BA050(ScriptCtx *ctx)
{
  u16 a = ~(*((u16 *) (ctx->pc + 2)));
  u16 b = ~(*((u16 *) (ctx->pc + 2)));
  ctx->pc += 4;
  D_8022A830_ovl_1BA050 &= a;
  D_8022A822_ovl_1BA050 &= b;
  return 0;
}

s32 func_80222664_ovl_1BA050(ScriptCtx *ctx) {
    D_8022A254_ovl_1BA050 |= 1;
    ctx->pc += 4;
    return 0;
}

s32 func_8022268C_ovl_1BA050(ScriptCtx *ctx) {
    D_8022A254_ovl_1BA050 &= ~1;
    ctx->pc += 4;
    return 0;
}

/* Same operations; the order of the loads and stores around the volatile pc differs. */
s32 func_802226B4_ovl_1BA050(ScriptCtx *ctx)
{
  u16 a = D_8022A828_ovl_1BA050 | (*((u16 *) (ctx->pc + 2)));
  ScriptCtx *new_var;
  D_8022A254_ovl_1BA050 |= 2;
  new_var = ctx;
  new_var->pc += 4;
  D_8022A828_ovl_1BA050 = a;
  return 0;
}

s32 func_802226F8_ovl_1BA050(ScriptCtx *ctx) {
    D_8022A256_ovl_1BA050 |= *(u16 *)(ctx->pc + 2);
    ctx->pc += 4;
    return 0;
}

s32 func_80222728_ovl_1BA050(ScriptCtx *ctx) {
    u16 bits = *(u16 *)(ctx->pc + 2);

    ctx->pc += 4;
    D_8022A256_ovl_1BA050 &= ~bits;
    return 0;
}

s32 func_8022275C_ovl_1BA050(ScriptCtx *ctx) {
    u8 *pc = ctx->pc;

    func_802219E0_ovl_1BA050(*(u8 **)(pc + 4), *(s32 *)(pc + 8), *(u16 *)(pc + 2));
    ctx->pc += 12;
    return 0;
}

s32 func_802227A0_ovl_1BA050(ScriptCtx *ctx) {
    u8 *p = D_8022A234_ovl_1BA050 + *(u16 *)(ctx->pc + 2) * 0x38;

    if (p[0] == 0) {
        for (;;) {
        }
    }
    bzero(p, 0x38);
    ctx->pc += 4;
    return 0;
}

s32 func_8022280C_ovl_1BA050(ScriptCtx *ctx) {
    *func_80222EEC_ovl_1BA050(*(u16 *)(ctx->pc + 2)) = 0;
    ctx->pc += 4;
    return 0;
}

s32 func_8022284C_ovl_1BA050(ScriptCtx *c) {
    u8 *o = func_80222EA0_ovl_1BA050(c->pc[1]);

    o[0] = 1;
    U16AT(o, 2) = U16AT(c->pc, 4);
    U16AT(o, 4) = U16AT(c->pc, 6);
    U16AT(o, 0x10) = 0;
    U16AT(o, 0xE) = 0;
    U16AT(o, 6) = U16AT(o, 0xA) = U16AT(o, 2);
    U16AT(o, 8) = U16AT(o, 0xC) = U16AT(o, 4);
    func_80224268_ovl_1BA050(o, U16AT(c->pc, 2), 1);
    c->pc += 8;
    return 0;
}

s32 func_802228DC_ovl_1BA050(ScriptCtx *c) {
    u8 *o = func_80222EEC_ovl_1BA050(c->pc[1]);

    if (o[0] != 1) {
        for (;;) {
        }
    }
    U16AT(o, 6) = U16AT(o, 2);
    U16AT(o, 8) = U16AT(o, 4);
    U16AT(o, 0xA) = U16AT(c->pc, 4);
    U16AT(o, 0xC) = U16AT(c->pc, 6);
    U16AT(o, 0xE) = U16AT(c->pc, 2);
    U16AT(o, 0x10) = 0;
    c->pc += 8;
    return 0;
}

s32 func_8022296C_ovl_1BA050(ScriptCtx *ctx) {
    u8 *o = func_80222EEC_ovl_1BA050(ctx->pc[1]);

    if (*o != 1) {
        for (;;) {
        }
    }
    func_80224268_ovl_1BA050(o, *(u16 *)(ctx->pc + 2), 1);
    ctx->pc += 4;
    return 0;
}

s32 func_802229D4_ovl_1BA050(ScriptCtx *ctx) {
    u8 *o = func_80222EEC_ovl_1BA050(ctx->pc[1]);

    if (*o != 1) {
        for (;;) {
        }
    }
    func_80224320_ovl_1BA050(o, *(u16 *)(ctx->pc + 2));
    ctx->pc += 4;
    return 0;
}

s32 func_80222A38_ovl_1BA050(ScriptCtx *ctx) {
    u8 *o = func_80222EEC_ovl_1BA050(ctx->pc[1]);

    if (*o != 1) {
        for (;;) {
        }
    }
    func_80224268_ovl_1BA050(o, *(u16 *)(ctx->pc + 2), 0);
    ctx->pc += 4;
    return 0;
}

s32 func_80222AA0_ovl_1BA050(ScriptCtx *ctx) {
    u8 *o = func_80222EA0_ovl_1BA050(*(u16 *)(ctx->pc + 2));

    o[0] = 2;
    *(u16 *)(o + 2) = *(u16 *)(ctx->pc + 4);
    *(u16 *)(o + 4) = *(u16 *)(ctx->pc + 6);
    *(s16 *)(o + 6) = -20;
    *(s16 *)(o + 8) = -20;
    *(s16 *)(o + 0xA) = 20;
    *(s16 *)(o + 0xC) = 20;
    *(s16 *)(o + 0xE) = -12;
    *(s16 *)(o + 0x10) = -12;
    *(s16 *)(o + 0x12) = 12;
    *(s16 *)(o + 0x14) = 12;
    o[0x16] = 16;
    ctx->pc += 8;
    return 0;
}

/* hitbox set from operands: symmetric extents (-x..x, -y..y) */
s32 func_80222B34_ovl_1BA050(ScriptCtx *ctx) {
    u8 *o = func_80222EEC_ovl_1BA050(ctx->pc[1]);
    u8 *p;
    s16 x0;
    s16 x1;
    s16 y0;
    s16 y1;

    if (o[0] != 2) {
        for (;;) {
        }
    }
    o[0x16] = *(u16 *)(ctx->pc + 2);
    p = ctx->pc;
    x0 = *(u16 *)(p + 4);
    x1 = *(u16 *)(p + 6);
    y0 = *(u16 *)(p + 8);
    y1 = *(u16 *)(p + 0xA);
    *(s16 *)(o + 6) = -x0;
    *(s16 *)(o + 8) = -x1;
    *(s16 *)(o + 0xE) = -y0;
    *(s16 *)(o + 0xA) = x0;
    *(s16 *)(o + 0xC) = x1;
    *(s16 *)(o + 0x10) = -y1;
    *(s16 *)(o + 0x12) = y0;
    *(s16 *)(o + 0x14) = y1;
    ctx->pc += 0xC;
    return 0;
}

/* hitbox set from operands: explicit extents */
s32 func_80222BDC_ovl_1BA050(ScriptCtx *ctx) {
    u8 *o = func_80222EEC_ovl_1BA050(ctx->pc[1]);

    if (o[0] != 2) {
        for (;;) {
        }
    }
    o[0x16] = *(u16 *)(ctx->pc + 2);
    *(s16 *)(o + 6) = *(u16 *)(ctx->pc + 4);
    *(s16 *)(o + 8) = *(u16 *)(ctx->pc + 6);
    *(s16 *)(o + 0xA) = *(u16 *)(ctx->pc + 8);
    *(s16 *)(o + 0xC) = *(u16 *)(ctx->pc + 0xA);
    *(s16 *)(o + 0xE) = *(u16 *)(ctx->pc + 0xC);
    *(s16 *)(o + 0x10) = *(u16 *)(ctx->pc + 0xE);
    *(s16 *)(o + 0x12) = *(u16 *)(ctx->pc + 0x10);
    *(s16 *)(o + 0x14) = *(u16 *)(ctx->pc + 0x12);
    ctx->pc += 0x14;
    return 0;
}

s32 func_80222CA0_ovl_1BA050(ScriptCtx *ctx) {
    *func_80222EA0_ovl_1BA050(*(u16 *)(ctx->pc + 2)) = 3;
    ctx->pc += 4;
    return 0;
}

static inline void func_80222CE4_clear(void) {
    if (D_8022A248_ovl_1BA050 != NULL && D_8022A24C_ovl_1BA050 != 0) {
        bzero(D_8022A248_ovl_1BA050, D_8022A24C_ovl_1BA050);
    }
    D_8022A250_ovl_1BA050 = 0;
}

/* select message table entry (mode 0) or clear it (mode 1) */
s32 func_80222CE4_ovl_1BA050(ScriptCtx *ctx) {
    switch (ctx->pc[1]) {
        case 0: {
            s32 v;

            if (D_8022A248_ovl_1BA050 != NULL && D_8022A24C_ovl_1BA050 != 0) {
                bzero(D_8022A248_ovl_1BA050, D_8022A24C_ovl_1BA050);
            }
            v = ((s32 *)D_8022A244_ovl_1BA050)[*(u16 *)(ctx->pc + 2)];
            D_8022A250_ovl_1BA050 = 0;
            D_8022A250_ovl_1BA050 = v;
            break;
        }
        case 1:
            func_80222CE4_clear();
            break;
    }
    ctx->pc += 4;
    return 0;
}

s32 func_80222DBC_ovl_1BA050(ScriptCtx *ctx) {
    u8 *pc = ctx->pc;
    s32 v = *(s16 *)(pc + 2);

    switch (pc[1]) {
        case 0:
            D_800E9C0A[6] = v;
            break;
        case 1:
            D_800E9C0A[9] = v;
            break;
    }
    ctx->pc += 4;
    return 0;
}

s32 func_80222E08_ovl_1BA050(ScriptCtx *ctx) {
    switch (ctx->pc[3]) {
        case 0:
            D_8022A821_ovl_1BA050 = 2;
            break;
        case 1:
            D_8022A821_ovl_1BA050 = 1;
            break;
    }
    ctx->pc += 4;
    return 0;
}

s32 func_80222E48_ovl_1BA050(ScriptCtx *ctx) {
    func_80229604_ovl_1BA050(*(s32 *)(ctx->pc + 4));
    ctx->pc += 8;
    return 0;
}

s32 func_80222E84_ovl_1BA050(ScriptCtx *ctx) {
    ctx->pc += 8;
    return 0;
}
