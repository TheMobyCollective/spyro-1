#ifndef __DRAGON_H
#define __DRAGON_H

#include "moby.h"
#include "wad.h"

typedef struct {
  int unk_0x0; // Unknown, always 0
  OffsetLength m_SpuData;
  OffsetLength m_DragonModel;
  OffsetLength m_SpyroModel;
  OffsetLength m_CameraData;
} WadDragonHeader;

extern struct {
  WadDragonHeader m_Header;

  int m_CutsceneIdx; // Dragon index for the cutscene
  int m_State;       // Cutscene state
  int m_Stage;       // Load stage
  int m_BlocksRead;  // Spu transfer stage
  int m_HasOverflow;
  int m_LoadLength;
  int unk_0x3C; // Cutscene ticks
  int unk_0x40;
  int unk_0x44;   //
  void *unk_0x48; // Camera data
  int unk_0x4C;   // Camera length

  // These are all used by the gamestate
  int unk_0x50;
  int m_SoundVoice; // SPU voice channel for cutscene audio (0-23, or 0x7F if
                    // none)
  int unk_0x58;
  int unk_0x5C;
  int unk_0x60;
  int unk_0x64;
  int unk_0x68;
  int unk_0x6C;
  int unk_0x70;
  int unk_0x74;
  int unk_0x78;
  int unk_0x7C;
  int unk_0x80;
  int unk_0x84;

  // The Moby pointers
  Moby *m_CutsceneSpyro;     // Cutscene dragon
  Moby *m_CutsceneDragon;    // Cutscene Spyro
  Moby *m_RescuedDragonMoby; // The dragon Moby being rescued
  int padding;
} g_DragonCutscene; // Dragon cutscene struct

#endif
