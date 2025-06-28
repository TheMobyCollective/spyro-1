#ifndef __HUD_H
#define __HUD_H

// clang-format off
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
// clang-format on

#include "moby.h"

// These are the target positions for the HUD mobys when they are fully
// displayed
extern Vector3D g_HudMobyTargetPos[12];

// Offsets that get added as the HUD is opening/closing
extern short g_HudOpeningOffsets[14]; // 8006E77C
extern short g_HudClosingOffsets[14];

// Target position for the HUD egg sprites
extern RECT g_HudEggTargetRect[12];

extern struct {
  u_char x;
  u_char y;
} g_LifeOrbXYTarget[20];

extern struct {
  u_char m_GemDisplayState;
  u_char m_DragonDisplayState;
  u_char m_LifeDisplayState;
  u_char m_EggDisplayState;
  u_char m_KeyDisplayState;
  u_char m_GemProgress;
  u_char m_DragonProgress;
  u_char m_LifeProgress;
  u_char m_EggProgress;
  u_char m_KeyProgress;
  // 2 bytes padding
  int m_GemSteadyTicks;
  int m_DragonSteadyTicks;
  int m_LifeSteadyTicks;
  int m_EggSteadyTicks;
  int m_KeySteadyTicks;
  int m_GemCount;
  int m_DragonCount;
  int m_LifeCount;
  int m_EggCount;
  int m_KeyFlag;
  int D_80077FDC;
  int m_LifeOrbCount;
  int unk_0x3c; // 80077FE4
  int unk_0x40; // 80077FE8

  // The HUD has 12 moby slots for the gem/dragon/life counts (and icons)
  Moby m_Mobys[12];

  // 12 slots for eggs, 20 slots for the life orb things
  RECT m_SpriteRect[32];
} g_Hud;

typedef enum {
  HDS_Hidden = 0,
  HDS_Opening = 1,
  HDS_Open = 2,
  HDS_Closing = 3,
  HDS_Completed = 4
} HudDisplayState;

/// @brief Converts the gem/dragon/life counts into mobys to display on the HUD
void HudPrint(int pIdx, int pLen, int pValue, int pArg4);

/// @brief Moves gem/dragon/life count mobys up and down
void HudMoveMoby(int pIdx, int pLen, int pYOffset);

/// @brief Moves egg sprites up and down
void HudMoveEgg(int pIdx, int pLen, int pYOffset);

/// @brief Rotates count/icon mobys
void HudMobyRotate(int pIdx, int pLen, int pZRot);

/// @brief Update the HUD gems + display
void HudGemUpdate(void);

/// @brief Initialize/reset the HUD data
void HudReset(int pArg);

/// @brief Tick all the HUD states
void HudTick();

/// @brief Generate the mobys displayed when you collect a gem
void GenerateGemCollectMobys(int pGemValue, Moby *pGemPos);

#endif