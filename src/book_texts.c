#include "global.h"

// Misc

static const u8 gBook_FishingJoke_1[] = _("\nThere be rare Pokémon in these waters.");

// Player Diaries

static const u8 gBook_PlayerDiary_1[] = _("\nZheng said he had something cool to show\nme today! I can't wait to see what it is!\nGotta get out of the house, Rui's been\nsuch an annoying brat lately :V");

// Sun Xia

static const u8 gBook_SunXia_End[] = _("\nWhen Sun Xia left the jungle after many\nmoons, she brought with her many\nfollowers, humans and Pokémon alike.\nTogether they journeyed to the golden\ntower on the golden mountain, where the\nDragon had first departed this world.\n'Please,' she begged the sky, 'let there\nbe peace in Tenso!'");

// Ballad of the Mad Emperor

static const u8 gBook_BOTME_11[] = _("\nAt the foot of the Golden summit\nUang came across a wise Altaria\nThe creature intoned, voice like a horn\n“I beseech thee, retreat!\nFor death around thee slithers!”\nAnd Uang replied with voice of scorn\n“Yet my journey is incomplete,\nAllow me to pass hither!”");

static const u8 *const gBookList[] = {
    gBook_PlayerDiary_1,
    gBook_SunXia_End,
    gBook_BOTME_11,
    gBook_FishingJoke_1,
};

const u8 *const getBook(u8 index)
{
    if (index < sizeof(gBookList) / sizeof(gBookList[0]))
        return gBookList[index];
    return "Bad book index :/";
}