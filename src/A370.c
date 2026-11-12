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
#define count D_800AF3A0
#define left D_800AF3FC
#define right D_800AF400
#define blocksize D_800AF3C6

extern u16 *D_800AF3FC;
extern u16 *D_800AF400;
void func_8007C74C(s16 nn, u8 nbit, s16 i_special);
void func_8007CAB8(void);
void func_8007E6DC(void);

extern u32 D_800AF3A0;
void func_8007DDF0(s32 p);

extern s32 D_800AF3D8;
extern s16 *D_800AF41C;

extern u8 *D_800AF404;
extern u16 *D_800AF40C;
extern u8 *D_800AF408;
extern u16 *D_800AF414;
extern u16 *D_800AF410;
extern s32 D_800A87CC; /* fixed[0][0] */
extern s32 D_800A87D0[];
extern s32 D_800A880C; /* fixed[1][0] */
extern s32 D_800A8810[];
extern u16 *D_800AF430;
extern s16 *D_800AF418;
extern s16 *D_800AF42C;
extern s16 *D_800AF420;
extern s16 *D_800AF428;
extern s16 *D_800AF424;
extern s32 D_800AF3D4;
extern s32 D_800AF3DC;
extern u16 D_800AF3D0;
extern u32 D_800AF3E0;
extern u32 D_800AF3E4;
extern u16 D_800AF39C;
void func_8007BC24(s16 nchar, u8 *bitlen, s16 tablebits, u16 *table);
void func_8007D5B8(void);
void func_8007D8A8(s32 start, s32 end);
s32 func_8007DBF4(s32 p);

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
extern u16 D_800AF3C6;
extern s32 D_800AF3CC;
extern u16 D_800AF3C8;
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
u32 ReadU32BE(u8 *p);



void func_8007C438(void);

