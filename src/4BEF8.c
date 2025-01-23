#include "buffers.h"
#include "common.h"
#include "graphics.h"
#include "memory.h"

// Set up the polygon buffers
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/4BEF8", func_8005B6F8);

#if 0 // Almost matches
void func_8005B6F8(int pReducedSpace) {
  int polyBufSize;

  D_800785D8.m_ParticleSpaceStart =
      (char *)D_800785D8.m_SharedAnimations - 0x2000;

  g_DB[0].m_WorldOT = (char *)D_800785D8.m_ParticleSpaceStart - 0x4000;
  g_DB[0].m_HudOT = (char *)g_DB[0].m_WorldOT - 8;

  // polyBufSize = !pReducedSpace ? 0xd000 : 0x4000;

  // if (!pReducedSpace) {
  //   polyBufSize = 0xd000;
  // } else {
  //   polyBufSize = 0x4000;
  // }

  g_DB[1].m_PolyBuf = (char *)g_DB[0].m_HudOT - polyBufSize;
  g_DB[0].m_PolyBuf = (char *)g_DB[1].m_PolyBuf - polyBufSize;

  // It's odd that they even have the OTs in the struct, they're always the same
  g_DB[1].m_WorldOT = g_DB[0].m_WorldOT;
  g_DB[1].m_HudOT = g_DB[0].m_HudOT;

  D_800785D8.m_LowerPolyBuffer = g_DB[0].m_PolyBuf;
  D_800785D8.m_HigherPolyBuffer = g_DB[1].m_PolyBuf;
  D_800785D8.m_HudOTStart = g_DB[0].m_HudOT;
  D_800785D8.m_WorldOTStart = g_DB[0].m_WorldOT;

  Memset(g_DB[0].m_HudOT, 0, 8);
  Memset(g_DB[0].m_WorldOT, 0, 0x4000);
}
#endif

// Load shared models from WAD.WAD
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/4BEF8", func_8005B7D8);
