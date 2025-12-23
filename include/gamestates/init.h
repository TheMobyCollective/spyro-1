#ifndef __GAMESTATE_INIT_H
#define __GAMESTATE_INIT_H

/// @brief Return home, sets gamestate to 1
void func_8002C664(void);

/// @brief Unpauses from the inventory menu
void func_8002C7BC(void);

/// @brief Initializes and starts the credits sequence
void InitCreditsSequence(int pLoadSharedModels);

#endif // !__GAMESTATE_INIT_H
