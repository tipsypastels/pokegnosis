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

static const u8 gPortraitMeiliName[] = _("{PLAYER}");
static const u8 gPortraitMeiliTextboxWidth = 3;
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

/* Kai Portraits */

static const u8 gPortraitKaiName[] = _("{PLAYER}");
static const u8 gPortraitKaiTextboxWidth = 3;
static const u32 gPortraitKaiPal[] = INCBIN_U32("graphics/portraits/kai/_palette.gbapal.lz");
static const u32 gPortraitKaiSmileGfx[] = INCBIN_U32("graphics/portraits/kai/smile.4bpp.lz");
static const u32 gPortraitKaiSmirkGfx[] = INCBIN_U32("graphics/portraits/kai/smirk.4bpp.lz");
static const u32 gPortraitKaiAngryGfx[] = INCBIN_U32("graphics/portraits/kai/angry.4bpp.lz");
static const u32 gPortraitKaiFrownGfx[] = INCBIN_U32("graphics/portraits/kai/frown.4bpp.lz");
static const u32 gPortraitKaiEyesClosedGfx[] = INCBIN_U32("graphics/portraits/kai/eyesclosed.4bpp.lz");
static const u32 gPortraitKaiEyesClosedGrinGfx[] = INCBIN_U32("graphics/portraits/kai/eyesclosedgrin.4bpp.lz");
static const u32 gPortraitKaiRantGfx[] = INCBIN_U32("graphics/portraits/kai/rant.4bpp.lz");
static const u32 gPortraitKaiSlightSmileGfx[] = INCBIN_U32("graphics/portraits/kai/slightsmile.4bpp.lz");
static const u32 gPortraitKaiSneakyGfx[] = INCBIN_U32("graphics/portraits/kai/sneaky.4bpp.lz");
static const u32 gPortraitKaiDevilishGfx[] = INCBIN_U32("graphics/portraits/kai/devilish.4bpp.lz");
static const u32 gPortraitKaiQuestionGfx[] = INCBIN_U32("graphics/portraits/kai/question.4bpp.lz");
static const u32 gPortraitKaiCryingGfx[] = INCBIN_U32("graphics/portraits/kai/crying.4bpp.lz");
static const u32 gPortraitKaiSleepingGfx[] = INCBIN_U32("graphics/portraits/kai/sleeping.4bpp.lz");
static const u32 gPortraitKaiSmileClosedMouthGfx[] = INCBIN_U32("graphics/portraits/kai/smileclosedmouth.4bpp.lz");
static const u32 gPortraitKaiDrunkGrinGfx[] = INCBIN_U32("graphics/portraits/kai/drunkgrin.4bpp.lz");
static const u32 gPortraitKaiWipedOutGrinGfx[] = INCBIN_U32("graphics/portraits/kai/wipedoutgrin.4bpp.lz");
static const u32 gPortraitKaiAlarmedGfx[] = INCBIN_U32("graphics/portraits/kai/alarmed.4bpp.lz");
static const u32 gPortraitKaiWinkGfx[] = INCBIN_U32("graphics/portraits/kai/wink.4bpp.lz");
static const u32 gPortraitKaiUnamusedGfx[] = INCBIN_U32("graphics/portraits/kai/unamused.4bpp.lz");
static const u32 gPortraitKaiBlushGfx[] = INCBIN_U32("graphics/portraits/kai/blush.4bpp.lz");
static const u32 gPortraitKaiRageGfx[] = INCBIN_U32("graphics/portraits/kai/rage.4bpp.lz");
static const u32 gPortraitKaiDazedGfx[] = INCBIN_U32("graphics/portraits/kai/dazed.4bpp.lz");
static const u32 gPortraitKaiSweatGfx[] = INCBIN_U32("graphics/portraits/kai/sweat.4bpp.lz");
static const u32 gPortraitKaiAnnoyedGfx[] = INCBIN_U32("graphics/portraits/kai/annoyed.4bpp.lz");

/* Zheng Portraits */

