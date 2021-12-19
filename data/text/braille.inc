@ NOTE: The brailleformat macro in this file is leftover from RS.
@       The numbers are simply skipped over. If you'd like to omit
@       this macro you must also stop it from skipping over this
@       section by editing ScrCmd_braillemessage.
Underwater_SealedChamber_Braille_GoUpHere:
	brailleformat 4, 6, 26, 13, 7, 9
#if GAME_LANGUAGE == LANGUAGE_SPANISH
	.braille "SUBE AHORA.$"
#else
	.braille "GO UP HERE.$"
#endif

SealedChamber_OuterRoom_Braille_ABC:
	brailleformat 7, 6, 21, 13, 10, 9
	.braille "ABC$"

SealedChamber_OuterRoom_Braille_GHI:
	brailleformat 7, 6, 21, 13, 10, 9
	.braille "GHI$"

SealedChamber_OuterRoom_Braille_MNO:
	brailleformat 7, 6, 21, 13, 10, 9
	.braille "MNO$"

SealedChamber_OuterRoom_Braille_TUV:
	brailleformat 7, 6, 21, 13, 10, 9
	.braille "TUV$"

SealedChamber_OuterRoom_Braille_DEF:
	brailleformat 7, 6, 21, 13, 10, 9
	.braille "DEF$"

SealedChamber_OuterRoom_Braille_JKL:
	brailleformat 7, 6, 21, 13, 10, 9
	.braille "JKL$"

SealedChamber_OuterRoom_Braille_PQRS:
	brailleformat 7, 6, 21, 13, 10, 9
	.braille "PQRS$"

SealedChamber_OuterRoom_Braille_Period:
	brailleformat 9, 6, 19, 13, 12, 9
	.braille ".$"

SealedChamber_OuterRoom_Braille_WXYZ:
	brailleformat 7, 6, 21, 13, 10, 9
	.braille "WXYZ$"

SealedChamber_OuterRoom_Braille_Comma:
	brailleformat 9, 6, 19, 13, 12, 9
	.braille ",$"

#if GAME_LANGUAGE == LANGUAGE_SPANISH
SealedChamber_OuterRoom_Braille_DigHere: @ 82A6B89
	.byte 7
	.byte 4
	.byte 23
	.byte 15
	.byte 10
	.byte 7
	.braille "CAVA AHORA.$"

SealedChamber_InnerRoom_Braille_FirstWailordLastRelicanth: @ 82A6B99
	.byte 0
	.byte 0
	.byte 29
	.byte 19
	.byte 3
	.byte 3
	.braille "PRIMERO\n"
	.braille "WAILORD.\n"
	.braille "AL FINAL\n"
	.braille "RELICANTH.$"

SealedChamber_InnerRoom_Braille_InThisCaveWeHaveLived: @ 82A6BCA
	.byte 2
	.byte 0
	.byte 26
	.byte 19
	.byte 5
	.byte 3
	.braille "ESTA CUEVA\n"
	.braille "HA SIDO\n"
	.braille "NUESTRO\n"
	.braille "HOGAR$"

SealedChamber_InnerRoom_Braille_WeOweAllToThePokemon: @ 82A6BEC
	.byte 7
	.byte 2
	.byte 23
	.byte 17
	.byte 10
	.byte 5
	.braille "LO QUE SOMOS\n"
	.braille "SE LO DEBEMOS\n"
	.braille "A LOS\n"
	.braille "POKEMON.$"

SealedChamber_InnerRoom_Braille_ButWeSealedThePokemonAway: @ 82A6C0D
	.byte 3
	.byte 0
	.byte 25
	.byte 19
	.byte 6
	.byte 3
	.braille "PERO LOS\n"
	.braille "ENCERRAMOS\n"
	.braille "PARA\n"
	.braille "SIEMPRE.$"

SealedChamber_InnerRoom_Braille_WeFearedIt: @ 82A6C34
	.byte 5
	.byte 6
	.byte 25
	.byte 13
	.byte 8
	.byte 9
	.braille "TUVIMOS MIEDO.$"

SealedChamber_InnerRoom_Braille_ThoseWithCourageHope: @ 82A6C48
	.byte 6
	.byte 0
	.byte 24
	.byte 19
	.byte 9
	.byte 3
	.braille "QUIENES\n"
	.braille "POSEEEN\n"
	.braille "VALOR Y\n"
	.braille "ESPERANZA$"

