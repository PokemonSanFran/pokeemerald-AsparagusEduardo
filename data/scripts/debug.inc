Debug_CheckSaveBlock::
	special CheckSaveBlock1Size
    msgbox Debug_CheckSaveBlock_Text
	releaseall
	end

Debug_SetPokedexFlags::
    msgbox Debug_SetPokedexFlags_Text
	releaseall
	end

Debug_CheckWeekDay::
	special CheckWeekDay
    msgbox Debug_CheckWeekDay_Text
	releaseall
	end

Debug_CheckWeekDay_Text:
	.string "Aaaaah, yes!\l"
	.string "{STR_VAR_1}s are made for dads!\l"
	.string "And dad's car!$"

Debug_CheckSaveBlock_Text:
	.string "SaveBlock1 is {STR_VAR_1} bytes long.\n"
	.string "Max size is 15872 bytes.\p"
	.string "SaveBlock2 is {STR_VAR_2} bytes long.\n"
	.string "Max size is 3968 bytes.\p"
	.string "PokemonStorage is {STR_VAR_3} bytes long.\n"
	.string "Max size is 35712 bytes.$"
	
Debug_SetPokedexFlags_Text:
	.string "Gotta catch 'em all!$"
