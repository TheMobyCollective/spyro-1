#include <sys/types.h>

#include <libcd.h>
#include <libetc.h>
#include <libmcrd.h>
#include <libpad.h>

#include "4BEF8.h"
#include "buffers.h"
#include "camera.h"
#include "cd.h"
#include "checkpoint.h"
#include "common.h"
#include "cutscene.h"
#include "environment.h"
#include "gamepad.h"
#include "gamestates/init.h"
#include "graphics.h"
#include "images.h"
#include "loaders.h"
#include "memory.h"
#include "music.h"
#include "save_file.h"
#include "sony_image.h"
#include "spu.h"
#include "spyro.h"
#include "variables.h"
#include "wad.h"

#include <stdio.h>

extern int _stacksize;

// Graphics init
void GraphicsInitialize(void) {
  RECT clearRect;

  SetDispMask(0);   // Disable display
  ResetGraph(0);    // Reset the GPU
  SetGraphDebug(0); // Disable debug output

  /*
   * +-------------------------+-------------------------+
   * |                         |                         |
   * |                         |                         |
   * |     Frame buffer 1      |                         |
   * |                         |                         |
   * |                         |                         |
   * +-------------------------+         Textures        |
   * |                         |                         |
   * |                         |                         |
   * |     Frame buffer 2      |                         |
   * |                         |                         |
   * |                         |                         |
   * +-------------------------+-------------------------+
   */

  // When we're drawing to db 0, we want to display db 1
  // and vice versa
  SetDefDrawEnv(&g_DB[0].m_DrawEnv, 0, 8, 512, 224);
  SetDefDrawEnv(&g_DB[1].m_DrawEnv, 0, 248, 512, 224);
  SetDefDispEnv(&g_DB[0].m_DispEnv, 0, 240, 512, 240);
  SetDefDispEnv(&g_DB[1].m_DispEnv, 0, 0, 512, 240);

  g_DB[0].m_DrawEnv.ofs[1] = 0;
  g_DB[1].m_DrawEnv.ofs[1] = 240;
  g_DB[0].m_DrawEnv.isbg = 1; // Enable auto-clear
  g_DB[1].m_DrawEnv.isbg = 1;
  g_DB[0].m_DrawEnv.dtd = 1; // Enable dithering
  g_DB[1].m_DrawEnv.dtd = 1;

  // Clear both screen buffers
  setRECT(&clearRect, 0, 0, 512, 512);
  ClearImage(&clearRect, 0, 0, 0);

  DrawSync(0);    // Wait for the GPU to finish
  SetDispMask(1); // Enable display
}

// Gamepad init, sets up VSync callback
void GamepadInitialize(void) {
  PadInitDirect((u_char *)&g_PadBuffer, (u_char *)&g_PadBufferSecondController);
  PadCaliReset(&g_PadBackup); // Clears the backup's calibration values
  PadCaliInit(&g_PadBackup);  // Initializes its calibration deadzone values

  // Reset the vibration timers
  D_80075904 = 0;
  D_80075764 = 0;
  D_800757D0 = 0;
  D_8007584C = 0;

  // Flag that enables analog input
  D_80075730 = 1;

  PadStartCom();

  // Call the VSync callback once (useless)
  PadVSync();

  // Set the VSync callback
  VSyncCallback(PadVSync);
}

// Initializes Memory Card
void MemoryCardInitialize(void) { MemCardInit(0); }

// Initializes the CD stuff
void CDInitialize(void) {
  u_char modeFlags = CdlModeSpeed;

  CdInit();

  // Set the mode to double speed
  CdControl(CdlSetmode, &modeFlags, 0);

  CdReadCallback(CDReadDone);

  g_CdMusic.m_Flags = 0x40;
  g_CdMusic.m_PostCDCommand = 0;
  g_CdMusic.m_Flags2 = 0;

  // Initializes the stereo mixing
  g_CdMusic.m_Aud.val2 = 127; /* volume for CD(R) -> SPU (L) */
  g_CdMusic.m_Aud.val0 = 127; /* volume for CD(L) -> SPU (L) */
  g_CdMusic.m_Aud.val3 = 0;   /* volume for CD(R) -> SPU (R) */
  g_CdMusic.m_Aud.val1 = 0;   /* volume for CD(L) -> SPU (R) */

  CdMix(&g_CdMusic.m_Aud);
}

// Loads the WAD header
void WadInitialize(void) {
  // TODO: lba.h from mkpsxiso
  g_CdState.m_WadSector = 37;

  // Read the WAD header into overlay space
  CDLoadSync(g_CdState.m_WadSector, g_OverlaySpacePointer, 2048, 0, 600);

  // Copy the WAD header to the global struct
  Memcpy(&g_WadHeader, g_OverlaySpacePointer, sizeof(g_WadHeader));
}

