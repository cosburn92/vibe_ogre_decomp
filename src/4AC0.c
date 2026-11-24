#include "common.h"
#include "heap.h"

/* SRAM save system: a RAM copy of the whole 32KB SRAM, two save slots, a suspend save and a
 * common block, each with a "QuestOG3" signature and two checksums. */

#define SRAM_SIZE 0x8000
#define SAVE_SLOTS 2
#define SAVE_COMMON 14
#define SAVE_SUSPEND 15
#define SAVE_FLUSH_KEY 0x37081383

#define COMMON_SIZE 0x10
#define SLOT_SIZE 0x1850
#define SUSPEND_SIZE 0x4AE8
#define SLOT_OFFSET(n) ((n) * SLOT_SIZE + 0x10)
#define SUSPEND_OFFSET 0x30B0
#define SAVE_HEADER 0xC

typedef struct {
    /* 0x00 */ u16 sum;
    /* 0x02 */ u16 bitSum;
    /* 0x04 */ u8 magic[8];
    /* 0x0C */ s32 count; /* first word of the data */
} SaveHeader;

typedef struct {
    /* 0x00 */ void (*clear)(void *data);
    /* 0x04 */ void (*load)(void *data);
    /* 0x08 */ void (*save)(void *data);
    /* 0x0C */ s32 offset;
    /* 0x10 */ void (*suspendLoad)(void *data);
    /* 0x14 */ void (*suspendSave)(void *data);
    /* 0x18 */ s32 suspendOffset;
} SaveHandler; /* size 0x1C */

extern u8 D_800A8240[]; /* "QuestOG3" */
extern SaveHandler D_800A824C[13];
extern u8 *D_800A83B8; /* SRAM cache */
extern u8 D_800A83BC;  /* cache dirty */
extern u8 D_800AEFD0[3];
extern u8 nuScPreNMIFlag;

void bzero(void *p, s32 n);
void _bcopy(void *src, void *dst, s32 n);
s32 _bcmp(void *a, void *b, s32 n);
void osSyncPrintf(const char *fmt, ...);
s32 func_8008A0F0(u32 addr, void *buf, u32 size, s32 write); /* nuPiReadWriteSram */
void func_8016CD90(void *data);
void func_8016CDCC(void *data);
void func_8016CDF4(void *data);

s32 func_80074DA0(void);
void func_80074F9C(s32 n);
void func_80074BF0(u32 key);
void func_80074C58(u8 *cache);
void func_80074CF0(void *dst, s32 offset, s32 size);
void func_8007513C(void);
void func_80075224(void);
s32 func_80075360(s32 n);
s32 func_8007541C(s32 n, SaveHeader *hdr);
s32 func_80075578(SaveHeader *hdr);
s32 func_80075688(SaveHeader *hdr);
void func_8007578C(s32 n, void *buf);
void func_80075858(void *buf);
void func_800758FC(void *buf);
void func_8007599C(s32 n, SaveHeader *hdr);
u16 func_80075A84(u8 *p, u16 len, s32 seed);
u16 func_80075B00(u8 *p, u16 len, s32 seed);

static inline void SramCacheLoad(void) {
    s32 i;

    if (D_800A83B8 == NULL) {
        D_800A83B8 = HMalloc(SRAM_SIZE);
        for (i = 0; i < SRAM_SIZE; i += 0x100) {
            func_8008A0F0(i, D_800A83B8 + i, 0x100, 0);
        }
    }
}

static inline void SramRead(void *dst, s32 offset, s32 size) {
    SramCacheLoad();
    _bcopy(D_800A83B8 + offset, dst, size);
}

static inline void SramWrite(void *src, s32 offset, s32 size) {
    SramCacheLoad();
    _bcopy(src, D_800A83B8 + offset, size);
    D_800A83BC = 1;
}

static inline s32 SaveChecksumOk(SaveHeader *hdr, u8 *data, u16 len, s32 seed) {
    if (hdr->sum != func_80075A84(data, len, seed)) {
        return 0;
    }
    if (hdr->bitSum != func_80075B00(data, len, seed)) {
        return 0;
    }
    return 1;
}

