#ifndef __MUSIC_H
#define __MUSIC_H

#include "common.h"

#include <libcd.h>

#define PETE_XA_COUNT 6
#define PETE_XA_TRACKS 8

typedef struct {
  int m_CurrentTrack;
  int m_Flags;
  struct {
    int start, end;
  } m_MusicTable[64]; // 64 entries, but only 48 are used
  int m_TrackPosition;
  char m_SyncData[8];
  int m_PostCDCommand;
  int m_Flags2;
  int m_EasterEggTicks;
  CdlATV m_Aud; // Stereo mixing
} CdMusic;

extern int D_8006EEDC[PETE_XA_COUNT][PETE_XA_TRACKS]; // Track lengths
extern int D_8006F200[PETE_XA_COUNT];                 // Pete XA offsets

// Level to track mapping (12 extra for easter eggs)
extern int D_8006EF9C[TOTAL_LEVEL_COUNT + 12];

// Egg to track mapping
extern int D_8006F05C[(TOTAL_LEVEL_COUNT - 1)][3];

extern CdMusic g_CdMusic;

/// @brief Updates the CD music system
void CDMusicUpdate(void);

#endif
