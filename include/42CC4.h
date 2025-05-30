#ifndef __42CC4_H
#define __42CC4_H

#include "moby.h"

/// @brief Allocates a new Moby
Moby *func_800524C4(void);

/// @brief Frees a Moby
void func_80052568(Moby *pMoby);

/// @brief
void func_800529CC(Moby *pMoby);

/// @brief Updates a Moby's shadow
void func_800533D0(Moby *pMoby);

/// @brief Creates the death sparks and poofs
void func_800530C0(Moby *pMoby, int pSomething);

#endif