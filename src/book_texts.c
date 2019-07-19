#include "global.h"

static const u8 gBook_Test[] = _("\nAnd the Nonman King cried words that sting:\nNow to me you must confess,\nFor death above you hovers!\nAnd the Emissary answered ever wary:\nWe are the race of flesh,\nWe are the race of lovers.");

static const u8 gBook_SunXia_End[] = _("\nWhen Sun Xia left the jungle after many\nmoons, she brought with her many\nfollowers, humans and Pokémon alike.\nTogether they journeyed to the golden\ntower on the golden mountain, where the\nDragon had first departed this world.\n'Please,' she begged the sky, 'let there\nbe peace in Tenso!'");

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