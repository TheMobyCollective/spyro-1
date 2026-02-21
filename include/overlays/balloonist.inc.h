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
#include "variables.h"

#include <rand.h>
#include <stdio.h>
#include <strings.h>

extern int g_ScreenBorderEnabled; // Is the screen border enabled
extern int D_800756C0;
void func_80049FAC(int);
void func_80048D10(int);
int func_8001796C(int, int);

extern SphericalCoordsOffset D_8006C8BC;
extern int D_8006EADC[9][2]; // BalloonArrivalJumpoffXY;

void NAME_OVERLAY_FUNCTION(Balloonist1)(Moby *pBalloonist) {
  int *props;
  Vector3D vec;
  props = (int *)pBalloonist->m_Props;

  g_Gamestate = GS_Balloonist;
  D_800777E8.m_State = 0;
  D_800777E8.unk_0x04 = 0;
  D_800777E8.unk_0x08 = 0;
  D_800777E8.m_BalloonistMoby = pBalloonist;
  D_800777E8.m_BalloonMoby = &g_LevelMobys[props[0]];
  g_ScreenBorderEnabled = 1;
  g_StateSwitch = 1;
  D_800777E8.unk_0x38 =
      Atan2(g_Camera.m_Position.x - pBalloonist->m_Position.x,
            g_Camera.m_Position.y - pBalloonist->m_Position.y, 1);
  VecSub(&vec, &g_Camera.m_Position, &pBalloonist->m_Position);
  D_800777E8.unk_0x3c = VecMagnitude(&vec, 0);
  D_800777E8.unk_0x40 = g_Camera.m_Position.z;
  D_800777E8.unk_0x50 = (pBalloonist->m_Rotation.z * 16 - 0x312) & 0xFFF;
  D_800777E8.unk_0x54 = 0x52E;
  D_800777E8.unk_0x58 = pBalloonist->m_Position.z + 0x58F;
}

void NAME_OVERLAY_FUNCTION(Balloonist2)(void) {
  func_8002D02C();
  g_Spyro.unk_0x1b4 = 0;
  g_Spyro.m_headRotation.z = 0;
  if (g_Sparx != nullptr) {
    g_Sparx->m_RenderRadius = 16;
  }
}

