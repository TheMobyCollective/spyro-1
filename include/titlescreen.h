#ifndef __TITLESCREEN_H
#define __TITLESCREEN_H

#include "save_file.h"
#include <sys/types.h>

// defining these like libmcrd.h since, arguably, they should have done them
#define McSyncMode_Sync (0)
#define McSyncMode_Async (1)

#define McSyncRet_Active (0)
#define McSyncRet_Finished (1)
#define McSyncRet_NothingRegistered (-1)

typedef enum {
  TSM_Init = 0,    // Default/uninitializeds
  TSM_Menu = 1,    // Interactive menu
  TSM_Loading = 2, // Demo loading transition
  TSM_Demo = 3     // Active demo playback
} TitlescreenMode;

// TSM_Init -> This is the mode coming out of the sony / universal screens when
// Spyro flies in and lands on the platform
// - SubState 0 -> Initialization, kick off load titlescreen data from CD
// - SubState 1 -> Loaded titlescreen data from CD, begin titlescreen sequence
// - SubState 2 -> Front half of titlescreen sequence before buttons are active
// - SubState 3 -> Spyro is flying in and then standing on the platform
// - SubState 4 -> Start/X pushed, moving to mem card screen
// - SubState 5 -> Titlescreen timed out, fading to demo

// TSM_Menu -> Mem card menus
// Most of these don't have "stages" to them - simply displaying information
// or asking for one of two inputs
// The ones with stages are listed below
// - SubState 0 - Initial state, begin mem card load sequence
//   - Stage (State) 0 - Interrogate port A
//   - Stage (State) 1 - Interrogate port B
//   - Stage (State) 2 - Figure out which memcard to use based on memcards
//   present
// - SubState 1 - Card has been selected, read it from memory
//   - Stage (State) 0 - Read save file from selected card
//   - Stage (State) 1 - Verify save file / recreate bad save blocks if needed
// - Substate 11 - Create new save file logic
//   - Stage (State) 0 - Nothing...
//   - Stage (State) 1 - Create initial mem card file
//   - Stage (State) 2 - Verify write to mem card can be re-read
//   - Stage (State) 3 - Verify write to mem card can be re-read

// TSM_Loading -> Save file picker
// - State 0 - Initial loading state
// - State 1 - Selecting slot for new game
// - State 2 - Confirm overwrite this save slot
// - State 3 - Selecting slot to load
// - State 4 - Save file display, pick new vs load
// - State 5 - Fade out towards demo/play

typedef enum {
  TSS_Setup = 0,   // Initial setup phase
  TSS_Loading = 1, // Loading assets
  TSS_Active = 2   // Active/running
} TitlescreenState;

typedef enum {
  TS_SubState_LoadMemCards = 0,
  TS_SubState_ReadSelectedCard = 1,
  TS_SubState_NoMemoryCard = 2,
  TS_SubState_MemCardUnavailable = 3,
  TS_SubState_WarningNoSave = 4,
  TS_SubState_MemCardFormat1 = 5,
  TS_SubState_MemCardFormat2 = 6,
  TS_SubState_MemCardFormatting = 7,
  TS_SubState_FormatComplete = 8,
  TS_SubState_FormatFailed = 9,
  TS_SubState_CreateSaveConfirm = 10,
  TS_SubState_CreatingSaveFile = 11,
  TS_SubState_MemCardFull = 12,
  TS_SubState_CantCreateSave = 13,
  TS_SubState_SelectMemCard = 15,
} TitlescreenMenuSubstate;

typedef enum {
  TSD_Cutscene = 0, // Play cutscene
  TSD_Level = 1,    // Reuse current level
  TSD_DemoLevel = 2 // Load demo level from table
} TitlescreenDemoType;

