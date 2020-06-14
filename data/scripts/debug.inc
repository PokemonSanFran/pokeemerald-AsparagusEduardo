Debug_CheckSaveBlock1::
	special CheckSaveBlock1Size
    msgbox Debug_CheckSaveBlock1_Text
	releaseall
	end
    
Debug_CheckSaveBlock1_Text:
	.string "SaveBlock1 is {STR_VAR_1} bytes long.\n"
	.string "Max size is 15872 bytes.$"
