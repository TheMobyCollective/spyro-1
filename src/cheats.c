#include "cheats.h"
#include "camera.h"
#include "common.h"
#include "gamepad.h"
#include "gamestates/init.h"
#include "loaders.h"
#include "specular_and_metal.h"
#include "spu.h"
#include "spyro.h"

#define CHEAT_INPUT_BUFFER_SIZE 16
#define CHEAT_COUNT 8

// (Input buffer and counter are extern for fuck knows why)

extern int cheat_InputCounter; // Input counter, runs mod 16
extern int cheat_InputBuffer[CHEAT_INPUT_BUFFER_SIZE]; // Stores the inputs

// Ditto
extern int cheat_LevelSelected;     // Unused, stores the level you selected
extern int cheat_HomeworldSelected; // Saves the homeworld you select

/* clang-format off */ 

/**
 * Table that contains all the cheats, padded with NULL inputs.
 */
int CheatTable[CHEAT_COUNT][CHEAT_INPUT_BUFFER_SIZE] = {
    // Cheat 0 (unused / INVINCIBLE)
    {
      PAD_SQUARE,
      PAD_CIRCLE,
      PAD_CIRCLE,
      PAD_LEFT,
      PAD_SQUARE,
      PAD_CIRCLE,
      PAD_CIRCLE,
      PAD_UP,
      PAD_SQUARE,
      PAD_CIRCLE,
      PAD_CIRCLE,
      PAD_RIGHT
    },

    // Cheat 1 (unused level cheat / LEVEL WARP)
    {
      PAD_R1,
      PAD_R2,
      PAD_L1,
      PAD_L2,
      PAD_R1,
      PAD_L1,
      PAD_R2,
      PAD_L2
    },

    // Cheat 2 (Credits cheat / CREDITS)
    {
      PAD_LEFT,
      PAD_RIGHT,
      PAD_UP,
      PAD_DOWN,
      PAD_CIRCLE,
      PAD_CIRCLE,
      PAD_SQUARE,
      PAD_R1,
      PAD_R2,
      PAD_L1,
      PAD_L2
    },

    // Cheat 3 (Unlocks all levels / LEVELS OPEN)
    {
      PAD_SQUARE,
      PAD_SQUARE,
      PAD_CIRCLE,
      PAD_SQUARE,
      PAD_LEFT,
      PAD_RIGHT,
      PAD_LEFT,
      PAD_RIGHT,
      PAD_CIRCLE,
      PAD_UP,
      PAD_RIGHT,
      PAD_DOWN
    },

    // Cheat 4 (99 LIVES)
    {
      PAD_SQUARE,
      PAD_SQUARE,
      PAD_SQUARE,
      PAD_SQUARE,
      PAD_SQUARE,
      PAD_SQUARE,
      PAD_CIRCLE,
      PAD_UP,
      PAD_CIRCLE,
      PAD_LEFT,
      PAD_CIRCLE,
      PAD_RIGHT,
      PAD_CIRCLE,
    },

    // Cheat 5 (Unused unknown)
    {
      PAD_UP,
      PAD_DOWN,
      PAD_LEFT,
      PAD_RIGHT,
      PAD_UP,
      PAD_DOWN,
      PAD_LEFT,
      PAD_RIGHT,
      PAD_UP,
      PAD_DOWN,
      PAD_RIGHT,
      PAD_LEFT,
      PAD_CROSS,
    },

    // Cheat 6 (Unused unknown)
    {
      // Bunch of circles, then cross
      PAD_CIRCLE,
      PAD_CIRCLE,
      PAD_CIRCLE,
      PAD_CIRCLE,
      PAD_CIRCLE,
      PAD_CIRCLE,
      PAD_CIRCLE,
      PAD_CIRCLE,
      PAD_CIRCLE,
      PAD_CIRCLE,
      PAD_CIRCLE,
      PAD_CIRCLE,
      PAD_CIRCLE,
      PAD_CIRCLE,
      PAD_CIRCLE,
      PAD_CROSS,
    },

    // Cheat 7 (Unused unknown)
    {
      PAD_LEFT,
      PAD_RIGHT,
      PAD_SQUARE,
      PAD_CIRCLE,
      PAD_SQUARE,
      PAD_RIGHT,
      PAD_LEFT,
      PAD_DOWN,
      PAD_UP,
      PAD_L1,
      PAD_L2,
      PAD_R2,
      PAD_R1,
      PAD_TRIANGLE,
      PAD_CROSS,
    }
};
/* clang-format on */

// Resets cheat input buffer
void CheatResetBuffer(void) {
  int i;

  // Clear the cheat input buffer
  for (i = 0; i < 16; i++)
    cheat_InputBuffer[i] = 0;

  // Reset the input counter
  cheat_InputCounter = 0;
}

