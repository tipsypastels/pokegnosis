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

Book_FishingJoke_1:: @ Dbr-output
  msgbox _Book_FishingJoke_1_Subscript_Text_0, MSGBOX_DEFAULT
  setvar VAR_CURRENT_BOOK, BOOK_FISHING_JOKE_1
  special Special_ShowBook
  end

_Book_FishingJoke_1_Subscript_Text_0: @ Dbr-output
  .string "It's a fishing almanac!\n"
  .string "Wonder what it could say?$"

_Book_FishingJoke_1_Subscript_Text_1:
  .string "It's certainly to the point...$"

Book_Poster_MeilisHouse:: @ Dbr-output
  msgbox _Book_Poster_MeilisHouse_Subscript_Text_0, MSGBOX_DEFAULT
  setvar VAR_CURRENT_BOOK, BOOK_POSTER_MEILISHOUSE
  special Special_ShowBook
  end

_Book_Poster_MeilisHouse_Subscript_Text_0: @ Dbr-output
  .string "It's an ancient saying…$"