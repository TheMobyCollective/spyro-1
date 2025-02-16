#include "camera.h"
#include "common.h"
#include "cyclorama.h"
#include "graphics.h"
#include "loaders.h"
#include "specular_and_metal.h"
#include "spu.h"
#include "spyro.h"
#include "variables.h"

extern int D_8007568C; // Pause menu no button ticks
extern int D_800758B8; // Pause menu text rotation ticks

extern int D_80075720; // Selected menu item index
extern int D_800757C8; // OptionsSubmenuIsOpen

extern char D_80077FA8;
extern char D_80077FA9;
extern char D_80077FAA;
extern char D_80077FAB;
extern char D_80077FAC;
extern char D_80077FAD;
extern char D_80077FAE;
extern char D_80077FAF;
extern char D_80077FB0;
extern char D_80077FB1;

/// @brief Pauses the game
// enteringFromGameplay is:
//   1 when entering the pause menu from the game.
//   0 when returning from the inventory screen to the pause menu
void func_8002C420(int enteringFromGameplay) {
    if (enteringFromGameplay != 0) {
        // Stop all sounds
        func_80056B28(0);
    }
    PlaySound(g_Spu.m_SoundTable->menuSound, nullptr, 0x10 /* 2D */, nullptr);
    g_Gamestate = 2;
    D_80075720 = 0; // Selected menu item index
    D_800757C8 = 0; // OptionsMenuIsOpen
    D_8007568C = 0; // Pause menu no button ticks
    if (D_80075690 != 0) { // If Spyro is in a flight level...
        if (enteringFromGameplay != 0) {
            D_800758B8 = 0; // Pause menu text rotation ticks
        }
    } else {
        // Something HUD-related
        func_80054600(0);
        if (enteringFromGameplay != 0) {
            D_800758B8 = 0; // Pause menu text rotation ticks
        } else {
            D_80077FA8 = 1;
            D_80077FA9 = 1;
            D_80077FAA = 1;
            D_80077FAB = 1;
            D_80077FAC = 1;
            D_80077FAD = 0xC;
            D_80077FAE = 0xC;
            D_80077FAF = 0xC;
            D_80077FB0 = 0xC;
            D_80077FB1 = 0xC;
        }
        // Something HUD-related
        func_80054988();
    }
}

extern int D_800774B0;
extern int D_800785F0;

/// @brief Unpauses the game, and sets the gamestate to 0
// The arg `always1` is always set to 1 in every call of this function.
void func_8002C534(int always1) {
    RECT rect;
    setRECT(&rect, 0x200, 0, 0x100, 0xE1);
    LoadImage(&rect, (u_long *)(D_800785F0 + 0xFFFE3E00));
    DrawSync(0);

    g_Gamestate = 0;

    SpecularReset();

    D_80077FA8 = 3;
    D_80077FA9 = 3;
    D_80077FAA = 3;
    D_80077FAB = 3;
    D_80077FAC = 3;
    D_80077FAD = 0xD;
    D_80077FAE = 0xD;
    D_80077FAF = 0xD;
    D_80077FB0 = 0xD;
    D_80077FB1 = 0xD;

    if (always1 != 0) {
        func_800567F4(D_800774B0, 8);
    }
}

/// @brief Exits level
void func_8002C618(void) {
  func_80056B28(0); // Stop all sounds
  g_Gamestate = 10; // Set gamestate to exit level
  D_8007568C = 0;   // Pause menu no button ticks
  D_800758B8 = 0;   // Pause menu text rotation ticks

  func_8004AC24(0); // Reset spyro
  func_8003EA68(0); // Set state to idle
}

/// @brief Return home, sets gamestate to 1
void func_8002C664(void) {
  SpecularReset();

  // Set the level you're traveling to
  // to the homeworld of the current level
  D_800758B4 = (g_LevelId / 10) * 10;

  g_LoadStage = 0;
  D_800756AC = 0;
  g_Camera.unk_0xC0 = 0x80000012;
  D_8007576C = -1;
  D_800758AC = g_LevelId;

  g_Gamestate = 1;

  D_800756D0 = 1;
  D_800756B0 = 1;

  g_StateSwitch = 1;
}

/// @brief Opens the inventory menu
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestate_init", func_8002C714);

/// @brief Unpauses from the inventory menu
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestate_init", func_8002C7BC);

extern int D_8007593C;
extern int D_80075940;

/// @brief Die, lose a life and respawn or game over
void func_8002C85C(void) {
  int newState;
  if (D_8007582C != 0) {
    D_8007582C--;
    newState = 4;
  } else {
    newState = 5;
  }

  g_Gamestate = newState;

  D_80075940 = 0;
  D_8007593C = 0;
}

/// @brief Sets gamestate 0, resets background color, and resets the specular
void func_8002C8A4(void) {
  g_Gamestate = 0;
  g_DB[0].m_DrawEnv.r0 = D_80078A40.m_BackgroundColor.r;
  g_DB[0].m_DrawEnv.g0 = D_80078A40.m_BackgroundColor.g;
  g_DB[0].m_DrawEnv.b0 = D_80078A40.m_BackgroundColor.b;
  g_DB[1].m_DrawEnv.r0 = D_80078A40.m_BackgroundColor.r;
  g_DB[1].m_DrawEnv.g0 = D_80078A40.m_BackgroundColor.g;
  g_DB[1].m_DrawEnv.b0 = D_80078A40.m_BackgroundColor.b;
  SpecularReset();
}

/// @brief Empty, used to open the dragon dialogue in protos
void func_8002C914(void){};

/// @brief Empty, used to update the dragon dialogue iirc?
void func_8002C91C(void){};

/// @brief Rescue a dragon, increments the needed values and starts the cutscene
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestate_init", func_8002C924);

/// @brief Exit dragon cutscene, back to gamestate 0
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestate_init", func_8002CB6C);

/// @brief Talk to a fairy
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestate_init", func_8002CCC8);

/// @brief Exit fairy
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestate_init", func_8002D02C);

/// @brief Start the titlescreen gamestate
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestate_init", func_8002D170);

/// @brief Plays the credits
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestate_init", func_8002D228);

/// @brief Starts cutscene
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestate_init", func_8002D338);

/// @brief Ends cutscene, moves to In the World of Dragons or plays credits
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestate_init", func_8002D440);
