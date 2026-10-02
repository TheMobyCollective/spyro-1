#include "common.h"

#include "camera.h"
#include "collision.h"
#include "environment.h"
#include "gamepad.h"
#include "loaders.h"
#include "math.h"
#include "memory.h"
#include "rand.h"
#include "spyro.h"

#include <libgte.h>

// FYI, these are inside of this file rather than just extern,
// because otherwise the compiler didn't make use of gp_rel!
// This means that these variables were orignally inside of
// this file as well.

// Fuck knows
int D_80075894;
int D_80075924; // L2 and R2 rotation speed

// Flag: set to 1 when camera forced to destination, 0 in collision func
int D_800756B8;

/// @brief Creates the Camera's view and projection matrices
void CameraUpdateMatrices(void) {
  // If it wasn't for the projection part, this function could've
  // been used for creating a matrix from any rotation vector..
  // But they decided to hardcode stuff instead

  MATRIX mtx;
  MATRIX tMtx;

  Memset(&mtx, 0, sizeof(MATRIX));
  SetTransMatrix(&mtx); // Clear the translation

  // X matrix
  // 4096    0       0
  // 0       cos(y)  -sin(y)
  // 0       sin(y)  cos(y)
  mtx.m[0][0] = 4096;
  mtx.m[1][1] = Cos(g_Camera.m_Rotation.y); // Y goes into the X matrix..
  mtx.m[2][1] = Sin(g_Camera.m_Rotation.y);
  mtx.m[1][2] = -Sin(g_Camera.m_Rotation.y);
  mtx.m[2][2] = Cos(g_Camera.m_Rotation.y);

  Memset(&tMtx, 0, sizeof(MATRIX)); // Clear the temporary matrix

  // Y matrix
  // cos(x)  0   sin(x)
  // 0       4096    0
  // -sin(x) 0   cos(x)
  tMtx.m[0][0] = Cos(g_Camera.m_Rotation.z); // Z goes into the Y matrix..
  tMtx.m[2][0] = -Sin(g_Camera.m_Rotation.z);
  tMtx.m[1][1] = 4096;
  tMtx.m[0][2] = Sin(g_Camera.m_Rotation.z);
  tMtx.m[2][2] = Cos(g_Camera.m_Rotation.z);

  MulMatrix(&mtx, &tMtx);

  Memset(&tMtx, 0, sizeof(MATRIX)); // Clear the temporary matrix

  // Z matrix
  // The [1][0] and [0][1] are swapped for some reason
  // cos(z)  sin(z) 0
  // -sin(z)  cos(z)  0
  // 0       0       4096
  tMtx.m[0][0] = Cos(g_Camera.m_Rotation.x); // X goes into the Z matrix..
  tMtx.m[1][0] = -Sin(g_Camera.m_Rotation.x);
  tMtx.m[0][1] = Sin(g_Camera.m_Rotation.x);
  tMtx.m[1][1] = Cos(g_Camera.m_Rotation.x);
  tMtx.m[2][2] = 4096;

  MulMatrix(&mtx, &tMtx);

  Memcpy(&g_Camera.m_ViewMatrix, &mtx, sizeof(SHORTMATRIX));

  // Create the projection matrix by scaling the view matrix
  // The framebuffer is 512x240, but the display is 4:3, so 320x240
  mtx.m[1][0] = mtx.m[1][0] * 320 / 512;
  mtx.m[1][1] = mtx.m[1][1] * 320 / 512;
  mtx.m[1][2] = mtx.m[1][2] * 320 / 512;

  Memcpy(&g_Camera.m_ProjectionMatrix, &mtx, sizeof(SHORTMATRIX));
}

// Casts a ray between two points, returns false if it hits something
int func_80033E40(Vector3D *pPoint1, Vector3D *pPoint2) {
  Vector3D distance;
  Vector3D rayStart, rayEnd;
  int magnitude, raySegments, i;

  VecSub(&distance, pPoint2, pPoint1);

  // TODO: This distance calculation causes Baruti crash, should create a
  // FIX_BUGS directive to fix it. We could fix it here, or inside of
  // VecMagnitude by changing add to addu, but I think here is preferable

  magnitude = VecMagnitude(&distance, 1);
  raySegments = magnitude >> 10; // Divide by 1024
  VecScaleToLength(&distance, magnitude, 1024);

  // Copy point 1 into the source
  VecCopy(&rayStart, pPoint1);

  for (i = 0; i < raySegments; i++) {
    VecAdd(&rayEnd, &rayStart, &distance);

    // Look if we've got a collision
    if (func_8004AE38(&rayStart, &rayEnd))
      return 0; // If we did, return it

    VecCopy(&rayStart, &rayEnd); // Advance the ray
  }

  return 1;
}