/* memcpy with word-aligned bulk copy */
inline void *func_80079F70(void *dst, void *src, u32 n) {
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
inline void *func_8007A070(void *dst, s32 c, u32 n) {
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

#ifdef NON_MATCHING
/* Close: register allocation and scheduling around the inlined memcpy/memset differ. */
/* Decompresses an LZ stream: a big-endian size, then op bytes (back references, literal runs,
 * zero and 0xFF fills). memcpy/memset are inline. Returns the size. */
u32 DecodeLZ(u8 *dst, u8 *src) {
    u32 size = ReadU32BE(src);
    u32 done;
    u32 len;
    u8 b;

    src += 4;
    for (done = 0; done < size;) {
        b = *src++;
        if (b & 0x80) {
            u8 lo;

            len = ((b >> 3) & 0xF) + 3;
            lo = *src++;
            func_80079F70(dst + done, dst + done - ((b & 7) << 8) - lo - 1, len);
            done += len;
        } else if (b & 0x40) {
            len = (b & 0x3F) + 1;
            func_80079F70(dst + done, src, len);
            done += len;
            src += len;
        } else if (b & 0x20) {
            len = (b & 0x1F) + 2;
            func_8007A070(dst + done, 0, len);
            done += len;
        } else if (b & 0x10) {
            u8 c1 = *src++;
            u8 c2 = *src++;

            len = ((b & 0xF) | ((c1 >> 2) & 0x30)) + 4;
            func_80079F70(dst + done, dst + done - (((c1 & 0x3F) << 8) | c2) - 1, len);
            done += len;
        } else {
            switch (b) {
                case 0: {
                    u8 n = *src++;
                    u8 hi = *src++;
                    u8 lo = *src++;

                    len = n + 5;
                    func_80079F70(dst + done, dst + done - ((hi << 8) | lo) - 1, len);
                    done += len;
                    break;
                }
                case 1:
                    len = *src++ + 3;
                    func_8007A070(dst + done, 0xFF, len);
                    done += len;
                    break;
                case 2:
                    len = *src++ + 3;
                    func_8007A070(dst + done, 0, len);
                    done += len;
                    break;
            }
        }
    }
    return size;
}
#else
INCLUDE_ASM("asm/nonmatchings/A370", DecodeLZ);
#endif

u32 ReadU32BE(u8 *p) {
    return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
}

#ifdef NON_MATCHING
/* Same code, different register allocation (src should reuse a2, the idx register). */
/* Decodes block idx of a compressed resource into dst; the header gives the mode (0-4) and
 * the length-field width, and the bytes after it are the preset dictionary. Returns the size. */
s32 func_8007A80C(u8 *dst, ArcCtx *ctx, s32 idx) {
    u8 *dict = ctx->hdr;
    u8 *src = ctx->ptrs[idx];
    u8 *out = dst;
    s32 done = 0;
    u8 mode = dict[0];
    u8 bits = dict[1];
    u16 mask = 0xFFFF;
    s32 size;
    s32 shift;
    s32 len;
    u8 *p;

    if (mode == 0 || mode == 1 || mode == 2) {
        size = (dict[2] << 8) + dict[3];
        dict += 4;
    } else {
        dict += 2;
        size = (src[0] << 8) + src[1];
        src += 2;
    }
    if (mode == 0 || mode == 3) {
        mask = mask >> (bits + 1);
    } else {
        mask = mask >> bits;
    }
    if (mode == 0 || mode == 3) {
        if (done != size) {
            shift = 8 - bits;
            do {
                u8 b = *src;

                if (b & 0x80) {
                    len = (b & 0x7F) + 1;
                    done += len;
                    src++;
                    while (len-- != 0) {
                        *out++ = *src++;
                    }
                } else {
                    len = ((b << 1) >> shift) + 3;
                    done += len;
                    p = dict + (((b << 8) + src[1]) & mask);
                    while (len-- != 0) {
                        *out++ = *p++;
                    }
                    src += 2;
                }
            } while (done != size);
        }
    } else if (mode == 1 || mode == 4) {
        u16 flags = 0;

        if (done != size) {
            shift = 8 - bits;
            do {
                flags <<= 1;
                if ((flags & 0xFE) == 0) {
                    flags = (*src++ << 8) | 0xFF;
                }
                if (flags & 0x8000) {
                    *out++ = *src++;
                    done++;
                } else {
                    len = (src[0] >> shift) + 3;
                    p = dict + (((src[0] << 8) + src[1]) & mask);
                    done += len;
                    while (len-- != 0) {
                        *out++ = *p++;
                    }
                    src += 2;
                }
            } while (done != size);
        }
    } else {
        if (done != size) {
            shift = 8 - bits;
            do {
                u8 b = *src;
                u8 lit, refs;

                if (b == 0) {
                    break;
                }
                refs = b & 7;
                lit = b >> 3;
                src++;
                done += lit;
                while (lit-- != 0) {
                    *out++ = *src++;
                }
                while (refs-- != 0) {
                    len = (src[0] >> shift) + 3;
                    p = dict + (((src[0] << 8) + src[1]) & mask);
                    done += len;
                    while (len-- != 0) {
                        *out++ = *p++;
                    }
                    src += 2;
                }
            } while (done != size);
        }
    }
    return size;
}
#else
INCLUDE_ASM("asm/nonmatchings/A370", func_8007A80C);
#endif

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

/* read_pt_len */
void func_8007C74C(s16 nn, u8 nbit, s16 i_special) {
    s16 i, c, n;

    n = func_8007C25C(nbit);
    if (n == 0) {
        c = func_8007C25C(nbit);
        for (i = 0; i < nn; i++) {
            pt_len[i] = 0;
        }
        for (i = 0; i < 256; i++) {
            pt_table[i] = c;
        }
    } else {
        i = 0;
        while (i < n) {
            c = bitbuf >> (16 - 3);
            if (c == 7) {
                u16 mask = 1 << (16 - 4);

                while (mask & bitbuf) {
                    mask >>= 1;
                    c++;
                }
            }
            fillbuf((c < 7) ? 3 : c - 3);
            pt_len[i++] = c;
            if (i == i_special) {
                c = func_8007C25C(2);
                while (--c >= 0) {
                    pt_len[i++] = 0;
                }
            }
        }
        while (i < nn) {
            pt_len[i++] = 0;
        }
        func_8007BC24(nn, pt_len, 8, pt_table);
    }
}

/* read_c_len */
void func_8007CAB8(void) {
    s16 i, c, n;

    n = func_8007C25C(9);
    if (n == 0) {
        c = func_8007C25C(9);
        for (i = 0; i < 510; i++) {
            c_len[i] = 0;
        }
        for (i = 0; i < 4096; i++) {
            c_table[i] = c;
        }
    } else {
        i = 0;
        while (i < n) {
            c = pt_table[bitbuf >> (16 - 8)];
            if (c >= 19) {
                u16 mask = 1 << (16 - 9);

                do {
                    if (bitbuf & mask) {
                        c = right[c];
                    } else {
                        c = left[c];
                    }
                    mask >>= 1;
                } while (c >= 19);
            }
            fillbuf(pt_len[c]);
            if (c <= 2) {
                if (c == 0) {
                    c = 1;
                } else if (c == 1) {
                    c = func_8007C25C(4) + 3;
                } else {
                    c = func_8007C25C(9) + 20;
                }
                while (--c >= 0) {
                    c_len[i++] = 0;
                }
            } else {
                c_len[i++] = c - 2;
            }
        }
        while (i < 510) {
            c_len[i++] = 0;
        }
        func_8007BC24(510, c_len, 12, c_table);
    }
}

/* decode_c_st1 */
u16 func_8007CE48(void) {
    u16 j, mask;

    if (blocksize == 0) {
        blocksize = func_8007C25C(16);
        func_8007C74C(19, 5, 3);
        func_8007CAB8();
        func_8007C74C(14, 4, -1);
    }
    blocksize--;
    j = c_table[bitbuf >> 4];
    if (j < 510) {
        fillbuf(c_len[j]);
    } else {
        fillbuf(12);
        mask = 1 << (16 - 1);
        do {
            if (bitbuf & mask) {
                j = right[j];
            } else {
                j = left[j];
            }
            mask >>= 1;
        } while (j >= 510);
        fillbuf(c_len[j] - 12);
    }
    return j;
}

/* decode_p_st1 */
u16 func_8007D200(void) {
    u16 j, mask;

    j = pt_table[bitbuf >> (16 - 8)];
    if (j < 14) {
        fillbuf(pt_len[j]);
    } else {
        fillbuf(8);
        mask = 1 << (16 - 1);
        do {
            if (bitbuf & mask) {
                j = right[j];
            } else {
                j = left[j];
            }
            mask >>= 1;
        } while (j >= 14);
        fillbuf(pt_len[j] - 8);
    }
    if (j != 0) {
        j = (1 << (j - 1)) + func_8007C25C(j - 1);
    }
    return j;
}

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

/* reconst: rebuilds the dynamic Huffman tree between start and end after halving the frequencies. */
void func_8007D8A8(s32 start, s32 end) {
    s32 i, j, k, l, b;
    u32 f, g;

    b = block[start];
    for (i = j = start; i < end; i++) {
        if ((k = child[i]) < 0) {
            freq[j] = (freq[i] + 1) / 2;
            child[j] = k;
            j++;
        }
        if (edge[b = block[i]] == i) {
            stock[--avail] = b;
        }
    }
    j--;
    i = end - 1;
    l = end - 2;
    while (i >= start) {
        while (i >= l) {
            freq[i] = freq[j];
            child[i] = child[j];
            i--, j--;
        }
        f = freq[l] + freq[l + 1];
        for (k = start; f < freq[k]; k++) {
        }
        while (j >= k) {
            freq[i] = freq[j];
            child[i] = child[j];
            i--, j--;
        }
        freq[i] = f;
        child[i] = l + 1;
        i--;
        l -= 2;
    }
    f = 0;
    for (i = start; i < end; i++) {
        if ((j = child[i]) < 0) {
            s_node[~j] = i;
        } else {
            parent[j] = parent[j - 1] = i;
        }
        if ((g = freq[i]) == f) {
            block[i] = b;
        } else {
            edge[b = block[i] = stock[avail++]] = i;
            f = g;
        }
    }
}

/* swap_inc */
s32 func_8007DBF4(s32 p) {
    s32 b, q, r, s;

    b = block[p];
    if ((q = edge[b]) != p) {
        r = child[p];
        s = child[q];
        child[p] = s;
        child[q] = r;
        if (r >= 0) {
            parent[r] = parent[r - 1] = q;
        } else {
            s_node[~r] = q;
        }
        if (s >= 0) {
            parent[s] = parent[s - 1] = p;
        } else {
            s_node[~s] = p;
        }
        p = q;
        goto Adjust;
    } else if (b == block[p + 1]) {
    Adjust:
        edge[b]++;
        if (++freq[p] == freq[p - 1]) {
            block[p] = block[p - 1];
        } else {
            edge[block[p] = stock[avail++]] = p;
        }
    } else if (++freq[p] == freq[p - 1]) {
        stock[--avail] = b;
        block[p] = block[p - 1];
    }
    return parent[p];
}

/* update_p */
static inline void update_p_inline(s32 p) {
    s32 q;

    if (total_p == 0x8000) {
        func_8007D8A8(628, most_p + 1);
        total_p = freq[628];
        freq[628] = 0xFFFF;
    }
    q = s_node[p + 314];
    while (q != 628) {
        q = func_8007DBF4(q);
    }
    total_p++;
}

/* make_new_node */
void func_8007DDF0(s32 p) {
    s32 q, r;

    r = most_p + 1;
    q = r + 1;
    s_node[~(child[r] = child[most_p])] = r;
    child[q] = ~(p + 314);
    child[most_p] = q;
    freq[r] = freq[most_p];
    freq[q] = 0;
    block[r] = block[most_p];
    if (most_p == 628) {
        freq[628] = 0xFFFF;
        edge[block[628]]++;
    }
    parent[r] = parent[q] = most_p;
    edge[block[q] = stock[avail++]] = s_node[p + 314] = most_p = q;
    update_p_inline(p);
}

/* update_c */
static inline void update_c_inline(s32 p) {
    s32 q;

    if (freq[0] == 0x8000) {
        func_8007D8A8(0, n_max * 2 - 1);
    }
    freq[0]++;
    q = s_node[p];
    do {
        q = func_8007DBF4(q);
    } while (q != 0);
}

/* decode_c_dyn */
u16 func_8007DFF0(void) {
    s32 c;
    s16 buf, cnt;

    c = child[0];
    buf = bitbuf;
    cnt = 0;
    do {
        c = child[c - (buf < 0)];
        buf <<= 1;
        if (++cnt == 16) {
            fillbuf(16);
            buf = bitbuf;
            cnt = 0;
        }
    } while (c > 0);
    fillbuf(cnt);
    c = ~c;
    update_c_inline(c);
    if (c == n1) {
        c += func_8007C25C(8);
    }
    return c;
}

/* decode_p_dyn */
u16 func_8007E2F8(void) {
    s32 c;
    s16 buf, cnt;

    while (count > nextcount) {
        func_8007DDF0(nextcount / 64);
        if ((nextcount += 64) >= nn) {
            nextcount = 0xFFFFFFFF;
        }
    }
    c = child[628];
    buf = bitbuf;
    cnt = 0;
    while (c > 0) {
        c = child[c - (buf < 0)];
        buf <<= 1;
        if (++cnt == 16) {
            fillbuf(16);
            buf = bitbuf;
            cnt = 0;
        }
    }
    fillbuf(cnt);
    c = (~c) - 314;
    update_p_inline(c);
    return (c << 6) + func_8007C25C(6);
}

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

/* decode_c_st0, with read_tree_p and ready_made(1) inlined.
 * Tests D_800AF3C6 but counts down D_800AF3C8, and read_tree_p's escape clears c_len/c_table: kept as in the original. */
u16 func_8007E8F0(void) {
    s32 i, j;

    if (D_800AF3C6 == 0) {
        D_800AF3C8 = func_8007C25C(16);
        func_8007E6DC();
        if (func_8007C25C(1)) {
            s32 i2, c;

            i2 = 0;
            while (i2 < 14) {
                pt_len[i2] = func_8007C25C(4);
                if (++i2 == 3 && pt_len[0] == 1 && pt_len[1] == 1 && pt_len[2] == 1) {
                    c = func_8007C25C(7);
                    for (i2 = 0; i2 < 14; i2++) {
                        c_len[i2] = 0;
                    }
                    for (i2 = 0; i2 < 256; i2++) {
                        c_table[i2] = c;
                    }
                    break;
                }
            }
        } else {
            s32 *tbl;
            s32 k, j2;
            u32 code, weight;

            j2 = D_800A880C;
            tbl = D_800A8810;
            weight = 1 << (16 - j2);
            code = 0;
            for (k = 0; k < np; k++) {
                while (*tbl == k) {
                    j2++;
                    tbl++;
                    weight >>= 1;
                }
                pt_len[k] = j2;
                pt_code[k] = code;
                code += weight;
            }
        }
        func_8007BC24(14, pt_len, 8, pt_table);
    }
    D_800AF3C8--;
    j = c_table[bitbuf >> 4];
    if (j < 286) {
        fillbuf(c_len[j]);
    } else {
        fillbuf(12);
        i = bitbuf;
        do {
            if ((s16)i < 0) {
                j = right[j];
            } else {
                j = left[j];
            }
            i <<= 1;
        } while (j >= 286);
        fillbuf(c_len[j] - 12);
    }
    if (j == 286 - 1) {
        j += func_8007C25C(8);
    }
    return j;
}

/* decode_p_st0 */
u16 func_8007EE2C(void) {
    s32 i, j;

    j = pt_table[bitbuf >> 8];
    if (j < np) {
        fillbuf(pt_len[j]);
    } else {
        fillbuf(8);
        i = bitbuf;
        do {
            if ((s16)i < 0) {
                j = right[j];
            } else {
                j = left[j];
            }
            i <<= 1;
        } while (j >= np);
        fillbuf(pt_len[j] - 8);
    }
    return (j << 6) + func_8007C25C(6);
}

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
