#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

#include <sys/types.h>

typedef struct {
  u_char m_Type;
  int m_Param1, m_Param2;
} SpecialSurface;

typedef struct {
  void *m_SectorPointer; // TODO: Type
  int m_SectorCount;
  void *m_OcclusionGroups; // TODO: Type
  int m_OcclusionGroupCount;
  SpecialSurface **m_SurfaceData;
  int m_SurfaceCount;
  void *m_LQTexturePointer; // TODO: Type
  void *m_HQTexturePointer; // TODO: Type
  int m_TextureCount;
  int m_LodDistance;
  int m_CullingDistance;
} Environment;

void func_8002B9CC(void);

extern Environment g_Environment;

extern int D_80075718; // Currently touching surface flag

#endif