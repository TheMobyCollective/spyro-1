#include "balloonist.h"
#include "buffers.h"
#include "camera.h"
#include "collision.h"
#include "cyclorama.h"
#include "environment.h"
#include "fairy.h"
#include "gamepad.h"
#include "gamestates/draw.h"
#include "gamestates/init.h"
#include "hud.h"
#include "loaders.h"
#include "math.h"
#include "memory.h"
#include "moby_lists.h"
#include "overlay_pointers.h"
#include "renderers.h"
#include "sony_image.h"
#include "specular_and_metal.h"
#include "spu.h"
#include "spyro.h"
#include "strings.h"
#include "variables.h"

#include <rand.h>
#include <stdio.h>

extern unsigned int strlen(char *);

extern int g_ScreenBorderEnabled; // Is the screen border enabled
extern int D_800756C0;

extern SphericalCoordsOffset D_8006C8BC;
extern int D_8006EADC[9][2]; // BalloonArrivalJumpoffXY;

void NAME_OVERLAY_FUNCTION(BalloonistEnter)(Moby *pBalloonist) {
  int *props;
  Vector3D vec;
  props = (int *)pBalloonist->m_Props;

  g_Gamestate = GS_Balloonist;
  g_Balloonist.m_State = 0;
  g_Balloonist.unk_0x04 = 0;
  g_Balloonist.unk_0x08 = 0;
  g_Balloonist.m_BalloonistMoby = pBalloonist;
  g_Balloonist.m_BalloonMoby = &g_LevelMobys[props[0]];
  g_ScreenBorderEnabled = 1;
  g_StateSwitch = 1;
  g_Balloonist.unk_0x38 =
      Atan2(g_Camera.m_Position.x - pBalloonist->m_Position.x,
            g_Camera.m_Position.y - pBalloonist->m_Position.y, 1);
  VecSub(&vec, &g_Camera.m_Position, &pBalloonist->m_Position);
  g_Balloonist.unk_0x3c = VecMagnitude(&vec, 0);
  g_Balloonist.unk_0x40 = g_Camera.m_Position.z;
  g_Balloonist.unk_0x50 = (pBalloonist->m_Rotation.z * 16 - 0x312) & 0xFFF;
  g_Balloonist.unk_0x54 = 0x52E;
  g_Balloonist.unk_0x58 = pBalloonist->m_Position.z + 0x58F;
}

void NAME_OVERLAY_FUNCTION(BalloonistExit)(void) {
  func_8002D02C();
  g_Spyro.unk_0x1b4 = 0;
  g_Spyro.m_HeadRotation.y = 0;
  if (g_Sparx != nullptr) {
    g_Sparx->m_RenderRadius = 16;
  }
}

