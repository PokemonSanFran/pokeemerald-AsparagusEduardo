UDTrade_EventScript_OpenDimensionList::
	lockall
	faceplayer
	special OpenUDTradeMenu
	waitstate
	end

UDTrade_EventScript_UDTradeCenter::
	copyvar VAR_0x8007, VAR_LAST_TALKED
	call CableClub_EventScript_CheckPartyTradeRequirements
	compare VAR_RESULT, 0
	goto_if_eq CableClub_EventScript_AbortLink
	call Common_EventScript_SaveGame
	compare VAR_RESULT, 0
	goto_if_eq CableClub_EventScript_AbortLink
	message gText_PleaseWaitForLink
	waitmessage
	special TryTradeLinkup
	waitstate
	compare VAR_RESULT, LINKUP_SUCCESS
	goto_if_eq UDTrade_EventScript_EnterUDTradeCenter
	compare VAR_RESULT, LINKUP_SOMEONE_NOT_READY
	goto_if_eq CableClub_EventScript_AbortLinkSomeoneNotReady
	compare VAR_RESULT, LINKUP_DIFF_SELECTIONS
	goto_if_eq CableClub_EventScript_AbortLinkDifferentSelections
	compare VAR_RESULT, LINKUP_WRONG_NUM_PLAYERS
	goto_if_eq CableClub_EventScript_AbortLinkIncorrectNumberOfParticipants
	compare VAR_RESULT, LINKUP_FAILED
	goto_if_eq CableClub_EventScript_AbortLink
	compare VAR_RESULT, LINKUP_CONNECTION_ERROR
	goto_if_eq CableClub_EventScript_AbortLinkConnectionError
	compare VAR_RESULT, LINKUP_PLAYER_NOT_READY
	goto_if_eq CableClub_EventScript_AbortLinkPlayerNotReady
	compare VAR_RESULT, LINKUP_PARTNER_NOT_READY
	goto_if_eq CableClub_EventScript_AbortLinkOtherTrainerNotReady
	end

UDTrade_EventScript_EnterUDTradeCenter::
	setvar VAR_0x8004, USING_TRADE_CENTER
	copyvar VAR_CABLE_CLUB_STATE, VAR_0x8004
	messageautoscroll CableClub_Text_PleaseEnter
	waitmessage
	call CableClub_EventScript_OpenUnionRoomBarrier
	special DrawWholeMapView
	playse SE_CLICK
	delay 60
	applymovement VAR_LAST_TALKED, Movement_AttendantFaceLeft
	waitmovement 0
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Movement_PlayerApproachLinkRoomLeft
	waitmovement 0
	opendoor 5, 1
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, Movement_PlayerEnterLinkRoom
	waitmovement 0
	hideobjectat OBJ_EVENT_ID_PLAYER, 0
	closedoor 5, 1
	waitdooranim
	release
	special SetCableClubWarp
	setwarp MAP_TRADE_CENTER, 255, 5, 8
	special DoCableClubWarp
	waitstate
	end

