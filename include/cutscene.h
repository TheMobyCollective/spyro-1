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

/// @brief Updates the cutscene for the current tick
/// @param pTick The current tick (unused)
void func_8002BFE0(int pTick);

#endif