#include "common.h"
#include "tables.h"

extern u8 D_80193C12_ovl_040E80;
extern u16 D_80193C14_ovl_040E80;
extern u16 D_80193C16_ovl_040E80;
extern u16 D_80193C18_ovl_040E80;
extern u16 D_80193C1A_ovl_040E80;
extern u16 D_80193C1C_ovl_040E80;
extern u16 D_80193C1E_ovl_040E80;

char *AttackGetName(u8 id);

extern u8 D_8018ECE4_ovl_040E80[][6];

u16 func_8016FA34_ovl_040E80(u16 a, u16 b, u16 c, u16 d);
u16 func_8016FB50_ovl_040E80(u16 a, u16 b, u16 c, u16 d);
u8 ItemGetElement(u16 id);

extern u16 (*D_8018B494_ovl_040E80[])(u8 cls, u8 baseCls);

typedef struct {
    u16 sprite[2]; /* (chunk index << 3) | sub-image, for the two variants */
    u8 flags;
} ClassSpriteInfo;
extern ClassSpriteInfo D_8018ECE0_ovl_040E80[];

s32 ChunkSize(s32 handle);
void *LoadChunkRaw(void *dst, s32 handle);
void *LoadChunk(s32 handle);
void *HMalloc(s32 size);
void HFree(void *p);
void *LoadAsset();


u8 func_8016D200_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].squadSlots;
    }
    return gClassTable[other].squadSlots;
}

u8 func_8016D254_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].element;
    }
    return gClassTable[other].element;
}

u8 func_8016D2A8_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].lockedSlots;
    }
    return gClassTable[other].lockedSlots;
}

u8 func_8016D2FC_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].physAttack;
    }
    return gClassTable[other].physAttack;
}

u8 func_8016D350_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].magicAttack;
    }
    return gClassTable[other].magicAttack;
}

u8 func_8016D3A4_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].physDefense;
    }
    return gClassTable[other].physDefense;
}

u8 func_8016D3F8_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].magicDefense;
    }
    return gClassTable[other].magicDefense;
}

u16 func_8016D44C_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].hpBase;
    }
    return gClassTable[other].hpBase;
}

u8 func_8016D4A0_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].hpGrowth;
    }
    return gClassTable[other].hpGrowth;
}

u16 func_8016D4F4_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].strBase;
    }
    return gClassTable[other].strBase;
}

u8 func_8016D548_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].strGrowth;
    }
    return gClassTable[other].strGrowth;
}

u16 func_8016D59C_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].vitBase;
    }
    return gClassTable[other].vitBase;
}

u8 func_8016D5F0_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].vitGrowth;
    }
    return gClassTable[other].vitGrowth;
}

u16 func_8016D644_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].intBase;
    }
    return gClassTable[other].intBase;
}

u8 func_8016D698_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].intGrowth;
    }
    return gClassTable[other].intGrowth;
}

u16 func_8016D6EC_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].menBase;
    }
    return gClassTable[other].menBase;
}

u8 func_8016D740_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].menGrowth;
    }
    return gClassTable[other].menGrowth;
}

u16 func_8016D794_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].agiBase;
    }
    return gClassTable[other].agiBase;
}

u8 func_8016D7E8_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].agiGrowth;
    }
    return gClassTable[other].agiGrowth;
}

u16 func_8016D83C_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].dexBase;
    }
    return gClassTable[other].dexBase;
}

u8 func_8016D890_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].dexGrowth;
    }
    return gClassTable[other].dexGrowth;
}

u8 func_8016D8E4_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].luck;
    }
    return gClassTable[other].luck;
}

u8 func_8016D938_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].alignment;
    }
    return gClassTable[other].alignment;
}

u8 func_8016D98C_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].resist[0];
    }
    return gClassTable[other].resist[0];
}

u8 func_8016D9E0_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].resist[1];
    }
    return gClassTable[other].resist[1];
}

u8 func_8016DA34_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].resist[2];
    }
    return gClassTable[other].resist[2];
}

