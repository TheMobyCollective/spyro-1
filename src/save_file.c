#include "common.h"
#include <sys/types.h>

#include "camera.h"
#include "gamepad.h"
#include "memory.h"
#include "save_file.h"
#include "spu.h"
#include "variables.h"

// Wouldn't know where to put these ones
extern int D_80075838;
extern int D_8007583C;

/// @brief Generate checksum for save file
int SaveChecksum(u_char *saveFile) {
  int checksum = 0;
  int i;

  for (i = 0; i < sizeof(SaveFile) - 4; i++) {
    checksum += saveFile[i];
  }

  return checksum;
}

/// @brief Load from save file
int SaveLoad(SaveFile *pSaveFile) {
  char *saveFilePtr;
  int i, j;
  g_LevelId = pSaveFile->m_LevelId;

  D_80075754 = pSaveFile->m_SoundVolume;
  g_Spu.unk_0x320 = (D_80075754 * 0x3fff) / 10;
  g_Spu.m_SoundVolume = (g_Spu.unk_0x320 * 0x1000) / 0x3fff;

  D_80075748 = pSaveFile->m_MusicVolume;
  g_Spu.m_CommonAttr.mask = SPU_COMMON_CDVOLL | SPU_COMMON_CDVOLR;
  g_Spu.m_MusicVolume = D_80075748 << 11; // * 2048
  g_Spu.m_CommonAttr.cd.volume.right = g_Spu.m_CommonAttr.cd.volume.left =
      g_Spu.m_MusicVolume;

  SpuSetCommonAttr(&g_Spu.m_CommonAttr);

  g_ActEnabled = pSaveFile->m_ControllerVibrationEnabled;
  D_80075914 = pSaveFile->m_CameraSpeed;
  g_Spu.m_AudioMono = pSaveFile->m_AudioMono;

  saveFilePtr = (char *)pSaveFile;

  D_80075838 = pSaveFile->m_UnusedByte1;
  D_8007583C = pSaveFile->m_UnusedByte2;

  D_8007582C = pSaveFile->m_ExtraLifeCount;

  if (D_8007582C < 4) { // If we have less than 4 lives, set it to 4
    D_8007582C = 4;
  }

  Memcpy(D_80078618, pSaveFile->m_Flight.m_CourseRecords,
         sizeof(pSaveFile->m_Flight.m_CourseRecords));

  for (j = 0; j < 5; j++) {
    for (i = 0; i < 5; i++) {
      D_80078680[j][i] = pSaveFile->m_Flight.m_FlightCollected[j][i];
    }
  }

  Memcpy(D_80078E72.m_Levels, pSaveFile->m_LevelsVisited,
         sizeof(pSaveFile->m_LevelsVisited));

  Memcpy(D_8007A6A8, pSaveFile->m_LevelsCompleted,
         sizeof(pSaveFile->m_LevelsCompleted));

  g_DragonTotal = 0;
  g_GemTotal = 0;
  g_EggTotal = 0;

  for (i = 0; i < TOTAL_LEVEL_COUNT; i++) {
    g_LevelDragonCount[i] = pSaveFile->m_CollectedDragons[i];
    g_DragonTotal = g_DragonTotal + g_LevelDragonCount[i];

    g_LevelGemCount[i] = pSaveFile->m_CollectedGems[i];
    g_GemTotal = g_GemTotal + g_LevelGemCount[i];

    if (i < LEVEL_PER_HOMEWORLD * 3) { // Thank fucking god
      g_LevelEggCount[i] = pSaveFile->m_CollectedEggs[i];
      g_EggTotal = g_EggTotal + g_LevelEggCount[i];
    }
  }

  for (i = 0; i < HOMEWORLD_COUNT; i++) {
    D_800758D0[i] = pSaveFile->m_UnlockedHomeworlds[i];
  }

  Memcpy(D_80077908, pSaveFile->m_GemCollectionMask,
         sizeof(pSaveFile->m_GemCollectionMask));

  return pSaveFile->m_Checksum == SaveChecksum(saveFilePtr);
}

/// @brief Create save file
void SaveCreate(SaveFile *pSaveFile) {
  int i, j;
  u_char *saveFilePtr;

  // SKELETON: Larger than the size of the struct, oh well
  Memset(pSaveFile, 0, 0x600);

  pSaveFile->m_LevelId = g_LevelId;
  pSaveFile->m_SoundVolume = D_80075754;
  pSaveFile->m_MusicVolume = D_80075748;
  pSaveFile->m_ControllerVibrationEnabled = g_ActEnabled;
  pSaveFile->m_CameraSpeed = D_80075914;
  pSaveFile->m_AudioMono = g_Spu.m_AudioMono;

  saveFilePtr = (u_char *)pSaveFile; // ????? Why here???

  pSaveFile->m_UnusedByte1 = D_80075838;
  pSaveFile->m_UnusedByte2 = D_8007583C;
  pSaveFile->m_ExtraLifeCount = D_8007582C;

  Memcpy(pSaveFile->m_Flight.m_CourseRecords, D_80078618,
         sizeof(pSaveFile->m_Flight.m_CourseRecords));

  for (j = 0; j < 5; j++) {
    for (i = 0; i < 5; i++) {
      pSaveFile->m_Flight.m_FlightCollected[j][i] = D_80078680[j][i];
    }
  }

  Memcpy(pSaveFile->m_LevelsVisited, D_80078E72.m_Levels,
         sizeof(pSaveFile->m_LevelsVisited));

  Memcpy(pSaveFile->m_LevelsCompleted, D_8007A6A8,
         sizeof(pSaveFile->m_LevelsCompleted));

  for (i = 0; i < TOTAL_LEVEL_COUNT; i++) {
    pSaveFile->m_CollectedDragons[i] = g_LevelDragonCount[i];
    pSaveFile->m_CollectedGems[i] = g_LevelGemCount[i];

    // SKELETON: Yeah...... this reads and writes out of bounds....
    pSaveFile->m_CollectedEggs[i] = g_LevelEggCount[i];
  }

  for (i = 0; i < HOMEWORLD_COUNT; i++) {
    pSaveFile->m_UnlockedHomeworlds[i] = D_800758D0[i];
  }

  Memcpy(pSaveFile->m_GemCollectionMask, D_80077908,
         sizeof(pSaveFile->m_GemCollectionMask));

  pSaveFile->m_Checksum = SaveChecksum(saveFilePtr);
}