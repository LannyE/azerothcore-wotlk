/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ACORE_SHAREDDEFINES_H
#define ACORE_SHAREDDEFINES_H

#include "DBCEnums.h"
#include "Define.h"
#include "EnumFlag.h"
#include <cassert>

float const GROUND_HEIGHT_TOLERANCE = 0.05f; // Extra tolerance to z position to check if it is in air or on ground.
constexpr float Z_OFFSET_FIND_HEIGHT = 2.0f;

enum SpellEffIndex : uint8
{
    EFFECT_0 = 0,
    EFFECT_1 = 1,
    EFFECT_2 = 2,
};

// used in script definitions
#define EFFECT_FIRST_FOUND 254
#define EFFECT_ALL 255

// loot modes for creatures and gameobjects, bitmask!
enum LootModes
{
    LOOT_MODE_DEFAULT                  = 0x01,
    LOOT_MODE_HARD_MODE_1              = 0x02,
    LOOT_MODE_HARD_MODE_2              = 0x04,
    LOOT_MODE_HARD_MODE_3              = 0x08,
    LOOT_MODE_HARD_MODE_4              = 0x10,
    LOOT_MODE_JUNK_FISH                = 0x8000
};

enum Expansions
{
    EXPANSION_CLASSIC                  = 0,
    EXPANSION_THE_BURNING_CRUSADE      = 1,
    EXPANSION_WRATH_OF_THE_LICH_KING   = 2,
    MAX_EXPANSIONS                     = 3
};

enum Gender
{
    GENDER_MALE                        = 0,
    GENDER_FEMALE                      = 1,
    GENDER_NONE                        = 2
};

// Race value is index in ChrRaces.dbc
// EnumUtils: DESCRIBE THIS
enum Races
{
    RACE_NONE               = 0,  // SKIP
    RACE_HUMAN              = 1,  // TITLE Human
    RACE_ORC                = 2,  // TITLE Orc
    RACE_DWARF              = 3,  // TITLE Dwarf
    RACE_NIGHTELF           = 4,  // TITLE Night Elf
    RACE_UNDEAD_PLAYER      = 5,  // TITLE Undead
    RACE_TAUREN             = 6,  // TITLE Tauren
    RACE_GNOME              = 7,  // TITLE Gnome
    RACE_TROLL              = 8,  // TITLE Troll
    //RACE_GOBLIN             = 9,
    RACE_BLOODELF           = 10, // TITLE Blood Elf
    RACE_DRAENEI            = 11 //, TITLE Draenei
    //RACE_FEL_ORC        = 12,
    //RACE_NAGA           = 13,
    //RACE_BROKEN         = 14,
    //RACE_SKELETON       = 15,
    //RACE_VRYKUL         = 16,
    //RACE_TUSKARR        = 17,
    //RACE_FOREST_TROLL   = 18,
    //RACE_TAUNKA         = 19,
    //RACE_NORTHREND_SKELETON = 20,
    //RACE_ICE_TROLL      = 21
};

// max+1 for player race
#define MAX_RACES         12

#define RACEMASK_ALL_PLAYABLE \
    ((1<<(RACE_HUMAN-1))   |(1<<(RACE_ORC-1))          |(1<<(RACE_DWARF-1))   | \
    (1<<(RACE_NIGHTELF-1))|(1<<(RACE_UNDEAD_PLAYER-1))|(1<<(RACE_TAUREN-1))  | \
    (1<<(RACE_GNOME-1))   |(1<<(RACE_TROLL-1))        |(1<<(RACE_BLOODELF-1))| \
    (1<<(RACE_DRAENEI-1)))

#define RACEMASK_ALLIANCE \
    ((1<<(RACE_HUMAN-1)) | (1<<(RACE_DWARF-1)) | (1<<(RACE_NIGHTELF-1)) | \
    (1<<(RACE_GNOME-1)) | (1<<(RACE_DRAENEI-1)))

#define RACEMASK_HORDE RACEMASK_ALL_PLAYABLE & ~RACEMASK_ALLIANCE

// DisplayRace values from CreatureDisplayInfoExtra.dbc
enum class DisplayRace : uint8
{
    None              = 0,
    Human             = 1,
    Orc               = 2,
    Dwarf             = 3,
    NightElf          = 4,
    Undead            = 5,
    Tauren            = 6,
    Gnome             = 7,
    Troll             = 8,
    Goblin            = 9,
    BloodElf          = 10,
    Draenei           = 11,
    FelOrc            = 12,
    Naga              = 13,
    Broken            = 14,
    Skeleton          = 15,
    Vrykul            = 16,
    Tuskarr           = 17,
    ForestTroll       = 18,
    Taunka            = 19,
    NorthrendSkeleton = 20,
    IceTroll          = 21
};

// Class value is index in ChrClasses.dbc
// EnumUtils: DESCRIBE THIS
enum Classes
{
    CLASS_NONE          = 0, // SKIP
    CLASS_WARRIOR       = 1, // TITLE Warrior
    CLASS_PALADIN       = 2, // TITLE Paladin
    CLASS_HUNTER        = 3, // TITLE Hunter
    CLASS_ROGUE         = 4, // TITLE Rogue
    CLASS_PRIEST        = 5, // TITLE Priest
    CLASS_DEATH_KNIGHT  = 6, // TITLE Death Knight
    CLASS_SHAMAN        = 7, // TITLE Shaman
    CLASS_MAGE          = 8, // TITLE Mage
    CLASS_WARLOCK       = 9, // TITLE Warlock
    //CLASS_UNK           = 10,
    CLASS_DRUID         = 11 // TITLE Druid
};

// max+1 for player class
#define MAX_CLASSES       12

#define CLASSMASK_ALL_PLAYABLE \
    ((1<<(CLASS_WARRIOR-1))|(1<<(CLASS_PALADIN-1))|(1<<(CLASS_HUNTER-1))| \
    (1<<(CLASS_ROGUE-1))  |(1<<(CLASS_PRIEST-1)) |(1<<(CLASS_SHAMAN-1))| \
    (1<<(CLASS_MAGE-1))   |(1<<(CLASS_WARLOCK-1))|(1<<(CLASS_DRUID-1)) | \
    (1<<(CLASS_DEATH_KNIGHT-1)))

// valid classes for creature_template.unit_class
enum UnitClass
{
    UNIT_CLASS_WARRIOR                  = 1,
    UNIT_CLASS_PALADIN                  = 2,
    UNIT_CLASS_ROGUE                    = 4,
    UNIT_CLASS_MAGE                     = 8,
};

//npcbot
/*
//end npcbot
#define CLASSMASK_ALL_CREATURES ((1<<(UNIT_CLASS_WARRIOR-1)) | (1<<(UNIT_CLASS_PALADIN-1)) | (1<<(UNIT_CLASS_ROGUE-1)) | (1<<(UNIT_CLASS_MAGE-1)))
//npcbot
*/
#define CLASSMASK_ALL_CREATURES CLASSMASK_ALL_PLAYABLE
//end npcbot

#define CLASSMASK_WAND_USERS ((1<<(CLASS_PRIEST-1))|(1<<(CLASS_MAGE-1))|(1<<(CLASS_WARLOCK-1)))

#define PLAYER_MAX_BATTLEGROUND_QUEUES 2

enum ReputationRank : uint8
{
    REP_HATED       = 0,
    REP_HOSTILE     = 1,
    REP_UNFRIENDLY  = 2,
    REP_NEUTRAL     = 3,
    REP_FRIENDLY    = 4,
    REP_HONORED     = 5,
    REP_REVERED     = 6,
    REP_EXALTED     = 7
};

enum FactionTemplates
{
    FACTION_NONE                        = 0,
    FACTION_CREATURE                    = 7,
    FACTION_ESCORTEE_A_NEUTRAL_PASSIVE  = 10,
    FACTION_MONSTER                     = 14,
    FACTION_MONSTER_2                   = 16,
    FACTION_BOOTY_BAY                   = 21,
    FACTION_TROLL_BLOODSCALP            = 28,
    FACTION_PREY                        = 31,
    FACTION_ESCORTEE_H_NEUTRAL_PASSIVE  = 33,
    FACTION_FRIENDLY                    = 35,
    FACTION_TROLL_FROSTMANE             = 37,
    FACTION_OGRE                        = 45,
    FACTION_ORC_DRAGONMAW               = 62,
    FACTION_HORDE_GENERIC               = 83,
    FACTION_ALLIANCE_GENERIC            = 84,
    FACTION_BLACKFATHOM                 = 88,
    FACTION_DEMON                       = 90,
    FACTION_ELEMENTAL                   = 91,
    FACTION_DRAGONFLIGHT_BLACK          = 103,
    FACTION_ESCORTEE_N_NEUTRAL_PASSIVE  = 113,
    FACTION_STORMWIND                   = 123,
    FACTION_ENEMY                       = 168,
    FACTION_ESCORTEE_A_NEUTRAL_ACTIVE   = 231,
    FACTION_ESCORTEE_H_NEUTRAL_ACTIVE   = 232,
    FACTION_ESCORTEE_N_NEUTRAL_ACTIVE   = 250,
    FACTION_ESCORTEE_N_FRIEND_PASSIVE   = 290,
    FACTION_TITAN                       = 415,
    FACTION_ESCORTEE_N_FRIEND_ACTIVE    = 495,
    FACTION_RATCHET                     = 637,
    FACTION_GOBLIN_DARK_IRON_BAR_PATRON = 736,
    FACTION_DARK_IRON_DWARVES           = 754,
    FACTION_ESCORTEE_A_PASSIVE          = 774,
    FACTION_ESCORTEE_H_PASSIVE          = 775,
    FACTION_UNDEAD_SCOURGE              = 974,
    FACTION_DRAGONKIN                   = 1720,
    FACTION_EARTHEN_RING                = 1726,
    FACTION_ALLIANCE_GENERIC_WG         = 1732,
    FACTION_HORDE_GENERIC_WG            = 1735,
    FACTION_ARAKKOA                     = 1738,
    FACTION_ASHTONGUE_DEATHSWORN        = 1820,
    FACTION_FLAYER_HUNTER               = 1840,
    FACTION_MONSTER_SPAR_BUDDY          = 1868,
    FACTION_VALIANCE_EXPEDITION_7       = 1974,
    FACTION_ESCORTEE_N_ACTIVE           = 1986,
    FACTION_UNDEAD_SCOURGE_9            = 1988,
    FACTION_ESCORTEE_H_ACTIVE           = 2046,
    FACTION_UNDEAD_SCOURGE_2            = 2068,
    FACTION_UNDEAD_SCOURGE_3            = 2084,
    FACTION_SCARLET_CRUSADE             = 2089,
    FACTION_SCARLET_CRUSADE_2           = 2096
};

#define MIN_REPUTATION_RANK (REP_HATED)
#define MAX_REPUTATION_RANK 8

#define MAX_SPILLOVER_FACTIONS 6

enum MoneyConstants
{
    COPPER = 1,
    SILVER = COPPER * 100,
    GOLD   = SILVER * 100
};

enum Stats
{
    STAT_STRENGTH                      = 0,
    STAT_AGILITY                       = 1,
    STAT_STAMINA                       = 2,
    STAT_INTELLECT                     = 3,
    STAT_SPIRIT                        = 4
};

#define MAX_STATS                        5

enum Powers
{
    POWER_MANA                          = 0,
    POWER_RAGE                          = 1,
    POWER_FOCUS                         = 2,
    POWER_ENERGY                        = 3,
    POWER_HAPPINESS                     = 4,
    POWER_RUNE                          = 5,
    POWER_RUNIC_POWER                   = 6,
    MAX_POWERS                          = 7,
    POWER_ALL                           = 127,    // default for class?
    POWER_HEALTH                        = 0xFFFFFFFE    // (-2 as signed value)
};

enum SpellSchools
{
    SPELL_SCHOOL_NORMAL                 = 0,
    SPELL_SCHOOL_HOLY                   = 1,
    SPELL_SCHOOL_FIRE                   = 2,
    SPELL_SCHOOL_NATURE                 = 3,
    SPELL_SCHOOL_FROST                  = 4,
    SPELL_SCHOOL_SHADOW                 = 5,
    SPELL_SCHOOL_ARCANE                 = 6
};

constexpr auto MAX_SPELL_SCHOOL = 7;

enum SpellSchoolMask
{
    SPELL_SCHOOL_MASK_NONE    = 0x00,                       // not exist
    SPELL_SCHOOL_MASK_NORMAL  = (1 << SPELL_SCHOOL_NORMAL), // PHYSICAL (Armor)
    SPELL_SCHOOL_MASK_HOLY    = (1 << SPELL_SCHOOL_HOLY),
    SPELL_SCHOOL_MASK_FIRE    = (1 << SPELL_SCHOOL_FIRE),
    SPELL_SCHOOL_MASK_NATURE  = (1 << SPELL_SCHOOL_NATURE),
    SPELL_SCHOOL_MASK_FROST   = (1 << SPELL_SCHOOL_FROST),
    SPELL_SCHOOL_MASK_SHADOW  = (1 << SPELL_SCHOOL_SHADOW),
    SPELL_SCHOOL_MASK_ARCANE  = (1 << SPELL_SCHOOL_ARCANE),

    // unions

    // 124, not include normal and holy damage
    SPELL_SCHOOL_MASK_SPELL   = (SPELL_SCHOOL_MASK_FIRE   |
                                 SPELL_SCHOOL_MASK_NATURE | SPELL_SCHOOL_MASK_FROST  |
                                 SPELL_SCHOOL_MASK_SHADOW | SPELL_SCHOOL_MASK_ARCANE),
    // 126
    SPELL_SCHOOL_MASK_MAGIC   = (SPELL_SCHOOL_MASK_HOLY | SPELL_SCHOOL_MASK_SPELL),

    // 127
    SPELL_SCHOOL_MASK_ALL     = (SPELL_SCHOOL_MASK_NORMAL | SPELL_SCHOOL_MASK_MAGIC)
};

inline SpellSchools GetFirstSchoolInMask(SpellSchoolMask mask)
{
    for (int i = 0; i < MAX_SPELL_SCHOOL; ++i)
        if (mask & (1 << i))
            return SpellSchools(i);

    return SPELL_SCHOOL_NORMAL;
}

enum ItemQualities
{
    ITEM_QUALITY_POOR                  = 0,                 //GREY
    ITEM_QUALITY_NORMAL                = 1,                 //WHITE
    ITEM_QUALITY_UNCOMMON              = 2,                 //GREEN
    ITEM_QUALITY_RARE                  = 3,                 //BLUE
    ITEM_QUALITY_EPIC                  = 4,                 //PURPLE
    ITEM_QUALITY_LEGENDARY             = 5,                 //ORANGE
    ITEM_QUALITY_ARTIFACT              = 6,                 //LIGHT YELLOW
    ITEM_QUALITY_HEIRLOOM              = 7
};

#define MAX_ITEM_QUALITY                 8

enum SpellCategory
{
    SPELL_CATEGORY_FOOD             = 11,
    SPELL_CATEGORY_DRINK            = 59,
};

enum SpellVisualKit
{
    SPELL_VISUAL_KIT_FOOD           = 406,
    SPELL_VISUAL_KIT_DRINK          = 438
};

const uint32 ItemQualityColors[MAX_ITEM_QUALITY] =
{
    0xff9d9d9d,        //GREY
    0xffffffff,        //WHITE
    0xff1eff00,        //GREEN
    0xff0070dd,        //BLUE
    0xffa335ee,        //PURPLE
    0xffff8000,        //ORANGE
    0xffe6cc80,        //LIGHT YELLOW
    0xffe6cc80         //LIGHT YELLOW
};

std::size_t constexpr MAX_QUEST_DIFFICULTY = 5;
uint32 constexpr QuestDifficultyColors[MAX_QUEST_DIFFICULTY] =
{
    0xff40c040,
    0xff808080,
    0xffffff00,
    0xffff8040,
    0xffff2020
};

// ***********************************
// Spell Attributes definitions
// ***********************************

// EnumUtils: DESCRIBE THIS
enum SpellAttr0 : uint32
{
    SPELL_ATTR0_PROC_FAILURE_BURNS_CHARGE        = 0x00000001, // TITLE Unknown attribute 0@Attr0
    SPELL_ATTR0_USES_RANGED_SLOT                 = 0x00000002, // TITLE Treat as ranged attack DESCRIPTION Use ammo, ranged attack range modifiers, ranged haste, etc.
    SPELL_ATTR0_ON_NEXT_SWING_NO_DAMAGE          = 0x00000004, // TITLE On next melee (type 1) DESCRIPTION Both "on next swing" attributes have identical handling in server & client
    SPELL_ATTR0_DO_NOT_LOG_IMMUNE_MISSES         = 0x00000008, // TITLE Replenishment (client only)
    SPELL_ATTR0_IS_ABILITY                       = 0x00000010, // TITLE Treat as ability DESCRIPTION Cannot be reflected, not affected by cast speed modifiers, etc.
    SPELL_ATTR0_IS_TRADESKILL                    = 0x00000020, // TITLE Trade skill recipe DESCRIPTION Displayed in recipe list, not affected by cast speed modifiers
    SPELL_ATTR0_PASSIVE                          = 0x00000040, // TITLE Passive spell DESCRIPTION Spell is automatically cast on self by core
    SPELL_ATTR0_DO_NOT_DISPLAY                   = 0x00000080, // TITLE Hidden in UI (client only) DESCRIPTION Not visible in spellbook or aura bar (Spellbook, Aura Icon, Combat Log)
    SPELL_ATTR0_DO_NOT_LOG                       = 0x00000100, // TITLE Hidden in combat log (client only) DESCRIPTION Spell will not appear in combat logs
    SPELL_ATTR0_HELD_ITEM_ONLY                   = 0x00000200, // TITLE Auto-target mainhand item (client only) DESCRIPTION Client will automatically select main-hand item as cast target
    SPELL_ATTR0_ON_NEXT_SWING                    = 0x00000400, // TITLE On next melee (type 2) DESCRIPTION Both "on next swing" attributes have identical handling in server & client
    SPELL_ATTR0_WEARER_CASTS_PROC_TRIGGER        = 0x00000800, // TITLE Unknown attribute 11@Attr0
    SPELL_ATTR0_SERVER_ONLY                      = 0x00001000, // TITLE Unused attribute 12@Attr0 DESCRIPTION not set in 3.3.5a
    SPELL_ATTR0_ALLOW_ITEM_SPELL_IN_PVP          = 0x00002000, // TITLE Only usable during nighttime
    SPELL_ATTR0_ONLY_INDOORS                     = 0x00004000, // TITLE Only usable indoors
    SPELL_ATTR0_ONLY_OUTDOORS                    = 0x00008000, // TITLE Only usable outdoors
    SPELL_ATTR0_NOT_SHAPESHIFTED                 = 0x00010000, // TITLE Not usable while shapeshifted
    SPELL_ATTR0_ONLY_STEALTHED                   = 0x00020000, // TITLE Only usable in stealth
    SPELL_ATTR0_DO_NOT_SHEATH                    = 0x00040000, // TITLE Don't shealthe weapons (client only)
    SPELL_ATTR0_SCALES_WITH_CREATURE_LEVEL       = 0x00080000, // TITLE Scale with caster level DESCRIPTION For non-player casts, scale impact and power cost with caster's level
    SPELL_ATTR0_CANCELS_AUTO_ATTACK_COMBAT       = 0x00100000, // TITLE Stop attacking after cast DESCRIPTION After casting this, the current auto-attack will be interrupted
    SPELL_ATTR0_NO_ACTIVE_DEFENSE                = 0x00200000, // TITLE Prevent physical avoidance DESCRIPTION Spell cannot be dodged, parried or blocked
    SPELL_ATTR0_TRACK_TARGET_IN_CAST_PLAYER_ONLY = 0x00400000, // TITLE Automatically face target during cast (client only)
    SPELL_ATTR0_ALLOW_CAST_WHILE_DEAD            = 0x00800000, // TITLE Can be cast while dead DESCRIPTION Spells without this flag cannot be cast by dead units in non-triggered contexts
    SPELL_ATTR0_ALLOW_WHILE_MOUNTED              = 0x01000000, // TITLE Can be cast while mounted
    SPELL_ATTR0_COOLDOWN_ON_EVENT                = 0x02000000, // TITLE Cooldown starts on expiry DESCRIPTION Spell is unusable while already active, and cooldown does not begin until the effects have worn off
    SPELL_ATTR0_AURA_IS_DEBUFF                   = 0x04000000, // TITLE Is negative spell DESCRIPTION Forces the spell to be treated as a negative spell
    SPELL_ATTR0_ALLOW_WHILE_SITTING              = 0x08000000, // TITLE Can be cast while sitting
    SPELL_ATTR0_NOT_IN_COMBAT_ONLY_PEACEFUL      = 0x10000000, // TITLE Cannot be used in combat
    SPELL_ATTR0_NO_IMMUNITIES                    = 0x20000000, // TITLE Pierce invulnerability DESCRIPTION Allows spell to pierce invulnerability, unless the invulnerability spell also has this attribute
    SPELL_ATTR0_HEARTBEAT_RESIST                 = 0x40000000, // TITLE Periodic resistance checks DESCRIPTION Periodically re-rolls against resistance to potentially expire aura early
    SPELL_ATTR0_NO_AURA_CANCEL                   = 0x80000000  // TITLE Aura cannot be cancelled DESCRIPTION Prevents the player from voluntarily canceling a positive aura
};

// EnumUtils: DESCRIBE THIS
enum SpellAttr1 : uint32
{
    SPELL_ATTR1_DISMISS_PET_FIRST                        = 0x00000001, // TITLE Dismiss Pet on cast DESCRIPTION Without this attribute, summoning spells will fail if caster already has a pet
    SPELL_ATTR1_USE_ALL_MANA                             = 0x00000002, // TITLE Drain all power DESCRIPTION Ignores listed power cost and drains entire pool instead
    SPELL_ATTR1_IS_CHANNELED                             = 0x00000004, // TITLE Channeled (type 1) DESCRIPTION Both "channeled" attributes have identical handling in server & client
    SPELL_ATTR1_NO_REDIRECTION                           = 0x00000008, // TITLE Ignore redirection effects DESCRIPTION Spell will not be attracted by SPELL_MAGNET auras (Grounding Totem)
    SPELL_ATTR1_NO_SKILL_INCREASE                        = 0x00000010, // TITLE Unknown attribute 4@Attr1 DESCRIPTION stealth and whirlwind
    SPELL_ATTR1_ALLOW_WHILE_STEALTHED                    = 0x00000020, // TITLE Does not break stealth
    SPELL_ATTR1_IS_SELF_CHANNELED                        = 0x00000040, // TITLE Channeled (type 2) DESCRIPTION Both "channeled" attributes have identical handling in server & client
    SPELL_ATTR1_NO_REFLECTION                            = 0x00000080, // TITLE Ignore reflection effects DESCRIPTION Spell will pierce through Spell Reflection and similar
    SPELL_ATTR1_ONLY_PEACEFUL_TARGETS                    = 0x00000100, // TITLE Target cannot be in combat
    SPELL_ATTR1_INITIATE_COMBAT                          = 0x00000200, // TITLE Enables Auto-Attack (client only) DESCRIPTION Caster will begin auto-attacking the target on cast
    SPELL_ATTR1_NO_THREAT                                = 0x00000400, // TITLE Does not generate threat DESCRIPTION Also does not cause target to engage
    SPELL_ATTR1_AURA_UNIQUE                              = 0x00000800, // TITLE Aura will not refresh its duration when recast
    SPELL_ATTR1_FAILURE_BREAKS_STEALTH                   = 0x00001000, // TITLE Pickpocket (client only)
    SPELL_ATTR1_TOGGLE_FAR_SIGHT                         = 0x00002000, // TITLE Farsight aura (client only)
    SPELL_ATTR1_TRACK_TARGET_IN_CHANNEL                  = 0x00004000, // TITLE Track target while channeling DESCRIPTION While channeling, adjust facing to face target
    SPELL_ATTR1_IMMUNITY_PURGES_EFFECT                   = 0x00008000, // TITLE Immunity cancels preapplied auras DESCRIPTION For immunity spells, cancel all auras that this spell would make you immune to when the spell is applied
    SPELL_ATTR1_IMMUNITY_TO_HOSTILE_AND_FRIENDLY_EFFECTS = 0x00010000, // TITLE Unaffected by school immunities DESCRIPTION Will not pierce Divine Shield, Ice Block and other full invulnerabilities
    SPELL_ATTR1_NO_AUTOCAST_AI                           = 0x00020000, // TITLE Cannot be autocast by pet DESCRIPTION (AI)
    SPELL_ATTR1_PREVENTS_ANIM                            = 0x00040000, // TITLE NYI, auras apply UNIT_FLAG_PREVENT_EMOTES_FROM_CHAT_TEXT
    SPELL_ATTR1_EXCLUDE_CASTER                           = 0x00080000, // TITLE Cannot be self-cast
    SPELL_ATTR1_FINISHING_MOVE_DAMAGE                    = 0x00100000, // TITLE Requires combo points (type 1)
    SPELL_ATTR1_THREAT_ONLY_ON_MISS                      = 0x00200000, // TITLE Unknown attribute 21@Attr1
    SPELL_ATTR1_FINISHING_MOVE_DURATION                  = 0x00400000, // TITLE Requires combo points (type 2)
    SPELL_ATTR1_IGNORE_OWNERS_DEATH                      = 0x00800000, // TITLE Unknwon attribute 23@Attr1
    SPELL_ATTR1_SPECIAL_SKILLUP                          = 0x01000000, // TITLE Fishing (client only)
    SPELL_ATTR1_AURA_STAYS_AFTER_COMBAT                  = 0x02000000, // TITLE Aura stays after combat DESCRIPTION Aura will not be removed when the unit leaves combat
    SPELL_ATTR1_REQUIRE_ALL_TARGETS                      = 0x04000000, // TITLE Unknown attribute 26@Attr1 DESCRIPTION Related to [target=focus] and [target=mouseover] macros?
    SPELL_ATTR1_DISCOUNT_POWER_ON_MISS                   = 0x08000000, // TITLE Unknown attribute 27@Attr1 DESCRIPTION Melee spell?
    SPELL_ATTR1_NO_AURA_ICON                             = 0x10000000, // TITLE Hide in aura bar (client only)
    SPELL_ATTR1_NAME_IN_CHANNEL_BAR                      = 0x20000000, // TITLE Show spell name during channel (client only)
    SPELL_ATTR1_COMBO_ON_BLOCK                           = 0x40000000, // TITLE Enable at dodge DESCRIPTION (Mainline: Dispel All Stacks)
    SPELL_ATTR1_CAST_WHEN_LEARNED                        = 0x80000000  // TITLE Unknown attribute 31@Attr1
};

// EnumUtils: DESCRIBE THIS
enum SpellAttr2 : uint32
{
    SPELL_ATTR2_ALLOW_DEAD_TARGET                    = 0x00000001, // TITLE Can target dead players or corpses
    SPELL_ATTR2_NO_SHAPESHIFT_UI                     = 0x00000002, // TITLE Unknown attribute 1@Attr2 DESCRIPTION vanish, shadowform, Ghost Wolf and other
    SPELL_ATTR2_IGNORE_LINE_OF_SIGHT                 = 0x00000004, // TITLE Ignore Line of Sight
    SPELL_ATTR2_ALLOW_LOW_LEVEL_BUFF                 = 0x00000008, // TITLE Ignore aura scaling
    SPELL_ATTR2_USE_SHAPESHIFT_BAR                   = 0x00000010, // TITLE Show in stance bar (client only)
    SPELL_ATTR2_AUTO_REPEAT                          = 0x00000020, // TITLE Ranged auto-attack spell
    SPELL_ATTR2_CANNOT_CAST_ON_TAPPED                = 0x00000040, // TITLE Cannot target others' tapped units DESCRIPTION Can only target untapped units, or those tapped by caster
    SPELL_ATTR2_DO_NOT_REPORT_SPELL_FAILURE          = 0x00000080, // TITLE Unknown attribute 7@Attr2
    SPELL_ATTR2_INCLUDE_IN_ADVANCED_COMBAT_LOG       = 0x00000100, // TITLE Unused attribute 8@Attr2 DESCRIPTION not set in 3.3.5a
    SPELL_ATTR2_ALWAYS_CAST_AS_UNIT                  = 0x00000200, // TITLE Unknown attribute 9@Attr2
    SPELL_ATTR2_SPECIAL_TAMING_FLAG                  = 0x00000400, // TITLE Unknown attribute 10@Attr2 DESCRIPTION Related to taming?
    SPELL_ATTR2_NO_TARGET_PER_SECOND_COST            = 0x00000800, // TITLE Health Funnel
    SPELL_ATTR2_CHAIN_FROM_CASTER                    = 0x00001000, // TITLE Chain from caster DESCRIPTION Cleave, Heart Strike, Maul, Sunder Armor, Swipe
    SPELL_ATTR2_ENCHANT_OWN_ITEM_ONLY                = 0x00002000, // TITLE Enchant persists when entering arena
    SPELL_ATTR2_ALLOW_WHILE_INVISIBLE                = 0x00004000, // TITLE Unknown attribute 14@Attr2
    SPELL_ATTR2_DO_NOT_CONSUME_IF_GAINED_DURING_CAST = 0x00008000, // TITLE Unused attribute 15@Attr2 DESCRIPTION not set in 3.3.5a
    SPELL_ATTR2_NO_ACTIVE_PETS                       = 0x00010000, // TITLE Tame Beast
    SPELL_ATTR2_DO_NOT_RESET_COMBAT_TIMERS           = 0x00020000, // TITLE Don't reset swing timer DESCRIPTION Does not reset melee/ranged autoattack timer on cast
    SPELL_ATTR2_NO_JUMP_WHILE_CAST_PENDING           = 0x00040000, // TITLE Requires dead pet
    SPELL_ATTR2_ALLOW_WHILE_NOT_SHAPESHIFTED         = 0x00080000, // TITLE Also allow outside shapeshift (caster form) DESCRIPTION Even if Stances are nonzero, allow spell to be cast outside of shapeshift (though not in a different shapeshift)
    SPELL_ATTR2_INITIATE_COMBAT_POST_CAST            = 0x00100000, // TITLE (Enables Auto-Attack)
    SPELL_ATTR2_FAIL_ON_ALL_TARGETS_IMMUNE           = 0x00200000, // TITLE Damage reduction ability DESCRIPTION Causes BG flags to be dropped if combined with ATTR1_DISPEL_AURAS_ON_IMMUNITY
    SPELL_ATTR2_NO_INITIAL_THREAD                    = 0x00400000, // TITLE Unknown attribute 22@Attr2 DESCRIPTION Ambush, Backstab, Cheap Shot, Death Grip, Garrote, Judgements, Mutilate, Pounce, Ravage, Shiv, Shred
    SPELL_ATTR2_PROC_COOLDOWN_ON_FAILURE             = 0x00800000, // TITLE Arcane Concentration
    SPELL_ATTR2_ITEM_CAST_WITH_OWNER_SKILL           = 0x01000000, // TITLE Unknown attribute 24@Attr2
    SPELL_ATTR2_DONT_BLOCK_MANA_REGEN                = 0x02000000, // TITLE Unknown attribute 25@Attr2
    SPELL_ATTR2_NO_SCHOOL_IMMUNITIES                 = 0x04000000, // TITLE Pierce aura application immunities DESCRIPTION Allow aura to be applied despite target being immune to new aura applications
    SPELL_ATTR2_IGNORE_WEAPONSKILL                   = 0x08000000, // TITLE Unknown attribute 27@Attr2
    SPELL_ATTR2_NOT_AN_ACTION                        = 0x10000000, // TITLE Unknown attribute 28@Attr2
    SPELL_ATTR2_CANT_CRIT                            = 0x20000000, // TITLE Cannot critically strike
    SPELL_ATTR2_ACTIVE_THREAT                        = 0x40000000, // TITLE Allow triggered spell to trigger (type 1) DESCRIPTION Without this attribute, any triggered spell will be unable to trigger other auras' procs
    SPELL_ATTR2_RETAIN_ITEM_CAST                     = 0x80000000  // TITLE Food buff (client only)
};

