#ifndef GUARD_PORTRAIT_H
#define GUARD_PORTAIT_H

#define PORTRAIT_ENTRY_EMOTION(character, emotion) \
  {.name = gPortrait##character##Name, .pal = gPortrait##character##Pal, .gfx = gPortrait##character##emotion##Gfx, .textboxWidth = &gPortrait##character##TextboxWidth},

#define PORTRAIT_ENTRY(character)                     \
  PORTRAIT_ENTRY_EMOTION(character, Smile)            \
  PORTRAIT_ENTRY_EMOTION(character, Smirk)            \
  PORTRAIT_ENTRY_EMOTION(character, Angry)            \
  PORTRAIT_ENTRY_EMOTION(character, Frown)            \
  PORTRAIT_ENTRY_EMOTION(character, EyesClosed)       \
  PORTRAIT_ENTRY_EMOTION(character, EyesClosedGrin)   \
  PORTRAIT_ENTRY_EMOTION(character, Rant)             \
  PORTRAIT_ENTRY_EMOTION(character, SlightSmile)      \
  PORTRAIT_ENTRY_EMOTION(character, Sneaky)           \
  PORTRAIT_ENTRY_EMOTION(character, Devilish)         \
  PORTRAIT_ENTRY_EMOTION(character, Question)         \
  PORTRAIT_ENTRY_EMOTION(character, Crying)           \
  PORTRAIT_ENTRY_EMOTION(character, Sleeping)         \
  PORTRAIT_ENTRY_EMOTION(character, SmileClosedMouth) \
  PORTRAIT_ENTRY_EMOTION(character, DrunkGrin)        \
  PORTRAIT_ENTRY_EMOTION(character, WipedOutGrin)     \
  PORTRAIT_ENTRY_EMOTION(character, Alarmed)          \
  PORTRAIT_ENTRY_EMOTION(character, Wink)             \
  PORTRAIT_ENTRY_EMOTION(character, Unamused)         \
  PORTRAIT_ENTRY_EMOTION(character, Blush)            \
  PORTRAIT_ENTRY_EMOTION(character, Rage)             \
  PORTRAIT_ENTRY_EMOTION(character, Dazed)            \
  PORTRAIT_ENTRY_EMOTION(character, Sweat)            \
  PORTRAIT_ENTRY_EMOTION(character, Annoyed)

struct Portrait
{
  const u8 *name;
  const u32 *pal;
  const u32 *gfx;
  const u8 *textboxWidth;
};

void ShowPortrait(u8 character, u8 emotion, u8 right);
void ShowPlayerPortrait(u8 emotion, u8 right);
void HidePortrait(void);

#endif