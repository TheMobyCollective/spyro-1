#include "gamestates/init.h"
#include "4BEF8.h"
#include "buffers.h"
#include "camera.h"
#include "cd.h"
#include "cheats.h"
#include "common.h"
#include "cutscene.h"
#include "cyclorama.h"
#include "dragon.h"
#include "fairy.h"
#include "gamestates/draw.h"
#include "graphics.h"
#include "hud.h"
#include "initialization.h"
#include "loaders.h"
#include "memory.h"
#include "music.h"
#include "rand.h"
#include "specular_and_metal.h"
#include "spu.h"
#include "spyro.h"
#include "titlescreen.h"
#include "variables.h"

extern int D_8007568C; // Pause menu no button ticks
extern int D_800758B8; // Pause menu text rotation ticks

extern int D_80075720; // Selected menu item index
extern int D_800757C8; // OptionsSubmenuIsOpen

// Inventory page transition state
// Set to 0 when not transitioning
// Set to -64 when transitioning to right. (When right button is pressed,
// Artisans to Peace Keepers) Set to 64 when transitioning to left. (When left
// button is pressed, Peace Keepers to Artisans)
extern int D_800756D4;
extern int D_80075744; // The index of the current page of the inventory screen
extern int D_800757CC; // Transition progress between inventory pages.

extern SphericalCoordsOffset D_8006C8BC;

/// @brief Pauses the game
// pEnteringFromGameplay is:
//   1 when entering the pause menu from the game.
//   0 when returning from the inventory screen to the pause menu
void func_8002C420(int pEnteringFromGameplay) {
  if (pEnteringFromGameplay) {
    // Stop all sounds
    func_80056B28(0);
  }

  PlaySound(g_Spu.m_SoundTable->menuSound, nullptr, 0x10 /* 2D */, nullptr);

  g_Gamestate = GS_PauseMenu; // Set gamestate to pause menu
  D_80075720 = 0;             // Selected menu item index
  D_800757C8 = 0;             // OptionsMenuIsOpen
  D_8007568C = 0;             // Pause menu no button ticks

  if (g_IsFlightLevel) { // If Spyro is in a flight level...
    if (pEnteringFromGameplay) {
      D_800758B8 = 0; // Pause menu text rotation ticks
    }
  } else {

    // Resets the HUD struct
    HudReset(0);

    if (pEnteringFromGameplay) {
      D_800758B8 = 0; // Pause menu text rotation ticks
    } else {
      g_Hud.m_GemDisplayState = HDS_Opening;
      g_Hud.m_DragonDisplayState = HDS_Opening;
      g_Hud.m_LifeDisplayState = HDS_Opening;
      g_Hud.m_EggDisplayState = HDS_Opening;
      g_Hud.m_KeyDisplayState = HDS_Opening;

      // These are progress variables used to move the HUD elements down
      // setting it to 12 causes them to snap down instantly
      g_Hud.m_GemProgress = 12;
      g_Hud.m_DragonProgress = 12;
      g_Hud.m_LifeProgress = 12;
      g_Hud.m_EggProgress = 12;
      g_Hud.m_KeyProgress = 12;
    }

    // Something HUD-related
    HudTick();
  }
}

/// @brief Unpauses the game, and sets the gamestate to 0
// The arg `pResumeMusic` is always set to 1 in every call of this function.
void func_8002C534(int pResumeMusic) {
  RECT rect;

  // Restores the VRAM that it overwrote for the background
  setRECT(&rect, 512, 0, 256, 225);
  LoadImage(&rect, (u_long *)((int)g_Buffers.m_HudOTStart - 115200));
  DrawSync(0);

  g_Gamestate = GS_Playing;

  SpecularReset();

  g_Hud.m_GemDisplayState = HDS_Closing;
  g_Hud.m_DragonDisplayState = HDS_Closing;
  g_Hud.m_LifeDisplayState = HDS_Closing;
  g_Hud.m_EggDisplayState = HDS_Closing;
  g_Hud.m_KeyDisplayState = HDS_Closing;
  g_Hud.m_GemProgress = 13;
  g_Hud.m_DragonProgress = 13;
  g_Hud.m_LifeProgress = 13;
  g_Hud.m_EggProgress = 13;
  g_Hud.m_KeyProgress = 13;

  if (pResumeMusic) {
    // Resume the level music
    func_800567F4(g_CdMusic.m_CurrentTrack, 8);
  }
}