void NAME_OVERLAY_FUNCTION(BalloonistUpdate)(void) {
  if (g_Balloonist.m_State < 4) {
    Moby **mobyList = (Moby **)&g_SonyImage.u.m_Buf[0x400];
    mobyList[0] = g_Balloonist.m_BalloonistMoby;
    mobyList[1] = 0;
    func_800522C0(mobyList, 0);
  }

  switch (g_Balloonist.m_State) {
  case 0: {
    Vector3D vec;
    Vector3D16 shortvec;
    int lerpProgress, interpAngle, interpRadius;

    if (g_Balloonist.unk_0x04 < 96) {
      lerpProgress = Sin((g_Balloonist.unk_0x04 << 11) / 96 - 0x400) + 0x1000;

      if (g_Balloonist.unk_0x04 == g_DeltaTime) {
        if (g_Sparx != nullptr) {
          g_Sparx->m_RenderRadius = 0;
          g_Sparx->m_WasDrawn = 0;
          if (((MobySparxProps *)g_Sparx->m_Props)->m_Glow != 0) {
            func_80058B60(((MobySparxProps *)g_Sparx->m_Props)->m_Glow);
            ((MobySparxProps *)g_Sparx->m_Props)->m_Glow = 0;
          }
        }
        g_SavedFairyKissTimer = g_SpyroFlame.m_FairyKissTimer;
        SpyroReset(1);

        g_Spyro.m_BodyAnimation = 1;
        g_Spyro.m_NextBodyAnimation = 1;
        g_Spyro.m_NextBodyAnimationFrame = 1;

        VecCopy(&g_Balloonist.unk_0x18, &g_Spyro.m_Position);

        g_Balloonist.unk_0x2C.x = 0x4a0;
        g_Balloonist.unk_0x2C.y = 0;
        g_Balloonist.unk_0x2C.z = 0x164;

        VecRotateByMatrix(
            (MATRIX *)&g_Balloonist.m_BalloonistMoby->m_RotationMatrix,
            &g_Balloonist.unk_0x2C, &g_Balloonist.unk_0x2C);
        VecAdd(&g_Balloonist.unk_0x2C, &g_Balloonist.unk_0x2C,
               &g_Balloonist.m_BalloonistMoby->m_Position);

        g_Balloonist.unk_0x30 = g_Spyro.m_BodyRotation.z << 4;
        VecSub(&vec, &g_Balloonist.unk_0x2C, &g_Balloonist.unk_0x18);
        g_Balloonist.unk_0x34 = Atan2(vec.x, vec.y, 1);
      }

      if (g_Balloonist.unk_0x04 < 24) {
        int temp = Sin((g_Balloonist.unk_0x04 << 11) / 24 - 1024) + 4096;
        if ((g_Balloonist.unk_0x34 - g_Balloonist.unk_0x30 & 0xfff) <= 2048) {
          g_Spyro.m_BodyRotation.z =
              (g_Balloonist.unk_0x30 +
               (func_80017928(g_Balloonist.unk_0x34, g_Balloonist.unk_0x30) *
                    temp >>
                13)) >>
              4;
        } else {
          g_Spyro.m_BodyRotation.z =
              (g_Balloonist.unk_0x30 -
               (func_80017928(g_Balloonist.unk_0x34, g_Balloonist.unk_0x30) *
                    temp >>
                13)) >>
              4;
        }
        g_Spyro.m_BodyAnimationSpeed = 8;
      } else if (g_Balloonist.unk_0x04 < 72) {
        int temp =
            (Sin(((g_Balloonist.unk_0x04 - 24) * 2048) / 48 - 1024) + 4096);
        VecSub(&vec, &g_Balloonist.unk_0x2C, &g_Balloonist.unk_0x18);
        VecMult(&vec, &vec, temp);
        VecShiftRight(&vec, 13);
        VecAdd(&g_Spyro.m_Position, &g_Balloonist.unk_0x18, &vec);

        g_Spyro.m_BodyAnimationSpeed = VecMagnitude(&vec, 0) >> 1;
        if (g_Spyro.m_BodyAnimationSpeed < 4) {
          g_Spyro.m_BodyAnimationSpeed = 4;
        }
        if (g_Spyro.m_BodyAnimationSpeed > 0x10) {
          g_Spyro.m_BodyAnimationSpeed = 0x10;
        }
      } else {
        int temp =
            Sin(((g_Balloonist.unk_0x04 - 72) * 2048) / 24 - 1024) + 4096;
        if (g_Balloonist.unk_0x04 - g_DeltaTime < 72) {
          g_Balloonist.unk_0x30 = g_Spyro.m_BodyRotation.z << 4;
          g_Balloonist.unk_0x34 =
              g_Balloonist.m_BalloonistMoby->m_Rotation.z * 16 - 2048 & 0xfff;
          g_Spyro.m_NextBodyAnimation = 3;
          g_Spyro.m_BodyAnimationFrame = g_Spyro.m_NextBodyAnimationFrame;
          g_Spyro.m_NextBodyAnimationFrame = 0;
          g_Spyro.m_BodyFrameProgress = 0;
          g_Spyro.m_BodyAnimationSpeed = 8;
        }
        if (((g_Balloonist.unk_0x34 - g_Balloonist.unk_0x30) & 0xfff) <= 2048) {
          g_Spyro.m_BodyRotation.z =
              (g_Balloonist.unk_0x30 +
               (func_80017928(g_Balloonist.unk_0x34, g_Balloonist.unk_0x30) *
                    temp >>
                13)) >>
              4;
        } else {
          g_Spyro.m_BodyRotation.z =
              (g_Balloonist.unk_0x30 -
               (func_80017928(g_Balloonist.unk_0x34, g_Balloonist.unk_0x30) *
                    temp >>
                13)) >>
              4;
        }
        g_Spyro.m_BodyAnimationSpeed = 8;
      }

      g_Spyro.m_BodyRotation.x = 0;
      g_Spyro.m_BodyRotation.y = 0;
      g_Spyro.m_FloorHeight = ColFindFloor(&g_Spyro.m_Position, 0x10000);
      RotVec8ToMatrix(&g_Spyro.m_BodyRotation, &g_Spyro.m_RotationMatrix, 0);
      func_80049FAC(1);
      func_80048D10(g_DeltaTime);

      if ((g_Balloonist.unk_0x50 - g_Balloonist.unk_0x38 & 0xfff) <= 0x800) {
        interpAngle = g_Balloonist.unk_0x38 +
                      (FIXED_MUL(func_80017928(g_Balloonist.unk_0x50,
                                               g_Balloonist.unk_0x38),
                                 lerpProgress) >>
                       1);
      } else {
        interpAngle = g_Balloonist.unk_0x38 -
                      (FIXED_MUL(func_80017928(g_Balloonist.unk_0x50,
                                               g_Balloonist.unk_0x38),
                                 lerpProgress) >>
                       1);
      }

      interpRadius = (g_Balloonist.unk_0x3c +
                      (FIXED_MUL(g_Balloonist.unk_0x54 - g_Balloonist.unk_0x3c,
                                 lerpProgress) >>
                       1));
      g_Camera.m_Position.x = g_Balloonist.m_BalloonistMoby->m_Position.x +
                              FIXED_MUL(Cos(interpAngle), interpRadius);
      g_Camera.m_Position.y = g_Balloonist.m_BalloonistMoby->m_Position.y +
                              FIXED_MUL(Sin(interpAngle), interpRadius);
      g_Camera.m_Position.z =
          g_Balloonist.unk_0x40 +
          (FIXED_MUL(g_Balloonist.unk_0x58 - g_Balloonist.unk_0x40,
                     lerpProgress) >>
           1);

      vec.x = 0x220;
      vec.y = 0;
      vec.z = 0x340;
      VecRotateByMatrix(
          (MATRIX *)&g_Balloonist.m_BalloonistMoby->m_RotationMatrix, &vec,
          &vec);
      VecAdd(&vec, &vec, &g_Balloonist.m_BalloonistMoby->m_Position);
      VecSub(&vec, &vec, &g_Camera.m_Position);

      if (g_Balloonist.unk_0x04 < 32) {
        shortvec.x = 0;
        shortvec.y = Atan2(VecMagnitude(&vec, 0), -vec.z, 1);
        shortvec.z = Atan2(vec.x, vec.y, 1);
        g_Camera.m_Rotation.x =
            g_Camera.m_Rotation.x +
                (func_8001796C(shortvec.x, g_Camera.m_Rotation.x) *
                     g_Balloonist.unk_0x04 >>
                 5) &
            0xfff;
        g_Camera.m_Rotation.y =
            g_Camera.m_Rotation.y +
                (func_8001796C(shortvec.y, g_Camera.m_Rotation.y) *
                     g_Balloonist.unk_0x04 >>
                 5) &
            0xfff;
        g_Camera.m_Rotation.z =
            g_Camera.m_Rotation.z +
                (func_8001796C(shortvec.z, g_Camera.m_Rotation.z) *
                     g_Balloonist.unk_0x04 >>
                 5) &
            0xfff;
      } else {
        g_Camera.m_Rotation.x = 0;
        g_Camera.m_Rotation.y = Atan2(VecMagnitude(&vec, 0), -vec.z, 1);
        g_Camera.m_Rotation.z = Atan2(vec.x, vec.y, 1);
      }
      (*g_UpdateParticle)(g_DeltaTime);
      SoundsUpdate();
    } else {
      g_Camera.m_Position.x =
          g_Balloonist.m_BalloonistMoby->m_Position.x +
          FIXED_MUL(Cos(g_Balloonist.unk_0x50), g_Balloonist.unk_0x54);
      g_Camera.m_Position.y =
          g_Balloonist.m_BalloonistMoby->m_Position.y +
          FIXED_MUL(Sin(g_Balloonist.unk_0x50), g_Balloonist.unk_0x54);
      g_Camera.m_Position.z = g_Balloonist.unk_0x58;

      VecCopy(&g_Spyro.m_Position, &g_Balloonist.unk_0x2C);

      g_Spyro.m_BodyRotation.z = g_Balloonist.unk_0x34 >> 4;
      g_Spyro.m_NextBodyAnimation = 0;
      g_Spyro.m_BodyAnimationFrame = g_Spyro.m_NextBodyAnimationFrame;
      g_Spyro.m_NextBodyAnimationFrame = 0;
      g_Spyro.m_BodyFrameProgress = 0;
      g_Spyro.m_BodyAnimationSpeed = 4;
      g_Balloonist.m_State = 1;
      g_Balloonist.unk_0x04 = 0;
    }
    break;
  }

  case 1: {
    if (g_Balloonist.m_DialogueId < 30) {
      if ((g_Pad.m_Down & (PAD_CROSS | PAD_START | PAD_RIGHT | PAD_DOWN)) &&
          (g_Balloonist.unk_0x04 > 80)) {
        int dialog = g_Balloonist.m_DialogueId % 6;
        if (dialog == 0) {
          g_Balloonist.m_DialogueId++;
        } else if (dialog < 3) {
          if ((g_Balloonist.m_DialogueId < 3) && (D_800758D0[1] < 2)) {
            (*g_BalloonistExit)();
          } else if (g_Balloonist.m_DialogueId == 14) {
            while (g_Balloonist.m_DialogueId == 14) {
              int random;
              random = rand() % 5;
              if (random == 0 && g_LevelEggCount[1] == 0) // Stone Hill
                g_Balloonist.m_DialogueId = 33;
              else if (random == 1 && g_LevelEggCount[7] == 0) // Dry Canyon
                g_Balloonist.m_DialogueId = 34;
              else if (random == 2 && g_LevelEggCount[8] == 0) // Cliff Town
                g_Balloonist.m_DialogueId = 35;
              else if (random == 3 && g_LevelEggCount[12] < 2) // Magic Crafters
                g_Balloonist.m_DialogueId = 36;
              else if (random == 4 && g_LevelEggCount[15] == 0) // Wizard Peak
                g_Balloonist.m_DialogueId = 37;
            }
          } else {
            g_Balloonist.m_DialogueId = 30;
          }
        } else if (dialog == 3) {
          g_Balloonist.m_DialogueId += 2;
        } else if (dialog == 4) {
          g_Balloonist.m_DialogueId++;
        } else {
          g_Balloonist.m_DialogueId = 31;
        }
        g_Balloonist.unk_0x04 = 0;
      }
    } else if (g_Balloonist.m_DialogueId == 30) {
      int homeworldId = 1;

      while (homeworldId < 6 && D_800758D0[homeworldId] == 2) {
        homeworldId++;
      }
      if (g_Pad.m_Down & PAD_UP) {
        g_Balloonist.unk_0x08--;
        if (g_Balloonist.unk_0x08 < 0) {
          g_Balloonist.unk_0x08 = homeworldId - 1;
        }
        g_Balloonist.unk_0x04 = 0x20;
        PlaySound(g_Spu.m_SoundTable->menuCursor, 0, 0x10, 0);
      } else if (g_Pad.m_Down & PAD_DOWN) {
        g_Balloonist.unk_0x08++;
        if (homeworldId <= g_Balloonist.unk_0x08) {
          g_Balloonist.unk_0x08 = 0;
        }
        g_Balloonist.unk_0x04 = 0x20;
        PlaySound(g_Spu.m_SoundTable->menuCursor, 0, 0x10, 0);
      }
      if ((g_Pad.m_Down & (PAD_CROSS | PAD_START)) &&
          g_Balloonist.unk_0x04 >= 31) {
        if (g_Balloonist.unk_0x08 == 0) {
          (*g_BalloonistExit)();
        } else {
          KillSoundsAndMusic(0);
          g_Balloonist.m_State = 2;
          g_Balloonist.unk_0x04 = 0;
          g_NextLevelId = g_Balloonist.unk_0x08 * 10;
          if (g_LevelId <= g_NextLevelId) {
            g_NextLevelId = g_NextLevelId + 10;
          }
          g_Balloonist.m_Homeworld = g_NextLevelId / 10 - 1;
        }
      }
    } else if (g_Balloonist.m_DialogueId == 31 ||
               g_Balloonist.m_DialogueId == 32) {
      if (g_Pad.m_Down & (PAD_UP | PAD_DOWN)) {
        g_Balloonist.unk_0x04 = 0x20;
        g_Balloonist.unk_0x08 = 1 - g_Balloonist.unk_0x08;
        PlaySound(g_Spu.m_SoundTable->menuCursor, 0, 0x10, 0);
      }

      if ((g_Pad.m_Down & (PAD_CROSS | PAD_START)) &&
          g_Balloonist.unk_0x04 >= 0x1f) {
        if (g_Balloonist.unk_0x08 == 0) {
          if (g_Balloonist.m_DialogueId == 31) {
            (*g_BalloonistExit)();
          } else {
            g_Balloonist.m_DialogueId = 30;
            g_Balloonist.unk_0x08 = 0;
            g_Balloonist.m_DialogueTopStr = 1;
          }
        } else {
          KillSoundsAndMusic(0);
          g_Balloonist.m_State = 2;
          g_Balloonist.unk_0x04 = 0;
          if (g_Balloonist.m_DialogueId == 31) {
            g_NextLevelId = g_LevelId + 10;
            g_Balloonist.m_Homeworld = (g_LevelId + 10) / 10 - 1;
          }
        }
      }
    } else if ((g_Pad.m_Down &
                (PAD_CROSS | PAD_START | PAD_RIGHT | PAD_DOWN)) &&
               g_Balloonist.unk_0x04 > 80) {
      if ((g_Balloonist.m_DialogueId == 36) ||
          (g_Balloonist.m_DialogueId == 38)) {
        g_Balloonist.m_DialogueId = 30;
        g_Balloonist.unk_0x08 = 0;
        g_Balloonist.m_DialogueTopStr = 1;
      } else if (g_Balloonist.m_DialogueId == 37) {
        g_Balloonist.m_DialogueId = 38;
        g_Balloonist.unk_0x04 = 0;
      } else {
        if (g_Balloonist.m_DialogueId == 33) {
          g_NextLevelId = 11;
        } else if (g_Balloonist.m_DialogueId == 34) {
          g_NextLevelId = 21;
        } else if (g_Balloonist.m_DialogueId == 35) {
          g_NextLevelId = 22;
        }
        g_Balloonist.m_Homeworld = g_Balloonist.m_DialogueId - 27;
        g_Balloonist.m_DialogueId = 32;
        g_Balloonist.unk_0x04 = 0;
      }
    }
    break;
  }

  case 2: {
    Vector3D vec;
    Vector3D16 shortvec;
    int lerpProgress, currentAngle, currentDist;
    if (g_Balloonist.unk_0x04 < 102) {
      lerpProgress = Sin((g_Balloonist.unk_0x04 * 2048) / 102 - 1024) + 4096;
      if (g_Balloonist.unk_0x04 == g_DeltaTime) {
        g_Balloonist.m_BalloonMoby->m_SectorIndex = -1;
        g_Balloonist.unk_0x38 = Atan2(
            g_Camera.m_Position.x - g_Balloonist.m_BalloonMoby->m_Position.x,
            g_Camera.m_Position.y - g_Balloonist.m_BalloonMoby->m_Position.y,
            1);
        VecSub(&vec, &g_Camera.m_Position,
               &g_Balloonist.m_BalloonMoby->m_Position);
        g_Balloonist.unk_0x3c = VecMagnitude(&vec, 0);
        g_Balloonist.unk_0x40 = g_Camera.m_Position.z;
        g_Balloonist.unk_0x44.x = g_Camera.m_Rotation.x;
        g_Balloonist.unk_0x44.y = g_Camera.m_Rotation.y;
        g_Balloonist.unk_0x44.z = g_Camera.m_Rotation.z;

        g_Balloonist.unk_0x50 =
            g_Balloonist.m_BalloonMoby->m_Rotation.z * 16 - 1152 & 0xfff;
        g_Balloonist.unk_0x54 = 0xe00;
        g_Balloonist.unk_0x58 = g_Balloonist.m_BalloonMoby->m_Position.z + 512;
        g_Balloonist.unk_0x5C[0] = g_Balloonist.m_BalloonMoby->m_Position.z;
        g_Balloonist.unk_0x5C[1] =
            g_Balloonist.m_BalloonistMoby->m_Position.z + 1160;
        VecCopy(&g_Balloonist.unk_0x18, &g_Spyro.m_Position);
        VecCopy(&g_Balloonist.unk_0x2C,
                &g_Balloonist.m_BalloonistMoby->m_Position);
        g_Spyro.m_BodyAnimationFrame = g_Spyro.m_NextBodyAnimationFrame;
        g_Spyro.m_NextBodyAnimation = 5;
        g_Spyro.m_NextBodyAnimationFrame = 0;
        g_Spyro.m_BodyFrameProgress = 0;
        g_Spyro.m_BodyAnimationSpeed = 7;
      }
      if (g_Balloonist.unk_0x04 < 48) {
        g_Spyro.m_Position.x =
            g_Balloonist.unk_0x18.x +
            ((g_Balloonist.unk_0x2C.x - g_Balloonist.unk_0x18.x) *
             g_Balloonist.unk_0x04) /
                48;
        g_Spyro.m_Position.y =
            g_Balloonist.unk_0x18.y +
            ((g_Balloonist.unk_0x2C.y - g_Balloonist.unk_0x18.y) *
             g_Balloonist.unk_0x04) /
                48;
        g_Spyro.m_Position.z = g_Balloonist.unk_0x18.z +
                               (Sin(g_Balloonist.unk_0x04 << 5) * 10) / 36;
        g_Spyro.m_FloorHeight = ColFindFloor(&g_Spyro.m_Position, 0x10000);
        RotVec8ToMatrix(&g_Spyro.m_BodyRotation, &g_Spyro.m_RotationMatrix, 0);
        func_80049FAC(1);
      } else {
        if (g_Balloonist.unk_0x04 - g_DeltaTime < 48) {
          g_Balloonist.unk_0x18.x = g_Balloonist.unk_0x2C.x;
          g_Balloonist.unk_0x18.y = g_Balloonist.unk_0x2C.y;
          g_Balloonist.unk_0x18.z = g_Balloonist.unk_0x18.z + 805;
          VecCopy(&g_Balloonist.unk_0x2C,
                  &g_Balloonist.m_BalloonMoby->m_Position);
          g_Spyro.m_BodyAnimationFrame = g_Spyro.m_NextBodyAnimationFrame;
          g_Spyro.m_NextBodyAnimationFrame = 0;
          g_Spyro.m_BodyFrameProgress = 0;
          g_Spyro.m_BodyAnimationSpeed = 4;
        }
        if (53 < g_Balloonist.unk_0x04 - g_DeltaTime) {
          g_Spyro.m_BodyAnimationSpeed = 7;
          g_Spyro.m_Position.x =
              g_Balloonist.unk_0x18.x +
              ((g_Balloonist.unk_0x2C.x - g_Balloonist.unk_0x18.x) *
               (g_Balloonist.unk_0x04 - 54)) /
                  48;
          g_Spyro.m_Position.y =
              g_Balloonist.unk_0x18.y +
              ((g_Balloonist.unk_0x2C.y - g_Balloonist.unk_0x18.y) *
               (g_Balloonist.unk_0x04 - 54)) /
                  48;
          g_Spyro.m_Position.z = g_Balloonist.unk_0x18.z +
                                 (Sin((g_Balloonist.unk_0x04 - 54) * 32) >> 2);
        }
      }
      if ((g_Balloonist.unk_0x50 - g_Balloonist.unk_0x38 & 0xfff) <= 2048) {
        currentAngle =
            g_Balloonist.unk_0x38 +
            (func_80017928(g_Balloonist.unk_0x50, g_Balloonist.unk_0x38) *
                 lerpProgress >>
             13);
      } else {
        currentAngle =
            g_Balloonist.unk_0x38 -
            (func_80017928(g_Balloonist.unk_0x50, g_Balloonist.unk_0x38) *
                 lerpProgress >>
             13);
      }

      currentDist = g_Balloonist.unk_0x3c +
                    (FIXED_MUL(g_Balloonist.unk_0x54 - g_Balloonist.unk_0x3c,
                               lerpProgress) >>
                     1);
      g_Camera.m_Position.x = g_Balloonist.m_BalloonMoby->m_Position.x +
                              FIXED_MUL(Cos(currentAngle), currentDist);
      g_Camera.m_Position.y = g_Balloonist.m_BalloonMoby->m_Position.y +
                              FIXED_MUL(Sin(currentAngle), currentDist);
      g_Camera.m_Position.z =
          g_Balloonist.unk_0x40 +
          ((g_Balloonist.unk_0x58 - g_Balloonist.unk_0x40) * lerpProgress >>
           13);
      VecSub(&vec, &g_Balloonist.m_BalloonMoby->m_Position,
             &g_Camera.m_Position);
      shortvec.y = Atan2(VecMagnitude(&vec, 0), -vec.z, 1);
      shortvec.z = Atan2(vec.x, vec.y, 1);
      g_Camera.m_Rotation.y =
          g_Balloonist.unk_0x44.y +
              (func_8001796C(shortvec.y, g_Balloonist.unk_0x44.y) *
                   lerpProgress >>
               13) &
          0xfff;
      g_Camera.m_Rotation.z =
          g_Balloonist.unk_0x44.z +
              (func_8001796C(shortvec.z, g_Balloonist.unk_0x44.z) *
                   lerpProgress >>
               13) &
          0xfff;
      g_Balloonist.m_BalloonMoby->m_Position.z =
          g_Balloonist.unk_0x5C[0] +
          ((g_Balloonist.unk_0x5C[1] - g_Balloonist.unk_0x5C[0]) *
               lerpProgress >>
           13);
    } else {
      g_Balloonist.m_State = 3;
      g_Balloonist.unk_0x04 = 0;
    }
    break;
  }

  case 3: {
    Vector3D vec;
    int ptrDiff;
    int *dataBuffer;
    if (0x7f >= g_Balloonist.unk_0x04) {
      if (g_Balloonist.unk_0x04 == g_DeltaTime) {
        g_Balloonist.unk_0x5C[0] = g_Balloonist.m_BalloonMoby->m_Position.z;
        g_Balloonist.unk_0x40 = g_Camera.m_Position.z;
        g_Spyro.m_Position.x = g_Balloonist.unk_0x2C.x;
        g_Spyro.m_Position.y = g_Balloonist.unk_0x2C.y;
        g_Spyro.m_Position.z = g_Balloonist.m_BalloonMoby->m_Position.z + 724;
        g_Spyro.m_NextBodyAnimation = 0;
        g_Spyro.m_BodyAnimationFrame = g_Spyro.m_NextBodyAnimationFrame;
        g_Spyro.m_BodyAnimationSpeed = 4;
        g_Spyro.m_NextBodyAnimationFrame = 0;
        g_Spyro.m_BodyFrameProgress = 0;
        g_Spyro.m_DepthSortOffset = 3;
      }
      if (g_Balloonist.unk_0x04 < 64) {
        g_Balloonist.m_BalloonMoby->m_Position.z =
            g_Balloonist.unk_0x5C[0] +
            ((Sin(g_Balloonist.unk_0x04 * 16 + 3072) + 4096) * 3 >> 2);
      } else {
        g_Balloonist.m_BalloonMoby->m_Position.z =
            g_Balloonist.m_BalloonMoby->m_Position.z + g_DeltaTime * 75;
        g_Camera.m_Position.z =
            g_Balloonist.unk_0x40 +
            ((Sin(g_Balloonist.unk_0x04 * 16 + 2048) + 4096) * 3 >> 2);
      }
      VecSub(&vec, &g_Balloonist.m_BalloonMoby->m_Position,
             &g_Camera.m_Position);
      g_Camera.m_Rotation.y = Atan2(VecMagnitude(&vec, 0), -vec.z, 1);

      g_Camera.m_Rotation.z = Atan2(vec.x, vec.y, 1);
      g_Spyro.m_Position.z = g_Balloonist.m_BalloonMoby->m_Position.z + 724;
      g_Spyro.m_BodyRotation.z = g_Balloonist.m_BalloonMoby->m_Rotation.z + 128;
    } else {
      g_Balloonist.unk_0x38 = Atan2(
          g_Camera.m_Position.x - g_Balloonist.m_BalloonMoby->m_Position.x,
          g_Camera.m_Position.y - g_Balloonist.m_BalloonMoby->m_Position.y, 1);
      VecSub(&vec, &g_Camera.m_Position,
             &g_Balloonist.m_BalloonMoby->m_Position);
      g_Balloonist.unk_0x3c = VecMagnitude(&vec, 0);
      g_Balloonist.unk_0x40 = g_Camera.m_Position.z;
      g_Balloonist.unk_0x50 =
          (912 + g_Balloonist.m_BalloonMoby->m_Rotation.z * 16) & 0xfff;
      g_Balloonist.unk_0x54 = 0x800;
      g_LoadStage = 0;
      D_8007576C = -1;
      g_HasLevelTransition = 0;
      g_PortalLevelId = 0;
      g_Balloonist.unk_0x58 = g_Balloonist.m_BalloonMoby->m_Position.z + 0x200;

      g_Balloonist.m_State = 4;
      g_Balloonist.unk_0x04 = 0;
      LoadLevel(1);
      Memcpy(&g_SonyImage.m_WorldFarQueued[106], g_Balloonist.m_BalloonMoby,
             0x58);
      g_Balloonist.m_BalloonMoby = (Moby *)&g_SonyImage.m_WorldFarQueued[106];
      if ((u_int)g_Buffers.m_LowerPolyBuffer < 0x80200000) {
        dataBuffer = (int *)((int)g_Cyclorama.m_Sectors - 0x400c);
      } else {
        dataBuffer = (int *)0x801FE000;
      }
      Memcpy(dataBuffer, g_Models[416], 0x4000);
      ptrDiff = ((int)dataBuffer - (int)g_Models[416]);
      g_Models[416] = (Model *)dataBuffer;
      g_Models[416]->m_Animations[0] =
          (AnimationHeader *)((int)g_Models[416]->m_Animations[0] + ptrDiff);
      g_Models[416]->m_Animations[0]->m_Faces =
          (void *)((int)g_Models[416]->m_Animations[0]->m_Faces + ptrDiff);
      g_Models[416]->m_Animations[0]->m_Colors =
          (void *)((int)g_Models[416]->m_Animations[0]->m_Colors + ptrDiff);
      g_Models[416]->m_Animations[0]->m_Frames[0].m.m_Data += ptrDiff;
    }
    break;
  }

  case 5: {
    Vector3D vec;
    int sineProgress;
    int angle;
    int dist;
    if (g_LoadStage < 13) {
      LoadLevel(1);
    }
    if (g_Balloonist.unk_0x04 < 0x100) {
      sineProgress = Sin(((g_Balloonist.unk_0x04 << 0xb) >> 8) - 1024) + 4096;
      if ((g_Balloonist.unk_0x38 - g_Balloonist.unk_0x50 & 0xfff) <= 2048) {
        angle = g_Balloonist.unk_0x50 +
                (func_80017928(g_Balloonist.unk_0x38, g_Balloonist.unk_0x50) *
                     sineProgress >>
                 13);
      } else {
        angle = g_Balloonist.unk_0x50 -
                (func_80017928(g_Balloonist.unk_0x38, g_Balloonist.unk_0x50) *
                     sineProgress >>
                 13);
      }
      dist = g_Balloonist.unk_0x54 +
             (FIXED_MUL(g_Balloonist.unk_0x3c - g_Balloonist.unk_0x54,
                        sineProgress) >>
              1);
      g_Camera.m_Position.x = g_Balloonist.m_BalloonMoby->m_Position.x +
                              FIXED_MUL(Cos(angle), dist);
      g_Camera.m_Position.y = g_Balloonist.m_BalloonMoby->m_Position.y +
                              FIXED_MUL(Sin(angle), dist);
      g_Camera.m_Position.z =
          g_Balloonist.unk_0x58 +
          (FIXED_MUL(g_Balloonist.unk_0x40 - g_Balloonist.unk_0x58,
                     sineProgress) >>
           1);
      VecSub(&vec, &g_Balloonist.m_BalloonMoby->m_Position,
             &g_Camera.m_Position);
      vec.z += 0x200 - (sineProgress >> 4);
      g_Camera.m_Rotation.y = Atan2(VecMagnitude(&vec, 0), -vec.z, 1);
      g_Camera.m_Rotation.z = Atan2(vec.x, vec.y, 1);
    } else if (g_LoadStage == 13) {
      g_Balloonist.m_State = 6;
      g_Balloonist.unk_0x04 = 0;
      LoadLevel(1);
    }
    break;
  }

  case 6: {
    Vector3D vec;
    if (0x7f >= g_Balloonist.unk_0x04) {
      if (g_Balloonist.unk_0x04 == g_DeltaTime) {
        g_Balloonist.unk_0x5C[0] = g_Balloonist.m_BalloonMoby->m_Position.z;
        g_Balloonist.unk_0x40 = g_Camera.m_Position.z;
      }
      if (g_Balloonist.unk_0x04 < 64) {
        g_Balloonist.m_BalloonMoby->m_Position.z -= g_DeltaTime * 75;
        g_Camera.m_Position.z =
            g_Balloonist.unk_0x40 + (Sin(-g_Balloonist.unk_0x04 * 16) * 3 >> 2);
      } else {
        if (g_Balloonist.unk_0x04 - g_DeltaTime < 64) {
          g_Balloonist.unk_0x5C[0] =
              g_Balloonist.m_BalloonMoby->m_Position.z - 75;
        }
        g_Balloonist.m_BalloonMoby->m_Position.z =
            g_Balloonist.unk_0x5C[0] +
            (Sin(1024 - g_Balloonist.unk_0x04 * 16) * 3 >> 2);
      }
      VecSub(&vec, &g_Balloonist.m_BalloonMoby->m_Position,
             &g_Camera.m_Position);
      g_Camera.m_Rotation.y = Atan2(VecMagnitude(&vec, 0), -vec.z, 1);
      g_Camera.m_Rotation.z = Atan2(vec.x, vec.y, 1);
      g_Spyro.m_Position.z = g_Balloonist.m_BalloonMoby->m_Position.z + 724;
      g_Spyro.m_BodyRotation.z = g_Balloonist.m_BalloonMoby->m_Rotation.z + 128;

    } else {
      g_Balloonist.m_State = 7;
      g_Balloonist.unk_0x04 = 0;
      VecCopy(&g_Balloonist.unk_0x18, &g_Spyro.m_Position);
      g_Balloonist.unk_0x2C.x = D_8006EADC[g_Balloonist.m_Homeworld][0];
      g_Balloonist.unk_0x2C.y = D_8006EADC[g_Balloonist.m_Homeworld][1];
      g_Balloonist.unk_0x2C.z = g_Spyro.m_Position.z;
      g_Balloonist.unk_0x2C.z =
          ColFindFloor(&g_Balloonist.unk_0x2C, 0x10000) + 356;
      g_Spyro.m_NextBodyAnimation = 5;
      g_Spyro.m_BodyAnimationFrame = g_Spyro.m_NextBodyAnimationFrame;
      g_Spyro.m_NextBodyAnimationFrame = 0;
      g_Spyro.m_BodyFrameProgress = 0;
      g_Spyro.m_BodyAnimationSpeed = 6;
    }
    break;
  }

  case 7: {
    int pad[2];
    if (g_Balloonist.unk_0x04 < 64) {
      g_Spyro.m_Position.x =
          g_Balloonist.unk_0x18.x +
          ((g_Balloonist.unk_0x2C.x - g_Balloonist.unk_0x18.x) *
               g_Balloonist.unk_0x04 >>
           6);
      g_Spyro.m_Position.y =
          g_Balloonist.unk_0x18.y +
          ((g_Balloonist.unk_0x2C.y - g_Balloonist.unk_0x18.y) *
               g_Balloonist.unk_0x04 >>
           6);
      g_Spyro.m_Position.z =
          g_Balloonist.unk_0x2C.z +
          (Sin(g_Balloonist.unk_0x04 * 24 + 512) *
           (g_Balloonist.unk_0x18.z - g_Balloonist.unk_0x2C.z)) /
              2896;
      g_Spyro.m_FloorHeight = ColFindFloor(&g_Spyro.m_Position, 0x10000);
      RotVec8ToMatrix(&g_Spyro.m_BodyRotation, &g_Spyro.m_RotationMatrix, 0);
      func_80049FAC(1);
      if (0x1f < g_Balloonist.unk_0x04) {
        g_Balloonist.m_BalloonMoby->m_Position.z +=
            g_Balloonist.unk_0x04 * g_DeltaTime;
      }
    } else {
      VecCopy(&g_Spyro.m_Position, &g_Balloonist.unk_0x2C);
      SpyroReset(1);
      g_Spyro.m_noGamepadUpdateFrames = 16;
      g_Camera.m_Focus = &g_Spyro.m_Position;
      g_Camera.m_State = 0;
      g_Camera.unk_0xC0 = 0;
      g_Camera.m_SphericalPreset = &D_8006C8BC;
      g_Camera.m_FocusRotation = g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;
      func_80033F08(&g_Camera.m_Position);
      Memcpy(&D_8006C8BC, &g_Camera.m_Simulation, 24);
      D_8006C8BC.m_Coords.azimuth =
          D_8006C8BC.m_Coords.azimuth + g_Camera.m_FocusRotation & 0xfff;
      func_80034358();
      HudReset(0);
      g_Gamestate = 0;
      g_StateSwitch = 1;
      g_ScreenBorderEnabled = 0;
      SpecularReset();
    }
    break;
  }
  }
}

