#include "camera.h"
#include "common.h"
#include "environment.h"
#include "gamepad.h"
#include "math.h"
#include "special_surfaces.h"
#include "spu.h"
#include "spyro.h"
#include "variables.h"
#include "vector.h"

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

/// @brief Creates the target speed and angle based on the stick
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8003D3B8);

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
void UpdateSpyroTurnMomentum(int pTableIndex) {
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

  // Calculate angular distance (And.. does nothing with it?)
  func_80017928(g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ,
                g_Spyro.m_Physics.m_SpeedAngle.m_RotZ);
}

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8003D840);

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

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8003DAE4);

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

  func_800170C0(&vec2, &vec2);
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
  func_800170C0(&vec2, &vec2);
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
      g_Spyro.m_slopeAngle = 0x400;
    }

    // Store collision triangle for moving platform tracking
    g_Spyro.m_CollisionTriangleIndex = g_CollisionTriangleIndex;
    ColTriUnpack(g_CollisionTriangleIndex,
                 g_Spyro.m_collisionTriangleUnpacked.points);

    // Check if slope is walkable (< 33 degrees)
    if (g_Spyro.m_slopeAngle < 0x21) {
      g_Spyro.m_onSlope = (g_Spyro.m_slopeAngle < 0x17) ^ 1;
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

      func_800170C0(&vec2, &vec2);
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
        g_Spyro.m_slopeAngle = 0x400;
      }

      // If walkable, mark as grounded and set slope flag
      if (g_Spyro.m_slopeAngle < 0x21) {
        g_Spyro.m_airTime = 0;
        g_Spyro.m_onSlope = (g_Spyro.m_slopeAngle < 0x17) ^ 1;
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

  func_800170C0(&vec3, &vec3);
  VecAdd(&vec3, &g_Spyro.m_Position, &vec3);

  func_800170C0(&vec2, &vec2);
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

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8003E90C);

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
// Invulnerability mask: -0x1F2 (0xFFFFFE0E) clears bits 0,4,5,6,7,8
// Charge immunity mask: -0x401 (0xFFFFFBFF) clears bit 10 (charge)

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
    pFlags &= -0x1F2; // Clear low damage bits
    if (g_Spyro.m_Physics.m_TrueVelocity.z > 0) {
      // Rising in air - also immune to charge damage
      pFlags &= -0x401;
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
      func_8003EA68(0x1B); // State 27
    } else if (pFlags & 0x80) {
      func_8003EA68(0x1C); // State 28
    } else if (pFlags & 0x100) {
      func_8003EA68(0x16); // State 22
    } else if (pFlags & 0x400) {
      // Charge damage in normal damage path
      func_8003EA68(0x1D); // State 29: Charge interrupted
      // Instant death on certain floor types
      if (*g_Spyro.m_floorFlagsPointer != 0 && D_800756A0 == 0) {
        g_Spyro.m_health = -1;
      }
    } else {
      func_8003EA68(0xE); // State 14: Default hurt state
    }

    // Grant invulnerability frames (0x5A = 90 frames)
    if (g_Spyro.m_invulverabilityTimer < 0x5A) {
      g_Spyro.m_invulverabilityTimer = 0x5A;
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
      if (g_Spyro.m_invulverabilityTimer < 0x5A) {
        g_Spyro.m_invulverabilityTimer = 0x5A;
      }
      func_8003EA68(0x1D); // State 29: Charge interrupted
    }
    result = 1;
  }

  // Knockback - applies external momentum (e.g. from cannons, wind)
  if (highFlags & 0x8000) {
    func_8003EA68(0xC); // State 12: Knockback
    func_80017330(&g_Spyro.m_KnockbackDirection,
                  0x800); // Normalize to magnitude 0x800
    VecCopy(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_KnockbackDirection);
    result = 1;
  }

  // Electrified/frozen state toggle
  if (highFlags & 0x800) {
    if (g_Spyro.m_State != 0x11) {
      func_8003EA68(0x11); // State 17: Electrified/stuck
      result = 1;
    }
  } else if (g_Spyro.m_State == 0x11) {
    // Release from electrified state
    func_8003EA68(0xF); // State 15: Recovery
  }

  // Supercharge flag management (state 44 is immune)
  if (g_Spyro.m_State != 0x2C) {
    if (highFlags & 0x2000) {
      g_Spyro.m_doingSupercharge = 1;
    } else {
      g_Spyro.m_doingSupercharge = 0;
    }
  }

  return result;
}

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80041270);

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

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80041670);

/// @brief Physics state update for Spyro
/// @param pDeltaTimeIndex Deltatime index, used for the pad input buffer
void func_80043FE4(int pDeltaTimeIndex);
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80043FE4);

/// @brief Per-frame state dispatch for Spyro
void func_80047B60(void);
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80047B60);

/// @brief Rotation updates for Spyro
void func_8004888C(void);
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8004888C);

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

/// @brief Update the head animation
void func_80049660(void);
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80049660);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80049880);

/// @brief Update flame
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_800499C0);

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

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80049FAC);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8004A200);

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
  if (g_Spyro.m_State != 0xF) {
    func_8003EA68(0xF);
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

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8004AC24);

