#ifndef __CYCLORAMA_H
#define __CYCLORAMA_H

#include <sys/types.h>

#include <camera.h>
#include <common.h>
#include <vector.h>

#include <libgte.h>

typedef struct {
  int m_SectorCount;
  void *m_Sectors; // TODO: Type
  int m_OcclusionGroupsCount;
  void *m_OcclusionGroups; // TODO: Type
  Color m_BackgroundColor;
} Cyclorama;

extern Cyclorama g_Cyclorama;

extern Cyclorama g_NewCyclorama;

// Portal depth and used as an accumulator
extern int D_80075934;

// Lerp color target
extern int D_800757D4;

typedef struct {
  int copySectorCount;
  void *copySectors;
  int zero;
  int zero2;
  int copyBgColor;
  int componentSize;
  Color m_BackgroundColor;
  uint m_SectorCount;
  void *m_Sectors[1];
} PortalDataSky;

typedef struct {
  PortalDataSky *m_Skybox; // This one is difficult to type,
                           // because it refers to the last (missing) point
                           // in the cyclorama points array, which is being used
                           // as strange storage

  int m_PointCount;
  Vector3D unk_0x8;
  int m_WorldSector;
  int m_PathMoby;
  int m_LevelId;
  Vector3D m_Center;
  Vector3D m_Points[1]; // To the length (m_PointCount - 1)
} Portal;

typedef struct {
  int m_Active; // 0 terminates the list
  int m_Start;
  int m_End;
  int m_A;
  int m_B;
  int m_C;
} PortalEdge;

extern Portal *g_Portals[6]; // Pointers for each possible portal
extern int g_PortalCount;    // Portal count

extern u_char *D_80075798;
extern PortalEdge D_80077EA0[11]; // Outline edges of the portal being drawn
extern Vector3D D_80078DD8[10];   // Portal points projected to the screen

// Screen rectangle of the portal being drawn (min y, max y, max x, min x)
extern int D_8007AA00[4];

extern int D_80075910; // Transition skybox yaw

extern int D_800758FC; // Portal rotation pitch
extern int D_80075858; // Portal rotation yaw

/// @brief Renders main Cyclorama and Portals
void func_80050BD0(void);

/// @brief Renders a portal's backdrop color
void func_8004FEA0(int *pColor);

/// @brief Renders a portal's skybox
void func_8004F4BC(PortalDataSky *pSky, MATRIX *pView, MATRIX *pProj);

/// @brief Renders a portal's skybox (With interpolation)
void func_80050240(PortalDataSky *pSky, MATRIX *pView, MATRIX *pProj);

/// @brief Renders the cyclorama / sky
void func_8004EBA8(int pOcclusionGroup, SHORTMATRIX *pViewMatrix,
                   SHORTMATRIX *pProjectionMatrix);

/// @brief Renders the cyclorama, no parameters
void func_8004F000(void);

#endif
