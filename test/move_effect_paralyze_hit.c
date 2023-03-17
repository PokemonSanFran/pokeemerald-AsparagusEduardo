#include "global.h"
#include "test_battle.h"

ASSUMPTIONS
{
    ASSUME(gBattleMoves[MOVE_THUNDER_SHOCK].effect == EFFECT_PARALYZE_HIT);
}

SINGLE_BATTLE_TEST("Thunder Shock inflicts paralysis")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_THUNDER_SHOCK); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_THUNDER_SHOCK, player);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PRZ, opponent);
        STATUS_ICON(opponent, paralysis: TRUE);
    }
}

#if B_PARALYZE_ELECTRIC >= GEN_6
SINGLE_BATTLE_TEST("Thunder Shock cannot paralyze an Electric-type in Gen 6+")
#else
SINGLE_BATTLE_TEST("Thunder Shock can paralyze an Electric-type before Gen 6")
#endif
{
    GIVEN {
        ASSUME(gSpeciesInfo[SPECIES_PIKACHU].types[0] == TYPE_ELECTRIC);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PIKACHU);
    } WHEN {
        TURN { MOVE(player, MOVE_THUNDER_SHOCK); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_THUNDER_SHOCK, player);
        HP_BAR(opponent);
#if B_PARALYZE_ELECTRIC >= GEN_6
        NOT ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PRZ, opponent);
        NOT STATUS_ICON(opponent, paralysis: TRUE);
#else
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PRZ, opponent);
        STATUS_ICON(opponent, paralysis: TRUE);
#endif
    }
}
