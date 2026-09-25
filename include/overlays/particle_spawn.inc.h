#include "camera.h"
#include "graphics.h"
#include "math.h"
#include "moby.h"
#include "overlay_pointers.h"
#include "rand.h"
#include "renderers.h"
#include "spyro.h"
#include "vector.h"

extern Color D_8006E438[];
extern Vector3D D_8006E498[];
extern Vector3D D_8006E4E0[];
extern Vector3D D_8006E570;

// Particle classes 11 and 72 are spawned by func_800530C0 (Moby death effect
// related) and not present in this function. They are still updated by
// ParticleUpdate
// TODO:
// -Determine how to handle m_Raw access. Dedicated structs per class?
// -Document spawnParam/extraParam types for each case. Possibly find a way to
//  avoid having to cast

void NAME_OVERLAY_FUNCTION(SpawnParticle)(int pCount, int pClass, void *spawnParam,
                                          int extraParam) {
  Particle *particle;
  int i;

  for (i = 0; i < pCount; i++) {
    switch (pClass) {
#ifdef HAS_PARTICLE_0
    case 0: {
      particle = func_80053570(2);
      particle->m_Class = pClass;
      particle->m_Timer = 0;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                           (Vector3D *)spawnParam);
      func_80017BFC((Vector3D16 *)&particle->m_Data.m_Raw[20],
                           (Vector3D *)extraParam);
      *(short *)&particle->m_Data.m_Raw[26] = 0;
      particle->m_Data.m_RotatedQuad.m_Size = 24;
      particle->m_Data.m_RotatedQuad.m_Rotation = rand();
      particle->m_Data.m_RotatedQuad.m_Color.r = 128;
      particle->m_Data.m_RotatedQuad.m_Color.g = 128;
      particle->m_Data.m_RotatedQuad.m_Color.b = 128;
      particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
      particle->m_Data.m_RotatedQuad.m_OtOffset = 4;
      particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_1
    case 1: {
      int gamestate;

      particle = func_80053570(2);
      particle->m_Class = pClass;
      particle->m_Timer = 0;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                           (Vector3D *)spawnParam);
      func_80017BFC((Vector3D16 *)&particle->m_Data.m_Raw[20],
                           (Vector3D *)extraParam);

      // TODO: hack
      gamestate = g_Gamestate;
      *(short *)&particle->m_Data.m_Raw[26] = 0;

      if (gamestate == GS_Dragon) {
        particle->m_Data.m_RotatedQuad.m_Size = 8;
      } else {
        particle->m_Data.m_RotatedQuad.m_Size = 16;
      }

      particle->m_Data.m_RotatedQuad.m_Rotation = rand();
      particle->m_Data.m_RotatedQuad.m_Color.r = 96;
      particle->m_Data.m_RotatedQuad.m_Color.g = 96;
      particle->m_Data.m_RotatedQuad.m_Color.b = 96;
      particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
      particle->m_Data.m_RotatedQuad.m_OtOffset = 4;
      particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_2
    case 2: {
      Vector3D randomVelocity;

      particle = func_80053570(2);
      particle->m_Class = pClass;
      particle->m_Timer = 0;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                           (Vector3D *)spawnParam);

      randomVelocity.x = (rand() & 63) - 32;
      randomVelocity.y = (rand() & 63) - 32;
      randomVelocity.z = 30;

      func_80017BFC((Vector3D16 *)&particle->m_Data.m_Raw[20],
                           &randomVelocity);
      *(short *)&particle->m_Data.m_Raw[26] = 0;
      particle->m_Data.m_RotatedQuad.m_Size = 32;
      particle->m_Data.m_RotatedQuad.m_Rotation = rand();

      particle->m_Data.m_RotatedQuad.m_Color.r = 128;
      particle->m_Data.m_RotatedQuad.m_Color.g = 128;
      particle->m_Data.m_RotatedQuad.m_Color.b = 128;
      particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
      particle->m_Data.m_RotatedQuad.m_OtOffset = 4;
      particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_4
    case 4: {
      particle = func_80053570(3);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 7;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_Quad.m_Position,
                           (Vector3D *)spawnParam);

      particle->m_Data.m_Quad.m_Position.x += (rand() & 126) - 63;
      particle->m_Data.m_Quad.m_Position.y += (rand() & 126) - 63;
      particle->m_Data.m_Quad.m_Position.z += (rand() & 126) - 63;

      *(int *)&particle->m_Data.m_Raw[20] = extraParam;
      *(short *)&particle->m_Data.m_Raw[26] = 0;

      particle->m_Data.m_Quad.m_Width = (rand() & 15) + 24;
      particle->m_Data.m_Quad.m_Height = (rand() & 7) + 15;

      particle->m_Data.m_Quad.m_Color.r = 128;
      particle->m_Data.m_Quad.m_Color.g = 128;
      particle->m_Data.m_Quad.m_Color.b = 128;
      particle->m_Data.m_Quad.m_Color.s = PRIM_POLY_FT4;
      particle->m_Data.m_Quad.m_OtOffset = 4;
      particle->m_Data.m_Quad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_5
    case 5: {
      particle = func_80053570(3);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 7;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_Quad.m_Position,
                           (Vector3D *)spawnParam);

      particle->m_Data.m_Quad.m_Position.x += (rand() & 62) - 31;
      particle->m_Data.m_Quad.m_Position.y += (rand() & 62) - 31;
      particle->m_Data.m_Quad.m_Position.z += (rand() & 62) - 31;

      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x = 0;
      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y = 0;
      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z = 0;

      particle->m_Data.m_Quad.m_Width = (rand() & 7) + 12;
      particle->m_Data.m_Quad.m_Height = (rand() & 7) + 10;

      particle->m_Data.m_Quad.m_Color.r = 128;
      particle->m_Data.m_Quad.m_Color.g = 128;
      particle->m_Data.m_Quad.m_Color.b = 128;
      particle->m_Data.m_Quad.m_Color.s = PRIM_POLY_FT4;
      particle->m_Data.m_Quad.m_OtOffset = 4;
      particle->m_Data.m_Quad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_6
    case 6: {
      // TODO: Type props struct
      int *props;
      // spawnParam is the whirlwind Moby (300) that is spawning this particle
      props = ((Moby *)spawnParam)->m_Props;

      particle = func_80053570(3);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 15;
      particle->m_WasRendered = 1;

      func_80017BFC(&particle->m_Data.m_Quad.m_Position,
                           &((Moby *)spawnParam)->m_Position);

      particle->m_Data.m_Quad.m_Position.x += (rand() & 126) - 63;
      particle->m_Data.m_Quad.m_Position.y += (rand() & 126) - 63;
      particle->m_Data.m_Quad.m_Position.z += (rand() & 511) - 256;

      *(Vector3D **)&particle->m_Data.m_Raw[20] = &((Moby *)spawnParam)->m_Position;
      *(short *)&particle->m_Data.m_Raw[24] = props[1];
      *(short *)&particle->m_Data.m_Raw[26] = props[0] >> 6;

      particle->m_Data.m_Quad.m_Width = 32;
      particle->m_Data.m_Quad.m_Height = 20;

      if (((Moby *)spawnParam)->m_Substate != 0) {
        switch (rand() & 7) {
        case 0:
          particle->m_Data.m_Quad.m_Color.r = 128;
          particle->m_Data.m_Quad.m_Color.g = 0;
          particle->m_Data.m_Quad.m_Color.b = 0;
          break;

        case 1:
          particle->m_Data.m_Quad.m_Color.r = 128;
          particle->m_Data.m_Quad.m_Color.g = 128;
          particle->m_Data.m_Quad.m_Color.b = 0;
          break;

        case 2:
          particle->m_Data.m_Quad.m_Color.r = 0;
          particle->m_Data.m_Quad.m_Color.g = 128;
          particle->m_Data.m_Quad.m_Color.b = 0;
          break;

        case 3:
          particle->m_Data.m_Quad.m_Color.r = 0;
          particle->m_Data.m_Quad.m_Color.g = 128;
          particle->m_Data.m_Quad.m_Color.b = 128;
          break;

        case 4:
          particle->m_Data.m_Quad.m_Color.r = 0;
          particle->m_Data.m_Quad.m_Color.g = 0;
          particle->m_Data.m_Quad.m_Color.b = 128;
          break;

        case 5:
          particle->m_Data.m_Quad.m_Color.r = 128;
          particle->m_Data.m_Quad.m_Color.g = 0;
          particle->m_Data.m_Quad.m_Color.b = 128;
          break;

        case 6:
          particle->m_Data.m_Quad.m_Color.r = 128;
          particle->m_Data.m_Quad.m_Color.g = 64;
          particle->m_Data.m_Quad.m_Color.b = 0;
          break;

        case 7:
          particle->m_Data.m_Quad.m_Color.r = 0;
          particle->m_Data.m_Quad.m_Color.g = 64;
          particle->m_Data.m_Quad.m_Color.b = 128;
          break;
        }
      } else if (g_LevelId == 50) {
        particle->m_Data.m_Quad.m_Color.r = 128;
        particle->m_Data.m_Quad.m_Color.g = 128;
        particle->m_Data.m_Quad.m_Color.b = 0;
      } else {
        particle->m_Data.m_Quad.m_Color.r = 128;
        particle->m_Data.m_Quad.m_Color.g = 128;
        particle->m_Data.m_Quad.m_Color.b = 128;
      }

      particle->m_Data.m_Quad.m_Color.s = PRIM_POLY_FT4;
      particle->m_Data.m_Quad.m_OtOffset = 0;
      particle->m_Data.m_Quad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_7
    case 7: {
      particle = func_80053570(2);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 15;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                           (Vector3D *)spawnParam);

      if (extraParam != 0) {
        particle->m_Data.m_RotatedQuad.m_Position.x +=
            (extraParam * ((rand() & 0xFE) - 0x7F)) >> 8;
        particle->m_Data.m_RotatedQuad.m_Position.y +=
            (extraParam * ((rand() & 0xFE) - 0x7F)) >> 8;
        particle->m_Data.m_RotatedQuad.m_Position.z +=
            (extraParam * ((rand() & 0xFE) - 0x30)) >> 8;
      }

      particle->m_Data.m_RotatedQuad.m_Size = particle->m_Timer * 4;
      particle->m_Data.m_RotatedQuad.m_Rotation = rand();

      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x = (rand() & 14) - 7;
      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y = (rand() & 14) - 7;
      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z = (rand() & 14) - 7;
      *(short *)&particle->m_Data.m_Raw[26] = (rand() & 15) + 6;

      particle->m_Data.m_RotatedQuad.m_Color.r = 128;
      particle->m_Data.m_RotatedQuad.m_Color.g = 128;
      particle->m_Data.m_RotatedQuad.m_Color.b = 128;
      particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);

      particle->m_Data.m_RotatedQuad.m_OtOffset = 4;
      particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_8
    case 8: {
      Vector3D position;

      particle = func_80053570(3);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 3;
      particle->m_WasRendered = 1;

      func_80052D64((Moby *)spawnParam, rand() & 1, &position);
      func_80017BFC(&particle->m_Data.m_Quad.m_Position, &position);

      particle->m_Data.m_Quad.m_Position.x += (rand() & 14) - 7;
      particle->m_Data.m_Quad.m_Position.y += (rand() & 14) - 7;
      particle->m_Data.m_Quad.m_Position.z += (rand() & 14) - 7;

      VecSub(&position, &position, &((Moby *)spawnParam)->m_Position);
      position.z -= 900;

      func_80017330(&position, 0x80);

      func_80017BFC((Vector3D16 *)&particle->m_Data.m_Raw[20],
                           &position);

      particle->m_Data.m_Raw[26] = (Moby *)extraParam - g_LevelMobys;
      particle->m_Data.m_Raw[27] = 0;

      particle->m_Data.m_Quad.m_Width = (rand() & 15) + 24;
      particle->m_Data.m_Quad.m_Height = (rand() & 7) + 15;

      particle->m_Data.m_Quad.m_Color.s = PRIM_POLY_FT4;
      particle->m_Data.m_Quad.m_OtOffset = 4;
      particle->m_Data.m_Quad.m_TextureIndex = 0;

      switch (rand() & 3) {
      case 0:
      case 1:
        particle->m_Data.m_Quad.m_Color.r = 127;
        particle->m_Data.m_Quad.m_Color.g = 127;
        particle->m_Data.m_Quad.m_Color.b = 32;
        break;
      case 2:
        particle->m_Data.m_Quad.m_Color.r = 64;
        particle->m_Data.m_Quad.m_Color.g = 127;
        particle->m_Data.m_Quad.m_Color.b = 64;
        break;
      case 3:
        particle->m_Data.m_Quad.m_Color.r = 127;
        particle->m_Data.m_Quad.m_Color.g = 127;
        particle->m_Data.m_Quad.m_Color.b = 127;
        break;
      }

      break;
    }
#endif
#ifdef HAS_PARTICLE_9
    case 9: {
      particle = func_80053570(2);
      particle->m_Class = pClass;
      particle->m_Timer = 0;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                           (Vector3D *)spawnParam);
      func_80017BFC((Vector3D16 *)&particle->m_Data.m_Raw[20],
                           (Vector3D *)extraParam);
      *(short *)&particle->m_Data.m_Raw[26] = 0;
      particle->m_Data.m_RotatedQuad.m_Size = 24;
      particle->m_Data.m_RotatedQuad.m_Rotation = rand();

      if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed > 0x5780) {
        particle->m_Data.m_RotatedQuad.m_Color.r = 255;
        particle->m_Data.m_RotatedQuad.m_Color.g = 0;
        particle->m_Data.m_RotatedQuad.m_Color.b = 0;
      } else if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed > 0x4240) {
        particle->m_Data.m_RotatedQuad.m_Color.r = 240;
        particle->m_Data.m_RotatedQuad.m_Color.g = 96;
        particle->m_Data.m_RotatedQuad.m_Color.b = 0;
      } else if (g_Spyro.m_Physics.m_SpeedAngle.m_Speed > 0x3680) {
        particle->m_Data.m_RotatedQuad.m_Color.r = 224;
        particle->m_Data.m_RotatedQuad.m_Color.g = 224;
        particle->m_Data.m_RotatedQuad.m_Color.b = 0;
      } else {
        particle->m_Data.m_RotatedQuad.m_Color.r = 128;
        particle->m_Data.m_RotatedQuad.m_Color.g = 128;
        particle->m_Data.m_RotatedQuad.m_Color.b = 128;
      }

      particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
      particle->m_Data.m_RotatedQuad.m_OtOffset = 4;
      particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_10
    case 10: {
      particle = func_80053570(3);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 31;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_Quad.m_Position,
                           &g_Spyro.m_Position);
      particle->m_Data.m_Quad.m_Width = 24;
      particle->m_Data.m_Quad.m_Height = 15;
      particle->m_Data.m_Quad.m_Color.r = D_8006E438[i].r;
      particle->m_Data.m_Quad.m_Color.g = D_8006E438[i].g;
      particle->m_Data.m_Quad.m_Color.b = D_8006E438[i].b;
      particle->m_Data.m_Quad.m_Color.s = PRIM_POLY_FT4;
      particle->m_Data.m_Quad.m_OtOffset = 4;
      particle->m_Data.m_Quad.m_TextureIndex = 0;
      *(short *)&particle->m_Data.m_Raw[20] = ((pCount - i) << 12) / 5;
      break;
    }