// EnumUtils: DESCRIBE THIS
enum SpellAttr3 : uint32
{
    SPELL_ATTR3_PVP_ENABLING                          = 0x00000001, // TITLE Unknown attribute 0@Attr3
    SPELL_ATTR3_NO_PROC_EQUIP_REQUIREMENT             = 0x00000002, // TITLE 1 Ignores subclass mask check when checking proc
    SPELL_ATTR3_NO_CASTING_BAR_TEXT                   = 0x00000004, // TITLE Unknown attribute 2@Attr3
    SPELL_ATTR3_COMPLETELY_BLOCKED                    = 0x00000008, // TITLE Blockable spell
    SPELL_ATTR3_NO_RES_TIMER                          = 0x00000010, // TITLE Ignore resurrection timer
    SPELL_ATTR3_NO_DURABILITY_LOSS                    = 0x00000020, // TITLE Unknown attribute 5@Attr3
    SPELL_ATTR3_NO_AVOIDANCE                          = 0x00000040, // TITLE Unknown attribute 6@Attr3
    SPELL_ATTR3_DOT_STACKING_RULE                     = 0x00000080, // TITLE Stack separately for each caster
    SPELL_ATTR3_ONLY_ON_PLAYER                        = 0x00000100, // TITLE Can only target players
    SPELL_ATTR3_NOT_A_PROC                            = 0x00000200, // TITLE Allow triggered spell to trigger (type 2) DESCRIPTION Without this attribute, any triggered spell will be unable to trigger other auras' procs
    SPELL_ATTR3_REQUIRES_MAIN_HAND_WEAPON             = 0x00000400, // TITLE Require main hand weapon
    SPELL_ATTR3_ONLY_BATTLEGROUNDS                    = 0x00000800, // TITLE Can only be cast in battleground
    SPELL_ATTR3_ONLY_ON_GHOSTS                        = 0x00001000, // TITLE Can only target ghost players
    SPELL_ATTR3_HIDE_CHANNEL_BAR                      = 0x00002000, // TITLE Do not display channel bar (client only)
    SPELL_ATTR3_HIDE_IN_RAID_FILTER                   = 0x00004000, // TITLE Honorless Target
    SPELL_ATTR3_NORMAL_RANGED_ATTACK                  = 0x00008000, // TITLE Unknown attribute 15@Attr3 DESCRIPTION Auto Shoot, Shoot, Throw - ranged normal attack attribute?
    SPELL_ATTR3_SUPPRESS_CASTER_PROCS                 = 0x00010000, // TITLE Cannot trigger procs
    SPELL_ATTR3_SUPPRESS_TARGET_PROCS                 = 0x00020000, // TITLE No initial aggro
    SPELL_ATTR3_ALWAYS_HIT                            = 0x00040000, // TITLE Ignore hit result DESCRIPTION Spell cannot miss, or be dodged/parried/blocked
    SPELL_ATTR3_INSTANT_TARGET_PROCS                  = 0x00080000, // TITLE Cannot trigger spells during aura proc
    SPELL_ATTR3_ALLOW_AURA_WHILE_DEAD                 = 0x00100000, // TITLE Persists through death
    SPELL_ATTR3_ONLY_PROC_OUTDOORS                    = 0x00200000, // TITLE Unused attribute 21@Attr3 DESCRIPTION Not set in 3.3.5a
    SPELL_ATTR3_CASTING_CANCELS_AUTOREPEAT            = 0x00400000, // TITLE Unused attribute 22@Attr3 DESCRIPTION Not set in 3.3.5a
    SPELL_ATTR3_NO_DAMAGE_HISTORY                     = 0x00800000, // TITLE Unknown attribute 23@Attr3
    SPELL_ATTR3_REQUIRES_OFF_HAND_WEAPON              = 0x01000000, // TITLE Requires offhand weapon
    SPELL_ATTR3_TREAT_AS_PERIODIC                     = 0x02000000, // TITLE Treat as periodic effect
    SPELL_ATTR3_CAN_PROC_FROM_PROCS                   = 0x04000000, // TITLE Can trigger from triggered spells
    SPELL_ATTR3_ONLY_PROC_ON_CASTER                   = 0x08000000, // TITLE Drain Soul
    SPELL_ATTR3_IGNORE_CASTER_AND_TARGET_RESTRICTIONS = 0x10000000, // TITLE Unknown attribute 28@Attr3
    SPELL_ATTR3_IGNORE_CASTER_MODIFIERS               = 0x20000000, // TITLE Damage dealt is unaffected by modifiers
    SPELL_ATTR3_DO_NOT_DISPLAY_RANGE                  = 0x40000000, // TITLE Do not show range in tooltip (client only)
    SPELL_ATTR3_NOT_ON_AOE_IMMUNE                     = 0x80000000  // TITLE Unknown attribute 31@Attr3
};

// EnumUtils: DESCRIBE THIS
enum SpellAttr4 : uint32
{
    SPELL_ATTR4_NO_CAST_LOG                        = 0x00000001, // TITLE Cannot be resisted
    SPELL_ATTR4_CLASS_TRIGGER_ONLY_ON_TARGET       = 0x00000002, // TITLE Only proc on self-cast
    SPELL_ATTR4_AURA_EXPIRES_OFFLINE               = 0x00000004, // TITLE Buff expires while offline DESCRIPTION Debuffs (except Resurrection Sickness) will automatically do this
    SPELL_ATTR4_NO_HELPFUL_THREAT                  = 0x00000008, // TITLE Unknown attribute 3@Attr4
    SPELL_ATTR4_NO_HARMFUL_THREAT                  = 0x00000010, // TITLE Treat as delayed spell DESCRIPTION This will no longer cause guards to attack on use??
    SPELL_ATTR4_ALLOW_CLIENT_TARGETING             = 0x00000020, // TITLE Unknown attribute 5@Attr4
    SPELL_ATTR4_CANNOT_BE_STOLEN                   = 0x00000040, // TITLE Aura cannot be stolen
    SPELL_ATTR4_ALLOW_CAST_WHILE_CASTING           = 0x00000080, // TITLE Can be cast while casting DESCRIPTION Ignores already in-progress cast and still casts
    SPELL_ATTR4_IGNORE_DAMAGE_TAKEN_MODIFIERS      = 0x00000100, // TITLE Deals fixed damage
    SPELL_ATTR4_COMBAT_FEEDBACK_WHEN_USABLE        = 0x00000200, // TITLE Spell is initially disabled (client only)
    SPELL_ATTR4_WEAPON_SPEED_COST_SCALING          = 0x00000400, // TITLE Attack speed modifies cost DESCRIPTION Adds 10 to power cost for each 1s of weapon speed
    SPELL_ATTR4_NO_PARTIAL_IMMUNITY                = 0x00000800, // TITLE Unknown attribute 11@Attr4
    SPELL_ATTR4_AURA_IS_BUFF                       = 0x00001000, // TITLE Unknown attribute 12@Attr4
    SPELL_ATTR4_DO_NOT_LOG_CASTER                  = 0x00002000, // TITLE Unknown attribute 13@Attr4
    SPELL_ATTR4_REACTIVE_DAMAGE_PROC               = 0x00004000, // TITLE Damage does not break auras
    SPELL_ATTR4_NOT_IN_SPELLBOOK                   = 0x00008000, // TITLE Unknown attribute 15@Attr4
    SPELL_ATTR4_NOT_IN_ARENA_OR_RATED_BATTLEGROUND = 0x00010000, // TITLE Not usable in arena DESCRIPTION Makes spell unusable despite CD <= 10min
    SPELL_ATTR4_IGNORE_DEFAULT_ARENA_RESTRICTIONS  = 0x00020000, // TITLE Usable in arena DESCRIPTION Makes spell usable despite CD > 10min
    SPELL_ATTR4_BOUNCY_CHAIN_MISSILES              = 0x00040000, // TITLE Chain area targets DESCRIPTION [NYI] Hits area targets over time instead of all at once
    SPELL_ATTR4_ALLOW_PROC_WHILE_SITTING           = 0x00080000, // TITLE Unknown attribute 19@Attr4 DESCRIPTION proc dalayed, after damage or don't proc on absorb?
    SPELL_ATTR4_AURA_NEVER_BOUNCES                 = 0x00100000, // TITLE Allow self-cast to override stronger aura (client only)
    SPELL_ATTR4_ALLOW_ENETRING_ARENA               = 0x00200000, // TITLE Keep when entering arena
    SPELL_ATTR4_PROC_SUPPRESS_SWING_ANIM           = 0x00400000, // TITLE Unknown attribute 22@Attr4 DESCRIPTION Seal of Command (42058,57770) and Gymer's Smash 55426
    SPELL_ATTR4_SUPPRESS_WEAPON_PROCS               = 0x00800000, // TITLE Cannot trigger item spells
    SPELL_ATTR4_AUTO_RANGED_COMBAT                 = 0x01000000, // TITLE Unknown attribute 24@Attr4 DESCRIPTION Shoot-type spell?
    SPELL_ATTR4_OWNER_POWER_SCALING                = 0x02000000, // TITLE Pet Scaling aura
    SPELL_ATTR4_ONLY_FLYING_AREAS                  = 0x04000000, // TITLE Only in Outland/Northrend
    SPELL_ATTR4_FORCE_DISPLAY_CASTBAR              = 0x08000000, // TITLE Inherit critical chance from triggering aura
    SPELL_ATTR4_IGNORE_COMBAT_TIMERS               = 0x10000000, // TITLE Unknown attribute 28@Attr4 DESCRIPTION Aimed Shot
    SPELL_ATTR4_AURA_BOUNCE_FAILS_SPELL            = 0x20000000, // TITLE Unknown attribute 29@Attr4
    SPELL_ATTR4_OBSOLETE                           = 0x40000000, // TITLE Unknown attribute 30@Attr4
    SPELL_ATTR4_USE_FACING_FROM_SPELL              = 0x80000000  // TITLE Unknown attribute 31@Attr4 DESCRIPTION Polymorph (chicken) 228 and Sonic Boom (38052,38488)
};

// EnumUtils: DESCRIBE THIS
enum SpellAttr5 : uint32
{
    SPELL_ATTR5_ALLOW_ACTION_DURING_CHANNEL                    = 0x00000001, // TITLE Can be channeled while moving/casting
    SPELL_ATTR5_NO_REAGENT_COST_WITH_AURA                      = 0x00000002, // TITLE No reagents during arena preparation
    SPELL_ATTR5_REMOVE_ENTERING_ARENA                          = 0x00000004, // TITLE Remove when entering arena DESCRIPTION Force this aura to be removed on entering arena, regardless of other properties
    SPELL_ATTR5_ALLOW_WHILE_STUNNED                            = 0x00000008, // TITLE Usable while stunned
    SPELL_ATTR5_TRIGGERS_CHANNELING                            = 0x00000010, // TITLE Unknown attribute 4@Attr5
    SPELL_ATTR5_LIMIT_N                                        = 0x00000020, // TITLE Single-target aura DESCRIPTION Remove previous application to another unit if applied
    SPELL_ATTR5_IGNORE_AREA_EFFECT_PVP_CHECK                   = 0x00000040, // TITLE Unknown attribute 6@Attr5
    SPELL_ATTR5_NOT_ON_PLAYER                                  = 0x00000080, // TITLE Cannot target players
    SPELL_ATTR5_NOT_ON_PLAYER_CONTROLLED_NPC                   = 0x00000100, // TITLE Cannot target player controlled units but can target players
    SPELL_ATTR5_EXTRA_INITIAL_PERIOD                           = 0x00000200, // TITLE Immediately do periodic tick on apply
    SPELL_ATTR5_DO_NOT_DISPLAY_DURATION                        = 0x00000400, // TITLE Do not send aura duration to client
    SPELL_ATTR5_IMPLIED_TARGETING                              = 0x00000800, // TITLE Auto-target target of target (client only)
    SPELL_ATTR5_MELEE_CHAIN_TARGETING                          = 0x00001000, // TITLE Unknown attribute 12@Attr5 DESCRIPTION Cleave related?
    SPELL_ATTR5_SPELL_HASTE_AFFECTS_PERIODIC                   = 0x00002000, // TITLE Duration scales with Haste Rating
    SPELL_ATTR5_NOT_AVALIABLE_WHILE_CHARMED                    = 0x00004000, // TITLE Charmed units cannot cast this spell
    SPELL_ATTR5_TREAT_AS_AREA_EFFECT                           = 0x00008000, // TITLE Unknown attribute 15@Attr5 DESCRIPTION Related to multi-target spells?
    SPELL_ATTR5_AURA_AFFECTS_NOT_JUST_REQ_EQUIPPED_ITEM        = 0x00010000, // TITLE DESCRIPTION this allows spells with EquippedItemClass to affect spells from other items if the required item is equipped
    SPELL_ATTR5_ALLOW_WHILE_FLEEING                            = 0x00020000, // TITLE Usable while feared
    SPELL_ATTR5_ALLOW_WHILE_CONFUSED                           = 0x00040000, // TITLE Usable while confused
    SPELL_ATTR5_AI_DOESNT_FACE_TARGET                          = 0x00080000, // TITLE Do not auto-turn while casting
    SPELL_ATTR5_DO_NOT_ATTEMPT_A_PET_RESUMMON_WHEN_DISMOUNTING = 0x00100000, // TITLE Unknown attribute 20@Attr5
    SPELL_ATTR5_IGNORE_TARGET_REQUIREMENTS                     = 0x00200000, // TITLE Unknown attribute 21@Attr5
    SPELL_ATTR5_NOT_ON_TRIVIAL                                 = 0x00400000, // TITLE Unknown attribute 22@Attr5
    SPELL_ATTR5_NO_PARTIAL_RESISTS                             = 0x00800000, // TITLE Unknown attribute 23@Attr5
    SPELL_ATTR5_IGNORE_CASTER_REQUIREMENETS                    = 0x01000000, // TITLE Unknown attribute 24@Attr5
    SPELL_ATTR5_ALWAYS_LINE_OF_SIGHT                           = 0x02000000, // TITLE Unknown attribute 25@Attr5
    SPELL_ATTR5_ALWAYS_AOE_LINE_OF_SIGHT                       = 0x04000000, // TITLE Ignore line of sight checks
    SPELL_ATTR5_NO_CASTER_AURA_ICON                            = 0x08000000, // TITLE Don't show aura if self-cast (client only)
    SPELL_ATTR5_NO_TARGET_AURA_ICON                            = 0x10000000, // TITLE Don't show aura unless self-cast (client only)
    SPELL_ATTR5_AURA_UNIQUE_PER_CASTER                         = 0x20000000, // TITLE Unknown attribute 29@Attr5
    SPELL_ATTR5_ALWAYS_SHOW_GROUND_TEXTURE                     = 0x40000000, // TITLE Unknown attribute 30@Attr5
    SPELL_ATTR5_ADD_MELEE_HIT_RATING                           = 0x80000000  // TITLE Unknown attribute 31@Attr5 DESCRIPTION Forces nearby enemies to attack caster?
};

// EnumUtils: DESCRIBE THIS
enum SpellAttr6 : uint32
{
    SPELL_ATTR6_NO_COOLDOWN_ON_TOOLTIP                     = 0x00000001, // TITLE Don't display cooldown (client only)
    SPELL_ATTR6_DO_NOT_RESET_COOLDOWN_IN_ARENA             = 0x00000002, // TITLE Only usable in arena
    SPELL_ATTR6_NOT_AN_ATTACK                              = 0x00000004, // TITLE Ignore all preventing caster auras
    SPELL_ATTR6_CAN_ASSIST_IMMUNE_PC                       = 0x00000008, // TITLE Ignore immunity flags when assisting
    SPELL_ATTR6_IGNORE_FOR_MOD_TIME_RATE                   = 0x00000010, // TITLE Unknown attribute 4@Attr6
    SPELL_ATTR6_DO_NOT_CONSUME_RESOURCES                   = 0x00000020, // TITLE Don't consume proc charges
    SPELL_ATTR6_FLOATING_COMBAT_TEXT_ON_CAST               = 0x00000040, // TITLE Generate spell_cast event instead of aura_start (client only)
    SPELL_ATTR6_AURA_IS_WEAPON_PROC                        = 0x00000080, // TITLE Unknown attribute 7@Attr6
    SPELL_ATTR6_DO_NOT_CHAIN_TO_CROWD_CONTROLLED_TARGETS   = 0x00000100, // TITLE Do not implicitly target in CC DESCRIPTION Implicit targeting (chaining and area targeting) will not impact crowd controlled targets
    SPELL_ATTR6_ALLOW_ON_CHARMED_TARGETS                   = 0x00000200, // TITLE Unknown attribute 9@Attr6
    SPELL_ATTR6_NO_AURA_LOG                                = 0x00000400, // TITLE Can target possessed friends DESCRIPTION [NYI]
    SPELL_ATTR6_NOT_IN_RAID_INSTANCES                      = 0x00000800, // TITLE Unusable in raid instances
    SPELL_ATTR6_ALLOW_WHILE_RIDING_VEHICLE                 = 0x00001000, // TITLE Castable while caster is on vehicle
    SPELL_ATTR6_IGNORE_PHASE_SHIFT                         = 0x00002000, // TITLE Can target invisible units
    SPELL_ATTR6_AI_PRIMARY_RANGED_ATTACK                   = 0x00004000, // TITLE Unknown attribute 14@Attr6
    SPELL_ATTR6_NO_PUSHBACK                                = 0x00008000, // TITLE Not affected by pushback DESCRIPTION Casts/Channels will not affected by pushback
    SPELL_ATTR6_NO_JUMP_PATHING                            = 0x00010000, // TITLE Unknown attribute 16@Attr6
    SPELL_ATTR6_ALLOW_EQUIP_WHILE_CASTING                  = 0x00020000, // TITLE Unknown attribute 17@Attr6 DESCRIPTION Mount related?
    SPELL_ATTR6_ORIGINATE_FROM_CONTROLLER                  = 0x00040000, // TITLE Spell is cast by charmer DESCRIPTION Client will prevent casting if not possessed, charmer will be caster for all intents and purposes
    SPELL_ATTR6_DELAY_COMBAT_TIMER_DURING_CAST             = 0x00080000, // TITLE Unknown attribute 19@Attr6 DESCRIPTION only 47488, 50782
    SPELL_ATTR6_AURA_ICON_ONLY_FOR_CASTER                  = 0x00100000, // TITLE Only visible to caster (client only) (LIMIT 10)
    SPELL_ATTR6_SHOW_MECHANIC_AS_COMBAT_TEXT               = 0x00200000, // TITLE Client UI target effects (client only)
    SPELL_ATTR6_ABSORB_CANNOT_BE_IGNORED                   = 0x00400000, // TITLE Unknown attribute 22@Attr6 DESCRIPTION only 72054
    SPELL_ATTR6_TAPS_IMMEDIATELY                           = 0x00800000, // TITLE Unknown attribute 23@Attr6
    SPELL_ATTR6_CAN_TARGET_UNTARGETABLE                    = 0x01000000, // TITLE Can target untargetable units
    SPELL_ATTR6_DOESNT_RESET_SWING_TIMER_IF_INSTANT        = 0x02000000, // TITLE Do not reset swing timer if cast time is instant
    SPELL_ATTR6_VEHICLE_IMMUNITY_CATEGORY                  = 0x04000000, // TITLE Unknown attribute 26@Attr6 DESCRIPTION Player castable buff?
    SPELL_ATTR6_IGNORE_HEALTH_MODIFIERS                    = 0x08000000, // TITLE Limit applicable %healing modifiers DESCRIPTION This prevents certain healing modifiers from applying - see implementation if you really care about details
    SPELL_ATTR6_DO_NOT_SELECT_TARGET_WITH_INITIATES_COMBAT = 0x10000000, // TITLE Unknown attribute 28@Attr6 DESCRIPTION Death grip?
    SPELL_ATTR6_IGNORE_CASTER_DAMAGE_MODIFIERS             = 0x20000000, // TITLE Limit applicable %damage modifiers DESCRIPTION This prevents certain damage modifiers from applying - see implementation if you really care about details
    SPELL_ATTR6_DISABLE_TIED_EFFECT_POINTS                 = 0x40000000, // TITLE Unknown attribute 30@Attr6
    SPELL_ATTR6_NO_CATEGORY_COOLDOWN_MODS                  = 0x80000000  // TITLE Ignore cooldown modifiers for category cooldown
};

// EnumUtils: DESCRIBE THIS
enum SpellAttr7 : uint32
{
    SPELL_ATTR7_ALLOW_SPELL_REFLECTION                        = 0x00000001, // TITLE Unknown attribute 0@Attr7 DESCRIPTION Shaman's new spells (Call of the ...), Feign Death.
    SPELL_ATTR7_NO_TARGET_DURATION_MOD                        = 0x00000002, // TITLE Ignore duration modifiers
    SPELL_ATTR7_DISABLE_AURA_WHILE_DEAD                       = 0x00000004, // TITLE Reactivate at resurrect (client only)
    SPELL_ATTR7_DEBUG_SPELL                                   = 0x00000008, // TITLE Is cheat spell DESCRIPTION Cannot cast if caster doesn't have UnitFlag2 & UNIT_FLAG2_ALLOW_CHEAT_SPELLS
    SPELL_ATTR7_TREAT_AS_RAID_BUFF                            = 0x00000010, // TITLE Unknown attribute 4@Attr7 DESCRIPTION Soulstone related?
    SPELL_ATTR7_CAN_BE_MULTI_CAST                             = 0x00000020, // TITLE Summons player-owned totem
    SPELL_ATTR7_DONT_CAUSE_SPELL_PUSHBACK                     = 0x00000040, // TITLE Damage dealt by this does not cause spell pushback
    SPELL_ATTR7_PREPARE_FOR_VEHICLE_CONTROL_END               = 0x00000080, // TITLE Unknown attribute 7@Attr7 DESCRIPTION 66218 (Launch) spell.
    SPELL_ATTR7_HORDE_SPECIFIC_SPELL                          = 0x00000100, // TITLE Horde only
    SPELL_ATTR7_ALLIANCE_SPECIFIC_SPELL                       = 0x00000200, // TITLE Alliance only
    SPELL_ATTR7_DISPEL_REMOVES_CHARGES                        = 0x00000400, // TITLE Dispel/Spellsteal remove individual charges
    SPELL_ATTR7_CAN_CAUSE_INTERRUPT                           = 0x00000800, // TITLE Only interrupt non-player casting
    SPELL_ATTR7_CAN_CAUSE_SILENCE                             = 0x00001000, // TITLE Unused attribute 12@Attr7 DESCRIPTION Not set in 3.3.5a.
    SPELL_ATTR7_NO_UI_NOT_INTERRUPTIBLE                       = 0x00002000, // TITLE Unused attribute 13@Attr7 DESCRIPTION Not set in 3.3.5a.
    SPELL_ATTR7_RECAST_ON_RESUMMON                            = 0x00004000, // TITLE Unknown attribute 14@Attr7 DESCRIPTION Only 52150 (Raise Dead - Pet) spell.
    SPELL_ATTR7_RESET_SWING_TIMER_AT_SPELL_START              = 0x00008000, // TITLE Unknown attribute 15@Attr7 DESCRIPTION Exorcism - guaranteed crit vs families?
    SPELL_ATTR7_ONLY_IN_SPELLBOOK_UNTIL_LEARNED               = 0x00010000, // TITLE Can restore secondary power DESCRIPTION Only spells with this attribute can replenish a non-active power type
    SPELL_ATTR7_DO_NOT_LOG_PVP_KILL                           = 0x00020000, // TITLE Unknown attribute 17@Attr7 DESCRIPTION Only 27965 (Suicide) spell.
    SPELL_ATTR7_ATTACK_ON_CHARGE_TO_UNIT                      = 0x00040000, // TITLE Has charge effect
    SPELL_ATTR7_REPORT_SPELL_FAILURE_TO_UNIT_TARGET           = 0x00080000, // TITLE Is zone teleport
    SPELL_ATTR7_NO_CLIENT_FAIL_WHILE_STUNNED_FLEEING_CONFUSED = 0x00100000, // TITLE Unknown attribute 20@Attr7 DESCRIPTION Invulnerability related?
    SPELL_ATTR7_RETAIN_COOLDOWN_THROUGH_LOAD                  = 0x00200000, // TITLE Unused attribute 21@Attr7 DESCRPIPTION Not set in 3.3.5a
    SPELL_ATTR7_IGNORES_COLD_WEATHER_FLYING_REQUIREMENT       = 0x00400000, // TITLE Ignore cold weather flying restriction DESCRIPTION Set for loaner mounts, allows them to be used despite lacking required flight skill
    SPELL_ATTR7_NO_ATTACK_DODGE                               = 0x00800000, // TITLE Spell cannot be dodged 23@Attr7 DESCRIPTION Motivate, Mutilate, Shattering Throw
    SPELL_ATTR7_NO_ATTACK_PARRY                               = 0x01000000, // TITLE Spell cannot be parried 24@Attr7 DESCRIPTION Motivate, Mutilate, Perform Speech, Shattering Throw
    SPELL_ATTR7_NO_ATTACK_MISS                                = 0x02000000, // TITLE Spell cannot be missed 25@Attr7
    SPELL_ATTR7_TREAT_AS_NPC_AOE                              = 0x04000000, // TITLE Treat as NPC AoE
    SPELL_ATTR7_BYPASS_NO_RESURRECTION_AURA                   = 0x08000000, // TITLE Bypasses the prevent resurrection aura
    SPELL_ATTR7_DO_NOT_COUNT_FOR_PVP_SCOREBOARD               = 0x10000000, // TITLE Consolidate in raid buff frame (client only)
    SPELL_ATTR7_REFLECTION_ONLY_DEFENDS                       = 0x20000000, // TITLE Unknown attribute 29@Attr7 DESCRIPTION only 69028, 71237
    SPELL_ATTR7_CAN_PROC_FROM_SUPPRESSED_TARGET_PROCS         = 0x40000000, // TITLE Unknown attribute 30@Attr7 DESCRIPTION Burning Determination, Divine Sacrifice, Earth Shield, Prayer of Mending
    SPELL_ATTR7_ALWAYS_CAST_LOG                               = 0x80000000  // TITLE Client indicator (client only)
};

#define MAX_TALENT_SPECS        2
#define MAX_GLYPH_SLOT_INDEX    6

// Custom values
enum SpellClickUserTypes
{
    SPELL_CLICK_USER_ANY = 0,
    SPELL_CLICK_USER_FRIEND = 1,
    SPELL_CLICK_USER_RAID = 2,
    SPELL_CLICK_USER_PARTY = 3,
    SPELL_CLICK_USER_MAX = 4
};

enum SpellClickCastFlags
{
    NPC_CLICK_CAST_CASTER_CLICKER       = 0x01,
    NPC_CLICK_CAST_TARGET_CLICKER       = 0x02,
    NPC_CLICK_CAST_ORIG_CASTER_OWNER    = 0x04,
};

enum SheathTypes
{
    SHEATHETYPE_NONE                   = 0,
    SHEATHETYPE_MAINHAND               = 1,
    SHEATHETYPE_OFFHAND                = 2,
    SHEATHETYPE_LARGEWEAPONLEFT        = 3,
    SHEATHETYPE_LARGEWEAPONRIGHT       = 4,
    SHEATHETYPE_HIPWEAPONLEFT          = 5,
    SHEATHETYPE_HIPWEAPONRIGHT         = 6,
    SHEATHETYPE_SHIELD                 = 7
};

#define MAX_SHEATHETYPE                  8

enum CharacterSlot
{
    SLOT_HEAD                          = 0,
    SLOT_NECK                          = 1,
    SLOT_SHOULDERS                     = 2,
    SLOT_SHIRT                         = 3,
    SLOT_CHEST                         = 4,
    SLOT_WAIST                         = 5,
    SLOT_LEGS                          = 6,
    SLOT_FEET                          = 7,
    SLOT_WRISTS                        = 8,
    SLOT_HANDS                         = 9,
    SLOT_FINGER1                       = 10,
    SLOT_FINGER2                       = 11,
    SLOT_TRINKET1                      = 12,
    SLOT_TRINKET2                      = 13,
    SLOT_BACK                          = 14,
    SLOT_MAIN_HAND                     = 15,
    SLOT_OFF_HAND                      = 16,
    SLOT_RANGED                        = 17,
    SLOT_TABARD                        = 18,
    SLOT_EMPTY                         = 19
};

enum Language
{
    LANG_UNIVERSAL      = 0,
    LANG_ORCISH         = 1,
    LANG_DARNASSIAN     = 2,
    LANG_TAURAHE        = 3,
    LANG_DWARVISH       = 6,
    LANG_COMMON         = 7,
    LANG_DEMONIC        = 8,
    LANG_TITAN          = 9,
    LANG_THALASSIAN     = 10,
    LANG_DRACONIC       = 11,
    LANG_KALIMAG        = 12,
    LANG_GNOMISH        = 13,
    LANG_TROLL          = 14,
    LANG_GUTTERSPEAK    = 33,
    LANG_DRAENEI        = 35,
    LANG_ZOMBIE         = 36,
    LANG_GNOMISH_BINARY = 37,
    LANG_GOBLIN_BINARY  = 38,
    LANG_ADDON          = 0xFFFFFFFF                        // used by addons, in 2.4.0 not exist, replaced by messagetype?
};

#define LANGUAGES_COUNT   19

enum TeamId : uint8
{
    TEAM_ALLIANCE = 0,
    TEAM_HORDE,
    TEAM_NEUTRAL,
};

enum Team
{
    HORDE               = 67,
    ALLIANCE            = 469,
    //TEAM_STEAMWHEEDLE_CARTEL = 169,                       // not used in code
    //TEAM_ALLIANCE_FORCES     = 891,
    //TEAM_HORDE_FORCES        = 892,
    //TEAM_SANCTUARY           = 936,
    //TEAM_OUTLAND             = 980,
    TEAM_OTHER               = 0,                         // if ReputationListId > 0 && Flags != FACTION_FLAG_TEAM_HEADER
};

