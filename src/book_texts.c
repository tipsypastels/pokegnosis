#include "global.h"

static const u8 gBook_Test[] = _("TEST BOOK TEXT");

static const u8 *const gBookList[] = {
    gBook_Test,
};

const u8 *const getBook(u8 index)
{
    if (index < sizeof(gBookList) / sizeof(gBookList[0]))
        return gBookList[index];
    return "Bad book index :/"; 
}