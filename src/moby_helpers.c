#include "moby_helpers.h"
#include "42CC4.h"
#include "checkpoint.h"
#include "collision.h"
#include "common.h"
#include "math.h"
#include "spu.h"
#include "spyro.h"
#include "variables.h"
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

int func_80038250(Vector3D *pPoint) {
  Vector3D distance;
  Vector3D rayStart;
  Vector3D rayEnd;
  int raySegments;
  int magnitude;
  int i;

  VecSub(&distance, &g_Spyro.m_Position, pPoint);
  magnitude = VecMagnitude(&distance, 1);
  // SKELETON: Newton's method, which isn't used
  func_8001729C(&distance, magnitude, 1);
  func_800175B8(&distance, magnitude, 0x400);
  VecCopy(&rayStart, pPoint);

  raySegments = magnitude >> 0xA; // div by 1024

  for (i = 0; i < raySegments; i++) {
    VecAdd(&rayEnd, &rayStart, &distance);

    // Look if we've got a collision
    if (func_8004AE38(&rayStart, &rayEnd))
      return 0; // If we did, return it

    VecCopy(&rayStart, &rayEnd); // Advance the ray
  }

  return 1;
}

// Looks for the floor below the Moby
int func_80038340(Moby *pMoby) {
  int position;

  pMoby->m_Position.z += 1500;
  position = func_8004D5EC(&pMoby->m_Position, 4096);
  pMoby->m_Position.z -= 1500;

  return position;
}

int func_8003838C(Moby *pMoby) {
  pMoby->m_Position.z += 1500;
  func_8004D5EC(&pMoby->m_Position, 4096);
  pMoby->m_Position.z -= 1500;
  return (char)func_800169AC(D_80077368.z, VecMagnitude(&D_80077368, 0)) < 24;
}

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

inline static int SavedMobyIsDead(int mobyIndex) {
  int index = mobyIndex >> 5;
  int bit = mobyIndex & 0x1F;
  return g_Checkpoint.m_KilledMobysSaved[index] & (1 << bit);
}

/// @brief Returns if a Moby has been killed
int func_80038494(Moby *pMoby) {
  // Since load layout sets m_DropMoby to 0xff if the moby is dead
  // the check for it is a bit odd
  return SavedMobyIsDead(pMoby - D_80075828) && pMoby->m_DropMoby == 0xff;
}

void func_8003851C(Moby *pMoby, int pSoundIndex, u_char *pChannel) {
  if (pChannel != nullptr) {
    PlaySound(D_80076378[pMoby->m_Class]->m_Sounds[pSoundIndex], pMoby,
              0x08 /* 3D */, pChannel);
  } else {
    // stop sounds from this moby
    func_800562A4(pMoby, 1);
    PlaySound(D_80076378[pMoby->m_Class]->m_Sounds[pSoundIndex], pMoby,
              0x08 /* 3D */, &pMoby->m_SoundChannel);
  }
}

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

int func_8003891C(Vector3D *pVec1, Vector3D *pVec2, int p3, int p4, int *pOut) {
  struct {
    int x;
    int y;
  } vec;
  int t;

  vec.x = pVec1->x - pVec2->x;
  vec.y = pVec1->y - pVec2->y;
  t = VecMagnitude((Vector3D *)&vec, 0) / p3;
  if (pOut != nullptr) {
    *pOut = t;
  }
  if (t != 0) {
    return -(pVec1->z - pVec2->z + (p4 * (t * t) >> 1)) / t;
  }
  return 0;
}

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

