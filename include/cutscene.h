#ifndef __CUTSCENE_H
#define __CUTSCENE_H

#include <sys/types.h>

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

extern CutsceneLayout *D_80075680;

/// Credits stage/state counter.
/// Starts at -1 when credits begin, increments through stages.
/// - -1: Initial state
/// - 0-98: Active credits display (overlay renders)
/// - 99: Begins loading next level
/// - 100: Loading level in progress
extern int g_CreditsStage;

/// Current credits entry/line index being displayed.
/// Initialized to 0 when credits start, incremented as each entry is shown.
extern int g_CreditsEntryIndex;

/// Number of credits entries that have been displayed/scrolled through.
/// Clamped between current position and total entry count.
extern int g_CreditsDisplayedCount;

/// Total number of entries in the credits sequence.
/// Used as the upper bound for g_CreditsEntryIndex comparisons.
extern int g_CreditsTotalEntries;

/// Pointer to the current credits data structure.
/// Accessed at offsets 0x0 and 0x4 during credits rendering.
extern int g_CreditsDataPtr;

/// Buffer pointer for credits rendering.
/// Set to overlay space + 0x2800 during credits initialization.
/// Used for Memcpy operations and image data during credits display.
extern int g_CreditsBuffer;

/// Timer that accumulates delta time during credits.
/// Used for fade transitions (stored to g_Fade) and HUD moby animation.
/// Reset to 0 when loading begins at stage 99.
extern int g_CreditsTimer;

/// Credits sequence counter/phase indicator.
/// - 0: Credits part 1 (after beating Gnasty Gnorc)
/// - 10: Credits part 2 (after 100% completion)
/// Incremented during credits playback to track progress.
extern int g_CreditsSequence;

/// @brief Updates the cutscene for the current tick
/// @param pTick The current tick (unused)
void func_8002BFE0(int pTick);

#endif