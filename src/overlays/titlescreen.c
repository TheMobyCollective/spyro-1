#include "titlescreen.h"

#include "buffers.h"
#include "camera.h"
#include "cd.h"
#include "common.h"
#include "cutscene.h"
#include "cyclorama.h"
#include "dragon.h"
#include "environment.h"
#include "fairy.h"
#include "gamepad.h"
#include "gamestates/draw.h"
#include "gamestates/update.h"
#include "graphics.h"
#include "initialization.h"
#include "libetc.h"
#include "libgpu.h"
#include "libmcrd.h"
#include "memory.h"
#include "moby_lists.h"
#include "music.h"
#include "rand.h"
#include "renderers.h"
#include "sony_image.h"
#include "specular_and_metal.h"
#include "spu.h"
#include "spyro.h"

extern struct {
  int post;
  int pre;
} D_80075950;

extern void CrashDemoLaunch(void);

static const char s_SaveFileName[20] = "BASCUS-94228SPYRO";

#define SWAP_MENU_SELECTION                                                    \
  g_TitlescreenState.m_SubTick = 16;                                           \
  g_TitlescreenState.m_OptionSelected =                                        \
      1 - g_TitlescreenState.m_OptionSelected;                                 \
  TitlescreenPlaySound(0);

#define RELOAD_MEMCARDS                                                        \
  g_TitlescreenState.m_SubState = TS_SubState_LoadMemCards;                    \
  g_TitlescreenState.m_State = 0;                                              \
  MemCardSync(McSyncMode_Sync,                                                 \
              (long *)&g_TitlescreenState.m_CardCompletedFunc,                 \
              (long *)&g_TitlescreenState.m_CardResultData);

#define START_DEMO(DEMO_TYPE)                                                  \
  g_TitlescreenState.m_State = 5;                                              \
  g_TitlescreenState.m_DemoType = DEMO_TYPE;                                   \
  g_FairyCutscene.unk_0x20 =                                                   \
      g_TitlescreenState.m_MemCardSave->m_Header.m_Clut[15];                   \
  g_FairyCutscene.m_HasMemoryCard = 1;                                         \
  g_FairyCutscene.m_MemoryCardSlot = g_TitlescreenState.m_CardSelected << 4;   \
  g_FairyCutscene.unk_0x1c = g_TitlescreenState.m_OptionSelected;              \
  MemCardSync(McSyncMode_Sync,                                                 \
              (long *)&g_TitlescreenState.m_CardCompletedFunc,                 \
              (long *)&g_TitlescreenState.m_CardResultData);

#define DRAW_OPTIONS(op1, op2)                                                 \
  if (g_TitlescreenState.m_SubTick > 7) {                                      \
    TitlescreenDrawSprite(128, 88, op1,                                        \
                          (g_TitlescreenState.m_OptionSelected == 0 &&         \
                           ((g_TitlescreenState.m_SubTick & 0xF) < 8))         \
                              ? TS_Color_Yellow                                \
                              : TS_Color_Gray);                                \
    TitlescreenDrawSprite(256, 88, op2,                                        \
                          (g_TitlescreenState.m_OptionSelected == 1 &&         \
                           ((g_TitlescreenState.m_SubTick & 0xF) < 8))         \
                              ? TS_Color_Yellow                                \
                              : TS_Color_Gray);                                \
  }

void TitlescreenPlaySound(int pSoundId) {
  g_Spu.m_SoundDefinitions = &g_CutsceneSoundDef;
  g_Spu.m_SoundDefinitions->m_Addr = g_TitlescreenSPUOffsets[pSoundId] + 0x1010;
  g_Spu.m_SoundDefinitions->m_LoopAddr = -1;
  g_Spu.m_SoundDefinitions->unk_0x8 = 0x50;
  g_Spu.m_SoundDefinitions->m_Pitch = 0x800;
  g_Spu.m_SoundDefinitions->m_PitchVariance = 0;
  g_Spu.m_SoundDefinitions->m_PitchMultiplier = 0;
  g_Spu.m_SoundDefinitions->m_VarianceType = 0;
  g_Spu.m_NextSoundOverrideFlags = 1;
  g_Spu.m_VolumeOverride.left = 0x3FFF;
  g_Spu.m_VolumeOverride.right = 0x3FFF;
  PlaySound(0, nullptr, 0x10, (u_char *)&g_DragonCutscene.m_SoundVoice);
}