// Return is something happened to the azimuth
int func_80033F08(Vector3D *pVec) {
  Vector3D diff;
  int magnitude;
  int newAzimuth;
  int azimuthDiff;
  int shiftedAzimuth;
  int flippedDiff;
  int elevationDiff;
  int azimuthOffset;
  int result;

  VecSub(&diff, pVec, g_Camera.m_Focus);

  magnitude = VecMagnitude(&diff, 1);
  g_Camera.m_Simulation.m_Coords.radius = magnitude;
  magnitude = VecRefineMagnitude(&diff, magnitude, 1);
  g_Camera.m_Simulation.m_Coords.radius = magnitude;

  magnitude = VecMagnitude(&diff, 0);
  magnitude = VecRefineMagnitude(&diff, magnitude, 0);

  g_Camera.m_Simulation.m_Coords.elevation = Atan2(magnitude, diff.z, 1);
  newAzimuth = Atan2(diff.x, -diff.y, 1);

  azimuthDiff = (newAzimuth - g_Camera.m_Simulation.m_Coords.azimuth) & 0xFFF;
  if (azimuthDiff >= 0x801) {
    azimuthDiff -= 0x1000;
  }

  shiftedAzimuth = g_Camera.m_Simulation.m_Coords.azimuth - 0x800;
  flippedDiff = (newAzimuth - shiftedAzimuth) & 0xFFF;
  if (flippedDiff >= 0x801) {
    flippedDiff -= 0x1000;
  }

  if ((ABS(flippedDiff) < ABS(azimuthDiff)) &&
      (g_Camera.m_State == 0x80000009 || g_Camera.unk_0xE8 != 0)) {
    if (ABS(diff.x) >= 0x81 || ABS(diff.y) >= 0x81) {
      g_Camera.m_Simulation.m_Coords.azimuth = (newAzimuth + 0x800) & 0xFFF;
    } else {
      g_Camera.m_Simulation.m_Coords.azimuth =
          g_Camera.m_Sphere.m_Coords.azimuth;
    }
    g_Camera.m_Simulation.m_Coords.elevation =
        (0x800 - g_Camera.m_Simulation.m_Coords.elevation) & 0xFFF;
    result = 1;
  } else {
    if (ABS(diff.x) >= 0x81 || ABS(diff.y) >= 0x81) {
      g_Camera.m_Simulation.m_Coords.azimuth = newAzimuth;
    } else {
      g_Camera.m_Simulation.m_Coords.azimuth =
          g_Camera.m_Sphere.m_Coords.azimuth;
    }
    result = 0;
  }

  g_Camera.m_Simulation.m_Offset.azimuth = g_Camera.m_Rotation.x;
  elevationDiff =
      (g_Camera.m_Rotation.y - g_Camera.m_Simulation.m_Coords.elevation) &
      0xFFF;
  g_Camera.m_Simulation.m_Offset.elevation = elevationDiff;
  if (elevationDiff >= 0x801) {
    g_Camera.m_Simulation.m_Offset.elevation = elevationDiff - 0x1000;
  }

  azimuthOffset =
      (0x800 - g_Camera.m_Rotation.z - g_Camera.m_Simulation.m_Coords.azimuth) &
      0xFFF;
  g_Camera.m_Simulation.m_Offset.radius = azimuthOffset;
  if (azimuthOffset >= 0x801) {
    g_Camera.m_Simulation.m_Offset.radius = azimuthOffset - 0x1000;
  }

  return result;
}

/// @brief Updates the spherical coordinates
void ApplySphericalPreset(void) {
  SphericalCoordsOffset *src = g_Camera.m_SphericalPreset;

  g_Camera.m_LastSimulation.m_Coords.azimuth =
      (src->m_Coords.azimuth - g_Camera.m_FocusRotation) & 0xFFF;
  g_Camera.m_LastSimulation.m_Coords.elevation = src->m_Coords.elevation;
  g_Camera.m_LastSimulation.m_Coords.radius = src->m_Coords.radius;
  g_Camera.m_LastSimulation.m_Offset.azimuth = src->m_Offset.azimuth;
  g_Camera.m_LastSimulation.m_Offset.elevation = src->m_Offset.elevation;
  g_Camera.m_LastSimulation.m_Offset.radius = src->m_Offset.radius;
}