// Does the level warp cheat (which doesn't exist in the final game)
void CheatProcessLevelWarp(void) {
  int level;

  // If no input, return
  if (g_Pad.m_Down == 0)
    return;

  level = -1; // Default to invalid level

  // Handle button inputs to select level/homeworld
  switch (g_Pad.m_Down) {
  /* clang-format off */
  case PAD_CIRCLE:    level = 0; break;
  case PAD_CROSS:     level = 1; break;
  case PAD_SQUARE:    level = 2; break;
  case PAD_TRIANGLE:  level = 3; break;
  case PAD_RIGHT:     level = 4; break;
  case PAD_DOWN:      level = 5; break;
  case PAD_LEFT:      level = 6; break;
  /* clang-format on */
  case PAD_UP:
    // Move to next level
    g_NextLevelId = g_LevelId + 1;
    if ((g_NextLevelId % 10) > 5) {
      g_NextLevelId = ((g_NextLevelId / 10) + 1) * 10;
    }
    if (g_NextLevelId < 10 || g_NextLevelId > 64) {
      g_NextLevelId = 10;
    }
    cheat_HomeworldSelected = g_NextLevelId / 10;
    level = g_NextLevelId % 10;
    break;
  }

  // If a valid level was selected
  if (level >= 0) {

    // If a homeworld was already selected, warp to the level
    if (cheat_HomeworldSelected != 0) {
      // Calculate target level
      cheat_LevelSelected = level;
      g_NextLevelId = cheat_HomeworldSelected * 10 + cheat_LevelSelected;

      // Check if level is valid
      if (g_NextLevelId < 10 || g_NextLevelId >= 65 || level >= 6) {
        // If it isn't, set the target level to the current level
        // to not break the game similar to Tuco
        g_NextLevelId = g_LevelId;
      } else {
        // Reset game state for level transition
        func_80056B28(0); // Stop all sounds
        SpecularReset();  // Reset specular table

        g_PortalLevelId = 0; // Reset portal level id
        D_8007576C = -1;     // Reset loading part

        func_8004AC24(0);  // Reset Spyro
        func_8003FDC8(15); // Reset Spyro to gliding state

        // Set level transition flags
        g_Gamestate = GS_LevelTransition; // Set gamestate to loading
        g_LoadStage = 1;                  // Set load stage to 1
        g_HasLevelTransition = 0;         // Set no level transition
        D_800756B0 = 0;                   // Set no transition text
        g_StateSwitch = 1; // Set skip draw routine due to gamestate switch

        g_Camera.unk_0xC0 = 0x80000012;
      }

      g_LevelCheatActive = 0; // Deactivate cheat
      return;
    }

    // If no homeworld was selected, set the homeworld
    cheat_HomeworldSelected = level;
  }
}

// Applies the cheat effect based on the input id
void CheatApplyEffect(int pCheatId) {
  int i;
  switch (pCheatId) {
  case 2: // Credits cheat
    D_80075818 = g_LevelId;
    InitCreditsSequence(0);

    // Confirmation sound
    PlaySound(g_Spu.m_SoundTable->gemPickup, nullptr, 0x10 /* 2D space */,
              nullptr);
    break;

  case 3: // Unlock all levels cheat
    for (i = 0; i < 32; i++)
      g_VisitedFlags.m_Levels[i] = 1;
    for (i = 0; i < 6; i++)
      D_800758D0[i] = 2;

    // Confirmation sound
    PlaySound(g_Spu.m_SoundTable->gemPickup, nullptr, 0x10 /* 2D space */,
              nullptr);
    break;

  case 4: // 99 Lives cheat
    D_8007582C = 99;

    // SKELETON: They forgot the confirmation sound???
    break;
  }
}

// Checks and then applies cheat codes
void CheatsProcess(void) {
  int i, j, k, match, cheatLength;

  // Not if loading or no input
  if (g_LoadStage >= 0 || g_Pad.m_Down == 0) {
    return;
  }

  // Add input to buffer
  cheat_InputBuffer[cheat_InputCounter] = g_Pad.m_Down;

  // Increment input counter and wrap it
  if (++cheat_InputCounter >= CHEAT_INPUT_BUFFER_SIZE)
    cheat_InputCounter = 0;

  // Loop through cheats
  for (i = 0; i < CHEAT_COUNT; i++) {

    // Get cheat length
    for (cheatLength = 0; CheatTable[i][cheatLength] != 0; cheatLength++)
      if (cheatLength >= CHEAT_INPUT_BUFFER_SIZE)
        break;

    if (cheatLength == 0) // Skip empty cheats (shouldn't happen...)
      continue;

    k = cheat_InputCounter; // Start at current input

    // SKELETON: You could calculate the start index directly rather than
    // looping, i.e. k = (cheat_InputCounter - cheatLength) & 0xF or
    // (cheat_InputCounter - cheatLength + CHEAT_INPUT_BUFFER_SIZE) %
    // CHEAT_INPUT_BUFFER_SIZE.
    // Turns out this is something that Spyro 3
    // actually fixed! there they do (cheat_InputCounter - cheatLength) and if
    // it's negative they add CHEAT_INPUT_BUFFER_SIZE

    // Calculate start index
    for (j = 0; j < cheatLength; j++)
      if (--k < 0) // Move backwards, wrap around back to 15 when reaching 0
        k = CHEAT_INPUT_BUFFER_SIZE - 1;

    // Check if cheat matches
    match = 1;

    for (j = 0; j < cheatLength; j++) {
      // If the input didn't match, break
      if (!match)
        break;

      // Check if input matches cheat, if it doesn't, set match to false
      if (cheat_InputBuffer[k] != CheatTable[i][j])
        match = 0;

      // Move forward, wrap around back to 0 when reaching 15
      if (++k >= CHEAT_INPUT_BUFFER_SIZE)
        k = 0;
    }

    // If cheat matches, apply effect
    if (match) {
      CheatApplyEffect(i);
      CheatResetBuffer();
      return;
    }
  }
}