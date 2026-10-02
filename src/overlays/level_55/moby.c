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

INCLUDE_ASM("asm/nonmatchings/overlays/level_55", func_level_55_8007CFB4);

Moby *func_level_55_80082028(int pClass, Moby *pParent) {
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
    lifeOrbProps->m_RotX = 3;
    lifeOrbProps->m_SparkleHandle = -1;
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

  case MOBYCLASS_FLIGHT_TRAIN_BARREL: { // Flight Train Barrel
    func_8003A720(moby); // Reset the Moby first
    func_800526A8(moby); // Update collision
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

  case 232: {
    struct {
      int unk_0x00;
      int unk_0x04;
      int unk_0x08;
      int unk_0x0C;
    } *props = moby->m_Props;
    int angle;

    func_8003A720(moby); // Reset the Moby first

    VecCopy(&moby->m_Position, &pParent->m_Position);

    moby->m_Position.z += 1024;
    func_800526A8(moby); // Update collision

    props->unk_0x04 = 200;
    props->unk_0x08 = 350;

    angle = Atan2(moby->m_Position.x - g_Spyro.m_Position.x,
                  moby->m_Position.y - g_Spyro.m_Position.y, 0);

    props->unk_0x00 = func_80038178(angle, g_Spyro.m_bodyRotation.z, 40, 64);
    props->unk_0x0C = 120;
    break;
  }

  // Flight chest fragments
  case 478:
  case 479:
  case 480: {
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

  case 481: // Flight Train, Wagon and Plane Fragments
  case 482: {
    MobyFragmentProps *props = moby->m_Props;
    int angle1, angle2;

    func_8003A720(moby);
    moby->m_RenderRadius = 32;
    VecCopy(&moby->m_Position, &pParent->m_Position);
    func_800526A8(moby);

    angle1 = rand() & 0xFFF;
    angle2 = rand() & 0x7FF;

    props->unk_0x00 = FIXED_MUL(Cos(angle2) >> 5, Cos(angle1));
    props->unk_0x02 = FIXED_MUL(Cos(angle2) >> 5, Sin(angle1));
    props->unk_0x04 = Sin(angle2) >> 5;

    props->unk_0x00 += g_Spyro.m_Physics.m_Acceleration.x >> 6;
    props->unk_0x02 += g_Spyro.m_Physics.m_Acceleration.y >> 6;
    props->unk_0x04 += g_Spyro.m_Physics.m_Acceleration.z >> 6;

    moby->m_Position.x += props->unk_0x00 * 4;
    moby->m_Position.y += props->unk_0x02 * 4;
    moby->m_Position.z += props->unk_0x04 * 4;

    props->unk_0x06 = rand() & 0xF;
    props->unk_0x08 = rand() & 0xF;
    props->unk_0x0A = rand() & 0xF;
    props->unk_0x10 = pParent->m_Position.z - 64;
    props->unk_0x0C = 64 - (rand() & 0xF);
    break;
  }

  case 359: // Flight Train Barrel Fragments
  case 360:
  case 361: {
    MobyFragmentProps *props = (MobyFragmentProps *)moby->m_Props;

    func_8003A720(moby); // Reset the Moby first

    moby->m_RenderRadius = 32;

    VecCopy(&moby->m_Position, &pParent->m_Position);
    func_800526A8(moby); // Update collision

    moby->m_Rotation.z = rand();

    props->unk_0x00 = COSINE_8(moby->m_Rotation.z & 0xFF) >> 7;
    props->unk_0x02 = SINE_8(moby->m_Rotation.z & 0xFF) >> 7;

    if ((rand() & 1)) {
      props->unk_0x04 = 90;
    } else {
      props->unk_0x04 = -90;
      moby->m_Rotation.x = 128;
    }

    moby->m_Position.x += props->unk_0x00 * 4;
    moby->m_Position.y += props->unk_0x02 * 4;
    moby->m_Position.z += props->unk_0x04 * 4;

    if (props->unk_0x04 < 20) {
      props->unk_0x04 = 20;
    }

    props->unk_0x06 = rand() & 0xF;
    props->unk_0x08 = rand() & 0xF;
    props->unk_0x0A = rand() & 0xF;

    props->unk_0x10 = pParent->m_Position.z - 64;

    props->unk_0x0C = 64 - (rand() & 0xF);
    break;
  }

  case MOBYCLASS_FLIGHT_TRAIN_WHEELS: { // Flight Train wheels
    MobyFragmentProps *targetProps = (MobyFragmentProps *)moby->m_Props;
    MobyFlightTrainProps *parentProps =
        (MobyFlightTrainProps *)pParent->m_Props;
    Vector3D v;
    func_8003A720(moby); // Reset
    moby->m_RenderRadius = 32;
    func_800526A8(moby); // Collision update

    VecCopy((Vector3D *)&targetProps->unk_0x00, &parentProps->unk_0x8);

    targetProps->unk_0x08 = 0;
    targetProps->unk_0x0A = 0;
    targetProps->unk_0x04 += 64;
    targetProps->unk_0x10 = pParent->m_Position.z - 64;
    targetProps->unk_0x0C = 64 - (rand() & 0xF);

    switch (rand() & 3) {
    case 0:
      v.x = 512;
      v.y = 512;
      moby->m_Rotation.z = 64;
      targetProps->unk_0x06 = 16;
      break;

    case 1:
      v.x = 512;
      v.y = -512;
      moby->m_Rotation.z = 192;
      targetProps->unk_0x06 = -16;
      break;

    case 2:
      v.x = -512;
      v.y = 512;
      moby->m_Rotation.z = 64;
      targetProps->unk_0x06 = 16;
      break;

    case 3:
      v.x = -512;
      v.y = -512;
      moby->m_Rotation.z = 192;
      targetProps->unk_0x06 = -16;
      break;
    }
    moby->m_Rotation.z += pParent->m_Rotation.z;
    v.z = 640;

    VecRotateByMatrix((MATRIX *)&pParent->m_RotationMatrix, &v, &v);

    VecAdd(&moby->m_Position, &v, &pParent->m_Position);

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

  case 345: // Flight +1S moby?
  case 346: // Flight +2S moby?
  case 347: // Flight +3S moby?
  {
    if (g_FlightCourseRecords[g_Homeworld]) {
      func_800529CC(moby); // Set shaded moby
      func_80052568(moby);
      moby = nullptr;
    } else {
      func_8003A720(moby); // Reset the Moby first
      if (pParent != nullptr) {
        VecCopy(&moby->m_Position, &pParent->m_Position);
      }
      moby->m_RenderRadius = 64;
      func_800529CC(moby); // Set shaded moby
      moby->m_SpecularMetalColor[0] = 0;
      moby->m_SpecularMetalColor[1] = 0;
      moby->m_SpecularMetalColor[2] = 0;
      moby->m_SpecularMetalType = 2;
    }
    break;
  }

  case 389:
  case 394:
  case 490:
  case 491: {
    func_8003A720(moby); // Reset the Moby first
    moby->m_RenderRadius = 0;
    moby->m_Position.x = -100;
    moby->m_Position.y = 30;
    moby->m_Position.z = 4096;

    func_800529CC(moby); // Set shaded moby
    moby->m_DepthOffset = 32;
    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;
    moby->m_SpecularMetalType = 0;
    break;
  }

  case 399: {            // ... Portal path Moby??
    func_8003A720(moby); // Reset the Moby first

    moby->m_RenderRadius = 255;

    moby->m_Position.x = 460;
    moby->m_Position.y = 40;
    moby->m_Position.z = 4096;

    func_800529CC(moby); // Set shaded moby

    moby->m_DepthOffset = 32;

    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;
    moby->m_SpecularMetalType = 0;

    break;
  }

  case 477: // Drowning bubbles
  case 405: // Drowning splash
  case 400: {
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
