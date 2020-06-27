Debug_CheckSaveBlock::
	special CheckSaveBlock1Size
    msgbox Debug_CheckSaveBlock_Text
	releaseall
	end

Debug_SetPokedexFlags::
    msgbox Debug_SetPokedexFlags_Text
	releaseall
	end

Debug_CheckSaveBlock_Text:
	.string "SaveBlock1 is {STR_VAR_1} bytes long.\n"
	.string "Max size is 15872 bytes.\p"
	.string "SaveBlock2 is {STR_VAR_2} bytes long.\n"
	.string "Max size is 3968 bytes.\p"
	.string "PokemonStorage is {STR_VAR_3} bytes long.\n"
	.string "Max size is 35712 bytes.$"
	
Debug_SetPokedexFlags_Text:
	.string "Gotta catch 'em all!$"
