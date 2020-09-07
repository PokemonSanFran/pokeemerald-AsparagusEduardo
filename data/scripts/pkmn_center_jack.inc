Common_EventScript_PkmnCenterJack::
	msgbox gText_PkmnCenterJack_GotPokemonQuestions, MSGBOX_DEFAULT
	multichoice 16, 0, MULTI_POKECENTER_JACK, 0
	copyvar VAR_TEMP_1, VAR_RESULT
	switch VAR_TEMP_1
	case 0, Common_EventScript_PkmnCenterJack_RateNickame
	case 1, Common_EventScript_PkmnCenterJack_RememberMove
	case 2, Common_EventScript_PkmnCenterJack_ForgetMove
	case 3, Common_EventScript_PkmnCenterJack_TeachMove
	case 4, Common_EventScript_PkmnCenterJack_ComeBackAnytime
	case MULTI_B_PRESSED, Common_EventScript_PkmnCenterJack_ComeBackAnytime
	end

Common_EventScript_PkmnCenterJack_RateNickame::
	goto Common_EventScript_PkmnCenterJack_ChooseMonToRate
    return

Common_EventScript_PkmnCenterJack_RememberMove::
	msgbox gText_PkmnCenterJack_Remember, MSGBOX_DEFAULT
    return

Common_EventScript_PkmnCenterJack_ForgetMove::
	msgbox gText_PkmnCenterJack_Forget, MSGBOX_DEFAULT
    return

Common_EventScript_PkmnCenterJack_TeachMove::
	msgbox gText_PkmnCenterJack_Teach, MSGBOX_DEFAULT
    return

Common_EventScript_PkmnCenterJack_ComeBackAnytime::
	msgbox gText_PkmnCenterJack_ComeBackAnytime, MSGBOX_DEFAULT
    return

Common_EventScript_PkmnCenterJack_ChooseMonToRate:: @ 8209AC6
	msgbox Common_PkmnCenterJack_Text_CritiqueWhichMonNickname, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, 255
	goto_if_ne Common_EventScript_PkmnCenterJack_RateMonNickname
	compare VAR_0x8004, 255
	goto_if_eq Common_EventScript_PkmnCenterJack_DeclineNameRate
	end

Common_EventScript_PkmnCenterJack_DeclineNameRate:: @ 8209AE9
	msgbox Common_PkmnCenterJack_Text_DoVisitAgain, MSGBOX_DEFAULT
	release
	end

Common_EventScript_PkmnCenterJack_RateMonNickname:: @ 8209AF3
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	compare VAR_RESULT, SPECIES_EGG
	goto_if_eq Common_EventScript_PkmnCenterJack_CantRateEgg
	special BufferMonNickname
	msgbox Common_PkmnCenterJack_Text_FineNameSuggestBetterOne, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Common_EventScript_PkmnCenterJack_ChangeNickname
	compare VAR_RESULT, NO
	goto_if_eq Common_EventScript_PkmnCenterJack_DeclineNameRate
	end

Common_EventScript_PkmnCenterJack_CantRateEgg:: @ 8209B46
	msgbox Common_PkmnCenterJack_Text_ThatIsMerelyAnEgg, MSGBOX_DEFAULT
	release
	end

Common_EventScript_PkmnCenterJack_ChangeNickname:: @ 8209B5A
	msgbox Common_PkmnCenterJack_Text_WhatShallNewNameBe, MSGBOX_DEFAULT
	call Common_EventScript_NameReceivedPartyMon
	specialvar VAR_RESULT, TryPutNameRaterShowOnTheAir
	special BufferMonNickname
	compare VAR_RESULT, TRUE
	goto_if_eq Common_EventScript_PkmnCenterJack_NewNameDifferent
	msgbox Common_PkmnCenterJack_Text_NameNoDifferentYetSuperior, MSGBOX_DEFAULT
	release
	end

Common_EventScript_PkmnCenterJack_NewNameDifferent:: @ 8209B84
	msgbox Common_PkmnCenterJack_Text_MonShallBeKnownAsName, MSGBOX_DEFAULT
	release
	end