int func_80039228(Moby *pMoby, Vector3D vec1, int arg4, int arg5, int arg6) {
  Vector3D vec2;
  Vector3D vec3;

  if (D_800756C4 == 3) {
    // vec1 *= 1.5
    VecCopy(&vec3, &vec1);
    VecShiftRight(&vec3, 1);
    VecAdd(&vec1, &vec1, &vec3);
  } else if (D_800756C4 == 4) {
    // vec1 *= 2
    VecShiftLeft(&vec1, 1);
  }
  VecAdd(&vec2, &pMoby->m_Position, &vec1);
  if (arg6 & 1) {
    vec2.z += 300 + arg5;
  }
  if (arg4 && func_8004E3C8(&vec2, arg4, 0, nullptr, pMoby, nullptr)) {
    return 1;
  }
  if (arg5 && func_8004BE4C(&vec2, arg5, arg5)) {
    return 2;
  }
  if (arg6 & 1) {
    vec2.z -= 300 + arg5;
  }
  VecCopy(&pMoby->m_Position, &vec2);
  func_800529E4(pMoby, UPDATE_PROP_CHAIN);
  return 0;
}

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_80039398);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_80039688);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_80039910);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_80039AA8);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_80039E94);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003A16C);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003A420);

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
  pMoby->m_AnimationState.m_FrameProgress = 0;
  pMoby->m_AnimationState.m_PerFrameProgress = 32;
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
}

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
void func_8003B294(Moby *pMoby, int pPodIdx, uint pFlag, int pWithinOctDist,
                   int pWithinZDist, int pWithinXYDist, int pWithinAngle) {
  int angle2;
  Moby *check_moby;
  ushort *pod_list;

  if (pPodIdx >= g_MobyPodCount)
    return;

  pod_list = g_MobyPods[pPodIdx];
  while (1) {
    check_moby = &D_80075828[*pod_list & 0x7FFF];
    if (check_moby->m_State < 0x80 &&
        ABS2(pMoby->m_Position.x - check_moby->m_Position.x) < pWithinXYDist &&
        ABS2(pMoby->m_Position.y - check_moby->m_Position.y) < pWithinXYDist &&
        OctDistance(&pMoby->m_Position, &check_moby->m_Position) <
            pWithinOctDist &&
        ABS2(check_moby->m_Position.z - pMoby->m_Position.z) < pWithinZDist) {
      angle2 =
          func_80016AB4(check_moby->m_Position.x - (pMoby->m_Position).x,
                        check_moby->m_Position.y - (pMoby->m_Position).y, 0);
      if (func_80017908((pMoby->m_Rotation).z, angle2) < pWithinAngle) {
        check_moby->m_DamageFlags |= pFlag;
      }
    }
    if ((short)*pod_list < 0) {
      break;
    }
    ++pod_list;
  }
}

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

/// @brief Collects a collectable moby
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003B854);

/// @brief Collect a gem moby, adds it to the collected gem array
void CollectItem(Moby *pMoby) {
  char x[16];
  int gem_value;

  // Update recently collected items, presumably for the little animation when
  // you leave a level
  g_RecentGemsCollected[D_800756C8 & 0x1F] = pMoby->m_Class;
  D_800756C8 += 1;

  // If this was a key, mark it as collected
  if (pMoby == D_80075758) {
    D_80075830 = 3;
  }

  // Updates the moby's rotation matrix
  // I'm not entirely sure why
  func_800529E4(pMoby, UPDATE_PROP_ROTMATRIX);

  // particle spawn
  (*D_800758E4)(6, 0xC, pMoby, (void *)D_8006E330[pMoby->m_Class]);

  if (pMoby->m_Class == MOBYCLASS_GEM_1)
    gem_value = 1;
  else if (pMoby->m_Class == MOBYCLASS_GEM_2)
    gem_value = 2;
  else if (pMoby->m_Class == MOBYCLASS_GEM_5)
    gem_value = 5;
  else if (pMoby->m_Class == MOBYCLASS_GEM_10)
    gem_value = 10;
  else if (pMoby->m_Class == MOBYCLASS_GEM_25)
    gem_value = 25;
  else
    return;

  // persist gem collection
  func_8003B854(gem_value, pMoby);
}

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003BAD0);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003BCCC);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers",
                         func_8003BED8); // Unused

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003BFC0);

