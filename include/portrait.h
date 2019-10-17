#ifndef GUARD_PORTRAIT_H
#define GUARD_PORTAIT_H

#define PORTRAIT_SMILE 0
#define PORTRAIT_SMIRK 1
#define PORTRAIT_ANGRY 2
#define PORTRAIT_FROWN 3
#define PORTRAIT_EYESCLOSED 4
#define PORTRAIT_EYESCLOSEDGRIN 5
#define PORTRAIT_RANT 6
#define PORTRAIT_SLIGHTSMILE 7
#define PORTRAIT_SNEAKY 8
#define PORTRAIT_DEVILISH 9
#define PORTRAIT_QUESTION 10
#define PORTRAIT_CRYING 11
#define PORTRAIT_SLEEPING 12
#define PORTRAIT_SMILECLOSEDMOUTH 13
#define PORTRAIT_DRUNKGRIN 14
#define PORTRAIT_WIPEDOUTGRIN 15
#define PORTRAIT_ALARMED 16
#define PORTRAIT_WINK 17
#define PORTRAIT_UNAMUSED 18
#define PORTRAIT_BLUSH 19
#define PORTRAIT_RAGE 20
#define PORTRAIT_DAZED 21
#define PORTRAIT_SWEAT 22
#define PORTRAIT_ANNOYED 23

#define PORTRAIT_ENTRY_EMOTION(character, emotion) \
  {.name = gPortrait##character##Name, .pal = gPortrait##character##Pal, .gfx = gPortrait##character##emotion##Gfx},

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
};

void ShowPortrait(u8 character, u8 emotion);
void HidePortrait(void);

#endif