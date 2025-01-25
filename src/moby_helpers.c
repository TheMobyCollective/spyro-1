#include "42CC4.h"
#include "checkpoint.h"
#include "collision.h"
#include "common.h"
#include "math.h"
#include "moby.h"
#include "moby_helpers.h"
#include "spu.h"
#include "spyro.h"
#include <sys/types.h>

/// @brief Function that ticks a timer
/// @param pTimer The timer to update
/// @param pTimerType The type of timer, equal to the size of the type
/// @return non-0 if the timer has elapsed
int func_80037F90(void *pTimer, int pTimerType) {
  if (pTimerType == sizeof(int)) {
    int timer = *(int *)pTimer;

    // D_800756C4 is deltatime inside overlays
    if (D_800756C4 >= timer) { // Less time left than the delta time
      if (timer != 0) {
        *(int *)pTimer = 0;
        return 2; // Timer underflowed
      }

      return 1;
    } else {
      *(int *)pTimer -= D_800756C4;
      return 0;
    }

  } else if (pTimerType == sizeof(short)) {
    short timer = *(short *)pTimer;

    if (D_800756C4 >= timer) { // Less time left than the delta time
      if (timer != 0) {
        *(short *)pTimer = 0;
        return 2; // Timer underflowed
      }

      return 1;
    } else {
      *(short *)pTimer -= D_800756C4;
      return 0;
    }

  } else if (pTimerType == sizeof(char)) {
    u_char timer = *(u_char *)pTimer;

    if (D_800756C4 >= timer) { // Less time left than the delta time
      if (timer != 0) {
        *(char *)pTimer = 0;
        return 2; // Timer underflowed
      }

      return 1;
    } else {
      *(char *)pTimer -= D_800756C4;
      return 0;
    }
  }
}

// Angle functions

/// @brief Adds two angles together
/// @param p1 Angle 1
/// @param p2 Angle 2
/// @return The sum of the two angles
int func_80038074(int p1, int p2) { return ((p1 + p2 + 256) % 256); }

int func_80038098(int p1, int p2, int p3) {
  int diff = func_800381BC(p1, p2);

  if (ABS(diff) > p3) {
    if (diff < 0) {
      return func_80038074(p2, p3);
    } else {
      return func_80038074(p2, -p3);
    }
  }

  return p1;
}

int func_80038120(int p1, int p2, u_char p3) {
  // wtf
  return func_80038074(p2, (func_800381BC(p2, p1) * (p3)) >> 8);
}

int func_80038178(int p1, int p2, int p3, u_char p4) {
  return func_80038120(func_80038098(p1, p2, p3), p2, p4);
}

/// @brief Normalizes the difference between two angles to -128 to 128
/// @param p1 Angle 1
/// @param p2 Angle 2
/// @return The normalized difference
int func_800381BC(int p1, int p2) {
  int diff = p2 - p1;

  // Normalize to -128 to 128
  if (diff > 128) {
    diff -= 256;
  }

  if (diff < -128) {
    diff += 256;
  }

  return diff;
}

// Vision functions

int func_800381E8(Moby *moby, int range) { // Unused
  // Returns true if spyro is in the range of the moby's vision
  return func_80017908(func_80016AB4(g_Spyro.m_Position.x - moby->m_Position.x,
                                     g_Spyro.m_Position.y - moby->m_Position.y,
                                     0),
                       moby->m_Rotation.z) < range;
}

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_80038250);

// Looks for the floor below the Moby
int func_80038340(Moby *pMoby) {
  int position;

  pMoby->m_Position.z += 1500;
  position = func_8004D5EC(&pMoby->m_Position, 4096);
  pMoby->m_Position.z -= 1500;

  return position;
}

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003838C);

int func_80038400(Moby *pMoby, int pDistFromFloor) {
  int position;

  pMoby->m_Position.z += pDistFromFloor;
  position = func_8004D5EC(&pMoby->m_Position, pDistFromFloor + 4096);
  pMoby->m_Position.z -= pDistFromFloor;

  return position;
}

void func_80038458(Moby *pMoby) {
  int floorZ = func_80038340(pMoby);

  pMoby->m_Position.z = floorZ + pMoby->m_FloorDistance;

  func_800533D0(pMoby);
}

/// @brief Returns if a Moby has been killed
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_80038494);
#if 0 // Close to matching, reg diff
int func_80038494(Moby *pMoby) {
  int mobyIdx = (pMoby - D_80075828);
  int killArrayIndex = mobyIdx >> 5;     // / 32
  int bitOffset = 1 << (mobyIdx & 0x1f); // % 32

  // Since load layout sets m_DropMoby to 0xff if the moby is dead
  // the check for it is a bit odd
  return (g_Checkpoint.m_KilledMobysSaved[killArrayIndex] & bitOffset) &&
         pMoby->m_DropMoby == 0xff;
}
#endif

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003851C);

