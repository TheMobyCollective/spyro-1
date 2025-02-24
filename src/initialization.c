#include <sys/types.h>

#include <libcd.h>
#include <libetc.h>
#include <libmcrd.h>
#include <libpad.h>

#include "buffers.h"
#include "camera.h"
#include "cd.h"
#include "checkpoint.h"
#include "common.h"
#include "environment.h"
#include "gamepad.h"
#include "graphics.h"
#include "images.h"
#include "loaders.h"
#include "memory.h"
#include "music.h"
#include "spu.h"
#include "spyro.h"
#include "variables.h"
#include "wad.h"

extern void *D_800113A0;   // Pointer to overlay space
extern char D_8006FCF4[1]; // Sony image
extern int _stacksize;

// Wouldn't know where to put these ones
extern int D_80075838;
extern int D_8007583C;

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
  PadInitDirect((u_char *)&g_PadBuffer, (u_char *)&D_80078E50);
  PadCaliReset(&D_800776D8); // Clears the backup's calibration values
  PadCaliInit(&D_800776D8);  // Initializes it's calibration
                             // deadzone values

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
  CDLoadSync(g_CdState.m_WadSector, D_800113A0, 2048, 0, 600);

  // Copy the WAD header to the global struct
  Memcpy(&g_WadHeader, D_800113A0, sizeof(g_WadHeader));
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

    D_80078E72.m_Levels[i] = 0;
    D_8007A6A8[i] = 0;
  }

  // I had to create the writer variable to get it to match
  for (i = HOMEWORLD_COUNT - 1, writer = &D_800758D0[HOMEWORLD_COUNT - 1];
       i >= 0; i--) {
    *(writer--) = 0;
  }

  D_800758D0[0] = 2; // Set the first homeworld as unlocked

  // Reset course records and flight collected
  for (i = 0; i < HOMEWORLD_COUNT; i++) {
    D_80078618[i] = 0; // Course records to 0
    for (j = 0; j < 5; j++) {
      D_80078680[i][j] = 0; // Flight collected to 0
    }
  }

  g_Spyro.m_health = 3; // Set Spyro's health to 3
  D_8007582C = 4;       // Set Spyro's extra life count to 4

  g_GemTotal = 0;
  g_DragonTotal = 0;
  g_EggTotal = 0;

  // Reset in-level variables
  D_8007587C = 0;  // Gems collected before entering the level
  D_800756C8 = 0;  // Gems collected in this level
  D_80075830 = 0;  // Key flag
  D_800758E8 = 0;  // Life orb count
  D_8007580C = -1; // Health before entering flight level

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

void func_8005B7D8(void); // Load shared models from WAD.WAD (todo)

void func_8002D338(void); // Gamestate init cutscene (why?)
void func_8002D170(void); // Gamestate init titlescreen

// Init function
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/initialization", Initialize);