enum SpellEffects
{
    SPELL_EFFECT_INSTAKILL                          = 1,
    SPELL_EFFECT_SCHOOL_DAMAGE                      = 2,
    SPELL_EFFECT_DUMMY                              = 3,
    SPELL_EFFECT_PORTAL_TELEPORT                    = 4,
    SPELL_EFFECT_TELEPORT_UNITS                     = 5,
    SPELL_EFFECT_APPLY_AURA                         = 6,
    SPELL_EFFECT_ENVIRONMENTAL_DAMAGE               = 7,
    SPELL_EFFECT_POWER_DRAIN                        = 8,
    SPELL_EFFECT_HEALTH_LEECH                       = 9,
    SPELL_EFFECT_HEAL                               = 10,
    SPELL_EFFECT_BIND                               = 11,
    SPELL_EFFECT_PORTAL                             = 12,
    SPELL_EFFECT_RITUAL_BASE                        = 13,
    SPELL_EFFECT_RITUAL_SPECIALIZE                  = 14,
    SPELL_EFFECT_RITUAL_ACTIVATE_PORTAL             = 15,
    SPELL_EFFECT_QUEST_COMPLETE                     = 16,
    SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL             = 17,
    SPELL_EFFECT_RESURRECT                          = 18,
    SPELL_EFFECT_ADD_EXTRA_ATTACKS                  = 19,
    SPELL_EFFECT_DODGE                              = 20,
    SPELL_EFFECT_EVADE                              = 21,
    SPELL_EFFECT_PARRY                              = 22,
    SPELL_EFFECT_BLOCK                              = 23,
    SPELL_EFFECT_CREATE_ITEM                        = 24,
    SPELL_EFFECT_WEAPON                             = 25,
    SPELL_EFFECT_DEFENSE                            = 26,
    SPELL_EFFECT_PERSISTENT_AREA_AURA               = 27,
    SPELL_EFFECT_SUMMON                             = 28,
    SPELL_EFFECT_LEAP                               = 29,
    SPELL_EFFECT_ENERGIZE                           = 30,
    SPELL_EFFECT_WEAPON_PERCENT_DAMAGE              = 31,
    SPELL_EFFECT_TRIGGER_MISSILE                    = 32,
    SPELL_EFFECT_OPEN_LOCK                          = 33,
    SPELL_EFFECT_SUMMON_CHANGE_ITEM                 = 34,
    SPELL_EFFECT_APPLY_AREA_AURA_PARTY              = 35,
    SPELL_EFFECT_LEARN_SPELL                        = 36,
    SPELL_EFFECT_SPELL_DEFENSE                      = 37,
    SPELL_EFFECT_DISPEL                             = 38,
    SPELL_EFFECT_LANGUAGE                           = 39,
    SPELL_EFFECT_DUAL_WIELD                         = 40,
    SPELL_EFFECT_JUMP                               = 41,
    SPELL_EFFECT_JUMP_DEST                          = 42,
    SPELL_EFFECT_TELEPORT_UNITS_FACE_CASTER         = 43,
    SPELL_EFFECT_SKILL_STEP                         = 44,
    SPELL_EFFECT_ADD_HONOR                          = 45,
    SPELL_EFFECT_SPAWN                              = 46,
    SPELL_EFFECT_TRADE_SKILL                        = 47,
    SPELL_EFFECT_STEALTH                            = 48,
    SPELL_EFFECT_DETECT                             = 49,
    SPELL_EFFECT_TRANS_DOOR                         = 50,
    SPELL_EFFECT_FORCE_CRITICAL_HIT                 = 51,
    SPELL_EFFECT_GUARANTEE_HIT                      = 52,
    SPELL_EFFECT_ENCHANT_ITEM                       = 53,
    SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY             = 54,
    SPELL_EFFECT_TAMECREATURE                       = 55,
    SPELL_EFFECT_SUMMON_PET                         = 56,
    SPELL_EFFECT_LEARN_PET_SPELL                    = 57,
    SPELL_EFFECT_WEAPON_DAMAGE                      = 58,
    SPELL_EFFECT_CREATE_RANDOM_ITEM                 = 59,
    SPELL_EFFECT_PROFICIENCY                        = 60,
    SPELL_EFFECT_SEND_EVENT                         = 61,
    SPELL_EFFECT_POWER_BURN                         = 62,
    SPELL_EFFECT_THREAT                             = 63,
    SPELL_EFFECT_TRIGGER_SPELL                      = 64,
    SPELL_EFFECT_APPLY_AREA_AURA_RAID               = 65,
    SPELL_EFFECT_CREATE_MANA_GEM                    = 66,
    SPELL_EFFECT_HEAL_MAX_HEALTH                    = 67,
    SPELL_EFFECT_INTERRUPT_CAST                     = 68,
    SPELL_EFFECT_DISTRACT                           = 69,
    SPELL_EFFECT_PULL                               = 70,
    SPELL_EFFECT_PICKPOCKET                         = 71,
    SPELL_EFFECT_ADD_FARSIGHT                       = 72,
    SPELL_EFFECT_UNTRAIN_TALENTS                    = 73,
    SPELL_EFFECT_APPLY_GLYPH                        = 74,
    SPELL_EFFECT_HEAL_MECHANICAL                    = 75,
    SPELL_EFFECT_SUMMON_OBJECT_WILD                 = 76,
    SPELL_EFFECT_SCRIPT_EFFECT                      = 77,
    SPELL_EFFECT_ATTACK                             = 78,
    SPELL_EFFECT_SANCTUARY                          = 79,
    SPELL_EFFECT_ADD_COMBO_POINTS                   = 80,
    SPELL_EFFECT_CREATE_HOUSE                       = 81,
    SPELL_EFFECT_BIND_SIGHT                         = 82,
    SPELL_EFFECT_DUEL                               = 83,
    SPELL_EFFECT_STUCK                              = 84,
    SPELL_EFFECT_SUMMON_PLAYER                      = 85,
    SPELL_EFFECT_ACTIVATE_OBJECT                    = 86,
    SPELL_EFFECT_GAMEOBJECT_DAMAGE                  = 87,
    SPELL_EFFECT_GAMEOBJECT_REPAIR                  = 88,
    SPELL_EFFECT_GAMEOBJECT_SET_DESTRUCTION_STATE   = 89,
    SPELL_EFFECT_KILL_CREDIT                        = 90,
    SPELL_EFFECT_THREAT_ALL                         = 91,
    SPELL_EFFECT_ENCHANT_HELD_ITEM                  = 92,
    SPELL_EFFECT_FORCE_DESELECT                     = 93,
    SPELL_EFFECT_SELF_RESURRECT                     = 94,
    SPELL_EFFECT_SKINNING                           = 95,
    SPELL_EFFECT_CHARGE                             = 96,
    SPELL_EFFECT_CAST_BUTTON                        = 97,
    SPELL_EFFECT_KNOCK_BACK                         = 98,
    SPELL_EFFECT_DISENCHANT                         = 99,
    SPELL_EFFECT_INEBRIATE                          = 100,
    SPELL_EFFECT_FEED_PET                           = 101,
    SPELL_EFFECT_DISMISS_PET                        = 102,
    SPELL_EFFECT_REPUTATION                         = 103,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT1                = 104,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT2                = 105,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT3                = 106,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT4                = 107,
    SPELL_EFFECT_DISPEL_MECHANIC                    = 108,
    SPELL_EFFECT_RESURRECT_PET                      = 109,
    SPELL_EFFECT_DESTROY_ALL_TOTEMS                 = 110,
    SPELL_EFFECT_DURABILITY_DAMAGE                  = 111,
    SPELL_EFFECT_112                                = 112,
    SPELL_EFFECT_RESURRECT_NEW                      = 113,
    SPELL_EFFECT_ATTACK_ME                          = 114,
    SPELL_EFFECT_DURABILITY_DAMAGE_PCT              = 115,
    SPELL_EFFECT_SKIN_PLAYER_CORPSE                 = 116,
    SPELL_EFFECT_SPIRIT_HEAL                        = 117,
    SPELL_EFFECT_SKILL                              = 118,
    SPELL_EFFECT_APPLY_AREA_AURA_PET                = 119,
    SPELL_EFFECT_TELEPORT_GRAVEYARD                 = 120,
    SPELL_EFFECT_NORMALIZED_WEAPON_DMG              = 121,
    SPELL_EFFECT_122                                = 122,
    SPELL_EFFECT_SEND_TAXI                          = 123,
    SPELL_EFFECT_PULL_TOWARDS                       = 124,
    SPELL_EFFECT_MODIFY_THREAT_PERCENT              = 125,
    SPELL_EFFECT_STEAL_BENEFICIAL_BUFF              = 126,
    SPELL_EFFECT_PROSPECTING                        = 127,
    SPELL_EFFECT_APPLY_AREA_AURA_FRIEND             = 128,
    SPELL_EFFECT_APPLY_AREA_AURA_ENEMY              = 129,
    SPELL_EFFECT_REDIRECT_THREAT                    = 130,
    SPELL_EFFECT_PLAY_SOUND                         = 131,
    SPELL_EFFECT_PLAY_MUSIC                         = 132,
    SPELL_EFFECT_UNLEARN_SPECIALIZATION             = 133,
    SPELL_EFFECT_KILL_CREDIT2                       = 134,
    SPELL_EFFECT_CALL_PET                           = 135,
    SPELL_EFFECT_HEAL_PCT                           = 136,
    SPELL_EFFECT_ENERGIZE_PCT                       = 137,
    SPELL_EFFECT_LEAP_BACK                          = 138,
    SPELL_EFFECT_CLEAR_QUEST                        = 139,
    SPELL_EFFECT_FORCE_CAST                         = 140,
    SPELL_EFFECT_FORCE_CAST_WITH_VALUE              = 141,
    SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE           = 142,
    SPELL_EFFECT_APPLY_AREA_AURA_OWNER              = 143,
    SPELL_EFFECT_KNOCK_BACK_DEST                    = 144,
    SPELL_EFFECT_PULL_TOWARDS_DEST                  = 145,
    SPELL_EFFECT_ACTIVATE_RUNE                      = 146,
    SPELL_EFFECT_QUEST_FAIL                         = 147,
    SPELL_EFFECT_TRIGGER_MISSILE_SPELL_WITH_VALUE   = 148,
    SPELL_EFFECT_CHARGE_DEST                        = 149,
    SPELL_EFFECT_QUEST_START                        = 150,
    SPELL_EFFECT_TRIGGER_SPELL_2                    = 151,
    SPELL_EFFECT_SUMMON_RAF_FRIEND                  = 152,
    SPELL_EFFECT_CREATE_TAMED_PET                   = 153,
    SPELL_EFFECT_DISCOVER_TAXI                      = 154,
    SPELL_EFFECT_TITAN_GRIP                         = 155,
    SPELL_EFFECT_ENCHANT_ITEM_PRISMATIC             = 156,
    SPELL_EFFECT_CREATE_ITEM_2                      = 157,
    SPELL_EFFECT_MILLING                            = 158,
    SPELL_EFFECT_ALLOW_RENAME_PET                   = 159,
    SPELL_EFFECT_FORCE_CAST_2                       = 160,
    SPELL_EFFECT_TALENT_SPEC_COUNT                  = 161,
    SPELL_EFFECT_TALENT_SPEC_SELECT                 = 162,
    SPELL_EFFECT_163                                = 163,
    SPELL_EFFECT_REMOVE_AURA                        = 164,
    TOTAL_SPELL_EFFECTS                             = 165
};

// EnumUtils: DESCRIBE THIS
enum SpellCastResult : uint8
{
    SPELL_FAILED_SUCCESS = 0,
    SPELL_FAILED_AFFECTING_COMBAT = 1,
    SPELL_FAILED_ALREADY_AT_FULL_HEALTH = 2,
    SPELL_FAILED_ALREADY_AT_FULL_MANA = 3,
    SPELL_FAILED_ALREADY_AT_FULL_POWER = 4,
    SPELL_FAILED_ALREADY_BEING_TAMED = 5,
    SPELL_FAILED_ALREADY_HAVE_CHARM = 6,
    SPELL_FAILED_ALREADY_HAVE_SUMMON = 7,
    SPELL_FAILED_ALREADY_OPEN = 8,
    SPELL_FAILED_AURA_BOUNCED = 9,
    SPELL_FAILED_AUTOTRACK_INTERRUPTED = 10,
    SPELL_FAILED_BAD_IMPLICIT_TARGETS = 11,
    SPELL_FAILED_BAD_TARGETS = 12,
    SPELL_FAILED_CANT_BE_CHARMED = 13,
    SPELL_FAILED_CANT_BE_DISENCHANTED = 14,
    SPELL_FAILED_CANT_BE_DISENCHANTED_SKILL = 15,
    SPELL_FAILED_CANT_BE_MILLED = 16,
    SPELL_FAILED_CANT_BE_PROSPECTED = 17,
    SPELL_FAILED_CANT_CAST_ON_TAPPED = 18,
    SPELL_FAILED_CANT_DUEL_WHILE_INVISIBLE = 19,
    SPELL_FAILED_CANT_DUEL_WHILE_STEALTHED = 20,
    SPELL_FAILED_CANT_STEALTH = 21,
    SPELL_FAILED_CASTER_AURASTATE = 22,
    SPELL_FAILED_CASTER_DEAD = 23,
    SPELL_FAILED_CHARMED = 24,
    SPELL_FAILED_CHEST_IN_USE = 25,
    SPELL_FAILED_CONFUSED = 26,
    SPELL_FAILED_DONT_REPORT = 27,
    SPELL_FAILED_EQUIPPED_ITEM = 28,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS = 29,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS_MAINHAND = 30,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS_OFFHAND = 31,
    SPELL_FAILED_ERROR = 32,
    SPELL_FAILED_FIZZLE = 33,
    SPELL_FAILED_FLEEING = 34,
    SPELL_FAILED_FOOD_LOWLEVEL = 35,
    SPELL_FAILED_HIGHLEVEL = 36,
    SPELL_FAILED_HUNGER_SATIATED = 37,
    SPELL_FAILED_IMMUNE = 38,
    SPELL_FAILED_INCORRECT_AREA = 39,
    SPELL_FAILED_INTERRUPTED = 40,
    SPELL_FAILED_INTERRUPTED_COMBAT = 41,
    SPELL_FAILED_ITEM_ALREADY_ENCHANTED = 42,
    SPELL_FAILED_ITEM_GONE = 43,
    SPELL_FAILED_ITEM_NOT_FOUND = 44,
    SPELL_FAILED_ITEM_NOT_READY = 45,
    SPELL_FAILED_LEVEL_REQUIREMENT = 46,
    SPELL_FAILED_LINE_OF_SIGHT = 47,
    SPELL_FAILED_LOWLEVEL = 48,
    SPELL_FAILED_LOW_CASTLEVEL = 49,
    SPELL_FAILED_MAINHAND_EMPTY = 50,
    SPELL_FAILED_MOVING = 51,
    SPELL_FAILED_NEED_AMMO = 52,
    SPELL_FAILED_NEED_AMMO_POUCH = 53,
    SPELL_FAILED_NEED_EXOTIC_AMMO = 54,
    SPELL_FAILED_NEED_MORE_ITEMS = 55,
    SPELL_FAILED_NOPATH = 56,
    SPELL_FAILED_NOT_BEHIND = 57,
    SPELL_FAILED_NOT_FISHABLE = 58,
    SPELL_FAILED_NOT_FLYING = 59,
    SPELL_FAILED_NOT_HERE = 60,
    SPELL_FAILED_NOT_INFRONT = 61,
    SPELL_FAILED_NOT_IN_CONTROL = 62,
    SPELL_FAILED_NOT_KNOWN = 63,
    SPELL_FAILED_NOT_MOUNTED = 64,
    SPELL_FAILED_NOT_ON_TAXI = 65,
    SPELL_FAILED_NOT_ON_TRANSPORT = 66,
    SPELL_FAILED_NOT_READY = 67,
    SPELL_FAILED_NOT_SHAPESHIFT = 68,
    SPELL_FAILED_NOT_STANDING = 69,
    SPELL_FAILED_NOT_TRADEABLE = 70,
    SPELL_FAILED_NOT_TRADING = 71,
    SPELL_FAILED_NOT_UNSHEATHED = 72,
    SPELL_FAILED_NOT_WHILE_GHOST = 73,
    SPELL_FAILED_NOT_WHILE_LOOTING = 74,
    SPELL_FAILED_NO_AMMO = 75,
    SPELL_FAILED_NO_CHARGES_REMAIN = 76,
    SPELL_FAILED_NO_CHAMPION = 77,
    SPELL_FAILED_NO_COMBO_POINTS = 78,
    SPELL_FAILED_NO_DUELING = 79,
    SPELL_FAILED_NO_ENDURANCE = 80,
    SPELL_FAILED_NO_FISH = 81,
    SPELL_FAILED_NO_ITEMS_WHILE_SHAPESHIFTED = 82,
    SPELL_FAILED_NO_MOUNTS_ALLOWED = 83,
    SPELL_FAILED_NO_PET = 84,
    SPELL_FAILED_NO_POWER = 85,
    SPELL_FAILED_NOTHING_TO_DISPEL = 86,
    SPELL_FAILED_NOTHING_TO_STEAL = 87,
    SPELL_FAILED_ONLY_ABOVEWATER = 88,
    SPELL_FAILED_ONLY_DAYTIME = 89,
    SPELL_FAILED_ONLY_INDOORS = 90,
    SPELL_FAILED_ONLY_MOUNTED = 91,
    SPELL_FAILED_ONLY_NIGHTTIME = 92,
    SPELL_FAILED_ONLY_OUTDOORS = 93,
    SPELL_FAILED_ONLY_SHAPESHIFT = 94,
    SPELL_FAILED_ONLY_STEALTHED = 95,
    SPELL_FAILED_ONLY_UNDERWATER = 96,
    SPELL_FAILED_OUT_OF_RANGE = 97,
    SPELL_FAILED_PACIFIED = 98,
    SPELL_FAILED_POSSESSED = 99,
    SPELL_FAILED_REAGENTS = 100,
    SPELL_FAILED_REQUIRES_AREA = 101,
    SPELL_FAILED_REQUIRES_SPELL_FOCUS = 102,
    SPELL_FAILED_ROOTED = 103,
    SPELL_FAILED_SILENCED = 104,
    SPELL_FAILED_SPELL_IN_PROGRESS = 105,
    SPELL_FAILED_SPELL_LEARNED = 106,
    SPELL_FAILED_SPELL_UNAVAILABLE = 107,
    SPELL_FAILED_STUNNED = 108,
    SPELL_FAILED_TARGETS_DEAD = 109,
    SPELL_FAILED_TARGET_AFFECTING_COMBAT = 110,
    SPELL_FAILED_TARGET_AURASTATE = 111,
    SPELL_FAILED_TARGET_DUELING = 112,
    SPELL_FAILED_TARGET_ENEMY = 113,
    SPELL_FAILED_TARGET_ENRAGED = 114,
    SPELL_FAILED_TARGET_FRIENDLY = 115,
    SPELL_FAILED_TARGET_IN_COMBAT = 116,
    SPELL_FAILED_TARGET_IS_PLAYER = 117,
    SPELL_FAILED_TARGET_IS_PLAYER_CONTROLLED = 118,
    SPELL_FAILED_TARGET_NOT_DEAD = 119,
    SPELL_FAILED_TARGET_NOT_IN_PARTY = 120,
    SPELL_FAILED_TARGET_NOT_LOOTED = 121,
    SPELL_FAILED_TARGET_NOT_PLAYER = 122,
    SPELL_FAILED_TARGET_NO_POCKETS = 123,
    SPELL_FAILED_TARGET_NO_WEAPONS = 124,
    SPELL_FAILED_TARGET_NO_RANGED_WEAPONS = 125,
    SPELL_FAILED_TARGET_UNSKINNABLE = 126,
    SPELL_FAILED_THIRST_SATIATED = 127,
    SPELL_FAILED_TOO_CLOSE = 128,
    SPELL_FAILED_TOO_MANY_OF_ITEM = 129,
    SPELL_FAILED_TOTEM_CATEGORY = 130,
    SPELL_FAILED_TOTEMS = 131,
    SPELL_FAILED_TRY_AGAIN = 132,
    SPELL_FAILED_UNIT_NOT_BEHIND = 133,
    SPELL_FAILED_UNIT_NOT_INFRONT = 134,
    SPELL_FAILED_WRONG_PET_FOOD = 135,
    SPELL_FAILED_NOT_WHILE_FATIGUED = 136,
    SPELL_FAILED_TARGET_NOT_IN_INSTANCE = 137,
    SPELL_FAILED_NOT_WHILE_TRADING = 138,
    SPELL_FAILED_TARGET_NOT_IN_RAID = 139,
    SPELL_FAILED_TARGET_FREEFORALL = 140,
    SPELL_FAILED_NO_EDIBLE_CORPSES = 141,
    SPELL_FAILED_ONLY_BATTLEGROUNDS = 142,
    SPELL_FAILED_TARGET_NOT_GHOST = 143,
    SPELL_FAILED_TRANSFORM_UNUSABLE = 144,
    SPELL_FAILED_WRONG_WEATHER = 145,
    SPELL_FAILED_DAMAGE_IMMUNE = 146,
    SPELL_FAILED_PREVENTED_BY_MECHANIC = 147,
    SPELL_FAILED_PLAY_TIME = 148,
    SPELL_FAILED_REPUTATION = 149,
    SPELL_FAILED_MIN_SKILL = 150,
    SPELL_FAILED_NOT_IN_ARENA = 151,
    SPELL_FAILED_NOT_ON_SHAPESHIFT = 152,
    SPELL_FAILED_NOT_ON_STEALTHED = 153,
    SPELL_FAILED_NOT_ON_DAMAGE_IMMUNE = 154,
    SPELL_FAILED_NOT_ON_MOUNTED = 155,
    SPELL_FAILED_TOO_SHALLOW = 156,
    SPELL_FAILED_TARGET_NOT_IN_SANCTUARY = 157,
    SPELL_FAILED_TARGET_IS_TRIVIAL = 158,
    SPELL_FAILED_BM_OR_INVISGOD = 159,
    SPELL_FAILED_EXPERT_RIDING_REQUIREMENT = 160,
    SPELL_FAILED_ARTISAN_RIDING_REQUIREMENT = 161,
    SPELL_FAILED_NOT_IDLE = 162,
    SPELL_FAILED_NOT_INACTIVE = 163,
    SPELL_FAILED_PARTIAL_PLAYTIME = 164,
    SPELL_FAILED_NO_PLAYTIME = 165,
    SPELL_FAILED_NOT_IN_BATTLEGROUND = 166,
    SPELL_FAILED_NOT_IN_RAID_INSTANCE = 167,
    SPELL_FAILED_ONLY_IN_ARENA = 168,
    SPELL_FAILED_TARGET_LOCKED_TO_RAID_INSTANCE = 169,
    SPELL_FAILED_ON_USE_ENCHANT = 170,
    SPELL_FAILED_NOT_ON_GROUND = 171,
    SPELL_FAILED_CUSTOM_ERROR = 172,
    SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW = 173,
    SPELL_FAILED_TOO_MANY_SOCKETS = 174,
    SPELL_FAILED_INVALID_GLYPH = 175,
    SPELL_FAILED_UNIQUE_GLYPH = 176,
    SPELL_FAILED_GLYPH_SOCKET_LOCKED = 177,
    SPELL_FAILED_NO_VALID_TARGETS = 178,
    SPELL_FAILED_ITEM_AT_MAX_CHARGES = 179,
    SPELL_FAILED_NOT_IN_BARBERSHOP = 180,
    SPELL_FAILED_FISHING_TOO_LOW = 181,
    SPELL_FAILED_ITEM_ENCHANT_TRADE_WINDOW = 182,
    SPELL_FAILED_SUMMON_PENDING = 183,
    SPELL_FAILED_MAX_SOCKETS = 184,
    SPELL_FAILED_PET_CAN_RENAME = 185,
    SPELL_FAILED_TARGET_CANNOT_BE_RESURRECTED = 186,
    SPELL_FAILED_UNKNOWN = 187, // actually doesn't exist in client

    SPELL_CAST_OK = 255 // custom value, must not be sent to client
};

enum SpellCustomErrors
{
    SPELL_CUSTOM_ERROR_NONE                             =  0,
    SPELL_CUSTOM_ERROR_CUSTOM_MSG                       =  1, // Something bad happened, and we want to display a custom message!
    SPELL_CUSTOM_ERROR_ALEX_BROKE_QUEST                 =  2, // Alex broke your quest! Thank him later!
    SPELL_CUSTOM_ERROR_NEED_HELPLESS_VILLAGER           =  3, // This spell may only be used on Helpless Wintergarde Villagers that have not been rescued.
    SPELL_CUSTOM_ERROR_NEED_WARSONG_DISGUISE            =  4, // Requires that you be wearing the Warsong Orc Disguise.
    SPELL_CUSTOM_ERROR_REQUIRES_PLAGUE_WAGON            =  5, // You must be closer to a plague wagon in order to drop off your 7th Legion Siege Engineer.
    SPELL_CUSTOM_ERROR_CANT_TARGET_FRIENDLY_NONPARTY    =  6, // You cannot target friendly units outside your party.
    SPELL_CUSTOM_ERROR_NEED_CHILL_NYMPH                 =  7, // You must target a weakened chill nymph.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_ENKILAH               =  8, // The Imbued Scourge Shroud will only work when equipped in the Temple City of En'kilah.
    SPELL_CUSTOM_ERROR_REQUIRES_CORPSE_DUST             =  9, // Requires Corpse Dust
    SPELL_CUSTOM_ERROR_CANT_SUMMON_GARGOYLE             = 10, // You cannot summon another gargoyle yet.
    SPELL_CUSTOM_ERROR_NEED_CORPSE_DUST_IF_NO_TARGET    = 11, // Requires Corpse Dust if the target is not dead and humanoid.
    SPELL_CUSTOM_ERROR_MUST_BE_AT_SHATTERHORN           = 12, // Can only be placed near Shatterhorn
    SPELL_CUSTOM_ERROR_MUST_TARGET_PROTO_DRAKE_EGG      = 13, // You must first select a Proto-Drake Egg.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_TREE            = 14, // You must be close to a marked tree.
    SPELL_CUSTOM_ERROR_MUST_TARGET_TURKEY               = 15, // You must target a Fjord Turkey.
    SPELL_CUSTOM_ERROR_MUST_TARGET_HAWK                 = 16, // You must target a Fjord Hawk.
    SPELL_CUSTOM_ERROR_TOO_FAR_FROM_BOUY                = 17, // You are too far from the bouy.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_OIL_SLICK       = 18, // Must be used near an oil slick.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_BOUY            = 19, // You must be closer to the buoy!
    SPELL_CUSTOM_ERROR_WYRMREST_VANQUISHER              = 20, // You may only call for the aid of a Wyrmrest Vanquisher in Wyrmrest Temple, The Dragon Wastes, Galakrond's Rest or The Wicked Coil.
    SPELL_CUSTOM_ERROR_MUST_TARGET_ICE_HEART_JORMUNGAR  = 21, // That can only be used on a Ice Heart Jormungar Spawn.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_SINKHOLE        = 22, // You must be closer to a sinkhole to use your map.
    SPELL_CUSTOM_ERROR_REQUIRES_HAROLD_LANE             = 23, // You may only call down a stampede on Harold Lane.
    SPELL_CUSTOM_ERROR_REQUIRES_GAMMOTH_MAGNATAUR       = 24, // You may only use the Pouch of Crushed Bloodspore on Gammothra or other magnataur in the Bloodspore Plains and Gammoth.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_RESURRECTION_CHAMBER  = 25, // Requires the magmawyrm resurrection chamber in the back of the Maw of Neltharion.
    SPELL_CUSTOM_ERROR_CANT_CALL_WINTERGARDE_HERE       = 26, // You may only call down a Wintergarde Gryphon in Wintergarde Keep or the Carrion Fields.
    SPELL_CUSTOM_ERROR_MUST_TARGET_WILHELM              = 27, // What are you doing? Only aim that thing at Wilhelm!
    SPELL_CUSTOM_ERROR_NOT_ENOUGH_HEALTH                = 28, // Not enough health!
    SPELL_CUSTOM_ERROR_NO_NEARBY_CORPSES                = 29, // There are no nearby corpses to use
    SPELL_CUSTOM_ERROR_TOO_MANY_GHOULS                  = 30, // You've created enough ghouls. Return to Gothik the Harvester at Death's Breach.
    SPELL_CUSTOM_ERROR_GO_FURTHER_FROM_SUNDERED_SHARD   = 31, // Your companion does not want to come here.  Go further from the Sundered Shard.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_CAT_FORM              = 32, // Must be in Cat Form
    SPELL_CUSTOM_ERROR_MUST_BE_DEATH_KNIGHT             = 33, // Only Death Knights may enter Ebon Hold.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_FERAL_FORM            = 34, // Must be in Cat Form, Bear Form, or Dire Bear Form
    SPELL_CUSTOM_ERROR_MUST_BE_NEAR_HELPLESS_VILLAGER   = 35, // You must be within range of a Helpless Wintergarde Villager.
    SPELL_CUSTOM_ERROR_CANT_TARGET_ELEMENTAL_MECHANICAL = 36, // You cannot target an elemental or mechanical corpse.
    SPELL_CUSTOM_ERROR_MUST_HAVE_USED_DALARAN_CRYSTAL   = 37, // This teleport crystal cannot be used until the teleport crystal in Dalaran has been used at least once.
    SPELL_CUSTOM_ERROR_YOU_ALREADY_HOLD_SOMETHING       = 38, // You are already holding something in your hand. You must throw the creature in your hand before picking up another.
    SPELL_CUSTOM_ERROR_YOU_DONT_HOLD_ANYTHING           = 39, // You don't have anything to throw! Find a Vargul and use Gymer Grab to pick one up!
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_VALDURAN        = 40, // Bouldercrag's War Horn can only be used within 10 yards of Valduran the Stormborn.
    SPELL_CUSTOM_ERROR_NO_PASSENGER                     = 41, // You are not carrying a passenger. There is nobody to drop off.
    SPELL_CUSTOM_ERROR_CANT_BUILD_MORE_VEHICLES         = 42, // You cannot build any more siege vehicles.
    SPELL_CUSTOM_ERROR_ALREADY_CARRYING_CRUSADER        = 43, // You are already carrying a captured Argent Crusader. You must return to the Argent Vanguard infirmary and drop off your passenger before you may pick up another.
    SPELL_CUSTOM_ERROR_CANT_DO_WHILE_ROOTED             = 44, // You can't do that while rooted.
    SPELL_CUSTOM_ERROR_REQUIRES_NEARBY_TARGET           = 45, // Requires a nearby target.
    SPELL_CUSTOM_ERROR_NOTHING_TO_DISCOVER              = 46, // Nothing left to discover.
    SPELL_CUSTOM_ERROR_NOT_ENOUGH_TARGETS               = 47, // No targets close enough to bluff.
    SPELL_CUSTOM_ERROR_CONSTRUCT_TOO_FAR                = 48, // Your Iron Rune Construct is out of range.
    SPELL_CUSTOM_ERROR_REQUIRES_GRAND_MASTER_ENGINEER   = 49, // Requires Grand Master Engineer
    SPELL_CUSTOM_ERROR_CANT_USE_THAT_MOUNT              = 50, // You can't use that mount.
    SPELL_CUSTOM_ERROR_NOONE_TO_EJECT                   = 51, // There is nobody to eject!
    SPELL_CUSTOM_ERROR_TARGET_MUST_BE_BOUND             = 52, // The target must be bound to you.
    SPELL_CUSTOM_ERROR_TARGET_MUST_BE_UNDEAD            = 53, // Target must be undead.
    SPELL_CUSTOM_ERROR_TARGET_TOO_FAR                   = 54, // You have no target or your target is too far away.
    SPELL_CUSTOM_ERROR_MISSING_DARK_MATTER              = 55, // Missing Reagents: Dark Matter
    SPELL_CUSTOM_ERROR_CANT_USE_THAT_ITEM               = 56, // You can't use that item
    SPELL_CUSTOM_ERROR_CANT_DO_WHILE_CYCYLONED          = 57, // You can't do that while Cycloned
    SPELL_CUSTOM_ERROR_TARGET_HAS_SCROLL                = 58, // Target is already affected by a scroll
    SPELL_CUSTOM_ERROR_POISON_TOO_STRONG                = 59, // That anti-venom is not strong enough to dispel that poison
    SPELL_CUSTOM_ERROR_MUST_HAVE_LANCE_EQUIPPED         = 60, // You must have a lance equipped.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_MAIDEN          = 61, // You must be near the Maiden of Winter's Breath Lake.
    SPELL_CUSTOM_ERROR_LEARNED_EVERYTHING               = 62, // You have learned everything from that book
    SPELL_CUSTOM_ERROR_PET_IS_DEAD                      = 63, // Your pet is dead
    SPELL_CUSTOM_ERROR_NO_VALID_TARGETS                 = 64, // There are no valid targets within range.
    SPELL_CUSTOM_ERROR_GM_ONLY                          = 65, // Only GMs may use that. Your account has been reported for investigation.
    SPELL_CUSTOM_ERROR_REQUIRES_LEVEL_58                = 66, // You must reach level 58 to use this portal.
    SPELL_CUSTOM_ERROR_AT_HONOR_CAP                     = 67, // You already have the maximum amount of honor.
    SPELL_CUSTOM_ERROR_68                               = 68, // ""
    SPELL_CUSTOM_ERROR_69                               = 69, // ""
    SPELL_CUSTOM_ERROR_70                               = 70, // ""
    SPELL_CUSTOM_ERROR_71                               = 71, // ""
    SPELL_CUSTOM_ERROR_72                               = 72, // ""
    SPELL_CUSTOM_ERROR_73                               = 73, // ""
    SPELL_CUSTOM_ERROR_74                               = 74, // ""
    SPELL_CUSTOM_ERROR_MUST_HAVE_DEMONIC_CIRCLE         = 75, // You must have a demonic circle active.
    SPELL_CUSTOM_ERROR_AT_MAX_RAGE                      = 76, // You already have maximum rage
    SPELL_CUSTOM_ERROR_REQUIRES_350_ENGINEERING         = 77, // Requires Engineering (350)
    SPELL_CUSTOM_ERROR_SOUL_BELONGS_TO_LICH_KING        = 78, // Your soul belongs to the Lich King
    SPELL_CUSTOM_ERROR_ATTENDANT_HAS_PONY               = 79, // Your attendant already has an Argent Pony
    SPELL_CUSTOM_ERROR_80                               = 80, // ""
    SPELL_CUSTOM_ERROR_81                               = 81, // ""
    SPELL_CUSTOM_ERROR_82                               = 82, // ""
    SPELL_CUSTOM_ERROR_MUST_HAVE_FIRE_TOTEM             = 83, // You must have a Fire Totem active.
    SPELL_CUSTOM_ERROR_CANT_TARGET_VAMPIRES             = 84, // You may not bite other vampires.
    SPELL_CUSTOM_ERROR_PET_ALREADY_AT_YOUR_LEVEL        = 85, // Your pet is already at your level.
    SPELL_CUSTOM_ERROR_MISSING_ITEM_REQUIREMENS         = 86, // You do not meet the level requirements for this item.
    SPELL_CUSTOM_ERROR_TOO_MANY_ABOMINATIONS            = 87, // There are too many Mutated Abominations.
    SPELL_CUSTOM_ERROR_ALL_POTIONS_USED                 = 88, // The potions have all been depleted by Professor Putricide.
    SPELL_CUSTOM_ERROR_89                               = 89, // ""
    SPELL_CUSTOM_ERROR_REQUIRES_LEVEL_65                = 90, // Requires level 65
    SPELL_CUSTOM_ERROR_91                               = 91, // ""
    SPELL_CUSTOM_ERROR_92                               = 92, // ""
    SPELL_CUSTOM_ERROR_93                               = 93, // ""
    SPELL_CUSTOM_ERROR_94                               = 94, // ""
    SPELL_CUSTOM_ERROR_95                               = 95, // ""
    SPELL_CUSTOM_ERROR_MAX_NUMBER_OF_RECRUITS           = 96, // You already have the max number of recruits.
    SPELL_CUSTOM_ERROR_MAX_NUMBER_OF_VOLUNTEERS         = 97, // You already have the max number of volunteers.
    SPELL_CUSTOM_ERROR_FROSTMOURNE_RENDERED_RESURRECT   = 98, // Frostmourne has rendered you unable to resurrect.
    SPELL_CUSTOM_ERROR_CANT_MOUNT_WITH_SHAPESHIFT       = 99, // You can't mount while affected by that shapeshift.
};

