#ifndef __FAIRY_H
#define __FAIRY_H

#include "moby.h"

extern struct {
  /** @brief State flag (1 = active) */
  int m_State;

  /** @brief Incremented by g_DeltaTime each frame, drives text wave animation
   */
  int m_AnimationTimer;

  /** @brief Selected menu option (0=SAVE/RETRY, 1=REPLAY/ABORT, 2=CONTINUE) */
  int m_MenuSelectedOption;

  /** @brief Current dialogue page index (0-7: HI SPYRO, NO SAVE FILE, SAVING,
   * etc.) */
  int m_MenuDialoguePage;

  /** @brief UI horizontal offset (0xB0 or 0, based on camera angle) */
  int m_MenuOffsetX;

  /** @brief Whether memory card is present (affects available options) */
  int m_HasMemoryCard;

  /** @brief Selected memory card slot (0 = Slot 1, non-zero = Slot 2) */
  int m_MemoryCardSlot;

  /** @brief Unknown - related to memory card / title screen? */
  int unk_0x1c;

  /** @brief Unknown - related to memory card / mobys? */
  int unk_0x20;

  /** @brief Unknown - unused? */
  int unk_0x24;

  /** @brief Unknown - unused? */
  int unk_0x28;

  /** @brief Angle from Spyro to cutscene fairy moby */
  int m_AngleFromSpyro;

  /** @brief Distance from Spyro to fairy moby */
  int m_DistanceFromSpyro;

  /** @brief Camera initial Z height (fairy position) */
  int m_CameraInitZ;

  /** @brief Camera initial horizontal angle */
  int m_CameraInitAngle;

  /** @brief Camera initial distance */
  int m_CameraInitDistance;

  /** @brief Camera target Z height (Spyro's Z + 0x170) */
  int m_CameraTargetZ;

  /** @brief Camera target horizontal angle (angle to g_Sparx) */
  int m_CameraTargetAngle;

  /** @brief Camera target distance (distance to g_Sparx) */
  int m_CameraTargetDistance;

  /** @brief Camera end angle (spawn angle + 180 degrees) */
  int m_CameraEndAngle;

  /** @brief Camera end distance (constant 0x600) */
  int m_CameraEndDistance;

  /** @brief Camera start angle (angle from Spyro to camera at cutscene init) */
  int m_CameraStartAngle;

  /** @brief Camera start distance (distance from Spyro to camera at cutscene
   * init) */
  int m_CameraStartDistance;

  /** @brief Camera start Z height (camera Z at cutscene init) */
  int m_CameraStartZ;

  /** @brief Camera viewing angle (spawn angle +/- 45 degrees, determines UI
   * side) */
  int m_CameraViewAngle;

  /** @brief Camera viewing distance (constant 0x4C9) */
  int m_CameraViewDistance;

  /** @brief Camera viewing Z height (Spyro's Z + 0x56B) */
  int m_CameraViewZ;

  /** @brief Spyro's Z rotation saved on init (unused - never restored) */
  int m_unused_SavedSpyroRotZ;

  /** @brief Angle from Spyro to fairy's level spawn position */
  int m_AngleToSpawn;

  /** @brief Pointer to the fairy moby that triggered the cutscene */
  Moby *m_CutsceneFairy;
} g_FairyCutscene;

/** @brief Temporarily stores fairy kiss timer during cutscene */
extern int g_SavedFairyKissTimer;

#endif