void func_800746C0(void) {
}

/* Checks every save; returns the list of broken ones (or NULL) */
u8 *func_800746C8(void) {
    s32 i;
    s32 n = 0;
    u8 *p;
    u8 c = 0xFF;

    D_800A83B8 = NULL;
    D_800A83BC = 0;
    for (i = 2, p = &D_800AEFD0[2]; i >= 0; i--) {
        *p-- = c;
    }
    if (func_80074DA0()) {
        osSyncPrintf("\x82\x72\x82\x71\x82\x60\x82\x6C\x82\xF0\x91\x53\x95\x94\x8F\x89\x8A\xFA\x89\xBB\x82\xB5"
                     "\x82\xDC\x82\xB5\x82\xBD\x81\x69\x8D\x48\x8F\xEA\x8F\x6F\x89\xD7\x8E\x9E\x81\x6A\n");
        for (i = 0; i < SAVE_SLOTS; i++) {
            func_80074F9C(i);
        }
        func_80074F9C(SAVE_SUSPEND);
        func_80074F9C(SAVE_COMMON);
    } else {
        for (i = 0; i < SAVE_SLOTS; i++) {
            if (!func_80075360(i)) {
                D_800AEFD0[n++] = i;
                osSyncPrintf("\x83\x5A\x81\x5B\x83\x75\x94\xD4\x8D\x86 %d \x82\xCD\x94\x6A\x89\xF3\x82\xB3\x82\xEA"
                             "\x82\xDC\x82\xB5\x82\xBD\x81\x42\n",
                             i);
            }
        }
        if (!func_80075360(SAVE_SUSPEND)) {
            D_800AEFD0[n++] = SAVE_SUSPEND;
            osSyncPrintf("\x92\x86\x92\x66\x83\x5A\x81\x5B\x83\x75\x82\xCD\x94\x6A\x89\xF3\x82\xB3\x82\xEA\x82\xDC"
                         "\x82\xB5\x82\xBD\x81\x42\n");
        }
        if (!func_80075360(SAVE_COMMON)) {
            D_800AEFD0[n++] = SAVE_COMMON;
            osSyncPrintf("\x8B\xA4\x92\xCA\x83\x5A\x81\x5B\x83\x75\x82\xCD\x94\x6A\x89\xF3\x82\xB3\x82\xEA\x82\xDC"
                         "\x82\xB5\x82\xBD\x81\x42\n");
        }
    }
    func_80074BF0(SAVE_FLUSH_KEY);
    if (n == 0) {
        return NULL;
    }
    return D_800AEFD0;
}

void func_80074834(s32 n) {
    func_80074F9C(n);
    func_80074BF0(SAVE_FLUSH_KEY);
}

/* Saves the game state into save n */
void func_8007485C(s32 n) {
    SaveHeader *common;
    SaveHeader *buf;
    s32 i;
    s32 count;

    if (n == SAVE_SUSPEND) {
        func_8007513C();
    } else if (n == SAVE_COMMON) {
        common = HMalloc(COMMON_SIZE);
        bzero(common, COMMON_SIZE);
        func_8016CDF4((u8 *)common + SAVE_HEADER);
        func_8007599C(SAVE_COMMON, common);
        func_800758FC(common);
        HFree(common);
    } else if (n < SAVE_SLOTS) {
        buf = HMalloc(SLOT_SIZE);
        count = buf->count + 1;
        bzero(buf, SLOT_SIZE);
        buf->count = count;
        if (count == 0) {
            buf->count = -1;
        }
        for (i = 0; i < 13; i++) {
            if (D_800A824C[i].save != NULL) {
                D_800A824C[i].save((u8 *)buf + (D_800A824C[i].offset + SAVE_HEADER));
            }
        }
        func_8007599C(n, buf);
        func_8007578C(n, buf);
        HFree(buf);
    } else {
        osSyncPrintf("buSave : \x83\x5A\x81\x5B\x83\x75\x94\xD4\x8D\x86\x82\xAA\x88\xD9\x8F\xED (SaveNo=%d)\n", n);
        while (1) {}
    }
    func_80074BF0(SAVE_FLUSH_KEY);
}