/// @brief Converts the camera's spherical coordinates to cartesian coordinates
void func_80034204(Vector3D *pOut) {
  // I curse whoever didn't want to add an input parameter to this function

  /* clang-format off */ 

  // x = r * cos(e) * cos(a)
  pOut->x =
      FIXED_MUL(
          FIXED_MUL(g_Camera.m_Sphere.m_Coords.radius, Cos(g_Camera.m_Sphere.m_Coords.elevation)),
          Cos(g_Camera.m_Sphere.m_Coords.azimuth)
        );

  // y = (-r * cos(e)) * sin(a)
  pOut->y =
      FIXED_MUL(
          -FIXED_MUL(g_Camera.m_Sphere.m_Coords.radius, Cos(g_Camera.m_Sphere.m_Coords.elevation)),
          Sin(g_Camera.m_Sphere.m_Coords.azimuth)
        );

  // z = r * sin(e)
  pOut->z = FIXED_MUL(g_Camera.m_Sphere.m_Coords.radius, Sin(g_Camera.m_Sphere.m_Coords.elevation));

  /* clang-format on */
}

/// @brief Updates the camera's rotation based on it's spherical coordinates
void func_800342F8(void) {
  g_Camera.m_Rotation.x = g_Camera.m_Sphere.m_Offset.azimuth;
  g_Camera.m_Rotation.y = g_Camera.m_Simulation.m_Coords.elevation +
                              g_Camera.m_Sphere.m_Offset.elevation &
                          0xfff;
  g_Camera.m_Rotation.z = 0x800 - g_Camera.m_Simulation.m_Coords.azimuth -
                              g_Camera.m_Sphere.m_Offset.radius &
                          0xfff;
}

// Some camera reset stuff
void func_80034358(void) {
  ApplySphericalPreset();

  g_Camera.m_Sphere.m_Coords.azimuth =
      g_Camera.m_LastSimulation.m_Coords.azimuth;
  g_Camera.m_Sphere.m_Coords.elevation =
      g_Camera.m_LastSimulation.m_Coords.elevation;
  g_Camera.m_Sphere.m_Coords.radius = g_Camera.m_LastSimulation.m_Coords.radius;

  g_Camera.unk_0xA8.m_Coords.azimuth = 0;
  g_Camera.unk_0xA8.m_Coords.elevation = 0;
  g_Camera.unk_0xA8.m_Coords.radius = 0;

  // No clue
  g_Camera.unk_0xA8.m_Offset.azimuth = 0;
  g_Camera.unk_0xA8.m_Offset.elevation = 0;
  g_Camera.unk_0xA8.m_Offset.radius = 0;
  g_Camera.unk_0xC4 = 0;

  g_Camera.m_SpyroOffCenterFrames = 0;

  // No clue
  g_Camera.m_Sphere.m_Offset.azimuth =
      g_Camera.m_LastSimulation.m_Offset.azimuth;
  g_Camera.m_Sphere.m_Offset.elevation =
      g_Camera.m_LastSimulation.m_Offset.elevation;
  g_Camera.m_Sphere.m_Offset.radius = g_Camera.m_LastSimulation.m_Offset.radius;

  func_80034204(
      &g_Camera.m_DestinationPosition); // Calculate the new position from the
                                        // spherical coordinates

  VecAdd(&g_Camera.m_DestinationPosition, &g_Camera.m_DestinationPosition,
         g_Camera.m_Focus); // m_DestinationPosition += m_Focus

  VecCopy(
      &g_Camera.m_Position,
      &g_Camera.m_DestinationPosition); // m_Position = m_DestinationPosition

  g_Camera.unk_0xE8 = func_80033F08(&g_Camera.m_Position);

  func_800342F8(); // Update the camera's rotation

  // Reset the screen shake stuff
  D_800756DC = 0;
  D_8007590C = 0;
}

// Does the camera's collision, updates the spherical coordinates
extern SphericalCoordsOffset D_8006C82C[5];
extern SphericalCoordsOffset D_8006C830[5];
extern SphericalCoordsOffset D_8006C834[5];
extern SphericalCoordsOffset D_8006CAB4[5];
extern Vector3D g_CollisionPoint;