#endif
#ifdef HAS_PARTICLE_12
    case 12: {
      Vector3D mobyPosition;

      particle = func_80053570(2);
      particle->m_Class = pClass;
      particle->m_WasRendered = 1;
      particle->m_Data.m_RotatedQuad.m_OtOffset = 4;

      if (((Moby *)spawnParam)->m_Class == MOBYCLASS_DRAGON_EGG) {
        VecCopy(&mobyPosition, &((Moby *)spawnParam)->m_Position);
      } else if (((Moby *)spawnParam)->m_Class == MOBYCLASS_KEY ||
                 ((Moby *)spawnParam)->m_Class == 181) {
        if (extraParam >> 24 < 6) {
          VecRotateByMatrix((MATRIX *)&((Moby *)spawnParam)->m_RotationMatrix,
                            &D_8006E4E0[extraParam >> 24], &mobyPosition);
          VecAdd(&mobyPosition, &mobyPosition, &((Moby *)spawnParam)->m_Position);
        } else {
          particle->m_RenderType = 5;
          particle->m_Data.m_RotatedQuad.m_OtOffset = 0x16;
          VecCopy(&mobyPosition, &D_8006E4E0[extraParam >> 24]);
        }
      } else {

        if (((Moby *)spawnParam)->m_Class == MOBYCLASS_SPARX) {
          VecRotateByMatrix((MATRIX *)&((Moby *)spawnParam)->m_RotationMatrix,
                            &D_8006E570, &mobyPosition);
          VecAdd(&mobyPosition, &mobyPosition, &((Moby *)spawnParam)->m_Position);

        } else {
          VecRotateByMatrix((MATRIX *)&((Moby *)spawnParam)->m_RotationMatrix,
                            &D_8006E498[i], &mobyPosition);
          VecAdd(&mobyPosition, &mobyPosition, &((Moby *)spawnParam)->m_Position);
        }
      }

      func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                           &mobyPosition);
      particle->m_Data.m_RotatedQuad.m_Color.g = extraParam >> 8;
      particle->m_Data.m_RotatedQuad.m_Color.r = extraParam;
      particle->m_Data.m_RotatedQuad.m_Color.b = extraParam >> 16;
      particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
      particle->m_Data.m_RotatedQuad.m_Size = (rand() & 7) + 16;
      particle->m_Data.m_RotatedQuad.m_Rotation = rand();
      particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_13
    case 13: {
      particle = func_80053570(2);
      particle->m_Class = pClass;
      particle->m_Timer = 0;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                           (Vector3D *)spawnParam);
      func_80017BFC((Vector3D16 *)&particle->m_Data.m_Raw[20],
                           (Vector3D *)extraParam);
      *(short *)&particle->m_Data.m_Raw[26] = 0;
      particle->m_Data.m_RotatedQuad.m_Size = 24;
      particle->m_Data.m_RotatedQuad.m_Rotation = rand();
      particle->m_Data.m_RotatedQuad.m_Color.r = 255;
      particle->m_Data.m_RotatedQuad.m_Color.g = 255;
      particle->m_Data.m_RotatedQuad.m_Color.b = 0;
      particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
      particle->m_Data.m_RotatedQuad.m_OtOffset = 4;
      particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_14
    case 14: {
      int distance;

      distance = OctDistance((Vector3D *)spawnParam, &g_Camera.m_Position);

      if (distance < 0x8000) {
        particle = func_80053570(2);
        particle->m_Class = pClass;
        particle->m_Timer = 0;
        particle->m_WasRendered = 1;
        func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                             (Vector3D *)spawnParam);
        func_80017BFC((Vector3D16 *)&particle->m_Data.m_Raw[20],
                             (Vector3D *)extraParam);

        *(short *)&particle->m_Data.m_Raw[26] = 0;
        particle->m_Data.m_RotatedQuad.m_Size = 64;
        particle->m_Data.m_RotatedQuad.m_Rotation = rand();

        if (distance > 0x6000) {
          distance = (0x8000 - distance) >> 6;
        } else {
          distance = 0x80;
        }

        particle->m_Data.m_RotatedQuad.m_Color.r = distance;
        particle->m_Data.m_RotatedQuad.m_Color.g = distance;
        particle->m_Data.m_RotatedQuad.m_Color.b = distance;
        particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
        particle->m_Data.m_RotatedQuad.m_OtOffset = 4;
        particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      }

      break;
    }
