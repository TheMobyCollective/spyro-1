#ifndef __SAVE_FILE_H
#define __SAVE_FILE_H

#include "common.h"
#include <sys/types.h>

typedef struct {
  int m_CourseRecords[5];
  u_char m_FlightCollected[5][5];
} SaveFlight;

typedef struct {
  u_char m_LevelId;
  u_char m_SoundVolume;
  u_char m_MusicVolume;
  u_char m_ControllerVibrationEnabled;
  int m_CameraSpeed;
  u_char m_AudioMono;
  u_char m_UnusedByte1;
  u_char m_UnusedByte2;
  u_char m_ExtraLifeCount;
  int unk_0x0C;

  SaveFlight m_Flight;

  u_char m_LevelsVisited[TOTAL_LEVEL_COUNT];
  u_char m_LevelsCompleted[TOTAL_LEVEL_COUNT];
  u_char m_CollectedDragons[TOTAL_LEVEL_COUNT];
  short m_CollectedGems[TOTAL_LEVEL_COUNT];
  // Only the first three homeworlds have eggs
  u_char m_CollectedEggs[LEVEL_PER_HOMEWORLD * 3];
  u_char m_UnlockedHomeworlds[HOMEWORLD_COUNT];
  // In memory, this is padded to 1200, but in the save file it's 1152
  u_char m_GemCollectionMask[TOTAL_LEVEL_COUNT * 32];
  int m_Checksum;
} SaveFile;

// Wouldn't know where else to put these ones
// They're unused, only initialized to 0
// and saved to the save file
extern int D_80075838;
extern int D_8007583C;

#endif // __SAVE_FILE_H