/// @brief Exits level
void func_8002C618(void) {
  func_80056B28(0);           // Stop all sounds
  g_Gamestate = GS_ExitLevel; // Set gamestate to exit level
  D_8007568C = 0;             // Pause menu no button ticks
  D_800758B8 = 0;             // Pause menu text rotation ticks

  func_8004AC24(0); // Reset spyro
  func_8003EA68(0); // Set state to idle
}

/// @brief Return home, sets gamestate to 1
void func_8002C664(void) {
  SpecularReset();

  // Set the level you're traveling to
  // to the homeworld of the current level
  g_NextLevelId = (g_LevelId / 10) * 10;

  g_LoadStage = 0;
  D_800756AC = 0;
  g_Camera.unk_0xC0 = 0x80000012;
  D_8007576C = -1;
  g_PortalLevelId = g_LevelId;

  g_Gamestate = GS_LevelTransition;

  g_HasLevelTransition = 1;
  D_800756B0 = 1;

  g_StateSwitch = 1;
}

/// @brief Opens the inventory menu
// pEnteringFromGameplay is:
//   1 when entering the inventory screen directly from the game.
//   0 when entering the inventory screen from the pause menu.
void func_8002C714(int pEnteringFromGameplay) {
  if (pEnteringFromGameplay) {
    // Stop all sounds
    func_80056B28(0);
  }

  PlaySound(g_Spu.m_SoundTable->menuSound, nullptr, 0x10 /* 2D */, nullptr);

  D_800757CC = 0; // Transition progress between inventory pages.
  D_800756D4 = 0; // Inventory page transition state
  g_Gamestate = GS_InventoryMenu;

  // Set the current inventory screen to the current level's index / 6.
  // This causes the inventory screen to open up to page that shows the current
  // world.
  D_80075744 = g_LevelIndex / LEVEL_PER_HOMEWORLD;
  if (pEnteringFromGameplay) {
    D_800758B8 = 0; // Pause menu text rotation ticks
  }

  CheatResetBuffer();
}

/// @brief Unpauses from the inventory menu
void func_8002C7BC(void) {
  RECT rect;

  // Restores the VRAM that it overwrote for the background
  setRECT(&rect, 512, 0, 256, 225);
  LoadImage(&rect, (u_long *)((int)g_Buffers.m_HudOTStart - 115200));
  DrawSync(0);

  g_Gamestate = GS_Playing;

  SpecularReset();

  g_Hud.m_GemDisplayState = HDS_Hidden;
  g_Hud.m_DragonDisplayState = HDS_Hidden;
  g_Hud.m_LifeDisplayState = HDS_Hidden;
  g_Hud.m_EggDisplayState = HDS_Hidden;
  g_Hud.m_KeyDisplayState = HDS_Hidden;

  // Resume the level music
  func_800567F4(g_CdMusic.m_CurrentTrack, 8);
}

extern int D_8007593C;
extern int D_80075940;

/// @brief Die, lose a life and respawn or game over
void func_8002C85C(void) {
  int newState;
  if (D_8007582C != 0) {
    D_8007582C--;
    newState = GS_Respawn;
  } else {
    newState = GS_GameOver;
  }

  g_Gamestate = newState;

  D_80075940 = 0;
  D_8007593C = 0;
}