#endif
#ifdef HAS_PARTICLE_15
    case 15: {
      particle = func_80053570(3);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 7;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_Quad.m_Position,
                           (Vector3D *)spawnParam);

      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x = (rand() & 0x1E) - 15;
      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y = (rand() & 0x1E) - 15;
      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z = (rand() & 0x1E) - 15;

      particle->m_Data.m_Quad.m_Position.x +=
          ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x;
      particle->m_Data.m_Quad.m_Position.y +=
          ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y;
      particle->m_Data.m_Quad.m_Position.z +=
          ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z;

      particle->m_Data.m_Quad.m_Width = (rand() & 7) + 12;
      particle->m_Data.m_Quad.m_Height = (rand() & 7) + 10;

      particle->m_Data.m_Quad.m_Color.r = 128;
      particle->m_Data.m_Quad.m_Color.g = 128;
      particle->m_Data.m_Quad.m_Color.b = 128;
      particle->m_Data.m_Quad.m_Color.s = PRIM_POLY_FT4;
      particle->m_Data.m_Quad.m_OtOffset = 4;
      particle->m_Data.m_Quad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_16
    case 16: {
      particle = func_80053570(2);
      particle->m_Class = pClass;
      particle->m_Timer = 0;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                           (Vector3D *)spawnParam);
      func_80017BFC((Vector3D16 *)&particle->m_Data.m_Raw[20],
                           (Vector3D *)spawnParam + 1);
      *(short *)&particle->m_Data.m_Raw[26] = 0;
      particle->m_Data.m_RotatedQuad.m_Size = ((int *)extraParam)[0];
      particle->m_Data.m_RotatedQuad.m_Rotation = rand();
      particle->m_Data.m_RotatedQuad.m_Color.r = ((int *)extraParam)[1] * 8;
      particle->m_Data.m_RotatedQuad.m_Color.g =
          particle->m_Data.m_RotatedQuad.m_Color.r;
      particle->m_Data.m_RotatedQuad.m_Color.b =
          particle->m_Data.m_RotatedQuad.m_Color.r;
      particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
      particle->m_Data.m_RotatedQuad.m_OtOffset = 4;
      particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_17
    case 17: {
      particle = func_80053570(2);
      particle->m_Class = pClass;
      particle->m_Timer = 0;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                           (Vector3D *)spawnParam);
      func_80017BFC((Vector3D16 *)&particle->m_Data.m_Raw[20],
                           (Vector3D *)spawnParam + 1);
      *(short *)&particle->m_Data.m_Raw[26] = 0;
      particle->m_Data.m_RotatedQuad.m_Size = 24;
      particle->m_Data.m_RotatedQuad.m_Rotation = rand();
      particle->m_Data.m_RotatedQuad.m_Color.r = ((int *)extraParam)[0];
      particle->m_Data.m_RotatedQuad.m_Color.g = ((int *)extraParam)[1];
      particle->m_Data.m_RotatedQuad.m_Color.b = ((int *)extraParam)[2];
      particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
      particle->m_Data.m_RotatedQuad.m_OtOffset = 4;
      particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_19
    case 19: {
      int distance;

      distance = OctDistance((Vector3D *)spawnParam, &g_Camera.m_Position);

      if (distance < 0x8000) {
        particle = func_80053570(2);
        particle->m_Class = pClass;
        particle->m_Timer = 0;
        particle->m_WasRendered = 1;
        func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                             (Vector3D *)spawnParam);

        *(int *)&particle->m_Data.m_Raw[20] = 32;
        particle->m_Data.m_RotatedQuad.m_Size = 64;
        particle->m_Data.m_RotatedQuad.m_Rotation = rand();

        if (distance > 0x6000) {
          distance = (0x8000 - distance) >> 6;
        } else {
          distance = 0x80;
        }

        particle->m_Data.m_RotatedQuad.m_Color.r = distance;
        particle->m_Data.m_RotatedQuad.m_Color.g = distance;
        particle->m_Data.m_RotatedQuad.m_Color.b = distance;
        particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
        particle->m_Data.m_RotatedQuad.m_OtOffset = 16;
        particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      }

      break;
    }
