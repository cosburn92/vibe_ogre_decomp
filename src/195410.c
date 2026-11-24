#include "common.h"
#include "tables.h"
#include "heap.h"

/* ovl_195410: builds characters and squads from stage templates */

typedef struct {
    /* 0x00 */ u8 cls;
    /* 0x01 */ u8 level;
    /* 0x02 */ u8 items[4]; /* two big-endian item ids */
    /* 0x06 */ u8 unk06;
} CharTemplateEntry;

typedef struct {
    /* 0x00 */ CharTemplateEntry a;
    /* 0x07 */ CharTemplateEntry b;
    /* 0x0E */ u8 unk0E[2];
    /* 0x10 */ CharTemplateEntry c;
} CharTemplate;

extern Character D_80193BC0[]; /* player characters, 0x38 bytes each */
extern Character D_80195560[]; /* enemy characters, 0x34 bytes each */
extern u8 D_801F1035;          /* level bonus */
extern char D_802172B0_ovl_195410[];

void bzero(void *p, s32 n);
void func_8009C550(char *dst, char *src);
void func_8016BD20(s32 enemy, u8 index);
void func_8016F11C(Character *c, u8 level);
u8 func_8016F5C8(u16 item);
s32 func_801DC054(void);
u16 func_801FE190(u8 slot);       /* squad member count (ovl_14EBE0) */
void func_801DC720(u16 item, u8 flag); /* InventoryAdd at this overlay's address */
extern u8 D_801971FD[][25];       /* gSquads[].items */

/* Unreferenced first word of this file's rodata: it puts the strings at
 * +4 and SquadSetupItems' 8-aligned jump table at +0x50. */
const s32 D_802172E0_ovl_195410 = 0;

/* Puts item in the equipment slot whose class default item is of the same kind */
void CharacterEquipItem(u16 item, Character *c) {
    u8 kind = func_8016F5C8(item);
    ClassData *cls;

    if (gClassTable[c->cls].baseClass != 0) {
        cls = &gClassTable[c->baseCls];
    } else {
        cls = &gClassTable[c->cls];
    }
    if (cls->defaultItems[0] != 0 && func_8016F5C8(cls->defaultItems[0]) == kind) {
        c->items[0] = item;
    } else if (cls->defaultItems[1] != 0 && func_8016F5C8(cls->defaultItems[1]) == kind) {
        c->items[1] = item;
    } else if (cls->defaultItems[2] != 0 && func_8016F5C8(cls->defaultItems[2]) == kind) {
        c->items[2] = item;
    } else if (cls->defaultItems[3] != 0 && func_8016F5C8(cls->defaultItems[3]) == kind) {
        c->items[3] = item;
    }
}

