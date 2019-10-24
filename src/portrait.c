#include "global.h"
#include "portrait.h"
#include "constants/portraits.h"
#include "graphics.h"
#include "event_data.h"
#include "string_util.h"
#include "text.h"
#include "menu.h"
#include "window.h"
#include "sprite.h"
#include "strings.h"
#include "decompress.h"

/* Meili Portraits */

static const u8 gPortraitMeiliName[] = _("Meili");
static const u32 gPortraitMeiliPal[] = INCBIN_U32("graphics/portraits/meili/_palette.gbapal.lz");
static const u32 gPortraitMeiliSmileGfx[] = INCBIN_U32("graphics/portraits/meili/smile.4bpp.lz");
static const u32 gPortraitMeiliSmirkGfx[] = INCBIN_U32("graphics/portraits/meili/smirk.4bpp.lz");
static const u32 gPortraitMeiliAngryGfx[] = INCBIN_U32("graphics/portraits/meili/angry.4bpp.lz");
static const u32 gPortraitMeiliFrownGfx[] = INCBIN_U32("graphics/portraits/meili/frown.4bpp.lz");
static const u32 gPortraitMeiliEyesClosedGfx[] = INCBIN_U32("graphics/portraits/meili/eyesclosed.4bpp.lz");
static const u32 gPortraitMeiliEyesClosedGrinGfx[] = INCBIN_U32("graphics/portraits/meili/eyesclosedgrin.4bpp.lz");
static const u32 gPortraitMeiliRantGfx[] = INCBIN_U32("graphics/portraits/meili/rant.4bpp.lz");
static const u32 gPortraitMeiliSlightSmileGfx[] = INCBIN_U32("graphics/portraits/meili/slightsmile.4bpp.lz");
static const u32 gPortraitMeiliSneakyGfx[] = INCBIN_U32("graphics/portraits/meili/sneaky.4bpp.lz");
static const u32 gPortraitMeiliDevilishGfx[] = INCBIN_U32("graphics/portraits/meili/devilish.4bpp.lz");
static const u32 gPortraitMeiliQuestionGfx[] = INCBIN_U32("graphics/portraits/meili/question.4bpp.lz");
static const u32 gPortraitMeiliCryingGfx[] = INCBIN_U32("graphics/portraits/meili/crying.4bpp.lz");
static const u32 gPortraitMeiliSleepingGfx[] = INCBIN_U32("graphics/portraits/meili/sleeping.4bpp.lz");
static const u32 gPortraitMeiliSmileClosedMouthGfx[] = INCBIN_U32("graphics/portraits/meili/smileclosedmouth.4bpp.lz");
static const u32 gPortraitMeiliDrunkGrinGfx[] = INCBIN_U32("graphics/portraits/meili/drunkgrin.4bpp.lz");
static const u32 gPortraitMeiliWipedOutGrinGfx[] = INCBIN_U32("graphics/portraits/meili/wipedoutgrin.4bpp.lz");
static const u32 gPortraitMeiliAlarmedGfx[] = INCBIN_U32("graphics/portraits/meili/alarmed.4bpp.lz");
static const u32 gPortraitMeiliWinkGfx[] = INCBIN_U32("graphics/portraits/meili/wink.4bpp.lz");
static const u32 gPortraitMeiliUnamusedGfx[] = INCBIN_U32("graphics/portraits/meili/unamused.4bpp.lz");
static const u32 gPortraitMeiliBlushGfx[] = INCBIN_U32("graphics/portraits/meili/blush.4bpp.lz");
static const u32 gPortraitMeiliRageGfx[] = INCBIN_U32("graphics/portraits/meili/rage.4bpp.lz");
static const u32 gPortraitMeiliDazedGfx[] = INCBIN_U32("graphics/portraits/meili/dazed.4bpp.lz");
static const u32 gPortraitMeiliSweatGfx[] = INCBIN_U32("graphics/portraits/meili/sweat.4bpp.lz");
static const u32 gPortraitMeiliAnnoyedGfx[] = INCBIN_U32("graphics/portraits/meili/annoyed.4bpp.lz");

