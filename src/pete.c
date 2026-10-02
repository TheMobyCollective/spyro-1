#include "camera.h"
#include "collision.h"
#include "common.h"
#include "environment.h"
#include "gamepad.h"
#include "gamestates/init.h"
#include "loaders.h"
#include "math.h"
#include "memory.h"
#include "overlay_pointers.h"
#include "special_surfaces.h"
#include "spu.h"
#include "spyro.h"
#include "variables.h"
#include "vector.h"

#include "rand.h"

extern struct {
  u_char m_StartFrame, m_EndFrame;
  u_char m_TransitionLastFrame, m_FrameRate;
} spyro_AnimationDetails[46]; // Frame details for animations

extern u_char spyro_StateDefaultAnimation[48]; // State to animation
extern u_char
    spyro_FlameBlockedInAnimation[48]; // Is flaming blocked in this animation
extern u_char D_8006BC84[45][45];      // Transition types

// Contains states { 18, 36, 37, 38, 39, 40, 41, 42, 43 }
// Which translates to the animations
// { 19, 37, 38, 39, 40, 41, 42, 43, 44 }

extern int D_8006BC60[9];      // Idle animation states table
extern int D_80075970;         // Idle animation index
extern short D_8006C5F0[][13]; // Turn rate lookup table

// Part of this file (gp_rel)
Moby *D_80075804;
int D_800756B4;   // Set to 1 when launching out of state 29 (used by the camera)
// Camera spring seeds written when grabbing the portal (state 17)
int D_80075724;
int D_80075668;
int D_8007578C;
int D_800757F0;
Moby *D_80075790; // The moby Spyro has locked onto for the charge sweep (state 11)

/* The toolchain headers used here do not define NULL. */
#ifndef NULL
#define NULL 0
#endif

// Spyro g_Spyro;

/// @brief Increments the body animation
/// @param pDeltaTime The delta time
void func_8003CB24(int pDeltaTime) {
  g_Spyro.m_bodyFrameProgress += pDeltaTime;

  if (g_Spyro.m_bodyFrameProgress >= 16) {
    g_Spyro.m_bodyFrameProgress -= 16;

    g_Spyro.m_bodyAnimation = g_Spyro.m_nextBodyAnimation;
    g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;

    g_Spyro.m_nextBodyAnimationFrame++;

    if (spyro_AnimationDetails[g_Spyro.m_nextBodyAnimation].m_EndFrame <=
        g_Spyro.m_nextBodyAnimationFrame) {
      g_Spyro.m_nextBodyAnimationFrame =
          spyro_AnimationDetails[g_Spyro.m_nextBodyAnimation].m_StartFrame;
    }
  }
}

// / @brief Increments the body animation and handles state transitions
int func_8003CBB8(int pDeltaTime) {
  g_Spyro.m_bodyFrameProgress += pDeltaTime;

  if (g_Spyro.m_bodyFrameProgress >= 16) {
    g_Spyro.m_bodyFrameProgress -= 16;

    g_Spyro.m_bodyAnimation = g_Spyro.m_nextBodyAnimation;
    g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;

    g_Spyro.m_nextBodyAnimationFrame++;

    if (spyro_AnimationDetails[g_Spyro.m_nextBodyAnimation]
            .m_TransitionLastFrame <= g_Spyro.m_nextBodyAnimationFrame) {
      g_Spyro.m_nextBodyAnimation =
          spyro_StateDefaultAnimation[g_Spyro.m_State];

      if (D_8006BC84[g_Spyro.m_lastAnimationState][g_Spyro.m_State] == 10) {
        g_Spyro.m_nextBodyAnimationFrame =
            spyro_AnimationDetails[spyro_StateDefaultAnimation[g_Spyro.m_State]]
                .m_StartFrame;
      } else {
        g_Spyro.m_nextBodyAnimationFrame = 1;
        g_Spyro.m_bodyFrameProgress = 4;
      }
      g_Spyro.m_lastAnimationState = g_Spyro.m_State;
      return 1;
    }
  }

  return 0;
}

/// @brief Handles the state transition for Spyro's body animation
void func_8003CCE4(void) {
  switch (D_8006BC84[g_Spyro.m_lastAnimationState][g_Spyro.m_State]) {
  case 1:
    g_Spyro.m_bodyTransitionType = TRANSITION_SLOW_BLEND;
    g_Spyro.m_bodyAnimation = g_Spyro.m_nextBodyAnimation;
    g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;

    g_Spyro.m_nextBodyAnimation = spyro_StateDefaultAnimation[g_Spyro.m_State];
    g_Spyro.m_nextBodyAnimationFrame = 0;
    g_Spyro.m_bodyFrameProgress = 2;

    g_Spyro.m_lastAnimationState = g_Spyro.m_State;
    break;

  case 8:
    g_Spyro.m_bodyTransitionType = TRANSITION_FAST_FROM_ZERO;
    g_Spyro.m_bodyAnimation = g_Spyro.m_nextBodyAnimation;
    g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;

    g_Spyro.m_nextBodyAnimation = spyro_StateDefaultAnimation[g_Spyro.m_State];
    g_Spyro.m_nextBodyAnimationFrame = 0;
    g_Spyro.m_bodyFrameProgress = 4;

    g_Spyro.m_lastAnimationState = g_Spyro.m_State;
    break;

  case 2:
    if (g_Spyro.m_nextBodyAnimationFrame >=
        spyro_AnimationDetails[g_Spyro.m_nextBodyAnimation].m_EndFrame) {
      g_Spyro.m_bodyTransitionType = TRANSITION_SLOW_AT_END;
      g_Spyro.m_bodyAnimation = g_Spyro.m_nextBodyAnimation;
      g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;
      g_Spyro.m_nextBodyAnimationFrame =
          spyro_AnimationDetails[g_Spyro.m_nextBodyAnimation].m_StartFrame;
      g_Spyro.m_bodyFrameProgress = 2;
    } else {
      g_Spyro.m_bodyTransitionType = TRANSITION_NONE;
    }
    break;

  case 5:
    g_Spyro.m_bodyAnimation = g_Spyro.m_nextBodyAnimation;
    g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;

    g_Spyro.m_nextBodyAnimation = spyro_StateDefaultAnimation[g_Spyro.m_State];
    g_Spyro.m_nextBodyAnimationFrame++;

    if (g_Spyro.m_nextBodyAnimationFrame >=
        spyro_AnimationDetails[g_Spyro.m_nextBodyAnimation].m_EndFrame) {
      g_Spyro.m_nextBodyAnimationFrame =
          spyro_AnimationDetails[g_Spyro.m_nextBodyAnimation].m_StartFrame;
    }

    g_Spyro.m_bodyFrameProgress = 4;
    g_Spyro.m_bodyTransitionType = TRANSITION_FAST_BLEND;
    g_Spyro.m_lastAnimationState = g_Spyro.m_State;
    break;

  case 3:
  case 10:
    g_Spyro.m_bodyTransitionType = TRANSITION_SPECIAL;
    break;

  case 4:
    g_Spyro.m_bodyAnimation = g_Spyro.m_nextBodyAnimation;
    g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;

    if (g_Spyro.m_lastAnimationState == 6 && g_Spyro.unk_0x84 < 24) {
      g_Spyro.m_bodyTransitionType = TRANSITION_SLOW_BLEND;
      g_Spyro.m_nextBodyAnimation =
          spyro_StateDefaultAnimation[g_Spyro.m_State];
      g_Spyro.m_nextBodyAnimationFrame = 0;
      g_Spyro.m_bodyFrameProgress = 2;
      g_Spyro.m_lastAnimationState = g_Spyro.m_State;
    } else {
      g_Spyro.m_nextBodyAnimationFrame =
          spyro_AnimationDetails[g_Spyro.m_nextBodyAnimation].m_EndFrame;
      g_Spyro.m_bodyFrameProgress = 4;
      g_Spyro.m_bodyTransitionType = TRANSITION_HOLD_END;

      if (g_Spyro.m_lastAnimationState == 6) {
        D_8007584C = 0xA0;
        if (D_800757D0 < 0xF) {
          D_800757D0 = 0xF;
        }
      }
    }
    break;

  case 6:
    g_Spyro.m_bodyTransitionType = TRANSITION_SLOW_FROM_START;
    g_Spyro.m_bodyAnimation = g_Spyro.m_nextBodyAnimation;
    g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;

    g_Spyro.m_nextBodyAnimation = spyro_StateDefaultAnimation[g_Spyro.m_State];
    g_Spyro.m_nextBodyAnimationFrame =
        spyro_AnimationDetails[g_Spyro.m_nextBodyAnimation].m_StartFrame;
    g_Spyro.m_bodyFrameProgress = 2;

    g_Spyro.m_lastAnimationState = g_Spyro.m_State;
    break;

  case 7:
    g_Spyro.m_bodyAnimation = spyro_StateDefaultAnimation[g_Spyro.m_State];
    g_Spyro.m_bodyAnimationFrame = 0;

    g_Spyro.m_nextBodyAnimation = spyro_StateDefaultAnimation[g_Spyro.m_State];
    g_Spyro.m_nextBodyAnimationFrame = 1;

    g_Spyro.m_bodyFrameProgress = 0;
    g_Spyro.m_bodyTransitionType = TRANSITION_NONE;
    g_Spyro.m_lastAnimationState = g_Spyro.m_State;
    break;

  case 11:
    g_Spyro.m_bodyAnimation = spyro_StateDefaultAnimation[g_Spyro.m_State];
    g_Spyro.m_bodyAnimationFrame =
        spyro_AnimationDetails[g_Spyro.m_bodyAnimation].m_StartFrame;

    g_Spyro.m_nextBodyAnimation = spyro_StateDefaultAnimation[g_Spyro.m_State];
    g_Spyro.m_nextBodyAnimationFrame =
        spyro_AnimationDetails[g_Spyro.m_bodyAnimation].m_StartFrame + 1;

    g_Spyro.m_bodyFrameProgress = 0;
    g_Spyro.m_bodyTransitionType = TRANSITION_NONE;
    g_Spyro.m_lastAnimationState = g_Spyro.m_State;
    break;

  default:
    // There used to be a printf here (removed after July) that said:
    // printf("illegal animation transition from %d to %d\n",
    // g_Spyro.m_lastAnimationState, g_Spyro.m_State)
    return;
  }
}

/// @brief Handles Spyro's body animation state machine
void UpdateBodyAnimationState(void) {
  switch (g_Spyro.m_bodyTransitionType) {
  case TRANSITION_NONE:
    if (g_Spyro.m_State == g_Spyro.m_lastAnimationState) {
      func_8003CB24(g_Spyro.m_bodyAnimationSpeed);
    } else {
      func_8003CCE4();
    }
    break;

  case TRANSITION_SLOW_BLEND:
  case TRANSITION_SLOW_AT_END:
  case TRANSITION_SLOW_FROM_START:
    g_Spyro.m_bodyFrameProgress += 2;
    if (g_Spyro.m_bodyFrameProgress < 16)
      break;
    func_8003CB24(0);
    g_Spyro.m_bodyTransitionType = TRANSITION_NONE;
    break;

  case TRANSITION_FAST_BLEND:
    g_Spyro.m_bodyFrameProgress += 4;
    if (g_Spyro.m_bodyFrameProgress < 16)
      break;
    func_8003CB24(0);
    g_Spyro.m_bodyTransitionType = TRANSITION_NONE;
    break;

  case TRANSITION_FAST_FROM_ZERO:
    func_8003CB24(2);
    g_Spyro.m_bodyTransitionType = TRANSITION_NONE;
    break;

  case TRANSITION_SPECIAL:
  case TRANSITION_SPECIAL_ALT: {
    u_char transType =
        D_8006BC84[g_Spyro.m_lastAnimationState][g_Spyro.m_State];
    if (transType != 3 && transType != 10 && transType != 4) {
      func_8003CCE4();
      break;
    }
    if (func_8003CBB8(
            spyro_AnimationDetails[g_Spyro.m_bodyAnimation].m_FrameRate)) {
      if (g_Spyro.m_bodyAnimation == 0x1A) {
        PlaySound(g_Spu.m_SoundTable->spyroStars, (Moby *)&g_Spyro, 0x10,
                  nullptr);
      }
      g_Spyro.m_bodyTransitionType = TRANSITION_NONE;
    }
    break;
  }

  case TRANSITION_HOLD_END:
    g_Spyro.m_bodyFrameProgress += g_Spyro.m_bodyAnimationSpeed;
    if (g_Spyro.m_bodyFrameProgress < 16)
      break;
    g_Spyro.m_bodyFrameProgress = 0;
    g_Spyro.m_bodyTransitionType = TRANSITION_SPECIAL;
    g_Spyro.m_bodyAnimation = g_Spyro.m_nextBodyAnimation;
    g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;
    g_Spyro.m_nextBodyAnimationFrame++;
    break;
  }
}

extern short D_8006C5D0[16];

/// @brief Creates the target speed and angle based on the stick
void func_8003D3B8(int speed) {
  int sX, sY;

  if ((g_ActivePad->m_LeftStickMoved != 0) &&
      (g_ActivePad->m_Sticks.m_LeftX != 0x7F ||
       g_ActivePad->m_Sticks.m_LeftY != 0x7F)) {
    g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ =
        Atan2(0x7F - g_ActivePad->m_Sticks.m_LeftY,
              0x7F - g_ActivePad->m_Sticks.m_LeftX, 1);
    g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ =
        (g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ + g_Camera.m_Rotation.z) &
        0xFFF;
    sY = 0x7F - g_ActivePad->m_Sticks.m_LeftY;
    sY = ABS(sY);
    sX = 0x7F - g_ActivePad->m_Sticks.m_LeftX;
    sX = ABS(sX);
    g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed = speed * (sY + sX) >> 7;
    if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed > speed) {
      g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed = speed;
    }
  } else {
    if (g_ActivePad->m_Released & 0xF000) {
      g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed = speed;
      g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ =
          D_8006C5D0[(g_ActivePad->m_Released >> 12) & 15];
      g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ =
          (g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ +
           g_Camera.m_Rotation.z) &
          0xFFF;
    } else {
      g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed = 0;
      g_Spyro.m_Physics.m_TurnMomentum = 0;
      g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ =
          g_Spyro.m_bodyRotation.z * 0x10;
    }
  }
}

/// @brief Updates the body rotation based on the true rotation
void func_8003D52C(int pUnknown) {
  int cosX;
  int sinX;
  int cosY;
  int sinY;
  Vector3D tempVec;

  cosX = Cos(g_Spyro.m_Physics.m_SpeedAngle.m_RotX);
  sinX = Sin(g_Spyro.m_Physics.m_SpeedAngle.m_RotX);
  cosY = Cos(-g_Spyro.m_Physics.m_SpeedAngle.m_RotY & 0xfff);
  if (cosY == 0) {
    cosY = 1;
  }
  sinY = Sin(-g_Spyro.m_Physics.m_SpeedAngle.m_RotY & 0xfff);

  // There's writes to stack here haha
  tempVec.x = FIXED_MUL((pUnknown * sinY) / cosY, cosX);
  tempVec.z = ((pUnknown * cosX) / cosY);
  tempVec.y = FIXED_MUL(pUnknown, sinX);

  g_Spyro.m_Physics.m_SpeedAngle.m_RotX =
      (g_Spyro.m_Physics.m_SpeedAngle.m_RotX + tempVec.x) & 0xfff;
  g_Spyro.m_bodyRotation.x = (g_Spyro.m_Physics.m_SpeedAngle.m_RotX >> 4);

  g_Spyro.m_Physics.m_SpeedAngle.m_RotY =
      (g_Spyro.m_Physics.m_SpeedAngle.m_RotY + tempVec.y) & 0xfff;
  g_Spyro.m_bodyRotation.y = (g_Spyro.m_Physics.m_SpeedAngle.m_RotY >> 4);

  g_Spyro.m_Physics.m_SpeedAngle.m_RotZ =
      (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ + tempVec.z) & 0xfff;
  g_Spyro.m_bodyRotation.z = (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ >> 4);
}

/// @brief Updates Spyro's turn momentum and applies rotation based on angular
/// difference. Manages turn acceleration/deceleration using a lookup table
/// indexed by turn momentum
/// @param pTableIndex Index selecting which row of the turn rate table to use
int UpdateSpyroTurnMomentum(int pTableIndex) {
  int angleDiff;
  int threshold;

  // Calculate unsigned 12-bit angle difference (0-4095)
  angleDiff = g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ -
              g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;
  angleDiff &= 0xFFF;

  // Update turn momentum based on turn direction (-6 = hard left, +6 = hard
  // right)
  if (angleDiff < 2048) {
    // Turning right (positive direction)
    g_Spyro.m_Physics.m_TurnMomentum++;
    if (g_Spyro.m_Physics.m_TurnMomentum <= 0) {
      g_Spyro.m_Physics.m_TurnMomentum = 1; // Snap to positive if crossing zero
    }
    if (g_Spyro.m_Physics.m_TurnMomentum > 6) {
      g_Spyro.m_Physics.m_TurnMomentum = 6; // Clamp max
    }
  } else {
    // Turning left (negative direction)
    g_Spyro.m_Physics.m_TurnMomentum--;
    if (g_Spyro.m_Physics.m_TurnMomentum < -6) {
      g_Spyro.m_Physics.m_TurnMomentum = -6; // Clamp min
    }
    if (g_Spyro.m_Physics.m_TurnMomentum > -1) {
      // Snap to negative if crossing zero
      g_Spyro.m_Physics.m_TurnMomentum = -1;
    }
  }

  // Look up turn rate threshold from table (13 values per row, 26 bytes)
  // Index by momentum+6 converts range [-6,+6] to [0,12]
  threshold = D_8006C5F0[pTableIndex][g_Spyro.m_Physics.m_TurnMomentum + 6];

  if (angleDiff > threshold && angleDiff < threshold + 4096) {
    // Within threshold range - apply gradual turn using table value
    func_8003D52C(threshold); // Applies rotation delta to Spyro's Z angle
  } else {
    // Outside threshold - snap directly to target, reset momentum
    int rawAngleDiff;
    int turnAmount;
    rawAngleDiff = g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ -
                   g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;
    turnAmount = rawAngleDiff & 0xFFF;

    if (turnAmount >= 2049) {
      turnAmount -= 4096; // Convert to signed (-2048 to +2047)
    }

    g_Spyro.m_Physics.m_TurnMomentum = 0;
    func_8003D52C(turnAmount); // Applies rotation delta to Spyro's Z angle
  }

  // Calculate angular distance and return it (callers reuse it as the turn angle)
  return func_80017928(g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ,
                       g_Spyro.m_Physics.m_SpeedAngle.m_RotZ);
}

/**
 * @brief Pre-processes analog stick input for Spyro's turning ("soft turn").
 *
 * When the left stick is held gently (magnitude < 0x60), interpolates
 * m_TargetSpeedAngle toward m_SpeedAngle proportionally to stick magnitude,
 * producing smooth micro-adjustments instead of a full turn. Larger stick
 * deflections fall through to the normal momentum-based turn. Always
 * delegates the actual rotation to UpdateSpyroTurnMomentum() afterward.
 */
int ApplySpyroSoftTurn(void) {
  Vector3D stickVec;
  int magnitude;
  int diff;
  int absDiff;

  // Skip if the pad isn't reporting a moved stick, or if the stick is centered
  // (0x7F = neutral)
  if (g_ActivePad->m_LeftStickMoved != 0 &&
      (g_ActivePad->m_Sticks.m_LeftX != 0x7F ||
       g_ActivePad->m_Sticks.m_LeftY != 0x7F)) {
    // Build a 2D vector centered on the stick's neutral position (0x7F)
    stickVec.x = g_ActivePad->m_Sticks.m_LeftX - 0x7F;
    stickVec.y = g_ActivePad->m_Sticks.m_LeftY - 0x7F;
    stickVec.z = 0;

    magnitude = VecMagnitude(&stickVec, 0); // 2D magnitude of stick deflection

    // Only the soft-turn tier — full deflection goes through the momentum
    // system
    if (magnitude < 0x60) {
      // Signed angular delta in 12-bit space, wrapped to [-0x800, +0x7FF]
      diff = (g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ -
              g_Spyro.m_Physics.m_SpeedAngle.m_RotZ) &
             0xFFF;

      if (diff > 2048) {
        diff -= 4096;
      }

      // Big pending turn — flag the state machine so Spyro visibly reorients
      if (ABS2(diff) > 256) {
        g_Spyro.m_walkingState = 1;
      }

      // Pull target angle toward current by (magnitude / 512) of the delta
      g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ =
          (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ + ((magnitude * diff) >> 9)) &
          0xFFF;
    }
  }

  return UpdateSpyroTurnMomentum(0); // Apply rotation using row 0 (walking turn rate)
}

/// @brief Makes the movement speed approach the target speed
void func_8003D92C(int pAddSpeed, int pSubtractSpeed) {
  if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed >
      g_Spyro.m_Physics.m_SpeedAngle.m_Speed) {

    g_Spyro.m_Physics.m_SpeedAngle.m_Speed += pAddSpeed;
    if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed <
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed) {
      g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
          g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed;
    }
  } else {
    g_Spyro.m_Physics.m_SpeedAngle.m_Speed -= pSubtractSpeed;

    if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed <
        g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed) {
      g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
          g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed;
    }
  }
}

