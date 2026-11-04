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

// Used in func_80035FB4
int D_80075938;

/* Linker alias for g_Camera.unk_0x100, retained for matching func_80035FB4. */
extern Vector3D D_80076ED0;
__asm__(".globl D_80076ED0\nD_80076ED0 = g_Camera + 0x100");

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

/// @brief Casts a ray between two points, returns false if it hits something
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
    if (ColTraceRay(&rayStart, &rayEnd))
      return 0; // If we did, return it

    VecCopy(&rayStart, &rayEnd); // Advance the ray
  }

  return 1;
}

// Return is something happened to the azimuth
int func_80033F08(Vector3D *pVec);

// Function for updating the spherical coordinates
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/camera", func_80033F08);

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
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/camera", func_80034480);

/// @brief Forces the camera to its destination position
void CameraForceToDestination(void) {
  VecCopy(&g_Camera.m_Position, &g_Camera.m_DestinationPosition);
  g_Camera.unk_0xC4 = 0;
  g_Camera.m_SpyroOffCenterFrames = 0;
  g_Camera.unk_0xCC = 1;
  D_800756B8 = 1;
  g_Camera.unk_0xE8 = func_80033F08(&g_Camera.m_Position);
}

// Updates the camera's spherical coordinates using six smoothing channels.
void func_80034CE8(int smoothingPreset) {
    int inputDelta;
    int springCoefficient;
    int deadbandThreshold;
    int filterResult;

    // Six Camera Channels
    // Channel One: coordinate azimuth.

    springCoefficient = D_8006C754[smoothingPreset];

    // Enforce a minimum spring coefficient in camera state 3.
    if (g_Camera.m_State == 3 && springCoefficient < 0x400) {
        springCoefficient = 0x400;
    }

    // Select the azimuth input delta, accounting for special camera states.
    if (D_80075924 != 0) {
        inputDelta = D_80075924;
    } else if (((((D_80075914 & 0x10) == 0) &&
                 (D_8007592C == 0)) ||
                (g_Camera.m_State != 0x80000011)) ||
               ((inputDelta = 0, D_800756B8 == 0))) {

        if ((((((D_80075914 & 0x10) != 0) &&
               ((u_int)(g_Spyro.m_State - 5) < 2)) ||
              (D_8007592C != 0)) &&
             (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0x400)) &&
            (g_Camera.unk_0xC4 == 0) &&
            ((inputDelta = 0, g_Camera.m_OnMovingPlatform == 0))) {

            g_Camera.unk_0xA8.m_Coords.azimuth = 0;

        } else {
            inputDelta = 0;

            if (g_Camera.m_State != 6) {
                inputDelta =
                    (g_Camera.m_LastSimulation.m_Coords.azimuth -
                     g_Camera.m_Sphere.m_Coords.azimuth) & 0xFFF;

                if (inputDelta >= 0x801) {
                    inputDelta -= 0x1000;
                }
            }
        }
    }

    // Apply the azimuth spring and damping, then test the deadband.
    // filterResult is reused for the accumulator, its magnitude and the
    // deadband predicate to retain the matching instruction sequence.
    filterResult =
        (g_Camera.unk_0xA8.m_Coords.azimuth +=
         (((springCoefficient * inputDelta) -
           (D_8006C79C[smoothingPreset] *
            g_Camera.unk_0xA8.m_Coords.azimuth)) >> 8));

    deadbandThreshold = D_8006C7E4[smoothingPreset];

    if (filterResult < 0) {
        filterResult = -filterResult;
    }

    filterResult = (filterResult < deadbandThreshold);

    if (filterResult) {
        g_Camera.unk_0xA8.m_Coords.azimuth = 0;

        if (g_Camera.unk_0xCC != 0) {
            if (inputDelta > 0) {
                g_Camera.unk_0xA8.m_Coords.azimuth = 0x100;
            } else if (inputDelta < 0) {
                g_Camera.unk_0xA8.m_Coords.azimuth = -0x100;
            }
        }
    }

    // Clamp azimuth during a particular Spyro animation state.
    if (g_Spyro.m_State == 0xF &&
        g_Spyro.m_walkingState == 0xB) {

        if (g_Camera.unk_0xA8.m_Coords.azimuth < -0x800) {
            g_Camera.unk_0xA8.m_Coords.azimuth = -0x800;
        }

        if (g_Camera.unk_0xA8.m_Coords.azimuth >= 0x801) {
            g_Camera.unk_0xA8.m_Coords.azimuth = 0x800;
        }
    }

    // Apply the optional azimuth limit for camera state 0x80000009 or state 3.
    if ((D_80075914 & 0x40) != 0 &&
        g_Camera.unk_0xC4 == 0 &&
        (g_Camera.m_State == 0x80000009u ||
         g_Camera.m_State == 3)) {

        if (g_Camera.unk_0xA8.m_Coords.azimuth < -0x2000) {
            g_Camera.unk_0xA8.m_Coords.azimuth = -0x2000;
        }

        if (g_Camera.unk_0xA8.m_Coords.azimuth > 0x2000) {
            g_Camera.unk_0xA8.m_Coords.azimuth = 0x2000;
        }
    }

    // Apply the additional clamp for camera states 0 and 0x80000000.
    if (((((D_80075914 & 0x10) ||
           (D_8007592C != 0)) &&
          (D_80075894 == 0)) &&
         (D_800756B8 != 0)) &&
        (g_Camera.m_OnMovingPlatform == 0) &&
        ((g_Camera.m_State == 0) ||
         (g_Camera.m_State == 0x80000000))) {

        if (g_Camera.unk_0xA8.m_Coords.azimuth < -0x800) {
            g_Camera.unk_0xA8.m_Coords.azimuth = -0x800;
        }

        if (g_Camera.unk_0xA8.m_Coords.azimuth >= 0x801) {
            g_Camera.unk_0xA8.m_Coords.azimuth = 0x800;
        }
    }

    // Accumulate the filtered azimuth into the camera angle.
    g_Camera.m_Sphere.m_Coords.azimuth +=
        g_Camera.unk_0xA8.m_Coords.azimuth >> 8;


    // Channel Two: coordinate elevation.

    if (((D_80075914 & 0x10) != 0 || D_8007592C != 0) &&
        g_Camera.m_State == 0x80000011) {

        inputDelta = 0;

    } else if ((D_80075914 & 0x10) != 0 &&
               g_Spyro.m_State == 6 &&
               ((inputDelta = 0), g_Camera.unk_0xC4 == 0)) {

        g_Camera.unk_0xA8.m_Coords.elevation = 0;

    } else if (g_Camera.m_State == 6) {
        inputDelta = 0;

    } else {
        inputDelta =
            (g_Camera.m_LastSimulation.m_Coords.elevation -
             g_Camera.m_Sphere.m_Coords.elevation) & 0xFFF;

        if (inputDelta >= 0x801) {
            inputDelta -= 0x1000;
        }
    }

    // Apply the elevation spring, damping and deadband.
    filterResult =
        (g_Camera.unk_0xA8.m_Coords.elevation +=
         (((springCoefficient = D_8006C760[smoothingPreset]) * inputDelta -
           (D_8006C7A8[smoothingPreset] *
            g_Camera.unk_0xA8.m_Coords.elevation)) >> 8));

    deadbandThreshold = D_8006C7F0[smoothingPreset];

    if (filterResult < 0) {
        filterResult = -filterResult;
    }

    filterResult = (filterResult < deadbandThreshold);

    if (filterResult) {
        g_Camera.unk_0xA8.m_Coords.elevation = 0;

        if (g_Camera.unk_0xCC != 0) {
            if (inputDelta > 0) {
                g_Camera.unk_0xA8.m_Coords.elevation = 0x100;
            } else if (inputDelta < 0) {
                g_Camera.unk_0xA8.m_Coords.elevation = -0x100;
            }
        }
    }

    // Apply the optional elevation limit for camera state 0x80000009.
    if ((D_80075914 & 0x40) != 0 &&
        g_Camera.m_State == 0x80000009 &&
        g_Camera.unk_0xC4 == 0) {

        if (g_Camera.unk_0xA8.m_Coords.elevation < -0x2000) {
            g_Camera.unk_0xA8.m_Coords.elevation = -0x2000;
        }

        if (g_Camera.unk_0xA8.m_Coords.elevation > 0x2000) {
            g_Camera.unk_0xA8.m_Coords.elevation = 0x2000;
        }
    }

    // Accumulate the filtered elevation into the camera angle.
    g_Camera.m_Sphere.m_Coords.elevation +=
        g_Camera.unk_0xA8.m_Coords.elevation >> 8;


    // Channel Three: coordinate radius.

    if (((((D_80075914 & 0x10) != 0) ||
          (D_8007592C != 0)) &&
         (g_Camera.m_State == 0x80000011)) ||
        (g_Camera.m_State == 6)) {

        inputDelta = 0;

    } else {
        inputDelta = g_Camera.m_LastSimulation.m_Coords.radius -
                     g_Camera.m_Sphere.m_Coords.radius;
    }

    // Apply the radius spring, damping and deadband.
    filterResult =
        (g_Camera.unk_0xA8.m_Coords.radius +=
         (((springCoefficient = D_8006C76C[smoothingPreset]) * inputDelta -
           (D_8006C7B4[smoothingPreset] *
            g_Camera.unk_0xA8.m_Coords.radius)) >> 8));

    deadbandThreshold = D_8006C7FC[smoothingPreset];

    if (filterResult < 0) {
        filterResult = -filterResult;
    }

    filterResult = (filterResult < deadbandThreshold);

    if (filterResult) {
        g_Camera.unk_0xA8.m_Coords.radius = 0;

        if (g_Camera.unk_0xCC != 0) {
            if (inputDelta > 0) {
                g_Camera.unk_0xA8.m_Coords.radius = 0x100;
            } else if (inputDelta < 0) {
                g_Camera.unk_0xA8.m_Coords.radius = -0x100;
            }
        }
    }

    // Accumulate the filtered radius into the camera distance.
    g_Camera.m_Sphere.m_Coords.radius +=
        g_Camera.unk_0xA8.m_Coords.radius >> 8;


    // Channel Four: offset azimuth.

    if (((((D_80075914 & 0x10) != 0) ||
          (D_8007592C != 0)) &&
         (g_Camera.m_State == 0x80000011)) ||
        (g_Camera.m_State == 6)) {

        inputDelta = 0;

    } else {
        inputDelta =
            (g_Camera.m_LastSimulation.m_Offset.azimuth -
             g_Camera.m_Sphere.m_Offset.azimuth) & 0xFFF;

        if (inputDelta >= 0x801) {
            inputDelta -= 0x1000;
        }
    }

    // Apply the offset azimuth spring, damping and deadband.
    filterResult =
        (g_Camera.unk_0xA8.m_Offset.azimuth +=
         (((springCoefficient = D_8006C778[smoothingPreset]) * inputDelta -
           (D_8006C7C0[smoothingPreset] *
            g_Camera.unk_0xA8.m_Offset.azimuth)) >> 8));

    deadbandThreshold = D_8006C808[smoothingPreset];

    if (filterResult < 0) {
        filterResult = -filterResult;
    }

    filterResult = (filterResult < deadbandThreshold);

    if (filterResult) {
        g_Camera.unk_0xA8.m_Offset.azimuth = 0;

        if (g_Camera.unk_0xCC != 0) {
            if (inputDelta > 0) {
                g_Camera.unk_0xA8.m_Offset.azimuth = 0x100;
            } else if (inputDelta < 0) {
                g_Camera.unk_0xA8.m_Offset.azimuth = -0x100;
            }
        }
    }

    // Accumulate the filtered offset azimuth.
    g_Camera.m_Sphere.m_Offset.azimuth +=
        g_Camera.unk_0xA8.m_Offset.azimuth >> 8;


    // Channel Five: offset elevation.

    if (((D_80075914 & 0x10) != 0 || D_8007592C != 0) &&
        g_Camera.m_State == 0x80000011) {

        inputDelta = 0;

    } else if (g_Camera.m_State == 6) {
        inputDelta = 0;

    } else {
        inputDelta =
            (g_Camera.m_LastSimulation.m_Offset.elevation -
             g_Camera.m_Sphere.m_Offset.elevation) & 0xFFF;

        if (inputDelta >= 0x801) {
            inputDelta -= 0x1000;
        }
    }

    // Apply the offset elevation spring, damping and deadband.
    filterResult =
        (g_Camera.unk_0xA8.m_Offset.elevation +=
         (((springCoefficient = D_8006C784[smoothingPreset]) * inputDelta -
           (D_8006C7CC[smoothingPreset] *
            g_Camera.unk_0xA8.m_Offset.elevation)) >> 8));

    deadbandThreshold = D_8006C814[smoothingPreset];

    if (filterResult < 0) {
        filterResult = -filterResult;
    }

    filterResult = (filterResult < deadbandThreshold);

    if (filterResult) {
        g_Camera.unk_0xA8.m_Offset.elevation = 0;

        if (g_Camera.unk_0xCC != 0) {
            if (inputDelta > 0) {
                g_Camera.unk_0xA8.m_Offset.elevation = 0x100;
            } else if (inputDelta < 0) {
                g_Camera.unk_0xA8.m_Offset.elevation = -0x100;
            }
        }
    }

    // Accumulate the filtered offset elevation.
    // Unlike coordinate elevation, this channel has no additional state clamp.
    g_Camera.m_Sphere.m_Offset.elevation +=
        g_Camera.unk_0xA8.m_Offset.elevation >> 8;


    // Channel Six: offset radius.

    if (((D_80075914 & 0x10) != 0 || D_8007592C != 0) &&
        g_Camera.m_State == 0x80000011) {

        inputDelta = 0;

    } else if (g_Camera.m_State == 6) {
        inputDelta = 0;

    } else {
        inputDelta =
            (g_Camera.m_LastSimulation.m_Offset.radius -
             g_Camera.m_Sphere.m_Offset.radius) & 0xFFF;

        if (inputDelta >= 0x801) {
            inputDelta -= 0x1000;
        }
    }

    // Apply the offset radius spring, damping and deadband.
    filterResult =
        (g_Camera.unk_0xA8.m_Offset.radius +=
         (((springCoefficient = D_8006C790[smoothingPreset]) * inputDelta -
           (D_8006C7D8[smoothingPreset] *
            g_Camera.unk_0xA8.m_Offset.radius)) >> 8));

    deadbandThreshold = D_8006C820[smoothingPreset];

    if (filterResult < 0) {
        filterResult = -filterResult;
    }

    filterResult = (filterResult < deadbandThreshold);

    if (filterResult) {
        g_Camera.unk_0xA8.m_Offset.radius = 0;

        if (g_Camera.unk_0xCC != 0) {
            if (inputDelta > 0) {
                g_Camera.unk_0xA8.m_Offset.radius = 0x100;
            } else if (inputDelta < 0) {
                g_Camera.unk_0xA8.m_Offset.radius = -0x100;
            }
        }
    }

    // Accumulate the filtered offset radius.
    g_Camera.m_Sphere.m_Offset.radius +=
        g_Camera.unk_0xA8.m_Offset.radius >> 8;
}

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

