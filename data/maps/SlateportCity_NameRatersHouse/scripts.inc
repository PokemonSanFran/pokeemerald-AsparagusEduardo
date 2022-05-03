SlateportCity_NameRatersHouse_MapScripts::
	.byte 0

SlateportCity_NameRatersHouse_EventScript_NameRater::
	lock
	faceplayer
	msgbox SlateportCity_NameRatersHouse_Text_PleasedToRateMonNickname, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_ChooseMonToRate::
	msgbox SlateportCity_NameRatersHouse_Text_CritiqueWhichMonNickname, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_ne VAR_0x8004, PARTY_NOTHING_CHOSEN, SlateportCity_NameRatersHouse_EventScript_RateMonNickname
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_DeclineNameRate::
	msgbox SlateportCity_NameRatersHouse_Text_DoVisitAgain, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_RateMonNickname::
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_DUCK, SlateportCity_NameRatersHouse_EventScript_CantRateDuck
	special BufferMonNickname
	special IsMonOTIDNotPlayers
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	specialvar VAR_RESULT, MonOTNameNotPlayer
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	msgbox SlateportCity_NameRatersHouse_Text_FineNameSuggestBetterOne, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_NameRatersHouse_EventScript_ChangeNickname
	goto_if_eq VAR_RESULT, NO, SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_CantRateDuck::
	msgbox SlateportCity_NameRatersHouse_Text_ThatIsMerelyAnDuck, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT::
	msgbox SlateportCity_NameRatersHouse_Text_MagnificentName, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_ChangeNickname::
	msgbox SlateportCity_NameRatersHouse_Text_WhatShallNewNameBe, MSGBOX_DEFAULT
	call Common_EventScript_NameReceivedPartyMon
	specialvar VAR_RESULT, TryPutNameRaterShowOnTheAir
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_NameRatersHouse_EventScript_NewNameDifferent
	msgbox SlateportCity_NameRatersHouse_Text_NameNoDifferentYetSuperior, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_NewNameDifferent::
	msgbox SlateportCity_NameRatersHouse_Text_MonShallBeKnownAsName, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_TradebackGuy_V1::
	lock
	faceplayer
	msgbox SlateportCity_NameRatersHouse_TradebackGuy_Text_IllTradeIfYouWant, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SlateportCity_NameRatersHouse_TradebackGuy_DeclineTrade
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, 255
	goto_if_eq SlateportCity_NameRatersHouse_TradebackGuy_DeclineTrade
	copyvar VAR_0x8005, VAR_0x8004
	setvar VAR_0x8004, 6
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox SlateportCity_NameRatersHouse_TradebackGuy_Text_ComeBack, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_TradebackGuy_V2::
	lock
	faceplayer
	msgbox SlateportCity_NameRatersHouse_TradebackGuy_Text_IllTradeIfYouWant, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SlateportCity_NameRatersHouse_TradebackGuy_DeclineTrade
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, 255
	goto_if_eq SlateportCity_NameRatersHouse_TradebackGuy_DeclineTrade
	copyvar VAR_0x8005, VAR_0x8004
	setvar VAR_0x8004, 7
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	setvar VAR_0x8004, 8
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox SlateportCity_NameRatersHouse_TradebackGuy_Text_ComeBack, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_TradebackGuy_DeclineTrade::
	msgbox SlateportCity_NameRatersHouse_TradebackGuy_Text_YouDontWantToThatsOkay, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_TradebackGuy_Text_IllTradeIfYouWant:
	.string "Hi! I'm the Tradeback Guy!\p"
	.string "If you have a Pokémon that only\n"
	.string "evolves through trading, then I\l"
	.string "can help you out!\p"
	.string "Do you have any Pokémon that you'd\n"
	.string "like to evolve?$"

SlateportCity_NameRatersHouse_TradebackGuy_Text_ComeBack:
	.string "Come back anytime!$"

SlateportCity_NameRatersHouse_TradebackGuy_Text_YouDontWantToThatsOkay:
	.string "Alrighty. Well, if you change\n"
	.string "mind I'll still be right here.$"

SlateportCity_NameRatersHouse_Text_PleasedToRateMonNickname:
	.string "Hi, hi! I'm the Name Rater!\p"
	.string "…Or rather, I used to be.\p"
	.string "Now you can rate nicknames in\n"
	.string "every Pokémon Center…\p"
	.string "My grandson however, has been\n"
	.string "doing good with his business.$"

SlateportCity_NameRatersHouse_Text_CritiqueWhichMonNickname:
	.string "Which Pokémon's nickname should\n"
	.string "I critique?$"

SlateportCity_NameRatersHouse_Text_FineNameSuggestBetterOne:
	.string "Hmmm… {STR_VAR_1}, is it? That is\n"
	.string "quite a fine name you bestowed.\p"
	.string "But! What say you, if I were to\n"
	.string "suggest a slightly better name?$"

SlateportCity_NameRatersHouse_Text_WhatShallNewNameBe:
	.string "Ah, good. Then, what shall the new\n"
	.string "nickname be?$"

SlateportCity_NameRatersHouse_Text_MonShallBeKnownAsName:
	.string "Done! From now on, this Pokémon\n"
	.string "shall be known as {STR_VAR_1}!\p"
	.string "It is a better name than before!\n"
	.string "How fortunate for you!$"

SlateportCity_NameRatersHouse_Text_DoVisitAgain:
	.string "I see.\n"
	.string "Do come visit again.$"

SlateportCity_NameRatersHouse_Text_NameNoDifferentYetSuperior:
	.string "Done! From now on, this Pokémon\n"
	.string "shall be known as {STR_VAR_1}!\p"
	.string "It looks no different from before,\n"
	.string "and yet, this is vastly superior!\p"
	.string "How fortunate for you!$"

SlateportCity_NameRatersHouse_Text_MagnificentName:
	.string "Hmmm… {STR_VAR_1} it is!\p"
	.string "This is a magnificent nickname!\n"
	.string "It is impeccably beyond reproach!\p"
	.string "You'll do well to cherish your\n"
	.string "{STR_VAR_1} now and beyond.$"

SlateportCity_NameRatersHouse_Text_ThatIsMerelyAnDuck:
	.string "Now, now.\n"
	.string "That is merely an Duck!$"