u8 func_8016DA88_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].resist[3];
    }
    return gClassTable[other].resist[3];
}

u8 func_8016DADC_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].resist[4];
    }
    return gClassTable[other].resist[4];
}

u8 func_8016DB30_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].resist[5];
    }
    return gClassTable[other].resist[5];
}

u8 func_8016DB84_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].resist[6];
    }
    return gClassTable[other].resist[6];
}

u8 func_8016DBD8_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].movement;
    }
    return gClassTable[other].movement;
}

u8 func_8016DC2C_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].attacks[0][0];
    }
    return gClassTable[other].attacks[0][0];
}

u8 func_8016DC80_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].attacks[0][1];
    }
    return gClassTable[other].attacks[0][1];
}

u8 func_8016DCD4_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[gClassTable[cls].baseClass].attacks[1][0];
    }
    return gClassTable[other].attacks[1][0];
}

u8 func_8016DD20_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].attacks[1][1];
    }
    return gClassTable[other].attacks[1][1];
}

u8 func_8016DD74_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].attacks[2][0];
    }
    return gClassTable[other].attacks[2][0];
}

u8 func_8016DDC8_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].attacks[2][1];
    }
    return gClassTable[other].attacks[2][1];
}

u8 func_8016DE1C_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].size;
    }
    return gClassTable[other].size;
}

u8 func_8016DE70_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].gender;
    }
    return gClassTable[other].gender;
}

u8 func_8016DEC4_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].leadership;
    }
    return gClassTable[other].leadership;
}

u8 func_8016DF18_ovl_040E80(u8 cls, u8 other) {
    if (D_8018ECE4_ovl_040E80[cls][0] & 0x80) {
        if (gClassTable[cls].baseClass == other) {
            other = cls;
        }
    }
    return D_8018ECE4_ovl_040E80[other][0] & 0x3F;
}

u16 func_8016DF88_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].defaultItems[0];
    }
    return gClassTable[other].defaultItems[0];
}

u16 func_8016DFDC_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].defaultItems[1];
    }
    return gClassTable[other].defaultItems[1];
}

u16 func_8016E030_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].defaultItems[2];
    }
    return gClassTable[other].defaultItems[2];
}

u16 func_8016E084_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].defaultItems[3];
    }
    return gClassTable[other].defaultItems[3];
}

char *func_8016E0D8_ovl_040E80(u8 cls, u8 other) {
    u8 id;

    if (gClassTable[cls].baseClass == other) {
        id = gClassTable[cls].attacks[0][0];
    } else {
        id = gClassTable[other].attacks[0][0];
    }
    return AttackGetName(id);
}

#ifdef NON_MATCHING
/* Only the prologue's `sw ra` is scheduled later than in the original. */
char *func_8016E140_ovl_040E80(u8 unused, u8 cls) {
    return AttackGetName(gClassTable[cls].attacks[1][0]);
}
#else
INCLUDE_ASM("asm/nonmatchings/43100", func_8016E140_ovl_040E80);
#endif

char *func_8016E174_ovl_040E80(u8 cls, u8 other) {
    u8 id;

    if (gClassTable[cls].baseClass == other) {
        id = gClassTable[cls].attacks[2][0];
    } else {
        id = gClassTable[other].attacks[2][0];
    }
    return AttackGetName(id);
}

char * func_8016E1DC_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].name;
    }
    return gClassTable[other].name;
}

#ifdef NON_MATCHING
/* The class's attack id for a row, falling back to the other class when unset (0xFF).
 * One instruction short: the original lays out row 0's fallback after a `j` to the exit. */
