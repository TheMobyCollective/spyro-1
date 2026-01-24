#include "buffers.h"
#include "camera.h"
#include "common.h"
#include "cutscene.h"
#include "gamepad.h"
#include "gamestates/draw.h"
#include "gamestates/init.h"
#include "graphics.h"
#include "loaders.h"
#include "math.h"
#include "overlay_pointers.h"
#include "specular_and_metal.h"
#include "spyro.h"
#include "sony_image.h"
#include "titlescreen.h"
#include "variables.h"

#include <libmcrd.h>

extern int _stacksize;


/// @brief Updates level transition gems and text
void func_8002DA74(void) {
  int i;

  g_LevelTransGems = (TransGem *)g_SonyImage.unk_0x2800;
  if (g_LevelTransTicks == 0) {
    g_LevelTransChestDuration = g_NGemsSinceLevelEntry * 2 + 140;
    if (g_LevelTransChestDuration > 192) {
      g_LevelTransChestDuration = 192;
    }
    for (i = 0; i < 64; i++) {
      g_LevelTransGems[i]._08 = 0;
    }
  }

  g_LevelTransTicks += g_DeltaTime;

  if (g_LevelTransTicks > 416) {
    g_LevelTransHudActive = 0;
  } else if (g_LevelTransTicks >= 128) {
    for (i = 0; i < 32; i++) {

      if (i < g_NGemsSinceLevelEntry && (i * 2 + 128) <= g_LevelTransTicks) {
        if (g_LevelTransTicks < 256) {
          if (g_LevelTransGems[i]._08 == 0) {
            g_LevelTransGems[i]._08 = 1;
            g_LevelTransGems[i].age = g_LevelTransTicks - 128 - i * 2 - g_DeltaTime;
            g_LevelTransGems[i].targetX = (rand() & 255) - 128;
            g_LevelTransGems[i].targetY = (rand() & 63) + 96;
            g_LevelTransGems[i].rot.x = (rand() & 63) - 32;
            g_LevelTransGems[i].rot.y = (rand() & 63) - 32;
            g_LevelTransGems[i].rot.z = rand();
            g_LevelTransGems[i]._0D = (rand() & 2) - 1;
            g_LevelTransGems[i]._0E = (rand() & 2) - 1;
            g_LevelTransGems[i]._0F = (rand() & 15) - 8;
            if ((g_LevelTransTicks & 7) == 0) {
              PlaySound(g_Spu.m_SoundTable->gemPickup, 0, 16, 0);
            }
          }
        }
        if (g_LevelTransGems[i]._08 != 0) {
          g_LevelTransGems[i].age += g_DeltaTime;
          g_LevelTransGems[i].rot.z += g_LevelTransGems[i]._0F;
          if (g_LevelTransGems[i].age < 48) {
            g_LevelTransGems[i].xOffset = FIXED_MUL(g_LevelTransGems[i].targetX,
                                                    4096 - COSINE_8(g_LevelTransGems[i].age * 4 / 3));
            g_LevelTransGems[i].yOffset = FIXED_MUL(g_LevelTransGems[i].targetY,
                                                    SINE_8(g_LevelTransGems[i].age * 4 / 3));
          } else if (g_LevelTransGems[i].age < 96) {
            g_LevelTransGems[i].xOffset = g_LevelTransGems[i].targetX +
                                          (FIXED_MUL(g_LevelTransGems[i].targetX,
                                          SINE_8((g_LevelTransGems[i].age - 48) * 8 / 3)) >> 1);
            g_LevelTransGems[i].yOffset = (g_LevelTransGems[i].targetY >> 1) +
                                          (FIXED_MUL(g_LevelTransGems[i].targetY,
                                          4096 + COSINE_8((g_LevelTransGems[i].age - 48) * 8 / 3)) >> 2);
          } else if (g_LevelTransGems[i].age < 147) {
            g_LevelTransGems[i].xOffset = g_LevelTransGems[i].targetX -
                                          FIXED_MUL(g_LevelTransGems[i].targetX,
                                          SINE_8((g_LevelTransGems[i].age - 96) * 4 / 3));
            g_LevelTransGems[i].yOffset = FIXED_MUL(g_LevelTransGems[i].targetY,
                                          COSINE_8((g_LevelTransGems[i].age - 96) * 4 / 3)) >> 1;
          } else {
            g_LevelTransGems[i]._08 = 0;
            if (i == (i / 3) * 3) {
              PlaySound(g_Spu.m_SoundTable->pickupDing, 0, 16, 0);
            }
          }
        }
      }
    }
  }
}



