Route114_MapScripts:: @ 81F252F
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route114_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route114_OnFrame
	.byte 0

Route114_OnTransition: @ 81F253F
	compare VAR_SHOULD_END_UNUSUAL_WEATHER, 1
	call_if_eq UnusualWeather_EventScript_HideMapNamePopup
	compare VAR_UNUSUAL_WEATHER_LOCATION, UNUSUAL_WEATHER_ROUTE_114_NORTH
	call_if_eq UnusualWeather_StartGroudonWeather
	compare VAR_UNUSUAL_WEATHER_LOCATION, UNUSUAL_WEATHER_ROUTE_114_SOUTH
	call_if_eq UnusualWeather_StartGroudonWeather
	end

Route114_OnLoad: @ 81F2561
	compare VAR_UNUSUAL_WEATHER_LOCATION, UNUSUAL_WEATHER_ROUTE_114_NORTH
	call_if_eq UnusualWeather_EventScript_PlaceTilesRoute114North
	compare VAR_UNUSUAL_WEATHER_LOCATION, UNUSUAL_WEATHER_ROUTE_114_SOUTH
	call_if_eq UnusualWeather_EventScript_PlaceTilesRoute114South
	end

Route114_OnFrame: @ 81F2578
	map_script_2 VAR_SHOULD_END_UNUSUAL_WEATHER, 1, UnusualWeather_EventScript_EndEventAndCleanup_1
	.2byte 0

Route114_EventScript_Man:: @ 81F2582
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_ROUTE_114_RECEIVED_BERRY, Route114_EventScript_ReceivedBerry
	msgbox Route114_Text_LoveUsingBerryCrushShareBerry, MSGBOX_DEFAULT
	random NUM_ROUTE_114_MAN_BERRIES
	addvar VAR_RESULT, NUM_ROUTE_114_MAN_BERRIES_SKIPPED
	addvar VAR_RESULT, FIRST_BERRY_INDEX
	giveitem_std VAR_RESULT
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_ROUTE_114_RECEIVED_BERRY
	msgbox Route114_Text_TryBerryCrushWithFriends, MSGBOX_DEFAULT
	release
	end

Route114_EventScript_ReceivedBerry:: @ 81F25C7
	msgbox Route114_Text_FunToThinkAboutBerries, MSGBOX_DEFAULT
	release
	end

Route114_EventScript_RoarGentleman:: @ 81F25D1
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM05, Route114_EventScript_ReceivedRoar
	msgbox Route114_Text_AllMyMonDoesIsRoarTakeThis, MSGBOX_DEFAULT
	giveitem_std ITEM_TM05
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM05
	msgbox Route114_Text_ExplainRoar, MSGBOX_DEFAULT
	release
	end

Route114_EventScript_ReceivedRoar:: @ 81F2608
	msgbox Route114_Text_ExplainRoar, MSGBOX_DEFAULT
	release
	end

Route114_EventScript_Poochyena:: @ 81F2612
	lock
	faceplayer
	waitse
	playmoncry SPECIES_POOCHYENA, 2
	msgbox Route114_Text_Poochyena, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route114_EventScript_MeteorFallsSign:: @ 81F2625
	msgbox Route114_Text_MeteorFallsSign, MSGBOX_SIGN
	end

Route114_EventScript_FossilManiacsHouseSign:: @ 81F262E
	msgbox Route114_Text_FossilManiacsHouseSign, MSGBOX_SIGN
	end

Route114_EventScript_LanettesHouseSign:: @ 81F2637
	msgbox Route114_Text_LanettesHouse, MSGBOX_SIGN
	end

