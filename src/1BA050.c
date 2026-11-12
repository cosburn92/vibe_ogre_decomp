#include "common.h"

/* Event-script interpreter context: opcodes advance pc and return 0 (continue) or 1 (wait). */
typedef struct {
    /* 0x00 */ u8 unk00[4];
    /* 0x04 */ u8 *base;
    /* 0x08 */ u8 *pc;
    /* 0x0C */ u16 depth;
    /* 0x0E */ u8 unk0E[2];
    /* 0x10 */ u8 *stack[7];
    /* 0x2C */ u16 cond;
} ScriptCtx;

extern u8 D_8022A1F0_ovl_1BA050[];
extern u8 *D_8022A248_ovl_1BA050;
extern s32 D_8022A24C_ovl_1BA050;
extern s32 D_8022A250_ovl_1BA050;
extern s32 *D_8022A214_ovl_1BA050;
extern s32 D_8022A82C_ovl_1BA050;
extern u16 D_8022A254_ovl_1BA050;
extern u16 D_8022A256_ovl_1BA050;
extern u8 D_8022A821_ovl_1BA050;
u8 *func_80222EEC_ovl_1BA050(u16 id);
void func_80229604_ovl_1BA050(s32 arg);





void func_80220F40_ovl_1BA050(void) {
    bzero(D_8022A1F0_ovl_1BA050, 0x20);
}

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80220F64_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80220FD0_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80221030_ovl_1BA050);

void func_8022126C_ovl_1BA050(void) {
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

INCLUDE_ASM("asm/nonmatchings/1BA050", func_802212D4_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80221354_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_802213A0_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_802213EC_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80221438_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80221484_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_802214D0_ovl_1BA050);

void func_80221750_ovl_1BA050(ScriptCtx *ctx) {
    bzero(ctx, 0x38);
}

INCLUDE_ASM("asm/nonmatchings/1BA050", func_8022176C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_802218E4_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_802219E0_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80221A6C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80221B5C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80221CB8_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80221D30_ovl_1BA050);

/* nop */
s32 func_8022200C_ovl_1BA050(ScriptCtx *ctx) {
    ctx->pc += 4;
    return 0;
}

s32 func_80222020_ovl_1BA050(ScriptCtx *ctx) {
    bzero(ctx, 0x38);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80222040_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_802220B4_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_8022212C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_802221D0_ovl_1BA050);

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

INCLUDE_ASM("asm/nonmatchings/1BA050", func_802222E0_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80222328_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_8022239C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80222418_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80222468_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_802224BC_ovl_1BA050);

#ifdef NON_MATCHING
/* The original reads ctx->pc twice; GCC merges the reads here. */
s32 func_80222564_ovl_1BA050(ScriptCtx *ctx) {
    s32 v = *(s32 *)(ctx->pc + 4);

    ctx->pc = ctx->pc + 8;
    D_8022A82C_ovl_1BA050 = v;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/1BA050", func_80222564_ovl_1BA050);
#endif

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

INCLUDE_ASM("asm/nonmatchings/1BA050", func_802225C4_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80222610_ovl_1BA050);

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

INCLUDE_ASM("asm/nonmatchings/1BA050", func_802226B4_ovl_1BA050);

#ifdef NON_MATCHING
/* The original reads ctx->pc twice; GCC merges the reads here. */
s32 func_802226F8_ovl_1BA050(ScriptCtx *ctx) {
    u16 bits = *(u16 *)(ctx->pc + 2);

    ctx->pc += 4;
    D_8022A256_ovl_1BA050 |= bits;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/1BA050", func_802226F8_ovl_1BA050);
#endif

#ifdef NON_MATCHING
/* The original reads ctx->pc twice; GCC merges the reads here. */
s32 func_80222728_ovl_1BA050(ScriptCtx *ctx) {
    u16 bits = *(u16 *)(ctx->pc + 2);

    ctx->pc += 4;
    D_8022A256_ovl_1BA050 &= ~bits;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/1BA050", func_80222728_ovl_1BA050);
#endif

INCLUDE_ASM("asm/nonmatchings/1BA050", func_8022275C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_802227A0_ovl_1BA050);

s32 func_8022280C_ovl_1BA050(ScriptCtx *ctx) {
    *func_80222EEC_ovl_1BA050(*(u16 *)(ctx->pc + 2)) = 0;
    ctx->pc += 4;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/1BA050", func_8022284C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_802228DC_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_8022296C_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_802229D4_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80222A38_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80222AA0_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80222B34_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80222BDC_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80222CA0_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80222CE4_ovl_1BA050);

INCLUDE_ASM("asm/nonmatchings/1BA050", func_80222DBC_ovl_1BA050);

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