/// @brief Gamestate 1
void func_8002DF9C(void) {
  UpdateSpyroEnterReturnHome(); // Spyro update
  CameraUpdate();               // Camera update

  func_8002DA74();

  if (g_LoadStage < 11 || !g_LevelTransHudActive) {
    LoadLevel(1);
  }
}

/// @brief Gamestate 9
void func_8002E000(void) {
  func_8004A200(); // Spyro update
  CameraUpdate();  // Camera update

  g_Camera.m_Rotation.y &= 0xFFF;

  if (g_Camera.m_Rotation.y > 0x800)
    g_Camera.m_Rotation.y -= 0x1000;

  if (g_Camera.m_Rotation.y < -0x200 ||
      g_Camera.m_SphericalPreset == &D_8006CA84) {
    g_Gamestate = GS_Playing;
  }
}

extern int D_8007568C; // Pause menu no button ticks
extern int D_800758B8; // Pause menu text rotation ticks

/// @brief Gamestate 10
void func_8002E084(void) {
  UpdateSpyroReturnHome();
  CameraUpdate(); // Camera update

  D_8007568C++;

  if (D_8007568C >= 32) {
    D_8007568C = 0;
    D_800758B8++;
    if (D_800758B8 == 2) {
      func_8002C664();
    }

  } else {
    if (D_8007568C == 16 && D_800758B8 == 0) {
      func_8003EA68(15); // Set state to gliding
    }
  }
}

/// @brief Gamestate 2
void func_8002E12C(void);
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestates/update", func_8002E12C);

/// @brief Gamestate 3
void func_8002EB2C(void);
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestates/update", func_8002EB2C);

/// @brief Gamestate 4 & 5
void func_8002EDF0(void);
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestates/update", func_8002EDF0);

/// @brief Gamestate 6 (Empty, used to be the dragon dialogue)
void func_8002F3C4(void) { func_8002C91C(); }

/// @brief Gamestate 8 Dragon cutscene
void func_8002F3E4(void);
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestates/update", func_8002F3E4);

/// @brief Gamestate 11 (Fairy)
void func_800314B4(void);
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestates/update", func_800314B4);

/// @brief Gamestate 12 (Balloonist)
void func_800324D8(void);
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestates/update", func_800324D8);

// Memory card used only by titlescreen?!?!?!?!?!?!?!?!?!?!?!
void func_80032A20(void) {
  int t = MemCardSync(1, (void *)&g_TitlescreenState.m_CardCompletedFunc,
                      (void *)&g_TitlescreenState.m_CardResultData);

  if (t) {
    if (t == 1) {
      g_TitlescreenState.m_CardStates[g_TitlescreenState.m_CardIdxChecking] =
          g_TitlescreenState.m_CardResultData;
      g_TitlescreenState.m_CardIdxChecking =
          1 - g_TitlescreenState.m_CardIdxChecking;
    }

    MemCardExist(g_TitlescreenState.m_CardIdxChecking << 4);
  }
}

// Memory card used only by titlescreen?!?!?!?!?!?!?!?!?!?!?!
void func_80032AB0(void) {
  if (g_Pad.m_Down & PAD_TRIANGLE) {
    g_TitlescreenState.m_Mode = TSM_Menu;
    g_TitlescreenState.m_0x10 = 0;
    g_TitlescreenState.m_State = TSS_Setup;
    MemCardSync(0, (void *)&g_TitlescreenState.m_CardCompletedFunc,
                (void *)&g_TitlescreenState.m_CardResultData);
  }
}

