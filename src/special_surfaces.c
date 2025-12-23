#include "common.h"

#include "cyclorama.h"
#include "environment.h"
#include "loaders.h"
#include "moby.h"
#include "overlay_pointers.h"
#include "spyro.h"

extern int D_80075728;    // TODO: spyro.h? not sure
extern int D_800777C0[8]; // Zapped floors

// TODO: m_DamageFlags enum / definitions

/// @brief Handles the effects of the special surfaces
void ApplySpecialSurfaceEffects(int surfaceIdx, u_int arg1) {
  Vector3D spyroPortalDist;
  PortalPathMobyData *pathData;
  int *surfaceFlags;
  int pathMoby;
  Portal **pportal2;
  Portal **pportal;
  int sidedness;

  surfaceFlags = &g_Environment.m_SurfaceData[surfaceIdx]->m_Param1;

  switch (g_Environment.m_SurfaceData[surfaceIdx]->m_Type) {
  case 0:
    if (arg1 == 1) {
      if ((g_Spyro.m_Position.z - g_Spyro.m_surfaceBelowSpyro) > 512) {
        g_Spyro.m_SurfaceProximityState = arg1;
        return;
      }
    }

    if (arg1 == 2) {
      g_Spyro.m_DamageFlags = (g_Spyro.m_DamageFlags & 0x3FF) | 0x400;
      g_Spyro.m_floorFlagsPointer = surfaceFlags;
      D_80075728 = surfaceFlags[1];
      g_Spyro.m_damagingFloorIndex = g_Spyro.m_surfaceBelowSpyro;
      return;
    }

    break;

  case 1:
    g_Spyro.m_DamageFlags = (g_Spyro.m_DamageFlags & 0x3FF) | 0x800;
    g_Spyro.m_damagingFloorFlags = surfaceFlags;
    break;

  case 2: // Used by the High Caves Spiders
    if (arg1 < 2 && g_Spyro.m_Position.z - g_Spyro.m_surfaceBelowSpyro <= 400) {
      surfaceFlags[0] = 1;
    }
    break;

  case 4: // Super charge

    g_Spyro.m_DamageFlags = (g_Spyro.m_DamageFlags & 0x3FF) | 0x2000;
    break;

  case 5: // Invisible wall

    g_Spyro.m_DamageFlags = (g_Spyro.m_DamageFlags & 0x3FF) | 0x8000;
    g_SpawnMoby(234, nullptr);
    break;

  case 6: // Portals

    if (g_Spyro.m_health >= 0) { // Make sure we're not dead

      g_NextLevelId = surfaceFlags[0]; // Level traveling to

      // If the level ID is over 64, we set
      // traveling back to the current level and return
      // This used to be how the 'THE END' portal in June was disabled
      if (g_NextLevelId > 64) {
        g_NextLevelId = g_LevelId;
        return;
      }

      D_800756D0 = 1;               // Has level transition I believe?
      D_8007576C = surfaceFlags[1]; // Portal

      if (g_LevelId != ((g_LevelId / 10) * 10)) {
        g_PortalLevelId = g_LevelId;
      }

      // This is a bit fucky wucky ??
      pportal2 = g_Portals;
      pportal = pportal2 + D_8007576C;

      VecSub(&spyroPortalDist, &g_Spyro.m_Position, (*pportal)->m_Points);

      // Bit weird to do it here but yeah
      sidedness = (-spyroPortalDist.x * (*pportal)->unk_0x8.x -
                   spyroPortalDist.y * (*pportal)->unk_0x8.y) -
                  spyroPortalDist.z * (*pportal)->unk_0x8.z;
      pathMoby = (*pportal)->m_PathMoby;

      // Fallback when there's no path moby set
      // Links are set to -1 when they're not filled
      if (pathMoby < 0) {
        g_LoadStage = 0;
        g_Gamestate = GS_LevelTransition;
        D_800756B0 = 1;
        D_800756AC = 0;
        return;
      }

      D_80075828[pathMoby].m_State = 1;
      D_80075828[pathMoby].m_UpdateDistance = 0xFF;

      pathData = D_80075828[pathMoby].m_Props;

      if (sidedness < 0) {
        D_80075828[pathMoby].m_Substate = 1;
        pathData->unk_0x4.x = -(*pportal)->unk_0x8.x >> 1;
        pathData->unk_0x4.y = -(*pportal)->unk_0x8.y >> 1;
        pathData->unk_0x4.z = -(*pportal)->unk_0x8.z >> 1;
      } else {
        D_80075828[pathMoby].m_Substate = 0;
        pathData->unk_0x4.x = (*pportal)->unk_0x8.x >> 1;
        pathData->unk_0x4.y = (*pportal)->unk_0x8.y >> 1;
        pathData->unk_0x4.z = (*pportal)->unk_0x8.z >> 1;
      }
    }
    break;
  case 7: // Electric floor
    if (arg1 == 2 && D_800777C0[surfaceFlags[0]] != 0) {
      g_Spyro.m_DamageFlags = (g_Spyro.m_DamageFlags & 0x3FF) | 0x26;
    }
    break;
  }
}

/// @brief Checks if the surface is a special surface, and returns it's type.
int func_80057380(void) {
  int idx = g_SurfaceBelowFlags & 63;

  if (idx != 63) // If the flag is 63, it means we're not touching a surface
    return g_Environment.m_SurfaceData[idx]->m_Type;

  return -1;
}