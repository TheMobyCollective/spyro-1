#ifndef __TITLESCREEN_H
#define __TITLESCREEN_H

#include <sys/types.h>

typedef enum {
  TSM_Init = 0,    // Default/uninitialized
  TSM_Menu = 1,    // Interactive menu
  TSM_Loading = 2, // Demo loading transition
  TSM_Demo = 3     // Active demo playback
} TitlescreenMode;

typedef enum {
  TSS_Setup = 0,   // Initial setup phase
  TSS_Loading = 1, // Loading assets
  TSS_Active = 2   // Active/running
} TitlescreenState;

typedef enum {
  TSD_Cutscene = 0, // Play cutscene
  TSD_Level = 1,    // Reuse current level
  TSD_DemoLevel = 2 // Load demo level from table
} TitlescreenDemoType;

extern struct {
  int m_Mode;
  int m_State;
  int m_Tick;
  int m_0x0C;
  int m_0x10; // State 2?
  int m_0x14;
  int m_0x18;
  int m_DemoType;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_CardIdxChecking; // 0 or 1

  // McErrNone (Connected), McErrCardNotExist (Not connected)
  int m_CardStates[4];
  int m_CardCompletedFunc;
  int m_CardResultData;
  int m_0x48;
  void *m_0x4C;
  int m_0x50;
  int m_0x54;
  int m_0x58;
} g_TitlescreenState; // 0x5C in size

void func_titlescreen_8007ABAC(void);

/// @brief Array of level IDs used for titlescreen demo playback
extern int g_DemoLevelIds[];

/// @brief Current demo index (0-3, cycles through available demos)
extern int g_DemoIndex;

/// @brief Demo fade-out timer (0-16, triggers transition at 16)
extern int g_DemoFadeTimer;

#endif
