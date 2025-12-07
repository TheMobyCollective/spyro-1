#include "camera.h"
#include "common.h"
#include "gamepad.h"
#include "math.h"
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
extern int D_8006BC60[9];              // Animation state table
extern int D_80075970;                 // Animation cycle index

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

      if (D_8006BC84[g_Spyro.unk_0x5C][g_Spyro.m_State] == 10) {
        g_Spyro.m_nextBodyAnimationFrame =
            spyro_AnimationDetails[spyro_StateDefaultAnimation[g_Spyro.m_State]]
                .m_StartFrame;
      } else {
        g_Spyro.m_nextBodyAnimationFrame = 1;
        g_Spyro.m_bodyFrameProgress = 4;
      }
      g_Spyro.unk_0x5C = g_Spyro.m_State;
      return 1;
    }
  }

  return 0;
}

/// @brief Handles the state transition for Spyro's body animation
void func_8003CCE4(void) {
  switch (D_8006BC84[g_Spyro.unk_0x5C][g_Spyro.m_State]) {
  case 1:
    g_Spyro.unk_0x54 = 1;
    g_Spyro.m_bodyAnimation = g_Spyro.m_nextBodyAnimation;
    g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;

    g_Spyro.m_nextBodyAnimation = spyro_StateDefaultAnimation[g_Spyro.m_State];
    g_Spyro.m_nextBodyAnimationFrame = 0;
    g_Spyro.m_bodyFrameProgress = 2;

    g_Spyro.unk_0x5C = g_Spyro.m_State;
    break;

  case 8:
    g_Spyro.unk_0x54 = 8;
    g_Spyro.m_bodyAnimation = g_Spyro.m_nextBodyAnimation;
    g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;

    g_Spyro.m_nextBodyAnimation = spyro_StateDefaultAnimation[g_Spyro.m_State];
    g_Spyro.m_nextBodyAnimationFrame = 0;
    g_Spyro.m_bodyFrameProgress = 4;

    g_Spyro.unk_0x5C = g_Spyro.m_State;
    break;

  case 2:
    if (g_Spyro.m_nextBodyAnimationFrame >=
        spyro_AnimationDetails[g_Spyro.m_nextBodyAnimation].m_EndFrame) {
      g_Spyro.unk_0x54 = 2;
      g_Spyro.m_bodyAnimation = g_Spyro.m_nextBodyAnimation;
      g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;
      g_Spyro.m_nextBodyAnimationFrame =
          spyro_AnimationDetails[g_Spyro.m_nextBodyAnimation].m_StartFrame;
      g_Spyro.m_bodyFrameProgress = 2;
    } else {
      g_Spyro.unk_0x54 = 0;
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
    g_Spyro.unk_0x54 = 5;
    g_Spyro.unk_0x5C = g_Spyro.m_State;
    break;

  case 3:
  case 10:
    g_Spyro.unk_0x54 = 3;
    break;

  case 4:
    g_Spyro.m_bodyAnimation = g_Spyro.m_nextBodyAnimation;
    g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;

    if (g_Spyro.unk_0x5C == 6 && g_Spyro.unk_0x84 < 24) {
      g_Spyro.unk_0x54 = 1;
      g_Spyro.m_nextBodyAnimation =
          spyro_StateDefaultAnimation[g_Spyro.m_State];
      g_Spyro.m_nextBodyAnimationFrame = 0;
      g_Spyro.m_bodyFrameProgress = 2;
      g_Spyro.unk_0x5C = g_Spyro.m_State;
    } else {
      g_Spyro.m_nextBodyAnimationFrame =
          spyro_AnimationDetails[g_Spyro.m_nextBodyAnimation].m_EndFrame;
      g_Spyro.m_bodyFrameProgress = 4;
      g_Spyro.unk_0x54 = 4;

      if (g_Spyro.unk_0x5C == 6) {
        D_8007584C = 0xA0;
        if (D_800757D0 < 0xF) {
          D_800757D0 = 0xF;
        }
      }
    }
    break;

  case 6:
    g_Spyro.unk_0x54 = 6;
    g_Spyro.m_bodyAnimation = g_Spyro.m_nextBodyAnimation;
    g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;

    g_Spyro.m_nextBodyAnimation = spyro_StateDefaultAnimation[g_Spyro.m_State];
    g_Spyro.m_nextBodyAnimationFrame =
        spyro_AnimationDetails[g_Spyro.m_nextBodyAnimation].m_StartFrame;
    g_Spyro.m_bodyFrameProgress = 2;

    g_Spyro.unk_0x5C = g_Spyro.m_State;
    break;

  case 7:
    g_Spyro.m_bodyAnimation = spyro_StateDefaultAnimation[g_Spyro.m_State];
    g_Spyro.m_bodyAnimationFrame = 0;

    g_Spyro.m_nextBodyAnimation = spyro_StateDefaultAnimation[g_Spyro.m_State];
    g_Spyro.m_nextBodyAnimationFrame = 1;

    g_Spyro.m_bodyFrameProgress = 0;
    g_Spyro.unk_0x54 = 0;
    g_Spyro.unk_0x5C = g_Spyro.m_State;
    break;

  case 11:
    g_Spyro.m_bodyAnimation = spyro_StateDefaultAnimation[g_Spyro.m_State];
    g_Spyro.m_bodyAnimationFrame =
        spyro_AnimationDetails[g_Spyro.m_bodyAnimation].m_StartFrame;

    g_Spyro.m_nextBodyAnimation = spyro_StateDefaultAnimation[g_Spyro.m_State];
    g_Spyro.m_nextBodyAnimationFrame =
        spyro_AnimationDetails[g_Spyro.m_bodyAnimation].m_StartFrame + 1;

    g_Spyro.m_bodyFrameProgress = 0;
    g_Spyro.unk_0x54 = 0;
    g_Spyro.unk_0x5C = g_Spyro.m_State;
    break;

  default:
    // There used to be a printf here (removed after July) that said:
    // printf("illegal animation transition from %d to %d\n", g_Spyro.unk_0x5C,
    // g_Spyro.m_State)
    return;
  }
}

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8003D194);

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
  tempVec.x = (((pUnknown * sinY) / cosY) * cosX >> 0xc);
  tempVec.z = ((pUnknown * cosX) / cosY);
  tempVec.y = (pUnknown * sinX >> 0xc);

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

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8003D6D0);

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

