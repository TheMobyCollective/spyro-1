#include "camera.h"
#include "dragon.h"
#include "graphics.h"
#include "math.h"
#include "overlay_pointers.h"
#include "renderers.h"
#include "spyro.h"
#include "vector.h"


// TODO:
// -Determine how to handle m_Raw access. Dedicated structs per class?

void NAME_OVERLAY_FUNCTION(UpdateParticle)(int pDelta) {
  Particle *particle;

  for (particle = g_Particles; particle->m_RenderType != 0xFF; particle++) {
    switch (particle->m_Class) {
#ifdef HAS_PARTICLE_0
    case 0:
      func_80017C84(&particle->m_Data.m_RotatedQuad.m_Position,
                  &particle->m_Data.m_RotatedQuad.m_Position,
                  (Vector3D16 *)&particle->m_Data.m_Raw[20]);

      if (*(short *)&particle->m_Data.m_Raw[26] != 0) {
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z++;
      }

      *(short *)&particle->m_Data.m_Raw[26] =
          1 - *(short *)&particle->m_Data.m_Raw[26];
      particle->m_Data.m_RotatedQuad.m_Size += pDelta * 2;
      particle->m_Data.m_RotatedQuad.m_Color.r -= pDelta * 4;
      particle->m_Data.m_RotatedQuad.m_Color.g -= pDelta * 4;
      particle->m_Data.m_RotatedQuad.m_Color.b -= pDelta * 4;
      particle->m_Timer += pDelta;

      if (particle->m_Timer >= 32 || !particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
#endif
#ifdef HAS_PARTICLE_1
    case 1:
      func_80017C84(&particle->m_Data.m_RotatedQuad.m_Position,
                  &particle->m_Data.m_RotatedQuad.m_Position,
                  (Vector3D16 *)&particle->m_Data.m_Raw[20]);

      if (*(short *)&particle->m_Data.m_Raw[26] != 0) {
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z++;
      }

      *(short *)&particle->m_Data.m_Raw[26] =
          1 - *(short *)&particle->m_Data.m_Raw[26];
      particle->m_Data.m_RotatedQuad.m_Size += pDelta * 4;
      particle->m_Data.m_RotatedQuad.m_Color.r -= pDelta * 4;
      particle->m_Data.m_RotatedQuad.m_Color.g -= pDelta * 4;
      particle->m_Data.m_RotatedQuad.m_Color.b -= pDelta * 4;
      particle->m_Timer += pDelta;

      if (particle->m_Timer >= 24 || !particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
#endif
#ifdef HAS_PARTICLE_2
    case 2:
      func_80017C84(&particle->m_Data.m_RotatedQuad.m_Position,
                  &particle->m_Data.m_RotatedQuad.m_Position,
                  (Vector3D16 *)&particle->m_Data.m_Raw[20]);

      if (*(short *)&particle->m_Data.m_Raw[26] != 0) {
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z++;
      }

      *(short *)&particle->m_Data.m_Raw[26] =
          1 - *(short *)&particle->m_Data.m_Raw[26];
      particle->m_Data.m_RotatedQuad.m_Size += pDelta * 4;
      particle->m_Data.m_RotatedQuad.m_Color.r -= pDelta * 4;
      particle->m_Data.m_RotatedQuad.m_Color.g -= pDelta * 4;
      particle->m_Data.m_RotatedQuad.m_Color.b -= pDelta * 4;
      particle->m_Timer += pDelta;

      if (particle->m_Timer >= 0x20 || !particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
#endif
#ifdef HAS_PARTICLE_4
    case 4: {
      Vector3D position;
      Vector3D delta;
      int value;

      if (particle->m_RenderType == 3) {
        func_80017C24(&position, &particle->m_Data.m_Quad.m_Position);
      } else {
        func_80017C24(&position, &particle->m_Data.m_Point.m_Position);
      }

      if (*(short *)&particle->m_Data.m_Raw[26] & 8) {
        if (particle->m_Timer >= 48) {
          func_80053608(particle);
          break;
        }

        *(short *)&particle->m_Data.m_Raw[20] += (rand() & 6) - 3;
        *(short *)&particle->m_Data.m_Raw[22] += (rand() & 6) - 3;
        (*(short *)&particle->m_Data.m_Raw[24])++;

        if (*(short *)&particle->m_Data.m_Raw[24] > 16) {
          *(short *)&particle->m_Data.m_Raw[24] = 16;
        }

        position.x += *(short *)&particle->m_Data.m_Raw[20];
        position.y += *(short *)&particle->m_Data.m_Raw[22];
        position.z -= *(short *)&particle->m_Data.m_Raw[24];

        if (particle->m_RenderType == 3) {
          func_80017BFC(&particle->m_Data.m_Quad.m_Position, &position);
        } else {
          func_80017BFC(&particle->m_Data.m_Point.m_Position, &position);
        }
        particle->m_Timer++;
      } else if (*(short *)&particle->m_Data.m_Raw[26] & 1) {
        if (particle->m_Timer >= 48) {
          particle->m_Timer = 0;
          *(short *)&particle->m_Data.m_Raw[20] = (rand() & 6) - 3;
          *(short *)&particle->m_Data.m_Raw[22] = (rand() & 6) - 3;
          *(short *)&particle->m_Data.m_Raw[24] = 0;
          *(short *)&particle->m_Data.m_Raw[26] = 8;
        } else {
          func_80017C24(&delta,
                               (Vector3D16 *)&particle->m_Data.m_Raw[20]);

          if (*(short *)&particle->m_Data.m_Raw[26] & 2) {
            delta.x += (particle->m_Timer * Cos(particle->m_Timer << 7)) >> 7;
          } else {
            delta.x -= (particle->m_Timer * Cos(particle->m_Timer << 7)) >> 7;
          }

          if (*(short *)&particle->m_Data.m_Raw[26] & 4) {
            delta.y += (particle->m_Timer * Sin(particle->m_Timer << 7)) >> 7;
          } else {
            delta.y -= (particle->m_Timer * Sin(particle->m_Timer << 7)) >> 7;
          }

          delta.z += particle->m_Timer << 5;

          VecSub(&delta, &delta, &position);
          value = VecMagnitude(&delta, 1);

          if (value > 0x80) {
            VecScaleToLength(&delta, value, 0x80);
          }

          VecAdd(&position, &position, &delta);

          if (particle->m_RenderType == 3) {
            func_80017BFC(&particle->m_Data.m_Quad.m_Position,
                                 &position);
          } else {
            func_80017BFC(&particle->m_Data.m_Point.m_Position,
                                 &position);
          }
          particle->m_Timer++;
        }
      } else {
        VecCopy(&delta, &(*(Moby **)&particle->m_Data.m_Raw[20])->m_Position);

        delta.x += Cos(particle->m_Timer << 7) >> 2;
        delta.y += Sin(particle->m_Timer << 7) >> 2;
        delta.z += Cos((particle->m_Timer * 128) + 512) >> 2;

        VecSub(&delta, &delta, &position);
        value = VecMagnitude(&delta, 1);

        if (value <= 0x400 || particle->m_Timer >= 65) {
          // TODO: Type props struct
          int *props;

          props = (*(Moby **)&particle->m_Data.m_Raw[20])->m_Props;

          if (props[5] == 1) {
            props[5] = 2;
            props[0] = 0x20;
          }

          *(short *)&particle->m_Data.m_Raw[26] = (rand() & 6) + 1;
          func_80017BFC(
              (Vector3D16 *)&particle->m_Data.m_Raw[20],
              &(*(Moby **)&particle->m_Data.m_Raw[20])->m_Position);
          *(short *)&particle->m_Data.m_Raw[24] += rand() & 127;
          particle->m_Timer = 0;
        } else {
          VecScaleToLength(&delta, value, 0x100);
          VecAdd(&position, &position, &delta);

          if (particle->m_RenderType == 3) {
            func_80017BFC(&particle->m_Data.m_Quad.m_Position,
                                 &position);
          } else {
            func_80017BFC(&particle->m_Data.m_Point.m_Position,
                                 &position);
          }
          particle->m_Timer++;
        }
      }

      VecSub(&delta, &position, &g_Camera.m_Position);
      value = ABS2(delta.x) + ABS2(delta.y) + ABS2(delta.z);

      if (particle->m_RenderType == 3) {
        if (value > 0x3000) {
          particle->m_Data.m_Point.m_Color.r = 255;
          particle->m_Data.m_Point.m_Color.g = 255;
          particle->m_Data.m_Point.m_Color.b = 255;
          particle->m_Data.m_Point.m_OtOffset = 4;
          particle->m_RenderType = 0;
          particle->m_Data.m_Point.m_Color.s = PRIM_LINE_F2;
        }
      } else if (value < 0x2800) {
        particle->m_RenderType = 3;
        particle->m_Data.m_Quad.m_Color.r = 128;
        particle->m_Data.m_Quad.m_Color.g = 128;
        particle->m_Data.m_Quad.m_Color.b = 128;
        particle->m_Data.m_Quad.m_OtOffset = 4;
        particle->m_Data.m_Quad.m_Color.s = PRIM_POLY_FT4;
        particle->m_Data.m_Quad.m_TextureIndex = 0;
        particle->m_Data.m_Quad.m_Width = (rand() & 15) + 24;
        particle->m_Data.m_Quad.m_Height = (rand() & 7) + 15;
      }

      break;
    }
#endif
#ifdef HAS_PARTICLE_5
    case 5: {
      Vector3D position;
      Vector3D velocity;

      if (particle->m_Timer < 48 && particle->m_WasRendered) {
        func_80017C24(&position, &particle->m_Data.m_Quad.m_Position);

        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x += (rand() & 6) - 3;
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y += (rand() & 6) - 3;
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z -= 1;

        func_80017C24(&velocity,
                             (Vector3D16 *)&particle->m_Data.m_Raw[20]);
        VecShiftRight(&velocity, 2);
        VecAdd(&position, &position, &velocity);
        func_80017BFC(&particle->m_Data.m_Quad.m_Position, &position);

        particle->m_Timer++;
      } else {
        func_80053608(particle);
      }
      break;
    }
#endif
#ifdef HAS_PARTICLE_6
    case 6: {
      Vector3D position;
      int angle;
      int radius;
      int maxHeight;

      VecCopy(&position, *(Vector3D **)&particle->m_Data.m_Raw[20]);

      maxHeight = position.z + (*(short *)&particle->m_Data.m_Raw[26] << 6);
      angle = particle->m_Timer << 6;
      radius = particle->m_Timer << 6;
      if (*(short *)&particle->m_Data.m_Raw[24] < radius) {
        radius = *(short *)&particle->m_Data.m_Raw[24];
      }

      position.x += (radius * Cos(angle)) >> 12;
      position.y += (radius * Sin(angle)) >> 12;
      position.z = (particle->m_Data.m_Quad.m_Position.z << 2) + 0x40;

      if (maxHeight < position.z || particle->m_Timer >= 201) {
        func_80053608(particle);
      } else {
        func_80017BFC(&particle->m_Data.m_Quad.m_Position, &position);
        particle->m_Timer++;
      }
      break;
    }
#endif
#ifdef HAS_PARTICLE_7
    case 7: {
      if (particle->m_Timer > 24 || !particle->m_WasRendered) {
        func_80053608(particle);
      } else {
        particle->m_Data.m_RotatedQuad.m_Rotation += particle->m_Data.m_Raw[26];
        if (particle->m_Timer > 12) {
          particle->m_Data.m_RotatedQuad.m_Size = (24 - particle->m_Timer) << 2;
        } else {
          particle->m_Data.m_RotatedQuad.m_Size = particle->m_Timer << 2;
        }

        particle->m_Data.m_RotatedQuad.m_Position.x +=
            ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x;
        particle->m_Data.m_RotatedQuad.m_Position.y +=
            ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y;
        particle->m_Data.m_RotatedQuad.m_Position.z +=
            ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z;
        particle->m_Timer++;
      }
      break;
    }
#endif
#ifdef HAS_PARTICLE_8
    case 8: {
      Vector3D position;
      Vector3D delta;
      int value;
      int red;
      int green;
      int blue;

      if (particle->m_RenderType == 3) {
        func_80017C24(&position, &particle->m_Data.m_Quad.m_Position);
      } else {
        func_80017C24(&position, &particle->m_Data.m_Point.m_Position);
      }

      if (!particle->m_WasRendered) {
        func_80053608(particle);
        break;
      }

      VecCopy(&delta, &g_LevelMobys[particle->m_Data.m_Raw[26]].m_Position);

      delta.x += Cos(particle->m_Timer << 7) >> 1;
      delta.y += Sin(particle->m_Timer << 7) >> 1;
      delta.z += Cos((particle->m_Timer << 7) - 0x100) >> 2;

      VecSub(&delta, &delta, &position);
      value = VecMagnitude(&delta, 1);

      if (value > 0x400 && particle->m_Timer < 65) {
        VecScaleToLength(&delta, value, 0x80);
        VecAdd(&position, &position, &delta);

        if (particle->m_RenderType == 3) {
          func_80017BFC(&particle->m_Data.m_Quad.m_Position, &position);
        } else {
          func_80017BFC(&particle->m_Data.m_Point.m_Position, &position);
        }

        particle->m_Timer++;

        VecSub(&delta, &position, &g_Camera.m_Position);
        value = ABS2(delta.x) + ABS2(delta.y) + ABS2(delta.z);

        if (particle->m_RenderType == 3) {
          if (value > 0x3000) {
            particle->m_Data.m_Point.m_OtOffset = 4;
            particle->m_Data.m_Point.m_Color.s = PRIM_LINE_F2;
            particle->m_RenderType = 0;

            red = particle->m_Data.m_Point.m_Color.r << 1;
            green = particle->m_Data.m_Point.m_Color.g << 1;
            blue = particle->m_Data.m_Point.m_Color.b << 1;

            particle->m_Data.m_Point.m_Color.r = red;
            particle->m_Data.m_Point.m_Color.g = green;
            particle->m_Data.m_Point.m_Color.b = blue;
          }
        } else if (value < 0x2800) {
          particle->m_RenderType = 3;
          particle->m_Data.m_Quad.m_OtOffset = 4;
          particle->m_Data.m_Quad.m_Color.s = PRIM_POLY_FT4;
          particle->m_Data.m_Quad.m_TextureIndex = 0;

          red = particle->m_Data.m_Quad.m_Color.r >> 1;
          green = particle->m_Data.m_Quad.m_Color.g >> 1;
          blue = particle->m_Data.m_Quad.m_Color.b >> 1;

          particle->m_Data.m_Quad.m_Color.r = red;
          particle->m_Data.m_Quad.m_Color.g = green;
          particle->m_Data.m_Quad.m_Color.b = blue;

          particle->m_Data.m_Quad.m_Width = (rand() & 15) + 24;
          particle->m_Data.m_Quad.m_Height = (rand() & 7) + 15;
        }

      } else {
        func_80053608(particle);
      }

      break;
    }
#endif
#ifdef HAS_PARTICLE_9
    case 9:
      func_80017C84(&particle->m_Data.m_RotatedQuad.m_Position,
                  &particle->m_Data.m_RotatedQuad.m_Position,
                  (Vector3D16 *)&particle->m_Data.m_Raw[20]);

      if (*(short *)&particle->m_Data.m_Raw[26] != 0) {
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z++;
      }

      *(short *)&particle->m_Data.m_Raw[26] =
          1 - *(short *)&particle->m_Data.m_Raw[26];
      particle->m_Data.m_RotatedQuad.m_Size += pDelta * 2;
      particle->m_Timer += pDelta;

      if (particle->m_Timer >= 32 || !particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
#endif
#ifdef HAS_PARTICLE_10
    case 10: {
      int value;
      Vector3D position;

      if (g_Spyro.m_State == 0x1D && g_Spyro.m_health < 0) {
        func_80053608(particle);
        break;
      }

      if (g_IsSpyroHidden || g_Spyro.m_invulverabilityTimer <= 0) {
        func_80053608(particle);
        break;
      }

      VecCopy(&position, &g_Spyro.m_Position);
      position.x += Cos(*(short *)&particle->m_Data.m_Raw[20]) >> 4;
      position.y += Sin(*(short *)&particle->m_Data.m_Raw[20]) >> 4;
      position.z += 0x100;
      func_80017BFC(&particle->m_Data.m_Quad.m_Position, &position);

      *(short *)&particle->m_Data.m_Raw[20] += 0x40;

      value =
          Cos((*(short *)&particle->m_Data.m_Raw[20] - g_Camera.m_Rotation.z) &
              0xFFF);
      particle->m_Data.m_Quad.m_Width = ABS2(value) / 170;
      break;
    }
#endif
#ifdef HAS_PARTICLE_11
    case 11: {
      // This particle is spawned by func_800530C0
      Vector3D16 *velocity = (Vector3D16 *)&particle->m_Data.m_Raw[14];
      func_80017C84(&particle->m_Data.m_RotatedQuad.m_Position,
                  &particle->m_Data.m_RotatedQuad.m_Position, velocity);
      particle->m_Data.m_RotatedQuad.m_Color.r -= 8;
      particle->m_Data.m_RotatedQuad.m_Color.g -= 8;
      particle->m_Data.m_RotatedQuad.m_Color.b -= 8;

      if (particle->m_Data.m_RotatedQuad.m_Color.r == 0 ||
          !particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
    }
#endif
#ifdef HAS_PARTICLE_12
    case 12:
      particle->m_Data.m_RotatedQuad.m_Rotation += 8;
      particle->m_Data.m_RotatedQuad.m_Size += 2;

      if (particle->m_Data.m_RotatedQuad.m_Color.r != 0) {
        particle->m_Data.m_RotatedQuad.m_Color.r -= 8;
      }

      if (particle->m_Data.m_RotatedQuad.m_Color.g != 0) {
        particle->m_Data.m_RotatedQuad.m_Color.g -= 8;
      }

      if (particle->m_Data.m_RotatedQuad.m_Color.b != 0) {
        particle->m_Data.m_RotatedQuad.m_Color.b -= 8;
      }

      if ((*(u_int *)&particle->m_Data.m_RotatedQuad.m_Color.r & 0x00FFFFFF) ==
              0 ||
          !particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
#endif
#ifdef HAS_PARTICLE_13
    case 13: {
      int colorValue;

      if (particle->m_Timer >= 0x1C || !particle->m_WasRendered) {
        func_80053608(particle);
        break;
      }

      func_80017C84(&particle->m_Data.m_RotatedQuad.m_Position,
                  &particle->m_Data.m_RotatedQuad.m_Position,
                  (Vector3D16 *)&particle->m_Data.m_Raw[20]);

      if (*(short *)&particle->m_Data.m_Raw[26] != 0) {
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z++;
      }

      *(short *)&particle->m_Data.m_Raw[26] =
          1 - *(short *)&particle->m_Data.m_Raw[26];
      particle->m_Data.m_RotatedQuad.m_Size += pDelta * 2;

      if (particle->m_Timer >= 13) {
        colorValue = 128 - ((particle->m_Timer - 12) * 8);
        if (colorValue < 0) {
          colorValue = 0;
        }

        particle->m_Data.m_RotatedQuad.m_Color.r = colorValue;

        colorValue = 64 - ((particle->m_Timer - 12) * 4);
        if (colorValue < 0) {
          colorValue = 0;
        }

        particle->m_Data.m_RotatedQuad.m_Color.g = colorValue;
        particle->m_Data.m_RotatedQuad.m_Color.b = 0;
      } else if (particle->m_Timer >= 5) {
        particle->m_Data.m_RotatedQuad.m_Color.r = 128;
        particle->m_Data.m_RotatedQuad.m_Color.g =
            -128 - ((particle->m_Timer - 4) << 3);
        particle->m_Data.m_RotatedQuad.m_Color.b = 0;
      } else {
        particle->m_Data.m_RotatedQuad.m_Color.r = 128;
        particle->m_Data.m_RotatedQuad.m_Color.g = 128;

        colorValue = 128 - (particle->m_Timer << 5);
        if (colorValue < 0) {
          colorValue = 0;
        }

        particle->m_Data.m_RotatedQuad.m_Color.b = colorValue;
      }

      particle->m_Timer += pDelta;
      break;
    }
#endif
#ifdef HAS_PARTICLE_14
    case 14: {
      int value;
      func_80017C84(&particle->m_Data.m_RotatedQuad.m_Position,
                  &particle->m_Data.m_RotatedQuad.m_Position,
                  (Vector3D16 *)&particle->m_Data.m_Raw[20]);

      if (((Vector3D16 *)&particle->m_Data.m_Raw[20])->x > 0) {
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x--;
      } else if (((Vector3D16 *)&particle->m_Data.m_Raw[20])->x < 0) {
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x++;
      }

      if (((Vector3D16 *)&particle->m_Data.m_Raw[20])->y > 0) {
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y--;
      } else if (((Vector3D16 *)&particle->m_Data.m_Raw[20])->y < 0) {
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y++;
      }

      if (*(short *)&particle->m_Data.m_Raw[26] != 0) {
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z++;
      }

      *(short *)&particle->m_Data.m_Raw[26] =
          1 - *(short *)&particle->m_Data.m_Raw[26];

      value = particle->m_Data.m_RotatedQuad.m_Size + pDelta * 2;
      if (value >= 0x100) {
        value = 0xFF;
      }
      particle->m_Data.m_RotatedQuad.m_Size = value;

      value = particle->m_Data.m_RotatedQuad.m_Color.r - pDelta;
      if (value <= 0) {
        func_80053608(particle);
        break;
      }

      particle->m_Data.m_RotatedQuad.m_Color.r = value;
      particle->m_Data.m_RotatedQuad.m_Color.g = value;
      particle->m_Data.m_RotatedQuad.m_Color.b = value;

      particle->m_Timer += pDelta;

      if (particle->m_Timer >= 0x80 || !particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
    }
#endif
#ifdef HAS_PARTICLE_15
    case 15: {
      Vector3D position;
      Vector3D velocity;

      if (particle->m_Timer >= 48 || !particle->m_WasRendered) {
        func_80053608(particle);
        break;
      }

      func_80017C24(&position, &particle->m_Data.m_Quad.m_Position);

      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x += (rand() & 6) - 3;
      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y += (rand() & 6) - 3;
      ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z -= 1;

      func_80017C4C(&velocity, (Vector3D16 *)&particle->m_Data.m_Raw[20]);
      VecAdd(&position, &position, &velocity);
      func_80017BFC(&particle->m_Data.m_Quad.m_Position, &position);

      particle->m_Timer++;
      break;
    }
#endif
#ifdef HAS_PARTICLE_16
    case 16:
      func_80017C84(&particle->m_Data.m_RotatedQuad.m_Position,
                  &particle->m_Data.m_RotatedQuad.m_Position,
                  (Vector3D16 *)&particle->m_Data.m_Raw[20]);

      if (*(short *)&particle->m_Data.m_Raw[26] != 0) {
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z++;
      }

      *(short *)&particle->m_Data.m_Raw[26] =
          1 - *(short *)&particle->m_Data.m_Raw[26];
      particle->m_Data.m_RotatedQuad.m_Size += pDelta * 2;
      particle->m_Data.m_RotatedQuad.m_Color.r -= 4;
      particle->m_Data.m_RotatedQuad.m_Color.g -= 4;
      particle->m_Data.m_RotatedQuad.m_Color.b -= 4;

      if (particle->m_Data.m_RotatedQuad.m_Color.r == 0 ||
          !particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
#endif
#ifdef HAS_PARTICLE_17
    case 17:
      func_80017C84(&particle->m_Data.m_RotatedQuad.m_Position,
                  &particle->m_Data.m_RotatedQuad.m_Position,
                  (Vector3D16 *)&particle->m_Data.m_Raw[20]);

      if (*(short *)&particle->m_Data.m_Raw[26] != 0) {
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z++;
      }

      *(short *)&particle->m_Data.m_Raw[26] =
          1 - *(short *)&particle->m_Data.m_Raw[26];
      particle->m_Data.m_RotatedQuad.m_Size += pDelta * 2;

      if (particle->m_Timer >= 9) {
        particle->m_Data.m_RotatedQuad.m_Color.r -= 32;
      }

      particle->m_Data.m_RotatedQuad.m_Color.g -= 8;
      particle->m_Data.m_RotatedQuad.m_Color.b -= 4;
      particle->m_Timer++;

      if (particle->m_Timer >= 0x0C || !particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
#endif
#ifdef HAS_PARTICLE_19
    case 19: {
      int value;
      particle->m_Data.m_RotatedQuad.m_Position.z +=
          *(int *)&particle->m_Data.m_Raw[20];

      *(int *)&particle->m_Data.m_Raw[20] -= 2;
      if (*(int *)&particle->m_Data.m_Raw[20] < 0) {
        *(int *)&particle->m_Data.m_Raw[20] = 0;
      }

      value = particle->m_Data.m_RotatedQuad.m_Size + pDelta * 3;
      if (value >= 256) {
        value = 255;
      }
      particle->m_Data.m_RotatedQuad.m_Size = value;

      value = particle->m_Data.m_RotatedQuad.m_Color.r - pDelta * 2;
      if (value <= 0) {
        func_80053608(particle);
        break;
      }

      particle->m_Data.m_RotatedQuad.m_Color.r = value;
      particle->m_Data.m_RotatedQuad.m_Color.g = value;
      particle->m_Data.m_RotatedQuad.m_Color.b = value;

      particle->m_Timer += pDelta;

      if (particle->m_Timer >= 128 || !particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
    }
#endif
#ifdef HAS_PARTICLE_21
    case 21:
      particle->m_Data.m_Raw[20] += g_DeltaTime * 4;
      particle->m_Data.m_Raw[21] += g_DeltaTime;

      particle->m_Data.m_RotatedQuad.m_Position.x =
          ((Vector3D16 *)&particle->m_Data.m_Raw[14])->x +
          ((COSINE_8(particle->m_Data.m_Raw[20]) *
            particle->m_Data.m_Raw[21]) >>
           12);
      particle->m_Data.m_RotatedQuad.m_Position.y =
          ((Vector3D16 *)&particle->m_Data.m_Raw[14])->y +
          ((SINE_8(particle->m_Data.m_Raw[20]) * particle->m_Data.m_Raw[21]) >>
           12);
      particle->m_Data.m_RotatedQuad.m_Position.z += g_DeltaTime * 6;

      particle->m_Data.m_RotatedQuad.m_Rotation += 4;

      if (particle->m_Data.m_Raw[21] >= 0xC1) {
        func_80053608(particle);
      }
      break;
#endif
#ifdef HAS_PARTICLE_22
    case 22: {
      int value;

      func_80017C84(&particle->m_Data.m_RotatedQuad.m_Position,
                  &particle->m_Data.m_RotatedQuad.m_Position,
                  (Vector3D16 *)&particle->m_Data.m_Raw[20]);

      if (((Vector3D16 *)&particle->m_Data.m_Raw[20])->x > 0) {
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x--;
      } else if (((Vector3D16 *)&particle->m_Data.m_Raw[20])->x < 0) {
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x++;
      }

      if (((Vector3D16 *)&particle->m_Data.m_Raw[20])->y > 0) {
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y--;
      } else if (((Vector3D16 *)&particle->m_Data.m_Raw[20])->y < 0) {
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y++;
      }

      particle->m_Data.m_RotatedQuad.m_Rotation += particle->m_Data.m_Raw[26];

      value = particle->m_Data.m_RotatedQuad.m_Color.b - g_DeltaTime;
      if (value <= 0) {
        func_80053608(particle);
        break;
      }

      particle->m_Data.m_RotatedQuad.m_Color.r = value >> 1;
      particle->m_Data.m_RotatedQuad.m_Color.g = value >> 1;
      particle->m_Data.m_RotatedQuad.m_Color.b = value;

      particle->m_Timer += pDelta;

      if (particle->m_Timer >= 0x40 || !particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
    }

#endif
#ifdef HAS_PARTICLE_23
    case 23:
      func_80017C84(&particle->m_Data.m_RotatedQuad.m_Position,
                  &particle->m_Data.m_RotatedQuad.m_Position,
                  (Vector3D16 *)&particle->m_Data.m_Raw[20]);

      particle->m_Data.m_RotatedQuad.m_Rotation += particle->m_Data.m_Raw[26];
      particle->m_Data.m_RotatedQuad.m_Size += pDelta * 2;

      particle->m_Data.m_RotatedQuad.m_Color.r -= pDelta * 2;
      particle->m_Data.m_RotatedQuad.m_Color.g -= pDelta * 2;
      particle->m_Data.m_RotatedQuad.m_Color.b -= pDelta * 2;

      particle->m_Timer += pDelta;

      if (particle->m_Timer >= 48 || !particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
#endif
#ifdef HAS_PARTICLE_24
    case 24: {
      int cutsceneProgress;

      if (particle->m_Data.m_RotatedQuad.m_Color.r < 240) {
        particle->m_Data.m_RotatedQuad.m_Color.r += 4;
      }

      if (particle->m_Data.m_RotatedQuad.m_Color.g < 240) {
        particle->m_Data.m_RotatedQuad.m_Color.g += 4;
      }

      if (particle->m_Data.m_RotatedQuad.m_Color.b < 240) {
        particle->m_Data.m_RotatedQuad.m_Color.b += 4;
      }

      particle->m_Data.m_Raw[24] += g_DeltaTime * 8;

      cutsceneProgress = g_DragonCutscene.m_CutsceneTicks >= 64
                             ? 63
                             : g_DragonCutscene.m_CutsceneTicks;

      *(short *)&particle->m_Data.m_Raw[20] =
          (particle->m_Data.m_Raw[25] * (0x48 - cutsceneProgress)) >> 3;
      *(short *)&particle->m_Data.m_Raw[22] =
          (((0x20 - particle->m_Data.m_Raw[25]) * cutsceneProgress) >> 4) + 8;

      particle->m_Data.m_RotatedQuad.m_Position.x =
          ((Vector3D16 *)&particle->m_Data.m_Raw[14])->x +
          ((COSINE_8(particle->m_Data.m_Raw[24]) *
            *(short *)&particle->m_Data.m_Raw[22]) >>
           12);
      particle->m_Data.m_RotatedQuad.m_Position.y =
          ((Vector3D16 *)&particle->m_Data.m_Raw[14])->y +
          ((SINE_8(particle->m_Data.m_Raw[24]) *
            *(short *)&particle->m_Data.m_Raw[22]) >>
           12);
      particle->m_Data.m_RotatedQuad.m_Position.z =
          ((Vector3D16 *)&particle->m_Data.m_Raw[14])->z + 0x20 +
          *(short *)&particle->m_Data.m_Raw[20];
      break;
    }
#endif
#ifdef HAS_PARTICLE_25
    case 25:
      func_80017C84(&particle->m_Data.m_RotatedQuad.m_Position,
                  &particle->m_Data.m_RotatedQuad.m_Position,
                  (Vector3D16 *)&particle->m_Data.m_Raw[20]);

      if (*(short *)&particle->m_Data.m_Raw[26] != 0) {
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z++;
      }

      *(short *)&particle->m_Data.m_Raw[26] =
          1 - *(short *)&particle->m_Data.m_Raw[26];
      particle->m_Data.m_RotatedQuad.m_Size += pDelta * 2;
      particle->m_Timer += pDelta;

      if (particle->m_Timer >= 32) {
        func_80053608(particle);
      }
      break;
#endif
#ifdef HAS_PARTICLE_26
    case 26:
      particle->m_Data.m_RotatedQuad.m_Color.r -= 8;
      particle->m_Data.m_RotatedQuad.m_Color.g -= 8;
      particle->m_Data.m_RotatedQuad.m_Color.b -= 8;

      if (particle->m_Data.m_RotatedQuad.m_Color.r == 0 ||
          !particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
#endif
#ifdef HAS_PARTICLE_27
    case 27:
      particle->m_Data.m_RotatedQuad.m_Color.r -= 8;
      particle->m_Data.m_RotatedQuad.m_Color.g -= 8;
      particle->m_Data.m_RotatedQuad.m_Color.b -= 8;
      particle->m_Data.m_RotatedQuad.m_Size += 12;

      if (particle->m_Data.m_RotatedQuad.m_Color.r == 0 ||
          !particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
#endif
#ifdef HAS_PARTICLE_28
    case 28: {

      particle->m_Data.m_RotatedQuad.m_Position.x +=
          ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x;
      particle->m_Data.m_RotatedQuad.m_Position.y +=
          ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y;
      particle->m_Data.m_RotatedQuad.m_Position.z +=
          ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z;
      particle->m_Data.m_RotatedQuad.m_Rotation += particle->m_Data.m_Raw[26];

      if (++particle->m_Timer >= 0x20 || !particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
    }
#endif
#ifdef HAS_PARTICLE_29
    case 29: {
      Vector3D position;
      Vector3D delta;

      // Is this necessary? What condition could make more sense here?
      // Particles 4 and 8 use this manner of check, and this case wouldn't
      // match without two calls like this. The condition does not emit assembly
      // and this Particle only uses RenderType 3.
      if (particle->m_RenderType == 3) {
        func_80017C24(&position, &particle->m_Data.m_Quad.m_Position);
      } else {
        func_80017C24(&position, &particle->m_Data.m_Raw);
      }

      if (*(short *)&particle->m_Data.m_Raw[26] & 8) {
        if (particle->m_Timer < 24) {
          *(short *)&particle->m_Data.m_Raw[20] += (rand() & 6) - 3;
          *(short *)&particle->m_Data.m_Raw[22] += (rand() & 6) - 3;
          (*(short *)&particle->m_Data.m_Raw[24])++;

          if (*(short *)&particle->m_Data.m_Raw[24] > 16) {
            *(short *)&particle->m_Data.m_Raw[24] = 16;
          }

          position.x += *(short *)&particle->m_Data.m_Raw[20];
          position.y += *(short *)&particle->m_Data.m_Raw[22];
          position.z -= *(short *)&particle->m_Data.m_Raw[24];

          func_80017BFC(&particle->m_Data.m_Quad.m_Position, &position);
          particle->m_Timer++;
        } else {
          func_80053608(particle);
        }

      } else if (*(short *)&particle->m_Data.m_Raw[26] & 1) {
        if (particle->m_Timer >= 24) {
          particle->m_Timer = 0;
          *(short *)&particle->m_Data.m_Raw[20] = (rand() & 6) - 3;
          *(short *)&particle->m_Data.m_Raw[22] = (rand() & 6) - 3;
          *(short *)&particle->m_Data.m_Raw[24] = 0;
          *(short *)&particle->m_Data.m_Raw[26] = 8;
        } else {
          int value;

          func_80017C24(&delta,
                               (Vector3D16 *)&particle->m_Data.m_Raw[20]);

          if (*(short *)&particle->m_Data.m_Raw[26] & 2) {
            delta.x += (particle->m_Timer * Cos(particle->m_Timer << 7)) >> 7;
          } else {
            delta.x -= (particle->m_Timer * Cos(particle->m_Timer << 7)) >> 7;
          }

          if (*(short *)&particle->m_Data.m_Raw[26] & 4) {
            delta.y += (particle->m_Timer * Sin(particle->m_Timer << 7)) >> 7;
          } else {
            delta.y -= (particle->m_Timer * Sin(particle->m_Timer << 7)) >> 7;
          }

          delta.z += particle->m_Timer << 5;

          VecSub(&delta, &delta, &position);
          value = VecMagnitude(&delta, 1);

          if (value > 0x80) {
            VecScaleToLength(&delta, value, 0x80);
          }

          VecAdd(&position, &position, &delta);
          func_80017BFC(&particle->m_Data.m_Quad.m_Position, &position);
          particle->m_Timer++;
        }
      } else {
        Moby *moby;
        // TODO: Type props struct
        int *props;
        PathData *path;
        int magnitude;

        moby = &g_LevelMobys[particle->m_Data.m_Raw[20]];
        props = (int *)moby->m_Props;
        path = (PathData *)props[particle->m_Data.m_Raw[21] + 1];
        moby = &g_LevelMobys[props[particle->m_Data.m_Raw[21] + 8]];

        func_80017C24(&position, &particle->m_Data.m_Quad.m_Position);
        VecCopy(&delta, &path->m_Nodes[particle->m_Data.m_Raw[22]].m_Position);

        delta.x += Cos(particle->m_Timer << 7) >> 2;
        delta.y += Sin(particle->m_Timer << 7) >> 2;
        delta.z += Cos((particle->m_Timer << 7) + 0x200) >> 2;

        VecSub(&delta, &delta, &position);
        magnitude = VecMagnitude(&delta, 1);

        if (magnitude <= 0x400) {
          particle->m_Data.m_Raw[22]++;

          if (particle->m_Data.m_Raw[22] >= path->m_NodeCount) {
            moby->m_Substate = 1;
            *(short *)&particle->m_Data.m_Raw[26] = (rand() & 6) + 1;
            func_80017BFC((Vector3D16 *)&particle->m_Data.m_Raw[20],
                                 &moby->m_Position);
            *(short *)&particle->m_Data.m_Raw[24] += rand() & 127;
            particle->m_Timer = 0;
            break;
          }
        }

        VecScaleToLength(&delta, magnitude, 0x100);
        VecAdd(&position, &position, &delta);
        func_80017BFC(&particle->m_Data.m_Quad.m_Position, &position);
        particle->m_Timer++;
      }

      break;
    }
#endif
#ifdef HAS_PARTICLE_30
    case 30:
      particle->m_Data.m_RotatedQuad.m_Position.z +=
          *(short *)&particle->m_Data.m_Raw[26];
      particle->m_Data.m_RotatedQuad.m_Size += 1;

      particle->m_Data.m_RotatedQuad.m_Color.r -= pDelta * 2;
      particle->m_Data.m_RotatedQuad.m_Color.g -= pDelta * 2;
      particle->m_Data.m_RotatedQuad.m_Color.b -= pDelta * 2;

      particle->m_Timer += pDelta;

      if (particle->m_Timer >= 32) {
        func_80053608(particle);
      }
      break;
#endif
#ifdef HAS_PARTICLE_31
    case 31:
      func_80017C84(&particle->m_Data.m_Quad.m_Position,
                  &particle->m_Data.m_Quad.m_Position,
                  (Vector3D16 *)&particle->m_Data.m_Raw[20]);
      particle->m_Timer += pDelta;

      if (particle->m_Timer >= 64) {
        func_80053608(particle);
      } else if (!particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
#endif
#ifdef HAS_PARTICLE_33
    case 33: {
      int value;
      func_80017C84(&particle->m_Data.m_RotatedQuad.m_Position,
                  &particle->m_Data.m_RotatedQuad.m_Position,
                  (Vector3D16 *)&particle->m_Data.m_Raw[20]);

      if (*(short *)&particle->m_Data.m_Raw[26] != 0) {
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z++;
      }

      *(short *)&particle->m_Data.m_Raw[26] =
          1 - *(short *)&particle->m_Data.m_Raw[26];
      particle->m_Data.m_RotatedQuad.m_Size += pDelta * 2;

      value = particle->m_Data.m_RotatedQuad.m_Color.r - pDelta;
      if (value < 0) {
        value = 0;
      }
      particle->m_Data.m_RotatedQuad.m_Color.r = value;

      value = particle->m_Data.m_RotatedQuad.m_Color.g - pDelta;
      if (value < 0) {
        value = 0;
      }
      particle->m_Data.m_RotatedQuad.m_Color.g = value;

      value = particle->m_Data.m_RotatedQuad.m_Color.b - pDelta;
      if (value < 0) {
        value = 0;
      }
      particle->m_Data.m_RotatedQuad.m_Color.b = value;

      particle->m_Timer += pDelta;

      if (particle->m_Timer >= 0x20 || !particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
    }
#endif
#ifdef HAS_PARTICLE_65
    case 65: {
      Vector3D16 delta;

      delta.x = (particle->m_Data.m_Line.m_End.x -
                 particle->m_Data.m_Line.m_Position.x) >>
                1;
      delta.y = (particle->m_Data.m_Line.m_End.y -
                 particle->m_Data.m_Line.m_Position.y) >>
                1;
      delta.z = (particle->m_Data.m_Line.m_End.z -
                 particle->m_Data.m_Line.m_Position.z) >>
                1;

      particle->m_Data.m_Line.m_Position.x += delta.x;
      particle->m_Data.m_Line.m_Position.y += delta.y;
      particle->m_Data.m_Line.m_Position.z += delta.z;

      delta.x += (rand() & 2) - 1;
      delta.y += (rand() & 2) - 1;

      particle->m_Data.m_Line.m_End.x += delta.x;
      particle->m_Data.m_Line.m_End.y += delta.y;
      particle->m_Data.m_Line.m_End.z += delta.z;

      particle->m_Timer++;

      if (particle->m_Timer >= 8 || !particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
    }
#endif
#ifdef HAS_PARTICLE_66
    case 66: {
      int i;

      for (i = 0; i < pDelta; i++) {
        if (particle->m_Timer & 1) {
          particle->m_Data.m_Point.m_Position.x +=
              ((Vector3D16 *)&particle->m_Data.m_Raw[12])->x;
          particle->m_Data.m_Point.m_Position.y +=
              ((Vector3D16 *)&particle->m_Data.m_Raw[12])->y;
          particle->m_Data.m_Point.m_Position.z +=
              ((Vector3D16 *)&particle->m_Data.m_Raw[12])->z;

          if (particle->m_Timer & 2) {
            ((Vector3D16 *)&particle->m_Data.m_Raw[12])->x += (rand() & 2) - 1;
            ((Vector3D16 *)&particle->m_Data.m_Raw[12])->y += (rand() & 2) - 1;
            ((Vector3D16 *)&particle->m_Data.m_Raw[12])->z += (rand() & 2) - 1;
          }
        }

        particle->m_Timer++;
      }

      if (particle->m_Timer >= 24 || !particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
    }
#endif
#ifdef HAS_PARTICLE_69
    case 69: {
      Vector3D position;
      Vector3D target;
      PathData *pathData;
      int offset;
      int distance;

      pathData = *(PathData **)&particle->m_Data.m_Raw[20];

      func_80017C24(&position, &particle->m_Data.m_Point.m_Position);

      VecCopy(
          &target,
          &pathData->m_Nodes[*(int *)&particle->m_Data.m_Raw[24]].m_Position);

      target.x += Cos(particle->m_Timer << 7) >> 2;
      target.y += Sin(particle->m_Timer << 7) >> 2;
      target.z += Cos((particle->m_Timer << 7) + 0x200) >> 2;

      VecSub(&target, &target, &position);
      distance = VecMagnitude(&target, 1);

      if (distance <= 0x400) {
        if (++*(int *)&particle->m_Data.m_Raw[24] >= pathData->m_NodeCount) {
          func_80053608(particle);
          break;
        }
      }

      VecScaleToLength(&target, distance, 0x100);
      VecAdd(&position, &position, &target);
      func_80017BFC(&particle->m_Data.m_Point.m_Position, &position);

      particle->m_Timer++;
      break;
    }
#endif
#ifdef HAS_PARTICLE_70
    case 70: {
      Vector3D16 delta;

      delta.x = (particle->m_Data.m_Line.m_End.x -
                 particle->m_Data.m_Line.m_Position.x) >>
                1;
      delta.y = (particle->m_Data.m_Line.m_End.y -
                 particle->m_Data.m_Line.m_Position.y) >>
                1;
      delta.z = (particle->m_Data.m_Line.m_End.z -
                 particle->m_Data.m_Line.m_Position.z) >>
                1;

      particle->m_Data.m_Line.m_Position.x += delta.x;
      particle->m_Data.m_Line.m_Position.y += delta.y;
      particle->m_Data.m_Line.m_Position.z += delta.z;

      delta.x += (rand() & 2) - 1;
      delta.y += (rand() & 2) - 1;

      if (particle->m_Timer & 1) {
        delta.z--;
      }

      particle->m_Data.m_Line.m_End.x += delta.x;
      particle->m_Data.m_Line.m_End.y += delta.y;
      particle->m_Data.m_Line.m_End.z += delta.z;

      particle->m_Timer++;

      if (particle->m_Timer >= 0x20 || !particle->m_WasRendered) {
        func_80053608(particle);
      } else {
        particle->m_Data.m_Line.m_Color0.r -= 3;
        if (particle->m_Data.m_Line.m_Color0.r < 128) {
          particle->m_Data.m_Line.m_Color0.r = 128;
        }

        particle->m_Data.m_Line.m_Color0.g -= 4;
        if (particle->m_Data.m_Line.m_Color0.g < 96) {
          particle->m_Data.m_Line.m_Color0.g = 96;
        }

        particle->m_Data.m_Line.m_Color0.b = 0;

        particle->m_Data.m_Line.m_Color1.r -= 3;
        if (particle->m_Data.m_Line.m_Color1.r < 192) {
          particle->m_Data.m_Line.m_Color1.r = 192;
        }

        particle->m_Data.m_Line.m_Color1.g -= 4;
        if (particle->m_Data.m_Line.m_Color1.g < 128) {
          particle->m_Data.m_Line.m_Color1.g = 128;
        }

        particle->m_Data.m_Line.m_Color1.b -= 6;
        if (particle->m_Data.m_Line.m_Color1.b < 32) {
          particle->m_Data.m_Line.m_Color1.b = 32;
        }
      }
      break;
    }
#endif
#ifdef HAS_PARTICLE_71
    case 71: {
      Vector3D delta;

      particle->m_Timer++;

      if (particle->m_Timer < 0x20 && particle->m_WasRendered != 0) {
        delta.x = particle->m_Data.m_Line.m_End.x -
                  particle->m_Data.m_Line.m_Position.x;
        delta.y = particle->m_Data.m_Line.m_End.y -
                  particle->m_Data.m_Line.m_Position.y;
        delta.z = particle->m_Data.m_Line.m_End.z -
                  particle->m_Data.m_Line.m_Position.z;

        delta.x += (rand() & 2) - 1;
        delta.y += (rand() & 2) - 1;
        delta.z += (rand() & 2) - 1;

        particle->m_Data.m_Line.m_End.x += delta.x;
        particle->m_Data.m_Line.m_End.y += delta.y;
        particle->m_Data.m_Line.m_End.z += delta.z;

        particle->m_Data.m_Line.m_Position.x =
            particle->m_Data.m_Line.m_End.x - delta.x;
        particle->m_Data.m_Line.m_Position.y =
            particle->m_Data.m_Line.m_End.y - delta.y;
        particle->m_Data.m_Line.m_Position.z =
            particle->m_Data.m_Line.m_End.z - delta.z;

        particle->m_Data.m_Line.m_Color1.r -= 2;
        particle->m_Data.m_Line.m_Color1.g -= 2;
        particle->m_Data.m_Line.m_Color1.b -= 4;
        particle->m_Data.m_Line.m_Color0.r -= 3;
        particle->m_Data.m_Line.m_Color0.g -= 3;
        particle->m_Data.m_Line.m_Color0.b -= 3;
      } else {
        func_80053608(particle);
      }
      break;
    }
#endif
#ifdef HAS_PARTICLE_72
    case 72: {
      // This particle is spawned by func_800530C0
      Vector3D delta;

      particle->m_Timer++;

      if (particle->m_Timer < 48 && particle->m_WasRendered) {
        delta.x = (particle->m_Data.m_Line.m_Position.x -
                   particle->m_Data.m_Line.m_End.x) >>
                  1;
        delta.y = (particle->m_Data.m_Line.m_Position.y -
                   particle->m_Data.m_Line.m_End.y) >>
                  1;
        delta.z = (particle->m_Data.m_Line.m_Position.z -
                   particle->m_Data.m_Line.m_End.z) >>
                  1;

        delta.x += (rand() & 4) - 2;
        delta.y += (rand() & 4) - 2;
        delta.z += (rand() & 2) - 1;

        particle->m_Data.m_Line.m_Position.x += delta.x;
        particle->m_Data.m_Line.m_Position.y += delta.y;
        particle->m_Data.m_Line.m_Position.z += delta.z;

        particle->m_Data.m_Line.m_End.x =
            particle->m_Data.m_Line.m_Position.x - delta.x * 2;
        particle->m_Data.m_Line.m_End.y =
            particle->m_Data.m_Line.m_Position.y - delta.y * 2;
        particle->m_Data.m_Line.m_End.z =
            particle->m_Data.m_Line.m_Position.z - delta.z * 2;
      } else {
        func_80053608(particle);
      }
      break;
    }
#endif
#ifdef HAS_PARTICLE_73
    case 73:
      if (particle->m_WasRendered && particle->m_Timer <= 32) {
        particle->m_Data.m_Point.m_Position.x =
            (particle->m_Data.m_Raw[27] *
             Cos((particle->m_Data.m_Raw[26] + particle->m_Timer) << 6)) >>
            10;
        particle->m_Data.m_Point.m_Position.y =
            (particle->m_Data.m_Raw[27] *
             Sin((particle->m_Data.m_Raw[26] + particle->m_Timer) << 6)) >>
            10;

        particle->m_Data.m_Point.m_Position.z = particle->m_Timer << 1;
        particle->m_Timer++;
        particle->m_Data.m_Point.m_Position.x +=
            *(short *)&particle->m_Data.m_Raw[20];
        particle->m_Data.m_Point.m_Position.y +=
            *(short *)&particle->m_Data.m_Raw[22];
        particle->m_Data.m_Point.m_Position.z +=
            *(short *)&particle->m_Data.m_Raw[24];
      } else {
        func_80053608(particle);
      }

      break;
#endif
#ifdef HAS_PARTICLE_74
    case 74:
      particle->m_Data.m_Point.m_Position.x +=
          ((Vector3D16 *)&particle->m_Data.m_Raw[12])->x;
      particle->m_Data.m_Point.m_Position.y +=
          ((Vector3D16 *)&particle->m_Data.m_Raw[12])->y;
      particle->m_Data.m_Point.m_Position.z +=
          ((Vector3D16 *)&particle->m_Data.m_Raw[12])->z;
      particle->m_Data.m_Point.m_Color.g -= 15;

      particle->m_Timer++;

      if (!particle->m_WasRendered || particle->m_Timer > 16) {
        func_80053608(particle);
      }
      break;
#endif
#ifdef HAS_PARTICLE_75
    case 75: {
      Vector3D position;
      Vector3D velocity;

      if (particle->m_Timer < 0x30 && particle->m_WasRendered) {
        func_80017C24(&position, &particle->m_Data.m_Point.m_Position);

        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->x += (rand() & 6) - 3;
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->y += (rand() & 6) - 3;
        ((Vector3D16 *)&particle->m_Data.m_Raw[20])->z -= 1;

        func_80017C4C(&velocity, (Vector3D16 *)&particle->m_Data.m_Raw[20]);
        VecAdd(&position, &position, &velocity);
        func_80017BFC(&particle->m_Data.m_Point.m_Position, &position);

        particle->m_Timer++;
      } else {
        func_80053608(particle);
      }

      break;
    }
#endif
#ifdef HAS_PARTICLE_76
    case 76:
      particle->m_Data.m_Raw[20] += g_DeltaTime * 4;
      particle->m_Data.m_Raw[21] += g_DeltaTime;

      particle->m_Data.m_Point.m_Position.x =
          ((Vector3D16 *)&particle->m_Data.m_Raw[12])->x +
          ((COSINE_8(particle->m_Data.m_Raw[20]) *
            particle->m_Data.m_Raw[21]) >>
           12);
      particle->m_Data.m_Point.m_Position.y =
          ((Vector3D16 *)&particle->m_Data.m_Raw[12])->y +
          ((SINE_8(particle->m_Data.m_Raw[20]) * particle->m_Data.m_Raw[21]) >>
           12);
      particle->m_Data.m_Point.m_Position.z += g_DeltaTime * 6;

      if (particle->m_Data.m_Raw[21] > 192) {
        func_80053608(particle);
      }
      break;
#endif
#ifdef HAS_PARTICLE_77
    case 77: {
      Vector3D16 delta;

      delta.x = (particle->m_Data.m_Line.m_End.x -
                 particle->m_Data.m_Line.m_Position.x) >>
                1;
      delta.y = (particle->m_Data.m_Line.m_End.y -
                 particle->m_Data.m_Line.m_Position.y) >>
                1;
      delta.z = (particle->m_Data.m_Line.m_End.z -
                 particle->m_Data.m_Line.m_Position.z) >>
                1;

      particle->m_Data.m_Line.m_Position.x += delta.x;
      particle->m_Data.m_Line.m_Position.y += delta.y;
      particle->m_Data.m_Line.m_Position.z += delta.z;

      delta.y++;

      particle->m_Data.m_Line.m_End.x += delta.x;
      particle->m_Data.m_Line.m_End.y += delta.y;
      particle->m_Data.m_Line.m_End.z += delta.z;

      particle->m_Timer++;

      if (particle->m_Timer >= 32) {
        func_80053608(particle);
      }
      break;
    }
#endif
#ifdef HAS_PARTICLE_78
    case 78:
      particle->m_Timer++;

      if (particle->m_Timer < 0x28 && particle->m_WasRendered != 0) {
        particle->m_Data.m_Point.m_Position.x +=
            ((Vector3D16 *)&particle->m_Data.m_Raw[12])->x;
        particle->m_Data.m_Point.m_Position.y +=
            ((Vector3D16 *)&particle->m_Data.m_Raw[12])->y;
        particle->m_Data.m_Point.m_Position.z +=
            ((Vector3D16 *)&particle->m_Data.m_Raw[12])->z;

        ((Vector3D16 *)&particle->m_Data.m_Raw[12])->x += (rand() & 2) - 1;
        ((Vector3D16 *)&particle->m_Data.m_Raw[12])->y += (rand() & 2) - 1;
        ((Vector3D16 *)&particle->m_Data.m_Raw[12])->z += (rand() & 2) - 1;

        if (((Vector3D16 *)&particle->m_Data.m_Raw[12])->z >= 3) {
          ((Vector3D16 *)&particle->m_Data.m_Raw[12])->z = 2;
        }

        if (((Vector3D16 *)&particle->m_Data.m_Raw[12])->z < -4) {
          ((Vector3D16 *)&particle->m_Data.m_Raw[12])->z = -4;
        }

        particle->m_Data.m_Point.m_Color.r -= 2;
        particle->m_Data.m_Point.m_Color.g -= 2;
        particle->m_Data.m_Point.m_Color.b -= 1;
      } else {
        func_80053608(particle);
      }
      break;
#endif
#ifdef HAS_PARTICLE_79
    case 79: {
      Vector3D16 delta;

      delta.x = (particle->m_Data.m_Line.m_End.x -
                 particle->m_Data.m_Line.m_Position.x) >>
                1;
      delta.y = (particle->m_Data.m_Line.m_End.y -
                 particle->m_Data.m_Line.m_Position.y) >>
                1;
      delta.z = (particle->m_Data.m_Line.m_End.z -
                 particle->m_Data.m_Line.m_Position.z) >>
                1;

      particle->m_Data.m_Line.m_Position.x += delta.x;
      particle->m_Data.m_Line.m_Position.y += delta.y;
      particle->m_Data.m_Line.m_Position.z += delta.z;

      particle->m_Data.m_Line.m_End.x += delta.x;
      particle->m_Data.m_Line.m_End.y += delta.y;
      particle->m_Data.m_Line.m_End.z += delta.z;

      particle->m_Timer++;

      if (particle->m_Timer >= 0x18 || !particle->m_WasRendered) {
        func_80053608(particle);
      } else {
        particle->m_Data.m_Line.m_Color0.r -= 3;
        particle->m_Data.m_Line.m_Color0.g -= 4;
        particle->m_Data.m_Line.m_Color1.r -= 3;
        particle->m_Data.m_Line.m_Color1.g -= 4;

        if (particle->m_Data.m_Line.m_Color1.b >= 6) {
          particle->m_Data.m_Line.m_Color1.b -= 6;
        }
      }
      break;
    }
#endif
#ifdef HAS_PARTICLE_80
    case 80: {
      Vector3D16 delta;

      delta.x = particle->m_Data.m_Line.m_End.x -
                particle->m_Data.m_Line.m_Position.x;
      delta.y = particle->m_Data.m_Line.m_End.y -
                particle->m_Data.m_Line.m_Position.y;
      delta.z = particle->m_Data.m_Line.m_End.z -
                particle->m_Data.m_Line.m_Position.z;

      particle->m_Data.m_Line.m_Position.x += delta.x;
      particle->m_Data.m_Line.m_Position.y += delta.y;
      particle->m_Data.m_Line.m_Position.z += delta.z;

      delta.z--;

      particle->m_Data.m_Line.m_End.x += delta.x;
      particle->m_Data.m_Line.m_End.y += delta.y;
      particle->m_Data.m_Line.m_End.z += delta.z;

      particle->m_Timer++;

      if (particle->m_Timer >= 0x20 || !particle->m_WasRendered) {
        func_80053608(particle);
      }
      break;
    }
#endif
    }
  }
}