#endif
#ifdef HAS_PARTICLE_21
    case 21: {
      particle = func_80053570(2);
      particle->m_Class = pClass;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                           (Vector3D *)spawnParam);
      func_80017BFC((Vector3D16 *)&particle->m_Data.m_Raw[14],
                           (Vector3D *)spawnParam);

      if ((extraParam & 0x1F) < 0x10) {
        particle->m_Data.m_Raw[20] = extraParam * 2;
      } else {
        particle->m_Data.m_Raw[20] = extraParam * 2 - 0x80;
      }

      particle->m_Data.m_Raw[21] = 8;
      particle->m_Data.m_RotatedQuad.m_Color.r = ~((extraParam & 15) << 4);
      particle->m_Data.m_RotatedQuad.m_Color.g = 255;
      particle->m_Data.m_RotatedQuad.m_Color.b = 128 - ((extraParam & 15) << 3);
      particle->m_Data.m_RotatedQuad.m_Size = 48 - ((extraParam & 15) << 1);
      particle->m_Data.m_RotatedQuad.m_Rotation = extraParam * 2;
      particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
      particle->m_Data.m_RotatedQuad.m_OtOffset = 2;
      particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_22
    case 22: {
      int distance;

      distance = OctDistance((Vector3D *)spawnParam, &g_Camera.m_Position);

      if (distance < 0x8000) {
        particle = func_80053570(2);
        particle->m_Class = pClass;
        particle->m_Timer = rand() & 15;
        particle->m_WasRendered = 1;
        func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                             (Vector3D *)spawnParam);

        particle->m_Data.m_RotatedQuad.m_Position.x +=
            (((rand() & 0xFFF) - 0x7FF) * 300) >> 12;
        particle->m_Data.m_RotatedQuad.m_Position.y +=
            (((rand() & 0xFFF) - 0x7FF) * 300) >> 12;

        extraParam = (extraParam + (rand() & 0x1E) - 15) & 0xFF;

        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x =
            (COSINE_8(extraParam) * 7) >> 11;
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y =
            (SINE_8(extraParam) * 7) >> 11;
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z = 8;
        *(short *)&particle->m_Data.m_Raw[26] = (rand() & 2) - 1;

        particle->m_Data.m_RotatedQuad.m_Size = 224;
        particle->m_Data.m_RotatedQuad.m_Rotation = rand();

        if (distance > 0x6000) {
          distance = (0x8000 - distance) >> 7;
        } else {
          distance = 0x40;
        }

        particle->m_Data.m_RotatedQuad.m_Color.r = distance >> 1;
        particle->m_Data.m_RotatedQuad.m_Color.g = distance >> 1;
        particle->m_Data.m_RotatedQuad.m_Color.b = distance;
        particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
        particle->m_Data.m_RotatedQuad.m_OtOffset = 12;
        particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      }
      break;
    }
#endif
#ifdef HAS_PARTICLE_23
    case 23: {
      particle = func_80053570(2);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 15;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                           (Vector3D *)spawnParam);

      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x = (rand() & 0x3E) - 0x1F;
      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y = (rand() & 0x3E) - 0x1F;
      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z = (rand() & 0x3E) - 0x1F;
      *(short *)&particle->m_Data.m_Raw[26] = (rand() & 8) - 4;

      particle->m_Data.m_RotatedQuad.m_Position.x +=
          ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x << 3;
      particle->m_Data.m_RotatedQuad.m_Position.y +=
          ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y << 3;
      particle->m_Data.m_RotatedQuad.m_Position.z +=
          ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z << 2;

      particle->m_Data.m_RotatedQuad.m_Size = 128;
      particle->m_Data.m_RotatedQuad.m_Rotation = rand();

      particle->m_Data.m_RotatedQuad.m_Color.r = 96;
      particle->m_Data.m_RotatedQuad.m_Color.g = 96;
      particle->m_Data.m_RotatedQuad.m_Color.b = 96;
      particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
      particle->m_Data.m_RotatedQuad.m_OtOffset = 4;
      particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_24
    case 24: {
      particle = func_80053570(2);
      particle->m_Class = pClass;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                           (Vector3D *)spawnParam);
      func_80017BFC((Vector3D16 *)&particle->m_Data.m_Raw[14],
                           (Vector3D *)spawnParam);
      particle->m_Data.m_RotatedQuad.m_Size = 48;
      particle->m_Data.m_RotatedQuad.m_Color.r = 128;
      particle->m_Data.m_RotatedQuad.m_Color.g = 128;
      particle->m_Data.m_RotatedQuad.m_Color.b = 128;
      particle->m_Data.m_RotatedQuad.m_Rotation = i * 16;
      particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
      particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      particle->m_Data.m_RotatedQuad.m_OtOffset = 8;
      *(short *)&particle->m_Data.m_Raw[20] = i * 32;
      *(short *)&particle->m_Data.m_Raw[22] = 0x10;
      particle->m_Data.m_Raw[24] = i << 4;
      particle->m_Data.m_Raw[25] = i;
      break;
    }