/* Loads save n into the game state */
void func_800749C0(s32 n) {
    u8 *common;
    u8 *buf;
    s32 i;

    if (n == SAVE_SUSPEND) {
        func_80075224();
    } else if (n == SAVE_COMMON) {
        common = HMalloc(COMMON_SIZE);
        func_80074CF0(common, 0, COMMON_SIZE);
        func_8016CDCC(common + SAVE_HEADER);
        HFree(common);
    } else {
        buf = HMalloc(SLOT_SIZE);
        func_80074CF0(buf, SLOT_OFFSET(n), SLOT_SIZE);
        for (i = 0; i < 13; i++) {
            if (D_800A824C[i].load != NULL) {
                D_800A824C[i].load(buf + (D_800A824C[i].offset + SAVE_HEADER));
            }
        }
        HFree(buf);
    }
    func_80074BF0(SAVE_FLUSH_KEY);
}

/* Returns a copy of the first 0x1A bytes of save n's data (the file-select summary) */
u8 *func_80074AD4(s32 n) {
    SaveHeader *buf;
    u8 *copy = NULL;
    u8 *src = NULL;
    s32 used;

    if (n == SAVE_SUSPEND) {
        buf = HMalloc(SUSPEND_SIZE);
        if (!func_80075578(buf)) {
            goto end;
        }
        func_80074CF0(buf, SUSPEND_OFFSET, SUSPEND_SIZE);
        used = *(s32 *)buf;
    } else {
        buf = HMalloc(SLOT_SIZE);
        if (!func_8007541C(n, buf)) {
            goto end;
        }
        func_80074CF0(buf, SLOT_OFFSET(n), SLOT_SIZE);
        used = buf->count;
    }
    if (used != 0) {
        src = (u8 *)buf + (D_800A824C[0].offset + SAVE_HEADER);
    }
end:
    func_80074BF0(SAVE_FLUSH_KEY);
    if (src != NULL) {
        copy = HMalloc(0x1A);
        _bcopy(src, copy, 0x1A);
    }
    HFree(buf);
    return copy;
}

/* Writes the cache back to SRAM if key is right, then drops it */
void func_80074BF0(u32 key) {
    if (D_800A83BC == 1) {
        if (key == SAVE_FLUSH_KEY) {
            func_80074C58(D_800A83B8);
        }
        D_800A83BC = 0;
    }
    if (D_800A83B8 != NULL) {
        HFree(D_800A83B8);
        D_800A83B8 = NULL;
    }
}

void func_80074C58(u8 *cache) {
    s32 (**rw)(u32 addr, void *buf, u32 size, s32 write) = HMalloc(0x10);
    s32 i;

    *rw = func_8008A0F0;
    if (!nuScPreNMIFlag) {
        for (i = 0; i < SRAM_SIZE; i += 0x100) {
            (*rw)(i, cache + i, 0x100, 1);
        }
    }
    HFree(rw);
}

void func_80074CF0(void *dst, s32 offset, s32 size) {
    SramRead(dst, offset, size);
}

/* Returns 1 when no save has a valid signature (fresh SRAM) */
s32 func_80074DA0(void) {
    u8 magic[8];
    s32 i;
    s32 slots = SAVE_SLOTS;

    for (i = 0; i < slots; i++) {
        SramRead(magic, SLOT_OFFSET(i) + 4, 8);
        if (_bcmp(D_800A8240, magic, 8) == 0) {
            return 0;
        }
    }
    SramRead(magic, SUSPEND_OFFSET + 4, 8);
    if (_bcmp(D_800A8240, magic, 8) == 0) {
        return 0;
    }
    SramRead(magic, 4, 8);
    return _bcmp(D_800A8240, magic, 8) != 0;
}

