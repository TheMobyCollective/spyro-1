#include "common.h"
#include "buffers.h"
#include "camera.h"
#include "cd.h"
#include "cutscene.h"
#include "cyclorama.h"
#include "environment.h"
#include "gamepad.h"
#include "graphics.h"
#include "loaders.h"
#include "memory.h"
#include "moby.h"
#include "moby_helpers.h"
#include "rand.h"
#include "renderers.h"
#include "sony_image.h"
#include "specular_and_metal.h"
#include "spu.h"
#include "wad.h"

#include <libetc.h>
#include <libgpu.h>
#include <libspu.h>
#include <stdlib.h>

extern int D_800756E4; // Credits record count

extern void func_80018880(void);
extern void func_800190D4(int pMode, int pR, int pG, int pB);
extern void func_credits_8007C338(void);

extern struct {
  int post;
  int pre;
} D_80075950;

extern u_char *D_800757EC;
extern int D_80075958;

typedef struct {
  u_char *m_Ptr;
} CreditsBufPtr;

typedef struct {
  u_char *m_Text; // 0x00
  short m_PosY;   // 0x04
  short m_Timer1; // 0x06
  short m_Timer2; // 0x08
  short m_State;  // 0x0A
} CreditsEntry; // 0x0C

extern CreditsEntry *D_80075708;

typedef struct {
  int m_CurrentTick; // 0x00
  int m_EntryOffset; // 0x04
  int m_Duration;    // 0x08
  CutsceneCameraData m_CameraData[1]; // 0x0C
} CreditsLayout;

typedef struct {
  int m_Size;       // 0x00
  int m_TextBase;   // 0x04
  int m_EntryCount; // 0x08
  CreditsEntry m_Entries[1]; // 0x0C
} CreditsData;

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
  short m_VelocityX; // 0x0C
  short m_VelocityY; // 0x0E
  short m_VelocityZ; // 0x10
  Vector3D16 m_Position; // 0x12
  short unk_0x18;
  short m_Class; // 0x1A
} CreditsRecord; // 0x1C

extern CreditsRecord *D_8007589C; // Credits records

