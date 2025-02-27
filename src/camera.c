#include "common.h"

#include "camera.h"
#include "collision.h"
#include "environment.h"
#include "gamepad.h"
#include "loaders.h"
#include "math.h"
#include "memory.h"
#include "spyro.h"

#include <libgte.h>

extern int rand(void); // From psyq
extern void srand(unsigned int);

// FYI, these are inside of this file rather than just extern,
// because otherwise the compiler didn't make use of gp_rel!
// This means that these variables were orignally inside of
// this file as well.

// Fuck knows
int D_80075894;
int D_80075924; // L2 and R2 rotation speed

/// @brief Creates the Camera's view and projection matrices
void CameraUpdateMatrices(void) {
  // If it wasn't for the projection part, this function could've
  // been used for creating a matrix from any rotation vector..
  // But they decided to hardcode stuff instead

  MATRIX mtx;
  MATRIX tMtx;
  int t;

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
  t = mtx.m[1][0] * 320;
  if (t < 0)
    t += 511;
  mtx.m[1][0] = t >> 9; // / 512

  t = mtx.m[1][1] * 320;
  if (t < 0)
    t += 511;
  mtx.m[1][1] = t >> 9; // / 512

  t = mtx.m[1][2] * 320;
  if (t < 0)
    t += 511;
  mtx.m[1][2] = t >> 9; // / 512

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
  func_800175B8(&distance, magnitude, 1024);

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
int func_80033F08(Vector3D *pVec);

// Function for updating the spherical coordinates
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/camera", func_80033F08);

// Updates the spherical coordinates, rotation related?
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/camera", func_80034198);
void func_80034198(void);

/// @brief: Converts the camera's spherical coordinates to cartesian coordinates
void func_80034204(Vector3D *pOut) {
  // I curse whoever didn't want to add an input parameter to this function

  /* clang-format off */ 

  // x = r * cos(e) * cos(a)
  pOut->x =
      FIXED_MUL(
          FIXED_MUL(g_Camera.m_SphereCoords.radius, Cos(g_Camera.m_SphereCoords.elevation)),
          Cos(g_Camera.m_SphereCoords.azimuth)
        );

  // y = (-r * cos(e)) * sin(a)
  pOut->y =
      FIXED_MUL(
          -FIXED_MUL(g_Camera.m_SphereCoords.radius, Cos(g_Camera.m_SphereCoords.elevation)),
          Sin(g_Camera.m_SphereCoords.azimuth)
        );

  // z = r * sin(e)
  pOut->z = FIXED_MUL(g_Camera.m_SphereCoords.radius, Sin(g_Camera.m_SphereCoords.elevation));

  /* clang-format on */
}

/// @brief Updates the camera's rotation based on it's spherical coordinates
void func_800342F8(void) {
  g_Camera.m_Rotation.x = g_Camera.unk_0x84.azimuth;
  g_Camera.m_Rotation.y = g_Camera.m_SimulationSphereCoords.elevation +
                              g_Camera.unk_0x84.elevation &
                          0xfff;
  g_Camera.m_Rotation.z = 0x800 - g_Camera.m_SimulationSphereCoords.azimuth -
                              g_Camera.unk_0x84.radius &
                          0xfff;
}

// Some camera reset stuff
void func_80034358(void) {
  func_80034198();

  g_Camera.m_SphereCoords.azimuth = g_Camera.m_LastSimulationCoords.azimuth;
  g_Camera.m_SphereCoords.elevation = g_Camera.m_LastSimulationCoords.elevation;
  g_Camera.m_SphereCoords.radius = g_Camera.m_LastSimulationCoords.radius;

  g_Camera.unk_0xA8.azimuth = 0;
  g_Camera.unk_0xA8.elevation = 0;
  g_Camera.unk_0xA8.radius = 0;

  // No clue
  g_Camera.unk_0xB4 = 0;
  g_Camera.unk_0xB8 = 0;
  g_Camera.unk_0xBC = 0;
  g_Camera.unk_0xC4 = 0;

  g_Camera.m_SpyroOffCenterFrames = 0;

  // No clue
  g_Camera.unk_0x84.azimuth = g_Camera.unk_0x6C.azimuth;
  g_Camera.unk_0x84.elevation = g_Camera.unk_0x6C.elevation;
  g_Camera.unk_0x84.radius = g_Camera.unk_0x6C.radius;

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
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/camera", func_80034480);

void func_80034C84(void);

// Forces the camera to it's destination forcefully
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/camera", func_80034C84);

void func_80034CE8(int);

// Related to updating the spherical coordinates, not 100% sure
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/camera", func_80034CE8);

void func_800357A4(void);

// Camera movement related, seems to be for warping it when blocked
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/camera", func_800357A4);

/// @brief Camera rotation with gamepad L2 R2
void func_80035F58() {
  D_80075924 = 0; // Reset the L2 R2 rotation speed

  // If the 0x1000 flag is set, or spyro isn't in the center of the screen,
  // return
  if (g_Spyro.unk_0x1f4 & 0x1000 || g_Camera.m_SpyroOffCenterFrames)
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

      func_800175B8(&spyroCameraDifference, cameraSpyroDistance, var_s0);

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

      func_80017330(&nodeNodeDifference, 0x1000);

      // SKELETON: Holy shit, this literally makes the compiler output dead
      // code the ABS is useless, and the < 0 that follows it more so
      var_s0 = ABS((((nodeNodeDifference.x * spyroCameraDifference.x) +
                     (nodeNodeDifference.y * spyroCameraDifference.y) +
                     (nodeNodeDifference.z * spyroCameraDifference.z)) /
                    cameraSpyroDistance));

      if (var_s0 < 0) {
        var_s0 = 0;
      }

      if (var_s0 > 0x1000) {
        var_s0 = 0x1000;
      }

      var_s0 = (var_s0 << 7) >> 0xc;
    }
  } else {
    // Spyro hasn't gone through the portal yet
    int t = g_Spyro.unk_0x244;

#if 0
    var_s0 = MIN(t, nodeDistance);
#else

    // TODO: This is fucked, they must've done something here
    // I haven't been able to match it properly without the assembly move
    __asm__ volatile("move %0, %1" : "=r"(var_s0) : "r"(nodeDistance));

    if (var_s0 > t) {
      var_s0 = t;
    }

#endif
  }

  // var_s0 (frame 1) = 0x60
  // var_s0 (frame 2) = 0x60
  // var_s0 (frame 3+) = 0x78

  func_800175B8(&pointNodeDifference, nodeDistance, var_s0 * g_DeltaTime);
  VecAdd(&g_Camera.m_Position, &g_Camera.m_Position,
         &pointNodeDifference); // g_Camera.m_Position += pointNodeDifference

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

// SKELETON: Weird shit array of three parameters that
// don't match any levels in the final game
extern LevelFlyInParameters D_8006EB24[3];

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

      VecSub(&tempVector, &g_Camera.m_Position, &g_Spyro.unk_0x8c);

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
extern SphericalCoordinates D_8006C964;
extern SphericalCoordinates D_8006CA3C;
extern SphericalCoordinates D_8006CA54;
extern SphericalCoordinates D_8006CA6C;

/// @brief Update function used during the level transition
void func_80037A20(void) {
  int i;

  g_Camera.m_Focus = &g_Spyro.m_Position;
  g_Camera.m_FocusRotation = g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;
  if (D_800758AC != 0) {
    if (g_LoadStage >= 0xA) {
      g_Camera.m_0xD8 = &D_8006C964;
    } else {
      g_Camera.m_0xD8 = &D_8006CA54;
    }
  } else if (g_Camera.m_0xD8 == nullptr) {
    if (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ < g_Camera.m_Rotation.z) {
      g_Camera.m_0xD8 = &D_8006CA3C;
    } else {
      g_Camera.m_0xD8 = &D_8006CA6C;
    }
  }

  func_80034198();

  D_80075924 = 0;

  for (i = 0; i < g_DeltaTime; i++) {
    func_80034CE8(0);
  }

  func_80034204(&g_Camera.m_DestinationPosition);
  VecAdd(&g_Camera.m_DestinationPosition, &g_Camera.m_DestinationPosition,
         g_Camera.m_Focus);
  func_80034C84();
  func_800342F8();

  // Update the sphere coordinates
  g_Camera.unk_0xE8 = func_80033F08(&g_Camera.m_Position);

  g_Camera.m_SphereCoords.azimuth = g_Camera.m_SimulationSphereCoords.azimuth;
  g_Camera.m_SphereCoords.elevation =
      g_Camera.m_SimulationSphereCoords.elevation;
  g_Camera.m_SphereCoords.radius = g_Camera.m_SimulationSphereCoords.radius;

  g_Camera.unk_0x84.azimuth = g_Camera.m_SimulationOffset.azimuth;
  g_Camera.unk_0x84.elevation = g_Camera.m_SimulationOffset.elevation;
  g_Camera.unk_0x84.radius = g_Camera.m_SimulationOffset.radius;
}

/// @brief Camera update function
void func_80037BD4(void) {

  if (g_Spyro.m_State == 0x1B) {
    D_8007592C = 1;
  } else {
    D_8007592C = 0;
  }

  D_80075944 = 0;

  if (g_Spyro.m_noGamepadUpdateFrames != 0) {
    func_80053708(&g_Pad, &D_800776D8);
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
          ((D_800756DC * D_8007590C * ((D_8007572C & 2) - 1)) / D_80075848) >>
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

  if (D_80075944 != 0) {
    func_80053708(&D_800776D8, &g_Pad);
  }
}
