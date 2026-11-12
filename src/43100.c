#include "common.h"
#include "tables.h"


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

INCLUDE_ASM("asm/nonmatchings/43100", func_8016DCD4_ovl_040E80);

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

INCLUDE_ASM("asm/nonmatchings/43100", func_8016DF18_ovl_040E80);

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

INCLUDE_ASM("asm/nonmatchings/43100", func_8016E0D8_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/43100", func_8016E140_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/43100", func_8016E174_ovl_040E80);

char * func_8016E1DC_ovl_040E80(u8 cls, u8 other) {
    if (gClassTable[cls].baseClass == other) {
        return gClassTable[cls].name;
    }
    return gClassTable[other].name;
}

INCLUDE_ASM("asm/nonmatchings/43100", func_8016E230_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/43100", func_8016E338_ovl_040E80);

char * AttackGetName(u8 id) {
    return gAttackTable[id].name;
}

u8 func_8016E458_ovl_040E80(u8 id) {
    return gAttackTable[id].kind;
}

INCLUDE_ASM("asm/nonmatchings/43100", AttackGetElement);

INCLUDE_ASM("asm/nonmatchings/43100", func_8016E50C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/43100", ClassAtLevel);

INCLUDE_ASM("asm/nonmatchings/43100", func_8016EAEC_ovl_040E80);

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

INCLUDE_ASM("asm/nonmatchings/43100", ItemGetElement);

u8 ItemGetRank(u16 id) {
    return gItemTable[id].rank;
}

u16 func_8016F62C_ovl_040E80(u16 id) {
    return gItemTable[id].price;
}

s8 func_8016F644_ovl_040E80(u16 id) {
    return gItemTable[id].luck;
}

INCLUDE_ASM("asm/nonmatchings/43100", func_8016F65C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/43100", func_8016F6AC_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/43100", func_8016F6FC_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/43100", func_8016F74C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/43100", func_8016F79C_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/43100", func_8016F7EC_ovl_040E80);

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

INCLUDE_ASM("asm/nonmatchings/43100", ItemIsWeapon);

INCLUDE_ASM("asm/nonmatchings/43100", func_8016FA34_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/43100", func_8016FB50_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/43100", func_8016FBE0_ovl_040E80);

INCLUDE_ASM("asm/nonmatchings/43100", func_8016FCEC_ovl_040E80);