void func_credits_8007AA50(void) {
  RECT rect;
  Vector3D textPos;
  Vector3D textParams;
  CreditsLayout *layout;
  CreditsEntry *entry;
  CreditsRecord *record;
  CreditsData *data;
  u_char *text;
  u_char *pScene;
  u_char *pText;
  u_char *pCreditsBase;
  int displayedCount;
  int entryIndex;
  int isUpper;
  int new_var2;
  int fadeState;
  int scanIndex;
  int halfWidth;
  int new_var;
  int recordIndex;
  int wrap;
  int scrollFrames;
  int dx;
  int dz;
  int advance;
  int baseX;
  int centerX;
  int duration;
  int tick;
  int i;
  int j;
  int bound;
  int len;

  if (g_CreditsStage == -1) {
    pCreditsBase = (u_char *) func_credits_8007C338;
    if (g_CreditsBuffer == 0) {
      D_8007589C = (CreditsRecord *) pCreditsBase;
      D_800756E4 = 0;
      for (i = 0; i < 100; i++) {
        D_8007589C[i].unk_0x04 = 0;
      }
      D_80075708 = (CreditsEntry *) (pCreditsBase + 0xAF0);
      g_CreditsBuffer = (int) (pCreditsBase + 0x2800);
      g_Buffers.m_CopyBuf = (void *) g_CreditsBuffer;
      g_Buffers.m_DiscCopyBuf = (void *) g_CreditsBuffer;
    }
    CDLoadSync(g_CdState.m_WadSector, g_Buffers.m_DiscCopyBuf, 0x800,
               g_WadHeader.m_Credits1Data[g_CreditsSequence].m_Offset, 0x258);
    Memcpy(&g_LevelHeader, g_Buffers.m_DiscCopyBuf, 0x1D0);
    CDLoadSync(g_CdState.m_WadSector, g_Buffers.m_DiscCopyBuf, 0x60000,
               g_LevelHeader.m_VramSramOffset +
                   g_WadHeader.m_Credits1Data[g_CreditsSequence].m_Offset,
               0x258);
    setRECT(&rect, 0x200, 0, 0x200, 0x180);
    LoadImage(&rect, (u_long *) g_Buffers.m_DiscCopyBuf);
    CDLoadSync(g_CdState.m_WadSector, g_Buffers.m_DiscCopyBuf,
               g_LevelHeader.m_VramSramSize - 0x60000,
               g_LevelHeader.m_VramSramOffset +
                   g_WadHeader.m_Credits1Data[g_CreditsSequence].m_Offset +
                   0x60000,
               0x258);
    SpuSetTransferStartAddr(0x1010);
    SpuWrite((u_char *) g_Buffers.m_DiscCopyBuf, 0x7EFF0);
    while (SpuIsTransferCompleted(0) == 0) {
    }
    CDLoadSync(g_CdState.m_WadSector, g_Buffers.m_DiscCopyBuf,
               g_LevelHeader.m_DataSize,
               g_LevelHeader.m_DataOffset +
                   g_WadHeader.m_Credits1Data[g_CreditsSequence].m_Offset,
               0x258);
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
               0x258);
    g_Spu.m_SoundDefinitions = &g_CutsceneSoundDef;
    g_CreditsDataPtr = (int) g_Buffers.m_LevelScene;
    g_Spu.m_SoundDefinitions->m_Addr = 0x1010;
    g_Spu.m_SoundDefinitions->m_LoopAddr = -1;
    g_Spu.m_SoundDefinitions->unk_0x8 = 0x50;
    g_Spu.m_SoundDefinitions->m_Pitch = 0x659;
    g_Spu.m_SoundDefinitions->m_PitchVariance = 0;
    g_Spu.m_SoundDefinitions->m_PitchMultiplier = 0;
    g_Spu.m_SoundDefinitions->m_VarianceType = 0;
    g_Spu.m_NextSoundOverrideFlags = 1;
    g_Spu.m_VolumeOverride.left = 0x3FFF;
    g_Spu.m_VolumeOverride.right = 0x3FFF;
    PlaySound(0, 0, 0x10, 0);
    data = (CreditsData *) ((u_char *) g_Buffers.m_LevelScene +
                            ((CreditsLayout *) g_CreditsDataPtr)->m_EntryOffset);
    /* NOTE: struct-typed store (matches ref sched homes; keeps loads below) */
    ((CreditsBufPtr *) &D_800757EC)->m_Ptr = (u_char *) data;
    len = data->m_Size - 0xC;
    pText = (u_char *) ((u_int) D_80075708 + data->m_TextBase - 0xC);
    g_CreditsTotalEntries = data->m_EntryCount;
    Memcpy(D_80075708, (u_char *) data + 0xC, len);
    bound = g_CreditsTotalEntries;
    j = 0;
    if (bound > 0) {
      do {
        D_80075708[j].m_Text =
          (u_char *) ((u_int) pText + (u_int) D_80075708[j].m_Text);
        j++;
      } while (j < bound);
    }
    g_CreditsStage = 0;
    g_CreditsSequence += 1;
  }
  if ((g_CreditsDataPtr != 0) && (g_CreditsStage >= 0)) {
    tick = ((CreditsLayout *) g_CreditsDataPtr)->m_CurrentTick + g_DeltaTime;
    duration = ((CreditsLayout *) g_CreditsDataPtr)->m_Duration;
    ((CreditsLayout *) g_CreditsDataPtr)->m_CurrentTick = tick;
    if (tick < duration * 2) {
      if (tick < 0x20) {
        g_Fade = 0x10 - (tick >> 1);
      } else if ((duration * 2 - tick) < 0x20) {
        g_Fade = 0x10 - ((duration * 2 - tick) >> 1);
      } else {
        g_Fade = 0;
      }
      if (g_Fade >= 0x10) {
        g_Fade = 0xF;
      }
      if (g_Fade < 0) {
        g_Fade = 0;
      }
      g_Camera.m_Position.x =
          ((((CreditsLayout *) g_CreditsDataPtr)->m_CurrentTick >> 1)
               [((CreditsLayout *) g_CreditsDataPtr)->m_CameraData])
              .m_Position.x;
      g_Camera.m_Position.y =
          ((CreditsLayout *) g_CreditsDataPtr)
              ->m_CameraData[((CreditsLayout *) g_CreditsDataPtr)
                                 ->m_CurrentTick >>
                             1]
              .m_Position.y;
      g_Camera.m_Position.z =
          ((CreditsLayout *) g_CreditsDataPtr)
              ->m_CameraData[((CreditsLayout *) g_CreditsDataPtr)
                                 ->m_CurrentTick >>
                             1]
              .m_Position.z;
      g_Camera.m_Rotation.x =
          ((CreditsLayout *) g_CreditsDataPtr)
              ->m_CameraData[((CreditsLayout *) g_CreditsDataPtr)
                                 ->m_CurrentTick >>
                             1]
              .m_Rotation.x;
      g_Camera.m_Rotation.y =
          ((CreditsLayout *) g_CreditsDataPtr)
              ->m_CameraData[((CreditsLayout *) g_CreditsDataPtr)
                                 ->m_CurrentTick >>
                             1]
              .m_Rotation.y;
      g_Camera.m_Rotation.z =
          ((CreditsLayout *) g_CreditsDataPtr)
              ->m_CameraData[((CreditsLayout *) g_CreditsDataPtr)
                                 ->m_CurrentTick >>
                             1]
              .m_Rotation.z;
    } else {
      g_CreditsStage += 1;
    }
  }
  if (D_800756E4 == 0) {
    if (g_CreditsEntryIndex >= g_CreditsTotalEntries) {
      g_Spu.m_SoundDefinitions->unk_0x8 -= 10;
      g_CreditsTimer += g_DeltaTime;
      if (g_Spu.m_SoundDefinitions->unk_0x8 < 0) {
        g_Spu.m_SoundDefinitions->unk_0x8 = 0;
      }
      g_Fade = g_CreditsTimer;
      if (g_CreditsTimer >= 0x10) {
        g_Fade = 0xF;
      }
      if (g_Fade == 0xF) {
        g_CreditsStage = 0x63;
      }
    }
  }
  if ((D_800756E4 > 0) ||
      ((g_CreditsTotalEntries > 0) &&
       (g_CreditsEntryIndex < g_CreditsTotalEntries))) {
    displayedCount = g_CreditsDisplayedCount;
    SpecularUpdate(3);
    entryIndex = g_CreditsEntryIndex;
    isUpper = 1;
    new_var2 = 0;
    if (displayedCount >= entryIndex) {
      do {
        fadeState = -1;
        if (func_80037F90((u_char *) D_80075708 + entryIndex * 0xC + 6, 2) !=
            0) {
          D_80075708[entryIndex].m_State = 2;
          if ((D_80075708[entryIndex].m_Timer2 == 0) &&
              (entryIndex == g_CreditsEntryIndex)) {
            g_CreditsEntryIndex = entryIndex + 1;
          }
        }
        if (D_80075708[0].m_State == 0) {
          fadeState = 0;
        } else if ((func_80037F90((u_char *) D_80075708 + entryIndex * 0xC + 8,
                                    2) != 0) &&
                   (D_80075708[entryIndex + 1].m_State == 0) &&
                   (entryIndex < (g_CreditsTotalEntries - 1))) {
          fadeState = entryIndex + 1;
        }
        if (fadeState != -1) {
          recordIndex = 0;
          wrap = 0;
          entry = (CreditsEntry *) (fadeState * 0xC + (int) D_80075708);
          entry->m_State = 1;
          advance = 0x10;
          if (g_CreditsDisplayedCount < fadeState) {
            g_CreditsDisplayedCount = fadeState;
          }
          if (g_CreditsDisplayedCount > g_CreditsTotalEntries) {
            g_CreditsDisplayedCount = g_CreditsTotalEntries;
          }
          baseX = 0x100;
          textPos.x = baseX;
          textPos.y = entry->m_PosY;
          textPos.z = 0x12B3;
          textParams.x = 0xE;
          textParams.y = 1;
          textParams.z = 0x1600;
          {
            int probe0;
            int probe1;
            int probe2;
            int probe3;
            int probe4;
            int probe5;
            int probe6;
            int probe7;

            (void) &probe0;
            (void) &probe1;
            (void) &probe2;
            (void) &probe3;
            (void) &probe4;
            (void) &probe5;
            (void) &probe6;
            (void) &probe7;
          }
          text = entry->m_Text;
          centerX = 0x100;
          while (*text != 0) {
            if (*text != ' ') {
allocRecord:
              for (scanIndex = recordIndex; scanIndex < D_800756E4;
                   scanIndex++) {
                if (D_8007589C[scanIndex].unk_0x04 == 0) {
                  break;
                }
              }
              if (scanIndex < D_800756E4) {
                recordIndex = scanIndex;
                record = &D_8007589C[scanIndex];
              } else {
                record = &D_8007589C[D_800756E4];
                D_800756E4 += 1;
              }
              if ((*text >= 'A') && (*text <= 'Z')) {
                isUpper = 1;
              }
              if ((*text >= 'a') && (*text <= 'z')) {
                isUpper = 0;
              }
              record->unk_0x04 = 1;
              record->unk_0x18 = fadeState;
              if (D_800756E4 >= 0x65) {
                exit(0);
              }
              record->m_Position.x = textPos.x;
              record->m_Position.y = textPos.y;
              record->m_Position.z = textPos.z;
              if (isUpper == 0) {
                record->m_Position.y += textParams.y;
                record->m_Position.z = textParams.z;
              }
              if ((*text >= '0') && (*text <= '9')) {
                record->m_Class = *text + 0xD4;
              } else if ((*text >= 'A') && (*text <= 'Z')) {
                record->m_Class = *text + 0x169;
              } else if ((*text >= 'a') && (*text <= 'z')) {
                record->m_Class = *text + 0x149;
              } else if (*text == '!') {
                record->m_Class = 0x4B;
              } else if (*text == ',') {
                record->m_Class = 0x4C;
              } else if (*text == '.') {
                record->m_Class = 0x147;
              } else if (*text == '-') {
                record->m_Class = 0x115;
              } else if (*text == ':') {
                record->m_Class = 0x147;
                record->m_Position.z += 0x578;
                if (wrap == 0) {
                  wrap = 1;
                  goto allocRecord;
                }
                wrap = 0;
                record->m_Position.y -= 6;
              } else {
                record->m_Class = 0x4C;
                record->m_Position.y -= (textParams.x * 2) / 3;
              }
              if (isUpper != 0) {
                textPos.x += advance;
              } else {
                textPos.x += textParams.x;
              }
              isUpper = (*text >= '0') && (*text <= '9');
            } else {
              textPos.x += (textParams.x * 3) / 4;
              isUpper = 1;
            }
            text++;
          }
          halfWidth = (textPos.x - centerX) >> 1;
          scrollFrames = 30;
          scanIndex = 0;
          if (D_800756E4 > 0) {
            do {
              if (D_8007589C[scanIndex].unk_0x18 == fadeState) {
                D_8007589C[scanIndex].m_Position.x -= halfWidth;
                dx = -((D_8007589C[scanIndex].m_Position.x - 0x100) * 3) / scrollFrames;
                dz = -(D_8007589C[scanIndex].m_Position.z * 2) / scrollFrames;
                D_8007589C[scanIndex].m_Position.x -= dx * scrollFrames;
                D_8007589C[scanIndex].m_Position.z -= dz * scrollFrames;
                D_8007589C[scanIndex].m_VelocityX = dx;
                D_8007589C[scanIndex].m_VelocityZ = dz;
                D_8007589C[scanIndex].unk_0x08 = RandRangeSigned(4, 0xF);
                D_8007589C[scanIndex].unk_0x09 = RandRangeSigned(4, 0xF);
                D_8007589C[scanIndex].unk_0x0A = RandRangeSigned(4, 0xF);
                D_8007589C[scanIndex].m_RotationX = -D_8007589C[scanIndex].unk_0x08 * scrollFrames;
                D_8007589C[scanIndex].m_RotationY = -D_8007589C[scanIndex].unk_0x09 * scrollFrames;
                D_8007589C[scanIndex].m_RotationZ = -D_8007589C[scanIndex].unk_0x0A * scrollFrames;
                D_8007589C[scanIndex].unk_0x0B = scrollFrames;
              }
              scanIndex++;
            } while (scanIndex < D_800756E4);
          }
        }
        entryIndex++;
      } while (displayedCount >= entryIndex);
    }
    scanIndex = new_var2;
    if (D_800756E4 > 0) {
      do {
        if (D_80075708[D_8007589C[scanIndex].unk_0x18].m_State == 2) {
          if (D_8007589C[scanIndex].unk_0x04 == 2) {
            D_8007589C[scanIndex].unk_0x04 = 3;
          } else if (D_8007589C[scanIndex].unk_0x04 == 4) {
            D_8007589C[scanIndex].unk_0x04 = 0;
          }
        }
        scanIndex++;
      } while (scanIndex < D_800756E4);
    }
    scanIndex = 0;
    if (D_800756E4 > 0) {
      do {
        switch (D_8007589C[scanIndex].unk_0x04) {
        case 1:
          D_8007589C[scanIndex].m_Position.x += D_8007589C[scanIndex].m_VelocityX;
          D_8007589C[scanIndex].m_Position.z += D_8007589C[scanIndex].m_VelocityZ;
          D_8007589C[scanIndex].m_RotationX += D_8007589C[scanIndex].unk_0x08;
          D_8007589C[scanIndex].m_RotationY += D_8007589C[scanIndex].unk_0x09;
          D_8007589C[scanIndex].m_RotationZ += D_8007589C[scanIndex].unk_0x0A;
          if (--D_8007589C[scanIndex].unk_0x0B == 0) {
            D_8007589C[scanIndex].unk_0x04 = 2;
            D_8007589C[scanIndex].m_VelocityX = RandRangeSigned(3, 0xB);
            D_8007589C[scanIndex].m_VelocityY = -RandRange(6, 0xA);
            D_8007589C[scanIndex].m_VelocityZ = RandRange(-0x23, 0x23);
            D_8007589C[scanIndex].unk_0x08 = RandRangeSigned(4, 9);
            D_8007589C[scanIndex].unk_0x09 = RandRangeSigned(4, 9);
            D_8007589C[scanIndex].unk_0x0A = RandRangeSigned(4, 9);
          }
          break;
        case 3:
          D_8007589C[scanIndex].m_Position.x += D_8007589C[scanIndex].m_VelocityX;
          D_8007589C[scanIndex].m_Position.y += D_8007589C[scanIndex].m_VelocityY;
          D_8007589C[scanIndex].m_Position.z += D_8007589C[scanIndex].m_VelocityZ;
          D_8007589C[scanIndex].m_VelocityY += 1;
          D_8007589C[scanIndex].m_RotationX += D_8007589C[scanIndex].unk_0x08;
          D_8007589C[scanIndex].m_RotationY += D_8007589C[scanIndex].unk_0x09;
          D_8007589C[scanIndex].m_RotationZ += D_8007589C[scanIndex].unk_0x0A;
          if (D_8007589C[scanIndex].m_VelocityY >= 0x15) {
            D_8007589C[scanIndex].m_VelocityY = 0x14;
          }
          if (D_8007589C[scanIndex].m_Position.y >= 0x119) {
            D_8007589C[scanIndex].unk_0x04 = 4;
          }
          break;
        }
        scanIndex++;
      } while (scanIndex < D_800756E4);
    }
    new_var = 0;
    if ((D_800756E4 > new_var) &&
        (D_8007589C[D_800756E4 - 1].unk_0x04 == 0)) {
      do {
        D_800756E4 -= 1;
      } while ((D_800756E4 > 0) &&
               (D_8007589C[D_800756E4 - 1].unk_0x04 == 0));
    }
  }
  if (g_CreditsStage != -1) {
    if (g_CreditsStage > 0) {
      CDLoadTime();
      if (g_CdState.m_IsReading != 0) {
        return;
      }
      if (CdSync(1, 0) != 2) {
        return;
      }
    }
    switch (g_CreditsStage) {
    case 0:
      CDLoadAsync(g_CdState.m_WadSector, D_800757EC, 0x800,
                  g_WadHeader.m_Credits1Data[g_CreditsSequence].m_Offset,
                  0x258);
      g_CreditsStage += 1;
      break;
    case 1:
      Memcpy(&g_LevelHeader, D_800757EC, 0x1D0);
      CDLoadAsync(g_CdState.m_WadSector, D_800757EC, 0x20000,
                  g_LevelHeader.m_VramSramOffset +
                      g_WadHeader.m_Credits1Data[g_CreditsSequence].m_Offset,
                  0x258);
      g_CreditsStage += 1;
      break;
    case 2:
      /* NOTE: reuses textPos storage for the temp rect (matches ref homes) */
      setRECT((RECT *) &textPos, 0x200, 0x180, 0x200, 0x80);
      DrawSync(0);
      LoadImage((RECT *) &textPos, (u_long *) D_800757EC);
      DrawSync(0);
      D_80075958 =
          (g_LevelHeader.m_DataSize + 0x40000) + g_LevelHeader.m_SceneSize;
      CDLoadAsync(g_CdState.m_WadSector, D_800757EC, D_80075958,
                  g_LevelHeader.m_VramSramOffset +
                      g_WadHeader.m_Credits1Data[g_CreditsSequence].m_Offset +
                      0x20000,
                  0x258);
      g_CreditsStage += 1;
      break;
    case 3:
      D_8007576C = 0;
      break;
    case 4:
      /* NOTE: reuses textPos.z storage for the temp rect (matches ref homes) */
      setRECT((RECT *) &textPos.z, 0x200, 0x80, 0x200, 0x100);
      g_Buffers.m_CopyBuf = (void *) g_CreditsBuffer;
      g_Buffers.m_DiscCopyBuf = (void *) g_CreditsBuffer;
      DrawSync(0);
      LoadImage((RECT *) &textPos.z, (u_long *) D_800757EC);
      setRECT((RECT *) &textPos.z, 0x200, 0x180, 0x200, 0x80);
      MoveImage((RECT *) &textPos.z, 0x200, 0);
      DrawSync(0);
      Memcpy((void *) g_CreditsBuffer, D_800757EC + 0x40000,
             D_80075958 - 0x40000);
      D_800757EC = (u_char *) (g_CreditsBuffer + D_80075958 - 0x40000);
      g_Buffers.m_ModelData = LoadLevelData(g_Buffers.m_DiscCopyBuf, 1);
      g_Cyclorama = g_NewCyclorama;
      pScene = (u_char *) g_Buffers.m_DiscCopyBuf + g_LevelHeader.m_DataSize;
      g_Buffers.m_LevelScene = pScene;
      g_CreditsDataPtr = (int) pScene;
      g_Buffers.m_LevelSceneSize = g_LevelHeader.m_SceneSize;
      g_Buffers.m_LevelSceneOffset = g_LevelHeader.m_SceneOffset;
      if ((g_CreditsSequence % 10) < 9) {
        g_CreditsStage = 0;
      } else {
        g_CreditsStage = 3;
      }
      g_CreditsSequence += 1;
      break;
    }
  }
}

INCLUDE_ASM("asm/nonmatchings/overlays/credits", func_credits_8007BFD0);

void func_credits_8007C338(void) {}
