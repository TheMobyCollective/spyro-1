#include "common.h"
#include "cyclorama.h"
#include "graphics.h"
#include "specular_and_metal.h"
#include "spu.h"
#include "spyro.h"
#include "variables.h"

extern int D_8007568C; // Pause menu no button ticks
extern int D_800758B8; // Pause menu text rotation ticks

/// @brief Pauses the game
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestate_init", func_8002C420);

/// @brief Unpauses the game, and sets the gamestate to 0
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestate_init", func_8002C534);

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
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/gamestate_init", func_8002C664);

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