void func_80034480(void) {
  Vector3D sp10;
  Vector3D sp20;
  SphericalCoordsOffset savedSimulation;
  int i;
  int j;
  int steps;
  int far;
  int collisionFound;
  int validMask;
  Vector3D *pDest;
  Vector3D *pArg;
  SphericalCoordsOffset *pSphere;
  collisionFound = 0;
  pDest = &g_Camera.m_DestinationPosition;
  VecSub(&sp20, pDest, &g_Spyro.m_Position);
  far = VecMagnitude(&sp20, 1) >= 0x2001;
  VecCopy(&sp10, pDest);
  VecSub(&sp20, pDest, &g_Camera.m_Position);
  steps = (VecMagnitude(&sp20, 1) / 0x100) + 1;
  if (steps >= 2) {
    sp20.x /= steps;
    sp20.y /= steps;
    sp20.z /= steps;
  }
  VecCopy(pDest, &g_Camera.m_Position);
  j = 0;
  if (collisionFound >= steps) {
    goto outer_end;
  }
outer_loop:
  VecAdd(pDest, pDest, &sp20);

  for (i = 0; i < 6; i++) {
    if (func_8004BE4C(pDest, 0x100, 0x100) == 0) {
      break;
    }
    VecCopy(pDest, &g_CollisionPoint);
    collisionFound = 1;
  }

  if (i == 6) {
    VecCopy(pDest, &sp10);
    j = steps;
  }
  j++;
  if (j < steps) {
    goto outer_loop;
  }
outer_end:
  g_Camera.unk_0xCC = 0;

  if (i < 6) {
    if (collisionFound != 0) {
      VecSub(&sp10, &g_Camera.m_DestinationPosition, &g_Camera.m_Position);
      if (((sp10.x >= 0) ? (sp10.x) : (-sp10.x)) < 0x20) {
        sp10.x = 0;
      }
      if (((sp10.y >= 0) ? (sp10.y) : (-sp10.y)) < 0x20) {
        sp10.y = 0;
      }
      if (((sp10.z >= 0) ? (sp10.z) : (-sp10.z)) < 0x20) {
        sp10.z = 0;
      }
      if (steps) {
        VecAdd(&g_Camera.m_Position, &g_Camera.m_Position, &sp10);
      } else {
        VecAdd(&g_Camera.m_Position, &g_Camera.m_Position, &sp10);
      }
    } else {
      VecCopy(&g_Camera.m_Position, &g_Camera.m_DestinationPosition);
      g_Camera.unk_0xCC = 1;
    }
  }
  g_Camera.unk_0xE8 = func_80033F08(&g_Camera.m_Position);
  VecCopy(&sp20, &g_Spyro.m_Position);
  sp20.z -= 0x134;
  if ((func_80033E40(&g_Camera.m_Position, &sp20) == 0) ||
      (func_80033E40(&sp20, &g_Camera.m_Position) == 0)) {
    D_800756B8 = 0;
    if (((u_char)g_Spyro.m_sortingDepth) < 0x7F) {
      g_Spyro.m_sortingDepth = 2;
    }
    D_8007AA10.unk_1c = 0;
    g_Camera.m_SpyroOffCenterFrames++;
    validMask = 0;
    if (g_Camera.m_SpyroOffCenterFrames >= 0x1F) {
      for (i = 0; i < 5; i++) {
        g_Camera.m_SphericalPreset = &D_8006CAB4[i];
        func_80034358();
        if (((func_8004BE4C(&g_Camera.m_DestinationPosition, 0x100, 0x100) ==
              0) &&
             (func_80033E40(&g_Camera.m_DestinationPosition, &sp20) != 0)) &&
            (func_80033E40(&sp20, &g_Camera.m_DestinationPosition) != 0)) {
          return;
        }
      }

      validMask = 0;
    }
    savedSimulation = g_Camera.m_Simulation;
    for (i = 0; i < 5; i++) {
      pSphere = &g_Camera.m_Sphere;
      g_Camera.m_Sphere.m_Coords.azimuth =
          (g_Camera.m_Simulation.m_Coords.azimuth +
           D_8006C82C[i].m_Coords.azimuth) &
          0xFFF;
      g_Camera.m_Sphere.m_Coords.elevation =
          (g_Camera.m_Simulation.m_Coords.elevation +
           D_8006C830[i].m_Coords.azimuth) &
          0xFFF;
      g_Camera.m_Sphere.m_Coords.radius =
          g_Camera.m_Simulation.m_Coords.radius +
          D_8006C834[i].m_Coords.azimuth;
      func_80034204(&g_Camera.m_DestinationPosition);
      VecAdd(&g_Camera.m_DestinationPosition, &g_Camera.m_DestinationPosition,
             g_Camera.m_Focus);
      if (func_8004BE4C(&g_Camera.m_DestinationPosition, 0x100, 0x100) != 0) {
        continue;
      }
      validMask |= 1 << i;
      if (func_80033E40(&g_Camera.m_DestinationPosition, &sp20) == 0) {
        continue;
      }
      if (func_80033E40(&sp20, &g_Camera.m_DestinationPosition) != 0) {
        pArg = &g_Camera.m_DestinationPosition;
        goto found_simulation;
      }
    }

    if (validMask != 0) {
      for (i = 0; i < 5; i++) {
        pSphere = &g_Camera.m_Sphere;
        if (!(validMask & (1 << i))) {
          continue;
        }
        g_Camera.m_Sphere.m_Coords.azimuth =
            (g_Camera.m_Simulation.m_Coords.azimuth +
             (D_8006C82C[i].m_Coords.azimuth * 2)) &
            0xFFF;
        g_Camera.m_Sphere.m_Coords.elevation =
            (g_Camera.m_Simulation.m_Coords.elevation +
             (D_8006C830[i].m_Coords.azimuth * 2)) &
            0xFFF;
        g_Camera.m_Sphere.m_Coords.radius =
            g_Camera.m_Simulation.m_Coords.radius +
            (D_8006C834[i].m_Coords.azimuth * 2);
        func_80034204(&g_Camera.m_DestinationPosition);
        VecAdd(&g_Camera.m_DestinationPosition, &g_Camera.m_DestinationPosition,
               g_Camera.m_Focus);
        if (func_8004BE4C(&g_Camera.m_DestinationPosition, 0x100, 0x100) != 0) {
          continue;
        }
        if (func_80033E40(&g_Camera.m_DestinationPosition, &sp20) == 0) {
          continue;
        }
        if (func_80033E40(&sp20, &g_Camera.m_DestinationPosition) != 0) {
          pArg = &g_Camera.m_DestinationPosition;
          goto found_simulation;
        }
      }

      if (validMask != 0) {
        for (i = 0; i < 5; i++) {
          pSphere = &g_Camera.m_Sphere;
          if (!(validMask & (1 << i))) {
            continue;
            do {
            } while (0);
          }
          g_Camera.m_Sphere.m_Coords.azimuth =
              (g_Camera.m_Simulation.m_Coords.azimuth +
               (D_8006C82C[i].m_Coords.azimuth * 4)) &
              0xFFF;
          g_Camera.m_Sphere.m_Coords.elevation =
              (g_Camera.m_Simulation.m_Coords.elevation +
               (D_8006C830[i].m_Coords.azimuth * 4)) &
              0xFFF;
          g_Camera.m_Sphere.m_Coords.radius =
              g_Camera.m_Simulation.m_Coords.radius +
              (D_8006C834[i].m_Coords.azimuth * 4);
          func_80034204(&g_Camera.m_DestinationPosition);
          VecAdd(&g_Camera.m_DestinationPosition,
                 &g_Camera.m_DestinationPosition, g_Camera.m_Focus);
          if (func_8004BE4C(&g_Camera.m_DestinationPosition, 0x100, 0x100) !=
              0) {
            continue;
          }
          if (func_80033E40(&g_Camera.m_DestinationPosition, &sp20) == 0) {
            continue;
          }
          if (func_80033E40(&sp20, &g_Camera.m_DestinationPosition) != 0) {
            pArg = &g_Camera.m_DestinationPosition;
            goto found_simulation;
          }
        }
      }
    }
    return;
  }
  D_800756B8 = 1;
  if (g_Camera.unk_0xC4 != 0) {
    if ((g_Camera.m_State == 0) || (g_Camera.m_State == 0x80000009)) {
      asm volatile("" : : : "memory");
      if (g_Camera.unk_0xE8 != 0) {
        g_Camera.unk_0xC4--;
      }
    } else {
      g_Camera.unk_0xC4--;
    }
  }
  if (((int)g_Camera.m_State) < 0) {
    goto zero_offcenter;
  }
  func_80017AA4(&sp20, &g_Spyro.m_Position);
  if (((((u_int)(sp20.x - 0x21)) >= 0x1BF) ||
       (((u_int)(sp20.y - 0x19)) >= 0xBF)) ||
      (far != 0)) {
    goto incr_offcenter;
  }
zero_offcenter:
  g_Camera.m_SpyroOffCenterFrames = 0;

  return;
found_simulation:
  *((int *)(((char *)pSphere) + 0x4C)) = 5;
  func_80033F08(pArg);
  *((SphericalCoordinates *)(((char *)pSphere) - 0x18)) =
      *((SphericalCoordinates *)(((char *)pSphere) + 0x18));
  *((SphericalCoordsOffset *)(((char *)pSphere) + 0x18)) = savedSimulation;
  return;
incr_offcenter:
  g_Camera.m_SpyroOffCenterFrames++;
}

