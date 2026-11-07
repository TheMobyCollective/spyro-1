#include "common.h"

#include "buffers.h"
#include "camera.h"
#include "cd.h"
#include "cutscene.h"
#include "cyclorama.h"
#include "environment.h"
#include "gamepad.h"
#include "gamestates/draw.h"
#include "loaders.h"
#include "memory.h"
#include "moby_helpers.h"
#include "rand.h"
#include "renderers.h"
#include "sony_image.h"
#include "specular_and_metal.h"
#include "vector.h"
#include "wad.h"

// For exit()
#include <libapi.h>
#include <libetc.h>
#include <libgte.h>
#include <stdlib.h>

#include <libgpu.h>

typedef struct {
  u_char *m_Text;
  short m_PosY;
  short m_Timer1;
  short m_Timer2;
  short m_State;
} CreditsEntry;

typedef struct {
  int unk_0x00;
  u_char unk_0x04;
  u_char m_RotationX;
  u_char m_RotationY;
  u_char m_RotationZ;
  u_char unk_0x08;
  u_char unk_0x09;
  u_char unk_0x0A;
  u_char unk_0x0B;
  short m_VelocityX;
  short m_VelocityY;
  short m_VelocityZ;
  Vector3D16 m_Position;
  short unk_0x18;
  short m_Class;
} CreditsRecord;

extern int D_800756E4;
extern CreditsEntry *D_80075708;
extern u_char *D_800757EC;
extern CreditsRecord *D_8007589C;
extern int D_80075958;

void Terminator_credits(void);