SealedChamber_InnerRoom_Braille_OpenDoorEternalPokemonWaits: @ 82A6C73
	.byte 3
	.byte 2
	.byte 27
	.byte 17
	.byte 6
	.byte 5
	.braille "ABREN LA\n"
	.braille "PUERTA HACIA\n"
	.braille "UN POKEMON\n"
	.braille "ETERNO.$"

DesertRuins_Braille_UseRockSmash: @ 82A6CA0
	.byte 1
	.byte 0
	.byte 27
	.byte 19
	.byte 4
	.byte 3
	.braille "IZDA IZDA\n"
	.braille "ABAJO ABAJO.\n"
	.braille "ENTONCES, USA\n"
	.braille "GOLPE ROCA.$"

IslandCave_Braille_RunLapAroundWall: @ 82A6CD4
	.byte 5
	.byte 0
	.byte 25
	.byte 19
	.byte 8
	.byte 3
	.braille "PONTE JUNTO\n"
	.braille "AL MURO.\n"
	.braille "DA UNA VUELTA\n"
	.braille "COMPLETA.$"

AncientTomb_Braille_ShineInTheMiddle: @ 82A6D06
	.byte 3
	.byte 0
	.byte 25
	.byte 19
	.byte 6
	.byte 3
	.braille "QUIEN DESEE LO\n"
	.braille "QUE NOSOTROS\n"
	.braille "QUE BRILLE\n"
	.braille "EN EL CENTRO.$"
#else
SealedChamber_OuterRoom_Braille_DigHere:
	brailleformat 7, 4, 23, 15, 10, 7
	.braille "DIG HERE.$"

SealedChamber_InnerRoom_Braille_FirstWailordLastRelicanth:
	brailleformat 0, 0, 29, 19, 3, 3
	.braille "FIRST COMES\n"
	.braille "WAILORD.\n"
	.braille "LAST COMES\n"
	.braille "RELICANTH.$"

SealedChamber_InnerRoom_Braille_InThisCaveWeHaveLived:
	brailleformat 2, 0, 26, 19, 5, 3
	.braille "IN THIS\n"
	.braille "CAVE WE\n"
	.braille "HAVE\n"
	.braille "LIVED.$"

SealedChamber_InnerRoom_Braille_WeOweAllToThePokemon:
	brailleformat 7, 2, 23, 17, 10, 5
	.braille "WE OWE ALL\n"
	.braille "TO THE\n"
	.braille "POKEMON.$"

SealedChamber_InnerRoom_Braille_ButWeSealedThePokemonAway:
	brailleformat 3, 0, 25, 19, 6, 3
	.braille "BUT, WE\n"
	.braille "SEALED THE\n"
	.braille "POKEMON\n"
	.braille "AWAY.$"

SealedChamber_InnerRoom_Braille_WeFearedIt:
	brailleformat 5, 6, 25, 13, 8, 9
	.braille "WE FEARED IT.$"

SealedChamber_InnerRoom_Braille_ThoseWithCourageHope:
	brailleformat 6, 0, 24, 19, 9, 3
	.braille "THOSE WITH\n"
	.braille "COURAGE,\n"
	.braille "THOSE WITH\n"
	.braille "HOPE.$"

SealedChamber_InnerRoom_Braille_OpenDoorEternalPokemonWaits:
	brailleformat 3, 2, 27, 17, 6, 5
	.braille "OPEN A DOOR.\n"
	.braille "AN ETERNAL\n"
	.braille "POKEMON\n"
	.braille "WAITS.$"

DesertRuins_Braille_UseRockSmash:
	brailleformat 1, 0, 27, 19, 4, 3
	.braille "LEFT, LEFT,\n"
	.braille "DOWN, DOWN.\n"
	.braille "THEN, USE\n"
	.braille "ROCK SMASH.$"

IslandCave_Braille_RunLapAroundWall:
	brailleformat 5, 0, 25, 19, 8, 3
	.braille "STAY CLOSE\n"
	.braille "TO THE WALL.\n"
	.braille "RUN AROUND\n"
	.braille "ONE LAP.$"

AncientTomb_Braille_ShineInTheMiddle:
	brailleformat 3, 0, 25, 19, 6, 3
	.braille "THOSE WHO\n"
	.braille "INHERIT OUR\n"
	.braille "WILL, SHINE\n"
	.braille "IN THE MIDDLE.$"
#endif