enum StealthType
{
    STEALTH_GENERAL     = 0,
    STEALTH_TRAP        = 1,

    TOTAL_STEALTH_TYPES = 2
};

enum InvisibilityType
{
    INVISIBILITY_GENERAL     =  0,
    INVISIBILITY_UNK1        =  1,
    INVISIBILITY_UNK2        =  2,
    INVISIBILITY_TRAP        =  3,
    INVISIBILITY_UNK4        =  4,
    INVISIBILITY_UNK5        =  5,
    INVISIBILITY_DRUNK       =  6,
    INVISIBILITY_UNK7        =  7,
    INVISIBILITY_UNK8        =  8,
    INVISIBILITY_UNK9        =  9,
    INVISIBILITY_UNK10       = 10,
    INVISIBILITY_UNK11       = 11,

    TOTAL_INVISIBILITY_TYPES = 12
};

enum ServerSideVisibilityType
{
    SERVERSIDE_VISIBILITY_GM          = 0,
    SERVERSIDE_VISIBILITY_GHOST       = 1,

    TOTAL_SERVERSIDE_VISIBILITY_TYPES = 2
};

enum GhostVisibilityType
{
    GHOST_VISIBILITY_ALIVE = 0x1,
    GHOST_VISIBILITY_GHOST = 0x2
};

// Spell aura states
// EnumUtils: DESCRIBE THIS
enum AuraStateType
{
    // (C) used in caster aura state     (T) used in target aura state
    // (c) used in caster aura state-not (t) used in target aura state-not
    AURA_STATE_NONE                         = 0,            // C   |
    AURA_STATE_DEFENSE                      = 1,            // C   |
    AURA_STATE_HEALTHLESS_20_PERCENT        = 2,            // CcT |
    AURA_STATE_BERSERKING                   = 3,            // C T |
    AURA_STATE_FROZEN                       = 4,            //  c t| frozen target
    AURA_STATE_JUDGEMENT                    = 5,            // C   |
    //AURA_STATE_UNKNOWN6                   = 6,            //     | not used
    AURA_STATE_HUNTER_PARRY                 = 7,            // C   |
    //AURA_STATE_UNKNOWN7                   = 7,            //  c  | creature cheap shot / focused bursts spells
    //AURA_STATE_UNKNOWN8                   = 8,            //    t| test spells
    //AURA_STATE_UNKNOWN9                   = 9,            //     |
    AURA_STATE_WARRIOR_VICTORY_RUSH         = 10,           // C   | warrior victory rush
    //AURA_STATE_UNKNOWN11                  = 11,           // C  t| 60348 - Maelstrom Ready!, test spells
    AURA_STATE_FAERIE_FIRE                  = 12,           //  c t|
    AURA_STATE_HEALTHLESS_35_PERCENT        = 13,           // C T |
    AURA_STATE_CONFLAGRATE                  = 14,           //   T |
    AURA_STATE_SWIFTMEND                    = 15,           //   T |
    AURA_STATE_DEADLY_POISON                = 16,           //   T |
    AURA_STATE_ENRAGE                       = 17,           // C   |
    AURA_STATE_BLEEDING                     = 18,           //    T|
    AURA_STATE_UNKNOWN19                    = 19,           //     |
    //AURA_STATE_UNKNOWN20                  = 20,           //  c  | only (45317 Suicide)
    //AURA_STATE_UNKNOWN21                  = 21,           //     | not used
    AURA_STATE_UNKNOWN22                    = 22,           // C  t| varius spells (63884, 50240)
    AURA_STATE_HEALTH_ABOVE_75_PERCENT      = 23,           // C   |
};

#define PER_CASTER_AURA_STATE_MASK (\
    (1<<(AURA_STATE_CONFLAGRATE-1))|(1<<(AURA_STATE_DEADLY_POISON-1)))

// Spell mechanics
// EnumUtils: DESCRIBE THIS
enum Mechanics : uint32
{
    MECHANIC_NONE             = 0,
    MECHANIC_CHARM            = 1,
    MECHANIC_DISORIENTED      = 2,
    MECHANIC_DISARM           = 3,
    MECHANIC_DISTRACT         = 4,
    MECHANIC_FEAR             = 5,
    MECHANIC_GRIP             = 6,
    MECHANIC_ROOT             = 7,
    MECHANIC_SLOW_ATTACK      = 8,
    MECHANIC_SILENCE          = 9,
    MECHANIC_SLEEP            = 10,
    MECHANIC_SNARE            = 11,
    MECHANIC_STUN             = 12,
    MECHANIC_FREEZE           = 13,
    MECHANIC_KNOCKOUT         = 14,
    MECHANIC_BLEED            = 15,
    MECHANIC_BANDAGE          = 16,
    MECHANIC_POLYMORPH        = 17,
    MECHANIC_BANISH           = 18,
    MECHANIC_SHIELD           = 19,
    MECHANIC_SHACKLE          = 20,
    MECHANIC_MOUNT            = 21,
    MECHANIC_INFECTED         = 22,
    MECHANIC_TURN             = 23,
    MECHANIC_HORROR           = 24,
    MECHANIC_INVULNERABILITY  = 25,
    MECHANIC_INTERRUPT        = 26,
    MECHANIC_DAZE             = 27,
    MECHANIC_DISCOVERY        = 28,
    MECHANIC_IMMUNE_SHIELD    = 29,                         // Divine (Blessing) Shield/Protection and Ice Block
    MECHANIC_SAPPED           = 30,
    MECHANIC_ENRAGED          = 31,
    MAX_MECHANIC              = 32 // SKIP
};

// Used for spell 42292 Immune Movement Impairment and Loss of Control (0x49967ca6)
#define IMMUNE_TO_MOVEMENT_IMPAIRMENT_AND_LOSS_CONTROL_MASK (\
    (1<<MECHANIC_CHARM)|(1<<MECHANIC_DISORIENTED)|(1<<MECHANIC_FEAR)| \
    (1<<MECHANIC_ROOT)|(1<<MECHANIC_SLEEP)|(1<<MECHANIC_SNARE)| \
    (1<<MECHANIC_STUN)|(1<<MECHANIC_FREEZE)|(1<<MECHANIC_KNOCKOUT)| \
    (1<<MECHANIC_POLYMORPH)|(1<<MECHANIC_BANISH)|(1<<MECHANIC_SHACKLE)| \
    (1<<MECHANIC_TURN)|(1<<MECHANIC_HORROR)|(1<<MECHANIC_DAZE)| \
    (1<<MECHANIC_SAPPED))

// Spell dispel type
enum DispelType
{
    DISPEL_NONE         = 0,
    DISPEL_MAGIC        = 1,
    DISPEL_CURSE        = 2,
    DISPEL_DISEASE      = 3,
    DISPEL_POISON       = 4,
    DISPEL_STEALTH      = 5,
    DISPEL_INVISIBILITY = 6,
    DISPEL_ALL          = 7,
    DISPEL_SPE_NPC_ONLY = 8,
    DISPEL_ENRAGE       = 9,
    DISPEL_ZG_TICKET    = 10,
    DESPEL_OLD_UNUSED   = 11
};

#define DISPEL_ALL_MASK ((1<<DISPEL_MAGIC) | (1<<DISPEL_CURSE) | (1<<DISPEL_DISEASE) | (1<<DISPEL_POISON))

//To all Immune system, if target has immunes,
//some spell that related to ImmuneToDispel or ImmuneToSchool or ImmuneToDamage type can't cast to it,
//some spell_effects that related to ImmuneToEffect<effect>(only this effect in the spell) can't cast to it,
//some aura(related to Mechanics or ImmuneToState<aura>) can't apply to it.
enum SpellImmunity
{
    IMMUNITY_EFFECT                = 0,                     // enum SpellEffects
    IMMUNITY_STATE                 = 1,                     // enum AuraType
    IMMUNITY_SCHOOL                = 2,                     // enum SpellSchoolMask
    IMMUNITY_DAMAGE                = 3,                     // enum SpellSchoolMask
    IMMUNITY_DISPEL                = 4,                     // enum DispelType
    IMMUNITY_MECHANIC              = 5,                     // enum Mechanics
    IMMUNITY_ID                    = 6,
    IMMUNITY_ALLOW_ID              = 7                      // xinef: special type of immunity, npc is immune to everything except for those spells id
};

#define MAX_SPELL_IMMUNITY           8

// target enum name consist of:
// TARGET_[OBJECT_TYPE]_[REFERENCE_TYPE(skipped for caster)]_[SELECTION_TYPE(skipped for default)]_[additional specifiers(friendly, BACK_LEFT, etc.]
enum Targets
{
    TARGET_UNIT_CASTER                 = 1,
    TARGET_UNIT_NEARBY_ENEMY           = 2,
    TARGET_UNIT_NEARBY_ALLY            = 3,
    TARGET_UNIT_NEARBY_PARTY           = 4,
    TARGET_UNIT_PET                    = 5,
    TARGET_UNIT_TARGET_ENEMY           = 6,
    TARGET_UNIT_SRC_AREA_ENTRY         = 7,
    TARGET_UNIT_DEST_AREA_ENTRY        = 8,
    TARGET_DEST_HOME                   = 9,
    TARGET_UNIT_SRC_AREA_UNK_11        = 11,
    TARGET_UNIT_SRC_AREA_ENEMY         = 15,
    TARGET_UNIT_DEST_AREA_ENEMY        = 16,
    TARGET_DEST_DB                     = 17,
    TARGET_DEST_CASTER                 = 18,
    TARGET_UNIT_CASTER_AREA_PARTY      = 20,
    TARGET_UNIT_TARGET_ALLY            = 21,
    TARGET_SRC_CASTER                  = 22,
    TARGET_GAMEOBJECT_TARGET           = 23,
    TARGET_UNIT_CONE_ENEMY_24          = 24,
    TARGET_UNIT_TARGET_ANY             = 25,
    TARGET_GAMEOBJECT_ITEM_TARGET      = 26,
    TARGET_UNIT_MASTER                 = 27,
    TARGET_DEST_DYNOBJ_ENEMY           = 28,
    TARGET_DEST_DYNOBJ_ALLY            = 29,
    TARGET_UNIT_SRC_AREA_ALLY          = 30,
    TARGET_UNIT_DEST_AREA_ALLY         = 31,
    TARGET_DEST_CASTER_SUMMON          = 32, // front left, doesn't use radius
    TARGET_UNIT_SRC_AREA_PARTY         = 33,
    TARGET_UNIT_DEST_AREA_PARTY        = 34,
    TARGET_UNIT_TARGET_PARTY           = 35,
    TARGET_DEST_CASTER_36              = 36,
    TARGET_UNIT_LASTTARGET_AREA_PARTY  = 37,
    TARGET_UNIT_NEARBY_ENTRY           = 38,
    TARGET_DEST_CASTER_FISHING         = 39,
    TARGET_GAMEOBJECT_NEARBY_ENTRY     = 40,
    TARGET_DEST_CASTER_FRONT_RIGHT     = 41,
    TARGET_DEST_CASTER_BACK_RIGHT      = 42,
    TARGET_DEST_CASTER_BACK_LEFT       = 43,
    TARGET_DEST_CASTER_FRONT_LEFT      = 44,
    TARGET_UNIT_TARGET_CHAINHEAL_ALLY  = 45,
    TARGET_DEST_NEARBY_ENTRY           = 46,
    TARGET_DEST_CASTER_FRONT           = 47,
    TARGET_DEST_CASTER_BACK            = 48,
    TARGET_DEST_CASTER_RIGHT           = 49,
    TARGET_DEST_CASTER_LEFT            = 50,
    TARGET_GAMEOBJECT_SRC_AREA         = 51,
    TARGET_GAMEOBJECT_DEST_AREA        = 52,
    TARGET_DEST_TARGET_ENEMY           = 53,
    TARGET_UNIT_CONE_ENEMY_54          = 54,
    TARGET_DEST_CASTER_FRONT_LEAP      = 55, // for a leap spell
    TARGET_UNIT_CASTER_AREA_RAID       = 56,
    TARGET_UNIT_TARGET_RAID            = 57,
    TARGET_UNIT_NEARBY_RAID            = 58,
    TARGET_UNIT_CONE_ALLY              = 59,
    TARGET_UNIT_CONE_ENTRY             = 60,
    TARGET_UNIT_TARGET_AREA_RAID_CLASS = 61,
    TARGET_UNK_62                      = 62,
    TARGET_DEST_TARGET_ANY             = 63,
    TARGET_DEST_TARGET_FRONT           = 64,
    TARGET_DEST_TARGET_BACK            = 65,
    TARGET_DEST_TARGET_RIGHT           = 66,
    TARGET_DEST_TARGET_LEFT            = 67,
    TARGET_DEST_TARGET_FRONT_RIGHT     = 68,
    TARGET_DEST_TARGET_BACK_RIGHT      = 69,
    TARGET_DEST_TARGET_BACK_LEFT       = 70,
    TARGET_DEST_TARGET_FRONT_LEFT      = 71,
    TARGET_DEST_CASTER_RANDOM          = 72,
    TARGET_DEST_CASTER_RADIUS          = 73,
    TARGET_DEST_TARGET_RANDOM          = 74,
    TARGET_DEST_TARGET_RADIUS          = 75,
    TARGET_DEST_CHANNEL_TARGET         = 76,
    TARGET_UNIT_CHANNEL_TARGET         = 77,
    TARGET_DEST_DEST_FRONT             = 78,
    TARGET_DEST_DEST_BACK              = 79,
    TARGET_DEST_DEST_RIGHT             = 80,
    TARGET_DEST_DEST_LEFT              = 81,
    TARGET_DEST_DEST_FRONT_RIGHT       = 82,
    TARGET_DEST_DEST_BACK_RIGHT        = 83,
    TARGET_DEST_DEST_BACK_LEFT         = 84,
    TARGET_DEST_DEST_FRONT_LEFT        = 85,
    TARGET_DEST_DEST_RANDOM            = 86,
    TARGET_DEST_DEST                   = 87,
    TARGET_DEST_DYNOBJ_NONE            = 88,
    TARGET_DEST_TRAJ                   = 89,
    TARGET_UNIT_TARGET_MINIPET         = 90,
    TARGET_DEST_DEST_RADIUS            = 91,
    TARGET_UNIT_SUMMONER               = 92,
    TARGET_CORPSE_SRC_AREA_ENEMY       = 93,
    TARGET_UNIT_VEHICLE                = 94,
    TARGET_UNIT_TARGET_PASSENGER       = 95,
    TARGET_UNIT_PASSENGER_0            = 96,
    TARGET_UNIT_PASSENGER_1            = 97,
    TARGET_UNIT_PASSENGER_2            = 98,
    TARGET_UNIT_PASSENGER_3            = 99,
    TARGET_UNIT_PASSENGER_4            = 100,
    TARGET_UNIT_PASSENGER_5            = 101,
    TARGET_UNIT_PASSENGER_6            = 102,
    TARGET_UNIT_PASSENGER_7            = 103,
    TARGET_UNIT_CONE_ENEMY_104         = 104,
    TARGET_UNIT_UNK_105                = 105, // 1 spell
    TARGET_DEST_CHANNEL_CASTER         = 106,
    TARGET_UNK_DEST_AREA_UNK_107       = 107, // not enough info - only generic spells avalible
    TARGET_GAMEOBJECT_CONE             = 108,
    TARGET_DEST_UNK_110                = 110, // 1 spell
    TOTAL_SPELL_TARGETS
};

enum SpellMissInfo
{
    SPELL_MISS_NONE                    = 0,
    SPELL_MISS_MISS                    = 1,
    SPELL_MISS_RESIST                  = 2,
    SPELL_MISS_DODGE                   = 3,
    SPELL_MISS_PARRY                   = 4,
    SPELL_MISS_BLOCK                   = 5,
    SPELL_MISS_EVADE                   = 6,
    SPELL_MISS_IMMUNE                  = 7,
    SPELL_MISS_IMMUNE2                 = 8, // one of these 2 is MISS_TEMPIMMUNE
    SPELL_MISS_DEFLECT                 = 9,
    SPELL_MISS_ABSORB                  = 10,
    SPELL_MISS_REFLECT                 = 11
};

enum SpellHitType
{
    SPELL_HIT_TYPE_CRIT_DEBUG           = 0x01,
    SPELL_HIT_TYPE_CRIT                 = 0x02,
    SPELL_HIT_TYPE_HIT_DEBUG            = 0x04,
    SPELL_HIT_TYPE_SPLIT                = 0x08,
    SPELL_HIT_TYPE_VICTIM_IS_ATTACKER   = 0x10,
    SPELL_HIT_TYPE_ATTACK_TABLE_DEBUG   = 0x20
};

enum SpellDmgClass
{
    SPELL_DAMAGE_CLASS_NONE     = 0,
    SPELL_DAMAGE_CLASS_MAGIC    = 1,
    SPELL_DAMAGE_CLASS_MELEE    = 2,
    SPELL_DAMAGE_CLASS_RANGED   = 3
};

enum SpellPreventionType
{
    SPELL_PREVENTION_TYPE_NONE      = 0,
    SPELL_PREVENTION_TYPE_SILENCE   = 1,
    SPELL_PREVENTION_TYPE_PACIFY    = 2
};

enum GameobjectTypes
{
    GAMEOBJECT_TYPE_DOOR                   = 0,
    GAMEOBJECT_TYPE_BUTTON                 = 1,
    GAMEOBJECT_TYPE_QUESTGIVER             = 2,
    GAMEOBJECT_TYPE_CHEST                  = 3,
    GAMEOBJECT_TYPE_BINDER                 = 4,
    GAMEOBJECT_TYPE_GENERIC                = 5,
    GAMEOBJECT_TYPE_TRAP                   = 6,
    GAMEOBJECT_TYPE_CHAIR                  = 7,
    GAMEOBJECT_TYPE_SPELL_FOCUS            = 8,
    GAMEOBJECT_TYPE_TEXT                   = 9,
    GAMEOBJECT_TYPE_GOOBER                 = 10,
    GAMEOBJECT_TYPE_TRANSPORT              = 11,
    GAMEOBJECT_TYPE_AREADAMAGE             = 12,
    GAMEOBJECT_TYPE_CAMERA                 = 13,
    GAMEOBJECT_TYPE_MAP_OBJECT             = 14,
    GAMEOBJECT_TYPE_MO_TRANSPORT           = 15,
    GAMEOBJECT_TYPE_DUEL_ARBITER           = 16,
    GAMEOBJECT_TYPE_FISHINGNODE            = 17,
    GAMEOBJECT_TYPE_SUMMONING_RITUAL       = 18,
    GAMEOBJECT_TYPE_MAILBOX                = 19,
    GAMEOBJECT_TYPE_DO_NOT_USE             = 20,
    GAMEOBJECT_TYPE_GUARDPOST              = 21,
    GAMEOBJECT_TYPE_SPELLCASTER            = 22,
    GAMEOBJECT_TYPE_MEETINGSTONE           = 23,
    GAMEOBJECT_TYPE_FLAGSTAND              = 24,
    GAMEOBJECT_TYPE_FISHINGHOLE            = 25,
    GAMEOBJECT_TYPE_FLAGDROP               = 26,
    GAMEOBJECT_TYPE_MINI_GAME              = 27,
    GAMEOBJECT_TYPE_DO_NOT_USE_2           = 28,
    GAMEOBJECT_TYPE_CAPTURE_POINT          = 29,
    GAMEOBJECT_TYPE_AURA_GENERATOR         = 30,
    GAMEOBJECT_TYPE_DUNGEON_DIFFICULTY     = 31,
    GAMEOBJECT_TYPE_BARBER_CHAIR           = 32,
    GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING  = 33,
    GAMEOBJECT_TYPE_GUILD_BANK             = 34,
    GAMEOBJECT_TYPE_TRAPDOOR               = 35
};

#define MAX_GAMEOBJECT_TYPE                  36             // sending to client this or greater value can crash client.
#define MAX_GAMEOBJECT_DATA                  24             // Max number of uint32 vars in gameobject_template data field

enum GameObjectFlags : uint32
{
    GO_FLAG_IN_USE          = 0x00000001,                   // disables interaction while animated
    GO_FLAG_LOCKED          = 0x00000002,                   // require key, spell, event, etc to be opened. Makes "Locked" appear in tooltip
    GO_FLAG_INTERACT_COND   = 0x00000004,                   // cannot interact (condition to interact)
    GO_FLAG_TRANSPORT       = 0x00000008,                   // any kind of transport? Object can transport (elevator, boat, car)
    GO_FLAG_NOT_SELECTABLE  = 0x00000010,                   // not selectable even in GM mode
    GO_FLAG_NODESPAWN       = 0x00000020,                   // never despawn, typically for doors, they just change state
    GO_FLAG_TRIGGERED       = 0x00000040,                   // typically, summoned objects. Triggered by spell or other events
    GO_FLAG_DAMAGED         = 0x00000200,
    GO_FLAG_DESTROYED       = 0x00000400,
};

DEFINE_ENUM_FLAG(GameObjectFlags);

enum GameObjectDynamicLowFlags
{
    GO_DYNFLAG_LO_ACTIVATE          = 0x01,                 // enables interaction with GO
    GO_DYNFLAG_LO_ANIMATE           = 0x02,                 // possibly more distinct animation of GO
    GO_DYNFLAG_LO_NO_INTERACT       = 0x04,                 // appears to disable interaction (not fully verified)
    GO_DYNFLAG_LO_SPARKLE           = 0x08,                 // makes GO sparkle
    GO_DYNFLAG_LO_STOPPED           = 0x10                  // Transport is stopped
};

enum GameObjectDestructibleState
{
    GO_DESTRUCTIBLE_INTACT      = 0,
    GO_DESTRUCTIBLE_DAMAGED     = 1,
    GO_DESTRUCTIBLE_DESTROYED   = 2,
    GO_DESTRUCTIBLE_REBUILDING  = 3,
};

// EmotesText.dbc
enum TextEmotes
{
    TEXT_EMOTE_AGREE                = 1,
    TEXT_EMOTE_AMAZE                = 2,
    TEXT_EMOTE_ANGRY                = 3,
    TEXT_EMOTE_APOLOGIZE            = 4,
    TEXT_EMOTE_APPLAUD              = 5,
    TEXT_EMOTE_BASHFUL              = 6,
    TEXT_EMOTE_BECKON               = 7,
    TEXT_EMOTE_BEG                  = 8,
    TEXT_EMOTE_BITE                 = 9,
    TEXT_EMOTE_BLEED                = 10,
    TEXT_EMOTE_BLINK                = 11,
    TEXT_EMOTE_BLUSH                = 12,
    TEXT_EMOTE_BONK                 = 13,
    TEXT_EMOTE_BORED                = 14,
    TEXT_EMOTE_BOUNCE               = 15,
    TEXT_EMOTE_BRB                  = 16,
    TEXT_EMOTE_BOW                  = 17,
    TEXT_EMOTE_BURP                 = 18,
    TEXT_EMOTE_BYE                  = 19,
    TEXT_EMOTE_CACKLE               = 20,
    TEXT_EMOTE_CHEER                = 21,
    TEXT_EMOTE_CHICKEN              = 22,
    TEXT_EMOTE_CHUCKLE              = 23,
    TEXT_EMOTE_CLAP                 = 24,
    TEXT_EMOTE_CONFUSED             = 25,
    TEXT_EMOTE_CONGRATULATE         = 26,
    TEXT_EMOTE_COUGH                = 27,
    TEXT_EMOTE_COWER                = 28,
    TEXT_EMOTE_CRACK                = 29,
    TEXT_EMOTE_CRINGE               = 30,
    TEXT_EMOTE_CRY                  = 31,
    TEXT_EMOTE_CURIOUS              = 32,
    TEXT_EMOTE_CURTSEY              = 33,
    TEXT_EMOTE_DANCE                = 34,
    TEXT_EMOTE_DRINK                = 35,
    TEXT_EMOTE_DROOL                = 36,
    TEXT_EMOTE_EAT                  = 37,
    TEXT_EMOTE_EYE                  = 38,
    TEXT_EMOTE_FART                 = 39,
    TEXT_EMOTE_FIDGET               = 40,
    TEXT_EMOTE_FLEX                 = 41,
    TEXT_EMOTE_FROWN                = 42,
    TEXT_EMOTE_GASP                 = 43,
    TEXT_EMOTE_GAZE                 = 44,
    TEXT_EMOTE_GIGGLE               = 45,
    TEXT_EMOTE_GLARE                = 46,
    TEXT_EMOTE_GLOAT                = 47,
    TEXT_EMOTE_GREET                = 48,
    TEXT_EMOTE_GRIN                 = 49,
    TEXT_EMOTE_GROAN                = 50,
    TEXT_EMOTE_GROVEL               = 51,
    TEXT_EMOTE_GUFFAW               = 52,
    TEXT_EMOTE_HAIL                 = 53,
    TEXT_EMOTE_HAPPY                = 54,
    TEXT_EMOTE_HELLO                = 55,
    TEXT_EMOTE_HUG                  = 56,
    TEXT_EMOTE_HUNGRY               = 57,
    TEXT_EMOTE_KISS                 = 58,
    TEXT_EMOTE_KNEEL                = 59,
    TEXT_EMOTE_LAUGH                = 60,
    TEXT_EMOTE_LAYDOWN              = 61,
    TEXT_EMOTE_MESSAGE              = 62,
    TEXT_EMOTE_MOAN                 = 63,
    TEXT_EMOTE_MOON                 = 64,
    TEXT_EMOTE_MOURN                = 65,
    TEXT_EMOTE_NO                   = 66,
    TEXT_EMOTE_NOD                  = 67,
    TEXT_EMOTE_NOSEPICK             = 68,
    TEXT_EMOTE_PANIC                = 69,
    TEXT_EMOTE_PEER                 = 70,
    TEXT_EMOTE_PLEAD                = 71,
    TEXT_EMOTE_POINT                = 72,
    TEXT_EMOTE_POKE                 = 73,
    TEXT_EMOTE_PRAY                 = 74,
    TEXT_EMOTE_ROAR                 = 75,
    TEXT_EMOTE_ROFL                 = 76,
    TEXT_EMOTE_RUDE                 = 77,
    TEXT_EMOTE_SALUTE               = 78,
    TEXT_EMOTE_SCRATCH              = 79,
    TEXT_EMOTE_SEXY                 = 80,
    TEXT_EMOTE_SHAKE                = 81,
    TEXT_EMOTE_SHOUT                = 82,
    TEXT_EMOTE_SHRUG                = 83,
    TEXT_EMOTE_SHY                  = 84,
    TEXT_EMOTE_SIGH                 = 85,
    TEXT_EMOTE_SIT                  = 86,
    TEXT_EMOTE_SLEEP                = 87,
    TEXT_EMOTE_SNARL                = 88,
    TEXT_EMOTE_SPIT                 = 89,
    TEXT_EMOTE_STARE                = 90,
    TEXT_EMOTE_SURPRISED            = 91,
    TEXT_EMOTE_SURRENDER            = 92,
    TEXT_EMOTE_TALK                 = 93,
    TEXT_EMOTE_TALKEX               = 94,
    TEXT_EMOTE_TALKQ                = 95,
    TEXT_EMOTE_TAP                  = 96,
    TEXT_EMOTE_THANK                = 97,
    TEXT_EMOTE_THREATEN             = 98,
    TEXT_EMOTE_TIRED                = 99,
    TEXT_EMOTE_VICTORY              = 100,
    TEXT_EMOTE_WAVE                 = 101,
    TEXT_EMOTE_WELCOME              = 102,
    TEXT_EMOTE_WHINE                = 103,
    TEXT_EMOTE_WHISTLE              = 104,
    TEXT_EMOTE_WORK                 = 105,
    TEXT_EMOTE_YAWN                 = 106,
    TEXT_EMOTE_BOGGLE               = 107,
    TEXT_EMOTE_CALM                 = 108,
    TEXT_EMOTE_COLD                 = 109,
    TEXT_EMOTE_COMFORT              = 110,
    TEXT_EMOTE_CUDDLE               = 111,
    TEXT_EMOTE_DUCK                 = 112,
    TEXT_EMOTE_INSULT               = 113,
    TEXT_EMOTE_INTRODUCE            = 114,
    TEXT_EMOTE_JK                   = 115,
    TEXT_EMOTE_LICK                 = 116,
    TEXT_EMOTE_LISTEN               = 117,
    TEXT_EMOTE_LOST                 = 118,
    TEXT_EMOTE_MOCK                 = 119,
    TEXT_EMOTE_PONDER               = 120,
    TEXT_EMOTE_POUNCE               = 121,
    TEXT_EMOTE_PRAISE               = 122,
    TEXT_EMOTE_PURR                 = 123,
    TEXT_EMOTE_PUZZLE               = 124,
    TEXT_EMOTE_RAISE                = 125,
    TEXT_EMOTE_READY                = 126,
    TEXT_EMOTE_SHIMMY               = 127,
    TEXT_EMOTE_SHIVER               = 128,
    TEXT_EMOTE_SHOO                 = 129,
    TEXT_EMOTE_SLAP                 = 130,
    TEXT_EMOTE_SMIRK                = 131,
    TEXT_EMOTE_SNIFF                = 132,
    TEXT_EMOTE_SNUB                 = 133,
    TEXT_EMOTE_SOOTHE               = 134,
    TEXT_EMOTE_STINK                = 135,
    TEXT_EMOTE_TAUNT                = 136,
    TEXT_EMOTE_TEASE                = 137,
    TEXT_EMOTE_THIRSTY              = 138,
    TEXT_EMOTE_VETO                 = 139,
    TEXT_EMOTE_SNICKER              = 140,
    TEXT_EMOTE_STAND                = 141,
    TEXT_EMOTE_TICKLE               = 142,
    TEXT_EMOTE_VIOLIN               = 143,
    TEXT_EMOTE_SMILE                = 163,
    TEXT_EMOTE_RASP                 = 183,
    TEXT_EMOTE_PITY                 = 203,
    TEXT_EMOTE_GROWL                = 204,
    TEXT_EMOTE_BARK                 = 205,
    TEXT_EMOTE_SCARED               = 223,
    TEXT_EMOTE_FLOP                 = 224,
    TEXT_EMOTE_LOVE                 = 225,
    TEXT_EMOTE_MOO                  = 226,
    TEXT_EMOTE_COMMEND              = 243,
    TEXT_EMOTE_TRAIN                = 264,
    TEXT_EMOTE_HELPME               = 303,
    TEXT_EMOTE_INCOMING             = 304,
    TEXT_EMOTE_CHARGE               = 305,
    TEXT_EMOTE_FLEE                 = 306,
    TEXT_EMOTE_ATTACKMYTARGET       = 307,
    TEXT_EMOTE_OOM                  = 323,
    TEXT_EMOTE_FOLLOW               = 324,
    TEXT_EMOTE_WAIT                 = 325,
    TEXT_EMOTE_HEALME               = 326,
    TEXT_EMOTE_OPENFIRE             = 327,
    TEXT_EMOTE_FLIRT                = 328,
    TEXT_EMOTE_JOKE                 = 329,
    TEXT_EMOTE_GOLFCLAP             = 343,
    TEXT_EMOTE_WINK                 = 363,
    TEXT_EMOTE_PAT                  = 364,
    TEXT_EMOTE_SERIOUS              = 365,
    TEXT_EMOTE_MOUNT_SPECIAL        = 366,
    TEXT_EMOTE_GOODLUCK             = 367,
    TEXT_EMOTE_BLAME                = 368,
    TEXT_EMOTE_BLANK                = 369,
    TEXT_EMOTE_BRANDISH             = 370,
    TEXT_EMOTE_BREATH               = 371,
    TEXT_EMOTE_DISAGREE             = 372,
    TEXT_EMOTE_DOUBT                = 373,
    TEXT_EMOTE_EMBARRASS            = 374,
    TEXT_EMOTE_ENCOURAGE            = 375,
    TEXT_EMOTE_ENEMY                = 376,
    TEXT_EMOTE_EYEBROW              = 377,
    TEXT_EMOTE_TOAST                = 378,
    TEXT_EMOTE_FAIL                 = 379,
    TEXT_EMOTE_HIGHFIVE             = 380,
    TEXT_EMOTE_ABSENT               = 381,
    TEXT_EMOTE_ARM                  = 382,
    TEXT_EMOTE_AWE                  = 383,
    TEXT_EMOTE_BACKPACK             = 384,
    TEXT_EMOTE_BADFEELING           = 385,
    TEXT_EMOTE_CHALLENGE            = 386,
    TEXT_EMOTE_CHUG                 = 387,
    TEXT_EMOTE_DING                 = 389,
    TEXT_EMOTE_FACEPALM             = 390,
    TEXT_EMOTE_FAINT                = 391,
    TEXT_EMOTE_GO                   = 392,
    TEXT_EMOTE_GOING                = 393,
    TEXT_EMOTE_GLOWER               = 394,
    TEXT_EMOTE_HEADACHE             = 395,
    TEXT_EMOTE_HICCUP               = 396,
    TEXT_EMOTE_HISS                 = 398,
    TEXT_EMOTE_HOLDHAND             = 399,
    TEXT_EMOTE_HURRY                = 401,
    TEXT_EMOTE_IDEA                 = 402,
    TEXT_EMOTE_JEALOUS              = 403,
    TEXT_EMOTE_LUCK                 = 404,
    TEXT_EMOTE_MAP                  = 405,
    TEXT_EMOTE_MERCY                = 406,
    TEXT_EMOTE_MUTTER               = 407,
    TEXT_EMOTE_NERVOUS              = 408,
    TEXT_EMOTE_OFFER                = 409,
    TEXT_EMOTE_PET                  = 410,
    TEXT_EMOTE_PINCH                = 411,
    TEXT_EMOTE_PROUD                = 413,
    TEXT_EMOTE_PROMISE              = 414,
    TEXT_EMOTE_PULSE                = 415,
    TEXT_EMOTE_PUNCH                = 416,
    TEXT_EMOTE_POUT                 = 417,
    TEXT_EMOTE_REGRET               = 418,
    TEXT_EMOTE_REVENGE              = 420,
    TEXT_EMOTE_ROLLEYES             = 421,
    TEXT_EMOTE_RUFFLE               = 422,
    TEXT_EMOTE_SAD                  = 423,
    TEXT_EMOTE_SCOFF                = 424,
    TEXT_EMOTE_SCOLD                = 425,
    TEXT_EMOTE_SCOWL                = 426,
    TEXT_EMOTE_SEARCH               = 427,
    TEXT_EMOTE_SHAKEFIST            = 428,
    TEXT_EMOTE_SHIFTY               = 429,
    TEXT_EMOTE_SHUDDER              = 430,
    TEXT_EMOTE_SIGNAL               = 431,
    TEXT_EMOTE_SILENCE              = 432,
    TEXT_EMOTE_SING                 = 433,
    TEXT_EMOTE_SMACK                = 434,
    TEXT_EMOTE_SNEAK                = 435,
    TEXT_EMOTE_SNEEZE               = 436,
    TEXT_EMOTE_SNORT                = 437,
    TEXT_EMOTE_SQUEAL               = 438,
    TEXT_EMOTE_STOPATTACK           = 439,
    TEXT_EMOTE_SUSPICIOUS           = 440,
    TEXT_EMOTE_THINK                = 441,
    TEXT_EMOTE_TRUCE                = 442,
    TEXT_EMOTE_TWIDDLE              = 443,
    TEXT_EMOTE_WARN                 = 444,
    TEXT_EMOTE_SNAP                 = 445,
    TEXT_EMOTE_CHARM                = 446,
    TEXT_EMOTE_COVEREARS            = 447,
    TEXT_EMOTE_CROSSARMS            = 448,
    TEXT_EMOTE_LOOK                 = 449,
    TEXT_EMOTE_OBJECT               = 450,
    TEXT_EMOTE_SWEAT                = 451,
    TEXT_EMOTE_YW                   = 453,
};

