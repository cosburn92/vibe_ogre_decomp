#ifndef TABLES_H
#define TABLES_H

#include "common.h"

/* gClassTable (ovl_040E80 data at 0x80187C14): 165 records */
typedef struct {
    /* 0x00 */ char *name;
    /* 0x04 */ u8 size;
    /* 0x05 */ u8 gender;
    /* 0x06 */ u8 leadership;
    /* 0x08 */ u16 hpBase;
    /* 0x0A */ u8 hpGrowth;
    /* 0x0C */ u16 strBase;
    /* 0x0E */ u8 strGrowth;
    /* 0x10 */ u16 vitBase;
    /* 0x12 */ u8 vitGrowth;
    /* 0x14 */ u16 intBase;
    /* 0x16 */ u8 intGrowth;
    /* 0x18 */ u16 menBase;
    /* 0x1A */ u8 menGrowth;
    /* 0x1C */ u16 agiBase;
    /* 0x1E */ u8 agiGrowth;
    /* 0x20 */ u16 dexBase;
    /* 0x22 */ u8 dexGrowth;
    /* 0x23 */ u8 luck;
    /* 0x24 */ u8 alignment;
    /* 0x25 */ u8 resist[7]; /* Physical, Wind, Flame, Earth, Water, Virtue, Bane */
    /* 0x2C */ u8 movement;
    /* 0x2E */ u16 defaultItems[4];
    /* 0x36 */ u8 lockedSlots;
    /* 0x37 */ u8 attacks[3][2]; /* (attack id, count) per row */
    /* 0x3D */ u8 physAttack;
    /* 0x3E */ u8 magicAttack;
    /* 0x3F */ u8 physDefense;
    /* 0x40 */ u8 magicDefense;
    /* 0x41 */ u8 promotions[4];
    /* 0x45 */ u8 baseClass;
    /* 0x46 */ u8 element;
    /* 0x47 */ u8 squadSlots;
} ClassData; /* size 0x48 */

/* gItemTable: 278 records */
typedef struct {
    /* 0x00 */ char *name;
    /* 0x04 */ u8 category;
    /* 0x05 */ u8 element;
    /* 0x06 */ u8 rank;
    /* 0x08 */ u16 price;
    /* 0x0A */ u8 str;
    /* 0x0B */ u8 intl;
    /* 0x0C */ u8 agi;
    /* 0x0D */ u8 dex;
    /* 0x0E */ u8 vit;
    /* 0x0F */ u8 men;
    /* 0x10 */ s8 luck;
    /* 0x11 */ s8 resist[7];
    /* 0x18 */ u8 growth[2];
    /* 0x1A */ u8 flags;
    /* 0x1B */ u8 inflict;
    /* 0x1C */ u8 protect;
} ItemData; /* size 0x20 */

/* gConsumableTable: 45 records */
typedef struct {
    /* 0x00 */ char *name;
    /* 0x04 */ u8 kind;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u16 price;
    /* 0x08 */ u8 target;
    /* 0x09 */ u8 use;
} ConsumableData; /* size 0xC */

/* gAttackTable: 159 records */
typedef struct {
    /* 0x00 */ char *name;
    /* 0x04 */ u8 kind;
    /* 0x05 */ u8 element;
    /* 0x06 */ u8 effect1[4];
    /* 0x0A */ u8 effect2[4];
} AttackData; /* size 0x10 */

/* Character record: player 0x80193BC0 (0x38 bytes), enemy 0x80195560 (0x34 bytes) */
typedef struct {
    /* 0x00 */ u8 unk00[0x11];
    /* 0x11 */ u8 cls;
    /* 0x12 */ u8 baseCls;
    /* 0x13 */ u8 level;
    /* 0x14 */ u8 gender;
    /* 0x16 */ u16 maxHp;
    /* 0x18 */ u16 hp;
    /* 0x1A */ u8 element;
    /* 0x1B */ u8 alignment;
    /* 0x1C */ u16 str;
    /* 0x1E */ u16 vit;
    /* 0x20 */ u16 intl;
    /* 0x22 */ u16 men;
    /* 0x24 */ u16 agi;
    /* 0x26 */ u16 dex;
    /* 0x28 */ u8 luck;
    /* 0x2A */ u16 items[4];
    /* 0x32 */ u8 fatigue;
    /* 0x33 */ u8 status;
} Character;

extern ClassData gClassTable[];
extern ItemData gItemTable[];
extern ConsumableData gConsumableTable[];
extern AttackData gAttackTable[];

#endif /* TABLES_H */
