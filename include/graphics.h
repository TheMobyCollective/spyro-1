#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#include "common.h"

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

/// @brief Adds a polygon to the world order table
/// @param pPoly The polygon to add
/// @param pOTIndex The OT index to add the polygon to
void func_800168A0(void *pPoly, int pOTIndex);

/// @brief Adds a polygon to the HUD order table
/// @param pPoly The polygon to add
void func_800168DC(void *pPoly);

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
extern TracerPoint *g_TracerLists[4];

typedef struct {
  int unk_0x00;
  int* unk_0x04;
  Vector3D* MobyPos;
  Color GlowColor;
  int unk_0x010;
  Vector3D PosOffset;
  int unk_0x20;
} Glow;

extern Glow D_80078800[16];

// Primitive codes
#define PRIM_LINE_F2 (0x40)
#define PRIM_LINE_G2 (0x50)

#define PRIM_POLY_F3 (0x20)
#define PRIM_POLY_F4 (0x28)
#define PRIM_POLY_G3 (0x30)
#define PRIM_POLY_G4 (0x38)

#define PRIM_POLY_FT3 (0x24)
#define PRIM_POLY_GT3 (0x34)
#define PRIM_POLY_FT4 (0x2C)
#define PRIM_POLY_GT4 (0x3C)
// Set semi-transparency bit in primitive code
#define PRIM_STP(primCode) (primCode | 0x2)
// Calculate 'len' of P_TAG with 'addr' null, as one int
#define PRIM_TAG(primType) ((sizeof(primType) / 4 - 1) << 24);

// static_assert(sizeof(g_DB[0]) == 0x84);

#endif
