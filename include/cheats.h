#ifndef __CHEATS_H
#define __CHEATS_H

#include <sys/types.h>

extern int g_LevelCheatActive; // Level cheat active flag

/// @brief Resets the cheat input buffer
void CheatResetBuffer(void);

/// @brief Processes the level warp cheat
void CheatProcessLevelWarp(void);

/// @brief Processes inputs and applies cheat effects
void CheatsProcess(void);

#endif