#endif
#ifdef HAS_PARTICLE_25
    case 25: {
      particle = func_80053570(2);
      particle->m_Class = pClass;
      particle->m_Timer = 0;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                           (Vector3D *)spawnParam);
      func_80017BFC((Vector3D16 *)&particle->m_Data.m_Raw[20],
                           (Vector3D *)spawnParam + 1);
      *(short *)&particle->m_Data.m_Raw[26] = 0;
      particle->m_Data.m_RotatedQuad.m_Size = 24;
      particle->m_Data.m_RotatedQuad.m_Rotation = rand();

      if (((int *)spawnParam)[6] > 460) {
        particle->m_Data.m_RotatedQuad.m_Color.r = 255;
        particle->m_Data.m_RotatedQuad.m_Color.g = 0;
        particle->m_Data.m_RotatedQuad.m_Color.b = 0;
      } else if (((int *)spawnParam)[6] > 400) {
        particle->m_Data.m_RotatedQuad.m_Color.r = 240;
        particle->m_Data.m_RotatedQuad.m_Color.g = 96;
        particle->m_Data.m_RotatedQuad.m_Color.b = 0;
      } else if (((int *)spawnParam)[6] > 320) {
        particle->m_Data.m_RotatedQuad.m_Color.r = 224;
        particle->m_Data.m_RotatedQuad.m_Color.g = 224;
        particle->m_Data.m_RotatedQuad.m_Color.b = 0;
      } else {
        particle->m_Data.m_RotatedQuad.m_Color.r = 128;
        particle->m_Data.m_RotatedQuad.m_Color.g = 128;
        particle->m_Data.m_RotatedQuad.m_Color.b = 128;
      }

      particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
      particle->m_Data.m_RotatedQuad.m_OtOffset = 4;
      particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_26
    case 26: {
      particle = func_80053570(2);
      particle->m_Class = pClass;
      particle->m_Timer = 0;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                           (Vector3D *)spawnParam);
      particle->m_Data.m_RotatedQuad.m_Size = 12;
      particle->m_Data.m_RotatedQuad.m_Rotation = rand();
      particle->m_Data.m_RotatedQuad.m_Color.r = extraParam * 8;
      particle->m_Data.m_RotatedQuad.m_Color.g = extraParam * 8;
      particle->m_Data.m_RotatedQuad.m_Color.b = extraParam * 8;
      particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
      particle->m_Data.m_RotatedQuad.m_OtOffset = 4;
      particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_27
    case 27: {
      particle = func_80053570(6);
      particle->m_Class = pClass;
      particle->m_Timer = 0;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                           (Vector3D *)spawnParam);
      particle->m_Data.m_RotatedQuad.m_Size = ((extraParam >> 16) * 6) + 12;
      particle->m_Data.m_RotatedQuad.m_Rotation =
          g_Spyro.m_bodyRotation.z + (rand() & 7) + 29;
      particle->m_Data.m_RotatedQuad.m_Color.r = (extraParam & 0xFFFF) * 8;
      particle->m_Data.m_RotatedQuad.m_Color.g = (extraParam & 0xFFFF) * 8;
      particle->m_Data.m_RotatedQuad.m_Color.b = (extraParam & 0xFFFF) * 8;

      if (!(rand() & 7)) {
        particle->m_Data.m_RotatedQuad.m_Color.r += 16;
        particle->m_Data.m_RotatedQuad.m_Color.g += 16;
        particle->m_Data.m_RotatedQuad.m_Color.b += 16;
      }

      particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
      particle->m_Data.m_RotatedQuad.m_OtOffset = 4;
      particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_28
    case 28: {
      Vector3D particleVelocity;
      int angle;
      angle = rand() & 0xFF;
      particleVelocity.x = 0;
      particleVelocity.y = (extraParam * COSINE_8(angle)) >> 12;
      particleVelocity.z = (extraParam * SINE_8(angle)) >> 12;
      VecRotateByMatrix((MATRIX *)&((Moby *)spawnParam)->m_RotationMatrix,
                        &particleVelocity, &particleVelocity);

      particle = func_80053570(2);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 15;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                           &((Moby *)spawnParam)->m_Position);
      particle->m_Data.m_RotatedQuad.m_Size = particle->m_Timer * 4;
      particle->m_Data.m_RotatedQuad.m_Rotation = rand();
      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x = particleVelocity.x;
      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y = particleVelocity.y;
      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z = particleVelocity.z;
      *(short *)&particle->m_Data.m_Raw[26] = (rand() & 7) - 4;
      particle->m_Data.m_RotatedQuad.m_Color.r = 128;
      particle->m_Data.m_RotatedQuad.m_Color.g = 128;
      particle->m_Data.m_RotatedQuad.m_Color.b = 128;
      particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
      particle->m_Data.m_RotatedQuad.m_OtOffset = 4;
      particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_29
    case 29: {
      // TODO: Type props struct
      int *props;
      // spawnParam is the Haunted Wizard Moby (204) that is spawning this particle
      props = ((Moby *)extraParam)->m_Props;

      particle = func_80053570(3);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 7;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_Quad.m_Position,
                           (Vector3D *)spawnParam);

      particle->m_Data.m_Quad.m_Position.x += (rand() & 126) - 63;
      particle->m_Data.m_Quad.m_Position.y += (rand() & 126) - 63;
      particle->m_Data.m_Quad.m_Position.z += (rand() & 126) - 63;

      particle->m_Data.m_Raw[20] = ((Moby *)extraParam) - g_LevelMobys;
      particle->m_Data.m_Raw[21] = props[15];
      particle->m_Data.m_Raw[22] = 0;
      *(short *)&particle->m_Data.m_Raw[26] = 0;

      particle->m_Data.m_Quad.m_Width = (rand() & 15) + 48;
      particle->m_Data.m_Quad.m_Height = (rand() & 7) + 30;

      particle->m_Data.m_Quad.m_Color.r = 0;
      particle->m_Data.m_Quad.m_Color.g = 128;
      particle->m_Data.m_Quad.m_Color.b = 0;
      particle->m_Data.m_Quad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
      particle->m_Data.m_Quad.m_OtOffset = 4;
      particle->m_Data.m_Quad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_30
    case 30:
      particle = func_80053570(2);
      particle->m_Class = pClass;
      particle->m_Timer = 0;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                           (Vector3D *)spawnParam);

      *(short *)&particle->m_Data.m_Raw[26] = rand() % 2 + 1;
      particle->m_Data.m_RotatedQuad.m_Size = 8;
      particle->m_Data.m_RotatedQuad.m_Rotation = rand();

      particle->m_Data.m_RotatedQuad.m_Color.r = 64;
      particle->m_Data.m_RotatedQuad.m_Color.g = 64;
      particle->m_Data.m_RotatedQuad.m_Color.b = 64;
      particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
      particle->m_Data.m_RotatedQuad.m_OtOffset = 4;
      particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      break;
#endif
#ifdef HAS_PARTICLE_31
    case 31: {
      int temp;

      temp = rand() & 0xFF;

      particle = func_80053570(3);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 15;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_Quad.m_Position,
                           (Vector3D *)spawnParam);

      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x =
          COSINE_8(temp) << 2 >> 12;
      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y = SINE_8(temp) << 2 >> 12;
      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z = 6;

      temp = (rand() & 7) + 16;
      particle->m_Data.m_Quad.m_Width = temp;
      particle->m_Data.m_Quad.m_Height = (temp * 5) << 2 >> 5;

      particle->m_Data.m_Quad.m_Color.r = 128;
      particle->m_Data.m_Quad.m_Color.g = 128;
      particle->m_Data.m_Quad.m_Color.b = 128;
      particle->m_Data.m_Quad.m_Color.s = PRIM_POLY_FT4;
      particle->m_Data.m_Quad.m_OtOffset = 4;
      particle->m_Data.m_Quad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_33
    case 33: {
      Vector3D spyroPosition;

      particle = func_80053570(2);
      particle->m_Class = pClass;
      particle->m_Timer = 0;
      particle->m_WasRendered = 1;

      if (extraParam != 0) {
        spyroPosition.x = 0x164;
        spyroPosition.y = 0;
        spyroPosition.z = 0;
        VecRotateByMatrix(&g_Spyro.m_RotationMatrix, &spyroPosition,
                          &spyroPosition);
        VecAdd(&spyroPosition, &spyroPosition, &g_Spyro.m_Position);
      } else {
        VecCopy(&spyroPosition, &g_Spyro.m_Position);
        spyroPosition.z = g_Spyro.m_surfaceBelowSpyro;
        spyroPosition.x += (rand() & 0x3E) - 0x1F;
        spyroPosition.y += (rand() & 0x3E) - 0x1F;
      }

      func_80017BFC(&particle->m_Data.m_RotatedQuad.m_Position,
                           &spyroPosition);
      func_80017BFC((Vector3D16 *)&particle->m_Data.m_Raw[20],
                           (Vector3D *)spawnParam);
      *(short *)&particle->m_Data.m_Raw[26] = 0;
      particle->m_Data.m_RotatedQuad.m_Size = 16;
      particle->m_Data.m_RotatedQuad.m_Rotation = rand();
      particle->m_Data.m_RotatedQuad.m_Color.r = 32;
      particle->m_Data.m_RotatedQuad.m_Color.g = 32;
      particle->m_Data.m_RotatedQuad.m_Color.b = 32;
      particle->m_Data.m_RotatedQuad.m_Color.s = PRIM_STP(PRIM_POLY_FT4);
      particle->m_Data.m_RotatedQuad.m_OtOffset = 4;
      particle->m_Data.m_RotatedQuad.m_TextureIndex = 0;
      break;
    }
