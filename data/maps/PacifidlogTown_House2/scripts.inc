PacifidlogTown_House2_MapScripts::
	.byte 0

PacifidlogTown_House2_EventScript_FanClubYoungerBrother::
	lock
	faceplayer
	call_if_set FLAG_MET_FANCLUB_YOUNGER_BROTHER, PacifidlogTown_House2_EventScript_MonAssessment
	call_if_unset FLAG_MET_FANCLUB_YOUNGER_BROTHER, PacifidlogTown_House2_EventScript_FirstMonAssessment
	setflag FLAG_MET_FANCLUB_YOUNGER_BROTHER
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	goto_if_ge VAR_RESULT, FRIENDSHIP_150_TO_199, PacifidlogTown_House2_EventScript_GiveReturn
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	goto_if_ge VAR_RESULT, FRIENDSHIP_50_TO_99, PacifidlogTown_House2_EventScript_PutInEffort
	goto PacifidlogTown_House2_EventScript_GiveFrustration
	end

PacifidlogTown_House2_EventScript_MonAssessment::
	msgbox PacifidlogTown_House2_Text_AhYourPokemon, MSGBOX_DEFAULT
	return

PacifidlogTown_House2_EventScript_FirstMonAssessment::
	msgbox PacifidlogTown_House2_Text_ChairmansYoungerBrotherOnVacation, MSGBOX_DEFAULT
	msgbox PacifidlogTown_House2_Text_AhYourPokemon, MSGBOX_DEFAULT
	return

PacifidlogTown_House2_EventScript_GiveReturn::
	call_if_set FLAG_RECEIVED_FANCLUB_TM_RETURN, PacifidlogTown_House2_EventScript_Adoring
	msgbox PacifidlogTown_House2_Text_AdoringPokemonTakeThis, MSGBOX_DEFAULT

	giveitem ITEM_TM27
	goto_if_eq VAR_RESULT, FALSE Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FANCLUB_TM_RETURN
	
	msgbox PacifidlogTown_House2_Text_YouMayAlsoHaveThis, MSGBOX_DEFAULT

	giveitem ITEM_TM21
	goto_if_eq VAR_RESULT, FALSE Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FANCLUB_TM_FRUSTRATION

	msgbox PacifidlogTown_House2_Text_ExplainReturnFrustration, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_PutInEffort::
	msgbox PacifidlogTown_House2_Text_PutInSomeMoreEffort, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_Adoring::
	msgbox PacifidlogTown_House2_Text_AdoringPokemon, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_Vicious::
	msgbox PacifidlogTown_House2_Text_ViciousPokemon, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_GiveFrustration::
	call_if_set FLAG_RECEIVED_FANCLUB_TM_FRUSTRATION, PacifidlogTown_House2_EventScript_Vicious
	msgbox PacifidlogTown_House2_Text_ViciousPokemonTakeThis, MSGBOX_DEFAULT

	giveitem ITEM_TM21
	goto_if_eq VAR_RESULT, FALSE Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FANCLUB_TM_FRUSTRATION
	
	msgbox PacifidlogTown_House2_Text_YouMayAlsoHaveThis, MSGBOX_DEFAULT

	giveitem ITEM_TM27
	goto_if_eq VAR_RESULT, FALSE Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FANCLUB_TM_RETURN

	msgbox PacifidlogTown_House2_Text_ExplainReturnFrustration, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_HappyAzurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_NORMAL
	msgbox PacifidlogTown_House2_Text_Rurii, MSGBOX_DEFAULT
	waitmoncry
	msgbox PacifidlogTown_House2_Text_VeryFriendlyWithTrainer, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_EventScript_UnhappyAzurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_ENCOUNTER
	msgbox PacifidlogTown_House2_Text_Rururi, MSGBOX_DEFAULT
	waitmoncry
	msgbox PacifidlogTown_House2_Text_DoesntLikeTrainerVeryMuch, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House2_Text_ChairmansYoungerBrotherOnVacation:
	.string "Er-hem!\p"
	.string "I am the Pokémon Fan Club's most\n"
	.string "important person, the Chairman's\l"
	.string "younger brother.\p"
	.string "I'm here enjoying my vacation with\n"
	.string "Pokémon, yes, indeed.$"

PacifidlogTown_House2_Text_AhYourPokemon:
	.string "Ah!\n"
	.string "Your Pokémon…$"

PacifidlogTown_House2_Text_AdoringPokemonTakeThis:
	.string "It clearly likes you very much.\p"
	.string "A Pokémon that adoring and adorable\n"
	.string "deserves a TM like this, no?$"

PacifidlogTown_House2_Text_AdoringPokemon:
	.string "It clearly likes you very much.$"

PacifidlogTown_House2_Text_PutInSomeMoreEffort:
	.string "Hmm…\n"
	.string "It's not bad, but it's also not good.\p"
	.string "You, as the Trainer, need to put in\n"
	.string "some more effort.$"

PacifidlogTown_House2_Text_ViciousPokemonTakeThis:
	.string "It has a vicious look to it.\p"
	.string "A frightening Pokémon like that\n"
	.string "deserves a TM like this.$"

PacifidlogTown_House2_Text_ViciousPokemon:
	.string "It has a vicious look to it.$"

PacifidlogTown_House2_Text_ExplainReturnFrustration:
	.string "If a Pokémon likes you a lot, Return's\n"
	.string "power is enhanced.\p"
	.string "If it doesn't like you, Frustration's\n"
	.string "power goes up.$"

PacifidlogTown_House2_Text_Rurii:
	.string "Azurill: Rurii.$"

PacifidlogTown_House2_Text_VeryFriendlyWithTrainer:
	.string "It appears to be very friendly with the\n"
	.string "Trainer.$"

PacifidlogTown_House2_Text_Rururi:
	.string "Azurill: Rururi!$"

PacifidlogTown_House2_Text_DoesntLikeTrainerVeryMuch:
	.string "It doesn't appear to like the Trainer\n"
	.string "very much.$"

PacifidlogTown_House2_Text_YouMayAlsoHaveThis:
	.string "You may also have this.$"