/// @brief Forces the camera to its destination position
void CameraForceToDestination(void) {
  VecCopy(&g_Camera.m_Position, &g_Camera.m_DestinationPosition);
  g_Camera.unk_0xC4 = 0;
  g_Camera.m_SpyroOffCenterFrames = 0;
  g_Camera.unk_0xCC = 1;
  D_800756B8 = 1;
  g_Camera.unk_0xE8 = func_80033F08(&g_Camera.m_Position);
}

void func_80034CE8(int);

// Related to updating the spherical coordinates, not 100% sure
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/camera", func_80034CE8);

void func_800357A4(void);

// Camera movement related, seems to be for warping it when blocked
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/camera", func_800357A4);

/// @brief Camera rotation with gamepad L2 R2
void func_80035F58() {
  D_80075924 = 0; // Reset the L2 R2 rotation speed

  // If CTRL_SKIP_CAMERA_CENTER is set, or Spyro isn't in the center of the
  // screen, return
  if (g_Spyro.m_ControlFlags & CTRL_SKIP_CAMERA_CENTER ||
      g_Camera.m_SpyroOffCenterFrames)
    return;

  // If L2 or R2 is held, set the rotation speed accordingly
  if (g_Pad.m_Held & PAD_R2) {
    D_80075924 = -1024;
  } else if (g_Pad.m_Held & PAD_L2) {
    D_80075924 = 1024;
  }
}

