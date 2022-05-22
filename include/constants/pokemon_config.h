#ifndef GUARD_CONSTANTS_POKEMON_CONFIG_H
#define GUARD_CONSTANTS_POKEMON_CONFIG_H

#include "constants/expansion_branches.h"

#ifndef GEN_3
#define GEN_3 0
#define GEN_4 1
#define GEN_5 2
#define GEN_6 3
#define GEN_7 4
#define GEN_8 5
#endif

#define P_UPDATED_TYPES         GEN_8 // In Gen6+, several Pokémon were changed to be partially or fully Fairy type.
#define P_UPDATED_STATS         GEN_8 // Since Gen 6, Pokémon stats are updated with each passing generation.
#define P_UPDATED_ABILITIES     GEN_8 // Since Gen 6, certain Pokémon have their abilities changed. Requires BATTLE_ENGINE for Gen4+ abilities.
#define P_UPDATED_EGG_GROUPS    GEN_8 // Since Gen 8, certain Pokémon have gained new egg groups.
#define P_SHEDINJA_BALL         GEN_8 // Since Gen 4, Shedinja requires a Poké Ball for its evolution. In Gen 3, Shedinja inherits Nincada's Ball.
#define P_LEGENDARY_PERFECT_IVS GEN_8 // Since Gen 6, Legendaries, Mythicals and Ultra Beasts found in the wild or given through gifts have at least 3 perfect IVs.
#define P_KADABRA_EVERSTONE     GEN_8 // Since Gen 4, Kadabra can evolve even when holding an Everstone.

#define P_ENABLE_DEBUG          TRUE  // Enables a debug menu for pokemon sprites and icons, accessed by pressing SELECT in the summary screen.