/* Formats save n */
void func_80074F9C(s32 n) {
    SaveHeader *common;
    SaveHeader *buf;
    u8 header[SAVE_HEADER];
    s32 i;

    if (n == SAVE_COMMON) {
        common = HMalloc(COMMON_SIZE);
        bzero(common, COMMON_SIZE);
        func_8016CD90((u8 *)common + SAVE_HEADER);
        func_8007599C(SAVE_COMMON, common);
        func_800758FC(common);
        HFree(common);
    } else if (n == SAVE_SUSPEND) {
        bzero(header, SAVE_HEADER);
        _bcopy(D_800A8240, header + 4, 8);
        SramWrite(header, SUSPEND_OFFSET, SAVE_HEADER);
    } else {
        buf = HMalloc(SLOT_SIZE);
        bzero(buf, SLOT_SIZE);
        for (i = 0; i < 13; i++) {
            if (D_800A824C[i].clear != NULL) {
                D_800A824C[i].clear((u8 *)buf + (D_800A824C[i].offset + SAVE_HEADER));
            }
        }
        func_8007599C(n, buf);
        func_8007578C(n, buf);
        HFree(buf);
    }
}

/* Writes a suspend save */
void func_8007513C(void) {
    u8 *buf = HMalloc(SUSPEND_SIZE);
    s32 i;

    bzero(buf, SUSPEND_SIZE);
    for (i = 0; i < 13; i++) {
        if (D_800A824C[i].save != NULL) {
            D_800A824C[i].save(buf + (D_800A824C[i].offset + SAVE_HEADER));
        }
    }
    for (i = 0; i < 13; i++) {
        if (D_800A824C[i].suspendSave != NULL) {
            D_800A824C[i].suspendSave(buf + (D_800A824C[i].suspendOffset + SLOT_SIZE));
        }
    }
    func_8007599C(SAVE_SUSPEND, buf);
    func_80075858(buf);
    HFree(buf);
}

/* Loads the suspend save */
void func_80075224(void) {
    u8 *buf = HMalloc(SUSPEND_SIZE);
    s32 i;

    SramRead(buf, SUSPEND_OFFSET, SUSPEND_SIZE);
    if (*(s32 *)buf != 0) {
        for (i = 0; i < 13; i++) {
            if (D_800A824C[i].load != NULL) {
                D_800A824C[i].load(buf + (D_800A824C[i].offset + SAVE_HEADER));
            }
        }
        for (i = 0; i < 13; i++) {
            if (D_800A824C[i].suspendLoad != NULL) {
                D_800A824C[i].suspendLoad(buf + (D_800A824C[i].suspendOffset + SLOT_SIZE));
            }
        }
    }
    HFree(buf);
}

/* Verifies save n, reformatting it when broken; returns whether it was valid */
#ifdef NON_MATCHING
/* Only differs in the order of two moves after HMalloc in the slot branch. */
s32 func_80075360(s32 n) {
    void *buf;
    s32 ok = 0;

    if (n == SAVE_COMMON) {
        buf = HMalloc(COMMON_SIZE);
        if (func_80075688(buf)) {
            ok = 1;
        }
    } else if (n == SAVE_SUSPEND) {
        buf = HMalloc(SUSPEND_SIZE);
        if (func_80075578(buf)) {
            ok = 1;
        }
    } else {
        buf = HMalloc(SLOT_SIZE);
        if (func_8007541C(n, buf)) {
            ok = 1;
        }
    }
    HFree(buf);
    if (!ok) {
        func_80074F9C(n);
    }
    return ok;
}
#else
INCLUDE_ASM("asm/nonmatchings/4AC0", func_80075360);
#endif

#ifdef NON_MATCHING
/* The original keeps the checksum length (0x1844) in a saved register and branches to
 * "return 1" instead of folding the last compare into a set-on-equal. */
s32 func_8007541C(s32 n, SaveHeader *hdr) {
    u8 *data = (u8 *)hdr + SAVE_HEADER;
    s32 offset = SLOT_OFFSET(n);

    SramRead(hdr, offset, SLOT_SIZE);
    if (_bcmp(D_800A8240, hdr->magic, 8) != 0) {
        return 0;
    }
    return SaveChecksumOk(hdr, data, SLOT_SIZE - SAVE_HEADER, SLOT_OFFSET(n));
}
#else
INCLUDE_ASM("asm/nonmatchings/4AC0", func_8007541C);
#endif