void func_credits_8007AA50(void) {
  RECT rect;

  if (g_CreditsStage == -1) {
    u_char *base;
    int *header;
    u_char *textBase;
    int size;
    int i;

    base = (u_char *)Terminator_credits;
    if (g_CreditsBuffer == nullptr) {
      D_8007589C = (CreditsRecord *)base;
      D_800756E4 = 0;
      for (i = 0; i < 100; i++) {
        D_8007589C[i].unk_0x04 = 0;
      }
      D_80075708 = (CreditsEntry *)(base + 0xAF0);
      g_CreditsBuffer = base + 0x2800;
      g_Buffers.m_CopyBuf = g_CreditsBuffer;
      g_Buffers.m_DiscCopyBuf = g_CreditsBuffer;
    }

    CDLoadSync(g_CdState.m_WadSector, g_Buffers.m_DiscCopyBuf, 0x800,
               g_WadHeader.m_Credits1Data[g_CreditsSequence].m_Offset, 600);
    Memcpy(&g_LevelHeader, g_Buffers.m_DiscCopyBuf, sizeof(g_LevelHeader));

    CDLoadSync(g_CdState.m_WadSector, g_Buffers.m_DiscCopyBuf, 0x60000,
               g_LevelHeader.m_VramSramOffset +
                   g_WadHeader.m_Credits1Data[g_CreditsSequence].m_Offset,
               600);
    setRECT(&rect, 512, 0, 512, 384);
    LoadImage(&rect, (u_long *)g_Buffers.m_DiscCopyBuf);

    CDLoadSync(g_CdState.m_WadSector, g_Buffers.m_DiscCopyBuf,
               g_LevelHeader.m_VramSramSize - 0x60000,
               g_LevelHeader.m_VramSramOffset +
                   g_WadHeader.m_Credits1Data[g_CreditsSequence].m_Offset +
                   0x60000,
               600);
    SpuSetTransferStartAddr(0x1010);
    SpuWrite((u_char *)g_Buffers.m_DiscCopyBuf, 0x7EFF0);
    while (!SpuIsTransferCompleted(SPU_TRANSFER_PEEK)) {
    }

    CDLoadSync(g_CdState.m_WadSector, g_Buffers.m_DiscCopyBuf,
               g_LevelHeader.m_DataSize,
               g_LevelHeader.m_DataOffset +
                   g_WadHeader.m_Credits1Data[g_CreditsSequence].m_Offset,
               600);
    g_Buffers.m_ModelData = LoadLevelData(g_Buffers.m_DiscCopyBuf, 1);
    g_Cyclorama = g_NewCyclorama;
    g_Buffers.m_LevelScene = g_Buffers.m_ModelData;
    g_Buffers.m_LevelSceneOffset = g_LevelHeader.m_SceneOffset;
    g_Buffers.m_LevelSceneSize = g_LevelHeader.m_SceneSize;
    g_PortalCount = 0;

    CDLoadSync(g_CdState.m_WadSector, g_Buffers.m_LevelScene,
               g_Buffers.m_LevelSceneSize,
               g_LevelHeader.m_SceneOffset +
                   g_WadHeader.m_Credits1Data[g_CreditsSequence].m_Offset,
               600);
    g_Spu.m_SoundDefinitions = &g_CutsceneSoundDef;
    g_CreditsDataPtr = g_Buffers.m_LevelScene;
    g_Spu.m_SoundDefinitions->m_Addr = 0x1010;
    g_Spu.m_SoundDefinitions->m_LoopAddr = -1;
    g_Spu.m_SoundDefinitions->unk_0x8 = 80;
    g_Spu.m_SoundDefinitions->m_Pitch = 1625;
    g_Spu.m_SoundDefinitions->m_PitchVariance = 0;
    g_Spu.m_SoundDefinitions->m_PitchMultiplier = 0;
    g_Spu.m_SoundDefinitions->m_VarianceType = 0;
    g_Spu.m_NextSoundOverrideFlags = 1;
    g_Spu.m_VolumeOverride.left = 0x3FFF;
    g_Spu.m_VolumeOverride.right = 0x3FFF;
    PlaySound(0, nullptr, 16, nullptr);

    D_800757EC =
        (u_char *)g_Buffers.m_LevelScene + g_CreditsDataPtr->m_EntryOffset;
    header = (int *)D_800757EC;
    size = header[0];
    textBase = (u_char *)D_80075708 + header[1] - 12;
    g_CreditsTotalEntries = header[2];
    Memcpy(D_80075708, D_800757EC + 12, size - 12);

    for (i = 0; i < g_CreditsTotalEntries; i++) {
      PATCH_POINTER(D_80075708[i].m_Text, textBase);
    }

    g_CreditsStage = 0;
    g_CreditsSequence++;
  }

  if (g_CreditsDataPtr != nullptr && g_CreditsStage >= 0) {
    int tick;
    int duration;

    tick = g_CreditsDataPtr->m_CurrentTick + g_DeltaTime;
    duration = g_CreditsDataPtr->m_Duration;
    g_CreditsDataPtr->m_CurrentTick = tick;

    if (tick < duration * 2) {
      if (tick < 32) {
        g_Fade = 16 - (tick >> 1);
      } else if (duration * 2 - tick < 32) {
        g_Fade = 16 - ((duration * 2 - tick) >> 1);
      } else {
        g_Fade = 0;
      }
      if (g_Fade > 15) {
        g_Fade = 15;
      }
      if (g_Fade < 0) {
        g_Fade = 0;
      }

      // TODO: Hack
      setXYZ(
          &g_Camera.m_Position,
          (g_CreditsDataPtr->m_CameraData +
           (g_CreditsDataPtr->m_CurrentTick >> 1))
              ->m_Position.x,
          g_CreditsDataPtr->m_CameraData[g_CreditsDataPtr->m_CurrentTick >> 1]
              .m_Position.y,
          g_CreditsDataPtr->m_CameraData[g_CreditsDataPtr->m_CurrentTick >> 1]
              .m_Position.z);
      setXYZ(
          &g_Camera.m_Rotation,
          g_CreditsDataPtr->m_CameraData[g_CreditsDataPtr->m_CurrentTick >> 1]
              .m_Rotation.x,
          g_CreditsDataPtr->m_CameraData[g_CreditsDataPtr->m_CurrentTick >> 1]
              .m_Rotation.y,
          g_CreditsDataPtr->m_CameraData[g_CreditsDataPtr->m_CurrentTick >> 1]
              .m_Rotation.z);
    } else {
      g_CreditsStage++;
    }
  }

  if (D_800756E4 == 0 && g_CreditsEntryIndex >= g_CreditsTotalEntries) {
    g_Spu.m_SoundDefinitions->unk_0x8 -= 10;
    g_CreditsTimer += g_DeltaTime;
    if (g_Spu.m_SoundDefinitions->unk_0x8 < 0) {
      g_Spu.m_SoundDefinitions->unk_0x8 = 0;
    }
    g_Fade = g_CreditsTimer;
    if (g_CreditsTimer > 15) {
      g_Fade = 15;
    }
    if (g_Fade == 15) {
      g_CreditsStage = 99;
    }
  }

  if (D_800756E4 > 0 || (g_CreditsTotalEntries > 0 &&
                         g_CreditsEntryIndex < g_CreditsTotalEntries)) {
    int displayedCount;
    int entryIndex;
    int newEntry;
    int isCapital;
    int i;

    displayedCount = g_CreditsDisplayedCount;
    SpecularUpdate(3);
    isCapital = 1;

    for (entryIndex = g_CreditsEntryIndex; entryIndex <= displayedCount;
         entryIndex++) {
      newEntry = -1;
      if (TICK_TIMER(D_80075708[entryIndex].m_Timer1) != 0) {
        D_80075708[entryIndex].m_State = 2;
        if (D_80075708[entryIndex].m_Timer2 == 0 &&
            entryIndex == g_CreditsEntryIndex) {
          g_CreditsEntryIndex = entryIndex + 1;
        }
      }

      if (D_80075708[0].m_State == 0) {
        newEntry = 0;
      } else if (TICK_TIMER(D_80075708[entryIndex].m_Timer2) != 0 &&
                 D_80075708[entryIndex + 1].m_State == 0 &&
                 entryIndex < g_CreditsTotalEntries - 1) {
        newEntry = entryIndex + 1;
      }

      if (newEntry != -1) {
        Vector3D textPos;
        Vector3D textSpacing;
        CreditsRecord *record;
        u_char *text;
        int recordIndex;
        int secondDotForColon;
        int spaceWidth;
        int startX;
        int halfWidth;
        int scrollFrames;
        int dx;
        int dz;

        recordIndex = 0;
        secondDotForColon = 0;
        D_80075708[newEntry].m_State = 1;
        spaceWidth = 16;
        if (g_CreditsDisplayedCount < newEntry) {
          g_CreditsDisplayedCount = newEntry;
        }
        if (g_CreditsDisplayedCount > g_CreditsTotalEntries) {
          g_CreditsDisplayedCount = g_CreditsTotalEntries;
        }

        textPos.x = 256;
        textPos.y = D_80075708[newEntry].m_PosY;
        textPos.z = 4787;
        textSpacing.x = 14;
        textSpacing.y = 1;
        textSpacing.z = 5632;

        text = D_80075708[newEntry].m_Text;
        startX = 256;
        while (*text != '\0') {
          if (*text != ' ') {
          allocRecord:
            for (i = recordIndex; i < D_800756E4; i++) {
              if (D_8007589C[i].unk_0x04 == 0) {
                break;
              }
            }
            if (i < D_800756E4) {
              recordIndex = i;
              record = &D_8007589C[i];
            } else {
              record = &D_8007589C[D_800756E4];
              D_800756E4++;
            }

            if (*text >= 'A' && *text <= 'Z') {
              isCapital = 1;
            }
            if (*text >= 'a' && *text <= 'z') {
              isCapital = 0;
            }
            record->unk_0x04 = 1;
            record->unk_0x18 = newEntry;
            if (D_800756E4 > 100) {
              exit(0);
            }

            record->m_Position.x = textPos.x;
            record->m_Position.y = textPos.y;
            record->m_Position.z = textPos.z;
            if (isCapital == 0) {
              record->m_Position.y += textSpacing.y;
              record->m_Position.z = textSpacing.z;
            }

            if (*text >= '0' && *text <= '9') {
              record->m_Class = MOBYCLASS_NUMBER_0 + *text - '0';
            } else if (*text >= 'A' && *text <= 'Z') {
              record->m_Class = MOBYCLASS_LETTER_A + *text - 'A';
            } else if (*text >= 'a' && *text <= 'z') {
              record->m_Class = MOBYCLASS_LETTER_A + *text - 'a';
            } else if (*text == '!') {
              record->m_Class = MOBYCLASS_EXCLAMATION_MARK;
            } else if (*text == ',') {
              record->m_Class = MOBYCLASS_LETTER_APOSTROPHE;
            } else if (*text == '.') {
              record->m_Class = MOBYCLASS_PERIOD;
            } else if (*text == '-') {
              record->m_Class = MOBYCLASS_SLASH;
            } else if (*text == ':') {
              record->m_Class = MOBYCLASS_PERIOD;
              record->m_Position.z += 1400;
              if (secondDotForColon == 0) {
                secondDotForColon = 1;
                goto allocRecord;
              }
              secondDotForColon = 0;
              record->m_Position.y -= 6;
            } else {
              record->m_Class = MOBYCLASS_LETTER_APOSTROPHE;
              record->m_Position.y -= textSpacing.x * 2 / 3;
            }

            if (isCapital != 0) {
              textPos.x += spaceWidth;
            } else {
              textPos.x += textSpacing.x;
            }
            isCapital = *text >= '0' && *text <= '9';
          } else {
            textPos.x += textSpacing.x * 3 / 4;
            isCapital = 1;
          }
          text++;
        }

        halfWidth = (textPos.x - startX) >> 1;
        scrollFrames = 30;
        for (i = 0; i < D_800756E4; i++) {
          if (D_8007589C[i].unk_0x18 == newEntry) {
            D_8007589C[i].m_Position.x -= halfWidth;
            dx = -((D_8007589C[i].m_Position.x - 256) * 3) / scrollFrames;
            dz = -(D_8007589C[i].m_Position.z * 2) / scrollFrames;
            D_8007589C[i].m_Position.x -= dx * scrollFrames;
            D_8007589C[i].m_Position.z -= dz * scrollFrames;
            D_8007589C[i].m_VelocityX = dx;
            D_8007589C[i].m_VelocityZ = dz;
            D_8007589C[i].unk_0x08 = RandRangeSigned(4, 15);
            D_8007589C[i].unk_0x09 = RandRangeSigned(4, 15);
            D_8007589C[i].unk_0x0A = RandRangeSigned(4, 15);
            D_8007589C[i].m_RotationX = -D_8007589C[i].unk_0x08 * scrollFrames;
            D_8007589C[i].m_RotationY = -D_8007589C[i].unk_0x09 * scrollFrames;
            D_8007589C[i].m_RotationZ = -D_8007589C[i].unk_0x0A * scrollFrames;
            D_8007589C[i].unk_0x0B = scrollFrames;
          }
        }
      }
    }

    for (i = 0; i < D_800756E4; i++) {
      if (D_80075708[D_8007589C[i].unk_0x18].m_State == 2) {
        if (D_8007589C[i].unk_0x04 == 2) {
          D_8007589C[i].unk_0x04 = 3;
        } else if (D_8007589C[i].unk_0x04 == 4) {
          D_8007589C[i].unk_0x04 = 0;
        }
      }
    }

    for (i = 0; i < D_800756E4; i++) {
      switch (D_8007589C[i].unk_0x04) {
      case 1:
        D_8007589C[i].m_Position.x += D_8007589C[i].m_VelocityX;
        D_8007589C[i].m_Position.z += D_8007589C[i].m_VelocityZ;
        D_8007589C[i].m_RotationX += D_8007589C[i].unk_0x08;
        D_8007589C[i].m_RotationY += D_8007589C[i].unk_0x09;
        D_8007589C[i].m_RotationZ += D_8007589C[i].unk_0x0A;
        if (--D_8007589C[i].unk_0x0B == 0) {
          D_8007589C[i].unk_0x04 = 2;
          D_8007589C[i].m_VelocityX = RandRangeSigned(3, 11);
          D_8007589C[i].m_VelocityY = -RandRange(6, 10);
          D_8007589C[i].m_VelocityZ = RandRange(-35, 35);
          D_8007589C[i].unk_0x08 = RandRangeSigned(4, 9);
          D_8007589C[i].unk_0x09 = RandRangeSigned(4, 9);
          D_8007589C[i].unk_0x0A = RandRangeSigned(4, 9);
        }
        break;

      case 3:
        D_8007589C[i].m_Position.x += D_8007589C[i].m_VelocityX;
        D_8007589C[i].m_Position.y += D_8007589C[i].m_VelocityY;
        D_8007589C[i].m_Position.z += D_8007589C[i].m_VelocityZ;
        D_8007589C[i].m_VelocityY += 1;
        D_8007589C[i].m_RotationX += D_8007589C[i].unk_0x08;
        D_8007589C[i].m_RotationY += D_8007589C[i].unk_0x09;
        D_8007589C[i].m_RotationZ += D_8007589C[i].unk_0x0A;
        if (D_8007589C[i].m_VelocityY > 20) {
          D_8007589C[i].m_VelocityY = 20;
        }
        if (D_8007589C[i].m_Position.y > 280) {
          D_8007589C[i].unk_0x04 = 4;
        }
        break;
      }
    }

    if (D_800756E4 > 0 && D_8007589C[D_800756E4 - 1].unk_0x04 == 0) {
      do {
        D_800756E4--;
      } while (D_800756E4 > 0 && D_8007589C[D_800756E4 - 1].unk_0x04 == 0);
    }
  }

  if (g_CreditsStage != -1) {
    RECT loadRect;
    RECT moveRect;

    if (g_CreditsStage > 0) {
      CDLoadTime();
      if (g_CdState.m_IsReading != 0) {
        return;
      }
      if (CdSync(1, nullptr) != CdlComplete) {
        return;
      }
    }

    switch (g_CreditsStage) {
    case 0:
      CDLoadAsync(g_CdState.m_WadSector, D_800757EC, 0x800,
                  g_WadHeader.m_Credits1Data[g_CreditsSequence].m_Offset, 600);
      g_CreditsStage++;
      break;

    case 1:
      Memcpy(&g_LevelHeader, D_800757EC, sizeof(g_LevelHeader));
      CDLoadAsync(g_CdState.m_WadSector, D_800757EC, 0x20000,
                  g_LevelHeader.m_VramSramOffset +
                      g_WadHeader.m_Credits1Data[g_CreditsSequence].m_Offset,
                  600);
      g_CreditsStage++;
      break;

    case 2:
      setRECT(&loadRect, 512, 384, 512, 128);
      DrawSync(0);
      LoadImage(&loadRect, (u_long *)D_800757EC);
      DrawSync(0);
      D_80075958 =
          g_LevelHeader.m_DataSize + 0x40000 + g_LevelHeader.m_SceneSize;
      CDLoadAsync(g_CdState.m_WadSector, D_800757EC, D_80075958,
                  g_LevelHeader.m_VramSramOffset +
                      g_WadHeader.m_Credits1Data[g_CreditsSequence].m_Offset +
                      0x20000,
                  600);
      g_CreditsStage++;
      break;

    case 3:
      D_8007576C = 0;
      break;

    case 4:
      setRECT(&moveRect, 512, 128, 512, 256);
      g_Buffers.m_CopyBuf = g_CreditsBuffer;
      g_Buffers.m_DiscCopyBuf = g_CreditsBuffer;
      DrawSync(0);
      LoadImage(&moveRect, (u_long *)D_800757EC);
      setRECT(&moveRect, 512, 384, 512, 128);
      MoveImage(&moveRect, 512, 0);
      DrawSync(0);

      Memcpy(g_CreditsBuffer, D_800757EC + 0x40000, D_80075958 - 0x40000);
      D_800757EC = g_CreditsBuffer + D_80075958 - 0x40000;
      g_Buffers.m_ModelData = LoadLevelData(g_Buffers.m_DiscCopyBuf, 1);
      g_Cyclorama = g_NewCyclorama;
      g_Buffers.m_LevelScene =
          (u_char *)g_Buffers.m_DiscCopyBuf + g_LevelHeader.m_DataSize;
      g_CreditsDataPtr = g_Buffers.m_LevelScene;
      g_Buffers.m_LevelSceneSize = g_LevelHeader.m_SceneSize;
      g_Buffers.m_LevelSceneOffset = g_LevelHeader.m_SceneOffset;
      if (g_CreditsSequence % 10 < 9) {
        g_CreditsStage = 0;
      } else {
        g_CreditsStage = 3;
      }
      g_CreditsSequence++;
      break;
    }
  }
}