void func_8003D978(void) {
  MATRIX m;
  Vector3D8 t;

  t.x = g_Spyro.m_Physics.m_SpeedAngle.m_RotX >> 4;
  t.y = g_Spyro.m_Physics.m_SpeedAngle.m_RotY >> 4;
  t.z = g_Spyro.m_Physics.m_SpeedAngle.m_RotZ >> 4;

  RotVec8ToMatrix(&t, &m, nullptr);

  g_Spyro.m_Physics.m_Acceleration.x = g_Spyro.m_Physics.m_SpeedAngle.m_Speed;
  g_Spyro.m_Physics.m_Acceleration.y = 0;
  g_Spyro.m_Physics.m_Acceleration.z = 0;

  VecRotateByMatrix(&m, &g_Spyro.m_Physics.m_Acceleration,
                    &g_Spyro.m_Physics.m_Acceleration);
}

/// @brief Smoothly rotates Spyro's orientation back to neutral
/// Uses a spring-damper system via m_RotXAccumulator and m_RotYAccumulator
/// to gradually transition RotX and RotY toward zero
void RotateSpyroToNeutral(void) {
  Vector3D t; // Wtf is up with these temporaries?

  t.x = 0;
  t.y = 0;

  t.x = -g_Spyro.m_Physics.m_SpeedAngle.m_RotX & 0xfff;
  if (t.x > 0x7ff) {
    t.x -= 0x1000;
  }
  t.y = -g_Spyro.m_Physics.m_SpeedAngle.m_RotY & 0xfff;
  if (t.y > 0x7ff) {
    t.y -= 0x1000;
  }
  g_Spyro.m_RotXAccumulator +=
      ((t.x << 2) >> 4) - ((g_Spyro.m_RotXAccumulator << 4) >> 6);
  g_Spyro.m_RotYAccumulator +=
      ((t.y << 2) >> 4) - ((g_Spyro.m_RotYAccumulator << 4) >> 6);

  t.x = (g_Spyro.m_RotXAccumulator >> 2);
  t.y = (g_Spyro.m_RotYAccumulator >> 2);

  g_Spyro.m_Physics.m_SpeedAngle.m_RotX += t.x;
  g_Spyro.m_Physics.m_SpeedAngle.m_RotY += t.y;
}

void func_8003DAE4(void) {
  Vector3D t;
  Vector3D rot;

  if (g_Spyro.m_slopeAngle >= 23) {
    RotateSpyroToNeutral();
    return;
  }

  // I was hoping FIXED_MUL would match here, but sadly it doesn't
  t.x = (g_Spyro.m_floorPositonOnSlope.x *
             Cos(g_Spyro.m_Physics.m_SpeedAngle.m_RotZ) +
         g_Spyro.m_floorPositonOnSlope.y *
             Sin(g_Spyro.m_Physics.m_SpeedAngle.m_RotZ)) >>
        12;

  t.y = (g_Spyro.m_floorPositonOnSlope.y *
             Cos(g_Spyro.m_Physics.m_SpeedAngle.m_RotZ) -
         g_Spyro.m_floorPositonOnSlope.x *
             Sin(g_Spyro.m_Physics.m_SpeedAngle.m_RotZ)) >>
        12;

  t.z = g_Spyro.m_floorPositonOnSlope.z;

  rot.x = -Atan2(func_80017A38(t.x * t.x + t.z * t.z), t.y, 1);
  rot.y = -Atan2(t.z, t.x, 1);

  rot.x = (rot.x - g_Spyro.m_Physics.m_SpeedAngle.m_RotX) & 0xFFF;
  if (rot.x > 2048) {
    rot.x -= 4096;
  }

  rot.y = (rot.y - g_Spyro.m_Physics.m_SpeedAngle.m_RotY) & 0xFFF;
  if (rot.y > 2048) {
    rot.y -= 4096;
  }

  g_Spyro.m_RotXAccumulator +=
      ((rot.x << 2) >> 4) - ((g_Spyro.m_RotXAccumulator << 4) >> 6);
  g_Spyro.m_RotYAccumulator +=
      ((rot.y << 2) >> 4) - ((g_Spyro.m_RotYAccumulator << 4) >> 6);

  rot.x = g_Spyro.m_RotXAccumulator >> 2;
  rot.y = g_Spyro.m_RotYAccumulator >> 2;

  g_Spyro.m_Physics.m_SpeedAngle.m_RotX =
      (g_Spyro.m_Physics.m_SpeedAngle.m_RotX + rot.x) & 0xFFF;
  if (g_Spyro.m_Physics.m_SpeedAngle.m_RotX > 2048) {
    g_Spyro.m_Physics.m_SpeedAngle.m_RotX -= 4096;
  }

  g_Spyro.m_Physics.m_SpeedAngle.m_RotY =
      (g_Spyro.m_Physics.m_SpeedAngle.m_RotY + rot.y) & 0xFFF;
  if (g_Spyro.m_Physics.m_SpeedAngle.m_RotY > 2048) {
    g_Spyro.m_Physics.m_SpeedAngle.m_RotY -= 4096;
  }

  if (g_Spyro.m_bodyRotation.x >= 32 && g_Spyro.m_bodyRotation.x <= 224 ||
      g_Spyro.m_bodyRotation.y >= 32 && g_Spyro.m_bodyRotation.y <= 224) {
    return;
  }

  t.y = FIXED_MUL(-Sin(rot.x), 372);
  t.x = FIXED_MUL(-Sin(rot.y), 372);
  t.z = FIXED_MUL((8192 - Cos(rot.x) - Cos(rot.y)), 372);

  RotVec8ToMatrix(&g_Spyro.m_bodyRotation, &g_Spyro.m_RotationMatrix, nullptr);
  VecRotateByMatrix(&g_Spyro.m_RotationMatrix, &t, &t);
  VecAdd(&g_Spyro.m_Position, &g_Spyro.m_Position, &t);
}

/// @brief Smoothly rotates Spyro's orientation to align with his acceleration
/// Uses a spring-damper system via m_RotXAccumulator and m_RotYAccumulator.
/// RotX approaches 0 (neutral), RotY approaches the elevation angle derived
/// from acceleration magnitude and z-component (Atan2 + 0x8E offset)
void RotateSpyroToAcceleration(void) {
  Vector3D t;
  int rotX, rotY;
  int tx, ty;

  t.x = 0;
  t.z = VecMagnitude(&g_Spyro.m_Physics.m_Acceleration, 0);
  t.y = Atan2(t.z, g_Spyro.m_Physics.m_Acceleration.z, 1) + 0x8E;

  tx = t.x;
  rotX = g_Spyro.m_Physics.m_SpeedAngle.m_RotX;
  t.x = (tx - rotX) & 0xFFF;
  if (t.x > 0x7FF) {
    t.x -= 0x1000;
  }

  ty = t.y;
  rotY = g_Spyro.m_Physics.m_SpeedAngle.m_RotY;
  t.y = (ty - rotY) & 0xFFF;
  if (t.y > 0x7FF) {
    t.y -= 0x1000;
  }

  g_Spyro.m_RotXAccumulator +=
      ((t.x << 2) >> 4) - ((g_Spyro.m_RotXAccumulator << 4) >> 6);
  g_Spyro.m_RotYAccumulator +=
      ((t.y << 2) >> 4) - ((g_Spyro.m_RotYAccumulator << 4) >> 6);

  t.x = g_Spyro.m_RotXAccumulator >> 2;
  t.y = g_Spyro.m_RotYAccumulator >> 2;

  g_Spyro.m_Physics.m_SpeedAngle.m_RotX = rotX + t.x;
  g_Spyro.m_Physics.m_SpeedAngle.m_RotY = rotY + t.y;
}

/// Unused function
void func_8003DF60(void) {
  VecCopy(&g_Spyro.m_Position, &g_Spyro.m_previousPosition);
  VecNull(&g_Spyro.m_Physics.m_TrueVelocity);
  g_Spyro.m_Physics.m_TrueSpeed = 0;
}

void func_8003DFA4(void) {
  VecNull(&g_Spyro.m_Physics.m_TrueVelocity);
  g_Spyro.m_Physics.m_TrueSpeed = 0;
  VecNull(&g_Spyro.m_Physics.m_Acceleration);
  g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0;
}

/// @brief Smoothly turns Spyro's body to face his velocity direction
/// @param pMaxTurnSpeed Maximum turn amount per frame (8-bit angle units)
/// @param pDeadzone Minimum angle difference required before turning
void TurnBodyToVelocity(int pMaxTurnSpeed, int pDeadzone) {
  int currentAngle;
  int targetAngle;
  int angleDiff;

  angleDiff = (targetAngle = Atan2(g_Spyro.m_Physics.m_TrueVelocity.x,
                                   g_Spyro.m_Physics.m_TrueVelocity.y, 0)) -
              (currentAngle = g_Spyro.m_bodyRotation.z);

  angleDiff &= 0xFF;

  if (!(pDeadzone < angleDiff))
    return;

  if (!(angleDiff < 256 - pDeadzone))
    return;

  if (!(pMaxTurnSpeed < angleDiff) || !(angleDiff < 256 - pMaxTurnSpeed)) {
    g_Spyro.m_bodyRotation.z = targetAngle;
  } else if ((u_int)angleDiff < 0x80u) {
    g_Spyro.m_bodyRotation.z = currentAngle + pMaxTurnSpeed;
  } else {
    g_Spyro.m_bodyRotation.z = currentAngle - pMaxTurnSpeed;
  }

  g_Spyro.m_Physics.m_SpeedAngle.m_RotZ = g_Spyro.m_bodyRotation.z << 4;
}

/// @brief Applies slope-based gravity adjustment
/// Uses floor position on slope to calculate a gravity-scaled adjustment vector
void ApplySlopeGravity(void) {
  Vector3D tempVec;
  int magnitude;
  int scaledZ;

  VecCopy(&tempVec, &g_Spyro.m_floorPositonOnSlope);
  magnitude = VecMagnitude(&tempVec, 1);

  if (magnitude == 0) {
    return;
  }

  scaledZ = (g_Spyro.m_Physics.m_gravity * tempVec.z) / magnitude;
  VecScaleToLength(&tempVec, magnitude, scaledZ);

  // Negate vector if z > 0 (pointing upward)
  if (tempVec.z > 0) {
    tempVec.x = -tempVec.x;
    tempVec.y = -tempVec.y;
    tempVec.z = -tempVec.z;
  }

  // Zero out the target speed angle Y/X rotation and m_SlopeGravityZ
  // Then store gravity and subtract tempVec
  VecNull((Vector3D *)&g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotY);
  g_Spyro.m_Physics.m_SlopeGravityZ = g_Spyro.m_Physics.m_gravity;
  VecSub((Vector3D *)&g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotY,
         (Vector3D *)&g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotY, &tempVec);
}

void func_8003E1AC(void) {
  Vector3D nullVec;
  VecCopy(&g_Spyro.m_Physics.unk_0xdc, &g_Spyro.m_floorPositonOnSlope);
  func_80017330(&g_Spyro.m_Physics.unk_0xdc, ABS(g_Spyro.m_Physics.m_gravity));

  VecNull(&nullVec);

  VecSub(&g_Spyro.m_Physics.unk_0xdc, &nullVec, &g_Spyro.m_Physics.unk_0xdc);
}

/// @brief Checks if Spyro is against a wall
/// Casts a ray from front to back and checks the collision angle
void CheckWallCollision(void) {
  Vector3D vec1, vec2;
  int magnitude;
  int angle;

  vec1.z = -0x164;
  vec2.x = 0x1C4;
  vec1.y = 0;
  vec1.x = 0;
  vec2.y = 0;
  vec2.z = -0x1A4;

  VecRotateByMatrix(&g_Spyro.m_RotationMatrix, &vec1, &vec1);
  VecAdd(&vec1, &vec1, &g_Spyro.m_Position);

  VecRotateByLastMatrix(&vec2, &vec2);
  VecAdd(&vec2, &vec2, &g_Spyro.m_Position);

  if (func_8004AE38(&vec1, &vec2) == 0)
    return;

  magnitude = VecMagnitude(&g_CollisionNormal, 0);
  angle = Atan2(g_CollisionNormal.z, magnitude, 0);

  angle = (signed char)angle;

  if (angle < 0x17)
    return;

  g_Spyro.m_againstWall = 1;
  VecCopy(&g_Spyro.m_wallAgainstSpyro, &g_CollisionNormal);
}

/**
 * @brief Performs floor collision detection when Spyro is on a slope.
 *
 * This function casts rays from positions around Spyro to detect the floor
 * surface, calculates the floor angle from the collision normal, and updates
 * related state including the collision triangle for moving platform tracking.
 *
 * The function performs up to three collision checks:
 *
 * 1. **Primary check**: Casts a ray from a point forward of Spyro (rotated by
 *    his rotation matrix) down toward a point behind (world-space rotation).
 *    This detects the floor surface regardless of Spyro's facing direction.
 *
 * 2. **Reverse verification check**: If the primary check finds a walkable
 *    slope (angle < 0x21), performs a reverse check with offset vectors to
 *    verify the surface is truly walkable. If this fails, sets m_onEdge = 1
 *    to trigger edge behavior (e.g., teetering animation).
 *
 * 3. **Fallback axis-aligned check**: If m_airTime is non-zero and
 *    m_floorIdleTime is zero, performs a simpler vertical collision check
 *    without rotation transforms (useful when Spyro is stationary on a slope).
 *
 * Slope angle thresholds:
 * - < 0x17 (23): Gentle slope, m_onSlope = 0 (normal walking)
 * - 0x17-0x20: Moderate slope, m_onSlope = 1 (may slide)
 * - >= 0x21 (33): Steep slope, not considered walkable
 */
void UpdateSlopeFloorCollision(void) {
  Vector3D vec1, vec2;
  int magnitude;
  int angle;

  // Increment air time counter (reset to 0 when grounded)
  g_Spyro.m_airTime++;

  // Initialize floor position to default "pointing up" vector
  VecNull(&g_Spyro.m_floorPositonOnSlope);
  g_Spyro.m_floorPositonOnSlope.z = 0x1000;
  g_Spyro.m_slopeAngle = 0;
  g_Spyro.m_onEdge = 0;

  // Early exit if surface checks are disabled (e.g., during cutscenes)
  if (g_Spyro.m_ControlFlags & CTRL_SKIP_SURFACE_CHECK) {
    return;
  }

  // === PRIMARY COLLISION CHECK ===
  // Cast ray from slightly above Spyro's feet to below ground level
  // vec1: Start point (player-relative, rotated by body matrix)
  // vec2: End point (world-space rotation via GTE)
  vec1.x = 0;
  vec2.x = 0;
  vec1.y = 0;
  vec2.y = 0;
  vec1.z = -0x104; // 260 units below origin
  vec2.z = -0x1C4; // 452 units below origin

  // Rotate start point by Spyro's body rotation matrix
  VecRotateByMatrix(&g_Spyro.m_RotationMatrix, &vec1, &vec1);
  VecAdd(&vec1, &vec1, &g_Spyro.m_Position);

  // Rotate end point using GTE world-space rotation
  VecRotateByLastMatrix(&vec2, &vec2);
  VecAdd(&vec2, &vec2, &g_Spyro.m_Position);

  // Cast the ray and check for collision
  if (func_8004AE38(&vec1, &vec2) != 0) {
    // Collision found - extract floor normal from g_CollisionNormal
    VecCopy(&g_Spyro.m_floorPositonOnSlope, &g_CollisionNormal);

    // Calculate slope angle from floor normal
    // magnitude = horizontal component, z = vertical component
    magnitude = VecMagnitude(&g_CollisionNormal, 0);
    angle = Atan2(g_CollisionNormal.z, magnitude, 0);

    // Sign-extend angle to 8-bit signed value
    angle = (signed char)angle;
    g_Spyro.m_slopeAngle = angle;

    // Clamp negative angles (invalid floor normal) to max slope
    if (angle < 0) {
      g_Spyro.m_slopeAngle = 1024;
    }

    // Store collision triangle for moving platform tracking
    g_Spyro.m_CollisionTriangleIndex = g_CollisionTriangleIndex;
    ColTriUnpack(g_CollisionTriangleIndex,
                 g_Spyro.m_collisionTriangleUnpacked.points);

    // Check if slope is walkable (< 33 degrees)
    if (g_Spyro.m_slopeAngle < 33) {
      g_Spyro.m_onSlope = (g_Spyro.m_slopeAngle < 23) ^ 1;
      g_Spyro.m_airTime = 0;

      // === REVERSE VERIFICATION CHECK ===
      // Cast ray with offset to detect edges/cliffs behind Spyro
      vec1.x = 0x104; // Offset forward
      vec1.y = 0;
      vec1.z = -0x104;
      vec2.x = 0x1C4; // Larger offset forward
      vec2.y = 0;
      vec2.z = -0x1C4;

      VecRotateByMatrix(&g_Spyro.m_RotationMatrix, &vec1, &vec1);
      VecAdd(&vec1, &vec1, &g_Spyro.m_Position);

      VecRotateByLastMatrix(&vec2, &vec2);
      VecAdd(&vec2, &vec2, &g_Spyro.m_Position);

      // If reverse check fails, Spyro is on an edge
      if (func_8004AE38(&vec1, &vec2) == 0) {
        g_Spyro.m_onEdge = 1;
      }
    }
  } else {
    // No collision found - clear triangle index
    g_Spyro.m_CollisionTriangleIndex = -1;
  }

  // === FALLBACK VERTICAL CHECK ===
  // When airborne and not idle, try a simple vertical raycast
  // This catches cases where the rotated ray missed but floor exists
  if (g_Spyro.m_airTime != 0 && g_Spyro.m_floorIdleTime == 0) {
    // Axis-aligned vertical ray (no rotation)
    vec1.z = -0x104;
    vec1.x = 0;
    vec1.y = 0;
    vec2.x = 0;
    vec2.y = 0;
    vec2.z = -0x1C4;

    // Add position directly (no rotation transform)
    VecAdd(&vec1, &vec1, &g_Spyro.m_Position);
    VecAdd(&vec2, &vec2, &g_Spyro.m_Position);

    if (func_8004AE38(&vec1, &vec2) != 0) {
      // Collision found - recalculate slope from this hit
      VecCopy(&g_Spyro.m_floorPositonOnSlope, &g_CollisionNormal);
      magnitude = VecMagnitude(&g_Spyro.m_floorPositonOnSlope, 0);
      angle = Atan2(g_Spyro.m_floorPositonOnSlope.z, magnitude, 0);

      // Sign-extend to 8-bit signed
      angle = (signed char)angle;
      g_Spyro.m_slopeAngle = angle;

      // Clamp negative angles to max slope
      if (angle < 0) {
        g_Spyro.m_slopeAngle = 1024;
      }

      // If walkable, mark as grounded and set slope flag
      if (g_Spyro.m_slopeAngle < 33) {
        g_Spyro.m_airTime = 0;
        g_Spyro.m_onSlope = (g_Spyro.m_slopeAngle < 23) ^ 1;
      }
    }
  }
}

/// @brief Capture the movement on a moving platform
void func_8003E628(void) {
  Vector3D points[3];
  Vector3D pointSum;
  int i;

  if (g_Spyro.m_CollisionTriangleIndex < 0) // No collision
    return;

  VecNull(&pointSum);

  ColTriUnpack(g_Spyro.m_CollisionTriangleIndex, points);

  // Calculate the movement
  for (i = 0; i < 3; i++) {
    VecSub(&points[i], &points[i],
           &g_Spyro.m_collisionTriangleUnpacked.points[i]);
    VecAdd(&pointSum, &pointSum, &points[i]);
  }

  // Average the points
  pointSum.x /= 3;
  pointSum.y /= 3;
  pointSum.z /= 3;

  // Store the movement
  VecCopy(&g_Spyro.m_Physics.m_CollisionMovement, &pointSum);

  // If we've moved more than 32 units, we're on a moving platform
  if (VecMagnitude(&pointSum, 1) > 32) {
    g_Camera.m_OnMovingPlatform = 1;
  }
}

/// @brief Adjusts Spyro's position based on ground collision during air time
void AdjustAirCollision(void) {
  Vector3D vec2, vec3, vec1;

  vec2.x = 0;
  vec2.y = 0;
  vec2.z = -0x164;

  VecCopy(&vec1, &vec2);
  vec1.z -= 0x80;

  VecCopy(&vec3, &vec2);
  vec3.z += 0x80;

  VecRotateByMatrix(&g_Spyro.m_RotationMatrix, &vec1, &vec1);
  VecAdd(&vec1, &g_Spyro.m_Position, &vec1);

  VecRotateByLastMatrix(&vec3, &vec3);
  VecAdd(&vec3, &g_Spyro.m_Position, &vec3);

  VecRotateByLastMatrix(&vec2, &vec2);
  VecAdd(&vec2, &g_Spyro.m_Position, &vec2);

  if (func_8004AE38(&vec3, &vec1) != 0 && g_CollisionNormal.z > 0) {
    VecSub(&vec2, &g_CollisionPoint, &vec2);

    if (ABS(vec2.x) < 8) {
      vec2.x = 0;
    }

    if (ABS(vec2.y) < 8) {
      vec2.y = 0;
    }

    if (ABS(vec2.z) < 8) {
      vec2.z = 0;
    }

    VecAdd(&g_Spyro.m_Position, &g_Spyro.m_Position, &vec2);
    g_Spyro.m_airTime = 0;
  } else {
    g_Spyro.m_airTime++;
  }
}

extern int D_8006C714[16];