#if 0 // Almost matches
void Initialize(void) {
  RECT frameRect;
  char *levelVram;
  char *universalImage;
  char *imageTemp;
  int i;
  int imageValueOffset;
  int frameCountStart;

  GraphicsInitialize(); // Graphics init

  // Strange place to do this but okay
  i = 0;

  MemoryCardInitialize(); // Memory card init

  imageValueOffset = -224;

  GamepadInitialize(); // Gamepad init
  SpuInitialize();     // Sound init
  CDInitialize();      // CD init
  MusicInitialize();   // Music init

  InitGeom();
  SetGeomOffset(256, 120); // Set the screen center
  SetGeomScreen(341);      // Set the FOV

  // Set the copy buffer to the titlescreen terminator
  D_800785D8.m_CopyBuf = func_titlescreen_8007DDE8;
  // Ditto for the disc
  D_800785D8.m_DiscCopyBuf = func_titlescreen_8007DDE8;

  frameCountStart = VSync(-1); // Get the frame count

  SetDispMask(0); // Disable display

  // Switch the display over to RGB24 mode
  g_DB[0].m_DispEnv.isrgb24 = 1;
  g_DB[1].m_DispEnv.isrgb24 = 1;

  // Clear the copy buffer for the images
  // to be decompressed into
  Memset(D_800785D8.m_CopyBuf, 0, 0x5a000);

  while (i < 8) {
    // Decompress the image
    func_80017F24(D_8006FCF4, D_800785D8.m_CopyBuf, imageValueOffset);
    setRECT(&frameRect, 0, 0, 768, 240);
    LoadImage(&frameRect, D_800785D8.m_CopyBuf);
    DrawSync(0);
    VSync(0);
    PutDispEnv(&g_DB[1].m_DispEnv);

    if (i == 0)
      SetDispMask(1); // Enable display

    i++;
    imageValueOffset += 32; // 32*7 = 224
  }

  WadInitialize(); // Load the WAD header

  CDLoadSync(g_CdState.m_WadSector, D_800113A0, 2048,
             g_WadHeader.m_TitleScreenData.m_Offset,
             600); // Load titlescreen_data.wad's header

  Memcpy(&g_LevelHeader, D_800113A0,
         sizeof(g_LevelHeader)); // Copy it to the header struct

  levelVram = (char *)0x80200000 - _stacksize - 0x40000;

  CDLoadSync(g_CdState.m_WadSector, levelVram, 0x40000,
             g_WadHeader.m_TitleScreenData.m_Offset +
                 g_LevelHeader.m_VramSramOffset,
             600); // Load the titlescreen VRAM

  CDLoadSync(g_CdState.m_WadSector, D_800113A0,
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
  Memset(D_800785D8.m_CopyBuf, 0, 0x5a000);

  i = 0;

  // Fade out the Sony logo
  do {
    i++;
    // Decompress the image
    func_80017F24(D_8006FCF4, D_800785D8.m_CopyBuf, -i * 32);
    setRECT(&frameRect, 0, 0, (512 * 3) / 2, 240);
    LoadImage(&frameRect, D_800785D8.m_CopyBuf);
    DrawSync(0);
    VSync(0);
    PutDispEnv(&g_DB[1].m_DispEnv);
  } while (i < 8);

  frameCountStart = VSync(-1); // Get the frame count again
  imageTemp = universalImage - 0x16800;
  Memset(imageTemp, 0, 0x5a000);

  // Fade in the Universal logo
  i = 0;
  imageValueOffset = -224;
  do {
    // Decompress the image
    func_80017F24(universalImage, imageTemp, imageValueOffset);
    setRECT(&frameRect, 0, 0, 768, 240);
    LoadImage(&frameRect, (u_long *)imageTemp);
    DrawSync(0);
    VSync(0);

    PutDispEnv(&g_DB[1].m_DispEnv);
    imageValueOffset += 32; // 32*7 = 224
    i++;
  } while (i < 8);

  // Load in the titlescreen
  g_LoadStage = 3;
  D_8007566C = 0;
  do {
    func_80014564();
  } while (g_LoadStage < 10);

  // Wait for 210 frames, / 60 = 3.5 seconds
  while (VSync(-1) - frameCountStart < 210)
    VSync(0);

  i = 0;

  // Fade out the Universal logo
  do {
    i++;
    // Decompress the image
    func_80017F24(levelVram, imageTemp, -i * 32);
    setRECT(&frameRect, 0, 0, (512 * 3) / 2, 240);
    LoadImage(&frameRect, (u_long *)imageTemp);
    DrawSync(0);
    VSync(0);
    PutDispEnv(&g_DB[1].m_DispEnv);
  } while (i < 8);

  SetDispMask(0); // Disable display

  // Switch the display back to BGR555 mode
  g_DB[0].m_DispEnv.isrgb24 = 0;
  g_DB[1].m_DispEnv.isrgb24 = 0;

  PutDispEnv(&g_DB[1].m_DispEnv);

  setRECT(&frameRect, 0, 0, 512, 480); // 480..?
  ClearImage(&frameRect, 0, 0, 0);
  DrawSync(0);

  // Enable display again
  SetDispMask(1);

  setRECT(&frameRect, 0, 0, 512, 256);
  LoadImage(&frameRect, (u_long *)levelVram);
  DrawSync(0);

  D_800785D8.m_SharedAnimations = (char *)0x80200000 - _stacksize;

  func_8005B7D8(); // Load shared models from WAD.WAD
  func_8002D338();

  D_80075918 = 15; // Fade

  func_8002D170();

  g_DeltaTime = 2;
  g_UnprocessedFrames = 0;
  g_Environment.m_LodDistance = 0x8000;
}
#endif