void func_80035FB4(void);

// Camera state update for all other states
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/camera", func_80035FB4);

// Camera state update for 0x8000000B
void func_8003740C(void) {
  Vector3D nodeNodeDifference;
  Vector3D spyroCameraDifference;
  Vector3D pointNodeDifference;
  int nodeDistance;
  int cameraSpyroDistance;
  int activePathNode;
  int var_s0; // First used for winding, then for something else

  activePathNode = g_Spyro.unk_0x240->m_CurrentNode;

  VecSub(&pointNodeDifference,
         &g_Spyro.unk_0x240->m_Nodes[activePathNode].m_Position,
         &g_Camera.m_Position);

  nodeDistance = VecMagnitude(&pointNodeDifference, 1);

  // Checks if the distance to the path node is less than 0.5M
  if (nodeDistance < 512) {
    if (g_Spyro.unk_0x248) {
      if (g_Spyro.unk_0x240->m_CurrentNode != 0)
        g_Spyro.unk_0x240->m_CurrentNode--;
    } else {
      if (g_Spyro.unk_0x240->m_CurrentNode < g_Spyro.unk_0x240->m_NodeCount - 1)
        g_Spyro.unk_0x240->m_CurrentNode++;
    }
  }

  var_s0 = 0;
  if (g_Spyro.unk_0x248 != 0) {
    var_s0 = activePathNode < (g_Spyro.unk_0x240->m_NodeCount - 1);
  } else if (activePathNode != 0) {
    var_s0 = 1;
  }

  if (var_s0 != 0) { // False until spyro goes through the portal
    VecSub(&spyroCameraDifference, &g_Spyro.m_Position, &g_Camera.m_Position);
    cameraSpyroDistance = VecMagnitude(&spyroCameraDifference, 1);
    var_s0 = 0;
    if (cameraSpyroDistance > 1024) {

      var_s0 = (cameraSpyroDistance - 1024) * 4;

      if (var_s0 > cameraSpyroDistance) {
        var_s0 = cameraSpyroDistance;
      }

      VecScaleToLength(&spyroCameraDifference, cameraSpyroDistance, var_s0);

      cameraSpyroDistance = var_s0;

      if (g_Spyro.unk_0x248 != 0) {
        VecSub(&nodeNodeDifference,
               &g_Spyro.unk_0x240->m_Nodes[activePathNode].m_Position,
               &g_Spyro.unk_0x240->m_Nodes[activePathNode + 1].m_Position);
      } else {
        VecSub(&nodeNodeDifference,
               &g_Spyro.unk_0x240->m_Nodes[activePathNode].m_Position,
               &g_Spyro.unk_0x240->m_Nodes[activePathNode - 1].m_Position);
      }

      func_80017330(&nodeNodeDifference, 4096);

      // SKELETON: Holy shit, this literally makes the compiler output dead
      // code the ABS is useless, and the < 0 that follows it more so
      var_s0 = ABS((((nodeNodeDifference.x * spyroCameraDifference.x) +
                     (nodeNodeDifference.y * spyroCameraDifference.y) +
                     (nodeNodeDifference.z * spyroCameraDifference.z)) /
                    cameraSpyroDistance));

      if (var_s0 < 0) {
        var_s0 = 0;
      }

      if (var_s0 > 4096) {
        var_s0 = 4096;
      }

      var_s0 = FIXED_MUL(var_s0, 128);
    }
  } else {
    // Spyro hasn't gone through the portal yet
    var_s0 = MIN(g_Spyro.unk_0x244, nodeDistance);
  }

  // var_s0 (frame 1) = 0x60
  // var_s0 (frame 2) = 0x60
  // var_s0 (frame 3+) = 0x78

  VecScaleToLength(&pointNodeDifference, nodeDistance, var_s0 * g_DeltaTime);
  VecAdd(&g_Camera.m_Position, &g_Camera.m_Position,
         &pointNodeDifference); // g_Camera.m_Position += pointNodeDifference

  var_s0 = 0; // ????? Needed to match the MIN above

  g_Camera.unk_0xE8 = func_80033F08(&g_Camera.m_Position);

  func_800342F8();
}

