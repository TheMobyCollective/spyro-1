#include "42CC4.h"
#include "camera.h"
#include "collision.h"
#include "dragon.h"
#include "math.h"
#include "moby.h"
#include "moby_helpers.h"
#include "overlay_pointers.h"
#include "rand.h"
#include "spyro.h"
#include "variables.h"
#include "vector.h"

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
    VecCopy(&butterflyProps->m_0x04, &moby->m_Position);

    butterflyProps->m_0x13 = 0;
    butterflyProps->m_0x12 = 0;
    butterflyProps->m_0x14 = 1800;
    break;
  }
#ifdef HAS_MOBY_17
  case 17: {
    Moby17Props *props;
    Vector3D v;
    func_8003A720(moby); // Reset the Moby first
    moby->m_Rotation.z = pParent->m_Rotation.z;
    moby->m_Position.x =
        pParent->m_Position.x + (COSINE_8(moby->m_Rotation.z) >> 4);
    moby->m_Position.y =
        pParent->m_Position.y + (SINE_8(moby->m_Rotation.z) >> 4);
    moby->m_Position.z = pParent->m_Position.z;
    v.x = g_Spyro.m_Position.x - moby->m_Position.x;
    v.y = g_Spyro.m_Position.y - moby->m_Position.y;
    v.z = g_Spyro.m_Position.z - moby->m_Position.z;
    VecScaleToLength(&v, VecMagnitude(&v, 1), 0xa0);
    func_800526A8(moby); // Update collision
    props = moby->m_Props;
    VecCopy(&props->m_0x00, &v);
    props->m_0x0c = 0x50;
    break;
  }
