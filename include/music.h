#ifndef __MUSIC_H
#define __MUSIC_H

#include <libcd.h>

#define PETE_XA_COUNT 6
#define PETE_XA_TRACKS 8

typedef struct {
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

extern CdMusic g_CdMusic;

extern int D_800774B0; // Currently playing track

void func_8002BBE0(void); // Music update

#endif