// Initializes the music table
int MusicInitialize(void) {
  // Unused 8 byte string, likely a sprintf leftover
  u_char pad[8];
  int i, j, tableIdx;

  for (i = 0; i < PETE_XA_COUNT; i++) {
    for (j = 0; j < PETE_XA_TRACKS; j++) {
      tableIdx = i * PETE_XA_TRACKS + j;
      g_CdMusic.m_MusicTable[tableIdx].start = D_8006F200[i];
      g_CdMusic.m_MusicTable[tableIdx].end = D_8006F200[i] + D_8006EEDC[i][j];
    }
  }

  g_CdMusic.m_Flags = 0x40;

  // Returns 1, in the demo version it returns 0 if it fails to find the sector
  // of the XA files
  return 1;
}

// Resets some saved stuff
void func_80012604(void) {
  u_char *writer;
  int i, j;

  for (i = 0; i < TOTAL_LEVEL_COUNT; i++) {
    g_LevelGemCount[i] = 0;
    g_LevelDragonCount[i] = 0;

    if (i < LEVEL_PER_HOMEWORLD * 3) {
      g_LevelEggCount[i] = 0;
    }

    g_VisitedFlags[i] = 0;
    g_LevelVortexExitFlags[i] = 0;
  }

  // I had to create the writer variable to get it to match
  for (i = HOMEWORLD_COUNT - 1, writer = &D_800758D0[HOMEWORLD_COUNT - 1];
       i >= 0; i--) {
    *(writer--) = 0;
  }

  D_800758D0[0] = 2; // Set the first homeworld as unlocked

  // Reset course records and flight collected
  for (i = 0; i < HOMEWORLD_COUNT; i++) {
    g_FlightCourseRecords[i] = 0; // Course records to 0
    for (j = 0; j < 5; j++) {
      g_FlightCollected[i][j] = 0; // Flight collected to 0
    }
  }

  g_Spyro.m_health = 3; // Set Spyro's health to 3
  g_SpyroLifeCount = 4; // Set Spyro's extra life count to 4

  g_GemTotal = 0;
  g_DragonTotal = 0;
  g_EggTotal = 0;

  // Reset in-level variables
  D_8007587C = 0;             // Gems collected before entering the level
  g_NGemsSinceLevelEntry = 0; // Gems collected in this level
  D_80075830 = 0;             // Key flag
  g_LifeOrbCount = 0;         // Life orb count
  D_8007580C = -1;            // Health before entering flight level

  D_80075838 = 0; // Unused var 1
  D_8007583C = 0; // Unused var 2

  Memset(&g_Checkpoint, 0, sizeof(g_Checkpoint));

  /* Size doesn't match what's allocated */
  Memset(&D_80077908, 0, TOTAL_LEVEL_COUNT * 32);
}

void func_8001277C(void) {
  // Resets some stuff
  g_LevelId = 10;   // Set the current level to Artisans
  g_ActEnabled = 1; // Enables the actuators
  D_80075914 = 82;  // Sets the camera to passive mode

  func_80012604(); // Resets some saved stuff
}

void func_titlescreen_8007DDE8(void); // Titlescreen terminator

