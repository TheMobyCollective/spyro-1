#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

#include <sys/types.h>

typedef struct {
  u_char m_Type;
  int m_Param1, m_Param2;
} SpecialSurface;

typedef struct {
  int m_TriangleCount;
  int m_FlagCount;
  u_short *m_BlockTree;
  u_short *m_Blocks;
  void *m_Triangles;
  u_char *m_TriangleOcclusionAssignment;
  u_char *m_Flags;
} TerrainCollision;

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
  TerrainCollision *m_TerrainCollision;
} Environment;

void func_8002A6FC(int pDeltaTime);
void func_8002B9CC(void);

extern Environment g_Environment;

extern int g_SurfaceBelowFlags; // Surface type flags from last height query

#endif