void func_800385BC(Moby *pMoby, int pUnknown) {
  if (pMoby != nullptr) {
    PlaySound(g_Spu.m_SoundTable->mobyPoof, pMoby, 0x08 /* 3D */,
              &pMoby->m_SoundChannel);

  } else {
    PlaySound(g_Spu.m_SoundTable->mobyPoof, nullptr, 0x10 /* 2D */, nullptr);
  }

  func_800530C0(pMoby, pUnknown);
}

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_80038638);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003891C);

/// @brief: Finds the path node closest to the moby
int func_80038A40(Moby *pMoby, PathData *pPathData, int *pNodeIndexOut) {
  int closestNodeDistance = 0xffffff;
  int closestNodeIndex;
  int i;

  for (i = 0; i < pPathData->m_NodeCount; i++) {
    int distance =
        OctDistance(&pMoby->m_Position, &pPathData->m_Nodes[i].m_Position);
    if (distance < closestNodeDistance) {
      closestNodeDistance = distance;
      closestNodeIndex = i;
    }
  }

  if (pNodeIndexOut != nullptr) {
    *pNodeIndexOut = closestNodeIndex;
  }

  return closestNodeDistance;
}

/// @brief: Finds the path node closest to Spyro
int func_80038AFC(PathData *pPathData, int *pNodeIndexOut) {
  int closestNodeDistance = 0xffffff;
  int closestNodeIndex;
  int i;

  for (i = 0; i < pPathData->m_NodeCount; i++) {
    int distance =
        OctDistance(&g_Spyro.m_Position, &pPathData->m_Nodes[i].m_Position);
    if (distance < closestNodeDistance) {
      closestNodeDistance = distance;
      closestNodeIndex = i;
    }
  }

  if (pNodeIndexOut != nullptr) {
    *pNodeIndexOut = closestNodeIndex;
  }

  return closestNodeDistance;
}

/// @brief: Find the path node furthest away from Spyro
int func_80038BB0(PathData *pPathData, int *pNodeIndexOut) {
  int furthestNodeDistance = 0;
  int furthestNodeIndex;
  int i;

  for (i = 0; i < pPathData->m_NodeCount; i++) {
    int distance =
        OctDistance(&g_Spyro.m_Position, &pPathData->m_Nodes[i].m_Position);
    if (distance > furthestNodeDistance) {
      furthestNodeDistance = distance;
      furthestNodeIndex = i;
    }
  }
  return furthestNodeIndex;
}

/// @brief: Checks if a point is within a rectangle
int func_80038C4C(Vector3D *point, Vector3D *rect) {
  // The stack usage here is insane
  Vector3D diff2;
  Vector3D diff;
  int z = rect[1].z;

  VecSub(&diff, point, rect);

  diff2.x = (diff.x * COSINE_8(z) >> 0xc) - (diff.y * SINE_8(z) >> 0xc);
  diff2.y = (diff.x * SINE_8(z) >> 0xc) + (diff.y * COSINE_8(z) >> 0xc);

  diff2.x = ABS(diff2.x);
  diff2.y = ABS(diff2.y);

  if (diff2.x < rect[1].x && diff2.y < rect[1].y)
    return 1;

  return 0;
}

/// @brief: Returns the dot product of two vectors (doesn't use the GTE)
int func_80038D54(Vector3D *param_1, Vector3D *param_2) {
  Vector3D unused; // Needed to match stack usage
  int sum = param_2->x * param_1->x + param_2->y * param_1->y +
            param_2->z * param_1->z;
  return ABS((sum >> 10) + param_2[1].x);
}

/// @brief Rotate moby to face Spyro
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_80038DC0);