// @brief Pushback from collision used while falling, strange implementation
void func_8003E90C(void) {
  Vector3D vecA;
  Vector3D vecB;
  int i, v;
  int result;

  result = 0;
  v = 0x20;

  for (i = 0; i < 4; i++) {

    vecA.x = vecB.x = COSINE_8(v) >> 4;
    vecA.y = vecB.y = SINE_8(v) >> 4;

    vecA.z = -292;
    vecB.z = -420;

    VecAdd(&vecA, &vecA, &g_Spyro.m_Position);
    VecAdd(&vecB, &vecB, &g_Spyro.m_Position);

    if (func_8004AE38(&vecA, &vecB) != 0) {
      result |= 1 << i;
    }

    v += 0x40;
  }

  v = D_8006C714[result];
  if (v >= 0) {
    // I failed to find a better match than the << 1 >> 1
    // I'm guessing they did some kind of shifting, or masking
    g_Spyro.m_Physics.m_Acceleration.x += (COSINE_8(v) << 1 >> 1) >> 4;
    g_Spyro.m_Physics.m_Acceleration.y += (SINE_8(v) << 1 >> 1) >> 4;
  }
}

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8003EA68);

/// @brief Forces state to and resets animation
void func_8003FDC8(int pNewState) {
  func_8003EA68(pNewState);
  g_Spyro.m_bodyAnimation = spyro_StateDefaultAnimation[g_Spyro.m_State];
  g_Spyro.m_bodyAnimationFrame = 0;
  g_Spyro.m_nextBodyAnimation = spyro_StateDefaultAnimation[g_Spyro.m_State];
  g_Spyro.m_nextBodyAnimationFrame = 1;
  g_Spyro.m_bodyFrameProgress = 0;
  g_Spyro.m_bodyTransitionType = 0;
  g_Spyro.m_lastAnimationState = g_Spyro.m_State;
}

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8003FE40);

// Damage flag bits:
//   0x0010 - Bounce damage (enemy contact, causes Spyro to bounce back)
//   0x0020 - Hazard damage (plays hurt sound, e.g. fire/electricity)
//   0x0040 - Unknown damage type (state 27)
//   0x0080 - Unknown damage type (state 28)
//   0x0100 - Unknown damage type (state 22)
//   0x0400 - Charge damage (hit while charging, stops momentum)
//   0x0800 - Electrified/frozen toggle (state 17 - stuck in place)
//   0x2000 - Supercharge flag
//   0x8000 - Knockback (applies m_KnockbackDirection to acceleration)
//
// Invulnerability mask: 0xFFFFFE0E clears bits 0,4,5,6,7,8
// Charge immunity mask: 0xFFFFFBFF clears bit 10 (charge)

/// @brief Processes damage and action flags for Spyro
/// @param pFlags The action/damage flags to process
/// @return 1 if action was processed, 0 if level transition or no action
int HandleSpyroDamage(int pFlags) {
  int result = 0;
  int highFlags;

  // Don't process damage during level transitions
  if (g_NextLevelId != g_LevelId) {
    return 0;
  }

  // When invulnerable, mask off most damage types
  if (g_Spyro.m_invulverabilityTimer != 0) {
    pFlags &= 0xFFFFFE0E; // Clear low damage bits
    if (g_Spyro.m_Physics.m_TrueVelocity.z > 0) {
      // Rising in air - also immune to charge damage
      pFlags &= 0xFFFFFBFF;
    }
  }

  // Filter by what damage types Spyro can currently receive
  pFlags &= g_Spyro.m_DamageFlags;

  // Check for "normal" damage flags (0x5F1 = bits 0,4,5,6,7,8,10)
  if ((pFlags & 0x5F1) != 0 && g_Spyro.m_health >= 0) {
    // Decrement health unless god mode is active
    if (D_800756A0 == 0) {
      g_Spyro.m_health--;
    }

    if (pFlags & 0x10) {
      // Bounce damage - state depends on whether Spyro survived
      if (g_Spyro.m_health < 0) {
        func_8003EA68(0x1F); // State 31: Death
      } else {
        func_8003EA68(0x19); // State 25: Hurt bounce
      }
    } else if (pFlags & 0x20) {
      // Hazard damage with sound effect
      PlaySound(g_Spu.m_SoundTable->electricShock, (Moby *)&g_Spyro, 4,
                &g_Spyro.m_damageSoundChannel);
      func_8003EA68(7); // State 7: Hurt (hazard)
    } else if (pFlags & 0x40) {
      func_8003EA68(27); // State 27
    } else if (pFlags & 0x80) {
      func_8003EA68(28); // State 28
    } else if (pFlags & 0x100) {
      func_8003EA68(22); // State 22
    } else if (pFlags & 0x400) {
      // Charge damage in normal damage path
      func_8003EA68(29); // State 29: Charge interrupted
      // Instant death on certain floor types
      if (*g_Spyro.m_floorFlagsPointer != 0 && D_800756A0 == 0) {
        g_Spyro.m_health = -1;
      }
    } else {
      func_8003EA68(14); // State 14: Default hurt state
    }

    // Grant invulnerability frames
    if (g_Spyro.m_invulverabilityTimer < 90) {
      g_Spyro.m_invulverabilityTimer = 90;
    }
    return 1;
  }

  // Extract high flags for special behaviors
  highFlags = pFlags & 0xFC00;

  // Charge damage when no other damage flags apply
  if (pFlags & 0x400) {
    if (g_Spyro.m_health >= 0) {
      func_8003DFA4(); // Reset all velocity/momentum
      if (D_800756A0 == 0) {
        g_Spyro.m_health--;
      }
      if (g_Spyro.m_invulverabilityTimer < 90) {
        g_Spyro.m_invulverabilityTimer = 90;
      }
      func_8003EA68(29); // State 29: Charge interrupted
    }
    result = 1;
  }

  // Knockback - applies external momentum (e.g. from cannons, wind)
  if (highFlags & 0x8000) {
    func_8003EA68(12); // State 12: Knockback
    func_80017330(&g_Spyro.m_KnockbackDirection,
                  0x800); // Normalize to magnitude 0x800
    VecCopy(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_KnockbackDirection);
    result = 1;
  }

  // Electrified/frozen state toggle
  if (highFlags & 0x800) {
    if (g_Spyro.m_State != 17) {
      func_8003EA68(17); // State 17: Electrified/stuck
      result = 1;
    }
  } else if (g_Spyro.m_State == 17) {
    // Release from electrified state
    func_8003EA68(15); // State 15: Recovery
  }

  // Supercharge flag management (state 44 is immune)
  if (g_Spyro.m_State != 44) {
    if (highFlags & 0x2000) {
      g_Spyro.m_doingSupercharge = 1;
    } else {
      g_Spyro.m_doingSupercharge = 0;
    }
  }

  return result;
}

/// @brief VERY similar to HandleSpyroDamage. But doesn't take in any flags, and
/// contains knockback/bonking logic.
int func_80041270(void) {
  int highFlags;
  int mask = 0xFFFF;
  int damaged = 0;

  if (g_NextLevelId != g_LevelId) {
    return 0;
  }

  if (g_Spyro.m_invulverabilityTimer) {
    mask = 0xFE0E;
  }

  mask = mask & g_Spyro.m_DamageFlags;

  switch (mask & 6) {
  case 2: {
    Vector3D diff;
    int angleDiff;

    VecSub(&diff, &D_80075804->m_Position, &g_Spyro.m_Position);
    angleDiff =
        (Atan2(diff.x, diff.y, 1) - g_Spyro.m_Physics.m_SpeedAngle.m_RotZ) &
        0xFFF;

    if (angleDiff >= 0x801) {
      angleDiff -= 0x1000;
    }
    if (ABS2(angleDiff) < 0x200) {
      func_8003EA68(12);
      damaged = 1;
    }
    break;
  }

  case 4:
    func_8003EA68(12);
    damaged = 1;
    break;

  case 6:
    if (!g_Spyro.m_invulverabilityTimer && g_Spyro.m_health >= 0) {
      int nextState;

      if (D_800756A0 == 0) {
        g_Spyro.m_health -= 1;
      }

      g_Spyro.m_invulverabilityTimer = 90;

      if (mask & 0x10) {
        nextState = 25;
        if (g_Spyro.m_health < 0) {
          nextState = 31;
        }
      } else {
        nextState = 7;

        if (!(mask & 0x20)) {
          if (mask & 0x40) {
            nextState = 27;
          } else if (mask & 0x80) {
            nextState = 28;
          } else if (mask & 0x100) {
            nextState = 22;
          } else if (mask & 0x400) {
            nextState = 29;
          } else {
            nextState = 14;
          }
        }
      }

      func_8003EA68(nextState);
      return 1;
    }
    break;
  }

  highFlags = mask & 0xfc00;

  if ((highFlags & 0x8000)) {
    func_8003EA68(0xC);
    func_80017330(&g_Spyro.m_KnockbackDirection, 0x800);
    VecCopy(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_KnockbackDirection);
    damaged = 1;
  }

  if (highFlags & 0x800 && g_Spyro.m_State != 17) {
    func_8003EA68(17);
    damaged = 1;
  }

  if (highFlags & 0x400) {
    if (g_Spyro.m_health >= 0) {
      func_8003DFA4();

      if (!D_800756A0) {
        g_Spyro.m_health -= 1;
      }

      if (g_Spyro.m_invulverabilityTimer < 90) {
        g_Spyro.m_invulverabilityTimer = 90;
      }
      func_8003EA68(29);
      damaged = 1;
    }
  }

  if (highFlags & 0x2000) {
    g_Spyro.m_doingSupercharge = 1;
  } else {
    g_Spyro.m_doingSupercharge = 0;
  }

  return damaged;
}

/// @brief Cycles through animation states until finding a loaded idle animation
/// Sets Spyro's state to the first available animation from the idle animation
/// table
void CycleSpyroIdleAnimation(void) {
  int startIndex = D_80075970;

  do {
    // Advance to next animation index, wrapping at 9
    if (++D_80075970 >= 9) {
      D_80075970 = 0;
    }

    // Check if we've looped all the way around without finding a valid
    // animation
    if (D_80075970 == startIndex &&
        g_Models[0]->m_Animations
                [spyro_StateDefaultAnimation[D_8006BC60[D_80075970]]] ==
            nullptr) {
      // Reset timer and return
      D_80075788 = 0x2710;
      return;
    }

  } while (
      g_Models[0]
          ->m_Animations[spyro_StateDefaultAnimation[D_8006BC60[D_80075970]]] ==
      nullptr); // Keep looping until we find a valid animation

  func_8003EA68(D_8006BC60[D_80075970]);
}

void func_80041670(void);
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80041670);

/// @brief Physics state update for Spyro
/// @param pDeltaTimeIndex Deltatime index, used for the pad input buffer
void func_80043FE4(int pDeltaTimeIndex);
/* ----- helpers / globals referenced only by func_80043FE4 ----- */

extern int g_PortalLevelId;

void func_8003D3B8(int speed);
void func_8003D52C(int pStep);
void func_8003D92C(int pAddSpeed, int pSubtractSpeed);
void func_8003D978(void);
void func_8003E90C(void);
int func_80017928(int pAngle1, int pAngle2);
void TurnBodyToVelocity(int pMaxTurnSpeed, int pDeadzone);
int ApplySpyroSoftTurn(void);
int UpdateSpyroTurnMomentum(int pTableIndex);

/* Props of the cannon / whirlwind ride moby (m_mobyInUseBySpyro->m_Props).
   Only the orbit-angle field is referenced from the ride physics. */
typedef struct {
  int unk_0x0;
  int unk_0x4;
  int unk_0x8;
  int unk_0xc;
  int unk_0x10;
  int m_SpinAngle; /* 0x14 — orbit angle, advanced each frame by the ride */
} CannonProps;

/* "Spring toward a value" easing used for the gliding/superfly pitch. */
extern int func_80017A38(int pVal);
/* Hop / bob easing helper used by the gem-spin fall. */
extern void func_80017614(Vector3D *pVec, int pA, int pB);
/* Surface probe used by the superfly ceiling chase (returns nonzero if blocked). */
extern int func_80033E40(Vector3D *pProbe, Vector3D *pPos);
/* Loads the level fly-in parameters for the glide-portal transition. */
extern void func_80037714(LevelFlyInParameters *pParams);
/* Spawns one of the flying-level firework / trail effect mobys. */
extern int func_80052F38(int pClass, Vector3D *pOut, u_char pX, u_char pY);
/* Builds the firework rotation matrix from two angle bytes. */
extern int func_80017894(Vector3D *pA, Vector3D *pB, Vector3D *pC, int pRot);

/* Per-octant steering-rate table (states 4 and 6). */
extern u_char D_8006C6F8[];
/* Turn-momentum -> steering angle table: 13 entries, -24..24 in steps of 4,
 * indexed by a signed momentum through its centre entry (&D_8006C704[6]). The
 * first and last entries double as the momentum clamp limits. */
extern signed char D_8006C704[13];
/* Reference world-Z used to compute the superfly descent progress. */
extern int D_80076B88;
/* Per-flight-level glide target table (direction vector + reach length). */
extern Vector3D D_8006E7DC[];
extern int D_8006E7E4[];

/**
 * @brief One physics sub-step of Spyro's movement, dispatched on m_State.
 *
 * The core per-substep state machine. For each Spyro state it ticks the i-frame
 * timer (m_invulverabilityTimer @0x160), rebuilds the target speed/angle from
 * the stick (func_8003D3B8) and turns toward it (ApplySpyroSoftTurn /
 * UpdateSpyroTurnMomentum), accelerates/decelerates toward the target speed
 * (func_8003D92C), rolls the speed+angle into the acceleration vector
 * (func_8003D978), projects acceleration against any wall Spyro is touching,
 * and then applies state-specific gravity, gliding, flame-launch, supercharge
 * and superfly (flying-level) logic.
 *
 * @param pDeltaTimeIndex selects which buffered gamepad frame to read for this
 *        sub-step; g_ActivePad is repointed to g_Pad.m_BufferedInputs[idx].
 */
