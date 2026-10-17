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

Moby *NAME_OVERLAY_FUNCTION(SpawnMoby)(int pClass, Moby *pParent) {
  u_long idx;

  // Allocate a new moby
  Moby *moby = MobyAlloc();

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

  // Extra life orb
  case 15: {
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

    MobyUpdateCollision(moby); // Update collision

    moby->m_Renderer.raw |= 0x80; // Set shiny renderer
    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;
    moby->m_SpecularMetalType = 1; // Set metal type
    break;
  }

  // Butterfly
  case 16: {
    MobyButterflyProps *butterflyProps = (MobyButterflyProps *)moby->m_Props;

    func_8003A720(moby);       // Reset the Moby first
    MobyUpdateCollision(moby); // Update collision
    VecCopy(&moby->m_Position, &pParent->m_Position);

    moby->m_Position.z += 512;
    VecCopy(&butterflyProps->m_0x04, &moby->m_Position);

    butterflyProps->m_0x13 = 0;
    butterflyProps->m_0x12 = 0;
    butterflyProps->m_0x14 = 1800;
    break;
  }

  // Unused flight projectile
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
    MobyUpdateCollision(moby); // Update collision
    props = moby->m_Props;
    VecCopy(&props->m_0x00, &v);
    props->m_0x0c = 0x50;
    break;
  }

  // Laser effect
  case 32: {
    Moby32Props *props = moby->m_Props;

    func_8003A720(moby);

    props->m_Parent = pParent;

    MobyGetAnimatedVertex(pParent, 0, &moby->m_Position);
    MobyUpdateCollision(moby);

    // Bug? Camera's Y rotation isn't being scaled down
    moby->m_Rotation.y = g_Camera.m_Rotation.y;
    moby->m_Rotation.z = (g_Camera.m_Rotation.z + ROTDEG12(90)) >> 4;
    break;
  }

  // Dragon Egg
  case 34: {
    func_8003A720(moby); // Reset the Moby first

    moby->m_RenderRadius = 32;
    moby->m_UpdateDistance = 255;

    if (pParent) {
      VecCopy(&moby->m_Position, &pParent->m_Position);
    }

    MobySetShaded(moby);

    break;
  }

  // Blowhard Storm Cloud
  case 37: {
    Moby37Props *props = moby->m_Props;
    Vector3D v;

    func_8003A720(moby);

    moby->m_ShadowDistance = -1;
    VecCopy(&v, &moby->m_Position);

    v.z += 1024;
    ColFindFloor(&v, 0x10000);
    MobyUpdateShadow(moby);

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
    MobyUpdateCollision(moby);
    break;
  }

  // Storm Wizard Lightning
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

    MobyUpdateCollision(moby);
    break;
  }

  // Blowhard Storm Cloud Lightning
  case 39: {
    Moby39Props *props = moby->m_Props;

    func_8003A720(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);
    MobyUpdateCollision(moby);

    moby->m_Rotation.z = Atan2(g_Camera.m_Position.x - moby->m_Position.x,
                               g_Camera.m_Position.y - moby->m_Position.y, 0);
    moby->m_Position.z -= 1024;

    props->m_0x00 = 0x40;
    props->m_0x04 = pParent;
    props->m_0x08 = 1;

    break;
  }

  // Cupid Arrow
  case 55: {
    int angle;
    Moby55Props *props = moby->m_Props;

    func_8003A720(moby);
    MobyGetAnimatedVertex(pParent, 0, &moby->m_Position);

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

    MobyUpdateCollision(moby);
    props->m_Lifetime = 140;

    break;
  }

  // Bat projectile (PROTOTYPE)
  case 56: {
    Moby56Props *props = moby->m_Props;
    int angle;

    func_8003A720(moby);
    MobyGetAnimatedVertex(pParent, 0, &moby->m_Position);

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

    MobyUpdateCollision(moby);
    props->m_Lifetime = 240;

    break;
  }

  // Flight Train Barrel
  case 78: {
    func_8003A720(moby);       // Reset the Moby first
    MobyUpdateCollision(moby); // Update collision
    break;
  }

  case 14:          // Life orb
  case 83 ... 87: { // Gems

    Vector3D v; // Name from S2
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
    MobySetShaded(moby); // Set shaded moby

    moby->m_ShadowDistance = -1;

    VecCopy(&v, &moby->m_Position);

    v.z += 1024;

    ColFindFloor(&v, 0x10000);

    MobyUpdateShadow(moby); // Sets the shadow size to the distance

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

  case 93: { // Metal Fragment
    MobyFragmentProps *props = moby->m_Props;
    Moby35Props *parentProps;
    int angle1;
    int angle2;
    int absCos;

    func_8003A720(moby);

    moby->m_RenderRadius = 32;
    VecCopy(&moby->m_Position, &pParent->m_Position);
    MobyUpdateCollision(moby);

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

  case 215: { // Tin soldier pieces
    MobyFragmentProps *props;
    int randRes;
    int angle;

    randRes = RandRange(120, 150);

    props = moby->m_Props;
    func_8003A720(moby);

    moby->m_RenderRadius = 32;
    VecCopy(&moby->m_Position, &pParent->m_Position);
    MobyUpdateCollision(moby);

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

  case 120: { // Sparx
    MobySparxProps *sparxProps = moby->m_Props;

    func_8003A720(moby);       // Reset the Moby first
    MobyUpdateCollision(moby); // Update collision

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

  case 124: { // Lamp fool transition
    Moby124Props *props = moby->m_Props;

    func_8003A720(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);

    moby->m_Rotation = pParent->m_Rotation;

    props->m_0x00 = pParent;

    MobyUpdateCollision(moby);
    break;
  }

  case 232: { // Gnorc Copter Blades
    Moby232Props *props = moby->m_Props;

    func_8003A720(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);
    moby->m_Position.z += 1024;
    MobyUpdateCollision(moby);

    props->m_0x04 = 200;
    props->m_0x08 = 350;
    props->m_0x00 = AngleLerpClamped(ANGLE_FROM_SPYRO(moby->m_Position),
                                     g_Spyro.m_bodyRotation.z, 40, 64);
    props->m_0x0c = 120;

    break;
  }

  case 152 ... 153: { // Fireworks chest fragments
    func_8003A720(moby);
    moby->m_RenderRadius = 32;
    moby->m_UpdateDistance = 255;
    MobySetShaded(moby);
    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;
    moby->m_SpecularMetalType = 13;
    break;
  }

  // Turtle Projectile
  case 155: {
    Moby155Props *props = moby->m_Props;
    int angle;

    func_8003A720(moby);
    MobyGetAnimatedVertex(pParent, 0, &moby->m_Position);

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

    MobyUpdateCollision(moby);
    props->m_0x00 = 240;
    break;
  }

  // TNT Barrel
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
    MobyUpdateCollision(moby);

    moby->m_Renderer.raw = 0x10;
    moby->m_RenderRadius = 32;
    moby->m_ShadowDistance = -1;

    VecCopy(&v, &moby->m_Position);
    v.z += 1024;
    ColFindFloor(&v, 0x10000);
    MobyUpdateShadow(moby);

    break;
  }

  // Metal Barrel
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
    MobyUpdateCollision(moby);

    moby->m_Renderer.raw = 0x90;
    moby->m_RenderRadius = 32;
    ((int *)&moby->m_SpecularMetalColor)[0] = 0xA18618;
    moby->m_ShadowDistance = -1;

    VecCopy(&v, &moby->m_Position);
    v.z += 1024;
    ColFindFloor(&v, 0x10000);
    MobyUpdateShadow(moby);

    break;
  }

  // Barrier effect
  case 234: {
    func_8003A720(moby); // Reset the Moby first
    VecCopy(&moby->m_Position, &g_Spyro.unk_0x17c);
    moby->m_Rotation.z = Atan2(g_Spyro.m_KnockbackDirection.x,
                               g_Spyro.m_KnockbackDirection.y, 0) +
                         64;
    MobyUpdateCollision(moby); // Update collision
    break;
  }

  // Fragments
  case 133:           // Door fragment
  case 151:           // Fireworks chest fragment
  case 255 ... 257:   // Wooden chest fragments
  case 67 ... 69:     // Spring chest fragments
  case 309 ... 311:   // Metal, locked and armored chest fragments
  case 423 ... 425:   // Extra life chest fragments
  case 478 ... 480: { // Flight chest fragments
    MobyFragmentProps *props = moby->m_Props;

    int angle1;
    int angle2;

    func_8003A720(moby); // Reset the Moby first

    moby->m_RenderRadius = 32;
    VecCopy(&moby->m_Position, &pParent->m_Position);

    MobyUpdateCollision(moby); // Update collision

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

  // Dragon fragment
  case 251: {
    Vector3D v; // Name from S2
    int randRes;

    MobyDragonFragmentProps *dragonFragmentProps = moby->m_Props;

    func_8003A720(moby); // Reset the Moby first

    moby->m_RenderRadius = 32;
    moby->m_UpdateDistance = -1;

    MobySetShaded(moby); // Set shaded moby

    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;
    moby->m_SpecularMetalType = 14;

    // (moby->m_ScaleOverride & 0x80000000) is an awful hack needed to match
    // stack usage, it's always false because m_ScaleOverride is a u_char
    if (g_DragonCutscene.m_State == 3 || (moby->m_ScaleOverride & 0x80000000)) {
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

  case 481 ... 483: { // Flight Train, Wagon and Plane Fragments
    MobyFragmentProps *props = moby->m_Props;
    int angle1, angle2;

    func_8003A720(moby);
    moby->m_RenderRadius = 32;
    VecCopy(&moby->m_Position, &pParent->m_Position);
    MobyUpdateCollision(moby);

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

  case 359 ... 361: { // Flight Train Barrel Fragments
    MobyFragmentProps *props = moby->m_Props;

    func_8003A720(moby); // Reset the Moby first

    moby->m_RenderRadius = 32;

    VecCopy(&moby->m_Position, &pParent->m_Position);
    MobyUpdateCollision(moby); // Update collision

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

  case 362: { // Flight Train wheels
    MobyFragmentProps *props = moby->m_Props;
    Moby407Props *parentProps = pParent->m_Props;
    Vector3D v;
    func_8003A720(moby); // Reset
    moby->m_RenderRadius = 32;
    MobyUpdateCollision(moby); // Collision update

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

  case 260 ... 269: // Text 0-9
  case 277:         // Text Slash
  case 327:         // Hud .
  {
    MobyNumberProps *textProps = moby->m_Props;

    func_8003A720(moby); // Reset the Moby first
    MobySetShaded(moby); // Set shaded moby

    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;
    moby->m_SpecularMetalType = 2;

    textProps->m_Lifetime = 64;
    break;
  }

  case 288 ... 289: { // Bird feathers
    Moby288Props *props = moby->m_Props;
    int angle1;
    int angle2;

    func_8003A720(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);
    MobyUpdateCollision(moby);

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

  case 295: { // Ice Wizard Projectile
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

    MobyUpdateCollision(moby);
    break;
  }

  case 304: { // Tornado
    Vector3D v;
    Moby304Props *props = moby->m_Props;
    Moby303Props *parentProps = pParent->m_Props;

    func_8003A720(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);

    props->m_0x04 = pParent;
    props->m_0x00 = parentProps->m_0x00;
    VecNull(&props->m_0x08);

    moby->m_RenderRadius = 32;
    MobyUpdateCollision(moby);

    moby->m_ShadowDistance = -1;
    VecCopy(&v, &moby->m_Position);

    v.z += 1024;
    ColFindFloor(&v, 0x10000);
    MobyUpdateShadow(moby);

    break;
  }

  case 318: { // Ice Wizard Projectile Sparks
    Moby318Props *props = moby->m_Props;

    func_8003A720(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);

    props->m_0x00.x = (rand() & 0x7E) - 63;
    props->m_0x00.y = (rand() & 0x7E) - 63;
    props->m_0x00.z = (rand() & 0x7E) - 16;
    props->m_0x0c = (rand() & 0x1F) + 32;

    MobyUpdateCollision(moby);
    break;
  }

  case 345 ... 347: // Flight +1S, +2S, +3S mobys
  {
    if (g_FlightCourseRecords[g_Homeworld]) {
      MobySetShaded(moby); // Set shaded moby
      MobyFree(moby);
      moby = nullptr;
    } else {
      func_8003A720(moby); // Reset the Moby first
      if (pParent != nullptr) {
        VecCopy(&moby->m_Position, &pParent->m_Position);
      }
      moby->m_RenderRadius = 64;
      MobySetShaded(moby); // Set shaded moby
      moby->m_SpecularMetalColor[0] = 0;
      moby->m_SpecularMetalColor[1] = 0;
      moby->m_SpecularMetalColor[2] = 0;
      moby->m_SpecularMetalType = 2;
    }
    break;
  }

  case 343: {
    Moby343Props *props = moby->m_Props;

    func_8003A720(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);

    props->m_0x00 = pParent;
    props->m_0x04 = 0;
    props->m_0x08 = 0;

    moby->m_RenderRadius = 0;

    MobyUpdateCollision(moby);

    moby->m_WasDrawn = 0;
    break;
  }

  case 374: {            // Flight Gate Fragment
    func_8003A720(moby); // Reset the Moby first
    VecCopy(&moby->m_Position, &pParent->m_Position);
    moby->m_Rotation = pParent->m_Rotation;
    MobyUpdateCollision(moby); // Update collision
    moby->m_Renderer.raw = 0xbf;
    moby->m_SpecularMetalColor[0] = pParent->m_SpecularMetalColor[0];
    moby->m_SpecularMetalColor[1] = pParent->m_SpecularMetalColor[1];
    moby->m_SpecularMetalColor[2] = pParent->m_SpecularMetalColor[2];
    moby->m_SpecularMetalType = pParent->m_SpecularMetalType;
    moby->m_RenderRadius = pParent->m_RenderRadius;
    break;
  }

  case 375 ... 386: {    // Flight Gate Remaining Fragments
    func_8003A720(moby); // Reset the Moby first
    VecCopy(&moby->m_Position, &pParent->m_Position);
    moby->m_Rotation = pParent->m_Rotation;
    MobyUpdateCollision(moby); // Update collision
    moby->m_Renderer.raw = 0xbf;
    moby->m_SpecularMetalColor[0] = pParent->m_SpecularMetalColor[0];
    moby->m_SpecularMetalColor[1] = pParent->m_SpecularMetalColor[1];
    moby->m_SpecularMetalColor[2] = pParent->m_SpecularMetalColor[2];
    moby->m_SpecularMetalType = pParent->m_SpecularMetalType;
    break;
  }

  // Flight HUD elements
  case 387 ... 389:   // Ring, arch, chest
  case 393 ... 394:   // Plane, copter
  case 396:           // Boat
  case 490 ... 491: { // Barrel, lighthouse
    func_8003A720(moby);
    moby->m_RenderRadius = 0;
    moby->m_Position.x = -100;
    moby->m_Position.y = 30;
    moby->m_Position.z = 4096;

    MobySetShaded(moby);
    moby->m_DepthOffset = 32;
    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;
    moby->m_SpecularMetalType = 0;
    break;
  }

  // Fan chest top
  case 392: {
    func_8003A720(moby); // Reset the Moby first
    moby->m_DepthOffset = 5;

    if (pParent) {
      VecCopy(&moby->m_Position, &pParent->m_Position);
    } else {
      VecCopy(&moby->m_Position, &g_Spyro.m_Position);
    }

    MobyUpdateCollision(moby); // Update collision
    break;
  }

  case 398:   // Portal Path Moby (OOPS, should be 397, dim lighthouse!)
  case 399: { // Lighthouse light lit
    func_8003A720(moby); // Reset the Moby first

    moby->m_RenderRadius = -1;

    moby->m_Position.x = 460;
    moby->m_Position.y = 40;
    moby->m_Position.z = 4096;

    MobySetShaded(moby); // Set shaded moby

    moby->m_DepthOffset = 32;

    moby->m_SpecularMetalColor[0] = 0;
    moby->m_SpecularMetalColor[1] = 0;
    moby->m_SpecularMetalColor[2] = 0;
    moby->m_SpecularMetalType = 0;

    break;
  }

  // Water effects
  case 363 ... 364:
  case 405: // Drowning splash
  case 477: // Drowning bubbles
  case 507 ... 508:
  case 400: {
    int d, dt;

    func_8003A720(moby); // Reset the Moby first

    if (pParent) {
      VecCopy(&moby->m_Position, &pParent->m_Position);
    } else {
      VecCopy(&moby->m_Position, &g_Spyro.m_Position);
    }

    moby->m_Position.z += 512;

    d = ColFindFloor(&moby->m_Position, 2048);

    dt = d - moby->m_Position.z;

    if (dt < 0)
      dt = -dt;

    if (dt < 2048) {
      moby->m_Position.z = d;
    } else {
      moby->m_Position.z -= 512;
    }

    MobyUpdateCollision(moby); // Update collision

    break;
  }

  // Breakable fragment
  case 454 ... 456: {
    MobyFragmentProps *props;
    int randRes;

    randRes = RandRange(-2400, 1400);

    props = moby->m_Props;
    func_8003A720(moby);
    VecCopy(&moby->m_Position, &pParent->m_Position);
    MobyUpdateCollision(moby);

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

  case 76:               // Apostrophe
  case 426 ... 451: {    // Text A-Z
    func_8003A720(moby); // Reset the Moby first

    moby->m_RenderRadius = 32;
    moby->m_UpdateDistance = -1;

    MobySetShaded(moby); // Set shaded moby
    break;
  }

  case 458 ... 459: { // Cannonball fragment
    MobyFragmentProps *props = moby->m_Props;

    func_8003A720(moby);
    moby->m_RenderRadius = 32;
    VecCopy(&moby->m_Position, &pParent->m_Position);
    MobyUpdateCollision(moby);

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

  // Chicken fodder feather
  case 502: {
    Moby502Props *props = moby->m_Props;
    int angle1;
    int angle2;

    func_8003A720(moby); // Reset the Moby first
    VecCopy(&moby->m_Position, &pParent->m_Position);
    MobyUpdateCollision(moby); // Update collision

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

  default: {
    func_8003A720(moby); // Reset the Moby first

    if (pParent) {
      VecCopy(&moby->m_Position, &pParent->m_Position);
    } else {
      VecCopy(&moby->m_Position, &g_Spyro.m_Position);
    }

    MobyUpdateCollision(moby); // Update collision
    break;
  }
  }

  return moby;
}