/**
 * @brief Gamestate 13 - Titlescreen demo mode update
 *
 * Manages the animated demo sequence that plays when the game is idle on the
 * title screen. Spyro flies through a scripted path using trigonometric
 * interpolation while the level/cutscene loads in the background.
 *
 * State machine (via m_State):
 * - TSS_Setup: Stops audio, initializes loading parameters, sets up camera
 *   and Spyro position
 * - TSS_Loading: Loads cutscene or level data in a blocking loop while keeping
 *   CD music alive
 * - TSS_Active: Animates Spyro through 6 phases (arc, hold, linear, reset,
 *   reverse arc, final), then transitions to cutscene playback or demo mode
 *
 * Demo types (via m_DemoType):
 * - TSD_Cutscene: Plays intro cutscene
 * - TSD_Level: Reuses current level for demo
 * - TSD_DemoLevel: Loads level from g_DemoLevelIds table
 */
void GamestateCutsceneTransition(void) {
  Vector3D tempPos;
  RECT rect;
  int tick;
  int angle;
  int levelId;

  if (g_TitlescreenState.m_Mode != TSM_Demo) {
    // Not in demo mode - skip to common exit
  } else if (g_TitlescreenState.m_State == TSS_Setup) {
    // Initial setup - stop audio and prepare loading
    func_80056B28(0); // Halts CD music and all SPU voices
    SpuUpdate();
    g_TitlescreenState.m_State = TSS_Loading;

    if (g_TitlescreenState.m_DemoType == TSD_Cutscene) {
      // Cutscene mode
      g_CutsceneIdx = 1;
      g_LoadStage = 0;
      g_Buffers.m_CopyBuf = g_OverlaySpacePointer;
      g_Buffers.m_DiscCopyBuf = g_OverlaySpacePointer;
    } else if (g_TitlescreenState.m_DemoType == TSD_Level) {
      // Level mode - reuse current level
      levelId = g_LevelId;
      g_IsFlightLevel = 0;
      g_LoadStage = 1;
      g_PortalLevelId = 0;
      g_HasLevelTransition = 0;
      g_NextLevelId = levelId;
    } else if (g_TitlescreenState.m_DemoType == TSD_DemoLevel) {
      // Demo level mode - reset game state and get level from table
      func_8001277C(); // Sets Artisans homeworld, resets progress

      levelId = g_DemoLevelIds[g_DemoIndex];
      g_IsFlightLevel = 0;
      g_LoadStage = 1;
      g_PortalLevelId = 0;
      g_HasLevelTransition = 0;
      g_LevelId = levelId;
      g_NextLevelId = levelId;
    }

    // Initialize camera
    g_Camera.m_Rotation.z = 0x400;
    g_Camera.m_Rotation.x = 0;
    g_Camera.m_Rotation.y = 0;
    g_Camera.m_Position.x = 0x2000;
    g_Camera.m_Position.y = 0;
    g_Camera.m_Position.z = 0x2000;

    // Reset Spyro physics (full reset) and set initial flyby position
    func_8004AC24(1); // Clears state machine and velocities
    g_Spyro.m_Position.x = 0x2780;
    g_Spyro.m_Position.y = 0xF00;
    g_Spyro.m_Position.z = 0x29A0;
    g_Spyro.m_bodyAnimation = 16;
    g_Spyro.m_nextBodyAnimation = 16;
    g_Spyro.m_bodyRotation.x = 0;
    g_Spyro.m_bodyRotation.y = 0;
    g_Spyro.m_bodyRotation.z = 0;
    g_Spyro.m_nextBodyAnimationFrame = 1;

  } else if (g_TitlescreenState.m_State == TSS_Loading) {
    // Loading phase
    if (g_TitlescreenState.m_DemoType == TSD_Cutscene) {
      // Load cutscene until stage 3
      while (g_LoadStage < 3) {
        LoadCutscene();
        CDMusicUpdate();
      }
    } else {
      // Load level until stage 6
      while (g_LoadStage < 6) {
        LoadLevel(1);
        CDMusicUpdate();
      }
    }

    g_TitlescreenState.m_State = TSS_Active;
    g_TitlescreenState.m_Tick = 0;
  } else if (g_TitlescreenState.m_State == TSS_Active) {
    // Animation phase
    VecCopy(&tempPos, &g_Spyro.m_Position);
    tick = g_TitlescreenState.m_Tick;

    if (tick < 80) {
      // Arc movement with Sin/Cos
      g_Spyro.m_Position.x =
          Cos(((-g_TitlescreenState.m_Tick) << 10) / 80) + 0x1780;
      g_Spyro.m_Position.y =
          (Sin(((-g_TitlescreenState.m_Tick) << 10) / 80) >> 1) + 0xE80;
      g_Spyro.m_Position.z =
          (Sin(((-g_TitlescreenState.m_Tick) << 10) / 80) >> 1) + 0x2980;
    } else if (tick < 120) {
      // Fixed position
      g_Spyro.m_Position.x = 0x1400;
      g_Spyro.m_Position.y = 0xC00;
      g_Spyro.m_Position.z = 0x20C0;
    } else if (tick < 200) {
      // Move right only
      g_Spyro.m_Position.x += 0x4C;
    } else if (tick < 240) {
      // New fixed position
      g_Spyro.m_Position.x = 0x2880;
      g_Spyro.m_Position.y = 0x680;
      g_Spyro.m_Position.z = 0x2180;
    } else if (tick < 320) {
      // Arc with offset
      g_Spyro.m_Position.x =
          Cos(0xC00 - ((g_TitlescreenState.m_Tick - 240) << 10) / 80) + 0x2880;
      g_Spyro.m_Position.y =
          (Sin(0xC00 - ((g_TitlescreenState.m_Tick - 240) << 10) / 80) >> 1) +
          0xE80;
      g_Spyro.m_Position.z =
          (Sin(((g_TitlescreenState.m_Tick - 240) << 10) / 80 + 0xC00) >> 1) +
          0x2980;
    } else {
      // Final position
      g_Spyro.m_Position.x = 0x2000;
      g_Spyro.m_Position.y = 0x1000;
      g_Spyro.m_Position.z = 0x4000;
    }

    // Calculate look-at angles from movement delta
    VecSub(&tempPos, &g_Spyro.m_Position, &tempPos);
    g_Spyro.m_bodyRotation.y = Atan2(VecMagnitude(&tempPos, 0), tempPos.z, 0);
    g_Spyro.m_bodyRotation.z = Atan2(tempPos.x, tempPos.y, 0);

    // Advance Spyro's animations at 3x speed for dramatic flyby effect
    func_8003CB24(3); // Advances body animation by 3 ticks
    func_80049660();  // Head animation state machine
    func_80049E8C();  // Tail follows body animation

    if (g_TitlescreenState.m_DemoType == TSD_Cutscene) {
      // Cutscene path
      if (g_LoadStage < 7) {
        LoadCutscene();
      }
      if (g_TitlescreenState.m_Tick >= 384 && g_LoadStage == 7) {
        // Flyby complete and cutscene data ready - finalize and start playback
        rect.w = 512;
        rect.x = 0;
        rect.y = 0;
        rect.h = 480;
        ClearImage(&rect, 0, 0, 0);
        DrawSync(0);
        g_Buffers.m_SharedAnimations = (void *)(0x80200000 - _stacksize);
        AllocateBuffers(1);
        while (g_LoadStage < 10) {
          LoadCutscene();
          CDMusicUpdate();
        }
        StartCutscenePlayback(); // Sets GS_Cutscene, starts cutscene audio
        g_StateSwitch = 1;
        return;
      }
    } else {
      // Level path
      if (g_LoadStage < 13) {
        LoadLevel(1);
      }
      if (g_TitlescreenState.m_Tick >= 384 && g_LoadStage == 13) {
        // Flyby complete and level fully loaded - start demo playback
        if (g_TitlescreenState.m_DemoType == TSD_DemoLevel) {
          g_DemoMode = 1;
          g_DemoFadeTimer = 0;
        }
        func_8004AC24(1); // Reset Spyro for actual gameplay
        LoadLevel(1);
        return;
      }
    }
  }

  SpecularUpdate(3);
  g_TitlescreenState.m_Tick++;
}