Route114_EventScript_Lenny:: @ 81F2640
	trainerbattle_single TRAINER_LENNY, Route114_Text_LennyIntro, Route114_Text_LennyDefeat
	msgbox Route114_Text_LennyPostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Lucas:: @ 81F2657
	trainerbattle_single TRAINER_LUCAS_1, Route114_Text_LucasIntro, Route114_Text_LucasDefeat
	msgbox Route114_Text_LucasPostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Shane:: @ 81F266E
	trainerbattle_single TRAINER_SHANE, Route114_Text_ShaneIntro, Route114_Text_ShaneDefeat
	msgbox Route114_Text_ShanePostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Nancy:: @ 81F2685
	trainerbattle_single TRAINER_NANCY, Route114_Text_NancyIntro, Route114_Text_NancyDefeat
	msgbox Route114_Text_NancyPostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Steve:: @ 81F269C
	trainerbattle_single TRAINER_STEVE_1, Route114_Text_SteveIntro, Route114_Text_SteveDefeat, Route114_EventScript_RegisterSteve
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route114_EventScript_RematchSteve
	msgbox Route114_Text_StevePostBattle, MSGBOX_DEFAULT
	release
	end

Route114_EventScript_RegisterSteve:: @ 81F26C8
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route114_Text_SteveRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_STEVE_1
	release
	end

Route114_EventScript_RematchSteve:: @ 81F26E7
	trainerbattle_rematch TRAINER_STEVE_1, Route114_Text_SteveRematchIntro, Route114_Text_SteveRematchDefeat
	msgbox Route114_Text_StevePostRematch, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Bernie:: @ 81F26FE
	trainerbattle_single TRAINER_BERNIE_1, Route114_Text_BernieIntro, Route114_Text_BernieDefeat, Route114_EventScript_RegisterBernie
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route114_EventScript_RematchBernie
	msgbox Route114_Text_BerniePostBattle, MSGBOX_DEFAULT
	release
	end

Route114_EventScript_RegisterBernie:: @ 81F272A
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route114_Text_BernieRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_BERNIE_1
	release
	end

Route114_EventScript_RematchBernie:: @ 81F2749
	trainerbattle_rematch TRAINER_BERNIE_1, Route114_Text_BernieRematchIntro, Route114_Text_BernieRematchDefeat
	msgbox Route114_Text_BerniePostRematch, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Claude:: @ 81F2760
	trainerbattle_single TRAINER_CLAUDE, Route114_Text_ClaudeIntro, Route114_Text_ClaudeDefeat
	msgbox Route114_Text_ClaudePostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Nolan:: @ 81F2777
	trainerbattle_single TRAINER_NOLAN, Route114_Text_NolanIntro, Route114_Text_NolanDefeat
	msgbox Route114_Text_NolanPostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Tyra:: @ 81F278E
	trainerbattle_double TRAINER_TYRA_AND_IVY, Route114_Text_TyraIntro, Route114_Text_TyraDefeat, Route114_Text_TyraNotEnoughMons
	msgbox Route114_Text_TyraPostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Ivy:: @ 81F27A9
	trainerbattle_double TRAINER_TYRA_AND_IVY, Route114_Text_IvyIntro, Route114_Text_IvyDefeat, Route114_Text_IvyNotEnoughMons
	msgbox Route114_Text_IvyPostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Angelina:: @ 81F27C4
	trainerbattle_single TRAINER_ANGELINA, Route114_Text_AngelinaIntro, Route114_Text_AngelinaDefeat
	msgbox Route114_Text_AngelinaPostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Charlotte:: @ 81F27DB
	trainerbattle_single TRAINER_CHARLOTTE, Route114_Text_CharlotteIntro, Route114_Text_CharlotteDefeat
	msgbox Route114_Text_CharlottePostBattle, MSGBOX_AUTOCLOSE
	end

Route114_EventScript_Kai:: @ 81F27F2
	trainerbattle_single TRAINER_KAI, Route114_Text_KaiIntro, Route114_Text_KaiDefeat
	msgbox Route114_Text_KaiPostBattle, MSGBOX_AUTOCLOSE
	end

Route114_Text_AllMyMonDoesIsRoarTakeThis: @ 81F2809
	.string "All my POKéMON does is ROAR…\n"
	.string "No one dares to come near me…\p"
	.string "Sigh… If you would, please take\n"
	.string "this TM away…$"

