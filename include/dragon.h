#ifndef __DRAGON_H
#define __DRAGON_H

#include "cutscene.h"
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
  int m_CutsceneTicks; // Cutscene ticks
  int unk_0x40;
  int m_Fade;                   //
  CutsceneCameraData *unk_0x48; // Camera data
  int unk_0x4C;                 // Camera length

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
  Moby *m_CutsceneDragon;    // Cutscene dragon
  Moby *m_CutsceneSpyro;     // Cutscene Spyro
  Moby *m_RescuedDragonMoby; // The dragon Moby being rescued
  int padding;
} g_DragonCutscene; // Dragon cutscene struct

extern struct {
  int unk_0x0;
  Vector3D vec_0x04;
  SHORTMATRIX mat_0x10;
  int unk_0x24;
  Vector3D8 vec_0x28;
  u_char unk_0x2b;
} D_80076248;

extern short D_8006F3C0[24];

extern u_char D_8006F390[4][2];
extern u_char D_8006F398[4][2];
extern Vector3D D_8006F3F0[3];

#endif
