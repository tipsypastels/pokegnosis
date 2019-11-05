#include "global.h"
#include "book.h"
#include "book_texts.h"
#include "palette.h"
#include "main.h"
#include "gpu_regs.h"
#include "scanline_effect.h"
#include "task.h"
#include "malloc.h"
#include "decompress.h"
#include "bg.h"
#include "window.h"
#include "string_util.h"
#include "text.h"
#include "overworld.h"
#include "menu.h"
#include "pokedex.h"
#include "constants/rgb.h"
#include "constants/vars.h"
#include "event_data.h"

static void MainCB2(void);
static void Task_BookFadeIn(u8);
static void Task_BookWaitForKeyPress(u8);
static void Task_BookFadeOut(u8);
static void DisplayBookText(void);
static void InitBookBg(void);
static void InitBookWindow(void);
static void PrintBookText(u8 *, u8, u8);

EWRAM_DATA static u8 *sBookTilemapPtr = NULL;

static void VBlankCB(void)
{
  LoadOam();
  ProcessSpriteCopyRequests();
  TransferPlttBuffer();
}

// TODO investigate this
static const u16 sBookPalettes[][16] =
    {
        INCBIN_U16("graphics/misc/book.gbapal"),
        INCBIN_U16("graphics/misc/book.gbapal"),
};

static const u32 sBookTilemap[] = INCBIN_U32("graphics/misc/book_map.bin.lz");
static const u32 sBookTiles[] = INCBIN_U32("graphics/misc/book.4bpp.lz");
static const u8 sBookColor[] = { 0, 2, 3 };

static const struct BookStyle sBookStyleList[] = {
  {
    .tilemap = sBookTilemap,
    .tiles = sBookTiles,
    .color = sBookColor,
  },
};

void CB2_ShowBook(void)
{
  SetVBlankCallback(NULL);
  SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0);
  SetGpuReg(REG_OFFSET_BG3CNT, DISPCNT_MODE_0);
  SetGpuReg(REG_OFFSET_BG2CNT, DISPCNT_MODE_0);
  SetGpuReg(REG_OFFSET_BG1CNT, DISPCNT_MODE_0);
  SetGpuReg(REG_OFFSET_BG0CNT, DISPCNT_MODE_0);
  SetGpuReg(REG_OFFSET_BG3HOFS, DISPCNT_MODE_0);
  SetGpuReg(REG_OFFSET_BG3VOFS, DISPCNT_MODE_0);
  SetGpuReg(REG_OFFSET_BG2HOFS, DISPCNT_MODE_0);
  SetGpuReg(REG_OFFSET_BG2VOFS, DISPCNT_MODE_0);
  SetGpuReg(REG_OFFSET_BG1HOFS, DISPCNT_MODE_0);
  SetGpuReg(REG_OFFSET_BG1VOFS, DISPCNT_MODE_0);
  SetGpuReg(REG_OFFSET_BG0HOFS, DISPCNT_MODE_0);
  SetGpuReg(REG_OFFSET_BG0VOFS, DISPCNT_MODE_0);
  // why doesn't this one use the dma manager either?
  DmaFill16(3, 0, VRAM, VRAM_SIZE);
  DmaFill32(3, 0, OAM, OAM_SIZE);
  DmaFill16(3, 0, PLTT, PLTT_SIZE);
  ScanlineEffect_Stop();
  ResetTasks();
  ResetSpriteData();
  ResetPaletteFade();
  FreeAllSpritePalettes();
  LoadPalette(sBookPalettes, 0, 64);
  sBookTilemapPtr = malloc(0x1000);
  InitBookBg();
  InitBookWindow();
  reset_temp_tile_data_buffers();
  decompress_and_copy_tile_data_to_vram(1, &sBookTiles, 0, 0, 0);
  while (free_temp_tile_data_buffers_if_possible())
    ;
  LZDecompressWram(sBookTilemap, sBookTilemapPtr);
  CopyBgTilemapBufferToVram(1);
  DisplayBookText();
  BlendPalettes(-1, 16, 0);
  BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
  EnableInterrupts(1);
  SetVBlankCallback(VBlankCB);
  SetMainCallback2(MainCB2);
  CreateTask(Task_BookFadeIn, 0);
}

static void MainCB2(void)
{
  RunTasks();
  AnimateSprites();
  BuildOamBuffer();
  UpdatePaletteFade();
}

static void Task_BookFadeIn(u8 taskId)
{
  if (!gPaletteFade.active)
    gTasks[taskId].func = Task_BookWaitForKeyPress;
}

static void Task_BookWaitForKeyPress(u8 taskId)
{
  if (gMain.newKeys & (A_BUTTON | B_BUTTON))
  {
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = Task_BookFadeOut;
  }
}

static void Task_BookFadeOut(u8 taskId)
{
  if (!gPaletteFade.active)
  {
    Free(sBookTilemapPtr);
    FreeAllWindowBuffers();
    DestroyTask(taskId);
    SetMainCallback2(sub_80861E8);
  }
}

static void DisplayBookText(void)
{
  u8 currentBookIdx = (u8) VarGet(VAR_CURRENT_BOOK);

  StringExpandPlaceholders(gStringVar4, getBook(currentBookIdx));
  PrintBookText(gStringVar4, 0, 1);
  PutWindowTilemap(0);
  CopyWindowToVram(0, 3);
}

static const struct BgTemplate sBookBgTemplates[2] =
    {
        {
            .bg = 0,
            .charBaseIndex = 1,
            .mapBaseIndex = 31,
            .screenSize = 0,
            .paletteMode = 0,
            .priority = 0,
            .baseTile = 0,
        },
        {
            .bg = 1,
            .charBaseIndex = 0,
            .mapBaseIndex = 6,
            .screenSize = 1,
            .paletteMode = 0,
            .priority = 1,
            .baseTile = 0,
        },
};

static void InitBookBg(void)
{
  ResetBgsAndClearDma3BusyFlags(0);
  InitBgsFromTemplates(0, sBookBgTemplates, 2);
  SetBgTilemapBuffer(1, sBookTilemapPtr);
  SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
  ShowBg(0);
  ShowBg(1);
  SetGpuReg(REG_OFFSET_BLDCNT, DISPCNT_MODE_0);
  SetGpuReg(REG_OFFSET_BLDALPHA, DISPCNT_MODE_0);
  SetGpuReg(REG_OFFSET_BLDY, DISPCNT_MODE_0);
}

static const struct WindowTemplate sBookWinTemplates[2] =
    {
        {
            .bg = 0,
            .tilemapLeft = 3,
            .tilemapTop = 2,
            .width = 30,
            .height = 16,
            .paletteNum = 15,
            .baseBlock = 1,
        },
        DUMMY_WIN_TEMPLATE,
};

static void InitBookWindow(void)
{
  InitWindows(sBookWinTemplates);
  DeactivateAllTextPrinters();
  LoadPalette(gUnknown_0860F074, 0xF0, 0x20);
  FillWindowPixelBuffer(0, PIXEL_FILL(0));
  PutWindowTilemap(0);
}

static void PrintBookText(u8 *text, u8 var1, u8 var2)
{
  u8 color[3] = {0, 2, 3};

  // TODO handwritten text font
  AddTextPrinterParameterized4(0, 0, var1, var2, 0, 0, color, -1, text);
}
