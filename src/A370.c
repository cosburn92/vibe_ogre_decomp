#include "common.h"

typedef struct {
    /* 0x00 */ u8 *hdr;
    /* 0x04 */ u8 *ptrs[1];
} ArcCtx;

typedef struct {
    /* 0x00 */ u8 unk00[8];
    /* 0x08 */ u8 done;
} ArcMsg;

/* In-memory FILE used by the LHa code: fopen/fread/fwrite/getc work on buf. */
typedef struct {
    /* 0x00 */ u8 open;
    /* 0x04 */ void *name;
    /* 0x08 */ u8 *buf;
    /* 0x0C */ s32 size;
    /* 0x10 */ s32 pos;
    /* 0x14 */ s32 unk14;
} ArcFile; /* size 0x18 */

#define getc(f) ((f)->buf[(f)->pos++])

#define bitbuf D_800AF3C2
#define subbitbuf D_800AF3C4
#define bitcount D_800AF3C5
#define compsize D_800AF398
#define infile D_800AF36C
#define flagcnt D_800AF3F0
#define flag D_800AF3EC
#define matchpos D_800AF3F4
#define text D_800AF3A8

extern s32 D_800AF3F0;
extern s32 D_800AF3EC;
extern u8 *D_800AF3A8;
extern ArcFile D_800AF340;
extern ArcFile D_800AF358;
void *func_8007F4B0(void *d, s32 c, u32 n);

extern u16 D_800AF3C2;
extern u8 D_800AF3C4;
extern u8 D_800AF3C5;
extern s32 D_800AF398;
extern ArcFile *D_800AF36C;
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
u16 func_8007C25C(u8 n);



void func_8007C438(void);

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

s32 func_8007B744(void) {
    s32 b0, b1, b2, b3;

    b0 = *D_800AF390++;
    b1 = *D_800AF390++;
    b2 = *D_800AF390++;
    b3 = *D_800AF390++;
    return (b3 << 24) + (b2 << 16) + (b1 << 8) + b0;
}

/* generic_to_unix_filename: '\' becomes '/', and all-upper-case names are lowered. */
void func_8007B7A8(u8 *name, s32 len) {
    s32 i;
    s32 lower = 0;

    for (i = 0; i < len; i++) {
        if (name[i] >= 'a' && name[i] <= 'z') {
            lower = 1;
            break;
        }
    }
    for (i = 0; i < len; i++) {
        if (name[i] == 0x5C) {
            name[i] = '/';
        } else if (!lower && name[i] >= 'A' && name[i] <= 'Z') {
            name[i] += 0x20;
        }
    }
}

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

static inline void fillbuf(u8 n) {
    while (n > bitcount) {
        n -= bitcount;
        bitbuf = (bitbuf << bitcount) + (subbitbuf >> (8 - bitcount));
        if (compsize != 0) {
            compsize--;
            subbitbuf = infile->buf[infile->pos++];
        } else {
            subbitbuf = 0;
        }
        bitcount = 8;
    }
    bitcount -= n;
    bitbuf = (bitbuf << n) + (subbitbuf >> (8 - n));
    subbitbuf <<= n;
}

/* getbits */
u16 func_8007C25C(u8 n) {
    u16 x = bitbuf >> (16 - n);

    fillbuf(n);
    return x;
}

INCLUDE_ASM("asm/nonmatchings/A370", func_8007C378);

/* init_getbits */
void func_8007C438(void) {
    bitbuf = 0;
    subbitbuf = 0;
    bitcount = 0;
    fillbuf(16);
}

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

/* decode_c_lz5 */
u16 func_8007F234(void) {
    s32 c;

    if (flagcnt == 0) {
        flagcnt = 8;
        flag = getc(infile);
    }
    flagcnt--;
    c = getc(infile);
    if ((flag & 1) == 0) {
        matchpos = c;
        c = getc(infile);
        matchpos += (c & 0xF0) << 4;
        c &= 0x0F;
        c += 0x100;
    }
    flag >>= 1;
    return c;
}

u16 func_8007F314(void) {
    return (D_800AF3A4 - D_800AF3F4 - 0x13) & 0xFFF;
}

/* decode_start_lz5 */
void func_8007F334(void) {
    s32 i;

    flagcnt = 0;
    for (i = 0; i < 256; i++) {
        func_8007F4B0(&text[i * 13 + 18], i, 13);
    }
    for (i = 0; i < 256; i++) {
        text[256 * 13 + 18 + i] = i;
    }
    for (i = 0; i < 256; i++) {
        text[256 * 13 + 256 + 18 + i] = 255 - i;
    }
    func_8007F4B0(&text[256 * 13 + 512 + 18], 0, 128);
    func_8007F4B0(&text[256 * 13 + 512 + 128 + 18], ' ', 128 - 18);
}

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

void *func_8007F4B0(void *d, s32 c, u32 n) {
    u8 *p = d;

    while (n-- != 0) {
        *p++ = c;
    }
    return d;
}

/* fopen on an in-memory buffer: mode "r" uses the read slot, anything else the write slot. */
ArcFile *func_8007F4E4(void *name, u8 *mode, u8 *buf, s32 size) {
    if (mode[0] == 'r') {
        if (D_800AF340.open) {
            return NULL;
        }
        D_800AF340.name = name;
        D_800AF340.buf = buf;
        D_800AF340.size = size;
        D_800AF340.pos = 0;
        return &D_800AF340;
    }
    if (D_800AF358.open) {
        return NULL;
    }
    D_800AF358.name = name;
    D_800AF358.buf = buf;
    D_800AF358.size = size;
    D_800AF358.pos = 0;
    return &D_800AF358;
}

/* fread */
s32 func_8007F570(u8 *dst, s32 size, s32 n, ArcFile *f) {
    s32 i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < size; j++) {
            if (f->pos >= f->size) {
                return i;
            }
            *dst++ = f->buf[f->pos++];
        }
    }
    return i;
}

/* fwrite */
s32 func_8007F5D8(u8 *src, s32 size, s32 n, ArcFile *f) {
    s32 i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < size; j++) {
            if (f->pos >= f->size) {
                return i;
            }
            f->buf[f->pos++] = *src++;
        }
    }
    return i;
}

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
