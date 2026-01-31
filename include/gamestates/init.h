#ifndef __GAMESTATE_INIT_H
#define __GAMESTATE_INIT_H

#include "moby.h"

/// @brief Return home, sets gamestate to 1
void func_8002C664(void);

/// @brief Unpauses from the inventory menu
void func_8002C7BC(void);

/// @brief Initializes and starts the credits sequence
void InitCreditsSequence(int pLoadSharedModels);

/// @brief Opens the pause menu
/// @param pEnteringFromGameplay
void func_8002C420(int pEnteringFromGameplay);

/// @brief Opens the inventory menu
/// @param pEnteringFromGameplay
void func_8002C714(int pEnteringFromGameplay);

/// @brief Exits level
void func_8002C618(void);

/// @brief Empty, proto dragon dialogue update calls this for some reason
void func_8002C91C(void);

/**
 * @brief Initializes fairy cutscene when Spyro talks to a fairy
 * @param pMoby The fairy moby that triggered the cutscene
 */
void InitFairyCutscene(Moby *pMoby);

/// @brief Exits fairy cutscene and returns to gameplay
void func_8002D02C(void);

#endif // !__GAMESTATE_INIT_H

