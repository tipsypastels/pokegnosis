#include "global.h"

static const u8 gBook_Test[] = _("\nAnd the Nonman King cried words that sting:\nNow to me you must confess,\nFor death above you hovers!\nAnd the Emissary answered ever wary:\nWe are the race of flesh,\nWe are the race of lovers.");

static const u8 gBook_SunXia_End[] = _("\nWhen Sun Xia left the jungle after many\nmoons, she brought with her many\nfollowers, humans and Pokémon alike.\nTogether they journeyed to the golden\ntower on the golden mountain, where the\nDragon had first departed this world.\n'Please,' she begged the sky, 'let there\nbe peace in Ximir!'");

static const u8 *const gBookList[] = {
    gBook_Test,
    gBook_SunXia_End,
};

const u8 *const getBook(u8 index)
{
    if (index < sizeof(gBookList) / sizeof(gBookList[0]))
        return gBookList[index];
    return "Bad book index :/";
}

/*
    And the Nonman King cried words that sting:
    Now to me you must confess,
    For death above you hovers!
    And the Emissary answered ever wary:
    We are the race of flesh,\nWe are the race of lovers.

    When Sun Xia left the jungle after many
    moons, she brought with her many followers,
    humans and Pokémon alike. Together they
    journeyed to the golden tower on the
    golden mountain, where the Dragon had
    first departed this world.  
    "Please," she begged the sky, "let there
    be peace in Ximir!"
*/