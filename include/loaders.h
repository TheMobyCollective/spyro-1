#ifndef __LOADERS_H
#define __LOADERS_H

#include <sys/types.h>

#include "vector.h"

extern int D_800758AC;  // Portal level id
extern int g_LoadStage; // Load stage
extern int D_8007566C;  // Cutscene type

extern int D_800756D0; // Has level transition
extern int D_800756B0; // Show transition text
extern int D_800756AC; // Ticks in level transition

void func_80014564(void); // Load titlescreen

void func_80015370(int); // Load level

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
  int m_0x08;
  int m_MobyCount;
  CutsceneCameraData *m_CameraData;
  CutsceneMobyData *m_MobyData[1]; // Variable length array, size m_MobyCount
} CutsceneLayout;

extern CutsceneLayout *D_80075680;

#endif