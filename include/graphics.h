#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#include <sys/types.h>

#include <libgte.h>

#include <libgpu.h>

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

extern DB *D_80075888; // Current DB

extern int D_800758B0; // Only written to, never read

extern void *D_800757B0; // Pointer to poly buffer
extern void *D_800756FC; // End of poly buffer

// static_assert(sizeof(g_DB[0]) == 0x84);

#endif