static const u8 gPortraitZhengName[] = _("Zheng");
static const u8 gPortraitZhengTextboxWidth = 4;
static const u32 gPortraitZhengPal[] = INCBIN_U32("graphics/portraits/zheng/_palette.gbapal.lz");
static const u32 gPortraitZhengSmileGfx[] = INCBIN_U32("graphics/portraits/zheng/smile.4bpp.lz");
static const u32 gPortraitZhengSmirkGfx[] = INCBIN_U32("graphics/portraits/zheng/smirk.4bpp.lz");
static const u32 gPortraitZhengAngryGfx[] = INCBIN_U32("graphics/portraits/zheng/angry.4bpp.lz");
static const u32 gPortraitZhengFrownGfx[] = INCBIN_U32("graphics/portraits/zheng/frown.4bpp.lz");
static const u32 gPortraitZhengEyesClosedGfx[] = INCBIN_U32("graphics/portraits/zheng/eyesclosed.4bpp.lz");
static const u32 gPortraitZhengEyesClosedGrinGfx[] = INCBIN_U32("graphics/portraits/zheng/eyesclosedgrin.4bpp.lz");
static const u32 gPortraitZhengRantGfx[] = INCBIN_U32("graphics/portraits/zheng/rant.4bpp.lz");
static const u32 gPortraitZhengSlightSmileGfx[] = INCBIN_U32("graphics/portraits/zheng/slightsmile.4bpp.lz");
static const u32 gPortraitZhengSneakyGfx[] = INCBIN_U32("graphics/portraits/zheng/sneaky.4bpp.lz");
static const u32 gPortraitZhengDevilishGfx[] = INCBIN_U32("graphics/portraits/zheng/devilish.4bpp.lz");
static const u32 gPortraitZhengQuestionGfx[] = INCBIN_U32("graphics/portraits/zheng/question.4bpp.lz");
static const u32 gPortraitZhengCryingGfx[] = INCBIN_U32("graphics/portraits/zheng/crying.4bpp.lz");
static const u32 gPortraitZhengSleepingGfx[] = INCBIN_U32("graphics/portraits/zheng/sleeping.4bpp.lz");
static const u32 gPortraitZhengSmileClosedMouthGfx[] = INCBIN_U32("graphics/portraits/zheng/smileclosedmouth.4bpp.lz");
static const u32 gPortraitZhengDrunkGrinGfx[] = INCBIN_U32("graphics/portraits/zheng/drunkgrin.4bpp.lz");
static const u32 gPortraitZhengWipedOutGrinGfx[] = INCBIN_U32("graphics/portraits/zheng/wipedoutgrin.4bpp.lz");
static const u32 gPortraitZhengAlarmedGfx[] = INCBIN_U32("graphics/portraits/zheng/alarmed.4bpp.lz");
static const u32 gPortraitZhengWinkGfx[] = INCBIN_U32("graphics/portraits/zheng/wink.4bpp.lz");
static const u32 gPortraitZhengUnamusedGfx[] = INCBIN_U32("graphics/portraits/zheng/unamused.4bpp.lz");
static const u32 gPortraitZhengBlushGfx[] = INCBIN_U32("graphics/portraits/zheng/blush.4bpp.lz");
static const u32 gPortraitZhengRageGfx[] = INCBIN_U32("graphics/portraits/zheng/rage.4bpp.lz");
static const u32 gPortraitZhengDazedGfx[] = INCBIN_U32("graphics/portraits/zheng/dazed.4bpp.lz");
static const u32 gPortraitZhengSweatGfx[] = INCBIN_U32("graphics/portraits/zheng/sweat.4bpp.lz");
static const u32 gPortraitZhengAnnoyedGfx[] = INCBIN_U32("graphics/portraits/zheng/annoyed.4bpp.lz");

/* Kumiho Portraits */

