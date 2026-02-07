#include "42CC4.h"
#include "collision.h"
#include "dragon.h"
#include "math.h"
#include "moby_helpers.h"
#include "overlay_pointers.h"
#include "spyro.h"
#include "variables.h"
#include "rand.h"

// We have to replace LEVEL with preprocessor LEVEL

Moby *NAME_OVERLAY_FUNCTION(SpawnMoby)(int pClass, Moby *pParent) {
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
#ifdef HAS_MOBY_17
  case 17: {
    Moby17Props *props;
    Vector3D v;
    func_8003A720(moby); // Reset the Moby first
    moby->m_Rotation.z = pParent->m_Rotation.z;
    moby->m_Position.x = pParent->m_Position.x + (COSINE_8(moby->m_Rotation.z) >> 4);
    moby->m_Position.y = pParent->m_Position.y + (SINE_8(moby->m_Rotation.z) >> 4);
    moby->m_Position.z = pParent->m_Position.z;
    v.x = g_Spyro.m_Position.x - moby->m_Position.x;
    v.y = g_Spyro.m_Position.y - moby->m_Position.y;
    v.z = g_Spyro.m_Position.z - moby->m_Position.z;
    VecScaleToLength(&v, VecMagnitude(&v, 1), 0xa0);
    func_800526A8(moby); // Update collision
    props = (Moby17Props *)moby->m_Props;
    VecCopy(&props->unk_0x00, &v);
    props->unk_0x0C = 0x50;
    break;
  }
#endif
  case MOBYCLASS_DRAGON_EGG: { // Dragon Egg
    func_8003A720(moby);       // Reset the Moby first

    moby->m_RenderRadius = 32;
    moby->m_UpdateDistance = 255;

    if (pParent) {
      VecCopy(&moby->m_Position, &pParent->m_Position);
    }

    func_800529CC(moby);

    break;
  }
#ifdef HAS_MOBY_78
case 78: { // Flight Train Barrel
    func_8003A720(moby); // Reset the Moby first
    func_800526A8(moby); // Update collision
      break;
  }
#endif
  case MOBYCLASS_LIFE_STATUE:
  case MOBYCLASS_GEM_1:
  case MOBYCLASS_GEM_2:
  case MOBYCLASS_GEM_5:
  case MOBYCLASS_GEM_10:
  case MOBYCLASS_GEM_25: { // Collectables
    Vector3D v; // Name from S2
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

  case 120: { // Sparx
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

#ifdef HAS_MOBY_234
  case 234: {
    func_8003A720(moby); // Reset the Moby first
    VecCopy(&moby->m_Position, &g_Spyro.unk_0x17c);
    moby->m_Rotation.z = Atan2(g_Spyro.m_KnockbackDirection.x,
                               g_Spyro.m_KnockbackDirection.y, 0) +
                         64;
    func_800526A8(moby); // Update collision
    break;
  }
#endif

#ifdef HAS_MOBY_194
#define HAS_ANY_CHEST_FRAGMENTS
  // Wooden chest fragments
  case 255:
  case 256:
  case 257:
#endif

#ifdef HAS_MOBY_329
#define HAS_ANY_CHEST_FRAGMENTS
  // Spring chest fragments
  case 67:
  case 68:
  case 69:
#endif

#if defined(HAS_MOBY_195) || \
    defined(HAS_MOBY_174) || \
    defined(HAS_MOBY_401)
#define HAS_ANY_CHEST_FRAGMENTS
  case 309: // Metal, locked and armored chest fragments
  case 310:
  case 311:
#endif

#ifdef HAS_MOBY_421
#define HAS_ANY_CHEST_FRAGMENTS
  case 423: // Extra life chest piece 1
  case 424: // Extra life chest piece 2
  case 425: // Extra life chest piece 3
#endif

#ifdef HAS_MOBY_299
#define HAS_ANY_CHEST_FRAGMENTS
  case 478: // Flight chest fragments
  case 479:
  case 480:
#endif
#ifdef HAS_ANY_CHEST_FRAGMENTS

  {
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
#endif
#ifdef HAS_MOBY_250
  case 251: { // Dragon fragment
    Vector3D v; // Name from S2
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
#endif
#if defined(HAS_MOBY_407) || \
    defined(HAS_MOBY_408) || \
    defined(HAS_MOBY_308)
  case 481: // Flight Train, Wagon and Plane Fragments
  case 482:
  case 483: {
    MobyFragmentProps *props = moby->m_Props;
    int angle1, angle2;

    func_8003A720(moby);
    moby->m_RenderRadius = 32;
    VecCopy(&moby->m_Position, &pParent->m_Position);
    func_800526A8(moby);

    angle1 = rand() & 0xFFF;
    angle2 = rand() & 0x7FF;

    props->unk_0x00 = FIXED_MUL(Cos(angle2) >> 5, Cos(angle1 & 0xFFF));
    props->unk_0x02 = FIXED_MUL(Cos(angle2) >> 5, Sin(angle1 & 0xFFF));
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
#endif

#ifdef HAS_MOBY_78
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
#endif
#if defined(HAS_MOBY_407) || \
    defined(HAS_MOBY_408)
  case 362: { // Flight Train wheels
    MobyFragmentProps *targetProps = (MobyFragmentProps *)moby->m_Props;
    FlightTrainMobyData *parentProps = (FlightTrainMobyData*)pParent->m_Props;
    int rnd;
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
#endif


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
  case 277: // Text Slash
  case 327: // Hud .
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

#ifdef HAS_MOBY_345
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
#endif
#ifdef HAS_MOBY_353
  case 374: { // Flight Gate Fragment
    func_8003A720(moby); // Reset the Moby first
    VecCopy(&moby->m_Position, &pParent->m_Position);
    moby->m_Rotation = pParent->m_Rotation;
    func_800526A8(moby); // Update collision
    moby->m_Renderer.raw = 0xbf;
    moby->m_SpecularMetalColor[0] = pParent->m_SpecularMetalColor[0];
    moby->m_SpecularMetalColor[1] = pParent->m_SpecularMetalColor[1];
    moby->m_SpecularMetalColor[2] = pParent->m_SpecularMetalColor[2];
    moby->m_SpecularMetalType = pParent->m_SpecularMetalType;
    moby->m_RenderRadius = pParent->m_RenderRadius;
    break;
  }
#endif

#ifdef HAS_MOBY_353
  case 375: // Flight Gate Remaining Fragments
  case 376:
  case 377:
  case 378:
  case 379:
  case 380:
  case 381:
  case 382:
  case 383:
  case 384:
  case 385:
  case 386: {
    func_8003A720(moby); // Reset the Moby first
    VecCopy(&moby->m_Position, &pParent->m_Position);
    moby->m_Rotation = pParent->m_Rotation;
    func_800526A8(moby); // Update collision
    moby->m_Renderer.raw = 0xbf;
    moby->m_SpecularMetalColor[0] = pParent->m_SpecularMetalColor[0];
    moby->m_SpecularMetalColor[1] = pParent->m_SpecularMetalColor[1];
    moby->m_SpecularMetalColor[2] = pParent->m_SpecularMetalColor[2];
    moby->m_SpecularMetalType = pParent->m_SpecularMetalType;
    break;
  }
#endif

#ifdef HAS_MOBY_387
  case 387:
  case 388:
  case 389:
  case 393:
  case 490: {
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
#endif

// Seemingly the start of level specific Mobys
#ifdef HAS_MOBY_398
  case 398: {            // ... Portal path Moby??
    func_8003A720(moby); // Reset the Moby first

    moby->m_RenderRadius = -1;

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
#endif

#ifdef HAS_MOBY_392
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
#endif

#ifdef HAS_MOBY_405
#define HAS_ANY_DROWNING
  case 477: // Drowning bubbles
  case 405: // Drowning splash
#endif
#ifdef HAS_MOBY_507
#define HAS_ANY_DROWNING
  case 507:
  case 508:
#endif
#ifdef HAS_MOBY_400
#define HAS_ANY_DROWNING
  case 400:
#endif
#ifdef HAS_ANY_DROWNING
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
#endif

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

#ifdef HAS_MOBY_502
  case 502: { // Chicken fodder feather
    struct {
      short unk_0x00;
      short unk_0x02;
      short unk_0x04;

      short unk_0x06;
      short unk_0x08;
      short unk_0x0A;

      char unk_0x0C;
      char unk_0x0D;
      short unk_0x0E;
      int unk_0x10;
    } *chickenFeatherProps = moby->m_Props;
    int angle1;
    int angle2;

    func_8003A720(moby); // Reset the Moby first
    VecCopy(&moby->m_Position, &pParent->m_Position);
    func_800526A8(moby); // Update collision

    angle2 = rand() & 0xFFF;
    angle1 = rand() & 0x7FF;

    if (angle1 < 128) {
      angle1 = 128;
    }

    if (angle1 > 1920) {
      angle1 = 1920;
    }

    chickenFeatherProps->unk_0x00 = (Cos(angle1) >> 5) * (Cos(angle2) >> 12);
    chickenFeatherProps->unk_0x02 = (Cos(angle1) >> 5) * (Sin(angle2) >> 12);
    chickenFeatherProps->unk_0x04 = Sin(angle1) >> 5;

    if (chickenFeatherProps->unk_0x04 < 32) {
      chickenFeatherProps->unk_0x04 = 32;
    }

    chickenFeatherProps->unk_0x04 += 32;

    moby->m_Rotation.z = rand();

    if ((rand() & 0xFF) > 128) {
      moby->m_Rotation.y = (rand() & 28) - 16;
      chickenFeatherProps->unk_0x10 = 1;
      if (chickenFeatherProps->unk_0x04 > 32) {
        chickenFeatherProps->unk_0x04 = 32;
      }
    }

    moby->m_Position.x += chickenFeatherProps->unk_0x00 * 4;
    moby->m_Position.y += chickenFeatherProps->unk_0x02 * 4;
    moby->m_Position.z += chickenFeatherProps->unk_0x04 * 4;

    chickenFeatherProps->unk_0x06 = (rand() & 0x1F) - 16;
    chickenFeatherProps->unk_0x08 = (rand() & 0x1F) - 16;
    chickenFeatherProps->unk_0x0A = (rand() & 0x1F) - 16;
    chickenFeatherProps->unk_0x0C = 50 - RandRange(0, 20);
    chickenFeatherProps->unk_0x0D = 10;
    chickenFeatherProps->unk_0x0E = 4;

    break;
  }
#endif

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
