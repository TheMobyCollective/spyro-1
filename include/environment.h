#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

#include <sys/types.h>

typedef struct {
  u_char m_Type;
  int m_Param1, m_Param2;
} SpecialSurface;

typedef struct {
  void *m_sectorPointer; // TODO: Type
  int m_sectorCount;
  void *m_occlusionGroups; // TODO: Type
  int m_occlusionGroupCount;
  SpecialSurface **surfaceData;
  int surfaceCount;
  void *m_LQTexturePointer; // TODO: Type
  void *m_HQTexturePointer; // TODO: Type
  int m_textureCount;
  int m_lodDistance;
  int m_cullingDistance;
} Environment;

extern Environment g_Environment;

extern int D_80075718; // Currently touching surface flag

#endif