// Camera state update for all other states
void func_80035FB4(void) {
    Vector3D relativePosition1;
    Vector3D velocityAdjustedPosition1;
    Vector3D relativePosition2;
    int padArray1[4]; /* Padding placeholder for target stack-layout matching. */
    Vector3D velocityAdjustedPosition2;
    int padArray2[8]; /* Padding placeholder for target stack-layout matching. */
    int step;
    int angleA;
    int angleB;
    int i;

    /*
     * Reset state 15 when camera control is active or the
     * camera-centering skip condition is enabled.
     */
    if ((D_80075914 & 0x10) != 0 || D_8007592C != 0) {
        if (g_Camera.m_State == 15) {
            g_Camera.m_State = 0;
        }
    }

    /*
     * Derive the camera update step from Spyro's off-center
     * frame count, limiting the initial value to 4.
     */
    step = (g_Camera.m_SpyroOffCenterFrames + 1) >> 1;

    if (step >= 5) {
        step = 4;
    }

    /*
     * Main camera-state dispatcher.
     *
     * Keep the state signed for matching switch lowering.
     * The high-bit camera states must retain their target
     * dispatch behavior.
     */
    switch ((int)g_Camera.m_State) {
    case 0:
    case 0x80000000: {
        int rotZAdjusted;

        /*
         * Set up the camera's focus and spherical preset when
         * the current camera-control conditions allow it.
         */
        if ((D_80075914 & 0x10) == 0 ||
            g_Camera.m_OnMovingPlatform != 0 ||
            D_80075924 != 0 ||
            g_Camera.unk_0xC4 != 0 ||
            (D_80075894 == 0 && g_Spyro.m_State != 0x1B)) {
            g_Camera.m_SphericalPreset = &D_8006C8D4;
            g_Camera.m_FocusRotation =
                g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;
            g_Camera.m_Focus = &g_Spyro.m_Position;

            g_Camera.unk_0xE8 =
                func_80033F08(&g_Camera.m_Position);

            g_Camera.m_Sphere.m_Coords.azimuth =
                g_Camera.m_Simulation.m_Coords.azimuth;

            if (g_Camera.unk_0xC4 == 0 || g_GameTick < 0x78) {
                ApplySphericalPreset();
            }
        }

        /*
         * Maintain the camera's automatic recentering timer.
         *
         * Continue normally only when none of the reset conditions
         * are active. The reset assignment is shared in the else branch.
         */
        if (((D_80075914 & 0x10) != 0 || D_8007592C != 0) &&
            g_Pad.m_NoButtonsDown != 0 &&
            D_800756B8 != 0 &&
            g_Camera.m_OnMovingPlatform == 0) {
            if (D_80075894 == 0) {
                break;
            }

            /*
             * Compare the camera's simulated orientation with
             * Spyro's orientation and the reference elevation.
             */
            rotZAdjusted =
                g_Spyro.m_Physics.m_SpeedAngle.m_RotZ - 0x800;

            angleA =
                (g_Camera.m_Simulation.m_Coords.azimuth +
                 rotZAdjusted) & 0xFFF;

            if (angleA >= 0x801) {
                angleA -= 0x1000;
            }

            angleB =
                (g_Camera.m_Simulation.m_Coords.elevation -
                 D_8006C8D8) & 0xFFF;

            if (angleB >= 0x801) {
                angleB -= 0x1000;
            }

            /*
             * Keep the timer while both angular differences remain
             * inside their respective thresholds.
             */
            if (ABS(angleA) < 0x191 && ABS(angleB) < 0x101) {
                break;
            }

            D_80075894 -= g_DeltaTime;

            if (D_80075894 > 0) {
                break;
            }

            D_80075894 = 0;

            g_Camera.unk_0xA8.m_Coords.azimuth = 0;
            g_Camera.unk_0xA8.m_Coords.elevation = 0;
            g_Camera.unk_0xA8.m_Coords.radius = 0;

            g_Camera.unk_0xA8.m_Offset.azimuth = 0;
            g_Camera.unk_0xA8.m_Offset.elevation = 0;
            g_Camera.unk_0xA8.m_Offset.radius = 0;
        } else {
            D_80075894 = 0x5A;
        }

        break;
    }

    case 0x80000010:
        g_Camera.m_SphericalPreset = &D_8006C8D4;
        g_Camera.m_FocusRotation =
            g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;
        g_Camera.m_Focus = &g_Spyro.m_Position;

        g_Camera.unk_0xE8 =
            func_80033F08(&g_Camera.m_Position);

        g_Camera.m_Sphere.m_Coords.azimuth =
            g_Camera.m_Simulation.m_Coords.azimuth;

        if (g_Camera.unk_0xC4 == 0) {
            ApplySphericalPreset();
        }

        /* Fall through: state 0x80000011 shares this tail. */

    case 0x80000011:
        D_80075938--;
        break;

    case 1: {
        g_Camera.m_Focus = &g_Spyro.m_Position;
        g_Camera.m_FocusRotation =
            g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;

        if (g_Camera.unk_0xC4 != 0) {
            break;
        }

        if (func_80017928(
                g_Spyro.m_Physics.m_SpeedAngle.m_RotZ,
                g_Camera.m_Rotation.z
            ) >= 0x579) {
            g_Camera.m_SphericalPreset = &D_8006C964;
        } else {
            g_Camera.m_SphericalPreset = &D_8006C934;

            if ((D_80075914 & 0x40) == 0) {
                g_Camera.unk_0xE8 =
                    func_80033F08(&g_Camera.m_Position);

                g_Camera.m_Sphere.m_Coords.azimuth =
                    g_Camera.m_Simulation.m_Coords.azimuth;
            }
        }

        ApplySphericalPreset();

        VecSub(
            &relativePosition1,
            &g_Spyro.m_Position,
            &g_Camera.m_Position
        );

        VecMult(
            &velocityAdjustedPosition1,
            &g_Spyro.m_Physics.m_TrueVelocity,
            D_8007527C
        );

        VecShiftRight(&velocityAdjustedPosition1, 6);

        VecAdd(
            &velocityAdjustedPosition1,
            &relativePosition1,
            &velocityAdjustedPosition1
        );

        g_Camera.m_LastSimulation.m_Offset.radius =
            (Atan2(
                 relativePosition1.x,
                 relativePosition1.y,
                 1
             ) -
             Atan2(
                 velocityAdjustedPosition1.x,
                 velocityAdjustedPosition1.y,
                 1
             )) & 0xFFF;

        break;
    }

    case 3: {
        g_Camera.m_SphericalPreset = &D_8006C994;
        g_Camera.m_Focus = &g_Spyro.m_Position;
        g_Camera.m_FocusRotation =
            g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;

        g_Camera.unk_0xE8 =
            func_80033F08(&g_Camera.m_Position);

        g_Camera.m_Sphere.m_Coords.azimuth =
            g_Camera.m_Simulation.m_Coords.azimuth;

        if (g_Camera.unk_0xC4 != 0) {
            g_Camera.unk_0xE8 =
                func_80033F08(&g_Camera.m_Position);
            g_Camera.m_Sphere = g_Camera.m_Simulation;
            break;
        }

        ApplySphericalPreset();

        g_Camera.m_LastSimulation.m_Offset.radius =
            ((-g_Spyro.m_Physics.m_TurnMomentum) << 3) & 0xFFF;

        break;
    }

    case 5: {
        g_Camera.m_Focus = &g_Spyro.m_Position;
        g_Camera.m_FocusRotation =
            g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;

        if (g_Camera.unk_0xC4 == 0) {
            if (g_Spyro.m_flyingAbility != 0) {
                if (g_Spyro.m_walkingState == 2) {
                    angleA =
                        (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ -
                         g_Camera.m_Rotation.z) & 0xFFF;

                    if (angleA >= 0x801) {
                        angleA -= 0x1000;
                    }

                    if (angleA > 0) {
                        g_Camera.m_SphericalPreset = &D_8006C94C;
                    } else {
                        g_Camera.m_SphericalPreset = &D_8006C97C;
                    }

                    g_Camera.m_FocusRotation =
                        (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ +
                         0x800) & 0xFFF;

                    g_Camera.unk_0xE8 =
                        func_80033F08(&g_Camera.m_Position);

                    g_Camera.m_Sphere.m_Coords.azimuth =
                        g_Camera.m_Simulation.m_Coords.azimuth;

                    ApplySphericalPreset();
                    break;
                } else {
                    if (g_Spyro.m_walkingState == 1) {
                        angleA =
                            (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ -
                             g_Camera.m_Rotation.z) & 0xFFF;

                        if (angleA >= 0x801) {
                            angleA -= 0x1000;
                        }

                        if (angleA >= 0x101) {
                            g_Camera.m_SphericalPreset = &D_8006C94C;
                        } else if (angleA < -0x100) {
                            g_Camera.m_SphericalPreset = &D_8006C97C;
                        } else {
                            g_Camera.m_SphericalPreset = &D_8006C934;
                        }

                        g_Camera.unk_0xE8 =
                            func_80033F08(&g_Camera.m_Position);

                        g_Camera.m_Sphere.m_Coords.azimuth =
                            g_Camera.m_Simulation.m_Coords.azimuth;
                    } else {
                        g_Camera.m_SphericalPreset = &D_8006C934;

                        g_Camera.unk_0xE8 =
                            func_80033F08(&g_Camera.m_Position);

                        g_Camera.m_Sphere.m_Coords.azimuth =
                            g_Camera.m_Simulation.m_Coords.azimuth;

                        g_Camera.m_Sphere.m_Coords.elevation =
                            g_Camera.m_Simulation.m_Coords.elevation;

                        ApplySphericalPreset();

                        VecSub(
                            &relativePosition2,
                            &g_Spyro.m_Position,
                            &g_Camera.m_Position
                        );

                        VecMult(
                            &velocityAdjustedPosition2,
                            &g_Spyro.m_Physics.m_TrueVelocity,
                            D_8007527C
                        );

                        VecShiftRight(&velocityAdjustedPosition2, 5);

                        VecAdd(
                            &velocityAdjustedPosition2,
                            &relativePosition2,
                            &velocityAdjustedPosition2
                        );

                        g_Camera.m_LastSimulation.m_Offset.radius =
                            (Atan2(
                                 relativePosition2.x,
                                 relativePosition2.y,
                                 1
                             ) -
                             Atan2(
                                 velocityAdjustedPosition2.x,
                                 velocityAdjustedPosition2.y,
                                 1
                             )) & 0xFFF;
                    }
                }
            } else {
                angleA =
                    func_80017928(
                        g_Spyro.m_Physics.m_SpeedAngle.m_RotZ,
                        g_Camera.m_Rotation.z
                    );

                if ((g_Spyro.m_walkingState != 0xB) &&
                    (angleA >= 0x579)) {
                    g_Camera.m_SphericalPreset = &D_8006C964;
                } else {
                    g_Camera.m_SphericalPreset = &D_8006C934;

                    g_Camera.unk_0xE8 =
                        func_80033F08(&g_Camera.m_Position);

                    g_Camera.m_Sphere.m_Coords.azimuth =
                        g_Camera.m_Simulation.m_Coords.azimuth;

                    g_Camera.m_Sphere.m_Coords.elevation =
                        g_Camera.m_Simulation.m_Coords.elevation;
                }

                ApplySphericalPreset();

                VecSub(
                    &relativePosition2,
                    &g_Spyro.m_Position,
                    &g_Camera.m_Position
                );

                VecMult(
                    &velocityAdjustedPosition2,
                    &g_Spyro.m_Physics.m_TrueVelocity,
                    D_8007527C
                );

                VecShiftRight(&velocityAdjustedPosition2, 5);

                VecAdd(
                    &velocityAdjustedPosition2,
                    &relativePosition2,
                    &velocityAdjustedPosition2
                );

                g_Camera.m_LastSimulation.m_Offset.radius =
                    (Atan2(
                         relativePosition2.x,
                         relativePosition2.y,
                         1
                     ) -
                     Atan2(
                         velocityAdjustedPosition2.x,
                         velocityAdjustedPosition2.y,
                         1
                     )) & 0xFFF;
            }

            break;
        } else {
            /*
             * Special path when the camera's unk_0xC4 flag is set.
             * Kept after the normal path to encourage tail merging.
             */
            g_Camera.unk_0xE8 =
                func_80033F08(&g_Camera.m_Position);
            g_Camera.m_Sphere = g_Camera.m_Simulation;
        }

        break;
    }

    case 6: {
        int j;
        int offsetMagnitude;

        if (g_Camera.m_Focus != &D_80077798) {
            VecCopy(&D_80077798, g_Camera.m_Focus);
            g_Camera.m_Focus = &D_80077798;
        }

        D_80075924 = 0;

        offsetMagnitude =
            ABS(g_Camera.unk_0xA8.m_Coords.azimuth) +
            ABS(g_Camera.unk_0xA8.m_Coords.elevation) +
            ABS(g_Camera.unk_0xA8.m_Coords.radius) +
            ABS(g_Camera.unk_0xA8.m_Offset.azimuth) +
            ABS(g_Camera.unk_0xA8.m_Offset.elevation) +
            ABS(g_Camera.unk_0xA8.m_Offset.radius);

        if (offsetMagnitude >= 0x21) {
            for (j = 0; j < g_DeltaTime; j++) {
                func_80034CE8(0);
            }

            func_80034204(&g_Camera.m_DestinationPosition);

            VecAdd(
                &g_Camera.m_DestinationPosition,
                &g_Camera.m_DestinationPosition,
                g_Camera.m_Focus
            );

            CameraForceToDestination();
            func_800342F8();
        }

        g_Camera.unk_0xE8 =
            func_80033F08(&g_Camera.m_Position);

        g_Camera.m_Sphere.m_Coords.azimuth =
            g_Camera.m_Simulation.m_Coords.azimuth;
        g_Camera.m_Sphere.m_Coords.elevation =
            g_Camera.m_Simulation.m_Coords.elevation;
        g_Camera.m_Sphere.m_Coords.radius =
            g_Camera.m_Simulation.m_Coords.radius;

        g_Camera.m_Sphere.m_Offset.azimuth =
            g_Camera.m_Simulation.m_Offset.azimuth;
        g_Camera.m_Sphere.m_Offset.elevation =
            g_Camera.m_Simulation.m_Offset.elevation;
        g_Camera.m_Sphere.m_Offset.radius =
            g_Camera.m_Simulation.m_Offset.radius;

        return;
    }

    case 4: {
        g_Camera.m_Focus = &g_Spyro.m_Position;
        g_Camera.m_FocusRotation =
            g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;

        if (g_Camera.unk_0xC4 == 0) {
            if (func_80017928(
                    g_Spyro.m_Physics.m_SpeedAngle.m_RotZ,
                    g_Camera.m_Rotation.z
                ) >= 0x579) {
                g_Camera.m_SphericalPreset = &D_8006C9DC;
                ApplySphericalPreset();
                break;
            } else {
                g_Camera.m_SphericalPreset = &D_8006C9AC;

                if ((D_80075914 & 0x40) == 0) {
                    g_Camera.unk_0xE8 =
                        func_80033F08(&g_Camera.m_Position);

                    g_Camera.m_Sphere.m_Coords.azimuth =
                        g_Camera.m_Simulation.m_Coords.azimuth;
                }
            }

            ApplySphericalPreset();
            break;
        } else {
            g_Camera.unk_0xE8 =
                func_80033F08(&g_Camera.m_Position);
            g_Camera.m_Sphere = g_Camera.m_Simulation;
        }

        break;
    }

    case 0x80000009: {
        int headLookAngle;

        g_Camera.m_SphericalPreset = &D_8006CA0C;
        g_Camera.m_Focus = &g_Spyro.m_Position;
        g_Camera.m_FocusRotation =
            g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;

        g_Camera.unk_0xE8 =
            func_80033F08(&g_Camera.m_Position);

        g_Camera.m_Sphere.m_Coords.azimuth =
            g_Camera.m_Simulation.m_Coords.azimuth;
        g_Camera.m_Sphere.m_Coords.elevation =
            g_Camera.m_Simulation.m_Coords.elevation;
        g_Camera.m_Sphere.m_Coords.radius =
            g_Camera.m_Simulation.m_Coords.radius;

        if (g_Camera.unk_0xC4 != 0) {
            step = 5;
            break;
        }

        ApplySphericalPreset();

        /*
         * If the active controller is an analogue stick controller
         * and its left stick is not centred, use the stick axes.
         */
        if (g_ActivePad->m_Down == 3 &&
            ((*(int *)(&g_ActivePad->m_Sticks) & 0xFFFF0000) !=
             0x7F7F0000)) {
            g_Camera.unk_0xDC +=
                (g_ActivePad->m_Sticks.m_LeftX - 0x7F) >> 1;
            g_Camera.unk_0xE0 +=
                (0x7F - g_ActivePad->m_Sticks.m_LeftY) >> 1;
        } else {
            if ((g_Pad.m_Held & PAD_LEFT) != 0) {
                g_Camera.unk_0xDC -= 0x30;
            } else if ((g_Pad.m_Held & PAD_RIGHT) != 0) {
                g_Camera.unk_0xDC += 0x30;
            }

            if ((g_Pad.m_Held & PAD_UP) != 0) {
                g_Camera.unk_0xE0 += 0x30;
            } else if ((g_Pad.m_Held & PAD_DOWN) != 0) {
                g_Camera.unk_0xE0 -= 0x30;
            }
        }

        /* Clamp the camera's two input offsets. */
        if (g_Camera.unk_0xDC < -0x400) {
            g_Camera.unk_0xDC = -0x400;
        }
        if (g_Camera.unk_0xDC > 0x400) {
            g_Camera.unk_0xDC = 0x400;
        }

        if (g_Camera.unk_0xE0 < -0x3D0) {
            g_Camera.unk_0xE0 = -0x3D0;
        }
        if (g_Camera.unk_0xE0 > 0x500) {
            g_Camera.unk_0xE0 = 0x500;
        }

        /*
         * Apply the offsets to the last simulation coordinates.
         */
        g_Camera.m_LastSimulation.m_Coords.azimuth +=
            g_Camera.unk_0xDC;

        if (g_Camera.unk_0xE0 < -0x140) {
            g_Camera.m_LastSimulation.m_Coords.elevation -= 0x140;

            g_Camera.m_LastSimulation.m_Offset.elevation +=
                0x140 + g_Camera.unk_0xE0;
        } else {
            g_Camera.m_LastSimulation.m_Coords.elevation +=
                g_Camera.unk_0xE0;
        }

        /*
         * Clamp the head-look target derived from the camera offsets.
         */
        headLookAngle = -g_Camera.unk_0xDC;

        if (headLookAngle < -0x300) {
            headLookAngle = -0x300;
        }
        if (headLookAngle > 0x300) {
            headLookAngle = 0x300;
        }

        g_Spyro.m_HeadLookTarget.z = headLookAngle;

        headLookAngle = -g_Camera.unk_0xE0;

        if (headLookAngle < -0x200) {
            headLookAngle = -0x200;
        }
        if (headLookAngle > 0x200) {
            headLookAngle = 0x200;
        }

        g_Spyro.m_HeadLookTarget.y = headLookAngle;
        step = 5;
        break;
    }

    case 2: {
        g_Camera.m_Focus = &g_Spyro.m_Position;
        g_Camera.m_FocusRotation =
            g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;

        if (g_Camera.unk_0xC4 == 0) {
            if (func_80017928(
                    g_Spyro.m_Physics.m_SpeedAngle.m_RotZ,
                    g_Camera.m_Rotation.z
                ) >= 0x579) {
                g_Camera.m_SphericalPreset = &D_8006C964;
            } else {
                g_Camera.m_SphericalPreset = &D_8006C934;
            }

            ApplySphericalPreset();
            break;
        } else {
            g_Camera.unk_0xE8 =
                func_80033F08(&g_Camera.m_Position);
            g_Camera.m_Sphere = g_Camera.m_Simulation;
            break;
        }
    }

    case 0x80000007: {
        Moby *moby;

        g_Camera.m_SphericalPreset = &D_8006CB5C;
        g_Camera.m_Focus = &D_80076ED0;
        moby = g_Spyro.m_mobyInUseBySpyro;

        D_80076ED0.x = moby->m_Position.x;
        D_80076ED0.y = moby->m_Position.y;
        D_80076ED0.z = g_Spyro.m_Position.z;

        g_Camera.m_FocusRotation = moby->m_Rotation.z << 4;

        g_Camera.unk_0xE8 =
            func_80033F08(&g_Camera.m_Position);

        g_Camera.m_Sphere.m_Coords.azimuth =
            g_Camera.m_Simulation.m_Coords.azimuth;
        g_Camera.m_Sphere.m_Coords.elevation =
            g_Camera.m_Simulation.m_Coords.elevation;
        g_Camera.m_Sphere.m_Coords.radius =
            g_Camera.m_Simulation.m_Coords.radius;

        ApplySphericalPreset();
        break;
    }

    case 0x8000000C: {
        Moby *moby;

        g_Camera.m_Focus = &g_Spyro.m_Position;
        moby = g_Spyro.m_mobyInUseBySpyro;

        g_Camera.m_FocusRotation =
            Atan2(
                moby->m_Position.x - g_Spyro.m_Position.x,
                moby->m_Position.y - g_Spyro.m_Position.y,
                1
            );

        if (g_Camera.unk_0xC4 != 0) {
            break;
        }

        g_Camera.m_SphericalPreset = &D_8006CB74;
        g_Camera.unk_0xE8 =
            func_80033F08(&g_Camera.m_Position);

        ApplySphericalPreset();
        break;
    }

    case 0x8000000A: {
        g_Camera.unk_0xE8 =
            func_80033F08(&g_Camera.m_Position);

        g_Camera.m_Sphere.m_Coords.azimuth =
            g_Camera.m_Simulation.m_Coords.azimuth;
        g_Camera.m_Sphere.m_Coords.elevation =
            g_Camera.m_Simulation.m_Coords.elevation;
        g_Camera.m_Sphere.m_Coords.radius =
            g_Camera.m_Simulation.m_Coords.radius;

        if (g_Camera.unk_0xC4 == 0) {
            ApplySphericalPreset();
        } else {
            g_Camera.unk_0xE8 =
                func_80033F08(&g_Camera.m_Position);
            g_Camera.m_Sphere = g_Camera.m_Simulation;
        }

        if ((g_Spyro.m_ControlFlags & 0x1000) == 0) {
            break;
        }

        step = 5;
        break;
    }

    case 15: {
        g_Camera.m_SphericalPreset = &D_8006C8D4;
        g_Camera.m_Focus = &g_Spyro.m_Position;
        g_Camera.m_FocusRotation =
            g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;

        g_Camera.unk_0xE8 =
            func_80033F08(&g_Camera.m_Position);

        g_Camera.m_Sphere.m_Coords.azimuth =
            g_Camera.m_Simulation.m_Coords.azimuth;
        g_Camera.m_Sphere.m_Coords.radius =
            g_Camera.m_Simulation.m_Coords.radius;

        if (g_Camera.unk_0xC4 == 0) {
            ApplySphericalPreset();
            break;
        }

        g_Camera.unk_0xE8 =
            func_80033F08(&g_Camera.m_Position);
        g_Camera.m_Sphere = g_Camera.m_Simulation;
        break;
    }

    default:
        break;
    }

    /*
     * Some camera states bypass the ordinary rotation-speed update.
     */
    if (g_Camera.m_State != 0x80000009 &&
        g_Camera.m_State != 0x80000007 &&
        g_Camera.m_State != 0x80000012 &&
        g_Camera.m_State != 0x8000000B &&
        g_Camera.m_State != 0x8000000E &&
        g_Camera.m_State != 3) {
        func_80035F58();
    } else {
        D_80075924 = 0;
    }

    /*
     * Either force the destination to the current camera position
     * and clear the smoothing offsets, or advance camera smoothing.
     */
    if (((D_80075914 & 0x10) != 0 || D_8007592C != 0) &&
        D_800756B8 != 0 &&
        D_80075894 != 0 &&
        g_Camera.m_OnMovingPlatform == 0 &&
        D_80075924 == 0 &&
        (g_Camera.m_State == 0 ||
         g_Camera.m_State == (int)0x80000000u)) {
        VecCopy(
            &g_Camera.m_DestinationPosition,
            &g_Camera.m_Position
        );

        g_Camera.unk_0xA8.m_Coords.azimuth = 0;
        g_Camera.unk_0xA8.m_Coords.elevation = 0;
        g_Camera.unk_0xA8.m_Coords.radius = 0;

        g_Camera.unk_0xA8.m_Offset.azimuth = 0;
        g_Camera.unk_0xA8.m_Offset.elevation = 0;
        g_Camera.unk_0xA8.m_Offset.radius = 0;
    } else {
        for (i = 0; i < g_DeltaTime; i++) {
            func_80034CE8(step);
        }

        func_80034204(&g_Camera.m_DestinationPosition);

        VecAdd(
            &g_Camera.m_DestinationPosition,
            &g_Camera.m_DestinationPosition,
            g_Camera.m_Focus
        );

        func_80034480();
        func_800342F8();
    }

    /*
     * Recalculate the camera's spherical position.
     */
    g_Camera.unk_0xE8 =
        func_80033F08(&g_Camera.m_Position);

    /*
     * In one specific movement state, retain the existing sphere
     * azimuth when Spyro's speed is below 0x400.
     */
    if ((D_80075914 & 0x10) == 0 ||
        g_Spyro.m_State != 5 ||
        g_Camera.m_OnMovingPlatform != 0 ||
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed >= 0x400) {
        g_Camera.m_Sphere.m_Coords.azimuth =
            g_Camera.m_Simulation.m_Coords.azimuth;
    }

    /*
     * The remaining five spherical values are copied unconditionally.
     */
    g_Camera.m_Sphere.m_Coords.elevation =
        g_Camera.m_Simulation.m_Coords.elevation;
    g_Camera.m_Sphere.m_Coords.radius =
        g_Camera.m_Simulation.m_Coords.radius;
    g_Camera.m_Sphere.m_Offset.azimuth =
        g_Camera.m_Simulation.m_Offset.azimuth;
    g_Camera.m_Sphere.m_Offset.elevation =
        g_Camera.m_Simulation.m_Offset.elevation;
    g_Camera.m_Sphere.m_Offset.radius =
        g_Camera.m_Simulation.m_Offset.radius;
}

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