/// @brief Sets gamestate 0, resets background color, and resets the specular
void func_8002C8A4(void) {
  g_Gamestate = GS_Playing;

  setRGB0(&g_DB[0].m_DrawEnv, g_Cyclorama.m_BackgroundColor.r,
          g_Cyclorama.m_BackgroundColor.g, g_Cyclorama.m_BackgroundColor.b);

  setRGB0(&g_DB[1].m_DrawEnv, g_Cyclorama.m_BackgroundColor.r,
          g_Cyclorama.m_BackgroundColor.g, g_Cyclorama.m_BackgroundColor.b);

  SpecularReset();
}

/// @brief Empty, used to open the dragon dialogue in protos
void func_8002C914(void){};

/// @brief Empty, proto dragon dialogue update calls this for some reason
void func_8002C91C(void){};

/// @brief Rescue a dragon, increments the needed values and starts the cutscene
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestate_init", func_8002C924);

/// @brief Exit dragon cutscene, back to gamestate 0
void func_8002CB6C(void) {
  Moby *moby;
  int moby_idx;

  g_Gamestate = GS_Playing;

  // Turn off the screen border
  g_ScreenBorderEnabled = 0;

  moby_idx = ((RescuedDragonMobyProps *)(g_DragonCutscene.m_RescuedDragonMoby)
                  ->m_Props)
                 ->m_DragonPadLink;

  if (moby_idx != -1) {
    moby = &g_LevelMobys[moby_idx];
    moby->m_AnimationState.m_Animation = 0;
    moby->m_State = 1;
  }

  // Reset spyro
  func_8004AC24(1);

  g_Spyro.m_noGamepadUpdateFrames = 12;

  // put focus on spyro
  g_Camera.m_Focus = &g_Spyro.m_Position;
  g_Camera.m_State = 0;
  g_Camera.unk_0xC0 = 0;
  g_Camera.m_SphericalPreset = &D_8006C8BC;

  g_SpyroFlame.m_FairyKissTimer = g_SavedFairyKissTimer;

  g_Camera.m_FocusRotation = g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;

  // something for updating spherical coordinates
  func_80033F08(&g_Camera.m_Position);
  Memcpy(&D_8006C8BC, &g_Camera.m_Simulation, sizeof(D_8006C8BC));
  D_8006C8BC.m_Coords.azimuth =
      (D_8006C8BC.m_Coords.azimuth + g_Camera.m_FocusRotation) & 0xFFF;

  // some more camera reset
  func_80034358();

  // build out the HUD
  HudReset(0);

  // hide all the HUD stats
  g_Hud.m_GemDisplayState = HDS_Hidden;
  g_Hud.m_DragonDisplayState = HDS_Hidden;
  g_Hud.m_LifeDisplayState = HDS_Hidden;
  g_Hud.m_EggDisplayState = HDS_Hidden;
  g_Hud.m_KeyDisplayState = HDS_Hidden;

  // Resume the music
  func_800567F4(g_CdMusic.m_CurrentTrack, 8);
}

/**
 * @brief Initializes fairy cutscene when Spyro talks to a fairy.
 *
 * Sets up camera waypoints for the cutscene animation sequence. The camera
 * transitions through multiple positions: starting at current camera position,
 * moving to fairy's position, panning to Sparx, then settling at a viewing
 * angle for the save menu UI.
 *
 * Also determines which side of the screen to display the fairy menu based on
 * the camera's approach angle relative to the fairy's spawn position.
 *
 * @param pMoby The fairy moby that triggered the cutscene
 */
