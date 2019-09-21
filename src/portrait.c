#include "global.h"
#include "portrait.h"
#include "graphics.h"
#include "event_data.h"
#include "string_util.h"
#include "text.h"
#include "menu.h"
#include "window.h"
#include "sprite.h"
#include "strings.h"
#include "decompress.h"

static const u32 gPortraitMeiliPal[] = INCBIN_U32("graphics/portraits/meili.gbapal.lz");
static const u32 gPortraitMeiliSmileGfx[] = INCBIN_U32("graphics/portraits/meili_smile.4bpp.lz");
static const u32 gPortraitMeiliTestGfx[] = INCBIN_U32("graphics/portraits/meili_test.4bpp.lz");
static const u8 gPortraitMeiliName[] = _("Meili");
static const u8 gPortraitMeiliName2[] = _("Xeili");

static const struct Portrait gPortraitList[] = {
    {.name = gPortraitMeiliName, .pal = gPortraitMeiliPal, .gfx = gPortraitMeiliSmileGfx},
    {.name = gPortraitMeiliName2, .pal = gPortraitMeiliPal, .gfx = gPortraitMeiliTestGfx},
};

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

void ShowPortrait(void) {
  struct WindowTemplate template;

  u8 currentPortraitIndex = (u8) VarGet(VAR_CURRENT_PORTRAIT);
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
