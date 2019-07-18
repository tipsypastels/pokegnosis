#include "global.h"

static const u8 gBook_Test[] = _("And the Nonman King cried words that string:\nNow to me you must confess,\nFor death above you hovers!\nAnd the Emissary answered ever wary:\nWe are the race of flesh,\nWe are the race of lovers.");

static const u8 *const gBookList[] = {
    gBook_Test,
};

const u8 *const getBook(u8 index)
{
    if (index < sizeof(gBookList) / sizeof(gBookList[0]))
        return gBookList[index];
    return "Bad book index :/";
}