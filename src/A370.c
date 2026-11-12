#include "common.h"

typedef struct {
    /* 0x00 */ u8 *hdr;
    /* 0x04 */ u8 *ptrs[1];
} ArcCtx;

typedef struct {
    /* 0x00 */ u8 unk00[8];
    /* 0x08 */ u8 done;
} ArcMsg;

extern u8 D_800AF320[];
extern u8 *D_800AF390;
extern u16 *D_800AF3F8;
extern s16 D_800AF3C6;
extern s32 D_800AF3CC;
extern s16 D_800AF3C8;
extern s16 D_800AF39E;
extern s32 D_800AF3E8;
extern u32 D_800AF3F4;
extern u16 D_800AF3A4;
extern char D_800AE30C[];
extern char D_800AE31C[];
extern char D_800AE324[];
extern char D_800AE334[];
s32 osSendMesg(void *mq, void *msg, s32 flag);
void osSyncPrintf(const char *fmt, ...);
u16 func_8007C25C(s32 n);



void func_8007C438();

INCLUDE_ASM("asm/nonmatchings/A370", func_80079F70);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007A070);

INCLUDE_ASM("asm/nonmatchings/A370", DecodeLZ);

u32 ReadU32BE(u8 *p) {
    return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
}

INCLUDE_ASM("asm/nonmatchings/A370", func_8007A80C);

s32 func_8007AB30(ArcCtx *c, s32 i) {
    u8 *h = c->hdr;
    u8 *p = c->ptrs[i];

    if (h[0] == 0 || h[0] == 1 || h[0] == 2) {
        return (h[2] << 8) | h[3];
    }
    return (p[0] << 8) | p[1];
}

void func_8007AB7C(ArcMsg *m) {
    m->done = 1;
    osSendMesg(&D_800AF320, m, 1);
}

INCLUDE_ASM("asm/nonmatchings/A370", func_8007ABAC);

INCLUDE_ASM("asm/nonmatchings/A370", UnpackProc);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007ACB0);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007AE9C);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007AF3C);

INCLUDE_RODATA("asm/nonmatchings/A370", D_800AE060);

INCLUDE_RODATA("asm/nonmatchings/A370", D_800AE068);

INCLUDE_RODATA("asm/nonmatchings/A370", D_800AE070);

INCLUDE_RODATA("asm/nonmatchings/A370", D_800AE078);

INCLUDE_RODATA("asm/nonmatchings/A370", D_800AE080);

INCLUDE_RODATA("asm/nonmatchings/A370", D_800AE088);

INCLUDE_RODATA("asm/nonmatchings/A370", D_800AE090);

INCLUDE_RODATA("asm/nonmatchings/A370", D_800AE098);

INCLUDE_RODATA("asm/nonmatchings/A370", D_800AE0A0);

INCLUDE_RODATA("asm/nonmatchings/A370", D_800AE0A8);

INCLUDE_RODATA("asm/nonmatchings/A370", D_800AE0AC);

INCLUDE_RODATA("asm/nonmatchings/A370", D_800AE0C8);

INCLUDE_ASM("asm/nonmatchings/A370", get_header);

s32 func_8007B710(void) {
    s32 lo = *D_800AF390++;
    s32 hi = *D_800AF390++;

    return (hi << 8) | lo;
}

INCLUDE_ASM("asm/nonmatchings/A370", func_8007B744);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007B7A8);

/* Converts a path to lower case with forward slashes. */
void func_8007B83C(u8 *s, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        u8 c = s[i];

        if (c == 0x5C /* '\' */) {
            s[i] = '/';
        } else if (c >= 'A' && c <= 'Z') {
            s[i] = c + 0x20;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/A370", extract_one);

INCLUDE_RODATA("asm/nonmatchings/A370", D_800AE2AC);

INCLUDE_RODATA("asm/nonmatchings/A370", D_800AE2D4);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007BA98);

/* Swaps ':' and '/' in a path. */
void func_8007BB48(u8 *s, s32 n) {
    s32 i;

    for (i = 0; i < n; i++) {
        u8 c = s[i];

        if (c == ':') {
            s[i] = '/';
        } else if (c == '/') {
            s[i] = ':';
        }
    }
}

void func_8007BB90(s32 a, s32 b) {
    osSyncPrintf(D_800AE30C, D_800AE31C, a, b);
}

void func_8007BBC0(s32 a) {
    osSyncPrintf(D_800AE30C, D_800AE324, D_800AE334, a);
}

void func_8007BBF4(s32 a, s32 b) {
    osSyncPrintf(D_800AE30C, D_800AE324, a, b);
}

INCLUDE_RODATA("asm/nonmatchings/A370", D_800AE30C);

INCLUDE_RODATA("asm/nonmatchings/A370", D_800AE31C);

INCLUDE_RODATA("asm/nonmatchings/A370", D_800AE324);

INCLUDE_RODATA("asm/nonmatchings/A370", D_800AE334);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007BC24);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007BF10);