void func_80043FE4(int pDeltaTimeIndex) {
  Vector3D vTmp9;  /* whirlwind-dash pull (sp+0x10) */
  Vector3D vTmp10; /* charge-slide drift/pull (sp+0x20) */
  Vector3D vTmp5;  /* charge lock-on target (sp+0x30) */
  Vector3D vTmp3;  /* forward probe / decel / flight homing (sp+0x40) */
  Vector3D vTmp11; /* near-portal landing emit (sp+0x50) */
  Vector3D vTmp;   /* firework main (sp+0x60) */
  Vector3D vTmp2;  /* firework blend (sp+0x70) */
  Vector3D vTmp8;  /* superfly wing-flap (sp+0x80) */
  Vector3D vTmp4;  /* whirlwind (sp+0x90) */
  Vector3D vTmp7;  /* cannon/whirlwind orbit (sp+0xa0) */
  Vector3D vTmp6;  /* knockback drag (sp+0xb0) */
  Moby *moby;
  int angle;
  int angDelta;
  int sinV, cosV;
  int lift;
  int stickX, stickY;
  int glideX;
  int roll;
  int targetCam;
  signed char *pClamp;
  int idx;
  int dz;
  int reach;
  int tilt; /* a1: pitch-nudge wrap temp shared by the RotX settle sites */
  int idleFrames; /* s3: m_idleTimer + pDeltaTimeIndex, computed once up front */

  /* Point the active pad at this sub-step's buffered input frame.
     g_ActivePad is typed as Gamepad* but the consumers only read the leading
     m_Type/m_Held/.../m_Sticks fields, which a buffered-input frame shares. */
  g_ActivePad = (Gamepad *)&g_Pad.m_BufferedInputs[pDeltaTimeIndex];
  idleFrames = g_Spyro.m_idleTimer + pDeltaTimeIndex;

  /* Gnasty's-loot special case: once airborne in level 0x40, force flying. */
  if (g_Gamestate == 0 && g_LevelId == 0x40 && g_Spyro.m_airTime == 0) {
    g_Spyro.m_flyingAbility = 1;
  }

  switch (g_Spyro.m_State) {
  case 0: /* idle / walking */
  case 13:
  case 18:
  case 36: case 37: case 38: case 39: case 40: case 41: case 42: case 43:
    if (--g_Spyro.m_invulverabilityTimer < 0) {
      g_Spyro.m_invulverabilityTimer = 0;
    }
    if (g_Spyro.unk_0x194 == 0) {
      func_8003D3B8(0); /* stop, build a zero target */
      goto clear_accel;
    }
    /* Scripted "force flame" sequence once idle long enough. */
    if (g_Spyro.m_idleTimer >= 0x2D && g_SpyroFlame.m_IsFlameActive == 0) {
      if (g_Spyro.m_walkingState != 0) {
        g_Spyro.unk_0x194 = 0;
        goto clear_accel;
      }
      g_Spyro.m_walkingState = 1;
      g_Pad.m_Down |= 0x20; /* press flame */
    }
    VecNull(&g_Spyro.m_Physics.m_Acceleration);
    goto epilogue;

  case 1: /* turning / walking turn */
  case 2:
  case 21:
    if (--g_Spyro.m_invulverabilityTimer < 0) {
      g_Spyro.m_invulverabilityTimer = 0;
    }
    if (g_Spyro.unk_0x194 == 0) {
      func_8003D3B8(g_Spyro.m_Physics.unk_0x144);
    } else {
      angDelta = (g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ -
                  g_Spyro.m_Physics.m_SpeedAngle.m_RotZ) & 0xFFF;
      if (angDelta > 0x800) {
        angDelta -= 0x1000;
      }
      if (ABS2(angDelta) < 0x10) {
        func_8003EA68(0);
      }
    }
    g_Spyro.m_walkingState = 0;
    {
      int speed = g_Spyro.m_Physics.m_SpeedAngle.m_Speed;
      int turn;
      if (speed < 0x400) {
        turn = ApplySpyroSoftTurn();
      } else {
        turn = UpdateSpyroTurnMomentum((speed < 0xC80) ? 1 : 2);
      }
      if (g_Spyro.m_walkingState != 0) {
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed -= 0xC0;
        if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0) {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0;
        }
      } else {
        if (turn > 0x200) {
          func_8003D92C(0, 0xC0);
        } else {
          func_8003D92C(0x140, 0xC0);
        }
      }
    }
    func_8003D978();
    goto walk_apply_wall;

walk_apply_wall:
  /* If Spyro is against a wall, cancel the component of acceleration that would
     drive him into it (project onto the wall normal). */
  if (g_Spyro.m_againstWall != 0) {
    g_Spyro.m_wallAgainstSpyro.z = 0;
    func_80017330(&g_Spyro.m_wallAgainstSpyro, 0x1000);
    {
      int push =
          (-g_Spyro.m_Physics.m_Acceleration.x * g_Spyro.m_wallAgainstSpyro.x -
           g_Spyro.m_Physics.m_Acceleration.y * g_Spyro.m_wallAgainstSpyro.y) >>
          12;
      if (push > 0) {
        VecScaleToLength(&g_Spyro.m_wallAgainstSpyro, 0x1000, push);
        VecAdd(&g_Spyro.m_Physics.m_Acceleration,
               &g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_wallAgainstSpyro);
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
            VecMagnitude(&g_Spyro.m_Physics.m_Acceleration, 1);
      }
    }
  }
wall_edge_test:
  if (g_Spyro.m_onEdge != 0 || g_Spyro.m_airTime != 0) {
    g_Spyro.m_Physics.m_Acceleration.z =
        g_Spyro.m_Physics.m_TrueVelocity.z - 0xC0;
    goto epilogue;
  }
  VecAdd(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.m_Acceleration,
         &g_Spyro.m_Physics.unk_0xdc);
  goto epilogue;


  case 4: /* lock-on / look-at idle */
    if (--g_Spyro.m_invulverabilityTimer < 0) {
      g_Spyro.m_invulverabilityTimer = 0;
    }
    {
      int turnRate = func_80017928(g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ,
                                   g_Spyro.m_Physics.m_SpeedAngle.m_RotZ);
      if (turnRate < 0x80) {
        turnRate >>= 3;
      } else {
        int frame = idleFrames;
        if (frame >= 0xC) {
          frame = 0xB;
        }
        turnRate = D_8006C6F8[frame];
      }
      func_8003D52C(turnRate);
    }
    if (g_Spyro.m_onEdge == 0) {
      g_Spyro.m_Physics.m_SpeedAngle.m_Speed -= 0x100;
      if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0) {
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0;
      }
    } else {
      g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0;
    }
    func_8003D978();
    VecAdd(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.m_Acceleration,
           &g_Spyro.m_Physics.unk_0xdc);
    goto epilogue;

  case 3: /* targeting an interest moby */
    if (--g_Spyro.m_invulverabilityTimer < 0) {
      g_Spyro.m_invulverabilityTimer = 0;
    }
    if (g_Pad.m_NoMovementButtonPressed != 0 && g_Spyro.m_walkingState == 7) {
      g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed = 0;
      if (D_80075804 != 0) {
        g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ =
            Atan2(D_80075804->m_Position.x - g_Spyro.m_Position.x,
                  D_80075804->m_Position.y - g_Spyro.m_Position.y, 1);
      }
    } else {
      func_8003D3B8(g_Spyro.m_Physics.unk_0x144);
    }
    if (g_Spyro.m_walkingState != 7) {
      g_Spyro.m_walkingState = 0;
    }
    {
      int speed = g_Spyro.m_Physics.m_SpeedAngle.m_Speed;
      int turn;
      if (speed < 0x400) {
        turn = ApplySpyroSoftTurn();
      } else {
        turn = UpdateSpyroTurnMomentum((speed < 0xC80) ? 1 : 2);
      }
      if (g_Spyro.m_onEdge != 0) {
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0;
      } else if (g_Spyro.m_walkingState != 0) {
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed -= 0xC0;
        if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0) {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0;
        }
      } else {
        if (turn > 0x200) {
          func_8003D92C(0, 0xC0);
        } else {
          func_8003D92C(0x140, 0xC0);
        }
      }
    }
    func_8003D978();
    /* Wall projection, written out per-case in retail (this copy skips the
       onEdge re-check: the case guard above already dispatched on it). */
    if (g_Spyro.m_againstWall != 0) {
      g_Spyro.m_wallAgainstSpyro.z = 0;
      func_80017330(&g_Spyro.m_wallAgainstSpyro, 0x1000);
      {
        int push =
            (-g_Spyro.m_Physics.m_Acceleration.x *
                 g_Spyro.m_wallAgainstSpyro.x -
             g_Spyro.m_Physics.m_Acceleration.y *
                 g_Spyro.m_wallAgainstSpyro.y) >>
            12;
        if (push > 0) {
          VecScaleToLength(&g_Spyro.m_wallAgainstSpyro, 0x1000, push);
          VecAdd(&g_Spyro.m_Physics.m_Acceleration,
                 &g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_wallAgainstSpyro);
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
              VecMagnitude(&g_Spyro.m_Physics.m_Acceleration, 1);
        }
      }
    }
    if (g_Spyro.m_airTime != 0) {
      g_Spyro.m_Physics.m_Acceleration.z =
          g_Spyro.m_Physics.m_TrueVelocity.z - 0xC0;
      goto epilogue;
    }
    VecAdd(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.m_Acceleration,
           &g_Spyro.m_Physics.unk_0xdc);
    goto epilogue;

  case 5: /* whirlwind launch: dash toward the target heading */
    if (--g_Spyro.m_invulverabilityTimer < 0) {
      g_Spyro.m_invulverabilityTimer = 0;
    }
    func_8003D3B8(0xC80);
    UpdateSpyroTurnMomentum(2);
    func_8003D92C(0x140, 0xC0);
    g_Spyro.m_Physics.unk_0xe8.x =
        (g_Spyro.m_Physics.m_SpeedAngle.m_Speed *
         Cos(g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ)) >>
        12;
    g_Spyro.m_Physics.unk_0xe8.y =
        (g_Spyro.m_Physics.m_SpeedAngle.m_Speed *
         Sin(g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ)) >>
        12;
    VecSub(&vTmp9, &g_Spyro.m_Physics.unk_0xe8, &g_Spyro.m_Physics.m_Acceleration);
    vTmp9.z = 0;
    {
      int mag; /* pull toward the heading, then the wall push */

      mag = VecMagnitude(&vTmp9, 0);
      if (mag >= 0x281) {
        VecScaleToLength(&vTmp9, mag, 0x280);
      }
      VecAdd(&g_Spyro.m_Physics.m_Acceleration,
             &g_Spyro.m_Physics.m_Acceleration, &vTmp9);
      if (g_Spyro.m_againstWall != 0) {
        g_Spyro.m_wallAgainstSpyro.z = 0;
        func_80017330(&g_Spyro.m_wallAgainstSpyro, 0x1000);
        mag = (-g_Spyro.m_Physics.m_Acceleration.x *
                   g_Spyro.m_wallAgainstSpyro.x -
               g_Spyro.m_Physics.m_Acceleration.y *
                   g_Spyro.m_wallAgainstSpyro.y) >>
              12;
        if (mag > 0) {
          VecScaleToLength(&g_Spyro.m_wallAgainstSpyro, 0x1000, mag);
          VecAdd(&g_Spyro.m_Physics.m_Acceleration,
                 &g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_wallAgainstSpyro);
        }
      }
    }
    if (idleFrames < 0xD &&
        g_Spyro.m_walkingState == 0 &&
        ((g_ActivePad->m_Released & 0x40) != 0 || D_800756B4 != 0)) {
      g_Spyro.m_Physics.unk_0xe8.z += 0xD7 + g_Spyro.m_Physics.m_gravity;
      g_Spyro.m_Physics.m_Acceleration.z =
          ((g_Spyro.m_highestFlightPoint - g_Spyro.m_Position.z) << 6) -
          g_Spyro.m_Physics.m_Velocity.z + g_Spyro.m_Physics.unk_0xe8.z;
      g_Spyro.m_highestFlightPoint =
          ((g_Spyro.m_Position.z << 6) + g_Spyro.m_Physics.m_Acceleration.z +
           g_Spyro.m_Physics.m_Velocity.z) >>
          6;
    } else {
      g_Spyro.m_Physics.unk_0xe8.z += g_Spyro.m_Physics.m_gravity;
      g_Spyro.m_Physics.m_Acceleration.z = g_Spyro.m_Physics.unk_0xe8.z;
    }
    goto epilogue;

  case 6: /* charge lock-on: home the heading, decelerate, gravity, wall push */
    if (--g_Spyro.m_invulverabilityTimer < 0) {
      g_Spyro.m_invulverabilityTimer = 0;
    }
    if (g_Spyro.m_flyingAbility != 0) {
      func_8003D3B8(g_Spyro.m_Physics.unk_0x144);
      {
        int turnRate = (g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ -
                        g_Spyro.m_Physics.m_SpeedAngle.m_RotZ) &
                       0xFFF;
        if (turnRate >= 0x801) {
          turnRate -= 0x1000;
        }
        if (turnRate >= 0x21) {
          turnRate = 0x20;
        }
        if (turnRate < -0x20) {
          turnRate = -0x20;
        }
        func_8003D52C(turnRate);
      }
    }
    if (g_Spyro.m_Physics.m_TrueSpeed < 0x80) {
      VecCopy(&vTmp10, &g_Spyro.m_wallAgainstSpyro);
      VecShiftRight(&vTmp10, 3);
      VecAdd(&g_Spyro.m_Physics.m_Acceleration,
             &g_Spyro.m_Physics.m_Acceleration, &vTmp10);
    }
    VecNull(&vTmp10);
    VecSub(&vTmp10, &vTmp10, &g_Spyro.m_Physics.m_Acceleration);
    vTmp10.z = 0;
    {
      int pull = VecMagnitude(&vTmp10, 0);
      if (pull >= 0x41) {
        VecScaleToLength(&vTmp10, pull, 0x40);
      }
    }
    vTmp10.z = g_Spyro.m_Physics.m_gravity;
    VecAdd(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.m_Acceleration,
           &vTmp10);
    if (g_Spyro.m_floorIdleTime == 0 && g_Spyro.m_slopeAngle < 0x20) {
      func_8003E90C();
    }
    if (g_Spyro.m_Physics.m_Acceleration.z < -0x2300) {
      g_Spyro.m_Physics.m_Acceleration.z = -0x2300;
    }
    if (g_Spyro.m_againstWall != 0) {
      g_Spyro.m_wallAgainstSpyro.z = 0;
      func_80017330(&g_Spyro.m_wallAgainstSpyro, 0x1000);
      {
        int push =
            (-g_Spyro.m_Physics.m_Acceleration.x *
                 g_Spyro.m_wallAgainstSpyro.x -
             g_Spyro.m_Physics.m_Acceleration.y *
                 g_Spyro.m_wallAgainstSpyro.y) >>
            12;
        if (push > 0) {
          VecScaleToLength(&g_Spyro.m_wallAgainstSpyro, 0x1000, push);
          VecAdd(&g_Spyro.m_Physics.m_Acceleration,
                 &g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_wallAgainstSpyro);
        }
      }
    }
    goto epilogue;

  case 9: /* flame-launch forward */
  case 10: /* flame-launch up */
    if (--g_Spyro.m_invulverabilityTimer < 0) {
      g_Spyro.m_invulverabilityTimer = 0;
    }
    func_8003D3B8(0x1000);
    UpdateSpyroTurnMomentum(3);
    g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed = 0x1000;
    func_8003D92C(0x140, 0xC0);

    {
      int launchSpeed = g_Spyro.m_Physics.m_SpeedAngle.m_Speed;
      g_Spyro.m_Physics.m_Acceleration.x = 0;
      g_Spyro.m_Physics.m_Acceleration.z = 0;
      g_Spyro.m_Physics.m_Acceleration.y = launchSpeed;
      if (g_Spyro.m_State == 10) {
        g_Spyro.m_Physics.m_Acceleration.y = -launchSpeed;
      }
    }
    /* Rotate the launch offset by Spyro's matrix, then decay it 1/16. */
    VecRotateByMatrix(&g_Spyro.m_RotationMatrix,
                      &g_Spyro.m_Physics.m_Acceleration,
                      &g_Spyro.m_Physics.m_Acceleration);
    g_Spyro.m_Physics.unk_0xe8.x -= g_Spyro.m_Physics.unk_0xe8.x >> 4;
    g_Spyro.m_Physics.unk_0xe8.y -= g_Spyro.m_Physics.unk_0xe8.y >> 4;
    g_Spyro.m_Physics.unk_0xe8.z -= g_Spyro.m_Physics.unk_0xe8.z >> 4;
    VecAdd(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.m_Acceleration,
           &g_Spyro.m_Physics.unk_0xe8);
    if (g_Spyro.m_onEdge != 0 || g_Spyro.m_airTime != 0) {
      g_Spyro.m_Physics.m_Acceleration.z =
          g_Spyro.m_Physics.m_TrueVelocity.z - 0xC0;
      goto epilogue;
    }
    VecAdd(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.m_Acceleration,
           &g_Spyro.m_Physics.unk_0xdc);
    goto epilogue;

  case 11: /* charge: camera-relative steer, lock-on homing, momentum */
    if (--g_Spyro.m_invulverabilityTimer < 0) {
      g_Spyro.m_invulverabilityTimer = 0;
    }
    if (g_Spyro.m_walkingState & 1) {
      /* Momentum clamp limits: the first/last entries of the turn table. The
         table pointer is taken here and handed to pClamp once the stick has
         been read (pClamp is the function-wide "current turn table", also
         used by the superfly steer in case 44). */
      signed char *turnTable = D_8006C704;
      if (g_ActivePad->m_LeftStickMoved != 0) {
        stickX = g_ActivePad->m_Sticks.m_LeftX - 0x7F;
        stickY = 0x7F - g_ActivePad->m_Sticks.m_LeftY;
      } else {
        if (g_ActivePad->m_Released & 0x1000) {
          stickY = 0x7F;
        } else {
          stickY = (g_ActivePad->m_Released & 0x4000) ? -0x7F : 0;
        }
        if (g_ActivePad->m_Released & 0x2000) {
          stickX = 0x7F;
        } else {
          stickX = (g_ActivePad->m_Released & 0x8000) ? -0x7F : 0;
        }
      }
      {
        int angle = (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ - g_Camera.m_Rotation.z) & 0xFFF;
        int cosV = Cos(angle);
        int sinV = Sin(angle);
        int lo;
        pClamp = turnTable;
        lo = pClamp[0]; /* read before the momentum store */
        g_Spyro.m_Physics.m_TurnMomentum = ((-stickX * cosV) - (stickY * sinV)) >> 13;
        if (g_Spyro.m_Physics.m_TurnMomentum < lo) {
          g_Spyro.m_Physics.m_TurnMomentum = lo;
        }
      }
      if (pClamp[12] < g_Spyro.m_Physics.m_TurnMomentum) {
        g_Spyro.m_Physics.m_TurnMomentum = pClamp[12];
      }
      func_8003D52C(g_Spyro.m_Physics.m_TurnMomentum);

      if (D_80075790 != 0 && g_Spyro.m_idleTimer < 0x78) {
        int aim =
            (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ - g_Camera.m_Rotation.z) & 0xFFF;
        if (aim >= 0x801) {
          aim -= 0x1000;
        }
        if (ABS(aim) >= 0x200) {
          int targetDist;
          VecSub(&vTmp5, &D_80075790->m_Position, &g_Spyro.m_Position);
          targetDist = VecMagnitude(&vTmp5, 1);
          targetCam = Atan2(vTmp5.x, vTmp5.y, 1);
          aim = (targetCam - g_Spyro.m_Physics.m_SpeedAngle.m_RotZ) & 0xFFF;
          if (aim >= 0x801) {
            aim -= 0x1000;
          }
          if (ABS(aim) < 0x200 && targetDist < 0x1800) {
            {
              aim >>= 2;
              if (aim < pClamp[0]) {
                aim = pClamp[0];
              }
              if (pClamp[12] < aim) {
                aim = pClamp[12];
              }
              func_8003D52C(aim);
            }
            goto charge_homing_done;
          }
        }
        D_80075790 = 0;
      charge_homing_done:;
      }

      if (g_Spyro.m_doingSupercharge != 0) {
        int drop = g_Spyro.m_highestFlightPoint - g_Spyro.m_Position.z;
        if (drop < 0) {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
              0x1F80 - func_80017A38((-drop) << 13);
        } else {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
              func_80017A38(drop << 13) + 0x1F80;
        }
        if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >= 0x5901) {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0x5900;
        }
        if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0x1400) {
          g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed = 0x1400;
          g_Spyro.m_highestFlightPoint = g_Spyro.m_Position.z;
        }
        func_8003D978();
        VecCopy(&g_Spyro.m_Physics.unk_0xe8, &g_Spyro.m_Physics.m_Acceleration);
        if (g_Spyro.m_onEdge != 0) {
          g_Spyro.m_Physics.m_Acceleration.z -= 0xC0;
          goto epilogue;
        }
        {
          Vector3D *pAccel = &g_Spyro.m_Physics.m_Acceleration;
          VecAdd(pAccel, pAccel, &g_Spyro.m_Physics.unk_0xdc);
        }
        goto epilogue;
      }
      vTmp3.x = (-g_Spyro.m_Physics.unk_0xe8.x * 300) >> 12;
      vTmp3.y = (-g_Spyro.m_Physics.unk_0xe8.y * 300) >> 12;
      vTmp3.z = (-g_Spyro.m_Physics.unk_0xe8.z * 300) >> 12;
      VecAdd(&g_Spyro.m_Physics.unk_0xe8, &g_Spyro.m_Physics.unk_0xe8, &vTmp3);
      g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0x240;
      func_8003D978();
      VecAdd(&g_Spyro.m_Physics.unk_0xe8, &g_Spyro.m_Physics.unk_0xe8,
             &g_Spyro.m_Physics.m_Acceleration);
      VecAdd(&g_Spyro.m_Physics.unk_0xe8, &g_Spyro.m_Physics.unk_0xe8,
             (Vector3D *)&g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotY);
      g_Spyro.m_Physics.m_SpeedAngle.m_Speed = VecMagnitude(&g_Spyro.m_Physics.unk_0xe8, 1);
      VecAdd(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.unk_0xe8,
             &g_Spyro.m_Physics.unk_0xdc);
      goto epilogue;
    }
    g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed = 0;
    func_8003D92C(0, 0x180);
    func_8003D978();
    VecAdd(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.m_Acceleration,
           (Vector3D *)&g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotY);
    {
      int speed = VecMagnitude(&g_Spyro.m_Physics.m_Acceleration, 1);
      g_Spyro.m_Physics.m_SpeedAngle.m_Speed = speed;
      if (speed >= 0x2301) {
        VecScaleToLength(&g_Spyro.m_Physics.m_Acceleration, speed, 0x2300);
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0x2300;
      }
    }
    if (g_Spyro.m_onEdge != 0) {
      g_Spyro.m_Physics.m_Acceleration.z -= 0xC0;
      goto epilogue;
    }
    VecAdd(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.m_Acceleration,
           &g_Spyro.m_Physics.unk_0xdc);
    goto epilogue;

  case 12: /* gem-spin fall */
    if (--g_Spyro.m_invulverabilityTimer < 0) {
      g_Spyro.m_invulverabilityTimer = 0;
    }
    if (g_Spyro.m_Physics.m_Acceleration.z < 0) {
      g_Spyro.m_Physics.m_Acceleration.z = 0;
    }
    if (idleFrames >= 0x13) {
      func_80017614(&g_Spyro.m_Physics.m_Acceleration, 7, 3);
    }
    g_Spyro.m_Physics.m_Acceleration.z += g_Spyro.m_Physics.m_gravity;
    goto epilogue;

  case 7: /* reset speed/accel, gentle settle */
  case 14:
    g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed = 0;
    func_8003D92C(0, 0xC0);
    func_8003D978();
    g_Spyro.m_Physics.m_Acceleration.z = g_Spyro.m_Physics.m_TrueVelocity.z - 0xC0;
    if (g_Spyro.m_Physics.m_Acceleration.z < -0x2300) {
      g_Spyro.m_Physics.m_Acceleration.z = -0x2300;
    }
    goto epilogue;

  case 25: /* underwater sink / settle */
    if (g_Spyro.m_airTime != 0) {
      g_Spyro.m_Physics.m_Acceleration.z -= 0x600;
      if (g_Spyro.m_Physics.m_Acceleration.z < -0x2300) {
        g_Spyro.m_Physics.m_Acceleration.z = -0x2300;
      }
      goto epilogue;
    }
    VecNull(&g_Spyro.m_Physics.m_Acceleration);
    goto epilogue;

  case 27: /* surfacing / float spin */
    if (g_Spyro.m_airTime != 0) {
      g_Spyro.m_Physics.m_Acceleration.z -= 0x600;
      if (g_Spyro.m_Physics.m_Acceleration.z < -0x2300) {
        g_Spyro.m_Physics.m_Acceleration.z = -0x2300;
      }
    } else {
      VecNull(&g_Spyro.m_Physics.m_Acceleration);
    }
    g_Spyro.m_Physics.m_SpeedAngle.m_RotZ += 0x55;
    goto epilogue;

  case 15: case 23: case 32: case 33: case 34: /* glide / superfly flight */
    if (--g_Spyro.m_invulverabilityTimer < 0) {
      g_Spyro.m_invulverabilityTimer = 0;
    }
    if (g_Spyro.m_flyingAbility == 0) {
      goto nofly_tail;
    }
    if ((u_int)g_Spyro.m_walkingState < 0xB) {
      switch (g_Spyro.m_walkingState) {
      case 0: /* main glide: stick pitch/roll, bank, hold altitude, home to target */
        if (g_ActivePad->m_LeftStickMoved != 0) {
          glideX = g_ActivePad->m_Sticks.m_LeftX - 0x7F;
          dz = 0x7F - g_ActivePad->m_Sticks.m_LeftY;
        } else {
          if (g_ActivePad->m_Released & 0x1000) {
            D_80075700 += 0x10;
            if (D_80075700 >= 0x80) {
              D_80075700 = 0x7F;
            }
          } else if (g_ActivePad->m_Released & 0x4000) {
            D_80075700 -= 0x10;
            if (D_80075700 < -0x7F) {
              D_80075700 = -0x7F;
            }
          } else {
            glideX = -D_80075700;
            if (glideX >= 0x21) {
              glideX = 0x20;
            }
            if (glideX < -0x20) {
              glideX = -0x20;
            }
            D_80075700 += glideX;
          }
          dz = D_80075700;
          if (g_ActivePad->m_Released & 0x2000) {
            D_800758A0 += 0x10;
            if (D_800758A0 >= 0x80) {
              D_800758A0 = 0x7F;
            }
          } else if (g_ActivePad->m_Released & 0x8000) {
            D_800758A0 -= 0x10;
            if (D_800758A0 < -0x7F) {
              D_800758A0 = -0x7F;
            }
          } else {
            roll = -D_800758A0;
            if (roll >= 0x21) {
              roll = 0x20;
            }
            if (roll < -0x20) {
              roll = -0x20;
            }
            D_800758A0 += roll;
          }
          glideX = D_800758A0;
        }
        cosV = -glideX;
        if (dz != 0) {
          sinV = dz;
        } else {
          sinV = g_Spyro.m_Physics.m_SpeedAngle.m_RotY >> 3;
          if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0x1040) {
            sinV += (0x1040 - g_Spyro.m_Physics.m_SpeedAngle.m_Speed) >> 6;
          }
          if (sinV >= 0x80) {
            sinV = 0x7F;
          }
          if (sinV < -0x7F) {
            sinV = -0x7F;
          }
        }
        lift = Cos(g_Spyro.m_Physics.m_SpeedAngle.m_RotY);
        glideX = (sinV - (sinV << 4)) >> 7;
        roll = (((cosV << 2) + cosV) << 2) >> 7;
        if (g_Spyro.m_Position.z < g_Spyro.m_highestFlightPoint) {
          int probeDrop = (g_Spyro.m_Physics.m_Acceleration.z >> 3) - 0x400;
          vTmp3.z = probeDrop;
          if (probeDrop < 0) {
            vTmp3.x = g_Spyro.m_Physics.m_Acceleration.x >> 3;
            vTmp3.y = g_Spyro.m_Physics.m_Acceleration.y >> 3;
            VecAdd(&vTmp3, &vTmp3, &g_Spyro.m_Position);
            if (func_80033E40(&g_Spyro.m_Position, &vTmp3) == 0) {
              dz = (g_Spyro.m_Position.z - D_80076B88) >> 3;
              if (dz >= 8) {
                dz = 7;
              }
              glideX += dz;
            }
          }
        }
        g_Spyro.m_Physics.m_SpeedAngle.m_RotZ =
            (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ + roll) & 0xFFF;
        g_Spyro.m_Physics.m_SpeedAngle.m_RotY =
            (g_Spyro.m_Physics.m_SpeedAngle.m_RotY + glideX) & 0xFFF;
        if (g_Spyro.m_Physics.m_SpeedAngle.m_RotY >= 0x801) {
          g_Spyro.m_Physics.m_SpeedAngle.m_RotY -= 0x1000;
        }
        if (g_Spyro.m_Physics.m_SpeedAngle.m_RotY >= 0x321) {
          g_Spyro.m_Physics.m_SpeedAngle.m_RotY = 0x320;
        }
        glideX = g_Spyro.m_highestFlightPoint - g_Spyro.m_Position.z;
        if (glideX < 0) {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
              0x1040 - (func_80017A38(-glideX) << 7);
        } else {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
              (func_80017A38(glideX) << 6) + 0x1040;
        }
        if (g_IsFlightLevel == 0) {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed += 0x41E;
        }
        if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >= 0x5901) {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0x5900;
        }
        glideX += 0x132;
        dz = glideX >> 2;
        if (dz < 0) {
          dz = 0;
        }
        if (dz < g_Spyro.m_Physics.m_SpeedAngle.m_RotY) {
          g_Spyro.m_Physics.m_SpeedAngle.m_RotY = dz;
        }
        if (g_Spyro.m_Physics.m_SpeedAngle.m_RotY < -0x320) {
          g_Spyro.m_Physics.m_SpeedAngle.m_RotY = -0x320;
        }
        if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0x780) {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0x780;
        }
        {
          int sway = (roll * -(lift << 5)) >> 12;
          sway -= (D_80075960 << 4) >> 6;
          sway -= (g_Spyro.m_Physics.m_SpeedAngle.m_RotX << 6) >> 6;
          D_80075960 += sway;
        }
        g_Spyro.m_Physics.m_SpeedAngle.m_RotX =
            (g_Spyro.m_Physics.m_SpeedAngle.m_RotX + (D_80075960 >> 6)) & 0xFFF;
        if (g_Spyro.m_Physics.m_SpeedAngle.m_RotX >= 0x801) {
          g_Spyro.m_Physics.m_SpeedAngle.m_RotX -= 0x1000;
        }
        if (g_Spyro.m_Physics.m_SpeedAngle.m_RotX >= 0x301) {
          g_Spyro.m_Physics.m_SpeedAngle.m_RotX = 0x300;
        }
        if (g_Spyro.m_Physics.m_SpeedAngle.m_RotX < -0x300) {
          g_Spyro.m_Physics.m_SpeedAngle.m_RotX = -0x300;
        }
        func_8003D978();
        if (g_IsFlightLevel != 0) {
          int reach;
          Vector3D *pHome = &vTmp3;
          glideX = g_LevelId / 10 - 1;
          VecSub(pHome, &D_8006E7DC[glideX], &g_Spyro.m_Position);
          VecShiftRight(pHome, 4);
          dz = VecMagnitude(pHome, 0);
          reach = D_8006E7E4[glideX * 3] >> 4;
          if (reach < dz) {
            angle = dz - reach;
            VecScaleToLength(pHome, dz, angle);
            VecShiftLeft(pHome, 5);
            vTmp3.z = 0;
            VecAdd(&g_Spyro.m_Physics.m_Acceleration,
                   &g_Spyro.m_Physics.m_Acceleration, pHome);
            cosV = (Atan2(vTmp3.x, vTmp3.y, 1) -
                    g_Spyro.m_Physics.m_SpeedAngle.m_RotZ) &
                   0xFFF;
            if (cosV >= 0x801) {
              cosV -= 0x1000;
            }
            cosV = (cosV * angle) >> 15;
            if (cosV < -0x20) {
              cosV = -0x20;
            }
            if (cosV >= 0x21) {
              cosV = 0x20;
            }
            g_Spyro.m_Physics.m_SpeedAngle.m_RotZ += cosV;
          }
        }
        break;

      case 1: /* climb-out: spin yaw to level, spring speed toward altitude */
        g_Spyro.m_Physics.m_SpeedAngle.m_RotZ =
            g_Spyro.m_Physics.m_SpeedAngle.m_RotZ & 0xFFF;
        g_Spyro.m_Physics.m_SpeedAngle.m_RotY =
            (g_Spyro.m_Physics.m_SpeedAngle.m_RotY + 0x1E) & 0xFFF;
        if (g_Spyro.m_Physics.m_SpeedAngle.m_RotY >= 0x801) {
          g_Spyro.m_Physics.m_SpeedAngle.m_RotY -= 0x1000;
        }
        if (g_Spyro.m_Physics.m_SpeedAngle.m_RotY >= 0x401) {
          g_Spyro.unk_0x254 = 1;
        } else if (g_Spyro.m_Physics.m_SpeedAngle.m_RotY > 0) {
          if (g_Spyro.unk_0x254 != 0) {
            g_Spyro.m_walkingState = 0;
          }
          g_Spyro.unk_0x254 = 0;
        }
        {
          tilt = -g_Spyro.m_Physics.m_SpeedAngle.m_RotX & 0xFFF;
          if (tilt >= 0x801) {
            tilt -= 0x1000;
          }
          if (tilt >= 0x11) {
            tilt = 0x10;
          }
          if (tilt < -0x10) {
            tilt = -0x10;
          }
          g_Spyro.m_Physics.m_SpeedAngle.m_RotX =
              (g_Spyro.m_Physics.m_SpeedAngle.m_RotX + tilt) & 0xFFF;
        }
        glideX = g_Spyro.m_highestFlightPoint - g_Spyro.m_Position.z;
        if (glideX < 0) {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0x1040 - (func_80017A38(-glideX) << 7);
        } else {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed = (func_80017A38(glideX) << 6) + 0x1040;
        }
        if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >= 0x5901) {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0x5900;
        }
        if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0x1E00 &&
            g_Spyro.unk_0x254 == 0) {
          g_Spyro.m_walkingState = 0;
          D_800758A0 = 0;
          D_80075700 = 0;
        }
        func_8003D978();
        break; /* fall through to the default firework/effect tail */

      case 2: /* banking glide: steer yaw/roll toward the target altitude */
        if (g_Spyro.unk_0x254 != 0) {
          int alt;
          glideX = -g_Spyro.m_Physics.m_SpeedAngle.m_RotY & 0xFFF;
          if (glideX >= 0x801) {
            glideX -= 0x1000;
          }
          alt = D_80075700 - g_Spyro.m_Position.z;
          glideX += (alt - (g_Spyro.m_Physics.m_TrueVelocity.z >> 5)) >> 2;
          if (glideX >= 0x1F) {
            glideX = 0x1E;
          }
          if (glideX < -0x1E) {
            glideX = -0x1E;
          }
          g_Spyro.m_Physics.m_SpeedAngle.m_RotY =
              (g_Spyro.m_Physics.m_SpeedAngle.m_RotY + glideX) & 0xFFF;
          if (g_Spyro.m_Physics.m_SpeedAngle.m_RotY >= 0x801) {
            g_Spyro.m_Physics.m_SpeedAngle.m_RotY -= 0x1000;
          }
          g_Spyro.m_Physics.m_SpeedAngle.m_RotZ =
              g_Spyro.m_Physics.m_SpeedAngle.m_RotZ & 0xFFF;
          if (ABS(g_Spyro.m_Physics.m_SpeedAngle.m_RotX) < 0x40) {
            if (ABS(alt) < 0x100 &&
                ABS(g_Spyro.m_Physics.m_SpeedAngle.m_RotY) < 0x80) {
              g_Spyro.m_walkingState = 0;
              g_Spyro.unk_0x254 = 0;
              D_800758A0 = 0;
              D_80075700 = 0;
            }
            g_Spyro.m_Physics.m_SpeedAngle.m_RotX = 0;
          } else {
            {
              tilt = -g_Spyro.m_Physics.m_SpeedAngle.m_RotX & 0xFFF;
              if (tilt >= 0x801) {
                tilt -= 0x1000;
              }
              if (tilt >= 0x11) {
                tilt = 0x10;
              }
              if (tilt < -0x10) {
                tilt = -0x10;
              }
              D_800758A0 += tilt;
            }
            if (D_800758A0 >= 0x41) {
              D_800758A0 = 0x40;
            }
            if (D_800758A0 < -0x40) {
              D_800758A0 = -0x40;
            }
            g_Spyro.m_Physics.m_SpeedAngle.m_RotX =
                (g_Spyro.m_Physics.m_SpeedAngle.m_RotX + D_800758A0) & 0xFFF;
          }
          if (g_Spyro.m_Physics.m_SpeedAngle.m_RotX >= 0x801) {
            g_Spyro.m_Physics.m_SpeedAngle.m_RotX -= 0x1000;
          }
        } else {
          g_Spyro.m_Physics.m_SpeedAngle.m_RotZ =
              g_Spyro.m_Physics.m_SpeedAngle.m_RotZ & 0xFFF;
          g_Spyro.m_Physics.m_SpeedAngle.m_RotY =
              (g_Spyro.m_Physics.m_SpeedAngle.m_RotY + 0x1E) & 0xFFF;
          if (g_Spyro.m_Physics.m_SpeedAngle.m_RotY >= 0x801) {
            g_Spyro.m_Physics.m_SpeedAngle.m_RotY -= 0x1000;
          }
          if (g_Spyro.m_Physics.m_SpeedAngle.m_RotY < -0x400) {
            g_Spyro.unk_0x254 = 1;
            g_Spyro.m_Physics.m_SpeedAngle.m_RotZ =
                (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ + 0x800) & 0xFFF;
            g_Spyro.m_Physics.m_SpeedAngle.m_RotY =
                (0x800 - g_Spyro.m_Physics.m_SpeedAngle.m_RotY) & 0xFFF;
            D_800758A0 = 0;
            g_Spyro.m_Physics.m_SpeedAngle.m_RotX =
                (g_Spyro.m_Physics.m_SpeedAngle.m_RotX + 0x800) & 0xFFF;
          }
          {
            tilt = -g_Spyro.m_Physics.m_SpeedAngle.m_RotX & 0xFFF;
            if (tilt >= 0x801) {
              tilt -= 0x1000;
            }
            if (tilt >= 0x11) {
              tilt = 0x10;
            }
            if (tilt < -0x10) {
              tilt = -0x10;
            }
            g_Spyro.m_Physics.m_SpeedAngle.m_RotX =
                (g_Spyro.m_Physics.m_SpeedAngle.m_RotX + tilt) & 0xFFF;
          }
        }
        glideX = g_Spyro.m_highestFlightPoint - g_Spyro.m_Position.z;
        if (glideX < 0) {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
              0x1040 - (func_80017A38(-glideX) << 7);
        } else {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
              (func_80017A38(glideX) << 6) + 0x1040;
        }
        if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >= 0x5901) {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0x5900;
        }
        if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0x1E00 &&
            g_Spyro.unk_0x254 == 0 &&
            g_Spyro.m_Physics.m_SpeedAngle.m_RotY < 0x400) {
          g_Spyro.m_walkingState = 0;
          D_800758A0 = 0;
          D_80075700 = 0;
        }
        func_8003D978();
        break;

      case 3: /* fly-in: load level glide params, yaw to 0x400, approach cruise */
        if (g_Camera.m_State != 0x8000000E) {
          VecCopy(&D_8006EBCC.m_CameraPosition, &g_Camera.m_Position);
          func_80037714(&D_8006EBCC);
        }
        glideX = (0x400 - g_Spyro.m_Physics.m_SpeedAngle.m_RotY) & 0xFFF;
        if (glideX >= 0x801) {
          glideX -= 0x1000;
        }
        if (glideX >= 0x1F) {
          glideX = 0x1E;
        }
        if (glideX < -0x1E) {
          glideX = -0x1E;
        }
        g_Spyro.m_Physics.m_SpeedAngle.m_RotY =
            (g_Spyro.m_Physics.m_SpeedAngle.m_RotY + glideX) & 0xFFF;
        g_Spyro.m_Physics.m_SpeedAngle.m_RotZ =
            g_Spyro.m_Physics.m_SpeedAngle.m_RotZ & 0xFFF;
        if (g_Spyro.m_Physics.m_SpeedAngle.m_RotY >= 0x801) {
          g_Spyro.m_Physics.m_SpeedAngle.m_RotY -= 0x1000;
        }
        {
          int bank = g_Spyro.m_Physics.m_SpeedAngle.m_RotY - 0x400;
          if (bank < 0) {
            bank = -bank;
          }
          if (bank >= 0x80) {
            tilt = -g_Spyro.m_Physics.m_SpeedAngle.m_RotX & 0xFFF;
            if (tilt >= 0x801) {
              tilt -= 0x1000;
            }
            if (tilt >= 0x11) {
              tilt = 0x10;
            }
            if (tilt < -0x10) {
              tilt = -0x10;
            }
          } else {
            tilt = 0x40;
          }
          g_Spyro.m_Physics.m_SpeedAngle.m_RotX =
              (g_Spyro.m_Physics.m_SpeedAngle.m_RotX + tilt) & 0xFFF;
        }
        glideX = 0x1040 - g_Spyro.m_Physics.m_SpeedAngle.m_Speed;
        if (glideX < -0x80) {
          glideX = -0x80;
        }
        if (glideX >= 0x81) {
          glideX = 0x80;
        }
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed += glideX;
        func_8003D978();
        break;

      case 10: /* cruise: approach speed 0x1900, spin yaw, settle pitch */
        g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed = 0x1900;
        if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0x1900) {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed += 0x80;
          if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed <
              g_Spyro.m_Physics.m_SpeedAngle.m_Speed) {
            g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
                g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed;
          }
        } else if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed <
                   g_Spyro.m_Physics.m_SpeedAngle.m_Speed) {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed -= 0x80;
          if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0x1900) {
            g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
                g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed;
          }
        }
        if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0x780) {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0x780;
        }
        g_Spyro.m_bodyRotation.z = g_Spyro.m_Physics.m_SpeedAngle.m_RotZ >> 4;
        dz = 0x1E;
        if (g_Spyro.unk_0x254 != 0) {
          if (g_Spyro.m_Physics.m_SpeedAngle.m_RotY >= -0xFF) {
            g_Spyro.m_walkingState = 0;
            g_Camera.unk_0xC0 = D_8006C588[g_Spyro.m_State];
            g_Spyro.m_sortingDepth = 4;
          }
        } else if (g_Spyro.m_Physics.m_SpeedAngle.m_RotY < 0) {
          g_Spyro.unk_0x254 = 1;
        }
        g_Spyro.m_Physics.m_SpeedAngle.m_RotY =
            (g_Spyro.m_Physics.m_SpeedAngle.m_RotY + dz) & 0xFFF;
        g_Spyro.m_bodyRotation.y = g_Spyro.m_Physics.m_SpeedAngle.m_RotY >> 4;
        if (g_Spyro.m_Physics.m_SpeedAngle.m_RotY >= 0x801) {
          g_Spyro.m_Physics.m_SpeedAngle.m_RotY -= 0x1000;
        }
        func_8003D978();
        if (g_Spyro.m_noGamepadUpdateFrames <= 0) {
          g_Spyro.m_noGamepadUpdateFrames = 1;
        }
        tilt = (-g_Spyro.m_Physics.m_TurnMomentum * 8 -
                g_Spyro.m_Physics.m_SpeedAngle.m_RotX) & 0xFFF;
        if (tilt >= 0x801) {
          tilt -= 0x1000;
        }
        if (tilt >= 0x11) {
          tilt = 0x10;
        } else if (tilt < -0x10) {
          tilt = -0x10;
        }
        g_Spyro.m_Physics.m_SpeedAngle.m_RotX =
            (g_Spyro.m_Physics.m_SpeedAngle.m_RotX + tilt) & 0xFFF;
        break; /* fall through to the default firework/effect tail */
      }
    }
    /* default tail (.L80046184): flying-level firework / trail effect spawner,
       reached by walkingState >= 0xB, inner sub-states 4-9, and the fall-through
       from cases 1/10 above. */
    if (g_Spyro.m_SurfaceProximityState != 0 &&
        g_Spyro.m_Position.z - g_Spyro.m_surfaceBelowSpyro < 0xC01) {
      idx = (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >> 11) + 2;
      if (g_Spyro.m_Physics.m_Velocity.x == 0 &&
          g_Spyro.m_Physics.m_Velocity.y == 0) {
        idx += 0x10000;
      }
      {
        Vector3D *pEmit = &vTmp11;
        VecCopy(pEmit, &g_Spyro.m_Physics.m_Velocity);
        VecShiftRight(pEmit, 6);
        vTmp11.x += g_Spyro.m_Position.x;
        vTmp11.y += g_Spyro.m_Position.y;
        vTmp11.z = g_Spyro.m_surfaceBelowSpyro;
        ((void (*)(int, int, void *, int))D_800758E4)(1, 0x1B, pEmit, idx);
      }
    }
    {
      int count;
      int blend;
      int cls;
      int i;
      int moving = (g_Spyro.m_Physics.m_Velocity.x != 0 ||
                    g_Spyro.m_Physics.m_Velocity.y != 0);
      if (g_Spyro.m_State == 0x20) {
        int step = moving - 3;
        count = (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >> 11) - step;
      } else {
        int step = moving - 1;
        count = (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >> 11) - step;
      }
      if (count <= 0) {
        count = 1;
      }
      blend = g_Spyro.m_bodyFrameProgress;
      if (moving != 0 && blend < 0xD) {
        blend += 4;
      }
      i = 0;
      do {
        cls = 0x9 + i * 0x5B;
        func_80052F38(cls, &vTmp, g_Spyro.m_bodyAnimation,
                      g_Spyro.m_bodyAnimationFrame);
        if (blend != 0) {
          func_80052F38(cls, &vTmp2, g_Spyro.m_nextBodyAnimation,
                        g_Spyro.m_nextBodyAnimationFrame);
          func_80017894(&vTmp, &vTmp, &vTmp2, blend << 8);
        }
        VecRotateByMatrix(&g_Spyro.m_RotationMatrix, &vTmp, &vTmp);
        VecAdd(&vTmp, &vTmp, &g_Spyro.m_Position);
        VecCopy(&vTmp2, &g_Spyro.m_Physics.m_Velocity);
        VecShiftRight(&vTmp2, 6);
        VecAdd(&vTmp, &vTmp, &vTmp2);
        ((void (*)(int, int, void *, int))D_800758E4)(1, 0x1A, &vTmp, count);
      } while (++i < 2);
    }
    goto epilogue;

  nofly_tail:
      /* ---- no-fly glide tail (.L800463CC): camera-relative steering ---- */
      if (g_ActivePad->m_LeftStickMoved != 0) {
        glideX = g_ActivePad->m_Sticks.m_LeftX - 0x7F;
        dz = 0x7F - g_ActivePad->m_Sticks.m_LeftY;
      } else {
        if (g_ActivePad->m_Released & 0x1000) {
          dz = 0x7F;
        } else {
          dz = (g_ActivePad->m_Released & 0x4000) ? -0x7F : 0;
        }
        if (g_ActivePad->m_Released & 0x2000) {
          glideX = 0x7F;
        } else {
          glideX = (g_ActivePad->m_Released & 0x8000) ? -0x7F : 0;
        }
      }
      /* rotate the stick vector into Spyro's frame using (RotZ - camera yaw) */
      {
        int angle =
            (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ - g_Camera.m_Rotation.z) & 0xFFF;
        int c = Cos(angle);
        cosV = (-glideX * c - dz * Sin(angle)) >> 12;
        sinV = (dz * Cos(angle) - glideX * Sin(angle)) >> 12;
      }
      /* forward component drives a target speed; dive (sinV<0) ramps it down */
      if (sinV < 0) {
        g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed =
            ((sinV * 0x1180) >> 7) + 0x1900;
      } else {
        g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed = 0x1900;
      }
      if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed >
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed) {
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed += 0x80;
        if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed <
            g_Spyro.m_Physics.m_SpeedAngle.m_Speed) {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
              g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed;
        }
      } else if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed <
                 g_Spyro.m_Physics.m_SpeedAngle.m_Speed) {
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed -= 0x80;
        if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed <
            g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed) {
          g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
              g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed;
        }
      }
      if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0x780) {
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0x780;
      }
      /* lateral component banks the heading (RotZ) and the body roll */
      g_Spyro.m_Physics.m_TurnMomentum = (cosV * 20) >> 7;
      g_Spyro.m_Physics.m_SpeedAngle.m_RotZ += g_Spyro.m_Physics.m_TurnMomentum;
      g_Spyro.m_bodyRotation.z = g_Spyro.m_Physics.m_SpeedAngle.m_RotZ >> 4;
      if (g_Spyro.m_walkingState == 8) {
        /* portal-entry: snap heading toward the portal angle, kill velocity */
        if (g_PortalLevelId == 0) {
          g_Spyro.m_Physics.m_TurnMomentum =
              ((g_Spyro.m_portalAngle.z << 4) -
               g_Spyro.m_Physics.m_SpeedAngle.m_RotZ) &
              0xFFF;
          if (g_Spyro.m_Physics.m_TurnMomentum >= 0x801) {
            g_Spyro.m_Physics.m_TurnMomentum -= 0x1000;
          }
          g_Spyro.m_Physics.m_TurnMomentum <<= 4;
          if (g_Spyro.m_Physics.m_TurnMomentum < -0x10) {
            g_Spyro.m_Physics.m_TurnMomentum = -0x10;
          }
          if (g_Spyro.m_Physics.m_TurnMomentum >= 0x11) {
            g_Spyro.m_Physics.m_TurnMomentum = 0x10;
          }
          g_Spyro.m_Physics.m_SpeedAngle.m_RotZ +=
              g_Spyro.m_Physics.m_TurnMomentum;
        }
        VecNull(&g_Spyro.m_Physics.m_Acceleration);
        goto nofly_rotY_zero;
      } else if (g_Spyro.m_walkingState == 9) {
        /* portal flythrough: drift toward the exit, end glide when close */
        func_8003D978();
        g_Spyro.m_Physics.m_Acceleration.z = 0;
        g_Spyro.m_ControlFlags = 0x80004000;
        if (g_Spyro.m_noGamepadUpdateFrames <= 0) {
          g_Spyro.m_noGamepadUpdateFrames = 1;
        }
        if (OctDistance(&g_Spyro.m_Position, &g_Spyro.m_portalEndPos) < 0x300) {
          g_Spyro.m_walkingState = 0;
          g_Camera.unk_0xC0 = D_8006C588[g_Spyro.m_State];
          g_Spyro.m_sortingDepth = 4;
        }
        goto nofly_rotY_zero;
      } else if (g_Spyro.m_walkingState == 0xB) {
        func_8003D978();
        g_Spyro.m_Physics.m_Acceleration.z = g_Spyro.m_Physics.m_TrueVelocity.z;
        g_Spyro.m_Physics.m_Acceleration.z =
            g_Spyro.m_Physics.m_TrueVelocity.z + g_Spyro.m_Physics.m_gravity;
        if (g_Spyro.m_Physics.m_Acceleration.z < -0x780) {
          g_Spyro.m_Physics.m_Acceleration.z = -0x780;
        }
        g_Spyro.m_Physics.m_SpeedAngle.m_RotY = 0;
        if (g_Spyro.m_noGamepadUpdateFrames <= 0) {
          g_Spyro.m_noGamepadUpdateFrames = 1;
        }
        goto nofly_rotX;
      } else if (g_Spyro.m_walkingState == 0xA) {
        /* landing flare: turn the nose toward the run-out heading */
        if (g_Spyro.m_idleTimer < 0x10) {
          dz = 0;
        } else {
          dz = func_8004D5EC((Vector3D *)&g_Spyro, 0x10000);
          if (g_Spyro.unk_0x254 != 0) {
            int floorGap = g_Spyro.m_Position.z - dz;
            if (floorGap < 0x200) {
              g_Spyro.m_walkingState = 0;
              g_Camera.unk_0xC0 = D_8006C588[g_Spyro.m_State];
              g_Spyro.m_sortingDepth = 4;
            } else if (floorGap < 0x800) {
              dz = (-0x100 - g_Spyro.m_Physics.m_SpeedAngle.m_RotY) & 0xFFF;
              if (dz >= 0x801) {
                dz -= 0x1000;
              }
              dz >>= 2;
              if (dz < -0x3C) {
                dz = -0x3C;
              }
              if (dz >= 0x3D) {
                dz = 0x3C;
              }
            } else {
              goto nofly_rotz_recover;
            }
          } else {
          nofly_rotz_recover:
            dz = 0x1E;
            if ((u_int)(g_Spyro.m_Physics.m_SpeedAngle.m_RotY + 0x100) >= 0x501) {
              g_Spyro.unk_0x254 = 1;
              dz = (-0x400 - g_Spyro.m_Physics.m_SpeedAngle.m_RotY) & 0xFFF;
              if (dz >= 0x801) {
                dz -= 0x1000;
              }
              if (g_LevelId == 0x16) {
                int lean = abs(dz);
                if (lean < 0x100) {
                  g_Camera.unk_0xC0 = D_8006C588[g_Spyro.m_State];
                }
              }
              dz >>= 4;
              if (dz < -0x1E) {
                dz = -0x1E;
              }
              if (dz >= 0x1F) {
                dz = 0x1E;
              }
            } else {
              g_Spyro.unk_0x254 = 0;
            }
          }
        }
        g_Spyro.m_Physics.m_SpeedAngle.m_RotY =
            (g_Spyro.m_Physics.m_SpeedAngle.m_RotY + dz) & 0xFFF;
        g_Spyro.m_bodyRotation.y = g_Spyro.m_Physics.m_SpeedAngle.m_RotY >> 4;
        if (g_Spyro.m_Physics.m_SpeedAngle.m_RotY >= 0x801) {
          g_Spyro.m_Physics.m_SpeedAngle.m_RotY -= 0x1000;
        }
        func_8003D978();
        /* fall through to the no-gamepad check */
      } else {
        goto nofly_default;
      }
      if (g_Spyro.m_noGamepadUpdateFrames <= 0) {
        g_Spyro.m_noGamepadUpdateFrames = 1;
      }
      goto nofly_rotX;
    nofly_default:
      func_8003D978();
      g_Spyro.m_Physics.m_Acceleration.z = g_Spyro.m_Physics.m_TrueVelocity.z;
      g_Spyro.m_Physics.m_Acceleration.z =
          g_Spyro.m_Physics.m_TrueVelocity.z + g_Spyro.m_Physics.m_gravity;
      if (g_Spyro.m_Physics.m_Acceleration.z < -0x780) {
        g_Spyro.m_Physics.m_Acceleration.z = -0x780;
      }
    nofly_rotY_zero:
      g_Spyro.m_Physics.m_SpeedAngle.m_RotY = 0;
    nofly_rotX:
      /* RotX spring: roll smoothly back from the bank toward level */
      tilt = ((-g_Spyro.m_Physics.m_TurnMomentum * 8) -
              g_Spyro.m_Physics.m_SpeedAngle.m_RotX) &
             0xFFF;
      if (tilt >= 0x801) {
        tilt -= 0x1000;
      }
      if (tilt >= 0x11) {
        tilt = 0x10;
      } else if (tilt < -0x10) {
        tilt = -0x10;
      }
      g_Spyro.m_Physics.m_SpeedAngle.m_RotX =
          (g_Spyro.m_Physics.m_SpeedAngle.m_RotX + tilt) & 0xFFF;
      goto epilogue;

  case 16: /* free-fall: gravity-accelerate, clamp terminal velocity */
    if (--g_Spyro.m_invulverabilityTimer < 0) {
      g_Spyro.m_invulverabilityTimer = 0;
    }
    g_Spyro.m_Physics.m_Acceleration.z += g_Spyro.m_Physics.m_gravity;
    if (g_Spyro.m_Physics.m_Acceleration.z < -0x2300) {
      g_Spyro.m_Physics.m_Acceleration.z = -0x2300;
    }
    goto epilogue;

  case 17: /* superfly: wing-flap toward the floor target / steer to the moby */
    if (--g_Spyro.m_invulverabilityTimer < 0) {
      g_Spyro.m_invulverabilityTimer = 0;
    }
    moby = g_Spyro.m_mobyInUseBySpyro;
    if (moby == NULL) {
      goto epilogue;
    }
    {
    int whirlTop;
    int t; /* s1: heading accumulator (angle / height delta / target index) */
    int dz; /* s0: height delta / flap magnitude, then the pull magnitude */
    if (moby->m_Class == 0x12C) {
      whirlTop = ((int *)moby->m_Props)[1];
    } else {
      whirlTop = 0x500;
    }
    if (g_Spyro.m_Position.z < D_80075668 + 0x400) {
      /* close to the floor target: damp straight onto unk_0x17c */
      reach = g_Spyro.m_Physics.unk_0xe8.z + 0x80;
      if (reach >= 0x12C1) {
        reach = 0x12C0;
      }
      VecCopy(&vTmp8, &g_Spyro.unk_0x17c);
      g_Spyro.m_walkingState = 0;
      g_Spyro.m_Physics.unk_0x144 = 0x400;
      t = g_Spyro.m_Position.z - D_80075668;
      t = ((t * t) >> 11) + D_8007578C;
    } else if (g_Spyro.m_Position.z < g_Spyro.m_highestFlightPoint - 0x400) {
      /* wing-flap upward toward the flight ceiling */
      if (g_Spyro.m_walkingState <= 0) {
        g_Spyro.m_walkingState = 1;
        D_8007578C += 0x200;
      }
      dz = (g_Spyro.m_Position.z - D_80075668) - 0x400;
      g_Spyro.m_Physics.unk_0x144 = 0xC80;
      t = D_8007578C + (D_800757F0 * dz) / D_80075724;
      t = (t + ((dz << 10) >> 10)) & 0xFFF;
      reach = 0x12C0;
      if (whirlTop < dz) {
        dz = whirlTop;
      }
      vTmp8.x = (dz * Cos(g_Spyro.m_Physics.m_SpeedAngle.m_RotZ)) >> 12;
      vTmp8.y = (dz * Sin(g_Spyro.m_Physics.m_SpeedAngle.m_RotZ)) >> 12;
      VecAdd(&vTmp8, &vTmp8, &g_Spyro.unk_0x17c);
      goto case17_merge;
    } else {
      /* steer toward the moby's facing direction */
      t = (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ -
           (g_Spyro.m_mobyInUseBySpyro->m_Rotation.z << 4)) &
          0xFFF;
      dz = whirlTop;
      if (t >= 0x801) {
        t -= 0x1000;
      }
      if (ABS(t) < 0x100) {
        dz += 0x800;
      }
      vTmp8.x = (dz * Cos(g_Spyro.m_Physics.m_SpeedAngle.m_RotZ)) >> 12;
      vTmp8.y = (dz * Sin(g_Spyro.m_Physics.m_SpeedAngle.m_RotZ)) >> 12;
      VecAdd(&vTmp8, &vTmp8, &g_Spyro.unk_0x17c);
      t = g_Spyro.m_highestFlightPoint - g_Spyro.m_Position.z;
      reach = (t * 0x12C0) >> 10;
      t = (g_Spyro.m_mobyInUseBySpyro->m_Rotation.z << 4) - ((t * t) >> 11);
      g_Spyro.m_Physics.unk_0x144 = 0xC80;
    }
  case17_merge:
    vTmp8.z = 0;
    VecSub(&vTmp8, &vTmp8, &g_Spyro.m_Position);
    dz = VecMagnitude(&vTmp8, 0);
    if (g_Spyro.m_Physics.unk_0x144 < dz) {
      VecScaleToLength(&vTmp8, dz, g_Spyro.m_Physics.unk_0x144);
    }
    VecCopy(&g_Spyro.m_Physics.unk_0xe8, &vTmp8);
    VecCopy(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.unk_0xe8);
    g_Spyro.m_Physics.unk_0xe8.z = reach;
    g_Spyro.m_Physics.m_Acceleration.z = reach;
    g_Spyro.m_Physics.m_SpeedAngle.m_RotZ = t & 0xFFF;
    goto epilogue;
    }

  case 19: /* updraft / whirlwind: damp drift toward zero, then accumulate */
    if (--g_Spyro.m_invulverabilityTimer < 0) {
      g_Spyro.m_invulverabilityTimer = 0;
    }
    TurnBodyToVelocity(0x8, 0x4);
    if (g_Spyro.m_slopeAngle < 0x17) {
      VecNull(&vTmp4);
      VecSub(&vTmp4, &vTmp4, &g_Spyro.m_Physics.unk_0xe8);
      {
        int damp = VecMagnitude(&vTmp4, 1);
        if (damp >= 0x101) {
          VecScaleToLength(&vTmp4, damp, 0x100);
        }
      }
      VecAdd(&g_Spyro.m_Physics.unk_0xe8, &g_Spyro.m_Physics.unk_0xe8, &vTmp4);
    }
    VecAdd(&g_Spyro.m_Physics.unk_0xe8, &g_Spyro.m_Physics.unk_0xe8,
           (Vector3D *)&g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotY);
    {
      int speed = VecMagnitude(&g_Spyro.m_Physics.unk_0xe8, 1);
      g_Spyro.m_Physics.m_SpeedAngle.m_Speed = speed;
      if (speed >= 0x2301) {
        VecScaleToLength(&g_Spyro.m_Physics.unk_0xe8, speed, 0x2300);
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0x2300;
      }
    }
    VecAdd(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.unk_0xe8,
           &g_Spyro.m_Physics.unk_0xdc);
    goto epilogue;

  case 20: /* flying-level steering: camera-relative turn + altitude spring */
    if (--g_Spyro.m_invulverabilityTimer < 0) {
      g_Spyro.m_invulverabilityTimer = 0;
    }
    if (g_ActivePad->m_LeftStickMoved != 0) {
      stickX = g_ActivePad->m_Sticks.m_LeftX - 0x7F;
      stickY = 0x7F - g_ActivePad->m_Sticks.m_LeftY;
    } else {
      if (g_ActivePad->m_Released & 0x1000) {
        stickY = 0x7F;
      } else {
        stickY = (g_ActivePad->m_Released & 0x4000) ? -0x7F : 0;
      }
      if (g_ActivePad->m_Released & 0x2000) {
        stickX = 0x7F;
      } else {
        stickX = (g_ActivePad->m_Released & 0x8000) ? -0x7F : 0;
      }
    }
    {
      int angle = (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ - g_Camera.m_Rotation.z) & 0xFFF;
      int cosV = Cos(angle);
      int sinV = Sin(angle);
      g_Spyro.m_Physics.m_TurnMomentum = ((-stickX * cosV) - (stickY * sinV)) >> 13;
    }
    if (g_Spyro.m_Physics.m_TurnMomentum < D_8006C704[0]) {
      g_Spyro.m_Physics.m_TurnMomentum = D_8006C704[0];
    }
    if (D_8006C704[12] < g_Spyro.m_Physics.m_TurnMomentum) {
      g_Spyro.m_Physics.m_TurnMomentum = D_8006C704[12];
    }
    func_8003D52C(g_Spyro.m_Physics.m_TurnMomentum);
    if (g_Spyro.m_walkingState & 0x40) {
      int climb = g_Spyro.m_highestFlightPoint - g_Spyro.m_Position.z;
      if (climb < 0) {
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
            g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed - func_80017A38((-climb) << 13);
      } else {
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
            g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed +
            func_80017A38(climb << 13);
      }
      if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >= 0x5901) {
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0x5900;
      }
      g_Spyro.m_Physics.m_Acceleration.x =
          (g_Spyro.m_Physics.m_SpeedAngle.m_Speed *
           Cos(g_Spyro.m_Physics.m_SpeedAngle.m_RotZ)) >> 12;
      g_Spyro.m_Physics.m_Acceleration.y =
          (g_Spyro.m_Physics.m_SpeedAngle.m_Speed *
           Sin(g_Spyro.m_Physics.m_SpeedAngle.m_RotZ)) >> 12;
      VecCopy(&g_Spyro.m_Physics.unk_0xe8, &g_Spyro.m_Physics.m_Acceleration);
    } else {
      g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed = 0x1E00;
      func_8003D92C(0x240, 0x180);
      g_Spyro.m_Physics.m_Acceleration.x =
          (g_Spyro.m_Physics.m_SpeedAngle.m_Speed *
           Cos(g_Spyro.m_Physics.m_SpeedAngle.m_RotZ)) >> 12;
      g_Spyro.m_Physics.m_Acceleration.y =
          (g_Spyro.m_Physics.m_SpeedAngle.m_Speed *
           Sin(g_Spyro.m_Physics.m_SpeedAngle.m_RotZ)) >> 12;
    }
    if (g_Spyro.m_againstWall != 0) {
      g_Spyro.m_wallAgainstSpyro.z = 0;
      func_80017330(&g_Spyro.m_wallAgainstSpyro, 0x1000);
      {
        int push =
            (-g_Spyro.m_Physics.m_Acceleration.x *
                 g_Spyro.m_wallAgainstSpyro.x -
             g_Spyro.m_Physics.m_Acceleration.y *
                 g_Spyro.m_wallAgainstSpyro.y) >>
            12;
        if (push > 0) {
          VecScaleToLength(&g_Spyro.m_wallAgainstSpyro, 0x1000, push);
          VecAdd(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.m_Acceleration,
                 &g_Spyro.m_wallAgainstSpyro);
        }
      }
    }
    g_Spyro.m_Physics.m_Acceleration.z -= 0xC0;
    if (g_Spyro.m_Physics.m_Acceleration.z < -0x2300) {
      g_Spyro.m_Physics.m_Acceleration.z = -0x2300;
    }
    goto epilogue;

  case 24: /* flying-level glide: camera-relative turn, gravity glide */
    if (--g_Spyro.m_invulverabilityTimer < 0) {
      g_Spyro.m_invulverabilityTimer = 0;
    }
    if (g_ActivePad->m_LeftStickMoved != 0) {
      stickX = g_ActivePad->m_Sticks.m_LeftX - 0x7F;
      stickY = 0x7F - g_ActivePad->m_Sticks.m_LeftY;
    } else {
      if (g_ActivePad->m_Released & 0x1000) {
        stickY = 0x7F;
      } else {
        stickY = (g_ActivePad->m_Released & 0x4000) ? -0x7F : 0;
      }
      if (g_ActivePad->m_Released & 0x2000) {
        stickX = 0x7F;
      } else {
        stickX = (g_ActivePad->m_Released & 0x8000) ? -0x7F : 0;
      }
    }
    {
      int angle = (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ - g_Camera.m_Rotation.z) & 0xFFF;
      int cosV = Cos(angle);
      int sinV = Sin(angle);
      g_Spyro.m_Physics.m_TurnMomentum = ((-stickX * cosV) - (stickY * sinV)) >> 13;
    }
    if (g_Spyro.m_Physics.m_TurnMomentum < D_8006C704[0]) {
      g_Spyro.m_Physics.m_TurnMomentum = D_8006C704[0];
    }
    if (D_8006C704[12] < g_Spyro.m_Physics.m_TurnMomentum) {
      g_Spyro.m_Physics.m_TurnMomentum = D_8006C704[12];
    }
    func_8003D52C(g_Spyro.m_Physics.m_TurnMomentum);
    g_Spyro.m_Physics.m_Acceleration.x =
        (g_Spyro.m_Physics.m_SpeedAngle.m_Speed *
         Cos(g_Spyro.m_Physics.m_SpeedAngle.m_RotZ)) >> 12;
    g_Spyro.m_Physics.m_Acceleration.y =
        (g_Spyro.m_Physics.m_SpeedAngle.m_Speed *
         Sin(g_Spyro.m_Physics.m_SpeedAngle.m_RotZ)) >> 12;
    VecCopy(&g_Spyro.m_Physics.unk_0xe8, &g_Spyro.m_Physics.m_Acceleration);
    if (g_Spyro.m_idleTimer >= 5) {
      g_Spyro.m_Physics.m_Acceleration.z -= g_Spyro.m_Physics.m_gravity;
    }
    if (g_Spyro.m_Physics.m_Acceleration.z < -0x2300) {
      g_Spyro.m_Physics.m_Acceleration.z = -0x2300;
    }
    goto epilogue;

  case 26: { /* cannon / whirlwind ride: orbit the moby in use */
    CannonProps *props = (CannonProps *)g_Spyro.m_mobyInUseBySpyro->m_Props;
    CannonProps *rideProps = (CannonProps *)g_Spyro.m_mobyInUseBySpyro->m_Props;
    int dz;
    if (--g_Spyro.m_invulverabilityTimer < 0) {
      g_Spyro.m_invulverabilityTimer = 0;
    }
    VecSub(&vTmp7, &g_Spyro.m_mobyInUseBySpyro->m_Position, &g_Spyro.m_Position);
    {
    int dist = VecMagnitude(&vTmp7, 0);
    angle = Atan2(vTmp7.x, vTmp7.y, 1);
    if (g_Spyro.m_walkingState == 1) {
      dz = -D_800758A0 >> 6;
    } else {
      dz = D_800758A0 >> 6;
    }
    func_8003D3B8(0x280);
    UpdateSpyroTurnMomentum(0);
    D_800758A0 += 0x20;
    if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed < D_800758A0) {
      D_800758A0 = g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed;
    }
    angle = (angle + dz + 0x800) & 0xFFF;
    if (g_Spyro.m_mobyInUseBySpyro->m_Class == 0xFF) {
      rideProps->m_SpinAngle = (rideProps->m_SpinAngle + dz) & 0xFFF;
      g_Spyro.m_mobyInUseBySpyro->m_Rotation.z = rideProps->m_SpinAngle >> 4;
    } else {
      props->m_SpinAngle = (props->m_SpinAngle + dz) & 0xFFF;
      g_Spyro.m_mobyInUseBySpyro->m_Rotation.z = props->m_SpinAngle >> 4;
    }
    vTmp7.x = (dist * Cos(angle)) >> 12;
    vTmp7.y = (dist * Sin(angle)) >> 12;
    }
    VecAdd(&vTmp7, &vTmp7, &g_Spyro.m_mobyInUseBySpyro->m_Position);
    VecSub(&vTmp7, &vTmp7, &g_Spyro.m_Position);
    vTmp7.z = 0;
    VecShiftLeft(&vTmp7, 6);
    VecCopy(&g_Spyro.m_Physics.m_Acceleration, &vTmp7);
    g_Spyro.m_Physics.m_SpeedAngle.m_RotZ =
        (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ + dz) & 0xFFF;
    if (g_Spyro.m_onEdge != 0) {
      g_Spyro.m_Physics.m_Acceleration.z -= 0xC0;
      goto epilogue;
    }
    VecAdd(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.m_Acceleration,
           &g_Spyro.m_Physics.unk_0xdc);
    goto epilogue;
  }

  case 22: /* glide knockback: drag accel back, settle */
  case 28:
    VecNull(&vTmp6);
    VecSub(&vTmp6, &vTmp6, &g_Spyro.m_Physics.m_Acceleration);
    if (g_Spyro.m_airTime != 0) {
      vTmp6.z = 0;
      {
        int drag = VecMagnitude(&vTmp6, 0);
        if (drag >= 0x41) {
          VecScaleToLength(&vTmp6, drag, 0x40);
        }
      }
      vTmp6.z = -0xC0;
      VecAdd(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.m_Acceleration, &vTmp6);
    } else {
      int drag = VecMagnitude(&vTmp6, 1);
      if (drag >= 0x101) {
        VecScaleToLength(&vTmp6, drag, 0x100);
      }
      VecAdd(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.m_Acceleration, &vTmp6);
      VecAdd(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.m_Acceleration,
             &g_Spyro.m_Physics.unk_0xdc);
    }
  tail_clamp_fall:
    if (g_Spyro.m_Physics.m_Acceleration.z < -0x2300) {
      g_Spyro.m_Physics.m_Acceleration.z = -0x2300;
    }
    goto epilogue;

  case 29: /* clear acceleration */
  clear_accel:
    VecNull(&g_Spyro.m_Physics.m_Acceleration);
    goto epilogue;

  case 30: case 31: /* drift: decay momentum 1/16, settle onto floor */
    g_Spyro.m_Physics.unk_0xe8.x -= g_Spyro.m_Physics.unk_0xe8.x >> 4;
    g_Spyro.m_Physics.unk_0xe8.y -= g_Spyro.m_Physics.unk_0xe8.y >> 4;
    g_Spyro.m_Physics.unk_0xe8.z -= g_Spyro.m_Physics.unk_0xe8.z >> 4;
    VecCopy(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.unk_0xe8);
    if (g_Spyro.m_onEdge != 0 || g_Spyro.m_airTime != 0) {
      g_Spyro.m_Physics.m_Acceleration.z = g_Spyro.m_Physics.m_TrueVelocity.z - 0xC0;
      goto epilogue;
    }
  tail_velocity:
    VecAdd(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.m_Acceleration,
           &g_Spyro.m_Physics.unk_0xdc);
    goto epilogue;

  case 8: /* superfly: tick the invulnerability timer */
  case 35:
    if (--g_Spyro.m_invulverabilityTimer < 0) {
      g_Spyro.m_invulverabilityTimer = 0;
    }
    goto epilogue;

  case 44: /* superfly steer: dpad/analog turn momentum + altitude spring */
    if (--g_Spyro.m_invulverabilityTimer < 0) {
      g_Spyro.m_invulverabilityTimer = 0;
    }
    if (g_ActivePad->m_LeftStickMoved != 0) {
      g_Spyro.m_Physics.m_TurnMomentum =
          (0x7F - g_ActivePad->m_Sticks.m_LeftX) >> 1;
      if (g_Spyro.m_Physics.m_TurnMomentum < D_8006C704[0]) {
        g_Spyro.m_Physics.m_TurnMomentum = D_8006C704[0];
      } else if (D_8006C704[12] < g_Spyro.m_Physics.m_TurnMomentum) {
        g_Spyro.m_Physics.m_TurnMomentum = D_8006C704[12];
      }
      func_8003D52C(g_Spyro.m_Physics.m_TurnMomentum);
    } else {
      if (g_ActivePad->m_Released & 0x8000) {
        if (g_Spyro.m_Physics.m_TurnMomentum < 0) {
          g_Spyro.m_Physics.m_TurnMomentum = 0;
        }
        if (g_Spyro.m_Physics.m_TurnMomentum < 6) {
          g_Spyro.m_Physics.m_TurnMomentum += 1;
        }
      } else if (g_ActivePad->m_Released & 0x2000) {
        if (g_Spyro.m_Physics.m_TurnMomentum > 0) {
          g_Spyro.m_Physics.m_TurnMomentum = 0;
        }
        if (g_Spyro.m_Physics.m_TurnMomentum >= -5) {
          g_Spyro.m_Physics.m_TurnMomentum -= 1;
        }
      } else {
        g_Spyro.m_Physics.m_TurnMomentum = 0;
      }
      pClamp = D_8006C704;
      func_8003D52C(pClamp[6 + g_Spyro.m_Physics.m_TurnMomentum]);
    }
    {
      int climb = g_Spyro.m_highestFlightPoint - g_Spyro.m_Position.z;
      if (climb < 0) {
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
            g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed -
            func_80017A38(-climb << 13);
      } else {
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
            g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed + func_80017A38(climb << 13);
      }
    }
    if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >= 0x5901) {
      g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0x5900;
    }
    if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0x1400) {
      g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed = 0x1400;
      g_Spyro.m_highestFlightPoint = g_Spyro.m_Position.z;
    }
    func_8003D978();
    VecCopy(&g_Spyro.m_Physics.unk_0xe8, &g_Spyro.m_Physics.m_Acceleration);
    if (g_Spyro.m_airTime == 0) {
      VecAdd(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.m_Acceleration,
             &g_Spyro.m_Physics.unk_0xdc);
    }
    D_8007584C = ((g_Spyro.m_Physics.m_SpeedAngle.m_Speed - 0x1400) >> 7) + 0x14;
    if (D_8007584C < 0x50) {
      D_8007584C = 0x50;
    }
    if (D_8007584C >= 0xA1) {
      D_8007584C = 0xA0;
    }
    if (D_800757D0 < 4) {
      D_800757D0 = 4;
    }
    goto epilogue;

  default:
    /* Remaining states (gliding 0x0B/0x14/0x15, whirlwind 0x19, superfly 0x10
       /0x16-0x23, etc.) carry large bodies that are still being reversed.
       They fall through to the common velocity-accumulation epilogue so the
       baseline at least models the shared tail faithfully. */
    goto epilogue;
  }

