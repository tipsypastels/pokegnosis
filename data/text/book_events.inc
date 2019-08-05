Book_Player_Diary_1::
  msgbox BookLabel_Player_Diary_1, MSGBOX_DEFAULT
	setvar VAR_CURRENT_BOOK, BOOK_PLAYER_DIARY_1
	special Special_ShowBook
	end

BookLabel_Player_Diary_1:
  .string "It's your diary...$"

Book_BOTME_11::
  msgbox BookLabel_BOTME_11, MSGBOX_DEFAULT
	setvar VAR_CURRENT_BOOK, BOOK_BOTME_11
	special Special_ShowBook
	end

BookLabel_BOTME_11:
  .string "It's an excerpt from the story “Ballad\n"
  .string "of the Mad Emperor”, Chapter 11...$"