void func_credits_8007BFD0(void) {
  RECT rect;
  CreditsRecord *record;
  int y;
  int i;

  if (g_CreditsStage == -1) {
    DrawSync(0);
    VSync(0);
    rect.x = 0;
    if (g_CurDB != &g_DB[0]) {
      y = 248;
    } else {
      y = 8;
    }
    rect.y = y;
    rect.w = 512;
    rect.h = 224;
    MoveImage(&rect, 0, 256 - y);
    DrawSync(0);
  } else {
    setRGB0(&g_DB[0].m_DrawEnv, g_Cyclorama.m_BackgroundColor.r,
            g_Cyclorama.m_BackgroundColor.g, g_Cyclorama.m_BackgroundColor.b);
    setRGB0(&g_DB[1].m_DrawEnv, g_Cyclorama.m_BackgroundColor.r,
            g_Cyclorama.m_BackgroundColor.g, g_Cyclorama.m_BackgroundColor.b);

    for (i = 0; i < D_800756E4; i++) {
      record = &D_8007589C[i];
      g_HudMobys -= 1;
      Memset(g_HudMobys, 0, sizeof(Moby));
      g_HudMobys->m_Position.x = record->m_Position.x;
      g_HudMobys->m_Position.y = record->m_Position.y;
      g_HudMobys->m_Position.z = record->m_Position.z;
      g_HudMobys->m_Rotation.x = record->m_RotationX;
      if (record->m_Class == MOBYCLASS_SLASH) {
        g_HudMobys->m_Rotation.x += 41;
        g_HudMobys->m_Position.z = 7168;
      }
      g_HudMobys->m_Rotation.y = record->m_RotationY;
      g_HudMobys->m_Rotation.z = record->m_RotationZ;
      g_HudMobys->m_Class = record->m_Class;
      g_HudMobys->m_SpecularMetalType = 11;
      g_HudMobys->m_RenderRadius = 255;
      g_HudMobys->m_DepthOffset = 127;
    }

    if (g_Fade != 0) {
      func_800190D4(2, g_Fade * 16, g_Fade * 16, g_Fade * 16);
    }

    g_SonyImage.m_ShadedMobys[0] = nullptr;
    func_80018880();
    Memset(g_SonyImage.u.m_Buf, 0, 0x900);
    func_80022A2C();
    Memset16(g_SonyImage.u.m_Buf, 0, 0x1C00);

    g_Environment.m_CullingDistance = 163840;
    func_800258F0(-1);
    func_8004EBA8(-1, &g_Camera.m_ViewMatrix, &g_Camera.m_ProjectionMatrix);

    DrawSync(0);
    if (D_80075784 != 0) {
      VSync(0);
    }

    D_80075950.pre = VSync(-1);
    while (D_80075950.pre - D_80075950.post < 2) {
      VSync(0);
      D_80075950.pre = VSync(-1);
    }
    D_80075950.post = VSync(-1);

    PutDispEnv(&g_CurDB->m_DispEnv);
    PutDrawEnv(&g_CurDB->m_DrawEnv);
    DrawOTag(func_80016784(0x800));
  }
}