void InitFairyCutscene(Moby *pMoby) {
  Vector3D vec;
  void *pProps;
  void *pSpyroBodyAnimation;
  void *pSpyroPosition;
  int angle;
  int zPos;
  int fairyAngle;

  pProps = pMoby->m_Props;

  g_Gamestate = GS_Fairy;

  g_ScreenBorderEnabled = 1;
  g_StateSwitch = 1;

  g_FairyCutscene.m_State = 0;
  g_FairyCutscene.m_AnimationTimer = 0;
  g_FairyCutscene.m_MenuDialoguePage = 0;

  // Default to SAVE option if memory card present, otherwise CONTINUE
  if (g_FairyCutscene.m_HasMemoryCard != 0) {
    g_FairyCutscene.m_MenuSelectedOption = 0;
  } else {
    g_FairyCutscene.m_MenuSelectedOption = 2;
  }

  g_FairyCutscene.m_CutsceneFairy = pMoby;
  g_SavedFairyKissTimer = g_SpyroFlame.m_FairyKissTimer;
  PlaySound(g_Spu.m_SoundTable->menuSound, nullptr, 0x10, nullptr);
  func_8004AC24(1); // Reset Spyro, keeping position

  pSpyroBodyAnimation = &g_Spyro.m_bodyAnimation;

  // Set Spyro to idle animation
  g_Spyro.m_bodyAnimation = 1;
  g_Spyro.m_nextBodyAnimation = 1;
  g_Spyro.m_bodyAnimationFrame = 0;
  g_Spyro.m_nextBodyAnimationFrame = 1;
  g_Spyro.m_bodyFrameProgress = 0;

  g_FairyCutscene.m_unused_SavedSpyroRotZ =
      g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;

  // Calculate angle from Spyro to dragon pad's position
  g_FairyCutscene.m_AngleToDragonPad = Atan2(
      g_LevelMobys[((int *)pProps)[1]].m_Position.x - g_Spyro.m_Position.x,
      g_LevelMobys[((int *)pProps)[1]].m_Position.y - g_Spyro.m_Position.y, 1);

  // Calculate angle and distance from Spyro to fairy's current position
  g_FairyCutscene.m_AngleFromSpyro =
      Atan2(pMoby->m_Position.x - g_Spyro.m_Position.x,
            pMoby->m_Position.y - g_Spyro.m_Position.y, 1);

  pSpyroPosition = &g_Spyro.m_Position;

  VecSub(&vec, &pMoby->m_Position, (Vector3D *)pSpyroPosition);

  g_FairyCutscene.m_DistanceFromSpyro = VecMagnitude(&vec, 0);

  zPos = pMoby->m_Position.z;
  fairyAngle = g_FairyCutscene.m_AngleToDragonPad;

  // Camera waypoint 1: Start at fairy's height, looking toward spawn
  g_FairyCutscene.m_CameraInitDistance = 0x480;
  g_FairyCutscene.m_CameraInitZ = zPos;
  g_FairyCutscene.m_CameraInitAngle = fairyAngle;

  g_FairyCutscene.m_CameraTargetZ = g_Spyro.m_Position.z + 0x170;

  // Camera waypoint 2: Pan to Sparx if present
  if (g_Sparx != nullptr) {
    g_FairyCutscene.m_CameraTargetAngle =
        Atan2(g_Sparx->m_Position.x - g_Spyro.m_Position.x,
              g_Sparx->m_Position.y - g_Spyro.m_Position.y, 1);

    VecSub(&vec, &g_Sparx->m_Position, (Vector3D *)pSpyroPosition);
    g_FairyCutscene.m_CameraTargetDistance = VecMagnitude(&vec, 0);

    // Camera waypoint 3: End position 180 degrees from spawn
    g_FairyCutscene.m_CameraEndDistance = 0x600;
    g_FairyCutscene.m_CameraEndAngle =
        (g_FairyCutscene.m_AngleToDragonPad + 0x800) & 0xFFF;
  }

  // Record current camera position as animation start point
  g_FairyCutscene.m_CameraStartAngle =
      Atan2(g_Camera.m_Position.x - g_Spyro.m_Position.x,
            g_Camera.m_Position.y - g_Spyro.m_Position.y, 1);

  VecSub(&vec, &g_Camera.m_Position, (Vector3D *)pSpyroPosition);

  g_FairyCutscene.m_CameraStartDistance = VecMagnitude(&vec, 0);

  // Default menu to right side of screen (offset 0xB0)
  g_FairyCutscene.m_MenuOffsetX = 0xB0;

  // View angle ~45 degrees from spawn direction
  angle = (g_FairyCutscene.m_AngleToDragonPad + 0x30B) & 0xFFF;

  g_FairyCutscene.m_CameraStartZ = g_Camera.m_Position.z;
  g_FairyCutscene.m_CameraViewAngle = angle;

  // If camera approach angle is >90 degrees from view angle, flip to other side
  if (func_80017928(g_FairyCutscene.m_CameraStartAngle, angle) > 0x400) {
    g_FairyCutscene.m_MenuOffsetX = 0;
    g_FairyCutscene.m_CameraViewAngle =
        (g_FairyCutscene.m_AngleToDragonPad - 0x30B) & 0xFFF;
  }

  // Final viewing position for save menu
  g_FairyCutscene.m_CameraViewDistance = 0x4C9;
  g_FairyCutscene.m_CameraViewZ = g_Spyro.m_Position.z + 0x56B;
}