#ifdef NON_MATCHING
/* Same length-register / final-compare difference as func_8007541C. */
s32 func_80075578(SaveHeader *hdr) {
    u8 *data = (u8 *)hdr + SAVE_HEADER;

    SramRead(hdr, SUSPEND_OFFSET, SUSPEND_SIZE);
    if (_bcmp(D_800A8240, hdr->magic, 8) != 0) {
        return 0;
    }
    if (*(s32 *)hdr == 0) {
        return 1;
    }
    return SaveChecksumOk(hdr, data, SUSPEND_SIZE - SAVE_HEADER, SUSPEND_OFFSET);
}
#else
INCLUDE_ASM("asm/nonmatchings/4AC0", func_80075578);
#endif

#ifdef NON_MATCHING
/* Same length-register / final-compare difference as func_8007541C. */
s32 func_80075688(SaveHeader *hdr) {
    u8 *data = (u8 *)hdr + SAVE_HEADER;

    SramCacheLoad();
    _bcopy(D_800A83B8, hdr, COMMON_SIZE);
    if (_bcmp(D_800A8240, hdr->magic, 8) != 0) {
        return 0;
    }
    return SaveChecksumOk(hdr, data, COMMON_SIZE - SAVE_HEADER, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/4AC0", func_80075688);
#endif

void func_8007578C(s32 n, void *buf) {
    SramWrite(buf, SLOT_OFFSET(n), SLOT_SIZE);
}

void func_80075858(void *buf) {
    SramWrite(buf, SUSPEND_OFFSET, SUSPEND_SIZE);
}

void func_800758FC(void *buf) {
    SramWrite(buf, 0, COMMON_SIZE);
}

/* Fills in the signature and checksums of save n */
void func_8007599C(s32 n, SaveHeader *hdr) {
    u8 *data;

    if (n == SAVE_COMMON) {
        data = (u8 *)hdr + SAVE_HEADER;
        hdr->sum = func_80075A84(data, COMMON_SIZE - SAVE_HEADER, 0);
        hdr->bitSum = func_80075B00(data, COMMON_SIZE - SAVE_HEADER, 0);
        _bcopy(D_800A8240, hdr->magic, 8);
    } else if (n == SAVE_SUSPEND) {
        data = (u8 *)hdr + SAVE_HEADER;
        hdr->sum = func_80075A84(data, SUSPEND_SIZE - SAVE_HEADER, SUSPEND_OFFSET);
        hdr->bitSum = func_80075B00(data, SUSPEND_SIZE - SAVE_HEADER, SUSPEND_OFFSET);
        _bcopy(D_800A8240, hdr->magic, 8);
    } else {
        data = (u8 *)hdr + SAVE_HEADER;
        hdr->sum = func_80075A84(data, SLOT_SIZE - SAVE_HEADER, SLOT_OFFSET(n));
        hdr->bitSum = func_80075B00(data, SLOT_SIZE - SAVE_HEADER, SLOT_OFFSET(n));
        _bcopy(D_800A8240, hdr->magic, 8);
    }
}

/* Byte sum plus seed */
u16 func_80075A84(u8 *p, u16 len, s32 seed) {
    u16 i;
    u16 sum = 0;

    for (i = 0; i < len; i++) {
        sum += p[i];
    }
    return sum + seed;
}

u16 func_80075AC4(u8 *p, u16 len) {
    u16 i;
    u16 sum = 0;

    for (i = 0; i < len; i++) {
        sum += p[i];
    }
    return sum;
}

/* Count of set bits plus seed */
u16 func_80075B00(u8 *p, u16 len, s32 seed) {
    u16 i;
    u16 j;
    u16 count = 0;
    u8 b;

    for (i = 0; i < len; i++) {
        b = p[i];
        for (j = 0; j < 8; j++) {
            if (b & 1) {
                count++;
            }
            b >>= 1;
        }
    }
    return count + seed;
}

u16 func_80075B60(u8 *p, u16 len) {
    u16 i;
    u16 j;
    u16 count = 0;
    u8 b;

    for (i = 0; i < len; i++) {
        b = p[i];
        for (j = 0; j < 8; j++) {
            if (b & 1) {
                count++;
            }
            b >>= 1;
        }
    }
    return count;
}
