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
#define c_len D_800AF404
#define c_table D_800AF40C
#define pt_len D_800AF408
#define pt_code D_800AF414
#define pt_table D_800AF410
#define n_max D_800AF3CC
#define maxmatch D_800AF39E
#define np D_800AF3E8
#define freq D_800AF430
#define child D_800AF418
#define s_node D_800AF42C
#define block D_800AF420
#define stock D_800AF428
#define edge D_800AF424
#define avail D_800AF3D4
#define most_p D_800AF3DC
#define total_p D_800AF3D0
#define nn D_800AF3E0
#define nextcount D_800AF3E4
#define dicbit D_800AF39C
#define n1 D_800AF3D8
#define parent D_800AF41C

extern s32 D_800AF3D8;
extern s16 *D_800AF41C;

extern u8 *D_800AF404;
extern u16 *D_800AF40C;
extern u8 *D_800AF408;
extern u16 *D_800AF414;
extern u16 *D_800AF410;
extern s32 D_800A87CC; /* fixed[0][0] */
extern s32 D_800A87D0[];
extern u16 *D_800AF430;
extern s16 *D_800AF418;
extern s16 *D_800AF42C;
extern s16 *D_800AF420;
extern s16 *D_800AF428;
extern s16 *D_800AF424;
extern s32 D_800AF3D4;
extern s32 D_800AF3DC;
extern u16 D_800AF3D0;
extern s32 D_800AF3E0;
extern s32 D_800AF3E4;
extern u16 D_800AF39C;
void func_8007BC24(s16 nchar, u8 *bitlen, s16 tablebits, u16 *table);
void func_8007D5B8(void);

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
typedef struct {
    /* 0x00 */ void *name;
    /* 0x04 */ u8 unk04[4];
    /* 0x08 */ u8 *buf;
    /* 0x0C */ s32 size;
} ArcReq;

typedef struct {
    /* 0x000 */ u8 unk00[8];
    /* 0x008 */ s32 packed_size;
    /* 0x00C */ u8 unk0C[0x124];
} LzHeader; /* size 0x130 */

typedef struct {
    void **ptr;
    s32 size;
} BufDesc;

extern BufDesc D_800A884C[];
extern u8 D_800AF320[];
extern u8 D_800AF300[];
extern u8 D_800AF0D0[0x1B0]; /* OSThread */
extern u64 D_800AF280[0x80 / 8]; /* its stack */
extern u8 D_800AE0A8[];
void UnpackProc(void *arg);
void osCreateMesgQueue(void *mq, void *msgs, s32 n);
void osCreateThread(void *t, s32 id, void (*entry)(void *), void *arg, void *sp, s32 pri);
void osStartThread(void *t);
void *HMalloc(s32 size);
void *HFree(void *p);
s32 get_header(ArcFile *f, LzHeader *h);
void func_8007AF3C(s32 alloc);
void func_8007C204(void);
void func_8007BBC0(s32 a);
ArcFile *func_8007F4E4(void *name, u8 *mode, u8 *buf, s32 size);
extern u8 *D_800AF390;
extern u16 *D_800AF3F8;
extern s16 D_800AF3C6;
extern s32 D_800AF3CC;
extern s16 D_800AF3C8;
extern u16 D_800AF39E;
extern u32 D_800AF3E8;
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

/* memcpy with word-aligned bulk copy */
void *func_80079F70(void *dst, void *src, u32 n) {
    u8 *d;
    u8 *s;
    u32 i;

    if (n == 0) {
        return dst;
    }
    d = dst;
    s = src;
    if (((u32)s - (u32)d) & 3) {
        while (n-- != 0) {
            *d++ = *s++;
        }
        return dst;
    }
    if ((u32)d & 1) {
        *d++ = *s++;
        n--;
    }
    if (n >= 2 && ((u32)d & 2)) {
        *(u16 *)d = *(u16 *)s;
        s += 2;
        n -= 2;
        d += 2;
    }
    i = n >> 2;
    while (i-- != 0) {
        *(u32 *)d = *(u32 *)s;
        s += 4;
        d += 4;
    }
    if (n & 2) {
        *(u16 *)d = *(u16 *)s;
        s += 2;
        d += 2;
    }
    if (n & 1) {
        *d = *s;
    }
    return dst;
}

/* memset with word-aligned bulk fill */
void *func_8007A070(void *dst, s32 c, u32 n) {
    u8 *d;
    u32 i;

    if (n == 0) {
        return dst;
    }
    c &= 0xFF;
    c |= c << 8;
    c |= c << 16;
    d = dst;
    if ((u32)d & 1) {
        *d = c;
        d++;
        n--;
    }
    if (n >= 2 && ((u32)d & 2)) {
        *(u16 *)d = c;
        d += 2;
        n -= 2;
    }
    i = n >> 2;
    while (i-- != 0) {
        *(u32 *)d = c;
        d += 4;
    }
    if (n & 2) {
        *(u16 *)d = c;
        d += 2;
    }
    if (n & 1) {
        *d = c;
    }
    return dst;
}

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

