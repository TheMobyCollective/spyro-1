#ifndef __CUTSCENE_H
#define __CUTSCENE_H

#include <sys/types.h>

#include "spu.h"
#include "vector.h"

typedef struct {
  Vector3D m_Position;
  Vector3D m_Rotation; // Yeah, Vector3D..
} CutsceneCameraData;

typedef struct {
  u_char m_0x00;
  u_char m_0x01;
  u_char m_0x02;
  u_char m_0x03;
} CutsceneMobyData;

typedef struct {
  int m_CurrentTick;
  int m_0x04;
  int m_Duration;
  int m_MobyCount;
  CutsceneCameraData *m_CameraData;
  CutsceneMobyData *m_MobyData[1]; // Variable length array, size m_MobyCount
} CutsceneLayout;

/// Pointer to the current cutscene layout data.
/// Contains playback state (m_CurrentTick), duration, and animation data
/// for camera and mobys. Loaded from level data in LoadCutscene().
extern CutsceneLayout *g_CutsceneLayout;

/// Temporary sound definition buffer used for cutscene audio.
/// Assigned to g_Spu.m_SoundDefinitions during cutscene playback.
extern SoundDefinition g_CutsceneSoundDef;

/// Array of cutscene-specific pitch values, indexed by g_CutsceneIdx.
/// Values: [0]=0x800, [1]=0x659, [2]=0x800, [3]=0x800
extern int g_CutscenePitchTable[];

/// Credits sequence counter/phase indicator.
/// - 0: Credits part 1 (after beating Gnasty Gnorc)
/// - 10: Credits part 2 (after 100% completion)
/// Incremented during credits playback to track progress.
extern int g_CreditsSequence;

/// @brief Updates the cutscene for the current tick
/// @param pTick The current tick (unused)
void func_8002BFE0(int pTick);

/// @brief Initializes and starts cutscene playback
void StartCutscenePlayback(void);

/// @brief Ends cutscene playback and transitions to the next gamestate
void EndCutscenePlayback(void);

#endif