#define setMobyLetterProps(props, parent, index, len)                          \
  (props)->m_Parent = parent;                                                  \
  (props)->m_Len = len;                                                        \
  (props)->m_Index = index

// Create portal text
void func_8003C358(Moby *pMoby, int pIsLevelName) {
  char const *level_name;
  u_char z_rot;
  Vector3D vec1;
  Vector3D vec2;
  Vector3D vec3;
  Vector3D vec4;
  int tmp4;
  int i;
  int char_moby_class;
  int string_len;
  u_char character;
  Moby *char_moby;
  Vector3D *pos;

  if (pIsLevelName) {
    level_name = D_8006F7F0[*(int *)(pMoby->m_Props)];
    z_rot = pMoby->m_Rotation.z;
  } else {
    level_name = D_8006F7F0[36]; //"RETURN HOME"
    z_rot = func_80016AB4(g_Spyro.m_Position.x - pMoby->m_Position.x,
                          g_Spyro.m_Position.y - pMoby->m_Position.y, 0);
  }

  setXYZ(&vec1, Cos(z_rot << 4) * 3 >> 4, Sin(z_rot << 4) * 3 >> 4, 0);

  setXYZ(&vec2, Cos((z_rot + 64) << 4) >> 5, Sin((z_rot + 64) << 4) >> 5, 0);

  if (pIsLevelName != 0) {
    if (pMoby->m_Substate == 0) {
      z_rot = pMoby->m_Rotation.z + 128;
    } else {
      z_rot = pMoby->m_Rotation.z;
      VecNull(&vec3);
      VecSub(&vec1, &vec3, &vec1);
      VecSub(&vec2, &vec3, &vec2);
    }
  }

  string_len = strlen(level_name);

  VecMult(&vec3, &vec2, string_len - 1);

  VecShiftLeft(&vec2, 1);

  tmp4 = (string_len - 1) * 2;

  vec3.z += Cos((tmp4 & 0xff) << 4) * 3 >> 3;

  setXYZ(&vec4, vec1.x * Cos((tmp4 & 0xff) << 4),
         vec1.y * Cos((tmp4 & 0xff) << 4), 0);

  for (i = 0; i < string_len; tmp4 -= 4, ++i) {
    character = level_name[i];
    if (character != ' ') {
      char_moby_class = character;
      if (character >= 'A' && character <= 'Z') {
        char_moby_class = char_moby_class - 'A' + MOBYCLASS_LETTER_A;
      } else {
        char_moby_class = MOBYCLASS_LETTER_BLANK;
      }
      char_moby = (*D_800758CC)(char_moby_class, pMoby);
      setMobyLetterProps((MobyLetterProps *)char_moby->m_Props, pMoby, i,
                         string_len);
      pos = &char_moby->m_Position;
      setXYZ(pos, vec1.x * Cos((tmp4 & 0xff) << 4),
             vec1.y * Cos((tmp4 & 0xff) << 4), 0);
      VecSub(pos, pos, &vec4);
      VecShiftRight(pos, 10);
      VecAdd(pos, pos, &vec1);
      VecAdd(pos, pos, &pMoby->m_Position);
      VecSub(pos, pos, &vec3);
      char_moby->m_Position.z += Cos((tmp4 & 0xff) << 4) * 3 >> 3;
      if (char_moby->m_Class == 76)
        char_moby->m_Position.z += 256;
      char_moby->m_Rotation.z = z_rot;
      char_moby->m_FloorDistance = z_rot;
      char_moby->m_State = pMoby->m_Substate;
      char_moby->m_Substate = i * 8;
      char_moby->m_SpecularMetalType = 2;
    }
    VecSub(&vec3, &vec3, &vec2);
  }
}

// Fragment animation
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003C6E4);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003C85C);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003C994);

// Random flight related thingy
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/moby_helpers", func_8003CAC4);
