#ifndef GUARD_PORTRAIT_H
#define GUARD_PORTAIT_H

struct Portrait
{
  const u8 *name;
  const u32 *pal;
  const u32 *gfx;
};

void ShowPortrait(void);
void HidePortrait(void);

#endif