u8 func_8016E230_ovl_040E80(u8 cls, u8 other, u8 row) {
    u8 v;

    if (gClassTable[cls].baseClass != other) {
        cls = other;
    }
    if (row == 0) {
        v = gClassTable[cls].attacks[0][0];
        if (v != 0xFF) {
            return v;
        }
        return gClassTable[other].attacks[0][0];
    }
    if (row == 1) {
        v = gClassTable[cls].attacks[1][0];
        if (v != 0xFF) {
            return v;
        }
        return gClassTable[other].attacks[1][0];
    }
    v = gClassTable[cls].attacks[2][0];
    if (v != 0xFF) {
        return v;
    }
    return gClassTable[other].attacks[2][0];
}
#else
INCLUDE_ASM("asm/nonmatchings/43100", func_8016E230_ovl_040E80);
#endif

#ifdef NON_MATCHING
/* The class's attack count for a row, falling back to the other class when unset (0xFF).
 * One instruction short: the original lays out row 0's fallback after a `j` to the exit. */
u8 func_8016E338_ovl_040E80(u8 cls, u8 other, u8 row) {
    u8 v;

    if (gClassTable[cls].baseClass != other) {
        cls = other;
    }
    if (row == 0) {
        v = gClassTable[cls].attacks[0][1];
        if (v != 0xFF) {
            return v;
        }
        return gClassTable[other].attacks[0][1];
    }
    if (row == 1) {
        v = gClassTable[cls].attacks[1][1];
        if (v != 0xFF) {
            return v;
        }
        return gClassTable[other].attacks[1][1];
    }
    v = gClassTable[cls].attacks[2][1];
    if (v != 0xFF) {
        return v;
    }
    return gClassTable[other].attacks[2][1];
}
#else
INCLUDE_ASM("asm/nonmatchings/43100", func_8016E338_ovl_040E80);
#endif

char * AttackGetName(u8 id) {
    return gAttackTable[id].name;
}

u8 func_8016E458_ovl_040E80(u8 id) {
    return gAttackTable[id].kind;
}

/* The attack's element, or for 0xFF / 0xF the element of the first matching equipped item. */
u8 AttackGetElement(u8 atk, u16 i0, u16 i1, u16 i2, u16 i3) {
    u8 e = gAttackTable[atk].element;
    u16 item;

    if (e != 0xFF && e != 0xF) {
        return e;
    }
    if (gAttackTable[atk].kind == 3) {
        item = func_8016FB50_ovl_040E80(i0, i1, i2, i3);
    } else {
        item = func_8016FA34_ovl_040E80(i0, i1, i2, i3);
    }
    if (item == 0) {
        return 0;
    }
    return ItemGetElement(item);
}

INCLUDE_ASM("asm/nonmatchings/43100", func_8016E50C_ovl_040E80);

/* The class a character of this class line has at the given level (promotion path). */
u8 ClassAtLevel(u8 cls, u8 other, u8 level) {
    if (gClassTable[cls].baseClass != other) {
        cls = other;
    }
    if (gClassTable[cls].promotions[1] != 0xFF && level < gClassTable[cls].promotions[1]) {
        cls = gClassTable[cls].promotions[0];
    } else if (gClassTable[cls].promotions[3] != 0xFF && level < gClassTable[cls].promotions[3]) {
        cls = gClassTable[cls].promotions[2];
    }
    return cls;
}

/* The item in an equipment slot, or the class's default for that slot when it is empty. */
u16 func_8016EAEC_ovl_040E80(Character *c, u8 slot) {
    u16 item = 0;

    switch (slot) {
        case 0:
            item = c->items[0];
            break;
        case 1:
            item = c->items[1];
            break;
        case 2:
            item = c->items[2];
            break;
        case 3:
            item = c->items[3];
            break;
    }
    if (item == 0) {
        item = D_8018B494_ovl_040E80[slot](c->cls, c->baseCls);
    }
    return item;
}

INCLUDE_ASM("asm/nonmatchings/43100", UnitLevelUp);

INCLUDE_ASM("asm/nonmatchings/43100", UnitSetupForLevel);

char * func_8016F4E0_ovl_040E80(u16 id) {
    return gConsumableTable[id].name;
}

u8 ConsumableGetKind(u16 id) {
    return gConsumableTable[id].kind;
}

u8 func_8016F520_ovl_040E80(u16 id) {
    return gConsumableTable[id].unk5;
}