void TitlescreenUpdate(void) {
  int old_state = g_TitlescreenState.m_Mode < 2 ? g_TitlescreenState.m_SubState
                                                : g_TitlescreenState.m_State;

  g_CutsceneLayout->m_CurrentTick += 2;

  if (g_CutsceneLayout->m_CurrentTick < 1100) {
    g_TitlescreenState.m_Tick = 0;
    if (g_TitlescreenState.m_SubState == 2 &&
        g_CutsceneLayout->m_CurrentTick >= 300 &&
        (g_Pad.m_Held & (PAD_START | PAD_CROSS)) != 0) {
      StopSound(g_DragonCutscene.m_SoundVoice, 4);
      g_CutsceneLayout->m_CurrentTick = 1170;
    }
  } else {
    if (g_CutsceneLayout->m_CurrentTick == 1344 && (rand() & 3) != 0) {
      g_CutsceneLayout->m_CurrentTick = 1172;
    } else if (g_CutsceneLayout->m_CurrentTick >= 1530) {
      g_CutsceneLayout->m_CurrentTick = 1172;
    }
  }

  if (g_Fade)
    --g_Fade;

  func_8002BFE0(g_CutsceneLayout->m_CurrentTick);

  g_Camera.m_Rotation.x = 0;
  g_Camera.m_Rotation.y += 16;

  switch (g_TitlescreenState.m_Mode) {
  case TSM_Init: {
    if (g_TitlescreenState.m_SubState < 2) {
      // Kick out while we're still loading from the CD
      CDLoadTime();
      if (g_CdState.m_IsReading != 0 || CdSync(1, 0) != CdlComplete ||
          (g_CdMusic.m_Flags & 0x40) == 0)
        break;

      if (g_TitlescreenState.m_SubState == 0) {
        // Kick off loading titlescreen data from the CD
        CDLoadAsync(g_CdState.m_WadSector,
                    g_Buffers.m_LowerPolyBuffer - 0x40000, 0x40000,
                    g_WadHeader.m_wad1.m_Offset, 600);
        g_TitlescreenState.m_SubState = 1;
      } else if (g_TitlescreenState.m_SubState == 1) {
        // Once we've loaded titlescreen data, initialize music and load up the
        // sprite sheet into vram
        RECT rc;
        g_CdMusic.m_CurrentTrack = 20;
        g_CdMusic.m_EasterEggTicks = 155520000;
        func_800567F4(20, 0x1);
        setRECT(&rc, 512, 256, 512, 256);
        LoadImage(&rc, g_Buffers.m_LowerPolyBuffer - 0x40000);
        g_TitlescreenState.m_SubState = 2;
      }
    } else if (g_TitlescreenState.m_SubState == 2) {
      // Titlescreen sequence is playing, just waiting for a bit
      if (g_CutsceneLayout->m_CurrentTick < 1169) {
        g_TitlescreenState.m_SubTick = 0;
      } else {
        if (g_TitlescreenState.m_SubTick == 1) {
          TitlescreenPlaySound(6);
        }
        if (g_TitlescreenState.m_SubTick >= 16)
          g_TitlescreenState.m_SubState = 3;
      }
    } else if (g_TitlescreenState.m_SubState == 3) {
      // Ready for button inputs or to time out to show the demo
      if ((g_Pad.m_Held & (PAD_L1 | PAD_TRIANGLE)) == (PAD_L1 | PAD_TRIANGLE)) {
        func_80056B28(0); // stop all sounds
        TitlescreenPlaySound(9);
        SpuUpdate();
        while (g_CdState.m_IsReading != 0 || CdSync(1, 0) != CdlComplete ||
               (g_CdMusic.m_Flags & 0x40) == 0) {
          CDLoadTime();
          func_8005637C(); // update sounds
          CDMusicUpdate();
        }
        CrashDemoLaunch();
      } else if (g_Pad.m_Down & (PAD_START | PAD_CROSS)) {
        g_TitlescreenState.m_SubState = 4;
        TitlescreenPlaySound(7);
      } else if (g_TitlescreenState.m_Tick >= 990) {
        g_TitlescreenState.m_SubState = 5;
      }
    } else if (g_TitlescreenState.m_SubState == 4) {
      // Animate out the logo, move to mem card screen
      if (g_TitlescreenState.m_SubTick == 16) {
        TitlescreenPlaySound(8);
      }
      if (g_TitlescreenState.m_SubTick >= 32) {
        g_TitlescreenState.m_Mode = TSM_Menu;
        g_TitlescreenState.m_SubState = TS_SubState_LoadMemCards;
        g_TitlescreenState.m_State = 0;
        MemCardStart();
      }
    } else if (g_TitlescreenState.m_SubState == 5) {
      // Button push timed out, fade out the screen for 16 ticks and then move
      // to demo mode
      if (g_TitlescreenState.m_SubTick == 0) {
        TitlescreenPlaySound(5);
      }
      g_Fade = g_TitlescreenState.m_SubTick;
      if (g_Fade > 15)
        g_Fade = 15;
      if (g_TitlescreenState.m_SubTick >= 16) {
        RECT rc;
        g_TitlescreenState.m_Mode = TSM_Demo;
        g_TitlescreenState.m_State = 0;
        g_TitlescreenState.m_DemoType = 2;
        setRECT(&rc, 0, 0, 512, 480);
        ClearImage(&rc, 0, 0, 0);
        DrawSync(0);
      }
    }
    break;
  }
  case TSM_Menu: {
    switch (g_TitlescreenState.m_SubState) {
    case TS_SubState_LoadMemCards: {
      // wait for async mem card function to finish
      if (MemCardSync(McSyncMode_Async,
                      (long *)&g_TitlescreenState.m_CardCompletedFunc,
                      (long *)&g_TitlescreenState.m_CardResultData) == 0)
        break;

      if (g_TitlescreenState.m_State == 0) {
        // Try to ping port A for a mem card
        TitlescreenPlaySound(2);
        MemCardAccept(0 /*port A card 0*/);
        g_TitlescreenState.m_State = 1;
      } else if (g_TitlescreenState.m_State == 1) {
        // Pull memcard state for port A
        g_TitlescreenState.m_CardStates[0] =
            g_TitlescreenState.m_CardResultData;

        if (g_TitlescreenState.m_CardStates[0] == McErrNewCard)
          g_TitlescreenState.m_CardStates[0] = McErrNone;
        if (g_TitlescreenState.m_CardStates[0] == McErrNotFormat) {
          g_TitlescreenState.m_CardStates[0] = McErrNone;
          g_TitlescreenState.m_CardNeedsFormat[0] = 1;
        } else
          g_TitlescreenState.m_CardNeedsFormat[0] = 0;

        // Now go and ping port B
        MemCardAccept(0x10 /*port B card 0*/);
        g_TitlescreenState.m_State = 2;
      } else {
        // Pull memcard state for port B
        g_TitlescreenState.m_CardStates[1] =
            g_TitlescreenState.m_CardResultData;

        if (g_TitlescreenState.m_CardStates[1] == McErrNewCard)
          g_TitlescreenState.m_CardStates[1] = McErrNone;
        if (g_TitlescreenState.m_CardStates[1] == McErrNotFormat) {
          g_TitlescreenState.m_CardStates[1] = McErrNone;
          g_TitlescreenState.m_CardNeedsFormat[1] = 1;
        } else {
          g_TitlescreenState.m_CardNeedsFormat[1] = 0;
        }

        // Figure out what screen to go to for our A/B memcard states
        if (g_TitlescreenState.m_CardStates[0] == McErrNone &&
            g_TitlescreenState.m_CardStates[1] == McErrNone) {
          // Both ports have a valid, formatted memcard, go to select menu
          g_TitlescreenState.m_SubState = TS_SubState_SelectMemCard;
          g_TitlescreenState.m_OptionSelected = 0;
        } else if (g_TitlescreenState.m_CardStates[0] == McErrNone &&
                   !g_TitlescreenState.m_CardNeedsFormat[0]) {
          // Port A is valid, and doesn't need formatting, assumme this one is
          // selected
          g_TitlescreenState.m_CardSelected = 0;
          g_TitlescreenState.m_SubState = TS_SubState_ReadSelectedCard;
          g_TitlescreenState.m_State = 0;
          g_TitlescreenState.m_MemCardTries = 0;
          g_TitlescreenState.m_OptionSelected = 0;
        } else if (g_TitlescreenState.m_CardStates[1] == McErrNone &&
                   !g_TitlescreenState.m_CardNeedsFormat[1]) {
          // Port B is valid, and doesn't need formatting, assumme this one is
          // selected
          g_TitlescreenState.m_CardSelected = 1;
          g_TitlescreenState.m_SubState = TS_SubState_ReadSelectedCard;
          g_TitlescreenState.m_State = 0;
          g_TitlescreenState.m_MemCardTries = 0;
          g_TitlescreenState.m_OptionSelected = 0;
        } else if (g_TitlescreenState.m_CardStates[0] == McErrNone &&
                   g_TitlescreenState.m_CardNeedsFormat[0]) {
          // Port A is valid, but needs to be formatted, ask if that's ok
          g_TitlescreenState.m_CardSelected = 0;
          g_TitlescreenState.m_SubState = TS_SubState_MemCardFormat1;
          g_TitlescreenState.m_OptionSelected = 0;
        } else if (g_TitlescreenState.m_CardStates[1] == McErrNone &&
                   g_TitlescreenState.m_CardNeedsFormat[1]) {
          // Port B is valid, but needs to be formatted, ask if that's ok
          g_TitlescreenState.m_CardSelected = 1;
          g_TitlescreenState.m_SubState = TS_SubState_MemCardFormat1;
          g_TitlescreenState.m_OptionSelected = 0;
        } else {
          // No valid cards found
          g_TitlescreenState.m_CardSelected = -1;
          g_TitlescreenState.m_SubState = TS_SubState_NoMemoryCard;
          g_TitlescreenState.m_OptionSelected = 0;
        }
      }
      break;
    }
    case TS_SubState_ReadSelectedCard: {
      // Wait for async mem card function to finish
      if (MemCardSync(McSyncMode_Async,
                      (long *)&g_TitlescreenState.m_CardCompletedFunc,
                      (long *)&g_TitlescreenState.m_CardResultData) == 0)
        break;

      if (g_TitlescreenState.m_State == 0) {
        // Read save file from the selected card
        MemCardReadFile(g_TitlescreenState.m_CardSelected << 4,
                        (char *)s_SaveFileName,
                        (u_long *)g_TitlescreenState.m_MemCardSave, 0,
                        sizeof(MemCardSaveFile));
        g_TitlescreenState.m_State = 1;
      } else if (g_TitlescreenState.m_State == 1) {
        // Save file has been read
        if (g_TitlescreenState.m_CardResultData == McErrNone) {
          // No errors reading, check to see if data is intact
          if (SaveChecksum(
                  (u_char *)&g_TitlescreenState.m_MemCardSave->m_Saves[0]) ==
                  g_TitlescreenState.m_MemCardSave->m_Saves[0].m_Checksum &&
              SaveChecksum(
                  (u_char *)&g_TitlescreenState.m_MemCardSave->m_Saves[1]) ==
                  g_TitlescreenState.m_MemCardSave->m_Saves[1].m_Checksum &&
              SaveChecksum(
                  (u_char *)&g_TitlescreenState.m_MemCardSave->m_Saves[2]) ==
                  g_TitlescreenState.m_MemCardSave->m_Saves[2].m_Checksum) {
            // Save cheecksums matched, go to save file picker
            g_TitlescreenState.m_Mode = TSM_Loading;
            g_TitlescreenState.m_State = 4;
            g_TitlescreenState.m_OptionSelected = 1;
            g_StateSwitch = 1;
            TitlescreenPlaySound(9);
          } else if (g_TitlescreenState.m_MemCardTries < 2) {
            // Save checksums didn't match, retry the read up to 2 times
            g_TitlescreenState.m_MemCardTries++;
            g_TitlescreenState.m_State = 0;
          } else {
            // Retries didn't work, recreate the ones that looked like garbage
            func_8001277C(); // reset game
            if (SaveChecksum(
                    (u_char *)&g_TitlescreenState.m_MemCardSave->m_Saves[0]) !=
                g_TitlescreenState.m_MemCardSave->m_Saves[0].m_Checksum)
              SaveCreate(&g_TitlescreenState.m_MemCardSave->m_Saves[0]);
            if (SaveChecksum(
                    (u_char *)&g_TitlescreenState.m_MemCardSave->m_Saves[1]) !=
                g_TitlescreenState.m_MemCardSave->m_Saves[1].m_Checksum)
              SaveCreate(&g_TitlescreenState.m_MemCardSave->m_Saves[1]);
            if (SaveChecksum(
                    (u_char *)&g_TitlescreenState.m_MemCardSave->m_Saves[2]) !=
                g_TitlescreenState.m_MemCardSave->m_Saves[2].m_Checksum)
              SaveCreate(&g_TitlescreenState.m_MemCardSave->m_Saves[2]);

            // Go to the save file picker
            g_TitlescreenState.m_Mode = TSM_Loading;
            g_TitlescreenState.m_State = 4;
            g_TitlescreenState.m_OptionSelected = 1;
            g_StateSwitch = 1;
            TitlescreenPlaySound(9);
          }
        } else if (g_TitlescreenState.m_CardResultData == McErrFileNotExist) {
          // No save file, ask if we can create one
          g_TitlescreenState.m_SubState = TS_SubState_CreateSaveConfirm;
          g_TitlescreenState.m_OptionSelected = 0;
        } else {
          // No memory card available anymore
          g_TitlescreenState.m_SubState = TS_SubState_MemCardUnavailable;
          g_TitlescreenState.m_OptionSelected = 0;
        }
      }
      break;
    }
    case TS_SubState_NoMemoryCard: {
      CheckMemcardsExist();

      if (g_TitlescreenState.m_CardStates[0] == McErrNone ||
          g_TitlescreenState.m_CardStates[0] == McErrNewCard ||
          g_TitlescreenState.m_CardStates[1] == McErrNone ||
          g_TitlescreenState.m_CardStates[1] == McErrNewCard) {
        RELOAD_MEMCARDS
        break;
      }

      if (g_TitlescreenState.m_SubTick == 0) {
        TitlescreenPlaySound(4);
      }

      if (g_TitlescreenState.m_SubTick >= 8) {
        if (func_80032AB0()) {
          // Triangle was pushed, func_80032AB0 already took care of it
        } else if (g_Pad.m_Down & (PAD_LEFT | PAD_RIGHT)) {
          SWAP_MENU_SELECTION
        } else if (g_Pad.m_Down & (PAD_START | PAD_CROSS)) {
          if (g_TitlescreenState.m_OptionSelected == 0) {
            g_TitlescreenState.m_SubState = TS_SubState_WarningNoSave;
            TitlescreenPlaySound(3);
          } else {
            RELOAD_MEMCARDS
          }
        }
      }
      break;
    }
    case TS_SubState_MemCardUnavailable: {
      CheckMemcardsExist();

      if (g_TitlescreenState.m_CardSelected >= 0) {
        if (g_TitlescreenState
                    .m_CardStates[g_TitlescreenState.m_CardSelected] !=
                McErrNone ||
            g_TitlescreenState
                    .m_CardStates[1 - g_TitlescreenState.m_CardSelected] ==
                McErrNewCard) {
          RELOAD_MEMCARDS
          break;
        }
      } else {
        if (g_TitlescreenState.m_CardStates[0] == McErrNone ||
            g_TitlescreenState.m_CardStates[0] == McErrNewCard ||
            g_TitlescreenState.m_CardStates[1] == McErrNone ||
            g_TitlescreenState.m_CardStates[1] == McErrNewCard) {
          RELOAD_MEMCARDS
          break;
        }
      }

      if (g_TitlescreenState.m_SubTick >= 8) {
        if (func_80032AB0()) {
          // Triangle was pushed, func_80032AB0 already took care of it
        } else if (g_Pad.m_Down & (PAD_LEFT | PAD_RIGHT)) {
          SWAP_MENU_SELECTION
        } else if (g_Pad.m_Down & (PAD_START | PAD_CROSS)) {
          if (g_TitlescreenState.m_OptionSelected == 0) {
            g_TitlescreenState.m_SubState = TS_SubState_WarningNoSave;
            TitlescreenPlaySound(3);
          } else {
            RELOAD_MEMCARDS
          }
        }
      }
      break;
    }
    case TS_SubState_WarningNoSave: {
      CheckMemcardsExist();

      if (g_TitlescreenState.m_CardSelected >= 0) {
        if (g_TitlescreenState
                    .m_CardStates[g_TitlescreenState.m_CardSelected] !=
                McErrNone ||
            g_TitlescreenState
                    .m_CardStates[1 - g_TitlescreenState.m_CardSelected] ==
                McErrNewCard) {
          RELOAD_MEMCARDS
          break;
        }
      } else {
        if (g_TitlescreenState.m_CardStates[0] == McErrNone ||
            g_TitlescreenState.m_CardStates[0] == McErrNewCard ||
            g_TitlescreenState.m_CardStates[1] == McErrNone ||
            g_TitlescreenState.m_CardStates[1] == McErrNewCard) {
          RELOAD_MEMCARDS
          break;
        }
      }

      // Mem card states still the same, process buttons after a few more ticks
      if (g_TitlescreenState.m_SubTick >= 8) {
        if (func_80032AB0()) {
          // Triangle was pushed, func_80032AB0 already took care of it
        } else if (g_Pad.m_Down & (PAD_LEFT | PAD_RIGHT)) {
          SWAP_MENU_SELECTION
        } else if (g_Pad.m_Down & (PAD_CROSS | PAD_START)) {
          if (g_TitlescreenState.m_OptionSelected == 0) {
            func_8001277C();
            g_TitlescreenState.m_Mode = TSM_Loading;
            g_TitlescreenState.m_State = 5;
            g_TitlescreenState.m_DemoType = 0;
            g_FairyCutscene.m_HasMemoryCard = 0;
          } else {
            RELOAD_MEMCARDS
          }
        }
      }
      break;
    }
    case TS_SubState_MemCardFormat1:
    case TS_SubState_MemCardFormat2: {
      CheckMemcardsExist();

      if (g_TitlescreenState.m_CardStates[g_TitlescreenState.m_CardSelected] !=
              McErrNone ||
          g_TitlescreenState
                  .m_CardStates[1 - g_TitlescreenState.m_CardSelected] ==
              McErrNewCard) {
        RELOAD_MEMCARDS
        break;
      }

      if (g_TitlescreenState.m_SubTick == 0) {
        TitlescreenPlaySound(3);
      }

      if (g_TitlescreenState.m_SubTick >= 8) {
        if (func_80032AB0()) {
          // Triangle was pushed, func_80032AB0 already took care of it
        } else if (g_Pad.m_Down & (PAD_LEFT | PAD_RIGHT)) {
          SWAP_MENU_SELECTION
        } else if (g_Pad.m_Down & (PAD_CROSS | PAD_START)) {
          if (g_TitlescreenState.m_OptionSelected == 0) {
            if (g_TitlescreenState.m_SubState == TS_SubState_MemCardFormat1) {
              g_TitlescreenState.m_SubState = TS_SubState_MemCardFormat2;
              g_TitlescreenState.m_OptionSelected = 1;
            } else {
              g_TitlescreenState.m_SubState = TS_SubState_MemCardFormatting;
              MemCardSync(McSyncMode_Sync,
                          (long *)&g_TitlescreenState.m_CardCompletedFunc,
                          (long *)&g_TitlescreenState.m_CardResultData);
              TitlescreenPlaySound(2);
            }
          } else {
            g_TitlescreenState.m_SubState = TS_SubState_MemCardUnavailable;
            g_TitlescreenState.m_OptionSelected = 0;
            TitlescreenPlaySound(3);
          }
        }
      }
      break;
    }
    case TS_SubState_MemCardFormatting: {
      if (g_TitlescreenState.m_SubTick >= 2) {
        g_TitlescreenState.m_CardResultData =
            MemCardFormat(g_TitlescreenState.m_CardSelected << 4);
        if (g_TitlescreenState.m_CardResultData == McErrNone) {
          g_TitlescreenState.m_CardStates[g_TitlescreenState.m_CardSelected] =
              McErrNone;
          g_TitlescreenState.m_SubState = TS_SubState_FormatComplete;
          g_TitlescreenState.m_OptionSelected = 0; // continue
          TitlescreenPlaySound(9);
        } else {
          g_TitlescreenState.m_SubState = TS_SubState_FormatFailed;
          g_TitlescreenState.m_OptionSelected = 1; // cancel
          TitlescreenPlaySound(4);
        }
      }
      break;
    }
    case TS_SubState_FormatComplete: {
      CheckMemcardsExist();

      if (g_TitlescreenState.m_CardStates[g_TitlescreenState.m_CardSelected] !=
              McErrNone ||
          g_TitlescreenState
                  .m_CardStates[1 - g_TitlescreenState.m_CardSelected] ==
              McErrNewCard) {
        RELOAD_MEMCARDS
        break;
      }

      if (g_TitlescreenState.m_SubTick >= 8) {
        if (func_80032AB0()) {
          // Triangle was pushed, func_80032AB0 already took care of it
        } else if (g_Pad.m_Down & (PAD_CROSS | PAD_START)) {
          TitlescreenPlaySound(1);
          g_TitlescreenState.m_SubState = TS_SubState_ReadSelectedCard;
          g_TitlescreenState.m_State = 0;
          g_TitlescreenState.m_MemCardTries = 0;
          g_TitlescreenState.m_OptionSelected = 1;
        }
      }

      break;
    }
    case TS_SubState_FormatFailed: {
      CheckMemcardsExist();

      if (g_TitlescreenState.m_CardStates[g_TitlescreenState.m_CardSelected] !=
              McErrNone ||
          g_TitlescreenState
                  .m_CardStates[1 - g_TitlescreenState.m_CardSelected] ==
              McErrNewCard) {
        RELOAD_MEMCARDS
        break;
      }

      if (g_TitlescreenState.m_SubTick >= 8) {
        if (func_80032AB0()) {
          // Triangle was pushed, func_80032AB0 already took care of it
        } else if (g_Pad.m_Down & (PAD_LEFT | PAD_RIGHT)) {
          SWAP_MENU_SELECTION
        } else if (g_Pad.m_Down & (PAD_CROSS | PAD_START)) {
          if (g_TitlescreenState.m_OptionSelected == 0) {
            // retry format
            g_TitlescreenState.m_SubState = TS_SubState_MemCardFormatting;
            MemCardSync(McSyncMode_Sync,
                        (long *)&g_TitlescreenState.m_CardCompletedFunc,
                        (long *)&g_TitlescreenState.m_CardResultData);
            TitlescreenPlaySound(2);
          } else {
            g_TitlescreenState.m_SubState = TS_SubState_MemCardUnavailable;
            g_TitlescreenState.m_OptionSelected = 0;
            TitlescreenPlaySound(3);
          }
        }
      }
      break;
    }
    case TS_SubState_CreateSaveConfirm: {
      CheckMemcardsExist();

      if (g_TitlescreenState.m_CardStates[g_TitlescreenState.m_CardSelected] !=
              McErrNone ||
          g_TitlescreenState
                  .m_CardStates[1 - g_TitlescreenState.m_CardSelected] ==
              McErrNewCard) {
        RELOAD_MEMCARDS
        break;
      }

      if (g_TitlescreenState.m_SubTick == 0) {
        TitlescreenPlaySound(3);
      }

      if (g_TitlescreenState.m_SubTick >= 8) {
        if (func_80032AB0()) {
          // Triangle was pushed, func_80032AB0 already took care of it
        } else if (g_Pad.m_Down & (PAD_LEFT | PAD_RIGHT)) {
          SWAP_MENU_SELECTION
        } else if (g_Pad.m_Down & (PAD_CROSS | PAD_START)) {
          if (g_TitlescreenState.m_OptionSelected == 0) {
            g_TitlescreenState.m_SubState = TS_SubState_CreatingSaveFile;
            g_TitlescreenState.m_State = 0;
            g_TitlescreenState.m_MemCardTries = 0;
            MemCardSync(McSyncMode_Sync,
                        (long *)&g_TitlescreenState.m_CardCompletedFunc,
                        (long *)&g_TitlescreenState.m_CardResultData);
            TitlescreenPlaySound(2);
          } else {
            g_TitlescreenState.m_SubState = TS_SubState_MemCardUnavailable;
            g_TitlescreenState.m_OptionSelected = 0;
            TitlescreenPlaySound(3);
          }
        }
      }

      break;
    }
    case TS_SubState_CreatingSaveFile: {
      int i;
      if (g_TitlescreenState.m_State == 0) {
        g_TitlescreenState.m_State = 1; // ok ...
      } else if (g_TitlescreenState.m_State == 1) {
        if (g_TitlescreenState.m_MemCardTries == 0) {
          g_TitlescreenState.m_CardResultData =
              MemCardCreateFile(g_TitlescreenState.m_CardSelected << 4,
                                (char *)s_SaveFileName, 1);
        }
        if (g_TitlescreenState.m_CardResultData == McErrNone) {
          char *mcs = (char *)g_TitlescreenState.m_MemCardSave;

          // Copy over the header/icons
          Memcpy(g_TitlescreenState.m_MemCardSave, g_MemCardSaveHeader,
                 sizeof(g_MemCardSaveHeader));

          g_FairyCutscene.unk_0x20 = func_80017FD4();
          g_TitlescreenState.m_MemCardSave->m_Header.m_Clut[15] =
              g_FairyCutscene.unk_0x20;

          // Reset game and create all 3 saves
          mcs += sizeof(g_MemCardSaveHeader);
          func_8001277C();
          for (i = 0; i < 3; ++i) {
            SaveCreate((SaveFile *)(mcs + i * sizeof(SaveFile)));
          }
          MemCardWriteFile(g_TitlescreenState.m_CardSelected << 4,
                           (char *)s_SaveFileName,
                           (u_long *)g_TitlescreenState.m_MemCardSave, 0,
                           sizeof(MemCardSaveFile));

          g_TitlescreenState.m_State = 2;
        } else if (g_TitlescreenState.m_CardResultData == McErrBlockFull) {
          g_TitlescreenState.m_SubState = TS_SubState_MemCardFull;
          g_TitlescreenState.m_OptionSelected = 0;
        } else {
          g_TitlescreenState.m_SubState = TS_SubState_CantCreateSave;
          g_TitlescreenState.m_OptionSelected = 0;
        }
      } else if (g_TitlescreenState.m_State == 2) {
        // Kick back if MemCardWrite is not complete yet
        if (MemCardSync(McSyncMode_Async,
                        (long *)&g_TitlescreenState.m_CardCompletedFunc,
                        (long *)&g_TitlescreenState.m_CardResultData) == 0)
          break;

        // Write is done, check to see if it was successful
        if (g_TitlescreenState.m_CardResultData != McErrNone) {
          g_TitlescreenState.m_SubState = TS_SubState_CantCreateSave;
          g_TitlescreenState.m_OptionSelected = 0;
        } else {
          // Save succeeded, let's re-read it off the card
          MemCardReadFile(g_TitlescreenState.m_CardSelected << 4,
                          (char *)s_SaveFileName,
                          (u_long *)g_TitlescreenState.m_MemCardSave, 0,
                          sizeof(MemCardSaveFile));
          g_TitlescreenState.m_State = 3;
        }
      } else {
        // Make sure the re-read looks good
        if (g_TitlescreenState.m_CardResultData == McErrNone) {
          if (SaveChecksum(
                  (u_char *)&g_TitlescreenState.m_MemCardSave->m_Saves[0]) ==
                  g_TitlescreenState.m_MemCardSave->m_Saves[0].m_Checksum &&
              SaveChecksum(
                  (u_char *)&g_TitlescreenState.m_MemCardSave->m_Saves[1]) ==
                  g_TitlescreenState.m_MemCardSave->m_Saves[1].m_Checksum &&
              SaveChecksum(
                  (u_char *)&g_TitlescreenState.m_MemCardSave->m_Saves[2]) ==
                  g_TitlescreenState.m_MemCardSave->m_Saves[2].m_Checksum) {
            g_TitlescreenState.m_Mode = TSM_Loading;
            g_TitlescreenState.m_State = 4;
            g_TitlescreenState.m_OptionSelected = 0;
            g_StateSwitch = 1;
            TitlescreenPlaySound(9);
          } else {
            if (g_TitlescreenState.m_MemCardTries < 2) {
              g_TitlescreenState.m_MemCardTries++;
              g_TitlescreenState.m_State = 2;
            } else {
              func_8001277C();
              if (SaveChecksum((u_char *)&g_TitlescreenState.m_MemCardSave
                                   ->m_Saves[0]) !=
                  g_TitlescreenState.m_MemCardSave->m_Saves[0].m_Checksum)
                SaveCreate(&g_TitlescreenState.m_MemCardSave->m_Saves[0]);
              if (SaveChecksum((u_char *)&g_TitlescreenState.m_MemCardSave
                                   ->m_Saves[1]) !=
                  g_TitlescreenState.m_MemCardSave->m_Saves[1].m_Checksum)
                SaveCreate(&g_TitlescreenState.m_MemCardSave->m_Saves[1]);
              if (SaveChecksum((u_char *)&g_TitlescreenState.m_MemCardSave
                                   ->m_Saves[2]) !=
                  g_TitlescreenState.m_MemCardSave->m_Saves[2].m_Checksum)
                SaveCreate(&g_TitlescreenState.m_MemCardSave->m_Saves[2]);
              g_TitlescreenState.m_Mode = TSM_Loading;
              g_TitlescreenState.m_State = 4;
              g_TitlescreenState.m_OptionSelected = 0;
              g_StateSwitch = 1;
              TitlescreenPlaySound(9);
            }
          }
        } else {
          g_TitlescreenState.m_SubState = TS_SubState_CantCreateSave;
          g_TitlescreenState.m_OptionSelected = 0;
        }
      }
      break;
    }
    case TS_SubState_MemCardFull: {
      CheckMemcardsExist();

      if (g_TitlescreenState.m_CardStates[g_TitlescreenState.m_CardSelected] !=
              McErrNone ||
          g_TitlescreenState
                  .m_CardStates[1 - g_TitlescreenState.m_CardSelected] ==
              McErrNewCard) {
        RELOAD_MEMCARDS
        break;
      }

      if (g_TitlescreenState.m_SubTick == 0) {
        TitlescreenPlaySound(4);
      }

      if (g_TitlescreenState.m_SubTick >= 8) {
        if (func_80032AB0()) {
          // Triangle was pushed, func_80032AB0 already took care of it
        } else if (g_Pad.m_Down & (PAD_START | PAD_CROSS)) {
          TitlescreenPlaySound(3);
          g_TitlescreenState.m_SubState = TS_SubState_MemCardUnavailable;
          g_TitlescreenState.m_OptionSelected = 0;
        }
      }
      break;
    }
    case TS_SubState_CantCreateSave: {
      CheckMemcardsExist();

      if (g_TitlescreenState.m_CardStates[g_TitlescreenState.m_CardSelected] !=
              McErrNone ||
          g_TitlescreenState
                  .m_CardStates[1 - g_TitlescreenState.m_CardSelected] ==
              McErrNewCard) {
        RELOAD_MEMCARDS
        break;
      }

      if (g_TitlescreenState.m_SubTick == 0) {
        TitlescreenPlaySound(4);
      }

      if (g_TitlescreenState.m_SubTick >= 8) {
        if (func_80032AB0()) {
          // Triangle was pushed, func_80032AB0 already took care of it
        } else if (g_Pad.m_Down & (PAD_LEFT | PAD_RIGHT)) {
          SWAP_MENU_SELECTION
        } else if (g_Pad.m_Down & (PAD_CROSS | PAD_START)) {
          if (g_TitlescreenState.m_OptionSelected == 0) {
            g_TitlescreenState.m_SubState = TS_SubState_CreatingSaveFile;
            g_TitlescreenState.m_State = 0;
            g_TitlescreenState.m_MemCardTries = 0;
            MemCardSync(McSyncMode_Sync,
                        (long *)&g_TitlescreenState.m_CardCompletedFunc,
                        (long *)&g_TitlescreenState.m_CardResultData);
            TitlescreenPlaySound(2);
          } else {
            g_TitlescreenState.m_SubState = TS_SubState_MemCardUnavailable;
            g_TitlescreenState.m_OptionSelected = 0;
            TitlescreenPlaySound(3);
          }
        }
      }
      break;
    }
    case TS_SubState_SelectMemCard: {
      CheckMemcardsExist();

      if (g_TitlescreenState.m_CardStates[0] == McErrCardNotExist ||
          g_TitlescreenState.m_CardStates[0] == McErrNewCard ||
          g_TitlescreenState.m_CardStates[1] == McErrCardNotExist ||
          g_TitlescreenState.m_CardStates[1] == McErrNewCard) {
        RELOAD_MEMCARDS;
        break;
      }

      if (g_TitlescreenState.m_SubTick == 0) {
        TitlescreenPlaySound(3);
      }

      if (g_TitlescreenState.m_SubTick >= 8) {
        if (g_Pad.m_Down & (PAD_LEFT | PAD_RIGHT)) {
          SWAP_MENU_SELECTION
        } else if (g_Pad.m_Down & (PAD_CROSS | PAD_START)) {
          g_TitlescreenState.m_CardSelected =
              g_TitlescreenState.m_OptionSelected;
          if (g_TitlescreenState
                  .m_CardNeedsFormat[g_TitlescreenState.m_OptionSelected]) {
            g_TitlescreenState.m_SubState = TS_SubState_MemCardFormat1;
            g_TitlescreenState.m_OptionSelected = 0;
          } else {
            g_TitlescreenState.m_SubState = TS_SubState_ReadSelectedCard;
            g_TitlescreenState.m_State = 0;
            g_TitlescreenState.m_MemCardTries = 0;
            g_TitlescreenState.m_OptionSelected = 1;
            TitlescreenPlaySound(1);
          }
        }
      }
      break;
    }
    }
    break;
  }
  case TSM_Loading: {
    // As long as we're not transitioning to the demo, we'll continue checking
    // our card states
    if (g_TitlescreenState.m_State < 5) {
      CheckMemcardsExist();

      if (g_TitlescreenState.m_CardStates[g_TitlescreenState.m_CardSelected] !=
              McErrNone ||
          g_TitlescreenState
                  .m_CardStates[1 - g_TitlescreenState.m_CardSelected] ==
              McErrNewCard) {
        g_TitlescreenState.m_Mode = TSM_Menu;
        g_TitlescreenState.m_SubState = TS_SubState_LoadMemCards;
        g_TitlescreenState.m_State = 0;
        MemCardSync(McSyncMode_Sync,
                    (long *)&g_TitlescreenState.m_CardCompletedFunc,
                    (long *)&g_TitlescreenState.m_CardResultData);
        break;
      }
    }

    // Keep checking to see if we have any save files (?)
    g_TitlescreenState.m_SaveFiles[0] =
        &g_TitlescreenState.m_MemCardSave->m_Saves[0];
    g_TitlescreenState.m_SaveFiles[1] =
        &g_TitlescreenState.m_MemCardSave->m_Saves[1];
    g_TitlescreenState.m_SaveFiles[2] =
        &g_TitlescreenState.m_MemCardSave->m_Saves[2];
    if (!g_TitlescreenState.m_SaveFiles[0]->m_LevelsVisited[0] &&
        !g_TitlescreenState.m_SaveFiles[1]->m_LevelsVisited[0] &&
        !g_TitlescreenState.m_SaveFiles[2]->m_LevelsVisited[0]) {
      g_TitlescreenState.m_HasAnySave = 0;
    } else {
      g_TitlescreenState.m_HasAnySave = 1;
    }

    if (g_TitlescreenState.m_State == 0) {
      if (g_TitlescreenState.m_NewGameOptionSelected == 0) {
        g_TitlescreenState.m_State = 1;
        if (!g_TitlescreenState.m_SaveFiles[0]->m_LevelsVisited[0]) {
          g_TitlescreenState.m_OptionSelected = 0;
        } else if (!g_TitlescreenState.m_SaveFiles[1]->m_LevelsVisited[0]) {
          g_TitlescreenState.m_OptionSelected = 1;
        } else if (!g_TitlescreenState.m_SaveFiles[2]->m_LevelsVisited[0]) {
          g_TitlescreenState.m_OptionSelected = 2;
        } else {
          g_TitlescreenState.m_OptionSelected = 0;
        }
      } else if (g_TitlescreenState.m_HasAnySave) {
        g_TitlescreenState.m_State = 3;
        if (g_TitlescreenState.m_SaveFiles[0]->m_LevelsVisited[0]) {
          g_TitlescreenState.m_OptionSelected = 0;
        } else if (g_TitlescreenState.m_SaveFiles[1]->m_LevelsVisited[0]) {
          g_TitlescreenState.m_OptionSelected = 1;
        } else {
          g_TitlescreenState.m_OptionSelected = 2;
        }
      } else {
        g_TitlescreenState.m_OptionSelected = 1;
        g_TitlescreenState.m_State = 4;
      }
    } else if (g_TitlescreenState.m_State == 1) {
      if (g_TitlescreenState.m_SubTick >= 8) {
        if (g_Pad.m_Down & (PAD_DOWN | PAD_TRIANGLE)) {
          TitlescreenPlaySound(9);
          g_TitlescreenState.m_State = 4;
          g_TitlescreenState.m_OptionSelected = 0;
        } else if (g_Pad.m_Down & PAD_LEFT) {
          g_TitlescreenState.m_SubTick = 16;
          g_TitlescreenState.m_OptionSelected -= 1;
          if (g_TitlescreenState.m_OptionSelected < 0)
            g_TitlescreenState.m_OptionSelected = 2;
          TitlescreenPlaySound(0);
        } else if (g_Pad.m_Down & PAD_RIGHT) {
          g_TitlescreenState.m_SubTick = 16;
          g_TitlescreenState.m_OptionSelected += 1;
          if (g_TitlescreenState.m_OptionSelected > 2)
            g_TitlescreenState.m_OptionSelected = 0;
          TitlescreenPlaySound(0);
        } else if (g_Pad.m_Down & (PAD_START | PAD_CROSS)) {
          if (g_TitlescreenState
                  .m_SaveFiles[g_TitlescreenState.m_OptionSelected]
                  ->m_LevelsVisited[0]) {
            TitlescreenPlaySound(3);
            g_TitlescreenState.m_State = 2;
            g_TitlescreenState.m_0x18 = 1;
          } else {
            func_8001277C();
            START_DEMO(0)
          }
        }
      }
    } else if (g_TitlescreenState.m_State == 2) {
      if (g_TitlescreenState.m_SubTick >= 8) {
        if ((g_Pad.m_Down & (PAD_RIGHT | PAD_LEFT))) {
          g_TitlescreenState.m_SubTick = 16;
          g_TitlescreenState.m_0x18 = 1 - g_TitlescreenState.m_0x18;
          TitlescreenPlaySound(0);
        } else if (g_Pad.m_Down & (PAD_START | PAD_CROSS | PAD_TRIANGLE)) {
          if (g_TitlescreenState.m_0x18 == 1 ||
              (g_Pad.m_Down & PAD_TRIANGLE) != 0) {
            g_TitlescreenState.m_State = 1;
            TitlescreenPlaySound(4);
          } else {
            func_8001277C();
            START_DEMO(0)
          }
        }
      }
    } else if (g_TitlescreenState.m_State == 3) {
      if (g_TitlescreenState.m_SubTick >= 8) {
        if (g_Pad.m_Down & (PAD_DOWN | PAD_TRIANGLE)) {
          TitlescreenPlaySound(9);
          g_TitlescreenState.m_State = 4;
          g_TitlescreenState.m_OptionSelected = 1;
        } else if (g_Pad.m_Down & PAD_LEFT) {
          int i;
          for (i = g_TitlescreenState.m_OptionSelected - 1; i >= 0; --i) {
            if (g_TitlescreenState.m_SaveFiles[i]->m_LevelsVisited[0]) {
              g_TitlescreenState.m_SubTick = 16;
              break;
            }
          }
          if (i >= 0) {
            g_TitlescreenState.m_OptionSelected = i;
            TitlescreenPlaySound(0);
          }
        } else if (g_Pad.m_Down & PAD_RIGHT) {
          int i;
          for (i = g_TitlescreenState.m_OptionSelected + 1; i < 3; ++i) {
            if (g_TitlescreenState.m_SaveFiles[i]->m_LevelsVisited[0]) {
              g_TitlescreenState.m_SubTick = 16;
              break;
            }
          }
          if (i < 3) {
            g_TitlescreenState.m_OptionSelected = i;
            TitlescreenPlaySound(0);
          }
        } else if (g_Pad.m_Down & (PAD_START | PAD_CROSS)) {
          g_Spyro.m_health = 3;
          g_LifeOrbCount = 0;
          D_8007580C = -1;
          SaveLoad(g_TitlescreenState
                       .m_SaveFiles[g_TitlescreenState.m_OptionSelected]);
          START_DEMO(1)
        }
      }
    } else if (g_TitlescreenState.m_State == 4) {
      if (g_TitlescreenState.m_SubTick >= 8) {
        if (func_80032AB0()) {
          // Triangle was pushed, func_80032AB0 already took care of it
        } else if (g_Pad.m_Down & (PAD_RIGHT | PAD_LEFT)) {
          SWAP_MENU_SELECTION
        } else if (g_Pad.m_Down & (PAD_UP | PAD_START | PAD_CROSS)) {
          if (g_TitlescreenState.m_OptionSelected == 1 &&
              !g_TitlescreenState.m_HasAnySave) {
            g_TitlescreenState.m_SubTick = 16;
            TitlescreenPlaySound(4);
          } else {
            g_TitlescreenState.m_State = 0;
            g_StateSwitch = 1;
            g_TitlescreenState.m_NewGameOptionSelected =
                g_TitlescreenState.m_OptionSelected;
            TitlescreenPlaySound(1);
          }
        }
      }
    } else if (g_TitlescreenState.m_State == 5) {
      if (g_TitlescreenState.m_SubTick == 0) {
        TitlescreenPlaySound(5);
      }

      g_Fade = g_TitlescreenState.m_SubTick + 1;
      if (g_Fade > 15)
        g_Fade = 15;

      if (g_TitlescreenState.m_SubTick >= 16) {
        RECT rc;
        MemCardStop();
        g_TitlescreenState.m_Mode = TSM_Demo;
        g_TitlescreenState.m_State = 0;
        setRECT(&rc, 0, 0, 512, 480);
        ClearImage(&rc, 0, 0, 0);
        DrawSync(0);
      }
    }
    break;
  }
  }

  SpecularUpdate(3);
  if (g_Pad.m_Type >= 2 && (ushort)g_Pad.m_Held != 0) {
    g_TitlescreenState.m_Tick = 0;
  } else {
    g_TitlescreenState.m_Tick++;
  }

  if (g_TitlescreenState.m_Mode < 2) {
    if (g_TitlescreenState.m_SubState != old_state)
      g_TitlescreenState.m_SubTick = 0;
    else
      g_TitlescreenState.m_SubTick = g_TitlescreenState.m_SubTick + 1;
  } else {
    if (g_TitlescreenState.m_State != old_state)
      g_TitlescreenState.m_SubTick = 0;
    else
      g_TitlescreenState.m_SubTick = g_TitlescreenState.m_SubTick + 1;
  }
}