/// @brief Exit fairy
void func_8002D02C(void) {
  g_Gamestate = GS_Playing;

  // Turn off the screen border
  g_ScreenBorderEnabled = 0;

  SpecularReset();
  VecNull(&g_Spyro.m_HeadLookTarget);

  // reset spyro
  func_8004AC24(1);
  g_Spyro.unk_0x1b4 = 256;
  g_Spyro.m_headRotation.z = 16;
  g_Spyro.m_noGamepadUpdateFrames = 8;

  // put camera on spyro
  g_Camera.m_Focus = &g_Spyro.m_Position;
  g_Camera.m_State = 0;
  g_Camera.unk_0xC0 = 0;
  g_Camera.m_SphericalPreset = &D_8006C8BC;

  //?? some sort of counter
  g_SpyroFlame.m_FairyKissTimer = g_SavedFairyKissTimer;

  g_Camera.m_FocusRotation = g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;

  // something for updating spherical coordinates
  func_80033F08(&g_Camera.m_Position);
  Memcpy(&D_8006C8BC, &g_Camera.m_Simulation, sizeof(D_8006C8BC));
  D_8006C8BC.m_Coords.azimuth =
      (D_8006C8BC.m_Coords.azimuth + g_Camera.m_FocusRotation) & 0xFFF;

  // some more camera reset
  func_80034358();

  // build out the HUD
  HudReset(0);

  // hide all the HUD stats
  g_Hud.m_GemDisplayState = HDS_Hidden;
  g_Hud.m_DragonDisplayState = HDS_Hidden;
  g_Hud.m_LifeDisplayState = HDS_Hidden;
  g_Hud.m_EggDisplayState = HDS_Hidden;
  g_Hud.m_KeyDisplayState = HDS_Hidden;

  // Resume the music
  func_800567F4(g_CdMusic.m_CurrentTrack, 8);
}

/// @brief Start the titlescreen gamestate
void func_8002D170(void) {
  g_Gamestate = GS_TitleScreen;
  Memset(&g_TitlescreenState, 0, sizeof(g_TitlescreenState));

  D_80075754 = 10; // sound volume

  g_TitlescreenState.m_0x4C = (char *)g_Buffers.m_LowerPolyBuffer - 0x2000;

  g_Spu.unk_0x320 = 0x3FFF;
  D_80075748 = 10; // music volume
  g_Spu.m_MusicVolume = 0x5000;
  g_Spu.m_CommonAttr.cd.volume.left = g_Spu.m_MusicVolume;
  g_Spu.m_CommonAttr.cd.volume.right = g_Spu.m_MusicVolume;
  g_Spu.m_CommonAttr.mask = SPU_COMMON_CDVOLL | SPU_COMMON_CDVOLR;
  SpuSetCommonAttr(&g_Spu.m_CommonAttr);

  g_SkipLowPolyWorld = 0;
  g_CutsceneLayout->m_CurrentTick = 0;

  srand(345);
}