Route114_Text_ExplainRoar: @ 81F2872
	.string "TM05 contains ROAR.\n"
	.string "A ROAR sends POKéMON scurrying.$"

Route114_Text_Poochyena: @ 81F28A6
	.string "Bow! Bowwow!$"

Route114_Text_MeteorFallsSign: @ 81F28B3
	.string "METEOR FALLS\n"
	.string "RUSTBORO CITY THROUGH HERE$"

Route114_Text_FossilManiacsHouseSign: @ 81F28DB
	.string "FOSSIL MANIAC'S HOUSE\n"
	.string "“Fossils gratefully accepted!”$"

Route114_Text_LanettesHouse: @ 81F2910
	.string "LANETTE'S HOUSE$"

DenseJungle_Sign:: @ Dbr-output
  lock
  showplayerportrait PORTRAIT_FROWN
  msgbox _DenseJungle_Sign_Subscript_Text_0, MSGBOX_DEFAULT
  hideportrait
  release
  end

_DenseJungle_Sign_Subscript_Text_0: @ Dbr-output
  .string "(Wow, it's too faded to read.)$"

DenseJungle_Starter_Egg:: @ Dbr-output
  lock
  call _DenseJungle_Starter_Egg_CenterPlayer
  applymovement EVENT_OBJ_ID_PLAYER, _DenseJungle_Starter_Egg_Subscript_Movement_0
  waitmovement EVENT_OBJ_ID_PLAYER
  applymovement 2, _DenseJungle_Starter_Egg_Subscript_Movement_1
  waitmovement 2
  showportrait PORTRAIT_ZHENG, PORTRAIT_DRUNK_GRIN
  msgbox _DenseJungle_Starter_Egg_Subscript_Text_2, MSGBOX_DEFAULT
  hideportrait
  showplayerportrait PORTRAIT_DRUNK_GRIN
  msgbox _DenseJungle_Starter_Egg_Subscript_Text_3, MSGBOX_DEFAULT
  hideportrait
  closemessage
  applymovement 2, _DenseJungle_Starter_Egg_Subscript_Movement_4
  waitmovement 2
  showportrait PORTRAIT_ZHENG, PORTRAIT_DRUNK_GRIN
  msgbox _DenseJungle_Starter_Egg_Subscript_Text_5, MSGBOX_DEFAULT
  hideportrait
  closemessage
  applymovement 2, _DenseJungle_Starter_Egg_Subscript_Movement_6
  playse SE_DANSA
  applymovement 2, _DenseJungle_Starter_Egg_Subscript_Movement_7
  waitmovement 2
  showportrait PORTRAIT_ZHENG, PORTRAIT_WIPED_OUT_GRIN
  msgbox _DenseJungle_Starter_Egg_Subscript_Text_8, MSGBOX_DEFAULT
  hideportrait
  closemessage
  applymovement 2, _DenseJungle_Starter_Egg_Subscript_Movement_9
  waitmovement 2
  applymovement EVENT_OBJ_ID_PLAYER, _DenseJungle_Starter_Egg_Subscript_Movement_10
  waitmovement EVENT_OBJ_ID_PLAYER
  showportrait PORTRAIT_ZHENG, PORTRAIT_EYES_CLOSED_GRIN
  msgbox _DenseJungle_Starter_Egg_Subscript_Text_11, MSGBOX_DEFAULT
  hideportrait
  closemessage
  applymovement EVENT_OBJ_ID_PLAYER, _DenseJungle_Starter_Egg_Subscript_Movement_12
  waitmovement EVENT_OBJ_ID_PLAYER
  showplayerportrait PORTRAIT_DEVILISH
  msgbox _DenseJungle_Starter_Egg_Subscript_Text_13, MSGBOX_DEFAULT
  hideportrait
  closemessage
  applymovement EVENT_OBJ_ID_PLAYER, _DenseJungle_Starter_Egg_Subscript_Movement_14
  waitmovement EVENT_OBJ_ID_PLAYER
  special ChooseStarter
  waitstate
  applymovement EVENT_OBJ_ID_PLAYER, _DenseJungle_Starter_Egg_Subscript_Movement_15
  waitmovement EVENT_OBJ_ID_PLAYER
  bufferleadmonspeciesname 0
  showplayerportrait PORTRAIT_WIPED_OUT_GRIN
  msgbox _DenseJungle_Starter_Egg_Subscript_Text_16, MSGBOX_DEFAULT
  hideportrait
  closemessage
  applymovement 2, _DenseJungle_Starter_Egg_Subscript_Movement_17
  waitmovement 2
  applymovement 2, _DenseJungle_Starter_Egg_Subscript_Movement_18
  playse SE_DANSA
  applymovement 2, _DenseJungle_Starter_Egg_Subscript_Movement_19
  waitmovement 2
  showportrait PORTRAIT_ZHENG, PORTRAIT_EYES_CLOSED_GRIN
  msgbox _DenseJungle_Starter_Egg_Subscript_Text_20, MSGBOX_DEFAULT
  hideportrait
  closemessage
  applymovement 2, _DenseJungle_Starter_Egg_Subscript_Movement_21
  waitmovement 2
  showportrait PORTRAIT_ZHENG, PORTRAIT_SNEAKY
  msgbox _DenseJungle_Starter_Egg_Subscript_Text_22, MSGBOX_DEFAULT
  hideportrait
  applymovement 2, _DenseJungle_Starter_Egg_Subscript_Movement_23
  waitmovement 2
  showportrait PORTRAIT_ZHENG, PORTRAIT_WINK
  msgbox _DenseJungle_Starter_Egg_Subscript_Text_24, MSGBOX_DEFAULT
  hideportrait
  closemessage
  applymovement EVENT_OBJ_ID_PLAYER, _DenseJungle_Starter_Egg_Subscript_Movement_25
  waitmovement EVENT_OBJ_ID_PLAYER
  applymovement 2, _DenseJungle_Starter_Egg_Subscript_Movement_26
  waitmovement 2
  showportrait PORTRAIT_ZHENG, PORTRAIT_SMILE_CLOSED_MOUTH
  msgbox _DenseJungle_Starter_Egg_Subscript_Text_27, MSGBOX_DEFAULT
  hideportrait
  closemessage
  applymovement 2, _DenseJungle_Starter_Egg_Subscript_Movement_28
  waitmovement 2
  playse MUS_FANFA4
  showplayerportrait PORTRAIT_DRUNK_GRIN
  msgbox _DenseJungle_Starter_Egg_Subscript_Text_29, MSGBOX_DEFAULT
  hideportrait
  showportrait PORTRAIT_ZHENG, PORTRAIT_DRUNK_GRIN
  msgbox _DenseJungle_Starter_Egg_Subscript_Text_30, MSGBOX_DEFAULT
  hideportrait
  closemessage
  applymovement 2, _DenseJungle_Starter_Egg_Subscript_Movement_31
  waitmovement 2
  showportrait PORTRAIT_ZHENG, PORTRAIT_SLIGHT_SMILE
  msgbox _DenseJungle_Starter_Egg_Subscript_Text_32, MSGBOX_DEFAULT
  hideportrait
  showportrait PORTRAIT_ZHENG, PORTRAIT_ALARMED
  msgbox _DenseJungle_Starter_Egg_Subscript_Text_33, MSGBOX_DEFAULT
  hideportrait
  closemessage
  setweather WEATHER_SHADE
  doweather
  playbgm MUS_AQA_0, 0
  applymovement EVENT_OBJ_ID_PLAYER, _DenseJungle_Starter_Egg_Subscript_Movement_34
  waitmovement EVENT_OBJ_ID_PLAYER
  showportrait PORTRAIT_ZHENG, PORTRAIT_SWEAT
  msgbox _DenseJungle_Starter_Egg_Subscript_Text_35, MSGBOX_DEFAULT
  hideportrait
  closemessage
  setvar VAR_0x8004, 1
  setvar VAR_0x8005, 1
  setvar VAR_0x8006, 16
  setvar VAR_0x8007, 5
  special ShakeCamera
  playse SE_W253
  msgbox _DenseJungle_Starter_Egg_Subscript_Text_36, MSGBOX_DEFAULT
  closemessage
  applymovement EVENT_OBJ_ID_PLAYER, _DenseJungle_Starter_Egg_Subscript_Movement_37
  applymovement 2, _DenseJungle_Starter_Egg_Subscript_Movement_38
  waitmovement 2
  showportrait PORTRAIT_ZHENG, PORTRAIT_ALARMED
  msgbox _DenseJungle_Starter_Egg_Subscript_Text_39, MSGBOX_DEFAULT
  hideportrait
  closemessage
  special SpawnCameraObject
  setvar VAR_0x8004, 3
  setvar VAR_0x8005, 3
  setvar VAR_0x8006, 32
  setvar VAR_0x8007, 3
  special ShakeCamera
  playse SE_W253
  applymovement EVENT_OBJ_ID_PLAYER, _DenseJungle_Starter_Egg_Subscript_Movement_40
  applymovement 2, _DenseJungle_Starter_Egg_Subscript_Movement_41
  waitmovement 2
  special RemoveCameraObject
  fadescreen 1
  warpsilent MAP_LITTLEROOT_TOWN_MAYS_HOUSE_1F, 0xFF, 0, 3
  waitstate
  release
  end