// Emotes.dbc
// EnumUtils: DESCRIBE THIS
enum Emote
{
    EMOTE_ONESHOT_NONE                  = 0, // SKIP
    EMOTE_ONESHOT_TALK                  = 1,
    EMOTE_ONESHOT_BOW                   = 2,
    EMOTE_ONESHOT_WAVE                  = 3,
    EMOTE_ONESHOT_CHEER                 = 4,
    EMOTE_ONESHOT_EXCLAMATION           = 5,
    EMOTE_ONESHOT_QUESTION              = 6,
    EMOTE_ONESHOT_EAT                   = 7,
    EMOTE_STATE_DANCE                   = 10,
    EMOTE_ONESHOT_LAUGH                 = 11,
    EMOTE_STATE_SLEEP                   = 12,
    EMOTE_STATE_SIT                     = 13,
    EMOTE_ONESHOT_RUDE                  = 14,
    EMOTE_ONESHOT_ROAR                  = 15,
    EMOTE_ONESHOT_KNEEL                 = 16,
    EMOTE_ONESHOT_KISS                  = 17,
    EMOTE_ONESHOT_CRY                   = 18,
    EMOTE_ONESHOT_CHICKEN               = 19,
    EMOTE_ONESHOT_BEG                   = 20,
    EMOTE_ONESHOT_APPLAUD               = 21,
    EMOTE_ONESHOT_SHOUT                 = 22,
    EMOTE_ONESHOT_FLEX                  = 23,
    EMOTE_ONESHOT_SHY                   = 24,
    EMOTE_ONESHOT_POINT                 = 25,
    EMOTE_STATE_STAND                   = 26,
    EMOTE_STATE_READY_UNARMED           = 27,
    EMOTE_STATE_WORK_SHEATHED           = 28,
    EMOTE_STATE_POINT                   = 29,
    EMOTE_STATE_NONE                    = 30,
    EMOTE_ONESHOT_WOUND                 = 33,
    EMOTE_ONESHOT_WOUND_CRITICAL        = 34,
    EMOTE_ONESHOT_ATTACK_UNARMED        = 35,
    EMOTE_ONESHOT_ATTACK1H              = 36,
    EMOTE_ONESHOT_ATTACK2HTIGHT         = 37,
    EMOTE_ONESHOT_ATTACK2H_LOOSE        = 38,
    EMOTE_ONESHOT_PARRY_UNARMED         = 39,
    EMOTE_ONESHOT_PARRY_SHIELD          = 43,
    EMOTE_ONESHOT_READY_UNARMED         = 44,
    EMOTE_ONESHOT_READY1H               = 45,
    EMOTE_ONESHOT_READY_BOW             = 48,
    EMOTE_ONESHOT_SPELL_PRECAST         = 50,
    EMOTE_ONESHOT_SPELL_CAST            = 51,
    EMOTE_ONESHOT_BATTLE_ROAR           = 53,
    EMOTE_ONESHOT_SPECIALATTACK1H       = 54,
    EMOTE_ONESHOT_KICK                  = 60,
    EMOTE_ONESHOT_ATTACK_THROWN         = 61,
    EMOTE_STATE_STUN                    = 64,
    EMOTE_STATE_DEAD                    = 65,
    EMOTE_ONESHOT_SALUTE                = 66,
    EMOTE_STATE_KNEEL                   = 68,
    EMOTE_STATE_USE_STANDING            = 69,
    EMOTE_ONESHOT_WAVE_NO_SHEATHE       = 70,
    EMOTE_ONESHOT_CHEER_NO_SHEATHE      = 71,
    EMOTE_ONESHOT_EAT_NO_SHEATHE        = 92,
    EMOTE_STATE_STUN_NO_SHEATHE         = 93,
    EMOTE_ONESHOT_DANCE                 = 94,
    EMOTE_ONESHOT_SALUTE_NO_SHEATH      = 113,
    EMOTE_STATE_USE_STANDING_NO_SHEATHE = 133,
    EMOTE_ONESHOT_LAUGH_NO_SHEATHE      = 153,
    EMOTE_STATE_WORK                    = 173,
    EMOTE_STATE_SPELL_PRECAST           = 193,
    EMOTE_ONESHOT_READY_RIFLE           = 213,
    EMOTE_STATE_READY_RIFLE             = 214,
    EMOTE_STATE_WORK_MINING             = 233,
    EMOTE_STATE_WORK_CHOPWOOD           = 234,
    EMOTE_STATE_APPLAUD                 = 253,
    EMOTE_ONESHOT_LIFTOFF               = 254,
    EMOTE_ONESHOT_YES                   = 273,
    EMOTE_ONESHOT_NO                    = 274,
    EMOTE_ONESHOT_TRAIN                 = 275,
    EMOTE_ONESHOT_LAND                  = 293,
    EMOTE_STATE_AT_EASE                 = 313,
    EMOTE_STATE_READY1H                 = 333,
    EMOTE_STATE_SPELL_KNEEL_START       = 353,
    EMOTE_STATE_SUBMERGED               = 373,
    EMOTE_ONESHOT_SUBMERGE              = 374,
    EMOTE_STATE_READY2H                 = 375,
    EMOTE_STATE_READY_BOW               = 376,
    EMOTE_ONESHOT_MOUNT_SPECIAL         = 377,
    EMOTE_STATE_TALK                    = 378,
    EMOTE_STATE_FISHING                 = 379,
    EMOTE_ONESHOT_FISHING               = 380,
    EMOTE_ONESHOT_LOOT                  = 381,
    EMOTE_STATE_WHIRLWIND               = 382,
    EMOTE_STATE_DROWNED                 = 383,
    EMOTE_STATE_HOLD_BOW                = 384,
    EMOTE_STATE_HOLD_RIFLE              = 385,
    EMOTE_STATE_HOLD_THROWN             = 386,
    EMOTE_ONESHOT_DROWN                 = 387,
    EMOTE_ONESHOT_STOMP                 = 388,
    EMOTE_ONESHOT_ATTACK_OFF            = 389,
    EMOTE_ONESHOT_ATTACK_OFF_PIERCE     = 390,
    EMOTE_STATE_ROAR                    = 391,
    EMOTE_STATE_LAUGH                   = 392,
    EMOTE_ONESHOT_CREATURE_SPECIAL      = 393,
    EMOTE_ONESHOT_JUMPLANDRUN           = 394,
    EMOTE_ONESHOT_JUMPEND               = 395,
    EMOTE_ONESHOT_TALK_NO_SHEATHE       = 396,
    EMOTE_ONESHOT_POINT_NO_SHEATHE      = 397,
    EMOTE_STATE_CANNIBALIZE             = 398,
    EMOTE_ONESHOT_JUMPSTART             = 399,
    EMOTE_STATE_DANCESPECIAL            = 400,
    EMOTE_ONESHOT_DANCESPECIAL          = 401,
    EMOTE_ONESHOT_CUSTOM_SPELL_01       = 402,
    EMOTE_ONESHOT_CUSTOM_SPELL_02       = 403,
    EMOTE_ONESHOT_CUSTOM_SPELL_03       = 404,
    EMOTE_ONESHOT_CUSTOM_SPELL_04       = 405,
    EMOTE_ONESHOT_CUSTOM_SPELL_05       = 406,
    EMOTE_ONESHOT_CUSTOM_SPELL_06       = 407,
    EMOTE_ONESHOT_CUSTOM_SPELL_07       = 408,
    EMOTE_ONESHOT_CUSTOM_SPELL_08       = 409,
    EMOTE_ONESHOT_CUSTOM_SPELL_09       = 410,
    EMOTE_ONESHOT_CUSTOM_SPELL_10       = 411,
    EMOTE_STATE_EXCLAIM                 = 412,
    EMOTE_STATE_DANCE_CUSTOM            = 413,
    EMOTE_STATE_SIT_CHAIR_MED           = 415,
    EMOTE_STATE_CUSTOM_SPELL_01         = 416,
    EMOTE_STATE_CUSTOM_SPELL_02         = 417,
    EMOTE_STATE_EAT                     = 418,
    EMOTE_STATE_CUSTOM_SPELL_04         = 419,
    EMOTE_STATE_CUSTOM_SPELL_03         = 420,
    EMOTE_STATE_CUSTOM_SPELL_05         = 421,
    EMOTE_STATE_SPELLEFFECT_HOLD        = 422,
    EMOTE_STATE_EAT_NO_SHEATHE          = 423,
    EMOTE_STATE_MOUNT                   = 424,
    EMOTE_STATE_READY2HL                = 425,
    EMOTE_STATE_SIT_CHAIR_HIGH          = 426,
    EMOTE_STATE_FALL                    = 427,
    EMOTE_STATE_LOOT                    = 428,
    EMOTE_STATE_SUBMERGED_NEW           = 429,
    EMOTE_ONESHOT_COWER                 = 430,
    EMOTE_STATE_COWER                   = 431,
    EMOTE_ONESHOT_USE_STANDING          = 432,
    EMOTE_STATE_STEALTH_STAND           = 433,
    EMOTE_ONESHOT_OMNICAST_GHOUL        = 434,
    EMOTE_ONESHOT_ATTACK_BOW            = 435,
    EMOTE_ONESHOT_ATTACK_RIFLE          = 436,
    EMOTE_STATE_SWIM_IDLE               = 437,
    EMOTE_STATE_ATTACK_UNARMED          = 438,
    EMOTE_ONESHOT_SPELL_CAST_W_SOUND    = 439,
    EMOTE_ONESHOT_DODGE                 = 440,
    EMOTE_ONESHOT_PARRY1H               = 441,
    EMOTE_ONESHOT_PARRY2H               = 442,
    EMOTE_ONESHOT_PARRY2HL              = 443,
    EMOTE_STATE_FLYFALL                 = 444,
    EMOTE_ONESHOT_FLYDEATH              = 445,
    EMOTE_STATE_FLY_FALL                = 446,
    EMOTE_ONESHOT_FLY_SIT_GROUND_DOWN   = 447,
    EMOTE_ONESHOT_FLY_SIT_GROUND_UP     = 448,
    EMOTE_ONESHOT_EMERGE                = 449,
    EMOTE_ONESHOT_DRAGON_SPIT           = 450,
    EMOTE_STATE_SPECIAL_UNARMED         = 451,
    EMOTE_ONESHOT_FLYGRAB               = 452,
    EMOTE_STATE_FLYGRABCLOSED           = 453,
    EMOTE_ONESHOT_FLYGRABTHROWN         = 454,
    EMOTE_STATE_FLY_SIT_GROUND          = 455,
    EMOTE_STATE_WALK_BACKWARDS          = 456,
    EMOTE_ONESHOT_FLYTALK               = 457,
    EMOTE_ONESHOT_FLYATTACK1H           = 458,
    EMOTE_STATE_CUSTOM_SPELL_08         = 459,
    EMOTE_ONESHOT_FLY_DRAGON_SPIT       = 460,
    EMOTE_STATE_SIT_CHAIR_LOW           = 461,
    EMOTE_ONESHOT_STUN                  = 462,
    EMOTE_ONESHOT_SPELL_CAST_OMNI       = 463,
    EMOTE_STATE_READY_THROWN            = 465,
    EMOTE_ONESHOT_WORK_CHOPWOOD         = 466,
    EMOTE_ONESHOT_WORK_MINING           = 467,
    EMOTE_STATE_SPELL_CHANNEL_OMNI      = 468,
    EMOTE_STATE_SPELL_CHANNEL_DIRECTED  = 469,
    EMOTE_STAND_STATE_NONE              = 470,
    EMOTE_STATE_READYJOUST              = 471,
    EMOTE_STATE_STRANGULATE             = 473,
    EMOTE_STATE_READY_SPELL_OMNI        = 474,
    EMOTE_STATE_HOLD_JOUST              = 475,
    EMOTE_ONESHOT_CRY_JAINA             = 476
};

// AnimationData.dbc
enum Anim
{
    ANIM_STAND                             = 0,
    ANIM_DEATH                             = 1,
    ANIM_SPELL                             = 2,
    ANIM_STOP                              = 3,
    ANIM_WALK                              = 4,
    ANIM_RUN                               = 5,
    ANIM_DEAD                              = 6,
    ANIM_RISE                              = 7,
    ANIM_STAND_WOUND                       = 8,
    ANIM_COMBAT_WOUND                      = 9,
    ANIM_COMBAT_CRITICAL                   = 10,
    ANIM_SHUFFLE_LEFT                      = 11,
    ANIM_SHUFFLE_RIGHT                     = 12,
    ANIM_WALK_BACKWARDS                    = 13,
    ANIM_STUN                              = 14,
    ANIM_HANDS_CLOSED                      = 15,
    ANIM_ATTACK_UNARMED                    = 16,
    ANIM_ATTACK1H                          = 17,
    ANIM_ATTACK2H                          = 18,
    ANIM_ATTACK2HL                         = 19,
    ANIM_PARRY_UNARMED                     = 20,
    ANIM_PARRY1H                           = 21,
    ANIM_PARRY2H                           = 22,
    ANIM_PARRY2HL                          = 23,
    ANIM_SHIELD_BLOCK                      = 24,
    ANIM_READY_UNARMED                     = 25,
    ANIM_READY1H                           = 26,
    ANIM_READY2H                           = 27,
    ANIM_READY2HL                          = 28,
    ANIM_READY_BOW                         = 29,
    ANIM_DODGE                             = 30,
    ANIM_SPELL_PRECAST                     = 31,
    ANIM_SPELL_CAST                        = 32,
    ANIM_SPELL_CAST_AREA                   = 33,
    ANIM_NPC_WELCOME                       = 34,
    ANIM_NPC_GOODBYE                       = 35,
    ANIM_BLOCK                             = 36,
    ANIM_JUMP_START                        = 37,
    ANIM_JUMP                              = 38,
    ANIM_JUMP_END                          = 39,
    ANIM_FALL                              = 40,
    ANIM_SWIM_IDLE                         = 41,
    ANIM_SWIM                              = 42,
    ANIM_SWIM_LEFT                         = 43,
    ANIM_SWIM_RIGHT                        = 44,
    ANIM_SWIM_BACKWARDS                    = 45,
    ANIM_ATTACK_BOW                        = 46,
    ANIM_FIRE_BOW                          = 47,
    ANIM_READY_RIFLE                       = 48,
    ANIM_ATTACK_RIFLE                      = 49,
    ANIM_LOOT                              = 50,
    ANIM_READY_SPELL_DIRECTED              = 51,
    ANIM_READY_SPELL_OMNI                  = 52,
    ANIM_SPELL_CAST_DIRECTED               = 53,
    ANIM_SPELL_CAST_OMNI                   = 54,
    ANIM_BATTLE_ROAR                       = 55,
    ANIM_READY_ABILITY                     = 56,
    ANIM_SPECIAL1H                         = 57,
    ANIM_SPECIAL2H                         = 58,
    ANIM_SHIELD_BASH                       = 59,
    ANIM_EMOTE_TALK                        = 60,
    ANIM_EMOTE_EAT                         = 61,
    ANIM_EMOTE_WORK                        = 62,
    ANIM_EMOTE_USE_STANDING                = 63,
    ANIM_EMOTE_TALK_EXCLAMATION            = 64,
    ANIM_EMOTE_TALK_QUESTION               = 65,
    ANIM_EMOTE_BOW                         = 66,
    ANIM_EMOTE_WAVE                        = 67,
    ANIM_EMOTE_CHEER                       = 68,
    ANIM_EMOTE_DANCE                       = 69,
    ANIM_EMOTE_LAUGH                       = 70,
    ANIM_EMOTE_SLEEP                       = 71,
    ANIM_EMOTE_SIT_GROUND                  = 72,
    ANIM_EMOTE_RUDE                        = 73,
    ANIM_EMOTE_ROAR                        = 74,
    ANIM_EMOTE_KNEEL                       = 75,
    ANIM_EMOTE_KISS                        = 76,
    ANIM_EMOTE_CRY                         = 77,
    ANIM_EMOTE_CHICKEN                     = 78,
    ANIM_EMOTE_BEG                         = 79,
    ANIM_EMOTE_APPLAUD                     = 80,
    ANIM_EMOTE_SHOUT                       = 81,
    ANIM_EMOTE_FLEX                        = 82,
    ANIM_EMOTE_SHY                         = 83,
    ANIM_EMOTE_POINT                       = 84,
    ANIM_ATTACK1H_PIERCE                   = 85,
    ANIM_ATTACK2H_LOOSE_PIERCE             = 86,
    ANIM_ATTACK_OFF                        = 87,
    ANIM_ATTACK_OFF_PIERCE                 = 88,
    ANIM_SHEATHE                           = 89,
    ANIM_HIP_SHEATHE                       = 90,
    ANIM_MOUNT                             = 91,
    ANIM_RUN_RIGHT                         = 92,
    ANIM_RUN_LEFT                          = 93,
    ANIM_MOUNT_SPECIAL                     = 94,
    ANIM_KICK                              = 95,
    ANIM_SIT_GROUND_DOWN                   = 96,
    ANIM_SIT_GROUND                        = 97,
    ANIM_SIT_GROUND_UP                     = 98,
    ANIM_SLEEP_DOWN                        = 99,
    ANIM_SLEEP                             = 100,
    ANIM_SLEEP_UP                          = 101,
    ANIM_SIT_CHAIR_LOW                     = 102,
    ANIM_SIT_CHAIR_MED                     = 103,
    ANIM_SIT_CHAIR_HIGH                    = 104,
    ANIM_LOAD_BOW                          = 105,
    ANIM_LOAD_RIFLE                        = 106,
    ANIM_ATTACK_THROWN                     = 107,
    ANIM_READY_THROWN                      = 108,
    ANIM_HOLD_BOW                          = 109,
    ANIM_HOLD_RIFLE                        = 110,
    ANIM_HOLD_THROWN                       = 111,
    ANIM_LOAD_THROWN                       = 112,
    ANIM_EMOTE_SALUTE                      = 113,
    ANIM_KNEEL_START                       = 114,
    ANIM_KNEEL_LOOP                        = 115,
    ANIM_KNEEL_END                         = 116,
    ANIM_ATTACK_UNARMED_OFF                = 117,
    ANIM_SPECIAL_UNARMED                   = 118,
    ANIM_STEALTH_WALK                      = 119,
    ANIM_STEALTH_STAND                     = 120,
    ANIM_KNOCKDOWN                         = 121,
    ANIM_EATING_LOOP                       = 122,
    ANIM_USE_STANDING_LOOP                 = 123,
    ANIM_CHANNEL_CAST_DIRECTED             = 124,
    ANIM_CHANNEL_CAST_OMNI                 = 125,
    ANIM_WHIRLWIND                         = 126,
    ANIM_BIRTH                             = 127,
    ANIM_USE_STANDING_START                = 128,
    ANIM_USE_STANDING_END                  = 129,
    ANIM_CREATURE_SPECIAL                  = 130,
    ANIM_DROWN                             = 131,
    ANIM_DROWNED                           = 132,
    ANIM_FISHING_CAST                      = 133,
    ANIM_FISHING_LOOP                      = 134,
    ANIM_FLY                               = 135,
    ANIM_EMOTE_WORK_NO_SHEATHE             = 136,
    ANIM_EMOTE_STUN_NO_SHEATHE             = 137,
    ANIM_EMOTE_USE_STANDING_NO_SHEATHE     = 138,
    ANIM_SPELL_SLEEP_DOWN                  = 139,
    ANIM_SPELL_KNEEL_START                 = 140,
    ANIM_SPELL_KNEEL_LOOP                  = 141,
    ANIM_SPELL_KNEEL_END                   = 142,
    ANIM_SPRINT                            = 143,
    ANIM_IN_FIGHT                          = 144,
    ANIM_SPAWN                             = 145,
    ANIM_CLOSE                             = 146,
    ANIM_CLOSED                            = 147,
    ANIM_OPEN                              = 148,
    ANIM_OPENED                            = 149,
    ANIM_DESTROY                           = 150,
    ANIM_DESTROYED                         = 151,
    ANIM_REBUILD                           = 152,
    ANIM_CUSTOM_0                          = 153,
    ANIM_CUSTOM_1                          = 154,
    ANIM_CUSTOM_2                          = 155,
    ANIM_CUSTOM_3                          = 156,
    ANIM_DESPAWN                           = 157,
    ANIM_HOLD                              = 158,
    ANIM_DECAY                             = 159,
    ANIM_BOW_PULL                          = 160,
    ANIM_BOW_RELEASE                       = 161,
    ANIM_SHIP_START                        = 162,
    ANIM_SHIP_MOVING                       = 163,
    ANIM_SHIP_STOP                         = 164,
    ANIM_GROUP_ARROW                       = 165,
    ANIM_ARROW                             = 166,
    ANIM_CORPSE_ARROW                      = 167,
    ANIM_GUIDE_ARROW                       = 168,
    ANIM_SWAY                              = 169,
    ANIM_DRUID_CAT_POUNCE                  = 170,
    ANIM_DRUID_CAT_RIP                     = 171,
    ANIM_DRUID_CAT_RAKE                    = 172,
    ANIM_DRUID_CAT_RAVAGE                  = 173,
    ANIM_DRUID_CAT_CLAW                    = 174,
    ANIM_DRUID_CAT_COWER                   = 175,
    ANIM_DRUID_BEAR_SWIPE                  = 176,
    ANIM_DRUID_BEAR_BITE                   = 177,
    ANIM_DRUID_BEAR_MAUL                   = 178,
    ANIM_DRUID_BEAR_BASH                   = 179,
    ANIM_DRAGON_TAIL                       = 180,
    ANIM_DRAGON_STOMP                      = 181,
    ANIM_DRAGON_SPIT                       = 182,
    ANIM_DRAGON_SPIT_HOVER                 = 183,
    ANIM_DRAGON_SPIT_FLY                   = 184,
    ANIM_EMOTE_YES                         = 185,
    ANIM_EMOTE_NO                          = 186,
    ANIM_JUMP_LAND_RUN                     = 187,
    ANIM_LOOT_HOLD                         = 188,
    ANIM_LOOT_UP                           = 189,
    ANIM_STAND_HIGH                        = 190,
    ANIM_IMPACT                            = 191,
    ANIM_LIFTOFF                           = 192,
    ANIM_HOVER                             = 193,
    ANIM_SUCCUBUS_ENTICE                   = 194,
    ANIM_EMOTE_TRAIN                       = 195,
    ANIM_EMOTE_DEAD                        = 196,
    ANIM_EMOTE_DANCE_ONCE                  = 197,
    ANIM_DEFLECT                           = 198,
    ANIM_EMOTE_EAT_NO_SHEATHE              = 199,
    ANIM_LAND                              = 200,
    ANIM_SUBMERGE                          = 201,
    ANIM_SUBMERGED                         = 202,
    ANIM_CANNIBALIZE                       = 203,
    ANIM_ARROW_BIRTH                       = 204,
    ANIM_GROUP_ARROW_BIRTH                 = 205,
    ANIM_CORPSE_ARROW_BIRTH                = 206,
    ANIM_GUIDE_ARROW_BIRTH                 = 207,
    ANIM_EMOTE_TALK_NO_SHEATHE             = 208,
    ANIM_EMOTE_POINT_NO_SHEATHE            = 209,
    ANIM_EMOTE_SALUTE_NO_SHEATHE           = 210,
    ANIM_EMOTE_DANCE_SPECIAL               = 211,
    ANIM_MUTILATE                          = 212,
    ANIM_CUSTOM_SPELL_01                   = 213,
    ANIM_CUSTOM_SPELL_02                   = 214,
    ANIM_CUSTOM_SPELL_03                   = 215,
    ANIM_CUSTOM_SPELL_04                   = 216,
    ANIM_CUSTOM_SPELL_05                   = 217,
    ANIM_CUSTOM_SPELL_06                   = 218,
    ANIM_CUSTOM_SPELL_07                   = 219,
    ANIM_CUSTOM_SPELL_08                   = 220,
    ANIM_CUSTOM_SPELL_09                   = 221,
    ANIM_CUSTOM_SPELL_10                   = 222,
    ANIM_STEALTH_RUN                       = 223,
    ANIM_EMERGE                            = 224,
    ANIM_COWER                             = 225,
    ANIM_GRAB                              = 226,
    ANIM_GRAB_CLOSED                       = 227,
    ANIM_GRAB_THROWN                       = 228,
    ANIM_FLY_STAND                         = 229,
    ANIM_FLY_DEATH                         = 230,
    ANIM_FLY_SPELL                         = 231,
    ANIM_FLY_STOP                          = 232,
    ANIM_FLY_WALK                          = 233,
    ANIM_FLY_RUN                           = 234,
    ANIM_FLY_DEAD                          = 235,
    ANIM_FLY_RISE                          = 236,
    ANIM_FLY_STAND_WOUND                   = 237,
    ANIM_FLY_COMBAT_WOUND                  = 238,
    ANIM_FLY_COMBAT_CRITICAL               = 239,
    ANIM_FLY_SHUFFLE_LEFT                  = 240,
    ANIM_FLY_SHUFFLE_RIGHT                 = 241,
    ANIM_FLY_WALK_BACKWARDS                = 242,
    ANIM_FLY_STUN                          = 243,
    ANIM_FLY_HANDS_CLOSED                  = 244,
    ANIM_FLY_ATTACK_UNARMED                = 245,
    ANIM_FLY_ATTACK1H                      = 246,
    ANIM_FLY_ATTACK2H                      = 247,
    ANIM_FLY_ATTACK2HL                     = 248,
    ANIM_FLY_PARRY_UNARMED                 = 249,
    ANIM_FLY_PARRY1H                       = 250,
    ANIM_FLY_PARRY2H                       = 251,
    ANIM_FLY_PARRY2HL                      = 252,
    ANIM_FLY_SHIELD_BLOCK                  = 253,
    ANIM_FLY_READY_UNARMED                 = 254,
    ANIM_FLY_READY1H                       = 255,
    ANIM_FLY_READY2H                       = 256,
    ANIM_FLY_READY2HL                      = 257,
    ANIM_FLY_READY_BOW                     = 258,
    ANIM_FLY_DODGE                         = 259,
    ANIM_FLY_SPELL_PRECAST                 = 260,
    ANIM_FLY_SPELL_CAST                    = 261,
    ANIM_FLY_SPELL_CAST_AREA               = 262,
    ANIM_FLY_NPC_WELCOME                   = 263,
    ANIM_FLY_NPC_GOODBYE                   = 264,
    ANIM_FLY_BLOCK                         = 265,
    ANIM_FLY_JUMP_START                    = 266,
    ANIM_FLY_JUMP                          = 267,
    ANIM_FLY_JUMP_END                      = 268,
    ANIM_FLY_FALL                          = 269,
    ANIM_FLY_SWIM_IDLE                     = 270,
    ANIM_FLY_SWIM                          = 271,
    ANIM_FLY_SWIM_LEFT                     = 272,
    ANIM_FLY_SWIM_RIGHT                    = 273,
    ANIM_FLY_SWIM_BACKWARDS                = 274,
    ANIM_FLY_ATTACK_BOW                    = 275,
    ANIM_FLY_FIRE_BOW                      = 276,
    ANIM_FLY_READY_RIFLE                   = 277,
    ANIM_FLY_ATTACK_RIFLE                  = 278,
    ANIM_FLY_LOOT                          = 279,
    ANIM_FLY_READY_SPELL_DIRECTED          = 280,
    ANIM_FLY_READY_SPELL_OMNI              = 281,
    ANIM_FLY_SPELL_CAST_DIRECTED           = 282,
    ANIM_FLY_SPELL_CAST_OMNI               = 283,
    ANIM_FLY_SPELL_BATTLE_ROAR             = 284,
    ANIM_FLY_READY_ABILITY                 = 285,
    ANIM_FLY_SPECIAL1H                     = 286,
    ANIM_FLY_SPECIAL2H                     = 287,
    ANIM_FLY_SHIELD_BASH                   = 288,
    ANIM_FLY_EMOTE_TALK                    = 289,
    ANIM_FLY_EMOTE_EAT                     = 290,
    ANIM_FLY_EMOTE_WORK                    = 291,
    ANIM_FLY_USE_STANDING                  = 292,
    ANIM_FLY_EMOTE_TALK_EXCLAMATION        = 293,
    ANIM_FLY_EMOTE_TALK_QUESTION           = 294,
    ANIM_FLY_EMOTE_BOW                     = 295,
    ANIM_FLY_EMOTE_WAVE                    = 296,
    ANIM_FLY_EMOTE_CHEER                   = 297,
    ANIM_FLY_EMOTE_DANCE                   = 298,
    ANIM_FLY_EMOTE_LAUGH                   = 299,
    ANIM_FLY_EMOTE_SLEEP                   = 300,
    ANIM_FLY_EMOTE_SIT_GROUND              = 301,
    ANIM_FLY_EMOTE_RUDE                    = 302,
    ANIM_FLY_EMOTE_ROAR                    = 303,
    ANIM_FLY_EMOTE_KNEEL                   = 304,
    ANIM_FLY_EMOTE_KISS                    = 305,
    ANIM_FLY_EMOTE_CRY                     = 306,
    ANIM_FLY_EMOTE_CHICKEN                 = 307,
    ANIM_FLY_EMOTE_BEG                     = 308,
    ANIM_FLY_EMOTE_APPLAUD                 = 309,
    ANIM_FLY_EMOTE_SHOUT                   = 310,
    ANIM_FLY_EMOTE_FLEX                    = 311,
    ANIM_FLY_EMOTE_SHY                     = 312,
    ANIM_FLY_EMOTE_POINT                   = 313,
    ANIM_FLY_ATTACK1H_PIERCE               = 314,
    ANIM_FLY_ATTACK2H_LOOSE_PIERCE         = 315,
    ANIM_FLY_ATTACK_OFF                    = 316,
    ANIM_FLY_ATTACK_OFF_PIERCE             = 317,
    ANIM_FLY_SHEATH                        = 318,
    ANIM_FLY_HIP_SHEATH                    = 319,
    ANIM_FLY_MOUNT                         = 320,
    ANIM_FLY_RUN_RIGHT                     = 321,
    ANIM_FLY_RUN_LEFT                      = 322,
    ANIM_FLY_MOUNT_SPECIAL                 = 323,
    ANIM_FLY_KICK                          = 324,
    ANIM_FLY_SIT_GROUND_DOWN               = 325,
    ANIM_FLY_SIT_GROUND                    = 326,
    ANIM_FLY_SIT_GROUND_UP                 = 327,
    ANIM_FLY_SLEEP_DOWN                    = 328,
    ANIM_FLY_SLEEP                         = 329,
    ANIM_FLY_SLEEP_UP                      = 330,
    ANIM_FLY_SIT_CHAIR_LOW                 = 331,
    ANIM_FLY_SIT_CHAIR_MED                 = 332,
    ANIM_FLY_SIT_CHAIR_HIGH                = 333,
    ANIM_FLY_LOAD_BOW                      = 334,
    ANIM_FLY_LOAD_RIFLE                    = 335,
    ANIM_FLY_ATTACK_THROWN                 = 336,
    ANIM_FLY_READY_THROWN                  = 337,
    ANIM_FLY_HOLD_BOW                      = 338,
    ANIM_FLY_HOLD_RIFLE                    = 339,
    ANIM_FLY_HOLD_THROWN                   = 340,
    ANIM_FLY_LOAD_THROWN                   = 341,
    ANIM_FLY_EMOTE_SALUTE                  = 342,
    ANIM_FLY_KNEEL_START                   = 343,
    ANIM_FLY_KNEEL_LOOP                    = 344,
    ANIM_FLY_KNEEL_END                     = 345,
    ANIM_FLY_ATTACK_UNARMED_OFF            = 346,
    ANIM_FLY_SPECIAL_UNARMED               = 347,
    ANIM_FLY_STEALTH_WALK                  = 348,
    ANIM_FLY_STEALTH_STAND                 = 349,
    ANIM_FLY_KNOCKDOWN                     = 350,
    ANIM_FLY_EATING_LOOP                   = 351,
    ANIM_FLY_USE_STANDING_LOOP             = 352,
    ANIM_FLY_CHANNEL_CAST_DIRECTED         = 353,
    ANIM_FLY_CHANNEL_CAST_OMNI             = 354,
    ANIM_FLY_WHIRLWIND                     = 355,
    ANIM_FLY_BIRTH                         = 356,
    ANIM_FLY_USE_STANDING_START            = 357,
    ANIM_FLY_USE_STANDING_END              = 358,
    ANIM_FLY_CREATURE_SPECIAL              = 359,
    ANIM_FLY_DROWN                         = 360,
    ANIM_FLY_DROWNED                       = 361,
    ANIM_FLY_FISHING_CAST                  = 362,
    ANIM_FLY_FISHING_LOOP                  = 363,
    ANIM_FLY_FLY                           = 364,
    ANIM_FLY_EMOTE_WORK_NO_SHEATHE         = 365,
    ANIM_FLY_EMOTE_STUN_NO_SHEATHE         = 366,
    ANIM_FLY_EMOTE_USE_STANDING_NO_SHEATHE = 367,
    ANIM_FLY_SPELL_SLEEP_DOWN              = 368,
    ANIM_FLY_SPELL_KNEEL_START             = 369,
    ANIM_FLY_SPELL_KNEEL_LOOP              = 370,
    ANIM_FLY_SPELL_KNEEL_END               = 371,
    ANIM_FLY_SPRINT                        = 372,
    ANIM_FLY_IN_FLIGHT                     = 373,
    ANIM_FLY_SPAWN                         = 374,
    ANIM_FLY_CLOSE                         = 375,
    ANIM_FLY_CLOSED                        = 376,
    ANIM_FLY_OPEN                          = 377,
    ANIM_FLY_OPENED                        = 378,
    ANIM_FLY_DESTROY                       = 379,
    ANIM_FLY_DESTROYED                     = 380,
    ANIM_FLY_REBUILD                       = 381,
    ANIM_FLY_CUSTOM_0                      = 382,
    ANIM_FLY_CUSTOM_1                      = 383,
    ANIM_FLY_CUSTOM_2                      = 384,
    ANIM_FLY_CUSTOM_3                      = 385,
    ANIM_FLY_DESPAWN                       = 386,
    ANIM_FLY_HOLD                          = 387,
    ANIM_FLY_DECAY                         = 388,
    ANIM_FLY_BOW_PULL                      = 389,
    ANIM_FLY_BOW_RELEASE                   = 390,
    ANIM_FLY_SHIP_START                    = 391,
    ANIM_FLY_SHIP_MOVING                   = 392,
    ANIM_FLY_SHIP_STOP                     = 393,
    ANIM_FLY_GROUP_ARROW                   = 394,
    ANIM_FLY_ARROW                         = 395,
    ANIM_FLY_CORPSE_ARROW                  = 396,
    ANIM_FLY_GUIDE_ARROW                   = 397,
    ANIM_FLY_SWAY                          = 398,
    ANIM_FLY_DRUID_CAT_POUNCE              = 399,
    ANIM_FLY_DRUID_CAT_RIP                 = 400,
    ANIM_FLY_DRUID_CAT_RAKE                = 401,
    ANIM_FLY_DRUID_CAT_RAVAGE              = 402,
    ANIM_FLY_DRUID_CAT_CLAW                = 403,
    ANIM_FLY_DRUID_CAT_COWER               = 404,
    ANIM_FLY_DRUID_BEAR_SWIPE              = 405,
    ANIM_FLY_DRUID_BEAR_BITE               = 406,
    ANIM_FLY_DRUID_BEAR_MAUL               = 407,
    ANIM_FLY_DRUID_BEAR_BASH               = 408,
    ANIM_FLY_DRAGON_TAIL                   = 409,
    ANIM_FLY_DRAGON_STOMP                  = 410,
    ANIM_FLY_DRAGON_SPIT                   = 411,
    ANIM_FLY_DRAGON_SPIT_HOVER             = 412,
    ANIM_FLY_DRAGON_SPIT_FLY               = 413,
    ANIM_FLY_EMOTE_YES                     = 414,
    ANIM_FLY_EMOTE_NO                      = 415,
    ANIM_FLY_JUMP_LAND_RUN                 = 416,
    ANIM_FLY_LOOT_HOLD                     = 417,
    ANIM_FLY_LOOT_UP                       = 418,
    ANIM_FLY_STAND_HIGH                    = 419,
    ANIM_FLY_IMPACT                        = 420,
    ANIM_FLY_LIFTOFF                       = 421,
    ANIM_FLY_HOVER                         = 422,
    ANIM_FLY_SUCCUBUS_ENTICE               = 423,
    ANIM_FLY_EMOTE_TRAIN                   = 424,
    ANIM_FLY_EMOTE_DEAD                    = 425,
    ANIM_FLY_EMOTE_DANCE_ONCE              = 426,
    ANIM_FLY_DEFLECT                       = 427,
    ANIM_FLY_EMOTE_EAT_NO_SHEATHE          = 428,
    ANIM_FLY_LAND                          = 429,
    ANIM_FLY_SUBMERGE                      = 430,
    ANIM_FLY_SUBMERGED                     = 431,
    ANIM_FLY_CANNIBALIZE                   = 432,
    ANIM_FLY_ARROW_BIRTH                   = 433,
    ANIM_FLY_GROUP_ARROW_BIRTH             = 434,
    ANIM_FLY_CORPSE_ARROW_BIRTH            = 435,
    ANIM_FLY_GUIDE_ARROW_BIRTH             = 436,
    ANIM_FLY_EMOTE_TALK_NO_SHEATHE         = 437,
    ANIM_FLY_EMOTE_POINT_NO_SHEATHE        = 438,
    ANIM_FLY_EMOTE_SALUTE_NO_SHEATHE       = 439,
    ANIM_FLY_EMOTE_DANCE_SPECIAL           = 440,
    ANIM_FLY_MUTILATE                      = 441,
    ANIM_FLY_CUSTOM_SPELL_01               = 442,
    ANIM_FLY_CUSTOM_SPELL_02               = 443,
    ANIM_FLY_CUSTOM_SPELL_03               = 444,
    ANIM_FLY_CUSTOM_SPELL_04               = 445,
    ANIM_FLY_CUSTOM_SPELL_05               = 446,
    ANIM_FLY_CUSTOM_SPELL_06               = 447,
    ANIM_FLY_CUSTOM_SPELL_07               = 448,
    ANIM_FLY_CUSTOM_SPELL_08               = 449,
    ANIM_FLY_CUSTOM_SPELL_09               = 450,
    ANIM_FLY_CUSTOM_SPELL_10               = 451,
    ANIM_FLY_STEALTH_RUN                   = 452,
    ANIM_FLY_EMERGE                        = 453,
    ANIM_FLY_COWER                         = 454,
    ANIM_FLY_GRAB                          = 455,
    ANIM_FLY_GRAB_CLOSED                   = 456,
    ANIM_FLY_GRAB_THROWN                   = 457,
    ANIM_TO_FLY                            = 458,
    ANIM_TO_HOVER                          = 459,
    ANIM_TO_GROUND                         = 460,
    ANIM_FLY_TO_FLY                        = 461,
    ANIM_FLY_TO_HOVER                      = 462,
    ANIM_FLY_TO_GROUND                     = 463,
    ANIM_SETTLE                            = 464,
    ANIM_FLY_SETTLE                        = 465,
    ANIM_DEATH_START                       = 466,
    ANIM_DEATH_LOOP                        = 467,
    ANIM_DEATH_END                         = 468,
    ANIM_FLY_DEATH_START                   = 469,
    ANIM_FLY_DEATH_LOOP                    = 470,
    ANIM_FLY_DEATH_END                     = 471,
    ANIM_DEATH_END_HOLD                    = 472,
    ANIM_FLY_DEATH_END_HOLD                = 473,
    ANIM_STRANGULATE                       = 474,
    ANIM_FLY_STRANGULATE                   = 475,
    ANIM_READY_JOUST                       = 476,
    ANIM_LOAD_JOUST                        = 477,
    ANIM_HOLD_JOUST                        = 478,
    ANIM_FLY_READY_JOUST                   = 479,
    ANIM_FLY_LOAD_JOUST                    = 480,
    ANIM_FLY_HOLD_JOUST                    = 481,
    ANIM_ATTACK_JOUST                      = 482,
    ANIM_FLY_ATTACK_JOUST                  = 483,
    ANIM_RECLINED_MOUNT                    = 484,
    ANIM_FLY_RECLINED_MOUNT                = 485,
    ANIM_TO_ALTERED                        = 486,
    ANIM_FROM_ALTERED                      = 487,
    ANIM_FLY_TO_ALTERED                    = 488,
    ANIM_FLY_FROM_ALTERED                  = 489,
    ANIM_IN_STOCKS                         = 490,
    ANIM_FLY_IN_STOCKS                     = 491,
    ANIM_VEHICLE_GRAB                      = 492,
    ANIM_VEHICLE_THROW                     = 493,
    ANIM_FLY_VEHICLE_GRAB                  = 494,
    ANIM_FLY_VEHICLE_THROW                 = 495,
    ANIM_TO_ALTERED_POST_SWAP              = 496,
    ANIM_FROM_ALTERED_POST_SWAP            = 497,
    ANIM_FLY_TO_ALTERED_POST_SWAP          = 498,
    ANIM_FLY_FROM_ALTERED_POST_SWAP        = 499,
    ANIM_RECLINED_MOUNT_PASSENGER          = 500,
    ANIM_FLY_RECLINED_MOUNT_PASSENGER      = 501,
    ANIM_CARRY2H                           = 502,
    ANIM_CARRIED2H                         = 503,
    ANIM_FLY_CARRY2H                       = 504,
    ANIM_FLY_CARRIED2H                     = 505
};