epilogue:
  /* Roll this frame's acceleration into the velocity, then snapshot the body
     rotation bytes (12-bit speed angles >> 4) for the renderer. */
  VecAdd(&g_Spyro.m_Physics.m_Velocity, &g_Spyro.m_Physics.m_Velocity,
         &g_Spyro.m_Physics.m_Acceleration);
  g_Spyro.m_bodyRotation.x = g_Spyro.m_Physics.m_SpeedAngle.m_RotX >> 4; /* 0xC */
  g_Spyro.m_bodyRotation.y = g_Spyro.m_Physics.m_SpeedAngle.m_RotY >> 4; /* 0xD */
  g_Spyro.m_bodyRotation.z = g_Spyro.m_Physics.m_SpeedAngle.m_RotZ >> 4; /* 0xE */
}

/// @brief Per-frame state dispatch for Spyro
void func_80047B60(void);
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80047B60);

void func_8003DAE4(void);

/// @brief Rotation updates for Spyro
void func_8004888C(void) {

  switch (g_Spyro.m_State) {
  case 6:
    RotateSpyroToNeutral();
    break;
  case 1:
    func_8003DAE4();
    if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed != 0) {

      if (g_Spyro.m_againstWall != 0) {
        g_Spyro.m_bodyAnimationSpeed = 4;
      } else {
        g_Spyro.m_bodyAnimationSpeed =
            g_Spyro.m_Physics.m_SpeedAngle.m_Speed >> 7;
      }

      if (g_Spyro.m_bodyAnimationSpeed < 1) {
        g_Spyro.m_bodyAnimationSpeed = 1;
      }

      if (g_Spyro.m_bodyAnimationSpeed > 16) {
        g_Spyro.m_bodyAnimationSpeed = 16;
      }

    } else {
      g_Spyro.m_bodyAnimationSpeed = 4;
      if (D_80075914 & 0x10 && !(g_Camera.unk_0xC0 & 0x80000000)) {
        g_Camera.unk_0xC0 = 0x80000000;
      }
    }
    break;
  case 5:
    func_8003DAE4();
    if (g_Spyro.m_bodyTransitionType == 0) {
      if (g_Spyro.m_walkingState == 0) {
        if (g_Spyro.m_nextBodyAnimationFrame < 3) {
          g_Spyro.m_bodyAnimationSpeed = 4;
        } else if (g_Spyro.m_nextBodyAnimationFrame < 6) {
          g_Spyro.m_bodyAnimationSpeed = 2;
        } else {
          g_Spyro.m_bodyAnimationSpeed = 0;
        }
      } else if (g_Spyro.m_nextBodyAnimationFrame < 8) {
        g_Spyro.m_bodyAnimationSpeed = 2;
      } else {
        g_Spyro.m_bodyAnimationSpeed = 0;
      }
    }
    break;
  case 11:
    func_8003DAE4();
    if ((g_Spyro.m_walkingState & 1) && g_Spyro.m_touchingMoby != 0) {
      g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 2560;
    }
    break;
  case 19:
    func_8003DAE4();
    g_Spyro.m_bodyAnimationSpeed =
        (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >> 11) + 3;

    if (g_Spyro.m_bodyAnimationSpeed < 4) {
      g_Spyro.m_bodyAnimationSpeed = 4;
    }

    if (g_Spyro.m_bodyAnimationSpeed > 12) {
      g_Spyro.m_bodyAnimationSpeed = 12;
    }
    break;
  case 20:
    RotateSpyroToAcceleration();
    break;
  case 21:
    func_8003DAE4();
    g_Spyro.m_bodyAnimationSpeed =
        ((g_Spyro.m_Physics.m_SpeedAngle.m_Speed - 0x640) >> 9) + 6;
    if (g_Spyro.m_bodyAnimationSpeed < 6) {
      g_Spyro.m_bodyAnimationSpeed = 6;
    }
    if (g_Spyro.m_bodyAnimationSpeed > 16) {
      g_Spyro.m_bodyAnimationSpeed = 16;
    }
    break;
  case 44:
    if (g_Spyro.m_airTime != 0) {
      break;
    }
    /* fallthrough */
  case 0:
  case 2:
  case 3:
  case 4:
  case 7:
  case 8:
  case 9:
  case 10:
  case 12:
  case 13:
  case 14:
  case 16:
  case 17:
  case 18:
  case 22:
  case 25:
  case 26:
  case 27:
  case 28:
  case 29:
  case 30:
  case 31:
  case 35:
  case 36:
  case 37:
  case 38:
  case 39:
  case 40:
  case 41:
  case 42:
  case 43:
    func_8003DAE4();
    break;
  case 24:
    RotateSpyroToAcceleration();
    g_Spyro.m_Physics.m_gravity += 12;
    if (g_Spyro.m_Physics.m_gravity > 192) {
      g_Spyro.m_Physics.m_gravity = 192;
    }
    break;
  default:
    break;
  }

  g_Spyro.m_idleTimer++;
}