/// @brief: Rotate moby to face a point
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_80038EE0);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_80038FC8);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_80039228);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_80039398);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_80039688);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_80039910);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_80039AA8);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_80039E94);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003A16C);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003A420);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003A720);
#if 0 // Close to matching
void func_8003A720(Moby *pMoby) {
  pMoby->m_RenderRadius = 16;
  pMoby->m_UpdateDistance = 0xff;
  pMoby->m_DepthOffset = 4;
  pMoby->m_State = 0;
  pMoby->m_Substate = 0;
  pMoby->m_AnimationState.m_Animation = 0;
  pMoby->m_AnimationState.m_NextAnimation = 0;
  pMoby->m_AnimationState.m_Frame = 0;
  pMoby->m_AnimationState.m_NextFrame = 1;
  pMoby->m_AnimationState.m_PerFrameProgress = 32;
  pMoby->m_AnimationState.m_FrameProgress = 0;
  pMoby->m_Pod = -1;
  pMoby->m_SectorIndex = -1;
  pMoby->m_DropMoby = -1;
  pMoby->m_DamageFlags = 0;
  pMoby->m_Rotation.x = 0;
  pMoby->m_Rotation.y = 0;
  pMoby->m_Rotation.z = 0;
  pMoby->m_ShadowDistance = 0;
  pMoby->m_ScaleOverride = 0;
  pMoby->m_SoundChannel = 0x7f;
  pMoby->m_FloorDistance = 0;
  pMoby->m_Renderer.raw = 32;
  *((int *)pMoby->m_SpecularMetalColor) = 0;
  // pMoby->m_SpecularMetalColor[0] = 0;
  // pMoby->m_SpecularMetalColor[1] = 0;
  // pMoby->m_SpecularMetalColor[2] = 0;
  // pMoby->m_SpecularMetalType = 0;
}
#endif

// Unused
int func_8003A79C(Moby *pMoby, PathData *path, int pDivider) {
  Vector3D dist;

  dist.x =
      path->m_Nodes[path->m_CurrentNode].m_Position.x - pMoby->m_Position.x;
  dist.y =
      path->m_Nodes[path->m_CurrentNode].m_Position.y - pMoby->m_Position.y;
  dist.z =
      path->m_Nodes[path->m_CurrentNode].m_Position.z - pMoby->m_Position.z;

  return VecMagnitude(&dist, 1) / pDivider;
}

// Unused
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003A850);

// Unused (Might be an early version of func_8003BFC0?)
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003A920);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003A9EC);

/// @brief: Apply flame heat
void func_8003AA84(Moby *pMoby) {
  // Are we being flamed?
  if (pMoby->m_DamageFlags & 0x10000) {
    // Being flamed, heat up
    pMoby->m_SpecularMetalColor[2] += 24;
    if (pMoby->m_SpecularMetalColor[2] > 96) {
      pMoby->m_SpecularMetalColor[2] = 96;
    }
  } else {
    // Not being flamed, cool down
    if (pMoby->m_SpecularMetalColor[2] > 32) {
      pMoby->m_SpecularMetalColor[2] -= 2;
    } else if (pMoby->m_SpecularMetalColor[2] > 0) {
      pMoby->m_SpecularMetalColor[2]--;
    }
  }
}

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003AAEC);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003ABC0);

// Moby pods

/// @brief Are any mobys in this pod still alive?
int func_8003B0DC(int pPod) {
  u_short *pod;
  int mobyId;

  if (pPod >= g_MobyPodCount)
    return 0;

  // Can't use an iterator, because func_8003B160 doesn't match that way.
  pod = g_MobyPods[pPod];

  do {

    mobyId = *pod;

    if ((u_char)D_80075828[mobyId & 0x7FFF].m_State <= 127)
      return 1;

    pod++;

    // If the top bit is set, we're done
    // This one (and the one below) are a bit different for some reason
  } while ((mobyId << 16) >= 0);

  return 0;
}

/// @brief Are all mobys in this pod in this state? (Unused)
int func_8003B160(int pPod, u_int pState) {
  u_short *pod;
  int mobyId;

  if (pPod >= g_MobyPodCount)
    return 0;

  pod = g_MobyPods[pPod];

  // Only matched when using a do-while loop and defining pod
  do {

    mobyId = *pod;

    if ((u_char)D_80075828[mobyId & 0x7FFF].m_State != pState)
      return 0;

    pod++;

    // If the top bit is set, we're done
    // This one (and the one above) are a bit different for some reason
  } while ((mobyId << 16) >= 0);

  return 1;
}

/// @brief Set the state of all mobys in the moby's pod
void func_8003B1E8(Moby *pMoby, u_int pState) {
  u_short *pod;

  if (pMoby->m_Pod >= g_MobyPodCount) {
    if ((u_char)pMoby->m_State <= 127)
      pMoby->m_State = pState;
    return;
  }

  pod = g_MobyPods[pMoby->m_Pod];

  do {
    if ((u_char)D_80075828[*pod & 0x7FFF].m_State <= 127)
      D_80075828[*pod & 0x7FFF].m_State = pState;

    // If the top bit is set (so negative), we're done
  } while ((*((short *)pod++)) >= 0);
}

// Something related to damaging other mobys inside a pod (metalhead)
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003B294);