typedef enum {
  TS_Sprite_SpyroLogo = 0,  // Big old spyro logo on the "Press Start" screen
  TS_Sprite_MainBorder = 1, // Main left/right decorative border

  // Save file select homeworld logos
  TS_Sprite_Homeworld_Artisans = 2,
  TS_Sprite_Homeworld_PeaceKeepers = 3,
  TS_Sprite_Homeworld_MagicCrafters = 4,
  TS_Sprite_Homeworld_BeastMakers = 5,
  TS_Sprite_Homeworld_DreamWeavers = 6,
  TS_Sprite_Homeworld_GnastysWorld = 7,

  TS_Sprite_EmptySave = 8,
  TS_Sprite_BlankSaveBox = 9,
  TS_Sprite_OverwriteGame = 10,
  TS_Sprite_PressStart = 11,
  TS_Sprite_LoadGame = 12, // Unused

  // Dragon count numbers
  TS_Sprite_DragonCt_Num0 = 13,
  TS_Sprite_DragonCt_Num1 = 14,
  TS_Sprite_DragonCt_Num2 = 15,
  TS_Sprite_DragonCt_Num3 = 16,
  TS_Sprite_DragonCt_Num4 = 17,
  TS_Sprite_DragonCt_Num5 = 18,
  TS_Sprite_DragonCt_Num6 = 19,
  TS_Sprite_DragonCt_Num7 = 20,
  TS_Sprite_DragonCt_Num8 = 21,
  TS_Sprite_DragonCt_Num9 = 22,

  TS_Sprite_DragonCt_Logo = 23,

  TS_Sprite_AccessingMemCard = 24,
  TS_Sprite_NoMemCard = 25,
  TS_Sprite_MemCardUnavailable = 26,

  TS_Sprite_Warning = 27,
  TS_Sprite_YouWillNotBeAbleTo = 28,
  TS_Sprite_SaveYourProgressUnless = 29,
  TS_Sprite_YouCreateASaveFileNow = 30,

  TS_Sprite_TheMemoryCardInSlot1 = 31,
  TS_Sprite_TheMemoryCardInSlot2 = 32,

  TS_Sprite_IsNotFormatted = 33,
  TS_Sprite_FormatItNow = 34,
  TS_Sprite_AnySaveDataOnThis = 35,
  TS_Sprite_MemoryCardWillBeLost = 36,

  TS_Sprite_Formatting = 37,
  TS_Sprite_FormatComplete = 38,
  TS_Sprite_FormatFailed = 39,

  TS_Sprite_DoesNotHaveASaveFile = 40,
  TS_Sprite_CreateSaveFileNow = 41,
  TS_Sprite_CreatingSaveFile = 42,

  TS_Sprite_IsFullThisGame = 43,
  TS_Sprite_RequiresOneFreeBlock = 44,
  TS_Sprite_UnableToCreateSaveFile = 45,

  TS_Sprite_SelectSlotForNewGame = 46,
  TS_Sprite_SelectSlotToLoadGame = 47,
  TS_Sprite_NoActiveCard_PressTriToGoBack = 48,
  TS_Sprite_UsingCardInSlot1_PressTriToGoBack = 49,
  TS_Sprite_UsingCardInSlot2_PressTriToGoBack = 50,

  TS_Sprite_SelectMemoryCard = 51,
  TS_Sprite_StartNewGameOpt = 52,
  TS_Sprite_RetryOpt = 53,
  TS_Sprite_CancelOpt = 54,
  TS_Sprite_FormatCardOpt = 55,
  TS_Sprite_CreateFileOpt = 56,
  TS_Sprite_ContinueOpt = 57,
  TS_Sprite_LoadGameOpt = 58,
  TS_Sprite_NewGameOpt = 59,
  TS_Sprite_Slot1Opt = 60,
  TS_Sprite_Slot2Opt = 61,
  TS_Sprite_Overwrite = 62,
  TS_Sprite_ToCreateASaveFile = 63,

} TitlescreenSprite;

typedef enum {
  TS_Color_Gray = 0,
  TS_Color_Yellow = 1,
  TS_Color_LightGray = 2,
  TS_Color_DarkGray = 3,
} TitlescreenColor;

extern struct {
  int m_Mode;
  int m_State;
  int m_Tick;
  int m_SubTick;
  int m_SubState;
  int m_OptionSelected;
  int m_0x18;
  int m_DemoType;
  int m_NewGameOptionSelected;
  int m_MemCardTries;
  int m_CardSelected;
  int m_CardIdxChecking; // 0 or 1

  // McErrNone (Connected), McErrCardNotExist (Not connected)
  int m_CardStates[2];
  int m_CardNeedsFormat[2];
  int m_CardCompletedFunc;
  int m_CardResultData;
  int m_HasAnySave;

  MemCardSaveFile *m_MemCardSave;
  SaveFile *m_SaveFiles[3];
} g_TitlescreenState; // 0x5C in size

void TitlescreenPlaySound(int pSoundId);
void TitlescreenUpdate(void);
void TitlescreenDrawSprite(int pX, int pY, int pSprite, int pColorId);
void TitlescreenDraw(void);

/// @brief Array of level IDs used for titlescreen demo playback
extern int g_DemoLevelIds[];

/// @brief Current demo index (0-3, cycles through available demos)
extern int g_DemoIndex;

/// @brief Demo fade-out timer (0-16, triggers transition at 16)
extern int g_DemoFadeTimer;

extern u_char g_MemCardSaveHeader[512];

extern u_char g_TitlescreenAnimIn[16];
extern u_char g_TitlescreenAnimOut[16];
extern int g_TitlescreenSPUOffsets[10 /*?*/];

extern u_long g_TitlescreenSelColors[4]; // P_CODEs;
extern struct {
  ushort m_tpage;
  ushort m_clut;
  u_char m_w;
  u_char m_h;
  u_char m_u;
  u_char m_v;
} g_TitlescreenSprites[64];

#endif
