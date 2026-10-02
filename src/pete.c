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

/**
 * @brief Pre-processes analog stick input for Spyro's turning ("soft turn").
 *
 * When the left stick is held gently (magnitude < 0x60), interpolates
 * m_TargetSpeedAngle toward m_SpeedAngle proportionally to stick magnitude,
 * producing smooth micro-adjustments instead of a full turn. Larger stick
 * deflections fall through to the normal momentum-based turn. Always
 * delegates the actual rotation to UpdateSpyroTurnMomentum() afterward.
 */
void ApplySpyroSoftTurn(void) {
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

  UpdateSpyroTurnMomentum(0); // Apply rotation using row 0 (walking turn rate)
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

extern u_char D_80075274[];
extern int D_8006C5B8;
extern int D_8006C5BC;
extern int D_8006C5C0;
extern int D_8006C5C4;
extern int D_8006C5C8;
extern int D_8006C5CC;
extern int D_80075728;
extern int D_8006EA34[];
int D_80075668;
int D_800756B4;
int D_80075724;
int D_8007578C;
Moby *D_80075790;
int D_800757F0;
/// @brief Changes Spyro's state
/// @param pNewState The state to change to
void func_8003EA68(int pNewState) {
  Vector3D mobyDelta;
  Vector3D particleOffset;
  int manhattanY;
  int manhattanX;
  register int manhattanZ asm("v0");
  switch (g_Spyro.m_State) {
  case 11:

  case 15:

  case 32:

  case 44:
    func_800562A4((Moby *)(&g_Spyro), 2);
    break;

  case 7:
    g_Spyro.m_colorFilter.m_interpolation = 0;

  case 14:

  case 22:

  case 27:

  case 28:
    PlaySound(g_Spu.m_SoundTable->spyroStars, (Moby *)(&g_Spyro), 4,
              &g_Spyro.m_damageSoundChannel);
    break;

  case 25:
    PlaySound(g_Spu.m_SoundTable->spyroUnsquish, (Moby *)(&g_Spyro), 4,
              &g_Spyro.m_damageSoundChannel);
    break;
  }

  switch (pNewState) {
  case 0:
    g_Spyro.m_walkingState = 0;
    D_80075788 = (D_80075274[rand() & 7] *
                  spyro_AnimationDetails[0].m_TransitionLastFrame) -
                 2;
    g_Spyro.m_Physics.m_gravity = -0x80;
    g_Spyro.unk_0x15c = 1;
    break;

  case 1:

  case 2:

  case 3:

  case 21: {
    int angleDiff;
    g_Spyro.m_walkingState = 0;
    angleDiff = (Atan2((&g_Spyro.m_Physics.m_TrueVelocity)->x,
                       g_Spyro.m_Physics.m_TrueVelocity.y, 1) -
                 g_Spyro.m_Physics.m_SpeedAngle.m_RotZ) &
                0xFFF;
    if ((angleDiff > 0x400) && (angleDiff < 0xC00)) {
      g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0;
    } else {
      g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
          VecMagnitude(&g_Spyro.m_Physics.m_TrueVelocity, 0);
    }
    if ((pNewState == 3) && (g_Spyro.m_Physics.m_SpeedAngle.m_Speed > 0x1400)) {
      g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0x1400;
    }
    g_Spyro.m_Physics.m_gravity = -0xC00;
    func_8003E1AC();
    if (g_Spyro.m_slopeAngle != 0) {
      int slopeFactor;
      int interpB;
      int interpA;
      angleDiff = (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ -
                   Atan2(g_Spyro.m_floorPositonOnSlope.x,
                         g_Spyro.m_floorPositonOnSlope.y, 1)) &
                  0xFFF;
      if (angleDiff >= 0x801) {
        angleDiff -= 0x1000;
      }
      slopeFactor = (g_Spyro.m_slopeAngle << 12) / 22;
      angleDiff = (angleDiff >= 0) ? (angleDiff) : (-angleDiff);
      if (angleDiff > 0x400) {
        angleDiff = 0x800 - angleDiff;
        interpB =
            D_8006C5C0 + ((slopeFactor * (D_8006C5CC - D_8006C5C0)) >> 12);
      } else {
        interpB =
            D_8006C5B8 + ((slopeFactor * (D_8006C5C4 - D_8006C5B8)) >> 12);
      }
      interpA = D_8006C5BC + ((slopeFactor * (D_8006C5C8 - D_8006C5BC)) >> 12);
      interpB = (interpB * Cos(angleDiff)) >> 12;
      interpA = (interpA * Sin(angleDiff)) >> 12;
      g_Spyro.m_Physics.unk_0x144 =
          func_80017A38((interpB * interpB) + (interpA * interpA));
    } else {
      g_Spyro.m_Physics.unk_0x144 = D_8006C5B8;
    }
    g_Spyro.unk_0x15c = 1;
    if (g_Spyro.unk_0x194 != 0) {
      g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed = 0;
      g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ = g_Spyro.m_portalAngle.z
                                                    << 4;
    }
    break;
  }

  case 4:
    g_Spyro.m_walkingState = 0;
    g_Spyro.m_Physics.m_gravity = -0xC00;
    func_8003E1AC();
    g_Spyro.unk_0x15c = 1;
    break;

  case 5:
    VecCopy(&g_Spyro.m_Physics.m_Acceleration,
            &g_Spyro.m_Physics.m_TrueVelocity);
    g_Spyro.m_Physics.unk_0xe8.z = 0xDC0;
    g_Spyro.m_Physics.m_gravity = -0xC0;
    g_Spyro.m_walkingState = 0;
    g_Spyro.m_isGliding = 0;
    g_Spyro.unk_0x15c = 0;
    g_Spyro.m_highestFlightPoint =
        g_Spyro.m_Position.z + (g_Spyro.m_Physics.m_Acceleration.z >> 6);
    if (g_Spyro.m_State == 0x1D) {
      D_800756B4 = 1;
    } else {
      D_800756B4 = 0;
    }
    break;

  case 6:
    g_Spyro.m_walkingState = 0;
    VecCopy(&g_Spyro.m_Physics.m_Acceleration,
            &g_Spyro.m_Physics.m_TrueVelocity);
    if ((g_Spyro.m_floorIdleTime == 0) && (g_Spyro.m_slopeAngle < 0x20)) {
      func_8003E90C();
    }
    g_Spyro.m_Physics.m_gravity = -0xC0;
    g_Spyro.m_isGliding = 0;
    g_Spyro.unk_0x15c = 0;
    break;

  case 16:
    g_Spyro.m_walkingState = 0;
    g_Spyro.m_Physics.m_Acceleration.x = 0;
    g_Spyro.m_Physics.m_Acceleration.y = 0;
    g_Spyro.m_Physics.m_Acceleration.z = g_Spyro.m_Physics.m_TrueVelocity.z;
    if ((g_Spyro.m_floorIdleTime == 0) && (g_Spyro.m_slopeAngle < 0x20)) {
      func_8003E90C();
    }
    g_Spyro.m_Physics.m_gravity = -0xC0;
    g_Spyro.m_isGliding = 0;
    g_Spyro.unk_0x15c = 0;
    break;

  case 9:

  case 10:
    g_Spyro.m_walkingState = 0;
    VecCopy(&g_Spyro.m_Physics.unk_0xe8, &g_Spyro.m_Physics.m_TrueVelocity);
    g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0;
    g_Spyro.m_Physics.m_gravity = -0xC00;
    func_8003E1AC();
    g_Spyro.unk_0x15c = 1;
    break;

  case 11: {
    int angleDiff;
    int absAngle;
    int bestScore;
    int mobyAngle;
    int mobyAbsAngle;
    Moby *moby;
    VecCopy(&g_Spyro.m_Physics.unk_0xe8, &g_Spyro.m_Physics.m_TrueVelocity);
    if (g_Spyro.m_doingSupercharge != 0) {
      if ((g_Spyro.m_walkingState & 0x80) == 0) {
        int magnitude;
        g_Spyro.m_highestFlightPoint = g_Spyro.m_Position.z;
        magnitude = VecMagnitude(&g_Spyro.m_Physics.unk_0xe8, 1);
        if (magnitude < 0x1F80) {
          magnitude = 0x1F80;
        }
        g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed = magnitude;
      }
      g_Spyro.m_walkingState = 0x81;
    } else {
      g_Spyro.m_walkingState = 1;
    }
    g_Spyro.m_Physics.m_TurnMomentum = 0;
    g_Spyro.m_Physics.m_gravity = -0x240;
    func_8003E1AC();
    ApplySlopeGravity();
    g_Spyro.unk_0x15c = 1;
    PlaySound(g_Spu.m_SoundTable->spyroCharge, (Moby *)(&g_Spyro), 4,
              &g_Spyro.m_chargeSoundChannel);
    D_80075790 = (void *)0;
    angleDiff =
        (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ - g_Camera.m_Rotation.z) & 0xFFF;
    if (angleDiff >= 0x801) {
      angleDiff -= 0x1000;
    }
    absAngle = (angleDiff >= 0) ? (angleDiff) : (-angleDiff);
    if (absAngle < 0x201) {
      break;
    }
    bestScore = 0x7530;
    for (moby = g_LevelMobys; moby < g_DynMobys; moby++) {
      if ((moby->m_State < 0x7F) && (moby->m_CollisionGroup != ((void *)0))) {
        VecSub(&mobyDelta, &moby->m_Position, &g_Spyro.m_Position);
        mobyAngle = (Atan2(mobyDelta.x, mobyDelta.y, 1) -
                     g_Spyro.m_Physics.m_SpeedAngle.m_RotZ) &
                    0xFFF;
        if (mobyAngle >= 0x801) {
          mobyAngle -= 0x1000;
        }
        mobyAbsAngle = (mobyAngle >= 0) ? (mobyAngle) : (-mobyAngle);
        if (mobyAbsAngle < 0x200) {
          manhattanX = mobyDelta.x;
          manhattanY = mobyDelta.y;
          manhattanZ = mobyDelta.z;
          if (manhattanX < 0) {
            manhattanX = -manhattanX;
          }
          if (manhattanY < 0) {
            manhattanY = -manhattanY;
          }
          /* Allocation steering only (no codegen): extra refs raise Y's
             global priority above X's so Y takes v1 and X takes a0. */
          __asm__ volatile("" : "=r"(manhattanY) : "0"(manhattanY));
          __asm__ volatile("" : "=r"(manhattanY) : "0"(manhattanY));
          manhattanX += manhattanY;
          /* Scheduling barrier only (no operands/clobbers): flips the
             case-11 s1/s2 allocation tiebreak to reference coloring. */
          __asm__ volatile("");
          manhattanZ = (manhattanZ >= 0) ? (manhattanZ) : (-manhattanZ);
          manhattanX += manhattanZ;
          if (manhattanX < 0x4000) {
            manhattanX = VecMagnitude(&mobyDelta, 1);
            if (manhattanX < 0x1800) {
              do {
                manhattanX += mobyAbsAngle * 4;
              } while (0);
              if (manhattanX < bestScore) {
                bestScore = manhattanX;
                D_80075790 = moby;
              }
            }
          }
        }
      }
    }

    break;
  }

  case 12: {
    int i;
    int angle;
    angle = rand() & 0x3F;
    for (i = 0; i < 4; i++) {
      particleOffset.x = 0;
      particleOffset.y = D_8006CC78[angle] >> 7;
      particleOffset.z = D_8006CBF8[angle] >> 7;
      VecRotateByMatrix(&g_Spyro.m_RotationMatrix, &particleOffset,
                        &particleOffset);
      D_800758E4(1, 0x21, &particleOffset, (void *)1);
      angle = (angle + 0x40) & 0xFF;
    }

    g_Spyro.m_walkingState = 0;
    VecNull(&g_Spyro.m_Physics.unk_0xe8);
    VecSub(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.unk_0xe8,
           &g_Spyro.m_Physics.m_Acceleration);
    VecShiftRight(&g_Spyro.m_Physics.m_Acceleration, 2);
    g_Spyro.m_Physics.m_gravity = -0x300;
    g_Spyro.unk_0x15c = 1;
    if (D_8007584C < 0x78) {
      D_8007584C = 0x78;
    }
    if (D_800757D0 < 0xF) {
      D_800757D0 = 0xF;
    }
    break;
  }

  case 13:
    g_Spyro.m_Physics.m_gravity = -0xC00;
    g_Spyro.m_walkingState = 0;
    g_Spyro.unk_0x15c = 1;
    break;

  case 7: {
    int magnitude;
    g_Spyro.m_walkingState = 0;
    VecNull(&g_Spyro.m_Physics.m_Acceleration);
    VecSub(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.m_Acceleration,
           &g_Spyro.m_Physics.m_TrueVelocity);
    magnitude = VecMagnitude(&g_Spyro.m_Physics.m_Acceleration, 1);
    if (magnitude > 0x1E00) {
      VecScaleToLength(&g_Spyro.m_Physics.m_Acceleration, magnitude, 0x1E00);
    }
    g_Spyro.m_Physics.m_gravity = -0x300;
    if (g_Spyro.m_airTime == 0) {
      func_8003E1AC();
    }
    g_Spyro.unk_0x15c = 1;
    D_800758E4(5, 0xA, (void *)0, (void *)0);
    if (D_80075764 < 0x2D) {
      D_80075764 = 0x2D;
    }
    break;
  }

  case 14: {
    int magnitude;
    g_Spyro.m_walkingState = 0;
    VecNull(&g_Spyro.m_Physics.m_Acceleration);
    VecSub(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.m_Acceleration,
           &g_Spyro.m_Physics.m_TrueVelocity);
    magnitude = VecMagnitude(&g_Spyro.m_Physics.m_Acceleration, 1);
    if (magnitude > 0x1E00) {
      VecScaleToLength(&g_Spyro.m_Physics.m_Acceleration, magnitude, 0x1E00);
    }
    g_Spyro.m_Physics.m_gravity = -0x300;
    if (g_Spyro.m_airTime == 0) {
      func_8003E1AC();
    }
    g_Spyro.unk_0x15c = 1;
    D_800758E4(5, 0xA, (void *)0, (void *)0);
    if (D_80075904 < 0xF) {
      D_80075904 = 0xF;
    }
    PlaySound(g_Spu.m_SoundTable->flipImpact, (Moby *)(&g_Spyro), 4,
              &g_Spyro.m_damageSoundChannel);
    break;
  }

  case 25:
    g_Spyro.m_walkingState = 0;
    VecNull(&g_Spyro.m_Physics.m_Acceleration);
    g_Spyro.m_Physics.m_Acceleration.z = -0xC00;
    g_Spyro.unk_0x15c = 1;
    D_800758E4(5, 0xA, (void *)0, (void *)0);
    if (D_80075904 < 0xF) {
      D_80075904 = 0xF;
    }
    PlaySound(g_Spu.m_SoundTable->splort, (Moby *)(&g_Spyro), 4,
              &g_Spyro.m_damageSoundChannel);
    break;

  case 27:
    g_Spyro.m_walkingState = 0;
    VecNull(&g_Spyro.m_Physics.m_Acceleration);
    g_Spyro.m_Physics.m_gravity = -0x300;
    g_Spyro.unk_0x15c = 1;
    D_800758E4(5, 0xA, (void *)0, (void *)0);
    if (D_80075904 < 0xF) {
      D_80075904 = 0xF;
    }
    break;

  case 15:

  case 23:

  case 32:

  case 33:

  case 34:
    if (((((g_Spyro.m_State != 0xF) && (g_Spyro.m_State != 0x17)) &&
          (g_Spyro.m_State != 0x20)) &&
         (g_Spyro.m_State != 0x21)) &&
        (g_Spyro.m_State != 0x22)) {
      g_Spyro.m_walkingState = 0;
      g_Spyro.m_onSlope = 1;
      g_Spyro.m_Physics.m_TurnMomentum = 0;
      D_80075960 = 0;
      D_800758A0 = 0;
      D_80075700 = 0;
      if (g_Spyro.m_Physics.m_TrueVelocity.z > 0) {
        g_Spyro.m_Physics.m_TrueVelocity.z = 0;
      }
      g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
          VecMagnitude(&g_Spyro.m_Physics.m_Acceleration, 0);
      if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed > 0x1900) {
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0x1900;
      }
      if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0x780) {
        g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0x780;
      }
      if (((g_Spyro.m_State != 6) || (g_IsFlightLevel != 0)) ||
          (g_Spyro.m_highestFlightPoint < g_Spyro.m_Position.z)) {
        g_Spyro.m_highestFlightPoint = g_Spyro.m_Position.z;
      }
      if (g_Spyro.m_Physics.m_SpeedAngle.m_RotY > 0x400) {
        g_Spyro.unk_0x254 = 1;
      } else {
        g_Spyro.unk_0x254 = 0;
      }
      g_Spyro.m_Physics.m_gravity = -0x80;
    }
    g_Spyro.unk_0x15c = 0;
    break;

  case 17:
    if (g_Spyro.m_mobyInUseBySpyro != ((void *)0)) {
      int heightDiff;
      int clampedAngle;
      int rotDiff;
      VecNull(&g_Spyro.m_Physics.m_Acceleration);
      g_Spyro.m_highestFlightPoint = g_Spyro.m_portalEndPos.z;
      D_8007578C = g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;
      heightDiff = (g_Spyro.m_portalEndPos.z - g_Spyro.m_Position.z) - 0x800;
      D_80075724 = heightDiff;
      D_80075668 = g_Spyro.m_Position.z;
      clampedAngle = ((heightDiff << 10) >> 10) + 0x400;
      D_800757F0 = clampedAngle;
      rotDiff = (((g_Spyro.m_mobyInUseBySpyro->m_Rotation.z * 0x10) -
                  g_Spyro.m_Physics.m_SpeedAngle.m_RotZ) -
                 clampedAngle) &
                0xFFF;
      D_800757F0 = rotDiff;
      if (rotDiff >= 0x801) {
        D_800757F0 = rotDiff - 0x1000;
      }
    } else {
      VecCopy(&g_Spyro.m_Physics.m_Acceleration,
              &g_Spyro.m_Physics.m_TrueVelocity);
    }
    g_Spyro.m_Physics.m_gravity = 0x80;
    g_Spyro.unk_0x15c = 0;
    break;

  case 18:

  case 36:

  case 37:

  case 38:

  case 39:

  case 40:

  case 41:

  case 42:

  case 43:
    g_Spyro.m_walkingState = 0;
    D_80075788 = spyro_AnimationDetails[pNewState].m_TransitionLastFrame * 0x10;
    g_Spyro.m_Physics.m_gravity = -0xC00;
    break;

  case 19:
    g_Spyro.m_walkingState = 0;
    VecCopy(&g_Spyro.m_Physics.unk_0xe8, &g_Spyro.m_Physics.m_TrueVelocity);
    if (g_Spyro.m_Physics.unk_0xe8.z > 0) {
      g_Spyro.m_Physics.unk_0xe8.z = 0;
    }
    g_Spyro.m_Physics.m_gravity = -0x200;
    func_8003E1AC();
    ApplySlopeGravity();
    g_Spyro.unk_0x15c = 0;
    break;

  case 20:
    VecCopy(&g_Spyro.m_Physics.m_Acceleration,
            &g_Spyro.m_Physics.m_TrueVelocity);
    VecCopy(&g_Spyro.m_Physics.unk_0xe8, &g_Spyro.m_Physics.m_TrueVelocity);
    g_Spyro.m_Physics.m_TurnMomentum = 0;
    if (g_Spyro.m_doingSupercharge != 0) {
      if ((g_Spyro.m_walkingState & 0x80) == 0) {
        int magnitude;
        g_Spyro.m_highestFlightPoint = g_Spyro.m_Position.z;
        magnitude = VecMagnitude(&g_Spyro.m_Physics.unk_0xe8, 1);
        if (magnitude < 0x1F80) {
          magnitude = 0x1F80;
        }
        g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed = magnitude;
      }
      g_Spyro.m_walkingState |= 0x80;
    } else {
      g_Spyro.m_walkingState = 0;
      g_Spyro.m_Physics.m_Acceleration.z = 0;
      g_Spyro.m_Physics.unk_0xe8.z = 0;
    }
    g_Spyro.m_Physics.m_gravity = -0x240;
    g_Spyro.m_isGliding = 0;
    g_Spyro.unk_0x15c = 0;
    break;

  case 24:
    VecCopy(&g_Spyro.m_Physics.m_Acceleration,
            &g_Spyro.m_Physics.m_TrueVelocity);
    VecCopy(&g_Spyro.m_Physics.unk_0xe8, &g_Spyro.m_Physics.m_TrueVelocity);
    g_Spyro.m_Physics.m_TurnMomentum = 0;
    g_Spyro.m_walkingState = 0xC0;
    g_Spyro.m_Physics.m_gravity = 0;
    g_Spyro.m_isGliding = 0;
    break;

  case 26: {
    int angleDiff;
    g_Spyro.m_walkingState = 0;
    angleDiff = Atan2(g_Spyro.m_Physics.m_TrueVelocity.x,
                      g_Spyro.m_Physics.m_TrueVelocity.y, 1) -
                g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;
    angleDiff &= 0xFFF;
    if ((angleDiff > 0x400) && (angleDiff < 0xC00)) {
      g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0;
    } else {
      g_Spyro.m_Physics.m_SpeedAngle.m_Speed =
          VecMagnitude(&g_Spyro.m_Physics.m_TrueVelocity, 0);
    }
    g_Spyro.m_Physics.m_gravity = -0xC00;
    func_8003E1AC();
    g_Spyro.m_Physics.unk_0x144 = 0x280;
    D_800758A0 = 0;
    g_Spyro.unk_0x15c = 1;
    break;
  }

  case 22:

  case 28:
    g_Spyro.m_Physics.m_Acceleration.x = g_Spyro.unk_0x208.x << 6;
    g_Spyro.m_walkingState = 0;
    g_Spyro.m_Physics.m_Acceleration.y = g_Spyro.unk_0x208.y << 6;
    if (g_Spyro.unk_0x208.z != 0) {
      g_Spyro.m_Physics.m_Acceleration.z = g_Spyro.unk_0x208.z << 6;
    } else {
      g_Spyro.m_Physics.m_Acceleration.z = g_Spyro.m_Physics.m_TrueVelocity.z;
    }
    Atan2(g_Spyro.m_Physics.m_Acceleration.x,
          g_Spyro.m_Physics.m_Acceleration.y, 1);
    g_Spyro.m_Physics.m_gravity = -0x300;
    if (g_Spyro.m_airTime == 0) {
      func_8003E1AC();
    }
    g_Spyro.unk_0x15c = 1;
    D_800758E4(5, 0xA, (void *)0, (void *)0);
    PlaySound(g_Spu.m_SoundTable->flipImpact, (Moby *)(&g_Spyro), 4,
              &g_Spyro.m_damageSoundChannel);
    if (D_80075904 < 0xF) {
      D_80075904 = 0xF;
    }
    break;

  case 29:
    g_Spyro.m_walkingState = 0;
    g_Spyro.m_Physics.m_gravity = -0x80;
    g_Spyro.unk_0x15c = 1;
    if (g_Spyro.m_invulverabilityTimer == 0) {
      D_800758E4(5, 0xA, (void *)0, (void *)0);
    }
    g_SpawnMoby(D_8006EA34[D_80075728], (void *)0);
    PlaySound(g_Spu.m_SoundTable->waterSplash, (Moby *)(&g_Spyro), 4,
              &g_Spyro.m_damageSoundChannel);
    PlaySound(g_Spu.m_SoundTable->spyroStars, (Moby *)(&g_Spyro), 4,
              &g_Spyro.m_damageSoundChannel);
    if (D_80075904 < 0xF) {
      D_80075904 = 0xF;
    }
    break;

  case 30:
    g_Spyro.m_walkingState = 0;
    VecCopy(&g_Spyro.m_Physics.unk_0xe8, &g_Spyro.m_Physics.m_TrueVelocity);
    g_Spyro.m_Physics.m_gravity = -0x300;
    if (g_Spyro.m_airTime == 0) {
      func_8003E1AC();
    }
    g_Spyro.unk_0x15c = 1;
    break;

  case 31:
    g_Spyro.m_walkingState = 0;
    VecCopy(&g_Spyro.m_Physics.unk_0xe8, &g_Spyro.m_Physics.m_TrueVelocity);
    g_Spyro.m_Physics.m_gravity = -0x300;
    if (g_Spyro.m_airTime == 0) {
      func_8003E1AC();
    }
    g_Spyro.unk_0x15c = 1;
    D_800758E4(5, 0xA, (void *)0, (void *)0);
    break;

  case 35:
    g_Spyro.m_Physics.m_gravity = -0x80;
    g_Spyro.m_walkingState = 0;
    g_Spyro.unk_0x15c = 1;
    break;

  case 8:
    g_Spyro.m_walkingState = 0;
    g_Spyro.unk_0x15c = 1;
    break;

  case 44:
    VecCopy(&g_Spyro.m_Physics.unk_0xe8, &g_Spyro.m_Physics.m_TrueVelocity);
    if ((g_Spyro.m_walkingState & 0x80) == 0) {
      int magnitude;
      g_Spyro.m_highestFlightPoint = g_Spyro.m_Position.z;
      magnitude = VecMagnitude(&g_Spyro.m_Physics.unk_0xe8, 1);
      if (magnitude < 0x1F80) {
        magnitude = 0x1F80;
      }
      g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed = magnitude;
    }
    g_Spyro.m_walkingState = 0xC0;
    g_Spyro.m_Physics.m_TurnMomentum = 0;
    g_Spyro.m_Physics.m_gravity = -0x240;
    func_8003E1AC();
    ApplySlopeGravity();
    g_Spyro.unk_0x15c = 1;
    D_80075700 = 0;
    PlaySound(g_Spu.m_SoundTable->superCharge, (Moby *)(&g_Spyro), 4,
              &g_Spyro.m_chargeSoundChannel);
    break;
  }

  g_Spyro.m_State = pNewState;
  g_Spyro.unk_0x84 = g_Spyro.m_idleTimer;
  g_Spyro.m_idleTimer = 0;
  g_Spyro.m_bodyAnimationSpeed =
      spyro_AnimationDetails[spyro_StateDefaultAnimation[g_Spyro.m_State]]
          .m_FrameRate;
}

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