enum LockKeyType
{
    LOCK_KEY_NONE  = 0,
    LOCK_KEY_ITEM  = 1,
    LOCK_KEY_SKILL = 2,
    LOCK_KEY_SPELL = 3
};

enum LockType
{
    LOCKTYPE_PICKLOCK              = 1,
    LOCKTYPE_HERBALISM             = 2,
    LOCKTYPE_MINING                = 3,
    LOCKTYPE_DISARM_TRAP           = 4,
    LOCKTYPE_OPEN                  = 5,
    LOCKTYPE_TREASURE              = 6,
    LOCKTYPE_CALCIFIED_ELVEN_GEMS  = 7,
    LOCKTYPE_CLOSE                 = 8,
    LOCKTYPE_ARM_TRAP              = 9,
    LOCKTYPE_QUICK_OPEN            = 10,
    LOCKTYPE_QUICK_CLOSE           = 11,
    LOCKTYPE_OPEN_TINKERING        = 12,
    LOCKTYPE_OPEN_KNEELING         = 13,
    LOCKTYPE_OPEN_ATTACKING        = 14,
    LOCKTYPE_GAHZRIDIAN            = 15,
    LOCKTYPE_BLASTING              = 16,
    LOCKTYPE_SLOW_OPEN             = 17,
    LOCKTYPE_SLOW_CLOSE            = 18,
    LOCKTYPE_FISHING               = 19,
    LOCKTYPE_INSCRIPTION           = 20,
    LOCKTYPE_OPEN_FROM_VEHICLE     = 21
};

enum TrainerType                                            // this is important type for npcs!
{
    TRAINER_TYPE_CLASS             = 0,
    TRAINER_TYPE_MOUNTS            = 1,                     // on blizz it's 2
    TRAINER_TYPE_TRADESKILLS       = 2,
    TRAINER_TYPE_PETS              = 3
};

#define MAX_TRAINER_TYPE 4

// CreatureType.dbc
enum CreatureType
{
    CREATURE_TYPE_BEAST            = 1,
    CREATURE_TYPE_DRAGONKIN        = 2,
    CREATURE_TYPE_DEMON            = 3,
    CREATURE_TYPE_ELEMENTAL        = 4,
    CREATURE_TYPE_GIANT            = 5,
    CREATURE_TYPE_UNDEAD           = 6,
    CREATURE_TYPE_HUMANOID         = 7,
    CREATURE_TYPE_CRITTER          = 8,
    CREATURE_TYPE_MECHANICAL       = 9,
    CREATURE_TYPE_NOT_SPECIFIED    = 10,
    CREATURE_TYPE_TOTEM            = 11,
    CREATURE_TYPE_NON_COMBAT_PET   = 12,
    CREATURE_TYPE_GAS_CLOUD        = 13
};

uint32 const CREATURE_TYPEMASK_DEMON_OR_UNDEAD = (1 << (CREATURE_TYPE_DEMON - 1)) | (1 << (CREATURE_TYPE_UNDEAD - 1));
uint32 const CREATURE_TYPEMASK_HUMANOID_OR_UNDEAD = (1 << (CREATURE_TYPE_HUMANOID - 1)) | (1 << (CREATURE_TYPE_UNDEAD - 1));
uint32 const CREATURE_TYPEMASK_MECHANICAL_OR_ELEMENTAL = (1 << (CREATURE_TYPE_MECHANICAL - 1)) | (1 << (CREATURE_TYPE_ELEMENTAL - 1));

// CreatureFamily.dbc
enum CreatureFamily
{
    CREATURE_FAMILY_WOLF           = 1,
    CREATURE_FAMILY_CAT            = 2,
    CREATURE_FAMILY_SPIDER         = 3,
    CREATURE_FAMILY_BEAR           = 4,
    CREATURE_FAMILY_BOAR           = 5,
    CREATURE_FAMILY_CROCOLISK      = 6,
    CREATURE_FAMILY_CARRION_BIRD   = 7,
    CREATURE_FAMILY_CRAB           = 8,
    CREATURE_FAMILY_GORILLA        = 9,
    CREATURE_FAMILY_HORSE_CUSTOM   = 10,                    // not exist in DBC but used for horse like beasts in DB
    CREATURE_FAMILY_RAPTOR         = 11,
    CREATURE_FAMILY_TALLSTRIDER    = 12,
    CREATURE_FAMILY_FELHUNTER      = 15,
    CREATURE_FAMILY_VOIDWALKER     = 16,
    CREATURE_FAMILY_SUCCUBUS       = 17,
    CREATURE_FAMILY_DOOMGUARD      = 19,
    CREATURE_FAMILY_SCORPID        = 20,
    CREATURE_FAMILY_TURTLE         = 21,
    CREATURE_FAMILY_IMP            = 23,
    CREATURE_FAMILY_BAT            = 24,
    CREATURE_FAMILY_HYENA          = 25,
    CREATURE_FAMILY_BIRD_OF_PREY   = 26,
    CREATURE_FAMILY_WIND_SERPENT   = 27,
    CREATURE_FAMILY_REMOTE_CONTROL = 28,
    CREATURE_FAMILY_FELGUARD       = 29,
    CREATURE_FAMILY_DRAGONHAWK     = 30,
    CREATURE_FAMILY_RAVAGER        = 31,
    CREATURE_FAMILY_WARP_STALKER   = 32,
    CREATURE_FAMILY_SPOREBAT       = 33,
    CREATURE_FAMILY_NETHER_RAY     = 34,
    CREATURE_FAMILY_SERPENT        = 35,
    CREATURE_FAMILY_MOTH           = 37,
    CREATURE_FAMILY_CHIMAERA       = 38,
    CREATURE_FAMILY_DEVILSAUR      = 39,
    CREATURE_FAMILY_GHOUL          = 40,
    CREATURE_FAMILY_SILITHID       = 41,
    CREATURE_FAMILY_WORM           = 42,
    CREATURE_FAMILY_RHINO          = 43,
    CREATURE_FAMILY_WASP           = 44,
    CREATURE_FAMILY_CORE_HOUND     = 45,
    CREATURE_FAMILY_SPIRIT_BEAST   = 46
};

enum CreatureTypeFlags
{
    CREATURE_TYPE_FLAG_TAMEABLE                          = 0x00000001,   // Makes the mob tameable (must also be a beast and have family set)
    CREATURE_TYPE_FLAG_VISIBLE_TO_GHOSTS                 = 0x00000002,   // Creature is also visible for not alive player. Allows gossip interaction if npcflag allows?
    CREATURE_TYPE_FLAG_BOSS_MOB                          = 0x00000004,   // Changes creature's visible level to "??" in the creature's portrait - Immune Knockback.
    CREATURE_TYPE_FLAG_DO_NOT_PLAY_WOUND_ANIM            = 0x00000008,   // Does not play wound animation on parry
    CREATURE_TYPE_FLAG_NO_FACTION_TOOLTIP                = 0x00000010,
    CREATURE_TYPE_FLAG_MORE_AUDIBLE                      = 0x00000020,   // Sound related
    CREATURE_TYPE_FLAG_SPELL_ATTACKABLE                  = 0x00000040,
    CREATURE_TYPE_FLAG_INTERACT_WHILE_DEAD               = 0x00000080,   // Player can interact with the creature if creature is dead (not if player is dead)
    CREATURE_TYPE_FLAG_SKIN_WITH_HERBALISM               = 0x00000100,   // Can be looted by herbalist
    CREATURE_TYPE_FLAG_SKIN_WITH_MINING                  = 0x00000200,   // Can be looted by miner
    CREATURE_TYPE_FLAG_NO_DEATH_MESSAGE                  = 0x00000400,   // Death event will not show up in combat log
    CREATURE_TYPE_FLAG_ALLOW_MOUNTED_COMBAT              = 0x00000800,   // Creature can remain mounted when entering combat
    CREATURE_TYPE_FLAG_CAN_ASSIST                        = 0x00001000,   // ? Can aid any player in combat if in range?
    CREATURE_TYPE_FLAG_NO_PET_BAR                        = 0x00002000,
    CREATURE_TYPE_FLAG_MASK_UID                          = 0x00004000,
    CREATURE_TYPE_FLAG_SKIN_WITH_ENGINEERING             = 0x00008000,   // Can be looted by engineer
    CREATURE_TYPE_FLAG_TAMEABLE_EXOTIC                   = 0x00010000,   // Can be tamed by hunter as exotic pet
    CREATURE_TYPE_FLAG_USE_MODEL_COLLISION_SIZE          = 0x00020000,   // Collision related. (always using default collision box?)
    CREATURE_TYPE_FLAG_ALLOW_INTERACTION_WHILE_IN_COMBAT = 0x00040000,
    CREATURE_TYPE_FLAG_COLLIDE_WITH_MISSILES             = 0x00080000,   // Projectiles can collide with this creature - interacts with TARGET_DEST_TRAJ
    CREATURE_TYPE_FLAG_NO_NAME_PLATE                     = 0x00100000,
    CREATURE_TYPE_FLAG_DO_NOT_PLAY_MOUNTED_ANIMATIONS    = 0x00200000,
    CREATURE_TYPE_FLAG_LINK_ALL                          = 0x00400000,
    CREATURE_TYPE_FLAG_INTERACT_ONLY_WITH_CREATOR        = 0x00800000,
    CREATURE_TYPE_FLAG_DO_NOT_PLAY_UNIT_EVENT_SOUNDS     = 0x01000000,
    CREATURE_TYPE_FLAG_HAS_NO_SHADOW_BLOB                = 0x02000000,
    CREATURE_TYPE_FLAG_TREAT_AS_RAID_UNIT                = 0x04000000,   // ! Creature can be targeted by spells that require target to be in caster's party/raid
    CREATURE_TYPE_FLAG_FORCE_GOSSIP                      = 0x08000000,   // Allows the creature to display a single gossip option.
    CREATURE_TYPE_FLAG_DO_NOT_SHEATHE                    = 0x10000000,
    CREATURE_TYPE_FLAG_DO_NOT_TARGET_ON_INTERACTION      = 0x20000000,
    CREATURE_TYPE_FLAG_DO_NOT_RENDER_OBJECT_NAME         = 0x40000000,
    CREATURE_TYPE_FLAG_QUEST_BOSS                        = 0x80000000    // Not verified
};

enum class CreatureStaticFlags : uint32
{
    MOUNTABLE                = 0x00000001,
    NO_XP                    = 0x00000002,
    NO_LOOT                  = 0x00000004,
    UNKILLABLE               = 0x00000008,
    TAMEABLE                 = 0x00000010, // CREATURE_TYPE_FLAG_TAMEABLE
    IMMUNE_TO_PC             = 0x00000020, // UNIT_FLAG_IMMUNE_TO_PC
    IMMUNE_TO_NPC            = 0x00000040, // UNIT_FLAG_IMMUNE_TO_NPC
    CAN_WIELD_LOOT           = 0x00000080,
    SESSILE                  = 0x00000100, // creature_template_movement.Rooted = 1
    UNINTERACTIBLE           = 0x00000200, // UNIT_FLAG_UNINTERACTIBLE
    NO_AUTOMATIC_REGEN       = 0x00000400, // Creatures with that flag uses no UNIT_FLAG2_REGENERATE_POWER
    DESPAWN_INSTANTLY        = 0x00000800, // Creature instantly disappear when killed
    CORPSE_RAID              = 0x00001000,
    CREATOR_LOOT             = 0x00002000, // Lootable only by creator(engineering dummies)
    NO_DEFENSE               = 0x00004000,
    NO_SPELL_DEFENSE         = 0x00008000,
    BOSS_MOB                 = 0x00010000, // CREATURE_TYPE_FLAG_BOSS_MOB, original description: Raid Boss Mob
    COMBAT_PING              = 0x00020000,
    AQUATIC                  = 0x00040000, // aka Water Only, creature_template_movement.Ground = 0
    AMPHIBIOUS               = 0x00080000, // creature_template_movement.Swim = 1
    NO_MELEE_FLEE            = 0x00100000, // Prevents melee and makes npc flee if it enters combat - also misused to just prevent melee on npcs that cant move
    VISIBLE_TO_GHOSTS        = 0x00200000, // CREATURE_TYPE_FLAG_VISIBLE_TO_GHOSTS
    PVP_ENABLING             = 0x00400000, // Old UNIT_FLAG_PVP_ENABLING, now UNIT_BYTES_2_OFFSET_PVP_FLAG from UNIT_FIELD_BYTES_2
    DO_NOT_PLAY_WOUND_ANIM   = 0x00800000, // CREATURE_TYPE_FLAG_DO_NOT_PLAY_WOUND_ANIM
    NO_FACTION_TOOLTIP       = 0x01000000, // CREATURE_TYPE_FLAG_NO_FACTION_TOOLTIP
    IGNORE_COMBAT            = 0x02000000, // Actually only changes react state to passive
    ONLY_ATTACK_PVP_ENABLING = 0x04000000, // "Only attack targets that are PvP enabling"
    CALLS_GUARDS             = 0x08000000, // Creature will summon a guard if player is within its aggro range (even if creature doesn't attack per se)
    CAN_SWIM                 = 0x10000000, // UnitFlags 0x8000 UNIT_FLAG_CAN_SWIM
    FLOATING                 = 0x20000000, // creature_template_movement.Flight = 1
    MORE_AUDIBLE             = 0x40000000, // CREATURE_TYPE_FLAG_MORE_AUDIBLE
    LARGE_AOI                = 0x80000000  // UnitFlags2 0x200000
};

enum class CreatureStaticFlags2 : uint32
{
    NO_PET_SCALING                       = 0x00000001,
    FORCE_PARTY_MEMBERS_INTO_COMBAT      = 0x00000002, // Original description: Force Raid Combat
    LOCK_TAPPERS_TO_RAID_ON_DEATH        = 0x00000004, // "Lock Tappers To Raid On Death", toggleable by 'Set "RAID_LOCK_ON_DEATH" flag for unit(s)' action, CREATURE_FLAG_EXTRA_INSTANCE_BIND
    SPELL_ATTACKABLE                     = 0x00000008, // CREATURE_TYPE_FLAG_SPELL_ATTACKABLE, original description(not valid anymore?): No Harmful Vertex Coloring
    NO_CRUSHING_BLOWS                    = 0x00000010,
    NO_OWNER_THREAT                      = 0x00000020,
    NO_WOUNDED_SLOWDOWN                  = 0x00000040,
    USE_CREATOR_BONUSES                  = 0x00000080,
    IGNORE_FEIGN_DEATH                   = 0x00000100,
    IGNORE_SANCTUARY                     = 0x00000200,
    ACTION_TRIGGERS_WHILE_CHARMED        = 0x00000400,
    INTERACT_WHILE_DEAD                  = 0x00000800, // CREATURE_TYPE_FLAG_INTERACT_WHILE_DEAD
    NO_INTERRUPT_SCHOOL_COOLDOWN         = 0x00001000,
    RETURN_SOUL_SHARD_TO_MASTER_OF_PET   = 0x00002000,
    SKIN_WITH_HERBALISM                  = 0x00004000, // CREATURE_TYPE_FLAG_SKIN_WITH_HERBALISM
    SKIN_WITH_MINING                     = 0x00008000, // CREATURE_TYPE_FLAG_SKIN_WITH_MINING
    ALERT_CONTENT_TEAM_ON_DEATH          = 0x00010000,
    ALERT_CONTENT_TEAM_AT_90_PCT_HP      = 0x00020000,
    ALLOW_MOUNTED_COMBAT                 = 0x00040000, // CREATURE_TYPE_FLAG_ALLOW_MOUNTED_COMBAT
    PVP_ENABLING_OOC                     = 0x00080000,
    NO_DEATH_MESSAGE                     = 0x00100000, // CREATURE_TYPE_FLAG_NO_DEATH_MESSAGE
    IGNORE_PATHING_FAILURE               = 0x00200000,
    FULL_SPELL_LIST                      = 0x00400000,
    DOES_NOT_REDUCE_REPUTATION_FOR_RAIDS = 0x00800000,
    IGNORE_MISDIRECTION                  = 0x01000000,
    HIDE_BODY                            = 0x02000000, // UNIT_FLAG2_HIDE_BODY
    SPAWN_DEFENSIVE                      = 0x04000000,
    SERVER_ONLY                          = 0x08000000,
    CAN_SAFE_FALL                        = 0x10000000, // Original description: No Collision
    CAN_ASSIST                           = 0x20000000, // CREATURE_TYPE_FLAG_CAN_ASSIST, original description: Player Can Heal/Buff
    NO_SKILL_GAINS                       = 0x40000000,
    NO_PET_BAR                           = 0x80000000  // CREATURE_TYPE_FLAG_NO_PET_BAR
};

enum class CreatureStaticFlags3 : uint32
{
    NO_DAMAGE_HISTORY                 = 0x00000001,
    DONT_PVP_ENABLE_OWNER             = 0x00000002,
    DO_NOT_FADE_IN                    = 0x00000004, // UNIT_FLAG2_DO_NOT_FADE_IN
    MASK_UID                          = 0x00000008, // CREATURE_TYPE_FLAG_MASK_UID, original description: Non-Unique In Combat Log
    SKIN_WITH_ENGINEERING             = 0x00000010, // CREATURE_TYPE_FLAG_SKIN_WITH_ENGINEERING
    NO_AGGRO_ON_LEASH                 = 0x00000020,
    NO_FRIENDLY_AREA_AURAS            = 0x00000040,
    EXTENDED_CORPSE_DURATION          = 0x00000080,
    CANNOT_SWIM                       = 0x00000100, // UNIT_FLAG_CANNOT_SWIM
    TAMEABLE_EXOTIC                   = 0x00000200, // CREATURE_TYPE_FLAG_TAMEABLE_EXOTIC
    GIGANTIC_AOI                      = 0x00000400, // Since MoP, creatures with that flag have UnitFlags2 0x400000
    INFINITE_AOI                      = 0x00000800, // Since MoP, creatures with that flag have UnitFlags2 0x40000000
    CANNOT_PENETRATE_WATER            = 0x00001000, // Waterwalking
    NO_NAME_PLATE                     = 0x00002000, // CREATURE_TYPE_FLAG_NO_NAME_PLATE
    CHECKS_LIQUIDS                    = 0x00004000,
    NO_THREAT_FEEDBACK                = 0x00008000,
    USE_MODEL_COLLISION_SIZE          = 0x00010000, // CREATURE_TYPE_FLAG_USE_MODEL_COLLISION_SIZE
    ATTACKER_IGNORES_FACING           = 0x00020000, // In 3.3.5 used only by Rocket Propelled Warhead
    ALLOW_INTERACTION_WHILE_IN_COMBAT = 0x00040000, // CREATURE_TYPE_FLAG_ALLOW_INTERACTION_WHILE_IN_COMBAT
    SPELL_CLICK_FOR_PARTY_ONLY        = 0x00080000,
    FACTION_LEADER                    = 0x00100000,
    IMMUNE_TO_PLAYER_BUFFS            = 0x00200000,
    COLLIDE_WITH_MISSILES             = 0x00400000, // CREATURE_TYPE_FLAG_COLLIDE_WITH_MISSILES
    CAN_BE_MULTITAPPED                = 0x00800000, // Original description: Do Not Tap (Credit to threat list)
    DO_NOT_PLAY_MOUNTED_ANIMATIONS    = 0x01000000, // CREATURE_TYPE_FLAG_DO_NOT_PLAY_MOUNTED_ANIMATIONS, original description: Disable Dodge, Parry and Block Animations
    CANNOT_TURN                       = 0x02000000, // UNIT_FLAG2_CANNOT_TURN
    ENEMY_CHECK_IGNORES_LOS           = 0x04000000,
    FOREVER_CORPSE_DURATION           = 0x08000000, // 7 days
    PETS_ATTACK_WITH_3D_PATHING       = 0x10000000, // "Pets attack with 3d pathing (Kologarn)"
    LINK_ALL                          = 0x20000000, // CREATURE_TYPE_FLAG_LINK_ALL
    AI_CAN_AUTO_TAKEOFF_IN_COMBAT     = 0x40000000,
    AI_CAN_AUTO_LAND_IN_COMBAT        = 0x80000000
};

