#include "common.h"

/* libultra libc xlitob.c */

#define BUFF_LEN 0x18
#define FLAGS_MINUS 0x4
#define FLAGS_ZERO 0x10

typedef struct {
    /* 0x00 */ union {
        s64 ll;
        f64 ld;
    } v;
    /* 0x08 */ char *s;
    /* 0x0C */ s32 n0;
    /* 0x10 */ s32 nz0;
    /* 0x14 */ s32 n1;
    /* 0x18 */ s32 nz1;
    /* 0x1C */ s32 n2;
    /* 0x20 */ s32 nz2;
    /* 0x24 */ s32 prec;
    /* 0x28 */ s32 width;
    /* 0x2C */ u32 nchar;
    /* 0x30 */ u32 flags;
    /* 0x34 */ char qual;
} _Pft;

typedef struct {
    s64 quot;
    s64 rem;
} lldiv_t;

extern char D_800ABC30[]; /* ldigs "0123456789abcdef" */
extern char D_800ABC44[]; /* udigs "0123456789ABCDEF" */

lldiv_t lldiv(s64 num, s64 denom);
void *memcpy(void *s1, const void *s2, u32 n);

void _Litob(_Pft *args, char type) {
    char buff[BUFF_LEN];
    const char *digs;
    s32 base;
    s32 i;
    u64 ullval;

    digs = (type == 'X') ? D_800ABC44 : D_800ABC30;
    base = (type == 'o') ? 8 : ((type != 'x' && type != 'X') ? 10 : 16);
    i = BUFF_LEN;
    ullval = args->v.ll;

    if ((type == 'd' || type == 'i') && args->v.ll < 0) {
        ullval = -ullval;
    }

    if (ullval != 0 || args->prec != 0) {
        buff[--i] = digs[ullval % base];
    }

    args->v.ll = ullval / base;

    while (args->v.ll > 0 && i > 0) {
        lldiv_t qr = lldiv(args->v.ll, base);

        args->v.ll = qr.quot;
        buff[--i] = digs[qr.rem];
    }

    args->n1 = BUFF_LEN - i;
    memcpy(args->s, buff + i, args->n1);

    if (args->n1 < args->prec) {
        args->nz0 = args->prec - args->n1;
    }

    if (args->prec < 0 && (args->flags & (FLAGS_ZERO | FLAGS_MINUS)) == FLAGS_ZERO) {
        if ((i = args->width - args->n0 - args->nz0 - args->n1) > 0) {
            args->nz0 += i;
        }
    }
}