/// @brief Gamestate 14 - Cutscene update
void GamestateCutsceneUpdate(void) {
  RECT rc;
  int duration;
  int currentTick;

  if (g_CutsceneIdx >= 2) {
    if (g_CutsceneLayout->m_CurrentTick == 0) {
      // Initial cutscene setup
      func_80056B28(0); // Stop all sounds
      SpuUpdate();

      // Clear screen
      setRECT(&rc, 0, 0, 512, 480);
      ClearImage(&rc, 0, 0, 0);
      DrawSync(0);

      g_LoadStage = 0;
      g_Buffers.m_CopyBuf = g_OverlaySpacePointer;
      g_Buffers.m_DiscCopyBuf = g_OverlaySpacePointer;

      if (g_CutsceneIdx == 3) {
        g_Buffers.m_SharedAnimations = (void *)(0x80200000 - _stacksize);
        AllocateBuffers(1); // Allocate buffers with reduced space for credits 2
      }

      // Load cutscene data loop
      while (g_LoadStage < 10) {
        LoadCutscene();
        CDMusicUpdate();
      }

      StartCutscenePlayback(); // Initialize cutscene playback state
    }
  }

  // Main update
  currentTick = g_CutsceneLayout->m_CurrentTick;
  duration = g_CutsceneLayout->m_Duration;
  currentTick += g_DeltaTime;
  duration <<= 1;
  g_CutsceneLayout->m_CurrentTick = currentTick;

  if (currentTick < duration) {
    // Fade logic
    if (currentTick < 16) {
      g_Fade = 16 - currentTick;
    } else {
      currentTick = duration - currentTick;
      if (currentTick < 16) {
        g_Fade = 16 - currentTick;
      } else {
        g_Fade = 0;
      }
    }

    if (g_Fade >= 16) {
      g_Fade = 15;
    }

    // Skip functionality for intro cutscene
    if (g_CutsceneIdx == 1) {
      if (g_Pad.m_Held & (PAD_START | PAD_CROSS)) {
        CutsceneLayout *pCutscene;
        int tick;
        pCutscene = g_CutsceneLayout;
        tick = pCutscene->m_CurrentTick;
        if (tick >= 241) {
          if (tick < (pCutscene->m_Duration << 1) - 32) {
            pCutscene->m_Duration = (tick >> 1) + 16;
          }
        }
      }
    }

    func_8002BFE0(
        g_CutsceneLayout->m_CurrentTick); // Update/render cutscene frame
  } else {
    EndCutscenePlayback();
  }
}