/**
 * @brief Initializes and starts the credits sequence.
 *
 * This function transitions the game into credits mode by:
 * 1. Clearing the entire framebuffer to black
 * 2. Stopping all audio (SPU voices and CD music)
 * 3. Optionally loading shared Spyro models from PETE.WAD
 * 4. Resetting Spyro's state machine
 * 5. Setting gamestate to GS_Credits and initializing credits variables
 * 6. Loading the credits overlay code from WAD.WAD
 *
 * Called in three contexts:
 * - Cheat code activation (pLoadSharedModels=0)
 * - After cutscene 2 / Gnasty's Loot intro (pLoadSharedModels=0)
 * - After cutscene 3 / 100% completion ending (pLoadSharedModels=1)
 *
 * The game has two credits sequences:
 * - Short credits (g_CreditsSequence=0): After defeating Gnasty Gnorc
 * - Full credits (g_CreditsSequence=10): After 100% completion
 *
 * @param pLoadSharedModels If non-zero, loads PETE.WAD containing Spyro's
 *                          shared models/animations needed for 100% credits.
 */
void InitCreditsSequence(int pLoadSharedModels) {
  char _pad[32]; // Stack padding to match original 72-byte frame
  RECT rect;
  int creditsType;

  // Clear the entire framebuffer to black
  setRECT(&rect, 0, 0, 512, 480);
  ClearImage(&rect, 0, 0, 0);
  DrawSync(0);

  // Stop all 24 SPU voice channels, clear moby sound refs, and stop CD music
  func_80056B28(0);
  SpuUpdate();

  // Load shared Spyro models from PETE.WAD if requested (for 100% credits)
  // This loads model data, patches pointers into g_Models[], and sets up
  // buffers
  if (pLoadSharedModels) {
    func_8005B7D8();
  }

  // Reset Spyro's state machine with full reset (preserves position/rotation)
  func_8004AC24(1);

  // Cache credits type before resetting state variables
  // g_CreditsSequence: 0 = short credits, 10 = full credits
  creditsType = g_CreditsSequence;

  // Set gamestate to credits mode
  g_Gamestate = GS_Credits;

  // Initialize credits sequence state variables
  g_CreditsStage = -1;
  g_CreditsEntryIndex = 0;
  g_CreditsDisplayedCount = 0;
  g_CreditsTotalEntries = 0;
  g_CreditsDataPtr = 0;
  g_CreditsBuffer = 0;
  g_CreditsTimer = 0;

  // Reset to short credits unless this is the full 100% credits sequence
  if (creditsType != 10) {
    g_CreditsSequence = 0;
  }

  // Load the credits overlay code from WAD.WAD into overlay memory
  // Timeout of 600 (10 seconds max read time)
  CDLoadSync(g_CdState.m_WadSector, g_OverlaySpacePointer,
             g_WadHeader.m_CreditsOverlay.m_Length,
             g_WadHeader.m_CreditsOverlay.m_Offset, 600);
}

/**
 * @brief Initializes and starts cutscene playback.
 *
 * This function transitions the game into cutscene mode by:
 * 1. Setting the gamestate to GS_Cutscene
 * 2. Resetting visual fade and tick counter
 * 3. Configuring SPU audio for cutscene playback at max volume
 * 4. Starting the cutscene audio via PlaySound
 *
 * Called in two contexts:
 * - During initial boot (from Initialize()) before switching to titlescreen
 * - After cutscene data finishes loading (when g_LoadStage >= 10)
 */
