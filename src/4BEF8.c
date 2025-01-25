#include "buffers.h"
#include "common.h"
#include "graphics.h"
#include "memory.h"

/// @brief: Set up the polygon buffers
void AllocateBuffers(int pReducedSpace) {
  // Tried being smart with this, doesn't natch
  D_800785D8.m_ParticleSpaceStart =
      (char *)D_800785D8.m_SharedAnimations - 0x2000;
  D_800785D8.m_WorldOTStart = (char *)D_800785D8.m_SharedAnimations - 0x6000;
  D_800785D8.m_HudOTStart = (char *)D_800785D8.m_SharedAnimations - 0x6008;

  if (pReducedSpace) {
    D_800785D8.m_HigherPolyBuffer = (char *)D_800785D8.m_HudOTStart - 0x13000;
    D_800785D8.m_LowerPolyBuffer =
        (char *)D_800785D8.m_HigherPolyBuffer - 0x13000;
  } else {
    D_800785D8.m_HigherPolyBuffer = (char *)D_800785D8.m_HudOTStart - 0x1c000;
    D_800785D8.m_LowerPolyBuffer =
        (char *)D_800785D8.m_HigherPolyBuffer - 0x1c000;
  }

  g_DB[0].m_PolyBuf = D_800785D8.m_LowerPolyBuffer;
  g_DB[1].m_PolyBuf = D_800785D8.m_HigherPolyBuffer;

  // It's odd that they even have the OTs in the struct, they're always the same
  g_DB[0].m_HudOT = D_800785D8.m_HudOTStart;
  g_DB[1].m_HudOT = D_800785D8.m_HudOTStart;
  g_DB[0].m_WorldOT = D_800785D8.m_WorldOTStart;
  g_DB[1].m_WorldOT = D_800785D8.m_WorldOTStart;

  Memset(D_800785D8.m_HudOTStart, 0, 8);
  Memset(D_800785D8.m_WorldOTStart, 0, 0x4000);
}

// Load shared models from WAD.WAD
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/4BEF8", func_8005B7D8);