_DenseJungle_Starter_Egg_Subscript_Movement_0: @ Dbr-output
  walk_up
  step_end

_DenseJungle_Starter_Egg_Subscript_Text_2: @ Dbr-output
  .string "These… these are {COLOR POKEMON_COLOR}Pokémon{COLOR NO_COLOR} eggs!\n"
  .string "I'm sure of it!$"

_DenseJungle_Starter_Egg_Subscript_Movement_6: @ Dbr-output
  jump_in_place_left
  step_end

_DenseJungle_Starter_Egg_Subscript_Movement_9: @ Dbr-output
  delay_16
  walk_slow_down
  face_left
  step_end

_DenseJungle_Starter_Egg_Subscript_Movement_14: @ Dbr-output
  delay_16
  delay_16
  step_end

_DenseJungle_Starter_Egg_Subscript_Movement_18: @ Dbr-output
  jump_in_place_left
  step_end

_DenseJungle_Starter_Egg_Subscript_Movement_25: @ Dbr-output
  face_up
  step_end

_DenseJungle_Starter_Egg_Subscript_Movement_17: @ Dbr-output
  emote_exclamation_mark
  step_end

_DenseJungle_Starter_Egg_Subscript_Text_35: @ Dbr-output
  .string "I think… we found…$"

_DenseJungle_Starter_Egg_Subscript_Text_29: @ Dbr-output
  .string "(Yes! I got a {COLOR POKEMON_COLOR}Dragon Egg{COLOR NO_COLOR}!)$"