#endif
#ifdef HAS_PARTICLE_65
    case 65: {
      particle = func_80053570(1);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 3;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_Line.m_Position,
                           &((Moby *)spawnParam)->m_Position);

      particle->m_Data.m_Line.m_Position.x += (rand() & 126) - 63;
      particle->m_Data.m_Line.m_Position.y += (rand() & 126) - 63;
      particle->m_Data.m_Line.m_Position.z += (rand() & 15) + 310;

      particle->m_Data.m_Line.m_End.x = particle->m_Data.m_Line.m_Position.x;
      particle->m_Data.m_Line.m_End.y = particle->m_Data.m_Line.m_Position.y;
      particle->m_Data.m_Line.m_End.z =
          particle->m_Data.m_Line.m_Position.z - 32;

      particle->m_Data.m_Line.m_Color1.m_OtOffset = 0;

      particle->m_Data.m_Line.m_Color0.r = 128;
      particle->m_Data.m_Line.m_Color0.g = 128;
      particle->m_Data.m_Line.m_Color0.b = 128;

      particle->m_Data.m_Line.m_Color1.r = 192;
      particle->m_Data.m_Line.m_Color1.g = 192;
      particle->m_Data.m_Line.m_Color1.b = 192;

      // LineG2 Primitive Code
      particle->m_Data.m_Line.m_Color0.s = PRIM_LINE_G2;
      break;
    }
#endif
#ifdef HAS_PARTICLE_66
    case 66: {
      particle = func_80053570(0);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 15;
      particle->m_WasRendered = 1;

      particle->m_Data.m_Point.m_Position.x =
          (((Vector3D *)spawnParam)->x >> 2) + (rand() & 15) - 8;
      particle->m_Data.m_Point.m_Position.y =
          (((Vector3D *)spawnParam)->y >> 2) + (rand() & 15) - 8;
      particle->m_Data.m_Point.m_Position.z =
          (((Vector3D *)spawnParam)->z >> 2) + (rand() & 15) - 8;
      ((Vector3D16 *)&particle->m_Data.m_Raw[12])->x = 0;
      ((Vector3D16 *)&particle->m_Data.m_Raw[12])->y = 0;
      ((Vector3D16 *)&particle->m_Data.m_Raw[12])->z = 0;
      particle->m_Data.m_Point.m_OtOffset = 2;

      if (extraParam == 1 || (extraParam == 0 && g_Spyro.m_health >= 3)) {
        particle->m_Data.m_Point.m_Color.r = 255;
        particle->m_Data.m_Point.m_Color.g = 255;
        particle->m_Data.m_Point.m_Color.b = 0;
      } else {
        switch (rand() & 7) {
        case 0:
          particle->m_Data.m_Point.m_Color.r = 255;
          particle->m_Data.m_Point.m_Color.g = 0;
          particle->m_Data.m_Point.m_Color.b = 0;
          break;

        case 1:
          particle->m_Data.m_Point.m_Color.r = 255;
          particle->m_Data.m_Point.m_Color.g = 255;
          particle->m_Data.m_Point.m_Color.b = 0;
          break;

        case 2:
          particle->m_Data.m_Point.m_Color.r = 0;
          particle->m_Data.m_Point.m_Color.g = 255;
          particle->m_Data.m_Point.m_Color.b = 0;
          break;

        case 3:
          particle->m_Data.m_Point.m_Color.r = 0;
          particle->m_Data.m_Point.m_Color.g = 255;
          particle->m_Data.m_Point.m_Color.b = 255;
          break;

        case 4:
          particle->m_Data.m_Point.m_Color.r = 0;
          particle->m_Data.m_Point.m_Color.g = 0;
          particle->m_Data.m_Point.m_Color.b = 255;
          break;

        case 5:
          particle->m_Data.m_Point.m_Color.r = 255;
          particle->m_Data.m_Point.m_Color.g = 0;
          particle->m_Data.m_Point.m_Color.b = 255;
          break;

        case 6:
          particle->m_Data.m_Point.m_Color.r = 255;
          particle->m_Data.m_Point.m_Color.g = 128;
          particle->m_Data.m_Point.m_Color.b = 0;
          break;

        case 7:
          particle->m_Data.m_Point.m_Color.r = 0;
          particle->m_Data.m_Point.m_Color.g = 128;
          particle->m_Data.m_Point.m_Color.b = 255;
          break;
        }
      }

      // LineF2 Primitive Code
      particle->m_Data.m_Point.m_Color.s = PRIM_LINE_F2;
      break;
    }
#endif
#ifdef HAS_PARTICLE_69
    case 69: {
      particle = func_80053570(0);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 15;
      particle->m_WasRendered = 1;

      particle->m_Data.m_Point.m_Position.x =
          (((Vector3D *)spawnParam)->x >> 2) + (rand() & 15) - 8;
      particle->m_Data.m_Point.m_Position.y =
          (((Vector3D *)spawnParam)->y >> 2) + (rand() & 15) - 8;
      particle->m_Data.m_Point.m_Position.z =
          (((Vector3D *)spawnParam)->z >> 2) + (rand() & 15) - 8;

      *(PathData **)&particle->m_Data.m_Raw[20] = (PathData *)extraParam;
      *(int *)&particle->m_Data.m_Raw[24] = 0;
      particle->m_Data.m_Point.m_OtOffset = 2;

      switch (rand() & 7) {
      case 0:
        particle->m_Data.m_Point.m_Color.r = 255;
        particle->m_Data.m_Point.m_Color.g = 0;
        particle->m_Data.m_Point.m_Color.b = 0;
        break;

      case 1:
        particle->m_Data.m_Point.m_Color.r = 255;
        particle->m_Data.m_Point.m_Color.g = 255;
        particle->m_Data.m_Point.m_Color.b = 0;
        break;

      case 2:
        particle->m_Data.m_Point.m_Color.r = 0;
        particle->m_Data.m_Point.m_Color.g = 255;
        particle->m_Data.m_Point.m_Color.b = 0;
        break;

      case 3:
        particle->m_Data.m_Point.m_Color.r = 0;
        particle->m_Data.m_Point.m_Color.g = 255;
        particle->m_Data.m_Point.m_Color.b = 255;
        break;

      case 4:
        particle->m_Data.m_Point.m_Color.r = 0;
        particle->m_Data.m_Point.m_Color.g = 0;
        particle->m_Data.m_Point.m_Color.b = 255;
        break;

      case 5:
        particle->m_Data.m_Point.m_Color.r = 255;
        particle->m_Data.m_Point.m_Color.g = 0;
        particle->m_Data.m_Point.m_Color.b = 255;
        break;

      case 6:
        particle->m_Data.m_Point.m_Color.r = 255;
        particle->m_Data.m_Point.m_Color.g = 128;
        particle->m_Data.m_Point.m_Color.b = 0;
        break;

      case 7:
        particle->m_Data.m_Point.m_Color.r = 0;
        particle->m_Data.m_Point.m_Color.g = 128;
        particle->m_Data.m_Point.m_Color.b = 255;
        break;
      }

      particle->m_Data.m_Point.m_Color.s = PRIM_LINE_F2;
      break;
    }