/* Builds the CRC-16 (polynomial 0xA001) table. */
void func_8007C204(void) {
    u32 i, j, r;

    for (i = 0; i < 256; i++) {
        r = i;
        for (j = 0; j < 8; j++) {
            if (r & 1) {
                r = (r >> 1) ^ 0xA001;
            } else {
                r >>= 1;
            }
        }
        D_800AF3F8[i] = r;
    }
}

INCLUDE_ASM("asm/nonmatchings/A370", func_8007C25C);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007C378);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007C438);

/* Replaces path separators ('\', '/', 0xFF) with sep; returns the start of the last component. */
u8 *func_8007C538(u8 *s, u8 sep) {
    u8 *p = s;
    u8 c;

    while ((c = *p) != 0) {
        if (c == 0x5C /* '\' */ || c == '/' || c == 0xFF) {
            *p = sep;
            s = p + 1;
        }
        p++;
    }
    return s;
}

INCLUDE_ASM("asm/nonmatchings/A370", func_8007C590);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007C74C);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007CAB8);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007CE48);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007D200);

void func_8007D594(void) {
    func_8007C438();
    D_800AF3C6 = 0;
}

INCLUDE_ASM("asm/nonmatchings/A370", func_8007D5B8);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007D7BC);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007D8A8);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007DBF4);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007DDF0);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007DFF0);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007E2F8);

void func_8007E698(void) {
    D_800AF3CC = 0x11E;
    D_800AF3C8 = 0;
    D_800AF39E = 0x100;
    func_8007C438();
    D_800AF3E8 = 0x80;
}

INCLUDE_ASM("asm/nonmatchings/A370", func_8007E6DC);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007E800);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007E8F0);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007EE2C);

u16 func_8007F1A0(void) {
    u16 r;

    if (func_8007C25C(1) == 0) {
        D_800AF3F4 = func_8007C25C(11);
        r = func_8007C25C(4) + 0x100;
    } else {
        r = func_8007C25C(8);
    }
    return r;
}

u16 func_8007F1F8(void) {
    return (D_800AF3A4 - D_800AF3F4 - 0x12) & 0x7FF;
}

void func_8007F218(void) {
    func_8007C438();
}

INCLUDE_ASM("asm/nonmatchings/A370", func_8007F234);

u16 func_8007F314(void) {
    return (D_800AF3A4 - D_800AF3F4 - 0x13) & 0xFFF;
}

INCLUDE_ASM("asm/nonmatchings/A370", func_8007F334);

u8 *func_8007F408(u8 *d, u8 *s) {
    u8 *p = d;

    while (*p != 0) {
        p++;
    }
    while (*s != 0) {
        *p++ = *s++;
    }
    *p = 0;
    return d;
}

u8 *func_8007F450(u8 *d, u8 *s) {
    u8 *p = d;

    while (*s != 0) {
        *p++ = *s++;
    }
    *p = 0;
    return d;
}

s32 func_8007F47C(u8 *a, u8 *b) {
    u8 c1 = *a++;
    u8 c2 = *b++;

    if (c1 != c2) {
        return c1 - c2;
    }
    if (c1 == 0) {
        return 0;
    }
    return func_8007F47C(a, b);
}

void *func_8007F4B0(void *d, u8 c, u32 n) {
    u8 *p = d;

    while (n-- != 0) {
        *p++ = c;
    }
    return d;
}

INCLUDE_ASM("asm/nonmatchings/A370", func_8007F4E4);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007F570);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007F5D8);

void func_8007F640(void) {
}

INCLUDE_ASM("asm/nonmatchings/A370", func_8007F648);

/* Counts characters in a Shift-JIS string (lead bytes >= 0x80 take two bytes). */
s32 func_8007F844(u8 *s) {
    s32 n = 0;
    u8 c;

    while ((c = *s++) != 0) {
        s += c >> 7;
        n++;
    }
    return n;
}