void NAME_OVERLAY_FUNCTION(BalloonistDraw)(void) {
  if (g_Balloonist.m_State <= 3) {
    if (g_Balloonist.m_State <= 1) {
      Vector3D vec1;
      Vector3D vec2;
      char buffer[32];
      Moby *hudmobyptr;
      int i;

      hudmobyptr = g_HudMobys;
      sprintf(buffer, "%s THE BALLOONIST",
              g_BalloonistNames[g_LevelId / 10 - 1]);
      vec1.x = 0x108 - strlen(buffer) * 8;
      vec1.y = 0xcc;
      vec1.z = 0x1100;
      vec2.x = 0x10;
      vec2.y = 0x1;
      vec2.z = 0x1400;
      func_800181AC(buffer, &vec1, &vec2, 0x12, 0xb);
      hudmobyptr--;
      for (i = 0; (int)g_HudMobys <= (int)hudmobyptr; i++) {
        hudmobyptr->m_Rotation.z =
            COSINE_8((g_Balloonist.unk_0x04 * 4 + (i * 12) & 0xff)) >> 8;
        hudmobyptr--;
      }
    }
    if (g_Balloonist.m_State == 1) {
      if (g_Balloonist.m_DialogueId <= 29 || g_Balloonist.m_DialogueId >= 33) {
        Vector3D vec1;
        Vector3D vec2;
        Moby *hudmobyptr;
        int i;

        func_8001860C(0x48, 0x1b8, 0x1c, 0x68);
        hudmobyptr = g_HudMobys;
        vec1.y = 0x2c;
        vec1.z = 0x1100;
        vec2.x = 0x10;
        vec2.y = 0x1;
        vec2.z = 0x1400;
        for (i = g_BalloonistDialogueIndices[g_Balloonist.m_DialogueId];
             i < g_BalloonistDialogueIndices[g_Balloonist.m_DialogueId + 1];
             i++) {
          vec1.x = 0x5e;
          func_800181AC(g_BalloonistDialogue[i], &vec1, &vec2, 0x12, 0xb);
          vec1.y += 0x12;
        }
        if (g_Balloonist.unk_0x04 < 80) {
          if ((int)g_HudMobys <= (int)(hudmobyptr - g_Balloonist.unk_0x04))
            g_HudMobys = hudmobyptr - g_Balloonist.unk_0x04;
        }
        hudmobyptr--;
        for (i = 0; (int)g_HudMobys <= (int)hudmobyptr; i++) {
          hudmobyptr->m_Rotation.z =
              COSINE_8((g_Balloonist.unk_0x04 * 4 + (i * 12) & 0xff)) >> 8;
          hudmobyptr--;
        }
        if (g_Balloonist.unk_0x04 > 0x4f) {
          vec1.x = 0x19c;
          vec1.y = 0x60;
          vec1.z = 0x1100;
          func_80018534(&vec1, g_Balloonist.unk_0x04, 0);
        }
      } else if (g_Balloonist.m_DialogueId == 30) {
        Vector3D vec1;
        Vector3D vec2;
        Moby *hudmobyptr;
        int someflag;
        int i;
        int j;

        vec2.x = 0xe;
        vec2.z = 0x1600;
        vec1.z = 0x1400;
        vec1.x = 0xf0;
        vec2.y = 0x1;
        vec1.y = 0x24;

        if (g_Balloonist.m_DialogueTopStr == 0) {
          func_800181AC("HOP ON, SPYRO!", &vec1, &vec2, 0x10, 0xb);
        } else if (g_Balloonist.m_DialogueTopStr == 1) {
          func_800181AC("NEED A LIFT?", &vec1, &vec2, 0x10, 0xb);
        } else {
          func_800181AC("WHERE TO, SPYRO?", &vec1, &vec2, 0x10, 0xb);
        }
        vec1.x = 0x110;
        vec1.y += 0x14;
        hudmobyptr = g_HudMobys - 1;
        func_800181AC("STAY HERE", &vec1, &vec2, 0x10, 0xb);
        vec1.y += 0xf;
        if (g_Balloonist.unk_0x08 == 0) {
          for (i = 0; g_HudMobys <= hudmobyptr; i++) {
            hudmobyptr->m_Rotation.z =
                COSINE_8((g_Balloonist.unk_0x04 * 4 + (i * 12) & 0xff)) >> 8;
            hudmobyptr--;
          }
        }
        someflag = 1;
        for (i = 0; i < 6; i++) {
          if (g_LevelId / 10 - 1 != i && D_800758D0[i] == 2) {
            vec1.x = 0x110;
            hudmobyptr = g_HudMobys - 1;
            func_800181AC(g_HomeworldNames[i], &vec1, &vec2, 0x10, 0xb);
            vec1.y += 0xf;
            if (g_Balloonist.unk_0x08 == someflag) {
              for (j = 0; g_HudMobys <= hudmobyptr; j++) {
                hudmobyptr->m_Rotation.z =
                    COSINE_8((g_Balloonist.unk_0x04 * 4 + (j * 12) & 0xff)) >>
                    8;
                hudmobyptr--;
              }
            }
            someflag++;
          }
        }
        func_8001860C(0xe0, 0x1d8, 0x19, someflag * 0xf + 0x33);
        func_8001844C(0xf0, 0x2e, 0x1a0, 0x2e);
        vec1.x = 0xf4;
        vec1.y = g_Balloonist.unk_0x08 * 0xf + 0x36;
        vec1.z = 0x1100;
        func_80018534(&vec1, g_Balloonist.unk_0x04, 0);
      } else if (g_Balloonist.m_DialogueId == 31 ||
                 g_Balloonist.m_DialogueId == 32) {
        Vector3D vec1;
        Vector3D vec2;
        char buffer[32];
        Moby *hudmobyptr;
        int i;

        func_8001860C(0x48, 0x1b8, 0x1c, 0x66);
        func_8001844C(100, 0x37, 0x184, 0x37);
        vec1.x = 0x60;
        vec1.y = g_Balloonist.unk_0x08 * 0x13 + 0x43;
        vec1.z = 0x1100;
        func_80018534(&vec1, g_Balloonist.unk_0x04, 0);
        vec2.x = 0x10;
        vec2.z = 0x1400;
        vec1.y = 0x2c;
        vec2.y = 1;
        vec1.z = 0x1100;
        vec1.x = 0x60;

        if (g_Balloonist.m_DialogueId == 31)
          func_800181AC("ARE YOU READY TO GO?", &vec1, &vec2, 0x12, 0xb);
        else
          func_800181AC("WOULD YOU LIKE TO GO?", &vec1, &vec2, 0x12, 0xb);
        vec1.x = 0x80;
        vec1.y += 0x19;
        hudmobyptr = g_HudMobys - 1;
        func_800181AC("STAY HERE", &vec1, &vec2, 0x12, 0xb);
        vec1.y += 0x13;
        if (g_Balloonist.unk_0x08 == 0) {
          for (i = 0; g_HudMobys <= hudmobyptr; i++) {
            hudmobyptr->m_Rotation.z =
                COSINE_8((g_Balloonist.unk_0x04 * 4 + (i * 12) & 0xff)) >> 8;
            hudmobyptr--;
          }
        }
        vec1.x = 0x80;
        hudmobyptr = g_HudMobys - 1;
        if (g_Balloonist.m_DialogueId == 31) {
          sprintf(buffer, "GO TO %s", g_HomeworldNames[g_LevelId / 10]);
        } else {
          sprintf(buffer, "GO TO %s",
                  g_HomeworldNames[7 + (g_NextLevelId / 10 - 1) * 6 +
                                   g_NextLevelId % 10]);
        }

        func_800181AC(buffer, &vec1, &vec2, 18, 11);

        if (g_Balloonist.unk_0x08 == 1) {
          for (i = 0; g_HudMobys <= hudmobyptr; i++) {
            hudmobyptr->m_Rotation.z =
                COSINE_8((g_Balloonist.unk_0x04 * 4 + (i * 12) & 0xff)) >> 8;
            hudmobyptr--;
          }
        }
      }
    }

    func_800521C0();
    func_80019698();

    if (g_Balloonist.m_State <= 1) {
      g_SonyImage.m_ShadedMobys[0] = 0;
      func_80018880();
      func_80022A2C();
    }
    func_8002B9CC();
    func_80050BD0();
    func_800573C8();
  } else {
    Moby **ptr;
    func_800521C0();
    ptr = (Moby **)&g_SonyImage.u.m_Buf[0];
    while (*ptr)
      ptr++;
    ptr[0] = g_Balloonist.m_BalloonMoby;
    ptr[1] = 0;
    func_80019698();
    func_8002B9CC();
    func_80050BD0();
    func_800573C8();
  }
}
