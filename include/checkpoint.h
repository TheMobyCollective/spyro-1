#ifndef __CHECKPOINT_H
#define __CHECKPOINT_H

#include "vector.h"

typedef struct {
  /// @brief Set to 1 if the player has stood on any checkpoint
  int m_StoodOnCheckpoint;

  // SKELETON: Written, but never read
  // That unused count is never used, so it's probably a remnant
  // of something that was removed
  int m_DragonCount;
  int m_GemCount;
  int m_unusedCount;

  // The difference between saved and not saved
  // is that when you die, the unsaved ones still spawn.
  // Saved when you stand on a checkpoint
  int m_KilledMobysSaved[8];
  int m_KilledMobys[8];

  // When you start the level, it's the level's starting position,
  // when you stand on a checkpoint, the checkpoint's position is written here
  Vector3D m_StartingPosition;
  int m_StartingRotation; // Only the Z axis is used, int for some reason

  int m_Unused1; // Never written to, only read to copy into m_Unused2
  int m_Unused2; // Only written to, never read from
} CheckpointData;

extern CheckpointData g_Checkpoint;

#endif