extern int D_8006E9A4[36]; // (w58 fwd decl; canonical decl later in file)
extern int D_8006EA40[];   // (w58 fwd decl; indexed spawn table)
void func_80041670(void) {
  switch (g_Spyro.m_State) {
  case 0: {
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    if ((g_Pad.m_Down & 0x40) != 0) {
      func_8003EA68(5);
      break;
    }
    if (g_Spyro.m_airTime >= 4) {
      func_8003EA68(6);
      break;
    }
    if (g_Spyro.m_slopeAngle >= 0x17) {
      func_8003EA68(6);
      break;
    }
    if ((g_Pad.m_Held & 0x80) != 0) {
      func_8003EA68(0xB);
      break;
    }
    if ((g_Pad.m_Down & 4) != 0) {
      func_8003EA68(9);
      break;
    }
    if ((g_Pad.m_Down & 8) != 0) {
      func_8003EA68(0xA);
      break;
    }
    if (g_Spyro.m_Physics.m_TrueSpeed >= 0x401) {
      func_8003EA68(3);
      g_Spyro.m_walkingState = 7;
      break;
    }
    if (g_Camera.unk_0xC0 == 0x80000009) {
      break;
    }
    if (g_Pad.m_NoMovementButtonPressed == 0) {
      func_8003EA68(1);
      break;
    }
    if (g_Spyro.m_noGamepadUpdateFrames != 0) {
      break;
    }
    if (g_Spyro.m_onEdge != 0) {
      func_8003EA68(0xD);
      break;
    }
    if (g_Spyro.m_idleTimer < D_80075788) {
      break;
    }
    if (g_Spyro.unk_0x198 == 1) {
      break;
    }
    CycleSpyroIdleAnimation();
    break;
  }
  case 1: {
    int speed;
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    if ((g_Pad.m_Down & 0x40) != 0) {
      func_8003EA68(5);
      break;
    }
    if (g_Spyro.m_airTime >= 4) {
      func_8003EA68(6);
      break;
    }
    if (g_Spyro.m_slopeAngle >= 0x17) {
      func_8003EA68(6);
      break;
    }
    if ((g_Pad.m_Held & 0x80) != 0) {
      func_8003EA68(0xB);
      break;
    }
    if ((g_Pad.m_Down & 4) != 0) {
      func_8003EA68(9);
      break;
    }
    if ((g_Pad.m_Down & 8) != 0) {
      func_8003EA68(0xA);
      break;
    }
    if ((g_Spyro.m_Physics.m_SpeedAngle.m_Speed == 0) &&
        (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed == 0) &&
        (g_Spyro.m_idleTimer >= 0x10)) {
      func_8003EA68(0);
      break;
    }
    speed = g_Spyro.m_Physics.m_SpeedAngle.m_Speed;
    if (speed >= 0xF01) {
      func_8003EA68(2);
      break;
    }
    if (speed < 0x781) {
      break;
    }
    func_8003EA68(0x15);
    break;
  }
  case 2: {
    int t;
    int speed;
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    if ((g_Pad.m_Down & 0x40) != 0) {
      func_8003EA68(5);
      break;
    }
    if (g_Spyro.m_airTime >= 4) {
      func_8003EA68(6);
      break;
    }
    if (g_Spyro.m_slopeAngle >= 0x17) {
      func_8003EA68(6);
      break;
    }
    if ((g_Pad.m_Held & 0x80) != 0) {
      func_8003EA68(0xB);
      break;
    }
    if ((g_Pad.m_Down & 4) != 0) {
      func_8003EA68(9);
      break;
    }
    if ((g_Pad.m_Down & 8) != 0) {
      func_8003EA68(0xA);
      break;
    }
    if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed == 0) {
      func_8003EA68(3);
      break;
    }
    if (func_80017928(g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ,
                      g_Spyro.m_Physics.m_SpeedAngle.m_RotZ) >= 0x501) {
      if (g_Pad.m_LeftStickMoved == 0) {
        goto s1_arm;
      }
      t = g_ActivePad->m_Sticks.m_LeftY - 0x7F;
      if (t < 0) {
        t = -t;
      }
      if (t >= 0x31) {
        func_8003EA68(4);
        break;
      }
      func_8003EA68(3);
      break;
    s1_arm:
      __asm__("");
      func_8003EA68(4);
      break;
    }
    if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed == 0) {
      func_8003EA68(0);
      break;
    }
    speed = g_Spyro.m_Physics.m_SpeedAngle.m_Speed;
    if (speed < 0x640) {
      func_8003EA68(1);
      break;
    }
    if (speed >= 0xC80) {
      break;
    }
    func_8003EA68(0x15);
    break;
  }
  case 3: {
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    if ((g_Pad.m_Down & 0x40) != 0) {
      func_8003EA68(5);
      break;
    }
    if (g_Spyro.m_airTime >= 4) {
      func_8003EA68(6);
      break;
    }
    if (g_Spyro.m_slopeAngle >= 0x17) {
      func_8003EA68(6);
      break;
    }
    if ((g_Pad.m_Held & 0x80) != 0) {
      func_8003EA68(0xB);
      break;
    }
    if ((g_Pad.m_Down & 4) != 0) {
      func_8003EA68(9);
      break;
    }
    if ((g_Pad.m_Down & 8) != 0) {
      func_8003EA68(0xA);
      break;
    }
    if ((g_Spyro.m_Physics.m_SpeedAngle.m_Speed == 0) &&
        (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed == 0) &&
        (g_Spyro.m_Physics.m_TrueSpeed < 0x100)) {
      func_8003EA68(0);
      break;
    }
    if ((g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed > 0) &&
        (g_Spyro.m_idleTimer < 0x12) &&
        (func_80017928(g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ,
                       g_Spyro.m_Physics.m_SpeedAngle.m_RotZ) >= 0x501)) {
      func_8003EA68(4);
      break;
    }
    if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >= 0xF01) {
      if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed > 0) {
        func_8003EA68(2);
        break;
      }
    }
    if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >= 0x781) {
      if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed > 0) {
        func_8003EA68(0x15);
        break;
      }
    }
    if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed > 0) {
      if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed > 0) {
        func_8003EA68(1);
        break;
      }
    }
    break;
  }
  case 4: {
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    if ((g_Spyro.m_airTime >= 4) || (g_Spyro.m_slopeAngle >= 0x17)) {
      func_8003EA68(6);
      break;
    }
    if (g_Spyro.m_idleTimer < 0x25) {
      break;
    }
    if (g_Pad.m_NoMovementButtonPressed != 0) {
      func_8003EA68(0);
      break;
    }
    g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0xA00;
    func_8003EA68(1);
    break;
  }
  case 5: {
    int dot;
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    if ((g_Spyro.m_onSlope == 0) && ((g_Pad.m_Down & 0x40) != 0)) {
      g_Spyro.m_isGliding = 1;
    }
    if (g_Spyro.m_Physics.m_TrueVelocity.z < 0) {
      g_Spyro.m_walkingState = 1;
    }
    if ((g_Spyro.m_walkingState == 0) && ((g_Pad.m_Held & 0x40) == 0) &&
        (D_800756B4 == 0)) {
      g_Spyro.m_walkingState = 2;
    }
    if ((g_Spyro.m_airTime != 0) || (g_Spyro.m_idleTimer < 0x10)) {
      goto case5_fly;
    }
    if (g_Spyro.m_slopeAngle >= 0x17) {
      func_8003EA68(0x13);
      break;
    }
    dot = g_Spyro.m_floorPositonOnSlope.x * g_Spyro.m_Physics.m_Acceleration.x +
          g_Spyro.m_floorPositonOnSlope.y * g_Spyro.m_Physics.m_Acceleration.y +
          g_Spyro.m_floorPositonOnSlope.z * g_Spyro.m_Physics.m_Acceleration.z;
    if (dot < 0) {
      if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed > 0) {
        int speed = g_Spyro.m_Physics.m_SpeedAngle.m_Speed;
        if (speed >= 0xF01) {
          func_8003EA68(2);
          break;
        }
        if (speed >= 0x781) {
          func_8003EA68(0x15);
          break;
        }
        func_8003EA68(1);
        break;
      }
      if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >= 0x780) {
        func_8003EA68(3);
        break;
      }
      func_8003DFA4();
      func_8003EA68(0);
      break;
    }
    break;
  case5_fly:
    if ((g_Pad.m_Held & 0x80) == 0) {
      goto case5fly_skip;
    }
    func_8003EA68(0x14);
    g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0x1F80;
    break;
  case5fly_skip:
    if ((g_Spyro.m_onSlope == 0) && (g_Spyro.m_walkingState == 1) &&
        (g_Spyro.m_isGliding != 0)) {
      if (g_IsFlightLevel != 0) {
        goto fl_s1;
      }
      if (g_LevelId == 0x40) {
        __asm__("");
        func_8003EA68(0x20);
        break;
      }
      func_8003EA68(0xF);
      break;
    fl_s1:
      func_8003EA68(0x20);
      break;
    }
    if (g_Spyro.m_Physics.m_TrueVelocity.z < -0x1900) {
      func_8003EA68(6);
      break;
    }
    if (g_Spyro.m_idleTimer >= 0x79) {
      func_8003EA68(6);
      break;
    }
    break;
  }
  case 6: {
    Vector3D vecA;
    Vector3D vecB;
    int i;
    int ang;
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    if ((g_Pad.m_Down & 0x40) != 0) {
      if ((g_Spyro.unk_0x15c != 0) && (g_Spyro.m_idleTimer < 4)) {
        func_8003EA68(5);
        break;
      }
    }
    if (((g_Pad.m_Down & 0x40) != 0) && (g_Spyro.m_walkingState == 0)) {
      if ((g_IsFlightLevel != 0) || (g_LevelId == 0x40)) {
        if (g_Spyro.m_onSlope == 0) {
          func_8003EA68(0x20);
          break;
        }
        if (g_Spyro.m_idleTimer >= 0x10) {
          func_8003EA68(0x20);
          break;
        }
        break;
      } else {
        if (g_Spyro.m_onSlope == 0) {
          func_8003EA68(0xF);
          break;
        }
        if (g_Spyro.m_idleTimer >= 0x1F) {
          func_8003EA68(0xF);
          break;
        }
        break;
      }
    }
    if ((g_Spyro.m_Position.z >= D_8006E9A4[g_LevelIndex]) &&
        (g_Spyro.m_airTime == 0)) {
      if (g_Spyro.m_slopeAngle < 0x17) {
        goto case6_ladder;
      }
      if (g_Spyro.m_idleTimer < 9) {
        break;
      }
      func_8003EA68(0x13);
      break;
    case6_ladder:
      if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed > 0) {
        int speed = g_Spyro.m_Physics.m_SpeedAngle.m_Speed;
        if (speed >= 0xF01) {
          func_8003EA68(2);
        } else if (speed >= 0x781) {
          func_8003EA68(0x15);
        } else {
          func_8003EA68(1);
        }
        ang = g_Spyro.m_bodyRotation.z;
        i = 0;
        vecA.z = 0;
        do {
          vecA.x = COSINE_8(ang) >> 7;
          vecA.y = SINE_8(ang) >> 7;
          D_800758E4(1, 0x21, &vecA, nullptr);
          ang = (ang + 0x40) & 0xFF;
          i++;
        } while (i < 4);
        break;
      }
      if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0x780) {
        func_8003DFA4();
        func_8003EA68(0);
      } else {
        func_8003EA68(3);
      }
      ang = g_Spyro.m_bodyRotation.z;
      i = 0;
      vecB.z = 0;
      do {
        vecB.x = COSINE_8(ang) >> 7;
        vecB.y = SINE_8(ang) >> 7;
        D_800758E4(1, 0x21, &vecB, nullptr);
        ang = (ang + 0x40) & 0xFF;
        i++;
      } while (i < 4);
      break;
    }
  case6_42204:
    if (g_Spyro.m_idleTimer < 0x12D) {
      break;
    }
    if (g_IsFlightLevel != 0) {
      goto case19_42ec8;
    } else {
      goto case19_42ef8;
    }
  }
  case 8: {
    if (HandleSpyroDamage(0xFBF9) != 0) {
      if (g_Spyro.m_idleTimer >= 0xD) {
        g_Spyro.m_Physics.m_SpeedAngle.m_RotZ =
            g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ;
        g_Spyro.m_Physics.m_SpeedAngle.m_RotX =
            -g_Spyro.m_Physics.m_SpeedAngle.m_RotX & 0xFFF;
        g_Spyro.m_Physics.m_SpeedAngle.m_RotY =
            -g_Spyro.m_Physics.m_SpeedAngle.m_RotY & 0xFFF;
      }
      break;
    }
    if (g_Spyro.m_idleTimer < 0x14) {
      break;
    }
    g_Spyro.m_Physics.m_SpeedAngle.m_RotZ =
        g_Spyro.m_Physics.m_TargetSpeedAngle.m_RotZ;
    g_Spyro.m_Physics.m_SpeedAngle.m_RotX =
        -g_Spyro.m_Physics.m_SpeedAngle.m_RotX & 0xFFF;
    g_Spyro.m_Physics.m_SpeedAngle.m_RotY =
        -g_Spyro.m_Physics.m_SpeedAngle.m_RotY & 0xFFF;
    if (g_Pad.m_NoMovementButtonPressed != 0) {
      func_8003EA68(0);
      break;
    }
    func_8003EA68(1);
    g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0x15;
    break;
  }
  case 9: {
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    if ((g_Spyro.m_airTime >= 4) || (g_Spyro.m_slopeAngle >= 0x17)) {
      func_8003EA68(6);
      break;
    }
    if ((g_Pad.m_Held & 4) != 0) {
      break;
    }
    if (g_Spyro.m_idleTimer < 0x15) {
      break;
    }
    VecCopy(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.unk_0xe8);
    g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0;
    func_8003EA68(0);
    break;
  }
  case 10: {
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    if ((g_Spyro.m_airTime >= 4) || (g_Spyro.m_slopeAngle >= 0x17)) {
      func_8003EA68(6);
      break;
    }
    if ((g_Pad.m_Held & 8) != 0) {
      break;
    }
    if (g_Spyro.m_idleTimer < 0x15) {
      break;
    }
    VecCopy(&g_Spyro.m_Physics.m_Acceleration, &g_Spyro.m_Physics.unk_0xe8);
    g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0;
    func_8003EA68(0);
    break;
  }
  case 11: {
    int v1;
    if (func_80041270()) {
      break;
    }
    if (((g_Pad.m_Held & 0xC0) == 0xC0) && (g_Spyro.m_slopeAngle < 0xC)) {
      int newAirTime;
      func_8003EA68(0x14);
      g_Spyro.m_Physics.m_Acceleration.z += 0xDC0;
      newAirTime = g_Spyro.m_airTime + 1;
      __asm__ volatile("#s11");
      g_Spyro.m_airTime = newAirTime;
      break;
    }
    if (g_Spyro.m_airTime >= 4) {
      func_8003EA68(0x14);
      break;
    }
    if (g_Spyro.m_slopeAngle >= 0x17) {
      func_8003EA68(6);
      break;
    }
    if ((g_Pad.m_Held & 0x80) == 0) {
      func_8003EA68(2);
      g_Spyro.m_idleTimer = g_Spyro.unk_0x84 << 1;
      break;
    }
    if ((g_Spyro.m_Physics.m_SpeedAngle.m_Speed >= 0xC81) &&
        ((g_Spyro.m_Physics.m_TrueSpeed << 1) <
         g_Spyro.m_Physics.m_SpeedAngle.m_Speed) &&
        (g_HasLevelTransition == 0)) {
      func_8003EA68(0xC);
      break;
    }
    if (g_Spyro.m_doingSupercharge != 0) {
      if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0x3001) {
        goto case11_ws80;
      }
      func_8003EA68(0x2C);
      break;
    case11_ws80:
      if ((g_Spyro.m_walkingState & 0x80) == 0) {
        g_Spyro.m_highestFlightPoint = g_Spyro.m_Position.z;
        v1 = VecMagnitude(&g_Spyro.m_Physics.unk_0xe8, 1);
        if (v1 < 0x1F80) {
          v1 = 0x1F80;
        }
        g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed = v1;
        g_Spyro.m_walkingState |= 0x80;
      }
      break;
    }
    g_Spyro.m_walkingState &= ~0x80;
    break;
  }
  case 12: {
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    if (g_Spyro.m_idleTimer >= 0x11) {
      if (g_Spyro.m_airTime != 0) {
        goto c12_call6;
      }
      if (g_Spyro.m_slopeAngle < 0x17) {
        goto c12_skip6;
      }
    c12_call6:
      func_8003EA68(6);
      break;
    }
  c12_skip6:;
    if (g_Spyro.m_idleTimer >= 0x19) {
      func_8003EA68(0);
      break;
    }
    break;
  }
  case 13: {
    int down;
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    down = g_Pad.m_Down;
    if ((down & 0x40) != 0) {
      func_8003EA68(5);
      break;
    }
    if (g_Spyro.m_airTime >= 4) {
      func_8003EA68(6);
      break;
    }
    if (g_Spyro.m_slopeAngle >= 0x17) {
      func_8003EA68(6);
      break;
    }
    if ((g_Pad.m_Held & 0x80) != 0) {
      func_8003EA68(0xB);
      break;
    }
    if ((down & 4) != 0) {
      func_8003EA68(9);
      break;
    }
    if ((down & 8) != 0) {
      func_8003EA68(0xA);
      break;
    }
    if (g_Camera.unk_0xC0 == 0x80000009) {
      func_8003EA68(0);
      break;
    }
    if (g_Pad.m_NoMovementButtonPressed == 0) {
      func_8003EA68(1);
      break;
    }
    if (g_Spyro.m_noGamepadUpdateFrames != 0) {
      func_8003EA68(0);
      break;
    }
    if (g_Spyro.m_idleTimer < 0x1F) {
      break;
    }
    if (g_Spyro.m_onEdge == 0) {
      func_8003EA68(0);
      break;
    }
    break;
  }
  case 7: {
    if ((g_Spyro.m_DamageFlags & 0x20) != 0) {
      break;
    }
    if (g_Spyro.m_idleTimer < 0x18) {
      break;
    }
    if (g_Spyro.m_health >= 0) {
      goto shared_43558;
    }
    func_8003EA68(0x1E);
    break;
  }
  case 14:
  case 22:
  case 28: {
    if (g_Spyro.m_idleTimer < 0x18) {
      break;
    }
    if (g_Spyro.m_health >= 0) {
      goto shared_43558;
    }
    func_8003EA68(0x1E);
    break;
  }
  case 27: {
    if (g_Spyro.m_idleTimer < 0x30) {
      break;
    }
    if (g_Spyro.m_health >= 0) {
      goto shared_43558;
    }
    func_8003EA68(0x1E);
    break;
  }
  case 15: {
    int speed;
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    if (g_Spyro.m_airTime == 0) {
      if (g_Spyro.m_slopeAngle >= 0x17) {
        func_8003EA68(6);
        break;
      }
      if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed > 0) {
        speed = g_Spyro.m_Physics.m_SpeedAngle.m_Speed;
        if (speed >= 0xF01) {
          func_8003EA68(2);
          break;
        }
        if (speed >= 0x781) {
          func_8003EA68(0x15);
          break;
        }
        func_8003EA68(1);
        break;
      }
      if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0x780) {
        func_8003DFA4();
        func_8003EA68(0);
        break;
      }
      func_8003EA68(3);
      break;
    }
    if (g_Spyro.m_floorIdleTime == 0) {
      func_8003EA68(6);
      break;
    }
    if (g_Spyro.m_Physics.m_TrueSpeed < 0x400) {
      func_8003EA68(6);
      break;
    }
    if ((g_Pad.m_Held & 0x80) != 0) {
      func_8003EA68(0x14);
      break;
    }
    if (g_Spyro.m_idleTimer >= 0x11) {
      if ((g_Pad.m_Down & 0x10) != 0) {
        func_8003EA68(0x10);
        break;
      }
    }
    if (g_Spyro.m_flyingAbility != 0) {
      int posZ;
      if (g_Spyro.m_walkingState != 0) {
        break;
      }
      posZ = g_Spyro.m_Position.z;
      if (posZ - g_Spyro.m_highestFlightPoint >= 0x201) {
        func_8003EA68(6);
        break;
      }
      if ((g_ActivePad->m_Released & 8) != 0) {
        g_Spyro.m_walkingState = 1;
        break;
      }
      if ((g_ActivePad->m_Released & 4) != 0) {
        g_Spyro.m_walkingState = 2;
        D_80075700 = posZ;
        break;
      }
      break;
    }
    if (g_Spyro.m_walkingState == 0) {
      if (g_Spyro.m_highestFlightPoint + 0x18 < g_Spyro.m_Position.z) {
        func_8003EA68(6);
        break;
      }
    }
    if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >= 0xC80) {
      break;
    }
    if (g_Spyro.m_idleTimer < 0x11) {
      break;
    }
    func_8003EA68(0x17);
    break;
  }
  case 17: {
    HandleSpyroDamage(0xFFF9);
    break;
  }
  case 18:
  case 36:
  case 37:
  case 38:
  case 39:
  case 40:
  case 41:
  case 42:
  case 43: {
    int down;
    u_char *c18_base;
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    down = g_Pad.m_Down;
    if ((down & 0x40) != 0) {
      func_8003EA68(5);
      break;
    }
    c18_base = (u_char *)&g_Spyro.m_airTime;
    asm("" : "=r"(c18_base) : "0"(c18_base));
    if (*(int *)c18_base >= 4) {
      goto c18_call6;
    }
    if (g_Spyro.m_slopeAngle < 0x17) {
      goto c18_held;
    }
  c18_call6:
    func_8003EA68(6);
    break;
  c18_held:
    if ((g_Pad.m_Held & 0x80) != 0) {
      func_8003EA68(0xB);
      break;
    }
    if ((down & 4) == 0) {
      goto c18_down8;
    }
    func_8003EA68(9);
    break;
  c18_down8:
    if ((down & 8) == 0) {
      goto c18_tspeed;
    }
    func_8003EA68(0xA);
    break;
  c18_tspeed:
    if (g_Spyro.m_Physics.m_TrueSpeed < 0x401) {
      goto c18_camera;
    }
    func_8003EA68(3);
    break;
  c18_camera:
    if (g_Camera.unk_0xC0 == 0x80000009) {
      goto case18_fdc8_0;
    }
    if (g_Pad.m_NoMovementButtonPressed == 0) {
      func_8003EA68(1);
      break;
    }
    if (g_Spyro.m_onEdge != 0) {
      func_8003FDC8(0xD);
      break;
    }
    if (g_Spyro.m_noGamepadUpdateFrames != 0) {
      goto case18_fdc8_0;
    }
    if (*(c18_base - 131) == spyro_StateDefaultAnimation[g_Spyro.m_State]) {
      if (*(c18_base - 125) >=
          spyro_AnimationDetails[*(c18_base - 131)].m_EndFrame - 1) {
        func_8003EA68(0);
        break;
      }
    }
    if (g_Spyro.unk_0x198 == 1) {
    case18_fdc8_0:
      func_8003FDC8(0);
    }
    break;
  }
  case 16: {
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    if ((g_Spyro.m_Position.z < D_8006E9A4[g_LevelIndex]) ||
        (g_Spyro.m_airTime != 0)) {
      goto case16_down;
    }
    if (g_Spyro.m_idleTimer >= 0x18) {
      goto case16_do6;
    }
    if (g_Spyro.m_slopeAngle < 0x17) {
      goto case16_do0;
    }
  case16_do6:
    func_8003EA68(6);
    g_Spyro.m_idleTimer = g_Spyro.unk_0x84;
    goto case16_join;
  case16_do0:
    func_8003EA68(0);
  case16_join:
    if (g_Spyro.m_noGamepadUpdateFrames < 8) {
      g_Spyro.m_noGamepadUpdateFrames = 8;
    }
    func_8003DFA4();
  case16_down:
    if ((g_Pad.m_Down & 0x40) == 0) {
      goto case6_42204;
    }
    if (g_Spyro.m_onSlope == 0) {
      func_8003EA68(0xF);
      break;
    }
    if (g_Spyro.m_idleTimer >= 0x10) {
      func_8003EA68(0xF);
      break;
    }
    break;
  }
  case 19: {
    int speed;
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    if ((g_Pad.m_Held & 0x40) != 0) {
      if (g_Spyro.m_idleTimer < 4) {
        func_8003EA68(5);
        break;
      }
    }
    if ((g_Pad.m_Held & 0x80) != 0) {
      if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >= 0x1F01) {
        func_8003EA68(0x14);
        break;
      }
    }
    if (g_Spyro.m_airTime >= 8) {
      func_8003EA68(6);
      break;
    }
    if ((g_Spyro.m_slopeAngle < 0x17) &&
        (g_Spyro.m_nextBodyAnimationFrame ==
         spyro_AnimationDetails[20].m_EndFrame - 1) &&
        (g_Spyro.m_Physics.m_TrueSpeed < 0x900)) {
      if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed > 0) {
        speed = g_Spyro.m_Physics.m_SpeedAngle.m_Speed;
        if (speed >= 0xF01) {
          func_8003EA68(2);
          break;
        }
        if (speed >= 0x781) {
          func_8003EA68(0x15);
          break;
        }
        func_8003EA68(1);
        break;
      }
      if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0x780) {
        func_8003DFA4();
        func_8003EA68(0);
        break;
      }
      func_8003EA68(3);
      break;
    }
    if (g_Spyro.m_idleTimer < 0x12D) {
      break;
    }
    if (g_IsFlightLevel != 0) {
    case19_42ec8:
      D_80075694();
      g_UpdateMoby();
      break;
    } else {
    case19_42ef8:
      g_SpyroLifeCount++;
      func_8002C85C();
      break;
    }
  }
  case 20: {
    int dot2;
    if ((g_Spyro.m_onSlope == 0) && ((g_Pad.m_Down & 0x40) != 0)) {
      g_Spyro.m_isGliding = 1;
    }
    if (((g_Spyro.m_walkingState & 0x40) == 0) && (func_80041270() != 0)) {
      break;
    }
    if ((g_Spyro.m_slopeAngle >= 0x17) && (g_HasLevelTransition == 0)) {
      dot2 =
          g_Spyro.m_Physics.m_Acceleration.x * g_Spyro.m_floorPositonOnSlope.x +
          g_Spyro.m_Physics.m_Acceleration.y * g_Spyro.m_floorPositonOnSlope.y;
      if (dot2 < 0) {
        func_8003EA68(0xC);
        break;
      }
    }
    if ((g_Spyro.m_touchingMoby == 0) &&
        (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >= 0xC81) &&
        ((g_Spyro.m_Physics.m_TrueSpeed << 1) <
         g_Spyro.m_Physics.m_SpeedAngle.m_Speed) &&
        (g_HasLevelTransition == 0)) {
      func_8003D978();
      func_8003EA68(0xC);
      break;
    }
    if (g_Spyro.m_airTime == 0) {
      if ((g_Spyro.m_walkingState & 0x40) == 0) {
        func_8003EA68(0xB);
        break;
      } else {
        func_8003EA68(0x2C);
        break;
      }
    }
    if (g_Spyro.m_Physics.m_Acceleration.z >= 0) {
      break;
    }
    if (g_Spyro.m_isGliding == 0) {
      break;
    }
    if (g_IsFlightLevel != 0) {
      goto fl_s2;
    }
    if (g_LevelId == 0x40) {
      __asm__("");
      func_8003EA68(0x20);
      break;
    } else {
      func_8003EA68(0xF);
      break;
    }
  fl_s2:
    func_8003EA68(0x20);
    break;
  }
  case 21: {
    int speed;
    int down;
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    down = g_Pad.m_Down;
    if ((down & 0x40) != 0) {
      func_8003EA68(5);
      break;
    }
    if (g_Spyro.m_airTime >= 4) {
      func_8003EA68(6);
      break;
    }
    if (g_Spyro.m_slopeAngle >= 0x17) {
      func_8003EA68(6);
      break;
    }
    if ((g_Pad.m_Held & 0x80) != 0) {
      func_8003EA68(0xB);
      break;
    }
    if ((down & 4) != 0) {
      func_8003EA68(9);
      break;
    }
    if ((down & 8) != 0) {
      func_8003EA68(0xA);
      break;
    }
    speed = g_Spyro.m_Physics.m_SpeedAngle.m_Speed;
    if (speed >= 0xF01) {
      func_8003EA68(2);
      break;
    }
    if (speed >= 0x640) {
      break;
    }
    func_8003EA68(1);
    break;
  }
  case 23: {
    int speed;
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    if (g_Spyro.m_airTime == 0) {
      if (g_Spyro.m_slopeAngle >= 0x17) {
        func_8003EA68(6);
        break;
      }
      if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed > 0) {
        speed = g_Spyro.m_Physics.m_SpeedAngle.m_Speed;
        if (speed >= 0xF01) {
          func_8003EA68(2);
          break;
        }
        if (speed >= 0x781) {
          func_8003EA68(0x15);
          break;
        }
        func_8003EA68(1);
        break;
      }
      if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0x780) {
        func_8003DFA4();
        func_8003EA68(0);
        break;
      }
      func_8003EA68(3);
      break;
    }
    if (g_Spyro.m_floorIdleTime == 0) {
      func_8003EA68(6);
      break;
    }
    if (g_Spyro.m_Physics.m_TrueSpeed < 0x400) {
      func_8003EA68(6);
      break;
    }
    if ((g_Pad.m_Held & 0x80) != 0) {
      func_8003EA68(0x14);
      break;
    }
    if ((g_Pad.m_Down & 0x10) != 0) {
      func_8003EA68(0x10);
      break;
    }
    if (g_Spyro.m_highestFlightPoint + 0x18 < g_Spyro.m_Position.z) {
      func_8003EA68(6);
      break;
    }
    if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0xC81) {
      return;
    }
    if (g_IsFlightLevel != 0) {
      goto fl_s3;
    }
    if (g_LevelId == 0x40) {
      __asm__("");
      func_8003EA68(0x20);
      break;
    }
    func_8003EA68(0xF);
    break;
  fl_s3:
    func_8003EA68(0x20);
    break;
  }
  case 24: {
    int mag;
    int ratio;
    register int dot2 __asm__("a0"); // (w237: explicit-reg force, #10 color)
    if (g_Spyro.m_idleTimer >= 4) {
      g_Spyro.unk_0x15c = 0;
    }
    if (((g_Pad.m_Held & 0x40) != 0) && (g_Spyro.unk_0x15c != 0)) {
      g_Spyro.unk_0x15c = 0;
      g_Spyro.m_Physics.m_Acceleration.z += 0xDC0;
    } else {
      if (((g_Pad.m_Down & 0x40) != 0) && (g_Spyro.m_onSlope == 0)) {
        g_Spyro.m_isGliding = 1;
      }
    }
    if ((g_Spyro.m_slopeAngle >= 0x17) && (g_HasLevelTransition == 0)) {
      dot2 =
          g_Spyro.m_Physics.m_Acceleration.x * g_Spyro.m_floorPositonOnSlope.x +
          g_Spyro.m_Physics.m_Acceleration.y * g_Spyro.m_floorPositonOnSlope.y;
      if (dot2 < 0) {
        func_8003EA68(0xC);
        break;
      }
    }
    mag = VecMagnitude(&g_Spyro.m_Physics.m_Acceleration, 1);
    if (mag == 0) {
      mag = 1;
    }
    ratio = (g_Spyro.m_Physics.m_TrueSpeed << 12) / mag;
    if ((g_Spyro.m_touchingMoby == 0) && (ratio < 0x800) &&
        (g_HasLevelTransition == 0)) {
      func_8003EA68(0xC);
      break;
    }
    if (g_Spyro.m_airTime == 0) {
      func_8003EA68(0xB);
      break;
    }
    if (g_Spyro.m_Physics.m_Acceleration.z >= 0) {
      break;
    }
    if (g_Spyro.m_isGliding == 0) {
      func_8003EA68(0x14);
      break;
    }
    if (g_IsFlightLevel != 0) {
      goto fl_s4;
    }
    if (g_LevelId == 0x40) {
      __asm__("");
      func_8003EA68(0x20);
      break;
    }
    func_8003EA68(0xF);
    break;
  fl_s4:
    func_8003EA68(0x20);
    break;
  }
  case 25: {
    if ((g_Spyro.m_DamageFlags & 0x10) != 0) {
      break;
    }
    if (g_Spyro.m_idleTimer < 0x18) {
      break;
    }
    if (g_Spyro.m_health >= 0) {
      goto shared_43558;
    }
    func_8003EA68(0x1E);
    break;
  }
  shared_43558:
    if (g_Spyro.m_airTime == 0) {
      func_8003EA68(0);
    } else {
      func_8003EA68(6);
    }
    if (g_Spyro.m_noGamepadUpdateFrames < 0xC) {
      g_Spyro.m_noGamepadUpdateFrames = 0xC;
    }
    break;
  case 26: {
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    if ((g_Pad.m_Down & 0x40) != 0) {
      func_8003EA68(5);
      break;
    }
    if (g_Spyro.m_airTime >= 4) {
      func_8003EA68(6);
      break;
    }
    if (g_Spyro.m_slopeAngle >= 0x17) {
      func_8003EA68(6);
      break;
    }
    if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed != 0) {
      func_8003EA68(1);
      break;
    }
    if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed != 0) {
      func_8003EA68(1);
      break;
    }
    if (g_Spyro.m_idleTimer >= 0x10) {
      func_8003EA68(0);
      break;
    }
    func_8003EA68(1);
    break;
  }
  case 29: {
    if (HandleSpyroDamage(0xFBF9)) {
      break;
    }
    if (g_Spyro.m_health < 0) {
      break;
    }
    if (g_Spyro.m_idleTimer >= 0x3D) {
      g_Spyro.m_health = -1;
      g_SpawnMoby(D_8006EA40[D_80075728], nullptr);
      break;
    }
    if (g_Spyro.m_idleTimer < 0x10) {
      break;
    }
    if ((g_Pad.m_Held & 0x40) == 0) {
      break;
    }
    func_8003EA68(5);
    break;
  }
  case 32: {
    int speed;
    int posZ;
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    if (g_Spyro.m_airTime == 0) {
      if (g_Spyro.m_slopeAngle >= 0x17) {
        func_8003EA68(6);
        goto case32_join;
      }
      if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed > 0) {
        speed = g_Spyro.m_Physics.m_SpeedAngle.m_Speed;
        if (speed >= 0xF01) {
          func_8003EA68(2);
          goto case32_join;
        }
        if (speed >= 0x781) {
          func_8003EA68(0x15);
          goto case32_join;
        }
        func_8003EA68(1);
        goto case32_join;
      }
      if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >= 0x780) {
        func_8003EA68(3);
        goto case32_join;
      }
      func_8003DFA4();
      func_8003EA68(0);
      goto case32_join;
    }
    if (g_Spyro.m_floorIdleTime == 0) {
      func_8003EA68(6);
      goto case32_join;
    }
    if (g_Spyro.m_Physics.m_TrueSpeed < 0x400) {
      func_8003EA68(6);
      goto case32_join;
    }
    if (g_Spyro.m_Physics.m_TrueVelocity.z >= 0x801) {
      func_8003EA68(0x21);
      goto case32_join;
    }
    if ((g_Pad.m_Down & 0x40) == 0) {
      goto case32_downfalse;
    }
    func_8003EA68(0x21);
    goto case32_join;
  case32_downfalse:
    if (g_Spyro.m_Physics.m_TrueVelocity.z >= -0x1000) {
      goto case32_ws;
    }
    func_8003EA68(0x22);
    goto case32_join;
  case32_ws:
    if (g_Spyro.m_walkingState == 0) {
      posZ = g_Spyro.m_Position.z;
      if (posZ - g_Spyro.m_highestFlightPoint >= 0x201) {
        func_8003EA68(6);
        goto case32_join;
      }
      if ((g_ActivePad->m_Released & 8) != 0) {
        g_Spyro.m_walkingState = 1;
        goto case32_join;
      }
      if ((g_ActivePad->m_Released & 4) != 0) {
        g_Spyro.m_walkingState = 2;
        D_80075700 = posZ;
      }
    }
  case32_join:
    if (g_IsFlightLevel != 0) {
      break;
    }
    if ((g_Pad.m_Held & 0x80) != 0) {
      func_8003EA68(0x14);
      break;
    }
    if (g_Spyro.m_idleTimer < 0x11) {
      break;
    }
    if ((g_Pad.m_Down & 0x10) != 0) {
      func_8003EA68(0x10);
      break;
    }
    break;
  }
  case 33: {
    int speed;
    int posZ;
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    if (g_Spyro.m_airTime == 0) {
      if (g_Spyro.m_slopeAngle >= 0x17) {
        func_8003EA68(6);
        goto case33_join;
      }
      if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed > 0) {
        speed = g_Spyro.m_Physics.m_SpeedAngle.m_Speed;
        if (speed >= 0xF01) {
          func_8003EA68(2);
          goto case33_join;
        }
        if (speed >= 0x781) {
          func_8003EA68(0x15);
          goto case33_join;
        }
        func_8003EA68(1);
        goto case33_join;
      }
      if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >= 0x780) {
        func_8003EA68(3);
        goto case33_join;
      }
      func_8003DFA4();
      func_8003EA68(0);
      goto case33_join;
    }
    if (g_Spyro.m_floorIdleTime == 0) {
      func_8003EA68(6);
      goto case33_join;
    }
    if (g_Spyro.m_Physics.m_TrueSpeed < 0x400) {
      func_8003EA68(6);
      goto case33_join;
    }
    if ((g_Spyro.m_idleTimer >= 0x1F) &&
        (g_Spyro.m_Physics.m_TrueVelocity.z < 0x600)) {
      func_8003EA68(0x20);
      goto case33_join;
    }
    if (g_Spyro.m_walkingState == 0) {
      posZ = g_Spyro.m_Position.z;
      if (posZ - g_Spyro.m_highestFlightPoint >= 0x201) {
        func_8003EA68(6);
        goto case33_join;
      }
      if ((g_ActivePad->m_Released & 8) != 0) {
        g_Spyro.m_walkingState = 1;
        goto case33_join;
      }
      if ((g_ActivePad->m_Released & 4) != 0) {
        g_Spyro.m_walkingState = 2;
        D_80075700 = posZ;
      }
    }
  case33_join:
    if (g_IsFlightLevel != 0) {
      break;
    }
    if ((g_Pad.m_Held & 0x80) != 0) {
      func_8003EA68(0x14);
      break;
    }
    __asm__ volatile("#j33");
    if (g_Spyro.m_idleTimer < 0x11) {
      break;
    }
    if ((g_Pad.m_Down & 0x10) != 0) {
      func_8003EA68(0x10);
      break;
    }
    break;
  }
  case 34: {
    int speed;
    int posZ;
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    if (g_Spyro.m_airTime == 0) {
      if (g_Spyro.m_slopeAngle >= 0x17) {
        func_8003EA68(6);
        goto case34_join;
      }
      if (g_Spyro.m_Physics.m_TargetSpeedAngle.m_Speed > 0) {
        speed = g_Spyro.m_Physics.m_SpeedAngle.m_Speed;
        if (speed >= 0xF01) {
          func_8003EA68(2);
          goto case34_join;
        }
        if (speed >= 0x781) {
          func_8003EA68(0x15);
          goto case34_join;
        }
        func_8003EA68(1);
        goto case34_join;
      }
      if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >= 0x780) {
        func_8003EA68(3);
        goto case34_join;
      }
      func_8003DFA4();
      func_8003EA68(0);
      goto case34_join;
    }
    if (g_Spyro.m_floorIdleTime == 0) {
      func_8003EA68(6);
      goto case34_join;
    }
    if (g_Spyro.m_Physics.m_TrueSpeed < 0x400) {
      func_8003EA68(6);
      goto case34_join;
    }
    if ((g_Pad.m_Down & 0x40) != 0) {
      func_8003EA68(0x21);
      goto case34_join;
    }
    if ((g_Spyro.m_idleTimer >= 0x1F) &&
        (g_Spyro.m_Physics.m_TrueVelocity.z >= -0xBFF)) {
      func_8003EA68(0x20);
      goto case34_join;
    }
    if (g_Spyro.m_walkingState == 0) {
      posZ = g_Spyro.m_Position.z;
      if (posZ - g_Spyro.m_highestFlightPoint >= 0x201) {
        func_8003EA68(6);
        goto case34_join;
      }
      if ((g_ActivePad->m_Released & 8) != 0) {
        g_Spyro.m_walkingState = 1;
        goto case34_join;
      }
      if ((g_ActivePad->m_Released & 4) != 0) {
        g_Spyro.m_walkingState = 2;
        D_80075700 = posZ;
      }
    }
  case34_join:
    if (g_IsFlightLevel != 0) {
      break;
    }
    __asm__ volatile("#j34");
    if ((g_Pad.m_Held & 0x80) != 0) {
      func_8003EA68(0x14);
      break;
    }
    if (g_Spyro.m_idleTimer < 0x11) {
      break;
    }
    if ((g_Pad.m_Down & 0x10) != 0) {
      func_8003EA68(0x10);
      break;
    }
    break;
  }
  case 35: {
    if (HandleSpyroDamage(0xFFF9)) {
      break;
    }
    if (g_Spyro.m_ControlFlags != 0) {
      break;
    }
    func_8003EA68(0);
    break;
  }
  case 44: {
    int *heldA44;
    if (HandleSpyroDamage(0x8400)) {
      break;
    }
    heldA44 = (int *)&g_Pad;
    if ((*(heldA44 + 2) & 0x40) != 0) {
      if ((D_80075700 >= 0xA) || (g_Spyro.m_airTime != 0)) {
        goto case44_e8c;
      }
      D_80075700 += g_DeltaTime;
    }
    if ((g_Pad.m_Released & 0x40) != 0) {
    case44_e8c:
      func_8003EA68(0x18);
      g_Spyro.m_Physics.m_Acceleration.z += 0xDC0;
      g_Spyro.m_airTime++;
      g_Spyro.unk_0x15c = 0;
      break;
    }
    if (g_Spyro.m_airTime >= 4) {
      func_8003EA68(0x18);
      g_Spyro.unk_0x15c = 1;
      break;
    }
    if (g_Spyro.m_slopeAngle >= 0x17) {
      func_8003EA68(6);
      break;
    }
    if ((g_Spyro.m_idleTimer >= 0xF) &&
        ((*(volatile int *)&g_Pad.m_Held & 0x80) == 0)) {
      func_8003EA68(0xB);
      break;
    }
    if ((g_Spyro.m_touchingMoby == 0) &&
        (g_Spyro.m_Physics.m_SpeedAngle.m_Speed >= 0xC81) &&
        ((g_Spyro.m_Physics.m_TrueSpeed << 1) <
         g_Spyro.m_Physics.m_SpeedAngle.m_Speed) &&
        (g_HasLevelTransition == 0)) {
      func_8003EA68(0xC);
      break;
    }
    if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed < 0x1E00) {
      func_8003EA68(0xB);
      break;
    }
    break;
  }
  }
}