/// @brief Sets the level fly-in parameters
/// @param param New level fly-in parameters
void func_80037714(LevelFlyInParameters *param) {

  g_Camera.unk_0xEC = param;

  // Copy over the camera position
  VecCopy(&g_Camera.m_Position, &g_Camera.unk_0xEC->m_CameraPosition);

  // Reset Spyro's acceleration, and give him negative z acceleration
  VecNull(&g_Spyro.m_Physics.m_Acceleration);
  g_Spyro.m_Physics.m_Acceleration.z = -8960;

  // Copy over the camera rotation
  g_Camera.m_Rotation.x = g_Camera.unk_0xEC->m_CameraRotation.x;
  g_Camera.m_Rotation.y = g_Camera.unk_0xEC->m_CameraRotation.y;
  g_Camera.m_Rotation.z = g_Camera.unk_0xEC->m_CameraRotation.z;

  // Set the camera state to 0x8000000E
  g_Camera.m_State = 0x8000000E;
  g_Camera.unk_0xC0 = 0x8000000E; // I think this is the next state?
}

/// @brief Bad bad function
void func_800377A8(void) {
  Vector3D tempVector;
  int spawnIndex;
  int spyroCameraDistance;

  spawnIndex = 0;

  // If load stage is < 0
  if (g_LoadStage < 0) {
    // - 32u >= 2 Makes fairly little sense.. Probably this was some kind of
    // optimized switch statement? Wasn't able to replicate it unfortunately
    if (g_Spyro.m_State != 6 && g_Spyro.m_State != 16 &&
        g_Spyro.m_State - 32u >= 2 && g_Spyro.m_State != 34 &&
        g_Spyro.m_State != 15 && g_Spyro.m_State != 29) {
      g_Camera.unk_0xC0 = D_8006C588[g_Spyro.m_State];
    }
  } else { // Can't be reached, because loadstage is always < 0 when this camera
           // is active!

    // SKELETON: This code is broken, and most importantly, unused!
    // It's some weird system that picks a random spawn spot for Spyro. No clue
    // why it's part of Camera. This code is ancient, in June it was already
    // broken
    if (g_Camera.unk_0xEC == nullptr) {
      spawnIndex = 1;
    } else {

      VecSub(&tempVector, &g_Camera.m_Position, &g_Spyro.m_Position);
      spyroCameraDistance = VecMagnitude(&tempVector, 1);

      VecSub(&tempVector, &g_Camera.m_Position, &g_Spyro.m_previousPosition);

      if (spyroCameraDistance > g_Camera.unk_0xEC->unk_0x34 &&
          spyroCameraDistance > VecMagnitude(&tempVector, 1)) {
        spawnIndex = 1;
      } else {
        func_80017AA4(&tempVector, &g_Spyro.m_Position);
        if (tempVector.y > 240) {
          spawnIndex = 1;
        }
      }
    }

    if (spawnIndex || (g_Camera.m_State != 0x8000000E)) {
      spawnIndex = (rand() & 0xFFF);
      spawnIndex = (spawnIndex * 3) >> 12;

      // SKELETON: This is broken, even by June, unk_0xEC is reset while the
      // camera is active.. Shows how old this code is
      if (g_Camera.unk_0xEC == &D_8006EB24[spawnIndex]) {
        // If we hit the same one as last time, pick the next one
        spawnIndex = (spawnIndex + 1) % 3;
      }

      // Change the intro position
      func_80037714(&D_8006EB24[spawnIndex]);
      VecCopy(&g_Spyro.m_Position, &g_Camera.unk_0xEC->m_SpyroPosition);

      g_Spyro.m_Physics.m_SpeedAngle.m_RotX =
          g_Camera.unk_0xEC->m_SpyroRotation.x;
      g_Spyro.m_Physics.m_SpeedAngle.m_RotY =
          g_Camera.unk_0xEC->m_SpyroRotation.y;
      g_Spyro.m_Physics.m_SpeedAngle.m_RotZ =
          g_Camera.unk_0xEC->m_SpyroRotation.z;
    }
  }

  if (g_Camera.unk_0xEC->unk_0x30 == 1) {

    // SKELETON: It calculates the distance, but does nothing with it
    VecSub(&tempVector, &g_Spyro.m_Position, &g_Camera.m_Position);

    // Update the spherical coordinates
    g_Camera.unk_0xE8 = func_80033F08(&g_Camera.m_Position);

    // Update the camera's rotation
    func_800342F8();
  }
}

