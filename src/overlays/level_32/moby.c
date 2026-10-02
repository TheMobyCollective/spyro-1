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

INCLUDE_ASM("asm/nonmatchings/overlays/level_32", func_level_32_8007B64C);

// Level specific Moby props
typedef struct {
  int unk_0x00;
  Moby *m_Parent;
  Vector3D unk_0x08;
} MobyLevel32Props;

Moby *func_level_32_8008883C(int pClass, Moby *pParent) {
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

    func_800526A8(moby); // Update collision

    moby->m_Renderer.raw |= 0x80; // Set shiny renderer
    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;
    moby->m_SpecularMetalType = 1; // Set metal type
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
    func_8003A720(moby);       // Reset the Moby first

    moby->m_RenderRadius = 32;
    moby->m_UpdateDistance = 255;

    if (pParent) {
      VecCopy(&moby->m_Position, &pParent->m_Position);
    }

    func_800529CC(moby);

    return moby;
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

    return moby;
  }

  case 152:
  case 153: {
    func_8003A720(moby); // Reset the Moby first

    moby->m_RenderRadius = 32;
    moby->m_UpdateDistance = 255;

    func_800529CC(moby); // Set shaded moby

    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;
    moby->m_SpecularMetalType = 13;
    break;
  }

  // Chest fragments
  case 67:
  case 68:
  case 69:
  case 151:
  case 255:
  case 256:
  case 257:
  case 309:
  case 310:
  case 311: {
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

    if (moby->m_Class >= 309 && moby->m_Class < 312) {
      // Possible union
      ((int *)&moby->m_SpecularMetalColor)[0] = 0xa18618;
      moby->m_Renderer.raw |= 0x80; // Set shiny renderer
    }
    break;
  }

  case MOBYCLASS_CRYSTAL_DRAGON_FRAGMENT: { // Dragon fragment
    Vector3D v; // Name from S2
    int randRes;

    MobyDragonFragmentProps *dragonFragmentProps =
        (MobyDragonFragmentProps *)moby->m_Props;

    func_8003A720(moby); // Reset the Moby first

    moby->m_RenderRadius = 32;
    moby->m_UpdateDistance = 255;

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

    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;
    moby->m_SpecularMetalType = 2;

    textProps->unk_0x0 = 64;
    break;
  }

  case 295: {
    MobyNumberProps *props = moby->m_Props;
    int angle;
    int dist;
    int d;

    func_8003A720(moby); // Reset the Moby first

    moby->m_Position.x =
        pParent->m_Position.x + (COSINE_8(pParent->m_Rotation.z) >> 1);
    moby->m_Position.y =
        pParent->m_Position.y + (SINE_8(pParent->m_Rotation.z) >> 1);
    moby->m_Position.z = pParent->m_Position.z + 0x300;

    angle = (Atan2(g_Spyro.m_Position.x - moby->m_Position.x,
                   g_Spyro.m_Position.y - moby->m_Position.y, 0) -
             pParent->m_Rotation.z) &
            0xFF;

    if (angle >= 0x81) {
      angle -= 0x100;
    }

    if (angle < -0x20) {
      angle = -0x20;
    }

    if (angle >= 0x21) {
      angle = 0x20;
    }

    moby->m_Rotation.z = pParent->m_Rotation.z + angle;

    dist = OctDistance(&moby->m_Position, &g_Spyro);
    d = moby->m_Position.z - 0x164;

    angle = (Atan2(dist, g_Spyro.m_surfaceBelowSpyro - d, 0) -
             pParent->m_Rotation.y) &
            0xFF;

    if (angle >= 0x81) {
      angle -= 0x100;
    }

    if (angle < -0x30) {
      angle = -0x30;
    }

    if (angle >= 0x31) {
      angle = 0x30;
    }

    moby->m_Rotation.y = pParent->m_Rotation.y + angle;

    props->unk_0x4 = 0x5A;
    props->unk_0x0 = 0;

    func_800526A8(moby); // Update collision
    break;
  }

  case 304: {
    MobyLevel32Props *props = moby->m_Props;
    MobyNumberProps *parentProps = pParent->m_Props;
    Vector3D v;
    char pad[8];

    func_8003A720(moby); // Reset the Moby first

    VecCopy(&moby->m_Position, &pParent->m_Position);

    props->m_Parent = pParent;
    props->unk_0x00 = parentProps->unk_0x0;

    VecNull(&props->unk_0x08);

    moby->m_RenderRadius = 32;
    func_800526A8(moby); // Update collision

    moby->m_ShadowDistance = -1;

    VecCopy(&v, &moby->m_Position);

    v.z += 1024;

    func_8004D5EC(&v, 0x10000);

    func_800533D0(moby); // Sets the shadow size to the distance

    return moby;
  }

  case 318: {
    MobyDragonFragmentProps *props = (MobyDragonFragmentProps *)moby->m_Props;

    func_8003A720(moby); // Reset the Moby first

    VecCopy(&moby->m_Position, &pParent->m_Position);

    props->trajectory.x = (rand() & 0x7E) - 0x3F;
    props->trajectory.y = (rand() & 0x7E) - 0x3F;
    props->trajectory.z = (rand() & 0x7E) - 0x10;
    props->initZ = (rand() & 0x1F) + 0x20;

    func_800526A8(moby); // Update collision
    break;
  }

  case 392: {            // Fan chest top
    func_8003A720(moby); // Reset the Moby first
    moby->m_DepthOffset = 5;

    if (pParent) {
      VecCopy(&moby->m_Position, &pParent->m_Position);
    } else {
      VecCopy(&moby->m_Position, &g_Spyro.m_Position);
    }

    func_800526A8(moby); // Update collision
    break;
  }

  case 405: // Drowning splash
  case 477: // Drowning bubbles
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
    moby->m_UpdateDistance = 255;

    func_800529CC(moby); // Set shaded moby

    return moby;
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