void TitlescreenDrawSprite(int pX, int pY, int pSprite, int pColorId) {
  POLY_FT4 *p;
  int mirrored = 0;

  if (pSprite < 0) {
    mirrored = 1;
    pSprite = -pSprite;
  }

  p = D_800757B0;
  p->tag = 0x09000000;
  ((u_long *)p)[1] = g_TitlescreenSelColors[pColorId];

  setXY4(p, pX, pY, g_TitlescreenSprites[pSprite].m_w + pX, pY, pX,
         g_TitlescreenSprites[pSprite].m_h + pY,
         g_TitlescreenSprites[pSprite].m_w + pX,
         g_TitlescreenSprites[pSprite].m_h + pY);

  setUVWH2(p, g_TitlescreenSprites[pSprite].m_u,
           g_TitlescreenSprites[pSprite].m_v, g_TitlescreenSprites[pSprite].m_w,
           g_TitlescreenSprites[pSprite].m_h);

  p->tpage = g_TitlescreenSprites[pSprite].m_tpage;
  p->clut = g_TitlescreenSprites[pSprite].m_clut;

  // add to OT
  func_800168DC(p);

  D_800757B0 = p + 1;

  if (mirrored) {
    p->u0 = p->u1;
    p->u1 = p->u2;
    p->u2 = p->u0;
    p->u3 = p->u1;
  }
}

