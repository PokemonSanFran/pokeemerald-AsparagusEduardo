#include "global.h"
#include "test_battle.h"

ASSUMPTIONS
{
    ASSUME(gBattleMoves[MOVE_ABSORB].effect == EFFECT_ABSORB);
}

SINGLE_BATTLE_TEST("Absorb recovers 50% of the damage dealt")
{
    s16 damage;
    s16 healed;
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(1); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_ABSORB); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ABSORB, player);
        HP_BAR(opponent, captureDamage: &damage);
        HP_BAR(player, captureDamage: &healed);
    } THEN {
        EXPECT_MUL_EQ(damage, Q_4_12(-0.5), healed);
    }
}

#if B_HEAL_BLOCKING >= GEN_6
SINGLE_BATTLE_TEST("Absorb fails if Heal Block applies in Gen 6+")
#else
SINGLE_BATTLE_TEST("Absorb succedes but doesn't heal if Heal Block applies before Gen 6")
#endif
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(1); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_HEAL_BLOCK); MOVE(player, MOVE_ABSORB); }
    } SCENE {
        MESSAGE("Wobbuffet was prevented from healing!");
    #if B_HEAL_BLOCKING >= GEN_6
        NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_ABSORB, player);
    #else
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ABSORB, player);
    #endif
        NOT HP_BAR(opponent);
        NOT HP_BAR(player);
    }
}