#ifndef ITEM_EXPANSION
//Item Definitions for gEvolutionTable

    //EVO_MEGA_EVOLUTION
    #define ITEM_VENUSAURITE         10001
    #define ITEM_CHARIZARDITE_X      10002
    #define ITEM_CHARIZARDITE_Y      10003
    #define ITEM_BLASTOISINITE       10004
    #define ITEM_BEEDRILLITE         10005
    #define ITEM_PIDGEOTITE          10006
    #define ITEM_ALAKAZITE           10007
    #define ITEM_SLOWBRONITE         10008
    #define ITEM_GENGARITE           10009
    #define ITEM_KANGASKHANITE       10010
    #define ITEM_PINSIRITE           10011
    #define ITEM_GYARADOSITE         10012
    #define ITEM_AERODACTYLITE       10013
    #define ITEM_MEWTWONITE_X        10014
    #define ITEM_MEWTWONITE_Y        10015
    #define ITEM_AMPHAROSITE         10016
    #define ITEM_STEELIXITE          10017
    #define ITEM_SCIZORITE           10018
    #define ITEM_HERACRONITE         10019
    #define ITEM_HOUNDOOMINITE       10020
    #define ITEM_TYRANITARITE        10021
    #define ITEM_SCEPTILITE          10022
    #define ITEM_BLAZIKENITE         10023
    #define ITEM_SWAMPERTITE         10024
    #define ITEM_SABLENITE           10025
    #define ITEM_SHARPEDONITE        10026
    #define ITEM_MANECTITE           10027
    #define ITEM_CAMERUPTITE         10028
    #define ITEM_GLALITITE           10029
    #define ITEM_MAWILITE            10030
    #define ITEM_MEDICHAMITE         10031
    #define ITEM_ALTARIANITE         10032
    #define ITEM_ABSOLITE            10033
    #define ITEM_BANETTITE           10034
    #define ITEM_AGGRONITE           10035
    #define ITEM_GARDEVOIRITE        10036
    #define ITEM_SALAMENCITE         10037
    #define ITEM_METAGROSSITE        10038
    #define ITEM_LATIASITE           10039
    #define ITEM_LATIOSITE           10040
    #define ITEM_LOPUNNITE           10041
    #define ITEM_GARCHOMPITE         10042
    #define ITEM_LUCARIONITE         10043
    #define ITEM_ABOMASITE           10044
    #define ITEM_GALLADITE           10045
    #define ITEM_AUDINITE            10046
    #define ITEM_DIANCITE            10047

    //EVO_TRADE_ITEM
    #define ITEM_PROTECTOR           10048
    #define ITEM_ELECTIRIZER         10049
    #define ITEM_MAGMARIZER          10050
    #define ITEM_DUBIOUS_DISC        10051
    #define ITEM_PRISM_SCALE         10052
    #define ITEM_REAPER_CLOTH        10053
    #define ITEM_SACHET              10054
    #define ITEM_WHIPPED_DREAM       10055

    //EVO_ITEM
    #define ITEM_ICE_STONE           10056
    #define ITEM_SHINY_STONE         10057
    #define ITEM_DUSK_STONE          10058
    #define ITEM_DAWN_STONE          10059
    #define ITEM_TART_APPLE          10060
    #define ITEM_SWEET_APPLE         10061
    #define ITEM_CRACKED_POT         10062
    #define ITEM_GALARICA_CUFF       10063
    #define ITEM_GALARICA_WREATH     10064
    #define ITEM_CHIPPED_POT         10065

    //EVO_ITEM_HOLD
    #define ITEM_RAZOR_FANG          10066
    #define ITEM_RAZOR_CLAW          10067
    #define ITEM_OVAL_STONE          10068

    //FORM_ITEM_HOLD
    #define ITEM_GRISEOUS_ORB        10069
    #define ITEM_DRACO_PLATE         10070
    #define ITEM_DREAD_PLATE         10071
    #define ITEM_EARTH_PLATE         10072
    #define ITEM_FIST_PLATE          10073
    #define ITEM_FLAME_PLATE         10074
    #define ITEM_ICICLE_PLATE        10075
    #define ITEM_INSECT_PLATE        10076
    #define ITEM_IRON_PLATE          10077
    #define ITEM_MEADOW_PLATE        10078
    #define ITEM_MIND_PLATE          10079
    #define ITEM_PIXIE_PLATE         10080
    #define ITEM_SKY_PLATE           10081
    #define ITEM_SPLASH_PLATE        10082
    #define ITEM_SPOOKY_PLATE        10083
    #define ITEM_STONE_PLATE         10084
    #define ITEM_TOXIC_PLATE         10085
    #define ITEM_ZAP_PLATE           10086
    #define ITEM_FIGHTINIUM_Z        10087
    #define ITEM_FLYINIUM_Z          10088
    #define ITEM_POISONIUM_Z         10089
    #define ITEM_GROUNDIUM_Z         10090
    #define ITEM_ROCKIUM_Z           10091
    #define ITEM_BUGINIUM_Z          10092
    #define ITEM_GHOSTIUM_Z          10093
    #define ITEM_STEELIUM_Z          10094
    #define ITEM_FIRIUM_Z            10095
    #define ITEM_WATERIUM_Z          10096
    #define ITEM_GRASSIUM_Z          10097
    #define ITEM_ELECTRIUM_Z         10098
    #define ITEM_PSYCHIUM_Z          10099
    #define ITEM_ICIUM_Z             10100
    #define ITEM_DRAGONIUM_Z         10101
    #define ITEM_DARKINIUM_Z         10102
    #define ITEM_FAIRIUM_Z           10103
    #define ITEM_DOUSE_DRIVE         10104
    #define ITEM_SHOCK_DRIVE         10105
    #define ITEM_BURN_DRIVE          10106
    #define ITEM_CHILL_DRIVE         10107
    #define ITEM_BUG_MEMORY          10108
    #define ITEM_DARK_MEMORY         10109
    #define ITEM_DRAGON_MEMORY       10110
    #define ITEM_ELECTRIC_MEMORY     10111
    #define ITEM_FAIRY_MEMORY        10112
    #define ITEM_FIGHTING_MEMORY     10113
    #define ITEM_FIRE_MEMORY         10114
    #define ITEM_FLYING_MEMORY       10115
    #define ITEM_GHOST_MEMORY        10116
    #define ITEM_GRASS_MEMORY        10117
    #define ITEM_GROUND_MEMORY       10118
    #define ITEM_ICE_MEMORY          10119
    #define ITEM_POISON_MEMORY       10120
    #define ITEM_PSYCHIC_MEMORY      10121
    #define ITEM_ROCK_MEMORY         10122
    #define ITEM_STEEL_MEMORY        10123
    #define ITEM_WATER_MEMORY        10124

    //FORM_ITEM_USE
    #define ITEM_GRACIDEA            10125
    #define ITEM_REVEAL_GLASS        10126
    #define ITEM_PRISON_BOTTLE       10127
    #define ITEM_RED_NECTAR          10128
    #define ITEM_YELLOW_NECTAR       10129
    #define ITEM_PINK_NECTAR         10130
    #define ITEM_PURPLE_NECTAR       10131