u8 ConsumableGetTarget(u16 id) {
    return gConsumableTable[id].target;
}

u8 ConsumableGetUse(u16 id) {
    return gConsumableTable[id].use;
}

u8 func_8016F580_ovl_040E80(u16 id) {
    return gItemTable[id].inflict;
}

u8 func_8016F598_ovl_040E80(u16 id) {
    return gItemTable[id].protect;
}

char * func_8016F5B0_ovl_040E80(u16 id) {
    return gItemTable[id].name;
}

u8 ItemGetCategory(u16 id) {
    return gItemTable[id].category;
}

/* Element 16 (Gallant Doll) takes the lord's element. */
u8 ItemGetElement(u16 id) {
    u8 e = gItemTable[id].element;

    if (e == 16) {
        e = D_80193C12_ovl_040E80;
    }
    return e;
}

u8 ItemGetRank(u16 id) {
    return gItemTable[id].rank;
}

u16 func_8016F62C_ovl_040E80(u16 id) {
    return gItemTable[id].price;
}

s8 func_8016F644_ovl_040E80(u16 id) {
    return gItemTable[id].luck;
}

/* Item 132 (Gallant Doll) gives the lord's stat / 20. */
s8 func_8016F65C_ovl_040E80(u16 id) {
    u8 v;

    if (id == 132) {
        v = D_80193C14_ovl_040E80 / 20;
    } else {
        v = gItemTable[id].str;
    }
    return v;
}

/* Item 132 (Gallant Doll) gives the lord's stat / 20. */
s8 func_8016F6AC_ovl_040E80(u16 id) {
    u8 v;

    if (id == 132) {
        v = D_80193C16_ovl_040E80 / 20;
    } else {
        v = gItemTable[id].vit;
    }
    return v;
}

/* Item 132 (Gallant Doll) gives the lord's stat / 20. */
s8 func_8016F6FC_ovl_040E80(u16 id) {
    u8 v;

    if (id == 132) {
        v = D_80193C18_ovl_040E80 / 20;
    } else {
        v = gItemTable[id].intl;
    }
    return v;
}

/* Item 132 (Gallant Doll) gives the lord's stat / 20. */
s8 func_8016F74C_ovl_040E80(u16 id) {
    u8 v;

    if (id == 132) {
        v = D_80193C1A_ovl_040E80 / 20;
    } else {
        v = gItemTable[id].men;
    }
    return v;
}

/* Item 132 (Gallant Doll) gives the lord's stat / 20. */
s8 func_8016F79C_ovl_040E80(u16 id) {
    u8 v;

    if (id == 132) {
        v = D_80193C1C_ovl_040E80 / 20;
    } else {
        v = gItemTable[id].agi;
    }
    return v;
}

/* Item 132 (Gallant Doll) gives the lord's stat / 20. */
s8 func_8016F7EC_ovl_040E80(u16 id) {
    u8 v;

    if (id == 132) {
        v = D_80193C1E_ovl_040E80 / 20;
    } else {
        v = gItemTable[id].dex;
    }
    return v;
}

s8 func_8016F83C_ovl_040E80(u16 id) {
    return gItemTable[id].resist[0];
}

s8 func_8016F854_ovl_040E80(u16 id) {
    return gItemTable[id].resist[1];
}

s8 func_8016F86C_ovl_040E80(u16 id) {
    return gItemTable[id].resist[2];
}

s8 func_8016F884_ovl_040E80(u16 id) {
    return gItemTable[id].resist[3];
}

s8 func_8016F89C_ovl_040E80(u16 id) {
    return gItemTable[id].resist[4];
}

s8 func_8016F8B4_ovl_040E80(u16 id) {
    return gItemTable[id].resist[5];
}

s8 func_8016F8CC_ovl_040E80(u16 id) {
    return gItemTable[id].resist[6];
}

u8 func_8016F8E4_ovl_040E80(u16 id) {
    return (gItemTable[id].growth[0] >> 6);
}