_DenseJungle_Starter_Egg_Subscript_Text_32: @ Dbr-output
  .string "…\p"
  .string "{COLOR CHARACTER_COLOR}{PLAYER}{COLOR NO_COLOR}…$"

_DenseJungle_Starter_Egg_Subscript_Movement_37: @ Dbr-output
  emote_exclamation_mark
  step_end

_DenseJungle_Starter_Egg_Subscript_Movement_40: @ Dbr-output
  walk_fast_down
  walk_fast_right
  walk_fast_right
  walk_fast_down
  walk_fast_down
  walk_fast_down
  walk_fast_down
  walk_fast_down
  walk_fast_down
  step_end

_DenseJungle_Starter_Egg_Subscript_Movement_1: @ Dbr-output
  walk_left
  step_end

_DenseJungle_Starter_Egg_Subscript_Text_3: @ Dbr-output
  .string "(…)$"

_DenseJungle_Starter_Egg_Subscript_Movement_4: @ Dbr-output
  delay_16
  face_player
  delay_16
  emote_exclamation_mark
  delay_16
  step_end

_DenseJungle_Starter_Egg_Subscript_Text_5: @ Dbr-output
  .string "Wait, you don't think…\l"
  .string "Could those be eggs from the {COLOR POKEMON_COLOR}Dragon{COLOR NO_COLOR}\n"
  .string "{COLOR POKEMON_COLOR}Pokémon{COLOR NO_COLOR} everyone's been searching for?$"