void TitlescreenDraw(void) {

  switch (g_TitlescreenState.m_Mode) {
  case TSM_Init: {

    if (g_TitlescreenState.m_SubState == 2) {
      // spyro landed, logo incoming
      if (g_CutsceneLayout->m_CurrentTick >= 1170)
        TitlescreenDrawSprite(
            128, g_TitlescreenAnimIn[g_TitlescreenState.m_SubTick] - 128,
            TS_Sprite_SpyroLogo, TS_Color_Gray);
    } else if (g_TitlescreenState.m_SubState == 3) {
      TitlescreenDrawSprite(128, 0, TS_Sprite_SpyroLogo, 0);
      TitlescreenDrawSprite(192, 210, TS_Sprite_PressStart,
                            ((g_TitlescreenState.m_SubTick & 0xF) < 8) * 2);
    } else if (g_TitlescreenState.m_SubState == 4) {
      if (g_TitlescreenState.m_SubTick < 16) {
        TitlescreenDrawSprite(
            128, g_TitlescreenAnimOut[g_TitlescreenState.m_SubTick] - 128,
            TS_Sprite_SpyroLogo, TS_Color_Gray);
      } else {
        TitlescreenDrawSprite(
            108, g_TitlescreenAnimIn[g_TitlescreenState.m_SubTick - 16] - 119,
            TS_Sprite_MainBorder, TS_Color_Gray);
        TitlescreenDrawSprite(
            255, g_TitlescreenAnimIn[g_TitlescreenState.m_SubTick - 16] - 119,
            -TS_Sprite_MainBorder, TS_Color_Gray);
      }
    }
    break;
  }
  case TSM_Menu: {
    // draw main menu decorative borders (left, then mirror right)
    TitlescreenDrawSprite(108, 9, TS_Sprite_MainBorder, TS_Color_Gray);
    TitlescreenDrawSprite(255, 9, -TS_Sprite_MainBorder, TS_Color_Gray);

    switch (g_TitlescreenState.m_SubState) {
    case TS_SubState_LoadMemCards:
      TitlescreenDrawSprite(128, 46, TS_Sprite_AccessingMemCard,
                            TS_Color_Gray); // accessing mem card
      break;
    case TS_SubState_ReadSelectedCard: // memcard slot selected, checking
      TitlescreenDrawSprite(128, 46, TS_Sprite_AccessingMemCard, TS_Color_Gray);
      if (g_TitlescreenState.m_OptionSelected != 0) {
        TitlescreenDrawSprite(128, 106,
                              g_TitlescreenState.m_CardSelected +
                                  TS_Sprite_UsingCardInSlot1_PressTriToGoBack,
                              TS_Color_Gray);
      }
      break;
    case TS_SubState_NoMemoryCard:
      TitlescreenDrawSprite(128, 46, TS_Sprite_NoMemCard, TS_Color_Gray);
      DRAW_OPTIONS(TS_Sprite_StartNewGameOpt, TS_Sprite_RetryOpt);
      TitlescreenDrawSprite(128, 106,
                            g_TitlescreenState.m_CardSelected +
                                TS_Sprite_UsingCardInSlot1_PressTriToGoBack,
                            TS_Color_Gray);
      break;
    case TS_SubState_MemCardUnavailable:
      TitlescreenDrawSprite(128, 46, TS_Sprite_MemCardUnavailable,
                            TS_Color_Gray);
      DRAW_OPTIONS(TS_Sprite_StartNewGameOpt, TS_Sprite_RetryOpt);
      TitlescreenDrawSprite(128, 106,
                            g_TitlescreenState.m_CardSelected +
                                TS_Sprite_UsingCardInSlot1_PressTriToGoBack,
                            TS_Color_Gray);
      break;
    case TS_SubState_WarningNoSave:
      TitlescreenDrawSprite(128, 22, TS_Sprite_Warning, TS_Color_Gray);
      TitlescreenDrawSprite(128, 38, TS_Sprite_YouWillNotBeAbleTo,
                            TS_Color_Gray);
      TitlescreenDrawSprite(128, 54, TS_Sprite_SaveYourProgressUnless,
                            TS_Color_Gray);
      TitlescreenDrawSprite(128, 70, TS_Sprite_YouCreateASaveFileNow,
                            TS_Color_Gray);
      DRAW_OPTIONS(TS_Sprite_StartNewGameOpt, TS_Sprite_CancelOpt);
      TitlescreenDrawSprite(128, 106,
                            g_TitlescreenState.m_CardSelected +
                                TS_Sprite_UsingCardInSlot1_PressTriToGoBack,
                            TS_Color_Gray);
      break;
    case TS_SubState_MemCardFormat1:
    case TS_SubState_MemCardFormat2:
      if (g_TitlescreenState.m_SubState == TS_SubState_MemCardFormat1) {
        TitlescreenDrawSprite(128, 30,
                              g_TitlescreenState.m_CardSelected +
                                  TS_Sprite_TheMemoryCardInSlot1,
                              TS_Color_Gray);
        TitlescreenDrawSprite(128, 46, TS_Sprite_IsNotFormatted, TS_Color_Gray);
        TitlescreenDrawSprite(128, 62, TS_Sprite_FormatItNow, TS_Color_Gray);
      } else {
        TitlescreenDrawSprite(128, 30, TS_Sprite_Warning, TS_Color_Gray);
        TitlescreenDrawSprite(128, 46, TS_Sprite_AnySaveDataOnThis,
                              TS_Color_Gray);
        TitlescreenDrawSprite(128, 62, TS_Sprite_MemoryCardWillBeLost,
                              TS_Color_Gray);
      }
      DRAW_OPTIONS(TS_Sprite_FormatCardOpt, TS_Sprite_CancelOpt);
      TitlescreenDrawSprite(128, 106,
                            g_TitlescreenState.m_CardSelected +
                                TS_Sprite_UsingCardInSlot1_PressTriToGoBack,
                            TS_Color_Gray);
      break;
    case TS_SubState_MemCardFormatting:
      TitlescreenDrawSprite(128, 46, TS_Sprite_Formatting, TS_Color_Gray);
      break;
    case TS_SubState_FormatComplete:
      TitlescreenDrawSprite(128, 46, TS_Sprite_FormatComplete, TS_Color_Gray);
      if (g_TitlescreenState.m_SubTick > 7) {
        TitlescreenDrawSprite(128, 88, TS_Sprite_ContinueOpt,
                              (g_TitlescreenState.m_SubTick & 0xf) < 8
                                  ? TS_Color_Yellow
                                  : TS_Color_Gray);
      }
      TitlescreenDrawSprite(128, 106,
                            g_TitlescreenState.m_CardSelected +
                                TS_Sprite_UsingCardInSlot1_PressTriToGoBack,
                            TS_Color_Gray);
      break;
    case TS_SubState_FormatFailed:
      TitlescreenDrawSprite(128, 46, TS_Sprite_FormatFailed, TS_Color_Gray);
      DRAW_OPTIONS(TS_Sprite_RetryOpt, TS_Sprite_CancelOpt);
      TitlescreenDrawSprite(128, 106,
                            g_TitlescreenState.m_CardSelected +
                                TS_Sprite_UsingCardInSlot1_PressTriToGoBack,
                            TS_Color_Gray);
      break;
    case TS_SubState_CreateSaveConfirm:
      TitlescreenDrawSprite(128, 30,
                            g_TitlescreenState.m_CardSelected +
                                TS_Sprite_TheMemoryCardInSlot1,
                            TS_Color_Gray);
      TitlescreenDrawSprite(128, 46, TS_Sprite_DoesNotHaveASaveFile,
                            TS_Color_Gray);
      TitlescreenDrawSprite(128, 62, TS_Sprite_CreateSaveFileNow,
                            TS_Color_Gray);

      DRAW_OPTIONS(TS_Sprite_CreateFileOpt, TS_Sprite_CancelOpt);
      TitlescreenDrawSprite(128, 106,
                            g_TitlescreenState.m_CardSelected +
                                TS_Sprite_UsingCardInSlot1_PressTriToGoBack,
                            TS_Color_Gray);
      break;
    case TS_SubState_CreatingSaveFile:
      TitlescreenDrawSprite(128, 46, TS_Sprite_CreatingSaveFile, TS_Color_Gray);
      TitlescreenDrawSprite(128, 106,
                            g_TitlescreenState.m_CardSelected +
                                TS_Sprite_UsingCardInSlot1_PressTriToGoBack,
                            TS_Color_Gray);
      break;
    case TS_SubState_MemCardFull:
      TitlescreenDrawSprite(128, 22,
                            g_TitlescreenState.m_CardSelected +
                                TS_Sprite_TheMemoryCardInSlot1,
                            0);
      TitlescreenDrawSprite(128, 38, TS_Sprite_IsFullThisGame, TS_Color_Gray);
      TitlescreenDrawSprite(128, 54, TS_Sprite_RequiresOneFreeBlock,
                            TS_Color_Gray);
      TitlescreenDrawSprite(128, 70, TS_Sprite_ToCreateASaveFile,
                            TS_Color_Gray);
      if (g_TitlescreenState.m_SubTick > 7) {
        TitlescreenDrawSprite(128, 88, TS_Sprite_ContinueOpt,
                              (g_TitlescreenState.m_SubTick & 0xF) < 8);
      }
      TitlescreenDrawSprite(128, 106,
                            g_TitlescreenState.m_CardSelected +
                                TS_Sprite_UsingCardInSlot1_PressTriToGoBack,
                            TS_Color_Gray);
      break;
    case TS_SubState_CantCreateSave:
      TitlescreenDrawSprite(128, 46, TS_Sprite_UnableToCreateSaveFile,
                            TS_Color_Gray);
      DRAW_OPTIONS(TS_Sprite_RetryOpt, TS_Sprite_CancelOpt);
      TitlescreenDrawSprite(128, 106,
                            g_TitlescreenState.m_CardSelected +
                                TS_Sprite_UsingCardInSlot1_PressTriToGoBack,
                            TS_Color_Gray);
      break;
    // no case 14?
    case TS_SubState_SelectMemCard:
      TitlescreenDrawSprite(128, 46, TS_Sprite_SelectMemoryCard, TS_Color_Gray);
      DRAW_OPTIONS(TS_Sprite_Slot1Opt, TS_Sprite_Slot2Opt);
      break;
    default:
      break;
    }
    break;
  }
  case TSM_Loading: {
    int i;
    int j;
    int dragon_count;
    if (g_TitlescreenState.m_State < 5) {
      TitlescreenDrawSprite(108, 9, TS_Sprite_MainBorder, TS_Color_Gray);
      TitlescreenDrawSprite(255, 9, -TS_Sprite_MainBorder, TS_Color_Gray);
      if (g_TitlescreenState.m_State > 0) {
        for (i = 0; i < 3; ++i) {
          if (!g_TitlescreenState.m_SaveFiles[i]->m_LevelsVisited[0]) {
            int color = 0;
            if ((g_TitlescreenState.m_State < 3 &&
                 g_TitlescreenState.m_OptionSelected != i) ||
                g_TitlescreenState.m_State - 3u < 2) {
              color = 3;
            }
            TitlescreenDrawSprite(140 + 80 * i, 38, TS_Sprite_EmptySave, color);
          } else {
            int color = 0;
            if ((g_TitlescreenState.m_State < 4 &&
                 g_TitlescreenState.m_OptionSelected != i) ||
                g_TitlescreenState.m_State == 4) {
              color = 3;
            }
            TitlescreenDrawSprite(140 + 80 * i, 38,
                                  g_TitlescreenState.m_SaveFiles[i]->m_LevelId /
                                          10 -
                                      1 + TS_Sprite_Homeworld_Artisans,
                                  color);
            TitlescreenDrawSprite(184 + 80 * i, 22, TS_Sprite_DragonCt_Logo,
                                  color);

            for (j = 0, dragon_count = 0; j < TOTAL_LEVEL_COUNT; ++j) {
              dragon_count +=
                  g_TitlescreenState.m_SaveFiles[i]->m_CollectedDragons[j];
            }

            // dragon count ones digit
            TitlescreenDrawSprite(168 + 80 * i, 22,
                                  dragon_count % 10 + TS_Sprite_DragonCt_Num0,
                                  color);
            if (dragon_count > 9) {
              // dragon count tens digit
              TitlescreenDrawSprite(152 + 80 * i, 22,
                                    dragon_count / 10 + TS_Sprite_DragonCt_Num0,
                                    color);
            }
          }
        }
      }
    } else {
      TitlescreenDrawSprite(
          108, g_TitlescreenAnimOut[g_TitlescreenState.m_SubTick] - 119,
          TS_Sprite_MainBorder, TS_Color_Gray);
      TitlescreenDrawSprite(
          255, g_TitlescreenAnimOut[g_TitlescreenState.m_SubTick] - 119,
          -TS_Sprite_MainBorder, TS_Color_Gray);
    }

    if (g_TitlescreenState.m_State == 1) {
      if ((g_TitlescreenState.m_SubTick & 0xF) < 8) {
        TitlescreenDrawSprite(g_TitlescreenState.m_OptionSelected * 80 + 140,
                              38, TS_Sprite_BlankSaveBox, TS_Color_Gray);
      }
      TitlescreenDrawSprite(128, 88, TS_Sprite_NewGameOpt, TS_Color_Yellow);
      TitlescreenDrawSprite(256, 88, TS_Sprite_LoadGameOpt, TS_Color_Gray);
      TitlescreenDrawSprite(128, 106, TS_Sprite_SelectSlotForNewGame,
                            TS_Color_Gray);
    } else if (g_TitlescreenState.m_State == 2) {
      TitlescreenDrawSprite(g_TitlescreenState.m_OptionSelected * 80 + 140, 38,
                            TS_Sprite_OverwriteGame, TS_Color_Gray);
      TitlescreenDrawSprite(g_TitlescreenState.m_OptionSelected * 80 + 140, 38,
                            TS_Sprite_BlankSaveBox, TS_Color_Gray);
      TitlescreenDrawSprite(128, 88, TS_Sprite_Overwrite,
                            (g_TitlescreenState.m_0x18 == 0 &&
                             ((g_TitlescreenState.m_SubTick & 0xF) < 8))
                                ? TS_Color_Yellow
                                : TS_Color_Gray);
      TitlescreenDrawSprite(256, 88, TS_Sprite_CancelOpt,
                            (g_TitlescreenState.m_0x18 == 1 &&
                             ((g_TitlescreenState.m_SubTick & 0xF) < 8))
                                ? TS_Color_Yellow
                                : TS_Color_Gray);
    } else if (g_TitlescreenState.m_State == 3) {
      if ((g_TitlescreenState.m_SubTick & 0xF) < 8) {
        TitlescreenDrawSprite(g_TitlescreenState.m_OptionSelected * 80 + 140,
                              38, TS_Sprite_BlankSaveBox, TS_Color_Gray);
      }
      TitlescreenDrawSprite(128, 88, TS_Sprite_NewGameOpt, TS_Color_Gray);
      TitlescreenDrawSprite(256, 88, TS_Sprite_LoadGameOpt, TS_Color_Yellow);
      TitlescreenDrawSprite(128, 106, TS_Sprite_SelectSlotToLoadGame,
                            TS_Color_Gray);
    } else if (g_TitlescreenState.m_State == 4) {
      TitlescreenDrawSprite(128, 88, TS_Sprite_NewGameOpt,
                            (g_TitlescreenState.m_OptionSelected == 0 &&
                             ((g_TitlescreenState.m_SubTick & 0xF) < 8))
                                ? TS_Color_Yellow
                                : TS_Color_Gray);
      TitlescreenDrawSprite(256, 88, TS_Sprite_LoadGameOpt,
                            (g_TitlescreenState.m_OptionSelected == 1 &&
                             ((g_TitlescreenState.m_SubTick & 0xF) < 8))
                                ? TS_Color_Yellow
                                : TS_Color_Gray);
      TitlescreenDrawSprite(128, 106,
                            g_TitlescreenState.m_CardSelected +
                                TS_Sprite_UsingCardInSlot1_PressTriToGoBack,
                            TS_Color_Gray);
    }

    break;
  }
  }

  setRGB0(&g_DB[0].m_DrawEnv, g_Cyclorama.m_BackgroundColor.r,
          g_Cyclorama.m_BackgroundColor.g, g_Cyclorama.m_BackgroundColor.b);
  setRGB0(&g_DB[1].m_DrawEnv, g_Cyclorama.m_BackgroundColor.r,
          g_Cyclorama.m_BackgroundColor.g, g_Cyclorama.m_BackgroundColor.b);

  // Draw the Mobys
  func_800521C0();
  func_8001F158();
  Memset(g_SonyImage.u.m_Draw.m_Moby, 0, sizeof(g_SonyImage.u.m_Draw.m_Moby));
  func_8001F798();

  // Draw the Environment
  Memset(g_SonyImage.u.m_Buf, 0, sizeof(g_SonyImage.u.m_Buf));
  g_Environment.m_CullingDistance = 0x1c000;
  func_800258F0(-1);

  // Draw the Cyclorama
  func_8004EBA8(-1, &g_Camera.m_ViewMatrix, &g_Camera.m_ProjectionMatrix);

  // Overlay the fade
  if (g_Fade) {
    func_800190D4(2, g_Fade << 4, g_Fade << 4, g_Fade << 4);
  }

  DrawSync(0);

  VSync(0);

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

// Only exists to find the end of the overlay
void func_titlescreen_8007DDE8(void) {}