#endif // ITEM_EXPANSION

#ifndef BATTLE_ENGINE
    // Gen 4
    #define ABILITY_TANGLED_FEET ABILITY_NONE
    #define ABILITY_MOTOR_DRIVE ABILITY_NONE
    #define ABILITY_RIVALRY ABILITY_NONE
    #define ABILITY_STEADFAST ABILITY_NONE
    #define ABILITY_SNOW_CLOAK ABILITY_NONE
    #define ABILITY_GLUTTONY ABILITY_NONE
    #define ABILITY_ANGER_POINT ABILITY_NONE
    #define ABILITY_UNBURDEN ABILITY_NONE
    #define ABILITY_HEATPROOF ABILITY_NONE
    #define ABILITY_SIMPLE ABILITY_NONE
    #define ABILITY_DRY_SKIN ABILITY_NONE
    #define ABILITY_DOWNLOAD ABILITY_NONE
    #define ABILITY_IRON_FIST ABILITY_NONE
    #define ABILITY_POISON_HEAL ABILITY_NONE
    #define ABILITY_ADAPTABILITY ABILITY_NONE
    #define ABILITY_SKILL_LINK ABILITY_NONE
    #define ABILITY_HYDRATION ABILITY_NONE
    #define ABILITY_SOLAR_POWER ABILITY_NONE
    #define ABILITY_QUICK_FEET ABILITY_NONE
    #define ABILITY_NORMALIZE ABILITY_NONE
    #define ABILITY_SNIPER ABILITY_NONE
    #define ABILITY_MAGIC_GUARD ABILITY_NONE
    #define ABILITY_NO_GUARD ABILITY_NONE
    #define ABILITY_STALL ABILITY_NONE
    #define ABILITY_TECHNICIAN ABILITY_NONE
    #define ABILITY_LEAF_GUARD ABILITY_NONE
    #define ABILITY_KLUTZ ABILITY_NONE
    #define ABILITY_MOLD_BREAKER ABILITY_NONE
    #define ABILITY_SUPER_LUCK ABILITY_NONE
    #define ABILITY_AFTERMATH ABILITY_NONE
    #define ABILITY_ANTICIPATION ABILITY_NONE
    #define ABILITY_FOREWARN ABILITY_NONE
    #define ABILITY_UNAWARE ABILITY_NONE
    #define ABILITY_TINTED_LENS ABILITY_NONE
    #define ABILITY_FILTER ABILITY_NONE
    #define ABILITY_SLOW_START ABILITY_NONE
    #define ABILITY_SCRAPPY ABILITY_NONE
    #define ABILITY_STORM_DRAIN ABILITY_NONE
    #define ABILITY_ICE_BODY ABILITY_NONE
    #define ABILITY_SOLID_ROCK ABILITY_NONE
    #define ABILITY_SNOW_WARNING ABILITY_NONE
    #define ABILITY_HONEY_GATHER ABILITY_NONE
    #define ABILITY_FRISK ABILITY_NONE
    #define ABILITY_RECKLESS ABILITY_NONE
    #define ABILITY_MULTITYPE ABILITY_NONE
    #define ABILITY_FLOWER_GIFT ABILITY_NONE
    #define ABILITY_BAD_DREAMS ABILITY_NONE
    // Gen 5
    #define ABILITY_PICKPOCKET ABILITY_NONE
    #define ABILITY_SHEER_FORCE ABILITY_NONE
    #define ABILITY_CONTRARY ABILITY_NONE
    #define ABILITY_UNNERVE ABILITY_NONE
    #define ABILITY_DEFIANT ABILITY_NONE
    #define ABILITY_DEFEATIST ABILITY_NONE
    #define ABILITY_CURSED_BODY ABILITY_NONE
    #define ABILITY_HEALER ABILITY_NONE
    #define ABILITY_FRIEND_GUARD ABILITY_NONE
    #define ABILITY_WEAK_ARMOR ABILITY_NONE
    #define ABILITY_HEAVY_METAL ABILITY_NONE
    #define ABILITY_LIGHT_METAL ABILITY_NONE
    #define ABILITY_MULTISCALE ABILITY_NONE
    #define ABILITY_TOXIC_BOOST ABILITY_NONE
    #define ABILITY_FLARE_BOOST ABILITY_NONE
    #define ABILITY_HARVEST ABILITY_NONE
    #define ABILITY_TELEPATHY ABILITY_NONE
    #define ABILITY_MOODY ABILITY_NONE
    #define ABILITY_OVERCOAT ABILITY_NONE
    #define ABILITY_POISON_TOUCH ABILITY_NONE
    #define ABILITY_REGENERATOR ABILITY_NONE
    #define ABILITY_BIG_PECKS ABILITY_NONE
    #define ABILITY_SAND_RUSH ABILITY_NONE
    #define ABILITY_WONDER_SKIN ABILITY_NONE
    #define ABILITY_ANALYTIC ABILITY_NONE
    #define ABILITY_ILLUSION ABILITY_NONE
    #define ABILITY_IMPOSTER ABILITY_NONE
    #define ABILITY_INFILTRATOR ABILITY_NONE
    #define ABILITY_MUMMY ABILITY_NONE
    #define ABILITY_MOXIE ABILITY_NONE
    #define ABILITY_JUSTIFIED ABILITY_NONE
    #define ABILITY_RATTLED ABILITY_NONE
    #define ABILITY_MAGIC_BOUNCE ABILITY_NONE
    #define ABILITY_SAP_SIPPER ABILITY_NONE
    #define ABILITY_PRANKSTER ABILITY_NONE
    #define ABILITY_SAND_FORCE ABILITY_NONE
    #define ABILITY_IRON_BARBS ABILITY_NONE
    #define ABILITY_ZEN_MODE ABILITY_NONE
    #define ABILITY_VICTORY_STAR ABILITY_NONE
    #define ABILITY_TURBOBLAZE ABILITY_NONE
    #define ABILITY_TERAVOLT ABILITY_NONE
    // Gen 6
    #define ABILITY_AROMA_VEIL ABILITY_NONE
    #define ABILITY_FLOWER_VEIL ABILITY_NONE
    #define ABILITY_CHEEK_POUCH ABILITY_NONE
    #define ABILITY_PROTEAN ABILITY_NONE
    #define ABILITY_FUR_COAT ABILITY_NONE
    #define ABILITY_MAGICIAN ABILITY_NONE
    #define ABILITY_BULLETPROOF ABILITY_NONE
    #define ABILITY_COMPETITIVE ABILITY_NONE
    #define ABILITY_STRONG_JAW ABILITY_NONE
    #define ABILITY_REFRIGERATE ABILITY_NONE
    #define ABILITY_SWEET_VEIL ABILITY_NONE
    #define ABILITY_STANCE_CHANGE ABILITY_NONE
    #define ABILITY_GALE_WINGS ABILITY_NONE
    #define ABILITY_MEGA_LAUNCHER ABILITY_NONE
    #define ABILITY_GRASS_PELT ABILITY_NONE
    #define ABILITY_SYMBIOSIS ABILITY_NONE
    #define ABILITY_TOUGH_CLAWS ABILITY_NONE
    #define ABILITY_PIXILATE ABILITY_NONE
    #define ABILITY_GOOEY ABILITY_NONE
    #define ABILITY_AERILATE ABILITY_NONE
    #define ABILITY_PARENTAL_BOND ABILITY_NONE
    #define ABILITY_DARK_AURA ABILITY_NONE
    #define ABILITY_FAIRY_AURA ABILITY_NONE
    #define ABILITY_AURA_BREAK ABILITY_NONE
    #define ABILITY_PRIMORDIAL_SEA ABILITY_NONE
    #define ABILITY_DESOLATE_LAND ABILITY_NONE
    #define ABILITY_DELTA_STREAM ABILITY_NONE
    // Gen 7
    #define ABILITY_STAMINA ABILITY_NONE
    #define ABILITY_WIMP_OUT ABILITY_NONE
    #define ABILITY_EMERGENCY_EXIT ABILITY_NONE
    #define ABILITY_WATER_COMPACTION ABILITY_NONE
    #define ABILITY_MERCILESS ABILITY_NONE
    #define ABILITY_SHIELDS_DOWN ABILITY_NONE
    #define ABILITY_STAKEOUT ABILITY_NONE
    #define ABILITY_WATER_BUBBLE ABILITY_NONE
    #define ABILITY_STEELWORKER ABILITY_NONE
    #define ABILITY_BERSERK ABILITY_NONE
    #define ABILITY_SLUSH_RUSH ABILITY_NONE
    #define ABILITY_LONG_REACH ABILITY_NONE
    #define ABILITY_LIQUID_VOICE ABILITY_NONE
    #define ABILITY_TRIAGE ABILITY_NONE
    #define ABILITY_GALVANIZE ABILITY_NONE
    #define ABILITY_SURGE_SURFER ABILITY_NONE
    #define ABILITY_SCHOOLING ABILITY_NONE
    #define ABILITY_DISGUISE ABILITY_NONE
    #define ABILITY_BATTLE_BOND ABILITY_NONE
    #define ABILITY_POWER_CONSTRUCT ABILITY_NONE
    #define ABILITY_CORROSION ABILITY_NONE
    #define ABILITY_COMATOSE ABILITY_NONE
    #define ABILITY_QUEENLY_MAJESTY ABILITY_NONE
    #define ABILITY_INNARDS_OUT ABILITY_NONE
    #define ABILITY_DANCER ABILITY_NONE
    #define ABILITY_BATTERY ABILITY_NONE
    #define ABILITY_FLUFFY ABILITY_NONE
    #define ABILITY_DAZZLING ABILITY_NONE
    #define ABILITY_SOUL_HEART ABILITY_NONE
    #define ABILITY_TANGLING_HAIR ABILITY_NONE
    #define ABILITY_RECEIVER ABILITY_NONE
    #define ABILITY_POWER_OF_ALCHEMY ABILITY_NONE
    #define ABILITY_BEAST_BOOST ABILITY_NONE
    #define ABILITY_RKS_SYSTEM ABILITY_NONE
    #define ABILITY_ELECTRIC_SURGE ABILITY_NONE
    #define ABILITY_PSYCHIC_SURGE ABILITY_NONE
    #define ABILITY_MISTY_SURGE ABILITY_NONE
    #define ABILITY_GRASSY_SURGE ABILITY_NONE
    #define ABILITY_FULL_METAL_BODY ABILITY_NONE
    #define ABILITY_SHADOW_SHIELD ABILITY_NONE
    #define ABILITY_PRISM_ARMOR ABILITY_NONE
    #define ABILITY_NEUROFORCE ABILITY_NONE
    // Gen 8
    #define ABILITY_INTREPID_SWORD ABILITY_NONE
    #define ABILITY_DAUNTLESS_SHIELD ABILITY_NONE
    #define ABILITY_LIBERO ABILITY_NONE
    #define ABILITY_BALL_FETCH ABILITY_NONE
    #define ABILITY_COTTON_DOWN ABILITY_NONE
    #define ABILITY_PROPELLER_TAIL ABILITY_NONE
    #define ABILITY_MIRROR_ARMOR ABILITY_NONE
    #define ABILITY_GULP_MISSILE ABILITY_NONE
    #define ABILITY_STALWART ABILITY_NONE
    #define ABILITY_STEAM_ENGINE ABILITY_NONE
    #define ABILITY_PUNK_ROCK ABILITY_NONE
    #define ABILITY_SAND_SPIT ABILITY_NONE
    #define ABILITY_ICE_SCALES ABILITY_NONE
    #define ABILITY_RIPEN ABILITY_NONE
    #define ABILITY_ICE_FACE ABILITY_NONE
    #define ABILITY_POWER_SPOT ABILITY_NONE
    #define ABILITY_MIMICRY ABILITY_NONE
    #define ABILITY_SCREEN_CLEANER ABILITY_NONE
    #define ABILITY_STEELY_SPIRIT ABILITY_NONE
    #define ABILITY_PERISH_BODY ABILITY_NONE
    #define ABILITY_WANDERING_SPIRIT ABILITY_NONE
    #define ABILITY_GORILLA_TACTICS ABILITY_NONE
    #define ABILITY_NEUTRALIZING_GAS ABILITY_NONE
    #define ABILITY_PASTEL_VEIL ABILITY_NONE
    #define ABILITY_HUNGER_SWITCH ABILITY_NONE
    #define ABILITY_QUICK_DRAW ABILITY_NONE
    #define ABILITY_UNSEEN_FIST ABILITY_NONE
    #define ABILITY_CURIOUS_MEDICINE ABILITY_NONE
    #define ABILITY_TRANSISTOR ABILITY_NONE
    #define ABILITY_DRAGONS_MAW ABILITY_NONE
    #define ABILITY_CHILLING_NEIGH ABILITY_NONE
    #define ABILITY_GRIM_NEIGH ABILITY_NONE
    #define ABILITY_AS_ONE_ICE_RIDER ABILITY_NONE
    #define ABILITY_AS_ONE_SHADOW_RIDER ABILITY_NONE
#endif // BATTLE_ENGINE

#endif // GUARD_CONSTANTS_POKEMON_CONFIG_H