/**
 * @brief Main per-frame update for Spyro's physics and surface interactions.
 *
 * This function is called every frame to update Spyro's state by:
 * 1. Resetting m_Velocity to zero before physics calculations
 * 2. Running state physics (func_80043FE4) for each delta time substep
 * 3. Running per-frame state dispatch (func_80047B60)
 * 4. Running rotation updates (func_8004888C) for each delta time substep
 * 5. Handling special surface interactions via ApplySpecialSurfaceEffects
 *
 * Surface interaction priority (handled in order):
 * - If grounded (m_airTime == 0) and close to surface below: mode 2
 * - If touching a special surface (m_touchingSurface): mode 0
 * - If surface exists below Spyro: mode 1
 *
 * Surface flags use the lower 6 bits (& 0x3F), where 0x3F means "no special
 * surface".
 */
void UpdateSpyroPhysicsAndSurfaces(void) {
  int i;
  int surfaceBelow;
  int surfaceFlag;
  int touchingLow;

  // Reset velocity vector before physics substeps recalculate it
  VecNull(&g_Spyro.m_Physics.m_Velocity);

  // Run physics state update for each delta time substep
  for (i = 0; i < g_DeltaTime; i++) {
    func_80043FE4(i);
  }

  // Run per-frame state dispatch (handles state-specific logic)
  func_80047B60();

  // Run rotation updates for each delta time substep
  for (i = 0; i < g_DeltaTime; i++) {
    func_8004888C();
  }

  // Skip surface interaction handling if CTRL_SKIP_SURFACE_CHECK is set
  if (g_Spyro.m_ControlFlags & CTRL_SKIP_SURFACE_CHECK) {
    return;
  }

  // Query the surface height below Spyro (max search depth 0x10000)
  surfaceBelow = func_8004D5EC(&g_Spyro.m_Position, 0x10000);
  g_Spyro.m_surfaceBelowSpyro = surfaceBelow;
  g_Spyro.m_SurfaceProximityState = 0;

  // Grounded and close to special surface below
  // If Spyro is grounded and within 512 units of the surface, trigger mode 2
  if (g_Spyro.m_airTime == 0) {
    surfaceFlag = g_SurfaceBelowFlags & 0x3F;
    if (surfaceFlag != 0x3F && g_Spyro.m_Position.z - surfaceBelow <= 512) {
      ApplySpecialSurfaceEffects(surfaceFlag, 2);
      return;
    }
  }

  // Currently touching a special surface
  // Lower 6 bits of m_touchingSurface indicate surface type
  touchingLow = g_Spyro.m_touchingSurface & 0x3F;
  if (touchingLow != 0x3F) {
    ApplySpecialSurfaceEffects(touchingLow, 0);
    return;
  }

  // Surface exists below Spyro (surfaceBelow > 0)
  if (g_Spyro.m_surfaceBelowSpyro <= 0) {
    return;
  }

  // Check if surface below has special properties
  surfaceFlag = g_SurfaceBelowFlags & 0x3F;
  if (surfaceFlag == 0x3F) {
    return;
  }

  // Trigger surface interaction mode 1 (above special surface)
  ApplySpecialSurfaceEffects(surfaceFlag, 1);
}

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80048D10);

