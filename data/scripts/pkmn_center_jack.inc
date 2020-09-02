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
	goto SlateportCity_NameRatersHouse_EventScript_ChooseMonToRate
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