#endif
#ifdef HAS_PARTICLE_70
    case 70: {
      Vector3D particleOffset;

      particle = func_80053570(1);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 15;
      particle->m_WasRendered = 1;

      particleOffset.x = (extraParam * ((rand() & 0xFFF) - 0x800)) >> 12;
      particleOffset.y = (extraParam * ((rand() & 0xFFF) - 0x800)) >> 12;
      particleOffset.z = (extraParam * (rand() & 0xFFF)) >> 12;

      particle->m_Data.m_Line.m_Position.x =
          (((Vector3D *)spawnParam)->x >> 2) + particleOffset.x * 4;
      particle->m_Data.m_Line.m_Position.y =
          (((Vector3D *)spawnParam)->y >> 2) + particleOffset.y * 4;
      particle->m_Data.m_Line.m_Position.z =
          (((Vector3D *)spawnParam)->z >> 2) + particleOffset.z * 4;

      particle->m_Data.m_Line.m_End.x =
          particle->m_Data.m_Line.m_Position.x + particleOffset.x * 2;
      particle->m_Data.m_Line.m_End.y =
          particle->m_Data.m_Line.m_Position.y + particleOffset.y * 2;
      particle->m_Data.m_Line.m_End.z =
          particle->m_Data.m_Line.m_Position.z + particleOffset.z * 2;

      particle->m_Data.m_Line.m_Color1.m_OtOffset = 2;

      particle->m_Data.m_Line.m_Color0.r = 224;
      particle->m_Data.m_Line.m_Color0.g = 192;
      particle->m_Data.m_Line.m_Color0.b = 0;

      particle->m_Data.m_Line.m_Color0.s = PRIM_LINE_G2;

      particle->m_Data.m_Line.m_Color1.r = 255;
      particle->m_Data.m_Line.m_Color1.g = 255;
      particle->m_Data.m_Line.m_Color1.b = 128;
      break;
    }
#endif
#ifdef HAS_PARTICLE_71
    case 71: {
      Vector3D particleOffset;

      particle = func_80053570(1);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 7;
      particle->m_WasRendered = 1;

      particleOffset.x = (((rand() & 0xFFF) - 0x800) * 0x10) >> 12;
      particleOffset.y = (((rand() & 0xFFF) - 0x800) * 0x10) >> 12;
      particleOffset.z = (((rand() & 0xFFF) - 0x800) * 0x10) >> 12;

      particle->m_Data.m_Line.m_Position.x =
          (((Vector3D *)spawnParam)->x >> 2) + particleOffset.x * 4;
      particle->m_Data.m_Line.m_Position.y =
          (((Vector3D *)spawnParam)->y >> 2) + particleOffset.y * 4;
      particle->m_Data.m_Line.m_Position.z =
          (((Vector3D *)spawnParam)->z >> 2) + particleOffset.z * 4;
      particle->m_Data.m_Line.m_End.x =
          particle->m_Data.m_Line.m_Position.x + particleOffset.x;
      particle->m_Data.m_Line.m_End.y =
          particle->m_Data.m_Line.m_Position.y + particleOffset.y;
      particle->m_Data.m_Line.m_End.z =
          particle->m_Data.m_Line.m_Position.z + particleOffset.z;
      particle->m_Data.m_Line.m_Color1.m_OtOffset = 2;

      particle->m_Data.m_Line.m_Color0.r = 224;
      particle->m_Data.m_Line.m_Color0.g = 224;
      particle->m_Data.m_Line.m_Color0.b = 96;

      particle->m_Data.m_Line.m_Color1.r = 255;
      particle->m_Data.m_Line.m_Color1.g = 255;
      particle->m_Data.m_Line.m_Color1.b = 255;

      particle->m_Data.m_Line.m_Color0.s = PRIM_LINE_G2;
      break;
    }
#endif
#ifdef HAS_PARTICLE_73
    case 73: {
      particle = func_80053570(0);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 15;
      particle->m_WasRendered = 1;

      particle->m_Data.m_Point.m_Position.x =
          (((Vector3D *)spawnParam)->x >> 2) + (rand() & 15) - 8;
      particle->m_Data.m_Point.m_Position.y =
          (((Vector3D *)spawnParam)->y >> 2) + (rand() & 15) - 8;
      particle->m_Data.m_Point.m_Position.z =
          (((Vector3D *)spawnParam)->z >> 2) + (rand() & 15) - 8;

      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x =
          particle->m_Data.m_Point.m_Position.x;
      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y =
          particle->m_Data.m_Point.m_Position.y;
      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z =
          particle->m_Data.m_Point.m_Position.z;
      particle->m_Data.m_Raw[26] = rand();
      particle->m_Data.m_Raw[27] = (rand() & 31) + 32;
      particle->m_Data.m_Point.m_OtOffset = 2;

      switch (rand() & 7) {
      case 0:
        particle->m_Data.m_Point.m_Color.r = 255;
        particle->m_Data.m_Point.m_Color.g = 0;
        particle->m_Data.m_Point.m_Color.b = 0;
        break;

      case 1:
        particle->m_Data.m_Point.m_Color.r = 255;
        particle->m_Data.m_Point.m_Color.g = 255;
        particle->m_Data.m_Point.m_Color.b = 0;
        break;

      case 2:
        particle->m_Data.m_Point.m_Color.r = 0;
        particle->m_Data.m_Point.m_Color.g = 255;
        particle->m_Data.m_Point.m_Color.b = 0;
        break;

      case 3:
        particle->m_Data.m_Point.m_Color.r = 0;
        particle->m_Data.m_Point.m_Color.g = 255;
        particle->m_Data.m_Point.m_Color.b = 255;
        break;

      case 4:
        particle->m_Data.m_Point.m_Color.r = 0;
        particle->m_Data.m_Point.m_Color.g = 0;
        particle->m_Data.m_Point.m_Color.b = 255;
        break;

      case 5:
        particle->m_Data.m_Point.m_Color.r = 255;
        particle->m_Data.m_Point.m_Color.g = 0;
        particle->m_Data.m_Point.m_Color.b = 255;
        break;

      case 6:
        particle->m_Data.m_Point.m_Color.r = 255;
        particle->m_Data.m_Point.m_Color.g = 128;
        particle->m_Data.m_Point.m_Color.b = 0;
        break;

      case 7:
        particle->m_Data.m_Point.m_Color.r = 0;
        particle->m_Data.m_Point.m_Color.g = 128;
        particle->m_Data.m_Point.m_Color.b = 255;
        break;
      }

      particle->m_Data.m_Point.m_Color.s = PRIM_LINE_F2;
      break;
    }
#endif
#ifdef HAS_PARTICLE_74
    case 74: {
      particle = func_80053570(0);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 15;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_Point.m_Position,
                           (Vector3D *)spawnParam);
      func_80017BFC((Vector3D16 *)&particle->m_Data.m_Raw[12],
                           (Vector3D *)extraParam);

      particle->m_Data.m_Point.m_Color.r = 255;
      particle->m_Data.m_Point.m_Color.g = 255;
      particle->m_Data.m_Point.m_Color.b = 0;

      particle->m_Data.m_Point.m_Color.s = PRIM_LINE_F2;

      particle->m_Data.m_Point.m_OtOffset = 4;
      break;
    }
#endif
#ifdef HAS_PARTICLE_75
    case 75: {
      particle = func_80053570(0);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 7;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_Point.m_Position,
                           (Vector3D *)spawnParam);

      particle->m_Data.m_Point.m_Position.x += (rand() & 0x3E) - 0x1F;
      particle->m_Data.m_Point.m_Position.y += (rand() & 0x3E) - 0x1F;
      particle->m_Data.m_Point.m_Position.z += (rand() & 0x3E) - 0x1F;

      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x = 0;
      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y = 0;
      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z = 0;

      particle->m_Data.m_Point.m_Color.r = 255;
      particle->m_Data.m_Point.m_Color.g = 255;
      particle->m_Data.m_Point.m_Color.b = 255;
      particle->m_Data.m_Point.m_Color.s = PRIM_LINE_F2;
      particle->m_Data.m_Point.m_OtOffset = 4;
      break;
    }
