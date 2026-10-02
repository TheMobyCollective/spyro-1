#include "common.h"
#include "42CC4.h"
#include "collision.h"
#include "dragon.h"
#include "math.h"
#include "moby_helpers.h"
#include "overlay_pointers.h"
#include "rand.h"
#include "spyro.h"
#include "variables.h"

INCLUDE_ASM("asm/nonmatchings/overlays/level_30", func_level_30_8007E398);

Moby *func_level_30_8008B2C0(int pClass, Moby *pParent) {
  u_long idx;
  Moby *moby = func_800524C4();
  moby->m_Class = pClass;
  if (pParent) {
    idx = pParent - g_LevelMobys;
    if (idx > 0xFF) {
      idx = 0;
    }
  } else {
    idx = 0;
  }
  moby->m_MobyIndex = idx;
  switch (pClass) {
  case MOBYCLASS_LIFE_ORB: {
    MobyCollectableProps *lifeOrbProps = moby->m_Props;
    func_8003A720(moby);
    lifeOrbProps->m_InitPos.x = 0;
    lifeOrbProps->m_InitPos.y = 0;
    lifeOrbProps->m_InitPos.z = 140;
    lifeOrbProps->m_SpawnState = 0;
    lifeOrbProps->m_Ticks = 0;
    lifeOrbProps->m_RotX = 3;
    lifeOrbProps->m_RotY = 0;
    lifeOrbProps->m_RotZ = 0;
    lifeOrbProps->m_RotationTicks = 0;
    lifeOrbProps->m_SparkleHandle = -1;
    moby->m_Substate = 2;
    moby->m_RenderRadius = 24;
    moby->m_UpdateDistance = 16;
    moby->m_Rotation.x = 32;
    moby->m_Rotation.y = 0;
    moby->m_Rotation.z = 0;
    if (pParent) {
      VecCopy(&moby->m_Position, &pParent->m_Position);
    }
    func_800526A8(moby);
    moby->m_Renderer.raw |= 0x80;
    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;
    moby->m_SpecularMetalType = 1;
    break;
  }
  case MOBYCLASS_BUTTERFLY: {
    MobyButterflyProps *butterflyProps = (MobyButterflyProps *)moby->m_Props;
    func_8003A720(moby);
    func_800526A8(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);
    moby->m_Position.z += 512;
    VecCopy(&butterflyProps->unk_0x04, &moby->m_Position);
    butterflyProps->unk_0x13 = 0;
    butterflyProps->unk_0x12 = 0;
    butterflyProps->unk_0x14 = 1800;
    break;
  }
  case MOBYCLASS_DRAGON_EGG: {
    func_8003A720(moby);
    moby->m_RenderRadius = 32;
    moby->m_UpdateDistance = 255;
    if (pParent) {
      VecCopy(&moby->m_Position, &pParent->m_Position);
    }
    func_800529CC(moby);
    break;
  }
  case 38: {
    int *props = moby->m_Props;
    int angle;

    func_8003A720(moby); // Reset the Moby first

    VecCopy(&moby->m_Position, &pParent->m_Position);

    if (pParent->m_Class == pClass) {
      moby->m_Rotation.z = pParent->m_Rotation.z;
      moby->m_State = 3;
      moby->m_AnimationState.m_FrameProgress = 0;
      moby->m_AnimationState.m_PerFrameProgress =
          g_Models[moby->m_Class]->m_Animations[3]->m_ProgressPerTick;
      moby->m_AnimationState.m_Animation = 3;
      moby->m_AnimationState.m_NextAnimation = 3;
      props[0] = 3;
    } else if (pParent->m_AnimationState.m_NextFrame >= 6) {

      moby->m_Position.x += Cos(pParent->m_Rotation.z << 4) >> 2;
      moby->m_Position.y += Sin(pParent->m_Rotation.z << 4) >> 2;
      moby->m_Position.z += 0x12C;

      moby->m_Rotation.z = pParent->m_Rotation.z;

      angle = (Atan2(OctDistance(&moby->m_Position, &g_Spyro),
                     g_Spyro.m_Position.z - moby->m_Position.z, 0) -
               pParent->m_Rotation.y) &
              0xFF;

      if (angle > 0x80) {
        angle -= 0x100;
      }

      if (angle < -0x10) {
        angle = -0x10;
      }

      if (angle >= 0x11) {
        angle = 0x10;
      }

      moby->m_Rotation.y = pParent->m_Rotation.y + angle;

      props[0] = 0x80;

      moby->m_State = 2;
      moby->m_AnimationState.m_FrameProgress = 0;
      moby->m_AnimationState.m_PerFrameProgress =
          g_Models[moby->m_Class]->m_Animations[2]->m_ProgressPerTick;
      moby->m_AnimationState.m_Animation = 2;
      moby->m_AnimationState.m_NextAnimation = 2;

      D_800758E4(4, 7, &moby->m_Position, 0x10);
    } else {
      if (pParent->m_AnimationState.m_NextFrame >= 2) {
        moby->m_Position.z += 0x12C;

        moby->m_Rotation.z = pParent->m_Rotation.z;
        moby->m_State = 1;
        moby->m_AnimationState.m_FrameProgress = 0;
        moby->m_AnimationState.m_PerFrameProgress =
            g_Models[moby->m_Class]->m_Animations[1]->m_ProgressPerTick;
        moby->m_AnimationState.m_Animation = 1;
        moby->m_AnimationState.m_NextAnimation = 1;

      } else {
        moby->m_Position.z += 0x180;
        moby->m_Rotation.z = pParent->m_Rotation.z;
      }
      props[0] = 2;
    }
    func_800526A8(moby);
    break;
  }

  case MOBYCLASS_LIFE_STATUE:
  case MOBYCLASS_GEM_1:
  case MOBYCLASS_GEM_2:
  case MOBYCLASS_GEM_5:
  case MOBYCLASS_GEM_10:
  case MOBYCLASS_GEM_25: {
    Vector3D v;
    MobyCollectableProps *gemProps = (MobyCollectableProps *)moby->m_Props;
    func_8003A720(moby);
    gemProps->m_InitPos.x = 0;
    gemProps->m_InitPos.y = 0;
    gemProps->m_InitPos.z = 140;
    gemProps->m_SpawnState = 0;
    gemProps->m_Ticks = 0;
    gemProps->m_RotY = 0;
    gemProps->m_RotZ = 0;
    gemProps->m_RotationTicks = 0;
    if (pParent->m_Class == 13) {
      gemProps->m_RotX = 2;
    } else {
      gemProps->m_RotX = 3;
    }
    gemProps->m_SparkleHandle = -1;
    moby->m_Substate = 2;
    moby->m_RenderRadius = 24;
    moby->m_UpdateDistance = 64;
    moby->m_Rotation.x = 32;
    moby->m_Rotation.y = 0;
    moby->m_Rotation.z = 0;
    VecCopy(&moby->m_Position, &pParent->m_Position);
    func_800529CC(moby);
    moby->m_ShadowDistance = -1;
    VecCopy(&v, &moby->m_Position);
    v.z += 1024;
    func_8004D5EC(&v, 0x10000);
    func_800533D0(moby);
    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;
    if (moby->m_Class == MOBYCLASS_LIFE_STATUE) {
      moby->m_SpecularMetalType = 12;
    }
    if (moby->m_Class == MOBYCLASS_GEM_1) {
      moby->m_SpecularMetalType = 1;
    }
    if (moby->m_Class == MOBYCLASS_GEM_2) {
      moby->m_SpecularMetalType = 2;
    }
    if (moby->m_Class == MOBYCLASS_GEM_5) {
      moby->m_SpecularMetalType = 3;
    }
    if (moby->m_Class == MOBYCLASS_GEM_10) {
      moby->m_SpecularMetalType = 4;
    }
    if (moby->m_Class == MOBYCLASS_GEM_25) {
      moby->m_SpecularMetalType = 5;
    }
    break;
  }
  case 120: {
    MobySparxProps *sparxProps = (MobySparxProps *)moby->m_Props;
    func_8003A720(moby);
    func_800526A8(moby);
    moby->m_Substate = 0;
    sparxProps->unk_0x00 = 0;
    sparxProps->unk_0x08 = 0;
    sparxProps->unk_0x06 = 0;
    sparxProps->unk_0x04 = 0;
    sparxProps->glow = 0;
    sparxProps->unk_0x10 = 0;
    if (pParent) {
      VecCopy(&moby->m_Position, &pParent->m_Position);
    }
    break;
  }
  case 255:
  case 256:
  case 257:
  case 67:
  case 68:
  case 69:
  case 309:
  case 310:
  case 311:
  case 423:
  case 424:
  case 425:
  {
    MobyFragmentProps *fragmentProps = moby->m_Props;
    int angle1;
    int angle2;
    func_8003A720(moby);
    moby->m_RenderRadius = 32;
    VecCopy(&moby->m_Position, &pParent->m_Position);
    func_800526A8(moby);
    angle2 = rand() & 0xFFF;
    angle1 = rand() & 0x7FF;
    fragmentProps->unk_0x00 = FIXED_MUL(Cos(angle1) >> 5, Cos(angle2));
    fragmentProps->unk_0x02 = FIXED_MUL(Cos(angle1) >> 5, Sin(angle2));
    fragmentProps->unk_0x04 = Sin(angle1) >> 5;
    if (pParent->m_DamageFlags & 0x20000) {
      fragmentProps->unk_0x00 += g_Spyro.m_Physics.m_Acceleration.x >> 6;
      fragmentProps->unk_0x02 += g_Spyro.m_Physics.m_Acceleration.y >> 6;
      fragmentProps->unk_0x04 += g_Spyro.m_Physics.m_Acceleration.z >> 6;
    }
    moby->m_Position.x += fragmentProps->unk_0x00 * 4;
    moby->m_Position.y += fragmentProps->unk_0x02 * 4;
    moby->m_Position.z += fragmentProps->unk_0x04 * 4;
    fragmentProps->unk_0x06 = rand() & 0xF;
    fragmentProps->unk_0x08 = rand() & 0xF;
    fragmentProps->unk_0x0A = rand() & 0xF;
    fragmentProps->unk_0x10 = pParent->m_Position.z - 64;
    fragmentProps->unk_0x0C = 64 - (rand() & 0xF);
    if (moby->m_Class >= 309 && moby->m_Class < 312) {
      ((int *)&moby->m_SpecularMetalColor)[0] = 0xa18618;
      moby->m_Renderer.raw |= 0x80;
    }
    break;
  }
  case 251: {
    Vector3D v;
    char pad[8];
    int randRes;
    MobyDragonFragmentProps *dragonFragmentProps =
        (MobyDragonFragmentProps *)moby->m_Props;
    func_8003A720(moby);
    moby->m_RenderRadius = 32;
    moby->m_UpdateDistance = -1;
    func_800529CC(moby);
    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;
    moby->m_SpecularMetalType = 14;
    if (g_DragonCutscene.m_State == 3) {
      moby->m_ScaleOverride = 20;
    } else if (g_DragonCutscene.m_State == 1) {
      moby->m_ScaleOverride = 48;
    }
    randRes = rand() & 7;
    v.x = D_8006F3A0[randRes][0];
    v.y = 0;
    v.z = D_8006F3A0[randRes][1];
    VecRotateByMatrix((MATRIX *)&pParent->m_RotationMatrix, &v, &v);
    v.x += -63 + (rand() & 127);
    v.y += -63 + (rand() & 127);
    v.z += -63 + (rand() & 127);
    VecAdd(&moby->m_Position, &pParent->m_Position, &v);
    VecCopy(&dragonFragmentProps->trajectory, &v);
    VecShiftRight(&dragonFragmentProps->trajectory, 2);
    dragonFragmentProps->trajectory.x += -127 + (rand() & 255);
    dragonFragmentProps->trajectory.y += -127 + (rand() & 255);
    dragonFragmentProps->trajectory.z += -127 + (rand() & 255);
    moby->m_Rotation.x = rand();
    moby->m_Rotation.y = rand();
    moby->m_Rotation.z = rand();
    dragonFragmentProps->unk_0x10 = rand() & 0xf;
    dragonFragmentProps->unk_0x11 = rand() & 0xf;
    dragonFragmentProps->unk_0x12 = rand() & 0xf;
    dragonFragmentProps->initZ = pParent->m_Position.z;
    dragonFragmentProps->m_Lifetime = (rand() & 3) + 16;
    break;
  }
  case MOBYCLASS_NUMBER_0:
  case MOBYCLASS_NUMBER_1:
  case MOBYCLASS_NUMBER_2:
  case MOBYCLASS_NUMBER_3:
  case MOBYCLASS_NUMBER_4:
  case MOBYCLASS_NUMBER_5:
  case MOBYCLASS_NUMBER_6:
  case MOBYCLASS_NUMBER_7:
  case MOBYCLASS_NUMBER_8:
  case MOBYCLASS_NUMBER_9:
  case 277:
  case 327:
  {
    MobyNumberProps *textProps = moby->m_Props;
    func_8003A720(moby);
    func_800529CC(moby);
    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;
    moby->m_SpecularMetalType = 2;
    textProps->unk_0x0 = 64;
    break;
  }
  case 392: {
    func_8003A720(moby);
    moby->m_DepthOffset = 5;
    if (pParent) {
      VecCopy(&moby->m_Position, &pParent->m_Position);
    } else {
      VecCopy(&moby->m_Position, &g_Spyro.m_Position);
    }
    func_800526A8(moby);
    break;
  }
  case 398: {
    func_8003A720(moby);
    moby->m_RenderRadius = -1;
    moby->m_Position.x = 460;
    moby->m_Position.y = 40;
    moby->m_Position.z = 4096;
    func_800529CC(moby);
    moby->m_DepthOffset = 32;
    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;
    moby->m_SpecularMetalType = 0;
    break;
  }
  case 477:
  case 405:
  {
    int d, dt;
    func_8003A720(moby);
    if (pParent) {
      VecCopy(&moby->m_Position, &pParent->m_Position);
    } else {
      VecCopy(&moby->m_Position, &g_Spyro.m_Position);
    }
    moby->m_Position.z += 512;
    d = func_8004D5EC(&moby->m_Position, 2048);
    dt = d - moby->m_Position.z;
    if (dt < 0)
      dt = -dt;
    if (dt < 2048) {
      moby->m_Position.z = d;
    } else {
      moby->m_Position.z -= 512;
    }
    func_800526A8(moby);
    break;
  }
  case MOBYCLASS_LETTER_APOSTROPHE:
  case MOBYCLASS_LETTER_A:
  case MOBYCLASS_LETTER_B:
  case MOBYCLASS_LETTER_C:
  case MOBYCLASS_LETTER_D:
  case MOBYCLASS_LETTER_E:
  case MOBYCLASS_LETTER_F:
  case MOBYCLASS_LETTER_G:
  case MOBYCLASS_LETTER_H:
  case MOBYCLASS_LETTER_I:
  case MOBYCLASS_LETTER_J:
  case MOBYCLASS_LETTER_K:
  case MOBYCLASS_LETTER_L:
  case MOBYCLASS_LETTER_M:
  case MOBYCLASS_LETTER_N:
  case MOBYCLASS_LETTER_O:
  case MOBYCLASS_LETTER_P:
  case MOBYCLASS_LETTER_Q:
  case MOBYCLASS_LETTER_R:
  case MOBYCLASS_LETTER_S:
  case MOBYCLASS_LETTER_T:
  case MOBYCLASS_LETTER_U:
  case MOBYCLASS_LETTER_V:
  case MOBYCLASS_LETTER_W:
  case MOBYCLASS_LETTER_X:
  case MOBYCLASS_LETTER_Y:
  case MOBYCLASS_LETTER_Z: {
    func_8003A720(moby);
    moby->m_RenderRadius = 32;
    moby->m_UpdateDistance = -1;
    func_800529CC(moby);
    break;
  }
  default:
    func_8003A720(moby);
    if (pParent) {
      VecCopy(&moby->m_Position, &pParent->m_Position);
    } else {
      VecCopy(&moby->m_Position, &g_Spyro.m_Position);
    }
    func_800526A8(moby);
    break;
  }
  return moby;
}