/// @brief Sets the state of all mobys in this pod, if they do not have a
/// certain state
void func_8003B47C(Moby *pMoby, u_int pState, u_int pRequiredNotState) {
  u_short *pod;

  if (pMoby->m_Pod >= g_MobyPodCount) {
    if ((u_char)pMoby->m_State <= 127 &&
        (u_char)pMoby->m_State != pRequiredNotState)
      pMoby->m_State = pState;
    return;
  }

  pod = g_MobyPods[pMoby->m_Pod];

  do {
    if ((u_char)D_80075828[*pod & 0x7FFF].m_State <= 127 &&
        (u_char)D_80075828[*pod & 0x7FFF].m_State != pRequiredNotState)
      D_80075828[*pod & 0x7FFF].m_State = pState;

    // If the top bit is set (so negative), we're done
  } while ((*((short *)pod++)) >= 0);
}

/// @brief Sets the state of all mobys in this pod, if they have a certain state
void func_8003B538(Moby *pMoby, u_int pState, u_int pRequiredState) {
  u_short *pod;

  if (pMoby->m_Pod >= g_MobyPodCount) {
    // SKELETON: Checking if the state is less than 127 is a bit weird
    // probably a copy paste from func_8003B47C
    if ((u_char)pMoby->m_State <= 127 &&
        (u_char)pMoby->m_State == pRequiredState)
      pMoby->m_State = pState;
    return;
  }

  pod = g_MobyPods[pMoby->m_Pod];

  do {
    // SKELETON: Ditto
    if ((u_char)D_80075828[*pod & 0x7FFF].m_State <= 127 &&
        (u_char)D_80075828[*pod & 0x7FFF].m_State == pRequiredState)
      D_80075828[*pod & 0x7FFF].m_State = pState;

    // If the top bit is set (so negative), we're done
  } while ((*((short *)pod++)) >= 0);
}

/// @brief Sets the damage flags of all mobys in this pod (metalhead)
void func_8003B5F4(int pPodId, int pDamageFlags) {
  u_short *pod;

  if (pPodId >= g_MobyPodCount) {
    return;
  }

  pod = g_MobyPods[pPodId];

  do {
    if ((u_char)D_80075828[*pod & 0x7FFF].m_State <= 127)
      D_80075828[*pod & 0x7FFF].m_DamageFlags |= pDamageFlags;

    // If the top bit is set (so negative), we're done
  } while ((*((short *)pod++)) >= 0);
}

/// @brief Deallocates all mobys inside this pod (metalhead)
void func_8003B688(int pPodId) {
  u_short *pod;

  if (pPodId >= g_MobyPodCount) {
    return;
  }

  pod = g_MobyPods[pPodId];

  do {
    if ((u_char)D_80075828[*pod & 0x7FFF].m_State <= 127)
      func_80052568(&D_80075828[*pod & 0x7FFF]);

    // If the top bit is set (so negative), we're done
  } while ((*((short *)pod++)) >= 0);
}

/// @brief Sets the substate of all mobys in this pod
void func_8003B728(Moby *pMoby, u_int pSubstate) {
  u_short *pod;

  if (pMoby->m_Pod >= g_MobyPodCount) {
    // SKELETON: There's no check that checks if the Moby is alive, where there
    // is one in all the other ones, and below :p
    pMoby->m_Substate = pSubstate;
    return;
  }

  pod = g_MobyPods[pMoby->m_Pod];

  do {
    if ((u_char)D_80075828[*pod & 0x7FFF].m_State <= 127)
      D_80075828[*pod & 0x7FFF].m_Substate = pSubstate;

    // If the top bit is set (so negative), we're done
  } while ((*((short *)pod++)) >= 0);
}

// Moby collectables

// Marks a moby as killed
void func_8003B7C0(Moby *pMoby) {
  // Make sure the Moby is a static one
  if (pMoby >= D_80075828 && pMoby < D_80075890) {
    // Get the index by subtracting the base moby pointer
    int mobyIndex = pMoby - D_80075828;

    // Seperate variables, won't match otherwise
    int killArrayIndex = mobyIndex >> 5; // / 32
    int bitOffset = mobyIndex & 0x1f;    // % 32

    g_Checkpoint.m_KilledMobys[killArrayIndex] |= 1 << bitOffset;
  }
}

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003B854);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003B9D4);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003BAD0);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003BCCC);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers",
                         func_8003BED8); // Unused

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003BFC0);

// Create portal text
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003C358);

// Fragment animation
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003C6E4);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003C85C);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003C994);

// Random flight related thingy
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003CAC4);
