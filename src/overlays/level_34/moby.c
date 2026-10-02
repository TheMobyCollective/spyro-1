#include "common.h"
#include "42CC4.h"
#include "camera.h"
#include "collision.h"
#include "dragon.h"
#include "math.h"
#include "moby_helpers.h"
#include "overlay_pointers.h"
#include "rand.h"
#include "spyro.h"
#include "variables.h"

INCLUDE_ASM("asm/nonmatchings/overlays/level_34", func_level_34_8007AF28);

Moby *func_level_34_80083AB4(int pClass, Moby *pParent) {
  u_long idx;

  // Allocate a new moby
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

  case MOBYCLASS_LIFE_ORB: { // Extra life orb
    MobyCollectableProps *lifeOrbProps = moby->m_Props;

    func_8003A720(moby); // Reset the Moby first

    lifeOrbProps->m_InitPos.z = 140;
    lifeOrbProps->m_RotX = 3;
    lifeOrbProps->m_SparkleHandle = -1;
    lifeOrbProps->m_InitPos.x = 0;
    lifeOrbProps->m_InitPos.y = 0;
    lifeOrbProps->m_SpawnState = 0;
    lifeOrbProps->m_Ticks = 0;
    lifeOrbProps->m_RotY = 0;
    lifeOrbProps->m_RotZ = 0;
    lifeOrbProps->m_RotationTicks = 0;

    moby->m_Substate = 2;
    moby->m_RenderRadius = 24;
    moby->m_UpdateDistance = 16;

    moby->m_Rotation.x = 32;
    moby->m_Rotation.y = 0;
    moby->m_Rotation.z = 0;

    if (pParent) {
      VecCopy(&moby->m_Position, &pParent->m_Position);
    }

    func_800526A8(moby); // Update collision

    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;
    moby->m_SpecularMetalType = 1; // Set metal type

    moby->m_Renderer.raw |= 0x80; // Set shiny renderer
    break;
  }

  case MOBYCLASS_BUTTERFLY: { // Butterfly
    MobyButterflyProps *butterflyProps = (MobyButterflyProps *)moby->m_Props;

    func_8003A720(moby); // Reset the Moby first
    func_800526A8(moby); // Update collision
    VecCopy(&moby->m_Position, &pParent->m_Position);

    moby->m_Position.z += 512;
    VecCopy(&butterflyProps->unk_0x04, &moby->m_Position);

    butterflyProps->unk_0x13 = 0;
    butterflyProps->unk_0x12 = 0;
    butterflyProps->unk_0x14 = 1800;
    break;
  }

  case MOBYCLASS_DRAGON_EGG: { // Dragon Egg
    func_8003A720(moby); // Reset the Moby first

    moby->m_RenderRadius = 32;
    moby->m_UpdateDistance = 255;

    if (pParent) {
      VecCopy(&moby->m_Position, &pParent->m_Position);
    }

    func_800529CC(moby);

    break;
  }

  case 37: {
    struct {
      Moby *unk_0x0;
      short unk_0x4;
      short unk_0x6;
      int unk_0x8;
      int unk_0xC;
      char unk_0x10;
    } *props = moby->m_Props;
    Vector3D v;
    int progress;

    func_8003A720(moby); // Reset the Moby first

    moby->m_ShadowDistance = -1;

    VecCopy(&v, &moby->m_Position);

    v.z += 1024;

    func_8004D5EC(&v, 0x10000);

    func_800533D0(moby); // Sets the shadow size to the distance

    switch (pParent->m_State) {
    case 0x48:
      props->unk_0x10 = 1;
      props->unk_0x4 = 0x40;
      props->unk_0x6 = 0xE00;
      break;

    case 0x52:
      props->unk_0x10 = 2;
      props->unk_0x4 = 0x100;
      props->unk_0x6 = 0x2000;
      break;

    case 0x5C:
      props->unk_0x10 = 3;
      props->unk_0x4 = 0x140;
      props->unk_0x6 = 0x2000;
      break;
    }

    moby->m_Position.x =
        pParent->m_Position.x + (COSINE_8(pParent->m_Rotation.z) * 4 >> 4);
    moby->m_Position.y =
        pParent->m_Position.y + (SINE_8(pParent->m_Rotation.z) * 4 >> 4);
    moby->m_Position.z = pParent->m_Position.z;

    props->unk_0x0 = pParent;
    props->unk_0xC = 0;

    moby->m_State = 0;

    progress = g_Models[moby->m_Class]->m_Animations[0]->m_ProgressPerTick;
    moby->m_AnimationState.m_NextAnimation = 0;
    moby->m_AnimationState.m_Animation = 0;
    moby->m_AnimationState.m_NextFrame = 0;
    moby->m_AnimationState.m_Frame = 0;
    moby->m_AnimationState.m_PerFrameProgress = progress;

    func_800526A8(moby); // Update collision
    break;
  }

  case 38: {
    struct {
      int unk_0x0;
    } *props = moby->m_Props;
    int angle;
    int progress;

    func_8003A720(moby); // Reset the Moby first

    VecCopy(&moby->m_Position, &pParent->m_Position);

    if (pParent->m_Class == 38) {
      moby->m_Rotation.z = pParent->m_Rotation.z;
      moby->m_State = 3;
      moby->m_AnimationState.m_FrameProgress = 0;
      progress = g_Models[moby->m_Class]->m_Animations[3]->m_ProgressPerTick;
      moby->m_AnimationState.m_Animation = 3;
      moby->m_AnimationState.m_NextAnimation = 3;
      moby->m_AnimationState.m_PerFrameProgress = progress;

      props->unk_0x0 = 3;
    } else if (pParent->m_AnimationState.m_NextFrame >= 6) {
      moby->m_Position.x += Cos(pParent->m_Rotation.z << 4) >> 2;
      moby->m_Position.y += Sin(pParent->m_Rotation.z << 4) >> 2;
      moby->m_Position.z += 300;
      moby->m_Rotation.z = pParent->m_Rotation.z;

      angle = Atan2(OctDistance(&moby->m_Position, &g_Spyro),
                    g_Spyro.m_Position.z - moby->m_Position.z, 0);
      angle = (angle - pParent->m_Rotation.y) & 0xFF;
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

      props->unk_0x0 = 0x80;

      moby->m_State = 2;
      moby->m_AnimationState.m_FrameProgress = 0;
      progress = g_Models[moby->m_Class]->m_Animations[2]->m_ProgressPerTick;
      moby->m_AnimationState.m_Animation = 2;
      moby->m_AnimationState.m_NextAnimation = 2;
      moby->m_AnimationState.m_PerFrameProgress = progress;

      (*D_800758E4)(4, 7, &moby->m_Position, (void *)0x10);
    } else if (pParent->m_AnimationState.m_NextFrame >= 2) {
      moby->m_Position.z += 300;
      moby->m_Rotation.z = pParent->m_Rotation.z;
      moby->m_State = 1;
      moby->m_AnimationState.m_FrameProgress = 0;
      progress = g_Models[moby->m_Class]->m_Animations[1]->m_ProgressPerTick;
      moby->m_AnimationState.m_Animation = 1;
      moby->m_AnimationState.m_NextAnimation = 1;
      moby->m_AnimationState.m_PerFrameProgress = progress;

      props->unk_0x0 = 2;
    } else {
      moby->m_Position.z += 384;
      moby->m_Rotation.z = pParent->m_Rotation.z;

      props->unk_0x0 = 2;
    }

    func_800526A8(moby); // Update collision
    break;
  }

  case 39: {
    struct {
      int unk_0x0;
      Moby *unk_0x4;
      int unk_0x8;
    } *props = moby->m_Props;

    func_8003A720(moby); // Reset the Moby first

    VecCopy(&moby->m_Position, &pParent->m_Position);

    func_800526A8(moby); // Update collision

    moby->m_Rotation.z = Atan2(g_Camera.m_Position.x - moby->m_Position.x,
                               g_Camera.m_Position.y - moby->m_Position.y, 0);

    moby->m_Position.z -= 0x400;

    props->unk_0x0 = 0x40;
    props->unk_0x4 = pParent;
    props->unk_0x8 = 1;
    break;
  }

  case MOBYCLASS_LIFE_STATUE:
  case MOBYCLASS_GEM_1:
  case MOBYCLASS_GEM_2:
  case MOBYCLASS_GEM_5:
  case MOBYCLASS_GEM_10:
  case MOBYCLASS_GEM_25: { // Collectables
    Vector3D v;            // Name from S2
    MobyCollectableProps *gemProps = (MobyCollectableProps *)moby->m_Props;

    func_8003A720(moby); // Reset the Moby first

    gemProps->m_InitPos.x = 0;
    gemProps->m_InitPos.y = 0;
    gemProps->m_InitPos.z = 140; // Uh

    gemProps->m_SpawnState = 0;
    gemProps->m_Ticks = 0;

    gemProps->m_RotY = 0;
    gemProps->m_RotZ = 0;

    gemProps->m_RotationTicks = 0;

    // Not sure about that
    if (pParent->m_Class == 13) {
      gemProps->m_RotX = 2;
    } else {
      gemProps->m_RotX = 3;
    }

    gemProps->m_SparkleHandle = -1; // Unset the sparkle handle

    moby->m_Substate = 2;
    moby->m_RenderRadius = 24;
    moby->m_UpdateDistance = 64;

    moby->m_Rotation.x = 32;
    moby->m_Rotation.y = 0;
    moby->m_Rotation.z = 0;

    VecCopy(&moby->m_Position, &pParent->m_Position);
    func_800529CC(moby); // Set shaded moby

    moby->m_ShadowDistance = -1;

    VecCopy(&v, &moby->m_Position);

    v.z += 1024;

    func_8004D5EC(&v, 0x10000);

    func_800533D0(moby); // Sets the shadow size to the distance

    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;

    if (moby->m_Class == MOBYCLASS_LIFE_STATUE) {
      // Extra life statue
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

  case MOBYCLASS_SPARX: { // Sparx
    MobySparxProps *sparxProps = (MobySparxProps *)moby->m_Props;

    func_8003A720(moby); // Reset the Moby first
    func_800526A8(moby); // Update collision

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

  case 152:
  case 153: {
    func_8003A720(moby); // Reset the Moby first

    moby->m_RenderRadius = 32;
    moby->m_UpdateDistance = -1;

    func_800529CC(moby); // Set shaded moby

    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;

    moby->m_SpecularMetalType = 13;
    break;
  }

  case 67:
  case 68:
  case 69:
  case 255:
  case 256:
  case 257:
  case 309:
  case 310:
  case 311:
  case 151: {
    MobyFragmentProps *fragmentProps = moby->m_Props;

    int angle1;
    int angle2;

    func_8003A720(moby); // Reset the Moby first

    moby->m_RenderRadius = 32;
    VecCopy(&moby->m_Position, &pParent->m_Position);

    func_800526A8(moby); // Update collision

    angle2 = rand() & 0xFFF;
    angle1 = rand() & 0x7FF;

    fragmentProps->unk_0x00 = FIXED_MUL(Cos(angle1) >> 5, Cos(angle2));
    fragmentProps->unk_0x02 = FIXED_MUL(Cos(angle1) >> 5, Sin(angle2));
    fragmentProps->unk_0x04 = Sin(angle1) >> 5;

    // Charge damage
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

    if ((u_short)moby->m_Class - 309u < 3u) {
      // Possible union
      ((int *)&moby->m_SpecularMetalColor)[0] = 0xa18618;
      moby->m_Renderer.raw |= 0x80; // Set shiny renderer
    }
    break;
  }

  case MOBYCLASS_CRYSTAL_DRAGON_FRAGMENT: { // Dragon fragment
    Vector3D v;                              // Name from S2
    char pad[8];
    int randRes;

    MobyDragonFragmentProps *dragonFragmentProps =
        (MobyDragonFragmentProps *)moby->m_Props;

    func_8003A720(moby); // Reset the Moby first

    moby->m_RenderRadius = 32;
    moby->m_UpdateDistance = -1;

    func_800529CC(moby); // Set shaded moby

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

  case MOBYCLASS_NUMBER_0: // Text 0-9
  case MOBYCLASS_NUMBER_1:
  case MOBYCLASS_NUMBER_2:
  case MOBYCLASS_NUMBER_3:
  case MOBYCLASS_NUMBER_4:
  case MOBYCLASS_NUMBER_5:
  case MOBYCLASS_NUMBER_6:
  case MOBYCLASS_NUMBER_7:
  case MOBYCLASS_NUMBER_8:
  case MOBYCLASS_NUMBER_9:
  case MOBYCLASS_SLASH:  // Text Slash
  case MOBYCLASS_PERIOD: // Hud .
  {
    MobyNumberProps *textProps = moby->m_Props;

    func_8003A720(moby); // Reset the Moby first
    func_800529CC(moby); // Set shaded moby

    moby->m_SpecularMetalType = 2;

    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;

    textProps->unk_0x0 = 64;
    break;
  }

  case 405: // Drowning bubbles
  case 477: // Drowning splash
  {
    int d, dt;

    func_8003A720(moby); // Reset the Moby first

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

    func_800526A8(moby); // Update collision

    break;
  }

  // And then.. these?
  case MOBYCLASS_LETTER_APOSTROPHE:
  case MOBYCLASS_LETTER_A: // Text A-Z
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
    func_8003A720(moby); // Reset the Moby first

    moby->m_RenderRadius = 32;
    moby->m_UpdateDistance = -1;

    func_800529CC(moby); // Set shaded moby
    break;
  }

  default:
    func_8003A720(moby); // Reset the Moby first

    if (pParent) {
      VecCopy(&moby->m_Position, &pParent->m_Position);
    } else {
      VecCopy(&moby->m_Position, &g_Spyro.m_Position);
    }

    func_800526A8(moby); // Update collision
    break;
  }

  return moby;
}