enum class CreatureStaticFlags4 : uint32
{
    NO_BIRTH_ANIM                                           = 0x00000001, // SMSG_UPDATE_OBJECT's "NoBirthAnim"
    TREAT_AS_PLAYER_FOR_DIMINISHING_RETURNS                 = 0x00000002, // Primarily used by ToC champions
    TREAT_AS_PLAYER_FOR_PVP_DEBUFF_DURATION                 = 0x00000004, // Primarily used by ToC champions
    INTERACT_ONLY_WITH_CREATOR                              = 0x00000008, // CREATURE_TYPE_FLAG_INTERACT_ONLY_WITH_CREATOR, original description: Only Display Gossip for Summoner
    DO_NOT_PLAY_UNIT_EVENT_SOUNDS                           = 0x00000010, // CREATURE_TYPE_FLAG_DO_NOT_PLAY_UNIT_EVENT_SOUNDS, original description: No Death Scream
    HAS_NO_SHADOW_BLOB                                      = 0x00000020, // CREATURE_TYPE_FLAG_HAS_NO_SHADOW_BLOB, original description(wrongly linked type flag or behavior was changed?): Can be Healed by Enemies
    DEALS_TRIPLE_DAMAGE_TO_PC_CONTROLLED_PETS               = 0x00000040,
    NO_NPC_DAMAGE_BELOW_85PTC                               = 0x00000080,
    OBEYS_TAUNT_DIMINISHING_RETURNS                         = 0x00000100, // CREATURE_FLAG_EXTRA_OBEYS_TAUNT_DIMINISHING_RETURNS
    NO_MELEE_APPROACH                                       = 0x00000200,
    UPDATE_CREATURE_RECORD_WHEN_INSTANCE_CHANGES_DIFFICULTY = 0x00000400, // Used only by Snobold Vassal
    CANNOT_DAZE                                             = 0x00000800, // "Cannot Daze (Combat Stun)"
    FLAT_HONOR_AWARD                                        = 0x00001000,
    IGNORE_LOS_WHEN_CASTING_ON_ME                           = 0x00002000, // "Other objects can ignore line of sight requirements when casting spells on me", used only by Ice Tomb in 3.3.5
    GIVE_QUEST_KILL_CREDIT_WHILE_OFFLINE                    = 0x00004000,
    TREAT_AS_RAID_UNIT_FOR_HELPFUL_SPELLS                   = 0x00008000, // CREATURE_TYPE_FLAG_TREAT_AS_RAID_UNIT, "Treat as Raid Unit For Helpful Spells (Instances ONLY)", used by Valithria Dreamwalker
    DONT_REPOSITION_IF_MELEE_TARGET_IS_TOO_CLOSE            = 0x00010000, // "Don't reposition because melee target is too close"
    PET_OR_GUARDIAN_AI_DONT_GO_BEHIND_TARGET                = 0x00020000,
    MINUTE_5_LOOT_ROLL_TIMER                                = 0x00040000, // Used by Lich King
    FORCE_GOSSIP                                            = 0x00080000, // CREATURE_TYPE_FLAG_FORCE_GOSSIP
    DONT_REPOSITION_WITH_FRIENDS_IN_COMBAT                  = 0x00100000,
    DO_NOT_SHEATHE                                          = 0x00200000, // CREATURE_TYPE_FLAG_DO_NOT_SHEATHE, original description: Manual Sheathing control
    IGNORE_SPELL_MIN_RANGE_RESTRICTIONS                     = 0x00400000, // UnitFlags2 0x8000000, original description: Attacker Ignores Minimum Ranges
    SUPPRESS_INSTANCE_WIDE_RELEASE_IN_COMBAT                = 0x00800000,
    PREVENT_SWIM                                            = 0x01000000, // UnitFlags2 0x1000000, original description: AI will only swim if target swims
    HIDE_IN_COMBAT_LOG                                      = 0x02000000, // UnitFlags2 0x2000000, original description: Don't generate combat log when engaged with NPC's
    ALLOW_NPC_COMBAT_WHILE_UNINTERACTIBLE                   = 0x04000000,
    PREFER_NPCS_WHEN_SEARCHING_FOR_ENEMIES                  = 0x08000000,
    ONLY_GENERATE_INITIAL_THREAT                            = 0x10000000,
    DO_NOT_TARGET_ON_INTERACTION                            = 0x20000000, // CREATURE_TYPE_FLAG_DO_NOT_TARGET_ON_INTERACTION, original description: Doesn't change target on right click
    DO_NOT_RENDER_OBJECT_NAME                               = 0x40000000, // CREATURE_TYPE_FLAG_DO_NOT_RENDER_OBJECT_NAME, original description: Hide name in world frame
    QUEST_BOSS                                              = 0x80000000  // CREATURE_TYPE_FLAG_QUEST_BOSS
};

enum class CreatureStaticFlags5 : uint32
{
    UNTARGETABLE_BY_CLIENT                           = 0x00000001, // UnitFlags2 0x4000000 UNIT_FLAG2_UNTARGETABLE_BY_CLIENT
    FORCE_SELF_MOUNTING                              = 0x00000002,
    UNINTERACTIBLE_IF_HOSTILE                        = 0x00000004, // UnitFlags2 0x10000000
    DISABLES_XP_AWARD                                = 0x00000008,
    DISABLE_AI_PREDICTION                            = 0x00000010,
    NO_LEAVECOMBAT_STATE_RESTORE                     = 0x00000020,
    BYPASS_INTERACT_INTERRUPTS                       = 0x00000040,
    DEGREE_BACK_ARC_240                              = 0x00000080,
    INTERACT_WHILE_HOSTILE                           = 0x00000100, // UnitFlags2 0x4000 UNIT_FLAG2_INTERACT_WHILE_HOSTILE
    DONT_DISMISS_ON_FLYING_MOUNT                     = 0x00000200,
    PREDICTIVE_POWER_REGEN                           = 0x00000400, // CREATURE_TYPEFLAGS_2_UNK1
    HIDE_LEVEL_INFO_IN_TOOLTIP                       = 0x00000800, // CREATURE_TYPEFLAGS_2_UNK2
    HIDE_HEALTH_BAR_UNDER_TOOLTIP                    = 0x00001000, // CREATURE_TYPEFLAGS_2_UNK3
    SUPPRESS_HIGHLIGHT_WHEN_TARGETED_OR_MOUSED_OVER  = 0x00002000, // UnitFlags2 0x80000
    AI_PREFER_PATHABLE_TARGETS                       = 0x00004000,
    FREQUENT_AREA_TRIGGER_CHECKS                     = 0x00008000,
    ASSIGN_KILL_CREDIT_TO_ENCOUNTER_LIST             = 0x00010000,
    NEVER_EVADE                                      = 0x00020000,
    AI_CANT_PATH_ON_STEEP_SLOPES                     = 0x00040000,
    AI_IGNORE_LOS_TO_MELEE_TARGET                    = 0x00080000,
    NO_TEXT_IN_CHAT_BUBBLE                           = 0x00100000, // "Never display emote or chat text in a chat bubble", CREATURE_TYPEFLAGS_2_UNK4
    CLOSE_IN_ON_UNPATHABLE_TARGET                    = 0x00200000, // "AI Pets close in on unpathable target"
    DONT_GO_BEHIND_ME                                = 0x00400000, // "Pet/Guardian AI Don't Go Behind Me (use on target)"
    NO_DEATH_THUD                                    = 0x00800000, // CREATURE_TYPEFLAGS_2_UNK5
    CLIENT_LOCAL_CREATURE                            = 0x01000000,
    CAN_DROP_LOOT_WHILE_IN_A_CHALLENGE_MODE_INSTANCE = 0x02000000,
    HAS_SAFE_LOCATION                                = 0x04000000,
    NO_HEALTH_REGEN                                  = 0x08000000,
    NO_POWER_REGEN                                   = 0x10000000,
    NO_PET_UNIT_FRAME                                = 0x20000000,
    NO_INTERACT_ON_LEFT_CLICK                        = 0x40000000, // CREATURE_TYPEFLAGS_2_UNK6
    GIVE_CRITERIA_KILL_CREDIT_WHEN_CHARMED           = 0x80000000
};

enum class CreatureStaticFlags6 : uint32
{
    DO_NOT_AUTO_RESUMMON                                   = 0x00000001, // "Do not auto-resummon this companion creature"
    REPLACE_VISIBLE_UNIT_IF_AVAILABLE                      = 0x00000002, // "Smooth Phasing: Replace visible unit if available"
    IGNORE_REALM_COALESCING_HIDING_CODE                    = 0x00000004, // "Ignore the realm coalescing hiding code (always show)"
    TAPS_TO_FACTION                                        = 0x00000008,
    ONLY_QUESTGIVER_FOR_SUMMONER                           = 0x00000010,
    AI_COMBAT_RETURN_PRECISE                               = 0x00000020,
    HOME_REALM_ONLY_LOOT                                   = 0x00000040,
    NO_INTERACT_RESPONSE                                   = 0x00000080, // TFLAG2_UNK7
    NO_INITIAL_POWER                                       = 0x00000100,
    DONT_CANCEL_CHANNEL_ON_MASTER_MOUNTING                 = 0x00000200,
    CAN_TOGGLE_BETWEEN_DEATH_AND_PERSONAL_LOOT             = 0x00000400,
    ALWAYS_STAND_ON_TOP_OF_TARGET                          = 0x00000800, // "Always, ALWAYS tries to stand right on top of his move to target. ALWAYS!!", toggleable by 'Set "Always Stand on Target" flag for unit(s)' or not same?
    UNCONSCIOUS_ON_DEATH                                   = 0x00001000,
    DONT_REPORT_TO_LOCAL_DEFENSE_CHANNEL_ON_DEATH          = 0x00002000,
    PREFER_UNENGAGED_MONSTERS                              = 0x00004000, // "Prefer unengaged monsters when picking a target"
    USE_PVP_POWER_AND_RESILIENCE                           = 0x00008000, // "Use PVP power and resilience when players attack this creature"
    DONT_CLEAR_DEBUFFS_ON_LEAVE_COMBAT                     = 0x00010000,
    PERSONAL_LOOT_HAS_FULL_SECURITY                        = 0x00020000, // "Personal loot has full security (guaranteed push/mail delivery)"
    TRIPLE_SPELL_VISUALS                                   = 0x00040000,
    USE_GARRISON_OWNER_LEVEL                               = 0x00080000,
    IMMEDIATE_AOI_UPDATE_ON_SPAWN                          = 0x00100000,
    UI_CAN_GET_POSITION                                    = 0x00200000,
    SEAMLESS_TRANSFER_PROHIBITED                           = 0x00400000,
    ALWAYS_USE_GROUP_LOOT_METHOD                           = 0x00800000,
    NO_BOSS_KILL_BANNER                                    = 0x01000000,
    FORCE_TRIGGERING_PLAYER_LOOT_ONLY                      = 0x02000000,
    SHOW_BOSS_FRAME_WHILE_UNINTERACTABLE                   = 0x04000000,
    SCALES_TO_PLAYER_LEVEL                                 = 0x08000000,
    AI_DONT_LEAVE_MELEE_FOR_RANGED_WHEN_TARGET_GETS_ROOTED = 0x10000000,
    DONT_USE_COMBAT_REACH_FOR_CHAINING                     = 0x20000000,
    DO_NOT_PLAY_PROCEDURAL_WOUND_ANIM                      = 0x40000000,
    APPLY_PROCEDURAL_WOUND_ANIM_TO_BASE                    = 0x80000000  // TFLAG2_UNK14
};

enum class CreatureStaticFlags7 : uint32
{
    IMPORTANT_NPC                            = 0x00000001,
    IMPORTANT_QUEST_NPC                      = 0x00000002,
    LARGE_NAMEPLATE                          = 0x00000004,
    TRIVIAL_PET                              = 0x00000008,
    AI_ENEMIES_DONT_BACKUP_WHEN_I_GET_ROOTED = 0x00000010,
    NO_AUTOMATIC_COMBAT_ANCHOR               = 0x00000020,
    ONLY_TARGETABLE_BY_CREATOR               = 0x00000040,
    TREAT_AS_PLAYER_FOR_ISPLAYERCONTROLLED   = 0x00000080,
    GENERATE_NO_THREAT_OR_DAMAGE             = 0x00000100,
    INTERACT_ONLY_ON_QUEST                   = 0x00000200,
    DISABLE_KILL_CREDIT_FOR_OFFLINE_PLAYERS  = 0x00000400,
    AI_ADDITIONAL_PATHING                    = 0x00080000,
};

enum class CreatureStaticFlags8 : uint32
{
    FORCE_CLOSE_IN_ON_PATH_FAIL_BEHAVIOR = 0x00000002,
    USE_2D_CHASING_CALCULATION           = 0x00000020,
    USE_FAST_CLASSIC_HEARTBEAT           = 0x00000040,
};

enum CreatureEliteType
{
    CREATURE_ELITE_NORMAL          = 0,
    CREATURE_ELITE_ELITE           = 1,
    CREATURE_ELITE_RAREELITE       = 2,
    CREATURE_ELITE_WORLDBOSS       = 3,
    CREATURE_ELITE_RARE            = 4,
    CREATURE_UNKNOWN               = 5                      // found in 2.2.3 for 2 mobs
};

// values based at Holidays.dbc
enum HolidayIds
{
    HOLIDAY_NONE                     = 0,

    HOLIDAY_FIREWORKS_SPECTACULAR    = 62,
    HOLIDAY_FEAST_OF_WINTER_VEIL     = 141,
    HOLIDAY_NOBLEGARDEN              = 181,
    HOLIDAY_CHILDRENS_WEEK           = 201,
    HOLIDAY_CALL_TO_ARMS_AV          = 283,
    HOLIDAY_CALL_TO_ARMS_WS          = 284,
    HOLIDAY_CALL_TO_ARMS_AB          = 285,
    HOLIDAY_FISHING_EXTRAVAGANZA     = 301,
    HOLIDAY_HARVEST_FESTIVAL         = 321,
    HOLIDAY_HALLOWS_END              = 324,
    HOLIDAY_LUNAR_FESTIVAL           = 327,
    // HOLIDAY_LOVE_IS_IN_THE_AIR    = 335, unused/duplicated
    HOLIDAY_FIRE_FESTIVAL            = 341,
    HOLIDAY_CALL_TO_ARMS_EY          = 353,
    HOLIDAY_BREWFEST                 = 372,
    HOLIDAY_DARKMOON_FAIRE_ELWYNN    = 374,
    HOLIDAY_DARKMOON_FAIRE_THUNDER   = 375,
    HOLIDAY_DARKMOON_FAIRE_SHATTRATH = 376,
    HOLIDAY_PIRATES_DAY              = 398,
    HOLIDAY_CALL_TO_ARMS_SA          = 400,
    HOLIDAY_PILGRIMS_BOUNTY          = 404,
    HOLIDAY_WOTLK_LAUNCH             = 406,
    HOLIDAY_DAY_OF_DEAD              = 409,
    HOLIDAY_CALL_TO_ARMS_IC          = 420,
    HOLIDAY_LOVE_IS_IN_THE_AIR       = 423,
    HOLIDAY_KALU_AK_FISHING_DERBY    = 424
};

// values based at QuestInfo.dbc
enum QuestTypes
{
    QUEST_TYPE_ELITE               = 1,
    QUEST_TYPE_LIFE                = 21,
    QUEST_TYPE_PVP                 = 41,
    QUEST_TYPE_RAID                = 62,
    QUEST_TYPE_DUNGEON             = 81,
    QUEST_TYPE_WORLD_EVENT         = 82,
    QUEST_TYPE_LEGENDARY           = 83,
    QUEST_TYPE_ESCORT              = 84,
    QUEST_TYPE_HEROIC              = 85,
    QUEST_TYPE_RAID_10             = 88,
    QUEST_TYPE_RAID_25             = 89
};

// values based at QuestSort.dbc
enum QuestSort
{
    QUEST_SORT_EPIC                = 1,
    QUEST_SORT_WAILING_CAVERNS_OLD = 21,
    QUEST_SORT_SEASONAL            = 22,
    QUEST_SORT_UNDERCITY_OLD       = 23,
    QUEST_SORT_HERBALISM           = 24,
    QUEST_SORT_BATTLEGROUNDS       = 25,
    QUEST_SORT_ULDAMN_OLD          = 41,
    QUEST_SORT_WARLOCK             = 61,
    QUEST_SORT_WARRIOR             = 81,
    QUEST_SORT_SHAMAN              = 82,
    QUEST_SORT_FISHING             = 101,
    QUEST_SORT_BLACKSMITHING       = 121,
    QUEST_SORT_PALADIN             = 141,
    QUEST_SORT_MAGE                = 161,
    QUEST_SORT_ROGUE               = 162,
    QUEST_SORT_ALCHEMY             = 181,
    QUEST_SORT_LEATHERWORKING      = 182,
    QUEST_SORT_ENGINEERING         = 201,
    QUEST_SORT_TREASURE_MAP        = 221,
    QUEST_SORT_SUNKEN_TEMPLE_OLD   = 241,
    QUEST_SORT_HUNTER              = 261,
    QUEST_SORT_PRIEST              = 262,
    QUEST_SORT_DRUID               = 263,
    QUEST_SORT_TAILORING           = 264,
    QUEST_SORT_SPECIAL             = 284,
    QUEST_SORT_COOKING             = 304,
    QUEST_SORT_FIRST_AID           = 324,
    QUEST_SORT_LEGENDARY           = 344,
    QUEST_SORT_DARKMOON_FAIRE      = 364,
    QUEST_SORT_AHN_QIRAJ_WAR       = 365,
    QUEST_SORT_LUNAR_FESTIVAL      = 366,
    QUEST_SORT_REPUTATION          = 367,
    QUEST_SORT_INVASION            = 368,
    QUEST_SORT_MIDSUMMER           = 369,
    QUEST_SORT_BREWFEST            = 370,
    QUEST_SORT_INSCRIPTION         = 371,
    QUEST_SORT_DEATH_KNIGHT        = 372,
    QUEST_SORT_JEWELCRAFTING       = 373,
    QUEST_SORT_NOBLEGARDEN         = 374,
    QUEST_SORT_PILGRIMS_BOUNTY     = 375,
    QUEST_SORT_LOVE_IS_IN_THE_AIR  = 376,
};

inline uint8 ClassByQuestSort(int32 QuestSort)
{
    switch (QuestSort)
    {
        case QUEST_SORT_WARLOCK:
            return CLASS_WARLOCK;
        case QUEST_SORT_WARRIOR:
            return CLASS_WARRIOR;
        case QUEST_SORT_SHAMAN:
            return CLASS_SHAMAN;
        case QUEST_SORT_PALADIN:
            return CLASS_PALADIN;
        case QUEST_SORT_MAGE:
            return CLASS_MAGE;
        case QUEST_SORT_ROGUE:
            return CLASS_ROGUE;
        case QUEST_SORT_HUNTER:
            return CLASS_HUNTER;
        case QUEST_SORT_PRIEST:
            return CLASS_PRIEST;
        case QUEST_SORT_DRUID:
            return CLASS_DRUID;
        case QUEST_SORT_DEATH_KNIGHT:
            return CLASS_DEATH_KNIGHT;
    }
    return 0;
}

enum SkillType
{
    SKILL_NONE                     = 0,

    SKILL_FROST                    = 6,
    SKILL_FIRE                     = 8,
    SKILL_ARMS                     = 26,
    SKILL_COMBAT                   = 38,
    SKILL_SUBTLETY                 = 39,
    SKILL_SWORDS                   = 43,
    SKILL_AXES                     = 44,
    SKILL_BOWS                     = 45,
    SKILL_GUNS                     = 46,
    SKILL_BEAST_MASTERY            = 50,
    SKILL_SURVIVAL                 = 51,
    SKILL_MACES                    = 54,
    SKILL_2H_SWORDS                = 55,
    SKILL_HOLY                     = 56,
    SKILL_SHADOW                   = 78,
    SKILL_DEFENSE                  = 95,
    SKILL_LANG_COMMON              = 98,
    SKILL_RACIAL_DWARVEN           = 101,
    SKILL_LANG_ORCISH              = 109,
    SKILL_LANG_DWARVEN             = 111,
    SKILL_LANG_DARNASSIAN          = 113,
    SKILL_LANG_TAURAHE             = 115,
    SKILL_DUAL_WIELD               = 118,
    SKILL_RACIAL_TAUREN            = 124,
    SKILL_ORC_RACIAL               = 125,
    SKILL_RACIAL_NIGHT_ELF         = 126,
    SKILL_FIRST_AID                = 129,
    SKILL_FERAL_COMBAT             = 134,
    SKILL_STAVES                   = 136,
    SKILL_LANG_THALASSIAN          = 137,
    SKILL_LANG_DRACONIC            = 138,
    SKILL_LANG_DEMON_TONGUE        = 139,
    SKILL_LANG_TITAN               = 140,
    SKILL_LANG_OLD_TONGUE          = 141,
    SKILL_SURVIVAL2                = 142,
    SKILL_RIDING_HORSE             = 148,
    SKILL_RIDING_WOLF              = 149,
    SKILL_RIDING_TIGER             = 150,
    SKILL_RIDING_RAM               = 152,
    SKILL_SWIMING                  = 155,
    SKILL_2H_MACES                 = 160,
    SKILL_UNARMED                  = 162,
    SKILL_MARKSMANSHIP             = 163,
    SKILL_BLACKSMITHING            = 164,
    SKILL_LEATHERWORKING           = 165,
    SKILL_ALCHEMY                  = 171,
    SKILL_2H_AXES                  = 172,
    SKILL_DAGGERS                  = 173,
    SKILL_THROWN                   = 176,
    SKILL_HERBALISM                = 182,
    SKILL_GENERIC_DND              = 183,
    SKILL_RETRIBUTION              = 184,
    SKILL_COOKING                  = 185,
    SKILL_MINING                   = 186,
    SKILL_PET_IMP                  = 188,
    SKILL_PET_FELHUNTER            = 189,
    SKILL_TAILORING                = 197,
    SKILL_ENGINEERING              = 202,
    SKILL_PET_SPIDER               = 203,
    SKILL_PET_VOIDWALKER           = 204,
    SKILL_PET_SUCCUBUS             = 205,
    SKILL_PET_INFERNAL             = 206,
    SKILL_PET_DOOMGUARD            = 207,
    SKILL_PET_WOLF                 = 208,
    SKILL_PET_CAT                  = 209,
    SKILL_PET_BEAR                 = 210,
    SKILL_PET_BOAR                 = 211,
    SKILL_PET_CROCILISK            = 212,
    SKILL_PET_CARRION_BIRD         = 213,
    SKILL_PET_CRAB                 = 214,
    SKILL_PET_GORILLA              = 215,
    SKILL_PET_RAPTOR               = 217,
    SKILL_PET_TALLSTRIDER          = 218,
    SKILL_RACIAL_UNDED             = 220,
    SKILL_CROSSBOWS                = 226,
    SKILL_WANDS                    = 228,
    SKILL_POLEARMS                 = 229,
    SKILL_PET_SCORPID              = 236,
    SKILL_ARCANE                   = 237,
    SKILL_PET_TURTLE               = 251,
    SKILL_ASSASSINATION            = 253,
    SKILL_FURY                     = 256,
    SKILL_PROTECTION               = 257,
    SKILL_PROTECTION2              = 267,
    SKILL_PET_TALENTS              = 270,
    SKILL_PLATE_MAIL               = 293,
    SKILL_LANG_GNOMISH             = 313,
    SKILL_LANG_TROLL               = 315,
    SKILL_ENCHANTING               = 333,
    SKILL_DEMONOLOGY               = 354,
    SKILL_AFFLICTION               = 355,
    SKILL_FISHING                  = 356,
    SKILL_ENHANCEMENT              = 373,
    SKILL_RESTORATION              = 374,
    SKILL_ELEMENTAL_COMBAT         = 375,
    SKILL_SKINNING                 = 393,
    SKILL_MAIL                     = 413,
    SKILL_LEATHER                  = 414,
    SKILL_CLOTH                    = 415,
    SKILL_SHIELD                   = 433,
    SKILL_FIST_WEAPONS             = 473,
    SKILL_RIDING_RAPTOR            = 533,
    SKILL_RIDING_MECHANOSTRIDER    = 553,
    SKILL_RIDING_UNDEAD_HORSE      = 554,
    SKILL_RESTORATION2             = 573,
    SKILL_BALANCE                  = 574,
    SKILL_DESTRUCTION              = 593,
    SKILL_HOLY2                    = 594,
    SKILL_DISCIPLINE               = 613,
    SKILL_LOCKPICKING              = 633,
    SKILL_PET_BAT                  = 653,
    SKILL_PET_HYENA                = 654,
    SKILL_PET_BIRD_OF_PREY         = 655,
    SKILL_PET_WIND_SERPENT         = 656,
    SKILL_LANG_GUTTERSPEAK         = 673,
    SKILL_RIDING_KODO              = 713,
    SKILL_RACIAL_TROLL             = 733,
    SKILL_RACIAL_GNOME             = 753,
    SKILL_RACIAL_HUMAN             = 754,
    SKILL_JEWELCRAFTING            = 755,
    SKILL_RACIAL_BLOODELF          = 756,
    SKILL_PET_EVENT_RC             = 758,
    SKILL_LANG_DRAENEI             = 759,
    SKILL_RACIAL_DRAENEI           = 760,
    SKILL_PET_FELGUARD             = 761,
    SKILL_RIDING                   = 762,
    SKILL_PET_DRAGONHAWK           = 763,
    SKILL_PET_NETHER_RAY           = 764,
    SKILL_PET_SPOREBAT             = 765,
    SKILL_PET_WARP_STALKER         = 766,
    SKILL_PET_RAVAGER              = 767,
    SKILL_PET_SERPENT              = 768,
    SKILL_INTERNAL                 = 769,
    SKILL_DK_BLOOD                 = 770,
    SKILL_DK_FROST                 = 771,
    SKILL_DK_UNHOLY                = 772,
    SKILL_INSCRIPTION              = 773,
    SKILL_PET_MOTH                 = 775,
    SKILL_RUNEFORGING              = 776,
    SKILL_MOUNTS                   = 777,
    SKILL_COMPANIONS               = 778,
    SKILL_PET_EXOTIC_CHIMAERA      = 780,
    SKILL_PET_EXOTIC_DEVILSAUR     = 781,
    SKILL_PET_GHOUL                = 782,
    SKILL_PET_EXOTIC_SILITHID      = 783,
    SKILL_PET_EXOTIC_WORM          = 784,
    SKILL_PET_WASP                 = 785,
    SKILL_PET_EXOTIC_RHINO         = 786,
    SKILL_PET_EXOTIC_CORE_HOUND    = 787,
    SKILL_PET_EXOTIC_SPIRIT_BEAST  = 788
};

#define MAX_SKILL_TYPE               789

inline SkillType SkillByLockType(LockType locktype)
{
    switch (locktype)
    {
        case LOCKTYPE_PICKLOCK:
            return SKILL_LOCKPICKING;
        case LOCKTYPE_HERBALISM:
            return SKILL_HERBALISM;
        case LOCKTYPE_MINING:
            return SKILL_MINING;
        case LOCKTYPE_FISHING:
            return SKILL_FISHING;
        case LOCKTYPE_INSCRIPTION:
            return SKILL_INSCRIPTION;
        default:
            break;
    }
    return SKILL_NONE;
}

inline uint32 SkillByQuestSort(int32 QuestSort)
{
    switch (QuestSort)
    {
        case QUEST_SORT_HERBALISM:
            return SKILL_HERBALISM;
        case QUEST_SORT_FISHING:
            return SKILL_FISHING;
        case QUEST_SORT_BLACKSMITHING:
            return SKILL_BLACKSMITHING;
        case QUEST_SORT_ALCHEMY:
            return SKILL_ALCHEMY;
        case QUEST_SORT_LEATHERWORKING:
            return SKILL_LEATHERWORKING;
        case QUEST_SORT_ENGINEERING:
            return SKILL_ENGINEERING;
        case QUEST_SORT_TAILORING:
            return SKILL_TAILORING;
        case QUEST_SORT_COOKING:
            return SKILL_COOKING;
        case QUEST_SORT_FIRST_AID:
            return SKILL_FIRST_AID;
        case QUEST_SORT_JEWELCRAFTING:
            return SKILL_JEWELCRAFTING;
        case QUEST_SORT_INSCRIPTION:
            return SKILL_INSCRIPTION;
    }
    return 0;
}

enum SkillCategory
{
    SKILL_CATEGORY_ATTRIBUTES    = 5,
    SKILL_CATEGORY_WEAPON        = 6,
    SKILL_CATEGORY_CLASS         = 7,
    SKILL_CATEGORY_ARMOR         = 8,
    SKILL_CATEGORY_SECONDARY     = 9,                       // secondary professions
    SKILL_CATEGORY_LANGUAGES     = 10,
    SKILL_CATEGORY_PROFESSION    = 11,                      // primary professions
    SKILL_CATEGORY_GENERIC       = 12
};

enum TotemCategory
{
    TC_SKINNING_SKIFE_OLD          = 1,
    TC_EARTH_TOTEM                 = 2,
    TC_AIR_TOTEM                   = 3,
    TC_FIRE_TOTEM                  = 4,
    TC_WATER_TOTEM                 = 5,
    TC_COPPER_ROD                  = 6,
    TC_SILVER_ROD                  = 7,
    TC_GOLDEN_ROD                  = 8,
    TC_TRUESILVER_ROD              = 9,
    TC_ARCANITE_ROD                = 10,
    TC_MINING_PICK_OLD             = 11,
    TC_PHILOSOPHERS_STONE          = 12,
    TC_BLACKSMITH_HAMMER_OLD       = 13,
    TC_ARCLIGHT_SPANNER            = 14,
    TC_GYROMATIC_MA                = 15,
    TC_MASTER_TOTEM                = 21,
    TC_FEL_IRON_ROD                = 41,
    TC_ADAMANTITE_ROD              = 62,
    TC_ETERNIUM_ROD                = 63,
    TC_HOLLOW_QUILL                = 81,
    TC_RUNED_AZURITE_ROD           = 101,
    TC_VIRTUOSO_INKING_SET         = 121,
    TC_DRUMS                       = 141,
    TC_GNOMISH_ARMY_KNIFE          = 161,
    TC_BLACKSMITH_HAMMER           = 162,
    TC_MINING_PICK                 = 165,
    TC_SKINNING_KNIFE              = 166,
    TC_HAMMER_PICK                 = 167,
    TC_BLADED_PICKAXE              = 168,
    TC_FLINT_AND_TINDER            = 169,
    TC_RUNED_COBALT_ROD            = 189,
    TC_RUNED_TITANIUM_ROD          = 190
};

enum UnitDynFlags
{
    UNIT_DYNFLAG_NONE                       = 0x0000,
    UNIT_DYNFLAG_LOOTABLE                   = 0x0001,
    UNIT_DYNFLAG_TRACK_UNIT                 = 0x0002,
    UNIT_DYNFLAG_TAPPED                     = 0x0004,       // Lua_UnitIsTapped
    UNIT_DYNFLAG_TAPPED_BY_PLAYER           = 0x0008,       // Lua_UnitIsTappedByPlayer
    UNIT_DYNFLAG_SPECIALINFO                = 0x0010,
    UNIT_DYNFLAG_DEAD                       = 0x0020,
    UNIT_DYNFLAG_REFER_A_FRIEND             = 0x0040,
    UNIT_DYNFLAG_TAPPED_BY_ALL_THREAT_LIST  = 0x0080        // Lua_UnitIsTappedByAllThreatList
};

enum CorpseDynFlags
{
    CORPSE_DYNFLAG_LOOTABLE        = 0x0001
};

enum WeatherType
{
    WEATHER_TYPE_FINE       = 0,
    WEATHER_TYPE_RAIN       = 1,
    WEATHER_TYPE_SNOW       = 2,
    WEATHER_TYPE_STORM      = 3,
    WEATHER_TYPE_THUNDERS   = 86,
    WEATHER_TYPE_BLACKRAIN  = 90
};

#define MAX_WEATHER_TYPE 4