u8 func_8016F900_ovl_040E80(u16 id) {
    return (gItemTable[id].growth[0] >> 4) & 3;
}

u8 func_8016F920_ovl_040E80(u16 id) {
    return (gItemTable[id].growth[0] >> 2) & 3;
}

u8 func_8016F940_ovl_040E80(u16 id) {
    return gItemTable[id].growth[0] & 3;
}

u8 func_8016F95C_ovl_040E80(u16 id) {
    return (gItemTable[id].growth[1] >> 6);
}

u8 func_8016F978_ovl_040E80(u16 id) {
    return (gItemTable[id].growth[1] >> 4) & 3;
}

u8 func_8016F998_ovl_040E80(u16 id) {
    return (gItemTable[id].growth[1] >> 2) & 3;
}

u8 func_8016F9B8_ovl_040E80(u16 id) {
    return gItemTable[id].growth[1] & 3;
}

u8 ItemGetFlag80(u16 id) {
    return (gItemTable[id].flags >> 7);
}

#ifdef NON_MATCHING
/* Same logic; GCC lays out the branches differently (the original tests c == 24 with bne/j). */
s32 ItemIsWeapon(u16 id) {
    s32 c = gItemTable[id].category;

    if (c != 0) {
        if (c < 14) {
            return 1;
        }
        if (c != 24) {
            return 0;
        }
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/43100", ItemIsWeapon);
#endif

INCLUDE_ASM("asm/nonmatchings/43100", func_8016FA34_ovl_040E80);

/* The first of the four items with category 23, or 0. */
u16 func_8016FB50_ovl_040E80(u16 a, u16 b, u16 c, u16 d) {
    if (gItemTable[a].category == 23) {
        return a;
    }
    if (gItemTable[b].category == 23) {
        return b;
    }
    if (gItemTable[c].category == 23) {
        return c;
    }
    if (gItemTable[d].category == 23) {
        return d;
    }
    return 0;
}

/* Loads a class's sprite sheet (variant 0 or 1) through the handle table in chunk 0x1DFB6EA.
 * Returns the loaded chunk and stores a pointer to the sub-image's 0xA0-byte record in *out. */
void *func_8016FBE0_ovl_040E80(u8 cls, u8 variant, void **out) {
    s32 *handles = HMalloc(ChunkSize(0x1DFB6EA));
    u16 v;
    s32 index;
    s32 sub;
    u8 *chunk;
    s32 *entry;

    if (variant == 0) {
        v = D_8018ECE0_ovl_040E80[cls].sprite[0];
        index = v >> 3;
    } else {
        v = D_8018ECE0_ovl_040E80[cls].sprite[1];
        index = v >> 3;
    }
    sub = v & 7;
    LoadChunkRaw(handles, 0x1DFB6EA);
    index *= 4;
    entry = (s32 *)(index + (s32)handles);
    if (ChunkSize(*entry) != 0) {
        chunk = LoadChunk(*entry);
        *out = chunk + (sub * 0xA0 + 0x780);
    } else {
        chunk = NULL;
        *out = NULL;
    }
    HFree(handles);
    return chunk;
}

#ifdef NON_MATCHING
/* As func_8016FBE0, through LoadAsset. Register allocation differs around the u16 sprite value. */
void *func_8016FCEC_ovl_040E80(u8 cls, u8 variant, void **out) {
    u16 v;
    s32 sub;
    u8 *chunk;

    if (variant == 0) {
        v = D_8018ECE0_ovl_040E80[cls].sprite[0];
    } else {
        v = D_8018ECE0_ovl_040E80[cls].sprite[1];
    }
    sub = v & 7;
    if (v != 0) {
        chunk = LoadAsset(0x1DFB6EA, v >> 3, -10);
        *out = chunk + (sub * 0xA0 + 0x780);
    } else {
        chunk = NULL;
        *out = NULL;
    }
    return chunk;
}
#else
INCLUDE_ASM("asm/nonmatchings/43100", func_8016FCEC_ovl_040E80);
#endif