_DenseJungle_Starter_Egg_Subscript_Movement_7: @ Dbr-output
  delay_16
  step_end

_DenseJungle_Starter_Egg_Subscript_Text_8: @ Dbr-output
  .string "Oh man, just imagine what could be in\n"
  .string "these!\p"
  .string "{COLOR POKEMON_COLOR}Dragon Pokémon{COLOR NO_COLOR} are like, legendary!$"

_DenseJungle_Starter_Egg_Subscript_Movement_10: @ Dbr-output
  face_right
  step_end

_DenseJungle_Starter_Egg_Subscript_Text_11: @ Dbr-output
  .string "C'mon, {COLOR CHARACTER_COLOR}{PLAYER}{COLOR NO_COLOR}?\l"
  .string "What do you think is in there?$"

_DenseJungle_Starter_Egg_Subscript_Movement_12: @ Dbr-output
  face_up
  step_end

_DenseJungle_Starter_Egg_Subscript_Text_13: @ Dbr-output
  .string "(Hmm… what's in there…)$"

_DenseJungle_Starter_Egg_Subscript_Movement_15: @ Dbr-output
  face_right
  step_end

_DenseJungle_Starter_Egg_Subscript_Text_16: @ Dbr-output
  .string "I think it's a {COLOR POKEMON_COLOR}{STR_VAR_1}{COLOR NO_COLOR}!$"

_DenseJungle_Starter_Egg_Subscript_Movement_19: @ Dbr-output
  delay_16
  step_end

_DenseJungle_Starter_Egg_Subscript_Text_20: @ Dbr-output
  .string "Wow! {COLOR POKEMON_COLOR}{STR_VAR_1}{COLOR NO_COLOR}? Really?\p"
  .string "That's so awesome!$"

_DenseJungle_Starter_Egg_Subscript_Movement_21: @ Dbr-output
  delay_16
  delay_16
  walk_slow_right
  delay_16
  step_end

_DenseJungle_Starter_Egg_Subscript_Text_22: @ Dbr-output
  .string "You know…\p"
  .string "There's nobody around…$"

_DenseJungle_Starter_Egg_Subscript_Movement_23: @ Dbr-output
  face_player
  step_end

_DenseJungle_Starter_Egg_Subscript_Text_24: @ Dbr-output
  .string "What do you say we each take\n"
  .string "one of these?\p"
  .string "We'd have our very own {COLOR POKEMON_COLOR}Pokémon{COLOR NO_COLOR}!\l"
  .string "Nothing could stop us then!$"

_DenseJungle_Starter_Egg_Subscript_Movement_26: @ Dbr-output
  walk_slow_left
  walk_slow_up
  face_left
  delay_16
  step_end

_DenseJungle_Starter_Egg_Subscript_Text_27: @ Dbr-output
  .string "Come on, I'll take this one.\l"
  .string "Yoink! Now it's your turn!$"

_DenseJungle_Starter_Egg_Subscript_Movement_28: @ Dbr-output
  delay_16
  step_end

_DenseJungle_Starter_Egg_Subscript_Text_30: @ Dbr-output
  .string "With our own {COLOR POKEMON_COLOR}Pokémon{COLOR NO_COLOR}, we'll be\n"
  .string "unstoppable!\p"
  .string "Just think! We could take on…$"

_DenseJungle_Starter_Egg_Subscript_Movement_31: @ Dbr-output
  delay_16
  face_up
  delay_16
  step_end