void StartCutscenePlayback(void) {
  int cutsceneIdx;

  // Set gamestate to cutscene mode (14 = GS_Cutscene)
  g_Gamestate = GS_Cutscene;

  // Reset fade (0 = no fade effect)
  g_Fade = 0;

  // Cache cutscene index and reset playback tick counter
  cutsceneIdx = g_CutsceneIdx;
  g_CutsceneLayout->m_CurrentTick = 0;

  // Intro cutscene special handling: skip low-poly world rendering
  if (cutsceneIdx == 1) {
    g_SkipLowPolyWorld = 1;
  }

  // Configure SPU sound definition for cutscene audio
  // Point to the temporary sound definition buffer
  g_Spu.m_SoundDefinitions = &g_CutsceneSoundDef;

  // Initialize the sound definition structure
  g_Spu.m_SoundDefinitions->m_Addr = 0x1010; // SPU address/flags
  g_Spu.m_SoundDefinitions->m_LoopAddr = -1; // -1 = looping audio
  g_Spu.m_SoundDefinitions->unk_0x8 = 0x50;  // Unused?
  g_Spu.m_SoundDefinitions->m_Pitch =
      g_CutscenePitchTable[cutsceneIdx];         // Cutscene-specific pitch
  g_Spu.m_SoundDefinitions->m_PitchVariance = 0; // No pitch randomization
  g_Spu.m_SoundDefinitions->m_PitchMultiplier = 0;
  g_Spu.m_SoundDefinitions->m_VarianceType = 0;

  // Enable volume override and set to max stereo volume (0x3FFF = 16383)
  // This ensures cutscene audio plays at full volume
  g_Spu.m_NextSoundOverrideFlags = 1;
  g_Spu.m_VolumeOverride.left = 0x3FFF;
  g_Spu.m_VolumeOverride.right = 0x3FFF;

  // Start cutscene audio playback
  PlaySound(0, 0, 0x10, (u_char *)&g_DragonCutscene.m_SoundVoice);
}

/**
 * @brief Ends cutscene playback and transitions to the next gamestate.
 *
 * Called when a cutscene finishes playing (tick >= duration * 2).
 * The transition depends on which cutscene just ended:
 *
 * - **Cutscene 1 (Intro "In the World of Dragons")**:
 *   Clears screen, stops all sounds, loads shared models from WAD.WAD,
 *   resets game state (gems, dragons, lives), and transitions to
 *   Artisans Home (level 10) with titlescreen overlay.
 *
 * - **Cutscene 2 (Credits Part 1)**:
 *   Plays the first credits sequence via func_8002D228(0).
 *
 * - **Cutscene 3 (Credits Part 2)**:
 *   Plays the second credits sequence via func_8002D228(1).
 */
void EndCutscenePlayback(void) {
  RECT rc;

  if (g_CutsceneIdx == 1) {
    // clear the screen
    setRECT(&rc, 0, 0, 0x200, 0x1E0);
    ClearImage(&rc, 0U, 0U, 0U);
    DrawSync(0);

    // stop all sounds
    func_80056B28(0);
    SpuUpdate();

    // load shared models from wad.wad
    func_8005B7D8();

    g_Gamestate = GS_TitleScreen;

    // reset/init this thing
    Memset(&g_TitlescreenState, 0, sizeof(g_TitlescreenState));
    g_TitlescreenState.m_Mode = TSM_Demo;
    g_TitlescreenState.m_State = TSS_Setup;
    g_TitlescreenState.m_DemoType = TSD_Level;

    // reset more stuff (also resets gems/dragons/lives/etc)
    func_8001277C();

    // change to artisans home
    g_LevelId = 10;
    g_StateSwitch = 1;
  } else if (g_CutsceneIdx == 2) {
    // play credits 1
    InitCreditsSequence(0);
    g_StateSwitch = 1;
  } else if (g_CutsceneIdx == 3) {
    // play credits 2
    g_CreditsSequence = 10;
    InitCreditsSequence(1);
    g_StateSwitch = 1;
  }
}

