#ifndef __CYCLORAMA_H
#define __CYCLORAMA_H

#include <sys/types.h>
#include <vector.h>

typedef struct {
  int m_SectorCount;
  void *m_Sectors; // TODO: Type
  int m_OcclusionGroupsCount;
  void *m_OcclusionGroups; // TODO: Type
  struct {
    u_char r, g, b, s;
  } m_BackgroundColor;
} Cyclorama;

extern Cyclorama g_Cyclorama;

extern Cyclorama g_NewCyclorama;

typedef struct {
  void *m_Skybox; // TODO: Type
  int m_PointCount;
  Vector3D unk_0x8;
  int m_WorldSector;
  int m_PathMoby;
  int m_LevelId;
  Vector3D m_Center;
  Vector3D m_Points[1]; // To the length m_PointCount
} Portal;

extern Portal *D_80078640[6];

#endif