static const u8 gPortraitKumihoName[] = _("Kumiho");
static const u8 gPortraitKumihoTextboxWidth = 5;
static const u32 gPortraitKumihoPal[] = INCBIN_U32("graphics/portraits/kumiho/_palette.gbapal.lz");
static const u32 gPortraitKumihoSmileGfx[] = INCBIN_U32("graphics/portraits/kumiho/smile.4bpp.lz");
static const u32 gPortraitKumihoSmirkGfx[] = INCBIN_U32("graphics/portraits/kumiho/smirk.4bpp.lz");
static const u32 gPortraitKumihoAngryGfx[] = INCBIN_U32("graphics/portraits/kumiho/angry.4bpp.lz");
static const u32 gPortraitKumihoFrownGfx[] = INCBIN_U32("graphics/portraits/kumiho/frown.4bpp.lz");
static const u32 gPortraitKumihoEyesClosedGfx[] = INCBIN_U32("graphics/portraits/kumiho/eyesclosed.4bpp.lz");
static const u32 gPortraitKumihoEyesClosedGrinGfx[] = INCBIN_U32("graphics/portraits/kumiho/eyesclosedgrin.4bpp.lz");
static const u32 gPortraitKumihoRantGfx[] = INCBIN_U32("graphics/portraits/kumiho/rant.4bpp.lz");
static const u32 gPortraitKumihoSlightSmileGfx[] = INCBIN_U32("graphics/portraits/kumiho/slightsmile.4bpp.lz");
static const u32 gPortraitKumihoSneakyGfx[] = INCBIN_U32("graphics/portraits/kumiho/sneaky.4bpp.lz");
static const u32 gPortraitKumihoDevilishGfx[] = INCBIN_U32("graphics/portraits/kumiho/devilish.4bpp.lz");
static const u32 gPortraitKumihoQuestionGfx[] = INCBIN_U32("graphics/portraits/kumiho/question.4bpp.lz");
static const u32 gPortraitKumihoCryingGfx[] = INCBIN_U32("graphics/portraits/kumiho/crying.4bpp.lz");
static const u32 gPortraitKumihoSleepingGfx[] = INCBIN_U32("graphics/portraits/kumiho/sleeping.4bpp.lz");
static const u32 gPortraitKumihoSmileClosedMouthGfx[] = INCBIN_U32("graphics/portraits/kumiho/smileclosedmouth.4bpp.lz");
static const u32 gPortraitKumihoDrunkGrinGfx[] = INCBIN_U32("graphics/portraits/kumiho/drunkgrin.4bpp.lz");
static const u32 gPortraitKumihoWipedOutGrinGfx[] = INCBIN_U32("graphics/portraits/kumiho/wipedoutgrin.4bpp.lz");
static const u32 gPortraitKumihoAlarmedGfx[] = INCBIN_U32("graphics/portraits/kumiho/alarmed.4bpp.lz");
static const u32 gPortraitKumihoWinkGfx[] = INCBIN_U32("graphics/portraits/kumiho/wink.4bpp.lz");
static const u32 gPortraitKumihoUnamusedGfx[] = INCBIN_U32("graphics/portraits/kumiho/unamused.4bpp.lz");
static const u32 gPortraitKumihoBlushGfx[] = INCBIN_U32("graphics/portraits/kumiho/blush.4bpp.lz");
static const u32 gPortraitKumihoRageGfx[] = INCBIN_U32("graphics/portraits/kumiho/rage.4bpp.lz");
static const u32 gPortraitKumihoDazedGfx[] = INCBIN_U32("graphics/portraits/kumiho/dazed.4bpp.lz");
static const u32 gPortraitKumihoSweatGfx[] = INCBIN_U32("graphics/portraits/kumiho/sweat.4bpp.lz");
static const u32 gPortraitKumihoAnnoyedGfx[] = INCBIN_U32("graphics/portraits/kumiho/annoyed.4bpp.lz");

/* Portraits List */

static const struct Portrait gPortraitList[] = {
    PORTRAIT_ENTRY(Meili)
    PORTRAIT_ENTRY(Kai)
    PORTRAIT_ENTRY(Zheng)
    PORTRAIT_ENTRY(Kumiho)
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

void ShowPortrait(u8 character, u8 emotion, u8 right) {
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

  SetWindowTemplateFields(&template, 0, right ? (21 - (*portrait.textboxWidth - 3)) : 6, 203, *portrait.textboxWidth, 2, 15, 8);
  sTalkingBoxWindowId = AddWindow(&template);
  FillWindowPixelBuffer(sTalkingBoxWindowId, PIXEL_FILL(0));
  PutWindowTilemap(sTalkingBoxWindowId);
  CopyWindowToVram(sTalkingBoxWindowId, 1);

  DrawStdFrameWithCustomTileAndPalette(sTalkingBoxWindowId, FALSE, 0x214, 14);
  StringExpandPlaceholders(gStringVar4, portrait.name);
  AddTextPrinterParameterized(sTalkingBoxWindowId, 1, gStringVar4, 1, 1, 0, NULL);

  LoadCompressedSpriteSheet(&sprites);
  LoadCompressedSpritePalette(&palette);
  sPortraitSpriteId = CreateSprite(&sSpriteTemplate_TestPortrait, right ? (240 - 22) : 22, 94, 0);
}

void ShowPlayerPortrait(u8 emotion, u8 right) {
  if (gSaveBlock2Ptr->playerGender == MALE) {
    ShowPortrait(PORTRAIT_KAI, emotion, right);
  } else {
    ShowPortrait(PORTRAIT_MEILI, emotion, right);
  }
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