void func_8003DA08(void) {
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
  g_Spyro.unk_0x258 += ((t.x << 2) >> 4) - ((g_Spyro.unk_0x258 << 4) >> 6);
  g_Spyro.unk_0x25c += ((t.y << 2) >> 4) - ((g_Spyro.unk_0x25c << 4) >> 6);

  t.x = (g_Spyro.unk_0x258 >> 2);
  t.y = (g_Spyro.unk_0x25c >> 2);

  g_Spyro.m_Physics.m_SpeedAngle.m_RotX += t.x;
  g_Spyro.m_Physics.m_SpeedAngle.m_RotY += t.y;
}

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8003DAE4);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8003DE44);

/// Unused function
void func_8003DF60(void) {
  VecCopy(&g_Spyro.m_Position, &g_Spyro.unk_0x8c);
  VecNull(&g_Spyro.m_Physics.m_TrueVelocity);
  g_Spyro.m_Physics.m_TrueSpeed = 0;
}

void func_8003DFA4(void) {
  VecNull(&g_Spyro.m_Physics.m_TrueVelocity);
  g_Spyro.m_Physics.m_TrueSpeed = 0;
  VecNull(&g_Spyro.m_Physics.m_Acceleration);
  g_Spyro.m_Physics.m_SpeedAngle.m_Speed = 0;
}

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8003DFEC);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8003E0B4);

void func_8003E1AC(void) {
  Vector3D nullVec;
  VecCopy(&g_Spyro.m_Physics.unk_0xdc, &g_Spyro.m_floorPositonOnSlope);
  func_80017330(&g_Spyro.m_Physics.unk_0xdc, ABS(g_Spyro.m_Physics.m_gravity));

  VecNull(&nullVec);

  VecSub(&g_Spyro.m_Physics.unk_0xdc, &nullVec, &g_Spyro.m_Physics.unk_0xdc);
}

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8003E218);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8003E318);

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

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8003E758);

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
  g_Spyro.unk_0x54 = 0;
  g_Spyro.unk_0x5C = g_Spyro.m_State;
}

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8003FE40);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80040F68);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80041270);

/// @brief Cycles through animation states until finding one with a loaded model
/// Sets Spyro's state to the first available animation from the state table
void CycleSpyroAnimation(void) {
  int *stateTable = D_8006BC60;
  u_char *animTable = spyro_StateDefaultAnimation;
  int startIndex = D_80075970;
  Model *spyroModel = g_Models[0];

  do {
    // Advance to next animation index, wrapping at 9
    D_80075970++;
    if (D_80075970 >= 9) {
      D_80075970 = 0;
    }

    // Check if animation is loaded for this state
    // NOTE: The (u_int) casts force correct addu operand order to match
    // original. Without casts, GCC puts the pointer first: addu v0, a1, v0 With
    // casts, GCC puts the index first:   addu v0, v0, a1
    if (D_80075970 == startIndex) {
      // We've cycled through all states
      if (spyroModel->m_Animations[((u_char *)((u_int)stateTable[D_80075970] +
                                               (u_int)animTable))[0]] != 0) {
        break;
      }
      // No valid animation found, set timer and return
      D_80075788 = 0x2710;
      return;
    }
  } while (spyroModel->m_Animations[((u_char *)((u_int)stateTable[D_80075970] +
                                                (u_int)animTable))[0]] == 0);

  func_8003EA68(D_8006BC60[D_80075970]);
}

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80041670);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80043FE4);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80047B60);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8004888C);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80048B9C);

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

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80049660);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_80049880);

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

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8004A7EC);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8004AA0C);

INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/pete", func_8004AC24);