/* Starts the unpack thread. */
void func_8007ABAC(s32 id, s32 pri) {
    osCreateMesgQueue(D_800AF320, D_800AF300, 8);
    osCreateThread(D_800AF0D0, id, UnpackProc, NULL, D_800AF280 + 0x80 / 8, pri);
    osStartThread(D_800AF0D0);
}

INCLUDE_ASM("asm/nonmatchings/A370", UnpackProc);

INCLUDE_ASM("asm/nonmatchings/A370", func_8007ACB0);

/* Counts the files in an LHa archive held in memory. */
s32 func_8007AE9C(ArcReq *r) {
    LzHeader hdr;
    ArcFile *f;
    s32 n;

    func_8007AF3C(1);
    func_8007C204();
    f = func_8007F4E4(r->name, D_800AE0A8, r->buf, r->size);
    if (f == NULL) {
        func_8007BBC0((s32)r->name);
    }
    n = 0;
    while (get_header(f, &hdr)) {
        f->pos += hdr.packed_size;
        n++;
    }
    f->open = 0;
    func_8007AF3C(0);
    return n;
}

/* Allocates (alloc != 0) or frees the decoder work buffers. */
void func_8007AF3C(s32 alloc) {
    s32 i;

    if (alloc) {
        for (i = 0; D_800A884C[i].ptr != NULL; i++) {
            *D_800A884C[i].ptr = HMalloc(D_800A884C[i].size);
        }
    } else {
        for (i = 0; D_800A884C[i].ptr != NULL; i++) {
            HFree(*D_800A884C[i].ptr);
        }
    }
}

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

/* start_c_dyn */
void func_8007D5B8(void) {
    s32 i, j, f;

    n1 = (n_max >= 256 + maxmatch - 3 + 1) ? 512 : n_max - 1;
    for (i = 0; i < 628; i++) {
        stock[i] = i;
        block[i] = 0;
    }
    for (i = 0, j = n_max * 2 - 2; i < n_max; i++, j--) {
        freq[j] = 1;
        child[j] = ~i;
        s_node[i] = j;
        block[j] = 1;
    }
    avail = 2;
    edge[1] = n_max - 1;
    i = n_max * 2 - 2;
    while (j >= 0) {
        f = freq[j] = freq[i] + freq[i - 1];
        child[j] = i;
        parent[i] = parent[i - 1] = j;
        if (f == freq[j + 1]) {
            edge[block[j] = block[j + 1]] = j;
        } else {
            edge[block[j] = stock[avail++]] = j;
        }
        i -= 2;
        j--;
    }
}

/* decode_start_dyn, with start_p_dyn inlined */
void func_8007D7BC(void) {
    n_max = 286;
    maxmatch = 256;
    func_8007C438();
    func_8007D5B8();
    freq[628] = 1;
    child[628] = ~314;
    s_node[314] = 628;
    edge[block[628] = stock[avail++]] = 628;
    most_p = 628;
    total_p = 0;
    nn = 1 << dicbit;
    nextcount = 64;
}

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

/* read_tree_c */
void func_8007E6DC(void) {
    s32 i, c;

    i = 0;
    while (i < 286) {
        if (func_8007C25C(1)) {
            c_len[i] = func_8007C25C(4) + 1;
        } else {
            c_len[i] = 0;
        }
        if (++i == 3 && c_len[0] == 1 && c_len[1] == 1 && c_len[2] == 1) {
            c = func_8007C25C(9);
            for (i = 0; i < 286; i++) {
                c_len[i] = 0;
            }
            for (i = 0; i < 4096; i++) {
                c_table[i] = c;
            }
            return;
        }
    }
    func_8007BC24(286, c_len, 12, c_table);
}

/* decode_start_fix, with ready_made(0) inlined */
void func_8007E800(void) {
    s32 *tbl;
    s32 i, j;
    u32 code, weight;

    n_max = 314;
    maxmatch = 60;
    func_8007C438();
    np = 1 << (12 - 6);
    func_8007D5B8();
    j = D_800A87CC;
    tbl = D_800A87D0;
    weight = 1 << (16 - j);
    code = 0;
    for (i = 0; i < np; i++) {
        while (*tbl == i) {
            j++;
            tbl++;
            weight >>= 1;
        }
        pt_len[i] = j;
        pt_code[i] = code;
        code += weight;
    }
    func_8007BC24(np, pt_len, 8, pt_table);
}

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