#endif
#ifdef HAS_PARTICLE_76
    case 76: {
      particle = func_80053570(0);
      particle->m_Class = pClass;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_Point.m_Position,
                           (Vector3D *)spawnParam);
      func_80017BFC((Vector3D16 *)&particle->m_Data.m_Raw[12],
                           (Vector3D *)spawnParam);

      if ((extraParam & 0x1F) < 0x10) {
        particle->m_Data.m_Raw[20] = extraParam * 2;
      } else {
        particle->m_Data.m_Raw[20] = extraParam * 2 - 0x80;
      }

      particle->m_Data.m_Raw[21] = 8;

      particle->m_Data.m_Point.m_Color.r = ~((extraParam & 15) * 16);
      particle->m_Data.m_Point.m_Color.g = 255;
      particle->m_Data.m_Point.m_Color.b = 128 - ((extraParam & 15) * 8);

      particle->m_Data.m_Point.m_Color.s = PRIM_LINE_F2;
      particle->m_Data.m_Point.m_OtOffset = 2;
      break;
    }
#endif
#ifdef HAS_PARTICLE_77
    case 77: {
      int angle;

      particle = func_80053570(4);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 15;
      func_80017BFC(&particle->m_Data.m_Line.m_End, (Vector3D *)spawnParam);
      func_80017BFC(&particle->m_Data.m_Line.m_Position,
                           (Vector3D *)spawnParam);

      angle = rand() & 0xFFF;

      particle->m_Data.m_Line.m_Position.x += Cos(angle) >> 8;
      particle->m_Data.m_Line.m_Position.y += Sin(rand() & 0x7FF) >> 8;
      particle->m_Data.m_Line.m_Position.z += Sin(angle) >> 8;
      particle->m_Data.m_Line.m_Color1.m_OtOffset = 0x7F;

      particle->m_Data.m_Line.m_Color0.r = 128;
      particle->m_Data.m_Line.m_Color0.g = 64;
      particle->m_Data.m_Line.m_Color0.b = 96;

      particle->m_Data.m_Line.m_Color1.r = 255;
      particle->m_Data.m_Line.m_Color1.g = 128;
      particle->m_Data.m_Line.m_Color1.b = 192;

      particle->m_Data.m_Line.m_Color0.s = PRIM_LINE_G2;
      break;
    }
#endif
#ifdef HAS_PARTICLE_78
    case 78: {
      particle = func_80053570(0);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 0x1F;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_Point.m_Position,
                           (Vector3D *)spawnParam);

      particle->m_Data.m_Point.m_Position.x += (rand() & 63) - 32;
      particle->m_Data.m_Point.m_Position.y += (rand() & 63) - 32;
      particle->m_Data.m_Point.m_Position.z += (rand() & 63) - 32;
      ((Vector3D16 *)&particle->m_Data.m_Raw[12])->x = (rand() & 2) - 1;
      ((Vector3D16 *)&particle->m_Data.m_Raw[12])->y = (rand() & 2) - 1;
      ((Vector3D16 *)&particle->m_Data.m_Raw[12])->z = -(rand() & 1);

      particle->m_Data.m_Point.m_Color.r = 128 | rand();
      particle->m_Data.m_Point.m_Color.g = (rand() & 127) + 96;

      if (particle->m_Data.m_Point.m_Color.r <
          particle->m_Data.m_Point.m_Color.g) {
        particle->m_Data.m_Point.m_Color.g = particle->m_Data.m_Point.m_Color.r;
      }

      particle->m_Data.m_Point.m_Color.b = (rand() & 63) + 64;
      particle->m_Data.m_Point.m_Color.s = PRIM_LINE_F2;
      particle->m_Data.m_Point.m_OtOffset = 2;
      break;
    }
#endif
#ifdef HAS_PARTICLE_79
    case 79: {
      Vector3D particleOffset;
      particle = func_80053570(1);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 15;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_Line.m_End, (Vector3D *)spawnParam);
      VecAdd(&particleOffset, (Vector3D *)spawnParam, (Vector3D *)extraParam);

      particleOffset.x += (rand() & 63) - 32;
      particleOffset.y += (rand() & 63) - 32;
      particleOffset.z += (rand() & 127) - 64;

      func_80017BFC(&particle->m_Data.m_Line.m_Position,
                           &particleOffset);
      particle->m_Data.m_Line.m_Color1.m_OtOffset = 2;

      if (g_SpyroFlame.unk_9c == 0) {
        particle->m_Data.m_Line.m_Color0.r = rand();
        particle->m_Data.m_Line.m_Color0.r |= 192;
        particle->m_Data.m_Line.m_Color0.g = (rand() & 63) - 96;
        particle->m_Data.m_Line.m_Color0.b = 0;
        particle->m_Data.m_Line.m_Color1.r = rand();
        particle->m_Data.m_Line.m_Color1.r |= 224;
        particle->m_Data.m_Line.m_Color1.g = rand();
        particle->m_Data.m_Line.m_Color1.g |= 224;
        particle->m_Data.m_Line.m_Color1.b = 128;
      } else {
        particle->m_Data.m_Line.m_Color0.r = rand();
        particle->m_Data.m_Line.m_Color0.r |= 192;
        particle->m_Data.m_Line.m_Color0.g = (rand() & 63) + 64;
        particle->m_Data.m_Line.m_Color0.b = (rand() & 63) + 64;
        particle->m_Data.m_Line.m_Color1.r = rand();
        particle->m_Data.m_Line.m_Color1.r |= 224;
        particle->m_Data.m_Line.m_Color1.g = (rand() & 31) - 96;
        particle->m_Data.m_Line.m_Color1.b = (rand() & 31) - 96;
      }

      particle->m_Data.m_Line.m_Color0.s = PRIM_LINE_G2;
      break;
    }
#endif
#ifdef HAS_PARTICLE_80
    case 80: {
      Vector3D particleOffset;

      particle = func_80053570(1);
      particle->m_Class = pClass;
      particle->m_Timer = rand() & 15;
      particle->m_WasRendered = 1;
      func_80017BFC(&particle->m_Data.m_Line.m_Position,
                           (Vector3D *)spawnParam);

      particleOffset.x = (extraParam * ((rand() & 0xFFF) - 0x800)) >> 12;
      particleOffset.y = (extraParam * ((rand() & 0xFFF) - 0x800)) >> 12;
      particleOffset.z = (extraParam * (rand() & 0xFFF)) >> 12;

      particle->m_Data.m_Line.m_Position.x += particleOffset.x * 4;
      particle->m_Data.m_Line.m_Position.y += particleOffset.y * 4;
      particle->m_Data.m_Line.m_Position.z += particleOffset.z * 4;

      particle->m_Data.m_Line.m_End.x =
          particle->m_Data.m_Line.m_Position.x + particleOffset.x * 2;
      particle->m_Data.m_Line.m_End.y =
          particle->m_Data.m_Line.m_Position.y + particleOffset.y * 2;
      particle->m_Data.m_Line.m_End.z =
          particle->m_Data.m_Line.m_Position.z + particleOffset.z * 2;

      particle->m_Data.m_Line.m_Color1.m_OtOffset = 2;

      particle->m_Data.m_Line.m_Color0.r = 224;
      particle->m_Data.m_Line.m_Color0.g = 192;
      particle->m_Data.m_Line.m_Color0.b = 0;

      particle->m_Data.m_Line.m_Color0.s = PRIM_LINE_G2;

      particle->m_Data.m_Line.m_Color1.r = 255;
      particle->m_Data.m_Line.m_Color1.g = 255;
      particle->m_Data.m_Line.m_Color1.b = 128;
      break;
    }
#endif
    }
  }
}