/// @brief Physics state update for Spyro
/// @param pDeltaTimeIndex Deltatime index, used for the pad input buffer
void func_80043FE4(int pDeltaTimeIndex);
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80043FE4);

/// @brief Per-frame state dispatch for Spyro
void func_80047B60(void);
extern int D_8006C5B8;
extern int D_8006C5BC;
extern int D_8006C5C0;
extern int D_8006C5C4;
extern int D_8006C5C8;
extern int D_8006C5CC;

/// @brief Per-frame state dispatch for Spyro
void func_80047B60(void) {
  Vector3D sp10;
  Vector3D sp20;
  Vector3D sp30;
  Vector3D sp40;
  Vector3D sp50;
  Vector3D sp60;
  Vector3D sp70;

  g_Camera.m_OnMovingPlatform = 0;

  switch (g_Spyro.m_State) {
  case 0:
  case 12:
  case 13:
  case 18:
  case 35:
  case 36:
  case 37:
  case 38:
  case 39:
  case 40:
  case 41:
  case 42:
  case 43:
    if (g_Pad.m_NoMovementButtonPressed != 0 && (g_Pad.m_Held & 0x10)) {
      g_Camera.unk_0xC0 = 0x80000009;
    }
    func_8003E628();
    func_8003FE40();
    UpdateSlopeFloorCollision();
    if (g_Spyro.m_ControlFlags == 0) {
      AdjustAirCollision();
    }
    break;

  case 1:
  case 2:
  case 3:
  case 21: {
    int angle;
    int slope;

    func_8003E628();
    func_8003FE40();
    UpdateSlopeFloorCollision();
    func_8003E1AC();

    if (g_Spyro.m_slopeAngle != 0) {
      int radius;
      int height;

      angle = (g_Spyro.m_Physics.m_SpeedAngle.m_RotZ -
               Atan2(g_Spyro.m_floorPositonOnSlope.x,
                     g_Spyro.m_floorPositonOnSlope.y, 1)) &
              0xFFF;

      if (angle >= 0x801) {
        angle -= 0x1000;
      }

      slope = (g_Spyro.m_slopeAngle << 0xC) / 22;
      angle = ABS(angle);
      if (angle > 0x400) {
        angle = 0x800 - angle;
        radius = D_8006C5C0 + ((slope * (D_8006C5CC - D_8006C5C0)) >> 0xC);
      } else {
        radius = D_8006C5B8 + ((slope * (D_8006C5C4 - D_8006C5B8)) >> 0xC);
      }
      height = D_8006C5BC + ((slope * (D_8006C5C8 - D_8006C5BC)) >> 0xC);
      radius = (radius * Cos(angle)) >> 0xC;
      height = (height * Sin(angle)) >> 0xC;
      g_Spyro.m_Physics.unk_0x144 =
          func_80017A38(radius * radius + height * height);
    } else {
      g_Spyro.m_Physics.unk_0x144 = D_8006C5B8;
    }

    if (g_Spyro.m_State == 3) {
      VecCopy(&sp20, &g_Spyro.m_Physics.m_TrueVelocity);
      VecShiftRight(&sp20, 6);
      D_800758E4(1, 0x21, &sp20, nullptr);
    }
    break;
  }

  case 4:
    func_8003E628();
    func_8003FE40();
    UpdateSlopeFloorCollision();
    func_8003E1AC();
    sp30.x = 0x20;
    sp30.y = 0;
    sp30.z = 0;
    VecRotateByMatrix(&g_Spyro.m_RotationMatrix, &sp30, &sp30);
    D_800758E4(1, 0x21, &sp30, nullptr);
    break;

  case 7:
    func_8003FE40();
    UpdateSlopeFloorCollision();
    func_8003E1AC();
    if (g_Spyro.m_nextBodyAnimationFrame < 0xA) {
      g_Spyro.m_colorFilter.m_interpolation = 0xFF;
      if (g_Spyro.m_nextBodyAnimationFrame & 1) {
        g_Spyro.m_colorFilter.m_blue = 0xFF;
        g_Spyro.m_colorFilter.m_green = 0xFF;
        g_Spyro.m_colorFilter.m_red = 0xFF;
      } else {
        g_Spyro.m_colorFilter.m_blue = 0x40;
        g_Spyro.m_colorFilter.m_green = 0x40;
        g_Spyro.m_colorFilter.m_red = 0x40;
      }
    } else {
      g_Spyro.m_colorFilter.m_interpolation = 0;
    }
    break;

  case 25:
  case 27:
    func_8003FE40();
    UpdateSlopeFloorCollision();
    break;

  case 5:
  case 17:
    func_8003FE40();
    UpdateSlopeFloorCollision();
    if (g_Spyro.m_againstWall == 0) {
      CheckWallCollision();
    }
    break;

  case 6:
  case 16:
    if (g_Spyro.m_flyingAbility == 0) {
      g_Spyro.m_highestFlightPoint = g_Spyro.m_Position.z;
    }
    func_8003FE40();
    UpdateSlopeFloorCollision();
    if (g_Spyro.m_flyingAbility != 0) {
      if (g_IsFlightLevel != 0) {
        int delta = D_800758C0 - g_Spyro.m_highestFlightPoint;
        if (delta > 0x40) {
          delta = 0x40;
        }
        if (delta < -0x10) {
          delta = -0x10;
        }
        g_Spyro.m_highestFlightPoint += delta;
      } else {
        if (D_800758C0 != 0) {
          int delta = D_800758C0 - g_Spyro.m_highestFlightPoint;
          if (delta > 0x40) {
            delta = 0x40;
          }
          if (delta < -0x10) {
            delta = -0x10;
          }
          g_Spyro.m_highestFlightPoint += delta;
        }
        if (g_Spyro.m_highestFlightPoint > D_800758C0 &&
            g_Spyro.m_floorIdleTime != 0) {
          D_800758C0 = g_Spyro.m_highestFlightPoint;
        }
        if (g_LevelId == 0x40 && D_800758C0 > D_80075678) {
          D_800758C0 = D_80075678;
        }
      }
    }
    if (g_Spyro.m_againstWall == 0) {
      CheckWallCollision();
    }
    VecCopy(&g_Spyro.m_Physics.m_Acceleration,
            &g_Spyro.m_Physics.m_TrueVelocity);
    break;

  case 23:
    if (g_Spyro.m_flyingAbility == 0) {
      g_Spyro.m_highestFlightPoint = g_Spyro.m_Position.z;
    }
    func_8003FE40();
    UpdateSlopeFloorCollision();
    if (g_Spyro.m_flyingAbility != 0) {
      if (g_IsFlightLevel != 0) {
        int delta = D_800758C0 - g_Spyro.m_highestFlightPoint;
        if (delta > 0x40) {
          delta = 0x40;
        }
        if (delta < -0x10) {
          delta = -0x10;
        }
        g_Spyro.m_highestFlightPoint += delta;
      } else {
        if (D_800758C0 != 0) {
          int delta = D_800758C0 - g_Spyro.m_highestFlightPoint;
          if (delta > 0x40) {
            delta = 0x40;
          }
          if (delta < -0x10) {
            delta = -0x10;
          }
          g_Spyro.m_highestFlightPoint += delta;
        }
        if (g_Spyro.m_highestFlightPoint > D_800758C0 &&
            g_Spyro.m_floorIdleTime != 0) {
          D_800758C0 = g_Spyro.m_highestFlightPoint;
        }
        if (g_LevelId == 0x40 && D_800758C0 > D_80075678) {
          D_800758C0 = D_80075678;
        }
      }
    }
    if (g_Spyro.m_againstWall == 0) {
      CheckWallCollision();
    }
    break;

  case 32:
  case 33:
  case 34:
    if (g_Spyro.m_flyingAbility == 0) {
      g_Spyro.m_highestFlightPoint = g_Spyro.m_Position.z;
    }
    func_8003FE40();
    UpdateSlopeFloorCollision();
    if (g_Spyro.m_flyingAbility != 0) {
      if (g_IsFlightLevel != 0) {
        int delta = D_800758C0 - g_Spyro.m_highestFlightPoint;
        if (delta > 0x40) {
          delta = 0x40;
        }
        if (delta < -0x10) {
          delta = -0x10;
        }
        g_Spyro.m_highestFlightPoint += delta;

        if (g_Spyro.m_walkingState == 3 &&
            func_8004BE4C(&g_Spyro.m_Position, 0x164, 0x164) != 0) {
          D_80075694();
        }
      } else {
        if (D_800758C0 != 0) {
          int delta = D_800758C0 - g_Spyro.m_highestFlightPoint;
          if (delta > 0x40) {
            delta = 0x40;
          }
          if (delta < -0x10) {
            delta = -0x10;
          }
          g_Spyro.m_highestFlightPoint += delta;
        }
        if (g_Spyro.m_highestFlightPoint > D_800758C0 &&
            g_Spyro.m_floorIdleTime != 0) {
          D_800758C0 = g_Spyro.m_highestFlightPoint;
        }
        if (g_LevelId == 0x40 && D_800758C0 > D_80075678) {
          D_800758C0 = D_80075678;
        }
      }
    }
    if (g_Spyro.m_againstWall == 0) {
      CheckWallCollision();
    }
    break;

  case 15:
    if (g_Spyro.m_flyingAbility == 0) {
      g_Spyro.m_highestFlightPoint = g_Spyro.m_Position.z;
    }
    func_8003FE40();
    UpdateSlopeFloorCollision();
    if (g_Spyro.m_flyingAbility != 0) {
      if (D_800758C0 != 0) {
        int delta = D_800758C0 - g_Spyro.m_highestFlightPoint;
        if (delta > 0x40) {
          delta = 0x40;
        }
        if (delta < -0x10) {
          delta = -0x10;
        }
        g_Spyro.m_highestFlightPoint += delta;
      }
      if (g_Spyro.m_highestFlightPoint > D_800758C0 &&
          g_Spyro.m_floorIdleTime != 0) {
        D_800758C0 = g_Spyro.m_highestFlightPoint;
      }
      if (g_LevelId == 0x40 && D_800758C0 > D_80075678) {
        D_800758C0 = D_80075678;
      }
    }
    if (g_Spyro.m_againstWall == 0) {
      CheckWallCollision();
    }
    if ((g_Spyro.m_ControlFlags & 0x4000) && g_Spyro.m_walkingState == 9) {
      g_Spyro.m_surfaceBelowSpyro = func_8004D5EC(&g_Spyro.m_Position, 0x10000);
    }
    break;

  case 8:
    func_8003E628();
    func_8003FE40();
    UpdateSlopeFloorCollision();
    AdjustAirCollision();
    break;

  case 11:
    func_8003FE40();
    UpdateSlopeFloorCollision();
    func_8003E1AC();
    ApplySlopeGravity();
    AdjustAirCollision();
    if (g_Spyro.m_againstWall == 0) {
      CheckWallCollision();
    }
    break;

  case 19:
    func_8003FE40();
    VecCopy(&g_Spyro.m_Physics.unk_0xe8, &g_Spyro.m_Physics.m_TrueVelocity);
    UpdateSlopeFloorCollision();
    func_8003E1AC();
    ApplySlopeGravity();
    break;

  case 20:
  case 24:
    func_8003FE40();
    UpdateSlopeFloorCollision();
    if (g_Spyro.m_walkingState & 0x40) {
      VecCopy(&sp40, &g_Spyro.m_Position);
      sp40.x = sp40.x + ((rand() & 0xFE) - 0x7F);
      sp40.y = sp40.y + ((rand() & 0xFE) - 0x7F);
      VecCopy(&sp50, &g_Spyro.m_Physics.m_TrueVelocity);
      VecShiftRight(&sp50, 6);
      D_800758E4(1, 9, &sp40, &sp50);
    }
    break;

  case 9:
  case 10:
  case 14:
  case 22:
  case 26:
  case 28:
  case 30:
  case 31:
    func_8003FE40();
    UpdateSlopeFloorCollision();
    func_8003E1AC();
    break;

  case 29:
    if (g_Spyro.m_drowningOffset != 0) {
      g_Spyro.m_drowningOffset += 8;
      g_Spyro.m_Position.z = g_Spyro.m_damagingFloorIndex + 0x164;
      if (g_Spyro.m_health >= 0) {
        if (g_Spyro.m_drowningOffset >= 0x97) {
          g_Spyro.m_drowningOffset = 0x96;
        }
      } else if (g_Spyro.m_drowningOffset >= 0x241) {
        g_Spyro.m_drowningOffset = 0x240;
      }
    }
    func_8003FE40();
    UpdateSlopeFloorCollision();
    AdjustAirCollision();
    break;

  case 44:
    func_8003FE40();
    UpdateSlopeFloorCollision();
    func_8003E1AC();
    ApplySlopeGravity();
    VecCopy(&sp60, &g_Spyro.m_Position);
    sp60.x = sp60.x + ((rand() & 0xFE) - 0x7F);
    sp60.y = sp60.y + ((rand() & 0xFE) - 0x7F);
    sp60.z -= 0x164;
    VecCopy(&sp70, &g_Spyro.m_Physics.m_TrueVelocity);
    VecShiftRight(&sp70, 6);
    D_800758E4(1, 9, &sp60, &sp70);
    break;
  }

  if (g_Spyro.m_State == 0x1D) {
    g_Spyro.m_Position.z -= g_Spyro.m_drowningOffset;
    if (g_Spyro.m_surfaceBelowSpyro != 0) {
      g_Spyro.m_FloorDistance = g_Spyro.m_surfaceBelowSpyro;
      return;
    }
    VecCopy(&sp10, &g_Spyro.m_Position);
    sp10.z += 0x800;
    g_Spyro.m_FloorDistance = func_8004D5EC(&sp10, 0xC00);
    return;
  }
  g_Spyro.m_FloorDistance = 0;
}

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
