#ifndef GUARD_BOOK_H
#define GUARD_BOOK_H

struct BookStyle
{
  const u32 *tilemap;
  const u32 *tiles;
  const u8 *color;
};

void CB2_ShowBook(void);

#endif // GUARD_BOOK_H