_DenseJungle_Starter_Egg_Subscript_Text_33: @ Dbr-output
  .string "Do you see that {COLOR POKEMON_COLOR}giant shadow{COLOR NO_COLOR} on the\n"
  .string "horizon or is that just me?$"

_DenseJungle_Starter_Egg_Subscript_Movement_34: @ Dbr-output
  walk_slow_left
  face_up
  emote_exclamation_mark
  delay_16
  step_end

_DenseJungle_Starter_Egg_Subscript_Text_36: @ Dbr-output
  .string "{COLOR POKEMON_COLOR}???{COLOR NO_COLOR}: Gyaaaaah!$"

_DenseJungle_Starter_Egg_Subscript_Movement_38: @ Dbr-output
  emote_exclamation_mark
  step_end

_DenseJungle_Starter_Egg_Subscript_Text_39: @ Dbr-output
  .string "I think we found the {COLOR POKEMON_COLOR}Dragon{COLOR NO_COLOR}! Run!$"

_DenseJungle_Starter_Egg_Subscript_Movement_41: @ Dbr-output
  face_left
  delay_4
  face_down
  delay_4
  face_right
  delay_4
  walk_fast_down
  walk_fast_down
  walk_fast_down
  walk_fast_down
  walk_fast_down
  walk_fast_down
  walk_fast_down
  step_end

_DenseJungle_Starter_Egg_CenterPlayer:: @ Dbr-output
  getplayerxy VAR_RESULT, VAR_TEMP_1
  compare VAR_RESULT, 9
  goto_if_eq __DenseJungle_Starter_Egg_CenterPlayer_Subscript_Code_1
  compare VAR_RESULT, 10
  goto_if_eq __DenseJungle_Starter_Egg_CenterPlayer_Subscript_Code_3
  compare VAR_RESULT, 12
  goto_if_eq __DenseJungle_Starter_Egg_CenterPlayer_Subscript_Code_5
  compare VAR_RESULT, 13
  goto_if_eq __DenseJungle_Starter_Egg_CenterPlayer_Subscript_Code_7
  return

__DenseJungle_Starter_Egg_CenterPlayer_Subscript_Movement_0: @ Dbr-output
  walk_right
  walk_right
  step_end

__DenseJungle_Starter_Egg_CenterPlayer_Subscript_Code_1:: @ Dbr-output
  applymovement EVENT_OBJ_ID_PLAYER, __DenseJungle_Starter_Egg_CenterPlayer_Subscript_Movement_0
  waitmovement EVENT_OBJ_ID_PLAYER
  return

__DenseJungle_Starter_Egg_CenterPlayer_Subscript_Movement_2: @ Dbr-output
  walk_right
  step_end

__DenseJungle_Starter_Egg_CenterPlayer_Subscript_Code_3:: @ Dbr-output
  applymovement EVENT_OBJ_ID_PLAYER, __DenseJungle_Starter_Egg_CenterPlayer_Subscript_Movement_2
  waitmovement EVENT_OBJ_ID_PLAYER
  return

__DenseJungle_Starter_Egg_CenterPlayer_Subscript_Movement_4: @ Dbr-output
  walk_left
  step_end

__DenseJungle_Starter_Egg_CenterPlayer_Subscript_Code_5:: @ Dbr-output
  applymovement EVENT_OBJ_ID_PLAYER, __DenseJungle_Starter_Egg_CenterPlayer_Subscript_Movement_4
  waitmovement EVENT_OBJ_ID_PLAYER
  return

__DenseJungle_Starter_Egg_CenterPlayer_Subscript_Movement_6: @ Dbr-output
  walk_left
  walk_left
  step_end

__DenseJungle_Starter_Egg_CenterPlayer_Subscript_Code_7:: @ Dbr-output
  applymovement EVENT_OBJ_ID_PLAYER, __DenseJungle_Starter_Egg_CenterPlayer_Subscript_Movement_6
  waitmovement EVENT_OBJ_ID_PLAYER
  return