void NAME_OVERLAY_FUNCTION(Balloonist3)(void) {
  if (D_800777E8.m_State < 4) {
    Moby **mobyList = (Moby **)&g_SonyImage.u.m_Buf[0x400];
    mobyList[0] = D_800777E8.m_BalloonistMoby;
    mobyList[1] = 0;
    func_800522C0(mobyList, 0);
  }

  switch (D_800777E8.m_State) {
  case 0: {
    Vector3D vec;
    Vector3D16 shortvec;
    int lerpProgress, interpAngle, interpRadius;

    if (D_800777E8.unk_0x04 < 96) {
      lerpProgress = Sin((D_800777E8.unk_0x04 << 11) / 96 - 0x400) + 0x1000;

      if (D_800777E8.unk_0x04 == g_DeltaTime) {
        if (g_Sparx != nullptr) {
          g_Sparx->m_RenderRadius = 0;
          g_Sparx->m_WasDrawn = 0;
          if (((MobySparxProps *)g_Sparx->m_Props)->glow != 0) {
            func_80058B60(((MobySparxProps *)g_Sparx->m_Props)->glow);
            ((MobySparxProps *)g_Sparx->m_Props)->glow = 0;
          }
        }
        g_SavedFairyKissTimer = g_SpyroFlame.m_FairyKissTimer;
        func_8004AC24(1);

        g_Spyro.m_bodyAnimation = 1;
        g_Spyro.m_nextBodyAnimation = 1;
        g_Spyro.m_nextBodyAnimationFrame = 1;

        VecCopy(&D_800777E8.unk_0x18, &g_Spyro.m_Position);

        D_800777E8.unk_0x2C.x = 0x4a0;
        D_800777E8.unk_0x2C.y = 0;
        D_800777E8.unk_0x2C.z = 0x164;

        VecRotateByMatrix(
            (MATRIX *)&D_800777E8.m_BalloonistMoby->m_RotationMatrix,
            &D_800777E8.unk_0x2C, &D_800777E8.unk_0x2C);
        VecAdd(&D_800777E8.unk_0x2C, &D_800777E8.unk_0x2C,
               &D_800777E8.m_BalloonistMoby->m_Position);

        D_800777E8.unk_0x30 = g_Spyro.m_bodyRotation.z << 4;
        VecSub(&vec, &D_800777E8.unk_0x2C, &D_800777E8.unk_0x18);
        D_800777E8.unk_0x34 = Atan2(vec.x, vec.y, 1);
      }

      if (D_800777E8.unk_0x04 < 24) {
        int temp = Sin((D_800777E8.unk_0x04 << 11) / 24 - 0x400) + 0x1000;
        if ((D_800777E8.unk_0x34 - D_800777E8.unk_0x30 & 0xfff) <= 0x800) {
          g_Spyro.m_bodyRotation.z =
              (D_800777E8.unk_0x30 +
               (func_80017928(D_800777E8.unk_0x34, D_800777E8.unk_0x30) *
                    temp >>
                13)) >>
              4;
        } else {
          g_Spyro.m_bodyRotation.z =
              (D_800777E8.unk_0x30 -
               (func_80017928(D_800777E8.unk_0x34, D_800777E8.unk_0x30) *
                    temp >>
                13)) >>
              4;
        }
        g_Spyro.m_bodyAnimationSpeed = 8;
      } else if (D_800777E8.unk_0x04 < 72) {
        int temp =
            (Sin(((D_800777E8.unk_0x04 - 24) * 0x800) / 48 - 0x400) + 0x1000);
        VecSub(&vec, &D_800777E8.unk_0x2C, &D_800777E8.unk_0x18);
        VecMult(&vec, &vec, temp);
        VecShiftRight(&vec, 13);
        VecAdd(&g_Spyro.m_Position, &D_800777E8.unk_0x18, &vec);

        g_Spyro.m_bodyAnimationSpeed = VecMagnitude(&vec, 0) >> 1;
        if (g_Spyro.m_bodyAnimationSpeed < 4) {
          g_Spyro.m_bodyAnimationSpeed = 4;
        }
        if (g_Spyro.m_bodyAnimationSpeed > 0x10) {
          g_Spyro.m_bodyAnimationSpeed = 0x10;
        }
      } else {
        int temp =
            Sin(((D_800777E8.unk_0x04 - 72) * 0x800) / 24 - 0x400) + 0x1000;
        if (D_800777E8.unk_0x04 - g_DeltaTime < 72) {
          D_800777E8.unk_0x30 = g_Spyro.m_bodyRotation.z << 4;
          D_800777E8.unk_0x34 =
              D_800777E8.m_BalloonistMoby->m_Rotation.z * 16 - 0x800 & 0xfff;
          g_Spyro.m_nextBodyAnimation = 3;
          g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;
          g_Spyro.m_nextBodyAnimationFrame = 0;
          g_Spyro.m_bodyFrameProgress = 0;
          g_Spyro.m_bodyAnimationSpeed = 8;
        }
        if (0x800 >= ((D_800777E8.unk_0x34 - D_800777E8.unk_0x30) & 0xfff)) {
          g_Spyro.m_bodyRotation.z =
              (D_800777E8.unk_0x30 +
               (func_80017928(D_800777E8.unk_0x34, D_800777E8.unk_0x30) *
                    temp >>
                13)) >>
              4;
        } else {
          g_Spyro.m_bodyRotation.z =
              (D_800777E8.unk_0x30 -
               (func_80017928(D_800777E8.unk_0x34, D_800777E8.unk_0x30) *
                    temp >>
                13)) >>
              4;
        }
        g_Spyro.m_bodyAnimationSpeed = 8;
      }

      g_Spyro.m_bodyRotation.x = 0;
      g_Spyro.m_bodyRotation.y = 0;
      g_Spyro.m_surfaceBelowSpyro = func_8004D5EC(&g_Spyro.m_Position, 0x10000);
      RotVec8ToMatrix(&g_Spyro.m_bodyRotation, &g_Spyro.m_RotationMatrix, 0);
      func_80049FAC(1);
      func_80048D10(g_DeltaTime);

      if ((D_800777E8.unk_0x50 - D_800777E8.unk_0x38 & 0xfff) <= 0x800) {
        interpAngle = D_800777E8.unk_0x38 +
                      (func_80017928(D_800777E8.unk_0x50, D_800777E8.unk_0x38) *
                           lerpProgress >>
                       13);
      } else {
        interpAngle = D_800777E8.unk_0x38 -
                      (func_80017928(D_800777E8.unk_0x50, D_800777E8.unk_0x38) *
                           lerpProgress >>
                       13);
      }

      interpRadius =
          (D_800777E8.unk_0x3c +
           ((D_800777E8.unk_0x54 - D_800777E8.unk_0x3c) * lerpProgress >> 13));
      g_Camera.m_Position.x = D_800777E8.m_BalloonistMoby->m_Position.x +
                              (Cos(interpAngle) * interpRadius >> 12);
      g_Camera.m_Position.y = D_800777E8.m_BalloonistMoby->m_Position.y +
                              (Sin(interpAngle) * interpRadius >> 12);
      g_Camera.m_Position.z =
          D_800777E8.unk_0x40 +
          (((D_800777E8.unk_0x58 - D_800777E8.unk_0x40) * lerpProgress) >> 13);

      vec.x = 0x220;
      vec.y = 0;
      vec.z = 0x340;
      VecRotateByMatrix(
          (MATRIX *)&D_800777E8.m_BalloonistMoby->m_RotationMatrix, &vec, &vec);
      VecAdd(&vec, &vec, &D_800777E8.m_BalloonistMoby->m_Position);
      VecSub(&vec, &vec, &g_Camera.m_Position);

      if (D_800777E8.unk_0x04 < 32) {
        shortvec.x = 0;
        shortvec.y = Atan2(VecMagnitude(&vec, 0), -vec.z, 1);
        shortvec.z = Atan2(vec.x, vec.y, 1);
        g_Camera.m_Rotation.x =
            g_Camera.m_Rotation.x +
                (func_8001796C(shortvec.x, g_Camera.m_Rotation.x) *
                     D_800777E8.unk_0x04 >>
                 5) &
            0xfff;
        g_Camera.m_Rotation.y =
            g_Camera.m_Rotation.y +
                (func_8001796C(shortvec.y, g_Camera.m_Rotation.y) *
                     D_800777E8.unk_0x04 >>
                 5) &
            0xfff;
        g_Camera.m_Rotation.z =
            g_Camera.m_Rotation.z +
                (func_8001796C(shortvec.z, g_Camera.m_Rotation.z) *
                     D_800777E8.unk_0x04 >>
                 5) &
            0xfff;
      } else {
        g_Camera.m_Rotation.x = 0;
        g_Camera.m_Rotation.y = Atan2(VecMagnitude(&vec, 0), -vec.z, 1);
        g_Camera.m_Rotation.z = Atan2(vec.x, vec.y, 1);
      }
      (*g_UpdateParticle)(g_DeltaTime);
      func_8005637C();
    } else {
      g_Camera.m_Position.x =
          D_800777E8.m_BalloonistMoby->m_Position.x +
          ((Cos(D_800777E8.unk_0x50) * D_800777E8.unk_0x54) >> 12);
      g_Camera.m_Position.y =
          D_800777E8.m_BalloonistMoby->m_Position.y +
          ((Sin(D_800777E8.unk_0x50) * D_800777E8.unk_0x54) >> 12);
      g_Camera.m_Position.z = D_800777E8.unk_0x58;

      VecCopy(&g_Spyro.m_Position, &D_800777E8.unk_0x2C);

      g_Spyro.m_bodyRotation.z = D_800777E8.unk_0x34 >> 4;
      g_Spyro.m_nextBodyAnimation = 0;
      g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;
      g_Spyro.m_nextBodyAnimationFrame = 0;
      g_Spyro.m_bodyFrameProgress = 0;
      g_Spyro.m_bodyAnimationSpeed = 4;
      D_800777E8.m_State = 1;
      D_800777E8.unk_0x04 = 0;
    }
    break;
  }

  case 1: {
    if (D_800777E8.m_DialogueId < 30) {
      if ((g_Pad.m_Down & (PAD_CROSS | PAD_START | PAD_RIGHT | PAD_DOWN)) &&
          (D_800777E8.unk_0x04 > 80)) {
        int dialog = D_800777E8.m_DialogueId % 6;
        if (dialog == 0) {
          D_800777E8.m_DialogueId++;
        } else if (dialog < 3) {
          if ((D_800777E8.m_DialogueId < 3) && (D_800758D0[1] < 2)) {
            (*D_800758A8)();
          } else if (D_800777E8.m_DialogueId == 14) {
            while (D_800777E8.m_DialogueId == 14) {
              int random;
              random = rand() % 5;
              if (random == 0 && g_LevelEggCount[1] == 0) // Stone Hill
                D_800777E8.m_DialogueId = 33;
              else if (random == 1 && g_LevelEggCount[7] == 0) // Dry Canyon
                D_800777E8.m_DialogueId = 34;
              else if (random == 2 && g_LevelEggCount[8] == 0) // Cliff Town
                D_800777E8.m_DialogueId = 35;
              else if (random == 3 && g_LevelEggCount[12] < 2) // Magic Crafters
                D_800777E8.m_DialogueId = 36;
              else if (random == 4 && g_LevelEggCount[15] == 0) // Wizard Peak
                D_800777E8.m_DialogueId = 37;
            }
          } else {
            D_800777E8.m_DialogueId = 30;
          }
        } else if (dialog == 3) {
          D_800777E8.m_DialogueId += 2;
        } else if (dialog == 4) {
          D_800777E8.m_DialogueId++;
        } else {
          D_800777E8.m_DialogueId = 31;
        }
        D_800777E8.unk_0x04 = 0;
      }
    } else if (D_800777E8.m_DialogueId == 30) {
      int homeworldId = 1;

      while (homeworldId < 6 && D_800758D0[homeworldId] == 2) {
        homeworldId++;
      }
      if (g_Pad.m_Down & PAD_UP) {
        D_800777E8.unk_0x08--;
        if (D_800777E8.unk_0x08 < 0) {
          D_800777E8.unk_0x08 = homeworldId - 1;
        }
        D_800777E8.unk_0x04 = 0x20;
        PlaySound(g_Spu.m_SoundTable->menuCursor, 0, 0x10, 0);
      } else if (g_Pad.m_Down & PAD_DOWN) {
        D_800777E8.unk_0x08++;
        if (homeworldId <= D_800777E8.unk_0x08) {
          D_800777E8.unk_0x08 = 0;
        }
        D_800777E8.unk_0x04 = 0x20;
        PlaySound(g_Spu.m_SoundTable->menuCursor, 0, 0x10, 0);
      }
      if ((g_Pad.m_Down & (PAD_CROSS | PAD_START)) &&
          D_800777E8.unk_0x04 >= 31) {
        if (D_800777E8.unk_0x08 == 0) {
          (*D_800758A8)();
        } else {
          func_80056B28(0);
          D_800777E8.m_State = 2;
          D_800777E8.unk_0x04 = 0;
          g_NextLevelId = D_800777E8.unk_0x08 * 10;
          if (g_LevelId <= g_NextLevelId) {
            g_NextLevelId = g_NextLevelId + 10;
          }
          D_800777E8.m_Homeworld = g_NextLevelId / 10 - 1;
        }
      }
    } else if (D_800777E8.m_DialogueId == 31 || D_800777E8.m_DialogueId == 32) {
      if (g_Pad.m_Down & (PAD_UP | PAD_DOWN)) {
        D_800777E8.unk_0x04 = 0x20;
        D_800777E8.unk_0x08 = 1 - D_800777E8.unk_0x08;
        PlaySound(g_Spu.m_SoundTable->menuCursor, 0, 0x10, 0);
      }

      if ((g_Pad.m_Down & (PAD_CROSS | PAD_START)) &&
          D_800777E8.unk_0x04 >= 0x1f) {
        if (D_800777E8.unk_0x08 == 0) {
          if (D_800777E8.m_DialogueId == 31) {
            (*D_800758A8)();
          } else {
            D_800777E8.m_DialogueId = 30;
            D_800777E8.unk_0x08 = 0;
            D_800777E8.m_DialogueTopStr = 1;
          }
        } else {
          func_80056B28(0);
          D_800777E8.m_State = 2;
          D_800777E8.unk_0x04 = 0;
          if (D_800777E8.m_DialogueId == 31) {
            g_NextLevelId = g_LevelId + 10;
            D_800777E8.m_Homeworld = (g_LevelId + 10) / 10 - 1;
          }
        }
      }
    } else if ((g_Pad.m_Down &
                (PAD_CROSS | PAD_START | PAD_RIGHT | PAD_DOWN)) &&
               D_800777E8.unk_0x04 > 80) {
      if ((D_800777E8.m_DialogueId == 36) || (D_800777E8.m_DialogueId == 38)) {
        D_800777E8.m_DialogueId = 30;
        D_800777E8.unk_0x08 = 0;
        D_800777E8.m_DialogueTopStr = 1;
      } else if (D_800777E8.m_DialogueId == 37) {
        D_800777E8.m_DialogueId = 38;
        D_800777E8.unk_0x04 = 0;
      } else {
        if (D_800777E8.m_DialogueId == 33) {
          g_NextLevelId = 11;
        } else if (D_800777E8.m_DialogueId == 34) {
          g_NextLevelId = 21;
        } else if (D_800777E8.m_DialogueId == 35) {
          g_NextLevelId = 22;
        }
        D_800777E8.m_Homeworld = D_800777E8.m_DialogueId - 27;
        D_800777E8.m_DialogueId = 32;
        D_800777E8.unk_0x04 = 0;
      }
    }
    break;
  }

  case 2: {
    Vector3D vec;
    Vector3D16 shortvec;
    int lerpProgress, currentAngle, currentDist;
    if (D_800777E8.unk_0x04 < 102) {
      lerpProgress = Sin((D_800777E8.unk_0x04 * 0x800) / 0x66 - 0x400) + 0x1000;
      if (D_800777E8.unk_0x04 == g_DeltaTime) {
        D_800777E8.m_BalloonMoby->m_SectorIndex = -1;
        D_800777E8.unk_0x38 = Atan2(
            g_Camera.m_Position.x - D_800777E8.m_BalloonMoby->m_Position.x,
            g_Camera.m_Position.y - D_800777E8.m_BalloonMoby->m_Position.y, 1);
        VecSub(&vec, &g_Camera.m_Position,
               &D_800777E8.m_BalloonMoby->m_Position);
        D_800777E8.unk_0x3c = VecMagnitude(&vec, 0);
        D_800777E8.unk_0x40 = g_Camera.m_Position.z;
        D_800777E8.unk_0x44.x = g_Camera.m_Rotation.x;
        D_800777E8.unk_0x44.y = g_Camera.m_Rotation.y;
        D_800777E8.unk_0x44.z = g_Camera.m_Rotation.z;

        D_800777E8.unk_0x50 =
            D_800777E8.m_BalloonMoby->m_Rotation.z * 0x10 - 0x480 & 0xfff;
        D_800777E8.unk_0x54 = 0xe00;
        D_800777E8.unk_0x58 = D_800777E8.m_BalloonMoby->m_Position.z + 0x200;
        D_800777E8.unk_0x5C[0] = D_800777E8.m_BalloonMoby->m_Position.z;
        D_800777E8.unk_0x5C[1] =
            D_800777E8.m_BalloonistMoby->m_Position.z + 0x488;
        VecCopy(&D_800777E8.unk_0x18, &g_Spyro.m_Position);
        VecCopy(&D_800777E8.unk_0x2C, &D_800777E8.m_BalloonistMoby->m_Position);
        g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;
        g_Spyro.m_nextBodyAnimation = 5;
        g_Spyro.m_nextBodyAnimationFrame = 0;
        g_Spyro.m_bodyFrameProgress = 0;
        g_Spyro.m_bodyAnimationSpeed = 7;
      }
      if (D_800777E8.unk_0x04 < 48) {
        g_Spyro.m_Position.x =
            D_800777E8.unk_0x18.x +
            ((D_800777E8.unk_0x2C.x - D_800777E8.unk_0x18.x) *
             D_800777E8.unk_0x04) /
                48;
        g_Spyro.m_Position.y =
            D_800777E8.unk_0x18.y +
            ((D_800777E8.unk_0x2C.y - D_800777E8.unk_0x18.y) *
             D_800777E8.unk_0x04) /
                48;
        g_Spyro.m_Position.z =
            D_800777E8.unk_0x18.z + (Sin(D_800777E8.unk_0x04 << 5) * 10) / 0x24;
        g_Spyro.m_surfaceBelowSpyro =
            func_8004D5EC(&g_Spyro.m_Position, 0x10000);
        RotVec8ToMatrix(&g_Spyro.m_bodyRotation, &g_Spyro.m_RotationMatrix, 0);
        func_80049FAC(1);
      } else {
        if (D_800777E8.unk_0x04 - g_DeltaTime < 48) {
          D_800777E8.unk_0x18.x = D_800777E8.unk_0x2C.x;
          D_800777E8.unk_0x18.y = D_800777E8.unk_0x2C.y;
          D_800777E8.unk_0x18.z = D_800777E8.unk_0x18.z + 0x325;
          VecCopy(&D_800777E8.unk_0x2C, &D_800777E8.m_BalloonMoby->m_Position);
          g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;
          g_Spyro.m_nextBodyAnimationFrame = 0;
          g_Spyro.m_bodyFrameProgress = 0;
          g_Spyro.m_bodyAnimationSpeed = 4;
        }
        if (53 < D_800777E8.unk_0x04 - g_DeltaTime) {
          g_Spyro.m_bodyAnimationSpeed = 7;
          g_Spyro.m_Position.x =
              D_800777E8.unk_0x18.x +
              ((D_800777E8.unk_0x2C.x - D_800777E8.unk_0x18.x) *
               (D_800777E8.unk_0x04 - 54)) /
                  48;
          g_Spyro.m_Position.y =
              D_800777E8.unk_0x18.y +
              ((D_800777E8.unk_0x2C.y - D_800777E8.unk_0x18.y) *
               (D_800777E8.unk_0x04 - 54)) /
                  48;
          g_Spyro.m_Position.z = D_800777E8.unk_0x18.z +
                                 (Sin((D_800777E8.unk_0x04 - 54) * 32) >> 2);
        }
      }
      if ((D_800777E8.unk_0x50 - D_800777E8.unk_0x38 & 0xfff) < 0x801) {
        currentAngle =
            D_800777E8.unk_0x38 +
            (func_80017928(D_800777E8.unk_0x50, D_800777E8.unk_0x38) *
                 lerpProgress >>
             13);
      } else {
        currentAngle =
            D_800777E8.unk_0x38 -
            (func_80017928(D_800777E8.unk_0x50, D_800777E8.unk_0x38) *
                 lerpProgress >>
             13);
      }
      currentDist =
          D_800777E8.unk_0x3c +
          ((D_800777E8.unk_0x54 - D_800777E8.unk_0x3c) * lerpProgress >> 13);
      g_Camera.m_Position.x = D_800777E8.m_BalloonMoby->m_Position.x +
                              (Cos(currentAngle) * currentDist >> 0xc);
      g_Camera.m_Position.y = D_800777E8.m_BalloonMoby->m_Position.y +
                              (Sin(currentAngle) * currentDist >> 0xc);
      g_Camera.m_Position.z =
          D_800777E8.unk_0x40 +
          ((D_800777E8.unk_0x58 - D_800777E8.unk_0x40) * lerpProgress >> 13);
      VecSub(&vec, &D_800777E8.m_BalloonMoby->m_Position, &g_Camera.m_Position);
      shortvec.y = Atan2(VecMagnitude(&vec, 0), -vec.z, 1);
      shortvec.z = Atan2(vec.x, vec.y, 1);
      g_Camera.m_Rotation.y =
          D_800777E8.unk_0x44.y +
              (func_8001796C(shortvec.y, D_800777E8.unk_0x44.y) *
                   lerpProgress >>
               13) &
          0xfff;
      g_Camera.m_Rotation.z =
          D_800777E8.unk_0x44.z +
              (func_8001796C(shortvec.z, D_800777E8.unk_0x44.z) *
                   lerpProgress >>
               13) &
          0xfff;
      D_800777E8.m_BalloonMoby->m_Position.z =
          D_800777E8.unk_0x5C[0] +
          ((D_800777E8.unk_0x5C[1] - D_800777E8.unk_0x5C[0]) * lerpProgress >>
           13);
    } else {
      D_800777E8.m_State = 3;
      D_800777E8.unk_0x04 = 0;
    }
    break;
  }

  case 3: {
    Vector3D vec;
    int ptrDiff;
    int *dataBuffer;
    if (0x7f >= D_800777E8.unk_0x04) {
      if (D_800777E8.unk_0x04 == g_DeltaTime) {
        D_800777E8.unk_0x5C[0] = D_800777E8.m_BalloonMoby->m_Position.z;
        D_800777E8.unk_0x40 = g_Camera.m_Position.z;
        g_Spyro.m_Position.x = D_800777E8.unk_0x2C.x;
        g_Spyro.m_Position.y = D_800777E8.unk_0x2C.y;
        g_Spyro.m_Position.z = D_800777E8.m_BalloonMoby->m_Position.z + 0x2d4;
        g_Spyro.m_nextBodyAnimation = 0;
        g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;
        g_Spyro.m_bodyAnimationSpeed = 4;
        g_Spyro.m_nextBodyAnimationFrame = 0;
        g_Spyro.m_bodyFrameProgress = 0;
        g_Spyro.m_sortingDepth = 3;
      }
      if (D_800777E8.unk_0x04 < 0x40) {
        D_800777E8.m_BalloonMoby->m_Position.z =
            D_800777E8.unk_0x5C[0] +
            ((Sin(D_800777E8.unk_0x04 * 0x10 + 0xc00) + 0x1000) * 3 >> 2);
      } else {
        D_800777E8.m_BalloonMoby->m_Position.z =
            D_800777E8.m_BalloonMoby->m_Position.z + g_DeltaTime * 75;
        g_Camera.m_Position.z =
            D_800777E8.unk_0x40 +
            ((Sin(D_800777E8.unk_0x04 * 0x10 + 0x800) + 0x1000) * 3 >> 2);
      }
      VecSub(&vec, &D_800777E8.m_BalloonMoby->m_Position, &g_Camera.m_Position);
      g_Camera.m_Rotation.y = Atan2(VecMagnitude(&vec, 0), -vec.z, 1);

      g_Camera.m_Rotation.z = Atan2(vec.x, vec.y, 1);
      g_Spyro.m_Position.z = D_800777E8.m_BalloonMoby->m_Position.z + 0x2d4;
      g_Spyro.m_bodyRotation.z = D_800777E8.m_BalloonMoby->m_Rotation.z + 0x80;
    } else {
      D_800777E8.unk_0x38 = Atan2(
          g_Camera.m_Position.x - D_800777E8.m_BalloonMoby->m_Position.x,
          g_Camera.m_Position.y - D_800777E8.m_BalloonMoby->m_Position.y, 1);
      VecSub(&vec, &g_Camera.m_Position, &D_800777E8.m_BalloonMoby->m_Position);
      D_800777E8.unk_0x3c = VecMagnitude(&vec, 0);
      D_800777E8.unk_0x40 = g_Camera.m_Position.z;
      D_800777E8.unk_0x50 =
          (0x390 + D_800777E8.m_BalloonMoby->m_Rotation.z * 0x10) & 0xfff;
      D_800777E8.unk_0x54 = 0x800;
      g_LoadStage = 0;
      D_8007576C = -1;
      g_HasLevelTransition = 0;
      g_PortalLevelId = 0;
      D_800777E8.unk_0x58 = D_800777E8.m_BalloonMoby->m_Position.z + 0x200;

      D_800777E8.m_State = 4;
      D_800777E8.unk_0x04 = 0;
      LoadLevel(1);
      Memcpy(&g_SonyImage.m_WorldFarQueued[106], D_800777E8.m_BalloonMoby,
             0x58);
      D_800777E8.m_BalloonMoby = (Moby *)&g_SonyImage.m_WorldFarQueued[106];
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
    if (D_800777E8.unk_0x04 < 0x100) {
      sineProgress = Sin(((D_800777E8.unk_0x04 << 0xb) >> 8) - 0x400) + 0x1000;
      if ((D_800777E8.unk_0x38 - D_800777E8.unk_0x50 & 0xfff) <= 0x800) {
        angle = D_800777E8.unk_0x50 +
                (func_80017928(D_800777E8.unk_0x38, D_800777E8.unk_0x50) *
                     sineProgress >>
                 13);
      } else {
        angle = D_800777E8.unk_0x50 -
                (func_80017928(D_800777E8.unk_0x38, D_800777E8.unk_0x50) *
                     sineProgress >>
                 13);
      }
      dist = D_800777E8.unk_0x54 +
             ((D_800777E8.unk_0x3c - D_800777E8.unk_0x54) * sineProgress >> 13);
      g_Camera.m_Position.x =
          D_800777E8.m_BalloonMoby->m_Position.x + (Cos(angle) * dist >> 12);
      g_Camera.m_Position.y =
          D_800777E8.m_BalloonMoby->m_Position.y + (Sin(angle) * dist >> 12);
      g_Camera.m_Position.z =
          D_800777E8.unk_0x58 +
          ((D_800777E8.unk_0x40 - D_800777E8.unk_0x58) * sineProgress >> 13);
      VecSub(&vec, &D_800777E8.m_BalloonMoby->m_Position, &g_Camera.m_Position);
      vec.z += 0x200 - (sineProgress >> 4);
      g_Camera.m_Rotation.y = Atan2(VecMagnitude(&vec, 0), -vec.z, 1);
      g_Camera.m_Rotation.z = Atan2(vec.x, vec.y, 1);
    } else if (g_LoadStage == 13) {
      D_800777E8.m_State = 6;
      D_800777E8.unk_0x04 = 0;
      LoadLevel(1);
    }
    break;
  }

  case 6: {
    Vector3D vec;
    if (0x7f >= D_800777E8.unk_0x04) {
      if (D_800777E8.unk_0x04 == g_DeltaTime) {
        D_800777E8.unk_0x5C[0] = D_800777E8.m_BalloonMoby->m_Position.z;
        D_800777E8.unk_0x40 = g_Camera.m_Position.z;
      }
      if (D_800777E8.unk_0x04 < 0x40) {
        D_800777E8.m_BalloonMoby->m_Position.z -= g_DeltaTime * 75;
        g_Camera.m_Position.z =
            D_800777E8.unk_0x40 + (Sin(-D_800777E8.unk_0x04 * 0x10) * 3 >> 2);
      } else {
        if (D_800777E8.unk_0x04 - g_DeltaTime < 0x40) {
          D_800777E8.unk_0x5C[0] = D_800777E8.m_BalloonMoby->m_Position.z - 75;
        }
        D_800777E8.m_BalloonMoby->m_Position.z =
            D_800777E8.unk_0x5C[0] +
            (Sin(0x400 - D_800777E8.unk_0x04 * 0x10) * 3 >> 2);
      }
      VecSub(&vec, &D_800777E8.m_BalloonMoby->m_Position, &g_Camera.m_Position);
      g_Camera.m_Rotation.y = Atan2(VecMagnitude(&vec, 0), -vec.z, 1);
      g_Camera.m_Rotation.z = Atan2(vec.x, vec.y, 1);
      g_Spyro.m_Position.z = D_800777E8.m_BalloonMoby->m_Position.z + 0x2d4;
      g_Spyro.m_bodyRotation.z = D_800777E8.m_BalloonMoby->m_Rotation.z + 0x80;

    } else {
      D_800777E8.m_State = 7;
      D_800777E8.unk_0x04 = 0;
      VecCopy(&D_800777E8.unk_0x18, &g_Spyro.m_Position);
      D_800777E8.unk_0x2C.x = D_8006EADC[D_800777E8.m_Homeworld][0];
      D_800777E8.unk_0x2C.y = D_8006EADC[D_800777E8.m_Homeworld][1];
      D_800777E8.unk_0x2C.z = g_Spyro.m_Position.z;
      D_800777E8.unk_0x2C.z =
          func_8004D5EC(&D_800777E8.unk_0x2C, 0x10000) + 0x164;
      g_Spyro.m_nextBodyAnimation = 5;
      g_Spyro.m_bodyAnimationFrame = g_Spyro.m_nextBodyAnimationFrame;
      g_Spyro.m_nextBodyAnimationFrame = 0;
      g_Spyro.m_bodyFrameProgress = 0;
      g_Spyro.m_bodyAnimationSpeed = 6;
    }
    break;
  }

  case 7: {
    int pad[2];
    if (D_800777E8.unk_0x04 < 0x40) {
      g_Spyro.m_Position.x = D_800777E8.unk_0x18.x +
                             ((D_800777E8.unk_0x2C.x - D_800777E8.unk_0x18.x) *
                                  D_800777E8.unk_0x04 >>
                              6);
      g_Spyro.m_Position.y = D_800777E8.unk_0x18.y +
                             ((D_800777E8.unk_0x2C.y - D_800777E8.unk_0x18.y) *
                                  D_800777E8.unk_0x04 >>
                              6);
      g_Spyro.m_Position.z = D_800777E8.unk_0x2C.z +
                             (Sin(D_800777E8.unk_0x04 * 24 + 0x200) *
                              (D_800777E8.unk_0x18.z - D_800777E8.unk_0x2C.z)) /
                                 0xb50;
      g_Spyro.m_surfaceBelowSpyro = func_8004D5EC(&g_Spyro.m_Position, 0x10000);
      RotVec8ToMatrix(&g_Spyro.m_bodyRotation, &g_Spyro.m_RotationMatrix, 0);
      func_80049FAC(1);
      if (0x1f < D_800777E8.unk_0x04) {
        D_800777E8.m_BalloonMoby->m_Position.z +=
            D_800777E8.unk_0x04 * g_DeltaTime;
      }
    } else {
      VecCopy(&g_Spyro.m_Position, &D_800777E8.unk_0x2C);
      func_8004AC24(1);
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

void NAME_OVERLAY_FUNCTION(Balloonist4)(void) {
  if (D_800777E8.m_State <= 3) {
    if (D_800777E8.m_State <= 1) {
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
            COSINE_8((D_800777E8.unk_0x04 * 4 + (i * 12) & 0xff)) >> 8;
        hudmobyptr--;
      }
    }
    if (D_800777E8.m_State == 1) {
      if (D_800777E8.m_DialogueId <= 29 || D_800777E8.m_DialogueId >= 33) {
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
        for (i = g_BalloonistDialogueIndices[D_800777E8.m_DialogueId];
             i < g_BalloonistDialogueIndices[D_800777E8.m_DialogueId + 1];
             i++) {
          vec1.x = 0x5e;
          func_800181AC(g_BalloonistDialogue[i], &vec1, &vec2, 0x12, 0xb);
          vec1.y += 0x12;
        }
        if (D_800777E8.unk_0x04 < 80) {
          if ((int)g_HudMobys <= (int)(hudmobyptr - D_800777E8.unk_0x04))
            g_HudMobys = hudmobyptr - D_800777E8.unk_0x04;
        }
        hudmobyptr--;
        for (i = 0; (int)g_HudMobys <= (int)hudmobyptr; i++) {
          hudmobyptr->m_Rotation.z =
              COSINE_8((D_800777E8.unk_0x04 * 4 + (i * 12) & 0xff)) >> 8;
          hudmobyptr--;
        }
        if (D_800777E8.unk_0x04 > 0x4f) {
          vec1.x = 0x19c;
          vec1.y = 0x60;
          vec1.z = 0x1100;
          func_80018534(&vec1, D_800777E8.unk_0x04, 0);
        }
      } else if (D_800777E8.m_DialogueId == 30) {
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

        if (D_800777E8.m_DialogueTopStr == 0) {
          func_800181AC("HOP ON, SPYRO!", &vec1, &vec2, 0x10, 0xb);
        } else if (D_800777E8.m_DialogueTopStr == 1) {
          func_800181AC("NEED A LIFT?", &vec1, &vec2, 0x10, 0xb);
        } else {
          func_800181AC("WHERE TO, SPYRO?", &vec1, &vec2, 0x10, 0xb);
        }
        vec1.x = 0x110;
        vec1.y += 0x14;
        hudmobyptr = g_HudMobys - 1;
        func_800181AC("STAY HERE", &vec1, &vec2, 0x10, 0xb);
        vec1.y += 0xf;
        if (D_800777E8.unk_0x08 == 0) {
          for (i = 0; g_HudMobys <= hudmobyptr; i++) {
            hudmobyptr->m_Rotation.z =
                COSINE_8((D_800777E8.unk_0x04 * 4 + (i * 12) & 0xff)) >> 8;
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
            if (D_800777E8.unk_0x08 == someflag) {
              for (j = 0; g_HudMobys <= hudmobyptr; j++) {
                hudmobyptr->m_Rotation.z =
                    COSINE_8((D_800777E8.unk_0x04 * 4 + (j * 12) & 0xff)) >> 8;
                hudmobyptr--;
              }
            }
            someflag++;
          }
        }
        func_8001860C(0xe0, 0x1d8, 0x19, someflag * 0xf + 0x33);
        func_8001844C(0xf0, 0x2e, 0x1a0, 0x2e);
        vec1.x = 0xf4;
        vec1.y = D_800777E8.unk_0x08 * 0xf + 0x36;
        vec1.z = 0x1100;
        func_80018534(&vec1, D_800777E8.unk_0x04, 0);
      } else if (D_800777E8.m_DialogueId == 31 ||
                 D_800777E8.m_DialogueId == 32) {
        Vector3D vec1;
        Vector3D vec2;
        char buffer[32];
        Moby *hudmobyptr;
        int i;

        func_8001860C(0x48, 0x1b8, 0x1c, 0x66);
        func_8001844C(100, 0x37, 0x184, 0x37);
        vec1.x = 0x60;
        vec1.y = D_800777E8.unk_0x08 * 0x13 + 0x43;
        vec1.z = 0x1100;
        func_80018534(&vec1, D_800777E8.unk_0x04, 0);
        vec2.x = 0x10;
        vec2.z = 0x1400;
        vec1.y = 0x2c;
        vec2.y = 1;
        vec1.z = 0x1100;
        vec1.x = 0x60;

        if (D_800777E8.m_DialogueId == 31)
          func_800181AC("ARE YOU READY TO GO?", &vec1, &vec2, 0x12, 0xb);
        else
          func_800181AC("WOULD YOU LIKE TO GO?", &vec1, &vec2, 0x12, 0xb);
        vec1.x = 0x80;
        vec1.y += 0x19;
        hudmobyptr = g_HudMobys - 1;
        func_800181AC("STAY HERE", &vec1, &vec2, 0x12, 0xb);
        vec1.y += 0x13;
        if (D_800777E8.unk_0x08 == 0) {
          for (i = 0; g_HudMobys <= hudmobyptr; i++) {
            hudmobyptr->m_Rotation.z =
                COSINE_8((D_800777E8.unk_0x04 * 4 + (i * 12) & 0xff)) >> 8;
            hudmobyptr--;
          }
        }
        vec1.x = 0x80;
        hudmobyptr = g_HudMobys - 1;
#if LEVEL == 10
#define GARBAGE_FIX 0x00, 0x2A, 0x2A, 0x2A
#elif LEVEL == 11
#define GARBAGE_FIX 0x00, 0x2A, 0x2A, 0x2A
#elif LEVEL == 13
#define GARBAGE_FIX 0x00, 0x2A, 0x2A, 0x2A
#elif LEVEL == 20
#define GARBAGE_FIX 0x00, 0x09, 0x53, 0x70
#elif LEVEL == 21
#define GARBAGE_FIX 0x00, 0x3B, 0x0D, 0x0A
#elif LEVEL == 22
#define GARBAGE_FIX 0x00, 0x2A, 0x2A, 0x2A
#elif LEVEL == 30
#define GARBAGE_FIX 0x00, 0x2A, 0x2A, 0x2A
#elif LEVEL == 40
#define GARBAGE_FIX 0x00, 0x20, 0x6C, 0x77
#elif LEVEL == 50
#define GARBAGE_FIX 0x00, 0x20, 0x70, 0x6F
#elif LEVEL == 60
#define GARBAGE_FIX 0x00, 0x35, 0x11, 0x3A
#endif
        if (D_800777E8.m_DialogueId == 31) {
          sprintf(buffer,
                  (char *)(char[]){'G', 'O', ' ', 'T', 'O', ' ', '%', 's',
                                   GARBAGE_FIX},
                  g_HomeworldNames[g_LevelId / 10]);
        } else {
          sprintf(buffer,
                  (char *)(char[]){'G', 'O', ' ', 'T', 'O', ' ', '%', 's',
                                   GARBAGE_FIX},
                  g_HomeworldNames[7 + (g_NextLevelId / 10 - 1) * 6 +
                                   g_NextLevelId % 10]);
        }
#undef GARBAGE_FIX

        func_800181AC(buffer, &vec1, &vec2, 18, 11);

        if (D_800777E8.unk_0x08 == 1) {
          for (i = 0; g_HudMobys <= hudmobyptr; i++) {
            hudmobyptr->m_Rotation.z =
                COSINE_8((D_800777E8.unk_0x04 * 4 + (i * 12) & 0xff)) >> 8;
            hudmobyptr--;
          }
        }
      }
    }

    func_800521C0();
    func_80019698();

    if (D_800777E8.m_State <= 1) {
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
    ptr[0] = D_800777E8.m_BalloonMoby;
    ptr[1] = 0;
    func_80019698();
    func_8002B9CC();
    func_80050BD0();
    func_800573C8();
  }
}