/// @brief Gamestate 15
void func_800333DC(void) {
  SpecularUpdate(3);

  switch (g_CreditsStage) {
  case 99:
    g_LoadStage = 1;

    // If we started the credits with the cheat,
    // return us to where we started it
    if (D_80075818 != -1) {
      g_NextLevelId = D_80075818;
      D_80075818 = -1;
    } else {
      // Otherwise, check if we completed loot, if we did, return us to Artisans
      if (g_GemTotal == 14000) {
        g_NextLevelId = 10; // Artisans
      } else {
        g_NextLevelId = 60; // Gnorc Gnexus
      }
    }

    g_PortalLevelId = 0;      // Reset portal level id
    g_HasLevelTransition = 0; // Set no level transition
    g_CreditsTimer = 0;

    g_CreditsStage++; // Start loading level
    return;
  case 100:
    // Load level
    g_CreditsTimer += g_DeltaTime;
    LoadLevel(1);
    return;
  }
}

/// @brief Update demo mode
int func_800334D4(void);
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestates/update", func_800334D4);

/**
 * @brief Main game loop update dispatcher, handles all gamestate logic.
 *
 * Called every frame from main(). Updates audio systems, then dispatches to
 * the appropriate gamestate handler. For GS_Playing: updates mobys, Spyro,
 * particles, HUD, camera, fade, and handles pause/inventory input.
 */