#ifdef NON_MATCHING
/* Prologue order and the masking of the second item id differ. */
void CharacterCreateFromTemplate(s32 index, u8 *tp, s32 variant, u8 enemy, u8 slot) {
    CharTemplate *t = (CharTemplate *)tp;
    Character *c;
    u8 cls;
    u8 base;

    if (enemy != 0 || slot >= 30) {
        c = (Character *)((u8 *)D_80195560 + index * 0x34);
    } else {
        c = (Character *)((u8 *)D_80193BC0 + index * 0x38);
    }
    if (variant == 0) {
        cls = t->a.cls;
    } else if (variant == 1) {
        cls = t->b.cls;
    } else {
        cls = t->c.cls;
    }
    c->cls = cls;
    base = gClassTable[cls].baseClass;
    if (base == 0) {
        base = cls;
    }
    c->baseCls = base;
    if (variant == 0) {
        func_8016F11C(c, D_801F1035 + t->a.level);
    } else if (variant == 1) {
        func_8016F11C(c, D_801F1035 + t->b.level);
    } else {
        func_8016F11C(c, D_801F1035 + t->c.level);
    }
    c->items[0] = 0;
    c->items[1] = 0;
    c->items[2] = 0;
    c->items[3] = 0;
    if (variant == 0) {
        CharacterEquipItem(t->a.items[1] | (t->a.items[0] << 8), c);
        CharacterEquipItem((u16)(t->a.items[3] | (t->a.items[2] << 8)), c);
    } else if (variant == 1) {
        CharacterEquipItem(t->b.items[1] | (t->b.items[0] << 8), c);
        CharacterEquipItem((u16)(t->b.items[3] | (t->b.items[2] << 8)), c);
    } else {
        CharacterEquipItem(t->c.items[1] | (t->c.items[0] << 8), c);
        CharacterEquipItem((u16)(t->c.items[3] | (t->c.items[2] << 8)), c);
    }
    c->fatigue = 0;
    if (variant == 0) {
        c->status = 0x82;
    } else {
        c->status = 0x80;
    }
    func_8016BD20(enemy != 0 || slot >= 30, index);
    if (func_801DC054() && slot == 30 && variant == 0) {
        bzero(c, 0x11);
        func_8009C550((char *)c, D_802172B0_ovl_195410);
    }
    if (enemy == 0 && slot < 30) {
        ((u8 *)c)[0x34] = index;
        ((u8 *)c)[0x35] = 0;
        ((u8 *)c)[0x36] = 0;
        ((u8 *)c)[0x37] = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/195410", CharacterCreateFromTemplate);
#endif

INCLUDE_ASM("asm/nonmatchings/195410", SquadCreateFromTemplate);

/* Fills the squad's consumable slots: builds a list of item ids (heals 1-3,
 * fruit 4-5, revives 6) for the squad's size, then copies them into the squad
 * record sorted by id, adding each to the inventory for player squads. */
void SquadSetupItems(u8 slot, u8 heals, u8 fruit, u8 revives) {
    u8 *buf;
    s32 n;
    s32 i;
    s32 k;
    s32 j; /* the fill phase (0 heals, 1 fruit, 2 revives), then the scan index */
    u8 *dst;

    buf = HMalloc(0x14);
    bzero(buf, 0x14);
    n = func_801FE190(slot);
    if (heals != 0 || fruit != 0 || revives != 0) {
        j = 0;
        i = 0;
        while (i < n) {
            switch (j) {
                case 0:
                    switch (heals) {
                        case 1:
                            buf[i++] = 1;
                            i += 4;
                            break;
                        case 2:
                            buf[i++] = 1;
                            buf[i++] = 1;
                            i += 2;
                            break;
                        case 3:
                            buf[i++] = 1;
                            buf[i++] = 1;
                            buf[i++] = 2;
                            i += 3;
                            break;
                        case 4:
                            buf[i++] = 2;
                            buf[i++] = 2;
                            i += 2;
                            break;
                        case 5:
                            buf[i++] = 2;
                            buf[i++] = 2;
                            buf[i++] = 3;
                            i += 3;
                            break;
                        case 6:
                            buf[i++] = 3;
                            buf[i++] = 3;
                            i += 2;
                            break;
                    }
                    j = 1;
                    break;
                case 1:
                    switch (fruit) {
                        case 1:
                            buf[i++] = 4;
                            buf[i++] = 4;
                            break;
                        case 2:
                            buf[i++] = 4;
                            buf[i++] = 5;
                            break;
                        case 3:
                            buf[i++] = 5;
                            buf[i++] = 5;
                            break;
                    }
                    j = 2;
                    break;
                case 2:
                    switch (revives) {
                        case 1:
                            buf[i++] = 6;
                            break;
                        case 2:
                            buf[i++] = 6;
                            buf[i++] = 6;
                            break;
                    }
                    j = 0;
                    break;
            }
        }
    }
    dst = D_801971FD[slot];
    bzero(dst, 10);
    if (heals != 0 || fruit != 0 || revives != 0) {
        for (k = 1, j = 0, i = 0; i < n && k < 7; j++) {
            if (j >= n) {
                k++;
                j = 0;
            }
            if (buf[j] == k) {
                dst[i++] = k;
                if (slot < 30) {
                    func_801DC720(k, 1);
                }
            }
        }
    }
    HFree(buf);
}

/* The jump table above is the file's last rodata; the original pads it to 16 bytes. */
__asm__(".section .rodata\n.word 0, 0\n.section .text\n");

INCLUDE_ASM("asm/nonmatchings/195410", StageSetupUnits);