// Init function
void Initialize(void) {
  RECT frameRect;
  RECT pad;
  char *levelVram;
  char *universalImage;
  int i;
  int j;
  int k;
  int l;
  int frameCountStart;
  const int blend_start = 224;
  const int blend_end = 0;
  const int blend_step_count = 8;
  const int blend_step = (blend_start - blend_end) / (blend_step_count - 1);
  const int rgb24_w = (512 / 2) * 3;
  const int rgb24_h = 240;
  const int image_size = 512 * 3 * 240;

  GraphicsInitialize(); // Graphics init

  MemoryCardInitialize(); // Memory card init

  GamepadInitialize(); // Gamepad init
  SpuInitialize();     // Sound init
  CDInitialize();      // CD init
  MusicInitialize();   // Music init

  InitGeom();
  SetGeomOffset(256, 120); // Set the screen center
  SetGeomScreen(341);      // Set the FOV

  // Set the copy buffer to the titlescreen terminator
  g_Buffers.m_CopyBuf = func_titlescreen_8007DDE8;
  // Ditto for the disc
  g_Buffers.m_DiscCopyBuf = func_titlescreen_8007DDE8;

  frameCountStart = VSync(-1); // Get the frame count

  SetDispMask(0); // Disable display

  // Switch the display over to RGB24 mode
  g_DB[0].m_DispEnv.isrgb24 = 1;
  g_DB[1].m_DispEnv.isrgb24 = 1;

  // Clear the copy buffer for the images
  // to be decompressed into
  Memset(g_Buffers.m_CopyBuf, 0, image_size);

  for (i = 0; i < 8; ++i) {
    // Decompress the image
    func_80017F24(&g_SonyImage, g_Buffers.m_CopyBuf,
                  i * blend_step - blend_start);
    setRECT(&frameRect, 0, 0, rgb24_w, rgb24_h);
    LoadImage(&frameRect, g_Buffers.m_CopyBuf);
    DrawSync(0);
    VSync(0);
    PutDispEnv(&g_DB[1].m_DispEnv);

    if (i == 0)
      SetDispMask(1); // Enable display
  }

  WadInitialize(); // Load the WAD header

  CDLoadSync(g_CdState.m_WadSector, g_OverlaySpacePointer, 2048,
             g_WadHeader.m_CutsceneData[Cutscene_Titlescreen].m_Offset,
             600); // Load titlescreen_data.wad's header

  Memcpy(&g_LevelHeader, g_OverlaySpacePointer,
         sizeof(g_LevelHeader)); // Copy it to the header struct

  levelVram = (char *)0x80200000 - _stacksize - 0x40000;

  CDLoadSync(g_CdState.m_WadSector, levelVram, 0x40000,
             g_LevelHeader.m_VramSramOffset +
                 g_WadHeader.m_CutsceneData[Cutscene_Titlescreen].m_Offset,
             600); // Load the titlescreen VRAM

  CDLoadSync(g_CdState.m_WadSector, g_OverlaySpacePointer,
             g_WadHeader.m_TitleScreenOverlay.m_Length,
             g_WadHeader.m_TitleScreenOverlay.m_Offset,
             600); // Load the titlescreen overlay

  universalImage = levelVram - g_WadHeader.m_UniversalLogo.m_Length;

  // Load the Universal Logo below the titlescreen VRAM
  CDLoadSync(g_CdState.m_WadSector, universalImage,
             g_WadHeader.m_UniversalLogo.m_Length,
             g_WadHeader.m_UniversalLogo.m_Offset, 600);

  // Wait for 210 frames, / 60 = 3.5 seconds
  while (VSync(-1) - frameCountStart < 210)
    VSync(0);

  // Clear the copy buffer for the images
  // to be decompressed into again
  Memset(g_Buffers.m_CopyBuf, 0, image_size);

  for (j = 0; j < 8; ++j) {
    // Decompress the image
    func_80017F24(&g_SonyImage, g_Buffers.m_CopyBuf, -(j + 1) * blend_step);
    setRECT(&frameRect, 0, 0, rgb24_w, rgb24_h);
    LoadImage(&frameRect, g_Buffers.m_CopyBuf);
    DrawSync(0);
    VSync(0);
    PutDispEnv(&g_DB[1].m_DispEnv);
  }

  frameCountStart = VSync(-1); // Get the frame count again
  Memset(universalImage - image_size, 0, image_size);

  // Fade in the Universal logo
  for (k = 0; k < 8; ++k) { // blend2 = -blend_start; k < blend_step_count;
                            // blend2 += blend_step
    // Decompress the image
    func_80017F24(universalImage, universalImage - image_size,
                  k * blend_step - blend_start);
    setRECT(&frameRect, 0, 0, rgb24_w, rgb24_h);
    LoadImage(&frameRect, (u_long *)(universalImage - image_size));
    DrawSync(0);
    VSync(0);

    PutDispEnv(&g_DB[1].m_DispEnv);
  }

  // Load in the titlescreen
  g_LoadStage = 3;
  g_CutsceneIdx = 0;

  do {
    LoadCutscene();
  } while (g_LoadStage < 10);

  // Wait for 210 frames, / 60 = 3.5 seconds
  while (VSync(-1) - frameCountStart < 210)
    VSync(0);

  // Fade out the Universal logo
  for (l = 0; l < 8; ++l) {
    // Decompress the image
    func_80017F24(universalImage, universalImage - image_size,
                  -(l + 1) * blend_step);
    setRECT(&frameRect, 0, 0, rgb24_w, rgb24_h);
    LoadImage(&frameRect, (u_long *)(universalImage - image_size));
    DrawSync(0);
    VSync(0);
    PutDispEnv(&g_DB[1].m_DispEnv);
  }

  SetDispMask(0); // Disable display

  // Switch the display back to BGR555 mode
  g_DB[0].m_DispEnv.isrgb24 = 0;
  g_DB[1].m_DispEnv.isrgb24 = 0;

  PutDispEnv(&g_DB[1].m_DispEnv);

  setRECT(&pad, 0, 0, 512, 480); // 480..?
  ClearImage(&pad, 0, 0, 0);
  DrawSync(0);

  // Enable display again
  SetDispMask(1);

  setRECT(&frameRect, 512, 0, 512, 256);
  LoadImage(&frameRect, (u_long *)levelVram);
  DrawSync(0);

  g_Buffers.m_SharedAnimations = (char *)0x80200000 - _stacksize;

  func_8005B7D8();         // Load shared models from WAD.WAD
  StartCutscenePlayback(); // Initialize the gamestate to cutscene

  g_Fade = 15; // Fade

  func_8002D170(); // But then switch it to titlescreen..

  g_DeltaTime = 2;
  g_UnprocessedFrames = 0;
  g_Environment.m_LodDistance = 0x8000;
}
