#ifndef __CYCLORAMA_H
#define __CYCLORAMA_H

#include <sys/types.h>

#include <common.h>
#include <vector.h>

typedef struct {
  int m_SectorCount;
  void *m_Sectors; // TODO: Type
  int m_OcclusionGroupsCount;
  void *m_OcclusionGroups; // TODO: Type
  Color m_BackgroundColor;
} Cyclorama;

extern Cyclorama g_Cyclorama;

extern Cyclorama g_NewCyclorama;

// Lerp color target
extern int D_800757D4;

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

void func_80050BD0(void);

#endif