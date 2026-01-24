#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#include <sys/types.h>

#include <libgte.h>

#include <libgpu.h>

#include "vector.h"

typedef struct {
  // The GPU contexts
  DRAWENV m_DrawEnv;
  DISPENV m_DispEnv;

  // Pointer to the
  void *m_PolyBuf;

  void *m_WorldOT;
  void *m_HudOT;

  int m_Unused1; // Might be unused OTs or pointers
  int m_Unused2; // No XREFs
} DB;

extern DB g_DB[2];

extern DB *g_CurDB; // Current DB

extern int D_800758B0; // Only written to, never read

extern void *D_800757B0; // Pointer to poly buffer
extern void *D_800756FC; // End of poly buffer

// ????
extern void *g_HudOT;   // HUD OT
extern void *g_WorldOT; // World OT

/// @brief Builds the final order table
/// @param size The size of the world order table
/// @return A pointer to the final order table's first entry
void *func_80016784(int size);

typedef struct {
  Vector3D WorldPos;
  Vector3D ScreenPos;
  int Age;
} TracerPoint;

extern int g_TracerCount;
extern int g_TracerPointCount[4];
extern TracerPoint* g_TracerLists[4];

// static_assert(sizeof(g_DB[0]) == 0x84);

#endif