// Not sure how to represent this properly, it might be an array
// But the way this data is formatted is just absurd
extern SphericalCoordsOffset D_8006C964;
extern SphericalCoordsOffset D_8006CA3C;
extern SphericalCoordsOffset D_8006CA54;
extern SphericalCoordsOffset D_8006CA6C;

/// @brief Update function used during the level transition
void func_80037A20(void) {
  int i;

  g_Camera.m_Focus = &g_Spyro.m_Position;
  g_Camera.m_FocusRotation = g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;
  if (g_PortalLevelId != 0) {
    if (g_LoadStage >= 0xA) {
      g_Camera.m_SphericalPreset = &D_8006C964;
    } else {
      g_Camera.m_SphericalPreset = &D_8006CA54;
    }
  } else if (g_Camera.m_SphericalPreset == nullptr) {
    if (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ < g_Camera.m_Rotation.z) {
      g_Camera.m_SphericalPreset = &D_8006CA3C;
    } else {
      g_Camera.m_SphericalPreset = &D_8006CA6C;
    }
  }

  ApplySphericalPreset();

  D_80075924 = 0;

  for (i = 0; i < g_DeltaTime; i++) {
    func_80034CE8(0);
  }

  func_80034204(&g_Camera.m_DestinationPosition);
  VecAdd(&g_Camera.m_DestinationPosition, &g_Camera.m_DestinationPosition,
         g_Camera.m_Focus);
  CameraForceToDestination();
  func_800342F8();

  // Update the sphere coordinates
  g_Camera.unk_0xE8 = func_80033F08(&g_Camera.m_Position);

  g_Camera.m_Sphere.m_Coords.azimuth = g_Camera.m_Simulation.m_Coords.azimuth;
  g_Camera.m_Sphere.m_Coords.elevation =
      g_Camera.m_Simulation.m_Coords.elevation;
  g_Camera.m_Sphere.m_Coords.radius = g_Camera.m_Simulation.m_Coords.radius;

  g_Camera.m_Sphere.m_Offset.azimuth = g_Camera.m_Simulation.m_Offset.azimuth;
  g_Camera.m_Sphere.m_Offset.elevation =
      g_Camera.m_Simulation.m_Offset.elevation;
  g_Camera.m_Sphere.m_Offset.radius = g_Camera.m_Simulation.m_Offset.radius;
}

/// @brief Camera update function
void CameraUpdate(void) {

  if (g_Spyro.m_State == 0x1B) {
    D_8007592C = 1;
  } else {
    D_8007592C = 0;
  }

  g_PadSwapFlag = 0;

  if (g_Spyro.m_noGamepadUpdateFrames != 0) {
    func_80053708(&g_Pad, &g_PadBackup);
  }

  if (g_Spyro.unk_0x194 != 0) {
    g_Camera.unk_0xC0 = 0;
    D_80075894 = 0;
  } else if (g_Camera.unk_0xC0 >= 0) {
    g_Camera.unk_0xC0 = D_8006C588[g_Spyro.m_State];
  }

  func_800357A4();

  if (g_Camera.m_State == 0x8000000E) {
    func_800377A8();
  } else if (g_Camera.m_State == 0x80000012) {
    func_80037A20();
  } else {
    if (g_Camera.m_State == 0x8000000B) {
      func_8003740C();
    } else {
      func_80035FB4();
    }

    // Check if the unused screen shake effect is active
    if (D_8007590C != 0) {
      if (D_80075848 < D_8007590C) {
        D_80075848 = D_8007590C;
      }

      // Update the unused screenshake effect
      D_8007590C -= g_DeltaTime;

      if (D_8007590C < 0) {
        D_8007590C = 0;
      }

      // Process the unused screenshake effect
      g_Camera.m_Position.z +=
          ((D_800756DC * D_8007590C * ((g_GameTick & 2) - 1)) / D_80075848) >>
          6;
    } else {
      //
      D_80075848 = 0;
    }

    if (g_LoadStage < 0) {
      if (func_8004DF24(&g_Camera.m_Position) != 0) {
        g_Camera.m_OcclusionGroup = D_80075844;
      }
      if (g_Camera.m_OcclusionGroup >= g_Environment.m_OcclusionGroupCount) {
        g_Camera.m_OcclusionGroup = -1;
      }
      g_Camera.unk_0xEC = 0;
    }
  }

  if (g_PadSwapFlag != 0) {
    func_80053708(&g_PadBackup, &g_Pad);
  }
}
