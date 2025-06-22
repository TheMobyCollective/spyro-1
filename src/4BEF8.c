#include "buffers.h"
#include "cd.h"
#include "common.h"
#include "graphics.h"
#include "loaders.h"
#include "memory.h"
#include "moby.h"
#include "wad.h"

extern int _stacksize;

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

// Load shared models from PETE.WAD inside WAD.WAD
void func_8005B7D8(void) {
  int i;

  struct {
    int m_DataSize;
    struct {
      int m_Offset;
      int m_Class;
    } models[64];
  } *peteData = (void *)(0x80200000 - g_WadHeader.m_PETE.m_Length -
                         g_WadHeader.m_PETE.m_Length - _stacksize);

  // PETE.WAD is loaded below the bottom of the stack,
  // but lower than where the shared animations will end up
  CDLoadSync(g_CdState.m_WadSector, peteData, g_WadHeader.m_PETE.m_Length,
             g_WadHeader.m_PETE.m_Offset, 600);

  // The shared animations are loaded below the bottom of the stack
  D_800785D8.m_SharedAnimations =
      (void *)(0x80200000 - peteData->m_DataSize - _stacksize);

  Memcpy(D_800785D8.m_SharedAnimations, (void *)((int)peteData + 0x800),
         peteData->m_DataSize);

  for (i = 0; i < 64; i++) {
    if (!peteData->models[i].m_Offset)
      break;

    D_80076378[peteData->models[i].m_Class] =
        PatchMobyModelPointers((void *)((char *)D_800785D8.m_SharedAnimations +
                                        peteData->models[i].m_Offset - 0x800));
  }

  AllocateBuffers(0);
}