#endif
#ifdef HAS_MOBY_32
  case 32: {
    Moby32Props *props = moby->m_Props;

    func_8003A720(moby);

    props->m_Parent = pParent;

    func_80052D64(pParent, 0, &moby->m_Position);
    func_800526A8(moby);

    // Bug? Camera's Y rotation isn't being scaled down
    moby->m_Rotation.y = g_Camera.m_Rotation.y;
    moby->m_Rotation.z = (g_Camera.m_Rotation.z + ROTDEG12(90)) >> 4;
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
#ifdef HAS_MOBY_37
  case 37: {
    Moby37Props *props = moby->m_Props;
    Vector3D v;

    func_8003A720(moby);

    moby->m_ShadowDistance = -1;
    VecCopy(&v, &moby->m_Position);

    v.z += 1024;
    func_8004D5EC(&v, 0x10000);
    func_800533D0(moby);

    switch (pParent->m_State) {
    case 72:
      props->m_0x10 = 1;
      props->m_0x04 = 0x40;
      props->m_0x06 = 0xE00;
      break;

    case 82:
      props->m_0x10 = 2;
      props->m_0x04 = 0x100;
      props->m_0x06 = 0x2000;
      break;

    case 92:
      props->m_0x10 = 3;
      props->m_0x04 = 0x140;
      props->m_0x06 = 0x2000;
      break;
    }

    moby->m_Position.x = pParent->m_Position.x +
                         FIXED_MUL(COSINE_8(pParent->m_Rotation.z), 1024);
    moby->m_Position.y =
        pParent->m_Position.y + FIXED_MUL(SINE_8(pParent->m_Rotation.z), 1024);
    moby->m_Position.z = pParent->m_Position.z;

    props->m_0x00 = pParent;
    props->m_0x0c = 0;

    moby->m_State = 0;

    moby->m_AnimationState.m_PerFrameProgress =
        g_Models[moby->m_Class]->m_Animations[0]->m_ProgressPerTick;
    moby->m_AnimationState.m_NextAnimation = 0;
    moby->m_AnimationState.m_Animation = 0;
    moby->m_AnimationState.m_NextFrame = 0;
    moby->m_AnimationState.m_Frame = 0;
    func_800526A8(moby);
    break;
  }
#endif
#ifdef HAS_MOBY_38
  case 38: {
    Moby38Props *props = moby->m_Props;
    int angle;

    func_8003A720(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);

    if (pParent->m_Class == 38) {
      moby->m_Rotation.z = pParent->m_Rotation.z;
      moby->m_State = 3;
      moby->m_AnimationState.m_FrameProgress = 0;
      moby->m_AnimationState.m_PerFrameProgress =
          g_Models[moby->m_Class]->m_Animations[3]->m_ProgressPerTick;
      moby->m_AnimationState.m_Animation = 3;
      moby->m_AnimationState.m_NextAnimation = 3;
      props->m_0x00 = 3;
    } else if (pParent->m_AnimationState.m_NextFrame >= 6) {
      moby->m_Position.x += Cos(pParent->m_Rotation.z << 4) >> 2;
      moby->m_Position.y += Sin(pParent->m_Rotation.z << 4) >> 2;
      moby->m_Position.z += 300;
      moby->m_Rotation.z = pParent->m_Rotation.z;

      angle = (Atan2(DISTANCE_TO_SPYRO(moby),
                     g_Spyro.m_Position.z - moby->m_Position.z, 0) -
               pParent->m_Rotation.y) &
              0xFF;

      if (angle > 0x80) {
        angle -= 0x100;
      }

      if (angle < -0x10) {
        angle = -0x10;
      }

      if (angle > 0x10) {
        angle = 0x10;
      }

      moby->m_Rotation.y = pParent->m_Rotation.y + angle;

      props->m_0x00 = 0x80;
      moby->m_State = 2;
      moby->m_AnimationState.m_FrameProgress = 0;
      moby->m_AnimationState.m_PerFrameProgress =
          g_Models[moby->m_Class]->m_Animations[2]->m_ProgressPerTick;
      moby->m_AnimationState.m_Animation = 2;
      moby->m_AnimationState.m_NextAnimation = 2;

      g_SpawnParticle(4, 7, &moby->m_Position, 0x10);
    } else {
      if (pParent->m_AnimationState.m_NextFrame >= 2) {
        moby->m_Position.z += 300;
        moby->m_Rotation.z = pParent->m_Rotation.z;
        moby->m_State = 1;
        moby->m_AnimationState.m_FrameProgress = 0;
        moby->m_AnimationState.m_PerFrameProgress =
            g_Models[moby->m_Class]->m_Animations[1]->m_ProgressPerTick;
        moby->m_AnimationState.m_Animation = 1;
        moby->m_AnimationState.m_NextAnimation = 1;
        props->m_0x00 = 2;
      } else {
        moby->m_Position.z += 384;
        moby->m_Rotation.z = pParent->m_Rotation.z;
        props->m_0x00 = 2;
      }
    }

    func_800526A8(moby);
    break;
  }
#endif
#ifdef HAS_MOBY_39
  case 39: {
    Moby39Props *props = moby->m_Props;

    func_8003A720(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);
    func_800526A8(moby);

    moby->m_Rotation.z = Atan2(g_Camera.m_Position.x - moby->m_Position.x,
                               g_Camera.m_Position.y - moby->m_Position.y, 0);
    moby->m_Position.z -= 1024;

    props->m_0x00 = 0x40;
    props->m_0x04 = pParent;
    props->m_0x08 = 1;

    break;
  }
#endif
#ifdef HAS_MOBY_55
  case 55: { // Cupid Arrow
    int angle;
    Moby55Props *props = moby->m_Props;

    func_8003A720(moby);
    func_80052D64(pParent, 0, &moby->m_Position);

    moby->m_Rotation.x = 0;
    angle = Atan2(DISTANCE_TO_SPYRO(moby),
                  g_Spyro.m_Position.z - moby->m_Position.z, 0);

    if (angle > 128) {
      angle -= 256;
    }
    if (angle < -16) {
      angle = -16;
    }
    if (angle > 16) {
      angle = 16;
    }

    moby->m_Rotation.y = angle;
    moby->m_Rotation.z = ANGLE_TO_SPYRO(moby->m_Position);

    func_800526A8(moby);
    props->m_Lifetime = 140;

    break;
  }
#endif
#ifdef HAS_MOBY_56
  case 56: {
    Moby56Props *props = moby->m_Props;
    int angle;

    func_8003A720(moby);
    func_80052D64(pParent, 0, &moby->m_Position);

    moby->m_Rotation.x = 0;
    angle = Atan2(DISTANCE_TO_SPYRO(moby),
                  g_Spyro.m_Position.z - moby->m_Position.z, 0);

    if (angle > 128) {
      angle -= 256;
    }

    if (angle < -16) {
      angle = -16;
    }

    if (angle > 16) {
      angle = 16;
    }

    moby->m_Rotation.y = angle;
    moby->m_Rotation.z = ANGLE_TO_SPYRO(moby->m_Position);

    func_800526A8(moby);
    props->m_Lifetime = 240;

    break;
  }
#endif
#ifdef HAS_MOBY_78
  case 78: {             // Flight Train Barrel
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
    Vector3D v;            // Name from S2
    MobyCollectableProps *gemProps = moby->m_Props;

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
    if (pParent->m_Class == MOBYCLASS_GEM_SPAWNER) {
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
#ifdef HAS_MOBY_93
  case 93: {
    MobyFragmentProps *props = moby->m_Props;
    Moby35Props *parentProps;
    int angle1;
    int angle2;
    int absCos;

    func_8003A720(moby);

    moby->m_RenderRadius = 32;
    VecCopy(&moby->m_Position, &pParent->m_Position);
    func_800526A8(moby);

    if (pParent->m_Class == 35) {
      parentProps = pParent->m_Props;

      angle2 = ((parentProps->m_0x0c + RandRange(-50, 50)) & 0xFF) << 4;
      angle1 = rand() & 0x7FF;

      absCos = ABS2(Cos(angle1) >> 4);

      props->m_Velocity.x = FIXED_MUL(absCos, Cos(angle2));
      props->m_Velocity.y = FIXED_MUL(absCos, Sin(angle2));
      props->m_Velocity.z = Sin(angle1) >> 4;

      props->m_Lifetime = RandRange(35, 50);
      moby->m_ScaleOverride = 32 - RandRange(6, 20);

      props->m_Velocity.x += g_Spyro.m_Physics.m_Acceleration.x >> 6;
      props->m_Velocity.y += g_Spyro.m_Physics.m_Acceleration.y >> 6;
      props->m_Velocity.z += g_Spyro.m_Physics.m_Acceleration.z >> 6;
    } else {
      angle2 = rand() & 0xFFF;
      angle1 = rand() & 0x7FF;

      props->m_Velocity.x = FIXED_MUL(Cos(angle1) >> 5, Cos(angle2));
      props->m_Velocity.y = FIXED_MUL(Cos(angle1) >> 5, Sin(angle2));
      props->m_Velocity.z = Sin(angle1) >> 5;

      if (pParent->m_DamageFlags & MOBY_DAMAGE_CHARGE) {
        props->m_Velocity.x += g_Spyro.m_Physics.m_Acceleration.x >> 6;
        props->m_Velocity.y += g_Spyro.m_Physics.m_Acceleration.y >> 6;
        props->m_Velocity.z += g_Spyro.m_Physics.m_Acceleration.z >> 6;
      }

      props->m_Lifetime = 64 - (rand() & 0xF);
    }

    moby->m_Position.x += props->m_Velocity.x << 2;
    moby->m_Position.y += props->m_Velocity.y << 2;
    moby->m_Position.z += props->m_Velocity.z << 2;

    props->m_AngularVelocity.x = rand() & 0xF;
    props->m_AngularVelocity.y = rand() & 0xF;
    props->m_AngularVelocity.z = rand() & 0xF;

    moby->m_Rotation.x += props->m_AngularVelocity.x << 2;
    moby->m_Rotation.y += props->m_AngularVelocity.y << 2;
    moby->m_Rotation.z += props->m_AngularVelocity.z << 2;

    props->m_MinZ = pParent->m_Position.z - 64;

    ((int *)&moby->m_SpecularMetalColor)[0] = 0x1000000;
    moby->m_Renderer.raw |= 0x80;

    break;
  }
#endif
#ifdef HAS_MOBY_215
  case 215: {
    MobyFragmentProps *props;
    int randRes;
    int angle;

    randRes = RandRange(120, 150);

    props = moby->m_Props;
    func_8003A720(moby);

    moby->m_RenderRadius = 32;
    VecCopy(&moby->m_Position, &pParent->m_Position);
    func_800526A8(moby);

    angle = (pParent->m_Rotation.y + RandRange(-15, 15)) & 0xFF;

    props->m_Velocity.x = FIXED_MUL(randRes, COSINE_8(angle));
    props->m_Velocity.y = FIXED_MUL(randRes, SINE_8(angle));
    props->m_Velocity.z = RandRange(100, 140);
    props->m_Lifetime = RandRange(30, 50);

    props->m_AngularVelocity.x = RandRangeSigned(7, 12);
    props->m_AngularVelocity.y = RandRangeSigned(7, 12);
    props->m_AngularVelocity.z = RandRangeSigned(7, 12);

    props->m_MinZ = MOBY_BASE_Z(pParent) - 64;

    ((int *)&moby->m_SpecularMetalColor)[0] = 0x1000000;
    moby->m_Renderer.raw |= 0x80;

    break;
  }
#endif
  case 120: { // Sparx
    MobySparxProps *sparxProps = moby->m_Props;

    func_8003A720(moby); // Reset the Moby first
    func_800526A8(moby); // Update collision

    moby->m_Substate = 0;

    sparxProps->m_Timer = 0;
    sparxProps->m_SpyroOffset.z = 0;
    sparxProps->m_SpyroOffset.y = 0;
    sparxProps->m_SpyroOffset.x = 0;
    sparxProps->m_Glow = 0;
    sparxProps->m_Target = 0;

    if (pParent) {
      VecCopy(&moby->m_Position, &pParent->m_Position);
    }

    break;
  }
#ifdef HAS_MOBY_124
  case 124: {
    Moby124Props *props = moby->m_Props;

    func_8003A720(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);

    moby->m_Rotation = pParent->m_Rotation;

    props->m_0x00 = pParent;

    func_800526A8(moby);
    break;
  }
#endif
#ifdef HAS_MOBY_232
  case 232: {
    Moby232Props *props = moby->m_Props;

    func_8003A720(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);
    moby->m_Position.z += 1024;
    func_800526A8(moby);

    props->m_0x04 = 200;
    props->m_0x08 = 350;
    props->m_0x00 = func_80038178(ANGLE_FROM_SPYRO(moby->m_Position),
                                  g_Spyro.m_bodyRotation.z, 40, 64);
    props->m_0x0c = 120;

    break;
  }
#endif
#if defined(HAS_MOBY_152) || defined(HAS_MOBY_153)
#ifdef HAS_MOBY_152
  case 152:
#endif
#ifdef HAS_MOBY_153
  case 153:
#endif
  {
    func_8003A720(moby);
    moby->m_RenderRadius = 32;
    moby->m_UpdateDistance = 255;
    func_800529CC(moby);
    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;
    moby->m_SpecularMetalType = 13;
    break;
  }
#endif
#ifdef HAS_MOBY_155
  case 155: {
    Moby155Props *props = moby->m_Props;
    int angle;

    func_8003A720(moby);
    func_80052D64(pParent, 0, &moby->m_Position);

    moby->m_Rotation.x = 0;
    angle = Atan2(DISTANCE_TO_SPYRO(moby),
                  g_Spyro.m_Position.z - moby->m_Position.z, 0);

    if (angle > 128) {
      angle -= 256;
    }
    if (angle < -16) {
      angle = -16;
    }
    if (angle > 16) {
      angle = 16;
    }

    moby->m_Rotation.y = angle;

    moby->m_Rotation.z = ANGLE_TO_SPYRO(moby->m_Position);
    angle = (moby->m_Rotation.z - pParent->m_Rotation.z) & 0xFF;

    if (angle > 128) {
      angle -= 256;
    }

    if (ABS(angle) > 16) {
      moby->m_Rotation.z = pParent->m_Rotation.z;
    }

    func_800526A8(moby);
    props->m_0x00 = 240;
    break;
  }
#endif
#ifdef HAS_MOBY_202
  case 202: {
    Moby202Props *props = moby->m_Props;
    Vector3D v;

    func_8003A720(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);

    props->m_0x0c = -12;
    props->m_0x04 = pParent;
    props->m_0x02 = 0;
    props->m_0x10 = -1;

    moby->m_FloorDistance = 461;
    func_800526A8(moby);

    moby->m_Renderer.raw = 0x10;
    moby->m_RenderRadius = 32;
    moby->m_ShadowDistance = -1;

    VecCopy(&v, &moby->m_Position);
    v.z += 1024;
    func_8004D5EC(&v, 0x10000);
    func_800533D0(moby);

    break;
  }
#endif

#ifdef HAS_MOBY_207
  case 207: {
    Moby207Props *props = moby->m_Props;
    Vector3D v;

    func_8003A720(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);

    props->m_0x0c = -12;
    props->m_0x04 = pParent;
    props->m_0x02 = 0;
    props->m_0x14 = 0;
    props->m_0x10 = -1;

    moby->m_FloorDistance = 461;
    func_800526A8(moby);

    moby->m_Renderer.raw = 0x90;
    moby->m_RenderRadius = 32;
    ((int *)&moby->m_SpecularMetalColor)[0] = 0xA18618;
    moby->m_ShadowDistance = -1;

    VecCopy(&v, &moby->m_Position);
    v.z += 1024;
    func_8004D5EC(&v, 0x10000);
    func_800533D0(moby);

    break;
  }
#endif
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

#if defined(HAS_MOBY_67) || defined(HAS_MOBY_68) || defined(HAS_MOBY_69) ||    \
    defined(HAS_MOBY_133) || defined(HAS_MOBY_151) || defined(HAS_MOBY_255) || \
    defined(HAS_MOBY_256) || defined(HAS_MOBY_257) || defined(HAS_MOBY_309) || \
    defined(HAS_MOBY_310) || defined(HAS_MOBY_311) || defined(HAS_MOBY_423) || \
    defined(HAS_MOBY_424) || defined(HAS_MOBY_425) || defined(HAS_MOBY_478) || \
    defined(HAS_MOBY_479) || defined(HAS_MOBY_480)
#ifdef HAS_MOBY_133
  case 133:
#endif
#ifdef HAS_MOBY_151
  case 151:
#endif
#ifdef HAS_MOBY_255
  case 255: // Wooden chest fragments
#endif
#ifdef HAS_MOBY_256
  case 256:
#endif
#ifdef HAS_MOBY_257
  case 257:
#endif
#ifdef HAS_MOBY_67
  case 67: // Spring chest fragments
#endif
#ifdef HAS_MOBY_68
  case 68:
#endif
#ifdef HAS_MOBY_69
  case 69:
#endif
#ifdef HAS_MOBY_309
  case 309: // Metal, locked and armored chest fragments
#endif
#ifdef HAS_MOBY_310
  case 310:
#endif
#ifdef HAS_MOBY_311
  case 311:
#endif
#ifdef HAS_MOBY_423
  case 423: // Extra life chest piece 1
#endif
#ifdef HAS_MOBY_424
  case 424: // Extra life chest piece 2
#endif
#ifdef HAS_MOBY_425
  case 425: // Extra life chest piece 3
#endif
#ifdef HAS_MOBY_478
  case 478: // Flight chest fragments
#endif
#ifdef HAS_MOBY_479
  case 479:
#endif
#ifdef HAS_MOBY_480
  case 480:
#endif
  {
    MobyFragmentProps *props = moby->m_Props;

    int angle1;
    int angle2;

    func_8003A720(moby); // Reset the Moby first

    moby->m_RenderRadius = 32;
    VecCopy(&moby->m_Position, &pParent->m_Position);

    func_800526A8(moby); // Update collision

    angle2 = rand() & 0xFFF;
    angle1 = rand() & 0x7FF;

    props->m_Velocity.x = FIXED_MUL(Cos(angle1) >> 5, Cos(angle2));
    props->m_Velocity.y = FIXED_MUL(Cos(angle1) >> 5, Sin(angle2));
    props->m_Velocity.z = Sin(angle1) >> 5;

    // Charge damage
    if (pParent->m_DamageFlags & MOBY_DAMAGE_CHARGE) {
      props->m_Velocity.x += g_Spyro.m_Physics.m_Acceleration.x >> 6;
      props->m_Velocity.y += g_Spyro.m_Physics.m_Acceleration.y >> 6;
      props->m_Velocity.z += g_Spyro.m_Physics.m_Acceleration.z >> 6;
    }

    moby->m_Position.x += props->m_Velocity.x * 4;
    moby->m_Position.y += props->m_Velocity.y * 4;
    moby->m_Position.z += props->m_Velocity.z * 4;

    props->m_AngularVelocity.x = rand() & 0xF;
    props->m_AngularVelocity.y = rand() & 0xF;
    props->m_AngularVelocity.z = rand() & 0xF;

    props->m_MinZ = pParent->m_Position.z - 64;
    props->m_Lifetime = 64 - (rand() & 0xF);

    if (moby->m_Class >= 309 && moby->m_Class <= 311) {
      // Possible union
      ((int *)&moby->m_SpecularMetalColor)[0] = 0xa18618;
      moby->m_Renderer.raw |= 0x80; // Set shiny renderer
    }
    break;
  }
#endif
#ifdef HAS_MOBY_251
  case 251: {   // Dragon fragment
    Vector3D v; // Name from S2
    int randRes;

    MobyDragonFragmentProps *dragonFragmentProps = moby->m_Props;

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

    VecCopy(&dragonFragmentProps->m_Velocity, &v);

    VecShiftRight(&dragonFragmentProps->m_Velocity, 2);

    dragonFragmentProps->m_Velocity.x += -127 + (rand() & 255);
    dragonFragmentProps->m_Velocity.y += -127 + (rand() & 255);
    dragonFragmentProps->m_Velocity.z += -127 + (rand() & 255);

    moby->m_Rotation.x = rand();
    moby->m_Rotation.y = rand();
    moby->m_Rotation.z = rand();

    dragonFragmentProps->m_AngularVelocity.x = rand() & 0xf;
    dragonFragmentProps->m_AngularVelocity.y = rand() & 0xf;
    dragonFragmentProps->m_AngularVelocity.z = rand() & 0xf;
    dragonFragmentProps->m_MinZ = pParent->m_Position.z;
    dragonFragmentProps->m_Lifetime = (rand() & 3) + 16;
    break;
  }
#endif

#if defined(HAS_MOBY_481) || defined(HAS_MOBY_482) || defined(HAS_MOBY_483)
#ifdef HAS_MOBY_481
  case 481: // Flight Train, Wagon and Plane Fragments
#endif
#ifdef HAS_MOBY_482
  case 482:
#endif
#ifdef HAS_MOBY_483
  case 483:
#endif
  {
    MobyFragmentProps *props = moby->m_Props;
    int angle1, angle2;

    func_8003A720(moby);
    moby->m_RenderRadius = 32;
    VecCopy(&moby->m_Position, &pParent->m_Position);
    func_800526A8(moby);

    angle1 = rand() & 0xFFF;
    angle2 = rand() & 0x7FF;

    props->m_Velocity.x = FIXED_MUL(Cos(angle2) >> 5, Cos(angle1));
    props->m_Velocity.y = FIXED_MUL(Cos(angle2) >> 5, Sin(angle1));
    props->m_Velocity.z = Sin(angle2) >> 5;

    props->m_Velocity.x += g_Spyro.m_Physics.m_Acceleration.x >> 6;
    props->m_Velocity.y += g_Spyro.m_Physics.m_Acceleration.y >> 6;
    props->m_Velocity.z += g_Spyro.m_Physics.m_Acceleration.z >> 6;

    moby->m_Position.x += props->m_Velocity.x * 4;
    moby->m_Position.y += props->m_Velocity.y * 4;
    moby->m_Position.z += props->m_Velocity.z * 4;

    props->m_AngularVelocity.x = rand() & 0xF;
    props->m_AngularVelocity.y = rand() & 0xF;
    props->m_AngularVelocity.z = rand() & 0xF;
    props->m_MinZ = pParent->m_Position.z - 64;
    props->m_Lifetime = 64 - (rand() & 0xF);
    break;
  }
#endif

#if defined(HAS_MOBY_359) || defined(HAS_MOBY_360) || defined(HAS_MOBY_361)
#ifdef HAS_MOBY_359
  case 359: // Flight Train Barrel Fragments
#endif
#ifdef HAS_MOBY_360
  case 360:
#endif
#ifdef HAS_MOBY_361
  case 361:
#endif
  {
    MobyFragmentProps *props = moby->m_Props;

    func_8003A720(moby); // Reset the Moby first

    moby->m_RenderRadius = 32;

    VecCopy(&moby->m_Position, &pParent->m_Position);
    func_800526A8(moby); // Update collision

    moby->m_Rotation.z = rand();

    props->m_Velocity.x = COSINE_8(moby->m_Rotation.z) >> 7;
    props->m_Velocity.y = SINE_8(moby->m_Rotation.z) >> 7;

    if ((rand() & 1)) {
      props->m_Velocity.z = 90;
    } else {
      props->m_Velocity.z = -90;
      moby->m_Rotation.x = 128;
    }

    moby->m_Position.x += props->m_Velocity.x * 4;
    moby->m_Position.y += props->m_Velocity.y * 4;
    moby->m_Position.z += props->m_Velocity.z * 4;

    if (props->m_Velocity.z < 20) {
      props->m_Velocity.z = 20;
    }

    props->m_AngularVelocity.x = rand() & 0xF;
    props->m_AngularVelocity.y = rand() & 0xF;
    props->m_AngularVelocity.z = rand() & 0xF;

    props->m_MinZ = pParent->m_Position.z - 64;

    props->m_Lifetime = 64 - (rand() & 0xF);
    break;
  }
#endif
#ifdef HAS_MOBY_362
  case 362: { // Flight Train wheels
    MobyFragmentProps *props = moby->m_Props;
    Moby407Props *parentProps = pParent->m_Props;
    Vector3D v;
    func_8003A720(moby); // Reset
    moby->m_RenderRadius = 32;
    func_800526A8(moby); // Collision update

    // A bug? Vector3D is being copied into the Vector3D16 Velocity
    VecCopy((Vector3D *)&props->m_Velocity, &parentProps->m_0x08);
    props->m_AngularVelocity.y = 0;
    props->m_AngularVelocity.z = 0;
    props->m_Velocity.z += 64;
    props->m_MinZ = pParent->m_Position.z - 64;
    props->m_Lifetime = 64 - (rand() & 0xF);

    switch (rand() & 3) {
    case 0:
      v.x = 512;
      v.y = 512;
      moby->m_Rotation.z = 64;
      props->m_AngularVelocity.x = 16;
      break;

    case 1:
      v.x = 512;
      v.y = -512;
      moby->m_Rotation.z = 192;
      props->m_AngularVelocity.x = -16;
      break;

    case 2:
      v.x = -512;
      v.y = 512;
      moby->m_Rotation.z = 64;
      props->m_AngularVelocity.x = 16;
      break;

    case 3:
      v.x = -512;
      v.y = -512;
      moby->m_Rotation.z = 192;
      props->m_AngularVelocity.x = -16;
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
#ifdef HAS_MOBY_277
  case 277: // Text Slash
#endif
#ifdef HAS_MOBY_327
  case 327: // Hud .
#endif
  {
    MobyNumberProps *textProps = moby->m_Props;

    func_8003A720(moby); // Reset the Moby first
    func_800529CC(moby); // Set shaded moby

    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;
    moby->m_SpecularMetalType = 2;

    textProps->m_Lifetime = 64;
    break;
  }

#if defined(HAS_MOBY_288) || defined(HAS_MOBY_289)
#ifdef HAS_MOBY_288
  case 288:
#endif
#ifdef HAS_MOBY_289
  case 289:
#endif
  {
    Moby288Props *props = moby->m_Props;
    int angle1;
    int angle2;

    func_8003A720(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);
    func_800526A8(moby);

    angle2 = rand() & 0xFFF;
    angle1 = rand() & 0x7FF;

    if (angle1 < 0x80) {
      angle1 = 0x80;
    }

    if (angle1 > 0x780) {
      angle1 = 0x780;
    }

    props->m_0x00 = (Cos(angle1) >> 5) * (Cos(angle2) >> 12);
    props->m_0x02 = (Cos(angle1) >> 5) * (Sin(angle2) >> 12);
    props->m_0x04 = Sin(angle1) >> 5;

    if (props->m_0x04 < 0x20) {
      props->m_0x04 = 0x20;
    }

    if (moby->m_Class == 289) {
      props->m_0x04 += 0x20;
      moby->m_Rotation.z = rand();

      if ((rand() & 0xFFF) >= 0x800) {
        moby->m_Rotation.y = (rand() & 0x1C) - 0x10;
        props->m_0x10 = 1;
      }
    } else {
      if (props->m_0x00 < -0x60) {
        props->m_0x00 = -0x60;
      }

      if (props->m_0x00 > 0x60) {
        props->m_0x00 = 0x60;
      }

      if (props->m_0x02 < -0x60) {
        props->m_0x02 = -0x60;
      }

      if (props->m_0x02 > 0x60) {
        props->m_0x02 = 0x60;
      }
    }

    moby->m_Position.x += props->m_0x00 * 4;
    moby->m_Position.y += props->m_0x02 * 4;
    moby->m_Position.z += props->m_0x04 * 4;

    props->m_0x06 = (rand() & 0x1F) - 0x10;
    props->m_0x08 = (rand() & 0x1F) - 0x10;
    props->m_0x0a = (rand() & 0x1F) - 0x10;
    props->m_0x0c = 50 - RandRange(0, 20);
    props->m_0x0d = 10;
    props->m_0x0e = 4;

    break;
  }
#endif

#ifdef HAS_MOBY_295
  case 295: {
    Moby295Props *props = moby->m_Props;
    int angle;

    func_8003A720(moby);

    moby->m_Position.x =
        pParent->m_Position.x + (COSINE_8(pParent->m_Rotation.z) >> 1);
    moby->m_Position.y =
        pParent->m_Position.y + (SINE_8(pParent->m_Rotation.z) >> 1);
    moby->m_Position.z = pParent->m_Position.z + 768;

    angle = (ANGLE_TO_SPYRO(moby->m_Position) - pParent->m_Rotation.z) & 0xFF;

    if (angle > 0x80) {
      angle -= 0x100;
    }

    if (angle < -0x20) {
      angle = -0x20;
    }

    if (angle > 0x20) {
      angle = 0x20;
    }

    moby->m_Rotation.z = pParent->m_Rotation.z + angle;

    angle = DISTANCE_TO_SPYRO(moby);
    angle = Atan2(angle,
                  0x164 + g_Spyro.m_surfaceBelowSpyro - moby->m_Position.z, 0);
    angle = (angle - pParent->m_Rotation.y) & 0xFF;

    if (angle > 0x80) {
      angle -= 0x100;
    }

    if (angle < -0x30) {
      angle = -0x30;
    }

    if (angle > 0x30) {
      angle = 0x30;
    }

    moby->m_Rotation.y = pParent->m_Rotation.y + angle;

    props->m_0x04 = 90;
    props->m_0x00 = 0;

    func_800526A8(moby);
    break;
  }
#endif

#ifdef HAS_MOBY_304
  case 304: {
    Vector3D v;
    Moby304Props *props = moby->m_Props;
    Moby303Props *parentProps = pParent->m_Props;

    func_8003A720(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);

    props->m_0x04 = pParent;
    props->m_0x00 = parentProps->m_0x00;
    VecNull(&props->m_0x08);

    moby->m_RenderRadius = 32;
    func_800526A8(moby);

    moby->m_ShadowDistance = -1;
    VecCopy(&v, &moby->m_Position);

    v.z += 1024;
    func_8004D5EC(&v, 0x10000);
    func_800533D0(moby);

    break;
  }
#endif
#ifdef HAS_MOBY_318
  case 318: {
    Moby318Props *props = moby->m_Props;

    func_8003A720(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);

    props->m_0x00.x = (rand() & 0x7E) - 63;
    props->m_0x00.y = (rand() & 0x7E) - 63;
    props->m_0x00.z = (rand() & 0x7E) - 16;
    props->m_0x0c = (rand() & 0x1F) + 32;

    func_800526A8(moby);
    break;
  }
#endif

#if defined(HAS_MOBY_345) || defined(HAS_MOBY_346) || defined(HAS_MOBY_347)
#ifdef HAS_MOBY_345
  case 345: // Flight +1S moby?
#endif
#ifdef HAS_MOBY_346
  case 346: // Flight +2S moby?
#endif
#ifdef HAS_MOBY_347
  case 347: // Flight +3S moby?
#endif
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
#ifdef HAS_MOBY_343
  case 343: {
    Moby343Props *props = moby->m_Props;

    func_8003A720(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);

    props->m_0x00 = pParent;
    props->m_0x04 = 0;
    props->m_0x08 = 0;

    moby->m_RenderRadius = 0;

    func_800526A8(moby);

    moby->m_WasDrawn = 0;
    break;
  }
#endif
#ifdef HAS_MOBY_374
  case 374: {            // Flight Gate Fragment
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

#if defined(HAS_MOBY_375) || defined(HAS_MOBY_376) || defined(HAS_MOBY_377) || \
    defined(HAS_MOBY_378) || defined(HAS_MOBY_379) || defined(HAS_MOBY_380) || \
    defined(HAS_MOBY_381) || defined(HAS_MOBY_382) || defined(HAS_MOBY_383) || \
    defined(HAS_MOBY_384) || defined(HAS_MOBY_385) || defined(HAS_MOBY_386)
#ifdef HAS_MOBY_375
  case 375: // Flight Gate Remaining Fragments
#endif
#ifdef HAS_MOBY_376
  case 376:
#endif
#ifdef HAS_MOBY_377
  case 377:
#endif
#ifdef HAS_MOBY_378
  case 378:
#endif
#ifdef HAS_MOBY_379
  case 379:
#endif
#ifdef HAS_MOBY_380
  case 380:
#endif
#ifdef HAS_MOBY_381
  case 381:
#endif
#ifdef HAS_MOBY_382
  case 382:
#endif
#ifdef HAS_MOBY_383
  case 383:
#endif
#ifdef HAS_MOBY_384
  case 384:
#endif
#ifdef HAS_MOBY_385
  case 385:
#endif
#ifdef HAS_MOBY_386
  case 386:
#endif
  {
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

#if defined(HAS_MOBY_387) || defined(HAS_MOBY_388) || defined(HAS_MOBY_389) || \
    defined(HAS_MOBY_393) || defined(HAS_MOBY_394) || defined(HAS_MOBY_396) || \
    defined(HAS_MOBY_490) || defined(HAS_MOBY_491)
#ifdef HAS_MOBY_387
  case 387:
#endif
#ifdef HAS_MOBY_388
  case 388:
#endif
#ifdef HAS_MOBY_389
  case 389:
#endif
#ifdef HAS_MOBY_393
  case 393:
#endif
#ifdef HAS_MOBY_394
  case 394:
#endif
#ifdef HAS_MOBY_396
  case 396:
#endif
#ifdef HAS_MOBY_490
  case 490:
#endif
#ifdef HAS_MOBY_491
  case 491:
#endif
  {
    func_8003A720(moby);
    moby->m_RenderRadius = 0;
    moby->m_Position.x = -100;
    moby->m_Position.y = 30;
    moby->m_Position.z = 4096;

    func_800529CC(moby);
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

#if defined(HAS_MOBY_398) || defined(HAS_MOBY_399)
#ifdef HAS_MOBY_398
  case 398:
#endif
#ifdef HAS_MOBY_399
  case 399:
#endif
  {
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
#if defined(HAS_MOBY_363) || defined(HAS_MOBY_364) || defined(HAS_MOBY_400) || \
    defined(HAS_MOBY_405) || defined(HAS_MOBY_477) || defined(HAS_MOBY_507) || \
    defined(HAS_MOBY_508)
#ifdef HAS_MOBY_363
  case 363:
#endif
#ifdef HAS_MOBY_364
  case 364:
#endif
#ifdef HAS_MOBY_405
  case 405: // Drowning splash
#endif
#ifdef HAS_MOBY_477
  case 477: // Drowning bubbles
#endif
#ifdef HAS_MOBY_507
  case 507:
#endif
#ifdef HAS_MOBY_508
  case 508:
#endif
#ifdef HAS_MOBY_400
  case 400:
#endif
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

#if defined(HAS_MOBY_454) || defined(HAS_MOBY_455) || defined(HAS_MOBY_456)
#ifdef HAS_MOBY_454
  case 454:
#endif
#ifdef HAS_MOBY_455
  case 455:
#endif
#ifdef HAS_MOBY_456
  case 456:
#endif
  {
    MobyFragmentProps *props;
    int randRes;

    randRes = RandRange(-2400, 1400);

    props = moby->m_Props;
    func_8003A720(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);
    func_800526A8(moby);

    // Unused rand result
    rand();

    props->m_Velocity.x = RandRange(-120, 120);
    props->m_Velocity.y = RandRange(-120, 120);
    props->m_Velocity.z = RandRange(50, 240);

    moby->m_Position.x += props->m_Velocity.x * 4;
    moby->m_Position.y += props->m_Velocity.y * 4;
    moby->m_Position.z += props->m_Velocity.z * 4;
    moby->m_Position.z += randRes;

    moby->m_Position.x += (props->m_Velocity.x * (-randRes + 1600)) >> 10;
    moby->m_Position.y += (props->m_Velocity.y * (-randRes + 1600)) >> 10;

    props->m_AngularVelocity.x = rand() & 0xF;
    props->m_AngularVelocity.y = rand() & 0xF;
    props->m_AngularVelocity.z = rand() & 0xF;
    props->m_Lifetime = 160;

    break;
  }
#endif

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
#if defined(HAS_MOBY_458) || defined(HAS_MOBY_459)
#ifdef HAS_MOBY_458
  case 458:
#endif
#ifdef HAS_MOBY_459
  case 459:
#endif
  {
    MobyFragmentProps *props = moby->m_Props;

    func_8003A720(moby);
    moby->m_RenderRadius = 32;
    VecCopy(&moby->m_Position, &pParent->m_Position);
    func_800526A8(moby);

    if (pParent->m_Class == 176) {
      props->m_Velocity.x = RandRange(-100, 100);
      props->m_Velocity.y = RandRange(-100, 100);
      props->m_Velocity.z = RandRange(-60, 110);
    } else {
      props->m_Velocity.x = RandRange(-150, 150);
      props->m_Velocity.y = RandRange(-150, 150);
      props->m_Velocity.z = RandRange(-70, 150);
    }

    moby->m_Position.x += props->m_Velocity.x * 4;
    moby->m_Position.y += props->m_Velocity.y * 4;
    moby->m_Position.z += props->m_Velocity.z * 4;

    props->m_AngularVelocity.x = rand() & 0xF;
    props->m_AngularVelocity.y = rand() & 0xF;
    props->m_AngularVelocity.z = rand() & 0xF;
    props->m_Lifetime = RandRange(24, 35);

    break;
  }
#endif
#ifdef HAS_MOBY_502
  case 502: { // Chicken fodder feather
    Moby502Props *props = moby->m_Props;
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

    props->m_Velocity.x = (Cos(angle1) >> 5) * (Cos(angle2) >> 12);
    props->m_Velocity.y = (Cos(angle1) >> 5) * (Sin(angle2) >> 12);
    props->m_Velocity.z = Sin(angle1) >> 5;

    if (props->m_Velocity.z < 32) {
      props->m_Velocity.z = 32;
    }

    props->m_Velocity.z += 32;

    moby->m_Rotation.z = rand();

    if ((rand() & 0xFF) > 128) {
      moby->m_Rotation.y = (rand() & 28) - 16;
      props->m_0x10 = 1;
      if (props->m_Velocity.z > 32) {
        props->m_Velocity.z = 32;
      }
    }

    moby->m_Position.x += props->m_Velocity.x * 4;
    moby->m_Position.y += props->m_Velocity.y * 4;
    moby->m_Position.z += props->m_Velocity.z * 4;

    props->m_AngularVelocity.x = (rand() & 0x1F) - 16;
    props->m_AngularVelocity.y = (rand() & 0x1F) - 16;
    props->m_AngularVelocity.z = (rand() & 0x1F) - 16;
    props->m_Lifetime = 50 - RandRange(0, 20);
    props->m_0x0d = 10;
    props->m_0x0e = 4;

    break;
  }
#endif

  default: {
    // TODO: This pad is necessary in all levels that have a dragon
    // Putting it in case 251 will work for all levels, except High Caves
    // This is the only hack in this file
#ifdef HAS_MOBY_250
    int pad[2];
#endif
    func_8003A720(moby); // Reset the Moby first

    if (pParent) {
      VecCopy(&moby->m_Position, &pParent->m_Position);
    } else {
      VecCopy(&moby->m_Position, &g_Spyro.m_Position);
    }

    func_800526A8(moby); // Update collision
    break;
  }
  }

  return moby;
}