// EnumUtils: DESCRIBE THIS
enum ChatMsg
{
    CHAT_MSG_ADDON                  = 0xFFFFFFFF,
    CHAT_MSG_SYSTEM                 = 0x00,
    CHAT_MSG_SAY                    = 0x01,
    CHAT_MSG_PARTY                  = 0x02,
    CHAT_MSG_RAID                   = 0x03,
    CHAT_MSG_GUILD                  = 0x04,
    CHAT_MSG_OFFICER                = 0x05,
    CHAT_MSG_YELL                   = 0x06,
    CHAT_MSG_WHISPER                = 0x07,
    CHAT_MSG_WHISPER_FOREIGN        = 0x08,
    CHAT_MSG_WHISPER_INFORM         = 0x09,
    CHAT_MSG_EMOTE                  = 0x0A,
    CHAT_MSG_TEXT_EMOTE             = 0x0B,
    CHAT_MSG_MONSTER_SAY            = 0x0C,
    CHAT_MSG_MONSTER_PARTY          = 0x0D,
    CHAT_MSG_MONSTER_YELL           = 0x0E,
    CHAT_MSG_MONSTER_WHISPER        = 0x0F,
    CHAT_MSG_MONSTER_EMOTE          = 0x10,
    CHAT_MSG_CHANNEL                = 0x11,
    CHAT_MSG_CHANNEL_JOIN           = 0x12,
    CHAT_MSG_CHANNEL_LEAVE          = 0x13,
    CHAT_MSG_CHANNEL_LIST           = 0x14,
    CHAT_MSG_CHANNEL_NOTICE         = 0x15,
    CHAT_MSG_CHANNEL_NOTICE_USER    = 0x16,
    CHAT_MSG_AFK                    = 0x17,
    CHAT_MSG_DND                    = 0x18,
    CHAT_MSG_IGNORED                = 0x19,
    CHAT_MSG_SKILL                  = 0x1A,
    CHAT_MSG_LOOT                   = 0x1B,
    CHAT_MSG_MONEY                  = 0x1C,
    CHAT_MSG_OPENING                = 0x1D,
    CHAT_MSG_TRADESKILLS            = 0x1E,
    CHAT_MSG_PET_INFO               = 0x1F,
    CHAT_MSG_COMBAT_MISC_INFO       = 0x20,
    CHAT_MSG_COMBAT_XP_GAIN         = 0x21,
    CHAT_MSG_COMBAT_HONOR_GAIN      = 0x22,
    CHAT_MSG_COMBAT_FACTION_CHANGE  = 0x23,
    CHAT_MSG_BG_SYSTEM_NEUTRAL      = 0x24,
    CHAT_MSG_BG_SYSTEM_ALLIANCE     = 0x25,
    CHAT_MSG_BG_SYSTEM_HORDE        = 0x26,
    CHAT_MSG_RAID_LEADER            = 0x27,
    CHAT_MSG_RAID_WARNING           = 0x28,
    CHAT_MSG_RAID_BOSS_EMOTE        = 0x29,
    CHAT_MSG_RAID_BOSS_WHISPER      = 0x2A,
    CHAT_MSG_FILTERED               = 0x2B,
    CHAT_MSG_BATTLEGROUND           = 0x2C,
    CHAT_MSG_BATTLEGROUND_LEADER    = 0x2D,
    CHAT_MSG_RESTRICTED             = 0x2E,
    CHAT_MSG_BATTLENET              = 0x2F,
    CHAT_MSG_ACHIEVEMENT            = 0x30,
    CHAT_MSG_GUILD_ACHIEVEMENT      = 0x31,
    CHAT_MSG_ARENA_POINTS           = 0x32,
    CHAT_MSG_PARTY_LEADER           = 0x33
};

#define MAX_CHAT_MSG_TYPE 0x34

enum ChatLinkColors
{
    CHAT_LINK_COLOR_TRADE       = 0xffffd000,   // orange
    CHAT_LINK_COLOR_TALENT      = 0xff4e96f7,   // blue
    CHAT_LINK_COLOR_SPELL       = 0xff71d5ff,   // bright blue
    CHAT_LINK_COLOR_ENCHANT     = 0xffffd000,   // orange
    CHAT_LINK_COLOR_ACHIEVEMENT = 0xffffff00,
    CHAT_LINK_COLOR_GLYPH       = 0xff66bbff
};

// Values from ItemPetFood (power of (value-1) used for compare with CreatureFamilyEntry.petDietMask
enum PetDiet
{
    PET_DIET_MEAT     = 1,
    PET_DIET_FISH     = 2,
    PET_DIET_CHEESE   = 3,
    PET_DIET_BREAD    = 4,
    PET_DIET_FUNGAS   = 5,
    PET_DIET_FRUIT    = 6,
    PET_DIET_RAW_MEAT = 7,
    PET_DIET_RAW_FISH = 8
};

#define MAX_PET_DIET 9

#define CHAIN_SPELL_JUMP_RADIUS 8

#define GUILD_BANKLOG_MAX_RECORDS   25
#define GUILD_EVENTLOG_MAX_RECORDS  100

enum AiReaction
{
    AI_REACTION_ALERT    = 0,                               // pre-aggro (used in client packet handler)
    AI_REACTION_FRIENDLY = 1,                               // (NOT used in client packet handler)
    AI_REACTION_HOSTILE  = 2,                               // sent on every attack, triggers aggro sound (used in client packet handler)
    AI_REACTION_AFRAID   = 3,                               // seen for polymorph (when AI not in control of self?) (NOT used in client packet handler)
    AI_REACTION_DESTROY  = 4,                               // used on object destroy (NOT used in client packet handler)
};

// Diminishing Returns Types
enum DiminishingReturnsType
{
    DRTYPE_NONE         = 0,                                // this spell is not diminished, but may have limited it's duration to 10s
    DRTYPE_PLAYER       = 1,                                // this spell is diminished only when applied on players
    DRTYPE_ALL          = 2                                 // this spell is diminished in every case
};

// Diminishing Return Groups
enum DiminishingGroup
{
    DIMINISHING_NONE                = 0,
    DIMINISHING_BANISH              = 1,
    DIMINISHING_CHARGE              = 2,
    DIMINISHING_OPENING_STUN        = 3, // Cheap Shot and Pounce
    DIMINISHING_CONTROLLED_STUN     = 4,
    DIMINISHING_CONTROLLED_ROOT     = 5,
    DIMINISHING_CYCLONE             = 6,
    DIMINISHING_DISARM              = 7,
    DIMINISHING_DISORIENT           = 8, // Several spells where name cant be generalized.
    DIMINISHING_ENTRAPMENT          = 9,
    DIMINISHING_FEAR                = 10,
    DIMINISHING_HORROR              = 11,
    DIMINISHING_MIND_CONTROL        = 12,
    DIMINISHING_ROOT                = 13,
    DIMINISHING_STUN                = 14,
    DIMINISHING_SCATTER_SHOT        = 15,
    DIMINISHING_SILENCE             = 16,
    DIMINISHING_SLEEP               = 17,
    DIMINISHING_TAUNT               = 18,
    DIMINISHING_LIMITONLY           = 19,
    DIMINISHING_DRAGONS_BREATH      = 20,
};

enum SummonCategory
{
    SUMMON_CATEGORY_WILD        = 0,
    SUMMON_CATEGORY_ALLY        = 1,
    SUMMON_CATEGORY_PET         = 2,
    SUMMON_CATEGORY_PUPPET      = 3,
    SUMMON_CATEGORY_VEHICLE     = 4,
    SUMMON_CATEGORY_UNK         = 5, // as of patch 3.3.5a only Bone Spike in Icecrown Citadel
    // uses this category
};

enum SummonType
{
    SUMMON_TYPE_NONE        = 0,
    SUMMON_TYPE_PET         = 1,
    SUMMON_TYPE_GUARDIAN    = 2,
    SUMMON_TYPE_MINION      = 3,
    SUMMON_TYPE_TOTEM       = 4,
    SUMMON_TYPE_MINIPET     = 5,
    SUMMON_TYPE_GUARDIAN2   = 6,
    SUMMON_TYPE_WILD2       = 7,
    SUMMON_TYPE_WILD3       = 8,    // Related to phases and DK prequest line (3.3.5a)
    SUMMON_TYPE_VEHICLE     = 9,
    SUMMON_TYPE_VEHICLE2    = 10,   // Oculus and Argent Tournament vehicles (3.3.5a)
    SUMMON_TYPE_LIGHTWELL   = 11,
    SUMMON_TYPE_JEEVES      = 12
};

enum SummonSlot
{
    SUMMON_SLOT_PET = 0,
    SUMMON_SLOT_TOTEM_FIRE = 1,
    SUMMON_SLOT_TOTEM_EARTH = 2,
    SUMMON_SLOT_TOTEM_WATER = 3,
    SUMMON_SLOT_TOTEM_AIR = 4,
    SUMMON_SLOT_MINIPET = 5,
    SUMMON_SLOT_QUEST = 6,

    MAX_SUMMON_SLOT
};

#define MAX_TOTEM_SLOT      5
#define MAX_GAMEOBJECT_SLOT 4

enum EventId
{
    EVENT_CHARGE            = 1003,

    /// Special charge event which is used for charge spells that have explicit targets
    /// and had a path already generated - using it in PointMovementGenerator will not
    /// create a new spline and launch it
    EVENT_CHARGE_PREPATH    = 1005,
};

enum ResponseCodes
{
    RESPONSE_SUCCESS                                       = 0x00,
    RESPONSE_FAILURE                                       = 0x01,
    RESPONSE_CANCELLED                                     = 0x02,
    RESPONSE_DISCONNECTED                                  = 0x03,
    RESPONSE_FAILED_TO_CONNECT                             = 0x04,
    RESPONSE_CONNECTED                                     = 0x05,
    RESPONSE_VERSION_MISMATCH                              = 0x06,

    CSTATUS_CONNECTING                                     = 0x07,
    CSTATUS_NEGOTIATING_SECURITY                           = 0x08,
    CSTATUS_NEGOTIATION_COMPLETE                           = 0x09,
    CSTATUS_NEGOTIATION_FAILED                             = 0x0A,
    CSTATUS_AUTHENTICATING                                 = 0x0B,

    AUTH_OK                                                = 0x0C,
    AUTH_FAILED                                            = 0x0D,
    AUTH_REJECT                                            = 0x0E,
    AUTH_BAD_SERVER_PROOF                                  = 0x0F,
    AUTH_UNAVAILABLE                                       = 0x10,
    AUTH_SYSTEM_ERROR                                      = 0x11,
    AUTH_BILLING_ERROR                                     = 0x12,
    AUTH_BILLING_EXPIRED                                   = 0x13,
    AUTH_VERSION_MISMATCH                                  = 0x14,
    AUTH_UNKNOWN_ACCOUNT                                   = 0x15,
    AUTH_INCORRECT_PASSWORD                                = 0x16,
    AUTH_SESSION_EXPIRED                                   = 0x17,
    AUTH_SERVER_SHUTTING_DOWN                              = 0x18,
    AUTH_ALREADY_LOGGING_IN                                = 0x19,
    AUTH_LOGIN_SERVER_NOT_FOUND                            = 0x1A,
    AUTH_WAIT_QUEUE                                        = 0x1B,
    AUTH_BANNED                                            = 0x1C,
    AUTH_ALREADY_ONLINE                                    = 0x1D,
    AUTH_NO_TIME                                           = 0x1E,
    AUTH_DB_BUSY                                           = 0x1F,
    AUTH_SUSPENDED                                         = 0x20,
    AUTH_PARENTAL_CONTROL                                  = 0x21,
    AUTH_LOCKED_ENFORCED                                   = 0x22,

    REALM_LIST_IN_PROGRESS                                 = 0x23,
    REALM_LIST_SUCCESS                                     = 0x24,
    REALM_LIST_FAILED                                      = 0x25,
    REALM_LIST_INVALID                                     = 0x26,
    REALM_LIST_REALM_NOT_FOUND                             = 0x27,

    ACCOUNT_CREATE_IN_PROGRESS                             = 0x28,
    ACCOUNT_CREATE_SUCCESS                                 = 0x29,
    ACCOUNT_CREATE_FAILED                                  = 0x2A,

    CHAR_LIST_RETRIEVING                                   = 0x2B,
    CHAR_LIST_RETRIEVED                                    = 0x2C,
    CHAR_LIST_FAILED                                       = 0x2D,

    CHAR_CREATE_IN_PROGRESS                                = 0x2E,
    CHAR_CREATE_SUCCESS                                    = 0x2F,
    CHAR_CREATE_ERROR                                      = 0x30,
    CHAR_CREATE_FAILED                                     = 0x31,
    CHAR_CREATE_NAME_IN_USE                                = 0x32,
    CHAR_CREATE_DISABLED                                   = 0x33,
    CHAR_CREATE_PVP_TEAMS_VIOLATION                        = 0x34,
    CHAR_CREATE_SERVER_LIMIT                               = 0x35,
    CHAR_CREATE_ACCOUNT_LIMIT                              = 0x36,
    CHAR_CREATE_SERVER_QUEUE                               = 0x37,
    CHAR_CREATE_ONLY_EXISTING                              = 0x38,
    CHAR_CREATE_EXPANSION                                  = 0x39,
    CHAR_CREATE_EXPANSION_CLASS                            = 0x3A,
    CHAR_CREATE_LEVEL_REQUIREMENT                          = 0x3B,
    CHAR_CREATE_UNIQUE_CLASS_LIMIT                         = 0x3C,
    CHAR_CREATE_CHARACTER_IN_GUILD                         = 0x3D,
    CHAR_CREATE_RESTRICTED_RACECLASS                       = 0x3E,
    CHAR_CREATE_CHARACTER_CHOOSE_RACE                      = 0x3F,
    CHAR_CREATE_CHARACTER_ARENA_LEADER                     = 0x40,
    CHAR_CREATE_CHARACTER_DELETE_MAIL                      = 0x41,
    CHAR_CREATE_CHARACTER_SWAP_FACTION                     = 0x42,
    CHAR_CREATE_CHARACTER_RACE_ONLY                        = 0x43,

    CHAR_CREATE_CHARACTER_GOLD_LIMIT                       = 0x44,

    CHAR_CREATE_FORCE_LOGIN                                = 0x45,

    CHAR_DELETE_IN_PROGRESS                                = 0x46,
    CHAR_DELETE_SUCCESS                                    = 0x47,
    CHAR_DELETE_FAILED                                     = 0x48,
    CHAR_DELETE_FAILED_LOCKED_FOR_TRANSFER                 = 0x49,
    CHAR_DELETE_FAILED_GUILD_LEADER                        = 0x4A,
    CHAR_DELETE_FAILED_ARENA_CAPTAIN                       = 0x4B,

    CHAR_LOGIN_IN_PROGRESS                                 = 0x4C,
    CHAR_LOGIN_SUCCESS                                     = 0x4D,
    CHAR_LOGIN_NO_WORLD                                    = 0x4E,
    CHAR_LOGIN_DUPLICATE_CHARACTER                         = 0x4F,
    CHAR_LOGIN_NO_INSTANCES                                = 0x50,
    CHAR_LOGIN_FAILED                                      = 0x51,
    CHAR_LOGIN_DISABLED                                    = 0x52,
    CHAR_LOGIN_NO_CHARACTER                                = 0x53,
    CHAR_LOGIN_LOCKED_FOR_TRANSFER                         = 0x54,
    CHAR_LOGIN_LOCKED_BY_BILLING                           = 0x55,
    CHAR_LOGIN_LOCKED_BY_MOBILE_AH                         = 0x56,

    CHAR_NAME_SUCCESS                                      = 0x57,
    CHAR_NAME_FAILURE                                      = 0x58,
    CHAR_NAME_NO_NAME                                      = 0x59,
    CHAR_NAME_TOO_SHORT                                    = 0x5A,
    CHAR_NAME_TOO_LONG                                     = 0x5B,
    CHAR_NAME_INVALID_CHARACTER                            = 0x5C,
    CHAR_NAME_MIXED_LANGUAGES                              = 0x5D,
    CHAR_NAME_PROFANE                                      = 0x5E,
    CHAR_NAME_RESERVED                                     = 0x5F,
    CHAR_NAME_INVALID_APOSTROPHE                           = 0x60,
    CHAR_NAME_MULTIPLE_APOSTROPHES                         = 0x61,
    CHAR_NAME_THREE_CONSECUTIVE                            = 0x62,
    CHAR_NAME_INVALID_SPACE                                = 0x63,
    CHAR_NAME_CONSECUTIVE_SPACES                           = 0x64,
    CHAR_NAME_RUSSIAN_CONSECUTIVE_SILENT_CHARACTERS        = 0x65,
    CHAR_NAME_RUSSIAN_SILENT_CHARACTER_AT_BEGINNING_OR_END = 0x66,
    CHAR_NAME_DECLENSION_DOESNT_MATCH_BASE_NAME            = 0x67
};

enum PvPTeamId
{
    PVP_TEAM_HORDE       = 0, // Battleground: Horde,    Arena: Green
    PVP_TEAM_ALLIANCE    = 1, // Battleground: Alliance, Arena: Gold
    PVP_TEAM_NEUTRAL     = 2  // Battleground: Neutral,  Arena: None
};

uint8 constexpr PVP_TEAMS_COUNT = 2;

inline PvPTeamId GetPvPTeamId(TeamId teamId)
{
    if (teamId == TEAM_ALLIANCE)
    {
        return PVP_TEAM_ALLIANCE;
    }

    if (teamId == TEAM_HORDE)
    {
        return PVP_TEAM_HORDE;
    }

    return PVP_TEAM_NEUTRAL;
}

inline TeamId GetTeamId(PvPTeamId teamId)
{
    if (teamId == PVP_TEAM_ALLIANCE)
    {
        return TEAM_ALLIANCE;
    }

    if (teamId == PVP_TEAM_HORDE)
    {
        return TEAM_HORDE;
    }

    return TEAM_NEUTRAL;
}

// indexes of BattlemasterList.dbc
enum BattlegroundTypeId : uint8
{
    BATTLEGROUND_TYPE_NONE     = 0, // None
    BATTLEGROUND_AV            = 1, // Alterac Valley
    BATTLEGROUND_WS            = 2, // Warsong Gulch
    BATTLEGROUND_AB            = 3, // Arathi Basin
    BATTLEGROUND_NA            = 4, // Nagrand Arena
    BATTLEGROUND_BE            = 5, // Blade's Edge Arena
    BATTLEGROUND_AA            = 6, // All Arenas
    BATTLEGROUND_EY            = 7, // Eye of the Storm
    BATTLEGROUND_RL            = 8, // Ruins of Lordaernon
    BATTLEGROUND_SA            = 9, // Strand of the Ancients
    BATTLEGROUND_DS            = 10, // Dalaran Sewers
    BATTLEGROUND_RV            = 11, // Ring of Valor
    BATTLEGROUND_IC            = 30, // Isle of Conquest
    BATTLEGROUND_RB            = 32 // Random Battleground
};

#define MAX_BATTLEGROUND_TYPE_ID 33

enum MailResponseType
{
    MAIL_SEND               = 0,
    MAIL_MONEY_TAKEN        = 1,
    MAIL_ITEM_TAKEN         = 2,
    MAIL_RETURNED_TO_SENDER = 3,
    MAIL_DELETED            = 4,
    MAIL_MADE_PERMANENT     = 5
};

enum MailResponseResult
{
    MAIL_OK                            = 0,
    MAIL_ERR_EQUIP_ERROR               = 1,
    MAIL_ERR_CANNOT_SEND_TO_SELF       = 2,
    MAIL_ERR_NOT_ENOUGH_MONEY          = 3,
    MAIL_ERR_RECIPIENT_NOT_FOUND       = 4,
    MAIL_ERR_NOT_YOUR_TEAM             = 5,
    MAIL_ERR_INTERNAL_ERROR            = 6,
    MAIL_ERR_DISABLED_FOR_TRIAL_ACC    = 14,
    MAIL_ERR_RECIPIENT_CAP_REACHED     = 15,
    MAIL_ERR_CANT_SEND_WRAPPED_COD     = 16,
    MAIL_ERR_MAIL_AND_CHAT_SUSPENDED   = 17,
    MAIL_ERR_TOO_MANY_ATTACHMENTS      = 18,
    MAIL_ERR_MAIL_ATTACHMENT_INVALID   = 19,
    MAIL_ERR_ITEM_HAS_EXPIRED          = 21,
};

enum SpellFamilyNames
{
    SPELLFAMILY_GENERIC     = 0,
    SPELLFAMILY_UNK1        = 1,                            // events, holidays
    // 2 - unused
    SPELLFAMILY_MAGE        = 3,
    SPELLFAMILY_WARRIOR     = 4,
    SPELLFAMILY_WARLOCK     = 5,
    SPELLFAMILY_PRIEST      = 6,
    SPELLFAMILY_DRUID       = 7,
    SPELLFAMILY_ROGUE       = 8,
    SPELLFAMILY_HUNTER      = 9,
    SPELLFAMILY_PALADIN     = 10,
    SPELLFAMILY_SHAMAN      = 11,
    SPELLFAMILY_UNK2        = 12,                           // 2 spells (silence resistance)
    SPELLFAMILY_POTION      = 13,
    // 14 - unused
    SPELLFAMILY_DEATHKNIGHT = 15,
    // 16 - unused
    SPELLFAMILY_PET         = 17
};

enum TradeStatus
{
    TRADE_STATUS_BUSY           = 0,
    TRADE_STATUS_BEGIN_TRADE    = 1,
    TRADE_STATUS_OPEN_WINDOW    = 2,
    TRADE_STATUS_TRADE_CANCELED = 3,
    TRADE_STATUS_TRADE_ACCEPT   = 4,
    TRADE_STATUS_BUSY_2         = 5,
    TRADE_STATUS_NO_TARGET      = 6,
    TRADE_STATUS_BACK_TO_TRADE  = 7,
    TRADE_STATUS_TRADE_COMPLETE = 8,
    // 9?
    TRADE_STATUS_TARGET_TO_FAR  = 10,
    TRADE_STATUS_WRONG_FACTION  = 11,
    TRADE_STATUS_CLOSE_WINDOW   = 12,
    // 13?
    TRADE_STATUS_IGNORE_YOU     = 14,
    TRADE_STATUS_YOU_STUNNED    = 15,
    TRADE_STATUS_TARGET_STUNNED = 16,
    TRADE_STATUS_YOU_DEAD       = 17,
    TRADE_STATUS_TARGET_DEAD    = 18,
    TRADE_STATUS_YOU_LOGOUT     = 19,
    TRADE_STATUS_TARGET_LOGOUT  = 20,
    TRADE_STATUS_TRIAL_ACCOUNT  = 21,                       // Trial accounts can not perform that action
    TRADE_STATUS_ONLY_CONJURED  = 22,                       // You can only trade conjured items... (cross realm BG related).
    TRADE_STATUS_NOT_ELIGIBLE   = 23                        // Related to trading soulbound loot items
};

enum XPColorChar : uint8
{
    XP_RED,
    XP_ORANGE,
    XP_YELLOW,
    XP_GREEN,
    XP_GRAY
};

enum RemoveMethod : uint8
{
    GROUP_REMOVEMETHOD_DEFAULT  = 0,
    GROUP_REMOVEMETHOD_KICK     = 1,
    GROUP_REMOVEMETHOD_LEAVE    = 2,
    GROUP_REMOVEMETHOD_KICK_LFG = 3
};

enum ActivateTaxiReply
{
    ERR_TAXIOK                      = 0,
    ERR_TAXIUNSPECIFIEDSERVERERROR  = 1,
    ERR_TAXINOSUCHPATH              = 2,
    ERR_TAXINOTENOUGHMONEY          = 3,
    ERR_TAXITOOFARAWAY              = 4,
    ERR_TAXINOVENDORNEARBY          = 5,
    ERR_TAXINOTVISITED              = 6,
    ERR_TAXIPLAYERBUSY              = 7,
    ERR_TAXIPLAYERALREADYMOUNTED    = 8,
    ERR_TAXIPLAYERSHAPESHIFTED      = 9,
    ERR_TAXIPLAYERMOVING            = 10,
    ERR_TAXISAMENODE                = 11,
    ERR_TAXINOTSTANDING             = 12
};

enum DuelCompleteType
{
    DUEL_INTERRUPTED = 0,
    DUEL_WON         = 1,
    DUEL_FLED        = 2
};

// handle the queue types and bg types separately to enable joining queue for different sized arenas at the same time
enum BattlegroundQueueTypeId : uint8
{
    BATTLEGROUND_QUEUE_NONE      = 0,
    BATTLEGROUND_QUEUE_AV        = 1,
    BATTLEGROUND_QUEUE_WS        = 2,
    BATTLEGROUND_QUEUE_AB        = 3,
    BATTLEGROUND_QUEUE_EY        = 4,
    BATTLEGROUND_QUEUE_SA        = 5,
    BATTLEGROUND_QUEUE_IC        = 6,
    BATTLEGROUND_QUEUE_RB        = 7,
    BATTLEGROUND_QUEUE_2v2       = 8,
    BATTLEGROUND_QUEUE_3v3       = 9,
    BATTLEGROUND_QUEUE_5v5       = 10,
    MAX_BATTLEGROUND_QUEUE_TYPES = 20,
};

enum GroupJoinBattlegroundResult
{
    // positive values are indexes in BattlemasterList.dbc
    ERR_GROUP_JOIN_BATTLEGROUND_FAIL        = 0,            // Your group has joined a battleground queue, but you are not eligible (showed for non existing BattlemasterList.dbc indexes)
    ERR_BATTLEGROUND_NONE                   = -1,           // not show anything
    ERR_GROUP_JOIN_BATTLEGROUND_DESERTERS   = -2,           // You cannot join the battleground yet because you or one of your party members is flagged as a Deserter.
    ERR_ARENA_TEAM_PARTY_SIZE               = -3,           // Incorrect party size for this arena.
    ERR_BATTLEGROUND_TOO_MANY_QUEUES        = -4,           // You can only be queued for 2 battles at once
    ERR_BATTLEGROUND_CANNOT_QUEUE_FOR_RATED = -5,           // You cannot queue for a rated match while queued for other battles
    ERR_BATTLEGROUND_QUEUED_FOR_RATED       = -6,           // You cannot queue for another battle while queued for a rated arena match
    ERR_BATTLEGROUND_TEAM_LEFT_QUEUE        = -7,           // Your team has left the arena queue
    ERR_BATTLEGROUND_NOT_IN_BATTLEGROUND    = -8,           // You can't do that in a battleground.
    ERR_BATTLEGROUND_JOIN_XP_GAIN           = -9,           // doesn't exist in client...
    ERR_BATTLEGROUND_JOIN_RANGE_INDEX       = -10,          // Cannot join the queue unless all members of your party are in the same battleground level range.
    ERR_BATTLEGROUND_JOIN_TIMED_OUT         = -11,          // %s was unavailable to join the queue. (ObjectGuid guid exist in client cache)
    ERR_BATTLEGROUND_JOIN_FAILED            = -12,          // Join as a group failed (ObjectGuid guid doesn't exist in client cache)
    ERR_LFG_CANT_USE_BATTLEGROUND           = -13,          // You cannot queue for a battleground or arena while using the dungeon system.
    ERR_IN_RANDOM_BG                        = -14,          // Can't do that while in a Random Battleground queue.
    ERR_IN_NON_RANDOM_BG                    = -15           // Can't queue for Random Battleground while in another Battleground queue.
};

enum PetNameInvalidReason
{
    // custom, not send
    PET_NAME_SUCCESS                                        = 0,

    PET_NAME_INVALID                                        = 1,
    PET_NAME_NO_NAME                                        = 2,
    PET_NAME_TOO_SHORT                                      = 3,
    PET_NAME_TOO_LONG                                       = 4,
    PET_NAME_MIXED_LANGUAGES                                = 6,
    PET_NAME_PROFANE                                        = 7,
    PET_NAME_RESERVED                                       = 8,
    PET_NAME_THREE_CONSECUTIVE                              = 11,
    PET_NAME_INVALID_SPACE                                  = 12,
    PET_NAME_CONSECUTIVE_SPACES                             = 13,
    PET_NAME_RUSSIAN_CONSECUTIVE_SILENT_CHARACTERS          = 14,
    PET_NAME_RUSSIAN_SILENT_CHARACTER_AT_BEGINNING_OR_END   = 15,
    PET_NAME_DECLENSION_DOESNT_MATCH_BASE_NAME              = 16
};

enum PetTameFailure
{
    PET_TAME_INVALID_CREATURE       = 1,
    PET_TAME_TOO_MANY               = 2,
    PET_TAME_CREATURE_ALREADY_OWNED = 3,
    PET_TAME_NOT_TAMEABLE           = 4,
    PET_TAME_ANOTHER_SUMMON_ACTIVE  = 5,
    PET_TAME_UNITS_CANT_TAME        = 6,
    PET_TAME_NOPET_AVAILABLE        = 7,
    PET_TAME_INTERNAL_ERROR         = 8,
    PET_TAME_TOO_HIGHLEVEL          = 9,
    PET_TAME_DEAD                   = 10,
    PET_TAME_NOTDEAD                = 11,
    PET_TAME_CANT_CONTROL_EXOTIC    = 12,
    PET_TAME_UNKNOWNERROR           = 13
};

enum DungeonStatusFlag
{
    DUNGEON_STATUSFLAG_NORMAL = 0x01,
    DUNGEON_STATUSFLAG_HEROIC = 0x02,

    RAID_STATUSFLAG_10MAN_NORMAL = 0x01,
    RAID_STATUSFLAG_25MAN_NORMAL = 0x02,
    RAID_STATUSFLAG_10MAN_HEROIC = 0x04,
    RAID_STATUSFLAG_25MAN_HEROIC = 0x08
};

enum PartyResult
{
    ERR_PARTY_RESULT_OK                 = 0,
    ERR_BAD_PLAYER_NAME_S               = 1,
    ERR_TARGET_NOT_IN_GROUP_S           = 2,
    ERR_TARGET_NOT_IN_INSTANCE_S        = 3,
    ERR_GROUP_FULL                      = 4,
    ERR_ALREADY_IN_GROUP_S              = 5,
    ERR_NOT_IN_GROUP                    = 6,
    ERR_NOT_LEADER                      = 7,
    ERR_PLAYER_WRONG_FACTION            = 8,
    ERR_IGNORING_YOU_S                  = 9,
    ERR_LFG_PENDING                     = 12,
    ERR_INVITE_RESTRICTED               = 13,
    ERR_GROUP_SWAP_FAILED               = 14,               // if (PartyOperation == PARTY_OP_SWAP) ERR_GROUP_SWAP_FAILED else ERR_INVITE_IN_COMBAT
    ERR_INVITE_UNKNOWN_REALM            = 15,
    ERR_INVITE_NO_PARTY_SERVER          = 16,
    ERR_INVITE_PARTY_BUSY               = 17,
    ERR_PARTY_TARGET_AMBIGUOUS          = 18,
    ERR_PARTY_LFG_INVITE_RAID_LOCKED    = 19,
    ERR_PARTY_LFG_BOOT_LIMIT            = 20,
    ERR_PARTY_LFG_BOOT_COOLDOWN_S       = 21,
    ERR_PARTY_LFG_BOOT_IN_PROGRESS      = 22,
    ERR_PARTY_LFG_BOOT_TOO_FEW_PLAYERS  = 23,
    ERR_PARTY_LFG_BOOT_NOT_ELIGIBLE_S   = 24,
    ERR_RAID_DISALLOWED_BY_LEVEL        = 25,
    ERR_PARTY_LFG_BOOT_IN_COMBAT        = 26,
    ERR_VOTE_KICK_REASON_NEEDED         = 27,
    ERR_PARTY_LFG_BOOT_DUNGEON_COMPLETE = 28,
    ERR_PARTY_LFG_BOOT_LOOT_ROLLS       = 29,
    ERR_PARTY_LFG_TELEPORT_IN_COMBAT    = 30
};

enum ServerProcessTypes
{
    SERVER_PROCESS_AUTHSERVER = 0,
    SERVER_PROCESS_WORLDSERVER = 1,

    NUM_SERVER_PROCESS_TYPES
};

// Login Failure Reasons
enum class LoginFailureReason : uint8
{
    Failed             = 0,
    NoWorld            = 1,
    DuplicateCharacter = 2,
    NoInstances        = 3,
    Disabled           = 4,
    NoCharacter        = 5,
    LockedForTransfer  = 6,
    LockedByBilling    = 7
};

namespace Acore::Impl
{
    struct AC_SHARED_API CurrentServerProcessHolder
    {
        static ServerProcessTypes type() { return _type; }
        static ServerProcessTypes _type;
    };
}

#define THIS_SERVER_PROCESS (Acore::Impl::CurrentServerProcessHolder::type())

#endif