void GamestateUpdate(void) {
  g_StateSwitch = 0;

  // Update active SPU voices (3D audio, volume fades, pitch ramping)
  func_8005637C();
  CDMusicUpdate();

  // Dispatch to appropriate gamestate handler
  if (g_Gamestate != GS_Playing) {
    if (g_Gamestate == GS_LevelTransition) {
      func_8002DF9C(); // Level transition update
    } else if (g_Gamestate == GS_PauseMenu) {
      func_8002E12C(); // Pause menu update
    } else if (g_Gamestate == GS_InventoryMenu) {
      func_8002EB2C(); // Inventory/atlas menu update
    } else if (g_Gamestate == GS_Respawn) {
      func_8002EDF0(); // Respawn spiral animation
    } else if (g_Gamestate == GS_GameOver) {
      func_8002EDF0(); // Game over spiral animation
    } else if (g_Gamestate == GS_OldDragon) {
      func_8002F3C4(); // Unused prototype dragon dialogue stub
    } else if (g_Gamestate == GS_FlightResults) {
      g_FlightResultsUpdate(); // Flight level results (overlay)
    } else if (g_Gamestate == GS_Dragon) {
      func_8002F3E4(); // Dragon rescue cutscene update
    } else if (g_Gamestate == GS_EntranceAnimation) {
      func_8002E000(); // Level entrance camera sweep
    } else if (g_Gamestate == GS_ExitLevel) {
      func_8002E084(); // Return home portal sequence
    } else if (g_Gamestate == GS_Fairy) {
      func_800314B4(); // Fairy save system update
    } else if (g_Gamestate == GS_Balloonist) {
      func_800324D8(); // Balloonist ride update
    } else if (g_Gamestate == GS_TitleScreen) {
      if (g_TitlescreenState.m_Mode != TSM_Demo) {
        func_titlescreen_8007ABAC(); // Titlescreen menu (overlay)
      } else {
        GamestateCutsceneTransition();
      }
    } else if (g_Gamestate == GS_Cutscene) {
      GamestateCutsceneUpdate();
    } else if (g_Gamestate == GS_Credits) {
      if (g_CreditsStage > 98) {
        func_800333DC(); // Credits cleanup/level load
      } else {
        func_credits_8007AA50(); // Credits update (overlay)
      }
    }

    SpuUpdate();

    return;
  }

  // GS_Playing: Normal gameplay update
  g_GameTick++;

  // Handle demo mode input playback; exit early if demo ends
  if (g_DemoMode) {
    if (func_800334D4()) {
      return;
    }
  }

  // Update environment animations
  func_8002A6FC(g_DeltaTime);

  // Level-specific Moby (enemy/object) update
  g_UpdateMoby();

  // Skip Spyro update for cutscene gamestates that handle their own Spyro
  if (g_Gamestate == GS_Fairy || g_Gamestate == GS_Balloonist ||
      g_Gamestate == GS_FlightResults || g_Gamestate == GS_LevelTransition) {
    return;
  }

  func_8004A200(); // Main Spyro update (physics, state machine, animation)

  // Skip remaining updates during respawn/death states
  if (g_Gamestate == GS_Respawn || g_Gamestate == GS_GameOver ||
      g_Gamestate == GS_FlightResults || g_Gamestate == GS_LevelTransition) {
    return;
  }

  // Level-specific particle update
  g_UpdateParticle(g_DeltaTime);

  // Skip HUD in flight levels (they have their own UI)
  if (!g_IsFlightLevel) {
    HudTick();
  }

  MetalBuildMatrix(); // Build metal texture matrix from camera rotation
  CameraUpdate();     // Main camera update

  // Screen fade timer (for smooth transitions)
  if (g_Fade != 0) {
    g_Fade -= g_DeltaTime;

    if (g_Fade < 0) {
      g_Fade = 0;
    }
  }

  // Pause/inventory input check (only when alive and in normal play)
  if (g_Gamestate == GS_Playing && g_ScreenBorderEnabled == 0 &&
      g_Spyro.m_health >= 0 && g_Camera.m_State != 0x8000000E) {
    if ((u_int)g_Pad.m_Type == CONTROLLER_TYPE_DISCONNECTED ||
        (u_int)g_Pad.m_Type == CONTROLLER_TYPE_INVALID) {
      func_8002C420(1); // No controller - force pause
    } else if (g_Pad.m_Down & PAD_START) {
      func_8002C420(1); // START - open pause menu
    } else if (g_Pad.m_Down & PAD_SELECT) {
      func_8002C714(1); // SELECT - open inventory
    }
  }

  SpuUpdate();
}