/* Portraits List */

static const struct Portrait gPortraitList[] = {
    PORTRAIT_ENTRY(Meili)
};

/* End Portraits */

#define PORTRAIT_TAG 0x2722

static const struct OamData sOamData_TestPortrait =
    {
        .y = 0,
        .affineMode = 0,
        .objMode = 0,
        .mosaic = 0,
        .bpp = 0,
        .shape = SPRITE_SHAPE(64x64),
        .x = 0,
        .matrixNum = 0,
        .size = SPRITE_SIZE(64x64),
        .tileNum = 0,
        .priority = 0,
        .paletteNum = 0,
        .affineParam = 0,
};

static const union AnimCmd sSpriteAnim_TestPortrait[] =
{
  ANIMCMD_FRAME(0, 0),
  ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_TestPortrait[] =
{
  sSpriteAnim_TestPortrait,
};

static const struct SpriteTemplate sSpriteTemplate_TestPortrait =
{
  .tileTag = PORTRAIT_TAG,
  .paletteTag = PORTRAIT_TAG,
  .oam = &sOamData_TestPortrait,
  .anims = sSpriteAnimTable_TestPortrait,
  .images = NULL,
  .affineAnims = gDummySpriteAffineAnimTable,
  .callback = SpriteCallbackDummy,
};

EWRAM_DATA static u8 sTalkingBoxWindowId = 0;
EWRAM_DATA static u8 sPortraitSpriteId = 0;

static void HidePortraitSpeakerName(void);
static void HidePortraitGraphic(void);

void ShowPortrait(u8 character, u8 emotion) {
  struct WindowTemplate template;
  u8 currentPortraitIndex = (character * PORTRAIT_EMOTIONS_COUNT) + emotion;
  // u8 currentPortraitIndex = (u8) VarGet(VAR_CURRENT_PORTRAIT);
  const struct Portrait portrait = gPortraitList[currentPortraitIndex];

  const struct CompressedSpritePalette palette = {
    .data = portrait.pal,
    .tag = PORTRAIT_TAG,
  };

  const struct CompressedSpriteSheet sprites = {
    .data = portrait.gfx,
    .size = 2048,
    .tag = PORTRAIT_TAG,
  };

  SetWindowTemplateFields(&template, 0, 6, 203, 3, 2, 15, 8);
  sTalkingBoxWindowId = AddWindow(&template);
  FillWindowPixelBuffer(sTalkingBoxWindowId, PIXEL_FILL(0));
  PutWindowTilemap(sTalkingBoxWindowId);
  CopyWindowToVram(sTalkingBoxWindowId, 1);

  DrawStdFrameWithCustomTileAndPalette(sTalkingBoxWindowId, FALSE, 0x214, 14);
  StringExpandPlaceholders(gStringVar4, portrait.name);
  AddTextPrinterParameterized(sTalkingBoxWindowId, 1, gStringVar4, 1, 1, 0, NULL);

  LoadCompressedSpriteSheet(&sprites);
  LoadCompressedSpritePalette(&palette);
  sPortraitSpriteId = CreateSprite(&sSpriteTemplate_TestPortrait, 22, 94, 0);
}

void ShowPlayerPortrait(u8 emotion) {
  ShowPortrait(PORTRAIT_MEILI, emotion);
  // if (gSaveBlock2Ptr->playerGender == MALE) {
  //   // TODO kai portrait
  // } else {
  //   ShowPortrait(PORTRAIT_MEILI, emotion);
  // }
}

void HidePortrait(void) {
  HidePortraitGraphic();
  HidePortraitSpeakerName();
}

static void HidePortraitSpeakerName(void)
{
  ClearStdWindowAndFrameToTransparent(sTalkingBoxWindowId, FALSE);
  CopyWindowToVram(sTalkingBoxWindowId, 2);
  RemoveWindow(sTalkingBoxWindowId);
}

static void HidePortraitGraphic(void)
{
  DestroySpriteAndFreeResources(&gSprites[sPortraitSpriteId]);
}
