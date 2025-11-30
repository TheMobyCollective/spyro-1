#include "checkpoint.h"
#include "common.h"
#include "memory.h"
#include "moby.h"
#include "variables.h"
#include "vector.h"

void CheckpointSave(Moby *checkpoint, u_int checkpointRotation) {
  int i;

  // Set the starting rotation
  g_Checkpoint.m_StartingRotation = ((int)checkpointRotation << 4) & 0xfff;

  // And copy the position
  VecCopy(&g_Checkpoint.m_StartingPosition, &checkpoint->m_Position);

  // Set the checkpoint flag
  g_Checkpoint.m_StoodOnCheckpoint = 1;

  // Move the starting position up a bit to accommodate for Spyro's hitsphere
  g_Checkpoint.m_StartingPosition.z += 356;

  // These values are written here, but never read
  g_Checkpoint.m_DragonCount =
      g_LevelDragonCount[g_LevelIndex]; // Get the current level's dragon count

  g_Checkpoint.m_GemCount =
      g_LevelGemCount[g_LevelIndex]; // Get the current level's dragon count

  g_Checkpoint.m_unusedCount = 0; // Only written here, never read.

  // Memcpy the killed mobys into the saved ones
  Memcpy(g_Checkpoint.m_KilledMobysSaved, g_Checkpoint.m_KilledMobys,
         sizeof(g_Checkpoint.m_KilledMobys));

  // SKELETON: Because of the memcpy above, this does absolutely nothing
  for (i = 0; i < 8; i++)
    g_Checkpoint.m_KilledMobysSaved[i] |= g_Checkpoint.m_KilledMobys[i];

  // SKELETON: Either value is completely unused aside from here
  g_Checkpoint.m_Unused2 = g_Checkpoint.m_Unused1;
}