/// @brief Increments the head animation
void func_800495D8(int pDeltaTime) {
  g_Spyro.m_headFrameProgress += pDeltaTime;

  if (g_Spyro.m_headFrameProgress >= 16) {
    g_Spyro.m_headFrameProgress -= 16;

    g_Spyro.m_headAnimation = g_Spyro.m_nextHeadAnimation;
    g_Spyro.m_headAnimationFrame = g_Spyro.m_nextHeadAnimationFrame;

    g_Spyro.m_nextHeadAnimationFrame++;

    if (spyro_AnimationDetails[g_Spyro.m_nextHeadAnimation]
            .m_TransitionLastFrame <= g_Spyro.m_nextHeadAnimationFrame) {
      g_Spyro.m_nextHeadAnimationFrame =
          spyro_AnimationDetails[g_Spyro.m_nextHeadAnimation]
              .m_TransitionLastFrame -
          1;
    }
  }
}

extern u_char D_80075264[2][2];
extern u_char D_80075268[4];

/// @brief Update the head animation, handling mismatched body and head
/// animations
void func_80049660(void) {
  switch (g_Spyro.unk_0x60) {
  case 0:
    if (g_Spyro.unk_0x198 == g_Spyro.unk_0x68) {
      if (g_Spyro.unk_0x198 == 0) {
        g_Spyro.m_headAnimation = g_Spyro.m_bodyAnimation;
        g_Spyro.m_headAnimationFrame = g_Spyro.m_bodyAnimationFrame;
        g_Spyro.m_nextHeadAnimation = g_Spyro.m_nextBodyAnimation;
        g_Spyro.m_nextHeadAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;
        g_Spyro.m_headFrameProgress = g_Spyro.m_bodyFrameProgress;
        return;
      }
      func_800495D8(g_Spyro.m_headAnimationSpeed);
      return;
    }

    switch (D_80075264[g_Spyro.unk_0x68][g_Spyro.unk_0x198]) {
    case 2:
      g_Spyro.unk_0x60 = D_80075264[g_Spyro.unk_0x68][g_Spyro.unk_0x198];
      g_Spyro.m_headAnimation = g_Spyro.m_nextHeadAnimation;
      g_Spyro.m_headAnimationFrame = g_Spyro.m_nextHeadAnimationFrame;
      g_Spyro.m_nextHeadAnimation = D_80075268[g_Spyro.unk_0x198];
      g_Spyro.m_nextHeadAnimationFrame = 0;
      g_Spyro.m_headFrameProgress = 4;
      g_Spyro.unk_0x68 = g_Spyro.unk_0x198;
      return;
    case 1:
      g_Spyro.unk_0x60 = D_80075264[g_Spyro.unk_0x68][g_Spyro.unk_0x198];
      g_Spyro.m_headAnimation = g_Spyro.m_nextHeadAnimation;
      g_Spyro.m_headAnimationFrame = g_Spyro.m_nextHeadAnimationFrame;
      g_Spyro.m_nextHeadAnimation = g_Spyro.m_nextBodyAnimation;
      g_Spyro.m_nextHeadAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;
      g_Spyro.m_headFrameProgress = 2;
      g_Spyro.unk_0x68 = g_Spyro.unk_0x198;
      return;
    }
    break;
  case 2:
    g_Spyro.m_headFrameProgress += 4;
    if (g_Spyro.m_headFrameProgress >= 16) {
      func_800495D8(0);
      g_Spyro.unk_0x60 = 0;
    }
    break;
  case 1:
    g_Spyro.m_headFrameProgress += 2;
    if (g_Spyro.m_headFrameProgress >= 16) {
      func_800495D8(0);
      g_Spyro.unk_0x60 = 0;
    }
  }
}

/// @brief Eases Spyro's head rotation toward m_HeadLookTarget using a per-axis
/// spring-damper. The smoothed result is written to the real head rotation,
/// which lives at m_bodyRotation + 4 (one padding byte ahead of the struct's
/// m_headRotation), the same location consumed by the head rotation matrix.
void func_80049880(void) {
  int delta;

  // Per axis: take the angle delta to the target, wrap it to the shortest
  // signed direction, integrate it into a velocity accumulator, then advance
  // the current angle by that velocity.
  delta = (g_Spyro.m_HeadLookTarget.x - g_Spyro.unk_0x1b0) & 0xFFF;
  if (delta > 2048) {
    delta -= 4096;
  }
  g_Spyro.unk_0x1bc += ((delta << 7) - (g_Spyro.unk_0x1bc << 4)) >> 6;
  g_Spyro.unk_0x1b0 += g_Spyro.unk_0x1bc >> 6;

  delta = (g_Spyro.m_HeadLookTarget.y - g_Spyro.unk_0x1b4) & 0xFFF;
  if (delta > 2048) {
    delta -= 4096;
  }
  g_Spyro.unk_0x1c0 += ((delta << 7) - (g_Spyro.unk_0x1c0 << 4)) >> 6;
  g_Spyro.unk_0x1b4 += g_Spyro.unk_0x1c0 >> 6;

  delta = (g_Spyro.m_HeadLookTarget.z - g_Spyro.unk_0x1b8) & 0xFFF;
  if (delta > 2048) {
    delta -= 4096;
  }

  g_Spyro.unk_0x1c4 += ((delta << 7) - (g_Spyro.unk_0x1c4 << 4)) >> 6;
  g_Spyro.unk_0x1b8 += g_Spyro.unk_0x1c4 >> 6;

  // The rotation bytes are the current angles scaled down by 16.
  g_Spyro.m_headRotation.x = g_Spyro.unk_0x1b0 >> 4;
  g_Spyro.m_headRotation.y = g_Spyro.unk_0x1b4 >> 4;
  g_Spyro.m_headRotation.z = g_Spyro.unk_0x1b8 >> 4;
}

// Particle direction vector, start offset and end offset for flame particles
extern Vector3D D_8006E238[4];

/// @brief Update flame
void func_800499C0(void) {
  if (spyro_FlameBlockedInAnimation
          [spyro_StateDefaultAnimation[g_Spyro.m_State]]) {
    g_Spyro.unk_0x198 = 0;
    VecNull(&g_Spyro.m_HeadLookTarget);
    func_80049880();
    return;
  }

  switch (g_Spyro.unk_0x198) {
  case 0:
    g_SpyroFlame.unk_99[1] = 0;
    if ((g_Pad.m_Down & PAD_CIRCLE) && g_SpyroFlame.m_IsFlameActive == 0) {
      int headSpeed;

      g_Spyro.unk_0x198 = 1;
      g_Spyro.unk_0x1a0 = -1;
      g_Spyro.unk_0x60 = 0;

      headSpeed =
          spyro_AnimationDetails[D_80075268[g_Spyro.unk_0x198]].m_FrameRate;
      g_SpyroFlame.m_IsFlameActive = 1;
      g_Spyro.m_headAnimationSpeed = headSpeed;
      g_SpyroFlame.unk_99[0] = 0;
      g_SpyroFlame.unk_99[1] = 1;
      g_SpyroFlame.unk_99[2] = rand() & 1;

      if (g_SpyroFlame.m_FairyKissTimer != 0) {
        g_SpyroFlame.unk_9c = 1;
      } else {
        g_SpyroFlame.unk_9c = 0;
      }

      Memset(&g_SpyroFlame.unk_20, 0, 8);
      VecNull(&g_Spyro.m_HeadLookTarget);
    }
    break;
  case 1:
    if (g_Spyro.unk_0x1a0 == 16) {
      g_SpyroFlame.unk_99[1] = 0;
    }

    if ((g_Spyro.unk_0x1a0 & 3) == 0 && g_Spyro.unk_0x1a0 >= 12 &&
        g_Spyro.unk_0x1a0 <= 28 && g_LoadStage < 0) {
      Vector3D particleStart;
      Vector3D direction;

      VecRotateByMatrix(&g_Spyro.m_headRotationMatrix, &D_8006E238[0],
                        &particleStart);
      VecAdd(&particleStart, &particleStart, &g_Spyro.m_Position);
      VecRotateByLastMatrix(&D_8006E238[2], &direction);

      if (g_SpyroFlame.unk_9c != 0) {
        D_800758E4(1, 1, &particleStart, &direction);
      } else {
        D_800758E4(1, 0, &particleStart, &direction);
      }

      VecRotateByMatrix(&g_Spyro.m_headRotationMatrix, &D_8006E238[1],
                        &particleStart);
      VecAdd(&particleStart, &particleStart, &g_Spyro.m_Position);
      VecRotateByLastMatrix(&D_8006E238[3], &direction);

      if (g_SpyroFlame.unk_9c != 0) {
        D_800758E4(1, 1, &particleStart, &direction);
      } else {
        D_800758E4(1, 0, &particleStart, &direction);
      }
    } else if ((g_Pad.m_Down & PAD_CIRCLE) && g_Spyro.unk_0x1a0 >= 44) {
      g_Spyro.unk_0x1a0 = -1;
      g_Spyro.unk_0x60 = 2;
      g_Spyro.m_headFrameProgress = 4;
      g_Spyro.m_nextHeadAnimationFrame = 0;
      g_SpyroFlame.m_IsFlameActive = 1;
      g_SpyroFlame.unk_99[0] = 0;
      g_SpyroFlame.unk_99[1] = 1;
      g_SpyroFlame.unk_99[2] = rand() & 1;

      if (g_SpyroFlame.m_FairyKissTimer != 0) {
        g_SpyroFlame.unk_9c = 1;
      } else {
        g_SpyroFlame.unk_9c = 0;
      }

      Memset(&g_SpyroFlame.unk_20, 0, 8);
    } else if (g_Spyro.unk_0x1a0 >= 48) {
      g_SpyroFlame.m_IsFlameActive = 0;
      Memset(&g_SpyroFlame.unk_20, 0, 8);
      g_Spyro.unk_0x198 = 0;
      g_Spyro.unk_0x1a0 = -1;
      g_Spyro.m_headAnimationSpeed =
          spyro_AnimationDetails[D_80075268[0]].m_FrameRate;
      VecNull(&g_Spyro.m_HeadLookTarget);
    }
    break;
  default:
    if (g_Camera.m_State != 0x80000009) {
      VecNull(&g_Spyro.m_HeadLookTarget);
    }
    break;
  }

  g_Spyro.unk_0x1a0++;
  func_80049880();
}

/// @brief Updates the tail animation
void func_80049DFC(int pAnimationSpeed) {
  g_Spyro.m_tailFrameProgress += pAnimationSpeed;

  if (g_Spyro.m_tailFrameProgress >= 16) {
    g_Spyro.m_tailFrameProgress -= 16;

    g_Spyro.m_tailAnimation = g_Spyro.m_nextTailAnimation;
    g_Spyro.m_tailAnimationFrame = g_Spyro.m_nextTailAnimationFrame;

    g_Spyro.m_nextTailAnimationFrame++;

    // SKELETON: This should be a >=, not a ==
    if (g_Spyro.m_nextTailAnimationFrame ==
        spyro_AnimationDetails[g_Spyro.m_nextTailAnimation].m_EndFrame) {
      g_Spyro.m_nextTailAnimationFrame =
          spyro_AnimationDetails[g_Spyro.m_nextTailAnimation].m_StartFrame;
    }
  }
}

/// @brief Update the tail animation
void func_80049E8C(void) {
  if (g_Spyro.unk_0x6C || g_Spyro.m_seperateTailAnimation != g_Spyro.unk_0x74)
    return;

  if (g_Spyro.m_seperateTailAnimation == 0) {
    // Copy the body
    g_Spyro.m_tailAnimation = g_Spyro.m_bodyAnimation;
    g_Spyro.m_tailAnimationFrame = g_Spyro.m_bodyAnimationFrame;
    g_Spyro.m_nextTailAnimation = g_Spyro.m_nextBodyAnimation;
    g_Spyro.m_nextTailAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;
    g_Spyro.m_tailFrameProgress = g_Spyro.m_bodyFrameProgress;
  } else {
    func_80049DFC(g_Spyro.m_tailAnimationSpeed);
  }
}

void func_80049F3C(void) {
  if (spyro_FlameBlockedInAnimation[g_Spyro.m_bodyAnimation] ||
      spyro_FlameBlockedInAnimation[g_Spyro.m_nextBodyAnimation]) {
    // I assume this is here to make it so flaming unblocks the animation
    g_Spyro.m_seperateTailAnimation = 0;

  } else {
    // SKELETON: Unused variable, never read, also never resets, so it's kinda
    // useless
    g_Spyro.m_flameableFrames++;
  }
}

void func_80049FAC(int);
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80049FAC);

extern int D_8006E9A4[TOTAL_LEVEL_COUNT]; // per-level surface-height threshold

void func_80048D10(int pDeltaTime);

/// @brief General Spyro update function
void func_8004A200(void) {
  int _padLo[8];
  int soundId[2]; // [0] = body anim sound id, [1] = head anim sound id
  int _padHi[2];
  int i;

  if ((g_Spyro.m_ControlFlags & 0x2000) || g_Spyro.unk_0x194 != 0) {
    if (g_Spyro.m_noGamepadUpdateFrames < 2) {
      g_Spyro.m_noGamepadUpdateFrames = 2;
    }
  }

  g_PadSwapFlag = 0;

  if (g_Spyro.m_noGamepadUpdateFrames != 0) {
    func_80053708(&g_Pad, &g_PadBackup);
    g_Spyro.m_noGamepadUpdateFrames--;
  }

  UpdateSpyroPhysicsAndSurfaces();

  if (g_Spyro.m_State == 29) {
    if (g_Spyro.m_drowningOffset <= 0) {
      g_Spyro.m_drowningOffset = 1;
    }
  } else {
    g_Spyro.m_drowningOffset = 0;
  }

  if (!(g_Spyro.m_ControlFlags & 0x100) && g_Spyro.unk_0x194 == 0) {
    func_80041670();
  }

  for (i = 0; i < g_DeltaTime; i++) {
    UpdateBodyAnimationState();
    func_800499C0();
    func_80049660();
    func_80049F3C();
    func_80049E8C();
  }

  g_Spyro.m_bodyRotation.x = g_Spyro.m_Physics.m_SpeedAngle.m_RotX >> 4;
  g_Spyro.m_bodyRotation.y = g_Spyro.m_Physics.m_SpeedAngle.m_RotY >> 4;
  g_Spyro.m_bodyRotation.z = g_Spyro.m_Physics.m_SpeedAngle.m_RotZ >> 4;

  RotVec8ToMatrix(&g_Spyro.m_bodyRotation, &g_Spyro.m_RotationMatrix, nullptr);
  RotVec8ToMatrix(&g_Spyro.m_headRotation, &g_Spyro.m_headRotationMatrix,
                  nullptr);
  MulMatrix0(&g_Spyro.m_RotationMatrix, &g_Spyro.m_headRotationMatrix,
             &g_Spyro.m_headRotationMatrix);
  func_80049FAC(1);
  func_80048D10(g_DeltaTime);

  g_Spyro.m_DamageFlags = 0;

  // Death animations
  if (g_Spyro.m_health < 0) {
    switch (g_Spyro.m_State) {
    case 29:
      if (g_Spyro.m_drowningOffset == 576) {
        if (g_IsFlightLevel) {
          (*D_80075694)();
          (*g_UpdateMoby)();
        } else {
          func_8002C85C();
        }
      }
      break;
    case 30:
      if (g_Spyro.m_idleTimer > 100) {
        func_8002C85C();
      }
      break;
    case 31:
      if (g_Spyro.m_idleTimer > 124) {
        func_8002C85C();
      }
      break;
    }
  } else if (g_Spyro.m_Position.z < 1024 ||
             // m_walkingState gets reused as a timer below
             (g_Spyro.m_State == 6 && g_Spyro.m_walkingState > 120)) {
    func_8002C85C();
  } else {
    if (g_Spyro.m_Position.z < D_8006E9A4[g_LevelIndex]) {
      if (g_Spyro.m_State != 6 && g_Spyro.m_State != 16) {
        func_8003EA68(6);
      }

      if (g_Spyro.m_walkingState == 0) {
        VecCopy(&D_8006EBCC.m_CameraPosition, &g_Camera.m_Position);
        func_80037714(&D_8006EBCC);
      }
      g_Spyro.m_walkingState += g_DeltaTime;
    } else if (g_Spyro.m_Position.x < 2048 || g_Spyro.m_Position.y < 2048) {
      if (g_Spyro.m_State != 6 && g_Spyro.m_State != 16) {
        VecNull(&g_Spyro.m_Physics.m_TrueVelocity);
        VecNull(&g_Spyro.m_Physics.m_Acceleration);
        func_8003EA68(6);
      }

      if (g_Spyro.m_walkingState == 0) {
        VecCopy(&D_8006EBCC.m_CameraPosition, &g_Camera.m_Position);
        func_80037714(&D_8006EBCC);
      }
      g_Spyro.m_walkingState += g_DeltaTime;
    }
  }

  // Spyro animation sound triggers

#define SPYRO_FRAME(anim, frame)                                               \
  ((SpyroAnimationFrame *)SPYRO_MODEL->m_Animations[anim]->m_Frames)[frame]

  // Body
  soundId[0] =
      SPYRO_FRAME(g_Spyro.m_bodyAnimation, g_Spyro.m_bodyAnimationFrame)
          .m_Props.soundForFrame;

  if (soundId[0] != 0xFF) {
    if (g_Spyro.m_LastBodyFrameData !=
        SPYRO_FRAME(g_Spyro.m_bodyAnimation, g_Spyro.m_bodyAnimationFrame)
            .m_Data) {
      PlaySound(soundId[0], (Moby *)&g_Spyro, 4, &g_Spyro.m_damageSoundChannel);
    }
  }

  g_Spyro.m_LastBodyFrameData =
      SPYRO_FRAME(g_Spyro.m_bodyAnimation, g_Spyro.m_bodyAnimationFrame).m_Data;

  // Head
  soundId[1] =
      SPYRO_FRAME(g_Spyro.m_headAnimation, g_Spyro.m_headAnimationFrame)
          .m_Props.soundForFrame;

  if (soundId[1] != 0xFF && soundId[0] != soundId[1]) {
    if (g_Spyro.m_LastHeadFrameData !=
        SPYRO_FRAME(g_Spyro.m_headAnimation, g_Spyro.m_headAnimationFrame)
            .m_Data) {
      PlaySound(soundId[1], (Moby *)&g_Spyro, 4, &g_Spyro.m_damageSoundChannel);
    }
  }

  g_Spyro.m_LastHeadFrameData =
      SPYRO_FRAME(g_Spyro.m_headAnimation, g_Spyro.m_headAnimationFrame).m_Data;

  g_Spyro.m_ControlFlags &= 0x7FFFFFFF;

  if (g_PadSwapFlag) {
    func_80053708(&g_PadBackup, &g_Pad);
  }

#undef SPYRO_FRAME
}

/**
 * @brief Updates Spyro during gamestate 1 (return home portal sequence).
 *
 * This function handles Spyro's update loop when entering a return home portal:
 * 1. Backing up gamepad state and disabling player input
 * 2. Forcing Spyro into state 0xF (gliding) if not already there
 * 3. Setting walking state to 8 and ensuring input lockout
 * 4. Running physics updates (velocity, position)
 * 5. Running animation updates (body, flame, head, tail)
 * 6. Updating rotation matrices from speed angles
 * 7. Clearing control flags and restoring gamepad state
 *
 * Called from gamestate 1 in src/gamestates/update.c.
 *
 * Key differences from UpdateSpyroReturnHome:
 * - Forces state to 0xF (gliding) if not already in that state
 * - Sets walking state unconditionally (not inside state check)
 */
void UpdateSpyroEnterReturnHome(void) {
  char _pad[32]; // Stack padding to match original 0x58 frame
  int i;
  Vector3D8 *bodyRot;
  MATRIX *rotMatrix;

  // Swap gamepad states
  g_PadSwapFlag = 0;
  func_80053708(&g_Pad, &g_PadBackup);

  // Force state to 15 (gliding) if not already there
  if (g_Spyro.m_State != 15) {
    func_8003EA68(15);
  }

  // Set walking state to 8
  g_Spyro.m_walkingState = 8;

  // Ensure gamepad update frames is at least 1
  if (g_Spyro.m_noGamepadUpdateFrames <= 0) {
    g_Spyro.m_noGamepadUpdateFrames = 1;
  }

  // Zero out velocity
  VecNull(&g_Spyro.m_Physics.m_Velocity);

  // Run state update loop
  for (i = 0; i < g_DeltaTime; i++) {
    func_80043FE4(i);
  }

  // Shift velocity right by 6
  VecShiftRight(&g_Spyro.m_Physics.m_Velocity, 6);

  // Save current position before movement
  VecCopy(&g_Spyro.m_previousPosition, &g_Spyro.m_Position);

  // Add velocity to position
  VecAdd(&g_Spyro.m_Position, &g_Spyro.m_Position,
         &g_Spyro.m_Physics.m_Velocity);

  // Run physics update loop
  for (i = 0; i < g_DeltaTime; i++) {
    func_8004888C();
  }

  // Run animation update loop
  for (i = 0; i < g_DeltaTime; i++) {
    UpdateBodyAnimationState();
    func_800499C0();
    func_80049660();
    func_80049F3C();
    func_80049E8C();
  }

  // Cache pointers for matrix operations
  bodyRot = &g_Spyro.m_bodyRotation;
  rotMatrix = &g_Spyro.m_RotationMatrix;

  // Update body rotation from speed angles
  bodyRot->x = g_Spyro.m_Physics.m_SpeedAngle.m_RotX >> 4;
  g_Spyro.m_bodyRotation.y = g_Spyro.m_Physics.m_SpeedAngle.m_RotY >> 4;
  g_Spyro.m_bodyRotation.z = g_Spyro.m_Physics.m_SpeedAngle.m_RotZ >> 4;

  // Create rotation matrix from body rotation
  RotVec8ToMatrix(bodyRot, rotMatrix, nullptr);

  // Create head rotation matrix from m_headRotation
  RotVec8ToMatrix((Vector3D8 *)((u_char *)bodyRot + 4),
                  &g_Spyro.m_headRotationMatrix, nullptr);

  // Combine body and head rotation
  MulMatrix0(rotMatrix, &g_Spyro.m_headRotationMatrix,
             &g_Spyro.m_headRotationMatrix);

  // Clear control flags
  g_Spyro.m_ControlFlags = 0;

  // Swap gamepad states back
  func_80053708(&g_PadBackup, &g_Pad);
}

/**
 * @brief Updates Spyro during the return home portal animation (gamestate 10).
 *
 * This function handles Spyro's update loop during the return home sequence:
 * 1. Backing up gamepad state and disabling player input
 * 2. Setting walking state to 8 if already in state 0xF (gliding)
 * 3. Ensuring input lockout (m_noGamepadUpdateFrames >= 1)
 * 4. Zeroing velocity and running physics state updates
 * 5. Applying velocity to position (shift right 6, then add)
 * 6. Running rotation updates via func_8004888C
 * 7. Running animation updates (body, flame, head, flame-block, tail)
 * 8. Updating body/head rotation matrices from speed angles
 * 9. Clearing control flags and restoring gamepad state
 *
 * Called from gamestate 10 in src/gamestates/update.c.
 *
 * Key differences from UpdateSpyroEnterReturnHome:
 * - Does NOT force state to 0xF (assumes already in correct state)
 * - Only sets walking state if state == 0xF (conditional)
 */
void UpdateSpyroReturnHome(void) {
  char _pad[32]; // Stack padding to match original 0x58 frame
  int i;
  Vector3D8 *bodyRot;
  MATRIX *rotMatrix;

  // Swap gamepad states
  g_PadSwapFlag = 0;
  func_80053708(&g_Pad, &g_PadBackup);

  // If state is 15 (gliding), set walking state to 8
  if (g_Spyro.m_State == 0xF) {
    g_Spyro.m_walkingState = 8;
  }

  // Ensure gamepad update frames is at least 1
  if (g_Spyro.m_noGamepadUpdateFrames <= 0) {
    g_Spyro.m_noGamepadUpdateFrames = 1;
  }

  // Zero out velocity
  VecNull(&g_Spyro.m_Physics.m_Velocity);

  // Run state update loop
  for (i = 0; i < g_DeltaTime; i++) {
    func_80043FE4(i);
  }

  // Shift velocity right by 6
  VecShiftRight(&g_Spyro.m_Physics.m_Velocity, 6);

  // Save current position before movement
  VecCopy(&g_Spyro.m_previousPosition, &g_Spyro.m_Position);

  // Add velocity to position
  VecAdd(&g_Spyro.m_Position, &g_Spyro.m_Position,
         &g_Spyro.m_Physics.m_Velocity);

  // Run physics update loop
  for (i = 0; i < g_DeltaTime; i++) {
    func_8004888C();
  }

  // Run animation update loop
  for (i = 0; i < g_DeltaTime; i++) {
    UpdateBodyAnimationState();
    func_800499C0();
    func_80049660();
    func_80049F3C();
    func_80049E8C();
  }

  // Cache pointers for matrix operations
  bodyRot = &g_Spyro.m_bodyRotation;
  rotMatrix = &g_Spyro.m_RotationMatrix;

  // Update body rotation from speed angles
  bodyRot->x = g_Spyro.m_Physics.m_SpeedAngle.m_RotX >> 4;
  g_Spyro.m_bodyRotation.y = g_Spyro.m_Physics.m_SpeedAngle.m_RotY >> 4;
  g_Spyro.m_bodyRotation.z = g_Spyro.m_Physics.m_SpeedAngle.m_RotZ >> 4;

  // Create rotation matrix from body rotation
  RotVec8ToMatrix(bodyRot, rotMatrix, nullptr);

  // Create head rotation matrix from m_headRotation (bodyRot + 4 for padding)
  RotVec8ToMatrix((Vector3D8 *)((u_char *)bodyRot + 4),
                  &g_Spyro.m_headRotationMatrix, nullptr);

  // Combine body and head rotation: head = body * head
  MulMatrix0(rotMatrix, &g_Spyro.m_headRotationMatrix,
             &g_Spyro.m_headRotationMatrix);

  // Clear control flags (exit scripted/cutscene mode)
  g_Spyro.m_ControlFlags = 0;

  // Swap gamepad states back
  func_80053708(&g_PadBackup, &g_Pad);
}

void func_8004AC24(int pKeepPosition) {
  // Clean up any state specific side effects before wiping
  switch (g_Spyro.m_State) {
  case 11:
  case 15:
  case 32:
  case 44:
    // Stop all of spyro's sounds
    func_800562A4((Moby *)&g_Spyro, 2);
    break;
  case 7:
    // Disable the color filter
    g_Spyro.m_colorFilter.m_interpolation = 0;
    break;
  }

  if (pKeepPosition != 0) {
    Vector3D posBackup;
    Vector3D8 rotationBackup;
    int healthBackup;

    // Create backups of some values before wiping the entire spyro struct
    VecCopy(&posBackup, &g_Spyro.m_Position);
    rotationBackup.x = g_Spyro.m_bodyRotation.x;
    rotationBackup.y = g_Spyro.m_bodyRotation.y;
    rotationBackup.z = g_Spyro.m_bodyRotation.z;
    healthBackup = g_Spyro.m_health;

    Memset(&g_Spyro, 0, sizeof(g_Spyro));

    VecCopy(&g_Spyro.m_Position, &posBackup);

    g_Spyro.m_bodyRotation.x = rotationBackup.x;
    g_Spyro.m_bodyRotation.y = rotationBackup.y;
    g_Spyro.m_bodyRotation.z = rotationBackup.z;
    g_Spyro.m_health = healthBackup;

    g_Spyro.m_sortingDepth = 4;
    g_Spyro.m_nextBodyAnimationFrame = 1;
    g_Spyro.m_CollisionTriangleIndex = -1;

    g_Spyro.m_Physics.m_SpeedAngle.m_RotX = rotationBackup.x * 0x10;
    g_Spyro.m_Physics.m_SpeedAngle.m_RotY = rotationBackup.y * 0x10;
    g_Spyro.m_Physics.m_SpeedAngle.m_RotZ = rotationBackup.z * 0x10;

    func_8003EA68(0);

    g_Spyro.m_touchingSurface = 0xFF;
    g_Spyro.m_damageSoundChannel = 0x3F;
    g_SpyroFlame.m_FairyKissTimer = 0;
  } else {
    // Leaves most things intact
    g_Spyro.m_CollisionTriangleIndex = -1;
    g_Spyro.m_touchingSurface = 0xFF;
    *((int *)&g_Spyro.m_colorFilter) = 0;
    g_Spyro.m_DamageFlags = 0;
    g_Spyro.m_FloorDistance = 0;
    g_Spyro.m_flyingAbility = 0;
    g_Spyro.m_doingSupercharge = 0;
    g_Spyro.unk_0x254 = 0;
    g_Spyro.m_drowningOffset = 0;
    g_SpyroFlame.m_FairyKissTimer = 0;

    g_Spyro.m_Physics.m_SpeedAngle.m_RotX = g_Spyro.m_bodyRotation.x * 0x10;
    g_Spyro.m_Physics.m_SpeedAngle.m_RotY = g_Spyro.m_bodyRotation.y * 0x10;
    g_Spyro.m_Physics.m_SpeedAngle.m_RotZ = g_Spyro.m_bodyRotation.z * 0x10;
  }
}
